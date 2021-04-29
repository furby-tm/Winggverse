#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/editContext.h"
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
#ifndef FORGE_USD_USD_EDIT_CONTEXT_H
#define FORGE_USD_USD_EDIT_CONTEXT_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/usd/editTarget.h"
#include "forge/base/tf/declarePtrs.h"

#include <memory>
#include <utility>

FORGE_NAMESPACE_BEGIN


TF_DECLARE_WEAK_PTRS(UsdStage);

/// \class UsdEditContext
///
/// A utility class to temporarily modify a stage's current EditTarget during
/// an execution scope.
///
/// This is an "RAII"-like object meant to be used as an automatic local
/// variable.  Upon construction, it sets a given stage's EditTarget, and upon
/// destruction it restores the stage's EditTarget to what it was previously.
///
/// Example usage, temporarily overriding a stage's EditTarget to direct an
/// edit to the stage's session layer.  When the \a ctx object expires, it
/// restores the stage's EditTarget to whatever it was previously.
///
/// \code
/// void SetVisState(const UsdPrim &prim, bool vis) {
///     UsdEditContext ctx(prim.GetStage(),
///                        prim.GetStage()->GetSessionLayer());
///     prim.GetAttribute("visible").Set(vis);
/// }
/// \endcode
///
/// <b>Threading Note</b>
///
/// When one thread is mutating a \a UsdStage, it is unsafe for any other thread
/// to either query or mutate it.  Using this class with a stage in such a way
/// that it modifies the stage's EditTarget constitutes a mutation.
///
class UsdEditContext
{
    UsdEditContext(UsdEditContext const &) = delete;
    UsdEditContext &operator=(UsdEditContext const &) = delete;
public:
    /// Construct without modifying \a stage's current EditTarget.  Save
    /// \a stage's current EditTarget to restore on destruction.
    USD_API
    explicit UsdEditContext(const UsdStagePtr &stage);

    /// Construct and save \a stage's current EditTarget to restore on
    /// destruction, then invoke stage->SetEditTarget(editTarget).
    ///
    /// If \a editTarget is invalid, a coding error will be issued by the
    /// \a stage, and its EditTarget will not be modified.
    USD_API
    UsdEditContext(const UsdStagePtr &stage, const UsdEditTarget &editTarget);

    /// \overload
    /// This ctor is handy to construct an edit context from the return
    /// value of another function (Cannot return a UsdEditContext since it
    /// needs to be noncopyable).
    ///
    /// If \a editTarget is invalid, a coding error will be issued by the
    /// \a stage, and its EditTarget will not be modified.
    USD_API
    UsdEditContext(const std::pair<UsdStagePtr, UsdEditTarget > &stageTarget);

    /// Restore the stage's original EditTarget if this context's stage is
    /// valid.  Otherwise do nothing.
    USD_API
    ~UsdEditContext();

private:
    // The stage this context is bound to.
    UsdStagePtr _stage;

    // The stage's original EditTarget.
    UsdEditTarget _originalEditTarget;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_EDIT_CONTEXT_H
