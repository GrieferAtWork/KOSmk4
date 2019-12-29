/* HASH CRC-32:0x511b6569 */
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_WRAPPERS32_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_WRAPPERS32_S 1

#include <kernel/compiler.h>

#include <asm/cfi.h>
#include <kos/kernel/gdt.h>
#include <kos/kernel/paging.h>
#include <kernel/arch/syscall.h>

EXTERN(__asm32_bad_sysenter_extension)










/* errno_t restart_syscall(void) */
.section .text.x86.asm32_syscall_int80.restart_syscall
INTERN_WEAK_FUNCTION(__x86_asm32_int80_restart_syscall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_restart_syscall)
	call   sys_restart_syscall
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_restart_syscall)

/* void exit(syscall_ulong_t status) */
.section .text.x86.asm32_syscall_int80.exit
INTERN_WEAK_FUNCTION(__x86_asm32_int80_exit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_exit)
	call   sys_exit
	.cfi_endproc
END(__x86_asm32_int80_exit)

/* pid_t fork(void) */
.section .text.x86.asm32_syscall_int80.fork
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fork)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_fork)
	call   sys_fork
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fork)

/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_int80.read
INTERN_WEAK_FUNCTION(__x86_asm32_int80_read)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_read)
	call   sys_read
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_read)

/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_int80.write
INTERN_WEAK_FUNCTION(__x86_asm32_int80_write)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_write)
	call   sys_write
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_write)

/* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
.section .text.x86.asm32_syscall_int80.open
INTERN_WEAK_FUNCTION(__x86_asm32_int80_open)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_open)
	call   sys_open
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_open)

/* Close a given file descriptor/handle `FD' */
/* errno_t close(fd_t fd) */
.section .text.x86.asm32_syscall_int80.close
INTERN_WEAK_FUNCTION(__x86_asm32_int80_close)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_close)
	call   sys_close
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_close)

/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t waitpid(pid_t pid, int32_t *stat_loc, syscall_ulong_t options) */
.section .text.x86.asm32_syscall_int80.waitpid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_waitpid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_waitpid)
	call   sys_waitpid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_waitpid)

/* fd_t creat(char const *filename, mode_t mode) */
.section .text.x86.asm32_syscall_int80.creat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_creat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_creat)
	call   sys_creat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_creat)

/* errno_t link(char const *existing_file, char const *link_file) */
.section .text.x86.asm32_syscall_int80.link
INTERN_WEAK_FUNCTION(__x86_asm32_int80_link)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_link)
	call   sys_link
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_link)

/* errno_t unlink(char const *filename) */
.section .text.x86.asm32_syscall_int80.unlink
INTERN_WEAK_FUNCTION(__x86_asm32_int80_unlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xa
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_unlink)
	call   sys_unlink
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_unlink)

/* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
.section .text.x86.asm32_syscall_int80.execve
INTERN_WEAK_FUNCTION(__x86_asm32_int80_execve)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xb
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_execve)
	call   sys_execve
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_execve)

/* errno_t chdir(char const *path) */
.section .text.x86.asm32_syscall_int80.chdir
INTERN_WEAK_FUNCTION(__x86_asm32_int80_chdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xc
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_chdir)
	call   sys_chdir
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_chdir)

/* int32_t time(int32_t *timer) */
.section .text.x86.asm32_syscall_int80.time
INTERN_WEAK_FUNCTION(__x86_asm32_int80_time)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xd
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_time)
	call   sys_time
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_time)

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
.section .text.x86.asm32_syscall_int80.mknod
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mknod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xe
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mknod)
	call   sys_mknod
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mknod)

/* errno_t chmod(char const *filename, mode_t mode) */
.section .text.x86.asm32_syscall_int80.chmod
INTERN_WEAK_FUNCTION(__x86_asm32_int80_chmod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xf
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_chmod)
	call   sys_chmod
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_chmod)

/* errno_t lchown(char const *filename, uint16_t owner, uint16_t group) */
.section .text.x86.asm32_syscall_int80.lchown
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lchown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x10
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lchown)
	call   sys_lchown
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_lchown)

/* errno_t break(void) */
.section .text.x86.asm32_syscall_int80.break
INTERN_WEAK_FUNCTION(__x86_asm32_int80_break)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x11
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_break)
	call   sys_break
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_break)

/* errno_t linux_oldstat(char const *filename, struct linux_oldstat *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_oldstat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_oldstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x12
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_oldstat)
	call   sys_linux_oldstat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_linux_oldstat)

/* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
.section .text.x86.asm32_syscall_int80.lseek
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lseek)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x13
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lseek)
	call   sys_lseek
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_lseek)

/* pid_t getpid(void) */
.section .text.x86.asm32_syscall_int80.getpid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getpid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x14
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getpid)
	call   sys_getpid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getpid)

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t rwflag, void const *data) */
.section .text.x86.asm32_syscall_int80.mount
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mount)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x15
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mount)
	call   sys_mount
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mount)

/* errno_t umount(char const *special_file) */
.section .text.x86.asm32_syscall_int80.umount
INTERN_WEAK_FUNCTION(__x86_asm32_int80_umount)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x16
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_umount)
	call   sys_umount
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_umount)

/* errno_t setuid(uint16_t uid) */
.section .text.x86.asm32_syscall_int80.setuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x17
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setuid)
	call   sys_setuid
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setuid)

/* uint16_t getuid(void) */
.section .text.x86.asm32_syscall_int80.getuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x18
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getuid)
	call   sys_getuid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getuid)

/* errno_t stime(time32_t const *t) */
.section .text.x86.asm32_syscall_int80.stime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_stime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x19
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_stime)
	call   sys_stime
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_stime)

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
.section .text.x86.asm32_syscall_int80.ptrace
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ptrace)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x1a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ptrace)
	call   sys_ptrace
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ptrace)

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
.section .text.x86.asm32_syscall_int80.alarm
INTERN_WEAK_FUNCTION(__x86_asm32_int80_alarm)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x1b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_alarm)
	call   sys_alarm
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_alarm)

/* errno_t linux_oldfstat(fd_t fd, struct linux_oldstat *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_oldfstat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_oldfstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x1c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_oldfstat)
	call   sys_linux_oldfstat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_linux_oldfstat)

/* errno_t pause(void) */
.section .text.x86.asm32_syscall_int80.pause
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pause)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x1d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_pause)
	call   sys_pause
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_pause)

/* errno_t utime(char const *filename, struct __utimbuf32 const *times) */
.section .text.x86.asm32_syscall_int80.utime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_utime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x1e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_utime)
	call   sys_utime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_utime)

/* errno_t stty(void) */
.section .text.x86.asm32_syscall_int80.stty
INTERN_WEAK_FUNCTION(__x86_asm32_int80_stty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x1f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_stty)
	call   sys_stty
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_stty)

/* errno_t gtty(void) */
.section .text.x86.asm32_syscall_int80.gtty
INTERN_WEAK_FUNCTION(__x86_asm32_int80_gtty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x20
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_gtty)
	call   sys_gtty
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_gtty)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
.section .text.x86.asm32_syscall_int80.access
INTERN_WEAK_FUNCTION(__x86_asm32_int80_access)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x21
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_access)
	call   sys_access
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_access)

/* errno_t nice(syscall_slong_t inc) */
.section .text.x86.asm32_syscall_int80.nice
INTERN_WEAK_FUNCTION(__x86_asm32_int80_nice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x22
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_nice)
	call   sys_nice
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_nice)

/* errno_t ftime(struct __timebx32 *tp) */
.section .text.x86.asm32_syscall_int80.ftime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ftime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x23
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ftime)
	call   sys_ftime
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ftime)

/* errno_t sync(void) */
.section .text.x86.asm32_syscall_int80.sync
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x24
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_sync)
	call   sys_sync
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sync)

/* @param: signo: One of `SIG*' */
/* errno_t kill(pid_t pid, syscall_ulong_t signo) */
.section .text.x86.asm32_syscall_int80.kill
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x25
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kill)
	call   sys_kill
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_kill)

/* errno_t rename(char const *oldname, char const *newname_or_path) */
.section .text.x86.asm32_syscall_int80.rename
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rename)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x26
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rename)
	call   sys_rename
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_rename)

/* errno_t mkdir(char const *pathname, mode_t mode) */
.section .text.x86.asm32_syscall_int80.mkdir
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mkdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x27
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mkdir)
	call   sys_mkdir
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mkdir)

/* errno_t rmdir(char const *path) */
.section .text.x86.asm32_syscall_int80.rmdir
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rmdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x28
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rmdir)
	call   sys_rmdir
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_rmdir)

/* fd_t dup(fd_t fd) */
.section .text.x86.asm32_syscall_int80.dup
INTERN_WEAK_FUNCTION(__x86_asm32_int80_dup)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x29
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_dup)
	call   sys_dup
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_dup)

/* errno_t pipe(fd_t[2] pipedes) */
.section .text.x86.asm32_syscall_int80.pipe
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pipe)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x2a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pipe)
	call   sys_pipe
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_pipe)

/* clock_t times(struct tms *buf) */
.section .text.x86.asm32_syscall_int80.times
INTERN_WEAK_FUNCTION(__x86_asm32_int80_times)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x2b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_times)
	call   sys_times
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_times)

/* errno_t prof(void) */
.section .text.x86.asm32_syscall_int80.prof
INTERN_WEAK_FUNCTION(__x86_asm32_int80_prof)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x2c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_prof)
	call   sys_prof
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_prof)

/* errno_t brk(void *addr) */
.section .text.x86.asm32_syscall_int80.brk
INTERN_WEAK_FUNCTION(__x86_asm32_int80_brk)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x2d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_brk)
	call   sys_brk
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_brk)

/* errno_t setgid(uint16_t gid) */
.section .text.x86.asm32_syscall_int80.setgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x2e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setgid)
	call   sys_setgid
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setgid)

/* uint16_t getgid(void) */
.section .text.x86.asm32_syscall_int80.getgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x2f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getgid)
	call   sys_getgid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getgid)

/* @param: signo: One of `SIG*' */
/* sighandler_t signal(syscall_ulong_t signo, sighandler_t handler) */
.section .text.x86.asm32_syscall_int80.signal
INTERN_WEAK_FUNCTION(__x86_asm32_int80_signal)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x30
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_signal)
	call   sys_signal
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_signal)

/* uint16_t geteuid(void) */
.section .text.x86.asm32_syscall_int80.geteuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_geteuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x31
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_geteuid)
	call   sys_geteuid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_geteuid)

/* uint16_t getegid(void) */
.section .text.x86.asm32_syscall_int80.getegid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getegid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x32
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getegid)
	call   sys_getegid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getegid)

/* errno_t acct(char const *filename) */
.section .text.x86.asm32_syscall_int80.acct
INTERN_WEAK_FUNCTION(__x86_asm32_int80_acct)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x33
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_acct)
	call   sys_acct
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_acct)

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.umount2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_umount2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x34
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_umount2)
	call   sys_umount2
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_umount2)

/* errno_t lock(void) */
.section .text.x86.asm32_syscall_int80.lock
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x35
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_lock)
	call   sys_lock
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_lock)

/* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t request, void *arg) */
.section .text.x86.asm32_syscall_int80.ioctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ioctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x36
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ioctl)
	call   sys_ioctl
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ioctl)

/* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t cmd, void *arg) */
.section .text.x86.asm32_syscall_int80.fcntl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fcntl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x37
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fcntl)
	call   sys_fcntl
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fcntl)

/* errno_t mpx(void) */
.section .text.x86.asm32_syscall_int80.mpx
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mpx)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x38
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_mpx)
	call   sys_mpx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mpx)

/* errno_t setpgid(pid_t pid, pid_t pgid) */
.section .text.x86.asm32_syscall_int80.setpgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setpgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x39
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setpgid)
	call   sys_setpgid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setpgid)

/* errno_t ulimit(void) */
.section .text.x86.asm32_syscall_int80.ulimit
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ulimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x3a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_ulimit)
	call   sys_ulimit
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ulimit)

/* errno_t oldolduname(struct linux_oldolduname *name) */
.section .text.x86.asm32_syscall_int80.oldolduname
INTERN_WEAK_FUNCTION(__x86_asm32_int80_oldolduname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x3b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_oldolduname)
	call   sys_oldolduname
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_oldolduname)

/* mode_t umask(mode_t mode) */
.section .text.x86.asm32_syscall_int80.umask
INTERN_WEAK_FUNCTION(__x86_asm32_int80_umask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x3c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_umask)
	call   sys_umask
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_umask)

/* errno_t chroot(char const *path) */
.section .text.x86.asm32_syscall_int80.chroot
INTERN_WEAK_FUNCTION(__x86_asm32_int80_chroot)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x3d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_chroot)
	call   sys_chroot
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_chroot)

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
.section .text.x86.asm32_syscall_int80.ustat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ustat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x3e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ustat)
	call   sys_ustat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ustat)

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
.section .text.x86.asm32_syscall_int80.dup2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_dup2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x3f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_dup2)
	call   sys_dup2
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_dup2)

/* pid_t getppid(void) */
.section .text.x86.asm32_syscall_int80.getppid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getppid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x40
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getppid)
	call   sys_getppid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getppid)

/* pid_t getpgrp(void) */
.section .text.x86.asm32_syscall_int80.getpgrp
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getpgrp)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x41
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getpgrp)
	call   sys_getpgrp
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getpgrp)

/* pid_t setsid(void) */
.section .text.x86.asm32_syscall_int80.setsid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setsid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x42
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_setsid)
	call   sys_setsid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setsid)

/* errno_t sigaction(syscall_ulong_t signo, struct sigaction32 const *act, struct sigaction32 *oact) */
.section .text.x86.asm32_syscall_int80.sigaction
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sigaction)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x43
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sigaction)
	call   sys_sigaction
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sigaction)

/* syscall_ulong_t sgetmask(void) */
.section .text.x86.asm32_syscall_int80.sgetmask
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sgetmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x44
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_sgetmask)
	call   sys_sgetmask
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sgetmask)

/* syscall_ulong_t ssetmask(syscall_ulong_t sigmask) */
.section .text.x86.asm32_syscall_int80.ssetmask
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ssetmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x45
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ssetmask)
	call   sys_ssetmask
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ssetmask)

/* errno_t setreuid(uint16_t ruid, uint16_t euid) */
.section .text.x86.asm32_syscall_int80.setreuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setreuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x46
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setreuid)
	call   sys_setreuid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setreuid)

/* errno_t setregid(uint16_t rgid, uint16_t egid) */
.section .text.x86.asm32_syscall_int80.setregid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setregid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x47
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setregid)
	call   sys_setregid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setregid)

/* errno_t sigsuspend(struct __sigset_struct const *set) */
.section .text.x86.asm32_syscall_int80.sigsuspend
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sigsuspend)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x48
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sigsuspend)
	call   sys_sigsuspend
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sigsuspend)

/* errno_t sigpending(struct __sigset_struct *set) */
.section .text.x86.asm32_syscall_int80.sigpending
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sigpending)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x49
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sigpending)
	call   sys_sigpending
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sigpending)

/* errno_t sethostname(char const *name, size_t len) */
.section .text.x86.asm32_syscall_int80.sethostname
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sethostname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x4a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sethostname)
	call   sys_sethostname
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sethostname)

/* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
.section .text.x86.asm32_syscall_int80.setrlimit
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setrlimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x4b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setrlimit)
	call   sys_setrlimit
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setrlimit)

/* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
.section .text.x86.asm32_syscall_int80.getrlimit
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getrlimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x4c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getrlimit)
	call   sys_getrlimit
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getrlimit)

/* errno_t getrusage(syscall_slong_t who, struct __rusagex32 *tv) */
.section .text.x86.asm32_syscall_int80.getrusage
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getrusage)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x4d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getrusage)
	call   sys_getrusage
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getrusage)

/* errno_t gettimeofday(struct __timevalx32 *tv, struct timezone *tz) */
.section .text.x86.asm32_syscall_int80.gettimeofday
INTERN_WEAK_FUNCTION(__x86_asm32_int80_gettimeofday)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x4e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_gettimeofday)
	call   sys_gettimeofday
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_gettimeofday)

/* errno_t settimeofday(struct __timevalx32 const *tv, struct timezone const *tz) */
.section .text.x86.asm32_syscall_int80.settimeofday
INTERN_WEAK_FUNCTION(__x86_asm32_int80_settimeofday)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x4f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_settimeofday)
	call   sys_settimeofday
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_settimeofday)

/* errno_t getgroups(size_t size, uint16_t[] list) */
.section .text.x86.asm32_syscall_int80.getgroups
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getgroups)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x50
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getgroups)
	call   sys_getgroups
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getgroups)

/* errno_t setgroups(size_t count, uint16_t const *groups) */
.section .text.x86.asm32_syscall_int80.setgroups
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setgroups)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x51
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setgroups)
	call   sys_setgroups
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setgroups)

/* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timevalx32 *timeout) */
.section .text.x86.asm32_syscall_int80.select
INTERN_WEAK_FUNCTION(__x86_asm32_int80_select)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x52
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_select)
	call   sys_select
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_select)

/* errno_t symlink(char const *link_text, char const *target_path) */
.section .text.x86.asm32_syscall_int80.symlink
INTERN_WEAK_FUNCTION(__x86_asm32_int80_symlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x53
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_symlink)
	call   sys_symlink
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_symlink)

/* errno_t linux_oldlstat(char const *filename, struct linux_oldstat *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_oldlstat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_oldlstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x54
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_oldlstat)
	call   sys_linux_oldlstat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_linux_oldlstat)

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
.section .text.x86.asm32_syscall_int80.readlink
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x55
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readlink)
	call   sys_readlink
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_readlink)

/* errno_t uselib(char const *library) */
.section .text.x86.asm32_syscall_int80.uselib
INTERN_WEAK_FUNCTION(__x86_asm32_int80_uselib)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x56
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_uselib)
	call   sys_uselib
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_uselib)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
.section .text.x86.asm32_syscall_int80.swapon
INTERN_WEAK_FUNCTION(__x86_asm32_int80_swapon)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x57
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_swapon)
	call   sys_swapon
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_swapon)

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
.section .text.x86.asm32_syscall_int80.reboot
INTERN_WEAK_FUNCTION(__x86_asm32_int80_reboot)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x58
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_reboot)
	call   sys_reboot
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_reboot)

/* Returns `0' to indicate end-of-directory; 1 to to indicate success */
/* errno_t readdir(fd_t fd, struct old_linux_dirent *dirp, size_t count) */
.section .text.x86.asm32_syscall_int80.readdir
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x59
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readdir)
	call   sys_readdir
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_readdir)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
.section .text.x86.asm32_syscall_int80.mmap
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mmap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x5a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mmap)
	call   sys_mmap
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mmap)

/* errno_t munmap(void *addr, size_t len) */
.section .text.x86.asm32_syscall_int80.munmap
INTERN_WEAK_FUNCTION(__x86_asm32_int80_munmap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x5b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_munmap)
	call   sys_munmap
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_munmap)

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
.section .text.x86.asm32_syscall_int80.truncate
INTERN_WEAK_FUNCTION(__x86_asm32_int80_truncate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x5c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_truncate)
	call   sys_truncate
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_truncate)

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
.section .text.x86.asm32_syscall_int80.ftruncate
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ftruncate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x5d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ftruncate)
	call   sys_ftruncate
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ftruncate)

/* errno_t fchmod(fd_t fd, mode_t mode) */
.section .text.x86.asm32_syscall_int80.fchmod
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchmod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x5e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchmod)
	call   sys_fchmod
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fchmod)

/* errno_t fchown(fd_t fd, uint16_t owner, uint16_t group) */
.section .text.x86.asm32_syscall_int80.fchown
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x5f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchown)
	call   sys_fchown
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fchown)

/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
.section .text.x86.asm32_syscall_int80.getpriority
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getpriority)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x60
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getpriority)
	call   sys_getpriority
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getpriority)

/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
.section .text.x86.asm32_syscall_int80.setpriority
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setpriority)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x61
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setpriority)
	call   sys_setpriority
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setpriority)

/* errno_t profil(uint16_t *sample_buffer, size_t size, size_t offset, syscall_ulong_t scale) */
.section .text.x86.asm32_syscall_int80.profil
INTERN_WEAK_FUNCTION(__x86_asm32_int80_profil)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x62
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_profil)
	call   sys_profil
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_profil)

/* errno_t statfs(char const *file, struct __statfs32 *buf) */
.section .text.x86.asm32_syscall_int80.statfs
INTERN_WEAK_FUNCTION(__x86_asm32_int80_statfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x63
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_statfs)
	call   sys_statfs
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_statfs)

/* errno_t fstatfs(fd_t file, struct __statfs32 *buf) */
.section .text.x86.asm32_syscall_int80.fstatfs
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fstatfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x64
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fstatfs)
	call   sys_fstatfs
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fstatfs)

/* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
.section .text.x86.asm32_syscall_int80.ioperm
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ioperm)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x65
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ioperm)
	call   sys_ioperm
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ioperm)

/* errno_t socketcall(int call, unsigned long *args) */
.section .text.x86.asm32_syscall_int80.socketcall
INTERN_WEAK_FUNCTION(__x86_asm32_int80_socketcall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x66
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_socketcall)
	call   sys_socketcall
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_socketcall)

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
.section .text.x86.asm32_syscall_int80.syslog
INTERN_WEAK_FUNCTION(__x86_asm32_int80_syslog)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x67
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_syslog)
	call   sys_syslog
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_syslog)

/* errno_t setitimer(syscall_ulong_t which, struct __itimerval32 const *newval, struct __itimerval32 *oldval) */
.section .text.x86.asm32_syscall_int80.setitimer
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setitimer)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x68
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setitimer)
	call   sys_setitimer
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setitimer)

/* errno_t getitimer(syscall_ulong_t which, struct __itimerval32 *curr_value) */
.section .text.x86.asm32_syscall_int80.getitimer
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getitimer)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x69
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getitimer)
	call   sys_getitimer
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getitimer)

/* errno_t linux_stat32(char const *filename, struct linux_stat32 *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_stat32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_stat32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x6a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_stat32)
	call   sys_linux_stat32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_linux_stat32)

/* errno_t linux_lstat32(char const *filename, struct linux_stat32 *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_lstat32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_lstat32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x6b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_lstat32)
	call   sys_linux_lstat32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_linux_lstat32)

/* errno_t linux_fstat32(fd_t fd, struct linux_stat32 *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_fstat32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_fstat32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x6c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_fstat32)
	call   sys_linux_fstat32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_linux_fstat32)

/* errno_t olduname(struct linux_olduname *name) */
.section .text.x86.asm32_syscall_int80.olduname
INTERN_WEAK_FUNCTION(__x86_asm32_int80_olduname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x6d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_olduname)
	call   sys_olduname
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_olduname)

/* errno_t iopl(syscall_ulong_t level) */
.section .text.x86.asm32_syscall_int80.iopl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_iopl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x6e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_iopl)
	call   sys_iopl
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_iopl)

