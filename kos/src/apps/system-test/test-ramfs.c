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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_RAMFS_C
#define GUARD_APPS_SYSTEM_TEST_TEST_RAMFS_C 1
#define _BSD_SOURCE 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/ksysctl.h>
#include <kos/types.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

DECL_BEGIN

DEFINE_TEST(ramfs) {
	fd_t fd;

	/* Cleanup a (possibly incomplete) previous invocation */
	umount("/tmp/submount");
	rmdir("/tmp/submount");

	EQd(0, mkdir("/tmp/submount", 0755));
	EQd(0, mount(NULL, "/tmp/submount", "ramfs", 0, NULL));

	/* Assert that the correct errors are produced when
	 * trying to do non-sense with mounting points. */
	EQd(-1, mkdir("/tmp/submount", 0755));
	EQd(errno, EEXIST);
	EQd(-1, rmdir("/tmp/submount"));
	EQd(errno, EBUSY);

	LEd(0, (fd = open("/tmp/submount/myfile.txt", O_CREAT | O_EXCL | O_WRONLY, 0644)));
	{
		static char const s[] = "File contents...\n";
		EQss(sizeof(s) - sizeof(char),
		     write(fd, s, sizeof(s) - sizeof(char)));
	}
	EQd(0, close(fd));

	EQd(0, mkdir("/tmp/submount/subdir", 0755));
	LEd(0, (fd = open("/tmp/submount/subdir/foo.bar", O_CREAT | O_EXCL | O_WRONLY, 0644)));
	{
		static char const s[] = "foo.bar file contents...\n";
		EQss(sizeof(s) - sizeof(char),
		     write(fd, s, sizeof(s) - sizeof(char)));
	}
	/*EQd(0, close(fd));*/ /* Intentionally not closed! */

	/* Unmount without first deleting "myfile.txt"
	 *
	 * Doing this leaves behind a reference loop that has to be resolved
	 * explicitly  within `fsuper_delete()'. Once all other system-tests
	 * are  complete, we always  assert that there  are no memory leaks,
	 * which this test leaves  behind in case `fsuper_delete()'  doesn't
	 * handle this case correctly. */
	EQd(0, umount("/tmp/submount"));
	EQd(0, rmdir("/tmp/submount"));
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_RAMFS_C */
