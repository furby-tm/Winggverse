#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/scopeDescription.h"
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
#ifndef FORGE_BASE_TF_SCOPE_DESCRIPTION_H
#define FORGE_BASE_TF_SCOPE_DESCRIPTION_H

#include "forge/forge.h"

#include "forge/base/tf/callContext.h"
#include "forge/base/tf/preprocessorUtils.h"
#include "forge/base/tf/stringUtils.h"
#include "forge/base/tf/api.h"

#include <boost/optional.hpp>
#include <boost/preprocessor/if.hpp>

#include <vector>
#include <string>

FORGE_NAMESPACE_BEGIN

/// \class TfScopeDescription
///
/// This class is used to provide high-level descriptions about scopes of
/// execution that could possibly block, or to provide relevant information
/// about high-level action that would be useful in a crash report.
///
/// This class is reasonably fast to use, especially if the message strings are
/// not dynamically created, however it should not be used in very highly
/// performance sensitive contexts.  The cost to push & pop is essentially a TLS
/// lookup plus a couple of atomic operations.
class TfScopeDescription
{
    TfScopeDescription() = delete;
    TfScopeDescription(TfScopeDescription const &) = delete;
    TfScopeDescription &operator=(TfScopeDescription const &) = delete;
public:
    /// Construct with a description.  Push \a description on the stack of
    /// descriptions for this thread.  Caller guarantees that the string
    /// \p description lives at least as long as this TfScopeDescription object.
    TF_API explicit
    TfScopeDescription(std::string const &description,
                       TfCallContext const &context = TfCallContext());

    /// Construct with a description.  Push \a description on the stack of
    /// descriptions for this thread.  This object adopts ownership of the
    /// rvalue \p description.
    TF_API explicit
    TfScopeDescription(std::string &&description,
                       TfCallContext const &context = TfCallContext());

    /// Construct with a description.  Push \a description on the stack of
    /// descriptions for this thread.  Caller guarantees that the string
    /// \p description lives at least as long as this TfScopeDescription object.
    TF_API explicit
    TfScopeDescription(char const *description,
                       TfCallContext const &context = TfCallContext());

    /// Destructor.
    /// Pop the description stack in this thread.
    TF_API ~TfScopeDescription();

    /// Replace the description stack entry for this scope description.  Caller
    /// guarantees that the string \p description lives at least as long as this
    /// TfScopeDescription object.
    TF_API void SetDescription(std::string const &description);

    /// Replace the description stack entry for this scope description.  This
    /// object adopts ownership of the rvalue \p description.
    TF_API void SetDescription(std::string &&description);

    /// Replace the description stack entry for this scope description.  Caller
    /// guarantees that the string \p description lives at least as long as this
    /// TfScopeDescription object.
    TF_API void SetDescription(char const *description);

private:
    friend inline TfScopeDescription *
    Tf_GetPreviousScopeDescription(TfScopeDescription *d) {
        return d->_prev;
    }
    friend inline char const *
    Tf_GetScopeDescriptionText(TfScopeDescription *d) {
        return d->_description;
    }
    friend inline TfCallContext const &
    Tf_GetScopeDescriptionContext(TfScopeDescription *d) {
        return d->_context;
    }

    inline void _Push();
    inline void _Pop() const;

    boost::optional<std::string> _ownedString;
    char const *_description;
    TfCallContext _context;
    void *_localStack;
    TfScopeDescription *_prev; // link to parent scope.
};

/// Return a copy of the current description stack for the "main" thread as
/// identified by ArchGetMainThreadId() as a vector of strings.  The most
/// recently pushed description is at back(), and the least recently pushed
/// description is at front().
TF_API std::vector<std::string>
TfGetCurrentScopeDescriptionStack();

/// Return a copy of the current description stack for the current thread of
/// execution as a vector of strings.  The most recently pushed description is
/// at back(), and the least recently pushed description is at front().
TF_API std::vector<std::string>
TfGetThisThreadScopeDescriptionStack();

/// Macro that accepts either a single string, or printf-style arguments and
/// creates a scope description local variable with the resulting string.
#define TF_DESCRIBE_SCOPE(fmt, ...)                                            \
    TfScopeDescription __scope_description__                                   \
    (BOOST_PP_IF(TF_NUM_ARGS(__VA_ARGS__),                                     \
                 TfStringPrintf(fmt, __VA_ARGS__), fmt), TF_CALL_CONTEXT)

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_SCOPE_DESCRIPTION_H
