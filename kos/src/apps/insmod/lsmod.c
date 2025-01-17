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
#ifndef GUARD_APPS_INSMOD_LSMOD_C
#define GUARD_APPS_INSMOD_LSMOD_C 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#include <kos/io.h>
#include <kos/ioctl/mod.h>
#include <kos/kernel/types.h>
#include <kos/ksysctl.h>
#include <kos/malloc.h>
#include <kos/sys/ioctl.h>
#include <kos/types.h>

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

PRIVATE fd_t OpenDriverList(void) {
	struct openfd hfd;
	hfd.of_mode  = OPENFD_MODE_AUTO;
	hfd.of_flags = IO_CLOEXEC;
	return KSysctl(KSYSCTL_DRIVER_LSMOD, &hfd);
}

PRIVATE size_t
GetDriverStringBuf(fd_t driver, u64 index, char *buf, size_t buflen) {
	struct mod_string h;
	bzero(&h, sizeof(h));
	h.ms_buf   = buf;
	h.ms_size  = buflen;
	h.ms_index = index;
	Ioctl(driver, MOD_IOC_GETSTRING, &h);
	return h.ms_size;
}

PRIVATE char *
GetDriverString(fd_t driver, u64 index,
                size_t *pstringlen_with_nul) {
	size_t buflen = 256;
	size_t new_buflen;
	char *buf;
	buf = (char *)Malloc(buflen);
again_getpath:
	new_buflen = GetDriverStringBuf(driver, index, buf, buflen);
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
OpenDriverObject(fd_t driver, u64 index) {
	struct mod_object d;
	bzero(&d, sizeof(d));
	d.mo_index           = index;
	d.mo_result.of_mode  = OPENFD_MODE_AUTO;
	d.mo_result.of_flags = IO_CLOEXEC;
	return Ioctl(driver, MOD_IOC_GETOBJECT, &d);
}


PRIVATE void PrinterDriverInformation(fd_t driver) {
	u64 i, count;
	char *temp, *iter;
	temp = GetDriverString(driver, MOD_STR_FILENAME, NULL);
	if (!*temp) {
		free(temp);
		temp = GetDriverString(driver, MOD_STR_NAME, NULL);
		if (!*temp) {
			free(temp);
			temp = strdup("?");
		}
	}
	printf("%s:[", temp);
	free(temp);
	temp = GetDriverString(driver, MOD_STR_CMDLINE, NULL);
	for (iter = temp; *iter; iter = strend(iter) + 1)
		printf("%s%q", iter == temp ? "" : ", ", iter);
	free(temp);
	printf("]\tdepends:[");
	count = 0;
	Ioctl(driver, MOD_IOC_GETCOUNT, &count);
	for (i = 0; i < count; ++i) {
		fd_t dep;
		dep  = OpenDriverObject(driver, i);
		temp = GetDriverString(dep, MOD_STR_NAME, NULL);
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
	Ioctl(drivers, MOD_IOC_GETCOUNT, &count);
	for (i = 0; i < count; ++i) {
		fd_t depfd;
		depfd = OpenDriverObject(drivers, i);
		PrinterDriverInformation(depfd);
		close(depfd);
	}
	return EXIT_SUCCESS;
}


DECL_END

#endif /* !GUARD_APPS_INSMOD_LSMOD_C */
