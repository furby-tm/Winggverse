#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/instantiateSingleton.h"
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
/*
 * This header is not meant to be included in a .h file.
 * Complain if we see this header twice through.
 */

#ifdef FORGE_BASE_TF_INSTANTIATE_SINGLETON_H
#error This file should only be included once in any given source (.cpp) file.
#endif

#define FORGE_BASE_TF_INSTANTIATE_SINGLETON_H

/// \file tf/instantiateSingleton.h
/// \ingroup group_tf_ObjectCreation
/// Manage a single instance of an object.

#include "forge/forge.h"
#include "forge/base/tf/singleton.h"
#include "forge/base/tf/mallocTag.h"
#include "forge/base/arch/demangle.h"

FORGE_NAMESPACE_BEGIN

template <class T> std::mutex* TfSingleton<T>::_mutex = 0;
template <class T> T* TfSingleton<T>::_instance = 0;

template <typename T>
T&
TfSingleton<T>::_CreateInstance()
{
    // Why is TfSingleton<T>::_mutex a pointer requiring allocation and
    // construction and not simply an object?  Because the default
    // std::mutex c'tor on MSVC 2015 isn't constexpr .  That means the
    // mutex is dynamically initialized.  That can be too late for
    // singletons, which are often accessed via ARCH_CONSTRUCTOR()
    // functions.
    static std::once_flag once;
    std::call_once(once, [](){
        TfSingleton<T>::_mutex = new std::mutex;
    });

    TfAutoMallocTag2 tag2("Tf", "TfSingleton::_CreateInstance");
    TfAutoMallocTag tag("Create Singleton " + ArchGetDemangled<T>());

    std::lock_guard<std::mutex> lock(*TfSingleton<T>::_mutex);
    if (!TfSingleton<T>::_instance) {
        ARCH_PRAGMA_PUSH
        ARCH_PRAGMA_MAY_NOT_BE_ALIGNED
        T *inst = new T;
        ARCH_PRAGMA_POP

        // T's constructor could cause this to be created and set
        // already, so guard against that.
        if (!TfSingleton<T>::_instance) {
            TfSingleton<T>::_instance = inst;
        }
    }

    return *TfSingleton<T>::_instance;
}

template <typename T>
void
TfSingleton<T>::_DestroyInstance()
{
    std::lock_guard<std::mutex> lock(*TfSingleton<T>::_mutex);
    delete TfSingleton<T>::_instance;
    TfSingleton<T>::_instance = 0;
}

/// Source file definition that a type is being used as a singleton.
///
/// To use a type \c T in conjunction with \c TfSingleton, add
/// TF_INSTANTIATE_SINGLETON(T) in one source file (typically the .cpp) file
/// for class \c T.
///
/// \hideinitializer
#define TF_INSTANTIATE_SINGLETON(T)                               \
    template class FORGE_NS_GLOBAL::TfSingleton<T>


FORGE_NAMESPACE_END
