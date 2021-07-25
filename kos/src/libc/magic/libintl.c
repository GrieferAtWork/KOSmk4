/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: GNU C Library (/intl/libintl.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/libintl.h) */
/* (#) Portability: diet libc     (/include/libintl.h) */
/* (#) Portability: musl libc     (/include/libintl.h) */
/* (#) Portability: uClibc        (/include/libintl.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.i18n")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/crt/locale.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

#define __USE_GNU_GETTEXT 1 /* We're emulating glibc's <libintrl.h> */
#define __GNU_GETTEXT_SUPPORTED_REVISION(major) ((major) == 0 ? 1 : -1)

#ifdef __CC__
__SYSDECL_BEGIN

}

[[userimpl, wunused, pure, export_alias("__dcgettext")]]
char *dcgettext(char const *domainname,
                [[format_arg]] char const *msgid,
                int category) {
	/* Generic no-op that works, but doesn't actually support languages */
	COMPILER_IMPURE();
	(void)domainname;
	(void)category;
	return (char *)msgid;
}

[[wunused, pure, export_alias("__dgettext")]]
[[impl_include("<bits/crt/locale.h>")]]
[[extern_inline, requires_include("<bits/crt/locale.h>")]]
[[requires(($has_function(dcgettext) && defined(__LC_MESSAGES)) ||
           (!defined(__CRT_HAVE_dcgettext) && !defined(__CRT_HAVE___dcgettext)))]]
/* NOTE: When  `dcgettext()'  isn't crt-supported,  then `__LC_MESSAGES'  not being
 *       defined doesn't actually matter since our default impl's going to be used.
 *       To handle that cause, simply stub-define `__LC_MESSAGES' if it's  unknown,
 *       so that the implementation doesn't break.
 *       Essentially, the only case where we can't be implemented is when the linked
 *       CRT _does_ support `dcgettext()', but we don't know what `__LC_MESSAGES' is
 *       supposed to be. */
[[impl_prefix(
#ifndef __LC_MESSAGES
#define __LC_MESSAGES 0
#endif /* !__LC_MESSAGES */
)]]
char *dgettext(char const *domainname, [[format_arg]] char const *msgid) {
	return dcgettext(domainname, msgid, __LC_MESSAGES);
}

[[wunused, pure]]
[[extern_inline, requires($has_function(dgettext))]]
char *gettext([[format_arg]] char const *msgid) {
	return dgettext(NULL, msgid);
}


[[wunused, pure, decl_include("<hybrid/typecore.h>")]]
[[extern_inline, requires($has_function(dgettext))]]
char *ngettext([[format_arg]] char const *msgid_singular,
               [[format_arg]] char const *msgid_plural,
               $ulongptr_t n) {
	return dgettext(NULL, (n) == 1 ? msgid_singular : msgid_plural);
}

[[wunused, pure, decl_include("<hybrid/typecore.h>")]]
[[extern_inline, requires($has_function(dgettext))]]
char *dngettext(char const *domainname,
                [[format_arg]] char const *msgid_singular,
                [[format_arg]] char const *msgid_plural,
                $ulongptr_t n) {
	return dgettext(domainname, (n) == 1 ? msgid_singular : msgid_plural);
}


[[wunused, pure, decl_include("<hybrid/typecore.h>")]]
[[extern_inline, requires($has_function(dcgettext))]]
char *dcngettext(char const *domainname,
                 [[format_arg]] char const *msgid_singular,
                 [[format_arg]] char const *msgid_plural,
                 $ulongptr_t n, int category) {
	return dcgettext(domainname, (n) == 1 ? msgid_singular : msgid_plural, category);
}


char *textdomain(char const *domainname);
char *bindtextdomain(char const *domainname, char const *dirname);
char *bind_textdomain_codeset(char const *domainname, char const *codeset);

%[insert:function(__dgettext = dgettext)]
%[insert:function(__dcgettext = dcgettext)]

%{

/* If appropriate, provide macro optimizations of the above functions */
#if (!defined(__OPTIMIZE_SIZE__) && (!defined(__cplusplus) || defined(__USE_CTYPE_MACROS)))
}
%[insert:pp_if(defined(@dcgettext@) || $has_function(dcgettext))]
%#define dcngettext(domainname, msgid_singular, msgid_plural, n, category) dcgettext(domainname, (n) == 1 ? msgid_singular : msgid_plural, category)
%#define __dcgettext(domainname, msgid, category)                          dcgettext(domainname, msgid, category)
%[insert:pp_endif]
%[insert:pp_if(!defined(__LC_MESSAGES) && !defined(__CRT_HAVE_dcgettext) && !defined(__CRT_HAVE___dcgettext))]
%#define __LC_MESSAGES 0
%[insert:pp_endif]
%[insert:pp_if(defined(__LC_MESSAGES) && (defined(@dcgettext@) || $has_function(dcgettext)))]
%#define dgettext(domainname, msgid)   dcgettext(domainname, msgid, __LC_MESSAGES)
%#define __dgettext(domainname, msgid) dcgettext(domainname, msgid, __LC_MESSAGES)
%[insert:pp_endif]
%[insert:pp_if(defined(@dgettext@) || $has_function(dgettext))]
%#define dngettext(domainname, msgid_singular, msgid_plural, n) dgettext(domainname, (n) == 1 ? msgid_singular : msgid_plural)
%#define gettext(msgid)                                         dgettext(__NULLPTR, msgid)
%[insert:pp_endif]
%[insert:pp_if(defined(@gettext@) || $has_function(gettext))]
%#define ngettext(msgid_singular, msgid_plural, n) gettext((n) == 1 ? msgid_singular : msgid_plural)
%[insert:pp_endif]
%{
#endif /* !__OPTIMIZE_SIZE__ && (!__cplusplus || __USE_CTYPE_MACROS) */

__SYSDECL_END
#endif /* __CC__ */

}
