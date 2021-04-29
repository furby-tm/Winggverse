#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/unitTestHelper.h"
/*
 * Copyright 2021 Forge. All Rights Reserved.
 *
 * The use of this software is subject to the terms of the
 * Forge license agreement provided at the time of installation
 * or download, or which otherwise accompanies this software in
 * either electronic or hard copy form.
 *
 * Portions of this file are derived from original work by Pixar
 * distributed with Universal Scene Description, a project of the
 * Academy Software Foundation (ASWF). https://www.aswf.io/
 *
 * Original Copyright (C) 2016-2021 Pixar.
 * Modifications copyright (C) 2020-2021 ForgeXYZ LLC.
 *
 * Forge. The Animation Software & Motion Picture Co.
 */
#ifndef FORGE_USD_IMAGING_USD_IMAGING_UNIT_TEST_HELPER_H
#define FORGE_USD_IMAGING_USD_IMAGING_UNIT_TEST_HELPER_H

/// \file usdImaging/unitTestHelper.h

#include "forge/forge.h"
#include "forge/usdImaging/usdImaging/delegate.h"

#include "forge/imaging/hd/changeTracker.h"
#include "forge/imaging/hd/engine.h"
#include "forge/imaging/hd/renderIndex.h"
#include "forge/imaging/hd/renderPass.h"
#include "forge/imaging/hd/rprim.h"
#include "forge/imaging/hd/rprimCollection.h"
#include "forge/imaging/hd/tokens.h"
#include "forge/imaging/hd/unitTestNullRenderDelegate.h"
#include "forge/imaging/hd/unitTestNullRenderPass.h"

#include <memory>
#include <string>

FORGE_NAMESPACE_BEGIN

using HdRenderPassSharedPtr = std::shared_ptr<HdRenderPass>;

/// A simple test task that just causes sync processing
class UsdImaging_TestTask final : public HdTask
{
public:
    UsdImaging_TestTask(HdRenderPassSharedPtr const &renderPass,
                        TfTokenVector const &renderTags)
        : HdTask(SdfPath::EmptyPath())
        , _renderPass(renderPass)
        , _renderTags(renderTags)
    {
    }

    virtual void Sync(HdSceneDelegate* delegate,
                      HdTaskContext* ctx,
                      HdDirtyBits* dirtyBits) override {
        _renderPass->Sync();

        *dirtyBits = HdChangeTracker::Clean;
    }

    virtual void Prepare(HdTaskContext* ctx,
                         HdRenderIndex* renderIndex) override {
    }

    virtual void Execute(HdTaskContext* ctx) override {
    }

    virtual const TfTokenVector &GetRenderTags() const override {
        return _renderTags;
    }

private:
    HdRenderPassSharedPtr _renderPass;
    TfTokenVector _renderTags;
};

/// \class UsdImaging_TestDriver
///
/// A unit test driver that exercises the core engine.
///
/// \note This test driver uses a Null render delegate, so
/// no images are produced.  It just tests interaction between Hydra and
/// UsdImaging during Hydra's Sync phase. of Hydra
///
class UsdImaging_TestDriver final {
public:
    UsdImaging_TestDriver(std::string const& usdFilePath)
        : _engine()
        , _renderDelegate()
        , _renderIndex(nullptr)
        , _delegate(nullptr)
        , _geometryPass()
        , _stage()
    {
        HdRprimCollection collection = HdRprimCollection(
                HdTokens->geometry,
                HdReprSelector(HdReprTokens->hull));

        TfTokenVector renderTags;
        renderTags.push_back(HdRenderTagTokens->geometry);

        _Init(UsdStage::Open(usdFilePath),
              collection,
              SdfPath::AbsoluteRootPath(),
              renderTags);
    }

