/* HASH CRC-32:0x1720ebaa */
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
#ifndef _KOS_UUID_H
#define _KOS_UUID_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/__byteswap.h>
#include <hybrid/byteorder.h>

#include <bits/crt/inttypes.h>
#include <kos/bits/uuid.h>

#ifdef __USE_KOS_KERNEL
#define OFFSET_UUID_A __OFFSET_UUID_A
#define OFFSET_UUID_B __OFFSET_UUID_B
#define OFFSET_UUID_C __OFFSET_UUID_C
#define OFFSET_UUID_D __OFFSET_UUID_D
#define OFFSET_UUID_E __OFFSET_UUID_E
#define SIZEOF_UUID   __SIZEOF_UUID
#endif /* __USE_KOS_KERNEL */

#ifdef __CC__
__SYSDECL_BEGIN

/* Example: "054b1def-b2ae-4d99-a99c-54b9730c3dc3" */
typedef __uuid_t uuid_t;

#define UUID_A(x) __hybrid_betoh32((x).g_data.g_a)
#define UUID_B(x) __hybrid_betoh16((x).g_data.g_b)
#define UUID_C(x) __hybrid_betoh16((x).g_data.g_c)
#define UUID_D(x) __hybrid_betoh16((x).g_data.g_d)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define UUID_E(x) (((__u64)__hybrid_betoh32((x).g_data.g_e_1) << 16) | (__u64)__hybrid_betoh16((x).g_data.g_e_2))
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define UUID_E(x) ((__u64)__hybrid_betoh32((x).g_data.g_e_1) | ((__u64)__hybrid_betoh16((x).g_data.g_e_2) << 32))
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */

/* Length of the string representation of a UUID */
#define UUID_STRLEN __UUID_STRLEN /* 36 */

/* Printf helpers for UUID printing */
#define FORMAT_UUID_T         "%" __PRINP_4 "-%" __PRINP_2 "-%" __PRINP_2 "-%" __PRINP_2 "-%.12" __PRI8_PREFIX "X"
#define FORMAT_UUID_T_ARGS(x) UUID_A(x), UUID_B(x), UUID_C(x), UUID_D(x), UUID_E(x)

