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
#ifndef _LIBPHYS_PHYS_H
#define _LIBPHYS_PHYS_H 1

#include "api.h"

/* Simple API access for low-level read/write of physical memory.
 * Note that in kernel-space, all of the necessary functions  are
 * instead provided by the core (in <kernel/mman/phys.h>) */

#ifdef __KERNEL__
#include <kernel/mman/phys.h>
#else /* __KERNEL__ */
#include <asm/os/mman.h> /* __MAP_FAILED */
#include <bits/types.h>
#include <kos/anno.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __physaddr_t_defined
#define __physaddr_t_defined
#ifdef __KERNEL__
#include <hybrid/__altint.h>
__HYBRID_ALTINT_TYPEDEF(__physaddr_t, physaddr_t, false); /* Physical memory address (== physpage_t * PAGESIZE) */
#else /* __KERNEL__ */
typedef __physaddr_t physaddr_t; /* Physical memory address (== physpage_t * PAGESIZE) */
#endif /* !__KERNEL__ */
#endif /* !__physaddr_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */



/************************************************************************/
/* Low-level physical memory read/write primitives.                     */
typedef __NOBLOCK __ATTR_WUNUSED_T __uint8_t __NOTHROW_T(LIBPHYS_CC *PPEEKPHYSB)(__PHYS physaddr_t addr);
typedef __NOBLOCK __ATTR_WUNUSED_T __uint16_t __NOTHROW_T(LIBPHYS_CC *PPEEKPHYSW)(/*aligned(2)*/ __PHYS physaddr_t addr);
typedef __NOBLOCK __ATTR_WUNUSED_T __uint32_t __NOTHROW_T(LIBPHYS_CC *PPEEKPHYSL)(/*aligned(4)*/ __PHYS physaddr_t addr);
typedef __NOBLOCK __ATTR_WUNUSED_T __uint16_t __NOTHROW_T(LIBPHYS_CC *PPEEKPHYSW_UNALIGNED)(__PHYS physaddr_t addr);
typedef __NOBLOCK __ATTR_WUNUSED_T __uint32_t __NOTHROW_T(LIBPHYS_CC *PPEEKPHYSL_UNALIGNED)(__PHYS physaddr_t addr);
typedef __NOBLOCK void __NOTHROW_T(LIBPHYS_CC *PPOKEPHYSB)(__PHYS physaddr_t addr, __uint8_t value);
typedef __NOBLOCK void __NOTHROW_T(LIBPHYS_CC *PPOKEPHYSW)(/*aligned(2)*/ __PHYS physaddr_t addr, __uint16_t value);
typedef __NOBLOCK void __NOTHROW_T(LIBPHYS_CC *PPOKEPHYSL)(/*aligned(4)*/ __PHYS physaddr_t addr, __uint32_t value);
typedef __NOBLOCK void __NOTHROW_T(LIBPHYS_CC *PPOKEPHYSW_UNALIGNED)(__PHYS physaddr_t addr, __uint16_t value);
typedef __NOBLOCK void __NOTHROW_T(LIBPHYS_CC *PPOKEPHYSL_UNALIGNED)(__PHYS physaddr_t addr, __uint32_t value);
#ifdef __UINT64_TYPE__
typedef __NOBLOCK __ATTR_WUNUSED_T __uint64_t __NOTHROW_T(LIBPHYS_CC *PPEEKPHYSQ)(/*aligned(8)*/ __PHYS physaddr_t addr);
typedef __NOBLOCK __ATTR_WUNUSED_T __uint64_t __NOTHROW_T(LIBPHYS_CC *PPEEKPHYSQ_UNALIGNED)(__PHYS physaddr_t addr);
typedef __NOBLOCK void __NOTHROW_T(LIBPHYS_CC *PPOKEPHYSQ)(/*aligned(8)*/ __PHYS physaddr_t addr, __uint64_t value);
typedef __NOBLOCK void __NOTHROW_T(LIBPHYS_CC *PPOKEPHYSQ_UNALIGNED)(__PHYS physaddr_t addr, __uint64_t value);
#endif /* __UINT64_TYPE__ */
#ifdef LIBPHYS_WANT_PROTOTYPES
LIBPHYS_DECL __NOBLOCK __ATTR_WUNUSED __uint8_t __NOTHROW(LIBPHYS_CC peekphysb)(__PHYS physaddr_t addr);
LIBPHYS_DECL __NOBLOCK __ATTR_WUNUSED __uint16_t __NOTHROW(LIBPHYS_CC peekphysw)(/*aligned(2)*/ __PHYS physaddr_t addr);
LIBPHYS_DECL __NOBLOCK __ATTR_WUNUSED __uint32_t __NOTHROW(LIBPHYS_CC peekphysl)(/*aligned(4)*/ __PHYS physaddr_t addr);
LIBPHYS_DECL __NOBLOCK __ATTR_WUNUSED __uint16_t __NOTHROW(LIBPHYS_CC peekphysw_unaligned)(__PHYS physaddr_t addr);
LIBPHYS_DECL __NOBLOCK __ATTR_WUNUSED __uint32_t __NOTHROW(LIBPHYS_CC peekphysl_unaligned)(__PHYS physaddr_t addr);
LIBPHYS_DECL __NOBLOCK void __NOTHROW(LIBPHYS_CC pokephysb)(__PHYS physaddr_t addr, __uint8_t value);
LIBPHYS_DECL __NOBLOCK void __NOTHROW(LIBPHYS_CC pokephysw)(/*aligned(2)*/ __PHYS physaddr_t addr, __uint16_t value);
LIBPHYS_DECL __NOBLOCK void __NOTHROW(LIBPHYS_CC pokephysl)(/*aligned(4)*/ __PHYS physaddr_t addr, __uint32_t value);
LIBPHYS_DECL __NOBLOCK void __NOTHROW(LIBPHYS_CC pokephysw_unaligned)(__PHYS physaddr_t addr, __uint16_t value);
LIBPHYS_DECL __NOBLOCK void __NOTHROW(LIBPHYS_CC pokephysl_unaligned)(__PHYS physaddr_t addr, __uint32_t value);
#ifdef __UINT64_TYPE__
LIBPHYS_DECL __NOBLOCK __ATTR_WUNUSED __uint64_t __NOTHROW(LIBPHYS_CC peekphysq)(/*aligned(8)*/ __PHYS physaddr_t addr);
LIBPHYS_DECL __NOBLOCK __ATTR_WUNUSED __uint64_t __NOTHROW(LIBPHYS_CC peekphysq_unaligned)(__PHYS physaddr_t addr);
LIBPHYS_DECL __NOBLOCK void __NOTHROW(LIBPHYS_CC pokephysq)(/*aligned(8)*/ __PHYS physaddr_t addr, __uint64_t value);
LIBPHYS_DECL __NOBLOCK void __NOTHROW(LIBPHYS_CC pokephysq_unaligned)(__PHYS physaddr_t addr, __uint64_t value);
#endif /* __UINT64_TYPE__ */
#endif /* LIBPHYS_WANT_PROTOTYPES */
/************************************************************************/



