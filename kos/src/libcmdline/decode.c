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
#ifndef GUARD_LIBCMDLINE_DECODE_C
#define GUARD_LIBCMDLINE_DECODE_C 1

#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <malloc.h>
#include <stddef.h>
#include <string.h>
#include <unicode.h>

#include <libcmdline/decode.h>

#include "decode.h"

#ifdef __KERNEL__
#include <kernel/malloc.h>
#endif /* __KERNEL__ */

DECL_BEGIN

struct argv_append_data {
	/*utf-8*/ char **aad_argv; /* [1..1][1..aad_argc|alloc(aad_arga)][owned] Argument vector */
	size_t           aad_argc; /* Used argument count */
	size_t           aad_arga; /* Allocated argument count */
	os_heap_gfpvar  (aad_gfp)  /* [const] Malloc flags. */
};

PRIVATE NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
argv_append(void *__restrict arg,
            /*utf-8*/ char const *__restrict data,
            size_t UNUSED(len)) {
	struct argv_append_data *buf;
	buf = (struct argv_append_data *)arg;
	if (buf->aad_argc >= buf->aad_arga) {
		char **new_argv;
		size_t new_alloc;
		new_alloc = buf->aad_arga * 2;
		new_argv = (char **)os_heap_realloc_nx(buf->aad_argv,
		                                       (new_alloc + 1) *
		                                       sizeof(char *),
		                                       buf->aad_gfp);
		if unlikely(!new_argv) {
			new_alloc = buf->aad_argc + 1;
			new_argv = (char **)os_heap_realloc_unx(buf->aad_argv,
			                                        (new_alloc + 1) *
			                                        sizeof(char *),
			                                        buf->aad_gfp);
#ifndef __KERNEL__
			if unlikely(!new_argv)
				return -1; /* Error */
#endif /* !__KERNEL__ */
		}
		buf->aad_argv = new_argv;
		buf->aad_arga = new_alloc;
	}
	buf->aad_argv[buf->aad_argc] = (char *)data;
	++buf->aad_argc;
	return 1;
}

/* Similar  to `cmdline_decode()', however return a heap-allocated
 * vector of the individual argument strings, which itself is then
 * terminated by a NULL-entry.
 * When `pargc' is non-NULL, store the number of arguments leading
 * up  to  (but   not  including)   the  terminating   NULL-entry.
 * Upon error, NULL is returned. */
INTERN ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char **CC
libcmdline_decode_argv(/*utf-8*/ char *__restrict cmdline,
                       size_t *pargc _os_heap_gfparg(gfp)) {
	struct argv_append_data buf;
	buf.aad_argc = 0;
	buf.aad_arga = 8;
	os_heap_gfpset(buf.aad_gfp, gfp);
	/* Allocate the initial buffer */
	buf.aad_argv = (char **)os_heap_malloc_nx((buf.aad_arga + 1) *
	                                          sizeof(char *),
	                                          gfp);
	if unlikely(!buf.aad_argv) {
		buf.aad_arga = 1;
		buf.aad_argv = (char **)os_heap_malloc_unx((buf.aad_arga + 1) *
		                                           sizeof(char *),
		                                           gfp);
#ifndef __KERNEL__
		if unlikely(!buf.aad_argv)
			goto done;
#endif /* !__KERNEL__ */
	}
	/* Decode the cmdline */
	if unlikely(libcmdline_decode(cmdline, &argv_append, &buf) < 0)
		goto err;
	/* Try to free unused memory. */
	{
		char **final_argv;
		final_argv = (char **)os_heap_realloc_nx(buf.aad_argv,
		                                         (buf.aad_argc + 1) *
		                                         sizeof(char *),
		                                         buf.aad_gfp);
		if likely(final_argv)
			buf.aad_argv = final_argv;
	}
	/* Terminate with argument vector with NULL */
	buf.aad_argv[buf.aad_argc] = NULL;
	if (pargc)
		*pargc = buf.aad_argc;
#ifndef __KERNEL__
done:
#endif /* !__KERNEL__ */
	return buf.aad_argv;
err:
	os_heap_free(buf.aad_argv);
	return NULL;
}



