#line 1 "C:/Users/tyler/dev/WINGG/forge/base/gf/line2d.h"
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
#ifndef FORGE_BASE_GF_LINE2D_H
#define FORGE_BASE_GF_LINE2D_H

/// \file gf/line2d.h
/// \ingroup group_gf_BasicGeometry

#include "forge/forge.h"
#include "forge/base/gf/vec2d.h"
#include "forge/base/gf/api.h"

#include <float.h>

FORGE_NAMESPACE_BEGIN

/// \class GfLine2d
/// \ingroup group_gf_BasicGeometry
///
/// Basic type: 2D line
///
/// This class represents a two-dimensional line in space.  Lines are
/// constructed from a point, \p p0, and a direction, dir.  The direction is
/// normalized in the constructor.
///
/// The line is kept in a parametric represention, p = p0 + t * dir.
///
class GfLine2d {

  public:

    /// The default constructor leaves line parameters undefined.
    GfLine2d() {
    }

    /// Construct a line from a point and a direction.
    GfLine2d(const GfVec2d &p0, const GfVec2d &dir ) {
        Set( p0, dir );
    }

    double Set(const GfVec2d &p0, const GfVec2d &dir ) {
        _p0 = p0;
        _dir = dir;
        return _dir.Normalize();
    }

    /// Return the point on the line at \p ( p0 + t * dir ).
    /// Remember dir has been normalized so t represents a unit distance.
    GfVec2d GetPoint( double t ) const { return _p0 + _dir * t; }

    /// Return the normalized direction of the line.
    const GfVec2d &GetDirection() const { return _dir; }

    /// Returns the point on the line that is closest to \p point. If \p t is
    /// not \c NULL, it will be set to the parametric distance along the line
    /// of the returned point.
    GF_API
    GfVec2d FindClosestPoint(const GfVec2d &point, double *t = NULL) const;

    /// Component-wise equality test. The starting points and directions, must
    /// match exactly for lines to be considered equal.
    bool		operator ==(const GfLine2d &l) const {
	return _p0 == l._p0 &&	_dir  == l._dir;
    }

    /// Component-wise inequality test. The starting points, and directions
    /// must match exactly for lines to be considered equal.
    bool		operator !=(const GfLine2d &r) const {
	return ! (*this == r);
    }

  private:
    GF_API
    friend bool GfFindClosestPoints( const GfLine2d &, const GfLine2d &,
                                     GfVec2d *, GfVec2d *,
                                     double *, double *);

    // Parametric description:
    //  l(t) = _p0 + t * _length * _dir;
    GfVec2d             _p0;
    GfVec2d             _dir;
};

/// Computes the closets points between two lines.
///
/// The two points are returned in \p p1 and \p p2.  The parametric distance
/// of each point on the lines is returned in \p t1 and \p t2.
///
/// This returns \c false if the lines were close enough to parallel that no
/// points could be computed; in this case, the other return values are
/// undefined.
GF_API
bool GfFindClosestPoints(const GfLine2d &l1, const GfLine2d &l2,
                         GfVec2d *p1 = nullptr, GfVec2d *p2 = nullptr,
                         double *t1 = nullptr, double *t2 = nullptr);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_GF_LINE2D_H
