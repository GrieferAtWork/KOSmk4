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
#ifndef GUARD_LIBKERNEL32_WINNLS_C
#define GUARD_LIBKERNEL32_WINNLS_C 1

#include "api.h"

#include <nt/winnls.h>

DECL_BEGIN

DEFINE_PUBLIC_ALIAS(IsValidCodePage, libk32_IsValidCodePage);
DEFINE_PUBLIC_ALIAS(GetACP, libk32_GetACP);
DEFINE_PUBLIC_ALIAS(GetOEMCP, libk32_GetOEMCP);
DEFINE_PUBLIC_ALIAS(IsDBCSLeadByte, libk32_IsDBCSLeadByte);
DEFINE_PUBLIC_ALIAS(IsDBCSLeadByteEx, libk32_IsDBCSLeadByteEx);

INTERN WINBOOL WINAPI libk32_IsValidCodePage(UINT CodePage) {
	COMPILER_IMPURE();
	(void)CodePage;
	return TRUE;
}

INTERN UINT WINAPI libk32_GetACP(void) {
	COMPILER_IMPURE();
	return 0;
}

INTERN UINT WINAPI libk32_GetOEMCP(void) {
	COMPILER_IMPURE();
	return 0;
}

INTERN WINBOOL WINAPI libk32_IsDBCSLeadByte(BYTE TestChar) {
	COMPILER_IMPURE();
	return TestChar >= 0x80;
}

INTERN WINBOOL WINAPI libk32_IsDBCSLeadByteEx(UINT CodePage, BYTE TestChar) {
	(void)CodePage;
	COMPILER_IMPURE();
	return TestChar >= 0x80;
}

DECL_END

#endif /* !GUARD_LIBKERNEL32_WINNLS_C */
