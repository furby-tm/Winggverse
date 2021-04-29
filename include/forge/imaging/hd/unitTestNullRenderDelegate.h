#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/unitTestNullRenderDelegate.h"
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
#ifndef FORGE_IMAGING_HD_UNIT_TEST_NULL_RENDER_DELEGATE_H
#define FORGE_IMAGING_HD_UNIT_TEST_NULL_RENDER_DELEGATE_H

#include "forge/forge.h"
#include "forge/imaging/hd/renderDelegate.h"
#include "forge/imaging/hd/instancer.h"

FORGE_NAMESPACE_BEGIN

class Hd_UnitTestNullRenderDelegate final : public HdRenderDelegate
{
public:
    Hd_UnitTestNullRenderDelegate() = default;
    virtual ~Hd_UnitTestNullRenderDelegate() = default;

    virtual const TfTokenVector &GetSupportedRprimTypes() const override;
    virtual const TfTokenVector &GetSupportedSprimTypes() const override;
    virtual const TfTokenVector &GetSupportedBprimTypes() const override;
    virtual HdRenderParam *GetRenderParam() const override;
    virtual HdResourceRegistrySharedPtr GetResourceRegistry() const override;

    ////////////////////////////////////////////////////////////////////////////
    ///
    /// Renderpass factory
    ///
    ////////////////////////////////////////////////////////////////////////////

    virtual HdRenderPassSharedPtr CreateRenderPass(HdRenderIndex *index,
                HdRprimCollection const& collection) override;

    ////////////////////////////////////////////////////////////////////////////
    ///
    /// Instancer Factory
    ///
    ////////////////////////////////////////////////////////////////////////////

    virtual HdInstancer *CreateInstancer(HdSceneDelegate *delegate,
                                         SdfPath const& id) override;

    virtual void DestroyInstancer(HdInstancer *instancer) override;

    ////////////////////////////////////////////////////////////////////////////
    ///
    /// Prim Factories
    ///
    ////////////////////////////////////////////////////////////////////////////

    virtual HdRprim *CreateRprim(TfToken const& typeId,
                                 SdfPath const& rprimId) override;

    virtual void DestroyRprim(HdRprim *rPrim) override;

    virtual HdSprim *CreateSprim(TfToken const& typeId,
                                 SdfPath const& sprimId) override;

    virtual HdSprim *CreateFallbackSprim(TfToken const& typeId) override;
    virtual void DestroySprim(HdSprim *sprim) override;

    virtual HdBprim *CreateBprim(TfToken const& typeId,
                                 SdfPath const& bprimId) override;

    virtual HdBprim *CreateFallbackBprim(TfToken const& typeId) override;

    virtual void DestroyBprim(HdBprim *bprim) override;

    ////////////////////////////////////////////////////////////////////////////
    ///
    /// Sync, Execute & Dispatch Hooks
    ///
    ////////////////////////////////////////////////////////////////////////////

    virtual void CommitResources(HdChangeTracker *tracker) override;



private:
    static const TfTokenVector SUPPORTED_RPRIM_TYPES;
    static const TfTokenVector SUPPORTED_SPRIM_TYPES;
    static const TfTokenVector SUPPORTED_BPRIM_TYPES;

    Hd_UnitTestNullRenderDelegate(
                                const Hd_UnitTestNullRenderDelegate &) = delete;
    Hd_UnitTestNullRenderDelegate &operator =(
                                const Hd_UnitTestNullRenderDelegate &) = delete;

};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_UNIT_TEST_NULL_RENDER_DELEGATE_H
