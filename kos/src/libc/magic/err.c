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

%[define_replacement(errno_t = __errno_t)]
%[default_impl_section(.text.crt.error)]

%{

}
%#ifdef __CC__

@@Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n'
[ATTR_LIBC_PRINTF(1, 2)][cp_stdio]
warn:(char const *format, ...) %{auto_block(printf(vwarn))}

[doc_alias(warn)][ATTR_LIBC_PRINTF(1, 0)][same_impl][cp_stdio]
[dependency_include(<parts/errno.h>)]
[requires_include(<local/stdstreams.h>)]
[requires_include(<local/program_invocation_name.h>)]
[requires(!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) &&
          $has_function(fprintf) && $has_function(vfprintf) &&
          $has_function(strerror))]
vwarn:(char const *format, va_list args) {
	int errval = @__libc_geterrno_or@(0);
#if (@@yield $has_function("flockfile")@@) && (@@yield $has_function("funlockfile")@@)
	flockfile(@__LOCAL_stderr@);
#endif
	fprintf(@__LOCAL_stderr@, "%s: ", @__LOCAL_program_invocation_short_name@);
	if (format) {
		vfprintf(@__LOCAL_stderr@, format, args);
		fprintf(@__LOCAL_stderr@, ": %s\n", strerror(errval));
	} else {
		fprintf(@__LOCAL_stderr@, "%s\n", strerror(errval));
	}
#if (@@yield $has_function("flockfile")@@) && (@@yield $has_function("funlockfile")@@)
	funlockfile(@__LOCAL_stderr@);
#endif
}


@@Print to stderr: `<program_invocation_short_name>: <format...>\n'
[ATTR_LIBC_PRINTF(1, 2)][cp_stdio]
warnx:(char const *format, ...) %{auto_block(printf(vwarnx))}

[doc_alias(warnx)][ATTR_LIBC_PRINTF(1, 0)][same_impl][cp_stdio]
[requires_include(<local/stdstreams.h>)]
[requires_include(<local/program_invocation_name.h>)]
[requires(!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) &&
          $has_function(fprintf) && $has_function(vfprintf) && $has_function(fputc))]
vwarnx:(char const *format, va_list args) {
#if (@@yield $has_function("flockfile")@@) && (@@yield $has_function("funlockfile")@@)
	flockfile(@__LOCAL_stderr@);
#endif
	fprintf(@__LOCAL_stderr@, "%s: ", @__LOCAL_program_invocation_short_name@);
	if (format)
		vfprintf(@__LOCAL_stderr@, format, args);
	fputc('\n', @__LOCAL_stderr@);
#if (@@yield $has_function("flockfile")@@) && (@@yield $has_function("funlockfile")@@)
	funlockfile(@__LOCAL_stderr@);
#endif
}


@@Same as `warn()', but follow up by calling `exit(status)'
[ATTR_NORETURN][ATTR_LIBC_PRINTF(2, 3)][throws]
err:(int status, char const *format, ...) %{auto_block(printf(verr))}

[doc_alias(err)][ATTR_NORETURN][ATTR_LIBC_PRINTF(2, 0)][same_impl][throws]
[requires($has_function(vwarn) && $has_function(exit))]
verr:(int status, char const *format, va_list args) {
	vwarn(format, args);
	exit(status);
}

@@Same as `warnx()', but follow up by calling `exit(status)'
[ATTR_NORETURN][ATTR_LIBC_PRINTF(2, 3)][throws]
errx:(int status, char const *format, ...) %{auto_block(printf(verrx))}

[doc_alias(err)][ATTR_NORETURN][ATTR_LIBC_PRINTF(2, 0)][same_impl][throws]
[requires($has_function(vwarnx) && $has_function(exit))]
verrx:(int status, char const *format, va_list args) {
	vwarnx(format, args);
	exit(status);
}


%#endif /* __CC__ */
%{

}

