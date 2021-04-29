#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdSkel/animMapper.h"
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
#ifndef FORGE_USD_USD_SKEL_ANIM_MAPPER_H
#define FORGE_USD_USD_SKEL_ANIM_MAPPER_H

/// \file usdSkel/animMapper.h

#include "forge/forge.h"
#include "forge/usd/usdSkel/api.h"

#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/matrix4f.h"
#include "forge/base/tf/span.h"
#include "forge/base/vt/array.h"
#include "forge/usd/sdf/types.h"

#include <type_traits>
#include <vector>


FORGE_NAMESPACE_BEGIN


using UsdSkelAnimMapperRefPtr = std::shared_ptr<class UsdSkelAnimMapper>;


/// \class UsdSkelAnimMap
///
/// Helper class for remapping vectorized animation data from
/// one ordering of tokens to another.
class UsdSkelAnimMapper {
public:
    /// Construct a null mapper.
    USDSKEL_API
    UsdSkelAnimMapper();

    /// Construct an identity mapper for remapping a range of \p size elems.
    /// An identity mapper is used to indicate that no remapping is required.
    USDSKEL_API
    UsdSkelAnimMapper(size_t size);

    /// Construct a mapper for mapping data from \p sourceOrder to
    /// \p targetOrder.
    USDSKEL_API
    UsdSkelAnimMapper(const VtTokenArray& sourceOrder,
                      const VtTokenArray& targetOrder);

    /// Construct a mapper for mapping data from \p sourceOrder to
    /// \p targetOrder, each being arrays of size \p sourceOrderSize
    /// and \p targetOrderSize, respectively.
    USDSKEL_API
    UsdSkelAnimMapper(const TfToken* sourceOrder, size_t sourceOrderSize,
                      const TfToken* targetOrder, size_t targetOrderSize);

    /// Typed remapping of data in an arbitrary, stl-like container.
    /// The \p source array provides a run of \p elementSize for each path in
    /// the \\em sourceOrder. These elements are remapped and copied over the
    /// \p target array.
    /// Prior to remapping, the \p target array is resized to the size of the
    /// \\em targetOrder (as given at mapper construction time) multiplied by
    /// the \p elementSize. New element created in the array are initialized
    /// to \p defaultValue, if provided.
    template <typename Container>
    bool Remap(const Container& source,
               Container* target,
               int elementSize=1,
               const typename Container::value_type*
                   defaultValue=nullptr) const;

    /// Type-erased remapping of data from \p source into \p target.
    /// The \p source array provides a run of \p elementSize elements for each
    /// path in the \\em sourceOrder. These elements are remapped and copied
    /// over the \p target array.
    /// Prior to remapping, the \p target array is resized to the size of the
    /// \\em targetOrder (as given at mapper construction time) multiplied by
    /// the \p elementSize. New elements created in the array are initialized
    /// to \p defaultValue, if provided.
    /// Remapping is supported for registered Sdf array value types only.
    USDSKEL_API
    bool Remap(const VtValue& source, VtValue* target,
               int elementSize=1, const VtValue& defaultValue=VtValue()) const;

    /// Convenience method for the common task of remapping transform arrays.
    /// This performs the same operation as Remap(), but sets the matrix
    /// identity as the default value.
    template <typename Matrix4>
    USDSKEL_API
    bool RemapTransforms(const VtArray<Matrix4>& source,
                         VtArray<Matrix4>* target,
                         int elementSize=1) const;

    /// Returns true if this is an identity map.
    /// The source and target orders of an identity map are identical.
    USDSKEL_API
    bool IsIdentity() const;

    /// Returns true if this is a sparse mapping.
    /// A sparse mapping means that not all target values will be overridden
    /// by source values, when mapped with Remap().
    USDSKEL_API
    bool IsSparse() const;

    /// Returns true if this is a null mapping.
    /// No source elements of a null map are mapped to the target.
    USDSKEL_API
    bool IsNull() const;

    /// Get the size of the output array that this mapper expects to
    /// map data into.
    USDSKEL_API
    size_t size() const { return _targetSize; }

    bool operator==(const UsdSkelAnimMapper& o) const;

    bool operator!=(const UsdSkelAnimMapper& o) const {
        return !(*this == o);
    }

private:

    template <typename T>
    bool _UntypedRemap(const VtValue& source, VtValue* target,
                       int elementSize, const VtValue& defaultValue) const;

    template <typename T>
    static void _ResizeContainer(VtArray<T>* array,
                                 size_t size,
                                 const T& defaultValue);

    template <typename Container>
    static void _ResizeContainer(
        Container* container,
        size_t size,
        const typename Container::value_type& defaultValue,
        typename std::enable_if<
            !VtIsArray<Container>::value,
            Container>::type* = 0)
        { container->resize(size, defaultValue); }

    USDSKEL_API
    bool _IsOrdered() const;

    /// Size of the output map.
    size_t _targetSize;

    /// For ordered mappings, an offset into the output array at which
    /// to map the source data.
    size_t _offset;

    /// For unordered mappings, an index map, mapping from source
    /// indices to target indices.
    VtIntArray _indexMap;
    int _flags;
};


template <typename T>
void
UsdSkelAnimMapper::_ResizeContainer(VtArray<T>* array, size_t size,
                                    const T& defaultValue)
{
    // XXX: VtArray::resize() doesn't take an default value atm.
    // We should fix this...
    const size_t prevSize = array->size();
    array->resize(size);
    auto span = TfMakeSpan(*array);
    for(size_t i = prevSize; i < size; ++i) {
        span[i] = defaultValue;
    }
}


template <typename Container>
bool
UsdSkelAnimMapper::Remap(const Container& source,
                         Container* target,
                         int elementSize,
                         const typename Container::value_type* defaultValue) const
{
    using _ValueType = typename Container::value_type;

    if (!target) {
        TF_CODING_ERROR("'target' is null");
        return false;
    }
    if (elementSize <= 0) {
        TF_WARN("Invalid elementSize [%d]: "
                "size must be greater than zero.", elementSize);
        return false;
    }

    const size_t targetArraySize = _targetSize*elementSize;

    if (IsIdentity() && source.size() == targetArraySize) {
        // Can make copy of the array.
        *target = source;
        return true;
    }

    // Resize the target array to the expected size.
    _ResizeContainer(target, targetArraySize,
                     defaultValue ? *defaultValue : _ValueType());

    if (IsNull()) {
        return true;
    } else if (_IsOrdered()) {

        size_t copyCount =
            std::min(source.size(), targetArraySize - _offset*elementSize);
        std::copy(source.cdata(), source.cdata()+copyCount,
                  target->data() + _offset*elementSize);
    } else {

        const _ValueType* sourceData = source.cdata();

        _ValueType* targetData = target->data();
        size_t copyCount = std::min(source.size()/elementSize,
                                    _indexMap.size());

        const int* indexMap = _indexMap.data();

        for (size_t i = 0; i < copyCount; ++i) {
            int targetIdx = indexMap[i];
            if (targetIdx >= 0 &&
                    static_cast<size_t>(targetIdx) < target->size()) {
                TF_DEV_AXIOM(i*elementSize < source.size());
                TF_DEV_AXIOM((i+1)*elementSize <= source.size());
                TF_DEV_AXIOM(static_cast<size_t>((targetIdx+1)*elementSize)
                                <= target->size());
                std::copy(sourceData + i*elementSize,
                          sourceData + (i+1)*elementSize,
                          targetData + targetIdx*elementSize);
            }
        }
    }
    return true;
}


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_SKEL_ANIM_MAPPER_H
