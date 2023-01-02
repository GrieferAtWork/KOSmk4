/* HASH CRC-32:0xa49c12bb */
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
#ifndef GUARD_LIBC_AUTO_KOS_UUID_C
#define GUARD_LIBC_AUTO_KOS_UUID_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "kos.uuid.h"

DECL_BEGIN

#include <libc/template/hex.h>
/* >> uuid_fromstr(3)
 * Convert a given `string' into a UUID
 * >> uuid_t g;
 * >> uuid_fromstr("054b1def-b2ae-4d99-a99c-54b9730c3dc3", &g);
 * @return: string + UUID_STRLEN: Success
 * @return: NULL:                 `string' isn't a valid UUID. */
INTERN ATTR_SECTION(".text.crt.sched.rpc") ATTR_IN(1) ATTR_OUT(2) char const *
NOTHROW_NCX(LIBCCALL libc_uuid_fromstr)(char const string[__UUID_STRLEN],
                                        uuid_t *__restrict result) {
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

		/* Write byte to result UUID */
		((byte_t *)result)[i] = nibbles[0];
	}
	return string;
inval:
	return NULL;
}

DECL_END

DEFINE_PUBLIC_ALIAS(uuid_fromstr, libc_uuid_fromstr);

#endif /* !GUARD_LIBC_AUTO_KOS_UUID_C */
