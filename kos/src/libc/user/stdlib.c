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
#ifndef GUARD_LIBC_USER_STDLIB_C
#define GUARD_LIBC_USER_STDLIB_C 1
#define _KOS_SOURCE 1
#define _UTF_SOURCE 1
#define _ALL_LIMITS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/sched/atomic-once.h>
#include <hybrid/sched/atomic-rwlock.h>
#include <hybrid/unaligned.h>

#include <kos/exec/idata.h>
#include <kos/exec/peb.h>
#include <kos/syscalls.h>
#include <sys/auxv.h>
#include <sys/wait.h>

#include <assert.h>
#include <atomic.h>
#include <ctype.h>
#include <direct.h>
#include <fcntl.h>
#include <format-printer.h>
#include <limits.h>
#include <malloc.h>
#include <malloca.h>
#include <pthread.h>
#include <sched.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <uchar.h>
#include <unistd.h>

#include "../libc/compat.h"
#include "../libc/dl.h"
#include "../libc/errno.h"
#include "../libc/globals.h"
#include "../libc/init.h"
#include "malloc.h"
#include "stdlib.h"


DECL_BEGIN

INTERN ATTR_SECTION(".bss.crt.fs.environ")
struct atomic_rwlock libc_environ_lock = ATOMIC_RWLOCK_INIT;

DEFINE_PUBLIC_ALIAS(__p__environ, libc_p_environ);
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.dos.fs.environ")
char ***NOTHROW(LIBCCALL libc_p_environ)(void) {
	return &environ;
}

/* Helper macros for `libc_environ_lock' */
#define environ_mustreap()   0
#define environ_reap()       (void)0
#define _environ_reap()      (void)0
#define environ_write()      atomic_rwlock_write(&libc_environ_lock)
#define environ_trywrite()   atomic_rwlock_trywrite(&libc_environ_lock)
#define environ_endwrite()   (atomic_rwlock_endwrite(&libc_environ_lock), environ_reap())
#define _environ_endwrite()  atomic_rwlock_endwrite(&libc_environ_lock)
#define environ_read()       atomic_rwlock_read(&libc_environ_lock)
#define environ_tryread()    atomic_rwlock_tryread(&libc_environ_lock)
#define _environ_endread()   atomic_rwlock_endread(&libc_environ_lock)
#define environ_endread()    (void)(atomic_rwlock_endread_ex(&libc_environ_lock) && (environ_reap(), 0))
#define _environ_end()       atomic_rwlock_end(&libc_environ_lock)
#define environ_end()        (void)(atomic_rwlock_end_ex(&libc_environ_lock) && (environ_reap(), 0))
#define environ_upgrade()    atomic_rwlock_upgrade(&libc_environ_lock)
#define environ_tryupgrade() atomic_rwlock_tryupgrade(&libc_environ_lock)
#define environ_downgrade()  atomic_rwlock_downgrade(&libc_environ_lock)
#define environ_reading()    atomic_rwlock_reading(&libc_environ_lock)
#define environ_writing()    atomic_rwlock_writing(&libc_environ_lock)
#define environ_canread()    atomic_rwlock_canread(&libc_environ_lock)
#define environ_canwrite()   atomic_rwlock_canwrite(&libc_environ_lock)
#define environ_waitread()   atomic_rwlock_waitread(&libc_environ_lock)
#define environ_waitwrite()  atomic_rwlock_waitwrite(&libc_environ_lock)


/* Since `environ' can easily  contain strings that weren't  allocated
 * using  `malloc()' and friends, and since `putenv()' is a thing that
 * exists to directly  inject user-provided strings  into the  environ
 * map, we run into a problem when it comes to preventing memory leaks
 * in regards of strings that _were_ injected dynamically through  use
 * of functions such as `setenv()'
 * The solution is to keep track of a singly-linked list of all environ
 * strings that _were_ allocated through use of `malloc()', and  simply
 * `free()' only  strings apart  of this  list when  functions such  as
 * `unsetenv()' or `clearenv()' are called.
 * Lastly,  in order  to check if  the `environ' vector  itself was dynamically
 * allocated  on  the  heap,  we   keep  a  secondary,  environ-like   variable
 * `libc_environ_heap' that is set to `NULL' initially (or after `clearenv()'),
 * and when non-NULL is then compared  against the real `environ' to  determine
 * is  changes  were made,  including  the hosted  application  overwriting the
 * value of `environ' itself. */

struct environ_heapstr {
	struct environ_heapstr       *ehs_next;  /* [0..1] next heap string. */
	COMPILER_FLEXIBLE_ARRAY(char, ehs_text); /* The NUL-terminated text of this string. */
};

/* [lock(libc_environ_lock)][0..1] The heap-allocated variant of `environ', or `NULL' if never used. */
PRIVATE ATTR_SECTION(".bss.crt.fs.environ.heap") char **libc_environ_heap = NULL;
/* [lock(libc_environ_lock)][0..1] Linked list of heap-allocated environ strings. */
PRIVATE ATTR_SECTION(".bss.crt.fs.environ.heap") struct environ_heapstr *libc_environ_strings = NULL;

LOCAL ATTR_SECTION(".text.crt.fs.environ.heap") bool LIBCCALL
environ_remove_heapstring_locked(struct environ_heapstr *ptr) {
	struct environ_heapstr **piter, *iter;
	assert(environ_reading());
	for (piter = &libc_environ_strings; (iter = *piter) != NULL;
	     piter = &iter->ehs_next) {
		if (iter == ptr) {
			*piter = iter->ehs_next;
			return true;
		}
	}
	return false;
}


PRIVATE ATTR_SECTION(".data.crt.sched.process")
pthread_key_t libc_cxa_thread_atexit_key = PTHREAD_ONCE_KEY_NP;
struct cxa_thread_atexit_entry {
	struct cxa_thread_atexit_entry *ctae_next; /* [0..1][owned] Next at-exit callback item. */
	void (LIBKCALL *ctae_func)(void *arg);     /* [1..1] Callback */
	void           *ctae_arg;                  /* [?..?] Cookie-argument for `ctae_func' */
	void           *ctae_dl_handle;            /* [1..1][REF] Module handle for `ctae_func' (must be dlclose'd) */
};

PRIVATE ATTR_SECTION(".text.crt.sched.process") void LIBKCALL
libc_cxa_thread_atexit_callback(void *data) {
	struct cxa_thread_atexit_entry *iter, *next;
	iter = (struct cxa_thread_atexit_entry *)data;
	while (iter) {
		next = iter->ctae_next;
		(*iter->ctae_func)(iter->ctae_arg);
		dlclose(iter->ctae_dl_handle);
		free(iter);
		iter = next;
	}
}

DEFINE_PUBLIC_WEAK_ALIAS(__cxa_thread_atexit, libc___cxa_thread_atexit_impl); /* WEAK, because libstdc++ likes to override this one */
DEFINE_PUBLIC_ALIAS(__cxa_thread_atexit_impl, libc___cxa_thread_atexit_impl);

/* C++ ABI function to dynamically register at-exit callbacks
 * to-be  invoked  as  soon  as  the  calling  thread  exits.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.process") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc___cxa_thread_atexit_impl)(void (LIBKCALL *func)(void *arg),
                                                    void *arg, void *dso_handle) {
	struct cxa_thread_atexit_entry *entry;
	errno_t error;
	/* Make sure that the cxa thread at-exit TLS descriptor has been allocated. */
	error = pthread_key_create_once_np(&libc_cxa_thread_atexit_key,
	                                   &libc_cxa_thread_atexit_callback);
	if unlikely(error != EOK)
		return libc_seterrno(error);

	/* Create a new entry for the cxa thread at-exit chain. */
	entry = (struct cxa_thread_atexit_entry *)malloc(sizeof(struct cxa_thread_atexit_entry));
	if unlikely(!entry)
		return -1;

	/* Get a  reference to  the specified  DL module  so  it
	 * can't be unloaded until the at-exit function has run. */
	if (dso_handle == NULL) {
		entry->ctae_dl_handle = dlopen(NULL, 0); /* Main program */
	} else {
		entry->ctae_dl_handle = dlgethandle(dso_handle, DLGETHANDLE_FINCREF);
	}
	if unlikely(!entry->ctae_dl_handle) {
		free(entry);
		return libc_seterrno(EFAULT); /* `dso_handle' doesn't map to any known module. */
	}
	entry->ctae_next = (struct cxa_thread_atexit_entry *)pthread_getspecific(libc_cxa_thread_atexit_key);
	entry->ctae_func = func;
	entry->ctae_arg  = arg;

	/* Store the new entry in our thread's at-exit callback chain. */
	error = pthread_setspecific(libc_cxa_thread_atexit_key, entry);
	if unlikely(error != EOK) {
		dlclose(entry->ctae_dl_handle);
		free(entry);
		return -1;
	}
	return 0;
}

/* TODO: Add support for: __cxa_at_quick_exit */
/* TODO: Add support for: __cxa_finalize */
DEFINE_PUBLIC_ALIAS(__cxa_atexit, libc___cxa_atexit);

INTERN ATTR_SECTION(".text.crt.sched.process") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc___cxa_atexit)(void (LIBCCALL *func)(void *arg),
                                        void *arg, void *dso_handle) {
	void *dl_handle, *error;
	/* NOTE: I  don't  really understand  why  this function  is  even necessary...
	 *       I mean sure:  it allows  c++ to register  destructor callbacks  lazily
	 *       for local statics, however the same effect could be achieved by  using
	 *       an __attribute__((destructor)), where its callback checks some kind of
	 *       was-initialized flag  and invokes  that callback  when this  is  true. */
	if (dso_handle == NULL) {
		/* Special case: When  `dso_handle'  is  `NULL',   register  the  callback  for   the
		 *               primary module, in which case the registered function must be called
		 *               alongside atexit() */
		dl_handle = NULL;
	} else {
		/* `dso_handle' is actually a pointer somewhere inside of the static memory segment
		 * of  some module  (either dynamically allocated,  or part of  the primary module)
		 * As such, we can make use of `dlgethandle(3D)' in order to look-up the associated
		 * shared object, which which we can then register the given callback. */
		dl_handle = dlgethandle(dso_handle, DLGETHANDLE_FINCREF);
		if unlikely(!dl_handle)
			return libc_seterrno(EFAULT); /* `dso_handle' doesn't map to any known module. */
	}
	/* Call into libdl to register the finalizer with the associated shared object. */
	error = dlauxctrl(dl_handle, DLAUXCTRL_ADD_FINALIZER, func, arg);
	dlclose(dl_handle);
	if unlikely(!error)
		return -1;
	return 0;
}








PRIVATE ATTR_SECTION(".rodata.crt.random") u32 const rand_map[] = {
	0x11e0ebcc, 0xa914eba6, 0xe400e438, 0xa6c4a4df,
	0x0da46171, 0x4b9a27d1, 0x201910ae, 0x95e213cb,
	0xd5ce0943, 0x00005fdc, 0x0319257d, 0x09280b06,
	0x1148c0a6, 0x07a24139, 0x021214a6, 0x03221af8
};
PRIVATE ATTR_SECTION(".bss.crt.random") u32 libc_seed = 0;
PRIVATE ATTR_SECTION(".text.crt.random") unsigned int
NOTHROW(LIBCCALL libc_do_random)(unsigned int *pseed) {
	unsigned int old_seed, new_seed;
	do {
		new_seed = old_seed = atomic_read(pseed);
		new_seed = (((new_seed + 7) << 1) / 3);
		new_seed ^= rand_map[(new_seed >> (new_seed & 7)) % lengthof(rand_map)];
	} while (!atomic_cmpxch_weak(pseed, old_seed, new_seed));
	return old_seed;
}

/*[[[head:libc_srand,hash:CRC-32=0x953f72d4]]]*/
INTERN ATTR_SECTION(".text.crt.random") void
NOTHROW(LIBCCALL libc_srand)(long seed)
/*[[[body:libc_srand]]]*/
{
	libc_seed = (u32)(unsigned long)seed;
}
/*[[[end:libc_srand]]]*/

/*[[[head:libc_rand,hash:CRC-32=0xcfa45bbe]]]*/
INTERN ATTR_SECTION(".text.crt.random") int
NOTHROW(LIBCCALL libc_rand)(void)
/*[[[body:libc_rand]]]*/
{
	unsigned int result;
	result = libc_do_random(&libc_seed);
#if IS_POWER_OF_TWO(RAND_MAX + 1)
	return (int)(result & RAND_MAX);
#else
	return (int)(result % (RAND_MAX + 1));
#endif
}
/*[[[end:libc_rand]]]*/

/*[[[head:libc_strfromd,hash:CRC-32=0x6b914fb5]]]*/
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_IN(3) ATTR_OUTS(1, 2) __STDC_INT32_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_strfromd)(char *__restrict buf,
                                    size_t buflen,
                                    char const *__restrict format,
                                    double fp)
/*[[[body:libc_strfromd]]]*/
/*AUTO*/{
	(void)buf;
	(void)buflen;
	(void)format;
	(void)fp;
	CRT_UNIMPLEMENTEDF("strfromd(buf: %q, buflen: %Ix, format: %q, fp: %f)", buf, buflen, format, fp); /* TODO */
	return (__STDC_INT32_AS_SIZE_T)libc_seterrno(ENOSYS);
}
/*[[[end:libc_strfromd]]]*/

/*[[[head:libc_strfromf,hash:CRC-32=0x379145b3]]]*/
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_IN(3) ATTR_OUTS(1, 2) __STDC_INT32_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_strfromf)(char *__restrict buf,
                                    size_t buflen,
                                    char const *__restrict format,
                                    float fp)
/*[[[body:libc_strfromf]]]*/
/*AUTO*/{
	(void)buf;
	(void)buflen;
	(void)format;
	(void)fp;
	CRT_UNIMPLEMENTEDF("strfromf(buf: %q, buflen: %Ix, format: %q, fp: %f)", buf, buflen, format, fp); /* TODO */
	return (__STDC_INT32_AS_SIZE_T)libc_seterrno(ENOSYS);
}
/*[[[end:libc_strfromf]]]*/

/*[[[head:libc_strfroml,hash:CRC-32=0x37aba810]]]*/
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc_strfroml, libc_strfromd);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_IN(3) ATTR_OUTS(1, 2) __STDC_INT32_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_strfroml)(char *__restrict buf,
                                    size_t buflen,
                                    char const *__restrict format,
                                    __LONGDOUBLE fp)
/*[[[body:libc_strfroml]]]*/
/*AUTO*/{
	(void)buf;
	(void)buflen;
	(void)format;
	(void)fp;
	CRT_UNIMPLEMENTEDF("strfroml(buf: %q, buflen: %Ix, format: %q, fp: %lf)", buf, buflen, format, fp); /* TODO */
	return (__STDC_INT32_AS_SIZE_T)libc_seterrno(ENOSYS);
}
#endif /* MAGIC:alias */
/*[[[end:libc_strfroml]]]*/

/*[[[head:libc_rand_r,hash:CRC-32=0x41a1acf2]]]*/
INTERN ATTR_SECTION(".text.crt.random") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_rand_r)(unsigned int *__restrict pseed)
/*[[[body:libc_rand_r]]]*/
{
	unsigned int result;
	result = libc_do_random(pseed);
#if IS_POWER_OF_TWO(RAND_MAX + 1)
	return (int)(result & RAND_MAX);
#else
	return (int)(result % (RAND_MAX + 1));
#endif
}
/*[[[end:libc_rand_r]]]*/

/*[[[impl:libc_random]]]*/
/*[[[impl:libc_srandom]]]*/
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_random, libc_rand);
DEFINE_INTERN_ALIAS(libc_srandom, libc_srand);
#else
INTERN ATTR_SECTION(".text.crt.random.random") long
NOTHROW_NCX(LIBCCALL libc_random)(void) {
#if __SIZEOF_LONG__ == __SIZEOF_INT__ * 2
	unsigned long result;
	result = (unsigned long)libc_do_random(&libc_seed) |
	         (unsigned long)libc_do_random(&libc_seed) << 31;
	return result & LONG_MAX;
#else
	return (long)libc_rand();
#endif
}
INTERN ATTR_SECTION(".text.crt.random.srandom") void
NOTHROW_NCX(LIBCCALL libc_srandom)(unsigned int seed) {
	libc_srand((long)seed);
}
#endif





/*[[[head:libc_getenv,hash:CRC-32=0x49ac0ac1]]]*/
INTERN ATTR_SECTION(".text.crt.fs.environ") WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_getenv)(char const *varname)
/*[[[body:libc_getenv]]]*/
{
	char *result, **envp;
	if unlikely(!varname)
		return NULL;
	environ_read();
	envp = environ;
	if unlikely(!envp) {
		result = NULL;
	} else {
		size_t namelen = strlen(varname);
#ifdef __OPTIMIZE_SIZE__
		for (; (result = *envp) != NULL; ++envp) {
			if (bcmp(result, varname, namelen, sizeof(char)) != 0)
				continue;
			if (result[namelen] != '=')
				continue;
			result += namelen + 1;
			break;
		}
#else /* __OPTIMIZE_SIZE__ */
		union {
			uint16_t      word;
			unsigned char chr[2];
		} pattern;

		/* Following the assumption that no environment variable string
		 * (should)  ever consist of an empty string, we can infer that
		 *
		 * all  variable strings  should consist  of at  least 2 bytes,
		 * namely the first character of the name, followed by at least
		 * the terminating NUL character.
		 *
		 * As such, when walking the table of strings, we can speed up
		 * operation via an initial dismissal check that compares  the
		 * first 2 characters from the environ-string against the  the
		 * expected pattern based on the caller's `varname'.
		 *
		 * As far as portability goes, Glibc makes the same assumption. */
		if unlikely(!namelen) {
			result = NULL;
		} else {
			pattern.word = UNALIGNED_GET16(varname);
			if unlikely(namelen == 1) {
				/* Single-character variable name -> Only need to search for
				 * that specific character,  as well as  the follow-up  '='! */
				pattern.chr[1] = '=';
				for (; (result = *envp) != NULL; ++envp) {
					if (UNALIGNED_GET16(result) != pattern.word)
						continue;
					result += 2;
					break;
				}
			} else {
				size_t tail_namelen;
				varname += 2;
				tail_namelen = namelen - 2;
				for (; (result = *envp) != NULL; ++envp) {
					if (UNALIGNED_GET16(result) != pattern.word)
						continue; /* First 2 characters don't match. */
					if (bcmp(result + 2, varname, tail_namelen, sizeof(char)) != 0)
						continue; /* Rest of string didn't match */
					if (result[namelen] != '=')
						continue; /* It's not the complete string. */
					result += namelen + 1;
					break;
				}
			}
		}
#endif /* !__OPTIMIZE_SIZE__ */
	}
	environ_endread();
	return result;
}
/*[[[end:libc_getenv]]]*/




