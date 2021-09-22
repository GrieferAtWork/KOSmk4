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
#ifndef _LIBGEN86_GEN_H
#define _LIBGEN86_GEN_H 1

#include "api.h"
/**/

#include "register.h"

/* NOTE: `gen_modrm' is one of:
 *   - `gen86_modrm_*'
 *
 * Example:
 * >> byte_t buf[512];
 * >> byte_t *writer = buf;
 * >> gen86_movb_r_mod(&writer, gen86_modrm_r, GEN86_R_AL, GEN86_R_AH);                         // movb %al, %ah
 * >> gen86_movb_r_mod(&writer, gen86_modrm_d, GEN86_R_AH, 0x12345678);                         // movb %ah, 0x12345678
 * >> gen86_movb_r_mod(&writer, gen86_modrm_dbis, GEN86_R_AH, 42, GEN86_R_PBX, GEN86_R_PAX, 4); // movb %ah, 42(%Pbx,%Pax,4)
 */

#if LIBGEN86_TARGET_BITS == 16
#define _gen86_pfx16_(p_pc) /* nothing */
#define _gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x66),
#define _gen86_adr16_(p_pc) /* nothing */
#define _gen86_adr32_(p_pc) _gen86_putb(p_pc, 0x67),
#else /* LIBGEN86_TARGET_BITS == 16 */
#define _gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x66),
#define _gen86_pfx32_(p_pc) /* nothing */
#define _gen86_adr16_(p_pc) _gen86_putb(p_pc, 0x67),
#define _gen86_adr32_(p_pc) /* nothing */
#endif /* LIBGEN86_TARGET_BITS != 16 */


/* Max # of bytes which may be written by any single
 * invocation  of one of the `gen86_*' macros below. */
#define GEN86_INSTRLEN_MAX 15

#if LIBGEN86_TARGET_BITS == 16
#define _GEN86_JMPP_EXTRA 1 /* == sizeof(gen86_jmpP) - sizeof(gen86_jmp8) */
#else /* LIBGEN86_TARGET_BITS == 16 */
#define _GEN86_JMPP_EXTRA 3 /* == sizeof(gen86_jmpP) - sizeof(gen86_jmp8) */
#endif /* LIBGEN86_TARGET_BITS != 16 */



/*[[[deemon
#define hex2(x) ("0x" + (x).hex()[2:].zfill(2))
function genArithBlock(name, start) {
	local pad = " " * (3 - #name);
	local reg = start / 8;
	print("#define gen86_", name, "b_r_mod(p_pc, gen_modrm, src_reg, ...)  ", pad, "/" "* ", name, "b", pad, "  %src_reg, ... *" "/ gen_modrm(p_pc, 0, _gen86_putb(p_pc, ", hex2(start), "), src_reg, __VA_ARGS__, (void)0)");
	print("#define gen86_", name, "w_r_mod(p_pc, gen_modrm, src_reg, ...)  ", pad, "/" "* ", name, "w", pad, "  %src_reg, ... *" "/ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, ", hex2(start+1), "), src_reg, __VA_ARGS__, (void)0))");
	print("#define gen86_", name, "l_r_mod(p_pc, gen_modrm, src_reg, ...)  ", pad, "/" "* ", name, "l", pad, "  %src_reg, ... *" "/ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, ", hex2(start+1), "), src_reg, __VA_ARGS__, (void)0))");
	print("#define gen86_", name, "b_mod_r(p_pc, gen_modrm, dst_reg, ...)  ", pad, "/" "* ", name, "b", pad, "  ..., %dst_reg *" "/ gen_modrm(p_pc, 0, _gen86_putb(p_pc, ", hex2(start+2), "), dst_reg, __VA_ARGS__, (void)0)");
	print("#define gen86_", name, "w_mod_r(p_pc, gen_modrm, dst_reg, ...)  ", pad, "/" "* ", name, "w", pad, "  ..., %dst_reg *" "/ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, ", hex2(start+3), "), dst_reg, __VA_ARGS__, (void)0))");
	print("#define gen86_", name, "l_mod_r(p_pc, gen_modrm, dst_reg, ...)  ", pad, "/" "* ", name, "l", pad, "  ..., %dst_reg *" "/ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, ", hex2(start+3), "), dst_reg, __VA_ARGS__, (void)0))");
	print("#define gen86_", name, "b_imm_al(p_pc, imm)                     ", pad, "/" "* ", name, "b", pad, "  $imm, %al     *" "/ (_gen86_putb(p_pc, ", hex2(start+4), "), _gen86_putb(p_pc, imm))");
	print("#define gen86_", name, "w_imm_ax(p_pc, imm)                     ", pad, "/" "* ", name, "w", pad, "  $imm, %ax     *" "/ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, ", hex2(start+5), "), _gen86_putw(p_pc, imm))");
	print("#define gen86_", name, "l_imm_eax(p_pc, imm)                    ", pad, "/" "* ", name, "l", pad, "  $imm, %eax    *" "/ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, ", hex2(start+5), "), _gen86_putl(p_pc, imm))");
	print("#define gen86_", name, "b_imm_mod(p_pc, gen_modrm, imm, ...)    ", pad, "/" "* ", name, "b", pad, "  $imm, ...     *" "/ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x80), ", reg, ", __VA_ARGS__, _gen86_putb(p_pc, imm))");
	print("#define gen86_", name, "w_imm16u_mod(p_pc, gen_modrm, imm, ...) ", pad, "/" "* ", name, "w", pad, "  $imm, ...     *" "/ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), ", reg, ", __VA_ARGS__, _gen86_putw(p_pc, imm)))");
	print("#define gen86_", name, "l_imm32s_mod(p_pc, gen_modrm, imm, ...) ", pad, "/" "* ", name, "l", pad, "  $imm, ...     *" "/ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), ", reg, ", __VA_ARGS__, _gen86_putl(p_pc, imm)))");
	print("#define gen86_", name, "w_imm8s_mod(p_pc, gen_modrm, imm, ...)  ", pad, "/" "* ", name, "w", pad, "  $imm, ...     *" "/ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), ", reg, ", __VA_ARGS__, _gen86_putsb(p_pc, imm)))");
	print("#define gen86_", name, "l_imm8s_mod(p_pc, gen_modrm, imm, ...)  ", pad, "/" "* ", name, "l", pad, "  $imm, ...     *" "/ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), ", reg, ", __VA_ARGS__, _gen86_putsb(p_pc, imm)))");
	print("#define gen86_", name, "w_imm_mod(p_pc, gen_modrm, imm, ...)    ", pad, "/" "* ", name, "w", pad, "  $imm, ...     *" "/ (_gen86_fitsb(imm) ? gen86_", name, "w_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_", name, "w_imm16u_mod(p_pc, gen_modrm, imm, __VA_ARGS__))");
	print("#define gen86_", name, "l_imm_mod(p_pc, gen_modrm, imm, ...)    ", pad, "/" "* ", name, "l", pad, "  $imm, ...     *" "/ (_gen86_fitsb(imm) ? gen86_", name, "l_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_", name, "l_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))");
	print("#if LIBGEN86_TARGET_BITS == 64");
	print("#define gen86_", name, "q_r_mod(p_pc, gen_modrm, src_reg, ...)  ", pad, "/" "* ", name, "q", pad, "  %src_reg, ... *" "/ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, ", hex2(start+1), "), src_reg, __VA_ARGS__, (void)0)");
	print("#define gen86_", name, "q_mod_r(p_pc, gen_modrm, dst_reg, ...)  ", pad, "/" "* ", name, "q", pad, "  ..., %dst_reg *" "/ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, ", hex2(start+3), "), dst_reg, __VA_ARGS__, (void)0)");
	print("#define gen86_", name, "q_imm_rax(p_pc, imm)                    ", pad, "/" "* ", name, "q", pad, "  $imm, %rax    *" "/ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, ", hex2(start+5), "), _gen86_putsl(p_pc, imm))");
	print("#define gen86_", name, "q_imm32s_mod(p_pc, gen_modrm, imm, ...) ", pad, "/" "* ", name, "q", pad, "  $imm, ...     *" "/ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x81), ", reg, ", __VA_ARGS__, _gen86_putsb(p_pc, imm))");
	print("#define gen86_", name, "q_imm8s_mod(p_pc, gen_modrm, imm, ...)  ", pad, "/" "* ", name, "q", pad, "  $imm, ...     *" "/ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x83), ", reg, ", __VA_ARGS__, _gen86_putsb(p_pc, imm))");
	print("#define gen86_", name, "q_imm_mod(p_pc, gen_modrm, imm, ...)    ", pad, "/" "* ", name, "q", pad, "  $imm, ...     *" "/ (_gen86_fitsb(imm) ? gen86_", name, "q_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_", name, "q_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))");
	print("#endif /" "* LIBGEN86_TARGET_BITS == 64 *" "/");
}
genArithBlock("add", 0x00);
genArithBlock("or",  0x08);
genArithBlock("adc", 0x10);
genArithBlock("sbb", 0x18);
genArithBlock("and", 0x20);
genArithBlock("sub", 0x28);
genArithBlock("xor", 0x30);
genArithBlock("cmp", 0x38);
]]]*/
#define gen86_addb_r_mod(p_pc, gen_modrm, src_reg, ...)  /* addb  %src_reg, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x00), src_reg, __VA_ARGS__, (void)0)
#define gen86_addw_r_mod(p_pc, gen_modrm, src_reg, ...)  /* addw  %src_reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x01), src_reg, __VA_ARGS__, (void)0))
#define gen86_addl_r_mod(p_pc, gen_modrm, src_reg, ...)  /* addl  %src_reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x01), src_reg, __VA_ARGS__, (void)0))
#define gen86_addb_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* addb  ..., %dst_reg */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x02), dst_reg, __VA_ARGS__, (void)0)
#define gen86_addw_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* addw  ..., %dst_reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x03), dst_reg, __VA_ARGS__, (void)0))
#define gen86_addl_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* addl  ..., %dst_reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x03), dst_reg, __VA_ARGS__, (void)0))
#define gen86_addb_imm_al(p_pc, imm)                     /* addb  $imm, %al     */ (_gen86_putb(p_pc, 0x04), _gen86_putb(p_pc, imm))
#define gen86_addw_imm_ax(p_pc, imm)                     /* addw  $imm, %ax     */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x05), _gen86_putw(p_pc, imm))
#define gen86_addl_imm_eax(p_pc, imm)                    /* addl  $imm, %eax    */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x05), _gen86_putl(p_pc, imm))
#define gen86_addb_imm_mod(p_pc, gen_modrm, imm, ...)    /* addb  $imm, ...     */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x80), 0, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_addw_imm16u_mod(p_pc, gen_modrm, imm, ...) /* addw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 0, __VA_ARGS__, _gen86_putw(p_pc, imm)))
#define gen86_addl_imm32s_mod(p_pc, gen_modrm, imm, ...) /* addl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 0, __VA_ARGS__, _gen86_putl(p_pc, imm)))
#define gen86_addw_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* addw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 0, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_addl_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* addl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 0, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_addw_imm_mod(p_pc, gen_modrm, imm, ...)    /* addw  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_addw_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_addw_imm16u_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#define gen86_addl_imm_mod(p_pc, gen_modrm, imm, ...)    /* addl  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_addl_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_addl_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_addq_r_mod(p_pc, gen_modrm, src_reg, ...)  /* addq  %src_reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x01), src_reg, __VA_ARGS__, (void)0)
#define gen86_addq_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* addq  ..., %dst_reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x03), dst_reg, __VA_ARGS__, (void)0)
#define gen86_addq_imm_rax(p_pc, imm)                    /* addq  $imm, %rax    */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0x05), _gen86_putsl(p_pc, imm))
#define gen86_addq_imm32s_mod(p_pc, gen_modrm, imm, ...) /* addq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x81), 0, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_addq_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* addq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x83), 0, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_addq_imm_mod(p_pc, gen_modrm, imm, ...)    /* addq  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_addq_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_addq_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_orb_r_mod(p_pc, gen_modrm, src_reg, ...)   /* orb   %src_reg, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x08), src_reg, __VA_ARGS__, (void)0)
#define gen86_orw_r_mod(p_pc, gen_modrm, src_reg, ...)   /* orw   %src_reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x09), src_reg, __VA_ARGS__, (void)0))
#define gen86_orl_r_mod(p_pc, gen_modrm, src_reg, ...)   /* orl   %src_reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x09), src_reg, __VA_ARGS__, (void)0))
#define gen86_orb_mod_r(p_pc, gen_modrm, dst_reg, ...)   /* orb   ..., %dst_reg */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x0a), dst_reg, __VA_ARGS__, (void)0)
#define gen86_orw_mod_r(p_pc, gen_modrm, dst_reg, ...)   /* orw   ..., %dst_reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x0b), dst_reg, __VA_ARGS__, (void)0))
#define gen86_orl_mod_r(p_pc, gen_modrm, dst_reg, ...)   /* orl   ..., %dst_reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x0b), dst_reg, __VA_ARGS__, (void)0))
#define gen86_orb_imm_al(p_pc, imm)                      /* orb   $imm, %al     */ (_gen86_putb(p_pc, 0x0c), _gen86_putb(p_pc, imm))
#define gen86_orw_imm_ax(p_pc, imm)                      /* orw   $imm, %ax     */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x0d), _gen86_putw(p_pc, imm))
#define gen86_orl_imm_eax(p_pc, imm)                     /* orl   $imm, %eax    */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x0d), _gen86_putl(p_pc, imm))
#define gen86_orb_imm_mod(p_pc, gen_modrm, imm, ...)     /* orb   $imm, ...     */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x80), 1, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_orw_imm16u_mod(p_pc, gen_modrm, imm, ...)  /* orw   $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 1, __VA_ARGS__, _gen86_putw(p_pc, imm)))
#define gen86_orl_imm32s_mod(p_pc, gen_modrm, imm, ...)  /* orl   $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 1, __VA_ARGS__, _gen86_putl(p_pc, imm)))
#define gen86_orw_imm8s_mod(p_pc, gen_modrm, imm, ...)   /* orw   $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 1, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_orl_imm8s_mod(p_pc, gen_modrm, imm, ...)   /* orl   $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 1, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_orw_imm_mod(p_pc, gen_modrm, imm, ...)     /* orw   $imm, ...     */ (_gen86_fitsb(imm) ? gen86_orw_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_orw_imm16u_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#define gen86_orl_imm_mod(p_pc, gen_modrm, imm, ...)     /* orl   $imm, ...     */ (_gen86_fitsb(imm) ? gen86_orl_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_orl_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_orq_r_mod(p_pc, gen_modrm, src_reg, ...)   /* orq   %src_reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x09), src_reg, __VA_ARGS__, (void)0)
#define gen86_orq_mod_r(p_pc, gen_modrm, dst_reg, ...)   /* orq   ..., %dst_reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x0b), dst_reg, __VA_ARGS__, (void)0)
#define gen86_orq_imm_rax(p_pc, imm)                     /* orq   $imm, %rax    */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0x0d), _gen86_putsl(p_pc, imm))
#define gen86_orq_imm32s_mod(p_pc, gen_modrm, imm, ...)  /* orq   $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x81), 1, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_orq_imm8s_mod(p_pc, gen_modrm, imm, ...)   /* orq   $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x83), 1, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_orq_imm_mod(p_pc, gen_modrm, imm, ...)     /* orq   $imm, ...     */ (_gen86_fitsb(imm) ? gen86_orq_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_orq_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_adcb_r_mod(p_pc, gen_modrm, src_reg, ...)  /* adcb  %src_reg, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x10), src_reg, __VA_ARGS__, (void)0)
#define gen86_adcw_r_mod(p_pc, gen_modrm, src_reg, ...)  /* adcw  %src_reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x11), src_reg, __VA_ARGS__, (void)0))
#define gen86_adcl_r_mod(p_pc, gen_modrm, src_reg, ...)  /* adcl  %src_reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x11), src_reg, __VA_ARGS__, (void)0))
#define gen86_adcb_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* adcb  ..., %dst_reg */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x12), dst_reg, __VA_ARGS__, (void)0)
#define gen86_adcw_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* adcw  ..., %dst_reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x13), dst_reg, __VA_ARGS__, (void)0))
#define gen86_adcl_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* adcl  ..., %dst_reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x13), dst_reg, __VA_ARGS__, (void)0))
#define gen86_adcb_imm_al(p_pc, imm)                     /* adcb  $imm, %al     */ (_gen86_putb(p_pc, 0x14), _gen86_putb(p_pc, imm))
#define gen86_adcw_imm_ax(p_pc, imm)                     /* adcw  $imm, %ax     */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x15), _gen86_putw(p_pc, imm))
#define gen86_adcl_imm_eax(p_pc, imm)                    /* adcl  $imm, %eax    */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x15), _gen86_putl(p_pc, imm))
#define gen86_adcb_imm_mod(p_pc, gen_modrm, imm, ...)    /* adcb  $imm, ...     */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x80), 2, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_adcw_imm16u_mod(p_pc, gen_modrm, imm, ...) /* adcw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 2, __VA_ARGS__, _gen86_putw(p_pc, imm)))
#define gen86_adcl_imm32s_mod(p_pc, gen_modrm, imm, ...) /* adcl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 2, __VA_ARGS__, _gen86_putl(p_pc, imm)))
#define gen86_adcw_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* adcw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 2, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_adcl_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* adcl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 2, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_adcw_imm_mod(p_pc, gen_modrm, imm, ...)    /* adcw  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_adcw_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_adcw_imm16u_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#define gen86_adcl_imm_mod(p_pc, gen_modrm, imm, ...)    /* adcl  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_adcl_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_adcl_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_adcq_r_mod(p_pc, gen_modrm, src_reg, ...)  /* adcq  %src_reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x11), src_reg, __VA_ARGS__, (void)0)
#define gen86_adcq_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* adcq  ..., %dst_reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x13), dst_reg, __VA_ARGS__, (void)0)
#define gen86_adcq_imm_rax(p_pc, imm)                    /* adcq  $imm, %rax    */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0x15), _gen86_putsl(p_pc, imm))
#define gen86_adcq_imm32s_mod(p_pc, gen_modrm, imm, ...) /* adcq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x81), 2, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_adcq_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* adcq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x83), 2, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_adcq_imm_mod(p_pc, gen_modrm, imm, ...)    /* adcq  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_adcq_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_adcq_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_sbbb_r_mod(p_pc, gen_modrm, src_reg, ...)  /* sbbb  %src_reg, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x18), src_reg, __VA_ARGS__, (void)0)
#define gen86_sbbw_r_mod(p_pc, gen_modrm, src_reg, ...)  /* sbbw  %src_reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x19), src_reg, __VA_ARGS__, (void)0))
#define gen86_sbbl_r_mod(p_pc, gen_modrm, src_reg, ...)  /* sbbl  %src_reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x19), src_reg, __VA_ARGS__, (void)0))
#define gen86_sbbb_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* sbbb  ..., %dst_reg */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x1a), dst_reg, __VA_ARGS__, (void)0)
#define gen86_sbbw_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* sbbw  ..., %dst_reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x1b), dst_reg, __VA_ARGS__, (void)0))
#define gen86_sbbl_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* sbbl  ..., %dst_reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x1b), dst_reg, __VA_ARGS__, (void)0))
#define gen86_sbbb_imm_al(p_pc, imm)                     /* sbbb  $imm, %al     */ (_gen86_putb(p_pc, 0x1c), _gen86_putb(p_pc, imm))
#define gen86_sbbw_imm_ax(p_pc, imm)                     /* sbbw  $imm, %ax     */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x1d), _gen86_putw(p_pc, imm))
#define gen86_sbbl_imm_eax(p_pc, imm)                    /* sbbl  $imm, %eax    */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x1d), _gen86_putl(p_pc, imm))
#define gen86_sbbb_imm_mod(p_pc, gen_modrm, imm, ...)    /* sbbb  $imm, ...     */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x80), 3, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_sbbw_imm16u_mod(p_pc, gen_modrm, imm, ...) /* sbbw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 3, __VA_ARGS__, _gen86_putw(p_pc, imm)))
#define gen86_sbbl_imm32s_mod(p_pc, gen_modrm, imm, ...) /* sbbl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 3, __VA_ARGS__, _gen86_putl(p_pc, imm)))
#define gen86_sbbw_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* sbbw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 3, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_sbbl_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* sbbl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 3, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_sbbw_imm_mod(p_pc, gen_modrm, imm, ...)    /* sbbw  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_sbbw_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_sbbw_imm16u_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#define gen86_sbbl_imm_mod(p_pc, gen_modrm, imm, ...)    /* sbbl  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_sbbl_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_sbbl_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_sbbq_r_mod(p_pc, gen_modrm, src_reg, ...)  /* sbbq  %src_reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x19), src_reg, __VA_ARGS__, (void)0)
#define gen86_sbbq_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* sbbq  ..., %dst_reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x1b), dst_reg, __VA_ARGS__, (void)0)
#define gen86_sbbq_imm_rax(p_pc, imm)                    /* sbbq  $imm, %rax    */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0x1d), _gen86_putsl(p_pc, imm))
#define gen86_sbbq_imm32s_mod(p_pc, gen_modrm, imm, ...) /* sbbq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x81), 3, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_sbbq_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* sbbq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x83), 3, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_sbbq_imm_mod(p_pc, gen_modrm, imm, ...)    /* sbbq  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_sbbq_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_sbbq_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_andb_r_mod(p_pc, gen_modrm, src_reg, ...)  /* andb  %src_reg, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x20), src_reg, __VA_ARGS__, (void)0)
#define gen86_andw_r_mod(p_pc, gen_modrm, src_reg, ...)  /* andw  %src_reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x21), src_reg, __VA_ARGS__, (void)0))
#define gen86_andl_r_mod(p_pc, gen_modrm, src_reg, ...)  /* andl  %src_reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x21), src_reg, __VA_ARGS__, (void)0))
#define gen86_andb_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* andb  ..., %dst_reg */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x22), dst_reg, __VA_ARGS__, (void)0)
#define gen86_andw_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* andw  ..., %dst_reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x23), dst_reg, __VA_ARGS__, (void)0))
#define gen86_andl_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* andl  ..., %dst_reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x23), dst_reg, __VA_ARGS__, (void)0))
#define gen86_andb_imm_al(p_pc, imm)                     /* andb  $imm, %al     */ (_gen86_putb(p_pc, 0x24), _gen86_putb(p_pc, imm))
#define gen86_andw_imm_ax(p_pc, imm)                     /* andw  $imm, %ax     */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x25), _gen86_putw(p_pc, imm))
#define gen86_andl_imm_eax(p_pc, imm)                    /* andl  $imm, %eax    */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x25), _gen86_putl(p_pc, imm))
#define gen86_andb_imm_mod(p_pc, gen_modrm, imm, ...)    /* andb  $imm, ...     */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x80), 4, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_andw_imm16u_mod(p_pc, gen_modrm, imm, ...) /* andw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 4, __VA_ARGS__, _gen86_putw(p_pc, imm)))
#define gen86_andl_imm32s_mod(p_pc, gen_modrm, imm, ...) /* andl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 4, __VA_ARGS__, _gen86_putl(p_pc, imm)))
#define gen86_andw_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* andw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 4, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_andl_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* andl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 4, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_andw_imm_mod(p_pc, gen_modrm, imm, ...)    /* andw  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_andw_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_andw_imm16u_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#define gen86_andl_imm_mod(p_pc, gen_modrm, imm, ...)    /* andl  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_andl_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_andl_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_andq_r_mod(p_pc, gen_modrm, src_reg, ...)  /* andq  %src_reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x21), src_reg, __VA_ARGS__, (void)0)
#define gen86_andq_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* andq  ..., %dst_reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x23), dst_reg, __VA_ARGS__, (void)0)
#define gen86_andq_imm_rax(p_pc, imm)                    /* andq  $imm, %rax    */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0x25), _gen86_putsl(p_pc, imm))
#define gen86_andq_imm32s_mod(p_pc, gen_modrm, imm, ...) /* andq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x81), 4, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_andq_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* andq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x83), 4, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_andq_imm_mod(p_pc, gen_modrm, imm, ...)    /* andq  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_andq_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_andq_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_subb_r_mod(p_pc, gen_modrm, src_reg, ...)  /* subb  %src_reg, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x28), src_reg, __VA_ARGS__, (void)0)
#define gen86_subw_r_mod(p_pc, gen_modrm, src_reg, ...)  /* subw  %src_reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x29), src_reg, __VA_ARGS__, (void)0))
#define gen86_subl_r_mod(p_pc, gen_modrm, src_reg, ...)  /* subl  %src_reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x29), src_reg, __VA_ARGS__, (void)0))
#define gen86_subb_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* subb  ..., %dst_reg */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x2a), dst_reg, __VA_ARGS__, (void)0)
#define gen86_subw_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* subw  ..., %dst_reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x2b), dst_reg, __VA_ARGS__, (void)0))
#define gen86_subl_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* subl  ..., %dst_reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x2b), dst_reg, __VA_ARGS__, (void)0))
#define gen86_subb_imm_al(p_pc, imm)                     /* subb  $imm, %al     */ (_gen86_putb(p_pc, 0x2c), _gen86_putb(p_pc, imm))
#define gen86_subw_imm_ax(p_pc, imm)                     /* subw  $imm, %ax     */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x2d), _gen86_putw(p_pc, imm))
#define gen86_subl_imm_eax(p_pc, imm)                    /* subl  $imm, %eax    */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x2d), _gen86_putl(p_pc, imm))
#define gen86_subb_imm_mod(p_pc, gen_modrm, imm, ...)    /* subb  $imm, ...     */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x80), 5, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_subw_imm16u_mod(p_pc, gen_modrm, imm, ...) /* subw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 5, __VA_ARGS__, _gen86_putw(p_pc, imm)))
#define gen86_subl_imm32s_mod(p_pc, gen_modrm, imm, ...) /* subl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 5, __VA_ARGS__, _gen86_putl(p_pc, imm)))
#define gen86_subw_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* subw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 5, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_subl_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* subl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 5, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_subw_imm_mod(p_pc, gen_modrm, imm, ...)    /* subw  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_subw_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_subw_imm16u_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#define gen86_subl_imm_mod(p_pc, gen_modrm, imm, ...)    /* subl  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_subl_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_subl_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_subq_r_mod(p_pc, gen_modrm, src_reg, ...)  /* subq  %src_reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x29), src_reg, __VA_ARGS__, (void)0)
#define gen86_subq_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* subq  ..., %dst_reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x2b), dst_reg, __VA_ARGS__, (void)0)
#define gen86_subq_imm_rax(p_pc, imm)                    /* subq  $imm, %rax    */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0x2d), _gen86_putsl(p_pc, imm))
#define gen86_subq_imm32s_mod(p_pc, gen_modrm, imm, ...) /* subq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x81), 5, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_subq_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* subq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x83), 5, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_subq_imm_mod(p_pc, gen_modrm, imm, ...)    /* subq  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_subq_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_subq_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_xorb_r_mod(p_pc, gen_modrm, src_reg, ...)  /* xorb  %src_reg, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x30), src_reg, __VA_ARGS__, (void)0)
#define gen86_xorw_r_mod(p_pc, gen_modrm, src_reg, ...)  /* xorw  %src_reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x31), src_reg, __VA_ARGS__, (void)0))
#define gen86_xorl_r_mod(p_pc, gen_modrm, src_reg, ...)  /* xorl  %src_reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x31), src_reg, __VA_ARGS__, (void)0))
#define gen86_xorb_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* xorb  ..., %dst_reg */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x32), dst_reg, __VA_ARGS__, (void)0)
#define gen86_xorw_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* xorw  ..., %dst_reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x33), dst_reg, __VA_ARGS__, (void)0))
#define gen86_xorl_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* xorl  ..., %dst_reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x33), dst_reg, __VA_ARGS__, (void)0))
#define gen86_xorb_imm_al(p_pc, imm)                     /* xorb  $imm, %al     */ (_gen86_putb(p_pc, 0x34), _gen86_putb(p_pc, imm))
#define gen86_xorw_imm_ax(p_pc, imm)                     /* xorw  $imm, %ax     */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x35), _gen86_putw(p_pc, imm))
#define gen86_xorl_imm_eax(p_pc, imm)                    /* xorl  $imm, %eax    */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x35), _gen86_putl(p_pc, imm))
#define gen86_xorb_imm_mod(p_pc, gen_modrm, imm, ...)    /* xorb  $imm, ...     */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x80), 6, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_xorw_imm16u_mod(p_pc, gen_modrm, imm, ...) /* xorw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 6, __VA_ARGS__, _gen86_putw(p_pc, imm)))
#define gen86_xorl_imm32s_mod(p_pc, gen_modrm, imm, ...) /* xorl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 6, __VA_ARGS__, _gen86_putl(p_pc, imm)))
#define gen86_xorw_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* xorw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 6, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_xorl_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* xorl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 6, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_xorw_imm_mod(p_pc, gen_modrm, imm, ...)    /* xorw  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_xorw_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_xorw_imm16u_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#define gen86_xorl_imm_mod(p_pc, gen_modrm, imm, ...)    /* xorl  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_xorl_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_xorl_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_xorq_r_mod(p_pc, gen_modrm, src_reg, ...)  /* xorq  %src_reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x31), src_reg, __VA_ARGS__, (void)0)
#define gen86_xorq_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* xorq  ..., %dst_reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x33), dst_reg, __VA_ARGS__, (void)0)
#define gen86_xorq_imm_rax(p_pc, imm)                    /* xorq  $imm, %rax    */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0x35), _gen86_putsl(p_pc, imm))
#define gen86_xorq_imm32s_mod(p_pc, gen_modrm, imm, ...) /* xorq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x81), 6, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_xorq_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* xorq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x83), 6, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_xorq_imm_mod(p_pc, gen_modrm, imm, ...)    /* xorq  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_xorq_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_xorq_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_cmpb_r_mod(p_pc, gen_modrm, src_reg, ...)  /* cmpb  %src_reg, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x38), src_reg, __VA_ARGS__, (void)0)
#define gen86_cmpw_r_mod(p_pc, gen_modrm, src_reg, ...)  /* cmpw  %src_reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x39), src_reg, __VA_ARGS__, (void)0))
#define gen86_cmpl_r_mod(p_pc, gen_modrm, src_reg, ...)  /* cmpl  %src_reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x39), src_reg, __VA_ARGS__, (void)0))
#define gen86_cmpb_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* cmpb  ..., %dst_reg */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x3a), dst_reg, __VA_ARGS__, (void)0)
#define gen86_cmpw_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* cmpw  ..., %dst_reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x3b), dst_reg, __VA_ARGS__, (void)0))
#define gen86_cmpl_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* cmpl  ..., %dst_reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x3b), dst_reg, __VA_ARGS__, (void)0))
#define gen86_cmpb_imm_al(p_pc, imm)                     /* cmpb  $imm, %al     */ (_gen86_putb(p_pc, 0x3c), _gen86_putb(p_pc, imm))
#define gen86_cmpw_imm_ax(p_pc, imm)                     /* cmpw  $imm, %ax     */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x3d), _gen86_putw(p_pc, imm))
#define gen86_cmpl_imm_eax(p_pc, imm)                    /* cmpl  $imm, %eax    */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x3d), _gen86_putl(p_pc, imm))
#define gen86_cmpb_imm_mod(p_pc, gen_modrm, imm, ...)    /* cmpb  $imm, ...     */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x80), 7, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_cmpw_imm16u_mod(p_pc, gen_modrm, imm, ...) /* cmpw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 7, __VA_ARGS__, _gen86_putw(p_pc, imm)))
#define gen86_cmpl_imm32s_mod(p_pc, gen_modrm, imm, ...) /* cmpl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x81), 7, __VA_ARGS__, _gen86_putl(p_pc, imm)))
#define gen86_cmpw_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* cmpw  $imm, ...     */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 7, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_cmpl_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* cmpl  $imm, ...     */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x83), 7, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_cmpw_imm_mod(p_pc, gen_modrm, imm, ...)    /* cmpw  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_cmpw_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_cmpw_imm16u_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#define gen86_cmpl_imm_mod(p_pc, gen_modrm, imm, ...)    /* cmpl  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_cmpl_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_cmpl_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_cmpq_r_mod(p_pc, gen_modrm, src_reg, ...)  /* cmpq  %src_reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x39), src_reg, __VA_ARGS__, (void)0)
#define gen86_cmpq_mod_r(p_pc, gen_modrm, dst_reg, ...)  /* cmpq  ..., %dst_reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x3b), dst_reg, __VA_ARGS__, (void)0)
#define gen86_cmpq_imm_rax(p_pc, imm)                    /* cmpq  $imm, %rax    */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0x3d), _gen86_putsl(p_pc, imm))
#define gen86_cmpq_imm32s_mod(p_pc, gen_modrm, imm, ...) /* cmpq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x81), 7, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_cmpq_imm8s_mod(p_pc, gen_modrm, imm, ...)  /* cmpq  $imm, ...     */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x83), 7, __VA_ARGS__, _gen86_putsb(p_pc, imm))
#define gen86_cmpq_imm_mod(p_pc, gen_modrm, imm, ...)    /* cmpq  $imm, ...     */ (_gen86_fitsb(imm) ? gen86_cmpq_imm8s_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : gen86_cmpq_imm32s_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#endif /* LIBGEN86_TARGET_BITS == 64 */
/*[[[end]]]*/

