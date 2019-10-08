/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODPROCFS_UTIL_C
#define GUARD_MODPROCFS_UTIL_C 1

#include "util.h"

#include <kernel/compiler.h>

#include <hybrid/limitcore.h>

#include <kos/types.h>

#include <format-printer.h>
#include <string.h>

DECL_BEGIN

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
		memcpy(closure->ssp_buf, data, closure->ssp_size);
		closure->ssp_buf += closure->ssp_size;
		closure->ssp_size = 0;
		return __SSIZE_MIN__; /* Stop printing (we've gotten everything) */
	}
	/* Print everything */
	memcpy(closure->ssp_buf, data, datalen);
	closure->ssp_size -= datalen;
	closure->ssp_buf  += datalen;
done:
	return result;
}


DECL_END

#endif /* !GUARD_MODPROCFS_UTIL_C */
