/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBBIOS86_BIOS86_H
#define _LIBBIOS86_BIOS86_H 1

#include "api.h"
/**/

#include <asm/os/kos/mman.h>
#include <bits/types.h>
#include <kos/anno.h>

#include <libvm86/emulator.h>

#ifdef __KERNEL__
#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <kernel/paging.h>
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
#endif /* __KERNEL__ */

/*
 * Helper library that  builds on-top of  libphys in  order
 * to provide  a memory  region  suitable for  making  bios
 * calls with the help of libvm86, thus providing a unified
 * interface  for allocating the  necessary buffers and for
 * making BIOS calls from protected mode.
 *
 * NOTE: This library is available both in kernel-, as  well
 *       as  user-space, but in the user-space version, it's
 *       the user's responsibility to grant I/O permissions.
 *       While  libphys will includes its own facilities for
 *       accessing  physical memory, the same cannot be said
 *       for this library in regards to I/O access. As  such
 *       it falls upon the user to do iopl(2) or ioperm(2).
 *
 * During  initialization,  this library  creates a  mapping as
 * follows, the base of which is returned from `bios86_init(3)'
 * and  may  not be  equal  to `NULL'!  (though  the pointed-to
 * memory will appear in low memory)
 *
 * Memory layout:
 *   00000-00fff   First page of physical memory; which includes the real-mode IVT
 *   01000-7ffff   Generic RAM (NOT identity-mapped)
 *   80000-fffff   EBDA+Video-ram+Video-BIOS+BIOS
 *
 * In total, this is exactly 1MiB of memory!
 */

#ifdef __CC__
__DECL_BEGIN

struct bios86 {
	__byte_t *b86_biosbase;    /* [1..1][owned] BIOS base address */
#ifdef __KERNEL__
	void    *_b86_unmapcookie; /* [1..1][owned] Unmap cookie */
#endif /* __KERNEL__ */
};

/* Size of the BIOS memory mapping. */
#define BIOS86_SIZE 0x100000 /* 1MiB (== 16 * 0xffff + 1) */

/* Base address where the virtual memory mapping for vm86 begins. */
#define BIOS86_MEM_SP    0x8000 /* 7K of stack memory (01000-07ffff is used for stack) */
#define BIOS86_MEM_GPBAS 0x8000 /* GeneralPurposeBASe for BIOS86 buffers. */
#define BIOS86_MEM_GPSIZ (0x80000 - BIOS86_MEM_GPBAS) /* Available space after `BIOS86_MEM_GPBAS' */

/* Helpers to calculate locations within a bios86 mapping. */
#define bios86_mem_gpbas(base)        ((__byte_t *)(base) + BIOS86_MEM_GPBAS)
#define BIOS86_FARPTR(seg, off)       (((seg) << 4) + (off))
#define bios86_farptr(base, seg, off) ((__byte_t *)(base) + BIOS86_FARPTR(seg, off))


/* Error return value for `bios86_init(3)' */
#if !defined(MAP_FAILED) && defined(__MAP_FAILED)
#define MAP_FAILED __MAP_FAILED
#endif /* !MAP_FAILED && __MAP_FAILED */


/* >> bios86_init(3)
 * Initialize a BIOS interrupt emulator `self'
 * @return:  0: Success.
 * @return: -1: Failed to initialize (s.a. `errno'). */
#ifdef __KERNEL__
typedef __ATTR_NONNULL_T((1)) void
(LIBBIOS86_CC *PBIOS86_INIT)(struct bios86 *__restrict self);
#ifdef LIBBIOS86_WANT_PROTOTYPES
LIBBIOS86_DECL __ATTR_NONNULL((1)) void
(LIBBIOS86_CC bios86_init)(struct bios86 *__restrict self);
#endif /* LIBBIOS86_WANT_PROTOTYPES */
#else /* __KERNEL__ */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) int
__NOTHROW_T(LIBBIOS86_CC *PBIOS86_INIT)(struct bios86 *__restrict self);
#ifdef LIBBIOS86_WANT_PROTOTYPES
LIBBIOS86_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW(LIBBIOS86_CC bios86_init)(struct bios86 *__restrict self);
#endif /* LIBBIOS86_WANT_PROTOTYPES */
#endif /* !__KERNEL__ */

/* >> bios86_fini(3)
 * Finalize the BIOS buffer interface. */
typedef __NOBLOCK __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBBIOS86_CC *PBIOS86_FINI)(struct bios86 *__restrict self);
#ifdef LIBBIOS86_WANT_PROTOTYPES
LIBBIOS86_DECL __NOBLOCK __ATTR_NONNULL((1)) void
__NOTHROW(LIBBIOS86_CC bios86_fini)(struct bios86 *__restrict self);
#endif /* LIBBIOS86_WANT_PROTOTYPES */



/* BIOS call emulation. */
struct bios86_emulator {
	vm86_state_t  b86e_vm;   /* VM86 controller. */
	struct bios86 b86e_bios; /* BIOS memory mapping. */
};

/* Helpers to calculate locations within a bios86 mapping. */
#define bios86_emulator_mem_gpbas(self)        bios86_mem_gpbas((self)->b86e_bios.b86_biosbase)
#define bios86_emulator_farptr(self, seg, off) bios86_farptr((self)->b86e_bios.b86_biosbase, seg, off)


/* >> bios86_emulator_init(3)
 * Same as `bios86_init(3)', but also set-up a vm86 emulator
 * that uses the pointed-to memory region, as well as  makes
 * use of native I/O instructions.
 * @return:  0: Success.
 * @return: -1: Failed to initialize (s.a. `errno'). */
