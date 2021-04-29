#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/dynamicFileFormatInterface.h"
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
#ifndef FORGE_USD_PCP_DYNAMIC_FILE_FORMAT_INTERFACE_H
#define FORGE_USD_PCP_DYNAMIC_FILE_FORMAT_INTERFACE_H

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"
#include "forge/usd/sdf/fileFormat.h"

FORGE_NAMESPACE_BEGIN

class PcpDynamicFileFormatContext;
class VtValue;

/// \class PcpDynamicFileFormatInterface
///
/// Interface mixin that can be included by SdfFileFormat subclasses to enable
/// dynamic file format argument generation for a file format plugin.
/// When prim index composition encounters a payload to an asset of a file
/// format that implements this interface, it will call
/// ComposeFieldsForFileFormatArguments to generate arguments from the current
/// composition context at which the payload is being added. The derived file
/// format is on the hook for using the provided context to compute any prim
/// field values it needs and generate the relevant file format arguments for
/// its content.
class PcpDynamicFileFormatInterface
{
public:
    /// Empty virtual destructor to prevent build errors with some compilers.
    PCP_API
    virtual ~PcpDynamicFileFormatInterface();

    /// Derived classes must implement this function to compose prim fields
    /// using the given \p context and use them to generate file format
    /// arguments for the layer at \p assetPath. The context provides methods
    /// to compose field values at the current point in prim index composition
    /// which can be used to generate the relevant file format arguments. These
    /// arguments need to be added to the set of file format arguments provided
    /// by \p args.
    ///
    /// Additionally, implementations can output \p dependencyContextData of
    /// any value type that will then be passed back in to calls to
    /// CanFieldChangeAffectFileFormatArguments during change processing.
    /// This can be used to provide more that context that is specific to the
    /// file format when determining whether a field change really does affect
    /// the arguments generated by a particular call to this function.
    PCP_API
    virtual void ComposeFieldsForFileFormatArguments(
        const std::string& assetPath,
        const PcpDynamicFileFormatContext &context,
        SdfFileFormat::FileFormatArguments* args,
        VtValue *dependencyContextData) const = 0;

    /// Derived classes must implement this function to return true if the
    /// change to scene description of the field named \p field can affect the
    /// dynamic file format arguments generated by
    /// ComposeFieldsForFileFormatArguments. This function will be called during
    /// change processing to determine whether a change to a field affects
    /// the dynamic file format arguments of a payload that a prim index depends
    /// on.
    ///
    /// \p oldValue and \p newValue contain the old and new values of the field.
    /// \p dependencyContextData is the arbitrary typed data that was generated
    /// by the call to ComposeFieldsForFileFormatArguments when the payload arc
    /// was computed.
    PCP_API
    virtual bool CanFieldChangeAffectFileFormatArguments(
        const TfToken& field,
        const VtValue& oldValue,
        const VtValue& newValue,
        const VtValue &dependencyContextData) const = 0;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_DYNAMIC_FILE_FORMAT_INTERFACE_H