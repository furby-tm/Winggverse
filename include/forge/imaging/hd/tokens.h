#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/tokens.h"
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
#ifndef FORGE_IMAGING_HD_TOKENS_H
#define FORGE_IMAGING_HD_TOKENS_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/base/tf/staticTokens.h"

FORGE_NAMESPACE_BEGIN

#define HD_TOKENS                               \
    (accelerations)                             \
    (adjacency)                                 \
    (bboxLocalMin)                              \
    (bboxLocalMax)                              \
    (bbox)                                      \
    (bezier)                                    \
    (bSpline)                                   \
    (camera)                                    \
    (catmullRom)                                \
    (collection)                                \
    (computeShader)                             \
    (coordSysBindings)                          \
    (cubic)                                     \
    (cullStyle)                                 \
    (doubleSided)                               \
    (dispatchCount)                             \
    (displayColor)                              \
    (displayOpacity)                            \
    (displayStyle)                              \
    (drawDispatch)                              \
    (drawingShader)                             \
    (drawingCoord0)                             \
    (drawingCoord1)                             \
    (drawingCoord2)                             \
    (drawingCoordI)                             \
    (drivers)                                   \
    (edgeIndices)                               \
    (elementCount)                              \
    (elementsVisibility)                        \
    (extent)                                    \
    (faceColors)                                \
    (filters)                                   \
    (full)                                      \
    (geometry)                                  \
    (hermite)                                   \
    (hullIndices)                               \
    (indices)                                   \
    (isFlipped)                                 \
    (itemsDrawn)                                \
    (layout)                                    \
    (leftHanded)                                \
    (linear)                                    \
    (lightLink)                                 \
    (lightFilterLink)                           \
    (materialParams)                            \
    (nonperiodic)                               \
    (normals)                                   \
    (params)                                    \
    (patchParam)                                \
    (periodic)                                  \
    (pinned)                                    \
    (points)                                    \
    (pointsIndices)                             \
    (power)                                     \
    (preview)                                   \
    (pointsVisibility)                          \
    (primvar)                                   \
    (primID)                                    \
    (primitiveParam)                            \
    (quadInfo)                                  \
    (renderTags)                                \
    (rightHanded)                               \
    (segmented)                                 \
    (shadowLink)                                \
    (subdivTags)                                \
    (taskState)                                 \
    (taskParams)                                \
    (topology)                                  \
    (topologyVisibility)                        \
    (totalItemCount)                            \
    (transform)                                 \
    (transformInverse)                          \
    (velocities)                                \
    (visibility)                                \
    (widths)

#define HD_INSTANCER_TOKENS                     \
    (culledInstanceIndices)                     \
    (instancer)                                 \
    (instancerTransform)                        \
    (instancerTransformInverse)                 \
    (instanceIndices)                           \
    (instanceIndexBase)                         \
    (instanceTransform)                         \
    (rotate)                                    \
    (scale)                                     \
    (translate)

#define HD_REPR_TOKENS                          \
    (disabled)                                  \
    (hull)                                      \
    (points)                                    \
    (smoothHull)                                \
    (refined)                                   \
    (refinedWire)                               \
    (refinedWireOnSurf)                         \
    (wire)                                      \
    (wireOnSurf)

#define HD_PERF_TOKENS                          \
    (adjacencyBufSize)                          \
    (basisCurvesTopology)                       \
    (bufferSourcesResolved)                     \
    (bufferArrayRangeMigrated)                    \
    (bufferArrayRangeContainerResized)          \
    (collectionsRefreshed)                      \
    (computationsCommited)                      \
    (drawBatches)                               \
    (drawCalls)                                 \
    (dirtyLists)                                \
    (dirtyListsRebuilt)                         \
    (garbageCollected)                          \
    (garbageCollectedSsbo)                      \
    (garbageCollectedUbo)                       \
    (garbageCollectedVbo)                       \
    (gpuMemoryUsed)                             \
    (instBasisCurvesTopology)                   \
    (instBasisCurvesTopologyRange)              \
    (instExtComputationDataRange)               \
    (instMeshTopology)                          \
    (instMeshTopologyRange)                     \
    (instPrimvarRange)                          \
    (instVertexAdjacency)                       \
    (meshTopology)                              \
    (nonUniformSize)                            \
    (numCompletedSamples)                       \
    (quadrangulateCPU)                          \
    (quadrangulateGPU)                          \
    (quadrangulateFaceVarying)                  \
    (quadrangulatedVerts)                       \
    (rebuildBatches)                            \
    (singleBufferSize)                          \
    (ssboSize)                                  \
    (skipInvisibleRprimSync)                    \
    (subdivisionRefineCPU)                      \
    (subdivisionRefineGPU)                      \
    (textureMemory)                             \
    (triangulateFaceVarying)                    \
    (uboSize)                                   \
    (vboRelocated)

#define HD_SHADER_TOKENS                        \
    (alphaThreshold)                            \
    (clipPlanes)                                \
    (commonShaderSource)                        \
    (computeShader)                             \
    (cullStyle)                                 \
    (drawRange)                                 \
    (environmentMap)                            \
    (fragmentShader)                            \
    (geometryShader)                            \
    (indicatorColor)                            \
    (lightingBlendAmount)                       \
    (overrideColor)                             \
    (maskColor)                                 \
    (projectionMatrix)                          \
    (pointColor)                                \
    (pointSize)                                 \
    (pointSelectedSize)                         \
    (materialTag)                               \
    (tessControlShader)                         \
    (tessEvalShader)                            \
    (tessLevel)                                 \
    (viewport)                                  \
    (vertexShader)                              \
    (wireframeColor)                            \
    (worldToViewMatrix)                         \
    (worldToViewInverseMatrix)

