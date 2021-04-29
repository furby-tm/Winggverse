#line 1 "C:/Users/tyler/dev/WINGG/forge/base/gf/quatd.h"
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
////////////////////////////////////////////////////////////////////////
// This file is generated by a script.  Do not edit directly.  Edit the
// quat.template.h file to make changes.

#ifndef FORGE_BASE_GF_QUATD_H
#define FORGE_BASE_GF_QUATD_H

/// \file gf/quatd.h
/// \ingroup group_gf_LinearAlgebra

#include "forge/forge.h"
#include "forge/base/gf/api.h"
#include "forge/base/gf/declare.h"
#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/traits.h"

#include <boost/functional/hash.hpp>

#include <iosfwd>

FORGE_NAMESPACE_BEGIN

template <>
struct GfIsGfQuat<class GfQuatd> { static const bool value = true; };


/// Return the dot (inner) product of two quaternions.
double GfDot(const GfQuatd& q1, const GfQuatd& q2);


/// \class GfQuatd
/// \ingroup group_gf_LinearAlgebra
///
/// Basic type: a quaternion, a complex number with a real coefficient and
/// three imaginary coefficients, stored as a 3-vector.
///
class GfQuatd
{
  public:
    typedef double ScalarType;
    typedef GfVec3d ImaginaryType;

    /// Default constructor leaves the quaternion undefined.
    GfQuatd() {}

    /// Initialize the real coefficient to \p realVal and the imaginary
    /// coefficients to zero.
    ///
    /// Since quaternions typically must be normalized, reasonable values for
    /// \p realVal are -1, 0, or 1.  Other values are legal but are likely to
    /// be meaningless.
    ///
    explicit GfQuatd (double realVal) : _imaginary(0), _real(realVal) {}

    /// Initialize the real and imaginary coefficients.
    GfQuatd(double real, double i, double j, double k)
        : _imaginary(i, j, k), _real(real)
    {
    }

    /// Initialize the real and imaginary coefficients.
    GfQuatd(double real, const GfVec3d &imaginary)
        : _imaginary(imaginary), _real(real)
    {
    }

    /// Implicitly convert from GfQuatf.
    GF_API
    GfQuatd(class GfQuatf const &other);
    /// Implicitly convert from GfQuath.
    GF_API
    GfQuatd(class GfQuath const &other);

    /// Return the identity quaternion, with real coefficient 1 and an
    /// imaginary coefficients all zero.
    static GfQuatd GetIdentity() { return GfQuatd(1.0); }

    /// Return the real coefficient.
    double GetReal() const { return _real; }

    /// Set the real coefficient.
    void SetReal(double real) { _real = real; }

    /// Return the imaginary coefficient.
    const GfVec3d &GetImaginary() const { return _imaginary; }

    /// Set the imaginary coefficients.
    void SetImaginary(const GfVec3d &imaginary) {
        _imaginary = imaginary;
    }

    /// Set the imaginary coefficients.
    void SetImaginary(double i, double j, double k) {
        _imaginary.Set(i, j, k);
    }

    /// Return geometric length of this quaternion.
    double GetLength() const { return GfSqrt(_GetLengthSquared()); }

    /// length of this quaternion is smaller than \p eps, return the identity
    /// quaternion.
    GfQuatd
    GetNormalized(double eps = GF_MIN_VECTOR_LENGTH) const {
        GfQuatd ret(*this);
        ret.Normalize(eps);
        return ret;
    }

    /// Normalizes this quaternion in place to unit length, returning the
    /// length before normalization. If the length of this quaternion is
    /// smaller than \p eps, this sets the quaternion to identity.
    GF_API
    double Normalize(double eps = GF_MIN_VECTOR_LENGTH);

    /// Return this quaternion's conjugate, which is the quaternion with the
    /// same real coefficient and negated imaginary coefficients.
    GfQuatd GetConjugate() const {
        return GfQuatd(GetReal(), -GetImaginary());
    }

    /// Return this quaternion's inverse, or reciprocal.  This is the
    /// quaternion's conjugate divided by it's squared length.
    GfQuatd GetInverse() const {
        return GetConjugate() / _GetLengthSquared();
    }

