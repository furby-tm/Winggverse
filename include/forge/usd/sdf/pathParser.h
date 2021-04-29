#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/pathParser.h"
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
#ifndef FORGE_USD_SDF_PATH_PARSER_H
#define FORGE_USD_SDF_PATH_PARSER_H

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/usd/sdf/path.h"
#include "forge/base/tf/token.h"
#include <string>
#include <vector>

// Opaque buffer type handle.
struct yy_buffer_state;

// Lexical scanner type.
typedef void *yyscan_t;

// Lexical scanner value type.
struct Sdf_PathLexerValue {
    FORGE_NS::TfToken token;
    FORGE_NS::SdfPath path;
};
#define YYSTYPE Sdf_PathLexerValue

typedef std::vector< std::pair<FORGE_NS::TfToken,
                               FORGE_NS::TfToken> > Sdf_PathVariantSelections;

// Lexical scanner context.
struct Sdf_PathParserContext {
    FORGE_NS::SdfPath path;
    std::vector<Sdf_PathVariantSelections> variantSelectionStack;
    std::string errStr;
    yyscan_t scanner;
};

// Generated bison symbols.
int pathYyparse(Sdf_PathParserContext *context);
int pathYylex_init(yyscan_t *yyscanner);
int pathYylex_destroy(yyscan_t yyscanner);
yy_buffer_state *pathYy_scan_string(const char* str, yyscan_t yyscanner);
yy_buffer_state *pathYy_scan_bytes(const char* str, size_t len,
                                   yyscan_t yyscanner);
void pathYy_delete_buffer(yy_buffer_state *b, yyscan_t yyscanner);

FORGE_NAMESPACE_BEGIN

SDF_API
int SdfPathYyparse(Sdf_PathParserContext *context);
SDF_API
int SdfPathYylex_init(yyscan_t *yyscanner);
SDF_API
int SdfPathYylex_destroy(yyscan_t yyscanner);
SDF_API
yy_buffer_state *SdfPathYy_scan_string(const char* str, yyscan_t yyscanner);

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_PATH_PARSER_H
