/* HASH CRC-32:0xbdc5df16 */
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
#ifndef GUARD_LIBC_AUTO_ARGZ_C
#define GUARD_LIBC_AUTO_ARGZ_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "argz.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <libc/errno.h>
#include <hybrid/__assert.h>
/* >> argz_create(3)
 * Construct  an  argz-string  from  a  given  NULL-terminated  `argv'-vector,
 * as is also passed to main(), and accepted by the exec() family of functions
 * An  argz-string is imply a string of '\0'-seperated sub-strings, where each
 * sub-string represents one of the original strings from `argv'
 *
 * The base-pointer to this string is stored in `*pargz'
 *
 * The overall length of the argz-string is  tracked at the offset from its  base
 * pointer, to the first  byte after a trailing  '\0' character that follows  the
 * last of the many sub-strings. An empty argz-string is thus represented as  any
 * base-pointer in conjunction with `*pargz_len=0'. (But note that GLibc seems to
 * suggest that certain APIs  should be used under  the assumption that an  empty
 * argz-string  can also be represented with the base pointer `*pargz=NULL'. This
 * kind of behavior is _NOT_ actually supported  by the API, and only implied  by
 * some (apparently) badly worded documentation of `argz_next(3)')
 *
 * When an argz-string is no longer needed, it can be destroyed by passing its
 * base pointer (as filled in at `*pargz' by this function, and updated by the
 * many other functions in this header) to `free(3)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTERN ATTR_SECTION(".text.crt.string.argz") ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(3) error_t
NOTHROW_NCX(LIBCCALL libc_argz_create)(char *const argv[],
                                       char **__restrict pargz,
                                       size_t *__restrict pargz_len) {
	size_t i, argc, total_len = 0;
	for (argc = 0; argv[argc] != NULL; ++argc)
		total_len += libc_strlen(argv[argc]) + 1;
	if unlikely(total_len == 0) {
		*pargz = NULL;
	} else {
		char *argz_string;
		argz_string = (char *)libc_malloc(total_len * sizeof(char));
		if unlikely(!argz_string) {
			*pargz = NULL;
			*pargz_len  = 0;

			return ENOMEM;



		}
		*pargz = argz_string;
		for (i = 0; i < argc; ++i) {
			argz_string = libc_stpcpy(argz_string, argv[argc]) + 1;
		}
		__hybrid_assert(argz_string == *pargz + total_len);
	}
	*pargz_len = total_len;
	return 0;
}
#include <libc/errno.h>
/* >> argz_create_sep(3)
 * Create an argz-string from `string' by splitting that string at each
 * occurrence of `sep'. This function behaves the same as the following
 * pseudo-code:
 *     [*pargz, *pargz_len] = string.replace(sep, "\0").replaceall("\0\0", "\0");
 * As can be seen in the pseudo-code, duplicate, successive instance of
 * `sep' are merged, such that no empty sub-strings will be present  in
 * the resulting argz-string.
 * For more information on the semantics of argz-strings, see the
 * documentation of `argz_create()'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTERN ATTR_SECTION(".text.crt.string.argz") ATTR_IN(1) ATTR_OUT(3) ATTR_OUT(4) error_t
NOTHROW_NCX(LIBCCALL libc_argz_create_sep)(char const *__restrict string,
                                           int sep,
                                           char **__restrict pargz,
                                           size_t *__restrict pargz_len) {
	/* return string.replace(sep, "\0").replaceall("\0\0", "\0"); */
	char *result_string, *dst;
	size_t slen = libc_strlen(string);
	if unlikely(!slen) {
empty_argz:
		*pargz     = NULL;
		*pargz_len = 0;
		return 0;
	}
	result_string = (char *)libc_malloc((slen + 1) * sizeof(char));
	*pargz = result_string;
	if unlikely(!result_string) {
		*pargz_len = 0;

		return ENOMEM;



	}
	dst = result_string;
	for (;;) {
		char ch;
		ch = *string++;
again_check_ch:
		if (!ch)
			break;
		if (ch != (char)(unsigned char)(unsigned int)sep) {
			*dst++ = ch;
			continue;
		}
		/* Split the string. */
		*dst++ = '\0';
		/* Skip consecutive `sep'-characters in `string' */
		do {
			ch = *string++;
		} while (ch == (char)(unsigned char)(unsigned int)sep);
		goto again_check_ch;
	}
	if unlikely(dst == result_string) {
		/* Empty string. (this can happen if `string' only consisted of `sep' characters) */

		libc_free(result_string);

		goto empty_argz;
	}
	/* Write the terminating NUL-byte (if there isn't one already) */
	if (dst[-1] != '\0')
		*dst++ = '\0';
	*pargz_len = (size_t)(dst - result_string);
	return 0;
}
/* >> argz_count(3)
 * Count and return the # of strings in `argz'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
INTERN ATTR_SECTION(".text.crt.string.argz") ATTR_PURE ATTR_INS(1, 2) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_argz_count)(char const *argz,
                                      size_t argz_len) {
	size_t result = 0;
	if likely(argz_len) {
		for (;;) {
			size_t temp;
			++result;
			temp = libc_strlen(argz) + 1;
			if (temp >= argz_len)
				break;
			argz_len -= temp;
			argz     += temp;
		}
	}
	return result;
}
/* >> argz_extract(3)
 * Extend pointers to  individual string  from `argz',  and sequentially  write them  to
 * `argv',  for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
INTERN ATTR_SECTION(".text.crt.string.argz") ATTR_INS(1, 2) ATTR_OUT(3) void
NOTHROW_NCX(LIBCCALL libc_argz_extract)(char const *__restrict argz,
                                        size_t argz_len,
                                        char **__restrict argv) {
	size_t i;
	if unlikely(!argz_len)
		return;
	for (i = 0;;) {
		size_t temp;
		argv[i++] = (char *)argz;
		temp = libc_strlen(argz) + 1;
		if (temp >= argz_len)
			break;
		argz_len -= temp;
		argz     += temp;
	}
}
/* >> argz_stringify(3)
 * Convert  an  `argz' string  into a  NUL-terminated c-string
 * with a total `strlen(argz) == len - 1', by replacing all of
 * the NUL-characters separating  the individual  argz-strings
 * with `sep'. */
