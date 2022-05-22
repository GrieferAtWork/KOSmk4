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
/* (#) Portability: Cygwin        (/newlib/libc/include/argz.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/argz.h) */
/* (#) Portability: GNU C Library (/string/argz.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/argz.h) */
/* (#) Portability: libc6         (/include/argz.h) */
/* (#) Portability: mintlib       (/include/argz.h) */
}

%[default:section(".text.crt{|.dos}.string.argz")]
%[define_partial_replacement(argc = ___argc)]
%[define_partial_replacement(argv = ___argv)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/types.h>
)]%{

/*
 * Note  that the KOS implementations of these functions was written entirely
 * from scratch, only using GLibc's implementation as a reference (which also
 * resulted in me discovering some bugs in GLibc's version that I'm not going
 * to  report because at least in my  mind, these are just suuuuch _absolute_
 * beginner's mistakes...)
 * The function's that I've fixed are:
 *  - argz_add_sep()
 *  - argz_insert()
 */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __error_t_defined
#define __error_t_defined
typedef __errno_t error_t;
#endif /* !__error_t_defined */

}

%[define_replacement(error_t = __errno_t)]


@@>> argz_create(3)
@@Construct  an  argz-string  from  a  given  NULL-terminated  `argv'-vector,
@@as is also passed to main(), and accepted by the exec() family of functions
@@An  argz-string is imply a string of '\0'-seperated sub-strings, where each
@@sub-string represents one of the original strings from `argv'
@@
@@The base-pointer to this string is stored in `*pargz'
@@
@@The overall length of the argz-string is  tracked at the offset from its  base
@@pointer, to the first  byte after a trailing  '\0' character that follows  the
@@last of the many sub-strings. An empty argz-string is thus represented as  any
@@base-pointer in conjunction with `*pargz_len=0'. (But note that GLibc seems to
@@suggest that certain APIs  should be used under  the assumption that an  empty
@@argz-string  can also be represented with the base pointer `*pargz=NULL'. This
@@kind of behavior is _NOT_ actually supported  by the API, and only implied  by
@@some (apparently) badly worded documentation of `argz_next(3)')
@@
@@When an argz-string is no longer needed, it can be destroyed by passing its
@@base pointer (as filled in at `*pargz' by this function, and updated by the
@@many other functions in this header) to `free(3)'
@@@return: 0 :     Success
@@@return: ENOMEM: Insufficient heap memory
[[decl_include("<bits/types.h>")]]
[[export_alias("__argz_create"), requires_function(malloc)]]
[[impl_include("<libc/errno.h>", "<hybrid/__assert.h>")]]
error_t argz_create([[in]] char *const argv[],
                    [[out]] char **__restrict pargz,
                    [[out]] size_t *__restrict pargz_len) {
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
@@pp_ifdef ENOMEM@@
			return ENOMEM;
@@pp_else@@
			return 1;
@@pp_endif@@
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

%[insert:function(__argz_create = argz_create)]

@@>> argz_create_sep(3)
@@Create an argz-string from `string' by splitting that string at each
@@occurrence of `sep'. This function behaves the same as the following
@@pseudo-code:
@@    [*pargz, *pargz_len] = string.replace(sep, "\0").replaceall("\0\0", "\0");
@@As can be seen in the pseudo-code, duplicate, successive instance of
@@`sep' are merged, such that no empty sub-strings will be present  in
@@the resulting argz-string.
@@For more information on the semantics of argz-strings, see the
@@documentation of `argz_create()'
@@@return: 0 :     Success
@@@return: ENOMEM: Insufficient heap memory
[[decl_include("<bits/types.h>")]]
[[export_alias("__argz_create_sep")]]
[[requires_function(malloc)]]
[[impl_include("<libc/errno.h>")]]
error_t argz_create_sep([[in]] char const *__restrict string, int sep,
                        [[out]] char **__restrict pargz,
                        [[out]] size_t *__restrict pargz_len) {
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
@@pp_ifdef ENOMEM@@
		return ENOMEM;
@@pp_else@@
		return 1;
@@pp_endif@@
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
@@pp_if $has_function(free)@@
		free(result_string);
@@pp_endif@@
		goto empty_argz;
	}
	/* Write the terminating NUL-byte (if there isn't one already) */
	if (dst[-1] != '\0')
		*dst++ = '\0';
	*pargz_len = (size_t)(dst - result_string);
	return 0;
}

%[insert:function(__argz_create_sep = argz_create_sep)]

@@>> argz_count(3)
@@Count and return the # of strings in `argz'
@@Simply count the number of`NUL-characters within `argz...+=argz_len'
[[pure, decl_include("<hybrid/typecore.h>")]]
[[export_alias("__argz_count")]]
size_t argz_count([[in(argz_len)]] char const *argz, size_t argz_len) {
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

%[insert:function(__argz_count = argz_count)]

@@>> argz_extract(3)
@@Extend pointers to  individual string  from `argz',  and sequentially  write them  to
@@`argv',  for which the caller is responsivle to provide sufficient space to hold them
@@all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements)
[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__argz_extract")]]
void argz_extract([[in(argz_len)]] char const *__restrict argz, size_t argz_len, [[out]] char **__restrict argv)
	[[([in(argz_len)] char *__restrict argz, size_t argz_len, [[out]] char **__restrict argv)]]
	[[([in(argz_len)] char const *__restrict argz, size_t argz_len, [[out]] char const **__restrict argv)]]
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

%[insert:function(__argz_extract = argz_extract)]

@@>> argz_stringify(3)
@@Convert  an  `argz' string  into a  NUL-terminated c-string
@@with a total `strlen(argz) == len - 1', by replacing all of
@@the NUL-characters separating  the individual  argz-strings
@@with `sep'.
[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__argz_stringify")]]
void argz_stringify([[inout(len)]] char *argz, size_t len, int sep) {
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

%[insert:function(__argz_stringify = argz_stringify)]


@@>> argz_append(3)
@@Increase allocated memory of `*pargz' and append `buf...+=buf_len'
@@@return: 0 :     Success
@@@return: ENOMEM: Insufficient heap memory
[[decl_include("<bits/types.h>")]]
[[requires_function(realloc)]]
[[export_alias("__argz_create_sep")]]
[[impl_include("<libc/errno.h>")]]
error_t argz_append([[inout]] char **__restrict pargz,
                    [[inout]] size_t *__restrict pargz_len,
                    [[in(buf_len)]] char const *__restrict buf,
                    size_t buf_len) {
	size_t oldlen = *pargz_len;
	size_t newlen = oldlen + buf_len;
	char *newargz = (char *)realloc(*pargz, newlen * sizeof(char));
	if unlikely(!newargz) {
@@pp_ifdef ENOMEM@@
		return ENOMEM;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	memcpyc(newargz + oldlen, buf, buf_len, sizeof(char));
	*pargz     = newargz;
	*pargz_len = newlen;
	return 0;
}

%[insert:function(__argz_append = argz_append)]

@@>> argz_add(3)
@@Append `str' (including its trailing NUL) to the argz string in `*pargz...+=pargz_len'
@@This    is    the   same    as   `argz_append(pargz, pargz_len, str, strlen(str) + 1)'
@@@return: 0 :     Success
@@@return: ENOMEM: Insufficient heap memory
[[decl_include("<bits/types.h>")]]
[[export_alias("__argz_add")]]
[[requires_function(argz_append)]]
error_t argz_add([[inout]] char **__restrict pargz,
                 [[inout]] size_t *__restrict pargz_len,
                 [[in]] char const *__restrict str) {
	return argz_append(pargz, pargz_len, str, strlen(str) + 1);
}

%[insert:function(__argz_add = argz_add)]

@@>> argz_add_sep(3)
@@A  combination of `argz_create_sep()'  and `argz_append()' that will
@@append a duplication of `string' onto `*pargz', whilst replacing all
@@instances of `sep' with NUL-characters,  thus turning them into  the
@@markers  between  separate  strings.  Note  however  that duplicate,
@@successive instance of  `sep' are  merged, such that  no empty  sub-
@@strings will be present in the resulting argz-string.
@@@return: 0 :     Success
@@@return: ENOMEM: Insufficient heap memory
[[decl_include("<bits/types.h>")]]
[[export_alias("__argz_add_sep")]]
[[requires_function(realloc)]]
[[impl_include("<libc/errno.h>")]]
error_t argz_add_sep([[inout]] char **__restrict pargz,
                     [[inout]] size_t *__restrict pargz_len,
                     [[in]] char const *__restrict string,
                     int sep) {
	char *result_string, *dst;
	size_t oldlen;
	size_t slen = strlen(string);
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
	result_string = (char *)realloc(*pargz, (oldlen + (slen + 1)) * sizeof(char));
	if unlikely(!result_string) {
@@pp_ifdef ENOMEM@@
		return ENOMEM;
@@pp_else@@
		return 1;
@@pp_endif@@
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

%[insert:function(__argz_add_sep = argz_add_sep)]

@@>> argz_delete(3)
@@Find the index  of `entry' inside  of `pargz...+=pargz_len', and,  if
@@found, remove that entry by shifting all following elements downwards
@@by one, as well as decrementing `*pargz_len' by one.
@@Note that `entry' must  be the actual pointer  to one of the  elements
@@of the given `pargz...+=pargz_len', and not just a string equal to one
@@of the elements... (took me a while to realize this one)
[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__argz_add_sep")]]
void argz_delete([[inout]] char **__restrict pargz,
                 [[inout]] size_t *__restrict pargz_len,
                 [[in_opt]] char *entry) {
	size_t entrylen, newlen;
	if unlikely(!entry)
		return;
	entrylen  = strlen(entry) + 1;
	newlen    = *pargz_len - entrylen;
	*pargz_len = newlen;
	if unlikely(newlen == 0) {
@@pp_if $has_function(free)@@
		free(*pargz);
@@pp_endif@@
		*pargz = NULL;
		return;
	}
	memmovedownc(entry, entry + entrylen,
	             (newlen - (size_t)(entry - *pargz)),
	             sizeof(char));
}

%[insert:function(__argz_delete = argz_delete)]

@@>> argz_insert(3)
@@When `before' is  `NULL', do the  same as  `argz_add(pargz, pargz_len, entry)'
@@Otherwise,  `before' should point  somewhere into the middle,  or to the start
@@of an existing argument entry, who's  beginning will first be located,  before
@@this function will then allocate additional memory to insert a copy of `entry'
@@such that the copy will appear before the entry pointed to by `before'
@@@return: 0 :     Success
@@@return: ENOMEM: Insufficient heap memory
@@@return: EINVAL: The given `before' is either `NULL', or apart of `*pargz'
[[decl_include("<bits/types.h>")]]
[[export_alias("__argz_insert")]]
[[requires_function(realloc, argz_add)]]
[[impl_include("<libc/errno.h>")]]
error_t argz_insert([[inout]] char **__restrict pargz,
                    [[inout]] size_t *__restrict pargz_len,
                    [[in_opt]] char *before,
                    [[in]] char const *__restrict entry) {
	char *argz;
	size_t argz_len;
	size_t entry_len;
	size_t insert_offset;
	if (!before)
		return argz_add(pargz, pargz_len, entry);
	argz     = *pargz;
	argz_len = *pargz_len;
	if (before < argz || before >= argz + argz_len) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
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
	entry_len = strlen(entry) + 1;
	argz_len += entry_len;
	insert_offset = (size_t)(before - argz);
	argz = (char *)realloc(argz, argz_len * sizeof(char));
	if unlikely(!argz) {
@@pp_ifdef ENOMEM@@
		return ENOMEM;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	/* Update argz-pointers. */
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

%[insert:function(__argz_insert = argz_insert)]


@@>> argz_replace(3)
@@Replace all matches of `str' inside of every string or sub-string from `pargz...+=pargz_len'
@@with `with', and resize the  argz-string if necessary. For  every replacement that is  done,
@@the given `replace_count' is incremented by one (if `replace_count' is non-NULL)
@@@return: 0:      Success
@@@return: ENOMEM: Insufficient heap memory (can only happen when `strlen(with) > strlen(str)',
@@                 but  note  that  the GLibc  implementation  of this  function  is completely
@@                 unreadable and may be able to return this for other cases as well...)
[[decl_include("<bits/types.h>")]]
[[export_alias("__argz_replace")]]
[[requires_function(realloc, free)]]
[[impl_include("<libc/errno.h>")]]
error_t argz_replace([[inout]] char **__restrict pargz,
                     [[inout]] size_t *__restrict pargz_len,
                     [[in_opt]] char const *__restrict str,
                     [[in]] char const *__restrict with,
                     [[inout_opt]] unsigned int *__restrict replace_count) {
	size_t findlen, repllen;
	size_t find_offset;
	if unlikely(!str)
		return 0; /* no-op */
	findlen = strlen(str);
	if unlikely(!findlen)
		return 0; /* no-op */
	repllen = strlen(with);
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
@@pp_ifdef ENOMEM@@
				return ENOMEM;
@@pp_else@@
				return 1;
@@pp_endif@@
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


%[insert:function(__argz_replace = argz_replace)]

@@>> argz_next(3)
@@Iterate the individual strings that make up a given argz-vector.
@@This function  is  intended  to  be  used  in  one  of  2  ways:
@@>> char *my_entry = NULL;
@@>> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
@@>>     handle_entry(my_entry);
@@or alternatively (if you like bloat):
@@>> char *entry;
@@>> for (entry = argz_len ? argz : NULL; entry != NULL;
@@>>      entry = argz_next(argz, argz_len, entry))
@@>>     handle_entry(my_entry);
@@Note  that  GLibc documents  the second  usage  case slightly  different, and
@@writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
@@thus assuming that an empty argz-string (i.e. `argz_len == 0') always has its
@@base pointer set to `NULL'  (which isn't something consistently enforced,  or
@@required  by any of  the other APIs, so  I'd just suggest  you always use the
@@first variant)
@@
@@Behavior:
@@ - When entry is `NULL', `return argz_len ? argz : NULL'
@@ - If `entry' points at, or past the end of `argz', return `NULL'
@@ - If the successor of `entry' points at, or past the end of `argz', return `NULL'
@@ - Return the successor of `entry' (i.e. `strend(entry) + 1')
[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[export_alias("__argz_next")]]
char *argz_next([[in(argz_len)]] char const *__restrict argz, size_t argz_len, [[in_opt]] char const *__restrict entry)
	[[([[in(argz_len)]] char *__restrict argz, size_t argz_len, [[in_opt]] char *__restrict entry): char *]]
	[[([[in(argz_len)]] char const *__restrict argz, size_t argz_len, [[in_opt]] char const *__restrict entry): char const *]]
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

%[insert:function(__argz_next = argz_next)]


%{

__SYSDECL_END
#endif /* __CC__ */

}
