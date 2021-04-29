from __future__ import print_function

from distutils.spawn import find_executable

import argparse
import textwrap
import codecs
import contextlib
import ctypes
import datetime
import distutils
import fnmatch
import glob
import locale
import multiprocessing
import os
import platform
import re
import shlex
import shutil
import subprocess
import sys
import sysconfig
import tarfile
import zipfile
import rarfile

if sys.version_info.major >= 3:
    from urllib.request import urlopen
else:
    from urllib2 import urlopen

# Helpers for printing output
verbosity = 1

def Print(msg):
    if verbosity > 0:
        print(msg)

def PrintWarning(warning):
    if verbosity > 0:
        print("WARNING:", warning)

def PrintStatus(status):
    if verbosity >= 1:
        print("STATUS:", status)

def PrintInfo(info):
    if verbosity >= 2:
        print("INFO:", info)

def PrintCommandOutput(output):
    if verbosity >= 3:
        sys.stdout.write(output)

def PrintError(error):
    if verbosity >= 3 and sys.exc_info()[1] is not None:
        import traceback
        traceback.print_exc()
    print ("ERROR:", error)

# Helpers for determining platform
def Windows():
    return platform.system() == "Windows"
def Linux():
    return platform.system() == "Linux"
def MacOS():
    return platform.system() == "Darwin"

INSTALL_DIR = ""
if Windows():
    INSTALL_DIR = "../../../lib/win64_vc15"
elif Linux():
    INSTALL_DIR = "../../../lib/linux_centos7_x86_64"

SOURCE_DIR = "../../../lib/win64_vc15/build_env/source"
BUILD_DIR = "../../../lib/win64_vc15/build_env/build"

def Python3():
    return sys.version_info.major == 3

def GetLocale():
    return sys.stdout.encoding or locale.getdefaultlocale()[1] or "UTF-8"

def GetCommandOutput(command):
    """Executes the specified command and returns output or None."""
    try:
        return subprocess.check_output(
            shlex.split(command),
            stderr=subprocess.STDOUT).decode(GetLocale(), 'replace').strip()
    except subprocess.CalledProcessError:
        pass
    return None

def GetXcodeDeveloperDirectory():
    """Returns the active developer directory as reported by 'xcode-select -p'.
    Returns None if none is set."""
    if not MacOS():
        return None

    return GetCommandOutput("xcode-select -p")

def GetVisualStudioCompilerAndVersion():
    """Returns a tuple containing the path to the Visual Studio compiler
    and a tuple for its version, e.g. (14, 0). If the compiler is not found
    or version number cannot be determined, returns None."""
    if not Windows():
        return None

    msvcCompiler = find_executable('cl')
    if msvcCompiler:
        # VisualStudioVersion environment variable should be set by the
        # Visual Studio Command Prompt.
        match = re.search(
            r"(\d+)\.(\d+)",
            os.environ.get("VisualStudioVersion", ""))
        if match:
            return (msvcCompiler, tuple(int(v) for v in match.groups()))
    return None

def IsVisualStudioVersionOrGreater(desiredVersion):
    if not Windows():
        return False

    msvcCompilerAndVersion = GetVisualStudioCompilerAndVersion()
    if msvcCompilerAndVersion:
        _, version = msvcCompilerAndVersion
        return version >= desiredVersion
    return False

def IsVisualStudio2019OrGreater():
    VISUAL_STUDIO_2019_VERSION = (16, 0)
    return IsVisualStudioVersionOrGreater(VISUAL_STUDIO_2019_VERSION)

def IsVisualStudio2017OrGreater():
    VISUAL_STUDIO_2017_VERSION = (15, 0)
    return IsVisualStudioVersionOrGreater(VISUAL_STUDIO_2017_VERSION)

def IsVisualStudio2015OrGreater():
    VISUAL_STUDIO_2015_VERSION = (14, 0)
    return IsVisualStudioVersionOrGreater(VISUAL_STUDIO_2015_VERSION)

def GetPythonInfo():

    python_version = "3.9"
    python_version_no_dot = "39"

    def _GetPythonLibraryFilename():
        if Windows():
            return "python" + python_version_no_dot + ".lib"
        elif Linux():
            return "libpython" + python_version + ".a"
        elif MacOS():
            return "libpython" + python_version + ".dylib"
        else:
            raise RuntimeError("Platform not supported")

    def _GetPythonEXEFilename():
        if Windows():
            return "python" + ".exe"
        elif Linux():
            return "python" + python_version + ".so"
        elif MacOS():
            return "python" + python_version + ".so"
        else:
            raise RuntimeError("Platform not supported")


    python_dir     = ""
    python_include = ""
    python_lib     = ""
    python_exe     = ""


    if Windows():
        python_dir     = os.path.join(os.path.dirname(os.path.realpath(__file__)), f"../../../lib/win64_vc15/python/{python_version_no_dot}")
        python_include = os.path.join(python_dir, "include")
        python_lib     = os.path.join(python_dir, "libs")
        python_exe     = os.path.join(python_dir, "bin", _GetPythonEXEFilename())
    elif Linux():
        python_dir     = os.path.join(os.path.dirname(os.path.realpath(__file__)), "../../../lib/linux_centos7_x86_64/python")
        python_include = os.path.join(python_dir, "include")
        python_lib     = os.path.join(python_dir, "lib", _GetPythonLibraryFilename())
        python_exe     = os.path.join(python_dir, "bin", _GetPythonEXEFilename())
    elif MacOS():
        python_dir     = os.path.join(os.path.dirname(os.path.realpath(__file__)), "../../../lib/FIX_ME/python")
        python_include = os.path.join(python_dir, "include")
        python_lib     = os.path.join(python_dir, "lib", _GetPythonLibraryFilename())
        python_exe     = os.path.join(python_dir, "bin", _GetPythonEXEFilename())
    else:
        raise RuntimeError("Platform not supported")

    python_info = {"python_include": python_include.replace('\\', '/'),
                   "python_lib": python_lib.replace('\\', '/'),
                   "python_exe": python_exe.replace('\\', '/'),
                   "python_version": python_version}

    return python_info

def GetCPUCount():
    try:
        return multiprocessing.cpu_count()
    except NotImplementedError:
        return 1

def Run(cmd, logCommandOutput = True):
    """Run the specified command in a subprocess."""
    PrintInfo('Running "{cmd}"'.format(cmd=cmd))

    with codecs.open("log.txt", "a", "utf-8") as logfile:
        logfile.write(datetime.datetime.now().strftime("%Y-%m-%d %H:%M"))
        logfile.write("\n")
        logfile.write(cmd)
        logfile.write("\n")

        # Let exceptions escape from subprocess calls -- higher level
        # code will handle them.
        if logCommandOutput:
            p = subprocess.Popen(shlex.split(cmd), stdout=subprocess.PIPE,
                                 stderr=subprocess.STDOUT)
            while True:
                l = p.stdout.readline().decode(GetLocale(), 'replace')
                if l:
                    logfile.write(l)
                    PrintCommandOutput(l)
                elif p.poll() is not None:
                    break
        else:
            p = subprocess.Popen(shlex.split(cmd))
            p.wait()

    if p.returncode != 0:
        # If verbosity >= 3, we'll have already been printing out command output
        # so no reason to print the log file again.
        if verbosity < 3:
            with open("log.txt", "r") as logfile:
                Print(logfile.read())
        raise RuntimeError("Failed to run '{cmd}'\nSee {log} for more details."
                           .format(cmd=cmd, log=os.path.abspath("log.txt")))

@contextlib.contextmanager
def CurrentWorkingDirectory(dir):
    """Context manager that sets the current working directory to the given
    directory and resets it to the original directory when closed."""
    curdir = os.getcwd()
    os.chdir(dir)
    try: yield
    finally: os.chdir(curdir)

def CopyFiles(context, src, dest):
    """Copy files like shutil.copy, but src may be a glob pattern."""
    filesToCopy = glob.glob(src)
    if not filesToCopy:
        raise RuntimeError("File(s) to copy {src} not found".format(src=src))

    instDestDir = os.path.join(context.libInstDir, dest)
    for f in filesToCopy:
        PrintCommandOutput("Copying {file} to {destDir}\n"
                           .format(file=f, destDir=instDestDir))
        shutil.copy(f, instDestDir)

