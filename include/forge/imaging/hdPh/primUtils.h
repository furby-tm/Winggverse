#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/primUtils.h"
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
#ifndef FORGE_IMAGING_HD_PH_PRIM_UTILS_H
#define FORGE_IMAGING_HD_PH_PRIM_UTILS_H

#include "forge/forge.h"
#include "forge/imaging/hd/sceneDelegate.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/resourceRegistry.h"

#include <memory>
#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

class HdChangeTracker;
class HdDrawItem;
class HdRenderIndex;
class HdRenderParam;
class HdRprim;
struct HdRprimSharedData;
class HdPhDrawItem;
class HdPhInstancer;

using HdBufferArrayRangeSharedPtr = std::shared_ptr<class HdBufferArrayRange>;

using HdBufferSourceSharedPtrVector = std::vector<HdBufferSourceSharedPtr>;
using HdBufferSpecVector = std::vector<struct HdBufferSpec>;
using HdPhShaderCodeSharedPtr = std::shared_ptr<class HdPhShaderCode>;

using HdComputationSharedPtr = std::shared_ptr<class HdComputation>;

using HdPhResourceRegistrySharedPtr = std::shared_ptr<HdPhResourceRegistry>;

// -----------------------------------------------------------------------------
// Draw invalidation and garbage collection utilities
// -----------------------------------------------------------------------------
HDPH_API
void HdPhMarkDrawBatchesDirty(HdRenderParam *renderParam);

HDPH_API
void HdPhMarkMaterialTagsDirty(HdRenderParam *renderParam);

HDPH_API
void HdPhMarkGarbageCollectionNeeded(HdRenderParam *renderParam);

// -----------------------------------------------------------------------------
// Primvar descriptor filtering utilities
// -----------------------------------------------------------------------------
// Get filtered primvar descriptors for drawItem
HDPH_API
HdPrimvarDescriptorVector HdPhGetPrimvarDescriptors(HdRprim const *prim,
                                                    HdPhDrawItem const *drawItem,
                                                    HdSceneDelegate *delegate,
                                                    HdInterpolation interpolation);

// Get filtered instancer primvar descriptors for drawItem
HDPH_API
HdPrimvarDescriptorVector HdPhGetInstancerPrimvarDescriptors(HdPhInstancer const *instancer,
                                                             HdSceneDelegate *delegate);

// -----------------------------------------------------------------------------
// Material processing utilities
// -----------------------------------------------------------------------------
HDPH_API
void HdPhSetMaterialId(HdSceneDelegate *delegate, HdRenderParam *renderParam, HdRprim *rprim);

HDPH_API
void HdPhSetMaterialTag(HdSceneDelegate *delegate,
                        HdRenderParam *renderParam,
                        HdRprim *rprim,
                        bool hasDisplayOpacityPrimvar,
                        bool occludedSelectionShowsThrough);
// Resolves the material shader for the given prim (using a fallback
// material as necessary), including optional mixin shader source code.
HDPH_API
HdPhShaderCodeSharedPtr HdPhGetMaterialShader(HdRprim const *prim,
                                              HdSceneDelegate *delegate,
                                              std::string const &mixinSource = std::string());

// -----------------------------------------------------------------------------
// Primvar processing and BAR allocation utilities
// -----------------------------------------------------------------------------
// Returns true if range is non-empty and valid.
HDPH_API
bool HdPhIsValidBAR(HdBufferArrayRangeSharedPtr const &range);

// Returns true if curRange can be used as-is (even if it's empty) during
// primvar processing.
HDPH_API
bool HdPhCanSkipBARAllocationOrUpdate(HdBufferSourceSharedPtrVector const &sources,
                                      HdPhComputationSharedPtrVector const &computations,
                                      HdBufferArrayRangeSharedPtr const &curRange,
                                      HdDirtyBits dirtyBits);

HDPH_API
bool HdPhCanSkipBARAllocationOrUpdate(HdBufferSourceSharedPtrVector const &sources,
                                      HdBufferArrayRangeSharedPtr const &curRange,
                                      HdDirtyBits dirtyBits);

// Returns the buffer specs that have been removed from curRange based on the
// new primvar descriptors and internally generated primvar names.
//
// Internally generated primvar names will never be among the specs returned,
HDPH_API
HdBufferSpecVector HdPhGetRemovedPrimvarBufferSpecs(
    HdBufferArrayRangeSharedPtr const &curRange,
    HdPrimvarDescriptorVector const &newPrimvarDescs,
    HdExtComputationPrimvarDescriptorVector const &newCompPrimvarDescs,
    TfTokenVector const &internallyGeneratedPrimvarNames,
    SdfPath const &rprimId);

HDPH_API
HdBufferSpecVector HdPhGetRemovedPrimvarBufferSpecs(
    HdBufferArrayRangeSharedPtr const &curRange,
    HdPrimvarDescriptorVector const &newPrimvarDescs,
    TfTokenVector const &internallyGeneratedPrimvarNames,
    SdfPath const &rprimId);

