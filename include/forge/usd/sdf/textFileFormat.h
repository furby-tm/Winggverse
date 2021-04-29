#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/textFileFormat.h"
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
#ifndef FORGE_USD_SDF_TEXT_FILE_FORMAT_H
#define FORGE_USD_SDF_TEXT_FILE_FORMAT_H

/// \file sdf/textFileFormat.h

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/sdf/fileFormat.h"
#include "forge/base/tf/staticTokens.h"

#include <iosfwd>
#include <string>

FORGE_NAMESPACE_BEGIN

#define SDF_TEXT_FILE_FORMAT_TOKENS \
    ((Id,      "sdf"))              \
    ((Version, "1.4.32"))           \
    ((Target,  "sdf"))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(SdfTextFileFormatTokens, SDF_API, SDF_TEXT_FILE_FORMAT_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

TF_DECLARE_WEAK_AND_REF_PTRS(SdfTextFileFormat);

SDF_DECLARE_HANDLES(SdfSpec);

/// \class SdfTextFileFormat
///
/// Sdf text file format
///
class SdfTextFileFormat : public SdfFileFormat
{
public:
    // SdfFileFormat overrides.
    SDF_API
    virtual bool CanRead(const std::string &file) const override;

    SDF_API
    virtual bool Read(
        SdfLayer* layer,
        const std::string& resolvedPath,
        bool metadataOnly) const override;

    SDF_API
    virtual bool WriteToFile(
        const SdfLayer& layer,
        const std::string& filePath,
        const std::string& comment = std::string(),
        const FileFormatArguments& args = FileFormatArguments()) const override;

    SDF_API
    virtual bool ReadFromString(
        SdfLayer* layer,
        const std::string& str) const override;

    SDF_API
    virtual bool WriteToString(
        const SdfLayer& layer,
        std::string* str,
        const std::string& comment = std::string()) const override;

    SDF_API
    virtual bool WriteToStream(
        const SdfSpecHandle &spec,
        std::ostream& out,
        size_t indent) const override;

protected:
    SDF_FILE_FORMAT_FACTORY_ACCESS;

    /// Destructor.
    SDF_API
    virtual ~SdfTextFileFormat();

    /// Constructor.
    SDF_API
    SdfTextFileFormat();

    /// Constructor. This form of the constructor may be used by formats that
    /// use the .sdf text format as their internal representation.
    /// If a non-empty versionString and target are provided, they will be
    /// used as the file format version and target; otherwise the .sdf format
    /// version and target will be implicitly used.
    SDF_API
    explicit SdfTextFileFormat(const TfToken& formatId,
                               const TfToken& versionString = TfToken(),
                               const TfToken& target = TfToken());

private:
    // Override to return false.  Reloading anonymous text layers clears their
    // content.
    SDF_API virtual bool _ShouldSkipAnonymousReload() const override;
};

FORGE_NAMESPACE_END

#endif // SDF_TEXT_FILE_FORMAT_H