#define gen86_pushw_es(p_pc) /* pushw %es */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x06))
#define gen86_pushP_es(p_pc) /* pushl %es */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x06))
#define gen86_popw_es(p_pc)  /* popw  %es */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x07))
#define gen86_popP_es(p_pc)  /* popl  %es */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x07))
#define gen86_pushw_cs(p_pc) /* pushw %cs */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x0e))
#define gen86_pushP_cs(p_pc) /* pushl %cs */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x0e))
#define gen86_pushw_ss(p_pc) /* pushw %ss */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x16))
#define gen86_pushP_ss(p_pc) /* pushl %ss */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x16))
#define gen86_popw_ss(p_pc)  /* popw  %ss */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x17))
#define gen86_popP_ss(p_pc)  /* popl  %ss */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x17))
#define gen86_pushw_ds(p_pc) /* pushw %ds */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x1e))
#define gen86_pushP_ds(p_pc) /* pushl %ds */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x1e))
#define gen86_popw_ds(p_pc)  /* popw  %ds */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x1f))
#define gen86_popP_ds(p_pc)  /* popl  %ds */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x1f))

#if LIBGEN86_TARGET_BITS == 64
#define gen86_pushq_es gen86_pushP_es
#define gen86_popq_es  gen86_popP_es
#define gen86_pushq_cs gen86_pushP_cs
#define gen86_pushq_ss gen86_pushP_ss
#define gen86_popq_ss  gen86_popP_ss
#define gen86_pushq_ds gen86_pushP_ds
#define gen86_popq_ds  gen86_popP_ds
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_pushl_es gen86_pushP_es
#define gen86_popl_es  gen86_popP_es
#define gen86_pushl_cs gen86_pushP_cs
#define gen86_pushl_ss gen86_pushP_ss
#define gen86_popl_ss  gen86_popP_ss
#define gen86_pushl_ds gen86_pushP_ds
#define gen86_popl_ds  gen86_popP_ds
#endif /* LIBGEN86_TARGET_BITS != 64 */

#define gen86_daa(p_pc) /* daa */ (_gen86_putb(p_pc, 0x27))
#define gen86_das(p_pc) /* das */ (_gen86_putb(p_pc, 0x2f))
#define gen86_aaa(p_pc) /* aaa */ (_gen86_putb(p_pc, 0x37))
#define gen86_aas(p_pc) /* aas */ (_gen86_putb(p_pc, 0x3f))

#if LIBGEN86_TARGET_BITS == 64
#define gen86_incw_r(p_pc, reg) /* incw %reg */ gen86_incw_mod(p_pc, gen86_modrm_r, reg)
#define gen86_incl_r(p_pc, reg) /* incl %reg */ gen86_incl_mod(p_pc, gen86_modrm_r, reg)
#define gen86_incq_r(p_pc, reg) /* incq %reg */ gen86_incq_mod(p_pc, gen86_modrm_r, reg)
#define gen86_decw_r(p_pc, reg) /* decw %reg */ gen86_decw_mod(p_pc, gen86_modrm_r, reg)
#define gen86_decl_r(p_pc, reg) /* decl %reg */ gen86_decl_mod(p_pc, gen86_modrm_r, reg)
#define gen86_decq_r(p_pc, reg) /* decq %reg */ gen86_decq_mod(p_pc, gen86_modrm_r, reg)
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_incw_r(p_pc, reg) /* incw %reg */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x40 + (reg)))
#define gen86_decw_r(p_pc, reg) /* decw %reg */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x48 + (reg)))
#define gen86_incl_r(p_pc, reg) /* incl %reg */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x40 + (reg)))
#define gen86_decl_r(p_pc, reg) /* decl %reg */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x48 + (reg)))
#endif /* LIBGEN86_TARGET_BITS != 64 */

#if LIBGEN86_TARGET_BITS == 64
#define gen86_pushw_r(p_pc, reg) /* pushw %reg */ (_gen86_pfx16_(p_pc) !((reg) & 8) || (_gen86_putb(p_pc, 0x40 | GEN86_REX_B), 0), _gen86_putb(p_pc, 0x50 + ((reg) & 7)))
#define gen86_pushq_r(p_pc, reg) /* pushq %reg */ (_gen86_pfx32_(p_pc) !((reg) & 8) || (_gen86_putb(p_pc, 0x40 | GEN86_REX_B), 0), _gen86_putb(p_pc, 0x50 + ((reg) & 7)))
#define gen86_popw_r(p_pc, reg)  /* popw  %reg */ (_gen86_pfx16_(p_pc) !((reg) & 8) || (_gen86_putb(p_pc, 0x40 | GEN86_REX_B), 0), _gen86_putb(p_pc, 0x58 + ((reg) & 7)))
#define gen86_popq_r(p_pc, reg)  /* popq  %reg */ (_gen86_pfx32_(p_pc) !((reg) & 8) || (_gen86_putb(p_pc, 0x40 | GEN86_REX_B), 0), _gen86_putb(p_pc, 0x58 + ((reg) & 7)))
#define gen86_movslq_mod_r(p_pc, gen_modrm, dst_reg, ...) /* movslq  ..., %dst_reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x63), src_reg, __VA_ARGS__, (void)0)
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_pushw_r(p_pc, reg) /* pushw %reg */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x50 + (reg)))
#define gen86_pushl_r(p_pc, reg) /* pushl %reg */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x50 + (reg)))
#define gen86_popw_r(p_pc, reg)  /* popw  %reg */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x58 + (reg)))
#define gen86_popl_r(p_pc, reg)  /* popl  %reg */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x58 + (reg)))
#define gen86_pushaw(p_pc)       /* pushaw     */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x60))
#define gen86_pushal(p_pc)       /* pushal     */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x60))
#define gen86_popaw(p_pc)        /* popaw      */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x61))
#define gen86_popal(p_pc)        /* popal      */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x61))
#define gen86_boundw(p_pc, gen_modrm, test_reg, ...) /* boundw ..., %test_reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x62), test_reg, __VA_ARGS__, (void)0))
#define gen86_boundl(p_pc, gen_modrm, test_reg, ...) /* boundl ..., %test_reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x62), test_reg, __VA_ARGS__, (void)0))
#define gen86_arpl(p_pc, gen_modrm, reg, ...)        /* arpl   %reg, ...      */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x63), reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS != 64 */

#define gen86_fs(p_pc) /* %fs: # Prefix */ _gen86_putb(p_pc, 0x64)
#define gen86_gs(p_pc) /* %gs: # Prefix */ _gen86_putb(p_pc, 0x65)

#define gen86_pushw_imm(p_pc, imm)   /* pushw $imm */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x68), _gen86_putw(p_pc, imm))
#define gen86_pushl_imm(p_pc, imm)   /* pushl $imm */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x68), _gen86_putl(p_pc, imm))
#define gen86_pushw_imm8s(p_pc, imm) /* pushw $imm */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x6a), _gen86_putsb(p_pc, imm))
#define gen86_pushl_imm8s(p_pc, imm) /* pushl $imm */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x6a), _gen86_putsb(p_pc, imm))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_pushq_imm(p_pc, imm)   /* pushq $imm */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0x68), _gen86_putsl(p_pc, imm))
#define gen86_pushq_imm8s(p_pc, imm) /* pushq $imm */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0x6a), _gen86_putsb(p_pc, imm))
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_imulw_imm_mod_r(p_pc, gen_modrm, imm, dst_reg, ...)   /* imulw $imm, ..., %dst_reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x69), dst_reg, __VA_ARGS__, _gen86_putw(p_pc, imm)))
#define gen86_imulw_imm8s_mod_r(p_pc, gen_modrm, imm, dst_reg, ...) /* imulw $imm, ..., %dst_reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x6b), dst_reg, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#define gen86_imull_imm_mod_r(p_pc, gen_modrm, imm, dst_reg, ...)   /* imull $imm, ..., %dst_reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x69), dst_reg, __VA_ARGS__, _gen86_putl(p_pc, imm)))
#define gen86_imull_imm8s_mod_r(p_pc, gen_modrm, imm, dst_reg, ...) /* imull $imm, ..., %dst_reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x6b), dst_reg, __VA_ARGS__, _gen86_putsb(p_pc, imm)))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_imulq_imm_mod_r(p_pc, gen_modrm, imm, dst_reg, ...)   /* imulq $imm, ..., %dst_reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x69), dst_reg, __VA_ARGS__, _gen86_putsl(p_pc, imm))
#define gen86_imulq_imm8s_mod_r(p_pc, gen_modrm, imm, dst_reg, ...) /* imulq $imm, ..., %dst_reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x6b), dst_reg, __VA_ARGS__, _gen86_putssb(p_pc, imm))
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_insb(p_pc)      /* insb      */ _gen86_putb(p_pc, 0x6c)
#define gen86_insw(p_pc)      /* insw      */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x6d))
#define gen86_insl(p_pc)      /* insl      */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x6d))
#define gen86_rep_insb(p_pc)  /* rep insb  */ (_gen86_putb(p_pc, 0xf3), _gen86_putb(p_pc, 0x6c))
#define gen86_rep_insw(p_pc)  /* rep insw  */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x6d))
#define gen86_rep_insl(p_pc)  /* rep insl  */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x6d))
#define gen86_outsb(p_pc)     /* outsb     */ _gen86_putb(p_pc, 0x6e)
#define gen86_outsw(p_pc)     /* outsw     */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x6f))
#define gen86_outsl(p_pc)     /* outsl     */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x6f))
#define gen86_rep_outsb(p_pc) /* rep outsb */ (_gen86_putb(p_pc, 0xf3), _gen86_putb(p_pc, 0x6e))
#define gen86_rep_outsw(p_pc) /* rep outsw */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x6f))
#define gen86_rep_outsl(p_pc) /* rep outsl */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x6f))

/* Conditional jump test codes */
#define GEN86_CC_O   0  /* Overflow */
#define GEN86_CC_NO  1  /* Not Overflow */
#define GEN86_CC_B   2  /* Below (unsigned) */
#define GEN86_CC_C   2  /* Carry */
#define GEN86_CC_NAE 2  /* Not Above or Equal (unsigned) */
#define GEN86_CC_AE  3  /* Above or Equal (unsigned) */
#define GEN86_CC_NB  3  /* Not Below (unsigned) */
#define GEN86_CC_NC  3  /* Not Carry */
#define GEN86_CC_Z   4  /* Zero */
#define GEN86_CC_E   4  /* Equal */
#define GEN86_CC_NZ  5  /* Not Zero */
#define GEN86_CC_NE  5  /* Not Equal */
#define GEN86_CC_BE  6  /* Below or Equal (unsigned) */
#define GEN86_CC_NA  6  /* Not Above (unsigned) */
#define GEN86_CC_A   7  /* Above (unsigned) */
#define GEN86_CC_NBE 7  /* Not Below or Equal (unsigned) */
#define GEN86_CC_S   8  /* Signed (< 0) */
#define GEN86_CC_NS  9  /* Not Signed (>= 0) */
#define GEN86_CC_P   10 /* Partity     (`(POPCOUNT & 1) == 0') */
#define GEN86_CC_PE  10 /* Parity Even (`(POPCOUNT & 1) == 0') */
#define GEN86_CC_NP  11 /* Not Partity (`(POPCOUNT & 1) != 0') */
#define GEN86_CC_PO  11 /* Partity Odd (`(POPCOUNT & 1) != 0') */
#define GEN86_CC_L   12 /* Less (signed) */
#define GEN86_CC_NGE 12 /* Not Greater or Equal (signed) */
#define GEN86_CC_GE  13 /* Greater or Equal (signed) */
#define GEN86_CC_NL  13 /* Not Less (signed) */
#define GEN86_CC_LE  14 /* Less or Equal (signed) */
#define GEN86_CC_NG  14 /* Not Greater (signed) */
#define GEN86_CC_G   15 /* Greater (signed) */
#define GEN86_CC_NLE 15 /* Not Less or Equal (signed) */

/* Conditional jumps
 * @param: cc: One of `GEN86_CC_*' */
#define gen86_jcc8(p_pc, cc, addr)          /* jcc8 addr          */ (_gen86_putb(p_pc, 0x70 + (cc)), _gen86_putsb_pcrel(p_pc, addr))
#define gen86_jcc8_offset(p_pc, cc, offset) /* jcc8 1f+offset; 1: */ (_gen86_putb(p_pc, 0x70 + (cc)), _gen86_putsb(p_pc, offset))
#if LIBGEN86_TARGET_BITS == 16
#define gen86_jccP(p_pc, cc, addr)          /* jccP addr          */ (_gen86_putb2(p_pc, 0x0f, 0x80 + (cc)), _gen86_putsw_pcrel(p_pc, addr))
#define gen86_jccP_offset(p_pc, cc, offset) /* jccP 1f+offset; 1: */ (_gen86_putb2(p_pc, 0x0f, 0x80 + (cc)), _gen86_putsw(p_pc, offset))
#define gen86_jccw                          gen86_jccP
#define gen86_jccw_offset                   gen86_jccP_offset
#else /* LIBGEN86_TARGET_BITS == 16 */
#define gen86_jccP(p_pc, cc, addr)          /* jccP addr          */ (_gen86_putb2(p_pc, 0x0f, 0x80 + (cc)), _gen86_putsl_pcrel(p_pc, offset))
#define gen86_jccP_offset(p_pc, cc, offset) /* jccP 1f+offset; 1: */ (_gen86_putb2(p_pc, 0x0f, 0x80 + (cc)), _gen86_putsl(p_pc, offset))
#define gen86_jccl                          gen86_jccP
#define gen86_jccl_offset                   gen86_jccP_offset
#endif /* LIBGEN86_TARGET_BITS != 16 */
#define gen86_jcc(p_pc, cc, addr)                                                                         \
	__XBLOCK({                                                                                            \
		__INT32_TYPE__ __g86_joff = (__INT32_TYPE__)(__INTPTR_TYPE__)((__UINTPTR_TYPE__)(addr) -          \
		                                                              ((__UINTPTR_TYPE__)(*(p_pc)) + 2)); \
		if (_gen86_fitsb(__g86_joff)) {                                                                   \
			gen86_jcc8_offset(p_pc, cc, __g86_joff);                                                      \
		} else {                                                                                          \
			__g86_joff -= _GEN86_JMPP_EXTRA;                                                              \
			gen86_jccP_offset(p_pc, cc, __g86_joff);                                                      \
		}                                                                                                 \
		(void)0;                                                                                          \
	})
#define gen86_jcc_offset(p_pc, cc, offset) \
	(_gen86_fitsb(offset)                  \
	 ? gen86_jcc8_offset(p_pc, cc, offset) \
	 : gen86_jccP_offset(p_pc, cc, offset))

#define gen86_testb_r_mod(p_pc, gen_modrm, r1, ...) /* testb %r1, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x84), r1, __VA_ARGS__, (void)0)
#define gen86_testw_r_mod(p_pc, gen_modrm, r1, ...) /* testw %r1, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x85), r1, __VA_ARGS__, (void)0))
#define gen86_testl_r_mod(p_pc, gen_modrm, r1, ...) /* testl %r1, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x85), r1, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_testq_r_mod(p_pc, gen_modrm, r1, ...) /* testq %r1, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x85), r1, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_xchgb_r_mod(p_pc, gen_modrm, r1, ...) /* xchgb %r1, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x86), r1, __VA_ARGS__, (void)0)
#define gen86_xchgw_r_mod(p_pc, gen_modrm, r1, ...) /* xchgw %r1, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x87), r1, __VA_ARGS__, (void)0))
#define gen86_xchgl_r_mod(p_pc, gen_modrm, r1, ...) /* xchgl %r1, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x87), r1, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_xchgq_r_mod(p_pc, gen_modrm, r1, ...) /* xchgq %r1, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x87), r1, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_movb_r_mod(p_pc, gen_modrm, src_reg, ...) /* movb %src_reg, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x88), src_reg, __VA_ARGS__, (void)0)
#define gen86_movw_r_mod(p_pc, gen_modrm, src_reg, ...) /* movw %src_reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x89), src_reg, __VA_ARGS__, (void)0))
#define gen86_movl_r_mod(p_pc, gen_modrm, src_reg, ...) /* movl %src_reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x89), src_reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_movq_r_mod(p_pc, gen_modrm, src_reg, ...) /* movq %src_reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x89), src_reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_movb_mod_r(p_pc, gen_modrm, dst_reg, ...) /* movb ..., %dst_reg */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x8a), dst_reg, __VA_ARGS__, (void)0)
#define gen86_movw_mod_r(p_pc, gen_modrm, dst_reg, ...) /* movw ..., %dst_reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x8b), dst_reg, __VA_ARGS__, (void)0))
#define gen86_movl_mod_r(p_pc, gen_modrm, dst_reg, ...) /* movl ..., %dst_reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x8b), dst_reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_movq_mod_r(p_pc, gen_modrm, dst_reg, ...) /* movq ..., %dst_reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x8b), dst_reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_movw_sgr_mod(p_pc, gen_modrm, src_sgreg, ...) /* movw %src_sgreg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x8c), src_sgreg, __VA_ARGS__, (void)0))
#define gen86_movl_sgr_mod(p_pc, gen_modrm, src_sgreg, ...) /* movl %src_sgreg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x8c), src_sgreg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_movq_sgr_mod(p_pc, gen_modrm, src_sgreg, ...) /* movq %src_sgreg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x8c), src_sgreg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_movw_mod_sgr(p_pc, gen_modrm, dst_sgreg, ...) /* movw ..., %dst_sgreg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x8e), dst_sgreg, __VA_ARGS__, (void)0))
#define gen86_movl_mod_sgr(p_pc, gen_modrm, dst_sgreg, ...) /* movl ..., %dst_sgreg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x8e), dst_sgreg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_movq_mod_sgr(p_pc, gen_modrm, dst_sgreg, ...) /* movq ..., %dst_sgreg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x8e), dst_sgreg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_leaw_mod_r(p_pc, gen_modrm, dst_reg, ...) /* leaw ..., %dst_reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x8d), dst_reg, __VA_ARGS__, (void)0))
#define gen86_leal_mod_r(p_pc, gen_modrm, dst_reg, ...) /* leal ..., %dst_reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x8d), dst_reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_leaq_mod_r(p_pc, gen_modrm, dst_reg, ...) /* leaq ..., %dst_reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x8d), dst_reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_popw_mod(p_pc, gen_modrm, ...) /* popw ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x8f), 0, __VA_ARGS__, (void)0))
#define gen86_popl_mod(p_pc, gen_modrm, ...) /* popl ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0x8f), 0, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_popq_mod(p_pc, gen_modrm, ...) /* popq ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0x8f), 0, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_nop(p_pc)   _gen86_putb(p_pc, 0x90)
#define gen86_pause(p_pc) (_gen86_putb(p_pc, 0xf3), _gen86_putb(p_pc, 0x90))

#if LIBGEN86_TARGET_BITS == 64
#define gen86_xchgw_r_ax(p_pc, reg)  /* xchgw %reg, %ax  */ (_gen86_pfx16_(p_pc) !((reg) & 8) || (_gen86_putb(p_pc, 0x40 | GEN86_REX_B), 0), _gen86_putb(p_pc, 0x90 + (reg)&7))
#define gen86_xchgl_r_eax(p_pc, reg) /* xchgl %reg, %eax */ (_gen86_pfx32_(p_pc) !((reg) & 8) || (_gen86_putb(p_pc, 0x40 | GEN86_REX_B), 0), _gen86_putb(p_pc, 0x90 + (reg)&7))
#define gen86_xchgq_r_rax(p_pc, reg) /* xchgq %reg, %rax */ (_gen86_putb(p_pc, 0x40 | ((reg) & 8 ? GEN86_REX_B : 0) | GEN86_REX_W), _gen86_putb(p_pc, 0x90 + (reg)&7))
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_xchgw_r_ax(p_pc, reg)  /* xchgw %reg, %ax  */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x90 + (reg)))
#define gen86_xchgl_r_eax(p_pc, reg) /* xchgl %reg, %eax */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x90 + (reg)))
#endif /* LIBGEN86_TARGET_BITS != 64 */

#define gen86_cbw(p_pc) /* cbw */ _gen86_putb(p_pc, 0x98)
#define gen86_cwd(p_pc) /* cwd */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x99))
#define gen86_cdq(p_pc) /* cdq */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x99))

#define gen86_lcallw(p_pc, segment, offset) /* lcallw $segment:$offset */ (_gen86_adr16_(p_pc) _gen86_putb(p_pc, 0x9a) _gen86_putw(p_pc, offset), _gen86_putw(p_pc, segment))
#define gen86_lcalll(p_pc, segment, offset) /* lcalll $segment:$offset */ (_gen86_adr32_(p_pc) _gen86_putb(p_pc, 0x9a) _gen86_putl(p_pc, offset), _gen86_putw(p_pc, segment))

#define gen86_pushfw(p_pc) /* pushfw */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x9c))
#define gen86_popfw(p_pc)  /* popfw  */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0x9d))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_pushfq(p_pc) /* pushfq */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x9c))
#define gen86_popfq(p_pc)  /* popfq  */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x9d))
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_pushfl(p_pc) /* pushfl */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x9c))
#define gen86_popfl(p_pc)  /* popfl  */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0x9d))
#endif /* LIBGEN86_TARGET_BITS != 64 */

#define gen86_sahf(p_pc) /* sahf */ _gen86_putb(p_pc, 0x9e)
#define gen86_lahf(p_pc) /* lahf */ _gen86_putb(p_pc, 0x9f)

#define gen86_movsb(p_pc)       /* movsb       */ _gen86_putb(p_pc, 0xa4)
#define gen86_movsw(p_pc)       /* movsw       */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xa5))
#define gen86_movsl(p_pc)       /* movsl       */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xa5))
#define gen86_rep_movsb(p_pc)   /* rep movsb   */ (_gen86_putb(p_pc, 0xf3), _gen86_putb(p_pc, 0xa4))
#define gen86_rep_movsw(p_pc)   /* rep movsw   */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xa5))
#define gen86_rep_movsl(p_pc)   /* rep movsl   */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xa5))
#define gen86_stosb(p_pc)       /* stosb       */ _gen86_putb(p_pc, 0xaa)
#define gen86_stosw(p_pc)       /* stosw       */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xab))
#define gen86_stosl(p_pc)       /* stosl       */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xab))
#define gen86_rep_stosb(p_pc)   /* rep stosb   */ (_gen86_putb(p_pc, 0xf3), _gen86_putb(p_pc, 0xaa))
#define gen86_rep_stosw(p_pc)   /* rep stosw   */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xab))
#define gen86_rep_stosl(p_pc)   /* rep stosl   */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xab))
#define gen86_lodsb(p_pc)       /* lodsb       */ _gen86_putb(p_pc, 0xac)
#define gen86_lodsw(p_pc)       /* lodsw       */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xad))
#define gen86_lodsl(p_pc)       /* lodsl       */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xad))
#define gen86_rep_lodsb(p_pc)   /* rep lodsb   */ (_gen86_putb(p_pc, 0xf3), _gen86_putb(p_pc, 0xac))
#define gen86_rep_lodsw(p_pc)   /* rep lodsw   */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xad))
#define gen86_rep_lodsl(p_pc)   /* rep lodsl   */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xad))
#define gen86_cmpsb(p_pc)       /* cmpsb       */ _gen86_putb(p_pc, 0xa6)
#define gen86_cmpsw(p_pc)       /* cmpsw       */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xa7))
#define gen86_cmpsl(p_pc)       /* cmpsl       */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xa7))
#define gen86_repe_cmpsb(p_pc)  /* repe cmpsb  */ (_gen86_putb(p_pc, 0xf3), _gen86_putb(p_pc, 0xa6))
#define gen86_repe_cmpsw(p_pc)  /* repe cmpsw  */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xa7))
#define gen86_repe_cmpsl(p_pc)  /* repe cmpsl  */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xa7))
#define gen86_repne_cmpsb(p_pc) /* repne cmpsb */ (_gen86_putb(p_pc, 0xf2), _gen86_putb(p_pc, 0xa6))
#define gen86_repne_cmpsw(p_pc) /* repne cmpsw */ (_gen86_putb(p_pc, 0xf2), _gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xa7))
#define gen86_repne_cmpsl(p_pc) /* repne cmpsl */ (_gen86_putb(p_pc, 0xf2), _gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xa7))
#define gen86_scasb(p_pc)       /* scasb       */ _gen86_putb(p_pc, 0xae)
#define gen86_scasw(p_pc)       /* scasw       */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xaf))
#define gen86_scasl(p_pc)       /* scasl       */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xaf))
#define gen86_repe_scasb(p_pc)  /* repe scasb  */ (_gen86_putb(p_pc, 0xf3), _gen86_putb(p_pc, 0xae))
#define gen86_repe_scasw(p_pc)  /* repe scasw  */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xaf))
#define gen86_repe_scasl(p_pc)  /* repe scasl  */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xaf))
#define gen86_repne_scasb(p_pc) /* repne scasb */ (_gen86_putb(p_pc, 0xf2), _gen86_putb(p_pc, 0xae))
#define gen86_repne_scasw(p_pc) /* repne scasw */ (_gen86_putb(p_pc, 0xf2), _gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xaf))
#define gen86_repne_scasl(p_pc) /* repne scasl */ (_gen86_putb(p_pc, 0xf2), _gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xaf))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_movsq(p_pc)       /* movsq       */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0xa5))
#define gen86_rep_movsq(p_pc)   /* rep movsq   */ (_gen86_putb(p_pc, 0xf3), _gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0xa5))
#define gen86_stosq(p_pc)       /* stosq       */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0xab))
#define gen86_rep_stosq(p_pc)   /* rep stosq   */ (_gen86_putb(p_pc, 0xf3), _gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0xab))
#define gen86_lodsq(p_pc)       /* lodsq       */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0xad))
#define gen86_rep_lodsq(p_pc)   /* rep lodsq   */ (_gen86_putb(p_pc, 0xf3), _gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0xad))
#define gen86_cmpsq(p_pc)       /* cmpsq       */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0xa7))
#define gen86_repe_cmpsq(p_pc)  /* repe cmpsq  */ (_gen86_putb(p_pc, 0xf3), _gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0xa7))
#define gen86_repne_cmpsq(p_pc) /* repne cmpsq */ (_gen86_putb(p_pc, 0xf2), _gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0xa7))
#define gen86_scasq(p_pc)       /* scasq       */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0xaf))
#define gen86_repe_scasq(p_pc)  /* repe scasq  */ (_gen86_putb(p_pc, 0xf3), _gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0xaf))
#define gen86_repne_scasq(p_pc) /* repne scasq */ (_gen86_putb(p_pc, 0xf2), _gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0xaf))
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_testb_imm_al(p_pc, imm)   /* testb $imm, %al  */ (_gen86_putb(p_pc, 0xa8), _gen86_putb(p_pc, imm))
#define _gen86_testw_imm_ax(p_pc, imm)  /* testw $imm, %ax  */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xa9), _gen86_putw(p_pc, imm))
#define gen86_testw_imm_ax(p_pc, imm)   /* testw $imm, %ax  */ ((__UINT16_TYPE__)(imm) <= __UINT8_C(0xff) ? gen86_testb_imm_al(p_pc, imm) : _gen86_testw_imm_ax(p_pc, imm))
#define _gen86_testl_imm_eax(p_pc, imm) /* testl $imm, %eax */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xa9), _gen86_putl(p_pc, imm))
#define gen86_testl_imm_eax(p_pc, imm)  /* testl $imm, %eax */ ((__UINT32_TYPE__)(imm) <= __UINT16_C(0xffff) ? gen86_testw_imm_ax(p_pc, imm) : _gen86_testl_imm_eax(p_pc, imm))
#if LIBGEN86_TARGET_BITS == 64
#define _gen86_testq_imm_rax(p_pc, imm) /* testq $imm, %rax */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W), _gen86_putb(p_pc, 0xa9), _gen86_putsl(p_pc, imm))
#define gen86_testq_imm_rax(p_pc, imm)  /* testq $imm, %rax */ ((__UINT32_TYPE__)(imm) <= __UINT32_C(0x7fffffff) ? gen86_testl_imm_eax(p_pc, imm) : _gen86_testq_imm_rax(p_pc, imm))
#endif /* LIBGEN86_TARGET_BITS == 64 */


#if LIBGEN86_TARGET_BITS == 64
#define gen86_movb_imm_r(p_pc, imm, reg)   /* movb   $imm, %reg */ (!((reg) & 0x18) || (_gen86_putb(p_pc, 0x40 | ((reg)&8 ? GEN86_REX_B : 0)), 0), _gen86_putb(p_pc, 0xb0 + (reg)&7), _gen86_putb(p_pc, imm))
#define gen86_movw_imm_r(p_pc, imm, reg)   /* movw   $imm, %reg */ (_gen86_pfx16_(p_pc) !((reg) & 8) || (_gen86_putb(p_pc, 0x40 | GEN86_REX_B), 0), _gen86_putb(p_pc, 0xb8 + (reg)&7), _gen86_putw(p_pc, imm))
#define gen86_movl_imm_r(p_pc, imm, reg)   /* movl   $imm, %reg */ (_gen86_pfx32_(p_pc) !((reg) & 8) || (_gen86_putb(p_pc, 0x40 | GEN86_REX_B), 0), _gen86_putb(p_pc, 0xb8 + (reg)&7), _gen86_putl(p_pc, imm))
#define gen86_movabs_imm_r(p_pc, imm, reg) /* movabs $imm, %reg */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W | ((reg)&8 ? GEN86_REX_B : 0)), _gen86_putb(p_pc, 0xb8 + (reg)&7), _gen86_putq(p_pc, imm))
#define gen86_movq_imm_r(p_pc, imm, reg)                                                     \
	(_gen86_fitsl(imm)                                                                       \
	 ? gen86_movq_imm_mod(p_pc, gen86_modrm_r, (__UINT32_TYPE__)(__UINT64_TYPE__)(imm), reg) \
	 : gen86_movabs_imm_r(p_pc, imm, reg))
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_movb_imm_r(p_pc, imm, reg) /* movb $imm, %reg */ (_gen86_putb(p_pc, 0xb0 + (reg)), _gen86_putb(p_pc, imm))
#define gen86_movw_imm_r(p_pc, imm, reg) /* movw $imm, %reg */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xb8 + (reg)), _gen86_putw(p_pc, imm))
#define gen86_movl_imm_r(p_pc, imm, reg) /* movl $imm, %reg */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xb8 + (reg)), _gen86_putl(p_pc, imm))
#endif /* LIBGEN86_TARGET_BITS != 64 */


