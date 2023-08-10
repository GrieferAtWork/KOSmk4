/* HASH CRC-32:0x789e70ce */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_attr_multif_defined
#define __local_attr_multif_defined
#include <__crt.h>
#include <attr/asm/attributes.h>
#if defined(__ATTR_DONTFOLLOW) && defined(__ATTR_OP_GET) && defined(__ATTR_OP_SET) && defined(__ATTR_OP_REMOVE) && defined(__CRT_HAVE_attr_getf) && defined(__CRT_HAVE_attr_setf) && defined(__CRT_HAVE_attr_removef)
#include <bits/types.h>
#include <attr/bits/attributes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_attr_getf_defined
#define __local___localdep_attr_getf_defined
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN(2) __ATTR_INOUT(4),int,__NOTHROW_NCX,__localdep_attr_getf,(__fd_t __fd, char const *__attrname, char *__attrvalue, int *__valuelength, int __flags),attr_getf,(__fd,__attrname,__attrvalue,__valuelength,__flags))
#endif /* !__local___localdep_attr_getf_defined */
#ifndef __local___localdep_attr_removef_defined
#define __local___localdep_attr_removef_defined
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_attr_removef,(__fd_t __fd, char const *__attrname, int __flags),attr_removef,(__fd,__attrname,__flags))
#endif /* !__local___localdep_attr_removef_defined */
#ifndef __local___localdep_attr_setf_defined
#define __local___localdep_attr_setf_defined
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN(2) __ATTR_INS(3, 4),int,__NOTHROW_NCX,__localdep_attr_setf,(__fd_t __fd, char const *__attrname, char const *__attrvalue, int __valuelength, int __flags),attr_setf,(__fd,__attrname,__attrvalue,__valuelength,__flags))
#endif /* !__local___localdep_attr_setf_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(attr_multif) __ATTR_FDARG(1) __ATTR_INOUTS(2, 3) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(attr_multif))(__fd_t __fd, struct attr_multiop *__oplist, int __count, int __flags) {
	int __i, __result = 0;
	if (__unlikely(__flags & ~__ATTR_DONTFOLLOW) ||
	    __unlikely(__count < 0)
#ifdef __ATTR_MAX_MULTIOPS
	    || __unlikely(__count > __ATTR_MAX_MULTIOPS)
#endif /* __ATTR_MAX_MULTIOPS */
	    ) {
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
			__result |= (__NAMESPACE_LOCAL_SYM __localdep_attr_getf)(__fd,
			                    __ent->am_attrname,
			                    __ent->am_attrvalue,
			                    &__ent->am_length,
			                    __ent_flags);
			break;

		case __ATTR_OP_SET:
			__result |= (__NAMESPACE_LOCAL_SYM __localdep_attr_setf)(__fd,
			                    __ent->am_attrname,
			                    __ent->am_attrvalue,
			                    __ent->am_length,
			                    __ent_flags);
			break;

		case __ATTR_OP_REMOVE:
			__result |= (__NAMESPACE_LOCAL_SYM __localdep_attr_removef)(__fd,
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
		__ent->am_error = __libc_geterrno_or(0);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_attr_multif_defined
#define __local___localdep_attr_multif_defined
#define __localdep_attr_multif __LIBC_LOCAL_NAME(attr_multif)
#endif /* !__local___localdep_attr_multif_defined */
#else /* __ATTR_DONTFOLLOW && __ATTR_OP_GET && __ATTR_OP_SET && __ATTR_OP_REMOVE && __CRT_HAVE_attr_getf && __CRT_HAVE_attr_setf && __CRT_HAVE_attr_removef */
#undef __local_attr_multif_defined
#endif /* !__ATTR_DONTFOLLOW || !__ATTR_OP_GET || !__ATTR_OP_SET || !__ATTR_OP_REMOVE || !__CRT_HAVE_attr_getf || !__CRT_HAVE_attr_setf || !__CRT_HAVE_attr_removef */
#endif /* !__local_attr_multif_defined */
