# Copyright (c) 2019-2023 Griefer@Work
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgement (see the following) in the product
#    documentation is required:
#    Portions Copyright (c) 2019-2023 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

CMAKE_TOOLCHAIN_FILE="$SYSROOT_BINUTILS_TARGET/opt/_cmake/toolchain.cmake"
CMAKE_MODULE_PATH="$SYSROOT_BINUTILS_TARGET/opt/_cmake/Modules"

install_rawfile_stdin "$CMAKE_TOOLCHAIN_FILE" <<EOF
set(CMAKE_SYSTEM_NAME Kos)
set(CMAKE_SYSTEM_PROCESSOR $TARGET_CPUNAME)
set(CMAKE_MODULE_PATH "$SYSROOT_BINUTILS_TARGET/opt/_cmake/Modules")

set(CMAKE_SYSROOT "")
# 'CMAKE_STAGING_PREFIX' is the runtime install location (so root of the KOS disk; iow: "/")
set(CMAKE_STAGING_PREFIX "/")

set(CMAKE_C_COMPILER "${CROSS_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${CROSS_PREFIX}g++")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_INSTALL_LIBDIR "$TARGET_LIBPATH")
EOF

install_rawfile_stdin "$CMAKE_MODULE_PATH/Platform/Kos.cmake" <<EOF
# Act like we're actually linux...
set(CMAKE_SYSTEM_NAME Linux)
include(Platform/Linux)

# Workaround for an issue related to "-rdynamic"
macro(__linux_compiler_gnu lang)
  set(CMAKE_SHARED_LIBRARY_LINK_${lang}_FLAGS "")
endmacro()
EOF
