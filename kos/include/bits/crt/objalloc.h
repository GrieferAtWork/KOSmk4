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
#ifndef _BITS_CRT_OBJALLOC_H
#define _BITS_CRT_OBJALLOC_H 1

#include <__stdinc.h>
#include <__crt.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

struct objalloc {
	char         *current_ptr;   /* [0..current_space] Pointer to unallocated space. (always aligned by `__LIBC_MALLOC_ALIGNMENT') */
	/* NOTE: In the original, `current_space' had type `unsigned int' */
	__SIZE_TYPE__ current_space; /* Amount of free (unallocated) space. (always aligned by `__LIBC_MALLOC_ALIGNMENT') */
	void         *chunks;        /* [0..n][owned] Linked list of allocated chunks. */
};


#if 1 /* Internal implementation details -- don't use! */
struct __objalloc_chunk {
	struct __objalloc_chunk *__oc_prev;   /* [0..1] Chunk allocated before this one. */
	char                    *__oc_curptr; /* [0..1] Value  of  `current_ptr'  before  this  chunk  was
	                                       * created, or `NULL' if the chunk contains "small objects". */
};
/* __OBJALLOC_CHUNK_HEADER_SIZE = CEIL_ALIGN(sizeof(struct __objalloc_chunk), __LIBC_MALLOC_ALIGNMENT) */
#define __OBJALLOC_CHUNK_HEADER_SIZE ((sizeof(struct __objalloc_chunk) + __LIBC_MALLOC_ALIGNMENT - 1) & ~(__LIBC_MALLOC_ALIGNMENT - 1))
#define __OBJALLOC_CHUNK_SIZE        (4096 - 32) /* Size of a chunk meant for "small objects" */
#define __OBJALLOC_BIG_REQUEST       512         /* objects with sizes < this are "small objects" */
#endif


__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_OBJALLOC_H */
