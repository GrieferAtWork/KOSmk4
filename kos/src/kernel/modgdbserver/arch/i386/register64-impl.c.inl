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
#ifdef __INTELLISENSE__
#include "register-impl.c.inl"
#endif /* __INTELLISENSE__ */

#include <kos/kernel/bits/cpu-state-helpers64.h>
#include <kos/kernel/bits/cpu-state64.h>
#include <kos/kernel/bits/fpu-state64.h>
#include <kos/kernel/bits/gdb-cpu-state64.h>

#include <inttypes.h>
#include <stddef.h>

DECL_BEGIN

PRIVATE NONNULL((1, 3)) size_t
NOTHROW(FCALL FUNC(ThreadRegister))(struct task *__restrict thread, uintptr_t regno,
                                    void BUF_CONST *buf, size_t bufsize) {
	if (regno >= GDB_REGISTER_X86_64_ST0 &&
	    regno <= GDB_REGISTER_X86_64_MXCSR) {
		struct fpustate64 *fpu;
		if (thread == GDBServer_Host)
			fpustate_save();
		fpu = FORTASK(thread, this_fpustate);
		if (!fpu) {
#ifdef GET_REGISTER
			size_t result;
			if (regno >= GDB_REGISTER_X86_64_ST0 &&
			    regno <= GDB_REGISTER_X86_64_ST7) {
				result = 10;
			} else if (regno >= GDB_REGISTER_X86_64_XMM0 &&
			           regno <= GDB_REGISTER_X86_64_XMM15) {
				result = 16;
			} else {
				result = 4;
			}
			if (bufsize >= result)
				bzero(buf, result);
			return result;
#elif defined(SET_REGISTER)
			fpu = fpustate_alloc_nx();
			if unlikely(!fpu)
				return 0;
			FORTASK(thread, this_fpustate) = fpu;
#endif /* ... */
		}
		switch (regno) {

		case GDB_REGISTER_X86_64_ST0 ... GDB_REGISTER_X86_64_ST7: {
			void *fpureg;
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				fpureg = &fpu->f_ssave.fs_regs[regno - GDB_REGISTER_X86_64_ST0];
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				fpureg = &fpu->f_xsave.fx_regs[regno - GDB_REGISTER_X86_64_ST0];
#ifdef SET_REGISTER
				if (bufsize == 10)
					bzero((byte_t *)fpureg + 10, 6);
#endif /* SET_REGISTER */
			} else {
#ifdef GET_REGISTER
				if (bufsize >= 10)
					bzero(buf, 10);
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

		case GDB_REGISTER_X86_64_XMM0 ... GDB_REGISTER_X86_64_XMM15: {
			if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				void *fpureg;
				fpureg = &fpu->f_xsave.fx_xmm[regno - GDB_REGISTER_X86_64_XMM0];
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
					bzero(buf, 16);
#endif /* GET_REGISTER */
			}
			return 16;
		}	break;

		case GDB_REGISTER_X86_64_FCW:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fcw);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_fcw);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_X86_64_FSW:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fsw);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_fsw);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_X86_64_FTW:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_ftw);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_ftw);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_X86_64_FCS:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fcs);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_X86_64_FIP:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fip);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_fip);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_X86_64_FDS:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fds);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_X86_64_FDP:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fdp);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_fdp);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_X86_64_FOP:
			if (x86_fpustate_variant == FPU_STATE_SSTATE) {
				FIELD4(fpu->f_ssave.fs_fop);
			} else if (x86_fpustate_variant == FPU_STATE_XSTATE) {
				FIELD4(fpu->f_xsave.fx_fop);
			} else {
				GETSET4_NOOP();
			}
			break;

		case GDB_REGISTER_X86_64_MXCSR:
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
	switch (regno) {

	case GDB_REGISTER_X86_64_CS:
		if (thread != GDBServer_Host) {
			/* TODO */
		}
		GETSET4(GDBThread_IsKernelThread(thread)
		        ? SEGMENT_KERNEL_CODE
		        : SEGMENT_USER_CODE64_RPL,
		        if (value != (GDBThread_IsKernelThread(thread)
		                      ? SEGMENT_KERNEL_CODE
		                      : SEGMENT_USER_CODE64_RPL)) return 0;);
		break;

	case GDB_REGISTER_X86_64_SS:
		if (thread != GDBServer_Host) {
			/* TODO */
		}
		GETSET4(GDBThread_IsKernelThread(thread)
		        ? SEGMENT_KERNEL_DATA
		        : SEGMENT_USER_DATA64_RPL,
		        if (value != (GDBThread_IsKernelThread(thread)
		                      ? SEGMENT_KERNEL_DATA
		                      : SEGMENT_USER_DATA64_RPL)) return 0;);
		break;

	case GDB_REGISTER_X86_64_DS:
		if (thread != GDBServer_Host) {
			/* TODO */
		}
		GETSET4(SEGMENT_USER_DATA64_RPL,
		        if (value != SEGMENT_USER_DATA64_RPL) return 0;);
		break;

	case GDB_REGISTER_X86_64_ES:
		if (thread != GDBServer_Host) {
			/* TODO */
		}
		GETSET4(SEGMENT_USER_DATA64_RPL,
		        if (value != SEGMENT_USER_DATA64_RPL) return 0;);
		break;

	case GDB_REGISTER_X86_64_FS:
		if (thread != GDBServer_Host) {
			/* TODO */
		}
		GETSET4(SEGMENT_USER_DATA64_RPL,
		        if (value != SEGMENT_USER_DATA64_RPL) return 0;);
		break;

	case GDB_REGISTER_X86_64_GS:
		if (thread != GDBServer_Host) {
			/* TODO */
		}
		GETSET4(SEGMENT_USER_DATA64_RPL,
		        if (value != SEGMENT_USER_DATA64_RPL) return 0;);
		break;

	default:
		break;
	}
	return 0;
}

