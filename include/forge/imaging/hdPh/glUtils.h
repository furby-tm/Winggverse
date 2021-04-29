#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/glUtils.h"
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
#ifndef FORGE_IMAGING_HD_PH_GL_UTILS_H
#define FORGE_IMAGING_HD_PH_GL_UTILS_H

#include "forge/forge.h"
#include "forge/imaging/hd/types.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hgi/buffer.h"

#include "forge/base/vt/value.h"

FORGE_NAMESPACE_BEGIN

class HdPhGLUtils {
 public:
  /// Reads the content of VBO back to VtArray.
  /// The \p vboOffset is expressed in bytes.
  HDPH_API
  static VtValue ReadBuffer(
      uint64_t vbo, HdTupleType tupleType, int vboOffset, int stride, int numElements);
};

/// \class HdPhBufferRelocator
///
/// A utility class to perform batched buffer copy.
///
class HdPhBufferRelocator {
 public:
  HdPhBufferRelocator(HgiBufferHandle const &srcBuffer, HgiBufferHandle const &dstBuffer)
      : _srcBuffer(srcBuffer), _dstBuffer(dstBuffer)
  {
  }

  /// Schedule the range to be copied. The consecutive ranges could be
  /// aggregated into a single copy where possible.
  HDPH_API
  void AddRange(ptrdiff_t readOffset, ptrdiff_t writeOffset, ptrdiff_t copySize);

  /// Execute Hgi buffer copy command to flush all scheduled range copies.
  HDPH_API
  void Commit(class HgiBlitCmds *blitCmds);

 private:
  struct _CopyUnit {
    _CopyUnit(ptrdiff_t read, ptrdiff_t write, ptrdiff_t size)
        : readOffset(read), writeOffset(write), copySize(size)
    {
    }

    bool Concat(_CopyUnit const &next)
    {
      if (readOffset + copySize == next.readOffset && writeOffset + copySize == next.writeOffset) {
        copySize += next.copySize;
        return true;
      }
      return false;
    }

    ptrdiff_t readOffset;
    ptrdiff_t writeOffset;
    ptrdiff_t copySize;
  };

  std::vector<_CopyUnit> _queue;
  HgiBufferHandle _srcBuffer;
  HgiBufferHandle _dstBuffer;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_GL_UTILS_H
