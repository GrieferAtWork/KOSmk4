/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_FSTAB_C
#define GUARD_LIBC_USER_FSTAB_C 1

#include "../api.h"
/**/

#include <mntent.h>
#include <stdio.h>
#include <string.h>

#include "fstab.h"

DECL_BEGIN

/* Global data symbols for <fstab.h> functions. */
PRIVATE ATTR_SECTION(".bss.crt.database.fstab") FILE *fstab_file = NULL;
PRIVATE ATTR_SECTION(".bss.crt.database.fstab") struct fstab fstab_ent = {};


/*[[[head:libc_setfsent,hash:CRC-32=0x77e4bb09]]]*/
/* >> setfsent(3)
 * Open the fstab database and rewind to its start
 * @return: 1 : Success
 * @return: 0 : Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.database.fstab") int
NOTHROW_NCX(LIBCCALL libc_setfsent)(void)
/*[[[body:libc_setfsent]]]*/
{
	if (!fstab_file) {
		fstab_file = fopen(_PATH_FSTAB, "r");
		if (!fstab_file)
			return 0; /* Yes: return 0 on error */
	} else {
		/* Rewind to the start */
		rewind(fstab_file);
	}
	return 1; /* Yes: return 1 on success */
}
/*[[[end:libc_setfsent]]]*/

/*[[[head:libc_endfsent,hash:CRC-32=0x11db6fa8]]]*/
/* >> endfsent(3)
 * Close the fstab database. */
INTERN ATTR_SECTION(".text.crt.database.fstab") void
NOTHROW_NCX(LIBCCALL libc_endfsent)(void)
/*[[[body:libc_endfsent]]]*/
{
	if (fstab_file) {
		fclose(fstab_file);
		fstab_file = NULL;
	}
}
/*[[[end:libc_endfsent]]]*/

PRIVATE ATTR_SECTION(".rodata.crt.database.fstab")
char const fstab_fallback_type[] = FSTAB_XX;
PRIVATE ATTR_SECTION(".rodata.crt.database.fstab")
char const fstab_types[] =
FSTAB_RW "\0"
FSTAB_RQ "\0"
FSTAB_RO "\0"
FSTAB_SW "\0";


/*[[[head:libc_getfsent,hash:CRC-32=0xd2ab1a24]]]*/
/* >> getfsent(3)
 * If necessary, open the fstab database, before reading+returning the next entry.
 * @return: * :   Pointer to a statically allocated fstab entry
 * @return: NULL: [errno = <unchanged>] All entries have been read
 * @return: NULL: [errno = *] Error */
INTERN ATTR_SECTION(".text.crt.database.fstab") WUNUSED struct fstab *
NOTHROW_NCX(LIBCCALL libc_getfsent)(void)
/*[[[body:libc_getfsent]]]*/
{
	struct mntent *ent;
	char const *ptr;

	/* Open the fstab file (if necessary) */
	if (!fstab_file && !libc_setfsent())
		return NULL;
	ent = getmntent(fstab_file);
	if (!ent)
		return NULL;

	/* Transpose the `mntent' structure into `fstab' */
	fstab_ent.fs_spec    = ent->mnt_fsname;
	fstab_ent.fs_file    = ent->mnt_dir;
	fstab_ent.fs_vfstype = ent->mnt_type;
	fstab_ent.fs_mntops  = ent->mnt_opts;
	fstab_ent.fs_freq    = ent->mnt_freq;
	fstab_ent.fs_passno  = ent->mnt_passno;
	fstab_ent.fs_type    = fstab_fallback_type;

	/* Determine `fs_type' */
	ptr = fstab_types;
	while (*ptr) {
		size_t len = strlen(ptr);
		/* s.a. modprocfs: `print_mounting_point()'
		 * HINT: On KOS, only "ro" and "rw" are ever generated (based on `MFILE_F_READONLY') */
		if (bcmp(fstab_ent.fs_mntops, ptr, len, sizeof(char)) == 0 &&
		    (fstab_ent.fs_mntops[len] == ',' || fstab_ent.fs_mntops[len] == '\0')) {
			fstab_ent.fs_type = ptr;
			break;
		}
		ptr += (len + 1);
	}

	/* Return the descriptor for the fstab entry. */
	return &fstab_ent;
}
/*[[[end:libc_getfsent]]]*/



/*[[[start:exports,hash:CRC-32=0xe5091e76]]]*/
DEFINE_PUBLIC_ALIAS(setfsent, libc_setfsent);
DEFINE_PUBLIC_ALIAS(endfsent, libc_endfsent);
DEFINE_PUBLIC_ALIAS(getfsent, libc_getfsent);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_FSTAB_C */
