#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/api.h"
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

#ifndef FORGE_IMAGING_HD_PH_API_H
#define FORGE_IMAGING_HD_PH_API_H

#include "forge/base/arch/export.h"

#if defined(FORGE_STATIC)
#  define HDPH_API
#  define HDPH_API_TEMPLATE_CLASS(...)
#  define HDPH_API_TEMPLATE_STRUCT(...)
#  define HDPH_LOCAL
#else
#  if defined(HDPH_EXPORTS)
#    define HDPH_API ARCH_EXPORT
#    define HDPH_API_TEMPLATE_CLASS(...) ARCH_EXPORT_TEMPLATE(class, __VA_ARGS__)
#    define HDPH_API_TEMPLATE_STRUCT(...) ARCH_EXPORT_TEMPLATE(struct, __VA_ARGS__)
#  else
#    define HDPH_API ARCH_IMPORT
#    define HDPH_API_TEMPLATE_CLASS(...) ARCH_IMPORT_TEMPLATE(class, __VA_ARGS__)
#    define HDPH_API_TEMPLATE_STRUCT(...) ARCH_IMPORT_TEMPLATE(struct, __VA_ARGS__)
#  endif
#  define HDPH_LOCAL ARCH_HIDDEN
#endif

#endif  // FORGE_IMAGING_HD_PH_API_H
