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
#ifndef GUARD_LIBKERNEL32_PROCESSTHREADSAPI_C
#define GUARD_LIBKERNEL32_PROCESSTHREADSAPI_C 1
#define _KOS_KERNEL_SOURCE 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define _LIBC_SOURCE 1 /* For "typedef struct pthread *pthread_t" */

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <asm/intrin.h>
#include <kos/ioctl/pidfd.h>
#include <kos/rpc.h>
#include <kos/syscalls.h>
#include <kos/types.h>
#include <nt/__stdinc.h>
#include <nt/handleapi.h>
#include <nt/processthreadsapi.h>
#include <nt/types.h>
#include <sys/ioctl.h>
#include <sys/syslog.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <assert.h>
#include <atomic.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <malloc.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

/************************************************************************/
/* INTER-PROCESS CONTROL                                                */
/************************************************************************/
INTERN WINBOOL WINAPI
libk32_TerminateProcess(HANDLE hProcess, UINT uExitCode) {
	errno_t error;
	TRACE("TerminateProcess(%p, %x)", hProcess, uExitCode);
	(void)uExitCode;
	if (!NTHANDLE_ISFD(hProcess)) {
		errno = EBADF;
		return FALSE;
	}
	error = sys_pidfd_send_signal(NTHANDLE_ASFD(hProcess), SIGKILL, NULL, 0);
	if (E_ISOK(error))
		return TRUE;
	errno = -error;
	return FALSE;
}

DEFINE_INTERN_ALIAS(libk32_TerminateThread, libk32_TerminateProcess);

INTERN HANDLE WINAPI
libk32_OpenProcess(DWORD dwDesiredAccess, WINBOOL bInheritHandle, DWORD dwProcessId) {
	fd_t result;
	TRACE("OpenProcess(%#x, %u, %#x)", dwDesiredAccess, bInheritHandle, dwProcessId);
	(void)dwDesiredAccess;
	result = sys_pidfd_open(dwProcessId, 0);
	if (E_ISERR(result)) {
		errno = -result;
		return NULL;
	}
	if (bInheritHandle) {
		if (fcntl(result, F_SETFL, 0) != 0) {
			(void)sys_close(result);
			return NULL;
		}
	}
	return NTHANDLE_FROMFD(result);
}

