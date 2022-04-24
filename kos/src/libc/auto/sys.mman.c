/* HASH CRC-32:0x8a9004c */
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
#ifndef GUARD_LIBC_AUTO_SYS_MMAN_C
#define GUARD_LIBC_AUTO_SYS_MMAN_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/sys.mman.h"
#include "../user/fcntl.h"
#include "string.h"
#include "../user/sys.stat.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/paths.h>
#include <asm/os/oflags.h>
#include <parts/malloca.h>
#include <libc/errno.h>
#include <bits/types.h>
/* >> shm_open(3) */
INTERN ATTR_SECTION(".text.crt.system.mman") NONNULL((1)) fd_t
NOTHROW_RPC(LIBCCALL libc_shm_open)(char const *name,
                                    oflag_t oflags,
                                    mode_t mode) {
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
	fullname = (char *)__malloca((__COMPILER_STRLEN(__PATH_SHM) + 1 +
	                              namelen + 1) *
	                             sizeof(char));
	if unlikely(!fullname)
		return -1;
	libc_memcpy(libc_mempcpy(fullname, __PATH_SHM "/",
	               (__COMPILER_STRLEN(__PATH_SHM) + 1) *
	               sizeof(char)),
	       fullname,
	       (namelen + 1) *
	       sizeof(char));
	result = libc_open(fullname, oflags, mode);

	if (result < 0 && (oflags & O_CREAT) != 0 && __libc_geterrno_or(ENOENT) == ENOENT) {
		/* Lazily create the SHM directory (/dev/shm), if it hadn't been created already.
		 * XXX:   This    assumes    that    `headof(__PATH_SHM)'    already    exists... */
		libc_mkdir(__PATH_SHM, 0777);
		result = libc_open(fullname, oflags, mode);
	}

	__freea(fullname);
	return result;
}
#include <asm/os/paths.h>
#include <hybrid/typecore.h>
#include <parts/malloca.h>
/* >> shm_unlink(3) */
INTERN ATTR_SECTION(".text.crt.system.mman") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_shm_unlink)(char const *name) {
	int result;
	char *fullname;
	size_t namelen;




	while (*name == '/')
		++name;

	namelen  = libc_strlen(name);
	fullname = (char *)__malloca((__COMPILER_STRLEN(__PATH_SHM) + 1 +
	                              namelen + 1) *
	                             sizeof(char));
	if unlikely(!fullname)
		return -1;
	libc_memcpy(libc_mempcpy(fullname, __PATH_SHM "/",
	               (__COMPILER_STRLEN(__PATH_SHM) + 1) *
	               sizeof(char)),
	       fullname,
	       (namelen + 1) *
	       sizeof(char));
	result = libc_unlink(fullname);
	__freea(fullname);
	return result;
}
#endif /* !__KERNEL__ */
#include <asm/pkey.h>
#if !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
#include <libc/errno.h>
/* >> pkey_set(3) */
INTERN ATTR_SECTION(".text.crt.system.mman") int
NOTHROW_NCX(LIBCCALL libc_pkey_set)(int pkey,
                                    unsigned int access_rights) {
	if unlikely(!__arch_pkey_verify_key(pkey) ||
	            !__arch_pkey_verify_rights(access_rights))
		goto badkey_or_rights;
	__arch_pkey_set(pkey, access_rights);
	return 0;
badkey_or_rights:

	return libc_seterrno(EINVAL);



}
#include <libc/errno.h>
/* >> pkey_get(3) */
INTERN ATTR_SECTION(".text.crt.system.mman") int
NOTHROW_NCX(LIBCCALL libc_pkey_get)(int pkey) {
	if unlikely(!__arch_pkey_verify_key(pkey))
		goto badkey;
	return __arch_pkey_get(pkey);
badkey:

	return libc_seterrno(EINVAL);



}
#endif /* !__KERNEL__ && __ARCH_HAVE_PKEY */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(shm_open, libc_shm_open);
DEFINE_PUBLIC_ALIAS(shm_unlink, libc_shm_unlink);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
DEFINE_PUBLIC_ALIAS(pkey_set, libc_pkey_set);
DEFINE_PUBLIC_ALIAS(pkey_get, libc_pkey_get);
#endif /* !__KERNEL__ && __ARCH_HAVE_PKEY */

#endif /* !GUARD_LIBC_AUTO_SYS_MMAN_C */
