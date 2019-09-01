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
#ifdef __INTELLISENSE__
#include "register.c"
#define SET_REGISTER 1
#endif /* __INTELLISENSE__ */

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


PRIVATE NONNULL((2, 4)) size_t
NOTHROW(FCALL FUNC(x86FpuRegister))(uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                    struct task *__restrict thread) {
	if (regno >= GDB_REGISTER_I386_ST0 &&
	    regno <= GDB_REGISTER_I386_MXCSR) {
		struct fpustate *fpu;
		if (thread == THIS_TASK)
			fpustate_save();
		fpu = FORTASK(thread, _this_fpustate);
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
			FORTASK(thread, _this_fpustate) = fpu;
#endif /* ... */
		}
		switch (regno) {

		case GDB_REGISTER_I386_ST0 ... GDB_REGISTER_I386_ST7: {
			void *fpureg;
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				fpureg = &fpu->f_ssave.fs_regs[regno - GDB_REGISTER_I386_ST0];
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				fpureg = &fpu->f_xsave.fs_regs[regno - GDB_REGISTER_I386_ST0];
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
				fpureg = &fpu->f_xsave.fs_xmm[regno - GDB_REGISTER_I386_XMM0];
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
				FIELD4(fpu->f_xsave.fs_fcw);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FSW:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fsw);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fs_fsw);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FTW:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_ftw);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fs_ftw);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FPUCS:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fpucs);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fs_fpucs);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FPUIP:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fpuip);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fs_fpuip);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FPUDS:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fpuds);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fs_fpuds);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FPUDP:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fpudp);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fs_fpudp);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_FOP:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fop);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fs_fop);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_I386_MXCSR:
			if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fs_mxcsr);
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
                                    struct gpregs STATE_CONST *__restrict gpregs_pointer) {
	if (regno >= GDB_REGISTER_I386_EAX &&
	    regno <= GDB_REGISTER_I386_EDI) {
		size_t offset;
		offset = (GDB_REGISTER_I386_EDI - regno) * 4;
		FIELD4(*(u32 *)((byte_t *)gpregs_pointer + offset));
	}
	return 0;
}

#ifdef SET_REGISTER
INTERN WUNUSED ATTR_RETNONNULL NONNULL((1)) struct icpustate *
NOTHROW(FCALL GDB_SetICpustateEsp)(struct icpustate *__restrict state, u32 new_esp) {
	struct icpustate *result = state;
	if (irregs_isuser(&state->ics_irregs))
		state->ics_irregs_u.ir_esp = new_esp;
	else {
		/* Move the entire CPUSTATE to a new location. */
		enum { ICPUSTATE_KERNEL_SIZE = OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL };
		result = (struct icpustate *)(new_esp - ICPUSTATE_KERNEL_SIZE);
		memcpy(result, state, ICPUSTATE_KERNEL_SIZE);
	}
	return result;
}
INTERN WUNUSED ATTR_RETNONNULL NONNULL((1)) struct scpustate *
NOTHROW(FCALL GDB_SetSCpustateEsp)(struct scpustate *__restrict state, u32 new_esp) {
	struct scpustate *result = state;
	if (irregs_isuser(&state->scs_irregs))
		state->scs_irregs_u.ir_esp = new_esp;
	else {
		/* Move the entire CPUSTATE to a new location. */
		enum { SCPUSTATE_KERNEL_SIZE = OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL };
		result = (struct scpustate *)(new_esp - SCPUSTATE_KERNEL_SIZE);
		memcpy(result, state, SCPUSTATE_KERNEL_SIZE);
	}
	return result;
}
#endif /* SET_REGISTER */


/* Arch-specific: Get/Set the value of a given register `regno'
 * @return: 0 : Invalid `regno'. */
INTERN NONNULL((2, 4, 5)) size_t FCALL
NOTHROW(FUNC(ICpuStateRegister))(uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                 struct task *__restrict thread,
                                 struct icpustate STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_I386_ESP:
		GETSET4(irregs_rdsp(&STATE->ics_irregs),
		        *pstate = GDB_SetICpustateEsp(*pstate, value));
		break;

	case GDB_REGISTER_I386_EIP:
		GETSET4(irregs_rdip(&STATE->ics_irregs),
		        irregs_wrip(&STATE->ics_irregs, value));
		break;

	case GDB_REGISTER_I386_EFLAGS:
		GETSET4(irregs_rdflags(&STATE->ics_irregs),
		        irregs_wrflags(&STATE->ics_irregs, value));
		break;

	case GDB_REGISTER_I386_CS:
		GETSET4(irregs_rdcs(&STATE->ics_irregs),
		        irregs_wrcs(&STATE->ics_irregs, value));
		break;

	case GDB_REGISTER_I386_SS:
		if (irregs_isuser(&STATE->ics_irregs)) {
			FIELD4(STATE->ics_irregs_u.ir_ss);
		} else {
			GETSET4(__rdss(), __wrss(value));
		}
		break;

	case GDB_REGISTER_I386_DS:
		FIELD4(*(irregs_isvm86(&STATE->ics_irregs)
		         ? &STATE->ics_irregs_v.ir_ds
		         : &STATE->ics_ds));
		break;

	case GDB_REGISTER_I386_ES:
		FIELD4(*(irregs_isvm86(&STATE->ics_irregs)
		         ? &STATE->ics_irregs_v.ir_es
		         : &STATE->ics_es));
		break;

	case GDB_REGISTER_I386_FS:
		FIELD4(*(irregs_isvm86(&STATE->ics_irregs)
		         ? &STATE->ics_irregs_v.ir_fs
		         : &STATE->ics_fs));
		break;

	case GDB_REGISTER_I386_GS:
		if (irregs_isuser(&STATE->ics_irregs)) {
			FIELD4(STATE->ics_irregs_v.ir_gs);
		} else {
			GETSET4(__rdgs(), __wrgs(value));
		}
		break;

	default: {
		size_t result;
		result = FUNC(GPRegsRegister)(regno, buf, bufsize, &STATE->ics_gpregs);
		if (result == 0)
			result = FUNC(x86FpuRegister)(regno, buf, bufsize, thread);
		return result;
	}	break;
	}
	return 0;
}

