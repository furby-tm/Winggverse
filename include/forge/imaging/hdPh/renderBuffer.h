#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/renderBuffer.h"
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
#ifndef FORGE_IMAGING_HD_PH_RENDER_BUFFER_H
#define FORGE_IMAGING_HD_PH_RENDER_BUFFER_H

#include "forge/base/gf/vec3i.h"
#include "forge/forge.h"
#include "forge/imaging/hd/renderBuffer.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hgi/enums.h"
#include "forge/imaging/hgi/hgi.h"
#include "forge/imaging/hgi/texture.h"

FORGE_NAMESPACE_BEGIN

class HdPhResourceRegistry;
class HdPhTextureIdentifier;
using HdPhDynamicUvTextureObjectSharedPtr = std::shared_ptr<class HdPhDynamicUvTextureObject>;

class HdPhRenderBuffer : public HdRenderBuffer {
 public:
  HDPH_API
  HdPhRenderBuffer(HdPhResourceRegistry *resourceRegistry, SdfPath const &id);

  HDPH_API
  ~HdPhRenderBuffer() override;

  HDPH_API
  void Sync(HdSceneDelegate *sceneDelegate,
            HdRenderParam *renderParam,
            HdDirtyBits *dirtyBits) override;

  HDPH_API
  bool Allocate(GfVec3i const &dimensions, HdFormat format, bool multiSampled) override;

  HDPH_API
  unsigned int GetWidth() const override;

  HDPH_API
  unsigned int GetHeight() const override;

  HDPH_API
  unsigned int GetDepth() const override;

  HDPH_API
  HdFormat GetFormat() const override
  {
    return _format;
  }

  HDPH_API
  bool IsMultiSampled() const override;

  /// Map the buffer for reading. The control flow should be Map(),
  /// before any I/O, followed by memory access, followed by Unmap() when
  /// done.
  ///   \return The address of the buffer.
  HDPH_API
  void *Map() override;

  /// Unmap the buffer.
  HDPH_API
  void Unmap() override;

  /// Return whether any clients have this buffer mapped currently.
  ///   \return True if the buffer is currently mapped by someone.
  HDPH_API
  bool IsMapped() const override
  {
    return _mappers.load() != 0;
  }

  /// Is the buffer converged?
  ///   \return True if the buffer is converged (not currently being
  ///           rendered to).
  HDPH_API
  bool IsConverged() const override
  {
    return true;
  }

  /// Resolve the sample buffer into final values.
  HDPH_API
  void Resolve() override;

  /// Returns the texture handle.
  HDPH_API
  VtValue GetResource(bool multiSampled) const override;

  /// The identifier that can be passed to, e.g.,
  /// HdPhResourceRegistry::AllocateTextureHandle so that a
  /// shader can bind this buffer as texture.
  HDPH_API
  HdPhTextureIdentifier GetTextureIdentifier(bool multiSampled);

 protected:
  void _Deallocate() override;

 private:
  // HdRenderBuffer::Allocate should take a scene delegate or
  // resource registry so that we do not need to save it here.
  HdPhResourceRegistry *_resourceRegistry;

  // Format saved here (somewhat redundantely) since the
  // Hgi texture descriptor holds an HgiFormat instead of HdFormat.
  HdFormat _format;

  uint32_t _msaaSampleCount;

  // The GPU texture resource
  HdPhDynamicUvTextureObjectSharedPtr _textureObject;

  // The GPU multi-sample texture resource (optional)
  HdPhDynamicUvTextureObjectSharedPtr _textureMSAAObject;

  // The number of callers mapping this buffer.
  std::atomic<int> _mappers;
  // Texels are temp captured into this buffer between map and unmap.
  std::vector<uint8_t> _mappedBuffer;
};

FORGE_NAMESPACE_END

#endif
