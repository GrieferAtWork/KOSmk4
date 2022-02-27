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
#ifndef GUARD_KERNEL_SRC_FD_SENDFILE_C
#define GUARD_KERNEL_SRC_FD_SENDFILE_C 1

#include <kernel/compiler.h>

#include <kernel/fs/filehandle.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/task.h>

#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/illop.h>

#include <alloca.h>
#include <stddef.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/types.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

#if (defined(__ARCH_WANT_SYSCALL_SENDFILE) ||   \
     defined(__ARCH_WANT_SYSCALL_SENDFILE64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SENDFILE))
PRIVATE size_t FCALL
sys_sendfile_impl(fd_t outfd, fd_t infd,
                  pos_t *pin_offset,
                  size_t num_bytes) {
	size_t result = 0;
	bool uses_stack;
	size_t bufsize = num_bytes;
	void *buffer;
	REF struct handle out, in;
	if (bufsize > 16 * 1024)
		bufsize = 16 * 1024; /* 16K */
	uses_stack = bufsize <= (get_stack_avail() / 2);

	/* Lookup handles and verify access permissions. */
	out = handles_lookup(outfd);
	RAII_FINALLY { decref(out); };
	if unlikely(!IO_CANWRITE(out.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, outfd, E_INVALID_HANDLE_OPERATION_WRITE, out.h_mode);
	in  = handles_lookup(infd);
	RAII_FINALLY { decref(in); };
	if unlikely(!IO_CANREAD(in.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, infd, E_INVALID_HANDLE_OPERATION_READ, in.h_mode);

	/* TODO: optimizations through use of write(out, mmap(in)) */
	/* TODO: optimizations for when `infd' is a `printnode',
	 *       though only use direct printing if `outfd' is a
	 *       terminal or something similarly capable of fast
	 *       writes. */

	/* Allocate I/O buffer. */
	buffer = uses_stack ? alloca(bufsize) : kmalloc(bufsize, GFP_NORMAL);
	RAII_FINALLY { if (!uses_stack) kfree(buffer); };

	if (pin_offset) {
		/* In  the presence of a user-provided file offset, we can always
		 * just dispatch via the standard pread() and pwrite() operators. */
		while (result < num_bytes) {
			size_t part;
			part = num_bytes - result;
			if (part > bufsize)
				part = bufsize;
			part = handle_pread(in, buffer, part, *pin_offset);
			if (!part)
				break;
			part = handle_write(out, buffer, part);
			if (!part)
				break;
			*pin_offset += part;
		}
	} else {
		switch (in.h_type) {

		case HANDLE_TYPE_FILEHANDLE: {
			pos_t offset;
			struct filehandle *infile;
			infile = (struct filehandle *)in.h_data;
			offset = (pos_t)atomic64_read(&infile->fh_offset);
			RAII_FINALLY {
				atomic64_write(&infile->fh_offset, (uint64_t)offset);
			};
			while (result < num_bytes) {
				size_t part;
				part = num_bytes - result;
				if (part > bufsize)
					part = bufsize;
				part = mfile_upread(infile->fh_file, buffer, part, offset, in.h_mode);
				if (!part)
					break;
				part = handle_write(out, buffer, part);
				if (!part)
					break;
				offset += part;
			}
		}	break;

		default:
			THROW(E_INVALID_OPERATION,
			      E_ILLEGAL_OPERATION_CONTEXT_SENDFILE_NO_FILE_POSITION,
			      infd, in.h_type);
			break;
		}
	}
	return result;
}
#endif /* sendfile... */


#ifdef __ARCH_WANT_SYSCALL_SENDFILE
DEFINE_SYSCALL4(ssize_t, sendfile, fd_t, outfd, fd_t, infd,
                USER UNCHECKED syscall_ulong_t *, pin_offset,
                size_t, num_bytes) {
	ssize_t result;
	pos_t offset;
	if (pin_offset == NULL)
		return (ssize_t)sys_sendfile_impl(outfd, infd, NULL, num_bytes);
	validate_readwrite(pin_offset, sizeof(*pin_offset));
	offset = (pos_t)*pin_offset;
#if __SIZEOF_SYSCALL_LONG_T__ < __SIZEOF_POS_T__
	{
		syscall_ulong_t maxio;
		maxio = ((syscall_ulong_t)-1) - offset;
		if unlikely(num_bytes > maxio) {
			num_bytes = maxio;
			if unlikely(!num_bytes)
				THROW(E_OVERFLOW);
		}
	}
#endif /* __SIZEOF_SYSCALL_LONG_T__ < __SIZEOF_POS_T__ */
	TRY {
		result = sys_sendfile_impl(outfd, infd, &offset, num_bytes);
	} EXCEPT {
		{
			NESTED_EXCEPTION;
			*pin_offset = (syscall_ulong_t)offset;
		}
		RETHROW();
	}
	*pin_offset = (syscall_ulong_t)offset;
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_SENDFILE */

#ifdef __ARCH_WANT_SYSCALL_SENDFILE64
DEFINE_SYSCALL4(ssize_t, sendfile64, fd_t, outfd, fd_t, infd,
                USER UNCHECKED uint64_t *, pin_offset,
                size_t, num_bytes) {
	ssize_t result;
	pos_t offset;
	if (pin_offset == NULL)
		return (ssize_t)sys_sendfile_impl(outfd, infd, NULL, num_bytes);
	validate_readwrite(pin_offset, sizeof(*pin_offset));
	offset      = (pos_t)*pin_offset;
	TRY {
		result = sys_sendfile_impl(outfd, infd, &offset, num_bytes);
	} EXCEPT {
		{
			NESTED_EXCEPTION;
			*pin_offset = (uint64_t)offset;
		}
		RETHROW();
	}
	*pin_offset = (uint64_t)offset;
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_SENDFILE64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SENDFILE
DEFINE_COMPAT_SYSCALL4(ssize_t, sendfile, fd_t, outfd, fd_t, infd,
                       USER UNCHECKED compat_syscall_ulong_t *, pin_offset,
                       size_t, num_bytes) {
	ssize_t result;
	pos_t offset;
	if (pin_offset == NULL)
		return (ssize_t)sys_sendfile_impl(outfd, infd, NULL, num_bytes);
	validate_readwrite(pin_offset, sizeof(*pin_offset));
	offset = (pos_t)*pin_offset;
#if __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T < __SIZEOF_POS_T__
	{
		compat_syscall_ulong_t maxio;
		maxio = ((compat_syscall_ulong_t)-1) - offset;
		if unlikely(num_bytes > maxio) {
			num_bytes = maxio;
			if unlikely(!num_bytes)
				THROW(E_OVERFLOW);
		}
	}
#endif /* __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T < __SIZEOF_POS_T__ */
	TRY {
		result = sys_sendfile_impl(outfd, infd, &offset, num_bytes);
	} EXCEPT {
		{
			NESTED_EXCEPTION;
			*pin_offset = (compat_syscall_ulong_t)offset;
		}
		RETHROW();
	}
	*pin_offset = (compat_syscall_ulong_t)offset;
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SENDFILE */

DECL_END

#endif /* !GUARD_KERNEL_SRC_FD_SENDFILE_C */
