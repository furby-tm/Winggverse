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

#ifndef FORGE_H
#define FORGE_H

/**
 * @file forge/forge.h
 *
 * Pixar's Universal Scene Description | Built for WINGG
 * .              +   .                .   . .     .  .
 *                   .                    .       .     *
 *  .       *                        . . . .  .   .  + .
 *            "You Are Here"            .   .  +  . . .
 *.                 |             .  .   .    .    . .
 *                  |           .     .     . +.    +  .
 *                 \|/            .       .   . .
 *        . .       V          .    * . . .  .  +   .
 *           +      .           .   .      +
 *                            .       . +  .+. .
 *  .                      .     . + .  . .     .      .
 *           .      .    .     . .   . . .        ! /
 *      *             .    . .  +    .  .       - O -
 *          .     .    .  +   . .  *  .       . / |
 *               . + .  .  .  .. +  .
 *.      .  .  .  *   .  *  . +..  .            *
 * .      .   . .   .   .   . .  +   .    .            +
 * Home of the WINGG project -- redefining animation composition,
 * collaborative workflows, simulation engines, skeletal rigging
 * systems, and look development from storyboard to final render.
 * Built on the underlying software architecture provided by Pixar,
 * and extended to meet the ever-growing needs of both artists and
 * production pipelines. It is with this strong core foundation,
 * that we may begin to solve the most challenging issues the world
 * of modern graphics demands, and push the framework for composition
 * & design into the future.
 */

#define FORGE_VERSION_MAJOR 0
#define FORGE_VERSION_MINOR 21
#define FORGE_VERSION_PATCH 05

#define FORGE_VERSION 2105

#define FORGE_USE_NAMESPACES 1

#if FORGE_USE_NAMESPACES

#define FORGE_NS forge
#define FORGE_INTERNAL_NS WINGGverse
#define FORGE_NS_GLOBAL ::FORGE_NS

namespace FORGE_INTERNAL_NS { }

// The root level namespace for all source in the USD distribution.
namespace FORGE_NS {
    using namespace FORGE_INTERNAL_NS;
}

#define FORGE_NAMESPACE_BEGIN   namespace FORGE_INTERNAL_NS {
#define FORGE_NAMESPACE_END  }
#define FORGE_NAMESPACE_USING using namespace FORGE_NS;

#else

#define FORGE_NS
#define FORGE_NS_GLOBAL
#define FORGE_NAMESPACE_BEGIN
#define FORGE_NAMESPACE_END
#define FORGE_NAMESPACE_USING

#endif // FORGE_USE_NAMESPACES

#if 1
#define FORGE_PYTHON_SUPPORT_ENABLED
#endif

#if 1
#define FORGE_PREFER_SAFETY_OVER_SPEED
#endif

#endif //FORGE_H
