#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/attributeQuery.h"
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
#ifndef FORGE_USD_USD_ATTRIBUTE_QUERY_H
#define FORGE_USD_USD_ATTRIBUTE_QUERY_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/usd/attribute.h"
#include "forge/usd/usd/common.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/resolveInfo.h"
#include "forge/usd/usd/timeCode.h"

#include "forge/base/tf/token.h"

#include <vector>

FORGE_NAMESPACE_BEGIN


/// \class UsdAttributeQuery
///
/// Object for efficiently making repeated queries for attribute values.
///
/// Retrieving an attribute's value at a particular time requires determining
/// the source of strongest opinion for that value.  Often (i.e.  unless the
/// attribute is affected by \ref Usd_Page_ValueClips "Value Clips") this
/// source does not vary over time.  UsdAttributeQuery uses this fact to
/// speed up repeated value queries by caching the source information for an
/// attribute.  It is safe to use a UsdAttributeQuery for any attribute - if
/// the attribute \em is affected by Value Clips, the performance gain will
/// just be less.
///
/// \section Thread safety
/// This object provides the basic thread-safety guarantee.  Multiple threads
/// may call the value accessor functions simultaneously.
///
/// \section Invalidation
/// This object does not listen for change notification.  If a consumer is
/// holding on to a UsdAttributeQuery, it is their responsibility to dispose
/// of it in response to a resync change to the associated attribute.
/// Failing to do so may result in incorrect values or crashes due to
/// dereferencing invalid objects.
///
class UsdAttributeQuery
{
public:
    /// Construct an invalid query object.
    USD_API
    UsdAttributeQuery();

    /// Construct a new query for the attribute \p attr.
    USD_API
    explicit UsdAttributeQuery(const UsdAttribute& attr);

    /// Construct a new query for the attribute named \p attrName under
    /// the prim \p prim.
    USD_API
    UsdAttributeQuery(const UsdPrim& prim, const TfToken& attrName);

    /// Construct new queries for the attributes named in \p attrNames under
    /// the prim \p prim. The objects in the returned vector will line up
    /// 1-to-1 with \p attrNames.
    USD_API
    static std::vector<UsdAttributeQuery> CreateQueries(
        const UsdPrim& prim, const TfTokenVector& attrNames);

    // --------------------------------------------------------------------- //
    /// \name Query information
    // --------------------------------------------------------------------- //

    /// @{

    /// Return the attribute associated with this query.
    USD_API
    const UsdAttribute& GetAttribute() const;

    /// Return true if this query is valid (i.e. it is associated with a
    /// valid attribute), false otherwise.
    bool IsValid() const {
        return GetAttribute().IsValid();
    }

public:
    /// Returns \c true if the query object is valid, \c false otherwise.
    explicit operator bool() const {
        return IsValid();
    }

    /// @}

    // --------------------------------------------------------------------- //
    /// \name Value & Time-Sample Accessors
    // --------------------------------------------------------------------- //

    /// @{

    /// Perform value resolution to fetch the value of the attribute associated
    /// with this query at the requested UsdTimeCode \p time.
    ///
    /// \sa UsdAttribute::Get
    template <typename T>
    bool Get(T* value, UsdTimeCode time = UsdTimeCode::Default()) const {
        static_assert(SdfValueTypeTraits<T>::IsValueType,
                      "T must be an SdfValueType.");
        return _Get(value, time);
    }
    /// \overload
    /// Type-erased access, often not as efficient as typed access.
    USD_API
    bool Get(VtValue* value, UsdTimeCode time = UsdTimeCode::Default()) const;

    /// Populates a vector with authored sample times.
    /// Returns false only on error.
    //
    /// Behaves identically to UsdAttribute::GetTimeSamples()
    ///
    /// \sa UsdAttributeQuery::GetTimeSamplesInInterval
    USD_API
    bool GetTimeSamples(std::vector<double>* times) const;

