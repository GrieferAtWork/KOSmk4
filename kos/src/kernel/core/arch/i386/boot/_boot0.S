/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

#include <kernel/compiler.h>

#include <hybrid/host.h>

#include <asm/cpu-flags.h>
#include <asm/instr/jccN.h>
#include <kos/kernel/segment.h>


.macro call16 sym:req
	.byte  0xe8
#ifdef __x86_64__
	.reloc ., R_X86_64_PC16, \sym
#else /* __x86_64__ */
	.reloc ., R_386_PC16, \sym
#endif /* !__x86_64__ */
	.word  -2
.endm
.macro call16_p sym:req
	.byte  0x66
	.byte  0xe8
#ifdef __x86_64__
	.reloc ., R_X86_64_PC16, \sym
#else /* __x86_64__ */
	.reloc ., R_386_PC16, \sym
#endif /* !__x86_64__ */
	.word  -2
.endm

.section .x86.boot0, "awx"
.code16
PRIVATE_FUNCTION(x86_boot0_sector)
#define S(x) (0x7c00 + ((x) - x86_boot0_sector))
	/* . = 0x7c00 */
	pushw  %dx

	/* GET DRIVE PARAMETERS  */
	xorw   %ax, %ax
	movw   %ax, %es
	movw   %ax, %di
	movb   $0x08, %ah
	int    $0x13
//	jc8    boot_error
	andb   $0x3f, %cl
	/* DH: Number of Heads -1 */
	/* CL: Sectors per Track */
	xorb   %ch, %ch
	movzbw %dh, %dx
	incw   %dx
	pushw  %dx
	pushw  %cx
	movw   %sp, %bp
#define SEC_TRACK  0(%bp) /* Sectors per track */
#define NUM_HEADS  2(%bp) /* Number of heads */
#define BOOTDISK   4(%bp) /* %dx, as given by the bios */

	/* At this point, we must:
	 * - Enabled A20 (Using the keyboard controller method)
	 * - Load the kernel using `read_lba' and copy its data to 0x00100000
	 * - Enable protected mode and fill in %cs and %ds
	 * - Jump to `_start' (which is at `_start - KERNEL_CORE_BASE')
	 * - If possible, also fill in custom boot magic in `%eax'
	 *   to pass information about `BOOTDISK' to the kernel. */

	/* Enable A20 (from https://wiki.osdev.org/A20_Line) */
	call16 a20wait
	movb   $0xAD, %al
	outb   %al, $0x64
	call16 a20wait
	movb   $0xd0, %al
	outb   %al, $0x64
	call16 a20wait2
	inb    $0x60, %al
	pushw  %ax
	call16 a20wait
	movb   $0xd1, %al
	outb   %al, $0x64
	call16 a20wait
	popw   %ax
	orb    $2, %al
	outb   %al, $0x60
	call16 a20wait
	movb   $0xae, %al
	outb   %al, $0x64
	call16 a20wait

	xorw   %ax, %ax
	movw   %ax, %ds
	movl   $(S(boot0_gdt_ptr)), %eax
	lgdtl  (%eax)

	EXTERN(__kernel_sector_count)
	movw   $(__kernel_sector_count), %cx
	movl   $0x00100000, %edi /* DESTPTR */
	movw   $0, %ax           /* SECNO */
1:

#if 1
	pushaw
	movw   $0xb800, %dx
	movw   %dx, %es
	xorw   %di, %di
	movw   %ax, %dx
	shrw   $12, %ax
	call16 tohex
	movb   $0x07, %ah
	stosw
	movw   %dx, %ax
	shrw   $8, %ax
	call16 tohex
	movb   $0x07, %ah
	stosw
	movw   %dx, %ax
	shrw   $4, %ax
	call16 tohex
	movb   $0x07, %ah
	stosw
	movw   %dx, %ax
	call16 tohex
	movb   $0x07, %ah
	stosw
	popaw
#endif

	movw   %cx, %dx
	xorw   %cx, %cx
	movw   %cx, %es     /* %es=0 */
	movw   $0x0500, %bx /* Buffer location: %es:0x0500 */
	pushw  %ax

	call   read_lba
	call16 pmode_enter
.code32
	/* Copy into high memory. */
	movzwl %bx, %esi
	movl   $128, %ecx
	rep;   movsl
	call16_p pmode_leave
.code16
	movw   %dx, %cx
	popw   %ax
	incw   %ax
	loopw  1b

	/* Enter protected mode for the last time. */
	call16 pmode_enter
.code32
	/* Jump to the kernel entry point */
	movl   $(_start - KERNEL_CORE_BASE), %eax
	jmp    *%eax
.code16

//	subw   $512, %sp
//	movw   %ss, %ax
//	movw   %ax, %es
//	movw   %sp, %bx
//	movw   $15, %ax /* LBA */
//	call16 read_lba
//
//	/* For debugging: Hexdump to VGA display */
//	movw   %ss, %ax
//	movw   %ax, %ds
//	movw   %sp, %si
//	movw   $0xb800, %ax
//	movw   %ax, %es
//	movw   $0, %di
//	movw   $512, %cx
//
//	movb   $0x07, %ah
//1:	lodsb
//	movb   %al, %dl
//	shrb   $4, %al
//	call16 tohex
//	stosw
//	movb   %dl, %al
//	call16 tohex
//	stosw
//	loop   1b
//
//
//1:	hlt
//	jmp8   1b

