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
#ifndef GUARD_LIBREGDUMP_ARCH_I386_CPU_STATE_C
#define GUARD_LIBREGDUMP_ARCH_I386_CPU_STATE_C 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include "../../api.h"
#include "cpu-state.h"
#include "x86.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libregdump/cpu-state.h>

#include <asm/intrin.h>
#include <kos/kernel/gdt.h>
#include <format-printer.h>

#ifdef __KERNEL__
#include <sched/task.h>
#endif /* __KERNEL__ */

#ifndef __KERNEL__
#include <sys/ucontext.h>
#endif /* !__KERNEL__ */

DECL_BEGIN

#define BEGIN      \
	ssize_t temp, result = 0
#define END        \
	return result; \
err:               \
	return temp


#define DO(...)               do{if unlikely((temp = __VA_ARGS__) < 0)goto err;result+=temp;}__WHILE0
#define print(str, len)       DO((*self->rdp_printer)(self->rdp_printer_arg, str, len))
#define printf(...)           DO(format_printf(self->rdp_printer, self->rdp_printer_arg, __VA_ARGS__))
#define PRINT(str)            print(str, COMPILER_STRLEN(str))
#define format(format_option) DO(regdump_printer_format(self, format_option))


#ifdef __x86_64__
#define ucs_Xflags ucs_rflags
#define ucs_Xip    ucs_rip
#define kcs_Xflags kcs_rflags
#define kcs_Xip    kcs_rip
#else /* __x86_64__ */
#define ucs_Xflags ucs_eflags
#define ucs_Xip    ucs_eip
#define kcs_Xflags kcs_eflags
#define kcs_Xip    kcs_eip
#endif /* !__x86_64__ */



/* Dump the contents of the given cpu-state / context. */
INTERN NONNULL((1, 2)) ssize_t CC
libregdump_ucpustate(struct regdump_printer *__restrict self,
                     struct ucpustate const *__restrict data) {
	BEGIN;
	DO(libregdump_gpregs(self, &data->ucs_gpregs));
	DO(libregdump_sgregs_with_cs_ss(self, &data->ucs_sgregs, data->ucs_cs, data->ucs_ss));
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_flags(self, data->ucs_Xflags));
	PRINT("\n");
	DO(libregdump_ip(self, data->ucs_Xip));
	END;
}

INTERN NONNULL((1, 2)) ssize_t CC
libregdump_lcpustate(struct regdump_printer *__restrict self,
                     struct lcpustate const *__restrict data) {
	BEGIN;
	format(REGDUMP_FORMAT_INDENT);
#ifdef __x86_64__
	DO(libregdump_gpreg(self, REGDUMP_GPREG_RBX, data->lcs_rbx));
	PRINT(" ");
	DO(libregdump_gpreg(self, REGDUMP_GPREG_RSP, data->lcs_rsp));
	PRINT(" ");
	DO(libregdump_gpreg(self, REGDUMP_GPREG_RBP, data->lcs_rbp));
	PRINT(" ");
	DO(libregdump_gpreg(self, REGDUMP_GPREG_R12, data->lcs_r12));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_gpreg(self, REGDUMP_GPREG_R13, data->lcs_r13));
	PRINT(" ");
	DO(libregdump_gpreg(self, REGDUMP_GPREG_R14, data->lcs_r14));
	PRINT(" ");
	DO(libregdump_gpreg(self, REGDUMP_GPREG_R15, data->lcs_r15));
	PRINT("\n");
	DO(libregdump_ip(self, data->lcs_rip));
#else
	DO(libregdump_gpreg(self, REGDUMP_GPREG_EDI, data->lcs_edi));
	PRINT(" ");
	DO(libregdump_gpreg(self, REGDUMP_GPREG_ESI, data->lcs_esi));
	PRINT(" ");
	DO(libregdump_gpreg(self, REGDUMP_GPREG_EBP, data->lcs_ebp));
	PRINT(" ");
	DO(libregdump_gpreg(self, REGDUMP_GPREG_ESP, data->lcs_esp));
	PRINT("\n");
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_gpreg(self, REGDUMP_GPREG_EBX, data->lcs_ebx));
	PRINT("\n");
	DO(libregdump_ip(self, data->lcs_eip));
