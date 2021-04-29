#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdMedia/tokens.h"
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
#ifndef USDMEDIA_TOKENS_H
#define USDMEDIA_TOKENS_H

/// \file usdMedia/tokens.h

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//
// This is an automatically generated file (by usdGenSchema.py).
// Do not hand-edit!
//
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "forge/forge.h"
#include "forge/usd/usdMedia/api.h"
#include "forge/base/tf/staticData.h"
#include "forge/base/tf/token.h"
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \class UsdMediaTokensType
///
/// \link UsdMediaTokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// UsdMediaTokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use UsdMediaTokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(UsdMediaTokens->auralMode);
/// \endcode
struct UsdMediaTokensType {
    USDMEDIA_API UsdMediaTokensType();
    /// \brief "auralMode"
    ///
    /// UsdMediaSpatialAudio
    const TfToken auralMode;
    /// \brief "endTime"
    ///
    /// UsdMediaSpatialAudio
    const TfToken endTime;
    /// \brief "filePath"
    ///
    /// UsdMediaSpatialAudio
    const TfToken filePath;
    /// \brief "gain"
    ///
    /// UsdMediaSpatialAudio
    const TfToken gain;
    /// \brief "loopFromStage"
    ///
    /// Possible value for UsdMediaSpatialAudio::GetPlaybackModeAttr()
    const TfToken loopFromStage;
    /// \brief "loopFromStart"
    ///
    /// Possible value for UsdMediaSpatialAudio::GetPlaybackModeAttr()
    const TfToken loopFromStart;
    /// \brief "loopFromStartToEnd"
    ///
    /// Possible value for UsdMediaSpatialAudio::GetPlaybackModeAttr()
    const TfToken loopFromStartToEnd;
    /// \brief "mediaOffset"
    ///
    /// UsdMediaSpatialAudio
    const TfToken mediaOffset;
    /// \brief "nonSpatial"
    ///
    /// Possible value for UsdMediaSpatialAudio::GetAuralModeAttr()
    const TfToken nonSpatial;
    /// \brief "onceFromStart"
    ///
    /// Possible value for UsdMediaSpatialAudio::GetPlaybackModeAttr(), Default value for UsdMediaSpatialAudio::GetPlaybackModeAttr()
    const TfToken onceFromStart;
    /// \brief "onceFromStartToEnd"
    ///
    /// Possible value for UsdMediaSpatialAudio::GetPlaybackModeAttr()
    const TfToken onceFromStartToEnd;
    /// \brief "playbackMode"
    ///
    /// UsdMediaSpatialAudio
    const TfToken playbackMode;
    /// \brief "spatial"
    ///
    /// Possible value for UsdMediaSpatialAudio::GetAuralModeAttr(), Default value for UsdMediaSpatialAudio::GetAuralModeAttr()
    const TfToken spatial;
    /// \brief "startTime"
    ///
    /// UsdMediaSpatialAudio
    const TfToken startTime;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var UsdMediaTokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa UsdMediaTokensType
extern USDMEDIA_API TfStaticData<UsdMediaTokensType> UsdMediaTokens;

FORGE_NAMESPACE_END

#endif
