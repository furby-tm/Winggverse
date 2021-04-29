#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hf/perfLog.h"
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
#ifndef FORGE_IMAGING_HF_PERF_LOG_H
#define FORGE_IMAGING_HF_PERF_LOG_H

#include "forge/forge.h"
#include "forge/base/tf/mallocTag.h"
#include "forge/base/tf/preprocessorUtilsLite.h"

FORGE_NAMESPACE_BEGIN


///
/// Creates an auto-mallocTag with the function, including template params.
///
#define HF_MALLOC_TAG_FUNCTION() \
    TfAutoMallocTag2 tagFunc(TF_PP_STRINGIZE(MFB_PACKAGE_NAME), \
                             __ARCH_PRETTY_FUNCTION__);

///
/// Creates an auto-mallocTag with the given named tag.
///
#define HF_MALLOC_TAG(x) \
    TfAutoMallocTag2 tag2(TF_PP_STRINGIZE(MFB_PACKAGE_NAME), x);

///
/// Overrides operator new/delete and injects malloc tags.
///
#define HF_MALLOC_TAG_NEW(x) \
    TF_MALLOC_TAG_NEW(TF_PP_STRINGIZE(MFB_PACKAGE_NAME), x);


#define HF_TRACE_FUNCTION_SCOPE(tag)                                  \
  TRACE_FUNCTION_SCOPE(tag)

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HF_PERF_LOG_H
