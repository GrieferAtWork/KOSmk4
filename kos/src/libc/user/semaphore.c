/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SEMAPHORE_C
#define GUARD_LIBC_USER_SEMAPHORE_C 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>

#include <kos/futex.h>
#include <kos/syscalls.h>
#include <sys/mman.h>
#include <sys/time.h>

#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <malloca.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "semaphore.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#if SEM_VALUE_MAX == INT8_MAX
#define SEM_COUNT_MASK   UINT8_C(0x7f)
#define SEM_WAITERS_FLAG UINT8_C(0x80)
#elif SEM_VALUE_MAX == INT16_MAX
#define SEM_COUNT_MASK   UINT16_C(0x7fff)
#define SEM_WAITERS_FLAG UINT16_C(0x8000)
#elif SEM_VALUE_MAX == INT32_MAX
#define SEM_COUNT_MASK   UINT32_C(0x7fffffff)
#define SEM_WAITERS_FLAG UINT32_C(0x80000000)
#elif SEM_VALUE_MAX == INT64_MAX
#define SEM_COUNT_MASK   UINT64_C(0x7fffffffffffffff)
#define SEM_WAITERS_FLAG UINT64_C(0x8000000000000000)
#else /* SEM_VALUE_MAX == ... */
#error "Unsupported `SEM_VALUE_MAX'"
#endif /* SEM_VALUE_MAX != ... */

/* <=, because `__SIZEOF_SEM_T' is the public ABI buffer size, while,
 * us being libc,  sizeof(sem_t) is the  actually used/needed  buffer
 * size, meaning that libc users  are allowed to provide more  buffer
 * space than we actually need. */
STATIC_ASSERT(sizeof(sem_t) <= __SIZEOF_SEM_T);



/*[[[head:libc_sem_init,hash:CRC-32=0x9df0c86f]]]*/
/* >> sem_init(3)
 * Initialize the given semaphore `sem' to start out with `value' tickets
 * @param: sem:     The semaphore to initialize
 * @param: pshared: When  non-zero, `sem'  may point  to a  memory region shared
 *                  with another process, such that both caller, and any process
 *                  the pointed-to memory is shared  with can safely operate  on
 *                  the same semaphore.
 * @param: value:   The initial # of tickets available.
 * @return: 0:      Success
 * @return: -1:     [errno=EINVAL] `value > SEM_VALUE_MAX'
 *                  HINT: Never returned `#if SEM_VALUE_MAX >= UINT_MAX'
 * @return: -1:     [errno=ENOSYS] `pshared != 0', but inter-process semaphores aren't supported
 *                  HINT: Never returned `#ifdef __ARCH_HAVE_INTERPROCESS_SEMAPHORES' */
INTERN ATTR_SECTION(".text.crt.sched.semaphore") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sem_init)(sem_t *sem,
                                    int pshared,
                                    unsigned int value)
/*[[[body:libc_sem_init]]]*/
{
	(void)pshared;
#if UINT_MAX > SEM_COUNT_MASK
	if unlikely(value > SEM_COUNT_MASK)
		return libc_seterrno(EINVAL);
#endif /* UINT_MAX > SEM_COUNT_MASK */
	DBG_memset(sem, 0xcc, __SIZEOF_SEM_T);
	sem->s_count = value;
	return 0;
}
/*[[[end:libc_sem_init]]]*/

/*[[[head:libc_sem_destroy,hash:CRC-32=0x42732111]]]*/
/* >> sem_destroy(3)
 * Destroy a semaphore previously initialized by `sem_init(3)'
 * @return: 0: Success */
INTERN ATTR_SECTION(".text.crt.sched.semaphore") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sem_destroy)(sem_t *sem)
/*[[[body:libc_sem_destroy]]]*/
{
	COMPILER_IMPURE();
	(void)sem;
	/* Nothing to do here... */
	DBG_memset(sem, 0xcc, __SIZEOF_SEM_T);
	return 0;
}
/*[[[end:libc_sem_destroy]]]*/



