#line 1 "C:/Users/tyler/dev/WINGG/forge/base/plug/testPlugBase.h"
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
#ifndef FORGE_BASE_PLUG_TEST_PLUG_BASE_H
#define FORGE_BASE_PLUG_TEST_PLUG_BASE_H

#include "forge/forge.h"
#include "forge/base/plug/api.h"
#include "forge/base/tf/refBase.h"
#include "forge/base/tf/stringUtils.h"
#include "forge/base/tf/type.h"
#include "forge/base/tf/weakBase.h"

#include <string>

FORGE_NAMESPACE_BEGIN

template <int M>
class _TestPlugBase : public TfRefBase, public TfWeakBase {
  public:
    typedef _TestPlugBase This;
    typedef TfRefPtr<This> RefPtr;
    typedef TfWeakPtr<This> Ptr;
    constexpr static int N = M;

    virtual ~_TestPlugBase() {}

    virtual std::string GetTypeName() {
        return TfType::Find(this).GetTypeName();
    }

    static RefPtr New() {
        return TfCreateRefPtr(new This());
    }

    PLUG_API
    static RefPtr Manufacture(const std::string & subclass);

  protected:
    _TestPlugBase() {}
};

template <int N>
class _TestPlugFactoryBase : public TfType::FactoryBase {
public:
    virtual TfRefPtr<_TestPlugBase<N> > New() const = 0;
};

template <typename T>
class _TestPlugFactory : public _TestPlugFactoryBase<T::N> {
public:
    virtual TfRefPtr<_TestPlugBase<T::N> > New() const
    {
        return T::New();
    }
};

typedef _TestPlugBase<1> _TestPlugBase1;
typedef _TestPlugBase<2> _TestPlugBase2;
typedef _TestPlugBase<3> _TestPlugBase3;
typedef _TestPlugBase<4> _TestPlugBase4;

FORGE_NAMESPACE_END

#endif // FORGE_BASE_PLUG_TEST_PLUG_BASE_H
