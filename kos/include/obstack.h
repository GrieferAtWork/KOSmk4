/* HASH CRC-32:0x605468f4 */
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
/* (#) Portability: EMX kLIBC     (/libc/include/obstack.h) */
/* (#) Portability: GNU C Library (/malloc/obstack.h) */
/* (#) Portability: libc4/5       (/include/obstack.h) */
/* (#) Portability: libc6         (/include/obstack.h) */
/* (#) Portability: mintlib       (/include/obstack.h) */
/* (#) Portability: uClibc        (/include/obstack.h) */
#ifndef _OBSTACK_H
#define _OBSTACK_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <bits/crt/obstack.h>
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
#include <libc/string.h>

#ifdef __USE_GLIBC
#include <stddef.h>
#include <string.h>
#endif /* __USE_GLIBC */


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

#ifdef __CRT_HAVE__obstack_begin
__CDECLARE(__ATTR_NONNULL((1, 4, 5)),int,__NOTHROW_NCX,_obstack_begin,(struct obstack *__self, _OBSTACK_SIZE_T __min_chunk_size, _OBSTACK_SIZE_T __min_object_alignment, void *(__LIBCCALL *__ob_malloc)(size_t __num_bytes), void (__LIBCCALL *__ob_free)(void *__ptr)),(__self,__min_chunk_size,__min_object_alignment,__ob_malloc,__ob_free))
#elif defined(__LOCAL_obstack_alloc_failed_handler) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)
#include <libc/local/obstack/_obstack_begin.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_obstack_begin, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4, 5)) int __NOTHROW_NCX(__LIBCCALL _obstack_begin)(struct obstack *__self, _OBSTACK_SIZE_T __min_chunk_size, _OBSTACK_SIZE_T __min_object_alignment, void *(__LIBCCALL *__ob_malloc)(size_t __num_bytes), void (__LIBCCALL *__ob_free)(void *__ptr)) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_obstack_begin))(__self, __min_chunk_size, __min_object_alignment, __ob_malloc, __ob_free); })
#endif /* ... */
#ifdef __CRT_HAVE__obstack_begin_1
__CDECLARE(__ATTR_NONNULL((1, 4, 5)),int,__NOTHROW_NCX,_obstack_begin_1,(struct obstack *__self, _OBSTACK_SIZE_T __min_chunk_size, _OBSTACK_SIZE_T __min_object_alignment, void *(*__ob_malloc)(void *__arg, size_t __num_bytes), void (*__ob_free)(void *__arg, void *__ptr), void *__arg),(__self,__min_chunk_size,__min_object_alignment,__ob_malloc,__ob_free,__arg))
#elif defined(__LOCAL_obstack_alloc_failed_handler) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)
#include <libc/local/obstack/_obstack_begin_1.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_obstack_begin_1, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4, 5)) int __NOTHROW_NCX(__LIBCCALL _obstack_begin_1)(struct obstack *__self, _OBSTACK_SIZE_T __min_chunk_size, _OBSTACK_SIZE_T __min_object_alignment, void *(*__ob_malloc)(void *__arg, size_t __num_bytes), void (*__ob_free)(void *__arg, void *__ptr), void *__arg) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_obstack_begin_1))(__self, __min_chunk_size, __min_object_alignment, __ob_malloc, __ob_free, __arg); })
#endif /* ... */
#ifdef __CRT_HAVE__obstack_newchunk
/* >> _obstack_newchunk(3)
 * Allocate  a new chunk of at least `num_bytes' bytes. Also: allocate
 * enough additional space for the object currently being constructed,
 * and move it to the start of the new chunk. */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_obstack_newchunk,(struct obstack *__self, _OBSTACK_SIZE_T __num_bytes),(__self,__num_bytes))
#elif defined(__LOCAL_obstack_alloc_failed_handler) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)
#include <libc/local/obstack/_obstack_newchunk.h>
/* >> _obstack_newchunk(3)
 * Allocate  a new chunk of at least `num_bytes' bytes. Also: allocate
 * enough additional space for the object currently being constructed,
 * and move it to the start of the new chunk. */
__NAMESPACE_LOCAL_USING_OR_IMPL(_obstack_newchunk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _obstack_newchunk)(struct obstack *__self, _OBSTACK_SIZE_T __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_obstack_newchunk))(__self, __num_bytes); })
#endif /* ... */
#ifdef __CRT_HAVE_obstack_free
/* >> obstack_free(3)
 * Unwind the  object-stack by  freeing everything  allocated after  (and  including)
 * `obj', where `obj' *should* be a pointer previously returned by `obstack_finish()'
 * When `obj' is `NULL',  simply free everything allocated  by `self', in which  case
 * `self' must be re-initialized (via `_obstack_begin(3)') upon return. */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,obstack_free,(struct obstack *__self, void *__obj),(__self,__obj))
#elif defined(__CRT_HAVE__obstack_free)
/* >> obstack_free(3)
 * Unwind the  object-stack by  freeing everything  allocated after  (and  including)
 * `obj', where `obj' *should* be a pointer previously returned by `obstack_finish()'
 * When `obj' is `NULL',  simply free everything allocated  by `self', in which  case
 * `self' must be re-initialized (via `_obstack_begin(3)') upon return. */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,obstack_free,(struct obstack *__self, void *__obj),_obstack_free,(__self,__obj))
#else /* ... */
#include <libc/local/obstack/obstack_free.h>
/* >> obstack_free(3)
 * Unwind the  object-stack by  freeing everything  allocated after  (and  including)
 * `obj', where `obj' *should* be a pointer previously returned by `obstack_finish()'
 * When `obj' is `NULL',  simply free everything allocated  by `self', in which  case
 * `self' must be re-initialized (via `_obstack_begin(3)') upon return. */
