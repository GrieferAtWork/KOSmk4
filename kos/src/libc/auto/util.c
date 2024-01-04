/* HASH CRC-32:0xf921400 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_UTIL_C
#define GUARD_LIBC_AUTO_UTIL_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/util.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/crt/stdio.h>
#include <asm/os/stdio.h>
#include <asm/crt/util.h>
/* >> fparseln(3)
 * Parse one line of text from `stream', whilst accounting for
 * special character escapes, as well as custom line-comments.
 * @param: plen:    When non-NULL, store `strlen(return)' here
 * @param: plineno: When non-NULL, incremented for every line-feed read from `stream'
 * @param: delim:   Special characters (use NUL to disable, and NULL to use defaults)
 *                     delim[0]: The escape character (defaults to '\\')
 *                     delim[1]: The line-continuation character (defaults to '\\')
 *                     delim[2]: The line-comment character (defaults to '#')
 * @param: flags:   Set of `FPARSELN_UNESC*'
 * @return: * :     Pointer to a heap-allocated, and pre-escaped (according to `flags')
 *                  line,  that must  be `free(3)'ed by  the caller once  they are done
 *                  using it.
 *                  If the result would be empty  as the result of `feof(stream)'  upon
 *                  return of this function, `strdup("")' will be returned. (i.e.  NULL
 *                  is only returned in case of an error; _NOT_ in case of end-of-file)
 * @return: NULL:   Error (s.a. `errno' and `ferror(stream)') */
INTERN ATTR_SECTION(".text.crt.FILE.locked.read.read") WUNUSED ATTR_INOUT(1) ATTR_INOUT_OPT(3) ATTR_IN_OPT(4) ATTR_OUT_OPT(2) char *
NOTHROW_CB_NCX(LIBCCALL libc_fparseln)(FILE *stream,
                                       size_t *plen,
                                       size_t *plineno,
                                       char const delim[3],
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
		line_len = libc_getline(&linebuf_ptr, &linebuf_alloc, stream);
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
					libc_memmovedownc(&linebuf_ptr[i - 1],
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
					libc_memmovedownc(&linebuf_ptr[i],
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
								new_result = (char *)libc_realloc(result, new_alloc * sizeof(char));
								if unlikely(!new_result) {
									new_alloc = total_length + 1;
									new_result = (char *)libc_realloc(result, new_alloc * sizeof(char));
									if unlikely(!new_result)
										goto err;
								}
								result       = new_result;
								result_alloc = new_alloc;
							}
							libc_memcpyc(result + result_length, linebuf_ptr,
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
						int comment_ch = libc_fgetc(stream);
again_check_ch_in_comment:
						if (comment_ch == EOF)
							break; /* end-of-file */
						if (comment_ch == delim_escape && delim_escape) {
							comment_ch = libc_fgetc(stream);
							if (comment_ch == '\r' || comment_ch == '\n') {
								if (plineno)
									++*plineno;
								if (comment_ch == '\r') {
									comment_ch = libc_fgetc(stream);
									if (comment_ch != '\n')
										libc_ungetc(comment_ch, stream);
								}
								if (delim_escape == delim_continue)
									continue;
								break;
							}
							continue;
						}
						if (comment_ch == delim_continue && delim_continue) {
							comment_ch = libc_fgetc(stream);
							if (comment_ch == '\r' || comment_ch == '\n') {
								if (plineno)
									++*plineno;
								if (comment_ch == '\r') {
									comment_ch = libc_fgetc(stream);
									if (comment_ch != '\n')
										libc_ungetc(comment_ch, stream);
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
							comment_ch = libc_fgetc(stream);
							if (comment_ch != '\n')
								libc_ungetc(comment_ch, stream);
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

			result = (char *)libc_malloc(sizeof(char));



			if unlikely(!result)
				goto done;
			result_alloc = 1;
		}
	}

	libc_free(linebuf_ptr);

	/* Trim a potential trailing line-feed */
	if (result_length && result[result_length - 1] == '\n')
		--result_length;
	/* Finalize the resulting buffer. */
	if (result_length + 1 < result_alloc) {
		/* Try to release unused memory. */
		char *new_result;
		new_result = (char *)libc_realloc(result,
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

	libc_free(linebuf_ptr);
	libc_free(result);

	return NULL;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(fparseln, libc_fparseln);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_UTIL_C */