/*[[[head:libc_setenv,hash:CRC-32=0x8c76c0c2]]]*/
INTERN ATTR_SECTION(".text.crt.fs.environ") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_setenv)(char const *varname,
                                  char const *val,
                                  int replace)
/*[[[body:libc_setenv]]]*/
{
	char **envp, **new_envp, **old_heap_envp;
	struct environ_heapstr *line;
	size_t namelen, vallen, envc, new_enva;
	if unlikely(!varname || !*varname || strchr(varname, '='))
		return libc_seterrno(EINVAL);
	/* Quick check: if we're not supported to replace variables, and if
	 *              the variable already exists, then there is no  need
	 *              to allocate a new environment line for it, only  to
	 *              free that line if it does already exist. */
	if (!replace) {
		if (getenv(varname) != NULL)
			return 0; /* Don't overwrite existing variables. */
	}
	namelen = strlen(varname);
	vallen  = strlen(val);
	line = (struct environ_heapstr *)malloc(offsetof(struct environ_heapstr, ehs_text) +
	                                        (namelen + 1 + vallen + 1) * sizeof(char));
	if unlikely(!line)
		return -1;
	memcpy(line->ehs_text, varname, namelen, sizeof(char));
	line->ehs_text[namelen] = '=';
	memcpy(line->ehs_text + namelen + 1, val, vallen, sizeof(char));
	line->ehs_text[namelen + 1 + vallen] = '\0';
	new_envp = NULL;
	new_enva = 0;
again_searchenv:
	environ_write();
	envp = environ;
	envc = 0;
	if (envp) {
		char **iter = envp, *existing_line;
		/* Search for an existing instance of `varname' */
		for (; (existing_line = *iter) != NULL; ++iter, ++envc) {
			struct environ_heapstr *existing_heapline;
			if (bcmp(existing_line, line->ehs_text, namelen + 1, sizeof(char)) != 0)
				continue;
			free(new_envp);
			if (!replace) {
				/* Even though we've already checked this above, another thread
				 * may have added  the environment variable  in the mean  time. */
				environ_endwrite();
				free(line);
				return 0;
			}
			/* Check if the existing line was already allocated on the heap. */
			existing_heapline = container_of(existing_line,
			                                 struct environ_heapstr,
			                                 ehs_text[0]);
			if (!environ_remove_heapstring_locked(existing_heapline))
				existing_heapline = NULL;
			/* Override the existing line. */
			*iter = line->ehs_text;
			line->ehs_next = libc_environ_strings;
			libc_environ_strings = line;
			environ_endwrite();
			/* Free the old line if it was heap-allocated. */
			free(existing_heapline);
			return 0;
		}
	}
	/* Using malloc_usable_size(), try to re-use an existing heap-based environ */
	if (!new_enva && (new_envp = libc_environ_heap) != NULL) {
		new_enva = malloc_usable_size(libc_environ_heap) / sizeof(char *);
		if likely(new_enva)
			--new_enva; /* Account for the trailing NULL */
	}
	/* The variable doesn't exist, yet.
	 * -> Allocate a larger environment table and add the variable to it. */
	if (new_enva != envc + 1) {
		char **new_new_envp;
		if (new_envp == libc_environ_heap) {
			if (new_enva >= envc + 1)
				goto do_fill_environ;
			new_envp = NULL;
		}
		environ_endwrite();
		new_enva     = envc + 1;
		new_new_envp = (char **)realloc(new_envp,
		                                new_enva + 1,
		                                sizeof(char *));
		if unlikely(!new_new_envp) {
			free(new_envp);
			return -1;
		}
		new_envp = new_new_envp;
		goto again_searchenv;
	}

do_fill_environ:
	/* Fill in the new environment table. */
	memmove(new_envp, envp, envc, sizeof(char *));
	new_envp[envc]     = line->ehs_text;
	new_envp[envc + 1] = NULL; /* Keep the table NULL-terminated */

	/* Add the new line as an environ heap-pointer. */
	line->ehs_next = libc_environ_strings;
	libc_environ_strings = line;

	/* Set the new environ map as the one that is active. */
	old_heap_envp     = libc_environ_heap;
	libc_environ_heap = new_envp;
	environ           = new_envp;

	environ_endwrite();

	/* Free the old environ table. */
	if (old_heap_envp != new_envp)
		free(old_heap_envp);

	return 0;
}
/*[[[end:libc_setenv]]]*/

/*[[[head:libc_unsetenv,hash:CRC-32=0x9de8ad64]]]*/
INTERN ATTR_SECTION(".text.crt.fs.environ") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_unsetenv)(char const *varname)
/*[[[body:libc_unsetenv]]]*/
{
	char **envp;
	size_t namelen;
	if unlikely(!varname || !*varname || strchr(varname, '='))
		return libc_seterrno(EINVAL);
	namelen = strlen(varname);
	environ_write();
	envp = environ;
	if (envp) {
		struct environ_heapstr *existing_heaplines = NULL;
		char *existing_line;
		/* Search for an existing instance of `varname' */
		for (; (existing_line = *envp) != NULL; ++envp) {
			char **envp_fwd;
			struct environ_heapstr *existing_heapline;
			if (bcmp(existing_line, varname, namelen, sizeof(char)) != 0 ||
			    existing_line[namelen] != '=')
				continue;
			/* Remove the line by shifting. */
			for (envp_fwd = envp;;) {
				char *next;
				next = envp_fwd[1];
				envp_fwd[0] = next;
				if (!next)
					break;
				++envp_fwd;
			}
			/* Check if the existing line was allocated on the heap. */
			existing_heapline = container_of(existing_line,
			                                 struct environ_heapstr,
			                                 ehs_text[0]);
			if (environ_remove_heapstring_locked(existing_heapline)) {
				existing_heapline->ehs_next = existing_heaplines;
				existing_heaplines = existing_heapline;
			}
			/* Continue searching for more matching lines.
			 * Since `environ' is exposed as-is to the hosted application,
			 * there is the possibility that  the user manually added  the
			 * same variable more than once... */
		}
		environ_endwrite();
		/* Free all removed lines that were allocated on the heap. */
		while (existing_heaplines) {
			struct environ_heapstr *next;
			next = existing_heaplines->ehs_next;
			free(existing_heaplines);
			existing_heaplines = next;
		}
		return 0;
	}
	environ_endwrite();
	return 0;
}
/*[[[end:libc_unsetenv]]]*/

/*[[[head:libc_clearenv,hash:CRC-32=0x7a5bba38]]]*/
INTERN ATTR_SECTION(".text.crt.fs.environ") int
NOTHROW_NCX(LIBCCALL libc_clearenv)(void)
/*[[[body:libc_clearenv]]]*/
{
	char **heap_envp;
	struct environ_heapstr *heap_strings, *next;
	environ_write();
	heap_envp            = libc_environ_heap;
	heap_strings         = libc_environ_strings;
	environ              = NULL;
	libc_environ_heap    = NULL;
	libc_environ_strings = NULL;
	environ_endwrite();
	/* Free all dynamically allocated strings, as
	 * well a dynamically allocated environ  map. */
	while (heap_strings) {
		next = heap_strings->ehs_next;
		free(heap_strings);
		heap_strings = next;
	}
	free(heap_envp);
	return 0;
}
/*[[[end:libc_clearenv]]]*/

/*[[[head:libc_putenv,hash:CRC-32=0xa3f531b4]]]*/
INTERN ATTR_SECTION(".text.crt.fs.environ") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_putenv)(char *string)
/*[[[body:libc_putenv]]]*/
{
	char *eq, **envp, **new_envp, **old_heap_envp;
	size_t namelen, envc, new_enva;
	eq = strchr(string, '=');
	if (!eq)
		return unsetenv(string);
	namelen = (size_t)(eq - string);
	if unlikely(!namelen) {
		/* Empty name is not allowed */
		return libc_seterrno(EINVAL);
	}
	new_envp = NULL;
	new_enva = 0;
again_searchenv:
	environ_write();
	envp = environ;
	envc = 0;
	if (envp) {
		char **iter = envp, *existing_line;
		/* Search for an existing instance of `varname' */
		for (; (existing_line = *iter) != NULL; ++iter, ++envc) {
			struct environ_heapstr *existing_heapline;
			if (bcmp(existing_line, string, namelen + 1, sizeof(char)) != 0)
				continue;
			/* Check if the existing line was allocated on the heap. */
			existing_heapline = container_of(existing_line,
			                                 struct environ_heapstr,
			                                 ehs_text[0]);
			if (!environ_remove_heapstring_locked(existing_heapline))
				existing_heapline = NULL;
			/* Override the existing line. */
			*iter = string;
			environ_endwrite();
			/* Free the old line if it was heap-allocated. */
			free(existing_heapline);
			free(new_envp);
			return 0;
		}
	}
	/* Using malloc_usable_size(), try to re-use an existing heap-based environ */
	if (!new_enva && (new_envp = libc_environ_heap) != NULL) {
		new_enva = malloc_usable_size(libc_environ_heap) / sizeof(char *);
		if likely(new_enva)
			--new_enva; /* Account for the trailing NULL */
	}
	/* The variable doesn't exist, yet.
	 * -> Allocate a larger environment table and add the variable to it. */
	if (new_enva != envc + 1) {
		char **new_new_envp;
		if (new_envp == libc_environ_heap) {
			if (new_enva >= envc + 1)
				goto do_fill_environ;
			new_envp = NULL;
		}
		environ_endwrite();
		new_enva = envc + 1;
		new_new_envp = (char **)realloc(new_envp,
		                                new_enva + 1,
		                                sizeof(char *));
		if unlikely(!new_new_envp) {
			free(new_envp);
			return -1;
		}
		new_envp = new_new_envp;
		goto again_searchenv;
	}

do_fill_environ:
	/* Fill in the new environment table. */
	memmove(new_envp, envp, envc, sizeof(char *));
	new_envp[envc]     = string;
	new_envp[envc + 1] = NULL; /* Keep the table NULL-terminated */

	/* Set the new environ map as the one that is active. */
	old_heap_envp     = libc_environ_heap;
	libc_environ_heap = new_envp;
	environ           = new_envp;
	environ_endwrite();

	/* Free the old environ table. */
	if (old_heap_envp != new_envp)
		free(old_heap_envp);

	return 0;
}
/*[[[end:libc_putenv]]]*/








/************************************************************************/
/* DOS ENVIRON HANDLING                                                 */
/************************************************************************/

/* Return the a prefix which is accepted by filesystem system calls under DOS
 * mode as a reference to the unix root directory. If "/" has been bound to a
 * DOS drive letter, we will use that letter, but if not, we use "\\unix\"
 *
 * Also note that the returned path is guarantied to end with a slash! */
PRIVATE ATTR_SECTION(".rodata.crt.dos.fs.environ") char const libd_dos_fsroot_default[] = "\\\\unix\\";
PRIVATE ATTR_SECTION(".bss.crt.dos.fs.environ") char const *libd_dos_fsroot = NULL;

/* Must clear `libd_dos_fsroot' in `DOS$chroot()' and `DOS$dup[2|3]()' with AT_FDROOT */
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") void
NOTHROW(CC libd_dos_fsroot_changed)(void) {
	if (libd_dos_fsroot != libd_dos_fsroot_default) {
		char *old_root = (char *)libd_dos_fsroot;
		libd_dos_fsroot = NULL;
		free(old_root);
	}
}

PRIVATE ATTR_SECTION(".text.crt.dos.fs.environ") ATTR_RETNONNULL WUNUSED char const *
NOTHROW_NCX(CC libd_get_dos_fsroot)(void) {
	if (!libd_dos_fsroot) {
		char *result;
		/* Try to print "/" as a DOS path. */
		result = libc_frealpathat(AT_FDCWD, "/", NULL, 0, AT_ALTPATH);
		if (!result || !*result) {
fallback:
			libd_dos_fsroot = libd_dos_fsroot_default;
		} else {
			char const *end = strend(result);
			if (end[-1] != '\\' && end[-1] != '/') {
				/* Must append a trailing '\\' */
				char *new_result;
				new_result = strdupf("%s\\", result);
				free(result);
				if unlikely(!new_result)
					goto fallback;
				result = new_result;
			}
			libd_dos_fsroot = result;
		}
	}
	return libd_dos_fsroot;
}

/* NOTE: This function is similar to `DOS$realpath()', but unlike that one,
 *       this one won't  expand symbolic  links, remove "."  and ".."  path
 *       segments, or fail if the named file doesn't actually exist!
 * NOTE: Only call this function when `unix_filename[0] == '/''!
 * @param: prefix: When non-NULL, a prefix to prepend before the returned string.
 * The returned path must be `free(3)'d */
PRIVATE ATTR_SECTION(".text.crt.dos.fs.environ") WUNUSED NONNULL((1, 2)) ssize_t
NOTHROW_NCX(CC libd_from_unix_filename_print)(struct format_aprintf_data *__restrict printer,
                                              char const *__restrict unix_filename,
                                              size_t unix_filename_len) {
	ssize_t result;
	char const *dos_fsroot, *end, *flush_start;
	assert(unix_filename_len >= 1);
	assert(unix_filename[0] == '/');
	++unix_filename, --unix_filename_len;
	while (unix_filename_len >= 2 &&
	       (unix_filename[0] == '.' && unix_filename[1] == '/')) {
		/* Skip "./" prefixes, else a prepended `\\unix\'-
		 * prefix would consider  it a CWD-relative  path. */
		unix_filename += 2;
		unix_filename_len -= 2;
	}

	/* Print the DOS fs-root prefix. */
	dos_fsroot = libd_get_dos_fsroot();
	result = format_aprintf_printer(printer, dos_fsroot, strlen(dos_fsroot));
	if unlikely(result < 0)
		goto done;
	flush_start = unix_filename;
	end         = unix_filename + unix_filename_len;
	while (unix_filename < end) {
		char ch = *unix_filename;
		if (ch == '/') {
			/* Replace with '\\' (not technically necessary,
			 * but  done  to get  that  uniform DOS-feeling) */
			result = format_aprintf_printer(printer, flush_start, (size_t)(unix_filename - flush_start));
			if unlikely(result < 0)
				goto done;
			result = format_aprintf_printer(printer, "\\", 1);
			if unlikely(result < 0)
				goto done;
			++unix_filename;
			flush_start = unix_filename;
		} else {
			++unix_filename;
		}
	}
	result = format_aprintf_printer(printer, flush_start, (size_t)(end - flush_start));
done:
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.dos.fs.environ") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(CC libd_from_unix_filename)(char const *unix_filename,
                                        char const *prefix,
                                        size_t prefix_len) {
	struct format_aprintf_data printer;
	format_aprintf_data_init(&printer);
	if (prefix_len) {
		if unlikely(format_aprintf_printer(&printer, prefix, prefix_len) < 0)
			goto err;
	}
	if unlikely(libd_from_unix_filename_print(&printer, unix_filename, strlen(unix_filename)) < 0)
		goto err;
	return format_aprintf_pack(&printer, NULL);
err:
	format_aprintf_data_fini(&printer);
	return NULL;
}

PRIVATE ATTR_SECTION(".text.crt.dos.fs.environ") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(CC libd_from_unix_filename_list)(char const *unix_filename_list,
                                             char const *prefix,
                                             size_t prefix_len) {
	struct format_aprintf_data printer;
	format_aprintf_data_init(&printer);
	if (prefix_len) {
		if (format_aprintf_printer(&printer, prefix, prefix_len) < 0)
			goto err;
	}
	for (;;) {
		char const *colon;
		size_t seglen;
		ssize_t error;
		colon  = strchrnul(unix_filename_list, ':');
		seglen = (size_t)(colon - unix_filename_list);
		if (seglen < 1 || unix_filename_list[0] != '/') {
			/* Keep as-is. */
			error = format_aprintf_printer(&printer, unix_filename_list, seglen);
		} else {
			/* Convert unix path to dos */
			error = libd_from_unix_filename_print(&printer, unix_filename_list, seglen);
		}
		if unlikely(error < 0)
			goto err;
		if (!*colon)
			break;
		/* Print a ';' as separator, replacing the ":" from the original string. */
		error = format_aprintf_printer(&printer, ";", 1);
		if unlikely(error < 0)
			goto err;
		unix_filename_list = colon + 1;
	}
	return format_aprintf_pack(&printer, NULL);
err:
	format_aprintf_data_fini(&printer);
	return NULL;
}


struct environ_special_struct {
	char          es_name[7]; /* Environment variable name. */
	unsigned char es_type;    /* One of `ENVIRON_SPECIAL_*' */
#define ENVIRON_SPECIAL_PATH  0 /* Singular path */
#define ENVIRON_SPECIAL_PATHS 1 /* ':'-separated path list (becomes ';'-separated under DOS) */
};

