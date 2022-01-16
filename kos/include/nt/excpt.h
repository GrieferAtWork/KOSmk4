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
#ifndef _INC_EXCPT
#define _INC_EXCPT 1

#include "__winstd.h"

#ifdef __COMPILER_HAVE_PRAGMA_PACK
#pragma pack(push, _CRT_PACKING)
#endif /* __COMPILER_HAVE_PRAGMA_PACK */

#ifdef __CC__
__DECL_BEGIN

struct _EXCEPTION_POINTERS;
#ifndef EXCEPTION_DISPOSITION
#define EXCEPTION_DISPOSITION   int
#endif /* !EXCEPTION_DISPOSITION */
#define ExceptionContinueExecution 0
#define ExceptionContinueSearch    1
#define ExceptionNestedException   2
#define ExceptionCollidedUnwind    3

#if defined(__i386__) && !defined(__x86_64__)
struct _EXCEPTION_RECORD;
struct _CONTEXT;
EXCEPTION_DISPOSITION __cdecl
_except_handler(struct _EXCEPTION_RECORD *_ExceptionRecord,
                void *_EstablisherFrame,
                struct _CONTEXT *_ContextRecord,
                void *_DispatcherContext);
#elif defined(__ia64__)
typedef struct _EXCEPTION_POINTERS *Exception_info_ptr;
struct _EXCEPTION_RECORD;
struct _CONTEXT;
struct _DISPATCHER_CONTEXT;
__MINGW_EXTENSION _CRTIMP EXCEPTION_DISPOSITION __cdecl
__C_specific_handler(struct _EXCEPTION_RECORD *_ExceptionRecord,
                     unsigned __int64 _MemoryStackFp,
                     unsigned __int64 _BackingStoreFp,
                     struct _CONTEXT *_ContextRecord,
                     struct _DISPATCHER_CONTEXT *_DispatcherContext,
                     unsigned __int64 _GlobalPointer);
#elif defined(__x86_64__)
struct _EXCEPTION_RECORD;
struct _CONTEXT;
#endif /* ... */

#define GetExceptionCode         _exception_code
#define exception_code           _exception_code
#define GetExceptionInformation (struct _EXCEPTION_POINTERS *)_exception_info
#define exception_info          (struct _EXCEPTION_POINTERS *)_exception_info
#define AbnormalTermination      _abnormal_termination
#define abnormal_termination     _abnormal_termination

unsigned long (__cdecl _exception_code)(void);
void *(__cdecl _exception_info)(void);
int (__cdecl _abnormal_termination)(void);

#define EXCEPTION_EXECUTE_HANDLER      1
#define EXCEPTION_CONTINUE_SEARCH      0
#define EXCEPTION_CONTINUE_EXECUTION (-1)

/* CRT stuff */
typedef void (__cdecl *_PHNDLR)(int);

struct _XCPT_ACTION {
	unsigned long XcptNum;
	int           SigNum;
	_PHNDLR       XcptAction;
};
extern struct _XCPT_ACTION _XcptActTab[];
extern int _XcptActTabCount;
extern int _XcptActTabSize;
extern int _First_FPE_Indx;
extern int _Num_FPE;
int (__cdecl __CppXcptFilter)(unsigned long _ExceptionNum, struct _EXCEPTION_POINTERS *_ExceptionPtr);
int (__cdecl _XcptFilter)(unsigned long _ExceptionNum, struct _EXCEPTION_POINTERS *_ExceptionPtr);

/* The type of function that is expected as an
 * exception handler to be installed with __try1. */
#ifndef __PEXCEPTION_HANDLER_DEFINED
#define __PEXCEPTION_HANDLER_DEFINED 1
typedef EXCEPTION_DISPOSITION (*PEXCEPTION_HANDLER)(struct _EXCEPTION_RECORD *,
                                                    void *, struct _CONTEXT *, void *);
#endif /* !__PEXCEPTION_HANDLER_DEFINED */

#ifndef HAVE_NO_SEH
/* This is not entirely necessary, but it is the
 * structure installed by the __try1 primitive below. */
typedef struct _EXCEPTION_REGISTRATION {
	struct _EXCEPTION_REGISTRATION *prev;
	EXCEPTION_DISPOSITION         (*handler)(struct _EXCEPTION_RECORD *, void *, struct _CONTEXT *, void *);
} EXCEPTION_REGISTRATION, *PEXCEPTION_REGISTRATION;
typedef EXCEPTION_REGISTRATION EXCEPTION_REGISTRATION_RECORD;
typedef PEXCEPTION_REGISTRATION PEXCEPTION_REGISTRATION_RECORD;
#endif /* !HAVE_NO_SEH */

#if defined(__i386__) && !defined(__x86_64__)
#define __try1(pHandler) __asm__ __volatile__ ("pushl %0;pushl %%fs:0;movl %%esp,%%fs:0;" : : "g" (pHandler));
#define __except1        __asm__ __volatile__ ("movl (%%esp),%%eax;movl %%eax,%%fs:0;addl $8,%%esp;" : : : "%eax");
#elif defined(__x86_64__)
#define __try1(pHandler) __asm__ __volatile__ ("pushq %0;pushq %%gs:0;movq %%rsp,%%gs:0;" : : "g" (pHandler));
#define __except1        __asm__ __volatile__ ("movq (%%rsp),%%rax;movq %%rax,%%gs:0;addq $16,%%rsp;" : : : "%rax");
#else /* ... */
#define __try1(pHandler)
#define __except1
#endif

__DECL_END
#endif /* __CC__ */

#ifdef __COMPILER_HAVE_PRAGMA_PACK
#pragma pack(pop)
#endif /* __COMPILER_HAVE_PRAGMA_PACK */

#endif /* !_INC_EXCPT */
