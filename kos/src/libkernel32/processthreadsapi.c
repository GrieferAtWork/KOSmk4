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
#include <kos/rpc.h>
#include <kos/syscalls.h>
#include <kos/types.h>
#include <nt/handleapi.h>
#include <nt/processthreadsapi.h>
#include <sys/ioctl.h>
#include <sys/wait.h>

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
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

struct k32_thread_start_data {
	LPTHREAD_START_ROUTINE lpStartAddress;
	LPVOID                 lpParameter;
	DWORD                  dwCreationFlags;
};

PRIVATE void *LIBCCALL
k32_thread_start_routine(void *arg) {
	struct k32_thread_start_data info;
	memcpy(&info, arg, sizeof(struct k32_thread_start_data));
	free(arg);
	if (info.dwCreationFlags & CREATE_SUSPENDED) {
		/* XXX: Kernel-side of this is not fully implemented
		 * -> Once it is, there should be ioctls to (recursively) suspend/resume threads */
		pthread_kill(pthread_self(), SIGSTOP);
	}
	return (void *)(uintptr_t)(*info.lpStartAddress)(info.lpParameter);
}

INTERN HANDLE WINAPI
libk32_CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize,
                    LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter,
                    DWORD dwCreationFlags, LPDWORD lpThreadId) {
	HANDLE result;
	pid_t tid;
	pthread_t thread;
	pthread_attr_t attr;
	errno_t error;
	struct k32_thread_start_data *cookie;
	(void)lpThreadAttributes;
	error = pthread_attr_init(&attr);
	if (error != EOK)
		goto seterr;
	cookie = (struct k32_thread_start_data *)malloc(sizeof(struct k32_thread_start_data));
	if (!cookie) {
		pthread_attr_destroy(&attr);
		goto err;
	}
	cookie->lpStartAddress  = lpStartAddress;
	cookie->lpParameter     = lpParameter;
	cookie->dwCreationFlags = dwCreationFlags;

	/* Use a custom stack size (if given) */
	if (dwStackSize != 0) {
		error = pthread_attr_setstacksize(&attr, dwStackSize);
		if (error != EOK)
			goto seterr_attr;
	}

	/* Actually create the new thread. */
	error = pthread_create(&thread, &attr, &k32_thread_start_routine, cookie);
	pthread_attr_destroy(&attr);
	if (error != EOK)
		goto seterr;

	/* Construct a PIDFD descriptor for the thread. */
	tid = pthread_gettid_np(thread);
	if (lpThreadId)
		*lpThreadId = tid;
	result = libk32_OpenThread(0, FALSE, tid);
	if (result == NULL)
		pthread_cancel(thread);

	/* Detach the pthread object. */
	pthread_detach(thread);

	if (dwCreationFlags & CREATE_SUSPENDED) {
		/* TODO: Wait for the thread to suspend itself */
	}

	/* Return a OS-level handle for the thread. */
	return result;
seterr_attr:
	pthread_attr_destroy(&attr);
seterr:
	errno = error;
err:
	return NULL;
}

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
	syslog(LOG_WARNING, "[k32] NotImplemented: IsProcessorFeaturePresent(%I32u)\n",
	       ProcessorFeature);
	return FALSE;
}

INTERN VOID WINAPI
libk32_FlushProcessWriteBuffers(VOID) {
	syslog(LOG_WARNING, "[k32] NotImplemented: FlushProcessWriteBuffers()\n");
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
	pid_t tid = libk32_GetThreadId(hThread);
	unsigned int mode;
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
	return libk32_QueueUserAPC2(pfnAPC, hThread, dwData, QUEUE_USER_APC_FLAGS_NONE);
}

INTERN DWORD WINAPI
libk32_SuspendThread(HANDLE hThread) {
	errno_t error;
	if (!NTHANDLE_ISFD(hThread)) {
		errno = EBADF;
		goto err;
	}
	error = sys_pidfd_send_signal(NTHANDLE_ASFD(hThread), SIGSTOP, NULL, 0);
	if (error != EOK) {
		errno = -error;
		goto err;
	}
	return 0;
err:
	return (DWORD)-1;
}

INTERN DWORD WINAPI
libk32_ResumeThread(HANDLE hThread) {
	errno_t error;
	if (!NTHANDLE_ISFD(hThread)) {
		errno = EBADF;
		goto err;
	}
	error = sys_pidfd_send_signal(NTHANDLE_ASFD(hThread), SIGCONT, NULL, 0);
	if (error != EOK) {
		errno = -error;
		goto err;
	}
	return 1;
err:
	return (DWORD)-1;
}

INTERN WINBOOL WINAPI
libk32_GetThreadContext(HANDLE hThread, LPCONTEXT lpContext) {
	syslog(LOG_WARNING, "[k32] NotImplemented: GetThreadContext(%p, %p)\n",
	       hThread, lpContext);
	errno = ENOTSUP;
	return FALSE;
}

INTERN WINBOOL WINAPI
libk32_SetThreadContext(HANDLE hThread, CONST CONTEXT *lpContext) {
	syslog(LOG_WARNING, "[k32] NotImplemented: SetThreadContext(%p, %p)\n",
	       hThread, lpContext);
	errno = ENOTSUP;
	return FALSE;
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
