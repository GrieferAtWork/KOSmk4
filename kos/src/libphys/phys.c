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
#ifndef GUARD_LIBPHYS_PHYS_C
#define GUARD_LIBPHYS_PHYS_C 1

#include "api.h"
/**/

#include <hybrid/atomic.h>

#include <sys/mman.h>

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "phys.h"


DECL_BEGIN

PRIVATE fd_t dev_mem = -1;

/* This one's called by `-Wl,-fini=libphys_fini' */
INTERN void libphys_fini(void) {
	if (dev_mem >= 0)
		close(dev_mem);
}

PRIVATE void NOTHROW(CC openmem)(void) {
	fd_t dm;
	dm = open("/dev/mem", O_RDWR | O_CLOEXEC);
	if likely(dm >= 0) {
		if unlikely(!ATOMIC_CMPXCH(dev_mem, -1, dm))
			close(dm);
	}
}

/* Select the technique by which /dev/mem should be opened. */
#if 1
#define WITHMEM(op, on_error)      \
	do {                           \
		if unlikely(dev_mem == -1) \
			openmem();             \
		if (!(op)) {               \
			on_error;              \
		}                          \
	}	__WHILE0
#else
#define WITHMEM(op, on_error) \
	do {                      \
		if (!(op)) {          \
			openmem();        \
			if (!(op)) {      \
				on_error;     \
			}                 \
		}                     \
	}	__WHILE0
#endif







/************************************************************************/
/* Low-level physical memory read/write primitives.                     */
INTERN NOBLOCK WUNUSED uint8_t
NOTHROW(CC libphys_peekphysb)(PHYS physaddr_t addr) {
	uint8_t result;
	WITHMEM(pread64(dev_mem, &result, sizeof(result),
	                (pos64_t)addr) == sizeof(result),
	        result = 0);
	return result;
}

INTERN NOBLOCK WUNUSED uint16_t
NOTHROW(CC libphys_peekphysw)(/*aligned(2)*/ PHYS physaddr_t addr) {
	uint16_t result;
	WITHMEM(pread64(dev_mem, &result, sizeof(result),
	                (pos64_t)addr) == sizeof(result),
	        result = 0);
	return result;
}

INTERN NOBLOCK WUNUSED uint32_t
NOTHROW(CC libphys_peekphysl)(/*aligned(4)*/ PHYS physaddr_t addr) {
	uint32_t result;
	WITHMEM(pread64(dev_mem, &result, sizeof(result),
	                (pos64_t)addr) == sizeof(result),
	        result = 0);
	return result;
}

INTERN NOBLOCK WUNUSED uint64_t
NOTHROW(CC libphys_peekphysq)(/*aligned(8)*/ PHYS physaddr_t addr) {
	uint64_t result;
	WITHMEM(pread64(dev_mem, &result, sizeof(result),
	                (pos64_t)addr) == sizeof(result),
	        result = 0);
	return result;
}

DEFINE_INTERN_ALIAS(libphys_peekphysw_unaligned, libphys_peekphysw);
DEFINE_INTERN_ALIAS(libphys_peekphysl_unaligned, libphys_peekphysl);
DEFINE_INTERN_ALIAS(libphys_peekphysq_unaligned, libphys_peekphysq);


INTERN NOBLOCK void
NOTHROW(CC libphys_pokephysb)(PHYS physaddr_t addr, uint8_t value) {
	WITHMEM(pwrite64(dev_mem, &value, sizeof(value),
	                 (pos64_t)addr) == sizeof(value),
	        (void)0);
}

INTERN NOBLOCK void
NOTHROW(CC libphys_pokephysw)(/*aligned(2)*/ PHYS physaddr_t addr, uint16_t value) {
	WITHMEM(pwrite64(dev_mem, &value, sizeof(value),
	                 (pos64_t)addr) == sizeof(value),
	        (void)0);
}

INTERN NOBLOCK void
NOTHROW(CC libphys_pokephysl)(/*aligned(4)*/ PHYS physaddr_t addr, uint32_t value) {
	WITHMEM(pwrite64(dev_mem, &value, sizeof(value),
	                 (pos64_t)addr) == sizeof(value),
	        (void)0);
}

INTERN NOBLOCK void
NOTHROW(CC libphys_pokephysq)(/*aligned(8)*/ PHYS physaddr_t addr, uint64_t value) {
	WITHMEM(pwrite64(dev_mem, &value, sizeof(value),
	                 (pos64_t)addr) == sizeof(value),
	        (void)0);
}

DEFINE_INTERN_ALIAS(libphys_pokephysw_unaligned, libphys_pokephysw);
DEFINE_INTERN_ALIAS(libphys_pokephysl_unaligned, libphys_pokephysl);
DEFINE_INTERN_ALIAS(libphys_pokephysq_unaligned, libphys_pokephysq);
/************************************************************************/



/************************************************************************/
/* Copy memory to/from/within the physical address space.               */
INTERN void CC
libphys_copyfromphys(void *dst, PHYS physaddr_t src, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	WITHMEM(pread64(dev_mem, dst, num_bytes, (pos64_t)src),
	        memset(dst, 0, num_bytes));
}

PRIVATE ATTR_NOINLINE void CC
touch_all_pages(void const *src, size_t num_bytes) {
#ifdef __ARCH_PAGESIZE
	size_t pagesize = __ARCH_PAGESIZE;
#else /* __ARCH_PAGESIZE */
	size_t pagesize = getpagesize();
#endif /* !__ARCH_PAGESIZE */
	if unlikely(!num_bytes)
		return;
	for (;;) {
		/* Force a read from the pointed-to memory location, thus
		 * causing a SEGFAULT if any  of those pages are  faulty. */
		__asm__ __volatile__("" : : "r" (*(byte_t const *)src) : "memory");
		if (num_bytes <= pagesize)
			break;
		src = (byte_t const *)src + pagesize;
		num_bytes -= pagesize;
	}
}

