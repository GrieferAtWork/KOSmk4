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
#ifndef GUARD_MODPROCFS_UTIL_C
#define GUARD_MODPROCFS_UTIL_C 1
#define _KOS_SOURCE 1

#include "util.h"

#include <kernel/compiler.h>

#include <fs/node.h>
#include <kernel/except.h>

#include <hybrid/atomic.h>
#include <hybrid/limitcore.h>

#include <kos/except/reason/inval.h>
#include <kos/types.h>

#include <format-printer.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unicode.h>

#include "procfs.h"

DECL_BEGIN

/* Printer for `struct procfs_singleton_reg_txt_data'-style INodes */
INTERN NONNULL((1, 2)) ssize_t KCALL
ProcFs_RegTxtDataPrinter(struct regular_node *__restrict self,
                         pformatprinter printer, void *arg) {
	struct procfs_singleton_reg_txt_data *fsdata;
	fsdata = (struct procfs_singleton_reg_txt_data *)self->i_fsdata;
	return (*printer)(arg, fsdata->psr_text, fsdata->psr_textlen);
}

/* Printer for `struct procfs_singleton_reg_ext_data'-style INodes */
INTERN NONNULL((1, 2)) ssize_t KCALL
ProcFs_RegExtDataPrinter(struct regular_node *__restrict self,
                         pformatprinter printer, void *arg) {
	struct procfs_singleton_reg_ext_data *fsdata;
	fsdata = (struct procfs_singleton_reg_ext_data *)self->i_fsdata;
	return format_printf(printer, arg, "%s\n", fsdata->psr_string);
}




INTERN WUNUSED NONNULL((1, 2)) ssize_t
NOTHROW(KCALL ProcFS_SubStringPrinter)(void *arg,
                                       char const *__restrict data,
                                       size_t datalen) {
	ProcFS_SubStringPrinterData *closure;
	ssize_t result = (ssize_t)datalen;
	closure = (ProcFS_SubStringPrinterData *)arg;
	if (closure->ssp_offset != 0) {
		if (closure->ssp_offset >= datalen) {
			closure->ssp_offset -= datalen;
			goto done;
		}
		data    += closure->ssp_offset;
		datalen -= closure->ssp_offset;
		closure->ssp_offset = 0;
	}
	if (datalen >= closure->ssp_size) {
		memcpy(closure->ssp_buf, data, closure->ssp_size, sizeof(char));
		closure->ssp_buf += closure->ssp_size;
		closure->ssp_size = 0;
		return __SSIZE_MIN__; /* Stop printing (we've gotten everything) */
	}
	/* Print everything */
	memcpy(closure->ssp_buf, data, datalen, sizeof(char));
	closure->ssp_size -= datalen;
	closure->ssp_buf  += datalen;
done:
	return result;
}


/* Print a string "0\n" or "1\n" depending on `value' */
INTERN NONNULL((1)) ssize_t FCALL
ProcFS_PrintBool(pformatprinter printer, void *arg, bool value) {
	char buf[2];
	buf[0] = value ? '1' : '0';
	buf[1] = '\n';
	return (*printer)(arg, buf, 2);
}

INTERN NONNULL((1)) ssize_t FCALL
ProcFS_PrintU32(pformatprinter printer, void *arg, u32 value) {
	return format_printf(printer, arg, "%" PRIu32 "\n", value);
}

INTERN NONNULL((1)) ssize_t FCALL
ProcFS_PrintU64(pformatprinter printer, void *arg, u64 value) {
	return format_printf(printer, arg, "%" PRIu64 "\n", value);
}


/* Parse a given user-space buffer from being a string `0' or `1', which
 * may optionally be surrounded by space characters that are automatically
 * stripped prior to being parsed.
 * If the buffer contains anything other than `[SPC]0|1[SPC]', then a
 * `E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER'
 * exception is thrown. */
