#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/usdaFileFormat.h"
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
#ifndef FORGE_USD_USD_USDA_FILE_FORMAT_H
#define FORGE_USD_USD_USDA_FILE_FORMAT_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/sdf/textFileFormat.h"
#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/staticTokens.h"

FORGE_NAMESPACE_BEGIN


#define USD_USDA_FILE_FORMAT_TOKENS \
    ((Id,      "usda"))             \
    ((Version, "1.0"))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(UsdUsdaFileFormatTokens, USD_API, USD_USDA_FILE_FORMAT_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

TF_DECLARE_WEAK_AND_REF_PTRS(UsdUsdaFileFormat);

/// \class UsdUsdaFileFormat
///
/// File format used by textual USD files.
///
class UsdUsdaFileFormat : public SdfTextFileFormat
{
private:
    SDF_FILE_FORMAT_FACTORY_ACCESS;

    UsdUsdaFileFormat();

    virtual ~UsdUsdaFileFormat();
};


FORGE_NAMESPACE_END

#endif // USDA_FILE_FORMAT_H
