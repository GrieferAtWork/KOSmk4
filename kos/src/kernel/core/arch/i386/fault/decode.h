/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_H
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_H 1

#undef CONFIG_USE_HANDLE_BAD_USAGE
#if 0 /* TODO: Enable me */
#define CONFIG_USE_HANDLE_BAD_USAGE 1
#endif

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <libemu86/emu86.h>

DECL_BEGIN

/* TODO: Get rid of these macros */
#define R_EAX  EMU86_R_EAX /* Accumulator. */
#define R_ECX  EMU86_R_ECX /* Counter register. */
#define R_EDX  EMU86_R_EDX /* General purpose d-register. */
#define R_EBX  EMU86_R_EBX /* General purpose b-register. */
#define R_ESP  EMU86_R_ESP /* Stack pointer. */
#define R_EBP  EMU86_R_EBP /* Stack base pointer. */
#define R_ESI  EMU86_R_ESI /* Source pointer. */
#define R_EDI  EMU86_R_EDI /* Destination pointer. */
#ifdef __x86_64__
#define R_R8   EMU86_R_R8  /* R8 */
#define R_R9   EMU86_R_R9  /* R9 */
#define R_R10  EMU86_R_R10 /* R10 */
#define R_R11  EMU86_R_R11 /* R11 */
#define R_R12  EMU86_R_R12 /* R12 */
#define R_R13  EMU86_R_R13 /* R13 */
#define R_R14  EMU86_R_R14 /* R14 */
#define R_R15  EMU86_R_R15 /* R15 */
#endif /* __x86_64__ */


/* Instruction flags. */
typedef emu86_opflags_t op_flag_t;

/* TODO: Get rid of these macros */
#define F_OP16        EMU86_F_OP16        /* The 0x66 prefix is being used. */
#define F_AD16        EMU86_F_AD16        /* The 0x67 prefix is being used. */
#define F_LOCK        EMU86_F_LOCK        /* The `lock' (0xf0) prefix is being used. */
#define F_REPNE       EMU86_F_REPNE       /* The `repne' (0xf2) prefix is being used. */
#define F_REP         EMU86_F_REP         /* The `rep' (0xf3) prefix is being used. */
#define F_HASVEX      EMU86_F_HASVEX      /* A VEX prefix was given. */
#define F_SEGMASK     EMU86_F_SEGMASK     /* Mask for segment overrides. */
#define F_VEX_VVVVV_M EMU86_F_VEX_VVVVV_M /* Mask for VEX.VVVVV */
#define F_VEX_VVVVV_S EMU86_F_VEX_VVVVV_S /* Shift for VEX.VVVVV */
#define F_VEX_W       EMU86_F_VEX_W       /* Value of VEX.W */
#define F_VEX_LL_M    EMU86_F_VEX_LL_M    /* Value of VEX.LL */
#define F_VEX_LL_S    EMU86_F_VEX_LL_S    /* Shift for VEX.LL */
#ifdef __x86_64__
#define F_AD64        F_AD16              /* The 0x67 prefix is being used. */
#define F_IS_X32      EMU86_F_32BIT       /* The hosted process is running in compatibility mode (32-bit). */
#define F_HASREX      EMU86_F_HASREX      /* A REX prefix is being used. */
#define F_REXSHFT     EMU86_F_REXSHFT     /* Shift for the REX prefix byte. */
#define F_REXMASK     EMU86_F_REXMASK     /* Mask of the REX prefix byte. */
#define F_REX_W       EMU86_F_REX_W       /* The REX.W flag (Indicates 64-bit operands). */
#define F_REX_R       EMU86_F_REX_R       /* The REX.R flag (1-bit extension to MODRM.reg). */
#define F_REX_X       EMU86_F_REX_X       /* The REX.X flag (1-bit extension to SIB.index). */
#define F_REX_B       EMU86_F_REX_B       /* The REX.B flag (1-bit extension to MODRM.rm). */
#define F_SEGDS       EMU86_F_SEGDS       /* DS override (compatibility mode ONLY). */
#define F_SEGES       EMU86_F_SEGES       /* ES override (compatibility mode ONLY). */
#define F_SEGCS       EMU86_F_SEGCS       /* CS override (compatibility mode ONLY). */
#define F_SEGSS       EMU86_F_SEGSS       /* SS override (compatibility mode ONLY). */
#define F_EVEX_z      EMU86_F_EVEX_z      /* Value of EVEX.z */
#define F_EVEX_b      EMU86_F_EVEX_b      /* Value of EVEX.b */
#define F_EVEX_R      EMU86_F_EVEX_R      /* The EVEX.R flag (a second 1-bit extension to MODRM.reg; use with `F_REX_R'). */
#define F_EVEX_aaa_M  EMU86_F_EVEX_aaa_M  /* Value of EVEX.aaa */
#define F_EVEX_aaa_S  EMU86_F_EVEX_aaa_S  /* Shift for EVEX.aaa */
#define F_HASEVEX     EMU86_F_HASEVEX     /* An EVEX prefix was given. */
#else /* __x86_64__ */
#define F_SEGDS       EMU86_F_SEGDS /* DS override. */
#define F_SEGES       EMU86_F_SEGES /* ES override. */
#define F_SEGCS       EMU86_F_SEGCS /* CS override. */
#define F_SEGSS       EMU86_F_SEGSS /* SS override. */
#endif /* !__x86_64__ */
#define F_SEGFS       EMU86_F_SEGFS /* FS override. */
#define F_SEGGS       EMU86_F_SEGGS /* GS override. */

