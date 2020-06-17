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

%[define_replacement(pid_t = __pid_t)]
%[default:section(".text.crt{|.dos}.bsd.stringlist")]

%{
#include <features.h>
#include <sys/types.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef ___stringlist_defined
#define ___stringlist_defined 1
typedef struct _stringlist {
	char   **sl_str; /* [1..1][owned(maybe)][0..sl_cur|ALLOC(sl_max)][owned] Vector of strings */
	size_t   sl_max; /* Allocated vector size */
	size_t   sl_cur; /* Used vector size */
} StringList;
#endif /* !___stringlist_defined */

}

%[define(DEFINE_STRINGLIST =
#ifndef ___stringlist_defined
#define ___stringlist_defined 1
typedef struct @_stringlist@ {
	char   **@sl_str@;
	size_t   @sl_max@;
	size_t   @sl_cur@;
} @StringList@;
#endif /* !___stringlist_defined */
)]


@@Allocates and returns a new StringList object. Upon error, `NULL' is returned
[[wunused, decl_prefix(DEFINE_STRINGLIST)]]
[[userimpl, requires($has_function(malloc) && $has_function(free))]]
struct _stringlist *sl_init() {
	struct _stringlist *result;
	result = (struct _stringlist *)malloc(sizeof(struct _stringlist));
	if likely(result != NULL) {
		result->@sl_cur@ = 0;
		result->@sl_max@ = 20;
		result->@sl_str@ = (char **)malloc(20 * sizeof(char *));
		if unlikely(result->@sl_str@ == NULL) {
			free(result);
			result = NULL;
		}
	}
	return result;
}


@@Append a given `NAME' to `SL'. `NAME' is considered
@@inherited if the StringList is destroyed with `1'
[[decl_prefix(DEFINE_STRINGLIST)]]
[[userimpl, requires_function(realloc)]]
int sl_add([[nonnull]] struct _stringlist *sl, [[nonnull]] char *name) {
	if unlikely(sl->@sl_cur@ >= sl->@sl_max@) {
		char **new_vector;
		size_t new_alloc;
		new_alloc = sl->@sl_max@ + 20;
		new_vector = (char **)realloc(sl->@sl_str@, new_alloc * sizeof(char *));
		if unlikely(new_vector == NULL)
			return -1;
		sl->@sl_str@ = new_vector;
		sl->@sl_max@ = new_alloc;
	}
	sl->@sl_str@[sl->@sl_cur@] = name; /* Inherit (maybe) */
	++sl->@sl_cur@;
	return 0;
}

@@Free a given string list. When `ALL' is non-zero, all contained
@@string pointers (as previously added with `sl_add()') will also
@@be `free(3)'ed.
[[decl_prefix(DEFINE_STRINGLIST)]]
[[userimpl, requires_function(free)]]
void sl_free([[nullable]] struct _stringlist *sl, int all) {
	if unlikely(!sl)
		return;
	if likely(sl->@sl_str@) {
		if (all) {
			size_t i;
			for (i = 0; i < sl->@sl_cur@; ++i)
				free(sl->@sl_str@[i]);
		}
		free(sl->@sl_str@);
	}
	free(sl);
}

%[define_c_language_keyword(__KOS_FIXED_CONST)]

@@Search for `NAME' within the given StringList. Upon success,
@@return a pointer to the equivalent string within `SL' (i.e. the
@@pointer originally passed to `sl_add()' to insert that string).
@@If `SL' doesn't contain an equivalent string, return `NULL' instead.
[[decl_include("<features.h>")]]
[[ATTR_PURE, decl_prefix(DEFINE_STRINGLIST)]]
[[nullable]] char *sl_find([[nonnull]] struct _stringlist __KOS_FIXED_CONST *sl,
                           [[nonnull]] char const *name) {
	size_t i;
	for (i = 0; i < sl->@sl_cur@; ++i) {
		char *s = sl->@sl_str@[i];
		if (strcmp(s, name) == 0)
			return s;
	}
	return NULL;
}



%{
#endif /* __CC__ */

__SYSDECL_END

}