INTERN WINBOOL WINAPI
libk32_GetExitCodeProcess(HANDLE hProcess, LPDWORD lpExitCode) {
	union wait w;
	TRACE("GetExitCodeProcess(%p, %p)", hProcess, lpExitCode);
	if (!NTHANDLE_ISFD(hProcess)) {
		errno = EBADF;
		return FALSE;
	}
	if (ioctl(NTHANDLE_ASFD(hProcess), PIDFD_IOC_EXITCODE, &w) < 0) {
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
	TRACE("OpenThread(%#x, %u, %#x)", dwDesiredAccess, bInheritHandle, dwThreadId);
	(void)dwDesiredAccess;
	result = sys_pidfd_open(dwThreadId, 0);
	if (E_ISERR(result)) {
		errno = -result;
		return NULL;
	}
	if (bInheritHandle) {
		if (fcntl(result, F_SETFL, 0) != 0) {
			(void)sys_close(result);
			return NULL;
		}
	}
	return NTHANDLE_FROMFD(result);
}

INTERN DWORD WINAPI
libk32_GetProcessId(HANDLE hProcess) {
	pid_t result;
	TRACE("GetProcessId(%p)", hProcess);
	if (!NTHANDLE_ISFD(hProcess)) {
		errno = EBADF;
		return 0;
	}
	if (ioctl(NTHANDLE_ASFD(hProcess), PIDFD_IOC_GETPID, &result) < 0)
		return 0;
	return result;
}

DEFINE_INTERN_ALIAS(libk32_GetProcessIdOfThread, libk32_GetProcessId);

INTERN DWORD WINAPI
libk32_GetThreadId(HANDLE hThread) {
	pid_t result;
	TRACE("GetThreadId(%p)", hThread);
	if (!NTHANDLE_ISFD(hThread)) {
		errno = EBADF;
		return 0;
	}
	if (ioctl(NTHANDLE_ASFD(hThread), PIDFD_IOC_GETTID, &result) < 0)
		return 0;
	return result;
}

INTERN WINBOOL WINAPI
libk32_GetProcessHandleCount(HANDLE hProcess, PDWORD pdwHandleCount) {
	/* Count the # of files in "/proc/pid/fd" */
	char pathname[lengthof("/proc/" PRIMAXd "/fd")];
	DWORD pid = libk32_GetProcessId(hProcess);
	DIR *fddir;
	size_t count;
	TRACE("GetProcessHandleCount(%p, %p)", hProcess, pdwHandleCount);
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
	TRACE("GetCurrentProcess()");
	return NTHANDLE_FROMFD(AT_FDPROC);
}

INTERN HANDLE WINAPI libk32_GetCurrentThread(VOID) {
	TRACE("GetCurrentThread()");
	return NTHANDLE_FROMFD(AT_FDTHRD);
}

DEFINE_PUBLIC_ALIAS(TerminateProcess, libk32_TerminateProcess);
DEFINE_PUBLIC_ALIAS(TerminateThread, libk32_TerminateThread);
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
/************************************************************************/




/************************************************************************/
/* SIMPLE PROC/THREAD CONTROL                                           */
/************************************************************************/
struct k32_thread_start_data {
	LPTHREAD_START_ROUTINE lpStartAddress;
	LPVOID                 lpParameter;
};

PRIVATE void *LIBCCALL
k32_thread_start_routine(void *arg) {
	struct k32_thread_start_data info;
	memcpy(&info, arg, sizeof(struct k32_thread_start_data));
	free(arg);
	return (void *)(uintptr_t)(*info.lpStartAddress)(info.lpParameter);
}

INTERN HANDLE WINAPI
libk32_CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize,
                    LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter,
                    DWORD dwCreationFlags, LPDWORD lpThreadId) {
	HANDLE result;
	pthread_t thread;
	pthread_attr_t attr;
	errno_t error;
	struct k32_thread_start_data *cookie;
	TRACE("CreateThread(%p, %#Ix, %p, %p, %#x, %p)",
	      lpThreadAttributes, dwStackSize, lpStartAddress,
	      lpParameter, dwCreationFlags, lpThreadId);
	(void)lpThreadAttributes;
	error = pthread_attr_init(&attr);
	if (error != EOK)
		goto seterr;
	cookie = (struct k32_thread_start_data *)malloc(sizeof(struct k32_thread_start_data));
	if (!cookie) {
		(void)pthread_attr_destroy(&attr);
		goto err;
	}
	cookie->lpStartAddress = lpStartAddress;
	cookie->lpParameter    = lpParameter;

	/* Have libc automatically pre-allocate a pidfd descriptor here! */
	error = pthread_attr_setpidfdallocated_np(&attr, 1);
	if (error != EOK)
		goto seterr_attr_cookie;

	if (dwCreationFlags & CREATE_SUSPENDED) {
		error = pthread_attr_setcreatesuspend_np(&attr);
		if (error != EOK)
			goto seterr_attr_cookie;
	}

	/* Use a custom stack size (if given) */
	if (dwStackSize != 0) {
		error = pthread_attr_setstacksize(&attr, dwStackSize);
		if (error != EOK)
			goto seterr_attr_cookie;
	}

	/* Actually create the new thread. */
	error = pthread_create(&thread, &attr, &k32_thread_start_routine, cookie);
	(void)pthread_attr_destroy(&attr);
	if (error != EOK)
		goto seterr;

	/* Load the thread's TID for use as its NT "ThreadId" field. */
	if (lpThreadId)
		*lpThreadId = pthread_gettid_np(thread);

	/* Steal the thread's PIDfd descriptor by clearing the flag
	 * that would case it to  close(2) its descriptor on  exit.
	 *
	 * Also  note that  the thread  can't get  destroyed until we
	 * call `pthread_detach(3)' below, so this is perfectly safe,
	 * with the only exception being  that the thread is  already
	 * running, and if it already called `pthread_getpidfd_np(3)'
	 * before we got  here, then  it would have  read its  actual
	 * thread file descriptor  (though since that  one is a  KOS-
	 * specific function, we can safely assume that anything that
	 * uses both that API and this one knows of this quirk). */
	assert(thread->pt_pidfd != -1);
	assert(thread->pt_flags & PTHREAD_FFREEPIDFD);
	result = NTHANDLE_FROMFD(thread->pt_pidfd);
	atomic_and(&thread->pt_flags, ~PTHREAD_FFREEPIDFD);

	/* Detach the pthread object. */
	(void)pthread_detach(thread);

	/* Return a OS-level handle for the thread. */
	return result;
seterr_attr_cookie:
	free(cookie);
	(void)pthread_attr_destroy(&attr);
seterr:
	errno = error;
err:
	return NULL;
}

