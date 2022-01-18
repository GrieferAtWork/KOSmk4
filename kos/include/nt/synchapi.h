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
#ifndef _NT_SYNCHAPI_H
#define _NT_SYNCHAPI_H 1

#include "__stdinc.h"
/**/

#include "types.h"
/**/

#include <features.h>
#include <hybrid/typecore.h>

#ifdef __USE_KOS_ALTERATIONS
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
#endif /* __USE_KOS_ALTERATIONS */

/* NT Synchronization Primitives */

#ifdef __CC__
__DECL_BEGIN

typedef void *LPSECURITY_ATTRIBUTES;
typedef void *PREASON_CONTEXT;


/************************************************************************/
/* CRITICAL_SECTION                                                     */
/************************************************************************/
typedef struct _RTL_CRITICAL_SECTION_DEBUG {
	WORD Type;
	WORD CreatorBackTraceIndex;
	struct _RTL_CRITICAL_SECTION *CriticalSection;
	LIST_ENTRY ProcessLocksList;
	DWORD EntryCount;
	DWORD ContentionCount;
	DWORD Flags;
	WORD CreatorBackTraceIndexHigh;
	WORD SpareWORD;
} RTL_CRITICAL_SECTION_DEBUG, *PRTL_CRITICAL_SECTION_DEBUG, RTL_RESOURCE_DEBUG, *PRTL_RESOURCE_DEBUG;
typedef RTL_CRITICAL_SECTION_DEBUG CRITICAL_SECTION_DEBUG;
typedef PRTL_CRITICAL_SECTION_DEBUG PCRITICAL_SECTION_DEBUG;
typedef PRTL_CRITICAL_SECTION_DEBUG LPCRITICAL_SECTION_DEBUG;
#define RTL_CRITSECT_TYPE                          0
#define RTL_RESOURCE_TYPE                          1
#define RTL_CRITICAL_SECTION_FLAG_NO_DEBUG_INFO    0x01000000
#define RTL_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN     0x02000000
#define RTL_CRITICAL_SECTION_FLAG_STATIC_INIT      0x04000000
#define RTL_CRITICAL_SECTION_FLAG_RESOURCE_TYPE    0x08000000
#define RTL_CRITICAL_SECTION_FLAG_FORCE_DEBUG_INFO 0x10000000
#define RTL_CRITICAL_SECTION_ALL_FLAG_BITS         0xff000000
#define RTL_CRITICAL_SECTION_FLAG_RESERVED        \
	(RTL_CRITICAL_SECTION_ALL_FLAG_BITS &         \
	 (~(RTL_CRITICAL_SECTION_FLAG_NO_DEBUG_INFO | \
	    RTL_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN |  \
	    RTL_CRITICAL_SECTION_FLAG_STATIC_INIT |   \
	    RTL_CRITICAL_SECTION_FLAG_RESOURCE_TYPE | \
	    RTL_CRITICAL_SECTION_FLAG_FORCE_DEBUG_INFO)))
#define RTL_CRITICAL_SECTION_DEBUG_FLAG_STATIC_INIT 0x00000001
#include "pshpack8.h"
typedef struct _RTL_CRITICAL_SECTION {
	PRTL_CRITICAL_SECTION_DEBUG DebugInfo; /* Unused under KOS */
	LONG LockCount;                        /* Unused under KOS */
	LONG RecursionCount;                   /* Unused under KOS */
#ifdef __USE_KOS_ALTERATIONS
	__pthread_t OwningThread;  /* pthread handle */
	__uintptr_t LockSemaphore; /* Futex (# of recursive locks by `OwningThread') */
#else /* __USE_KOS_ALTERATIONS */
	HANDLE OwningThread;
	HANDLE LockSemaphore;
#endif /* !__USE_KOS_ALTERATIONS */
	ULONG_PTR SpinCount;
} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;
typedef PRTL_CRITICAL_SECTION PCRITICAL_SECTION;
typedef PRTL_CRITICAL_SECTION LPCRITICAL_SECTION;
typedef RTL_CRITICAL_SECTION CRITICAL_SECTION;
#include "poppack.h"
WINBASEAPI VOID WINAPI EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI VOID WINAPI LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI WINBOOL WINAPI TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI VOID WINAPI DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI WINBOOL WINAPI InitializeCriticalSectionEx(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount, DWORD Flags);
WINBASEAPI VOID WINAPI InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI WINBOOL WINAPI InitializeCriticalSectionAndSpinCount(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount);
WINBASEAPI DWORD WINAPI SetCriticalSectionSpinCount(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount);





