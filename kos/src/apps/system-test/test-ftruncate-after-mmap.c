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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_FTRUNCATE_AFTER_MMAP_C
#define GUARD_APPS_SYSTEM_TEST_TEST_FTRUNCATE_AFTER_MMAP_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <system-test/ctest.h>

#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

DEFINE_TEST(ftruncate_after_mmap) {
	fd_t fd;
	void *m1, *m2;
	unsigned char vec[1];

	(void)mkdir("/var", 0755); /* Use /var since ramfs on /tmp would refuse to unload file contents */
	(void)unlink("/var/mmaptest.dat");
	fd = open("/var/mmaptest.dat", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if unlikely(fd < 0)
		return; /* Maybe some FS problem??? Whatever the case: not our job to fix */
	EQ(4, write(fd, "TEST", 4));
	EQ(0, fsync(fd));

	m1 = mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	NE(MAP_FAILED, m1);
	EQ(0, madvise(m1, 4, MADV_PAGEOUT)); /* Advise the kernel to unload the mapping */

	/* Assert that our "TEST" really isn't loaded into the core anymore
	 * This is only here to ensure that `MADV_PAGEOUT' actually  worked
	 * to unload the mapping from memory. */
	EQ(0, mincore(m1, 4, vec));
	EQ(0, vec[0]);

	/* Do the magical truncate on the file. */
	EQ(0, ftruncate(fd, 0));

	/* Assert that ftruncate caused our MAP_PRIVATE
	 * mapping  to magically re-appear in the core. */
	EQ(0, mincore(m1, 4, vec));
	EQ(1, vec[0]);

	/* Create another mapping of the file. */
	m2 = mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	NE(MAP_FAILED, m2);
	EQ(0, close(fd));

	/* Assert the validity of the 2 mappings we created. */
	EQmemf("TEST", m1, 4, "A MAP_PRIVATE mapping must retain its contents, even after an ftruncate");
	EQmemf("\0\0\0\0", m2, 4, "This mapping was created after the ftruncate, so it must be all 0-es");

	/* Cleanup... */
	EQ(0, munmap(m1, 4));
	EQ(0, munmap(m2, 4));
	EQ(0, unlink("/var/mmaptest.dat"));
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_FTRUNCATE_AFTER_MMAP_C */
