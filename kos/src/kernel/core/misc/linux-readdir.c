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
#ifndef GUARD_KERNEL_CORE_MISC_LINUX_READDIR_C
#define GUARD_KERNEL_CORE_MISC_LINUX_READDIR_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/sig.h>

#include <hybrid/align.h>

#include <compat/config.h>
#include <kos/compat/linux-dirent.h>
#include <kos/compat/linux-dirent64.h>
#include <kos/compat/linux-olddirent.h>

#include <assert.h>
#include <atomic.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/compat/linux-dirent.h>
#include <compat/kos/compat/linux-olddirent.h>
#endif /* __ARCH_HAVE_COMPAT */

#undef WANT_LINUX_READDIR
#if (defined(__ARCH_WANT_SYSCALL_READDIR) ||        \
     defined(__ARCH_WANT_SYSCALL_GETDENTS) ||       \
     defined(__ARCH_WANT_SYSCALL_GETDENTS64) ||     \
     defined(__ARCH_WANT_COMPAT_SYSCALL_READDIR) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_GETDENTS))
#define WANT_LINUX_READDIR 1
#endif /* __ARCH_WANT_... */


#ifdef WANT_LINUX_READDIR
DECL_BEGIN

/* NOTE: In order to emulate linux's readdir() API, we have to make
 *       a compromise  as far  as thread-safety  and semantics  go:
 *
 * On KOS,  the  readdir()  operation (s.a.  `sys_kreaddir()')  is  dispatched
 * via  an  atomic handle  operation `h_readdir'  that does  all of  the usual
 * read+advance all on its own. (this callback also supports a PEEK operation)
 *
 * As such, it is up to the operator to decide when to actually advance the
 * read/write   pointer,   which  is   controlled  via   the  readdir-mode:
 *   - READDIR_DEFAULT:  Yield to next entry when `buf' was of sufficient size
 *   - READDIR_CONTINUE: Always yield to next entry
 *   - READDIR_PEEK:     Never yield to next entry
 *
 * The readdir() implementation from libc.so makes use of `READDIR_DEFAULT',
 * in  conjunction  with  `READDIR_MULTIPLE'  to  get  optimal  performance.
 *
 * However,  we run into a problem since  we can't let the per-handle backend
 * decide when to actually advance the read/write pointer, since only we know
 * when  the user-provided buffer actually has sufficient length to store any
 * additional directory entries.
 *
 * As such, the API emulated in this file isn't 100% thread-safe, in that multiple
 * threads reading from the same directory  stream might get duplicate entries  at
 * one point, but skip other entries at other points:
 *
 *  #1: Use `READDIR_PEEK' to read the next directory entry.
 *      If end-of-directory was  encountered, stop  reading.
 *
 *  #2: Convert the entry to the appropriate linux-format.
 *      If the user-provided buffer is too small, indicate
 *      this fact to the caller.
 *
 *  #3: Use `READDIR_CONTINUE' alongside an empty buffer to
 *      force the directory stream  to advance to the  next
 *      entry.
 *
 *  #4: Continue with step #1
 *
 * You should immediately realize that this scheme isn't thread-safe, since another
 * thread  may read some other entry from the directory between step #1 and #3, and
 * you would be right in this assessment.
 *
 * To (try to)  mitigate this problem  (since using multiple  threads to read  directory
 * entries isn't  actually  something  too far-fetched),  a  hash-vector  of  statically
 * allocated locks exists that is used alongside the internal address of the  associated
 * file-handle in order to acquire a (waitable) lock during every linux-emulated readdir
 * operation.
 * But note that this only guards against parallel calls to linux's readdir API. When
 * this  is also mixed with KOS's kreaddir API, you will once again run into the data
 * race described above.
 */



/*[[[config CONFIG_KERNEL_LINUX_READDIR_LOCKCNT! = 512
 * NOTE: The  readdir lock system is designed to  have as small of a memory
 *       footprint as possible. - It's not (even meant to be) designed  for
 *       performance. (since this whole file is only meant for binary linux
 *       compatibility)
 * ]]]*/