/*[[[deemon
function genShift(name, reg) {
	print("#define gen86_", name, "b_imm_mod(p_pc, gen_modrm, imm, ...) /" "* ", name, "b $imm, ... *" "/ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc0), ", reg, ", __VA_ARGS__, _gen86_putb(p_pc, imm))");
	print("#define gen86_", name, "w_imm_mod(p_pc, gen_modrm, imm, ...) /" "* ", name, "w $imm, ... *" "/ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), ", reg, ", __VA_ARGS__, _gen86_putb(p_pc, imm)))");
	print("#define gen86_", name, "l_imm_mod(p_pc, gen_modrm, imm, ...) /" "* ", name, "l $imm, ... *" "/ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), ", reg, ", __VA_ARGS__, _gen86_putb(p_pc, imm)))");
	print("#define gen86_", name, "b_1_mod(p_pc, gen_modrm, ...)        /" "* ", name, "b $1,   ... *" "/ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd0), ", reg, ", __VA_ARGS__, (void)0)");
	print("#define gen86_", name, "w_1_mod(p_pc, gen_modrm, ...)        /" "* ", name, "w $1,   ... *" "/ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), ", reg, ", __VA_ARGS__, (void)0))");
	print("#define gen86_", name, "l_1_mod(p_pc, gen_modrm, ...)        /" "* ", name, "l $1,   ... *" "/ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), ", reg, ", __VA_ARGS__, (void)0))");
	print("#define gen86_", name, "b_cl_mod(p_pc, gen_modrm, ...)       /" "* ", name, "b %cl,  ... *" "/ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd2), ", reg, ", __VA_ARGS__, (void)0)");
	print("#define gen86_", name, "w_cl_mod(p_pc, gen_modrm, ...)       /" "* ", name, "w %cl,  ... *" "/ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), ", reg, ", __VA_ARGS__, (void)0))");
	print("#define gen86_", name, "l_cl_mod(p_pc, gen_modrm, ...)       /" "* ", name, "l %cl,  ... *" "/ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), ", reg, ", __VA_ARGS__, (void)0))");
	print("#if LIBGEN86_TARGET_BITS == 64");
	print("#define gen86_", name, "q_imm_mod(p_pc, gen_modrm, imm, ...) /" "* ", name, "q $imm, ... *" "/ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xc1), ", reg, ", __VA_ARGS__, _gen86_putb(p_pc, imm))");
	print("#define gen86_", name, "q_1_mod(p_pc, gen_modrm, ...)        /" "* ", name, "q $1,   ... *" "/ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd1), ", reg, ", __VA_ARGS__, (void)0)");
	print("#define gen86_", name, "q_cl_mod(p_pc, gen_modrm, ...)       /" "* ", name, "q %cl,  ... *" "/ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd3), ", reg, ", __VA_ARGS__, (void)0)");
	print("#endif /" "* LIBGEN86_TARGET_BITS == 64 *" "/");
}
genShift("rol", 0);
genShift("ror", 1);
genShift("rcl", 2);
genShift("rcr", 3);
genShift("shl", 4);
genShift("shr", 5);
genShift("sal", 6);
genShift("sar", 7);
]]]*/
#define gen86_rolb_imm_mod(p_pc, gen_modrm, imm, ...) /* rolb $imm, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc0), 0, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_rolw_imm_mod(p_pc, gen_modrm, imm, ...) /* rolw $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 0, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_roll_imm_mod(p_pc, gen_modrm, imm, ...) /* roll $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 0, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_rolb_1_mod(p_pc, gen_modrm, ...)        /* rolb $1,   ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd0), 0, __VA_ARGS__, (void)0)
#define gen86_rolw_1_mod(p_pc, gen_modrm, ...)        /* rolw $1,   ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 0, __VA_ARGS__, (void)0))
#define gen86_roll_1_mod(p_pc, gen_modrm, ...)        /* roll $1,   ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 0, __VA_ARGS__, (void)0))
#define gen86_rolb_cl_mod(p_pc, gen_modrm, ...)       /* rolb %cl,  ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd2), 0, __VA_ARGS__, (void)0)
#define gen86_rolw_cl_mod(p_pc, gen_modrm, ...)       /* rolw %cl,  ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 0, __VA_ARGS__, (void)0))
#define gen86_roll_cl_mod(p_pc, gen_modrm, ...)       /* roll %cl,  ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 0, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_rolq_imm_mod(p_pc, gen_modrm, imm, ...) /* rolq $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xc1), 0, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_rolq_1_mod(p_pc, gen_modrm, ...)        /* rolq $1,   ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd1), 0, __VA_ARGS__, (void)0)
#define gen86_rolq_cl_mod(p_pc, gen_modrm, ...)       /* rolq %cl,  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd3), 0, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_rorb_imm_mod(p_pc, gen_modrm, imm, ...) /* rorb $imm, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc0), 1, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_rorw_imm_mod(p_pc, gen_modrm, imm, ...) /* rorw $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 1, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_rorl_imm_mod(p_pc, gen_modrm, imm, ...) /* rorl $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 1, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_rorb_1_mod(p_pc, gen_modrm, ...)        /* rorb $1,   ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd0), 1, __VA_ARGS__, (void)0)
#define gen86_rorw_1_mod(p_pc, gen_modrm, ...)        /* rorw $1,   ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 1, __VA_ARGS__, (void)0))
#define gen86_rorl_1_mod(p_pc, gen_modrm, ...)        /* rorl $1,   ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 1, __VA_ARGS__, (void)0))
#define gen86_rorb_cl_mod(p_pc, gen_modrm, ...)       /* rorb %cl,  ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd2), 1, __VA_ARGS__, (void)0)
#define gen86_rorw_cl_mod(p_pc, gen_modrm, ...)       /* rorw %cl,  ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 1, __VA_ARGS__, (void)0))
#define gen86_rorl_cl_mod(p_pc, gen_modrm, ...)       /* rorl %cl,  ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 1, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_rorq_imm_mod(p_pc, gen_modrm, imm, ...) /* rorq $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xc1), 1, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_rorq_1_mod(p_pc, gen_modrm, ...)        /* rorq $1,   ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd1), 1, __VA_ARGS__, (void)0)
#define gen86_rorq_cl_mod(p_pc, gen_modrm, ...)       /* rorq %cl,  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd3), 1, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_rclb_imm_mod(p_pc, gen_modrm, imm, ...) /* rclb $imm, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc0), 2, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_rclw_imm_mod(p_pc, gen_modrm, imm, ...) /* rclw $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 2, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_rcll_imm_mod(p_pc, gen_modrm, imm, ...) /* rcll $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 2, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_rclb_1_mod(p_pc, gen_modrm, ...)        /* rclb $1,   ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd0), 2, __VA_ARGS__, (void)0)
#define gen86_rclw_1_mod(p_pc, gen_modrm, ...)        /* rclw $1,   ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 2, __VA_ARGS__, (void)0))
#define gen86_rcll_1_mod(p_pc, gen_modrm, ...)        /* rcll $1,   ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 2, __VA_ARGS__, (void)0))
#define gen86_rclb_cl_mod(p_pc, gen_modrm, ...)       /* rclb %cl,  ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd2), 2, __VA_ARGS__, (void)0)
#define gen86_rclw_cl_mod(p_pc, gen_modrm, ...)       /* rclw %cl,  ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 2, __VA_ARGS__, (void)0))
#define gen86_rcll_cl_mod(p_pc, gen_modrm, ...)       /* rcll %cl,  ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 2, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_rclq_imm_mod(p_pc, gen_modrm, imm, ...) /* rclq $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xc1), 2, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_rclq_1_mod(p_pc, gen_modrm, ...)        /* rclq $1,   ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd1), 2, __VA_ARGS__, (void)0)
#define gen86_rclq_cl_mod(p_pc, gen_modrm, ...)       /* rclq %cl,  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd3), 2, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_rcrb_imm_mod(p_pc, gen_modrm, imm, ...) /* rcrb $imm, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc0), 3, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_rcrw_imm_mod(p_pc, gen_modrm, imm, ...) /* rcrw $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 3, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_rcrl_imm_mod(p_pc, gen_modrm, imm, ...) /* rcrl $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 3, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_rcrb_1_mod(p_pc, gen_modrm, ...)        /* rcrb $1,   ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd0), 3, __VA_ARGS__, (void)0)
#define gen86_rcrw_1_mod(p_pc, gen_modrm, ...)        /* rcrw $1,   ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 3, __VA_ARGS__, (void)0))
#define gen86_rcrl_1_mod(p_pc, gen_modrm, ...)        /* rcrl $1,   ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 3, __VA_ARGS__, (void)0))
#define gen86_rcrb_cl_mod(p_pc, gen_modrm, ...)       /* rcrb %cl,  ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd2), 3, __VA_ARGS__, (void)0)
#define gen86_rcrw_cl_mod(p_pc, gen_modrm, ...)       /* rcrw %cl,  ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 3, __VA_ARGS__, (void)0))
#define gen86_rcrl_cl_mod(p_pc, gen_modrm, ...)       /* rcrl %cl,  ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 3, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_rcrq_imm_mod(p_pc, gen_modrm, imm, ...) /* rcrq $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xc1), 3, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_rcrq_1_mod(p_pc, gen_modrm, ...)        /* rcrq $1,   ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd1), 3, __VA_ARGS__, (void)0)
#define gen86_rcrq_cl_mod(p_pc, gen_modrm, ...)       /* rcrq %cl,  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd3), 3, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_shlb_imm_mod(p_pc, gen_modrm, imm, ...) /* shlb $imm, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc0), 4, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_shlw_imm_mod(p_pc, gen_modrm, imm, ...) /* shlw $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 4, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_shll_imm_mod(p_pc, gen_modrm, imm, ...) /* shll $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 4, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_shlb_1_mod(p_pc, gen_modrm, ...)        /* shlb $1,   ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd0), 4, __VA_ARGS__, (void)0)
#define gen86_shlw_1_mod(p_pc, gen_modrm, ...)        /* shlw $1,   ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 4, __VA_ARGS__, (void)0))
#define gen86_shll_1_mod(p_pc, gen_modrm, ...)        /* shll $1,   ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 4, __VA_ARGS__, (void)0))
#define gen86_shlb_cl_mod(p_pc, gen_modrm, ...)       /* shlb %cl,  ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd2), 4, __VA_ARGS__, (void)0)
#define gen86_shlw_cl_mod(p_pc, gen_modrm, ...)       /* shlw %cl,  ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 4, __VA_ARGS__, (void)0))
#define gen86_shll_cl_mod(p_pc, gen_modrm, ...)       /* shll %cl,  ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 4, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_shlq_imm_mod(p_pc, gen_modrm, imm, ...) /* shlq $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xc1), 4, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_shlq_1_mod(p_pc, gen_modrm, ...)        /* shlq $1,   ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd1), 4, __VA_ARGS__, (void)0)
#define gen86_shlq_cl_mod(p_pc, gen_modrm, ...)       /* shlq %cl,  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd3), 4, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_shrb_imm_mod(p_pc, gen_modrm, imm, ...) /* shrb $imm, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc0), 5, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_shrw_imm_mod(p_pc, gen_modrm, imm, ...) /* shrw $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 5, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_shrl_imm_mod(p_pc, gen_modrm, imm, ...) /* shrl $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 5, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_shrb_1_mod(p_pc, gen_modrm, ...)        /* shrb $1,   ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd0), 5, __VA_ARGS__, (void)0)
#define gen86_shrw_1_mod(p_pc, gen_modrm, ...)        /* shrw $1,   ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 5, __VA_ARGS__, (void)0))
#define gen86_shrl_1_mod(p_pc, gen_modrm, ...)        /* shrl $1,   ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 5, __VA_ARGS__, (void)0))
#define gen86_shrb_cl_mod(p_pc, gen_modrm, ...)       /* shrb %cl,  ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd2), 5, __VA_ARGS__, (void)0)
#define gen86_shrw_cl_mod(p_pc, gen_modrm, ...)       /* shrw %cl,  ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 5, __VA_ARGS__, (void)0))
#define gen86_shrl_cl_mod(p_pc, gen_modrm, ...)       /* shrl %cl,  ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 5, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_shrq_imm_mod(p_pc, gen_modrm, imm, ...) /* shrq $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xc1), 5, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_shrq_1_mod(p_pc, gen_modrm, ...)        /* shrq $1,   ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd1), 5, __VA_ARGS__, (void)0)
#define gen86_shrq_cl_mod(p_pc, gen_modrm, ...)       /* shrq %cl,  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd3), 5, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_salb_imm_mod(p_pc, gen_modrm, imm, ...) /* salb $imm, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc0), 6, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_salw_imm_mod(p_pc, gen_modrm, imm, ...) /* salw $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 6, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_sall_imm_mod(p_pc, gen_modrm, imm, ...) /* sall $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 6, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_salb_1_mod(p_pc, gen_modrm, ...)        /* salb $1,   ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd0), 6, __VA_ARGS__, (void)0)
#define gen86_salw_1_mod(p_pc, gen_modrm, ...)        /* salw $1,   ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 6, __VA_ARGS__, (void)0))
#define gen86_sall_1_mod(p_pc, gen_modrm, ...)        /* sall $1,   ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 6, __VA_ARGS__, (void)0))
#define gen86_salb_cl_mod(p_pc, gen_modrm, ...)       /* salb %cl,  ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd2), 6, __VA_ARGS__, (void)0)
#define gen86_salw_cl_mod(p_pc, gen_modrm, ...)       /* salw %cl,  ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 6, __VA_ARGS__, (void)0))
#define gen86_sall_cl_mod(p_pc, gen_modrm, ...)       /* sall %cl,  ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 6, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_salq_imm_mod(p_pc, gen_modrm, imm, ...) /* salq $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xc1), 6, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_salq_1_mod(p_pc, gen_modrm, ...)        /* salq $1,   ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd1), 6, __VA_ARGS__, (void)0)
#define gen86_salq_cl_mod(p_pc, gen_modrm, ...)       /* salq %cl,  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd3), 6, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_sarb_imm_mod(p_pc, gen_modrm, imm, ...) /* sarb $imm, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc0), 7, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_sarw_imm_mod(p_pc, gen_modrm, imm, ...) /* sarw $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 7, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_sarl_imm_mod(p_pc, gen_modrm, imm, ...) /* sarl $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc1), 7, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_sarb_1_mod(p_pc, gen_modrm, ...)        /* sarb $1,   ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd0), 7, __VA_ARGS__, (void)0)
#define gen86_sarw_1_mod(p_pc, gen_modrm, ...)        /* sarw $1,   ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 7, __VA_ARGS__, (void)0))
#define gen86_sarl_1_mod(p_pc, gen_modrm, ...)        /* sarl $1,   ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd1), 7, __VA_ARGS__, (void)0))
#define gen86_sarb_cl_mod(p_pc, gen_modrm, ...)       /* sarb %cl,  ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd2), 7, __VA_ARGS__, (void)0)
#define gen86_sarw_cl_mod(p_pc, gen_modrm, ...)       /* sarw %cl,  ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 7, __VA_ARGS__, (void)0))
#define gen86_sarl_cl_mod(p_pc, gen_modrm, ...)       /* sarl %cl,  ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xd3), 7, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_sarq_imm_mod(p_pc, gen_modrm, imm, ...) /* sarq $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xc1), 7, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_sarq_1_mod(p_pc, gen_modrm, ...)        /* sarq $1,   ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd1), 7, __VA_ARGS__, (void)0)
#define gen86_sarq_cl_mod(p_pc, gen_modrm, ...)       /* sarq %cl,  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xd3), 7, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */
/*[[[end]]]*/


#define gen86_retw_imm(p_pc, imm) /* retw $imm */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xc2), _gen86_putw(p_pc, imm))
#define gen86_ret_imm(p_pc, imm)  /* ret  $imm */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xc2), _gen86_putw(p_pc, imm))
#define gen86_retw(p_pc)          /* retw      */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xc3))
#define gen86_ret(p_pc)           /* ret       */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xc3))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_retq_imm(p_pc, imm) /* retq $imm */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xc2), _gen86_putw(p_pc, imm))
#define gen86_retq(p_pc)          /* retq      */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xc3))
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_retl_imm(p_pc, imm) /* retl $imm */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xc2), _gen86_putw(p_pc, imm))
#define gen86_retl(p_pc)          /* retl      */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xc3))
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_movb_imm_mod(p_pc, gen_modrm, imm, ...) /* movb $imm, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc6), 0, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_movw_imm_mod(p_pc, gen_modrm, imm, ...) /* movw $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc7), 0, __VA_ARGS__, _gen86_putw(p_pc, imm)))
#define gen86_movl_imm_mod(p_pc, gen_modrm, imm, ...) /* movl $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xc7), 0, __VA_ARGS__, _gen86_putl(p_pc, imm)))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_movq_imm_mod(p_pc, gen_modrm, imm, ...) /* movq $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xc7), 0, __VA_ARGS__, _gen86_putsl(p_pc, imm))
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_enter(p_pc, size, nesting) /* enter $size, $nesting */ (_gen86_putb(p_pc, 0xc8), _gen86_putw(p_pc, size), _gen86_putb(p_pc, nesting))
#define gen86_leave(p_pc)                /* leave                 */ _gen86_putb(p_pc, 0xc9)

#define gen86_lret_imm(p_pc, imm) /* lret  $imm */ (_gen86_putb(p_pc, 0xca), _gen86_putw(p_pc, imm))
#define gen86_lret(p_pc)          /* lret       */ _gen86_putb(p_pc, 0xcb)

#define gen86_int3(p_pc)     /* int3     */ _gen86_putb(p_pc, 0xcc)
#define gen86_int(p_pc, imm) /* int $imm */ (_gen86_putb(p_pc, 0xcd), _gen86_putb(p_pc, imm))
#define gen86_into(p_pc)     /* into     */ _gen86_putb(p_pc, 0xce)

#define gen86_iretw(p_pc) /* iretw */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xcf))
#define gen86_iretl(p_pc) /* iretl */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xcf))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_iretq(p_pc) /* iretq */ (_gen86_putb2(p_pc, 0x40 | GEN86_REX_W, 0xcf))
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_aam(p_pc, imm) /* aam $imm */ (_gen86_putb(p_pc, 0xd4), _gen86_putb(p_pc, imm))
#define gen86_aad(p_pc, imm) /* aad $imm */ (_gen86_putb(p_pc, 0xd5), _gen86_putb(p_pc, imm))
#define gen86_xlatb(p_pc)    /* xlatb    */ _gen86_putb(p_pc, 0xd7)

#define gen86_loopnz(p_pc, addr)          /* loopnz addr          */ (_gen86_putb(p_pc, 0xe0), _gen86_putsb_pcrel(p_pc, addr))
#define gen86_loopz(p_pc, addr)           /* loopz  addr          */ (_gen86_putb(p_pc, 0xe1), _gen86_putsb_pcrel(p_pc, addr))
#define gen86_loop(p_pc, addr)            /* loop   addr          */ (_gen86_putb(p_pc, 0xe2), _gen86_putsb_pcrel(p_pc, addr))
#define gen86_jcxz(p_pc, addr)            /* jcxz   addr          */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xe3), _gen86_putsb_pcrel(p_pc, addr))
#define gen86_jecxz(p_pc, addr)           /* jecxz  addr          */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xe3), _gen86_putsb_pcrel(p_pc, addr))
#define gen86_loopnz_offset(p_pc, offset) /* loopnz 1f+offset; 1: */ (_gen86_putb(p_pc, 0xe0), _gen86_putsb(p_pc, offset))
#define gen86_loopz_offset(p_pc, offset)  /* loopz  1f+offset; 1: */ (_gen86_putb(p_pc, 0xe1), _gen86_putsb(p_pc, offset))
#define gen86_loop_offset(p_pc, offset)   /* loop   1f+offset; 1: */ (_gen86_putb(p_pc, 0xe2), _gen86_putsb(p_pc, offset))
#define gen86_jcxz_offset(p_pc, offset)   /* jcxz   1f+offset; 1: */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xe3), _gen86_putsb(p_pc, offset))
#define gen86_jecxz_offset(p_pc, offset)  /* jecxz  1f+offset; 1: */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xe3), _gen86_putsb(p_pc, offset))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_jrcxz(p_pc, addr)          /* jrcxz  addr          */ (_gen86_putb2(p_pc, 0x40 | GEN86_REX_W, 0xe3), _gen86_putsb_pcrel(p_pc, addr))
#define gen86_jrcxz_offset(p_pc, offset) /* jrcxz  1f+offset; 1: */ (_gen86_putb2(p_pc, 0x40 | GEN86_REX_W, 0xe3), _gen86_putsb(p_pc, offset))
#define gen86_jPcxz                      gen86_jrcxz
#define gen86_jPcxz_offset               gen86_jrcxz_offset
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_jPcxz        gen86_jecxz
#define gen86_jPcxz_offset gen86_jecxz_offset
#endif /* LIBGEN86_TARGET_BITS != 64 */

#define gen86_inb_imm_al(p_pc, imm)   /* inb  $imm, %al  */ (_gen86_putb(p_pc, 0xe4), _gen86_putb(p_pc, imm))
#define gen86_inw_imm_ax(p_pc, imm)   /* inw  $imm, %ax  */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xe5), _gen86_putb(p_pc, imm))
#define gen86_inl_imm_eax(p_pc, imm)  /* inl  $imm, %eax */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xe5), _gen86_putb(p_pc, imm))
#define gen86_outb_al_imm(p_pc, imm)  /* outb %al, $imm  */ (_gen86_putb(p_pc, 0xe6), _gen86_putb(p_pc, imm))
#define gen86_outw_ax_imm(p_pc, imm)  /* outw %ax, $imm  */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xe7), _gen86_putb(p_pc, imm))
#define gen86_outl_eax_imm(p_pc, imm) /* outl %eax, $imm */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xe7), _gen86_putb(p_pc, imm))

#if LIBGEN86_TARGET_BITS == 16
#define gen86_callP(p_pc, addr)          /* call  addr          */ (_gen86_putb(p_pc, 0xe8), _gen86_putsw_pcrel(p_pc, addr))
#define gen86_jmpP(p_pc, addr)           /* jmp   addr          */ (_gen86_putb(p_pc, 0xe9), _gen86_putsw_pcrel(p_pc, addr))
#define gen86_callP_offset(p_pc, offset) /* call  1f+offset; 1: */ (_gen86_putb(p_pc, 0xe8), _gen86_putsw(p_pc, offset))
#define gen86_jmpP_offset(p_pc, offset)  /* jmp   1f+offset; 1: */ (_gen86_putb(p_pc, 0xe9), _gen86_putsw(p_pc, offset))
#define gen86_callw                     gen86_callP
#define gen86_jmpw                      gen86_jmpP
#define gen86_callw_offset              gen86_callP_offset
#define gen86_jmpw_offset               gen86_jmpP_offset
#elif LIBGEN86_TARGET_BITS == 32
#define gen86_callP(p_pc, addr)          /* call  addr          */ (_gen86_putb(p_pc, 0xe8), _gen86_putsl_pcrel(p_pc, addr))
#define gen86_jmpP(p_pc, addr)           /* jmp   addr          */ (_gen86_putb(p_pc, 0xe9), _gen86_putsl_pcrel(p_pc, addr))
#define gen86_callP_offset(p_pc, offset) /* call  1f+offset; 1: */ (_gen86_putb(p_pc, 0xe8), _gen86_putsl(p_pc, offset))
#define gen86_jmpP_offset(p_pc, offset)  /* jmp   1f+offset; 1: */ (_gen86_putb(p_pc, 0xe9), _gen86_putsl(p_pc, offset))
#define gen86_calll                     gen86_callP
#define gen86_jmpl                      gen86_jmpP
#define gen86_calll_offset              gen86_callP_offset
#define gen86_jmpl_offset               gen86_jmpP_offset
#else /* LIBGEN86_TARGET_BITS == ... */
#define gen86_callP(p_pc, addr)          /* call  addr          */ (_gen86_putb(p_pc, 0xe8), _gen86_putsl_pcrel(p_pc, addr))
#define gen86_jmpP(p_pc, addr)           /* jmp   addr          */ (_gen86_putb(p_pc, 0xe9), _gen86_putsl_pcrel(p_pc, addr))
#define gen86_callP_offset(p_pc, offset) /* call  1f+offset; 1: */ (_gen86_putb(p_pc, 0xe8), _gen86_putsl(p_pc, offset))
#define gen86_jmpP_offset(p_pc, offset)  /* jmp   1f+offset; 1: */ (_gen86_putb(p_pc, 0xe9), _gen86_putsl(p_pc, offset))
#define gen86_callq                     gen86_callP
#define gen86_jmpq                      gen86_jmpP
#define gen86_callq_offset              gen86_callP_offset
#define gen86_jmpq_offset               gen86_jmpP_offset
#endif /* LIBGEN86_TARGET_BITS != ... */
#define gen86_call        gen86_callP
#define gen86_call_offset gen86_callP_offset

#define gen86_jmp8(p_pc, addr)          /* jmp8 addr          */ (_gen86_putb(p_pc, 0xeb), _gen86_putsb_pcrel(p_pc, addr))
#define gen86_jmp8_offset(p_pc, offset) /* jmp8 1f+offset; 1: */ (_gen86_putb(p_pc, 0xeb), _gen86_putsb(p_pc, offset))

#define gen86_jmp_offset(p_pc, offset) \
	(_gen86_fitsb(offset)              \
	 ? gen86_jmp8_offset(p_pc, offset) \
	 : gen86_jmpP_offset(p_pc, offset))
#define gen86_jmp(p_pc, addr)                                                                             \
	__XBLOCK({                                                                                            \
		__INT32_TYPE__ __g86_joff = (__INT32_TYPE__)(__INTPTR_TYPE__)((__UINTPTR_TYPE__)(addr) -          \
		                                                              ((__UINTPTR_TYPE__)(*(p_pc)) + 2)); \
		if (_gen86_fitsb(__g86_joff)) {                                                                   \
			gen86_jmp8_offset(p_pc, __g86_joff);                                                          \
		} else {                                                                                          \
			__g86_joff -= _GEN86_JMPP_EXTRA;                                                              \
			gen86_jmpP_offset(p_pc, __g86_joff);                                                          \
		}                                                                                                 \
		(void)0;                                                                                          \
	})

#define gen86_ljmpw(p_pc, segment, offset) /* ljmpw $segment:$offset */ (_gen86_adr16_(p_pc) _gen86_putb(p_pc, 0xea) _gen86_putw(p_pc, offset), _gen86_putw(p_pc, segment))
#define gen86_ljmpl(p_pc, segment, offset) /* ljmpl $segment:$offset */ (_gen86_adr32_(p_pc) _gen86_putb(p_pc, 0xea) _gen86_putl(p_pc, offset), _gen86_putw(p_pc, segment))

#define gen86_inb_dx_al(p_pc)   /* inb  %dx, %al  */ _gen86_putb(p_pc, 0xec)
#define gen86_inw_dx_ax(p_pc)   /* inw  %dx, %ax  */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xed))
#define gen86_inl_dx_eax(p_pc)  /* inl  %dx, %eax */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xed))
#define gen86_outb_al_dx(p_pc)  /* outb %al, %dx  */ _gen86_putb(p_pc, 0xee)
#define gen86_outw_ax_dx(p_pc)  /* outw %ax, %dx  */ (_gen86_pfx16_(p_pc) _gen86_putb(p_pc, 0xef))
#define gen86_outl_eax_dx(p_pc) /* outl %eax, %dx */ (_gen86_pfx32_(p_pc) _gen86_putb(p_pc, 0xef))

#define gen86_int1(p_pc) /* int1 */ _gen86_putb(p_pc, 0xf1)
#define gen86_hlt(p_pc)  /* hlt  */ _gen86_putb(p_pc, 0xf4)
#define gen86_cmc(p_pc)  /* cmc  */ _gen86_putb(p_pc, 0xf5)

#define gen86_testb_imm_mod(p_pc, gen_modrm, imm, ...)  /* testb $imm, ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf6), 0, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define _gen86_testw_imm_mod(p_pc, gen_modrm, imm, ...) /* testw $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 0, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_testw_imm_mod(p_pc, gen_modrm, imm, ...)  /* testw $imm, ... */ ((__UINT16_TYPE__)(imm) <= __UINT8_C(0xff) ? gen86_testb_imm_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : _gen86_testw_imm_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#define _gen86_testl_imm_mod(p_pc, gen_modrm, imm, ...) /* testl $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 0, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_testl_imm_mod(p_pc, gen_modrm, imm, ...)  /* testl $imm, ... */ ((__UINT32_TYPE__)(imm) <= __UINT16_C(0xffff) ? gen86_testw_imm_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : _gen86_testl_imm_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#if LIBGEN86_TARGET_BITS == 64
#define _gen86_testq_imm_mod(p_pc, gen_modrm, imm, ...) /* testq $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xf7), 0, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_testq_imm_mod(p_pc, gen_modrm, imm, ...)  /* testq $imm, ... */ ((__UINT32_TYPE__)(imm) <= __UINT32_C(0x7fffffff) ? gen86_testl_imm_mod(p_pc, gen_modrm, imm, __VA_ARGS__) : _gen86_testq_imm_mod(p_pc, gen_modrm, imm, __VA_ARGS__))
#endif /* LIBGEN86_TARGET_BITS == 64 */



#define gen86_notb_mod(p_pc, gen_modrm, ...)  /* notb  ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf6), 2, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_notw_mod(p_pc, gen_modrm, ...)  /* notw  ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 2, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_notl_mod(p_pc, gen_modrm, ...)  /* notl  ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 2, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_negb_mod(p_pc, gen_modrm, ...)  /* negb  ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf6), 3, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_negw_mod(p_pc, gen_modrm, ...)  /* negw  ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 3, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_negl_mod(p_pc, gen_modrm, ...)  /* negl  ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 3, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_mulb_mod(p_pc, gen_modrm, ...)  /* mulb  ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf6), 4, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_mulw_mod(p_pc, gen_modrm, ...)  /* mulw  ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 4, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_mull_mod(p_pc, gen_modrm, ...)  /* mull  ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 4, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_imulb_mod(p_pc, gen_modrm, ...) /* imulb ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf6), 5, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_imulw_mod(p_pc, gen_modrm, ...) /* imulw ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 5, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_imull_mod(p_pc, gen_modrm, ...) /* imull ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 5, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_divb_mod(p_pc, gen_modrm, ...)  /* divb  ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf6), 6, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_divw_mod(p_pc, gen_modrm, ...)  /* divw  ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 6, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_divl_mod(p_pc, gen_modrm, ...)  /* divl  ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 6, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_idivb_mod(p_pc, gen_modrm, ...) /* idivb ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf6), 7, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_idivw_mod(p_pc, gen_modrm, ...) /* idivw ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 7, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_idivl_mod(p_pc, gen_modrm, ...) /* idivl ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xf7), 7, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_notq_mod(p_pc, gen_modrm, ...)  /* notq  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xf7), 2, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_negq_mod(p_pc, gen_modrm, ...)  /* negq  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xf7), 3, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_mulq_mod(p_pc, gen_modrm, ...)  /* mulq  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xf7), 4, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_imulq_mod(p_pc, gen_modrm, ...) /* imulq ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xf7), 5, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_divq_mod(p_pc, gen_modrm, ...)  /* divq  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xf7), 6, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_idivq_mod(p_pc, gen_modrm, ...) /* idivq ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xf7), 7, __VA_ARGS__, _gen86_putb(p_pc, imm))
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_clc(p_pc) /* clc */ _gen86_putb(p_pc, 0xf8)
#define gen86_stc(p_pc) /* stc */ _gen86_putb(p_pc, 0xf9)
#define gen86_cli(p_pc) /* cli */ _gen86_putb(p_pc, 0xfa)
#define gen86_sti(p_pc) /* sti */ _gen86_putb(p_pc, 0xfb)
#define gen86_cld(p_pc) /* cld */ _gen86_putb(p_pc, 0xfc)
#define gen86_std(p_pc) /* std */ _gen86_putb(p_pc, 0xfd)

#define gen86_incb_mod(p_pc, gen_modrm, ...) /* incb ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xfe), 0, __VA_ARGS__, (void)0)
#define gen86_incw_mod(p_pc, gen_modrm, ...) /* incw ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 0, __VA_ARGS__, (void)0))
#define gen86_incl_mod(p_pc, gen_modrm, ...) /* incl ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 0, __VA_ARGS__, (void)0))
#define gen86_decb_mod(p_pc, gen_modrm, ...) /* decb ... */ gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xfe), 1, __VA_ARGS__, (void)0)
#define gen86_decw_mod(p_pc, gen_modrm, ...) /* decw ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 1, __VA_ARGS__, (void)0))
#define gen86_decl_mod(p_pc, gen_modrm, ...) /* decl ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 1, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_incq_mod(p_pc, gen_modrm, ...) /* incq ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xff), 0, __VA_ARGS__, (void)0)
#define gen86_decq_mod(p_pc, gen_modrm, ...) /* decq ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xff), 1, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_callw_mod(p_pc, gen_modrm, ...)  /* callw  *... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 2, __VA_ARGS__, (void)0))
#define gen86_calll_mod(p_pc, gen_modrm, ...)  /* calll  *... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 2, __VA_ARGS__, (void)0))
#define gen86_lcallw_mod(p_pc, gen_modrm, ...) /* lcallw ...  */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 3, __VA_ARGS__, (void)0))
#define gen86_lcalll_mod(p_pc, gen_modrm, ...) /* lcalll ...  */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 3, __VA_ARGS__, (void)0))
#define gen86_jmpw_mod(p_pc, gen_modrm, ...)   /* jmpw   *... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 4, __VA_ARGS__, (void)0))
#define gen86_jmpl_mod(p_pc, gen_modrm, ...)   /* jmpl   *... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 4, __VA_ARGS__, (void)0))
#define gen86_ljmpw_mod(p_pc, gen_modrm, ...)  /* ljmpw  ...  */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 5, __VA_ARGS__, (void)0))
#define gen86_ljmpl_mod(p_pc, gen_modrm, ...)  /* ljmpl  ...  */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 5, __VA_ARGS__, (void)0))
#define gen86_pushw_mod(p_pc, gen_modrm, ...)  /* pushw  ...  */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 6, __VA_ARGS__, (void)0))
#define gen86_pushl_mod(p_pc, gen_modrm, ...)  /* pushl  ...  */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb(p_pc, 0xff), 6, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_callq_mod(p_pc, gen_modrm, ...)  /* callq  *... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xff), 2, __VA_ARGS__, (void)0)
#define gen86_lcallq_mod(p_pc, gen_modrm, ...) /* lcallq ...  */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xff), 3, __VA_ARGS__, (void)0)
#define gen86_jmpq_mod(p_pc, gen_modrm, ...)   /* jmpq   *... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xff), 4, __VA_ARGS__, (void)0)
#define gen86_ljmpq_mod(p_pc, gen_modrm, ...)  /* ljmpq  ...  */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xff), 5, __VA_ARGS__, (void)0)
#define gen86_pushq_mod(p_pc, gen_modrm, ...)  /* pushq  ...  */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb(p_pc, 0xff), 6, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */


