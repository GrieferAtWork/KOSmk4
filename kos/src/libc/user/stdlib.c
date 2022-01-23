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
#ifndef GUARD_LIBC_USER_STDLIB_C
#define GUARD_LIBC_USER_STDLIB_C 1

#include "../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-once.h>
#include <hybrid/sync/atomic-rwlock.h>
#include <hybrid/unaligned.h>

#include <kos/exec/idata.h>
#include <kos/exec/peb.h>
#include <kos/syscalls.h>
#include <sys/auxv.h>
#include <sys/wait.h>

#include <assert.h>
#include <fcntl.h>
#include <limits.h>
#include <malloc.h>
#include <malloca.h>
#include <sched.h>
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
INTERN WUNUSED ATTR_CONST ATTR_RETNONNULL ATTR_SECTION(".text.crt.dos.fs.environ")
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
#define environ_endread()    (void)(atomic_rwlock_endread(&libc_environ_lock) && (environ_reap(), 0))
#define _environ_end()       atomic_rwlock_end(&libc_environ_lock)
#define environ_end()        (void)(atomic_rwlock_end(&libc_environ_lock) && (environ_reap(), 0))
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

LOCAL ATTR_SECTION(".text.crt.fs.environ.heap")
bool LIBCCALL environ_remove_heapstring_locked(struct environ_heapstr *ptr) {
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


/* TODO: Add support for: __cxa_thread_atexit */
/* TODO: Add support for: __cxa_thread_atexit_impl  */
DEFINE_PUBLIC_ALIAS(__cxa_atexit, libc___cxa_atexit);

INTERN ATTR_SECTION(".text.crt.sched.process") int
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
		 * As such, we can make use of  `dlgethandle()' in order to look-up the  associated
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
		new_seed = old_seed = ATOMIC_READ(*pseed);
		new_seed = (((new_seed + 7) << 1) / 3);
		new_seed ^= rand_map[(new_seed >> (new_seed & 7)) % COMPILER_LENOF(rand_map)];
	} while (!ATOMIC_CMPXCH_WEAK(*pseed, old_seed, new_seed));
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

/*[[[head:libc_rand_r,hash:CRC-32=0x50bd9f7e]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1)) int
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





/*[[[head:libc_getenv,hash:CRC-32=0x5a7650b6]]]*/
INTERN ATTR_SECTION(".text.crt.fs.environ") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_getenv)(char const *varname)
/*[[[body:libc_getenv]]]*/
{
	char *result, **envp;
	if unlikely(!varname)
		return NULL;
	environ_read();
	envp = environ;
	if unlikely(!envp)
		result = NULL;
	else {
		size_t namelen = strlen(varname);
#ifdef __OPTIMIZE_SIZE__
		for (; (result = *envp) != NULL; ++envp) {
			if (memcmp(result, varname, namelen * sizeof(char)) != 0)
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
		 * As far as portability goes, gLibc makes the same assumption. */
		if unlikely(!namelen)
			result = NULL;
		else {
			pattern.word = UNALIGNED_GET16((uint16_t const *)varname);
			if unlikely(namelen == 1) {
				/* Single-character variable name -> Only need to search for
				 * that specific character,  as well as  the follow-up  '='! */
				pattern.chr[1] = '=';
				for (; (result = *envp) != NULL; ++envp) {
					if (UNALIGNED_GET16((uint16_t const *)result) != pattern.word)
						continue;
					result += 2;
					break;
				}
			} else {
				size_t tail_namelen;
				varname += 2;
				tail_namelen = namelen - 2;
				for (; (result = *envp) != NULL; ++envp) {
					if (UNALIGNED_GET16((uint16_t const *)result) != pattern.word)
						continue; /* First 2 characters don't match. */
					if (memcmp(result + 2, varname, tail_namelen * sizeof(char)) != 0)
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




/*[[[head:libc_setenv,hash:CRC-32=0x4507caac]]]*/
INTERN ATTR_SECTION(".text.crt.fs.environ") NONNULL((1, 2)) int
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
			if (memcmp(existing_line, line->ehs_text, (namelen + 1) * sizeof(char)) != 0)
				continue;
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

/*[[[head:libc_unsetenv,hash:CRC-32=0x823d2ab5]]]*/
INTERN ATTR_SECTION(".text.crt.fs.environ") NONNULL((1)) int
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
			if (memcmp(existing_line, varname, namelen * sizeof(char)) != 0 ||
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

/*[[[head:libc_putenv,hash:CRC-32=0x9816a81b]]]*/
INTERN ATTR_SECTION(".text.crt.fs.environ") NONNULL((1)) int
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
			if (memcmp(existing_line, string, (namelen + 1) * sizeof(char)) != 0)
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

/*[[[head:libc_secure_getenv,hash:CRC-32=0x43530c7b]]]*/
INTERN ATTR_SECTION(".text.crt.fs.environ") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_secure_getenv)(char const *varname)
/*[[[body:libc_secure_getenv]]]*/
{
	if (getauxval(AT_SECURE))
		return NULL; /* Unconditionally return `NULL' for setuid() programs */
	return libc_getenv(varname);
}
/*[[[end:libc_secure_getenv]]]*/








/************************************************************************/
/* DOS ENVIRON HANDLING                                                 */
/************************************************************************/