#ifndef CONFIG_KERNEL_LINUX_READDIR_LOCKCNT
#define CONFIG_KERNEL_LINUX_READDIR_LOCKCNT 512
#endif /* !CONFIG_KERNEL_LINUX_READDIR_LOCKCNT */
/*[[[end]]]*/

/* Bitset of linux readdir lock-bits. */
PRIVATE uintptr_t readdir_lockbits[CONFIG_KERNEL_LINUX_READDIR_LOCKCNT / BITSOF(uintptr_t)] = { 0, };

/* Signal broadcast whenever one of `readdir_lockbits' is cleared. */
PRIVATE struct sig readdir_locksig = SIG_INIT;

#define readdir_lockbits_word(i) ((i) / BITSOF(uintptr_t))
#define readdir_lockbits_mask(i) ((uintptr_t)1 << ((i) % BITSOF(uintptr_t)))

/* Return the lock-index for a given `h_data' pointer */
PRIVATE ATTR_CONST WUNUSED unsigned int
NOTHROW(KCALL readdir_lock_index)(void *h_data) {
	uintptr_t result;
	result = (uintptr_t)h_data;
#if __SIZEOF_POINTER__ > 4 && CONFIG_KERNEL_LINUX_READDIR_LOCKCNT <= UINT32_MAX
	result ^= result >> 32;
#endif /* __SIZEOF_POINTER__ > 4 && CONFIG_KERNEL_LINUX_READDIR_LOCKCNT <= UINT32_MAX */
#if CONFIG_KERNEL_LINUX_READDIR_LOCKCNT <= UINT16_MAX
	result ^= result >> 16;
#endif /* CONFIG_KERNEL_LINUX_READDIR_LOCKCNT <= UINT16_MAX */
#if CONFIG_KERNEL_LINUX_READDIR_LOCKCNT <= UINT8_MAX
	result ^= result >> 8;
#endif /* CONFIG_KERNEL_LINUX_READDIR_LOCKCNT <= UINT8_MAX */
#if IS_POWER_OF_TWO(CONFIG_KERNEL_LINUX_READDIR_LOCKCNT)
	return (unsigned int)result & (CONFIG_KERNEL_LINUX_READDIR_LOCKCNT - 1);
#else /* IS_POWER_OF_TWO(CONFIG_KERNEL_LINUX_READDIR_LOCKCNT) */
	return (unsigned int)result % CONFIG_KERNEL_LINUX_READDIR_LOCKCNT;
#endif /* !IS_POWER_OF_TWO(CONFIG_KERNEL_LINUX_READDIR_LOCKCNT) */
}

/* Acquire a readdir lock */
PRIVATE void KCALL
readdir_lock_acquire(void *h_data) {
	unsigned int index, word;
	uintptr_t mask;
	assert(!task_wasconnected());
	index = readdir_lock_index(h_data);
	word  = readdir_lockbits_word(index);
	mask  = readdir_lockbits_mask(index);

	/* NOTE: No need  to worry  about re-entrancy  for this  lock!
	 *       This lock is only acquired from the syscall  wrappers
	 *       in  this file, and  there is no  way that some kernel
	 *       callback further down the path of execution will call
	 *       back to one of these, mainly since directly  invoking
	 *       system  calls while already  in kernel isn't allowed.
	 *       (You  can only invoke syscalls _after_ having unwound
	 *       any preceding system call)
	 *
	 * -> The  only way one system call can invoke another system call,
	 *    is by sending an RPC to itself, and using `syscall_emulate()'
	 *    alongside the register state given to the RPC handler. And in
	 *    this scenario, the RPC  delivery mechanism will have  already
	 *    unwound our stack,  at which we'd  have already released  the
	 *    readdir lock, so no dead-lock is possible. */
	for (;;) {
		if ((atomic_fetchor(&readdir_lockbits[word], mask) & mask) == 0)
			break;
		task_connect(&readdir_locksig);
		if ((atomic_fetchor(&readdir_lockbits[word], mask) & mask) == 0) {
			task_disconnectall();
			break;
		}
		/* Wait for the lock bit to become available. */
		task_waitfor();
	}
}

