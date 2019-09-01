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

#include <elf.h>
#include <errno.h>
#include <signal.h>

#include "errno.h"

DECL_BEGIN

/* Per-thread variables FTW! */
INTERN ATTR_THREAD errno_t libc_errno_global = EOK;

INTDEF ATTR_WEAK NOBLOCK ATTR_CONST
ATTR_SECTION(".text.crt.errno_access.__errno_location") errno_t *
NOTHROW(LIBCCALL libc_errno_p)(void) {
	return &libc_errno_global;
}

INTDEF ATTR_WEAK NOBLOCK
ATTR_SECTION(".text.crt.errno_access.geterrno") errno_t
NOTHROW(LIBCCALL libc_geterrno)(void) {
	return libc_errno_global;
}

INTDEF ATTR_WEAK NOBLOCK
ATTR_SECTION(".text.crt.errno_access.seterrno") syscall_slong_t
NOTHROW(__FCALL libc_seterrno)(errno_t value) {
	libc_errno_global = value;
	return -1;
}


#undef _errno
#undef __errno
#undef __errno_location
DEFINE_PUBLIC_ALIAS(_errno, libc_errno_p);
DEFINE_PUBLIC_ALIAS(__errno, libc_errno_p);
DEFINE_PUBLIC_ALIAS(__errno_location, libc_errno_p);
DEFINE_INTERN_ALIAS(libc___errno_location, libc_errno_p);


INTERN ATTR_SECTION(".data.crt.errno.sys_errlist_internal")
char const *sys_errlist_internal[__ECOUNT];

#define E(id, text)                                                                                               \
	PRIVATE ATTR_ALIGNED(1) ATTR_SECTION(".rodata.crt.errno.name." #id) char const errno_name_##id[]       = #id; \
	PRIVATE ATTR_ALIGNED(1) ATTR_SECTION(".rodata.crt.errno.message." #id) char const errno_message_##id[] = text;
E(EOK, "Success")
#include "errno_errlist.def"
#undef E



DEFINE_PUBLIC_WEAK_ALIAS(strerror_s, libc_strerror_s);

INTERN WUNUSED ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.errno.strerror_s") char const *
NOTHROW(LIBCCALL libc_strerror_s)(int errnum) {
	if ((unsigned int)errnum >= __ECOUNT)
		return NULL;
	return libc___sys_errlist()[(unsigned int)errnum];
}

DEFINE_PUBLIC_WEAK_ALIAS(strerrorname_s, libc_strerrorname_s);

INTERN WUNUSED ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.errno.strerrorname_s") char const *
NOTHROW(LIBCCALL libc_strerrorname_s)(int errnum) {
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


PRIVATE ATTR_ALIGNED(1)
ATTR_SECTION(".data.crt.errno._sys_nerr")
int libc__sys_nerr = __ECOUNT;

INTERN ATTR_CONST WUNUSED ATTR_RETNONNULL int *
ATTR_SECTION(".text.crt.errno.__sys_nerr")
NOTHROW(LIBCCALL libc___sys_nerr)(void) {
	return &libc__sys_nerr;
}
DEFINE_PUBLIC_ALIAS(__sys_nerr, libc___sys_nerr);



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



INTERN ATTR_SECTION(".text.crt.dos.errno_access.__errno_location")
NOBLOCK ATTR_CONST errno_t *NOTHROW(LIBDCALL libd_errno_p)(void) {
	/* TODO: Dynamically convert */
	return libc_errno_p();
}

INTERN ATTR_SECTION(".text.crt.dos.errno_access.geterrno")
NOBLOCK /*dos*/errno_t NOTHROW(LIBDCALL libd_geterrno)(void) {
	return libd_errno_kos2dos(libc_geterrno());
}

INTERN ATTR_SECTION(".text.crt.dos.errno_access.seterrno")
NOBLOCK syscall_slong_t NOTHROW(__FCALL libd_seterrno)(/*dos*/errno_t value) {
	return libc_seterrno(libd_errno_dos2kos(value));
}

INTERN ATTR_SECTION(".text.crt.dos.errno_access.errno_kos2dos")
NOBLOCK /*dos*/errno_t NOTHROW(__FCALL libd_errno_kos2dos)(/*kos*/errno_t value) {
	/* TODO */
	return value;
}

INTERN ATTR_SECTION(".text.crt.dos.errno_access.errno_dos2kos")
NOBLOCK /*kos*/errno_t NOTHROW(__FCALL libd_errno_dos2kos)(/*dos*/errno_t value) {
	/* TODO */
	return value;
}



DECL_END

#endif /* !GUARD_LIBC_LIBC_ERRNO_C */