/* Cygwin converts the following paths:
 *  - $PATH              -- /usr/bin:/bin    <===>   C:\usr\bin;C:\bin
 *  - $HOME              -- /root            <===>   C:\root
 *  - $LD_LIBRARY_PATH   -- /usr/lib:/lib    <===>   C:\usr\lib;C:\lib
 *  - $TMPDIR            -- /tmp             <===>   C:\tmp
 *  - $TMP               -- /tmp             <===>   C:\tmp
 *  - $TEMP              -- /tmp             <===>   C:\tmp
 *
 * Of these, treat `$PATH' and $LD_LIBRARY_PATH as path lists,
 * but all of the other  variables are treated as  single-path
 * objects.
 *
 * Since I really don't see the point, exclude $LD_LIBRARY_PATH
 * from this list since that one's meaningless under true  DOS,
 * such that converting it would just be unnecessary overhead.
 *
 * Also note that we can't  simply use `realpath()' to have  the
 * kernel do the path conversion for us! That function will fail
 * if  the named files/folders  don't exist (as  well as do path
 * expansion based on symbolic links). We mustn't do that, so we
 * have to implement our own path conversion system!
 *
 * NOTES:
 *  - Non-absolute paths don't need to be converted ('/' is OK
 *    when used as path separator in DOS paths)
 *  - When "/" isn't bound to a DOS drive, replace the leading
 *    "/" with "\\unix\", thus turning the entire path into  a
 *    universal unix path (s.a. kernel:`path_traverse_ex()')
 *
 * However, still need to ask the kernel for the DOS name of "/"
 */
PRIVATE ATTR_SECTION(".rodata.crt.dos.fs.environ")
struct environ_special_struct const environ_special[] = {
	{ "PATH", /*  */ ENVIRON_SPECIAL_PATHS },
	{ "HOME", /*  */ ENVIRON_SPECIAL_PATH },
	{ "TMPDIR", /**/ ENVIRON_SPECIAL_PATH },
	{ "TMP", /*   */ ENVIRON_SPECIAL_PATH },
	{ "TEMP", /*  */ ENVIRON_SPECIAL_PATH },
};


#define libd_free_environ(tab) convert_freev(tab)
PRIVATE ATTR_SECTION(".text.crt.dos.fs.environ") WUNUSED char **
NOTHROW_NCX(CC libd_alloc_environ)(char **unix_environ) {
	char **result;
	size_t i, count;
	if (!unix_environ)
		return NULL;
	for (count = 0; unix_environ[count]; ++count)
		;
	result = (char **)malloc(count + 1, sizeof(char *));
	if unlikely(!result)
		return NULL;
	for (i = 0; i < count; ++i) {
		char *str = unix_environ[i];
		char *eq;
		if (!libd_have_dosfs())
			goto fallback;
		eq = strchr(str, '=');
		if (eq) {
			size_t i, name_length = (size_t)(eq - str);
			if (name_length > COMPILER_STRLEN(environ_special[0].es_name))
				goto fallback;
			/* Check for special variable names. */
			for (i = 0;; ++i) {
				if (i >= lengthof(environ_special))
					goto fallback;
				if (environ_special[i].es_name[name_length] != '\0')
					continue;
				if (bcmp(str, environ_special[i].es_name, name_length, sizeof(char)) != 0)
					continue;
				switch (environ_special[i].es_type) {
				case ENVIRON_SPECIAL_PATH:
					str = libd_from_unix_filename(eq + 1, str, name_length + 1);
					break;
				case ENVIRON_SPECIAL_PATHS:
					str = libd_from_unix_filename_list(eq + 1, str, name_length + 1);
					break;
				default: __builtin_unreachable();
				}
				break;
			}
		} else {
fallback:
			str = strdup(str);
		}
		if (!str)
			goto err;
		result[i] = str;
	}
	result[i] = NULL;
	return result;
err:
	while (i) {
		--i;
		free(result[i]);
	}
	free(result);
	return NULL;
}



/* DOS single-byte environment table. */
#undef DOS$environ
#undef DOS$_environ
#undef DOS$__environ
DEFINE_PUBLIC_ALIAS(DOS$__p__environ, libd_p_environ);
DEFINE_PUBLIC_IDATA(DOS$environ, libd_p_environ, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(DOS$_environ, libd_p_environ, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(DOS$__environ, libd_p_environ, __SIZEOF_POINTER__);

/* Don't need to use dlsym("DOS$environ") because PE doesn't have copy relocations */
#define DOS$environ (*libd_p_environ())

/* Internal storage for `DOS$environ' */
PRIVATE ATTR_SECTION(".bss.crt.dos.fs.environ") char **libd_environ = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.fs.environ")
struct atomic_once libd_environ_initialized = ATOMIC_ONCE_INIT;

/* Lazy initializer for `DOS$environ' */
ATTR_SECTION(".text.crt.dos.fs.environ")
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED char ***
NOTHROW(LIBDCALL libd_p_environ)(void) {
	/* Allocate the environment table on first access. */
	ATOMIC_ONCE_RUN(&libd_environ_initialized, {
		libd_environ = libd_alloc_environ(environ);
	});
	return &libd_environ;
}

/*[[[head:libd_getenv,hash:CRC-32=0xb1cc890b]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.environ") WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBDCALL libd_getenv)(char const *varname)
/*[[[body:libd_getenv]]]*/
{
	char **dos_environ;
	if (!libd_have_dosfs())
		return libc_getenv(varname);
	if unlikely(!varname)
		return NULL;
	if (libd_environ != NULL &&
	    (dos_environ = DOS$environ) != NULL) {
		/* Search through our c32-environment cache. */
		size_t i, len;
		char *envstr;
search_dos_environment:
		len = strlen(varname);
		for (i = 0; (envstr = dos_environ[i]) != NULL; ++i) {
			if (bcmp(envstr, varname, len, sizeof(char)) != 0)
				continue;
			if (envstr[len] != '=')
				continue;
			return envstr + len + 1;
		}
		return NULL;
	}

	/* Check for special variables. If the one being requested is one such
	 * special variable, then allocate the  DOS environment and search  it
	 * for said variable. */
	{
		size_t i;
		for (i = 0; i < lengthof(environ_special); ++i) {
			if (strcmp(environ_special[i].es_name, varname) != 0)
				continue;
			/* Yup: it's one of the special variables! */
			dos_environ = DOS$environ;
			if unlikely(!dos_environ)
				return NULL; /* No dos environ */
			goto search_dos_environment;
		}
	}

	/* Fallback: for regular, old environment variables, just scan the unix environ! */
	return libc_getenv(varname);
}
/*[[[end:libd_getenv]]]*/


struct libd_to_unix_cache {
	char *d2uc_drives[('Z' - 'A') + 1]; /* [0..1][owned] Unix paths for DOS drives. */
	int   d2uc_drive;                   /* Current drive letter (or `0' if unknown) */
};
#define libd_to_unix_cache_init(self) bzero(self, sizeof(*(self)))
PRIVATE ATTR_SECTION(".text.crt.dos.fs.environ") NONNULL((1)) void
NOTHROW(CC libd_to_unix_cache_fini)(struct libd_to_unix_cache *__restrict self) {
	size_t i;
	for (i = 0; i < lengthof(self->d2uc_drives); ++i)
		free(self->d2uc_drives[i]);
}

PRIVATE ATTR_SECTION(".text.crt.dos.fs.environ") char *
NOTHROW(CC libd_to_unix_cache_drivepath)(struct libd_to_unix_cache *self,
                                         char drive_letter) {
	char *result;
	char buf[4];
	drive_letter = toupper(drive_letter);
	assert(drive_letter >= 'A' && drive_letter <= 'Z');
	if (self) {
		result = self->d2uc_drives[drive_letter - 'A'];
		if (result)
			return result;
	}
	sprintf(buf, "%c:\\", drive_letter);
	result = libc_frealpathat(AT_FDCWD, buf, NULL, 0, AT_DOSPATH | AT_ALTPATH);
	if (self)
		self->d2uc_drives[drive_letter - 'A'] = result;
	return result;
}


PRIVATE ATTR_SECTION(".text.crt.dos.fs.environ") WUNUSED NONNULL((1, 2)) ssize_t
NOTHROW_NCX(CC libd_to_unix_filename_print)(struct format_aprintf_data *__restrict printer,
                                            char const *__restrict dos_filename,
                                            size_t dos_filename_len,
                                            struct libd_to_unix_cache *cache) {
	char const *flush_start, *end;
	ssize_t temp;
	if (!dos_filename_len)
		return 0;
	if (dos_filename[0] == '/' || dos_filename[0] == '\\') {
		/* Path relative to root of current drive, or "\\unix\"-prefix. */
		if (dos_filename_len >= COMPILER_STRLEN("\\\\unix\\") &&
		    dos_filename[0] == '\\' && dos_filename[1] == '\\' &&
		    memcasecmp(dos_filename + 2, "unix", 4 * sizeof(char)) == 0 &&
		    dos_filename[6] == '\\') {
			dos_filename += COMPILER_STRLEN("\\\\unix\\");
			dos_filename_len -= COMPILER_STRLEN("\\\\unix\\");
		} else {
			int drive = 0;
			char *path;
			size_t path_len;
			if (cache)
				drive = cache->d2uc_drive;
			if (drive == 0) {
				drive = _getdrive();
				if (drive < 0)
					goto err;
				drive += 'A';
				if (cache)
					cache->d2uc_drive = drive;
			}
			path = libd_to_unix_cache_drivepath(cache, drive);
			if (!path)
				goto err;
			path_len = strlen(path);
			while (path_len && path[path_len - 1] == '/')
				--path_len;
			temp = format_aprintf_printer(printer, path, path_len);
			if (!cache)
				free(path);
			if unlikely(temp < 0)
				goto err;
			++dos_filename;
			--dos_filename_len;
		}
print_slash_before_prefix:
		temp = format_aprintf_printer(printer, "/", 1);
		if unlikely(temp < 0)
			goto err;
	} else if (dos_filename_len >= 2 &&
	           dos_filename[1] == ':' &&
	           isalpha(dos_filename[0])) {
		char drive = dos_filename[0];
		bool must_free_path;
		char *path;
		size_t path_len;
		if (dos_filename_len >= 3 && (dos_filename[2] == '/' ||
		                              dos_filename[2] == '\\')) {
			/* Relative to root of drive */
			path = libd_to_unix_cache_drivepath(cache, drive);
			must_free_path = cache == NULL;
			dos_filename += 3;
			dos_filename_len -= 3;
		} else {
			/* Relative to cwd of drive */
			char buf[3] = { drive, ':', '\0' };
			path = libc_frealpathat(AT_FDCWD, buf, NULL, 0, AT_DOSPATH | AT_ALTPATH);
			must_free_path = true;
			dos_filename += 2;
			dos_filename_len -= 2;
		}
		if unlikely(!path)
			goto err;
		path_len = strlen(path);
		while (path_len && path[path_len - 1] == '/')
			--path_len;
		temp = format_aprintf_printer(printer, path, path_len);
		if (must_free_path)
			free(path);
		goto print_slash_before_prefix;
	} else {
		/* Relative path (no prefix needed) */
	}

	/* Convert the relative path portion. */
	flush_start = dos_filename;
	end         = dos_filename + dos_filename_len;
	while (dos_filename < end) {
		char ch = *dos_filename;
		if (ch == '\\') {
			if (format_aprintf_printer(printer, flush_start, (size_t)(dos_filename - flush_start)) < 0)
				goto err;
			if (format_aprintf_printer(printer, "/", 1) < 0)
				goto err;
			++dos_filename;
			flush_start = dos_filename;
		} else {
			++dos_filename;
		}
	}
	return format_aprintf_printer(printer, flush_start, (size_t)(end - flush_start));
err:
	return -1;
}

PRIVATE ATTR_SECTION(".text.crt.dos.fs.environ") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(CC libd_to_unix_filename)(char const *dos_filename,
                                      struct libd_to_unix_cache *cache) {
	struct format_aprintf_data printer;
	format_aprintf_data_init(&printer);
	if unlikely(libd_to_unix_filename_print(&printer, dos_filename, strlen(dos_filename), cache) < 0)
		goto err;
	return format_aprintf_pack(&printer, NULL);
err:
	format_aprintf_data_fini(&printer);
	return NULL;
}

PRIVATE ATTR_SECTION(".text.crt.dos.fs.environ") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(CC libd_to_unix_filename_list)(char const *dos_filename_list,
                                           struct libd_to_unix_cache *cache) {
	struct format_aprintf_data printer;
	format_aprintf_data_init(&printer);
	for (;;) {
		char const *semicolon;
		size_t seglen;
		ssize_t error;
		semicolon = strchrnul(dos_filename_list, ';');
		seglen    = (size_t)(semicolon - dos_filename_list);
		/* Convert dos path to unix */
		error = libd_to_unix_filename_print(&printer, dos_filename_list, seglen, cache);
		if unlikely(error < 0)
			goto err;
		if (!*semicolon)
			break;
		/* Print a ':' as separator, replacing the ";" from the original string. */
		error = format_aprintf_printer(&printer, ":", 1);
		if unlikely(error < 0)
			goto err;
		dos_filename_list = semicolon + 1;
	}
	return format_aprintf_pack(&printer, NULL);
err:
	format_aprintf_data_fini(&printer);
	return NULL;
}


/*[[[head:libd_setenv,hash:CRC-32=0xe5c6ff51]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.environ") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBDCALL libd_setenv)(char const *varname,
                                  char const *val,
                                  int replace)
/*[[[body:libd_setenv]]]*/
{
	size_t i;
	if (!libd_have_dosfs())
		return libc_setenv(varname, val, replace);

	if (!replace) {
		if (libc_getenv(varname) != NULL)
			return 0; /* Don't overwrite existing variables. */
	}

	/* Update the dos environment table (if it was allocated). */
	if (libd_environ != NULL) {
		/* Update the variable within the DOS$environ table. */
		char ***p_dos_environ = &DOS$environ;
		char **dos_environ = *p_dos_environ;
		if (dos_environ != NULL) {
			char **new_environ;
			size_t j;
			size_t namelen = strlen(varname);
			char *newstr   = strdupf("%s=%s", varname, val);
			if (!newstr)
				return -1;
			for (j = 0; dos_environ[j]; ++j) {
				char *str = dos_environ[j];
				if (bcmp(str, varname, namelen, sizeof(char)) != 0)
					continue;
				if (str[namelen] != '=')
					continue;
				/* Override an existing variable. */
				dos_environ[j] = newstr;
				free(str);
				goto did_update_dos_environ;
			}
			/* Must append `newstr' to `DOS$environ */
			new_environ = (char **)realloc(dos_environ, j + 2, sizeof(char *));
			if unlikely(!new_environ) {
				free(newstr);
				return -1;
			}
			new_environ[j + 0] = newstr;
			new_environ[j + 1] = NULL;
			*p_dos_environ     = new_environ;
		}
	}
did_update_dos_environ:

	/* Check for special variables. */
	for (i = 0; i < lengthof(environ_special); ++i) {
		int result;
		char *unixval;
		if (strcmp(environ_special[i].es_name, varname) != 0)
			continue;

		/* Yup: it's one of the special variables!
		 * In this case, we must convert `val' into unix format. */
		switch (environ_special[i].es_type) {
		case ENVIRON_SPECIAL_PATH:
			unixval = libd_to_unix_filename(val, NULL);
			break;
		case ENVIRON_SPECIAL_PATHS: {
			struct libd_to_unix_cache cache;
			libd_to_unix_cache_init(&cache);
			unixval = libd_to_unix_filename_list(val, &cache);
			libd_to_unix_cache_fini(&cache);
		}	break;
		default: __builtin_unreachable();
		}
		if unlikely(!unixval)
			return -1;
		result = libc_setenv(varname, unixval, 1);
		free(unixval);
		return result;
	}

	/* Fallback: normal environment variables can just be set as-is under unix. */
	return libc_setenv(varname, val, 1);
}
/*[[[end:libd_setenv]]]*/

/************************************************************************/



/*[[[head:libd_unsetenv,hash:CRC-32=0xc566c44e]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.environ") ATTR_IN(1) int
NOTHROW_NCX(LIBDCALL libd_unsetenv)(char const *varname)
/*[[[body:libd_unsetenv]]]*/
{
	int result;
	result = libc_unsetenv(varname);

	/* On success, also  try to  remove the string  from the  DOS
	 * environment table (in case said table has been allocated). */
	if (result == 0 && libd_environ != NULL && libd_have_dosfs()) {
		char **tab, ***p_dos_environ = &DOS$environ;
		if ((tab = *p_dos_environ) != NULL) {
			char *str;
			size_t i, len = strlen(varname);
			for (i = 0; (str = tab[i]) != NULL; ++i) {
				if (bcmp(str, varname, len, sizeof(char)) != 0)
					continue;
				if (str[len] != '=')
					continue;
				/* Remove `str' from the DOS environment table. */
				for (len = i + 1; tab[len]; ++len)
					;
				memmovedown(&tab[i], &tab[i + 1], len - i, sizeof(char *));
				--len; /* Decrement `len' after, so `memmovedown' includes the trailing `NULL' */
				tab = (char **)realloc(tab, len, sizeof(char *));
				if likely(tab)
					*p_dos_environ = tab;
				free(str);
				break;
			}
		}
	}
	return result;
}
/*[[[end:libd_unsetenv]]]*/






/************************************************************************/
/* Wide-character environment tables                                    */
/************************************************************************/
#undef DOS$_wenviron
#undef _wenviron
PRIVATE ATTR_SECTION(".bss.crt.dos.wchar.fs.environ") char16_t **libd_wenviron = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.wchar.fs.environ") char32_t **libc_wenviron = NULL;
DEFINE_PUBLIC_IDATA(DOS$_wenviron, libd___p__wenviron, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(_wenviron, libc___p__wenviron, __SIZEOF_POINTER__);
#define DOS$_wenviron libd_wenviron
#define _wenviron     GET_NOREL_GLOBAL(_wenviron)

#define libd_alloc_wenviron()   convert_mbstoc16v(*libd_p_environ())
#define libd_free_wenviron(tab) convert_freev(tab)

#define libc_alloc_wenviron()   convert_mbstoc32v(environ)
#define libc_free_wenviron(tab) convert_freev(tab)

PRIVATE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") int
NOTHROW_NCX(LIBKCALL libd_update_wenviron)(void) {
	char16_t ***_pwenviron, **oldtab, **newtab;
	newtab = libd_alloc_wenviron();
	if unlikely(newtab == NULL)
		return -1;
	_pwenviron  = &DOS$_wenviron;
	oldtab      = *_pwenviron;
	*_pwenviron = newtab;
	libd_free_wenviron(oldtab);
	return 0;
}

PRIVATE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") int
NOTHROW_NCX(LIBKCALL libc_update_wenviron)(void) {
	char32_t ***_pwenviron, **oldtab, **newtab;
	newtab = libc_alloc_wenviron();
	if unlikely(newtab == NULL)
		return -1;
	_pwenviron  = &_wenviron;
	oldtab      = *_pwenviron;
	*_pwenviron = newtab;
	libc_free_wenviron(oldtab);
	return 0;
}

/*[[[head:libd___p__wenviron,hash:CRC-32=0x87c29721]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***
NOTHROW(LIBDCALL libd___p__wenviron)(void)
/*[[[body:libd___p__wenviron]]]*/
{
	if (libd_wenviron == NULL)
		libd_wenviron = libd_alloc_wenviron();
	return &libd_wenviron;
}
/*[[[end:libd___p__wenviron]]]*/

/*[[[head:libc___p__wenviron,hash:CRC-32=0x41ec1e33]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***
NOTHROW(LIBKCALL libc___p__wenviron)(void)
/*[[[body:libc___p__wenviron]]]*/
{
	if (libc_wenviron == NULL)
		libc_wenviron = libc_alloc_wenviron();
	return &libc_wenviron;
}
/*[[[end:libc___p__wenviron]]]*/


/*[[[head:libc__wgetenv,hash:CRC-32=0xa4942c43]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") WUNUSED ATTR_IN(1) char32_t *
NOTHROW_NCX(LIBKCALL libc__wgetenv)(char32_t const *varname)
/*[[[body:libc__wgetenv]]]*/
{
	static ATTR_SECTION(".bss.crt.dos.wchar.fs.environ") char32_t *last_c32getenv = NULL;
	char *utf8_varname, *utf8_varval;
	char32_t *c32_varval, **wenviron;
	if ((libc_wenviron != NULL) && (wenviron = _wenviron) != NULL) {
		/* Search through our c32-environment cache. */
		size_t i, len = c32len(varname);
		char32_t *envstr;
		for (i = 0; (envstr = wenviron[i]) != NULL; ++i) {
			if (c32memcmp(envstr, varname, len) != 0)
				continue;
			if (envstr[len] != '=')
				continue;
			return envstr + len + 1;
		}
		return NULL;
	}
	utf8_varname = convert_c32tombs(varname);
	if (!utf8_varname)
		return NULL;
	utf8_varval = libc_getenv(utf8_varname);
	free(utf8_varname);
	if (!utf8_varval)
		return NULL;
	c32_varval = convert_mbstoc32(utf8_varval);
	if (c32_varval) {
		free(last_c32getenv);
		last_c32getenv = c32_varval;
	}
	return c32_varval;
}
/*[[[end:libc__wgetenv]]]*/

/*[[[head:libd__wgetenv,hash:CRC-32=0xe2551d54]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") WUNUSED ATTR_IN(1) char16_t *
NOTHROW_NCX(LIBDCALL libd__wgetenv)(char16_t const *varname)
/*[[[body:libd__wgetenv]]]*/
{
	static ATTR_SECTION(".bss.crt.dos.wchar.fs.environ") char16_t *last_c16getenv = NULL;
	char *utf8_varname, *utf8_varval;
	char16_t *c16_varval;
	if (libd_wenviron != NULL) {
		/* Search through our c32-environment cache. */
		size_t i, len = c16len(varname);
		char16_t *envstr;
		for (i = 0; (envstr = libd_wenviron[i]) != NULL; ++i) {
			if (c16memcmp(envstr, varname, len) != 0)
				continue;
			if (envstr[len] != '=')
				continue;
			return envstr + len + 1;
		}
		return NULL;
	}
	utf8_varname = convert_c16tombs(varname);
	if (!utf8_varname)
		return NULL;
	utf8_varval = libd_getenv(utf8_varname);
	free(utf8_varname);
	if (!utf8_varval)
		return NULL;
	c16_varval = convert_mbstoc16(utf8_varval);
	if (c16_varval) {
		free(last_c16getenv);
		last_c16getenv = c16_varval;
	}
	return c16_varval;
}
/*[[[end:libd__wgetenv]]]*/

/*[[[head:libd_putenv,hash:CRC-32=0x5120d37f]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.environ") ATTR_INOUT(1) int
NOTHROW_NCX(LIBDCALL libd_putenv)(char *string)
/*[[[body:libd_putenv]]]*/
{
	int result;
	char *eq, *base;
	eq = strchr(string, '=');
	if (!eq)
		return libd_unsetenv(string);
	base = mstrndupa(string, (size_t)(eq - string));
	if (!base)
		return -1;
	++eq;
	result = libd_setenv(base, eq, 1);
	freea(base);
	return result;
}
/*[[[end:libd_putenv]]]*/

/*[[[head:libd__wputenv,hash:CRC-32=0xab764012]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_INOUT(1) int
NOTHROW_NCX(LIBDCALL libd__wputenv)(char16_t *string)
/*[[[body:libd__wputenv]]]*/
{
	int result;
	char *utf8 = convert_c16tombs(string);
	if (!utf8)
		return -1;
	result = libd_putenv(utf8);
	free(utf8);

	/* If it's being used, update the global utf-16 `_wenviron' array. */
	if (result == 0 && libd_wenviron != NULL)
		result = libd_update_wenviron();
	return result;
}
/*[[[end:libd__wputenv]]]*/

/*[[[head:libc__wputenv,hash:CRC-32=0x10840d12]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_INOUT(1) int
NOTHROW_NCX(LIBKCALL libc__wputenv)(char32_t *string)
/*[[[body:libc__wputenv]]]*/
{
	int result;
	char *eq;
	char *utf8 = convert_c32tombs(string);
	if (!utf8)
		return -1;
	eq = strchr(utf8, '=');
	if (!eq) {
		result = libc_unsetenv(utf8);
	} else {
		*eq++ = '\0';
		result = libc_setenv(utf8, eq, 1);
	}
	free(utf8);

	/* If it's being used, update the global utf-32 `_wenviron' array. */
	if (result == 0 && libc_wenviron != NULL)
		result = libc_update_wenviron();
	return result;
}
/*[[[end:libc__wputenv]]]*/

/*[[[head:libd__wputenv_s,hash:CRC-32=0x49f754ec]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") errno_t
NOTHROW_NCX(LIBDCALL libd__wputenv_s)(char16_t const *varname,
                                      char16_t const *val)
/*[[[body:libd__wputenv_s]]]*/
{
	errno_t result;
	char *utf8_varname;
	char *utf8_val;
	utf8_varname = convert_c16tombs(varname);
	if (!utf8_varname)
		goto err;
	utf8_val = convert_c16tombs(val);
	if (!utf8_val)
		goto err_varname;
	result = libd__putenv_s(utf8_varname, utf8_val);
	free(utf8_val);
	free(utf8_varname);

	/* If it's being used, update the global utf-32 `_wenviron' array. */
	if (result == 0 && libd_wenviron != NULL) {
		if (libd_update_wenviron())
			result = libc_geterrno();
	}
	return result;
/*err_val:
	free(utf8_val);*/
err_varname:
	free(utf8_varname);
err:
	return libd_geterrno();
}
/*[[[end:libd__wputenv_s]]]*/

/*[[[head:libc__wputenv_s,hash:CRC-32=0xcfcd97a5]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") errno_t
NOTHROW_NCX(LIBKCALL libc__wputenv_s)(char32_t const *varname,
                                      char32_t const *val)
/*[[[body:libc__wputenv_s]]]*/
{
	errno_t result;
	char *utf8_varname;
	char *utf8_val;
	utf8_varname = convert_c32tombs(varname);
	if (!utf8_varname)
		goto err;
	utf8_val = convert_c32tombs(val);
	if (!utf8_val)
		goto err_varname;
	result = libc__putenv_s(utf8_varname, utf8_val);
	free(utf8_val);
	free(utf8_varname);

	/* If it's being used, update the global utf-32 `_wenviron' array. */
	if (result == 0 && libc_wenviron != NULL) {
		if (libc_update_wenviron())
			result = libc_geterrno();
	}
	return result;
/*err_val:
	free(utf8_val);*/
err_varname:
	free(utf8_varname);
err:
	return libc_geterrno();
}
/*[[[end:libc__wputenv_s]]]*/






/*[[[head:libc__searchenv_s,hash:CRC-32=0xebac777]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4) errno_t
NOTHROW_RPC(LIBCCALL libc__searchenv_s)(char const *file,
                                        char const *envvar,
                                        char *__restrict resultpath,
                                        size_t resultpath_len)
/*[[[body:libc__searchenv_s]]]*/
/*AUTO*/{
	(void)file;
	(void)envvar;
	(void)resultpath;
	(void)resultpath_len;
	CRT_UNIMPLEMENTEDF("_searchenv_s(file: %q, envvar: %q, resultpath: %q, resultpath_len: %Ix)", file, envvar, resultpath, resultpath_len); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__searchenv_s]]]*/

struct atexit_callback {
	void (LIBCCALL *ac_func)(int status, void *arg); /* [1..1] The function to-be invoked. */
	void           *ac_arg;                          /* Argument for `ac_func'. */
};

struct atexit_vector_struct {
	struct atomic_rwlock    av_lock; /* Lock for this vector. */
	size_t                  av_size; /* [lock(av_lock)] Number of registered functions. */
	struct atexit_callback *av_vect; /* [0..av_size][owned][lock(av_lock)] Array of functions. */
	int                     av_stat; /* Process exit status. */
};

PRIVATE ATTR_SECTION(".bss.crt.application.exit")
struct atexit_vector_struct atexit_vector = {
	.av_lock = ATOMIC_RWLOCK_INIT,
	.av_size = 0,
	.av_vect = NULL,
	.av_stat = 0
};


INTERN ATTR_SECTION(".text.crt.application.exit")
void LIBCCALL libc_run_atexit(int status) {
	size_t length;
	atomic_write(&atexit_vector.av_stat, status);
	atomic_rwlock_read(&atexit_vector.av_lock);
	length = atexit_vector.av_size;
	atexit_vector.av_size = 0;
	while (length) {
		struct atexit_callback *ent;
		--length;
		ent = &atexit_vector.av_vect[length];
		(*ent->ac_func)(status, ent->ac_arg);
	}
}

/*[[[head:libc_on_exit,hash:CRC-32=0x28daac51]]]*/
INTERN ATTR_SECTION(".text.crt.sched.process") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_on_exit)(void (LIBCCALL *func)(int status, void *arg),
                                   void *arg)
