/* HASH CRC-32:0xbf524b01 */
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
#ifndef GUARD_LIBC_AUTO_STRINGLIST_C
#define GUARD_LIBC_AUTO_STRINGLIST_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "stringlist.h"
#include "../user/stdlib.h"
#include "../user/string.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> sl_init(3)
 * Allocates and returns a new StringList object. Upon error, `NULL' is returned */
INTERN ATTR_SECTION(".text.crt.bsd.stringlist") WUNUSED struct _stringlist *
NOTHROW_NCX(LIBCCALL libc_sl_init)(void) {
	struct _stringlist *result;
	result = (struct _stringlist *)libc_malloc(sizeof(struct _stringlist));
	if likely(result != NULL) {
		result->sl_cur = 0;
		result->sl_max = 20;
		result->sl_str = (char **)libc_malloc(20 * sizeof(char *));
		if unlikely(result->sl_str == NULL) {
			libc_free(result);
			result = NULL;
		}
	}
	return result;
}
/* >> sl_add(3)
 * Append a  given `name'  to  `sl'. `name'  is  considered
 * inherited if the StringList is destroyed with `freeit=1' */
INTERN ATTR_SECTION(".text.crt.bsd.stringlist") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_sl_add)(struct _stringlist *sl,
                                  char *name) {
	if unlikely(sl->sl_cur >= sl->sl_max) {
		char **new_vector;
		size_t new_alloc;
		new_alloc = sl->sl_max + 20;
		new_vector = (char **)libc_realloc(sl->sl_str, new_alloc * sizeof(char *));
		if unlikely(new_vector == NULL)
			return -1;
		sl->sl_str = new_vector;
		sl->sl_max = new_alloc;
	}
	sl->sl_str[sl->sl_cur] = name; /* Inherit (maybe) */
	++sl->sl_cur;
	return 0;
}
/* >> sl_free(3)
 * Free a given string list. When `freeit' is non-zero, all contained
 * string pointers (as previously added with `sl_add()') will also be
 * `free(3)'d. */
INTERN ATTR_SECTION(".text.crt.bsd.stringlist") void
NOTHROW_NCX(LIBCCALL libc_sl_free)(struct _stringlist *sl,
                                   int freeit) {
	if unlikely(!sl)
		return;
	if likely(sl->sl_str) {
		if (freeit) {
			size_t i;
			for (i = 0; i < sl->sl_cur; ++i)
				libc_free(sl->sl_str[i]);
		}
		libc_free(sl->sl_str);
	}
	libc_free(sl);
}
/* >> sl_find(3)
 * Search  for  `name'  within  the  given  StringList.  Upon  success,
 * return a  pointer to  the equivalent  string within  `sl' (i.e.  the
 * pointer originally  passed to  `sl_add()'  to insert  that  string).
 * If `sl' doesn't contain an equivalent string, return `NULL' instead. */
INTERN ATTR_SECTION(".text.crt.bsd.stringlist") ATTR_PURE NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_sl_find)(struct _stringlist __KOS_FIXED_CONST *sl,
                                   char const *name) {
	size_t i, count = sl->sl_cur;
	for (i = 0; i < count; ++i) {
		char *s = sl->sl_str[i];
		if (libc_strcmp(s, name) == 0)
			return s;
	}
	return NULL;
}
/* >> sl_delete(3) [NetBSD]
 * Remove an entry `name' from `sl'
 * When `freeit' is non-zero, a removed string is deallocated using `free(3)'
 * @return: 0:  Successfully removed a string equal to `name'
 * @return: -1: No string equal to `name' was found in `sl' */
INTERN ATTR_SECTION(".text.crt.bsd.stringlist") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_sl_delete)(struct _stringlist *sl,
                                     char const *name,
                                     int freeit) {
	size_t i, count = sl->sl_cur;
	for (i = 0; i < count; ++i) {
		char *s = sl->sl_str[i];
		if (libc_strcmp(s, name) != 0)
			continue;
		/* Found it! */
		sl->sl_cur = --count;
		libc_memmovedownc(&sl->sl_str[i],
		             &sl->sl_str[i + 1],
		             count - i,
		             sizeof(char *));
		if (freeit) {

			libc_free(s);

		}
		return 0;
	}
	return -1; /* Not found */
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(sl_init, libc_sl_init);
DEFINE_PUBLIC_ALIAS(sl_add, libc_sl_add);
DEFINE_PUBLIC_ALIAS(sl_free, libc_sl_free);
DEFINE_PUBLIC_ALIAS(sl_find, libc_sl_find);
DEFINE_PUBLIC_ALIAS(sl_delete, libc_sl_delete);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_STRINGLIST_C */
