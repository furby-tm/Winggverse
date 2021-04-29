#line 1 "C:/Users/tyler/dev/WINGG/forge/base/gf/rotation.h"
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
#ifndef FORGE_BASE_GF_ROTATION_H
#define FORGE_BASE_GF_ROTATION_H

/// \file gf/rotation.h
/// \ingroup group_gf_LinearAlgebra

#include "forge/forge.h"
#include "forge/base/gf/quaternion.h"
#include "forge/base/gf/quatd.h"
#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/api.h"

#include <boost/functional/hash.hpp>

#include <iosfwd>

FORGE_NAMESPACE_BEGIN

/// \class GfRotation
/// \ingroup group_gf_LinearAlgebra
///
/// Basic type: 3-space rotation specification.
///
/// This class represents a rotation in 3-space. This stores an axis as a
/// normalized vector of 3 \c doubles and an angle in degrees (as a double).
/// Rotations follow the right-hand rule: a positive rotation about an axis
/// vector appears counter-clockwise when looking from the end of the vector
/// toward the origin.
///
class GfRotation {

  public:

    /// The default constructor leaves the rotation undefined.
    GfRotation() {
    }

    /// This constructor initializes the rotation to be \p angle
    /// degrees about \p axis.
    GfRotation(const GfVec3d &axis, double angle) {
        SetAxisAngle(axis, angle);
    }

    /// This constructor initializes the rotation from a quaternion.
    GfRotation(const GfQuaternion &quaternion) {
        SetQuaternion(quaternion);
    }

    /// This constructor initializes the rotation from a quaternion.  Note that
    /// this constructor accepts GfQuatf and GfQuath since they implicitly
    /// convert to GfQuatd.
    GfRotation(const GfQuatd &quat) { SetQuat(quat); }

    /// This constructor initializes the rotation to one that brings
    /// the \p rotateFrom vector to align with \p rotateTo. The passed
    /// vectors need not be unit length.
    GF_API
    GfRotation(const GfVec3d &rotateFrom, const GfVec3d &rotateTo) {
        SetRotateInto(rotateFrom, rotateTo);
    }

    /// Sets the rotation to be \p angle degrees about \p axis.
    GfRotation &        SetAxisAngle(const GfVec3d &axis, double angle) {
        _axis = axis;
        _angle = angle;
        if (!GfIsClose(_axis * _axis, 1.0, 1e-10))
            _axis.Normalize();
        return *this;
    }

    /// Sets the rotation from a quaternion.  Note that this method accepts
    /// GfQuatf and GfQuath since they implicitly convert to GfQuatd.
    GF_API
    GfRotation &        SetQuat(const GfQuatd &quat);

    /// Sets the rotation from a quaternion.
    GfRotation &        SetQuaternion(const GfQuaternion &quat) {
        return SetQuat(GfQuatd(quat.GetReal(), quat.GetImaginary()));
    }

    /// Sets the rotation to one that brings the \p rotateFrom vector
    /// to align with \p rotateTo. The passed vectors need not be unit
    /// length.
    GF_API
    GfRotation &        SetRotateInto(const GfVec3d &rotateFrom,
                                      const GfVec3d &rotateTo);

    /// Sets the rotation to an identity rotation.
    /// (This is chosen to be 0 degrees around the positive X axis.)
    GfRotation &        SetIdentity() {
        _axis.Set(1.0, 0.0, 0.0);
        _angle = 0.0;
        return *this;
    }

    /// Returns the axis of rotation.
    const GfVec3d &     GetAxis() const {
        return _axis;
    }

    /// Returns the rotation angle in degrees.
    double              GetAngle() const {
        return _angle;
    }

    /// Returns the rotation expressed as a quaternion.
    GfQuaternion        GetQuaternion() const {
        auto quat = GetQuat();
        return GfQuaternion(quat.GetReal(), quat.GetImaginary());
    }

    /// Returns the rotation expressed as a quaternion.
    GF_API
    GfQuatd             GetQuat() const;

    /// Returns the inverse of this rotation.
    GfRotation          GetInverse() const {
        return GfRotation(_axis, -_angle);
    }

    /// Decompose rotation about 3 orthogonal axes.
    /// If the axes are not orthogonal, warnings will be spewed.
    GF_API
    GfVec3d Decompose( const GfVec3d &axis0,
                       const GfVec3d &axis1,
                       const GfVec3d &axis2 ) const;

