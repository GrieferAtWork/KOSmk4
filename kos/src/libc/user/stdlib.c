/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
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

#include <kos/exec/peb.h>
#include <kos/syscalls.h>
#include <parts/dos/errno.h>
#include <parts/errno.h>
#include <sys/auxv.h>
#include <sys/wait.h>

#include <assert.h>
#include <fcntl.h>
#include <limits.h>
#include <malloc.h>
#include <sched.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "../libc/dl.h"
#include "../libc/errno.h"
#include "../libc/globals.h"
#include "../libc/init.h"
#include "malloc.h"
#include "stdlib.h"


DECL_BEGIN

INTDEF struct atomic_rwlock libc_environ_lock;

/* Since `environ' can easily contain strings that weren't allocated
 * using `malloc()' and friends, and since `putenv()' is a thing that
 * exists to directly inject user-provided strings into the environ
 * map, we run into a problem when it comes to preventing memory leaks
 * in regards of strings that _were_ injected dynamically through use
 * of functions such as `setenv()'
 * The solution is to keep track of a singly-linked list of all environ
 * strings that _were_ allocated through use of `malloc()', and simply
 * `free()' only strings apart of this list when functions such as
 * `unsetenv()' or `clearenv()' are called.
 * Lastly, in order to check if the `environ' vector itself was dynamically
 * allocated on the heap, we keep a secondary, environ-like variable
 * `libc_environ_heap' that is set to `NULL' initially (or after `clearenv()'),
 * and when non-NULL is then compared against the real `environ' to determine
 * is changes were made, including the hosted application overwriting the
 * value of `environ' itself. */

struct environ_heapstr {
	struct environ_heapstr       *ehs_next;  /* [0..1] next heap string. */
	COMPILER_FLEXIBLE_ARRAY(char, ehs_text); /* The NUL-terminated text of this string. */
};

/* [lock(libc_environ_lock)][0..1] The heap-allocated variant of `environ', or `NULL' if never used. */
PRIVATE ATTR_SECTION(".bss.crt.fs.environ.heap") char **libc_environ_heap = NULL;
/* [lock(libc_environ_lock)][0..1] Linked list of heap-allocated environ strings. */
PRIVATE ATTR_SECTION(".bss.crt.fs.environ.heap") struct environ_heapstr *libc_environ_strings = NULL;

LOCAL ATTR_SECTION(".text.crt.fs.environ.heap.environ_remove_heapstring_locked")
bool LIBCCALL environ_remove_heapstring_locked(struct environ_heapstr *ptr) {
	struct environ_heapstr **piter, *iter;
	assert(atomic_rwlock_reading(&libc_environ_lock));
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

struct cxa_atexit_callback {
	void (LIBCCALL *ac_func)(void *arg); /* [1..1] Function */
	void           *ac_arg;              /* [?..?] Argument */
};

struct cxa_atexit_list {
	struct atomic_rwlock        al_lock; /*  */
	size_t                      al_size; /*  */
	struct cxa_atexit_callback *al_list; /* [] */
};

INTERN ATTR_SECTION(".text.crt.sched.process.__cxa_atexit") int
NOTHROW_NCX(LIBCCALL libc___cxa_atexit)(void (LIBCCALL *func)(void *arg),
                                        void *arg, void *dso_handle) {
	void *dl_handle, *error;
	/* NOTE: I don't really understand why this function is even necessary...
	 *       I mean sure: it allows c++ to register destructor callbacks lazily
	 *       for local statics, however the same effect could be achieved by using
	 *       an __attribute__((destructor)), where its callback checks some kind of
	 *       was-initialized flag and invokes that callback when this is true. */
	if (dso_handle == NULL) {
		/* Special case: When `dso_handle' is `NULL', register the callback for the
		 *               primary module, in which case the registered function must be called
		 *               alongside atexit() */
		dl_handle = NULL;
	} else {
		/* `dso_handle' is actually a pointer somewhere inside of the static memory segment
		 * of some module (either dynamically allocated, or part of the primary module)
		 * As such, we can make use of `dlgethandle()' in order to look-up the associated
		 * shared object, which which we can then register the given callback. */
		dl_handle = dlgethandle(dso_handle, DLGETHANDLE_FINCREF);
		if unlikely(!dl_handle) {
			libc_seterrno(EFAULT); /* `dso_handle' doesn't map to any known module. */
			return -1;
		}
	}
	/* Call into libdl to register the finalizer with the associated shared object. */
	error = dlauxctrl(dl_handle, DLAUXCTRL_ADD_FINALIZER, func, arg);
	dlclose(dl_handle);
	if unlikely(!error)
		return -1;
	return 0;
}





/*[[[start:implementation]]]*/


PRIVATE ATTR_SECTION(".rodata.crt.random.rand_map") u32 const rand_map[] = {
	0x11e0ebcc, 0xa914eba6, 0xe400e438, 0xa6c4a4df,
	0x0da46171, 0x4b9a27d1, 0x201910ae, 0x95e213cb,
	0xd5ce0943, 0x00005fdc, 0x0319257d, 0x09280b06,
	0x1148c0a6, 0x07a24139, 0x021214a6, 0x03221af8
};
PRIVATE ATTR_SECTION(".bss.crt.random.seed") u32 libc_seed = 0;
PRIVATE ATTR_SECTION(".text.crt.random.seed") unsigned int
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
	size_t namelen;
	char *result, **envp;
	if unlikely(!varname)
		return NULL;
	namelen = strlen(varname);
	atomic_rwlock_read(&libc_environ_lock);
	envp = environ;
	if unlikely(!envp)
		result = NULL;
	else {
		for (; (result = *envp) != NULL; ++envp) {
			if (memcmp(result, varname, namelen * sizeof(char)) != 0 ||
			    result[namelen] != '=')
				continue;
			result += namelen + 1;
			break;
		}
	}
	atomic_rwlock_endread(&libc_environ_lock);
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
	if unlikely(!varname || !*varname || strchr(varname, '=')) {
		libc_seterrno(EINVAL);
		return -1;
	}
	/* Quick check: if we're not supported to replace variables, and if
	 *              the variable already exists, then there is no need
	 *              to allocate a new environment line for it, only to
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
	atomic_rwlock_write(&libc_environ_lock);
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
				 * may have added the environment variable in the mean time. */
				atomic_rwlock_endwrite(&libc_environ_lock);
				free(line);
				return 0;
			}
			/* Check if the existing line was already allocated on the heap. */
			existing_heapline = COMPILER_CONTAINER_OF(existing_line,
			                                          struct environ_heapstr,
			                                          ehs_text);
			if (!environ_remove_heapstring_locked(existing_heapline))
				existing_heapline = NULL;
			/* Override the existing line. */
			*iter = line->ehs_text;
			line->ehs_next = libc_environ_strings;
			libc_environ_strings = line;
			atomic_rwlock_endwrite(&libc_environ_lock);
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
		atomic_rwlock_endwrite(&libc_environ_lock);
		new_enva     = envc + 1;
		new_new_envp = (char **)realloc(new_envp,
		                                (new_enva + 1) *
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
	memmove(new_envp, envp, envc * sizeof(char *));
	new_envp[envc]     = line->ehs_text;
	new_envp[envc + 1] = NULL; /* Keep the table NULL-terminated */

	/* Add the new line as an environ heap-pointer. */
	line->ehs_next = libc_environ_strings;
	libc_environ_strings = line;

	/* Set the new environ map as the one that is active. */
	old_heap_envp     = libc_environ_heap;
	libc_environ_heap = new_envp;
	environ           = new_envp;

	atomic_rwlock_endwrite(&libc_environ_lock);

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
	if unlikely(!varname || !*varname || strchr(varname, '=')) {
		libc_seterrno(EINVAL);
		return -1;
	}
	namelen = strlen(varname);
	atomic_rwlock_write(&libc_environ_lock);
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
			existing_heapline = COMPILER_CONTAINER_OF(existing_line,
			                                          struct environ_heapstr,
			                                          ehs_text);
			if (environ_remove_heapstring_locked(existing_heapline)) {
				existing_heapline->ehs_next = existing_heaplines;
				existing_heaplines = existing_heapline;
			}
			/* Continue searching for more matching lines.
			 * Since `environ' is exposed as-is to the hosted application,
			 * there is the possibility that the user manually added the
			 * same variable more than once... */
		}
		atomic_rwlock_endwrite(&libc_environ_lock);
		/* Free all removed lines that were allocated on the heap. */
		while (existing_heaplines) {
			struct environ_heapstr *next;
			next = existing_heaplines->ehs_next;
			free(existing_heaplines);
			existing_heaplines = next;
		}
		return 0;
	}
	atomic_rwlock_endwrite(&libc_environ_lock);
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
	atomic_rwlock_write(&libc_environ_lock);
	heap_envp            = libc_environ_heap;
	heap_strings         = libc_environ_strings;
	environ              = NULL;
	libc_environ_heap    = NULL;
	libc_environ_strings = NULL;
	atomic_rwlock_endwrite(&libc_environ_lock);
	/* Free all dynamically allocated strings, as
	 * well a dynamically allocated environ map. */
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
		libc_seterrno(EINVAL);
		return -1;
	}
	new_envp = NULL;
	new_enva = 0;
