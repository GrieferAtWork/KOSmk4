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
#ifndef GUARD_LIBSVGADRV_CS_VMWARE_C
#define GUARD_LIBSVGADRV_CS_VMWARE_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _KOS_ALTERATIONS_SOURCE 1

#include "api.h"
/**/

#ifdef CONFIG_HAVE_LIBSVGADRV_CHIPSET_VMWARE
#include <hybrid/align.h>
#include <hybrid/bit.h>
#include <hybrid/minmax.h>
#include <hybrid/sequence/list.h>
#include <hybrid/unaligned.h>

#include <hw/bus/pci.h>
#include <hw/video/vmware.h>
#include <kos/except.h>
#include <kos/kernel/printk.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <libpciaccess/pciaccess.h>
#include <libsvgadrv/chipsets/vmware.h>

#include "cs-vga.h"
#include "cs-vmware.h"

#ifdef __KERNEL__
#include <kernel/mman.h>      /* mman_kernel */
#include <kernel/mman/kram.h> /* mman_unmap_kram_and_kfree */
#include <kernel/mman/map.h>  /* mman_map */
#include <sched/task.h>
#else /* __KERNEL__ */
#include <dlfcn.h>
#include <pthread.h>
#endif /* !__KERNEL__ */

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

PRIVATE NONNULL((1)) void CC
vmware_fifo_handle_full(struct vmware_chipset *__restrict self) {
	(void)self;
#ifdef __KERNEL__
	task_tryyield_or_pause();
#else /* __KERNEL__ */
	pthread_yield();
#endif /* !__KERNEL__ */
}

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *CC
vmware_fifo_reserve(struct vmware_chipset *__restrict self, size_t n_bytes) {
	/* Derived from reference impl of "SVGA_FIFOReserve" */
	uint32_t max = self->vw_fifo_max;
	uint32_t min = self->vw_fifo_min;
	uint32_t next_cmd = self->vm_fifo[SVGA_FIFO_NEXT_CMD];
	assert((n_bytes & 3) == 0);
	assert(n_bytes <= (VMWARE_MAX_FIFO_COMMAND_WORDS * 4));
	for (;;) {
		uint32_t stop = self->vm_fifo[SVGA_FIFO_STOP];
		if (next_cmd >= stop) {
			if (next_cmd + n_bytes < max ||
			    (next_cmd + n_bytes == max && stop > min)) {
do_reserveInPlace:
				if (n_bytes <= 4)
					goto do_return_next_cmd;
				if (vm_fifo_hascap(self, SVGA_FIFO_CAP_RESERVE)) {
					self->vm_fifo_debounce_inuse      = false;
					self->vm_fifo[SVGA_FIFO_RESERVED] = n_bytes;
do_return_next_cmd:
					return (uint32_t *)((uint8_t *)self->vm_fifo + next_cmd);
				}
do_needBounce:
				self->vm_fifo_debounce_inuse = true;
				return self->vm_fifo_debounce;
			} else if ((max - next_cmd) + (stop - min) <= n_bytes) {
				vmware_fifo_handle_full(self);
			} else {
				goto do_needBounce;
			}
		} else {
			if (next_cmd + n_bytes < stop) {
				goto do_reserveInPlace;
			} else {
				vmware_fifo_handle_full(self);
			}
		}
	}
}

PRIVATE NONNULL((1)) void CC
vmware_fifo_commit(struct vmware_chipset *__restrict self, size_t n_bytes) {
	/* Derived from reference impl of "SVGA_FIFOCommit" */
	uint32_t next_cmd = self->vm_fifo[SVGA_FIFO_NEXT_CMD];
	uint32_t max = self->vw_fifo_max;
	uint32_t min = self->vw_fifo_min;
	assert((n_bytes & 3) == 0);
	assert(n_bytes <= (VMWARE_MAX_FIFO_COMMAND_WORDS * 4));
	if (self->vm_fifo_debounce_inuse) {
		uint32_t *buffer = self->vm_fifo_debounce;
		if (vm_fifo_hascap(self, SVGA_FIFO_CAP_RESERVE)) {
			uint32_t chunk_bytes = MIN(n_bytes, max - next_cmd);
			self->vm_fifo[SVGA_FIFO_RESERVED] = n_bytes;
			memcpyl((uint8_t *)self->vm_fifo + next_cmd, buffer, chunk_bytes / 4);
			memcpyl((uint8_t *)self->vm_fifo + min, buffer + chunk_bytes, (n_bytes - chunk_bytes) / 4);
		} else {
			while (n_bytes > 0) {
				self->vm_fifo[next_cmd / 4] = *buffer++;
				next_cmd += 4;
				if (next_cmd >= max)
					next_cmd = min;
				self->vm_fifo[SVGA_FIFO_NEXT_CMD] = next_cmd;
				n_bytes -= 4;
			}
		}
	}
	if (!self->vm_fifo_debounce_inuse || vm_fifo_hascap(self, SVGA_FIFO_CAP_RESERVE)) {
		next_cmd += n_bytes;
		if (next_cmd >= max)
			next_cmd -= max - min;
		self->vm_fifo[SVGA_FIFO_NEXT_CMD] = next_cmd;
	}
	if (vm_fifo_hascap(self, SVGA_FIFO_CAP_RESERVE))
		self->vm_fifo[SVGA_FIFO_RESERVED] = 0;
}


