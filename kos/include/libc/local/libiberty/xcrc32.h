/* HASH CRC-32:0xba967462 */
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
#ifndef __local_xcrc32_defined
#define __local_xcrc32_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(xcrc32) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) __UINT32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(xcrc32))(__BYTE_TYPE__ const *__buf, __STDC_INT_AS_SIZE_T __len, __UINT32_TYPE__ __crc) {
	/* Taken from `libiberty' (which is the  same library also used by  `gdbserver')
	 * Note that even though `libiberty' is the origin of the contents of this file,
	 * heavy  changes  have been  made to  better incorporate  the system  into KOS.
	 * Find the origin of information here:
	 *   https://code.woboq.org/gcc/libiberty/crc32.c.html
	 * And see the (unmodified) copyright notice taken form the start of that file below.
	 */
	/* crc32.c
	   Copyright (C) 2009-2017 Free Software Foundation, Inc.
	   This file is part of the libiberty library.
	   This file is free software; you can redistribute it and/or modify
	   it under the terms of the GNU General Public License as published by
	   the Free Software Foundation; either version 2 of the License, or
	   (at your option) any later version.
	   In addition to the permissions in the GNU General Public License, the
	   Free Software Foundation gives you unlimited permission to link the
	   compiled version of this file into combinations with other programs,
	   and to distribute those combinations without any restriction coming
	   from the use of this file.  (The General Public License restrictions
	   do apply in other respects; for example, they cover modification of
	   the file, and distribution when not linked into a combined
	   executable.)
	   This program is distributed in the hope that it will be useful,
	   but WITHOUT ANY WARRANTY; without even the implied warranty of
	   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	   GNU General Public License for more details.
	   You should have received a copy of the GNU General Public License
	   along with this program; if not, write to the Free Software
	   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
	*/
	static __UINT32_TYPE__ const __crc32_table[] = {
		__UINT32_C(0x00000000), __UINT32_C(0x04c11db7), __UINT32_C(0x09823b6e), __UINT32_C(0x0d4326d9),
		__UINT32_C(0x130476dc), __UINT32_C(0x17c56b6b), __UINT32_C(0x1a864db2), __UINT32_C(0x1e475005),
		__UINT32_C(0x2608edb8), __UINT32_C(0x22c9f00f), __UINT32_C(0x2f8ad6d6), __UINT32_C(0x2b4bcb61),
		__UINT32_C(0x350c9b64), __UINT32_C(0x31cd86d3), __UINT32_C(0x3c8ea00a), __UINT32_C(0x384fbdbd),
		__UINT32_C(0x4c11db70), __UINT32_C(0x48d0c6c7), __UINT32_C(0x4593e01e), __UINT32_C(0x4152fda9),
		__UINT32_C(0x5f15adac), __UINT32_C(0x5bd4b01b), __UINT32_C(0x569796c2), __UINT32_C(0x52568b75),
		__UINT32_C(0x6a1936c8), __UINT32_C(0x6ed82b7f), __UINT32_C(0x639b0da6), __UINT32_C(0x675a1011),
		__UINT32_C(0x791d4014), __UINT32_C(0x7ddc5da3), __UINT32_C(0x709f7b7a), __UINT32_C(0x745e66cd),
		__UINT32_C(0x9823b6e0), __UINT32_C(0x9ce2ab57), __UINT32_C(0x91a18d8e), __UINT32_C(0x95609039),
		__UINT32_C(0x8b27c03c), __UINT32_C(0x8fe6dd8b), __UINT32_C(0x82a5fb52), __UINT32_C(0x8664e6e5),
		__UINT32_C(0xbe2b5b58), __UINT32_C(0xbaea46ef), __UINT32_C(0xb7a96036), __UINT32_C(0xb3687d81),
		__UINT32_C(0xad2f2d84), __UINT32_C(0xa9ee3033), __UINT32_C(0xa4ad16ea), __UINT32_C(0xa06c0b5d),
		__UINT32_C(0xd4326d90), __UINT32_C(0xd0f37027), __UINT32_C(0xddb056fe), __UINT32_C(0xd9714b49),
		__UINT32_C(0xc7361b4c), __UINT32_C(0xc3f706fb), __UINT32_C(0xceb42022), __UINT32_C(0xca753d95),
		__UINT32_C(0xf23a8028), __UINT32_C(0xf6fb9d9f), __UINT32_C(0xfbb8bb46), __UINT32_C(0xff79a6f1),
		__UINT32_C(0xe13ef6f4), __UINT32_C(0xe5ffeb43), __UINT32_C(0xe8bccd9a), __UINT32_C(0xec7dd02d),
		__UINT32_C(0x34867077), __UINT32_C(0x30476dc0), __UINT32_C(0x3d044b19), __UINT32_C(0x39c556ae),
		__UINT32_C(0x278206ab), __UINT32_C(0x23431b1c), __UINT32_C(0x2e003dc5), __UINT32_C(0x2ac12072),
		__UINT32_C(0x128e9dcf), __UINT32_C(0x164f8078), __UINT32_C(0x1b0ca6a1), __UINT32_C(0x1fcdbb16),
		__UINT32_C(0x018aeb13), __UINT32_C(0x054bf6a4), __UINT32_C(0x0808d07d), __UINT32_C(0x0cc9cdca),
		__UINT32_C(0x7897ab07), __UINT32_C(0x7c56b6b0), __UINT32_C(0x71159069), __UINT32_C(0x75d48dde),
		__UINT32_C(0x6b93dddb), __UINT32_C(0x6f52c06c), __UINT32_C(0x6211e6b5), __UINT32_C(0x66d0fb02),
		__UINT32_C(0x5e9f46bf), __UINT32_C(0x5a5e5b08), __UINT32_C(0x571d7dd1), __UINT32_C(0x53dc6066),
		__UINT32_C(0x4d9b3063), __UINT32_C(0x495a2dd4), __UINT32_C(0x44190b0d), __UINT32_C(0x40d816ba),
		__UINT32_C(0xaca5c697), __UINT32_C(0xa864db20), __UINT32_C(0xa527fdf9), __UINT32_C(0xa1e6e04e),
		__UINT32_C(0xbfa1b04b), __UINT32_C(0xbb60adfc), __UINT32_C(0xb6238b25), __UINT32_C(0xb2e29692),
		__UINT32_C(0x8aad2b2f), __UINT32_C(0x8e6c3698), __UINT32_C(0x832f1041), __UINT32_C(0x87ee0df6),
		__UINT32_C(0x99a95df3), __UINT32_C(0x9d684044), __UINT32_C(0x902b669d), __UINT32_C(0x94ea7b2a),
		__UINT32_C(0xe0b41de7), __UINT32_C(0xe4750050), __UINT32_C(0xe9362689), __UINT32_C(0xedf73b3e),
		__UINT32_C(0xf3b06b3b), __UINT32_C(0xf771768c), __UINT32_C(0xfa325055), __UINT32_C(0xfef34de2),
		__UINT32_C(0xc6bcf05f), __UINT32_C(0xc27dede8), __UINT32_C(0xcf3ecb31), __UINT32_C(0xcbffd686),
		__UINT32_C(0xd5b88683), __UINT32_C(0xd1799b34), __UINT32_C(0xdc3abded), __UINT32_C(0xd8fba05a),
		__UINT32_C(0x690ce0ee), __UINT32_C(0x6dcdfd59), __UINT32_C(0x608edb80), __UINT32_C(0x644fc637),
		__UINT32_C(0x7a089632), __UINT32_C(0x7ec98b85), __UINT32_C(0x738aad5c), __UINT32_C(0x774bb0eb),
		__UINT32_C(0x4f040d56), __UINT32_C(0x4bc510e1), __UINT32_C(0x46863638), __UINT32_C(0x42472b8f),
		__UINT32_C(0x5c007b8a), __UINT32_C(0x58c1663d), __UINT32_C(0x558240e4), __UINT32_C(0x51435d53),
		__UINT32_C(0x251d3b9e), __UINT32_C(0x21dc2629), __UINT32_C(0x2c9f00f0), __UINT32_C(0x285e1d47),
		__UINT32_C(0x36194d42), __UINT32_C(0x32d850f5), __UINT32_C(0x3f9b762c), __UINT32_C(0x3b5a6b9b),
		__UINT32_C(0x0315d626), __UINT32_C(0x07d4cb91), __UINT32_C(0x0a97ed48), __UINT32_C(0x0e56f0ff),
		__UINT32_C(0x1011a0fa), __UINT32_C(0x14d0bd4d), __UINT32_C(0x19939b94), __UINT32_C(0x1d528623),
		__UINT32_C(0xf12f560e), __UINT32_C(0xf5ee4bb9), __UINT32_C(0xf8ad6d60), __UINT32_C(0xfc6c70d7),
		__UINT32_C(0xe22b20d2), __UINT32_C(0xe6ea3d65), __UINT32_C(0xeba91bbc), __UINT32_C(0xef68060b),
		__UINT32_C(0xd727bbb6), __UINT32_C(0xd3e6a601), __UINT32_C(0xdea580d8), __UINT32_C(0xda649d6f),
		__UINT32_C(0xc423cd6a), __UINT32_C(0xc0e2d0dd), __UINT32_C(0xcda1f604), __UINT32_C(0xc960ebb3),
		__UINT32_C(0xbd3e8d7e), __UINT32_C(0xb9ff90c9), __UINT32_C(0xb4bcb610), __UINT32_C(0xb07daba7),
		__UINT32_C(0xae3afba2), __UINT32_C(0xaafbe615), __UINT32_C(0xa7b8c0cc), __UINT32_C(0xa379dd7b),
		__UINT32_C(0x9b3660c6), __UINT32_C(0x9ff77d71), __UINT32_C(0x92b45ba8), __UINT32_C(0x9675461f),
		__UINT32_C(0x8832161a), __UINT32_C(0x8cf30bad), __UINT32_C(0x81b02d74), __UINT32_C(0x857130c3),
		__UINT32_C(0x5d8a9099), __UINT32_C(0x594b8d2e), __UINT32_C(0x5408abf7), __UINT32_C(0x50c9b640),
		__UINT32_C(0x4e8ee645), __UINT32_C(0x4a4ffbf2), __UINT32_C(0x470cdd2b), __UINT32_C(0x43cdc09c),
		__UINT32_C(0x7b827d21), __UINT32_C(0x7f436096), __UINT32_C(0x7200464f), __UINT32_C(0x76c15bf8),
		__UINT32_C(0x68860bfd), __UINT32_C(0x6c47164a), __UINT32_C(0x61043093), __UINT32_C(0x65c52d24),
		__UINT32_C(0x119b4be9), __UINT32_C(0x155a565e), __UINT32_C(0x18197087), __UINT32_C(0x1cd86d30),
		__UINT32_C(0x029f3d35), __UINT32_C(0x065e2082), __UINT32_C(0x0b1d065b), __UINT32_C(0x0fdc1bec),
		__UINT32_C(0x3793a651), __UINT32_C(0x3352bbe6), __UINT32_C(0x3e119d3f), __UINT32_C(0x3ad08088),
		__UINT32_C(0x2497d08d), __UINT32_C(0x2056cd3a), __UINT32_C(0x2d15ebe3), __UINT32_C(0x29d4f654),
		__UINT32_C(0xc5a92679), __UINT32_C(0xc1683bce), __UINT32_C(0xcc2b1d17), __UINT32_C(0xc8ea00a0),
		__UINT32_C(0xd6ad50a5), __UINT32_C(0xd26c4d12), __UINT32_C(0xdf2f6bcb), __UINT32_C(0xdbee767c),
		__UINT32_C(0xe3a1cbc1), __UINT32_C(0xe760d676), __UINT32_C(0xea23f0af), __UINT32_C(0xeee2ed18),
		__UINT32_C(0xf0a5bd1d), __UINT32_C(0xf464a0aa), __UINT32_C(0xf9278673), __UINT32_C(0xfde69bc4),
		__UINT32_C(0x89b8fd09), __UINT32_C(0x8d79e0be), __UINT32_C(0x803ac667), __UINT32_C(0x84fbdbd0),
		__UINT32_C(0x9abc8bd5), __UINT32_C(0x9e7d9662), __UINT32_C(0x933eb0bb), __UINT32_C(0x97ffad0c),
		__UINT32_C(0xafb010b1), __UINT32_C(0xab710d06), __UINT32_C(0xa6322bdf), __UINT32_C(0xa2f33668),
		__UINT32_C(0xbcb4666d), __UINT32_C(0xb8757bda), __UINT32_C(0xb5365d03), __UINT32_C(0xb1f740b4)
	};

	/*
	@deftypefn Extension {unsigned int} crc32 (const unsigned char *@var{buf}, @
	  int @var{len}, unsigned int @var{init})
	Compute the 32-bit CRC of @var{buf} which has length @var{len}.  The
	starting value is @var{init}; this may be used to compute the CRC of
	data split across multiple buffers by passing the return value of each
	call as the @var{init} parameter of the next.
	This is used by the @command{gdb} remote protocol for the @samp{qCRC}
	command.  In order to get the same results as gdb for a block of data,
	you must pass the first CRC parameter as @code{0xffffffff}.
	This CRC can be specified as:
	  Width  : 32
	  Poly   : 0x04c11db7
	  Init   : parameter, typically 0xffffffff
	  RefIn  : false
	  RefOut : false
	  XorOut : 0
	This differs from the "standard" CRC-32 algorithm in that the values
	are not reflected, and there is no final XOR value.  These differences
	make it easy to compose the values of multiple blocks.
	@end deftypefn
	*/
	while (__len--) {
		__crc = (__crc << 8) ^ __crc32_table[((__crc >> 24) ^ *__buf) & 255];
		__buf++;
	}
	return __crc;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_xcrc32_defined
#define __local___localdep_xcrc32_defined
#define __localdep_xcrc32 __LIBC_LOCAL_NAME(xcrc32)
#endif /* !__local___localdep_xcrc32_defined */
#endif /* !__local_xcrc32_defined */
