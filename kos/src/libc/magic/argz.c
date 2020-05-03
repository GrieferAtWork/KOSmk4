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

%[default_impl_section(.text.crt.string.argz)]

%{
#include <features.h>
#include <bits/types.h>

/* Documentation is derived from GLibc: /usr/include/argz.h
 * Note that _ONLY_ the documentation was taken (and in places modified),
 * but the implementations were written from scratch, using GLibc's
 * implementation only as a reference (which also resulted in me discovering
 * some bugs in GLibc's version that I'm not going to report because at least
 * in my mind, these are just suuuuch _absolute_ beginner's mistakes...)
 * The function's that I've fixed are:
 *  - argz_add_sep()
 *  - argz_insert()
 * By the way: GLibc guys: If you want to copy my (fixed) implementation, that
 *                         is licensed under the ZLib license, so if one of you
 *                         comes across this, don't forget to include my copyright
 *                         notice when pasting ;)
 */
/* Routines for dealing with '\0' separated arg vectors.
   Copyright (C) 1995-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __error_t_defined
#define __error_t_defined 1
typedef __errno_t error_t;
#endif /* !__error_t_defined */

}

%[define_replacement(error_t = __errno_t)]


@@Make a '\0' separated arg vector from a unix argv vector, returning it in
@@`PARGZ', and the total length in `PLEN'. If a memory allocation error occurs,
@@`ENOMEM' is returned, otherwise `0'. The result can be destroyed using `free()'
[alias(__argz_create)][same_impl][requires($has_function(malloc))]
[dependency_include(<parts/errno.h>)]
[dependency_include(<hybrid/__assert.h>)]
argz_create:([nonnull] char *const argv[],
             [nonnull] char **__restrict pargz,
             [nonnull] size_t *__restrict pargz_len) -> error_t {
	size_t i, argc, total_len = 0;
	for (argc = 0; argv[argc] != NULL; ++argc)
		total_len += strlen(argv[argc]) + 1;
	if unlikely(total_len == 0) {
		*pargz = NULL;
	} else {
		char *argz_string;
		argz_string = (char *)malloc(total_len * sizeof(char));
		if unlikely(!argz_string) {
			*pargz = NULL;
			*pargz_len  = 0;
#ifdef ENOMEM
			return ENOMEM;
#else /* ENOMEM */
			return 1;
#endif /* !ENOMEM */
		}
		*pargz = argz_string;
		for (i = 0; i < argc; ++i) {
			argz_string = stpcpy(argz_string, argv[argc]) + 1;
		}
		__hybrid_assert(argz_string == *pargz + total_len);
	}
	*pargz_len = total_len;
	return 0;
}

[alias(*)][attribute(*)] __argz_create:(*) = argz_create;

@@Make a '\0' separated arg vector from a `SEP' separated list in
@@`STRING', returning it in `PARGZ', and the total length in `PLEN'.
@@If a memory allocation error occurs, `ENOMEM' is returned, otherwise `0'.
@@The result can be destroyed using `free()'
[alias(__argz_create_sep)][same_impl]
[requires($has_function(malloc) && $has_function(free))]
[dependency_include(<parts/errno.h>)]
argz_create_sep:(char const *__restrict string,
                 int sep, char **__restrict pargz,
                 size_t *__restrict pargz_len) -> error_t {
	/* return string.replace(sep, "\0").replaceall("\0\0", "\0"); */
	char *result_string, *dst;
	size_t slen = strlen(string);
	if unlikely(!slen) {
empty_argz:
		*pargz     = NULL;
		*pargz_len = 0;
		return 0;
	}
	result_string = (char *)malloc((slen + 1) * sizeof(char));
	*pargz = result_string;
	if unlikely(!result_string) {
		*pargz_len = 0;
#ifdef ENOMEM
		return ENOMEM;
#else /* ENOMEM */
		return 1;
#endif /* !ENOMEM */
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
		free(result_string);
		goto empty_argz;
	}
	/* Write the terminating NUL-byte (if there isn't one already) */
	if (dst[-1] != '\0')
		*dst++ = '\0';
	*pargz_len = (size_t)(dst - result_string);
	return 0;
}

[alias(*)][attribute(*)] __argz_create_sep:(*) = argz_create_sep;

@@Returns the number of strings in `ARGZ'
@@Simply count the number of`NUL-characters within `argz...+=argz_len'
[alias(__argz_count)][ATTR_PURE]
argz_count:([inp_opt(argz_len)] char const *argz, size_t argz_len) -> size_t {
	size_t result = 0;
	if likely(argz_len) {
		for (;;) {
			size_t temp;
			++result;
			temp = strlen(argz) + 1;
			if (temp >= argz_len)
				break;
			argz_len -= temp;
			argz     += temp;
		}
	}
	return result;
}