/* errno_t vhangup(void) */
.section .text.x86.asm32_syscall_int80.vhangup
INTERN_WEAK_FUNCTION(__x86_asm32_int80_vhangup)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x6f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_vhangup)
	call   sys_vhangup
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_vhangup)

/* errno_t idle(void) */
.section .text.x86.asm32_syscall_int80.idle
INTERN_WEAK_FUNCTION(__x86_asm32_int80_idle)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x70
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_idle)
	call   sys_idle
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_idle)

/* errno_t vm86old(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.vm86old
INTERN_WEAK_FUNCTION(__x86_asm32_int80_vm86old)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x71
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_vm86old)
	call   sys_vm86old
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_vm86old)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct __rusagex32 *usage) */
.section .text.x86.asm32_syscall_int80.wait4
INTERN_WEAK_FUNCTION(__x86_asm32_int80_wait4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x72
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_wait4)
	call   sys_wait4
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_wait4)

/* errno_t swapoff(char const *pathname) */
.section .text.x86.asm32_syscall_int80.swapoff
INTERN_WEAK_FUNCTION(__x86_asm32_int80_swapoff)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x73
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_swapoff)
	call   sys_swapoff
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_swapoff)

/* errno_t sysinfo(struct sysinfo *info) */
.section .text.x86.asm32_syscall_int80.sysinfo
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sysinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x74
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sysinfo)
	call   sys_sysinfo
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sysinfo)

/* errno_t ipc(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.ipc
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ipc)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x75
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ipc)
	call   sys_ipc
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ipc)

/* errno_t fsync(fd_t fd) */
.section .text.x86.asm32_syscall_int80.fsync
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fsync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x76
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fsync)
	call   sys_fsync
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fsync)

/* Restore the specified register state when returning from a signal handler
 * Note that the order and locations of arguments taken by this system call
 * are of great importance, as they must match what is encoded by the kernel
 * within `sighand_raise_signal()'
 * The order chosen is also important, as it is selected such that arguments
 * are only passed through registers that are preserved by CDECL */
/* void sigreturn(struct fpustate32 const *restore_fpu, syscall_ulong_t unused1, syscall_ulong_t unused2, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info32 *sc_info, struct ucpustate32 const *restore_cpu) */
.section .text.x86.asm32_syscall_int80.sigreturn
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sigreturn)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x77
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sigreturn)
	call   sys_sigreturn
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sigreturn)

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, uintptr_t newtls, pid_t *ctid) */
.section .text.x86.asm32_syscall_int80.clone
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clone)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x78
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clone)
	call   sys_clone
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_clone)

/* errno_t setdomainname(char const *name, size_t len) */
.section .text.x86.asm32_syscall_int80.setdomainname
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setdomainname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x79
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setdomainname)
	call   sys_setdomainname
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setdomainname)

/* errno_t uname(struct utsname *name) */
.section .text.x86.asm32_syscall_int80.uname
INTERN_WEAK_FUNCTION(__x86_asm32_int80_uname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x7a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_uname)
	call   sys_uname
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_uname)

/* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
.section .text.x86.asm32_syscall_int80.modify_ldt
INTERN_WEAK_FUNCTION(__x86_asm32_int80_modify_ldt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x7b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_modify_ldt)
	call   sys_modify_ldt
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_modify_ldt)

/* errno_t adjtimex(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.adjtimex
INTERN_WEAK_FUNCTION(__x86_asm32_int80_adjtimex)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x7c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_adjtimex)
	call   sys_adjtimex
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_adjtimex)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
.section .text.x86.asm32_syscall_int80.mprotect
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mprotect)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x7d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mprotect)
	call   sys_mprotect
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mprotect)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset) */
.section .text.x86.asm32_syscall_int80.sigprocmask
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sigprocmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x7e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sigprocmask)
	call   sys_sigprocmask
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sigprocmask)

/* errno_t create_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.create_module
INTERN_WEAK_FUNCTION(__x86_asm32_int80_create_module)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x7f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_create_module)
	call   sys_create_module
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_create_module)

/* errno_t init_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.init_module
INTERN_WEAK_FUNCTION(__x86_asm32_int80_init_module)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_init_module)
	call   sys_init_module
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_init_module)

/* errno_t delete_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.delete_module
INTERN_WEAK_FUNCTION(__x86_asm32_int80_delete_module)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x81
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_delete_module)
	call   sys_delete_module
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_delete_module)

/* errno_t get_kernel_syms(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.get_kernel_syms
INTERN_WEAK_FUNCTION(__x86_asm32_int80_get_kernel_syms)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x82
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_get_kernel_syms)
	call   sys_get_kernel_syms
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_get_kernel_syms)

/* errno_t quotactl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.quotactl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_quotactl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x83
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_quotactl)
	call   sys_quotactl
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_quotactl)

/* pid_t getpgid(pid_t pid) */
.section .text.x86.asm32_syscall_int80.getpgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getpgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x84
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getpgid)
	call   sys_getpgid
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getpgid)

/* errno_t fchdir(fd_t fd) */
.section .text.x86.asm32_syscall_int80.fchdir
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x85
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchdir)
	call   sys_fchdir
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fchdir)

/* errno_t bdflush(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.bdflush
INTERN_WEAK_FUNCTION(__x86_asm32_int80_bdflush)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x86
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_bdflush)
	call   sys_bdflush
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_bdflush)

/* errno_t sysfs(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.sysfs
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sysfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x87
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sysfs)
	call   sys_sysfs
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sysfs)

/* errno_t personality(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.personality
INTERN_WEAK_FUNCTION(__x86_asm32_int80_personality)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x88
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_personality)
	call   sys_personality
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_personality)

/* errno_t afs_syscall(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.afs_syscall
INTERN_WEAK_FUNCTION(__x86_asm32_int80_afs_syscall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x89
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_afs_syscall)
	call   sys_afs_syscall
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_afs_syscall)

/* errno_t setfsuid(uint16_t uid) */
.section .text.x86.asm32_syscall_int80.setfsuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setfsuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setfsuid)
	call   sys_setfsuid
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setfsuid)

/* errno_t setfsgid(uint16_t gid) */
.section .text.x86.asm32_syscall_int80.setfsgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setfsgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setfsgid)
	call   sys_setfsgid
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setfsgid)

/* errno_t _llseek(fd_t fd, int64_t offset, uint64_t *result, syscall_ulong_t whence) */
.section .text.x86.asm32_syscall_int80._llseek
INTERN_WEAK_FUNCTION(__x86_asm32_int80__llseek)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys__llseek)
	call   sys__llseek
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80__llseek)

/* ssize_t getdents(fd_t fd, struct linux_dirent *dirp, size_t count) */
.section .text.x86.asm32_syscall_int80.getdents
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getdents)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getdents)
	call   sys_getdents
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getdents)

/* errno_t _newselect(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80._newselect
INTERN_WEAK_FUNCTION(__x86_asm32_int80__newselect)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys__newselect)
	call   sys__newselect
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80__newselect)

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
.section .text.x86.asm32_syscall_int80.flock
INTERN_WEAK_FUNCTION(__x86_asm32_int80_flock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_flock)
	call   sys_flock
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_flock)

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.msync
INTERN_WEAK_FUNCTION(__x86_asm32_int80_msync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x90
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_msync)
	call   sys_msync
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_msync)

/* ssize_t readv(fd_t fd, struct iovec32 const *iovec, size_t count) */
.section .text.x86.asm32_syscall_int80.readv
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x91
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readv)
	call   sys_readv
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_readv)

/* ssize_t writev(fd_t fd, struct iovec32 const *iovec, size_t count) */
.section .text.x86.asm32_syscall_int80.writev
INTERN_WEAK_FUNCTION(__x86_asm32_int80_writev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x92
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_writev)
	call   sys_writev
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_writev)

/* pid_t getsid(pid_t pid) */
.section .text.x86.asm32_syscall_int80.getsid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getsid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x93
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getsid)
	call   sys_getsid
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getsid)

/* errno_t fdatasync(fd_t fd) */
.section .text.x86.asm32_syscall_int80.fdatasync
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fdatasync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x94
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fdatasync)
	call   sys_fdatasync
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fdatasync)

/* errno_t _sysctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80._sysctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80__sysctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x95
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys__sysctl)
	call   sys__sysctl
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80__sysctl)

/* errno_t mlock(void const *addr, size_t len) */
.section .text.x86.asm32_syscall_int80.mlock
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mlock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x96
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mlock)
	call   sys_mlock
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mlock)

/* errno_t munlock(void const *addr, size_t len) */
.section .text.x86.asm32_syscall_int80.munlock
INTERN_WEAK_FUNCTION(__x86_asm32_int80_munlock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x97
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_munlock)
	call   sys_munlock
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_munlock)

/* errno_t mlockall(syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.mlockall
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mlockall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x98
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mlockall)
	call   sys_mlockall
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mlockall)

/* errno_t munlockall(void) */
.section .text.x86.asm32_syscall_int80.munlockall
INTERN_WEAK_FUNCTION(__x86_asm32_int80_munlockall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x99
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_munlockall)
	call   sys_munlockall
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_munlockall)

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
.section .text.x86.asm32_syscall_int80.sched_setparam
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_setparam)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x9a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_setparam)
	call   sys_sched_setparam
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sched_setparam)

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
.section .text.x86.asm32_syscall_int80.sched_getparam
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_getparam)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x9b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_getparam)
	call   sys_sched_getparam
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sched_getparam)

/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
.section .text.x86.asm32_syscall_int80.sched_setscheduler
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_setscheduler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x9c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_setscheduler)
	call   sys_sched_setscheduler
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sched_setscheduler)

/* syscall_slong_t sched_getscheduler(pid_t pid) */
.section .text.x86.asm32_syscall_int80.sched_getscheduler
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_getscheduler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x9d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_getscheduler)
	call   sys_sched_getscheduler
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sched_getscheduler)

/* errno_t sched_yield(void) */
.section .text.x86.asm32_syscall_int80.sched_yield
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_yield)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x9e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_sched_yield)
	call   sys_sched_yield
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sched_yield)

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
.section .text.x86.asm32_syscall_int80.sched_get_priority_max
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_get_priority_max)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x9f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_get_priority_max)
	call   sys_sched_get_priority_max
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sched_get_priority_max)

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
.section .text.x86.asm32_syscall_int80.sched_get_priority_min
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_get_priority_min)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xa0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_get_priority_min)
	call   sys_sched_get_priority_min
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sched_get_priority_min)

/* errno_t sched_rr_get_interval(pid_t pid, struct __timespecx32 *tms) */
.section .text.x86.asm32_syscall_int80.sched_rr_get_interval
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_rr_get_interval)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xa1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_rr_get_interval)
	call   sys_sched_rr_get_interval
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sched_rr_get_interval)

/* errno_t nanosleep(struct __timespecx32 const *req, struct __timespecx32 *rem) */
.section .text.x86.asm32_syscall_int80.nanosleep
INTERN_WEAK_FUNCTION(__x86_asm32_int80_nanosleep)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xa2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_nanosleep)
	call   sys_nanosleep
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_nanosleep)

/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
.section .text.x86.asm32_syscall_int80.mremap
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mremap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xa3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mremap)
	call   sys_mremap
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mremap)

/* errno_t setresuid(uint16_t ruid, uint16_t euid, uint16_t suid) */
.section .text.x86.asm32_syscall_int80.setresuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setresuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xa4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setresuid)
	call   sys_setresuid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setresuid)

/* errno_t getresuid(uint16_t *ruid, uint16_t *euid, uint16_t *suid) */
.section .text.x86.asm32_syscall_int80.getresuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getresuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xa5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getresuid)
	call   sys_getresuid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getresuid)

/* errno_t vm86(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.vm86
INTERN_WEAK_FUNCTION(__x86_asm32_int80_vm86)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xa6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_vm86)
	call   sys_vm86
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_vm86)

/* errno_t query_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.query_module
INTERN_WEAK_FUNCTION(__x86_asm32_int80_query_module)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xa7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_query_module)
	call   sys_query_module
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_query_module)

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
.section .text.x86.asm32_syscall_int80.poll
INTERN_WEAK_FUNCTION(__x86_asm32_int80_poll)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xa8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_poll)
	call   sys_poll
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_poll)

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.nfsservctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_nfsservctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xa9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_nfsservctl)
	call   sys_nfsservctl
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_nfsservctl)

/* errno_t setresgid(uint16_t rgid, uint16_t egid, uint16_t sgid) */
.section .text.x86.asm32_syscall_int80.setresgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setresgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xaa
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setresgid)
	call   sys_setresgid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setresgid)

/* errno_t getresgid(uint16_t *rgid, uint16_t *egid, uint16_t *sgid) */
.section .text.x86.asm32_syscall_int80.getresgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getresgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xab
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getresgid)
	call   sys_getresgid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getresgid)

/* errno_t prctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.prctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_prctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xac
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_prctl)
	call   sys_prctl
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_prctl)

/* void rt_sigreturn(struct fpustate const *restore_fpu, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info *sc_info, struct ucpustate const *restore_cpu) */
.section .text.x86.asm32_syscall_int80.rt_sigreturn
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigreturn)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xad
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigreturn)
	call   sys_rt_sigreturn
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_rt_sigreturn)

/* errno_t rt_sigaction(syscall_ulong_t signo, struct sigaction32 const *act, struct sigaction32 *oact, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.rt_sigaction
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigaction)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xae
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigaction)
	call   sys_rt_sigaction
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_rt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.rt_sigprocmask
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigprocmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xaf
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigprocmask)
	call   sys_rt_sigprocmask
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_rt_sigprocmask)

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.rt_sigpending
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigpending)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xb0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigpending)
	call   sys_rt_sigpending
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_rt_sigpending)

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo32_struct *info, struct __timespecx32 const *timeout, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.rt_sigtimedwait
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigtimedwait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xb1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigtimedwait)
	call   sys_rt_sigtimedwait
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_rt_sigtimedwait)

/* @param: signo: One of `SIG*' */
/* errno_t rt_sigqueueinfo(pid_t tgid, syscall_ulong_t signo, struct __siginfo32_struct const *uinfo) */
.section .text.x86.asm32_syscall_int80.rt_sigqueueinfo
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigqueueinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xb2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigqueueinfo)
	call   sys_rt_sigqueueinfo
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_rt_sigqueueinfo)

/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.rt_sigsuspend
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigsuspend)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xb3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigsuspend)
	call   sys_rt_sigsuspend
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_rt_sigsuspend)

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
.section .text.x86.asm32_syscall_int80.pread64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pread64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xb4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pread64)
	call   sys_pread64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_pread64)

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
.section .text.x86.asm32_syscall_int80.pwrite64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pwrite64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xb5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pwrite64)
	call   sys_pwrite64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_pwrite64)

/* errno_t chown(char const *filename, uint16_t owner, uint16_t group) */
.section .text.x86.asm32_syscall_int80.chown
INTERN_WEAK_FUNCTION(__x86_asm32_int80_chown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xb6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_chown)
	call   sys_chown
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_chown)

/* ssize_t getcwd(char *buf, size_t size) */
.section .text.x86.asm32_syscall_int80.getcwd
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getcwd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xb7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getcwd)
	call   sys_getcwd
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getcwd)

/* errno_t capget(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.capget
INTERN_WEAK_FUNCTION(__x86_asm32_int80_capget)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xb8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_capget)
	call   sys_capget
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_capget)

/* errno_t capset(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.capset
INTERN_WEAK_FUNCTION(__x86_asm32_int80_capset)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xb9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_capset)
	call   sys_capset
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_capset)

/* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
.section .text.x86.asm32_syscall_int80.sigaltstack
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sigaltstack)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xba
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sigaltstack)
	call   sys_sigaltstack
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sigaltstack)

/* ssize_t sendfile(fd_t out_fd, fd_t in_fd, syscall_ulong_t *offset, size_t count) */
.section .text.x86.asm32_syscall_int80.sendfile
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sendfile)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xbb
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sendfile)
	call   sys_sendfile
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sendfile)

/* errno_t getpmsg(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.getpmsg
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getpmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xbc
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getpmsg)
	call   sys_getpmsg
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getpmsg)

/* errno_t putpmsg(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.putpmsg
INTERN_WEAK_FUNCTION(__x86_asm32_int80_putpmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xbd
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_putpmsg)
	call   sys_putpmsg
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_putpmsg)

/* pid_t vfork(void) */
.section .text.x86.asm32_syscall_int80.vfork
INTERN_WEAK_FUNCTION(__x86_asm32_int80_vfork)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xbe
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_vfork)
	call   sys_vfork
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_vfork)

/* errno_t ugetrlimit(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.ugetrlimit
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ugetrlimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xbf
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ugetrlimit)
	call   sys_ugetrlimit
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ugetrlimit)

/* void *mmap2(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t pgoffset) */
.section .text.x86.asm32_syscall_int80.mmap2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mmap2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xc0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mmap2)
	call   sys_mmap2
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mmap2)

/* errno_t truncate64(char const *filename, uint64_t length) */
.section .text.x86.asm32_syscall_int80.truncate64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_truncate64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xc1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_truncate64)
	call   sys_truncate64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_truncate64)

/* errno_t ftruncate64(fd_t fd, uint64_t length) */
.section .text.x86.asm32_syscall_int80.ftruncate64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ftruncate64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xc2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ftruncate64)
	call   sys_ftruncate64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ftruncate64)

/* errno_t linux_stat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_stat64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_stat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xc3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_stat64)
	call   sys_linux_stat64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_linux_stat64)

/* errno_t linux_lstat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_lstat64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_lstat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xc4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_lstat64)
	call   sys_linux_lstat64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_linux_lstat64)

/* errno_t linux_fstat64(fd_t fd, struct linux_stat64 *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_fstat64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_fstat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xc5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_fstat64)
	call   sys_linux_fstat64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_linux_fstat64)

/* errno_t lchown32(char const *filename, uint32_t owner, uint32_t group) */
.section .text.x86.asm32_syscall_int80.lchown32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lchown32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xc6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lchown32)
	call   sys_lchown32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_lchown32)

/* uint32_t getuid32(void) */
.section .text.x86.asm32_syscall_int80.getuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xc7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getuid32)
	call   sys_getuid32
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getuid32)

/* uint32_t getgid32(void) */
.section .text.x86.asm32_syscall_int80.getgid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xc8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getgid32)
	call   sys_getgid32
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getgid32)

/* uint32_t geteuid32(void) */
.section .text.x86.asm32_syscall_int80.geteuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_geteuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xc9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_geteuid32)
	call   sys_geteuid32
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_geteuid32)

/* uint32_t getegid32(void) */
.section .text.x86.asm32_syscall_int80.getegid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getegid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xca
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getegid32)
	call   sys_getegid32
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getegid32)

/* errno_t setreuid32(uint32_t ruid, uint32_t euid) */
.section .text.x86.asm32_syscall_int80.setreuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setreuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xcb
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setreuid32)
	call   sys_setreuid32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setreuid32)

/* errno_t setregid32(uint32_t rgid, uint32_t egid) */
.section .text.x86.asm32_syscall_int80.setregid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setregid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xcc
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setregid32)
	call   sys_setregid32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setregid32)

/* errno_t getgroups32(size_t size, uint32_t[] list) */
.section .text.x86.asm32_syscall_int80.getgroups32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getgroups32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xcd
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getgroups32)
	call   sys_getgroups32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getgroups32)

/* errno_t setgroups32(size_t count, uint32_t const *groups) */
.section .text.x86.asm32_syscall_int80.setgroups32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setgroups32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xce
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setgroups32)
	call   sys_setgroups32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setgroups32)

/* errno_t fchown32(fd_t fd, uint32_t owner, uint32_t group) */
.section .text.x86.asm32_syscall_int80.fchown32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchown32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xcf
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchown32)
	call   sys_fchown32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fchown32)

/* errno_t setresuid32(uint32_t ruid, uint32_t euid, uint32_t suid) */
.section .text.x86.asm32_syscall_int80.setresuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setresuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xd0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setresuid32)
	call   sys_setresuid32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setresuid32)

/* errno_t getresuid32(uint32_t *ruid, uint32_t *euid, uint32_t *suid) */
.section .text.x86.asm32_syscall_int80.getresuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getresuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xd1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getresuid32)
	call   sys_getresuid32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getresuid32)

/* errno_t setresgid32(uint32_t rgid, uint32_t egid, uint32_t sgid) */
.section .text.x86.asm32_syscall_int80.setresgid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setresgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xd2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setresgid32)
	call   sys_setresgid32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setresgid32)

/* errno_t getresgid32(uint32_t *rgid, uint32_t *egid, uint32_t *sgid) */
.section .text.x86.asm32_syscall_int80.getresgid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getresgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xd3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getresgid32)
	call   sys_getresgid32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getresgid32)

/* errno_t chown32(char const *filename, uint32_t owner, uint32_t group) */
.section .text.x86.asm32_syscall_int80.chown32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_chown32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xd4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_chown32)
	call   sys_chown32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_chown32)

/* errno_t setuid32(uint32_t uid) */
.section .text.x86.asm32_syscall_int80.setuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xd5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setuid32)
	call   sys_setuid32
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setuid32)

/* errno_t setgid32(uint32_t gid) */
.section .text.x86.asm32_syscall_int80.setgid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xd6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setgid32)
	call   sys_setgid32
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setgid32)

/* errno_t setfsuid32(uint32_t uid) */
.section .text.x86.asm32_syscall_int80.setfsuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setfsuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xd7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setfsuid32)
	call   sys_setfsuid32
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setfsuid32)

/* errno_t setfsgid32(uint32_t gid) */
.section .text.x86.asm32_syscall_int80.setfsgid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setfsgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xd8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setfsgid32)
	call   sys_setfsgid32
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setfsgid32)

/* errno_t pivot_root(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.pivot_root
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pivot_root)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xd9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pivot_root)
	call   sys_pivot_root
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_pivot_root)

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
.section .text.x86.asm32_syscall_int80.mincore
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mincore)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xda
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mincore)
	call   sys_mincore
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mincore)

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
.section .text.x86.asm32_syscall_int80.madvise
INTERN_WEAK_FUNCTION(__x86_asm32_int80_madvise)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xdb
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_madvise)
	call   sys_madvise
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_madvise)

/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *dirp, size_t count) */
.section .text.x86.asm32_syscall_int80.getdents64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getdents64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xdc
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getdents64)
	call   sys_getdents64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getdents64)

/* syscall_slong_t fcntl64(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.x86.asm32_syscall_int80.fcntl64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fcntl64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xdd
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fcntl64)
	call   sys_fcntl64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fcntl64)

/* pid_t gettid(void) */
.section .text.x86.asm32_syscall_int80.gettid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_gettid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xe0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_gettid)
	call   sys_gettid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_gettid)

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
.section .text.x86.asm32_syscall_int80.readahead
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readahead)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xe1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readahead)
	call   sys_readahead
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_readahead)

/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.setxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xe2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setxattr)
	call   sys_setxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setxattr)

/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.lsetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lsetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xe3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lsetxattr)
	call   sys_lsetxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_lsetxattr)

