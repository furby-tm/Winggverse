#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/unitTestDelegate.h"
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
#ifndef FORGE_IMAGING_HDX_UNIT_TEST_DELEGATE_H
#define FORGE_IMAGING_HDX_UNIT_TEST_DELEGATE_H

#include "forge/forge.h"
#include "forge/imaging/hd/sceneDelegate.h"
#include "forge/imaging/hd/tokens.h"
#include "forge/imaging/glf/simpleLight.h"
#include "forge/imaging/pxOsd/tokens.h"

#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec4f.h"
#include "forge/base/gf/vec4d.h"
#include "forge/base/gf/matrix4f.h"
#include "forge/base/gf/matrix4d.h"
#include "forge/base/vt/array.h"

FORGE_NAMESPACE_BEGIN

template <typename T>
static VtArray<T>
_BuildArray(T values[], int numValues)
{
    VtArray<T> result(numValues);
    std::copy(values, values+numValues, result.begin());
    return result;
}

class Hdx_UnitTestDelegate : public HdSceneDelegate
{
public:
    Hdx_UnitTestDelegate(HdRenderIndex *renderIndex);

    void SetRefineLevel(int level);

    // camera
    void SetCamera(GfMatrix4d const &viewMatrix, GfMatrix4d const &projMatrix);
    void SetCamera(
        SdfPath const &id,
        GfMatrix4d const &viewMatrix,
        GfMatrix4d const &projMatrix);
    void AddCamera(SdfPath const &id);

    // light
    void AddLight(SdfPath const &id, GlfSimpleLight const &light);
    void SetLight(SdfPath const &id, TfToken const &key, VtValue value);

    // draw target
    void AddDrawTarget(SdfPath const &id);
    void SetDrawTarget(SdfPath const &id, TfToken const &key, VtValue value);

    // tasks
    void AddRenderTask(SdfPath const &id);
    void AddRenderSetupTask(SdfPath const &id);
    void AddSimpleLightTask(SdfPath const &id);
    void AddShadowTask(SdfPath const &id);
    void AddSelectionTask(SdfPath const &id);
    void AddDrawTargetTask(SdfPath const &id);
    void AddPickTask(SdfPath const &id);

    void SetTaskParam(SdfPath const &id, TfToken const &name, VtValue val);
    VtValue GetTaskParam(SdfPath const &id, TfToken const &name);
    HdRenderBufferDescriptor GetRenderBufferDescriptor(SdfPath const &id) override;

    /// Instancer
    void AddInstancer(SdfPath const &id,
                      SdfPath const &parentId=SdfPath(),
                      GfMatrix4f const &rootTransform=GfMatrix4f(1));

    void SetInstancerProperties(SdfPath const &id,
                                VtIntArray const &prototypeIndex,
                                VtVec3fArray const &scale,
                                VtVec4fArray const &rotate,
                                VtVec3fArray const &translate);

    /// Material
    void AddMaterialResource(SdfPath const &id,
                             VtValue materialResource);

    void BindMaterial(SdfPath const &rprimId, SdfPath const &materialId);

    // prims
    void AddMesh(SdfPath const &id,
                 GfMatrix4d const &transform,
                 VtVec3fArray const &points,
                 VtIntArray const &numVerts,
                 VtIntArray const &verts,
                 bool guide=false,
                 SdfPath const &instancerId=SdfPath(),
                 TfToken const &scheme=PxOsdOpenSubdivTokens->catmullClark,
                 TfToken const &orientation=HdTokens->rightHanded,
                 bool doubleSided=false);

    void AddMesh(SdfPath const &id,
                 GfMatrix4d const &transform,
                 VtVec3fArray const &points,
                 VtIntArray const &numVerts,
                 VtIntArray const &verts,
                 PxOsdSubdivTags const &subdivTags,
                 VtValue const &color,
                 HdInterpolation colorInterpolation,
                 VtValue const &opacity,
                 HdInterpolation opacityInterpolation,
                 bool guide=false,
                 SdfPath const &instancerId=SdfPath(),
                 TfToken const &scheme=PxOsdOpenSubdivTokens->catmullClark,
                 TfToken const &orientation=HdTokens->rightHanded,
                 bool doubleSided=false);

    void AddCube(SdfPath const &id, GfMatrix4d const &transform,
                 bool guide=false,
                 SdfPath const &instancerId=SdfPath(),
                 TfToken const &scheme=PxOsdOpenSubdivTokens->catmullClark,
                 VtValue const &color = VtValue(GfVec3f(1,1,1)),
                 HdInterpolation colorInterpolation = HdInterpolationConstant,
                 VtValue const &opacity = VtValue(1.0f),
                 HdInterpolation opacityInterpolation = HdInterpolationConstant);

