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
#ifndef GUARD_LIBC_USER_CORECRT_STARTUP_C
#define GUARD_LIBC_USER_CORECRT_STARTUP_C 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <kos/exec/idata.h>
#include <kos/exec/peb.h>

#include <dlfcn.h>
#include <errno.h>
#include <format-printer.h>
#include <inttypes.h>
#include <math.h>
#include <pthread.h>
#include <stddef.h>
#include <uchar.h>

#include <libcmdline/api.h>
#include <libcmdline/encode.h>

#include "../libc/dl.h"
#include "../libc/globals.h"
#include "corecrt_startup.h"

DECL_BEGIN

/*[[[head:libc__seh_filter_dll,hash:CRC-32=0xa7d4eb05]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") ATTR_INOUT(2) int
NOTHROW_NCX(LIBDCALL libc__seh_filter_dll)(__ULONG32_TYPE__ xno,
                                           struct _EXCEPTION_POINTERS *infp_ptrs)
/*[[[body:libc__seh_filter_dll]]]*/
/*AUTO*/{
	(void)xno;
	(void)infp_ptrs;
	CRT_UNIMPLEMENTEDF("_seh_filter_dll(xno: %" PRIx32 ", infp_ptrs: %p)", xno, infp_ptrs); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc__seh_filter_dll]]]*/

/*[[[head:libc__seh_filter_exe,hash:CRC-32=0x494f67b]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") ATTR_INOUT(2) int
NOTHROW_NCX(LIBDCALL libc__seh_filter_exe)(__ULONG32_TYPE__ xno,
                                           struct _EXCEPTION_POINTERS *infp_ptrs)
/*[[[body:libc__seh_filter_exe]]]*/
/*AUTO*/{
	(void)xno;
	(void)infp_ptrs;
	CRT_UNIMPLEMENTEDF("_seh_filter_exe(xno: %" PRIx32 ", infp_ptrs: %p)", xno, infp_ptrs); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc__seh_filter_exe]]]*/

/*[[[head:libc__set_app_type,hash:CRC-32=0xa24d1202]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") void
NOTHROW_NCX(LIBDCALL libc__set_app_type)(_crt_app_type type)
/*[[[body:libc__set_app_type]]]*/
/*AUTO*/{
	(void)type;
	CRT_UNIMPLEMENTEDF("_set_app_type(type: %x)", type); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__set_app_type]]]*/






/************************************************************************/
/* _setusermatherr()                                                    */
/************************************************************************/
#ifndef __NO_FPU
#ifdef __cplusplus
struct __exception;
#define STRUCT_EXCEPTION struct __exception
#else /* __cplusplus */
struct exception;
#define STRUCT_EXCEPTION struct exception
#endif /* !__cplusplus */

struct _exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};
#define _DOMAIN    1
#define _SING      2
#define _OVERFLOW  3
#define _UNDERFLOW 4
#define _TLOSS     5
#define _PLOSS     6

/* Assert that DOS's `struct _exception' is ABI-compatible with ours (which it should be) */
static_assert(offsetof(struct _exception, type) == offsetof(STRUCT_EXCEPTION, type));
static_assert(offsetafter(struct _exception, type) == offsetafter(STRUCT_EXCEPTION, type));
static_assert(offsetof(struct _exception, name) == offsetof(STRUCT_EXCEPTION, name));
static_assert(offsetafter(struct _exception, name) == offsetafter(STRUCT_EXCEPTION, name));
static_assert(offsetof(struct _exception, arg1) == offsetof(STRUCT_EXCEPTION, arg1));
static_assert(offsetafter(struct _exception, arg1) == offsetafter(STRUCT_EXCEPTION, arg1));
static_assert(offsetof(struct _exception, arg2) == offsetof(STRUCT_EXCEPTION, arg2));
static_assert(offsetafter(struct _exception, arg2) == offsetafter(STRUCT_EXCEPTION, arg2));
static_assert(offsetof(struct _exception, retval) == offsetof(STRUCT_EXCEPTION, retval));
static_assert(offsetafter(struct _exception, retval) == offsetafter(STRUCT_EXCEPTION, retval));
static_assert(_DOMAIN == __MATH_EXCEPT_DOMAIN);
static_assert(_SING == __MATH_EXCEPT_SING);
static_assert(_OVERFLOW == __MATH_EXCEPT_OVERFLOW);
static_assert(_UNDERFLOW == __MATH_EXCEPT_UNDERFLOW);
static_assert(_TLOSS == __MATH_EXCEPT_TLOSS);
static_assert(_PLOSS == __MATH_EXCEPT_PLOSS);