PRIVATE NONNULL((2, 4)) size_t
NOTHROW(FCALL FUNC(GPRegsRegister))(uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                    struct gpregs64 STATE_CONST *__restrict gpregs_pointer) {
	if (regno >= GDB_REGISTER_X86_64_RAX &&
	    regno <= GDB_REGISTER_X86_64_R15) {
		size_t offset;
		offset = (GDB_REGISTER_X86_64_R15 - regno) * 8;
		FIELD8(*(u64 *)((byte_t *)gpregs_pointer + offset));
	}
	return 0;
}

PRIVATE NONNULL((2, 4)) size_t
NOTHROW(FCALL FUNC(GPRegsNspRegister))(uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct gpregsnsp64 STATE_CONST *__restrict gpregs_pointer) {
	if (regno >= GDB_REGISTER_X86_64_RAX &&
	    regno <= GDB_REGISTER_X86_64_R15 &&
	    regno != GDB_REGISTER_X86_64_RSP) {
		PRIVATE ptrdiff_t const offset_table[16] = {
			/* [GDB_REGISTER_X86_64_RAX - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_rax),
			/* [GDB_REGISTER_X86_64_RBX - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_rbx),
			/* [GDB_REGISTER_X86_64_RCX - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_rcx),
			/* [GDB_REGISTER_X86_64_RDX - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_rdx),
			/* [GDB_REGISTER_X86_64_RSI - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_rsi),
			/* [GDB_REGISTER_X86_64_RDI - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_rdi),
			/* [GDB_REGISTER_X86_64_RBP - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_rbp),
			/* [GDB_REGISTER_X86_64_RSP - GDB_REGISTER_X86_64_RAX] = */ 0,
			/* [GDB_REGISTER_X86_64_R8  - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_r8 ),
			/* [GDB_REGISTER_X86_64_R9  - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_r9 ),
			/* [GDB_REGISTER_X86_64_R10 - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_r10),
			/* [GDB_REGISTER_X86_64_R11 - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_r11),
			/* [GDB_REGISTER_X86_64_R12 - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_r12),
			/* [GDB_REGISTER_X86_64_R13 - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_r13),
			/* [GDB_REGISTER_X86_64_R14 - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_r14),
			/* [GDB_REGISTER_X86_64_R15 - GDB_REGISTER_X86_64_RAX] = */ offsetof(struct gpregsnsp64, gp_r15),
		};
		size_t offset;
		offset = offset_table[regno - GDB_REGISTER_X86_64_RAX];
		FIELD8(*(u64 *)((byte_t *)gpregs_pointer + offset));
	}
	return 0;
}