INTERN ATTR_SECTION(".text.crt.string.argz") ATTR_INOUTS(1, 2) void
NOTHROW_NCX(LIBCCALL libc_argz_stringify)(char *argz,
                                          size_t len,
                                          int sep) {
	/* replace(base: argz, count: len - 1, old: '\0', new: sep); */
	if unlikely(!len)
		return;
	for (;;) {
		size_t temp;
		temp = libc_strlen(argz) + 1;
		if (temp >= len)
			break;
		len  -= temp;
		argz += temp;
		argz[-1] = (char)(unsigned char)(unsigned int)sep;
	}
}
#include <libc/errno.h>
/* >> argz_append(3)
 * Increase allocated memory of `*pargz' and append `buf...+=buf_len'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTERN ATTR_SECTION(".text.crt.string.argz") ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INS(3, 4) error_t
NOTHROW_NCX(LIBCCALL libc_argz_append)(char **__restrict pargz,
                                       size_t *__restrict pargz_len,
                                       char const *__restrict buf,
                                       size_t buf_len) {
	size_t oldlen = *pargz_len;
	size_t newlen = oldlen + buf_len;
	char *newargz = (char *)libc_realloc(*pargz, newlen * sizeof(char));
	if unlikely(!newargz) {

		return ENOMEM;



	}
	libc_memcpyc(newargz + oldlen, buf, buf_len, sizeof(char));
	*pargz     = newargz;
	*pargz_len = newlen;
	return 0;
}
/* >> argz_add(3)
 * Append `str' (including its trailing NUL) to the argz string in `*pargz...+=pargz_len'
 * This    is    the   same    as   `argz_append(pargz, pargz_len, str, strlen(str) + 1)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTERN ATTR_SECTION(".text.crt.string.argz") ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) error_t
NOTHROW_NCX(LIBCCALL libc_argz_add)(char **__restrict pargz,
                                    size_t *__restrict pargz_len,
                                    char const *__restrict str) {
	return libc_argz_append(pargz, pargz_len, str, libc_strlen(str) + 1);
}
#include <libc/errno.h>
/* >> argz_add_sep(3)
 * A  combination of `argz_create_sep()'  and `argz_append()' that will
 * append a duplication of `string' onto `*pargz', whilst replacing all
 * instances of `sep' with NUL-characters,  thus turning them into  the
 * markers  between  separate  strings.  Note  however  that duplicate,
 * successive instance of  `sep' are  merged, such that  no empty  sub-
 * strings will be present in the resulting argz-string.
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTERN ATTR_SECTION(".text.crt.string.argz") ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) error_t
NOTHROW_NCX(LIBCCALL libc_argz_add_sep)(char **__restrict pargz,
                                        size_t *__restrict pargz_len,
                                        char const *__restrict string,
                                        int sep) {
	char *result_string, *dst;
	size_t oldlen;
	size_t slen = libc_strlen(string);
	if unlikely(!slen)
		return 0;
	oldlen = *pargz_len;
	/* Note that GLibc actually has a bug here that causes it to write `NULL'
	 * into  the given  `*pargz' pointer  when the  allocation fails, instead
	 * of leaving that  pointer in  its original state  (allowing the  caller
	 * to cleanup  the argz-array,  instead of  forcing the  array to  become
	 * a memory leak)
	 * -> That bug is fixed here!
	 * Glibc's  version  of this:
	 * >> *argz = (char *) realloc (*argz, *argz_len + nlen); // <<< Right here!
	 * >> if (*argz == NULL)
	 * >>   return ENOMEM;
	 * As reference that the intended behavior in the ENOMEM-branch is an
	 * unmodified `*pargz' pointer (or at the very least, a  simultaneous
	 * setting of the `*pargz_len' pointer  to ZERO(0)), you may look  at
	 * Glibc's version  of `argz_append()',  which handles  that case  as
	 * leaving all pointers unmodified (just as one should)
	 */
	result_string = (char *)libc_realloc(*pargz, (oldlen + (slen + 1)) * sizeof(char));
	if unlikely(!result_string) {

		return ENOMEM;



	}
	*pargz = result_string;
	dst    = result_string + oldlen;
	for (;;) {
		char ch;
		ch = *string++;
again_check_ch:
		if (!ch)
			break;
		if (ch != (char)(unsigned char)(unsigned int)sep) {
			*dst++ = ch;
			continue;
		}
		/* Split the string. */
		*dst++ = '\0';
		/* Skip consecutive `sep'-characters in `string' */
		do {
			ch = *string++;
		} while (ch == (char)(unsigned char)(unsigned int)sep);
		goto again_check_ch;
	}
	if unlikely(dst == result_string) {
		/* Empty string. (this can happen if `string' only consisted of `sep' characters) */
		libc_free(result_string);
		*pargz     = NULL;
		*pargz_len = 0;
		return 0;
	}
	/* Write the terminating NUL-byte (if there isn't one already) */
	if (dst[-1] != '\0')
		*dst++ = '\0';
	*pargz_len = (size_t)(dst - result_string);
	return 0;
}
/* >> argz_delete(3)
 * Find the index  of `entry' inside  of `pargz...+=pargz_len', and,  if
 * found, remove that entry by shifting all following elements downwards
 * by one, as well as decrementing `*pargz_len' by one.
 * Note that `entry' must  be the actual pointer  to one of the  elements
 * of the given `pargz...+=pargz_len', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
INTERN ATTR_SECTION(".text.crt.string.argz") ATTR_INOUT(1) ATTR_INOUT(2) ATTR_IN_OPT(3) void
NOTHROW_NCX(LIBCCALL libc_argz_delete)(char **__restrict pargz,
                                       size_t *__restrict pargz_len,
                                       char *entry) {
	size_t entrylen, newlen;
	if unlikely(!entry)
		return;
	entrylen  = libc_strlen(entry) + 1;
	newlen    = *pargz_len - entrylen;
	*pargz_len = newlen;
	if unlikely(newlen == 0) {

		libc_free(*pargz);

		*pargz = NULL;
		return;
	}
	libc_memmovedownc(entry, entry + entrylen,
	             (newlen - (size_t)(entry - *pargz)),
	             sizeof(char));
}
#include <libc/errno.h>
/* >> argz_insert(3)
 * When `before' is  `NULL', do the  same as  `argz_add(pargz, pargz_len, entry)'
 * Otherwise,  `before' should point  somewhere into the middle,  or to the start
 * of an existing argument entry, who's  beginning will first be located,  before
 * this function will then allocate additional memory to insert a copy of `entry'
 * such that the copy will appear before the entry pointed to by `before'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory
 * @return: EINVAL: The given `before' is either `NULL', or apart of `*pargz' */