    /// Transform the GfVec3d point. If the quaternion is normalized,
    /// the transformation is a rotation. Given a GfQuatd q, q.Transform(point)
    /// is equivalent to:
    ///
    ///     (q * GfQuatd(0, point) * q.GetInverse()).GetImaginary()
    ///
    /// but is more efficient.
    GF_API
    GfVec3d Transform(const GfVec3d& point) const;

    /// Hash.
    friend inline size_t hash_value(const GfQuatd &q) {
        size_t h = boost::hash<ScalarType>()(q.GetReal());
        boost::hash_combine(h, q.GetImaginary());
        return h;
    }

    /// Component-wise negation.
    GfQuatd operator-() const {
        return GfQuatd(-GetReal(), -GetImaginary());
    }

    /// Component-wise quaternion equality test. The real and imaginary parts
    /// must match exactly for quaternions to be considered equal.
    bool operator==(const GfQuatd &q) const {
        return (GetReal() == q.GetReal() &&
                GetImaginary() == q.GetImaginary());
    }

    /// Component-wise quaternion inequality test. The real and imaginary
    /// parts must match exactly for quaternions to be considered equal.
    bool operator!=(const GfQuatd &q) const {
        return !(*this == q);
    }

    /// Post-multiply quaternion \p q into this quaternion.
    GF_API
    GfQuatd &operator *=(const GfQuatd &q);

    /// Multiply this quaternion's coefficients by \p s.
    GfQuatd &operator *=(double s) {
        _real *= s;
        _imaginary *= s;
        return *this;
    }

    /// Divide this quaternion's coefficients by \p s.
    GfQuatd &operator /=(double s) {
        _real /= s;
        _imaginary /= s;
        return *this;
    }

    /// Add quaternion \p q to this quaternion.
    GfQuatd &operator +=(const GfQuatd &q) {
        _real += q._real;
        _imaginary += q._imaginary;
        return *this;
    }

    /// Component-wise unary difference operator.
    GfQuatd &operator -=(const GfQuatd &q)  {
        _real -= q._real;
        _imaginary -= q._imaginary;
        return *this;
    }

    /// Component-wise binary sum operator.
    friend GfQuatd
    operator +(const GfQuatd &q1, const GfQuatd &q2) {
        return GfQuatd(q1) += q2;
    }

    /// Component-wise binary difference operator.
    friend GfQuatd
    operator -(const GfQuatd &q1, const GfQuatd &q2) {
        return GfQuatd(q1) -= q2;
    }

    /// Returns the product of quaternions \p q1 and \p q2.
    friend GfQuatd
    operator *(const GfQuatd &q1, const GfQuatd &q2) {
        return GfQuatd(q1) *= q2;
    }

    /// Returns the product of quaternion \p q and scalar \p s.
    friend GfQuatd
    operator *(const GfQuatd &q, double s) {
        return GfQuatd(q) *= s;
    }

    /// Returns the product of quaternion \p q and scalar \p s.
    friend GfQuatd
    operator *(double s, const GfQuatd &q) {
        return GfQuatd(q) *= s;
    }

    /// Returns the product of quaternion \p q and scalar 1 / \p s.
    friend GfQuatd
    operator /(const GfQuatd &q, double s) {
        return GfQuatd(q) /= s;
    }

  private:
    /// Imaginary part
    GfVec3d _imaginary;

    /// Real part
    double _real;

    /// Returns the square of the length
    double
    _GetLengthSquared() const {
        return GfDot(*this, *this);
    }
};

/// Spherically linearly interpolate between \p q0 and \p q1.
///
/// If the interpolant \p alpha is zero, then the result is \p q0, while
/// \p alpha of one yields \p q1.
GF_API GfQuatd
GfSlerp(double alpha, const GfQuatd& q0, const GfQuatd& q1);

GF_API GfQuatd
GfSlerp(const GfQuatd& q0, const GfQuatd& q1, double alpha);

inline double
GfDot(GfQuatd const &q1, GfQuatd const &q2) {
    return GfDot(q1.GetImaginary(), q2.GetImaginary()) +
                 q1.GetReal()*q2.GetReal();
}

/// Output a GfQuatd using the format (re, i, j, k)
/// \ingroup group_gf_DebuggingOutput
GF_API std::ostream& operator<<(std::ostream &, GfQuatd const &);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_GF_QUATD_H