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
#ifndef GUARD_LIBC_USER_ATTR_ATTRIBUTES_C
#define GUARD_LIBC_USER_ATTR_ATTRIBUTES_C 1

#include "../api.h"
/**/

#include "attr.attributes.h"

DECL_BEGIN

/*[[[head:libc_attr_get,hash:CRC-32=0xf7b63ba0]]]*/
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_DEPRECATED("Use getxattr(2) or lgetxattr(2) instead") int
NOTHROW_NCX(LIBCCALL libc_attr_get)(char const *path,
                                    char const *attrname,
                                    char *attrvalue,
                                    int *valuelength,
                                    int flags)
/*[[[body:libc_attr_get]]]*/
/*AUTO*/{
	(void)path;
	(void)attrname;
	(void)attrvalue;
	(void)valuelength;
	(void)flags;
	CRT_UNIMPLEMENTEDF("attr_get(path: %q, attrname: %q, attrvalue: %q, valuelength: %p, flags: %x)", path, attrname, attrvalue, valuelength, flags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_attr_get]]]*/

/*[[[head:libc_attr_getf,hash:CRC-32=0x217d172e]]]*/
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_DEPRECATED("Use fgetxattr(2) instead") int
NOTHROW_NCX(LIBCCALL libc_attr_getf)(fd_t fd,
                                     char const *attrname,
                                     char *attrvalue,
                                     int *valuelength,
                                     int flags)
/*[[[body:libc_attr_getf]]]*/
/*AUTO*/{
	(void)fd;
	(void)attrname;
	(void)attrvalue;
	(void)valuelength;
	(void)flags;
	CRT_UNIMPLEMENTEDF("attr_getf(fd: %" PRIxN(__SIZEOF_FD_T__) ", attrname: %q, attrvalue: %q, valuelength: %p, flags: %x)", fd, attrname, attrvalue, valuelength, flags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_attr_getf]]]*/

/*[[[head:libc_attr_set,hash:CRC-32=0xc9f62eee]]]*/
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_DEPRECATED("Use setxattr(2) or lsetxattr(2) instead") int
NOTHROW_NCX(LIBCCALL libc_attr_set)(char const *path,
                                    char const *attrname,
                                    char const *attrvalue,
                                    int valuelength,
                                    int flags)
/*[[[body:libc_attr_set]]]*/
/*AUTO*/{
	(void)path;
	(void)attrname;
	(void)attrvalue;
	(void)valuelength;
	(void)flags;
	CRT_UNIMPLEMENTEDF("attr_set(path: %q, attrname: %q, attrvalue: %q, valuelength: %x, flags: %x)", path, attrname, attrvalue, valuelength, flags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_attr_set]]]*/

/*[[[head:libc_attr_setf,hash:CRC-32=0x643520c0]]]*/
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_DEPRECATED("Use fsetxattr(2) instead") int
NOTHROW_NCX(LIBCCALL libc_attr_setf)(fd_t fd,
                                     char const *attrname,
                                     char const *attrvalue,
                                     int valuelength,
                                     int flags)
/*[[[body:libc_attr_setf]]]*/
/*AUTO*/{
	(void)fd;
	(void)attrname;
	(void)attrvalue;
	(void)valuelength;
	(void)flags;
	CRT_UNIMPLEMENTEDF("attr_setf(fd: %" PRIxN(__SIZEOF_FD_T__) ", attrname: %q, attrvalue: %q, valuelength: %x, flags: %x)", fd, attrname, attrvalue, valuelength, flags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_attr_setf]]]*/

/*[[[head:libc_attr_remove,hash:CRC-32=0xb59f6097]]]*/
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_DEPRECATED("Use removexattr(2) or lremovexattr(2) instead") int
NOTHROW_NCX(LIBCCALL libc_attr_remove)(char const *path,
                                       char const *attrname,
                                       int flags)
/*[[[body:libc_attr_remove]]]*/
/*AUTO*/{
	(void)path;
	(void)attrname;
	(void)flags;
	CRT_UNIMPLEMENTEDF("attr_remove(path: %q, attrname: %q, flags: %x)", path, attrname, flags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_attr_remove]]]*/

/*[[[head:libc_attr_removef,hash:CRC-32=0x5365a58d]]]*/
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_DEPRECATED("Use fremovexattr(2) instead") int
NOTHROW_NCX(LIBCCALL libc_attr_removef)(fd_t fd,
                                        char const *attrname,
                                        int flags)
