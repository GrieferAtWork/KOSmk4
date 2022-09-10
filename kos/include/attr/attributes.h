/* HASH CRC-32:0x24499923 */
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
/* (#) Portability: libattr (/include/attributes.h) */
#ifndef _ATTR_ATTRIBUTES_H
#define _ATTR_ATTRIBUTES_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <attr/asm/attributes.h>
#include <attr/bits/attributes.h>
#include <bits/types.h>
#include <errno.h>

#if !defined(ENOATTR) && defined(ENODATA)
#define ENOATTR ENODATA
#endif /* !ENOATTR && ENODATA */

/* Max size for attribute values */
#if !defined(ATTR_MAX_VALUELEN) && defined(__ATTR_MAX_VALUELEN)
#define ATTR_MAX_VALUELEN __ATTR_MAX_VALUELEN /* Max size for attribute values */
#endif /* !ATTR_MAX_VALUELEN && __ATTR_MAX_VALUELEN */

/* Possible values for the `flags' arguments of functions from `<attr/attributes.h>' */
#if !defined(ATTR_DONTFOLLOW) && defined(__ATTR_DONTFOLLOW)
#define ATTR_DONTFOLLOW __ATTR_DONTFOLLOW /* Don't follow symbolic links */
#endif /* !ATTR_DONTFOLLOW && __ATTR_DONTFOLLOW */
#if !defined(ATTR_ROOT) && defined(__ATTR_ROOT)
#define ATTR_ROOT __ATTR_ROOT /* Prefix attribute names with "trusted." or "xfsroot." (else: ATTR_SECURE) */
#endif /* !ATTR_ROOT && __ATTR_ROOT */
#if !defined(ATTR_TRUST) && defined(__ATTR_TRUST)
#define ATTR_TRUST __ATTR_TRUST /* Ignored... */
#endif /* !ATTR_TRUST && __ATTR_TRUST */
#if !defined(ATTR_SECURE) && defined(__ATTR_SECURE)
#define ATTR_SECURE __ATTR_SECURE /* Prefix attribute names with "security." (else: prefix with "user.") */
#endif /* !ATTR_SECURE && __ATTR_SECURE */
#if !defined(ATTR_CREATE) && defined(__ATTR_CREATE)
#define ATTR_CREATE __ATTR_CREATE /* Create new attribute, fail if attribute already exists (s.a. `XATTR_CREATE') */
#endif /* !ATTR_CREATE && __ATTR_CREATE */
#if !defined(ATTR_REPLACE) && defined(__ATTR_REPLACE)
#define ATTR_REPLACE __ATTR_REPLACE /* Replace existing attribute, fail if attribute doesn't already exists (s.a. `XATTR_REPLACE') */
#endif /* !ATTR_REPLACE && __ATTR_REPLACE */

/* Max allowed value for `attr_multi[f]::count' */
#if !defined(ATTR_MAX_MULTIOPS) && defined(__ATTR_MAX_MULTIOPS)
#define ATTR_MAX_MULTIOPS __ATTR_MAX_MULTIOPS /* Max allowed value for `attr_multi[f]::count' */
#endif /* !ATTR_MAX_MULTIOPS && __ATTR_MAX_MULTIOPS */

/* Possible values for `struct attr_multiop::am_opcode' */
#if !defined(ATTR_OP_GET) && defined(__ATTR_OP_GET)
#define ATTR_OP_GET __ATTR_OP_GET /* Perform a call to `attr_get(3)' or `attr_getf(3)' */
#endif /* !ATTR_OP_GET && __ATTR_OP_GET */
#if !defined(ATTR_OP_SET) && defined(__ATTR_OP_SET)
#define ATTR_OP_SET __ATTR_OP_SET /* Perform a call to `attr_set(3)' or `attr_setf(3)' */
#endif /* !ATTR_OP_SET && __ATTR_OP_SET */
#if !defined(ATTR_OP_REMOVE) && defined(__ATTR_OP_REMOVE)
#define ATTR_OP_REMOVE __ATTR_OP_REMOVE /* Perform a call to `attr_remove(3)' or `attr_removef(3)' */
#endif /* !ATTR_OP_REMOVE && __ATTR_OP_REMOVE */

#ifdef __CC__
__SYSDECL_BEGIN

typedef struct attrlist attrlist_t;
typedef struct attrlist_ent attrlist_ent_t;
typedef struct attrlist_cursor attrlist_cursor_t;
typedef struct attr_multiop attr_multiop_t;

#define ATTR_ENTRY(buf, i) \
	((struct attrlist_ent *)((__BYTE_TYPE__ *)(buf) + ((struct attrlist const *)(buffer))->al_offset[i]))

