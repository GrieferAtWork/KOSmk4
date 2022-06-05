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
#ifndef GUARD_LIBC_LIBC_ERRNO_C
#define GUARD_LIBC_LIBC_ERRNO_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <hybrid/host.h>

#include <elf.h>
#include <errno.h>
#include <signal.h>

#include "errno.h"
#include "tls.h"

DECL_BEGIN

#undef __errno
#undef __errno_location
DEFINE_PUBLIC_ALIAS(__errno, libc_errno_p);
DEFINE_PUBLIC_ALIAS(__errno_location, libc_errno_p);
DEFINE_INTERN_ALIAS(libc___errno, libc_errno_p);
DEFINE_INTERN_ALIAS(libc___errno_location, libc_errno_p);
INTERN NOBLOCK ATTR_CONST ATTR_SECTION(".text.crt.errno_access.core") errno_t *
NOTHROW(LIBCCALL libc_errno_p)(void) {
	struct pthread *me = &current;
	if unlikely(me->pt_errno_kind != LIBC_ERRNO_KIND_KOS) {
		if (me->pt_errno_kind == LIBC_ERRNO_KIND_DOS) {
			me->pt_errno_value = libd_errno_dos2kos(me->pt_errno_value);
		} else if (me->pt_errno_kind == LIBC_ERRNO_KIND_NT) {
			me->pt_errno_value = libd_errno_nt2kos(me->pt_errno_value);
		} else {
			me->pt_errno_value = libd_errno_cyg2kos(me->pt_errno_value);
		}
		me->pt_errno_kind = LIBC_ERRNO_KIND_KOS;
	}
	return &me->pt_errno_value;
}

DEFINE_PUBLIC_ALIAS(__get_errno_fast, libc_geterrno);
DEFINE_INTERN_ALIAS(libc___get_errno_fast, libc_geterrno);
INTERN NOBLOCK ATTR_PURE ATTR_SECTION(".text.crt.errno_access.core") errno_t
NOTHROW(LIBCCALL libc_geterrno)(void) {
	return current.pt_errno_value;
}

DEFINE_PUBLIC_ALIAS(__get_errno, libc_geterrno_safe);
DEFINE_INTERN_ALIAS(libc___get_errno, libc_geterrno);
INTERN NOBLOCK ATTR_PURE ATTR_SECTION(".text.crt.errno_access.core") errno_t
NOTHROW(LIBCCALL libc_geterrno_safe)(void) {
	return *libc_errno_p();
}

#ifndef __NO_ATTR_FASTCALL
DEFINE_PUBLIC_ALIAS(__set_errno, libc_seterrno_compat);
INTERN NOBLOCK ATTR_SECTION(".text.crt.errno_access.core") syscall_slong_t
NOTHROW(LIBCCALL libc_seterrno_compat)(errno_t value) {
	return libc_seterrno(value);
}
DEFINE_PUBLIC_ALIAS(__set_errno_f, libc_seterrno);
#else /* !__NO_ATTR_FASTCALL */
DEFINE_PUBLIC_ALIAS(__set_errno, libc_seterrno);
#endif /* __NO_ATTR_FASTCALL */
INTERN NOBLOCK ATTR_SECTION(".text.crt.errno_access.core") syscall_slong_t
NOTHROW(__FCALL libc_seterrno)(errno_t value) {
	struct pthread *me = &current;
	me->pt_errno_value = value;
	me->pt_errno_kind  = LIBC_ERRNO_KIND_KOS;
	return -1;
}

INTERN NOBLOCK ATTR_SECTION(".text.crt.errno_access.core") syscall_slong_t
NOTHROW(__FCALL libc_seterrno_neg)(errno_t value) {
	struct pthread *me = &current;
	me->pt_errno_value = -value;
	me->pt_errno_kind  = LIBC_ERRNO_KIND_KOS;
	return -1;
}


/************************************************************************/
/* DOS/NT                                                               */
/************************************************************************/

DEFINE_PUBLIC_ALIAS(__doserrno_location, libd_errno_p);
DEFINE_PUBLIC_ALIAS(DOS$_errno, libd_errno_p);
DEFINE_INTERN_ALIAS(libd__errno, libd_errno_p);
INTERN NOBLOCK ATTR_CONST ATTR_SECTION(".text.crt.dos.errno_access") /*dos*/ errno_t *
NOTHROW(LIBDCALL libd_errno_p)(void) {
	struct pthread *me = &current;
	if (me->pt_errno_kind != LIBC_ERRNO_KIND_DOS) {
		if (me->pt_errno_kind == LIBC_ERRNO_KIND_KOS) {
			me->pt_errno_value = libd_errno_kos2dos(me->pt_errno_value);
		} else if (me->pt_errno_kind == LIBC_ERRNO_KIND_NT) {
			me->pt_errno_value = libd_errno_nt2dos(me->pt_errno_value);
		} else {
			me->pt_errno_value = libd_errno_cyg2dos(me->pt_errno_value);
		}
		me->pt_errno_kind = LIBC_ERRNO_KIND_DOS;
	}
	return &me->pt_errno_value;
}

DEFINE_PUBLIC_ALIAS(__get_doserrno, libd_geterrno);
DEFINE_INTERN_ALIAS(libc___get_doserrno, libd_geterrno);
INTERN NOBLOCK ATTR_PURE ATTR_SECTION(".text.crt.dos.errno_access") /*dos*/ errno_t
NOTHROW(LIBDCALL libd_geterrno)(void) {
	return *libd_errno_p();
}

