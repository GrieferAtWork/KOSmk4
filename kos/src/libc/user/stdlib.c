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
#ifndef GUARD_LIBC_USER_STDLIB_C
#define GUARD_LIBC_USER_STDLIB_C 1

#include "../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-once.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/process.h>
#include <kos/syscalls.h>
#include <parts/dos/errno.h>
#include <parts/errno.h>
#include <sys/wait.h>
#include <sys/auxv.h>

#include <assert.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <malloc.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#include "../libc/init.h"
#include "stdlib.h"

DECL_BEGIN

#undef __libc_geterrno_or
#define __libc_geterrno_or(alt) libc_geterrno()

#undef environ
#ifndef __environ_defined
#define __environ_defined 1
extern char **environ;
#endif /* !__environ_defined */
DECLARE_NOREL_GLOBAL_META(char **, environ);
#define environ  GET_NOREL_GLOBAL(environ)
INTDEF struct atomic_rwlock libc_environ_lock;

/* Since `environ' can easily contain strings that weren't allocated
 * using `malloc()' and friends, as well as since `putenv()' exists,
 * which can be used to directly inject user-provided strings into
 * the environ map, we run into a problem when it comes to preventing
 * memory leaks in regards of strings that _were_ injected dynamically
 * through use of functions such as `setenv()'
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



#undef __argc
#undef __argv
#undef _pgmptr
DEFINE_NOREL_GLOBAL_META(int, __argc, ".crt.dos.application.init");
DEFINE_NOREL_GLOBAL_META(char **, __argv, ".crt.dos.application.init");
DEFINE_NOREL_GLOBAL_META(char *, _pgmptr, ".crt.dos.application.init");
#define __argc  GET_NOREL_GLOBAL(__argc)
#define __argv  GET_NOREL_GLOBAL(__argv)
#define _pgmptr GET_NOREL_GLOBAL(_pgmptr)





DEFINE_PUBLIC_ALIAS(__cxa_atexit, libc___cxa_atexit);
INTERN ATTR_SECTION(".text.crt.sched.process.__cxa_atexit") int
NOTHROW_NCX(LIBCCALL libc___cxa_atexit)(void (LIBCCALL *func)(void *arg),
                                        void *arg, void *dso_handle) {
	/* NOTE: I don't really understand why this function is even necessary...
	 *       I mean sure: it allows c++ to register destructor callbacks lazily
	 *       for local statics, however the same effect could be achieved by using
	 *       an __attribute__((destructor)), where its callback checks some kind of
	 *       was-initialized flag and invokes that callback when this is true. */
	/* HINT: `dso_handle' is `NULL' for the primary module (in which case
	 *       the registered function must be called alongside atexit()), or
	 *       is some arbitrary pointer apart of the static image of the
	 *       associated binary (which can be resolved using `dlgethandle()') */
	/* TODO */
	return -1;
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

/*[[[head:srand,hash:CRC-32=0xc8e1187f]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.random.srand") void
NOTHROW(LIBCCALL libc_srand)(long seed)
/*[[[body:srand]]]*/
{
	libc_seed = (u32)(unsigned long)seed;
}
/*[[[end:srand]]]*/

/*[[[head:rand,hash:CRC-32=0xc5723c5a]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.random.rand") int
NOTHROW(LIBCCALL libc_rand)(void)
/*[[[body:rand]]]*/
{
	unsigned int result;
	result = libc_do_random(&libc_seed);
#if IS_POWER_OF_TWO(RAND_MAX + 1)
	return (int)(result & RAND_MAX);
#else
	return (int)(result % (RAND_MAX + 1));
#endif
}
/*[[[end:rand]]]*/

/*[[[head:rand_r,hash:CRC-32=0xf9a72780]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.random.rand_r") int
NOTHROW_NCX(LIBCCALL libc_rand_r)(unsigned int *__restrict seed)
/*[[[body:rand_r]]]*/
{
	unsigned int result;
	result = libc_do_random(seed);
#if IS_POWER_OF_TWO(RAND_MAX + 1)
	return (int)(result & RAND_MAX);
#else
	return (int)(result % (RAND_MAX + 1));
#endif
}
/*[[[end:rand_r]]]*/

/*[[[impl:random]]]*/
/*[[[impl:srandom]]]*/
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


/*[[[head:rand_s,hash:CRC-32=0xa99a8e5]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.random.rand_s") errno_t
NOTHROW_NCX(LIBCCALL libc_rand_s)(unsigned int *__restrict randval)
/*[[[body:rand_s]]]*/
/*AUTO*/{
	if (!randval)
		return __EINVAL;
	*randval = libc_rand();
	return 0;
}
/*[[[end:rand_s]]]*/

/*[[[head:DOS$rand_s,hash:CRC-32=0xc2849c27]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.random.rand_s") errno_t
NOTHROW_NCX(LIBDCALL libd_rand_s)(unsigned int *__restrict randval)
/*[[[body:DOS$rand_s]]]*/
{
	if (!randval)
		return __DOS_EINVAL;
	*randval = libc_rand();
	return 0;
}
/*[[[end:DOS$rand_s]]]*/



/*[[[head:getenv,hash:CRC-32=0x27bd1e2e]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.environ.getenv") char *
NOTHROW_NCX(LIBCCALL libc_getenv)(char const *varname)
/*[[[body:getenv]]]*/
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
/*[[[end:getenv]]]*/




/*[[[head:setenv,hash:CRC-32=0xb3054959]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.environ.setenv") int
NOTHROW_NCX(LIBCCALL libc_setenv)(char const *varname,
                                  char const *val,
                                  int replace)
/*[[[body:setenv]]]*/
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
	memcpy(line->ehs_text, varname, namelen * sizeof(char));
	line->ehs_text[namelen] = '=';
	memcpy(line->ehs_text + namelen + 1, val, vallen * sizeof(char));
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
/*[[[end:setenv]]]*/

/*[[[head:unsetenv,hash:CRC-32=0xe95b689e]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.environ.unsetenv") int
NOTHROW_NCX(LIBCCALL libc_unsetenv)(char const *varname)
/*[[[body:unsetenv]]]*/
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
/*[[[end:unsetenv]]]*/

/*[[[head:clearenv,hash:CRC-32=0x13a7d7a3]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.environ.clearenv") int
NOTHROW_NCX(LIBCCALL libc_clearenv)(void)
/*[[[body:clearenv]]]*/
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
/*[[[end:clearenv]]]*/

/*[[[head:putenv,hash:CRC-32=0x18400de0]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.environ.putenv") int
NOTHROW_NCX(LIBCCALL libc_putenv)(char *string)
/*[[[body:putenv]]]*/
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
/*[[[end:putenv]]]*/

/*[[[head:secure_getenv,hash:CRC-32=0xc94db2bd]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.environ.secure_getenv") char *
NOTHROW_NCX(LIBCCALL libc_secure_getenv)(char const *varname)
/*[[[body:secure_getenv]]]*/
{
	if (getauxval(AT_SECURE))
		return NULL; /* Unconditionally return `NULL' for setuid() programs */
	return getenv(varname);
}
/*[[[end:secure_getenv]]]*/