PRIVATE NONNULL((2, 4)) size_t
NOTHROW(FCALL FUNC(SGBaseRegister))(uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                    struct sgbase64 STATE_CONST *__restrict sgbase) {
	if (regno == GDB_REGISTER_X86_64_FSBASE ||
	    regno == GDB_REGISTER_X86_64_GSBASE) {
		FIELD8(*(regno == GDB_REGISTER_X86_64_FSBASE ? &sgbase->sg_fsbase
		                                             : &sgbase->sg_gsbase));
	}
	return 0;
}

/* Arch-specific: Get/Set the value of a given register `regno'
 * @return: 0 : Invalid `regno'. */
INTERN NONNULL((1, 3, 5)) size_t FCALL
NOTHROW(FUNC(ICpuStateRegister))(struct task *__restrict thread,
                                 uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                 struct icpustate64 STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_X86_64_RSP:
		if (thread == GDBServer_Host) {
			GETSET8(icpustate64_getrsp(STATE),
			        icpustate64_setrsp(STATE, value));
		} else {
			FIELD8(STATE->ics_irregs.ir_rsp);
		}
		break;

	case GDB_REGISTER_X86_64_RIP:
		if (thread == GDBServer_Host) {
			GETSET8(icpustate64_getrip(STATE),
			        icpustate64_setrip(STATE, value));
		} else {
			FIELD8(STATE->ics_irregs.ir_rip);
		}
		break;

	case GDB_REGISTER_X86_64_RFLAGS:
		if (thread == GDBServer_Host) {
			GETSET4(icpustate64_getrflags(STATE),
			        icpustate64_setrflags(STATE, value));
		} else {
			FIELD4(STATE->ics_irregs.ir_rflags);
		}
		break;

	case GDB_REGISTER_X86_64_CS:
		if (thread == GDBServer_Host) {
			GETSET4(icpustate64_getcs(STATE),
			        icpustate64_setcs(STATE, value));
		} else {
			FIELD4(STATE->ics_irregs.ir_cs);
		}
		break;

	case GDB_REGISTER_X86_64_SS:
		if (thread == GDBServer_Host) {
			GETSET4(icpustate64_getss(STATE),
			        icpustate64_setss(STATE, value));
		} else {
			FIELD4(STATE->ics_irregs.ir_ss);
		}
		break;

	default: {
		size_t result;
		result = FUNC(GPRegsNspRegister)(regno, buf, bufsize, &STATE->ics_gpregs);
		if (result == 0)
			result = FUNC(ThreadRegister)(thread, regno, buf, bufsize);
		return result;
	}	break;
	}
	return 0;
}

