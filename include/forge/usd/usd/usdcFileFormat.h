#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/usdcFileFormat.h"
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
#ifndef FORGE_USD_USD_USDC_FILE_FORMAT_H
#define FORGE_USD_USD_USDC_FILE_FORMAT_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/sdf/fileFormat.h"
#include "forge/base/tf/staticTokens.h"
#include <string>

FORGE_NAMESPACE_BEGIN

#define USD_USDC_FILE_FORMAT_TOKENS   \
    ((Id,      "usdc"))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(UsdUsdcFileFormatTokens, USD_API, USD_USDC_FILE_FORMAT_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

TF_DECLARE_WEAK_AND_REF_PTRS(UsdUsdcFileFormat);

/// \class UsdUsdcFileFormat
///
/// File format for binary Usd files.
///
class UsdUsdcFileFormat : public SdfFileFormat
{
public:
    using SdfFileFormat::FileFormatArguments;
    using string = std::string;

    virtual SdfAbstractDataRefPtr InitData(
        const FileFormatArguments& args) const override;

    virtual bool CanRead(const string &file) const override;

    virtual bool Read(
        SdfLayer* layer,
        const string& resolvedPath,
        bool metadataOnly) const override;

    virtual bool WriteToFile(
        const SdfLayer& layer,
        const string& filePath,
        const string& comment = string(),
        const FileFormatArguments& args = FileFormatArguments()) const override;

    virtual bool ReadFromString(SdfLayer* layer,
                                const string& str) const override;

    virtual bool WriteToString(const SdfLayer& layer,
                               string* str,
                               const string& comment = string()) const override;

    virtual bool WriteToStream(const SdfSpecHandle &spec,
                               std::ostream& out,
                               size_t indent) const override;

protected:
    SDF_FILE_FORMAT_FACTORY_ACCESS;

    UsdUsdcFileFormat();
    virtual ~UsdUsdcFileFormat();

};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_USDC_FILE_FORMAT_H
