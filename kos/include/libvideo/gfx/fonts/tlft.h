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
#ifndef _LIBVIDEO_GFX_FONTS_TLFT_H
#define _LIBVIDEO_GFX_FONTS_TLFT_H 1

#include <__stdinc.h>

#include <hybrid/__byteswap.h>
#include <hybrid/__overflow.h>
#include <bits/types.h>

#ifndef TLFT_NO_LOOKUP
#include <hybrid/sequence/bsearch.h>
#endif /* !TLFT_NO_LOOKUP */

__DECL_BEGIN

/* Definitions for a simple tile-based font file format.
 * This file format is defined to be saved to a file that is then mmap()-ed
 * into  a processes memory, at which point a header can be read to quickly
 * determine the file offset (and  thus memory address) of a  bitmask-based
 * descriptor  of which pixels  to turn on/off  for representing some given
 * character.
 * With this in mind:
 *   - Characters are grouped as blocks of consecutively mapped unicode ranges
 *   - Only 16-bit unicode characters (U+0000 to U+FFFF) can be mapped
 *   - All characters have a fixed max width/height
 * Essentially, this file format is designed in order to house a unicode
 * character font set such  as u_vga16, as used  by KOS and found  here:
 *    http://www.inp.nsk.su/~bolkhov/files/fonts/univga/
 */

#ifdef __CC__

#define TI_MAG0  0
#define TLFTMAG0 127

#define TI_MAG1  1
#define TLFTMAG1 'T'

#define TI_MAG2  2
#define TLFTMAG2 'l'

#define TI_MAG3  3
#define TLFTMAG3 'F'

#define TI_MAG4  4
#define TLFTMAG4 't'

#define TI_VERS     5
#define TLFTVERSION 0 /* Version ID */

#define TLFT_NIDENT 6

typedef struct {
	__uint8_t     h_ident[TLFT_NIDENT];  /* Identification bits. */
	__uint8_t     h_hdrsize;             /* Offset of `h_groups' (from the start of the file; always divisible by 2) */
	__uint8_t     h_chwidth;             /* Character width (in bits) (usually `8') */
	__uint8_t     h_log2chsize;          /* log2(Character tile size (in bytes)) (usually `3' (for 8) or `4' (for 16)) */
	__uint8_t     h_ngroups;             /* Number of unicode character groups. */
	__uint16_t    h_nchars;              /* Number of characters in `h_chars' (<= 0xffa1 == 0x10000 - 95) (little endian). */
/*	__byte_t      h_pad[offsetafter(TLFT_Hdr, h_nchars) - h_hdrsize]; */
/*	TLFT_UniGroup h_groups[h_ngroups];    * Unicode character groups */
/*	__byte_t      h_ascii[95][1 << h_log2chsize]; * Representations for U+0020-U+007e */
/*	__byte_t      h_chars[][1 << h_log2chsize];   * Unicode group blobs. */
} TLFT_Hdr;

/* Helper macros to getting offsets and file size from a given TLFT header.
 * NOTE: To verify the integrity of a TLFT memory mapping, all that's  required
 *       is to ensure that header identification bits have their proper values,
 *       as well as that `stat::st_size >= TLFT_Hdr_GetSizeOfFile()' */
#define TLFT_Hdr_GetOffsetOfGroups(self) (__CCAST(__uint32_t)(self)->h_hdrsize)
#define TLFT_Hdr_GetOffsetOfAscii(self)  (TLFT_Hdr_GetOffsetOfGroups(self) + __CCAST(__uint32_t)((self)->h_ngroups * 8))
#define TLFT_Hdr_GetOffsetOfChars(self)  (TLFT_Hdr_GetOffsetOfAscii(self) + (__CCAST(__uint32_t)95 << (self)->h_log2chsize))
#define TLFT_Hdr_GetSizeOfFile(self)     (TLFT_Hdr_GetOffsetOfAscii(self) + __CCAST(__uint32_t)((__CCAST(__uint32_t)(self)->h_nchars + 95) << (self)->h_log2chsize))

typedef struct {
	__uint16_t ug_minuni; /* Lowest unicode character within this group (little endian) */
	__uint16_t ug_maxuni; /* Greatest unicode character within this group  */
	__uint16_t ug_offset; /* Offset of the first character bitmap within this group
	                       * To-be shifted by `h_log2chsize' and added to `h_chars' */
	__uint8_t _ug_pad[2]; /* Unused (for now) */
} TLFT_UniGroup;


#ifndef TLFT_NO_LOOKUP
/* Sample implementation for  how to perform  a character  bitmap
 * lookup for a given TLFT file that has been mapped into memory.
 * Upon success, return the `1 << self->h_log2chsize'-byte  large
 * bitmap  for `ch', or `NULL' if the character is not printable. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __uint8_t const *
tlft_lookup(TLFT_Hdr const *__restrict self, __uint32_t ch) {
	__uint8_t const *chars, *ascii;
	TLFT_UniGroup *groups;
	__uint8_t i;
	groups = (TLFT_UniGroup *)((__byte_t *)self + self->h_hdrsize);
	ascii  = (__uint8_t *)(groups + self->h_ngroups);
	/* Check for simple case: ASCII character */
	if (ch >= 0x0020 && ch <= 0x007e)
		return ascii + ((ch - 0x0020) << self->h_log2chsize);
	chars = ascii + (95 << self->h_log2chsize);
	/* bsearch-style lookup */
	BSEARCH_RANGE(i, groups, self->h_ngroups,
	               /*item*/ .ug_minuni,
	               /*item*/ .ug_maxuni, ch) {
		/* Found it! */
		return chars + (groups[i].ug_offset << self->h_log2chsize);
	}
	return __NULLPTR;
}
#endif /* !TLFT_NO_LOOKUP */

#endif /* __CC__ */



__DECL_END

#endif /* !_LIBVIDEO_GFX_FONTS_TLFT_H */
