/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_IOCTLS_BLOCK_H
#define _ASM_IOCTLS_BLOCK_H 1

#include <asm/ioctl.h>

#if defined(__KOS__) || defined(__linux__)
#include <hybrid/typecore.h>

#define BLKROSET      _IO(0x12, 93)  /* [int const *arg] Set device read-only (0 = read-write) */
#define BLKROGET      _IO(0x12, 94)  /* [int *arg] Get read-only status (0 = read_write) */
#define BLKRRPART     _IO(0x12, 95)  /* Re-read partition table */
#define BLKGETSIZE    _IO(0x12, 96)  /* [long *arg] Return device size/512 */
#define BLKFLSBUF     _IO(0x12, 97)  /* Flush buffer cache */
#define BLKRASET      _IO(0x12, 98)  /* [unsigned long const *arg] Set read ahead for block device */
#define BLKRAGET      _IO(0x12, 99)  /* [unsigned long *arg] Get current read ahead setting */
#define BLKFRASET     _IO(0x12, 100) /* [unsigned long const *arg] Set filesystem read-ahead. */
#define BLKFRAGET     _IO(0x12, 101) /* [unsigned long *arg] Get filesystem read-ahead. */
#define BLKSECTSET    _IO(0x12, 102) /* [u16 const *arg] Set max sectors per request. */
#define BLKSECTGET    _IO(0x12, 103) /* [u16 *arg] Get max sectors per request. */
#define BLKSSZGET     _IO(0x12, 104) /* Get block device sector size */
#define BLKBSZGET    _IOR(0x12, 112, __SIZE_TYPE__) /* [size_t *arg] */
#define BLKBSZSET    _IOW(0x12, 113, __SIZE_TYPE__) /* [size_t *arg] */
#define BLKGETSIZE64 _IOR(0x12, 114, __SIZE_TYPE__) /* [u64 *arg] return device size in bytes */
#endif /* __KOS__ || __linux__ */

#endif /* !_ASM_IOCTLS_BLOCK_H */
