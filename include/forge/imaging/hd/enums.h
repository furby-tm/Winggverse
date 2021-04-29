#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/enums.h"
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
#ifndef FORGE_IMAGING_HD_ENUMS_H
#define FORGE_IMAGING_HD_ENUMS_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"

FORGE_NAMESPACE_BEGIN

/// \enum HdCompareFunction
///
/// Abstraction of the Graphics compare functions.
///
enum HdCompareFunction
{
    HdCmpFuncNever,
    HdCmpFuncLess,
    HdCmpFuncEqual,
    HdCmpFuncLEqual,
    HdCmpFuncGreater,
    HdCmpFuncNotEqual,
    HdCmpFuncGEqual,
    HdCmpFuncAlways,

    HdCmpFuncLast
};

/// \enum HdStencilOp
///
/// Abstraction of the Graphics stencil test operations.
///
enum HdStencilOp
{
    HdStencilOpKeep,
    HdStencilOpZero,
    HdStencilOpReplace,
    HdStencilOpIncrement,
    HdStencilOpIncrementWrap,
    HdStencilOpDecrement,
    HdStencilOpDecrementWrap,
    HdStencilOpInvert,

    HdStencilOpLast
};

/// \enum HdBlendOp
///
/// Abstraction of the Graphics blend operations.
///
enum HdBlendOp
{
    HdBlendOpAdd,
    HdBlendOpSubtract,
    HdBlendOpReverseSubtract,
    HdBlendOpMin,
    HdBlendOpMax,

    HdBlendOpLast
};

/// \enum HdBlendFactor
///
/// Abstraction of the Graphics blend factors.
///
enum HdBlendFactor
{
    HdBlendFactorZero,
    HdBlendFactorOne,
    HdBlendFactorSrcColor,
    HdBlendFactorOneMinusSrcColor,
    HdBlendFactorDstColor,
    HdBlendFactorOneMinusDstColor,
    HdBlendFactorSrcAlpha,
    HdBlendFactorOneMinusSrcAlpha,
    HdBlendFactorDstAlpha,
    HdBlendFactorOneMinusDstAlpha,
    HdBlendFactorConstantColor,
    HdBlendFactorOneMinusConstantColor,
    HdBlendFactorConstantAlpha,
    HdBlendFactorOneMinusConstantAlpha,
    HdBlendFactorSrcAlphaSaturate,
    HdBlendFactorSrc1Color,
    HdBlendFactorOneMinusSrc1Color,
    HdBlendFactorSrc1Alpha,
    HdBlendFactorOneMinusSrc1Alpha,

    HdBlendFactorLast
};

/// \enum HdCullStyle
///
/// Face culling options.
///
/// DontCare indicates this prim doesn't determine what should be culled.
/// Any other CullStyle opinion will override this (such as from the viewer).
///
/// BackUnlessDoubleSided and FrontUnlessDoubleSided will only cull back or
/// front faces if prim isn't marked as doubleSided.
///
enum HdCullStyle
{
    HdCullStyleDontCare,
    HdCullStyleNothing,
    HdCullStyleBack,
    HdCullStyleFront,
    HdCullStyleBackUnlessDoubleSided,
    HdCullStyleFrontUnlessDoubleSided
};

/// Returns the opposite of the given cullstyle; backface culling becomes
/// frontface and vice versa.
HD_API
HdCullStyle HdInvertCullStyle(HdCullStyle cs);

enum HdPolygonMode
{
    HdPolygonModeFill,
    HdPolygonModeLine
};

/// \enum HdMeshGeomStyle
///
/// Hydra native geom styles.
///
enum HdMeshGeomStyle {
    HdMeshGeomStyleInvalid,
    HdMeshGeomStyleSurf,
    HdMeshGeomStyleEdgeOnly,
    HdMeshGeomStyleEdgeOnSurf,
    HdMeshGeomStyleHull,
    HdMeshGeomStyleHullEdgeOnly,
    HdMeshGeomStyleHullEdgeOnSurf,
    HdMeshGeomStylePoints
};

enum HdBasisCurvesGeomStyle {
    HdBasisCurvesGeomStyleInvalid,
    HdBasisCurvesGeomStyleWire,
    HdBasisCurvesGeomStylePatch,
    HdBasisCurvesGeomStylePoints
};

enum HdPointsGeomStyle {
    HdPointsGeomStyleInvalid,
    HdPointsGeomStylePoints
};

///
/// \enum HdInterpolation
///
/// Enumerates Hydra's primvar interpolation modes.
///
/// Constant:    One value remains constant over the entire surface primitive.
///
/// Uniform:     One value remains constant for each uv patch segment of the
///              surface primitive.
///
/// Varying:     Four values are interpolated over each uv patch segment of
///              the surface. Bilinear interpolation is used for interpolation
///              between the four values.
///
/// Vertex:      Values are interpolated between each vertex in the surface
///              primitive. The basis function of the surface is used for
///              interpolation between vertices.
///
/// Facevarying: For polygons and subdivision surfaces, four values are
///              interpolated over each face of the mesh. Bilinear interpolation
///              is used for interpolation between the four values.
///
/// Instance:    One value remains constant across each instance.
///
enum HdInterpolation
{
    HdInterpolationConstant = 0,
    HdInterpolationUniform,
    HdInterpolationVarying,
    HdInterpolationVertex,
    HdInterpolationFaceVarying,
    HdInterpolationInstance,

    HdInterpolationCount
};

///
/// \enum HdTextureType
/// Enumerates Hydra's supported texture types.
///
/// Uv:    Sample the uv coordinates and accesses a single 2d texture.
///
/// Field: Transform coordinates by matrix before accessing a single 3d
///        texture.
///
/// Ptex:  Use the ptex connectivity information to sample a ptex texture.
///
/// Udim:  Remap the uv coordinates into udim coordinates using a maximum
///        tile width of 10 and sample all the udim tiles found in the
///        file system.
///
enum class HdTextureType
{
    Uv,
    Field,
    Ptex,
    Udim
};

/// \enum HdDepthPriority
/// Sets the priorities for a depth based operation
///
/// <ul>
///     <li>HdDepthPriorityNearest     Prioritize objects nearest to the camera</li>
///     <li>HdDepthPriorityFarthest    Prioritize objects farthest from the camera</li>
/// </ul>
///
enum HdDepthPriority
{
    HdDepthPriorityNearest = 0,
    HdDepthPriorityFarthest,

    HdDepthPriorityCount
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_ENUMS_H
