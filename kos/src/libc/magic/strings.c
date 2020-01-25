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

%{
#include <features.h>
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8)
}

[guard][crtbuiltin]
bcopy:([nonnull] void const *src,
       [nonnull] void *dst, $size_t num_bytes) {
	memmove(dst, src, num_bytes);
}

[guard][crtbuiltin][export_alias(__bzero)]
bzero:([nonnull] void *__restrict dst, $size_t num_bytes) {
	memset(dst, 0, num_bytes);
}

/* FIXME: This declaration causes `bcmp' to be exported by the kernel (which it shouldn't) */
[guard][ATTR_WUNUSED][ATTR_PURE][crtbuiltin]
bcmp:([nonnull] void const *s1,
      [nonnull] void const *s2,
      $size_t num_bytes) -> int = memcmp;


[guard][ATTR_WUNUSED][ATTR_PURE][crtbuiltin]
index:([nonnull] char const *__restrict haystack, int needle) -> char *
	[([nonnull] char *__restrict haystack, int needle) -> char *]
	[([nonnull] char const *__restrict haystack, int needle) -> char const *]
{
	for (; *haystack; ++haystack) {
		if (*haystack == needle)
			return (char *)haystack;
	}
	if (!needle)
		return (char *)haystack;
	return NULL;
}

[guard][ATTR_WUNUSED][ATTR_PURE][crtbuiltin]
rindex:([nonnull] char const *__restrict haystack, int needle) -> char *
	[([nonnull] char *__restrict haystack, int needle) -> char *]
	[([nonnull] char const *__restrict haystack, int needle) -> char const *]
{
	char const *result = NULL;
	for (; *haystack; ++haystack) {
		if (*haystack == needle)
			result = haystack;
	}
	if (!needle)
		return (char *)haystack;
	return (char *)result;
}

%#endif /* __USE_MISC || !__USE_XOPEN2K8 */
%
%[insert:extern(strcasecmp)]
%[insert:extern(strncasecmp)]
%
%#ifdef __USE_XOPEN2K8
%[insert:extern(strcasecmp_l)]
%[insert:extern(strncasecmp_l)]
%#endif /* __USE_XOPEN2K8 */
%
%{
#endif /* __CC__ */

__SYSDECL_END

}

