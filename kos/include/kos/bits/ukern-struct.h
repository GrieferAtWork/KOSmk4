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
#ifndef _KOS_BITS_UKERN_STRUCT_H
#define _KOS_BITS_UKERN_STRUCT_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <bits/types.h>
#include <kos/kernel/cpu-state.h>

#define OFFSET_USERKERN_BASE 0
#define OFFSET_USERKERN_TID  __SIZEOF_POINTER__
#define OFFSET_USERKERN_PID  (__SIZEOF_POINTER__ * 2)
#define OFFSET_USERKERN_PPID (__SIZEOF_POINTER__ * 3)
#define OFFSET_USERKERN_PGID (__SIZEOF_POINTER__ * 4)
#define OFFSET_USERKERN_SID  (__SIZEOF_POINTER__ * 5)
#define OFFSET_USERKERN_UID  (__SIZEOF_POINTER__ * 6)
#define OFFSET_USERKERN_GID  (__SIZEOF_POINTER__ * 7)
#define OFFSET_USERKERN_EUID (__SIZEOF_POINTER__ * 8)
#define OFFSET_USERKERN_EGID (__SIZEOF_POINTER__ * 9)
#define OFFSET_USERKERN_SUID (__SIZEOF_POINTER__ * 10)
#define OFFSET_USERKERN_SGID (__SIZEOF_POINTER__ * 11)
#define OFFSET_USERKERN_REGS (__SIZEOF_POINTER__ * 12)
#define SIZEOF_USERKERN      (__SIZEOF_POINTER__ * 12 + SIZEOF_UCPUSTATE)

#ifdef __CC__
#if __SIZEOF_PID_T__ < __SIZEOF_POINTER__
#define __USERKERN_PAD_PID(name)  __byte_t name[__SIZEOF_POINTER__ - __SIZEOF_PID_T__];
#else /* __SIZEOF_PID_T__ < __SIZEOF_POINTER__ */
#define __USERKERN_PAD_PID(name)  /* nothing */
#endif /* __SIZEOF_PID_T__ >= __SIZEOF_POINTER__ */
#if __SIZEOF_UID_T__ < __SIZEOF_POINTER__
#define __USERKERN_PAD_UID(name)  __byte_t name[__SIZEOF_POINTER__ - __SIZEOF_UID_T__];
#else /* __SIZEOF_UID_T__ < __SIZEOF_POINTER__ */
#define __USERKERN_PAD_UID(name)  /* nothing */
#endif /* __SIZEOF_UID_T__ >= __SIZEOF_POINTER__ */
#if __SIZEOF_GID_T__ < __SIZEOF_POINTER__
#define __USERKERN_PAD_GID(name)  __byte_t name[__SIZEOF_POINTER__ - __SIZEOF_GID_T__];
#else /* __SIZEOF_GID_T__ < __SIZEOF_POINTER__ */
#define __USERKERN_PAD_GID(name)  /* nothing */
#endif /* __SIZEOF_GID_T__ >= __SIZEOF_POINTER__ */


struct userkern /*[PREFIX(uk_)]*/ {
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
	struct userkern   *uk_base;  /* [1..1][== self] Base address of the thread segment.
	                              * During thread creation, this  address is first randomized  before
	                              * being assigned to the TLS register returned by `userkern_self()'.
	                              * Note that the userkern descriptor is implemented through VIO,  as
	                              * well as the fact that it always points into kernel-space (meaning
	                              * that it doesn't use up any user-space memory ranges)
	                              * NOTE: This field  can be  written to  in  order to  move the  base  address
	                              *       of  the  userkern  segment,  although  the  new  address  must remain
	                              *       within kernel-space, with an `E_INVALID_ARGUMENT_BAD_VALUE' exception
	                              *       being  thrown  (context   `E_INVALID_ARGUMENT_CONTEXT_USERKERN_BASE')
	                              * NOTE: userkern functionality  is only  provided while  the thread's  TLS
	                              *       register points into  user-space. - When  altering the address  of
	                              *       the TLS register (e.g.  on x86 `__wr(fs|gs)base()'), the  userkern
	                              *       segment is moved as well, however access to this structure is lost
	                              *       if the TLS register base no longer points into kernel-space. */
	__pid_t const      uk_tid;   /* [const] TID of the calling thread. */
	__USERKERN_PAD_PID(__uk_pad0)
	__pid_t const      uk_pid;   /* [const] PID of the calling process. */
	__USERKERN_PAD_PID(__uk_pad1)
	__pid_t const      uk_ppid;  /* [const] PID of the calling process's parent process. */
	__USERKERN_PAD_PID(__uk_pad2)
	__pid_t const      uk_pgid;  /* [const] ID of the process group that the calling thread is apart of. */
	__USERKERN_PAD_PID(__uk_pad3)
	__pid_t const      uk_sid;   /* [const] ID of the session that the calling thread is apart of. */
	__USERKERN_PAD_PID(__uk_pad4)
	__uid_t volatile   uk_uid;   /* Access to real uid (`getuid()' / `setuid()') of the calling process */
	__USERKERN_PAD_UID(__uk_pad5)
	__gid_t volatile   uk_gid;   /* Access to real gid (`getgid()' / `setgid()') of the calling process */
	__USERKERN_PAD_GID(__uk_pad6)
	__uid_t volatile   uk_euid;  /* Access to effective uid (`geteuid()' / `seteuid()') of the calling process */
	__USERKERN_PAD_UID(__uk_pad7)
	__gid_t volatile   uk_egid;  /* Access to effective gid (`getegid()' / `setegid()') of the calling process */
	__USERKERN_PAD_GID(__uk_pad8)
	__uid_t volatile   uk_suid;  /* Access to saved uid of the calling process */
	__USERKERN_PAD_UID(__uk_pad9)
	__gid_t volatile   uk_sgid;  /* Access to saved gid of the calling process */
	__USERKERN_PAD_GID(__uk_pad10)
	struct ucpustate   uk_regs;  /* Your current register  state. (essentially, this  is can  be
	                              * used as a memory-mapped copy of your current register state) */
	/* TODO: Thread priority/scheduling control */
	/* TODO: Thread I/O permission control (ioperm) */
};
#undef __USERKERN_PAD_GID
#undef __USERKERN_PAD_UID
#undef __USERKERN_PAD_PID
#endif /* __CC__ */

#endif /* !_KOS_BITS_UKERN_STRUCT_H */
