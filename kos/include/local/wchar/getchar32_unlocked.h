/* HASH 0x190f1664 */
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
#ifndef __local_getchar32_unlocked_defined
#include <features.h>
#if (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && !defined(__NO_STDSTREAMS)
#define __local_getchar32_unlocked_defined 1
#include <kos/anno.h>
/* Dependency: "fgetwc_unlocked" */
#ifndef ____localdep_fgetc32_unlocked_defined
#define ____localdep_fgetc32_unlocked_defined 1
#if defined(__CRT_HAVE_fgetwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#else /* LIBC: fgetc32_unlocked */
#undef ____localdep_fgetc32_unlocked_defined
#endif /* fgetc32_unlocked... */
#endif /* !____localdep_fgetc32_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getchar32_unlocked) __WINT_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(getchar32_unlocked))(void) __THROWS(...) {
#line 890 "kos/src/libc/magic/wchar.c"
	return __localdep_fgetc32_unlocked(__LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && !defined(__NO_STDSTREAMS) */
#endif /* !__local_getchar32_unlocked_defined */
