/* HASH CRC-32:0x238d28ee */
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

/* ??? */
#if !defined(ATTR_MAX_VALUELEN) && defined(__ATTR_MAX_VALUELEN)
#define ATTR_MAX_VALUELEN __ATTR_MAX_VALUELEN /* ??? */
#endif /* !ATTR_MAX_VALUELEN && __ATTR_MAX_VALUELEN */

/* ??? */
#if !defined(ATTR_DONTFOLLOW) && defined(__ATTR_DONTFOLLOW)
#define ATTR_DONTFOLLOW __ATTR_DONTFOLLOW /* ??? */
#endif /* !ATTR_DONTFOLLOW && __ATTR_DONTFOLLOW */
#if !defined(ATTR_ROOT) && defined(__ATTR_ROOT)
#define ATTR_ROOT __ATTR_ROOT /* ??? */
#endif /* !ATTR_ROOT && __ATTR_ROOT */
#if !defined(ATTR_TRUST) && defined(__ATTR_TRUST)
#define ATTR_TRUST __ATTR_TRUST /* ??? */
#endif /* !ATTR_TRUST && __ATTR_TRUST */
#if !defined(ATTR_SECURE) && defined(__ATTR_SECURE)
#define ATTR_SECURE __ATTR_SECURE /* ??? */
#endif /* !ATTR_SECURE && __ATTR_SECURE */
#if !defined(ATTR_CREATE) && defined(__ATTR_CREATE)
#define ATTR_CREATE __ATTR_CREATE /* ??? */
#endif /* !ATTR_CREATE && __ATTR_CREATE */
#if !defined(ATTR_REPLACE) && defined(__ATTR_REPLACE)
#define ATTR_REPLACE __ATTR_REPLACE /* ??? */
#endif /* !ATTR_REPLACE && __ATTR_REPLACE */

/* ??? */
#if !defined(ATTR_MAX_MULTIOPS) && defined(__ATTR_MAX_MULTIOPS)
#define ATTR_MAX_MULTIOPS __ATTR_MAX_MULTIOPS /* ??? */
#endif /* !ATTR_MAX_MULTIOPS && __ATTR_MAX_MULTIOPS */

/* ??? */
#if !defined(ATTR_OP_GET) && defined(__ATTR_OP_GET)
#define ATTR_OP_GET __ATTR_OP_GET /* ??? */
#endif /* !ATTR_OP_GET && __ATTR_OP_GET */
#if !defined(ATTR_OP_SET) && defined(__ATTR_OP_SET)
#define ATTR_OP_SET __ATTR_OP_SET /* ??? */
#endif /* !ATTR_OP_SET && __ATTR_OP_SET */
#if !defined(ATTR_OP_REMOVE) && defined(__ATTR_OP_REMOVE)
#define ATTR_OP_REMOVE __ATTR_OP_REMOVE /* ??? */
#endif /* !ATTR_OP_REMOVE && __ATTR_OP_REMOVE */

#ifdef __CC__
__SYSDECL_BEGIN

typedef struct attrlist attrlist_t;
typedef struct attrlist_ent attrlist_ent_t;
typedef struct attrlist_cursor attrlist_cursor_t;
typedef struct attr_multiop attr_multiop_t;

#define ATTR_ENTRY(buf, i) \
	((struct attrlist_ent *)((__BYTE_TYPE__ *)(buf) + ((struct attrlist const *)(buffer))->al_offset[i]))

__CDECLARE_OPT(__ATTR_DEPRECATED("Use getxattr(2) or lgetxattr(2) instead"),int,__NOTHROW_NCX,attr_get,(char const *__path, char const *__attrname, char *__attrvalue, int *__valuelength, int __flags),(__path,__attrname,__attrvalue,__valuelength,__flags))
__CDECLARE_OPT(__ATTR_DEPRECATED("Use fgetxattr(2) instead"),int,__NOTHROW_NCX,attr_getf,(__fd_t __fd, char const *__attrname, char *__attrvalue, int *__valuelength, int __flags),(__fd,__attrname,__attrvalue,__valuelength,__flags))
__CDECLARE_OPT(__ATTR_DEPRECATED("Use setxattr(2) or lsetxattr(2) instead"),int,__NOTHROW_NCX,attr_set,(char const *__path, char const *__attrname, char const *__attrvalue, int __valuelength, int __flags),(__path,__attrname,__attrvalue,__valuelength,__flags))
__CDECLARE_OPT(__ATTR_DEPRECATED("Use fsetxattr(2) instead"),int,__NOTHROW_NCX,attr_setf,(__fd_t __fd, char const *__attrname, char const *__attrvalue, int __valuelength, int __flags),(__fd,__attrname,__attrvalue,__valuelength,__flags))
__CDECLARE_OPT(__ATTR_DEPRECATED("Use removexattr(2) or lremovexattr(2) instead"),int,__NOTHROW_NCX,attr_remove,(char const *__path, char const *__attrname, int __flags),(__path,__attrname,__flags))
__CDECLARE_OPT(__ATTR_DEPRECATED("Use fremovexattr(2) instead"),int,__NOTHROW_NCX,attr_removef,(__fd_t __fd, char const *__attrname, int __flags),(__fd,__attrname,__flags))
__CDECLARE_OPT(__ATTR_DEPRECATED("Use listxattr(2) or llistxattr(2) instead"),int,__NOTHROW_NCX,attr_list,(char const *__path, char *__buffer, int __buffersize, int __flags, struct attrlist_cursor *__cursor),(__path,__buffer,__buffersize,__flags,__cursor))
__CDECLARE_OPT(__ATTR_DEPRECATED("Use flistxattr(2) instead"),int,__NOTHROW_NCX,attr_listf,(__fd_t __fd, char *__buffer, int __buffersize, int __flags, struct attrlist_cursor *__cursor),(__fd,__buffer,__buffersize,__flags,__cursor))
__CDECLARE_OPT(__ATTR_DEPRECATED("Use getxattr(2), setxattr(2), removexattr(2) and listxattr(2) instead"),int,__NOTHROW_NCX,attr_multi,(char const *__path, struct attr_multiop *__oplist, int __count, int __flags),(__path,__oplist,__count,__flags))
__CDECLARE_OPT(__ATTR_DEPRECATED("Use getxattr(2), setxattr(2), removexattr(2) and listxattr(2) instead"),int,__NOTHROW_NCX,attr_multif,(__fd_t __fd, struct attr_multiop *__oplist, int __count, int __flags),(__fd,__oplist,__count,__flags))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ATTR_ATTRIBUTES_H */
