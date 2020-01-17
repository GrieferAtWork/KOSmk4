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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID___ASM_H
#define __GUARD_HYBRID___ASM_H 1

#include "../__stdinc.h"


#if defined(__CC__) && defined(__COMPILER_HAVE_GCC_ASM) && \
   !defined(__INTELLISENSE__)
#define __ASM_BEGIN      __asm__(
#define __ASM_END        );
#if defined(__TPP_VERSION__)
#define __ASM_ARG(x)     x
#else /* __TPP_VERSION__ */
/* CPP doesn't seem to escape this backslash when using PP_STR()?
 * Don't know if that's a bug, but I do know TPP does escape it.
 * So... Add the second slash manually to work around that. */
#define __ASM_ARG(x)     \x
#endif /* !__TPP_VERSION__ */
#define __ASM_LINE2(...) #__VA_ARGS__ "\n\t"
#define __ASM_L(...)     __ASM_LINE2(__VA_ARGS__)
#elif defined(__ASSEMBLY__)
#define __ASM_BEGIN      /* nothing */
#define __ASM_END        /* nothing */
#define __ASM_ARG(x)     x
#define __ASM_L(...)     __VA_ARGS__ ;
#else
#define __ASM_BEGIN      /* nothing */
#define __ASM_END        /* nothing */
#define __ASM_ARG(x)     /* nothing */
#define __ASM_L(...)     /* nothing */
#endif


#endif /* !__GUARD_HYBRID___ASM_H */
