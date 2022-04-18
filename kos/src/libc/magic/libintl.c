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
/* (#) Portability: EMX kLIBC     (/libc/include/libintl.h) */
/* (#) Portability: GNU C Library (/intl/libintl.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/libintl.h) */
/* (#) Portability: diet libc     (/include/libintl.h) */
/* (#) Portability: libc6         (/include/libintl.h) */
/* (#) Portability: musl libc     (/include/libintl.h) */
/* (#) Portability: uClibc        (/include/libintl.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.i18n")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/crt/locale.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

#define __USE_GNU_GETTEXT 1 /* We're emulating glibc's <libintl.h> */
#define __GNU_GETTEXT_SUPPORTED_REVISION(major) ((major) == 0 ? 1 : -1)

#ifdef __CC__
__SYSDECL_BEGIN

}

%[define(DEFINE_FALLBACK___LC_MESSAGES =
@@pp_ifndef __LC_MESSAGES@@
#define __LC_MESSAGES 0
@@pp_endif@@
)]

%[insert:prefix(DEFINE_FALLBACK___LC_MESSAGES)]



[[pure, wunused, export_alias("__dcgettext")]]
[[extern_inline, impl_include("<asm/crt/locale.h>")]]
[[impl_prefix(DEFINE_FALLBACK___LC_MESSAGES)]]
char *dcgettext(char const *domainname, [[format_arg]] char const *msgid, int category) {
	return dcngettext(domainname, msgid, NULL, 1, category);
}

[[pure, wunused, export_alias("__dgettext")]]
[[extern_inline, impl_include("<asm/crt/locale.h>")]]
[[impl_prefix(DEFINE_FALLBACK___LC_MESSAGES)]]
char *dgettext(char const *domainname, [[format_arg]] char const *msgid) {
	return dcngettext(domainname, msgid, NULL, 1, __LC_MESSAGES);
}

[[pure, wunused]]
[[extern_inline, impl_include("<asm/crt/locale.h>")]]
[[impl_prefix(DEFINE_FALLBACK___LC_MESSAGES)]]
char *gettext([[format_arg]] char const *msgid) {
	return dcngettext(NULL, msgid, NULL, 1, __LC_MESSAGES);
}


[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[extern_inline, impl_include("<asm/crt/locale.h>")]]
[[impl_prefix(DEFINE_FALLBACK___LC_MESSAGES)]]
char *ngettext([[format_arg]] char const *msgid_singular,
               [[format_arg]] char const *msgid_plural,
               $ulongptr_t n) {
	return dcngettext(NULL, msgid_singular, msgid_plural, n, __LC_MESSAGES);
}

[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[extern_inline, impl_include("<asm/crt/locale.h>")]]
[[impl_prefix(DEFINE_FALLBACK___LC_MESSAGES)]]
char *dngettext(char const *domainname,
                [[format_arg]] char const *msgid_singular,
                [[format_arg]] char const *msgid_plural,
                $ulongptr_t n) {
	return dcngettext(domainname, msgid_singular, msgid_plural, n, __LC_MESSAGES);
}


[[pure, wunused, userimpl, decl_include("<hybrid/typecore.h>")]]
char *dcngettext(char const *domainname,
                 [[format_arg]] char const *msgid_singular,
                 [[format_arg]] char const *msgid_plural,
                 $ulongptr_t n, int category) {
	/* Generic no-op that works, but doesn't actually support languages */
	COMPILER_IMPURE();
	(void)domainname;
	(void)category;
	return n == 1 ? (char *)msgid_singular
	              : (char *)msgid_plural;
}


char *textdomain(char const *domainname);
char *bindtextdomain(char const *domainname, char const *dirname);
char *bind_textdomain_codeset(char const *domainname, char const *codeset);

%[insert:function(__dgettext = dgettext)]
%[insert:function(__dcgettext = dcgettext)]

%{

/* If appropriate, provide macro optimizations of the above functions */
#if (!defined(__OPTIMIZE_SIZE__) && (!defined(__cplusplus) || defined(__USE_CTYPE_MACROS)))
#ifndef __CRT_HAVE_dcngettext
#define dcngettext(domainname, msgid_singular, msgid_plural, n, category) ((char *)((n) == 1 ? (msgid_singular) : (msgid_plural)))
#define dngettext(domainname, msgid_singular, msgid_plural, n)            ((char *)((n) == 1 ? (msgid_singular) : (msgid_plural)))
#define ngettext(msgid_singular, msgid_plural, n)                         ((char *)((n) == 1 ? (msgid_singular) : (msgid_plural)))
#define dgettext(domainname, msgid)                                       ((char *)(msgid))
#define gettext(msgid)                                                    ((char *)(msgid))
#else /* !__CRT_HAVE_dcngettext */
#if 0 /* Let's not bloat program assembly too much ;) */
#define dngettext(domainname, msgid_singular, msgid_plural, n) \
	dcngettext(domainname, msgid_singular, msgid_plural, n, __LC_MESSAGES)
#define dgettext(domainname, msgid) \
	dcngettext(domainname, msgid, __NULLPTR, 1, __LC_MESSAGES)
#define ngettext(msgid_singular, msgid_plural, n) \
	dcngettext(__NULLPTR, msgid_singular, msgid_plural, n, __LC_MESSAGES)
#define gettext(msgid) \
	dcngettext(__NULLPTR, msgid, __NULLPTR, 1, __LC_MESSAGES)
#endif
#endif /* __CRT_HAVE_dcngettext */
#define __dcngettext(domainname, msgid_singular, msgid_plural, n, category) \
	dcngettext(domainname, msgid_singular, msgid_plural, n, category)
#define __dgettext(domainname, msgid) \
	dgettext(domainname, msgid)
#endif /* !__OPTIMIZE_SIZE__ && (!__cplusplus || __USE_CTYPE_MACROS) */

__SYSDECL_END
#endif /* __CC__ */

}
