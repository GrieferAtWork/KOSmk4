/* HASH CRC-32:0x1f505103 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_CORECRT_STARTUP_C
#define GUARD_LIBC_AUTO_CORECRT_STARTUP_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/corecrt_startup.h"
#include "../user/malloc.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/sys.syslog.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/crt/dos/corecrt_startup.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST WUNUSED _crt_app_type
NOTHROW(LIBDCALL libc__query_app_type)(void) {
	return (_crt_app_type)1;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") errno_t
NOTHROW_NCX(LIBDCALL libc__configure_narrow_argv)(_crt_argv_mode mode) {
	COMPILER_IMPURE();
	(void)mode;
	return 0;
}
DEFINE_INTERN_ALIAS_P(libc__configure_wide_argv,libc_libc__configure_narrow_argv,,errno_t,NOTHROW_NCX,LIBDCALL,(_crt_argv_mode mode),(mode));
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") int
NOTHROW_NCX(LIBDCALL libc__initialize_narrow_environment)(void) {
	COMPILER_IMPURE();
	return 0;
}
DEFINE_INTERN_ALIAS_P(libc__initialize_wide_environment,libc_libc__initialize_narrow_environment,,int,NOTHROW_NCX,LIBDCALL,(void),());
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") ATTR_PURE WUNUSED char **
NOTHROW_NCX(LIBDCALL libc__get_initial_narrow_environment)(void) {
	return *libc___p___initenv();
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") ATTR_PURE WUNUSED __WCHAR16_TYPE__ **
NOTHROW_NCX(LIBDCALL libc__get_initial_wide_environment)(void) {
	return (__WCHAR16_TYPE__ **)*libd___p___winitenv();
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") ATTR_PURE WUNUSED char *
NOTHROW_NCX(LIBDCALL libc__get_narrow_winmain_command_line)(void) {
	return *libc___p__acmdln();
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") ATTR_PURE WUNUSED __WCHAR16_TYPE__ *
NOTHROW_NCX(LIBDCALL libc__get_wide_winmain_command_line)(void) {
	return (__WCHAR16_TYPE__ *)*libc___p__wcmdln();
}
#include <bits/crt/dos/corecrt_startup.h>
#include <asm/os/syslog.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") void
NOTHROW_NCX(LIBDCALL libc__initterm)(_PVFV *start,
                                     _PVFV *end) {
	for (; start < end; ++start) {
		if (*start == NULL)
			continue;

		(void)libc_syslog(__LOG_DEBUG, "[libd] _initterm: call %p\n", *start);

		(**start)();
	}

	(void)libc_syslog(__LOG_DEBUG, "[libd] _initterm: done\n");

}
#include <bits/crt/dos/corecrt_startup.h>
#include <asm/os/syslog.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") int
NOTHROW_NCX(LIBDCALL libc__initterm_e)(_onexit_t *start,
                                       _onexit_t *end) {
	int result = 0;
	for (; start < end; ++start) {
		if (!*start)
			continue;

		(void)libc_syslog(__LOG_DEBUG, "[libd] _initterm_e: call %p\n", *start);

		result = (**start)();
		if (result != 0) {

			(void)libc_syslog(__LOG_DEBUG, "[libd] _initterm_e: call %p failed -> %d\n", *start, result);

			break;
		}
	}

	(void)libc_syslog(__LOG_DEBUG, "[libd] _initterm_e: done\n");

	return result;
}
#include <bits/crt/dos/corecrt_startup.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") int
NOTHROW_NCX(LIBDCALL libc__initialize_onexit_table)(struct _onexit_table_t *self) {
	if unlikely(!self)
		return -1;
	libc_bzero(self, sizeof(*self));
	return 0;
}
#include <hybrid/typecore.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") int
NOTHROW_NCX(LIBDCALL libc__register_onexit_function)(struct _onexit_table_t *self,
                                                     _onexit_t function) {
	if unlikely(!self)
		return -1;
	if (self->_last >= self->_end) {
		_onexit_t *newtab;
		size_t newcnt;
		newcnt = (size_t)(self->_last - self->_first) + 1;
		newtab = (_onexit_t *)libc_realloc(self->_first, (newcnt + 1) * sizeof(_onexit_t));
		if unlikely(!newtab)
			return -1;
		newcnt = libc_malloc_usable_size(newtab) / sizeof(_onexit_t);
		self->_last  = (_PVFV *)newtab + (size_t)(self->_last - self->_first);
		self->_end   = (_PVFV *)newtab + newcnt;
		self->_first = (_PVFV *)newtab;
	}
	*self->_last++ = (_PVFV)function;
	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") int
NOTHROW_NCX(LIBDCALL libc__execute_onexit_table)(struct _onexit_table_t *self) {
	int result;
	_onexit_t *first = (_onexit_t *)self->_first;
	_onexit_t *last  = (_onexit_t *)self->_last;
	(void)libc__initialize_onexit_table(self);
	result = libc__initterm_e(first, last);

	libc_free(first);

	return result;
}
#include <bits/crt/dos/corecrt_startup.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") ATTR_INOUT(2) ATTR_INOUT(3) int
NOTHROW_NCX(LIBDCALL libc___dllonexit)(_onexit_t func,
                                       _onexit_t **p_begin,
                                       _onexit_t **p_end) {
	int result;
	struct _onexit_table_t tab;
	tab._first = (_PVFV *)*p_begin;
	tab._last  = (_PVFV *)*p_end;
	tab._end   = tab._last;
	result = libc__register_onexit_function(&tab, func);
	*p_begin = (_onexit_t *)tab._first;
	*p_end   = (_onexit_t *)tab._last;
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_query_app_type,libc__query_app_type,ATTR_CONST WUNUSED,_crt_app_type,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_configure_narrow_argv,libc__configure_narrow_argv,,errno_t,NOTHROW_NCX,LIBDCALL,(_crt_argv_mode mode),(mode));
DEFINE_PUBLIC_ALIAS_P(_configure_wide_argv,libc__configure_wide_argv,,errno_t,NOTHROW_NCX,LIBDCALL,(_crt_argv_mode mode),(mode));
DEFINE_PUBLIC_ALIAS_P(_initialize_narrow_environment,libc__initialize_narrow_environment,,int,NOTHROW_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_initialize_wide_environment,libc__initialize_wide_environment,,int,NOTHROW_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_get_initial_narrow_environment,libc__get_initial_narrow_environment,ATTR_PURE WUNUSED,char **,NOTHROW_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_get_initial_wide_environment,libc__get_initial_wide_environment,ATTR_PURE WUNUSED,__WCHAR16_TYPE__ **,NOTHROW_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_get_narrow_winmain_command_line,libc__get_narrow_winmain_command_line,ATTR_PURE WUNUSED,char *,NOTHROW_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_get_wide_winmain_command_line,libc__get_wide_winmain_command_line,ATTR_PURE WUNUSED,__WCHAR16_TYPE__ *,NOTHROW_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(_initterm,libc__initterm,,NOTHROW_NCX,LIBDCALL,(_PVFV *start, _PVFV *end),(start,end));
DEFINE_PUBLIC_ALIAS_P(_initterm_e,libc__initterm_e,,int,NOTHROW_NCX,LIBDCALL,(_onexit_t *start, _onexit_t *end),(start,end));
DEFINE_PUBLIC_ALIAS_P(_initialize_onexit_table,libc__initialize_onexit_table,,int,NOTHROW_NCX,LIBDCALL,(struct _onexit_table_t *self),(self));
DEFINE_PUBLIC_ALIAS_P(_register_onexit_function,libc__register_onexit_function,,int,NOTHROW_NCX,LIBDCALL,(struct _onexit_table_t *self, _onexit_t function),(self,function));
DEFINE_PUBLIC_ALIAS_P(_execute_onexit_table,libc__execute_onexit_table,,int,NOTHROW_NCX,LIBDCALL,(struct _onexit_table_t *self),(self));
DEFINE_PUBLIC_ALIAS_P(__dllonexit,libc___dllonexit,ATTR_INOUT(2) ATTR_INOUT(3),int,NOTHROW_NCX,LIBDCALL,(_onexit_t func, _onexit_t **p_begin, _onexit_t **p_end),(func,p_begin,p_end));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CORECRT_STARTUP_C */
