/* HASH CRC-32:0xccc1116e */
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
#ifndef __local_getchar32_defined
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc))
#define __local_getchar32_defined 1
#include <kos/anno.h>
#include <local/stdstreams.h>
/* Dependency: "fgetwc" */
#ifndef ____localdep_fgetc32_defined
#define ____localdep_fgetc32_defined 1
#if defined(__CRT_HAVE_fgetwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fgetc32,(__FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fgetc32,(__FILE *__restrict __stream),getwc,(__stream))
#else /* LIBC: fgetc32 */
#undef ____localdep_fgetc32_defined
#endif /* fgetc32... */
#endif /* !____localdep_fgetc32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getchar32) __WINT_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(getchar32))(void) __THROWS(...) {
#line 374 "kos/src/libc/magic/wchar.c"
	return __localdep_fgetc32(__LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#endif /* !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) */
#endif /* !__local_getchar32_defined */