DEFINE_PUBLIC_ALIAS(_dosmaperr, libd_seterrno);
DEFINE_PUBLIC_ALIAS(__set_doserrno, libd_seterrno);
DEFINE_INTERN_ALIAS(libc__dosmaperr, libd_seterrno);
DEFINE_INTERN_ALIAS(libc___set_doserrno, libd_seterrno);
INTERN NOBLOCK ATTR_SECTION(".text.crt.dos.errno_access") syscall_slong_t
NOTHROW(LIBDCALL libd_seterrno)(/*dos*/ errno_t value) {
	struct pthread *me = &current;
	me->pt_errno_value = value;
	me->pt_errno_kind  = LIBC_ERRNO_KIND_DOS;
	return -1;
}

DEFINE_PUBLIC_ALIAS(__nterrno_location, libd_nterrno_p);
DEFINE_PUBLIC_ALIAS(__doserrno, libd_nterrno_p);
DEFINE_INTERN_ALIAS(libc___doserrno, libd_nterrno_p);
INTERN NOBLOCK ATTR_CONST ATTR_SECTION(".text.crt.dos.errno_access") /*nt*/ errno_t *
NOTHROW(LIBDCALL libd_nterrno_p)(void) {
	struct pthread *me = &current;
	if (me->pt_errno_kind != LIBC_ERRNO_KIND_NT) {
		if (me->pt_errno_kind == LIBC_ERRNO_KIND_KOS) {
			me->pt_errno_value = libd_errno_kos2nt(me->pt_errno_value);
		} else if (me->pt_errno_kind == LIBC_ERRNO_KIND_DOS) {
			me->pt_errno_value = libd_errno_dos2nt(me->pt_errno_value);
		} else {
			me->pt_errno_value = libd_errno_cyg2nt(me->pt_errno_value);
		}
		me->pt_errno_kind = LIBC_ERRNO_KIND_NT;
	}
	return &me->pt_errno_value;
}

DEFINE_PUBLIC_ALIAS(__get_nterrno, libd_getnterrno);
DEFINE_INTERN_ALIAS(libc___get_nterrno, libd_setnterrno);
INTERN NOBLOCK ATTR_PURE ATTR_SECTION(".text.crt.dos.errno_access") /*nt*/ errno_t
NOTHROW(LIBDCALL libd_getnterrno)(void) {
	return *libd_nterrno_p();
}

DEFINE_PUBLIC_ALIAS(__set_nterrno, libd_setnterrno);
DEFINE_INTERN_ALIAS(libc___set_nterrno, libd_setnterrno);
INTERN NOBLOCK ATTR_SECTION(".text.crt.dos.errno_access") syscall_slong_t
NOTHROW(LIBDCALL libd_setnterrno)(/*nt*/ errno_t value) {
	struct pthread *me = &current;
	me->pt_errno_value = value;
	me->pt_errno_kind  = LIBC_ERRNO_KIND_NT;
	return -1;
}



/************************************************************************/
/* CYGWIN                                                               */
/************************************************************************/

DEFINE_PUBLIC_ALIAS(__cygerrno_location, libd_cygerrno_p);
DEFINE_PUBLIC_ALIAS(DOS$__errno, libd_cygerrno_p);
DEFINE_INTERN_ALIAS(libd___errno, libd_cygerrno_p);
INTERN NOBLOCK ATTR_CONST ATTR_SECTION(".text.crt.dos.errno_access") /*cyg*/ errno_t *
NOTHROW(LIBDCALL libd_cygerrno_p)(void) {
	struct pthread *me = &current;
	if (me->pt_errno_kind != LIBC_ERRNO_KIND_CYG) {
		if (me->pt_errno_kind == LIBC_ERRNO_KIND_KOS) {
			me->pt_errno_value = libd_errno_kos2cyg(me->pt_errno_value);
		} else if (me->pt_errno_kind == LIBC_ERRNO_KIND_DOS) {
			me->pt_errno_value = libd_errno_dos2cyg(me->pt_errno_value);
		} else {
			me->pt_errno_value = libd_errno_nt2cyg(me->pt_errno_value);
		}
		me->pt_errno_kind = LIBC_ERRNO_KIND_CYG;
	}
	return &me->pt_errno_value;
}

DEFINE_PUBLIC_ALIAS(__get_cygerrno, libd_getcygerrno);
DEFINE_INTERN_ALIAS(libc___get_cygerrno, libd_getcygerrno);
INTERN NOBLOCK ATTR_PURE ATTR_SECTION(".text.crt.dos.errno_access") /*cyg*/ errno_t
NOTHROW(LIBDCALL libd_getcygerrno)(void) {
	return *libd_cygerrno_p();
}

DEFINE_PUBLIC_ALIAS(__set_cygerrno, libd_setcygerrno);
DEFINE_INTERN_ALIAS(libc___set_cygerrno, libd_setcygerrno);
INTERN NOBLOCK ATTR_SECTION(".text.crt.dos.errno_access") syscall_slong_t
NOTHROW(LIBDCALL libd_setcygerrno)(/*cyg*/ errno_t value) {
	struct pthread *me = &current;
	me->pt_errno_value = value;
	me->pt_errno_kind  = LIBC_ERRNO_KIND_CYG;
	return -1;
}

DECL_END

#endif /* !GUARD_LIBC_LIBC_ERRNO_C */
