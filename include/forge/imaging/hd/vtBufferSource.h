#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/vtBufferSource.h"
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
#ifndef FORGE_IMAGING_HD_VT_BUFFER_SOURCE_H
#define FORGE_IMAGING_HD_VT_BUFFER_SOURCE_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/types.h"

#include "forge/base/tf/token.h"
#include "forge/base/gf/matrix4d.h"
#include "forge/base/vt/value.h"

#include <vector>

#include <iosfwd>

FORGE_NAMESPACE_BEGIN


/// \class HdVtBufferSource
///
/// An implementation of HdBufferSource where the source data value is a
/// VtValue.
///
class HdVtBufferSource final : public HdBufferSource
{
public:
    /// Constructs a new buffer from a VtValue.
    ///
    /// \param arraySize indicates how many values are provided per element.
    HD_API
    HdVtBufferSource(TfToken const &name, VtValue const& value,
                     int arraySize=1);

    /// Constructs a new buffer from a matrix.
    /// The data is convert to the default type (see GetDefaultMatrixType()).
    ///
    /// note that if we use above VtValue taking constructor, we can use
    /// either float or double matrix regardless the default type.
    HD_API
    HdVtBufferSource(TfToken const &name, GfMatrix4d const &matrix);

    /// Constructs a new buffer from a matrix.
    /// The data is convert to the default type (see GetDefaultMatrixType()).
    ///
    /// note that if we use above VtValue taking constructor, we can use
    /// either float or double matrix regardless the default type.
    ///
    /// \param arraySize indicates how many values are provided per element.
    HD_API
    HdVtBufferSource(TfToken const &name, VtArray<GfMatrix4d> const &matrices,
                     int arraySize=1);

    /// Returns the default matrix type.
    /// The default is HdTypeFloatMat4, but if HD_ENABLE_DOUBLEMATRIX is true,
    /// then HdTypeDoubleMat4 is used instead.
    HD_API
    static HdType GetDefaultMatrixType();

    /// Destructor deletes the internal storage.
    HD_API
    ~HdVtBufferSource();

    /// Truncate the buffer to the given number of elements.
    /// If the VtValue contains too much data, this is a way to only forward
    /// part of the data to the hydra buffer system. numElements must be less
    /// than or equal to the current result of GetNumElements().
    HD_API
    void Truncate(size_t numElements);

    /// Return the name of this buffer source.
    virtual TfToken const &GetName() const override {
        return _name;
    }

    /// Returns the raw pointer to the underlying data.
    virtual void const* GetData() const override {
        return HdGetValueData(_value);
    }

    /// Returns the data type and count of this buffer source.
    virtual HdTupleType GetTupleType() const override {
        return _tupleType;
    }

    /// Returns the number of elements (e.g. VtVec3dArray().GetLength()) from
    /// the source array.
    HD_API
    virtual size_t GetNumElements() const override;

    /// Add the buffer spec for this buffer source into given bufferspec vector.
    virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override {
        specs->push_back(HdBufferSpec(_name, _tupleType));
    }

    /// Prepare the access of GetData().
    virtual bool Resolve() override {
        if (!_TryLock()) return false;

        // nothing. just marks as resolved, and returns _data in GetData()
        _SetResolved();
        return true;
    }

protected:
    HD_API
    virtual bool _CheckValid() const override;

private:
    // Constructor helper.
    void _SetValue(const VtValue &v, int arraySize);

    TfToken _name;

    // We hold the source value to avoid making unnecessary copies of the data: if
    // we immediately copy the source into a temporary buffer, we may need to
    // copy it again into an aggregate buffer later.
    //
    // We can elide this member easily with only a few internal changes, it
    // should never surface in the public API and for the same reason, this
    // class should remain noncopyable.
    VtValue _value;
    HdTupleType _tupleType;
    size_t _numElements;
};

/// Diagnostic output.
HD_API
std::ostream &operator <<(std::ostream &out, const HdVtBufferSource& self);

FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HD_VT_BUFFER_SOURCE_H