#endif
	END;
}

INTERN NONNULL((1, 2)) ssize_t CC
libregdump_kcpustate(struct regdump_printer *__restrict self,
                     struct kcpustate const *__restrict data) {
	BEGIN;
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_gpregs(self, &data->kcs_gpregs));
	format(REGDUMP_FORMAT_INDENT);
	DO(libregdump_flags(self, data->kcs_Xflags));
	PRINT("\n");
	DO(libregdump_ip(self, data->kcs_Xip));
	END;
}

#if defined(__KERNEL__) || defined(__INTELLISENSE__)
INTERN NONNULL((1, 2)) ssize_t CC
libregdump_icpustate(struct regdump_printer *__restrict self,
                     struct icpustate const *__restrict data) {
	struct sgregs sg;
	BEGIN;
	DO(libregdump_gpregs_with_sp(self,
	                             &data->ics_gpregs,
	                             ICPUSTATE_SP(*data)));
#ifdef __KERNEL__
	DO(libregdump_ip(self, irregs_rdip(&data->ics_irregs)));
#else /* __KERNEL__ */
	DO(libregdump_ip(self, ICPUSTATE_PC(*data)));
#endif /* !__KERNEL__ */
#ifdef __x86_64__
	sg.sg_gs = __rdgs();
	sg.sg_fs = __rdfs();
	sg.sg_es = __rdes();
	sg.sg_ds = __rdds();
#else /* __x86_64__ */
	sg.sg_gs = ICPUSTATE_GS(*data);
	sg.sg_fs = ICPUSTATE_FS(*data);
	sg.sg_es = ICPUSTATE_ES(*data);
	sg.sg_ds = ICPUSTATE_DS(*data);
#endif /* !__x86_64__ */
#ifdef __x86_64__
#ifdef __KERNEL__
	DO(libregdump_sgregs_with_cs_ss(self, &sg,
	                                irregs_rdcs(&data->ics_irregs),
	                                irregs_rdss(&data->ics_irregs)));
#else /* __KERNEL__ */
	DO(libregdump_sgregs_with_cs_ss(self, &sg,
	                                data->ics_irregs.ir_cs,
	                                data->ics_irregs.ir_ss));
#endif /* !__KERNEL__ */
#else /* __x86_64__ */
#ifdef __KERNEL__
	DO(libregdump_sgregs_with_cs_ss(self, &sg,
	                                irregs_rdcs(&data->ics_irregs_k),
	                                ICPUSTATE_SS(*data)));
#else /* __KERNEL__ */
	DO(libregdump_sgregs_with_cs_ss(self, &sg,
	                                data->ics_irregs_k.ir_cs,
	                                ICPUSTATE_SS(*data)));
#endif /* !__KERNEL__ */
#endif /* !__x86_64__ */
	format(REGDUMP_FORMAT_INDENT);
#ifdef __KERNEL__
	DO(libregdump_flags(self, irregs_rdflags(&data->ics_irregs)));
#elif defined(__x86_64__)
	DO(libregdump_flags(self, data->ics_irregs.ir_rflags));
#else /* __x86_64__ */
	DO(libregdump_flags(self, data->ics_irregs.ir_eflags));
#endif /* !__x86_64__ */
	PRINT("\n");
	END;
}

INTERN NONNULL((1, 2)) ssize_t CC
libregdump_scpustate(struct regdump_printer *__restrict self,
                     struct scpustate const *__restrict data) {
#ifndef __x86_64__
	struct sgregs sg;
#endif /* !__x86_64__ */
	BEGIN;
	DO(libregdump_gpregs_with_sp(self, &data->scs_gpregs, SCPUSTATE_SP(*data)));
	DO(libregdump_ip(self, SCPUSTATE_PC(*data)));
#ifdef __x86_64__
	/* TODO: SGBASE */
	DO(libregdump_sgregs_with_cs_ss(self, &data->scs_sgregs,
	                                data->scs_irregs.ir_cs,
	                                data->scs_irregs.ir_ss));
#else /* __x86_64__ */
	sg.sg_gs = SCPUSTATE_GS(*data);
	sg.sg_fs = SCPUSTATE_FS(*data);
	sg.sg_es = SCPUSTATE_ES(*data);
	sg.sg_ds = SCPUSTATE_DS(*data);
	DO(libregdump_sgregs_with_cs_ss(self, &sg,
	                                data->scs_irregs_k.ir_cs,
	                                SCPUSTATE_SS(*data)));
#endif /* !__x86_64__ */
	format(REGDUMP_FORMAT_INDENT);
#ifdef __x86_64__
	DO(libregdump_flags(self, data->scs_irregs.ir_rflags));
#else /* __x86_64__ */
	DO(libregdump_flags(self, data->scs_irregs_k.ir_eflags));
#endif /* !__x86_64__ */
	PRINT("\n");
	END;
}
#endif /* __KERNEL__ */

