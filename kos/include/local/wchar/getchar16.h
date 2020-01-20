/* HASH CRC-32:0xe666f4c8 */
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
#ifndef __local_getchar16_defined
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc))
#define __local_getchar16_defined 1
#include <kos/anno.h>
#include <local/stdstreams.h>
/* Dependency: "fgetwc" */
#ifndef ____localdep_fgetc16_defined
#define ____localdep_fgetc16_defined 1
#if defined(__CRT_HAVE_fgetwc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_DOS$getwc)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc,(__stream))
#else /* LIBC: fgetc16 */
#undef ____localdep_fgetc16_defined
#endif /* fgetc16... */
#endif /* !____localdep_fgetc16_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getchar16) __WINT_TYPE__
(__LIBDCALL __LIBC_LOCAL_NAME(getchar16))(void) __THROWS(...) {
#line 463 "kos/src/libc/magic/wchar.c"
	return __localdep_fgetc16(__LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#endif /* !__NO_STDSTREAMS && (__CRT_HAVE_fgetwc || __CRT_HAVE_getwc) */
#endif /* !__local_getchar16_defined */
