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
%(c_prefix){
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/corecrt_startup.h) */
/* (#) Portability: Windows Kits (/ucrt/corecrt_startup.h) */
}

%[default:section(".text.crt.dos.application.init")]

%[define_replacement(fd_t = __fd_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <vcruntime_startup.h>
)]%{

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

struct _EXCEPTION_POINTERS;

typedef enum _crt_app_type {
	_crt_unknown_app = 0,
	_crt_console_app = 1,
	_crt_gui_app     = 2,
} _crt_app_type;

typedef int (__LIBCCALL *_UserMathErrorFunctionPointer)(struct _exception *);

typedef void (__LIBDCALL *_PVFV)(void);
typedef int  (__LIBDCALL *_PIFV)(void);
typedef void (__LIBDCALL *_PVFI)(int __exit_code);

typedef struct _onexit_table_t {
	_PVFV *_first;
	_PVFV *_last;
	_PVFV *_end;
} _onexit_table_t;

#ifndef _CRT_ONEXIT_T_DEFINED
#define _CRT_ONEXIT_T_DEFINED
#ifndef _ONEXIT_T_DEFINED
#define _ONEXIT_T_DEFINED
typedef int (__LIBDCALL *_onexit_t)(void);
#endif /* !_ONEXIT_T_DEFINED */
#endif /* !_CRT_ONEXIT_T_DEFINED */

}

%[define(_crt_unknown_app = 0)]
%[define(_crt_console_app = 1)]
%[define(_crt_gui_app     = 2)]

%[define_replacement(_crt_argv_mode = "enum _crt_argv_mode")]
%[define_replacement(_crt_app_type = "enum _crt_app_type")]
%[define_type_class(_crt_argv_mode = "TD")]
%[define_type_class(_crt_app_type = "TD")]
%[define_type_class(_PVFV     = "TP")]
%[define_type_class(_PIFV     = "TP")]
%[define_type_class(_PVFI     = "TP")]
%[define_type_class(_onexit_t = "TP")]
%[define_type_class(onexit_t  = "TP")]

[[crt_dos_only]]
int _seh_filter_dll(__ULONG32_TYPE__ xno, [[nonnull]] struct _EXCEPTION_POINTERS *infp_ptrs);

[[crt_dos_only]]
int _seh_filter_exe(__ULONG32_TYPE__ xno, [[nonnull]] struct _EXCEPTION_POINTERS *infp_ptrs);

[[const, wunused, crt_dos_only]]
[[decl_include("<corecrt_startup.h>")]]
_crt_app_type _query_app_type(void) {
	return (_crt_app_type)_crt_console_app;
}

[[crt_dos_only, export_alias("__set_app_type")]]
[[decl_include("<corecrt_startup.h>")]]
void _set_app_type(_crt_app_type type);

[[crt_dos_variant]]
void __setusermatherr([[nonnull]] int (__LIBCCALL *fptr)(struct _exception *));

[[crt_dos_only, decl_include("<bits/types.h>", "<vcruntime_startup.h>")]]
errno_t _configure_narrow_argv(_crt_argv_mode mode) {
	COMPILER_IMPURE();
	(void)mode;
	return 0;
}

[[crt_dos_only, decl_include("<bits/types.h>", "<vcruntime_startup.h>")]]
[[crt_intern_alias("libc__configure_narrow_argv")]]
errno_t _configure_wide_argv(_crt_argv_mode mode) {
	COMPILER_IMPURE();
	(void)mode;
	return 0;
}

[[crt_dos_only]]
int _initialize_narrow_environment(void) {
	COMPILER_IMPURE();
	return 0;
}

[[crt_dos_only]]
[[crt_intern_alias("libc__initialize_narrow_environment")]]
int _initialize_wide_environment(void) {
	COMPILER_IMPURE();
	return 0;
}

[[wunused, pure, crt_dos_only, requires_function(__p___initenv)]]
char **_get_initial_narrow_environment(void) {
	return *__p___initenv();
}

[[wunused, pure, crt_dos_only, requires_function(__p___c16initenv)]]
__WCHAR16_TYPE__ **_get_initial_wide_environment(void) {
	return (__WCHAR16_TYPE__ **)*__p___c16initenv();
}

[[wunused, pure, crt_dos_only, requires_function(__p__acmdln)]]
char *_get_narrow_winmain_command_line(void) {
	return *__p__acmdln();
}

[[wunused, pure, crt_dos_only, requires_function(__p__wcmdln)]]
__WCHAR16_TYPE__ *_get_wide_winmain_command_line(void) {
	return (__WCHAR16_TYPE__ *)*__p__wcmdln();
}



[[crt_dos_only]]
char **__p__acmdln(void);

[[crt_dos_only, no_crt_self_import, no_crt_self_export]]
[[if(defined(__PE__)), alias("__p__wcmdln")]]
[[alias("DOS$__p__wcmdln"), export_as("DOS$__p__wcmdln")]]
__WCHAR16_TYPE__ **__p__wcmdln(void);

%[insert:pp_if(!defined(_acmdln))]
%[insert:pp_if(defined(__CRT_HAVE__acmdln))]
%__CSDECLARE(,char *,_acmdln)
%#define _acmdln _acmdln
%[insert:pp_elif($has_function(__p__acmdln))]
%#define _acmdln (*__p__acmdln())
%[insert:pp_endif]
%[insert:pp_endif]