/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.fsetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fsetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xe4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fsetxattr)
	call   sys_fsetxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fsetxattr)

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_int80.getxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xe5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getxattr)
	call   sys_getxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getxattr)

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_int80.lgetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lgetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xe6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lgetxattr)
	call   sys_lgetxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_lgetxattr)

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_int80.fgetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fgetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xe7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fgetxattr)
	call   sys_fgetxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fgetxattr)

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.x86.asm32_syscall_int80.listxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_listxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xe8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_listxattr)
	call   sys_listxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_listxattr)

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.x86.asm32_syscall_int80.llistxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_llistxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xe9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_llistxattr)
	call   sys_llistxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_llistxattr)

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
.section .text.x86.asm32_syscall_int80.flistxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_flistxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xea
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_flistxattr)
	call   sys_flistxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_flistxattr)

/* errno_t removexattr(char const *path, char const *name) */
.section .text.x86.asm32_syscall_int80.removexattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_removexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xeb
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_removexattr)
	call   sys_removexattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_removexattr)

/* errno_t lremovexattr(char const *path, char const *name) */
.section .text.x86.asm32_syscall_int80.lremovexattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lremovexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xec
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lremovexattr)
	call   sys_lremovexattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_lremovexattr)

/* errno_t fremovexattr(int fd, char const *name) */
.section .text.x86.asm32_syscall_int80.fremovexattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fremovexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xed
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fremovexattr)
	call   sys_fremovexattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fremovexattr)

/* errno_t tkill(pid_t tid, syscall_ulong_t signo) */
.section .text.x86.asm32_syscall_int80.tkill
INTERN_WEAK_FUNCTION(__x86_asm32_int80_tkill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xee
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_tkill)
	call   sys_tkill
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_tkill)

/* ssize_t sendfile64(fd_t out_fd, fd_t in_fd, uint64_t *offset, size_t count) */
.section .text.x86.asm32_syscall_int80.sendfile64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sendfile64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xef
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sendfile64)
	call   sys_sendfile64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sendfile64)

/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct __timespecx32 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
.section .text.x86.asm32_syscall_int80.futex
INTERN_WEAK_FUNCTION(__x86_asm32_int80_futex)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xf0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_futex)
	call   sys_futex
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_futex)

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
.section .text.x86.asm32_syscall_int80.sched_setaffinity
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_setaffinity)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xf1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_setaffinity)
	call   sys_sched_setaffinity
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sched_setaffinity)

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
.section .text.x86.asm32_syscall_int80.sched_getaffinity
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_getaffinity)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xf2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_getaffinity)
	call   sys_sched_getaffinity
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sched_getaffinity)

/* errno_t set_thread_area(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.set_thread_area
INTERN_WEAK_FUNCTION(__x86_asm32_int80_set_thread_area)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xf3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_set_thread_area)
	call   sys_set_thread_area
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_set_thread_area)

/* errno_t get_thread_area(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.get_thread_area
INTERN_WEAK_FUNCTION(__x86_asm32_int80_get_thread_area)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xf4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_get_thread_area)
	call   sys_get_thread_area
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_get_thread_area)

/* errno_t io_setup(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.io_setup
INTERN_WEAK_FUNCTION(__x86_asm32_int80_io_setup)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xf5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_io_setup)
	call   sys_io_setup
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_io_setup)

/* errno_t io_destroy(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.io_destroy
INTERN_WEAK_FUNCTION(__x86_asm32_int80_io_destroy)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xf6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_io_destroy)
	call   sys_io_destroy
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_io_destroy)

/* errno_t io_getevents(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.io_getevents
INTERN_WEAK_FUNCTION(__x86_asm32_int80_io_getevents)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xf7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_io_getevents)
	call   sys_io_getevents
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_io_getevents)

/* errno_t io_submit(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.io_submit
INTERN_WEAK_FUNCTION(__x86_asm32_int80_io_submit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xf8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_io_submit)
	call   sys_io_submit
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_io_submit)

/* errno_t io_cancel(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.io_cancel
INTERN_WEAK_FUNCTION(__x86_asm32_int80_io_cancel)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xf9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_io_cancel)
	call   sys_io_cancel
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_io_cancel)

/* errno_t fadvise64(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.fadvise64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fadvise64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xfa
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fadvise64)
	call   sys_fadvise64
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fadvise64)

/* void exit_group(syscall_ulong_t exit_code) */
.section .text.x86.asm32_syscall_int80.exit_group
INTERN_WEAK_FUNCTION(__x86_asm32_int80_exit_group)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xfc
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_exit_group)
	call   sys_exit_group
	.cfi_endproc
END(__x86_asm32_int80_exit_group)

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.lookup_dcookie
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lookup_dcookie)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xfd
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lookup_dcookie)
	call   sys_lookup_dcookie
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_lookup_dcookie)

/* fd_t epoll_create(syscall_ulong_t size) */
.section .text.x86.asm32_syscall_int80.epoll_create
INTERN_WEAK_FUNCTION(__x86_asm32_int80_epoll_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xfe
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_epoll_create)
	call   sys_epoll_create
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_epoll_create)

/* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.x86.asm32_syscall_int80.epoll_ctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_epoll_ctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0xff
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_epoll_ctl)
	call   sys_epoll_ctl
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_epoll_ctl)

/* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.x86.asm32_syscall_int80.epoll_wait
INTERN_WEAK_FUNCTION(__x86_asm32_int80_epoll_wait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x100
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_epoll_wait)
	call   sys_epoll_wait
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_epoll_wait)

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.remap_file_pages
INTERN_WEAK_FUNCTION(__x86_asm32_int80_remap_file_pages)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x101
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_remap_file_pages)
	call   sys_remap_file_pages
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_remap_file_pages)

/* pid_t set_tid_address(pid_t *tidptr) */
.section .text.x86.asm32_syscall_int80.set_tid_address
INTERN_WEAK_FUNCTION(__x86_asm32_int80_set_tid_address)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x102
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_set_tid_address)
	call   sys_set_tid_address
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_set_tid_address)

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
.section .text.x86.asm32_syscall_int80.timer_create
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x103
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_create)
	call   sys_timer_create
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_timer_create)

/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct __itimerspecx32 const *value, struct __itimerspecx32 *ovalue) */
.section .text.x86.asm32_syscall_int80.timer_settime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x104
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_settime)
	call   sys_timer_settime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_timer_settime)

/* errno_t timer_gettime(timer_t timerid, struct __itimerspecx32 *value) */
.section .text.x86.asm32_syscall_int80.timer_gettime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x105
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_gettime)
	call   sys_timer_gettime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_timer_gettime)

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
.section .text.x86.asm32_syscall_int80.timer_getoverrun
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_getoverrun)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x106
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_getoverrun)
	call   sys_timer_getoverrun
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_timer_getoverrun)

/* errno_t timer_delete(timer_t timerid) */
.section .text.x86.asm32_syscall_int80.timer_delete
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_delete)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x107
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_delete)
	call   sys_timer_delete
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_timer_delete)

/* errno_t clock_settime(clockid_t clock_id, struct __timespecx32 const *tp) */
.section .text.x86.asm32_syscall_int80.clock_settime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x108
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_settime)
	call   sys_clock_settime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_clock_settime)

/* errno_t clock_gettime(clockid_t clock_id, struct __timespecx32 *tp) */
.section .text.x86.asm32_syscall_int80.clock_gettime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x109
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_gettime)
	call   sys_clock_gettime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_clock_gettime)

/* errno_t clock_getres(clockid_t clock_id, struct __timespecx32 *res) */
.section .text.x86.asm32_syscall_int80.clock_getres
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_getres)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x10a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_getres)
	call   sys_clock_getres
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_clock_getres)

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct __timespecx32 const *requested_time, struct __timespecx32 *remaining) */
.section .text.x86.asm32_syscall_int80.clock_nanosleep
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_nanosleep)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x10b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_nanosleep)
	call   sys_clock_nanosleep
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_clock_nanosleep)

/* errno_t statfs64(char const *file, struct statfs64 *buf) */
.section .text.x86.asm32_syscall_int80.statfs64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_statfs64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x10c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_statfs64)
	call   sys_statfs64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_statfs64)

/* errno_t fstatfs64(fd_t file, struct statfs64 *buf) */
.section .text.x86.asm32_syscall_int80.fstatfs64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fstatfs64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x10d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fstatfs64)
	call   sys_fstatfs64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fstatfs64)

/* errno_t tgkill(pid_t tgid, pid_t tid, syscall_ulong_t signo) */
.section .text.x86.asm32_syscall_int80.tgkill
INTERN_WEAK_FUNCTION(__x86_asm32_int80_tgkill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x10e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_tgkill)
	call   sys_tgkill
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_tgkill)

/* errno_t utimes(char const *filename, struct __timevalx32 const[2] times) */
.section .text.x86.asm32_syscall_int80.utimes
INTERN_WEAK_FUNCTION(__x86_asm32_int80_utimes)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x10f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_utimes)
	call   sys_utimes
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_utimes)

/* errno_t fadvise64_64(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.fadvise64_64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fadvise64_64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x110
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fadvise64_64)
	call   sys_fadvise64_64
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fadvise64_64)

/* errno_t vserver(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.vserver
INTERN_WEAK_FUNCTION(__x86_asm32_int80_vserver)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x111
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_vserver)
	call   sys_vserver
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_vserver)

/* errno_t mbind(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.mbind
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mbind)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x112
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mbind)
	call   sys_mbind
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mbind)

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.get_mempolicy
INTERN_WEAK_FUNCTION(__x86_asm32_int80_get_mempolicy)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x113
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_get_mempolicy)
	call   sys_get_mempolicy
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_get_mempolicy)

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.set_mempolicy
INTERN_WEAK_FUNCTION(__x86_asm32_int80_set_mempolicy)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x114
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_set_mempolicy)
	call   sys_set_mempolicy
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_set_mempolicy)

/* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
.section .text.x86.asm32_syscall_int80.mq_open
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_open)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x115
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_open)
	call   sys_mq_open
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mq_open)

/* errno_t mq_unlink(char const *name) */
.section .text.x86.asm32_syscall_int80.mq_unlink
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_unlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x116
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_unlink)
	call   sys_mq_unlink
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mq_unlink)

/* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct __timespecx32 const *abs_timeout) */
.section .text.x86.asm32_syscall_int80.mq_timedsend
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_timedsend)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x117
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_timedsend)
	call   sys_mq_timedsend
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mq_timedsend)

/* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct __timespecx32 const *abs_timeout) */
.section .text.x86.asm32_syscall_int80.mq_timedreceive
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_timedreceive)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x118
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_timedreceive)
	call   sys_mq_timedreceive
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mq_timedreceive)

/* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
.section .text.x86.asm32_syscall_int80.mq_notify
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_notify)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x119
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_notify)
	call   sys_mq_notify
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mq_notify)

/* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
.section .text.x86.asm32_syscall_int80.mq_getsetattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_getsetattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x11a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_getsetattr)
	call   sys_mq_getsetattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mq_getsetattr)

/* errno_t kexec_load(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.kexec_load
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kexec_load)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x11b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kexec_load)
	call   sys_kexec_load
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_kexec_load)

/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo32_struct *infop, syscall_ulong_t options, struct __rusagex32 *ru) */
.section .text.x86.asm32_syscall_int80.waitid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_waitid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x11c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_waitid)
	call   sys_waitid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_waitid)

/* errno_t add_key(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.add_key
INTERN_WEAK_FUNCTION(__x86_asm32_int80_add_key)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x11e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_add_key)
	call   sys_add_key
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_add_key)

/* errno_t request_key(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.request_key
INTERN_WEAK_FUNCTION(__x86_asm32_int80_request_key)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x11f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_request_key)
	call   sys_request_key
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_request_key)

/* errno_t keyctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.keyctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_keyctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x120
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_keyctl)
	call   sys_keyctl
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_keyctl)

/* errno_t ioprio_set(syscall_ulong_t which, syscall_ulong_t who, syscall_ulong_t ioprio) */
.section .text.x86.asm32_syscall_int80.ioprio_set
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ioprio_set)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x121
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ioprio_set)
	call   sys_ioprio_set
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ioprio_set)

/* errno_t ioprio_get(syscall_ulong_t which, syscall_ulong_t who) */
.section .text.x86.asm32_syscall_int80.ioprio_get
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ioprio_get)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x122
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ioprio_get)
	call   sys_ioprio_get
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ioprio_get)

/* errno_t inotify_init(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.inotify_init
INTERN_WEAK_FUNCTION(__x86_asm32_int80_inotify_init)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x123
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_inotify_init)
	call   sys_inotify_init
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_inotify_init)

/* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.inotify_add_watch
INTERN_WEAK_FUNCTION(__x86_asm32_int80_inotify_add_watch)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x124
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_inotify_add_watch)
	call   sys_inotify_add_watch
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_inotify_add_watch)

/* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.inotify_rm_watch
INTERN_WEAK_FUNCTION(__x86_asm32_int80_inotify_rm_watch)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x125
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_inotify_rm_watch)
	call   sys_inotify_rm_watch
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_inotify_rm_watch)

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.migrate_pages
INTERN_WEAK_FUNCTION(__x86_asm32_int80_migrate_pages)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x126
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_migrate_pages)
	call   sys_migrate_pages
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_migrate_pages)

/* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
.section .text.x86.asm32_syscall_int80.openat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_openat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x127
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_openat)
	call   sys_openat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_openat)

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
.section .text.x86.asm32_syscall_int80.mkdirat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mkdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x128
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mkdirat)
	call   sys_mkdirat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mkdirat)

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
.section .text.x86.asm32_syscall_int80.mknodat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mknodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x129
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mknodat)
	call   sys_mknodat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.fchownat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchownat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x12a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchownat)
	call   sys_fchownat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fchownat)

/* errno_t futimesat(fd_t dirfd, const char *filename, struct __timevalx32 const[2] times) */
.section .text.x86.asm32_syscall_int80.futimesat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_futimesat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x12b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_futimesat)
	call   sys_futimesat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_futimesat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t linux_fstatat64(fd_t dirfd, char const *filename, struct linux_stat64 *statbuf, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.linux_fstatat64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_fstatat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x12c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_fstatat64)
	call   sys_linux_fstatat64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_linux_fstatat64)

/* @param: flags: Set of `0 | AT_REMOVEDIR|AT_REMOVEREG | AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.unlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_unlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x12d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_unlinkat)
	call   sys_unlinkat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_unlinkat)

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
.section .text.x86.asm32_syscall_int80.renameat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_renameat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x12e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_renameat)
	call   sys_renameat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_renameat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.linkat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x12f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linkat)
	call   sys_linkat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_linkat)

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
.section .text.x86.asm32_syscall_int80.symlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_symlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x130
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_symlinkat)
	call   sys_symlinkat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_symlinkat)

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
.section .text.x86.asm32_syscall_int80.readlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x131
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readlinkat)
	call   sys_readlinkat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_readlinkat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.fchmodat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchmodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x132
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchmodat)
	call   sys_fchmodat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fchmodat)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_EACCESS | AT_DOSPATH' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.faccessat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_faccessat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x133
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_faccessat)
	call   sys_faccessat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_faccessat)

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespecx32 const *timeout, void const *sigmask_sigset_and_len) */
.section .text.x86.asm32_syscall_int80.pselect6
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pselect6)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x134
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pselect6)
	call   sys_pselect6
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_pselect6)

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct __timespecx32 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.ppoll
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ppoll)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x135
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ppoll)
	call   sys_ppoll
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ppoll)

/* param flags: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.unshare
INTERN_WEAK_FUNCTION(__x86_asm32_int80_unshare)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x136
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_unshare)
	call   sys_unshare
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_unshare)

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.set_robust_list
INTERN_WEAK_FUNCTION(__x86_asm32_int80_set_robust_list)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x137
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_set_robust_list)
	call   sys_set_robust_list
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_set_robust_list)

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.get_robust_list
INTERN_WEAK_FUNCTION(__x86_asm32_int80_get_robust_list)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x138
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_get_robust_list)
	call   sys_get_robust_list
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_get_robust_list)

/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.splice
INTERN_WEAK_FUNCTION(__x86_asm32_int80_splice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x139
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_splice)
	call   sys_splice
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_splice)

/* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.sync_file_range
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sync_file_range)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x13a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sync_file_range)
	call   sys_sync_file_range
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sync_file_range)

/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.tee
INTERN_WEAK_FUNCTION(__x86_asm32_int80_tee)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x13b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_tee)
	call   sys_tee
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_tee)

/* ssize_t vmsplice(fd_t fdout, struct iovec32 const *iov, size_t count, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.vmsplice
INTERN_WEAK_FUNCTION(__x86_asm32_int80_vmsplice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x13c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_vmsplice)
	call   sys_vmsplice
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_vmsplice)

/* errno_t move_pages(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.move_pages
INTERN_WEAK_FUNCTION(__x86_asm32_int80_move_pages)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x13d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_move_pages)
	call   sys_move_pages
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_move_pages)

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
.section .text.x86.asm32_syscall_int80.getcpu
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getcpu)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x13e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getcpu)
	call   sys_getcpu
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getcpu)

/* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
.section .text.x86.asm32_syscall_int80.epoll_pwait
INTERN_WEAK_FUNCTION(__x86_asm32_int80_epoll_pwait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x13f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_epoll_pwait)
	call   sys_epoll_pwait
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_epoll_pwait)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct __timespecx32 const[2] times, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.utimensat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_utimensat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x140
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_utimensat)
	call   sys_utimensat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_utimensat)

/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.signalfd
INTERN_WEAK_FUNCTION(__x86_asm32_int80_signalfd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x141
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_signalfd)
	call   sys_signalfd
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_signalfd)

/* Return file descriptor for new interval timer source */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.timerfd_create
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timerfd_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x142
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timerfd_create)
	call   sys_timerfd_create
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_timerfd_create)

/* fd_t eventfd(syscall_ulong_t initval) */
.section .text.x86.asm32_syscall_int80.eventfd
INTERN_WEAK_FUNCTION(__x86_asm32_int80_eventfd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x143
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_eventfd)
	call   sys_eventfd
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_eventfd)

/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
.section .text.x86.asm32_syscall_int80.fallocate
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fallocate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x144
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fallocate)
	call   sys_fallocate
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fallocate)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
/* errno_t timerfd_settime(fd_t ufd, syscall_ulong_t flags, struct __itimerspecx32 const *utmr, struct __itimerspecx32 *otmr) */
.section .text.x86.asm32_syscall_int80.timerfd_settime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timerfd_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x145
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timerfd_settime)
	call   sys_timerfd_settime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_timerfd_settime)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t ufd, struct __itimerspecx32 *otmr) */
.section .text.x86.asm32_syscall_int80.timerfd_gettime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timerfd_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x146
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timerfd_gettime)
	call   sys_timerfd_gettime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_timerfd_gettime)

/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.signalfd4
INTERN_WEAK_FUNCTION(__x86_asm32_int80_signalfd4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x147
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_signalfd4)
	call   sys_signalfd4
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_signalfd4)

/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.eventfd2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_eventfd2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x148
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_eventfd2)
	call   sys_eventfd2
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_eventfd2)

/* fd_t epoll_create1(syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.epoll_create1
INTERN_WEAK_FUNCTION(__x86_asm32_int80_epoll_create1)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x149
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_epoll_create1)
	call   sys_epoll_create1
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_epoll_create1)

/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
.section .text.x86.asm32_syscall_int80.dup3
INTERN_WEAK_FUNCTION(__x86_asm32_int80_dup3)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x14a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_dup3)
	call   sys_dup3
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_dup3)

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
.section .text.x86.asm32_syscall_int80.pipe2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pipe2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x14b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pipe2)
	call   sys_pipe2
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_pipe2)

/* errno_t inotify_init1(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.inotify_init1
INTERN_WEAK_FUNCTION(__x86_asm32_int80_inotify_init1)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x14c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_inotify_init1)
	call   sys_inotify_init1
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_inotify_init1)

/* ssize_t preadv(fd_t fd, struct iovec32 const *iovec, size_t count, uint64_t offset) */
.section .text.x86.asm32_syscall_int80.preadv
INTERN_WEAK_FUNCTION(__x86_asm32_int80_preadv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x14d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_preadv)
	call   sys_preadv
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_preadv)

/* ssize_t pwritev(fd_t fd, struct iovec32 const *iovec, size_t count, uint64_t offset) */
.section .text.x86.asm32_syscall_int80.pwritev
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pwritev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x14e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pwritev)
	call   sys_pwritev
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_pwritev)

/* @param: signo: One of `SIG*' */
/* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, syscall_ulong_t signo, struct __siginfo32_struct const *uinfo) */
.section .text.x86.asm32_syscall_int80.rt_tgsigqueueinfo
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_tgsigqueueinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x14f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_tgsigqueueinfo)
	call   sys_rt_tgsigqueueinfo
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_rt_tgsigqueueinfo)

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.perf_event_open
INTERN_WEAK_FUNCTION(__x86_asm32_int80_perf_event_open)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x150
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_perf_event_open)
	call   sys_perf_event_open
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_perf_event_open)

/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespecx32 *tmo) */
.section .text.x86.asm32_syscall_int80.recvmmsg
INTERN_WEAK_FUNCTION(__x86_asm32_int80_recvmmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x151
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_recvmmsg)
	call   sys_recvmmsg
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_recvmmsg)

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.fanotify_init
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fanotify_init)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x152
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fanotify_init)
	call   sys_fanotify_init
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fanotify_init)

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.fanotify_mark
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fanotify_mark)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x153
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fanotify_mark)
	call   sys_fanotify_mark
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fanotify_mark)

/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
.section .text.x86.asm32_syscall_int80.prlimit64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_prlimit64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x154
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_prlimit64)
	call   sys_prlimit64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_prlimit64)

/* errno_t name_to_handle_at(fd_t dirfd, char const *name, struct file_handle *handle, int32_t *mnt_id, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.name_to_handle_at
INTERN_WEAK_FUNCTION(__x86_asm32_int80_name_to_handle_at)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x155
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_name_to_handle_at)
	call   sys_name_to_handle_at
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_name_to_handle_at)

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle *handle, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.open_by_handle_at
INTERN_WEAK_FUNCTION(__x86_asm32_int80_open_by_handle_at)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x156
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_open_by_handle_at)
	call   sys_open_by_handle_at
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_open_by_handle_at)

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.clock_adjtime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_adjtime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x157
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_adjtime)
	call   sys_clock_adjtime
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_clock_adjtime)

/* errno_t syncfs(fd_t fd) */
.section .text.x86.asm32_syscall_int80.syncfs
INTERN_WEAK_FUNCTION(__x86_asm32_int80_syncfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x158
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_syncfs)
	call   sys_syncfs
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_syncfs)

/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.sendmmsg
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sendmmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x159
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sendmmsg)
	call   sys_sendmmsg
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sendmmsg)

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
.section .text.x86.asm32_syscall_int80.setns
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setns)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x15a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setns)
	call   sys_setns
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setns)

