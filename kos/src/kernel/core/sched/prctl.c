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
#ifndef GUARD_KERNEL_SRC_SCHED_PRCTL_C
#define GUARD_KERNEL_SRC_SCHED_PRCTL_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/rt/except-syscall.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/comm.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/byteorder.h>

#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>
#include <linux/prctl.h>

#include <errno.h>
#include <signal.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <kernel/compat.h>

#include <compat/kos/types.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define NATIVE_ENDIAN PR_ENDIAN_LITTLE
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define NATIVE_ENDIAN PR_ENDIAN_BIG
#else /* __BYTE_ORDER__ == ... */
#define NATIVE_ENDIAN (-1) /* ??? */
#endif /* __BYTE_ORDER__ != ... */



/************************************************************************/
/* prctl()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_PRCTL
DEFINE_SYSCALL5(syscall_slong_t, prctl, unsigned int, command,
                syscall_ulong_t, arg2, syscall_ulong_t, arg3,
                syscall_ulong_t, arg4, syscall_ulong_t, arg5) {
	struct task *me       = THIS_TASK;
	struct taskpid *mypid = task_gettaskpid_of(me);
	switch (command) {

	case PR_SET_PDEATHSIG:
		if unlikely(!sigvalid(arg2)) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO,
			      arg2);
		}
		mypid->tp_SIGCLD = (uint8_t)arg2;
		break;

	case PR_GET_PDEATHSIG:
		validate_readable((USER UNCHECKED signo_t *)arg2, sizeof(signo_t));
		*(USER CHECKED signo_t *)arg2 = mypid->tp_SIGCLD;
		break;

	/* TODO: PR_GET_DUMPABLE */
	/* TODO: PR_SET_DUMPABLE */

	case PR_GET_KEEPCAPS: {
		struct cred *mycred = FORTASK(me, this_cred);
		return (ATOMIC_READ(mycred->c_securebits) & SECBIT_KEEP_CAPS) != 0;
	}	break;

	case PR_SET_KEEPCAPS: {
		struct cred *mycred = FORTASK(me, this_cred);
		if unlikely(arg2 != 0 && arg2 != 1) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_SET_KEEPCAPS_BADBOOL,
			      arg2);
		}
		require(CAP_SETPCAP); /* "The CAP_SETPCAP capability is required to modify the flags" */
		cred_write(mycred);
		if (mycred->c_securebits & SECBIT_KEEP_CAPS_LOCKED) {
			cred_endwrite(mycred);
			THROW(E_ILLEGAL_OPERATION,
			      E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_KEEPCAPS_LOCKED);
		}
		mycred->c_securebits &= ~SECBIT_KEEP_CAPS;
		if (arg2)
			mycred->c_securebits |= SECBIT_KEEP_CAPS;
		cred_endwrite(mycred);
	}	break;

	case PR_GET_TIMING:
		return PR_TIMING_STATISTICAL;
	case PR_SET_TIMING:
		if (arg2 != PR_TIMING_STATISTICAL) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_SET_TIMING_BADMODE,
			      arg2);
		}
		break;

#ifdef CONFIG_HAVE_TASK_COMM
	case PR_SET_NAME: {
		char buf[TASK_COMM_LEN];
		USER CHECKED char const *name;
		name = (USER CHECKED char const *)validate_readableaddr((USER UNCHECKED char const *)arg2);
		strlcpy(buf, name, TASK_COMM_LEN);
		task_setcomm(buf);
	}	break;

	case PR_GET_NAME: {
		char buf[TASK_COMM_LEN];
		USER CHECKED char *name;
		memcpy(buf, FORTASK(me, this_comm), sizeof(buf));
		name = (USER CHECKED char *)validate_writableaddr((USER UNCHECKED char *)arg2);
		memcpy(name, buf, strlen(buf) + 1, sizeof(char));
	}	break;
#endif /* CONFIG_HAVE_TASK_COMM */

	case PR_GET_ENDIAN: {
		USER CHECKED int *pmode;
		pmode  = (USER CHECKED int *)validate_writable((USER UNCHECKED int *)arg2, sizeof(int));
		*pmode = NATIVE_ENDIAN;
	}	break;

	case PR_SET_ENDIAN: {
		if (arg2 != NATIVE_ENDIAN) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_SET_ENDIAN_BADENDIAN,
			      arg2);
		}
	}	break;

	case PR_CAPBSET_READ: {
		struct cred *mycred = FORTASK(me, this_cred);
		if ((syscall_slong_t)arg2 < CAP_FIRST_CAP ||
		    (syscall_slong_t)arg2 > CAP_LAST_CAP) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BADCAP,
			      (syscall_slong_t)arg2);
		}
		return credcap_capable(&mycred->c_cap_bounding, (syscall_slong_t)arg2) ? 1 : 0;
	}	break;

	case PR_CAPBSET_DROP: {
		struct cred *mycred = FORTASK(me, this_cred);
		require(CAP_SETPCAP);
		if ((syscall_slong_t)arg2 < CAP_FIRST_CAP ||
		    (syscall_slong_t)arg2 > CAP_LAST_CAP) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BADCAP,
			      (syscall_slong_t)arg2);
		}
		cred_write(mycred);
		credcap_turnoff(&mycred->c_cap_bounding, (syscall_slong_t)arg2);
		cred_endwrite(mycred);
	}	break;

