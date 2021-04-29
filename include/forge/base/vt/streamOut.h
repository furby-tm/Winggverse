#line 1 "C:/Users/tyler/dev/WINGG/forge/base/vt/streamOut.h"
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
#ifndef FORGE_BASE_VT_STREAM_OUT_H
#define FORGE_BASE_VT_STREAM_OUT_H

#include "forge/forge.h"
#include "forge/base/vt/api.h"
#include "forge/base/tf/enum.h"

#include <iosfwd>
#include <typeinfo>
#include <type_traits>

FORGE_NAMESPACE_BEGIN

// Helper that's used to stream a generic string for a type that isn't
// streamable and doesn't provide VtStreamOut.  Inserts a message like
// <'typeName' @ 0xXXXXXXXX>.
VT_API std::ostream &
Vt_StreamOutGeneric(std::type_info const &type,
                    void const *addr,
                    std::ostream &stream);

// Function used in the case that T has a stream insertion operator.
template <class T>
inline auto
Vt_StreamOutImpl(T const &obj, std::ostream &stream, int)
    -> decltype(stream << obj)
{
    return stream << obj;
}

// Function used in the case that T does not have a stream insertion operator.
template <class T>
inline std::ostream &
Vt_StreamOutImpl(T const &obj, std::ostream &stream, long)
{
    return Vt_StreamOutGeneric(
        typeid(T), static_cast<void const *>(&obj), stream);
}

/// VtValue and VtArray make unqualified calls to VtStreamOut when writing
/// values to streams.  Clients may overload VtStreamOut for their own types
/// if desired.
template <class T>
typename std::enable_if<!std::is_enum<T>::value, std::ostream &>::type
VtStreamOut(T const &obj, std::ostream &stream)
{
    // For types that have an operator<< suitable for ostream, we use the
    // traditional int/long 0-argument technique to disambiguate overloads.
    return Vt_StreamOutImpl(obj, stream, 0);
}
template <class EnumT>
typename std::enable_if<std::is_enum<EnumT>::value, std::ostream &>::type
VtStreamOut(EnumT const &e, std::ostream &stream)
{
    return VtStreamOut(TfEnum::GetName(e), stream);
}
VT_API std::ostream &VtStreamOut(bool const &, std::ostream &);
VT_API std::ostream &VtStreamOut(char const &, std::ostream &);
VT_API std::ostream &VtStreamOut(unsigned char const &, std::ostream &);
VT_API std::ostream &VtStreamOut(signed char const &, std::ostream &);
VT_API std::ostream &VtStreamOut(float const &, std::ostream &);
VT_API std::ostream &VtStreamOut(double const &, std::ostream &);

class VtStreamOutIterator {
public:
    VT_API virtual ~VtStreamOutIterator();
    virtual void Next(std::ostream&) = 0;
};

struct Vt_ShapeData;

VT_API void VtStreamOutArray(VtStreamOutIterator*, size_t size,
                             const Vt_ShapeData*, std::ostream&);

#ifdef FORGE_PYTHON_SUPPORT_ENABLED
VT_API std::ostream &VtStreamOut(class TfPyObjWrapper const &, std::ostream &);
#endif // FORGE_PYTHON_SUPPORT_ENABLED

FORGE_NAMESPACE_END

#endif // FORGE_BASE_VT_STREAM_OUT_H