INTERN NONNULL((1, 2)) ssize_t CC
libregdump_fcpustate(struct regdump_printer *__restrict self,
                     struct fcpustate const *__restrict data) {
	struct sgregs sg;
	BEGIN;
	DO(libregdump_gpregs(self, &data->fcs_gpregs));
	DO(libregdump_ip(self, FCPUSTATE_PC(*data)));
	sg.sg_gs = data->fcs_sgregs.sg_gs;
	sg.sg_fs = data->fcs_sgregs.sg_fs;
	sg.sg_es = data->fcs_sgregs.sg_es;
	sg.sg_ds = data->fcs_sgregs.sg_ds;
	DO(libregdump_sgregs_with_cs_ss_tr_ldt(self, &sg,
	                                       data->fcs_sgregs.sg_cs,
	                                       data->fcs_sgregs.sg_ss,
	                                       data->fcs_sgregs.sg_tr,
	                                       data->fcs_sgregs.sg_ldt));
	format(REGDUMP_FORMAT_INDENT);
#ifdef __x86_64__
	/* TODO: SGBASE */
	DO(libregdump_flags(self, data->fcs_rflags));
#else /* __x86_64__ */
	DO(libregdump_flags(self, data->fcs_eflags));
#endif /* !__x86_64__ */
	PRINT("\n");
	DO(libregdump_coregs(self, &data->fcs_coregs));
	DO(libregdump_drregs(self, &data->fcs_drregs));
	DO(libregdump_gdt(self, &data->fcs_gdt));
	DO(libregdump_idt(self, &data->fcs_idt));
	END;
}

#ifndef __KERNEL__
INTERN NONNULL((1, 2)) ssize_t CC
libregdump_ucontext(struct regdump_printer *__restrict self,
                    struct ucontext const *__restrict data) {
	/* XXX: Dump the sigmask? */
	/* XXX: Dump the stack? */
	return libregdump_mcontext(self, &data->uc_mcontext);
}

INTERN NONNULL((1, 2)) ssize_t CC
libregdump_mcontext(struct regdump_printer *__restrict self,
                    struct mcontext const *__restrict data) {
	/* XXX: Dump the FPU state? */
	/* XXX: Dump cr2? */
	return libregdump_ucpustate(self, &data->mc_context);
}
#endif /* !__KERNEL__ */


/* TODO: Add support for dumping fs/gs-base registers. */
/* TODO: Dump functions for FPU registers */



DEFINE_PUBLIC_ALIAS(regdump_ucpustate, libregdump_ucpustate);
DEFINE_PUBLIC_ALIAS(regdump_lcpustate, libregdump_lcpustate);
DEFINE_PUBLIC_ALIAS(regdump_kcpustate, libregdump_kcpustate);
DEFINE_PUBLIC_ALIAS(regdump_fcpustate, libregdump_fcpustate);

#ifdef __KERNEL__
DEFINE_PUBLIC_ALIAS(regdump_icpustate, libregdump_icpustate);
DEFINE_PUBLIC_ALIAS(regdump_scpustate, libregdump_scpustate);
#endif /* __KERNEL__ */

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(regdump_ucontext, libregdump_ucontext);
DEFINE_PUBLIC_ALIAS(regdump_mcontext, libregdump_mcontext);
#endif /* !__KERNEL__ */


DECL_END

#endif /* !GUARD_LIBREGDUMP_ARCH_I386_CPU_STATE_C */
