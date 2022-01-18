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
#ifndef GUARD_LIBKERNEL32_STRINGAPISET_C
#define GUARD_LIBKERNEL32_STRINGAPISET_C 1

#include "api.h"

#include <kos/types.h>
#include <nt/stringapiset.h>

#include <syslog.h>

DECL_BEGIN

DEFINE_PUBLIC_ALIAS(MultiByteToWideChar, libk32_MultiByteToWideChar);
DEFINE_PUBLIC_ALIAS(WideCharToMultiByte, libk32_WideCharToMultiByte);

INTERN int WINAPI
libk32_MultiByteToWideChar(UINT CodePage, DWORD dwFlags,
                           LPCCH lpMultiByteStr, int cbMultiByte,
                           LPWSTR lpWideCharStr, int cchWideChar) {
	syslog(LOG_WARNING, "NotImplemented: MultiByteToWideChar(%u, %#x, %q, %d, %p, %d)\n",
	       CodePage, dwFlags, lpMultiByteStr, cbMultiByte, lpWideCharStr, cchWideChar);
	/* TODO */
	return 0;
}

INTERN int WINAPI
libk32_WideCharToMultiByte(UINT CodePage, DWORD dwFlags,
                           LPCWCH lpWideCharStr, int cchWideChar,
                           LPSTR lpMultiByteStr, int cbMultiByte,
                           LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar) {
	syslog(LOG_WARNING, "NotImplemented: WideCharToMultiByte(%u, %#x, %I16q, %d, %p, %d, %p, %p)\n",
	       CodePage, dwFlags, lpWideCharStr, cchWideChar,
	       lpMultiByteStr, cbMultiByte, lpDefaultChar, lpUsedDefaultChar);
	/* TODO */
	return 0;
}

DECL_END

#endif /* !GUARD_LIBKERNEL32_STRINGAPISET_C */