/* If non-NULL, the  currently used `matherr(3)'  handler in  "libc/matherr.c"
 * When `NULL', lazily load the matherr handler via `dlsym(3D)', and fall back
 * to a no-op handler when no override was defined.
 *
 * To facilitate DOS's `__setusermatherr(3)', we simply re-assign this pointer
 * with  another function that  will invoke the  DOS-given math error handler. */
typedef int (LIBKCALL *LPMATHERR)(STRUCT_EXCEPTION *exc);
INTDEF LPMATHERR libc_pdyn_matherr; /* From "libc/matherr.c" */


DEFINE_PUBLIC_ALIAS(__setusermatherr, libc___setusermatherr);
INTERN ATTR_SECTION(".text.crt.dos.application.init") NONNULL((1)) void
NOTHROW_NCX(LIBKCALL libc___setusermatherr)(int (LIBKCALL *fptr)(struct _exception *)) {
	/* We've already asserted  that DOS's `struct _exception'  and
	 * our `STRUCT_EXCEPTION'  are  binary  compatible  (s.a.  the
	 * static asserts above), so  if the calling conventions  also
	 * match, then we can simply cast+assign the function pointer. */
	libc_pdyn_matherr = (LPMATHERR)fptr;
}

#ifndef __LIBDCALL_IS_LIBKCALL
/* When calling conventions don't match, then we need to do some extra
 * work  in order to  set-up a wrapper that  calls DOS's error handler
 * using the proper calling convention. */
INTERN ATTR_SECTION(".bss.crt.dos.application.init")
int (LIBDCALL *libd_usermatherr_fptr)(struct _exception *) = NULL;
INTERN ATTR_SECTION(".text.crt.dos.application.init") int LIBKCALL
libd_usermatherr_wrapper(STRUCT_EXCEPTION *exc) {
	/* Even when calling conventions don't match, we still know that
	 * our `STRUCT_EXCEPTION' matches DOS's `struct _exception',  so
	 * no need to do some extra conversion in here.
	 *
	 * If they didn't match, this compat function could still  be
	 * provided, only that we'd need to do some extra fiddling in
	 * order to achieve ABI compatibility. */
	return (*libd_usermatherr_fptr)((struct _exception *)exc);
}

DEFINE_PUBLIC_ALIAS(DOS$__setusermatherr, libd___setusermatherr);
INTERN ATTR_SECTION(".text.crt.dos.application.init") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd___setusermatherr)(int (LIBDCALL *fptr)(struct _exception *)) {
	/* Assign the function pointer to-be called by the wrapper. */
	libd_usermatherr_fptr = fptr;

	/* Assign the wrapper to-be called as `matherr(3)' handler. */
	libc_pdyn_matherr = &libd_usermatherr_wrapper;
}
#else /* !__LIBDCALL_IS_LIBKCALL */
DEFINE_INTERN_ALIAS(libd___setusermatherr, libc___setusermatherr);
#endif /* __LIBDCALL_IS_LIBKCALL */
#endif /* !__NO_FPU */
/*[[[skip:libd___setusermatherr]]]*/
/*[[[skip:libc___setusermatherr]]]*/



/************************************************************************/
/* _acmdln                                                              */
/************************************************************************/
PRIVATE ATTR_SECTION(".text.crt.dos.application.init") char *LIBCCALL
libc_construct_dos_commandline(void) {
	struct process_peb *peb = &__peb;
	char *result            = NULL;
	void *libcmdline;
	PCMDLINE_ENCODE cmdline_encode;
	libcmdline = dlopen(LIBCMDLINE_LIBRARY_NAME, RTLD_LAZY | RTLD_LOCAL);
	if (!libcmdline)
		return NULL;
	*(void **)&cmdline_encode = dlsym(libcmdline, "cmdline_encode");
	if (cmdline_encode) {
		ssize_t error;
		struct format_aprintf_data printer;
		/* Encode the commandline. */
		format_aprintf_data_init(&printer);
		error = (*cmdline_encode)(&format_aprintf_printer, &printer,
		                          peb->pp_argc, peb->pp_argv);
		if unlikely(error < 0) {
			format_aprintf_data_fini(&printer);
		} else {
			result = format_aprintf_pack(&printer, NULL);
		}
	}
	dlclose(libcmdline);
	return result;
}

