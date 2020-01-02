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
#ifndef _I386_KOS_BITS_SELECT_H
#define _I386_KOS_BITS_SELECT_H 1


#ifndef __FD_SETSIZE
#define __FD_SETSIZE 1024
#endif

#ifdef __COMPILER_HAVE_GCC_ASM
#include <hybrid/host.h>
#ifdef __x86_64__
#define __FD_ZERO_STOS "stosq"
#else /* __x86_64__ */
#define __FD_ZERO_STOS "stosl"
#endif /* !__x86_64__ */
#define __FD_ZERO(fdsp) \
do{ register __intptr_t __d0,__d1; \
    __asm__ __volatile__("cld; rep; " __FD_ZERO_STOS \
                         : "=c" (__d0), "=D" (__d1) \
                         : "a" (0), "0" (sizeof(fd_set)/sizeof(__fd_mask)) \
                         , "1" (&__FDS_BITS(fdsp)[0]) \
                         : "memory"); \
}__WHILE0
#endif /* __COMPILER_HAVE_GCC_ASM */

#include "../../bits/select.h"

#endif /* !_I386_KOS_BITS_SELECT_H */