INTERN NONNULL((1)) bool FCALL
ProcFS_ParseBool(USER CHECKED void const *buf, size_t bufsize)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE, E_BUFFER_TOO_SMALL) {
	USER CHECKED char const *endp;
	bool result;
	char mode;
	endp = (USER CHECKED char const *)buf + bufsize;
	while (endp > (USER CHECKED char const *)buf &&
	       unicode_isspace(endp[-1]))
		--endp;
	while ((USER CHECKED char const *)buf < endp &&
	       unicode_isspace(((char const *)buf)[0]))
		buf = (char *)buf + 1;
	bufsize = (size_t)(endp - (USER CHECKED char const *)buf);
	if (bufsize != 1)
		THROW(E_BUFFER_TOO_SMALL, 1, bufsize);
	mode = ATOMIC_READ(*(char *)buf);
	if (mode == '0')
		result = false;
	else if (mode == '1')
		result = true;
	else {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER,
		      (uintptr_t)(mode - '0')); /* This may underflow, but that's user-space problem! */
	}
	return result;
}

INTERN NONNULL((1)) u32 FCALL
ProcFS_ParseU32(USER CHECKED void const *buf, size_t bufsize, u32 minval, u32 maxval)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE, E_BUFFER_TOO_SMALL) {
	char intbuf[16];
	USER CHECKED char const *endp;
	USER CHECKED char *real_endp;
	u32 result;
	endp = (USER CHECKED char const *)buf + bufsize;
	while (endp > (USER CHECKED char const *)buf &&
	       unicode_isspace(endp[-1]))
		--endp;
	while ((USER CHECKED char const *)buf < endp &&
	       unicode_isspace(((char const *)buf)[0]))
		buf = (char *)buf + 1;
	bufsize = (size_t)(endp - (USER CHECKED char const *)buf);
	if (!bufsize || bufsize >= COMPILER_LENOF(intbuf))
		THROW(E_BUFFER_TOO_SMALL, 1, bufsize);
	COMPILER_READ_BARRIER();
	memcpy(intbuf, buf, bufsize);
	COMPILER_READ_BARRIER();
	intbuf[bufsize] = 0;
	result = strtou32(intbuf, &real_endp, 10);
	if (real_endp != intbuf + bufsize)
		THROW(E_BUFFER_TOO_SMALL, (size_t)(real_endp - intbuf), bufsize);
	if (result < minval || result > maxval) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER,
		      (uintptr_t)result);
	}
	return result;
}

INTERN NONNULL((1)) u64 FCALL
ProcFS_ParseU64(USER CHECKED void const *buf, size_t bufsize, u64 minval, u64 maxval)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE, E_BUFFER_TOO_SMALL) {
	char intbuf[32];
	USER CHECKED char const *endp;
	USER CHECKED char *real_endp;
	u64 result;
	endp = (USER CHECKED char const *)buf + bufsize;
	while (endp > (USER CHECKED char const *)buf &&
	       unicode_isspace(endp[-1]))
		--endp;
	while ((USER CHECKED char const *)buf < endp &&
	       unicode_isspace(((char const *)buf)[0]))
		buf = (char *)buf + 1;
	bufsize = (size_t)(endp - (USER CHECKED char const *)buf);
	if (!bufsize || bufsize >= COMPILER_LENOF(intbuf))
		THROW(E_BUFFER_TOO_SMALL, 1, bufsize);
	COMPILER_READ_BARRIER();
	memcpy(intbuf, buf, bufsize);
	COMPILER_READ_BARRIER();
	intbuf[bufsize] = 0;
	result = strtou64(intbuf, &real_endp, 10);
	if (real_endp != intbuf + bufsize)
		THROW(E_BUFFER_TOO_SMALL, (size_t)(real_endp - intbuf), bufsize);
	if (result < minval || result > maxval) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER,
		      (uintptr_t)result); /* XXX: This may cause the value to be truncated... */
	}
	return result;
}



DECL_END

#endif /* !GUARD_MODPROCFS_UTIL_C */