INTERN ATTR_SECTION(".text.crt.string.argz") ATTR_IN(4) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_IN_OPT(3) error_t
NOTHROW_NCX(LIBCCALL libc_argz_insert)(char **__restrict pargz,
                                       size_t *__restrict pargz_len,
                                       char *before,
                                       char const *__restrict entry) {
	char *argz;
	size_t argz_len;
	size_t entry_len;
	size_t insert_offset;
	if (!before)
		return libc_argz_add(pargz, pargz_len, entry);
	argz     = *pargz;
	argz_len = *pargz_len;
	if (before < argz || before >= argz + argz_len) {

		return EINVAL;



	}
	/* Adjust  `before'  to  point  to  the  start  of  an  entry
	 * Note that GLibc has a bug here that causes it to  accessed
	 * memory before `*pargz' when `before' points into the first
	 * element of the argz vector.
	 * -> That bug is fixed here!
	 * As such, GLibc's version would only work when `((char *)malloc(N))[-1] == 0'
	 * for  an  arbitrary  N  that   results  in  `malloc()'  returning   non-NULL.
	 * Glibc's version of this:
	 * >> if (before > *argz)
	 * >>   while (before[-1]) // <<< Right here!
	 * >>     before--;
	 */
	while (before > argz && before[-1])
		--before;
	entry_len = libc_strlen(entry) + 1;
	argz_len += entry_len;
	insert_offset = (size_t)(before - argz);
	argz = (char *)libc_realloc(argz, argz_len * sizeof(char));
	if unlikely(!argz) {

		return ENOMEM;



	}
	/* Update argz-pointers. */
	*pargz     = argz;
	*pargz_len = argz_len;
	/* Make space for the new entry. */
	libc_memmoveupc(argz + insert_offset + entry_len,
	           argz + insert_offset,
	           (argz_len - (insert_offset + entry_len)),
	           sizeof(char));
	/* Insert the new entry. */
	libc_memcpyc(argz + insert_offset,
	        entry, entry_len,
	        sizeof(char));
	return 0;
}
#include <libc/errno.h>
/* >> argz_replace(3)
 * Replace all matches of `str' inside of every string or sub-string from `pargz...+=pargz_len'
 * with `with', and resize the  argz-string if necessary. For  every replacement that is  done,
 * the given `replace_count' is incremented by one (if `replace_count' is non-NULL)
 * @return: 0:      Success
 * @return: ENOMEM: Insufficient heap memory (can only happen when `strlen(with) > strlen(str)',
 *                  but  note  that  the GLibc  implementation  of this  function  is completely
 *                  unreadable and may be able to return this for other cases as well...) */
