/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID___DEBUG_ALIGNMENT_H
#define __GUARD_HYBRID___DEBUG_ALIGNMENT_H 1

#include "../__stdinc.h"
#include "host.h"


#if defined(NDEBUG_DATA_ALIGNMENT) || defined(NDEBUG)
/* ... */
#elif defined(__PE__) && !defined(_MSC_VER)
/* debug-data-alignment runs into problems in dynamically linked DLLs,
 * because GCC tends to leave the PLT unaligned, meaning that any access
 * to an imported symbol could lead to an error being thrown wrongly! */
#elif defined(__x86_64__)
#ifdef _MSC_VER
__NAMESPACE_INT_BEGIN
__SYSDECL_BEGIN
unsigned __int64 __readeflags(void);
void __writeeflags(unsigned __int64);
#pragma intrinsic(__readeflags)
#pragma intrinsic(__writeeflags)
__SYSDECL_END
__NAMESPACE_INT_END
#define __hybrid_dbg_alignment_enable()  (__NAMESPACE_INT_SYM __writeeflags(__NAMESPACE_INT_SYM __readeflags() | 0x40000))
#define __hybrid_dbg_alignment_disable() (__NAMESPACE_INT_SYM __writeeflags(__NAMESPACE_INT_SYM __readeflags() & ~0x40000))
#elif defined(__COMPILER_HAVE_GCC_ASM)
#define __hybrid_dbg_alignment_enable  __NAMESPACE_INT_SYM __impl_hybrid_dbg_alignment_enable
#define __hybrid_dbg_alignment_disable __NAMESPACE_INT_SYM __impl_hybrid_dbg_alignment_disable
__NAMESPACE_INT_BEGIN
__SYSDECL_BEGIN
__LOCAL void __impl_hybrid_dbg_alignment_enable(void) {
	__asm__("pushf{q}\n\t"
	        "or{q $0x40000, 0(%%rsp)| QWORD PTR [RSP], 0x40000}\n\t"
	        "popf{q}" : );
}
__LOCAL void __impl_hybrid_dbg_alignment_disable(void) {
	__asm__("pushf{q}\n\t"
	        "and{q $~0x40000, 0(%%rsp)| QWORD PTR [RSP], ~0x40000}\n\t"
	        "popf{q}" : );
}
__SYSDECL_END
__NAMESPACE_INT_END
#endif
#endif /* ... */

#ifndef __hybrid_dbg_alignment_enable
#define __NO_hybrid_dbg_alignment 1
#define __hybrid_dbg_alignment_enable()  (void)0
#define __hybrid_dbg_alignment_disable() (void)0
#endif /* !__hybrid_dbg_alignment_enable */


#if !defined(__NO_hybrid_dbg_alignment) && \
    !defined(__KOS_SYSTEM_HEADERS__)
#include "typecore.h"
/* C's string functions aren't alignment-safe, so we override them here! */
#include <string.h>
#ifdef _MSC_VER
#include <wchar.h>
#endif
__NAMESPACE_INT_BEGIN
__SYSDECL_BEGIN
__LOCAL void *
(__impl_dbg_alignment_memcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __num_bytes) {
	void *__res;
	__hybrid_dbg_alignment_disable();
	__res = memcpy(__dst,__src,__num_bytes);
	__hybrid_dbg_alignment_enable();
	return __res;
}
__LOCAL void *
(__impl_dbg_alignment_memmove)(void *__dst, void const *__src, __SIZE_TYPE__ __num_bytes) {
	void *__res;
	__hybrid_dbg_alignment_disable();
	__res = memmove(__dst,__src,__num_bytes);
	__hybrid_dbg_alignment_enable();
	return __res;
}
__LOCAL void *
(__impl_dbg_alignment_memset)(void *__restrict __dst, int __val, __SIZE_TYPE__ __num_bytes) {
	void *__res;
	__hybrid_dbg_alignment_disable();
	__res = memset(__dst,__val,__num_bytes);
	__hybrid_dbg_alignment_enable();
	return __res;
}
__LOCAL int
(__impl_dbg_alignment_memcmp)(void const *__restrict __a,
                              void const *__restrict __b,
                              __SIZE_TYPE__ __num_bytes) {
	int __res;
	__hybrid_dbg_alignment_disable();
	__res = memcmp(__a,__b,__num_bytes);
	__hybrid_dbg_alignment_enable();
	return __res;
}
__SYSDECL_END
__NAMESPACE_INT_END
#undef memcpy
#undef memmove
#undef memset
#undef memcmp
#define memcpy   __NAMESPACE_INT_SYM __impl_dbg_alignment_memcpy
#define memmove  __NAMESPACE_INT_SYM __impl_dbg_alignment_memmove
#define memset   __NAMESPACE_INT_SYM __impl_dbg_alignment_memset
#define memcmp   __NAMESPACE_INT_SYM __impl_dbg_alignment_memcmp
#endif /* C-api fixes */



#endif /* !__GUARD_HYBRID_XCH_H */
