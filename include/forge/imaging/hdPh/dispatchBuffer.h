#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/dispatchBuffer.h"
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
#ifndef FORGE_IMAGING_HD_PH_DISPATCH_BUFFER_H
#define FORGE_IMAGING_HD_PH_DISPATCH_BUFFER_H

#include "forge/forge.h"
#include "forge/imaging/hd/bufferArray.h"
#include "forge/imaging/hd/bufferSpec.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/bufferArrayRange.h"
#include "forge/imaging/hdPh/bufferResource.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdPhResourceRegistry;

using HdPhDispatchBufferSharedPtr = std::shared_ptr<class HdPhDispatchBuffer>;

/// \class HdPhDispatchBuffer
///
/// A VBO of a simple array of unsigned integers.
///
/// This buffer is used to prepare data on the GPU for indirect dispatch i.e.
/// to be consumed by MultiDrawIndirect or DispatchComputeIndirect. At the
/// same time, interleaved subsets of the array are bound in several different
/// ways to provide additional data interface to shaders.
///
/// For each binding, we define 'BufferResourceView' on top of the uint array.
/// HdBufferArray aggregates those views and HdResourceBinder binds them
/// with specified binding method and interleaved offset.
///
/// Example:
///    DrawElements + Instance culling : 14 integers for each drawitem
///
///                              BufferResourceViews    BufferResourceViews
///                                 for draw               for cull
///
/// +----draw item 0----+----------------------------> destination buffer
/// | count             | --+
/// | instanceCount     |   |
/// | first             |   |----> MDI dispatch
/// | baseVertex        |   |
/// | baseInstance      | --+-------------------------> drawitem index
/// | cullCount         | ----+
/// | cullInstanceCount |     |------------------------> MDI dispatch
/// | cullFirstVertex   |     |
/// | cullBaseInstance  | ----+
/// | modelDC           | --+
/// | constantDC        |   |----> DrawingCoord0 -------> DrawingCoord0
/// | elementDC         |   |
/// | primitiveDC       | --+
/// | fvarDC            | --+
/// | instanceIndexDC   |   |----> DrawingCoord1 -------> DrawingCoord1
/// | shaderDC          | --+
/// | (instanceDC[0])   | --+
/// | (instanceDC[1])   |   |----> DrawingCoordI -------> DrawingCoordI
/// | (instanceDC[2])   |   |
/// | ...               | --+
/// +----draw item 1----+
/// | count             |
/// | instanceCount     |
/// | ...               |
///
/// XXX: it would be better to generalize this class not only for dispatch
/// buffer, if we see other similar use-cases.
///
class HdPhDispatchBuffer : public HdBufferArray {
 public:
  /// Constructor. commandNumUints is given in how many integers.
  HDPH_API
  HdPhDispatchBuffer(HdPhResourceRegistry *resourceRegistry,
                     TfToken const &role,
                     int count,
                     unsigned int commandNumUints);

  /// Destructor.
  HDPH_API
  ~HdPhDispatchBuffer() override;

  /// Update entire buffer data
  HDPH_API
  void CopyData(std::vector<uint32_t> const &data);

  /// Add an interleaved view to this buffer.
  HDPH_API
  void AddBufferResourceView(TfToken const &name, HdTupleType tupleType, int offset);

  /// Returns the dispatch count
  int GetCount() const
  {
    return _count;
  }

  /// Returns the number of uints in a single draw command.
  unsigned int GetCommandNumUints() const
  {
    return _commandNumUints;
  }

  /// Returns a bar which locates all interleaved resources of the entire
  /// buffer.
  HdPhBufferArrayRangeSharedPtr GetBufferArrayRange() const
  {
    return _bar;
  }

  /// Returns entire buffer as a single HdBufferResource.
  HdPhBufferResourceSharedPtr GetEntireResource() const
  {
    return _entireResource;
  }

  // HdBufferArray overrides. they are not supported in this class.
  HDPH_API
  bool GarbageCollect() override;
  HDPH_API
  void Reallocate(std::vector<HdBufferArrayRangeSharedPtr> const &,
                  HdBufferArraySharedPtr const &) override;

  HDPH_API
  void DebugDump(std::ostream &out) const override;

  /// Returns the GPU resource. If the buffer array contains more than one
  /// resource, this method raises a coding error.
  HDPH_API
  HdPhBufferResourceSharedPtr GetResource() const;

  /// Returns the named GPU resource. This method returns the first found
  /// resource. In HDPH_SAFE_MODE it checks all underlying GPU buffers
  /// in _resourceMap and raises a coding error if there are more than
  /// one GPU buffers exist.
  HDPH_API
  HdPhBufferResourceSharedPtr GetResource(TfToken const &name);

  /// Returns the list of all named GPU resources for this bufferArray.
  HdPhBufferResourceNamedList const &GetResources() const
  {
    return _resourceList;
  }

 protected:
  /// Adds a new, named GPU resource and returns it.
  HDPH_API
  HdPhBufferResourceSharedPtr _AddResource(TfToken const &name,
                                           HdTupleType tupleType,
                                           int offset,
                                           int stride);

 private:
  HdPhResourceRegistry *_resourceRegistry;
  int _count;
  unsigned int _commandNumUints;
  HdPhBufferResourceNamedList _resourceList;
  HdPhBufferResourceSharedPtr _entireResource;
  HdPhBufferArrayRangeSharedPtr _bar;  // Alternative to range list in base class
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_DISPATCH_BUFFER_H
