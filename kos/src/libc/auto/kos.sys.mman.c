/* HASH CRC-32:0x1678fa08 */
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
#ifndef GUARD_LIBC_AUTO_KOS_SYS_MMAN_C
#define GUARD_LIBC_AUTO_KOS_SYS_MMAN_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/kos.sys.mman.h"
#include "../user/kos.except.h"
#include "../user/kos.fcntl.h"
#include "../user/kos.sys.stat.h"
#include "../user/kos.unistd.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/paths.h>
#include <asm/os/oflags.h>
#include <kos/parts/malloca.h>
#include <libc/errno.h>
#include <bits/types.h>
INTERN ATTR_SECTION(".text.crt.except.system.mman") ATTR_IN(1) fd_t
(LIBCCALL libc_ShmOpen)(char const *name,
                        oflag_t oflags,
                        mode_t mode) THROWS(...) {
	fd_t result;
	char *fullname;
	size_t namelen;

	if (oflags & O_DOSPATH) {
		while (*name == '/' || *name == '\\')
			++name;
	} else {
		while (*name == '/')
			++name;
	}







	namelen  = libc_strlen(name);
	fullname = (char *)__Malloca((__COMPILER_STRLEN(__PATH_SHM) + 1 +
	                              namelen + 1) *
	                             sizeof(char));
	libc_memcpy(libc_mempcpy(fullname, __PATH_SHM "/",
	               (__COMPILER_STRLEN(__PATH_SHM) + 1) *
	               sizeof(char)),
	       fullname,
	       (namelen + 1) *
	       sizeof(char));
	result = libc_Open(fullname, oflags, mode);

	if (result < 0 && (oflags & O_CREAT) != 0 && __libc_geterrno_or(ENOENT) == ENOENT) {
		/* Lazily create the SHM directory (/dev/shm), if it hadn't been created already.
		 * XXX:   This    assumes    that    `headof(__PATH_SHM)'    already    exists... */
		libc_MkDir(__PATH_SHM, 0777);
		result = libc_Open(fullname, oflags, mode);
	}

	__freea(fullname);
	return result;
}
#include <asm/os/paths.h>
#include <hybrid/typecore.h>
#include <kos/parts/malloca.h>
INTERN ATTR_SECTION(".text.crt.except.system.mman") ATTR_IN(1) void
(LIBCCALL libc_ShmUnlink)(char const *name) THROWS(...) {
	char *fullname;
	size_t namelen;




	while (*name == '/')
		++name;

	namelen  = libc_strlen(name);
	fullname = (char *)__Malloca((__COMPILER_STRLEN(__PATH_SHM) + 1 +
	                              namelen + 1) *
	                             sizeof(char));
	libc_memcpy(libc_mempcpy(fullname, __PATH_SHM "/",
	               (__COMPILER_STRLEN(__PATH_SHM) + 1) *
	               sizeof(char)),
	       fullname,
	       (namelen + 1) *
	       sizeof(char));
	libc_Unlink(fullname);
	__freea(fullname);
}
#endif /* !__KERNEL__ */
#include <asm/pkey.h>
#if !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
#include <kos/except/codes.h>
#include <kos/except/reason/inval.h>
/* >> pkey_set(3) */
INTERN ATTR_SECTION(".text.crt.except.system.mman") void
(LIBCCALL libc_PKeySet)(int pkey,
                        unsigned int access_rights) THROWS(...) {
	if unlikely(!__arch_pkey_verify_key(pkey))
		libc_except_thrown(EXCEPT_CODEOF(E_INVALID_ARGUMENT_BAD_VALUE), 2, E_INVALID_ARGUMENT_CONTEXT_PKEY_SET_PKEY, pkey);
	if unlikely(!__arch_pkey_verify_rights(access_rights))
		libc_except_thrown(EXCEPT_CODEOF(E_INVALID_ARGUMENT_BAD_VALUE), 2, E_INVALID_ARGUMENT_CONTEXT_PKEY_SET_ACCESS_RIGHTS, access_rights);
	__arch_pkey_set(pkey, access_rights);
}
#include <kos/except/codes.h>
#include <kos/except/reason/inval.h>
/* >> pkey_get(3) */
INTERN ATTR_SECTION(".text.crt.except.system.mman") unsigned int
(LIBCCALL libc_PKeyGet)(int pkey) THROWS(...) {
	if unlikely(!__arch_pkey_verify_key(pkey))
		libc_except_thrown(EXCEPT_CODEOF(E_INVALID_ARGUMENT_BAD_VALUE), 2, E_INVALID_ARGUMENT_CONTEXT_PKEY_GET_PKEY, pkey);
	return __arch_pkey_get(pkey);
}
#endif /* !__KERNEL__ && __ARCH_HAVE_PKEY */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(ShmOpen, libc_ShmOpen);
DEFINE_PUBLIC_ALIAS(ShmUnlink, libc_ShmUnlink);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
DEFINE_PUBLIC_ALIAS(PKeySet, libc_PKeySet);
DEFINE_PUBLIC_ALIAS(PKeyGet, libc_PKeyGet);
#endif /* !__KERNEL__ && __ARCH_HAVE_PKEY */

#endif /* !GUARD_LIBC_AUTO_KOS_SYS_MMAN_C */
