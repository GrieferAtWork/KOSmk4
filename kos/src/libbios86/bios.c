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
#ifndef GUARD_LIBBIOS86_BIOS_C
#define GUARD_LIBBIOS86_BIOS_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <kos/except.h>
#include <kos/kernel/types.h>
#include <kos/types.h>
#include <sys/io.h>
#include <sys/mman.h>

#include <assert.h>
#include <stddef.h>

#include <libbios86/bios.h>
#include <libphys/phys.h>
#include <libvm86/emulator.h>

#include "bios.h"

#ifdef __KERNEL__
#include <debugger/config.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/mman.h>      /* mman_kernel */
#include <kernel/mman/kram.h> /* mman_unmap_kram_and_kfree */
#include <kernel/mman/map.h>  /* mman_map */
#include <kernel/paging.h>
#endif /* __KERNEL__ */

DECL_BEGIN

#ifndef __port_t_defined
#define __port_t_defined
typedef __port_t port_t;
#endif /* !__port_t_defined */


/* >> bios86_init(3)
 * Initialize a BIOS interrupt emulator `self'
 * @return:  0: Success.
 * @return: -1: Failed to initialize (s.a. `errno'). */
DEFINE_PUBLIC_ALIAS(bios86_init, libbios86_init);
#ifdef __KERNEL__
INTERN NONNULL((1)) void CC
libbios86_init(struct bios86 *__restrict self)
#else /* __KERNEL__ */
INTERN WUNUSED NONNULL((1)) int
NOTHROW(CC libbios86_init)(struct bios86 *__restrict self)
#endif /* !__KERNEL__ */
{
	/* Map relevant memory. */
#ifdef __KERNEL__
	self->_b86_unmapcookie = mman_unmap_kram_cookie_alloc();
	TRY {
		/* Use a regular memory mapping. */
		self->b86_biosbase = (byte_t *)mman_map(/* self:        */ &mman_kernel,
		                                        /* hint:        */ MHINT_GETADDR(KERNEL_MHINT_DEVICE),
		                                        /* num_bytes:   */ BIOS86_SIZE,
		                                        /* prot:        */ PROT_READ | PROT_WRITE | PROT_EXEC | PROT_SHARED,
		                                        /* flags:       */ MHINT_GETMODE(KERNEL_MHINT_DEVICE),
		                                        /* file:        */ &mfile_phys,
		                                        /* file_fspath: */ NULL,
		                                        /* file_fsname: */ NULL,
		                                        /* file_pos:    */ (pos_t)0);
	} EXCEPT {
		mman_unmap_kram_cookie_free(self->_b86_unmapcookie);
		RETHROW();
	}
	TRY {
		/* Map anonymous memory into the RAM area. */
		mman_map(/* self:        */ &mman_kernel,
		         /* hint:        */ self->b86_biosbase + 0x01000,
		         /* num_bytes:   */ 0x80000 - 0x01000,
		         /* prot:        */ PROT_READ | PROT_WRITE | PROT_EXEC | PROT_SHARED,
		         /* flags:       */ MAP_FIXED | MHINT_GETMODE(KERNEL_MHINT_DEVICE),
		         /* file:        */ &mfile_zero);
	} EXCEPT {
		mman_unmap_kram_and_kfree(self->b86_biosbase, BIOS86_SIZE,
		                          self->_b86_unmapcookie);
		RETHROW();
	}
#else /* __KERNEL__ */
	fd_t devmem = getdevmem();
	if (devmem < 0)
		return -1;
	self->b86_biosbase = (byte_t *)mmap(NULL, BIOS86_SIZE,
	                                    PROT_READ | PROT_WRITE | PROT_EXEC,
	                                    MAP_SHARED | MAP_FILE,
	                                    devmem, 0);
	if (self->b86_biosbase == (byte_t *)MAP_FAILED)
		return -1;
	if (mmap(self->b86_biosbase + 0x01000, 0x80000 - 0x01000,
	         PROT_READ | PROT_WRITE | PROT_EXEC,
	         MAP_PRIVATE | MAP_ANON, -1, 0) == MAP_FAILED) {
		munmap(self->b86_biosbase, BIOS86_SIZE);
		return -1;
	}
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
	return 0;
#endif /* !__KERNEL__ */
}

/* >> bios86_fini(3)
 * Finalize the BIOS buffer interface. */
