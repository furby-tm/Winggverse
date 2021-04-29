#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/mapExpression.h"
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
#ifndef FORGE_USD_PCP_MAP_EXPRESSION_H
#define FORGE_USD_PCP_MAP_EXPRESSION_H

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"
#include "forge/usd/pcp/mapFunction.h"

#include <boost/intrusive_ptr.hpp>

#if !defined(Q_MOC_RUN)
# include <tbb/spin_mutex.h>
#endif /* Q_MOC_RUN */

#include <atomic>
#include <memory>

FORGE_NAMESPACE_BEGIN

/// \class PcpMapExpression
///
/// An expression that yields a PcpMapFunction value.
///
/// Expressions comprise constant values, variables, and operators
/// applied to sub-expressions.  Expressions cache their computed values
/// internally.  Assigning a new value to a variable automatically
/// invalidates the cached values of dependent expressions.  Common
/// (sub-)expressions are automatically detected and shared.
///
/// PcpMapExpression exists solely to support efficient incremental
/// handling of relocates edits.  It represents a tree of the namespace
/// mapping operations and their inputs, so we can narrowly redo the
/// computation when one of the inputs changes.
///
class PcpMapExpression
{
public:
    /// The value type of PcpMapExpression is a PcpMapFunction.
    typedef PcpMapFunction Value;

    /// Evaluate this expression, yielding a PcpMapFunction value.
    /// The computed result is cached.
    /// The return value is a reference to the internal cached value.
    /// The cache is automatically invalidated as needed.
    PCP_API
    const Value & Evaluate() const;

    /// Default-construct a NULL expression.
    PCP_API
    PcpMapExpression();

    /// Swap this expression with the other.
    PCP_API
    void Swap(PcpMapExpression &other);

    /// Return true if this is a null expression.
    PCP_API
    bool IsNull() const;

    /// \name Creating expressions
    /// @{

    /// Return an expression representing PcpMapFunction::Identity().
    PCP_API
    static PcpMapExpression Identity();

    /// Create a new constant.
    PCP_API
    static PcpMapExpression Constant( const Value & constValue );

    /// A Variable is a mutable memory cell that holds a value.
    /// Changing a variable's value invalidates any expressions using
    /// that variable.
    class Variable {
        Variable(Variable const &) = delete;
        Variable &operator=(Variable const &) = delete;
    public:
        Variable() = default;
        virtual ~Variable();
        /// Return the current value.
        virtual const Value & GetValue() const = 0;
        /// Mutate the variable to have the new value.
        /// This will also invalidate dependant expressions.
        virtual void SetValue(Value && value) = 0;
        /// Return an expression representing the value of this variable.
        /// This lets you use the variable as a sub-term in other expressions.
        virtual PcpMapExpression GetExpression() const = 0;
    };

    /// Variables are held by reference.
    typedef std::unique_ptr<Variable> VariableUniquePtr;

    /// Create a new variable.
    /// The client is expected to retain the reference for as long as
    /// it wishes to continue being able to set the value of the variable.
    /// After the reference is dropped, expressions using the variable
    /// will continue to be valid, but there will be no way to further
    /// change the value of the variable.
    PCP_API
    static VariableUniquePtr NewVariable(Value && initialValue);

    /// Create a new PcpMapExpression representing the application of
    /// f's value, followed by the application of this expression's value.
    PCP_API
    PcpMapExpression Compose(const PcpMapExpression &f) const;

    /// Create a new PcpMapExpression representing the inverse of f.
    PCP_API
    PcpMapExpression Inverse() const;

    /// Return a new expression representing this expression with an added
    /// (if necessary) mapping from </> to </>.
    PCP_API
    PcpMapExpression AddRootIdentity() const;

    /// Return true if the map function is the constant identity function.
    bool IsConstantIdentity() const {
        return _node && _node->key.op == _OpConstant &&
            _node->key.valueForConstant.IsIdentity();
    }

    /// @}

    /// \name Convenience API
    /// The following API just forwards through to the underlying evaluated
    /// mapfunction value.
    /// @{

