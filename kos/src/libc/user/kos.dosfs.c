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
#ifndef GUARD_LIBC_USER_KOS_DOSFS_C
#define GUARD_LIBC_USER_KOS_DOSFS_C 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>

#include <fcntl.h>

#include "kos.dosfs.h"

DECL_BEGIN

INTERN ATTR_SECTION(".bss.crt.dos.io.access") oflag_t libd_O_DOSPATH   = 0; /* Either `0' or `O_DOSPATH' */
INTERN ATTR_SECTION(".bss.crt.dos.io.access") atflag_t libd_AT_DOSPATH = 0; /* Either `0' or `AT_DOSPATH' */


/*[[[head:libc_dosfs_getenabled,hash:CRC-32=0x689daec6]]]*/
/* >> dosfs_getenabled(3)
 * Get the current dosfs-emulation mode, as used by
 * libc filesystem functions  whose names are  pre-
 * fixed with `DOS$' (s.a.  `dosfs_setenabled(3)').
 * @return: * : The current mode (one of `DOSFS_*') */
INTERN ATTR_SECTION(".text.crt.dos.io.access") ATTR_PURE WUNUSED unsigned int
NOTHROW(LIBCCALL libc_dosfs_getenabled)(void)
/*[[[body:libc_dosfs_getenabled]]]*/
{
	if (ATOMIC_READ(libd_O_DOSPATH) != 0)
		return DOSFS_ENABLED;
	return DOSFS_DISABLED;
}
/*[[[end:libc_dosfs_getenabled]]]*/

/*[[[head:libc_dosfs_setenabled,hash:CRC-32=0x8b2ce713]]]*/
/* >> dosfs_setenabled(3)
 * Set the is-enabled  state for filesystem  emulation.
 * When enabled, all DOS$-prefixed filesystem functions
 * will include  `O_DOSPATH' /  `AT_DOSPATH' in  system
 * calls,  meaning they accept/return DOS paths, rather
 * than unix paths.
 *
 * The default state of dosfs emulation depends on the
 * binary format of the main application. If the  main
 * application is an ELF binary, the default state  is
 * set  to  `DOSFS_DISABLED'. When  it's a  PE binary,
 * the default state is `DOSFS_ENABLED'
 *
 * Note that this function does not affect programs  that
 * explicitly pass  `O_DOSPATH'  /  `AT_DOSPATH'  to  API
 * functions.  -  This  only affects  the  implicit flags
 * added to caller-given arguments within DOS$ functions.
 *
 * @param: newmode: The new mode to set (one of `DOSFS_*')
 * @return: * :     The old mode (one of `DOSFS_*') */
INTERN ATTR_SECTION(".text.crt.dos.io.access") unsigned int
NOTHROW(LIBCCALL libc_dosfs_setenabled)(unsigned int newmode)
/*[[[body:libc_dosfs_setenabled]]]*/
{
	oflag_t old_oflags;
	switch (newmode) {

	case DOSFS_ENABLED:
		old_oflags = ATOMIC_XCH(libd_O_DOSPATH, O_DOSPATH);
		ATOMIC_WRITE(libd_AT_DOSPATH, AT_DOSPATH);
		break;

	case DOSFS_DISABLED:
		old_oflags = ATOMIC_XCH(libd_O_DOSPATH, 0);
		ATOMIC_WRITE(libd_AT_DOSPATH, 0);
		break;

	default:
		old_oflags = ATOMIC_READ(libd_O_DOSPATH);
		break;
	}
	if (old_oflags != 0)
		return DOSFS_ENABLED;
	return DOSFS_DISABLED;
}
/*[[[end:libc_dosfs_setenabled]]]*/

/*[[[start:exports,hash:CRC-32=0xfeb97267]]]*/
DEFINE_PUBLIC_ALIAS(dosfs_getenabled, libc_dosfs_getenabled);
DEFINE_PUBLIC_ALIAS(dosfs_setenabled, libc_dosfs_setenabled);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_DOSFS_C */