def CopyDirectory(context, srcDir, destDir):
    """Copy directory like shutil.copytree."""
    instDestDir = os.path.join(context.libInstDir, destDir)
    if os.path.isdir(instDestDir):
        shutil.rmtree(instDestDir)

    PrintCommandOutput("Copying {srcDir} to {destDir}\n"
                       .format(srcDir=srcDir, destDir=instDestDir))
    shutil.copytree(srcDir, instDestDir)

def FormatMultiProcs(numJobs, generator):
    tag = "-j"
    if generator:
        if "Visual Studio" in generator:
            tag = "/M:"
        elif "Xcode" in generator:
            tag = "-j "

    return "{tag}{procs}".format(tag=tag, procs=numJobs)

def RunCMake(context, force, extraArgs = None):
    """Invoke CMake to configure, build, and install a library whose
    source code is located in the current working directory."""
    # Create a directory for out-of-source builds in the build directory
    # using the name of the current working directory.
    srcDir = os.getcwd()
    libInstDir = (context.libInstDir)
    buildDir = os.path.join(context.buildDir, os.path.split(srcDir)[1])
    if force and os.path.isdir(buildDir):
        shutil.rmtree(buildDir)

    if not os.path.isdir(buildDir):
        os.makedirs(buildDir)

    generator = context.cmakeGenerator

    # On Windows, we need to explicitly specify the generator to ensure we're
    # building a 64-bit project. (Surely there is a better way to do this?)
    # TODO: figure out exactly what "vcvarsall.bat x64" sets to force x64
    if generator is None and Windows():
        if IsVisualStudio2019OrGreater():
            generator = "Visual Studio 16 2019"
        elif IsVisualStudio2017OrGreater():
            generator = "Visual Studio 15 2017 Win64"
        else:
            generator = "Visual Studio 14 2015 Win64"

    if generator is not None:
        generator = '-G "{gen}"'.format(gen=generator)

    if IsVisualStudio2019OrGreater():
        generator = generator + " -A x64"

    toolset = context.cmakeToolset
    if toolset is not None:
        toolset = '-T "{toolset}"'.format(toolset=toolset)

    # On MacOS, enable the use of @rpath for relocatable builds.
    osx_rpath = None
    if MacOS():
        osx_rpath = "-DCMAKE_MACOSX_RPATH=ON"

    # We use -DCMAKE_BUILD_TYPE for single-configuration generators
    # (Ninja, make), and --config for multi-configuration generators
    # (Visual Studio); technically we don't need BOTH at the same
    # time, but specifying both is simpler than branching
    config=("Debug" if context.buildDebug else "Release")

    with CurrentWorkingDirectory(buildDir):
        Run('cmake '
            '-DCMAKE_INSTALL_PREFIX="{libInstDir}" '
            '-DCMAKE_PREFIX_PATH="{libInstDir}" '
            '-DCMAKE_BUILD_TYPE={config} '
            '{osx_rpath} '
            '{generator} '
            '{toolset} '
            '{extraArgs} '
            '"{srcDir}"'
            .format(libInstDir=libInstDir,
                    depsInstDir=context.libInstDir,
                    config=config,
                    srcDir=srcDir,
                    osx_rpath=(osx_rpath or ""),
                    generator=(generator or ""),
                    toolset=(toolset or ""),
                    extraArgs=(" ".join(extraArgs) if extraArgs else "")))
        Run("cmake --build . --config {config} --target install -- {multiproc}"
            .format(config=config,
                    multiproc=FormatMultiProcs(context.numJobs, generator)))

def GetCMakeVersion():
    """
    Returns the CMake version as tuple of integers (major, minor) or
    (major, minor, patch) or None if an error occured while launching cmake and
    parsing its output.
    """

    output_string = GetCommandOutput("cmake --version")
    if not output_string:
        PrintWarning("Could not determine cmake version -- please install it "
                     "and adjust your PATH")
        return None

    # cmake reports, e.g., "... version 3.14.3"
    match = re.search(r"version (\d+)\.(\d+)(\.(\d+))?", output_string)
    if not match:
        PrintWarning("Could not determine cmake version")
        return None

    major, minor, patch_group, patch = match.groups()
    if patch_group is None:
        return (int(major), int(minor))
    else:
        return (int(major), int(minor), int(patch))

def PatchFile(filename, patches, multiLineMatches=False):
    """Applies patches to the specified file. patches is a list of tuples
    (old string, new string)."""
    if multiLineMatches:
        oldLines = [open(filename, 'r').read()]
    else:
        oldLines = open(filename, 'r').readlines()
    newLines = oldLines
    for (oldString, newString) in patches:
        newLines = [s.replace(oldString, newString) for s in newLines]
    if newLines != oldLines:
        PrintInfo("Patching file {filename} (original in {oldFilename})..."
                  .format(filename=filename, oldFilename=filename + ".old"))
        shutil.copy(filename, filename + ".old")
        open(filename, 'w').writelines(newLines)

def DownloadFileWithCurl(url, outputFilename):
    # Don't log command output so that curl's progress
    # meter doesn't get written to the log file.
    Run("curl {progress} -L -o {filename} {url}".format(
        progress="-#" if verbosity >= 2 else "-s",
        filename=outputFilename, url=url),
        logCommandOutput=False)

def DownloadFileWithPowershell(url, outputFilename):
    # It's important that we specify to use TLS v1.2 at least or some
    # of the downloads will fail.
    cmd = "powershell [Net.ServicePointManager]::SecurityProtocol = \
            [Net.SecurityProtocolType]::Tls12; \"(new-object \
            System.Net.WebClient).DownloadFile('{url}', '{filename}')\""\
            .format(filename=outputFilename, url=url)

    Run(cmd,logCommandOutput=False)

def DownloadFileWithUrllib(url, outputFilename):
    r = urlopen(url)
    with open(outputFilename, "wb") as outfile:
        outfile.write(r.read())

def DownloadURL(url, context, force, dontExtract = None):
    """Download and extract the archive file at given URL to the
    source directory specified in the context.

    dontExtract may be a sequence of path prefixes that will
    be excluded when extracting the archive.

    Returns the absolute path to the directory where files have
    been extracted."""
    with CurrentWorkingDirectory(context.srcDir):
        # Extract filename from URL and see if file already exists.
        filename = url.split("/")[-1]

        if os.path.exists(filename):
            os.remove(filename)

        if os.path.exists(filename):
            PrintInfo("{0} already exists, skipping download".format(os.path.abspath(filename)))
        else:
            PrintInfo("Downloading {0} to {1}"
                      .format(url, os.path.abspath(filename)))

            # To work around occasional hiccups with downloading from websites
            # (SSL validation errors, etc.), retry a few times if we don't
            # succeed in downloading the file.
            maxRetries = 5
            lastError = None

            # Download to a temporary file and rename it to the expected
            # filename when complete. This ensures that incomplete downloads
            # will be retried if the script is run again.
            tmpFilename = filename + ".tmp"
            if os.path.exists(tmpFilename):
                os.remove(tmpFilename)

            for i in range(maxRetries):
                try:
                    context.downloader(url, tmpFilename)
                    break
                except Exception as e:
                    PrintCommandOutput("Retrying download due to error: {err}\n"
                                       .format(err=e))
                    lastError = e
            else:
                errorMsg = str(lastError)
                if "SSL: TLSV1_ALERT_PROTOCOL_VERSION" in errorMsg:
                    errorMsg += ("\n\n"
                                 "Your OS or version of Python may not support "
                                 "TLS v1.2+, which is required for downloading "
                                 "files from certain websites. This support "
                                 "was added in Python 2.7.9."
                                 "\n\n"
                                 "You can use curl to download dependencies "
                                 "by installing it in your PATH and re-running "
                                 "this script.")
                raise RuntimeError("Failed to download {url}: {err}"
                                   .format(url=url, err=errorMsg))

            shutil.move(tmpFilename, filename)

        # Open the archive and retrieve the name of the top-most directory.
        # This assumes the archive contains a single directory with all
        # of the contents beneath it.
        archive = None
        rootDir = None
        members = None

        try:
            if tarfile.is_tarfile(filename):
                archive = tarfile.open(filename)
                rootDir = archive.getnames()[0].split('/')[0]
                if dontExtract != None:
                    members = (m for m in archive.getmembers()
                               if not any((fnmatch.fnmatch(m.name, p)
                                           for p in dontExtract)))

            elif zipfile.is_zipfile(filename):
                archive = zipfile.ZipFile(filename)
                rootDir = archive.namelist()[0].split('/')[0]
                if dontExtract != None:
                    members = (m for m in archive.getnames()
                               if not any((fnmatch.fnmatch(m, p)
                                           for p in dontExtract)))
                                           
            elif rarfile.is_rarfile(filename):
                archive = rarfile.RarFile(filename)
                rootDir = archive.namelist()[0].split('/')[0]
                if dontExtract != None:
                    members = (m for m in archive.getnames()
                               if not any((fnmatch.fnmatch(m, p)
                                           for p in dontExtract)))

            else:
                raise RuntimeError("unrecognized archive file type")

            with archive:
                extractedPath = os.path.abspath(rootDir)
                if force and os.path.isdir(extractedPath):
                    shutil.rmtree(extractedPath)

                if os.path.isdir(extractedPath):
                    PrintInfo("Directory {0} already exists, skipping extract".format(extractedPath))
                else:
                    PrintInfo("Extracting archive to {0}".format(extractedPath))

                    # Extract to a temporary directory then move the contents
                    # to the expected location when complete. This ensures that
                    # incomplete extracts will be retried if the script is run
                    # again.
                    tmpExtractedPath = os.path.abspath("extract_dir")
                    if os.path.isdir(tmpExtractedPath):
                        shutil.rmtree(tmpExtractedPath)

                    archive.extractall(tmpExtractedPath, members=members)

                    shutil.move(os.path.join(tmpExtractedPath, rootDir),
                                extractedPath)
                    shutil.rmtree(tmpExtractedPath)

                return extractedPath
        except Exception as e:
            # If extraction failed for whatever reason, assume the
            # archive file was bad and move it aside so that re-running
            # the script will try downloading and extracting again.
            shutil.move(filename, filename + ".bad")
            raise RuntimeError("Failed to extract archive {filename}: {err}".format(filename=filename, err=e))

