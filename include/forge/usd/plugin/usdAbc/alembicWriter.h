#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/plugin/usdAbc/alembicWriter.h"
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
#ifndef FORGE_USD_PLUGIN_USD_ABC_ALEMBIC_WRITER_H
#define FORGE_USD_PLUGIN_USD_ABC_ALEMBIC_WRITER_H

/// \file usdAbc/alembicWriter.h

#include "forge/forge.h"
#include "forge/base/tf/staticTokens.h"
#include "forge/base/tf/declarePtrs.h"
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <set>
#include <string>

FORGE_NAMESPACE_BEGIN


// Note -- Even though this header is private we try to keep Alembic headers
//         out of it anyway for simplicity's sake.

TF_DECLARE_WEAK_AND_REF_PTRS(SdfAbstractData);

/// \class UsdAbc_AlembicDataWriter
///
/// An alembic writer suitable for an SdfAbstractData.
///
class UsdAbc_AlembicDataWriter : boost::noncopyable {
public:
    UsdAbc_AlembicDataWriter();
    ~UsdAbc_AlembicDataWriter();

    bool Open(const std::string& filePath, const std::string& comment);
    bool Write(const SdfAbstractDataConstPtr& data);
    bool Close();

    bool IsValid() const;
    std::string GetErrors() const;

    void SetFlag(const TfToken&, bool set = true);

private:
    boost::scoped_ptr<class UsdAbc_AlembicDataWriterImpl> _impl;
    std::string _errorLog;
};


FORGE_NAMESPACE_END

#endif