INTERN NONNULL((1, 3, 5)) size_t
NOTHROW(FCALL FUNC(SCpuStateRegister))(struct task *__restrict thread,
                                       uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct scpustate64 STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_X86_64_RSP:
		GETSET8(scpustate64_getrsp(STATE),
		        scpustate64_setrsp(STATE, value));
		break;

	case GDB_REGISTER_X86_64_RIP:
		GETSET8(scpustate64_getrip(STATE),
		        scpustate64_setrip(STATE, value));
		break;

	case GDB_REGISTER_X86_64_RFLAGS:
		GETSET4(scpustate64_getrflags(STATE),
		        scpustate64_setrflags(STATE, value));
		break;

	case GDB_REGISTER_X86_64_CS:
		GETSET4(scpustate64_getcs(STATE),
		        scpustate64_setcs(STATE, value));
		break;

	case GDB_REGISTER_X86_64_SS:
		GETSET4(scpustate64_getss(STATE),
		        scpustate64_setss(STATE, value));
		break;

	case GDB_REGISTER_X86_64_DS:
		GETSET4(scpustate64_getds(STATE),
		        scpustate64_setds(STATE, value));
		break;

	case GDB_REGISTER_X86_64_ES:
		GETSET4(scpustate64_getes(STATE),
		        scpustate64_setes(STATE, value));
		break;

	case GDB_REGISTER_X86_64_FS:
		GETSET4(scpustate64_getfs(STATE),
		        scpustate64_setfs(STATE, value));
		break;

	case GDB_REGISTER_X86_64_GS:
		GETSET4(scpustate64_getgs(STATE),
		        scpustate64_setgs(STATE, value));
		break;

	default: {
		size_t result;
		result = FUNC(GPRegsNspRegister)(regno, buf, bufsize, &STATE->scs_gpregs);
		if (result == 0)
			result = FUNC(SGBaseRegister)(regno, buf, bufsize, &STATE->scs_sgbase);
		if (result == 0)
			result = FUNC(ThreadRegister)(thread, regno, buf, bufsize);
		return result;
	}	break;
	}
	return 0;
}

INTERN NONNULL((1, 3, 5)) size_t
NOTHROW(FCALL FUNC(UCpuStateRegister))(struct task *__restrict thread,
                                       uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct ucpustate64 STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_X86_64_RIP:
		FIELD8(STATE->ucs_rip);
		break;

	case GDB_REGISTER_X86_64_RFLAGS:
		FIELD4(STATE->ucs_rflags);
		break;

	case GDB_REGISTER_X86_64_CS:
		FIELD4(STATE->ucs_cs);
		break;

	case GDB_REGISTER_X86_64_SS:
		FIELD4(STATE->ucs_ss);
		break;

	case GDB_REGISTER_X86_64_DS:
		FIELD4(STATE->ucs_sgregs.sg_ds);
		break;

	case GDB_REGISTER_X86_64_ES:
		FIELD4(STATE->ucs_sgregs.sg_es);
		break;

	case GDB_REGISTER_X86_64_FS:
		FIELD4(STATE->ucs_sgregs.sg_fs);
		break;

	case GDB_REGISTER_X86_64_GS:
		FIELD4(STATE->ucs_sgregs.sg_gs);
		break;

	default: {
		size_t result;
		result = FUNC(GPRegsRegister)(regno, buf, bufsize, &STATE->ucs_gpregs);
		if (result == 0)
			result = FUNC(SGBaseRegister)(regno, buf, bufsize, &STATE->ucs_sgbase);
		if (result == 0)
			result = FUNC(ThreadRegister)(thread, regno, buf, bufsize);
		return result;
	}	break;
	}
	return 0;
}


INTERN NONNULL((1, 3, 5)) size_t
NOTHROW(FCALL FUNC(KCpuStateRegister))(struct task *__restrict thread,
                                       uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct kcpustate64 STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_X86_64_RIP:
		FIELD8(STATE->kcs_rip);
		break;

	case GDB_REGISTER_X86_64_RFLAGS:
		FIELD4(STATE->kcs_rflags);
		break;

	default: {
		size_t result;
		result = FUNC(GPRegsRegister)(regno, buf, bufsize, &STATE->kcs_gpregs);
		if (result == 0)
			result = FUNC(ThreadRegister)(thread, regno, buf, bufsize);
		return result;
	}	break;
	}
	return 0;
}

