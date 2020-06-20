/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
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
NOBLOCK ATTR_PURE errno_t NOTHROW(LIBCCALL libc_geterrno)(void) {
	return libc_errno_global.ed_value;
}

DEFINE_PUBLIC_ALIAS(__get_errno, libc_geterrno_safe);
DEFINE_INTERN_ALIAS(libc___get_errno, libc_geterrno);
INTERN ATTR_SECTION(".text.crt.dos.errno_access.geterrno_safe")
NOBLOCK ATTR_PURE errno_t NOTHROW(LIBCCALL libc_geterrno_safe)(void) {
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
NOBLOCK ATTR_PURE /*dos*/ errno_t NOTHROW(LIBDCALL libd_geterrno)(void) {
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
INTERN ATTR_CONST ATTR_SECTION(".text.crt.dos.errno_access.__doserrno")
NOBLOCK /*nt*/ errno_t *NOTHROW(LIBDCALL libd_nterrno_p)(void) {
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
NOBLOCK ATTR_PURE /*nt*/ errno_t NOTHROW(LIBDCALL libd_getnterrno)(void) {
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
NOBLOCK ATTR_PURE /*cyg*/ errno_t NOTHROW(LIBDCALL libd_getcygerrno)(void) {
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
