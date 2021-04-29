#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/glf/simpleMaterial.h"
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
#ifndef FORGE_IMAGING_GLF_SIMPLE_MATERIAL_H
#define FORGE_IMAGING_GLF_SIMPLE_MATERIAL_H

/// \file glf/simpleMaterial.h

#include "forge/forge.h"
#include "forge/imaging/glf/api.h"
#include "forge/base/gf/vec4f.h"

FORGE_NAMESPACE_BEGIN


class GlfSimpleMaterial final {
public:
    GLF_API
    GlfSimpleMaterial();
    GLF_API
    ~GlfSimpleMaterial();

    GLF_API
    GfVec4f const & GetAmbient() const;
    GLF_API
    void SetAmbient(GfVec4f const & ambient);

    GLF_API
    GfVec4f const & GetDiffuse() const;
    GLF_API
    void SetDiffuse(GfVec4f const & diffuse);

    GLF_API
    GfVec4f const & GetSpecular() const;
    GLF_API
    void SetSpecular(GfVec4f const & specular);

    GLF_API
    GfVec4f const & GetEmission() const;
    GLF_API
    void SetEmission(GfVec4f const & specular);

    GLF_API
    double GetShininess() const;
    GLF_API
    void SetShininess(double specular);

    GLF_API
    bool operator ==(GlfSimpleMaterial const & other) const;
    GLF_API
    bool operator !=(GlfSimpleMaterial const & other) const;

private:
    GfVec4f _ambient;
    GfVec4f _diffuse;
    GfVec4f _specular;
    GfVec4f _emission;
    double _shininess;
};


FORGE_NAMESPACE_END

#endif
