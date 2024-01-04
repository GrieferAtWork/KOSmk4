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
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/int_fmtio.h) */
#ifndef _SYS_INT_FMTIO_H
#define _SYS_INT_FMTIO_H 1

#include <__stdinc.h>

#include <inttypes.h> /* Only need non-extension PRI* and SCA* macros. */

/* For some reason, these are also defined here? */
#ifndef SCNX8
#define SCNX8       __SCA1_PREFIX "X"
#define SCNX16      __SCA2_PREFIX "X"
#define SCNX32      __SCA4_PREFIX "X"
#define SCNX64      __SCA8_PREFIX "X"
#define SCNXLEAST8  __SCAL1_PREFIX "X"
#define SCNXLEAST16 __SCAL2_PREFIX "X"
#define SCNXLEAST32 __SCAL4_PREFIX "X"
#define SCNXLEAST64 __SCAL8_PREFIX "X"
#define SCNXFAST8   __SCAF1_PREFIX "X"
#define SCNXFAST16  __SCAF2_PREFIX "X"
#define SCNXFAST32  __SCAF4_PREFIX "X"
#define SCNXFAST64  __SCAF8_PREFIX "X"
#define SCNXMAX     __SCA8_PREFIX "X"
#define SCNXPTR     __SCAP_PREFIX "X"
#endif /* !SCNX8 */

#endif /* !_SYS_INT_FMTIO_H */
