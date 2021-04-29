#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyResultConversions.h"
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
#ifndef FORGE_BASE_TF_PY_RESULT_CONVERSIONS_H
#define FORGE_BASE_TF_PY_RESULT_CONVERSIONS_H

#include "forge/forge.h"

#include "forge/base/tf/pyUtils.h"

#include <boost/python/tuple.hpp>
#include <boost/python/list.hpp>
#include <boost/python/dict.hpp>

#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <type_traits>

FORGE_NAMESPACE_BEGIN

template <typename T> struct Tf_PySequenceToListConverter;
template <typename T> struct Tf_PySequenceToSetConverter;
template <typename T> struct Tf_PyMapToDictionaryConverter;
template <typename T> struct Tf_PySequenceToTupleConverter;
template <typename First, typename Second> struct Tf_PyPairToTupleConverter;

/// \class TfPySequenceToList
///
/// A \c boost::python result converter generator which converts standard
/// library sequences to lists.
///
/// The way to use this is as a return value policy for a function which
/// returns a sequence or a const reference to a sequence.  For example this
/// function:
/// \code
/// vector<double> getDoubles() {
///     vector<double> ret;
///     ret.push_back(1.0);
///     ret.push_back(2.0);
///     ret.push_back(3.0);
///     return ret;
/// }
/// \endcode
///
/// May be wrapped as:
/// \code
/// def("getDoubles", &getDoubles, return_value_policy<TfPySequenceToList>())
/// \endcode
struct TfPySequenceToList {
    template <typename T>
    struct apply {
        typedef Tf_PySequenceToListConverter<T> type;
    };
};

/// \class TfPySequenceToSet
///
/// A \c boost::python result converter generator which converts standard
/// library sequences to sets.
///
/// The way to use this is as a return value policy for a function which
/// returns a sequence or a const reference to a sequence.  For example this
/// function:
/// \code
/// unordered_set<double> getDoubles() {
///     unordered_set<double> ret;
///     ret.insert(1.0);
///     ret.insert(2.0);
///     ret.insert(3.0);
///     return ret;
/// }
/// \endcode
///
/// May be wrapped as:
/// \code
/// def("getDoubles", &getDoubles, return_value_policy<TfPySequenceToSet>())
/// \endcode
struct TfPySequenceToSet {
    template <typename T>
    struct apply {
        typedef Tf_PySequenceToSetConverter<T> type;
    };
};

/// \class TfPyMapToDictionary
///
/// A \c boost::python result converter generator which converts standard
/// library maps to dictionaries.
struct TfPyMapToDictionary {
    template <typename T>
    struct apply {
        typedef Tf_PyMapToDictionaryConverter<T> type;
    };
};

/// \class TfPySequenceToTuple
///
/// A \c boost::python result converter generator which converts standard
/// library sequences to tuples.
/// \see TfPySequenceToList.
struct TfPySequenceToTuple {
    template <typename T>
    struct apply {
        typedef Tf_PySequenceToTupleConverter<T> type;
    };
};

/// A \c boost::python result converter generator which converts standard
/// library pairs to tuples.
struct TfPyPairToTuple {
    template <typename T>
    struct apply {
        typedef Tf_PyPairToTupleConverter<typename T::first_type,
                                          typename T::second_type> type;
    };
};

template <typename T>
struct Tf_PySequenceToListConverter {
    typedef typename boost::remove_reference<T>::type SeqType;
    bool convertible() const {
        return true;
    }
    PyObject *operator()(T seq) const {
        return boost::python::incref(TfPyCopySequenceToList(seq).ptr());
    }
    PyTypeObject *get_pytype() {
        return &PyList_Type;
    }
};

template <typename T>
struct Tf_PySequenceToSetConverter {
    typedef typename std::remove_reference<T>::type SeqType;
    bool convertible() const {
        return true;
    }
    PyObject *operator()(T seq) const {
        return boost::python::incref(TfPyCopySequenceToSet(seq).ptr());
    }
    PyTypeObject *get_pytype() {
        return &PySet_Type;
    }
};

template <typename T>
struct Tf_PyMapToDictionaryConverter {
    typedef typename boost::remove_reference<T>::type SeqType;
    // TODO: convertible() should be made more robust by checking that the
    // value_type of the container is pair<const key_type, data_type>
    bool convertible() const {
        return true;
    }
    PyObject *operator()(T seq) const {
        return boost::python::incref(TfPyCopyMapToDictionary(seq).ptr());
    }
    PyTypeObject *get_pytype() {
        return &PyDict_Type;
    }
};

template <typename T>
struct Tf_PySequenceToTupleConverter {
    typedef typename boost::remove_reference<T>::type SeqType;
    bool convertible() const {
        return true;
    }
    PyObject *operator()(T seq) const {
        return boost::python::incref(TfPyCopySequenceToTuple(seq).ptr());
    }
    PyTypeObject *get_pytype() {
        return &PyTuple_Type;
    }
};

template <typename First, typename Second>
struct Tf_PyPairToTupleConverter {
    typedef std::pair<First, Second> PairType;
    bool convertible() const {
        return true;
    }
    PyObject *operator()(PairType const& a) const {
        boost::python::tuple result =
            boost::python::make_tuple(a.first, a.second);
        return boost::python::incref(result.ptr());
    }
    PyTypeObject *get_pytype() {
        return &PyTuple_Type;
    }
};

FORGE_NAMESPACE_END

#endif // TF_RESULT_CONVERSIONS_H