PRIVATE ATTR_SECTION(".rodata.crt.sched.semaphore") char const named_prefix[] = "/dev/shm/sem.";
#define NAMED_PREFIX_OFFSETOF_SEM COMPILER_STRLEN("/dev/shm/")


/*[[[head:libc_sem_open,hash:CRC-32=0x3ad38857]]]*/
/* >> sem_open(3)
 * Open a named semaphore `name', which must be string that starts with `/'
 * NOTE: When called multiple times with identical strings for  `name',
 *       the behavior of this function differs between implementations:
 *       #ifdef __ARCH_HAVE_NON_UNIQUE_SEM_OPEN
 *          The  returned pointer is  allowed to be  unique and different from
 *          any previously returned semaphore, but the backing physical memory
 *          will be shared with other semaphores with the same name.
 *       #else // __ARCH_HAVE_NON_UNIQUE_SEM_OPEN
 *          The returned pointer  may be identical  to a pointer  previously
 *          returned for the same semaphore. In this case, `sem_close()' may
 *          only have to be  called once to close  all open handles for  the
 *          semaphore
 *       #endif // !__ARCH_HAVE_NON_UNIQUE_SEM_OPEN
 * @param: oflags:      Set of `0 | O_CREAT | O_EXCL' (When `O_CREAT' is given, this functions
 *                      takes 2  additional arguments  `..., mode_t mode, unsigned int value')
 * @return: * :         A pointer to the opened semaphore, which must be closed by `sem_close(3)'
 * @return: SEM_FAILED: [errno=EINVAL] The given `name' contains no characters after the initial `/'
 * @return: SEM_FAILED: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.semaphore") NONNULL((1)) sem_t *
NOTHROW_RPC_KOS(VLIBCCALL libc_sem_open)(char const *name,
                                         oflag_t oflags,
                                         ...)
/*[[[body:libc_sem_open]]]*/
{
#define MMAP_SEMAPHORE(fd)                                        \
	((sem_t *)mmap(NULL, sizeof(sem_t),                           \
	               PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, \
	               (fd), 0))
	char *filename;
	size_t name_length;
	fd_t fd;
	va_list args;
	mode_t mode;
	sem_t *result;
	unsigned int value;
	while (*name == '/')
		++name;
	va_start(args, oflags);
	mode  = va_arg(args, mode_t);
	value = va_arg(args, unsigned int);
	va_end(args);
	name_length = strlen(name);
	if unlikely(!name_length || (oflags & (O_CREAT | O_EXCL)) != 0) {
		libc_seterrno(EINVAL);
		goto err;
	}
	filename = (char *)malloca(COMPILER_STRLEN(named_prefix) +
	                           name_length + 1,
	                           sizeof(char));
	if unlikely(!filename)
		goto err;
	memcpy(mempcpy(filename, named_prefix,
	               sizeof(named_prefix) - sizeof(char)),
	       name, name_length + 1, sizeof(char));
	if ((oflags & O_CREAT) != 0 && (value != 0)) {
again_open_or_create:
		/* Special case: We need to know when the semaphore gets created, so we
		 *               can set the initial counter  value only in that  case.
		 * To prevent the semaphore from becoming visible to other processes before
		 * then, we create it under a different name, which we then refactor to the
		 * proper name once it's been initialized. */
		fd = open(filename, O_RDWR | O_CREAT | O_CLOEXEC | O_CLOFORK, mode);
		if (fd != -1) {
			/* Semaphore already exists. */
			if unlikely(oflags & O_EXCL) {
				sys_close(fd);
				libc_seterrno(EEXIST);
				goto err_filename;
			}
		} else {
			char *tempname;
			size_t namesize;
			/* With the semaphore initialized, rename
			 * the temporary file to its proper name. */
			namesize = (COMPILER_STRLEN(named_prefix) +
			            name_length + 1) *
			           sizeof(char);
			tempname = (char *)malloca(namesize);
			if unlikely(!tempname)
				goto err_filename;
			memcpy(tempname, filename, namesize);
			tempname[NAMED_PREFIX_OFFSETOF_SEM] = 't';
again_create_temp_file:
			fd = open(tempname, O_RDWR | O_CREAT | O_EXCL | O_CLOEXEC | O_CLOFORK, mode);
			if unlikely(fd == -1) {
				struct timespec ts;
				if unlikely(libc_geterrno() != EEXIST) {
err_tempname_filename:
					freea(tempname);
					goto err_filename;
				}
				/* Another process may  currently be creating  the same  semaphore
				 * in the same way as  we are trying to.  On the other hand,  that
				 * other  process may have  terminated/crashed before it finished,
				 * and the remaining file that we're seeing is just a left-over...
				 *
				 * Handle this case by giving  that potential other process  some
				 * time to finish, and if the file still exists after this delay,
				 * forcibly remove it to deal with problematic processes. */
				ts.tv_sec  = 0;
				ts.tv_nsec = 25000000; /* 1/40th of a second. */
				nanosleep(&ts, NULL);
				fd = open(tempname, O_RDWR | O_CREAT | O_EXCL | O_CLOEXEC | O_CLOFORK, mode);
				if (fd == -1) {
					if unlikely(libc_geterrno() != EEXIST)
						goto err_tempname_filename;
					/* Just delete the file and re-create it ourself. */
					if unlikely(unlink(tempname) != 0)
						goto err_tempname_filename;
					goto again_create_temp_file;
				}
			}
			result = MMAP_SEMAPHORE(fd);
			sys_close(fd);
			if unlikely(result == (sem_t *)MAP_FAILED) {
				sys_unlink(tempname);
				goto err_tempname_filename;
			}
			/* Fill in the initial count value. */
			result->s_count = value;
			COMPILER_BARRIER();
			/* Try to rename the temporary file to its proper name, thus making
			 * the  (now  initialized)  semaphore visible  to  other processes. */
			if (rename(tempname, filename) != 0) {
				errno_t error;
				sys_unlink(tempname);
				freea(tempname);
				error = libc_geterrno();
				if (error == EEXIST) {
					/* Race condition: Another thread created the semaphore in the mean time. */
					if (oflags & O_EXCL) {
						libc_seterrno(EEXIST);
						goto err_filename;
					}
					goto again_open_or_create;
				}
				if (error == ENOENT) {
					/* Race condition: We took too long to create the semaphore, and another thread
					 * got  bored while waiting for us. Wait (a  bit longer than they did) for them
					 * to create the semaphore, and try again. */
					struct timespec ts;
					ts.tv_sec  = 0;
					ts.tv_nsec = 250000000; /* 1/4th of a second. */
					nanosleep(&ts, NULL);
					goto again_open_or_create;
				}
				goto err_filename; /* Some other error... */
			}
			freea(tempname);
			/* Success: new semaphore was created and initialized. */
			return result;
		}
	}
	fd = open(filename, O_RDWR | oflags | O_CLOEXEC | O_CLOFORK, mode);
	if unlikely(fd < 0)
		goto err_filename;
	freea(filename);
	result = MMAP_SEMAPHORE(fd);
	sys_close(fd);
	if unlikely(result == (sem_t *)MAP_FAILED)
		goto err;
	return result;
err_filename:
	freea(filename);
err:
	return SEM_FAILED;
}
/*[[[end:libc_sem_open]]]*/

