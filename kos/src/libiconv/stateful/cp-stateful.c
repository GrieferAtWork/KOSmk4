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
#ifndef GUARD_LIBICONV_STATEFUL_CP_STATEFUL_C
#define GUARD_LIBICONV_STATEFUL_CP_STATEFUL_C 1

#include "../api.h"
/**/

#include <hybrid/byteorder.h>

#include <kos/types.h>

#include <assert.h>
#include <stddef.h>

#include <libiconv/iconv.h>

#include "../codecs.h"
#include "cp-stateful.h"

#if CODEC_STATEFUL_COUNT != 0
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
 *    if (ch == 0x0E)             // 0x0E = ascii.SO
 *        STATE = DOUBLE_BYTE_1;
 *    else if (ch == 0x0F)        // 0x0F = ascii.SI
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
 *        return <DOUBLE_BYTE_LOOKUP_TABLE>[ch];
 *    }
 * }
 *
 */

/*[[[deemon
import File from deemon;
import fs;
// Put in a seperate file so this one doesn't bloat too much
local dataFilename = "cp-stateful-data.c.inl";
local savedStdout = File.stdout;
File.stdout = File.open(dataFilename, "w");
File.stdout.write(File.open("cp-stateful.c").read().decode("utf-8").partition("#ifndef")[0].unifylines());
(printCpStatefulDatabase from ..iconvdata.iconvdata)();
File.stdout.close();
File.stdout = savedStdout;
print "#include", repr dataFilename;
]]]*/
#include "cp-stateful-data.c.inl"
/*[[[end]]]*/


/************************************************************************/
/* Stateful code page encode/decode functions.                          */
/************************************************************************/
//INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
//libiconv_stateful_decode(struct iconv_decode *__restrict self,
//                         /*cp???*/ char const *__restrict data, size_t size) {
//	/* TODO */
//}
//
//INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
//libiconv_stateful_encode(struct iconv_encode *__restrict self,
//                         /*utf-8*/ char const *__restrict data, size_t size) {
//	/* TODO */
//}


/* Initialize a stateful encoder/decoder. */
INTERN NONNULL((1, 2)) void CC
libiconv_stateful_encode_init(struct iconv_encode *__restrict self,
                              /*out*/ struct iconv_printer *__restrict input) {
	assert(self->ice_codec >= CODEC_STATEFUL_MIN &&
	       self->ice_codec <= CODEC_STATEFUL_MAX);
	(void)self;
	(void)input;
	/* TODO */
}

INTERN NONNULL((1, 2)) void CC
libiconv_stateful_decode_init(struct iconv_decode *__restrict self,
                              /*out*/ struct iconv_printer *__restrict input) {
	assert(self->icd_codec >= CODEC_STATEFUL_MIN &&
	       self->icd_codec <= CODEC_STATEFUL_MAX);
	(void)self;
	(void)input;
	/* TODO */
}

/* These two functions are lazily loaded in `/libiconv/iconv.c' */
DEFINE_PUBLIC_ALIAS(iconv_stateful_encode_init, libiconv_stateful_encode_init);
DEFINE_PUBLIC_ALIAS(iconv_stateful_decode_init, libiconv_stateful_decode_init);

DECL_END
#endif /* CODEC_STATEFUL_COUNT != 0 */

#endif /* !GUARD_LIBICONV_STATEFUL_CP_STATEFUL_C */