INTERN NONNULL((1, 3, 5)) size_t
NOTHROW(FCALL FUNC(LCpuStateRegister))(struct task *__restrict thread,
                                       uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct lcpustate64 STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_X86_64_R15:
		FIELD8(STATE->lcs_r15);
		break;

	case GDB_REGISTER_X86_64_R14:
		FIELD8(STATE->lcs_r14);
		break;

	case GDB_REGISTER_X86_64_R13:
		FIELD8(STATE->lcs_r13);
		break;

	case GDB_REGISTER_X86_64_R12:
		FIELD8(STATE->lcs_r12);
		break;

	case GDB_REGISTER_X86_64_RBP:
		FIELD8(STATE->lcs_rbp);
		break;

	case GDB_REGISTER_X86_64_RSP:
		FIELD8(STATE->lcs_rsp);
		break;

	case GDB_REGISTER_X86_64_RBX:
		FIELD8(STATE->lcs_rbx);
		break;

	case GDB_REGISTER_X86_64_RIP:
		FIELD8(STATE->lcs_rip);
		break;

	case GDB_REGISTER_X86_64_RFLAGS:
		GETSET4_NOOP();
		break;

	default: {
		size_t result;
		if (regno >= GDB_REGISTER_X86_64_RAX &&
		    regno <= GDB_REGISTER_X86_64_R15)
			GETSET8_NOOP();
		result = FUNC(ThreadRegister)(thread, regno, buf, bufsize);
		return result;
	}	break;
	}
	return 0;
}

INTERN NONNULL((1, 3, 5)) size_t
NOTHROW(FCALL FUNC(FCpuStateRegister))(struct task *__restrict thread,
                                       uintptr_t regno, void BUF_CONST *buf, size_t bufsize,
                                       struct fcpustate64 STATE_PARAM) {
	switch (regno) {

	case GDB_REGISTER_X86_64_RIP:
		FIELD8(STATE->fcs_rip);
		break;

	case GDB_REGISTER_X86_64_RFLAGS:
		FIELD4(STATE->fcs_rflags);
		break;

	case GDB_REGISTER_X86_64_CS:
		FIELD4(STATE->fcs_sgregs.sg_cs);
		break;

	case GDB_REGISTER_X86_64_SS:
		FIELD4(STATE->fcs_sgregs.sg_ss);
		break;

	case GDB_REGISTER_X86_64_DS:
		FIELD4(STATE->fcs_sgregs.sg_ds);
		break;

	case GDB_REGISTER_X86_64_ES:
		FIELD4(STATE->fcs_sgregs.sg_es);
		break;

	case GDB_REGISTER_X86_64_FS:
		FIELD4(STATE->fcs_sgregs.sg_fs);
		break;

	case GDB_REGISTER_X86_64_GS:
		FIELD4(STATE->fcs_sgregs.sg_gs);
		break;

	default: {
		size_t result;
		result = FUNC(GPRegsRegister)(regno, buf, bufsize, &STATE->fcs_gpregs);
		if (result == 0)
			result = FUNC(SGBaseRegister)(regno, buf, bufsize, &STATE->fcs_sgbase);
		if (result == 0)
			result = FUNC(ThreadRegister)(thread, regno, buf, bufsize);
		return result;
	}	break;
	}
	return 0;
}


/* Get/Set the full GDB cpustate. */
INTERN NONNULL((1, 2)) bool
NOTHROW(FCALL FUNC(Registers))(struct task *__restrict thread,
                               struct gdb_cpustate64 BUF_CONST *buf) {
	uintptr_t regno;
	byte_t BUF_CONST *ptr = (byte_t BUF_CONST *)buf;
	for (regno = 0; regno < GDB_REGISTER_X86_64_RFLAGS; ++regno) {
		if (FUNC(Register)(thread, regno, ptr, 8) != 8) {
			GDB_DEBUG("[gdb] Failed to access x86_64 8-byte register %#" PRIxPTR "\n", regno);
			return false;
		}
		ptr += 8;
	}
	for (; regno < GDB_REGISTER_X86_64_ST0; ++regno) {
		if (FUNC(Register)(thread, regno, ptr, 4) != 4) {
			GDB_DEBUG("[gdb] Failed to access x86_64 4-byte register %#" PRIxPTR "\n", regno);
			return false;
		}
		ptr += 4;
	}
	return true;
}


DECL_END