/*[[[body:libc_on_exit]]]*/
{
	struct atexit_callback *new_vector;
	while (!atomic_rwlock_trywrite(&atexit_vector.av_lock)) {
		if (atomic_rwlock_reading(&atexit_vector.av_lock)) { /* TODO: FIXME: This also triggers if another thread is holding a write-lock! */
			/* atexit functions have already been invoked. -> Do so ourself as well. */
			(*func)(atexit_vector.av_stat, arg);
			return 0;
		}
		sched_yield();
	}
	new_vector = (struct atexit_callback *)realloc(atexit_vector.av_vect,
	                                               atexit_vector.av_size + 1,
	                                               sizeof(struct atexit_callback));
	if unlikely(!new_vector) {
		atomic_rwlock_endwrite(&atexit_vector.av_lock);
		return -1;
	}
	atexit_vector.av_vect = new_vector;
	new_vector += atexit_vector.av_size++;
	new_vector->ac_func = func;
	new_vector->ac_arg  = arg;
	atomic_rwlock_endwrite(&atexit_vector.av_lock);
	return 0;
}
/*[[[end:libc_on_exit]]]*/

#ifndef __LIBCCALL_IS_LIBDCALL
struct libd_on_exit_cookie {
	void (LIBDCALL *func)(int status, void *arg);
	void *arg;
};
PRIVATE ATTR_SECTION(".text.crt.dos.sched.process") void LIBCCALL
libd_on_exit_wrapper(int status, void *arg) {
	struct libd_on_exit_cookie cookie;
	cookie = *(struct libd_on_exit_cookie *)arg;
	free(arg);
	(*cookie.func)(status, cookie.arg);
}
#endif /* __LIBCCALL_IS_LIBDCALL */

/*[[[head:libd_on_exit,hash:CRC-32=0xf5c79fa8]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.sched.process") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_on_exit)(void (LIBDCALL *func)(int status, void *arg),
                                   void *arg)
/*[[[body:libd_on_exit]]]*/
{
	int result;
	struct libd_on_exit_cookie *cookie;
	cookie = (struct libd_on_exit_cookie *)malloc(sizeof(struct libd_on_exit_cookie));
	if unlikely(!cookie)
		return -1;
	cookie->func = func;
	cookie->arg = arg;
	result = libc_on_exit(&libd_on_exit_wrapper, cookie);
	if unlikely(result != 0)
		free(cookie);
	return result;
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_on_exit]]]*/


PRIVATE ATTR_SECTION(".text.crt.sched.process") void
NOTHROW_NCX(LIBCCALL libc_atexit_wrapper)(int status, void *arg) {
	(void)status;
	(*(void (LIBCCALL *)(void))arg)();
}

/*[[[head:libc_atexit,hash:CRC-32=0xd7fad4d9]]]*/
INTERN ATTR_SECTION(".text.crt.sched.process") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_atexit)(void (LIBCCALL *func)(void))
/*[[[body:libc_atexit]]]*/
{
	/* TODO: Instead of this right here, we should register `func'
	 *       for  invocation  when `dlgethandle(func)'  is closed!
	 *       s.a. `DLAUXCTRL_ADD_FINALIZER' */
	return on_exit(&libc_atexit_wrapper, (void *)func);
}
/*[[[end:libc_atexit]]]*/



struct at_quick_exit_callback {
	void (LIBCCALL *aqc_func)(void); /* [1..1] The function to-be invoked. */
};

struct at_quick_exit_vector_struct {
	size_t                         aqv_size; /* [lock(atexit_vector.av_lock)] Number of registered functions. */
	struct at_quick_exit_callback *aqv_vect; /* [0..av_size][owned][lock(atexit_vector.av_lock)] Array of functions. */
};

PRIVATE ATTR_SECTION(".bss.crt.application.exit")
struct at_quick_exit_vector_struct at_quick_exit_vector = {
	/* .av_size = */ 0,
	/* .av_vect = */ NULL
};

INTERN ATTR_SECTION(".text.crt.application.exit")
void LIBCCALL libc_run_at_quick_exit(int status) {
	size_t length;
	atomic_write(&atexit_vector.av_stat, status);
	atomic_rwlock_read(&atexit_vector.av_lock);
	length = at_quick_exit_vector.aqv_size;
	at_quick_exit_vector.aqv_size = 0;
	while (length) {
		struct at_quick_exit_callback *ent;
		--length;
		ent = &at_quick_exit_vector.aqv_vect[length];
		(*ent->aqc_func)();
	}
}

/*[[[head:libc_at_quick_exit,hash:CRC-32=0xb1cd172a]]]*/
INTERN ATTR_SECTION(".text.crt.sched.process") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_at_quick_exit)(void (LIBCCALL *func)(void))
/*[[[body:libc_at_quick_exit]]]*/
{
	struct at_quick_exit_callback *new_vector;
	while (!atomic_rwlock_trywrite(&atexit_vector.av_lock)) {
		if (atomic_rwlock_reading(&atexit_vector.av_lock)) { /* TODO: FIXME: This also triggers if another thread is holding a write-lock! */
			/* atexit functions have already been invoked. -> Do so ourself as well. */
			(*func)();
			return 0;
		}
		sched_yield();
	}
	new_vector = (struct at_quick_exit_callback *)realloc(at_quick_exit_vector.aqv_vect,
	                                                      at_quick_exit_vector.aqv_size + 1,
	                                                      sizeof(struct at_quick_exit_callback));
	if unlikely(!new_vector) {
		atomic_rwlock_endwrite(&atexit_vector.av_lock);
		return -1;
	}
	at_quick_exit_vector.aqv_vect = new_vector;
	new_vector += at_quick_exit_vector.aqv_size++;
	new_vector->aqc_func = func;
	atomic_rwlock_endwrite(&atexit_vector.av_lock);
	return 0;
}
/*[[[end:libc_at_quick_exit]]]*/

/*[[[head:libc_exit,hash:CRC-32=0x7f9a0666]]]*/
INTERN ATTR_SECTION(".text.crt.application.exit") ATTR_NORETURN void
(LIBCCALL libc_exit)(int status)
/*[[[body:libc_exit]]]*/
{
	/* Finalize TLS objects for the calling thread (c++11-specific) */
	dlauxctrl(NULL, DLAUXCTRL_RUNTLSFINI);

	/* Run functions registered with `atexit()' or `on_exit()'. */
	libc_run_atexit(status);

	/* Run library finalizers (NOTE: This will also call back to invoke
	 * `libc_fini()' because libc  is compiled with  `-fini=libc_fini') */
	dlauxctrl(NULL, DLAUXCTRL_RUNFINI);
	_Exit(status);
}
/*[[[end:libc_exit]]]*/