DEFINE_PUBLIC_ALIAS(bios86_fini, libbios86_fini);
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(CC libbios86_fini)(struct bios86 *__restrict self) {
#ifdef __KERNEL__
	mman_unmap_kram_and_kfree(self->b86_biosbase, BIOS86_SIZE,
	                          self->_b86_unmapcookie);
#else /* __KERNEL__ */
	munmap(self->b86_biosbase, BIOS86_SIZE);
#endif /* !__KERNEL__ */
	self->b86_biosbase = (byte_t *)MAP_FAILED;
}


PRIVATE ATTR_PURE WUNUSED NONNULL((1)) void *LIBVM86_TRANSLATE_CC
bios86_vm_translate(vm86_state_t *__restrict self, void *ptr) {
	struct bios86_emulator *me;
	void *result;
	me     = container_of(self, struct bios86_emulator, b86e_vm);
	result = me->b86e_bios.b86_biosbase + (uintptr_t)ptr;
	return result;
}

PRIVATE NONNULL((1)) int LIBVM86_CC
bios86_vm_io(vm86_state_t *__restrict UNUSED(self),
             uint16_t port, unsigned int action, void *data) {
	int result = VM86_SUCCESS;
	switch (action) {
	case VM86_HANDLE_IO_INB: *(uint8_t *)data = inb((port_t)port); break;
	case VM86_HANDLE_IO_INW: *(uint16_t *)data = inw((port_t)port); break;
	case VM86_HANDLE_IO_INL: *(uint32_t *)data = inl((port_t)port); break;
	case VM86_HANDLE_IO_OUTB: outb((port_t)port, *(uint8_t const *)data); break;
	case VM86_HANDLE_IO_OUTW: outw((port_t)port, *(uint16_t const *)data); break;
	case VM86_HANDLE_IO_OUTL: outl((port_t)port, *(uint32_t const *)data); break;
	default: result = VM86_BADPORT; break;
	}
	return result;
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC bios86_emulator_init_common)(struct bios86_emulator *__restrict self) {
	self->b86e_vm.vr_trans = &bios86_vm_translate;
	self->b86e_vm.vr_io    = &bios86_vm_io;
	self->b86e_vm.vr_intr  = NULL;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC bios86_emulator_fini_common)(struct bios86_emulator *__restrict self) {
	(void)self;
	COMPILER_IMPURE();
	/* Nothing (for now) */
}



/* >> bios86_emulator_init(3)
 * Same as `bios86_init(3)', but also set-up a vm86 emulator
 * that uses the pointed-to memory region, as well as  makes
 * use of native I/O instructions.
 * @return:  0: Success.
 * @return: -1: Failed to initialize (s.a. `errno'). */
DEFINE_PUBLIC_ALIAS(bios86_emulator_init, libbios86_emulator_init);
#ifdef __KERNEL__
INTERN NONNULL((1)) void CC
libbios86_emulator_init(struct bios86_emulator *__restrict self)
#else /* __KERNEL__ */
INTERN WUNUSED NONNULL((1)) int
NOTHROW(CC libbios86_emulator_init)(struct bios86_emulator *__restrict self)
#endif /* !__KERNEL__ */
{
#ifdef __KERNEL__
	libbios86_init(&self->b86e_bios);
	bios86_emulator_init_common(self);
#else /* __KERNEL__ */
	int result;
	result = libbios86_init(&self->b86e_bios);
	if likely(result == 0)
		bios86_emulator_init_common(self);
	return result;
#endif /* !__KERNEL__ */
}

/* >> bios86_emulator_fini(3)
 * Finalize the BIOS buffer interface. */
DEFINE_PUBLIC_ALIAS(bios86_emulator_fini, libbios86_emulator_fini);
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(CC libbios86_emulator_fini)(struct bios86_emulator *__restrict self) {
	bios86_emulator_fini_common(self);
	libbios86_fini(&self->b86e_bios);
}



/* >> bios86_emulator_int(3)
 * Do an interrupt.
 * The caller must initialize `self->b86e_vm.vr_regs.*',
 * with the  exception of  `ESP', `SS',  `EIP' and  `CS'
 *
 * @return: true:  Success.
 * @return: false: Interrupt failed (illegal instruction / bad I/O, etc...) */
