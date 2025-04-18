/* HASH CRC-32:0xa819c723 */
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
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/byteorder.h) */
/*!always_includes <sys/isa_defs.h>*/
/*!always_includes <sys/int_types.h>*/
#ifndef _SYS_BYTEORDER_H
#define _SYS_BYTEORDER_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/byteorder.h>
#include <hybrid/__byteswap.h>
#include <hybrid/__unaligned.h>
#include <hybrid/typecore.h>

#include <sys/isa_defs.h>  /* Mandatory dependency (for OpenSolaris compat) */
#include <sys/int_types.h> /* Mandatory dependency (for OpenSolaris compat) */

#if !defined(__USE_XOPEN_EXTENDED) || defined(__USE_SOLARIS)
#define BSWAP_8(x)  ((x) & __UINT8_C(0xff))
#define BSWAP_16(x) __hybrid_bswap16(x)
#define BSWAP_32(x) __hybrid_bswap32(x)
#ifdef __hybrid_bswap64
#define	BSWAP_64(x) __hybrid_bswap64(x)
#endif /* __hybrid_bswap64 */
#define BMASK_8(x)  ((x) & __UINT8_C(0xff))
#define BMASK_16(x) ((x) & __UINT16_C(0xffff))
#define BMASK_32(x) ((x) & __UINT32_C(0xffffffff))
#define BMASK_64(x) (x)
#define BE_8(x)     ((x) & __UINT8_C(0xff))
#define LE_8(x)     ((x) & __UINT8_C(0xff))

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define BE_16(x) BMASK_16(x)
#define LE_16(x) BSWAP_16(x)
#define BE_32(x) BMASK_32(x)
#define LE_32(x) BSWAP_32(x)
#define BE_64(x) BMASK_64(x)
#define LE_64(x) BSWAP_64(x)
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define LE_16(x) BMASK_16(x)
#define BE_16(x) BSWAP_16(x)
#define LE_32(x) BMASK_32(x)
#define BE_32(x) BSWAP_32(x)
#define LE_64(x) BMASK_64(x)
#define BE_64(x) BSWAP_64(x)
#endif /* __BYTE_ORDER__ == ... */
#define BE_IN8(ptr)      (*(__UINT8_TYPE__ const *)(ptr))
#define LE_IN8(ptr)      (*(__UINT8_TYPE__ const *)(ptr))
#define BE_OUT8(ptr, v)  *(__UINT8_TYPE__ *)(ptr) = (v);
#define LE_OUT8(ptr, v)  *(__UINT8_TYPE__ *)(ptr) = (v);
#define BE_IN16(ptr)     __hybrid_unaligned_getbe16(ptr)
#define LE_IN16(ptr)     __hybrid_unaligned_getle16(ptr)
#define BE_OUT16(ptr, v) __hybrid_unaligned_setbe16(ptr, v);
#define LE_OUT16(ptr, v) __hybrid_unaligned_setle16(ptr, v);
#define BE_IN32(ptr)     __hybrid_unaligned_getbe32(ptr)
#define LE_IN32(ptr)     __hybrid_unaligned_getle32(ptr)
#define BE_OUT32(ptr, v) __hybrid_unaligned_setbe32(ptr, v);
#define LE_OUT32(ptr, v) __hybrid_unaligned_setle32(ptr, v);
#ifdef __UINT64_TYPE__
#define BE_IN64(ptr)     __hybrid_unaligned_getbe64(ptr)
#define LE_IN64(ptr)     __hybrid_unaligned_getle64(ptr)
#define BE_OUT64(ptr, v) __hybrid_unaligned_setbe64(ptr, v);
#define LE_OUT64(ptr, v) __hybrid_unaligned_setle64(ptr, v);
#endif /* __UINT64_TYPE__ */
#endif /* !__USE_XOPEN_EXTENDED || __USE_SOLARIS */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __htons_defined
#define __htons_defined
#ifdef __CRT_HAVE_htons
__CEIDECLARE(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,htons,(__UINT16_TYPE__ __hostword),{ return (__UINT16_TYPE__)__hybrid_htobe32(__hostword); })
#elif defined(__CRT_HAVE_ntohs) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,htons,(__UINT16_TYPE__ __hostword),ntohs,{ return (__UINT16_TYPE__)__hybrid_htobe32(__hostword); })
#elif defined(__CRT_HAVE___htons)
__CEIREDIRECT(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,htons,(__UINT16_TYPE__ __hostword),__htons,{ return (__UINT16_TYPE__)__hybrid_htobe32(__hostword); })
#elif defined(__CRT_HAVE___ntohs) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,htons,(__UINT16_TYPE__ __hostword),__ntohs,{ return (__UINT16_TYPE__)__hybrid_htobe32(__hostword); })
#else /* ... */
__LOCAL __ATTR_CONST __UINT16_TYPE__ __NOTHROW(__LIBCCALL htons)(__UINT16_TYPE__ __hostword) { return (__UINT16_TYPE__)__hybrid_htobe32(__hostword); }
#endif /* !... */
#endif /* !__htons_defined */
#ifndef __ntohs_defined
#define __ntohs_defined
#ifdef __CRT_HAVE_ntohs
__CEIDECLARE(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,ntohs,(__UINT16_TYPE__ __netshort),{ return (__UINT16_TYPE__)__hybrid_betoh16(__netshort); })
#elif defined(__CRT_HAVE_htons) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,ntohs,(__UINT16_TYPE__ __netshort),htons,{ return (__UINT16_TYPE__)__hybrid_betoh16(__netshort); })
#elif defined(__CRT_HAVE___ntohs)
__CEIREDIRECT(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,ntohs,(__UINT16_TYPE__ __netshort),__ntohs,{ return (__UINT16_TYPE__)__hybrid_betoh16(__netshort); })
#elif defined(__CRT_HAVE___htons) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,ntohs,(__UINT16_TYPE__ __netshort),__htons,{ return (__UINT16_TYPE__)__hybrid_betoh16(__netshort); })
#else /* ... */
__LOCAL __ATTR_CONST __UINT16_TYPE__ __NOTHROW(__LIBCCALL ntohs)(__UINT16_TYPE__ __netshort) { return (__UINT16_TYPE__)__hybrid_betoh16(__netshort); }
#endif /* !... */
#endif /* !__ntohs_defined */
#ifndef __htonl_defined
#define __htonl_defined
#ifdef __CRT_HAVE_htonl
__CEIDECLARE(__ATTR_CONST,__UINT32_TYPE__,__NOTHROW,htonl,(__UINT32_TYPE__ __hostlong),{ return (__UINT32_TYPE__)__hybrid_htobe32(__hostlong); })
#elif defined(__CRT_HAVE_ntohl) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,__UINT32_TYPE__,__NOTHROW,htonl,(__UINT32_TYPE__ __hostlong),ntohl,{ return (__UINT32_TYPE__)__hybrid_htobe32(__hostlong); })
#elif defined(__CRT_HAVE___htonl)
__CEIREDIRECT(__ATTR_CONST,__UINT32_TYPE__,__NOTHROW,htonl,(__UINT32_TYPE__ __hostlong),__htonl,{ return (__UINT32_TYPE__)__hybrid_htobe32(__hostlong); })
#elif defined(__CRT_HAVE___ntohl) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,__UINT32_TYPE__,__NOTHROW,htonl,(__UINT32_TYPE__ __hostlong),__ntohl,{ return (__UINT32_TYPE__)__hybrid_htobe32(__hostlong); })
#else /* ... */
__LOCAL __ATTR_CONST __UINT32_TYPE__ __NOTHROW(__LIBCCALL htonl)(__UINT32_TYPE__ __hostlong) { return (__UINT32_TYPE__)__hybrid_htobe32(__hostlong); }
#endif /* !... */
#endif /* !__htonl_defined */
#ifndef __ntohl_defined
#define __ntohl_defined
#ifdef __CRT_HAVE_ntohl
__CEIDECLARE(__ATTR_CONST,__UINT32_TYPE__,__NOTHROW,ntohl,(__UINT32_TYPE__ __netlong),{ return (__UINT32_TYPE__)__hybrid_betoh32(__netlong); })
#elif defined(__CRT_HAVE_htonl) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,__UINT32_TYPE__,__NOTHROW,ntohl,(__UINT32_TYPE__ __netlong),htonl,{ return (__UINT32_TYPE__)__hybrid_betoh32(__netlong); })
#elif defined(__CRT_HAVE___ntohl)
__CEIREDIRECT(__ATTR_CONST,__UINT32_TYPE__,__NOTHROW,ntohl,(__UINT32_TYPE__ __netlong),__ntohl,{ return (__UINT32_TYPE__)__hybrid_betoh32(__netlong); })
#elif defined(__CRT_HAVE___htonl) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,__UINT32_TYPE__,__NOTHROW,ntohl,(__UINT32_TYPE__ __netlong),__htonl,{ return (__UINT32_TYPE__)__hybrid_betoh32(__netlong); })
#else /* ... */
__LOCAL __ATTR_CONST __UINT32_TYPE__ __NOTHROW(__LIBCCALL ntohl)(__UINT32_TYPE__ __netlong) { return (__UINT32_TYPE__)__hybrid_betoh32(__netlong); }
#endif /* !... */
#endif /* !__ntohl_defined */
#if (!defined(__USE_XOPEN_EXTENDED) || defined(__USE_SOLARIS)) && defined(__UINT64_TYPE__)
#ifdef __CRT_HAVE_htonq
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__UINT64_TYPE__,__NOTHROW,htonll,(__UINT64_TYPE__ __hostquad),htonq,{ return (__UINT64_TYPE__)__hybrid_htobe64(__hostquad); })
#elif defined(__CRT_HAVE_ntohq) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__UINT64_TYPE__,__NOTHROW,htonll,(__UINT64_TYPE__ __hostquad),ntohq,{ return (__UINT64_TYPE__)__hybrid_htobe64(__hostquad); })
#else /* ... */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT64_TYPE__ __NOTHROW(__LIBCCALL htonll)(__UINT64_TYPE__ __hostquad) { return (__UINT64_TYPE__)__hybrid_htobe64(__hostquad); }
#endif /* !... */
#ifdef __CRT_HAVE_ntohq
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__UINT64_TYPE__,__NOTHROW,ntohll,(__UINT64_TYPE__ __netquad),ntohq,{ return (__UINT64_TYPE__)__hybrid_betoh64(__netquad); })
#elif defined(__CRT_HAVE_htonq) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__UINT64_TYPE__,__NOTHROW,ntohll,(__UINT64_TYPE__ __netquad),htonq,{ return (__UINT64_TYPE__)__hybrid_betoh64(__netquad); })
#else /* ... */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT64_TYPE__ __NOTHROW(__LIBCCALL ntohll)(__UINT64_TYPE__ __netquad) { return (__UINT64_TYPE__)__hybrid_betoh64(__netquad); }
#endif /* !... */
#endif /* (!__USE_XOPEN_EXTENDED || __USE_SOLARIS) && __UINT64_TYPE__ */
#ifdef __USE_KOS_ALTERATIONS
#define htons(x) __hybrid_htobe16(x)
#define ntohs(x) __hybrid_betoh16(x)
#define htonl(x) __hybrid_htobe32(x)
#define ntohl(x) __hybrid_betoh32(x)
#if (!defined(__USE_XOPEN_EXTENDED) || defined(__USE_SOLARIS)) && defined(__UINT64_TYPE__)
#define htonll(x) __hybrid_htobe64(x)
#define ntohll(x) __hybrid_betoh64(x)
#endif /* (!__USE_XOPEN_EXTENDED || __USE_SOLARIS) && __UINT64_TYPE__ */
#else /* __USE_KOS_ALTERATIONS */
#define htons(x) __CCAST(__uint16_t)__hybrid_htobe16(x)
#define ntohs(x) __CCAST(__uint16_t)__hybrid_betoh16(x)
#define htonl(x) __CCAST(__uint32_t)__hybrid_htobe32(x)
#define ntohl(x) __CCAST(__uint32_t)__hybrid_betoh32(x)
#if (!defined(__USE_XOPEN_EXTENDED) || defined(__USE_SOLARIS)) && defined(__UINT64_TYPE__)
#define htonll(x) __CCAST(__uint64_t)__hybrid_htobe64(x)
#define ntohll(x) __CCAST(__uint64_t)__hybrid_betoh64(x)
#endif /* (!__USE_XOPEN_EXTENDED || __USE_SOLARIS) && __UINT64_TYPE__ */
#endif /* !__USE_KOS_ALTERATIONS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_BYTEORDER_H */