/*[[[head:libc_quick_exit,hash:CRC-32=0x64157d92]]]*/
INTERN ATTR_SECTION(".text.crt.sched.process") ATTR_NORETURN void
(LIBCCALL libc_quick_exit)(int status)
/*[[[body:libc_quick_exit]]]*/
{
	/* Run at_quick_exit() functions */
	libc_run_at_quick_exit(status);
	/* Don't run library finalizers,  but still run libc_fini()  to
	 * at least  flush open  file streams,  ensuring that  no  open
	 * file  is left in an undefined state, and any potential error
	 * message written prior to quick_exit() being called will also
	 * be printed on-screen. */
	libc_fini();
	_Exit(status);
}
/*[[[end:libc_quick_exit]]]*/

/*[[[head:libc__Exit,hash:CRC-32=0xc6ad99bc]]]*/
INTERN ATTR_SECTION(".text.crt.application.exit") ATTR_NORETURN void
(LIBCCALL libc__Exit)(int status)
/*[[[body:libc__Exit]]]*/
{
	sys_exit_group((syscall_ulong_t)(unsigned int)status);
}
/*[[[end:libc__Exit]]]*/

PRIVATE ATTR_SECTION(".text.crt.dos.sched.process")
void LIBCCALL libc_onexit_wrapper(void *arg) {
	(*(onexit_t)arg)();
}

/*[[[head:libc_onexit,hash:CRC-32=0x48d44540]]]*/
INTERN ATTR_SECTION(".text.crt.dos.sched.process") onexit_t
NOTHROW_NCX(LIBCCALL libc_onexit)(onexit_t func)
/*[[[body:libc_onexit]]]*/
{
	int error;
	error = libc___cxa_atexit(&libc_onexit_wrapper,
	                          (void *)func,
	                          __builtin_return_address(0));
	return error ? NULL : func;
}
/*[[[end:libc_onexit]]]*/

/*[[[head:libc_drand48_r,hash:CRC-32=0x1d0c3083]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_drand48_r)(struct drand48_data *__restrict buffer,
                                     double *__restrict result)
/*[[[body:libc_drand48_r]]]*/
/*AUTO*/{
	(void)buffer;
	(void)result;
	CRT_UNIMPLEMENTEDF("drand48_r(buffer: %p, result: %p)", buffer, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_drand48_r]]]*/

/*[[[head:libc_erand48_r,hash:CRC-32=0x7b00694f]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_erand48_r)(unsigned short xsubi[3],
                                     struct drand48_data *__restrict buffer,
                                     double *__restrict result)
/*[[[body:libc_erand48_r]]]*/
/*AUTO*/{
	(void)xsubi;
	(void)buffer;
	(void)result;
	CRT_UNIMPLEMENTEDF("erand48_r(xsubi: %p, buffer: %p, result: %p)", xsubi, buffer, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_erand48_r]]]*/

/*[[[head:libc_lrand48_r,hash:CRC-32=0x5645a408]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_lrand48_r)(struct drand48_data *__restrict buffer,
                                     long *__restrict result)
/*[[[body:libc_lrand48_r]]]*/
/*AUTO*/{
	(void)buffer;
	(void)result;
	CRT_UNIMPLEMENTEDF("lrand48_r(buffer: %p, result: %p)", buffer, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_lrand48_r]]]*/

/*[[[head:libc_nrand48_r,hash:CRC-32=0x57cf1edb]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_nrand48_r)(unsigned short xsubi[3],
                                     struct drand48_data *__restrict buffer,
                                     long *__restrict result)
/*[[[body:libc_nrand48_r]]]*/
/*AUTO*/{
	(void)xsubi;
	(void)buffer;
	(void)result;
	CRT_UNIMPLEMENTEDF("nrand48_r(xsubi: %p, buffer: %p, result: %p)", xsubi, buffer, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_nrand48_r]]]*/

/*[[[head:libc_mrand48_r,hash:CRC-32=0xe0127105]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_mrand48_r)(struct drand48_data *__restrict buffer,
                                     long *__restrict result)
/*[[[body:libc_mrand48_r]]]*/
/*AUTO*/{
	(void)buffer;
	(void)result;
	CRT_UNIMPLEMENTEDF("mrand48_r(buffer: %p, result: %p)", buffer, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_mrand48_r]]]*/

/*[[[head:libc_jrand48_r,hash:CRC-32=0x2e720523]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_jrand48_r)(unsigned short xsubi[3],
                                     struct drand48_data *__restrict buffer,
                                     long *__restrict result)
/*[[[body:libc_jrand48_r]]]*/
/*AUTO*/{
	(void)xsubi;
	(void)buffer;
	(void)result;
	CRT_UNIMPLEMENTEDF("jrand48_r(xsubi: %p, buffer: %p, result: %p)", xsubi, buffer, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_jrand48_r]]]*/

/*[[[head:libc_srand48_r,hash:CRC-32=0xbea2e522]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_srand48_r)(long seedval,
                                     struct drand48_data *buffer)
/*[[[body:libc_srand48_r]]]*/
/*AUTO*/{
	(void)seedval;
	(void)buffer;
	CRT_UNIMPLEMENTEDF("srand48_r(seedval: %lx, buffer: %p)", seedval, buffer); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_srand48_r]]]*/

/*[[[head:libc_seed48_r,hash:CRC-32=0x7caba8b6]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_seed48_r)(unsigned short seed16v[3],
                                    struct drand48_data *buffer)
/*[[[body:libc_seed48_r]]]*/
/*AUTO*/{
	(void)seed16v;
	(void)buffer;
	CRT_UNIMPLEMENTEDF("seed48_r(seed16v: %p, buffer: %p)", seed16v, buffer); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_seed48_r]]]*/

/*[[[head:libc_lcong48_r,hash:CRC-32=0x629b77fb]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_lcong48_r)(unsigned short param[7],
                                     struct drand48_data *buffer)
/*[[[body:libc_lcong48_r]]]*/
/*AUTO*/{
	(void)param;
	(void)buffer;
	CRT_UNIMPLEMENTEDF("lcong48_r(param: %p, buffer: %p)", param, buffer); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_lcong48_r]]]*/

/*[[[head:libc_random_r,hash:CRC-32=0x867fd0f4]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_random_r)(struct random_data *__restrict buf,
                                    int32_t *__restrict result)
/*[[[body:libc_random_r]]]*/
/*AUTO*/{
	(void)buf;
	(void)result;
	CRT_UNIMPLEMENTEDF("random_r(buf: %p, result: %p)", buf, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_random_r]]]*/

/*[[[head:libc_srandom_r,hash:CRC-32=0xe840ebc5]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_srandom_r)(unsigned int seed,
                                     struct random_data *buf)
/*[[[body:libc_srandom_r]]]*/
/*AUTO*/{
	(void)seed;
	(void)buf;
	CRT_UNIMPLEMENTEDF("srandom_r(seed: %x, buf: %p)", seed, buf); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_srandom_r]]]*/

/*[[[head:libc_initstate_r,hash:CRC-32=0x3fa13c2a]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((2, 4)) int
NOTHROW_NCX(LIBCCALL libc_initstate_r)(unsigned int seed,
                                       char *__restrict statebuf,
                                       size_t statelen,
                                       struct random_data *__restrict buf)
/*[[[body:libc_initstate_r]]]*/
/*AUTO*/{
	(void)seed;
	(void)statebuf;
	(void)statelen;
	(void)buf;
	CRT_UNIMPLEMENTEDF("initstate_r(seed: %x, statebuf: %q, statelen: %Ix, buf: %p)", seed, statebuf, statelen, buf); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_initstate_r]]]*/

/*[[[head:libc_setstate_r,hash:CRC-32=0x6113ff06]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_setstate_r)(char *__restrict statebuf,
                                      struct random_data *__restrict buf)
/*[[[body:libc_setstate_r]]]*/
/*AUTO*/{
	(void)statebuf;
	(void)buf;
	CRT_UNIMPLEMENTEDF("setstate_r(statebuf: %q, buf: %p)", statebuf, buf); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_setstate_r]]]*/




/*[[[head:libc_getloadavg,hash:CRC-32=0x5e8ab693]]]*/
INTERN ATTR_SECTION(".text.crt.system.utility") int
NOTHROW_RPC(LIBCCALL libc_getloadavg)(double loadavg[],
                                      __STDC_INT_AS_SIZE_T nelem)
/*[[[body:libc_getloadavg]]]*/
/*AUTO*/{
	(void)loadavg;
	(void)nelem;
	CRT_UNIMPLEMENTEDF("getloadavg(loadavg: %p, nelem: %x)", loadavg, nelem); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getloadavg]]]*/

/*[[[head:libc_drand48,hash:CRC-32=0x154b0864]]]*/
INTERN ATTR_SECTION(".text.crt.random") double
NOTHROW_NCX(LIBCCALL libc_drand48)(void)
/*[[[body:libc_drand48]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("drand48"); /* TODO */
	return (double)libc_seterrno(ENOSYS);
}
/*[[[end:libc_drand48]]]*/

/*[[[head:libc_lrand48,hash:CRC-32=0x3d0384e2]]]*/
INTERN ATTR_SECTION(".text.crt.random") long
NOTHROW_NCX(LIBCCALL libc_lrand48)(void)
/*[[[body:libc_lrand48]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("lrand48"); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_lrand48]]]*/

/*[[[head:libc_mrand48,hash:CRC-32=0x84f85f0a]]]*/
INTERN ATTR_SECTION(".text.crt.random") long
NOTHROW_NCX(LIBCCALL libc_mrand48)(void)
/*[[[body:libc_mrand48]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("mrand48"); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_mrand48]]]*/

/*[[[head:libc_erand48,hash:CRC-32=0xcacb6009]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1)) double
NOTHROW_NCX(LIBCCALL libc_erand48)(unsigned short xsubi[3])
/*[[[body:libc_erand48]]]*/
/*AUTO*/{
	(void)xsubi;
	CRT_UNIMPLEMENTEDF("erand48(xsubi: %p)", xsubi); /* TODO */
	return (double)libc_seterrno(ENOSYS);
}
/*[[[end:libc_erand48]]]*/

/*[[[head:libc_nrand48,hash:CRC-32=0xf0cd3639]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1)) long
NOTHROW_NCX(LIBCCALL libc_nrand48)(unsigned short xsubi[3])
/*[[[body:libc_nrand48]]]*/
/*AUTO*/{
	(void)xsubi;
	CRT_UNIMPLEMENTEDF("nrand48(xsubi: %p)", xsubi); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_nrand48]]]*/

/*[[[head:libc_jrand48,hash:CRC-32=0x62c472e1]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1)) long
NOTHROW_NCX(LIBCCALL libc_jrand48)(unsigned short xsubi[3])
/*[[[body:libc_jrand48]]]*/
/*AUTO*/{
	(void)xsubi;
	CRT_UNIMPLEMENTEDF("jrand48(xsubi: %p)", xsubi); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_jrand48]]]*/

/*[[[head:libc_srand48,hash:CRC-32=0x1c9c73b7]]]*/
INTERN ATTR_SECTION(".text.crt.random") void
NOTHROW_NCX(LIBCCALL libc_srand48)(long seedval)
/*[[[body:libc_srand48]]]*/
/*AUTO*/{
	(void)seedval;
	CRT_UNIMPLEMENTEDF("srand48(seedval: %lx)", seedval); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_srand48]]]*/

/*[[[head:libc_seed48,hash:CRC-32=0x65a13274]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1)) unsigned short *
NOTHROW_NCX(LIBCCALL libc_seed48)(unsigned short seed16v[3])
/*[[[body:libc_seed48]]]*/
/*AUTO*/{
	(void)seed16v;
	CRT_UNIMPLEMENTEDF("seed48(seed16v: %p)", seed16v); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_seed48]]]*/

/*[[[head:libc_lcong48,hash:CRC-32=0xa48fb33]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_lcong48)(unsigned short param[7])
/*[[[body:libc_lcong48]]]*/
/*AUTO*/{
	(void)param;
	CRT_UNIMPLEMENTEDF("lcong48(param: %p)", param); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_lcong48]]]*/

/*[[[head:libc_initstate,hash:CRC-32=0x68122cf5]]]*/
INTERN ATTR_SECTION(".text.crt.random") ATTR_OUTS(2, 3) char *
NOTHROW_NCX(LIBCCALL libc_initstate)(unsigned int seed,
                                     char *statebuf,
                                     size_t statelen)
/*[[[body:libc_initstate]]]*/
/*AUTO*/{
	(void)seed;
	(void)statebuf;
	(void)statelen;
	CRT_UNIMPLEMENTEDF("initstate(seed: %x, statebuf: %q, statelen: %Ix)", seed, statebuf, statelen); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_initstate]]]*/

/*[[[head:libc_setstate,hash:CRC-32=0xd2fa96df]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_setstate)(char *statebuf)
/*[[[body:libc_setstate]]]*/
/*AUTO*/{
	(void)statebuf;
	CRT_UNIMPLEMENTEDF("setstate(statebuf: %q)", statebuf); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_setstate]]]*/

/*[[[head:libd_frealpath4,hash:CRC-32=0x4f81f8d5]]]*/
/* >> frealpath4(2)
 * Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0 | AT_ALTPATH | AT_DOSPATH'
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED ATTR_FDARG(1) ATTR_OUT_OPT(2) char *
NOTHROW_RPC(LIBDCALL libd_frealpath4)(fd_t fd,
                                      char *resolved,
                                      size_t buflen,
                                      atflag_t flags)
/*[[[body:libd_frealpath4]]]*/
{
	return libc_frealpath4(fd, resolved, buflen, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_frealpath4]]]*/

/*[[[head:libc_frealpath4,hash:CRC-32=0x29cef56]]]*/
/* >> frealpath4(2)
 * Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0 | AT_ALTPATH | AT_DOSPATH'
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED ATTR_FDARG(1) ATTR_OUT_OPT(2) char *
NOTHROW_RPC(LIBCCALL libc_frealpath4)(fd_t fd,
                                      char *resolved,
                                      size_t buflen,
                                      atflag_t flags)
/*[[[body:libc_frealpath4]]]*/
{
	ssize_t result;
	char *buffer = resolved;
	if unlikely(flags & AT_READLINK_REQSIZE) {
		libc_seterrno(EINVAL);
		return NULL;
	}
	if (!resolved) {
		if (!buflen) {
			/* Automatically allocate + determine buffer size. */
			buflen = PATH_MAX;
			buffer = (char *)malloc(buflen);
			if unlikely(!buffer)
				buflen = 0;
			for (;;) {
				result = sys_frealpath4(fd,
				                        buffer,
				                        buflen,
				                        flags | AT_READLINK_REQSIZE);
				if unlikely(E_ISERR(result))
					goto err_buffer_result_errno;
				if likely((size_t)result <= buflen)
					break;
				/* Allocate the required amount of memory. */
				resolved = (char *)realloc(buffer, (size_t)result);
				if unlikely(!resolved) {
					free(buffer);
					return NULL;
				}
				buflen = (size_t)result;
				buffer = resolved;
			}
			if ((size_t)result != buflen) {
				resolved = (char *)realloc(buffer, (size_t)result);
				if likely(resolved)
					buffer = resolved;
			}
			return buffer;
		}
		buffer = (char *)malloc(buflen);
		if unlikely(!buffer)
			goto done;
	}
	result = sys_frealpath4(fd,
	                        buffer,
	                        buflen,
	                        flags);
	if (E_ISERR(result)) {
		if (!resolved) {
err_buffer_result_errno:
			free(buffer);
		}
		libc_seterrno_neg(result);
		return NULL;
	}
	if unlikely((size_t)result > buflen) {
		result = -ERANGE;
		goto err_buffer_result_errno;
	}
done:
	return buffer;
}
/*[[[end:libc_frealpath4]]]*/

/*[[[head:libd_frealpathat,hash:CRC-32=0x28b27baf]]]*/
/* >> frealpathat(2)
 * Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is not dereferenced,
 * causing the path to  the symlink itself to  be printed. - Otherwise,  the
 * file pointed to by the symbolic link is printed.
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size.
 * @param flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
 * @return: NULL: [errno=ERANGE]: `buflen' is too small to fit the entire path */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED ATTR_IN(2) ATTR_OUT_OPT(3) char *
NOTHROW_RPC(LIBDCALL libd_frealpathat)(fd_t dirfd,
                                       char const *filename,
                                       char *resolved,
                                       size_t buflen,
                                       atflag_t flags)
/*[[[body:libd_frealpathat]]]*/
{
	return libc_frealpathat(dirfd, filename, resolved, buflen, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_frealpathat]]]*/

/*[[[head:libc_frealpathat,hash:CRC-32=0x2583b937]]]*/
/* >> frealpathat(2)
 * Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is not dereferenced,
 * causing the path to  the symlink itself to  be printed. - Otherwise,  the
 * file pointed to by the symbolic link is printed.
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size.
 * @param flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
 * @return: NULL: [errno=ERANGE]: `buflen' is too small to fit the entire path */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED ATTR_IN(2) ATTR_OUT_OPT(3) char *
NOTHROW_RPC(LIBCCALL libc_frealpathat)(fd_t dirfd,
                                       char const *filename,
                                       char *resolved,
                                       size_t buflen,
                                       atflag_t flags)