again_searchenv:
	atomic_rwlock_write(&libc_environ_lock);
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
			existing_heapline = COMPILER_CONTAINER_OF(existing_line,
			                                          struct environ_heapstr,
			                                          ehs_text);
			if (!environ_remove_heapstring_locked(existing_heapline))
				existing_heapline = NULL;
			/* Override the existing line. */
			*iter = string;
			atomic_rwlock_endwrite(&libc_environ_lock);
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
		atomic_rwlock_endwrite(&libc_environ_lock);
		new_enva = envc + 1;
		new_new_envp = (char **)realloc(new_envp, (new_enva + 1) * sizeof(char *));
		if unlikely(!new_new_envp) {
			free(new_envp);
			return -1;
		}
		new_envp = new_new_envp;
		goto again_searchenv;
	}

do_fill_environ:
	/* Fill in the new environment table. */
	memmove(new_envp, envp, envc * sizeof(char *));
	new_envp[envc]     = string;
	new_envp[envc + 1] = NULL; /* Keep the table NULL-terminated */

	/* Set the new environ map as the one that is active. */
	old_heap_envp     = libc_environ_heap;
	libc_environ_heap = new_envp;
	environ           = new_envp;

	atomic_rwlock_endwrite(&libc_environ_lock);

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
	return getenv(varname);
}
/*[[[end:libc_secure_getenv]]]*/


/*[[[head:libc__dupenv_s,hash:CRC-32=0x58aa7375]]]*/
INTERN ATTR_SECTION(".text.crt.dos.utility") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__dupenv_s)(char **__restrict pbuf,
                                     size_t *pbuflen,
                                     char const *varname)
