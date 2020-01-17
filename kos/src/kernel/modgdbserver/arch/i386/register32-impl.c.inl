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
#ifdef __INTELLISENSE__
#include "register.c"
#define SET_REGISTER 1
#endif /* __INTELLISENSE__ */

#include <kos/kernel/cpu-state-helpers32.h>
#include <kos/kernel/cpu-state32.h>
#include <kos/kernel/fpu-state32.h>
#include <kos/kernel/gdb-cpu-state32.h>

#if (defined(GET_REGISTER) + defined(SET_REGISTER)) != 1
#error "Must either defined GET_REGISTER or SET_REGISTER"
#endif


DECL_BEGIN

#ifdef GET_REGISTER
#define FUNC(x) GDB_Get##x
#define FIELD4(field)                                \
	do {                                             \
		if (bufsize >= 4)                            \
			UNALIGNED_SET32((u32 *)buf, (u32)field); \
		return 4;                                    \
	} __WHILE0
#define GETSET4(get, set)                       \
	do {                                        \
		if (bufsize >= 4) {                     \
			u32 value;                          \
			value = get;                        \
			UNALIGNED_SET32((u32 *)buf, value); \
		}                                       \
		return 4;                               \
	} __WHILE0
#define GETSET4_NOOP()                      \
	do {                                    \
		if (bufsize >= 4) {                 \
			UNALIGNED_SET32((u32 *)buf, 0); \
		}                                   \
		return 4;                           \
	} __WHILE0
#define STATE       state
#define STATE_PARAM const *__restrict state
#define STATE_CONST const
#define BUF_CONST   /* nothing */
#elif defined(SET_REGISTER)
#define FUNC(x)       GDB_Set##x
#define FIELD4(field)                                               \
	do {                                                            \
		if (bufsize == 4)                                           \
			field = (__typeof__(field))UNALIGNED_GET32((u32 *)buf); \
		return 4;                                                   \
	} __WHILE0
#define GETSET4(get, set)                        \
	do {                                         \
		if (bufsize == 4) {                      \
			u32 value;                           \
			value = UNALIGNED_GET32((u32 *)buf); \
			set;                                 \
		}                                        \
		return 4;                                \
	} __WHILE0
#define GETSET4_NOOP()                           \
	do {                                         \
		return 4;                                \
	} __WHILE0
#define STATE       (*pstate)
#define STATE_PARAM **__restrict pstate
#define STATE_CONST /* nothing */
#define BUF_CONST   const
#endif


PRIVATE NONNULL((1, 3)) size_t
NOTHROW(FCALL FUNC(x86FpuRegister))(struct task *__restrict thread, uintptr_t regno,
                                    void BUF_CONST *buf, size_t bufsize) {
	if (regno >= GDB_REGISTER_I386_ST0 &&
	    regno <= GDB_REGISTER_I386_MXCSR) {
		struct fpustate32 *fpu;
		if (thread == THIS_TASK)
			fpustate_save();
		fpu = FORTASK(thread, this_x86_fpustate);
		if (!fpu) {
#ifdef GET_REGISTER
			size_t result;
			if (regno >= GDB_REGISTER_I386_ST0 &&
			    regno <= GDB_REGISTER_I386_ST7) {
				result = 10;
			} else if (regno >= GDB_REGISTER_I386_XMM0 &&
			           regno <= GDB_REGISTER_I386_XMM7) {
				result = 16;
			} else {
				result = 4;
			}
			if (bufsize >= result)
				memset(buf, 0, result);
			return result;
#elif defined(SET_REGISTER)
			fpu = fpustate_alloc_nx();
			if unlikely(!fpu)
				return 0;
			FORTASK(thread, this_x86_fpustate) = fpu;
#endif /* ... */
		}
		switch (regno) {

		case GDB_REGISTER_I386_ST0 ... GDB_REGISTER_I386_ST7: {
			void *fpureg;
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				fpureg = &fpu->f_ssave.fs_regs[regno - GDB_REGISTER_I386_ST0];
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				fpureg = &fpu->f_xsave.fx_regs[regno - GDB_REGISTER_I386_ST0];
#ifdef SET_REGISTER
				if (bufsize == 10)
					memset((byte_t *)fpureg + 10, 0, 6);
#endif /* SET_REGISTER */
			} else {
#ifdef GET_REGISTER
				if (bufsize >= 10)
					memset(buf, 0, 10);
#endif /* GET_REGISTER */
				return 10;
			}
#ifdef GET_REGISTER
			if (bufsize >= 10)
				memcpy(buf, fpureg, 10);
#elif defined(SET_REGISTER)
			if (bufsize == 10)
				memcpy(fpureg, buf, 10);
#endif /* ... */
			return 10;
		}	break;

		case GDB_REGISTER_I386_XMM0 ... GDB_REGISTER_I386_XMM7: {
			if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				void *fpureg;
				fpureg = &fpu->f_xsave.fx_xmm[regno - GDB_REGISTER_I386_XMM0];
#ifdef GET_REGISTER
				if (bufsize >= 16)
					memcpy(buf, fpureg, 16);
#elif defined(SET_REGISTER)
				if (bufsize == 16)
					memcpy(fpureg, buf, 16);
#endif /* ... */
			} else {
#ifdef GET_REGISTER
				if (bufsize >= 16)
					memset(buf, 0, 16);
#endif /* GET_REGISTER */
			}
			return 16;
		}	break;

		case GDB_REGISTER_I386_FCW:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fcw);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_fcw);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FSW:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fsw);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_fsw);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FTW:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_ftw);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_ftw);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FCS:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fcs);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_fcs);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FIP:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fip);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_fip);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FDS:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fds);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_fds);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FDP:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fdp);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_fdp);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FOP:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fop);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_fop);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_MXCSR:
			if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_mxcsr);
			} else {
				GETSET4_NOOP();
			}
			break;

		default:
			break;
		}
	}
	return 0;
}