#define vmware_fifo_commit_cmd(self, n_words) \
	vmware_fifo_commit(self, 4 + ((n_words) * 4))
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *CC
vmware_fifo_reserve_cmd(struct vmware_chipset *__restrict self,
                        uint32_t cmd, size_t n_words) {
	uint32_t *result = vmware_fifo_reserve(self, 4 + (n_words * 4));
	*result++ = cmd;
	return result;
}









PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC vmware_v_fini)(struct svga_chipset *__restrict self) {
	struct vmware_chipset *me = (struct vmware_chipset *)self;
	(void)me;
#ifdef __KERNEL__
	mman_unmap_kram_and_kfree((void *)me->vm_fifo, me->vw_fifosize,
	                          me->vm_fifo_unmap_cookie);
#else /* __KERNEL__ */
	(*me->vw_munmapphys)((void *)me->vm_fifo, me->vw_fifosize);
	if (me->vw_libpciaccess)
		dlclose(me->vw_libpciaccess);
#endif /* !__KERNEL__ */
}


struct vmware_videomode {
	uint16_t vm_resx;
	uint16_t vm_resy;
};

PRIVATE struct vmware_videomode const vmware_videomodes[] = {
	/* Supported video modes (resolutions are stolen from what VESA reports under QEMU) */
	{ 320, 200 },
	{ 640, 400 },
	{ 800, 600 },
	{ 1024, 768 },
	{ 1152, 864 },
	{ 1280, 1024 },
	{ 1280, 720 },
	{ 1280, 768 },
	{ 1280, 800 },
	{ 1280, 960 },
	{ 1400, 1050 },
	{ 1440, 900 },
	{ 1600, 1200 },
	{ 1600, 900 },
	{ 1680, 1050 },
	{ 1920, 1080 },
	{ 1920, 1200 },
	{ 2560, 1440 },
	{ 2560, 1600 },
};