/************************************************************************/
/* CRITICAL_SECTION                                                     */
/************************************************************************/
typedef struct _RTL_SRWLOCK {
	PVOID Ptr;
} RTL_SRWLOCK, *PRTL_SRWLOCK;
typedef RTL_SRWLOCK SRWLOCK, *PSRWLOCK;
#define RTL_SRWLOCK_INIT { 0 }
#define SRWLOCK_INIT RTL_SRWLOCK_INIT
WINBASEAPI VOID WINAPI InitializeSRWLock(PSRWLOCK SRWLock);
WINBASEAPI VOID WINAPI ReleaseSRWLockExclusive(PSRWLOCK SRWLock);
WINBASEAPI VOID WINAPI ReleaseSRWLockShared(PSRWLOCK SRWLock);
WINBASEAPI VOID WINAPI AcquireSRWLockExclusive(PSRWLOCK SRWLock);
WINBASEAPI VOID WINAPI AcquireSRWLockShared(PSRWLOCK SRWLock);
WINBASEAPI BOOLEAN WINAPI TryAcquireSRWLockExclusive(PSRWLOCK SRWLock);
WINBASEAPI BOOLEAN WINAPI TryAcquireSRWLockShared(PSRWLOCK SRWLock);




/************************************************************************/
/* CONDITION_VARIABLE                                                   */
/************************************************************************/
typedef struct _RTL_CONDITION_VARIABLE {
	PVOID Ptr;
} RTL_CONDITION_VARIABLE, *PRTL_CONDITION_VARIABLE;
typedef RTL_CONDITION_VARIABLE CONDITION_VARIABLE, *PCONDITION_VARIABLE;
#define RTL_CONDITION_VARIABLE_INIT { 0 }
#define RTL_CONDITION_VARIABLE_LOCKMODE_SHARED 0x1
#define CONDITION_VARIABLE_INIT            RTL_CONDITION_VARIABLE_INIT
#define CONDITION_VARIABLE_LOCKMODE_SHARED RTL_CONDITION_VARIABLE_LOCKMODE_SHARED
WINBASEAPI VOID WINAPI InitializeConditionVariable(PCONDITION_VARIABLE ConditionVariable);
WINBASEAPI VOID WINAPI WakeConditionVariable(PCONDITION_VARIABLE ConditionVariable);
WINBASEAPI VOID WINAPI WakeAllConditionVariable(PCONDITION_VARIABLE ConditionVariable);
WINBASEAPI WINBOOL WINAPI SleepConditionVariableCS(PCONDITION_VARIABLE ConditionVariable, PCRITICAL_SECTION CriticalSection, DWORD dwMilliseconds);
WINBASEAPI WINBOOL WINAPI SleepConditionVariableSRW(PCONDITION_VARIABLE ConditionVariable, PSRWLOCK SRWLock, DWORD dwMilliseconds, ULONG Flags);




/************************************************************************/
/* INIT_ONCE                                                            */
/************************************************************************/
#ifndef _RTL_RUN_ONCE_DEF
#define _RTL_RUN_ONCE_DEF 1
typedef struct _RTL_RUN_ONCE {
	PVOID Ptr;
} RTL_RUN_ONCE, *PRTL_RUN_ONCE;
typedef DWORD (WINAPI *PRTL_RUN_ONCE_INIT_FN)(PRTL_RUN_ONCE InitOnce, PVOID Parameter, PVOID *Context);
#define RTL_RUN_ONCE_INIT { 0 }
#define RTL_RUN_ONCE_CHECK_ONLY        __MSABI_LONG(1U)
#define RTL_RUN_ONCE_ASYNC             __MSABI_LONG(2U)
#define RTL_RUN_ONCE_INIT_FAILED       __MSABI_LONG(4U)
#define RTL_RUN_ONCE_CTX_RESERVED_BITS 2
#endif /* !_RTL_RUN_ONCE_DEF */
typedef RTL_RUN_ONCE INIT_ONCE;
typedef PRTL_RUN_ONCE PINIT_ONCE;
typedef PRTL_RUN_ONCE LPINIT_ONCE;
typedef WINBOOL (WINAPI *PINIT_ONCE_FN)(PINIT_ONCE InitOnce, PVOID Parameter, PVOID *Context);
#define INIT_ONCE_STATIC_INIT       RTL_RUN_ONCE_INIT
#define INIT_ONCE_CHECK_ONLY        RTL_RUN_ONCE_CHECK_ONLY
#define INIT_ONCE_ASYNC             RTL_RUN_ONCE_ASYNC
#define INIT_ONCE_INIT_FAILED       RTL_RUN_ONCE_INIT_FAILED
#define INIT_ONCE_CTX_RESERVED_BITS RTL_RUN_ONCE_CTX_RESERVED_BITS
WINBASEAPI VOID WINAPI InitOnceInitialize(PINIT_ONCE InitOnce);
WINBASEAPI WINBOOL WINAPI InitOnceExecuteOnce(PINIT_ONCE InitOnce, PINIT_ONCE_FN InitFn, PVOID Parameter, LPVOID *Context);
WINBASEAPI WINBOOL WINAPI InitOnceBeginInitialize(LPINIT_ONCE lpInitOnce, DWORD dwFlags, PBOOL fPending, LPVOID *lpContext);
WINBASEAPI WINBOOL WINAPI InitOnceComplete(LPINIT_ONCE lpInitOnce, DWORD dwFlags, LPVOID lpContext);