    void AddGrid(SdfPath const &id, GfMatrix4d const &transform,
                 bool guide=false, SdfPath const &instancerId=SdfPath());

    void AddTet(SdfPath const &id, GfMatrix4d const &transform,
                 bool guide=false, SdfPath const &instancerId=SdfPath(),
                 TfToken const &scheme=PxOsdOpenSubdivTokens->catmullClark);

    void SetRefineLevel(SdfPath const &id, int level);

    void SetReprName(SdfPath const &id, TfToken const &reprName);

    // delegate methods
    GfRange3d GetExtent(SdfPath const & id) override;
    GfMatrix4d GetTransform(SdfPath const & id) override;
    bool GetVisible(SdfPath const& id) override;
    HdMeshTopology GetMeshTopology(SdfPath const& id) override;
    VtValue Get(SdfPath const& id, TfToken const& key) override;
    HdPrimvarDescriptorVector GetPrimvarDescriptors(
        SdfPath const& id,
        HdInterpolation interpolation) override;
    VtIntArray GetInstanceIndices(
        SdfPath const& instancerId,
        SdfPath const& prototypeId) override;

    GfMatrix4d GetInstancerTransform(SdfPath const& instancerId) override;
    HdDisplayStyle GetDisplayStyle(SdfPath const& id) override;
    HdReprSelector GetReprSelector(SdfPath const &id) override;

    SdfPath GetMaterialId(SdfPath const &rprimId) override;
    VtValue GetMaterialResource(SdfPath const &materialId) override;

    SdfPath GetInstancerId(SdfPath const &primId) override;

    VtValue GetCameraParamValue(
        SdfPath const &cameraId,
        TfToken const &paramName) override;

    TfTokenVector GetTaskRenderTags(SdfPath const& taskId) override;

private:
    struct _Mesh {
        _Mesh() { }
        _Mesh(TfToken const &scheme,
              TfToken const &orientation,
              GfMatrix4d const &transform,
              VtVec3fArray const &points,
              VtIntArray const &numVerts,
              VtIntArray const &verts,
              PxOsdSubdivTags const &subdivTags,
              VtValue const &color,
              HdInterpolation colorInterpolation,
              VtValue const &opacity,
              HdInterpolation opacityInterpolation,
              bool guide,
              bool doubleSided) :
            scheme(scheme), orientation(orientation),
            transform(transform),
            points(points), numVerts(numVerts), verts(verts),
            subdivTags(subdivTags), color(color),
            colorInterpolation(colorInterpolation), opacity(opacity),
            opacityInterpolation(opacityInterpolation), guide(guide),
            doubleSided(doubleSided) { }

        TfToken scheme;
        TfToken orientation;
        GfMatrix4d transform;
        VtVec3fArray points;
        VtIntArray numVerts;
        VtIntArray verts;
        PxOsdSubdivTags subdivTags;
        VtValue color;
        HdInterpolation colorInterpolation;
        VtValue opacity;
        HdInterpolation opacityInterpolation;
        bool guide;
        bool doubleSided;
        TfToken reprName;
    };

    struct _Instancer {
        _Instancer() { }
        _Instancer(VtVec3fArray const &scale,
                   VtVec4fArray const &rotate,
                   VtVec3fArray const &translate,
                   GfMatrix4f const &rootTransform) :
            scale(scale), rotate(rotate), translate(translate),
            rootTransform(rootTransform) {
        }
        VtVec3fArray scale;
        VtVec4fArray rotate;
        VtVec3fArray translate;
        VtIntArray prototypeIndices;
        GfMatrix4f rootTransform;

        std::vector<SdfPath> prototypes;
    };
    struct _DrawTarget {
    };
    std::map<SdfPath, _Mesh> _meshes;
    std::map<SdfPath, _Instancer> _instancers;
    std::map<SdfPath, VtValue> _materials;
    std::map<SdfPath, int> _refineLevels;
    std::map<SdfPath, _DrawTarget> _drawTargets;
    int _refineLevel;

    using SdfPathMap = std::map<SdfPath, SdfPath>;
    SdfPathMap _materialBindings;
    SdfPathMap _instancerBindings;

    using _ValueCache = TfHashMap<TfToken, VtValue, TfToken::HashFunctor>;
    using _ValueCacheMap = TfHashMap<SdfPath, _ValueCache, SdfPath::Hash>;
    _ValueCacheMap _valueCacheMap;

    SdfPath _cameraId;
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HDX_UNIT_TEST_DELEGATE_H