INTERN NONNULL((2, 4, 5)) size_t
NOTHROW(FCALL FUNC(SCpuStateRegister))(uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct task *__restrict thread,
                                       struct scpustate STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_I386_ESP:
		GETSET4(irregs_rdsp(&STATE->scs_irregs),
		        *pstate = GDB_SetSCpustateEsp(*pstate, value));
		break;

	case GDB_REGISTER_I386_EIP:
		GETSET4(irregs_rdip(&STATE->scs_irregs),
		        irregs_wrip(&STATE->scs_irregs, value));
		break;

	case GDB_REGISTER_I386_EFLAGS:
		GETSET4(irregs_rdflags(&STATE->scs_irregs),
		        irregs_wrflags(&STATE->scs_irregs, value));
		break;

	case GDB_REGISTER_I386_CS:
		GETSET4(irregs_rdcs(&STATE->scs_irregs),
		        irregs_wrcs(&STATE->scs_irregs, value));
		break;

	case GDB_REGISTER_I386_SS:
		if (irregs_isuser(&STATE->scs_irregs)) {
			FIELD4(STATE->scs_irregs_u.ir_ss);
		} else {
			GETSET4(__rdss(), __wrss(value));
		}
		break;

	case GDB_REGISTER_I386_DS:
		FIELD4(*(irregs_isvm86(&STATE->scs_irregs)
		         ? &STATE->scs_irregs_v.ir_ds
		         : &STATE->scs_sgregs.sg_ds));
		break;

	case GDB_REGISTER_I386_ES:
		FIELD4(*(irregs_isvm86(&STATE->scs_irregs)
		         ? &STATE->scs_irregs_v.ir_es
		         : &STATE->scs_sgregs.sg_es));
		break;

	case GDB_REGISTER_I386_FS:
		FIELD4(*(irregs_isvm86(&STATE->scs_irregs)
		         ? &STATE->scs_irregs_v.ir_fs
		         : &STATE->scs_sgregs.sg_fs));
		break;

	case GDB_REGISTER_I386_GS:
		FIELD4(*(irregs_isvm86(&STATE->scs_irregs)
		         ? &STATE->scs_irregs_v.ir_gs
		         : &STATE->scs_sgregs.sg_gs));
		break;

	default: {
		size_t result;
		result = FUNC(GPRegsRegister)(regno, buf, bufsize, &STATE->scs_gpregs);
		if (result == 0)
			result = FUNC(x86FpuRegister)(regno, buf, bufsize, thread);
		return result;
	}	break;
	}
	return 0;
}

INTERN NONNULL((2, 4, 5)) size_t
NOTHROW(FCALL FUNC(UCpuStateRegister))(uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct task *__restrict thread,
                                       struct ucpustate STATE_PARAM) {
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
			result = FUNC(x86FpuRegister)(regno, buf, bufsize, thread);
		return result;
	}	break;
	}
	return 0;
}


INTERN NONNULL((2)) size_t
NOTHROW(FCALL FUNC(ActiveSegmentRegister))(uintptr_t regno, void BUF_CONST *buf, size_t bufsize) {
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

INTERN NONNULL((2, 4, 5)) size_t
NOTHROW(FCALL FUNC(KCpuStateRegister))(uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct task *__restrict thread,
                                       struct kcpustate STATE_PARAM) {
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
			result = FUNC(x86FpuRegister)(regno, buf, bufsize, thread);
		return result;
	}	break;
	}
	return 0;
}

INTERN NONNULL((2, 4, 5)) size_t
NOTHROW(FCALL FUNC(LCpuStateRegister))(uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct task *__restrict thread,
                                       struct lcpustate STATE_PARAM) {
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
			result = FUNC(x86FpuRegister)(regno, buf, bufsize, thread);
		return result;
	}	break;
	}
	return 0;
}

INTERN NONNULL((2, 4, 5)) size_t
NOTHROW(FCALL FUNC(FCpuStateRegister))(uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct task *__restrict thread,
                                       struct fcpustate STATE_PARAM) {
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
			result = FUNC(x86FpuRegister)(regno, buf, bufsize, thread);
		return result;
	}	break;
	}
	return 0;
}


/* Get/Set the full GDB cpustate. */
INTERN NONNULL((1)) void
NOTHROW(FCALL FUNC(Registers))(struct gdb_cpustate BUF_CONST *buf) {
	uintptr_t regno;
	for (regno = 0; regno <= sizeof(struct gdb_cpustate)/4; ++regno) {
		FUNC(Register)(regno, (u32 *)buf + regno, 4);
	}
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
