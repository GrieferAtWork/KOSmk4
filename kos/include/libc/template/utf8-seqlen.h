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
{
	/* ASCII */
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0x00-0x0f */
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0x10-0x1f */
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0x20-0x2f */
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0x30-0x3f */
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0x40-0x4f */
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0x50-0x5f */
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0x60-0x6f */
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0x70-0x7f */
	/* Unicode follow-up word (`0b10??????'). */
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /* 0x80-0x8f */
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /* 0x90-0x9f */
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /* 0xa0-0xaf */
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /* 0xb0-0xbf */
	/* `0b110?????' */
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, /* 0xc0-0xcf */
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, /* 0xd0-0xdf */
	/* `0b1110????' */
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3, /* 0xe0-0xef */
	/* `0b11110???' */
	4,4,4,4,4,4,4,4,                 /* 0xf0-0xf7 */
	5,5,5,5,                         /* 0xf8-0xfb */
	6,6,                             /* 0xfc-0xfd */
	7,                               /* 0xfe */
	8                                /* 0xff */
}