/* ssize_t process_vm_readv(pid_t pid, struct iovec32 const *lvec, size_t liovcnt, struct iovec32 const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.process_vm_readv
INTERN_WEAK_FUNCTION(__x86_asm32_int80_process_vm_readv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x15b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_process_vm_readv)
	call   sys_process_vm_readv
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_process_vm_readv)

/* ssize_t process_vm_writev(pid_t pid, struct iovec32 const *lvec, size_t liovcnt, struct iovec32 const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.process_vm_writev
INTERN_WEAK_FUNCTION(__x86_asm32_int80_process_vm_writev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x15c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_process_vm_writev)
	call   sys_process_vm_writev
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_process_vm_writev)

/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
.section .text.x86.asm32_syscall_int80.kcmp
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kcmp)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x15d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kcmp)
	call   sys_kcmp
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_kcmp)

/* errno_t finit_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.finit_module
INTERN_WEAK_FUNCTION(__x86_asm32_int80_finit_module)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x15e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_finit_module)
	call   sys_finit_module
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_finit_module)

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.sched_setattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_setattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x15f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_setattr)
	call   sys_sched_setattr
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sched_setattr)

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.sched_getattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_getattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x160
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_getattr)
	call   sys_sched_getattr
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sched_getattr)

/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.renameat2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_renameat2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x161
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_renameat2)
	call   sys_renameat2
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_renameat2)

/* errno_t seccomp(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.seccomp
INTERN_WEAK_FUNCTION(__x86_asm32_int80_seccomp)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x162
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_seccomp)
	call   sys_seccomp
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_seccomp)

/* errno_t getrandom(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.getrandom
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getrandom)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x163
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getrandom)
	call   sys_getrandom
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getrandom)

/* errno_t memfd_create(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.memfd_create
INTERN_WEAK_FUNCTION(__x86_asm32_int80_memfd_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x164
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_memfd_create)
	call   sys_memfd_create
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_memfd_create)

/* errno_t bpf(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.bpf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_bpf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x165
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_bpf)
	call   sys_bpf
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_bpf)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.execveat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_execveat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x166
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_execveat)
	call   sys_execveat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_execveat)

/* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
.section .text.x86.asm32_syscall_int80.socket
INTERN_WEAK_FUNCTION(__x86_asm32_int80_socket)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x167
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_socket)
	call   sys_socket
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_socket)

/* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
.section .text.x86.asm32_syscall_int80.socketpair
INTERN_WEAK_FUNCTION(__x86_asm32_int80_socketpair)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x168
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_socketpair)
	call   sys_socketpair
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_socketpair)

/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm32_syscall_int80.bind
INTERN_WEAK_FUNCTION(__x86_asm32_int80_bind)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x169
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_bind)
	call   sys_bind
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_bind)

/* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm32_syscall_int80.connect
INTERN_WEAK_FUNCTION(__x86_asm32_int80_connect)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x16a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_connect)
	call   sys_connect
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_connect)

/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
.section .text.x86.asm32_syscall_int80.listen
INTERN_WEAK_FUNCTION(__x86_asm32_int80_listen)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x16b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_listen)
	call   sys_listen
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_listen)

/* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.accept4
INTERN_WEAK_FUNCTION(__x86_asm32_int80_accept4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x16c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_accept4)
	call   sys_accept4
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_accept4)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
.section .text.x86.asm32_syscall_int80.getsockopt
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getsockopt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x16d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getsockopt)
	call   sys_getsockopt
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getsockopt)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
.section .text.x86.asm32_syscall_int80.setsockopt
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setsockopt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x16e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setsockopt)
	call   sys_setsockopt
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setsockopt)

/* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm32_syscall_int80.getsockname
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getsockname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x16f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getsockname)
	call   sys_getsockname
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getsockname)

/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm32_syscall_int80.getpeername
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getpeername)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x170
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getpeername)
	call   sys_getpeername
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getpeername)

/* param flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
/* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm32_syscall_int80.sendto
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sendto)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x171
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sendto)
	call   sys_sendto
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sendto)

/* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.sendmsg
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sendmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x172
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sendmsg)
	call   sys_sendmsg
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sendmsg)

/* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm32_syscall_int80.recvfrom
INTERN_WEAK_FUNCTION(__x86_asm32_int80_recvfrom)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x173
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_recvfrom)
	call   sys_recvfrom
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_recvfrom)

/* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.recvmsg
INTERN_WEAK_FUNCTION(__x86_asm32_int80_recvmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x174
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_recvmsg)
	call   sys_recvmsg
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_recvmsg)

/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
.section .text.x86.asm32_syscall_int80.shutdown
INTERN_WEAK_FUNCTION(__x86_asm32_int80_shutdown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x175
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_shutdown)
	call   sys_shutdown
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_shutdown)

/* errno_t userfaultfd(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.userfaultfd
INTERN_WEAK_FUNCTION(__x86_asm32_int80_userfaultfd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x176
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_userfaultfd)
	call   sys_userfaultfd
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_userfaultfd)

/* errno_t membarrier(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.membarrier
INTERN_WEAK_FUNCTION(__x86_asm32_int80_membarrier)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x177
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_membarrier)
	call   sys_membarrier
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_membarrier)

/* errno_t mlock2(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.mlock2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mlock2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x178
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mlock2)
	call   sys_mlock2
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mlock2)

/* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.x86.asm32_syscall_int80.hop
INTERN_WEAK_FUNCTION(__x86_asm32_int80_hop)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000001
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_hop)
	call   sys_hop
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_hop)

/* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.x86.asm32_syscall_int80.hopf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_hopf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000002
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_hopf)
	call   sys_hopf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_hopf)

/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.readf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000003
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readf)
	call   sys_readf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_readf)

/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.writef
INTERN_WEAK_FUNCTION(__x86_asm32_int80_writef)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000004
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_writef)
	call   sys_writef
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_writef)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the thread from turning into a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling thread from the set of running children within
 *     its own process. Note however that when this is done by the main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the calling process the same way a double-fork would:
 *     >> if (fork() == 0) {
 *     >> 	if (fork() == 0) {
 *     >> 		// This is a daemonized process
 *     >> 		// aka. the parent process no longer knows
 *     >> 		// about us, and also can't wait(2) on us.
 *     >> 		...
 *     >> 	}
 *     >> 	exit(0);
 *     >> }
 *     Same as:
 *     >> if (fork() == 0) {
 *     >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
 *     >> 	// This is a daemonized process
 *     >> 	// aka. the parent process no longer knows
 *     >> 	// about us, and also can't wait(2) on us.
 *     >> 	...
 *     >> }
 *   - PID == -1:
 *     Detach all child processes/threads of the calling process, essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * Before any of this is done, the thread referred to by `PID' is one of the following:
 *   - The leader of the process that called `fork()' or `clone()' without
 *    `CLONE_PARENT' to create the thread referred to by `PID'
 *   - The creator of the process containing a thread that called
 *    `clone()' with `CLONE_PARENT', which then created the thread
 *     referred to by `PID'.
 *   - Even if the thread doesn't deliver a signal upon it terminating,
 *     the process that would have received such a signal is still relevant.
 *   -> In other words: The thread `PID' must be one of your children,
 *                      or you had to have been assigned as its child.
 * If the calling thread isn't part of that process that will receive
 * the signal if the thread dies without being detached first, then
 * the call fails by throwing an `E_ILLEGAL_OPERATION'.
 * If the thread had already been detached, then the call fails by
 * throwing an `E_ILLEGAL_OPERATION' as well.
 * Upon success, the thread referred to by `PID' will clean up its own
 * PID descriptor without the need of anyone to wait() for it, a behavior
 * that linux implements using `CLONE_THREAD' (which you shouldn't use,
 * because it's flawed by design)
 * Once detached, any further use of PID results in a race condition
 * (which linux neglects to mention for `CLONE_THREAD'), because there
 * is no way of ensuring that PID still refers to the original thread,
 * as another thread may have been created using the same PID, after
 * the detached thread exited.
 * NOTE: If a thread is crated using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had already
 *       be called.
 * NOTE: If the thread already has terminated, detaching it will kill
 *       its zombie the same way wait() would.
 * NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
 *       However, this operation fails if the calling thread isn't
 *       part of the same process as the parent process of the thread.
 *       In other words, the child of a fork() can't do this, and
 *       neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
 *       clone(0) or clone(CLONE_PARENT).
 * @return: -EPERM:             The calling process isn't the recipient of signals
 *                              delivered when `PID' changes state. This can either
 *                              be because `PID' has already been detached, or because
 *                              YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
 *                              Another possibility is that the thread was already
 *                              detached, then exited, following which a new thread
 *                              got created and had been assigned the PID of your
 *                              ancient, no longer existent thread.
 * @return: -ECHILD:           `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
 *                              This could mean that it had already been detached
 *                              and exited, or that the `PID' is just invalid (which
 *                              would also be the case if it was valid at some point) */
/* errno_t detach(pid_t pid) */
.section .text.x86.asm32_syscall_int80.detach
INTERN_WEAK_FUNCTION(__x86_asm32_int80_detach)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000005
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_detach)
	call   sys_detach
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_detach)

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
.section .text.x86.asm32_syscall_int80.getdrives
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getdrives)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000006
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getdrives)
	call   sys_getdrives
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getdrives)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.frealpath4
INTERN_WEAK_FUNCTION(__x86_asm32_int80_frealpath4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000007
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_frealpath4)
	call   sys_frealpath4
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_frealpath4)

/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.frealpathat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_frealpathat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000008
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_frealpathat)
	call   sys_frealpathat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_frealpathat)

/* Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
/* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, __HYBRID_PTR32(void) *arguments) */
.section .text.x86.asm32_syscall_int80.rpc_schedule
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rpc_schedule)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000009
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rpc_schedule)
	call   sys_rpc_schedule
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_rpc_schedule)

/* syscall_slong_t ksysctl(syscall_ulong_t command, void *arg) */
.section .text.x86.asm32_syscall_int80.ksysctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ksysctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000000a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ksysctl)
	call   sys_ksysctl
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ksysctl)

/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
.section .text.x86.asm32_syscall_int80.openpty
INTERN_WEAK_FUNCTION(__x86_asm32_int80_openpty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000000b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_openpty)
	call   sys_openpty
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_openpty)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.fchdirat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000000c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchdirat)
	call   sys_fchdirat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fchdirat)

/* int64_t time64(int64_t *timer) */
.section .text.x86.asm32_syscall_int80.time64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_time64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000000d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_time64)
	call   sys_time64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_time64)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
/* errno_t set_exception_handler(syscall_ulong_t mode, __except_handler32_t handler, void *handler_sp) */
.section .text.x86.asm32_syscall_int80.set_exception_handler
INTERN_WEAK_FUNCTION(__x86_asm32_int80_set_exception_handler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000000e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_set_exception_handler)
	call   sys_set_exception_handler
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_set_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
/* errno_t get_exception_handler(__ULONG32_TYPE__ *pmode, __except_handler32_t *phandler, __HYBRID_PTR32(void) *phandler_sp) */
.section .text.x86.asm32_syscall_int80.get_exception_handler
INTERN_WEAK_FUNCTION(__x86_asm32_int80_get_exception_handler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000000f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_get_exception_handler)
	call   sys_get_exception_handler
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_get_exception_handler)

/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
/* errno_t set_library_listdef(struct library_listdef32 const *listdef) */
.section .text.x86.asm32_syscall_int80.set_library_listdef
INTERN_WEAK_FUNCTION(__x86_asm32_int80_set_library_listdef)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000010
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_set_library_listdef)
	call   sys_set_library_listdef
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_set_library_listdef)

/* Trigger a debugger trap `trapno', optionally extended with `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to the
 * given `state', though given the purpose of this system call being
 * to inform a connected debugger of some breakable event, allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
/* errno_t debugtrap(struct ucpustate32 const *state, struct debugtrap_reason32 const *reason) */
.section .text.x86.asm32_syscall_int80.debugtrap
INTERN_WEAK_FUNCTION(__x86_asm32_int80_debugtrap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000011
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_debugtrap)
	call   sys_debugtrap
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_debugtrap)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKEMASK, size_t val = count, struct timespec64 const *timeout = mask_and, uintptr_t val2 = mask_or)
 *    - LFUTEX_NOP:                (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_NOP)
 *    - LFUTEX_WAIT:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT, uintptr_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_LOCK, uintptr_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_ABOVE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BELOW, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
/* syscall_slong_t lfutex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct __timespecx32_64 const *timeout, uint32_t val2) */
.section .text.x86.asm32_syscall_int80.lfutex
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lfutex)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000012
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lfutex)
	call   sys_lfutex
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_lfutex)

/* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
.section .text.x86.asm32_syscall_int80.lseek64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lseek64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000013
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lseek64)
	call   sys_lseek64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_lseek64)

/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexexpr(void *base, size_t exprc, struct lfutexexpr32 const *exprv, struct __timespecx32_64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.x86.asm32_syscall_int80.lfutexexpr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lfutexexpr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000014
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lfutexexpr)
	call   sys_lfutexexpr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_lfutexexpr)

/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexlockexpr(uint32_t *ulockaddr, void *base, size_t exprc, struct lfutexexpr32 const *exprv, struct __timespecx32_64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.x86.asm32_syscall_int80.lfutexlockexpr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lfutexlockexpr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000015
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lfutexlockexpr)
	call   sys_lfutexlockexpr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_lfutexlockexpr)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(fd_t keyboard, fd_t display, char const *name, syscall_ulong_t rsvd) */
.section .text.x86.asm32_syscall_int80.mktty
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mktty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000016
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mktty)
	call   sys_mktty
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mktty)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
/* errno_t raiseat(struct ucpustate32 const *state, struct __siginfo32_struct const *si) */
.section .text.x86.asm32_syscall_int80.raiseat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_raiseat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000017
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_raiseat)
	call   sys_raiseat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_raiseat)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `exception' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When `curr_state' is also `NULL', then the current CPU state is used instead.
 * @param: traceback_vector: (potentially incomplete) vector of additional program pointers that were
 *                           travered when the stack was walked from `orig_state' to `curr_state'
 *                           Note that earlier entires within this vector are further up the call-stack, with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it can be assumed that the traceback is complete and contains all travered instruction locations.
 *                           In this case, a traceback displayed to a human should not include the text location at
 *                           `traceback_vector[traceback_length-1]', since that location would also be printed when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: exception:        The exception that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           Note that when `unwind_error == UNWIND_SUCCESS', this argument is interpreted as `siginfo_t *',
 *                           allowing coredumps to also be triggerred for unhandled signals.
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_NOTHROW' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
/* errno_t coredump(struct ucpustate32 const *curr_state, struct ucpustate32 const *orig_state, __HYBRID_PTR32(void) const *traceback_vector, size_t traceback_length, struct exception_data32 const *exception, syscall_ulong_t unwind_error) */
.section .text.x86.asm32_syscall_int80.coredump
INTERN_WEAK_FUNCTION(__x86_asm32_int80_coredump)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000018
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_coredump)
	call   sys_coredump
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_coredump)

/* errno_t stime64(time64_t const *t) */
.section .text.x86.asm32_syscall_int80.stime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_stime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000019
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_stime64)
	call   sys_stime64
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_stime64)

/* errno_t utime64(char const *filename, struct __utimbuf64 const *times) */
.section .text.x86.asm32_syscall_int80.utime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_utime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000001e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_utime64)
	call   sys_utime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_utime64)

/* errno_t ftime64(struct __timebx32_64 *tp) */
.section .text.x86.asm32_syscall_int80.ftime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ftime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000023
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ftime64)
	call   sys_ftime64
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ftime64)

/* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.x86.asm32_syscall_int80.ioctlf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ioctlf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000036
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ioctlf)
	call   sys_ioctlf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ioctlf)

/* uint64_t fsmode(uint64_t mode) */
.section .text.x86.asm32_syscall_int80.fsmode
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fsmode)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000003c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fsmode)
	call   sys_fsmode
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fsmode)

/* errno_t getrusage64(syscall_slong_t who, struct __rusagex32_64 *tv) */
.section .text.x86.asm32_syscall_int80.getrusage64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getrusage64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000004d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getrusage64)
	call   sys_getrusage64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getrusage64)

/* errno_t gettimeofday64(struct __timevalx32_64 *tv, struct timezone *tz) */
.section .text.x86.asm32_syscall_int80.gettimeofday64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_gettimeofday64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000004e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_gettimeofday64)
	call   sys_gettimeofday64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_gettimeofday64)

/* errno_t settimeofday64(struct __timevalx32_64 const *tv, struct timezone const *tz) */
.section .text.x86.asm32_syscall_int80.settimeofday64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_settimeofday64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000004f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_settimeofday64)
	call   sys_settimeofday64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_settimeofday64)

/* ssize_t select64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timevalx32_64 *timeout) */
.section .text.x86.asm32_syscall_int80.select64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_select64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000052
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_select64)
	call   sys_select64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_select64)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|
 *                       MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP|
 *                       MAP_DONT_OVERRIDE'
 * @param: fd:    A handle for the library file being mapped
 *                (must be a file or vm_datablock/inode)
 * @param: hdrv:  Pointer to a vector of `Elf32_Phdr' or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
/* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, void *hdrv, size_t hdrc) */
.section .text.x86.asm32_syscall_int80.maplibrary
INTERN_WEAK_FUNCTION(__x86_asm32_int80_maplibrary)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000056
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_maplibrary)
	call   sys_maplibrary
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_maplibrary)

/* errno_t setitimer64(syscall_ulong_t which, struct __itimerval64 const *newval, struct __itimerval64 *oldval) */
.section .text.x86.asm32_syscall_int80.setitimer64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setitimer64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000068
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setitimer64)
	call   sys_setitimer64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_setitimer64)

/* errno_t getitimer64(syscall_ulong_t which, struct __itimerval64 *curr_value) */
.section .text.x86.asm32_syscall_int80.getitimer64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getitimer64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000069
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getitimer64)
	call   sys_getitimer64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_getitimer64)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4_64(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct __rusagex32_64 *usage) */
.section .text.x86.asm32_syscall_int80.wait4_64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_wait4_64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000072
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_wait4_64)
	call   sys_wait4_64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_wait4_64)

/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
.section .text.x86.asm32_syscall_int80.kreaddir
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kreaddir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000008d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kreaddir)
	call   sys_kreaddir
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_kreaddir)

/* ssize_t readvf(fd_t fd, struct iovec32 const *iovec, size_t count, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.readvf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readvf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000091
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readvf)
	call   sys_readvf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_readvf)

/* ssize_t writevf(fd_t fd, struct iovec32 const *iovec, size_t count, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.writevf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_writevf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000092
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_writevf)
	call   sys_writevf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_writevf)

/* syscall_slong_t rpc_service(void) */
.section .text.x86.asm32_syscall_int80.rpc_service
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rpc_service)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000009e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_rpc_service)
	call   sys_rpc_service
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_rpc_service)

/* errno_t sched_rr_get_interval64(pid_t pid, struct __timespecx32_64 *tms) */
.section .text.x86.asm32_syscall_int80.sched_rr_get_interval64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_rr_get_interval64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x800000a1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_rr_get_interval64)
	call   sys_sched_rr_get_interval64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_sched_rr_get_interval64)

/* errno_t nanosleep64(struct __timespecx32_64 const *req, struct __timespecx32_64 *rem) */
.section .text.x86.asm32_syscall_int80.nanosleep64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_nanosleep64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x800000a2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_nanosleep64)
	call   sys_nanosleep64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_nanosleep64)

/* syscall_slong_t rt_sigtimedwait64(struct __sigset_struct const *set, struct __siginfo32_struct *info, struct __timespecx32_64 const *timeout, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.rt_sigtimedwait64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigtimedwait64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x800000b1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigtimedwait64)
	call   sys_rt_sigtimedwait64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_rt_sigtimedwait64)

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.pread64f
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pread64f)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x800000b4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pread64f)
	call   sys_pread64f
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_pread64f)

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.pwrite64f
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pwrite64f)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x800000b5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pwrite64f)
	call   sys_pwrite64f
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_pwrite64f)

/* errno_t kstat(char const *filename, struct stat *statbuf) */
.section .text.x86.asm32_syscall_int80.kstat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x800000c3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kstat)
	call   sys_kstat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_kstat)

/* errno_t klstat(char const *filename, struct stat *statbuf) */
.section .text.x86.asm32_syscall_int80.klstat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_klstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x800000c4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_klstat)
	call   sys_klstat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_klstat)

/* errno_t kfstat(fd_t fd, struct stat *statbuf) */
.section .text.x86.asm32_syscall_int80.kfstat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kfstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x800000c5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kfstat)
	call   sys_kfstat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_kfstat)

/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
.section .text.x86.asm32_syscall_int80.kreaddirf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kreaddirf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x800000dc
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kreaddirf)
	call   sys_kreaddirf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_kreaddirf)

/* errno_t timer_settime64(timer_t timerid, syscall_ulong_t flags, struct __itimerspecx32_64 const *value, struct __itimerspecx32_64 *ovalue) */
.section .text.x86.asm32_syscall_int80.timer_settime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_settime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000104
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_settime64)
	call   sys_timer_settime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_timer_settime64)

/* errno_t timer_gettime64(timer_t timerid, struct __itimerspecx32_64 *value) */
.section .text.x86.asm32_syscall_int80.timer_gettime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_gettime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000105
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_gettime64)
	call   sys_timer_gettime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_timer_gettime64)

/* errno_t clock_settime64(clockid_t clock_id, struct __timespecx32_64 const *tp) */
.section .text.x86.asm32_syscall_int80.clock_settime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_settime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000108
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_settime64)
	call   sys_clock_settime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_clock_settime64)

/* errno_t clock_gettime64(clockid_t clock_id, struct __timespecx32_64 *tp) */
.section .text.x86.asm32_syscall_int80.clock_gettime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_gettime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000109
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_gettime64)
	call   sys_clock_gettime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_clock_gettime64)

/* errno_t clock_getres64(clockid_t clock_id, struct __timespecx32_64 *res) */
.section .text.x86.asm32_syscall_int80.clock_getres64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_getres64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000010a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_getres64)
	call   sys_clock_getres64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_clock_getres64)

/* errno_t clock_nanosleep64(clockid_t clock_id, syscall_ulong_t flags, struct __timespecx32_64 const *requested_time, struct __timespecx32_64 *remaining) */
.section .text.x86.asm32_syscall_int80.clock_nanosleep64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_nanosleep64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000010b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_nanosleep64)
	call   sys_clock_nanosleep64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_clock_nanosleep64)

/* errno_t utimes64(char const *filename, struct __timevalx32_64 const[2] times) */
.section .text.x86.asm32_syscall_int80.utimes64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_utimes64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000010f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_utimes64)
	call   sys_utimes64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_utimes64)

/* errno_t mq_timedsend64(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct __timespecx32_64 const *abs_timeout) */
.section .text.x86.asm32_syscall_int80.mq_timedsend64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_timedsend64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000117
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_timedsend64)
	call   sys_mq_timedsend64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mq_timedsend64)

/* ssize_t mq_timedreceive64(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct __timespecx32_64 const *abs_timeout) */
.section .text.x86.asm32_syscall_int80.mq_timedreceive64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_timedreceive64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000118
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_timedreceive64)
	call   sys_mq_timedreceive64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_mq_timedreceive64)

/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid64(syscall_ulong_t idtype, id_t id, struct __siginfo32_struct *infop, syscall_ulong_t options, struct __rusagex32_64 *ru) */
.section .text.x86.asm32_syscall_int80.waitid64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_waitid64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000011c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_waitid64)
	call   sys_waitid64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_waitid64)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.fmkdirat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fmkdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000128
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fmkdirat)
	call   sys_fmkdirat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fmkdirat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.fmknodat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fmknodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000129
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fmknodat)
	call   sys_fmknodat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fmknodat)

/* errno_t futimesat64(fd_t dirfd, const char *filename, struct __timevalx32_64 const[2] times) */
.section .text.x86.asm32_syscall_int80.futimesat64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_futimesat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000012b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_futimesat64)
	call   sys_futimesat64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_futimesat64)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct stat *statbuf, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.kfstatat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kfstatat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000012c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kfstatat)
	call   sys_kfstatat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_kfstatat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.frenameat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_frenameat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000012e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_frenameat)
	call   sys_frenameat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_frenameat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.fsymlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fsymlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000130
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fsymlinkat)
	call   sys_fsymlinkat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fsymlinkat)

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.freadlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_freadlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000131
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_freadlinkat)
	call   sys_freadlinkat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_freadlinkat)

/* ssize_t pselect6_64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespecx32_64 const *timeout, void const *sigmask_sigset_and_len) */
.section .text.x86.asm32_syscall_int80.pselect6_64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pselect6_64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000134
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pselect6_64)
	call   sys_pselect6_64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_pselect6_64)

/* ssize_t ppoll64(struct pollfd *fds, size_t nfds, struct __timespecx32_64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.ppoll64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ppoll64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000135
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ppoll64)
	call   sys_ppoll64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_ppoll64)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
/* errno_t utimensat64(fd_t dirfd, char const *filename, struct __timespecx32_64 const[2] times, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.utimensat64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_utimensat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000140
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_utimensat64)
	call   sys_utimensat64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_utimensat64)

/* errno_t fallocate64(fd_t fd, syscall_ulong_t mode, uint64_t offset, uint64_t length) */
.section .text.x86.asm32_syscall_int80.fallocate64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fallocate64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000144
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fallocate64)
	call   sys_fallocate64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_fallocate64)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
/* errno_t timerfd_settime64(fd_t ufd, syscall_ulong_t flags, struct __itimerspecx32_64 const *utmr, struct __itimerspecx32_64 *otmr) */
.section .text.x86.asm32_syscall_int80.timerfd_settime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timerfd_settime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000145
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timerfd_settime64)
	call   sys_timerfd_settime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_timerfd_settime64)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime64(fd_t ufd, struct __itimerspecx32_64 *otmr) */
.section .text.x86.asm32_syscall_int80.timerfd_gettime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timerfd_gettime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000146
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timerfd_gettime64)
	call   sys_timerfd_gettime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_timerfd_gettime64)

/* ssize_t preadvf(fd_t fd, struct iovec32 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.preadvf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_preadvf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000014d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_preadvf)
	call   sys_preadvf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_preadvf)

/* ssize_t pwritevf(fd_t fd, struct iovec32 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.pwritevf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pwritevf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x8000014e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebp  /* Arg #5 */
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pwritevf)
	call   sys_pwritevf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_pwritevf)

/* ssize_t recvmmsg64(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespecx32_64 *tmo) */
.section .text.x86.asm32_syscall_int80.recvmmsg64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_recvmmsg64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_int80
	.cfi_lsda 0, 0x80000151
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edi  /* Arg #4 */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_recvmmsg64)
	call   sys_recvmmsg64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_int80_recvmmsg64)










/* errno_t restart_syscall(void) */
.section .text.x86.asm32_syscall_sysenter.restart_syscall
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_restart_syscall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_restart_syscall)
	call   sys_restart_syscall
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_restart_syscall)

/* void exit(syscall_ulong_t status) */
.section .text.x86.asm32_syscall_sysenter.exit
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_exit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_exit)
	call   sys_exit
	.cfi_endproc
END(__x86_asm32_sysenter_exit)

/* pid_t fork(void) */
.section .text.x86.asm32_syscall_sysenter.fork
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fork)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_fork)
	call   sys_fork
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fork)

/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_sysenter.read
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_read)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_read)
	call   sys_read
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_read)

/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_sysenter.write
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_write)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_write)
	call   sys_write
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_write)

/* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.open
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_open)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_open)
	call   sys_open
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_open)

/* Close a given file descriptor/handle `FD' */
/* errno_t close(fd_t fd) */
.section .text.x86.asm32_syscall_sysenter.close
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_close)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_close)
	call   sys_close
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_close)

