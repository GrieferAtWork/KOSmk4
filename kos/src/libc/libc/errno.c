/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ERRNO_C
#define GUARD_LIBC_LIBC_ERRNO_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <parts/errno.h>
#include <parts/dos/errno.h>
#include <parts/cyg/errno.h>

#include <elf.h>
#include <errno.h>
#include <signal.h>
#include <hybrid/host.h>

#include "errno.h"

DECL_BEGIN

#define LIBC_ERRNO_KIND_KOS 0
#define LIBC_ERRNO_KIND_DOS 1
#define LIBC_ERRNO_KIND_NT  2
#define LIBC_ERRNO_KIND_CYG 3

struct libc_errno_desc {
	errno_t      ed_value; /* Errno value */
	unsigned int ed_kind;  /* Errno kind (one of `LIBC_ERRNO_KIND_*') */
};

/* Per-thread variables FTW! */
INTERN ATTR_THREAD struct libc_errno_desc libc_errno_global = { EOK, LIBC_ERRNO_KIND_KOS };

#undef _errno
#undef __errno
#undef __errno_location
DEFINE_PUBLIC_ALIAS(_errno, libc_errno_p);
DEFINE_PUBLIC_ALIAS(__errno, libc_errno_p);
DEFINE_PUBLIC_ALIAS(__errno_location, libc_errno_p);
DEFINE_INTERN_ALIAS(libc__errno, libc_errno_p);
DEFINE_INTERN_ALIAS(libc___errno, libc_errno_p);
DEFINE_INTERN_ALIAS(libc___errno_location, libc_errno_p);
INTERN ATTR_CONST ATTR_SECTION(".text.crt.errno_access.__errno_location")
NOBLOCK errno_t *NOTHROW(LIBCCALL libc_errno_p)(void) {
	struct libc_errno_desc *result;
	result = &libc_errno_global;
	if unlikely(result->ed_kind != LIBC_ERRNO_KIND_KOS) {
		if (result->ed_kind == LIBC_ERRNO_KIND_DOS)
			result->ed_value = libd_errno_dos2kos(result->ed_value);
		else if (result->ed_kind == LIBC_ERRNO_KIND_NT) {
			result->ed_value = libd_errno_nt2kos(result->ed_value);
		} else {
			result->ed_value = libd_errno_cyg2kos(result->ed_value);
		}
		result->ed_kind = LIBC_ERRNO_KIND_KOS;
	}
	return &result->ed_value;
}

DEFINE_PUBLIC_ALIAS(__get_errno_fast, libc_geterrno);
DEFINE_INTERN_ALIAS(libc___get_errno_fast, libc_geterrno);
INTERN ATTR_SECTION(".text.crt.errno_access.geterrno")
NOBLOCK errno_t NOTHROW(LIBCCALL libc_geterrno)(void) {
	return libc_errno_global.ed_value;
}

DEFINE_PUBLIC_ALIAS(__get_errno, libc_geterrno_safe);
DEFINE_INTERN_ALIAS(libc___get_errno, libc_geterrno);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.geterrno_safe")
NOBLOCK errno_t NOTHROW(LIBCCALL libc_geterrno_safe)(void) {
	return *libc_errno_p();
}

#ifndef __NO_ATTR_FASTCALL
DEFINE_PUBLIC_ALIAS(__set_errno, libc_seterrno_compat);
INTERN ATTR_SECTION(".text.crt.errno_access.seterrno_compat")
NOBLOCK syscall_slong_t NOTHROW(LIBCCALL libc_seterrno_compat)(errno_t value) {
	return libc_seterrno(value);
}
DEFINE_PUBLIC_ALIAS(__set_errno_f, libc_seterrno);
#else /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(__set_errno, libc_seterrno);
#endif /* !__i386__ || __x86_64__ */
INTERN ATTR_SECTION(".text.crt.errno_access.seterrno")
NOBLOCK syscall_slong_t NOTHROW(__FCALL libc_seterrno)(errno_t value) {
	struct libc_errno_desc *d;
	d = &libc_errno_global;
	d->ed_value = value;
	d->ed_kind  = LIBC_ERRNO_KIND_KOS;
	return -1;
}