a20wait:
	inb    $0x64, %al
	testb  $2, %al
	jnz8   a20wait
	ret

a20wait2:
	inb    $0x64, %al
	testb  $1, %al
	jz8    a20wait2
	ret

PRIVATE_FUNCTION(pmode_enter)
	movl   %cr0, %eax
	orw    $(CR0_PE), %ax
	movl   %eax, %cr0
	movw   %ss, %ax
	/* ljmpl $8, $<return-addr> */
	ljmpl $8, $S(1f)
	.code32
1:	/* Fixup the stack pointer. */
	movzwl %ax, %eax
	shll   $4, %eax
	addl   %eax, %esp
	/* Set p-mode %ss */
	movw   $16, %ax
	movw   %ax, %ss
	movw   %ax, %ds
	movw   %ax, %es
	/* Return to the caller */
	retw
	.code16
END(pmode_enter)

PRIVATE_FUNCTION(pmode_leave)
	.code32
	pushw  %cx
	pushw  %dx
	/* Split ESP */
	movl   %esp, %edx
	shrl   $4, %edx
	movw   $32, %cx
	movw   %cx, %ss
	movl   %cr0, %ecx
	ljmpl  $24, $S(1f) /* Jump to segmented real-mode */
1:	.code16
	andw   $(~CR0_PE), %cx
	movl   %ecx, %cr0
	ljmpw  $0, $S(1f) /* Jump to raw real-mode */
1:	/* Set stack segment */
	andw   $0xf000, %dx
	movw   %dx, %ss /* See above */
	/* Return to the caller */
	popw   %dx
	popw   %cx
	ret
END(pmode_enter)

PRIVATE_OBJECT(boot0_gdt_ptr)
	.word  (5 * SIZEOF_SEGMENT_DESCRIPTOR) - 1
	.long  S(boot0_gdt)
END(boot0_gdt_ptr)
PRIVATE_OBJECT(boot0_gdt)
#define DEFINE_SEGMENT_DESCRIPTOR(TYPE, args) \
	.long  SEGMENT_##TYPE##_INIT_UL args; \
	.long  SEGMENT_##TYPE##_INIT_UH args;
1:	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD, 1, 0, 1, 0, 0, 1, 1)) /* protected-mode */
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, 0, 1, 1)) /* protected-mode */
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD, 1, 0, 1, 0, 0, 0, 1)) /* real-mode */
	DEFINE_SEGMENT_DESCRIPTOR(DESCRIPTOR, (0, 0xfffff, SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR, 1, 0, 1, 0, 0, 0, 1)) /* real-mode */
#undef DEFINE_SEGMENT_DESCRIPTOR
END(boot0_gdt)

	/* %al = (%al >= 10 ? 'A' + (%al - 10) : '0' + %al)
	 * IN:  u8 value = %al;   (Upper 4 bits are ignored)
	 * OUT: char hexch = %al; */
PRIVATE_FUNCTION(tohex)
	andb   $0xf, %al
	cmpb   $10, %al
	jae8   1f
	addb   $'0', %al
	ret
1:	addb   $(+ 'A' - 10), %al
	ret
END(tohex)

	/* Read 1 sectors from LBA #%ax into %es:%bx (does not return on error)
	 * IN: u16 sector_lba  = %ax;
	 * IN: void *buffer    = %es:%bx; */
PRIVATE_FUNCTION(read_lba)
	/* Temp     = %ax / SEC_TRACK
	 * Sector   = (%ax % SEC_TRACK) + 1
	 * Cylinder = Temp / NUM_HEADS
	 * Head     = Temp % NUM_HEADS*/
	pushaw
	xorw   %dx, %dx
	divw   SEC_TRACK
	/* Sector   = %dx + 1
	 * Cylinder = %ax / NUM_HEADS
	 * Head     = %ax % NUM_HEADS */
	movb   %dl, %cl
	incb   %cl
	andb   $0x3f, %cl
	/* Sector   = %cl
	 * Cylinder = %ax / NUM_HEADS
	 * Head     = %ax % NUM_HEADS */
	xorw   %dx, %dx
	divw   NUM_HEADS
	/* Sector   = %cl
	 * Cylinder = %ax
	 * Head     = %dx */
	movb   %dl, %dh
	/* Sector   = %cl
	 * Cylinder = %ax
	 * Head     = %dh */
	/* Only one missing now: Cylinder */
	movb   %al, %ch
	andb   $0x03, %ah
	shlb   $6, %ah
	orb    %ah, %cl
	/* Disk:     BOOTDISK (== %dl)
	 * Sector:   1-63     (== %cl & 0x3f)
	 * Cylinder: 0-0x3ff  (== %ch | ((%cl & 0xc0) << 8))
	 * Head:     0-0xff   (== %dh) */
	movb   BOOTDISK, %dl
	/* Now we can finally invoke `int 13h' */
	movw   $0x0201, %ax /* 0x01: # of sectors; 0x0200: Function ID */
	int    $0x13
	popaw
//	jc8    boot_error
	ret
END(read_lba)

PRIVATE_FUNCTION(boot_error)
	xchgw %bx, %bx
1:	hlt
	jmp8 1b
END(boot_error)
.if (. - x86_boot0_sector) > 510
.error "Boot sector too large"
.endif
.if (. - x86_boot0_sector) < 510
.skip 510 - (. - x86_boot0_sector)
.endif
	.byte 0x55
	.byte 0xaa
#undef S
END(x86_boot0_sector)

.code32