/************************************************************************/
/* Copy memory to/from/within the physical address space.               */
typedef void LIBPHYS_CC (*PCOPYFROMPHYS)(void *dst, __PHYS physaddr_t src, size_t num_bytes) __THROWS(E_SEGFAULT);
typedef void LIBPHYS_CC (*PCOPYTOPHYS)(__PHYS physaddr_t dst, void const *src, size_t num_bytes) __THROWS(E_SEGFAULT);
typedef __NOBLOCK void __NOTHROW_T(LIBPHYS_CC *PCOPYINPHYS)(__PHYS physaddr_t dst, __PHYS physaddr_t src, size_t num_bytes);
typedef __NOBLOCK void __NOTHROW_T(LIBPHYS_CC *PMEMSETPHYS)(__PHYS physaddr_t dst, int byte, size_t num_bytes);
#ifdef LIBPHYS_WANT_PROTOTYPES
LIBPHYS_DECL void LIBPHYS_CC copyfromphys(void *dst, __PHYS physaddr_t src, size_t num_bytes) __THROWS(E_SEGFAULT);
LIBPHYS_DECL void LIBPHYS_CC copytophys(__PHYS physaddr_t dst, void const *src, size_t num_bytes) __THROWS(E_SEGFAULT);
LIBPHYS_DECL __NOBLOCK void __NOTHROW(LIBPHYS_CC copyinphys)(__PHYS physaddr_t dst, __PHYS physaddr_t src, size_t num_bytes);
LIBPHYS_DECL __NOBLOCK void __NOTHROW(LIBPHYS_CC memsetphys)(__PHYS physaddr_t dst, int byte, size_t num_bytes);
#endif /* LIBPHYS_WANT_PROTOTYPES */
/************************************************************************/



