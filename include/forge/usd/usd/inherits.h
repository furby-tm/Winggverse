#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/inherits.h"
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
#ifndef FORGE_USD_USD_INHERITS_H
#define FORGE_USD_USD_INHERITS_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/usd/common.h"
#include "forge/usd/usd/prim.h"

#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/sdf/path.h"

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfPrimSpec);

/// \class UsdInherits
///
/// A proxy class for applying listOp edits to the inherit paths list for a
/// prim.
///
/// All paths passed to the UsdInherits API are expected to be in the
/// namespace of the owning prim's stage. Subroot prim inherit paths
/// will be translated from this namespace to the  namespace of the current
/// edit target, if necessary. If a path cannot be translated, a coding error
/// will be issued and no changes will be made. Root prim inherit paths will
/// not be translated.
///
class UsdInherits {
    friend class UsdPrim;

    explicit UsdInherits(const UsdPrim& prim) : _prim(prim) {}

public:
    /// Adds a path to the inheritPaths listOp at the current EditTarget,
    /// in the position specified by \p position.
    USD_API
    bool AddInherit(const SdfPath &primPath,
                    UsdListPosition position=UsdListPositionBackOfPrependList);

    /// Removes the specified path from the inheritPaths listOp at the
    /// current EditTarget.
    USD_API
    bool RemoveInherit(const SdfPath &primPath);

    /// Removes the authored inheritPaths listOp edits at the current edit
    /// target.
    USD_API
    bool ClearInherits();

    /// Explicitly set the inherited paths, potentially blocking weaker opinions
    /// that add or remove items, returning true on success, false if the edit
    /// could not be performed.
    USD_API
    bool SetInherits(const SdfPathVector& items);

    /// Return all the paths in this prim's stage's local layer stack that would
    /// compose into this prim via direct inherits (excluding prim specs that
    /// would be composed into this prim due to inherits authored on ancestral
    /// prims) in strong-to-weak order.
    ///
    /// Note that there currently may not be any scene description at these
    /// paths on the stage.  This returns all the potential places that such
    /// opinions could appear.
    USD_API
    SdfPathVector GetAllDirectInherits() const;

    /// Return the prim this object is bound to.
    const UsdPrim &GetPrim() const { return _prim; }
    UsdPrim GetPrim() { return _prim; }

    explicit operator bool() { return bool(_prim); }

    // ---------------------------------------------------------------------- //
    // Private Methods and Members
    // ---------------------------------------------------------------------- //
private:

    UsdPrim _prim;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_INHERITS_H