DEFINE_PUBLIC_ALIAS(DOS$__p__environ, libd_p_environ);
DEFINE_PUBLIC_IDATA_G(DOS$environ, libd_p_environ, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA_G(DOS$_environ, libd_p_environ, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA_G(DOS$__environ, libd_p_environ, __SIZEOF_POINTER__);
INTERN WUNUSED ATTR_CONST ATTR_RETNONNULL ATTR_SECTION(".text.crt.dos.fs.environ")
char ***NOTHROW(LIBDCALL libd_p_environ)(void) {
	/* TODO: Special handling for certain variables. */
	return libc_p_environ();
}

/*[[[head:libd_getenv,hash:CRC-32=0x6479cc27]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_getenv)(char const *varname)
/*[[[body:libd_getenv]]]*/
{
	/* TODO: Special handling for certain variables. */
	return libc_getenv(varname);
}
/*[[[end:libd_getenv]]]*/

/*[[[head:libd_setenv,hash:CRC-32=0xb2e0dbfc]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_setenv)(char const *varname,
                                  char const *val,
                                  int replace)
/*[[[body:libd_setenv]]]*/
{
	/* TODO: Special handling for certain variables. */
	return libc_setenv(varname, val, replace);
}
/*[[[end:libd_setenv]]]*/

/*[[[head:libd_unsetenv,hash:CRC-32=0x656808f6]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_unsetenv)(char const *varname)
/*[[[body:libd_unsetenv]]]*/
{
	/* TODO: Special handling for certain variables. */
	return libc_unsetenv(varname);
}
/*[[[end:libd_unsetenv]]]*/

/*[[[head:libd___p__wenviron,hash:CRC-32=0xf111074f]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***
NOTHROW_NCX(LIBDCALL libd___p__wenviron)(void)
/*[[[body:libd___p__wenviron]]]*/
{
	/* TODO: Special handling for certain variables. */
	CRT_UNIMPLEMENTED("DOS$__p__wenviron"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd___p__wenviron]]]*/

/*[[[head:libc___p__wenviron,hash:CRC-32=0x6f0d52ce]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***
NOTHROW_NCX(LIBKCALL libc___p__wenviron)(void)
/*[[[body:libc___p__wenviron]]]*/
{
	/* TODO: Special handling for certain variables. */
	CRT_UNIMPLEMENTED("__p__wenviron"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p__wenviron]]]*/