/*[[[head:libc_sem_close,hash:CRC-32=0x41ee39f3]]]*/
/* >> sem_close(3)
 * Close a semaphore previously returned by `sem_open(3)'. But note the case
 * of opening the same semaphore more than once within the same process,  as
 * described by in `sem_open(3)' and by `__ARCH_HAVE_NON_UNIQUE_SEM_OPEN'->
 * @return: 0: Success */
INTERN ATTR_SECTION(".text.crt.sched.semaphore") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sem_close)(sem_t *sem)
/*[[[body:libc_sem_close]]]*/
{
	return munmap(sem, sizeof(sem_t));
}
/*[[[end:libc_sem_close]]]*/

/*[[[head:libc_sem_unlink,hash:CRC-32=0x33d24593]]]*/
/* >> sem_unlink(3)
 * Unlink (delete) a named semaphore `name' that was
 * previously  created  by `sem_open(name, O_CREAT)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `name' contains no characters after the initial `/'
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.semaphore") NONNULL((1)) int
NOTHROW_RPC_KOS(LIBCCALL libc_sem_unlink)(const char *name)
/*[[[body:libc_sem_unlink]]]*/
{
	int result;
	char *filename;
	size_t name_length;
	while (*name == '/')
		++name;
	name_length = strlen(name);
	if unlikely(!name_length) {
		libc_seterrno(EINVAL);
		goto err;
	}
	filename = (char *)malloca(COMPILER_STRLEN(named_prefix) +
	                           name_length + 1,
	                           sizeof(char));
	if unlikely(!filename)
		goto err;
	memcpy(mempcpy(filename, named_prefix,
	               sizeof(named_prefix) - sizeof(char)),
	       name, name_length + 1, sizeof(char));
	result = unlink(filename);
	freea(filename);
	return result;
err:
	return -1;
}
/*[[[end:libc_sem_unlink]]]*/

