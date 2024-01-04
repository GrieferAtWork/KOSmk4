/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_BITS_UKERN_STRUCT32_H
#define _I386_KOS_KOS_BITS_UKERN_STRUCT32_H 1

#include <__stdinc.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/types.h>
#include <kos/kernel/bits/cpu-state32.h>
#include <kos/kernel/bits/fpu-sstate.h>
#include <kos/kernel/bits/fpu-state32.h>

__DECL_BEGIN

#ifndef __x86_64__
#define OFFSET_USERKERN_BASE   OFFSET_USERKERN32_BASE
#define OFFSET_USERKERN_TID    OFFSET_USERKERN32_TID
#define OFFSET_USERKERN_PID    OFFSET_USERKERN32_PID
#define OFFSET_USERKERN_PPID   OFFSET_USERKERN32_PPID
#define OFFSET_USERKERN_PGID   OFFSET_USERKERN32_PGID
#define OFFSET_USERKERN_SID    OFFSET_USERKERN32_SID
#define OFFSET_USERKERN_UID    OFFSET_USERKERN32_UID
#define OFFSET_USERKERN_GID    OFFSET_USERKERN32_GID
#define OFFSET_USERKERN_EUID   OFFSET_USERKERN32_EUID
#define OFFSET_USERKERN_EGID   OFFSET_USERKERN32_EGID
#define OFFSET_USERKERN_SUID   OFFSET_USERKERN32_SUID
#define OFFSET_USERKERN_SGID   OFFSET_USERKERN32_SGID
#define OFFSET_USERKERN_REGS   OFFSET_USERKERN32_REGS
#define OFFSET_USERKERN_SFPU   OFFSET_USERKERN32_SFPU
#define OFFSET_USERKERN_XFPU   OFFSET_USERKERN32_XFPU
#define SIZEOF_USERKERN        SIZEOF_USERKERN32
#define userkern32             userkern
#endif /* !__x86_64__ */


#define OFFSET_USERKERN32_BASE   0
#define OFFSET_USERKERN32_TID    4
#define OFFSET_USERKERN32_PID    8
#define OFFSET_USERKERN32_PPID   12
#define OFFSET_USERKERN32_PGID   16
#define OFFSET_USERKERN32_SID    20
#define OFFSET_USERKERN32_UID    24
#define OFFSET_USERKERN32_GID    28
#define OFFSET_USERKERN32_EUID   32
#define OFFSET_USERKERN32_EGID   36
#define OFFSET_USERKERN32_SUID   40
#define OFFSET_USERKERN32_SGID   44
#define OFFSET_USERKERN32_REGS   48
#define OFFSET_USERKERN32_SFPU   112
#define OFFSET_USERKERN32_XFPU   224
#define SIZEOF_USERKERN32        736

#ifdef __CC__
struct userkern32 /*[PREFIX(uk_)]*/ {
	/* Thread-local state information provided by the kernel.
	 * NOTE: This structure is implemented through VIO, so it doesn't really behave
	 *       like  you would expect it to, while any sort of memory access is quite
	 *       slow and should be kept at a minimum for that reason.
	 *  - The contents of this structure are thread-local for the most part
	 *  - Calling the address of this structure after adding an offset of one of `__NR_*',
	 *    allows   that  system   call  to  be   invoked  as  a   regular,  old  function:
	 *    >> typedef int (*POPEN)(char const *filename, oflag_t flags, ...);
	 *    >> typedef int (*PCLOSE)(int fd);
	 *    >> struct userkern *t = userkern_get();
	 *    >> POPEN pfun = (POPEN)((byte_t *)t + USERKERN_SYSCALL_ENCODE(SYS_open));
	 *    >> PCLOSE pclose = (PCLOSE)((byte_t *)t + USERKERN_SYSCALL_ENCODE(SYS_close));
	 *    >>
	 *    >> int fd = (*pfun)("/bin/init", O_RDONLY);
	 *    >> printf("fd = %d\n", fd);
	 *    >> (*pclose)(fd);
	 *  - Attempting to invoke a non-existent system call via this method will not
	 *    cause an E_SEGFAULT
	 *  - Attempting to write to one of the constant fields of this structure will
	 *    cause an E_SEGFAULT_READONLY exception to be thrown. */
	__HYBRID_PTR32(struct userkern32)
		                        uk_base;  /* [1..1][== self] Base address of the thread segment.
	                                       * During thread creation, this address is first randomized before
	                                       * being assigned to the TLS register returned by `userkern_self()'.
	                                       * Note that the userkern descriptor is implemented through VIO, as
	                                       * well as the fact that it always points into kernel-space (meaning
	                                       * that it doesn't use up any user-space memory ranges)
	                                       * NOTE: This field can be written to in order to move the base address
	                                       *       of the userkern segment, although the new address must remain
	                                       *       within kernel-space, with an `E_INVALID_ARGUMENT_BAD_VALUE' exception
	                                       *       being thrown (context `E_INVALID_ARGUMENT_CONTEXT_USERKERN_BASE')
	                                       * NOTE: userkern functionality is only provided while the thread's TLS
	                                       *       register points into user-space. - When altering the address of
	                                       *       the TLS register (e.g. on x86 `__wr(fs|gs)base()'), the userkern
	                                       *       segment is moved as well, however access to this structure is lost
	                                       *       if the TLS register base no longer points into kernel-space. */
	__uint32_t const            uk_tid;   /* [const] TID of the calling thread. */
	__uint32_t const            uk_pid;   /* [const] PID of the calling process. */
	__uint32_t const            uk_ppid;  /* [const] PID of the calling process's parent process. */
	__uint32_t const            uk_pgid;  /* [const] ID of the process group that the calling thread is apart of. */
	__uint32_t const            uk_sid;   /* [const] ID of the session that the calling thread is apart of. */
	__uint32_t volatile         uk_uid;   /* Access to real uid (`getuid()' / `setuid()') of the calling process */
	__uint32_t volatile         uk_gid;   /* Access to real gid (`getgid()' / `setgid()') of the calling process */
	__uint32_t volatile         uk_euid;  /* Access to effective uid (`geteuid()' / `seteuid()') of the calling process */
	__uint32_t volatile         uk_egid;  /* Access to effective gid (`getegid()' / `setegid()') of the calling process */
	__uint32_t volatile         uk_suid;  /* Access to saved uid of the calling process */
	__uint32_t volatile         uk_sgid;  /* Access to saved gid of the calling process */
	struct ucpustate32 volatile uk_regs;  /* Your current register  state. (essentially, this  is can  be
	                                       * used as a memory-mapped copy of your current register state) */
	struct sfpustate volatile   uk_sfpu;  /* Simple FPU register map */
	__uint8_t                 __uk_pad[4]; /* Pad to have `uk_xfpu' be aligned by 16 bytes */
	struct xfpustate32 volatile uk_xfpu;  /* Extended FPU register map */
};
#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_KOS_BITS_UKERN_STRUCT_H */
