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
#ifndef GUARD_LIBSVGA_CS_VESA_C
#define GUARD_LIBSVGA_CS_VESA_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <kos/kernel/printk.h>
#include <kos/kernel/types.h>

#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#include <libbios86/bios.h>

#include "cs-vesa.h"

DECL_BEGIN

/*
 * VESA driver. Based on:
 * https://www.lowlevel.eu/wiki/VESA_BIOS_Extensions
 */

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* vm86 controller. */
PRIVATE struct bios86_emulator vesa_emu;
#define vesa_gpbase           bios86_emulator_mem_gpbas(&vesa_emu)
#define vesa_farptr(seg, off) bios86_emulator_farptr(&vesa_emu, seg, off)
#define VESA_GPBASE           BIOS86_MEM_GPBAS


/* Check if the BIOS has VESA support. */
PRIVATE struct vbe_biosinfo *CC vesa_testbios(void) {
	struct vbe_biosinfo *result;
	result = (struct vbe_biosinfo *)vesa_gpbase;
	memset(&vesa_emu.b86e_vm.vr_regs, 0, sizeof(vesa_emu.b86e_vm.vr_regs));
	DBG_memset(result, 0xcc, sizeof(*result));
	memcpy(result->vbi_signature, "VBE2", 4);
	vesa_emu.b86e_vm.vr_regs.vr_eax = 0x4f00;
	vesa_emu.b86e_vm.vr_regs.vr_es  = VESA_GPBASE >> 4;
	if (!bios86_emulator_int(&vesa_emu, 0x10))
		return NULL;
	if ((vesa_emu.b86e_vm.vr_regs.vr_eax & 0xffff) != 0x4f)
		return NULL;
	if (memcmp(result->vbi_signature, "VESA", 4) != 0)
		return NULL;
	return result;
}


INTERN void vesa_init(void) {
	struct vbe_biosinfo *vbi;
	u16 *modelist, mode;
	bios86_emulator_init(&vesa_emu);
	vbi = vesa_testbios();
	if (!vbi) {
		printk(KERN_DEBUG "[vesa] No BIOS support\n");
		bios86_emulator_fini(&vesa_emu);
		return;
	}

	printk(KERN_INFO "[vesa] Bios claims VESA support\n");
	printk(KERN_INFO "[vesa] oem_string:       %q\n", (char *)vesa_farptr(vbi->vbi_oem_string_seg, vbi->vbi_oem_string_off));
	printk(KERN_INFO "[vesa] oem_vendor_name:  %q\n", (char *)vesa_farptr(vbi->vbi_oem_vendor_name_seg, vbi->vbi_oem_vendor_name_off));
	printk(KERN_INFO "[vesa] oem_product_name: %q\n", (char *)vesa_farptr(vbi->vbi_oem_product_name_seg, vbi->vbi_oem_product_name_off));
	printk(KERN_INFO "[vesa] oem_product_rev:  %q\n", (char *)vesa_farptr(vbi->vbi_oem_product_rev_seg, vbi->vbi_oem_product_rev_off));
	modelist = (u16 *)vesa_farptr(vbi->vbi_vidmodelist_seg, vbi->vbi_vidmodelist_off);
	for (; (mode = *modelist) != 0xffff; ++modelist) {
		printk(KERN_INFO "[vesa] mode: %" PRIu16 "\n", mode);
		/* TODO */
	}

	/* TODO */

	bios86_emulator_fini(&vesa_emu);
}

DECL_END

#endif /* !GUARD_LIBSVGA_CS_VESA_C */
