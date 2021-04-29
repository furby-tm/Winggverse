#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/crateData.h"
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
#ifndef FORGE_USD_USD_CRATE_DATA_H
#define FORGE_USD_USD_CRATE_DATA_H

#include "forge/forge.h"
#include "forge/usd/sdf/abstractData.h"

#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/token.h"
#include "forge/base/vt/value.h"

#include <memory>
#include <vector>
#include <set>

FORGE_NAMESPACE_BEGIN


/// \class Usd_CrateData
///
class Usd_CrateData : public SdfAbstractData
{
public:

    Usd_CrateData();
    virtual ~Usd_CrateData();

    static TfToken const &GetSoftwareVersionToken();

    static bool CanRead(const std::string &assetPath);
    bool Save(const std::string &fileName);
    bool Open(const std::string &assetPath);

    virtual bool StreamsData() const;
    virtual void CreateSpec(const SdfPath &path,
                            SdfSpecType specType);
    virtual bool HasSpec(const SdfPath &path) const;
    virtual void EraseSpec(const SdfPath &path);
    virtual void MoveSpec(const SdfPath& oldPath,
                          const SdfPath& newPath);
    virtual SdfSpecType GetSpecType(const SdfPath &path) const;

    virtual bool Has(const SdfPath& path, const TfToken& fieldName,
                     SdfAbstractDataValue* value) const;
    virtual bool Has(const SdfPath& path, const TfToken& fieldName,
                     VtValue *value=nullptr) const;
    virtual VtValue Get(const SdfPath& path,
                        const TfToken& fieldName) const;
    virtual std::type_info const &GetTypeid(const SdfPath& path,
                                            const TfToken& fieldname) const;
    virtual void Set(const SdfPath& path, const TfToken& fieldName,
                     const VtValue& value);
    virtual void Set(const SdfPath& path, const TfToken& fieldName,
                     const SdfAbstractDataConstValue& value);
    virtual void Erase(const SdfPath& path,
                       const TfToken& fieldName);
    virtual std::vector<TfToken> List(const SdfPath& path) const;

    /// \name Time-sample API
    /// @{

    virtual std::set<double>
    ListAllTimeSamples() const;

    virtual std::set<double>
    ListTimeSamplesForPath(const SdfPath& path) const;

    virtual bool
    GetBracketingTimeSamples(double time, double* tLower, double* tUpper) const;

    virtual size_t
    GetNumTimeSamplesForPath(const SdfPath& path) const;

    virtual bool
    GetBracketingTimeSamplesForPath(const SdfPath& path,
                                    double time,
                                    double* tLower, double* tUpper) const;

    virtual bool
    QueryTimeSample(const SdfPath& path, double time,
                    SdfAbstractDataValue *value) const;
    virtual bool
    QueryTimeSample(const SdfPath& path, double time,
                    VtValue *value) const;

    virtual void
    SetTimeSample(const SdfPath& path, double time,
                  const VtValue & value);

    virtual void
    EraseTimeSample(const SdfPath& path, double time);

    /// @}

private:

    // SdfAbstractData overrides
    virtual void _VisitSpecs(SdfAbstractDataSpecVisitor* visitor) const;

    friend class Usd_CrateDataImpl;
    std::unique_ptr<class Usd_CrateDataImpl> _impl;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_CRATE_DATA_H