/* Compare `self' against the given, constant UUID */
#define UUID_EQUALS(self, a, b, c, d, e)                                                    \
	((self).g_uuid[0] == (__u8)((__UINT32_C(0x##a) & __UINT32_C(0xff000000)) >> 24) &&      \
	 (self).g_uuid[1] == (__u8)((__UINT32_C(0x##a) & __UINT32_C(0x00ff0000)) >> 16) &&      \
	 (self).g_uuid[2] == (__u8)((__UINT32_C(0x##a) & __UINT32_C(0x0000ff00)) >> 8) &&       \
	 (self).g_uuid[3] == (__u8)((__UINT32_C(0x##a) & __UINT32_C(0x000000ff))) &&            \
	 (self).g_uuid[4] == (__u8)((__UINT16_C(0x##b) & __UINT16_C(0xff00)) >> 8) &&           \
	 (self).g_uuid[5] == (__u8)((__UINT16_C(0x##b) & __UINT16_C(0x00ff))) &&                \
	 (self).g_uuid[6] == (__u8)((__UINT16_C(0x##c) & __UINT16_C(0xff00)) >> 8) &&           \
	 (self).g_uuid[7] == (__u8)((__UINT16_C(0x##c) & __UINT16_C(0x00ff))) &&                \
	 (self).g_uuid[8] == (__u8)((__UINT16_C(0x##d) & __UINT16_C(0xff00)) >> 8) &&           \
	 (self).g_uuid[9] == (__u8)((__UINT16_C(0x##d) & __UINT16_C(0x00ff))) &&                \
	 (self).g_uuid[10] == (__u8)((__UINT64_C(0x##e) & __UINT64_C(0xff0000000000)) >> 40) && \
	 (self).g_uuid[11] == (__u8)((__UINT64_C(0x##e) & __UINT64_C(0x00ff00000000)) >> 32) && \
	 (self).g_uuid[12] == (__u8)((__UINT64_C(0x##e) & __UINT64_C(0x0000ff000000)) >> 24) && \
	 (self).g_uuid[13] == (__u8)((__UINT64_C(0x##e) & __UINT64_C(0x000000ff0000)) >> 16) && \
	 (self).g_uuid[14] == (__u8)((__UINT64_C(0x##e) & __UINT64_C(0x00000000ff00)) >> 8) &&  \
	 (self).g_uuid[15] == (__u8)((__UINT64_C(0x##e) & __UINT64_C(0x0000000000ff))))

/* Static initializer for UUIDs */
#define UUID_INIT(a, b, c, d, e)                                        \
	{{                                                                  \
		(__u8)((__UINT32_C(0x##a) & __UINT32_C(0xff000000)) >> 24),     \
		(__u8)((__UINT32_C(0x##a) & __UINT32_C(0x00ff0000)) >> 16),     \
		(__u8)((__UINT32_C(0x##a) & __UINT32_C(0x0000ff00)) >> 8),      \
		(__u8)((__UINT32_C(0x##a) & __UINT32_C(0x000000ff))),           \
		(__u8)((__UINT16_C(0x##b) & __UINT16_C(0xff00)) >> 8),          \
		(__u8)((__UINT16_C(0x##b) & __UINT16_C(0x00ff))),               \
		(__u8)((__UINT16_C(0x##c) & __UINT16_C(0xff00)) >> 8),          \
		(__u8)((__UINT16_C(0x##c) & __UINT16_C(0x00ff))),               \
		(__u8)((__UINT16_C(0x##d) & __UINT16_C(0xff00)) >> 8),          \
		(__u8)((__UINT16_C(0x##d) & __UINT16_C(0x00ff))),               \
		(__u8)((__UINT64_C(0x##e) & __UINT64_C(0xff0000000000)) >> 40), \
		(__u8)((__UINT64_C(0x##e) & __UINT64_C(0x00ff00000000)) >> 32), \
		(__u8)((__UINT64_C(0x##e) & __UINT64_C(0x0000ff000000)) >> 24), \
		(__u8)((__UINT64_C(0x##e) & __UINT64_C(0x000000ff0000)) >> 16), \
		(__u8)((__UINT64_C(0x##e) & __UINT64_C(0x00000000ff00)) >> 8),  \
		(__u8)((__UINT64_C(0x##e) & __UINT64_C(0x0000000000ff)))        \
	}}

#ifdef __CRT_HAVE_uuid_fromstr
/* >> uuid_fromstr(3)
 * Convert a given `string' into a UUID
 * >> uuid_t g;
 * >> uuid_fromstr("054b1def-b2ae-4d99-a99c-54b9730c3dc3", &g);
 * @return: string + UUID_STRLEN: Success
 * @return: NULL:                 `string' isn't a valid UUID. */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),char const *,__NOTHROW_NCX,uuid_fromstr,(char const __string[__UUID_STRLEN], uuid_t *__restrict __result),(__string,__result))
#else /* __CRT_HAVE_uuid_fromstr */
#include <libc/local/kos.uuid/uuid_fromstr.h>
/* >> uuid_fromstr(3)
 * Convert a given `string' into a UUID
 * >> uuid_t g;
 * >> uuid_fromstr("054b1def-b2ae-4d99-a99c-54b9730c3dc3", &g);
 * @return: string + UUID_STRLEN: Success
 * @return: NULL:                 `string' isn't a valid UUID. */
__NAMESPACE_LOCAL_USING_OR_IMPL(uuid_fromstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) char const *__NOTHROW_NCX(__LIBCCALL uuid_fromstr)(char const __string[__UUID_STRLEN], uuid_t *__restrict __result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(uuid_fromstr))(__string, __result); })
#endif /* !__CRT_HAVE_uuid_fromstr */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_UUID_H */
