/* HASH CRC-32:0x1cc8716a */
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
#ifndef __local_physmem_total_defined
#define __local_physmem_total_defined
#include <__crt.h>
#include <asm/crt/confname.h>
#include <asm/pagesize.h>
#if (defined(__CRT_HAVE_getpagesize) || defined(__CRT_HAVE___getpagesize) || defined(__ARCH_PAGESIZE)) && (defined(__CRT_HAVE_sysconf) || defined(__CRT_HAVE___sysconf)) && defined(_SC_PHYS_PAGES)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getpagesize_defined
#define __local___localdep_getpagesize_defined
#if defined(__CRT_HAVE_getpagesize) && defined(__ARCH_PAGESIZE)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,__localdep_getpagesize,(void),getpagesize,{ return __ARCH_PAGESIZE; })
#elif defined(__CRT_HAVE_getpagesize)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,__localdep_getpagesize,(void),getpagesize,())
#elif defined(__CRT_HAVE___getpagesize)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,__localdep_getpagesize,(void),__getpagesize,())
#elif defined(__ARCH_PAGESIZE)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL __localdep_getpagesize)(void) { return __ARCH_PAGESIZE; }
#else /* ... */
#undef __local___localdep_getpagesize_defined
#endif /* !... */
#endif /* !__local___localdep_getpagesize_defined */
#ifndef __local___localdep_sysconf_defined
#define __local___localdep_sysconf_defined
#ifdef __CRT_HAVE_sysconf
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,__localdep_sysconf,(__STDC_INT_AS_UINT_T __name),sysconf,(__name))
#elif defined(__CRT_HAVE___sysconf)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,__localdep_sysconf,(__STDC_INT_AS_UINT_T __name),__sysconf,(__name))
#else /* ... */
#undef __local___localdep_sysconf_defined
#endif /* !... */
#endif /* !__local___localdep_sysconf_defined */
__LOCAL_LIBC(physmem_total) __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(physmem_total))(void) {
	__SIZE_TYPE__ __pages    = (__NAMESPACE_LOCAL_SYM __localdep_sysconf)(_SC_PHYS_PAGES);
	__SIZE_TYPE__ __pagesize = (__NAMESPACE_LOCAL_SYM __localdep_getpagesize)();
	return (double)__pages * (double)__pagesize;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_physmem_total_defined
#define __local___localdep_physmem_total_defined
#define __localdep_physmem_total __LIBC_LOCAL_NAME(physmem_total)
#endif /* !__local___localdep_physmem_total_defined */
#else /* (__CRT_HAVE_getpagesize || __CRT_HAVE___getpagesize || __ARCH_PAGESIZE) && (__CRT_HAVE_sysconf || __CRT_HAVE___sysconf) && _SC_PHYS_PAGES */
#undef __local_physmem_total_defined
#endif /* (!__CRT_HAVE_getpagesize && !__CRT_HAVE___getpagesize && !__ARCH_PAGESIZE) || (!__CRT_HAVE_sysconf && !__CRT_HAVE___sysconf) || !_SC_PHYS_PAGES */
#endif /* !__local_physmem_total_defined */
