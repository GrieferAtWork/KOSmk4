/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBANSITTY_CP_H
#define GUARD_LIBANSITTY_CP_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#ifndef FCALL
#define FCALL __FCALL
#endif /* !FCALL */

DECL_BEGIN

INTDEF ATTR_CONST WUNUSED char32_t NOTHROW(FCALL libansitty_decode_cp_ldm)(uint8_t byte);

INTDEF ATTR_CONST WUNUSED char32_t NOTHROW(FCALL libansitty_decode_cp_dutch)(uint8_t byte);
INTDEF ATTR_CONST WUNUSED char32_t NOTHROW(FCALL libansitty_decode_cp_finnish)(uint8_t byte);
INTDEF ATTR_CONST WUNUSED char32_t NOTHROW(FCALL libansitty_decode_cp_french)(uint8_t byte);
INTDEF ATTR_CONST WUNUSED char32_t NOTHROW(FCALL libansitty_decode_cp_french_canadian)(uint8_t byte);
INTDEF ATTR_CONST WUNUSED char32_t NOTHROW(FCALL libansitty_decode_cp_german)(uint8_t byte);
INTDEF ATTR_CONST WUNUSED char32_t NOTHROW(FCALL libansitty_decode_cp_italian)(uint8_t byte);
INTDEF ATTR_CONST WUNUSED char32_t NOTHROW(FCALL libansitty_decode_cp_norwegian)(uint8_t byte); /* Or Danish */
INTDEF ATTR_CONST WUNUSED char32_t NOTHROW(FCALL libansitty_decode_cp_portuguese)(uint8_t byte);
INTDEF ATTR_CONST WUNUSED char32_t NOTHROW(FCALL libansitty_decode_cp_spanish)(uint8_t byte);
INTDEF ATTR_CONST WUNUSED char32_t NOTHROW(FCALL libansitty_decode_cp_swedish)(uint8_t byte);
INTDEF ATTR_CONST WUNUSED char32_t NOTHROW(FCALL libansitty_decode_cp_swiss)(uint8_t byte);

INTDEF ATTR_CONST WUNUSED uint8_t NOTHROW(FCALL libansitty_encode_cp_dutch)(char32_t ch);
INTDEF ATTR_CONST WUNUSED uint8_t NOTHROW(FCALL libansitty_encode_cp_finnish)(char32_t ch);
INTDEF ATTR_CONST WUNUSED uint8_t NOTHROW(FCALL libansitty_encode_cp_french)(char32_t ch);
INTDEF ATTR_CONST WUNUSED uint8_t NOTHROW(FCALL libansitty_encode_cp_french_canadian)(char32_t ch);
INTDEF ATTR_CONST WUNUSED uint8_t NOTHROW(FCALL libansitty_encode_cp_german)(char32_t ch);
INTDEF ATTR_CONST WUNUSED uint8_t NOTHROW(FCALL libansitty_encode_cp_italian)(char32_t ch);
INTDEF ATTR_CONST WUNUSED uint8_t NOTHROW(FCALL libansitty_encode_cp_norwegian)(char32_t ch); /* Or Danish */
INTDEF ATTR_CONST WUNUSED uint8_t NOTHROW(FCALL libansitty_encode_cp_portuguese)(char32_t ch);
INTDEF ATTR_CONST WUNUSED uint8_t NOTHROW(FCALL libansitty_encode_cp_spanish)(char32_t ch);
INTDEF ATTR_CONST WUNUSED uint8_t NOTHROW(FCALL libansitty_encode_cp_swedish)(char32_t ch);
INTDEF ATTR_CONST WUNUSED uint8_t NOTHROW(FCALL libansitty_encode_cp_swiss)(char32_t ch);

DECL_END

#endif /* !GUARD_LIBANSITTY_CP_H */
