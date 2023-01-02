/* HASH CRC-32:0xd622573c */
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
#ifndef __local_atomic_xchq_nopf_defined
#define __local_atomic_xchq_nopf_defined
#include <__crt.h>
#include <kos/bits/nopf.h>
#if (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchq_nopf) || defined(__CRT_HAVE_atomic_cmpxchq_nopf))
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_atomic_cmpxchq_nopf_defined
#define __local___localdep_atomic_cmpxchq_nopf_defined
#ifdef __arch_atomic_cmpxchq_nopf
__FORCELOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(4) __BOOL __NOTHROW(__LIBCCALL __localdep_atomic_cmpxchq_nopf)(void *__addr, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval, __UINT64_TYPE__ *__preal_oldval) { return __arch_atomic_cmpxchq_nopf(__addr, __oldval, __newval, __preal_oldval); }
#elif defined(__CRT_HAVE_atomic_cmpxchq_nopf)
__CREDIRECT(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(4),__BOOL,__NOTHROW,__localdep_atomic_cmpxchq_nopf,(void *__addr, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval, __UINT64_TYPE__ *__preal_oldval),atomic_cmpxchq_nopf,(__addr,__oldval,__newval,__preal_oldval))
#else /* ... */
#undef __local___localdep_atomic_cmpxchq_nopf_defined
#endif /* !... */
#endif /* !__local___localdep_atomic_cmpxchq_nopf_defined */
#ifndef __local___localdep_readq_nopf_defined
#define __local___localdep_readq_nopf_defined
#ifdef __arch_readq_nopf
__FORCELOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2) __BOOL __NOTHROW(__LIBCCALL __localdep_readq_nopf)(void const *__addr, __UINT64_TYPE__ *__presult) { return __arch_readq_nopf(__addr, __presult); }
#elif defined(__CRT_HAVE_readq_nopf)
__CREDIRECT(__ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2),__BOOL,__NOTHROW,__localdep_readq_nopf,(void const *__addr, __UINT64_TYPE__ *__presult),readq_nopf,(__addr,__presult))
#elif defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.nopf/readq_nopf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_readq_nopf __LIBC_LOCAL_NAME(readq_nopf)
#else /* ... */
#undef __local___localdep_readq_nopf_defined
#endif /* !... */
#endif /* !__local___localdep_readq_nopf_defined */
__LOCAL_LIBC(atomic_xchq_nopf) __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3) __BOOL
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(atomic_xchq_nopf))(void *__addr, __UINT64_TYPE__ __newval, __UINT64_TYPE__ *__poldval) {
	__BOOL __nopf;
	__UINT64_TYPE__  __expected_oldval;
	do {
		__nopf = __likely((__NAMESPACE_LOCAL_SYM __localdep_readq_nopf)(__addr, &__expected_oldval)) &&
		       __likely((__NAMESPACE_LOCAL_SYM __localdep_atomic_cmpxchq_nopf)(__addr, __expected_oldval, __newval, __poldval));
	} while (__likely(__nopf) && __unlikely(*__poldval != __expected_oldval));
	return __nopf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_atomic_xchq_nopf_defined
#define __local___localdep_atomic_xchq_nopf_defined
#define __localdep_atomic_xchq_nopf __LIBC_LOCAL_NAME(atomic_xchq_nopf)
#endif /* !__local___localdep_atomic_xchq_nopf_defined */
#else /* (__arch_readb_nopf || __CRT_HAVE_readb_nopf || __arch_readw_nopf || __CRT_HAVE_readw_nopf || __arch_readl_nopf || __CRT_HAVE_readl_nopf || __arch_readq_nopf || __CRT_HAVE_readq_nopf || __arch_memcpy_nopf || __CRT_HAVE_memcpy_nopf) && (__arch_atomic_cmpxchq_nopf || __CRT_HAVE_atomic_cmpxchq_nopf) */
#undef __local_atomic_xchq_nopf_defined
#endif /* (!__arch_readb_nopf && !__CRT_HAVE_readb_nopf && !__arch_readw_nopf && !__CRT_HAVE_readw_nopf && !__arch_readl_nopf && !__CRT_HAVE_readl_nopf && !__arch_readq_nopf && !__CRT_HAVE_readq_nopf && !__arch_memcpy_nopf && !__CRT_HAVE_memcpy_nopf) || (!__arch_atomic_cmpxchq_nopf && !__CRT_HAVE_atomic_cmpxchq_nopf) */
#endif /* !__local_atomic_xchq_nopf_defined */
