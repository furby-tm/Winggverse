#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/extCompInputSource.h"
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

#ifndef FORGE_IMAGING_HD_EXT_COMP_INPUT_SOURCE_H
#define FORGE_IMAGING_HD_EXT_COMP_INPUT_SOURCE_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/bufferSource.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class VtValue;

///
/// Abstract base class for a Buffer Source that represents a binding to an
/// input to an ExtComputation.
///
///
class Hd_ExtCompInputSource : public HdNullBufferSource {
public:
    /// Constructs the input binding with the name inputName
    HD_API
    Hd_ExtCompInputSource(const TfToken &inputName);

    HD_API
    virtual ~Hd_ExtCompInputSource() = default;

    /// Returns the name of the input.
    HD_API
    virtual TfToken const &GetName() const final;

    /// Returns the value associated with the input.
    HD_API
    virtual const VtValue &GetValue() const = 0;

private:
    TfToken _inputName;

    Hd_ExtCompInputSource()                                            = delete;
    Hd_ExtCompInputSource(const Hd_ExtCompInputSource &)               = delete;
    Hd_ExtCompInputSource &operator = (const Hd_ExtCompInputSource &)  = delete;
};

using Hd_ExtCompInputSourceSharedPtr =
   std::shared_ptr<Hd_ExtCompInputSource>;
using Hd_ExtCompInputSourceSharedPtrVector =
    std::vector<Hd_ExtCompInputSourceSharedPtr>;


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_EXT_COMP_INPUT_SOURCE_H
