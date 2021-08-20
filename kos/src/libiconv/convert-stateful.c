/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBICONV_CONVERT_STATEFUL_C
#define GUARD_LIBICONV_CONVERT_STATEFUL_C 1

#include "api.h"
/**/

#include <hybrid/byteorder.h>

#include <kos/types.h>

#include <libiconv/iconv.h>

#include "codecs.h"

DECL_BEGIN

/*
 * Codec: IBM930
 * Codec: IBM933
 * Codec: IBM935
 * Codec: IBM937
 * Codec: IBM939
 * Codec: IBM1364
 * Codec: IBM1371
 * Codec: IBM1388
 * Codec: IBM1390  [*]
 * Codec: IBM1399  [*]
 *
 * [*] The DOUBLE_BYTE_LOOKUP_TABLE contains entires that decode to 2 unicode characters
 *
 * NOTE: Each codec has a different <SINGLE_BYTE_LOOKUP_TABLE> / <DOUBLE_BYTE_LOOKUP_TABLE>
 *
 * VAR STATE: enum { SINGLE_BYTE, DOUBLE_BYTE_1, DOUBLE_BYTE_2 } = SINGLE_BYTE
 * VAR SAVED_BYTE: unsigned char                                 = <undefined>
 *
 * decode(unsigned char ch) {
 *    if (ch == 0x0e)             // 0x0e = ascii.SO
 *        STATE = DOUBLE_BYTE_1;
 *    else if (ch == 0x0f)        // 0x0e = ascii.SI
 *        STATE = SINGLE_BYTE;
 *    else {
 *        if (STATE == SINGLE_BYTE) {
 *            return <SINGLE_BYTE_LOOKUP_TABLE>[ch];
 *        }
 *        if (STATE == DOUBLE_BYTE_1) {
 *            STATE = DOUBLE_BYTE_2;
 *            SAVED_BYTE = ch;
 *            return;
 *        }
 *        assert(STATE == DOUBLE_BYTE_2);
 *        uint16_t ch16 = (SAVED_BYTE << 8) | ch;
 *        return  <DOUBLE_BYTE_LOOKUP_TABLE>[ch];
 *    }
 * }
 *
 */


/* TODO */

DECL_END

#endif /* !GUARD_LIBICONV_CONVERT_STATEFUL_C */
