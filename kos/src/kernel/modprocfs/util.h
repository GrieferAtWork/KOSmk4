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
#ifndef GUARD_MODPROCFS_UTIL_H
#define GUARD_MODPROCFS_UTIL_H 1

#include <kernel/compiler.h>

#include <kos/types.h>

#include <format-printer.h>

DECL_BEGIN

typedef struct {
	size_t             ssp_offset; /* Remaining number of bytes to skip */
	size_t             ssp_size;   /* Remaining number of bytes to print */
	USER CHECKED char *ssp_buf;    /* Destination buffer. */
} ProcFS_SubStringPrinterData;

INTDEF WUNUSED NONNULL((1, 2)) ssize_t
NOTHROW(KCALL ProcFS_SubStringPrinter)(void *arg,
                                       char const *__restrict data,
                                       size_t datalen);


DECL_END

#endif /* !GUARD_MODPROCFS_UTIL_H */
