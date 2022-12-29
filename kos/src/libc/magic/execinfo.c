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
%(c_prefix){
/* (#) Portability: GNU C Library (/debug/execinfo.h) */
/* (#) Portability: GNU Hurd      (/usr/include/execinfo.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/execinfo.h) */
/* (#) Portability: libc6         (/include/execinfo.h) */
/* (#) Portability: uClibc        (/include/execinfo.h) */
}

%[default:section(".text.crt{|.dos}.debug")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __USE_KOS
#include <bits/crt/format-printer.h>
#endif /* __USE_KOS */

#ifdef __CC__
__SYSDECL_BEGIN

}

%(auto_header){
#include <format-printer.h>
}


@@>> backtrace(3)
@@Create a  traceback of  up to  `size' instruction  pointers  from
@@the  calling function, their  caller, and so  forth. On KOS, this
@@information is constructed with the help of CFI  instrumentation,
@@and  the  functions  from  `<libunwind/...>'.  However,  on other
@@systems, this function is fairly dumb and relies on all traversed
@@code having been compiled with function frames enabled.
@@@return: * : The actual number of pointers written to `array' (always `<= size')
[[export_alias("__backtrace"), decl_include("<features.h>")]]
__STDC_INT_AS_SIZE_T backtrace([[out(return <= size)]] void **array,
                               __STDC_INT_AS_SIZE_T size);

@@>> backtrace_symbols(3)
@@Same as `backtrace_symbols_fmt(array, size, NULL)'
@@
@@The returned  pointer is  a size-element  long vector  of  strings
@@describing the  addresses  from  `array', and  should  be  freed()
@@using `free(3)'. Note however that you must _ONLY_ `free(return)',
@@and not the individual strings pointed-to by that vector!
@@@return: * :   A heap pointer to a vector of function names
@@@return: NULL: Insufficient heap memory available
[[export_alias("__backtrace_symbols"), decl_include("<features.h>")]]
[[requires_function(backtrace_symbols_fmt)]]
char **backtrace_symbols([[in(size)]] void *const *array,
                         __STDC_INT_AS_SIZE_T size) {
	return backtrace_symbols_fmt(array, size, NULL);
}

