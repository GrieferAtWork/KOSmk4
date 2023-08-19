/* HASH CRC-32:0x75e8f8fd */
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
#ifndef __local_imaxdiv_defined
#define __local_imaxdiv_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#ifndef ____imaxdiv_struct_defined
#define ____imaxdiv_struct_defined
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("quot")
#pragma push_macro("rem")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef quot
#undef rem
struct __imaxdiv_struct {
	__INTMAX_TYPE__ quot; /* Quotient. */
	__INTMAX_TYPE__ rem;  /* Remainder. */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("rem")
#pragma pop_macro("quot")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !____imaxdiv_struct_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(imaxdiv) __ATTR_CONST struct __imaxdiv_struct
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(imaxdiv))(__INTMAX_TYPE__ __numer, __INTMAX_TYPE__ __denom) {
	struct __imaxdiv_struct __result;
	__result.quot = __numer / __denom;
	__result.rem  = __numer % __denom;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_imaxdiv_defined
#define __local___localdep_imaxdiv_defined
#define __localdep_imaxdiv __LIBC_LOCAL_NAME(imaxdiv)
#endif /* !__local___localdep_imaxdiv_defined */
#endif /* !__local_imaxdiv_defined */