/*[[[head:libd___p___winitenv,hash:CRC-32=0xbaabf17d]]]*/
/* Access to the initial environment block */
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***
NOTHROW_NCX(LIBDCALL libd___p___winitenv)(void)
/*[[[body:libd___p___winitenv]]]*/
{
	/* TODO: Special handling for certain variables. */
	CRT_UNIMPLEMENTED("DOS$__p___winitenv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd___p___winitenv]]]*/

/*[[[head:libc___p___winitenv,hash:CRC-32=0x208a5e9e]]]*/
/* Access to the initial environment block */
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***
NOTHROW_NCX(LIBKCALL libc___p___winitenv)(void)
/*[[[body:libc___p___winitenv]]]*/
{
	/* TODO: Special handling for certain variables. */
	CRT_UNIMPLEMENTED("__p___winitenv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p___winitenv]]]*/


#undef _wenviron
#undef __winitenv
DEFINE_PUBLIC_IDATA_G(_wenviron, libc___p__wenviron, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA_G(DOS$_wenviron, libd___p__wenviron, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA_G(__winitenv, libc___p___winitenv, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA_G(DOS$__winitenv, libd___p___winitenv, __SIZEOF_POINTER__);
/************************************************************************/





/*[[[head:libc__wgetenv,hash:CRC-32=0x47d36374]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc__wgetenv)(char32_t const *varname)
/*[[[body:libc__wgetenv]]]*/
{
	static ATTR_SECTION(".bss.crt.dos.wchar.fs.environ") char32_t *last_c32getenv = NULL;
	char *utf8_varname, *utf8_varval;
	char32_t *c32_varval;
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

/*[[[head:libd__wgetenv,hash:CRC-32=0xa7845fca]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd__wgetenv)(char16_t const *varname)
/*[[[body:libd__wgetenv]]]*/
{
	static ATTR_SECTION(".bss.crt.dos.wchar.fs.environ") char16_t *last_c16getenv = NULL;
	char *utf8_varname, *utf8_varval;
	char16_t *c16_varval;
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

/*[[[head:libd_putenv,hash:CRC-32=0x2ddbec6f]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") NONNULL((1)) int
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

/*[[[head:libd_secure_getenv,hash:CRC-32=0xf2ecbf88]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_secure_getenv)(char const *varname)
/*[[[body:libd_secure_getenv]]]*/
{
	if (getauxval(AT_SECURE))
		return NULL; /* Unconditionally return `NULL' for setuid() programs */
	return libd_getenv(varname);
}
/*[[[end:libd_secure_getenv]]]*/

/*[[[head:libd__wputenv,hash:CRC-32=0x2ede1d24]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd__wputenv)(char16_t *string)
/*[[[body:libd__wputenv]]]*/
{
	int result;
	char *utf8 = convert_c16tombs(string);
	if (!utf8)
		return -1;
	result = libd_putenv(utf8);
	free(utf8);
	return result;
}
/*[[[end:libd__wputenv]]]*/

/*[[[head:libc__wputenv,hash:CRC-32=0x913e79b2]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc__wputenv)(char32_t *string)
/*[[[body:libc__wputenv]]]*/
{
	int result;
	char *eq;
	char *utf8 = convert_c32tombs(string);
	if (!utf8)
		return -1;
	eq = strchr(utf8, '=');
	if (!eq)
		result = libc_unsetenv(utf8);
	else {
		*eq++ = '\0';
		result = libc_setenv(utf8, eq, 1);
	}
	free(utf8);
	return result;
}
/*[[[end:libc__wputenv]]]*/

/*[[[head:libd__wputenv_s,hash:CRC-32=0x985727da]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") errno_t
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
	return result;
/*err_val:
	free(utf8_val);*/
err_varname:
	free(utf8_varname);
err:
	return libc_geterrno();
}
/*[[[end:libc__wputenv_s]]]*/






/*[[[head:libc__searchenv_s,hash:CRC-32=0x46622a54]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1, 2, 3)) errno_t
NOTHROW_RPC(LIBCCALL libc__searchenv_s)(char const *file,
                                        char const *envvar,
                                        char *__restrict resultpath,
                                        size_t buflen)
/*[[[body:libc__searchenv_s]]]*/
/*AUTO*/{
	(void)file;
	(void)envvar;
	(void)resultpath;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("_searchenv_s(%q, %q, %q, %Ix)", file, envvar, resultpath, buflen); /* TODO */
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
	ATOMIC_WRITE(atexit_vector.av_stat, status);
	atomic_rwlock_read(&atexit_vector.av_lock);
	length = ATOMIC_XCH(atexit_vector.av_size, 0);
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
		if (atomic_rwlock_reading(&atexit_vector.av_lock)) {
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

/*[[[head:libd_on_exit,hash:CRC-32=0xc3379334]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
INTERN ATTR_SECTION(".text.crt.dos.sched.process") NONNULL((1)) int
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
	ATOMIC_WRITE(atexit_vector.av_stat, status);
	atomic_rwlock_read(&atexit_vector.av_lock);
	length = ATOMIC_XCH(at_quick_exit_vector.aqv_size, 0);
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
		if (atomic_rwlock_reading(&atexit_vector.av_lock)) {
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

/*[[[head:libc_exit,hash:CRC-32=0xc5fc2590]]]*/
INTERN ATTR_SECTION(".text.crt.application.exit") ATTR_NORETURN void
(LIBCCALL libc_exit)(int status) THROWS(...)
/*[[[body:libc_exit]]]*/
{
	/* Finalizer TLS objects for the calling thread (c++11-specific) */
	dlauxctrl(NULL, DLAUXCTRL_RUNTLSFINI, NULL, NULL);
	/* Run functions registered with `atexit()' or `on_exit()'. */
	libc_run_atexit(status);
	/* Run library finalizers (NOTE: This will also call back to invoke
	 * `libc_fini()' because libc  is compiled with  `-fini=libc_fini') */
	dlauxctrl(NULL, DLAUXCTRL_RUNFINI, NULL, NULL);
	_Exit(status);
}
/*[[[end:libc_exit]]]*/

/*[[[head:libc_quick_exit,hash:CRC-32=0x66efab6c]]]*/
INTERN ATTR_SECTION(".text.crt.sched.process") ATTR_NORETURN void
(LIBCCALL libc_quick_exit)(int status) THROWS(...)
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

/*[[[head:libc__Exit,hash:CRC-32=0x57701208]]]*/
INTERN ATTR_SECTION(".text.crt.application.exit") ATTR_NORETURN void
(LIBCCALL libc__Exit)(int status) THROWS(...)
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
	CRT_UNIMPLEMENTEDF("drand48_r(%p, %p)", buffer, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("erand48_r(%p, %p, %p)", xsubi, buffer, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("lrand48_r(%p, %p)", buffer, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("nrand48_r(%p, %p, %p)", xsubi, buffer, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("mrand48_r(%p, %p)", buffer, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("jrand48_r(%p, %p, %p)", xsubi, buffer, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("srand48_r(%lx, %p)", seedval, buffer); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("seed48_r(%p, %p)", seed16v, buffer); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("lcong48_r(%p, %p)", param, buffer); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("random_r(%p, %p)", buf, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("srandom_r(%x, %p)", seed, buf); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("initstate_r(%x, %q, %Ix, %p)", seed, statebuf, statelen, buf); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("setstate_r(%q, %p)", statebuf, buf); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("getloadavg(%p, %x)", loadavg, nelem); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getloadavg]]]*/

/*[[[head:libc_drand48,hash:CRC-32=0x154b0864]]]*/
INTERN ATTR_SECTION(".text.crt.random") double
NOTHROW_NCX(LIBCCALL libc_drand48)(void)
/*[[[body:libc_drand48]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("drand48"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_drand48]]]*/

/*[[[head:libc_lrand48,hash:CRC-32=0x3d0384e2]]]*/
INTERN ATTR_SECTION(".text.crt.random") long
NOTHROW_NCX(LIBCCALL libc_lrand48)(void)
/*[[[body:libc_lrand48]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("lrand48"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_lrand48]]]*/

/*[[[head:libc_mrand48,hash:CRC-32=0x84f85f0a]]]*/
INTERN ATTR_SECTION(".text.crt.random") long
NOTHROW_NCX(LIBCCALL libc_mrand48)(void)
/*[[[body:libc_mrand48]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("mrand48"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_mrand48]]]*/

/*[[[head:libc_erand48,hash:CRC-32=0xcacb6009]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1)) double
NOTHROW_NCX(LIBCCALL libc_erand48)(unsigned short xsubi[3])
/*[[[body:libc_erand48]]]*/
/*AUTO*/{
	(void)xsubi;
	CRT_UNIMPLEMENTEDF("erand48(%p)", xsubi); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_erand48]]]*/

/*[[[head:libc_nrand48,hash:CRC-32=0xf0cd3639]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1)) long
NOTHROW_NCX(LIBCCALL libc_nrand48)(unsigned short xsubi[3])
/*[[[body:libc_nrand48]]]*/
/*AUTO*/{
	(void)xsubi;
	CRT_UNIMPLEMENTEDF("nrand48(%p)", xsubi); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_nrand48]]]*/

/*[[[head:libc_jrand48,hash:CRC-32=0x62c472e1]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1)) long
NOTHROW_NCX(LIBCCALL libc_jrand48)(unsigned short xsubi[3])
/*[[[body:libc_jrand48]]]*/
/*AUTO*/{
	(void)xsubi;
	CRT_UNIMPLEMENTEDF("jrand48(%p)", xsubi); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_jrand48]]]*/

/*[[[head:libc_srand48,hash:CRC-32=0x1c9c73b7]]]*/
INTERN ATTR_SECTION(".text.crt.random") void
NOTHROW_NCX(LIBCCALL libc_srand48)(long seedval)
/*[[[body:libc_srand48]]]*/
/*AUTO*/{
	(void)seedval;
	CRT_UNIMPLEMENTEDF("srand48(%lx)", seedval); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_srand48]]]*/

/*[[[head:libc_seed48,hash:CRC-32=0x65a13274]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1)) unsigned short *
NOTHROW_NCX(LIBCCALL libc_seed48)(unsigned short seed16v[3])
/*[[[body:libc_seed48]]]*/
/*AUTO*/{
	(void)seed16v;
	CRT_UNIMPLEMENTEDF("seed48(%p)", seed16v); /* TODO */
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
	CRT_UNIMPLEMENTEDF("lcong48(%p)", param); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_lcong48]]]*/

/*[[[head:libc_initstate,hash:CRC-32=0x3f377d70]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_initstate)(unsigned int seed,
                                     char *statebuf,
                                     size_t statelen)
/*[[[body:libc_initstate]]]*/
/*AUTO*/{
	(void)seed;
	(void)statebuf;
	(void)statelen;
	CRT_UNIMPLEMENTEDF("initstate(%x, %q, %Ix)", seed, statebuf, statelen); /* TODO */
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
	CRT_UNIMPLEMENTEDF("setstate(%q)", statebuf); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_setstate]]]*/

/*[[[head:libd_realpath,hash:CRC-32=0xe61a4788]]]*/
/* Load the filesystem location of a given file handle.
 * This  function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL  to automatically `malloc()'ate  and return  a
 *                   buffer of sufficient size. */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED NONNULL((1)) char *
NOTHROW_RPC(LIBDCALL libd_realpath)(char const *filename,
                                    char *resolved)
/*[[[body:libd_realpath]]]*/
{
	return libc_frealpathat(AT_FDCWD, filename, resolved,
	                        resolved ? PATH_MAX : 0, AT_DOSPATH);
}
/*[[[end:libd_realpath]]]*/

/*[[[head:libc_realpath,hash:CRC-32=0x124eed81]]]*/
/* Load the filesystem location of a given file handle.
 * This  function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL  to automatically `malloc()'ate  and return  a
 *                   buffer of sufficient size. */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED NONNULL((1)) char *
NOTHROW_RPC(LIBCCALL libc_realpath)(char const *filename,
                                    char *resolved)
/*[[[body:libc_realpath]]]*/
{
	return libc_frealpathat(AT_FDCWD, filename, resolved,
	                        resolved ? PATH_MAX : 0, 0);
}
/*[[[end:libc_realpath]]]*/

/*[[[head:libd_frealpath,hash:CRC-32=0xa79bd98]]]*/
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED char *
NOTHROW_RPC(LIBDCALL libd_frealpath)(fd_t fd,
                                     char *resolved,
                                     size_t buflen)
/*[[[body:libd_frealpath]]]*/
{
	return libc_frealpath4(fd, resolved, buflen, AT_DOSPATH);
}
/*[[[end:libd_frealpath]]]*/

/*[[[head:libc_frealpath,hash:CRC-32=0x56ec606d]]]*/
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_frealpath)(fd_t fd,
                                     char *resolved,
                                     size_t buflen)
/*[[[body:libc_frealpath]]]*/
{
	return libc_frealpath4(fd, resolved, buflen, 0);
}
/*[[[end:libc_frealpath]]]*/

/*[[[head:libd_frealpath4,hash:CRC-32=0xb9506afa]]]*/
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0 | AT_ALTPATH | AT_DOSPATH'
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED char *
NOTHROW_RPC(LIBDCALL libd_frealpath4)(fd_t fd,
                                      char *resolved,
                                      size_t buflen,
                                      atflag_t flags)
/*[[[body:libd_frealpath4]]]*/
{
	return libc_frealpath4(fd, resolved, buflen, flags | AT_DOSPATH);
}
/*[[[end:libd_frealpath4]]]*/

/*[[[head:libc_frealpath4,hash:CRC-32=0x6655b46f]]]*/
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0 | AT_ALTPATH | AT_DOSPATH'
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED char *
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

/*[[[head:libd_frealpathat,hash:CRC-32=0x4d90df47]]]*/
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is not dereferenced,
 * causing the path to  the symlink itself to  be printed. - Otherwise,  the
 * file pointed to by the symblic link is printed.
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size.
 * @param flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
 * @return: NULL: [errno=ERANGE]: `buflen' is too small to fit the entire path */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED NONNULL((2)) char *
NOTHROW_RPC(LIBDCALL libd_frealpathat)(fd_t dirfd,
                                       char const *filename,
                                       char *resolved,
                                       size_t buflen,
                                       atflag_t flags)
/*[[[body:libd_frealpathat]]]*/
{
	return libc_frealpathat(dirfd, filename, resolved, buflen, flags | AT_DOSPATH);
}
/*[[[end:libd_frealpathat]]]*/

/*[[[head:libc_frealpathat,hash:CRC-32=0xe792b5bd]]]*/
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is not dereferenced,
 * causing the path to  the symlink itself to  be printed. - Otherwise,  the
 * file pointed to by the symblic link is printed.
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size.
 * @param flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
 * @return: NULL: [errno=ERANGE]: `buflen' is too small to fit the entire path */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED NONNULL((2)) char *
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

/*[[[head:libc_grantpt,hash:CRC-32=0xd1e26f46]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_grantpt)(fd_t fd)
/*[[[body:libc_grantpt]]]*/
/*AUTO*/{
	(void)fd;
	CRT_UNIMPLEMENTEDF("grantpt(%" PRIxN(__SIZEOF_FD_T__) ")", fd); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_grantpt]]]*/