/*[[[body:libc_frealpathat]]]*/
{
	ssize_t result;
	char *buffer = resolved;
	if unlikely(flags & AT_READLINK_REQSIZE) {
		libc_seterrno(EINVAL);
		return NULL;
	}
	if (!resolved) {
		if (!buflen) {
			/* Automatically allocate + determine buffer size. */
			buflen = PATH_MAX;
			buffer = (char *)malloc(buflen);
			if unlikely(!buffer)
				buflen = 0;
			for (;;) {
				result = sys_frealpathat(dirfd,
				                         filename,
				                         buffer,
				                         buflen,
				                         flags | AT_READLINK_REQSIZE);
				if unlikely(E_ISERR(result))
					goto err_buffer_result_errno;
				if likely((size_t)result <= buflen)
					break;
				/* Allocate the required amount of memory. */
				resolved = (char *)realloc(buffer, (size_t)result);
				if unlikely(!resolved) {
					free(buffer);
					return NULL;
				}
				buflen = (size_t)result;
				buffer = resolved;
			}
			if ((size_t)result != buflen) {
				resolved = (char *)realloc(buffer, (size_t)result);
				if likely(resolved)
					buffer = resolved;
			}
			return buffer;
		}
		buffer = (char *)malloc(buflen);
		if unlikely(!buffer)
			goto done;
	}
	result = sys_frealpathat(dirfd,
	                         filename,
	                         buffer,
	                         buflen,
	                         flags | AT_READLINK_REQSIZE);
	if (E_ISERR(result)) {
		if (!resolved) {
err_buffer_result_errno:
			free(buffer);
		}
		libc_seterrno_neg(result);
		return NULL;
	}
	if unlikely((size_t)result > buflen) {
		result = -ERANGE;
		goto err_buffer_result_errno;
	}
done:
	return buffer;
}
/*[[[end:libc_frealpathat]]]*/

/*[[[head:libc_grantpt,hash:CRC-32=0xb6ffa2a4]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_FDARG(1) int
NOTHROW_NCX(LIBCCALL libc_grantpt)(fd_t fd)
/*[[[body:libc_grantpt]]]*/
/*AUTO*/{
	(void)fd;
	CRT_UNIMPLEMENTEDF("grantpt(fd: %" PRIxN(__SIZEOF_FD_T__) ")", fd); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_grantpt]]]*/



/*[[[head:libc_posix_openpt,hash:CRC-32=0x9f0949e1]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED fd_t
NOTHROW_RPC(LIBCCALL libc_posix_openpt)(oflag_t oflags)
/*[[[body:libc_posix_openpt]]]*/
/*AUTO*/{
	(void)oflags;
	CRT_UNIMPLEMENTEDF("posix_openpt(oflags: %" PRIxN(__SIZEOF_OFLAG_T__) ")", oflags); /* TODO */
	return (fd_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc_posix_openpt]]]*/

/*[[[head:libd_ptsname_r,hash:CRC-32=0x294bb2a9]]]*/
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.io.tty") ATTR_FDARG(1) ATTR_OUTS(2, 3) int
NOTHROW_NCX(LIBDCALL libd_ptsname_r)(fd_t fd,
                                     char *buf,
                                     size_t buflen)
/*[[[body:libd_ptsname_r]]]*/
/*AUTO*/{
	(void)fd;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("ptsname_r(fd: %" PRIxN(__SIZEOF_FD_T__) ", buf: %q, buflen: %Ix)", fd, buf, buflen); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libd_ptsname_r]]]*/

/*[[[head:libc_ptsname_r,hash:CRC-32=0xe5d395c8]]]*/
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_FDARG(1) ATTR_OUTS(2, 3) int
NOTHROW_NCX(LIBCCALL libc_ptsname_r)(fd_t fd,
                                     char *buf,
                                     size_t buflen)
/*[[[body:libc_ptsname_r]]]*/
/*AUTO*/{
	(void)fd;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("ptsname_r(fd: %" PRIxN(__SIZEOF_FD_T__) ", buf: %q, buflen: %Ix)", fd, buf, buflen); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_ptsname_r]]]*/

/*[[[head:libc_getpt,hash:CRC-32=0x3ef69a1d]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_RPC(LIBCCALL libc_getpt)(void)
/*[[[body:libc_getpt]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getpt"); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getpt]]]*/

/*[[[head:libd_canonicalize_file_name,hash:CRC-32=0x527eafb4]]]*/
/* >> canonicalize_file_name(3)
 * Return the result of `realpath(filename)' as a `malloc()'-
 * allocated  buffer. Upon error, `NULL' is returned instead. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") ATTR_MALLOC WUNUSED ATTR_IN(1) char *
NOTHROW_RPC(LIBDCALL libd_canonicalize_file_name)(char const *filename)
/*[[[body:libd_canonicalize_file_name]]]*/
{
	return libd_realpath(filename, NULL);
}
/*[[[end:libd_canonicalize_file_name]]]*/

/*[[[head:libc_canonicalize_file_name,hash:CRC-32=0x7318024d]]]*/
/* >> canonicalize_file_name(3)
 * Return the result of `realpath(filename)' as a `malloc()'-
 * allocated  buffer. Upon error, `NULL' is returned instead. */
INTERN ATTR_SECTION(".text.crt.fs.property") ATTR_MALLOC WUNUSED ATTR_IN(1) char *
NOTHROW_RPC(LIBCCALL libc_canonicalize_file_name)(char const *filename)
/*[[[body:libc_canonicalize_file_name]]]*/
{
	return libc_realpath(filename, NULL);
}
/*[[[end:libc_canonicalize_file_name]]]*/

/*[[[skip:libc_malloc]]]*/
/*[[[skip:libc_free]]]*/
/*[[[skip:libc_calloc]]]*/
/*[[[skip:libc_realloc]]]*/

/*[[[head:libc___p___argc,hash:CRC-32=0x83476cd6]]]*/
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED int *
NOTHROW(LIBCCALL libc___p___argc)(void)
/*[[[body:libc___p___argc]]]*/
{
	return &__argc;
}
/*[[[end:libc___p___argc]]]*/

/*[[[head:libc___p___argv,hash:CRC-32=0xd1d0ce72]]]*/
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char ***
NOTHROW(LIBCCALL libc___p___argv)(void)
/*[[[body:libc___p___argv]]]*/
{
	return &__argv;
}
/*[[[end:libc___p___argv]]]*/

PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") char16_t **libd___p___wargv_pointer = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") char32_t **libc___p___wargv_pointer = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") struct atomic_once libd___p___wargv_initialized = ATOMIC_ONCE_INIT;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") struct atomic_once libc___p___wargv_initialized = ATOMIC_ONCE_INIT;

#undef __wargv
DEFINE_PUBLIC_IDATA(__wargv, libc___p___wargv, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(DOS$__wargv, libd___p___wargv, __SIZEOF_POINTER__);

/*[[[head:libd___p___wargv,hash:CRC-32=0xbae7ee2e]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***
NOTHROW(LIBDCALL libd___p___wargv)(void)
/*[[[body:libd___p___wargv]]]*/
{
	ATOMIC_ONCE_RUN(&libd___p___wargv_initialized, {
		libd___p___wargv_pointer = convert_mbstoc16v(__argv);
	});
	return &libd___p___wargv_pointer;
}
/*[[[end:libd___p___wargv]]]*/

/*[[[head:libc___p___wargv,hash:CRC-32=0xfda1b2fe]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***
NOTHROW(LIBKCALL libc___p___wargv)(void)
/*[[[body:libc___p___wargv]]]*/
{
	ATOMIC_ONCE_RUN(&libc___p___wargv_initialized, {
		libc___p___wargv_pointer = convert_mbstoc32v(__argv);
	});
	return &libc___p___wargv_pointer;
}
/*[[[end:libc___p___wargv]]]*/


PRIVATE ATTR_CONST WUNUSED ATTR_SECTION(".text.crt.dos.application.init")
char **NOTHROW_NCX(LIBDCALL libc_get_initenv)(void) {
	struct process_peb *peb;
	char **result;
	peb = &__peb;
	/* Construct a pointer to what (presumably) is `pp_envp_vector'
	 * NOTE: If  the hosted application modified `pp_argc' (who's address
	 *       by the way is aliased by `__argc' and `*__p___argc()'), then
	 *       this calculation may not necessarily be correct! */
	result = (char **)(peb + 1) + peb->pp_argc + 1;
	return result;
}

PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") char **libc___p___initenv_pointer = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") char **libd___p___initenv_pointer = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") struct atomic_once libc___p___initenv_initialized = ATOMIC_ONCE_INIT;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") struct atomic_once libd___p___initenv_initialized = ATOMIC_ONCE_INIT;

#undef __initenv
DEFINE_PUBLIC_IDATA(__initenv, libc___p___initenv, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(DOS$__initenv, libd___p___initenv, __SIZEOF_POINTER__);

/*[[[head:libc___p___initenv,hash:CRC-32=0x88c0a004]]]*/
/* Access to the initial environment block */
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") ATTR_CONST ATTR_RETNONNULL WUNUSED char ***
NOTHROW(LIBCCALL libc___p___initenv)(void)
/*[[[body:libc___p___initenv]]]*/
{
	ATOMIC_ONCE_RUN(&libc___p___initenv_initialized, {
		libc___p___initenv_pointer = libc_get_initenv();
	});
	return &libc___p___initenv_pointer;
}
/*[[[end:libc___p___initenv]]]*/

PRIVATE ATTR_SECTION(".text.crt.dos.application.init") WUNUSED char **
NOTHROW_NCX(LIBDCALL libd_alloc_initenv)(void) {
	return libd_alloc_environ(libc_get_initenv());
}

/*[[[head:libd___p___initenv,hash:CRC-32=0x2535deb8]]]*/
/* Access to the initial environment block */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.environ") ATTR_CONST ATTR_RETNONNULL WUNUSED char ***
NOTHROW(LIBDCALL libd___p___initenv)(void)
/*[[[body:libd___p___initenv]]]*/
{
	ATOMIC_ONCE_RUN(&libd___p___initenv_initialized, {
		libd___p___initenv_pointer = libd_alloc_initenv();
	});
	return &libd___p___initenv_pointer;
}
/*[[[end:libd___p___initenv]]]*/

PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") char16_t **libd___p___winitenv_pointer = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") char32_t **libc___p___winitenv_pointer = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") struct atomic_once libd___p___winitenv_initialized = ATOMIC_ONCE_INIT;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") struct atomic_once libc___p___winitenv_initialized = ATOMIC_ONCE_INIT;

#undef __winitenv
DEFINE_PUBLIC_IDATA(__winitenv, libc___p___winitenv, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(DOS$__winitenv, libd___p___winitenv, __SIZEOF_POINTER__);

/*[[[head:libd___p___winitenv,hash:CRC-32=0x81627022]]]*/
/* Access to the initial environment block */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***
NOTHROW(LIBDCALL libd___p___winitenv)(void)
/*[[[body:libd___p___winitenv]]]*/
{
	ATOMIC_ONCE_RUN(&libd___p___winitenv_initialized, {
		libd___p___winitenv_pointer = convert_mbstoc16v(*libd___p___initenv());
	});
	return &libd___p___winitenv_pointer;
}
/*[[[end:libd___p___winitenv]]]*/

/*[[[head:libc___p___winitenv,hash:CRC-32=0x7c0cfe67]]]*/
/* Access to the initial environment block */
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***
NOTHROW(LIBKCALL libc___p___winitenv)(void)
/*[[[body:libc___p___winitenv]]]*/
{
	ATOMIC_ONCE_RUN(&libc___p___winitenv_initialized, {
		libc___p___winitenv_pointer = convert_mbstoc32v(*libd___p___initenv());
	});
	return &libc___p___winitenv_pointer;
}
/*[[[end:libc___p___winitenv]]]*/


PRIVATE ATTR_SECTION(".bss.crt.dos.application.init")
struct atomic_once libd___p__pgmptr_initialized = ATOMIC_ONCE_INIT;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init")
char *libd___p__pgmptr_pointer = NULL;

PRIVATE ATTR_SECTION(".text.crt.dos.application.init") WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_alloc_pgmptr)(void) {
	char *unix_pgmptr = _pgmptr;
	if (!unix_pgmptr)
		return NULL;
	if (unix_pgmptr[0] != '/')
		return unix_pgmptr; /* Non-absolute paths work the same under DOS */
	if (!libd_have_dosfs())
		return unix_pgmptr; /* Not trying to emulate a DOS filesystem */
	/* Convert path into a DOS name. */
	return libd_from_unix_filename(unix_pgmptr, NULL, 0);
}

DEFINE_PUBLIC_IDATA(DOS$_pgmptr, libd___p__pgmptr, __SIZEOF_POINTER__);
DEFINE_PUBLIC_ALIAS(DOS$__p__pgmptr, libd___p__pgmptr);
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char **
NOTHROW_NCX(LIBDCALL libd___p__pgmptr)(void) {
	ATOMIC_ONCE_RUN(&libd___p__pgmptr_initialized, {
		libd___p__pgmptr_pointer = libd_alloc_pgmptr();
	});
	return &libd___p__pgmptr_pointer;
}


PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") char16_t *libd___p__wpgmptr_pointer = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") char32_t *libc___p__wpgmptr_pointer = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") struct atomic_once libd___p__wpgmptr_initialized = ATOMIC_ONCE_INIT;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init") struct atomic_once libc___p__wpgmptr_initialized = ATOMIC_ONCE_INIT;

#undef _wpgmptr
DEFINE_PUBLIC_IDATA(_wpgmptr, libc___p__wpgmptr, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(DOS$_wpgmptr, libd___p__wpgmptr, __SIZEOF_POINTER__);

/*[[[head:libd___p__wpgmptr,hash:CRC-32=0xef17771a]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t **
NOTHROW(LIBDCALL libd___p__wpgmptr)(void)
/*[[[body:libd___p__wpgmptr]]]*/
{
	ATOMIC_ONCE_RUN(&libd___p__wpgmptr_initialized, {
		libd___p__wpgmptr_pointer = convert_mbstoc16(*libd___p__pgmptr());
	});
	return &libd___p__wpgmptr_pointer;
}
/*[[[end:libd___p__wpgmptr]]]*/

/*[[[head:libc___p__wpgmptr,hash:CRC-32=0x76b3f854]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t **
NOTHROW(LIBKCALL libc___p__wpgmptr)(void)
/*[[[body:libc___p__wpgmptr]]]*/
{
	ATOMIC_ONCE_RUN(&libc___p__wpgmptr_initialized, {
		libc___p__wpgmptr_pointer = convert_mbstoc32(_pgmptr);
	});
	return &libc___p__wpgmptr_pointer;
}
/*[[[end:libc___p__wpgmptr]]]*/

/* This one is implemented in libc/libc/errno.c */
/*[[[skip:libc___doserrno]]]*/

/*[[[head:libd__get_errno,hash:CRC-32=0xf859afee]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.errno_access") errno_t
NOTHROW_NCX(LIBDCALL libd__get_errno)(errno_t *perr)
/*[[[body:libd__get_errno]]]*/
{
	if unlikely(!perr)
		return DOS_EINVAL;
	*perr = libd_geterrno();
	return EOK;
}
/*[[[end:libd__get_errno]]]*/

/*[[[head:libc__get_errno,hash:CRC-32=0x6d797f41]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno_access") errno_t
NOTHROW_NCX(LIBCCALL libc__get_errno)(errno_t *perr)
/*[[[body:libc__get_errno]]]*/
{
	if unlikely(!perr)
		return EINVAL;
	*perr = libc_geterrno();
	return EOK;
}
/*[[[end:libc__get_errno]]]*/

/*[[[head:libd__set_errno,hash:CRC-32=0x727b5373]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.errno_access") errno_t
NOTHROW_NCX(LIBDCALL libd__set_errno)(errno_t err)
/*[[[body:libd__set_errno]]]*/
{
	libd_seterrno(err);
	return EOK;
}
/*[[[end:libd__set_errno]]]*/

/*[[[head:libc__set_errno,hash:CRC-32=0x57b23e35]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno_access") errno_t
NOTHROW_NCX(LIBCCALL libc__set_errno)(errno_t err)
/*[[[body:libc__set_errno]]]*/
{
	libc_seterrno(err);
	return EOK;
}
/*[[[end:libc__set_errno]]]*/

/*[[[head:libd__get_doserrno,hash:CRC-32=0xfeffb474]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.errno") errno_t
NOTHROW_NCX(LIBDCALL libd__get_doserrno)(u32 *perr)
/*[[[body:libd__get_doserrno]]]*/
{
	if (!perr)
		return DOS_EINVAL;
	*perr = libd_getnterrno();
	return 0;
}
/*[[[end:libd__get_doserrno]]]*/

/*[[[head:libc__get_doserrno,hash:CRC-32=0x8bad074a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") errno_t
NOTHROW_NCX(LIBCCALL libc__get_doserrno)(u32 *perr)
/*[[[body:libc__get_doserrno]]]*/
{
	if (!perr)
		return EINVAL;
	*perr = libd_getnterrno();
	return 0;
}
/*[[[end:libc__get_doserrno]]]*/


/*[[[head:libc__set_doserrno,hash:CRC-32=0xd9a78cf6]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") errno_t
NOTHROW_NCX(LIBCCALL libc__set_doserrno)(u32 err)
/*[[[body:libc__set_doserrno]]]*/
{
	libd_setnterrno(err);
	return EOK;
}
/*[[[end:libc__set_doserrno]]]*/




/*[[[head:libc__seterrormode,hash:CRC-32=0xb76bea9f]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") void
NOTHROW_NCX(LIBCCALL libc__seterrormode)(int mode)
/*[[[body:libc__seterrormode]]]*/
/*AUTO*/{
	(void)mode;
	CRT_UNIMPLEMENTEDF("_seterrormode(mode: %x)", mode); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__seterrormode]]]*/

/*[[[head:libc__set_error_mode,hash:CRC-32=0x2437863d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") int
NOTHROW_NCX(LIBCCALL libc__set_error_mode)(int mode)
/*[[[body:libc__set_error_mode]]]*/
/*AUTO*/{
	(void)mode;
	CRT_UNIMPLEMENTEDF("_set_error_mode(mode: %x)", mode); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc__set_error_mode]]]*/

