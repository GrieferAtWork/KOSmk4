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
#ifndef _I386_KOS_KOS_BITS_EXCEPTION_DATA_CONVERT_H
#define _I386_KOS_KOS_BITS_EXCEPTION_DATA_CONVERT_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <kos/bits/exception_data32.h>
#include <kos/bits/exception_data64.h>

#include <libc/string.h>

#ifdef __CC__
__DECL_BEGIN

/* Convert between 32-bit and 64-bit siginfo_t structures */
#define exception_data32_to_exception_data32(self, result)                     \
	__libc_memcpy(__COMPILER_REQTYPE(struct __exception_data32 *, result),     \
	              __COMPILER_REQTYPE(struct __exception_data32 const *, self), \
	              sizeof(struct __exception_data32))
#define exception_data64_to_exception_data64(self, result)                     \
	__libc_memcpy(__COMPILER_REQTYPE(struct __exception_data64 *, result),     \
	              __COMPILER_REQTYPE(struct __exception_data64 const *, self), \
	              sizeof(struct __exception_data64))

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(exception_data32_to_exception_data64)(struct __exception_data32 const *__restrict __self,
                                                    struct __exception_data64 *__restrict __result) {
	unsigned int i;
	__result->e_class    = (__except_class64_t)__self->e_class;
	__result->e_subclass = (__except_subclass64_t)__self->e_subclass;
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
		__result->e_args.e_pointers[i] = (__ULONG64_TYPE__)__self->e_args.e_pointers[i];
	__result->e_faultaddr = (__HYBRID_PTR64(void const))__self->e_faultaddr;
}

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(exception_data64_to_exception_data32)(struct __exception_data64 const *__restrict __self,
                                                    struct __exception_data32 *__restrict __result) {
	unsigned int i;
	__result->e_class    = (__except_class32_t)__self->e_class;
	__result->e_subclass = (__except_subclass32_t)__self->e_subclass;
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
		__result->e_args.e_pointers[i] = (__ULONG32_TYPE__)__self->e_args.e_pointers[i];
	__result->e_faultaddr = (__HYBRID_PTR32(void const))__self->e_faultaddr;
}

#ifdef __x86_64__
#define exception_data64_to_exception_data exception_data64_to_exception_data64
#define exception_data32_to_exception_data exception_data32_to_exception_data64
#define exception_data_to_exception_data32 exception_data64_to_exception_data32
#define exception_data_to_exception_data64 exception_data64_to_exception_data64
#else /* __x86_64__ */
#define exception_data64_to_exception_data exception_data64_to_exception_data32
#define exception_data32_to_exception_data exception_data32_to_exception_data32
#define exception_data_to_exception_data32 exception_data32_to_exception_data32
#define exception_data_to_exception_data64 exception_data32_to_exception_data64
#endif /* !__x86_64__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_BITS_EXCEPTION_DATA_CONVERT_H */