/*[[[head:libc_posix_openpt,hash:CRC-32=0x9f0949e1]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED fd_t
NOTHROW_RPC(LIBCCALL libc_posix_openpt)(oflag_t oflags)
/*[[[body:libc_posix_openpt]]]*/
/*AUTO*/{
	(void)oflags;
	CRT_UNIMPLEMENTEDF("posix_openpt(%" PRIxN(__SIZEOF_OFLAG_T__) ")", oflags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_openpt]]]*/

/*[[[head:libd_ptsname_r,hash:CRC-32=0xdd2f3f26]]]*/
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_ptsname_r)(fd_t fd,
                                     char *buf,
                                     size_t buflen)
/*[[[body:libd_ptsname_r]]]*/
/*AUTO*/{
	(void)fd;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("ptsname_r(%" PRIxN(__SIZEOF_FD_T__) ", %q, %Ix)", fd, buf, buflen); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd_ptsname_r]]]*/

/*[[[head:libc_ptsname_r,hash:CRC-32=0xfab75b90]]]*/
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_ptsname_r)(fd_t fd,
                                     char *buf,
                                     size_t buflen)
/*[[[body:libc_ptsname_r]]]*/
/*AUTO*/{
	(void)fd;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("ptsname_r(%" PRIxN(__SIZEOF_FD_T__) ", %q, %Ix)", fd, buf, buflen); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ptsname_r]]]*/

/*[[[head:libc_getpt,hash:CRC-32=0x3ef69a1d]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_RPC(LIBCCALL libc_getpt)(void)
/*[[[body:libc_getpt]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getpt"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getpt]]]*/

/*[[[head:libd_canonicalize_file_name,hash:CRC-32=0x640e6ae]]]*/
/* Return the result of `realpath(filename)' as a `malloc()'-allocated buffer
 * Upon error, `NULL' is returned instead */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") ATTR_MALLOC WUNUSED NONNULL((1)) char *
