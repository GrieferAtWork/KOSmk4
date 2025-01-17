/* HASH CRC-32:0x9b77366d */
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
#ifndef __local_readb_nopf_defined
#define __local_readb_nopf_defined
#include <__crt.h>
#include <kos/bits/nopf.h>
#if defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf)
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_memcpy_nopf_defined
#define __local___localdep_crt_memcpy_nopf_defined
#ifdef __arch_memcpy_nopf
__FORCELOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __SIZE_TYPE__ __NOTHROW(__LIBCCALL __localdep_crt_memcpy_nopf)(void *__dst, void const *__src, __SIZE_TYPE__ __num_bytes) { return __arch_memcpy_nopf(__dst, __src, __num_bytes); }
#elif defined(__CRT_HAVE_memcpy_nopf)
__CREDIRECT(__ATTR_WUNUSED __NOBLOCK __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW,__localdep_crt_memcpy_nopf,(void *__dst, void const *__src, __SIZE_TYPE__ __num_bytes),memcpy_nopf,(__dst,__src,__num_bytes))
#else /* ... */
#undef __local___localdep_crt_memcpy_nopf_defined
#endif /* !... */
#endif /* !__local___localdep_crt_memcpy_nopf_defined */
#ifndef __local___localdep_crt_readl_nopf_defined
#define __local___localdep_crt_readl_nopf_defined
#ifdef __arch_readl_nopf
__FORCELOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2) __BOOL __NOTHROW(__LIBCCALL __localdep_crt_readl_nopf)(void const *__addr, __UINT32_TYPE__ *__presult) { return __arch_readl_nopf(__addr, __presult); }
#elif defined(__CRT_HAVE_readl_nopf)
__CREDIRECT(__ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2),__BOOL,__NOTHROW,__localdep_crt_readl_nopf,(void const *__addr, __UINT32_TYPE__ *__presult),readl_nopf,(__addr,__presult))
#else /* ... */
#undef __local___localdep_crt_readl_nopf_defined
#endif /* !... */
#endif /* !__local___localdep_crt_readl_nopf_defined */
#ifndef __local___localdep_crt_readw_nopf_defined
#define __local___localdep_crt_readw_nopf_defined
#ifdef __arch_readw_nopf
__FORCELOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2) __BOOL __NOTHROW(__LIBCCALL __localdep_crt_readw_nopf)(void const *__addr, __UINT16_TYPE__ *__presult) { return __arch_readw_nopf(__addr, __presult); }
#elif defined(__CRT_HAVE_readw_nopf)
__CREDIRECT(__ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2),__BOOL,__NOTHROW,__localdep_crt_readw_nopf,(void const *__addr, __UINT16_TYPE__ *__presult),readw_nopf,(__addr,__presult))
#else /* ... */
#undef __local___localdep_crt_readw_nopf_defined
#endif /* !... */
#endif /* !__local___localdep_crt_readw_nopf_defined */
__LOCAL_LIBC(readb_nopf) __ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2) __BOOL
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(readb_nopf))(void const *__addr, __UINT8_TYPE__ *__presult) {
#if defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)
	return __likely((__NAMESPACE_LOCAL_SYM __localdep_crt_memcpy_nopf)(__presult, __addr, 1) == 0);
#elif defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf)
	__BOOL __ok;
	union { __UINT16_TYPE__ __w; __UINT8_TYPE__ __b[2]; } __result;
	__ok = (__NAMESPACE_LOCAL_SYM __localdep_crt_readw_nopf)((void const *)((__UINTPTR_TYPE__)__addr & ~1), &__result.__w);
	*__presult = __result.__b[(__UINTPTR_TYPE__)__addr & 1];
	return __ok;
#elif defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf)
	__BOOL __ok;
	union { __UINT32_TYPE__ __l; __UINT8_TYPE__ __b[4]; } __result;
	__ok = (__NAMESPACE_LOCAL_SYM __localdep_crt_readl_nopf)((void const *)((__UINTPTR_TYPE__)__addr & ~3), &__result.__l);
	*__presult = __result.__b[(__UINTPTR_TYPE__)__addr & 3];
	return __ok;
#else /* ... */
	__BOOL __ok;
	union { __UINT64_TYPE__ __q; __UINT8_TYPE__ __b[2]; } __result;
	__ok = (__NAMESPACE_LOCAL_SYM __localdep_crt_readw_nopf)((void const *)((__UINTPTR_TYPE__)__addr & ~7), &__result.__q);
	*__presult = __result.__b[(__UINTPTR_TYPE__)__addr & 7];
	return __ok;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_readb_nopf_defined
#define __local___localdep_readb_nopf_defined
#define __localdep_readb_nopf __LIBC_LOCAL_NAME(readb_nopf)
#endif /* !__local___localdep_readb_nopf_defined */
#else /* __arch_memcpy_nopf || __CRT_HAVE_memcpy_nopf || __arch_readw_nopf || __CRT_HAVE_readw_nopf || __arch_readl_nopf || __CRT_HAVE_readl_nopf || __arch_readq_nopf || __CRT_HAVE_readq_nopf */
#undef __local_readb_nopf_defined
#endif /* !__arch_memcpy_nopf && !__CRT_HAVE_memcpy_nopf && !__arch_readw_nopf && !__CRT_HAVE_readw_nopf && !__arch_readl_nopf && !__CRT_HAVE_readl_nopf && !__arch_readq_nopf && !__CRT_HAVE_readq_nopf */
#endif /* !__local_readb_nopf_defined */
