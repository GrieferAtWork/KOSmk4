/* HASH CRC-32:0xa62b824f */
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
#ifndef GUARD_LIBC_AUTO_EXECINFO_C
#define GUARD_LIBC_AUTO_EXECINFO_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/execinfo.h"
#include "format-printer.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> backtrace_symbols(3)
 * Same as `backtrace_symbols_fmt(array, size, NULL)'
 *
 * The returned  pointer is  a size-element  long vector  of  strings
 * describing the  addresses  from  `array', and  should  be  freed()
 * using `free(3)'. Note however that you must _ONLY_ `free(return)',
 * and not the individual strings pointed-to by that vector!
 * @return: * :   A heap pointer to a vector of function names
 * @return: NULL: Insufficient heap memory available */
INTERN ATTR_SECTION(".text.crt.debug") ATTR_INS(1, 2) char **
NOTHROW_NCX(LIBCCALL libc_backtrace_symbols)(void *const *array,
                                             __STDC_INT_AS_SIZE_T size) {
	return libc_backtrace_symbols_fmt(array, size, NULL);
}
/* >> backtrace_symbols_fd(3)
 * Same as `backtrace_symbols_fd_fmt(array, size, fd, NULL)'
 * @return: 0 : Success
 * @return: -1: Error */
INTERN ATTR_SECTION(".text.crt.debug") ATTR_INS(1, 2) int
NOTHROW_NCX(LIBCCALL libc_backtrace_symbols_fd)(void *const *array,
                                                __STDC_INT_AS_SIZE_T size,
                                                fd_t fd) {
	return libc_backtrace_symbols_fd_fmt(array, size, fd, NULL);
}
#include <hybrid/typecore.h>
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_aprintf_data_defined */
/* >> backtrace_symbols_fmt(3)
 * Format the given `array' of addresses into backtrace strings,
 * where   each  line  is  constructed  according  to  `format':
 *  - '%a': printf("%p", array[i])
 *  - '%n': printf("%s", NAME_OF_CONTAINING_FUNCTION(array[i]))
 *  - '%d': off = array[i] - START_OF_CONTAINING_FUNCTION(array[i]); printf("%#tx", off)
 *  - '%D': off = array[i] - START_OF_CONTAINING_FUNCTION(array[i]); if (off) printf("%+#tx", off)
 *  - '%f': printf("%s", dlmodulename(dlgethandle(array[i])))
 *  - '%%': A single '%'
 *  - ...:  Anything else is copied from `format' as-is.
 * When `format == NULL', use "%a <%n%D> at %f" instead
 *
 * The returned  pointer is  a size-element  long vector  of  strings
 * describing the  addresses  from  `array', and  should  be  freed()
 * using `free(3)'. Note however that you must _ONLY_ `free(return)',
 * and not the individual strings pointed-to by that vector!
 * @return: * :   A heap pointer to a vector of function names
 * @return: NULL: Insufficient heap memory available */
INTERN ATTR_SECTION(".text.crt.debug") ATTR_INS(1, 2) ATTR_IN_OPT(3) char **
NOTHROW_NCX(LIBCCALL libc_backtrace_symbols_fmt)(void *const *array,
                                                 __STDC_INT_AS_SIZE_T size,
                                                 char const *format) {
	char **result;
	struct format_aprintf_data printer;
	size_t i;
	printer.ap_base  = NULL;
	printer.ap_avail = 0;
	printer.ap_used  = 0;

	/* Make space for the string array itself. */
	if unlikely(!libc_format_aprintf_alloc(&printer,
	                                  (((size + 1) * sizeof(char *)) +
	                                   sizeof(char) - 1) /
	                                  sizeof(char)))
		goto err;

	for (i = 0; i < (size_t)size; ++i) {
		if (i != 0) {
			/* NUL-terminate  the  preceding string  (the last  string will
			 * be automatically NUL-terminated by `format_aprintf_pack()'!) */
			if unlikely(libc_format_aprintf_printer(&printer, "", 1) < 0)
				goto err;
		}
		/* Print the backtrack string. */
		if unlikely(libc_backtrace_symbol_printf(&libc_format_aprintf_printer,
		                                    &printer,
		                                    array[i],
		                                    format) < 0)
			goto err;
	}

	/* Pack together the buffer */
	result = (char **)libc_format_aprintf_pack(&printer, NULL);
	if likely(result) {
		char *strings;
		strings = (char *)((byte_t *)result + ((size_t)size * sizeof(char *)));
		for (i = 0; i < (size_t)size; ++i) {
			result[i] = strings;
			strings = libc_strend(strings) + 1;
		}
		result[i] = NULL;
	}
	return result;
err:

	libc_free(printer.ap_base);

	return NULL;
}
#include <bits/types.h>
/* >> backtrace_symbols_fd_fmt(3)
 * Same as `backtrace_symbols_fmt()', but rather than return a vector
 * of  symbol  names, print  the names  directly  to `fd',  such that
 * one function  name will  be written  per line,  with `size'  lines
 * written in total.
 * @return: 0 : Success
 * @return: -1: Error */
INTERN ATTR_SECTION(".text.crt.debug") ATTR_INS(1, 2) ATTR_IN_OPT(4) int
NOTHROW_NCX(LIBCCALL libc_backtrace_symbols_fd_fmt)(void *const *array,
                                                    __STDC_INT_AS_SIZE_T size,
                                                    fd_t fd,
                                                    char const *format) {
	size_t i;
	void *fdarg;
	fdarg = (void *)(uintptr_t)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))fd;
	for (i = 0; i < (size_t)size; ++i) {
		if unlikely(libc_backtrace_symbol_printf(&libc_write_printer, fdarg, array[i], format) < 0)
			goto err;
		if unlikely(libc_write_printer(fdarg, "\n", 1) < 0)
			goto err;
	}
	return 0;
err:
	return -1;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__backtrace_symbols, libc_backtrace_symbols);
DEFINE_PUBLIC_ALIAS(backtrace_symbols, libc_backtrace_symbols);
DEFINE_PUBLIC_ALIAS(__backtrace_symbols_fd, libc_backtrace_symbols_fd);
DEFINE_PUBLIC_ALIAS(backtrace_symbols_fd, libc_backtrace_symbols_fd);
DEFINE_PUBLIC_ALIAS(__backtrace_symbols, libc_backtrace_symbols_fmt);
DEFINE_PUBLIC_ALIAS(backtrace_symbols_fmt, libc_backtrace_symbols_fmt);
DEFINE_PUBLIC_ALIAS(__backtrace_symbols_fd, libc_backtrace_symbols_fd_fmt);
DEFINE_PUBLIC_ALIAS(backtrace_symbols_fd_fmt, libc_backtrace_symbols_fd_fmt);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_EXECINFO_C */
