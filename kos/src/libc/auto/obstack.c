/* HASH CRC-32:0x727689a3 */
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
#ifndef GUARD_LIBC_AUTO_OBSTACK_C
#define GUARD_LIBC_AUTO_OBSTACK_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "obstack.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/typecore.h>

#include <kos/exec/idata.h>

#include <atomic.h>
#include <stdio.h>
#include <stdlib.h>

#include <libintl.h>

#include "../libc/globals.h"

/* Apparently, once-upon-a-time ("before 1994"), this global variable was
 * used  by obstack macros in order to prevent multiple-evaluation of the
 * `self' argument. -- It is retained in the ABI for backward-compat. */
INTDEF struct obstack *libc__obstack;
INTERN ATTR_SECTION(".bss.crt.heap.obstack")
struct obstack *libc__obstack = NULL;
DEFINE_PUBLIC_ALIAS(_obstack, libc__obstack);


/* Public dat symbols. */
#undef obstack_exit_failure
#undef obstack_alloc_failed_handler
DEFINE_PUBLIC_ALIAS(obstack_exit_failure, libc_obstack_exit_failure);
DEFINE_PUBLIC_IDATA(obstack_alloc_failed_handler, libc_obstack_alloc_failed_handler_resolve, __SIZEOF_POINTER__);
#define obstack_exit_failure         GET_NOREL_GLOBAL(obstack_exit_failure)
#define obstack_alloc_failed_handler GET_NOREL_GLOBAL(obstack_alloc_failed_handler)

/* Default allocation failure exit code. */
INTERN ATTR_SECTION(".data.crt.heap.obstack")
int libc_obstack_exit_failure = EXIT_FAILURE;

/* Default allocation failure handler. */
PRIVATE ATTR_SECTION(".bss.crt.heap.obstack")
void (__LIBKCALL *libc_obstack_alloc_failed_handler)(void) = NULL;
PRIVATE ATTR_SECTION(".rodata.crt.heap.obstack")
char const libc_obstack_alloc_failed_message[] = "memory exhausted";
PRIVATE ATTR_NORETURN ATTR_SECTION(".text.crt.heap.obstack")
void libc_obstack_alloc_failed_default(void) {
	fprintf(stderr, "%s\n", gettext(libc_obstack_alloc_failed_message));
	exit(obstack_exit_failure);
}

