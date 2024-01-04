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
/* (#) Portability: Cygwin (/winsup/cygwin/include/asm/bitsperlong.h) */
/* (#) Portability: Linux  (/usr/include/[...]/asm/bitsperlong.h) */
#ifndef _ASM_BITSPERLONG_H
#define _ASM_BITSPERLONG_H 1

#include <hybrid/typecore.h>

#ifndef __BITS_PER_LONG
#ifndef __SIZEOF_POINTER__
#error "Unknown `sizeof(void *)' -> can't determine `__BITS_PER_LONG'"
#endif /* !__SIZEOF_POINTER__ */
#if __SIZEOF_POINTER__ == 4
#define __BITS_PER_LONG 32
#elif __SIZEOF_POINTER__ == 8
#define __BITS_PER_LONG 64
#elif __SIZEOF_POINTER__ == 2
#define __BITS_PER_LONG 16
#elif __SIZEOF_POINTER__ == 1
#define __BITS_PER_LONG 8
#else /* __SIZEOF_POINTER__ == ... */
#define __BITS_PER_LONG (__SIZEOF_POINTER__ * 8)
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* !__BITS_PER_LONG */

#endif /* !_ASM_BITSPERLONG_H */
