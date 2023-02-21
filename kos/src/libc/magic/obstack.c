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
%(c_prefix){
/* (#) Portability: EMX kLIBC     (/libc/include/obstack.h) */
/* (#) Portability: GNU C Library (/malloc/obstack.h) */
/* (#) Portability: GNU Hurd      (/usr/include/obstack.h) */
/* (#) Portability: libc4/5       (/include/obstack.h) */
/* (#) Portability: libc6         (/include/obstack.h) */
/* (#) Portability: mintlib       (/include/obstack.h) */
/* (#) Portability: uClibc        (/include/obstack.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.heap.obstack")]

%[define_decl_include_implication("<bits/crt/obstack.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/crt/obstack.h>": ["struct obstack", "_OBSTACK_SIZE_T", "_CHUNK_SIZE_T"])]


%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <bits/crt/obstack.h>
)]%[insert:prefix(
#include <bits/crt/format-printer.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <libc/string.h>
)]%{

#ifdef __USE_GLIBC_BLOAT
#include <stddef.h>
#include <string.h>
#endif /* __USE_GLIBC_BLOAT */

}%{

#ifndef __attribute_pure__
#define __attribute_pure__ __ATTR_PURE
#endif /* !__attribute_pure__ */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#define PTR_INT_TYPE __PTRDIFF_TYPE__

/* [1..1] Allocation failure handler. (never  returns)
 * Defaults to a function that prints an error message
 * to stderr, then does `exit(obstack_exit_failure)'.
 * HINT: The message is `gettext("memory exhausted")'
 * HINT: This function is allowed to `longjmp(3)'! */
#ifndef obstack_alloc_failed_handler
#ifdef __LOCAL_obstack_alloc_failed_handler
#define obstack_alloc_failed_handler __LOCAL_obstack_alloc_failed_handler
#elif defined(__CRT_HAVE_obstack_alloc_failed_handler)
__CSDECLARE2(,void (__LIBKCALL *obstack_alloc_failed_handler)(void),obstack_alloc_failed_handler)
#define obstack_alloc_failed_handler obstack_alloc_failed_handler
#endif /* __CRT_HAVE_obstack_alloc_failed_handler */
#endif /* !obstack_alloc_failed_handler */

/* Program exit code for when an allocation fails (defaults to `EXIT_FAILURE') */
#ifndef obstack_exit_failure
#ifdef __LOCAL_obstack_exit_failure
#define obstack_exit_failure __LOCAL_obstack_exit_failure
#elif defined(__CRT_HAVE_obstack_exit_failure)
__CSDECLARE(,int,obstack_exit_failure)
#define obstack_exit_failure obstack_exit_failure
#endif /* __CRT_HAVE_obstack_exit_failure */
#endif /* !obstack_exit_failure */

}

%[declare_user_export("_obstack")]
%[declare_user_export("obstack_alloc_failed_handler")]
%[declare_user_export("obstack_exit_failure")]

%[assume_defined_in_kos_userspace(__LOCAL_obstack_exit_failure, obstack_exit_failure)]
%[assume_defined_in_kos_userspace(__LOCAL_obstack_alloc_failed_handler, obstack_alloc_failed_handler)]

%(auto_source){
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
}


%[define_replacement(_OBSTACK_SIZE_T = __SIZE_TYPE__)]
%[define_replacement(_CHUNK_SIZE_T = __SIZE_TYPE__)]