NOTHROW_RPC(LIBDCALL libd_canonicalize_file_name)(char const *filename)
/*[[[body:libd_canonicalize_file_name]]]*/
{
	return libd_realpath(filename, NULL);
}
/*[[[end:libd_canonicalize_file_name]]]*/

/*[[[head:libc_canonicalize_file_name,hash:CRC-32=0xf563004a]]]*/
/* Return the result of `realpath(filename)' as a `malloc()'-allocated buffer
 * Upon error, `NULL' is returned instead */
INTERN ATTR_SECTION(".text.crt.fs.property") ATTR_MALLOC WUNUSED NONNULL((1)) char *
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

/*[[[head:libc___p___argc,hash:CRC-32=0x247bbd5d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED int *
NOTHROW_NCX(LIBCCALL libc___p___argc)(void)
/*[[[body:libc___p___argc]]]*/
{
	return &__argc;
}
/*[[[end:libc___p___argc]]]*/

/*[[[head:libc___p___argv,hash:CRC-32=0xc89484f3]]]*/
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char ***
NOTHROW_NCX(LIBCCALL libc___p___argv)(void)
/*[[[body:libc___p___argv]]]*/
{
	return &__argv;
}
/*[[[end:libc___p___argv]]]*/


PRIVATE ATTR_CONST WUNUSED ATTR_SECTION(".text.crt.dos.application.init")
char **NOTHROW(libc_get_initenv)(void) {
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
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init")
struct atomic_once libc___p___initenv_initialized = ATOMIC_ONCE_INIT;

#undef __initenv
DEFINE_PUBLIC_IDATA_G(__initenv, libc___p___initenv, __SIZEOF_POINTER__);

/*[[[head:libc___p___initenv,hash:CRC-32=0x2f3a191d]]]*/
/* Access to the initial environment block */
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") ATTR_CONST ATTR_RETNONNULL WUNUSED char ***
NOTHROW_NCX(LIBCCALL libc___p___initenv)(void)
/*[[[body:libc___p___initenv]]]*/
{
	ATOMIC_ONCE_RUN(&libc___p___initenv_initialized, {
		libc___p___initenv_pointer = libc_get_initenv();
	});
	return &libc___p___initenv_pointer;
}
/*[[[end:libc___p___initenv]]]*/

/*[[[head:libd___p___wargv,hash:CRC-32=0x61c5fc73]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***
NOTHROW_NCX(LIBDCALL libd___p___wargv)(void)
/*[[[body:libd___p___wargv]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("DOS$__p___wargv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd___p___wargv]]]*/

/*[[[head:libc___p___wargv,hash:CRC-32=0xa62e593b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***
NOTHROW_NCX(LIBKCALL libc___p___wargv)(void)
/*[[[body:libc___p___wargv]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p___wargv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p___wargv]]]*/

/*[[[head:libd___p__wpgmptr,hash:CRC-32=0xdf5a3664]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t **
NOTHROW_NCX(LIBDCALL libd___p__wpgmptr)(void)
/*[[[body:libd___p__wpgmptr]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("DOS$__p__wpgmptr"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd___p__wpgmptr]]]*/

/*[[[head:libc___p__wpgmptr,hash:CRC-32=0xc65340b2]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t **
NOTHROW_NCX(LIBKCALL libc___p__wpgmptr)(void)
/*[[[body:libc___p__wpgmptr]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p__wpgmptr"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p__wpgmptr]]]*/

/*[[[head:libc__fullpath,hash:CRC-32=0x78797651]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") char *
NOTHROW_RPC(LIBCCALL libc__fullpath)(char *buf,
                                     char const *path,
                                     size_t buflen)
/*[[[body:libc__fullpath]]]*/
{
	return frealpathat(AT_FDCWD, path, buf, buflen, AT_DOSPATH);
}
/*[[[end:libc__fullpath]]]*/

/* All of these are implemented in libc/libc/errno.c */
/*[[[skip:libc___doserrno]]]*/

/*[[[head:libd__get_errno,hash:CRC-32=0x89478bd0]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno_access") errno_t
NOTHROW_NCX(LIBDCALL libd__get_errno)(errno_t *perr)
/*[[[body:libd__get_errno]]]*/
{
	if (!perr)
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
	if (!perr)
		return EINVAL;
	*perr = libd_geterrno();
	return EOK;
}
/*[[[end:libc__get_errno]]]*/

/*[[[head:libd__set_errno,hash:CRC-32=0xd9d75bda]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno_access") errno_t
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

/*[[[head:libd__get_doserrno,hash:CRC-32=0xbb969dc6]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") errno_t
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
	CRT_UNIMPLEMENTEDF("_seterrormode(%x)", mode); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__seterrormode]]]*/

/*[[[head:libc__set_error_mode,hash:CRC-32=0x2437863d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") int
NOTHROW_NCX(LIBCCALL libc__set_error_mode)(int mode)
/*[[[body:libc__set_error_mode]]]*/
/*AUTO*/{
	(void)mode;
	CRT_UNIMPLEMENTEDF("_set_error_mode(%x)", mode); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("_beep(%x, %x)", freq, duration); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__beep]]]*/

/*[[[head:libc__set_purecall_handler,hash:CRC-32=0xa0356abb]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") _purecall_handler
NOTHROW_NCX(LIBCCALL libc__set_purecall_handler)(_purecall_handler __handler)
/*[[[body:libc__set_purecall_handler]]]*/
/*AUTO*/{
	(void)__handler;
	CRT_UNIMPLEMENTEDF("_set_purecall_handler(%p)", __handler); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__set_purecall_handler]]]*/

/*[[[head:libc__get_purecall_handler,hash:CRC-32=0x47e9bd6f]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") _purecall_handler
NOTHROW_NCX(LIBCCALL libc__get_purecall_handler)(void)
/*[[[body:libc__get_purecall_handler]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_get_purecall_handler"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__get_purecall_handler]]]*/