    /// Populates a vector with authored sample times in \p interval.
    /// Returns false only on an error.
    ///
    /// Behaves identically to UsdAttribute::GetTimeSamplesInInterval()
    USD_API
    bool GetTimeSamplesInInterval(const GfInterval& interval,
                                  std::vector<double>* times) const;

    /// Populates the given vector, \p times with the union of all the
    /// authored sample times on all of the given attribute-query objects,
    /// \p attrQueries.
    ///
    /// Behaves identically to UsdAttribute::GetUnionedTimeSamples()
    ///
    /// \return false if one or more attribute-queries in \p attrQueries are
    /// invalid or if there's an error fetching time-samples for any of
    /// the attribute-query objects.
    ///
    /// \sa UsdAttribute::GetUnionedTimeSamples
    /// \sa UsdAttributeQuery::GetUnionedTimeSamplesInInterval
    USD_API
    static bool GetUnionedTimeSamples(
        const std::vector<UsdAttributeQuery> &attrQueries,
        std::vector<double> *times);

    /// Populates the given vector, \p times with the union of all the
    /// authored sample times in the GfInterval, \p interval on all of the
    /// given attribute-query objects, \p attrQueries.
    ///
    /// Behaves identically to UsdAttribute::GetUnionedTimeSamplesInInterval()
    ///
    /// \return false if one or more attribute-queries in \p attrQueries are
    /// invalid or if there's an error fetching time-samples for any of
    /// the attribute-query objects.
    ///
    /// \sa UsdAttribute::GetUnionedTimeSamplesInInterval
    USD_API
    static bool GetUnionedTimeSamplesInInterval(
        const std::vector<UsdAttributeQuery> &attrQueries,
        const GfInterval &interval,
        std::vector<double> *times);

    /// Returns the number of time samples that have been authored.
    ///
    /// \sa UsdAttribute::GetNumTimeSamples
    USD_API
    size_t GetNumTimeSamples() const;

    /// Populate \a lower and \a upper with the next greater and lesser
    /// value relative to the \a desiredTime.
    ///
    /// \sa UsdAttribute::GetBracketingTimeSamples
    USD_API
    bool GetBracketingTimeSamples(double desiredTime,
                                  double* lower,
                                  double* upper,
                                  bool* hasTimeSamples) const;

    /// Return true if the attribute associated with this query has an
    /// authored default value, authored time samples or a fallback value
    /// provided by a registered schema.
    ///
    /// \sa UsdAttribute::HasValue
    USD_API
    bool HasValue() const;

    /// \deprecated This method is deprecated because it returns `true` even when
    /// an attribute is blocked.  Please use HasAuthoredValue() instead. If
    /// you truly need to know whether the attribute has **any** authored
    /// value opinions, *including blocks*, you can make the following query:
    /// `query.GetAttribute().GetResolveInfo().HasAuthoredValueOpinion()`
    ///
    ///
    /// Return true if this attribute has either an authored default value or
    /// authored time samples.
    USD_API
    bool HasAuthoredValueOpinion() const;

    /// Return true if this attribute has either an authored default value or
    /// authored time samples.  If the attribute has been
    /// \ref Usd_AttributeBlocking "blocked", then return `false`
    /// \sa UsdAttribute::HasAuthoredValue()
    USD_API
    bool HasAuthoredValue() const;

    /// Return true if the attribute associated with this query has a
    /// fallback value provided by a registered schema.
    ///
    /// \sa UsdAttribute::HasFallbackValue
    USD_API
    bool HasFallbackValue() const;

    /// Return true if it is possible, but not certain, that this attribute's
    /// value changes over time, false otherwise.
    ///
    /// \sa UsdAttribute::ValueMightBeTimeVarying
    USD_API
    bool ValueMightBeTimeVarying() const;

    /// @}

private:
    void _Initialize(const UsdAttribute& attr);

    template <typename T>
    USD_API
    bool _Get(T* value, UsdTimeCode time) const;

private:
    UsdAttribute _attr;
    UsdResolveInfo _resolveInfo;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_ATTRIBUTE_QUERY_H