#undef _acmdln
DEFINE_PUBLIC_IDATA(_acmdln, libc___p__acmdln, __SIZEOF_POINTER__);
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") char *libc__acmdln = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init")
pthread_once_t libc___p__acmdln_initialized = PTHREAD_ONCE_INIT;
PRIVATE ATTR_SECTION(".text.crt.dos.application.init")
void LIBCCALL libc___p__acmdln_initialize(void) {
	libc__acmdln = libc_construct_dos_commandline();
}

/*[[[head:libc___p__acmdln,hash:CRC-32=0xdc6cc6bf]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") char **
NOTHROW_NCX(LIBDCALL libc___p__acmdln)(void)
/*[[[body:libc___p__acmdln]]]*/
{
	pthread_once(&libc___p__acmdln_initialized,
	             &libc___p__acmdln_initialize);
	return &libc__acmdln;
}
/*[[[end:libc___p__acmdln]]]*/



/************************************************************************/
/* _wcmdln                                                              */
/************************************************************************/
PRIVATE ATTR_SECTION(".text.crt.dos.application.init") char16_t *LIBCCALL
libd_construct_dos_wcommandline(void) {
	char *acmdln = *libc___p__acmdln();
	return acmdln ? convert_mbstoc16(acmdln) : NULL;
}

#undef _wcmdln
#undef DOS$_wcmdln
DEFINE_PUBLIC_IDATA(DOS$_wcmdln, libc___p__wcmdln, __SIZEOF_POINTER__);
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") char16_t *libd__wcmdln = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init")
pthread_once_t libd___p__wcmdln_initialized = PTHREAD_ONCE_INIT;
PRIVATE ATTR_SECTION(".text.crt.dos.application.init")
void LIBCCALL libd___p__wcmdln_initialize(void) {
	libd__wcmdln = libd_construct_dos_wcommandline();
}

/*[[[head:libc___p__wcmdln,hash:CRC-32=0xb0bf62a]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.application.init") __WCHAR16_TYPE__ **
NOTHROW_NCX(LIBDCALL libc___p__wcmdln)(void)
/*[[[body:libc___p__wcmdln]]]*/
{
	pthread_once(&libd___p__wcmdln_initialized,
	             &libd___p__wcmdln_initialize);
	return (__WCHAR16_TYPE__ **)&libd__wcmdln;
}
/*[[[end:libc___p__wcmdln]]]*/

/*[[[start:exports,hash:CRC-32=0x710acc7f]]]*/
DEFINE_PUBLIC_ALIAS_P(_seh_filter_dll,libc__seh_filter_dll,ATTR_INOUT(2),int,NOTHROW_NCX,LIBDCALL,(__ULONG32_TYPE__ xno, struct _EXCEPTION_POINTERS *infp_ptrs),(xno,infp_ptrs));
DEFINE_PUBLIC_ALIAS_P(_seh_filter_exe,libc__seh_filter_exe,ATTR_INOUT(2),int,NOTHROW_NCX,LIBDCALL,(__ULONG32_TYPE__ xno, struct _EXCEPTION_POINTERS *infp_ptrs),(xno,infp_ptrs));
DEFINE_PUBLIC_ALIAS_P_VOID(__set_app_type,libc__set_app_type,,NOTHROW_NCX,LIBDCALL,(_crt_app_type type),(type));
DEFINE_PUBLIC_ALIAS_P_VOID(_set_app_type,libc__set_app_type,,NOTHROW_NCX,LIBDCALL,(_crt_app_type type),(type));
DEFINE_PUBLIC_ALIAS_P(__p__acmdln,libc___p__acmdln,,char **,NOTHROW_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$__p__wcmdln,libc___p__wcmdln,,__WCHAR16_TYPE__ **,NOTHROW_NCX,LIBDCALL,(void),());
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CORECRT_STARTUP_C */
