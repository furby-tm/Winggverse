#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/textParserContext.h"
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
#ifndef FORGE_USD_SDF_TEXT_PARSER_CONTEXT_H
#define FORGE_USD_SDF_TEXT_PARSER_CONTEXT_H

#include "forge/forge.h"
#include "forge/usd/sdf/data.h"
#include "forge/usd/sdf/layerHints.h"
#include "forge/usd/sdf/layerOffset.h"
#include "forge/usd/sdf/listOp.h"
#include "forge/usd/sdf/parserValueContext.h"
#include "forge/usd/sdf/path.h"
#include "forge/usd/sdf/payload.h"
#include "forge/usd/sdf/reference.h"
#include "forge/usd/sdf/types.h"

#include "forge/base/vt/dictionary.h"

#include "forge/base/tf/token.h"

#include <boost/optional.hpp>

#include <string>
#include <vector>

// Lexical scanner type.
typedef void *yyscan_t;

FORGE_NAMESPACE_BEGIN

// This class contains the global state while parsing a menva file.
// It contains the data structures that we use to create the scene description
// from the file.

class Sdf_TextParserContext {
public:
    // Constructor.
    Sdf_TextParserContext();

    // Destructor.
    ~Sdf_TextParserContext() {
    }

    std::string magicIdentifierToken;
    std::string versionString;
    std::string fileContext;

    // State for layer refs, in general
    std::string layerRefPath;
    SdfLayerOffset layerRefOffset;

    // State for sublayers
    std::vector<std::string> subLayerPaths;

    // State for sublayer offsets
    std::vector<SdfLayerOffset> subLayerOffsets;

    // String list currently being built
    std::vector<TfToken> nameVector;

    SdfTimeSampleMap timeSamples;
    double timeSampleTime;

    SdfPath savedPath;

    // Whether the current relationship target being parsed is allowed to
    // have data like relational attributes.
    bool relParsingAllowTargetData;
    // relationship target paths that will be saved in a list op
    // (use a boost::optional to track whether we have seen an opinion at all.)
    boost::optional<SdfPathVector> relParsingTargetPaths;
    // relationship target paths that will be appended to the relationship's
    // list of target children.
    SdfPathVector relParsingNewTargetChildren;

    // helpers for connection path parsing
    SdfPathVector connParsingTargetPaths;
    bool connParsingAllowConnectionData;

    // helpers for inherit path parsing
    SdfPathVector inheritParsingTargetPaths;

    // helpers for specializes path parsing
    SdfPathVector specializesParsingTargetPaths;

    // helpers for reference parsing
    SdfReferenceVector referenceParsingRefs;

    // helpers for payload parsing
    SdfPayloadVector payloadParsingRefs;

    // helper for relocates parsing
    SdfRelocatesMap relocatesParsingMap;

    // helpers for generic metadata
    TfToken genericMetadataKey;
    SdfListOpType listOpType;

    // The value parser context
    Sdf_ParserValueContext values;

    // Last parsed value
    VtValue currentValue;

    // Vector of dictionaries used to parse nested dictionaries.
    // The first element in the vector contains the last parsed dictionary.
    std::vector<VtDictionary> currentDictionaries;

    bool seenError;

    bool custom;
    SdfSpecifier specifier;
    SdfDataRefPtr data;
    SdfPath path;
    TfToken typeName;
    VtValue variability;
    VtValue assoc;

    // Should we only read metadata from the file?
    bool metadataOnly;

    // Hints to fill in about the layer's contents.
    SdfLayerHints layerHints;

    // Stack for the child names of all the prims currently being parsed
    // For instance if we're currently parsing /A/B then this vector
    // will contain three elements:
    //    names of the root prims
    //    names of A's children
    //    names of B's children.
    std::vector<std::vector<TfToken> > nameChildrenStack;

    // Stack for the property names of all the objects currently being parsed
    std::vector<std::vector<TfToken> > propertiesStack;

    // Stack of names of variant sets  being built.
    std::vector<std::string> currentVariantSetNames;

    // Stack of names of variants for the variant sets being built
    std::vector<std::vector<std::string> > currentVariantNames;

    unsigned int menvaLineNo;

    // Used by flex for reentrant parsing
    yyscan_t scanner;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_TEXT_PARSER_CONTEXT_H