INTERN ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.heap.obstack") void *
NOTHROW(LIBCCALL libc_obstack_alloc_failed_handler_resolve)(void) {
	if (libc_obstack_alloc_failed_handler == NULL)
		atomic_cmpxch(&libc_obstack_alloc_failed_handler, NULL, &libc_obstack_alloc_failed_default);
	return (void *)&libc_obstack_alloc_failed_handler;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#include <bits/crt/obstack.h>
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.heap.obstack") ATTR_OUT(1) NONNULL((4, 5)) int
NOTHROW_NCX(LIBCCALL libc__obstack_begin)(struct obstack *self,
                                          _OBSTACK_SIZE_T min_chunk_size,
                                          _OBSTACK_SIZE_T min_object_alignment,
                                          void *(__LIBCCALL *ob_malloc)(size_t num_bytes),
                                          void (__LIBCCALL *ob_free)(void *ptr)) {
	struct _obstack_chunk *nchunk;
	if (min_object_alignment < __ALIGNOF_MAX_ALIGN_T__)
		min_object_alignment = __ALIGNOF_MAX_ALIGN_T__;
	if (min_chunk_size == 0) {
		/* This is what the source material does in this case.
		 * We don't want to break the ABI, so we do the  same. */
		size_t extra = ((((12 + sizeof(__MAX_ALIGN_TYPE__) - 1) &
		                  ~(sizeof(__MAX_ALIGN_TYPE__) - 1)) +
		                 4 + sizeof(__MAX_ALIGN_TYPE__) - 1) &
		                ~(sizeof(__MAX_ALIGN_TYPE__) - 1));
		min_chunk_size = 4096 - extra;
	}

	self->chunkfun.plain = (void *(__LIBCCALL *)(__SIZE_TYPE__))ob_malloc;
	self->freefun.plain  = (void (__LIBCCALL *)(void *))ob_free;
	self->chunk_size       = min_chunk_size;
	self->alignment_mask   = min_object_alignment - 1;

	nchunk = (struct _obstack_chunk *)((*ob_malloc)(min_chunk_size));
	if (!nchunk) {

		(*__LOCAL_obstack_alloc_failed_handler)();





	}
	self->chunk       = nchunk;
	self->object_base = __PTR_ALIGN((char *)nchunk, nchunk->contents, min_object_alignment - 1);
	self->next_free   = self->object_base;
	nchunk->limit     = (char *)nchunk + min_chunk_size;
	self->chunk_limit = nchunk->limit;
	nchunk->prev      = __NULLPTR;
	self->use_extra_arg      = 0;
	self->maybe_empty_object = 0;
	self->alloc_failed       = 0;
	return 1;
}
#include <bits/crt/obstack.h>
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.heap.obstack") ATTR_OUT(1) NONNULL((4, 5)) int
NOTHROW_NCX(LIBCCALL libc__obstack_begin_1)(struct obstack *self,
                                            _OBSTACK_SIZE_T min_chunk_size,
                                            _OBSTACK_SIZE_T min_object_alignment,
                                            void *(*ob_malloc)(void *arg, size_t num_bytes),
                                            void (*ob_free)(void *arg, void *ptr),
                                            void *arg) {
	struct _obstack_chunk *nchunk;
	if (min_object_alignment < __ALIGNOF_MAX_ALIGN_T__)
		min_object_alignment = __ALIGNOF_MAX_ALIGN_T__;
	if (min_chunk_size == 0) {
		/* This is what the source material does in this case.
		 * We don't want to break the ABI, so we do the  same. */
		size_t extra = ((((12 + sizeof(__MAX_ALIGN_TYPE__) - 1) &
		                  ~(sizeof(__MAX_ALIGN_TYPE__) - 1)) +
		                 4 + sizeof(__MAX_ALIGN_TYPE__) - 1) &
		                ~(sizeof(__MAX_ALIGN_TYPE__) - 1));
		min_chunk_size = 4096 - extra;
	}

	self->chunkfun.extra = (void *(__LIBCCALL *)(void *, __SIZE_TYPE__))ob_malloc;
	self->freefun.extra  = (void (__LIBCCALL *)(void *, void *))ob_free;
	self->chunk_size       = min_chunk_size;
	self->alignment_mask   = min_object_alignment - 1;

	nchunk = (struct _obstack_chunk *)((*ob_malloc)(arg, min_chunk_size));
	if (!nchunk) {

		(*__LOCAL_obstack_alloc_failed_handler)();





	}
	self->chunk       = nchunk;
	self->object_base = __PTR_ALIGN((char *)nchunk, nchunk->contents, min_object_alignment - 1);
	self->next_free   = self->object_base;
	nchunk->limit     = (char *)nchunk + min_chunk_size;
	self->chunk_limit = nchunk->limit;
	nchunk->prev      = __NULLPTR;
	self->extra_arg   = arg;
	self->use_extra_arg      = 1;
	self->maybe_empty_object = 0;
	self->alloc_failed       = 0;
	return 1;
}
#include <bits/crt/obstack.h>
/* >> _obstack_newchunk(3)
 * Allocate  a new chunk of at least `num_bytes' bytes. Also: allocate
 * enough additional space for the object currently being constructed,
 * and move it to the start of the new chunk. */
INTERN ATTR_SECTION(".text.crt.heap.obstack") ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc__obstack_newchunk)(struct obstack *self,
                                             _OBSTACK_SIZE_T num_bytes) {
	void *curobj;
	struct _obstack_chunk *ochunk;
	struct _obstack_chunk *nchunk;
	size_t osize = (size_t)(self->next_free - self->object_base);
	size_t csize = osize + num_bytes + (osize >> 3) + self->alignment_mask + 100;
	if (csize < self->chunk_size)
		csize = self->chunk_size;
	/* Allocate the new chunk. */
	ochunk = self->chunk;
	nchunk = (struct _obstack_chunk *)__obstack_malloc(self, csize);
	if (!nchunk) {
		csize = osize + num_bytes + self->alignment_mask;
		if (csize < self->chunk_size)
			csize = self->chunk_size;
		nchunk = (struct _obstack_chunk *)__obstack_malloc(self, csize);
		if (!nchunk) {

			(*__LOCAL_obstack_alloc_failed_handler)();





		}
	}
	nchunk->prev      = ochunk;
	nchunk->limit     = (char *)nchunk + csize;
	self->chunk       = nchunk;
	self->chunk_limit = nchunk->limit;
	curobj = __PTR_ALIGN((char *)nchunk, nchunk->contents, self->alignment_mask);

	/* Copy the current object to the new chunk. */
	libc_memcpy(curobj, self->object_base, osize);

	/* If the old object was the only one of the old chunk, and if the
	 * old chunk couldn't possibly  have contained an "empty"  object,
	 * then we can free the old chunk. */
	if (!self->maybe_empty_object &&
	    self->object_base == __PTR_ALIGN((char *)ochunk, ochunk->contents,
	                                       self->alignment_mask)) {
		nchunk->prev = ochunk->prev;
		__obstack_free(self, ochunk);
	}

	/* Remember the specs */
	self->object_base = (char *)curobj;
	self->next_free   = (char *)curobj + osize;
	self->maybe_empty_object = 0;
}
#include <bits/crt/obstack.h>
#include <hybrid/__assert.h>
/* >> obstack_free(3)
 * Unwind the  object-stack by  freeing everything  allocated after  (and  including)
 * `obj', where `obj' *should* be a pointer previously returned by `obstack_finish()'
 * When `obj' is `NULL',  simply free everything allocated  by `self', in which  case
 * `self' must be re-initialized (via `_obstack_begin(3)') upon return. */
