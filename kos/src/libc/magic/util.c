/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: NetBSD  (/include/util.h) */
/* (#) Portability: OpenBSD (/lib/libutil/util.h) */
}

%[default:section(".text.crt{|.dos}.io.tty")]

%{

}%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/crt/util.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <sys/types.h>
)]%[insert:prefix(
#include <stdio.h>
)]%[insert:prefix(
#include <pwd.h>
)]%[insert:prefix(
#include <termios.h>
)]%{

#ifdef __INTELLISENSE__
#include <bits/types/FILE.h>
#include <bits/types/size_t.h>
#endif /* __INTELLISENSE__ */

__SYSDECL_BEGIN

/* Options for the `dflags' argument to `opendev(3)' */
#if !defined(OPENDEV_PART) && defined(__OPENDEV_PART)
#define OPENDEV_PART __OPENDEV_PART /* Attempt to open a raw partition during expansion. */
#endif /* !OPENDEV_PART && __OPENDEV_PART */
#if !defined(OPENDEV_BLCK) && defined(__OPENDEV_BLCK)
#define OPENDEV_BLCK __OPENDEV_BLCK /* Open a block device (rather than a character device). */
#endif /* !OPENDEV_BLCK && __OPENDEV_BLCK */

/* Options for the `flags' argument to `fparseln(3)' */
#if !defined(FPARSELN_UNESCESC) && defined(__FPARSELN_UNESCESC)
#define FPARSELN_UNESCESC  __FPARSELN_UNESCESC  /* Remove escape before an escaped escape. */
#endif /* !FPARSELN_UNESCESC && __FPARSELN_UNESCESC */
#if !defined(FPARSELN_UNESCCONT) && defined(__FPARSELN_UNESCCONT)
#define FPARSELN_UNESCCONT __FPARSELN_UNESCCONT /* Remove escape before an escaped continuation. */
#endif /* !FPARSELN_UNESCCONT && __FPARSELN_UNESCCONT */
#if !defined(FPARSELN_UNESCCOMM) && defined(__FPARSELN_UNESCCOMM)
#define FPARSELN_UNESCCOMM __FPARSELN_UNESCCOMM /* Remove escape before an escaped comment. */
#endif /* !FPARSELN_UNESCCOMM && __FPARSELN_UNESCCOMM */
#if !defined(FPARSELN_UNESCREST) && defined(__FPARSELN_UNESCREST)
#define FPARSELN_UNESCREST __FPARSELN_UNESCREST /* Remove escape before some other character.*/
#endif /* !FPARSELN_UNESCREST && __FPARSELN_UNESCREST */
#if !defined(FPARSELN_UNESCALL) && defined(__FPARSELN_UNESCALL)
#define FPARSELN_UNESCALL __FPARSELN_UNESCALL /* Remove all escape prefixes */
#endif /* !FPARSELN_UNESCALL && __FPARSELN_UNESCALL */

#ifdef __CC__
struct utmp;
struct termios;
struct winsize;
struct iovec;

#ifndef __FILE_defined
#define __FILE_defined
typedef __FILE FILE;
#endif /* !__FILE_defined */

#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */


}


%[insert:extern(login)]
%[insert:extern(login_tty)]
%[insert:extern(logout)]
%[insert:extern(logwtmp)]