INTERN ATTR_SECTION(".text.crt.string.argz") ATTR_IN(4) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_IN_OPT(3) error_t
NOTHROW_NCX(LIBCCALL libc_argz_replace)(char **__restrict pargz,
                                        size_t *__restrict pargz_len,
                                        char const *__restrict str,
                                        char const *__restrict with,
                                        unsigned int *__restrict replace_count) {
	size_t findlen, repllen;
	size_t find_offset;
	if unlikely(!str)
		return 0; /* no-op */
	findlen = libc_strlen(str);
	if unlikely(!findlen)
		return 0; /* no-op */
	repllen = libc_strlen(with);
	find_offset = 0;
	/* I have no  idea what the  GLibc implementation does  here, and I'm  not
	 * quite sure it  knows either.  - At first  I though  that this  function
	 * was supposed to  only replace  entries of  an argz-string  as a  whole,
	 * but now I  believe it's just  supposed to do  replacement of any  match
	 * found.  However, GLibc appears to be utterly afraid of using `memmem()'
	 * for  this,  and instead  opt's to  using  `argz_next()' to  iterate the
	 * argz-vector, and doing  `strstr()' on each  element, before doing  some
	 * dark  voodoo magic  with `strndup()',  temporary buffers,  and god only
	 * knows why  there are  even delayed  calls to  `argz_add()' in  there???
	 * If  this implementation doesn't do exactly what GLibc does, don't fault
	 * me.  Every  function in  this file  was originally  created as  a GLibc
	 * extension, so there really isn't any official documentation on intended
	 * behavior other than GLibc reference implementation.
	 * Anyways... At least my version is readable... */
	while (find_offset < *pargz_len) {
		char *pos;
		pos = (char *)libc_memmem(*pargz + find_offset,
		                     *pargz_len - find_offset,
		                     str, findlen);
		if (!pos)
			break; /* Nothing else to find! */
		if (repllen < findlen) {
			/* Simple case: The replacement string is smaller than the find-string */
			char *old_argz, *new_argz;
			size_t diff, trailing_characters;
			pos  = (char *)libc_mempcpyc(pos, with, repllen, sizeof(char));
			diff = findlen - repllen;
			*pargz_len -= diff;
			old_argz = *pargz;
			trailing_characters = *pargz_len - (size_t)(pos - old_argz);
			libc_memmovedownc(pos, pos + diff, trailing_characters, sizeof(char));
			new_argz = (char *)libc_realloc(old_argz, *pargz_len * sizeof(char));
			if likely(new_argz) {
				pos    = new_argz + (pos - old_argz);
				*pargz = new_argz;
			}
		} else if (repllen > findlen) {
			char *old_argz, *new_argz;
			size_t old_argzlen, new_argzlen;
			size_t diff, trailing_characters;
			/* Difficult case: The replacement string is longer than the find-string */
			diff = repllen - findlen;
			old_argzlen = *pargz_len;
			new_argzlen = old_argzlen + diff;
			old_argz = *pargz;
			new_argz = (char *)libc_realloc(old_argz, new_argzlen * sizeof(char));
			if unlikely(!new_argz) {

				return ENOMEM;



			}
			pos = new_argz + (pos - old_argz);
			/* Make space for extra data */
			trailing_characters = new_argzlen - ((pos + repllen) - new_argz);
			libc_memmoveupc(pos + repllen,
			           pos + findlen,
			           trailing_characters,
			           sizeof(char));
			/* Fill in the replacement string. */
			pos = (char *)libc_mempcpyc(pos, with, repllen, sizeof(char));
		} else {
			/* Simple case: The replacement string has the same length as the find-string */
			pos = (char *)libc_mempcpyc(pos, with, repllen, sizeof(char));
		}
		if (replace_count)
			++*replace_count;
	}
	return 0;
}
/* >> argz_next(3)
 * Iterate the individual strings that make up a given argz-vector.
 * This function  is  intended  to  be  used  in  one  of  2  ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note  that  GLibc documents  the second  usage  case slightly  different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty argz-string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL'  (which isn't something consistently enforced,  or
 * required  by any of  the other APIs, so  I'd just suggest  you always use the
 * first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of `argz', return `NULL'
 *  - If the successor of `entry' points at, or past the end of `argz', return `NULL'
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
INTERN ATTR_SECTION(".text.crt.string.argz") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_IN_OPT(3) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_argz_next)(char const *__restrict argz,
                                     size_t argz_len,
                                     char const *__restrict entry) {
	char const *argz_end;
	if (!entry)
		return argz_len ? (char *)argz : NULL;
	argz_end = argz + argz_len;
	if (entry < argz_end)
		entry = libc_strend(entry) + 1;
	if (entry >= argz_end)
		return NULL;
	return (char *)entry;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__argz_create, libc_argz_create);
DEFINE_PUBLIC_ALIAS(argz_create, libc_argz_create);
DEFINE_PUBLIC_ALIAS(__argz_create_sep, libc_argz_create_sep);
DEFINE_PUBLIC_ALIAS(argz_create_sep, libc_argz_create_sep);
DEFINE_PUBLIC_ALIAS(__argz_count, libc_argz_count);
DEFINE_PUBLIC_ALIAS(argz_count, libc_argz_count);
DEFINE_PUBLIC_ALIAS(__argz_extract, libc_argz_extract);
DEFINE_PUBLIC_ALIAS(argz_extract, libc_argz_extract);
DEFINE_PUBLIC_ALIAS(__argz_stringify, libc_argz_stringify);
DEFINE_PUBLIC_ALIAS(argz_stringify, libc_argz_stringify);
DEFINE_PUBLIC_ALIAS(__argz_create_sep, libc_argz_append);
DEFINE_PUBLIC_ALIAS(argz_append, libc_argz_append);
DEFINE_PUBLIC_ALIAS(__argz_add, libc_argz_add);
DEFINE_PUBLIC_ALIAS(argz_add, libc_argz_add);
DEFINE_PUBLIC_ALIAS(__argz_add_sep, libc_argz_add_sep);
DEFINE_PUBLIC_ALIAS(argz_add_sep, libc_argz_add_sep);
DEFINE_PUBLIC_ALIAS(__argz_add_sep, libc_argz_delete);
DEFINE_PUBLIC_ALIAS(argz_delete, libc_argz_delete);
DEFINE_PUBLIC_ALIAS(__argz_insert, libc_argz_insert);
DEFINE_PUBLIC_ALIAS(argz_insert, libc_argz_insert);
DEFINE_PUBLIC_ALIAS(__argz_replace, libc_argz_replace);
DEFINE_PUBLIC_ALIAS(argz_replace, libc_argz_replace);
DEFINE_PUBLIC_ALIAS(__argz_next, libc_argz_next);
DEFINE_PUBLIC_ALIAS(argz_next, libc_argz_next);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_ARGZ_C */