/*[[[body:libc_attr_removef]]]*/
/*AUTO*/{
	(void)fd;
	(void)attrname;
	(void)flags;
	CRT_UNIMPLEMENTEDF("attr_removef(fd: %" PRIxN(__SIZEOF_FD_T__) ", attrname: %q, flags: %x)", fd, attrname, flags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_attr_removef]]]*/

/*[[[head:libc_attr_list,hash:CRC-32=0xa0c6baf5]]]*/
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_DEPRECATED("Use listxattr(2) or llistxattr(2) instead") int
NOTHROW_NCX(LIBCCALL libc_attr_list)(char const *path,
                                     char *buffer,
                                     int buffersize,
                                     int flags,
                                     struct attrlist_cursor *cursor)
/*[[[body:libc_attr_list]]]*/
/*AUTO*/{
	(void)path;
	(void)buffer;
	(void)buffersize;
	(void)flags;
	(void)cursor;
	CRT_UNIMPLEMENTEDF("attr_list(path: %q, buffer: %q, buffersize: %x, flags: %x, cursor: %p)", path, buffer, buffersize, flags, cursor); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_attr_list]]]*/

/*[[[head:libc_attr_listf,hash:CRC-32=0x1bd110b4]]]*/
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_DEPRECATED("Use flistxattr(2) instead") int
NOTHROW_NCX(LIBCCALL libc_attr_listf)(fd_t fd,
                                      char *buffer,
                                      int buffersize,
                                      int flags,
                                      struct attrlist_cursor *cursor)
/*[[[body:libc_attr_listf]]]*/
/*AUTO*/{
	(void)fd;
	(void)buffer;
	(void)buffersize;
	(void)flags;
	(void)cursor;
	CRT_UNIMPLEMENTEDF("attr_listf(fd: %" PRIxN(__SIZEOF_FD_T__) ", buffer: %q, buffersize: %x, flags: %x, cursor: %p)", fd, buffer, buffersize, flags, cursor); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_attr_listf]]]*/

/*[[[head:libc_attr_multi,hash:CRC-32=0x6c87f882]]]*/
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_DEPRECATED("Use getxattr(2), setxattr(2), removexattr(2) and listxattr(2) instead") int
NOTHROW_NCX(LIBCCALL libc_attr_multi)(char const *path,
                                      struct attr_multiop *oplist,
                                      int count,
                                      int flags)
/*[[[body:libc_attr_multi]]]*/
/*AUTO*/{
	(void)path;
	(void)oplist;
	(void)count;
	(void)flags;
	CRT_UNIMPLEMENTEDF("attr_multi(path: %q, oplist: %p, count: %x, flags: %x)", path, oplist, count, flags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_attr_multi]]]*/

/*[[[head:libc_attr_multif,hash:CRC-32=0x39035608]]]*/
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_DEPRECATED("Use getxattr(2), setxattr(2), removexattr(2) and listxattr(2) instead") int
NOTHROW_NCX(LIBCCALL libc_attr_multif)(fd_t fd,
                                       struct attr_multiop *oplist,
                                       int count,
                                       int flags)
/*[[[body:libc_attr_multif]]]*/
/*AUTO*/{
	(void)fd;
	(void)oplist;
	(void)count;
	(void)flags;
	CRT_UNIMPLEMENTEDF("attr_multif(fd: %" PRIxN(__SIZEOF_FD_T__) ", oplist: %p, count: %x, flags: %x)", fd, oplist, count, flags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_attr_multif]]]*/

/*[[[start:exports,hash:CRC-32=0xbd489e13]]]*/
DEFINE_PUBLIC_ALIAS(attr_get, libc_attr_get);
DEFINE_PUBLIC_ALIAS(attr_getf, libc_attr_getf);
DEFINE_PUBLIC_ALIAS(attr_set, libc_attr_set);
DEFINE_PUBLIC_ALIAS(attr_setf, libc_attr_setf);
DEFINE_PUBLIC_ALIAS(attr_remove, libc_attr_remove);
DEFINE_PUBLIC_ALIAS(attr_removef, libc_attr_removef);
DEFINE_PUBLIC_ALIAS(attr_list, libc_attr_list);
DEFINE_PUBLIC_ALIAS(attr_listf, libc_attr_listf);
DEFINE_PUBLIC_ALIAS(attr_multi, libc_attr_multi);
DEFINE_PUBLIC_ALIAS(attr_multif, libc_attr_multif);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ATTR_ATTRIBUTES_C */
