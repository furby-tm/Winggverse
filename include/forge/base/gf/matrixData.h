#line 1 "C:/Users/tyler/dev/WINGG/forge/base/gf/matrixData.h"
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
#ifndef FORGE_BASE_GF_MATRIX_DATA_H
#define FORGE_BASE_GF_MATRIX_DATA_H

#include "forge/forge.h"
#include "forge/base/gf/api.h"

FORGE_NAMESPACE_BEGIN

/// \class GfMatrixData
///
/// A class template used by GfMatrixXX to store values.
template <class T, int Rows, int Columns>
class GfMatrixData {
public:

    /// Return a pointer to a \a row of data.
    T *operator[](int row) {
        return _data + (row * Columns);
    }

    /// Return a const pointer to a \a row of data.
    T const *operator[](int row) const {
        return _data + (row * Columns);
    }

    /// Return a pointer to the start of all the data.
    T *GetData() {
        return _data;
    }

    /// Return a const pointer to the start of all the data.
    T const *GetData() const {
        return _data;
    }

private:

    T _data[Rows * Columns];
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_GF_MATRIX_DATA_H
