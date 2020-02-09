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
#ifndef GUARD_LIBC_USER_STRINGLIST_C
#define GUARD_LIBC_USER_STRINGLIST_C 1

#include "../api.h"
/**/

#include "stringlist.h"
#include "stdlib.h"
#include "malloc.h"
#include "string.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:sl_init,hash:CRC-32=0x5de32777]]]*/
/* Allocates and returns a new StringList object. Upon error, `NULL' is returned */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.bsd.stringlist.sl_init") struct _stringlist *
NOTHROW_NCX(LIBCCALL libc_sl_init)(void)
/*[[[body:sl_init]]]*/
/*AUTO*/{
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
/*[[[end:sl_init]]]*/

/*[[[head:sl_add,hash:CRC-32=0xc0c8a094]]]*/
/* Append a given `NAME' to `SL'. `NAME' is considered
 * inherited if the StringList is destroyed with `1' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.bsd.stringlist.sl_add") int
NOTHROW_NCX(LIBCCALL libc_sl_add)(struct _stringlist *sl,
                                  char *name)
/*[[[body:sl_add]]]*/
/*AUTO*/{
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
/*[[[end:sl_add]]]*/

/*[[[head:sl_free,hash:CRC-32=0x3f923a95]]]*/
/* Free a given string list. When `ALL' is non-zero, all contained
 * string pointers (as previously added with `sl_add()') will also
 * be `free(3)'ed. */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.bsd.stringlist.sl_free") void
NOTHROW_NCX(LIBCCALL libc_sl_free)(struct _stringlist *sl,
                                   int all)
/*[[[body:sl_free]]]*/
/*AUTO*/{
	if unlikely(!sl)
		return;
	if likely(sl->sl_str) {
		if (all) {
			size_t i;
			for (i = 0; i < sl->sl_cur; ++i)
				libc_free(sl->sl_str[i]);
		}
		libc_free(sl->sl_str);
	}
	libc_free(sl);
}
/*[[[end:sl_free]]]*/

/*[[[head:sl_find,hash:CRC-32=0xd2246152]]]*/
/* Search for `NAME' within the given StringList. Upon success,
 * return a pointer to the equivalent string within `SL' (i.e. the
 * pointer originally passed to `sl_add()' to insert that string).
 * If `SL' doesn't contain an equivalent string, return `NULL' instead. */
INTERN ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.bsd.stringlist.sl_find") char *
NOTHROW_NCX(LIBCCALL libc_sl_find)(struct _stringlist __KOS_FIXED_CONST *sl,
                                   char const *name)
/*[[[body:sl_find]]]*/
/*AUTO*/{
	size_t i;
	for (i = 0; i < sl->sl_cur; ++i) {
		char *s = sl->sl_str[i];
		if (libc_strcmp(s, name) == 0)
			return s;
	}
	return NULL;
}
/*[[[end:sl_find]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xe3aacf99]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(sl_init, libc_sl_init);
DEFINE_PUBLIC_WEAK_ALIAS(sl_add, libc_sl_add);
DEFINE_PUBLIC_WEAK_ALIAS(sl_free, libc_sl_free);
DEFINE_PUBLIC_WEAK_ALIAS(sl_find, libc_sl_find);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STRINGLIST_C */