PRIVATE NONNULL((2, 4)) size_t
NOTHROW(FCALL FUNC(GPRegsRegister))(uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                    struct gpregs32 STATE_CONST *__restrict gpregs_pointer) {
	if (regno >= GDB_REGISTER_I386_EAX &&
	    regno <= GDB_REGISTER_I386_EDI) {
		size_t offset;
		offset = (GDB_REGISTER_I386_EDI - regno) * 4;
		FIELD4(*(u32 *)((byte_t *)gpregs_pointer + offset));
	}
	return 0;
}

/* Arch-specific: Get/Set the value of a given register `regno'
 * @return: 0 : Invalid `regno'. */
INTERN NONNULL((1, 3, 5)) size_t FCALL
NOTHROW(FUNC(ICpuStateRegister))(struct task *__restrict thread,
                                 uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                 struct icpustate32 STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_I386_ESP:
		GETSET4(icpustate32_getesp(STATE),
		        *pstate = icpustate32_setesp_p(*pstate, value));
		break;

	case GDB_REGISTER_I386_EIP:
		GETSET4(icpustate32_geteip(STATE),
		        icpustate32_seteip(STATE, value));
		break;

	case GDB_REGISTER_I386_EFLAGS:
		GETSET4(icpustate32_geteflags(STATE),
		        icpustate32_seteflags(STATE, value));
		break;

	case GDB_REGISTER_I386_CS:
		GETSET4(icpustate32_getcs(STATE),
		        icpustate32_setcs(STATE, value));
		break;

	case GDB_REGISTER_I386_SS:
		if (icpustate32_isuser(STATE)) {
			FIELD4(STATE->ics_irregs_u.ir_ss);
		} else {
			GETSET4(__rdss(), __wrss(value));
		}
		break;

	case GDB_REGISTER_I386_DS:
		GETSET4(icpustate32_getds(STATE),
		        icpustate32_setds(STATE, value));
		break;

	case GDB_REGISTER_I386_ES:
		GETSET4(icpustate32_getes(STATE),
		        icpustate32_setes(STATE, value));
		break;

	case GDB_REGISTER_I386_FS:
		GETSET4(icpustate32_getfs(STATE),
		        icpustate32_setfs(STATE, value));
		break;

	case GDB_REGISTER_I386_GS:
		GETSET4(icpustate32_getgs(STATE),
		        icpustate32_setgs(STATE, value));
		break;

	default: {
		size_t result;
		result = FUNC(GPRegsRegister)(regno, buf, bufsize, &STATE->ics_gpregs);
		if (result == 0)
			result = FUNC(x86FpuRegister)(thread, regno, buf, bufsize);
		return result;
	}	break;
	}
	return 0;
}