/*[[[head:libc__beep,hash:CRC-32=0x369ee9ec]]]*/
INTERN ATTR_SECTION(".text.crt.dos.system") void
NOTHROW_NCX(LIBCCALL libc__beep)(unsigned int freq,
                                 unsigned int duration)
/*[[[body:libc__beep]]]*/
/*AUTO*/{
	(void)freq;
	(void)duration;
	CRT_UNIMPLEMENTEDF("_beep(freq: %x, duration: %x)", freq, duration); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__beep]]]*/

/*[[[head:libc__set_purecall_handler,hash:CRC-32=0x67fa5e45]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") _purecall_handler
NOTHROW_NCX(LIBCCALL libc__set_purecall_handler)(_purecall_handler handler)
/*[[[body:libc__set_purecall_handler]]]*/
/*AUTO*/{
	(void)handler;
	CRT_UNIMPLEMENTEDF("_set_purecall_handler(handler: %p)", handler); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__set_purecall_handler]]]*/

/*[[[head:libc__get_purecall_handler,hash:CRC-32=0x47e9bd6f]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") _purecall_handler
NOTHROW_NCX(LIBCCALL libc__get_purecall_handler)(void)
/*[[[body:libc__get_purecall_handler]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_get_purecall_handler"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__get_purecall_handler]]]*/


#undef _fmode
INTERN ATTR_SECTION(".bss.crt.dos.FILE.utility") int libd__fmode = 0;
DEFINE_PUBLIC_ALIAS(_fmode, libd__fmode);
#define _fmode libd__fmode

/*[[[head:libc___p__fmode,hash:CRC-32=0x6c97165e]]]*/
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") ATTR_CONST ATTR_RETNONNULL WUNUSED int *
NOTHROW(LIBCCALL libc___p__fmode)(void)
/*[[[body:libc___p__fmode]]]*/
{
	return &_fmode;
}
/*[[[end:libc___p__fmode]]]*/

/*[[[head:libc__set_fmode,hash:CRC-32=0xba018643]]]*/
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") errno_t
NOTHROW_NCX(LIBCCALL libc__set_fmode)(int mode)
/*[[[body:libc__set_fmode]]]*/
{
	_fmode = mode;
	return EOK;
}
/*[[[end:libc__set_fmode]]]*/

/*[[[head:libc__get_fmode,hash:CRC-32=0xd3273751]]]*/
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc__get_fmode)(int *pmode)
/*[[[body:libc__get_fmode]]]*/
{
	*pmode = _fmode;
	return EOK;
}
/*[[[end:libc__get_fmode]]]*/

/*[[[head:libc__set_abort_behavior,hash:CRC-32=0x9642f3c4]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") unsigned int
NOTHROW_NCX(LIBCCALL libc__set_abort_behavior)(unsigned int flags,
                                               unsigned int mask)
/*[[[body:libc__set_abort_behavior]]]*/
/*AUTO*/{
	(void)flags;
	(void)mask;
	CRT_UNIMPLEMENTEDF("_set_abort_behavior(flags: %x, mask: %x)", flags, mask); /* TODO */
	return (unsigned int)libc_seterrno(ENOSYS);
}
/*[[[end:libc__set_abort_behavior]]]*/




/*[[[head:libd__wsearchenv_s,hash:CRC-32=0x6699654]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4) errno_t
NOTHROW_RPC(LIBDCALL libd__wsearchenv_s)(char16_t const *file,
                                         char16_t const *envvar,
                                         char16_t *__restrict resultpath,
                                         size_t resultpath_len)
/*[[[body:libd__wsearchenv_s]]]*/
/*AUTO*/{
	(void)file;
	(void)envvar;
	(void)resultpath;
	(void)resultpath_len;
	CRT_UNIMPLEMENTEDF("DOS$_wsearchenv_s(file: %p, envvar: %p, resultpath: %p, resultpath_len: %Ix)", file, envvar, resultpath, resultpath_len); /* TODO */
	return ENOSYS;
}
/*[[[end:libd__wsearchenv_s]]]*/

/*[[[head:libc__wsearchenv_s,hash:CRC-32=0xfd8f9c75]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4) errno_t
NOTHROW_RPC(LIBKCALL libc__wsearchenv_s)(char32_t const *file,
                                         char32_t const *envvar,
                                         char32_t *__restrict resultpath,
                                         size_t resultpath_len)
/*[[[body:libc__wsearchenv_s]]]*/
/*AUTO*/{
	(void)file;
	(void)envvar;
	(void)resultpath;
	(void)resultpath_len;
	CRT_UNIMPLEMENTEDF("_wsearchenv_s(file: %p, envvar: %p, resultpath: %p, resultpath_len: %Ix)", file, envvar, resultpath, resultpath_len); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__wsearchenv_s]]]*/





/*[[[head:libc_radixsort,hash:CRC-32=0x70f7f2c3]]]*/
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_INOUTS(1, 2) ATTR_IN_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_radixsort)(unsigned char const **base,
                                     int item_count,
                                     unsigned char const table[256],
                                     unsigned endbyte)
/*[[[body:libc_radixsort]]]*/
/*AUTO*/{
	(void)base;
	(void)item_count;
	(void)table;
	(void)endbyte;
	CRT_UNIMPLEMENTEDF("radixsort(base: %p, item_count: %x, table: %p, endbyte: %x)", base, item_count, table, endbyte); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_radixsort]]]*/

/*[[[head:libc_sradixsort,hash:CRC-32=0x81ae9281]]]*/
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_INOUTS(1, 2) ATTR_IN_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_sradixsort)(unsigned char const **base,
                                      int item_count,
                                      unsigned char const table[256],
                                      unsigned endbyte)
/*[[[body:libc_sradixsort]]]*/
/*AUTO*/{
	(void)base;
	(void)item_count;
	(void)table;
	(void)endbyte;
	CRT_UNIMPLEMENTEDF("sradixsort(base: %p, item_count: %x, table: %p, endbyte: %x)", base, item_count, table, endbyte); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_sradixsort]]]*/

/*[[[head:libc_getbsize,hash:CRC-32=0xbd5ec922]]]*/
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED ATTR_OUT(1) ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc_getbsize)(int *headerlenp,
                                    __LONGPTR_TYPE__ *blocksizep)
/*[[[body:libc_getbsize]]]*/
/*AUTO*/{
	(void)headerlenp;
	(void)blocksizep;
	CRT_UNIMPLEMENTEDF("getbsize(headerlenp: %p, blocksizep: %p)", headerlenp, blocksizep); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getbsize]]]*/

/*[[[head:libc_devname_r,hash:CRC-32=0xb25c6f92]]]*/
/* >> devname(3), devname_r(3) */
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_OUTS(3, 4) int
NOTHROW_NCX(LIBCCALL libc_devname_r)(dev_t dev,
                                     mode_t type,
                                     char *buf,
                                     size_t len)
/*[[[body:libc_devname_r]]]*/
/*AUTO*/{
	(void)dev;
	(void)type;
	(void)buf;
	(void)len;
	CRT_UNIMPLEMENTEDF("devname_r(dev: %" PRIxN(__SIZEOF_DEV_T__) ", type: %" PRIxN(__SIZEOF_MODE_T__) ", buf: %q, len: %Ix)", dev, type, buf, len); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_devname_r]]]*/

/*[[[head:libc_humanize_number,hash:CRC-32=0xa3c253da]]]*/
/* >> humanize_number(3), dehumanize_number(3)
 * @param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
 * @param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES' */
INTERN ATTR_SECTION(".text.crt.bsd") int
NOTHROW_NCX(LIBCCALL libc_humanize_number)(char *buf,
                                           size_t len,
                                           int64_t bytes,
                                           char const *suffix,
                                           int scale,
                                           int flags)
/*[[[body:libc_humanize_number]]]*/
/*AUTO*/{
	(void)buf;
	(void)len;
	(void)bytes;
	(void)suffix;
	(void)scale;
	(void)flags;
	CRT_UNIMPLEMENTEDF("humanize_number(buf: %q, len: %Ix, bytes: %" PRIx64 ", suffix: %q, scale: %x, flags: %x)", buf, len, bytes, suffix, scale, flags); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_humanize_number]]]*/

/*[[[head:libc_dehumanize_number,hash:CRC-32=0x535f46a0]]]*/
/* >> humanize_number(3), dehumanize_number(3)
 * @param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
 * @param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES' */
INTERN ATTR_SECTION(".text.crt.bsd") int
NOTHROW_NCX(LIBCCALL libc_dehumanize_number)(char const *str,
                                             int64_t *size)
/*[[[body:libc_dehumanize_number]]]*/
/*AUTO*/{
	(void)str;
	(void)size;
	CRT_UNIMPLEMENTEDF("dehumanize_number(str: %q, size: %p)", str, size); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_dehumanize_number]]]*/




/************************************************************************/
/* Functions from <crtdefs.h>                                           */
/************************************************************************/
PRIVATE ATTR_SECTION(".bss.crt.dos.errno") _invalid_parameter_handler
libd_invalid_parameter_handler = NULL;

DEFINE_PUBLIC_ALIAS(_invalid_parameter, libd__invalid_parameter);
#ifdef __x86_64__
DEFINE_PUBLIC_ALIAS("?_invalid_parameter@@YAXPEBG00I_K@Z", libd__invalid_parameter);
#endif /* __x86_64__ */

INTERN ATTR_SECTION(".text.crt.dos.errno") void
NOTHROW_NCX(LIBDCALL libd__invalid_parameter)(__WCHAR16_TYPE__ const *expr, __WCHAR16_TYPE__ const *func,
                                              __WCHAR16_TYPE__ const *file, unsigned int line,
                                              uintptr_t zero) {
	_invalid_parameter_handler handler;
	handler = atomic_read(&libd_invalid_parameter_handler);
	if (handler) {
		(*handler)(expr, func, file, line, zero);
	} else {
		/* We treat no-handle as a no-op. */
	}
}

DEFINE_PUBLIC_ALIAS(_invoke_watson, libd__invoke_watson);
INTERN ATTR_NORETURN ATTR_SECTION(".text.crt.dos.errno") void
NOTHROW_NCX(LIBDCALL libd__invoke_watson)(__WCHAR16_TYPE__ const *expr, __WCHAR16_TYPE__ const *func,
                                          __WCHAR16_TYPE__ const *file, unsigned int line,
                                          uintptr_t zero) {
	(void)expr;
	(void)func;
	(void)file;
	(void)line;
	(void)zero;
	abort();
}

DEFINE_PUBLIC_ALIAS(_invalid_parameter_noinfo, libd__invalid_parameter_noinfo);
INTERN ATTR_SECTION(".text.crt.dos.errno") void
NOTHROW_NCX(LIBDCALL libd__invalid_parameter_noinfo)(void) {
	libd__invalid_parameter(NULL, NULL, NULL, 0, 0);
}

DEFINE_PUBLIC_ALIAS(_invalid_parameter_noinfo_noreturn, libd__invalid_parameter_noinfo_noreturn);
INTERN ATTR_NORETURN ATTR_SECTION(".text.crt.dos.errno") void
NOTHROW_NCX(LIBDCALL libd__invalid_parameter_noinfo_noreturn)(void) {
	libd__invalid_parameter(NULL, NULL, NULL, 0, 0);
	abort();
}


/*[[[head:libc__set_invalid_parameter_handler,hash:CRC-32=0xdae2af3b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") _invalid_parameter_handler
NOTHROW_NCX(LIBCCALL libc__set_invalid_parameter_handler)(_invalid_parameter_handler handler)
/*[[[body:libc__set_invalid_parameter_handler]]]*/
{
	return atomic_xch(&libd_invalid_parameter_handler, handler);
}
/*[[[end:libc__set_invalid_parameter_handler]]]*/

/*[[[head:libc__get_invalid_parameter_handler,hash:CRC-32=0x31cb9fb2]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") _invalid_parameter_handler
NOTHROW_NCX(LIBCCALL libc__get_invalid_parameter_handler)(void)
/*[[[body:libc__get_invalid_parameter_handler]]]*/
{
	return atomic_read(&libd_invalid_parameter_handler);
}
/*[[[end:libc__get_invalid_parameter_handler]]]*/