[[decl_include("<bits/crt/obstack.h>")]]
[[impl_include("<bits/crt/obstack.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_include("<bits/crt/obstack.h>")]]
[[requires(defined(__LOCAL_obstack_alloc_failed_handler) || $has_function(exit))]]
int _obstack_begin([[out]] struct obstack *self,
                   _OBSTACK_SIZE_T min_chunk_size,
                   _OBSTACK_SIZE_T min_object_alignment,
                   [[nonnull]] void *(__LIBCCALL *ob_malloc)(size_t num_bytes),
                   [[nonnull]] void (__LIBCCALL *ob_free)(void *ptr)) {
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

	self->@chunkfun@.@plain@ = (void *(__LIBCCALL *)(__SIZE_TYPE__))ob_malloc;
	self->@freefun@.@plain@  = (void (__LIBCCALL *)(void *))ob_free;
	self->@chunk_size@       = min_chunk_size;
	self->@alignment_mask@   = min_object_alignment - 1;

	nchunk = (struct _obstack_chunk *)((*ob_malloc)(min_chunk_size));
	if (!nchunk) {
@@pp_ifdef __LOCAL_obstack_alloc_failed_handler@@
		(*__LOCAL_obstack_alloc_failed_handler)();
@@pp_elif defined(__LOCAL_obstack_exit_failure)@@
		exit(__LOCAL_obstack_exit_failure);
@@pp_else@@
		exit(1);
@@pp_endif@@
	}
	self->@chunk@       = nchunk;
	self->@object_base@ = __PTR_ALIGN((char *)nchunk, nchunk->@contents@, min_object_alignment - 1);
	self->@next_free@   = self->@object_base@;
	nchunk->@limit@     = (char *)nchunk + min_chunk_size;
	self->@chunk_limit@ = nchunk->@limit@;
	nchunk->@prev@      = __NULLPTR;
	self->@use_extra_arg@      = 0;
	self->@maybe_empty_object@ = 0;
	self->@alloc_failed@       = 0;
	return 1;
}

[[decl_include("<bits/crt/obstack.h>")]]
[[impl_include("<bits/crt/obstack.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[requires_include("<bits/crt/obstack.h>")]]
[[requires(defined(__LOCAL_obstack_alloc_failed_handler) || $has_function(exit))]]
int _obstack_begin_1([[out]] struct obstack *self,
                     _OBSTACK_SIZE_T min_chunk_size,
                     _OBSTACK_SIZE_T min_object_alignment,
                     [[nonnull]] void *(*ob_malloc)(void *arg, size_t num_bytes),
                     [[nonnull]] void (*ob_free)(void *arg, void *ptr),
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

	self->@chunkfun@.@extra@ = (void *(__LIBCCALL *)(void *, __SIZE_TYPE__))ob_malloc;
	self->@freefun@.@extra@  = (void (__LIBCCALL *)(void *, void *))ob_free;
	self->@chunk_size@       = min_chunk_size;
	self->@alignment_mask@   = min_object_alignment - 1;

	nchunk = (struct _obstack_chunk *)((*ob_malloc)(arg, min_chunk_size));
	if (!nchunk) {
@@pp_ifdef __LOCAL_obstack_alloc_failed_handler@@
		(*__LOCAL_obstack_alloc_failed_handler)();
@@pp_elif defined(__LOCAL_obstack_exit_failure)@@
		exit(__LOCAL_obstack_exit_failure);
@@pp_else@@
		exit(1);
@@pp_endif@@
	}
	self->@chunk@       = nchunk;
	self->@object_base@ = __PTR_ALIGN((char *)nchunk, nchunk->@contents@, min_object_alignment - 1);
	self->@next_free@   = self->@object_base@;
	nchunk->@limit@     = (char *)nchunk + min_chunk_size;
	self->@chunk_limit@ = nchunk->@limit@;
	nchunk->@prev@      = __NULLPTR;
	self->@extra_arg@   = arg;
	self->@use_extra_arg@      = 1;
	self->@maybe_empty_object@ = 0;
	self->@alloc_failed@       = 0;
	return 1;
}


@@>> _obstack_newchunk(3)
@@Allocate  a new chunk of at least `num_bytes' bytes. Also: allocate
@@enough additional space for the object currently being constructed,
@@and move it to the start of the new chunk.
[[decl_include("<bits/crt/obstack.h>")]]
[[impl_include("<bits/crt/obstack.h>")]]
[[requires_include("<bits/crt/obstack.h>")]]
[[requires(defined(__LOCAL_obstack_alloc_failed_handler) || $has_function(exit))]]
void _obstack_newchunk([[inout]] struct obstack *self, _OBSTACK_SIZE_T num_bytes) {
	void *curobj;
	struct _obstack_chunk *ochunk;
	struct _obstack_chunk *nchunk;
	size_t osize = (size_t)(self->@next_free@ - self->@object_base@);
	size_t csize = osize + num_bytes + (osize >> 3) + self->@alignment_mask@ + 100;
	if (csize < self->@chunk_size@)
		csize = self->@chunk_size@;
	/* Allocate the new chunk. */
	ochunk = self->@chunk@;
	nchunk = (struct _obstack_chunk *)__obstack_malloc(self, csize);
	if (!nchunk) {
		csize = osize + num_bytes + self->@alignment_mask@;
		if (csize < self->@chunk_size@)
			csize = self->@chunk_size@;
		nchunk = (struct _obstack_chunk *)__obstack_malloc(self, csize);
		if (!nchunk) {
@@pp_ifdef __LOCAL_obstack_alloc_failed_handler@@
			(*__LOCAL_obstack_alloc_failed_handler)();
@@pp_elif defined(__LOCAL_obstack_exit_failure)@@
			exit(__LOCAL_obstack_exit_failure);
@@pp_else@@
			exit(1);
@@pp_endif@@
		}
	}
	nchunk->@prev@      = ochunk;
	nchunk->@limit@     = (char *)nchunk + csize;
	self->@chunk@       = nchunk;
	self->@chunk_limit@ = nchunk->@limit@;
	curobj = __PTR_ALIGN((char *)nchunk, nchunk->@contents@, self->@alignment_mask@);

	/* Copy the current object to the new chunk. */
	memcpy(curobj, self->@object_base@, osize);

	/* If the old object was the only one of the old chunk, and if the
	 * old chunk couldn't possibly  have contained an "empty"  object,
	 * then we can free the old chunk. */
	if (!self->@maybe_empty_object@ &&
	    self->@object_base@ == __PTR_ALIGN((char *)ochunk, ochunk->@contents@,
	                                       self->@alignment_mask@)) {
		nchunk->@prev@ = ochunk->@prev@;
		__obstack_free(self, ochunk);
	}

	/* Remember the specs */
	self->@object_base@ = (char *)curobj;
	self->@next_free@   = (char *)curobj + osize;
	self->@maybe_empty_object@ = 0;
}

@@>> obstack_free(3)
@@Unwind the  object-stack by  freeing everything  allocated after  (and  including)
@@`obj', where `obj' *should* be a pointer previously returned by `obstack_finish()'
@@When `obj' is `NULL',  simply free everything allocated  by `self', in which  case
@@`self' must be re-initialized (via `_obstack_begin(3)') upon return.
[[export_alias("_obstack_free")]]
[[decl_include("<bits/crt/obstack.h>")]]
[[impl_include("<bits/crt/obstack.h>")]]
[[impl_include("<hybrid/__assert.h>")]]
void obstack_free([[inout]] struct obstack *self, void *obj) {
	struct _obstack_chunk *iter;
	for (iter = self->@chunk@; iter;) {
		struct _obstack_chunk *prev;
		if (obj >= (void *)iter && obj < (void *)iter->@limit@)
			break;
		prev = iter->@prev@;
		__obstack_free(self, iter);
		iter = prev;
		self->@maybe_empty_object@ = 1;
	}
	if (iter) {
		self->@object_base@ = (char *)(obj);
		self->@next_free@   = (char *)(obj);
		self->@chunk_limit@ = iter->@limit@;
		self->@chunk@       = iter;
	} else {
		/* If `obj == NULL', then it's allowed to not belong to `self' */
		__hybrid_assertf(obj == NULL,
		                 "Object %p does not belong to this obstack",
		                 obj);
@@pp_if !defined(NDEBUG) && !defined(NDEBUG_FINI)@@
		memset(self, 0xcc, sizeof(*self));
@@pp_endif@@
	}
}

@@>> _obstack_memory_used(3)
@@Return the total size of all chunks allocated by `self'
[[pure, wunused, decl_include("<features.h>")]]
[[decl_include("<bits/crt/obstack.h>")]]
[[impl_include("<bits/crt/obstack.h>")]]
_OBSTACK_SIZE_T _obstack_memory_used([[in]] struct obstack __KOS_FIXED_CONST *self) {
	_OBSTACK_SIZE_T result = 0;
	struct _obstack_chunk *iter;
	for (iter = self->@chunk@; iter; iter = iter->@prev@)
		result += (size_t)(iter->@limit@ - (char *)iter);
	return result;
}


@@>> _obstack_allocated_p(3)
@@Returns non-zero if `obj' was allocated by `self'
[[hidden, pure, wunused]]
[[decl_include("<bits/crt/obstack.h>")]]
[[impl_include("<bits/crt/obstack.h>")]]
int _obstack_allocated_p([[in]] struct obstack const *self, void const *obj) {
	struct _obstack_chunk *iter;
	for (iter = self->@chunk@; iter; iter = iter->@prev@) {
		if (obj >= (void *)iter && obj < (void *)iter->@limit@)
			return 1;
	}
	return 0;
}

%{

#if 0 /* To-be provided by the user (referenced by `obstack_init(3)') */
void *obstack_chunk_alloc(size_t num_bytes);
void obstack_chunk_free(void *ptr);
#elif 0 /* ... or you could just do this: */
#include <stdlib.h>
#define obstack_chunk_alloc malloc
#define obstack_chunk_free  free
#endif


/* Object stack initializer functions. */
#define obstack_init(self)                                                \
	_obstack_begin(self, 0, 0,                                            \
	               _OBSTACK_CAST(void *(*)(size_t), obstack_chunk_alloc), \
	               _OBSTACK_CAST(void (*)(void *), obstack_chunk_free))
#define obstack_begin(self, min_chunk_size)                               \
	_obstack_begin(self, min_chunk_size, 0,                               \
	               _OBSTACK_CAST(void *(*)(size_t), obstack_chunk_alloc), \
	               _OBSTACK_CAST(void (*)(void *), obstack_chunk_free))
#define obstack_specify_allocation(self, min_chunk_size, min_object_alignment, ob_malloc, ob_free) \
	_obstack_begin(self, min_chunk_size, min_object_alignment,                                     \
	               _OBSTACK_CAST(void *(*)(size_t), ob_malloc),                                    \
	               _OBSTACK_CAST(void (*)(void *), ob_free))
#define obstack_specify_allocation_with_arg(self, min_chunk_size, min_object_alignment, ob_malloc, ob_free, arg) \
	_obstack_begin_1(self, min_chunk_size, min_object_alignment,                                                 \
	                 _OBSTACK_CAST(void *(*)(void *, size_t), ob_malloc),                                        \
	                 _OBSTACK_CAST(void (*)(void *, void *), ob_free), arg)

/* >> obstack_memory_used(3)
 * Return the total size of all chunks allocated by `self' */
#define obstack_memory_used(self) _obstack_memory_used(self)

/* Get information about the current object/chunk */
#define obstack_base(self)           (void *)(self)->object_base
#define obstack_chunk_size(self)     (self)->chunk_size
#define obstack_next_free(self)      (void *)(self)->next_free
#define obstack_alignment_mask(self) (self)->alignment_mask

/* Override the chunk alloc/free functions used by `self'. */
#define obstack_chunkfun(self, new_ob_malloc) (void)((self)->chunkfun.extra = (void *(*)(void *, size_t))(new_ob_malloc))
#define obstack_freefun(self, new_ob_free)    (void)((self)->freefun.extra = (void *(*)(void *, void *))(new_ob_free))

/* Return the num_bytes of the current object. */
#define obstack_object_size(self) (_OBSTACK_SIZE_T)((self)->next_free - (self)->object_base)

/* Returns non-zero if nothing has yet to be written to the given obstack. */
#define obstack_empty_p(self)                                  \
	((self)->chunk->prev == __NULLPTR &&                       \
	 (self)->next_free == __PTR_ALIGN((char *)(self)->chunk,   \
	                                  (self)->chunk->contents, \
	                                  (self)->alignment_mask))

/* Return the amount of free, pending bytes. */
#define obstack_room(self) (_OBSTACK_SIZE_T)((self)->chunk_limit - (self)->next_free)

/* Without checking if space is sufficient, append a char, integer, or pointer */
#define obstack_1grow_fast(self, char_value)   (void)(*(self)->next_free++ = (char_value))
#define obstack_int_grow_fast(self, int_value) __obstack_Tgrow_fast(self, int, int_value)
#define obstack_ptr_grow_fast(self, ptr_value) __obstack_Tgrow_fast(self, void const *, ptr_value)
#define __obstack_Tgrow_fast(self, T, value)  \
	(void)(*(T *)(self)->next_free = (value), \
	       (self)->next_free += sizeof(T))

/* Without checking if space is sufficient, skip ahead `n' bytes */
#define obstack_blank_fast(self, n) (void)((self)->next_free += (n))

/* Ensure sufficient space for `num_bytes' bytes. */
#ifdef __NO_XBLOCK
#define obstack_make_room(self, num_bytes)       \
	(void)((self)->temp.__tempsiz = (num_bytes), \
	       __obstack_make_room(self, (self)->temp.__tempsiz))
#else /* __NO_XBLOCK */
#define obstack_make_room(self, num_bytes)        \
	__XBLOCK({                                    \
		_OBSTACK_SIZE_T __omr_size = (num_bytes); \
		__obstack_make_room(self, __omr_size);    \
		(void)0;                                  \
	})
#endif /* !__NO_XBLOCK */
#define __obstack_make_room(self, num_bytes) \
	(obstack_room(self) < (num_bytes) ? _obstack_newchunk(self, num_bytes) : (void)0)

/* Append `src...+=num_bytes' */
#ifdef __NO_XBLOCK
#define obstack_grow(self, src, num_bytes)                    \
	(void)((self)->temp.__tempsiz = (num_bytes),              \
	       __obstack_make_room(self, (self)->temp.__tempsiz), \
	       (self)->next_free = (char *)__libc_mempcpy((self)->next_free, src, (self)->temp.__tempsiz))
#else /* __NO_XBLOCK */
#define obstack_grow(self, src, num_bytes)                                             \
	__XBLOCK({                                                                         \
		_OBSTACK_SIZE_T __og_size = (num_bytes);                                       \
		__obstack_make_room(self, __og_size);                                          \
		(self)->next_free = (char *)__libc_mempcpy((self)->next_free, src, __og_size); \
		(void)0;                                                                       \
	})
#endif /* !__NO_XBLOCK */

/* Append `src...+=num_bytes', followed by '\0' */
#ifdef __NO_XBLOCK
#define obstack_grow0(self, src, num_bytes)                                                               \
	(void)((self)->temp.__tempsiz = (num_bytes),                                                          \
	       __obstack_make_room(self, (self)->temp.__tempsiz + 1);                                         \
	       (self)->next_free    = (char *)__libc_mempcpy((self)->next_free, src, (self)->temp.__tempsiz); \
	       *(self)->next_free++ = 0)
#else /* __NO_XBLOCK */
#define obstack_grow0(self, src, num_bytes)                                               \
	__XBLOCK({                                                                            \
		_OBSTACK_SIZE_T __og0_len = (num_bytes);                                          \
		__obstack_make_room(self, __og0_len + 1);                                         \
		(self)->next_free    = (char *)__libc_mempcpy((self)->next_free, src, __og0_len); \
		*(self)->next_free++ = 0;                                                         \
		(void)0;                                                                          \
	})
#endif /* !__NO_XBLOCK */

/* Append a char, integer, or pointer */
#define obstack_1grow(self, char_value)   (__obstack_make_room(self, 1), obstack_1grow_fast(self, char_value))
#define obstack_ptr_grow(self, ptr_value) (__obstack_make_room(self, sizeof(void *)), obstack_ptr_grow_fast(self, ptr_value))
#define obstack_int_grow(self, int_value) (__obstack_make_room(self, sizeof(int)), obstack_int_grow_fast(self, int_value))

/* Skip ahead `num_bytes' bytes */
#ifdef __NO_XBLOCK
#define obstack_blank(self, num_bytes)                  \
	((self)->temp.__tempsiz = (num_bytes),              \
	 __obstack_make_room(self, (self)->temp.__tempsiz), \
	 obstack_blank_fast(self, (self)->temp.__tempsiz))
#else /* __NO_XBLOCK */
#define obstack_blank(self, num_bytes)             \
	__XBLOCK({                                     \
		_OBSTACK_SIZE_T __ob_nbytes = (num_bytes); \
		__obstack_make_room(self, __ob_nbytes);    \
		obstack_blank_fast(self, __ob_nbytes);     \
	})
#endif /* !__NO_XBLOCK */

/* Finalize the current object and return its base address. */
#ifdef __NO_XBLOCK
#define obstack_finish(self)                                  \
	((void *)(self)->next_free == (void *)(self)->object_base \
	 ? (void)((self)->maybe_empty_object = 1)                 \
	 : (void)0,                                               \
	 (self)->next_free = __PTR_ALIGN((self)->object_base,     \
	                                 (self)->next_free,       \
	                                 (self)->alignment_mask), \
	 (self)->next_free > (self)->chunk_limit                  \
	 ? (void)((self)->next_free = (self)->chunk_limit)        \
	 : (void)0,                                               \
	 (self)->temp.tempptr = (void *)(self)->object_base,      \
	 (self)->object_base  = (self)->next_free,                \
	 (self)->temp.tempptr)
#else /* __NO_XBLOCK */
#define obstack_finish(self)                                     \
	__XBLOCK({                                                   \
		void *__of_res = (void *)(self)->object_base;            \
		if ((void *)(self)->next_free == __of_res)               \
			(self)->maybe_empty_object = 1;                      \
		(self)->next_free = __PTR_ALIGN((char *)__of_res,        \
		                                (self)->next_free,       \
		                                (self)->alignment_mask); \
		if ((self)->next_free > (self)->chunk_limit)             \
			(self)->next_free = (self)->chunk_limit;             \
		(self)->object_base = (self)->next_free;                 \
		__of_res;                                                \
	})
#endif /* !__NO_XBLOCK */

/* >> obstack_free(3)
 * Unwind the  object-stack by  freeing everything  allocated after  (and  including)
 * `obj', where `obj' *should* be a pointer previously returned by `obstack_finish()'
 * When `obj' is `NULL',  simply free everything allocated  by `self', in which  case
 * `self' must be re-initialized (via `_obstack_begin(3)') upon return. */
#if defined(__NO_XBLOCK) || defined(__OPTIMIZE_SIZE__)
#define obstack_free(self, obj) __obstack_free(self, obj)
#else /* __NO_XBLOCK || __OPTIMIZE_SIZE__ */
#define obstack_free(self, obj)                                                         \
	__XBLOCK({                                                                          \
		void *__of_obj = (void *)(obj);                                                 \
		if (__of_obj > (void *)(self)->chunk && __of_obj < (void *)(self)->chunk_limit) \
			(self)->next_free = (self)->object_base = (char *)__of_obj;                 \
		else {                                                                          \
			__obstack_free(self, __of_obj);                                             \
		}                                                                               \
	})
#endif /* !__NO_XBLOCK && !__OPTIMIZE_SIZE__ */
#ifndef __obstack_free
#define __obstack_free (obstack_free)
#endif /* !__obstack_free */

/* Combination of `obstack_blank()' + `obstack_finish()' */
#define obstack_alloc(self, num_bytes) \
	(obstack_blank(self, num_bytes), obstack_finish(self))

/* Combination of `obstack_grow()' + `obstack_finish()' */
#define obstack_copy(self, src, num_bytes) \
	(obstack_grow(self, src, num_bytes), obstack_finish(self))

/* Combination of `obstack_grow0()' + `obstack_finish()' */
#define obstack_copy0(self, src, num_bytes) \
	(obstack_grow0(self, src, num_bytes), obstack_finish(self))


}
%#ifdef __USE_KOS

@@>> obstack_printer(3)
@@A pformatprinter-compatible printer  sink that appends  data to  the
@@object currently being constructed by a given `struct obstack *arg'.
@@Note  that obstacks don't have out-of-memory errors (you have to use
@@longjmp  from a custom  `obstack_alloc_failed_handler'), so in turn,
@@this function doesn't have an error return-value!
@@HINT: Ths function does the same as `obstack_grow(3)'!
@@@return: datalen: Success.
[[wunused, no_crt_dos_wrapper, cc(__FORMATPRINTER_CC)]]
[[decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
[[impl_include("<bits/crt/obstack.h>"), requires_function(_obstack_newchunk)]]
$ssize_t obstack_printer([[nonnull]] /*struct obstack **/ void *arg,
                         [[in(datalen)]] /*utf-8*/ char const *__restrict data, $size_t datalen) {
	struct obstack *me = (struct obstack *)arg;
	if ((size_t)(me->@chunk_limit@ - me->@next_free@) < datalen)
		_obstack_newchunk(me, datalen);
	me->@next_free@ = (char *)mempcpy(me->@next_free@, data, datalen);
	return (ssize_t)datalen;
}

%#endif /* __USE_KOS */
%{


__SYSDECL_END
#endif /* __CC__ */

}