INTERN NONNULL((1, 3, 5)) size_t
NOTHROW(FCALL FUNC(SCpuStateRegister))(struct task *__restrict thread,
                                       uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct scpustate32 STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_I386_ESP:
		GETSET4(scpustate32_getesp(STATE),
		        *pstate = scpustate32_setesp_p(*pstate, value));
		break;

	case GDB_REGISTER_I386_EIP:
		GETSET4(scpustate32_geteip(STATE),
		        scpustate32_seteip(STATE, value));
		break;

	case GDB_REGISTER_I386_EFLAGS:
		GETSET4(scpustate32_geteflags(STATE),
		        scpustate32_seteflags(STATE, value));
		break;

	case GDB_REGISTER_I386_CS:
		GETSET4(scpustate32_getcs(STATE),
		        scpustate32_setcs(STATE, value));
		break;

	case GDB_REGISTER_I386_SS:
		if (scpustate32_isuser(STATE)) {
			FIELD4(STATE->scs_irregs_u.ir_ss);
		} else {
			GETSET4(__rdss(), __wrss(value));
		}
		break;

	case GDB_REGISTER_I386_DS:
		GETSET4(scpustate32_getds(STATE),
		        scpustate32_setds(STATE, value));
		break;

	case GDB_REGISTER_I386_ES:
		GETSET4(scpustate32_getes(STATE),
		        scpustate32_setes(STATE, value));
		break;

	case GDB_REGISTER_I386_FS:
		GETSET4(scpustate32_getfs(STATE),
		        scpustate32_setfs(STATE, value));
		break;

	case GDB_REGISTER_I386_GS:
		GETSET4(scpustate32_getgs(STATE),
		        scpustate32_setgs(STATE, value));
		break;

	default: {
		size_t result;
		result = FUNC(GPRegsRegister)(regno, buf, bufsize, &STATE->scs_gpregs);
		if (result == 0)
			result = FUNC(x86FpuRegister)(thread, regno, buf, bufsize);
		return result;
	}	break;
	}
	return 0;
}

INTERN NONNULL((1, 3, 5)) size_t
NOTHROW(FCALL FUNC(UCpuStateRegister))(struct task *__restrict thread,
                                       uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct ucpustate32 STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_I386_EIP:
		FIELD4(STATE->ucs_eip);
		break;

	case GDB_REGISTER_I386_EFLAGS:
		FIELD4(STATE->ucs_eflags);
		break;

	case GDB_REGISTER_I386_CS:
		FIELD4(STATE->ucs_cs);
		break;

	case GDB_REGISTER_I386_SS:
		FIELD4(STATE->ucs_ss);
		break;

	case GDB_REGISTER_I386_DS:
		FIELD4(STATE->ucs_sgregs.sg_ds);
		break;

	case GDB_REGISTER_I386_ES:
		FIELD4(STATE->ucs_sgregs.sg_es);
		break;

	case GDB_REGISTER_I386_FS:
		FIELD4(STATE->ucs_sgregs.sg_fs);
		break;

	case GDB_REGISTER_I386_GS:
		FIELD4(STATE->ucs_sgregs.sg_gs);
		break;

	default: {
		size_t result;
		result = FUNC(GPRegsRegister)(regno, buf, bufsize, &STATE->ucs_gpregs);
		if (result == 0)
			result = FUNC(x86FpuRegister)(thread, regno, buf, bufsize);
		return result;
	}	break;
	}
	return 0;
}


INTERN NONNULL((2)) size_t
NOTHROW(FCALL FUNC(ActiveSegmentRegister))(uintptr_t regno,
                                           void BUF_CONST *buf,
                                           size_t bufsize) {
	switch (regno) {

	case GDB_REGISTER_I386_CS:
		GETSET4(__rdcs(), __wrcs(value));
		break;

	case GDB_REGISTER_I386_SS:
		GETSET4(__rdss(), __wrss(value));
		break;

	case GDB_REGISTER_I386_DS:
		GETSET4(__rdds(), __wrds(value));
		break;

	case GDB_REGISTER_I386_ES:
		GETSET4(__rdes(), __wres(value));
		break;

	case GDB_REGISTER_I386_FS:
		GETSET4(__rdfs(), __wrfs(value));
		break;

	case GDB_REGISTER_I386_GS:
		GETSET4(__rdgs(), __wrgs(value));
		break;

	default:
		break;
	}
	return 0;
}

