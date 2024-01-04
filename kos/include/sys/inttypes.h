/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: NetBSD      (/sys/sys/inttypes.h) */
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/inttypes.h) */
#ifndef _SYS_INTTYPES_H
#define _SYS_INTTYPES_H 1

#include <features.h>

#include <sys/feature_tests.h>
#include <sys/int_types.h>
#if !defined(__USE_XOPEN) || defined(__USE_XOPEN2K) || defined(__USE_SOLARIS)
#include <sys/int_limits.h>
#include <sys/int_const.h>
#include <sys/int_fmtio.h>
#endif /* !__USE_XOPEN || __USE_XOPEN2K || __USE_SOLARIS */

#endif /* !_SYS_INTTYPES_H */
