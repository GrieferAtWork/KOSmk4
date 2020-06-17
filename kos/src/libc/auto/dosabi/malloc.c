/* HASH CRC-32:0xfb53472f */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_DOSABI_MALLOC_C
#define GUARD_LIBC_AUTO_DOSABI_MALLOC_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/malloc.h"

DECL_BEGIN

/* @EXCEPT: `realloc_in_place()' will return `NULL' if the reallocation isn't
 *           possible due to the requested memory above `MALLPTR' already being
 *           in use. However, an `E_BADALLOC' exception is thrown if insufficient
 *           memory (for internal control structures) is available to complete
 *           the operation */
INTERN ATTR_SECTION(".text.crt.dos.heap.helpers") ATTR_MALL_DEFAULT_ALIGNED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBDCALL libd_realloc_in_place)(void *__restrict mallptr,
                                            size_t n_bytes) {
	return libc_realloc_in_place(mallptr, n_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.malloc") ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(1) ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBDCALL libd_memalign)(size_t alignment,
                                    size_t n_bytes) {
	return libc_memalign(alignment, n_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.rare_helpers") ATTR_MALLOC ATTR_MALL_PAGEALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBDCALL libd_pvalloc)(size_t n_bytes) {
	return libc_pvalloc(n_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.rare_helpers") ATTR_MALL_PAGEALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBDCALL libd_valloc)(size_t n_bytes) {
	return libc_valloc(n_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.rare_helpers") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_posix_memalign)(void **__restrict pp,
                                          size_t alignment,
                                          size_t n_bytes) {
	return libc_posix_memalign(pp, alignment, n_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.utility") int
NOTHROW_NCX(LIBDCALL libd_malloc_trim)(size_t pad) {
	return libc_malloc_trim(pad);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.helpers") ATTR_PURE WUNUSED size_t
NOTHROW_NCX(LIBDCALL libd_malloc_usable_size)(void *__restrict mallptr) {
	return libc_malloc_usable_size(mallptr);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.utility") int
NOTHROW_NCX(LIBDCALL libd_mallopt)(int parameter_number,
                                   int parameter_value) {
	return libc_mallopt(parameter_number, parameter_value);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.rare_helpers") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_memdup)(void const *__restrict ptr,
                                  size_t n_bytes) {
	return libc_memdup(ptr, n_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.rare_helpers") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_memcdup)(void const *__restrict ptr,
                                   int needle,
                                   size_t n_bytes) {
	return libc_memcdup(ptr, needle, n_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBDCALL libd_reallocarray)(void *ptr,
                                        size_t elem_count,
                                        size_t elem_size) {
	return libc_reallocarray(ptr, elem_count, elem_size);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBDCALL libd_recalloc)(void *mallptr,
                                    size_t num_bytes) {
	return libc_recalloc(mallptr, num_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBDCALL libd_recallocv)(void *mallptr,
                                     size_t elem_count,
                                     size_t elem_size) {
	return libc_recallocv(mallptr, elem_count, elem_size);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$realloc_in_place, libd_realloc_in_place);
DEFINE_PUBLIC_ALIAS(DOS$aligned_alloc, libd_memalign);
DEFINE_PUBLIC_ALIAS(DOS$memalign, libd_memalign);
DEFINE_PUBLIC_ALIAS(DOS$pvalloc, libd_pvalloc);
DEFINE_PUBLIC_ALIAS(DOS$valloc, libd_valloc);
DEFINE_PUBLIC_ALIAS(DOS$posix_memalign, libd_posix_memalign);
DEFINE_PUBLIC_ALIAS(DOS$malloc_trim, libd_malloc_trim);
DEFINE_PUBLIC_ALIAS(DOS$_msize, libd_malloc_usable_size);
DEFINE_PUBLIC_ALIAS(DOS$malloc_usable_size, libd_malloc_usable_size);
DEFINE_PUBLIC_ALIAS(DOS$mallopt, libd_mallopt);
DEFINE_PUBLIC_ALIAS(DOS$__memdup, libd_memdup);
DEFINE_PUBLIC_ALIAS(DOS$memdup, libd_memdup);
DEFINE_PUBLIC_ALIAS(DOS$__memcdup, libd_memcdup);
DEFINE_PUBLIC_ALIAS(DOS$memcdup, libd_memcdup);
DEFINE_PUBLIC_ALIAS(DOS$reallocarray, libd_reallocarray);
DEFINE_PUBLIC_ALIAS(DOS$recalloc, libd_recalloc);
DEFINE_PUBLIC_ALIAS(DOS$_recalloc, libd_recallocv);
DEFINE_PUBLIC_ALIAS(DOS$recallocv, libd_recallocv);

#endif /* !GUARD_LIBC_AUTO_DOSABI_MALLOC_C */
