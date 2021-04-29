#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdUtils/coalescingDiagnosticDelegate.h"
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
#ifndef FORGE_USD_USD_UTILS_COALESCING_DIAGNOSTIC_DELEGATE_H
#define FORGE_USD_USD_UTILS_COALESCING_DIAGNOSTIC_DELEGATE_H

/// \file usdUtils/coalescingDiagnosticDelegate.h
///
/// A class which provides aggregation of warnings and statuses
/// emitted from Tf's diagnostic management system. These diagnostic
/// notifications can be coalesced by invocation point,
/// currently defined as the source file, line number and function name,
/// to recieve a more concise output.

#include "forge/forge.h"
#include "forge/usd/usdUtils/api.h"
#include "forge/base/tf/diagnosticMgr.h"

#include <ostream>
#include <memory>
#include <string>
#include <vector>

#if !defined(Q_MOC_RUN)
# include <tbb/concurrent_queue.h>
#endif /* Q_MOC_RUN */

FORGE_NAMESPACE_BEGIN

/// The shared component in a coalesced result
/// This type can be thought of as the key by which we
/// coalesce our diagnostics.
struct UsdUtilsCoalescingDiagnosticDelegateSharedItem {
    size_t sourceLineNumber;
    std::string sourceFunction;
    std::string sourceFileName;
};

/// The unshared component in a coalesced result
struct UsdUtilsCoalescingDiagnosticDelegateUnsharedItem {
    TfCallContext context;
    std::string commentary;
};

/// An item used in coalesced results, containing a shared component:
/// the file/function/line number, and a set of unshared components: the
/// call context and commentary.
struct UsdUtilsCoalescingDiagnosticDelegateItem {
    UsdUtilsCoalescingDiagnosticDelegateSharedItem sharedItem;
    std::vector<UsdUtilsCoalescingDiagnosticDelegateUnsharedItem> unsharedItems;
};

/// A vector of coalesced results, each containing a shared component,
/// the file/function/line number, and a set of unshared components, the
/// call context and commentary.
typedef std::vector<UsdUtilsCoalescingDiagnosticDelegateItem>
        UsdUtilsCoalescingDiagnosticDelegateVector;

/// A class which collects warnings and statuses from the
/// Tf diagnostic manager system in a thread safe manner.
///
/// This class allows clients to get both the unfiltered
/// results, as well as a compressed view which deduplicates
/// diagnostic events by their source line number, function and file
/// from which they occurred.
class UsdUtilsCoalescingDiagnosticDelegate : public TfDiagnosticMgr::Delegate {
public:
    USDUTILS_API
    UsdUtilsCoalescingDiagnosticDelegate();

    USDUTILS_API
    virtual ~UsdUtilsCoalescingDiagnosticDelegate();

    /// Methods that implement the interface provided in TfDiagnosticMgr::Delegate

    USDUTILS_API
    virtual void IssueError(const TfError&) override;

    USDUTILS_API
    virtual void IssueStatus(const TfStatus&) override;

    USDUTILS_API
    virtual void IssueWarning(const TfWarning&) override;

    USDUTILS_API
    virtual void IssueFatalError(const TfCallContext&, const std::string &) override;

    // Methods that provide collection of diagnostics as well as sending
    // them to a stream(stderr, stdout, a file, etc).

    /// Print all pending diagnostics in a coalesced form to \p ostr
    /// \note This method clears the pending diagnostics.
    USDUTILS_API
    void DumpCoalescedDiagnostics(std::ostream& ostr);

    /// Print all pending diagnostics without any coalescing to \p ostr
    /// \note This method clears the pending diagnostics.
    USDUTILS_API
    void DumpUncoalescedDiagnostics(std::ostream& ostr);

    /// Get all pending diagnostics in a coalesced form.
    /// \note This method clears the pending diagnostics.
    USDUTILS_API
    UsdUtilsCoalescingDiagnosticDelegateVector TakeCoalescedDiagnostics();

    /// Get all pending diagnostics without any coalescing.
    /// \note This method clears the pending diagnostics.
    USDUTILS_API
    std::vector<std::unique_ptr<TfDiagnosticBase>> TakeUncoalescedDiagnostics();

private:
    tbb::concurrent_queue<TfDiagnosticBase*> _diagnostics;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_UTILS_COALESCING_DIAGNOSTIC_DELEGATE_H
