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

/*[[[head:libc_sl_init,hash:CRC-32=0x329355d0]]]*/
/* Allocates and returns a new StringList object. Upon error, `NULL' is returned */
INTERN ATTR_SECTION(".text.crt.bsd.stringlist") WUNUSED struct _stringlist *
NOTHROW_NCX(LIBCCALL libc_sl_init)(void)
/*[[[body:libc_sl_init]]]*/
/*AUTO*/{
	struct _stringlist *result;
	result = (struct _stringlist *)malloc(sizeof(struct _stringlist));
	if likely(result != NULL) {
		result->sl_cur = 0;
		result->sl_max = 20;
		result->sl_str = (char **)malloc(20 * sizeof(char *));
		if unlikely(result->sl_str == NULL) {
			free(result);
			result = NULL;
		}
	}
	return result;
}
/*[[[end:libc_sl_init]]]*/

/*[[[head:libc_sl_add,hash:CRC-32=0x7412a6f9]]]*/
/* Append a given `NAME' to `SL'. `NAME' is considered
 * inherited if the StringList is destroyed with `1' */
INTERN ATTR_SECTION(".text.crt.bsd.stringlist") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_sl_add)(struct _stringlist *sl,
                                  char *name)
/*[[[body:libc_sl_add]]]*/
/*AUTO*/{
	if unlikely(sl->sl_cur >= sl->sl_max) {
		char **new_vector;
		size_t new_alloc;
		new_alloc = sl->sl_max + 20;
		new_vector = (char **)realloc(sl->sl_str, new_alloc * sizeof(char *));
		if unlikely(new_vector == NULL)
			return -1;
		sl->sl_str = new_vector;
		sl->sl_max = new_alloc;
	}
	sl->sl_str[sl->sl_cur] = name; /* Inherit (maybe) */
	++sl->sl_cur;
	return 0;
}
/*[[[end:libc_sl_add]]]*/

/*[[[head:libc_sl_free,hash:CRC-32=0xa22950cf]]]*/
/* Free a given string list. When `ALL' is non-zero, all contained
 * string pointers (as previously added with `sl_add()') will also
 * be `free(3)'ed. */
INTERN ATTR_SECTION(".text.crt.bsd.stringlist") void
NOTHROW_NCX(LIBCCALL libc_sl_free)(struct _stringlist *sl,
                                   int all)
/*[[[body:libc_sl_free]]]*/
/*AUTO*/{
	if unlikely(!sl)
		return;
	if likely(sl->sl_str) {
		if (all) {
			size_t i;
			for (i = 0; i < sl->sl_cur; ++i)
				free(sl->sl_str[i]);
		}
		free(sl->sl_str);
	}
	free(sl);
}
/*[[[end:libc_sl_free]]]*/


/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x1eb57cca]]]*/
DEFINE_PUBLIC_ALIAS(sl_init, libc_sl_init);
DEFINE_PUBLIC_ALIAS(sl_add, libc_sl_add);
DEFINE_PUBLIC_ALIAS(sl_free, libc_sl_free);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STRINGLIST_C */