############################################################
# 3rd-Party Dependencies

AllDependencies = list()
AllDependenciesByName = dict()

class Dependency(object):
    def __init__(self, name, installer, *files):
        self.name = name
        self.installer = installer
        self.filesToCheck = files

        AllDependencies.append(self)
        AllDependenciesByName.setdefault(name.lower(), self)

    def Exists(self, context):
        return all([os.path.isfile(os.path.join(context.libInstDir, f))
                    for f in self.filesToCheck])

class PythonDependency(object):
    def __init__(self, name, getInstructions, moduleNames):
        self.name = name
        self.getInstructions = getInstructions
        self.moduleNames = moduleNames

    def Exists(self, context):
        # If one of the modules in our list imports successfully, we are good.
        for moduleName in self.moduleNames:
            try:
                pyModule = __import__(moduleName)
                return True
            except:
                pass

        return False

def AnyPythonDependencies(deps):
    return any([type(d) is PythonDependency for d in deps])

############################################################
# zlib

ZLIB_URL = "https://github.com/madler/zlib/archive/refs/tags/v1.2.11.zip"

def InstallZlib(context, force, buildArgs):
    context.libInstDir = INSTALL_DIR + "/zlib1.2.11"
    with CurrentWorkingDirectory(DownloadURL(ZLIB_URL, context, force)):
        RunCMake(context, force, buildArgs)

ZLIB = Dependency("zlib", InstallZlib, "include/zlib.h")

############################################################
# boost

if MacOS():
    BOOST_URL = "https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.gz"
    BOOST_VERSION_FILE = "include/boost/version.hpp"
elif Linux():
    if Python3():
        BOOST_URL = "https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.gz"
    else:
        BOOST_URL = "https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.gz"
    BOOST_VERSION_FILE = "include/boost/version.hpp"
elif Windows():
    # The default installation of boost on Windows puts headers in a versioned
    # subdirectory, which we have to account for here. In theory, specifying
    # "layout=system" would make the Windows install match Linux/MacOS, but that
    # causes problems for other dependencies that look for boost.
    #
    # boost 1.70 is required for Visual Studio 2019. For simplicity, we use
    # this version for all older Visual Studio versions as well.
    BOOST_URL = "https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.zip"
    BOOST_VERSION_FILE = "include/boost-1_76/boost/version.hpp"

def InstallBoost_Helper(context, force, buildArgs):
    force = True
    # Documentation files in the boost archive can have exceptionally
    # long paths. This can lead to errors when extracting boost on Windows,
    # since paths are limited to 260 characters by default on that platform.
    # To avoid this, we skip extracting all documentation.
    #
    # For some examples, see: https://svn.boost.org/trac10/ticket/11677
    dontExtract = ["*/doc/*", "*/libs/*/doc/*"]

    with CurrentWorkingDirectory(DownloadURL(BOOST_URL, context, force, dontExtract)):
        bootstrap = "bootstrap.bat" if Windows() else "./bootstrap.sh"
        Run('{bootstrap} --prefix="{libInstDir}"'.format(bootstrap=bootstrap, libInstDir=context.libInstDir + "/boost"))

        # b2 supports at most -j64 and will error if given a higher value.
        num_procs = min(64, context.numJobs)

        boost_user_config_jam = "{buildDir}/boost.user-config.jam".format(buildDir=context.buildDir)
        boost_build_options = [
            '--prefix="{libInstDir}"'.format(libInstDir=context.libInstDir + "/boost"),
            '--build-dir="{buildDir}"'.format(buildDir=context.buildDir),
            '-j{procs}'.format(procs=num_procs),
            'address-model=64',
            'link=shared',
            'runtime-link=shared',
            'threading=multi',
            'variant={variant}'.format(variant="debug" if context.buildDebug else "release"),
            '--with-atomic',
            '--with-program_options',
            '--with-regex',
            '--with-python',
            '--with-date_time',
            '--with-system',
            '--with-thread',
            '--with-iostreams',
            "--with-filesystem",
            '-sNO_BZIP2=1',
            '--user-config={boost_user_config_jam}'.format(boost_user_config_jam=boost_user_config_jam).replace('\\', '/'),
        ]

        pythonInfo = GetPythonInfo()
        PYTHON_SHORT_VERSION =  pythonInfo["python_version"]
        PYTHON_BINARY        =  pythonInfo["python_exe"]
        PYTHON_INCLUDE       =  pythonInfo["python_include"]
        PYTHON_LIB           =  pythonInfo["python_lib"]

        with open(boost_user_config_jam, 'w') as patch_boost:
            patch_boost.write(f'using python : {PYTHON_SHORT_VERSION} : {PYTHON_BINARY}\n')
            patch_boost.write(f' : {PYTHON_INCLUDE}\n')
            patch_boost.write(f' : {PYTHON_LIB}\n')
            patch_boost.write(f';')
            patch_boost.close()

        if force:
            boost_build_options.append("-a")

        if Windows():
            # toolset parameter for Visual Studio documented here:
            # https://github.com/boostorg/build/blob/develop/src/tools/msvc.jam
            if context.cmakeToolset == "v142":
                boost_build_options.append("toolset=msvc-14.2")
            elif context.cmakeToolset == "v141":
                boost_build_options.append("toolset=msvc-14.1")
            elif context.cmakeToolset == "v140":
                boost_build_options.append("toolset=msvc-14.0")
            elif IsVisualStudio2019OrGreater():
                boost_build_options.append("toolset=msvc-14.2")
            elif IsVisualStudio2017OrGreater():
                boost_build_options.append("toolset=msvc-14.1")
            else:
                boost_build_options.append("toolset=msvc-14.2")

        if MacOS():
            # Must specify toolset=clang to ensure install_name for boost
            # libraries includes @rpath
            boost_build_options.append("toolset=clang")

        # Add on any user-specified extra arguments.
        # boost_build_options += buildArgs

        build_command = "b2" if Windows() else "./b2"
        Run('{build_command} {options} install'.format(build_command=build_command, options=" ".join(boost_build_options)))

def InstallBoost(context, force, buildArgs):
    # Boost's build system will install the version.hpp header before
    # building its libraries. We make sure to remove it in case of
    # any failure to ensure that the build script detects boost as a
    # dependency to build the next time it's run.
    try:
        InstallBoost_Helper(context, force, buildArgs)
    except:
        versionHeader = os.path.join(context.libInstDir + "/boost", BOOST_VERSION_FILE)
        if os.path.isfile(versionHeader):
            try: os.remove(versionHeader)
            except: pass
        raise

BOOST = Dependency("boost", InstallBoost, BOOST_VERSION_FILE)

