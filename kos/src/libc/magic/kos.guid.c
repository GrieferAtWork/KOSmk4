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
%[default:section(".text.crt{|.dos}.sched.rpc")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/__byteswap.h>
)]%[insert:prefix(
#include <hybrid/byteorder.h>
)]%{

}%[insert:prefix(
#include <bits/crt/inttypes.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#define __OFFSET_GUID_A 0
#define __OFFSET_GUID_B 4
#define __OFFSET_GUID_C 6
#define __OFFSET_GUID_D 8
#define __OFFSET_GUID_E 10
#define __SIZEOF_GUID   16
#ifdef __USE_KOS_KERNEL
#define OFFSET_GUID_A __OFFSET_GUID_A
#define OFFSET_GUID_B __OFFSET_GUID_B
#define OFFSET_GUID_C __OFFSET_GUID_C
#define OFFSET_GUID_D __OFFSET_GUID_D
#define OFFSET_GUID_E __OFFSET_GUID_E
#define SIZEOF_GUID   __SIZEOF_GUID
#endif /* __USE_KOS_KERNEL */

#ifdef __CC__
__SYSDECL_BEGIN

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

/* Example: "054b1def-b2ae-4d99-a99c-54b9730c3dc3" */
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


#define GUID_A(x) __hybrid_betoh32((x).g_data.g_a)
#define GUID_B(x) __hybrid_betoh16((x).g_data.g_b)
#define GUID_C(x) __hybrid_betoh16((x).g_data.g_c)
#define GUID_D(x) __hybrid_betoh16((x).g_data.g_d)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define GUID_E(x) (((__u64)__hybrid_betoh32((x).g_data.g_e_1) << 16) | (__u64)__hybrid_betoh16((x).g_data.g_e_2))
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define GUID_E(x) ((__u64)__hybrid_betoh32((x).g_data.g_e_1) | ((__u64)__hybrid_betoh16((x).g_data.g_e_2) << 32))
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */

/* Length of the string representation of a GUID */
#define GUID_STRLEN 36

/* Printf helpers for GUID printing */
#define FORMAT_GUID_T         "%" __PRINP_4 "-%" __PRINP_2 "-%" __PRINP_2 "-%" __PRINP_2 "-%.12" __PRI8_PREFIX "X"
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

}

%[define_replacement(guid_t = guid_t)]


@@>> guid_fromstr(3)
@@Convert a given `string' into a GUID
@@>> guid_t g;
@@>> guid_fromstr("054b1def-b2ae-4d99-a99c-54b9730c3dc3", &g);
@@@return: string + GUID_STRLEN: Success
@@@return: NULL:                 `string' isn't a valid GUID.
[[kernel, impl_include("<libc/template/hex.h>")]]
char const *guid_fromstr([[nonnull]] char const string[@GUID_STRLEN@],
                         [[nonnull]] guid_t *__restrict result) {
	unsigned int i;
	for (i = 0; i < 16; ++i) {
		byte_t nibbles[2];
		unsigned int j;

		/* [05][4b][1d][ef]-[b2][ae]-[4d][99]-[a9][9c]-[54][b9][73][0c][3d][c3]
		 *  0   1   2   3    4   5    6   7    8   9    10  11  12  13  14  15
		 *
		 * There are mandatory '-' characters before bytes: 4, 6, 8 and 10 */
		if (!(i & 1) && i >= 4 && i <= 10) {
			if (*string != '-')
				goto inval;
			++string;
		}

		/* Decode nibbles */
		for (j = 0; j < 2; ++j) {
			char ch = *string++;
			if (!__libc_hex2int(ch, &nibbles[j]))
				goto inval;
		}

		/* Convert nibbles to byte */
		nibbles[0] <<= 4;
		nibbles[0] |= nibbles[1];

		/* Write byte to result GUID */
		((byte_t *)result)[i] = nibbles[0];
	}
	return string;
inval:
	return NULL;
}




%{

__SYSDECL_END
#endif /* __CC__ */

}
