#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/plugin/hdEmbree/config.h"
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
#ifndef FORGE_IMAGING_PLUGIN_HD_EMBREE_CONFIG_H
#define FORGE_IMAGING_PLUGIN_HD_EMBREE_CONFIG_H

#include "forge/forge.h"
#include "forge/base/tf/singleton.h"

FORGE_NAMESPACE_BEGIN

/// \class HdEmbreeConfig
///
/// This class is a singleton, holding configuration parameters for HdEmbree.
/// Everything is provided with a default, but can be overridden using
/// environment variables before launching a hydra process.
///
/// Many of the parameters can be used to control quality/performance
/// tradeoffs, or to alter how HdEmbree takes advantage of parallelism.
///
/// At startup, this class will print config parameters if
/// *HDEMBREE_PRINT_CONFIGURATION* is true. Integer values greater than zero
/// are considered "true".
///
class HdEmbreeConfig {
public:
    /// \brief Return the configuration singleton.
    static const HdEmbreeConfig &GetInstance();

    /// How many samples do we need before a pixel is considered
    /// converged?
    ///
    /// Override with *HDEMBREE_SAMPLES_TO_CONVERGENCE*.
    unsigned int samplesToConvergence;

    /// How many pixels are in an atomic unit of parallel work?
    /// A work item is a square of size [tileSize x tileSize] pixels.
    ///
    /// Override with *HDEMBREE_TILE_SIZE*.
    unsigned int tileSize;

    /// How many ambient occlusion rays should we generate per
    /// camera ray?
    ///
    /// Override with *HDEMBREE_AMBIENT_OCCLUSION_SAMPLES*.
    unsigned int ambientOcclusionSamples;

    /// Should the renderpass jitter camera rays for antialiasing?
    ///
    /// Override with *HDEMBREE_JITTER_CAMERA*. Integer values greater than
    /// zero are considered "true".
    bool jitterCamera;

    /// Should the renderpass use the color primvar, or flat white colors?
    /// (Flat white shows off ambient occlusion better).
    ///
    /// Override with *HDEMBREE_USE_FACE_COLORS*. Integer values greater than
    /// zero are considered "true".
    bool useFaceColors;

    /// What should the intensity of the camera light be, specified as a
    /// percent of <1, 1, 1>.  For example, 300 would be <3, 3, 3>.
    ///
    /// Override with *HDEMBREE_CAMERA_LIGHT_INTENSITY*.
    float cameraLightIntensity;

private:
    // The constructor initializes the config variables with their
    // default or environment-provided override, and optionally prints
    // them.
    HdEmbreeConfig();
    ~HdEmbreeConfig() = default;

    HdEmbreeConfig(const HdEmbreeConfig&) = delete;
    HdEmbreeConfig& operator=(const HdEmbreeConfig&) = delete;

    friend class TfSingleton<HdEmbreeConfig>;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_PLUGIN_HD_EMBREE_CONFIG_H
