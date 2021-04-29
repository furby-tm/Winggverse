#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/repr.h"
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
#ifndef FORGE_IMAGING_HD_REPR_H
#define FORGE_IMAGING_HD_REPR_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/drawItem.h"
#include "forge/imaging/hd/tokens.h"
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \class HdReprSelector
///
/// Describes one or more authored display representations for an rprim.
/// Display opinions are separated by the topology index they represent.
/// This allows the application to specify one or more topological
/// representations for a given HdRprim.
/// For some visualizations, an application may choose to provide an opinion for
/// the display of the refined surface, the unrefined hull and the points
/// separately from the rprim's authored opinions.
/// HdReprSelector allows these opinions to compose/merge into a final composite
/// representation to be used for rendering.
///
class HdReprSelector
{
public:
    explicit HdReprSelector()
    : refinedToken()
    , unrefinedToken()
    , pointsToken() { }

    explicit HdReprSelector(TfToken const &token)
    : refinedToken(token)
    , unrefinedToken()
    , pointsToken() { }

    explicit HdReprSelector(
        TfToken const &refined,
        TfToken const &unrefined)
    : refinedToken(refined)
    , unrefinedToken(unrefined)
    , pointsToken() { }

    explicit HdReprSelector(
        TfToken const &refined,
        TfToken const &unrefined,
        TfToken const &points)
    : refinedToken(refined)
    , unrefinedToken(unrefined)
    , pointsToken(points) { }

    /// Currenly support upto 3 topology tokens.
    static const size_t MAX_TOPOLOGY_REPRS = 3;

    /// Returns true if the passed in reprToken is in the set of tokens
    /// for any topology index.
    HD_API
    bool Contains(const TfToken &reprToken) const;

    /// Returns true if the topology token at an index is active, i.e., neither
    /// empty nor disabled.
    HD_API
    bool IsActiveRepr(size_t topologyIndex) const;

    /// Returns true if any of the topology tokens is valid, i.e., neither
    /// empty nor disabled.
    HD_API
    bool AnyActiveRepr() const;

    /// Returns a selector that is the composite of this selector 'over'
    /// the passed in selector.
    /// For each token that IsEmpty in this selector return the corresponding
    /// token in the passed in selector.
    /// Effectively this performs a merge operation where this selector wins
    /// for each topological index it has an opinion on.
    HD_API
    HdReprSelector CompositeOver(const HdReprSelector &under) const;

    HD_API
    bool operator==(const HdReprSelector &rhs) const;

    HD_API
    bool operator!=(const HdReprSelector &rhs) const;

    HD_API
    bool operator<(const HdReprSelector &rhs) const;

    HD_API
    size_t Hash() const;

    HD_API
    char const* GetText() const;

    HD_API
    friend std::ostream &operator <<(std::ostream &stream,
                                     HdReprSelector const& t);


    HD_API
    TfToken const &operator[](size_t topologyIndex) const;

private:
    // TfHash support.
    template <class HashState>
    friend void
    TfHashAppend(HashState &h, HdReprSelector const &rs) {
        h.Append(rs.refinedToken, rs.unrefinedToken, rs.pointsToken);
    }

    TfToken refinedToken;
    TfToken unrefinedToken;
    TfToken pointsToken;
};


/// \class HdRepr
///
/// An HdRepr refers to a (single) topological representation of an rprim, and
/// owns the draw item(s) that visually represent it. The draw items are
/// populated by the rprim.
/// The relevant compositional hierarchy is:
///
/// HdRprim
///  |
///  +--HdRepr(s)
///       |
///       +--HdDrawItem(s)
///
/// When multiple topological representations are required for an rprim, we use
/// HdReprSelector to compose the individual representations.
///
class HdRepr final
{
public:
    using DrawItemUniquePtr = std::unique_ptr<HdDrawItem>;
    using DrawItemUniquePtrVector = std::vector<DrawItemUniquePtr>;

    HD_API
    HdRepr();
    HD_API
    ~HdRepr();

    /// Returns the draw items for this representation.
    const DrawItemUniquePtrVector& GetDrawItems() const {
        return _drawItems;
    }

    /// Transfers ownership of a draw item to this repr.
    void AddDrawItem(std::unique_ptr<HdDrawItem> &&item) {
        _drawItems.push_back(std::move(item));
    }

    /// Returns the draw item at the requested index.
    ///
    /// Note that the pointer returned is owned by this object and must not be
    /// deleted.
    HdDrawItem* GetDrawItem(size_t index) const {
        return _drawItems[index].get();
    }

private:
    // Noncopyable
    HdRepr(const HdRepr&) = delete;
    HdRepr& operator=(const HdRepr&) = delete;

private:
    DrawItemUniquePtrVector _drawItems;
};


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HD_REPR_H