/************************************************************************/
/* MUTEX                                                                */
/************************************************************************/
#define MUTEX_MODIFY_STATE MUTANT_QUERY_STATE
#define MUTEX_ALL_ACCESS   MUTANT_ALL_ACCESS
WINBASEAPI WINBOOL WINAPI ReleaseMutex(HANDLE hMutex);
WINBASEAPI HANDLE WINAPI OpenMutexW(DWORD dwDesiredAccess, WINBOOL bInheritHandle, LPCWSTR lpName);
#define CREATE_MUTEX_INITIAL_OWNER 0x1
WINBASEAPI HANDLE WINAPI CreateMutexExA(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess);
WINBASEAPI HANDLE WINAPI CreateMutexExW(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess);
WINBASEAPI HANDLE WINAPI CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, WINBOOL bInitialOwner, LPCSTR lpName);
WINBASEAPI HANDLE WINAPI CreateMutexW(LPSECURITY_ATTRIBUTES lpMutexAttributes, WINBOOL bInitialOwner, LPCWSTR lpName);




/************************************************************************/
/* EVENT                                                                */
/************************************************************************/
WINBASEAPI WINBOOL WINAPI SetEvent(HANDLE hEvent);
WINBASEAPI WINBOOL WINAPI ResetEvent(HANDLE hEvent);
WINBASEAPI HANDLE WINAPI OpenEventA(DWORD dwDesiredAccess, WINBOOL bInheritHandle, LPCSTR lpName);
WINBASEAPI HANDLE WINAPI OpenEventW(DWORD dwDesiredAccess, WINBOOL bInheritHandle, LPCWSTR lpName);
#define CREATE_EVENT_MANUAL_RESET 0x1
#define CREATE_EVENT_INITIAL_SET  0x2
WINBASEAPI HANDLE WINAPI CreateEventExA(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess);
WINBASEAPI HANDLE WINAPI CreateEventExW(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess);
WINBASEAPI HANDLE WINAPI CreateEventA(LPSECURITY_ATTRIBUTES lpEventAttributes, WINBOOL bManualReset, WINBOOL bInitialState, LPCSTR lpName);
WINBASEAPI HANDLE WINAPI CreateEventW(LPSECURITY_ATTRIBUTES lpEventAttributes, WINBOOL bManualReset, WINBOOL bInitialState, LPCWSTR lpName);




/************************************************************************/
/* SYNCHRONIZATION_BARRIER                                              */
/************************************************************************/
typedef struct _RTL_BARRIER {
	DWORD Reserved1;
	DWORD Reserved2;
	ULONG_PTR Reserved3[2];
	DWORD Reserved4;
	DWORD Reserved5;
} RTL_BARRIER, *PRTL_BARRIER;
typedef RTL_BARRIER SYNCHRONIZATION_BARRIER;
typedef PRTL_BARRIER PSYNCHRONIZATION_BARRIER;
typedef PRTL_BARRIER LPSYNCHRONIZATION_BARRIER;
#define SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY  0x01
#define SYNCHRONIZATION_BARRIER_FLAGS_BLOCK_ONLY 0x02
#define SYNCHRONIZATION_BARRIER_FLAGS_NO_DELETE  0x04
WINBASEAPI WINBOOL WINAPI EnterSynchronizationBarrier(LPSYNCHRONIZATION_BARRIER lpBarrier, DWORD dwFlags);
WINBASEAPI WINBOOL WINAPI InitializeSynchronizationBarrier(LPSYNCHRONIZATION_BARRIER lpBarrier, LONG lTotalThreads, LONG lSpinCount);
WINBASEAPI WINBOOL WINAPI DeleteSynchronizationBarrier(LPSYNCHRONIZATION_BARRIER lpBarrier);




/************************************************************************/
/* SEMAPHORE                                                            */
/************************************************************************/
WINBASEAPI WINBOOL WINAPI ReleaseSemaphore(HANDLE hSemaphore, LONG lReleaseCount, LPLONG lpPreviousCount);
WINBASEAPI HANDLE WINAPI OpenSemaphoreW(DWORD dwDesiredAccess, WINBOOL bInheritHandle, LPCWSTR lpName);
WINBASEAPI HANDLE WINAPI CreateSemaphoreExW(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess);




