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
#ifndef GUARD_LIBC_USER_ARGZ_C
#define GUARD_LIBC_USER_ARGZ_C 1

#include "../api.h"
/**/

#include "stdlib.h"
#include "malloc.h"
#include "string.h"
#include "argz.h"
#include <parts/errno.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:argz_create,hash:CRC-32=0xa4b6d8cd]]]*/
/* Make a '\0' separated arg vector from a unix argv vector, returning it in
 * `PARGZ', and the total length in `PLEN'. If a memory allocation error occurs,
 * `ENOMEM' is returned, otherwise `0'. The result can be destroyed using `free()' */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.argz.argz_create") error_t
NOTHROW_NCX(LIBCCALL libc_argz_create)(char *const argv[],
                                       char **__restrict pargz,
                                       size_t *__restrict pargz_len)
/*[[[body:argz_create]]]*/
/*AUTO*/{
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
#ifdef __ENOMEM
			return __ENOMEM;
#else /* __ENOMEM */
			return 1;
#endif /* !__ENOMEM */
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
/*[[[end:argz_create]]]*/

/*[[[head:argz_create_sep,hash:CRC-32=0xc9f3b0a6]]]*/
/* Make a '\0' separated arg vector from a `SEP' separated list in
 * `STRING', returning it in `PARGZ', and the total length in `PLEN'.
 * If a memory allocation error occurs, `ENOMEM' is returned, otherwise `0'.
 * The result can be destroyed using `free()' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.string.argz.argz_create_sep") error_t
NOTHROW_NCX(LIBCCALL libc_argz_create_sep)(char const *__restrict string,
                                           int sep,
                                           char **__restrict pargz,
                                           size_t *__restrict pargz_len)
/*[[[body:argz_create_sep]]]*/
/*AUTO*/{
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
#ifdef __ENOMEM
		return __ENOMEM;
#else /* __ENOMEM */
		return 1;
#endif /* !__ENOMEM */
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
/*[[[end:argz_create_sep]]]*/

/*[[[head:argz_append,hash:CRC-32=0x99afdff1]]]*/
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.argz.argz_append") error_t
NOTHROW_NCX(LIBCCALL libc_argz_append)(char **__restrict pargz,
                                       size_t *__restrict pargz_len,
                                       char const *__restrict buf,
                                       size_t buf_len)
/*[[[body:argz_append]]]*/
/*AUTO*/{
	size_t oldlen = *pargz_len;
	size_t newlen = oldlen + buf_len;
	char *newargz = (char *)libc_realloc(*pargz, newlen * sizeof(char));
	if unlikely(!newargz) {
#ifdef __ENOMEM
		return __ENOMEM;
#else /* __ENOMEM */
		return 1;
#endif /* !__ENOMEM */
	}
	memcpy(newargz + oldlen, buf, buf_len * sizeof(char));
	*pargz     = newargz;
	*pargz_len = newlen;
	return 0;
}
/*[[[end:argz_append]]]*/

/*[[[head:argz_add,hash:CRC-32=0xdf1b6f58]]]*/
/* Append `STR' to the argz vector in `PARGZ & PARGZ_LEN' */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.argz.argz_add") error_t
NOTHROW_NCX(LIBCCALL libc_argz_add)(char **__restrict pargz,
                                    size_t *__restrict pargz_len,
                                    char const *__restrict str)
/*[[[body:argz_add]]]*/
/*AUTO*/{
	return libc_argz_append(pargz, pargz_len, str, libc_strlen(str) + 1);
}
/*[[[end:argz_add]]]*/

/*[[[head:argz_add_sep,hash:CRC-32=0xdc0a6f64]]]*/
/* Append `SEP' separated list in `STRING' to the argz vector in `PARGZ & PARGZ_LEN' */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.argz.argz_add_sep") error_t
NOTHROW_NCX(LIBCCALL libc_argz_add_sep)(char **__restrict pargz,
                                        size_t *__restrict pargz_len,
                                        char const *__restrict string,
                                        int sep)
/*[[[body:argz_add_sep]]]*/
/*AUTO*/{
	char *result_string, *dst;
	size_t oldlen;
	size_t slen = libc_strlen(string);
	if unlikely(!slen)
		return 0;
	oldlen = *pargz_len;
	/* Note that GLibc actually has a bug here that causes it write `NULL'
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
	 * unmodified `*pargz' pointer (or at the very least, a simultanious
	 * setting of the `*pargz_len' pointer to ZERO(0)), you may look at
	 * Glibc's version of `argz_append()', which handles that case as
	 * leaving all pointers unmodified (just as one should)
	 */
	result_string = (char *)libc_realloc(*pargz, (oldlen + (slen + 1)) * sizeof(char));
	if unlikely(!result_string) {
#ifdef __ENOMEM
		return __ENOMEM;
#else /* __ENOMEM */
		return 1;
#endif /* !__ENOMEM */
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
/*[[[end:argz_add_sep]]]*/

/*[[[head:argz_delete,hash:CRC-32=0x4e168663]]]*/
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.argz.argz_delete") void
NOTHROW_NCX(LIBCCALL libc_argz_delete)(char **__restrict pargz,
                                       size_t *__restrict pargz_len,
                                       char *entry)
/*[[[body:argz_delete]]]*/
/*AUTO*/{
	size_t entrylen, newlen;
	if unlikely(!entry)
		return;
	entrylen  = libc_strlen(entry) + 1;
	newlen    = *pargz_len - entrylen;
	*pargz_len = newlen;
	if unlikely(newlen == 0) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
		libc_free(*pargz);
#endif /* defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) */
		*pargz = NULL;
		return;
	}
	memmove(entry, entry + entrylen,
	        (newlen - (size_t)(entry - *pargz)) *
	        sizeof(char));
}
/*[[[end:argz_delete]]]*/

/*[[[head:argz_insert,hash:CRC-32=0xeed0d7a2]]]*/
/* Insert `ENTRY' into `ARGZ & ARGZ_LEN' before `BEFORE', which should be an
 * existing entry in `ARGZ'; if `BEFORE' is `NULL', `ENTRY' is appended to the end.
 * Since `ARGZ's first entry is the same as `ARGZ', `argz_insert(ARGZ, ARGZ_LEN, ARGZ, ENTRY)'
 * will insert `ENTRY' at the beginning of `ARGZ'. If `BEFORE' is not in `ARGZ', `EINVAL'
 * is returned, else if memory can't be allocated for the new `ARGZ', `ENOMEM' is returned.
 * On success, `0' is returned */
INTERN NONNULL((1, 2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.string.argz.argz_insert") error_t
NOTHROW_NCX(LIBCCALL libc_argz_insert)(char **__restrict pargz,
                                       size_t *__restrict pargz_len,
                                       char *before,
                                       char const *__restrict entry)
/*[[[body:argz_insert]]]*/
/*AUTO*/{
	char *argz;
	size_t argz_len;
	size_t entry_len;
	size_t insert_offset;
	if (!before)
		return libc_argz_add(pargz, pargz_len, entry);
	argz     = *pargz;
	argz_len = *pargz_len;
	if (before < argz || before >= argz + argz_len) {
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
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
	entry_len = libc_strlen(entry) + 1;
	argz_len += entry_len;
	insert_offset = (size_t)(before - argz);
	argz = (char *)libc_realloc(argz, argz_len * sizeof(char));
	if unlikely(!argz) {
#ifdef __ENOMEM
		return __ENOMEM;
#else /* __ENOMEM */
		return 1;
#endif /* !__ENOMEM */
	}
	/* Update ARGZ pointers. */
	*pargz     = argz;
	*pargz_len = argz_len;
	/* Make space for the new entry. */
	memmove(argz + insert_offset + entry_len,
	        argz + insert_offset,
	        (argz_len - (insert_offset + entry_len)) * sizeof(char));
	/* Insert the new entry. */
	memcpy(argz + insert_offset,
	       entry,
	       entry_len * sizeof(char));
	return 0;
}
/*[[[end:argz_insert]]]*/

/*[[[head:argz_replace,hash:CRC-32=0x97ab26de]]]*/
/* Replace any occurrences of the string `STR' in `PARGZ' with `WITH', reallocating
 * `PARGZ' as necessary. If `PREPLACE_COUNT' is non-NULL, `*PREPLACE_COUNT' will be
 * incremented by number of replacements performed */
INTERN NONNULL((1, 2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.string.argz.argz_replace") error_t
NOTHROW_NCX(LIBCCALL libc_argz_replace)(char **__restrict pargz,
                                        size_t *__restrict pargz_len,
                                        char const *__restrict str,
                                        char const *__restrict with,
                                        unsigned int *__restrict replace_count)
/*[[[body:argz_replace]]]*/
/*AUTO*/{
	size_t findlen, repllen;
	size_t find_offset;
	if unlikely(!str)
		return 0; /* no-op */
	findlen = libc_strlen(str);
	if unlikely(!findlen)
		return 0; /* no-op */
	repllen = libc_strlen(with);
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
		pos = (char *)libc_memmem(*pargz + find_offset,
		                     *pargz_len - find_offset,
		                     str, findlen);
		if (!pos)
			break; /* Nothing else to find! */
		if (repllen < findlen) {
			/* Simple case: The replacement string is smaller than the find-string */
			char *old_argz, *new_argz;
			size_t diff, trailing_characters;
			pos  = (char *)mempcpy(pos, with, repllen * sizeof(char));
			diff = findlen - repllen;
			*pargz_len -= diff;
			old_argz = *pargz;
			trailing_characters = *pargz_len - (size_t)(pos - old_argz);
			memmove(pos, pos + diff, trailing_characters * sizeof(char));
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
#ifdef __ENOMEM
				return __ENOMEM;
#else /* __ENOMEM */
				return 1;
#endif /* !__ENOMEM */
			}
			pos = new_argz + (pos - old_argz);
			/* Make space for extra data */
			trailing_characters = new_argzlen - ((pos + repllen) - new_argz);
			memmove(pos + repllen,
			        pos + findlen,
			        trailing_characters * sizeof(char));
			/* Fill in the replacement string. */
			pos = (char *)mempcpy(pos, with, repllen * sizeof(char));
		} else {
			/* Simple case: The replacement string has the same length as the find-string */
			pos = (char *)mempcpy(pos, with, repllen * sizeof(char));
		}
		if (replace_count)
			++*replace_count;
	}
	return 0;
}
/*[[[end:argz_replace]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xff6436fc]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(argz_create, libc_argz_create);
DEFINE_PUBLIC_WEAK_ALIAS(__argz_create, libc_argz_create);
DEFINE_PUBLIC_WEAK_ALIAS(argz_create_sep, libc_argz_create_sep);
DEFINE_PUBLIC_WEAK_ALIAS(__argz_create_sep, libc_argz_create_sep);
DEFINE_PUBLIC_WEAK_ALIAS(argz_append, libc_argz_append);
DEFINE_PUBLIC_WEAK_ALIAS(__argz_append, libc_argz_append);
DEFINE_PUBLIC_WEAK_ALIAS(argz_add, libc_argz_add);
DEFINE_PUBLIC_WEAK_ALIAS(__argz_add, libc_argz_add);
DEFINE_PUBLIC_WEAK_ALIAS(argz_add_sep, libc_argz_add_sep);
DEFINE_PUBLIC_WEAK_ALIAS(__argz_add_sep, libc_argz_add_sep);
DEFINE_PUBLIC_WEAK_ALIAS(argz_delete, libc_argz_delete);
DEFINE_PUBLIC_WEAK_ALIAS(__argz_delete, libc_argz_delete);
DEFINE_PUBLIC_WEAK_ALIAS(argz_insert, libc_argz_insert);
DEFINE_PUBLIC_WEAK_ALIAS(__argz_insert, libc_argz_insert);
DEFINE_PUBLIC_WEAK_ALIAS(argz_replace, libc_argz_replace);
DEFINE_PUBLIC_WEAK_ALIAS(__argz_replace, libc_argz_replace);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ARGZ_C */