/*[[[head:libc__set_invalid_parameter_handler,hash:CRC-32=0xdb334151]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") _invalid_parameter_handler
NOTHROW_NCX(LIBCCALL libc__set_invalid_parameter_handler)(_invalid_parameter_handler __handler)
/*[[[body:libc__set_invalid_parameter_handler]]]*/
/*AUTO*/{
	(void)__handler;
	CRT_UNIMPLEMENTEDF("_set_invalid_parameter_handler(%p)", __handler); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__set_invalid_parameter_handler]]]*/

/*[[[head:libc__get_invalid_parameter_handler,hash:CRC-32=0x31cb9fb2]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") _invalid_parameter_handler
NOTHROW_NCX(LIBCCALL libc__get_invalid_parameter_handler)(void)
/*[[[body:libc__get_invalid_parameter_handler]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_get_invalid_parameter_handler"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__get_invalid_parameter_handler]]]*/

#undef _fmode
INTERN ATTR_SECTION(".bss.crt.dos.FILE.utility") int libd__fmode = 0;
DEFINE_PUBLIC_ALIAS(_fmode, libd__fmode);

/*[[[head:libc___p__fmode,hash:CRC-32=0x75afe2d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") ATTR_CONST ATTR_RETNONNULL WUNUSED int *
NOTHROW_NCX(LIBCCALL libc___p__fmode)(void)
/*[[[body:libc___p__fmode]]]*/
{
	return &libd__fmode;
}
/*[[[end:libc___p__fmode]]]*/

/*[[[head:libc__set_fmode,hash:CRC-32=0xba018643]]]*/
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") errno_t
NOTHROW_NCX(LIBCCALL libc__set_fmode)(int mode)
/*[[[body:libc__set_fmode]]]*/
{
	libd__fmode = mode;
	return EOK;
}
/*[[[end:libc__set_fmode]]]*/

/*[[[head:libc__get_fmode,hash:CRC-32=0xce6fa140]]]*/
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") errno_t
NOTHROW_NCX(LIBCCALL libc__get_fmode)(int *pmode)
/*[[[body:libc__get_fmode]]]*/
{
	*pmode = libd__fmode;
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
	CRT_UNIMPLEMENTEDF("_set_abort_behavior(%x, %x)", flags, mask); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__set_abort_behavior]]]*/




/*[[[head:libd__wfullpath,hash:CRC-32=0x8506fc61]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") char16_t *
NOTHROW_NCX(LIBDCALL libd__wfullpath)(char16_t *buf,
                                      char16_t const *path,
                                      size_t buflen)
/*[[[body:libd__wfullpath]]]*/
/*AUTO*/{
	(void)buf;
	(void)path;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("DOS$_wfullpath(%p, %p, %Ix)", buf, path, buflen); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__wfullpath]]]*/

/*[[[head:libc__wfullpath,hash:CRC-32=0xe620b50]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") char32_t *
NOTHROW_NCX(LIBKCALL libc__wfullpath)(char32_t *buf,
                                      char32_t const *path,
                                      size_t buflen)
/*[[[body:libc__wfullpath]]]*/
/*AUTO*/{
	(void)buf;
	(void)path;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("_wfullpath(%p, %p, %Ix)", buf, path, buflen); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wfullpath]]]*/

/*[[[head:libd__wsearchenv_s,hash:CRC-32=0x39e33fd3]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1, 2, 3)) errno_t
NOTHROW_RPC(LIBDCALL libd__wsearchenv_s)(char16_t const *file,
                                         char16_t const *envvar,
                                         char16_t *__restrict resultpath,
                                         size_t buflen)
/*[[[body:libd__wsearchenv_s]]]*/
/*AUTO*/{
	(void)file;
	(void)envvar;
	(void)resultpath;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("DOS$_wsearchenv_s(%p, %p, %p, %Ix)", file, envvar, resultpath, buflen); /* TODO */
	return ENOSYS;
}
/*[[[end:libd__wsearchenv_s]]]*/

/*[[[head:libc__wsearchenv_s,hash:CRC-32=0x3e9d5b1]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1, 2, 3)) errno_t
NOTHROW_RPC(LIBKCALL libc__wsearchenv_s)(char32_t const *file,
                                         char32_t const *envvar,
                                         char32_t *__restrict resultpath,
                                         size_t buflen)
/*[[[body:libc__wsearchenv_s]]]*/
/*AUTO*/{
	(void)file;
	(void)envvar;
	(void)resultpath;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("_wsearchenv_s(%p, %p, %p, %Ix)", file, envvar, resultpath, buflen); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__wsearchenv_s]]]*/





/*[[[head:libc_radixsort,hash:CRC-32=0xfedeeb47]]]*/
INTERN ATTR_SECTION(".text.crt.bsd") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_radixsort)(unsigned char const **base,
                                     int item_count,
                                     unsigned char const *table,
                                     unsigned endbyte)
/*[[[body:libc_radixsort]]]*/
/*AUTO*/{
	(void)base;
	(void)item_count;
	(void)table;
	(void)endbyte;
	CRT_UNIMPLEMENTEDF("radixsort(%p, %x, %p, %x)", base, item_count, table, endbyte); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_radixsort]]]*/

/*[[[head:libc_sradixsort,hash:CRC-32=0xd2fec85]]]*/
INTERN ATTR_SECTION(".text.crt.bsd") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sradixsort)(unsigned char const **base,
                                      int item_count,
                                      unsigned char const *table,
                                      unsigned endbyte)
/*[[[body:libc_sradixsort]]]*/
/*AUTO*/{
	(void)base;
	(void)item_count;
	(void)table;
	(void)endbyte;
	CRT_UNIMPLEMENTEDF("sradixsort(%p, %x, %p, %x)", base, item_count, table, endbyte); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_sradixsort]]]*/

/*[[[head:libc_getbsize,hash:CRC-32=0x7815d4f]]]*/
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_getbsize)(int *headerlenp,
                                    __LONGPTR_TYPE__ *blocksizep)
/*[[[body:libc_getbsize]]]*/
/*AUTO*/{
	(void)headerlenp;
	(void)blocksizep;
	CRT_UNIMPLEMENTEDF("getbsize(%p, %p)", headerlenp, blocksizep); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getbsize]]]*/

