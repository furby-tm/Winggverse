#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/concurrentList.h"
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

#ifndef FORGE_BASE_TRACE_CONCURRENT_LIST_H
#define FORGE_BASE_TRACE_CONCURRENT_LIST_H

#include "forge/forge.h"

#include "forge/base/arch/align.h"

#if !defined(Q_MOC_RUN)
# include <tbb/cache_aligned_allocator.h>
#endif /* Q_MOC_RUN */

#include <atomic>
#include <iterator>

FORGE_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////
/// \class TraceConcurrentList
///
/// This class supports thread safe insertion and iteration over a list of items.
///
template <typename T>
class TraceConcurrentList {

    // Linked list node that is cache line aligned to prevent false sharing.
    struct alignas(ARCH_CACHE_LINE_SIZE*2) Node {
        T value;
        Node* next;
    };

public:
    ////////////////////////////////////////////////////////////////////////////
    /// \class iterator
    ///
    /// This class provides forward iterator support to iterate over all the
    /// items.
    ///
    class iterator {
    public:
        // iterator types
        using iterator_category = std::forward_iterator_tag;
        using value = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = ptrdiff_t;

        iterator() : _node(nullptr) {}

        pointer operator->() {
            return _node ? &_node->value : nullptr;
        }

        reference operator*() {
            return _node->value;
        }

        iterator& operator++() {
            _node = _node->next;
            return *this;
        }

        iterator operator++(int) {
            iterator result(*this);
            _node = _node->next;
            return result;
        }

        bool operator !=(const iterator& other) const {
            return _node != other._node;
        }

        bool operator ==(const iterator& other) const {
            return _node == other._node;
        }

    private:
        explicit iterator(Node* node) : _node(node) {}
        Node* _node;
        friend class TraceConcurrentList;
    };

    /// Constructor.
    TraceConcurrentList() : _head(nullptr) {}

    /// Destructor.
    ~TraceConcurrentList() {
        // Delete all nodes in the list.
        Node* curNode = _head.load(std::memory_order_acquire);
        while (curNode) {
            Node* nodeToDelete = curNode;
            curNode = curNode->next;
            nodeToDelete->~Node();
            _alloc.deallocate(nodeToDelete, 1);
        }
    }

    // No copies
    TraceConcurrentList(const TraceConcurrentList&) = delete;
    TraceConcurrentList& operator=(const TraceConcurrentList&) = delete;

    /// \name Iterator support.
    /// @{
    iterator begin() { return iterator(_head.load(std::memory_order_acquire)); }
    iterator end() { return iterator(); }
    /// @}

    /// Inserts an item at the beginning of the list and returns an iterator to
    /// the newly created item.
    iterator Insert() {
        Node* newNode = _alloc.allocate(1);
        new((void*)newNode) Node();

        // Add the node to the linked list in an atomic manner.
        do {
            newNode->next = _head.load(std::memory_order_relaxed);
        } while (!_head.compare_exchange_weak(newNode->next, newNode));
        return iterator(newNode);
    }

private:
    std::atomic<Node*> _head;
    tbb::cache_aligned_allocator<Node> _alloc;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_CONCURRENT_LIST_H