/************************************************************************/
/* FUTEX                                                                */
/************************************************************************/
WINBASEAPI WINBOOL WINAPI WaitOnAddress(volatile VOID *Address, PVOID CompareAddress, SIZE_T AddressSize, DWORD dwMilliseconds);
WINBASEAPI VOID WINAPI WakeByAddressSingle(PVOID Address);
WINBASEAPI VOID WINAPI WakeByAddressAll(PVOID Address);




/************************************************************************/
/* TIMER                                                                */
/************************************************************************/
typedef VOID (APIENTRY *PTIMERAPCROUTINE)(LPVOID lpArgToCompletionRoutine, DWORD dwTimerLowValue, DWORD dwTimerHighValue);
WINBASEAPI WINBOOL WINAPI SetWaitableTimer(HANDLE hTimer, LARGE_INTEGER const *lpDueTime, LONG lPeriod, PTIMERAPCROUTINE pfnCompletionRoutine, LPVOID lpArgToCompletionRoutine, WINBOOL fResume);
WINBASEAPI WINBOOL WINAPI CancelWaitableTimer(HANDLE hTimer);
WINBASEAPI HANDLE WINAPI OpenWaitableTimerW(DWORD dwDesiredAccess, WINBOOL bInheritHandle, LPCWSTR lpTimerName);
#define CREATE_WAITABLE_TIMER_MANUAL_RESET 0x1
WINBASEAPI HANDLE WINAPI CreateWaitableTimerExW(LPSECURITY_ATTRIBUTES lpTimerAttributes, LPCWSTR lpTimerName, DWORD dwFlags, DWORD dwDesiredAccess);
WINBASEAPI WINBOOL WINAPI SetWaitableTimerEx(HANDLE hTimer, LARGE_INTEGER const *lpDueTime, LONG lPeriod, PTIMERAPCROUTINE pfnCompletionRoutine, LPVOID lpArgToCompletionRoutine, PREASON_CONTEXT WakeContext, ULONG TolerableDelay);




/************************************************************************/
/* MISC                                                                 */
/************************************************************************/
#define STATUS_WAIT_0           ((DWORD)0x00000000)
#define STATUS_ABANDONED_WAIT_0 ((DWORD)0x00000080)
#define STATUS_USER_APC         ((DWORD)0x000000C0)
#define STATUS_TIMEOUT          ((DWORD)0x00000102)
#define STATUS_PENDING          ((DWORD)0x00000103)
#define WAIT_FAILED             ((DWORD)0xffffffff)
#define WAIT_OBJECT_0           (STATUS_WAIT_0 + 0)
#define WAIT_ABANDONED          (STATUS_ABANDONED_WAIT_0 + 0)
#define WAIT_ABANDONED_0        (STATUS_ABANDONED_WAIT_0 + 0)
#define WAIT_IO_COMPLETION      STATUS_USER_APC
WINBASEAPI DWORD WINAPI WaitForSingleObjectEx(HANDLE hHandle, DWORD dwMilliseconds, WINBOOL bAlertable);
WINBASEAPI DWORD WINAPI WaitForMultipleObjectsEx(DWORD nCount, CONST HANDLE *lpHandles, WINBOOL bWaitAll, DWORD dwMilliseconds, WINBOOL bAlertable);
WINBASEAPI DWORD WINAPI WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);
WINBASEAPI DWORD WINAPI SleepEx(DWORD dwMilliseconds, WINBOOL bAlertable);
WINBASEAPI VOID WINAPI Sleep(DWORD dwMilliseconds);
WINBASEAPI DWORD WINAPI SignalObjectAndWait(HANDLE hObjectToSignal, HANDLE hObjectToWaitOn, DWORD dwMilliseconds, WINBOOL bAlertable);




/************************************************************************/
/* UNICODE                                                              */
/************************************************************************/
#define CreateMutex   __MINGW_NAME_AW(CreateMutex)
#define CreateMutexEx __MINGW_NAME_AW(CreateMutexEx)
#define CreateEvent   __MINGW_NAME_AW(CreateEvent)
#define CreateEventEx __MINGW_NAME_AW(CreateEventEx)
#define OpenEvent     __MINGW_NAME_AW(OpenEvent)
#ifdef UNICODE
#define CreateSemaphoreEx     CreateSemaphoreExW
#define OpenMutex             OpenMutexW
#define OpenSemaphore         OpenSemaphoreW
#define CreateWaitableTimerEx CreateWaitableTimerExW
#define OpenWaitableTimer     OpenWaitableTimerW
#endif /* UNICODE */

__DECL_END
#endif /* __CC__ */

#endif /* !_NT_SYNCHAPI_H */
