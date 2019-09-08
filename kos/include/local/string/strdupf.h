/* HASH 0x829c4ce6 */
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
#ifndef __local_strdupf_defined
#if ((((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_format_aprintf_pack)) && ((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_format_aprintf_printer)) && ((__has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)) || defined(__CRT_HAVE_vasprintf)) || defined(__CRT_HAVE_vstrdupf))
#define __local_strdupf_defined 1
/* Dependency: "vstrdupf" from "string" */
#ifndef ____localdep_vstrdupf_defined
#define ____localdep_vstrdupf_defined 1
#if defined(__CRT_HAVE_vstrdupf)
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_LIBC_PRINTF(1, 0),char *,__NOTHROW_NCX,__localdep_vstrdupf,(char const *__restrict __format, __builtin_va_list __args),vstrdupf,(__format,__args))
#elif (((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_format_aprintf_pack)) && ((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_format_aprintf_printer)) && ((__has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)) || defined(__CRT_HAVE_vasprintf))
#include <local/string/vstrdupf.h>
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
#define __localdep_vstrdupf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vstrdupf))
#else /* CUSTOM: vstrdupf */
#undef ____localdep_vstrdupf_defined
#endif /* vstrdupf... */
#endif /* !____localdep_vstrdupf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
__LOCAL_LIBC(strdupf) __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_LIBC_PRINTF(1, 0) char *
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(strdupf))(char const *__restrict __format,
                                                      ...) {
#line 3472 "kos/src/libc/magic/string.c"
	char * __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vstrdupf(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* ((((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_format_aprintf_pack)) && ((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_format_aprintf_printer)) && ((__has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)) || defined(__CRT_HAVE_vasprintf)) || defined(__CRT_HAVE_vstrdupf)) */
#endif /* !__local_strdupf_defined */