[alias(*)][attribute(*)] __argz_count:(*) = argz_count;

@@Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
@@to hold them all (aka: have space for at least `argz_count()' elements)
[alias(__argz_extract)]
argz_extract:([inp(argz_len)] char const *__restrict argz, size_t argz_len, [nonnull] char **__restrict argv)
	[([inp(argz_len)] char *__restrict argz, size_t argz_len, [nonnull] char **__restrict argv)]
	[([inp(argz_len)] char const *__restrict argz, size_t argz_len, [nonnull] char const **__restrict argv)]
{
	size_t i;
	if unlikely(!argz_len)
		return;
	for (i = 0;;) {
		size_t temp;
		argv[i++] = (char *)argz;
		temp = strlen(argz) + 1;
		if (temp >= argz_len)
			break;
		argz_len -= temp;
		argz     += temp;
	}
}

[alias(*)][attribute(*)] __argz_extract:(*) = argz_extract;

@@Make '\0' separated arg vector `ARGZ' printable by converting
@@all the '\0's except the last into the character `SEP'
[alias(__argz_stringify)]
argz_stringify:(char *argz, size_t len, int sep) {
	/* replace(base: argz, count: len - 1, old: '\0', new: sep); */
	if unlikely(!len)
		return;
	for (;;) {
		size_t temp;
		temp = strlen(argz) + 1;
		if (temp >= len)
			break;
		len  -= temp;
		argz += temp;
		argz[-1] = (char)(unsigned char)(unsigned int)sep;
	}
}

[alias(*)][attribute(*)] __argz_stringify:(*) = argz_stringify;


@@Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN'
[alias(__argz_create_sep)][same_impl]
[requires($has_function(realloc))]
[dependency_include(<parts/errno.h>)]
argz_append:([nonnull] char **__restrict pargz, [nonnull] size_t *__restrict pargz_len,
             [inp_opt(buf_len)] char const *__restrict buf, size_t buf_len) -> error_t {
	size_t oldlen = *pargz_len;
	size_t newlen = oldlen + buf_len;
	char *newargz = (char *)realloc(*pargz, newlen * sizeof(char));
	if unlikely(!newargz) {
#ifdef ENOMEM
		return ENOMEM;
#else /* ENOMEM */
		return 1;
#endif /* !ENOMEM */
	}
	memcpyc(newargz + oldlen, buf, buf_len, sizeof(char));
	*pargz     = newargz;
	*pargz_len = newlen;
	return 0;
}

[alias(*)][attribute(*)] __argz_append:(*) = argz_append;

@@Append `STR' to the argz vector in `PARGZ & PARGZ_LEN'
[alias(__argz_add)][same_impl][requires($has_function(argz_append))]
argz_add:([nonnull] char **__restrict pargz, [nonnull] size_t *__restrict pargz_len,
          [nonnull] char const *__restrict str) -> error_t {
	return argz_append(pargz, pargz_len, str, strlen(str) + 1);
}

[alias(*)][attribute(*)] __argz_add:(*) = argz_add;

@@Append `SEP' separated list in `STRING' to the argz vector in `PARGZ & PARGZ_LEN'
[alias(__argz_add_sep)][same_impl]
[requires($has_function(realloc))]
[dependency_include(<parts/errno.h>)]
argz_add_sep:([nonnull] char **__restrict pargz, [nonnull] size_t *__restrict pargz_len,
              [nonnull] char const *__restrict string, int sep) -> error_t {
	char *result_string, *dst;
	size_t oldlen;
	size_t slen = strlen(string);
	if unlikely(!slen)
		return 0;
	oldlen = *pargz_len;
	/* Note that GLibc actually has a bug here that causes it to write `NULL'
	 * into the given `*pargz' pointer when the allocation fails, instead
	 * of leaving that pointer in its original state (allowing the caller
	 * to cleanup the ARGZ array, instead of forcing the array to become
	 * a memory leak)
	 * -> That bug is fixed here!
	 * Glibc's version of this:
	 * >> *argz = (char *) realloc (*argz, *argz_len + nlen); // <<< Right here!
	 * >> if (*argz == NULL)
	 * >>   return ENOMEM;
	 * As reference that the intended behavior in the ENOMEM-branch is an
	 * unmodified `*pargz' pointer (or at the very least, a simultaneous
	 * setting of the `*pargz_len' pointer to ZERO(0)), you may look at
	 * Glibc's version of `argz_append()', which handles that case as
	 * leaving all pointers unmodified (just as one should)
	 */
	result_string = (char *)realloc(*pargz, (oldlen + (slen + 1)) * sizeof(char));
	if unlikely(!result_string) {
#ifdef ENOMEM
		return ENOMEM;
#else /* ENOMEM */
		return 1;
#endif /* !ENOMEM */
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
		free(result_string);
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

[alias(*)][attribute(*)] __argz_add_sep:(*) = argz_add_sep;

@@Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
@@Note that `ENTRY' must be the actual pointer to one of the elements
@@of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
@@of the elements... (took me a while to realize this one)
[alias(__argz_add_sep)][userimpl]
argz_delete:([nonnull] char **__restrict pargz,
             [nonnull] size_t *__restrict pargz_len,
             [nullable] char *entry) {
	size_t entrylen, newlen;
	if unlikely(!entry)
		return;
	entrylen  = strlen(entry) + 1;
	newlen    = *pargz_len - entrylen;
	*pargz_len = newlen;
	if unlikely(newlen == 0) {
@@if_has_function(free)@@
		free(*pargz);
@@endif_has_function(free)@@
		*pargz = NULL;
		return;
	}
	memmovedownc(entry, entry + entrylen,
	             (newlen - (size_t)(entry - *pargz)),
	             sizeof(char));
}

[alias(*)][attribute(*)] __argz_delete:(*) = argz_delete;

@@Insert `ENTRY' into `ARGZ & ARGZ_LEN' before `BEFORE', which should be an
@@existing entry in `ARGZ'; if `BEFORE' is `NULL', `ENTRY' is appended to the end.
@@Since `ARGZ's first entry is the same as `ARGZ', `argz_insert(ARGZ, ARGZ_LEN, ARGZ, ENTRY)'
@@will insert `ENTRY' at the beginning of `ARGZ'. If `BEFORE' is not in `ARGZ', `EINVAL'
@@is returned, else if memory can't be allocated for the new `ARGZ', `ENOMEM' is returned.
@@On success, `0' is returned
[alias(__argz_insert)][same_impl][dependency_include(<parts/errno.h>)]
[requires($has_function(realloc) && $has_function(argz_add))]
argz_insert:([nonnull] char **__restrict pargz, [nonnull] size_t *__restrict pargz_len,
             [nullable] char *before, [nonnull] char const *__restrict entry) -> error_t {
	char *argz;
	size_t argz_len;
	size_t entry_len;
	size_t insert_offset;
	if (!before)
		return argz_add(pargz, pargz_len, entry);
	argz     = *pargz;
	argz_len = *pargz_len;
	if (before < argz || before >= argz + argz_len) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	/* Adjust `before' to point to the start of an entry
	 * Note that GLibc has a bug here that causes it to accessed
	 * memory before `*pargz' when `before' points into the first
	 * element of the argz vector.
	 * -> That bug is fixed here!
	 * As such, GLibc's version would only work when `((char *)malloc(N))[-1] == 0'
	 * for an arbitrary N that results in `malloc()' returning non-NULL.
	 * Glibc's version of this:
	 * >> if (before > *argz)
	 * >>   while (before[-1]) // <<< Right here!
	 * >>     before--;
	 */
	while (before > argz && before[-1])
		--before;
	entry_len = strlen(entry) + 1;
	argz_len += entry_len;
	insert_offset = (size_t)(before - argz);
	argz = (char *)realloc(argz, argz_len * sizeof(char));
	if unlikely(!argz) {
#ifdef ENOMEM
		return ENOMEM;
#else /* ENOMEM */
		return 1;
#endif /* !ENOMEM */
	}
	/* Update ARGZ pointers. */
	*pargz     = argz;
	*pargz_len = argz_len;
	/* Make space for the new entry. */
	memmoveupc(argz + insert_offset + entry_len,
	           argz + insert_offset,
	           (argz_len - (insert_offset + entry_len)),
	           sizeof(char));
	/* Insert the new entry. */
	memcpyc(argz + insert_offset,
	        entry, entry_len,
	        sizeof(char));
	return 0;
}

[alias(*)][attribute(*)] __argz_insert:(*) = argz_insert;


@@Replace any occurrences of the string `STR' in `PARGZ' with `WITH', reallocating
@@`PARGZ' as necessary. If `PREPLACE_COUNT' is non-NULL, `*PREPLACE_COUNT' will be
@@incremented by number of replacements performed
[alias(__argz_replace)][same_impl][dependency_include(<parts/errno.h>)]
[requires($has_function(realloc) && $has_function(free))]
argz_replace:([nonnull] char **__restrict pargz,
              [nonnull] size_t *__restrict pargz_len,
              [nullable] char const *__restrict str,
              [nonnull] char const *__restrict with,
              [nullable] unsigned int *__restrict replace_count) -> error_t {
	size_t findlen, repllen;
	size_t find_offset;
	if unlikely(!str)
		return 0; /* no-op */
	findlen = strlen(str);
	if unlikely(!findlen)
		return 0; /* no-op */
	repllen = strlen(with);
	find_offset = 0;
	/* I have no idea what the GLibc implementation does here, and I'm not
	 * quite sure it knows either. - At first I though that this function
	 * was supposed to only replace entries of an ARGZ vector as a whole,
	 * but now I believe it's just supposed to do replacement of any match
	 * found. However, GLibc appears to be utterly afraid of using `memmem()'
	 * for this, and instead opt's to using `argz_next()' to iterate the
	 * ARGZ vector, and doing `strstr()' on each element, before doing some
	 * dark voodoo magic with `strndup()', temporary buffers, and god only
	 * knows why there are even delayed calls to `argz_add()' in there???
	 * If this implementation doesn't do exactly what GLibc does, don't fault
	 * me. Every function in this file was originally created as a GLibc
	 * extension, so there really isn't any official documentation on intended
	 * behavior other than GLibc reference implementation.
	 * Anyways... At least my version is readable... */
	while (find_offset < *pargz_len) {
		char *pos;
		pos = (char *)memmem(*pargz + find_offset,
		                     *pargz_len - find_offset,
		                     str, findlen);
		if (!pos)
			break; /* Nothing else to find! */
		if (repllen < findlen) {
			/* Simple case: The replacement string is smaller than the find-string */
			char *old_argz, *new_argz;
			size_t diff, trailing_characters;
			pos  = (char *)mempcpyc(pos, with, repllen, sizeof(char));
			diff = findlen - repllen;
			*pargz_len -= diff;
			old_argz = *pargz;
			trailing_characters = *pargz_len - (size_t)(pos - old_argz);
			memmovedownc(pos, pos + diff, trailing_characters, sizeof(char));
			new_argz = (char *)realloc(old_argz, *pargz_len * sizeof(char));
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
			new_argz = (char *)realloc(old_argz, new_argzlen * sizeof(char));
			if unlikely(!new_argz) {
#ifdef ENOMEM
				return ENOMEM;
#else /* ENOMEM */
				return 1;
#endif /* !ENOMEM */
			}
			pos = new_argz + (pos - old_argz);
			/* Make space for extra data */
			trailing_characters = new_argzlen - ((pos + repllen) - new_argz);
			memmoveupc(pos + repllen,
			           pos + findlen,
			           trailing_characters,
			           sizeof(char));
			/* Fill in the replacement string. */
			pos = (char *)mempcpyc(pos, with, repllen, sizeof(char));
		} else {
			/* Simple case: The replacement string has the same length as the find-string */
			pos = (char *)mempcpyc(pos, with, repllen, sizeof(char));
		}
		if (replace_count)
			++*replace_count;
	}
	return 0;
}


[alias(*)][attribute(*)] __argz_replace:(*) = argz_replace;

@@Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
@@are no more. If entry is NULL, then the first entry is returned. This
@@behavior allows two convenient iteration styles:
@@>> char *entry = NULL;
@@>> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
@@>>     ...;
@@or
@@>> char *entry;
@@>> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
@@>>     ...;
[alias(__argz_next)][ATTR_PURE][ATTR_WUNUSED]
argz_next:([inp_opt(argz_len)] char const *__restrict argz, size_t argz_len, [nullable] char const *__restrict entry) -> char *
	[([inp_opt(argz_len)] char *__restrict argz, size_t argz_len, [nullable] char *__restrict entry) -> char *]
	[([inp_opt(argz_len)] char const *__restrict argz, size_t argz_len, [nullable] char const *__restrict entry) -> char const *]
{
	char const *argz_end;
	if (!entry)
		return argz_len ? (char *)argz : NULL;
	argz_end = argz + argz_len;
	if (entry < argz_end)
		entry = strend(entry) + 1;
	if (entry >= argz_end)
		return NULL;
	return (char *)entry;
}

[alias(*)][attribute(*)] __argz_next:(*) = argz_next;


%{

#endif /* __CC__ */

__SYSDECL_END

}