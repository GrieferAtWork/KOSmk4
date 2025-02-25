/* HASH CRC-32:0x678005f7 */
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
#ifndef __local_hasmntopt_defined
#define __local_hasmntopt_defined
#include <__crt.h>
#include <bits/crt/db/mntent.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bcmpc_defined
#define __local___localdep_bcmpc_defined
#ifdef __CRT_HAVE_bcmpc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bcmpc,(__s1,__s2,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_memcmpc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcmpc,(__s1,__s2,__elem_count,__elem_size))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmpc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bcmpc __LIBC_LOCAL_NAME(memcmpc)
#endif /* !... */
#endif /* !__local___localdep_bcmpc_defined */
#ifndef __local___localdep_strchrnul_defined
#define __local___localdep_strchrnul_defined
#ifdef __CRT_HAVE_strchrnul
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchrnul,(char const *__restrict __haystack, int __needle),strchrnul,(__haystack,__needle))
#else /* __CRT_HAVE_strchrnul */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strchrnul.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strchrnul __LIBC_LOCAL_NAME(strchrnul)
#endif /* !__CRT_HAVE_strchrnul */
#endif /* !__local___localdep_strchrnul_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__LOCAL_LIBC(hasmntopt) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(hasmntopt))(struct mntent const *__mnt, char const *__opt) {
	char *__str;
	if __likely(__mnt && __opt && (__str = __mnt->mnt_opts) != __NULLPTR) {
		__SIZE_TYPE__ __optlen = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__opt);
		while (*__str) {
			if ((__NAMESPACE_LOCAL_SYM __localdep_bcmpc)(__str, __opt, __optlen, sizeof(char)) == 0 &&
			    (__str[__optlen] == ',' || __str[__optlen] == '\0'))
				return __str;
			__str = (__NAMESPACE_LOCAL_SYM __localdep_strchrnul)(__str, ',');
		}
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_hasmntopt_defined
#define __local___localdep_hasmntopt_defined
#define __localdep_hasmntopt __LIBC_LOCAL_NAME(hasmntopt)
#endif /* !__local___localdep_hasmntopt_defined */
#endif /* !__local_hasmntopt_defined */
