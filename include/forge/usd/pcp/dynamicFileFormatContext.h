#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/dynamicFileFormatContext.h"
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
#ifndef FORGE_USD_PCP_DYNAMIC_FILE_FORMAT_CONTEXT_H
#define FORGE_USD_PCP_DYNAMIC_FILE_FORMAT_CONTEXT_H

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"
#include "forge/usd/pcp/node.h"

FORGE_NAMESPACE_BEGIN

class PcpPrimIndex_StackFrame;
class PcpCache;

/// \class PcpDynamicFileFormatContext
///
/// Context object for the current state of a prim index that is being built
/// that allows implementations of PcpDynamicFileFormatInterface to compose
/// field values when generating dynamic file format arguments. The context
/// allows us to iterate over all nodes that have already been composed looking
/// for the strongest opinion for a relevant field.
class PcpDynamicFileFormatContext
{
public:
    using VtValueVector = std::vector<VtValue>;

    PCP_API
    ~PcpDynamicFileFormatContext() = default;

    /// Compose the \p value of the given \p field and return its current
    /// strongest opinion. For dictionary valued fields this will be a
    /// dictionary containing the strongest value for each individual key.
    /// Returns true if a value for the field was found.
    PCP_API
    bool ComposeValue(const TfToken &field, VtValue *value) const;

    /// Compose the \p values of the given \p field returning all available
    /// opinions ordered from strongest to weakest. For dictionary valued
    /// fields, the dictionaries from each opinion are not composed together
    /// at each step and are instead returned in the list as is.
    /// Returns true if a value for the field was found.
    ///
    /// Note that this is slower than ComposeValue, especially for
    /// non-dictionary valued fields, and should only be used if knowing more
    /// than just the strongest value is necessary.
    PCP_API
    bool ComposeValueStack(const TfToken &field,
                           VtValueVector *values) const;

private:
    // Callback function for ComposeValue. This callback function will
    // be passed values for the field given to ComposeValue from
    // strongest to weakest available opinion and is free to copy or
    // swap out the value as desired.
    using _ComposeFunction = std::function<void(VtValue &&)>;

    /// Constructs a context.
    /// \p parentNode and \p previousFrame are used to traverse the
    /// current state of the prim index graph when composing the opinions on
    /// fields. \p composedFieldNames is the set of field names that is
    /// to be updated with the names of fields that ComposeValue and
    /// ComposeValueStack are called on for dependency tracking.
    PcpDynamicFileFormatContext(
        const PcpNodeRef &parentNode,
        PcpPrimIndex_StackFrame *previousFrame,
        TfToken::Set *composedFieldNames);
    /// Access to private constructor. Should only be called by prim indexing.
    friend PcpDynamicFileFormatContext Pcp_CreateDynamicFileFormatContext(
        const PcpNodeRef &, PcpPrimIndex_StackFrame *, TfToken::Set *);

    /// Returns whether the given \p field is allowed to be used to generate
    /// file format arguments. It can also return whether the value type of
    /// the field is a dictionary if needed.
    bool _IsAllowedFieldForArguments(
        const TfToken &field, bool *fieldValueIsDictionary = nullptr) const;

private:
    PcpNodeRef _parentNode;
    PcpPrimIndex_StackFrame *_previousStackFrame;

    // Cached names of fields that had values composed by this context.
    TfToken::Set *_composedFieldNames;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_DYNAMIC_FILE_FORMAT_CONTEXT_H
