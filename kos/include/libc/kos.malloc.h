/* HASH CRC-32:0x988a49d5 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBC_KOS_MALLOC_H
#define _LIBC_KOS_MALLOC_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include "core/kos.malloc.h"

#if !defined(____libc_Malloc_defined) && defined(____libc_core_Malloc_defined)
#define ____libc_Malloc_defined
#define __libc_Malloc __libc_core_Malloc
#endif /* !____libc_Malloc_defined && ____libc_core_Malloc_defined */
#if !defined(____libc_Calloc_defined) && defined(____libc_core_Calloc_defined)
#define ____libc_Calloc_defined
#define __libc_Calloc __libc_core_Calloc
#endif /* !____libc_Calloc_defined && ____libc_core_Calloc_defined */
#if !defined(____libc_Realloc_defined) && defined(____libc_core_Realloc_defined)
#define ____libc_Realloc_defined
#define __libc_Realloc __libc_core_Realloc
#endif /* !____libc_Realloc_defined && ____libc_core_Realloc_defined */

#endif /* __CC__ */

#endif /* !_LIBC_KOS_MALLOC_H */