/* Release a readdir lock */
PRIVATE NOBLOCK void
NOTHROW(KCALL readdir_lock_release)(void *h_data) {
	unsigned int index, word;
	uintptr_t mask;
	index = readdir_lock_index(h_data);
	word  = readdir_lockbits_word(index);
	mask  = readdir_lockbits_mask(index);
	atomic_and(&readdir_lockbits[word], ~mask);
}





struct readdir_buffer {
	REF struct handle rb_file;   /* [const] Descriptor for the file from which to read. */
	struct dirent    *rb_buf;    /* [1..rb_buflen][owned_if(!= rb_sbuf)] Intermediate buffer. */
	size_t            rb_buflen; /* Intermediate buffer length. */
	byte_t            rb_sbuf[offsetof(struct dirent, d_name) + 512]; /* Static, pre-allocated buffer. */
};

/* Initialize a given readdir buffer, and acquire the readdir lock. */
PRIVATE NONNULL((1)) void KCALL
readdir_buffer_init(struct readdir_buffer *__restrict self, fd_t fd) {
	/* Lookup the given file and set-up the initial, static buffer. */
	handles_lookup(fd, &self->rb_file);
	self->rb_buflen = sizeof(self->rb_sbuf);
	self->rb_buf    = (struct dirent *)self->rb_sbuf;
	/* Acquire the readdir lock for the file's backing object. */
	TRY {
		readdir_lock_acquire(self->rb_file.h_data);
	} EXCEPT {
		decref(self->rb_file);
		RETHROW();
	}
}

/* Finalize a given readdir buffer and release the readdir lock. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL readdir_buffer_fini)(struct readdir_buffer *__restrict self) {
	/* Release the readdir lock for the file's backing object. */
	readdir_lock_release(self->rb_file.h_data);

	/* Free a potentially dynamic-allocated intermediate buffer. */
	if (self->rb_buf != (struct dirent *)self->rb_sbuf)
		kfree(self->rb_buf);
	decref(self->rb_file);
}

#define FINALLY_readdir_buffer_fini(self) \
	struct _readdir_buffer_finally_fini PP_CAT2(__rbf_, __LINE__)(self)
struct _readdir_buffer_finally_fini {
private:
	struct readdir_buffer *m_self;
public:
	ATTR_FORCEINLINE _readdir_buffer_finally_fini(struct readdir_buffer *__restrict self) noexcept
	    : m_self(self) { }
	ATTR_FORCEINLINE ~_readdir_buffer_finally_fini() noexcept {
		readdir_buffer_fini(m_self);
	}
};


/* Try to peek the next  not-yet-consumed directory entry from  `self'.
 * Once the end of the directory has been reached, return NULL instead. */
PRIVATE WUNUSED NONNULL((1)) struct dirent *KCALL
readdir_buffer_peek(struct readdir_buffer *__restrict self) {
	size_t reqlen;
again:
	reqlen = handle_readdir(self->rb_file,
	                        self->rb_buf,
	                        self->rb_buflen,
	                        READDIR_PEEK);
	if unlikely(reqlen > self->rb_buflen) {
		/* Must increase the buffer size. */
		struct dirent *oldptr, *newptr;
		oldptr = self->rb_buf;
		if (oldptr == (struct dirent *)self->rb_sbuf)
			oldptr = NULL; /* Don't realloc a static pointer! */
		newptr = (struct dirent *)krealloc(oldptr, reqlen, GFP_NORMAL);
		self->rb_buf    = newptr;
		self->rb_buflen = reqlen;
		goto again;
	}
	/* Check for special case: end-of-directory */
	if (!reqlen)
		return NULL;
	/* Return a pointer to the directory entry we've just read. */
	return self->rb_buf;
}