PRIVATE WUNUSED NONNULL((1, 2, 3)) bool CC
vmware_v_getmode(struct svga_chipset *__restrict self,
                 struct svga_modeinfo *__restrict _result,
                 uintptr_t *__restrict p_index)
		THROWS(E_IOERROR) {
	uint32_t old_enable, old_config_done;
	uint32_t old_width, old_height, old_bpp;
	uint32_t rmask, gmask, bmask;
	struct vmware_chipset *me = (struct vmware_chipset *)self;
	struct vmware_modeinfo *result = (struct vmware_modeinfo *)_result;
	struct vmware_videomode const *vm;
next:
	if (*p_index >= lengthof(vmware_videomodes)) {
		/* Enumerate standard VGA modes. */
		bool ok;
		result->vmi_modeid = (uint8_t)-1;
		*p_index -= lengthof(vmware_videomodes);
		ok = vga_v_getmode(self, result, p_index);
		*p_index += lengthof(vmware_videomodes);
		return ok;
	}
	vm = &vmware_videomodes[*p_index];
	++*p_index;

	/* Check if this mode is supported. */
	if (vm->vm_resx > me->vw_maxresx)
		goto next;
	if (vm->vm_resy > me->vw_maxresy)
		goto next;

	result->vmi_modeid         = *p_index;
	result->smi_flags          = SVGA_MODEINFO_F_LFB;
	result->smi_resx           = vm->vm_resx;
	result->smi_resy           = vm->vm_resy;
	result->smi_bits_per_pixel = me->vw_hbpp;
	result->smi_scanline       = CEIL_ALIGN(vm->vm_resx * 4, 64);

	/* Figure out scanline and such... */
	old_enable      = vm_getreg(me, SVGA_REG_ENABLE);
	old_config_done = vm_getreg(me, SVGA_REG_CONFIG_DONE);
	old_width       = vm_getreg(me, SVGA_REG_WIDTH);
	old_height      = vm_getreg(me, SVGA_REG_HEIGHT);
	old_bpp         = vm_getreg(me, SVGA_REG_BPP);
	vm_setreg(me, SVGA_REG_CONFIG_DONE, 0);
	vm_setreg(me, SVGA_REG_ENABLE, SVGA_REG_ENABLE_DISABLE);
	vm_setreg(me, SVGA_REG_WIDTH, vm->vm_resx);
	vm_setreg(me, SVGA_REG_HEIGHT, vm->vm_resy);
	if (me->vw_caps & SVGA_CAP_8BIT_EMULATION)
		vm_setreg(me, SVGA_REG_BPP, me->vw_hbpp);

	result->smi_lfb = me->vw_fbstart + vm_getreg(me, SVGA_REG_FB_OFFSET);
	result->smi_scanline = vm_getreg(me, SVGA_REG_BYTES_PER_LINE);
	result->smi_colorbits = vm_getreg(me, SVGA_REG_DEPTH);
	rmask = vm_getreg(me, SVGA_REG_RED_MASK);
	gmask = vm_getreg(me, SVGA_REG_GREEN_MASK);
	bmask = vm_getreg(me, SVGA_REG_BLUE_MASK);
	result->smi_rshift = rmask ? CTZ(rmask) : 0;
	result->smi_rbits  = POPCOUNT(rmask);
	result->smi_gshift = gmask ? CTZ(gmask) : 0;
	result->smi_gbits  = POPCOUNT(gmask);
	result->smi_bshift = bmask ? CTZ(bmask) : 0;
	result->smi_bbits  = POPCOUNT(bmask);

	/* Restore old registers */
	if (me->vw_caps & SVGA_CAP_8BIT_EMULATION)
		vm_setreg(me, SVGA_REG_BPP, old_bpp);
	vm_setreg(me, SVGA_REG_HEIGHT, old_height);
	vm_setreg(me, SVGA_REG_WIDTH, old_width);
	vm_setreg(me, SVGA_REG_ENABLE, old_enable);
	vm_setreg(me, SVGA_REG_CONFIG_DONE, old_config_done);
	return true;
}