############################################################
# Intel TBB

if Windows():
    TBB_URL = "https://github.com/oneapi-src/oneTBB/releases/download/v2021.1.1/oneapi-tbb-2021.1.1-win.zip"
else:
    TBB_URL = "https://github.com/oneapi-src/oneTBB/archive/2017_U6.tar.gz"

def InstallTBB(context, force, buildArgs):
    if Windows():
        InstallTBB_Windows(context, force, buildArgs)
    elif Linux() or MacOS():
        InstallTBB_LinuxOrMacOS(context, force, buildArgs)

def InstallTBB_Windows(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(TBB_URL, context, force)):
        # On Windows, we simply copy headers and pre-built DLLs to
        # the appropriate location.

        # if buildArgs:
        #     PrintWarning("Ignoring build arguments {}, TBB is "
        #                  "not built from source on this platform."
        #                  .format(buildArgs))

        CopyFiles(context, "bin\\intel64\\vc14\\*.*", "bin")
        CopyFiles(context, "lib\\intel64\\vc14\\*.*", "lib")
        CopyDirectory(context, "include\\serial", "include\\serial")
        CopyDirectory(context, "include\\tbb", "include\\tbb")

def InstallTBB_LinuxOrMacOS(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(TBB_URL, context, force)):
        # Note: TBB installation fails on OSX when cuda is installed, a
        # suggested fix:
        # https://github.com/spack/spack/issues/6000#issuecomment-358817701
        if MacOS():
            PatchFile("build/macos.inc",
                    [("shell clang -v ", "shell clang --version ")])
        # TBB does not support out-of-source builds in a custom location.
        Run('make -j{procs} {buildArgs}'
            .format(procs=context.numJobs,
                    buildArgs=" ".join(buildArgs)))

        # Install both release and debug builds. USD requires the debug
        # libraries when building in debug mode, and installing both
        # makes it easier for users to install dependencies in some
        # location that can be shared by both release and debug USD
        # builds. Plus, the TBB build system builds both versions anyway.
        CopyFiles(context, "build/*_release/libtbb*.*", "lib")
        CopyFiles(context, "build/*_debug/libtbb*.*", "lib")
        CopyDirectory(context, "include/serial", "include/serial")
        CopyDirectory(context, "include/tbb", "include/tbb")

TBB = Dependency("TBB", InstallTBB, "include/tbb/tbb.h")

############################################################
# JPEG

if Windows():
    JPEG_URL = "https://storage.googleapis.com/dependency_links/libjpeg-turbo-2.0.90.zip"
else:
    JPEG_URL = "https://www.ijg.org/files/jpegsrc.v9b.tar.gz"

def InstallJPEG(context, force, buildArgs):
    if Windows():
        InstallJPEG_Turbo(context, force, buildArgs)
    else:
        InstallJPEG_Lib(context, force, buildArgs)

def InstallJPEG_Turbo(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(JPEG_URL, context, force)):
        RunCMake(context, force, buildArgs)

def InstallJPEG_Lib(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(JPEG_URL, context, force)):
        Run('./configure --prefix="{libInstDir}" '
            '--disable-static --enable-shared '
            '{buildArgs}'
            .format(libInstDir=context.libInstDir,
                    buildArgs=" ".join(buildArgs)))
        Run('make -j{procs} install'
            .format(procs=context.numJobs))

JPEG = Dependency("JPEG", InstallJPEG, "include/jpeglib.h")

############################################################
# TIFF

TIFF_URL = "https://gitlab.com/libtiff/libtiff/-/archive/v4.2.0/libtiff-v4.2.0.zip"

def InstallTIFF(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(TIFF_URL, context, force)):
        # libTIFF has a build issue on Windows where tools/tiffgt.c
        # unconditionally includes unistd.h, which does not exist.
        # To avoid this, we patch the CMakeLists.txt to skip building
        # the tools entirely. We do this on Linux and MacOS as well
        # to avoid requiring some GL and X dependencies.
        #
        # We also need to skip building tests, since they rely on
        # the tools we've just elided.
        PatchFile("CMakeLists.txt",
                   [("add_subdirectory(tools)", "# add_subdirectory(tools)"),
                    ("add_subdirectory(test)", "# add_subdirectory(test)")])

        # The libTIFF CMakeScript says the ld-version-script
        # functionality is only for compilers using GNU ld on
        # ELF systems or systems which provide an emulation; therefore
        # skipping it completely on mac and windows.
        if MacOS() or Windows():
            extraArgs = ["-Dld-version-script=OFF"]
        else:
            extraArgs = []
        extraArgs += buildArgs
        RunCMake(context, force, extraArgs)

TIFF = Dependency("TIFF", InstallTIFF, "include/tiff.h")

############################################################
# PNG

PNG_URL = "https://github.com/glennrp/libpng/archive/refs/tags/v1.6.35.zip"

def InstallPNG(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(PNG_URL, context, force)):
        RunCMake(context, force, buildArgs)

PNG = Dependency("PNG", InstallPNG, "include/png.h")

############################################################
# IlmBase/OpenEXR

OPENEXR_URL   = "https://github.com/openexr/openexr/archive/v3.0.0-beta.zip"
# IMATH_URL = "https://github.com/AcademySoftwareFoundation/Imath/archive/refs/tags/v3.0.0-beta.zip"

def InstallOpenEXR(context, force, buildArgs):
    srcDir = DownloadURL(OPENEXR_URL, context, force)

    # ilmbaseSrcDir = os.path.join(srcDir, "")
    # with CurrentWorkingDirectory(ilmbaseSrcDir):
    #     # openexr 2.2 has a bug with Ninja:
    #     # https://github.com/openexr/openexr/issues/94
    #     # https://github.com/openexr/openexr/pull/142
    #     # Fix commit here:
    #     # https://github.com/openexr/openexr/commit/8eed7012c10f1a835385d750fd55f228d1d35df9
    #     # Merged here:
    #     # https://github.com/openexr/openexr/commit/b206a243a03724650b04efcdf863c7761d5d5d5b
    #     if context.cmakeGenerator == "Ninja":
    #         PatchFile(
    #             os.path.join('Half', 'CMakeLists.txt'),
    #             [
    #                 ("TARGET eLut POST_BUILD",
    #                  "OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/eLut.h"),
    #                 ("  COMMAND eLut > ${CMAKE_CURRENT_BINARY_DIR}/eLut.h",
    #                  "  COMMAND eLut ARGS > ${CMAKE_CURRENT_BINARY_DIR}/eLut.h\n"
    #                     "  DEPENDS eLut"),
    #                 ("TARGET toFloat POST_BUILD",
    #                  "OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/toFloat.h"),
    #                 ("  COMMAND toFloat > ${CMAKE_CURRENT_BINARY_DIR}/toFloat.h",
    #                  "  COMMAND toFloat ARGS > ${CMAKE_CURRENT_BINARY_DIR}/toFloat.h\n"
    #                     "  DEPENDS toFloat"),

    #                 ("  ${CMAKE_CURRENT_BINARY_DIR}/eLut.h\n"
    #                      "  OBJECT_DEPENDS\n"
    #                      "  ${CMAKE_CURRENT_BINARY_DIR}/toFloat.h\n",
    #                  '  "${CMAKE_CURRENT_BINARY_DIR}/eLut.h;${CMAKE_CURRENT_BINARY_DIR}/toFloat.h"\n'),
    #             ],
    #             multiLineMatches=True)
    #     RunCMake(context, force, buildArgs)

    openexrSrcDir = os.path.join(srcDir, "")
    with CurrentWorkingDirectory(openexrSrcDir):
        RunCMake(context, force,
                 ['-DILMBASE_PACKAGE_PREFIX="{libInstDir}"'
                  .format(libInstDir=context.libInstDir)] + buildArgs)

OPENEXR = Dependency("OpenEXR", InstallOpenEXR, "include/OpenEXR/ImfVersion.h")

############################################################
# Ptex

PTEX_URL = "https://github.com/wdas/ptex/archive/v2.3.2.zip"

def InstallPtex(context, force, buildArgs):
    if Windows():
        InstallPtex_Windows(context, force, buildArgs)
    else:
        InstallPtex_LinuxOrMacOS(context, force, buildArgs)

