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
%(c_prefix){
/* (#) Portability: DragonFly BSD (/include/fstab.h) */
/* (#) Portability: FreeBSD       (/include/fstab.h) */
/* (#) Portability: GNU C Library (/misc/fstab.h) */
/* (#) Portability: GNU Hurd      (/usr/include/fstab.h) */
/* (#) Portability: NetBSD        (/include/fstab.h) */
/* (#) Portability: OpenBSD       (/include/fstab.h) */
/* (#) Portability: OpenSolaris   (/usr/src/lib/libbc/inc/include/fstab.h) */
/* (#) Portability: libc6         (/include/fstab.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.database.fstab")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <paths.h>
)]%[insert:prefix(
#include <bits/crt/db/fstab.h>
)]%{

/************************************************************************/
/* <fstab.h>: An alternate interface/wrapper for <mntent.h>             */
/************************************************************************/

/* The filename of the fstab database file. (s.a. `_PATH_MNTTAB') */
#ifdef _PATH_MNTTAB
#define _PATH_FSTAB _PATH_MNTTAB
#define FSTAB       _PATH_MNTTAB /* Deprecated macro */
#endif /* _PATH_MNTTAB */

/* Possible values for `struct fstab::fs_type' */
#define FSTAB_RW "rw" /* read+write */
#define FSTAB_RQ "rq" /* read+write with quotas */
#define FSTAB_RO "ro" /* read-only */
#define FSTAB_SW "sw" /* swap */
#define FSTAB_XX "xx" /* ??? */

#ifdef __CC__
__SYSDECL_BEGIN

}

@@>> setfsent(3)
@@Open the fstab database and rewind to its start
@@@return: 1 : Success
@@@return: 0 : Error (s.a. `errno')
int setfsent(void);

@@>> endfsent(3)
@@Close the fstab database.
void endfsent(void);

@@>> getfsent(3)
@@If necessary, open the fstab database, before reading+returning the next entry.
@@@return: * :   Pointer to a statically allocated fstab entry
@@@return: NULL: [errno = <unchanged>] All entries have been read
@@@return: NULL: [errno = *] Error
[[wunused, nullable]]
[[decl_include("<bits/crt/db/fstab.h>")]]
struct fstab *getfsent(void);


@@>> getfsspec(3)
@@Find and return the fstab entry with `strcmp(ent->fs_spec, special_file) == 0'
@@@return: * :   Pointer to a statically allocated fstab entry for `special_file'
@@@return: NULL: [errno = <unchanged>] No entry exists matching `special_file'
@@@return: NULL: [errno = *] Error
[[wunused, nullable, requires_function(getfsent, setfsent)]]
[[decl_include("<bits/crt/db/fstab.h>")]]
[[impl_include("<bits/crt/db/fstab.h>")]]
struct fstab *getfsspec([[in]] const char *special_file) {
	struct fstab *result;
	if (!setfsent())
		return NULL;
	while ((result = getfsent()) != NULL) {
		if (strcmp(result->@fs_spec@, special_file) == 0)
			break;
	}
	return result;
}

@@>> getfsfile(3)
@@Find and return the fstab entry with `strcmp(ent->fs_file, mount_point) == 0'
@@@return: * :   Pointer to a statically allocated fstab entry for `mount_point'
@@@return: NULL: [errno = <unchanged>] No entry exists matching `mount_point'
@@@return: NULL: [errno = *] Error
[[wunused, nullable, requires_function(getfsent, setfsent)]]
[[decl_include("<bits/crt/db/fstab.h>")]]
[[impl_include("<bits/crt/db/fstab.h>")]]
struct fstab *getfsfile([[in]] const char *mount_point) {
	struct fstab *result;
	if (!setfsent())
		return NULL;
	while ((result = getfsent()) != NULL) {
		if (strcmp(result->@fs_file@, mount_point) == 0)
			break;
	}
	return result;
}



%{

__SYSDECL_END
#endif /* __CC__ */

}
