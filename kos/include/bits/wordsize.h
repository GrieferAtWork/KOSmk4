/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/bits/wordsize.h) */
/* (#) Portability: GNU C Library (/bits/wordsize.h) */
#ifndef __WORDSIZE
/* NOTE: This file must _always_ be kept for GLibc compatibility! */

#include <hybrid/typecore.h>

#include <bits/typesizes.h>

#ifndef __SIZEOF_TIME32_T__
#define __SIZEOF_TIME32_T__ 4
#endif /* !__SIZEOF_TIME32_T__ */
#ifndef __SIZEOF_TIME64_T__
#define __SIZEOF_TIME64_T__ 8
#endif /* !__SIZEOF_TIME64_T__ */

/* __WORDSIZE = __SIZEOF_POINTER__ * __CHAR_BIT__ */
#define __WORDSIZE __INTPTR_WIDTH__

#ifndef __SIZEOF_SYSCALL_LONG_T__
#define __SIZEOF_SYSCALL_LONG_T__ __SIZEOF_REGISTER__
#endif /* !__SIZEOF_SYSCALL_LONG_T__ */

/* __SYSCALL_WORDSIZE = __SIZEOF_SYSCALL_LONG_T__ * __CHAR_BIT__ */
#ifndef __SYSCALL_WORDSIZE
#define __SYSCALL_WORDSIZE __PRIVATE_WIDTH(__SIZEOF_SYSCALL_LONG_T__)
#endif /* !__SYSCALL_WORDSIZE */

/* defined(__WORDSIZE_TIME64_COMPAT32) = __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __WORDSIZE_TIME64_COMPAT32 1
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

#endif /* !__WORDSIZE */