// Updates the existing range at drawCoordIndex with newRange and flags garbage
// collection (for the existing range) and rebuild of all draw batches when
// necessary.
HDPH_API
void HdPhUpdateDrawItemBAR(HdBufferArrayRangeSharedPtr const &newRange,
                           int drawCoordIndex,
                           HdRprimSharedData *sharedData,
                           HdRenderParam *renderParam,
                           HdChangeTracker *changeTracker);

// Returns true if primvar with primvarName exists within primvar descriptor
// vector primvars and primvar has a valid value
HDPH_API
bool HdPhIsPrimvarExistentAndValid(HdRprim *prim,
                                   HdSceneDelegate *delegate,
                                   HdPrimvarDescriptorVector const &primvars,
                                   TfToken const &primvarName);

// -----------------------------------------------------------------------------
// Constant primvar processing utilities
// -----------------------------------------------------------------------------
// Returns whether constant primvars need to be populated/updated based on the
// dirty bits for a given rprim.
HDPH_API
bool HdPhShouldPopulateConstantPrimvars(HdDirtyBits const *dirtyBits, SdfPath const &id);

// Given prim information it will create sources representing
// constant primvars and hand it to the resource registry.
// If transforms are dirty, updates the optional bool.
HDPH_API
void HdPhPopulateConstantPrimvars(HdRprim *prim,
                                  HdRprimSharedData *sharedData,
                                  HdSceneDelegate *delegate,
                                  HdRenderParam *renderParam,
                                  HdDrawItem *drawItem,
                                  HdDirtyBits *dirtyBits,
                                  HdPrimvarDescriptorVector const &constantPrimvars,
                                  bool *hasMirroredTransform = nullptr);

// -----------------------------------------------------------------------------
// Instancer processing utilities
// -----------------------------------------------------------------------------

// Updates drawItem bindings for changes to instance topology/primvars.
HDPH_API
void HdPhUpdateInstancerData(HdRenderIndex &renderIndex,
                             HdRenderParam *renderParam,
                             HdRprim *prim,
                             HdPhDrawItem *drawItem,
                             HdRprimSharedData *sharedData,
                             HdDirtyBits rprimDirtyBits);

// Returns true if primvar with primvarName exists among instance primvar
// descriptors.
HDPH_API
bool HdPhIsInstancePrimvarExistentAndValid(HdRenderIndex &renderIndex,
                                           HdRprim *prim,
                                           TfToken const &primvarName);

// -----------------------------------------------------------------------------
// Topological visibility processing utility
// -----------------------------------------------------------------------------
// Creates/Updates/Migrates the topology visiblity BAR with element and point
// visibility encoded using one bit per element/point of the topology.
HDPH_API
void HdPhProcessTopologyVisibility(VtIntArray invisibleElements,
                                   int numTotalElements,
                                   VtIntArray invisiblePoints,
                                   int numTotalPoints,
                                   HdRprimSharedData *sharedData,
                                   HdPhDrawItem *drawItem,
                                   HdRenderParam *renderParam,
                                   HdChangeTracker *changeTracker,
                                   HdPhResourceRegistrySharedPtr const &resourceRegistry,
                                   SdfPath const &rprimId);

//
// De-duplicating and sharing immutable primvar data.
//
// Primvar data is identified using a hash computed from the
// sources of the primvar data, of which there are generally
// two kinds:
//   - data provided by the scene delegate
//   - data produced by computations
//
// Immutable and mutable buffer data is managed using distinct
// heaps in the resource registry. Aggregation of buffer array
// ranges within each heap is managed separately.
//
// We attempt to balance the benefits of sharing vs efficient
// varying update using the following simple strategy:
//
//  - When populating the first repr for an rprim, allocate
//    the primvar range from the immutable heap and attempt
//    to deduplicate the data by looking up the primvarId
//    in the primvar instance registry.
//
//  - When populating an additional repr for an rprim using
//    an existing immutable primvar range, compute an updated
//    primvarId and allocate from the immutable heap, again
//    attempting to deduplicate.
//
//  - Otherwise, migrate the primvar data to the mutable heap
//    and abandon further attempts to deduplicate.
//
//  - The computation of the primvarId for an rprim is cumulative
//    and includes the new sources of data being committed
//    during each successive update.
//
//  - Once we have migrated a primvar allocation to the mutable
//    heap we will no longer spend time computing a primvarId.
//

HDPH_API
bool HdPhIsEnabledSharedVertexPrimvar();

HDPH_API
uint64_t HdPhComputeSharedPrimvarId(uint64_t baseId,
                                    HdBufferSourceSharedPtrVector const &sources,
                                    HdPhComputationSharedPtrVector const &computations);

HDPH_API
void HdPhGetBufferSpecsFromCompuations(HdPhComputationSharedPtrVector const &computations,
                                       HdBufferSpecVector *bufferSpecs);

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_PRIM_UTILS_H
