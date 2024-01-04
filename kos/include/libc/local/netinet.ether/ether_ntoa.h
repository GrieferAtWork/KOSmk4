/* HASH CRC-32:0x9a28c97a */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ether_ntoa_defined
#define __local_ether_ntoa_defined
#include <__crt.h>
struct ether_addr;
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ether_ntoa_r_defined
#define __local___localdep_ether_ntoa_r_defined
#ifdef __CRT_HAVE_ether_ntoa_r
__CREDIRECT(__ATTR_RETNONNULL __ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,__localdep_ether_ntoa_r,(struct ether_addr const *__restrict __addr, char *__restrict __buf),ether_ntoa_r,(__addr,__buf))
#else /* __CRT_HAVE_ether_ntoa_r */
__NAMESPACE_LOCAL_END
#include <libc/local/netinet.ether/ether_ntoa_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ether_ntoa_r __LIBC_LOCAL_NAME(ether_ntoa_r)
#endif /* !__CRT_HAVE_ether_ntoa_r */
#endif /* !__local___localdep_ether_ntoa_r_defined */
#ifndef __local___localdep_xmalloc_defined
#define __local___localdep_xmalloc_defined
#ifdef __CRT_HAVE_xmalloc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_xmalloc,(__SIZE_TYPE__ __num_bytes),xmalloc,(__num_bytes))
#elif defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/xmalloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_xmalloc __LIBC_LOCAL_NAME(xmalloc)
#else /* ... */
#undef __local___localdep_xmalloc_defined
#endif /* !... */
#endif /* !__local___localdep_xmalloc_defined */
__NAMESPACE_LOCAL_END
#include <net/ethernet.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ether_ntoa) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ether_ntoa))(struct ether_addr const *__restrict __addr) {






	static char __ether_ntoa_buf[21] = {0};
	return (__NAMESPACE_LOCAL_SYM __localdep_ether_ntoa_r)(__addr, __ether_ntoa_buf);

}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ether_ntoa_defined
#define __local___localdep_ether_ntoa_defined
#define __localdep_ether_ntoa __LIBC_LOCAL_NAME(ether_ntoa)
#endif /* !__local___localdep_ether_ntoa_defined */
#endif /* !__local_ether_ntoa_defined */
