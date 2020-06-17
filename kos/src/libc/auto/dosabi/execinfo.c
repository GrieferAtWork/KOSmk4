/* HASH CRC-32:0x11e006c3 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_EXECINFO_C
#define GUARD_LIBC_AUTO_DOSABI_EXECINFO_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/execinfo.h"

DECL_BEGIN

/* Store up to SIZE return address of the current program state
 * in ARRAY and return the exact number of values stored */
INTERN ATTR_SECTION(".text.crt.dos.debug") NONNULL((1)) __STDC_INT_AS_UINT_T
NOTHROW_NCX(LIBDCALL libd_backtrace)(void **array,
                                     __STDC_INT_AS_UINT_T size) {
	return libc_backtrace(array, size);
}
/* Return names of functions from the backtrace list
 * in ARRAY in a newly malloc()ed memory block */
INTERN ATTR_SECTION(".text.crt.dos.debug") NONNULL((1)) char **
NOTHROW_NCX(LIBDCALL libd_backtrace_symbols)(void *const *array,
                                             __STDC_INT_AS_UINT_T size) {
	return libc_backtrace_symbols(array, size);
}
/* This function is similar to backtrace_symbols()
 * but it writes the result immediately to a file */
INTERN ATTR_SECTION(".text.crt.dos.debug") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_backtrace_symbols_fd)(void *const *array,
                                                __STDC_INT_AS_UINT_T size,
                                                fd_t fd) {
	libc_backtrace_symbols_fd(array, size, fd);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$__backtrace, libd_backtrace);
DEFINE_PUBLIC_ALIAS(DOS$backtrace, libd_backtrace);
DEFINE_PUBLIC_ALIAS(DOS$__backtrace_symbols, libd_backtrace_symbols);
DEFINE_PUBLIC_ALIAS(DOS$backtrace_symbols, libd_backtrace_symbols);
DEFINE_PUBLIC_ALIAS(DOS$__backtrace_symbols_fd, libd_backtrace_symbols_fd);
DEFINE_PUBLIC_ALIAS(DOS$backtrace_symbols_fd, libd_backtrace_symbols_fd);

#endif /* !GUARD_LIBC_AUTO_DOSABI_EXECINFO_C */