/************************************************************************/
/* MMap at least `num_bytes' of physical memory starting at `addr', and
 * return the base-address of the resulting mapping, or MAP_FAILED upon
 * error (s.a. `errno' and `mmap(2)')
 * Memory is always mapped as `PROT_READ | PROT_WRITE'.
 *
 * The returned pointer should be unmapped as `munmapphys(return, num_bytes)'
 * The caller need not concern themself  with the alignment of `addr'  and/or
 * `num_bytes', as this function will automatically CEIL_ALIGN the  requested
 * address range  to contain  whole pages,  and later  adjusted the  returned
 * pointed to  account for  a potential  in-page alignment  offset of  `addr'
 * This adjustment will later be undone automatically by `munmapphys(3)'
 *
 * @return: * :         Base address of the newly created memory mapping.
 * @return: MAP_FAILED: Operation failed (s.a. `errno') */
typedef __NOBLOCK __ATTR_WUNUSED_T void *__NOTHROW_T(LIBPHYS_CC *PMMAPPHYS)(__PHYS physaddr_t addr, size_t num_bytes);
typedef __NOBLOCK void __NOTHROW_T(LIBPHYS_CC *PMUNMAPPHYS)(void *base, size_t num_bytes);
#ifdef LIBPHYS_WANT_PROTOTYPES
LIBPHYS_DECL __NOBLOCK __ATTR_WUNUSED void *__NOTHROW(LIBPHYS_CC mmapphys)(__PHYS physaddr_t addr, size_t num_bytes);
LIBPHYS_DECL __NOBLOCK void __NOTHROW(LIBPHYS_CC munmapphys)(void *base, size_t num_bytes);
#endif /* LIBPHYS_WANT_PROTOTYPES */
/************************************************************************/


/* Return a file descriptor for /dev/mem (or -1 with `errno' modified)
 * NOTE: Don't try to dup() or close() the file descriptor. - Just  use
 *       it as-is. It will be close()'d automatically once libphys gets
 *       unloaded. */
typedef __NOBLOCK __ATTR_PURE_T __ATTR_WUNUSED_T __fd_t __NOTHROW_T(LIBPHYS_CC *PGETDEVMEM)(void);
#ifdef LIBPHYS_WANT_PROTOTYPES
LIBPHYS_DECL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __fd_t __NOTHROW(LIBPHYS_CC getdevmem)(void);
#endif /* LIBPHYS_WANT_PROTOTYPES */

/* Sets the internally used /dev/mem file descriptor.
 * - The old internal /dev/mem file descriptor ISN'T closed
 * - The given `new_devmem_fd' descriptor ISN'T duped
 * - When  `new_devmem_fd == -1', the next use of getdevmem()
 *   or anything else that requires use of /dev/mem will once
 *   again try to open the device file
 * - When `new_devmem_fd != -1', the given descriptor will be
 *   closed when libphys is dlclose'd. */
typedef __NOBLOCK void __NOTHROW_T(LIBPHYS_CC *PSETDEVMEM)(__fd_t new_devmem_fd);
#ifdef LIBPHYS_WANT_PROTOTYPES
LIBPHYS_DECL __NOBLOCK void __NOTHROW(LIBPHYS_CC setdevmem)(__fd_t new_devmem_fd);
#endif /* LIBPHYS_WANT_PROTOTYPES */


#if !defined(MAP_FAILED) && defined(__MAP_FAILED)
#define MAP_FAILED __MAP_FAILED
#endif /* !MAP_FAILED && __MAP_FAILED */


__DECL_END
#endif /* __CC__ */
#endif /* !__KERNEL__ */

#endif /* !_LIBPHYS_PHYS_H */
