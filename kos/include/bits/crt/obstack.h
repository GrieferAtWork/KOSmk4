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
#ifndef _BITS_CRT_OBSTACK_H
#define _BITS_CRT_OBSTACK_H 1

#include <__stdinc.h>

#include <gnu-versions.h>
#include <hybrid/typecore.h>

#if (!defined(_OBSTACK_INTERFACE_VERSION) && defined(_GNU_OBSTACK_INTERFACE_VERSION))
#define _OBSTACK_INTERFACE_VERSION _GNU_OBSTACK_INTERFACE_VERSION
#endif /* !_OBSTACK_INTERFACE_VERSION && _GNU_OBSTACK_INTERFACE_VERSION */
#ifndef _OBSTACK_INTERFACE_VERSION
#define _OBSTACK_INTERFACE_VERSION 2
#endif /* !_OBSTACK_INTERFACE_VERSION */


#ifdef __CC__
__DECL_BEGIN

#if _OBSTACK_INTERFACE_VERSION == 1
#define _OBSTACK_SIZE_T           unsigned int
#define _CHUNK_SIZE_T             __ULONGPTR_TYPE__
#define _OBSTACK_CAST(type, expr) ((type)(expr))
#else /* _OBSTACK_INTERFACE_VERSION == 1 */
#define _OBSTACK_SIZE_T           __SIZE_TYPE__
#define _CHUNK_SIZE_T             __SIZE_TYPE__
#define _OBSTACK_CAST(type, expr) (expr)
#endif /* _OBSTACK_INTERFACE_VERSION != 1 */


struct _obstack_chunk {
	char                  *limit;       /* [1..1][const] Pointer to end of chunk */
	struct _obstack_chunk *prev;        /* [0..1] Previous chunk */
	char                   contents[4]; /* Actually a flexible array: chunk data */
};

struct obstack {
	_CHUNK_SIZE_T            chunk_size;     /* [const] Minimum chunk size */
	struct _obstack_chunk   *chunk;          /* [1..1] Current chunk */
	char                    *object_base;    /* [1..1] Current object base address */
	char                    *next_free;      /* [1..1] Current object end pointer */
	char                    *chunk_limit;    /* [1..1][== chunk->limit] Current chunk end */
	union {
		__SIZE_TYPE__      __tempsiz;        /* ... */
		__INTPTR_TYPE__      tempint;        /* ... */
		void                *tempptr;        /* ... */
	}                        temp;           /* Temp storage (must be kept to retain ABI compat...) */
	_CHUNK_SIZE_T            alignment_mask; /* [const] Minimum object alignment minus 1 */
	/* [1..1] Allocator function -- `__arg' only exists when `use_extra_arg' */
	union {
		/*struct _obstack_chunk*/ void *(__LIBCCALL *plain)(__SIZE_TYPE__ __num_bytes);
		/*struct _obstack_chunk*/ void *(__LIBCCALL *extra)(void *__arg, __SIZE_TYPE__ __num_bytes);
	} chunkfun;
	/* [1..1] Free function -- `__arg' only exists when `use_extra_arg' */
	union {
		void (__LIBCCALL *plain)(/*struct _obstack_chunk*/ void *__ptr);
		void (__LIBCCALL *extra)(void *__arg, /*struct _obstack_chunk*/ void *__ptr);
	} freefun;
	void                    *extra_arg;              /* [?..?][valid_if(use_extra_arg)] Extra argument */
	unsigned int             use_extra_arg : 1;      /* Pass an additional cookie-argument to alloc/free */
	unsigned int             maybe_empty_object : 1; /* The current object may be empty */
	unsigned int             alloc_failed : 1;       /* [const] Always `0' */
};

/* Helpers to invoke the alloc/free functions */
#define __obstack_malloc(self, num_bytes)                                            \
	((self)->use_extra_arg ? (*(self)->chunkfun.extra)((self)->extra_arg, num_bytes) \
	                       : (*(self)->chunkfun.plain)(num_bytes))
#define __obstack_free(self, ptr)                                             \
	((self)->use_extra_arg ? (*(self)->freefun.extra)((self)->extra_arg, ptr) \
	                       : (*(self)->freefun.plain)(ptr))



/* [1..1] Allocation failure handler. (never  returns)
 * Defaults to a function that prints an error message
 * to stderr, then does `exit(obstack_exit_failure)'.
 * HINT: The message is `gettext("memory exhausted")'
 * HINT: This function is allowed to `longjmp(3)'! */
#ifndef __LOCAL_obstack_alloc_failed_handler
#ifdef obstack_alloc_failed_handler
#define __LOCAL_obstack_alloc_failed_handler obstack_alloc_failed_handler
#elif defined(__CRT_HAVE_obstack_alloc_failed_handler)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE2(,void (__LIBKCALL *obstack_alloc_failed_handler)(void),obstack_alloc_failed_handler)
#define __LOCAL_obstack_alloc_failed_handler obstack_alloc_failed_handler
#define obstack_alloc_failed_handler         obstack_alloc_failed_handler
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT2(,void (__LIBKCALL *__LOCAL_obstack_alloc_failed_handler)(void),__LOCAL_obstack_alloc_failed_handler,obstack_alloc_failed_handler)
#define __LOCAL_obstack_alloc_failed_handler __LOCAL_obstack_alloc_failed_handler
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* !obstack_alloc_failed_handler */
#endif /* !__LOCAL_obstack_alloc_failed_handler */

/* Program exit code for when an allocation fails (defaults to `EXIT_FAILURE') */
#ifndef __LOCAL_obstack_exit_failure
#ifdef obstack_exit_failure
#define __LOCAL_obstack_exit_failure obstack_exit_failure
#elif defined(__CRT_HAVE_obstack_exit_failure)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,int,obstack_exit_failure)
#define __LOCAL_obstack_exit_failure obstack_exit_failure
#define obstack_exit_failure         obstack_exit_failure
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,int,__LOCAL_obstack_exit_failure,obstack_exit_failure)
#define __LOCAL_obstack_exit_failure __LOCAL_obstack_exit_failure
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* !obstack_exit_failure */
#endif /* !__LOCAL_obstack_exit_failure */


/* Do `base + CEIL_ALIGN(ptr - base, alignment_mask + 1)' */
#define __BPTR_ALIGN(base, ptr, alignment_mask) \
	((base) + (((ptr) - (base) + (alignment_mask)) & ~(alignment_mask)))
#if __SIZEOF_PTRDIFF_T__ < __SIZEOF_POINTER__
#define __PTR_ALIGN(base, ptr, alignment_mask) \
	__BPTR_ALIGN(base, ptr, alignment_mask)
#else /* __SIZEOF_PTRDIFF_T__ < __SIZEOF_POINTER__ */
#define __PTR_ALIGN(base, ptr, alignment_mask) \
	((char *)(((__UINTPTR_TYPE__)(ptr) + (alignment_mask)) & ~(alignment_mask)))
#endif /* __SIZEOF_PTRDIFF_T__ >= __SIZEOF_POINTER__ */


__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_OBSTACK_H */
