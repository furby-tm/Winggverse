#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/cmds.h"
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
#ifndef FORGE_IMAGING_HGI_CMDS_H
#define FORGE_IMAGING_HGI_CMDS_H

#include "forge/forge.h"
#include "forge/imaging/hgi/api.h"
#include "forge/imaging/hgi/enums.h"
#include <memory>

FORGE_NAMESPACE_BEGIN

class Hgi;

using HgiCmdsUniquePtr = std::unique_ptr<class HgiCmds>;


/// \class HgiCmds
///
/// Graphics commands are recorded in 'cmds' objects which are later submitted
/// to hgi. HgiCmds is the base class for other cmds objects.
///
class HgiCmds
{
public:
    HGI_API
    virtual ~HgiCmds();

    /// Returns true if the HgiCmds object has been submitted to GPU.
    HGI_API
    bool IsSubmitted() const;

protected:
    friend class Hgi;

    HGI_API
    HgiCmds();

    // Submit can be called inside of Hgi::SubmitCmds to commit the
    // command buffer to the GPU. Returns true if work was committed.
    // The default implementation returns false.
    HGI_API
    virtual bool _Submit(Hgi* hgi, HgiSubmitWaitType wait);

    // Flags the HgiCmds object as 'submitted' to GPU.
    HGI_API
    void _SetSubmitted();

private:
    HgiCmds & operator=(const HgiCmds&) = delete;
    HgiCmds(const HgiCmds&) = delete;

    bool _submitted;
};


FORGE_NAMESPACE_END

#endif
