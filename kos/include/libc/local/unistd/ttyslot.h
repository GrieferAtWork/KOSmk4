/* HASH CRC-32:0x81707488 */
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
#ifndef __local_ttyslot_defined
#define __local_ttyslot_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_ttyname) || defined(__CRT_HAVE___ttyname) || defined(__CRT_HAVE_ttyname_r)) && defined(__CRT_HAVE_setttyent) && defined(__CRT_HAVE_getttyent)
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_endttyent_defined) && defined(__CRT_HAVE_endttyent)
#define __local___localdep_endttyent_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_endttyent,(void),endttyent,())
#endif /* !__local___localdep_endttyent_defined && __CRT_HAVE_endttyent */
#ifndef __local___localdep_getttyent_defined
#define __local___localdep_getttyent_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/db/ttyent.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,struct ttyent *,__NOTHROW_RPC_KOS,__localdep_getttyent,(void),getttyent,())
#endif /* !__local___localdep_getttyent_defined */
#ifndef __local___localdep_setttyent_defined
#define __local___localdep_setttyent_defined
__CREDIRECT(,int,__NOTHROW_RPC_KOS,__localdep_setttyent,(void),setttyent,())
#endif /* !__local___localdep_setttyent_defined */
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
#ifndef __local___localdep_strrchrnul_defined
#define __local___localdep_strrchrnul_defined
#ifdef __CRT_HAVE_strrchrnul
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strrchrnul,(char const *__restrict __haystack, int __needle),strrchrnul,(__haystack,__needle))
#else /* __CRT_HAVE_strrchrnul */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strrchrnul.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strrchrnul __LIBC_LOCAL_NAME(strrchrnul)
#endif /* !__CRT_HAVE_strrchrnul */
#endif /* !__local___localdep_strrchrnul_defined */
#ifndef __local___localdep_ttyname_defined
#define __local___localdep_ttyname_defined
#ifdef __CRT_HAVE_ttyname
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,__localdep_ttyname,(__fd_t __fd),ttyname,(__fd))
#elif defined(__CRT_HAVE___ttyname)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,__localdep_ttyname,(__fd_t __fd),__ttyname,(__fd))
#elif defined(__CRT_HAVE_ttyname_r)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/ttyname.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ttyname __LIBC_LOCAL_NAME(ttyname)
#else /* ... */
#undef __local___localdep_ttyname_defined
#endif /* !... */
#endif /* !__local___localdep_ttyname_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <bits/types.h>
#include <asm/os/stdio.h>
#include <bits/crt/db/ttyent.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ttyslot) __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ttyslot))(void) {
	__fd_t __fd;
	__PRIVATE_FOREACH_STDFILENO(__fd) {
		char const *__tnam;
		int __result;
		struct ttyent *__tty;
		if ((__tnam = (__NAMESPACE_LOCAL_SYM __localdep_ttyname)(__fd)) == __NULLPTR)
			continue;
		__tnam = (__NAMESPACE_LOCAL_SYM __localdep_strrchrnul)(__tnam, '/') + 1;
		(__NAMESPACE_LOCAL_SYM __localdep_setttyent)();
		for (__result = 1; (__tty = (__NAMESPACE_LOCAL_SYM __localdep_getttyent)()) != __NULLPTR; ++__result) {
			if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__tty->ty_name, __tnam) == 0) {
#ifdef __CRT_HAVE_endttyent
				(__NAMESPACE_LOCAL_SYM __localdep_endttyent)();
#endif /* __CRT_HAVE_endttyent */
				return __result;
			}
		}
#ifdef __CRT_HAVE_endttyent
		(__NAMESPACE_LOCAL_SYM __localdep_endttyent)();
#endif /* __CRT_HAVE_endttyent */
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ttyslot_defined
#define __local___localdep_ttyslot_defined
#define __localdep_ttyslot __LIBC_LOCAL_NAME(ttyslot)
#endif /* !__local___localdep_ttyslot_defined */
#else /* (__CRT_HAVE_ttyname || __CRT_HAVE___ttyname || __CRT_HAVE_ttyname_r) && __CRT_HAVE_setttyent && __CRT_HAVE_getttyent */
#undef __local_ttyslot_defined
#endif /* (!__CRT_HAVE_ttyname && !__CRT_HAVE___ttyname && !__CRT_HAVE_ttyname_r) || !__CRT_HAVE_setttyent || !__CRT_HAVE_getttyent */
#endif /* !__local_ttyslot_defined */
