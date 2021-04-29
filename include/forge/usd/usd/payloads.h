#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/payloads.h"
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
#ifndef FORGE_USD_USD_PAYLOADS_H
#define FORGE_USD_USD_PAYLOADS_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/usd/common.h"
#include "forge/usd/usd/prim.h"

#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/sdf/path.h"
#include "forge/usd/sdf/payload.h"

FORGE_NAMESPACE_BEGIN

/// \class UsdPayloads
///
/// UsdPayloads provides an interface to authoring and introspecting payloads.
/// Payloads behave the same as Usd references except that payloads can be
/// optionally loaded.
class UsdPayloads {
    friend class UsdPrim;

    explicit UsdPayloads(const UsdPrim& prim) : _prim(prim) {}

public:
    /// Adds a payload to the payload listOp at the current EditTarget, in the
    /// position specified by \p position.
    /// \sa \ref Usd_Failing_References "Why adding references may fail" for
    /// explanation of expectations on \p payload and what return values and
    /// errors to expect, and \ref Usd_OM_ListOps for details on list editing
    /// and composition of listOps.
    USD_API
    bool AddPayload(const SdfPayload& payload,
                    UsdListPosition position=UsdListPositionBackOfPrependList);

    /// \overload
    USD_API
    bool AddPayload(const std::string &identifier,
                    const SdfPath &primPath,
                    const SdfLayerOffset &layerOffset = SdfLayerOffset(),
                    UsdListPosition position=UsdListPositionBackOfPrependList);

    /// \overload
    /// \sa \ref Usd_DefaultPrim_References "Payloads Without Prim Paths"
    USD_API
    bool AddPayload(const std::string &identifier,
                    const SdfLayerOffset &layerOffset = SdfLayerOffset(),
                    UsdListPosition position=UsdListPositionBackOfPrependList);

    /// Add an internal payload to the specified prim.
    /// \sa \ref Usd_Internal_References "Internal Payloads"
    USD_API
    bool AddInternalPayload(const SdfPath &primPath,
                    const SdfLayerOffset &layerOffset = SdfLayerOffset(),
                    UsdListPosition position=UsdListPositionBackOfPrependList);

    /// Removes the specified payload from the payloads listOp at the
    /// current EditTarget.  This does not necessarily eliminate the payload
    /// completely, as it may be added or set in another layer in the same
    /// LayerStack as the current EditTarget.
    /// \sa \ref Usd_OM_ListOps
    USD_API
    bool RemovePayload(const SdfPayload& ref);

    /// Removes the authored payload listOp edits at the current EditTarget.
    /// The same caveats for Remove() apply to Clear().  In fact, Clear() may
    /// actually increase the number of composed payloads, if the listOp being
    /// cleared contained the "remove" operator.
    /// \sa \ref Usd_OM_ListOps
    USD_API
    bool ClearPayloads();

    /// Explicitly set the payloads, potentially blocking weaker opinions that
    /// add or remove items.
    /// \sa \ref Usd_Failing_References "Why adding payloads may fail" for
    /// explanation of expectations on \p items and what return values and
    /// errors to expect, and \ref Usd_OM_ListOps for details on list editing
    /// and composition of listOps.
    USD_API
    bool SetPayloads(const SdfPayloadVector& items);

    /// Return the prim this object is bound to.
    const UsdPrim &GetPrim() const { return _prim; }

    /// \overload
    UsdPrim GetPrim() { return _prim; }

    explicit operator bool() { return bool(_prim); }

private:
    UsdPrim _prim;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_PAYLOADS_H
