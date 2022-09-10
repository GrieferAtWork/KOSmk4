/* HASH CRC-32:0xc47bf8b5 */
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
#ifndef __local_attr_multi_defined
#define __local_attr_multi_defined
#include <__crt.h>
#include <attr/asm/attributes.h>
#if defined(__ATTR_DONTFOLLOW) && defined(__ATTR_OP_GET) && defined(__ATTR_OP_SET) && defined(__ATTR_OP_REMOVE) && defined(__CRT_HAVE_attr_get) && defined(__CRT_HAVE_attr_set) && defined(__CRT_HAVE_attr_remove)
#include <attr/bits/attributes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_attr_get_defined
#define __local___localdep_attr_get_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_attr_get,(char const *__path, char const *__attrname, char *__attrvalue, int *__valuelength, int __flags),attr_get,(__path,__attrname,__attrvalue,__valuelength,__flags))
#endif /* !__local___localdep_attr_get_defined */
#ifndef __local___localdep_attr_remove_defined
#define __local___localdep_attr_remove_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_attr_remove,(char const *__path, char const *__attrname, int __flags),attr_remove,(__path,__attrname,__flags))
#endif /* !__local___localdep_attr_remove_defined */
#ifndef __local___localdep_attr_set_defined
#define __local___localdep_attr_set_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_attr_set,(char const *__path, char const *__attrname, char const *__attrvalue, int __valuelength, int __flags),attr_set,(__path,__attrname,__attrvalue,__valuelength,__flags))
#endif /* !__local___localdep_attr_set_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(attr_multi) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(attr_multi))(char const *__path, struct attr_multiop *__oplist, int __count, int __flags) {
	int __i, __result = 0;
	if __unlikely(__flags & ~__ATTR_DONTFOLLOW) {
#ifdef __EINVAL
		return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return __libc_seterrno(1);
#endif /* !__EINVAL */
	}
	for (__i = 0; __i < __count; ++__i) {
		struct attr_multiop *__ent = &__oplist[__i];
		int __ent_flags = __ent->am_flags | __flags;
		switch (__ent->am_opcode) {

		case __ATTR_OP_GET:
			__result |= (__NAMESPACE_LOCAL_SYM __localdep_attr_get)(__path,
			                   __ent->am_attrname,
			                   __ent->am_attrvalue,
			                   &__ent->am_length,
			                   __ent_flags);
			break;

		case __ATTR_OP_SET:
			__result |= (__NAMESPACE_LOCAL_SYM __localdep_attr_set)(__path,
			                   __ent->am_attrname,
			                   __ent->am_attrvalue,
			                   __ent->am_length,
			                   __ent_flags);
			break;

		case __ATTR_OP_REMOVE:
			__result |= (__NAMESPACE_LOCAL_SYM __localdep_attr_remove)(__path,
			                      __ent->am_attrname,
			                      __ent_flags);
			break;

		default:
#ifdef __EINVAL
			__result = __libc_seterrno(__EINVAL);
#else /* __EINVAL */
			__result = __libc_seterrno(1);
#endif /* !__EINVAL */
			break;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_attr_multi_defined
#define __local___localdep_attr_multi_defined
#define __localdep_attr_multi __LIBC_LOCAL_NAME(attr_multi)
#endif /* !__local___localdep_attr_multi_defined */
#else /* __ATTR_DONTFOLLOW && __ATTR_OP_GET && __ATTR_OP_SET && __ATTR_OP_REMOVE && __CRT_HAVE_attr_get && __CRT_HAVE_attr_set && __CRT_HAVE_attr_remove */
#undef __local_attr_multi_defined
#endif /* !__ATTR_DONTFOLLOW || !__ATTR_OP_GET || !__ATTR_OP_SET || !__ATTR_OP_REMOVE || !__CRT_HAVE_attr_get || !__CRT_HAVE_attr_set || !__CRT_HAVE_attr_remove */
#endif /* !__local_attr_multi_defined */