/*[[[body:libc__dupenv_s]]]*/
/*AUTO*/{
	(void)pbuf;
	(void)pbuflen;
	(void)varname;
	CRT_UNIMPLEMENTED("_dupenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__dupenv_s]]]*/

/*[[[head:libc_getenv_s,hash:CRC-32=0x7ab40405]]]*/
INTERN ATTR_SECTION(".text.crt.dos.utility") NONNULL((1, 2, 4)) errno_t
NOTHROW_NCX(LIBCCALL libc_getenv_s)(size_t *psize,
                                    char *buf,
                                    rsize_t buflen,
                                    char const *varname)
/*[[[body:libc_getenv_s]]]*/
/*AUTO*/{
	(void)psize;
	(void)buf;
	(void)buflen;
	(void)varname;
	CRT_UNIMPLEMENTED("getenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getenv_s]]]*/

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
	CRT_UNIMPLEMENTED("_searchenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__searchenv_s]]]*/




PRIVATE ATTR_SECTION(".rodata.crt.fs.exec.system.system") char const path_bin_busybox[] = "/bin/busybox";
PRIVATE ATTR_SECTION(".rodata.crt.fs.exec.system.system") char const path_bin_sh[] = "/bin/sh";
PRIVATE ATTR_SECTION(".rodata.crt.fs.exec.system.system") char const dash_c[] = "-c";

INTERN ATTR_NOINLINE ATTR_SECTION(".text.crt.fs.exec.system.system") pid_t
NOTHROW_RPC(LIBCCALL libc_do_system_spawn)(char const *__restrict command) {
	pid_t cpid;
	cpid = vfork();
	if (cpid == 0) {
		execl(path_bin_busybox, path_bin_sh + 5, dash_c, command, (char *)NULL);
		execl(path_bin_sh, path_bin_sh + 5, dash_c, command, (char *)NULL);
		/* NOTE: system() must return ZERO(0) if no command processor is available. */
		_Exit(command ? 127 : 0);
	}
	return cpid;
}

/*[[[head:libc_system,hash:CRC-32=0x5ec78712]]]*/
INTERN ATTR_SECTION(".text.crt.fs.exec.system") int
NOTHROW_RPC(LIBCCALL libc_system)(char const *command)
/*[[[body:libc_system]]]*/
{
	pid_t cpid, error;
	int status;
	cpid = libc_do_system_spawn(command);
	if (cpid < 0)
		return -1;
	for (;;) {
		error = waitpid(cpid, &status, 0);
		if (error == cpid)
			break;
		if (error >= 0)
			continue;
		if (libc_geterrno() != EINTR)
			return -1;
	}
	return WIFEXITED(status)
	       ? WEXITSTATUS(status)
	       : 1;
}
/*[[[end:libc_system]]]*/


struct atexit_callback {
	__on_exit_func_t ac_func; /* [1..1] The function to-be invoked. */
	void            *ac_arg;  /* Argument for `ac_func'. */
};

struct atexit_vector_struct {
	struct atomic_rwlock    av_lock; /* Lock for this vector. */
	size_t                  av_size; /* [lock(av_lock)] Number of registered functions. */
	struct atexit_callback *av_vect; /* [0..av_size][owned][lock(av_lock)] Array of functions. */
	int                     av_stat; /* Process exit status. */
};

PRIVATE ATTR_SECTION(".bss.crt.application.exit.atexit_vector")
struct atexit_vector_struct atexit_vector = {
	/* .av_lock = */ ATOMIC_RWLOCK_INIT,
	/* .av_size = */ 0,
	/* .av_vect = */ NULL,
	/* .av_stat = */ 0
};


INTERN ATTR_SECTION(".text.crt.application.exit.libc_run_atexit")
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

/*[[[head:libc_on_exit,hash:CRC-32=0xc49f8108]]]*/
INTERN ATTR_SECTION(".text.crt.sched.process") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_on_exit)(__on_exit_func_t func,
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
	                                               (atexit_vector.av_size + 1) *
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

PRIVATE ATTR_SECTION(".text.crt.sched.process.libc_atexit_wrapper") void
NOTHROW_NCX(LIBCCALL libc_atexit_wrapper)(int status, void *arg) {
	(void)status;
	(*(__atexit_func_t)arg)();
}

/*[[[head:libc_atexit,hash:CRC-32=0x1e48b9c9]]]*/
INTERN ATTR_SECTION(".text.crt.sched.process") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_atexit)(__atexit_func_t func)
/*[[[body:libc_atexit]]]*/
{
	return on_exit(&libc_atexit_wrapper, (void *)func);
}
/*[[[end:libc_atexit]]]*/



struct at_quick_exit_callback {
	__atexit_func_t aqc_func; /* [1..1] The function to-be invoked. */
};

struct at_quick_exit_vector_struct {
	size_t                         aqv_size; /* [lock(atexit_vector.av_lock)] Number of registered functions. */
	struct at_quick_exit_callback *aqv_vect; /* [0..av_size][owned][lock(atexit_vector.av_lock)] Array of functions. */
};

PRIVATE ATTR_SECTION(".bss.crt.application.exit.at_quick_exit_vector")
struct at_quick_exit_vector_struct at_quick_exit_vector = {
	/* .av_size = */ 0,
	/* .av_vect = */ NULL
};

INTERN ATTR_SECTION(".text.crt.application.exit.libc_run_at_quick_exit")
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

/*[[[head:libc_at_quick_exit,hash:CRC-32=0x85221818]]]*/
INTERN ATTR_SECTION(".text.crt.sched.process") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_at_quick_exit)(__atexit_func_t func)
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
	                                                      (at_quick_exit_vector.aqv_size + 1) *
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
	 * `libc_fini()' because libc is compiled with `-fini=libc_fini') */
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
	/* Don't run library finalizers, but still run libc_fini() to
	 * at least flush open file streams, ensuring that no open
	 * file is left in an undefined state, and any potential error
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

PRIVATE ATTR_SECTION(".text.crt.dos.sched.process.libc_onexit_wrapper")
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
	CRT_UNIMPLEMENTED("drand48_r"); /* TODO */
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
	CRT_UNIMPLEMENTED("erand48_r"); /* TODO */
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
	CRT_UNIMPLEMENTED("lrand48_r"); /* TODO */
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
	CRT_UNIMPLEMENTED("nrand48_r"); /* TODO */
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
	CRT_UNIMPLEMENTED("mrand48_r"); /* TODO */
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
	CRT_UNIMPLEMENTED("jrand48_r"); /* TODO */
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
	CRT_UNIMPLEMENTED("srand48_r"); /* TODO */
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
	CRT_UNIMPLEMENTED("seed48_r"); /* TODO */
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
	CRT_UNIMPLEMENTED("lcong48_r"); /* TODO */
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
	CRT_UNIMPLEMENTED("random_r"); /* TODO */
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
	CRT_UNIMPLEMENTED("srandom_r"); /* TODO */
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
	CRT_UNIMPLEMENTED("initstate_r"); /* TODO */
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
	CRT_UNIMPLEMENTED("setstate_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_setstate_r]]]*/

/*[[[head:libc_mkstemps,hash:CRC-32=0xfd5623f5]]]*/
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_mkstemps)(char *template_,
                                    int suffixlen)
/*[[[body:libc_mkstemps]]]*/
/*AUTO*/{
	(void)template_;
	(void)suffixlen;
	CRT_UNIMPLEMENTED("mkstemps"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_mkstemps]]]*/

/*[[[head:libc_rpmatch,hash:CRC-32=0x30b72b07]]]*/
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_rpmatch)(char const *response)
/*[[[body:libc_rpmatch]]]*/
/*AUTO*/{
	(void)response;
	CRT_UNIMPLEMENTED("rpmatch"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_rpmatch]]]*/

