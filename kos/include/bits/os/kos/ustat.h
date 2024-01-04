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
#ifndef _BITS_OS_KOS_USTAT_H
#define _BITS_OS_KOS_USTAT_H 1

/* File:
 *    <bits/os/kos/ustat.h>
 *
 * Definitions:
 *    struct ustat {
 *        ...
 *    };
 */

#include <__stdinc.h>

#include <bits/types.h>

#define __OFFSET_USTAT_TFREE  0
#if __SIZEOF_INO32_T__ > __SIZEOF_DADDR_T__
#define __OFFSET_USTAT_TINODE __SIZEOF_INO32_T__
#else /* __SIZEOF_INO32_T__ > __SIZEOF_DADDR_T__ */
#define __OFFSET_USTAT_TINODE __SIZEOF_DADDR_T__
#endif /* __SIZEOF_INO32_T__ <= __SIZEOF_DADDR_T__ */
#define __OFFSET_USTAT_FNAME  (__OFFSET_USTAT_TINODE + __SIZEOF_INO32_T__)
#define __OFFSET_USTAT_FPACK  (__OFFSET_USTAT_TINODE + __SIZEOF_INO32_T__ + 6)
#if __SIZEOF_INO32_T__ > __SIZEOF_DADDR_T__
#define __SIZEOF_USTAT (__OFFSET_USTAT_TINODE + __SIZEOF_INO32_T__ + 12 + __SIZEOF_INO32_T__ - __SIZEOF_DADDR_T__)
#else /* __SIZEOF_INO32_T__ > __SIZEOF_DADDR_T__ */
#define __SIZEOF_USTAT (__OFFSET_USTAT_TINODE + __SIZEOF_INO32_T__ + 12)
#endif /* __SIZEOF_INO32_T__ <= __SIZEOF_DADDR_T__ */

#if __SIZEOF_INO32_T__ > __SIZEOF_DADDR_T__
#define __ALIGNOF_USTAT __SIZEOF_INO32_T__
#else /* __SIZEOF_INO32_T__ > __SIZEOF_DADDR_T__ */
#define __ALIGNOF_USTAT __SIZEOF_DADDR_T__
#endif /* __SIZEOF_INO32_T__ <= __SIZEOF_DADDR_T__ */

#ifdef __CC__
__DECL_BEGIN

struct ustat /*[PREFIX(f_)]*/ {
	__daddr_t f_tfree;    /* Number of free blocks. */
#if __SIZEOF_INO32_T__ > __SIZEOF_DADDR_T__
	__byte_t __f_pad[__SIZEOF_INO32_T__ - __SIZEOF_DADDR_T__]; /* Hidden padding... */
#endif /* __SIZEOF_INO32_T__ > __SIZEOF_DADDR_T__ */
	__ino32_t f_tinode;   /* Number of free inodes. */
	char      f_fname[6]; /* ??? */
	char      f_fpack[6]; /* ??? */
#if __SIZEOF_INO32_T__ > __SIZEOF_DADDR_T__
	__byte_t __f_pad2[__SIZEOF_INO32_T__ - __SIZEOF_DADDR_T__]; /* Hidden padding... */
#endif /* __SIZEOF_INO32_T__ > __SIZEOF_DADDR_T__ */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_USTAT_H */
