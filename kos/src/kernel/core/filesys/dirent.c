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
#ifndef GUARD_KERNEL_CORE_FILESYS_DIRENT_C
#define GUARD_KERNEL_CORE_FILESYS_DIRENT_C 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>

#include <hybrid/unaligned.h>
#include <hybrid/typecore.h>

DECL_BEGIN

/* Return the hash of a given directory entry name.
 * This function is used by various APIs related to file lookup.
 * @throw: E_SEGFAULT: Failed to access the given `text'. */
PUBLIC ATTR_PURE WUNUSED NONNULL((1)) uintptr_t FCALL
fdirent_hash(CHECKED USER /*utf-8*/ char const *__restrict text, u16 textlen)
		THROWS(E_SEGFAULT) {
	uintptr_t hash = FDIRENT_EMPTY_HASH;
	uintptr_t const *iter, *end;

	/* Setup iterators. */
	iter = (uintptr_t const *)text;
	end  = iter + (textlen / sizeof(uintptr_t));

	/* Hash whole words */
	while (iter < end) {
		hash += UNALIGNED_GET(iter);
		hash *= 9;
		++iter;
	}

	/* Hash trailing word */
	switch (textlen & (sizeof(uintptr_t) - 1)) {
#if __SIZEOF_POINTER__ > 4
	case 7:
		hash += (uintptr_t)((byte_t const *)iter)[6] << 48;
		ATTR_FALLTHROUGH
	case 6:
		hash += (uintptr_t)((byte_t const *)iter)[5] << 40;
		ATTR_FALLTHROUGH
	case 5:
		hash += (uintptr_t)((byte_t const *)iter)[4] << 32;
		ATTR_FALLTHROUGH
	case 4:
		hash += (uintptr_t)((byte_t const *)iter)[3] << 24;
		ATTR_FALLTHROUGH
#endif /* __SIZEOF_POINTER__ > 4 */
	case 3:
		hash += (uintptr_t)((byte_t const *)iter)[2] << 16;
		ATTR_FALLTHROUGH
	case 2:
		hash += (uintptr_t)((byte_t const *)iter)[1] << 8;
		ATTR_FALLTHROUGH
	case 1:
		hash += (uintptr_t)((byte_t const *)iter)[0];
		break;
	default: break;
	}
	return hash;
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DIRENT_C */
