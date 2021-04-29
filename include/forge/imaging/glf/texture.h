#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/glf/texture.h"
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
#ifndef FORGE_IMAGING_GLF_TEXTURE_H
#define FORGE_IMAGING_GLF_TEXTURE_H

/// \file glf/texture.h

#include "forge/forge.h"
#include "forge/imaging/glf/api.h"
#include "forge/imaging/hio/image.h"
#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/refPtr.h"
#include "forge/base/tf/staticTokens.h"
#include "forge/base/tf/weakPtr.h"
#include "forge/base/vt/dictionary.h"

#include "forge/imaging/garch/glApi.h"

#include <map>
#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN


#define GLF_TEXTURE_TOKENS                      \
    (texels)                                    \
    (layout)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(GlfTextureTokens, GLF_API, GLF_TEXTURE_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

TF_DECLARE_WEAK_AND_REF_PTRS(GlfTexture);

/// \class GlfTexture
///
/// Represents a texture object in Glf.
///
/// A texture is typically defined by reading texture image data from an image
/// file but a texture might also represent an attachment of a draw target.
///
class GlfTexture : public TfRefBase, public TfWeakBase
{
public:
    /// \class Binding
    ///
    /// A texture has one or more bindings which describe how the different
    /// aspects of the texture should be bound in order to allow shader
    /// access. Most textures will have a single binding for the role
    /// "texels", but some textures might need multiple bindings, e.g. a
    /// ptexTexture will have an additional binding for the role "layout".
    ///
    struct Binding {
        Binding(TfToken name, TfToken role, GLenum target,
                GLuint textureId, GLuint samplerId)
            : name(name)
            , role(role)
            , target(target)
            , textureId(textureId)
            , samplerId(samplerId) { }

            TfToken name;
            TfToken role;
            GLenum target;
            GLuint textureId;
            GLuint samplerId;
    };
    typedef std::vector<Binding> BindingVector;

    GLF_API
    virtual ~GlfTexture() = 0;

    // Disallow copies
    GlfTexture(const GlfTexture&) = delete;
    GlfTexture& operator=(const GlfTexture&) = delete;

    /// Returns the bindings to use this texture for the shader resource
    /// named \a identifier. If \a samplerId is specified, the bindings
    /// returned will use this samplerId for resources which can be sampled.
    virtual BindingVector GetBindings(TfToken const & identifier,
                                      GLuint samplerId = 0) = 0;

    /// Returns the OpenGl texture name for the texture.
    virtual GLuint GetGlTextureName() = 0;

    /// Amount of memory used to store the texture
    GLF_API
    size_t GetMemoryUsed() const;

    /// Amount of memory the user wishes to allocate to the texture
    GLF_API
    size_t GetMemoryRequested() const;

    /// Specify the amount of memory the user wishes to allocate to the texture
    GLF_API
    void SetMemoryRequested(size_t targetMemory);

    virtual VtDictionary GetTextureInfo(bool forceLoad) = 0;

    GLF_API
    virtual bool IsMinFilterSupported(GLenum filter);

    GLF_API
    virtual bool IsMagFilterSupported(GLenum filter);

    /// static reporting function
    GLF_API
    static size_t GetTextureMemoryAllocated();

    /// Returns an identifier that can be used to determine when the
    /// contents of this texture (i.e. its image data) has changed.
    ///
    /// The contents of most textures will be immutable for the lifetime
    /// of the texture. However, the contents of the texture attachments
    /// of a draw target change when the draw target is updated.
    GLF_API
    size_t GetContentsID() const;

    GLF_API
    HioImage::ImageOriginLocation GetOriginLocation() const;

    GLF_API
    bool IsOriginLowerLeft() const;

protected:
    GLF_API
    GlfTexture();

    GLF_API
    GlfTexture(HioImage::ImageOriginLocation originLocation);

    GLF_API
    void _SetMemoryUsed(size_t size);

    GLF_API
    virtual void _OnMemoryRequestedDirty();

    GLF_API
    void _UpdateContentsID();

private:
    size_t _memoryUsed;
    size_t _memoryRequested;
    size_t _contentsID;
    HioImage::ImageOriginLocation _originLocation;
};

class GlfTextureFactoryBase : public TfType::FactoryBase {
public:
    virtual GlfTextureRefPtr New(const TfToken& texturePath,
                        HioImage::ImageOriginLocation originLocation) const = 0;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_GLF_TEXTURE_H