/*[[[head:libc_sem_wait,hash:CRC-32=0x725db4a0]]]*/
/* >> sem_wait(3)
 * Wait  for a ticket  to become available to  the given semaphore `sem'
 * Once a ticket has become available, consume it and return. Until that
 * point in time, keep on blocking.
 * @return: 0:  Success
 * @return: -1: [errno=EINTR] Interrupted. */
INTERN ATTR_SECTION(".text.crt.sched.semaphore") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_sem_wait)(sem_t *sem)
/*[[[body:libc_sem_wait]]]*/
{
	for (;;) {
		int error;
		lfutex_t oldval;
		oldval = ATOMIC_READ(sem->s_count);
		if (oldval & SEM_COUNT_MASK) {
			if (!ATOMIC_CMPXCH_WEAK(sem->s_count, oldval, oldval - 1))
				continue;
			return 0; /* Success! */
		}
		/* Set the is-waiting bit the first time around. */
		if (!(oldval & SEM_WAITERS_FLAG)) {
			if (!ATOMIC_CMPXCH_WEAK(sem->s_count,
			                        oldval,
			                        oldval | SEM_WAITERS_FLAG))
				continue;
		}
		/* Wait until `SEM_COUNT_MASK' becomes non-zero. */
		error = futex_waitwhile_exactbits(&sem->s_count,
		                                  SEM_COUNT_MASK,
		                                  0);
		if (error < 0)
			return error;
	}
	return 0;
}
/*[[[end:libc_sem_wait]]]*/

/*[[[head:libc_sem_timedwait,hash:CRC-32=0xc28b06c9]]]*/
/* >> sem_timedwait(3), sem_timedwait64(3)
 * Wait for a  ticket to  become available  to the  given semaphore  `sem'
 * Once a ticket has become available, consume it and return. If no ticket
 * becomes  available until `abstime' has passed, return `errno=ETIMEDOUT'
 * @return: 0:  Success
 * @return: -1: [errno=EINTR]     Interrupted.
 * @return: -1: [errno=ETIMEDOUT] The given `abstime' expired before a ticket became available. */
INTERN ATTR_SECTION(".text.crt.sched.semaphore") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_sem_timedwait)(sem_t *__restrict sem,
                                         struct timespec const *__restrict abstime)
