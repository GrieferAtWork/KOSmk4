/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!replace_with_include <kos/exec/rtld.h>*/
#ifndef _I386_KOS_KOS_EXEC_ASM_RTLD_H
#define _I386_KOS_KOS_EXEC_ASM_RTLD_H 1

#include <hybrid/host.h>

/* On x86_64, RTLD paths are somewhat different due to multiarch */
#ifdef __x86_64__
#define RTLD_LIBDL        "/lib64/libdl.so"
#define _RTLD_LIBDL_HASH  /*[[[fdirent_hash("/lib64/libdl.so")]]]*/FDIRENT_HASH_INIT(0x491b7fcc, 0xce184917e2193010, 0xe7201438, 0xab3f27a2543a0d35)/*[[[end]]]*/
#define RTLD_LIBRARY_PATH "/usr/lib64:/lib64"
#define RTLD_LIB          "lib64"
#define RTLD_PLATFORM     "x86_64"
#else /* __x86_64__ */
#define RTLD_LIBDL        "/lib/libdl.so"
#define _RTLD_LIBDL_HASH  /*[[[fdirent_hash("/lib/libdl.so")]]]*/FDIRENT_HASH_INIT(0x6e321ca9, 0x75b4ce19e8e33a0b, 0x94d3128e, 0xaacfb4e31dfe20d6)/*[[[end]]]*/
#define RTLD_LIBRARY_PATH "/usr/lib:/lib"
#define RTLD_LIB          "lib"
#define RTLD_PLATFORM     "i386"
#endif /* !__x86_64__ */

#endif /* !_I386_KOS_KOS_EXEC_ASM_RTLD_H */
