/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_GUID_H
#define _KOS_GUID_H 1

#include <__stdinc.h>

#include <hybrid/__byteorder.h>
#include <hybrid/__byteswap.h>

#include <bits/types.h>

#define __OFFSET_GUID_A    0
#define __OFFSET_GUID_B    4
#define __OFFSET_GUID_C    6
#define __OFFSET_GUID_D    8
#define __OFFSET_GUID_E    10
#define __SIZEOF_GUID_T__  16
#ifdef __USE_KOS_KERNEL
#define OFFSET_GUID_A    __OFFSET_GUID_A
#define OFFSET_GUID_B    __OFFSET_GUID_B
#define OFFSET_GUID_C    __OFFSET_GUID_C
#define OFFSET_GUID_D    __OFFSET_GUID_D
#define OFFSET_GUID_E    __OFFSET_GUID_E
#define SIZEOF_GUID      __SIZEOF_GUID_T__
#endif

#ifdef __CC__
__DECL_BEGIN

#ifndef __guid_t_defined
#define __guid_t_defined 1
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("g_guid")
#pragma push_macro("g_a")
#pragma push_macro("g_b")
#pragma push_macro("g_c")
#pragma push_macro("g_d")
#pragma push_macro("g_e_1")
#pragma push_macro("g_e_2")
#pragma push_macro("g_data")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef g_guid
#undef g_a
#undef g_b
#undef g_c
#undef g_d
#undef g_e_1
#undef g_e_2
#undef g_data
typedef union __ATTR_PACKED {
	__u8       g_guid[16]; /* GUID */
	struct {
		__be32 g_a;
		__be16 g_b;
		__be16 g_c;
		__be16 g_d;
		__be32 g_e_1;
		__be16 g_e_2;
	}          g_data;
} guid_t;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("g_data")
#pragma pop_macro("g_e_2")
#pragma pop_macro("g_e_1")
#pragma pop_macro("g_d")
#pragma pop_macro("g_c")
#pragma pop_macro("g_b")
#pragma pop_macro("g_a")
#pragma pop_macro("g_guid")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !__guid_t_defined */


#define GUID_A(x) __hybrid_betoh32((x).g_data.g_a)
#define GUID_B(x) __hybrid_betoh16((x).g_data.g_b)
#define GUID_C(x) __hybrid_betoh16((x).g_data.g_c)
#define GUID_D(x) __hybrid_betoh16((x).g_data.g_d)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define GUID_E(x) (((__u64)__hybrid_betoh32((x).g_data.g_e_1) << 16) | (__u64)__hybrid_betoh16((x).g_data.g_e_2))
#else
#define GUID_E(x) ((__u64)__hybrid_betoh32((x).g_data.g_e_1) | ((__u64)__hybrid_betoh16((x).g_data.g_e_2) << 32))
#endif

/* Printf helpers for GUID printing */
#define FORMAT_GUID_T         "%.8I32X-%.4I16X-%.4I16X-%.4I16X-%.12I64X"
#define FORMAT_GUID_T_ARGS(x) GUID_A(x), GUID_B(x), GUID_C(x), GUID_D(x), GUID_E(x)

/* Compare `self' against the given, constant GUID */
#define GUID_EQUALS(self, a, b, c, d, e)                                                    \
	((self).g_guid[0] == (__u8)((__UINT32_C(0x##a) & __UINT32_C(0xff000000)) >> 24) &&      \
	 (self).g_guid[1] == (__u8)((__UINT32_C(0x##a) & __UINT32_C(0x00ff0000)) >> 16) &&      \
	 (self).g_guid[2] == (__u8)((__UINT32_C(0x##a) & __UINT32_C(0x0000ff00)) >> 8) &&       \
	 (self).g_guid[3] == (__u8)((__UINT32_C(0x##a) & __UINT32_C(0x000000ff))) &&            \
	 (self).g_guid[4] == (__u8)((__UINT16_C(0x##b) & __UINT16_C(0xff00)) >> 8) &&           \
	 (self).g_guid[5] == (__u8)((__UINT16_C(0x##b) & __UINT16_C(0x00ff))) &&                \
	 (self).g_guid[6] == (__u8)((__UINT16_C(0x##c) & __UINT16_C(0xff00)) >> 8) &&           \
	 (self).g_guid[7] == (__u8)((__UINT16_C(0x##c) & __UINT16_C(0x00ff))) &&                \
	 (self).g_guid[8] == (__u8)((__UINT16_C(0x##d) & __UINT16_C(0xff00)) >> 8) &&           \
	 (self).g_guid[9] == (__u8)((__UINT16_C(0x##d) & __UINT16_C(0x00ff))) &&                \
	 (self).g_guid[10] == (__u8)((__UINT64_C(0x##e) & __UINT64_C(0xff0000000000)) >> 40) && \
	 (self).g_guid[11] == (__u8)((__UINT64_C(0x##e) & __UINT64_C(0x00ff00000000)) >> 32) && \
	 (self).g_guid[12] == (__u8)((__UINT64_C(0x##e) & __UINT64_C(0x0000ff000000)) >> 24) && \
	 (self).g_guid[13] == (__u8)((__UINT64_C(0x##e) & __UINT64_C(0x000000ff0000)) >> 16) && \
	 (self).g_guid[14] == (__u8)((__UINT64_C(0x##e) & __UINT64_C(0x00000000ff00)) >> 8) &&  \
	 (self).g_guid[15] == (__u8)((__UINT64_C(0x##e) & __UINT64_C(0x0000000000ff))))


/* Static initializer for GUIDs */
#define GUID_INIT(a, b, c, d, e)                                        \
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

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_GUID_H */
