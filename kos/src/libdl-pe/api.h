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
#ifndef GUARD_LIBDL_PE_API_H
#define GUARD_LIBDL_PE_API_H 1
#define __WANT_INLINE_SYSCALLS

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/config/config.h> /* Pull in config-specific macro overrides */

#include <libdl/api.h>

#define CC  LIBDL_CC
#define VCC LIBDL_VCC

#ifndef FCALL
#define FCALL __FCALL
#endif /* !FCALL */

#ifndef DLFCN_CC
#define DLFCN_CC __DLFCN_CC
#endif /* !DLFCN_CC */
#ifndef DLFCN_VCC
#define DLFCN_VCC __DLFCN_VCC
#endif /* !DLFCN_VCC */

#ifndef REF
#define REF __REF
#endif /* !REF */

#endif /* !GUARD_LIBDL_PE_API_H */
