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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_IOPERM_C
#define GUARD_KERNEL_CORE_ARCH_I386_IOPERM_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/task.h>
#include <sched/x86/iobm.h>
#include <sched/x86/tss.h>

#include <hybrid/align.h>

#include <kos/except/reason/inval.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <string.h>

DECL_BEGIN

LOCAL NONNULL((1)) void KCALL
iob_maskbyte(byte_t *pbyte, u8 byte_mask, u8 byte_flag) {
	u8 oldval;
	do {
		oldval = atomic_read(pbyte);
		/* FIXME: A rare (and random) E_SEGFAULT has been observed that originates from the following line:
		 * >> [2022-06-19T15:19:18.457399057:trace ][16] sys_ioperm(from: 1016, num: 1, turn_on: 1)
		 * >> [2022-06-19T15:19:18.458021345:debug ][16][segfault] Fault at FFFFFFFF8095907F (page FFFFFFFF80959000) [pc=FFFFFFFF803D7B9C,FFFFFFFF803D7BA0] [ecode=0x3]
		 * >> [2022-06-19T15:19:18.458376352:trace ][16][except] Translate exception 0xff0e:0x2,E_SEGFAULT_READONLY[0xffffffff8095907f,0x3] into errno=-EFAULT
		 * Another instance:
		 * >> [2022-12-13T10:14:18.841998792:trace ][6] sys32_ioperm(from: 1016, num: 1, turn_on: 0)
		 * >> [2022-12-13T10:14:18.842094932:debug ][6][segfault] Fault at FFFFFFFF8097E07F (page FFFFFFFF8097E000) [pc=FFFFFFFF803D94C6,FFFFFFFF803D94CA] [ecode=0x3]
		 * >> [2022-12-13T10:14:18.844260930:trace ][6][except] Translate exception 0xff0e:0x2,E_SEGFAULT_READONLY[0xffffffff8097e07f,0x3] into errno=-EFAULT
		 * And another:
		 * [2023-06-15T14:55:29.925834392:trace ][17][test:ioperm_works_correctly] kos/src/apps/system-test/test-ioperm.c:57
		 * [2023-06-15T14:55:29.925991577:trace ][17] sys_write(fd: STDOUT_FILENO, buf: "test:ioperm_works_correctly\e[K\n", bufsize: 31)
		 * [2023-06-15T14:55:29.927792212:trace ][17][except] Propagate exception 0xff06:0x3,E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE[0x6e,0x40,0x3f8,0x1] hand:[pc=E0486A9,sp=7FFFFEB0] orig:[pc=806D104,sp=7FFFFF00] fault:[pc=806D102] [mode=0x4003]
		 * [2023-06-15T14:55:29.928091442:trace ][17] sys_Xarch_prctl(command: ARCH_GET_GS, addr: 0x7ffffcc8)
		 * [2023-06-15T14:55:29.929845315:trace ][17][rtld] Lazy resolve "except_nesting_begin" in "/lib/libunwind.so" (to 0E0CBBEB from "/lib/libc.so")
		 * [2023-06-15T14:55:29.930036182:trace ][17][rtld] Lazy resolve "except_nesting_end" in "/lib/libunwind.so" (to 0E0CBC88 from "/lib/libc.so")
		 * [2023-06-15T14:55:29.930826719:trace ][17][rtld] Lazy resolve "except_code" in "/bin/system-test" (to 0E048DE4 from "/lib/libc.so")
		 * [2023-06-15T14:55:29.931008164:trace ][17][rtld] Lazy resolve "iopl" in "/bin/system-test" (to 0E0901D1 from "/lib/libc.so")
		 * [2023-06-15T14:55:29.931178481:trace ][17] sys_iopl(level: 3)
		 *
		 * HELLO QEMU DEBUG PORT
		 * HELLO QEMU DEBUG PORT
		 * HELLO QEMU DEBUG PORT
		 *
		 * [2023-06-15T14:55:29.931411051:trace ][17] sys_iopl(level: 0)
		 * [2023-06-15T14:55:29.931514504:trace ][17][except] Propagate exception 0xff06:0x3,E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE[0x6e,0x40,0x3f8,0x1] hand:[pc=E0486A9,sp=7FFFFEB0] orig:[pc=806D104,sp=7FFFFF00] fault:[pc=806D102] [mode=0x4003]
		 * [2023-06-15T14:55:29.931806719:trace ][17] sys_Xarch_prctl(command: ARCH_GET_GS, addr: 0x7ffffcc8)
		 * [2023-06-15T14:55:29.931947965:trace ][17][rtld] Lazy resolve "ioperm" in "/bin/system-test" (to 0E09014F from "/lib/libc.so")
		 * [2023-06-15T14:55:29.932123595:trace ][17] sys_ioperm(from: 1016, num: 1, turn_on: 1)
		 * [2023-06-15T14:55:29.932479267:debug ][17][segfault] Fault at C091507F (page C0915000) [pc=C03704C9,C03704CD] [ecode=0x3]
		 * [2023-06-15T14:55:29.933688395:trace ][17][except] Translate exception 0xff0e:0x2,E_SEGFAULT_READONLY[0xc091507f,0x3] into errno=-EFAULT
		 * [2023-06-15T14:55:29.933877659:trace ][17][rtld] Lazy resolve "__afailf" in "/bin/system-test" (to 0E09308B from "/lib/libc.so")
		 * [2023-06-15T14:55:29.943122200:trace ][17] sys_ioctl(fd: STDERR_FILENO, command: TCGETA, arg: 7FFFF294)
		 * [2023-06-15T14:55:29.943319182:trace ][17] sys_write(fd: STDERR_FILENO, buf: "Assertion Failure [pc=", bufsize: 22)
		 * [2023-06-15T14:55:29.943488999:trace ][17] sys_write(fd: STDERR_FILENO, buf: "0", bufsize: 1)
		 * [2023-06-15T14:55:29.943670744:trace ][17] sys_write(fd: STDERR_FILENO, buf: "806D285", bufsize: 7)
		 * [2023-06-15T14:55:29.943786527:trace ][17] sys_write(fd: STDERR_FILENO, buf: "]\n", bufsize: 2)
		 * [2023-06-15T14:55:29.943475165:error ][17] Assertion Failure [pc=0806D285]
		 * [2023-06-15T14:55:29.944591700:trace ][17] sys_write(fd: STDERR_FILENO, buf: "kos/src/apps/system-test/test-ioperm.c", bufsize: 38)
		 * [2023-06-15T14:55:29.944859556:trace ][17] sys_write(fd: STDERR_FILENO, buf: "(", bufsize: 1)
		 * [2023-06-15T14:55:29.944982758:trace ][17] sys_write(fd: STDERR_FILENO, buf: "82", bufsize: 2)
		 * [2023-06-15T14:55:29.945152675:trace ][17] sys_write(fd: STDERR_FILENO, buf: ") : ", bufsize: 4)
		 * [2023-06-15T14:55:29.945370107:trace ][17] sys_write(fd: STDERR_FILENO, buf: "test_ioperm_works_correctly", bufsize: 27)
		 * [2023-06-15T14:55:29.945624230:trace ][17] sys_write(fd: STDERR_FILENO, buf: " : ", bufsize: 3)
		 * [2023-06-15T14:55:29.945762268:trace ][17] sys_write(fd: STDERR_FILENO, buf: "0 == ioperm(portno, 1, 1)", bufsize: 25)
		 * [2023-06-15T14:55:29.945955441:trace ][17] sys_write(fd: STDERR_FILENO, buf: "\n", bufsize: 1)
		 * [2023-06-15T14:55:29.944845923:error ][17] kos/src/apps/system-test/test-ioperm.c(82) : test_ioperm_works_correctly : 0 == ioperm(portno, 1, 1)
		 * [2023-06-15T14:55:29.946817554:trace ][17] sys_write(fd: STDERR_FILENO, buf: "0 == -1\n", bufsize: 8)
		 * [2023-06-15T14:55:29.947475465:error ][17] 0 == -1
		 * [2023-06-15T14:55:29.947560273:trace ][17] sys_coredump(curr_state: 7FFFF620, orig_state: 00000000, traceback_vector: 00000000, traceback_length: 0, reason: 7FFFF6AC, unwind_error: 00000045)
		 * [2023-06-15T14:55:29.948698562:error ][17][coredump] Creating coredump...
		 * assert.expr: "0 == ioperm(portno, 1, 1)"
		 * assert.file: "kos/src/apps/system-test/test-ioperm.c"
		 * assert.line: 82
		 * assert.func: "test_ioperm_works_correctly"
		 * assert.mesg: "0 == -1"
		 * 806D285 [test-ioperm.c:83,7:test_ioperm_works_correctly] orig_ustate
		 * Coredump /bin/system-test tid:17
		 * assert.expr: "0 == ioperm(portno, 1, 1)"
		 * assert.file: "kos/src/apps/system-test/test-ioperm.c"
		 * assert.line: 82
		 * assert.func: "test_ioperm_works_correctly"
		 * assert.mesg: "0 == -1"
		 * E:\c\kls\kos\kos\src\apps\system-test\test-ioperm.c(83,7) : 0806D285+5[/bin/system-test][test_ioperm_works_correctly+366] [orig_ustate]
		 * > [2023-06-15T14:55:31.463858083:trace ][17][sched] Exiting thread E2016DE4
		 */
	} while (!atomic_cmpxch_weak(pbyte, oldval, (oldval & byte_mask) | byte_flag));
}