#if defined(__i386__) || defined(__x86_64__)
	/* TODO: PR_GET_TSC */
	/* TODO: PR_GEPR_SET_TSCT_TSC */
#endif /* !__USE_KOS_PURE || __i386__ || __x86_64__ */

	case PR_GET_SECUREBITS: {
		struct cred *mycred = FORTASK(me, this_cred);
		return mycred->c_securebits;
	}	break;

	case PR_SET_SECUREBITS: {
#define SECBITS_ALL                                           \
	(SECBIT_NOROOT | SECBIT_NOROOT_LOCKED |                   \
	 SECBIT_NO_SETUID_FIXUP | SECBIT_NO_SETUID_FIXUP_LOCKED | \
	 SECBIT_KEEP_CAPS | SECBIT_KEEP_CAPS_LOCKED |             \
	 SECBIT_NO_CAP_AMBIENT_RAISE | SECBIT_NO_CAP_AMBIENT_RAISE_LOCKED)
#define SECBITS_LOCKS                                       \
	(SECBIT_NOROOT_LOCKED | SECBIT_NO_SETUID_FIXUP_LOCKED | \
	 SECBIT_KEEP_CAPS_LOCKED | SECBIT_NO_CAP_AMBIENT_RAISE_LOCKED)
		struct cred *mycred = FORTASK(me, this_cred);
		if (arg2 & ~SECBITS_ALL) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_SET_SECUREBITS_BADBITS,
			      arg2, ~SECBITS_ALL);
		}
		require(CAP_SETPCAP); /* "The CAP_SETPCAP capability is required to modify the flags" */
		cred_write(mycred);
		/* Don't allow locks to be released. (they can only be added) */
		if ((mycred->c_securebits & ~arg2 & SECBITS_LOCKS) != 0) {
			cred_endwrite(mycred);
			THROW(E_ILLEGAL_OPERATION,
			      E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_SECUREBITS_UNLOCK);
		}

		/* Don't allow changes to locked bits. */
		if ((((arg2 & ~SECBITS_LOCKS) ^ (mycred->c_securebits & ~SECBITS_LOCKS)) & /* Bitset of changed non-lock bits. */
		     ((mycred->c_securebits & SECBITS_LOCKS) >> 1)                         /* Bitset of immutable non-lock bits */
		     ) != 0) {
			cred_endwrite(mycred);
			THROW(E_ILLEGAL_OPERATION,
			      E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_SECUREBITS_LOCKED);
		}
		mycred->c_securebits = (typeof(mycred->c_securebits))arg2;
		cred_endwrite(mycred);
