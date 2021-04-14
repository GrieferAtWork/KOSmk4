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
#ifndef GUARD_MODPROCFS_FILES_FILESYSTEMS_C
#define GUARD_MODPROCFS_FILES_FILESYSTEMS_C 1

#define _KOS_SOURCE 1 /* snprintf returns size_t */

#include <kernel/compiler.h>

#include <fs/node.h>

#include <string.h>

#include "../procfs.h"

DECL_BEGIN

INTERN NONNULL((1, 2)) ssize_t KCALL
ProcFS_Filesystems_Printer(struct regular_node *__restrict UNUSED(self),
                           pformatprinter printer, void *arg) {
	ssize_t temp, result = 0;
	REF struct superblock_type *iter;
	sync_read(&fs_filesystem_types.ft_typelock);
	iter = xincref(fs_filesystem_types.ft_types);
	sync_endread(&fs_filesystem_types.ft_typelock);
	while (iter) {
		REF struct superblock_type *next;
		TRY {
			/* Print the filesystem type name in 1 of 2 ways:
			 *     - "        <name>\n"
			 *     - "nodev   <name>\n" */
			PRIVATE char const prefix[2][9] = {
				[0] = "        ",
				[1] = "nodev   ",
			};
			char const *used_prefix;
#if SUPERBLOCK_TYPE_FNODEV == 1
			used_prefix = prefix[iter->st_flags & SUPERBLOCK_TYPE_FNODEV];
#else /* SUPERBLOCK_TYPE_FNODEV == 1 */
			used_prefix = prefix[(iter->st_flags & SUPERBLOCK_TYPE_FNODEV) ? 1 : 0];
#endif /* SUPERBLOCK_TYPE_FNODEV != 1 */

			/* Print the info-line */
			temp = format_printf(printer, arg, "%s%s\n",
			                     used_prefix, iter->st_name);

			/* Account for errors */
			if unlikely(temp < 0)
				goto err;
			result += temp;

			/* Acquire a new read-lock to the filesystem-types chain. */
			sync_read(&fs_filesystem_types.ft_typelock);
		} EXCEPT {
			decref_unlikely(iter);
			RETHROW();
		}
		/* Iterate towards the next type. */
		next = xincref(iter->st_chain);
		sync_endread(&fs_filesystem_types.ft_typelock);
		decref_unlikely(iter);
		iter = next;
	}
	return result;
err:
	decref_unlikely(iter);
	return temp;
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_FILESYSTEMS_C */
