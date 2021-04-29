#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/usdzFileFormat.h"
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
#ifndef FORGE_USD_USD_USDZ_FILE_FORMAT_H
#define FORGE_USD_USD_USDZ_FILE_FORMAT_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/sdf/fileFormat.h"
#include "forge/base/tf/staticTokens.h"

#include <string>

FORGE_NAMESPACE_BEGIN

TF_DECLARE_WEAK_AND_REF_PTRS(UsdUsdzFileFormat);

#define USD_USDZ_FILE_FORMAT_TOKENS  \
    ((Id,      "usdz"))              \
    ((Version, "1.0"))               \
    ((Target,  "usd"))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(UsdUsdzFileFormatTokens, USD_API, USD_USDZ_FILE_FORMAT_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/// \class UsdUsdzFileFormat
///
/// File format for package .usdz files.
class UsdUsdzFileFormat : public SdfFileFormat
{
public:
    using SdfFileFormat::FileFormatArguments;

    USD_API
    virtual bool IsPackage() const override;

    USD_API
    virtual std::string GetPackageRootLayerPath(
        const std::string& resolvedPath) const override;

    USD_API
    virtual SdfAbstractDataRefPtr
    InitData(const FileFormatArguments& args) const override;

    USD_API
    virtual bool CanRead(const std::string &file) const override;

    USD_API
    virtual bool Read(
        SdfLayer* layer,
        const std::string& resolvedPath,
        bool metadataOnly) const override;

    USD_API
    virtual bool WriteToFile(
        const SdfLayer& layer,
        const std::string& filePath,
        const std::string& comment = std::string(),
        const FileFormatArguments& args = FileFormatArguments()) const override;

    USD_API
    virtual bool ReadFromString(
        SdfLayer* layer,
        const std::string& str) const override;

    USD_API
    virtual bool WriteToString(
        const SdfLayer& layer,
        std::string* str,
        const std::string& comment = std::string()) const override;

    USD_API
    virtual bool WriteToStream(
        const SdfSpecHandle &spec,
        std::ostream& out,
        size_t indent) const override;

protected:
    SDF_FILE_FORMAT_FACTORY_ACCESS;

private:
    UsdUsdzFileFormat();
    virtual ~UsdUsdzFileFormat();
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_USDZ_FILE_FORMAT_H