/************************************************************************/
/* 0Fh instructions                                                     */
/************************************************************************/

#define gen86_sldt(p_pc, gen_modrm, ...) /* sldt ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x00), 0, __VA_ARGS__, (void)0)
#define gen86_str(p_pc, gen_modrm, ...)  /* str  ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x00), 1, __VA_ARGS__, (void)0)
#define gen86_lldt(p_pc, gen_modrm, ...) /* lldt ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x00), 2, __VA_ARGS__, (void)0)
#define gen86_ltr(p_pc, gen_modrm, ...)  /* ltr  ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x00), 3, __VA_ARGS__, (void)0)
#define gen86_verr(p_pc, gen_modrm, ...) /* verr ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x00), 4, __VA_ARGS__, (void)0)
#define gen86_verw(p_pc, gen_modrm, ...) /* verw ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x00), 5, __VA_ARGS__, (void)0)
#define gen86_sgdt(p_pc, gen_modrm, ...) /* sgdt ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x01), 0, __VA_ARGS__, (void)0)
#define gen86_sidt(p_pc, gen_modrm, ...) /* sidt ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x01), 1, __VA_ARGS__, (void)0)
#define gen86_lgdt(p_pc, gen_modrm, ...) /* lgdt ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x01), 2, __VA_ARGS__, (void)0)
#define gen86_lidt(p_pc, gen_modrm, ...) /* lidt ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x01), 3, __VA_ARGS__, (void)0)

#define gen86_smsww(p_pc, gen_modrm, ...) /* smsww ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x01), 4, __VA_ARGS__, (void)0))
#define gen86_smswl(p_pc, gen_modrm, ...) /* smswl ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x01), 4, __VA_ARGS__, (void)0))
#define gen86_lmsww(p_pc, gen_modrm, ...) /* lmsww ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x01), 6, __VA_ARGS__, (void)0))
#define gen86_lmswl(p_pc, gen_modrm, ...) /* lmswl ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x01), 6, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_smswq(p_pc, gen_modrm, ...) /* smswq ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0x01), 4, __VA_ARGS__, (void)0)
#define gen86_lmswq(p_pc, gen_modrm, ...) /* lmswq ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0x01), 6, __VA_ARGS__, (void)0)
#define gen86_sgdtq                       gen86_sgdt
#define gen86_sidtq                       gen86_sidt
#define gen86_lgdtq                       gen86_lgdt
#define gen86_lidtq                       gen86_lidt
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_sgdtl                       gen86_sgdt
#define gen86_sidtl                       gen86_sidt
#define gen86_lgdtl                       gen86_lgdt
#define gen86_lidtl                       gen86_lidt
#endif /* LIBGEN86_TARGET_BITS != 64 */

#define gen86_invlpg(p_pc, gen_modrm, ...) /* invlpg ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x01), 7, __VA_ARGS__, (void)0)
#define gen86_vmcall(p_pc)                 /* vmcall                    */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xc1)
#define gen86_vmlaunch(p_pc)               /* vmlaunch                  */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xc2)
#define gen86_vmresume(p_pc)               /* vmresume                  */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xc3)
#define gen86_vmxoff(p_pc)                 /* vmxoff                    */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xc4)
#define gen86_monitor(p_pc)                /* monitor %Pax, %Pcx, %Pdx  */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xc8)
#define gen86_mwait(p_pc)                  /* mwait %Pax, %Pcx          */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xc9)
#define gen86_clac(p_pc)                   /* clac                      */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xca)
#define gen86_stac(p_pc)                   /* stac                      */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xcb)
#define gen86_encls(p_pc)                  /* encls                     */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xcf)
#define gen86_xgetbv(p_pc)                 /* xgetbv                    */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xd0)
#define gen86_xsetbv(p_pc)                 /* xsetbv                    */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xd1)
#define gen86_vmfunc(p_pc)                 /* vmfunc                    */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xd4)
#define gen86_xend(p_pc)                   /* xend                      */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xd5)
#define gen86_xtest(p_pc)                  /* xtest                     */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xd6)
#define gen86_enclu(p_pc)                  /* enclu                     */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xd7)
#define gen86_vmrun(p_pc)                  /* vmrun %Pax                */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xd8)
#define gen86_vmmcall(p_pc)                /* vmmcall                   */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xd9)
#define gen86_vmload(p_pc)                 /* vmload                    */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xda)
#define gen86_vmsave(p_pc)                 /* vmsave                    */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xdb)
#define gen86_stgi(p_pc)                   /* stgi                      */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xdc)
#define gen86_clgi(p_pc)                   /* clgi                      */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xdd)
#define gen86_skinit(p_pc)                 /* skinit %Pax               */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xde)
#define gen86_invlpga(p_pc)                /* invlpga %Pax, %Pcx        */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xdf)
#define gen86_swapgs(p_pc)                 /* swapgs                    */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xf8)
#define gen86_rdtscp(p_pc)                 /* rdtscp                    */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xf9)
#define gen86_monitorx(p_pc)               /* monitorx %Pax, %Pcx, %Pdx */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xfa)
#define gen86_mcommit(p_pc)                /* mcommit                   */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xfa)
#define gen86_mwaitx(p_pc)                 /* mwaitx %Pax, %Pcx         */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xfb)
#define gen86_clzero(p_pc)                 /* clzero %Pax               */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xfc)
#define gen86_rdpru(p_pc)                  /* rdpru                     */ _gen86_putb3(p_pc, 0x0f, 0x01, 0xfd)

#define gen86_lar_mod_r(p_pc, gen_modrm, reg, ...) /* lar ..., %reg */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x02), reg, __VA_ARGS__, (void)0)

#define gen86_lslw_mod_r(p_pc, gen_modrm, reg, ...) /* lslw ..., %reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x03), reg, __VA_ARGS__, (void)0))
#define gen86_lsll_mod_r(p_pc, gen_modrm, reg, ...) /* lsll ..., %reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x03), reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_lslq_mod_r(p_pc, gen_modrm, reg, ...) /* lslq ..., %reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0x03), reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#if LIBGEN86_TARGET_BITS == 64
#define gen86_syscall(p_pc) /* syscall */ _gen86_putb2(p_pc, 0x0f, 0x05)
#define gen86_sysret(p_pc)  /* sysret  */ _gen86_putb2(p_pc, 0x0f, 0x07)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_clts(p_pc)     /* clts     */ _gen86_putb2(p_pc, 0x0f, 0x06)
#define gen86_invd(p_pc)     /* invd     */ _gen86_putb2(p_pc, 0x0f, 0x08)
#define gen86_wbnoinvd(p_pc) /* wbnoinvd */ _gen86_putb3(p_pc, 0xf3, 0x0f, 0x09)
#define gen86_wbinvd(p_pc)   /* wbinvd   */ _gen86_putb2(p_pc, 0x0f, 0x09)
#define gen86_ud2(p_pc)      /* ud2      */ _gen86_putb2(p_pc, 0x0f, 0x0b)

#define gen86_prefetch(p_pc, gen_modrm, ...)    /* prefetch    ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x0d), 0, __VA_ARGS__, (void)0)
#define gen86_prefetchw(p_pc, gen_modrm, ...)   /* prefetchw   ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x0d), 1, __VA_ARGS__, (void)0)
#define gen86_prefetchwt1(p_pc, gen_modrm, ...) /* prefetchwt1 ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x0d), 2, __VA_ARGS__, (void)0)
#define gen86_prefetchnta(p_pc, gen_modrm, ...) /* prefetchnta ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x18), 0, __VA_ARGS__, (void)0)
#define gen86_prefetcht0(p_pc, gen_modrm, ...)  /* prefetcht0  ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x18), 1, __VA_ARGS__, (void)0)
#define gen86_prefetcht1(p_pc, gen_modrm, ...)  /* prefetcht1  ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x18), 2, __VA_ARGS__, (void)0)
#define gen86_prefetcht2(p_pc, gen_modrm, ...)  /* prefetcht2  ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x18), 3, __VA_ARGS__, (void)0)
#define gen86_cldemote(p_pc, gen_modrm, ...)    /* cldemote    ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x1c), 0, __VA_ARGS__, (void)0)

#define gen86_nopw_mod(p_pc, gen_modrm, ...) /* nopw ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x1f), 0, __VA_ARGS__, (void)0))
#define gen86_nopl_mod(p_pc, gen_modrm, ...) /* nopl ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x1f), 0, __VA_ARGS__, (void)0))

#define gen86_mov_cr_mod(p_pc, gen_modrm, crN, ...) /* mov %crN, ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x20), crN, __VA_ARGS__, (void)0)
#define gen86_mov_dr_mod(p_pc, gen_modrm, drN, ...) /* mov ..., %drN */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x21), drN, __VA_ARGS__, (void)0)
#define gen86_mov_mod_cr(p_pc, gen_modrm, crN, ...) /* mov %crN, ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x22), crN, __VA_ARGS__, (void)0)
#define gen86_mov_mod_dr(p_pc, gen_modrm, drN, ...) /* mov ..., %drN */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x23), drN, __VA_ARGS__, (void)0)
#if LIBGEN86_TARGET_BITS == 64
#define gen86_movq_cr_mod gen86_mov_cr_mod
#define gen86_movq_dr_mod gen86_mov_dr_mod
#define gen86_movq_mod_cr gen86_mov_mod_cr
#define gen86_movq_mod_dr gen86_mov_mod_dr
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_movl_cr_mod gen86_mov_cr_mod
#define gen86_movl_dr_mod gen86_mov_dr_mod
#define gen86_movl_mod_cr gen86_mov_mod_cr
#define gen86_movl_mod_dr gen86_mov_mod_dr
#endif /* LIBGEN86_TARGET_BITS != 64 */

#define gen86_wrmsr(p_pc)    /* wrmsr    */ _gen86_putb2(p_pc, 0x0f, 0x30)
#define gen86_rdtsc(p_pc)    /* rdtsc    */ _gen86_putb2(p_pc, 0x0f, 0x31)
#define gen86_rdmsr(p_pc)    /* rdmsr    */ _gen86_putb2(p_pc, 0x0f, 0x32)
#define gen86_rdpmc(p_pc)    /* rdpmc    */ _gen86_putb2(p_pc, 0x0f, 0x33)
#define gen86_sysenter(p_pc) /* sysenter */ _gen86_putb2(p_pc, 0x0f, 0x34)
#define gen86_sysexit(p_pc)  /* sysexit  */ _gen86_putb2(p_pc, 0x0f, 0x35)
#define gen86_getsec(p_pc)   /* getsec   */ _gen86_putb2(p_pc, 0x0f, 0x37)

#define gen86_cmovccw_mod_r(p_pc, cc, gen_modrm, reg, ...) /* cmovccw ..., %reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x40 + (cc)), reg, __VA_ARGS__, (void)0))
#define gen86_cmovccl_mod_r(p_pc, cc, gen_modrm, reg, ...) /* cmovccl ..., %reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x40 + (cc)), reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_cmovccq_mod_r(p_pc, cc, gen_modrm, reg, ...) /* cmovccq ..., %reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0x40 + (cc)), reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_cmovccw_r_r(p_pc, cc, src_reg, dst_reg) /* cmovccw %src_reg, %dst_reg */ gen86_cmovccw_mod_r(p_pc, cc, gen86_modrm_r, dst_reg, src_reg)
#define gen86_cmovccl_r_r(p_pc, cc, src_reg, dst_reg) /* cmovccl %src_reg, %dst_reg */ gen86_cmovccl_mod_r(p_pc, cc, gen86_modrm_r, dst_reg, src_reg)
#if LIBGEN86_TARGET_BITS == 64
#define gen86_cmovccq_r_r(p_pc, cc, src_reg, dst_reg) /* cmovccq %src_reg, %dst_reg */ gen86_cmovccq_mod_r(p_pc, cc, gen86_modrm_r, dst_reg, src_reg)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_setcc_mod(p_pc, cc, gen_modrm, ...) /* setcc ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0x90 + (cc)), 0, __VA_ARGS__, (void)0)

#define gen86_pushw_fs(p_pc) /* pushw %fs */ (_gen86_pfx16_(p_pc) _gen86_putb2(p_pc, 0x0f, 0xa0))
#define gen86_pushP_fs(p_pc) /* pushP %fs */ (_gen86_pfx32_(p_pc) _gen86_putb2(p_pc, 0x0f, 0xa0))
#define gen86_popw_fs(p_pc)  /* popw  %fs */ (_gen86_pfx16_(p_pc) _gen86_putb2(p_pc, 0x0f, 0xa1))
#define gen86_popP_fs(p_pc)  /* popP  %fs */ (_gen86_pfx32_(p_pc) _gen86_putb2(p_pc, 0x0f, 0xa1))
#define gen86_pushw_gs(p_pc) /* pushw %gs */ (_gen86_pfx16_(p_pc) _gen86_putb2(p_pc, 0x0f, 0xa8))
#define gen86_pushP_gs(p_pc) /* pushP %gs */ (_gen86_pfx32_(p_pc) _gen86_putb2(p_pc, 0x0f, 0xa8))
#define gen86_popw_gs(p_pc)  /* popw  %gs */ (_gen86_pfx16_(p_pc) _gen86_putb2(p_pc, 0x0f, 0xa9))
#define gen86_popP_gs(p_pc)  /* popP  %gs */ (_gen86_pfx32_(p_pc) _gen86_putb2(p_pc, 0x0f, 0xa9))

#if LIBGEN86_TARGET_BITS == 64
#define gen86_pushq_fs gen86_pushP_fs
#define gen86_popq_fs  gen86_popP_fs
#define gen86_pushq_gs gen86_pushP_gs
#define gen86_popq_gs  gen86_popP_gs
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_pushl_fs gen86_pushP_fs
#define gen86_popl_fs  gen86_popP_fs
#define gen86_pushl_gs gen86_pushP_gs
#define gen86_popl_gs  gen86_popP_gs
#endif /* LIBGEN86_TARGET_BITS != 64 */

#define gen86_cpuid(p_pc) /* cpuid */ _gen86_putb2(p_pc, 0x0f, 0xa2)

#define gen86_btw_r_mod(p_pc, gen_modrm, reg, ...) /* btw %reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xa3), reg, __VA_ARGS__, (void)0))
#define gen86_btl_r_mod(p_pc, gen_modrm, reg, ...) /* btl %reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xa3), reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_btq_r_mod(p_pc, gen_modrm, reg, ...) /* btq %reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xa3), reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_shldw_imm_r_mod(p_pc, gen_modrm, imm, reg, ...) /* shldw %cl, %reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xa3), reg, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_shldl_imm_r_mod(p_pc, gen_modrm, imm, reg, ...) /* shldl %cl, %reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xa3), reg, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_shldw_cl_r_mod(p_pc, gen_modrm, reg, ...)       /* shldw %cl, %reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xa4), reg, __VA_ARGS__, (void)0))
#define gen86_shldl_cl_r_mod(p_pc, gen_modrm, reg, ...)       /* shldl %cl, %reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xa4), reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_shldq_imm_r_mod(p_pc, gen_modrm, imm, reg, ...) /* shldq %cl, %reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xa3), reg, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_shldq_cl_r_mod(p_pc, gen_modrm, reg, ...)       /* shldq %cl, %reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xa4), reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_rms(p_pc) /* rms */ _gen86_putb2(p_pc, 0x0f, 0xaa)

#define gen86_btsw_r_mod(p_pc, gen_modrm, reg, ...) /* btsw %reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xab), reg, __VA_ARGS__, (void)0))
#define gen86_btsl_r_mod(p_pc, gen_modrm, reg, ...) /* btsl %reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xab), reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_btsq_r_mod(p_pc, gen_modrm, reg, ...) /* btsq %reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xab), reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_shrdw_imm_r_mod(p_pc, gen_modrm, imm, reg, ...) /* shrdw %cl, %reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xac), reg, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_shrdl_imm_r_mod(p_pc, gen_modrm, imm, reg, ...) /* shrdl %cl, %reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xac), reg, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_shrdw_cl_r_mod(p_pc, gen_modrm, reg, ...)       /* shrdw %cl, %reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xad), reg, __VA_ARGS__, (void)0))
#define gen86_shrdl_cl_r_mod(p_pc, gen_modrm, reg, ...)       /* shrdl %cl, %reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xad), reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_shrdq_imm_r_mod(p_pc, gen_modrm, imm, reg, ...) /* shrdq %cl, %reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xac), reg, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_shrdq_cl_r_mod(p_pc, gen_modrm, reg, ...)       /* shrdq %cl, %reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xad), reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */


#define gen86_rdfsbasel(p_pc, reg) /* rdfsbasel %reg */ (_gen86_putb(p_pc, 0xf3), gen86_modrm_r(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xae), 0, reg, (void)0))
#define gen86_rdgsbasel(p_pc, reg) /* rdgsbasel %reg */ (_gen86_putb(p_pc, 0xf3), gen86_modrm_r(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xae), 1, reg, (void)0))
#define gen86_wrfsbasel(p_pc, reg) /* wrfsbasel %reg */ (_gen86_putb(p_pc, 0xf3), gen86_modrm_r(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xae), 2, reg, (void)0))
#define gen86_wrgsbasel(p_pc, reg) /* wrgsbasel %reg */ (_gen86_putb(p_pc, 0xf3), gen86_modrm_r(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xae), 3, reg, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_rdfsbaseq(p_pc, reg) /* rdfsbaseq %reg */ (_gen86_putb(p_pc, 0xf3), gen86_modrm_r(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xae), 0, reg, (void)0))
#define gen86_rdgsbaseq(p_pc, reg) /* rdgsbaseq %reg */ (_gen86_putb(p_pc, 0xf3), gen86_modrm_r(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xae), 1, reg, (void)0))
#define gen86_wrfsbaseq(p_pc, reg) /* wrfsbaseq %reg */ (_gen86_putb(p_pc, 0xf3), gen86_modrm_r(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xae), 2, reg, (void)0))
#define gen86_wrgsbaseq(p_pc, reg) /* wrgsbaseq %reg */ (_gen86_putb(p_pc, 0xf3), gen86_modrm_r(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xae), 3, reg, (void)0))
#endif /* LIBGEN86_TARGET_BITS == 64 */


#define gen86_fxsave(p_pc, gen_modrm, ...)     /* fxsave     ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xae), 0, __VA_ARGS__, (void)0)
#define gen86_fxrstor(p_pc, gen_modrm, ...)    /* fxrstor    ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xae), 1, __VA_ARGS__, (void)0)
#define gen86_ldmxcsr(p_pc, gen_modrm, ...)    /* ldmxcsr    ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xae), 2, __VA_ARGS__, (void)0)
#define gen86_stmxcsr(p_pc, gen_modrm, ...)    /* stmxcsr    ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xae), 3, __VA_ARGS__, (void)0)
#define gen86_xsave(p_pc, gen_modrm, ...)      /* xsave      ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xae), 4, __VA_ARGS__, (void)0)
#define gen86_xrstor(p_pc, gen_modrm, ...)     /* xrstor     ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xae), 5, __VA_ARGS__, (void)0)
#define gen86_xsaveopt(p_pc, gen_modrm, ...)   /* xsaveopt   ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xae), 6, __VA_ARGS__, (void)0)
#define gen86_clflushopt(p_pc, gen_modrm, ...) /* clflushopt ... */ (_gen86_putb(p_pc, 0x66),gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xae), 7, __VA_ARGS__, (void)0))
#define gen86_clflush(p_pc, gen_modrm, ...)    /* clflush    ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xae), 7, __VA_ARGS__, (void)0)
#if LIBGEN86_TARGET_BITS == 64
#define gen86_fxsave64(p_pc, gen_modrm, ...)   /* fxsave64   ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xae), 0, __VA_ARGS__, (void)0)
#define gen86_fxrstor64(p_pc, gen_modrm, ...)  /* fxrstor64  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xae), 1, __VA_ARGS__, (void)0)
#define gen86_xsave64(p_pc, gen_modrm, ...)    /* xsave64    ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xae), 4, __VA_ARGS__, (void)0)
#define gen86_xrstor64(p_pc, gen_modrm, ...)   /* xrstor64   ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xae), 5, __VA_ARGS__, (void)0)
#define gen86_xsaveopt64(p_pc, gen_modrm, ...) /* xsaveopt64 ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xae), 6, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_lfence(p_pc) /* lfence */ _gen86_putb3(p_pc, 0x0f, 0xae, 0xe8)
#define gen86_mfence(p_pc) /* lfence */ _gen86_putb3(p_pc, 0x0f, 0xae, 0xf0)
#define gen86_sfence(p_pc) /* lfence */ _gen86_putb3(p_pc, 0x0f, 0xae, 0xf8)

#define gen86_imulw_mod_r(p_pc, gen_modrm, reg, ...) /* imulw ..., %reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xaf), reg, __VA_ARGS__, (void)0))
#define gen86_imull_mod_r(p_pc, gen_modrm, reg, ...) /* imull ..., %reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xaf), reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_imulq_mod_r(p_pc, gen_modrm, reg, ...) /* imulq ..., %reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xaf), reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_cmpxchgb_r_mod(p_pc, gen_modrm, reg, ...) /* cmpxchgb %reg, ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xb0), reg, __VA_ARGS__, (void)0)
#define gen86_cmpxchgw_r_mod(p_pc, gen_modrm, reg, ...) /* cmpxchgw %reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xb1), reg, __VA_ARGS__, (void)0))
#define gen86_cmpxchgl_r_mod(p_pc, gen_modrm, reg, ...) /* cmpxchgl %reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xb1), reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_cmpxchgq_r_mod(p_pc, gen_modrm, reg, ...) /* cmpxchgq %reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xb1), reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_btrw_r_mod(p_pc, gen_modrm, reg, ...) /* btrw %reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xb3), reg, __VA_ARGS__, (void)0))
#define gen86_btrl_r_mod(p_pc, gen_modrm, reg, ...) /* btrl %reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xb3), reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_btrq_r_mod(p_pc, gen_modrm, reg, ...) /* btrq %reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xb3), reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_movzbw_mod_r(p_pc, gen_modrm, reg, ...) /* movzbw ..., %reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xb6), reg, __VA_ARGS__, (void)0))
#define gen86_movzbl_mod_r(p_pc, gen_modrm, reg, ...) /* movzbl ..., %reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xb6), reg, __VA_ARGS__, (void)0))
#define gen86_movzwl_mod_r(p_pc, gen_modrm, reg, ...) /* movzwl ..., %reg */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xb7), reg, __VA_ARGS__, (void)0)
#if LIBGEN86_TARGET_BITS == 64
#define gen86_movzbq_mod_r(p_pc, gen_modrm, reg, ...) /* movzbq ..., %reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xb6), reg, __VA_ARGS__, (void)0)
#define gen86_movzwq_mod_r(p_pc, gen_modrm, reg, ...) /* movzwq ..., %reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xb7), reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_popcntw_mod_r(p_pc, gen_modrm, reg, ...) /* popcntw ..., %reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xb8), reg, __VA_ARGS__, (void)0))
#define gen86_popcntl_mod_r(p_pc, gen_modrm, reg, ...) /* popcntl ..., %reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xb8), reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_popcntq_mod_r(p_pc, gen_modrm, reg, ...) /* popcntq ..., %reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xb8), reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_ud1_mod(p_pc, gen_modrm, reg, ...) /* ud1 ..., %reg */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xb9), reg, __VA_ARGS__, (void)0)


#define gen86_btw_imm_mod(p_pc, gen_modrm, imm, ...)  /* btw    $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xba), 4, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_btl_imm_mod(p_pc, gen_modrm, imm, ...)  /* btl    $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xba), 4, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_btsw_imm_mod(p_pc, gen_modrm, imm, ...) /* btsw   $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xba), 5, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_btsl_imm_mod(p_pc, gen_modrm, imm, ...) /* btsl   $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xba), 5, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_btrw_imm_mod(p_pc, gen_modrm, imm, ...) /* btrw   $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xba), 6, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_btrl_imm_mod(p_pc, gen_modrm, imm, ...) /* btrl   $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xba), 6, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_btcw_imm_mod(p_pc, gen_modrm, imm, ...) /* btcw   $imm, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xba), 7, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_btcl_imm_mod(p_pc, gen_modrm, imm, ...) /* btcl   $imm, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xba), 7, __VA_ARGS__, _gen86_putb(p_pc, imm)))
#define gen86_btcw_r_mod(p_pc, gen_modrm, reg, ...)   /* btcw   %reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xbb), reg, __VA_ARGS__, (void)0))
#define gen86_btcl_r_mod(p_pc, gen_modrm, reg, ...)   /* btcl   %reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xbb), reg, __VA_ARGS__, (void)0))
#define gen86_bsfw_mod_r(p_pc, gen_modrm, reg, ...)   /* bsfw   ..., %reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xbc), reg, __VA_ARGS__, (void)0))
#define gen86_bsfl_mod_r(p_pc, gen_modrm, reg, ...)   /* bsfl   ..., %reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xbc), reg, __VA_ARGS__, (void)0))
#define gen86_tzcntw_mod_r(p_pc, gen_modrm, reg, ...) /* tzcntw ..., %reg */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xbc), reg, __VA_ARGS__, (void)0))
#define gen86_tzcntl_mod_r(p_pc, gen_modrm, reg, ...) /* tzcntl ..., %reg */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xbc), reg, __VA_ARGS__, (void)0))
#define gen86_bsrw_mod_r(p_pc, gen_modrm, reg, ...)   /* bsrw   ..., %reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xbd), reg, __VA_ARGS__, (void)0))
#define gen86_bsrl_mod_r(p_pc, gen_modrm, reg, ...)   /* bsrl   ..., %reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xbd), reg, __VA_ARGS__, (void)0))
#define gen86_lzcntw_mod_r(p_pc, gen_modrm, reg, ...) /* lzcntw ..., %reg */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xbd), reg, __VA_ARGS__, (void)0))
#define gen86_lzcntl_mod_r(p_pc, gen_modrm, reg, ...) /* lzcntl ..., %reg */ (_gen86_putb(p_pc, 0xf3), _gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xbd), reg, __VA_ARGS__, (void)0))
#define gen86_movsbw_mod_r(p_pc, gen_modrm, reg, ...) /* movsbw ..., %reg */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xbe), reg, __VA_ARGS__, (void)0))
#define gen86_movsbl_mod_r(p_pc, gen_modrm, reg, ...) /* movsbl ..., %reg */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xbe), reg, __VA_ARGS__, (void)0))
#define gen86_movswl_mod_r(p_pc, gen_modrm, reg, ...) /* movswl ..., %reg */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xbf), reg, __VA_ARGS__, (void)0)
#define gen86_xaddb_r_mod(p_pc, gen_modrm, reg, ...)  /* xaddb  %reg, ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xc0), reg, __VA_ARGS__, (void)0)
#define gen86_xaddw_r_mod(p_pc, gen_modrm, reg, ...)  /* xaddw  %reg, ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xc1), reg, __VA_ARGS__, (void)0))
#define gen86_xaddl_r_mod(p_pc, gen_modrm, reg, ...)  /* xaddl  %reg, ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xc1), reg, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_btq_imm_mod(p_pc, gen_modrm, imm, ...)  /* btq    $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xba), 4, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_btsq_imm_mod(p_pc, gen_modrm, imm, ...) /* btsq   $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xba), 5, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_btrq_imm_mod(p_pc, gen_modrm, imm, ...) /* btrq   $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xba), 6, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_btcq_imm_mod(p_pc, gen_modrm, imm, ...) /* btcq   $imm, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xba), 7, __VA_ARGS__, _gen86_putb(p_pc, imm))
#define gen86_btcq_r_mod(p_pc, gen_modrm, reg, ...)   /* btcq   %reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xbb), reg, __VA_ARGS__, (void)0)
#define gen86_bsfq_mod_r(p_pc, gen_modrm, reg, ...)   /* bsfq   ..., %reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xbc), reg, __VA_ARGS__, (void)0)
#define gen86_tzcntq_mod_r(p_pc, gen_modrm, reg, ...) /* tzcntq ..., %reg */ (_gen86_putb(p_pc, 0xf3), gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xbc), reg, __VA_ARGS__, (void)0))
#define gen86_bsrq_mod_r(p_pc, gen_modrm, reg, ...)   /* bsrq   ..., %reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xbd), reg, __VA_ARGS__, (void)0)
#define gen86_lzcntq_mod_r(p_pc, gen_modrm, reg, ...) /* lzcntq ..., %reg */ (_gen86_putb(p_pc, 0xf3), gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xbd), reg, __VA_ARGS__, (void)0))
#define gen86_movsbq_mod_r(p_pc, gen_modrm, reg, ...) /* movsbq ..., %reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xbe), reg, __VA_ARGS__, (void)0)
#define gen86_movswq_mod_r(p_pc, gen_modrm, reg, ...) /* movswq ..., %reg */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xbf), reg, __VA_ARGS__, (void)0)
#define gen86_xaddq_r_mod(p_pc, gen_modrm, reg, ...)  /* xaddq  %reg, ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xc1), reg, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#if LIBGEN86_TARGET_BITS == 64
#define gen86_cmpxchg16b_mod(p_pc, gen_modrm, ...) /* cmpxchg16b ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xc7), 1, __VA_ARGS__, (void)0)
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_cmpxchg8b_mod(p_pc, gen_modrm, ...) /* cmpxchg8b ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xc7), 1, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS != 64 */

#define gen86_xrstors_mod(p_pc, gen_modrm, ...)   /* xrstors   ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xc7), 3, __VA_ARGS__, (void)0)
#define gen86_xsavec_mod(p_pc, gen_modrm, ...)    /* xsavec    ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xc7), 4, __VA_ARGS__, (void)0)
#define gen86_xsaves_mod(p_pc, gen_modrm, ...)    /* xsaves    ... */ gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xc7), 5, __VA_ARGS__, (void)0)
#if LIBGEN86_TARGET_BITS == 64
#define gen86_xrstors64_mod(p_pc, gen_modrm, ...) /* xrstors64 ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xc7), 3, __VA_ARGS__, (void)0)
#define gen86_xsavec64_mod(p_pc, gen_modrm, ...)  /* xsavec64  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xc7), 4, __VA_ARGS__, (void)0)
#define gen86_xsaves64_mod(p_pc, gen_modrm, ...)  /* xsaves64  ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xc7), 5, __VA_ARGS__, (void)0)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_rdrandw_mod(p_pc, gen_modrm, ...) /* rdrandw ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xc7), 6, __VA_ARGS__, (void)0))
#define gen86_rdrandl_mod(p_pc, gen_modrm, ...) /* rdrandl ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xc7), 6, __VA_ARGS__, (void)0))
#define gen86_rdseedw_mod(p_pc, gen_modrm, ...) /* rdseedw ... */ (_gen86_pfx16_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xc7), 7, __VA_ARGS__, (void)0))
#define gen86_rdseedl_mod(p_pc, gen_modrm, ...) /* rdseedl ... */ (_gen86_pfx32_(p_pc) gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xc7), 7, __VA_ARGS__, (void)0))
#define gen86_rdpidP_mod(p_pc, gen_modrm, ...)  /* rdpidP  ... */ (_gen86_putb(p_pc, 0xf3), gen_modrm(p_pc, 0, _gen86_putb2(p_pc, 0x0f, 0xc7), 7, __VA_ARGS__, (void)0))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_rdrandq_mod(p_pc, gen_modrm, ...) /* rdrandq ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xc7), 6, __VA_ARGS__, (void)0)
#define gen86_rdseedq_mod(p_pc, gen_modrm, ...) /* rdseedq ... */ gen_modrm(p_pc, GEN86_REX_W, _gen86_putb2(p_pc, 0x0f, 0xc7), 7, __VA_ARGS__, (void)0)
#define gen86_rdpidq_mod gen86_rdpidP_mod
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_rdpidl_mod gen86_rdpidP_mod
#endif /* LIBGEN86_TARGET_BITS != 64 */

