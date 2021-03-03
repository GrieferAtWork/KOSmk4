/* HASH CRC-32:0xef40d304 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_MNTENT_C
#define GUARD_LIBC_AUTO_MNTENT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/mntent.h"
#include "../user/stdio.h"
#include "../user/string.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> addmntent(3)
 * Append a line `"%s %s %s %s %d %d\n" % (mnt_fsname, mnt_dir,
 * mnt_type, mnt_opts, mnt_freq, mnt_passno)' to the end of `stream'
 * @return: 0: Success
 * @return: 1: Error (WARNING: `errno' is left undefined) */
INTERN ATTR_SECTION(".text.crt.database.mntent") NONNULL((1, 2)) int
(LIBCCALL libc_addmntent)(FILE *__restrict stream,
                          struct mntent const *__restrict mnt) THROWS(...) {
	if unlikely(!mnt ||
	            !mnt->mnt_fsname || !mnt->mnt_dir ||
	            !mnt->mnt_type || !mnt->mnt_opts)
		return 1;
	if (libc_fseek(stream, 0, __SEEK_END) < 0)
		return 1;
	libc_fprintf(stream, "%s %s %s %s %d %d\n",
	        mnt->mnt_fsname,
	        mnt->mnt_dir,
	        mnt->mnt_type,
	        mnt->mnt_opts,
	        mnt->mnt_freq,
	        mnt->mnt_passno);
	return 0;
}
/* >> hasmntopt(3)
 * Check if `mnt->mnt_opts' contains an option matching `opt'.
 * @return: * :   Address of the `opt'-string in `mnt->mnt_opts'
 * @return: NULL: No option `opt' found in `mnt->mnt_opts' */
INTERN ATTR_SECTION(".text.crt.database.mntent") ATTR_PURE WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_hasmntopt)(struct mntent const *mnt,
                                     char const *opt) {
	char *str;
	if likely(mnt && opt && (str = mnt->mnt_opts) != NULL) {
		size_t optlen = libc_strlen(opt);
		while (*str) {
			if (libc_memcmp(str, opt, optlen * sizeof(char)) == 0 &&
			    (str[optlen] == ',' || str[optlen] == '\0'))
				return str;
			str = libc_strchrnul(str, ',');
		}
	}
	return NULL;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(addmntent, libc_addmntent);
DEFINE_PUBLIC_ALIAS(hasmntopt, libc_hasmntopt);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_MNTENT_C */