/*[[[head:libc_mkstemps64,hash:CRC-32=0xdfb71f3]]]*/
#if !defined(__O_LARGEFILE) || !__O_LARGEFILE
DEFINE_INTERN_ALIAS(libc_mkstemps64, libc_mkstemps);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_mkstemps64)(char *template_,
                                      int suffixlen)
/*[[[body:libc_mkstemps64]]]*/
/*AUTO*/{
	(void)template_;
	(void)suffixlen;
	CRT_UNIMPLEMENTED("mkstemps64"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_mkstemps64]]]*/

/*[[[head:libc_getloadavg,hash:CRC-32=0x20bc57b0]]]*/
INTERN ATTR_SECTION(".text.crt.system.utility") int
NOTHROW_RPC(LIBCCALL libc_getloadavg)(double loadavg[],
                                      int nelem)
/*[[[body:libc_getloadavg]]]*/
/*AUTO*/{
	(void)loadavg;
	(void)nelem;
	CRT_UNIMPLEMENTED("getloadavg"); /* TODO */
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
	CRT_UNIMPLEMENTED("erand48"); /* TODO */
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
	CRT_UNIMPLEMENTED("nrand48"); /* TODO */
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
	CRT_UNIMPLEMENTED("jrand48"); /* TODO */
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
	CRT_UNIMPLEMENTED("srand48"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_srand48]]]*/

/*[[[head:libc_seed48,hash:CRC-32=0x65a13274]]]*/
INTERN ATTR_SECTION(".text.crt.random") NONNULL((1)) unsigned short *
NOTHROW_NCX(LIBCCALL libc_seed48)(unsigned short seed16v[3])
/*[[[body:libc_seed48]]]*/
/*AUTO*/{
	(void)seed16v;
	CRT_UNIMPLEMENTED("seed48"); /* TODO */
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
	CRT_UNIMPLEMENTED("lcong48"); /* TODO */
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
	CRT_UNIMPLEMENTED("initstate"); /* TODO */
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
	CRT_UNIMPLEMENTED("setstate"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_setstate]]]*/

/*[[[head:libc_l64a,hash:CRC-32=0xc2c78b77]]]*/
INTERN ATTR_SECTION(".text.crt.string.encrypt") WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_l64a)(long n)
/*[[[body:libc_l64a]]]*/
/*AUTO*/{
	(void)n;
	CRT_UNIMPLEMENTED("l64a"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_l64a]]]*/

/*[[[head:libc_a64l,hash:CRC-32=0xea4a21cb]]]*/
INTERN ATTR_SECTION(".text.crt.string.encrypt") ATTR_PURE WUNUSED NONNULL((1)) long
NOTHROW_NCX(LIBCCALL libc_a64l)(char const *s)
/*[[[body:libc_a64l]]]*/
/*AUTO*/{
	(void)s;
	CRT_UNIMPLEMENTED("a64l"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_a64l]]]*/

/*[[[head:libc_realpath,hash:CRC-32=0x30ce7bd1]]]*/
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL to automatically `malloc()'ate and return a
 *                   buffer of sufficient size. */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED NONNULL((1)) char *
NOTHROW_RPC(LIBCCALL libc_realpath)(char const *__restrict filename,
                                    char *resolved)
/*[[[body:libc_realpath]]]*/
{
	return libc_frealpathat(AT_FDCWD, filename, resolved,
	                        resolved ? PATH_MAX : 0, 0);
}
/*[[[end:libc_realpath]]]*/

/*[[[head:libc_frealpath,hash:CRC-32=0xaabc516]]]*/
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_frealpath)(fd_t fd,
                                     char *resolved,
                                     size_t buflen)
/*[[[body:libc_frealpath]]]*/
{
	return frealpath4(fd, resolved, buflen, 0);
}
/*[[[end:libc_frealpath]]]*/

/*[[[head:libc_frealpath4,hash:CRC-32=0x66630493]]]*/
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0|AT_ALTPATH|AT_DOSPATH'
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
 *       bytes automatically allocated in the heap, ontop of which you may also
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
			buffer  = (char *)malloc(buflen);
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
				buffer  = resolved;
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
		libc_seterrno(-result);
		return NULL;
	}
done:
	return buffer;
}
/*[[[end:libc_frealpath4]]]*/

/*[[[head:libc_frealpathat,hash:CRC-32=0xc7c2c07d]]]*/
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_FOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size.
 * @param flags: Set of `0|AT_ALTPATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
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
			buffer  = (char *)malloc(buflen);
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
				buffer  = resolved;
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
	                         flags);
	if (E_ISERR(result)) {
		if (!resolved) {
err_buffer_result_errno:
			free(buffer);
		}
		libc_seterrno(-result);
		return NULL;
	}
done:
	return buffer;
}
/*[[[end:libc_frealpathat]]]*/

/*[[[head:libc_mktemp,hash:CRC-32=0x4ab0ffae]]]*/
INTERN ATTR_SECTION(".text.crt.fs.utility") NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_mktemp)(char *template_)
/*[[[body:libc_mktemp]]]*/
/*AUTO*/{
	(void)template_;
	CRT_UNIMPLEMENTED("mktemp"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_mktemp]]]*/

/*[[[head:libc_mkstemp,hash:CRC-32=0x3fc81c66]]]*/
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_mkstemp)(char *template_)
/*[[[body:libc_mkstemp]]]*/
/*AUTO*/{
	return mktemp(template_) ? 0 : -1;
}
/*[[[end:libc_mkstemp]]]*/

/*[[[head:libc_mkstemp64,hash:CRC-32=0xe2385956]]]*/
#if !defined(__O_LARGEFILE) || !__O_LARGEFILE
DEFINE_INTERN_ALIAS(libc_mkstemp64, libc_mkstemp);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_mkstemp64)(char *template_)
/*[[[body:libc_mkstemp64]]]*/
/*AUTO*/{
	return mkstemp(template_);
}
#endif /* MAGIC:alias */
/*[[[end:libc_mkstemp64]]]*/

