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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_SYSTEM_RTLD_RO_C
#define GUARD_APPS_SYSTEM_TEST_TEST_SYSTEM_RTLD_RO_C 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/except.h>
#include <kos/ioctl/file.h>
#include <kos/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

/* Ensure that `AT_FDSYSRTLD' cannot be used to re-write the system RTLD */
DEFINE_TEST(system_rtld_ro) {
	fd_t sysrtld;
	struct stat st;
	byte_t buf[128];
	void *map;
	size_t ps;

	/* Because the system might assign `IO_RDONLY' to `AT_FDSYSRTLD',  we
	 * have to do some extra work to get around that fact and (hopefully)
	 * be able to get a file descriptor that is writable.
	 *
	 * For this, we use the reopen-via-procfs trick. */
	{
		fd_t tempfd;
		char name[sizeof("/proc/self/fd/" PRIMAXd)];
		NEd(-1, (tempfd = dup(AT_FDSYSRTLD))); /* Make the FD appear in procfs */
		sprintf(name, "/proc/self/fd/%d", tempfd);
		NEd(-1, (sysrtld = open(name, O_RDWR)));
		/* And with that, we should have a writable file descriptor! */
		EQd(0, close(tempfd));
	}

	EQd(0, fstat(sysrtld, &st));
	assert(st.st_size > 0);
	LEss(1, pread(sysrtld, buf, sizeof(buf), 0));

	errno = 0;
	EQss(-1, pwrite(sysrtld, buf, sizeof(buf), 0));
	EQd(errno, EROFS); /* EROFS for `E_FSERROR_READONLY' (because writing isn't allowed) */

	/* Make sure that we're not able to clear the `MFILE_F_READONLY' flag.
	 * We should be prevented from doing  so because the system RTLD  uses
	 * the `MFILE_F_ROFLAGS' flag to prevent `MFILE_F_READONLY' from being
	 * changed. */
	{
		int ro = -1;
		EQd(0, ioctl(sysrtld, FILE_IOC_GETRO, &ro));
		EQd(ro, 1);

		ro = 0;
		errno = 0;
		EQd(-1, ioctl(sysrtld, FILE_IOC_SETRO, &ro));
		EQd(errno, EPERM); /* s.a. `E_ILLEGAL_OPERATION_CONTEXT_READONLY_FILE_FLAGS' */
		errno = 0;
	}

	/* Also make sure that `FS_IOC_GETFLAGS' / `FS_IOC_SETFLAGS' can't be used to clear READONLY */
	{
		long flags = 0;
		EQd(0, ioctl(sysrtld, FS_IOC_GETFLAGS, &flags));
		assert(flags & FS_IMMUTABLE_FL);
		flags &= ~FS_IMMUTABLE_FL;
		EQd(-1, ioctl(sysrtld, FS_IOC_SETFLAGS, &flags));
		EQd(errno, EPERM); /* s.a. `E_ILLEGAL_OPERATION_CONTEXT_READONLY_FILE_FLAGS' */
		flags = 0;
		EQd(-1, ioctl(sysrtld, FS_IOC_SETFLAGS, &flags));
		EQd(errno, EPERM); /* s.a. `E_ILLEGAL_OPERATION_CONTEXT_READONLY_FILE_FLAGS' */
	}

	errno = 0;
	EQss(-1, pwrite(sysrtld, buf, sizeof(buf), 0));
	EQd(errno, EROFS); /* EROFS for `E_FSERROR_READONLY' (because writing isn't allowed) */

	errno = 0, ps = getpagesize();
	EQp(MAP_FAILED, (map = mmap(NULL, ps, PROT_READ | PROT_WRITE, MAP_SHARED, sysrtld, 0)));
	EQd(EROFS, errno); /* EROFS for `E_FSERROR_READONLY' (because WRITE+SHARED aren't allowed) */

	NEp(MAP_FAILED, (map = mmap(NULL, ps, PROT_READ | PROT_WRITE, MAP_PRIVATE, sysrtld, 0)));
	if (ps > sizeof(buf))
		ps = sizeof(buf);
	if (ps > st.st_size)
		ps = (size_t)st.st_size;
	assert(memcmp(map, buf, ps) == 0);
	EQd(0, munmap(map, getpagesize()));

	/* Make sure that mprotect() also can't be used to gain write access. */
	errno = 0, ps = getpagesize();
	NEp(MAP_FAILED, (map = mmap(NULL, ps, PROT_READ, MAP_SHARED, sysrtld, 0)));
	if (mprotect(map, ps, PROT_READ | PROT_WRITE) == 0) {
		/* Even though the mprotect succeeds, actually trying to modify the
		 * pointed-to memory sees the #PF handler throw E_FSERROR_READONLY. */
		TRY {
			memset(map, 0xff, ps);
			assert_failed("Shouldn't get here");
		} EXCEPT {
			/* This `E_FSERROR_READONLY' is thrown as  the result of an attempt  to
			 * write-fault a memory mapping of a read-only file. It originates from
			 * the kernel  function `mfault_or_unlock()',  whose documentation  has
			 * some more details on this behavior. */
			assert(was_thrown(E_FSERROR_READONLY));
		}
	} else {
		/* EACCES in case `sysrtld' is IO_RDONLY */
		EQd(errno, EACCES);
	}
	EQd(0, munmap(map, ps));

	if (sysrtld != AT_FDSYSRTLD)
		EQd(0, close(sysrtld));
	errno = 0;
	EQd(-1, close(AT_FDSYSRTLD));
	EQd(errno, EBADF); /* Cannot be closed */

	/* Make sure that mmap(MAP_SHARED) on an IO_RDONLY handle works as expected.
	 * In this case, the  expected exception is E_INVALID_HANDLE_OPERATION  with
	 * op-code  `E_INVALID_HANDLE_OPERATION_MMAP_SHARED_RDWR',  which  is   then
	 * translated to `EACCES' (matching posix behavior) */
	errno = 0;
	EQp(MAP_FAILED, (map = mmap(NULL, ps, PROT_READ | PROT_WRITE, MAP_SHARED, AT_FDSYSRTLD, 0)));
	EQd(errno, EACCES);
	NEp(MAP_FAILED, (map = mmap(NULL, ps, PROT_READ, MAP_SHARED, AT_FDSYSRTLD, 0)));

	/* Try to mprotect() a memory mapping created by PROT_READ+MAP_SHARED of a  non-IO_RDWR
	 * file descriptor must fail with EACCES. (E_INVALID_HANDLE_OPERATION_MMAP_SHARED_RDWR)
	 *
	 * s.a. kernel:MNODE_F_PDENYWRITE */
	errno = 0;
	EQd(-1, mprotect(map, ps, PROT_READ | PROT_WRITE));
	EQd(errno, EACCES);
	EQd(0, munmap(map, ps));

}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_SYSTEM_RTLD_RO_C */
