#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/timeCode.h"
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
#ifndef FORGE_USD_SDF_TIME_CODE_H
#define FORGE_USD_SDF_TIME_CODE_H

/// \file sdf/timeCode.h

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"

#include <algorithm>
#include <functional>
#include <iosfwd>

FORGE_NAMESPACE_BEGIN

/// \class SdfTimeCode
///
/// Value type that represents a time code. It's equivalent to a double type
/// value but is used to indicate that this value should be resolved by any
/// time based value resolution.
///
class SdfTimeCode
{
public:
    /// \name Constructors
    /// @{
    ///

    /// Construct a time code with the given time.
    /// A default constructed SdfTimeCode has a time of 0.0.
    /// A double value can implicitly cast to SdfTimeCode.
    constexpr SdfTimeCode(double time = 0.0) noexcept : _time(time) {};

    /// @}

    ///\name Operators
    /// @{

    constexpr bool operator==(const SdfTimeCode &rhs) const noexcept
        { return _time == rhs._time; }
    constexpr bool operator!=(const SdfTimeCode &rhs) const noexcept
        { return _time != rhs._time; }
    constexpr bool operator<(const SdfTimeCode &rhs) const noexcept
        { return _time < rhs._time; }
    constexpr bool operator>(const SdfTimeCode &rhs) const noexcept
        { return _time > rhs._time; }
    constexpr bool operator<=(const SdfTimeCode &rhs) const noexcept
        { return _time <= rhs._time; }
    constexpr bool operator>=(const SdfTimeCode &rhs) const noexcept
        { return _time >= rhs._time; }

    constexpr SdfTimeCode operator*(const SdfTimeCode &rhs) const noexcept
        { return SdfTimeCode(_time * rhs._time); }
    constexpr SdfTimeCode operator/(const SdfTimeCode &rhs) const noexcept
        { return SdfTimeCode(_time / rhs._time); }
    constexpr SdfTimeCode operator+(const SdfTimeCode &rhs) const noexcept
        { return SdfTimeCode(_time + rhs._time); }
    constexpr SdfTimeCode operator-(const SdfTimeCode &rhs) const noexcept
        { return SdfTimeCode(_time - rhs._time); }

    /// Explicit conversion to double
    explicit constexpr operator double() const noexcept {return _time;}

    /// Hash function
    size_t GetHash() const {
        return std::hash<double>()(_time);
    }

    /// \class Hash
    struct Hash
    {
        size_t operator()(const SdfTimeCode &ap) const {
            return ap.GetHash();
        }
    };

    friend size_t hash_value(const SdfTimeCode &ap) { return ap.GetHash(); }

    /// @}

    /// \name Accessors
    /// @{

    /// Return the time value.
    constexpr double GetValue() const noexcept {
        return _time;
    }

    /// @}

private:
    friend inline void swap(SdfTimeCode &lhs, SdfTimeCode &rhs) {
        std::swap(lhs._time, rhs._time);
    }

    double _time;
};

/// \name Related
/// Binary arithmetic and comparison operators with double valued lefthand side.
/// @{

inline constexpr
SdfTimeCode operator*(double time, const SdfTimeCode &timeCode) noexcept
    { return SdfTimeCode(time) * timeCode; }

inline constexpr
SdfTimeCode operator/(double time, const SdfTimeCode &timeCode) noexcept
    { return SdfTimeCode(time) / timeCode; }

inline constexpr
SdfTimeCode operator+(double time, const SdfTimeCode &timeCode) noexcept
    { return SdfTimeCode(time) + timeCode; }

inline constexpr
SdfTimeCode operator-(double time, const SdfTimeCode &timeCode) noexcept
    { return SdfTimeCode(time) - timeCode; }

inline constexpr
bool operator==(double time, const SdfTimeCode &timeCode) noexcept
    { return SdfTimeCode(time) == timeCode; }

inline constexpr
bool operator!=(double time, const SdfTimeCode &timeCode) noexcept
    { return SdfTimeCode(time) != timeCode; }

inline constexpr
bool operator<(double time, const SdfTimeCode &timeCode) noexcept
    { return SdfTimeCode(time) < timeCode; }

inline constexpr
bool operator>(double time, const SdfTimeCode &timeCode) noexcept
    { return SdfTimeCode(time) > timeCode; }

inline constexpr
bool operator<=(double time, const SdfTimeCode &timeCode) noexcept
    { return SdfTimeCode(time) <= timeCode; }

inline constexpr
bool operator>=(double time, const SdfTimeCode &timeCode) noexcept
    { return SdfTimeCode(time) >= timeCode; }

/// Stream insertion operator for the string representation of this time code.
SDF_API std::ostream& operator<<(std::ostream& out, const SdfTimeCode& ap);

/// @}

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_TIME_CODE_H