PRIVATE NONNULL((1, 2)) void CC
vmware_v_setmode(struct svga_chipset *__restrict self,
                 struct svga_modeinfo const *__restrict _mode) {
	uint32_t final_scanline;
	uint32_t rmask, gmask, bmask;
	uint32_t want_rmask, want_gmask, want_bmask;
	struct vmware_chipset *me = (struct vmware_chipset *)self;
	struct vmware_modeinfo const *mode = (struct vmware_modeinfo const *)_mode;

	/* Support for standard VGA modes. */
	if (mode->vmi_modeid >= lengthof(vmware_videomodes)) {
		vm_setreg(me, SVGA_REG_ENABLE, SVGA_REG_ENABLE_DISABLE);
		vga_v_setmode(self, mode);
		return;
	}

	/* SetMode */
	vm_setreg(me, SVGA_REG_CONFIG_DONE, 0);
	vm_setreg(me, SVGA_REG_WIDTH, mode->smi_resx);
	vm_setreg(me, SVGA_REG_HEIGHT, mode->smi_resy);
	if (me->vw_caps & SVGA_CAP_8BIT_EMULATION)
		vm_setreg(me, SVGA_REG_BPP, mode->smi_bits_per_pixel);

	/* Read scanline config and verify it. */
	final_scanline = vm_getreg(me, SVGA_REG_BYTES_PER_LINE);
	if unlikely(final_scanline != mode->smi_scanline) {
		printk(KERN_ERR "[vmware] Final scanline=%" PRIu32 " differs from cached scanline=%" PRIu32 "\n",
		       final_scanline, mode->smi_scanline);
	}

	/* Read color mask config and verify it. */
	rmask = vm_getreg(me, SVGA_REG_RED_MASK);
	gmask = vm_getreg(me, SVGA_REG_GREEN_MASK);
	bmask = vm_getreg(me, SVGA_REG_BLUE_MASK);
	want_rmask = (((uint32_t)1 << mode->smi_rbits) - 1) << mode->smi_rshift;
	want_gmask = (((uint32_t)1 << mode->smi_gbits) - 1) << mode->smi_gshift;
	want_bmask = (((uint32_t)1 << mode->smi_bbits) - 1) << mode->smi_bshift;
	if (rmask != want_rmask)
		printk(KERN_ERR "[vmware] Final rmask=%#.8" PRIx32 " differs from cached rmask=%#.8" PRIx32 "\n", rmask, want_rmask);
	if (gmask != want_gmask)
		printk(KERN_ERR "[vmware] Final gmask=%#.8" PRIx32 " differs from cached gmask=%#.8" PRIx32 "\n", gmask, want_gmask);
	if (bmask != want_bmask)
		printk(KERN_ERR "[vmware] Final bmask=%#.8" PRIx32 " differs from cached bmask=%#.8" PRIx32 "\n", bmask, want_bmask);

	/* Initialize the command FIFO */
	me->vw_fifo_caps = SVGA_FIFO_CAP_NONE;
	if (me->vw_caps & SVGA_CAP_EXTENDED_FIFO) {
		me->vm_fifo[SVGA_FIFO_MIN] = SVGA_FIFO_NUM_REGS;
		me->vw_fifo_rfsz = me->vm_fifo[SVGA_FIFO_MIN];
		me->vm_fifo[SVGA_FIFO_MAX]      = me->vw_fifosize;
		me->vm_fifo[SVGA_FIFO_NEXT_CMD] = me->vw_fifo_min;
		me->vm_fifo[SVGA_FIFO_STOP]     = me->vw_fifo_min;
		if (vm_fifo_hasreg(me, SVGA_FIFO_CAPABILITIES))
			me->vw_fifo_caps = me->vm_fifo[SVGA_FIFO_CAPABILITIES];
	} else {
		me->vm_fifo[SVGA_FIFO_MIN]      = 16;
		me->vm_fifo[SVGA_FIFO_MAX]      = me->vw_fifosize;
		me->vm_fifo[SVGA_FIFO_NEXT_CMD] = 16;
		me->vm_fifo[SVGA_FIFO_STOP]     = 16;
		me->vw_fifo_rfsz                = 16;
	}

	/* Enable SVGA */
	vm_setreg(me, SVGA_REG_ENABLE, SVGA_REG_ENABLE_ENABLE);

	/* Enable the command FIFO */
	vm_setreg(me, SVGA_REG_CONFIG_DONE, 1);
}

PRIVATE NONNULL((1, 2)) void
NOTHROW(LIBSVGADRV_CC vmware_v_updaterect)(struct svga_chipset *__restrict self,
                                           struct svga_rect const *__restrict rect) {
	struct vmware_chipset *me = (struct vmware_chipset *)self;
	uint32_t *packet;
	printk(KERN_DEBUG "[vmware] updaterect(x: %" PRIu16 ", y: %" PRIu16 ", sx: %" PRIu16 ", sy: %" PRIu16 ")\n",
	       rect->svr_x, rect->svr_y, rect->svr_sx, rect->svr_sy);
	packet = vmware_fifo_reserve_cmd(me, SVGA_CMD_UPDATE, 4);
	*packet++ = rect->svr_x;
	*packet++ = rect->svr_y;
	*packet++ = rect->svr_sx;
	*packet++ = rect->svr_sy;
	vmware_fifo_commit_cmd(me, 4);
}


