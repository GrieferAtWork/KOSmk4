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
#ifndef GUARD_LIBKERNEL32_PROCESSTHREADSAPI_C
#define GUARD_LIBKERNEL32_PROCESSTHREADSAPI_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <kos/types.h>
#include <nt/processthreadsapi.h>

#include <errno.h>
#include <pthread.h>

DECL_BEGIN

DEFINE_PUBLIC_ALIAS(TlsAlloc, libk32_TlsAlloc);
DEFINE_PUBLIC_ALIAS(TlsGetValue, libk32_TlsGetValue);
DEFINE_PUBLIC_ALIAS(TlsSetValue, libk32_TlsSetValue);
DEFINE_PUBLIC_ALIAS(TlsFree, libk32_TlsFree);

INTERN DWORD WINAPI libk32_TlsAlloc(VOID) {
	pthread_key_t key;
	errno_t error = pthread_key_create(&key, NULL);
	if (error != EOK) {
		errno = error;
		key   = TLS_OUT_OF_INDEXES;
	}
	return key;
}

INTERN LPVOID WINAPI
libk32_TlsGetValue(DWORD dwTlsIndex) {
	return pthread_getspecific(dwTlsIndex);
}

INTERN WINBOOL WINAPI
libk32_TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue) {
	errno_t error;
	error = pthread_setspecific(dwTlsIndex, lpTlsValue);
	if (error == EOK)
		return TRUE;
	errno = error;
	return FALSE;
}

INTERN WINBOOL WINAPI libk32_TlsFree(DWORD dwTlsIndex) {
	errno_t error;
	error = pthread_key_delete(dwTlsIndex);
	if (error == EOK)
		return TRUE;
	errno = error;
	return FALSE;
}

DECL_END

#endif /* !GUARD_LIBKERNEL32_PROCESSTHREADSAPI_C */
