/* HASH CRC-32:0x6bbfbc3f */
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
#ifndef __local_getfsfile_defined
#define __local_getfsfile_defined
#include <__crt.h>
#if defined(__CRT_HAVE_getfsent) && defined(__CRT_HAVE_setfsent)
#include <bits/crt/db/fstab.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getfsent_defined
#define __local___localdep_getfsent_defined
__CREDIRECT(__ATTR_WUNUSED,struct fstab *,__NOTHROW_NCX,__localdep_getfsent,(void),getfsent,())
#endif /* !__local___localdep_getfsent_defined */
#ifndef __local___localdep_setfsent_defined
#define __local___localdep_setfsent_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setfsent,(void),setfsent,())
#endif /* !__local___localdep_setfsent_defined */
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
__LOCAL_LIBC(getfsfile) __ATTR_WUNUSED __ATTR_ACCESS_RO(1) struct fstab *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getfsfile))(const char *__mount_point) {
	struct fstab *__result;
	if (!(__NAMESPACE_LOCAL_SYM __localdep_setfsent)())
		return __NULLPTR;
	while ((__result = (__NAMESPACE_LOCAL_SYM __localdep_getfsent)()) != __NULLPTR) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__result->fs_file, __mount_point) == 0)
			break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getfsfile_defined
#define __local___localdep_getfsfile_defined
#define __localdep_getfsfile __LIBC_LOCAL_NAME(getfsfile)
#endif /* !__local___localdep_getfsfile_defined */
#else /* __CRT_HAVE_getfsent && __CRT_HAVE_setfsent */
#undef __local_getfsfile_defined
#endif /* !__CRT_HAVE_getfsent || !__CRT_HAVE_setfsent */
#endif /* !__local_getfsfile_defined */
