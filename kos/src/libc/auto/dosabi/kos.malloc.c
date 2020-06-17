/* HASH CRC-32:0x212a0867 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_KOS_MALLOC_C
#define GUARD_LIBC_AUTO_DOSABI_KOS_MALLOC_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/kos.malloc.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.except.heap.malloc") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1)) void *
(LIBDCALL libd_Malloc)(size_t num_bytes) THROWS(E_BADALLOC) {
	return libc_Malloc(num_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.except.heap.malloc") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *
(LIBDCALL libd_Calloc)(size_t count,
                       size_t num_bytes) THROWS(E_BADALLOC) {
	return libc_Calloc(count, num_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.except.heap.malloc") ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((2)) void *
(LIBDCALL libd_Realloc)(void *mallptr,
                        size_t num_bytes) THROWS(E_BADALLOC) {
	return libc_Realloc(mallptr, num_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.except.heap.malloc") ATTR_MALLOC ATTR_RETNONNULL WUNUSED ATTR_ALLOC_ALIGN(1) ATTR_ALLOC_SIZE((2)) void *
(LIBDCALL libd_Memalign)(size_t alignment,
                         size_t num_bytes) THROWS(E_BADALLOC) {
	return libc_Memalign(alignment, num_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.except.heap.rare_helpers") ATTR_MALLOC ATTR_RETNONNULL WUNUSED __ATTR_MALL_PAGEALIGNED ATTR_ALLOC_SIZE((1)) void *
(LIBDCALL libd_PValloc)(size_t num_bytes) THROWS(E_BADALLOC) {
	return libc_PValloc(num_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.except.heap.rare_helpers") ATTR_MALLOC ATTR_RETNONNULL WUNUSED __ATTR_MALL_PAGEALIGNED ATTR_ALLOC_SIZE((1)) void *
(LIBDCALL libd_Valloc)(size_t num_bytes) THROWS(E_BADALLOC) {
	return libc_Valloc(num_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.except.heap.rare_helpers") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((2)) NONNULL((1)) void *
(LIBDCALL libd_Memdup)(void const *__restrict ptr,
                       size_t num_bytes) THROWS(E_BADALLOC) {
	return libc_Memdup(ptr, num_bytes);
}
/* @throws: E_BADALLOC: ... */
INTERN ATTR_SECTION(".text.crt.dos.except.heap.rare_helpers") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
(LIBDCALL libd_Memcdup)(void const *__restrict ptr,
                        int needle,
                        size_t num_bytes) THROWS(E_BADALLOC) {
	return libc_Memcdup(ptr, needle, num_bytes);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$Malloc, libd_Malloc);
DEFINE_PUBLIC_ALIAS(DOS$Calloc, libd_Calloc);
DEFINE_PUBLIC_ALIAS(DOS$Realloc, libd_Realloc);
DEFINE_PUBLIC_ALIAS(DOS$Memalign, libd_Memalign);
DEFINE_PUBLIC_ALIAS(DOS$PValloc, libd_PValloc);
DEFINE_PUBLIC_ALIAS(DOS$Valloc, libd_Valloc);
DEFINE_PUBLIC_ALIAS(DOS$Memdup, libd_Memdup);
DEFINE_PUBLIC_ALIAS(DOS$Memcdup, libd_Memcdup);

#endif /* !GUARD_LIBC_AUTO_DOSABI_KOS_MALLOC_C */
