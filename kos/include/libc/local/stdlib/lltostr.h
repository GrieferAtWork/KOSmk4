/* HASH CRC-32:0x1354d553 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_lltostr_defined
#define __local_lltostr_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ulltostr_defined
#define __local___localdep_ulltostr_defined
#ifdef __CRT_HAVE_ulltostr
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_OUT(2),char *,__NOTHROW_NCX,__localdep_ulltostr,(__ULONGLONG ___value, char *__buf),ulltostr,(___value,__buf))
#else /* __CRT_HAVE_ulltostr */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/ulltostr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ulltostr __LIBC_LOCAL_NAME(ulltostr)
#endif /* !__CRT_HAVE_ulltostr */
#endif /* !__local___localdep_ulltostr_defined */
__LOCAL_LIBC(lltostr) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_OUT(2) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(lltostr))(__LONGLONG ___value, char *__buf) {
	char *__result;
	if (___value < 0) {
		__result    = (__NAMESPACE_LOCAL_SYM __localdep_ulltostr)((__ULONGLONG)0 - ___value, __buf);
		*--__result = '-';
	} else {
		__result = (__NAMESPACE_LOCAL_SYM __localdep_ulltostr)((__ULONGLONG)___value, __buf);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lltostr_defined
#define __local___localdep_lltostr_defined
#define __localdep_lltostr __LIBC_LOCAL_NAME(lltostr)
#endif /* !__local___localdep_lltostr_defined */
#endif /* !__local_lltostr_defined */