#if LIBGEN86_TARGET_BITS == 64
#define gen86_bswapl(p_pc, reg) /* bswapl %reg */ (!((reg) & 8) || (_gen86_putb(p_pc, 0x40 | GEN86_REX_B), 0), _gen86_putb2(p_pc, 0xf0, 0xc8 + (reg)&7))
#define gen86_bswapq(p_pc, reg) /* bswapq %reg */ (_gen86_putb(p_pc, 0x40 | GEN86_REX_W | ((reg) & 8 ? GEN86_REX_B : 0)), _gen86_putb2(p_pc, 0xf0, 0xc8 + (reg)&7))
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_bswapl(p_pc, reg) /* bswapl %reg */ _gen86_putb2(p_pc, 0xf0, 0xc8 + (reg))
#endif /* LIBGEN86_TARGET_BITS != 64 */

#define gen86_ud0(p_pc) /* ud0 */ _gen86_putb2(0xf0, 0xff)



/* Compatibility/pointer-sized instructions */
#if LIBGEN86_TARGET_BITS == 64
#define gen86_movzbP_mod_r      gen86_movzbq_mod_r
#define gen86_movzwP_mod_r      gen86_movzwq_mod_r
#define gen86_movzlP_mod_r      gen86_movl_mod_r
#define gen86_movsbP_mod_r      gen86_movsbq_mod_r
#define gen86_movswP_mod_r      gen86_movswq_mod_r
#define gen86_movslP_mod_r      gen86_movslq_mod_r
#define gen86_addP_r_mod        gen86_addq_r_mod
#define gen86_addP_mod_r        gen86_addq_mod_r
#define gen86_addP_imm_Pax      gen86_addq_imm_rax
#define gen86_addP_imm_mod      gen86_addq_imm_mod
#define gen86_addP_imm8s_mod    gen86_addq_imm8s_mod
#define gen86_orP_r_mod         gen86_orq_r_mod
#define gen86_orP_mod_r         gen86_orq_mod_r
#define gen86_orP_imm_Pax       gen86_orq_imm_rax
#define gen86_orP_imm_mod       gen86_orq_imm_mod
#define gen86_orP_imm8s_mod     gen86_orq_imm8s_mod
#define gen86_adcP_r_mod        gen86_adcq_r_mod
#define gen86_adcP_mod_r        gen86_adcq_mod_r
#define gen86_adcP_imm_Pax      gen86_adcq_imm_rax
#define gen86_adcP_imm_mod      gen86_adcq_imm_mod
#define gen86_adcP_imm8s_mod    gen86_adcq_imm8s_mod
#define gen86_sbbP_r_mod        gen86_sbbq_r_mod
#define gen86_sbbP_mod_r        gen86_sbbq_mod_r
#define gen86_sbbP_imm_Pax      gen86_sbbq_imm_rax
#define gen86_sbbP_imm_mod      gen86_sbbq_imm_mod
#define gen86_sbbP_imm8s_mod    gen86_sbbq_imm8s_mod
#define gen86_andP_r_mod        gen86_andq_r_mod
#define gen86_andP_mod_r        gen86_andq_mod_r
#define gen86_andP_imm_Pax      gen86_andq_imm_rax
#define gen86_andP_imm_mod      gen86_andq_imm_mod
#define gen86_andP_imm8s_mod    gen86_andq_imm8s_mod
#define gen86_subP_r_mod        gen86_subq_r_mod
#define gen86_subP_mod_r        gen86_subq_mod_r
#define gen86_subP_imm_Pax      gen86_subq_imm_rax
#define gen86_subP_imm_mod      gen86_subq_imm_mod
#define gen86_subP_imm8s_mod    gen86_subq_imm8s_mod
#define gen86_xorP_r_mod        gen86_xorq_r_mod
#define gen86_xorP_mod_r        gen86_xorq_mod_r
#define gen86_xorP_imm_Pax      gen86_xorq_imm_rax
#define gen86_xorP_imm_mod      gen86_xorq_imm_mod
#define gen86_xorP_imm8s_mod    gen86_xorq_imm8s_mod
#define gen86_cmpP_r_mod        gen86_cmpq_r_mod
#define gen86_cmpP_mod_r        gen86_cmpq_mod_r
#define gen86_cmpP_imm_Pax      gen86_cmpq_imm_rax
#define gen86_cmpP_imm_mod      gen86_cmpq_imm_mod
#define gen86_cmpP_imm8s_mod    gen86_cmpq_imm8s_mod
#define gen86_incP_r            gen86_incq_r
#define gen86_decP_r            gen86_decq_r
#define gen86_pushP_r           gen86_pushq_r
#define gen86_popP_r            gen86_popq_r
#define gen86_pushP_imm         gen86_pushq_imm
#define gen86_pushP_imm8s       gen86_pushq_imm8s
#define gen86_imulP_imm_mod_r   gen86_imulq_imm_mod_r
#define gen86_imulP_imm8s_mod_r gen86_imulq_imm8s_mod_r
#define gen86_testP_r_mod       gen86_testq_r_mod
#define gen86_xchgP_r_mod       gen86_xchgq_r_mod
#define gen86_movP_r_mod        gen86_movq_r_mod
#define gen86_movP_mod_r        gen86_movq_mod_r
#define gen86_movP_sgr_mod      gen86_movq_sgr_mod
#define gen86_movP_mod_sgr      gen86_movq_mod_sgr
#define gen86_leaP_mod_r        gen86_leaq_mod_r
#define gen86_popP_mod          gen86_popq_mod
#define gen86_xchgP_r_Pax       gen86_xchgq_r_rax
#define gen86_pushfP            gen86_pushfq
#define gen86_popfP             gen86_popfq
#define gen86_movsP             gen86_movsq
#define gen86_rep_movsP         gen86_rep_movsq
#define gen86_stosP             gen86_stosq
#define gen86_rep_stosP         gen86_rep_stosq
#define gen86_lodsP             gen86_lodsq
#define gen86_rep_lodsP         gen86_rep_lodsq
#define gen86_cmpsP             gen86_cmpsq
#define gen86_repe_cmpsP        gen86_repe_cmpsq
#define gen86_repne_cmpsP       gen86_repne_cmpsq
#define gen86_scasP             gen86_scasq
#define gen86_repe_scasP        gen86_repe_scasq
#define gen86_repne_scasP       gen86_repne_scasq
#define gen86_testP_imm_Pax     gen86_testq_imm_rax
#define gen86_movP_imm_r        gen86_movq_imm_r
#define gen86_rolP_imm_mod      gen86_rolq_imm_mod
#define gen86_rolP_1_mod        gen86_rolq_1_mod
#define gen86_rolP_cl_mod       gen86_rolq_cl_mod
#define gen86_rorP_imm_mod      gen86_rorq_imm_mod
#define gen86_rorP_1_mod        gen86_rorq_1_mod
#define gen86_rorP_cl_mod       gen86_rorq_cl_mod
#define gen86_rclP_imm_mod      gen86_rclq_imm_mod
#define gen86_rclP_1_mod        gen86_rclq_1_mod
#define gen86_rclP_cl_mod       gen86_rclq_cl_mod
#define gen86_rcrP_imm_mod      gen86_rcrq_imm_mod
#define gen86_rcrP_1_mod        gen86_rcrq_1_mod
#define gen86_rcrP_cl_mod       gen86_rcrq_cl_mod
#define gen86_shlP_imm_mod      gen86_shlq_imm_mod
#define gen86_shlP_1_mod        gen86_shlq_1_mod
#define gen86_shlP_cl_mod       gen86_shlq_cl_mod
#define gen86_shrP_imm_mod      gen86_shrq_imm_mod
#define gen86_shrP_1_mod        gen86_shrq_1_mod
#define gen86_shrP_cl_mod       gen86_shrq_cl_mod
#define gen86_salP_imm_mod      gen86_salq_imm_mod
#define gen86_salP_1_mod        gen86_salq_1_mod
#define gen86_salP_cl_mod       gen86_salq_cl_mod
#define gen86_sarP_imm_mod      gen86_sarq_imm_mod
#define gen86_sarP_1_mod        gen86_sarq_1_mod
#define gen86_sarP_cl_mod       gen86_sarq_cl_mod
#define gen86_retP_imm          gen86_retq_imm
#define gen86_retP              gen86_retq
#define gen86_movP_imm_mod      gen86_movq_imm_mod
#define gen86_iretP             gen86_iretq
#define gen86_testP_imm_mod     gen86_testq_imm_mod
#define gen86_notP_mod          gen86_notq_mod
#define gen86_negP_mod          gen86_negq_mod
#define gen86_mulP_mod          gen86_mulq_mod
#define gen86_imulP_mod         gen86_imulq_mod
#define gen86_divP_mod          gen86_divq_mod
#define gen86_idivP_mod         gen86_idivq_mod
#define gen86_incP_mod          gen86_incq_mod
#define gen86_decP_mod          gen86_decq_mod
#define gen86_callP_mod         gen86_callq_mod
#define gen86_lcallP_mod        gen86_lcallq_mod
#define gen86_jmpP_mod          gen86_jmpq_mod
#define gen86_ljmpP_mod         gen86_ljmpq_mod
#define gen86_pushP_mod         gen86_pushq_mod
#define gen86_smswP             gen86_smswq
#define gen86_lmswP             gen86_lmswq
#define gen86_lslP_mod_r        gen86_lslq_mod_r
#define gen86_movP_cr_mod       gen86_movq_cr_mod
#define gen86_movP_dr_mod       gen86_movq_dr_mod
#define gen86_movP_mod_cr       gen86_movq_mod_cr
#define gen86_movP_mod_dr       gen86_movq_mod_dr
#define gen86_cmovccP_mod_r     gen86_cmovccq_mod_r
#define gen86_cmovccP_r_r       gen86_cmovccq_r_r
#define gen86_btP_r_mod         gen86_btq_r_mod
#define gen86_shldP_imm_r_mod   gen86_shldq_imm_r_mod
#define gen86_shldP_cl_r_mod    gen86_shldq_cl_r_mod
#define gen86_btsP_r_mod        gen86_btsq_r_mod
#define gen86_shrdP_imm_r_mod   gen86_shrdq_imm_r_mod
#define gen86_shrdP_cl_r_mod    gen86_shrdq_cl_r_mod
#define gen86_rdfsbaseP         gen86_rdfsbaseq
#define gen86_rdgsbaseP         gen86_rdgsbaseq
#define gen86_wrfsbaseP         gen86_wrfsbaseq
#define gen86_wrgsbaseP         gen86_wrgsbaseq
#define gen86_imulP_mod_r       gen86_imulq_mod_r
#define gen86_cmpxchgP_r_mod    gen86_cmpxchgq_r_mod
#define gen86_btrP_r_mod        gen86_btrq_r_mod
#define gen86_popcntP_mod_r     gen86_popcntq_mod_r
#define gen86_btP_imm_mod       gen86_btq_imm_mod
#define gen86_btsP_imm_mod      gen86_btsq_imm_mod
#define gen86_btrP_imm_mod      gen86_btrq_imm_mod
#define gen86_btcP_imm_mod      gen86_btcq_imm_mod
#define gen86_btcP_r_mod        gen86_btcq_r_mod
#define gen86_bsfP_mod_r        gen86_bsfq_mod_r
#define gen86_tzcntP_mod_r      gen86_tzcntq_mod_r
#define gen86_bsrP_mod_r        gen86_bsrq_mod_r
#define gen86_lzcntP_mod_r      gen86_lzcntq_mod_r
#define gen86_xaddP_r_mod       gen86_xaddq_r_mod
#define gen86_rdrandP_mod       gen86_rdrandq_mod
#define gen86_rdseedP_mod       gen86_rdseedq_mod
#define gen86_bswapP            gen86_bswapq
#elif LIBGEN86_TARGET_BITS == 32
#define gen86_movzbP_mod_r      gen86_movzbl_mod_r
#define gen86_movzwP_mod_r      gen86_movzwl_mod_r
#define gen86_movzlP_mod_r      gen86_movl_mod_r
#define gen86_movsbP_mod_r      gen86_movsbl_mod_r
#define gen86_movswP_mod_r      gen86_movswl_mod_r
#define gen86_movslP_mod_r      gen86_movl_mod_r
#define gen86_addP_r_mod        gen86_addl_r_mod
#define gen86_addP_mod_r        gen86_addl_mod_r
#define gen86_addP_imm_Pax      gen86_addl_imm_eax
#define gen86_addP_imm_mod      gen86_addl_imm_mod
#define gen86_addP_imm8s_mod    gen86_addl_imm8s_mod
#define gen86_orP_r_mod         gen86_orl_r_mod
#define gen86_orP_mod_r         gen86_orl_mod_r
#define gen86_orP_imm_Pax       gen86_orl_imm_eax
#define gen86_orP_imm_mod       gen86_orl_imm_mod
#define gen86_orP_imm8s_mod     gen86_orl_imm8s_mod
#define gen86_adcP_r_mod        gen86_adcl_r_mod
#define gen86_adcP_mod_r        gen86_adcl_mod_r
#define gen86_adcP_imm_Pax      gen86_adcl_imm_eax
#define gen86_adcP_imm_mod      gen86_adcl_imm_mod
#define gen86_adcP_imm8s_mod    gen86_adcl_imm8s_mod
#define gen86_sbbP_r_mod        gen86_sbbl_r_mod
#define gen86_sbbP_mod_r        gen86_sbbl_mod_r
#define gen86_sbbP_imm_Pax      gen86_sbbl_imm_eax
#define gen86_sbbP_imm_mod      gen86_sbbl_imm_mod
#define gen86_sbbP_imm8s_mod    gen86_sbbl_imm8s_mod
#define gen86_andP_r_mod        gen86_andl_r_mod
#define gen86_andP_mod_r        gen86_andl_mod_r
#define gen86_andP_imm_Pax      gen86_andl_imm_eax
#define gen86_andP_imm_mod      gen86_andl_imm_mod
#define gen86_andP_imm8s_mod    gen86_andl_imm8s_mod
#define gen86_subP_r_mod        gen86_subl_r_mod
#define gen86_subP_mod_r        gen86_subl_mod_r
#define gen86_subP_imm_Pax      gen86_subl_imm_eax
#define gen86_subP_imm_mod      gen86_subl_imm_mod
#define gen86_subP_imm8s_mod    gen86_subl_imm8s_mod
#define gen86_xorP_r_mod        gen86_xorl_r_mod
#define gen86_xorP_mod_r        gen86_xorl_mod_r
#define gen86_xorP_imm_Pax      gen86_xorl_imm_eax
#define gen86_xorP_imm_mod      gen86_xorl_imm_mod
#define gen86_xorP_imm8s_mod    gen86_xorl_imm8s_mod
#define gen86_cmpP_r_mod        gen86_cmpl_r_mod
#define gen86_cmpP_mod_r        gen86_cmpl_mod_r
#define gen86_cmpP_imm_Pax      gen86_cmpl_imm_eax
#define gen86_cmpP_imm_mod      gen86_cmpl_imm_mod
#define gen86_cmpP_imm8s_mod    gen86_cmpl_imm8s_mod
#define gen86_incP_r            gen86_incl_r
#define gen86_decP_r            gen86_decl_r
#define gen86_pushP_r           gen86_pushl_r
#define gen86_popP_r            gen86_popl_r
#define gen86_pushP_imm         gen86_pushl_imm
#define gen86_pushP_imm8s       gen86_pushl_imm8s
#define gen86_imulP_imm_mod_r   gen86_imull_imm_mod_r
#define gen86_imulP_imm8s_mod_r gen86_imull_imm8s_mod_r
#define gen86_testP_r_mod       gen86_testl_r_mod
#define gen86_xchgP_r_mod       gen86_xchgl_r_mod
#define gen86_movP_r_mod        gen86_movl_r_mod
#define gen86_movP_mod_r        gen86_movl_mod_r
#define gen86_movP_sgr_mod      gen86_movl_sgr_mod
#define gen86_movP_mod_sgr      gen86_movl_mod_sgr
#define gen86_leaP_mod_r        gen86_leal_mod_r
#define gen86_popP_mod          gen86_popl_mod
#define gen86_xchgP_r_Pax       gen86_xchgl_r_eax
#define gen86_pushfP            gen86_pushfl
#define gen86_popfP             gen86_popfl
#define gen86_movsP             gen86_movsl
#define gen86_rep_movsP         gen86_rep_movsl
#define gen86_stosP             gen86_stosl
#define gen86_rep_stosP         gen86_rep_stosl
#define gen86_lodsP             gen86_lodsl
#define gen86_rep_lodsP         gen86_rep_lodsl
#define gen86_cmpsP             gen86_cmpsl
#define gen86_repe_cmpsP        gen86_repe_cmpsl
#define gen86_repne_cmpsP       gen86_repne_cmpsl
#define gen86_scasP             gen86_scasl
#define gen86_repe_scasP        gen86_repe_scasl
#define gen86_repne_scasP       gen86_repne_scasl
#define gen86_testP_imm_Pax     gen86_testl_imm_eax
#define gen86_movP_imm_r        gen86_movl_imm_r
#define gen86_rolP_imm_mod      gen86_roll_imm_mod
#define gen86_rolP_1_mod        gen86_roll_1_mod
#define gen86_rolP_cl_mod       gen86_roll_cl_mod
#define gen86_rorP_imm_mod      gen86_rorl_imm_mod
#define gen86_rorP_1_mod        gen86_rorl_1_mod
#define gen86_rorP_cl_mod       gen86_rorl_cl_mod
#define gen86_rclP_imm_mod      gen86_rcll_imm_mod
#define gen86_rclP_1_mod        gen86_rcll_1_mod
#define gen86_rclP_cl_mod       gen86_rcll_cl_mod
#define gen86_rcrP_imm_mod      gen86_rcrl_imm_mod
#define gen86_rcrP_1_mod        gen86_rcrl_1_mod
#define gen86_rcrP_cl_mod       gen86_rcrl_cl_mod
#define gen86_shlP_imm_mod      gen86_shll_imm_mod
#define gen86_shlP_1_mod        gen86_shll_1_mod
#define gen86_shlP_cl_mod       gen86_shll_cl_mod
#define gen86_shrP_imm_mod      gen86_shrl_imm_mod
#define gen86_shrP_1_mod        gen86_shrl_1_mod
#define gen86_shrP_cl_mod       gen86_shrl_cl_mod
#define gen86_salP_imm_mod      gen86_sall_imm_mod
#define gen86_salP_1_mod        gen86_sall_1_mod
#define gen86_salP_cl_mod       gen86_sall_cl_mod
#define gen86_sarP_imm_mod      gen86_sarl_imm_mod
#define gen86_sarP_1_mod        gen86_sarl_1_mod
#define gen86_sarP_cl_mod       gen86_sarl_cl_mod
#define gen86_retP_imm          gen86_retl_imm
#define gen86_retP              gen86_retl
#define gen86_movP_imm_mod      gen86_movl_imm_mod
#define gen86_iretP             gen86_iretl
#define gen86_testP_imm_mod     gen86_testl_imm_mod
#define gen86_notP_mod          gen86_notl_mod
#define gen86_negP_mod          gen86_negl_mod
#define gen86_mulP_mod          gen86_mull_mod
#define gen86_imulP_mod         gen86_imull_mod
#define gen86_divP_mod          gen86_divl_mod
#define gen86_idivP_mod         gen86_idivl_mod
#define gen86_incP_mod          gen86_incl_mod
#define gen86_decP_mod          gen86_decl_mod
#define gen86_callP_mod         gen86_calll_mod
#define gen86_lcallP_mod        gen86_lcalll_mod
#define gen86_jmpP_mod          gen86_jmpl_mod
#define gen86_ljmpP_mod         gen86_ljmpl_mod
#define gen86_pushP_mod         gen86_pushl_mod
#define gen86_smswP             gen86_smswl
#define gen86_lmswP             gen86_lmswl
#define gen86_lslP_mod_r        gen86_lsll_mod_r
#define gen86_movP_cr_mod       gen86_movl_cr_mod
#define gen86_movP_dr_mod       gen86_movl_dr_mod
#define gen86_movP_mod_cr       gen86_movl_mod_cr
#define gen86_movP_mod_dr       gen86_movl_mod_dr
#define gen86_cmovccP_mod_r     gen86_cmovccl_mod_r
#define gen86_cmovccP_r_r       gen86_cmovccl_r_r
#define gen86_btP_r_mod         gen86_btl_r_mod
#define gen86_shldP_imm_r_mod   gen86_shldl_imm_r_mod
#define gen86_shldP_cl_r_mod    gen86_shldl_cl_r_mod
#define gen86_btsP_r_mod        gen86_btsl_r_mod
#define gen86_shrdP_imm_r_mod   gen86_shrdl_imm_r_mod
#define gen86_shrdP_cl_r_mod    gen86_shrdl_cl_r_mod
#define gen86_rdfsbaseP         gen86_rdfsbasel
#define gen86_rdgsbaseP         gen86_rdgsbasel
#define gen86_wrfsbaseP         gen86_wrfsbasel
#define gen86_wrgsbaseP         gen86_wrgsbasel
#define gen86_imulP_mod_r       gen86_imull_mod_r
#define gen86_cmpxchgP_r_mod    gen86_cmpxchgl_r_mod
#define gen86_btrP_r_mod        gen86_btrl_r_mod
#define gen86_popcntP_mod_r     gen86_popcntl_mod_r
#define gen86_btP_imm_mod       gen86_btl_imm_mod
#define gen86_btsP_imm_mod      gen86_btsl_imm_mod
#define gen86_btrP_imm_mod      gen86_btrl_imm_mod
#define gen86_btcP_imm_mod      gen86_btcl_imm_mod
#define gen86_btcP_r_mod        gen86_btcl_r_mod
#define gen86_bsfP_mod_r        gen86_bsfl_mod_r
#define gen86_tzcntP_mod_r      gen86_tzcntl_mod_r
#define gen86_bsrP_mod_r        gen86_bsrl_mod_r
#define gen86_lzcntP_mod_r      gen86_lzcntl_mod_r
#define gen86_xaddP_r_mod       gen86_xaddl_r_mod
#define gen86_rdrandP_mod       gen86_rdrandl_mod
#define gen86_rdseedP_mod       gen86_rdseedl_mod
#define gen86_bswapP            gen86_bswapl
#else /* LIBGEN86_TARGET_BITS == ... */
#define gen86_movzbP_mod_r      gen86_movzbw_mod_r
#define gen86_movzwP_mod_r      gen86_movw_mod_r
#define gen86_movsbP_mod_r      gen86_movsbw_mod_r
#define gen86_movswP_mod_r      gen86_movw_mod_r
#define gen86_addP_r_mod        gen86_addw_r_mod
#define gen86_addP_mod_r        gen86_addw_mod_r
#define gen86_addP_imm_Pax      gen86_addw_imm_ax
#define gen86_addP_imm_mod      gen86_addw_imm_mod
#define gen86_addP_imm8s_mod    gen86_addw_imm8s_mod
#define gen86_orP_r_mod         gen86_orw_r_mod
#define gen86_orP_mod_r         gen86_orw_mod_r
#define gen86_orP_imm_Pax       gen86_orw_imm_ax
#define gen86_orP_imm_mod       gen86_orw_imm_mod
#define gen86_orP_imm8s_mod     gen86_orw_imm8s_mod
#define gen86_adcP_r_mod        gen86_adcw_r_mod
#define gen86_adcP_mod_r        gen86_adcw_mod_r
#define gen86_adcP_imm_Pax      gen86_adcw_imm_ax
#define gen86_adcP_imm_mod      gen86_adcw_imm_mod
#define gen86_adcP_imm8s_mod    gen86_adcw_imm8s_mod
#define gen86_sbbP_r_mod        gen86_sbbw_r_mod
#define gen86_sbbP_mod_r        gen86_sbbw_mod_r
#define gen86_sbbP_imm_Pax      gen86_sbbw_imm_ax
#define gen86_sbbP_imm_mod      gen86_sbbw_imm_mod
#define gen86_sbbP_imm8s_mod    gen86_sbbw_imm8s_mod
#define gen86_andP_r_mod        gen86_andw_r_mod
#define gen86_andP_mod_r        gen86_andw_mod_r
#define gen86_andP_imm_Pax      gen86_andw_imm_ax
#define gen86_andP_imm_mod      gen86_andw_imm_mod
#define gen86_andP_imm8s_mod    gen86_andw_imm8s_mod
#define gen86_subP_r_mod        gen86_subw_r_mod
#define gen86_subP_mod_r        gen86_subw_mod_r
#define gen86_subP_imm_Pax      gen86_subw_imm_ax
#define gen86_subP_imm_mod      gen86_subw_imm_mod
#define gen86_subP_imm8s_mod    gen86_subw_imm8s_mod
#define gen86_xorP_r_mod        gen86_xorw_r_mod
#define gen86_xorP_mod_r        gen86_xorw_mod_r
#define gen86_xorP_imm_Pax      gen86_xorw_imm_ax
#define gen86_xorP_imm_mod      gen86_xorw_imm_mod
#define gen86_xorP_imm8s_mod    gen86_xorw_imm8s_mod
#define gen86_cmpP_r_mod        gen86_cmpw_r_mod
#define gen86_cmpP_mod_r        gen86_cmpw_mod_r
#define gen86_cmpP_imm_Pax      gen86_cmpw_imm_ax
#define gen86_cmpP_imm_mod      gen86_cmpw_imm_mod
#define gen86_cmpP_imm8s_mod    gen86_cmpw_imm8s_mod
#define gen86_incP_r            gen86_incw_r
#define gen86_decP_r            gen86_decw_r
#define gen86_pushP_r           gen86_pushw_r
#define gen86_popP_r            gen86_popw_r
#define gen86_pushP_imm         gen86_pushw_imm
#define gen86_pushP_imm8s       gen86_pushw_imm8s
#define gen86_imulP_imm_mod_r   gen86_imulw_imm_mod_r
#define gen86_imulP_imm8s_mod_r gen86_imulw_imm8s_mod_r
#define gen86_testP_r_mod       gen86_testw_r_mod
#define gen86_xchgP_r_mod       gen86_xchgw_r_mod
#define gen86_movP_r_mod        gen86_movw_r_mod
#define gen86_movP_mod_r        gen86_movw_mod_r
#define gen86_movP_sgr_mod      gen86_movw_sgr_mod
#define gen86_movP_mod_sgr      gen86_movw_mod_sgr
#define gen86_leaP_mod_r        gen86_leaw_mod_r
#define gen86_popP_mod          gen86_popw_mod
#define gen86_xchgP_r_Pax       gen86_xchgw_r_ax
#define gen86_pushfP            gen86_pushfw
#define gen86_popfP             gen86_popfw
#define gen86_movsP             gen86_movsw
#define gen86_rep_movsP         gen86_rep_movsw
#define gen86_stosP             gen86_stosw
#define gen86_rep_stosP         gen86_rep_stosw
#define gen86_lodsP             gen86_lodsw
#define gen86_rep_lodsP         gen86_rep_lodsw
#define gen86_cmpsP             gen86_cmpsw
#define gen86_repe_cmpsP        gen86_repe_cmpsw
#define gen86_repne_cmpsP       gen86_repne_cmpsw
#define gen86_scasP             gen86_scasw
#define gen86_repe_scasP        gen86_repe_scasw
#define gen86_repne_scasP       gen86_repne_scasw
#define gen86_testP_imm_Pax     gen86_testw_imm_ax
#define gen86_movP_imm_r        gen86_movw_imm_r
#define gen86_rolP_imm_mod      gen86_rolw_imm_mod
#define gen86_rolP_1_mod        gen86_rolw_1_mod
#define gen86_rolP_cl_mod       gen86_rolw_cl_mod
#define gen86_rorP_imm_mod      gen86_rorw_imm_mod
#define gen86_rorP_1_mod        gen86_rorw_1_mod
#define gen86_rorP_cl_mod       gen86_rorw_cl_mod
#define gen86_rclP_imm_mod      gen86_rclw_imm_mod
#define gen86_rclP_1_mod        gen86_rclw_1_mod
#define gen86_rclP_cl_mod       gen86_rclw_cl_mod
#define gen86_rcrP_imm_mod      gen86_rcrw_imm_mod
#define gen86_rcrP_1_mod        gen86_rcrw_1_mod
#define gen86_rcrP_cl_mod       gen86_rcrw_cl_mod
#define gen86_shlP_imm_mod      gen86_shlw_imm_mod
#define gen86_shlP_1_mod        gen86_shlw_1_mod
#define gen86_shlP_cl_mod       gen86_shlw_cl_mod
#define gen86_shrP_imm_mod      gen86_shrw_imm_mod
#define gen86_shrP_1_mod        gen86_shrw_1_mod
#define gen86_shrP_cl_mod       gen86_shrw_cl_mod
#define gen86_salP_imm_mod      gen86_salw_imm_mod
#define gen86_salP_1_mod        gen86_salw_1_mod
#define gen86_salP_cl_mod       gen86_salw_cl_mod
#define gen86_sarP_imm_mod      gen86_sarw_imm_mod
#define gen86_sarP_1_mod        gen86_sarw_1_mod
#define gen86_sarP_cl_mod       gen86_sarw_cl_mod
#define gen86_retP_imm          gen86_retw_imm
#define gen86_retP              gen86_retw
#define gen86_movP_imm_mod      gen86_movw_imm_mod
#define gen86_iretP             gen86_iretw
#define gen86_testP_imm_mod     gen86_testw_imm_mod
#define gen86_notP_mod          gen86_notw_mod
#define gen86_negP_mod          gen86_negw_mod
#define gen86_mulP_mod          gen86_mulw_mod
#define gen86_imulP_mod         gen86_imulw_mod
#define gen86_divP_mod          gen86_divw_mod
#define gen86_idivP_mod         gen86_idivw_mod
#define gen86_incP_mod          gen86_incw_mod
#define gen86_decP_mod          gen86_decw_mod
#define gen86_callP_mod         gen86_callw_mod
#define gen86_lcallP_mod        gen86_lcallw_mod
#define gen86_jmpP_mod          gen86_jmpw_mod
#define gen86_ljmpP_mod         gen86_ljmpw_mod
#define gen86_pushP_mod         gen86_pushw_mod
#define gen86_smswP             gen86_smsww
#define gen86_lmswP             gen86_lmsww
#define gen86_lslP_mod_r        gen86_lslw_mod_r
#define gen86_cmovccP_mod_r     gen86_cmovccw_mod_r
#define gen86_cmovccP_r_r       gen86_cmovccw_r_r
#define gen86_btP_r_mod         gen86_btw_r_mod
#define gen86_shldP_imm_r_mod   gen86_shldw_imm_r_mod
#define gen86_shldP_cl_r_mod    gen86_shldw_cl_r_mod
#define gen86_btsP_r_mod        gen86_btsw_r_mod
#define gen86_shrdP_imm_r_mod   gen86_shrdw_imm_r_mod
#define gen86_shrdP_cl_r_mod    gen86_shrdw_cl_r_mod
#define gen86_imulP_mod_r       gen86_imulw_mod_r
#define gen86_cmpxchgP_r_mod    gen86_cmpxchgw_r_mod
#define gen86_btrP_r_mod        gen86_btrw_r_mod
#define gen86_popcntP_mod_r     gen86_popcntw_mod_r
#define gen86_btP_imm_mod       gen86_btw_imm_mod
#define gen86_btsP_imm_mod      gen86_btsw_imm_mod
#define gen86_btrP_imm_mod      gen86_btrw_imm_mod
#define gen86_btcP_imm_mod      gen86_btcw_imm_mod
#define gen86_btcP_r_mod        gen86_btcw_r_mod
#define gen86_bsfP_mod_r        gen86_bsfw_mod_r
#define gen86_tzcntP_mod_r      gen86_tzcntw_mod_r
#define gen86_bsrP_mod_r        gen86_bsrw_mod_r
#define gen86_lzcntP_mod_r      gen86_lzcntw_mod_r
#define gen86_xaddP_r_mod       gen86_xaddw_r_mod
#define gen86_rdrandP_mod       gen86_rdrandw_mod
#define gen86_rdseedP_mod       gen86_rdseedw_mod
#endif /* LIBGEN86_TARGET_BITS != ... */


/* Helper macros */

#define gen86_setcc_r(p_pc, cc, reg) /* setcc %reg */ gen86_setcc_mod(p_pc, cc, gen86_modrm_r, reg)

