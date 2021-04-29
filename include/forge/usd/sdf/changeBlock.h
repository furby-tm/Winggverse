#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/changeBlock.h"
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
#ifndef FORGE_USD_SDF_CHANGE_BLOCK_H
#define FORGE_USD_SDF_CHANGE_BLOCK_H

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"

FORGE_NAMESPACE_BEGIN

/// \class SdfChangeBlock
///
/// <b>DANGER DANGER DANGER</b>
///
/// Please make sure you have read and fully understand the
/// issues below before using a changeblock!  They are very
/// easy to use in an unsafe way that could make the system
/// crash or corrupt data.  If you have any questions, please
/// contact the USD team, who would be happy to help!
///
/// SdfChangeBlock provides a way to group a round of related changes to
/// scene description in order to process them more efficiently.
///
/// Normally, Sdf sends notification immediately as changes are made so
/// that downstream representations in Csd and Mf can update accordingly.
///
/// However, sometimes it can be advantageous to group a series of Sdf
/// changes into a batch so that they can be processed more efficiently,
/// with a single round of change processing.  An example might be when
/// setting many avar values on a model at the same time.
///
/// Opening a changeblock tells Sdf to delay sending notification about
/// changes until the outermost changeblock is exited.  Until then,
/// Sdf internally queues up the notification it needs to send.
///
/// \note  It is *not* safe to use Csd, Mf, or other downstream API
/// while a changeblock is open!!111  This is because those derived
/// representations will not have had a chance to update while the
/// changeblock is open.  Not only will their view of the world be
/// stale, it could be unsafe to even make queries from, since they
/// may be holding onto expired handles to Sdf objects that no longer
/// exist.
///
/// If you need to make a bunch of changes to scene description,
/// the best approach is to build a list of necessary changes that
/// can be performed directly via the Sdf API, then submit those all
/// inside a changeblock without talking to any downstream libraries.
/// For example, this is how Csd performs namespace edits.
///

class SdfChangeBlock {
public:
    SDF_API
    SdfChangeBlock();
    SDF_API
    ~SdfChangeBlock();
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_CHANGE_BLOCK_H