@@>> opendev(3)
@@@param: dflags: Set of `0 | OPENDEV_PART | OPENDEV_BLCK'
[[cp, wunused, decl_include("<features.h>", "<bits/types.h>")]]
$fd_t opendev([[in]] char const *path, $oflag_t oflags,
              __STDC_INT_AS_UINT_T dflags,
              [[out_opt]] char **realpath);

%[insert:extern(openpty)]
%[insert:extern(forkpty)]


@@>> fparseln(3)
@@Parse one line of text from `stream', whilst accounting for
@@special character escapes, as well as custom line-comments.
@@@param: plen:    When non-NULL, store `strlen(return)' here
@@@param: plineno: When non-NULL, incremented for every line-feed read from `stream'
@@@param: delim:   Special characters (use NUL to disable, and NULL to use defaults)
@@                    delim[0]: The escape character (defaults to '\\')
@@                    delim[1]: The line-continuation character (defaults to '\\')
@@                    delim[2]: The line-comment character (defaults to '#')
@@@param: flags:   Set of `FPARSELN_UNESC*'
@@@return: * :     Pointer to a heap-allocated, and pre-escaped (according to `flags')
@@                 line,  that must  be `free(3)'ed by  the caller once  they are done
@@                 using it.
@@                 If the result would be empty  as the result of `feof(stream)'  upon
@@                 return of this function, `strdup("")' will be returned. (i.e.  NULL
@@                 is only returned in case of an error; _NOT_ in case of end-of-file)
@@@return: NULL:   Error (s.a. `errno' and `ferror(stream)')
[[cp_stdio, wunused, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[impl_include("<asm/crt/stdio.h>", "<asm/os/stdio.h>", "<asm/crt/util.h>")]]
[[guard, requires_function(getline, fgetc, ungetc, realloc)]]
[[section(".text.crt{|.dos}.FILE.locked.read.read")]]
char *fparseln([[inout]] $FILE *stream,
               [[out_opt]] size_t *plen,
               [[inout_opt]] size_t *plineno,
               [[in_opt]] char const delim[3],
               __STDC_INT_AS_UINT_T flags) {
	char *result;
	size_t result_alloc;
	size_t result_length;
	char *linebuf_ptr;
	size_t linebuf_alloc;
	char delim_escape   = '\\';
	char delim_continue = '\\';
	char delim_comment  = '#';
	if (delim) {
		delim_escape   = delim[0];
		delim_continue = delim[1];
		delim_comment  = delim[2];
	}
	result        = NULL;
	result_alloc  = 0;
	result_length = 0;
	linebuf_ptr   = NULL;
	linebuf_alloc = 0;
	for (;;) {
		ssize_t line_len;
		size_t i;
again_getline:
		line_len = getline(&linebuf_ptr, &linebuf_alloc, stream);
		if unlikely(line_len < 0)
			goto err;
		if (!line_len)
			break; /* End-of-file! */
		if (plineno)
			++*plineno;
		/* Scan the read line for abnormalities */
		for (i = 0;; ++i) {
			char ch;
again_scan_linech_at_i:
			if (i >= (size_t)line_len) {
apped_current_line_and_stop:
				stream = NULL; /* Cause `apped_current_line_and_continue_or_stop' to stop scanning. */
				goto apped_current_line_and_continue_or_stop;
			}
			ch = linebuf_ptr[i];
			if (ch == delim_escape && delim_escape) {
				++i;
				if (i >= (size_t)line_len)
					goto apped_current_line_and_stop;
				ch = linebuf_ptr[i];
				if (ch == delim_escape && (flags & FPARSELN_UNESCESC)) {
do_erase_character_preceding_i_without_rescan:
					memmovedownc(&linebuf_ptr[i - 1],
					             &linebuf_ptr[i],
					             (size_t)line_len - i,
					             sizeof(char));
					--line_len;
					goto again_scan_linech_at_i;
				}
				if (ch == '\n' && (flags & FPARSELN_UNESCCONT) &&
				    delim_escape == delim_continue) {
					/* Escaped line-feed */
					--i;
deleted_escaped_newline_starting_at_i:
					line_len -= 2;
					memmovedownc(&linebuf_ptr[i],
					             &linebuf_ptr[i + 2],
					             (size_t)line_len - i,
					             sizeof(char));
continue_line_if_i_at_line_len:
					if likely(i >= (size_t)line_len) {
apped_current_line_and_continue_or_stop:
						if (!result) {
							/* Simple case: Inherit the already-allocated buffer from getline() */
							result        = linebuf_ptr;
							result_alloc  = linebuf_alloc;
							result_length = (size_t)line_len;
							linebuf_ptr   = NULL;
							linebuf_alloc = 0;
						} else {
							size_t total_length;
							/* Complicated case: Must append the line returned by `getline()' onto `result' */
							total_length = result_length + (size_t)line_len;
							if (total_length > result_alloc) {
								char *new_result;
								size_t new_alloc = result_alloc * 2;
								if (new_alloc < total_length)
									new_alloc = total_length + 1;
								new_result = (char *)realloc(result, new_alloc * sizeof(char));
								if unlikely(!new_result) {
									new_alloc = total_length + 1;
									new_result = (char *)realloc(result, new_alloc * sizeof(char));
									if unlikely(!new_result)
										goto err;
								}
								result       = new_result;
								result_alloc = new_alloc;
							}
							memcpyc(result + result_length, linebuf_ptr,
							        (size_t)line_len, sizeof(char));
							result_length = total_length;
						}
						/* `stream' is set to NULL to indicate that we're to stop scanning! */
						if (!stream)
							goto got_result;
						goto again_getline;
					}
					goto again_scan_linech_at_i;
				}
				/* Check if we're still supposed to unescape this character. */
				if ((flags & FPARSELN_UNESCREST) ||
				    ((flags & FPARSELN_UNESCCOMM) && ch == delim_comment && delim_comment))
					goto do_erase_character_preceding_i_without_rescan;
				continue;
			}
			if (ch == delim_continue && (i + 1) < (size_t)line_len &&
			    linebuf_ptr[i + 1] == '\n' && delim_continue) {
				if (flags & FPARSELN_UNESCCONT)
					goto deleted_escaped_newline_starting_at_i;
				++i;
				goto continue_line_if_i_at_line_len;
			}
			if (ch == delim_comment && delim_comment) {
				/* Got it! - The line actually stops here! */
				/* Check for special case: Escaped line-feed at the end of a comment */
				if ((size_t)line_len >= 2 && delim_continue &&
				    linebuf_ptr[(size_t)line_len - 2] == delim_continue &&
				    linebuf_ptr[(size_t)line_len - 1] == '\n') {
					/* Must keep  on scanning  (and discarding  characters) until  after
					 * the next  unescaped line-feed.  Note that  to prevent  additional
					 * heap allocations, we use fgetc() for this, rather than getline(),
					 * though  because of this we must still  account for all 3 types of
					 * linefeeds that exist.
					 * HINT: Right now, the previous call to getline() will have left
					 *       the given `stream' pointed at the first character of the
					 *       line succeeding the one returned by getline()! */
					for (;;) {
						int comment_ch = fgetc(stream);
again_check_ch_in_comment:
						if (comment_ch == EOF)
							break; /* end-of-file */
						if (comment_ch == delim_escape && delim_escape) {
							comment_ch = fgetc(stream);
							if (comment_ch == '\r' || comment_ch == '\n') {
								if (plineno)
									++*plineno;
								if (comment_ch == '\r') {
									comment_ch = fgetc(stream);
									if (comment_ch != '\n')
										ungetc(comment_ch, stream);
								}
								if (delim_escape == delim_continue)
									continue;
								break;
							}
							continue;
						}
						if (comment_ch == delim_continue && delim_continue) {
							comment_ch = fgetc(stream);
							if (comment_ch == '\r' || comment_ch == '\n') {
								if (plineno)
									++*plineno;
								if (comment_ch == '\r') {
									comment_ch = fgetc(stream);
									if (comment_ch != '\n')
										ungetc(comment_ch, stream);
								}
								continue; /* Escaped line-feed */
							}
							goto again_check_ch_in_comment;
						}
						if (comment_ch == '\n') {
do_increment_lineno_and_break_comment:
							if (plineno)
								++*plineno;
							break;
						}
						if (comment_ch == '\r') {
							comment_ch = fgetc(stream);
							if (comment_ch != '\n')
								ungetc(comment_ch, stream);
							goto do_increment_lineno_and_break_comment;
						}
					}
				}
				line_len = (ssize_t)i;
				goto apped_current_line_and_stop;
			}
		}
	}
got_result:
	/* Special case:  Nothing was  read (this  can
	 * happen if `stream' was at its EOF location) */
	if unlikely(!result) {
		result_length = 0;
		if likely(linebuf_ptr) {
			result       = linebuf_ptr;
			result_alloc = linebuf_alloc;
			linebuf_ptr  = NULL;
			/*linebuf_alloc = 0;*/ /* Not needed */
		} else {
@@pp_if $has_function(malloc)@@
			result = (char *)malloc(sizeof(char));
@@pp_else@@
			result = (char *)realloc(NULL, sizeof(char));
@@pp_endif@@
			if unlikely(!result)
				goto done;
			result_alloc = 1;
		}
	}
@@pp_if $has_function(free)@@
	free(linebuf_ptr);
@@pp_endif@@
	/* Trim a potential trailing line-feed */
	if (result_length && result[result_length - 1] == '\n')
		--result_length;
	/* Finalize the resulting buffer. */
	if (result_length + 1 < result_alloc) {
		/* Try to release unused memory. */
		char *new_result;
		new_result = (char *)realloc(result,
		                             (result_length + 1) *
		                             sizeof(char));
		if likely(new_result)
			result = new_result;
	}
	/* Ensure NUL-termination */
	result[result_length] = '\0';
	if (plen)
		*plen = result_length;
done:
	return result;
err:
@@pp_if $has_function(free)@@
	free(linebuf_ptr);
	free(result);
@@pp_endif@@
	return NULL;
}



%{

__SYSDECL_END
#endif /* __CC__ */


}