/* Decode and transform a given `cmdline' (which must be a \0-terminated string),
 * and    invoke   `arg_printer'   with   each   individual   argument   segment.
 * NOTE: When `arg_printer' return an error ((*arg_printer)(...) < 0), that error
 *       is  propagated and re-returned by this function. In this case, `cmdline'
 *       is left in an undefined state.
 * This function recognizes the following commandline rules:
 *   - >\x<    can be used to escape a given character `x'
 *             This character can  be anything, and  in the leading  \-character
 *             is always removed, meaning that in order to include a \-character
 *             in the actual argument vector, \\ must be written
 *   - >a b<   Any sort of space characters (s.a. `unicode_isspace()') is recognized
 *             as a suitable separator between arguments.
 *             Multiple consecutive space characters are merged into a single one.
 *   - >"a b"< Write text in  space-escaped mode.  - In this  mode, space  characters
 *             do not mark separate arguments. Additionally, the leading and trailing
 *             "-characters are removed from the generated arguments
 *   - >'a b'< Same  as "a b", but with this, you can do >"How's it going"< or
 *             >'I said "Hello"'< instead of having to use >'How\'s it going'<
 *             and >"I said \"Hello\""<
 *   - >""<    Special case: When  >""< or  >''< is encountered,  but is  surrounded
 *             by whitespace, or the start/end of the commandline, an empty argument
 *             will be emit (see examples below)
 * Examples:
 *     >a b c<                  { "a", "b", "c" }
 *     >ls "New Folder"<        { "ls", "New Folder" }
 *     >ls New\ Folder<         { "ls", "New Folder" }
 *     >ls "" foo<              { "ls", "", "foo" }     // Empty argument!
 */
INTERN NONNULL((1, 2)) ssize_t CC
libcmdline_decode(/*utf-8*/ char *__restrict cmdline,
                  pformatprinter arg_printer,
                  void *arg_printer_arg) {
	char *cmdline_end;
	ssize_t temp, result = 0;
	char *next_ch, *arg_start;
	char32_t ch;
	/* Skip leading space. */
	for (;;) {
		next_ch = cmdline;
		ch      = unicode_readutf8(&next_ch);
		if (!unicode_isspace(ch))
			break;
		cmdline = next_ch;
	}
	/* Check for empty commandline. */
	if unlikely(!ch)
		goto done;
	arg_start   = cmdline;
	cmdline_end = strend(cmdline);
	for (;;) {
parse_next_ch:
		/* Escaped characters. */
		if (cmdline_isbslsh(ch)) {
			if (next_ch >= cmdline_end)
				goto done_cmdline;
			memmovedown(cmdline, next_ch,
			            (size_t)(cmdline_end - next_ch),
			            sizeof(char));
			cmdline_end -= (size_t)(next_ch - cmdline);
			next_ch = cmdline;
			ch      = unicode_readutf8(&next_ch); /* Skip the next character */
			/* Read the next non-escaped character */
			goto read_next_ch;
		}
		/* String arguments. */
		if (cmdline_isquote(ch)) {
			char32_t end_ch = ch;
			if (next_ch >= cmdline_end)
				goto done_cmdline;
			memmovedown(cmdline, next_ch,
			            (size_t)(cmdline_end - next_ch),
			            sizeof(char));
			cmdline_end -= (size_t)(next_ch - cmdline);
			next_ch = cmdline;
			for (;;) {
				cmdline = next_ch;
				if unlikely(next_ch >= cmdline_end)
					goto done_cmdline;
				ch = unicode_readutf8(&next_ch);
				if (cmdline_isbslsh(ch)) {
					if (next_ch >= cmdline_end)
						goto done_cmdline;
					memmovedown(cmdline, next_ch,
					            (size_t)(cmdline_end - next_ch),
					            sizeof(char));
					cmdline_end -= (size_t)(next_ch - cmdline);
					next_ch = cmdline;
					ch      = unicode_readutf8(&next_ch); /* Skip the next character */
					/* Read the next non-escaped character */
					cmdline = next_ch;
					if (next_ch >= cmdline_end)
						goto done_cmdline;
					next_ch += unicode_utf8seqlen[(unsigned char)*next_ch];
					continue;
				}
				if (ch == end_ch) {
					if (next_ch >= cmdline_end)
						goto done_cmdline;
					memmovedown(cmdline, next_ch,
					            (size_t)(cmdline_end - next_ch),
					            sizeof(char));
					cmdline_end -= (size_t)(next_ch - cmdline);
					next_ch = cmdline;
					if (next_ch >= cmdline_end) {
						if unlikely(arg_start == cmdline) {
							/* Special case: Empty, trailing argument */
							arg_start[0] = '\0';
							temp         = (*arg_printer)(arg_printer_arg, arg_start, 0);
							if unlikely(temp < 0)
								goto err;
							result += temp;
						}
						goto done_cmdline;
					}
					ch = unicode_readutf8(&next_ch);
					if unlikely(arg_start == cmdline && unicode_isspace(ch)) {
						/* Special case: Empty argument (foo bar "" baz --> { "foo", "bar", "", "baz" }) */
						/* To keep all strings apart of  the given cmdline, reclaim 1  character
						 * which we can then set to \0. - Note that we are guarantied to have at
						 * least 2 bytes available, due to the 2 " or '-characters */
						memmoveup(arg_start + 1, arg_start,
						          (size_t)(cmdline_end - arg_start),
						          sizeof(char));
						arg_start[0] = '\0';
						temp = (*arg_printer)(arg_printer_arg, arg_start, 0);
						if unlikely(temp < 0)
							goto err;
						result += temp;
						++cmdline_end;
						arg_start = cmdline = ++next_ch;
						goto skip_secondary_whitespace;
					}
					goto parse_next_ch;
				}
			}
		}
		/* Space -> Argument separator. */
		if (unicode_isspace(ch)) {
			*cmdline = '\0'; /* Terminate the previous argument. */
			/* Invoke the caller's function with this new argument. */
			temp = (*arg_printer)(arg_printer_arg,
			                      arg_start,
			                      (size_t)(cmdline - arg_start));
			if unlikely(temp < 0)
				goto err;
			result += temp;
skip_secondary_whitespace:
			/* Skip multiple consecutive spaces. */
			for (;;) {
				if (next_ch >= cmdline_end)
					goto done; /* Commandline ends with space */
				arg_start = next_ch;
				ch = unicode_readutf8(&next_ch);
				if (!unicode_isspace(ch))
					break;
			}
			/* Next non-space character was found */
			cmdline = arg_start;
			goto parse_next_ch;
		}
read_next_ch:
		cmdline = next_ch;
		if (next_ch >= cmdline_end)
			goto done_cmdline;
		ch = unicode_readutf8(&next_ch);
	}
done_cmdline:
	*cmdline = '\0';
	temp = (*arg_printer)(arg_printer_arg,
	                      arg_start,
	                      (size_t)(cmdline - arg_start));
	if unlikely(temp < 0)
		goto err;
	result += temp;
done:
	return result;
err:
	return temp;
}





