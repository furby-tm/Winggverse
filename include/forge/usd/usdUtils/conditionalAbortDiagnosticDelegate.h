#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdUtils/conditionalAbortDiagnosticDelegate.h"
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
#ifndef FORGE_USD_USD_UTILS_CONDITIONAL_ABORT_DIAGNOSTIC_DELEGATE_H
#define FORGE_USD_USD_UTILS_CONDITIONAL_ABORT_DIAGNOSTIC_DELEGATE_H

#include "forge/forge.h"
#include "forge/usd/usdUtils/api.h"
#include "forge/base/tf/diagnosticMgr.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

class TfPatternMatcher;

/// A class which represents the inclusion exclusion filters on which errors
/// will be matched
/// stringFilters: matching and filtering will be done on explicit string
/// of the error/warning
/// codePathFilters: matching and filtering will be done on errors/warnings
/// coming from a specific usd code path
class UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters
{
public:
    UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters() {}
    USDUTILS_API
    UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters(
            const std::vector<std::string>& stringFilters,
            const std::vector<std::string>& codePathFilters);

    const std::vector<std::string>& GetStringFilters() const {
        return _stringFilters;
    };

    const std::vector<std::string>& GetCodePathFilters() const {
        return _codePathFilters;
    }

    USDUTILS_API
    void SetStringFilters(const std::vector<std::string>& stringFilters);
    USDUTILS_API
    void SetCodePathFilters(const std::vector<std::string>& codePathFilters);
private:
    std::vector<std::string> _stringFilters;
    std::vector<std::string> _codePathFilters;
};

/// A class that allows client application to instantiate a diagnostic delegate
/// that can be used to abort operations for a non fatal USD error or warning
/// based on immutable include exclude rules defined for this instance.
///
/// These rules are regex strings where case sensitive matching is done on
/// error/warning text or the location of the code path where the error/warning
/// occured.
/// Note that these rules will be respected only during the lifetime of the
/// delegate.
/// Include Rules determine what errors or warnings will cause a fatal abort.
/// Exclude Rules determine what errors or warnings matched from the Include
/// Rules should not cause the fatal abort.
/// Example: to abort on all errors and warnings coming from "*pxr*" codepath
/// but not from "*ConditionalAbortDiagnosticDelegate*", a client can create the
/// following delegate:
///
/// \code
/// UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters includeFilters;
/// UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters excludeFilters;
/// includeFilters.SetCodePathFilters({"*pxr*"});
/// excludeFilters.SetCodePathFilters({"*ConditionalAbortDiagnosticDelegate*"});
/// UsdUtilsConditionalAbortDiagnosticDelegate delegate =
///     UsdUtilsConditionalAbortDiagnosticDelegate(includeFilters,
///         excludeFilters);
/// \endcode
///
class UsdUtilsConditionalAbortDiagnosticDelegate :
    public TfDiagnosticMgr::Delegate
{
public:

    /// Constructor to initialize conditionalAbortDiagnosticDelegate.
    /// Responsible for adding this delegate instance to TfDiagnosticMgr and
    /// also sets the \p includeFilters and \p excludeFilters
    /// \note The _includeFilters and _excludeFilters are immutable
    USDUTILS_API
    UsdUtilsConditionalAbortDiagnosticDelegate(
        const UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters&
        includeFilters,
        const UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters&
        excludeFilters);

    /// Handles the removal of this delegate from TfDiagnosticMgr.
    USDUTILS_API
    virtual ~UsdUtilsConditionalAbortDiagnosticDelegate();

    UsdUtilsConditionalAbortDiagnosticDelegate() = delete;
    UsdUtilsConditionalAbortDiagnosticDelegate(
        const UsdUtilsConditionalAbortDiagnosticDelegate& delegate) = delete;
    UsdUtilsConditionalAbortDiagnosticDelegate& operator=(
        const UsdUtilsConditionalAbortDiagnosticDelegate& delegate) = delete;

    // Interface overrides
    void IssueError(const TfError& err) override;
    void IssueWarning(const TfWarning& warning) override;
    void IssueFatalError(const TfCallContext &ctx,
            const std::string &msg) override;
    // Following will be no-ops for our purposes - prints same message as
    // DiagnosticMgr
    void IssueStatus(const TfStatus& status) override;

private:

    const std::vector<TfPatternMatcher> _includePatternStringFilters;
    const std::vector<TfPatternMatcher> _includePatternCodePathFilters;
    const std::vector<TfPatternMatcher> _excludePatternStringFilters;
    const std::vector<TfPatternMatcher> _excludePatternCodePathFilters;

protected:
    /// Helper to match \p err against a given set of \p errorFilters
    /// A client can override this to affect the behavior of the rule matcher.
    virtual bool _RuleMatcher(const TfDiagnosticBase& err,
            const std::vector<TfPatternMatcher>& stringPatternFilters,
            const std::vector<TfPatternMatcher>& codePathPatternFilters);
};


FORGE_NAMESPACE_END

#endif
