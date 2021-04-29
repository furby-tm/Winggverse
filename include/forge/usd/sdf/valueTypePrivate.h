#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/valueTypePrivate.h"
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
#ifndef FORGE_USD_SDF_VALUE_TYPE_PRIVATE_H
#define FORGE_USD_SDF_VALUE_TYPE_PRIVATE_H

#include "forge/forge.h"
#include "forge/usd/sdf/valueTypeName.h"
#include "forge/base/tf/enum.h"
#include "forge/base/tf/type.h"
#include "forge/base/vt/value.h"
#include <vector>

FORGE_NAMESPACE_BEGIN

class Sdf_ValueTypeImpl;

struct Sdf_ValueTypePrivate {
public:
    struct Empty { };

    // Represents a type/role pair.
    struct CoreType {
        CoreType() { }
        CoreType(Empty);

        TfType type;
        std::string cppTypeName;
        TfToken role;
        SdfTupleDimensions dim;
        VtValue value;
        TfEnum unit;

        // All type names aliasing this type/role pair in registration order.
        // The first alias is the "fundamental" type name.
        std::vector<TfToken> aliases;
    };

    /// Construct a SdfValueTypeName.
    static SdfValueTypeName MakeValueTypeName(const Sdf_ValueTypeImpl* impl);

    /// Return the value type implementation representing the empty type name.
    static const Sdf_ValueTypeImpl* GetEmptyTypeName();
};

/// Represents a registered type name.
class Sdf_ValueTypeImpl {
public:
    Sdf_ValueTypeImpl();

    const Sdf_ValueTypePrivate::CoreType* type;
    TfToken name;
    const Sdf_ValueTypeImpl* scalar;
    const Sdf_ValueTypeImpl* array;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_VALUE_TYPE_PRIVATE_H