PRIVATE NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
cmdline_flatten_callback(void *arg,
                         char const *__restrict data,
                         size_t datalen) {
	char *dst = *(char **)arg;
	if (dst != data) /* Flatten arguments. */
		memmovedown(dst, data, datalen + 1, sizeof(char));
	dst += datalen + 1;
	*(char **)arg = dst;
	return 1;
}

/* Split a given commandline into tightly-packed, NUL-terminated
 * strings,   and   return   the   total   number   of  strings.
 * NOTE:  Obviously, this function will modify `cmdline'
 * >> char *iter, *my_cmdline = get_cmdline();
 * >> size_t i, argc = cmdline_split(my_cmdline, NULL);
 * >> for (iter = my_cmdline, i = 0; i < argc; ++i, iter = strend(iter) + 1) {
 * >>     printf("argv[%" PRIuSIZ "] = %q\n", i, iter);
 * >> }
 * @param: pendptr: When non-NULL, store a pointer to one byte past the end of the last argument
 * @return: * :     The total number of individual argument strings. */
INTERN NONNULL((1)) size_t CC
libcmdline_split(/*utf-8*/ char *__restrict cmdline, char **pendptr) {
	size_t result;
	result = (size_t)libcmdline_decode(cmdline,
	                                   &cmdline_flatten_callback,
	                                   (void *)&cmdline);
	if (pendptr)
		*pendptr = cmdline;
	return result;
}





DEFINE_PUBLIC_ALIAS(cmdline_decode_argv, libcmdline_decode_argv);
DEFINE_PUBLIC_ALIAS(cmdline_decode, libcmdline_decode);
DEFINE_PUBLIC_ALIAS(cmdline_split, libcmdline_split);


DECL_END

#endif /* !GUARD_LIBCMDLINE_CMDLINE_C */