INTERN void CC
libphys_copytophys(PHYS physaddr_t dst, void const *src, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	WITHMEM(pwrite64(dev_mem, src, num_bytes, (pos64_t)dst),
	        touch_all_pages(src, num_bytes));
}

INTERN NOBLOCK void
NOTHROW(CC libphys_copyinphys)(PHYS physaddr_t dst,
                               PHYS physaddr_t src,
                               size_t num_bytes) {
	void *temp;
	temp = libphys_mmapphys(src, num_bytes);
	if unlikely(temp == MAP_FAILED)
		return;
	WITHMEM(pwrite64(dev_mem, temp, num_bytes, (pos64_t)dst), (void)0);
	libphys_munmapphys(temp, num_bytes);
}

INTERN NOBLOCK void
NOTHROW(CC libphys_memsetphys)(PHYS physaddr_t dst,
                               int byte, size_t num_bytes) {
	void *temp;
	temp = libphys_mmapphys(dst, num_bytes);
	if unlikely(temp == MAP_FAILED)
		return;
	temp = memset(temp, byte, num_bytes);
	libphys_munmapphys(temp, num_bytes);
}
/************************************************************************/



/************************************************************************/
/* MMap at least `num_bytes' of physical memory starting at `addr', and
 * return the base-address of the resulting mapping, or MAP_FAILED upon
 * error (s.a. `errno' and `mmap(2)')
 * Memory is always mapped as `PROT_READ | PROT_WRITE'.
 *
 * The returned memory block should be unmapped as `munmapphys(return, num_bytes)'
 * The  caller  need not  concern  themself with  the  alignment of  `addr' and/or
 * `num_bytes', as  this  function  will automatically  CEIL_ALIGN  the  requested
 * address  range  to  contain  whole  pages,  and  later  adjusted  the  returned
 * pointed  to  account  for  a  potential  in-page  alignment  offset  of  `addr'
 * This adjustment will later be undone automatically by `munmapphys(3)'
 *
 * @return: * :         Base address of the newly created memory mapping.
 * @return: MAP_FAILED: Operation failed (s.a. `errno') */
INTERN NOBLOCK void *
NOTHROW(CC libphys_mmapphys)(PHYS physaddr_t addr, size_t num_bytes) {
	void *result;
	/* NOTE: As an  extension, KOS's  mmap(2) system  call automatically  does
	 *       all of the  in-page-offset alignment  when it has  been given  an
	 *       unaligned file-offset  or fixed  based address.  - It  will  only
	 *       error  out of  a fixed address  is given, and  its in-page offset
	 *       differs  from that used  by the file  position. However, since we
	 *       only pass a fixed file position, that case can never happen here. */
	WITHMEM((result = mmap64(NULL, num_bytes, PROT_READ | PROT_WRITE,
	                         MAP_SHARED | MAP_FILE, dev_mem,
	                         (pos64_t)addr)) != MAP_FAILED,
	        (result = MAP_FAILED));
	return result;
}

INTERN NOBLOCK void
NOTHROW(CC libphys_munmapphys)(void *base, size_t num_bytes) {
	/* For now, this is a simple wrapper, but in the future, a cache of
	 * recently used physical memory location may be added to  libphys,
	 * at which point this function would be used to mark cache entires
	 * as no-longer-in-use. */
	munmap(base, num_bytes);
}
/************************************************************************/




/* Library exports */
DEFINE_PUBLIC_ALIAS(peekphysb, libphys_peekphysb);
DEFINE_PUBLIC_ALIAS(peekphysw, libphys_peekphysw);
DEFINE_PUBLIC_ALIAS(peekphysl, libphys_peekphysl);
DEFINE_PUBLIC_ALIAS(peekphysw_unaligned, libphys_peekphysw_unaligned);
DEFINE_PUBLIC_ALIAS(peekphysl_unaligned, libphys_peekphysl_unaligned);
DEFINE_PUBLIC_ALIAS(pokephysb, libphys_pokephysb);
DEFINE_PUBLIC_ALIAS(pokephysw, libphys_pokephysw);
DEFINE_PUBLIC_ALIAS(pokephysl, libphys_pokephysl);
DEFINE_PUBLIC_ALIAS(pokephysw_unaligned, libphys_pokephysw_unaligned);
DEFINE_PUBLIC_ALIAS(pokephysl_unaligned, libphys_pokephysl_unaligned);
DEFINE_PUBLIC_ALIAS(peekphysq, libphys_peekphysq);
DEFINE_PUBLIC_ALIAS(peekphysq_unaligned, libphys_peekphysq_unaligned);
DEFINE_PUBLIC_ALIAS(pokephysq, libphys_pokephysq);
DEFINE_PUBLIC_ALIAS(pokephysq_unaligned, libphys_pokephysq_unaligned);
DEFINE_PUBLIC_ALIAS(copyfromphys, libphys_copyfromphys);
DEFINE_PUBLIC_ALIAS(copytophys, libphys_copytophys);
DEFINE_PUBLIC_ALIAS(copyinphys, libphys_copyinphys);
DEFINE_PUBLIC_ALIAS(memsetphys, libphys_memsetphys);
DEFINE_PUBLIC_ALIAS(mmapphys, libphys_mmapphys);
DEFINE_PUBLIC_ALIAS(munmapphys, libphys_munmapphys);

DECL_END

#endif /* !GUARD_LIBPHYS_PHYS_C */