/*[[[head:libc_mkdtemp,hash:CRC-32=0xeb048757]]]*/
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_mkdtemp)(char *template_)
/*[[[body:libc_mkdtemp]]]*/
/*AUTO*/{
	(void)template_;
	CRT_UNIMPLEMENTED("mkdtemp"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_mkdtemp]]]*/


/*[[[head:libc_grantpt,hash:CRC-32=0xd1e26f46]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_grantpt)(fd_t fd)
/*[[[body:libc_grantpt]]]*/
/*AUTO*/{
	(void)fd;
	CRT_UNIMPLEMENTED("grantpt"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_grantpt]]]*/

/*[[[head:libc_unlockpt,hash:CRC-32=0x861f28fa]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_unlockpt)(fd_t fd)
/*[[[body:libc_unlockpt]]]*/
/*AUTO*/{
	(void)fd;
	CRT_UNIMPLEMENTED("unlockpt"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_unlockpt]]]*/

/*[[[head:libc_ptsname,hash:CRC-32=0xf5496d8]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_ptsname)(fd_t fd)
/*[[[body:libc_ptsname]]]*/
/*AUTO*/{
	(void)fd;
	CRT_UNIMPLEMENTED("ptsname"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_ptsname]]]*/

/*[[[head:libc_posix_openpt,hash:CRC-32=0xe65ede97]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED int
NOTHROW_RPC(LIBCCALL libc_posix_openpt)(oflag_t oflags)
/*[[[body:libc_posix_openpt]]]*/
/*AUTO*/{
	(void)oflags;
	CRT_UNIMPLEMENTED("posix_openpt"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_posix_openpt]]]*/

/*[[[head:libc_getpt,hash:CRC-32=0xa0920e89]]]*/
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") int
NOTHROW_RPC(LIBCCALL libc_getpt)(void)
/*[[[body:libc_getpt]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getpt"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getpt]]]*/

/*[[[head:libc_ptsname_r,hash:CRC-32=0xcd858348]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_ptsname_r)(fd_t fd,
                                     char *buf,
                                     size_t buflen)
/*[[[body:libc_ptsname_r]]]*/
/*AUTO*/{
	(void)fd;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTED("ptsname_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ptsname_r]]]*/

/*[[[head:libc_canonicalize_file_name,hash:CRC-32=0xf563004a]]]*/
/* Return the result of `realpath(filename)' as a `malloc()'-allocated buffer
 * Upon error, `NULL' is returned instead */
INTERN ATTR_SECTION(".text.crt.fs.property") ATTR_MALLOC WUNUSED NONNULL((1)) char *
NOTHROW_RPC(LIBCCALL libc_canonicalize_file_name)(char const *filename)
/*[[[body:libc_canonicalize_file_name]]]*/
{
	return realpath(filename, NULL);
}
/*[[[end:libc_canonicalize_file_name]]]*/

/*[[[head:libc_mkostemp,hash:CRC-32=0xebe47ea3]]]*/
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_mkostemp)(char *template_,
                                    int flags)
/*[[[body:libc_mkostemp]]]*/
/*AUTO*/{
	(void)template_;
	(void)flags;
	CRT_UNIMPLEMENTED("mkostemp"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_mkostemp]]]*/

/*[[[head:libc_mkostemps,hash:CRC-32=0x4ddfea24]]]*/
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_mkostemps)(char *template_,
                                     int suffixlen,
                                     int flags)
/*[[[body:libc_mkostemps]]]*/
/*AUTO*/{
	(void)template_;
	(void)suffixlen;
	(void)flags;
	CRT_UNIMPLEMENTED("mkostemps"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_mkostemps]]]*/

/*[[[head:libc_mkostemp64,hash:CRC-32=0xf1a2db9f]]]*/
#if !defined(__O_LARGEFILE) || !__O_LARGEFILE
DEFINE_INTERN_ALIAS(libc_mkostemp64, libc_mkostemp);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_mkostemp64)(char *template_,
                                      int flags)
/*[[[body:libc_mkostemp64]]]*/
/*AUTO*/{
	(void)template_;
	(void)flags;
	CRT_UNIMPLEMENTED("mkostemp64"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_mkostemp64]]]*/

/*[[[head:libc_mkostemps64,hash:CRC-32=0x4e38af15]]]*/
#if !defined(__O_LARGEFILE) || !__O_LARGEFILE
DEFINE_INTERN_ALIAS(libc_mkostemps64, libc_mkostemps);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_mkostemps64)(char *template_,
                                       int suffixlen,
                                       int flags)
/*[[[body:libc_mkostemps64]]]*/
/*AUTO*/{
	(void)template_;
	(void)suffixlen;
	(void)flags;
	CRT_UNIMPLEMENTED("mkostemps64"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_mkostemps64]]]*/

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


PRIVATE ATTR_CONST WUNUSED
ATTR_SECTION(".text.crt.dos.application.init.__p___initenv.get_initenv")
char **NOTHROW(libc_get_initenv)(void) {
	struct process_peb *peb;
	char **result;
	peb = &__peb;
	/* Construct a pointer to what (presumably) is `pp_envp_vector'
	 * NOTE: If the hosted application modified `pp_argc' (who's address
	 *       by the way is aliased by `__argc' and `*__p___argc()'), then
	 *       this calculation may not necessarily be correct! */
	result = (char **)(peb + 1) + peb->pp_argc + 1;
	return result;
}

PRIVATE ATTR_SECTION(".bss.crt.dos.application.init.__p___initenv.pointer")
char **libc___p___initenv_pointer = NULL;
PRIVATE ATTR_SECTION(".bss.crt.dos.application.init.__p___initenv.initialized")
struct atomic_once libc___p___initenv_initialized = ATOMIC_ONCE_INIT;

/*[[[head:libc___p___initenv,hash:CRC-32=0xb551ec82]]]*/
/* Access to the initial environment block */
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char ***
NOTHROW_NCX(LIBCCALL libc___p___initenv)(void)
/*[[[body:libc___p___initenv]]]*/
{
	ATOMIC_ONCE_RUN(&libc___p___initenv_initialized, {
		libc___p___initenv_pointer = libc_get_initenv();
	});
	return &libc___p___initenv_pointer;
}
/*[[[end:libc___p___initenv]]]*/