/*[[[deemon
local names = { "add", "or", "adc", "sbb", "and", "sub", "xor" };
for (local n: names) {
	local pad = " " * (4 - #n);
	print("#define gen86_", n, "b_r_r(p_pc, src_reg, dst_reg)", pad, " /" "* ", n, "b", pad, " %src_reg, %dst_reg *" "/ gen86_", n, "b_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)");
	print("#define gen86_", n, "w_r_r(p_pc, src_reg, dst_reg)", pad, " /" "* ", n, "w", pad, " %src_reg, %dst_reg *" "/ gen86_", n, "w_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)");
	print("#define gen86_", n, "l_r_r(p_pc, src_reg, dst_reg)", pad, " /" "* ", n, "l", pad, " %src_reg, %dst_reg *" "/ gen86_", n, "l_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)");
	print("#define gen86_", n, "P_r_r(p_pc, src_reg, dst_reg)", pad, " /" "* ", n, "P", pad, " %src_reg, %dst_reg *" "/ gen86_", n, "P_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)");
}
print("#if LIBGEN86_TARGET_BITS == 64");
for (local n: names) {
	local pad = " " * (4 - #n);
	print("#define gen86_", n, "q_r_r(p_pc, src_reg, dst_reg)", pad, " /" "* ", n, "q", pad, " %src_reg, %dst_reg *" "/ gen86_", n, "q_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)");
}
print("#endif /" "* LIBGEN86_TARGET_BITS == 64 *" "/");
]]]*/
#define gen86_addb_r_r(p_pc, src_reg, dst_reg)  /* addb  %src_reg, %dst_reg */ gen86_addb_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_addw_r_r(p_pc, src_reg, dst_reg)  /* addw  %src_reg, %dst_reg */ gen86_addw_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_addl_r_r(p_pc, src_reg, dst_reg)  /* addl  %src_reg, %dst_reg */ gen86_addl_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_addP_r_r(p_pc, src_reg, dst_reg)  /* addP  %src_reg, %dst_reg */ gen86_addP_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_orb_r_r(p_pc, src_reg, dst_reg)   /* orb   %src_reg, %dst_reg */ gen86_orb_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_orw_r_r(p_pc, src_reg, dst_reg)   /* orw   %src_reg, %dst_reg */ gen86_orw_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_orl_r_r(p_pc, src_reg, dst_reg)   /* orl   %src_reg, %dst_reg */ gen86_orl_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_orP_r_r(p_pc, src_reg, dst_reg)   /* orP   %src_reg, %dst_reg */ gen86_orP_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_adcb_r_r(p_pc, src_reg, dst_reg)  /* adcb  %src_reg, %dst_reg */ gen86_adcb_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_adcw_r_r(p_pc, src_reg, dst_reg)  /* adcw  %src_reg, %dst_reg */ gen86_adcw_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_adcl_r_r(p_pc, src_reg, dst_reg)  /* adcl  %src_reg, %dst_reg */ gen86_adcl_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_adcP_r_r(p_pc, src_reg, dst_reg)  /* adcP  %src_reg, %dst_reg */ gen86_adcP_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_sbbb_r_r(p_pc, src_reg, dst_reg)  /* sbbb  %src_reg, %dst_reg */ gen86_sbbb_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_sbbw_r_r(p_pc, src_reg, dst_reg)  /* sbbw  %src_reg, %dst_reg */ gen86_sbbw_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_sbbl_r_r(p_pc, src_reg, dst_reg)  /* sbbl  %src_reg, %dst_reg */ gen86_sbbl_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_sbbP_r_r(p_pc, src_reg, dst_reg)  /* sbbP  %src_reg, %dst_reg */ gen86_sbbP_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_andb_r_r(p_pc, src_reg, dst_reg)  /* andb  %src_reg, %dst_reg */ gen86_andb_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_andw_r_r(p_pc, src_reg, dst_reg)  /* andw  %src_reg, %dst_reg */ gen86_andw_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_andl_r_r(p_pc, src_reg, dst_reg)  /* andl  %src_reg, %dst_reg */ gen86_andl_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_andP_r_r(p_pc, src_reg, dst_reg)  /* andP  %src_reg, %dst_reg */ gen86_andP_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_subb_r_r(p_pc, src_reg, dst_reg)  /* subb  %src_reg, %dst_reg */ gen86_subb_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_subw_r_r(p_pc, src_reg, dst_reg)  /* subw  %src_reg, %dst_reg */ gen86_subw_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_subl_r_r(p_pc, src_reg, dst_reg)  /* subl  %src_reg, %dst_reg */ gen86_subl_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_subP_r_r(p_pc, src_reg, dst_reg)  /* subP  %src_reg, %dst_reg */ gen86_subP_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_xorb_r_r(p_pc, src_reg, dst_reg)  /* xorb  %src_reg, %dst_reg */ gen86_xorb_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_xorw_r_r(p_pc, src_reg, dst_reg)  /* xorw  %src_reg, %dst_reg */ gen86_xorw_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_xorl_r_r(p_pc, src_reg, dst_reg)  /* xorl  %src_reg, %dst_reg */ gen86_xorl_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_xorP_r_r(p_pc, src_reg, dst_reg)  /* xorP  %src_reg, %dst_reg */ gen86_xorP_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#if LIBGEN86_TARGET_BITS == 64
#define gen86_addq_r_r(p_pc, src_reg, dst_reg)  /* addq  %src_reg, %dst_reg */ gen86_addq_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_orq_r_r(p_pc, src_reg, dst_reg)   /* orq   %src_reg, %dst_reg */ gen86_orq_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_adcq_r_r(p_pc, src_reg, dst_reg)  /* adcq  %src_reg, %dst_reg */ gen86_adcq_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_sbbq_r_r(p_pc, src_reg, dst_reg)  /* sbbq  %src_reg, %dst_reg */ gen86_sbbq_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_andq_r_r(p_pc, src_reg, dst_reg)  /* andq  %src_reg, %dst_reg */ gen86_andq_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_subq_r_r(p_pc, src_reg, dst_reg)  /* subq  %src_reg, %dst_reg */ gen86_subq_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#define gen86_xorq_r_r(p_pc, src_reg, dst_reg)  /* xorq  %src_reg, %dst_reg */ gen86_xorq_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#endif /* LIBGEN86_TARGET_BITS == 64 */
/*[[[end]]]*/

#define gen86_movb_r_r(p_pc, src_reg, dst_reg) /* movb %src_reg, %dst_reg */ ((src_reg) == (dst_reg) ? (void)0 : gen86_movb_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg))
#define gen86_movw_r_r(p_pc, src_reg, dst_reg) /* movw %src_reg, %dst_reg */ ((src_reg) == (dst_reg) ? (void)0 : gen86_movw_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg))
#define gen86_movP_r_r(p_pc, src_reg, dst_reg) /* movP %src_reg, %dst_reg */ ((src_reg) == (dst_reg) ? (void)0 : gen86_movP_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg))
#if LIBGEN86_TARGET_BITS == 64
#define gen86_movl_r_r(p_pc, src_reg, dst_reg) /* movl %src_reg, %dst_reg */ gen86_movl_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg) /* mov to same register here actually zeroes out the upper 32 bits! */
#define gen86_movq_r_r(p_pc, src_reg, dst_reg) /* movq %src_reg, %dst_reg */ gen86_movq_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg)
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_movl_r_r(p_pc, src_reg, dst_reg) /* movl %src_reg, %dst_reg */ ((src_reg) == (dst_reg) ? (void)0 : gen86_movl_r_mod(p_pc, gen86_modrm_r, src_reg, dst_reg))
#endif /* LIBGEN86_TARGET_BITS != 64 */

#define gen86_testb_r_r(p_pc, r1, r2)  /* testb %r1, %r2   */ gen86_testb_r_mod(p_pc, gen86_modrm_r, r1, r2)
#define gen86_testw_r_r(p_pc, r1, r2)  /* testw %r1, %r2   */ gen86_testw_r_mod(p_pc, gen86_modrm_r, r1, r2)
#define gen86_testl_r_r(p_pc, r1, r2)  /* testl %r1, %r2   */ gen86_testl_r_mod(p_pc, gen86_modrm_r, r1, r2)
#define gen86_testP_r_r(p_pc, r1, r2)  /* testP %r1, %r2   */ gen86_testP_r_mod(p_pc, gen86_modrm_r, r1, r2)
#define gen86_cmpb_r_r(p_pc, rhs, lhs) /* cmpb  %rhs, %lhs */ gen86_cmpb_r_mod(p_pc, gen86_modrm_r, rhs, lhs)
#define gen86_cmpw_r_r(p_pc, rhs, lhs) /* cmpw  %rhs, %lhs */ gen86_cmpw_r_mod(p_pc, gen86_modrm_r, rhs, lhs)
#define gen86_cmpl_r_r(p_pc, rhs, lhs) /* cmpl  %rhs, %lhs */ gen86_cmpl_r_mod(p_pc, gen86_modrm_r, rhs, lhs)
#define gen86_cmpP_r_r(p_pc, rhs, lhs) /* cmpP  %rhs, %lhs */ gen86_cmpP_r_mod(p_pc, gen86_modrm_r, rhs, lhs)
#if LIBGEN86_TARGET_BITS == 64
#define gen86_testq_r_r(p_pc, r1, r2)  /* testq %r1, %r2   */ gen86_testq_r_mod(p_pc, gen86_modrm_r, r1, r2)
#define gen86_cmpq_r_r(p_pc, rhs, lhs) /* cmpq  %rhs, %lhs */ gen86_cmpq_r_mod(p_pc, gen86_modrm_r, rhs, lhs)
#endif /* LIBGEN86_TARGET_BITS == 64 */

#define gen86_mov_cr_r(p_pc, crN, reg) /* mov %crN, %reg */ gen86_mov_cr_mod(p_pc, gen86_modrm_r, crN, reg)
#define gen86_mov_dr_r(p_pc, reg, drN) /* mov %reg, %drN */ gen86_mov_dr_mod(p_pc, gen86_modrm_r, drN, reg)
#define gen86_mov_r_cr(p_pc, crN, reg) /* mov %crN, %reg */ gen86_mov_mod_cr(p_pc, gen86_modrm_r, crN, reg)
#define gen86_mov_r_dr(p_pc, reg, drN) /* mov %reg, %drN */ gen86_mov_mod_dr(p_pc, gen86_modrm_r, drN, reg)
#if LIBGEN86_TARGET_BITS == 64
#define gen86_movq_cr_r gen86_mov_cr_r
#define gen86_movq_dr_r gen86_mov_dr_r
#define gen86_movq_r_cr gen86_mov_r_cr
#define gen86_movq_r_dr gen86_mov_r_dr
#else /* LIBGEN86_TARGET_BITS == 64 */
#define gen86_movl_cr_r gen86_mov_cr_r
#define gen86_movl_dr_r gen86_mov_dr_r
#define gen86_movl_r_cr gen86_mov_r_cr
#define gen86_movl_r_dr gen86_mov_r_dr
#endif /* LIBGEN86_TARGET_BITS != 64 */


#define _gen86_xchgX_select(p_pc, r1, r2, gen86_xchgX_r_mod, gen86_xchgX_r_Xax) \
	((r1) == (r2)                                                               \
	 ? (void)0                                                                  \
	 : (r1) == GEN86_R_AX                                                       \
	   ? gen86_xchgX_r_Xax(p_pc, r2)                                            \
	   : (r2) == GEN86_R_AX                                                     \
	     ? gen86_xchgX_r_Xax(p_pc, r1)                                          \
	     : gen86_xchgX_r_mod(p_pc, gen86_modrm_r, r1, r2))
#define gen86_xchgb_r_r(p_pc, r1, r2) /* xchgb  %r1, %r2 */ gen86_xchgb_r_mod(p_pc, gen86_modrm_r, r1, r2)
#define gen86_xchgw_r_r(p_pc, r1, r2) /* xchgw  %r1, %r2 */ _gen86_xchgX_select(p_pc, r1, r2, gen86_xchgw_r_mod, gen86_xchgw_r_ax)
#define gen86_xchgl_r_r(p_pc, r1, r2) /* xchgl  %r1, %r2 */ _gen86_xchgX_select(p_pc, r1, r2, gen86_xchgl_r_mod, gen86_xchgl_r_eax)
#define gen86_xchgP_r_r(p_pc, r1, r2) /* xchgP  %r1, %r2 */ _gen86_xchgX_select(p_pc, r1, r2, gen86_xchgP_r_mod, gen86_xchgP_r_Pax)
#if LIBGEN86_TARGET_BITS == 64
#define gen86_xchgq_r_r(p_pc, r1, r2) /* xchgq  %r1, %r2 */ _gen86_xchgX_select(p_pc, r1, r2, gen86_xchgq_r_mod, gen86_xchgq_r_rax)
#endif /* LIBGEN86_TARGET_BITS == 64 */