    UsdImaging_TestDriver(std::string const& usdFilePath,
                          TfToken const &collectionName,
                          TfToken const &reprName,
                          TfTokenVector const &renderTags)
        : _engine()
        , _renderDelegate()
        , _renderIndex(nullptr)
        , _delegate(nullptr)
        , _geometryPass()
        , _stage()
    {
        HdRprimCollection collection = HdRprimCollection(
                collectionName,
                HdReprSelector(reprName));

        _Init(UsdStage::Open(usdFilePath),
              collection,
              SdfPath::AbsoluteRootPath(),
              renderTags);
    }

    UsdImaging_TestDriver(UsdStageRefPtr const& usdStage)
        : _engine()
        , _renderDelegate()
        , _renderIndex(nullptr)
        , _delegate(nullptr)
        , _geometryPass()
        , _stage()
    {
        HdRprimCollection collection = HdRprimCollection(
                HdTokens->geometry,
                HdReprSelector(HdReprTokens->hull));

        TfTokenVector renderTags;
        renderTags.push_back(HdRenderTagTokens->geometry);

        _Init(usdStage, collection, SdfPath::AbsoluteRootPath(), renderTags);
    }

    UsdImaging_TestDriver(UsdStageRefPtr const& usdStage,
                          TfToken const &collectionName,
                          TfToken const &reprName,
                          TfTokenVector const &renderTags)
        : _engine()
        , _renderDelegate()
        , _renderIndex(nullptr)
        , _delegate(nullptr)
        , _geometryPass()
        , _stage()
    {
        HdRprimCollection collection = HdRprimCollection(
                collectionName,
                HdReprSelector(reprName));

        _Init(usdStage, collection, SdfPath::AbsoluteRootPath(), renderTags);
    }

    UsdImaging_TestDriver(UsdStageRefPtr const& usdStage,
                          HdRprimCollection const &collection,
                          SdfPath const &delegateId,
                          TfTokenVector const &renderTags)
        : _engine()
        , _renderDelegate()
        , _renderIndex(nullptr)
        , _delegate(nullptr)
        , _geometryPass()
        , _stage()
    {
        _Init(usdStage, collection, delegateId, renderTags);
    }

    ~UsdImaging_TestDriver()
    {
        delete _delegate;
        delete _renderIndex;
    }

    void Draw() {
        HdTaskSharedPtrVector tasks = {
            std::make_shared<UsdImaging_TestTask>(_geometryPass, _renderTags)
        };
        _engine.Execute(&_delegate->GetRenderIndex(), &tasks);
    }
    void SetTime(double time) {
        _delegate->SetTime(time);
    }

    /// Marks an rprim in the RenderIndex as dirty with the given dirty flags.
    void MarkRprimDirty(SdfPath path, HdDirtyBits flag) {
        _delegate->GetRenderIndex().GetChangeTracker()
            .MarkRprimDirty(path, flag);
    }

    /// Returns the underlying delegate for this driver.
    UsdImagingDelegate& GetDelegate() {
        return *_delegate;
    }

    /// Returns the populated UsdStage for this driver.
    UsdStageRefPtr const& GetStage() {
        return _stage;
    }

private:
    HdEngine _engine;
    Hd_UnitTestNullRenderDelegate _renderDelegate;
    HdRenderIndex       *_renderIndex;
    UsdImagingDelegate  *_delegate;
    HdRenderPassSharedPtr _geometryPass;
    UsdStageRefPtr _stage;
    TfTokenVector _renderTags;

    void _Init(UsdStageRefPtr const& usdStage,
               HdRprimCollection const &collection,
               SdfPath const &delegateId,
               TfTokenVector const &renderTags) {
        _renderIndex = HdRenderIndex::New(&_renderDelegate, HdDriverVector());
        TF_VERIFY(_renderIndex != nullptr);
        _delegate = new UsdImagingDelegate(_renderIndex, delegateId);

        _stage = usdStage;
        _delegate->Populate(_stage->GetPseudoRoot());

        _geometryPass = HdRenderPassSharedPtr(
                       new Hd_UnitTestNullRenderPass(_renderIndex, collection));

        _renderTags = renderTags;
    }
};

FORGE_NAMESPACE_END

#endif //FORGE_USD_IMAGING_USD_IMAGING_UNIT_TEST_HELPER_H
