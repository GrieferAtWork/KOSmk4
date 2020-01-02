/* Copyright (c) 2019-2020 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_EXEC_RTLD_H
#define _KOS_EXEC_RTLD_H 1

#include <__stdinc.h>

#include <kos/exec/asm/rtld.h>

/* Absolute path of the libdl driver itself. */
#ifndef RTLD_LIBDL
#define RTLD_LIBDL "/lib/libdl.so"
#endif /* !RTLD_LIBDL */

/* Default for `LD_LIBRARY_PATH' */
#ifndef RTLD_LIBRARY_PATH
#define RTLD_LIBRARY_PATH "/usr/lib:/lib"
#endif /* !RTLD_LIBRARY_PATH */

/* The string to which `$LIB' in library paths is expanded */
#ifndef RTLD_LIB
#define RTLD_LIB "lib"
#endif /* !RTLD_LIB */

/* The string to which `$PLATFORM' in library paths is expanded */
#ifndef RTLD_PLATFORM
#define RTLD_PLATFORM "?"
#endif /* !RTLD_PLATFORM */

#endif /* !_KOS_EXEC_RTLD_H */