LOCAL NONNULL((1)) void KCALL
iob_maskbyte_c(byte_t *pbyte, shift_t minbit, shift_t bitcnt, bool turn_on) {
	u8 bitmask;
	assert((minbit + bitcnt) <= 8);
	bitmask = (u8)(((1 << bitcnt) - 1) << minbit);
	iob_maskbyte(pbyte, ~bitmask,
	             turn_on ? 0 : bitmask);
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) bool KCALL
iob_isenabled(byte_t const *iob, u16 port) {
	return (iob[FLOORDIV(port, 8)] & (1 << (port & 7))) != 0;
}

/* Turn permission bits for a given range on/off. */
LOCAL NONNULL((1)) void KCALL
iob_setrange(byte_t *iob, u16 minport, u16 maxport, bool turn_on) {
	size_t minbyte, maxbyte;
	shift_t minbit;
	assert(maxport >= minport);
	minbyte = FLOORDIV(minport, 8);
	maxbyte = CEILDIV(maxport + 1, 8) - 1;
	assert(maxbyte >= minbyte);

	/* Special case: only a single byte is getting modified. */
	if (maxbyte == minbyte) {
		shift_t bitcnt;
		minbit = minport & 7;
		bitcnt = (maxport - minport) + 1;

		/* Update the bitmap mask. */
		iob_maskbyte_c(iob + minbyte,
		               minbit, bitcnt,
		               turn_on);
		return;
	}

	/* Update the bitsets for the first and last affected bitset byte */
	minbit = minport & 7;
	iob_maskbyte_c(iob + minbyte, minbit, 8 - minbit, turn_on);
	iob_maskbyte_c(iob + maxbyte, 0, (maxport & 7) + 1, turn_on);

	/* Fill in all intermediate bytes. */
	if (minbyte + 1 < maxbyte) {
		memset(iob + minbyte,
		       turn_on ? 0x00 : 0xff,
		       (maxbyte - minbyte) - 1);
	}
}


