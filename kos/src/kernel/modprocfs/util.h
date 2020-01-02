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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODPROCFS_UTIL_H
#define GUARD_MODPROCFS_UTIL_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/typecore.h>

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

/* Print a string "0\n" or "1\n" depending on `value' */
INTDEF NONNULL((1)) ssize_t FCALL ProcFS_PrintBool(pformatprinter printer, void *arg, bool value);
INTDEF NONNULL((1)) ssize_t FCALL ProcFS_PrintU32(pformatprinter printer, void *arg, u32 value);
INTDEF NONNULL((1)) ssize_t FCALL ProcFS_PrintU64(pformatprinter printer, void *arg, u64 value);

/* Parse a given user-space buffer from being a string `0' or `1', which
 * may optionally be surrounded by space characters that are automatically
 * stripped prior to being parsed.
 * If the buffer contains anything other than `[SPC]0|1[SPC]', then a
 * `E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER'
 * exception is thrown.
 * If the buffer has an incorrect length, then a `E_BUFFER_TOO_SMALL'
 * exception is thrown instead. */
INTDEF NONNULL((1)) bool FCALL
ProcFS_ParseBool(USER CHECKED void const *buf, size_t bufsize)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE, E_BUFFER_TOO_SMALL);
INTDEF NONNULL((1)) u32 FCALL
ProcFS_ParseU32(USER CHECKED void const *buf, size_t bufsize, u32 minval DFL(0), u32 maxval DFL((u32)-1))
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE, E_BUFFER_TOO_SMALL);
INTDEF NONNULL((1)) u64 FCALL
ProcFS_ParseU64(USER CHECKED void const *buf, size_t bufsize, u64 minval DFL(0), u64 maxval DFL((u64)-1))
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE, E_BUFFER_TOO_SMALL);

#if __SIZEOF_SIZE_T__ >= 8
#define ProcFS_ParseSize ProcFS_ParseU64
#define ProcFS_PrintSize ProcFS_PrintU64
#else /* __SIZEOF_SIZE_T__ >= 8 */
#define ProcFS_ParseSize ProcFS_ParseU32
#define ProcFS_PrintSize ProcFS_PrintU32
#endif /* __SIZEOF_SIZE_T__ < 8 */

#if __SIZEOF_INT__ >= 8
#define ProcFS_ParseUInt ProcFS_ParseU64
#define ProcFS_PrintUInt ProcFS_PrintU64
#else /* __SIZEOF_INT__ >= 8 */
#define ProcFS_ParseUInt ProcFS_ParseU32
#define ProcFS_PrintUInt ProcFS_PrintU32
#endif /* __SIZEOF_INT__ < 8 */


DECL_END

#endif /* !GUARD_MODPROCFS_UTIL_H */
