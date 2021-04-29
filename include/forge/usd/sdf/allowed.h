#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/allowed.h"
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
#ifndef FORGE_USD_SDF_ALLOWED_H
#define FORGE_USD_SDF_ALLOWED_H

/// \file sdf/allowed.h

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/base/tf/diagnostic.h"

#include <string>
#include <utility>
#include <boost/operators.hpp>
#include <boost/optional.hpp>

FORGE_NAMESPACE_BEGIN

/// \class SdfAllowed
///
/// Indicates if an operation is allowed and, if not, why not.
///
/// A \c SdfAllowed either evaluates to \c true in a boolean context
/// or evaluates to \c false and has a string annotation.
///
class SdfAllowed : private boost::equality_comparable<SdfAllowed> {
private:
    typedef boost::optional<std::string> _State;

public:
    typedef std::pair<bool, std::string> Pair;

    /// Construct \c true.
    SdfAllowed() { }
    /// Construct \c true.
    SdfAllowed(bool x) { TF_AXIOM(x); }
    /// Construct \c false with annotation \p whyNot.
    SdfAllowed(const char* whyNot) : _state(std::string(whyNot)) { }
    /// Construct \c false with annotation \p whyNot.
    SdfAllowed(const std::string& whyNot) : _state(whyNot) { }
    /// Construct in \p condition with annotation \p whyNot if \c false.
    SdfAllowed(bool condition, const char* whyNot) :
        _state(!condition, std::string(whyNot)) { }
    /// Construct in \p condition with annotation \p whyNot if \c false.
    SdfAllowed(bool condition, const std::string& whyNot) :
        _state(!condition, whyNot) { }
    /// Construct from bool,string pair \p x.
    SdfAllowed(const Pair& x) : _state(!x.first, x.second) { }
    ~SdfAllowed() { }

#if !defined(doxygen)
    typedef _State SdfAllowed::*UnspecifiedBoolType;
#endif

    /// Returns \c true in a boolean context if allowed, \c false otherwise.
    operator UnspecifiedBoolType() const
    {
        return _state ? NULL : &SdfAllowed::_state;
    }

    /// Returns \c false in a boolean context if allowed, \c true otherwise.
    bool operator!() const
    {
        return static_cast<bool>(_state);
    }

    /// Returns the reason why the operation is not allowed.  If the
    /// operation is allowed this returns the empty string.
    operator const std::string&() const
    {
        return GetWhyNot();
    }

    /// Returns the reason why the operation is not allowed.  If the
    /// operation is allowed this returns the empty string.
    SDF_API const std::string& GetWhyNot() const;

    /// Returns \c true if allowed, otherwise fills \p whyNot if not \c NULL
    /// and returns \c false.
    bool IsAllowed(std::string* whyNot) const
    {
        if (whyNot && _state) {
            *whyNot = *_state;
        }
        return !_state;
    }

    /// Compare to \p other.  Returns \c true if both are \c true or
    /// both are \c false and reasons why not are identical.
    bool operator==(const SdfAllowed& other) const
    {
        return _state == other._state;
    }

private:
    _State _state;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_ALLOWED_H