__NAMESPACE_LOCAL_USING_OR_IMPL(obstack_free, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL obstack_free)(struct obstack *__self, void *__obj) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(obstack_free))(__self, __obj); })
#endif /* !... */
#ifdef __CRT_HAVE__obstack_memory_used
/* >> _obstack_memory_used(3)
 * Return the total size of all chunks allocated by `self' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),_OBSTACK_SIZE_T,__NOTHROW_NCX,_obstack_memory_used,(struct obstack __KOS_FIXED_CONST *__self),(__self))
#else /* __CRT_HAVE__obstack_memory_used */
#include <libc/local/obstack/_obstack_memory_used.h>
/* >> _obstack_memory_used(3)
 * Return the total size of all chunks allocated by `self' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_obstack_memory_used, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) _OBSTACK_SIZE_T __NOTHROW_NCX(__LIBCCALL _obstack_memory_used)(struct obstack __KOS_FIXED_CONST *__self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_obstack_memory_used))(__self); })
#endif /* !__CRT_HAVE__obstack_memory_used */

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
#define obstack_specify_allocation(self, min_chunk_size, alignment, chunkfun, freefun) \
	_obstack_begin(self, min_chunk_size, alignment,                                    \
	               _OBSTACK_CAST(void *(*)(size_t), chunkfun),                         \
	               _OBSTACK_CAST(void (*)(void *), freefun))
#define obstack_specify_allocation_with_arg(self, min_chunk_size, alignment, chunkfun, freefun, arg) \
	_obstack_begin_1(self, min_chunk_size, alignment,                                                \
	                 _OBSTACK_CAST(void *(*)(void *, size_t), chunkfun),                             \
	                 _OBSTACK_CAST(void (*)(void *, void *), freefun), arg)

/* >> obstack_memory_used(3)
 * Return the total size of all chunks allocated by `self' */
#define obstack_memory_used(self) _obstack_memory_used(self)

/* Get information about the current object/chunk */
#define obstack_base(self)           (void *)(self)->object_base
#define obstack_chunk_size(self)     (self)->chunk_size
#define obstack_next_free(self)      (void *)(self)->next_free
#define obstack_alignment_mask(self) (self)->alignment_mask

/* Override the chunk alloc/free functions used by `self'. */
#define obstack_chunkfun(self, new_chunkfun) (void)((self)->chunkfun.extra = (void *(*)(void *, size_t))(new_chunkfun))
#define obstack_freefun(self, new_freefun)   (void)((self)->freefun.extra = (void *(*)(void *, void *))(new_freefun))

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
	((self)->next_free == (self)->object_base                 \
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
		if ((self)->next_free == __of_res)                       \
			(self)->maybe_empty_object = 1;                      \
		(self)->next_free = __PTR_ALIGN((self)->object_base,     \
		                                (self)->next_free,       \
		                                (self)->alignment_mask); \
		if ((self)->next_free > (self)->chunk_limit)             \
			(self)->next_free = (self)->chunk_limit;             \
		(self)->object_base = (self)->next_free;                 \
		__of_res;                                                \
	})
#endif /* !__NO_XBLOCK */

/* >> obstack_free(3)
 * Unwind  the  object-stack by  freeing  everything allocated  after  (and including)
 * `obj', where `obj' *should* be a pointer previously returned by `obstack_finish()'. */
#if defined(__NO_XBLOCK) || defined(__OPTIMIZE_SIZE__)
#define obstack_free(self, obj) (__obstack_free)(self, obj)
#else /* __NO_XBLOCK || __OPTIMIZE_SIZE__ */
#define obstack_free(self, obj)                                                         \
	__XBLOCK({                                                                          \
		void *__of_obj = (void *)(obj);                                                 \
		if (__of_obj > (void *)(self)->chunk && __of_obj < (void *)(self)->chunk_limit) \
			(self)->next_free = (self)->object_base = (char *)__of_obj;                 \
		else {                                                                          \
			(__obstack_free)(self, __of_obj);                                           \
		}                                                                               \
	})
#endif /* !__NO_XBLOCK && !__OPTIMIZE_SIZE__ */
#ifndef __obstack_free
#define __obstack_free obstack_free
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


#ifdef __USE_KOS
#ifdef __CRT_HAVE_obstack_printer
/* >> obstack_printer(3)
 * A pformatprinter-compatible printer  sink that appends  data to  the
 * object currently being constructed by a given `struct obstack *arg'.
 * Note that obstacks don't have out-of-memory errors (you have to use
 * longjmp from a custom `obstack_alloc_failed_handler'), so in turn,
 * this function doesn't have an error return-value!
 * HINT: Ths function does the same as `obstack_grow(3)'!
 * @return: datalen: Success. */
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC obstack_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __CASMNAME_SAME("obstack_printer");
#elif defined(__CRT_HAVE__obstack_newchunk) || defined(__LOCAL_obstack_alloc_failed_handler) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)
#include <libc/local/obstack/obstack_printer.h>
/* >> obstack_printer(3)
 * A pformatprinter-compatible printer  sink that appends  data to  the
 * object currently being constructed by a given `struct obstack *arg'.
 * Note that obstacks don't have out-of-memory errors (you have to use
 * longjmp from a custom `obstack_alloc_failed_handler'), so in turn,
 * this function doesn't have an error return-value!
 * HINT: Ths function does the same as `obstack_grow(3)'!
 * @return: datalen: Success. */
__NAMESPACE_LOCAL_USING_OR_IMPL(obstack_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC obstack_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(obstack_printer))(__arg, __data, __datalen); })
#endif /* ... */
#endif /* __USE_KOS */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_OBSTACK_H */