PRIVATE NONNULL((1, 2)) void CC
vmware_v_getregs(struct svga_chipset *__restrict self, byte_t regbuf[]) {
	size_t i;
	struct vmware_chipset *me = (struct vmware_chipset *)self;
	struct vmware_regs *reginfo = (struct vmware_regs *)regbuf;
	UNALIGNED_SET32(&reginfo->vmr_INDEX_PORT, vm_getindex(me));
	UNALIGNED_SET32(&reginfo->vmr_REG_ID, vm_getreg(me, SVGA_REG_ID));
	UNALIGNED_SET32(&reginfo->vmr_REG_ENABLE, vm_getreg(me, SVGA_REG_ENABLE));
	UNALIGNED_SET32(&reginfo->vmr_REG_WIDTH, vm_getreg(me, SVGA_REG_WIDTH));
	UNALIGNED_SET32(&reginfo->vmr_REG_HEIGHT, vm_getreg(me, SVGA_REG_HEIGHT));
	UNALIGNED_SET32(&reginfo->vmr_REG_DEPTH, vm_getreg(me, SVGA_REG_DEPTH));
	UNALIGNED_SET32(&reginfo->vmr_REG_BPP, vm_getreg(me, SVGA_REG_BPP));
	UNALIGNED_SET32(&reginfo->vmr_REG_CONFIG_DONE, vm_getreg(me, SVGA_REG_CONFIG_DONE));
	UNALIGNED_SET32(&reginfo->vmr_REG_SYNC, vm_getreg(me, SVGA_REG_SYNC));
	UNALIGNED_SET32(&reginfo->vmr_REG_GUEST_ID, vm_getreg(me, SVGA_REG_GUEST_ID));
	UNALIGNED_SET32(&reginfo->vmr_REG_CURSOR_ID, vm_getreg(me, SVGA_REG_CURSOR_ID));
	UNALIGNED_SET32(&reginfo->vmr_REG_CURSOR_X, vm_getreg(me, SVGA_REG_CURSOR_X));
	UNALIGNED_SET32(&reginfo->vmr_REG_CURSOR_Y, vm_getreg(me, SVGA_REG_CURSOR_Y));
	UNALIGNED_SET32(&reginfo->vmr_REG_CURSOR_ON, vm_getreg(me, SVGA_REG_CURSOR_ON));
	if (me->vw_caps & SVGA_CAP_PITCHLOCK)
		UNALIGNED_SET32(&reginfo->vmr_REG_PITCHLOCK, vm_getreg(me, SVGA_REG_PITCHLOCK));
	for (i = 0; i < me->vw_nscratch; ++i)
		UNALIGNED_SET32(&reginfo->vmr_REG_SCRATCH[i], vm_getreg(me, SVGA_SCRATCH_BASE + i));
	for (i = 0; i < COMPILER_LENOF(reginfo->vmr_REG_PALETTE); ++i)
		UNALIGNED_SET32(&reginfo->vmr_REG_PALETTE[i], vm_getreg(me, SVGA_PALETTE_BASE + i));
	vm_setindex(me, UNALIGNED_GET32(&reginfo->vmr_INDEX_PORT));
}

PRIVATE NONNULL((1, 2)) void CC
vmware_v_setregs(struct svga_chipset *__restrict self, byte_t const regbuf[]) {
	size_t i;
	uint32_t cursor_on;
	struct vmware_chipset *me = (struct vmware_chipset *)self;
	struct vmware_regs const *reginfo = (struct vmware_regs const *)regbuf;
	vm_setreg(me, SVGA_REG_ID, UNALIGNED_GET32(&reginfo->vmr_REG_ID));
	vm_setreg(me, SVGA_REG_CONFIG_DONE, 0);
	vm_setreg(me, SVGA_REG_ENABLE, SVGA_REG_ENABLE_DISABLE);
	vm_setreg(me, SVGA_REG_GUEST_ID, UNALIGNED_GET32(&reginfo->vmr_REG_GUEST_ID));

	vm_setreg(me, SVGA_REG_WIDTH, UNALIGNED_GET32(&reginfo->vmr_REG_WIDTH));
	vm_setreg(me, SVGA_REG_HEIGHT, UNALIGNED_GET32(&reginfo->vmr_REG_HEIGHT));
	vm_setreg(me, SVGA_REG_DEPTH, UNALIGNED_GET32(&reginfo->vmr_REG_DEPTH));
	vm_setreg(me, SVGA_REG_BPP, UNALIGNED_GET32(&reginfo->vmr_REG_BPP));

	vm_setreg(me, SVGA_REG_ENABLE, UNALIGNED_GET32(&reginfo->vmr_REG_ENABLE));
	vm_setreg(me, SVGA_REG_CONFIG_DONE, UNALIGNED_GET32(&reginfo->vmr_REG_CONFIG_DONE));

	vm_setreg(me, SVGA_REG_SYNC, UNALIGNED_GET32(&reginfo->vmr_REG_SYNC));
	cursor_on = UNALIGNED_GET32(&reginfo->vmr_REG_CURSOR_ON);
	if (cursor_on) {
		vm_setreg(me, SVGA_REG_CURSOR_ID, UNALIGNED_GET32(&reginfo->vmr_REG_CURSOR_ID));
		vm_setreg(me, SVGA_REG_CURSOR_X, UNALIGNED_GET32(&reginfo->vmr_REG_CURSOR_X));
		vm_setreg(me, SVGA_REG_CURSOR_Y, UNALIGNED_GET32(&reginfo->vmr_REG_CURSOR_Y));
		vm_setreg(me, SVGA_REG_CURSOR_ON, cursor_on);
	}
	if (me->vw_caps & SVGA_CAP_PITCHLOCK)
		vm_setreg(me, SVGA_REG_PITCHLOCK, UNALIGNED_GET32(&reginfo->vmr_REG_PITCHLOCK));
	for (i = 0; i < COMPILER_LENOF(reginfo->vmr_REG_PALETTE); ++i)
		vm_setreg(me, SVGA_PALETTE_BASE + i, UNALIGNED_GET32(&reginfo->vmr_REG_PALETTE[i]));
	for (i = 0; i < me->vw_nscratch; ++i)
		vm_setreg(me, SVGA_SCRATCH_BASE + i, UNALIGNED_GET32(&reginfo->vmr_REG_SCRATCH[i]));
	vm_setindex(me, UNALIGNED_GET32(&reginfo->vmr_INDEX_PORT));
}