/*[[[start:exports,hash:CRC-32=0x12439d81]]]*/
DEFINE_PUBLIC_ALIAS_P(DOS$getenv,libd_getenv,WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBDCALL,(char const *varname),(varname));
DEFINE_PUBLIC_ALIAS_P(getenv,libc_getenv,WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBCCALL,(char const *varname),(varname));
DEFINE_PUBLIC_ALIAS_P_VOID(xexit,libc_exit,ATTR_NORETURN,,LIBCCALL,(int status),(status));
DEFINE_PUBLIC_ALIAS_P_VOID(exit,libc_exit,ATTR_NORETURN,,LIBCCALL,(int status),(status));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_crt_atexit,libc_atexit,NONNULL((1)),int,NOTHROW_NCX,LIBCCALL,(void (LIBCCALL *func)(void)),(func));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(xatexit,libc_atexit,NONNULL((1)),int,NOTHROW_NCX,LIBCCALL,(void (LIBCCALL *func)(void)),(func));
DEFINE_PUBLIC_ALIAS_P(atexit,libc_atexit,NONNULL((1)),int,NOTHROW_NCX,LIBCCALL,(void (LIBCCALL *func)(void)),(func));
DEFINE_PUBLIC_ALIAS_P_VOID(quick_exit,libc_quick_exit,ATTR_NORETURN,,LIBCCALL,(int status),(status));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_crt_at_quick_exit,libc_at_quick_exit,NONNULL((1)),int,NOTHROW_NCX,LIBCCALL,(void (LIBCCALL *func)(void)),(func));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(at_quick_exit,libc_at_quick_exit,NONNULL((1)),int,NOTHROW_NCX,LIBCCALL,(void (LIBCCALL *func)(void)),(func));
DEFINE_PUBLIC_ALIAS_P_VOID(_exit,libc__Exit,ATTR_NORETURN,,LIBCCALL,(int status),(status));
DEFINE_PUBLIC_ALIAS_P_VOID(_Exit,libc__Exit,ATTR_NORETURN,,LIBCCALL,(int status),(status));
DEFINE_PUBLIC_ALIAS_P_VOID(srand,libc_srand,,NOTHROW,LIBCCALL,(long seed),(seed));
DEFINE_PUBLIC_ALIAS_P(rand,libc_rand,,int,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(strfromd,libc_strfromd,ATTR_IN(3) ATTR_OUTS(1, 2),__STDC_INT32_AS_SIZE_T,NOTHROW_NCX,LIBCCALL,(char *__restrict buf, size_t buflen, char const *__restrict format, double fp),(buf,buflen,format,fp));
DEFINE_PUBLIC_ALIAS_P(strfromf,libc_strfromf,ATTR_IN(3) ATTR_OUTS(1, 2),__STDC_INT32_AS_SIZE_T,NOTHROW_NCX,LIBCCALL,(char *__restrict buf, size_t buflen, char const *__restrict format, float fp),(buf,buflen,format,fp));
DEFINE_PUBLIC_ALIAS_P(strfroml,libc_strfroml,ATTR_IN(3) ATTR_OUTS(1, 2),__STDC_INT32_AS_SIZE_T,NOTHROW_NCX,LIBCCALL,(char *__restrict buf, size_t buflen, char const *__restrict format, __LONGDOUBLE fp),(buf,buflen,format,fp));
DEFINE_PUBLIC_ALIAS_P(rand_r,libc_rand_r,ATTR_INOUT(1),int,NOTHROW_NCX,LIBCCALL,(unsigned int *__restrict pseed),(pseed));
DEFINE_PUBLIC_ALIAS_P(getloadavg,libc_getloadavg,,int,NOTHROW_RPC,LIBCCALL,(double loadavg[], __STDC_INT_AS_SIZE_T nelem),(loadavg,nelem));
DEFINE_PUBLIC_ALIAS_P(drand48_r,libc_drand48_r,NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(struct drand48_data *__restrict buffer, double *__restrict result),(buffer,result));
DEFINE_PUBLIC_ALIAS_P(erand48_r,libc_erand48_r,NONNULL((1, 2, 3)),int,NOTHROW_NCX,LIBCCALL,(unsigned short xsubi[3], struct drand48_data *__restrict buffer, double *__restrict result),(xsubi,buffer,result));
DEFINE_PUBLIC_ALIAS_P(lrand48_r,libc_lrand48_r,NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(struct drand48_data *__restrict buffer, long *__restrict result),(buffer,result));
DEFINE_PUBLIC_ALIAS_P(nrand48_r,libc_nrand48_r,NONNULL((1, 2, 3)),int,NOTHROW_NCX,LIBCCALL,(unsigned short xsubi[3], struct drand48_data *__restrict buffer, long *__restrict result),(xsubi,buffer,result));
DEFINE_PUBLIC_ALIAS_P(mrand48_r,libc_mrand48_r,NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(struct drand48_data *__restrict buffer, long *__restrict result),(buffer,result));
DEFINE_PUBLIC_ALIAS_P(jrand48_r,libc_jrand48_r,NONNULL((1, 2, 3)),int,NOTHROW_NCX,LIBCCALL,(unsigned short xsubi[3], struct drand48_data *__restrict buffer, long *__restrict result),(xsubi,buffer,result));
DEFINE_PUBLIC_ALIAS_P(srand48_r,libc_srand48_r,NONNULL((2)),int,NOTHROW_NCX,LIBCCALL,(long seedval, struct drand48_data *buffer),(seedval,buffer));
DEFINE_PUBLIC_ALIAS_P(seed48_r,libc_seed48_r,NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(unsigned short seed16v[3], struct drand48_data *buffer),(seed16v,buffer));
DEFINE_PUBLIC_ALIAS_P(lcong48_r,libc_lcong48_r,NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(unsigned short param[7], struct drand48_data *buffer),(param,buffer));
DEFINE_PUBLIC_ALIAS_P(__random_r,libc_random_r,NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(struct random_data *__restrict buf, int32_t *__restrict result),(buf,result));
DEFINE_PUBLIC_ALIAS_P(random_r,libc_random_r,NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(struct random_data *__restrict buf, int32_t *__restrict result),(buf,result));
DEFINE_PUBLIC_ALIAS_P(__srandom_r,libc_srandom_r,NONNULL((2)),int,NOTHROW_NCX,LIBCCALL,(unsigned int seed, struct random_data *buf),(seed,buf));
DEFINE_PUBLIC_ALIAS_P(srandom_r,libc_srandom_r,NONNULL((2)),int,NOTHROW_NCX,LIBCCALL,(unsigned int seed, struct random_data *buf),(seed,buf));
DEFINE_PUBLIC_ALIAS_P(__initstate_r,libc_initstate_r,NONNULL((2, 4)),int,NOTHROW_NCX,LIBCCALL,(unsigned int seed, char *__restrict statebuf, size_t statelen, struct random_data *__restrict buf),(seed,statebuf,statelen,buf));
DEFINE_PUBLIC_ALIAS_P(initstate_r,libc_initstate_r,NONNULL((2, 4)),int,NOTHROW_NCX,LIBCCALL,(unsigned int seed, char *__restrict statebuf, size_t statelen, struct random_data *__restrict buf),(seed,statebuf,statelen,buf));
DEFINE_PUBLIC_ALIAS_P(__setstate_r,libc_setstate_r,NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(char *__restrict statebuf, struct random_data *__restrict buf),(statebuf,buf));
DEFINE_PUBLIC_ALIAS_P(setstate_r,libc_setstate_r,NONNULL((1, 2)),int,NOTHROW_NCX,LIBCCALL,(char *__restrict statebuf, struct random_data *__restrict buf),(statebuf,buf));
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(DOS$__on_exit,libd_on_exit,NONNULL((1)),int,NOTHROW_NCX,LIBDCALL,(void (LIBDCALL *func)(int status, void *arg), void *arg),(func,arg));
DEFINE_PUBLIC_ALIAS_P(DOS$on_exit,libd_on_exit,NONNULL((1)),int,NOTHROW_NCX,LIBDCALL,(void (LIBDCALL *func)(int status, void *arg), void *arg),(func,arg));
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__on_exit,libc_on_exit,NONNULL((1)),int,NOTHROW_NCX,LIBCCALL,(void (LIBCCALL *func)(int status, void *arg), void *arg),(func,arg));
DEFINE_PUBLIC_ALIAS_P(on_exit,libc_on_exit,NONNULL((1)),int,NOTHROW_NCX,LIBCCALL,(void (LIBCCALL *func)(int status, void *arg), void *arg),(func,arg));
DEFINE_PUBLIC_ALIAS_P(__clearenv,libc_clearenv,,int,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(clearenv,libc_clearenv,,int,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$setenv,libd_setenv,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char const *varname, char const *val, int replace),(varname,val,replace));
DEFINE_PUBLIC_ALIAS_P(setenv,libc_setenv,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(char const *varname, char const *val, int replace),(varname,val,replace));
DEFINE_PUBLIC_ALIAS_P(DOS$unsetenv,libd_unsetenv,ATTR_IN(1),int,NOTHROW_NCX,LIBDCALL,(char const *varname),(varname));
DEFINE_PUBLIC_ALIAS_P(unsetenv,libc_unsetenv,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(char const *varname),(varname));
DEFINE_PUBLIC_ALIAS_P(drand48,libc_drand48,,double,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(lrand48,libc_lrand48,,long,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(mrand48,libc_mrand48,,long,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(erand48,libc_erand48,NONNULL((1)),double,NOTHROW_NCX,LIBCCALL,(unsigned short xsubi[3]),(xsubi));
DEFINE_PUBLIC_ALIAS_P(nrand48,libc_nrand48,NONNULL((1)),long,NOTHROW_NCX,LIBCCALL,(unsigned short xsubi[3]),(xsubi));
DEFINE_PUBLIC_ALIAS_P(jrand48,libc_jrand48,NONNULL((1)),long,NOTHROW_NCX,LIBCCALL,(unsigned short xsubi[3]),(xsubi));
DEFINE_PUBLIC_ALIAS_P_VOID(srand48,libc_srand48,,NOTHROW_NCX,LIBCCALL,(long seedval),(seedval));
DEFINE_PUBLIC_ALIAS_P(seed48,libc_seed48,NONNULL((1)),unsigned short *,NOTHROW_NCX,LIBCCALL,(unsigned short seed16v[3]),(seed16v));
DEFINE_PUBLIC_ALIAS_P_VOID(lcong48,libc_lcong48,NONNULL((1)),NOTHROW_NCX,LIBCCALL,(unsigned short param[7]),(param));
DEFINE_PUBLIC_ALIAS_P(DOS$_putenv,libd_putenv,ATTR_INOUT(1),int,NOTHROW_NCX,LIBDCALL,(char *string),(string));
DEFINE_PUBLIC_ALIAS_P(DOS$putenv,libd_putenv,ATTR_INOUT(1),int,NOTHROW_NCX,LIBDCALL,(char *string),(string));
DEFINE_PUBLIC_ALIAS_P(putenv,libc_putenv,ATTR_INOUT(1),int,NOTHROW_NCX,LIBCCALL,(char *string),(string));
DEFINE_PUBLIC_ALIAS_P(__random,libc_random,,long,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(random,libc_random,,long,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(__srandom,libc_srandom,,NOTHROW_NCX,LIBCCALL,(unsigned int seed),(seed));
DEFINE_PUBLIC_ALIAS_P_VOID(srandom,libc_srandom,,NOTHROW_NCX,LIBCCALL,(unsigned int seed),(seed));
DEFINE_PUBLIC_ALIAS_P(__initstate,libc_initstate,ATTR_OUTS(2, 3),char *,NOTHROW_NCX,LIBCCALL,(unsigned int seed, char *statebuf, size_t statelen),(seed,statebuf,statelen));
DEFINE_PUBLIC_ALIAS_P(initstate,libc_initstate,ATTR_OUTS(2, 3),char *,NOTHROW_NCX,LIBCCALL,(unsigned int seed, char *statebuf, size_t statelen),(seed,statebuf,statelen));
DEFINE_PUBLIC_ALIAS_P(__setstate,libc_setstate,NONNULL((1)),char *,NOTHROW_NCX,LIBCCALL,(char *statebuf),(statebuf));
DEFINE_PUBLIC_ALIAS_P(setstate,libc_setstate,NONNULL((1)),char *,NOTHROW_NCX,LIBCCALL,(char *statebuf),(statebuf));
DEFINE_PUBLIC_ALIAS_P(DOS$frealpath4,libd_frealpath4,WUNUSED ATTR_FDARG(1) ATTR_OUT_OPT(2),char *,NOTHROW_RPC,LIBDCALL,(fd_t fd, char *resolved, size_t buflen, atflag_t flags),(fd,resolved,buflen,flags));
DEFINE_PUBLIC_ALIAS_P(frealpath4,libc_frealpath4,WUNUSED ATTR_FDARG(1) ATTR_OUT_OPT(2),char *,NOTHROW_RPC,LIBCCALL,(fd_t fd, char *resolved, size_t buflen, atflag_t flags),(fd,resolved,buflen,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$frealpathat,libd_frealpathat,WUNUSED ATTR_IN(2) ATTR_OUT_OPT(3),char *,NOTHROW_RPC,LIBDCALL,(fd_t dirfd, char const *filename, char *resolved, size_t buflen, atflag_t flags),(dirfd,filename,resolved,buflen,flags));
DEFINE_PUBLIC_ALIAS_P(frealpathat,libc_frealpathat,WUNUSED ATTR_IN(2) ATTR_OUT_OPT(3),char *,NOTHROW_RPC,LIBCCALL,(fd_t dirfd, char const *filename, char *resolved, size_t buflen, atflag_t flags),(dirfd,filename,resolved,buflen,flags));
DEFINE_PUBLIC_ALIAS_P(grantpt,libc_grantpt,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(posix_openpt,libc_posix_openpt,WUNUSED,fd_t,NOTHROW_RPC,LIBCCALL,(oflag_t oflags),(oflags));
DEFINE_PUBLIC_ALIAS_P(DOS$ptsname_r,libd_ptsname_r,ATTR_FDARG(1) ATTR_OUTS(2, 3),int,NOTHROW_NCX,LIBDCALL,(fd_t fd, char *buf, size_t buflen),(fd,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(ptsname_r,libc_ptsname_r,ATTR_FDARG(1) ATTR_OUTS(2, 3),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, char *buf, size_t buflen),(fd,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(getpt,libc_getpt,,int,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$canonicalize_file_name,libd_canonicalize_file_name,ATTR_MALLOC WUNUSED ATTR_IN(1),char *,NOTHROW_RPC,LIBDCALL,(char const *filename),(filename));
DEFINE_PUBLIC_ALIAS_P(canonicalize_file_name,libc_canonicalize_file_name,ATTR_MALLOC WUNUSED ATTR_IN(1),char *,NOTHROW_RPC,LIBCCALL,(char const *filename),(filename));
DEFINE_PUBLIC_ALIAS_P(getbsize,libc_getbsize,WUNUSED ATTR_OUT(1) ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(int *headerlenp, __LONGPTR_TYPE__ *blocksizep),(headerlenp,blocksizep));
DEFINE_PUBLIC_ALIAS_P(radixsort,libc_radixsort,ATTR_INOUTS(1, 2) ATTR_IN_OPT(3),int,NOTHROW_NCX,LIBCCALL,(unsigned char const **base, int item_count, unsigned char const table[256], unsigned endbyte),(base,item_count,table,endbyte));
DEFINE_PUBLIC_ALIAS_P(sradixsort,libc_sradixsort,ATTR_INOUTS(1, 2) ATTR_IN_OPT(3),int,NOTHROW_NCX,LIBCCALL,(unsigned char const **base, int item_count, unsigned char const table[256], unsigned endbyte),(base,item_count,table,endbyte));
DEFINE_PUBLIC_ALIAS_P(devname_r,libc_devname_r,ATTR_OUTS(3, 4),int,NOTHROW_NCX,LIBCCALL,(dev_t dev, mode_t type, char *buf, size_t len),(dev,type,buf,len));
DEFINE_PUBLIC_ALIAS_P(humanize_number,libc_humanize_number,,int,NOTHROW_NCX,LIBCCALL,(char *buf, size_t len, int64_t bytes, char const *suffix, int scale, int flags),(buf,len,bytes,suffix,scale,flags));
DEFINE_PUBLIC_ALIAS_P(dehumanize_number,libc_dehumanize_number,,int,NOTHROW_NCX,LIBCCALL,(char const *str, int64_t *size),(str,size));
DEFINE_PUBLIC_ALIAS_P(DOS$_get_errno,libd__get_errno,,errno_t,NOTHROW_NCX,LIBDCALL,(errno_t *perr),(perr));
DEFINE_PUBLIC_ALIAS_P(_get_errno,libc__get_errno,,errno_t,NOTHROW_NCX,LIBCCALL,(errno_t *perr),(perr));
DEFINE_PUBLIC_ALIAS_P(DOS$_set_errno,libd__set_errno,,errno_t,NOTHROW_NCX,LIBDCALL,(errno_t err),(err));
DEFINE_PUBLIC_ALIAS_P(_set_errno,libc__set_errno,,errno_t,NOTHROW_NCX,LIBCCALL,(errno_t err),(err));
DEFINE_PUBLIC_ALIAS_P(DOS$_get_doserrno,libd__get_doserrno,,errno_t,NOTHROW_NCX,LIBDCALL,(u32 *perr),(perr));
DEFINE_PUBLIC_ALIAS_P(_get_doserrno,libc__get_doserrno,,errno_t,NOTHROW_NCX,LIBCCALL,(u32 *perr),(perr));
DEFINE_PUBLIC_ALIAS_P(_set_doserrno,libc__set_doserrno,,errno_t,NOTHROW_NCX,LIBCCALL,(u32 err),(err));
DEFINE_PUBLIC_ALIAS_P(__p___argc,libc___p___argc,ATTR_CONST ATTR_RETNONNULL WUNUSED,int *,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p___argv,libc___p___argv,ATTR_CONST ATTR_RETNONNULL WUNUSED,char ***,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$__p___wargv,libd___p___wargv,ATTR_CONST ATTR_RETNONNULL WUNUSED,char16_t ***,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p___wargv,libc___p___wargv,ATTR_CONST ATTR_RETNONNULL WUNUSED,char32_t ***,NOTHROW,LIBKCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$__p__wenviron,libd___p__wenviron,ATTR_CONST ATTR_RETNONNULL WUNUSED,char16_t ***,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p__wenviron,libc___p__wenviron,ATTR_CONST ATTR_RETNONNULL WUNUSED,char32_t ***,NOTHROW,LIBKCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$__p__wpgmptr,libd___p__wpgmptr,ATTR_CONST ATTR_RETNONNULL WUNUSED,char16_t **,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p__wpgmptr,libc___p__wpgmptr,ATTR_CONST ATTR_RETNONNULL WUNUSED,char32_t **,NOTHROW,LIBKCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$__p___initenv,libd___p___initenv,ATTR_CONST ATTR_RETNONNULL WUNUSED,char ***,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p___initenv,libc___p___initenv,ATTR_CONST ATTR_RETNONNULL WUNUSED,char ***,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$__p___winitenv,libd___p___winitenv,ATTR_CONST ATTR_RETNONNULL WUNUSED,char16_t ***,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p___winitenv,libc___p___winitenv,ATTR_CONST ATTR_RETNONNULL WUNUSED,char32_t ***,NOTHROW,LIBKCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_set_purecall_handler,libc__set_purecall_handler,,_purecall_handler,NOTHROW_NCX,LIBCCALL,(_purecall_handler handler),(handler));
DEFINE_PUBLIC_ALIAS_P(_get_purecall_handler,libc__get_purecall_handler,,_purecall_handler,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_set_invalid_parameter_handler,libc__set_invalid_parameter_handler,,_invalid_parameter_handler,NOTHROW_NCX,LIBCCALL,(_invalid_parameter_handler handler),(handler));
DEFINE_PUBLIC_ALIAS_P(_get_invalid_parameter_handler,libc__get_invalid_parameter_handler,,_invalid_parameter_handler,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p__fmode,libc___p__fmode,ATTR_CONST ATTR_RETNONNULL WUNUSED,int *,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_set_fmode,libc__set_fmode,,errno_t,NOTHROW_NCX,LIBCCALL,(int mode),(mode));
DEFINE_PUBLIC_ALIAS_P(_get_fmode,libc__get_fmode,ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBCCALL,(int *pmode),(pmode));
DEFINE_PUBLIC_ALIAS_P(_set_abort_behavior,libc__set_abort_behavior,,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int flags, unsigned int mask),(flags,mask));
DEFINE_PUBLIC_ALIAS_P(_searchenv_s,libc__searchenv_s,ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4),errno_t,NOTHROW_RPC,LIBCCALL,(char const *file, char const *envvar, char *__restrict resultpath, size_t resultpath_len),(file,envvar,resultpath,resultpath_len));
DEFINE_PUBLIC_ALIAS_P_VOID(_seterrormode,libc__seterrormode,,NOTHROW_NCX,LIBCCALL,(int mode),(mode));
DEFINE_PUBLIC_ALIAS_P(_set_error_mode,libc__set_error_mode,,int,NOTHROW_NCX,LIBCCALL,(int mode),(mode));
DEFINE_PUBLIC_ALIAS_P_VOID(_beep,libc__beep,,NOTHROW_NCX,LIBCCALL,(unsigned int freq, unsigned int duration),(freq,duration));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_onexit,libc_onexit,,onexit_t,NOTHROW_NCX,LIBCCALL,(onexit_t func),(func));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(onexit,libc_onexit,,onexit_t,NOTHROW_NCX,LIBCCALL,(onexit_t func),(func));
DEFINE_PUBLIC_ALIAS_P(DOS$_wgetenv,libd__wgetenv,WUNUSED ATTR_IN(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *varname),(varname));
DEFINE_PUBLIC_ALIAS_P(_wgetenv,libc__wgetenv,WUNUSED ATTR_IN(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *varname),(varname));
DEFINE_PUBLIC_ALIAS_P(DOS$_wputenv,libd__wputenv,ATTR_INOUT(1),int,NOTHROW_NCX,LIBDCALL,(char16_t *string),(string));
DEFINE_PUBLIC_ALIAS_P(_wputenv,libc__wputenv,ATTR_INOUT(1),int,NOTHROW_NCX,LIBKCALL,(char32_t *string),(string));
DEFINE_PUBLIC_ALIAS_P(DOS$_wputenv_s,libd__wputenv_s,,errno_t,NOTHROW_NCX,LIBDCALL,(char16_t const *varname, char16_t const *val),(varname,val));
DEFINE_PUBLIC_ALIAS_P(_wputenv_s,libc__wputenv_s,,errno_t,NOTHROW_NCX,LIBKCALL,(char32_t const *varname, char32_t const *val),(varname,val));
DEFINE_PUBLIC_ALIAS_P(DOS$_wsearchenv_s,libd__wsearchenv_s,ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4),errno_t,NOTHROW_RPC,LIBDCALL,(char16_t const *file, char16_t const *envvar, char16_t *__restrict resultpath, size_t resultpath_len),(file,envvar,resultpath,resultpath_len));
DEFINE_PUBLIC_ALIAS_P(_wsearchenv_s,libc__wsearchenv_s,ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4),errno_t,NOTHROW_RPC,LIBKCALL,(char32_t const *file, char32_t const *envvar, char32_t *__restrict resultpath, size_t resultpath_len),(file,envvar,resultpath,resultpath_len));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STDLIB_C */
