#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/plugin/usdAbc/alembicFileFormat.h"
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
#ifndef FORGE_USD_PLUGIN_USD_ABC_ALEMBIC_FILE_FORMAT_H
#define FORGE_USD_PLUGIN_USD_ABC_ALEMBIC_FILE_FORMAT_H

#include "forge/forge.h"
#include "forge/usd/sdf/fileFormat.h"
#include "forge/base/tf/staticTokens.h"
#include <iosfwd>
#include <string>

FORGE_NAMESPACE_BEGIN

#define USDABC_ALEMBIC_FILE_FORMAT_TOKENS  \
    ((Id,      "abc"))                  \
    ((Version, "1.0"))                  \
    ((Target,  "usd"))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(UsdAbcAlembicFileFormatTokens, USDABC_ALEMBIC_FILE_FORMAT_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

TF_DECLARE_WEAK_AND_REF_PTRS(UsdAbcAlembicFileFormat);

/// \class UsdAbcAlembicFileFormat
///
class UsdAbcAlembicFileFormat : public SdfFileFormat {
public:
    // SdfFileFormat overrides
    virtual SdfAbstractDataRefPtr InitData(const FileFormatArguments&) const override;
    virtual bool CanRead(const std::string &file) const override;
    virtual bool Read(SdfLayer* layer,
                      const std::string& resolvedPath,
                      bool metadataOnly) const override;
    virtual bool WriteToFile(const SdfLayer& layer,
                             const std::string& filePath,
                             const std::string& comment = std::string(),
                             const FileFormatArguments& args =
                                 FileFormatArguments()) const override;
    virtual bool ReadFromString(SdfLayer* layer,
                                const std::string& str) const override;
    virtual bool WriteToString(const SdfLayer& layer,
                               std::string* str,
                               const std::string& comment=std::string())
                               const override;
    virtual bool WriteToStream(const SdfSpecHandle &spec,
                               std::ostream& out,
                               size_t indent) const override;

protected:
    SDF_FILE_FORMAT_FACTORY_ACCESS;

    virtual ~UsdAbcAlembicFileFormat();

    UsdAbcAlembicFileFormat();

private:
    SdfFileFormatConstPtr _usda;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_PLUGIN_USD_ABC_ALEMBIC_FILE_FORMAT_H
