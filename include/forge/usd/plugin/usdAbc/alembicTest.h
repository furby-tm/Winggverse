#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/plugin/usdAbc/alembicTest.h"
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
#ifndef FORGE_USD_PLUGIN_USD_ABC_ALEMBIC_TEST_H
#define FORGE_USD_PLUGIN_USD_ABC_ALEMBIC_TEST_H

#include "forge/forge.h"
#include "forge/usd/plugin/usdAbc/api.h"
#include <string>

FORGE_NAMESPACE_BEGIN


/// Test Alembic conversion.
USDABC_API
bool UsdAbc_TestAlembic(const std::string& pathname);

/// Read Usd file from \p srcPathname and write as Alembic to \p dstPathname.
USDABC_API
bool UsdAbc_WriteAlembic(const std::string& srcPathname,
                         const std::string& dstPathname);


FORGE_NAMESPACE_END

#endif // FORGE_USD_PLUGIN_USD_ABC_ALEMBIC_TEST_H