/*[[[head:libc_devname_r,hash:CRC-32=0x4bcc89ac]]]*/
/* >> devname(3), devname_r(3) */
INTERN ATTR_SECTION(".text.crt.bsd") NONNULL((3)) int
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
	CRT_UNIMPLEMENTEDF("devname_r(%" PRIxN(__SIZEOF_DEV_T__) ", %" PRIxN(__SIZEOF_MODE_T__) ", %q, %Ix)", dev, type, buf, len); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("humanize_number(%q, %Ix, %" PRIx64 ", %q, %x, %x)", buf, len, bytes, suffix, scale, flags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTEDF("dehumanize_number(%q, %p)", str, size); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_dehumanize_number]]]*/

/*[[[head:libd_setproctitle,hash:CRC-32=0x1916f1eb]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
/* >> setproctitle(3) */
INTERN ATTR_SECTION(".text.crt.dos.bsd") ATTR_LIBC_PRINTF(1, 2) void
NOTHROW_NCX(VLIBDCALL libd_setproctitle)(char const *format,
                                         ...)
/*[[[body:libd_setproctitle]]]*/
/*AUTO*/{
	(void)format;
	CRT_UNIMPLEMENTED("setproctitle"); /* TODO */
	libc_seterrno(ENOSYS);
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_setproctitle]]]*/

/*[[[head:libc_setproctitle,hash:CRC-32=0x935ea57]]]*/
/* >> setproctitle(3) */
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_LIBC_PRINTF(1, 2) void
NOTHROW_NCX(VLIBCCALL libc_setproctitle)(char const *format,
                                         ...)
/*[[[body:libc_setproctitle]]]*/
/*AUTO*/{
	(void)format;
	CRT_UNIMPLEMENTED("setproctitle"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setproctitle]]]*/





