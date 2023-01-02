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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_CC_C
#define GUARD_APPS_SYSTEM_TEST_TEST_CC_C 1
#define _BSD_SOURCE 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/ksysctl.h>
#include <kos/types.h>
#include <sys/stat.h>
#include <system-test/ctest.h>

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

DECL_BEGIN

DEFINE_TEST(cc) {
	static char const dat[] = "File data. Hello!\n";
#define DATSZ (sizeof(dat) - sizeof(char))
	char buf[DATSZ];

	fd_t fd;
	unlink("/var/testfile.txt");
	fd = open("/var/testfile.txt", O_CREAT | O_EXCL | O_WRONLY, 0644); /* NOLINT */
	if (fd < 0) {
		mkdir("/var/", 755);
		ISpos((fd = open("/var/testfile.txt", O_CREAT | O_EXCL | O_WRONLY, 0644))); /* NOLINT */
	}
	EQ(DATSZ, pwrite(fd, dat, DATSZ, 512));
	EQ(0, close(fd));

	/* sync+cc to force unload all data relating to "testfile.txt" from memory */
	sync();
	ksysctl(KSYSCTL_SYSTEM_CLEARCACHES);

	/* Re-open the file and append data. Because  no parts of the file are  currently
	 * loaded into memory, the kernel will have to do so really complicated  trickery
	 * because our write will be unaligned, but  in a manner that still requires  the
	 * data written above to be re-loaded since this write goes into the same sector.
	 *
	 * It  used to be that the kernel failed  to re-read data in this scenario, as a
	 * result of missing handling for the case  where a write into an unloaded  file
	 * area, that is also beyond the end of a file, means that the entire write only
	 * affects previously unpopulated areas of the file (which isn't the case as the
	 * relevant part may have just not been loaded yet)
	 *
	 * This test ensures that this no longer happens, and that file data is preserved
	 * across sync+cc, even  if the first  access thereafter happens  to be a  write. */
	ISpos((fd = open("/var/testfile.txt", O_WRONLY | O_APPEND))); /* NOLINT */
	EQ(4, write(fd, "tail", 4));
	EQ(0, close(fd));
	sync();
	ksysctl(KSYSCTL_SYSTEM_CLEARCACHES);

	ISpos((fd = open("/var/testfile.txt", O_RDONLY))); /* NOLINT */
	EQ(DATSZ, pread(fd, buf, DATSZ, 512));
	EQmem(dat, buf, DATSZ);

	EQ(0, close(fd));
	EQ(0, unlink("/var/testfile.txt"));
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_CC_C */