INTERN DECLSPEC_NORETURN VOID WINAPI
libk32_ExitThread(DWORD dwExitCode) {
	TRACE("ExitThread(%#x)", dwExitCode);
	/* TODO: This sets the pthread return value, but we want to set the system thread exit code!
	 * libc: >> pthread_exit_thread(&current, dwExitCode); */
	pthread_exit((void *)(uintptr_t)dwExitCode);
}

INTERN DECLSPEC_NORETURN VOID WINAPI
libk32_ExitProcess(UINT uExitCode) {
	TRACE("ExitProcess(%#x)", uExitCode);
	_exit((int)uExitCode);
}

INTERN WINBOOL WINAPI
libk32_SwitchToThread(VOID) {
	TRACE("SwitchToThread()");
	pthread_yield();
	return TRUE;
}

INTERN DWORD WINAPI
libk32_GetCurrentProcessorNumber(VOID) {
	int result = sched_getcpu();
	TRACE("GetCurrentProcessorNumber(): %d", result);
	return result;
}

INTERN WINBOOL WINAPI
libk32_ProcessIdToSessionId(DWORD dwProcessId, DWORD *pSessionId) {
	pid_t sid;
	TRACE("ProcessIdToSessionId(%#x, %p)", dwProcessId, pSessionId);
	sid = getsid((pid_t)dwProcessId);
	if (sid == -1)
		return FALSE;
	*pSessionId = sid;
	return TRUE;
}

INTERN DWORD WINAPI
libk32_GetCurrentProcessId(VOID) {
	pid_t result = getpid();
	TRACE("GetCurrentProcessId(): %d", result);
	return result;
}

INTERN DWORD WINAPI
libk32_GetCurrentThreadId(VOID) {
	pid_t result = gettid();
	TRACE("GetCurrentThreadId(): %d", result);
	return result;
}

INTERN WINBOOL WINAPI
libk32_IsProcessorFeaturePresent(DWORD ProcessorFeature) {
	TRACE("IsProcessorFeaturePresent(%#x)", ProcessorFeature);
	syslog(LOG_WARNING, "[k32] NotImplemented: IsProcessorFeaturePresent(%I32u)\n",
	       ProcessorFeature);
	return FALSE;
}

INTERN VOID WINAPI
libk32_FlushProcessWriteBuffers(VOID) {
	TRACE("FlushProcessWriteBuffers()");
	syslog(LOG_WARNING, "[k32] NotImplemented: FlushProcessWriteBuffers()\n");
}

