#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/singleton.h"
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
#ifndef FORGE_BASE_TF_SINGLETON_H
#define FORGE_BASE_TF_SINGLETON_H

/// \file tf/singleton.h
/// \ingroup group_tf_ObjectCreation
/// Manage a single instance of an object.
///
/// Many classes (for example, registries) should have only a single, globally
/// available instance that is created as needed on demand.  This is a classic
/// design pattern known as a \e singleton.  Additionally, creation of this
/// class (though not access to it per se) must be made threadsafe.
///
/// There are two possibilities in creating a singleton: you can create a
/// class all of whose member functions and variables are static, and let
/// users access this class.  Unfortunately, instantiating the static
/// variables of this class is prone to difficulty; more importantly, should
/// you change your mind and wish to allow multiple instances of the class,
/// much rewriting follows.
///
/// A better solution is to define the class with regular members and
/// variables, and then permit only a single instance of the class to exist.
/// This is the philosophy embodied by the \c TfSingleton template.  It takes
/// care of both multithreaded initialization and initialization before main;
/// the cost of this is quite low (a single boolean comparison to access the
/// instanced object after initial creation). The \c TfSingleton template
/// works in conjunction with a macro in the source file
/// TF_INSTANTIATE_SINGLETON(), which is itself defined by  including the file
/// "forge/base/tf/instantiateSingleton.h".
///
/// \anchor TfSingleton_typicalUse
/// <B> Typical Use </B>
///
/// The typical use of \c TfSingleton is as follows:
/// \code
///     // file: registry.h
///     #include "forge/base/tf/singleton.h"
///     #include <boost/noncopyable.hpp>
///
///     class Registry : boost::noncopyable {
///     public:
///         static Registry& GetInstance() {
///              return TfSingleton<Registry>::GetInstance();
///         }
///
///         ...
///
///     private:
///         Registry();
///         ~Registry();
///
///         friend class TfSingleton<Registry>;
///      };
///
///     // file: Registry.cpp
///     #include "common/astrology/registry.h"
///     #include "forge/base/tf/instantiateSingleton.h"
///
///     TF_INSTANTIATE_SINGLETON(Registry);
///
///
///     // file: RandomCode.cpp
///     #include "common/astrology/registry.h"
///
///     void Code() {
///          Registry& r = Registry::GetInstance();
///          r.Lookup(...);
///          ...
///     }
/// \endcode
///
/// The constructor and destructor are declared private, and the singleton
/// object will typically derive off of \c boost::noncopyable to prevent
/// copying. Note that singleton objects quite commonly also make use of \c
/// TfRegistryManager to acquire the data they need throughout a program.
///
/// The friend class \c TfSingleton<Registry> is the only class allowed to
/// create an instance of a Registry.  The helper function \c
/// Registry::GetInstance() is for convenience only; one can just as well call
/// the longer \c TfSingleton<Registry>::GetInstance() to obtain a reference
/// to the sole instance of the registry.

#include "forge/forge.h"
#include "forge/base/arch/hints.h"
#include "forge/base/arch/pragmas.h"
#include "forge/base/tf/diagnosticLite.h"

#include <mutex>

FORGE_NAMESPACE_BEGIN

/// \class TfSingleton
/// \ingroup group_tf_ObjectCreation
///
/// Manage a single instance of an object (see
///
/// \ref TfSingleton_typicalUse "Typical Use" for a canonical example).
///
template <class T>
class TfSingleton {
public:
    /// Return a reference to an object of type \c T, creating it if
    /// necessary.
    ///
    /// When \c GetInstance() is called for the first time, it creates an
    /// object of type \c T, and returns a reference to it.  The type in
    /// question must have a default constructor (i.e. a constructor taking no
    /// arguments).
    ///
    /// Subsequent calls to \c GetInstance() return a reference to the same
    /// object.  This call is threadsafe; simultaneous attempts to create an
    /// object result in only one object being created; locking beyond this
    /// (for example, letting only one thread at a time call a member
    /// function) are the responsibility of the class author.
    inline static T& GetInstance() {
        ARCH_PRAGMA_PUSH
        // Suppress warnings from clang. TfSingletons are explicitly
        // instantiated, so the warning around this usage is a false positive.
        ARCH_PRAGMA_UNDEFINED_VAR_TEMPLATE
        return ARCH_LIKELY(_instance) ? *_instance : _CreateInstance();
        ARCH_PRAGMA_POP
    }

    /// Return whether or not the single object of type \c T is currently in
    /// existence.
    ///
    /// This call tests whether or not the singleton currently exists.
    static bool CurrentlyExists() {
        return _instance ? true : false;
    }

    /// Indicate that the sole instance object has already been created.
    ///
    /// This function is public, but can only be called usefully from within
    /// the class T itself. This function is used to allow the constructor of
    /// T to indicate that the sole instance of T has been created, and that
    /// future calls to \c GetInstance() can immediately return \p instance.
    ///
    /// The need for this function occurs when the constructor of \c T
    /// generates a call chain that leads to calling \c
    /// TfSingleton<T>::GetInstance(). Until the constructor for \c T has
    /// finished, however, \c TfSingleton<T>::GetInstance() is unable to
    /// return a value. Calling \c SetInstanceConstructed() allows future
    /// calls to \c TfSingleton<T>::GetInstance() to return before \c T's
    /// constructor has finished.
    ///
    /// Be sure that \c T has been constructed (enough) before calling this
    /// function. Calling this function anyplace but within the call chain of
    /// \c T's constructor will generate a fatal coding error.
    static void SetInstanceConstructed(T& instance) {
        if (_instance)
            TF_FATAL_ERROR("this function may not be called after "
                           "GetInstance() has completed");
        _instance = &instance;
    }

    /// Destroy the sole instance object of type \c T, if it exists.
    ///
    /// A singleton can be destroyed by a call to \c DeleteInstance. This call
    /// is threadsafe in the sense that competing simultaneous calls will not
    /// result in double deletion; however, it is up to the user to ensure
    /// that the instance is not being used in one thread during an attempt to
    /// delete the instance from another thread.  After being destroyed, a
    /// call to \c GetInstance() will create a new instance.
    static void DeleteInstance() {
        if (_instance)
            _DestroyInstance();
    }
private:
    static T& _CreateInstance();
    static void _DestroyInstance();
    static T* _instance;
    ARCH_PRAGMA_PUSH
    ARCH_PRAGMA_NEEDS_EXPORT_INTERFACE
    static std::mutex* _mutex;
    ARCH_PRAGMA_POP
};

FORGE_NAMESPACE_END

#endif