INTERN ATTR_SECTION(".data.crt.errno.sys_errlist_internal")
char const *sys_errlist_internal[__ECOUNT];

#define E(id, text)                                                                                               \
	PRIVATE ATTR_ALIGNED(1) ATTR_SECTION(".rodata.crt.errno.name." #id) char const errno_name_##id[]       = #id; \
	PRIVATE ATTR_ALIGNED(1) ATTR_SECTION(".rodata.crt.errno.message." #id) char const errno_message_##id[] = text;
E(EOK, "Success")
#include "errno_errlist.def"
#undef E



DEFINE_PUBLIC_ALIAS(strerror_s, libc_strerror_s);
INTERN WUNUSED ATTR_CONST ATTR_SECTION(".text.crt.errno.strerror_s")
NOBLOCK char const *NOTHROW(LIBCCALL libc_strerror_s)(int errnum) {
	if ((unsigned int)errnum >= __ECOUNT)
		return NULL;
	return libc___sys_errlist()[(unsigned int)errnum];
}

DEFINE_PUBLIC_ALIAS(strerrorname_s, libc_strerrorname_s);
INTERN WUNUSED ATTR_CONST ATTR_SECTION(".text.crt.errno.strerrorname_s")
NOBLOCK char const *NOTHROW(LIBCCALL libc_strerrorname_s)(int errnum) {
	char const *result;
	switch (errnum) {
#define E(id, message) \
	case id: result = errno_name_##id; break;
		E(EOK, "Success")
#include "errno_errlist.def"
#undef E
	default: result = NULL; break;
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(DOS$strerror_s, libd_strerror_s);
INTERN WUNUSED ATTR_CONST ATTR_SECTION(".text.crt.dos.errno.strerror_s")
NOBLOCK char const *NOTHROW(LIBDCALL libd_strerror_s)(int errnum) {
	return libc_strerror_s(libd_errno_dos2kos(errnum));
}

DEFINE_PUBLIC_ALIAS(DOS$strerrorname_s, libd_strerrorname_s);
INTERN WUNUSED ATTR_CONST ATTR_SECTION(".text.crt.dos.errno.strerrorname_s")
NOBLOCK char const *NOTHROW(LIBDCALL libd_strerrorname_s)(int errnum) {
	return libc_strerrorname_s(libd_errno_dos2kos(errnum));
}




INTERN ATTR_CONST WUNUSED ATTR_RETNONNULL
ATTR_SECTION(".text.crt.errno.__sys_errlist") char const *const *
NOTHROW(LIBCCALL libc___sys_errlist)(void) {
	if (!sys_errlist_internal[EOK]) {
#define E(id, text) \
		sys_errlist_internal[id] = (char *)errno_message_##id;
#include "errno_errlist.def"
		COMPILER_WRITE_BARRIER();
		E(EOK, "Success")
		COMPILER_WRITE_BARRIER();
#undef E
	}
	return sys_errlist_internal;
}
DEFINE_PUBLIC_ALIAS(__sys_errlist, libc___sys_errlist);


PRIVATE ATTR_SECTION(".data.crt.errno._sys_nerr") int libc__sys_nerr = __ECOUNT;
DEFINE_PUBLIC_ALIAS(__sys_nerr, libc___sys_nerr);
INTERN ATTR_CONST WUNUSED ATTR_RETNONNULL ATTR_SECTION(".text.crt.errno.__sys_nerr")
NOBLOCK int *NOTHROW(LIBCCALL libc___sys_nerr)(void) {
	return &libc__sys_nerr;
}



PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGHUP[]    = "SIGHUP";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGINT[]    = "SIGINT";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGQUIT[]   = "SIGQUIT";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGILL[]    = "SIGILL";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGTRAP[]   = "SIGTRAP";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGABRT[]   = "SIGABRT";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGIOT[]    = "SIGIOT";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGBUS[]    = "SIGBUS";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGFPE[]    = "SIGFPE";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGKILL[]   = "SIGKILL";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGUSR1[]   = "SIGUSR1";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGSEGV[]   = "SIGSEGV";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGUSR2[]   = "SIGUSR2";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGPIPE[]   = "SIGPIPE";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGALRM[]   = "SIGALRM";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGTERM[]   = "SIGTERM";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGSTKFLT[] = "SIGSTKFLT";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGCHLD[]   = "SIGCHLD";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGCONT[]   = "SIGCONT";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGSTOP[]   = "SIGSTOP";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGTSTP[]   = "SIGTSTP";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGTTIN[]   = "SIGTTIN";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGTTOU[]   = "SIGTTOU";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGURG[]    = "SIGURG";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGXCPU[]   = "SIGXCPU";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGXFSZ[]   = "SIGXFSZ";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGVTALRM[] = "SIGVTALRM";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGPROF[]   = "SIGPROF";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGWINCH[]  = "SIGWINCH";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGIO[]     = "SIGIO";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGPWR[]    = "SIGPWR";
PRIVATE ATTR_SECTION(".rodata.crt.errno.sys_siglist_names") char const name_SIGSYS[] = "SIGSYS";
PRIVATE ATTR_SECTION(".bss.crt.errno.sys_siglist") char const *libc_sys_siglist[NSIG] = { NULL };

INTERN ATTR_CONST WUNUSED ATTR_RETNONNULL char const *const *
ATTR_SECTION(".text.crt.errno.__p_sys_siglist")
NOTHROW_NCX(libc___p_sys_siglist)(void) {
	char const **result = libc_sys_siglist;
	if (!result[__SIGSYS]) {
		result[SIGHUP]    = name_SIGHUP;
		result[SIGINT]    = name_SIGINT;
		result[SIGQUIT]   = name_SIGQUIT;
		result[SIGILL]    = name_SIGILL;
		result[SIGTRAP]   = name_SIGTRAP;
		result[SIGABRT]   = name_SIGABRT;
		result[SIGIOT]    = name_SIGIOT;
		result[SIGBUS]    = name_SIGBUS;
		result[SIGFPE]    = name_SIGFPE;
		result[SIGKILL]   = name_SIGKILL;
		result[SIGUSR1]   = name_SIGUSR1;
		result[SIGSEGV]   = name_SIGSEGV;
		result[SIGUSR2]   = name_SIGUSR2;
		result[SIGPIPE]   = name_SIGPIPE;
		result[SIGALRM]   = name_SIGALRM;
		result[SIGTERM]   = name_SIGTERM;
		result[SIGSTKFLT] = name_SIGSTKFLT;
		result[SIGCHLD]   = name_SIGCHLD;
		result[SIGCONT]   = name_SIGCONT;
		result[SIGSTOP]   = name_SIGSTOP;
		result[SIGTSTP]   = name_SIGTSTP;
		result[SIGTTIN]   = name_SIGTTIN;
		result[SIGTTOU]   = name_SIGTTOU;
		result[SIGURG]    = name_SIGURG;
		result[SIGXCPU]   = name_SIGXCPU;
		result[SIGXFSZ]   = name_SIGXFSZ;
		result[SIGVTALRM] = name_SIGVTALRM;
		result[SIGPROF]   = name_SIGPROF;
		result[SIGWINCH]  = name_SIGWINCH;
		result[SIGIO]     = name_SIGIO;
		result[SIGPWR]    = name_SIGPWR;
		COMPILER_WRITE_BARRIER();
		result[SIGSYS] = name_SIGSYS;
		COMPILER_WRITE_BARRIER();
	}
	return result;
}

/************************************************************************/
/* DOS/NT                                                               */
/************************************************************************/

DEFINE_PUBLIC_ALIAS(DOS$_errno, libd_errno_p);
DEFINE_INTERN_ALIAS(libd__errno, libd_errno_p);
INTERN ATTR_SECTION(".text.crt.dos.errno_access._errno")
NOBLOCK ATTR_CONST /*dos*/ errno_t *NOTHROW(LIBDCALL libd_errno_p)(void) {
	struct libc_errno_desc *result;
	result = &libc_errno_global;
	if (result->ed_kind != LIBC_ERRNO_KIND_DOS) {
		if (result->ed_kind == LIBC_ERRNO_KIND_KOS)
			result->ed_value = libd_errno_kos2dos(result->ed_value);
		else if (result->ed_kind == LIBC_ERRNO_KIND_NT)
			result->ed_value = libd_errno_nt2dos(result->ed_value);
		else {
			result->ed_value = libd_errno_cyg2dos(result->ed_value);
		}
		result->ed_kind = LIBC_ERRNO_KIND_DOS;
	}
	return &result->ed_value;
}

DEFINE_PUBLIC_ALIAS(__get_doserrno, libd_geterrno);
DEFINE_INTERN_ALIAS(libc___get_doserrno, libd_geterrno);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.__get_doserrno")
NOBLOCK /*dos*/ errno_t NOTHROW(LIBDCALL libd_geterrno)(void) {
	return *libd_errno_p();
}

DEFINE_PUBLIC_ALIAS(_dosmaperr, libd_seterrno);
DEFINE_PUBLIC_ALIAS(__set_doserrno, libd_seterrno);
DEFINE_INTERN_ALIAS(libc__dosmaperr, libd_seterrno);
DEFINE_INTERN_ALIAS(libc___set_doserrno, libd_seterrno);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.__set_doserrno")
NOBLOCK syscall_slong_t NOTHROW(LIBDCALL libd_seterrno)(/*dos*/ errno_t value) {
	struct libc_errno_desc *d;
	d = &libc_errno_global;
	d->ed_value = value;
	d->ed_kind  = LIBC_ERRNO_KIND_DOS;
	return -1;
}

DEFINE_PUBLIC_ALIAS(__doserrno, libd_nterrno_p);
DEFINE_INTERN_ALIAS(libc___doserrno, libd_nterrno_p);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.__doserrno")
NOBLOCK ATTR_CONST /*nt*/ errno_t *NOTHROW(LIBDCALL libd_nterrno_p)(void) {
	struct libc_errno_desc *result;
	result = &libc_errno_global;
	if (result->ed_kind != LIBC_ERRNO_KIND_NT) {
		if (result->ed_kind == LIBC_ERRNO_KIND_KOS)
			result->ed_value = libd_errno_kos2nt(result->ed_value);
		else if (result->ed_kind == LIBC_ERRNO_KIND_DOS)
			result->ed_value = libd_errno_dos2nt(result->ed_value);
		else {
			result->ed_value = libd_errno_cyg2nt(result->ed_value);
		}
		result->ed_kind = LIBC_ERRNO_KIND_NT;
	}
	return &result->ed_value;
}

DEFINE_PUBLIC_ALIAS(__get_nterrno, libd_getnterrno);
DEFINE_INTERN_ALIAS(libc___get_nterrno, libd_setnterrno);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.__get_nterrno")
NOBLOCK /*nt*/ errno_t NOTHROW(LIBDCALL libd_getnterrno)(void) {
	return *libd_nterrno_p();
}

DEFINE_PUBLIC_ALIAS(__set_nterrno, libd_setnterrno);
DEFINE_INTERN_ALIAS(libc___set_nterrno, libd_setnterrno);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.__set_nterrno")
NOBLOCK syscall_slong_t NOTHROW(LIBDCALL libd_setnterrno)(/*nt*/ errno_t value) {
	struct libc_errno_desc *d;
	d = &libc_errno_global;
	d->ed_value = value;
	d->ed_kind  = LIBC_ERRNO_KIND_NT;
	return -1;
}


DEFINE_PUBLIC_ALIAS(_get_errno, libd__get_errno);
DEFINE_INTERN_ALIAS(libc__get_errno, libd__get_errno);
INTERN ATTR_SECTION(".text.crt.dos.errno_access._get_errno")
NOBLOCK errno_t NOTHROW(LIBDCALL libd__get_errno)(errno_t *value) {
	if (!value)
		return __DOS_EINVAL;
	*value = libd_geterrno();
	return 0;
}

DEFINE_PUBLIC_ALIAS(_set_errno, libd__set_errno);
DEFINE_INTERN_ALIAS(libc__set_errno, libd__set_errno);
INTERN ATTR_SECTION(".text.crt.dos.errno_access._set_errno")
NOBLOCK errno_t NOTHROW(LIBDCALL libd__set_errno)(errno_t value) {
	libd_seterrno(value);
	return 0;
}

DEFINE_PUBLIC_ALIAS(_get_doserrno, libd__get_doserrno);
DEFINE_INTERN_ALIAS(libc__get_doserrno, libd__get_doserrno);
INTERN ATTR_SECTION(".text.crt.dos.errno_access._get_doserrno")
NOBLOCK errno_t NOTHROW(LIBDCALL libd__get_doserrno)(errno_t *value) {
	if (!value)
		return __DOS_EINVAL;
	*value = libd_getnterrno();
	return 0;
}

DEFINE_PUBLIC_ALIAS(_set_doserrno, libd__set_doserrno);
DEFINE_INTERN_ALIAS(libc__set_doserrno, libd__set_doserrno);
INTERN ATTR_SECTION(".text.crt.dos.errno_access._set_doserrno")
NOBLOCK errno_t NOTHROW(LIBDCALL libd__set_doserrno)(errno_t value) {
	libd_setnterrno(value);
	return 0;
}




/************************************************************************/
/* CYGWIN                                                               */
/************************************************************************/

DEFINE_PUBLIC_ALIAS(DOS$__errno, libd_cygerrno_p);
DEFINE_INTERN_ALIAS(libd___errno, libd_cygerrno_p);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.__errno")
NOBLOCK ATTR_CONST /*cyg*/ errno_t *NOTHROW(LIBDCALL libd_cygerrno_p)(void) {
	struct libc_errno_desc *result;
	result = &libc_errno_global;
	if (result->ed_kind != LIBC_ERRNO_KIND_CYG) {
		if (result->ed_kind == LIBC_ERRNO_KIND_KOS)
			result->ed_value = libd_errno_kos2cyg(result->ed_value);
		else if (result->ed_kind == LIBC_ERRNO_KIND_DOS)
			result->ed_value = libd_errno_dos2cyg(result->ed_value);
		else {
			result->ed_value = libd_errno_nt2cyg(result->ed_value);
		}
		result->ed_kind = LIBC_ERRNO_KIND_CYG;
	}
	return &result->ed_value;
}

DEFINE_PUBLIC_ALIAS(__get_cygerrno, libd_getcygerrno);
DEFINE_INTERN_ALIAS(libc___get_cygerrno, libd_getcygerrno);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.__get_cygerrno")
NOBLOCK /*cyg*/ errno_t NOTHROW(LIBDCALL libd_getcygerrno)(void) {
	return *libd_cygerrno_p();
}

DEFINE_PUBLIC_ALIAS(__set_cygerrno, libd_setcygerrno);
DEFINE_INTERN_ALIAS(libc___set_cygerrno, libd_setcygerrno);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.__set_cygerrno")
NOBLOCK syscall_slong_t NOTHROW(LIBDCALL libd_setcygerrno)(/*cyg*/ errno_t value) {
	struct libc_errno_desc *d;
	d = &libc_errno_global;
	d->ed_value = value;
	d->ed_kind  = LIBC_ERRNO_KIND_CYG;
	return -1;
}

DECL_END

#endif /* !GUARD_LIBC_LIBC_ERRNO_C */