/*[[[head:libd___p__wenviron,hash:CRC-32=0x876527b4]]]*/
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***
NOTHROW_NCX(LIBDCALL libd___p__wenviron)(void)
/*[[[body:libd___p__wenviron]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("DOS$__p__wenviron"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd___p__wenviron]]]*/

/*[[[head:libc___p__wenviron,hash:CRC-32=0x19797235]]]*/
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***
NOTHROW_NCX(LIBKCALL libc___p__wenviron)(void)
/*[[[body:libc___p__wenviron]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p__wenviron"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p__wenviron]]]*/

/*[[[head:libd___p___winitenv,hash:CRC-32=0x90b2aec9]]]*/
/* Access to the initial environment block */
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***
NOTHROW_NCX(LIBDCALL libd___p___winitenv)(void)
/*[[[body:libd___p___winitenv]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("DOS$__p___winitenv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd___p___winitenv]]]*/

/*[[[head:libc___p___winitenv,hash:CRC-32=0xa93012a]]]*/
/* Access to the initial environment block */
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***
NOTHROW_NCX(LIBKCALL libc___p___winitenv)(void)
/*[[[body:libc___p___winitenv]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p___winitenv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p___winitenv]]]*/

/*[[[head:libd___p___wargv,hash:CRC-32=0x1611f440]]]*/
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***
NOTHROW_NCX(LIBDCALL libd___p___wargv)(void)
/*[[[body:libd___p___wargv]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("DOS$__p___wargv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd___p___wargv]]]*/

/*[[[head:libc___p___wargv,hash:CRC-32=0xd1fa5108]]]*/
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***
NOTHROW_NCX(LIBKCALL libc___p___wargv)(void)
/*[[[body:libc___p___wargv]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p___wargv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p___wargv]]]*/

/*[[[head:libd___p__wpgmptr,hash:CRC-32=0xa88e3e57]]]*/
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t **
NOTHROW_NCX(LIBDCALL libd___p__wpgmptr)(void)
/*[[[body:libd___p__wpgmptr]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("DOS$__p__wpgmptr"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd___p__wpgmptr]]]*/

/*[[[head:libc___p__wpgmptr,hash:CRC-32=0xb1874881]]]*/
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t **
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
		return __DOS_EINVAL;
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
		return __DOS_EINVAL;
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
	CRT_UNIMPLEMENTED("_seterrormode"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__seterrormode]]]*/

/*[[[head:libc__set_error_mode,hash:CRC-32=0x2437863d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") int
NOTHROW_NCX(LIBCCALL libc__set_error_mode)(int mode)
/*[[[body:libc__set_error_mode]]]*/
/*AUTO*/{
	(void)mode;
	CRT_UNIMPLEMENTED("_set_error_mode"); /* TODO */
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
	CRT_UNIMPLEMENTED("_beep"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__beep]]]*/

/*[[[head:libc__set_purecall_handler,hash:CRC-32=0xa0356abb]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") _purecall_handler
NOTHROW_NCX(LIBCCALL libc__set_purecall_handler)(_purecall_handler __handler)
/*[[[body:libc__set_purecall_handler]]]*/
/*AUTO*/{
	(void)__handler;
	CRT_UNIMPLEMENTED("_set_purecall_handler"); /* TODO */
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
	CRT_UNIMPLEMENTED("_set_invalid_parameter_handler"); /* TODO */
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

/*[[[head:libc___p__fmode,hash:CRC-32=0x75afe2d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") ATTR_CONST ATTR_RETNONNULL WUNUSED int *
NOTHROW_NCX(LIBCCALL libc___p__fmode)(void)
/*[[[body:libc___p__fmode]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p__fmode"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p__fmode]]]*/

/*[[[head:libc__set_fmode,hash:CRC-32=0xba018643]]]*/
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") errno_t
NOTHROW_NCX(LIBCCALL libc__set_fmode)(int mode)
/*[[[body:libc__set_fmode]]]*/
/*AUTO*/{
	(void)mode;
	CRT_UNIMPLEMENTED("_set_fmode"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__set_fmode]]]*/

/*[[[head:libc__get_fmode,hash:CRC-32=0xce6fa140]]]*/
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") errno_t
NOTHROW_NCX(LIBCCALL libc__get_fmode)(int *pmode)
/*[[[body:libc__get_fmode]]]*/
/*AUTO*/{
	(void)pmode;
	CRT_UNIMPLEMENTED("_get_fmode"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTED("_set_abort_behavior"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__set_abort_behavior]]]*/