/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t waitpid(pid_t pid, int32_t *stat_loc, syscall_ulong_t options) */
.section .text.x86.asm32_syscall_sysenter.waitpid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_waitpid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_waitpid)
	call   sys_waitpid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_waitpid)

/* fd_t creat(char const *filename, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.creat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_creat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_creat)
	call   sys_creat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_creat)

/* errno_t link(char const *existing_file, char const *link_file) */
.section .text.x86.asm32_syscall_sysenter.link
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_link)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_link)
	call   sys_link
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_link)

/* errno_t unlink(char const *filename) */
.section .text.x86.asm32_syscall_sysenter.unlink
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_unlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xa
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_unlink)
	call   sys_unlink
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_unlink)

/* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
.section .text.x86.asm32_syscall_sysenter.execve
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_execve)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xb
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_execve)
	call   sys_execve
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_execve)

/* errno_t chdir(char const *path) */
.section .text.x86.asm32_syscall_sysenter.chdir
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_chdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xc
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_chdir)
	call   sys_chdir
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_chdir)

/* int32_t time(int32_t *timer) */
.section .text.x86.asm32_syscall_sysenter.time
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_time)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xd
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_time)
	call   sys_time
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_time)

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
.section .text.x86.asm32_syscall_sysenter.mknod
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mknod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xe
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mknod)
	call   sys_mknod
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mknod)

/* errno_t chmod(char const *filename, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.chmod
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_chmod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xf
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_chmod)
	call   sys_chmod
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_chmod)

/* errno_t lchown(char const *filename, uint16_t owner, uint16_t group) */
.section .text.x86.asm32_syscall_sysenter.lchown
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lchown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x10
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lchown)
	call   sys_lchown
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_lchown)

/* errno_t break(void) */
.section .text.x86.asm32_syscall_sysenter.break
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_break)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x11
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_break)
	call   sys_break
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_break)

/* errno_t linux_oldstat(char const *filename, struct linux_oldstat *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_oldstat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_oldstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x12
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_oldstat)
	call   sys_linux_oldstat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_linux_oldstat)

/* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
.section .text.x86.asm32_syscall_sysenter.lseek
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lseek)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x13
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lseek)
	call   sys_lseek
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_lseek)

/* pid_t getpid(void) */
.section .text.x86.asm32_syscall_sysenter.getpid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getpid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x14
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getpid)
	call   sys_getpid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getpid)

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t rwflag, void const *data) */
.section .text.x86.asm32_syscall_sysenter.mount
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mount)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x15
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mount)
	call   sys_mount
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mount)

/* errno_t umount(char const *special_file) */
.section .text.x86.asm32_syscall_sysenter.umount
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_umount)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x16
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_umount)
	call   sys_umount
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_umount)

/* errno_t setuid(uint16_t uid) */
.section .text.x86.asm32_syscall_sysenter.setuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x17
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setuid)
	call   sys_setuid
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setuid)

/* uint16_t getuid(void) */
.section .text.x86.asm32_syscall_sysenter.getuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x18
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getuid)
	call   sys_getuid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getuid)

/* errno_t stime(time32_t const *t) */
.section .text.x86.asm32_syscall_sysenter.stime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_stime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x19
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_stime)
	call   sys_stime
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_stime)

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
.section .text.x86.asm32_syscall_sysenter.ptrace
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ptrace)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x1a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ptrace)
	call   sys_ptrace
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ptrace)

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
.section .text.x86.asm32_syscall_sysenter.alarm
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_alarm)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x1b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_alarm)
	call   sys_alarm
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_alarm)

/* errno_t linux_oldfstat(fd_t fd, struct linux_oldstat *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_oldfstat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_oldfstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x1c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_oldfstat)
	call   sys_linux_oldfstat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_linux_oldfstat)

/* errno_t pause(void) */
.section .text.x86.asm32_syscall_sysenter.pause
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pause)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x1d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_pause)
	call   sys_pause
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_pause)

/* errno_t utime(char const *filename, struct __utimbuf32 const *times) */
.section .text.x86.asm32_syscall_sysenter.utime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_utime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x1e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_utime)
	call   sys_utime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_utime)

/* errno_t stty(void) */
.section .text.x86.asm32_syscall_sysenter.stty
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_stty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x1f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_stty)
	call   sys_stty
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_stty)

/* errno_t gtty(void) */
.section .text.x86.asm32_syscall_sysenter.gtty
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_gtty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x20
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_gtty)
	call   sys_gtty
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_gtty)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
.section .text.x86.asm32_syscall_sysenter.access
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_access)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x21
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_access)
	call   sys_access
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_access)

/* errno_t nice(syscall_slong_t inc) */
.section .text.x86.asm32_syscall_sysenter.nice
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_nice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x22
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_nice)
	call   sys_nice
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_nice)

/* errno_t ftime(struct __timebx32 *tp) */
.section .text.x86.asm32_syscall_sysenter.ftime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ftime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x23
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ftime)
	call   sys_ftime
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ftime)

/* errno_t sync(void) */
.section .text.x86.asm32_syscall_sysenter.sync
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x24
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_sync)
	call   sys_sync
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sync)

/* @param: signo: One of `SIG*' */
/* errno_t kill(pid_t pid, syscall_ulong_t signo) */
.section .text.x86.asm32_syscall_sysenter.kill
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x25
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kill)
	call   sys_kill
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_kill)

/* errno_t rename(char const *oldname, char const *newname_or_path) */
.section .text.x86.asm32_syscall_sysenter.rename
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rename)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x26
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rename)
	call   sys_rename
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_rename)

/* errno_t mkdir(char const *pathname, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.mkdir
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mkdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x27
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mkdir)
	call   sys_mkdir
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mkdir)

/* errno_t rmdir(char const *path) */
.section .text.x86.asm32_syscall_sysenter.rmdir
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rmdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x28
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rmdir)
	call   sys_rmdir
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_rmdir)

/* fd_t dup(fd_t fd) */
.section .text.x86.asm32_syscall_sysenter.dup
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_dup)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x29
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_dup)
	call   sys_dup
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_dup)

/* errno_t pipe(fd_t[2] pipedes) */
.section .text.x86.asm32_syscall_sysenter.pipe
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pipe)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x2a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pipe)
	call   sys_pipe
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_pipe)

/* clock_t times(struct tms *buf) */
.section .text.x86.asm32_syscall_sysenter.times
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_times)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x2b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_times)
	call   sys_times
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_times)

/* errno_t prof(void) */
.section .text.x86.asm32_syscall_sysenter.prof
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_prof)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x2c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_prof)
	call   sys_prof
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_prof)

/* errno_t brk(void *addr) */
.section .text.x86.asm32_syscall_sysenter.brk
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_brk)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x2d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_brk)
	call   sys_brk
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_brk)

/* errno_t setgid(uint16_t gid) */
.section .text.x86.asm32_syscall_sysenter.setgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x2e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setgid)
	call   sys_setgid
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setgid)

/* uint16_t getgid(void) */
.section .text.x86.asm32_syscall_sysenter.getgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x2f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getgid)
	call   sys_getgid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getgid)

/* @param: signo: One of `SIG*' */
/* sighandler_t signal(syscall_ulong_t signo, sighandler_t handler) */
.section .text.x86.asm32_syscall_sysenter.signal
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_signal)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x30
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_signal)
	call   sys_signal
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_signal)

/* uint16_t geteuid(void) */
.section .text.x86.asm32_syscall_sysenter.geteuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_geteuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x31
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_geteuid)
	call   sys_geteuid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_geteuid)

/* uint16_t getegid(void) */
.section .text.x86.asm32_syscall_sysenter.getegid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getegid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x32
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getegid)
	call   sys_getegid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getegid)

/* errno_t acct(char const *filename) */
.section .text.x86.asm32_syscall_sysenter.acct
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_acct)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x33
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_acct)
	call   sys_acct
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_acct)

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.umount2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_umount2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x34
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_umount2)
	call   sys_umount2
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_umount2)

/* errno_t lock(void) */
.section .text.x86.asm32_syscall_sysenter.lock
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x35
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_lock)
	call   sys_lock
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_lock)

/* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t request, void *arg) */
.section .text.x86.asm32_syscall_sysenter.ioctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ioctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x36
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ioctl)
	call   sys_ioctl
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ioctl)

/* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t cmd, void *arg) */
.section .text.x86.asm32_syscall_sysenter.fcntl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fcntl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x37
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fcntl)
	call   sys_fcntl
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fcntl)

/* errno_t mpx(void) */
.section .text.x86.asm32_syscall_sysenter.mpx
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mpx)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x38
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_mpx)
	call   sys_mpx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mpx)

/* errno_t setpgid(pid_t pid, pid_t pgid) */
.section .text.x86.asm32_syscall_sysenter.setpgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setpgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x39
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setpgid)
	call   sys_setpgid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setpgid)

/* errno_t ulimit(void) */
.section .text.x86.asm32_syscall_sysenter.ulimit
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ulimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x3a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_ulimit)
	call   sys_ulimit
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ulimit)

/* errno_t oldolduname(struct linux_oldolduname *name) */
.section .text.x86.asm32_syscall_sysenter.oldolduname
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_oldolduname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x3b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_oldolduname)
	call   sys_oldolduname
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_oldolduname)

/* mode_t umask(mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.umask
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_umask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x3c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_umask)
	call   sys_umask
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_umask)

/* errno_t chroot(char const *path) */
.section .text.x86.asm32_syscall_sysenter.chroot
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_chroot)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x3d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_chroot)
	call   sys_chroot
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_chroot)

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
.section .text.x86.asm32_syscall_sysenter.ustat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ustat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x3e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ustat)
	call   sys_ustat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ustat)

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
.section .text.x86.asm32_syscall_sysenter.dup2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_dup2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x3f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_dup2)
	call   sys_dup2
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_dup2)

/* pid_t getppid(void) */
.section .text.x86.asm32_syscall_sysenter.getppid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getppid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x40
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getppid)
	call   sys_getppid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getppid)

/* pid_t getpgrp(void) */
.section .text.x86.asm32_syscall_sysenter.getpgrp
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getpgrp)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x41
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getpgrp)
	call   sys_getpgrp
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getpgrp)

/* pid_t setsid(void) */
.section .text.x86.asm32_syscall_sysenter.setsid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setsid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x42
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_setsid)
	call   sys_setsid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setsid)

/* errno_t sigaction(syscall_ulong_t signo, struct sigaction32 const *act, struct sigaction32 *oact) */
.section .text.x86.asm32_syscall_sysenter.sigaction
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sigaction)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x43
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sigaction)
	call   sys_sigaction
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sigaction)

/* syscall_ulong_t sgetmask(void) */
.section .text.x86.asm32_syscall_sysenter.sgetmask
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sgetmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x44
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_sgetmask)
	call   sys_sgetmask
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sgetmask)

/* syscall_ulong_t ssetmask(syscall_ulong_t sigmask) */
.section .text.x86.asm32_syscall_sysenter.ssetmask
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ssetmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x45
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ssetmask)
	call   sys_ssetmask
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ssetmask)

/* errno_t setreuid(uint16_t ruid, uint16_t euid) */
.section .text.x86.asm32_syscall_sysenter.setreuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setreuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x46
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setreuid)
	call   sys_setreuid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setreuid)

/* errno_t setregid(uint16_t rgid, uint16_t egid) */
.section .text.x86.asm32_syscall_sysenter.setregid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setregid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x47
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setregid)
	call   sys_setregid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setregid)

/* errno_t sigsuspend(struct __sigset_struct const *set) */
.section .text.x86.asm32_syscall_sysenter.sigsuspend
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sigsuspend)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x48
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sigsuspend)
	call   sys_sigsuspend
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sigsuspend)

/* errno_t sigpending(struct __sigset_struct *set) */
.section .text.x86.asm32_syscall_sysenter.sigpending
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sigpending)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x49
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sigpending)
	call   sys_sigpending
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sigpending)

/* errno_t sethostname(char const *name, size_t len) */
.section .text.x86.asm32_syscall_sysenter.sethostname
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sethostname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x4a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sethostname)
	call   sys_sethostname
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sethostname)

/* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
.section .text.x86.asm32_syscall_sysenter.setrlimit
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setrlimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x4b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setrlimit)
	call   sys_setrlimit
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setrlimit)

/* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
.section .text.x86.asm32_syscall_sysenter.getrlimit
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getrlimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x4c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getrlimit)
	call   sys_getrlimit
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getrlimit)

/* errno_t getrusage(syscall_slong_t who, struct __rusagex32 *tv) */
.section .text.x86.asm32_syscall_sysenter.getrusage
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getrusage)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x4d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getrusage)
	call   sys_getrusage
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getrusage)

/* errno_t gettimeofday(struct __timevalx32 *tv, struct timezone *tz) */
.section .text.x86.asm32_syscall_sysenter.gettimeofday
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_gettimeofday)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x4e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_gettimeofday)
	call   sys_gettimeofday
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_gettimeofday)

/* errno_t settimeofday(struct __timevalx32 const *tv, struct timezone const *tz) */
.section .text.x86.asm32_syscall_sysenter.settimeofday
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_settimeofday)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x4f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_settimeofday)
	call   sys_settimeofday
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_settimeofday)

/* errno_t getgroups(size_t size, uint16_t[] list) */
.section .text.x86.asm32_syscall_sysenter.getgroups
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getgroups)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x50
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getgroups)
	call   sys_getgroups
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getgroups)

/* errno_t setgroups(size_t count, uint16_t const *groups) */
.section .text.x86.asm32_syscall_sysenter.setgroups
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setgroups)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x51
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setgroups)
	call   sys_setgroups
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setgroups)

/* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timevalx32 *timeout) */
.section .text.x86.asm32_syscall_sysenter.select
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_select)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x52
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_select)
	call   sys_select
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_select)

/* errno_t symlink(char const *link_text, char const *target_path) */
.section .text.x86.asm32_syscall_sysenter.symlink
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_symlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x53
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_symlink)
	call   sys_symlink
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_symlink)

/* errno_t linux_oldlstat(char const *filename, struct linux_oldstat *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_oldlstat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_oldlstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x54
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_oldlstat)
	call   sys_linux_oldlstat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_linux_oldlstat)

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
.section .text.x86.asm32_syscall_sysenter.readlink
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x55
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readlink)
	call   sys_readlink
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_readlink)

/* errno_t uselib(char const *library) */
.section .text.x86.asm32_syscall_sysenter.uselib
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_uselib)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x56
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_uselib)
	call   sys_uselib
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_uselib)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
.section .text.x86.asm32_syscall_sysenter.swapon
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_swapon)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x57
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_swapon)
	call   sys_swapon
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_swapon)

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
.section .text.x86.asm32_syscall_sysenter.reboot
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_reboot)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x58
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_reboot)
	call   sys_reboot
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_reboot)

/* Returns `0' to indicate end-of-directory; 1 to to indicate success */
/* errno_t readdir(fd_t fd, struct old_linux_dirent *dirp, size_t count) */
.section .text.x86.asm32_syscall_sysenter.readdir
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x59
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readdir)
	call   sys_readdir
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_readdir)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
.section .text.x86.asm32_syscall_sysenter.mmap
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mmap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x5a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mmap)
	call   sys_mmap
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mmap)

/* errno_t munmap(void *addr, size_t len) */
.section .text.x86.asm32_syscall_sysenter.munmap
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_munmap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x5b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_munmap)
	call   sys_munmap
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_munmap)

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
.section .text.x86.asm32_syscall_sysenter.truncate
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_truncate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x5c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_truncate)
	call   sys_truncate
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_truncate)

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
.section .text.x86.asm32_syscall_sysenter.ftruncate
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ftruncate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x5d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ftruncate)
	call   sys_ftruncate
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ftruncate)

/* errno_t fchmod(fd_t fd, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.fchmod
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchmod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x5e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchmod)
	call   sys_fchmod
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fchmod)

/* errno_t fchown(fd_t fd, uint16_t owner, uint16_t group) */
.section .text.x86.asm32_syscall_sysenter.fchown
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x5f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchown)
	call   sys_fchown
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fchown)

/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
.section .text.x86.asm32_syscall_sysenter.getpriority
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getpriority)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x60
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getpriority)
	call   sys_getpriority
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getpriority)

/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
.section .text.x86.asm32_syscall_sysenter.setpriority
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setpriority)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x61
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setpriority)
	call   sys_setpriority
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setpriority)

/* errno_t profil(uint16_t *sample_buffer, size_t size, size_t offset, syscall_ulong_t scale) */
.section .text.x86.asm32_syscall_sysenter.profil
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_profil)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x62
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_profil)
	call   sys_profil
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_profil)

/* errno_t statfs(char const *file, struct __statfs32 *buf) */
.section .text.x86.asm32_syscall_sysenter.statfs
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_statfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x63
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_statfs)
	call   sys_statfs
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_statfs)

/* errno_t fstatfs(fd_t file, struct __statfs32 *buf) */
.section .text.x86.asm32_syscall_sysenter.fstatfs
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fstatfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x64
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fstatfs)
	call   sys_fstatfs
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fstatfs)

/* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
.section .text.x86.asm32_syscall_sysenter.ioperm
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ioperm)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x65
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ioperm)
	call   sys_ioperm
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ioperm)

/* errno_t socketcall(int call, unsigned long *args) */
.section .text.x86.asm32_syscall_sysenter.socketcall
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_socketcall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x66
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_socketcall)
	call   sys_socketcall
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_socketcall)

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
.section .text.x86.asm32_syscall_sysenter.syslog
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_syslog)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x67
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_syslog)
	call   sys_syslog
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_syslog)

/* errno_t setitimer(syscall_ulong_t which, struct __itimerval32 const *newval, struct __itimerval32 *oldval) */
.section .text.x86.asm32_syscall_sysenter.setitimer
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setitimer)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x68
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setitimer)
	call   sys_setitimer
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setitimer)

/* errno_t getitimer(syscall_ulong_t which, struct __itimerval32 *curr_value) */
.section .text.x86.asm32_syscall_sysenter.getitimer
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getitimer)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x69
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getitimer)
	call   sys_getitimer
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getitimer)

