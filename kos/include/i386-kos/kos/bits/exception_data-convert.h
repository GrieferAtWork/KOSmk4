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
#ifndef _I386_KOS_KOS_BITS_EXCEPTION_DATA_CONVERT_H
#define _I386_KOS_KOS_BITS_EXCEPTION_DATA_CONVERT_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <kos/bits/exception_data32.h>
#include <kos/bits/exception_data64.h>

__SYSDECL_BEGIN

/* Convert between 32-bit and 64-bit siginfo_t structures */
#ifdef __CC__

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(exception_data32_to_exception_data64)(struct exception_data64 *__restrict dst,
                                                    struct exception_data32 const *__restrict src) {
	unsigned int i;
	dst->e_class    = (error_class64_t)src->e_class;
	dst->e_subclass = (error_subclass64_t)src->e_subclass;
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
		dst->e_pointers[i] = (__UINT64_TYPE__)src->e_pointers[i];
}

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(exception_data64_to_exception_data32)(struct exception_data32 *__restrict dst,
                                                    struct exception_data64 const *__restrict src) {
	unsigned int i;
	dst->e_class    = (error_class32_t)src->e_class;
	dst->e_subclass = (error_subclass32_t)src->e_subclass;
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
		dst->e_pointers[i] = (__UINT32_TYPE__)src->e_pointers[i];
}

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_KOS_BITS_EXCEPTION_DATA_CONVERT_H */
