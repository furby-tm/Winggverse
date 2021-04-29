#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ar/resolverContext.h"
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
#ifndef FORGE_USD_AR_RESOLVER_CONTEXT_H
#define FORGE_USD_AR_RESOLVER_CONTEXT_H

/// \file ar/resolverContext.h

#include "forge/forge.h"
#include "forge/usd/ar/ar.h"

#define INCLUDE_AR_RESOLVER_CONTEXT

#if AR_VERSION == 1
#include "forge/usd/ar/resolverContext_v1.h"
#elif AR_VERSION == 2
#include "forge/usd/ar/resolverContext_v2.h"
#else
#error Unhandled AR_VERSION
#endif

#undef INCLUDE_AR_RESOLVER_CONTEXT

#endif // FORGE_USD_AR_RESOLVER_CONTEXT_H
