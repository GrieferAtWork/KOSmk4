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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_VIO_C
#define GUARD_APPS_SYSTEM_TEST_TEST_VIO_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/host.h>
#include <hybrid/wordbits.h>

#include <kos/kernel/types.h>
#include <kos/types.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <libvio/vio.h>

#ifdef LIBVIO_CONFIG_ENABLED
DECL_BEGIN

PRIVATE void *libvio;
PRIVATE PVIO_CREATE vio_create;
PRIVATE PVIO_DESTROY vio_destroy;

PRIVATE u32 volatile num_vio_read  = 0;
PRIVATE u32 volatile num_vio_write = 0;
PRIVATE u32 volatile sink;

PRIVATE NONNULL((1)) u32 LIBVIO_CC
myvio_readl(struct vioargs *__restrict UNUSED(args),
            vio_addr_t UNUSED(addr)) {
	/* This function is called synchronously every time our VIO region is read from! */
	return num_vio_read++;
}

PRIVATE NONNULL((1)) void LIBVIO_CC
myvio_writel(struct vioargs *__restrict UNUSED(args),
             vio_addr_t UNUSED(addr),
             u32 UNUSED(value)) {
	/* This function is called synchronously every time our VIO region is written to! */
	num_vio_write++;
}

PRIVATE struct vio_ops const myvio_ops = {
	/* .vo_read  = */ VIO_CALLBACK_INIT_READ(NULL, NULL, &myvio_readl, NULL),
	/* .vo_write = */ VIO_CALLBACK_INIT_WRITE(NULL, NULL, &myvio_writel, NULL),
};


/* The problem:
 *     When a mapping exists for  BFFFF000-BFFFFFFF, and an access is  made
 *     at  an address that overlaps with the  far end of this address range
 *     (for  this purpose, perform  a 4-byte access  at `BFFFFFFF'), #PF is
 *     triggered with %cr2=C0000000, which in turn results in VIO emulation
 *     being triggered as well. However, vio will then find that the access
 *     is  actually  happening at  `BFFFFFFF', which  causes  it to  not be
 *     dispatched through vio (since only addresses >= C0000000 are  always
 *     handled via VIO). As a result,  the kernel will re-trigger the  same
 *     #PF  that originally  caused the fault,  and after a  whole bunch of
 *     recursion, the kernel will end up double-faulting.
 * Solution:
 *     In `kos/src/libviocore/arch/i386/viocore.c', all  of the  range-checking
 *     dispatch functions must  handle the  case where an  address is  accessed
 *     that is only partially overlapping with VIO. This should then be handled
 *     by performing both  a normal  memory access, as  well as  a VIO  access.
 *     In the event  of such an  access being  performed in the  context of  an
 *     atomic  operation,  the  kernel should  throw  an `E_SEGFAULT_UNALIGNED'
 *     exception.
 *
 * This test ensures that this handling is done correctly, alongside
 * some testing to see if VIO is working in general
 */