def InstallPtex_Windows(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(PTEX_URL, context, force)):
        # Ptex has a bug where the import library for the dynamic library and
        # the static library both get the same name, Ptex.lib, and as a
        # result one clobbers the other. We hack the appropriate CMake
        # file to prevent that. Since we don't need the static library we'll
        # rename that.
        #
        # In addition src\tests\CMakeLists.txt adds -DPTEX_STATIC to the
        # compiler but links tests against the dynamic library, causing the
        # links to fail. We patch the file to not add the -DPTEX_STATIC
        PatchFile('src\\ptex\\CMakeLists.txt',
                  [("set_target_properties(Ptex_static PROPERTIES OUTPUT_NAME Ptex)",
                    "set_target_properties(Ptex_static PROPERTIES OUTPUT_NAME Ptexs)")])
        PatchFile('src\\tests\\CMakeLists.txt',
                  [("add_definitions(-DPTEX_STATIC)",
                    "# add_definitions(-DPTEX_STATIC)")])

        # Patch Ptex::String to export symbol for operator<<
        # This is required for newer versions of OIIO, which make use of the
        # this operator on Windows platform specifically.
        PatchFile('src\\ptex\\Ptexture.h',
                  [("std::ostream& operator << (std::ostream& stream, const Ptex::String& str);",
                    "PTEXAPI std::ostream& operator << (std::ostream& stream, const Ptex::String& str);")])


        RunCMake(context, force, buildArgs)

def InstallPtex_LinuxOrMacOS(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(PTEX_URL, context, force)):
        RunCMake(context, force, buildArgs)

PTEX = Dependency("Ptex", InstallPtex, "include/PtexVersion.h")

############################################################
# BLOSC (Compression used by OpenVDB)

# Using latest blosc since neither the version OpenVDB recommends
# (1.5) nor the version we test against (1.6.1) compile on Mac OS X
# Sierra (10.12) or Mojave (10.14).
BLOSC_URL = "https://github.com/Blosc/c-blosc/archive/refs/tags/v1.21.0.zip"

def InstallBLOSC(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(BLOSC_URL, context, force)):
        RunCMake(context, force, buildArgs)

BLOSC = Dependency("Blosc", InstallBLOSC, "include/blosc.h")

############################################################
# OpenVDB

# Using version 6.1.0 since it has reworked its CMake files so that
# there are better options to not compile the OpenVDB binaries and to
# not require additional dependencies such as GLFW. Note that version
# 6.1.0 does require CMake 3.3 though.

OPENVDB_URL = "https://storage.googleapis.com/dependency_links/OpenVDB-8.1.0.zip"

def InstallOpenVDB(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(OPENVDB_URL, context, force)):
        extraArgs = [
            '-DOPENVDB_BUILD_PYTHON_MODULE=OFF',
            '-DOPENVDB_BUILD_BINARIES=OFF',
            '-DOPENVDB_BUILD_UNITTESTS=OFF'
        ]

        # Make sure to use boost installed by the build script and not any
        # system installed boost
        extraArgs.append('-DBoost_NO_BOOST_CMAKE=On')
        extraArgs.append('-DBoost_NO_SYSTEM_PATHS=True')

        extraArgs.append('-DBLOSC_ROOT="{libInstDir}"'.format(libInstDir='C:/Users/tyler/dev/lib/win64_vc15/blosc'))
        extraArgs.append('-DTBB_ROOT="{libInstDir}"'.format(libInstDir='C:/Users/tyler/dev/lib/win64_vc15/tbb'))
        # OpenVDB needs Half type from IlmBase
        extraArgs.append('-DILMBASE_ROOT={libInstDir}'.format(libInstDir='C:/Users/tyler/dev/lib/win64_vc15/openexr'))

        # Add on any user-specified extra arguments.
        extraArgs += buildArgs

        RunCMake(context, force, extraArgs)

OPENVDB = Dependency("OpenVDB", InstallOpenVDB, "include/openvdb/openvdb.h")

############################################################
# OpenImageIO

OIIO_URL = "https://github.com/OpenImageIO/oiio/archive/Release-2.2.12.0.zip"

def InstallOpenImageIO(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(OIIO_URL, context, force)):
        extraArgs = ['-DOIIO_BUILD_TOOLS=OFF',
                     '-DOIIO_BUILD_TESTS=OFF',
                     '-DUSE_PYTHON=OFF',
                     '-DSTOP_ON_WARNING=OFF']

        # OIIO's FindOpenEXR module circumvents CMake's normal library
        # search order, which causes versions of OpenEXR installed in
        # /usr/local or other hard-coded locations in the module to
        # take precedence over the version we've built, which would
        # normally be picked up when we specify CMAKE_PREFIX_PATH.
        # This may lead to undefined symbol errors at build or runtime.
        # So, we explicitly specify the OpenEXR we want to use here.
        extraArgs.append('-DOPENEXR_HOME="{libInstDir}"'
                         .format(libInstDir=context.libInstDir))

        extraArgs.append('-DUSE_PTEX=ON')

        # Make sure to use boost installed by the build script and not any
        # system installed boost
        extraArgs.append('-DJPEGTurbo_ROOT=C:/Users/tyler/dev/lib/win64_vc15/jpeg')
        extraArgs.append('-DBoost_ROOT="C:/Users/tyler/dev/lib/win64_vc15/boost"')
        extraArgs.append('-DBoost_NO_BOOST_CMAKE=On')
        extraArgs.append('-DBoost_NO_SYSTEM_PATHS=True')

        # Add on any user-specified extra arguments.
        extraArgs += buildArgs

        RunCMake(context, force, extraArgs)

OPENIMAGEIO = Dependency("OpenImageIO", InstallOpenImageIO, "include/OpenImageIO/oiioversion.h")

############################################################
# OpenColorIO

# Use v1.1.0 on MacOS and Windows since v1.0.9 doesn't build properly on
# those platforms.
if Linux():
    OCIO_URL = "https://github.com/imageworks/OpenColorIO/archive/v1.0.9.zip"
else:
    OCIO_URL = "https://github.com/AcademySoftwareFoundation/OpenColorIO/archive/refs/tags/v2.0.0.zip"

def InstallOpenColorIO(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(OCIO_URL, context, force)):
        extraArgs = ['-DOCIO_BUILD_TRUELIGHT=OFF',
                     '-DOCIO_BUILD_APPS=OFF',
                     '-DOCIO_BUILD_NUKE=OFF',
                     '-DOCIO_BUILD_DOCS=OFF',
                     '-DOCIO_BUILD_TESTS=OFF',
                     '-DOCIO_BUILD_PYGLUE=OFF',
                     '-DOCIO_BUILD_JNIGLUE=OFF',
                     '-DOCIO_STATIC_JNIGLUE=OFF']

        # The OCIO build treats all warnings as errors but several come up
        # on various platforms, including:
        # - On gcc6, v1.1.0 emits many -Wdeprecated-declaration warnings for
        #   std::auto_ptr
        # - On clang, v1.1.0 emits a -Wself-assign-field warning. This is fixed
        #   in https://github.com/AcademySoftwareFoundation/OpenColorIO/commit/0be465feb9ac2d34bd8171f30909b276c1efa996
        #
        # To avoid build failures we force all warnings off for this build.
        if GetVisualStudioCompilerAndVersion():
            # This doesn't work because CMake stores default flags for
            # MSVC in CMAKE_CXX_FLAGS and this would overwrite them.
            # However, we don't seem to get any warnings on Windows
            # (at least with VS2015 and 2017).
            # extraArgs.append('-DCMAKE_CXX_FLAGS=/w')
            pass
        else:
            extraArgs.append('-DCMAKE_CXX_FLAGS=-w')

        # Add on any user-specified extra arguments.
        extraArgs += buildArgs

        RunCMake(context, force, extraArgs)

OPENCOLORIO = Dependency("OpenColorIO", InstallOpenColorIO,
                         "include/OpenColorIO/OpenColorABI.h")

############################################################
# OpenSubdiv

OPENSUBDIV_URL = "https://github.com/PixarAnimationStudios/OpenSubdiv/archive/refs/tags/v3_4_4.zip"

