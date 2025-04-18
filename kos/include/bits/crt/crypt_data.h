/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!included_by <crypt.h>*/
#ifndef _BITS_CRT_CRYPT_DATA_H
#define _BITS_CRT_CRYPT_DATA_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("keysched")
#pragma push_macro("sb0")
#pragma push_macro("sb1")
#pragma push_macro("sb2")
#pragma push_macro("sb3")
#pragma push_macro("crypt_3_buf")
#pragma push_macro("current_salt")
#pragma push_macro("current_saltbits")
#pragma push_macro("direction")
#pragma push_macro("initialized")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef keysched
#undef sb0
#undef sb1
#undef sb2
#undef sb3
#undef crypt_3_buf
#undef current_salt
#undef current_saltbits
#undef direction
#undef initialized
struct crypt_data {
	char             keysched[16 * 8];
	char             sb0[32768];
	char             sb1[32768];
	char             sb2[32768];
	char             sb3[32768];
	/* end-of-aligment-critical-data */
	char             crypt_3_buf[14];
	char             current_salt[2];
	__LONGPTR_TYPE__ current_saltbits;
	__INT32_TYPE__   direction;
	__INT32_TYPE__   initialized;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("initialized")
#pragma pop_macro("direction")
#pragma pop_macro("current_saltbits")
#pragma pop_macro("current_salt")
#pragma pop_macro("crypt_3_buf")
#pragma pop_macro("sb3")
#pragma pop_macro("sb2")
#pragma pop_macro("sb1")
#pragma pop_macro("sb0")
#pragma pop_macro("keysched")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_CRYPT_DATA_H */