#ifdef __KERNEL__
typedef __ATTR_NONNULL_T((1)) void
(LIBBIOS86_CC *PBIOS86_EMULATOR_INIT)(struct bios86_emulator *__restrict self);
#ifdef LIBBIOS86_WANT_PROTOTYPES
LIBBIOS86_DECL __ATTR_NONNULL((1)) void
(LIBBIOS86_CC bios86_emulator_init)(struct bios86_emulator *__restrict self);
#endif /* LIBBIOS86_WANT_PROTOTYPES */
#else /* __KERNEL__ */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) int
__NOTHROW_T(LIBBIOS86_CC *PBIOS86_EMULATOR_INIT)(struct bios86_emulator *__restrict self);
#ifdef LIBBIOS86_WANT_PROTOTYPES
LIBBIOS86_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW(LIBBIOS86_CC bios86_emulator_init)(struct bios86_emulator *__restrict self);
#endif /* LIBBIOS86_WANT_PROTOTYPES */
#endif /* !__KERNEL__ */

/* >> bios86_emulator_fini(3)
 * Finalize the BIOS buffer interface. */
typedef __NOBLOCK __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBBIOS86_CC *PBIOS86_EMULATOR_FINI)(struct bios86_emulator *__restrict self);
#ifdef LIBBIOS86_WANT_PROTOTYPES
LIBBIOS86_DECL __NOBLOCK __ATTR_NONNULL((1)) void
__NOTHROW(LIBBIOS86_CC bios86_emulator_fini)(struct bios86_emulator *__restrict self);
#endif /* LIBBIOS86_WANT_PROTOTYPES */


/* >> bios86_emulator_int(3)
 * Do an interrupt.
 * The caller must initialize `self->b86e_vm.vr_regs.*',
 * with the  exception of  `ESP', `SS',  `EIP' and  `CS'
 *
 * @return: true:  Success.
 * @return: false: Interrupt failed (illegal instruction / bad I/O, etc...) */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __BOOL
(LIBBIOS86_CC *PBIOS86_EMULATOR_INT)(struct bios86_emulator *__restrict self,
                                     __uint8_t intno);
#ifdef LIBBIOS86_WANT_PROTOTYPES
LIBBIOS86_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL LIBBIOS86_CC
bios86_emulator_int(struct bios86_emulator *__restrict self,
                    __uint8_t intno);
#endif /* LIBBIOS86_WANT_PROTOTYPES */



#ifdef __KERNEL__
/* Same as  above,  but  must be  used  if  `dbg_onstack()'
 * Also note that `bios86_init()' becomes  NOBLOCK+NOTHROW,
 * but may return `-1' if insufficient memory is available. */
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
struct bios86_for_debugger
#ifdef __cplusplus
    : bios86
#endif /* __cplusplus */
{
#ifndef __cplusplus
	__byte_t          *b86_biosbase;     /* [1..1][owned] BIOS base address */
#endif /* !__cplusplus */
	pagedir_pushval_t _b86_dbg_backup[BIOS86_SIZE / PAGESIZE]; /* Backup of page directory mappings. */
	physpage_t        _b86_dbg_rambase;  /* Physical base of ram for `01000-7ffff' */
};

struct bios86_emulator_for_debugger
#ifdef __cplusplus
    : bios86_emulator
#endif /* __cplusplus */
{
#ifndef __cplusplus
	vm86_state_t  b86e_vm;   /* VM86 controller. */
	struct bios86 b86e_bios; /* BIOS memory mapping. */
#endif /* !__cplusplus */
	pagedir_pushval_t _b86_dbg_backup[BIOS86_SIZE / PAGESIZE]; /* Backup of page directory mappings. */
	physpage_t        _b86_dbg_rambase;  /* Physical base of ram for `01000-7ffff' */
};


typedef __NOBLOCK __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) int
__NOTHROW_T(LIBBIOS86_CC *PBIOS86_INIT_FOR_DEBUGGER)(struct bios86_for_debugger *__restrict self);
typedef __NOBLOCK __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBBIOS86_CC *PBIOS86_FINI_FOR_DEBUGGER)(struct bios86_for_debugger *__restrict self);
typedef __NOBLOCK __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) int
__NOTHROW_T(LIBBIOS86_CC *PBIOS86_EMULATOR_INIT_FOR_DEBUGGER)(struct bios86_emulator_for_debugger *__restrict self);
typedef __NOBLOCK __ATTR_NONNULL_T((1)) void
__NOTHROW_T(LIBBIOS86_CC *PBIOS86_EMULATOR_FINI_FOR_DEBUGGER)(struct bios86_emulator_for_debugger *__restrict self);
#ifdef LIBBIOS86_WANT_PROTOTYPES
LIBBIOS86_DECL __NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW(LIBBIOS86_CC bios86_init_for_debugger)(struct bios86_for_debugger *__restrict self);
LIBBIOS86_DECL __NOBLOCK __ATTR_NONNULL((1)) void
__NOTHROW(LIBBIOS86_CC bios86_fini_for_debugger)(struct bios86_for_debugger *__restrict self);
LIBBIOS86_DECL __NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW(LIBBIOS86_CC bios86_emulator_init_for_debugger)(struct bios86_emulator_for_debugger *__restrict self);
LIBBIOS86_DECL __NOBLOCK __ATTR_NONNULL((1)) void
__NOTHROW(LIBBIOS86_CC bios86_emulator_fini_for_debugger)(struct bios86_emulator_for_debugger *__restrict self);
#endif /* LIBBIOS86_WANT_PROTOTYPES */
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
#endif /* __KERNEL__ */



__DECL_END
#endif /* __CC__ */

#endif /* !_LIBBIOS86_BIOS86_H */
