/* HASH CRC-32:0x9b5ee6da */
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
#ifndef GUARD_LIBC_AUTO_OBSTACK_H
#define GUARD_LIBC_AUTO_OBSTACK_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <obstack.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_OUT(1) NONNULL((4, 5)) int NOTHROW_NCX(LIBDCALL libd__obstack_begin)(struct obstack *self, _OBSTACK_SIZE_T min_chunk_size, _OBSTACK_SIZE_T min_object_alignment, void *(__LIBDCALL *ob_malloc)(size_t num_bytes), void (__LIBDCALL *ob_free)(void *ptr));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_OUT(1) NONNULL((4, 5)) int NOTHROW_NCX(LIBCCALL libc__obstack_begin)(struct obstack *self, _OBSTACK_SIZE_T min_chunk_size, _OBSTACK_SIZE_T min_object_alignment, void *(__LIBCCALL *ob_malloc)(size_t num_bytes), void (__LIBCCALL *ob_free)(void *ptr));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_OUT(1) NONNULL((4, 5)) int NOTHROW_NCX(LIBDCALL libd__obstack_begin_1)(struct obstack *self, _OBSTACK_SIZE_T min_chunk_size, _OBSTACK_SIZE_T min_object_alignment, void *(*ob_malloc)(void *arg, size_t num_bytes), void (*ob_free)(void *arg, void *ptr), void *arg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_OUT(1) NONNULL((4, 5)) int NOTHROW_NCX(LIBCCALL libc__obstack_begin_1)(struct obstack *self, _OBSTACK_SIZE_T min_chunk_size, _OBSTACK_SIZE_T min_object_alignment, void *(*ob_malloc)(void *arg, size_t num_bytes), void (*ob_free)(void *arg, void *ptr), void *arg);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> _obstack_newchunk(3)
 * Allocate  a new chunk of at least `num_bytes' bytes. Also: allocate
 * enough additional space for the object currently being constructed,
 * and move it to the start of the new chunk. */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBDCALL libd__obstack_newchunk)(struct obstack *self, _OBSTACK_SIZE_T num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> _obstack_newchunk(3)
 * Allocate  a new chunk of at least `num_bytes' bytes. Also: allocate
 * enough additional space for the object currently being constructed,
 * and move it to the start of the new chunk. */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBCCALL libc__obstack_newchunk)(struct obstack *self, _OBSTACK_SIZE_T num_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> obstack_free(3)
 * Unwind the  object-stack by  freeing everything  allocated after  (and  including)
 * `obj', where `obj' *should* be a pointer previously returned by `obstack_finish()'
 * When `obj' is `NULL',  simply free everything allocated  by `self', in which  case
 * `self' must be re-initialized (via `_obstack_begin(3)') upon return. */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBDCALL libd_obstack_free)(struct obstack *self, void *obj);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> obstack_free(3)
 * Unwind the  object-stack by  freeing everything  allocated after  (and  including)
 * `obj', where `obj' *should* be a pointer previously returned by `obstack_finish()'
 * When `obj' is `NULL',  simply free everything allocated  by `self', in which  case
 * `self' must be re-initialized (via `_obstack_begin(3)') upon return. */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBCCALL libc_obstack_free)(struct obstack *self, void *obj);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> _obstack_memory_used(3)
 * Return the total size of all chunks allocated by `self' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) _OBSTACK_SIZE_T NOTHROW_NCX(LIBDCALL libd__obstack_memory_used)(struct obstack __KOS_FIXED_CONST *self);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> _obstack_memory_used(3)
 * Return the total size of all chunks allocated by `self' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) _OBSTACK_SIZE_T NOTHROW_NCX(LIBCCALL libc__obstack_memory_used)(struct obstack __KOS_FIXED_CONST *self);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> _obstack_allocated_p(3)
 * Returns non-zero if `obj' was allocated by `self' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd__obstack_allocated_p)(struct obstack const *self, void const *obj);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> _obstack_allocated_p(3)
 * Returns non-zero if `obj' was allocated by `self' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc__obstack_allocated_p)(struct obstack const *self, void const *obj);
/* >> obstack_printer(3)
 * A pformatprinter-compatible printer  sink that appends  data to  the
 * object currently being constructed by a given `struct obstack *arg'.
 * Note  that obstacks don't have out-of-memory errors (you have to use
 * longjmp  from a custom  `obstack_alloc_failed_handler'), so in turn,
 * this function doesn't have an error return-value!
 * HINT: Ths function does the same as `obstack_grow(3)'!
 * @return: datalen: Success. */
INTDEF WUNUSED ATTR_INS(2, 3) NONNULL((1)) ssize_t NOTHROW_NCX(__FORMATPRINTER_CC libc_obstack_printer)(void *arg, char const *__restrict data, size_t datalen);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_OBSTACK_H */