/* Explicit prefix byte flags. */
/* TODO: Get rid of these macros */
#define F_66 EMU86_F_66 /* The 0x66 prefix is being used. */
#define F_67 EMU86_F_67 /* The 0x67 prefix is being used. */
#define F_f0 EMU86_F_f0 /* The 0xf0 prefix is being used. */
#define F_f2 EMU86_F_f2 /* The 0xf2 prefix is being used. */
#define F_f3 EMU86_F_f3 /* The 0xf3 prefix is being used. */


struct icpustate;

/* @param: regno: One of `R_*' */
#ifdef __x86_64__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) u8 NOTHROW(FCALL x86_icpustate_get8)(struct icpustate *__restrict state, u8 regno, op_flag_t flags);
INTDEF NONNULL((1)) void NOTHROW(FCALL x86_icpustate_set8)(struct icpustate *__restrict state, u8 regno, op_flag_t flags, u8 value);
#else /* __x86_64__ */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) u8 NOTHROW(FCALL x86_icpustate_get8)(struct icpustate *__restrict state, u8 regno);
INTDEF NONNULL((1)) void NOTHROW(FCALL x86_icpustate_set8)(struct icpustate *__restrict state, u8 regno, u8 value);
#define x86_icpustate_get8(state, regno, flags)        x86_icpustate_get8(state, regno)
#define x86_icpustate_set8(state, regno, flags, value) x86_icpustate_set8(state, regno, value)
#endif /* !__x86_64__ */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) u16 NOTHROW(FCALL x86_icpustate_get16)(struct icpustate *__restrict state, u8 regno);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) u32 NOTHROW(FCALL x86_icpustate_get32)(struct icpustate *__restrict state, u8 regno);
#ifdef __x86_64__
INTDEF NONNULL((1)) void NOTHROW(FCALL x86_icpustate_set16)(struct icpustate *__restrict state, u8 regno, u16 value);
INTDEF NONNULL((1)) void NOTHROW(FCALL x86_icpustate_set32)(struct icpustate *__restrict state, u8 regno, u32 value);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) u64 NOTHROW(FCALL x86_icpustate_get64)(struct icpustate *__restrict state, u8 regno);
INTDEF NONNULL((1)) void NOTHROW(FCALL x86_icpustate_set64)(struct icpustate *__restrict state, u8 regno, u64 value);
#define x86_icpustate_get(state,regno)       x86_icpustate_get64(state,regno)
#define x86_icpustate_set(state,regno,value) x86_icpustate_set64(state,regno,value)
#else /* __x86_64__ */
INTDEF NONNULL((1)) void FCALL x86_icpustate_set16(struct icpustate *__restrict state, u8 regno, u16 value);
INTDEF NONNULL((1)) void FCALL x86_icpustate_set32(struct icpustate *__restrict state, u8 regno, u32 value);
#define x86_icpustate_get(state, regno)        x86_icpustate_get32(state, regno)
#define x86_icpustate_set(state, regno, value) x86_icpustate_set32(state, regno, value)
#endif /* !__x86_64__ */


INTDEF uintptr_t NOTHROW(KCALL x86_decode_segmentbase)(struct icpustate *__restrict state, op_flag_t flags);
INTDEF uintptr_t NOTHROW(KCALL x86_decode_modrmgetmem)(struct icpustate *__restrict state,
                                                       struct emu86_modrm *__restrict modrm, op_flag_t flags);

