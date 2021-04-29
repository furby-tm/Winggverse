#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pathUtils.h"
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
#ifndef FORGE_BASE_TF_PATH_UTILS_H
#define FORGE_BASE_TF_PATH_UTILS_H

#include "forge/forge.h"
#include "forge/base/tf/api.h"
#include "forge/base/arch/fileSystem.h"
#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

/// \file tf/pathUtils.h
/// \ingroup group_tf_Path
/// Definitions of basic path utilities in tf.
///
/// These are utilities that operate on paths (represented by strings as
/// something like: "/chars/Buzz/Torso".

/// Returns the canonical path of the specified filename, eliminating any
/// symbolic links encountered in the path.
///
/// This is a wrapper to realpath(3), which caters for situations where the
/// real realpath() would return a NULL string, such as the case where the
/// path is really just a program name.  The memory allocated by realpath is
/// managed internally.
///
/// If \a allowInaccessibleSuffix is true, then this function will only invoke
/// realpath on the longest accessible prefix of \a path, and then append the
/// inaccessible suffix.
///
/// If \a error is provided, it is set to the error reason should an error
/// occur while computing the real path. If no error occurs, the string is
/// cleared.
TF_API
std::string TfRealPath(std::string const& path,
                       bool allowInaccessibleSuffix = false,
                       std::string* error = 0);

/// Normalizes the specified path, eliminating double slashes, etc.
///
/// This canonicalizes paths, removing any double slashes, and eliminiating
/// '.', and '..' components of the path.  This emulates the behavior of
/// os.path.normpath in Python.
///
/// On Windows, all backslashes are converted to forward slashes and drive
/// specifiers (e.g., "C:") are lower-cased. If \p stripDriveSpecifier
/// is \c true, these drive specifiers are removed from the path.
TF_API
std::string TfNormPath(std::string const& path,
                       bool stripDriveSpecifier = false);

/// Return the index delimiting the longest accessible prefix of \a path.
///
/// The returned value is safe to use to split the string via it's generalized
/// copy constructor. If the entire path is accessible, return the length of
/// the input string. If none of the path is accessible, return 0.  Otherwise
/// the index points to the path separator that delimits the existing prefix
/// from the non-existing suffix.
///
/// Examples: suppose the paths /, /usr, and /usr/anim exist, but no other
/// paths exist.
///
/// TfFindLongestAccessiblePrefix('/usr/anim')     -> 9
/// TfFindLongestAccessiblePrefix('/usr/anim/foo') -> 9
/// TfFindLongestAccessiblePrefix('/foo/bar')      -> 0
///
/// If an error occurs, and the \a error string is not null, it is set to the
/// reason for the error. If the error string is set, the returned index is
/// the path separator before the element at which the error occurred.
TF_API
std::string::size_type
TfFindLongestAccessiblePrefix(std::string const &path, std::string* error = 0);

/// Returns the canonical absolute path of the specified filename.
///
/// This makes the specified path absolute, by prepending the current working
/// directory.  If the path is already absolute, it is returned unmodified.
/// This function differs from TfRealPath in that the path may point to a
/// symlink, or not exist at all, and still result in an absolute path, rather
/// than an empty string.
TF_API
std::string TfAbsPath(std::string const& path);

/// Returns the extension for a file path
///
/// If \p path is a directory path, an empty path, or a dotfile path, return
/// the empty string. Otherwise return \p path 's dot-separated extension as
/// a string(dot not included).
///
/// Examples:
///
/// TfGetExtension('/foo/bar')              -> ''
/// TfGetExtension('/foo/bar/foo.baz')      -> 'baz'
/// TfGetExtension('/foo.bar/foo.baz')      -> 'baz'
/// TfGetExtension('/foo/bar/foo.101.baz')  -> 'baz'
/// TfGetExtension('/foo/bar/.foo.baz')     -> 'baz'
/// TfGetExtension('/foo/bar/.foo')         -> ''
TF_API
std::string TfGetExtension(std::string const& path);

/// Returns the value of a symbolic link.  Returns the empty string on
/// error or if path is not a symbolic link.
TF_API
std::string TfReadLink(std::string const& path);

/// Return true if and only if a path is relative (not absolute).
TF_API
bool TfIsRelativePath(std::string const& path);

/// Expands one or more shell glob patterns.
///
/// This is a wrapper to glob(3), which manages the C structures necessary to
/// glob a pattern, returning a std::vector of results. If no flags are
/// specified, the GLOB_MARK and GLOB_NOCHECK flags are set by default.
/// GLOB_MARK marks directories which match the glob pattern with a trailing
/// slash. GLOB_NOCHECK returns any unexpanded patterns in the result.
TF_API
std::vector<std::string> TfGlob(std::vector<std::string> const& paths,
                                unsigned int flags=ARCH_GLOB_DEFAULT);

/// Expands a shell glob pattern.
///
/// This form of Glob calls TfGlob.  For efficiency reasons, if expanding more
/// than one pattern, use the vector form.  As with the vector form of TfGlob,
/// if flags is not set, the default glob flags are GLOB_MARK and
/// GLOB_NOCHECK.
TF_API
std::vector<std::string> TfGlob(std::string const& path,
                                unsigned int flags=ARCH_GLOB_DEFAULT);

FORGE_NAMESPACE_END

#endif /* FORGE_BASE_TF_PATH_UTILS_H */