INTERN ATTR_SECTION(".text.crt.heap.obstack") ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc_obstack_free)(struct obstack *self,
                                        void *obj) {
	struct _obstack_chunk *iter;
	for (iter = self->chunk; iter;) {
		struct _obstack_chunk *prev;
		if (obj >= (void *)iter && obj < (void *)iter->limit)
			break;
		prev = iter->prev;
		__obstack_free(self, iter);
		iter = prev;
		self->maybe_empty_object = 1;
	}
	if (iter) {
		self->object_base = (char *)(obj);
		self->next_free   = (char *)(obj);
		self->chunk_limit = iter->limit;
		self->chunk       = iter;
	} else {
		/* If `obj == NULL', then it's allowed to not belong to `self' */
		__hybrid_assertf(obj == NULL,
		                 "Object %p does not belong to this obstack",
		                 obj);
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
		libc_memset(self, 0xcc, sizeof(*self));
#endif /* !NDEBUG && !NDEBUG_FINI */
	}
}
#include <bits/crt/obstack.h>
/* >> _obstack_memory_used(3)
 * Return the total size of all chunks allocated by `self' */
INTERN ATTR_SECTION(".text.crt.heap.obstack") ATTR_PURE WUNUSED ATTR_IN(1) _OBSTACK_SIZE_T
NOTHROW_NCX(LIBCCALL libc__obstack_memory_used)(struct obstack __KOS_FIXED_CONST *self) {
	_OBSTACK_SIZE_T result = 0;
	struct _obstack_chunk *iter;
	for (iter = self->chunk; iter; iter = iter->prev)
		result += (size_t)(iter->limit - (char *)iter);
	return result;
}
#include <bits/crt/obstack.h>
/* >> _obstack_allocated_p(3)
 * Returns non-zero if `obj' was allocated by `self' */
