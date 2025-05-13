/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBPHYS_PHYS_H
#define GUARD_LIBPHYS_PHYS_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <stddef.h>
#include <stdint.h>

#include <libphys/phys.h>

#ifndef THROWS
#define THROWS __THROWS
#endif /* !THROWS */

#ifndef NOBLOCK
#define NOBLOCK __NOBLOCK
#endif /* !NOBLOCK */

#ifndef PHYS
#define PHYS __PHYS
#endif /* !PHYS */

DECL_BEGIN

/************************************************************************/
/* Low-level physical memory read/write primitives.                     */
INTDEF NOBLOCK WUNUSED uint8_t NOTHROW(CC libphys_peekphysb)(physaddr_t addr);
INTDEF NOBLOCK WUNUSED uint16_t NOTHROW(CC libphys_peekphysw)(/*aligned(2)*/ physaddr_t addr);
INTDEF NOBLOCK WUNUSED uint32_t NOTHROW(CC libphys_peekphysl)(/*aligned(4)*/ physaddr_t addr);
INTDEF NOBLOCK WUNUSED uint64_t NOTHROW(CC libphys_peekphysq)(/*aligned(8)*/ physaddr_t addr);
INTDEF NOBLOCK WUNUSED uint16_t NOTHROW(CC libphys_peekphysw_unaligned)(physaddr_t addr);
INTDEF NOBLOCK WUNUSED uint32_t NOTHROW(CC libphys_peekphysl_unaligned)(physaddr_t addr);
INTDEF NOBLOCK WUNUSED uint64_t NOTHROW(CC libphys_peekphysq_unaligned)(physaddr_t addr);
INTDEF NOBLOCK void NOTHROW(CC libphys_pokephysb)(physaddr_t addr, uint8_t value);
INTDEF NOBLOCK void NOTHROW(CC libphys_pokephysw)(/*aligned(2)*/ physaddr_t addr, uint16_t value);
INTDEF NOBLOCK void NOTHROW(CC libphys_pokephysl)(/*aligned(4)*/ physaddr_t addr, uint32_t value);
INTDEF NOBLOCK void NOTHROW(CC libphys_pokephysq)(/*aligned(8)*/ physaddr_t addr, uint64_t value);
INTDEF NOBLOCK void NOTHROW(CC libphys_pokephysw_unaligned)(physaddr_t addr, uint16_t value);
INTDEF NOBLOCK void NOTHROW(CC libphys_pokephysl_unaligned)(physaddr_t addr, uint32_t value);
INTDEF NOBLOCK void NOTHROW(CC libphys_pokephysq_unaligned)(physaddr_t addr, uint64_t value);
/************************************************************************/



/************************************************************************/
/* Copy memory to/from/within the physical address space.               */
INTDEF void CC libphys_copyfromphys(void *dst, physaddr_t src, size_t num_bytes) THROWS(E_SEGFAULT);
INTDEF void CC libphys_copytophys(physaddr_t dst, void const *src, size_t num_bytes) THROWS(E_SEGFAULT);
INTDEF NOBLOCK void NOTHROW(CC libphys_copyinphys)(physaddr_t dst, physaddr_t src, size_t num_bytes);
INTDEF NOBLOCK void NOTHROW(CC libphys_memsetphys)(physaddr_t dst, int byte, size_t num_bytes);
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
INTDEF NOBLOCK WUNUSED void *
NOTHROW(CC libphys_mmapphys)(physaddr_t addr, size_t num_bytes);
INTDEF NOBLOCK void
NOTHROW(CC libphys_munmapphys)(void *base, size_t num_bytes);
/************************************************************************/


/* Return a file descriptor for /dev/mem (or -1 with `errno' modified)
 * NOTE: Don't try to dup() or close() the file descriptor. - Just  use
 *       it as-is. It will be close()'d automatically once libphys gets
 *       unloaded. */
INTDEF NOBLOCK ATTR_PURE WUNUSED fd_t NOTHROW(CC libphys_getdevmem)(void);

/* Sets the internally used /dev/mem file descriptor.
 * - The old internal /dev/mem file descriptor ISN'T closed
 * - The given `new_devmem_fd' descriptor ISN'T duped
 * - When  `new_devmem_fd == -1', the next use of getdevmem()
 *   or anything else that requires use of /dev/mem will once
 *   again try to open the device file
 * - When `new_devmem_fd != -1', the given descriptor will be
 *   closed when libphys is dlclose'd. */
INTDEF NOBLOCK void NOTHROW(CC libphys_setdevmem)(fd_t new_devmem_fd);


DECL_END

#endif /* !GUARD_LIBPHYS_PHYS_H */