/*[[[deemon
local tests = {
	"o"   : "GEN86_CC_O",
	"no"  : "GEN86_CC_NO",
	"b"   : "GEN86_CC_B",
	"c"   : "GEN86_CC_C",
	"nae" : "GEN86_CC_NAE",
	"ae"  : "GEN86_CC_AE",
	"nb"  : "GEN86_CC_NB",
	"nc"  : "GEN86_CC_NC",
	"z"   : "GEN86_CC_Z",
	"e"   : "GEN86_CC_E",
	"nz"  : "GEN86_CC_NZ",
	"ne"  : "GEN86_CC_NE",
	"be"  : "GEN86_CC_BE",
	"na"  : "GEN86_CC_NA",
	"a"   : "GEN86_CC_A",
	"nbe" : "GEN86_CC_NBE",
	"s"   : "GEN86_CC_S",
	"ns"  : "GEN86_CC_NS",
	"p"   : "GEN86_CC_P",
	"pe"  : "GEN86_CC_PE",
	"np"  : "GEN86_CC_NP",
	"po"  : "GEN86_CC_PO",
	"l"   : "GEN86_CC_L",
	"nge" : "GEN86_CC_NGE",
	"ge"  : "GEN86_CC_GE",
	"nl"  : "GEN86_CC_NL",
	"le"  : "GEN86_CC_LE",
	"ng"  : "GEN86_CC_NG",
	"g"   : "GEN86_CC_G",
	"nle" : "GEN86_CC_NLE",
};
local macros = [];
function printInstruction(name, params) {
	local param_names = ", ".join(params);
	local arg_names   = ", ".join(for (local p: params) { "..." : "__VA_ARGS__" }.get(p, p));
	for (local tname, cc: tests) {
		local a = "gen86_{}(p_pc, {})".format({ name.format({ tname }), param_names });
		local b = "gen86_{}(p_pc, {}, {})".format({ name.format({ "cc" }), cc, arg_names });
		macros.append((a, b));
	}
}
printInstruction("j{}8", ["addr"]);
printInstruction("j{}8_offset", ["offset"]);
printInstruction("j{}P", ["addr"]);
printInstruction("j{}P_offset", ["offset"]);
printInstruction("j{}", ["addr"]);
printInstruction("j{}_offset", ["offset"]);
printInstruction("set{}_r", ["reg"]);
printInstruction("set{}_mod", ["gen_modrm", "..."]);
printInstruction("cmov{}w_r_r", ["src_reg", "dst_reg"]);
printInstruction("cmov{}l_r_r", ["src_reg", "dst_reg"]);
printInstruction("cmov{}P_r_r", ["src_reg", "dst_reg"]);
printInstruction("cmov{}w_mod_r", ["gen_modrm", "reg", "..."]);
printInstruction("cmov{}l_mod_r", ["gen_modrm", "reg", "..."]);
printInstruction("cmov{}P_mod_r", ["gen_modrm", "reg", "..."]);
local longestName = (macros.each.first.length > ...) + 1;
for (local a, b: macros)
	print("#define ", a.ljust(longestName), b);
macros.clear();
printInstruction("cmov{}q_r_r", ["src_reg", "dst_reg"]);
printInstruction("cmov{}q_mod_r", ["gen_modrm", "reg", "..."]);
print("#if LIBGEN86_TARGET_BITS == 64");
local longestName = (macros.each.first.length > ...) + 1;
for (local a, b: macros)
	print("#define ", a.ljust(longestName), b);
print("#endif /" "* LIBGEN86_TARGET_BITS == 64 *" "/");
]]]*/
#define gen86_jae8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_AE, addr)
#define gen86_jbe8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_BE, addr)
#define gen86_jb8(p_pc, addr)                           gen86_jcc8(p_pc, GEN86_CC_B, addr)
#define gen86_jna8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_NA, addr)
#define gen86_jnae8(p_pc, addr)                         gen86_jcc8(p_pc, GEN86_CC_NAE, addr)
#define gen86_jpe8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_PE, addr)
#define gen86_jne8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_NE, addr)
#define gen86_jng8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_NG, addr)
#define gen86_jg8(p_pc, addr)                           gen86_jcc8(p_pc, GEN86_CC_G, addr)
#define gen86_jz8(p_pc, addr)                           gen86_jcc8(p_pc, GEN86_CC_Z, addr)
#define gen86_jns8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_NS, addr)
#define gen86_jp8(p_pc, addr)                           gen86_jcc8(p_pc, GEN86_CC_P, addr)
#define gen86_jnb8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_NB, addr)
#define gen86_jc8(p_pc, addr)                           gen86_jcc8(p_pc, GEN86_CC_C, addr)
#define gen86_jnge8(p_pc, addr)                         gen86_jcc8(p_pc, GEN86_CC_NGE, addr)
#define gen86_jnbe8(p_pc, addr)                         gen86_jcc8(p_pc, GEN86_CC_NBE, addr)
#define gen86_jnle8(p_pc, addr)                         gen86_jcc8(p_pc, GEN86_CC_NLE, addr)
#define gen86_jpo8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_PO, addr)
#define gen86_je8(p_pc, addr)                           gen86_jcc8(p_pc, GEN86_CC_E, addr)
#define gen86_jnl8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_NL, addr)
#define gen86_jnz8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_NZ, addr)
#define gen86_jl8(p_pc, addr)                           gen86_jcc8(p_pc, GEN86_CC_L, addr)
#define gen86_jnc8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_NC, addr)
#define gen86_jno8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_NO, addr)
#define gen86_js8(p_pc, addr)                           gen86_jcc8(p_pc, GEN86_CC_S, addr)
#define gen86_ja8(p_pc, addr)                           gen86_jcc8(p_pc, GEN86_CC_A, addr)
#define gen86_jo8(p_pc, addr)                           gen86_jcc8(p_pc, GEN86_CC_O, addr)
#define gen86_jle8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_LE, addr)
#define gen86_jnp8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_NP, addr)
#define gen86_jge8(p_pc, addr)                          gen86_jcc8(p_pc, GEN86_CC_GE, addr)
#define gen86_jae8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_AE, offset)
#define gen86_jbe8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_BE, offset)
#define gen86_jb8_offset(p_pc, offset)                  gen86_jcc8_offset(p_pc, GEN86_CC_B, offset)
#define gen86_jna8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_NA, offset)
#define gen86_jnae8_offset(p_pc, offset)                gen86_jcc8_offset(p_pc, GEN86_CC_NAE, offset)
#define gen86_jpe8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_PE, offset)
#define gen86_jne8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_NE, offset)
#define gen86_jng8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_NG, offset)
#define gen86_jg8_offset(p_pc, offset)                  gen86_jcc8_offset(p_pc, GEN86_CC_G, offset)
#define gen86_jz8_offset(p_pc, offset)                  gen86_jcc8_offset(p_pc, GEN86_CC_Z, offset)
#define gen86_jns8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_NS, offset)
#define gen86_jp8_offset(p_pc, offset)                  gen86_jcc8_offset(p_pc, GEN86_CC_P, offset)
#define gen86_jnb8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_NB, offset)
#define gen86_jc8_offset(p_pc, offset)                  gen86_jcc8_offset(p_pc, GEN86_CC_C, offset)
#define gen86_jnge8_offset(p_pc, offset)                gen86_jcc8_offset(p_pc, GEN86_CC_NGE, offset)
#define gen86_jnbe8_offset(p_pc, offset)                gen86_jcc8_offset(p_pc, GEN86_CC_NBE, offset)
#define gen86_jnle8_offset(p_pc, offset)                gen86_jcc8_offset(p_pc, GEN86_CC_NLE, offset)
#define gen86_jpo8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_PO, offset)
#define gen86_je8_offset(p_pc, offset)                  gen86_jcc8_offset(p_pc, GEN86_CC_E, offset)
#define gen86_jnl8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_NL, offset)
#define gen86_jnz8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_NZ, offset)
#define gen86_jl8_offset(p_pc, offset)                  gen86_jcc8_offset(p_pc, GEN86_CC_L, offset)
#define gen86_jnc8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_NC, offset)
#define gen86_jno8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_NO, offset)
#define gen86_js8_offset(p_pc, offset)                  gen86_jcc8_offset(p_pc, GEN86_CC_S, offset)
#define gen86_ja8_offset(p_pc, offset)                  gen86_jcc8_offset(p_pc, GEN86_CC_A, offset)
#define gen86_jo8_offset(p_pc, offset)                  gen86_jcc8_offset(p_pc, GEN86_CC_O, offset)
#define gen86_jle8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_LE, offset)
#define gen86_jnp8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_NP, offset)
#define gen86_jge8_offset(p_pc, offset)                 gen86_jcc8_offset(p_pc, GEN86_CC_GE, offset)
#define gen86_jaeP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_AE, addr)
#define gen86_jbeP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_BE, addr)
#define gen86_jbP(p_pc, addr)                           gen86_jccP(p_pc, GEN86_CC_B, addr)
#define gen86_jnaP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_NA, addr)
#define gen86_jnaeP(p_pc, addr)                         gen86_jccP(p_pc, GEN86_CC_NAE, addr)
#define gen86_jpeP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_PE, addr)
#define gen86_jneP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_NE, addr)
#define gen86_jngP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_NG, addr)
#define gen86_jgP(p_pc, addr)                           gen86_jccP(p_pc, GEN86_CC_G, addr)
#define gen86_jzP(p_pc, addr)                           gen86_jccP(p_pc, GEN86_CC_Z, addr)
#define gen86_jnsP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_NS, addr)
#define gen86_jpP(p_pc, addr)                           gen86_jccP(p_pc, GEN86_CC_P, addr)
#define gen86_jnbP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_NB, addr)
#define gen86_jcP(p_pc, addr)                           gen86_jccP(p_pc, GEN86_CC_C, addr)
#define gen86_jngeP(p_pc, addr)                         gen86_jccP(p_pc, GEN86_CC_NGE, addr)
#define gen86_jnbeP(p_pc, addr)                         gen86_jccP(p_pc, GEN86_CC_NBE, addr)
#define gen86_jnleP(p_pc, addr)                         gen86_jccP(p_pc, GEN86_CC_NLE, addr)
#define gen86_jpoP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_PO, addr)
#define gen86_jeP(p_pc, addr)                           gen86_jccP(p_pc, GEN86_CC_E, addr)
#define gen86_jnlP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_NL, addr)
#define gen86_jnzP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_NZ, addr)
#define gen86_jlP(p_pc, addr)                           gen86_jccP(p_pc, GEN86_CC_L, addr)
#define gen86_jncP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_NC, addr)
#define gen86_jnoP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_NO, addr)
#define gen86_jsP(p_pc, addr)                           gen86_jccP(p_pc, GEN86_CC_S, addr)
#define gen86_jaP(p_pc, addr)                           gen86_jccP(p_pc, GEN86_CC_A, addr)
#define gen86_joP(p_pc, addr)                           gen86_jccP(p_pc, GEN86_CC_O, addr)
#define gen86_jleP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_LE, addr)
#define gen86_jnpP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_NP, addr)
#define gen86_jgeP(p_pc, addr)                          gen86_jccP(p_pc, GEN86_CC_GE, addr)
#define gen86_jaeP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_AE, offset)
#define gen86_jbeP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_BE, offset)
#define gen86_jbP_offset(p_pc, offset)                  gen86_jccP_offset(p_pc, GEN86_CC_B, offset)
#define gen86_jnaP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_NA, offset)
#define gen86_jnaeP_offset(p_pc, offset)                gen86_jccP_offset(p_pc, GEN86_CC_NAE, offset)
#define gen86_jpeP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_PE, offset)
#define gen86_jneP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_NE, offset)
#define gen86_jngP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_NG, offset)
#define gen86_jgP_offset(p_pc, offset)                  gen86_jccP_offset(p_pc, GEN86_CC_G, offset)
#define gen86_jzP_offset(p_pc, offset)                  gen86_jccP_offset(p_pc, GEN86_CC_Z, offset)
#define gen86_jnsP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_NS, offset)
#define gen86_jpP_offset(p_pc, offset)                  gen86_jccP_offset(p_pc, GEN86_CC_P, offset)
#define gen86_jnbP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_NB, offset)
#define gen86_jcP_offset(p_pc, offset)                  gen86_jccP_offset(p_pc, GEN86_CC_C, offset)
#define gen86_jngeP_offset(p_pc, offset)                gen86_jccP_offset(p_pc, GEN86_CC_NGE, offset)
#define gen86_jnbeP_offset(p_pc, offset)                gen86_jccP_offset(p_pc, GEN86_CC_NBE, offset)
#define gen86_jnleP_offset(p_pc, offset)                gen86_jccP_offset(p_pc, GEN86_CC_NLE, offset)
#define gen86_jpoP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_PO, offset)
#define gen86_jeP_offset(p_pc, offset)                  gen86_jccP_offset(p_pc, GEN86_CC_E, offset)
#define gen86_jnlP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_NL, offset)
#define gen86_jnzP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_NZ, offset)
#define gen86_jlP_offset(p_pc, offset)                  gen86_jccP_offset(p_pc, GEN86_CC_L, offset)
#define gen86_jncP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_NC, offset)
#define gen86_jnoP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_NO, offset)
#define gen86_jsP_offset(p_pc, offset)                  gen86_jccP_offset(p_pc, GEN86_CC_S, offset)
#define gen86_jaP_offset(p_pc, offset)                  gen86_jccP_offset(p_pc, GEN86_CC_A, offset)
#define gen86_joP_offset(p_pc, offset)                  gen86_jccP_offset(p_pc, GEN86_CC_O, offset)
#define gen86_jleP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_LE, offset)
#define gen86_jnpP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_NP, offset)
#define gen86_jgeP_offset(p_pc, offset)                 gen86_jccP_offset(p_pc, GEN86_CC_GE, offset)
#define gen86_jae(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_AE, addr)
#define gen86_jbe(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_BE, addr)
#define gen86_jb(p_pc, addr)                            gen86_jcc(p_pc, GEN86_CC_B, addr)
#define gen86_jna(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_NA, addr)
#define gen86_jnae(p_pc, addr)                          gen86_jcc(p_pc, GEN86_CC_NAE, addr)
#define gen86_jpe(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_PE, addr)
#define gen86_jne(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_NE, addr)
#define gen86_jng(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_NG, addr)
#define gen86_jg(p_pc, addr)                            gen86_jcc(p_pc, GEN86_CC_G, addr)
#define gen86_jz(p_pc, addr)                            gen86_jcc(p_pc, GEN86_CC_Z, addr)
#define gen86_jns(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_NS, addr)
#define gen86_jp(p_pc, addr)                            gen86_jcc(p_pc, GEN86_CC_P, addr)
#define gen86_jnb(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_NB, addr)
#define gen86_jc(p_pc, addr)                            gen86_jcc(p_pc, GEN86_CC_C, addr)
#define gen86_jnge(p_pc, addr)                          gen86_jcc(p_pc, GEN86_CC_NGE, addr)
#define gen86_jnbe(p_pc, addr)                          gen86_jcc(p_pc, GEN86_CC_NBE, addr)
#define gen86_jnle(p_pc, addr)                          gen86_jcc(p_pc, GEN86_CC_NLE, addr)
#define gen86_jpo(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_PO, addr)
#define gen86_je(p_pc, addr)                            gen86_jcc(p_pc, GEN86_CC_E, addr)
#define gen86_jnl(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_NL, addr)
#define gen86_jnz(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_NZ, addr)
#define gen86_jl(p_pc, addr)                            gen86_jcc(p_pc, GEN86_CC_L, addr)
#define gen86_jnc(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_NC, addr)
#define gen86_jno(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_NO, addr)
#define gen86_js(p_pc, addr)                            gen86_jcc(p_pc, GEN86_CC_S, addr)
#define gen86_ja(p_pc, addr)                            gen86_jcc(p_pc, GEN86_CC_A, addr)
#define gen86_jo(p_pc, addr)                            gen86_jcc(p_pc, GEN86_CC_O, addr)
#define gen86_jle(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_LE, addr)
#define gen86_jnp(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_NP, addr)
#define gen86_jge(p_pc, addr)                           gen86_jcc(p_pc, GEN86_CC_GE, addr)
#define gen86_jae_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_AE, offset)
#define gen86_jbe_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_BE, offset)
#define gen86_jb_offset(p_pc, offset)                   gen86_jcc_offset(p_pc, GEN86_CC_B, offset)
#define gen86_jna_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_NA, offset)
#define gen86_jnae_offset(p_pc, offset)                 gen86_jcc_offset(p_pc, GEN86_CC_NAE, offset)
#define gen86_jpe_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_PE, offset)
#define gen86_jne_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_NE, offset)
#define gen86_jng_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_NG, offset)
#define gen86_jg_offset(p_pc, offset)                   gen86_jcc_offset(p_pc, GEN86_CC_G, offset)
#define gen86_jz_offset(p_pc, offset)                   gen86_jcc_offset(p_pc, GEN86_CC_Z, offset)
#define gen86_jns_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_NS, offset)
#define gen86_jp_offset(p_pc, offset)                   gen86_jcc_offset(p_pc, GEN86_CC_P, offset)
#define gen86_jnb_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_NB, offset)
#define gen86_jc_offset(p_pc, offset)                   gen86_jcc_offset(p_pc, GEN86_CC_C, offset)
#define gen86_jnge_offset(p_pc, offset)                 gen86_jcc_offset(p_pc, GEN86_CC_NGE, offset)
#define gen86_jnbe_offset(p_pc, offset)                 gen86_jcc_offset(p_pc, GEN86_CC_NBE, offset)
#define gen86_jnle_offset(p_pc, offset)                 gen86_jcc_offset(p_pc, GEN86_CC_NLE, offset)
#define gen86_jpo_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_PO, offset)
#define gen86_je_offset(p_pc, offset)                   gen86_jcc_offset(p_pc, GEN86_CC_E, offset)
#define gen86_jnl_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_NL, offset)
#define gen86_jnz_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_NZ, offset)
#define gen86_jl_offset(p_pc, offset)                   gen86_jcc_offset(p_pc, GEN86_CC_L, offset)
#define gen86_jnc_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_NC, offset)
#define gen86_jno_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_NO, offset)
#define gen86_js_offset(p_pc, offset)                   gen86_jcc_offset(p_pc, GEN86_CC_S, offset)
#define gen86_ja_offset(p_pc, offset)                   gen86_jcc_offset(p_pc, GEN86_CC_A, offset)
#define gen86_jo_offset(p_pc, offset)                   gen86_jcc_offset(p_pc, GEN86_CC_O, offset)
#define gen86_jle_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_LE, offset)
#define gen86_jnp_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_NP, offset)
#define gen86_jge_offset(p_pc, offset)                  gen86_jcc_offset(p_pc, GEN86_CC_GE, offset)
#define gen86_setae_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_AE, reg)
#define gen86_setbe_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_BE, reg)
#define gen86_setb_r(p_pc, reg)                         gen86_setcc_r(p_pc, GEN86_CC_B, reg)
#define gen86_setna_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_NA, reg)
#define gen86_setnae_r(p_pc, reg)                       gen86_setcc_r(p_pc, GEN86_CC_NAE, reg)
#define gen86_setpe_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_PE, reg)
#define gen86_setne_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_NE, reg)
#define gen86_setng_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_NG, reg)
#define gen86_setg_r(p_pc, reg)                         gen86_setcc_r(p_pc, GEN86_CC_G, reg)
#define gen86_setz_r(p_pc, reg)                         gen86_setcc_r(p_pc, GEN86_CC_Z, reg)
#define gen86_setns_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_NS, reg)
#define gen86_setp_r(p_pc, reg)                         gen86_setcc_r(p_pc, GEN86_CC_P, reg)
#define gen86_setnb_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_NB, reg)
#define gen86_setc_r(p_pc, reg)                         gen86_setcc_r(p_pc, GEN86_CC_C, reg)
#define gen86_setnge_r(p_pc, reg)                       gen86_setcc_r(p_pc, GEN86_CC_NGE, reg)
#define gen86_setnbe_r(p_pc, reg)                       gen86_setcc_r(p_pc, GEN86_CC_NBE, reg)
#define gen86_setnle_r(p_pc, reg)                       gen86_setcc_r(p_pc, GEN86_CC_NLE, reg)
#define gen86_setpo_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_PO, reg)
#define gen86_sete_r(p_pc, reg)                         gen86_setcc_r(p_pc, GEN86_CC_E, reg)
#define gen86_setnl_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_NL, reg)
#define gen86_setnz_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_NZ, reg)
#define gen86_setl_r(p_pc, reg)                         gen86_setcc_r(p_pc, GEN86_CC_L, reg)
#define gen86_setnc_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_NC, reg)
#define gen86_setno_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_NO, reg)
#define gen86_sets_r(p_pc, reg)                         gen86_setcc_r(p_pc, GEN86_CC_S, reg)
#define gen86_seta_r(p_pc, reg)                         gen86_setcc_r(p_pc, GEN86_CC_A, reg)
#define gen86_seto_r(p_pc, reg)                         gen86_setcc_r(p_pc, GEN86_CC_O, reg)
#define gen86_setle_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_LE, reg)
#define gen86_setnp_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_NP, reg)
#define gen86_setge_r(p_pc, reg)                        gen86_setcc_r(p_pc, GEN86_CC_GE, reg)
#define gen86_setae_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_AE, gen_modrm, __VA_ARGS__)
#define gen86_setbe_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_BE, gen_modrm, __VA_ARGS__)
#define gen86_setb_mod(p_pc, gen_modrm, ...)            gen86_setcc_mod(p_pc, GEN86_CC_B, gen_modrm, __VA_ARGS__)
#define gen86_setna_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_NA, gen_modrm, __VA_ARGS__)
#define gen86_setnae_mod(p_pc, gen_modrm, ...)          gen86_setcc_mod(p_pc, GEN86_CC_NAE, gen_modrm, __VA_ARGS__)
#define gen86_setpe_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_PE, gen_modrm, __VA_ARGS__)
#define gen86_setne_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_NE, gen_modrm, __VA_ARGS__)
#define gen86_setng_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_NG, gen_modrm, __VA_ARGS__)
#define gen86_setg_mod(p_pc, gen_modrm, ...)            gen86_setcc_mod(p_pc, GEN86_CC_G, gen_modrm, __VA_ARGS__)
#define gen86_setz_mod(p_pc, gen_modrm, ...)            gen86_setcc_mod(p_pc, GEN86_CC_Z, gen_modrm, __VA_ARGS__)
#define gen86_setns_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_NS, gen_modrm, __VA_ARGS__)
#define gen86_setp_mod(p_pc, gen_modrm, ...)            gen86_setcc_mod(p_pc, GEN86_CC_P, gen_modrm, __VA_ARGS__)
#define gen86_setnb_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_NB, gen_modrm, __VA_ARGS__)
#define gen86_setc_mod(p_pc, gen_modrm, ...)            gen86_setcc_mod(p_pc, GEN86_CC_C, gen_modrm, __VA_ARGS__)
#define gen86_setnge_mod(p_pc, gen_modrm, ...)          gen86_setcc_mod(p_pc, GEN86_CC_NGE, gen_modrm, __VA_ARGS__)
#define gen86_setnbe_mod(p_pc, gen_modrm, ...)          gen86_setcc_mod(p_pc, GEN86_CC_NBE, gen_modrm, __VA_ARGS__)
#define gen86_setnle_mod(p_pc, gen_modrm, ...)          gen86_setcc_mod(p_pc, GEN86_CC_NLE, gen_modrm, __VA_ARGS__)
#define gen86_setpo_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_PO, gen_modrm, __VA_ARGS__)
#define gen86_sete_mod(p_pc, gen_modrm, ...)            gen86_setcc_mod(p_pc, GEN86_CC_E, gen_modrm, __VA_ARGS__)
#define gen86_setnl_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_NL, gen_modrm, __VA_ARGS__)
#define gen86_setnz_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_NZ, gen_modrm, __VA_ARGS__)
#define gen86_setl_mod(p_pc, gen_modrm, ...)            gen86_setcc_mod(p_pc, GEN86_CC_L, gen_modrm, __VA_ARGS__)
#define gen86_setnc_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_NC, gen_modrm, __VA_ARGS__)
#define gen86_setno_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_NO, gen_modrm, __VA_ARGS__)
#define gen86_sets_mod(p_pc, gen_modrm, ...)            gen86_setcc_mod(p_pc, GEN86_CC_S, gen_modrm, __VA_ARGS__)
#define gen86_seta_mod(p_pc, gen_modrm, ...)            gen86_setcc_mod(p_pc, GEN86_CC_A, gen_modrm, __VA_ARGS__)
#define gen86_seto_mod(p_pc, gen_modrm, ...)            gen86_setcc_mod(p_pc, GEN86_CC_O, gen_modrm, __VA_ARGS__)
#define gen86_setle_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_LE, gen_modrm, __VA_ARGS__)
#define gen86_setnp_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_NP, gen_modrm, __VA_ARGS__)
#define gen86_setge_mod(p_pc, gen_modrm, ...)           gen86_setcc_mod(p_pc, GEN86_CC_GE, gen_modrm, __VA_ARGS__)
#define gen86_cmovaew_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_AE, src_reg, dst_reg)
#define gen86_cmovbew_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_BE, src_reg, dst_reg)
#define gen86_cmovbw_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccw_r_r(p_pc, GEN86_CC_B, src_reg, dst_reg)
#define gen86_cmovnaw_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_NA, src_reg, dst_reg)
#define gen86_cmovnaew_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccw_r_r(p_pc, GEN86_CC_NAE, src_reg, dst_reg)
#define gen86_cmovpew_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_PE, src_reg, dst_reg)
#define gen86_cmovnew_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_NE, src_reg, dst_reg)
#define gen86_cmovngw_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_NG, src_reg, dst_reg)
#define gen86_cmovgw_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccw_r_r(p_pc, GEN86_CC_G, src_reg, dst_reg)
#define gen86_cmovzw_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccw_r_r(p_pc, GEN86_CC_Z, src_reg, dst_reg)
#define gen86_cmovnsw_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_NS, src_reg, dst_reg)
#define gen86_cmovpw_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccw_r_r(p_pc, GEN86_CC_P, src_reg, dst_reg)
#define gen86_cmovnbw_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_NB, src_reg, dst_reg)
#define gen86_cmovcw_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccw_r_r(p_pc, GEN86_CC_C, src_reg, dst_reg)
#define gen86_cmovngew_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccw_r_r(p_pc, GEN86_CC_NGE, src_reg, dst_reg)
#define gen86_cmovnbew_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccw_r_r(p_pc, GEN86_CC_NBE, src_reg, dst_reg)
#define gen86_cmovnlew_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccw_r_r(p_pc, GEN86_CC_NLE, src_reg, dst_reg)
#define gen86_cmovpow_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_PO, src_reg, dst_reg)
#define gen86_cmovew_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccw_r_r(p_pc, GEN86_CC_E, src_reg, dst_reg)
#define gen86_cmovnlw_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_NL, src_reg, dst_reg)
#define gen86_cmovnzw_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_NZ, src_reg, dst_reg)
#define gen86_cmovlw_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccw_r_r(p_pc, GEN86_CC_L, src_reg, dst_reg)
#define gen86_cmovncw_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_NC, src_reg, dst_reg)
#define gen86_cmovnow_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_NO, src_reg, dst_reg)
#define gen86_cmovsw_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccw_r_r(p_pc, GEN86_CC_S, src_reg, dst_reg)
#define gen86_cmovaw_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccw_r_r(p_pc, GEN86_CC_A, src_reg, dst_reg)
#define gen86_cmovow_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccw_r_r(p_pc, GEN86_CC_O, src_reg, dst_reg)
#define gen86_cmovlew_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_LE, src_reg, dst_reg)
#define gen86_cmovnpw_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_NP, src_reg, dst_reg)
#define gen86_cmovgew_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccw_r_r(p_pc, GEN86_CC_GE, src_reg, dst_reg)
#define gen86_cmovael_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_AE, src_reg, dst_reg)
#define gen86_cmovbel_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_BE, src_reg, dst_reg)
#define gen86_cmovbl_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccl_r_r(p_pc, GEN86_CC_B, src_reg, dst_reg)
#define gen86_cmovnal_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_NA, src_reg, dst_reg)
#define gen86_cmovnael_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccl_r_r(p_pc, GEN86_CC_NAE, src_reg, dst_reg)
#define gen86_cmovpel_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_PE, src_reg, dst_reg)
#define gen86_cmovnel_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_NE, src_reg, dst_reg)
#define gen86_cmovngl_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_NG, src_reg, dst_reg)
#define gen86_cmovgl_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccl_r_r(p_pc, GEN86_CC_G, src_reg, dst_reg)
#define gen86_cmovzl_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccl_r_r(p_pc, GEN86_CC_Z, src_reg, dst_reg)
#define gen86_cmovnsl_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_NS, src_reg, dst_reg)
#define gen86_cmovpl_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccl_r_r(p_pc, GEN86_CC_P, src_reg, dst_reg)
#define gen86_cmovnbl_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_NB, src_reg, dst_reg)
#define gen86_cmovcl_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccl_r_r(p_pc, GEN86_CC_C, src_reg, dst_reg)
#define gen86_cmovngel_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccl_r_r(p_pc, GEN86_CC_NGE, src_reg, dst_reg)
#define gen86_cmovnbel_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccl_r_r(p_pc, GEN86_CC_NBE, src_reg, dst_reg)
#define gen86_cmovnlel_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccl_r_r(p_pc, GEN86_CC_NLE, src_reg, dst_reg)
#define gen86_cmovpol_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_PO, src_reg, dst_reg)
#define gen86_cmovel_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccl_r_r(p_pc, GEN86_CC_E, src_reg, dst_reg)
#define gen86_cmovnll_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_NL, src_reg, dst_reg)
#define gen86_cmovnzl_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_NZ, src_reg, dst_reg)
#define gen86_cmovll_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccl_r_r(p_pc, GEN86_CC_L, src_reg, dst_reg)
#define gen86_cmovncl_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_NC, src_reg, dst_reg)
#define gen86_cmovnol_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_NO, src_reg, dst_reg)
#define gen86_cmovsl_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccl_r_r(p_pc, GEN86_CC_S, src_reg, dst_reg)
#define gen86_cmoval_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccl_r_r(p_pc, GEN86_CC_A, src_reg, dst_reg)
#define gen86_cmovol_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccl_r_r(p_pc, GEN86_CC_O, src_reg, dst_reg)
#define gen86_cmovlel_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_LE, src_reg, dst_reg)
#define gen86_cmovnpl_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_NP, src_reg, dst_reg)
#define gen86_cmovgel_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccl_r_r(p_pc, GEN86_CC_GE, src_reg, dst_reg)
#define gen86_cmovaeP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_AE, src_reg, dst_reg)
#define gen86_cmovbeP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_BE, src_reg, dst_reg)
#define gen86_cmovbP_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccP_r_r(p_pc, GEN86_CC_B, src_reg, dst_reg)
#define gen86_cmovnaP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_NA, src_reg, dst_reg)
#define gen86_cmovnaeP_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccP_r_r(p_pc, GEN86_CC_NAE, src_reg, dst_reg)
#define gen86_cmovpeP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_PE, src_reg, dst_reg)
#define gen86_cmovneP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_NE, src_reg, dst_reg)
#define gen86_cmovngP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_NG, src_reg, dst_reg)
#define gen86_cmovgP_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccP_r_r(p_pc, GEN86_CC_G, src_reg, dst_reg)
#define gen86_cmovzP_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccP_r_r(p_pc, GEN86_CC_Z, src_reg, dst_reg)
#define gen86_cmovnsP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_NS, src_reg, dst_reg)
#define gen86_cmovpP_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccP_r_r(p_pc, GEN86_CC_P, src_reg, dst_reg)
#define gen86_cmovnbP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_NB, src_reg, dst_reg)
#define gen86_cmovcP_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccP_r_r(p_pc, GEN86_CC_C, src_reg, dst_reg)
#define gen86_cmovngeP_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccP_r_r(p_pc, GEN86_CC_NGE, src_reg, dst_reg)
#define gen86_cmovnbeP_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccP_r_r(p_pc, GEN86_CC_NBE, src_reg, dst_reg)
#define gen86_cmovnleP_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccP_r_r(p_pc, GEN86_CC_NLE, src_reg, dst_reg)
#define gen86_cmovpoP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_PO, src_reg, dst_reg)
#define gen86_cmoveP_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccP_r_r(p_pc, GEN86_CC_E, src_reg, dst_reg)
#define gen86_cmovnlP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_NL, src_reg, dst_reg)
#define gen86_cmovnzP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_NZ, src_reg, dst_reg)
#define gen86_cmovlP_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccP_r_r(p_pc, GEN86_CC_L, src_reg, dst_reg)
#define gen86_cmovncP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_NC, src_reg, dst_reg)
#define gen86_cmovnoP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_NO, src_reg, dst_reg)
#define gen86_cmovsP_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccP_r_r(p_pc, GEN86_CC_S, src_reg, dst_reg)
#define gen86_cmovaP_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccP_r_r(p_pc, GEN86_CC_A, src_reg, dst_reg)
#define gen86_cmovoP_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccP_r_r(p_pc, GEN86_CC_O, src_reg, dst_reg)
#define gen86_cmovleP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_LE, src_reg, dst_reg)
#define gen86_cmovnpP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_NP, src_reg, dst_reg)
#define gen86_cmovgeP_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccP_r_r(p_pc, GEN86_CC_GE, src_reg, dst_reg)
#define gen86_cmovaew_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_AE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovbew_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_BE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovbw_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccw_mod_r(p_pc, GEN86_CC_B, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnaw_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_NA, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnaew_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccw_mod_r(p_pc, GEN86_CC_NAE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovpew_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_PE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnew_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_NE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovngw_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_NG, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovgw_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccw_mod_r(p_pc, GEN86_CC_G, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovzw_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccw_mod_r(p_pc, GEN86_CC_Z, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnsw_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_NS, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovpw_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccw_mod_r(p_pc, GEN86_CC_P, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnbw_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_NB, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovcw_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccw_mod_r(p_pc, GEN86_CC_C, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovngew_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccw_mod_r(p_pc, GEN86_CC_NGE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnbew_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccw_mod_r(p_pc, GEN86_CC_NBE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnlew_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccw_mod_r(p_pc, GEN86_CC_NLE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovpow_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_PO, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovew_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccw_mod_r(p_pc, GEN86_CC_E, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnlw_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_NL, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnzw_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_NZ, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovlw_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccw_mod_r(p_pc, GEN86_CC_L, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovncw_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_NC, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnow_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_NO, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovsw_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccw_mod_r(p_pc, GEN86_CC_S, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovaw_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccw_mod_r(p_pc, GEN86_CC_A, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovow_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccw_mod_r(p_pc, GEN86_CC_O, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovlew_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_LE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnpw_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_NP, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovgew_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccw_mod_r(p_pc, GEN86_CC_GE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovael_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_AE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovbel_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_BE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovbl_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccl_mod_r(p_pc, GEN86_CC_B, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnal_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_NA, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnael_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccl_mod_r(p_pc, GEN86_CC_NAE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovpel_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_PE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnel_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_NE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovngl_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_NG, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovgl_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccl_mod_r(p_pc, GEN86_CC_G, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovzl_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccl_mod_r(p_pc, GEN86_CC_Z, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnsl_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_NS, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovpl_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccl_mod_r(p_pc, GEN86_CC_P, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnbl_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_NB, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovcl_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccl_mod_r(p_pc, GEN86_CC_C, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovngel_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccl_mod_r(p_pc, GEN86_CC_NGE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnbel_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccl_mod_r(p_pc, GEN86_CC_NBE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnlel_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccl_mod_r(p_pc, GEN86_CC_NLE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovpol_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_PO, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovel_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccl_mod_r(p_pc, GEN86_CC_E, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnll_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_NL, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnzl_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_NZ, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovll_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccl_mod_r(p_pc, GEN86_CC_L, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovncl_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_NC, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnol_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_NO, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovsl_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccl_mod_r(p_pc, GEN86_CC_S, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmoval_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccl_mod_r(p_pc, GEN86_CC_A, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovol_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccl_mod_r(p_pc, GEN86_CC_O, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovlel_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_LE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnpl_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_NP, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovgel_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccl_mod_r(p_pc, GEN86_CC_GE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovaeP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_AE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovbeP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_BE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovbP_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccP_mod_r(p_pc, GEN86_CC_B, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnaP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_NA, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnaeP_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccP_mod_r(p_pc, GEN86_CC_NAE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovpeP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_PE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovneP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_NE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovngP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_NG, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovgP_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccP_mod_r(p_pc, GEN86_CC_G, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovzP_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccP_mod_r(p_pc, GEN86_CC_Z, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnsP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_NS, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovpP_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccP_mod_r(p_pc, GEN86_CC_P, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnbP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_NB, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovcP_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccP_mod_r(p_pc, GEN86_CC_C, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovngeP_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccP_mod_r(p_pc, GEN86_CC_NGE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnbeP_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccP_mod_r(p_pc, GEN86_CC_NBE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnleP_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccP_mod_r(p_pc, GEN86_CC_NLE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovpoP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_PO, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmoveP_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccP_mod_r(p_pc, GEN86_CC_E, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnlP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_NL, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnzP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_NZ, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovlP_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccP_mod_r(p_pc, GEN86_CC_L, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovncP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_NC, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnoP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_NO, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovsP_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccP_mod_r(p_pc, GEN86_CC_S, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovaP_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccP_mod_r(p_pc, GEN86_CC_A, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovoP_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccP_mod_r(p_pc, GEN86_CC_O, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovleP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_LE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnpP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_NP, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovgeP_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccP_mod_r(p_pc, GEN86_CC_GE, gen_modrm, reg, __VA_ARGS__)
#if LIBGEN86_TARGET_BITS == 64
#define gen86_cmovaeq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_AE, src_reg, dst_reg)
#define gen86_cmovbeq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_BE, src_reg, dst_reg)
#define gen86_cmovbq_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccq_r_r(p_pc, GEN86_CC_B, src_reg, dst_reg)
#define gen86_cmovnaq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_NA, src_reg, dst_reg)
#define gen86_cmovnaeq_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccq_r_r(p_pc, GEN86_CC_NAE, src_reg, dst_reg)
#define gen86_cmovpeq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_PE, src_reg, dst_reg)
#define gen86_cmovneq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_NE, src_reg, dst_reg)
#define gen86_cmovngq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_NG, src_reg, dst_reg)
#define gen86_cmovgq_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccq_r_r(p_pc, GEN86_CC_G, src_reg, dst_reg)
#define gen86_cmovzq_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccq_r_r(p_pc, GEN86_CC_Z, src_reg, dst_reg)
#define gen86_cmovnsq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_NS, src_reg, dst_reg)
#define gen86_cmovpq_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccq_r_r(p_pc, GEN86_CC_P, src_reg, dst_reg)
#define gen86_cmovnbq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_NB, src_reg, dst_reg)
#define gen86_cmovcq_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccq_r_r(p_pc, GEN86_CC_C, src_reg, dst_reg)
#define gen86_cmovngeq_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccq_r_r(p_pc, GEN86_CC_NGE, src_reg, dst_reg)
#define gen86_cmovnbeq_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccq_r_r(p_pc, GEN86_CC_NBE, src_reg, dst_reg)
#define gen86_cmovnleq_r_r(p_pc, src_reg, dst_reg)      gen86_cmovccq_r_r(p_pc, GEN86_CC_NLE, src_reg, dst_reg)
#define gen86_cmovpoq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_PO, src_reg, dst_reg)
#define gen86_cmoveq_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccq_r_r(p_pc, GEN86_CC_E, src_reg, dst_reg)
#define gen86_cmovnlq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_NL, src_reg, dst_reg)
#define gen86_cmovnzq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_NZ, src_reg, dst_reg)
#define gen86_cmovlq_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccq_r_r(p_pc, GEN86_CC_L, src_reg, dst_reg)
#define gen86_cmovncq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_NC, src_reg, dst_reg)
#define gen86_cmovnoq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_NO, src_reg, dst_reg)
#define gen86_cmovsq_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccq_r_r(p_pc, GEN86_CC_S, src_reg, dst_reg)
#define gen86_cmovaq_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccq_r_r(p_pc, GEN86_CC_A, src_reg, dst_reg)
#define gen86_cmovoq_r_r(p_pc, src_reg, dst_reg)        gen86_cmovccq_r_r(p_pc, GEN86_CC_O, src_reg, dst_reg)
#define gen86_cmovleq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_LE, src_reg, dst_reg)
#define gen86_cmovnpq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_NP, src_reg, dst_reg)
#define gen86_cmovgeq_r_r(p_pc, src_reg, dst_reg)       gen86_cmovccq_r_r(p_pc, GEN86_CC_GE, src_reg, dst_reg)
#define gen86_cmovaeq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_AE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovbeq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_BE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovbq_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccq_mod_r(p_pc, GEN86_CC_B, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnaq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_NA, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnaeq_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccq_mod_r(p_pc, GEN86_CC_NAE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovpeq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_PE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovneq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_NE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovngq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_NG, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovgq_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccq_mod_r(p_pc, GEN86_CC_G, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovzq_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccq_mod_r(p_pc, GEN86_CC_Z, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnsq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_NS, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovpq_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccq_mod_r(p_pc, GEN86_CC_P, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnbq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_NB, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovcq_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccq_mod_r(p_pc, GEN86_CC_C, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovngeq_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccq_mod_r(p_pc, GEN86_CC_NGE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnbeq_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccq_mod_r(p_pc, GEN86_CC_NBE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnleq_mod_r(p_pc, gen_modrm, reg, ...) gen86_cmovccq_mod_r(p_pc, GEN86_CC_NLE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovpoq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_PO, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmoveq_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccq_mod_r(p_pc, GEN86_CC_E, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnlq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_NL, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnzq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_NZ, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovlq_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccq_mod_r(p_pc, GEN86_CC_L, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovncq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_NC, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnoq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_NO, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovsq_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccq_mod_r(p_pc, GEN86_CC_S, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovaq_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccq_mod_r(p_pc, GEN86_CC_A, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovoq_mod_r(p_pc, gen_modrm, reg, ...)   gen86_cmovccq_mod_r(p_pc, GEN86_CC_O, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovleq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_LE, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovnpq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_NP, gen_modrm, reg, __VA_ARGS__)
#define gen86_cmovgeq_mod_r(p_pc, gen_modrm, reg, ...)  gen86_cmovccq_mod_r(p_pc, GEN86_CC_GE, gen_modrm, reg, __VA_ARGS__)
#endif /* LIBGEN86_TARGET_BITS == 64 */
/*[[[end]]]*/

/*[[[deemon
local names = { "add", "or",  "adc", "sbb", "and", "sub", "xor", "cmp" };
for (local n: names) {
	local pad = " " * (3 - #n);
	print("#define gen86_", n, "b_imm_r(p_pc, imm, reg)", pad, " /" "* ", n, "b", pad, " $imm, %reg *" "/ gen86_", n, "b_imm_mod(p_pc, gen86_modrm_r, imm, reg)");
	print("#define gen86_", n, "w_imm_r(p_pc, imm, reg)", pad, " /" "* ", n, "w", pad, " $imm, %reg *" "/ gen86_", n, "w_imm_mod(p_pc, gen86_modrm_r, imm, reg)");
	print("#define gen86_", n, "l_imm_r(p_pc, imm, reg)", pad, " /" "* ", n, "l", pad, " $imm, %reg *" "/ gen86_", n, "l_imm_mod(p_pc, gen86_modrm_r, imm, reg)");
	print("#define gen86_", n, "P_imm_r(p_pc, imm, reg)", pad, " /" "* ", n, "P", pad, " $imm, %reg *" "/ gen86_", n, "P_imm_mod(p_pc, gen86_modrm_r, imm, reg)");
}
print("#if LIBGEN86_TARGET_BITS == 64");
for (local n: names) {
	local pad = " " * (3 - #n);
	print("#define gen86_", n, "q_imm_r(p_pc, imm, reg)", pad, " /" "* ", n, "q", pad, " $imm, %reg *" "/ gen86_", n, "q_imm_mod(p_pc, gen86_modrm_r, imm, reg)");
}
print("#endif /" "* LIBGEN86_TARGET_BITS == 64 *" "/");
]]]*/
#define gen86_addb_imm_r(p_pc, imm, reg) /* addb $imm, %reg */ gen86_addb_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_addw_imm_r(p_pc, imm, reg) /* addw $imm, %reg */ gen86_addw_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_addl_imm_r(p_pc, imm, reg) /* addl $imm, %reg */ gen86_addl_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_addP_imm_r(p_pc, imm, reg) /* addP $imm, %reg */ gen86_addP_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_orb_imm_r(p_pc, imm, reg)  /* orb  $imm, %reg */ gen86_orb_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_orw_imm_r(p_pc, imm, reg)  /* orw  $imm, %reg */ gen86_orw_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_orl_imm_r(p_pc, imm, reg)  /* orl  $imm, %reg */ gen86_orl_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_orP_imm_r(p_pc, imm, reg)  /* orP  $imm, %reg */ gen86_orP_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_adcb_imm_r(p_pc, imm, reg) /* adcb $imm, %reg */ gen86_adcb_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_adcw_imm_r(p_pc, imm, reg) /* adcw $imm, %reg */ gen86_adcw_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_adcl_imm_r(p_pc, imm, reg) /* adcl $imm, %reg */ gen86_adcl_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_adcP_imm_r(p_pc, imm, reg) /* adcP $imm, %reg */ gen86_adcP_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_sbbb_imm_r(p_pc, imm, reg) /* sbbb $imm, %reg */ gen86_sbbb_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_sbbw_imm_r(p_pc, imm, reg) /* sbbw $imm, %reg */ gen86_sbbw_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_sbbl_imm_r(p_pc, imm, reg) /* sbbl $imm, %reg */ gen86_sbbl_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_sbbP_imm_r(p_pc, imm, reg) /* sbbP $imm, %reg */ gen86_sbbP_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_andb_imm_r(p_pc, imm, reg) /* andb $imm, %reg */ gen86_andb_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_andw_imm_r(p_pc, imm, reg) /* andw $imm, %reg */ gen86_andw_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_andl_imm_r(p_pc, imm, reg) /* andl $imm, %reg */ gen86_andl_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_andP_imm_r(p_pc, imm, reg) /* andP $imm, %reg */ gen86_andP_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_subb_imm_r(p_pc, imm, reg) /* subb $imm, %reg */ gen86_subb_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_subw_imm_r(p_pc, imm, reg) /* subw $imm, %reg */ gen86_subw_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_subl_imm_r(p_pc, imm, reg) /* subl $imm, %reg */ gen86_subl_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_subP_imm_r(p_pc, imm, reg) /* subP $imm, %reg */ gen86_subP_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_xorb_imm_r(p_pc, imm, reg) /* xorb $imm, %reg */ gen86_xorb_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_xorw_imm_r(p_pc, imm, reg) /* xorw $imm, %reg */ gen86_xorw_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_xorl_imm_r(p_pc, imm, reg) /* xorl $imm, %reg */ gen86_xorl_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_xorP_imm_r(p_pc, imm, reg) /* xorP $imm, %reg */ gen86_xorP_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_cmpb_imm_r(p_pc, imm, reg) /* cmpb $imm, %reg */ gen86_cmpb_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_cmpw_imm_r(p_pc, imm, reg) /* cmpw $imm, %reg */ gen86_cmpw_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_cmpl_imm_r(p_pc, imm, reg) /* cmpl $imm, %reg */ gen86_cmpl_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_cmpP_imm_r(p_pc, imm, reg) /* cmpP $imm, %reg */ gen86_cmpP_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#if LIBGEN86_TARGET_BITS == 64
#define gen86_addq_imm_r(p_pc, imm, reg) /* addq $imm, %reg */ gen86_addq_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_orq_imm_r(p_pc, imm, reg)  /* orq  $imm, %reg */ gen86_orq_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_adcq_imm_r(p_pc, imm, reg) /* adcq $imm, %reg */ gen86_adcq_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_sbbq_imm_r(p_pc, imm, reg) /* sbbq $imm, %reg */ gen86_sbbq_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_andq_imm_r(p_pc, imm, reg) /* andq $imm, %reg */ gen86_andq_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_subq_imm_r(p_pc, imm, reg) /* subq $imm, %reg */ gen86_subq_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_xorq_imm_r(p_pc, imm, reg) /* xorq $imm, %reg */ gen86_xorq_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#define gen86_cmpq_imm_r(p_pc, imm, reg) /* cmpq $imm, %reg */ gen86_cmpq_imm_mod(p_pc, gen86_modrm_r, imm, reg)
#endif /* LIBGEN86_TARGET_BITS == 64 */
/*[[[end]]]*/

