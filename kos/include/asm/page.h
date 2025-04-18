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
#ifndef _ASM_PAGE_H
#define _ASM_PAGE_H 1

/* DO NOT REMOVE THIS FILE!
 *
 * It, and its contents are here for compatibility
 * with  older   versions  of   Glibc  on   linux!
 *
 * Some (old) 3rd party code may exist that directly
 * includes this file.
 *
 * Purpose:
 *    #define PAGE_SIZE  __ARCH_PAGESIZE   (known)
 *    #define PAGE_SHIFT __ARCH_PAGESHIFT  (likely)
 *    #define PAGE_MASK  __ARCH_PAGEMASK   (likely)
 *
 * The  original  headers  (supposedly,  as  I  can't  actually
 * find a proper instance of  this header, due to an  ambiguity
 * with  an  internal linux  kernel  header of  the  same name)
 * defines  these  macros   unconditionally,  however  due   to
 * portability concerns, we can only define them conditionally!
 *
 * One example of a 3rd party program that references this header is:
 *   - xorg-server-1.12.2:/Xext/xf86bigfont.c:43-49
 */

#include <asm/pagesize.h>

#if !defined(PAGE_MASK) && defined(__ARCH_PAGEMASK)
#define PAGE_MASK __ARCH_PAGEMASK
#endif /* !PAGE_MASK && __ARCH_PAGEMASK */

#if !defined(PAGE_SIZE) && defined(__ARCH_PAGESIZE)
#define PAGE_SIZE __ARCH_PAGESIZE
#endif /* !PAGE_SIZE && __ARCH_PAGESIZE */

#if !defined(PAGE_SHIFT) && defined(__ARCH_PAGESHIFT)
#define PAGE_SHIFT __ARCH_PAGESHIFT
#endif /* !PAGE_SHIFT && __ARCH_PAGESHIFT */

#endif /* !_ASM_PAGE_H */
