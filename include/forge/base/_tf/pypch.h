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
#if defined(ARCH_OS_DARWIN)
#include <dirent.h>
#include <glob.h>
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/time.h>
#include <unistd.h>
#include <utime.h>
#include <boost/preprocessor/comparison/greater_equal.hpp>
#include <boost/preprocessor/config/limits.hpp>
#include <mach/mach_time.h>
#endif
#if defined(ARCH_OS_LINUX)
#include <dirent.h>
#include <glob.h>
#include <sys/param.h>
#include <sys/statfs.h>
#include <sys/time.h>
#include <unistd.h>
#include <utime.h>
#include <x86intrin.h>
#include <boost/preprocessor/comparison/greater_equal.hpp>
#include <boost/preprocessor/config/limits.hpp>
#endif
#if defined(ARCH_OS_WINDOWS)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <Shlwapi.h>
#include <intrin.h>
#include <io.h>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/vmd/is_empty.hpp>
#include <boost/vmd/is_tuple.hpp>
#endif
#include <algorithm>
#include <atomic>
#include <cctype>
#include <cerrno>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <deque>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <inttypes.h>
#include <iosfwd>
#include <iostream>
#include <iterator>
#include <limits.h>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <math.h>
#include <memory>
#include <mutex>
#include <new>
#include <ostream>
#include <set>
#include <signal.h>
#include <sstream>
#include <stdarg.h>
#include <stddef.h>
#include <stdexcept>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <boost/any.hpp>
#include <boost/assign.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/call_traits.hpp>
#include <boost/compressed_pair.hpp>
#include <boost/function.hpp>
#include <boost/functional/hash.hpp>
#include <boost/functional/hash_fwd.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/noncopyable.hpp>
#include <boost/operators.hpp>
#include <boost/optional.hpp>
#include <boost/preprocessor.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/logical/and.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/filter.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/push_back.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#ifdef FORGE_PYTHON_SUPPORT_ENABLED
#include <boost/python.hpp>
#include <boost/python/bases.hpp>
#include <boost/python/borrowed.hpp>
#include <boost/python/call.hpp>
#include <boost/python/class.hpp>
#include <boost/python/converter/from_python.hpp>
#include <boost/python/converter/registered.hpp>
#include <boost/python/converter/registrations.hpp>
#include <boost/python/converter/registry.hpp>
#include <boost/python/converter/rvalue_from_python_data.hpp>
#include <boost/python/converter/to_python_function_type.hpp>
#include <boost/python/def.hpp>
#include <boost/python/def_visitor.hpp>
#include <boost/python/default_call_policies.hpp>
#include <boost/python/detail/api_placeholder.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/docstring_options.hpp>
#include <boost/python/errors.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/handle.hpp>
#include <boost/python/has_back_reference.hpp>
#include <boost/python/implicit.hpp>
#include <boost/python/list.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/manage_new_object.hpp>
#include <boost/python/module.hpp>
#include <boost/python/object.hpp>
#include <boost/python/object/class_detail.hpp>
#include <boost/python/object/function.hpp>
#include <boost/python/object/iterator.hpp>
#include <boost/python/object_fwd.hpp>
#include <boost/python/object_operators.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/override.hpp>
#include <boost/python/pure_virtual.hpp>
#include <boost/python/raw_function.hpp>
#include <boost/python/refcount.hpp>
#include <boost/python/register_ptr_to_python.hpp>
#include <boost/python/return_arg.hpp>
#include <boost/python/return_by_value.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/slice.hpp>
#include <boost/python/stl_iterator.hpp>
#include <boost/python/str.hpp>
#include <boost/python/to_python_converter.hpp>
#include <boost/python/to_python_value.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/type_id.hpp>
#include <boost/python/wrapper.hpp>
#if defined(__APPLE__) // Fix breakage caused by Python's pyport.h.
#undef tolower
#undef toupper
#endif
#endif // FORGE_PYTHON_SUPPORT_ENABLED
#include <boost/smart_ptr.hpp>
#include <boost/type_traits.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/has_left_shift.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/in_place_factory.hpp>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>
#include <boost/variant/variant.hpp>
#include <tbb/enumerable_thread_specific.h>
#include <tbb/spin_mutex.h>
#include <tbb/spin_rw_mutex.h>
#ifdef FORGE_PYTHON_SUPPORT_ENABLED
#include "forge/base/tf/pySafePython.h"
#include <frameobject.h>
#endif // FORGE_PYTHON_SUPPORT_ENABLED
