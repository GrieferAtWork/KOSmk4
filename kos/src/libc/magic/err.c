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

%[define_replacement(errno_t = __errno_t)]
%[default:section(".text.crt{|.dos}.error")]

%(auto_source){
#include "../libc/globals.h"
}

%{
#include <features.h>
#include <kos/anno.h>
#include <bits/types.h>

}
%#ifdef __CC__
%
%__SYSDECL_BEGIN
%

@@Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n'
[[cp_stdio, ATTR_LIBC_PRINTF(1, 2)]]
void warn(char const *format, ...)
	%{printf("vwarn")}

[[cp_stdio, doc_alias(warn), ATTR_LIBC_PRINTF(1, 0)]]
[[requires_function(vwarnc), impl_include("<parts/errno.h>")]]
void vwarn(char const *format, $va_list args) {
	vwarnc(__libc_geterrno_or(0), format, args);
}


%
%#ifdef __USE_BSD
@@Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n'
[[guard, cp_stdio, ATTR_LIBC_PRINTF(1, 2), decl_include("<bits/types.h>")]]
void warnc($errno_t used_errno, char const *format, ...)
	%{printf("vwarnc")}

[[guard, cp_stdio, doc_alias("warnc"), ATTR_LIBC_PRINTF(1, 0)]]
[[impl_include("<local/stdstreams.h>"), decl_include("<bits/types.h>")]]
[[impl_include("<local/program_invocation_name.h>")]]
[[requires_include("<__crt.h>", "<local/program_invocation_name.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) &&
           $has_function(fprintf) && $has_function(vfprintf) && $has_function(strerror))]]
void vwarnc($errno_t used_errno, char const *format, $va_list args) {
@@pp_if $has_function(flockfile) && $has_function(funlockfile)@@
	flockfile(stderr);
@@pp_endif@@
	fprintf(stderr, "%s: ", __LOCAL_program_invocation_short_name);
	if (format) {
		vfprintf(stderr, format, args);
		fprintf(stderr, ": %s\n", strerror(used_errno));
	} else {
		fprintf(stderr, "%s\n", strerror(used_errno));
	}
@@pp_if $has_function(flockfile) && $has_function(funlockfile)@@
	funlockfile(stderr);
@@pp_endif@@
}
%#endif /* __USE_BSD */
%


@@Print to stderr: `<program_invocation_short_name>: <format...>\n'
[[cp_stdio, ATTR_LIBC_PRINTF(1, 2)]]
void warnx(char const *format, ...)
	%{printf("vwarnx")}

[[cp_stdio, doc_alias("warnx"), ATTR_LIBC_PRINTF(1, 0)]]
[[impl_include("<local/stdstreams.h>")]]
[[impl_include("<local/program_invocation_name.h>")]]
[[requires_include("<__crt.h>", "<local/program_invocation_name.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) &&
           $has_function(fprintf) && $has_function(vfprintf) && $has_function(fputc))]]
void vwarnx(char const *format, $va_list args) {
@@pp_if $has_function(flockfile) && $has_function(funlockfile)@@
	flockfile(stderr);
@@pp_endif@@
	fprintf(stderr, "%s: ", @__LOCAL_program_invocation_short_name@);
	if (format)
		vfprintf(stderr, format, args);
	fputc('\n', stderr);
@@pp_if $has_function(flockfile) && $has_function(funlockfile)@@
	funlockfile(stderr);
@@pp_endif@@
}


@@Same as `warn()', but follow up by calling `exit(status)'
[[throws, ATTR_NORETURN, ATTR_LIBC_PRINTF(2, 3)]]
void err(int status, char const *format, ...)
	%{printf("verr")}

[[doc_alias("err"), throws, ATTR_NORETURN, ATTR_LIBC_PRINTF(2, 0)]]
[[requires_function(verrc), impl_include("<parts/errno.h>")]]
void verr(int status, char const *format, $va_list args) {
	verrc(status, __libc_geterrno_or(0), format, args);
}

%
%#ifdef __USE_BSD
@@Same as `warnc()', but follow up by calling `exit(status)'
[[guard, throws, ATTR_NORETURN, ATTR_LIBC_PRINTF(2, 3)]]
[[decl_include("<bits/types.h>")]]
void errc(int status, $errno_t used_errno, char const *format, ...)
	%{printf("verrc")}

[[guard, doc_alias("errc"), throws, ATTR_NORETURN, ATTR_LIBC_PRINTF(2, 0)]]
[[decl_include("<bits/types.h>")]]
[[requires_function(vwarnc, exit)]]
void verrc(int status, $errno_t used_errno, char const *format, $va_list args) {
	vwarnc(used_errno, format, args);
	exit(status);
}
%#endif /* __USE_BSD */
%

@@Same as `warnx()', but follow up by calling `exit(status)'
[[throws, ATTR_NORETURN, ATTR_LIBC_PRINTF(2, 3)]]
[[requires_function(verrx)]]
void errx(int status, char const *format, ...) {
	va_list args;
	va_start(args, format);
	verrx(status, format, args);
}

[[doc_alias("errx"), throws, ATTR_NORETURN, ATTR_LIBC_PRINTF(2, 0)]]
[[requires_function(vwarnx, exit)]]
void verrx(int status, char const *format, $va_list args) {
	vwarnx(format, args);
	exit(status);
}

%
%__SYSDECL_END
%
%#endif /* __CC__ */
%{

}