#undef SECBITS_LOCKS
#undef SECBITS_ALL
	}	break;

	/* XXX: PR_SET_MM? */

	/* TODO: PR_SET_CHILD_SUBREAPER */
	/* TODO: PR_GET_CHILD_SUBREAPER */

	case PR_SET_NO_NEW_PRIVS: {
		struct cred *mycred = FORTASK(me, this_cred);
		if (arg2 != 0 && arg2 != 1) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_SET_NO_NEW_PRIVS_BADBOOL,
			      arg2);
		}
		if unlikely(arg3 != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_SET_NO_NEW_PRIVS_RESERVED3,
			      arg3);
		}
		if unlikely(arg4 != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_SET_NO_NEW_PRIVS_RESERVED4,
			      arg4);
		}
		if unlikely(arg5 != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_SET_NO_NEW_PRIVS_RESERVED5,
			      arg5);
		}
		cred_write(mycred);
		if (arg2 == 0 && mycred->c_no_new_privs != 0) {
			cred_endwrite(mycred);
			THROW(E_ILLEGAL_OPERATION,
			      E_ILLEGAL_OPERATION_CONTEXT_PRCTL_SET_NO_NEW_PRIVS_CANNOT_DISABLE);
		}
		mycred->c_no_new_privs = (typeof(mycred->c_no_new_privs))arg2;
		cred_endwrite(mycred);
	}	break;

	case PR_GET_NO_NEW_PRIVS: {
		struct cred *mycred = FORTASK(me, this_cred);
		if unlikely(arg2 != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_GET_NO_NEW_PRIVS_RESERVED2,
			      arg2);
		}
		if unlikely(arg3 != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_GET_NO_NEW_PRIVS_RESERVED3,
			      arg3);
		}
		if unlikely(arg4 != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_GET_NO_NEW_PRIVS_RESERVED4,
			      arg4);
		}
		if unlikely(arg5 != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_GET_NO_NEW_PRIVS_RESERVED5,
			      arg5);
		}
		return ATOMIC_READ(mycred->c_no_new_privs) != 0 ? 1 : 0;
	}	break;

	case PR_GET_TID_ADDRESS: {
		uintptr_t tidaddr = (uintptr_t)FORTASK(me, this_tid_address);
#ifdef __ARCH_HAVE_COMPAT
		if (syscall_iscompat()) {
			*(USER CHECKED compat_uintptr_t *)compat_validate_writable(
			(USER UNCHECKED void *)arg2, sizeof(compat_uintptr_t)) = (compat_uintptr_t)tidaddr;
		} else
#endif /* __ARCH_HAVE_COMPAT */
		{
			*(USER CHECKED uintptr_t *)validate_writable(
			(USER UNCHECKED void *)arg2, sizeof(uintptr_t)) = tidaddr;
		}
	}	break;

	case PR_CAP_AMBIENT: {
		struct cred *mycred = FORTASK(me, this_cred);
		if unlikely(arg4 != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_CAP_AMBIENT_RESERVED4,
				  arg4);
		}
		if unlikely(arg5 != 0) {
			THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_CAP_AMBIENT_RESERVED5,
				  arg5);
		}
		if (arg2 == PR_CAP_AMBIENT_CLEAR_ALL) {
			if unlikely(arg3 != 0) {
				THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
				      E_INVALID_ARGUMENT_CONTEXT_PRCTL_CAP_AMBIENT_RESERVED3,
				      arg3);
			}
			cred_write(mycred);
			bzero(&mycred->c_cap_ambient, sizeof(mycred->c_cap_ambient));
			cred_endwrite(mycred);
			break;
		}
		if ((syscall_slong_t)arg3 < CAP_FIRST_CAP ||
		    (syscall_slong_t)arg3 > CAP_LAST_CAP) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BADCAP,
			      (syscall_slong_t)arg3);
		}
		switch (arg2) {

		case PR_CAP_AMBIENT_IS_SET:
			return credcap_capable(&mycred->c_cap_ambient, (syscall_slong_t)arg3) ? 1 : 0;

		case PR_CAP_AMBIENT_RAISE: {
			cred_write(mycred);
			if unlikely(mycred->c_securebits & SECBIT_NO_CAP_AMBIENT_RAISE) {
				cred_endwrite(mycred);
				THROW(E_ILLEGAL_OPERATION,
				      E_ILLEGAL_OPERATION_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DISABLED,
				      (syscall_slong_t)arg3);
			}
			if (!credcap_capable(&mycred->c_cap_permitted, (syscall_slong_t)arg3) ||
			    !credcap_capable(&mycred->c_cap_inheritable, (syscall_slong_t)arg3)) {
				cred_endwrite(mycred);
				THROW(E_ILLEGAL_OPERATION,
				      E_ILLEGAL_OPERATION_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DENIED,
				      (syscall_slong_t)arg3);
			}
			credcap_turnon(&mycred->c_cap_ambient, (syscall_slong_t)arg3);
			cred_endwrite(mycred);
		}	break;

		case PR_CAP_AMBIENT_LOWER:
			cred_write(mycred);
			credcap_turnoff(&mycred->c_cap_ambient, (syscall_slong_t)arg3);
			cred_endwrite(mycred);
			break;

		default:
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_PRCTL_CAP_AMBIENT_BADSUBMODE,
			      arg2);
			break;
		}
	}	break;

	/* TODO: PR_GET_SPECULATION_CTRL */
	/* TODO: PR_SET_SPECULATION_CTRL */

	/* TODO: PR_SET_IO_FLUSHER */
	/* TODO: PR_GET_IO_FLUSHER */

	/* TODO: PR_SET_PTRACER */


	case PR_KOS_GET_AT_SECURE: {
		/* Determine AT_SECURE as documented here:
		 * https://man7.org/linux/man-pages/man8/ld.so.8.html */
		syscall_slong_t result;
		struct cred *mycred = FORTASK(me, this_cred);
		cred_read(mycred);
		/* XXX: must also set  AT_SECURE if dlmodulename(dlopen(NULL,  0))
		 *      had extended attributes set that were added to our process
		 *      during execution (s.a. kernel:`inode_get_file_creds()')
		 * Currently, this never happens on KOS since `inode_get_file_creds'
		 * is  implemented as a  no-op (for now),  but once it's implemented
		 * properly, we must check here if it may have done something. */
		result = (mycred->c_ruid != mycred->c_euid) ||
		         (mycred->c_rgid != mycred->c_egid);
		cred_endread(mycred);
		return result;
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_PRCTL_COMMAND,
		      command);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_PRCTL */


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_PRCTL_C */
