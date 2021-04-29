#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/handle.h"
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
#ifndef FORGE_IMAGING_HGI_HANDLE_H
#define FORGE_IMAGING_HGI_HANDLE_H

#include "forge/forge.h"
#include "forge/imaging/hgi/api.h"

#include <stdint.h>

FORGE_NAMESPACE_BEGIN

/// \class HgiHandle
///
/// Handle that contains a hgi object and unique id.
///
/// The unique id is used to compare two handles to gaurd against pointer
/// aliasing, where the same memory address is used to create a similar object,
/// but it is not actually the same object.
///
/// Handle is not a shared or weak_ptr and destruction of the contained object
/// should be explicitely managed by the client via the HgiDestroy*** functions.
///
/// If shared/weak ptr functionality is desired, the client creating Hgi objects
/// can wrap the returned handle in a shared_ptr.
///
template<class T>
class HgiHandle
{
public:
    HgiHandle() : _ptr(nullptr), _id(0) {}
    HgiHandle(T* obj, uint64_t id) : _ptr(obj), _id(id) {}

    T*
    Get() const {
        return _ptr;
    }

    // Note this only checks if a ptr is set, it does not offer weak_ptr safety.
    explicit operator bool() const {return _ptr!=nullptr;}

    // Pointer access operator
    T* operator ->() const {return _ptr;}

    bool operator==(const HgiHandle& other) const {
        return _id == other._id;
    }

    bool operator!=(const HgiHandle& other) const {
        return !(*this == other);
    }

private:
    T* _ptr;
    uint64_t _id;
};


FORGE_NAMESPACE_END

#endif