/*[[[body:libc_sem_timedwait]]]*/
{
	for (;;) {
		int error;
		lfutex_t oldval;
		oldval = ATOMIC_READ(sem->s_count);
		if (oldval & SEM_COUNT_MASK) {
			if (!ATOMIC_CMPXCH_WEAK(sem->s_count, oldval, oldval - 1))
				continue;
			return 0; /* Success! */
		}
		/* Set the is-waiting bit the first time around. */
		if (!(oldval & SEM_WAITERS_FLAG)) {
			if (!ATOMIC_CMPXCH_WEAK(sem->s_count,
			                        oldval,
			                        oldval | SEM_WAITERS_FLAG))
				continue;
		}
		/* Wait until `SEM_COUNT_MASK' becomes non-zero. */
		error = lfutex(&sem->s_count,
		               LFUTEX_WAIT_WHILE_BITMASK |
		               LFUTEX_WAIT_FLAG_TIMEOUT_REALTIME,
		               (lfutex_t)SEM_COUNT_MASK,
		               abstime, (lfutex_t)0);
		if (error < 0)
			return error;
	}
	return 0;
}
/*[[[end:libc_sem_timedwait]]]*/

/*[[[head:libc_sem_timedwait64,hash:CRC-32=0xfc8ce2f]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_sem_timedwait64, libc_sem_timedwait);
#else /* MAGIC:alias */
/* >> sem_timedwait(3), sem_timedwait64(3)
 * Wait for a  ticket to  become available  to the  given semaphore  `sem'
 * Once a ticket has become available, consume it and return. If no ticket
 * becomes  available until `abstime' has passed, return `errno=ETIMEDOUT'
 * @return: 0:  Success
 * @return: -1: [errno=EINTR]     Interrupted.
 * @return: -1: [errno=ETIMEDOUT] The given `abstime' expired before a ticket became available. */
INTERN ATTR_SECTION(".text.crt.sched.semaphore") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_sem_timedwait64)(sem_t *__restrict sem,
                                           struct timespec64 const *__restrict abstime)
/*[[[body:libc_sem_timedwait64]]]*/
{
	for (;;) {
		int error;
		lfutex_t oldval;
		oldval = ATOMIC_READ(sem->s_count);
		if (oldval & SEM_COUNT_MASK) {
			if (!ATOMIC_CMPXCH_WEAK(sem->s_count, oldval, oldval - 1))
				continue;
			return 0; /* Success! */
		}
		/* Set the is-waiting bit the first time around. */
		if (!(oldval & SEM_WAITERS_FLAG)) {
			if (!ATOMIC_CMPXCH_WEAK(sem->s_count,
			                        oldval,
			                        oldval | SEM_WAITERS_FLAG))
				continue;
		}
		/* Wait until `SEM_COUNT_MASK' becomes non-zero. */
		error = lfutex64(&sem->s_count,
		                 LFUTEX_WAIT_WHILE_BITMASK |
		                 LFUTEX_WAIT_FLAG_TIMEOUT_REALTIME,
		                 (lfutex_t)SEM_COUNT_MASK,
		                 abstime, (lfutex_t)0);
		if (error < 0)
			return error;
	}
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_sem_timedwait64]]]*/

/*[[[head:libc_sem_trywait,hash:CRC-32=0x3007d222]]]*/
/* >> sem_trywait(3)
 * Atomically check if at least 1 ticket is available for `sem', and consume
 * one if this is the case, or return with `errno=EAGAIN' if no tickets were
 * available at the time of the call.
 * @return: 0:  Success
 * @return: -1: [errno=EAGAIN] A ticket could not be acquired without blocking. */
INTERN ATTR_SECTION(".text.crt.sched.semaphore") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sem_trywait)(sem_t *sem)
/*[[[body:libc_sem_trywait]]]*/
{
	lfutex_t oldval;
again:
	oldval = ATOMIC_READ(sem->s_count);
	if (oldval & SEM_COUNT_MASK) {
		if (!ATOMIC_CMPXCH_WEAK(sem->s_count, oldval, oldval - 1))
			goto again;
		return 0; /* Success! */
	}
	/* No tickets available... */
	libc_seterrno(EAGAIN);
	return -1;
}
/*[[[end:libc_sem_trywait]]]*/