INTERN NONNULL((1, 3, 5)) size_t
NOTHROW(FCALL FUNC(KCpuStateRegister))(struct task *__restrict thread,
                                       uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct kcpustate32 STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_I386_EIP:
		FIELD4(STATE->kcs_eip);
		break;

	case GDB_REGISTER_I386_EFLAGS:
		FIELD4(STATE->kcs_eflags);
		break;

	default: {
		size_t result;
		result = FUNC(GPRegsRegister)(regno, buf, bufsize, &STATE->kcs_gpregs);
		if (result == 0)
			result = FUNC(ActiveSegmentRegister)(regno, buf, bufsize);
		if (result == 0)
			result = FUNC(x86FpuRegister)(thread, regno, buf, bufsize);
		return result;
	}	break;
	}
	return 0;
}

INTERN NONNULL((1, 3, 5)) size_t
NOTHROW(FCALL FUNC(LCpuStateRegister))(struct task *__restrict thread,
                                       uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct lcpustate32 STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_I386_EDI:
		FIELD4(STATE->lcs_edi);
		break;

	case GDB_REGISTER_I386_ESI:
		FIELD4(STATE->lcs_esi);
		break;

	case GDB_REGISTER_I386_EBP:
		FIELD4(STATE->lcs_ebp);
		break;

	case GDB_REGISTER_I386_ESP:
		FIELD4(STATE->lcs_esp);
		break;

	case GDB_REGISTER_I386_EBX:
		FIELD4(STATE->lcs_ebx);
		break;

	case GDB_REGISTER_I386_EIP:
		FIELD4(STATE->lcs_eip);
		break;

	case GDB_REGISTER_I386_EFLAGS:
		GETSET4_NOOP();
		break;

	default: {
		size_t result;
		if (regno >= GDB_REGISTER_I386_EAX &&
		    regno <= GDB_REGISTER_I386_EDI)
			GETSET4_NOOP();
		result = FUNC(ActiveSegmentRegister)(regno, buf, bufsize);
		if (result == 0)
			result = FUNC(x86FpuRegister)(thread, regno, buf, bufsize);
		return result;
	}	break;
	}
	return 0;
}

INTERN NONNULL((1, 3, 5)) size_t
NOTHROW(FCALL FUNC(FCpuStateRegister))(struct task *__restrict thread,
                                       uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct fcpustate32 STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_I386_EIP:
		FIELD4(STATE->fcs_eip);
		break;

	case GDB_REGISTER_I386_EFLAGS:
		FIELD4(STATE->fcs_eflags);
		break;

	case GDB_REGISTER_I386_CS:
		FIELD4(STATE->fcs_sgregs.sg_cs);
		break;

	case GDB_REGISTER_I386_SS:
		FIELD4(STATE->fcs_sgregs.sg_ss);
		break;

	case GDB_REGISTER_I386_DS:
		FIELD4(STATE->fcs_sgregs.sg_ds);
		break;

	case GDB_REGISTER_I386_ES:
		FIELD4(STATE->fcs_sgregs.sg_es);
		break;

	case GDB_REGISTER_I386_FS:
		FIELD4(STATE->fcs_sgregs.sg_fs);
		break;

	case GDB_REGISTER_I386_GS:
		FIELD4(STATE->fcs_sgregs.sg_gs);
		break;

	default: {
		size_t result;
		result = FUNC(GPRegsRegister)(regno, buf, bufsize, &STATE->fcs_gpregs);
		if (result == 0)
			result = FUNC(x86FpuRegister)(thread, regno, buf, bufsize);
		return result;
	}	break;
	}
	return 0;
}


/* Get/Set the full GDB cpustate. */
INTERN NONNULL((1, 2)) bool
NOTHROW(FCALL FUNC(Registers))(struct task *__restrict thread,
                               struct gdb_cpustate32 BUF_CONST *buf) {
	uintptr_t regno;
	for (regno = 0; regno <= sizeof(struct gdb_cpustate32) / 4; ++regno) {
		if (!FUNC(Register)(thread, regno, (u32 *)buf + regno, 4))
			return false;
	}
	return true;
}


DECL_END

#undef FUNC
#undef SET_REGISTER
#undef GET_REGISTER
#undef FIELD4
#undef GETSET4
#undef GETSET4_NOOP
#undef BUF_CONST
#undef STATE
#undef STATE_PARAM
#undef STATE_CONST
