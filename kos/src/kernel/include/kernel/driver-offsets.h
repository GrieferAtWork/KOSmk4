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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_OFFSETS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_OFFSETS_H 1

/* WARNING: If offsets from this file are changed, then you must touch
 *          /kos/misc/magicemulator/_vboxgdbkos.dee, as that file includes
 *          this one but may not get re-compiled once this one changes. */


/* Offsets into `struct driver' (on 32-bit machines) */
#define OFFSET_DRIVER32_REFCNT               0
#define OFFSET_DRIVER32_WEAKREFCNT           4
#define OFFSET_DRIVER32_NAME                 8
#define OFFSET_DRIVER32_FILENAME             12
#define OFFSET_DRIVER32_FILE                 16
#define OFFSET_DRIVER32_CMDLINE              20
#define OFFSET_DRIVER32_ARGC                 24
#define OFFSET_DRIVER32_ARGV                 28
#define OFFSET_DRIVER32_FLAGS                32
#define OFFSET_DRIVER32_INITTHREAD           36
#define OFFSET_DRIVER32_LOADADDR             40
#define OFFSET_DRIVER32_LOADSTART            44
#define OFFSET_DRIVER32_LOADEND              48
#define OFFSET_DRIVER32_EH_FRAME_START       52
#define OFFSET_DRIVER32_EH_FRAME_END         56
#define OFFSET_DRIVER32_EH_FRAME_CACHE       60
#define OFFSET_DRIVER32_EH_FRAME_CACHE_LOCK  64
#define OFFSET_DRIVER32_EH_FRAME_CACHE_SEMI0 68
#define OFFSET_DRIVER32_EH_FRAME_CACHE_LEVE0 72
#define OFFSET_DRIVER32_DEPCNT               76
#define OFFSET_DRIVER32_DEPVEC               80
#define OFFSET_DRIVER32_DYNCNT               84
#define OFFSET_DRIVER32_DYNHDR               88
#define OFFSET_DRIVER32_DYNSYM_TAB           92
#define OFFSET_DRIVER32_DYNSYM_CNT           96
#define OFFSET_DRIVER32_HASHTAB              100
#define OFFSET_DRIVER32_DYNSTR               104
#define OFFSET_DRIVER32_DYNSTR_END           108
#define OFFSET_DRIVER32_SHOFF                112
#define OFFSET_DRIVER32_SHSTRNDX             116 /* 2-byte! */
#define OFFSET_DRIVER32_SHNUM                118 /* 2-byte! */
#define OFFSET_DRIVER32_SHDR                 120
#define OFFSET_DRIVER32_SECTIONS_LOCK        124
#define OFFSET_DRIVER32_SECTIONS             128
#define OFFSET_DRIVER32_DEADSECT             132
#define OFFSET_DRIVER32_DANGSECT             136
#define OFFSET_DRIVER32_SHSTRTAB             140
#define OFFSET_DRIVER32_SHSTRTAB_END         144
#define OFFSET_DRIVER32_PHNUM                148 /* 2-byte! */
#define OFFSET_DRIVER32_PHDR                 152

/* Offsets into `struct driver' (on 64-bit machines) */
#define OFFSET_DRIVER64_REFCNT               0
#define OFFSET_DRIVER64_WEAKREFCNT           8
#define OFFSET_DRIVER64_NAME                 16
#define OFFSET_DRIVER64_FILENAME             24
#define OFFSET_DRIVER64_FILE                 32
#define OFFSET_DRIVER64_CMDLINE              40
#define OFFSET_DRIVER64_ARGC                 48
#define OFFSET_DRIVER64_ARGV                 56
#define OFFSET_DRIVER64_FLAGS                64
#define OFFSET_DRIVER64_INITTHREAD           72
#define OFFSET_DRIVER64_LOADADDR             80
#define OFFSET_DRIVER64_LOADSTART            88
#define OFFSET_DRIVER64_LOADEND              96
#define OFFSET_DRIVER64_EH_FRAME_START       104
#define OFFSET_DRIVER64_EH_FRAME_END         112
#define OFFSET_DRIVER64_EH_FRAME_CACHE       120
#define OFFSET_DRIVER64_EH_FRAME_CACHE_LOCK  128
#define OFFSET_DRIVER64_EH_FRAME_CACHE_SEMI0 136
#define OFFSET_DRIVER64_EH_FRAME_CACHE_LEVE0 144 /* 4-byte! */
#define OFFSET_DRIVER64_DEPCNT               152
#define OFFSET_DRIVER64_DEPVEC               160
#define OFFSET_DRIVER64_DYNCNT               168
#define OFFSET_DRIVER64_DYNHDR               176
#define OFFSET_DRIVER64_DYNSYM_TAB           184
#define OFFSET_DRIVER64_DYNSYM_CNT           192
#define OFFSET_DRIVER64_HASHTAB              200
#define OFFSET_DRIVER64_DYNSTR               208
#define OFFSET_DRIVER64_DYNSTR_END           216
#define OFFSET_DRIVER64_SHOFF                224
#define OFFSET_DRIVER64_SHSTRNDX             232 /* 2-byte! */
#define OFFSET_DRIVER64_SHNUM                234 /* 2-byte! */
#define OFFSET_DRIVER64_SHDR                 240
#define OFFSET_DRIVER64_SECTIONS_LOCK        248
#define OFFSET_DRIVER64_SECTIONS             256
#define OFFSET_DRIVER64_DEADSECT             264
#define OFFSET_DRIVER64_DANGSECT             272
#define OFFSET_DRIVER64_SHSTRTAB             280
#define OFFSET_DRIVER64_SHSTRTAB_END         288
#define OFFSET_DRIVER64_PHNUM                296 /* 2-byte! */
#define OFFSET_DRIVER64_PHDR                 304


/* Offsets into `struct driver_state' (on 32-bit machines) */
#define OFFSET_DRIVER_STATE32_REFCNT   0
#define OFFSET_DRIVER_STATE32_COUNT    4
#define OFFSET_DRIVER_STATE32_DRIVERS  8

/* Offsets into `struct driver_state' (on 64-bit machines) */
#define OFFSET_DRIVER_STATE64_REFCNT   0
#define OFFSET_DRIVER_STATE64_COUNT    8
#define OFFSET_DRIVER_STATE64_DRIVERS  16


#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_OFFSETS_H */
