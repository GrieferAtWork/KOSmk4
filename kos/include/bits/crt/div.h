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
#ifndef _BITS_CRT_DIV_H
#define _BITS_CRT_DIV_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#define __OFFSET_DIV_QUOT     0
#define __OFFSET_DIV_REM      __SIZEOF_INT__
#define __SIZEOF_DIV_STRUCT   (2 * __SIZEOF_INT__)
#define __OFFSET_LDIV_QUOT    0
#define __OFFSET_LDIV_REM     __SIZEOF_LONG__
#define __SIZEOF_LDIV_STRUCT  (2 * __SIZEOF_LONG__)
#ifdef __LONGLONG
#define __OFFSET_LLDIV_QUOT   0
#define __OFFSET_LLDIV_REM    __SIZEOF_LONG_LONG__
#define __SIZEOF_LLDIV_STRUCT (2 * __SIZEOF_LONG_LONG__)
#endif /* __LONGLONG */

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("quot")
#pragma push_macro("rem")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef quot
#undef rem
struct __div_struct {
	int quot;
	int rem;
};
struct __ldiv_struct {
	long quot;
	long rem;
};
#ifdef __LONGLONG
struct __lldiv_struct {
	__LONGLONG quot;
	__LONGLONG rem;
};
#endif /* __LONGLONG */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("rem")
#pragma pop_macro("quot")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */


__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DIV_H */