DEFINE_SYSCALL3(errno_t, ioperm,
                syscall_ulong_t, from,
                syscall_ulong_t, num,
                syscall_ulong_t, turn_on) {
	uintptr_t old_thread_flags;
	struct task *caller;
	struct cpu *me;
	byte_t *iob;
	if unlikely(!num)
		return -EOK;
	if unlikely((syscall_ulong_t)(from + num) < from ||
	            (syscall_ulong_t)(from + num) > 0x10000) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_IOPERM_RANGE,
		      0x10000);
	}
	if (turn_on != 0 && turn_on != 1) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_IOPERM_TURNON,
		      turn_on);
	}

	/* Manipulate the  IOBM of  our own  thread  through use  of the  `thiscpu_x86_iob'  vector.
	 * Access to said vector is directly granted so-long as we keep the TASK_FKEEPCORE flag set. */
	caller           = THIS_TASK;
	old_thread_flags = atomic_fetchor(&caller->t_flags, TASK_FKEEPCORE);
	RAII_FINALLY {
		if (!(old_thread_flags & TASK_FKEEPCORE))
			atomic_and(&caller->t_flags, ~TASK_FKEEPCORE);
	};
	COMPILER_READ_BARRIER();
	me  = caller->t_cpu;
	iob = &FORCPU(me, thiscpu_x86_iob[0]);

	/* Ensure that the caller is allowed hardware port access.
	 * This essentially enforces that:
	 *  - Anyone is allowed to disable ports (or keep them enabled)
	 *  - As such, we must only throw an insufficient-rights exception
	 *    if the calling  thread doesn't have  permissions to turn  on
	 *    permissions for some specific port. */
#ifndef CONFIG_KERNEL_EVERYONE_IS_ROOT
	if (turn_on && !capable(CAP_SYS_RAWIO)) {
		u32 i, end = (u32)(u16)from + (u32)(u16)num;
		for (i = (u32)(u16)from; i < end; ++i) {
			if (!iob_isenabled(iob, i))
				THROW(E_INSUFFICIENT_RIGHTS, CAP_SYS_RAWIO);
		}
	} else
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
	{
		/* Update bits for the given range. */
		iob_setrange(iob,
		             (u16)from,
		             (u16)from + (u16)num - 1,
		             turn_on != 0);
	}
	return -EOK;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_IOPERM_C */