%[insert:pp_if(!defined(_wcmdln))]
%[insert:pp_if(defined(__CRT_HAVE__wcmdln) && defined(__PE__))]
%__CSDECLARE(,__WCHAR16_TYPE__ *,_wcmdln)
%#define _wcmdln _wcmdln
%[insert:pp_elif(defined(@DOS$_wcmdln@))]
%#define _wcmdln DOS$_wcmdln
%[insert:pp_elif(defined(__CRT_HAVE_DOS$_wcmdln))]
%[insert:pp_if(!defined(__NO_COMPILER_SREDIRECT))]
%__CSREDIRECT(,__WCHAR16_TYPE__ *,_wcmdln,DOS$_wcmdln)
%#define _wcmdln _wcmdln
%[insert:pp_else]
%__CSDECLARE(,__WCHAR16_TYPE__ *,DOS$_wcmdln)
%#define DOS$_wcmdln DOS$_wcmdln
%#define _wcmdln     DOS$_wcmdln
%[insert:pp_endif]
%[insert:pp_elif($has_function(__p__wcmdln))]
%#define _wcmdln (*__p__wcmdln())
%[insert:pp_endif]
%[insert:pp_endif]



[[crt_dos_only, impl_include("<asm/os/syslog.h>")]]
void _initterm(_PVFV *start, _PVFV *end) {
	for (; start < end; ++start) {
		if (*start == NULL)
			continue;
@@pp_if $has_function(syslog)@@
		syslog(__LOG_DEBUG, "[libd] _initterm: call %p\n", *start);
@@pp_endif@@
		(**start)();
	}
@@pp_if $has_function(syslog)@@
	syslog(__LOG_DEBUG, "[libd] _initterm: done\n");
@@pp_endif@@
}

[[crt_dos_only, impl_include("<asm/os/syslog.h>")]]
int _initterm_e(_onexit_t *start, _onexit_t *end) {
	int result = 0;
	for (; start < end; ++start) {
		if (!*start)
			continue;
@@pp_if $has_function(syslog)@@
		syslog(__LOG_DEBUG, "[libd] _initterm_e: call %p\n", *start);
@@pp_endif@@
		result = (**start)();
		if (result != 0) {
@@pp_if $has_function(syslog)@@
			syslog(__LOG_DEBUG, "[libd] _initterm_e: call %p failed -> %d\n", *start, result);
@@pp_endif@@
			break;
		}
	}
@@pp_if $has_function(syslog)@@
	syslog(__LOG_DEBUG, "[libd] _initterm_e: done\n");
@@pp_endif@@
	return result;
}

[[crt_dos_only, decl_include("<corecrt_startup.h>"), requires_function(bzero)]]
int _initialize_onexit_table([[nullable]] struct _onexit_table_t *self) {
	if unlikely(!self)
		return -1;
	bzero(self, sizeof(*self));
	return 0;
}

[[decl_include("<corecrt_startup.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[crt_dos_only, requires_function(realloc, malloc_usable_size)]]
int _register_onexit_function([[nullable]] struct _onexit_table_t *self,
                              [[nullable]] _onexit_t function) {
	if unlikely(!self)
		return -1;
	if (self->@_last@ >= self->@_end@) {
		_onexit_t *newtab;
		size_t newcnt;
		newcnt = (size_t)(self->@_last@ - self->@_first@) + 1;
		newtab = (_onexit_t *)realloc(self->@_first@, (newcnt + 1) * sizeof(_onexit_t));
		if unlikely(!newtab)
			return -1;
		newcnt = malloc_usable_size(newtab) / sizeof(_onexit_t);
		self->@_last@  = (_PVFV *)newtab + (size_t)(self->@_last@ - self->@_first@);
		self->@_end@   = (_PVFV *)newtab + newcnt;
		self->@_first@ = (_PVFV *)newtab;
	}
	*self->@_last@++ = (_PVFV)function;
	return 0;
}

[[crt_dos_only, decl_include("<corecrt_startup.h>")]]
[[requires_function(_initialize_onexit_table, _initterm_e)]]
int _execute_onexit_table([[nullable]] struct _onexit_table_t *self) {
	int result;
	_onexit_t *first = (_onexit_t *)self->@_first@;
	_onexit_t *last  = (_onexit_t *)self->@_last@;
	_initialize_onexit_table(self);
	result = _initterm_e(first, last);
@@pp_if $has_function(free)@@
	free(first);
@@pp_endif@@
	return result;
}


%[insert:function(_crt_atexit = atexit)]
%[insert:function(_crt_at_quick_exit = at_quick_exit)]


[[hidden, crt_dos_only, requires_function(_register_onexit_function)]]
[[decl_include("<corecrt_startup.h>"), impl_include("<corecrt_startup.h>")]]
int __dllonexit(_onexit_t func,
                [[nonnull]] _onexit_t **p_begin,
                [[nonnull]] _onexit_t **p_end) {
	int result;
	struct _onexit_table_t tab;
	tab.@_first@ = (_PVFV *)*p_begin;
	tab.@_last@  = (_PVFV *)*p_end;
	tab.@_end@   = tab.@_last@;
	result = _register_onexit_function(&tab, func);
	*p_begin = (_onexit_t *)tab.@_first@;
	*p_end   = (_onexit_t *)tab.@_last@;
	return result;
}



%{

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

}
