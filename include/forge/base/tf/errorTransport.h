#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/errorTransport.h"
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
#ifndef FORGE_BASE_TF_ERROR_TRANSPORT_H
#define FORGE_BASE_TF_ERROR_TRANSPORT_H

/// \file tf/errorTransport.h

#include "forge/forge.h"
#include "forge/base/tf/diagnosticMgr.h"
#include "forge/base/arch/hints.h"
#include "forge/base/tf/api.h"

FORGE_NAMESPACE_BEGIN

/// \class TfErrorTransport
///
/// A facility for transporting errors from thread to thread.
///
/// Typical use is to create a TfErrorMark in the thread that is the error
/// source (e.g. the child thread), then call TfErrorMark::Transport() or
/// TfErrorMark::TransportTo() to lift generated errors out into a
/// TfErrorTransport object.  Later the thread that wants to sink those errors
/// (e.g. the parent thread) invokes TfErrorTransport::Post() to post all
/// contained errors to its own thread's error list.
class TfErrorTransport
{
public:
    typedef TfDiagnosticMgr::ErrorList ErrorList;

    /// Construct an empty TfErrorTransport.
    TfErrorTransport() {}

    /// Post all contained errors to the current thread's error list, leaving
    /// this TfErrorTransport empty.
    void Post() {
        if (ARCH_UNLIKELY(!IsEmpty()))
            _PostImpl();
    }

    /// Return true if this TfErrorTransport contains no errors, false
    /// otherwise.
    bool IsEmpty() const { return _errorList.empty(); }

    /// Swap this TfErrorTransport's content with \p other.  This provides a
    /// lightweight way to move the contents of one TfErrorTransport to
    /// another.
    void swap(TfErrorTransport &other) {
        _errorList.swap(other._errorList);
    }

private:
    friend class TfErrorMark;

    TfErrorTransport(ErrorList &src,
                     ErrorList::iterator first,
                     ErrorList::iterator last) {
        _errorList.splice(_errorList.begin(), src, first, last);
    }

    TF_API
    void _PostImpl();

    ErrorList _errorList;
};

inline void
swap(TfErrorTransport &l, TfErrorTransport &r)
{
    l.swap(r);
}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_ERROR_TRANSPORT_H