/* Access the register or memory location described by a MODRM instruction. */
INTDEF u8  KCALL modrm_getrmb(struct icpustate *__restrict state, struct emu86_modrm *__restrict modrm, op_flag_t flags) THROWS(E_SEGFAULT);
INTDEF u16 KCALL modrm_getrmw(struct icpustate *__restrict state, struct emu86_modrm *__restrict modrm, op_flag_t flags) THROWS(E_SEGFAULT);
INTDEF u32 KCALL modrm_getrml(struct icpustate *__restrict state, struct emu86_modrm *__restrict modrm, op_flag_t flags) THROWS(E_SEGFAULT);
INTDEF void KCALL modrm_setrmb(struct icpustate *__restrict state, struct emu86_modrm *__restrict modrm, op_flag_t flags, u8  value) THROWS(E_SEGFAULT);
INTDEF void KCALL modrm_setrmw(struct icpustate *__restrict state, struct emu86_modrm *__restrict modrm, op_flag_t flags, u16 value) THROWS(E_SEGFAULT);
INTDEF void KCALL modrm_setrml(struct icpustate *__restrict state, struct emu86_modrm *__restrict modrm, op_flag_t flags, u32 value) THROWS(E_SEGFAULT);
#ifdef __x86_64__
INTDEF u64 KCALL modrm_getrmq(struct icpustate *__restrict state, struct emu86_modrm *__restrict modrm, op_flag_t flags) THROWS(E_SEGFAULT);
INTDEF void KCALL modrm_setrmq(struct icpustate *__restrict state, struct emu86_modrm *__restrict modrm, op_flag_t flags, u64 value) THROWS(E_SEGFAULT);
#endif /* __x86_64__ */

#define modrm_getregb(state, modrm, flags)        x86_icpustate_get8(state, (modrm)->mi_reg, flags)
#define modrm_setregb(state, modrm, flags, value) x86_icpustate_set8(state, (modrm)->mi_reg, flags, value)
#define modrm_getregw(state, modrm, flags)        x86_icpustate_get16(state, (modrm)->mi_reg)
#define modrm_setregw(state, modrm, flags, value) x86_icpustate_set16(state, (modrm)->mi_reg, value)
#define modrm_getregl(state, modrm, flags)        x86_icpustate_get32(state, (modrm)->mi_reg)
#define modrm_setregl(state, modrm, flags, value) x86_icpustate_set32(state, (modrm)->mi_reg, value)
#ifdef __x86_64__
#define modrm_getregq(state, modrm, flags)        x86_icpustate_get64(state, (modrm)->mi_reg)
#define modrm_setregq(state, modrm, flags, value) x86_icpustate_set64(state, (modrm)->mi_reg, value)
#define modrm_getreg(state, modrm, flags)         x86_icpustate_get64(state, (modrm)->mi_reg)
#define modrm_setreg(state, modrm, flags, value)  x86_icpustate_set64(state, (modrm)->mi_reg, value)
#else /* __x86_64__ */
#define modrm_getreg(state, modrm, flags)         x86_icpustate_get32(state, (modrm)->mi_reg)
#define modrm_setreg(state, modrm, flags, value)  x86_icpustate_set32(state, (modrm)->mi_reg, value)
#endif /* !__x86_64__ */

#define modrm_getrmregb(state, modrm, flags)        x86_icpustate_get8(state, (modrm)->mi_rm, flags)
#define modrm_setrmregb(state, modrm, flags, value) x86_icpustate_set8(state, (modrm)->mi_rm, flags, value)
#define modrm_getrmregw(state, modrm, flags)        x86_icpustate_get16(state, (modrm)->mi_rm)
#define modrm_setrmregw(state, modrm, flags, value) x86_icpustate_set16(state, (modrm)->mi_rm, value)
#define modrm_getrmregl(state, modrm, flags)        x86_icpustate_get32(state, (modrm)->mi_rm)
#define modrm_setrmregl(state, modrm, flags, value) x86_icpustate_set32(state, (modrm)->mi_rm, value)
#ifdef __x86_64__
#define modrm_getrmregq(state, modrm, flags)        x86_icpustate_get64(state, (modrm)->mi_rm)
#define modrm_setrmregq(state, modrm, flags, value) x86_icpustate_set64(state, (modrm)->mi_rm, value)
#define modrm_getrmreg(state, modrm, flags)         x86_icpustate_get64(state, (modrm)->mi_rm)
#define modrm_setrmreg(state, modrm, flags, value)  x86_icpustate_set64(state, (modrm)->mi_rm, value)
#else /* __x86_64__ */
#define modrm_getrmreg(state, modrm, flags)         x86_icpustate_get32(state, (modrm)->mi_rm)
#define modrm_setrmreg(state, modrm, flags, value)  x86_icpustate_set32(state, (modrm)->mi_rm, value)
#endif /* !__x86_64__ */


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_H */