/* For convenience, define inlined modr/m versions of `mov' */
#define gen86_movb_d_r(p_pc, src_disps, dst_reg)                                    /* movb src_disps, %dst_reg                                 */ gen86_movb_mod_r(p_pc, gen86_modrm_d, dst_reg, src_disps)
#define gen86_movw_d_r(p_pc, src_disps, dst_reg)                                    /* movw src_disps, %dst_reg                                 */ gen86_movw_mod_r(p_pc, gen86_modrm_d, dst_reg, src_disps)
#define gen86_movl_d_r(p_pc, src_disps, dst_reg)                                    /* movl src_disps, %dst_reg                                 */ gen86_movl_mod_r(p_pc, gen86_modrm_d, dst_reg, src_disps)
#define gen86_movP_d_r(p_pc, src_disps, dst_reg)                                    /* movP src_disps, %dst_reg                                 */ gen86_movP_mod_r(p_pc, gen86_modrm_d, dst_reg, src_disps)
#define gen86_movb_b_r(p_pc, src_breg, dst_reg)                                     /* movb (%src_breg), %dst_reg                               */ gen86_movb_mod_r(p_pc, gen86_modrm_b, dst_reg, src_breg)
#define gen86_movw_b_r(p_pc, src_breg, dst_reg)                                     /* movw (%src_breg), %dst_reg                               */ gen86_movw_mod_r(p_pc, gen86_modrm_b, dst_reg, src_breg)
#define gen86_movl_b_r(p_pc, src_breg, dst_reg)                                     /* movl (%src_breg), %dst_reg                               */ gen86_movl_mod_r(p_pc, gen86_modrm_b, dst_reg, src_breg)
#define gen86_movP_b_r(p_pc, src_breg, dst_reg)                                     /* movP (%src_breg), %dst_reg                               */ gen86_movP_mod_r(p_pc, gen86_modrm_b, dst_reg, src_breg)
#define gen86_movb_db_r(p_pc, src_disps, src_breg, dst_reg)                         /* movb src_disps(%src_breg), %dst_reg                      */ gen86_movb_mod_r(p_pc, gen86_modrm_db, dst_reg, src_disps, src_breg)
#define gen86_movw_db_r(p_pc, src_disps, src_breg, dst_reg)                         /* movw src_disps(%src_breg), %dst_reg                      */ gen86_movw_mod_r(p_pc, gen86_modrm_db, dst_reg, src_disps, src_breg)
#define gen86_movl_db_r(p_pc, src_disps, src_breg, dst_reg)                         /* movl src_disps(%src_breg), %dst_reg                      */ gen86_movl_mod_r(p_pc, gen86_modrm_db, dst_reg, src_disps, src_breg)
#define gen86_movP_db_r(p_pc, src_disps, src_breg, dst_reg)                         /* movP src_disps(%src_breg), %dst_reg                      */ gen86_movP_mod_r(p_pc, gen86_modrm_db, dst_reg, src_disps, src_breg)
#define gen86_movb_bi_r(p_pc, src_breg, src_index, dst_reg)                         /* movb (%src_breg,%src_index), %dst_reg                    */ gen86_movb_mod_r(p_pc, gen86_modrm_bi, dst_reg, src_breg, src_index)
#define gen86_movw_bi_r(p_pc, src_breg, src_index, dst_reg)                         /* movw (%src_breg,%src_index), %dst_reg                    */ gen86_movw_mod_r(p_pc, gen86_modrm_bi, dst_reg, src_breg, src_index)
#define gen86_movl_bi_r(p_pc, src_breg, src_index, dst_reg)                         /* movl (%src_breg,%src_index), %dst_reg                    */ gen86_movl_mod_r(p_pc, gen86_modrm_bi, dst_reg, src_breg, src_index)
#define gen86_movP_bi_r(p_pc, src_breg, src_index, dst_reg)                         /* movP (%src_breg,%src_index), %dst_reg                    */ gen86_movP_mod_r(p_pc, gen86_modrm_bi, dst_reg, src_breg, src_index)
#define gen86_movb_dbi_r(p_pc, src_disps, src_breg, src_index, dst_reg)             /* movb src_disps(%src_breg,%src_index), %dst_reg           */ gen86_movb_mod_r(p_pc, gen86_modrm_dbi, dst_reg, src_disps, src_breg, src_index)
#define gen86_movw_dbi_r(p_pc, src_disps, src_breg, src_index, dst_reg)             /* movw src_disps(%src_breg,%src_index), %dst_reg           */ gen86_movw_mod_r(p_pc, gen86_modrm_dbi, dst_reg, src_disps, src_breg, src_index)
#define gen86_movl_dbi_r(p_pc, src_disps, src_breg, src_index, dst_reg)             /* movl src_disps(%src_breg,%src_index), %dst_reg           */ gen86_movl_mod_r(p_pc, gen86_modrm_dbi, dst_reg, src_disps, src_breg, src_index)
#define gen86_movP_dbi_r(p_pc, src_disps, src_breg, src_index, dst_reg)             /* movP src_disps(%src_breg,%src_index), %dst_reg           */ gen86_movP_mod_r(p_pc, gen86_modrm_dbi, dst_reg, src_disps, src_breg, src_index)
#define gen86_movb_bis_r(p_pc, src_breg, src_index, src_scale, dst_reg)             /* movb (%src_breg,%src_index,src_scale), %dst_reg          */ gen86_movb_mod_r(p_pc, gen86_modrm_bis, dst_reg, src_breg, src_index, src_scale)
#define gen86_movw_bis_r(p_pc, src_breg, src_index, src_scale, dst_reg)             /* movw (%src_breg,%src_index,src_scale), %dst_reg          */ gen86_movw_mod_r(p_pc, gen86_modrm_bis, dst_reg, src_breg, src_index, src_scale)
#define gen86_movl_bis_r(p_pc, src_breg, src_index, src_scale, dst_reg)             /* movl (%src_breg,%src_index,src_scale), %dst_reg          */ gen86_movl_mod_r(p_pc, gen86_modrm_bis, dst_reg, src_breg, src_index, src_scale)
#define gen86_movP_bis_r(p_pc, src_breg, src_index, src_scale, dst_reg)             /* movP (%src_breg,%src_index,src_scale), %dst_reg          */ gen86_movP_mod_r(p_pc, gen86_modrm_bis, dst_reg, src_breg, src_index, src_scale)
#define gen86_movb_dbis_r(p_pc, src_disps, src_breg, src_index, src_scale, dst_reg) /* movb src_disps(%src_breg,%src_index,src_scale), %dst_reg */ gen86_movb_mod_r(p_pc, gen86_modrm_dbis, dst_reg, src_disps, src_breg, src_index, src_scale)
#define gen86_movw_dbis_r(p_pc, src_disps, src_breg, src_index, src_scale, dst_reg) /* movw src_disps(%src_breg,%src_index,src_scale), %dst_reg */ gen86_movw_mod_r(p_pc, gen86_modrm_dbis, dst_reg, src_disps, src_breg, src_index, src_scale)
#define gen86_movl_dbis_r(p_pc, src_disps, src_breg, src_index, src_scale, dst_reg) /* movl src_disps(%src_breg,%src_index,src_scale), %dst_reg */ gen86_movl_mod_r(p_pc, gen86_modrm_dbis, dst_reg, src_disps, src_breg, src_index, src_scale)
#define gen86_movP_dbis_r(p_pc, src_disps, src_breg, src_index, src_scale, dst_reg) /* movP src_disps(%src_breg,%src_index,src_scale), %dst_reg */ gen86_movP_mod_r(p_pc, gen86_modrm_dbis, dst_reg, src_disps, src_breg, src_index, src_scale)
#define gen86_movb_r_d(p_pc, src_reg, dst_disps)                                    /* movb %src_reg, dst_disps                                 */ gen86_movb_r_mod(p_pc, gen86_modrm_d, src_reg, dst_disps)
#define gen86_movw_r_d(p_pc, src_reg, dst_disps)                                    /* movw %src_reg, dst_disps                                 */ gen86_movw_r_mod(p_pc, gen86_modrm_d, src_reg, dst_disps)
#define gen86_movl_r_d(p_pc, src_reg, dst_disps)                                    /* movl %src_reg, dst_disps                                 */ gen86_movl_r_mod(p_pc, gen86_modrm_d, src_reg, dst_disps)
#define gen86_movP_r_d(p_pc, src_reg, dst_disps)                                    /* movP %src_reg, dst_disps                                 */ gen86_movP_r_mod(p_pc, gen86_modrm_d, src_reg, dst_disps)
#define gen86_movb_r_b(p_pc, src_reg, dst_breg)                                     /* movb %src_reg, (%dst_breg)                               */ gen86_movb_r_mod(p_pc, gen86_modrm_b, src_reg, dst_breg)
#define gen86_movw_r_b(p_pc, src_reg, dst_breg)                                     /* movw %src_reg, (%dst_breg)                               */ gen86_movw_r_mod(p_pc, gen86_modrm_b, src_reg, dst_breg)
#define gen86_movl_r_b(p_pc, src_reg, dst_breg)                                     /* movl %src_reg, (%dst_breg)                               */ gen86_movl_r_mod(p_pc, gen86_modrm_b, src_reg, dst_breg)
#define gen86_movP_r_b(p_pc, src_reg, dst_breg)                                     /* movP %src_reg, (%dst_breg)                               */ gen86_movP_r_mod(p_pc, gen86_modrm_b, src_reg, dst_breg)
#define gen86_movb_r_db(p_pc, src_reg, dst_disps, dst_breg)                         /* movb %src_reg, dst_disps(%dst_breg)                      */ gen86_movb_r_mod(p_pc, gen86_modrm_db, src_reg, dst_disps, dst_breg)
#define gen86_movw_r_db(p_pc, src_reg, dst_disps, dst_breg)                         /* movw %src_reg, dst_disps(%dst_breg)                      */ gen86_movw_r_mod(p_pc, gen86_modrm_db, src_reg, dst_disps, dst_breg)
#define gen86_movl_r_db(p_pc, src_reg, dst_disps, dst_breg)                         /* movl %src_reg, dst_disps(%dst_breg)                      */ gen86_movl_r_mod(p_pc, gen86_modrm_db, src_reg, dst_disps, dst_breg)
#define gen86_movP_r_db(p_pc, src_reg, dst_disps, dst_breg)                         /* movP %src_reg, dst_disps(%dst_breg)                      */ gen86_movP_r_mod(p_pc, gen86_modrm_db, src_reg, dst_disps, dst_breg)
#define gen86_movb_r_bi(p_pc, src_reg, dst_breg, dst_index)                         /* movb %src_reg, (%dst_breg,%dst_index)                    */ gen86_movb_r_mod(p_pc, gen86_modrm_bi, src_reg, dst_breg, dst_index)
#define gen86_movw_r_bi(p_pc, src_reg, dst_breg, dst_index)                         /* movw %src_reg, (%dst_breg,%dst_index)                    */ gen86_movw_r_mod(p_pc, gen86_modrm_bi, src_reg, dst_breg, dst_index)
#define gen86_movl_r_bi(p_pc, src_reg, dst_breg, dst_index)                         /* movl %src_reg, (%dst_breg,%dst_index)                    */ gen86_movl_r_mod(p_pc, gen86_modrm_bi, src_reg, dst_breg, dst_index)
#define gen86_movP_r_bi(p_pc, src_reg, dst_breg, dst_index)                         /* movP %src_reg, (%dst_breg,%dst_index)                    */ gen86_movP_r_mod(p_pc, gen86_modrm_bi, src_reg, dst_breg, dst_index)
#define gen86_movb_r_dbi(p_pc, src_reg, dst_disps, dst_breg, dst_index)             /* movb %src_reg, dst_disps(%dst_breg,%dst_index)           */ gen86_movb_r_mod(p_pc, gen86_modrm_dbi, src_reg, dst_disps, dst_breg, dst_index)
#define gen86_movw_r_dbi(p_pc, src_reg, dst_disps, dst_breg, dst_index)             /* movw %src_reg, dst_disps(%dst_breg,%dst_index)           */ gen86_movw_r_mod(p_pc, gen86_modrm_dbi, src_reg, dst_disps, dst_breg, dst_index)
#define gen86_movl_r_dbi(p_pc, src_reg, dst_disps, dst_breg, dst_index)             /* movl %src_reg, dst_disps(%dst_breg,%dst_index)           */ gen86_movl_r_mod(p_pc, gen86_modrm_dbi, src_reg, dst_disps, dst_breg, dst_index)
#define gen86_movP_r_dbi(p_pc, src_reg, dst_disps, dst_breg, dst_index)             /* movP %src_reg, dst_disps(%dst_breg,%dst_index)           */ gen86_movP_r_mod(p_pc, gen86_modrm_dbi, src_reg, dst_disps, dst_breg, dst_index)
#define gen86_movb_r_bis(p_pc, src_reg, dst_breg, dst_index, dst_scale)             /* movb %src_reg, (%dst_breg,%dst_index,dst_scale)          */ gen86_movb_r_mod(p_pc, gen86_modrm_bis, src_reg, dst_breg, dst_index, dst_scale)
#define gen86_movw_r_bis(p_pc, src_reg, dst_breg, dst_index, dst_scale)             /* movw %src_reg, (%dst_breg,%dst_index,dst_scale)          */ gen86_movw_r_mod(p_pc, gen86_modrm_bis, src_reg, dst_breg, dst_index, dst_scale)
#define gen86_movl_r_bis(p_pc, src_reg, dst_breg, dst_index, dst_scale)             /* movl %src_reg, (%dst_breg,%dst_index,dst_scale)          */ gen86_movl_r_mod(p_pc, gen86_modrm_bis, src_reg, dst_breg, dst_index, dst_scale)
#define gen86_movP_r_bis(p_pc, src_reg, dst_breg, dst_index, dst_scale)             /* movP %src_reg, (%dst_breg,%dst_index,dst_scale)          */ gen86_movP_r_mod(p_pc, gen86_modrm_bis, src_reg, dst_breg, dst_index, dst_scale)
#define gen86_movb_r_dbis(p_pc, src_reg, dst_disps, dst_breg, dst_index, dst_scale) /* movb %src_reg, dst_disps(%dst_breg,%dst_index,dst_scale) */ gen86_movb_r_mod(p_pc, gen86_modrm_dbis, src_reg, dst_disps, dst_breg, dst_index, dst_scale)
#define gen86_movw_r_dbis(p_pc, src_reg, dst_disps, dst_breg, dst_index, dst_scale) /* movw %src_reg, dst_disps(%dst_breg,%dst_index,dst_scale) */ gen86_movw_r_mod(p_pc, gen86_modrm_dbis, src_reg, dst_disps, dst_breg, dst_index, dst_scale)
#define gen86_movl_r_dbis(p_pc, src_reg, dst_disps, dst_breg, dst_index, dst_scale) /* movl %src_reg, dst_disps(%dst_breg,%dst_index,dst_scale) */ gen86_movl_r_mod(p_pc, gen86_modrm_dbis, src_reg, dst_disps, dst_breg, dst_index, dst_scale)
#define gen86_movP_r_dbis(p_pc, src_reg, dst_disps, dst_breg, dst_index, dst_scale) /* movP %src_reg, dst_disps(%dst_breg,%dst_index,dst_scale) */ gen86_movP_r_mod(p_pc, gen86_modrm_dbis, src_reg, dst_disps, dst_breg, dst_index, dst_scale)
#define gen86_movb_imm_d(p_pc, imm, dst_disps)                                      /* movb $imm, dst_disps                                     */ gen86_movb_imm_mod(p_pc, gen86_modrm_d, imm, dst_disps)
#define gen86_movw_imm_d(p_pc, imm, dst_disps)                                      /* movw $imm, dst_disps                                     */ gen86_movw_imm_mod(p_pc, gen86_modrm_d, imm, dst_disps)
#define gen86_movl_imm_d(p_pc, imm, dst_disps)                                      /* movl $imm, dst_disps                                     */ gen86_movl_imm_mod(p_pc, gen86_modrm_d, imm, dst_disps)
#define gen86_movP_imm_d(p_pc, imm, dst_disps)                                      /* movP $imm, dst_disps                                     */ gen86_movP_imm_mod(p_pc, gen86_modrm_d, imm, dst_disps)
#define gen86_movb_imm_b(p_pc, imm, dst_breg)                                       /* movb $imm, (%dst_breg)                                   */ gen86_movb_imm_mod(p_pc, gen86_modrm_b, imm, dst_breg)
#define gen86_movw_imm_b(p_pc, imm, dst_breg)                                       /* movw $imm, (%dst_breg)                                   */ gen86_movw_imm_mod(p_pc, gen86_modrm_b, imm, dst_breg)
#define gen86_movl_imm_b(p_pc, imm, dst_breg)                                       /* movl $imm, (%dst_breg)                                   */ gen86_movl_imm_mod(p_pc, gen86_modrm_b, imm, dst_breg)
#define gen86_movP_imm_b(p_pc, imm, dst_breg)                                       /* movP $imm, (%dst_breg)                                   */ gen86_movP_imm_mod(p_pc, gen86_modrm_b, imm, dst_breg)
#define gen86_movb_imm_db(p_pc, imm, dst_disps, dst_breg)                           /* movb $imm, dst_disps(%dst_breg)                          */ gen86_movb_imm_mod(p_pc, gen86_modrm_db, imm, dst_disps, dst_breg)
#define gen86_movw_imm_db(p_pc, imm, dst_disps, dst_breg)                           /* movw $imm, dst_disps(%dst_breg)                          */ gen86_movw_imm_mod(p_pc, gen86_modrm_db, imm, dst_disps, dst_breg)
#define gen86_movl_imm_db(p_pc, imm, dst_disps, dst_breg)                           /* movl $imm, dst_disps(%dst_breg)                          */ gen86_movl_imm_mod(p_pc, gen86_modrm_db, imm, dst_disps, dst_breg)
#define gen86_movP_imm_db(p_pc, imm, dst_disps, dst_breg)                           /* movP $imm, dst_disps(%dst_breg)                          */ gen86_movP_imm_mod(p_pc, gen86_modrm_db, imm, dst_disps, dst_breg)
#define gen86_movb_imm_bi(p_pc, imm, dst_breg, dst_index)                           /* movb $imm, (%dst_breg,%dst_index)                        */ gen86_movb_imm_mod(p_pc, gen86_modrm_bi, imm, dst_breg, dst_index)
#define gen86_movw_imm_bi(p_pc, imm, dst_breg, dst_index)                           /* movw $imm, (%dst_breg,%dst_index)                        */ gen86_movw_imm_mod(p_pc, gen86_modrm_bi, imm, dst_breg, dst_index)
#define gen86_movl_imm_bi(p_pc, imm, dst_breg, dst_index)                           /* movl $imm, (%dst_breg,%dst_index)                        */ gen86_movl_imm_mod(p_pc, gen86_modrm_bi, imm, dst_breg, dst_index)
#define gen86_movP_imm_bi(p_pc, imm, dst_breg, dst_index)                           /* movP $imm, (%dst_breg,%dst_index)                        */ gen86_movP_imm_mod(p_pc, gen86_modrm_bi, imm, dst_breg, dst_index)
#define gen86_movb_imm_dbi(p_pc, imm, dst_disps, dst_breg, dst_index)               /* movb $imm, dst_disps(%dst_breg,%dst_index)               */ gen86_movb_imm_mod(p_pc, gen86_modrm_dbi, imm, dst_disps, dst_breg, dst_index)
#define gen86_movw_imm_dbi(p_pc, imm, dst_disps, dst_breg, dst_index)               /* movw $imm, dst_disps(%dst_breg,%dst_index)               */ gen86_movw_imm_mod(p_pc, gen86_modrm_dbi, imm, dst_disps, dst_breg, dst_index)
#define gen86_movl_imm_dbi(p_pc, imm, dst_disps, dst_breg, dst_index)               /* movl $imm, dst_disps(%dst_breg,%dst_index)               */ gen86_movl_imm_mod(p_pc, gen86_modrm_dbi, imm, dst_disps, dst_breg, dst_index)
#define gen86_movP_imm_dbi(p_pc, imm, dst_disps, dst_breg, dst_index)               /* movP $imm, dst_disps(%dst_breg,%dst_index)               */ gen86_movP_imm_mod(p_pc, gen86_modrm_dbi, imm, dst_disps, dst_breg, dst_index)
#define gen86_movb_imm_bis(p_pc, imm, dst_breg, dst_index, dst_scale)               /* movb $imm, (%dst_breg,%dst_index,dst_scale)              */ gen86_movb_imm_mod(p_pc, gen86_modrm_bis, imm, dst_breg, dst_index, dst_scale)
#define gen86_movw_imm_bis(p_pc, imm, dst_breg, dst_index, dst_scale)               /* movw $imm, (%dst_breg,%dst_index,dst_scale)              */ gen86_movw_imm_mod(p_pc, gen86_modrm_bis, imm, dst_breg, dst_index, dst_scale)
#define gen86_movl_imm_bis(p_pc, imm, dst_breg, dst_index, dst_scale)               /* movl $imm, (%dst_breg,%dst_index,dst_scale)              */ gen86_movl_imm_mod(p_pc, gen86_modrm_bis, imm, dst_breg, dst_index, dst_scale)
#define gen86_movP_imm_bis(p_pc, imm, dst_breg, dst_index, dst_scale)               /* movP $imm, (%dst_breg,%dst_index,dst_scale)              */ gen86_movP_imm_mod(p_pc, gen86_modrm_bis, imm, dst_breg, dst_index, dst_scale)
#define gen86_movb_imm_dbis(p_pc, imm, dst_disps, dst_breg, dst_index, dst_scale)   /* movb $imm, dst_disps(%dst_breg,%dst_index,dst_scale)     */ gen86_movb_imm_mod(p_pc, gen86_modrm_dbis, imm, dst_disps, dst_breg, dst_index, dst_scale)
#define gen86_movw_imm_dbis(p_pc, imm, dst_disps, dst_breg, dst_index, dst_scale)   /* movw $imm, dst_disps(%dst_breg,%dst_index,dst_scale)     */ gen86_movw_imm_mod(p_pc, gen86_modrm_dbis, imm, dst_disps, dst_breg, dst_index, dst_scale)
#define gen86_movl_imm_dbis(p_pc, imm, dst_disps, dst_breg, dst_index, dst_scale)   /* movl $imm, dst_disps(%dst_breg,%dst_index,dst_scale)     */ gen86_movl_imm_mod(p_pc, gen86_modrm_dbis, imm, dst_disps, dst_breg, dst_index, dst_scale)
#define gen86_movP_imm_dbis(p_pc, imm, dst_disps, dst_breg, dst_index, dst_scale)   /* movP $imm, dst_disps(%dst_breg,%dst_index,dst_scale)     */ gen86_movP_imm_mod(p_pc, gen86_modrm_dbis, imm, dst_disps, dst_breg, dst_index, dst_scale)
#if LIBGEN86_TARGET_BITS == 64
#define gen86_movq_d_r(p_pc, src_disps, dst_reg)                                    /* movq src_disps, %dst_reg                                 */ gen86_movq_mod_r(p_pc, gen86_modrm_d, dst_reg, src_disps)
#define gen86_movq_b_r(p_pc, src_breg, dst_reg)                                     /* movq (%src_breg), %dst_reg                               */ gen86_movq_mod_r(p_pc, gen86_modrm_b, dst_reg, src_breg)
#define gen86_movq_db_r(p_pc, src_disps, src_breg, dst_reg)                         /* movq src_disps(%src_breg), %dst_reg                      */ gen86_movq_mod_r(p_pc, gen86_modrm_db, dst_reg, src_disps, src_breg)
#define gen86_movq_bi_r(p_pc, src_breg, src_index, dst_reg)                         /* movq src_disps(%src_breg,%src_index), %dst_reg           */ gen86_movq_mod_r(p_pc, gen86_modrm_bi, dst_reg, src_breg, src_index)
#define gen86_movq_dbi_r(p_pc, src_disps, src_breg, src_index, dst_reg)             /* movq src_disps(%src_breg,%src_index), %dst_reg           */ gen86_movq_mod_r(p_pc, gen86_modrm_dbi, dst_reg, src_disps, src_breg, src_index)
#define gen86_movq_bis_r(p_pc, src_breg, src_index, src_scale, dst_reg)             /* movq (%src_breg,%src_index,src_scale), %dst_reg          */ gen86_movq_mod_r(p_pc, gen86_modrm_bis, dst_reg, src_breg, src_index, src_scale)
#define gen86_movq_dbis_r(p_pc, src_disps, src_breg, src_index, src_scale, dst_reg) /* movq src_disps(%src_breg,%src_index,src_scale), %dst_reg */ gen86_movq_mod_r(p_pc, gen86_modrm_dbis, dst_reg, src_disps, src_breg, src_index, src_scale)
#define gen86_movq_r_d(p_pc, src_reg, dst_disps)                                    /* movq %src_reg, dst_disps                                 */ gen86_movq_r_mod(p_pc, gen86_modrm_d, src_reg, dst_disps)
#define gen86_movq_r_b(p_pc, src_reg, dst_breg)                                     /* movq %src_reg, (%dst_breg)                               */ gen86_movq_r_mod(p_pc, gen86_modrm_b, src_reg, dst_breg)
#define gen86_movq_r_db(p_pc, src_reg, dst_disps, dst_breg)                         /* movq %src_reg, dst_disps(%dst_breg)                      */ gen86_movq_r_mod(p_pc, gen86_modrm_db, src_reg, dst_disps, dst_breg)
#define gen86_movq_r_bi(p_pc, src_reg, dst_breg, dst_index)                         /* movq %src_reg, dst_disps(%dst_breg,%dst_index)           */ gen86_movq_r_mod(p_pc, gen86_modrm_bi, src_reg, dst_breg, dst_index)
#define gen86_movq_r_dbi(p_pc, src_reg, dst_disps, dst_breg, dst_index)             /* movq %src_reg, dst_disps(%dst_breg,%dst_index)           */ gen86_movq_r_mod(p_pc, gen86_modrm_dbi, src_reg, dst_disps, dst_breg, dst_index)
#define gen86_movq_r_bis(p_pc, src_reg, dst_breg, dst_index, dst_scale)             /* movq %src_reg, (%dst_breg,%dst_index,dst_scale)          */ gen86_movq_r_mod(p_pc, gen86_modrm_bis, src_reg, dst_breg, dst_index, dst_scale)
#define gen86_movq_r_dbis(p_pc, src_reg, dst_disps, dst_breg, dst_index, dst_scale) /* movq %src_reg, dst_disps(%dst_breg,%dst_index,dst_scale) */ gen86_movq_r_mod(p_pc, gen86_modrm_dbis, src_reg, dst_disps, dst_breg, dst_index, dst_scale)
#define gen86_movq_imm_d(p_pc, imm, dst_disps)                                      /* movq $imm, dst_disps                                     */ gen86_movq_imm_mod(p_pc, gen86_modrm_d, imm, dst_disps)
#define gen86_movq_imm_b(p_pc, imm, dst_breg)                                       /* movq $imm, (%dst_breg)                                   */ gen86_movq_imm_mod(p_pc, gen86_modrm_b, imm, dst_breg)
#define gen86_movq_imm_db(p_pc, imm, dst_disps, dst_breg)                           /* movq $imm, dst_disps(%dst_breg)                          */ gen86_movq_imm_mod(p_pc, gen86_modrm_db, imm, dst_disps, dst_breg)
#define gen86_movq_imm_bi(p_pc, imm, dst_breg, dst_index)                           /* movq $imm, dst_disps(%dst_breg,%dst_index)               */ gen86_movq_imm_mod(p_pc, gen86_modrm_bi, imm, dst_breg, dst_index)
#define gen86_movq_imm_dbi(p_pc, imm, dst_disps, dst_breg, dst_index)               /* movq $imm, dst_disps(%dst_breg,%dst_index)               */ gen86_movq_imm_mod(p_pc, gen86_modrm_dbi, imm, dst_disps, dst_breg, dst_index)
#define gen86_movq_imm_bis(p_pc, imm, dst_breg, dst_index, dst_scale)               /* movq $imm, (%dst_breg,%dst_index,dst_scale)              */ gen86_movq_imm_mod(p_pc, gen86_modrm_bis, imm, dst_breg, dst_index, dst_scale)
#define gen86_movq_imm_dbis(p_pc, imm, dst_disps, dst_breg, dst_index, dst_scale)   /* movq $imm, dst_disps(%dst_breg,%dst_index,dst_scale)     */ gen86_movq_imm_mod(p_pc, gen86_modrm_dbis, imm, dst_disps, dst_breg, dst_index, dst_scale)
#endif /* LIBGEN86_TARGET_BITS == 64 */

/* For convenience, define inlined modr/m versions of `lea' */
#define gen86_leaw_db_r(p_pc, disps, breg, dst_reg)                 /* leaw disps(%breg), %dst_reg              */ ((disps) == 0 ? gen86_movw_r_r(p_pc, breg, dst_reg) : gen86_leaw_mod_r(p_pc, gen86_modrm_db, dst_reg, disps, breg))
#define gen86_leal_db_r(p_pc, disps, breg, dst_reg)                 /* leal disps(%breg), %dst_reg              */ ((disps) == 0 ? gen86_movl_r_r(p_pc, breg, dst_reg) : gen86_leal_mod_r(p_pc, gen86_modrm_db, dst_reg, disps, breg))
#define gen86_leaP_db_r(p_pc, disps, breg, dst_reg)                 /* leaP disps(%breg), %dst_reg              */ ((disps) == 0 ? gen86_movP_r_r(p_pc, breg, dst_reg) : gen86_leaP_mod_r(p_pc, gen86_modrm_db, dst_reg, disps, breg))
#define gen86_leaw_bi_r(p_pc, breg, index, dst_reg)                 /* leaw (%breg,%index), %dst_reg            */ gen86_leaw_mod_r(p_pc, gen86_modrm_bi, dst_reg, breg, index)
#define gen86_leal_bi_r(p_pc, breg, index, dst_reg)                 /* leal (%breg,%index), %dst_reg            */ gen86_leal_mod_r(p_pc, gen86_modrm_bi, dst_reg, breg, index)
#define gen86_leaP_bi_r(p_pc, breg, index, dst_reg)                 /* leaP (%breg,%index), %dst_reg            */ gen86_leaP_mod_r(p_pc, gen86_modrm_bi, dst_reg, breg, index)
#define gen86_leaw_dbi_r(p_pc, disps, breg, index, dst_reg)         /* leaw disps(%breg,%index), %dst_reg       */ gen86_leaw_mod_r(p_pc, gen86_modrm_dbi, dst_reg, disps, breg, index)
#define gen86_leal_dbi_r(p_pc, disps, breg, index, dst_reg)         /* leal disps(%breg,%index), %dst_reg       */ gen86_leal_mod_r(p_pc, gen86_modrm_dbi, dst_reg, disps, breg, index)
#define gen86_leaP_dbi_r(p_pc, disps, breg, index, dst_reg)         /* leaP disps(%breg,%index), %dst_reg       */ gen86_leaP_mod_r(p_pc, gen86_modrm_dbi, dst_reg, disps, breg, index)
#define gen86_leaw_bis_r(p_pc, breg, index, scale, dst_reg)         /* leaw (%breg,%index,scale), %dst_reg      */ gen86_leaw_mod_r(p_pc, gen86_modrm_bis, dst_reg, breg, index, scale)
#define gen86_leal_bis_r(p_pc, breg, index, scale, dst_reg)         /* leal (%breg,%index,scale), %dst_reg      */ gen86_leal_mod_r(p_pc, gen86_modrm_bis, dst_reg, breg, index, scale)
#define gen86_leaP_bis_r(p_pc, breg, index, scale, dst_reg)         /* leaP (%breg,%index,scale), %dst_reg      */ gen86_leaP_mod_r(p_pc, gen86_modrm_bis, dst_reg, breg, index, scale)
#define gen86_leaw_dbis_r(p_pc, disps, breg, index, scale, dst_reg) /* leaw disps(%breg,%index,scale), %dst_reg */ gen86_leaw_mod_r(p_pc, gen86_modrm_dbis, dst_reg, disps, breg, index, scale)
#define gen86_leal_dbis_r(p_pc, disps, breg, index, scale, dst_reg) /* leal disps(%breg,%index,scale), %dst_reg */ gen86_leal_mod_r(p_pc, gen86_modrm_dbis, dst_reg, disps, breg, index, scale)
#define gen86_leaP_dbis_r(p_pc, disps, breg, index, scale, dst_reg) /* leaP disps(%breg,%index,scale), %dst_reg */ gen86_leaP_mod_r(p_pc, gen86_modrm_dbis, dst_reg, disps, breg, index, scale)
#define gen86_leaw_di_r(p_pc, disps, index, dst_reg)                /* leaw disps(,%index), %dst_reg            */ gen86_leaw_mod_r(p_pc, gen86_modrm_di, dst_reg, disps, index)
#define gen86_leal_di_r(p_pc, disps, index, dst_reg)                /* leal disps(,%index), %dst_reg            */ gen86_leal_mod_r(p_pc, gen86_modrm_di, dst_reg, disps, index)
#define gen86_leaP_di_r(p_pc, disps, index, dst_reg)                /* leaP disps(,%index), %dst_reg            */ gen86_leaP_mod_r(p_pc, gen86_modrm_di, dst_reg, disps, index)
#define gen86_leaw_is_r(p_pc, index, scale, dst_reg)                /* leaw (,%index,scale), %dst_reg           */ gen86_leaw_mod_r(p_pc, gen86_modrm_is, dst_reg, index, scale)
#define gen86_leal_is_r(p_pc, index, scale, dst_reg)                /* leal (,%index,scale), %dst_reg           */ gen86_leal_mod_r(p_pc, gen86_modrm_is, dst_reg, index, scale)
#define gen86_leaP_is_r(p_pc, index, scale, dst_reg)                /* leaP (,%index,scale), %dst_reg           */ gen86_leaP_mod_r(p_pc, gen86_modrm_is, dst_reg, index, scale)
#define gen86_leaw_dis_r(p_pc, disps, index, scale, dst_reg)        /* leaw disps(,%index,scale), %dst_reg      */ gen86_leaw_mod_r(p_pc, gen86_modrm_dis, dst_reg, disps, index, scale)
#define gen86_leal_dis_r(p_pc, disps, index, scale, dst_reg)        /* leal disps(,%index,scale), %dst_reg      */ gen86_leal_mod_r(p_pc, gen86_modrm_dis, dst_reg, disps, index, scale)
#define gen86_leaP_dis_r(p_pc, disps, index, scale, dst_reg)        /* leaP disps(,%index,scale), %dst_reg      */ gen86_leaP_mod_r(p_pc, gen86_modrm_dis, dst_reg, disps, index, scale)
#if LIBGEN86_TARGET_BITS == 64
#define gen86_leaq_db_r(p_pc, disps, breg, dst_reg)                 /* leaq disps(%breg), %dst_reg              */ ((disps) == 0 ? gen86_movq_r_r(p_pc, breg, dst_reg) : gen86_leaq_mod_r(p_pc, gen86_modrm_db, dst_reg, disps, breg))
#define gen86_leaq_bi_r(p_pc, breg, index, dst_reg)                 /* leaq disps(%breg,%index), %dst_reg       */ gen86_leaq_mod_r(p_pc, gen86_modrm_bi, dst_reg, breg, index)
#define gen86_leaq_dbi_r(p_pc, disps, breg, index, dst_reg)         /* leaq disps(%breg,%index), %dst_reg       */ gen86_leaq_mod_r(p_pc, gen86_modrm_dbi, dst_reg, disps, breg, index)
#define gen86_leaq_bis_r(p_pc, breg, index, scale, dst_reg)         /* leaq (%breg,%index,scale), %dst_reg      */ gen86_leaq_mod_r(p_pc, gen86_modrm_bis, dst_reg, breg, index, scale)
#define gen86_leaq_dbis_r(p_pc, disps, breg, index, scale, dst_reg) /* leaq disps(%breg,%index,scale), %dst_reg */ gen86_leaq_mod_r(p_pc, gen86_modrm_dbis, dst_reg, disps, breg, index, scale)
#define gen86_leaq_di_r(p_pc, disps, index, dst_reg)                /* leaq disps(,%index), %dst_reg            */ gen86_leaq_mod_r(p_pc, gen86_modrm_di, dst_reg, disps, index)
#define gen86_leaq_is_r(p_pc, index, scale, dst_reg)                /* leaq (,%index,scale), %dst_reg           */ gen86_leaq_mod_r(p_pc, gen86_modrm_is, dst_reg, index, scale)
#define gen86_leaq_dis_r(p_pc, disps, index, scale, dst_reg)        /* leaq disps(,%index,scale), %dst_reg      */ gen86_leaq_mod_r(p_pc, gen86_modrm_dis, dst_reg, disps, index, scale)
#endif /* LIBGEN86_TARGET_BITS == 64 */



#endif /* !_LIBGEN86_GEN_H */
