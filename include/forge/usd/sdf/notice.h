#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/notice.h"
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
#ifndef FORGE_USD_SDF_NOTICE_H
#define FORGE_USD_SDF_NOTICE_H

/// \file sdf/notice.h

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/usd/sdf/changeList.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/sdf/path.h"
#include "forge/base/tf/notice.h"

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfLayer);

/// \class SdfNotice
///
/// Wrapper class for Sdf notices.
///
class SdfNotice {
public:
    /// \class Base
    ///
    /// Base notification class for scene.  Only useful for type hierarchy
    /// purposes.
    ///
    class Base : public TfNotice {
    public:
        SDF_API ~Base();
    };

    /// \class BaseLayersDidChange
    ///
    /// Base class for LayersDidChange and LayersDidChangeSentPerLayer.
    ///
    class BaseLayersDidChange {
    public:
        BaseLayersDidChange(const SdfLayerChangeListVec &changeVec,
                            size_t serialNumber)
            : _vec(&changeVec)
            , _serialNumber(serialNumber)
            {}

        using const_iterator = SdfLayerChangeListVec::const_iterator;
        using iterator = const_iterator;

        /// A list of layers changed.
        SDF_API
        SdfLayerHandleVector GetLayers() const;

        /// A list of layers and the changes that occurred to them.
        const SdfLayerChangeListVec &GetChangeListVec() const { return *_vec; }

        const_iterator begin() const { return _vec->begin(); }
        const_iterator cbegin() const { return _vec->cbegin(); }
        const_iterator end() const { return _vec->end(); }
        const_iterator cend() const { return _vec->cend(); }

        const_iterator find(SdfLayerHandle const &layer) const {
            return std::find_if(
                begin(), end(),
                [&layer](SdfLayerChangeListVec::value_type const &p) {
                    return p.first == layer;
                });
        }

        bool count(SdfLayerHandle const &layer) const {
            return find(layer) != end();
        }

        /// The serial number for this round of change processing.
        size_t GetSerialNumber() const { return _serialNumber; }

    private:
        const SdfLayerChangeListVec *_vec;
        const size_t _serialNumber;
    };

    /// \class LayersDidChangeSentPerLayer
    ///
    /// Notice sent per-layer indicating all layers whose contents have changed
    /// within a single round of change processing.  If more than one layer
    /// changes in a single round of change processing, we send this notice once
    /// per layer with the same changeVec and serialNumber.  This is so clients
    /// can listen to notices from only the set of layers they care about rather
    /// than listening to the global LayersDidChange notice.
    ///
    class LayersDidChangeSentPerLayer
        : public Base, public BaseLayersDidChange {
    public:
        LayersDidChangeSentPerLayer(const SdfLayerChangeListVec &changeVec,
                                    size_t serialNumber)
            : BaseLayersDidChange(changeVec, serialNumber) {}
        SDF_API virtual ~LayersDidChangeSentPerLayer();
    };

    /// \class LayersDidChange
    ///
    /// Global notice sent to indicate that layer contents have changed.
    ///
    class LayersDidChange
        : public Base, public BaseLayersDidChange {
    public:
        LayersDidChange(const SdfLayerChangeListVec &changeVec,
                        size_t serialNumber)
            : BaseLayersDidChange(changeVec, serialNumber) {}
        SDF_API virtual ~LayersDidChange();
    };

    /// \class LayerInfoDidChange
    ///
    /// Sent when the (scene spec) info of a layer have changed.
    ///
    class LayerInfoDidChange : public Base {
    public:
        LayerInfoDidChange( const TfToken &key ) :
            _key(key) {}
        SDF_API ~LayerInfoDidChange();

        /// Return the key affected.
        const TfToken & key() const { return _key; }
    private:
        TfToken _key;
    };

    /// \class LayerIdentifierDidChange
    ///
    /// Sent when the identifier of a layer has changed.
    ///
    class LayerIdentifierDidChange : public Base {
    public:
        SDF_API
        LayerIdentifierDidChange(const std::string& oldIdentifier,
                                 const std::string& newIdentifier);
        SDF_API
        ~LayerIdentifierDidChange();

        /// Returns the old identifier for the layer.
        const std::string& GetOldIdentifier() const { return _oldId; }

        /// Returns the new identifier for the layer.
        const std::string& GetNewIdentifier() const { return _newId; }

    private:
        std::string _oldId;
        std::string _newId;
    };

    /// \class LayerDidReplaceContent
    ///
    /// Sent after a menv layer has been loaded from a file.
    ///
    class LayerDidReplaceContent : public Base {
    public:
        SDF_API ~LayerDidReplaceContent();
    };

    /// \class LayerDidReloadContent
    /// Sent after a layer is reloaded.
    class LayerDidReloadContent : public LayerDidReplaceContent {
    public:
        SDF_API virtual ~LayerDidReloadContent();
    };

    /// \class LayerDidSaveLayerToFile
    ///
    /// Sent after a layer is saved to file.
    ///
    class LayerDidSaveLayerToFile : public Base {
    public:
        SDF_API ~LayerDidSaveLayerToFile();
    };

    /// \class LayerDirtinessChanged
    ///
    /// Similar behavior to LayersDidChange, but only gets sent if a change
    /// in the dirty status of a layer occurs.
    ///
    class LayerDirtinessChanged : public Base {
    public:
        SDF_API ~LayerDirtinessChanged();
    };

    /// \class LayerMutenessChanged
    ///
    /// Sent after a layer has been added or removed from the set of
    /// muted layers. Note this does not necessarily mean the specified
    /// layer is currently loaded.
    ///
    class LayerMutenessChanged : public Base {
    public:
        LayerMutenessChanged(const std::string& layerPath, bool wasMuted)
            : _layerPath(layerPath)
            , _wasMuted(wasMuted)
        { }

        SDF_API ~LayerMutenessChanged();

        /// Returns the path of the layer that was muted or unmuted.
        const std::string& GetLayerPath() const { return _layerPath; }

        /// Returns true if the layer was muted, false if unmuted.
        bool WasMuted() const { return _wasMuted; }

    private:
        std::string _layerPath;
        bool _wasMuted;
    };
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_NOTICE_H
