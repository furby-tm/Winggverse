#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/jsonSerialization.h"
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

#ifndef FORGE_BASE_TRACE_JSON_SERIALIZATION_H
#define FORGE_BASE_TRACE_JSON_SERIALIZATION_H

#include "forge/forge.h"
#include "forge/base/trace/collection.h"

FORGE_NAMESPACE_BEGIN

class JsValue;
class JsWriter;

///////////////////////////////////////////////////////////////////////////////
/// \class Trace_JSONSerialization
///
/// This class contains methods to read and write TraceCollections in JSON
/// format.  This JSON format for a TraceCollection is an extension of the
/// Chrome Tracing format.
class Trace_JSONSerialization {
public:
    /// Write a JSON representation of \p collections.
    static bool WriteCollectionsToJSON(JsWriter& js,
        const std::vector<std::shared_ptr<TraceCollection>>& collections);

    /// Creates a TraceCollection from a JSON value if possible.
    static std::unique_ptr<TraceCollection> CollectionFromJSON(const JsValue&);
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_JSON_SERIALIZATION_H
