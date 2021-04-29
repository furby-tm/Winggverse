#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/children.h"
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
#ifndef FORGE_USD_SDF_CHILDREN_H
#define FORGE_USD_SDF_CHILDREN_H

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/sdf/path.h"

#include <boost/iterator/iterator_facade.hpp>
#include <vector>

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfLayer);
class SdfSpec;

/// \class Sdf_Children
///
/// Sdf_Children generically represents the children of an object. For
/// instance, it might be used for the name children of a prim or the
/// relationship targets of a relationship.
///
/// The provided ChildPolicy class determines how this object behaves.
/// It primarily specifies how to map between keys (such as the name of
/// an object) and values (such as SpecHandles for those objects).
///
template<class ChildPolicy>
class Sdf_Children
{
public:
    typedef typename ChildPolicy::KeyPolicy KeyPolicy;
    typedef typename ChildPolicy::KeyType KeyType;
    typedef typename ChildPolicy::ValueType ValueType;
    typedef typename ChildPolicy::FieldType FieldType;
    typedef Sdf_Children<ChildPolicy> This;

    SDF_API
    Sdf_Children();

    SDF_API
    Sdf_Children(const Sdf_Children<ChildPolicy> &other);

    SDF_API
    Sdf_Children(const SdfLayerHandle &layer,
        const SdfPath &parentPath, const TfToken &childrenKey,
        const KeyPolicy& keyPolicy = KeyPolicy());

    /// Return whether this object is valid.
    SDF_API
    bool IsValid() const;

    /// Return the number of children that this object contains.
    SDF_API
    size_t GetSize() const;

    /// Return the child at the specified index.
    SDF_API
    ValueType GetChild(size_t index) const;

    /// Find the index of the specified key, or return the size if it's not found.
    SDF_API
    size_t Find(const KeyType &key) const;

    /// Find the key that corresponds to \a value, or return a default
    /// constructed key if it's not found.
    SDF_API
    KeyType FindKey(const ValueType &value) const;

    /// Return true if this object and \a other are equivalent.
    SDF_API
    bool IsEqualTo(const This &other) const;

    /// Replace this object's children with the ones in \a values.
    SDF_API
    bool Copy(const std::vector<ValueType> & values, const std::string &type);

    /// Insert a new child at the specified \a index.
    SDF_API
    bool Insert(const ValueType& value, size_t index, const std::string &type);

    /// Erase the child with the specified key.
    SDF_API
    bool Erase(const KeyType& key, const std::string &type);

private:
    void _UpdateChildNames() const;

private:
    SdfLayerHandle _layer;
    SdfPath _parentPath;
    TfToken _childrenKey;
    KeyPolicy _keyPolicy;

    mutable std::vector<FieldType> _childNames;
    mutable bool _childNamesValid;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_CHILDREN_H