def InstallOpenSubdiv(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(OPENSUBDIV_URL, context, force)):
        extraArgs = [
            '-DNO_EXAMPLES=ON',
            '-DNO_TUTORIALS=ON',
            '-DNO_REGRESSION=ON',
            '-DNO_DOC=ON',
            '-DNO_OMP=ON',
            '-DNO_CUDA=ON',
            '-DNO_OPENCL=ON',
            '-DNO_DX=ON',
            '-DNO_TESTS=ON',
            '-DNO_GLEW=ON',
            '-DNO_GLFW=ON',
        ]

        # NOTE: For now, we disable TBB in our OpenSubdiv build.
        # This avoids an issue where OpenSubdiv will link against
        # all TBB libraries it finds, including libtbbmalloc and
        # libtbbmalloc_proxy. On Linux and MacOS, this has the
        # unwanted effect of replacing the system allocator with
        # tbbmalloc.
        extraArgs.append('-DNO_TBB=ON')

        # Add on any user-specified extra arguments.
        extraArgs += buildArgs

        # OpenSubdiv seems to error when building on windows w/ Ninja...
        # ...so just use the default generator (ie, Visual Studio on Windows)
        # until someone can sort it out
        oldGenerator = context.cmakeGenerator
        if oldGenerator == "Ninja" and Windows():
            context.cmakeGenerator = None

        # OpenSubdiv 3.3 and later on MacOS occasionally runs into build
        # failures with multiple build jobs. Workaround this by using
        # just 1 job for now. See:
        # https://github.com/PixarAnimationStudios/OpenSubdiv/issues/1194
        oldNumJobs = context.numJobs
        if MacOS():
            context.numJobs = 1

        try:
            RunCMake(context, force, extraArgs)
        finally:
            context.cmakeGenerator = oldGenerator
            context.numJobs = oldNumJobs

OPENSUBDIV = Dependency("OpenSubdiv", InstallOpenSubdiv, "include/opensubdiv/version.h")

############################################################
# OSL

OSL_URL = "https://github.com/AcademySoftwareFoundation/OpenShadingLanguage/archive/refs/tags/v1.11.12.0.zip"

def InstallOSL(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(OSL_URL, context, force)):
        extraArgs = [
            '-DBUILD_SHARED_LIBS=ON',
            '-DOSL_BUILD_TESTS=OFF',
            '-DOSL_BUILD_MATERIALX=ON',
            '-DOIIO_LIBRARY_PATH={oiio_library_path}'.format(oiio_library_path="C:/Users/tyler/dev/lib/win64_vc15/lib"),
            '-DBOOST_ROOT={boost_root_path}'.format(boost_root_path="C:/Users/tyler/dev/lib/win64_vc15/boost"),
            '-Dpugixml_ROOT={pugixml_root_path}'.format(pugixml_root_path="C:/Users/tyler/dev/lib/win64_vc15/pugixml"),
            '-DLLVM_DIRECTORY={llvm_dir_path}'.format(llvm_dir_path="C:/Users/tyler/dev/lib/win64_vc15/llvm"),
            '-LLVM_LIB_DIR={llvm_library_path}'.format(llvm_library_path="C:/Users/tyler/dev/lib/win64_vc15/llvm/lib"),
            '-DLLVM_ROOT={llvm_root_path}'.format(llvm_root_path="C:/Users/tyler/dev/lib/win64_vc15/llvm"),
            '-DLLVM_ROOT_DIR={llvm_root_path}'.format(llvm_root_path="C:/Users/tyler/dev/lib/win64_vc15/llvm"),
            '-DLLVM_INCLUDES={llvm_includes}'.format(llvm_includes="C:/Users/tyler/dev/lib/win64_vc15/llvm/include"),
            '-DBISON_ROOT={bison_dir}'.format(bison_dir="C:/Users/tyler/dev/lib/win64_vc15/flex"),
            '-DFLEX_ROOT={flex_dir}'.format(flex_dir="C:/Users/tyler/dev/lib/win64_vc15/flex"),
            "-Dpartio_ROOT={partio_dir}".format(partio_dir="C:/Users/tyler/dev/lib/win64_vc15/partio"),
            "-Dpartio_DIR={partio_dir}".format(partio_dir="C:/Users/tyler/dev/lib/win64_vc15/partio")
        ]

        # Add on any user-specified extra arguments.
        extraArgs += buildArgs

        RunCMake(context, force, extraArgs)

OSL = Dependency("OSL", InstallOSL, "include/OSL/oslversion.h")

############################################################
# PyOpenGL

def GetPyOpenGLInstructions():
    return ('PyOpenGL is not installed. If you have pip '
            'installed, run "pip install PyOpenGL" to '
            'install it, then re-run this script.\n'
            'If PyOpenGL is already installed, you may need to '
            'update your PYTHONPATH to indicate where it is '
            'located.')

PYOPENGL = PythonDependency("PyOpenGL", GetPyOpenGLInstructions,
                            moduleNames=["OpenGL"])

############################################################
# PySide

def GetPySideInstructions():
    # For licensing reasons, this script cannot install PySide itself.
    if Windows():
        # There is no distribution of PySide2 for Windows for Python 2.7.
        # So use PySide instead. See the following for more details:
        # https://wiki.qt.io/Qt_for_Python/Considerations#Missing_Windows_.2F_Python_2.7_release
        return ('PySide is not installed. If you have pip '
                'installed, run "pip install PySide" '
                'to install it, then re-run this script.\n'
                'If PySide is already installed, you may need to '
                'update your PYTHONPATH to indicate where it is '
                'located.')
    else:
        return ('PySide2 is not installed. If you have pip '
                'installed, run "pip install PySide2" '
                'to install it, then re-run this script.\n'
                'If PySide2 is already installed, you may need to '
                'update your PYTHONPATH to indicate where it is '
                'located.')

PYSIDE = PythonDependency("PySide", GetPySideInstructions,
                          moduleNames=["PySide", "PySide2"])

############################################################
# HDF5

HDF5_URL = "https://github.com/HDFGroup/hdf5/archive/refs/tags/hdf5-1_13_0-rc5.zip"

def InstallHDF5(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(HDF5_URL, context, force)):
        RunCMake(context, force,
                 ['-DBUILD_TESTING=OFF',
                  '-DHDF5_BUILD_TOOLS=OFF',
                  '-DHDF5_BUILD_EXAMPLES=OFF'] + buildArgs)

HDF5 = Dependency("HDF5", InstallHDF5, "include/hdf5.h")

############################################################
# Alembic

ALEMBIC_URL = "https://github.com/alembic/alembic/archive/refs/tags/1.7.16.zip"

def InstallAlembic(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(ALEMBIC_URL, context, force)):
        cmakeOptions = ['-DUSE_BINARIES=OFF', '-DUSE_TESTS=OFF']
        # if context.enableHDF5:
            # HDF5 requires the H5_BUILT_AS_DYNAMIC_LIB macro be defined if
            # it was built with CMake as a dynamic library.
        cmakeOptions += [
            '-DUSE_HDF5=ON',
            '-DHDF5_ROOT="{libInstDir}"'.format(libInstDir="C:/Users/tyler/dev/lib/win64_vc15/hdf5"),
            '-DILMBASE_ROOT="{libInstDir}"'.format(libInstDir="C:/Users/tyler/dev/lib/win64_vc15/openexr"),
            '-DALEMBIC_ILMBASE_IMATH_LIB="{libInstDir}"'.format(libInstDir="C:/Users/tyler/dev/lib/win64_vc15/openexr/lib/Imath-3_0.lib"),
            '-DALEMBIC_ILMBASE_ILMTHREAD_LIB="{libInstDir}"'.format(libInstDir="C:/Users/tyler/dev/lib/win64_vc15/openexr/lib/IlmThread-3_0.lib"),
            '-DALEMBIC_ILMBASE_IEX_LIB="{libInstDir}"'.format(libInstDir="C:/Users/tyler/dev/lib/win64_vc15/openexr/lib/Iex-3_0.lib"),
            '-DALEMBIC_ILMBASE_HALF_LIB="{libInstDir}"'.format(libInstDir="C:/Users/tyler/dev/lib/win64_vc15/openexr/lib/Imath-3_0.lib"),
            '-DALEMBIC_ILMBASE_INCLUDE_DIRECTORY="{libInstDir}"'.format(libInstDir="C:/Users/tyler/dev/lib/win64_vc15/openexr/include/Imath"),
            '-DIMATH_DLL=ON',
            '-DCMAKE_CXX_FLAGS="-DH5_BUILT_AS_DYNAMIC_LIB"']
        # else:
        #    cmakeOptions += ['-DUSE_HDF5=OFF']

        # cmakeOptions += buildArgs

        RunCMake(context, force, cmakeOptions)

ALEMBIC = Dependency("Alembic", InstallAlembic, "include/Alembic/Abc/Base.h")

