#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/tokens.h"
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
#ifndef FORGE_USD_SDF_TOKENS_H
#define FORGE_USD_SDF_TOKENS_H

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/base/tf/staticTokens.h"

FORGE_NAMESPACE_BEGIN

// Miscellaneous Tokens
#define SDF_TOKENS                                      \
    ((AnyTypeToken, "__AnyType__"))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(SdfTokens, SDF_API, SDF_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#define SDF_PATH_NS_DELIMITER_CHAR ':'
#define SDF_PATH_NS_DELIMITER_STR ":"

#define SDF_PATH_TOKENS                                 \
    ((menvaStart, "<"))                                 \
    ((menvaEnd, ">"))                                   \
    ((absoluteIndicator, "/"))                          \
    ((relativeRoot, "."))                               \
    ((childDelimiter, "/"))                             \
    ((propertyDelimiter, "."))                          \
    ((relationshipTargetStart, "["))                    \
    ((relationshipTargetEnd, "]"))                      \
    ((parentPathElement, ".."))                         \
    ((mapperIndicator, "mapper"))                       \
    ((expressionIndicator, "expression"))               \
    ((mapperArgDelimiter, "."))                         \
    ((namespaceDelimiter, SDF_PATH_NS_DELIMITER_STR))   \
    ((empty, ""))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(SdfPathTokens, SDF_API, SDF_PATH_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#define SDF_METADATA_DISPLAYGROUP_TOKENS              \
    ((core, ""))                                      \
    ((internal, "Internal"))                          \
    ((dmanip, "Direct Manip"))                        \
    ((pipeline, "Pipeline"))                          \
    ((symmetry, "Symmetry"))                          \
    ((ui, "User Interface"))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(SdfMetadataDisplayGroupTokens, SDF_API, SDF_METADATA_DISPLAYGROUP_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_TOKENS_H