/* >> attr_get(3), attr_getf(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_DEPRECATED("Use `getxattr(2)\' or `lgetxattr(2)\' instead") __ATTR_IN(1) __ATTR_IN(2) __ATTR_INOUT(4),int,__NOTHROW_NCX,attr_get,(char const *__path, char const *__attrname, char *__attrvalue, int *__valuelength, int __flags),(__path,__attrname,__attrvalue,__valuelength,__flags))
/* >> attr_get(3), attr_getf(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_DEPRECATED("Use `fgetxattr(2)\' instead") __ATTR_IN(2) __ATTR_INOUT(4),int,__NOTHROW_NCX,attr_getf,(__fd_t __fd, char const *__attrname, char *__attrvalue, int *__valuelength, int __flags),(__fd,__attrname,__attrvalue,__valuelength,__flags))
/* >> attr_set(3), attr_setf(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_CREATE | ATTR_REPLACE | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_DEPRECATED("Use `setxattr(2)\' or `lsetxattr(2)\' instead") __ATTR_IN(1) __ATTR_IN(2) __ATTR_INS(3, 4),int,__NOTHROW_NCX,attr_set,(char const *__path, char const *__attrname, char const *__attrvalue, int __valuelength, int __flags),(__path,__attrname,__attrvalue,__valuelength,__flags))
/* >> attr_set(3), attr_setf(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_CREATE | ATTR_REPLACE | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_DEPRECATED("Use `fsetxattr(2)\' instead") __ATTR_IN(2) __ATTR_INS(3, 4),int,__NOTHROW_NCX,attr_setf,(__fd_t __fd, char const *__attrname, char const *__attrvalue, int __valuelength, int __flags),(__fd,__attrname,__attrvalue,__valuelength,__flags))
/* >> attr_remove(3), attr_removef(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_DEPRECATED("Use `removexattr(2)\' or `lremovexattr(2)\' instead") __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,attr_remove,(char const *__path, char const *__attrname, int __flags),(__path,__attrname,__flags))
/* >> attr_remove(3), attr_removef(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_DEPRECATED("Use `fremovexattr(2)\' instead") __ATTR_IN(2),int,__NOTHROW_NCX,attr_removef,(__fd_t __fd, char const *__attrname, int __flags),(__fd,__attrname,__flags))
/* >> attr_list(3), attr_listf(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_DEPRECATED("Use `listxattr(2)\' or `llistxattr(2)\' instead") __ATTR_IN(1) __ATTR_INOUT(5) __ATTR_OUTS(2, 3),int,__NOTHROW_NCX,attr_list,(char const *__path, char *__buffer, int __buffersize, int __flags, struct attrlist_cursor *__cursor),(__path,__buffer,__buffersize,__flags,__cursor))
/* >> attr_list(3), attr_listf(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_DEPRECATED("Use `flistxattr(2)\' instead") __ATTR_INOUT(5) __ATTR_OUTS(2, 3),int,__NOTHROW_NCX,attr_listf,(__fd_t __fd, char *__buffer, int __buffersize, int __flags, struct attrlist_cursor *__cursor),(__fd,__buffer,__buffersize,__flags,__cursor))
#ifdef __CRT_HAVE_attr_multi
/* >> attr_multi(3), attr_multif(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_DEPRECATED("Use `getxattr(2)\', `setxattr(2)\' and `removexattr(2)\' instead") __ATTR_IN(1) __ATTR_INOUTS(2, 3),int,__NOTHROW_NCX,attr_multi,(char const *__path, struct attr_multiop *__oplist, int __count, int __flags),(__path,__oplist,__count,__flags))
#elif defined(__ATTR_DONTFOLLOW) && defined(__ATTR_OP_GET) && defined(__ATTR_OP_SET) && defined(__ATTR_OP_REMOVE) && defined(__CRT_HAVE_attr_get) && defined(__CRT_HAVE_attr_set) && defined(__CRT_HAVE_attr_remove)
#include <libc/local/attr.attributes/attr_multi.h>
/* >> attr_multi(3), attr_multif(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(attr_multi, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_DEPRECATED("Use `getxattr(2)\', `setxattr(2)\' and `removexattr(2)\' instead") __ATTR_IN(1) __ATTR_INOUTS(2, 3) int __NOTHROW_NCX(__LIBCCALL attr_multi)(char const *__path, struct attr_multiop *__oplist, int __count, int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(attr_multi))(__path, __oplist, __count, __flags); })
#endif /* ... */
#ifdef __CRT_HAVE_attr_multif
/* >> attr_multi(3), attr_multif(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_DEPRECATED("Use `fgetxattr(2)\', `fsetxattr(2)\' and `fremovexattr(2)\' instead") __ATTR_INOUTS(2, 3),int,__NOTHROW_NCX,attr_multif,(__fd_t __fd, struct attr_multiop *__oplist, int __count, int __flags),(__fd,__oplist,__count,__flags))
#elif defined(__ATTR_DONTFOLLOW) && defined(__ATTR_OP_GET) && defined(__ATTR_OP_SET) && defined(__ATTR_OP_REMOVE) && defined(__CRT_HAVE_attr_getf) && defined(__CRT_HAVE_attr_setf) && defined(__CRT_HAVE_attr_removef)
#include <libc/local/attr.attributes/attr_multif.h>
/* >> attr_multi(3), attr_multif(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(attr_multif, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_DEPRECATED("Use `fgetxattr(2)\', `fsetxattr(2)\' and `fremovexattr(2)\' instead") __ATTR_INOUTS(2, 3) int __NOTHROW_NCX(__LIBCCALL attr_multif)(__fd_t __fd, struct attr_multiop *__oplist, int __count, int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(attr_multif))(__fd, __oplist, __count, __flags); })
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ATTR_ATTRIBUTES_H */
