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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_FTRUNCATE_AFTER_MMAP_C
#define GUARD_APPS_SYSTEM_TEST_TEST_FTRUNCATE_AFTER_MMAP_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/io.h>
#include <kos/ioctl/file.h>
#include <kos/types.h>
#include <sys/ioctl.h>
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

PRIVATE void ftruncate_after_mmap_impl(bool use_unlink) {
	fd_t fd, msfd;
	void *m1, *m2, *m3;
	unsigned char vec[1];
	struct file_msalign fms;

	(void)mkdir("/var", 0755); /* Use /var since ramfs on /tmp would refuse to unload file contents */
	(void)unlink("/var/mmaptest.dat");
	fd = open("/var/mmaptest.dat", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if unlikely(fd < 0)
		return; /* Maybe some FS problem??? Whatever the case: not our job to diagnose */

	/* Create a misaligned wrapper for `fd' with offset=2 */
	fms.fmsa_offset         = 2;
	fms.fmsa_resfd.of_mode  = OPENFD_MODE_AUTO;
	fms.fmsa_resfd.of_flags = IO_CLOEXEC;
	ISpos((msfd = ioctl(fd, FILE_IOC_MSALIGN, &fms)));
	EQ(0, fms.fmsa_offset & (getpagesize() - 1));

	EQ(4, write(fd, "TEST", 4));
	EQ(0, fsync(fd));

	m1 = mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	NE(MAP_FAILED, m1);
	m2 = mmap(NULL, 2, PROT_READ | PROT_WRITE, MAP_PRIVATE, msfd, fms.fmsa_offset);
	NE(MAP_FAILED, m2);
	EQmem("TEST", m1, 4);
	EQmem("ST", m2, 2);

	/* Advise the kernel to unload the mappings */
	EQ(0, madvise(m1, 4, MADV_PAGEOUT));
	EQ(0, madvise(m2, 2, MADV_PAGEOUT));

	/* Assert that our "TEST" really isn't loaded into the core anymore
	 * This is only here to ensure that `MADV_PAGEOUT' actually  worked
	 * to unload the mapping from memory. */
	EQ(0, mincore(m1, 4, vec));
	EQ(0, vec[0]);
	EQ(0, mincore(m2, 2, vec));
	EQ(0, vec[0]);

	/* Do the magical truncate on the file. */
	if (use_unlink) {
		EQ(0, unlink("/var/mmaptest.dat"));
	} else {
		EQ(0, ftruncate(fd, 0));
	}

	/* Assert that ftruncate caused our MAP_PRIVATE
	 * mappings to magically re-appear in the core. */
	EQ(0, mincore(m1, 4, vec));
	EQ(1, vec[0]);
	EQ(0, mincore(m2, 2, vec));
	EQ(1, vec[0]);

	/* Create another mapping of the file. */
	m3 = MAP_FAILED;
	if (!use_unlink) { /* TODO: Shouldn't this also work after unlink? */
		m3 = mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
		NE(MAP_FAILED, m3);
	}
	EQ(0, close(msfd));
	EQ(0, close(fd));

	/* Assert the validity of the 3 mappings we created (ensuring that they all contain the expected data) */
	EQmemf("TEST", m1, 4, "A MAP_PRIVATE mapping must retain its contents, even after an ftruncate");
	EQmemf("ST", m2, 2, "A misaligned sub-file must retain its contents, even after an ftruncate");
	if (m3 != MAP_FAILED)
		EQmemf("\0\0\0\0", m3, 4, "This mapping was created after the ftruncate, so it must be all 0-es");

	/* Cleanup... */
	EQ(0, munmap(m1, 4));
	EQ(0, munmap(m2, 2));
	if (m3 != MAP_FAILED)
		EQ(0, munmap(m3, 4));
	if (!use_unlink)
		EQ(0, unlink("/var/mmaptest.dat"));
}

DEFINE_TEST(ftruncate_after_mmap) {
	ctest_substatf("With ftruncate");
	ftruncate_after_mmap_impl(false);
	ctest_substatf("With unlink");
	ftruncate_after_mmap_impl(true);
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_FTRUNCATE_AFTER_MMAP_C */