/*[[[start:exports,hash:CRC-32=0x484cd6f5]]]*/
DEFINE_PUBLIC_ALIAS(DOS$getenv, libd_getenv);
DEFINE_PUBLIC_ALIAS(getenv, libc_getenv);
DEFINE_PUBLIC_ALIAS(exit, libc_exit);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_crt_atexit, libc_atexit);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(atexit, libc_atexit);
DEFINE_PUBLIC_ALIAS(quick_exit, libc_quick_exit);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_crt_at_quick_exit, libc_at_quick_exit);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(at_quick_exit, libc_at_quick_exit);
DEFINE_PUBLIC_ALIAS(_exit, libc__Exit);
DEFINE_PUBLIC_ALIAS(_Exit, libc__Exit);
DEFINE_PUBLIC_ALIAS(srand, libc_srand);
DEFINE_PUBLIC_ALIAS(rand, libc_rand);
DEFINE_PUBLIC_ALIAS(rand_r, libc_rand_r);
DEFINE_PUBLIC_ALIAS(drand48_r, libc_drand48_r);
DEFINE_PUBLIC_ALIAS(erand48_r, libc_erand48_r);
DEFINE_PUBLIC_ALIAS(lrand48_r, libc_lrand48_r);
DEFINE_PUBLIC_ALIAS(nrand48_r, libc_nrand48_r);
DEFINE_PUBLIC_ALIAS(mrand48_r, libc_mrand48_r);
DEFINE_PUBLIC_ALIAS(jrand48_r, libc_jrand48_r);
DEFINE_PUBLIC_ALIAS(srand48_r, libc_srand48_r);
DEFINE_PUBLIC_ALIAS(seed48_r, libc_seed48_r);
DEFINE_PUBLIC_ALIAS(lcong48_r, libc_lcong48_r);
DEFINE_PUBLIC_ALIAS(random_r, libc_random_r);
DEFINE_PUBLIC_ALIAS(srandom_r, libc_srandom_r);
DEFINE_PUBLIC_ALIAS(initstate_r, libc_initstate_r);
DEFINE_PUBLIC_ALIAS(setstate_r, libc_setstate_r);
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$on_exit, libd_on_exit);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(on_exit, libc_on_exit);
DEFINE_PUBLIC_ALIAS(clearenv, libc_clearenv);
DEFINE_PUBLIC_ALIAS(getloadavg, libc_getloadavg);
DEFINE_PUBLIC_ALIAS(DOS$setenv, libd_setenv);
DEFINE_PUBLIC_ALIAS(setenv, libc_setenv);
DEFINE_PUBLIC_ALIAS(DOS$unsetenv, libd_unsetenv);
DEFINE_PUBLIC_ALIAS(unsetenv, libc_unsetenv);
DEFINE_PUBLIC_ALIAS(drand48, libc_drand48);
DEFINE_PUBLIC_ALIAS(lrand48, libc_lrand48);
DEFINE_PUBLIC_ALIAS(mrand48, libc_mrand48);
DEFINE_PUBLIC_ALIAS(erand48, libc_erand48);
DEFINE_PUBLIC_ALIAS(nrand48, libc_nrand48);
DEFINE_PUBLIC_ALIAS(jrand48, libc_jrand48);
DEFINE_PUBLIC_ALIAS(srand48, libc_srand48);
DEFINE_PUBLIC_ALIAS(seed48, libc_seed48);
DEFINE_PUBLIC_ALIAS(lcong48, libc_lcong48);
DEFINE_PUBLIC_ALIAS(DOS$_putenv, libd_putenv);
DEFINE_PUBLIC_ALIAS(DOS$putenv, libd_putenv);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_putenv, libc_putenv);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(putenv, libc_putenv);
DEFINE_PUBLIC_ALIAS(__random, libc_random);
DEFINE_PUBLIC_ALIAS(random, libc_random);
DEFINE_PUBLIC_ALIAS(__srandom, libc_srandom);
DEFINE_PUBLIC_ALIAS(srandom, libc_srandom);
DEFINE_PUBLIC_ALIAS(__initstate, libc_initstate);
DEFINE_PUBLIC_ALIAS(initstate, libc_initstate);
DEFINE_PUBLIC_ALIAS(__setstate, libc_setstate);
DEFINE_PUBLIC_ALIAS(setstate, libc_setstate);
DEFINE_PUBLIC_ALIAS(DOS$realpath, libd_realpath);
DEFINE_PUBLIC_ALIAS(realpath, libc_realpath);
DEFINE_PUBLIC_ALIAS(DOS$frealpath, libd_frealpath);
DEFINE_PUBLIC_ALIAS(frealpath, libc_frealpath);
DEFINE_PUBLIC_ALIAS(DOS$frealpath4, libd_frealpath4);
DEFINE_PUBLIC_ALIAS(frealpath4, libc_frealpath4);
DEFINE_PUBLIC_ALIAS(DOS$frealpathat, libd_frealpathat);
DEFINE_PUBLIC_ALIAS(frealpathat, libc_frealpathat);
DEFINE_PUBLIC_ALIAS(grantpt, libc_grantpt);
DEFINE_PUBLIC_ALIAS(posix_openpt, libc_posix_openpt);
DEFINE_PUBLIC_ALIAS(DOS$ptsname_r, libd_ptsname_r);
DEFINE_PUBLIC_ALIAS(ptsname_r, libc_ptsname_r);
DEFINE_PUBLIC_ALIAS(DOS$__secure_getenv, libd_secure_getenv);
DEFINE_PUBLIC_ALIAS(DOS$__libc_secure_getenv, libd_secure_getenv);
DEFINE_PUBLIC_ALIAS(DOS$secure_getenv, libd_secure_getenv);
DEFINE_PUBLIC_ALIAS(__secure_getenv, libc_secure_getenv);
DEFINE_PUBLIC_ALIAS(__libc_secure_getenv, libc_secure_getenv);
DEFINE_PUBLIC_ALIAS(secure_getenv, libc_secure_getenv);
DEFINE_PUBLIC_ALIAS(getpt, libc_getpt);
DEFINE_PUBLIC_ALIAS(DOS$canonicalize_file_name, libd_canonicalize_file_name);
DEFINE_PUBLIC_ALIAS(canonicalize_file_name, libc_canonicalize_file_name);
DEFINE_PUBLIC_ALIAS(getbsize, libc_getbsize);
DEFINE_PUBLIC_ALIAS(radixsort, libc_radixsort);
DEFINE_PUBLIC_ALIAS(sradixsort, libc_sradixsort);
DEFINE_PUBLIC_ALIAS(devname_r, libc_devname_r);
DEFINE_PUBLIC_ALIAS(humanize_number, libc_humanize_number);
DEFINE_PUBLIC_ALIAS(dehumanize_number, libc_dehumanize_number);
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$setproctitle, libd_setproctitle);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(setproctitle, libc_setproctitle);
DEFINE_PUBLIC_ALIAS(DOS$_get_errno, libd__get_errno);
DEFINE_PUBLIC_ALIAS(_get_errno, libc__get_errno);
DEFINE_PUBLIC_ALIAS(DOS$_set_errno, libd__set_errno);
DEFINE_PUBLIC_ALIAS(_set_errno, libc__set_errno);
DEFINE_PUBLIC_ALIAS(DOS$_get_doserrno, libd__get_doserrno);
DEFINE_PUBLIC_ALIAS(_get_doserrno, libc__get_doserrno);
DEFINE_PUBLIC_ALIAS(_set_doserrno, libc__set_doserrno);
DEFINE_PUBLIC_ALIAS(__p___argc, libc___p___argc);
DEFINE_PUBLIC_ALIAS(__p___argv, libc___p___argv);
DEFINE_PUBLIC_ALIAS(DOS$__p___wargv, libd___p___wargv);
DEFINE_PUBLIC_ALIAS(__p___wargv, libc___p___wargv);
DEFINE_PUBLIC_ALIAS(DOS$__p__wenviron, libd___p__wenviron);
DEFINE_PUBLIC_ALIAS(__p__wenviron, libc___p__wenviron);
DEFINE_PUBLIC_ALIAS(DOS$__p__wpgmptr, libd___p__wpgmptr);
DEFINE_PUBLIC_ALIAS(__p__wpgmptr, libc___p__wpgmptr);
DEFINE_PUBLIC_ALIAS(__p___initenv, libc___p___initenv);
DEFINE_PUBLIC_ALIAS(DOS$__p___winitenv, libd___p___winitenv);
DEFINE_PUBLIC_ALIAS(__p___winitenv, libc___p___winitenv);
DEFINE_PUBLIC_ALIAS(_set_purecall_handler, libc__set_purecall_handler);
DEFINE_PUBLIC_ALIAS(_get_purecall_handler, libc__get_purecall_handler);
DEFINE_PUBLIC_ALIAS(_set_invalid_parameter_handler, libc__set_invalid_parameter_handler);
DEFINE_PUBLIC_ALIAS(_get_invalid_parameter_handler, libc__get_invalid_parameter_handler);
DEFINE_PUBLIC_ALIAS(__p__fmode, libc___p__fmode);
DEFINE_PUBLIC_ALIAS(_set_fmode, libc__set_fmode);
DEFINE_PUBLIC_ALIAS(_get_fmode, libc__get_fmode);
DEFINE_PUBLIC_ALIAS(_set_abort_behavior, libc__set_abort_behavior);
DEFINE_PUBLIC_ALIAS(_fullpath, libc__fullpath);
DEFINE_PUBLIC_ALIAS(_searchenv_s, libc__searchenv_s);
DEFINE_PUBLIC_ALIAS(_seterrormode, libc__seterrormode);
DEFINE_PUBLIC_ALIAS(_set_error_mode, libc__set_error_mode);
DEFINE_PUBLIC_ALIAS(_beep, libc__beep);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_onexit, libc_onexit);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(onexit, libc_onexit);
DEFINE_PUBLIC_ALIAS(DOS$_wgetenv, libd__wgetenv);
DEFINE_PUBLIC_ALIAS(_wgetenv, libc__wgetenv);
DEFINE_PUBLIC_ALIAS(DOS$_wfullpath, libd__wfullpath);
DEFINE_PUBLIC_ALIAS(_wfullpath, libc__wfullpath);
DEFINE_PUBLIC_ALIAS(DOS$_wputenv, libd__wputenv);
DEFINE_PUBLIC_ALIAS(_wputenv, libc__wputenv);
DEFINE_PUBLIC_ALIAS(DOS$_wputenv_s, libd__wputenv_s);
DEFINE_PUBLIC_ALIAS(_wputenv_s, libc__wputenv_s);
DEFINE_PUBLIC_ALIAS(DOS$_wsearchenv_s, libd__wsearchenv_s);
DEFINE_PUBLIC_ALIAS(_wsearchenv_s, libc__wsearchenv_s);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STDLIB_C */