/* errno_t linux_stat32(char const *filename, struct linux_stat32 *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_stat32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_stat32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x6a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_stat32)
	call   sys_linux_stat32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_linux_stat32)

/* errno_t linux_lstat32(char const *filename, struct linux_stat32 *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_lstat32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_lstat32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x6b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_lstat32)
	call   sys_linux_lstat32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_linux_lstat32)

/* errno_t linux_fstat32(fd_t fd, struct linux_stat32 *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_fstat32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_fstat32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x6c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_fstat32)
	call   sys_linux_fstat32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_linux_fstat32)

/* errno_t olduname(struct linux_olduname *name) */
.section .text.x86.asm32_syscall_sysenter.olduname
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_olduname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x6d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_olduname)
	call   sys_olduname
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_olduname)

/* errno_t iopl(syscall_ulong_t level) */
.section .text.x86.asm32_syscall_sysenter.iopl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_iopl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x6e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_iopl)
	call   sys_iopl
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_iopl)

/* errno_t vhangup(void) */
.section .text.x86.asm32_syscall_sysenter.vhangup
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_vhangup)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x6f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_vhangup)
	call   sys_vhangup
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_vhangup)

/* errno_t idle(void) */
.section .text.x86.asm32_syscall_sysenter.idle
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_idle)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x70
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_idle)
	call   sys_idle
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_idle)

/* errno_t vm86old(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.vm86old
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_vm86old)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x71
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_vm86old)
	call   sys_vm86old
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_vm86old)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct __rusagex32 *usage) */
.section .text.x86.asm32_syscall_sysenter.wait4
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_wait4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x72
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_wait4)
	call   sys_wait4
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_wait4)

/* errno_t swapoff(char const *pathname) */
.section .text.x86.asm32_syscall_sysenter.swapoff
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_swapoff)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x73
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_swapoff)
	call   sys_swapoff
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_swapoff)

/* errno_t sysinfo(struct sysinfo *info) */
.section .text.x86.asm32_syscall_sysenter.sysinfo
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sysinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x74
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sysinfo)
	call   sys_sysinfo
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sysinfo)

/* errno_t ipc(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.ipc
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ipc)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x75
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ipc)
	call   sys_ipc
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ipc)

/* errno_t fsync(fd_t fd) */
.section .text.x86.asm32_syscall_sysenter.fsync
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fsync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x76
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fsync)
	call   sys_fsync
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fsync)

/* Restore the specified register state when returning from a signal handler
 * Note that the order and locations of arguments taken by this system call
 * are of great importance, as they must match what is encoded by the kernel
 * within `sighand_raise_signal()'
 * The order chosen is also important, as it is selected such that arguments
 * are only passed through registers that are preserved by CDECL */
/* void sigreturn(struct fpustate32 const *restore_fpu, syscall_ulong_t unused1, syscall_ulong_t unused2, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info32 *sc_info, struct ucpustate32 const *restore_cpu) */
.section .text.x86.asm32_syscall_sysenter.sigreturn
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sigreturn)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x77
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sigreturn)
	call   sys_sigreturn
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sigreturn)

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, uintptr_t newtls, pid_t *ctid) */
.section .text.x86.asm32_syscall_sysenter.clone
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clone)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x78
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clone)
	call   sys_clone
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_clone)

/* errno_t setdomainname(char const *name, size_t len) */
.section .text.x86.asm32_syscall_sysenter.setdomainname
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setdomainname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x79
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setdomainname)
	call   sys_setdomainname
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setdomainname)

/* errno_t uname(struct utsname *name) */
.section .text.x86.asm32_syscall_sysenter.uname
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_uname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x7a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_uname)
	call   sys_uname
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_uname)

/* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
.section .text.x86.asm32_syscall_sysenter.modify_ldt
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_modify_ldt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x7b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_modify_ldt)
	call   sys_modify_ldt
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_modify_ldt)

/* errno_t adjtimex(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.adjtimex
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_adjtimex)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x7c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_adjtimex)
	call   sys_adjtimex
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_adjtimex)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
.section .text.x86.asm32_syscall_sysenter.mprotect
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mprotect)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x7d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mprotect)
	call   sys_mprotect
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mprotect)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset) */
.section .text.x86.asm32_syscall_sysenter.sigprocmask
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sigprocmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x7e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sigprocmask)
	call   sys_sigprocmask
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sigprocmask)

/* errno_t create_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.create_module
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_create_module)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x7f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_create_module)
	call   sys_create_module
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_create_module)

/* errno_t init_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.init_module
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_init_module)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_init_module)
	call   sys_init_module
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_init_module)

/* errno_t delete_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.delete_module
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_delete_module)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x81
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_delete_module)
	call   sys_delete_module
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_delete_module)

/* errno_t get_kernel_syms(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.get_kernel_syms
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_get_kernel_syms)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x82
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_get_kernel_syms)
	call   sys_get_kernel_syms
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_get_kernel_syms)

/* errno_t quotactl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.quotactl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_quotactl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x83
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_quotactl)
	call   sys_quotactl
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_quotactl)

/* pid_t getpgid(pid_t pid) */
.section .text.x86.asm32_syscall_sysenter.getpgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getpgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x84
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getpgid)
	call   sys_getpgid
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getpgid)

/* errno_t fchdir(fd_t fd) */
.section .text.x86.asm32_syscall_sysenter.fchdir
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x85
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchdir)
	call   sys_fchdir
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fchdir)

/* errno_t bdflush(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.bdflush
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_bdflush)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x86
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_bdflush)
	call   sys_bdflush
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_bdflush)

/* errno_t sysfs(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.sysfs
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sysfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x87
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sysfs)
	call   sys_sysfs
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sysfs)

/* errno_t personality(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.personality
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_personality)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x88
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_personality)
	call   sys_personality
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_personality)

/* errno_t afs_syscall(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.afs_syscall
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_afs_syscall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x89
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_afs_syscall)
	call   sys_afs_syscall
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_afs_syscall)

/* errno_t setfsuid(uint16_t uid) */
.section .text.x86.asm32_syscall_sysenter.setfsuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setfsuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setfsuid)
	call   sys_setfsuid
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setfsuid)

/* errno_t setfsgid(uint16_t gid) */
.section .text.x86.asm32_syscall_sysenter.setfsgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setfsgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setfsgid)
	call   sys_setfsgid
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setfsgid)

/* errno_t _llseek(fd_t fd, int64_t offset, uint64_t *result, syscall_ulong_t whence) */
.section .text.x86.asm32_syscall_sysenter._llseek
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter__llseek)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys__llseek)
	call   sys__llseek
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter__llseek)

/* ssize_t getdents(fd_t fd, struct linux_dirent *dirp, size_t count) */
.section .text.x86.asm32_syscall_sysenter.getdents
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getdents)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getdents)
	call   sys_getdents
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getdents)

/* errno_t _newselect(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter._newselect
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter__newselect)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys__newselect)
	call   sys__newselect
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter__newselect)

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
.section .text.x86.asm32_syscall_sysenter.flock
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_flock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_flock)
	call   sys_flock
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_flock)

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.msync
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_msync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x90
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_msync)
	call   sys_msync
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_msync)

/* ssize_t readv(fd_t fd, struct iovec32 const *iovec, size_t count) */
.section .text.x86.asm32_syscall_sysenter.readv
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x91
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readv)
	call   sys_readv
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_readv)

/* ssize_t writev(fd_t fd, struct iovec32 const *iovec, size_t count) */
.section .text.x86.asm32_syscall_sysenter.writev
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_writev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x92
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_writev)
	call   sys_writev
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_writev)

/* pid_t getsid(pid_t pid) */
.section .text.x86.asm32_syscall_sysenter.getsid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getsid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x93
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getsid)
	call   sys_getsid
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getsid)

/* errno_t fdatasync(fd_t fd) */
.section .text.x86.asm32_syscall_sysenter.fdatasync
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fdatasync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x94
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fdatasync)
	call   sys_fdatasync
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fdatasync)

/* errno_t _sysctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter._sysctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter__sysctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x95
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys__sysctl)
	call   sys__sysctl
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter__sysctl)

/* errno_t mlock(void const *addr, size_t len) */
.section .text.x86.asm32_syscall_sysenter.mlock
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mlock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x96
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mlock)
	call   sys_mlock
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mlock)

/* errno_t munlock(void const *addr, size_t len) */
.section .text.x86.asm32_syscall_sysenter.munlock
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_munlock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x97
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_munlock)
	call   sys_munlock
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_munlock)

/* errno_t mlockall(syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.mlockall
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mlockall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x98
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mlockall)
	call   sys_mlockall
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mlockall)

/* errno_t munlockall(void) */
.section .text.x86.asm32_syscall_sysenter.munlockall
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_munlockall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x99
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_munlockall)
	call   sys_munlockall
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_munlockall)

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
.section .text.x86.asm32_syscall_sysenter.sched_setparam
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_setparam)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x9a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_setparam)
	call   sys_sched_setparam
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sched_setparam)

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
.section .text.x86.asm32_syscall_sysenter.sched_getparam
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_getparam)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x9b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_getparam)
	call   sys_sched_getparam
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sched_getparam)

/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
.section .text.x86.asm32_syscall_sysenter.sched_setscheduler
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_setscheduler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x9c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_setscheduler)
	call   sys_sched_setscheduler
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sched_setscheduler)

/* syscall_slong_t sched_getscheduler(pid_t pid) */
.section .text.x86.asm32_syscall_sysenter.sched_getscheduler
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_getscheduler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x9d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_getscheduler)
	call   sys_sched_getscheduler
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sched_getscheduler)

/* errno_t sched_yield(void) */
.section .text.x86.asm32_syscall_sysenter.sched_yield
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_yield)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x9e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_sched_yield)
	call   sys_sched_yield
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sched_yield)

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
.section .text.x86.asm32_syscall_sysenter.sched_get_priority_max
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_get_priority_max)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x9f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_get_priority_max)
	call   sys_sched_get_priority_max
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sched_get_priority_max)

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
.section .text.x86.asm32_syscall_sysenter.sched_get_priority_min
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_get_priority_min)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xa0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_get_priority_min)
	call   sys_sched_get_priority_min
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sched_get_priority_min)

/* errno_t sched_rr_get_interval(pid_t pid, struct __timespecx32 *tms) */
.section .text.x86.asm32_syscall_sysenter.sched_rr_get_interval
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_rr_get_interval)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xa1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_rr_get_interval)
	call   sys_sched_rr_get_interval
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sched_rr_get_interval)

/* errno_t nanosleep(struct __timespecx32 const *req, struct __timespecx32 *rem) */
.section .text.x86.asm32_syscall_sysenter.nanosleep
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_nanosleep)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xa2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_nanosleep)
	call   sys_nanosleep
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_nanosleep)

/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
.section .text.x86.asm32_syscall_sysenter.mremap
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mremap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xa3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mremap)
	call   sys_mremap
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mremap)

/* errno_t setresuid(uint16_t ruid, uint16_t euid, uint16_t suid) */
.section .text.x86.asm32_syscall_sysenter.setresuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setresuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xa4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setresuid)
	call   sys_setresuid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setresuid)

/* errno_t getresuid(uint16_t *ruid, uint16_t *euid, uint16_t *suid) */
.section .text.x86.asm32_syscall_sysenter.getresuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getresuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xa5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getresuid)
	call   sys_getresuid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getresuid)

/* errno_t vm86(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.vm86
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_vm86)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xa6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_vm86)
	call   sys_vm86
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_vm86)

/* errno_t query_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.query_module
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_query_module)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xa7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_query_module)
	call   sys_query_module
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_query_module)

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
.section .text.x86.asm32_syscall_sysenter.poll
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_poll)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xa8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_poll)
	call   sys_poll
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_poll)

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.nfsservctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_nfsservctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xa9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_nfsservctl)
	call   sys_nfsservctl
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_nfsservctl)

/* errno_t setresgid(uint16_t rgid, uint16_t egid, uint16_t sgid) */
.section .text.x86.asm32_syscall_sysenter.setresgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setresgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xaa
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setresgid)
	call   sys_setresgid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setresgid)

/* errno_t getresgid(uint16_t *rgid, uint16_t *egid, uint16_t *sgid) */
.section .text.x86.asm32_syscall_sysenter.getresgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getresgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xab
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getresgid)
	call   sys_getresgid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getresgid)

/* errno_t prctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.prctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_prctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xac
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_prctl)
	call   sys_prctl
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_prctl)

/* void rt_sigreturn(struct fpustate const *restore_fpu, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info *sc_info, struct ucpustate const *restore_cpu) */
.section .text.x86.asm32_syscall_sysenter.rt_sigreturn
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigreturn)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xad
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigreturn)
	call   sys_rt_sigreturn
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_rt_sigreturn)

/* errno_t rt_sigaction(syscall_ulong_t signo, struct sigaction32 const *act, struct sigaction32 *oact, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.rt_sigaction
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigaction)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xae
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigaction)
	call   sys_rt_sigaction
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_rt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.rt_sigprocmask
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigprocmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xaf
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigprocmask)
	call   sys_rt_sigprocmask
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_rt_sigprocmask)

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.rt_sigpending
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigpending)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xb0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigpending)
	call   sys_rt_sigpending
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_rt_sigpending)

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo32_struct *info, struct __timespecx32 const *timeout, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.rt_sigtimedwait
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigtimedwait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xb1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigtimedwait)
	call   sys_rt_sigtimedwait
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_rt_sigtimedwait)

/* @param: signo: One of `SIG*' */
/* errno_t rt_sigqueueinfo(pid_t tgid, syscall_ulong_t signo, struct __siginfo32_struct const *uinfo) */
.section .text.x86.asm32_syscall_sysenter.rt_sigqueueinfo
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigqueueinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xb2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigqueueinfo)
	call   sys_rt_sigqueueinfo
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_rt_sigqueueinfo)

/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.rt_sigsuspend
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigsuspend)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xb3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigsuspend)
	call   sys_rt_sigsuspend
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_rt_sigsuspend)

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
.section .text.x86.asm32_syscall_sysenter.pread64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pread64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xb4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pread64)
	call   sys_pread64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_pread64)

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
.section .text.x86.asm32_syscall_sysenter.pwrite64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pwrite64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xb5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pwrite64)
	call   sys_pwrite64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_pwrite64)

/* errno_t chown(char const *filename, uint16_t owner, uint16_t group) */
.section .text.x86.asm32_syscall_sysenter.chown
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_chown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xb6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_chown)
	call   sys_chown
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_chown)

/* ssize_t getcwd(char *buf, size_t size) */
.section .text.x86.asm32_syscall_sysenter.getcwd
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getcwd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xb7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getcwd)
	call   sys_getcwd
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getcwd)

/* errno_t capget(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.capget
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_capget)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xb8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_capget)
	call   sys_capget
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_capget)

/* errno_t capset(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.capset
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_capset)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xb9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_capset)
	call   sys_capset
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_capset)

/* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
.section .text.x86.asm32_syscall_sysenter.sigaltstack
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sigaltstack)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xba
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sigaltstack)
	call   sys_sigaltstack
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sigaltstack)

/* ssize_t sendfile(fd_t out_fd, fd_t in_fd, syscall_ulong_t *offset, size_t count) */
.section .text.x86.asm32_syscall_sysenter.sendfile
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sendfile)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xbb
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sendfile)
	call   sys_sendfile
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sendfile)

/* errno_t getpmsg(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.getpmsg
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getpmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xbc
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getpmsg)
	call   sys_getpmsg
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getpmsg)

/* errno_t putpmsg(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.putpmsg
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_putpmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xbd
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_putpmsg)
	call   sys_putpmsg
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_putpmsg)

/* pid_t vfork(void) */
.section .text.x86.asm32_syscall_sysenter.vfork
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_vfork)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xbe
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_vfork)
	call   sys_vfork
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_vfork)

/* errno_t ugetrlimit(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.ugetrlimit
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ugetrlimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xbf
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ugetrlimit)
	call   sys_ugetrlimit
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ugetrlimit)

/* void *mmap2(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t pgoffset) */
.section .text.x86.asm32_syscall_sysenter.mmap2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mmap2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xc0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mmap2)
	call   sys_mmap2
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mmap2)

/* errno_t truncate64(char const *filename, uint64_t length) */
.section .text.x86.asm32_syscall_sysenter.truncate64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_truncate64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xc1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_truncate64)
	call   sys_truncate64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_truncate64)

/* errno_t ftruncate64(fd_t fd, uint64_t length) */
.section .text.x86.asm32_syscall_sysenter.ftruncate64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ftruncate64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xc2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ftruncate64)
	call   sys_ftruncate64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ftruncate64)

/* errno_t linux_stat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_stat64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_stat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xc3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_stat64)
	call   sys_linux_stat64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_linux_stat64)

/* errno_t linux_lstat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_lstat64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_lstat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xc4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_lstat64)
	call   sys_linux_lstat64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_linux_lstat64)

/* errno_t linux_fstat64(fd_t fd, struct linux_stat64 *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_fstat64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_fstat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xc5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_fstat64)
	call   sys_linux_fstat64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_linux_fstat64)

/* errno_t lchown32(char const *filename, uint32_t owner, uint32_t group) */
.section .text.x86.asm32_syscall_sysenter.lchown32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lchown32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xc6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lchown32)
	call   sys_lchown32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_lchown32)

/* uint32_t getuid32(void) */
.section .text.x86.asm32_syscall_sysenter.getuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xc7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getuid32)
	call   sys_getuid32
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getuid32)

/* uint32_t getgid32(void) */
.section .text.x86.asm32_syscall_sysenter.getgid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xc8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getgid32)
	call   sys_getgid32
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getgid32)

/* uint32_t geteuid32(void) */
.section .text.x86.asm32_syscall_sysenter.geteuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_geteuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xc9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_geteuid32)
	call   sys_geteuid32
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_geteuid32)

/* uint32_t getegid32(void) */
.section .text.x86.asm32_syscall_sysenter.getegid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getegid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xca
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getegid32)
	call   sys_getegid32
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getegid32)

/* errno_t setreuid32(uint32_t ruid, uint32_t euid) */
.section .text.x86.asm32_syscall_sysenter.setreuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setreuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xcb
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setreuid32)
	call   sys_setreuid32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setreuid32)

/* errno_t setregid32(uint32_t rgid, uint32_t egid) */
.section .text.x86.asm32_syscall_sysenter.setregid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setregid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xcc
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setregid32)
	call   sys_setregid32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setregid32)

/* errno_t getgroups32(size_t size, uint32_t[] list) */
.section .text.x86.asm32_syscall_sysenter.getgroups32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getgroups32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xcd
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getgroups32)
	call   sys_getgroups32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getgroups32)

/* errno_t setgroups32(size_t count, uint32_t const *groups) */
.section .text.x86.asm32_syscall_sysenter.setgroups32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setgroups32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xce
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setgroups32)
	call   sys_setgroups32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setgroups32)

/* errno_t fchown32(fd_t fd, uint32_t owner, uint32_t group) */
.section .text.x86.asm32_syscall_sysenter.fchown32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchown32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xcf
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchown32)
	call   sys_fchown32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fchown32)

/* errno_t setresuid32(uint32_t ruid, uint32_t euid, uint32_t suid) */
.section .text.x86.asm32_syscall_sysenter.setresuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setresuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xd0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setresuid32)
	call   sys_setresuid32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setresuid32)

/* errno_t getresuid32(uint32_t *ruid, uint32_t *euid, uint32_t *suid) */
.section .text.x86.asm32_syscall_sysenter.getresuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getresuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xd1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getresuid32)
	call   sys_getresuid32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getresuid32)

/* errno_t setresgid32(uint32_t rgid, uint32_t egid, uint32_t sgid) */
.section .text.x86.asm32_syscall_sysenter.setresgid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setresgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xd2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setresgid32)
	call   sys_setresgid32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setresgid32)

/* errno_t getresgid32(uint32_t *rgid, uint32_t *egid, uint32_t *sgid) */
.section .text.x86.asm32_syscall_sysenter.getresgid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getresgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xd3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getresgid32)
	call   sys_getresgid32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getresgid32)

/* errno_t chown32(char const *filename, uint32_t owner, uint32_t group) */
.section .text.x86.asm32_syscall_sysenter.chown32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_chown32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xd4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_chown32)
	call   sys_chown32
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_chown32)

/* errno_t setuid32(uint32_t uid) */
.section .text.x86.asm32_syscall_sysenter.setuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xd5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setuid32)
	call   sys_setuid32
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setuid32)

/* errno_t setgid32(uint32_t gid) */
.section .text.x86.asm32_syscall_sysenter.setgid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xd6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setgid32)
	call   sys_setgid32
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setgid32)

/* errno_t setfsuid32(uint32_t uid) */
.section .text.x86.asm32_syscall_sysenter.setfsuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setfsuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xd7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setfsuid32)
	call   sys_setfsuid32
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setfsuid32)

/* errno_t setfsgid32(uint32_t gid) */
.section .text.x86.asm32_syscall_sysenter.setfsgid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setfsgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xd8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setfsgid32)
	call   sys_setfsgid32
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setfsgid32)

/* errno_t pivot_root(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.pivot_root
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pivot_root)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xd9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pivot_root)
	call   sys_pivot_root
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_pivot_root)

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
.section .text.x86.asm32_syscall_sysenter.mincore
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mincore)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xda
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mincore)
	call   sys_mincore
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mincore)

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
.section .text.x86.asm32_syscall_sysenter.madvise
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_madvise)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xdb
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_madvise)
	call   sys_madvise
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_madvise)

/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *dirp, size_t count) */
.section .text.x86.asm32_syscall_sysenter.getdents64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getdents64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xdc
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getdents64)
	call   sys_getdents64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getdents64)

/* syscall_slong_t fcntl64(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.x86.asm32_syscall_sysenter.fcntl64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fcntl64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xdd
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fcntl64)
	call   sys_fcntl64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fcntl64)

/* pid_t gettid(void) */
.section .text.x86.asm32_syscall_sysenter.gettid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_gettid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xe0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_gettid)
	call   sys_gettid
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_gettid)

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
.section .text.x86.asm32_syscall_sysenter.readahead
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readahead)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xe1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readahead)
	call   sys_readahead
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_readahead)

/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.setxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xe2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setxattr)
	call   sys_setxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setxattr)

/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.lsetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lsetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xe3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lsetxattr)
	call   sys_lsetxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_lsetxattr)

/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.fsetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fsetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xe4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fsetxattr)
	call   sys_fsetxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fsetxattr)

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_sysenter.getxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xe5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getxattr)
	call   sys_getxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getxattr)

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_sysenter.lgetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lgetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xe6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lgetxattr)
	call   sys_lgetxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_lgetxattr)

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_sysenter.fgetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fgetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xe7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fgetxattr)
	call   sys_fgetxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fgetxattr)

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.x86.asm32_syscall_sysenter.listxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_listxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xe8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_listxattr)
	call   sys_listxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_listxattr)

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.x86.asm32_syscall_sysenter.llistxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_llistxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xe9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_llistxattr)
	call   sys_llistxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_llistxattr)

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
.section .text.x86.asm32_syscall_sysenter.flistxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_flistxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xea
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_flistxattr)
	call   sys_flistxattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_flistxattr)

/* errno_t removexattr(char const *path, char const *name) */
.section .text.x86.asm32_syscall_sysenter.removexattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_removexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xeb
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_removexattr)
	call   sys_removexattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_removexattr)