/* Advance the underlying directory stream to the next directory entry. */
PRIVATE NONNULL((1)) void KCALL
readdir_buffer_continue(struct readdir_buffer *__restrict self) {
	handle_readdir(self->rb_file, NULL, 0, READDIR_CONTINUE);
}

/* Return the current, underlying stream position of `self' */
PRIVATE WUNUSED NONNULL((1)) pos64_t KCALL
readdir_buffer_getfpos(struct readdir_buffer *__restrict self) {
	return handle_seek(self->rb_file, 0, SEEK_CUR);
}




#ifdef __ARCH_WANT_SYSCALL_READDIR
typedef typeof(((struct old_linux_dirent *)0)->d_ino) old_linux_dirent_ino_t;
typedef typeof(((struct old_linux_dirent *)0)->d_offset) old_linux_dirent_off_t;
DEFINE_SYSCALL2(syscall_slong_t, readdir, fd_t, fd,
                NCX UNCHECKED struct old_linux_dirent *, buf) {
	struct readdir_buffer rb;
	struct dirent *ent;
	readdir_buffer_init(&rb, fd);
	FINALLY_readdir_buffer_fini(&rb);
	ent = readdir_buffer_peek(&rb);
	if (!ent)
		return 0;
	COMPILER_BARRIER();
	validate_writable(buf,
	                  offsetof(struct old_linux_dirent, d_name) +
	                  (ent->d_namlen + 1) * sizeof(char));
	buf->d_ino = (old_linux_dirent_ino_t)ent->d_ino;
	__STATIC_IF (sizeof(old_linux_dirent_ino_t) < sizeof(ino_t)) {
		if ((ino_t)buf->d_ino != ent->d_ino)
			THROW(E_OVERFLOW);
	}
	buf->d_namlen = ent->d_namlen;
	/* Copy the name to user-space.
	 * WARNING: This copy has no buffer  bounds, and there is no  way
	 *          for user-space to limit how much data is copied here.
	 *          Furthermore, on KOS  the max  *possible* name  length
	 *          copied here is 65535 (2^16)! */
	memcpy(buf->d_name, ent->d_name,
	       ent->d_namlen + 1,
	       sizeof(char));
	COMPILER_BARRIER();
	readdir_buffer_continue(&rb);
	COMPILER_BARRIER();
	buf->d_offset = (old_linux_dirent_off_t)readdir_buffer_getfpos(&rb);
	COMPILER_BARRIER();
	return 1;
}
#endif /* __ARCH_WANT_SYSCALL_READDIR */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_READDIR
typedef typeof(((struct compat_old_linux_dirent *)0)->d_ino) compat_old_linux_dirent_ino_t;
typedef typeof(((struct compat_old_linux_dirent *)0)->d_offset) compat_old_linux_dirent_off_t;
DEFINE_COMPAT_SYSCALL2(syscall_slong_t, readdir, fd_t, fd,
                       NCX UNCHECKED struct compat_old_linux_dirent *, buf) {

	struct readdir_buffer rb;
	struct dirent *ent;
	readdir_buffer_init(&rb, fd);
	FINALLY_readdir_buffer_fini(&rb);
	ent = readdir_buffer_peek(&rb);
	if (!ent)
		return 0;
	COMPILER_BARRIER();
	compat_validate_writable(buf,
	                         offsetof(struct compat_old_linux_dirent, d_name) +
	                         (ent->d_namlen + 1) * sizeof(char));
	buf->d_ino = (compat_old_linux_dirent_ino_t)ent->d_ino;
	__STATIC_IF (sizeof(compat_old_linux_dirent_ino_t) < sizeof(ino_t)) {
		if ((ino_t)buf->d_ino != ent->d_ino)
			THROW(E_OVERFLOW);
	}
	buf->d_namlen = ent->d_namlen;
	/* Copy the name to user-space.
	 * WARNING: This copy has no buffer  bounds, and there is no  way
	 *          for user-space to limit how much data is copied here.
	 *          Furthermore, on KOS  the max  *possible* name  length
	 *          copied here is 65535 (2^16)! */
	memcpy(buf->d_name, ent->d_name,
	       ent->d_namlen + 1,
	       sizeof(char));
	COMPILER_BARRIER();
	readdir_buffer_continue(&rb);
	COMPILER_BARRIER();
	buf->d_offset = (compat_old_linux_dirent_off_t)readdir_buffer_getfpos(&rb);
	COMPILER_BARRIER();
	return 1;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_READDIR */

#ifdef __ARCH_WANT_SYSCALL_GETDENTS
typedef typeof(((struct linux_dirent *)0)->d_ino) linux_dirent_ino_t;
typedef typeof(((struct linux_dirent *)0)->d_off) linux_dirent_off_t;
DEFINE_SYSCALL3(ssize_t, getdents, fd_t, fd,
                NCX UNCHECKED struct linux_dirent *, buf,
                size_t, buflen) {
	ssize_t result = 0;
	struct readdir_buffer rb;
	struct dirent *ent;
	validate_writable(buf, buflen);
	readdir_buffer_init(&rb, fd);
	FINALLY_readdir_buffer_fini(&rb);
	while ((ent = readdir_buffer_peek(&rb)) != NULL) {
		size_t reqlen, reclen;
		reqlen = offsetof(struct linux_dirent, d_name) +
		         (ent->d_namlen + 1) * sizeof(char);
		if (reqlen > buflen) {
			/* Insufficient space for yet another entry! */
			if (!result)
				THROW(E_INVALID_ARGUMENT); /* return -EINVAL; */
			goto done;
		}
		/* Translate the entry. */
		COMPILER_BARRIER();
		buf->d_ino = (linux_dirent_ino_t)ent->d_ino;
		__STATIC_IF (sizeof(linux_dirent_ino_t) < sizeof(ino_t)) {
			if ((ino_t)buf->d_ino != ent->d_ino)
				THROW(E_OVERFLOW);
		}
		reclen = CEIL_ALIGN(offsetof(struct linux_dirent, d_name) +
		                    ent->d_namlen + 2,
		                    sizeof(void *));
		memcpy(buf->d_name, ent->d_name,
		       ent->d_namlen + 1,
		       sizeof(char));
		buf->d_reclen = (u16)reclen;
		*(uint8_t *)((byte_t *)buf + reclen - 2) = 0; /* Mandated to be `0' */
		*(uint8_t *)((byte_t *)buf + reclen - 1) = ent->d_type;
		COMPILER_BARRIER();
		readdir_buffer_continue(&rb);
		COMPILER_BARRIER();
		buf->d_off = (linux_dirent_off_t)readdir_buffer_getfpos(&rb);
		COMPILER_BARRIER();
		++result;
		buf = (NCX UNCHECKED struct linux_dirent *)((byte_t *)buf + reclen);
		buflen -= reclen;
	}
done:
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_GETDENTS */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_GETDENTS
typedef typeof(((struct compat_linux_dirent *)0)->d_ino) compat_linux_dirent_ino_t;
typedef typeof(((struct compat_linux_dirent *)0)->d_off) compat_linux_dirent_off_t;
DEFINE_COMPAT_SYSCALL3(ssize_t, getdents, fd_t, fd,
                       NCX UNCHECKED struct compat_linux_dirent *, buf,
                       size_t, buflen) {
	ssize_t result = 0;
	struct readdir_buffer rb;
	struct dirent *ent;
	compat_validate_writable(buf, buflen);
	readdir_buffer_init(&rb, fd);
	FINALLY_readdir_buffer_fini(&rb);
	while ((ent = readdir_buffer_peek(&rb)) != NULL) {
		size_t reqlen, reclen;
		reqlen = offsetof(struct compat_linux_dirent, d_name) +
		         (ent->d_namlen + 1) * sizeof(char);
		if (reqlen > buflen) {
			/* Insufficient space for yet another entry! */
			if (!result)
				THROW(E_INVALID_ARGUMENT); /* return -EINVAL; */
			goto done;
		}
		/* Translate the entry. */
		COMPILER_BARRIER();
		buf->d_ino = (compat_linux_dirent_ino_t)ent->d_ino;
		__STATIC_IF (sizeof(compat_linux_dirent_ino_t) < sizeof(ino_t)) {
			if ((ino_t)buf->d_ino != ent->d_ino)
				THROW(E_OVERFLOW);
		}
		reclen = CEIL_ALIGN(offsetof(struct compat_linux_dirent, d_name) +
		                    ent->d_namlen + 2,
		                    sizeof(void *));
		memcpy(buf->d_name, ent->d_name,
		       ent->d_namlen + 1,
		       sizeof(char));
		buf->d_reclen = (u16)reclen;
		*(uint8_t *)((byte_t *)buf + reclen - 2) = 0; /* Mandated to be `0' */
		*(uint8_t *)((byte_t *)buf + reclen - 1) = ent->d_type;
		COMPILER_BARRIER();
		readdir_buffer_continue(&rb);
		COMPILER_BARRIER();
		buf->d_off = (compat_linux_dirent_off_t)readdir_buffer_getfpos(&rb);
		COMPILER_BARRIER();
		++result;
		buf = (NCX UNCHECKED struct compat_linux_dirent *)((byte_t *)buf + reclen);
		buflen -= reclen;
	}
done:
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_GETDENTS */

#ifdef __ARCH_WANT_SYSCALL_GETDENTS64
typedef typeof(((struct linux_dirent64 *)0)->d_ino) linux_dirent64_ino_t;
typedef typeof(((struct linux_dirent64 *)0)->d_off) linux_dirent64_off_t;
DEFINE_SYSCALL3(ssize_t, getdents64, fd_t, fd,
                NCX UNCHECKED struct linux_dirent64 *, buf,
                size_t, buflen) {
	ssize_t result = 0;
	struct readdir_buffer rb;
	struct dirent *ent;
	validate_writable(buf, buflen);
	readdir_buffer_init(&rb, fd);
	FINALLY_readdir_buffer_fini(&rb);
	while ((ent = readdir_buffer_peek(&rb)) != NULL) {
		size_t reqlen, reclen;
		reqlen = offsetof(struct linux_dirent64, d_name) +
		         (ent->d_namlen + 1) * sizeof(char);
		if (reqlen > buflen) {
			/* Insufficient space for yet another entry! */
			if (!result)
				THROW(E_INVALID_ARGUMENT); /* return -EINVAL; */
			goto done;
		}
		/* Translate the entry. */
		COMPILER_BARRIER();
		buf->d_ino = (linux_dirent64_ino_t)ent->d_ino;
		__STATIC_IF (sizeof(linux_dirent64_ino_t) < sizeof(ino_t)) {
			if ((ino_t)buf->d_ino != ent->d_ino)
				THROW(E_OVERFLOW);
		}
		reclen = CEIL_ALIGN(offsetof(struct linux_dirent64, d_name) +
		                    ent->d_namlen + 2,
		                    sizeof(void *));
		memcpy(buf->d_name, ent->d_name,
		       ent->d_namlen + 1,
		       sizeof(char));
		buf->d_reclen = (u16)reclen;
		buf->d_type   = ent->d_type;
		COMPILER_BARRIER();
		readdir_buffer_continue(&rb);
		COMPILER_BARRIER();
		buf->d_off = (linux_dirent64_off_t)readdir_buffer_getfpos(&rb);
		COMPILER_BARRIER();
		++result;
		buf = (NCX UNCHECKED struct linux_dirent64 *)((byte_t *)buf + reclen);
		buflen -= reclen;
	}
done:
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_GETDENTS64 */

DECL_END
#endif /* WANT_LINUX_READDIR */

#endif /* !GUARD_KERNEL_CORE_MISC_LINUX_READDIR_C */
