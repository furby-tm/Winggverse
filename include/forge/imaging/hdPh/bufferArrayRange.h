#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/bufferArrayRange.h"
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
#ifndef FORGE_IMAGING_HD_PH_BUFFER_ARRAY_RANGE_H
#define FORGE_IMAGING_HD_PH_BUFFER_ARRAY_RANGE_H

#include "forge/base/tf/token.h"
#include "forge/forge.h"
#include "forge/imaging/hd/bufferArrayRange.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdBufferArrayGL;
class HdPhResourceRegistry;

using HdPhBufferArrayRangeSharedPtr = std::shared_ptr<class HdPhBufferArrayRange>;

class HdPhBufferResource;

using HdPhBufferResourceSharedPtr = std::shared_ptr<class HdPhBufferResource>;
using HdPhBufferResourceNamedList = std::vector<std::pair<TfToken, HdPhBufferResourceSharedPtr>>;

/// \class HdPhBufferArrayRange
///
/// Interface class for representing range (subset) locator of HdBufferArray.
///
/// Each memory management strategy defines a specialized range class which is
/// inherited of this interface so that client (drawItem) can be agnostic about
/// the implementation detail of aggregation.
///
class HdPhBufferArrayRange : public HdBufferArrayRange {
 public:
  HdPhBufferArrayRange(HdPhResourceRegistry *resourceRegistry);

  /// Destructor (do nothing).
  /// The specialized range class may want to do something for garbage
  /// collection in its destructor. However, be careful not do any
  /// substantial work here (obviously including any kind of GL calls),
  /// since the destructor gets called frequently on various contexts.
  HDPH_API
  virtual ~HdPhBufferArrayRange();

  /// Returns the GPU resource. If the buffer array contains more than one
  /// resource, this method raises a coding error.
  virtual HdPhBufferResourceSharedPtr GetResource() const = 0;

  /// Returns the named GPU resource.
  virtual HdPhBufferResourceSharedPtr GetResource(TfToken const &name) = 0;

  /// Returns the list of all named GPU resources for this bufferArrayRange.
  virtual HdPhBufferResourceNamedList const &GetResources() const = 0;

  /// Sets the bufferSpecs for all resources.
  HDPH_API
  virtual void GetBufferSpecs(HdBufferSpecVector *bufferSpecs) const override;

 protected:
  HdPhResourceRegistry *GetResourceRegistry();

 private:
  HdPhResourceRegistry *_resourceRegistry;
};

HDPH_API
std::ostream &operator<<(std::ostream &out, const HdPhBufferArrayRange &self);

/// \class HdPhBufferArrayRangeContainer
///
/// A resizable container of HdBufferArrayRanges.
///
class HdPhBufferArrayRangeContainer {
 public:
  /// Constructor
  HdPhBufferArrayRangeContainer(int size) : _ranges(size)
  {
  }

  /// Set \p range into the container at \p index.
  /// If the size of container is smaller than index, resize it.
  HDPH_API
  void Set(int index, HdPhBufferArrayRangeSharedPtr const &range);

  /// Returns the bar at \p index. returns null if either the index
  // is out of range or not yet set.
  HDPH_API
  HdPhBufferArrayRangeSharedPtr const &Get(int index) const;

 private:
  std::vector<HdPhBufferArrayRangeSharedPtr> _ranges;
};

FORGE_NAMESPACE_END

#endif  // HD_BUFFER_ARRAY_RANGE_GL_H