/*[[[head:libc_sem_post,hash:CRC-32=0x6fdea9c3]]]*/
/* >> sem_post(3)
 * Post a ticket to the given semaphore `sem', waking up to 1 other thread
 * that may be waiting for  tickets to become available before  returning.
 * @return: 0:  Success
 * @return: -1: [errno=EOVERFLOW] The maximum number of tickets have already been posted. */
INTERN ATTR_SECTION(".text.crt.sched.semaphore") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sem_post)(sem_t *sem)
/*[[[body:libc_sem_post]]]*/
{
	lfutex_t oldval;
	do {
		oldval = ATOMIC_READ(sem->s_count);
		if unlikely((oldval & SEM_COUNT_MASK) == SEM_VALUE_MAX)
			return libc_seterrno(EOVERFLOW);
	} while (!ATOMIC_CMPXCH_WEAK(sem->s_count,
	                             oldval,
	                             oldval + 1));
	/* If there are waiting threads, wake one of them. */
	if (oldval & SEM_WAITERS_FLAG) {
		/* NOTE: Make use of `LFUTEX_WAKEMASK' to do the equivalent of:
		 * >> if (!sys_lfutex(&self->s_count, LFUTEX_WAKE, 1, NULL, 0)) {
		 * >>     ATOMIC_AND(&self->s_count, ~SEM_WAITERS_FLAG);
		 * >>     sys_lfutex(&self->s_count, LFUTEX_WAKE, (size_t)-1, NULL, 0);
		 * >> } */
		sys_lfutex(&sem->s_count, LFUTEX_WAKEMASK, 1,
		           (struct timespec64 const *)(uintptr_t)~SEM_WAITERS_FLAG, 0);
	}
	return 0;
}
/*[[[end:libc_sem_post]]]*/

/*[[[head:libc_sem_getvalue,hash:CRC-32=0xe7b0d8bf]]]*/
/* >> sem_getvalue(3)
 * Capture a snapshot of how may tickets are available storing that number in `*sval'
 * @return: 0: Success */
INTERN ATTR_SECTION(".text.crt.sched.semaphore") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_sem_getvalue)(sem_t *__restrict sem,
                                        __STDC_INT_AS_UINT_T *__restrict sval)
/*[[[body:libc_sem_getvalue]]]*/
{
	*sval = (int)(unsigned int)(ATOMIC_READ(sem->s_count) & SEM_COUNT_MASK);
	return 0;
}
/*[[[end:libc_sem_getvalue]]]*/


/*[[[start:exports,hash:CRC-32=0x83453b4]]]*/
DEFINE_PUBLIC_ALIAS(sem_init, libc_sem_init);
DEFINE_PUBLIC_ALIAS(sem_destroy, libc_sem_destroy);
DEFINE_PUBLIC_ALIAS(sem_open, libc_sem_open);
DEFINE_PUBLIC_ALIAS(sem_close, libc_sem_close);
DEFINE_PUBLIC_ALIAS(sem_unlink, libc_sem_unlink);
DEFINE_PUBLIC_ALIAS(sem_wait, libc_sem_wait);
DEFINE_PUBLIC_ALIAS(sem_timedwait, libc_sem_timedwait);
DEFINE_PUBLIC_ALIAS(sem_timedwait64, libc_sem_timedwait64);
DEFINE_PUBLIC_ALIAS(sem_trywait, libc_sem_trywait);
DEFINE_PUBLIC_ALIAS(sem_post, libc_sem_post);
DEFINE_PUBLIC_ALIAS(sem_getvalue, libc_sem_getvalue);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SEMAPHORE_C */
