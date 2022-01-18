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
#define _GNU_SOURCE 1

#include "api.h"
/**/

#include <kos/types.h>
#include <nt/processthreadsapi.h>

#include <errno.h>
#include <pthread.h>
#include <sched.h>
#include <syslog.h>
#include <unistd.h>

DECL_BEGIN

/************************************************************************/
/* SIMPLE PROC/THREAD CONTROL                                           */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(ExitThread, libk32_ExitThread);
DEFINE_PUBLIC_ALIAS(ExitProcess, libk32_ExitProcess);
DEFINE_PUBLIC_ALIAS(SwitchToThread, libk32_SwitchToThread);
DEFINE_PUBLIC_ALIAS(GetCurrentProcessorNumber, libk32_GetCurrentProcessorNumber);
DEFINE_PUBLIC_ALIAS(ProcessIdToSessionId, libk32_ProcessIdToSessionId);
DEFINE_PUBLIC_ALIAS(GetCurrentProcessId, libk32_GetCurrentProcessId);
DEFINE_PUBLIC_ALIAS(GetCurrentThreadId, libk32_GetCurrentThreadId);
DEFINE_PUBLIC_ALIAS(IsProcessorFeaturePresent, libk32_IsProcessorFeaturePresent);
DEFINE_PUBLIC_ALIAS(FlushProcessWriteBuffers, libk32_FlushProcessWriteBuffers);

INTERN DECLSPEC_NORETURN VOID WINAPI
libk32_ExitThread(DWORD dwExitCode) {
	/* TODO: This sets the pthread return value, but we want to set the system thread exit code!
	 * libc: >> pthread_exit_thread(&current, dwExitCode); */
	pthread_exit((void *)(uintptr_t)dwExitCode);
}

INTERN DECLSPEC_NORETURN VOID WINAPI
libk32_ExitProcess(UINT uExitCode) {
	_exit((int)uExitCode);
}

INTERN WINBOOL WINAPI
libk32_SwitchToThread(VOID) {
	pthread_yield();
	return TRUE;
}

INTERN DWORD WINAPI
libk32_GetCurrentProcessorNumber(VOID) {
	return sched_getcpu();
}

INTERN WINBOOL WINAPI
libk32_ProcessIdToSessionId(DWORD dwProcessId, DWORD *pSessionId) {
	pid_t sid = getsid((pid_t)dwProcessId);
	if (sid == -1)
		return FALSE;
	*pSessionId = sid;
	return TRUE;
}

INTERN DWORD WINAPI
libk32_GetCurrentProcessId(VOID) {
	return getpid();
}

INTERN DWORD WINAPI
libk32_GetCurrentThreadId(VOID) {
	return gettid();
}

INTERN WINBOOL WINAPI
libk32_IsProcessorFeaturePresent(DWORD ProcessorFeature) {
	syslog(LOG_WARNING, "[k32] Not implemented: IsProcessorFeaturePresent(%I32u)\n",
	       ProcessorFeature);
	return FALSE;
}

INTERN VOID WINAPI
libk32_FlushProcessWriteBuffers(VOID) {
	syslog(LOG_WARNING, "[k32] Not implemented: FlushProcessWriteBuffers()\n");
}



/************************************************************************/
/* TLS                                                                  */
/************************************************************************/
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