INTERN ATTR_SECTION(".text.crt.heap.obstack") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc__obstack_allocated_p)(struct obstack const *self,
                                                void const *obj) {
	struct _obstack_chunk *iter;
	for (iter = self->chunk; iter; iter = iter->prev) {
		if (obj >= (void *)iter && obj < (void *)iter->limit)
			return 1;
	}
	return 0;
}
#include <bits/crt/obstack.h>
/* >> obstack_printer(3)
 * A pformatprinter-compatible printer  sink that appends  data to  the
 * object currently being constructed by a given `struct obstack *arg'.
 * Note  that obstacks don't have out-of-memory errors (you have to use
 * longjmp  from a custom  `obstack_alloc_failed_handler'), so in turn,
 * this function doesn't have an error return-value!
 * HINT: Ths function does the same as `obstack_grow(3)'!
 * @return: datalen: Success. */
INTERN ATTR_SECTION(".text.crt.heap.obstack") WUNUSED ATTR_INS(2, 3) NONNULL((1)) ssize_t
NOTHROW_NCX(__FORMATPRINTER_CC libc_obstack_printer)(void *arg,
                                                     char const *__restrict data,
                                                     size_t datalen) {
	struct obstack *me = (struct obstack *)arg;
	if ((size_t)(me->chunk_limit - me->next_free) < datalen)
		libc__obstack_newchunk(me, datalen);
	me->next_free = (char *)libc_mempcpy(me->next_free, data, datalen);
	return (ssize_t)datalen;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_obstack_begin,libc__obstack_begin,ATTR_OUT(1) NONNULL((4, 5)),int,NOTHROW_NCX,LIBCCALL,(struct obstack *self, _OBSTACK_SIZE_T min_chunk_size, _OBSTACK_SIZE_T min_object_alignment, void *(__LIBCCALL *ob_malloc)(size_t num_bytes), void (__LIBCCALL *ob_free)(void *ptr)),(self,min_chunk_size,min_object_alignment,ob_malloc,ob_free));
DEFINE_PUBLIC_ALIAS_P(_obstack_begin_1,libc__obstack_begin_1,ATTR_OUT(1) NONNULL((4, 5)),int,NOTHROW_NCX,LIBCCALL,(struct obstack *self, _OBSTACK_SIZE_T min_chunk_size, _OBSTACK_SIZE_T min_object_alignment, void *(*ob_malloc)(void *arg, size_t num_bytes), void (*ob_free)(void *arg, void *ptr), void *arg),(self,min_chunk_size,min_object_alignment,ob_malloc,ob_free,arg));
DEFINE_PUBLIC_ALIAS_P_VOID(_obstack_newchunk,libc__obstack_newchunk,ATTR_INOUT(1),NOTHROW_NCX,LIBCCALL,(struct obstack *self, _OBSTACK_SIZE_T num_bytes),(self,num_bytes));
DEFINE_PUBLIC_ALIAS_P_VOID(_obstack_free,libc_obstack_free,ATTR_INOUT(1),NOTHROW_NCX,LIBCCALL,(struct obstack *self, void *obj),(self,obj));
DEFINE_PUBLIC_ALIAS_P_VOID(obstack_free,libc_obstack_free,ATTR_INOUT(1),NOTHROW_NCX,LIBCCALL,(struct obstack *self, void *obj),(self,obj));
DEFINE_PUBLIC_ALIAS_P(_obstack_memory_used,libc__obstack_memory_used,ATTR_PURE WUNUSED ATTR_IN(1),_OBSTACK_SIZE_T,NOTHROW_NCX,LIBCCALL,(struct obstack __KOS_FIXED_CONST *self),(self));
DEFINE_PUBLIC_ALIAS_P(_obstack_allocated_p,libc__obstack_allocated_p,ATTR_PURE WUNUSED ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(struct obstack const *self, void const *obj),(self,obj));
DEFINE_PUBLIC_ALIAS_P(obstack_printer,libc_obstack_printer,WUNUSED ATTR_INS(2, 3) NONNULL((1)),ssize_t,NOTHROW_NCX,__FORMATPRINTER_CC,(void *arg, char const *__restrict data, size_t datalen),(arg,data,datalen));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_OBSTACK_C */