    /// Return true if the evaluated map function is the identity function.
    /// For identity, MapSourceToTarget() always returns the path unchanged.
    bool IsIdentity() const {
        return Evaluate().IsIdentity();
    }

    /// Map a path in the source namespace to the target.
    /// If the path is not in the domain, returns an empty path.
    SdfPath MapSourceToTarget(const SdfPath &path) const {
        return Evaluate().MapSourceToTarget(path);
    }

    /// Map a path in the target namespace to the source.
    /// If the path is not in the co-domain, returns an empty path.
    SdfPath MapTargetToSource(const SdfPath &path) const {
        return Evaluate().MapTargetToSource(path);
    }

    /// The time offset of the mapping.
    const SdfLayerOffset &GetTimeOffset() const {
        return Evaluate().GetTimeOffset();
    }

    /// Returns a string representation of this mapping for debugging
    /// purposes.
    std::string GetString() const {
        return Evaluate().GetString();
    }

    /// @}

private:
    // Allow Pcp_Statistics access to internal data for diagnostics.
    friend class Pcp_Statistics;
    friend struct Pcp_VariableImpl;

    class _Node;
    typedef boost::intrusive_ptr<_Node> _NodeRefPtr;

    explicit PcpMapExpression(const _NodeRefPtr & node) : _node(node) {}

private: // data
    enum _Op {
        _OpConstant,
        _OpVariable,
        _OpInverse,
        _OpCompose,
        _OpAddRootIdentity
    };

    class _Node : public boost::noncopyable {
    public:
        // The Key holds all the state needed to uniquely identify
        // this (sub-)expression.
        struct Key {
            const _Op op;
            const _NodeRefPtr arg1, arg2;
            const Value valueForConstant;

            Key( _Op op_,
                 const _NodeRefPtr & arg1_,
                 const _NodeRefPtr & arg2_,
                 const Value & valueForConstant_ )
                : op(op_)
                , arg1(arg1_)
                , arg2(arg2_)
                , valueForConstant(valueForConstant_)
            {}
            inline size_t GetHash() const;
            bool operator==(const Key &key) const;
        };

        // The Key of a node is const, and established when it is created.
        const Key key;

        // Whether or not the expression tree up to and including this node
        // will always include an identity mapping.
        const bool expressionTreeAlwaysHasIdentity;

        // Factory method to create new nodes.
        static _NodeRefPtr
        New( _Op op,
             const _NodeRefPtr & arg1 = _NodeRefPtr(),
             const _NodeRefPtr & arg2 = _NodeRefPtr(),
             const Value & valueForConstant = Value() );
        ~_Node();

        // Evaluate (and internally cache) the value of this node.
        const Value & EvaluateAndCache() const;

        // For _OpVariable nodes, sets the variable's value.
        void SetValueForVariable(Value &&newValue);

        // For _OpVariable nodes, returns the variable's value.
        const Value & GetValueForVariable() const {
            return _valueForVariable;
        }

    private:
        explicit _Node( const Key &key_ );
        void _Invalidate();
        Value _EvaluateUncached() const;

        // Helper to determine if the expression tree indicated by key
        // will always contains the root identity.
        static bool _ExpressionTreeAlwaysHasIdentity(const Key& key);

        // Ref-counting ops manage _refCount.
        // Need to friend them here to have access to _refCount.
        friend PCP_API void intrusive_ptr_add_ref(_Node*);
        friend PCP_API void intrusive_ptr_release(_Node*);

        // Registry of node instances, identified by Key.
        // Note: variable nodes are not tracked by the registry.
        struct _NodeMap;
        static TfStaticData<_NodeMap> _nodeRegistry;

        mutable std::atomic<int> _refCount;
        mutable Value _cachedValue;
        mutable std::set<_Node*> _dependentExpressions;
        Value _valueForVariable;
        mutable tbb::spin_mutex _mutex;
        mutable std::atomic<bool> _hasCachedValue;
    };

    // Need to friend them here to have visibility to private class _Node.
    friend PCP_API void intrusive_ptr_add_ref(_Node*);
    friend PCP_API void intrusive_ptr_release(_Node*);

    _NodeRefPtr _node;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_MAP_EXPRESSION_H