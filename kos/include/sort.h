/* HASH CRC-32:0x5285e645 */
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
/* (#) Portability: libiberty (/include/sort.h) */
#ifndef _SORT_H
#define _SORT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifdef __CRT_HAVE_sort_pointers
/* >> sort_pointers(3)
 * Sort an array of `count' pointers `sortme' in ascending order
 * @param: work: An  additional array of `count' elements that may
 *               be used as temporary storage by the implemenation
 *               The  contents  of this  array are  undefined upon
 *               return of this function. */
__CDECLARE_VOID(__ATTR_INOUTS(2, 1) __ATTR_OUTS(3, 1),__NOTHROW_NCX,sort_pointers,(size_t __count, void **__sortme, void **__work),(__count,__sortme,__work))
#else /* __CRT_HAVE_sort_pointers */
#include <libc/local/sort/sort_pointers.h>
/* >> sort_pointers(3)
 * Sort an array of `count' pointers `sortme' in ascending order
 * @param: work: An  additional array of `count' elements that may
 *               be used as temporary storage by the implemenation
 *               The  contents  of this  array are  undefined upon
 *               return of this function. */
__NAMESPACE_LOCAL_USING_OR_IMPL(sort_pointers, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUTS(2, 1) __ATTR_OUTS(3, 1) void __NOTHROW_NCX(__LIBCCALL sort_pointers)(size_t __count, void **__sortme, void **__work) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sort_pointers))(__count, __sortme, __work); })
#endif /* !__CRT_HAVE_sort_pointers */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SORT_H */
