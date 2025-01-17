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
#ifndef _NT_PROCESSTHREADSAPI_H
#define _NT_PROCESSTHREADSAPI_H 1

#include "__stdinc.h"
/**/

#include "types.h"
/**/

#ifdef __CC__
__DECL_BEGIN

#ifndef STATUS_PENDING
#define STATUS_PENDING ((DWORD)0x00000103)
#endif /* !STATUS_PENDING */
#define STILL_ACTIVE STATUS_PENDING

/************************************************************************/
/* INTER-PROCESS CONTROL                                                */
/************************************************************************/
WINBASEAPI WINBOOL WINAPI TerminateProcess(HANDLE hProcess, UINT uExitCode);
WINBASEAPI WINBOOL WINAPI TerminateThread(HANDLE hThread, DWORD dwExitCode);
WINBASEAPI HANDLE WINAPI OpenProcess(DWORD dwDesiredAccess, WINBOOL bInheritHandle, DWORD dwProcessId);
WINBASEAPI WINBOOL WINAPI GetExitCodeProcess(HANDLE hProcess, LPDWORD lpExitCode);
WINBASEAPI WINBOOL WINAPI GetExitCodeThread(HANDLE hThread, LPDWORD lpExitCode);
WINBASEAPI HANDLE WINAPI OpenThread(DWORD dwDesiredAccess, WINBOOL bInheritHandle, DWORD dwThreadId);
WINBASEAPI DWORD WINAPI GetProcessId(HANDLE hProcess);
WINBASEAPI DWORD WINAPI GetThreadId(HANDLE Thread);
WINBASEAPI WINBOOL WINAPI GetProcessHandleCount(HANDLE hProcess, PDWORD pdwHandleCount);
WINBASEAPI DWORD WINAPI GetProcessIdOfThread(HANDLE Thread);
WINBASEAPI HANDLE WINAPI GetCurrentProcess(VOID);
WINBASEAPI HANDLE WINAPI GetCurrentThread(VOID);


/************************************************************************/
/* SIMPLE PROC/THREAD CONTROL                                           */
/************************************************************************/
typedef DWORD(WINAPI *PTHREAD_START_ROUTINE)(LPVOID lpThreadParameter);
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;
#define CREATE_SUSPENDED 0x4
WINBASEAPI HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
WINBASEAPI DECLSPEC_NORETURN VOID WINAPI ExitThread(DWORD dwExitCode);
WINBASEAPI DECLSPEC_NORETURN VOID WINAPI ExitProcess(UINT uExitCode);
WINBASEAPI WINBOOL WINAPI SwitchToThread(VOID);
WINBASEAPI DWORD WINAPI GetCurrentProcessorNumber(VOID);
WINBASEAPI WINBOOL WINAPI ProcessIdToSessionId(DWORD dwProcessId, DWORD *pSessionId);
WINBASEAPI DWORD WINAPI GetCurrentProcessId(VOID);
WINBASEAPI DWORD WINAPI GetCurrentThreadId(VOID);
WINBASEAPI WINBOOL WINAPI IsProcessorFeaturePresent(DWORD ProcessorFeature);
WINBASEAPI VOID WINAPI FlushProcessWriteBuffers(VOID);
WINBASEAPI WINBOOL WINAPI FlushInstructionCache(HANDLE hProcess, LPCVOID lpBaseAddress, SIZE_T dwSize);
typedef VOID(NTAPI *PAPCFUNC)(ULONG_PTR Parameter);
typedef enum _QUEUE_USER_APC_FLAGS {
	QUEUE_USER_APC_FLAGS_NONE,
	QUEUE_USER_APC_FLAGS_SPECIAL_USER_APC
} QUEUE_USER_APC_FLAGS;
WINBASEAPI DWORD WINAPI QueueUserAPC(PAPCFUNC pfnAPC, HANDLE hThread, ULONG_PTR dwData);
WINBASEAPI BOOL WINAPI QueueUserAPC2(PAPCFUNC pfnAPC, HANDLE hThread, ULONG_PTR dwData, QUEUE_USER_APC_FLAGS flFlags);
WINBASEAPI DWORD WINAPI SuspendThread(HANDLE hThread);
WINBASEAPI DWORD WINAPI ResumeThread(HANDLE hThread);
typedef struct _CONTEXT {
	int placeholder; /* TODO */
} CONTEXT;
typedef CONTEXT *LPCONTEXT;
WINBASEAPI WINBOOL WINAPI GetThreadContext(HANDLE hThread, LPCONTEXT lpContext);
WINBASEAPI WINBOOL WINAPI SetThreadContext(HANDLE hThread, CONST CONTEXT *lpContext);



/************************************************************************/
/* TLS                                                                  */
/************************************************************************/
#define TLS_OUT_OF_INDEXES ((DWORD)0xffffffff)
WINBASEAPI DWORD WINAPI TlsAlloc(VOID);
WINBASEAPI LPVOID WINAPI TlsGetValue(DWORD dwTlsIndex);
WINBASEAPI WINBOOL WINAPI TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue);
WINBASEAPI WINBOOL WINAPI TlsFree(DWORD dwTlsIndex);

__DECL_END
#endif /* __CC__ */

#endif /* !_NT_PROCESSTHREADSAPI_H */
