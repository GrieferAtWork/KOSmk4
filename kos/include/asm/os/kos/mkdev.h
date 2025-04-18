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
#ifndef _ASM_OS_KOS_MKDEV_H
#define _ASM_OS_KOS_MKDEV_H 1

#include <__stdinc.h>

#include <bits/typesizes.h>

#ifndef __SIZEOF_DEV_T__
#define __SIZEOF_DEV_T__ 8
#endif /* !__SIZEOF_DEV_T__ */

#define __MKDEV_V0_MAJOR_SHFT 20
#if __SIZEOF_DEV_T__ == 8
#define __MKDEV_V0_MAJOR_BITS 44
#elif __SIZEOF_DEV_T__ == 4
#define __MKDEV_V0_MAJOR_BITS 12
#else /* __SIZEOF_DEV_T__ == ... */
#define __MKDEV_V0_MAJOR_BITS ((__SIZEOF_DEV_T__ * 8) - 20)
#endif /* __SIZEOF_DEV_T__ != ... */
#define __MKDEV_V0_MINOR_SHFT 0
#define __MKDEV_V0_MINOR_BITS 20

#define __MKDEV_CURRENT_VERSION 0
#define __MKDEV_MAJOR_SHFT(v) __MKDEV_V0_MAJOR_SHFT
#define __MKDEV_MAJOR_BITS(v) __MKDEV_V0_MAJOR_BITS
#define __MKDEV_MINOR_SHFT(v) __MKDEV_V0_MINOR_SHFT
#define __MKDEV_MINOR_BITS(v) __MKDEV_V0_MINOR_BITS

/* Bad/invalid device number */
#define __MKDEV_BADDEV 0

/* The first automatically assigned device major-number */
#define __MKDEV_MAJOR_AUTO 256

#endif /* !_ASM_OS_KOS_MKDEV_H */
