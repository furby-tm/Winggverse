#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/shaderSection.h"
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

#ifndef FORGE_IMAGING_HGI_SHADERSECTION_H
#define FORGE_IMAGING_HGI_SHADERSECTION_H

#include "forge/forge.h"
#include "forge/imaging/hgi/api.h"
#include <memory>
#include <ostream>
#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

//struct to hold attribute definitions
struct HgiShaderSectionAttribute
{
    std::string identifier;
    std::string index;
};

using HgiShaderSectionAttributeVector =
    std::vector<HgiShaderSectionAttribute>;

/// \class HgiShaderSection
///
/// A base class for a Shader Section.
/// In its simplest form then it is a construct that knows
/// how to declare itself, define and pass as param.
/// Can be subclassed to add more behaviour for complex cases
/// and to hook into the visitor tree.
///
class HgiShaderSection
{
public:
    HGI_API
    virtual ~HgiShaderSection();

    /// Write out the type, shader section does not hold a type
    /// string as how a type is defined is fully controlled
    /// by sub classes and no assumptions are made
    HGI_API
    virtual void WriteType(std::ostream& ss) const;

    /// Writes the unique name of an instance of the section
    HGI_API
    virtual void WriteIdentifier(std::ostream& ss) const;

    /// Writes a decleration statement for a member or in global scope
    HGI_API
    virtual void WriteDeclaration(std::ostream& ss) const;

    /// Writes the section as a parameter to a function
    HGI_API
    virtual void WriteParameter(std::ostream& ss) const;

    HGI_API
    const HgiShaderSectionAttributeVector& GetAttributes() const;

protected:
    HGI_API
    explicit HgiShaderSection(
            const std::string &identifier,
            const HgiShaderSectionAttributeVector& attributes = {},
            const std::string &defaultValue = std::string());

    HGI_API
    const std::string& _GetDefaultValue() const;

private:
    const std::string _identifierVar;
    const HgiShaderSectionAttributeVector _attributes;
    const std::string _defaultValue;
};

FORGE_NAMESPACE_END

#endif
