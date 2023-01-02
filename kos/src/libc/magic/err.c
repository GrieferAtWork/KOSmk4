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
%(c_prefix){
/* (#) Portability: Cygwin        (/winsup/cygwin/include/err.h) */
/* (#) Portability: DragonFly BSD (/include/err.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/err.h) */
/* (#) Portability: FreeBSD       (/include/err.h) */
/* (#) Portability: GNU C Library (/misc/err.h) */
/* (#) Portability: GNU Hurd      (/usr/include/err.h) */
/* (#) Portability: NetBSD        (/include/err.h) */
/* (#) Portability: OpenBSD       (/include/err.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/err.h) */
/* (#) Portability: diet libc     (/include/err.h) */
/* (#) Portability: libbsd        (/include/bsd/err.h) */
/* (#) Portability: libc6         (/include/err.h) */
/* (#) Portability: mintlib       (/include/err.h) */
/* (#) Portability: musl libc     (/include/err.h) */
/* (#) Portability: uClibc        (/include/err.h) */
}

%[define_replacement(errno_t = __errno_t)]
%[default:section(".text.crt{|.dos}.error")]

%(auto_source){
#include "../libc/globals.h"
}

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

/* These are defined in <libc/template/program_invocation_name.h> */
%[define_replacement(program_invocation_name       = __LOCAL_program_invocation_name)]
%[define_replacement(program_invocation_short_name = __LOCAL_program_invocation_short_name)]


@@>> warn(3), vwarn(3)
@@Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n'
[[cp_stdio]]
void warn([[in_opt, format("printf")]] char const *format, ...)
	%{printf("vwarn")}

[[cp_stdio, doc_alias("warn")]]
[[requires_function(vwarnc), impl_include("<libc/errno.h>")]]
void vwarn([[in_opt, format("printf")]] char const *format, $va_list args) {
	vwarnc(__libc_geterrno_or(0), format, args);
}


%
%#ifdef __USE_BSD
@@>> warnc(3), vwarnc(3)
@@Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n'
[[guard, cp_stdio, decl_include("<bits/types.h>")]]
void warnc($errno_t used_errno, [[in_opt, format("printf")]] char const *format, ...)
	%{printf("vwarnc")}

[[guard, cp_stdio, doc_alias("warnc")]]
[[impl_include("<libc/template/stdstreams.h>"), decl_include("<bits/types.h>")]]
[[impl_include("<libc/template/program_invocation_name.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) &&
           $has_function(fprintf) && $has_function(vfprintf) && $has_function(strerror))]]
void vwarnc($errno_t used_errno, [[in_opt, format("printf")]] char const *format, $va_list args) {
@@pp_if $has_function(flockfile) && $has_function(funlockfile)@@
	flockfile(stderr);
@@pp_endif@@
	fprintf(stderr, "%s: ", program_invocation_short_name);
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


@@>> warnx(3), vwarnx(3)
@@Print to stderr: `<program_invocation_short_name>: <format...>\n'
[[cp_stdio]]
void warnx([[in_opt, format("printf")]] char const *format, ...)
	%{printf("vwarnx")}

[[cp_stdio, doc_alias("warnx")]]
[[impl_include("<libc/template/stdstreams.h>")]]
[[impl_include("<libc/template/program_invocation_name.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) &&
           $has_function(fprintf) && $has_function(vfprintf) && $has_function(fputc))]]
void vwarnx([[in_opt, format("printf")]] char const *format, $va_list args) {
@@pp_if $has_function(flockfile) && $has_function(funlockfile)@@
	flockfile(stderr);
@@pp_endif@@
	fprintf(stderr, "%s: ", program_invocation_short_name);
	if (format)
		vfprintf(stderr, format, args);
	fputc('\n', stderr);
@@pp_if $has_function(flockfile) && $has_function(funlockfile)@@
	funlockfile(stderr);
@@pp_endif@@
}


@@>> err(3), verr(3)
@@Same as `warn()', but follow up by calling `exit(status)'
[[throws, noreturn]]
void err(int status, [[in_opt, format("printf")]] char const *format, ...)
	%{printf("verr")}

[[doc_alias("err"), throws, noreturn]]
[[requires_function(verrc), impl_include("<libc/errno.h>")]]
void verr(int status, [[in_opt, format("printf")]] char const *format, $va_list args) {
	verrc(status, __libc_geterrno_or(0), format, args);
}

%
%#ifdef __USE_BSD
@@>> errc(3), verrc(3)
@@Same as `warnc()', but follow up by calling `exit(status)'
[[guard, throws, noreturn, decl_include("<bits/types.h>")]]
void errc(int status, $errno_t used_errno, [[in_opt, format("printf")]] char const *format, ...)
	%{printf("verrc")}

[[guard, doc_alias("errc"), throws, noreturn]]
[[decl_include("<bits/types.h>")]]
[[requires_function(vwarnc, exit)]]
void verrc(int status, $errno_t used_errno, [[in_opt, format("printf")]] char const *format, $va_list args) {
	vwarnc(used_errno, format, args);
	exit(status);
}
%#endif /* __USE_BSD */
%

@@>> errx(3), verrx(3)
@@Same as `warnx()', but follow up by calling `exit(status)'
[[throws, noreturn, requires_function(verrx)]]
void errx(int status, [[in_opt, format("printf")]] char const *format, ...) {
	va_list args;
	va_start(args, format);
	verrx(status, format, args);
}

[[doc_alias("errx"), throws, noreturn, requires_function(vwarnx, exit)]]
void verrx(int status, [[in_opt, format("printf")]] char const *format, $va_list args) {
	vwarnx(format, args);
	exit(status);
}

%{

__SYSDECL_END
#endif /* __CC__ */

}
