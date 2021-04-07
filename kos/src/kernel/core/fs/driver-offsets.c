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
#ifndef GUARD_KERNEL_CORE_FS_DRIVER_OFFSETS_C
#define GUARD_KERNEL_CORE_FS_DRIVER_OFFSETS_C 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_DRIVER
#include <kernel/driver-offsets.h>
#include <kernel/driver.h>

#include <stddef.h>

DECL_BEGIN

#if __SIZEOF_POINTER__ >= 8
#define WS(base, name) OFFSET_##base##64_##name
#else /* __SIZEOF_POINTER__ >= 8 */
#define WS(base, name) OFFSET_##base##32_##name
#endif /* __SIZEOF_POINTER__ < 8 */

/* Assert offsets for `struct driver' */
STATIC_ASSERT(offsetof(struct driver, d_refcnt)               == WS(DRIVER, REFCNT));
STATIC_ASSERT(offsetof(struct driver, d_weakrefcnt)           == WS(DRIVER, WEAKREFCNT));
STATIC_ASSERT(offsetof(struct driver, d_name)                 == WS(DRIVER, NAME));
STATIC_ASSERT(offsetof(struct driver, d_filename)             == WS(DRIVER, FILENAME));
STATIC_ASSERT(offsetof(struct driver, d_file)                 == WS(DRIVER, FILE));
STATIC_ASSERT(offsetof(struct driver, d_cmdline)              == WS(DRIVER, CMDLINE));
STATIC_ASSERT(offsetof(struct driver, d_argc)                 == WS(DRIVER, ARGC));
STATIC_ASSERT(offsetof(struct driver, d_argv)                 == WS(DRIVER, ARGV));
STATIC_ASSERT(offsetof(struct driver, d_flags)                == WS(DRIVER, FLAGS));
STATIC_ASSERT(offsetof(struct driver, d_initthread)           == WS(DRIVER, INITTHREAD));
STATIC_ASSERT(offsetof(struct driver, d_loadaddr)             == WS(DRIVER, LOADADDR));
STATIC_ASSERT(offsetof(struct driver, d_loadstart)            == WS(DRIVER, LOADSTART));
STATIC_ASSERT(offsetof(struct driver, d_loadend)              == WS(DRIVER, LOADEND));
STATIC_ASSERT(offsetof(struct driver, d_eh_frame_start)       == WS(DRIVER, EH_FRAME_START));
STATIC_ASSERT(offsetof(struct driver, d_eh_frame_end)         == WS(DRIVER, EH_FRAME_END));
STATIC_ASSERT(offsetof(struct driver, d_eh_frame_cache)       == WS(DRIVER, EH_FRAME_CACHE));
STATIC_ASSERT(offsetof(struct driver, d_eh_frame_cache_lock)  == WS(DRIVER, EH_FRAME_CACHE_LOCK));
STATIC_ASSERT(offsetof(struct driver, d_eh_frame_cache_semi0) == WS(DRIVER, EH_FRAME_CACHE_SEMI0));
STATIC_ASSERT(offsetof(struct driver, d_eh_frame_cache_leve0) == WS(DRIVER, EH_FRAME_CACHE_LEVE0));
STATIC_ASSERT(offsetof(struct driver, d_depcnt)               == WS(DRIVER, DEPCNT));
STATIC_ASSERT(offsetof(struct driver, d_depvec)               == WS(DRIVER, DEPVEC));
STATIC_ASSERT(offsetof(struct driver, d_dyncnt)               == WS(DRIVER, DYNCNT));
STATIC_ASSERT(offsetof(struct driver, d_dynhdr)               == WS(DRIVER, DYNHDR));
STATIC_ASSERT(offsetof(struct driver, d_dynsym_tab)           == WS(DRIVER, DYNSYM_TAB));
STATIC_ASSERT(offsetof(struct driver, d_dynsym_cnt)           == WS(DRIVER, DYNSYM_CNT));
STATIC_ASSERT(offsetof(struct driver, d_hashtab)              == WS(DRIVER, HASHTAB));
STATIC_ASSERT(offsetof(struct driver, d_dynstr)               == WS(DRIVER, DYNSTR));
STATIC_ASSERT(offsetof(struct driver, d_dynstr_end)           == WS(DRIVER, DYNSTR_END));
STATIC_ASSERT(offsetof(struct driver, d_shoff)                == WS(DRIVER, SHOFF));
STATIC_ASSERT(offsetof(struct driver, d_shstrndx)             == WS(DRIVER, SHSTRNDX));
STATIC_ASSERT(offsetof(struct driver, d_shnum)                == WS(DRIVER, SHNUM));
STATIC_ASSERT(offsetof(struct driver, d_shdr)                 == WS(DRIVER, SHDR));
STATIC_ASSERT(offsetof(struct driver, d_sections_lock)        == WS(DRIVER, SECTIONS_LOCK));
STATIC_ASSERT(offsetof(struct driver, d_sections)             == WS(DRIVER, SECTIONS));
STATIC_ASSERT(offsetof(struct driver, d_deadsect)             == WS(DRIVER, DEADSECT));
STATIC_ASSERT(offsetof(struct driver, d_dangsect)             == WS(DRIVER, DANGSECT));
STATIC_ASSERT(offsetof(struct driver, d_shstrtab)             == WS(DRIVER, SHSTRTAB));
STATIC_ASSERT(offsetof(struct driver, d_shstrtab_end)         == WS(DRIVER, SHSTRTAB_END));
STATIC_ASSERT(offsetof(struct driver, d_phnum)                == WS(DRIVER, PHNUM));
STATIC_ASSERT(offsetof(struct driver, d_phdr)                 == WS(DRIVER, PHDR));

/* Assert offsets for `struct driver_state' */
STATIC_ASSERT(offsetof(struct driver_state, ds_refcnt)  == WS(DRIVER_STATE, REFCNT));
STATIC_ASSERT(offsetof(struct driver_state, ds_count)   == WS(DRIVER_STATE, COUNT));
STATIC_ASSERT(offsetof(struct driver_state, ds_drivers) == WS(DRIVER_STATE, DRIVERS));


DECL_END
#endif /* !CONFIG_USE_NEW_DRIVER */

#endif /* !GUARD_KERNEL_CORE_FS_DRIVER_OFFSETS_C */
