#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/plugin/usdMtlx/utils.h"
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

#ifndef FORGE_USD_PLUGIN_USD_MTLX_UTILS_H
#define FORGE_USD_PLUGIN_USD_MTLX_UTILS_H

#include "forge/forge.h"
#include "forge/usd/plugin/usdMtlx/api.h"
#include "forge/usd/ndr/declare.h"
#include "forge/usd/sdf/valueTypeName.h"
#include "forge/base/tf/staticTokens.h"
#include "forge/base/vt/value.h"
#include <MaterialXCore/Document.h>
#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

#define USD_MTLX_TOKENS \
    ((DefaultOutputName, "out"))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(UsdMtlxTokens, USDMTLX_LOCAL, USD_MTLX_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/// Return the contents of a search path environment variable named
/// \p name as a vector of strings.  The path is split on the platform's
/// native path list separator.
USDMTLX_LOCAL
NdrStringVec
UsdMtlxGetSearchPathsFromEnvVar(const char* name);

/// Combines two search path lists.
USDMTLX_LOCAL
NdrStringVec
UsdMtlxMergeSearchPaths(const NdrStringVec& stronger,
                        const NdrStringVec& weaker);

/// Return the MaterialX standard library paths.  All standard library
/// files (and only standard library files) should be found on these
/// paths.
USDMTLX_LOCAL
const NdrStringVec&
UsdMtlxStandardLibraryPaths();

/// Return the MaterialX standard file extensions.
USDMTLX_LOCAL
NdrStringVec
UsdMtlxStandardFileExtensions();

/// Return the (possibly cached) MaterialX document at \p resolvedUri.
/// Return null if the document could not be read and report a
/// warning (once per uri).  \p resolvedUri may be empty to indicate
/// the MaterialX standard library documents all rolled into one.
USDMTLX_LOCAL
MaterialX::ConstDocumentPtr
UsdMtlxGetDocument(const std::string& resolvedUri);

/// Returns the (possibly cached) MaterialX document created from the given
/// string containing the source MaterialX XML.
USDMTLX_LOCAL
MaterialX::ConstDocumentPtr
UsdMtlxGetDocumentFromString(const std::string &mtlxXml);

// Return the version of the mtlx element.  If the version cannot be
// found then return an invalid default version.  If implicitDefault
// isn't null then we do to two things:  we set implicitDefault to
// false iff the isdefaultversion attribute exists and isn't empty,
// otherwise we set it to true;  and we return the version as a
// default if isdefaultversion exists and is set to "true".
USDMTLX_LOCAL
NdrVersion
UsdMtlxGetVersion(const MaterialX::ConstInterfaceElementPtr& mtlx,
                  bool* implicitDefault = nullptr);

/// Return the source URI for a MaterialX element.  If the element
/// doesn't have a non-empty URI then return the source URI of the
/// closest element up the element hierarchy that does have one.
/// Return the empty string if no element has a source URI.
USDMTLX_LOCAL
const std::string&
UsdMtlxGetSourceURI(const MaterialX::ConstElementPtr& element);

/// Result of \c UsdMtlxGetUsdType().
struct UsdMtlxUsdTypeInfo {
    UsdMtlxUsdTypeInfo(
        SdfValueTypeName valueTypeName,
        bool valueTypeNameIsExact,
        TfToken shaderPropertyType,
        int arraySize=0)
        : valueTypeName(valueTypeName)
        , shaderPropertyType(shaderPropertyType)
        , arraySize(arraySize)
        , valueTypeNameIsExact(valueTypeNameIsExact)
    { }

    /// The value type name that most closely matches the MaterialX type.
    /// If the type isn't recognized this is the invalid value type name.
    /// Clients can check for array types by calling \c IsArray() on this.
    SdfValueTypeName valueTypeName;

    /// The exact \c SdrShaderProperty type name.  If there is no exact
    /// match this is empty.
    TfToken shaderPropertyType;

    /// If the value type is a fixed-size array/tuple, this will be greater
    /// then zero.  For "dynamic arrays" this will be zero.
    int arraySize;

    /// \c true iff the value type name is an exact match to the
    /// MaterialX type.
    bool valueTypeNameIsExact;
};

/// Convert a (standard) MaterialX type name.
USDMTLX_LOCAL
UsdMtlxUsdTypeInfo
UsdMtlxGetUsdType(const std::string& mtlxTypeName);

/// Return the value in \p mtlx as a \c VtValue.  Returns an
/// empty VtValue and reports an error if the conversion cannot be
/// applied.  If \p getDefaultValue is \c true then converts the
/// default value.  It is not an error if the value doesn't exist;
/// that silently returns an empty VtValue.
USDMTLX_LOCAL
VtValue
UsdMtlxGetUsdValue(const MaterialX::ConstElementPtr& mtlx,
                   bool getDefaultValue = false);

/// Return the MaterialX values in \p values assuming it contains an
/// array of values of MaterialX type \p type as a vector of VtValue.
USDMTLX_LOCAL
std::vector<VtValue>
UsdMtlxGetPackedUsdValues(const std::string& values, const std::string& type);

/// Split a MaterialX string array into a vector of strings.
///
/// The MaterialX specification says:
///
/// > Individual string values within stringarrays may not contain
/// > commas or semicolons, and any leading and trailing whitespace
/// > characters in them is ignored.
///
/// These restrictions do not apply to the string type.
USDMTLX_LOCAL
std::vector<std::string>
UsdMtlxSplitStringArray(const std::string& s);

FORGE_NAMESPACE_END

#endif // FORGE_USD_PLUGIN_USD_MTLX_UTILS_H