@@>> backtrace_symbols_fd(3)
@@Same as `backtrace_symbols_fd_fmt(array, size, fd, NULL)'
@@@return: 0 : Success
@@@return: -1: Error
[[export_alias("__backtrace_symbols_fd")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[requires_function(backtrace_symbols_fd_fmt)]]
int backtrace_symbols_fd([[in(size)]] void *const *array,
                         __STDC_INT_AS_SIZE_T size,
                         $fd_t fd) {
	return backtrace_symbols_fd_fmt(array, size, fd, NULL);
}


/* The following are extensions from FreeBSD (and NetBSD), but in their original
 * headers they're not put a restricted *_SOURCE namespace, so we don't  either. */

@@>> backtrace_symbols_fmt(3)
@@Format the given `array' of addresses into backtrace strings,
@@where   each  line  is  constructed  according  to  `format':
@@ - '%a': printf("%p", array[i])
@@ - '%n': printf("%s", NAME_OF_CONTAINING_FUNCTION(array[i]))
@@ - '%d': off = array[i] - START_OF_CONTAINING_FUNCTION(array[i]); printf("%#tx", off)
@@ - '%D': off = array[i] - START_OF_CONTAINING_FUNCTION(array[i]); if (off) printf("%+#tx", off)
@@ - '%f': printf("%s", dlmodulename(dlgethandle(array[i])))
@@ - '%%': A single '%'
@@ - ...:  Anything else is copied from `format' as-is.
@@When `format == NULL', use "%a <%n%D> at %f" instead
@@
@@The returned  pointer is  a size-element  long vector  of  strings
@@describing the  addresses  from  `array', and  should  be  freed()
@@using `free(3)'. Note however that you must _ONLY_ `free(return)',
@@and not the individual strings pointed-to by that vector!
@@@return: * :   A heap pointer to a vector of function names
@@@return: NULL: Insufficient heap memory available
[[export_alias("__backtrace_symbols"), decl_include("<features.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE_FORMAT_APRINTF_DATA)]]
[[requires_function(backtrace_symbol_printf, format_aprintf_alloc,
                    format_aprintf_pack, format_aprintf_printer)]]
char **backtrace_symbols_fmt([[in(size)]] void *const *array,
                             __STDC_INT_AS_SIZE_T size,
                             [[in_opt]] char const *format) {
	char **result;
	struct format_aprintf_data printer;
	size_t i;
	printer.@ap_base@  = NULL;
	printer.@ap_avail@ = 0;
	printer.@ap_used@  = 0;

	/* Make space for the string array itself. */
	if unlikely(!format_aprintf_alloc(&printer,
	                                  (((size + 1) * sizeof(char *)) +
	                                   sizeof(char) - 1) /
	                                  sizeof(char)))
		goto err;

	for (i = 0; i < (size_t)size; ++i) {
		if (i != 0) {
			/* NUL-terminate  the  preceding string  (the last  string will
			 * be automatically NUL-terminated by `format_aprintf_pack()'!) */
			if unlikely(format_aprintf_printer(&printer, "", 1) < 0)
				goto err;
		}
		/* Print the backtrack string. */
		if unlikely(backtrace_symbol_printf(&format_aprintf_printer,
		                                    &printer,
		                                    array[i],
		                                    format) < 0)
			goto err;
	}

	/* Pack together the buffer */
	result = (char **)format_aprintf_pack(&printer, NULL);
	if likely(result) {
		char *strings;
		strings = (char *)((byte_t *)result + ((size_t)size * sizeof(char *)));
		for (i = 0; i < (size_t)size; ++i) {
			result[i] = strings;
			strings = strend(strings) + 1;
		}
		result[i] = NULL;
	}
	return result;
err:
@@pp_if $has_function(free)@@
	free(printer.@ap_base@);
@@pp_endif@@
	return NULL;
}

@@>> backtrace_symbols_fd_fmt(3)
@@Same as `backtrace_symbols_fmt()', but rather than return a vector
@@of  symbol  names, print  the names  directly  to `fd',  such that
@@one function  name will  be written  per line,  with `size'  lines
@@written in total.
@@@return: 0 : Success
@@@return: -1: Error
[[export_alias("__backtrace_symbols_fd")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[impl_include("<bits/types.h>")]]
[[requires_function(write_printer, backtrace_symbol_printf)]]
int backtrace_symbols_fd_fmt([[in(size)]] void *const *array,
                             __STDC_INT_AS_SIZE_T size, $fd_t fd,
                             [[in_opt]] char const *format) {
	size_t i;
	void *fdarg;
	fdarg = (void *)(uintptr_t)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))fd;
	for (i = 0; i < (size_t)size; ++i) {
		if unlikely(backtrace_symbol_printf(&write_printer, fdarg, array[i], format) < 0)
			goto err;
		if unlikely(write_printer(fdarg, "\n", 1) < 0)
			goto err;
	}
	return 0;
err:
	return -1;
}


%
%#ifdef __USE_KOS
%{
#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */
}


@@>> backtrace_symbol_printf(3)
@@Print the formatted representation of `address' to `printer'
@@ - The used format is `format' (or "%a <%n%D> at %f" if NULL)
@@ - No trailing linefeed is printed
@@ - If debug information could not be loaded, use "???" for strings
@@@return: * : pformatprinter-compatible return value
[[decl_include("<hybrid/typecore.h>", "<bits/crt/format-printer.h>")]]
ssize_t backtrace_symbol_printf([[nonnull]] $pformatprinter printer, void *arg,
                                void const *address, [[in_opt]] char const *format);

%#endif /* __USE_KOS */



%{

__SYSDECL_END
#endif /* __CC__ */

}
