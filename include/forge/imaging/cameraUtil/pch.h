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
// WARNING: THIS FILE IS GENERATED.  DO NOT EDIT.
//

#define TF_MAX_ARITY 7
#include "forge/forge.h"
#include "forge/base/arch/defines.h"
#if defined(ARCH_OS_WINDOWS)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <boost/preprocessor/variadic/size.hpp>
#include <boost/vmd/is_empty.hpp>
#include <boost/vmd/is_tuple.hpp>
#endif
#include <atomic>
#include <cfloat>
#include <cinttypes>
#include <cmath>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <float.h>
#include <functional>
#include <initializer_list>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <math.h>
#include <memory>
#include <mutex>
#include <set>
#include <sstream>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <sys/types.h>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <boost/any.hpp>
#include <boost/functional/hash.hpp>
#include <boost/functional/hash_fwd.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/noncopyable.hpp>
#include <boost/operators.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#ifdef FORGE_PYTHON_SUPPORT_ENABLED
#include <boost/python.hpp>
#include <boost/python/class.hpp>
#include <boost/python/converter/from_python.hpp>
#include <boost/python/converter/registered.hpp>
#include <boost/python/converter/rvalue_from_python_data.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/handle.hpp>
#include <boost/python/list.hpp>
#include <boost/python/module.hpp>
#include <boost/python/object.hpp>
#include <boost/python/object_fwd.hpp>
#include <boost/python/object_operators.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/refcount.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/to_python_converter.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/type_id.hpp>
#if defined(__APPLE__) // Fix breakage caused by Python's pyport.h.
#undef tolower
#undef toupper
#endif
#endif // FORGE_PYTHON_SUPPORT_ENABLED
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#ifdef FORGE_PYTHON_SUPPORT_ENABLED
#include "forge/base/tf/pySafePython.h"
#endif // FORGE_PYTHON_SUPPORT_ENABLED
