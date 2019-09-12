/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _BITS_USTAT_H
#define _BITS_USTAT_H 1

#include <__stdinc.h>

#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

struct ustat {
	__daddr_t f_tfree;    /* Number of free blocks. */
	__ino32_t f_tinode;   /* Number of free inodes. */
	char      f_fname[6]; /* ??? */
	char      f_fpack[6]; /* ??? */
};

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BITS_USTAT_H */