############################################################
# Draco

DRACO_URL = "https://github.com/google/draco/archive/refs/tags/1.4.1.zip"

def InstallDraco(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(DRACO_URL, context, force)):
        cmakeOptions = ['-DBUILD_USD_PLUGIN=ON']
        cmakeOptions += buildArgs
        RunCMake(context, force, cmakeOptions)

DRACO = Dependency("Draco", InstallDraco, "include/draco/compression/decode.h")

############################################################
# MaterialX

MATERIALX_URL = "https://github.com/materialx/MaterialX/releases/download/v1.38.0/MaterialX-1.38.0.zip"

def InstallMaterialX(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(MATERIALX_URL, context, force)):
        # USD requires MaterialX to be built as a shared library on Linux
        # Currently MaterialX does not support shared builds on Windows or MacOS
        cmakeOptions = []
        if Linux():
            cmakeOptions += ['-DMATERIALX_BUILD_SHARED_LIBS=ON']

        cmakeOptions += buildArgs;

        RunCMake(context, force, cmakeOptions)

MATERIALX = Dependency("MaterialX", InstallMaterialX, "include/MaterialXCore/Library.h")

############################################################
# Embree
# For MacOS we use version 3.7.0 to include a fix from Intel
# to build on Catalina.
if MacOS():
    EMBREE_URL = "https://github.com/embree/embree/archive/v3.7.0.tar.gz"
else:
    EMBREE_URL = "https://github.com/embree/embree/archive/refs/tags/v3.12.2.tar.gz"

def InstallEmbree(context, force, buildArgs):
    with CurrentWorkingDirectory(DownloadURL(EMBREE_URL, context, force)):
        extraArgs = [
            '-DTBB_ROOT={libInstDir}'.format(libInstDir="C:/Users/tyler/dev/lib/win64_vc15/tbb"),
            '-DEMBREE_TUTORIALS=OFF',
            '-DEMBREE_ISPC_SUPPORT=OFF'
        ]

        # By default Embree fails to build on Visual Studio 2015 due
        # to an internal compiler issue that is worked around via the
        # following flag. For more details see:
        # https://github.com/embree/embree/issues/157
        if IsVisualStudio2015OrGreater() and not IsVisualStudio2017OrGreater():
            extraArgs.append('-DCMAKE_CXX_FLAGS=/d2SSAOptimizer-')

        extraArgs += buildArgs

        RunCMake(context, force, extraArgs)

EMBREE = Dependency("Embree", InstallEmbree, "include/embree3/rtcore.h")

############################################################
# Install script

print("\n\n")

programDescription = """\
*** WINGG -- ENVIRONMENT BUILDER ***

Builds and installs 3rd-party dependencies to a specified location.

LIBRARIES:
The following is a list of libraries that this script
can download and build as needed:

{libraryList}

""".format(
    libraryList="{}".format("".join(["* " + d.name + "\n" for d in AllDependencies])))

parser = argparse.ArgumentParser(description=programDescription, formatter_class=argparse.RawDescriptionHelpFormatter, usage=argparse.SUPPRESS, epilog=textwrap.dedent('''\
                                                                                                                                                ::
                                                                                                                                                ::
                                                                                                                                                :: WINGG. 2021.'''), add_help=False)
parser._optionals.title = "WINGG DEPENDENCIES | COMMAND LINE OPTIONS"

group_build = parser.add_mutually_exclusive_group()
group_build.add_argument("--build",      type=str, action="append", dest="force_build", default=[], help="Download and build the specified library")
group_build.add_argument("--build-all",  action="store_true",       dest="force_all", help="Download and build all libraries")

group_cmake = parser.add_mutually_exclusive_group()
group_cmake.add_argument("--generator",  type=str, dest="generator", help="CMake generator to use when building libraries with cmake")
group_cmake.add_argument("--toolset",    type=str, dest="toolset",   help="CMake toolset to use when building libraries with cmake")


group_help = parser.add_mutually_exclusive_group()
group_help.add_argument("--help", action='help', default=argparse.SUPPRESS, help='Show this help message.')

args = parser.parse_args()

class InstallContext:
    def __init__(self, args):

        # Directory where dependencies will be installed
        self.libInstDir = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__)), INSTALL_DIR)).replace('\\', '/')

        # Directory where dependencies will be installed
        self.libInstDir = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__)), INSTALL_DIR)).replace('\\', '/')

        # Directory where dependencies will be downloaded and extracted
        self.srcDir = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__)), SOURCE_DIR)).replace('\\', '/')

        # Directory where USD and dependencies will be built
        self.buildDir = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__)), BUILD_DIR)).replace('\\', '/')

        # Determine which downloader to use.  The reason we don't simply
        # use urllib2 all the time is that some older versions of Python
        # don't support TLS v1.2, which is required for downloading some
        # dependencies.
        if find_executable("curl"):
            self.downloader = DownloadFileWithCurl
            self.downloaderName = "curl"
        elif Windows() and find_executable("powershell"):
            self.downloader = DownloadFileWithPowershell
            self.downloaderName = "powershell"
        else:
            self.downloader = DownloadFileWithUrllib
            self.downloaderName = "built-in"

        # Number of jobs
        self.numJobs = multiprocessing.cpu_count()

        # Dependencies to build
        self.forceBuild = [dep.lower() for dep in args.force_build]
        self.forceBuildAll = args.force_all

        # CMake generator and toolset
        self.cmakeGenerator = args.generator
        self.cmakeToolset = args.toolset

        self.buildDebug = False

        # - DEPENDENCIES
        self.buildBoost     = any("boost"     in dep for dep in self.forceBuild)
        self.buildPtex      = any("ptex"      in dep for dep in self.forceBuild)
        self.buildOpenVDB   = any("openvdb"   in dep for dep in self.forceBuild)
        self.buildEmbree    = any("embree"    in dep for dep in self.forceBuild)
        self.buildOIIO      = any("oiio"      in dep for dep in self.forceBuild)
        self.buildOCIO      = any("ocio"      in dep for dep in self.forceBuild)
        self.buildAlembic   = any("alembic"   in dep for dep in self.forceBuild)
        self.buildDraco     = any("draco"     in dep for dep in self.forceBuild)
        self.buildMaterialX = any("materialx" in dep for dep in self.forceBuild)
        self.buildOSL       = any("osl"       in dep for dep in self.forceBuild)

        self.buildAll       = any("all"       in dep for dep in self.forceBuild)

    def GetBuildArguments(self, dep):
        return self.forceBuild

    def ForceBuildDependency(self, dep):
        return self.forceBuildAll or dep.name.lower() in self.forceBuild

try:
    context = InstallContext(args)
except Exception as e:
    PrintError(str(e))
    sys.exit(1)

# Augment PATH on Windows so that 3rd-party dependencies can find libraries
# they depend on. In particular, this is needed for building IlmBase/OpenEXR.
extraPaths = []
extraPythonPaths = []
if Windows():
    extraPaths.append(os.path.join(context.libInstDir, "lib"))
    extraPaths.append(os.path.join(context.libInstDir, "bin"))

if extraPaths:
    paths = os.environ.get('PATH', '').split(os.pathsep) + extraPaths
    os.environ['PATH'] = os.pathsep.join(paths)

if extraPythonPaths:
    paths = os.environ.get('PYTHONPATH', '').split(os.pathsep) + extraPythonPaths
    os.environ['PYTHONPATH'] = os.pathsep.join(paths)

# Determine list of dependencies that are required based on options
# user has selected.

requiredDependencies = []

if context.buildBoost:
    requiredDependencies += [BOOST]

if context.buildAlembic:
    requiredDependencies += [ALEMBIC]

if context.buildDraco:
    requiredDependencies += [DRACO]

if context.buildMaterialX:
    requiredDependencies += [MATERIALX]

if context.buildOSL:
    requiredDependencies += [OSL]

if context.buildOpenVDB:
    requiredDependencies += [OPENVDB]

if context.buildOIIO:
    requiredDependencies += [PTEX, OPENSUBDIV, BOOST, JPEG, TIFF, PNG, OPENEXR, OPENIMAGEIO]

if context.buildAll:
    requiredDependencies += [ZLIB, PTEX, OPENSUBDIV, BLOSC, BOOST, OPENEXR, HDF5, ALEMBIC, JPEG, TIFF, PNG, OPENIMAGEIO, OPENCOLORIO, OPENVDB, TBB, EMBREE, MATERIALX, DRACO]