    // Full-featured method to  Decompose a rotation matrix into Cardarian
    // angles.
    // Axes have must be normalized. If useHint is specified
    // then the current values stored within thetaTw, thetaFB, thetaLR,
    // and thetaSw will be treated as hint and  used to help choose
    // an equivalent rotation that is as close as possible to the hints.
    //
    // One can use this routine to generate any combination of the three
    // angles by passing in NULL for the angle that is to be omitted.
    //
    // Passing in valid pointers for all four angles will decompose into
    // Tw, FB, and LR but allows Sw to be used for best matching of hint
    // values.  It also allows an swShift value to be passed in as a
    // Sw that is applied after the rotation matrix to get a best fit rotation
    // in four angles.
    //
    // Angles are in radians.
    //
    // Specify \p handedness as -1.0 or 1.0, same as for MultiRotate.
    //
    // NOTE:
    // Geppetto math function Originally brought over to extMover
    // from //depot/main/tools/src/menv/lib/gpt/util.h [10/16/06]
    // And moved into GfRotation[12/1/08].  Updated for any
    // combination of three angles [12/1/11].
    //
    GF_API
    static void DecomposeRotation(const GfMatrix4d &rot,
                                  const GfVec3d &TwAxis,
                                  const GfVec3d &FBAxis,
                                  const GfVec3d &LRAxis,
                                  double handedness,
                                  double *thetaTw,
                                  double *thetaFB,
                                  double *thetaLR,
                                  double *thetaSw = NULL,
                                  bool   useHint=false,
                                  const double *swShift=NULL);

    // This function projects the vectors \p v1 and \p v2 onto the plane
    // normal to \p axis, and then returns the rotation about \p axis that
    // brings \p v1 onto \p v2.
    GF_API
    static GfRotation RotateOntoProjected(const GfVec3d &v1,
                                          const GfVec3d &v2,
                                          const GfVec3d &axis);

    /// Transforms row vector \p vec by the rotation, returning the result.
    GF_API
    GfVec3f TransformDir( const GfVec3f &vec ) const;

    /// \overload
    GF_API
    GfVec3d TransformDir( const GfVec3d &vec ) const;

    /// Hash.
    friend inline size_t hash_value(const GfRotation &r) {
        size_t h = 0;
        boost::hash_combine(h, r._axis);
        boost::hash_combine(h, r._angle);
        return h;
    }

    /// Component-wise rotation equality test. The axes and angles must match
    /// exactly for rotations to be considered equal. (To compare equality of
    /// the actual rotations, you can convert both to quaternions and test the
    /// results for equality.)
    bool        operator ==(const GfRotation &r) const {
        return (_axis  == r._axis &&
            _angle == r._angle);
    }

    /// Component-wise rotation inequality test. The axes and angles must
    /// match exactly for rotations to be considered equal. (To compare
    /// equality of the actual rotations, you can convert both to quaternions
    /// and test the results for equality.)
    bool        operator !=(const GfRotation &r) const {
        return ! (*this == r);
    }

    /// Post-multiplies rotation \p r into this rotation.
    GF_API
    GfRotation &        operator *=(const GfRotation &r);

    /// Scales rotation angle by multiplying by \p scale.
    GfRotation &        operator *=(double scale) {
        _angle *= scale;
        return *this;
    }

    /// Scales rotation angle by dividing by \p scale.
    GfRotation &    operator /=(double scale) {
        _angle /= scale;
        return *this;
    }

    /// Returns composite rotation of rotations \p r1 and \p r2.
    friend GfRotation   operator *(const GfRotation &r1,
                   const GfRotation &r2) {
        GfRotation r  = r1;
        return     r *= r2;
    }

    /// Returns a rotation equivalent to \p r with its angle multiplied
    /// by \p scale.
    friend GfRotation   operator *(const GfRotation &r, double scale) {
        GfRotation rTmp  = r;
        return     rTmp *= scale;
    }

    /// Returns a rotation equivalent to \p r with its angle multiplied
    /// by \p scale.
    friend GfRotation   operator *(double scale, const GfRotation &r) {
        return (r * scale);
    }

    /// Returns a rotation equivalent to \p r with its angle divided
    /// by \p scale.
    friend GfRotation   operator /(const GfRotation &r, double scale) {
        GfRotation rTmp  = r;
        return     rTmp /= scale;
    }

  private:
    /// Axis storage.
    /// This axis is normalized to unit length whenever it is set.
    GfVec3d     _axis;
    /// Angle storage (represented in degrees).
    double      _angle;
};

/// Output a GfRotation using the format [(x y z) a].
/// \ingroup group_gf_DebuggingOutput
GF_API std::ostream& operator<<(std::ostream&, const GfRotation&);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_GF_ROTATION_H