/*[[[head:_putenv_s,hash:CRC-32=0x9712fa75]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.environ._putenv_s") errno_t
NOTHROW_NCX(LIBCCALL libc__putenv_s)(char const *varname,
                                     char const *val)
/*[[[body:_putenv_s]]]*/
/*AUTO*/{
	return libc_setenv(varname, val, 1) ? __libc_geterrno_or(__EINVAL) : 0;
}
/*[[[end:_putenv_s]]]*/

/*[[[head:_dupenv_s,hash:CRC-32=0x70fe2978]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.utility._dupenv_s") errno_t
NOTHROW_NCX(LIBCCALL libc__dupenv_s)(char **__restrict pbuf,
                                     size_t *pbuflen,
                                     char const *varname)
/*[[[body:_dupenv_s]]]*/
{
	CRT_UNIMPLEMENTED("_dupenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_dupenv_s]]]*/

/*[[[head:getenv_s,hash:CRC-32=0x96a565cd]]]*/
INTERN NONNULL((1, 2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.utility.getenv_s") errno_t
NOTHROW_NCX(LIBCCALL libc_getenv_s)(size_t *psize,
                                    char *buf,
                                    rsize_t bufsize,
                                    char const *varname)
/*[[[body:getenv_s]]]*/
{
	CRT_UNIMPLEMENTED("getenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:getenv_s]]]*/

/*[[[head:_searchenv_s,hash:CRC-32=0x5cde1c3]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility._searchenv_s") errno_t
NOTHROW_RPC(LIBCCALL libc__searchenv_s)(char const *file,
                                        char const *envvar,
                                        char *__restrict resultpath,
                                        size_t buflen)
/*[[[body:_searchenv_s]]]*/
{
	CRT_UNIMPLEMENTED("_searchenv_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_searchenv_s]]]*/

/*[[[head:_searchenv,hash:CRC-32=0xcf9d896b]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility._searchenv") void
NOTHROW_RPC(LIBCCALL libc__searchenv)(char const *file,
                                      char const *envvar,
                                      char *__restrict resultpath)
/*[[[body:_searchenv]]]*/
/*AUTO*/{
	libc__searchenv_s(file, envvar, resultpath, (size_t)-1);
}
/*[[[end:_searchenv]]]*/



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

/*[[[head:system,hash:CRC-32=0x46b37e69]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.system.system") int
NOTHROW_RPC(LIBCCALL libc_system)(char const *__restrict command)
/*[[[body:system]]]*/
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
/*[[[end:system]]]*/

/*[[[head:abort,hash:CRC-32=0x1f73605]]]*/
INTERN ATTR_NORETURN
ATTR_WEAK ATTR_SECTION(".text.crt.application.exit.abort") void
(LIBCCALL libc_abort)(void)
/*[[[body:abort]]]*/
{
	_Exit(EXIT_FAILURE);
}
/*[[[end:abort]]]*/

/*[[[head:exit,hash:CRC-32=0x14509474]]]*/
INTERN ATTR_NORETURN
ATTR_WEAK ATTR_SECTION(".text.crt.application.exit.exit") void
(LIBCCALL libc_exit)(int status)
		__THROWS(...)
/*[[[body:exit]]]*/
{
	/* TODO: Run at-exit */
	/* TODO: Run library finalizers */
	libc_fini();
	_Exit(status);
}
/*[[[end:exit]]]*/

/*[[[head:atexit,hash:CRC-32=0x7b9caa0b]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.process.atexit") int
NOTHROW_NCX(LIBCCALL libc_atexit)(__atexit_func_t func)
/*[[[body:atexit]]]*/
{
	CRT_UNIMPLEMENTED("atexit"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:atexit]]]*/

/*[[[head:quick_exit,hash:CRC-32=0xfa3c2759]]]*/
INTERN ATTR_NORETURN
ATTR_WEAK ATTR_SECTION(".text.crt.sched.process.quick_exit") void
(LIBCCALL libc_quick_exit)(int status)
		__THROWS(...)
/*[[[body:quick_exit]]]*/
{
	/* TODO: Run quick-at-exit */
	/* TODO: Run library finalizers */
	_Exit(status);
}
/*[[[end:quick_exit]]]*/

/*[[[head:at_quick_exit,hash:CRC-32=0x8671a9ef]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.process.at_quick_exit") int
NOTHROW_NCX(LIBCCALL libc_at_quick_exit)(__atexit_func_t func)
/*[[[body:at_quick_exit]]]*/
{
	CRT_UNIMPLEMENTED("at_quick_exit"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:at_quick_exit]]]*/

/*[[[head:_Exit,hash:CRC-32=0x2a36c796]]]*/
INTERN ATTR_NORETURN
ATTR_WEAK ATTR_SECTION(".text.crt.application.exit._Exit") void
(LIBCCALL libc__Exit)(int status)
/*[[[body:_Exit]]]*/
{
	sys_exit_group((syscall_ulong_t)(unsigned int)status);
}
/*[[[end:_Exit]]]*/

/*[[[head:drand48_r,hash:CRC-32=0x739469fd]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.random.drand48_r") int
NOTHROW_NCX(LIBCCALL libc_drand48_r)(struct drand48_data *__restrict buffer,
                                     double *__restrict result)
/*[[[body:drand48_r]]]*/
{
	CRT_UNIMPLEMENTED("drand48_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:drand48_r]]]*/

/*[[[head:erand48_r,hash:CRC-32=0x241699f9]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.random.erand48_r") int
NOTHROW_NCX(LIBCCALL libc_erand48_r)(unsigned short xsubi[3],
                                     struct drand48_data *__restrict buffer,
                                     double *__restrict result)
/*[[[body:erand48_r]]]*/
{
	CRT_UNIMPLEMENTED("erand48_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:erand48_r]]]*/

/*[[[head:lrand48_r,hash:CRC-32=0x420a4735]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.random.lrand48_r") int
NOTHROW_NCX(LIBCCALL libc_lrand48_r)(struct drand48_data *__restrict buffer,
                                     long *__restrict result)
/*[[[body:lrand48_r]]]*/
{
	CRT_UNIMPLEMENTED("lrand48_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:lrand48_r]]]*/

/*[[[head:nrand48_r,hash:CRC-32=0xec488ce6]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.random.nrand48_r") int
NOTHROW_NCX(LIBCCALL libc_nrand48_r)(unsigned short xsubi[3],
                                     struct drand48_data *__restrict buffer,
                                     long *__restrict result)
/*[[[body:nrand48_r]]]*/
{
	CRT_UNIMPLEMENTED("nrand48_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:nrand48_r]]]*/

/*[[[head:mrand48_r,hash:CRC-32=0x78955e8e]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.random.mrand48_r") int
NOTHROW_NCX(LIBCCALL libc_mrand48_r)(struct drand48_data *__restrict buffer,
                                     long *__restrict result)
/*[[[body:mrand48_r]]]*/
{
	CRT_UNIMPLEMENTED("mrand48_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:mrand48_r]]]*/

/*[[[head:jrand48_r,hash:CRC-32=0xc1083299]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.random.jrand48_r") int
NOTHROW_NCX(LIBCCALL libc_jrand48_r)(unsigned short xsubi[3],
                                     struct drand48_data *__restrict buffer,
                                     long *__restrict result)
/*[[[body:jrand48_r]]]*/
{
	CRT_UNIMPLEMENTED("jrand48_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:jrand48_r]]]*/

/*[[[head:srand48_r,hash:CRC-32=0x6b07f412]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.random.srand48_r") int
NOTHROW_NCX(LIBCCALL libc_srand48_r)(long seedval,
                                     struct drand48_data *buffer)
/*[[[body:srand48_r]]]*/
{
	CRT_UNIMPLEMENTED("srand48_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:srand48_r]]]*/

/*[[[head:seed48_r,hash:CRC-32=0x879782f5]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.random.seed48_r") int
NOTHROW_NCX(LIBCCALL libc_seed48_r)(unsigned short seed16v[3],
                                    struct drand48_data *buffer)
/*[[[body:seed48_r]]]*/
{
	CRT_UNIMPLEMENTED("seed48_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:seed48_r]]]*/

/*[[[head:lcong48_r,hash:CRC-32=0xe15fdff8]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.random.lcong48_r") int
NOTHROW_NCX(LIBCCALL libc_lcong48_r)(unsigned short param[7],
                                     struct drand48_data *buffer)
/*[[[body:lcong48_r]]]*/
{
	CRT_UNIMPLEMENTED("lcong48_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:lcong48_r]]]*/

/*[[[head:random_r,hash:CRC-32=0x36c5a774]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.random.random_r") int
NOTHROW_NCX(LIBCCALL libc_random_r)(struct random_data *__restrict buf,
                                    int32_t *__restrict result)
/*[[[body:random_r]]]*/
{
	CRT_UNIMPLEMENTED("random_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:random_r]]]*/

/*[[[head:srandom_r,hash:CRC-32=0xa0691f77]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.random.srandom_r") int
NOTHROW_NCX(LIBCCALL libc_srandom_r)(unsigned int seed,
                                     struct random_data *buf)
/*[[[body:srandom_r]]]*/
{
	CRT_UNIMPLEMENTED("srandom_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:srandom_r]]]*/

/*[[[head:initstate_r,hash:CRC-32=0x9d6e3c55]]]*/
INTERN NONNULL((2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.random.initstate_r") int
NOTHROW_NCX(LIBCCALL libc_initstate_r)(unsigned int seed,
                                       char *__restrict statebuf,
                                       size_t statelen,
                                       struct random_data *__restrict buf)
/*[[[body:initstate_r]]]*/
{
	CRT_UNIMPLEMENTED("initstate_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:initstate_r]]]*/

/*[[[head:setstate_r,hash:CRC-32=0xfbc7d8a5]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.random.setstate_r") int
NOTHROW_NCX(LIBCCALL libc_setstate_r)(char *__restrict statebuf,
                                      struct random_data *__restrict buf)
/*[[[body:setstate_r]]]*/
{
	CRT_UNIMPLEMENTED("setstate_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:setstate_r]]]*/

/*[[[head:on_exit,hash:CRC-32=0xcd734836]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.process.on_exit") int
NOTHROW_NCX(LIBCCALL libc_on_exit)(__on_exit_func_t func,
                                   void *arg)
/*[[[body:on_exit]]]*/
{
	CRT_UNIMPLEMENTED("on_exit"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:on_exit]]]*/

/*[[[head:mkstemps,hash:CRC-32=0x78f97579]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.mkstemps") int
NOTHROW_NCX(LIBCCALL libc_mkstemps)(char *template_,
                                    int suffixlen)
/*[[[body:mkstemps]]]*/
{
	CRT_UNIMPLEMENTED("mkstemps"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:mkstemps]]]*/

/*[[[head:rpmatch,hash:CRC-32=0x1e8600e1]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.rpmatch") int
NOTHROW_NCX(LIBCCALL libc_rpmatch)(char const *response)
/*[[[body:rpmatch]]]*/
{
	CRT_UNIMPLEMENTED("rpmatch"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:rpmatch]]]*/

/*[[[head:mkstemps64,hash:CRC-32=0x5ce33c02]]]*/
#if !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0
DEFINE_INTERN_ALIAS(libc_mkstemps64, libc_mkstemps);
#else
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.mkstemps64") int
NOTHROW_NCX(LIBCCALL libc_mkstemps64)(char *template_,
                                      int suffixlen)
/*[[[body:mkstemps64]]]*/
{
	CRT_UNIMPLEMENTED("mkstemps64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:mkstemps64]]]*/

/*[[[head:getloadavg,hash:CRC-32=0x24f50b2d]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.utility.getloadavg") int
NOTHROW_RPC(LIBCCALL libc_getloadavg)(double loadavg[],
                                      int nelem)
/*[[[body:getloadavg]]]*/
{
	CRT_UNIMPLEMENTED("getloadavg"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getloadavg]]]*/

/*[[[head:drand48,hash:CRC-32=0x415f3fb9]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.random.drand48") double
NOTHROW_NCX(LIBCCALL libc_drand48)(void)
/*[[[body:drand48]]]*/
{
	CRT_UNIMPLEMENTED("drand48"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:drand48]]]*/

/*[[[head:lrand48,hash:CRC-32=0xf8e8f88d]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.random.lrand48") long
NOTHROW_NCX(LIBCCALL libc_lrand48)(void)
/*[[[body:lrand48]]]*/
{
	CRT_UNIMPLEMENTED("lrand48"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:lrand48]]]*/

/*[[[head:mrand48,hash:CRC-32=0x47e4aaeb]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.random.mrand48") long
NOTHROW_NCX(LIBCCALL libc_mrand48)(void)
/*[[[body:mrand48]]]*/
{
	CRT_UNIMPLEMENTED("mrand48"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:mrand48]]]*/

/*[[[head:erand48,hash:CRC-32=0x5f030d9a]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.random.erand48") double
NOTHROW_NCX(LIBCCALL libc_erand48)(unsigned short xsubi[3])
/*[[[body:erand48]]]*/
{
	CRT_UNIMPLEMENTED("erand48"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:erand48]]]*/

/*[[[head:nrand48,hash:CRC-32=0x82ab480]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.random.nrand48") long
NOTHROW_NCX(LIBCCALL libc_nrand48)(unsigned short xsubi[3])
/*[[[body:nrand48]]]*/
{
	CRT_UNIMPLEMENTED("nrand48"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:nrand48]]]*/

/*[[[head:jrand48,hash:CRC-32=0xf83d7ea2]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.random.jrand48") long
NOTHROW_NCX(LIBCCALL libc_jrand48)(unsigned short xsubi[3])
/*[[[body:jrand48]]]*/
{
	CRT_UNIMPLEMENTED("jrand48"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:jrand48]]]*/

/*[[[head:srand48,hash:CRC-32=0x54f59449]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.random.srand48") void
NOTHROW_NCX(LIBCCALL libc_srand48)(long seedval)
/*[[[body:srand48]]]*/
{
	CRT_UNIMPLEMENTED("srand48"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:srand48]]]*/

/*[[[head:seed48,hash:CRC-32=0x66816c1a]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.random.seed48") unsigned short *
NOTHROW_NCX(LIBCCALL libc_seed48)(unsigned short seed16v[3])
/*[[[body:seed48]]]*/
{
	CRT_UNIMPLEMENTED("seed48"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:seed48]]]*/

/*[[[head:lcong48,hash:CRC-32=0xd5ba93ee]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.random.lcong48") void
NOTHROW_NCX(LIBCCALL libc_lcong48)(unsigned short param[7])
/*[[[body:lcong48]]]*/
{
	CRT_UNIMPLEMENTED("lcong48"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:lcong48]]]*/

/*[[[head:initstate,hash:CRC-32=0x533d5321]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.random.initstate") char *
NOTHROW_NCX(LIBCCALL libc_initstate)(unsigned int seed,
                                     char *statebuf,
                                     size_t statelen)
/*[[[body:initstate]]]*/
{
	CRT_UNIMPLEMENTED("initstate"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:initstate]]]*/

/*[[[head:setstate,hash:CRC-32=0x7172660c]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.random.setstate") char *
NOTHROW_NCX(LIBCCALL libc_setstate)(char *statebuf)
/*[[[body:setstate]]]*/
{
	CRT_UNIMPLEMENTED("setstate"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:setstate]]]*/

/*[[[head:l64a,hash:CRC-32=0x913a8790]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.string.encrypt.l64a") char *
NOTHROW_NCX(LIBCCALL libc_l64a)(long n)
/*[[[body:l64a]]]*/
{
	CRT_UNIMPLEMENTED("l64a"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:l64a]]]*/

/*[[[head:a64l,hash:CRC-32=0xa0e1d45a]]]*/
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.encrypt.a64l") long
NOTHROW_NCX(LIBCCALL libc_a64l)(char const *s)
/*[[[body:a64l]]]*/
{
	CRT_UNIMPLEMENTED("a64l"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:a64l]]]*/

/*[[[head:realpath,hash:CRC-32=0x2dea3a06]]]*/
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL to automatically `malloc()'ate and return a
 *                   buffer of sufficient size. */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.property.realpath") char *
NOTHROW_RPC(LIBCCALL libc_realpath)(char const *__restrict filename,
                                    char *resolved)
/*[[[body:realpath]]]*/
{
	return libc_frealpathat(AT_FDCWD, filename, resolved,
	                        resolved ? PATH_MAX : 0, 0);
}
/*[[[end:realpath]]]*/

/*[[[head:frealpath,hash:CRC-32=0xde151c69]]]*/
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `bufsize'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `bufsize' to automatically determine the required buffer size. */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.fs.property.frealpath") char *
NOTHROW_RPC(LIBCCALL libc_frealpath)(fd_t fd,
                                     char *resolved,
                                     size_t bufsize)
/*[[[body:frealpath]]]*/
{
	return frealpath4(fd, resolved, bufsize, 0);
}
/*[[[end:frealpath]]]*/

/*[[[head:frealpath4,hash:CRC-32=0x103a07d1]]]*/
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0|AT_ALTPATH|AT_DOSPATH'
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `bufsize'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `bufsize' to automatically determine the required buffer size. */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.fs.property.frealpath4") char *
NOTHROW_RPC(LIBCCALL libc_frealpath4)(fd_t fd,
                                      char *resolved,
                                      size_t bufsize,
                                      atflag_t flags)
/*[[[body:frealpath4]]]*/
{
	ssize_t result;
	char *buffer = resolved;
	if unlikely(flags & AT_READLINK_REQSIZE) {
		libc_seterrno(EINVAL);
		return NULL;
	}
	if (!resolved) {
		if (!bufsize) {
			/* Automatically allocate + determine buffer size. */
			bufsize = PATH_MAX;
			buffer  = (char *)malloc(bufsize);
			if unlikely(!buffer)
				bufsize = 0;
			for (;;) {
				result = sys_frealpath4(fd,
				                        buffer,
				                        bufsize,
				                        flags | AT_READLINK_REQSIZE);
				if unlikely(E_ISERR(result))
					goto err_buffer_result_errno;
				if likely((size_t)result <= bufsize)
					break;
				/* Allocate the required amount of memory. */
				resolved = (char *)realloc(buffer, (size_t)result);
				if unlikely(!resolved) {
					free(buffer);
					return NULL;
				}
				bufsize = (size_t)result;
				buffer  = resolved;
			}
			if ((size_t)result != bufsize) {
				resolved = (char *)realloc(buffer, (size_t)result);
				if likely(resolved)
					buffer = resolved;
			}
			return buffer;
		}
		buffer = (char *)malloc(bufsize);
		if unlikely(!buffer)
			goto done;
	}
	result = sys_frealpath4(fd,
	                        buffer,
	                        bufsize,
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
/*[[[end:frealpath4]]]*/

/*[[[head:frealpathat,hash:CRC-32=0x2a5dcd44]]]*/
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_FOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `bufsize'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `bufsize' to automatically determine the required buffer size.
 * @param flags: Set of `0|AT_ALTPATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.property.frealpathat") char *
NOTHROW_RPC(LIBCCALL libc_frealpathat)(fd_t dirfd,
                                       char const *filename,
                                       char *resolved,
                                       size_t bufsize,
                                       atflag_t flags)
/*[[[body:frealpathat]]]*/
{
	ssize_t result;
	char *buffer = resolved;
	if unlikely(flags & AT_READLINK_REQSIZE) {
		libc_seterrno(EINVAL);
		return NULL;
	}
	if (!resolved) {
		if (!bufsize) {
			/* Automatically allocate + determine buffer size. */
			bufsize = PATH_MAX;
			buffer  = (char *)malloc(bufsize);
			if unlikely(!buffer)
				bufsize = 0;
			for (;;) {
				result = sys_frealpathat(dirfd,
				                         filename,
				                         buffer,
				                         bufsize,
				                         flags | AT_READLINK_REQSIZE);
				if unlikely(E_ISERR(result))
					goto err_buffer_result_errno;
				if
					likely((size_t)result <= bufsize)
				break;
				/* Allocate the required amount of memory. */
				resolved = (char *)realloc(buffer, (size_t)result);
				if unlikely(!resolved) {
					free(buffer);
					return NULL;
				}
				bufsize = (size_t)result;
				buffer  = resolved;
			}
			if ((size_t)result != bufsize) {
				resolved = (char *)realloc(buffer, (size_t)result);
				if likely(resolved)
					buffer = resolved;
			}
			return buffer;
		}
		buffer = (char *)malloc(bufsize);
		if unlikely(!buffer)
			goto done;
	}
	result = sys_frealpathat(dirfd,
	                         filename,
	                         buffer,
	                         bufsize,
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
/*[[[end:frealpathat]]]*/

/*[[[head:mktemp,hash:CRC-32=0x1e8369]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.mktemp") char *
NOTHROW_NCX(LIBCCALL libc_mktemp)(char *template_)
/*[[[body:mktemp]]]*/
{
	CRT_UNIMPLEMENTED("mktemp"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:mktemp]]]*/

/*[[[head:mkstemp,hash:CRC-32=0x3c28455d]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.mkstemp") int
NOTHROW_NCX(LIBCCALL libc_mkstemp)(char *template_)
/*[[[body:mkstemp]]]*/
{
	CRT_UNIMPLEMENTED("mkstemp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:mkstemp]]]*/

/*[[[head:mkdtemp,hash:CRC-32=0x2efcd67b]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.mkdtemp") char *
NOTHROW_NCX(LIBCCALL libc_mkdtemp)(char *template_)
/*[[[body:mkdtemp]]]*/
{
	CRT_UNIMPLEMENTED("mkdtemp"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:mkdtemp]]]*/

/*[[[head:setkey,hash:CRC-32=0x2efe9326]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.setkey") void
NOTHROW_NCX(LIBCCALL libc_setkey)(char const *key)
/*[[[body:setkey]]]*/
{
	CRT_UNIMPLEMENTED("setkey"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:setkey]]]*/

/*[[[head:grantpt,hash:CRC-32=0xaef0dcd4]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.grantpt") int
NOTHROW_NCX(LIBCCALL libc_grantpt)(fd_t fd)
/*[[[body:grantpt]]]*/
{
	CRT_UNIMPLEMENTED("grantpt"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:grantpt]]]*/

/*[[[head:unlockpt,hash:CRC-32=0xbf9aab92]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.unlockpt") int
NOTHROW_NCX(LIBCCALL libc_unlockpt)(fd_t fd)
/*[[[body:unlockpt]]]*/
{
	CRT_UNIMPLEMENTED("unlockpt"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:unlockpt]]]*/

/*[[[head:ptsname,hash:CRC-32=0x2e14f3ce]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.ptsname") char *
NOTHROW_NCX(LIBCCALL libc_ptsname)(fd_t fd)
/*[[[body:ptsname]]]*/
{
	CRT_UNIMPLEMENTED("ptsname"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:ptsname]]]*/

/*[[[head:posix_openpt,hash:CRC-32=0xea4ea142]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.posix_openpt") int
NOTHROW_RPC(LIBCCALL libc_posix_openpt)(oflag_t oflag)
/*[[[body:posix_openpt]]]*/
{
	CRT_UNIMPLEMENTED("posix_openpt"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_openpt]]]*/

/*[[[head:getpt,hash:CRC-32=0x4662c95f]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.getpt") int
NOTHROW_RPC(LIBCCALL libc_getpt)(void)
/*[[[body:getpt]]]*/
{
	CRT_UNIMPLEMENTED("getpt"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getpt]]]*/

/*[[[head:ptsname_r,hash:CRC-32=0xa47ed5ed]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.ptsname_r") int
NOTHROW_NCX(LIBCCALL libc_ptsname_r)(fd_t fd,
                                     char *buf,
                                     size_t buflen)
/*[[[body:ptsname_r]]]*/
{
	CRT_UNIMPLEMENTED("ptsname_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:ptsname_r]]]*/

/*[[[head:canonicalize_file_name,hash:CRC-32=0x7a381eaf]]]*/
/* Return the result of `realpath(filename)' as a `malloc()'-allocated buffer
 * Upon error, `NULL' is returned instead */
INTERN ATTR_MALLOC WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.property.canonicalize_file_name") char *
NOTHROW_RPC(LIBCCALL libc_canonicalize_file_name)(char const *filename)
/*[[[body:canonicalize_file_name]]]*/
{
	return realpath(filename, NULL);
}
/*[[[end:canonicalize_file_name]]]*/

/*[[[head:mkostemp,hash:CRC-32=0x57c47d03]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.mkostemp") int
NOTHROW_RPC(LIBCCALL libc_mkostemp)(char *template_,
                                    int flags)
/*[[[body:mkostemp]]]*/
{
	CRT_UNIMPLEMENTED("mkostemp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:mkostemp]]]*/

/*[[[head:mkostemps,hash:CRC-32=0xa2715472]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.mkostemps") int
NOTHROW_RPC(LIBCCALL libc_mkostemps)(char *template_,
                                     int suffixlen,
                                     int flags)
/*[[[body:mkostemps]]]*/
{
	CRT_UNIMPLEMENTED("mkostemps"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:mkostemps]]]*/

/*[[[head:mkostemp64,hash:CRC-32=0xfa792204]]]*/
#if !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0
DEFINE_INTERN_ALIAS(libc_mkostemp64, libc_mkostemp);
#else
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.mkostemp64") int
NOTHROW_RPC(LIBCCALL libc_mkostemp64)(char *template_,
                                      int flags)
/*[[[body:mkostemp64]]]*/
{
	CRT_UNIMPLEMENTED("mkostemp64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:mkostemp64]]]*/

/*[[[head:mkostemps64,hash:CRC-32=0x9f5110c3]]]*/
#if !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0
DEFINE_INTERN_ALIAS(libc_mkostemps64, libc_mkostemps);
#else
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.utility.mkostemps64") int
NOTHROW_RPC(LIBCCALL libc_mkostemps64)(char *template_,
                                       int suffixlen,
                                       int flags)
/*[[[body:mkostemps64]]]*/
{
	CRT_UNIMPLEMENTED("mkostemps64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:mkostemps64]]]*/

/* `__errno_location' is provided in libc/errno.c */
/*[[[skip:__errno_location]]]*/

/*[[[head:__p___argc,hash:CRC-32=0xb5855cce]]]*/
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.application.init.__p___argc") int *
NOTHROW_NCX(LIBCCALL libc___p___argc)(void)
/*[[[body:__p___argc]]]*/
{
	return &__argc;
}
/*[[[end:__p___argc]]]*/

/*[[[head:__p___argv,hash:CRC-32=0x3c793cc4]]]*/
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.application.init.__p___argv") char ***
NOTHROW_NCX(LIBCCALL libc___p___argv)(void)
/*[[[body:__p___argv]]]*/
{
	return &__argv;
}
/*[[[end:__p___argv]]]*/

/*[[[head:__p__pgmptr,hash:CRC-32=0x9b4880c2]]]*/
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.application.init.__p__pgmptr") char **
NOTHROW_NCX(LIBCCALL libc___p__pgmptr)(void)
/*[[[body:__p__pgmptr]]]*/
{
	return &_pgmptr;
}
/*[[[end:__p__pgmptr]]]*/

PRIVATE ATTR_CONST WUNUSED
ATTR_SECTION(".text.crt.dos.application.init.__p___initenv.get_initenv")
char **NOTHROW(libc_get_initenv)(void) {
	struct process_peb *peb;
	char **result;
	peb    = (struct process_peb *)dlsym(RTLD_DEFAULT, "__peb");
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

/*[[[head:__p___initenv,hash:CRC-32=0x9fe24b00]]]*/
/* Access to the initial environment block */
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.dos.application.init.__p___initenv") char ***
NOTHROW_NCX(LIBCCALL libc___p___initenv)(void)
/*[[[body:__p___initenv]]]*/
{
	ATOMIC_ONCE_RUN(&libc___p___initenv_initialized, {
		libc___p___initenv_pointer = libc_get_initenv();
	});
	return &libc___p___initenv_pointer;
}
/*[[[end:__p___initenv]]]*/

/*[[[head:_aligned_malloc,hash:CRC-32=0x4d8c91f2]]]*/
INTERN ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) ATTR_ALLOC_ALIGN(2)
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap._aligned_malloc") void *
NOTHROW_NCX(LIBCCALL libc__aligned_malloc)(size_t num_bytes,
                                           size_t min_alignment)
/*[[[body:_aligned_malloc]]]*/
{
	CRT_UNIMPLEMENTED("_aligned_malloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:_aligned_malloc]]]*/

/*[[[head:DOS$__p__wenviron,hash:CRC-32=0x2a342ca3]]]*/
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.application.init.__p__wenviron") char16_t ***
NOTHROW_NCX(LIBDCALL libd___p__wenviron)(void)
/*[[[body:DOS$__p__wenviron]]]*/
{
	CRT_UNIMPLEMENTED("__p__wenviron"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$__p__wenviron]]]*/

/*[[[head:__p__wenviron,hash:CRC-32=0x25cb482c]]]*/
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.application.init.__p__wenviron") char32_t ***
NOTHROW_NCX(LIBCCALL libc___p__wenviron)(void)
/*[[[body:__p__wenviron]]]*/
{
	CRT_UNIMPLEMENTED("__p__wenviron"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__p__wenviron]]]*/

/*[[[head:DOS$__p___winitenv,hash:CRC-32=0xea43d103]]]*/
/* Access to the initial environment block */
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.dos.application.init.__p___winitenv") char16_t ***
NOTHROW_NCX(LIBDCALL libd___p___winitenv)(void)
/*[[[body:DOS$__p___winitenv]]]*/
{
	CRT_UNIMPLEMENTED("__p___winitenv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$__p___winitenv]]]*/

/*[[[head:__p___winitenv,hash:CRC-32=0x974bb0d6]]]*/
/* Access to the initial environment block */
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.dos.application.init.__p___winitenv") char32_t ***
NOTHROW_NCX(LIBCCALL libc___p___winitenv)(void)
/*[[[body:__p___winitenv]]]*/
{
	CRT_UNIMPLEMENTED("__p___winitenv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__p___winitenv]]]*/

/*[[[head:DOS$__p___wargv,hash:CRC-32=0x15cc90ff]]]*/
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.application.init.__p___wargv") char16_t ***
NOTHROW_NCX(LIBDCALL libd___p___wargv)(void)
/*[[[body:DOS$__p___wargv]]]*/
{
	CRT_UNIMPLEMENTED("__p___wargv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$__p___wargv]]]*/

/*[[[head:__p__wpgmptr,hash:CRC-32=0xda4fb24e]]]*/
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.application.init.__p__wpgmptr") char32_t **
NOTHROW_NCX(LIBCCALL libc___p__wpgmptr)(void)
/*[[[body:__p__wpgmptr]]]*/
{
	CRT_UNIMPLEMENTED("__p__wpgmptr"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__p__wpgmptr]]]*/

/*[[[head:DOS$__p__wpgmptr,hash:CRC-32=0x87790bd9]]]*/
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.application.init.__p__wpgmptr") char16_t **
NOTHROW_NCX(LIBDCALL libd___p__wpgmptr)(void)
/*[[[body:DOS$__p__wpgmptr]]]*/
{
	CRT_UNIMPLEMENTED("__p__wpgmptr"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$__p__wpgmptr]]]*/

/*[[[head:_fullpath,hash:CRC-32=0xb89e2b18]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.utility._fullpath") char *
NOTHROW_RPC(LIBCCALL libc__fullpath)(char *buf,
                                     char const *path,
                                     size_t buflen)
/*[[[body:_fullpath]]]*/
{
	CRT_UNIMPLEMENTED("_fullpath"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:_fullpath]]]*/

/*[[[head:_aligned_free,hash:CRC-32=0xf8bd5941]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap._aligned_free") void
NOTHROW_NCX(LIBCCALL libc__aligned_free)(void *mptr)
/*[[[body:_aligned_free]]]*/
{
	CRT_UNIMPLEMENTED("_aligned_free"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:_aligned_free]]]*/

/*[[[head:_aligned_recalloc,hash:CRC-32=0x3628bac6]]]*/
INTERN WUNUSED ATTR_ALLOC_SIZE((2, 3)) ATTR_ALLOC_ALIGN(4)
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap._aligned_recalloc") void *
NOTHROW_NCX(LIBCCALL libc__aligned_recalloc)(void *mptr,
                                             size_t count,
                                             size_t num_bytes,
                                             size_t min_alignment)
/*[[[body:_aligned_recalloc]]]*/
{
	CRT_UNIMPLEMENTED("_aligned_recalloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:_aligned_recalloc]]]*/

/*[[[head:__doserrno,hash:CRC-32=0x65d90b38]]]*/
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.dos.errno.__doserrno") u32 *
NOTHROW_NCX(LIBCCALL libc___doserrno)(void)
/*[[[body:__doserrno]]]*/
{
	CRT_UNIMPLEMENTED("__doserrno"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__doserrno]]]*/

/*[[[head:__p___wargv,hash:CRC-32=0x871da926]]]*/
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.application.init.__p___wargv") char32_t ***
NOTHROW_NCX(LIBCCALL libc___p___wargv)(void)
/*[[[body:__p___wargv]]]*/
{
	CRT_UNIMPLEMENTED("__p___wargv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__p___wargv]]]*/

/*[[[head:_get_doserrno,hash:CRC-32=0x313fa82a]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.errno._get_doserrno") errno_t
NOTHROW_NCX(LIBCCALL libc__get_doserrno)(u32 *perr)
/*[[[body:_get_doserrno]]]*/
{
	CRT_UNIMPLEMENTED("_get_doserrno"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_get_doserrno]]]*/

/*[[[head:_aligned_offset_malloc,hash:CRC-32=0x2b246c46]]]*/
INTERN ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap._aligned_offset_malloc") void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_malloc)(size_t num_bytes,
                                                  size_t min_alignment,
                                                  size_t offset)
/*[[[body:_aligned_offset_malloc]]]*/
{
	CRT_UNIMPLEMENTED("_aligned_offset_malloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:_aligned_offset_malloc]]]*/

/*[[[head:_aligned_offset_realloc,hash:CRC-32=0x776dc7c4]]]*/
INTERN WUNUSED ATTR_ALLOC_SIZE((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap._aligned_offset_realloc") void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_realloc)(void *mptr,
                                                   size_t newsize,
                                                   size_t min_alignment,
                                                   size_t offset)
/*[[[body:_aligned_offset_realloc]]]*/
{
	CRT_UNIMPLEMENTED("_aligned_offset_realloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:_aligned_offset_realloc]]]*/

/*[[[head:_aligned_offset_recalloc,hash:CRC-32=0xb2922b1c]]]*/
INTERN WUNUSED ATTR_ALLOC_SIZE((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap._aligned_offset_recalloc") void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_recalloc)(void *mptr,
                                                    size_t count,
                                                    size_t num_bytes,
                                                    size_t min_alignment,
                                                    size_t offset)
/*[[[body:_aligned_offset_recalloc]]]*/
{
	CRT_UNIMPLEMENTED("_aligned_offset_recalloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:_aligned_offset_recalloc]]]*/

/*[[[head:_recalloc,hash:CRC-32=0x87d5769]]]*/
INTERN ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap._recalloc") void *
NOTHROW_NCX(LIBCCALL libc__recalloc)(void *mptr,
                                     size_t count,
                                     size_t num_bytes)
/*[[[body:_recalloc]]]*/
{
	CRT_UNIMPLEMENTED("_recalloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:_recalloc]]]*/

/*[[[head:_set_doserrno,hash:CRC-32=0x641cccdf]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.errno._set_doserrno") errno_t
NOTHROW_NCX(LIBCCALL libc__set_doserrno)(u32 err)
/*[[[body:_set_doserrno]]]*/
{
	CRT_UNIMPLEMENTED("_set_doserrno"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_set_doserrno]]]*/

/*[[[head:_set_error_mode,hash:CRC-32=0x2e83accf]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.errno._set_error_mode") int
NOTHROW_NCX(LIBCCALL libc__set_error_mode)(int mode)
/*[[[body:_set_error_mode]]]*/
{
	CRT_UNIMPLEMENTED("_set_error_mode"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_set_error_mode]]]*/

/*[[[head:_aligned_realloc,hash:CRC-32=0x6bdbbaea]]]*/
INTERN WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_ALLOC_ALIGN(3)
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap._aligned_realloc") void *
NOTHROW_NCX(LIBCCALL libc__aligned_realloc)(void *mptr,
                                            size_t newsize,
                                            size_t min_alignment)
/*[[[body:_aligned_realloc]]]*/
{
	CRT_UNIMPLEMENTED("_aligned_realloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:_aligned_realloc]]]*/

/*[[[head:onexit,hash:CRC-32=0x51f0023a]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.convert.onexit") onexit_t
NOTHROW_NCX(LIBCCALL libc_onexit)(onexit_t func)
/*[[[body:onexit]]]*/
{
	CRT_UNIMPLEMENTED("onexit"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:onexit]]]*/

/*[[[head:_wperror,hash:CRC-32=0xa5962fc3]]]*/
INTERN ATTR_COLD
ATTR_WEAK ATTR_SECTION(".text.crt.dos.errno._wperror") void
NOTHROW_RPC(LIBCCALL libc__wperror)(char32_t const *errmsg)
/*[[[body:_wperror]]]*/
{
	CRT_UNIMPLEMENTED("_wperror"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:_wperror]]]*/

/*[[[head:_seterrormode,hash:CRC-32=0x62b91e01]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.errno._seterrormode") void
NOTHROW_NCX(LIBCCALL libc__seterrormode)(int mode)
/*[[[body:_seterrormode]]]*/
{
	CRT_UNIMPLEMENTED("_seterrormode"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:_seterrormode]]]*/

/*[[[head:DOS$_wperror,hash:CRC-32=0xf1b3aa1]]]*/
INTERN ATTR_COLD
ATTR_WEAK ATTR_SECTION(".text.crt.dos.errno._wperror") void
NOTHROW_RPC(LIBDCALL libd__wperror)(char16_t const *errmsg)
/*[[[body:DOS$_wperror]]]*/
{
	CRT_UNIMPLEMENTED("_wperror"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:DOS$_wperror]]]*/

/*[[[head:_beep,hash:CRC-32=0xac9f7eb3]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.system._beep") void
NOTHROW_NCX(LIBCCALL libc__beep)(unsigned int freq,
                                 unsigned int duration)
/*[[[body:_beep]]]*/
{
	CRT_UNIMPLEMENTED("_beep"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:_beep]]]*/

/*[[[skip:malloc]]]*/
/*[[[skip:free]]]*/
/*[[[skip:calloc]]]*/
/*[[[skip:realloc]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x9e97d8b3]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(getenv, libc_getenv);
DEFINE_PUBLIC_WEAK_ALIAS(system, libc_system);
DEFINE_PUBLIC_WEAK_ALIAS(abort, libc_abort);
DEFINE_PUBLIC_WEAK_ALIAS(exit, libc_exit);
DEFINE_PUBLIC_WEAK_ALIAS(atexit, libc_atexit);
DEFINE_PUBLIC_WEAK_ALIAS(quick_exit, libc_quick_exit);
DEFINE_PUBLIC_WEAK_ALIAS(at_quick_exit, libc_at_quick_exit);
DEFINE_PUBLIC_WEAK_ALIAS(_Exit, libc__Exit);
DEFINE_PUBLIC_WEAK_ALIAS(_exit, libc__Exit);
DEFINE_PUBLIC_WEAK_ALIAS(srand, libc_srand);
DEFINE_PUBLIC_WEAK_ALIAS(rand, libc_rand);
DEFINE_PUBLIC_WEAK_ALIAS(drand48_r, libc_drand48_r);
DEFINE_PUBLIC_WEAK_ALIAS(erand48_r, libc_erand48_r);
DEFINE_PUBLIC_WEAK_ALIAS(lrand48_r, libc_lrand48_r);
DEFINE_PUBLIC_WEAK_ALIAS(nrand48_r, libc_nrand48_r);
DEFINE_PUBLIC_WEAK_ALIAS(mrand48_r, libc_mrand48_r);
DEFINE_PUBLIC_WEAK_ALIAS(jrand48_r, libc_jrand48_r);
DEFINE_PUBLIC_WEAK_ALIAS(srand48_r, libc_srand48_r);
DEFINE_PUBLIC_WEAK_ALIAS(seed48_r, libc_seed48_r);
DEFINE_PUBLIC_WEAK_ALIAS(lcong48_r, libc_lcong48_r);
DEFINE_PUBLIC_WEAK_ALIAS(random_r, libc_random_r);
DEFINE_PUBLIC_WEAK_ALIAS(srandom_r, libc_srandom_r);
DEFINE_PUBLIC_WEAK_ALIAS(initstate_r, libc_initstate_r);
DEFINE_PUBLIC_WEAK_ALIAS(setstate_r, libc_setstate_r);
DEFINE_PUBLIC_WEAK_ALIAS(on_exit, libc_on_exit);
DEFINE_PUBLIC_WEAK_ALIAS(clearenv, libc_clearenv);
DEFINE_PUBLIC_WEAK_ALIAS(mkstemps, libc_mkstemps);
DEFINE_PUBLIC_WEAK_ALIAS(rpmatch, libc_rpmatch);
DEFINE_PUBLIC_WEAK_ALIAS(mkstemps64, libc_mkstemps64);
DEFINE_PUBLIC_WEAK_ALIAS(rand_r, libc_rand_r);
DEFINE_PUBLIC_WEAK_ALIAS(getloadavg, libc_getloadavg);
DEFINE_PUBLIC_WEAK_ALIAS(drand48, libc_drand48);
DEFINE_PUBLIC_WEAK_ALIAS(lrand48, libc_lrand48);
DEFINE_PUBLIC_WEAK_ALIAS(mrand48, libc_mrand48);
DEFINE_PUBLIC_WEAK_ALIAS(erand48, libc_erand48);
DEFINE_PUBLIC_WEAK_ALIAS(nrand48, libc_nrand48);
DEFINE_PUBLIC_WEAK_ALIAS(jrand48, libc_jrand48);
DEFINE_PUBLIC_WEAK_ALIAS(srand48, libc_srand48);
DEFINE_PUBLIC_WEAK_ALIAS(seed48, libc_seed48);
DEFINE_PUBLIC_WEAK_ALIAS(lcong48, libc_lcong48);
DEFINE_PUBLIC_WEAK_ALIAS(putenv, libc_putenv);
DEFINE_PUBLIC_WEAK_ALIAS(_putenv, libc_putenv);
DEFINE_PUBLIC_WEAK_ALIAS(random, libc_random);
DEFINE_PUBLIC_WEAK_ALIAS(srandom, libc_srandom);
DEFINE_PUBLIC_WEAK_ALIAS(initstate, libc_initstate);
DEFINE_PUBLIC_WEAK_ALIAS(setstate, libc_setstate);
DEFINE_PUBLIC_WEAK_ALIAS(l64a, libc_l64a);
DEFINE_PUBLIC_WEAK_ALIAS(a64l, libc_a64l);
DEFINE_PUBLIC_WEAK_ALIAS(realpath, libc_realpath);
DEFINE_PUBLIC_WEAK_ALIAS(frealpath, libc_frealpath);
DEFINE_PUBLIC_WEAK_ALIAS(frealpath4, libc_frealpath4);
DEFINE_PUBLIC_WEAK_ALIAS(frealpathat, libc_frealpathat);
DEFINE_PUBLIC_WEAK_ALIAS(setenv, libc_setenv);
DEFINE_PUBLIC_WEAK_ALIAS(unsetenv, libc_unsetenv);
DEFINE_PUBLIC_WEAK_ALIAS(mktemp, libc_mktemp);
DEFINE_PUBLIC_WEAK_ALIAS(__mktemp, libc_mktemp);
DEFINE_PUBLIC_WEAK_ALIAS(mkstemp, libc_mkstemp);
DEFINE_PUBLIC_WEAK_ALIAS(mkdtemp, libc_mkdtemp);
DEFINE_PUBLIC_WEAK_ALIAS(setkey, libc_setkey);
DEFINE_PUBLIC_WEAK_ALIAS(grantpt, libc_grantpt);
DEFINE_PUBLIC_WEAK_ALIAS(unlockpt, libc_unlockpt);
DEFINE_PUBLIC_WEAK_ALIAS(ptsname, libc_ptsname);
DEFINE_PUBLIC_WEAK_ALIAS(posix_openpt, libc_posix_openpt);
DEFINE_PUBLIC_WEAK_ALIAS(secure_getenv, libc_secure_getenv);
DEFINE_PUBLIC_WEAK_ALIAS(__secure_getenv, libc_secure_getenv);
DEFINE_PUBLIC_WEAK_ALIAS(ptsname_r, libc_ptsname_r);
DEFINE_PUBLIC_WEAK_ALIAS(getpt, libc_getpt);
DEFINE_PUBLIC_WEAK_ALIAS(canonicalize_file_name, libc_canonicalize_file_name);
DEFINE_PUBLIC_WEAK_ALIAS(mkostemp, libc_mkostemp);
DEFINE_PUBLIC_WEAK_ALIAS(mkostemps, libc_mkostemps);
DEFINE_PUBLIC_WEAK_ALIAS(mkostemp64, libc_mkostemp64);
DEFINE_PUBLIC_WEAK_ALIAS(mkostemps64, libc_mkostemps64);
DEFINE_PUBLIC_WEAK_ALIAS(__doserrno, libc___doserrno);
DEFINE_PUBLIC_WEAK_ALIAS(_get_doserrno, libc__get_doserrno);
DEFINE_PUBLIC_WEAK_ALIAS(_set_doserrno, libc__set_doserrno);
DEFINE_PUBLIC_WEAK_ALIAS(__p___argc, libc___p___argc);
DEFINE_PUBLIC_WEAK_ALIAS(__p___argv, libc___p___argv);
DEFINE_PUBLIC_WEAK_ALIAS(__p__pgmptr, libc___p__pgmptr);
DEFINE_PUBLIC_WEAK_ALIAS(__p___wargv, libc___p___wargv);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$__p___wargv, libd___p___wargv);
DEFINE_PUBLIC_WEAK_ALIAS(__p__wenviron, libc___p__wenviron);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$__p__wenviron, libd___p__wenviron);
DEFINE_PUBLIC_WEAK_ALIAS(__p__wpgmptr, libc___p__wpgmptr);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$__p__wpgmptr, libd___p__wpgmptr);
DEFINE_PUBLIC_WEAK_ALIAS(__p___initenv, libc___p___initenv);
DEFINE_PUBLIC_WEAK_ALIAS(__p___winitenv, libc___p___winitenv);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$__p___winitenv, libd___p___winitenv);
DEFINE_PUBLIC_WEAK_ALIAS(getenv_s, libc_getenv_s);
DEFINE_PUBLIC_WEAK_ALIAS(_dupenv_s, libc__dupenv_s);
DEFINE_PUBLIC_WEAK_ALIAS(rand_s, libc_rand_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$rand_s, libd_rand_s);
DEFINE_PUBLIC_WEAK_ALIAS(_recalloc, libc__recalloc);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_malloc, libc__aligned_malloc);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_offset_malloc, libc__aligned_offset_malloc);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_realloc, libc__aligned_realloc);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_recalloc, libc__aligned_recalloc);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_offset_realloc, libc__aligned_offset_realloc);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_offset_recalloc, libc__aligned_offset_recalloc);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_free, libc__aligned_free);
DEFINE_PUBLIC_WEAK_ALIAS(_fullpath, libc__fullpath);
DEFINE_PUBLIC_WEAK_ALIAS(_putenv_s, libc__putenv_s);
DEFINE_PUBLIC_WEAK_ALIAS(_searchenv, libc__searchenv);
DEFINE_PUBLIC_WEAK_ALIAS(_searchenv_s, libc__searchenv_s);
DEFINE_PUBLIC_WEAK_ALIAS(_seterrormode, libc__seterrormode);
DEFINE_PUBLIC_WEAK_ALIAS(_set_error_mode, libc__set_error_mode);
DEFINE_PUBLIC_WEAK_ALIAS(_beep, libc__beep);
DEFINE_PUBLIC_WEAK_ALIAS(_wperror, libc__wperror);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wperror, libd__wperror);
DEFINE_PUBLIC_WEAK_ALIAS(onexit, libc_onexit);
DEFINE_PUBLIC_WEAK_ALIAS(_onexit, libc_onexit);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STDLIB_C */