PRIVATE NONNULL((1, 2)) ssize_t CC
vmware_v_strings(struct svga_chipset *__restrict self,
                svga_chipset_enumstring_t cb, void *arg) {
	ssize_t temp, result = 0;
	struct vmware_chipset *me = (struct vmware_chipset *)self;
	char valbuf[MAX_C(lengthof("0x" PRIMAXx16),
	                  lengthof("0x" PRIMAXx32),
	                  lengthof("0x" PRIMAXx32 "-" "0x" PRIMAXx32),
	                  lengthof(PRIMAXu32),
	                  lengthof("0x" PRIMAXx16 ".0x" PRIMAXx16),
	                  lengthof("0x" PRIMAXx8 ".0x" PRIMAXx8 "."
	                           "0x" PRIMAXx8 ".0x" PRIMAXx8))];
#define REPORT(name, ...)                \
	do {                                 \
		sprintf(valbuf, __VA_ARGS__);    \
		temp = (*cb)(arg, name, valbuf); \
		if unlikely (temp < 0)           \
			goto err;                    \
		result += temp;                  \
	}	__WHILE0
	REPORT("vmware.iobase", "%#" PRIx32, me->vw_iobase);
	REPORT("vmware.reg.CAPABILITIES", "%#" PRIx32, me->vw_caps);
	REPORT("vmware.reg.HOST_BITS_PER_PIXEL", "%" PRIu32, me->vw_hbpp);
	REPORT("vmware.reg.FB", "%#" PRIx32 "-%#" PRIx32, me->vw_fbstart, me->vw_fbstart + me->vw_fbsize - 1);
	REPORT("vmware.reg.MEM", "%#" PRIx32 "-%#" PRIx32, me->vw_fifoaddr, me->vw_fifoaddr + me->vw_fifosize - 1);
	REPORT("vmware.reg.MAX_WIDTH", "%" PRIu32, me->vw_maxresx);
	REPORT("vmware.reg.MAX_HEIGHT", "%" PRIu32, me->vw_maxresy);
	REPORT("vmware.reg.SCRATCH_SIZE", "%" PRIu32, me->vw_nscratch);
	REPORT("vmware.fifo.CAPABILITIES", "%#" PRIx32, me->vw_fifo_caps);
	REPORT("vmware.fifo.MIN", "%" PRIu32, me->vw_fifo_min);
	REPORT("vmware.fifo.MAX", "%" PRIu32, me->vw_fifo_max);
	REPORT("pci.addr", "%#" PRIx32, me->vw_pci->pd_addr);
	REPORT("pci.vendor", "%#.4" PRIx16 ".%#.4" PRIx16, me->vw_pci->pd_vendor_id, me->vw_pci->pd_subvendor_id);
	REPORT("pci.device", "%#.4" PRIx16 ".%#.4" PRIx16, me->vw_pci->pd_device_id, me->vw_pci->pd_subdevice_id);
	REPORT("pci.class", "%#.2" PRIx8 ".%#.2" PRIx8 ".%#.2" PRIx8 ".%#.2" PRIx8,
	       me->vw_pci->pd_class_id, me->vw_pci->pd_subclass_id,
	       me->vw_pci->pd_progif_id, me->vw_pci->pd_revision);
	return result;
err:
	return temp;
#undef REPORT
}