INTERN WINBOOL WINAPI
libk32_FlushInstructionCache(HANDLE hProcess, LPCVOID lpBaseAddress, SIZE_T dwSize) {
	TRACE("FlushInstructionCache(%p, %p, %#Ix)",
	      hProcess, lpBaseAddress, dwSize);
	if (hProcess != NTHANDLE_FROMFD(AT_FDPROC)) {
		errno = EACCES;
		return FALSE;
	}
	(void)lpBaseAddress;
	(void)dwSize;
	__flush_instruction_cache();
	return TRUE;
}

struct user_apc_data {
	PAPCFUNC  pfnAPC;
	ULONG_PTR dwData;
};

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
user_apc_callback(struct rpc_context *__restrict UNUSED(ctx), void *cookie) {
	struct user_apc_data dat;
	memcpy(&dat, cookie, sizeof(struct user_apc_data));
	free(cookie); /* FIXME: This is unsafe until we get a non-blocking free function! */
	(*dat.pfnAPC)(dat.dwData);
}

INTERN BOOL WINAPI
libk32_QueueUserAPC2(PAPCFUNC pfnAPC, HANDLE hThread,
                     ULONG_PTR dwData, QUEUE_USER_APC_FLAGS flFlags) {
	struct user_apc_data *cookie;
	pid_t tid;
	unsigned int mode;
	TRACE("QueueUserAPC2(%p, %p, %p, %#x)",
	      pfnAPC, hThread, dwData, flFlags);
	tid = libk32_GetThreadId(hThread);
	if (tid == 0)
		return 0;
	cookie = (struct user_apc_data *)malloc(sizeof(struct user_apc_data));
	if (!cookie)
		return 0;
	cookie->pfnAPC = pfnAPC;
	cookie->dwData = dwData;
	/* From what I understand, "special" user-APC functions are just async RPCs... */
	mode = RPC_SYNCMODE_CP | RPC_DOMAIN_THREAD | RPC_JOIN_WAITFOR;
	if (flFlags == QUEUE_USER_APC_FLAGS_SPECIAL_USER_APC)
		mode = RPC_SYNCMODE_ASYNC | RPC_DOMAIN_THREAD | RPC_JOIN_WAITFOR;
	if (rpc_exec(tid, mode, &user_apc_callback, cookie) != 0) {
		free(cookie);
		return 0;
	}
	return 1;
}

INTERN DWORD WINAPI
libk32_QueueUserAPC(PAPCFUNC pfnAPC, HANDLE hThread, ULONG_PTR dwData) {
	TRACE("QueueUserAPC(%p, %p, %p)",
	      pfnAPC, hThread, dwData);
	return libk32_QueueUserAPC2(pfnAPC, hThread, dwData, QUEUE_USER_APC_FLAGS_NONE);
}

INTERN DWORD WINAPI
libk32_SuspendThread(HANDLE hThread) {
	errno_t error;
	pthread_t thread;
	uint32_t old_suspend_count;
	TRACE("SuspendThread(%p)", hThread);
	if (!NTHANDLE_ISFD(hThread)) {
		errno = EBADF;
		goto err;
	}
	error = pthread_attachpidfd_np(NTHANDLE_ASFD(hThread), &thread);
	if (error != EOK)
		goto err_errno;
	error = pthread_suspend2_np(thread, &old_suspend_count);
	(void)pthread_detach(thread);
	if (error != EOK)
		goto err_errno;
	if unlikely(old_suspend_count == (uint32_t)-1) {
		(void)pthread_resume_np(thread);
		error = EOVERFLOW;
		goto err_errno;
	}
	return (DWORD)old_suspend_count;
err_errno:
	errno = error;
err:
	return (DWORD)-1;
}