/* errno_t lremovexattr(char const *path, char const *name) */
.section .text.x86.asm32_syscall_sysenter.lremovexattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lremovexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xec
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lremovexattr)
	call   sys_lremovexattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_lremovexattr)

/* errno_t fremovexattr(int fd, char const *name) */
.section .text.x86.asm32_syscall_sysenter.fremovexattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fremovexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xed
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fremovexattr)
	call   sys_fremovexattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fremovexattr)

/* errno_t tkill(pid_t tid, syscall_ulong_t signo) */
.section .text.x86.asm32_syscall_sysenter.tkill
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_tkill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xee
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_tkill)
	call   sys_tkill
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_tkill)

/* ssize_t sendfile64(fd_t out_fd, fd_t in_fd, uint64_t *offset, size_t count) */
.section .text.x86.asm32_syscall_sysenter.sendfile64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sendfile64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xef
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sendfile64)
	call   sys_sendfile64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sendfile64)

/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct __timespecx32 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
.section .text.x86.asm32_syscall_sysenter.futex
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_futex)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xf0
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_futex)
	call   sys_futex
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_futex)

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
.section .text.x86.asm32_syscall_sysenter.sched_setaffinity
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_setaffinity)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xf1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_setaffinity)
	call   sys_sched_setaffinity
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sched_setaffinity)

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
.section .text.x86.asm32_syscall_sysenter.sched_getaffinity
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_getaffinity)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xf2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_getaffinity)
	call   sys_sched_getaffinity
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sched_getaffinity)

/* errno_t set_thread_area(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.set_thread_area
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_set_thread_area)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xf3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_set_thread_area)
	call   sys_set_thread_area
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_set_thread_area)

/* errno_t get_thread_area(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.get_thread_area
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_get_thread_area)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xf4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_get_thread_area)
	call   sys_get_thread_area
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_get_thread_area)

/* errno_t io_setup(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.io_setup
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_io_setup)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xf5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_io_setup)
	call   sys_io_setup
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_io_setup)

/* errno_t io_destroy(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.io_destroy
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_io_destroy)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xf6
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_io_destroy)
	call   sys_io_destroy
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_io_destroy)

/* errno_t io_getevents(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.io_getevents
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_io_getevents)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xf7
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_io_getevents)
	call   sys_io_getevents
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_io_getevents)

/* errno_t io_submit(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.io_submit
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_io_submit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xf8
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_io_submit)
	call   sys_io_submit
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_io_submit)

/* errno_t io_cancel(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.io_cancel
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_io_cancel)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xf9
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_io_cancel)
	call   sys_io_cancel
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_io_cancel)

/* errno_t fadvise64(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.fadvise64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fadvise64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xfa
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fadvise64)
	call   sys_fadvise64
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fadvise64)

/* void exit_group(syscall_ulong_t exit_code) */
.section .text.x86.asm32_syscall_sysenter.exit_group
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_exit_group)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xfc
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_exit_group)
	call   sys_exit_group
	.cfi_endproc
END(__x86_asm32_sysenter_exit_group)

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.lookup_dcookie
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lookup_dcookie)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xfd
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lookup_dcookie)
	call   sys_lookup_dcookie
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_lookup_dcookie)

/* fd_t epoll_create(syscall_ulong_t size) */
.section .text.x86.asm32_syscall_sysenter.epoll_create
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_epoll_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xfe
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_epoll_create)
	call   sys_epoll_create
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_epoll_create)

/* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.x86.asm32_syscall_sysenter.epoll_ctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_epoll_ctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0xff
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_epoll_ctl)
	call   sys_epoll_ctl
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_epoll_ctl)

/* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.x86.asm32_syscall_sysenter.epoll_wait
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_epoll_wait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x100
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_epoll_wait)
	call   sys_epoll_wait
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_epoll_wait)

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.remap_file_pages
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_remap_file_pages)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x101
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_remap_file_pages)
	call   sys_remap_file_pages
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_remap_file_pages)

/* pid_t set_tid_address(pid_t *tidptr) */
.section .text.x86.asm32_syscall_sysenter.set_tid_address
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_set_tid_address)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x102
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_set_tid_address)
	call   sys_set_tid_address
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_set_tid_address)

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
.section .text.x86.asm32_syscall_sysenter.timer_create
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x103
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_create)
	call   sys_timer_create
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_timer_create)

/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct __itimerspecx32 const *value, struct __itimerspecx32 *ovalue) */
.section .text.x86.asm32_syscall_sysenter.timer_settime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x104
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_settime)
	call   sys_timer_settime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_timer_settime)

/* errno_t timer_gettime(timer_t timerid, struct __itimerspecx32 *value) */
.section .text.x86.asm32_syscall_sysenter.timer_gettime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x105
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_gettime)
	call   sys_timer_gettime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_timer_gettime)

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
.section .text.x86.asm32_syscall_sysenter.timer_getoverrun
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_getoverrun)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x106
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_getoverrun)
	call   sys_timer_getoverrun
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_timer_getoverrun)

/* errno_t timer_delete(timer_t timerid) */
.section .text.x86.asm32_syscall_sysenter.timer_delete
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_delete)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x107
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_delete)
	call   sys_timer_delete
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_timer_delete)

/* errno_t clock_settime(clockid_t clock_id, struct __timespecx32 const *tp) */
.section .text.x86.asm32_syscall_sysenter.clock_settime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x108
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_settime)
	call   sys_clock_settime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_clock_settime)

/* errno_t clock_gettime(clockid_t clock_id, struct __timespecx32 *tp) */
.section .text.x86.asm32_syscall_sysenter.clock_gettime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x109
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_gettime)
	call   sys_clock_gettime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_clock_gettime)

/* errno_t clock_getres(clockid_t clock_id, struct __timespecx32 *res) */
.section .text.x86.asm32_syscall_sysenter.clock_getres
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_getres)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x10a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_getres)
	call   sys_clock_getres
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_clock_getres)

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct __timespecx32 const *requested_time, struct __timespecx32 *remaining) */
.section .text.x86.asm32_syscall_sysenter.clock_nanosleep
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_nanosleep)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x10b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_nanosleep)
	call   sys_clock_nanosleep
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_clock_nanosleep)

/* errno_t statfs64(char const *file, struct statfs64 *buf) */
.section .text.x86.asm32_syscall_sysenter.statfs64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_statfs64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x10c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_statfs64)
	call   sys_statfs64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_statfs64)

/* errno_t fstatfs64(fd_t file, struct statfs64 *buf) */
.section .text.x86.asm32_syscall_sysenter.fstatfs64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fstatfs64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x10d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fstatfs64)
	call   sys_fstatfs64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fstatfs64)

/* errno_t tgkill(pid_t tgid, pid_t tid, syscall_ulong_t signo) */
.section .text.x86.asm32_syscall_sysenter.tgkill
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_tgkill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x10e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_tgkill)
	call   sys_tgkill
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_tgkill)

/* errno_t utimes(char const *filename, struct __timevalx32 const[2] times) */
.section .text.x86.asm32_syscall_sysenter.utimes
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_utimes)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x10f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_utimes)
	call   sys_utimes
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_utimes)

/* errno_t fadvise64_64(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.fadvise64_64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fadvise64_64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x110
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fadvise64_64)
	call   sys_fadvise64_64
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fadvise64_64)

/* errno_t vserver(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.vserver
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_vserver)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x111
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_vserver)
	call   sys_vserver
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_vserver)

/* errno_t mbind(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.mbind
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mbind)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x112
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mbind)
	call   sys_mbind
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mbind)

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.get_mempolicy
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_get_mempolicy)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x113
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_get_mempolicy)
	call   sys_get_mempolicy
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_get_mempolicy)

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.set_mempolicy
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_set_mempolicy)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x114
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_set_mempolicy)
	call   sys_set_mempolicy
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_set_mempolicy)

/* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.mq_open
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_open)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x115
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_open)
	call   sys_mq_open
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mq_open)

/* errno_t mq_unlink(char const *name) */
.section .text.x86.asm32_syscall_sysenter.mq_unlink
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_unlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x116
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_unlink)
	call   sys_mq_unlink
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mq_unlink)

/* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct __timespecx32 const *abs_timeout) */
.section .text.x86.asm32_syscall_sysenter.mq_timedsend
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_timedsend)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x117
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_timedsend)
	call   sys_mq_timedsend
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mq_timedsend)

/* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct __timespecx32 const *abs_timeout) */
.section .text.x86.asm32_syscall_sysenter.mq_timedreceive
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_timedreceive)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x118
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_timedreceive)
	call   sys_mq_timedreceive
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mq_timedreceive)

/* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
.section .text.x86.asm32_syscall_sysenter.mq_notify
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_notify)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x119
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_notify)
	call   sys_mq_notify
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mq_notify)

/* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
.section .text.x86.asm32_syscall_sysenter.mq_getsetattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_getsetattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x11a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_getsetattr)
	call   sys_mq_getsetattr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mq_getsetattr)

/* errno_t kexec_load(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.kexec_load
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kexec_load)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x11b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kexec_load)
	call   sys_kexec_load
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_kexec_load)

/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo32_struct *infop, syscall_ulong_t options, struct __rusagex32 *ru) */
.section .text.x86.asm32_syscall_sysenter.waitid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_waitid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x11c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_waitid)
	call   sys_waitid
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_waitid)

/* errno_t add_key(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.add_key
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_add_key)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x11e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_add_key)
	call   sys_add_key
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_add_key)

/* errno_t request_key(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.request_key
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_request_key)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x11f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_request_key)
	call   sys_request_key
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_request_key)

/* errno_t keyctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.keyctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_keyctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x120
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_keyctl)
	call   sys_keyctl
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_keyctl)

/* errno_t ioprio_set(syscall_ulong_t which, syscall_ulong_t who, syscall_ulong_t ioprio) */
.section .text.x86.asm32_syscall_sysenter.ioprio_set
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ioprio_set)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x121
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ioprio_set)
	call   sys_ioprio_set
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ioprio_set)

/* errno_t ioprio_get(syscall_ulong_t which, syscall_ulong_t who) */
.section .text.x86.asm32_syscall_sysenter.ioprio_get
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ioprio_get)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x122
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ioprio_get)
	call   sys_ioprio_get
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ioprio_get)

/* errno_t inotify_init(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.inotify_init
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_inotify_init)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x123
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_inotify_init)
	call   sys_inotify_init
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_inotify_init)

/* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.inotify_add_watch
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_inotify_add_watch)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x124
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_inotify_add_watch)
	call   sys_inotify_add_watch
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_inotify_add_watch)

/* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.inotify_rm_watch
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_inotify_rm_watch)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x125
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_inotify_rm_watch)
	call   sys_inotify_rm_watch
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_inotify_rm_watch)

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.migrate_pages
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_migrate_pages)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x126
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_migrate_pages)
	call   sys_migrate_pages
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_migrate_pages)

/* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.openat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_openat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x127
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_openat)
	call   sys_openat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_openat)

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.mkdirat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mkdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x128
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mkdirat)
	call   sys_mkdirat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mkdirat)

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
.section .text.x86.asm32_syscall_sysenter.mknodat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mknodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x129
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mknodat)
	call   sys_mknodat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.fchownat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchownat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x12a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchownat)
	call   sys_fchownat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fchownat)

/* errno_t futimesat(fd_t dirfd, const char *filename, struct __timevalx32 const[2] times) */
.section .text.x86.asm32_syscall_sysenter.futimesat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_futimesat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x12b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_futimesat)
	call   sys_futimesat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_futimesat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t linux_fstatat64(fd_t dirfd, char const *filename, struct linux_stat64 *statbuf, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.linux_fstatat64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_fstatat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x12c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linux_fstatat64)
	call   sys_linux_fstatat64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_linux_fstatat64)

/* @param: flags: Set of `0 | AT_REMOVEDIR|AT_REMOVEREG | AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.unlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_unlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x12d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_unlinkat)
	call   sys_unlinkat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_unlinkat)

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
.section .text.x86.asm32_syscall_sysenter.renameat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_renameat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x12e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_renameat)
	call   sys_renameat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_renameat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.linkat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x12f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_linkat)
	call   sys_linkat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_linkat)

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
.section .text.x86.asm32_syscall_sysenter.symlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_symlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x130
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_symlinkat)
	call   sys_symlinkat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_symlinkat)

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
.section .text.x86.asm32_syscall_sysenter.readlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x131
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readlinkat)
	call   sys_readlinkat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_readlinkat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.fchmodat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchmodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x132
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchmodat)
	call   sys_fchmodat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fchmodat)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_EACCESS | AT_DOSPATH' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.faccessat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_faccessat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x133
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_faccessat)
	call   sys_faccessat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_faccessat)

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespecx32 const *timeout, void const *sigmask_sigset_and_len) */
.section .text.x86.asm32_syscall_sysenter.pselect6
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pselect6)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x134
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pselect6)
	call   sys_pselect6
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_pselect6)

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct __timespecx32 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.ppoll
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ppoll)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x135
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ppoll)
	call   sys_ppoll
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ppoll)

/* param flags: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.unshare
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_unshare)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x136
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_unshare)
	call   sys_unshare
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_unshare)

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.set_robust_list
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_set_robust_list)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x137
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_set_robust_list)
	call   sys_set_robust_list
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_set_robust_list)

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.get_robust_list
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_get_robust_list)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x138
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_get_robust_list)
	call   sys_get_robust_list
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_get_robust_list)

/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.splice
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_splice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x139
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_splice)
	call   sys_splice
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_splice)

/* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.sync_file_range
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sync_file_range)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x13a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sync_file_range)
	call   sys_sync_file_range
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sync_file_range)

/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.tee
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_tee)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x13b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_tee)
	call   sys_tee
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_tee)

/* ssize_t vmsplice(fd_t fdout, struct iovec32 const *iov, size_t count, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.vmsplice
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_vmsplice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x13c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_vmsplice)
	call   sys_vmsplice
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_vmsplice)

/* errno_t move_pages(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.move_pages
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_move_pages)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x13d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_move_pages)
	call   sys_move_pages
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_move_pages)

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
.section .text.x86.asm32_syscall_sysenter.getcpu
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getcpu)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x13e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getcpu)
	call   sys_getcpu
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getcpu)

/* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
.section .text.x86.asm32_syscall_sysenter.epoll_pwait
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_epoll_pwait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x13f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_epoll_pwait)
	call   sys_epoll_pwait
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_epoll_pwait)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct __timespecx32 const[2] times, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.utimensat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_utimensat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x140
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_utimensat)
	call   sys_utimensat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_utimensat)

/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.signalfd
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_signalfd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x141
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_signalfd)
	call   sys_signalfd
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_signalfd)

/* Return file descriptor for new interval timer source */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.timerfd_create
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timerfd_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x142
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timerfd_create)
	call   sys_timerfd_create
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_timerfd_create)

/* fd_t eventfd(syscall_ulong_t initval) */
.section .text.x86.asm32_syscall_sysenter.eventfd
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_eventfd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x143
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_eventfd)
	call   sys_eventfd
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_eventfd)

/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
.section .text.x86.asm32_syscall_sysenter.fallocate
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fallocate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x144
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fallocate)
	call   sys_fallocate
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fallocate)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
/* errno_t timerfd_settime(fd_t ufd, syscall_ulong_t flags, struct __itimerspecx32 const *utmr, struct __itimerspecx32 *otmr) */
.section .text.x86.asm32_syscall_sysenter.timerfd_settime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timerfd_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x145
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timerfd_settime)
	call   sys_timerfd_settime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_timerfd_settime)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t ufd, struct __itimerspecx32 *otmr) */
.section .text.x86.asm32_syscall_sysenter.timerfd_gettime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timerfd_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x146
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timerfd_gettime)
	call   sys_timerfd_gettime
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_timerfd_gettime)

/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.signalfd4
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_signalfd4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x147
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_signalfd4)
	call   sys_signalfd4
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_signalfd4)

/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.eventfd2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_eventfd2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x148
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_eventfd2)
	call   sys_eventfd2
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_eventfd2)

/* fd_t epoll_create1(syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.epoll_create1
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_epoll_create1)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x149
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_epoll_create1)
	call   sys_epoll_create1
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_epoll_create1)

/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.dup3
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_dup3)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x14a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_dup3)
	call   sys_dup3
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_dup3)

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.pipe2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pipe2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x14b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pipe2)
	call   sys_pipe2
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_pipe2)

/* errno_t inotify_init1(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.inotify_init1
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_inotify_init1)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x14c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_inotify_init1)
	call   sys_inotify_init1
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_inotify_init1)

/* ssize_t preadv(fd_t fd, struct iovec32 const *iovec, size_t count, uint64_t offset) */
.section .text.x86.asm32_syscall_sysenter.preadv
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_preadv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x14d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_preadv)
	call   sys_preadv
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_preadv)

/* ssize_t pwritev(fd_t fd, struct iovec32 const *iovec, size_t count, uint64_t offset) */
.section .text.x86.asm32_syscall_sysenter.pwritev
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pwritev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x14e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pwritev)
	call   sys_pwritev
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_pwritev)

/* @param: signo: One of `SIG*' */
/* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, syscall_ulong_t signo, struct __siginfo32_struct const *uinfo) */
.section .text.x86.asm32_syscall_sysenter.rt_tgsigqueueinfo
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_tgsigqueueinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x14f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_tgsigqueueinfo)
	call   sys_rt_tgsigqueueinfo
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_rt_tgsigqueueinfo)

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.perf_event_open
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_perf_event_open)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x150
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_perf_event_open)
	call   sys_perf_event_open
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_perf_event_open)

/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespecx32 *tmo) */
.section .text.x86.asm32_syscall_sysenter.recvmmsg
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_recvmmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x151
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_recvmmsg)
	call   sys_recvmmsg
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_recvmmsg)

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.fanotify_init
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fanotify_init)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x152
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fanotify_init)
	call   sys_fanotify_init
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fanotify_init)

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.fanotify_mark
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fanotify_mark)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x153
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fanotify_mark)
	call   sys_fanotify_mark
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fanotify_mark)

/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
.section .text.x86.asm32_syscall_sysenter.prlimit64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_prlimit64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x154
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_prlimit64)
	call   sys_prlimit64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_prlimit64)

/* errno_t name_to_handle_at(fd_t dirfd, char const *name, struct file_handle *handle, int32_t *mnt_id, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.name_to_handle_at
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_name_to_handle_at)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x155
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_name_to_handle_at)
	call   sys_name_to_handle_at
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_name_to_handle_at)

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle *handle, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.open_by_handle_at
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_open_by_handle_at)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x156
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_open_by_handle_at)
	call   sys_open_by_handle_at
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_open_by_handle_at)

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.clock_adjtime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_adjtime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x157
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_adjtime)
	call   sys_clock_adjtime
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_clock_adjtime)

/* errno_t syncfs(fd_t fd) */
.section .text.x86.asm32_syscall_sysenter.syncfs
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_syncfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x158
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_syncfs)
	call   sys_syncfs
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_syncfs)

/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.sendmmsg
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sendmmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x159
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sendmmsg)
	call   sys_sendmmsg
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sendmmsg)

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
.section .text.x86.asm32_syscall_sysenter.setns
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setns)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x15a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setns)
	call   sys_setns
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setns)

