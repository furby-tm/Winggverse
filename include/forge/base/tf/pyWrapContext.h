#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyWrapContext.h"
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
#ifndef FORGE_BASE_TF_PY_WRAP_CONTEXT_H
#define FORGE_BASE_TF_PY_WRAP_CONTEXT_H

#include "forge/forge.h"

#include "forge/base/tf/singleton.h"

#include <boost/noncopyable.hpp>

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

// This is used internally by the Tf python wrapping infrastructure.

class Tf_PyWrapContextManager : public boost::noncopyable {

  public:

    typedef Tf_PyWrapContextManager This;

    static This &GetInstance() {
        return TfSingleton<This>::GetInstance();
    }

    std::string GetCurrentContext() const {
        return _contextStack.empty() ? std::string() : _contextStack.back();
    }

    void PushContext(std::string const &ctx) {
        _contextStack.push_back(ctx);
    }

    void PopContext() {
        _contextStack.pop_back();
    }

  private:

    Tf_PyWrapContextManager();

    friend class TfSingleton<This>;

    std::vector<std::string> _contextStack;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_WRAP_CONTEXT_H
