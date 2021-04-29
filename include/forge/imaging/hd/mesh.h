#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/mesh.h"
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
#ifndef FORGE_IMAGING_HD_MESH_H
#define FORGE_IMAGING_HD_MESH_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/meshTopology.h"
#include "forge/imaging/hd/rprim.h"
#include "forge/imaging/hd/tokens.h"
#include "forge/imaging/pxOsd/subdivTags.h"

FORGE_NAMESPACE_BEGIN

#define HD_MESH_REPR_DESC_TOKENS \
    (surfaceShader)              \
    (surfaceShaderUnlit)         \
    (surfaceShaderSheer)         \
    (surfaceShaderOutline)       \
    (constantColor)              \
    (hullColor)                  \
    (pointColor)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdMeshReprDescTokens, HD_API, HD_MESH_REPR_DESC_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/// \class HdMeshReprDesc
///
/// Descriptor to configure the drawItem(s) for a repr
///
struct HdMeshReprDesc {
    HdMeshReprDesc(HdMeshGeomStyle geomStyle = HdMeshGeomStyleInvalid,
                   HdCullStyle cullStyle = HdCullStyleDontCare,
                   TfToken shadingTerminal = HdMeshReprDescTokens->surfaceShader,
                   bool flatShadingEnabled = true,
                   bool blendWireframeColor = true,
                   bool doubleSided = false,
                   float lineWidth = 0,
                   bool useCustomDisplacement = true,
                   bool enableScalarOverride = true)
        : geomStyle(geomStyle)
        , cullStyle(cullStyle)
        , shadingTerminal(shadingTerminal)
        , flatShadingEnabled(flatShadingEnabled)
        , blendWireframeColor(blendWireframeColor)
        , doubleSided(doubleSided)
        , lineWidth(lineWidth)
        , useCustomDisplacement(useCustomDisplacement)
        , enableScalarOverride(enableScalarOverride)
        {}

    bool IsEmpty() const {
        return geomStyle == HdMeshGeomStyleInvalid;
    }

    /// The rendering style: draw refined/unrefined, edge, points, etc.
    HdMeshGeomStyle geomStyle;
    /// The culling style: draw front faces, back faces, etc.
    HdCullStyle     cullStyle;
    /// Specifies how the fragment color should be computed from surfaceShader;
    /// this can be used to render a mesh lit, unlit, unshaded, etc.
    TfToken         shadingTerminal;
    /// Does this mesh want flat shading?
    bool            flatShadingEnabled;
    /// Should the wireframe color be blended into the color primvar?
    bool            blendWireframeColor;
    /// Should this mesh be treated as double-sided? The resolved value is
    /// (prim.doubleSided || repr.doubleSided).
    bool            doubleSided;
    /// How big (in pixels) should line drawing be?
    float           lineWidth;
    /// Should this mesh use displacementShader() to displace points?
    bool            useCustomDisplacement;
    /// Should scalar override be allowed on this drawItem.
    /// scalar override allows for visualization of a single float value
    /// across a prim.
    bool            enableScalarOverride;
};

/// Hydra Schema for a subdivision surface or poly-mesh object.
///
class HdMesh : public HdRprim {
public:
    HD_API
    virtual ~HdMesh();

    ///
    /// Render State
    ///
    inline bool        IsDoubleSided(HdSceneDelegate* delegate) const;
    inline HdCullStyle GetCullStyle(HdSceneDelegate* delegate)  const;
    inline VtValue     GetShadingStyle(HdSceneDelegate* delegate)  const;

    ///
    /// Topological accessors via the scene delegate
    ///
    inline HdMeshTopology  GetMeshTopology(HdSceneDelegate* delegate) const;
    inline HdDisplayStyle  GetDisplayStyle(HdSceneDelegate* delegate)  const;
    inline PxOsdSubdivTags GetSubdivTags(HdSceneDelegate* delegate)   const;

    /// Topology getter
    virtual HdMeshTopologySharedPtr  GetTopology() const;

    ///
    /// Primvars Accessors
    ///
    inline VtValue GetPoints(HdSceneDelegate* delegate)  const;
    inline VtValue GetNormals(HdSceneDelegate* delegate) const;

    HD_API
    TfTokenVector const & GetBuiltinPrimvarNames() const override;

    /// Configure the geometric style of the mesh for a given representation.
    /// We currently allow up to 2 descriptors for a representation.
    /// Example of when this may be useful:
    ///     Drawing the outline in addition to the surface for a mesh.
    HD_API
    static void ConfigureRepr(TfToken const &reprName,
                              HdMeshReprDesc desc1,
                              HdMeshReprDesc desc2=HdMeshReprDesc());

protected:
    /// Constructor. instancerId, if specified, is the instancer which uses
    /// this mesh as a prototype.
    HD_API
    HdMesh(SdfPath const& id);

    // We allow up to 2 repr descs per repr for meshes (see ConfigureRepr above)
    typedef _ReprDescConfigs<HdMeshReprDesc, 2> _MeshReprConfig;

    HD_API
    static _MeshReprConfig::DescArray _GetReprDesc(TfToken const &reprName);

private:

    // Class can not be default constructed or copied.
    HdMesh()                           = delete;
    HdMesh(const HdMesh &)             = delete;
    HdMesh &operator =(const HdMesh &) = delete;

    static _MeshReprConfig _reprDescConfig;
};

inline bool
HdMesh::IsDoubleSided(HdSceneDelegate* delegate) const
{
    return delegate->GetDoubleSided(GetId());
}

inline HdCullStyle
HdMesh::GetCullStyle(HdSceneDelegate* delegate) const
{
    return delegate->GetCullStyle(GetId());
}

inline VtValue
HdMesh::GetShadingStyle(HdSceneDelegate* delegate) const
{
    return delegate->GetShadingStyle(GetId());
}

inline HdMeshTopology
HdMesh::GetMeshTopology(HdSceneDelegate* delegate) const
{
    return delegate->GetMeshTopology(GetId());
}

inline HdDisplayStyle
HdMesh::GetDisplayStyle(HdSceneDelegate* delegate) const
{
    return delegate->GetDisplayStyle(GetId());
}

inline PxOsdSubdivTags
HdMesh::GetSubdivTags(HdSceneDelegate* delegate) const
{
    return delegate->GetSubdivTags(GetId());
}

inline HdMeshTopologySharedPtr
HdMesh::GetTopology() const
{
    return HdMeshTopologySharedPtr();
}

inline VtValue
HdMesh::GetPoints(HdSceneDelegate* delegate) const
{
    return GetPrimvar(delegate, HdTokens->points);
}

inline VtValue
HdMesh::GetNormals(HdSceneDelegate* delegate) const
{
    return GetPrimvar(delegate, HdTokens->normals);
}


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HD_MESH_H
