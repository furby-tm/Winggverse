#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hio/glslfxConfig.h"
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
#ifndef FORGE_IMAGING_HIO_GLSLFX_CONFIG_H
#define FORGE_IMAGING_HIO_GLSLFX_CONFIG_H

/// \file hio/glslfxConfig.h

#include "forge/forge.h"
#include "forge/imaging/hio/api.h"
#include "forge/base/tf/token.h"
#include "forge/base/vt/dictionary.h"

#include <string>

FORGE_NAMESPACE_BEGIN

/// \class HioGlslfxConfig
///
/// A class representing the configuration of a glslfx file.
///
/// HioGlslfxConfig provides an API for querying the configuration of a
/// glslfx file
///
class HioGlslfxConfig
{
public:
    /// Enumerates Roles that parameters can have.
    ///
    /// <b>enum Role:</b>
    /// <ul>
    ///     <li><b><c> RoleNone  = 0</c></b>   None:  the default role
    ///     <li><b><c> RoleColor = 1</c></b>   Color: the role of a color
    /// </ul>
    ///
    enum Role {
        RoleNone = 0,
        RoleColor = 1,
    };

    /// \class Parameter
    ///
    /// A class representing a parameter.
    ///
    class Parameter {
    public:
        Parameter(std::string const & name,
                  VtValue const & defaultValue,
                  std::string const & docString = "",
                  Role const & role = RoleNone) :
            name(name),
            defaultValue(defaultValue),
            docString(docString),
            role(role) { }

        std::string name;
        VtValue defaultValue;
        std::string docString;
        Role role;
    };

    typedef std::vector<Parameter> Parameters;

    /// \class Texture
    ///
    /// A class representing a texture.
    ///
    class Texture {
    public:
        Texture(std::string const & name,
                VtValue const & defaultValue,
                std::string const & docString = "") :
            name(name),
            defaultValue(defaultValue),
            docString(docString) { }

        std::string name;
        VtValue defaultValue;
        std::string docString;
    };

    typedef std::vector<Texture> Textures;

    /// \class Attribute
    ///
    /// A class representing an attribute.
    ///
    class Attribute {
    public:
        Attribute(std::string const & name,
                  VtValue const & defaultValue,
                  std::string const & docString = "") :
            name(name),
            defaultValue(defaultValue),
            docString(docString) { }

        std::string name;
        VtValue defaultValue;
        std::string docString;
    };

    typedef std::vector<Attribute> Attributes;

    /// Create a new HioGlslfxConfig from an input string
    ///
    /// The \p filename parameter is only used for error reporting.
    ///
    HIO_API
    static HioGlslfxConfig * Read(TfToken const & technique,
                                  std::string const & input,
                                  std::string const & filename,
                                  std::string *errorStr);

    typedef std::vector<std::string> SourceKeys;

    typedef VtDictionary MetadataDictionary;

    /// Return the set of source keys for a particular shader stage
    HIO_API
    SourceKeys GetSourceKeys(TfToken const & shaderStageKey) const;

    /// Return the parameters specified in the configuration
    HIO_API
    Parameters GetParameters() const;

    /// Return the textures specified in the configuration
    HIO_API
    Textures GetTextures() const;

    /// Returns the attributes specified in the configuration
    HIO_API
    Attributes GetAttributes() const;

    /// Returns the metadata specified in the configuration
    HIO_API
    MetadataDictionary GetMetadata() const;

private:
    // private ctor. should only be called by ::Read
    HioGlslfxConfig(TfToken const& technique,
                    VtDictionary const & dict,
                    std::string *errorStr);

    void _Init(VtDictionary const & dict, std::string *errorStr);

    Parameters _GetParameters(VtDictionary const & dict,
                              std::string *errorStr) const;
    Textures _GetTextures(VtDictionary const & dict,
                          std::string *errorStr) const;

    Attributes _GetAttributes(VtDictionary const & dict,
                              std::string *errorStr) const;

    MetadataDictionary _GetMetadata(VtDictionary const & dict,
                                    std::string *errorStr) const;

    typedef std::map<std::string, SourceKeys> _SourceKeyMap;
    _SourceKeyMap _GetSourceKeyMap(VtDictionary const & dict,
                                   std::string *errorStr) const;

    TfToken _technique;
    Parameters _params;
    Textures _textures;
    Attributes _attributes;
    MetadataDictionary _metadata;
    _SourceKeyMap _sourceKeyMap;
};


FORGE_NAMESPACE_END

#endif
