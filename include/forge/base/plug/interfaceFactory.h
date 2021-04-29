#line 1 "C:/Users/tyler/dev/WINGG/forge/base/plug/interfaceFactory.h"
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
#ifndef FORGE_BASE_PLUG_INTERFACE_FACTORY_H
#define FORGE_BASE_PLUG_INTERFACE_FACTORY_H

/// \file plug/interfaceFactory.h

#include "forge/forge.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

// For use by \c PLUG_REGISTER_INTERFACE_SINGLETON_TYPE.
class Plug_InterfaceFactory {
public:
    struct Base : public TfType::FactoryBase {
    public:
        virtual void* New() = 0;
    };

    template <class Interface, class Implementation>
    struct SingletonFactory : public Base {
    public:
        virtual void* New()
        {
            static_assert(std::is_abstract<Interface>::value,
                          "Interface type must be abstract.");
            static Implementation impl;
            return static_cast<Interface*>(&impl);
        }
    };
};

/// Defines the \c Interface \c TfType with a factory to return a
/// \c Implementation singleton.  This is suitable for use with
/// \c PlugStaticInterface. \p Interface must be abstract and
/// \p Implementation a concrete subclass of \p Interface.  Note
/// that this is a factory on \c Interface \b not \c Implementation.
///
/// The result of the factory is a singleton instance of \c Implementation
/// and the client of TfType::GetFactory() must not destroy it.
///
/// Clients that want to create instances of types defined in a plugin
/// but not added to the TfType system should create a singleton with
/// factory methods to create those objects.
#define PLUG_REGISTER_INTERFACE_SINGLETON_TYPE(Interface, Implementation)   \
TF_REGISTRY_FUNCTION(TfType)                                                \
{                                                                           \
    TfType::Define<Interface>()                                             \
        .SetFactory<Plug_InterfaceFactory::SingletonFactory<                \
            Interface, Implementation> >();                                 \
}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_PLUG_INTERFACE_FACTORY_H
