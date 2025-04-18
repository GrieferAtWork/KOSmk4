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
/*!replace_with_include <asm/os/mkdev.h>*/
#ifndef _ASM_OS_SOLARIS_MKDEV_H
#define _ASM_OS_SOLARIS_MKDEV_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#define __MKDEV_V0_MAJOR_BITS 7
#define __MKDEV_V0_MAJOR_SHFT 8
#define __MKDEV_V0_MINOR_BITS 8
#define __MKDEV_V0_MINOR_SHFT 0

#define __MKDEV_V1_MAJOR_BITS_32 14
#define __MKDEV_V1_MAJOR_SHFT_32 18
#define __MKDEV_V1_MINOR_BITS_32 18
#define __MKDEV_V1_MINOR_SHFT_32 0

#define __MKDEV_V1_MAJOR_BITS_64 32
#define __MKDEV_V1_MAJOR_SHFT_64 32
#define __MKDEV_V1_MINOR_BITS_64 32
#define __MKDEV_V1_MINOR_SHFT_64 0

#if __SIZEOF_POINTER__ <= 4
#define __MKDEV_V1_MAJOR_BITS __MKDEV_V1_MAJOR_BITS_32
#define __MKDEV_V1_MAJOR_SHFT __MKDEV_V1_MAJOR_SHFT_32
#define __MKDEV_V1_MINOR_BITS __MKDEV_V1_MINOR_BITS_32
#define __MKDEV_V1_MINOR_SHFT __MKDEV_V1_MINOR_SHFT_32
#else /* __SIZEOF_POINTER__ <= 4 */
#define __MKDEV_V1_MAJOR_BITS __MKDEV_V1_MAJOR_BITS_64
#define __MKDEV_V1_MAJOR_SHFT __MKDEV_V1_MAJOR_SHFT_64
#define __MKDEV_V1_MINOR_BITS __MKDEV_V1_MINOR_BITS_64
#define __MKDEV_V1_MINOR_SHFT __MKDEV_V1_MINOR_SHFT_64
#endif /* __SIZEOF_POINTER__ > 4 */

/* Current version number */
#define __MKDEV_CURRENT_VERSION 1

#define __MKDEV_MAJOR_SHFT(v) ((v) == 1 ? __MKDEV_V1_MAJOR_SHFT : __MKDEV_V0_MAJOR_SHFT)
#define __MKDEV_MAJOR_BITS(v) ((v) == 1 ? __MKDEV_V1_MAJOR_BITS : __MKDEV_V0_MAJOR_BITS)
#define __MKDEV_MINOR_SHFT(v) ((v) == 1 ? __MKDEV_V1_MINOR_SHFT : __MKDEV_V0_MINOR_SHFT)
#define __MKDEV_MINOR_BITS(v) ((v) == 1 ? __MKDEV_V1_MINOR_BITS : __MKDEV_V0_MINOR_BITS)

/* Bad/invalid device number */
#define __MKDEV_BADDEV 0

/* Device version numbers (for `<sys/mkdev.h>') */
#define OLDDEV 0
#define NEWDEV 1

#endif /* !_ASM_OS_SOLARIS_MKDEV_H */
