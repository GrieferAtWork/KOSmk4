/* HASH CRC-32:0x81a09e1e */
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
#ifndef __local_dn_comp_defined
#define __local_dn_comp_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ns_name_compress_defined
#define __local___localdep_ns_name_compress_defined
#ifdef __CRT_HAVE_ns_name_compress
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ns_name_compress,(char const *__srcbuf, unsigned char *__dstbuf, __SIZE_TYPE__ __dstbufsize, unsigned char const **__d, unsigned char const **__e),ns_name_compress,(__srcbuf,__dstbuf,__dstbufsize,__d,__e))
#elif defined(__CRT_HAVE_dn_comp) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ns_name_compress,(char const *__srcbuf, unsigned char *__dstbuf, __SIZE_TYPE__ __dstbufsize, unsigned char const **__d, unsigned char const **__e),dn_comp,(__srcbuf,__dstbuf,__dstbufsize,__d,__e))
#elif defined(__CRT_HAVE___dn_comp) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ns_name_compress,(char const *__srcbuf, unsigned char *__dstbuf, __SIZE_TYPE__ __dstbufsize, unsigned char const **__d, unsigned char const **__e),__dn_comp,(__srcbuf,__dstbuf,__dstbufsize,__d,__e))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/arpa.nameser/ns_name_compress.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ns_name_compress __LIBC_LOCAL_NAME(ns_name_compress)
#endif /* !... */
#endif /* !__local___localdep_ns_name_compress_defined */
__LOCAL_LIBC(dn_comp) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dn_comp))(char const *__srcbuf, unsigned char *__dstbuf, int __dstbufsize, unsigned char **__d, unsigned char **__e) {
	return (__NAMESPACE_LOCAL_SYM __localdep_ns_name_compress)(__srcbuf, __dstbuf, (__SIZE_TYPE__)__dstbufsize, (unsigned char const **)__d, (unsigned char const **)__e);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dn_comp_defined
#define __local___localdep_dn_comp_defined
#define __localdep_dn_comp __LIBC_LOCAL_NAME(dn_comp)
#endif /* !__local___localdep_dn_comp_defined */
#endif /* !__local_dn_comp_defined */