// Deprecated. Use: HdPhMaterialTagTokens
#define HD_MATERIALTAG_TOKENS                   \
    (defaultMaterialTag)

/* Terminal keys used in material networks.
 */
#define HD_MATERIAL_TERMINAL_TOKENS             \
    (surface)                                   \
    (displacement)                              \
    (volume)                                    \
    (light)                                     \
    (lightFilter)

#define HD_RENDERTAG_TOKENS                     \
    (geometry)                                  \
    (guide)                                     \
    (hidden)                                    \
    (proxy)                                     \
    (render)

#define HD_OPTION_TOKENS                        \
    (parallelRprimSync)

#define HD_PRIMTYPE_TOKENS                      \
    /* Rprims */                                \
    (mesh)                                      \
    (basisCurves)                               \
    (points)                                    \
    (volume)                                    \
                                                \
    /* Sprims */                                \
    (camera)                                    \
    (drawTarget)                                \
    (material)                                  \
    (coordSys)                                  \
    /* Sprims Lights */                         \
    (simpleLight)                               \
    (cylinderLight)                             \
    (diskLight)                                 \
    (distantLight)                              \
    (domeLight)                                 \
    (light)                                     \
    (lightFilter)                               \
    (pluginLight)                               \
    (rectLight)                                 \
    (sphereLight)                               \
    /* Sprims ExtComputations */                \
    (extComputation)                            \
                                                \
    /* Bprims */                                \
    (renderBuffer)

#define HD_PRIMVAR_ROLE_TOKENS                  \
    ((none, ""))                                \
    (color)                                     \
    (vector)                                    \
    (normal)                                    \
    (point)                                     \
    (textureCoordinate)

/* Schema for "Alternate Output Values" rendering,
 * describing which values a renderpass should
 * compute and write at render time.
 */
#define HD_AOV_TOKENS                           \
    /* Standard rendering outputs */            \
                                                \
    /* HdAovTokens->color represents the final
     * fragment RGBA color. For correct compositing
     * using Hydra, it should have pre-multiplied alpha.
     */                                         \
    (color)                                     \
    /* HdAovTokens->depth represents the clip-space
     * depth of the final fragment.
     */                                         \
    (depth)                                     \
    /* HdAovTokens->cameraDepth represents the camera-space
     * depth of the final fragment.
     */                                         \
    (cameraDepth)                               \
    /* ID rendering - these tokens represent the
     * prim, instance, and subprim ids of the final
     * fragment.
     */                                         \
    (primId)                                    \
    (instanceId)                                \
    (elementId)                                 \
    (edgeId)                                    \
    (pointId)                                   \
    /* Geometric data */                        \
    (Peye)                                      \
    (Neye)                                      \
    (patchCoord)                                \
    (primitiveParam)                            \
    (normal)                                    \
    /* Others we might want to add:
     * https://rmanwiki.pixar.com/display/REN/Arbitrary+Output+Variables
     * - curvature
     * - tangent
     * - velocity
     */                                         \
    /* Primvars:
     *   The tokens don't try to enumerate primvars,
     *   but instead provide an identifying namespace.
     *   The "color" primvar is addressable as "primvars:color".
     */                                         \
    ((primvars, "primvars:"))                   \
    /* Light path expressions:
     *   Applicable only to raytracers, these tell
     *   the renderer to output specific shading
     *   components for specific classes of lightpath.
     *
     *   Lightpath syntax is defined here:
     *   https://rmanwiki.pixar.com/display/REN/Light+Path+Expressions
     *   ... so for example, you could specify
     *   "lpe:CD[<L.>O]"
     */                                         \
    ((lpe, "lpe:"))                             \
    /* Shader signals:
     *   This tells the renderer to output a partial shading signal,
     *   whether from the BXDF (e.g. bxdf.diffuse) or from an intermediate
     *   shading node (e.g. fractal.rgb).
     *   XXX: The exact format is TBD.
     */                                         \
    ((shader, "shader:"))

HD_API
TfToken HdAovTokensMakePrimvar(TfToken const& primvar);

HD_API
TfToken HdAovTokensMakeLpe(TfToken const& lpe);

HD_API
TfToken HdAovTokensMakeShader(TfToken const& shader);

/* Schema for application-configurable render settings. */
#define HD_RENDER_SETTINGS_TOKENS                     \
    /* General graphical options */                   \
    (enableShadows)                                   \
    (enableSceneMaterials)                            \
    (enableSceneLights)                               \
    /* Raytracer sampling settings */                 \
    (convergedVariance)                               \
    (convergedSamplesPerPixel)                        \
    /* thread limit settings */                       \
    (threadLimit)

#define HD_RESOURCE_TYPE_TOKENS                       \
    (texture)                                         \
    (shaderFile)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdTokens, HD_API, HD_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(HdInstancerTokens, HD_API, HD_INSTANCER_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(HdReprTokens, HD_API, HD_REPR_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(HdPerfTokens, HD_API, HD_PERF_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(HdShaderTokens, HD_API, HD_SHADER_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(HdMaterialTagTokens, HD_API, HD_MATERIALTAG_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(HdMaterialTerminalTokens, HD_API, HD_MATERIAL_TERMINAL_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(HdRenderTagTokens, HD_API, HD_RENDERTAG_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(HdOptionTokens, HD_API, HD_OPTION_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(HdPrimTypeTokens, HD_API, HD_PRIMTYPE_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(HdPrimvarRoleTokens, HD_API, HD_PRIMVAR_ROLE_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(HdAovTokens, HD_API, HD_AOV_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(HdRenderSettingsTokens, HD_API, HD_RENDER_SETTINGS_TOKENS);
TF_DECLARE_PUBLIC_TOKENS(HdResourceTypeTokens, HD_API, HD_RESOURCE_TYPE_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HD_TOKENS_H
