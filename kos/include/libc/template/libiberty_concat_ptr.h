/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __LOCAL_libiberty_concat_ptr
#include <__crt.h>
#ifndef __LOCAL_libiberty_concat_ptr
__DECL_BEGIN
#ifdef libiberty_concat_ptr
#define __LOCAL_libiberty_concat_ptr libiberty_concat_ptr
#elif defined(__CRT_HAVE_libiberty_concat_ptr)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,__FILE *,libiberty_concat_ptr)
#define libiberty_concat_ptr         libiberty_concat_ptr
#define __LOCAL_libiberty_concat_ptr libiberty_concat_ptr
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,__FILE *,__LOCAL_libiberty_concat_ptr,libiberty_concat_ptr)
#define __LOCAL_libiberty_concat_ptr __LOCAL_libiberty_concat_ptr
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
__DECL_END
#endif /* !__LOCAL_libiberty_concat_ptr */
#endif /* !__LOCAL_libiberty_concat_ptr */
