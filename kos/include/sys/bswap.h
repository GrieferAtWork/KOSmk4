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
/* (#) Portability: NetBSD (/sys/sys/bswap.h) */
#ifndef _SYS_BSWAP_H
#define _SYS_BSWAP_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/__byteswap.h>
#include <hybrid/typecore.h>

#include <sys/stdint.h>
/*#include <machine/bswap.h>*/

#ifdef __CC__
__DECL_BEGIN

#ifdef __UINT16_TYPE__
__LOCAL __ATTR_CONST __UINT16_TYPE__
__NOTHROW(__LIBCCALL bswap16)(__UINT16_TYPE__ __x) {
	return __hybrid_bswap16(__x);
}
#endif /* __UINT16_TYPE__ */

#ifdef __UINT32_TYPE__
__LOCAL __ATTR_CONST __UINT32_TYPE__
__NOTHROW(__LIBCCALL bswap32)(__UINT32_TYPE__ __x) {
	return __hybrid_bswap32(__x);
}
#endif /* __UINT32_TYPE__ */

#ifdef __UINT64_TYPE__
__LOCAL __ATTR_CONST __UINT64_TYPE__
__NOTHROW(__LIBCCALL bswap64)(__UINT64_TYPE__ __x) {
	return __hybrid_bswap64(__x);
}
#endif /* __UINT64_TYPE__ */

__DECL_END
#endif /* __CC__ */

#define __byte_swap_u16_constant(x) __hybrid_bswap16_c(x)
#define __byte_swap_u32_constant(x) __hybrid_bswap32_c(x)
#define __byte_swap_u64_constant(x) __hybrid_bswap64_c(x)
#ifndef bswap16
#define bswap16(x) __hybrid_bswap16(x)
#endif /* !bswap16 */
#ifndef bswap32
#define bswap32(x) __hybrid_bswap32(x)
#endif /* !bswap32 */
#ifndef bswap64
#define bswap64(x) __hybrid_bswap64(x)
#endif /* !bswap64 */

#endif /* !_SYS_BSWAP_H */