DEFINE_PUBLIC_ALIAS(bios86_emulator_int, libbios86_emulator_int);
INTERN WUNUSED NONNULL((1)) bool CC
libbios86_emulator_int(struct bios86_emulator *__restrict self,
                       uint8_t intno) {
	int error;
	assertf(self->b86e_vm.vr_trans == &bios86_vm_translate &&
	        self->b86e_vm.vr_io == &bios86_vm_io &&
	        self->b86e_vm.vr_intr == NULL,
	        "Emulator not initialized");

	/* Fill in register state */
	self->b86e_vm.vr_regs.vr_esp = BIOS86_MEM_SP & 0xffff;
	self->b86e_vm.vr_regs.vr_ss  = (BIOS86_MEM_SP & 0xf0000) >> 4;
	self->b86e_vm.vr_regs.vr_eip = 0xffff;
	self->b86e_vm.vr_regs.vr_cs  = 0xffff;

	/* Generate a software interrupt */
	error = vm86_intr(&self->b86e_vm, intno);
	if (error != VM86_SUCCESS)
		return false;

	/* Execute VM86 code. */
	error = vm86_exec(&self->b86e_vm);
	return error == VM86_SUCCESS ||
	       error == VM86_STOPPED;
}





#ifdef __KERNEL__
/* Same as  above,  but  must be  used  if  `dbg_onstack()'
 * Also note that `bios86_init()' becomes  NOBLOCK+NOTHROW,
 * but may return `-1' if insufficient memory is available. */
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#define BIOS86_DBG_BIOSBASE (byte_t *)KERNEL_CORE_BASE

DEFINE_PUBLIC_ALIAS(bios86_init_for_debugger, libbios86_init_for_debugger);
INTERN NOBLOCK WUNUSED NONNULL((1)) int
NOTHROW(CC libbios86_init_for_debugger)(struct bios86_for_debugger *__restrict self) {
	unsigned int i;
	byte_t *virt;
	physaddr_t phys;
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (!pagedir_prepare(BIOS86_DBG_BIOSBASE, BIOS86_SIZE))
		return -1;
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	self->_b86_dbg_rambase = page_malloc((0x80000 - 0x01000) / PAGESIZE);
	if (self->_b86_dbg_rambase == PHYSPAGE_INVALID) {
		pagedir_kernelunprepare(BIOS86_DBG_BIOSBASE, BIOS86_SIZE);
		return -1;
	}
	self->b86_biosbase = BIOS86_DBG_BIOSBASE;
	for (i = 0, virt = self->b86_biosbase, phys = 0; i < BIOS86_SIZE / PAGESIZE; ++i) {
		self->_b86_dbg_backup[i] = pagedir_push_mapone(virt, phys,
		                                               PAGEDIR_PROT_READ |
		                                               PAGEDIR_PROT_WRITE |
		                                               PAGEDIR_PROT_EXEC);
		phys += PAGESIZE;
		virt += PAGESIZE;
	}
	pagedir_map(BIOS86_DBG_BIOSBASE + 0x01000, 0x80000 - 0x01000,
	            physpage2addr(self->_b86_dbg_rambase),
	            PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_EXEC);
	pagedir_syncall();
	return 0;
}

DEFINE_PUBLIC_ALIAS(bios86_fini_for_debugger, libbios86_fini_for_debugger);
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(CC libbios86_fini_for_debugger)(struct bios86_for_debugger *__restrict self) {
	unsigned int i;
	byte_t *virt;
	for (i = 0, virt = BIOS86_DBG_BIOSBASE; i < BIOS86_SIZE / PAGESIZE; ++i) {
		pagedir_pop_mapone(virt, self->_b86_dbg_backup[i]);
		virt += PAGESIZE;
	}
	page_free(self->_b86_dbg_rambase, (0x80000 - 0x01000) / PAGESIZE);
	pagedir_kernelunprepare(BIOS86_DBG_BIOSBASE, BIOS86_SIZE);
	pagedir_syncall();
}

DEFINE_PUBLIC_ALIAS(bios86_emulator_init_for_debugger, libbios86_emulator_init_for_debugger);
INTERN NOBLOCK WUNUSED NONNULL((1)) int
NOTHROW(CC libbios86_emulator_init_for_debugger)(struct bios86_emulator_for_debugger *__restrict self) {
	int result;
	result = libbios86_init_for_debugger((struct bios86_for_debugger *)&self->b86e_bios);
	if likely(result == 0)
		bios86_emulator_init_common(self);
	return result;
}

DEFINE_PUBLIC_ALIAS(bios86_emulator_fini_for_debugger, libbios86_emulator_fini_for_debugger);
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(CC libbios86_emulator_fini_for_debugger)(struct bios86_emulator_for_debugger *__restrict self) {
	bios86_emulator_fini_common(self);
	libbios86_fini_for_debugger((struct bios86_for_debugger *)&self->b86e_bios);
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
#endif /* __KERNEL__ */






DECL_END

#endif /* !GUARD_LIBBIOS86_BIOS_C */
