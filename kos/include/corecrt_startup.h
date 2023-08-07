/* HASH CRC-32:0x1fd5138c */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/corecrt_startup.h) */
/* (#) Portability: Windows Kits (/ucrt/corecrt_startup.h) */
#ifndef _CORECRT_STARTUP_H
#define _CORECRT_STARTUP_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <bits/crt/dos/corecrt_startup.h>
#include <vcruntime_startup.h>

#ifdef __USE_DOS
#include <corecrt.h>
#ifndef __USE_DOS_CLEAN
#include <math.h>
#endif /* !__USE_DOS_CLEAN */
#endif /* !__USE_DOS */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifdef __CRT_HAVE__seh_filter_dll
__LIBC __ATTR_INOUT(2) int __NOTHROW_NCX(__LIBDCALL _seh_filter_dll)(__ULONG32_TYPE__ __xno, struct _EXCEPTION_POINTERS *__infp_ptrs) __CASMNAME_SAME("_seh_filter_dll");
#endif /* __CRT_HAVE__seh_filter_dll */
#ifdef __CRT_HAVE__seh_filter_exe
__LIBC __ATTR_INOUT(2) int __NOTHROW_NCX(__LIBDCALL _seh_filter_exe)(__ULONG32_TYPE__ __xno, struct _EXCEPTION_POINTERS *__infp_ptrs) __CASMNAME_SAME("_seh_filter_exe");
#endif /* __CRT_HAVE__seh_filter_exe */
#ifdef __CRT_HAVE__query_app_type
__LIBC __ATTR_CONST __ATTR_WUNUSED _crt_app_type __NOTHROW(__LIBDCALL _query_app_type)(void) __CASMNAME_SAME("_query_app_type");
#else /* __CRT_HAVE__query_app_type */
#include <libc/local/corecrt_startup/_query_app_type.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_query_app_type, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED _crt_app_type __NOTHROW(__LIBDCALL _query_app_type)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_query_app_type))(); })
#endif /* !__CRT_HAVE__query_app_type */
#ifdef __CRT_HAVE__set_app_type
__LIBC void __NOTHROW_NCX(__LIBDCALL _set_app_type)(_crt_app_type __type) __CASMNAME_SAME("_set_app_type");
#elif defined(__CRT_HAVE___set_app_type)
__COMPILER_CREDIRECT_VOID(__LIBC,,__NOTHROW_NCX,__LIBDCALL,_set_app_type,(_crt_app_type __type),__set_app_type,(__type))
#endif /* ... */
__CDECLARE_VOID_OPT(__ATTR_NONNULL((1)),__NOTHROW_NCX,__setusermatherr,(int (__LIBCCALL *__fptr)(struct _exception *)),(__fptr))
#ifdef __CRT_HAVE__configure_narrow_argv
__LIBC errno_t __NOTHROW_NCX(__LIBDCALL _configure_narrow_argv)(_crt_argv_mode __mode) __CASMNAME_SAME("_configure_narrow_argv");
#else /* __CRT_HAVE__configure_narrow_argv */
#include <libc/local/corecrt_startup/_configure_narrow_argv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_configure_narrow_argv, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBDCALL _configure_narrow_argv)(_crt_argv_mode __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_configure_narrow_argv))(__mode); })
#endif /* !__CRT_HAVE__configure_narrow_argv */
#ifdef __CRT_HAVE__configure_wide_argv
__LIBC errno_t __NOTHROW_NCX(__LIBDCALL _configure_wide_argv)(_crt_argv_mode __mode) __CASMNAME_SAME("_configure_wide_argv");
#else /* __CRT_HAVE__configure_wide_argv */
#include <libc/local/corecrt_startup/_configure_wide_argv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_configure_wide_argv, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBDCALL _configure_wide_argv)(_crt_argv_mode __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_configure_wide_argv))(__mode); })
#endif /* !__CRT_HAVE__configure_wide_argv */
#ifdef __CRT_HAVE__initialize_narrow_environment
__LIBC int __NOTHROW_NCX(__LIBDCALL _initialize_narrow_environment)(void) __CASMNAME_SAME("_initialize_narrow_environment");
#else /* __CRT_HAVE__initialize_narrow_environment */
#include <libc/local/corecrt_startup/_initialize_narrow_environment.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_initialize_narrow_environment, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBDCALL _initialize_narrow_environment)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_initialize_narrow_environment))(); })
#endif /* !__CRT_HAVE__initialize_narrow_environment */
#ifdef __CRT_HAVE__initialize_wide_environment
__LIBC int __NOTHROW_NCX(__LIBDCALL _initialize_wide_environment)(void) __CASMNAME_SAME("_initialize_wide_environment");
#else /* __CRT_HAVE__initialize_wide_environment */
#include <libc/local/corecrt_startup/_initialize_wide_environment.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_initialize_wide_environment, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBDCALL _initialize_wide_environment)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_initialize_wide_environment))(); })
#endif /* !__CRT_HAVE__initialize_wide_environment */
#ifdef __CRT_HAVE__get_initial_narrow_environment
__LIBC __ATTR_PURE __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBDCALL _get_initial_narrow_environment)(void) __CASMNAME_SAME("_get_initial_narrow_environment");
#elif defined(__CRT_HAVE___p___initenv)
#include <libc/local/corecrt_startup/_get_initial_narrow_environment.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_initial_narrow_environment, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBDCALL _get_initial_narrow_environment)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_initial_narrow_environment))(); })
#endif /* ... */
#ifdef __CRT_HAVE__get_initial_wide_environment
__LIBC __ATTR_PURE __ATTR_WUNUSED __WCHAR16_TYPE__ **__NOTHROW_NCX(__LIBDCALL _get_initial_wide_environment)(void) __CASMNAME_SAME("_get_initial_wide_environment");
#elif (defined(__CRT_HAVE___p___winitenv) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$__p___winitenv)
#include <libc/local/corecrt_startup/_get_initial_wide_environment.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_initial_wide_environment, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WCHAR16_TYPE__ **__NOTHROW_NCX(__LIBDCALL _get_initial_wide_environment)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_initial_wide_environment))(); })
#endif /* ... */
#ifdef __CRT_HAVE__get_narrow_winmain_command_line
__LIBC __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL _get_narrow_winmain_command_line)(void) __CASMNAME_SAME("_get_narrow_winmain_command_line");
#elif defined(__CRT_HAVE___p__acmdln)
#include <libc/local/corecrt_startup/_get_narrow_winmain_command_line.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_narrow_winmain_command_line, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL _get_narrow_winmain_command_line)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_narrow_winmain_command_line))(); })
#endif /* ... */
#ifdef __CRT_HAVE__get_wide_winmain_command_line
__LIBC __ATTR_PURE __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL _get_wide_winmain_command_line)(void) __CASMNAME_SAME("_get_wide_winmain_command_line");
#elif (defined(__CRT_HAVE___p__wcmdln) && defined(__PE__)) || defined(__CRT_HAVE_DOS$__p__wcmdln)
#include <libc/local/corecrt_startup/_get_wide_winmain_command_line.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_wide_winmain_command_line, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL _get_wide_winmain_command_line)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_wide_winmain_command_line))(); })
#endif /* ... */
#ifdef __CRT_HAVE___p__acmdln
__LIBC char **__NOTHROW_NCX(__LIBDCALL __p__acmdln)(void) __CASMNAME_SAME("__p__acmdln");
#endif /* __CRT_HAVE___p__acmdln */
#if defined(__CRT_HAVE___p__wcmdln) && defined(__PE__)
__LIBC __WCHAR16_TYPE__ **__NOTHROW_NCX(__LIBDCALL __p__wcmdln)(void) __CASMNAME_SAME("__p__wcmdln");
#elif defined(__CRT_HAVE_DOS$__p__wcmdln)
__CREDIRECT_DOS(,__WCHAR16_TYPE__ **,__NOTHROW_NCX,__p__wcmdln,(void),__p__wcmdln,())
#endif /* ... */
#ifndef ___acmdln
#ifdef __CRT_HAVE__acmdln
__CSDECLARE(,char *,_acmdln)
#define _acmdln _acmdln
#elif defined(__CRT_HAVE___p__acmdln)
#define _acmdln (*__p__acmdln())
#endif /* ... */
#endif /* !___acmdln */
#ifndef ___wcmdln
#if defined(__CRT_HAVE__wcmdln) && defined(__PE__)
__CSDECLARE(,__WCHAR16_TYPE__ *,_wcmdln)
#define _wcmdln _wcmdln
#elif defined(DOS$_wcmdln)
#define _wcmdln DOS$_wcmdln
#elif defined(__CRT_HAVE_DOS$_wcmdln)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,__WCHAR16_TYPE__ *,_wcmdln,DOS$_wcmdln)
#define _wcmdln _wcmdln
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,__WCHAR16_TYPE__ *,DOS$_wcmdln)
#define DOS$_wcmdln DOS$_wcmdln
#define _wcmdln     DOS$_wcmdln
#endif /* __NO_COMPILER_SREDIRECT */
#elif (defined(__CRT_HAVE___p__wcmdln) && defined(__PE__)) || defined(__CRT_HAVE_DOS$__p__wcmdln)
#define _wcmdln (*__p__wcmdln())
#endif /* ... */
#endif /* !___wcmdln */
#ifdef __CRT_HAVE__initterm
__LIBC void __NOTHROW_NCX(__LIBDCALL _initterm)(_PVFV *__start, _PVFV *__end) __CASMNAME_SAME("_initterm");
#else /* __CRT_HAVE__initterm */
#include <libc/local/corecrt_startup/_initterm.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_initterm, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBDCALL _initterm)(_PVFV *__start, _PVFV *__end) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_initterm))(__start, __end); })
#endif /* !__CRT_HAVE__initterm */
#ifdef __CRT_HAVE__initterm_e
__LIBC int __NOTHROW_NCX(__LIBDCALL _initterm_e)(_onexit_t *__start, _onexit_t *__end) __CASMNAME_SAME("_initterm_e");
#else /* __CRT_HAVE__initterm_e */
#include <libc/local/corecrt_startup/_initterm_e.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_initterm_e, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBDCALL _initterm_e)(_onexit_t *__start, _onexit_t *__end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_initterm_e))(__start, __end); })
#endif /* !__CRT_HAVE__initterm_e */
#ifdef __CRT_HAVE__initialize_onexit_table
__LIBC int __NOTHROW_NCX(__LIBDCALL _initialize_onexit_table)(struct _onexit_table_t *__self) __CASMNAME_SAME("_initialize_onexit_table");
#else /* __CRT_HAVE__initialize_onexit_table */
#include <libc/local/corecrt_startup/_initialize_onexit_table.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_initialize_onexit_table, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBDCALL _initialize_onexit_table)(struct _onexit_table_t *__self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_initialize_onexit_table))(__self); })
#endif /* !__CRT_HAVE__initialize_onexit_table */
#ifdef __CRT_HAVE__register_onexit_function
__LIBC int __NOTHROW_NCX(__LIBDCALL _register_onexit_function)(struct _onexit_table_t *__self, _onexit_t __function) __CASMNAME_SAME("_register_onexit_function");
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <libc/local/corecrt_startup/_register_onexit_function.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_register_onexit_function, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBDCALL _register_onexit_function)(struct _onexit_table_t *__self, _onexit_t __function) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_register_onexit_function))(__self, __function); })
#endif /* ... */
#ifdef __CRT_HAVE__execute_onexit_table
__LIBC int __NOTHROW_NCX(__LIBDCALL _execute_onexit_table)(struct _onexit_table_t *__self) __CASMNAME_SAME("_execute_onexit_table");
#else /* __CRT_HAVE__execute_onexit_table */
#include <libc/local/corecrt_startup/_execute_onexit_table.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_execute_onexit_table, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBDCALL _execute_onexit_table)(struct _onexit_table_t *__self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_execute_onexit_table))(__self); })
#endif /* !__CRT_HAVE__execute_onexit_table */
#ifdef __CRT_HAVE_atexit
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_crt_atexit,(void (__LIBCCALL *__func)(void)),atexit,(__func))
#elif defined(__CRT_HAVE__crt_atexit)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_crt_atexit,(void (__LIBCCALL *__func)(void)),(__func))
#elif defined(__CRT_HAVE_at_quick_exit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_crt_atexit,(void (__LIBCCALL *__func)(void)),at_quick_exit,(__func))
#elif defined(__CRT_HAVE__crt_at_quick_exit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_crt_atexit,(void (__LIBCCALL *__func)(void)),_crt_at_quick_exit,(__func))
#elif defined(__CRT_HAVE_xatexit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_crt_atexit,(void (__LIBCCALL *__func)(void)),xatexit,(__func))
#endif /* ... */
#ifdef __CRT_HAVE_at_quick_exit
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_crt_at_quick_exit,(void (__LIBCCALL *__func)(void)),at_quick_exit,(__func))
#elif defined(__CRT_HAVE__crt_at_quick_exit)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_crt_at_quick_exit,(void (__LIBCCALL *__func)(void)),(__func))
#elif defined(__CRT_HAVE_atexit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_crt_at_quick_exit,(void (__LIBCCALL *__func)(void)),atexit,(__func))
#elif defined(__CRT_HAVE__crt_atexit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_crt_at_quick_exit,(void (__LIBCCALL *__func)(void)),_crt_atexit,(__func))
#endif /* ... */

/* Static functions */
#ifdef _MSC_VER
extern int (__LIBDCALL _is_c_termination_complete)(void);
extern __BOOL (__LIBDCALL __acrt_initialize)(void);
extern __BOOL (__LIBDCALL __acrt_uninitialize)(__BOOL __terminating);
extern __BOOL (__LIBDCALL __acrt_uninitialize_critical)(__BOOL __terminating);
extern __BOOL (__LIBDCALL __acrt_thread_attach)(void);
extern __BOOL (__LIBDCALL __acrt_thread_detach)(void);
#endif /* _MSC_VER */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_CORECRT_STARTUP_H */
