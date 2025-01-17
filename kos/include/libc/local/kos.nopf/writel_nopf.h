/* HASH CRC-32:0xa8befdc5 */
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
#ifndef __local_writel_nopf_defined
#define __local_writel_nopf_defined
#include <__crt.h>
#include <kos/bits/nopf.h>
#if (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_writew_nopf) || defined(__CRT_HAVE_writew_nopf) || defined(__arch_writeb_nopf) || defined(__CRT_HAVE_writeb_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf))
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_readw_nopf_defined
#define __local___localdep_readw_nopf_defined
#ifdef __arch_readw_nopf
__FORCELOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2) __BOOL __NOTHROW(__LIBCCALL __localdep_readw_nopf)(void const *__addr, __UINT16_TYPE__ *__presult) { return __arch_readw_nopf(__addr, __presult); }
#elif defined(__CRT_HAVE_readw_nopf)
__CREDIRECT(__ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2),__BOOL,__NOTHROW,__localdep_readw_nopf,(void const *__addr, __UINT16_TYPE__ *__presult),readw_nopf,(__addr,__presult))
#elif defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.nopf/readw_nopf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_readw_nopf __LIBC_LOCAL_NAME(readw_nopf)
#else /* ... */
#undef __local___localdep_readw_nopf_defined
#endif /* !... */
#endif /* !__local___localdep_readw_nopf_defined */
#ifndef __local___localdep_writew_nopf_defined
#define __local___localdep_writew_nopf_defined
#ifdef __arch_writew_nopf
__FORCELOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL __localdep_writew_nopf)(void *__addr, __UINT16_TYPE__ __val) { return __arch_writew_nopf(__addr, __val); }
#elif defined(__CRT_HAVE_writew_nopf)
__CREDIRECT(__ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1),__BOOL,__NOTHROW,__localdep_writew_nopf,(void *__addr, __UINT16_TYPE__ __val),writew_nopf,(__addr,__val))
#elif defined(__arch_writeb_nopf) || defined(__CRT_HAVE_writeb_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.nopf/writew_nopf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_writew_nopf __LIBC_LOCAL_NAME(writew_nopf)
#else /* ... */
#undef __local___localdep_writew_nopf_defined
#endif /* !... */
#endif /* !__local___localdep_writew_nopf_defined */
__LOCAL_LIBC(writel_nopf) __ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1) __BOOL
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(writel_nopf))(void *__addr, __UINT32_TYPE__ __val) {
	union { __UINT32_TYPE__ __l; __UINT16_TYPE__ __w[2]; } __uval;
	__UINT16_TYPE__ __old_addr0;
	__uval.__l = __val;
	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_readw_nopf)(__addr, &__old_addr0))
		return 0;
	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_writew_nopf)(__addr, __uval.__w[0]))
		return 0;
	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_writew_nopf)((__UINT16_TYPE__ *)__addr + 1, __uval.__w[1])) {
		__COMPILER_UNUSED((__NAMESPACE_LOCAL_SYM __localdep_writew_nopf)(__addr, __old_addr0));
		return 0;
	}
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_writel_nopf_defined
#define __local___localdep_writel_nopf_defined
#define __localdep_writel_nopf __LIBC_LOCAL_NAME(writel_nopf)
#endif /* !__local___localdep_writel_nopf_defined */
#else /* (__arch_readb_nopf || __CRT_HAVE_readb_nopf || __arch_readw_nopf || __CRT_HAVE_readw_nopf || __arch_readl_nopf || __CRT_HAVE_readl_nopf || __arch_readq_nopf || __CRT_HAVE_readq_nopf || __arch_memcpy_nopf || __CRT_HAVE_memcpy_nopf) && (__arch_writew_nopf || __CRT_HAVE_writew_nopf || __arch_writeb_nopf || __CRT_HAVE_writeb_nopf || __arch_memcpy_nopf || __CRT_HAVE_memcpy_nopf) */
#undef __local_writel_nopf_defined
#endif /* (!__arch_readb_nopf && !__CRT_HAVE_readb_nopf && !__arch_readw_nopf && !__CRT_HAVE_readw_nopf && !__arch_readl_nopf && !__CRT_HAVE_readl_nopf && !__arch_readq_nopf && !__CRT_HAVE_readq_nopf && !__arch_memcpy_nopf && !__CRT_HAVE_memcpy_nopf) || (!__arch_writew_nopf && !__CRT_HAVE_writew_nopf && !__arch_writeb_nopf && !__CRT_HAVE_writeb_nopf && !__arch_memcpy_nopf && !__CRT_HAVE_memcpy_nopf) */
#endif /* !__local_writel_nopf_defined */