/*[[[head:libc__wgetenv,hash:CRC-32=0x47d36374]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc__wgetenv)(char32_t const *varname)
/*[[[body:libc__wgetenv]]]*/
/*AUTO*/{
	(void)varname;
	CRT_UNIMPLEMENTED("_wgetenv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wgetenv]]]*/

/*[[[head:libd__wgetenv,hash:CRC-32=0xa7845fca]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd__wgetenv)(char16_t const *varname)
/*[[[body:libd__wgetenv]]]*/
/*AUTO*/{
	(void)varname;
	CRT_UNIMPLEMENTED("DOS$_wgetenv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__wgetenv]]]*/

/*[[[head:libc__wgetenv_s,hash:CRC-32=0x6726fc33]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1, 4)) errno_t
NOTHROW_NCX(LIBKCALL libc__wgetenv_s)(size_t *return_size,
                                      char32_t *buf,
                                      size_t buflen,
                                      char32_t const *varname)
/*[[[body:libc__wgetenv_s]]]*/
/*AUTO*/{
	(void)return_size;
	(void)buf;
	(void)buflen;
	(void)varname;
	CRT_UNIMPLEMENTED("_wgetenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__wgetenv_s]]]*/

/*[[[head:libd__wgetenv_s,hash:CRC-32=0x22cb9a76]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1, 4)) errno_t
NOTHROW_NCX(LIBDCALL libd__wgetenv_s)(size_t *return_size,
                                      char16_t *buf,
                                      size_t buflen,
                                      char16_t const *varname)
/*[[[body:libd__wgetenv_s]]]*/
/*AUTO*/{
	(void)return_size;
	(void)buf;
	(void)buflen;
	(void)varname;
	CRT_UNIMPLEMENTED("DOS$_wgetenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd__wgetenv_s]]]*/

/*[[[head:libc__wdupenv_s,hash:CRC-32=0xfdaac8e8]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBKCALL libc__wdupenv_s)(char32_t **pbuf,
                                      size_t *pbuflen,
                                      char32_t const *varname)
/*[[[body:libc__wdupenv_s]]]*/
/*AUTO*/{
	(void)pbuf;
	(void)pbuflen;
	(void)varname;
	CRT_UNIMPLEMENTED("_wdupenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__wdupenv_s]]]*/

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
	CRT_UNIMPLEMENTED("DOS$_wfullpath"); /* TODO */
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
	CRT_UNIMPLEMENTED("_wfullpath"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wfullpath]]]*/

/*[[[head:libd__wputenv,hash:CRC-32=0x2ede1d24]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd__wputenv)(char16_t *string)
/*[[[body:libd__wputenv]]]*/
/*AUTO*/{
	(void)string;
	CRT_UNIMPLEMENTED("DOS$_wputenv"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd__wputenv]]]*/

/*[[[head:libc__wputenv,hash:CRC-32=0x913e79b2]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc__wputenv)(char32_t *string)
/*[[[body:libc__wputenv]]]*/
/*AUTO*/{
	(void)string;
	CRT_UNIMPLEMENTED("_wputenv"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__wputenv]]]*/

/*[[[head:libd__wputenv_s,hash:CRC-32=0x985727da]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") errno_t
NOTHROW_NCX(LIBDCALL libd__wputenv_s)(char16_t const *varname,
                                      char16_t const *val)
/*[[[body:libd__wputenv_s]]]*/
/*AUTO*/{
	(void)varname;
	(void)val;
	CRT_UNIMPLEMENTED("DOS$_wputenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd__wputenv_s]]]*/

/*[[[head:libc__wputenv_s,hash:CRC-32=0xcfcd97a5]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") errno_t
NOTHROW_NCX(LIBKCALL libc__wputenv_s)(char32_t const *varname,
                                      char32_t const *val)
/*[[[body:libc__wputenv_s]]]*/
/*AUTO*/{
	(void)varname;
	(void)val;
	CRT_UNIMPLEMENTED("_wputenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__wputenv_s]]]*/

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
	CRT_UNIMPLEMENTED("DOS$_wsearchenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
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
	CRT_UNIMPLEMENTED("_wsearchenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__wsearchenv_s]]]*/

/*[[[head:libd__wdupenv_s,hash:CRC-32=0xdb82c616]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBDCALL libd__wdupenv_s)(char16_t **pbuf,
                                      size_t *pbuflen,
                                      char16_t const *varname)
/*[[[body:libd__wdupenv_s]]]*/
/*AUTO*/{
	(void)pbuf;
	(void)pbuflen;
	(void)varname;
	CRT_UNIMPLEMENTED("DOS$_wdupenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd__wdupenv_s]]]*/

/*[[[head:libc_reallocf,hash:CRC-32=0x79be04b8]]]*/
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBCCALL libc_reallocf)(void *mallptr,
                                    size_t num_bytes)
/*[[[body:libc_reallocf]]]*/
/*AUTO*/{
	void *result;
	result = realloc(mallptr, num_bytes);
	if unlikely(!result)
		free(mallptr);
	return result;
}
/*[[[end:libc_reallocf]]]*/

/*[[[head:libc_recallocarray,hash:CRC-32=0x15c974db]]]*/
/* Same as `recallocv(mallptr, new_elem_count, elem_size)', but also ensure that
 * when `mallptr != NULL', memory pointed to by the old `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((3, 4)) void *
NOTHROW_NCX(LIBCCALL libc_recallocarray)(void *mallptr,
                                         size_t old_elem_count,
                                         size_t new_elem_count,
                                         size_t elem_size)
/*[[[body:libc_recallocarray]]]*/
/*AUTO*/{
	if (mallptr != NULL && old_elem_count != 0) {
		void *result;
		size_t oldusable, newneeded;
		oldusable = malloc_usable_size(mallptr);
		newneeded = new_elem_count * elem_size;
		if (oldusable >= newneeded) {
			if (old_elem_count > new_elem_count) {
				size_t zero_bytes;
				zero_bytes = (old_elem_count - new_elem_count) * elem_size;
				explicit_bzero((byte_t *)mallptr + newneeded, zero_bytes);
			}
			return mallptr;
		}
		/* Allocate a new block so we can ensure that an
		 * existing block gets freezero()'ed in all cases */
		result = calloc(new_elem_count, elem_size);
		if (result) {
			if (oldusable > newneeded)
				oldusable = newneeded;
			memcpy(result, mallptr, oldusable);
			freezero(mallptr, old_elem_count * elem_size);
		}
		return result;
	}
	return recallocv(mallptr, new_elem_count, elem_size);
}
/*[[[end:libc_recallocarray]]]*/

/*[[[head:libc_freezero,hash:CRC-32=0xe08eaf1c]]]*/
/* Same as `free(mallptr)', but also ensure that the memory region
 * described by `mallptr...+=size' is explicitly freed to zero, or
 * immediately returned to the OS, rather than being left in cache
 * while still containing its previous contents. */
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") void
NOTHROW_NCX(LIBCCALL libc_freezero)(void *mallptr,
                                    size_t size)
/*[[[body:libc_freezero]]]*/
/*AUTO*/{
	if likely(mallptr) {
		explicit_bzero(mallptr, size);
		free(mallptr);
	}
}
/*[[[end:libc_freezero]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xad665e64]]]*/
DEFINE_PUBLIC_ALIAS(getenv, libc_getenv);
DEFINE_PUBLIC_ALIAS(system, libc_system);
DEFINE_PUBLIC_ALIAS(exit, libc_exit);
DEFINE_PUBLIC_ALIAS(atexit, libc_atexit);
DEFINE_PUBLIC_ALIAS(quick_exit, libc_quick_exit);
DEFINE_PUBLIC_ALIAS(at_quick_exit, libc_at_quick_exit);
DEFINE_PUBLIC_ALIAS(_exit, libc__Exit);
DEFINE_PUBLIC_ALIAS(_Exit, libc__Exit);
DEFINE_PUBLIC_ALIAS(srand, libc_srand);
DEFINE_PUBLIC_ALIAS(rand, libc_rand);
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
DEFINE_PUBLIC_ALIAS(on_exit, libc_on_exit);
DEFINE_PUBLIC_ALIAS(clearenv, libc_clearenv);
DEFINE_PUBLIC_ALIAS(mkstemps, libc_mkstemps);
DEFINE_PUBLIC_ALIAS(rpmatch, libc_rpmatch);
DEFINE_PUBLIC_ALIAS(mkstemps64, libc_mkstemps64);
DEFINE_PUBLIC_ALIAS(rand_r, libc_rand_r);
DEFINE_PUBLIC_ALIAS(getloadavg, libc_getloadavg);
DEFINE_PUBLIC_ALIAS(drand48, libc_drand48);
DEFINE_PUBLIC_ALIAS(lrand48, libc_lrand48);
DEFINE_PUBLIC_ALIAS(mrand48, libc_mrand48);
DEFINE_PUBLIC_ALIAS(erand48, libc_erand48);
DEFINE_PUBLIC_ALIAS(nrand48, libc_nrand48);
DEFINE_PUBLIC_ALIAS(jrand48, libc_jrand48);
DEFINE_PUBLIC_ALIAS(srand48, libc_srand48);
DEFINE_PUBLIC_ALIAS(seed48, libc_seed48);
DEFINE_PUBLIC_ALIAS(lcong48, libc_lcong48);
DEFINE_PUBLIC_ALIAS(_putenv, libc_putenv);
DEFINE_PUBLIC_ALIAS(putenv, libc_putenv);
DEFINE_PUBLIC_ALIAS(random, libc_random);
DEFINE_PUBLIC_ALIAS(srandom, libc_srandom);
DEFINE_PUBLIC_ALIAS(initstate, libc_initstate);
DEFINE_PUBLIC_ALIAS(setstate, libc_setstate);
DEFINE_PUBLIC_ALIAS(l64a, libc_l64a);
DEFINE_PUBLIC_ALIAS(a64l, libc_a64l);
DEFINE_PUBLIC_ALIAS(realpath, libc_realpath);
DEFINE_PUBLIC_ALIAS(frealpath, libc_frealpath);
DEFINE_PUBLIC_ALIAS(frealpath4, libc_frealpath4);
DEFINE_PUBLIC_ALIAS(frealpathat, libc_frealpathat);
DEFINE_PUBLIC_ALIAS(setenv, libc_setenv);
DEFINE_PUBLIC_ALIAS(unsetenv, libc_unsetenv);
DEFINE_PUBLIC_ALIAS(__mktemp, libc_mktemp);
DEFINE_PUBLIC_ALIAS(mktemp, libc_mktemp);
DEFINE_PUBLIC_ALIAS(mkstemp, libc_mkstemp);
DEFINE_PUBLIC_ALIAS(mkstemp64, libc_mkstemp64);
DEFINE_PUBLIC_ALIAS(mkdtemp, libc_mkdtemp);
DEFINE_PUBLIC_ALIAS(grantpt, libc_grantpt);
DEFINE_PUBLIC_ALIAS(unlockpt, libc_unlockpt);
DEFINE_PUBLIC_ALIAS(ptsname, libc_ptsname);
DEFINE_PUBLIC_ALIAS(posix_openpt, libc_posix_openpt);
DEFINE_PUBLIC_ALIAS(__secure_getenv, libc_secure_getenv);
DEFINE_PUBLIC_ALIAS(secure_getenv, libc_secure_getenv);
DEFINE_PUBLIC_ALIAS(ptsname_r, libc_ptsname_r);
DEFINE_PUBLIC_ALIAS(getpt, libc_getpt);
DEFINE_PUBLIC_ALIAS(canonicalize_file_name, libc_canonicalize_file_name);
DEFINE_PUBLIC_ALIAS(mkostemp, libc_mkostemp);
DEFINE_PUBLIC_ALIAS(mkostemps, libc_mkostemps);
DEFINE_PUBLIC_ALIAS(mkostemp64, libc_mkostemp64);
DEFINE_PUBLIC_ALIAS(mkostemps64, libc_mkostemps64);
DEFINE_PUBLIC_ALIAS(reallocf, libc_reallocf);
DEFINE_PUBLIC_ALIAS(recallocarray, libc_recallocarray);
DEFINE_PUBLIC_ALIAS(freezero, libc_freezero);
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
DEFINE_PUBLIC_ALIAS(getenv_s, libc_getenv_s);
DEFINE_PUBLIC_ALIAS(_dupenv_s, libc__dupenv_s);
DEFINE_PUBLIC_ALIAS(_fullpath, libc__fullpath);
DEFINE_PUBLIC_ALIAS(_searchenv_s, libc__searchenv_s);
DEFINE_PUBLIC_ALIAS(_seterrormode, libc__seterrormode);
DEFINE_PUBLIC_ALIAS(_set_error_mode, libc__set_error_mode);
DEFINE_PUBLIC_ALIAS(_beep, libc__beep);
DEFINE_PUBLIC_ALIAS(_onexit, libc_onexit);
DEFINE_PUBLIC_ALIAS(onexit, libc_onexit);
DEFINE_PUBLIC_ALIAS(DOS$_wgetenv, libd__wgetenv);
DEFINE_PUBLIC_ALIAS(_wgetenv, libc__wgetenv);
DEFINE_PUBLIC_ALIAS(DOS$_wgetenv_s, libd__wgetenv_s);
DEFINE_PUBLIC_ALIAS(_wgetenv_s, libc__wgetenv_s);
DEFINE_PUBLIC_ALIAS(DOS$_wdupenv_s, libd__wdupenv_s);
DEFINE_PUBLIC_ALIAS(_wdupenv_s, libc__wdupenv_s);
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
