/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_FD_READWRITE_C
#define GUARD_KERNEL_SRC_FD_READWRITE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/iovec.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>

#include <bits/os/iovec.h> /* struct iovec */
#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <errno.h>
#include <malloca.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/iovec.h>
#include <compat/kos/types.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

/************************************************************************/
/* lseek(), lseek64(), _llseek()                                        */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_LSEEK
DEFINE_SYSCALL3(syscall_slong_t, lseek,
                fd_t, fd, syscall_slong_t, offset,
                syscall_ulong_t, whence) {
	pos_t result;
	struct handle hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	result = handle_seek(hand, (off_t)offset, whence);
	return (syscall_slong_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_LSEEK */

#ifdef __ARCH_WANT_SYSCALL_LSEEK64
DEFINE_SYSCALL3(int64_t, lseek64,
                fd_t, fd, int64_t, offset,
                syscall_ulong_t, whence) {
	pos_t result;
	struct handle hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	result = handle_seek(hand, (off_t)offset, whence);
	return (int64_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_LSEEK64 */

#ifdef __ARCH_WANT_SYSCALL__LLSEEK
DEFINE_SYSCALL4(errno_t, _llseek, fd_t, fd, int64_t, offset,
                NCX UNCHECKED uint64_t *, result,
                syscall_ulong_t, whence) {
	uint64_t retpos;
	validate_writable(result, sizeof(*result));
	retpos  = (uint64_t)sys_lseek64(fd, offset, whence);
	*result = retpos;
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL__LLSEEK */

#ifdef __ARCH_WANT_COMPAT_SYSCALL__LLSEEK
DEFINE_COMPAT_SYSCALL4(errno_t, _llseek,
                       fd_t, fd, int64_t, offset,
                       NCX UNCHECKED uint64_t *, result,
                       syscall_ulong_t, whence) {
	uint64_t retpos;
	compat_validate_writable(result, sizeof(*result));
#ifdef __ARCH_WANT_SYSCALL_LSEEK64
	retpos  = (uint64_t)sys_lseek64(fd, offset, whence);
#else /* __ARCH_WANT_SYSCALL_LSEEK64 */
	retpos  = (uint64_t)sys_lseek(fd, offset, whence);
#endif /* !__ARCH_WANT_SYSCALL_LSEEK64 */
	*result = retpos;
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL__LLSEEK */





/************************************************************************/
/* read(), write(), readf(), writef()                                   */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_READ
DEFINE_SYSCALL3(ssize_t, read, fd_t, fd,
                NCX UNCHECKED void *, buf, size_t, bufsize) {
	size_t result;
	struct handle hand;
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	buf    = validate_writable(buf, bufsize);
	result = handle_read(hand, buf, bufsize);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_READ */

#ifdef __ARCH_WANT_SYSCALL_WRITE
DEFINE_SYSCALL3(ssize_t, write, fd_t, fd,
                NCX UNCHECKED void const *, buf, size_t, bufsize) {
	size_t result;
	struct handle hand;
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	buf    = validate_readable(buf, bufsize);
	result = handle_write(hand, buf, bufsize);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_WRITE */

#ifdef __ARCH_WANT_SYSCALL_READF
DEFINE_SYSCALL4(ssize_t, readf,
                fd_t, fd, NCX UNCHECKED void *, buf,
                size_t, bufsize, iomode_t, mode) {
	size_t result;
	struct handle hand;
	VALIDATE_FLAGSET(mode,
	                 IO_USERF_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_READF_MODE);
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	buf    = validate_writable(buf, bufsize);
	result = handle_readf(hand, buf, bufsize,
	                      (hand.h_mode & ~IO_USERF_MASK) | mode);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_READF */

#ifdef __ARCH_WANT_SYSCALL_WRITEF
DEFINE_SYSCALL4(ssize_t, writef,
                fd_t, fd, NCX UNCHECKED void const *, buf,
                size_t, bufsize, iomode_t, mode) {
	size_t result;
	struct handle hand;
	VALIDATE_FLAGSET(mode,
	                 IO_USERF_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_WRITEF_MODE);
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	buf    = validate_readable(buf, bufsize);
	result = handle_writef(hand, buf, bufsize,
	                       (hand.h_mode & ~IO_USERF_MASK) | mode);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_WRITEF */





/************************************************************************/
/* pread64(), pwrite64(), pread64f(), pwrite64f()                       */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_PREAD64
DEFINE_SYSCALL4(ssize_t, pread64, fd_t, fd,
                NCX UNCHECKED void *, buf,
                size_t, bufsize, uint64_t, offset) {
	size_t result;
	struct handle hand;
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	buf    = validate_writable(buf, bufsize);
	result = handle_pread(hand, buf, bufsize, (pos_t)offset);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PREAD64 */

#ifdef __ARCH_WANT_SYSCALL_PWRITE64
DEFINE_SYSCALL4(ssize_t, pwrite64, fd_t, fd,
                NCX UNCHECKED void const *, buf,
                size_t, bufsize, uint64_t, offset) {
	size_t result;
	struct handle hand;
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	buf    = validate_readable(buf, bufsize);
	result = handle_pwrite(hand, buf, bufsize, (pos_t)offset);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PWRITE64 */

#ifdef __ARCH_WANT_SYSCALL_PREAD64F
DEFINE_SYSCALL5(ssize_t, pread64f,
                fd_t, fd, NCX UNCHECKED void *, buf,
                size_t, bufsize, uint64_t, offset, iomode_t, mode) {
	size_t result;
	struct handle hand;
	VALIDATE_FLAGSET(mode,
	                 IO_USERF_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_PREADF_MODE);
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	buf    = validate_writable(buf, bufsize);
	result = handle_preadf(hand, buf, bufsize, (pos_t)offset,
	                       (hand.h_mode & ~IO_USERF_MASK) | mode);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PREAD64F */

#ifdef __ARCH_WANT_SYSCALL_PWRITE64F
DEFINE_SYSCALL5(ssize_t, pwrite64f,
                fd_t, fd, NCX UNCHECKED void const *, buf,
                size_t, bufsize, uint64_t, offset, iomode_t, mode) {
	size_t result;
	struct handle hand;
	VALIDATE_FLAGSET(mode,
	                 IO_USERF_MASK,
	                 E_INVALID_ARGUMENT_CONTEXT_PWRITEF_MODE);
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	buf    = validate_readable(buf, bufsize);
	result = handle_pwritef(hand, buf, bufsize, (pos_t)offset,
	                        (hand.h_mode & ~IO_USERF_MASK) | mode);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PWRITE64F */





/************************************************************************/
/* readv(), writev()                                                  */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_PREADV
DEFINE_SYSCALL3(ssize_t, readv, fd_t, fd,
                NCX UNCHECKED struct iovec const *, iov,
                size_t, count) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	validate_readablem(iov, count, sizeof(*iov));
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		/* TODO: IOV_MAX limit (currently defined as "-1"; that should probably change...) */
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (NCX UNCHECKED byte_t *)iov[i].iov_base;
			entries[i].ive_size = iov[i].iov_len;
			COMPILER_READ_BARRIER();
			validate_writable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the read */
		result = handle_readv(hand, &dst, num_bytes);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PREADV */

#ifdef __ARCH_WANT_SYSCALL_PWRITEV
DEFINE_SYSCALL3(ssize_t, writev, fd_t, fd,
                NCX UNCHECKED struct iovec const *, iov,
                size_t, count) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	validate_readablem(iov, count, sizeof(*iov));
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		/* TODO: IOV_MAX limit (currently defined as "-1"; that should probably change...) */
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (NCX UNCHECKED byte_t *)iov[i].iov_base;
			entries[i].ive_size = iov[i].iov_len;
			COMPILER_READ_BARRIER();
			validate_readable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the write */
		result = handle_writev(hand, &dst, num_bytes);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PWRITEV */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PREADV
DEFINE_COMPAT_SYSCALL3(ssize_t, readv, fd_t, fd,
                       NCX UNCHECKED struct compat_iovec const *, iov,
                       size_t, count) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	compat_validate_readablem(iov, count, sizeof(*iov));
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		/* TODO: IOV_MAX limit (currently defined as "-1"; that should probably change...) */
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (NCX UNCHECKED byte_t *)(void *)(uintptr_t)(*(compat_uintptr_t const *)&iov[i].iov_base);
			entries[i].ive_size = iov[i].iov_len;
			COMPILER_READ_BARRIER();
			compat_validate_writable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the read */
		result = handle_readv(hand, &dst, num_bytes);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PREADV */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PWRITEV
DEFINE_COMPAT_SYSCALL3(ssize_t, writev, fd_t, fd,
                       NCX UNCHECKED struct compat_iovec const *, iov,
                       size_t, count) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	compat_validate_readablem(iov, count, sizeof(*iov));
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		/* TODO: IOV_MAX limit (currently defined as "-1"; that should probably change...) */
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (NCX UNCHECKED byte_t *)(void *)(uintptr_t)(*(compat_uintptr_t *)&iov[i].iov_base);
			entries[i].ive_size = iov[i].iov_len;
			COMPILER_READ_BARRIER();
			compat_validate_readable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the write */
		result = handle_writev(hand, &dst, num_bytes);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PWRITEV */





/************************************************************************/
/* preadv(), pwritev()                                                  */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_PREADV
DEFINE_SYSCALL4(ssize_t, preadv, fd_t, fd,
                NCX UNCHECKED struct iovec const *, iov,
                size_t, count, uint64_t, offset) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	validate_readablem(iov, count, sizeof(*iov));
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		/* TODO: IOV_MAX limit (currently defined as "-1"; that should probably change...) */
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (NCX UNCHECKED byte_t *)iov[i].iov_base;
			entries[i].ive_size = iov[i].iov_len;
			COMPILER_READ_BARRIER();
			validate_writable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the read */
		result = handle_preadv(hand, &dst, num_bytes, (pos_t)offset);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PREADV */

#ifdef __ARCH_WANT_SYSCALL_PWRITEV
DEFINE_SYSCALL4(ssize_t, pwritev, fd_t, fd,
                NCX UNCHECKED struct iovec const *, iov,
                size_t, count, uint64_t, offset) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	validate_readablem(iov, count, sizeof(*iov));
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		/* TODO: IOV_MAX limit (currently defined as "-1"; that should probably change...) */
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (NCX UNCHECKED byte_t *)iov[i].iov_base;
			entries[i].ive_size = iov[i].iov_len;
			COMPILER_READ_BARRIER();
			validate_readable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the write */
		result = handle_pwritev(hand, &dst, num_bytes, (pos_t)offset);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PWRITEV */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PREADV
DEFINE_COMPAT_SYSCALL4(ssize_t, preadv, fd_t, fd,
                       NCX UNCHECKED struct compat_iovec const *, iov,
                       size_t, count, uint64_t, offset) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	compat_validate_readablem(iov, count, sizeof(*iov));
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANREAD(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_READ, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		/* TODO: IOV_MAX limit (currently defined as "-1"; that should probably change...) */
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (NCX UNCHECKED byte_t *)(void *)(uintptr_t)(*(compat_uintptr_t *)&iov[i].iov_base);
			entries[i].ive_size = iov[i].iov_len;
			COMPILER_READ_BARRIER();
			compat_validate_writable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the read */
		result = handle_preadv(hand, &dst, num_bytes, (pos_t)offset);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PREADV */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PWRITEV
DEFINE_COMPAT_SYSCALL4(ssize_t, pwritev, fd_t, fd,
                       NCX UNCHECKED struct compat_iovec const *, iov,
                       size_t, count, uint64_t, offset) {
	size_t result, num_bytes;
	struct handle hand;
	struct iov_buffer dst;
	compat_validate_readablem(iov, count, sizeof(*iov));
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	if unlikely(!IO_CANWRITE(hand.h_mode))
		THROW(E_INVALID_HANDLE_OPERATION, fd, E_INVALID_HANDLE_OPERATION_WRITE, hand.h_mode);
	if unlikely(!count) {
		result = 0;
	} else {
		size_t i;
		struct iov_entry *entries;
		/* TODO: IOV_MAX limit (currently defined as "-1"; that should probably change...) */
		entries = (struct iov_entry *)malloca(count, sizeof(struct iov_entry));
		RAII_FINALLY { freea(entries); };
		dst.iv_entc = count;
		dst.iv_entv = entries;
		for (i = 0, num_bytes = 0; i < count; ++i) {
			entries[i].ive_base = (NCX UNCHECKED byte_t *)(void *)(uintptr_t)(*(compat_uintptr_t const *)&iov[i].iov_base);
			entries[i].ive_size = iov[i].iov_len;
			COMPILER_READ_BARRIER();
			compat_validate_readable(entries[i].ive_base, entries[i].ive_size);
			num_bytes += entries[i].ive_size;
		}
		dst.iv_head = entries[0];
		dst.iv_last = entries[count - 1].ive_size;

		/* Do the write */
		result = handle_pwritev(hand, &dst, num_bytes, (pos_t)offset);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PWRITEV */


DECL_END

#endif /* !GUARD_KERNEL_SRC_FD_READWRITE_C */