INTERN DWORD WINAPI
libk32_ResumeThread(HANDLE hThread) {
	errno_t error;
	pthread_t thread;
	uint32_t old_suspend_count;
	TRACE("ResumeThread(%p)", hThread);
	if (!NTHANDLE_ISFD(hThread)) {
		errno = EBADF;
		goto err;
	}
	error = pthread_attachpidfd_np(NTHANDLE_ASFD(hThread), &thread);
	if (error != EOK)
		goto err_errno;
	error = pthread_resume2_np(thread, &old_suspend_count);
	(void)pthread_detach(thread);
	if (error != EOK)
		goto err_errno;
	if unlikely(old_suspend_count == (uint32_t)-1) {
		(void)pthread_suspend_np(thread);
		error = EOVERFLOW;
		goto err_errno;
	}
	return (DWORD)old_suspend_count;
err_errno:
	errno = error;
err:
	return (DWORD)-1;
}

INTERN WINBOOL WINAPI
libk32_GetThreadContext(HANDLE hThread, LPCONTEXT lpContext) {
	TRACE("GetThreadContext(%p, %p)", hThread, lpContext);
	syslog(LOG_WARNING, "[k32] NotImplemented: GetThreadContext(%p, %p)\n",
	       hThread, lpContext);
	errno = ENOTSUP;
	return FALSE;
}

INTERN WINBOOL WINAPI
libk32_SetThreadContext(HANDLE hThread, CONST CONTEXT *lpContext) {
	TRACE("SetThreadContext(%p, %p)", hThread, lpContext);
	syslog(LOG_WARNING, "[k32] NotImplemented: SetThreadContext(%p, %p)\n",
	       hThread, lpContext);
	errno = ENOTSUP;
	return FALSE;
}

DEFINE_PUBLIC_ALIAS(CreateThread, libk32_CreateThread);
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
DEFINE_PUBLIC_ALIAS(QueueUserAPC, libk32_QueueUserAPC);
DEFINE_PUBLIC_ALIAS(QueueUserAPC2, libk32_QueueUserAPC2);
DEFINE_PUBLIC_ALIAS(SuspendThread, libk32_SuspendThread);
DEFINE_PUBLIC_ALIAS(ResumeThread, libk32_ResumeThread);
DEFINE_PUBLIC_ALIAS(GetThreadContext, libk32_GetThreadContext);
DEFINE_PUBLIC_ALIAS(SetThreadContext, libk32_SetThreadContext);
/************************************************************************/










/************************************************************************/
/* TLS                                                                  */
/************************************************************************/
INTERN DWORD WINAPI
libk32_TlsAlloc(VOID) {
	pthread_key_t key;
	errno_t error;
	TRACE("TlsAlloc()");
	error = pthread_key_create(&key, NULL);
	if (error != EOK) {
		errno = error;
		key   = TLS_OUT_OF_INDEXES;
	}
	return key;
}

INTERN LPVOID WINAPI
libk32_TlsGetValue(DWORD dwTlsIndex) {
	TRACE("TlsGetValue(%#x)", dwTlsIndex);
	return pthread_getspecific(dwTlsIndex);
}

INTERN WINBOOL WINAPI
libk32_TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue) {
	errno_t error;
	TRACE("TlsSetValue(%#x)", dwTlsIndex);
	error = pthread_setspecific(dwTlsIndex, lpTlsValue);
	if (error == EOK)
		return TRUE;
	errno = error;
	return FALSE;
}

INTERN WINBOOL WINAPI
libk32_TlsFree(DWORD dwTlsIndex) {
	errno_t error;
	TRACE("TlsFree(%#x)", dwTlsIndex);
	error = pthread_key_delete(dwTlsIndex);
	if (error == EOK)
		return TRUE;
	errno = error;
	return FALSE;
}

DEFINE_PUBLIC_ALIAS(TlsAlloc, libk32_TlsAlloc);
DEFINE_PUBLIC_ALIAS(TlsGetValue, libk32_TlsGetValue);
DEFINE_PUBLIC_ALIAS(TlsSetValue, libk32_TlsSetValue);
DEFINE_PUBLIC_ALIAS(TlsFree, libk32_TlsFree);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_PROCESSTHREADSAPI_C */
