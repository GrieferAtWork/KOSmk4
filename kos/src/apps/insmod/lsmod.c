/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_INSMOD_LSMOD_C
#define GUARD_APPS_INSMOD_LSMOD_C 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#include <kos/hop/driver.h>
#include <kos/io.h>
#include <kos/kernel/types.h>
#include <kos/ksysctl.h>
#include <kos/malloc.h>
#include <kos/types.h>

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

PRIVATE fd_t OpenDriverList(void) {
	struct hop_openfd hfd;
	hfd.of_mode  = HOP_OPENFD_MODE_AUTO;
	hfd.of_flags = IO_CLOEXEC;
	return KSysctl(KSYSCTL_DRIVER_LSMOD, &hfd);
}

PRIVATE size_t
GetDriverStringBuf(fd_t driver, syscall_ulong_t cmd,
                   u64 index, char *buf, size_t buflen) {
	struct hop_driver_string h;
	memset(&h, 0, sizeof(h));
	h.ds_struct_size = sizeof(h);
	h.ds_buf         = buf;
	h.ds_size        = buflen;
	h.ds_index       = index;
	Hop(driver, cmd, &h);
	return h.ds_size;
}

PRIVATE char *
GetDriverString(fd_t driver,
                syscall_ulong_t cmd, u64 index,
                size_t *pstringlen_with_nul) {
	size_t buflen = 256;
	size_t new_buflen;
	char *buf;
	buf = (char *)Malloc(buflen);
again_getpath:
	new_buflen = GetDriverStringBuf(driver, cmd, index, buf, buflen);
	if (new_buflen > buflen) {
		buf    = (char *)Realloc(buf, new_buflen);
		buflen = new_buflen;
		goto again_getpath;
	} else if (new_buflen < buflen) {
		char *newbuf;
		newbuf = (char *)realloc(buf, new_buflen);
		if likely(newbuf)
			buf = newbuf;
	}
	if (pstringlen_with_nul)
		*pstringlen_with_nul = new_buflen;
	return buf;
}

PRIVATE fd_t
OpenDriverDependency(fd_t driver, syscall_ulong_t cmd, u64 index) {
	struct hop_driver_open_dependency d;
	memset(&d, 0, sizeof(d));
	d.dod_struct_size     = sizeof(d);
	d.dod_depno           = index;
	d.dod_result.of_mode  = HOP_OPENFD_MODE_AUTO;
	d.dod_result.of_flags = IO_CLOEXEC;
	return Hop(driver, cmd, &d);
}


PRIVATE void PrinterDriverInformation(fd_t driver) {
	struct hop_driver_stat st;
	char *temp;
	u64 i;
	memset(&st, 0, sizeof(st));
	st.ds_struct_size = sizeof(st);
	Hop(driver, HOP_DRIVER_STAT, &st);
	temp = GetDriverString(driver,
	                       st.ds_flags & HOP_DRIVER_FLAG_HAS_FILENAME
	                       ? HOP_DRIVER_GET_FILENAME
	                       : HOP_DRIVER_GET_NAME,
	                       0, NULL);
	printf("%s:[", temp);
	free(temp);
	for (i = 0; i < st.ds_argc; ++i) {
		char *arg;
		arg = GetDriverString(driver, HOP_DRIVER_GET_ARGV, i, NULL);
		printf("%s%q", i == 0 ? "" : ", ", arg);
		free(arg);
	}
	printf("]\tdepends:[");
	for (i = 0; i < st.ds_depc; ++i) {
		fd_t dep;
		dep  = OpenDriverDependency(driver, HOP_DRIVER_OPEN_DEPENDENCY, i);
		temp = GetDriverString(dep, HOP_DRIVER_GET_NAME, 0, NULL);
		close(dep);
		printf("%s%s", i == 0 ? "" : ", ", temp);
		free(temp);
	}
	printf("]\n");
}


int main(int argc, char *argv[]) {
	fd_t drivers;
	u64 i, count;
	if (argc != 1) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
		return EXIT_FAILURE;
	}
	drivers = OpenDriverList();
	count   = 0;
	Hop(drivers, HOP_DRIVER_STATE_GET_COUNT, &count);
	for (i = 0; i < count; ++i) {
		fd_t depfd;
		depfd = OpenDriverDependency(drivers, HOP_DRIVER_STATE_GET_DRIVER, i);
		PrinterDriverInformation(depfd);
		close(depfd);
	}
	return EXIT_SUCCESS;
}


DECL_END

#endif /* !GUARD_APPS_INSMOD_LSMOD_C */
