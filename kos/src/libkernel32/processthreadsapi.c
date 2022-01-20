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
#define _KOS_KERNEL_SOURCE 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"
/**/

#include <asm/intrin.h>
#include <kos/ioctl/task.h>
#include <kos/syscalls.h>
#include <kos/types.h>
#include <nt/handleapi.h>
#include <nt/processthreadsapi.h>
#include <sys/ioctl.h>
#include <sys/wait.h>

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <syslog.h>
#include <unistd.h>

DECL_BEGIN

/************************************************************************/
/* INTER-PROCESS CONTROL                                                */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(OpenProcess, libk32_OpenProcess);
DEFINE_PUBLIC_ALIAS(GetExitCodeProcess, libk32_GetExitCodeProcess);
DEFINE_PUBLIC_ALIAS(GetExitCodeThread, libk32_GetExitCodeThread);
DEFINE_PUBLIC_ALIAS(OpenThread, libk32_OpenThread);
DEFINE_PUBLIC_ALIAS(GetProcessId, libk32_GetProcessId);
DEFINE_PUBLIC_ALIAS(GetThreadId, libk32_GetThreadId);
DEFINE_PUBLIC_ALIAS(GetProcessHandleCount, libk32_GetProcessHandleCount);
DEFINE_PUBLIC_ALIAS(GetProcessIdOfThread, libk32_GetProcessIdOfThread);
DEFINE_PUBLIC_ALIAS(GetCurrentProcess, libk32_GetCurrentProcess);
DEFINE_PUBLIC_ALIAS(GetCurrentThread, libk32_GetCurrentThread);

INTERN HANDLE WINAPI
libk32_OpenProcess(DWORD dwDesiredAccess, WINBOOL bInheritHandle, DWORD dwProcessId) {
	fd_t result;
	(void)dwDesiredAccess;
	result = sys_pidfd_open(dwProcessId, 0);
	if (E_ISERR(result)) {
		errno = -result;
		return NULL;
	}
	if (bInheritHandle) {
		if (fcntl(result, F_SETFL, 0) != 0) {
			close(result);
			return NULL;
		}
	}
	return NTHANDLE_FROMFD(result);
}

INTERN WINBOOL WINAPI
libk32_GetExitCodeProcess(HANDLE hProcess, LPDWORD lpExitCode) {
	union wait w;
	if (!NTHANDLE_ISFD(hProcess)) {
		errno = EBADF;
		return FALSE;
	}
	if (ioctl(NTHANDLE_ASFD(hProcess), TASK_IOC_EXITCODE, &w) < 0) {
		if (errno == EINVAL) {
			*lpExitCode = STILL_ACTIVE;
			return TRUE;
		}
		return FALSE;
	}
	if (WIFEXITED(w)) {
		*lpExitCode = WEXITSTATUS(w);
		return TRUE;
	}
	/* Something else (e.h. a signal or coredump) */
	*lpExitCode = (DWORD)-1;
	return TRUE;
}

DEFINE_INTERN_ALIAS(libk32_GetExitCodeThread, libk32_GetExitCodeProcess);
INTERN HANDLE WINAPI
libk32_OpenThread(DWORD dwDesiredAccess, WINBOOL bInheritHandle, DWORD dwThreadId) {
	fd_t result;
	char filename[64];
	(void)dwDesiredAccess;
	/* NOTE: For linux compat, `sys_pidfd_open()' can't be used to open thread
	 *       handles! - Instead, those can be opened via `open("/proc/[tid]")' */
	sprintf(filename, "/proc/%d", (pid_t)dwThreadId);
	result = open(filename,
	              bInheritHandle ? (O_RDWR | O_DIRECTORY)
	                             : (O_RDWR | O_DIRECTORY | O_CLOEXEC));
	if (result == -1)
		return NULL;
	return NTHANDLE_FROMFD(result);
}

DEFINE_INTERN_ALIAS(libk32_GetProcessIdOfThread, libk32_GetProcessId);
INTERN DWORD WINAPI
libk32_GetProcessId(HANDLE hProcess) {
	pid_t result;
	if (!NTHANDLE_ISFD(hProcess)) {
		errno = EBADF;
		return 0;
	}
	if (ioctl(NTHANDLE_ASFD(hProcess), TASK_IOC_GETPID, &result) < 0)
		return 0;
	return result;
}

INTERN DWORD WINAPI
libk32_GetThreadId(HANDLE hThread) {
	pid_t result;
	if (!NTHANDLE_ISFD(hThread)) {
		errno = EBADF;
		return 0;
	}
	if (ioctl(NTHANDLE_ASFD(hThread), TASK_IOC_GETTID, &result) < 0)
		return 0;
	return result;
}

INTERN WINBOOL WINAPI
libk32_GetProcessHandleCount(HANDLE hProcess, PDWORD pdwHandleCount) {
	/* Count the # of files in "/proc/pid/fd" */
	char pathname[64];
	DWORD pid = libk32_GetProcessId(hProcess);
	DIR *fddir;
	size_t count;
	if (pid == 0)
		return FALSE;
	sprintf(pathname, "/proc/%d/fd", (pid_t)pid);
	fddir = opendir(pathname);
	if (!fddir)
		return FALSE;
	for (count = 0; readdir(fddir) != NULL; ++count)
		;
	closedir(fddir);
	*pdwHandleCount = (DWORD)count;
	return TRUE;
}

INTERN HANDLE WINAPI libk32_GetCurrentProcess(VOID) {
	return NTHANDLE_FROMFD(AT_THIS_PROCESS);
}

INTERN HANDLE WINAPI libk32_GetCurrentThread(VOID) {
	return NTHANDLE_FROMFD(AT_THIS_TASK);
}



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
DEFINE_PUBLIC_ALIAS(FlushInstructionCache, libk32_FlushInstructionCache);

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

INTERN WINBOOL WINAPI
libk32_FlushInstructionCache(HANDLE hProcess, LPCVOID lpBaseAddress, SIZE_T dwSize) {
	if (hProcess != NTHANDLE_FROMFD(AT_THIS_PROCESS)) {
		errno = EACCES;
		return FALSE;
	}
	(void)lpBaseAddress;
	(void)dwSize;
	__flush_instruction_cache();
	return TRUE;
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