if context.buildOCIO:
    requiredDependencies += [PTEX, OPENSUBDIV, OPENCOLORIO]

if context.buildEmbree:
    requiredDependencies += [PTEX, OPENSUBDIV, TBB, EMBREE]

# Assume zlib already exists on Linux platforms and don't build
# our own. This avoids potential issues where a host application
# loads an older version of zlib than the one we'd build and link
# our libraries against.
if Linux():
    requiredDependencies.remove(ZLIB)

# Error out if user explicitly specified building usdview without required
# components. Otherwise, usdview will be silently disabled. This lets users
# specify "--no-python" without explicitly having to specify "--no-usdview",
# for instance.
if "--usdview" in sys.argv:
    if not context.buildUsdImaging:
        PrintError("Cannot build usdview when usdImaging is disabled.")
        sys.exit(1)
    if not context.buildPython:
        PrintError("Cannot build usdview when Python support is disabled.")
        sys.exit(1)

dependenciesToBuild = []
for dep in requiredDependencies:
    if context.ForceBuildDependency(dep) or not dep.Exists(context):
        if dep not in dependenciesToBuild:
            dependenciesToBuild.append(dep)

# Verify toolchain needed to build required dependencies
if (not find_executable("g++") and
    not find_executable("clang") and
    not GetXcodeDeveloperDirectory() and
    not GetVisualStudioCompilerAndVersion()):
    PrintError("C++ compiler not found -- please install a compiler")
    sys.exit(1)

if find_executable("python"):
    # Error out if a 64bit version of python interpreter is not found
    # Note: Ideally we should be checking the python binary found above, but
    # there is an assumption (for very valid reasons) at other places in the
    # script that the python process used to run this script will be found.
    isPython64Bit = (ctypes.sizeof(ctypes.c_voidp) == 8)
    if not isPython64Bit:
        PrintError("64bit python not found -- please install it and adjust your"
                   "PATH")
        sys.exit(1)

else:
    PrintError("python not found -- please ensure python is included in your "
               "PATH")
    sys.exit(1)

if find_executable("cmake"):
    # Check cmake requirements
    if Windows():
        # Windows build depend on boost 1.70, which is not supported before
        # cmake version 3.14
        cmake_required_version = (3, 14)
    else:
        cmake_required_version = (3, 12)
    cmake_version = GetCMakeVersion()
    if not cmake_version:
        PrintError("Failed to determine CMake version")
        sys.exit(1)

    if cmake_version < cmake_required_version:
        def _JoinVersion(v):
            return ".".join(str(n) for n in v)
        PrintError("CMake version {req} or later required to build USD, "
                   "but version found was {found}".format(
                       req=_JoinVersion(cmake_required_version),
                       found=_JoinVersion(cmake_version)))
        sys.exit(1)
else:
    PrintError("CMake not found -- please install it and adjust your PATH")
    sys.exit(1)

if PYSIDE in requiredDependencies:
    # The USD build will skip building usdview if pyside2-uic or pyside-uic is
    # not found, so check for it here to avoid confusing users. This list of
    # PySide executable names comes from cmake/modules/FindPySide.cmake
    pyside2Uic = ["pyside2-uic", "python2-pyside2-uic", "pyside2-uic-2.7"]
    found_pyside2Uic = any([find_executable(p) for p in pyside2Uic])
    pysideUic = ["pyside-uic", "python2-pyside-uic", "pyside-uic-2.7"]
    found_pysideUic = any([find_executable(p) for p in pysideUic])
    if not found_pyside2Uic and not found_pysideUic:
        if Windows():
            # Windows does not support PySide2 with Python2.7
            PrintError("pyside-uic not found -- please install PySide and"
                       " adjust your PATH. (Note that this program may be named"
                       " {0} depending on your platform)"
                   .format(" or ".join(pysideUic)))
        else:
            PrintError("pyside2-uic not found -- please install PySide2 and"
                       " adjust your PATH. (Note that this program may be"
                       " named {0} depending on your platform)"
                       .format(" or ".join(pyside2Uic)))
        sys.exit(1)

if JPEG in requiredDependencies:
    # NASM is required to build libjpeg-turbo
    if (Windows() and not find_executable("nasm")):
        PrintError("nasm not found -- please install it and adjust your PATH")
        sys.exit(1)

# Summarize
summaryMsg = """\
BUILD SUMMARY:
  WINGG Dependency Libraries    {libInstDir}
  WINGG Dependency Source       {srcDir}
  WINGG Dependency Build        {buildDir}
  CMake generator               {cmakeGenerator}
  CMake toolset                 {cmakeToolset}
  Downloader                    {downloader}

    Boost                       {buildBoost}
    Ptex                        {buildPtex}
    OpenVDB                     {buildOpenVDB}
    Embree                      {buildEmbree}
    OpenImageIO                 {buildOIIO}
    OpenColorIO                 {buildOCIO}
    Alembic                     {buildAlembic}
    Draco                       {buildDraco}
    MaterialX                   {buildMaterialX}
    OSL                         {buildOSL}

  Dependencies                  {dependencies}""".format(
    libInstDir=context.libInstDir,
    srcDir=context.srcDir,
    buildDir=context.buildDir,
    cmakeGenerator=("Default" if not context.cmakeGenerator else context.cmakeGenerator),
    cmakeToolset=("Default"   if not context.cmakeToolset   else context.cmakeToolset),
    downloader=(context.downloaderName),
    dependencies=("None" if not dependenciesToBuild else ", ".join([d.name for d in dependenciesToBuild])),
    # buildConfig=("Debug" if context.buildDebug else "Release"),

    buildBoost=    ("On" if context.buildBoost      or context.buildAll else "Off"),
    buildPtex=     ("On" if context.buildPtex       or context.buildAll else "Off"),
    buildOpenVDB=  ("On" if context.buildOpenVDB    or context.buildAll else "Off"),
    buildEmbree=   ("On" if context.buildEmbree     or context.buildAll else "Off"),
    buildOIIO=     ("On" if context.buildOIIO       or context.buildAll else "Off"),
    buildOCIO=     ("On" if context.buildOCIO       or context.buildAll else "Off"),
    buildAlembic=  ("On" if context.buildAlembic    or context.buildAll else "Off"),
    buildDraco=    ("On" if context.buildDraco      or context.buildAll else "Off"),
    buildMaterialX=("On" if context.buildMaterialX  or context.buildAll else "Off"),
    buildOSL=      ("On" if context.buildOSL        or context.buildAll else "Off"),

    buildAll=("On" if context.buildAll else "Off"))

Print(summaryMsg)

# if args.dry_run:
#     sys.exit(0)

# Scan for any dependencies that the user is required to install themselves
# and print those instructions first.
pythonDependencies = \
    [dep for dep in dependenciesToBuild if type(dep) is PythonDependency]
if pythonDependencies:
    for dep in pythonDependencies:
        Print(dep.getInstructions())
    sys.exit(1)

# Ensure directory structure is created and is writable.
for dir in [context.libInstDir, context.libInstDir, context.srcDir,
            context.buildDir]:
    try:
        if os.path.isdir(dir):
            testFile = os.path.join(dir, "canwrite")
            open(testFile, "w").close()
            os.remove(testFile)
        else:
            os.makedirs(dir)
    except Exception as e:
        PrintError("Could not write to directory {dir}. Change permissions "
                   "or choose a different location to install to."
                   .format(dir=dir))
        sys.exit(1)

try:
    # Download and install 3rd-party dependencies.
    for dep in dependenciesToBuild:
        PrintStatus("Installing {dep}...".format(dep=dep.name))
        dep.installer(context,
                      buildArgs=context.GetBuildArguments(dep),
                      force=context.ForceBuildDependency(dep))
except Exception as e:
    PrintError(str(e))
    sys.exit(1)

# Done. Print out a final status message.
requiredInPythonPath = set([
    os.path.join(context.libInstDir, "lib", "python")
])
requiredInPythonPath.update(extraPythonPaths)

requiredInPath = set([
    os.path.join(context.libInstDir, "bin")
])
requiredInPath.update(extraPaths)

if Windows():
    requiredInPath.update([
        os.path.join(context.libInstDir, "lib"),
        os.path.join(context.libInstDir, "bin"),
        os.path.join(context.libInstDir, "lib")
    ])

Print("""
Success! Now build WINGG, simply use the './make' command:""")