/* ssize_t process_vm_readv(pid_t pid, struct iovec32 const *lvec, size_t liovcnt, struct iovec32 const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.process_vm_readv
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_process_vm_readv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x15b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_process_vm_readv)
	call   sys_process_vm_readv
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_process_vm_readv)

/* ssize_t process_vm_writev(pid_t pid, struct iovec32 const *lvec, size_t liovcnt, struct iovec32 const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.process_vm_writev
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_process_vm_writev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x15c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_process_vm_writev)
	call   sys_process_vm_writev
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_process_vm_writev)

/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
.section .text.x86.asm32_syscall_sysenter.kcmp
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kcmp)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x15d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kcmp)
	call   sys_kcmp
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_kcmp)

/* errno_t finit_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.finit_module
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_finit_module)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x15e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_finit_module)
	call   sys_finit_module
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_finit_module)

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.sched_setattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_setattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x15f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_setattr)
	call   sys_sched_setattr
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sched_setattr)

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.sched_getattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_getattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x160
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_getattr)
	call   sys_sched_getattr
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sched_getattr)

/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.renameat2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_renameat2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x161
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_renameat2)
	call   sys_renameat2
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_renameat2)

/* errno_t seccomp(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.seccomp
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_seccomp)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x162
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_seccomp)
	call   sys_seccomp
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_seccomp)

/* errno_t getrandom(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.getrandom
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getrandom)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x163
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getrandom)
	call   sys_getrandom
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getrandom)

/* errno_t memfd_create(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.memfd_create
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_memfd_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x164
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_memfd_create)
	call   sys_memfd_create
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_memfd_create)

/* errno_t bpf(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.bpf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_bpf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x165
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_bpf)
	call   sys_bpf
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_bpf)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.execveat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_execveat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x166
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_execveat)
	call   sys_execveat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_execveat)

/* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
.section .text.x86.asm32_syscall_sysenter.socket
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_socket)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x167
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_socket)
	call   sys_socket
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_socket)

/* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
.section .text.x86.asm32_syscall_sysenter.socketpair
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_socketpair)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x168
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_socketpair)
	call   sys_socketpair
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_socketpair)

/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm32_syscall_sysenter.bind
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_bind)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x169
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_bind)
	call   sys_bind
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_bind)

/* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm32_syscall_sysenter.connect
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_connect)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x16a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_connect)
	call   sys_connect
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_connect)

/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
.section .text.x86.asm32_syscall_sysenter.listen
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_listen)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x16b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_listen)
	call   sys_listen
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_listen)

/* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.accept4
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_accept4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x16c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_accept4)
	call   sys_accept4
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_accept4)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
.section .text.x86.asm32_syscall_sysenter.getsockopt
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getsockopt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x16d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getsockopt)
	call   sys_getsockopt
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getsockopt)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
.section .text.x86.asm32_syscall_sysenter.setsockopt
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setsockopt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x16e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setsockopt)
	call   sys_setsockopt
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setsockopt)

/* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm32_syscall_sysenter.getsockname
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getsockname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x16f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getsockname)
	call   sys_getsockname
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getsockname)

/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm32_syscall_sysenter.getpeername
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getpeername)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x170
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getpeername)
	call   sys_getpeername
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getpeername)

/* param flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
/* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm32_syscall_sysenter.sendto
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sendto)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x171
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sendto)
	call   sys_sendto
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sendto)

/* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.sendmsg
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sendmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x172
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sendmsg)
	call   sys_sendmsg
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sendmsg)

/* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm32_syscall_sysenter.recvfrom
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_recvfrom)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x173
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_recvfrom)
	call   sys_recvfrom
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_recvfrom)

/* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.recvmsg
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_recvmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x174
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_recvmsg)
	call   sys_recvmsg
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_recvmsg)

/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
.section .text.x86.asm32_syscall_sysenter.shutdown
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_shutdown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x175
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_shutdown)
	call   sys_shutdown
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_shutdown)

/* errno_t userfaultfd(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.userfaultfd
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_userfaultfd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x176
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_userfaultfd)
	call   sys_userfaultfd
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_userfaultfd)

/* errno_t membarrier(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.membarrier
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_membarrier)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x177
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_membarrier)
	call   sys_membarrier
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_membarrier)

/* errno_t mlock2(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.mlock2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mlock2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x178
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mlock2)
	call   sys_mlock2
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mlock2)

/* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.x86.asm32_syscall_sysenter.hop
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_hop)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000001
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_hop)
	call   sys_hop
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_hop)

/* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.x86.asm32_syscall_sysenter.hopf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_hopf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000002
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_hopf)
	call   sys_hopf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_hopf)

/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.readf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000003
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readf)
	call   sys_readf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_readf)

/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.writef
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_writef)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000004
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_writef)
	call   sys_writef
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_writef)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the thread from turning into a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling thread from the set of running children within
 *     its own process. Note however that when this is done by the main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the calling process the same way a double-fork would:
 *     >> if (fork() == 0) {
 *     >> 	if (fork() == 0) {
 *     >> 		// This is a daemonized process
 *     >> 		// aka. the parent process no longer knows
 *     >> 		// about us, and also can't wait(2) on us.
 *     >> 		...
 *     >> 	}
 *     >> 	exit(0);
 *     >> }
 *     Same as:
 *     >> if (fork() == 0) {
 *     >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
 *     >> 	// This is a daemonized process
 *     >> 	// aka. the parent process no longer knows
 *     >> 	// about us, and also can't wait(2) on us.
 *     >> 	...
 *     >> }
 *   - PID == -1:
 *     Detach all child processes/threads of the calling process, essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * Before any of this is done, the thread referred to by `PID' is one of the following:
 *   - The leader of the process that called `fork()' or `clone()' without
 *    `CLONE_PARENT' to create the thread referred to by `PID'
 *   - The creator of the process containing a thread that called
 *    `clone()' with `CLONE_PARENT', which then created the thread
 *     referred to by `PID'.
 *   - Even if the thread doesn't deliver a signal upon it terminating,
 *     the process that would have received such a signal is still relevant.
 *   -> In other words: The thread `PID' must be one of your children,
 *                      or you had to have been assigned as its child.
 * If the calling thread isn't part of that process that will receive
 * the signal if the thread dies without being detached first, then
 * the call fails by throwing an `E_ILLEGAL_OPERATION'.
 * If the thread had already been detached, then the call fails by
 * throwing an `E_ILLEGAL_OPERATION' as well.
 * Upon success, the thread referred to by `PID' will clean up its own
 * PID descriptor without the need of anyone to wait() for it, a behavior
 * that linux implements using `CLONE_THREAD' (which you shouldn't use,
 * because it's flawed by design)
 * Once detached, any further use of PID results in a race condition
 * (which linux neglects to mention for `CLONE_THREAD'), because there
 * is no way of ensuring that PID still refers to the original thread,
 * as another thread may have been created using the same PID, after
 * the detached thread exited.
 * NOTE: If a thread is crated using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had already
 *       be called.
 * NOTE: If the thread already has terminated, detaching it will kill
 *       its zombie the same way wait() would.
 * NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
 *       However, this operation fails if the calling thread isn't
 *       part of the same process as the parent process of the thread.
 *       In other words, the child of a fork() can't do this, and
 *       neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
 *       clone(0) or clone(CLONE_PARENT).
 * @return: -EPERM:             The calling process isn't the recipient of signals
 *                              delivered when `PID' changes state. This can either
 *                              be because `PID' has already been detached, or because
 *                              YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
 *                              Another possibility is that the thread was already
 *                              detached, then exited, following which a new thread
 *                              got created and had been assigned the PID of your
 *                              ancient, no longer existent thread.
 * @return: -ECHILD:           `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
 *                              This could mean that it had already been detached
 *                              and exited, or that the `PID' is just invalid (which
 *                              would also be the case if it was valid at some point) */
/* errno_t detach(pid_t pid) */
.section .text.x86.asm32_syscall_sysenter.detach
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_detach)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000005
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_detach)
	call   sys_detach
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_detach)

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
.section .text.x86.asm32_syscall_sysenter.getdrives
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getdrives)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000006
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_getdrives)
	call   sys_getdrives
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getdrives)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.frealpath4
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_frealpath4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000007
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_frealpath4)
	call   sys_frealpath4
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_frealpath4)

/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.frealpathat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_frealpathat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000008
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_frealpathat)
	call   sys_frealpathat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_frealpathat)

/* Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
/* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, __HYBRID_PTR32(void) *arguments) */
.section .text.x86.asm32_syscall_sysenter.rpc_schedule
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rpc_schedule)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000009
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rpc_schedule)
	call   sys_rpc_schedule
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_rpc_schedule)

/* syscall_slong_t ksysctl(syscall_ulong_t command, void *arg) */
.section .text.x86.asm32_syscall_sysenter.ksysctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ksysctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000000a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ksysctl)
	call   sys_ksysctl
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ksysctl)

/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
.section .text.x86.asm32_syscall_sysenter.openpty
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_openpty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000000b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_openpty)
	call   sys_openpty
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_openpty)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.fchdirat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000000c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fchdirat)
	call   sys_fchdirat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fchdirat)

/* int64_t time64(int64_t *timer) */
.section .text.x86.asm32_syscall_sysenter.time64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_time64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000000d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_time64)
	call   sys_time64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_sysenter_time64)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
/* errno_t set_exception_handler(syscall_ulong_t mode, __except_handler32_t handler, void *handler_sp) */
.section .text.x86.asm32_syscall_sysenter.set_exception_handler
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_set_exception_handler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000000e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_set_exception_handler)
	call   sys_set_exception_handler
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_set_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
/* errno_t get_exception_handler(__ULONG32_TYPE__ *pmode, __except_handler32_t *phandler, __HYBRID_PTR32(void) *phandler_sp) */
.section .text.x86.asm32_syscall_sysenter.get_exception_handler
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_get_exception_handler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000000f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_get_exception_handler)
	call   sys_get_exception_handler
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_get_exception_handler)

/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
/* errno_t set_library_listdef(struct library_listdef32 const *listdef) */
.section .text.x86.asm32_syscall_sysenter.set_library_listdef
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_set_library_listdef)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000010
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_set_library_listdef)
	call   sys_set_library_listdef
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_set_library_listdef)

/* Trigger a debugger trap `trapno', optionally extended with `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to the
 * given `state', though given the purpose of this system call being
 * to inform a connected debugger of some breakable event, allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
/* errno_t debugtrap(struct ucpustate32 const *state, struct debugtrap_reason32 const *reason) */
.section .text.x86.asm32_syscall_sysenter.debugtrap
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_debugtrap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000011
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_debugtrap)
	call   sys_debugtrap
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_debugtrap)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKEMASK, size_t val = count, struct timespec64 const *timeout = mask_and, uintptr_t val2 = mask_or)
 *    - LFUTEX_NOP:                (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_NOP)
 *    - LFUTEX_WAIT:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT, uintptr_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_LOCK, uintptr_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_ABOVE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BELOW, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
/* syscall_slong_t lfutex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct __timespecx32_64 const *timeout, uint32_t val2) */
.section .text.x86.asm32_syscall_sysenter.lfutex
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lfutex)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000012
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lfutex)
	call   sys_lfutex
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_lfutex)

/* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
.section .text.x86.asm32_syscall_sysenter.lseek64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lseek64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000013
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lseek64)
	call   sys_lseek64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_sysenter_lseek64)

/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexexpr(void *base, size_t exprc, struct lfutexexpr32 const *exprv, struct __timespecx32_64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.x86.asm32_syscall_sysenter.lfutexexpr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lfutexexpr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000014
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lfutexexpr)
	call   sys_lfutexexpr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_lfutexexpr)

/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexlockexpr(uint32_t *ulockaddr, void *base, size_t exprc, struct lfutexexpr32 const *exprv, struct __timespecx32_64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.x86.asm32_syscall_sysenter.lfutexlockexpr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lfutexlockexpr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000015
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_lfutexlockexpr)
	call   sys_lfutexlockexpr
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_lfutexlockexpr)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(fd_t keyboard, fd_t display, char const *name, syscall_ulong_t rsvd) */
.section .text.x86.asm32_syscall_sysenter.mktty
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mktty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000016
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mktty)
	call   sys_mktty
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mktty)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
/* errno_t raiseat(struct ucpustate32 const *state, struct __siginfo32_struct const *si) */
.section .text.x86.asm32_syscall_sysenter.raiseat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_raiseat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000017
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_raiseat)
	call   sys_raiseat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_raiseat)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `exception' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When `curr_state' is also `NULL', then the current CPU state is used instead.
 * @param: traceback_vector: (potentially incomplete) vector of additional program pointers that were
 *                           travered when the stack was walked from `orig_state' to `curr_state'
 *                           Note that earlier entires within this vector are further up the call-stack, with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it can be assumed that the traceback is complete and contains all travered instruction locations.
 *                           In this case, a traceback displayed to a human should not include the text location at
 *                           `traceback_vector[traceback_length-1]', since that location would also be printed when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: exception:        The exception that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           Note that when `unwind_error == UNWIND_SUCCESS', this argument is interpreted as `siginfo_t *',
 *                           allowing coredumps to also be triggerred for unhandled signals.
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_NOTHROW' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
/* errno_t coredump(struct ucpustate32 const *curr_state, struct ucpustate32 const *orig_state, __HYBRID_PTR32(void) const *traceback_vector, size_t traceback_length, struct exception_data32 const *exception, syscall_ulong_t unwind_error) */
.section .text.x86.asm32_syscall_sysenter.coredump
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_coredump)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000018
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_coredump)
	call   sys_coredump
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_coredump)

/* errno_t stime64(time64_t const *t) */
.section .text.x86.asm32_syscall_sysenter.stime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_stime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000019
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_stime64)
	call   sys_stime64
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_stime64)

/* errno_t utime64(char const *filename, struct __utimbuf64 const *times) */
.section .text.x86.asm32_syscall_sysenter.utime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_utime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000001e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_utime64)
	call   sys_utime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_utime64)

/* errno_t ftime64(struct __timebx32_64 *tp) */
.section .text.x86.asm32_syscall_sysenter.ftime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ftime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000023
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ftime64)
	call   sys_ftime64
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ftime64)

/* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.x86.asm32_syscall_sysenter.ioctlf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ioctlf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000036
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ioctlf)
	call   sys_ioctlf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ioctlf)

/* uint64_t fsmode(uint64_t mode) */
.section .text.x86.asm32_syscall_sysenter.fsmode
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fsmode)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000003c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fsmode)
	call   sys_fsmode
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(__x86_asm32_sysenter_fsmode)

/* errno_t getrusage64(syscall_slong_t who, struct __rusagex32_64 *tv) */
.section .text.x86.asm32_syscall_sysenter.getrusage64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getrusage64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000004d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getrusage64)
	call   sys_getrusage64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getrusage64)

/* errno_t gettimeofday64(struct __timevalx32_64 *tv, struct timezone *tz) */
.section .text.x86.asm32_syscall_sysenter.gettimeofday64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_gettimeofday64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000004e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_gettimeofday64)
	call   sys_gettimeofday64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_gettimeofday64)

/* errno_t settimeofday64(struct __timevalx32_64 const *tv, struct timezone const *tz) */
.section .text.x86.asm32_syscall_sysenter.settimeofday64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_settimeofday64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000004f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_settimeofday64)
	call   sys_settimeofday64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_settimeofday64)

/* ssize_t select64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timevalx32_64 *timeout) */
.section .text.x86.asm32_syscall_sysenter.select64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_select64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000052
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_select64)
	call   sys_select64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_select64)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|
 *                       MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP|
 *                       MAP_DONT_OVERRIDE'
 * @param: fd:    A handle for the library file being mapped
 *                (must be a file or vm_datablock/inode)
 * @param: hdrv:  Pointer to a vector of `Elf32_Phdr' or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
/* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, void *hdrv, size_t hdrc) */
.section .text.x86.asm32_syscall_sysenter.maplibrary
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_maplibrary)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000056
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_maplibrary)
	call   sys_maplibrary
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_maplibrary)

/* errno_t setitimer64(syscall_ulong_t which, struct __itimerval64 const *newval, struct __itimerval64 *oldval) */
.section .text.x86.asm32_syscall_sysenter.setitimer64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setitimer64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000068
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_setitimer64)
	call   sys_setitimer64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_setitimer64)

/* errno_t getitimer64(syscall_ulong_t which, struct __itimerval64 *curr_value) */
.section .text.x86.asm32_syscall_sysenter.getitimer64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getitimer64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000069
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_getitimer64)
	call   sys_getitimer64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_getitimer64)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4_64(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct __rusagex32_64 *usage) */
.section .text.x86.asm32_syscall_sysenter.wait4_64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_wait4_64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000072
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_wait4_64)
	call   sys_wait4_64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_wait4_64)

/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
.section .text.x86.asm32_syscall_sysenter.kreaddir
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kreaddir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000008d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kreaddir)
	call   sys_kreaddir
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_kreaddir)

/* ssize_t readvf(fd_t fd, struct iovec32 const *iovec, size_t count, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.readvf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readvf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000091
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_readvf)
	call   sys_readvf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_readvf)

/* ssize_t writevf(fd_t fd, struct iovec32 const *iovec, size_t count, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.writevf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_writevf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000092
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_writevf)
	call   sys_writevf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_writevf)

/* syscall_slong_t rpc_service(void) */
.section .text.x86.asm32_syscall_sysenter.rpc_service
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rpc_service)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000009e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	EXTERN(sys_rpc_service)
	call   sys_rpc_service
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_rpc_service)

/* errno_t sched_rr_get_interval64(pid_t pid, struct __timespecx32_64 *tms) */
.section .text.x86.asm32_syscall_sysenter.sched_rr_get_interval64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_rr_get_interval64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x800000a1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_sched_rr_get_interval64)
	call   sys_sched_rr_get_interval64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_sched_rr_get_interval64)

/* errno_t nanosleep64(struct __timespecx32_64 const *req, struct __timespecx32_64 *rem) */
.section .text.x86.asm32_syscall_sysenter.nanosleep64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_nanosleep64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x800000a2
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_nanosleep64)
	call   sys_nanosleep64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_nanosleep64)

/* syscall_slong_t rt_sigtimedwait64(struct __sigset_struct const *set, struct __siginfo32_struct *info, struct __timespecx32_64 const *timeout, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.rt_sigtimedwait64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigtimedwait64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x800000b1
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_rt_sigtimedwait64)
	call   sys_rt_sigtimedwait64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_rt_sigtimedwait64)

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.pread64f
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pread64f)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x800000b4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pread64f)
	call   sys_pread64f
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_pread64f)

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.pwrite64f
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pwrite64f)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x800000b5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pwrite64f)
	call   sys_pwrite64f
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_pwrite64f)

/* errno_t kstat(char const *filename, struct stat *statbuf) */
.section .text.x86.asm32_syscall_sysenter.kstat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x800000c3
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kstat)
	call   sys_kstat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_kstat)

/* errno_t klstat(char const *filename, struct stat *statbuf) */
.section .text.x86.asm32_syscall_sysenter.klstat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_klstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x800000c4
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_klstat)
	call   sys_klstat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_klstat)

/* errno_t kfstat(fd_t fd, struct stat *statbuf) */
.section .text.x86.asm32_syscall_sysenter.kfstat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kfstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x800000c5
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kfstat)
	call   sys_kfstat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_kfstat)

/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
.section .text.x86.asm32_syscall_sysenter.kreaddirf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kreaddirf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x800000dc
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kreaddirf)
	call   sys_kreaddirf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_kreaddirf)

/* errno_t timer_settime64(timer_t timerid, syscall_ulong_t flags, struct __itimerspecx32_64 const *value, struct __itimerspecx32_64 *ovalue) */
.section .text.x86.asm32_syscall_sysenter.timer_settime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_settime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000104
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_settime64)
	call   sys_timer_settime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_timer_settime64)

/* errno_t timer_gettime64(timer_t timerid, struct __itimerspecx32_64 *value) */
.section .text.x86.asm32_syscall_sysenter.timer_gettime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_gettime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000105
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timer_gettime64)
	call   sys_timer_gettime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_timer_gettime64)

/* errno_t clock_settime64(clockid_t clock_id, struct __timespecx32_64 const *tp) */
.section .text.x86.asm32_syscall_sysenter.clock_settime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_settime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000108
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_settime64)
	call   sys_clock_settime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_clock_settime64)

/* errno_t clock_gettime64(clockid_t clock_id, struct __timespecx32_64 *tp) */
.section .text.x86.asm32_syscall_sysenter.clock_gettime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_gettime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000109
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_gettime64)
	call   sys_clock_gettime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_clock_gettime64)

/* errno_t clock_getres64(clockid_t clock_id, struct __timespecx32_64 *res) */
.section .text.x86.asm32_syscall_sysenter.clock_getres64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_getres64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000010a
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_getres64)
	call   sys_clock_getres64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_clock_getres64)

/* errno_t clock_nanosleep64(clockid_t clock_id, syscall_ulong_t flags, struct __timespecx32_64 const *requested_time, struct __timespecx32_64 *remaining) */
.section .text.x86.asm32_syscall_sysenter.clock_nanosleep64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_nanosleep64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000010b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_clock_nanosleep64)
	call   sys_clock_nanosleep64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_clock_nanosleep64)

/* errno_t utimes64(char const *filename, struct __timevalx32_64 const[2] times) */
.section .text.x86.asm32_syscall_sysenter.utimes64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_utimes64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000010f
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_utimes64)
	call   sys_utimes64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_utimes64)

/* errno_t mq_timedsend64(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct __timespecx32_64 const *abs_timeout) */
.section .text.x86.asm32_syscall_sysenter.mq_timedsend64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_timedsend64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000117
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_timedsend64)
	call   sys_mq_timedsend64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mq_timedsend64)

/* ssize_t mq_timedreceive64(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct __timespecx32_64 const *abs_timeout) */
.section .text.x86.asm32_syscall_sysenter.mq_timedreceive64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_timedreceive64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000118
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_mq_timedreceive64)
	call   sys_mq_timedreceive64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_mq_timedreceive64)

/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid64(syscall_ulong_t idtype, id_t id, struct __siginfo32_struct *infop, syscall_ulong_t options, struct __rusagex32_64 *ru) */
.section .text.x86.asm32_syscall_sysenter.waitid64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_waitid64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000011c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_waitid64)
	call   sys_waitid64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_waitid64)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.fmkdirat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fmkdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000128
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fmkdirat)
	call   sys_fmkdirat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fmkdirat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.fmknodat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fmknodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000129
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fmknodat)
	call   sys_fmknodat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fmknodat)

/* errno_t futimesat64(fd_t dirfd, const char *filename, struct __timevalx32_64 const[2] times) */
.section .text.x86.asm32_syscall_sysenter.futimesat64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_futimesat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000012b
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_futimesat64)
	call   sys_futimesat64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_futimesat64)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct stat *statbuf, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.kfstatat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kfstatat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000012c
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_kfstatat)
	call   sys_kfstatat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_kfstatat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.frenameat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_frenameat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000012e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_frenameat)
	call   sys_frenameat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_frenameat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.fsymlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fsymlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000130
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fsymlinkat)
	call   sys_fsymlinkat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fsymlinkat)

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.freadlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_freadlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000131
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_freadlinkat)
	call   sys_freadlinkat
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_freadlinkat)

/* ssize_t pselect6_64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespecx32_64 const *timeout, void const *sigmask_sigset_and_len) */
.section .text.x86.asm32_syscall_sysenter.pselect6_64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pselect6_64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000134
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pselect6_64)
	call   sys_pselect6_64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_pselect6_64)

/* ssize_t ppoll64(struct pollfd *fds, size_t nfds, struct __timespecx32_64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.ppoll64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ppoll64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000135
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_ppoll64)
	call   sys_ppoll64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_ppoll64)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
/* errno_t utimensat64(fd_t dirfd, char const *filename, struct __timespecx32_64 const[2] times, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.utimensat64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_utimensat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000140
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_utimensat64)
	call   sys_utimensat64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_utimensat64)

/* errno_t fallocate64(fd_t fd, syscall_ulong_t mode, uint64_t offset, uint64_t length) */
.section .text.x86.asm32_syscall_sysenter.fallocate64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fallocate64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000144
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_fallocate64)
	call   sys_fallocate64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_fallocate64)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
/* errno_t timerfd_settime64(fd_t ufd, syscall_ulong_t flags, struct __itimerspecx32_64 const *utmr, struct __itimerspecx32_64 *otmr) */
.section .text.x86.asm32_syscall_sysenter.timerfd_settime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timerfd_settime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000145
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timerfd_settime64)
	call   sys_timerfd_settime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi_r %esi
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_timerfd_settime64)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime64(fd_t ufd, struct __itimerspecx32_64 *otmr) */
.section .text.x86.asm32_syscall_sysenter.timerfd_gettime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timerfd_gettime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000146
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	pushl_cfi_r %edx
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_timerfd_gettime64)
	call   sys_timerfd_gettime64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_timerfd_gettime64)

/* ssize_t preadvf(fd_t fd, struct iovec32 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.preadvf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_preadvf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000014d
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_preadvf)
	call   sys_preadvf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_preadvf)

/* ssize_t pwritevf(fd_t fd, struct iovec32 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.pwritevf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pwritevf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x8000014e
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   4(%ebp)  /* Arg #5 (WARNING: SEGFAULT!) */
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_pwritevf)
	call   sys_pwritevf
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(12), %esp
	.cfi_adjust_cfa_offset -12
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_pwritevf)

/* ssize_t recvmmsg64(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespecx32_64 *tmo) */
.section .text.x86.asm32_syscall_sysenter.recvmmsg64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_recvmmsg64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality_asm32_sysenter
	.cfi_lsda 0, 0x80000151
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	pushl_cfi %ds
	.cfi_restore_iret_ds_or_offset -4
	pushl_cfi %es
	.cfi_restore_iret_es_or_offset -8
	pushl_cfi %fs
	.cfi_restore_iret_fs_or_offset -12
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
	cmpl   $(KERNELSPACE_BASE), %ebp
	jae    __asm32_bad_sysenter_extension
	pushl_cfi   0(%ebp)  /* Arg #4 (WARNING: SEGFAULT!) */
	pushl_cfi_r %esi  /* Arg #3 */
	pushl_cfi_r %edx  /* Arg #2 */
	pushl_cfi_r %ecx  /* Arg #1 */
	pushl_cfi_r %ebx  /* Arg #0 */
	EXTERN(sys_recvmmsg64)
	call   sys_recvmmsg64
	popl_cfi_r %ebx
	popl_cfi_r %ecx
	popl_cfi_r %edx
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	X86_IRET_BUT_PREFER_SYSEXIT
	.cfi_endproc
END(__x86_asm32_sysenter_recvmmsg64)


#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_WRAPPERS32_S */
