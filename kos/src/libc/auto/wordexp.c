/* HASH CRC-32:0xf06f0b71 */
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
#ifndef GUARD_LIBC_AUTO_WORDEXP_C
#define GUARD_LIBC_AUTO_WORDEXP_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/wordexp.h"
#include "../user/stdlib.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/crt/wordexp.h>
/* >> wordfree(3)
 * Free dynamic allocations made by `wordexp(3)' */
INTERN ATTR_SECTION(".text.crt.wordexp") ATTR_INOUT_OPT(1) void
NOTHROW_NCX(LIBCCALL libc_wordfree)(wordexp_t *self) {
	size_t i, end;
	char **words;
	if unlikely(!self)
		return;
	words = self->we_wordv;
	if unlikely(!words)
		return;
	i   = self->we_offs;
	end = i + self->we_wordc;
	for (; i < end; ++i)
		libc_free(words[i]);
	libc_free(words);
	self->we_wordv = NULL;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(wordfree, libc_wordfree);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_WORDEXP_C */