/* Probe for VESA support.
 * @return: true:  Chipset found.
 * @return: false: Chipset isn't present. */
INTERN WUNUSED NONNULL((1)) bool CC
cs_vmware_probe(struct svga_chipset *__restrict self) {
	struct vmware_chipset *me = (struct vmware_chipset *)self;
#ifndef __KERNEL__
	PMMAPPHYS mmapphys;
	me->vw_libpciaccess = NULL;
	me->vw_libphys = NULL;
	TRY
#endif /* !__KERNEL__ */
	{
		struct pci_device *pci;
#ifdef __KERNEL__
		pci = SLIST_FIRST(&pci_devices);
#else /* __KERNEL__ */
		/* Load+initialize libphys. */
		me->vw_libphys = dlopen(LIBPHYS_LIBRARY_NAME, RTLD_LOCAL);
		if unlikely(!me->vw_libphys)
			goto err_initfailed;
		*(void **)&me->vw_munmapphys = dlsym(me->vw_libphys, "munmapphys");
		if unlikely(!me->vw_munmapphys)
			goto err_initfailed;
		*(void **)&mmapphys = dlsym(me->vw_libphys, "mmapphys");
		if unlikely(!mmapphys)
			goto err_initfailed;

		/* Load+initialize libpciaccess. */
		pci = NULL;
		me->vw_libpciaccess = dlopen(LIBPCIACCESS_LIBRARY_NAME, RTLD_LOCAL);
		if (me->vw_libpciaccess) {
			typeof(pci_system_init) *pdyn_pci_system_init;
			typeof(__pci_devices) *pdyn_pci_devices;
			if ((*(void **)&pdyn_pci_system_init = dlsym(me->vw_libpciaccess, "pci_system_init")) == NULL ||
			    (*(void **)&pdyn_pci_devices = dlsym(me->vw_libpciaccess, "pci_devices")) == NULL ||
			    ((*pdyn_pci_system_init)() != EOK) || (pci = (*pdyn_pci_devices)()) == NULL) {
				dlclose(me->vw_libpciaccess);
				me->vw_libpciaccess = NULL;
			}
		}
#endif /* !__KERNEL__ */

		/* Find the relevant PCI device. */
		for (;; pci = SLIST_NEXT(pci, _pd_link)) {
			if (!pci)
				goto err_initfailed;
			if (pci->pd_vendor_id == PCI_VENDOR_ID_VMWARE &&
			    pci->pd_device_id == PCI_DEVICE_ID_VMWARE_SVGA2)
				break;
		}

		/* Remember the relevant PCI device. */
		me->vw_pci = pci;
		printk(KERN_INFO "[vmware] Chipset detected [pci: %#" PRIx32 "]\n", pci->pd_addr);

		/* Load video limits */
		if (!pci->pd_regions[0].pmr_is_IO)
			goto err_initfailed_late;
		if (!pci->pd_regions[0].pmr_addr)
			goto err_initfailed_late;
		me->vw_iobase = (uint16_t)pci->pd_regions[0].pmr_addr;
		printk(KERN_INFO "[vmware] iobase=%#" PRIx16 "\n", me->vw_iobase);
		me->vw_index  = (uint32_t)-1;
		printk(KERN_INFO "[vmware] Enable PCI BUSMASTER+MEMTOUCH+IOTOUCH\n");
		pci_device_cfg_writel(pci, PCI_DEV4,
		                      (pci_device_cfg_readl(pci, PCI_DEV4)) |
		                      (PCI_CDEV4_BUSMASTER | PCI_CDEV4_ALLOW_MEMTOUCH | PCI_CDEV4_ALLOW_IOTOUCH));

		vm_setreg(me, SVGA_REG_ID, SVGA_ID_2);
		{
			uint32_t ver = vm_getreg(me, SVGA_REG_ID);
			if (ver != SVGA_ID_2) {
				printk(KERN_WARNING "[vmware] Unsupported version %#" PRIx32 " "
				                    "reported (expected: %#" PRIx32 ")\n",
				       ver, SVGA_ID_2);
				goto err_initfailed_late;
			}
		}

		/* Read memory config */
		me->vw_fbstart  = vm_getreg(me, SVGA_REG_FB_START);
		me->vw_fbsize   = vm_getreg(me, SVGA_REG_FB_SIZE);
		me->vw_fifoaddr = vm_getreg(me, SVGA_REG_MEM_START);
		me->vw_fifosize = vm_getreg(me, SVGA_REG_MEM_SIZE);
		me->sc_vmemsize = vm_getreg(me, SVGA_REG_VRAM_SIZE);

		/* Read display config */
		me->vw_caps     = vm_getreg(me, SVGA_REG_CAPABILITIES);
		me->vw_maxresx  = vm_getreg(me, SVGA_REG_MAX_WIDTH);
		me->vw_maxresy  = vm_getreg(me, SVGA_REG_MAX_HEIGHT);
		me->vw_hbpp     = vm_getreg(me, SVGA_REG_HOST_BITS_PER_PIXEL);
		me->vw_nscratch = vm_getreg(me, SVGA_REG_SCRATCH_SIZE);

		/* Advertise our OS (we like to act like we're linux) */
		vm_setreg(me, SVGA_REG_GUEST_ID, SVGA_REG_GUEST_LINUX);

		/* Fill in operators and the like... */
		DBG_memset(&me->sc_ops, 0xcc, sizeof(me->sc_ops));
		me->sc_logicalwidth_max = UINT32_MAX; /* Max value that can physically be written */
		if (me->sc_logicalwidth_max > self->sc_vmemsize)
			me->sc_logicalwidth_max = self->sc_vmemsize;
		me->sc_ops.sco_fini         = &vmware_v_fini;
		me->sc_ops.sco_modeinfosize = sizeof(struct vmware_modeinfo);
		me->sc_ops.sco_strings      = &vmware_v_strings;
		me->sc_ops.sco_getmode      = &vmware_v_getmode;
		me->sc_ops.sco_setmode      = &vmware_v_setmode;
		me->sc_ops.sco_getregs      = &vmware_v_getregs;
		me->sc_ops.sco_setregs      = &vmware_v_setregs;
		me->sc_ops.sco_regsize      = sizeof__vmware_regs(me->vw_nscratch);
		me->sc_ops.sco_updaterect   = &vmware_v_updaterect;

		/* Map the FIFO into memory. */
#ifdef __KERNEL__
		me->vm_fifo_unmap_cookie = mman_unmap_kram_cookie_alloc();
		TRY {
			me->vm_fifo = (uint32_t volatile *)mman_map(/* self:        */ &mman_kernel,
			                                            /* hint:        */ MHINT_GETADDR(KERNEL_MHINT_DEVICE),
			                                            /* num_bytes:   */ me->vw_fifosize,
			                                            /* prot:        */ PROT_READ | PROT_WRITE | PROT_SHARED,
			                                            /* flags:       */ MHINT_GETMODE(KERNEL_MHINT_DEVICE),
			                                            /* file:        */ &mfile_phys,
			                                            /* file_fspath: */ NULL,
			                                            /* file_fsname: */ NULL,
			                                            /* file_pos:    */ (pos_t)me->vw_fifoaddr);
		} EXCEPT {
			mman_unmap_kram_cookie_free(me->vm_fifo_unmap_cookie);
			RETHROW();
		}
#else /* __KERNEL__ */
		me->vm_fifo = (uint32_t volatile *)(*mmapphys)(me->vw_fifoaddr, me->vw_fifosize);
		if unlikely(me->vm_fifo == (uint32_t *)MAP_FAILED)
			goto err_initfailed_late;
#endif /* !__KERNEL__ */

		/* Misc. runtime fields. */
		me->vw_fifo_caps = 0;
		me->vm_fifo_debounce_inuse = false;
		return true;
	}
#ifndef __KERNEL__
#undef pci_devices
	EXCEPT {
		if (me->vw_libphys)
			dlclose(me->vw_libphys);
		if (me->vw_libpciaccess)
			dlclose(me->vw_libpciaccess);
		RETHROW();
	}
#endif /* !__KERNEL__ */
err_initfailed_late:
	printk(KERN_ERR "[vmware] Adapter initialization failed\n");
err_initfailed:
#ifndef __KERNEL__
	if (me->vw_libphys)
		dlclose(me->vw_libphys);
	if (me->vw_libpciaccess)
		dlclose(me->vw_libpciaccess);
#endif /* !__KERNEL__ */
	return false;
}

DECL_END
#endif /* CONFIG_HAVE_LIBSVGADRV_CHIPSET_VMWARE */

#endif /* !GUARD_LIBSVGADRV_CS_VMWARE_C */