DEFINE_TEST(vio) {
	/* Use mmap() to find a 3-page large address range. */
	size_t ps = getpagesize();
	void *addr;
	volatile void *viobase;
	fd_t viofd;
	NEf(MAP_FAILED,
	    (addr = mmap(NULL, 3 * ps, PROT_READ | PROT_WRITE,
	                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)),
	    "errno = %u (%m)", errno);
	/* Fill the newly mapped memory with all 1-bits */
	memset(addr, 0xff, 3 * ps);

	/* Punch a hole into the middle of the 3 pages. */
	EQf(0, munmap((byte_t *)addr + ps, ps), "errno = %u (%m)", errno);

	/* Load the VIO library */
	ISnonnullf((libvio = dlopen(LIBVIO_LIBRARY_NAME, RTLD_LAZY | RTLD_GLOBAL)), "%s", dlerror());
	ISnonnullf((*(void **)&vio_create  = dlsym(libvio, "vio_create")), "%s", dlerror());
	ISnonnullf((*(void **)&vio_destroy = dlsym(libvio, "vio_destroy")), "%s", dlerror());

	/* Create the VIO controller. */
	ISposf((viofd = vio_create(&myvio_ops, NULL, ps, O_CLOEXEC)), "errno = %u (%m)", errno);

	/* Map our VIO region into the hole we punched above. */
	EQf((byte_t *)addr + ps,
	    (viobase = mmap((byte_t *)addr + ps, ps, PROT_READ | PROT_WRITE,
	                    MAP_PRIVATE | MAP_FILE | MAP_FIXED, viofd, 0)),
	    "errno = %u (%m)", errno);

	/* All right! Everything's been set up */
	EQ(0, num_vio_read);
	EQ(0, num_vio_write);

	/* First test: make sure that reading/writing is correctly dispatched */
	sink = ((u32 volatile *)viobase)[0];
	EQ(1, num_vio_read);
	EQ(0, num_vio_write);
	((u32 volatile *)viobase)[0] = sink;
	EQ(1, num_vio_read);
	EQ(1, num_vio_write);

	/* This  is where  it gets a  bit complicated, because  we're testing to
	 * ensure that  reading/writing from  an unaligned  memory address  near
	 * the top/bottom of the  VIO range (such that  part of the memory  that
	 * is being accessed isn't actually apart of VIO), still works correctly */
	{
		union {
			u8  v8[4];
			u32 v32;
		} value;
		/* This read should yield { 0xff, 0x11, 0x22, 0x33 },
		 * as  well as increment `num_vio_read' by exactly 1. */
		num_vio_read = BETOH32(0x11223344);
		value.v32 = *(u32 volatile *)((byte_t volatile *)viobase - 1);
		assertf(value.v8[0] == 0xff && value.v8[1] == 0x11 &&
		        value.v8[2] == 0x22 && value.v8[3] == 0x33,
		        "value = [%#" PRIx8 ",%#" PRIx8 ",%#" PRIx8 ",%#" PRIx8 "]",
		        value.v8[0], value.v8[1],
		        value.v8[2], value.v8[3]);
		assertf(num_vio_read == BETOH32(0x11223344) + 1,
		        "num_vio_read = %#" PRIx32 " (diff:%" PRId32 ")",
		        num_vio_read, num_vio_read - BETOH32(0x11223344));

		num_vio_read = BETOH32(0x11223344);
		value.v32 = *(u32 volatile *)((byte_t volatile *)viobase - 2);
		assertf(value.v8[0] == 0xff && value.v8[1] == 0xff &&
		        value.v8[2] == 0x11 && value.v8[3] == 0x22,
		        "value = [%#" PRIx8 ",%#" PRIx8 ",%#" PRIx8 ",%#" PRIx8 "]",
		        value.v8[0], value.v8[1],
		        value.v8[2], value.v8[3]);
		assertf(num_vio_read == BETOH32(0x11223344) + 1,
		        "num_vio_read = %#" PRIx32 " (diff:%" PRId32 ")",
		        num_vio_read, num_vio_read - BETOH32(0x11223344));

		num_vio_read = BETOH32(0x11223344);
		value.v32 = *(u32 volatile *)((byte_t volatile *)viobase - 3);
		assertf(value.v8[0] == 0xff && value.v8[1] == 0xff &&
		        value.v8[2] == 0xff && value.v8[3] == 0x11,
		        "value = %#" PRIx32, value);
		assertf(num_vio_read == BETOH32(0x11223344) + 1,
		        "num_vio_read = %#" PRIx32 " (diff:%" PRId32 ")",
		        num_vio_read, num_vio_read - BETOH32(0x11223344));

		num_vio_read = BETOH32(0x11223344);
		value.v32 = *(u32 volatile *)((byte_t volatile *)viobase - 4);
		assertf(value.v8[0] == 0xff && value.v8[1] == 0xff &&
		        value.v8[2] == 0xff && value.v8[3] == 0xff,
		        "value = %#" PRIx32 "", value);
		assertf(num_vio_read == BETOH32(0x11223344) + 0, /* Shouldn't have been incremented */
		        "num_vio_read = %#" PRIx32 " (diff:%" PRId32 ")",
		        num_vio_read, num_vio_read - BETOH32(0x11223344));

		/* Also assert the same kind of access behavior at the top of the VIO region. */
		num_vio_read = BETOH32(0x55667788);
		value.v32 = *(u32 volatile *)((byte_t volatile *)viobase + ps - 3);
		assertf(value.v8[0] == 0x66 && value.v8[1] == 0x77 &&
		        value.v8[2] == 0x88 && value.v8[3] == 0xff,
		        "value = [%#" PRIx8 ",%#" PRIx8 ",%#" PRIx8 ",%#" PRIx8 "]",
		        value.v8[0], value.v8[1],
		        value.v8[2], value.v8[3]);
		assertf(num_vio_read == BETOH32(0x55667788) + 1,
		        "num_vio_read = %#" PRIx32 " (diff:%" PRId32 ")",
		        num_vio_read, num_vio_read - BETOH32(0x55667788));

		num_vio_read = BETOH32(0x55667788);
		value.v32 = *(u32 volatile *)((byte_t volatile *)viobase + ps - 2);
		assertf(value.v8[0] == 0x77 && value.v8[1] == 0x88 &&
		        value.v8[2] == 0xff && value.v8[3] == 0xff,
		        "value = [%#" PRIx8 ",%#" PRIx8 ",%#" PRIx8 ",%#" PRIx8 "]",
		        value.v8[0], value.v8[1],
		        value.v8[2], value.v8[3]);
		assertf(num_vio_read == BETOH32(0x55667788) + 1,
		        "num_vio_read = %#" PRIx32 " (diff:%" PRId32 ")",
		        num_vio_read, num_vio_read - BETOH32(0x55667788));

		num_vio_read = BETOH32(0x55667788);
		value.v32 = *(u32 volatile *)((byte_t volatile *)viobase + ps - 1);
		assertf(value.v8[0] == 0x88 && value.v8[1] == 0xff &&
		        value.v8[2] == 0xff && value.v8[3] == 0xff,
		        "value = [%#" PRIx8 ",%#" PRIx8 ",%#" PRIx8 ",%#" PRIx8 "]",
		        value.v8[0], value.v8[1],
		        value.v8[2], value.v8[3]);
		assertf(num_vio_read == BETOH32(0x55667788) + 1,
		        "num_vio_read = %#" PRIx32 " (diff:%" PRId32 ")",
		        num_vio_read, num_vio_read - BETOH32(0x55667788));

		num_vio_read = BETOH32(0x55667788);
		value.v32 = *(u32 volatile *)((byte_t volatile *)viobase + ps - 0);
		assertf(value.v8[0] == 0xff && value.v8[1] == 0xff &&
		        value.v8[2] == 0xff && value.v8[3] == 0xff,
		        "value = [%#" PRIx8 ",%#" PRIx8 ",%#" PRIx8 ",%#" PRIx8 "]",
		        value.v8[0], value.v8[1],
		        value.v8[2], value.v8[3]);
		assertf(num_vio_read == BETOH32(0x55667788) + 0, /* Shouldn't have been incremented */
		        "num_vio_read = %#" PRIx32 " (diff:%" PRId32 ")",
		        num_vio_read, num_vio_read - BETOH32(0x55667788));
	}

	/* Cleanup... */
	EQ(0, vio_destroy(viofd));
	EQ(0, dlclose(libvio));
	EQ(0, munmap(addr, 3 * ps));
}


DECL_END
#endif /* LIBVIO_CONFIG_ENABLED */

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_VIO_C */
