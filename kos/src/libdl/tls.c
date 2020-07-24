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
#ifndef GUARD_LIBDL_TLS_C
#define GUARD_LIBDL_TLS_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "dl.h"
/**/

#include <hybrid/minmax.h>
#include <hybrid/sequence/atree.h>
#include <hybrid/sequence/list.h>

#include <kos/syscalls.h>

#include <malloc.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

DECL_BEGIN

struct dtls_extension {
	/* Tree for mapping TLS extensions data tables to modules.
		* NOTE: These extension tables are allocated lazily! */
	ATREE_NODE_SINGLE(struct dtls_extension, uintptr_t) te_tree; /* [lock(:ts_exlock)] NOTE: KEY == DlModule */
	byte_t                                             *te_data; /* Pointer to the base of TLS data. */
	/* The actual extension data goes here. */
};

DECL_END

#define ATREE(x)      dtls_extension_tree_##x
#define ATREE_NOTHROW /* nothing */
#define Tkey          uintptr_t
#define T             struct dtls_extension
#define N_NODEPATH    te_tree
#define ATREE_SINGLE  1
#include <hybrid/sequence/atree-abi.h>

DECL_BEGIN

/* This is the actual structure that the TLS register (e.g. `%fs.base' / `%gs.base') points to. */
struct tls_segment {
	/* Static TLS data goes here (aka. at negative offsets from `ts_self') */
	struct tls_segment               *ts_self;    /* [1..1][const][== self] Self-pointer
	                                               * At offset 0; mandaged by ELF, and a good idea in general. */
	LLIST_NODE(struct tls_segment)    ts_threads; /* [lock(:static_tls_lock)] Thread entry within `static_tls_list' */
	struct atomic_rwlock              ts_exlock;  /* Lock for `ts_extree' */
	ATREE_HEAD(struct dtls_extension) ts_extree;  /* [0..1][lock(ts_exlock)] TLS extension table. */
};

STATIC_ASSERT_MSG(offsetof(struct tls_segment, ts_self) == 0,
                  "The self-pointer being at offset=0 is ABI mandated");

/* List of all allocated static-tls segments (usually 1 for each thread) */
PRIVATE struct atomic_rwlock static_tls_lock = ATOMIC_RWLOCK_INIT;
PRIVATE LLIST(struct tls_segment) static_tls_list = LLIST_INIT;

/* Minimum alignment of the static TLS segment. */
PRIVATE size_t static_tls_align = COMPILER_ALIGNOF(struct tls_segment);

/* Total size of the static TLS segment (including the `struct tls_segment' descriptor)
 * NOTE: The segment base itself is then located at `p + static_tls_size - sizeof(struct tls_segment)' */
PRIVATE size_t static_tls_size = sizeof(struct tls_segment);
PRIVATE size_t static_tls_size_no_segment = 0;

/* Initializer for the first `static_tls_size_no_segment' bytes of the static TLS segment. */
PRIVATE void const *static_tls_init = NULL;



INTERN NONNULL((1)) void CC
DlModule_RemoveTLSExtension(DlModule *__restrict self) {
	struct tls_segment *iter;
	struct dtls_extension *chain, *next;
	chain = NULL;
again:
	atomic_rwlock_read(&static_tls_lock);
	LLIST_FOREACH(iter, static_tls_list, ts_threads) {
		if (!atomic_rwlock_trywrite(&iter->ts_exlock)) {
			atomic_rwlock_endread(&static_tls_lock);
			sys_sched_yield();
			goto again;
		}
		next = dtls_extension_tree_remove(&iter->ts_extree, (uintptr_t)self);
		atomic_rwlock_endwrite(&iter->ts_exlock);
		if (next) {
			next->te_tree.a_min = chain;
			chain               = next;
		}
	}
	atomic_rwlock_endread(&static_tls_lock);
	/* Free all instances of extension data for this module. */
	while (chain) {
		next = chain->te_tree.a_min;
		free(chain);
		chain = next;
	}
}


/* Initialize the static TLS bindings table from the set of currently loaded modules. */
INTERN WUNUSED int CC
DlModule_InitStaticTLSBindings(void) {
	DlModule *iter;
	ptrdiff_t endptr = 0;
	/* Assign static TLS offsets to all currently loaded modules.
	 * NOTE: Since we've yet to invoke a user-defined code (other than IFUNC selectors),
	 *       we are allowed to assume that no threads other than the calling (main) thread
	 *       are currently running, meaning we don't have to do any sort of lock for this! */
	DlModule_AllList_FOREACH(iter) {
		if (!iter->dm_tlsmsize)
			continue;
		if (static_tls_align < iter->dm_tlsalign)
			static_tls_align = iter->dm_tlsalign;
		endptr -= iter->dm_tlsmsize;
		endptr &= ~(iter->dm_tlsalign - 1);
		iter->dm_tlsstoff = endptr;
	}
	static_tls_size_no_segment = (size_t)-endptr;
	static_tls_init = malloc(static_tls_size_no_segment);
	if unlikely(!static_tls_init)
		goto err_nomem;
	/* Load static TLS template data */
	DlModule_AllList_FOREACH(iter) {
		byte_t *dst;
		if (!iter->dm_tlsmsize)
			continue;
		dst = (byte_t *)static_tls_init +
		      static_tls_size_no_segment +
		      iter->dm_tlsstoff;
		if (iter->dm_tlsfsize) {
			fd_t fd = DlModule_GetFd(iter);
			if unlikely(fd < 0)
				goto err;
			if (preadall(fd, dst, iter->dm_tlsfsize, iter->dm_tlsoff) <= 0) {
				__STATIC_IF(sizeof(ElfW(Off)) >= 8) {
					dl_seterrorf("%q: Failed to read %Iu bytes of TLS template data from %I64u",
					             iter->dm_filename,
					             iter->dm_tlsfsize,
					             (uint64_t)iter->dm_tlsoff);
				} __STATIC_ELSE(sizeof(ElfW(Off)) >= 8) {
					dl_seterrorf("%q: Failed to read %Iu bytes of TLS template data from %I32u",
					             iter->dm_filename,
					             iter->dm_tlsfsize,
					             (uint32_t)iter->dm_tlsoff);
				}
				goto err;
			}
		}
		/* ZERO-initialize trailing TLS BSS bytes. */
		memset(dst + iter->dm_tlsfsize, 0,
		       iter->dm_tlsmsize -
		       iter->dm_tlsfsize);
	}
	static_tls_size = static_tls_size_no_segment;
	static_tls_size += sizeof(struct tls_segment);
	return 0;
err_nomem:
	dl_seterror_nomem();
err:
	return -1;
}

PRIVATE NONNULL((1)) void CC
try_incref_extension_table_modules(struct dtls_extension *__restrict self) {
again:
	if (!DlModule_TryIncref((DlModule *)self->te_tree.a_vaddr))
		self->te_tree.a_vaddr = 0;
	if (self->te_tree.a_min) {
		if (self->te_tree.a_max)
			try_incref_extension_table_modules(self->te_tree.a_max);
		self = self->te_tree.a_min;
		goto again;
	}
	if (self->te_tree.a_max) {
		self = self->te_tree.a_max;
		goto again;
	}
}

PRIVATE NONNULL((1)) void CC
decref_tls_extension_modules(struct dtls_extension *__restrict self) {
	struct dtls_extension *minptr, *maxptr;
again:
	if (self->te_tree.a_vaddr)
		DlModule_Decref((DlModule *)self->te_tree.a_vaddr);
	minptr = self->te_tree.a_min;
	maxptr = self->te_tree.a_max;
	free(self);
	if (minptr) {
		if (maxptr)
			decref_tls_extension_modules(maxptr);
		self = minptr;
		goto again;
	}
	if (maxptr) {
		self = maxptr;
		goto again;
	}
}

PRIVATE NONNULL((1)) void CC
fini_tls_extension_tables(struct dtls_extension *__restrict self) {
	struct dtls_extension *minptr, *maxptr;
again:
	if (self->te_tree.a_vaddr) {
		DlModule *mod;
		void (*callback)(void *arg, void *base);
		mod = (DlModule *)self->te_tree.a_vaddr;
		callback = mod->dm_tls_fini;
		if (callback) {
			TRY {
				(*callback)(mod->dm_tls_arg,
				            self->te_data);
			} EXCEPT {
				decref_tls_extension_modules(self);
				RETHROW();
			}
		}
		DlModule_Decref(mod);
	}
	minptr = self->te_tree.a_min;
	maxptr = self->te_tree.a_max;
	free(self);
	if (minptr) {
		if (maxptr)
			fini_tls_extension_tables(maxptr);
		self = minptr;
		goto again;
	}
	if (maxptr) {
		self = maxptr;
		goto again;
	}
}

/* Run finalizers for all TLS segments allocated within the calling thread. */
INTERN void CC DlModule_RunAllTlsFinalizers(void) {
	struct tls_segment *self;
	struct dtls_extension *ext_free;
	self = (struct tls_segment *)RD_TLS_BASE_REGISTER();
	if unlikely(!self)
		return;
	atomic_rwlock_write(&self->ts_exlock);
	ext_free = self->ts_extree;
	if (ext_free) {
		try_incref_extension_table_modules(ext_free);
		atomic_rwlock_endwrite(&self->ts_exlock);
		/* Free the extension tables, and invoke finalizers. */
		fini_tls_extension_tables(ext_free);
	} else {
		atomic_rwlock_endwrite(&self->ts_exlock);
	}
}


/* Allocate/Free a static TLS segment
 * These functions are called by by libc in order to safely create a new thread, such that
 * all current and future modules are able to store thread-local storage within that thread.
 * NOTE: The caller is responsible to store the returned segment to the appropriate TLS register.
 * @return: * :   Pointer to the newly allocated TLS segment.
 * @return: NULL: Error (s.a. dlerror()) */
INTERN WUNUSED ATTR_MALLOC void *LIBCCALL
libdl_dltlsallocseg(void) {
	struct tls_segment *result;
	result = (struct tls_segment *)memalign(static_tls_align,
	                                        static_tls_size);
	if unlikely(!result)
		goto err_nomem;
	memcpy(result, static_tls_init, static_tls_size_no_segment);
	result = (struct tls_segment *)((byte_t *)result +
	                                static_tls_size_no_segment);
	result->ts_self = result;
	atomic_rwlock_init(&result->ts_exlock);
	result->ts_extree = NULL;
	atomic_rwlock_write(&static_tls_lock);
	LLIST_INSERT(static_tls_list, result, ts_threads);
	atomic_rwlock_endwrite(&static_tls_lock);
	return result;
err_nomem:
	dl_seterror_nomem();
	return NULL;
}

PRIVATE NONNULL((1)) void CC
delete_extension_tables(struct dtls_extension *__restrict self) {
	struct dtls_extension *minptr, *maxptr;
again:
	if (self->te_tree.a_vaddr) {
		DlModule *mod;
		void (*callback)(void *arg, void *base);
		mod = (DlModule *)self->te_tree.a_vaddr;
		callback = mod->dm_tls_fini;
		if (callback) {
			TRY {
				(*callback)(mod->dm_tls_arg, self->te_data);
			} EXCEPT {
				decref_tls_extension_modules(self);
				RETHROW();
			}
		}
		DlModule_Decref(mod);
	}
	minptr = self->te_tree.a_min;
	maxptr = self->te_tree.a_max;
	free(self);
	if (minptr) {
		if (maxptr)
			delete_extension_tables(maxptr);
		self = minptr;
		goto again;
	}
	if (maxptr) {
		self = maxptr;
		goto again;
	}
}

LOCAL NONNULL((1)) void CC
clear_extension_table(struct tls_segment *__restrict self) {
	struct dtls_extension *ext_free;
	atomic_rwlock_write(&self->ts_exlock);
	ext_free = self->ts_extree;
	if (ext_free) {
		self->ts_extree = NULL;
		try_incref_extension_table_modules(ext_free);
		atomic_rwlock_endwrite(&self->ts_exlock);
		/* Free the extension tables, and invoke finalizers. */
		delete_extension_tables(ext_free);
	} else {
		atomic_rwlock_endwrite(&self->ts_exlock);
	}
}

/* Free a previously allocated static TLS segment (usually called by `pthread_exit()' and friends). */
INTERN NONNULL((1)) int LIBCCALL
libdl_dltlsfreeseg(void *ptr) {
	struct tls_segment *seg;
	if unlikely(!ptr)
		goto err_badptr;
	seg = (struct tls_segment *)ptr;
	atomic_rwlock_write(&static_tls_lock);
	LLIST_REMOVE(seg, ts_threads);
	atomic_rwlock_endwrite(&static_tls_lock);
	clear_extension_table(seg);
	free((byte_t *)ptr - static_tls_size_no_segment);
	return 0;
err_badptr:
	return dl_seterror_badptr(ptr);
}


#define SIZEOF_DL_MODULE_FOR_TLS \
	MAX(offsetafter(DlModule, dm_refcnt),   \
	MAX(offsetafter(DlModule, dm_tls_arg),  \
	MAX(offsetafter(DlModule, dm_tls_fini), \
	MAX(offsetafter(DlModule, dm_tls_init), \
	MAX(offsetafter(DlModule, dm_tlsstoff), \
	MAX(offsetafter(DlModule, dm_tlsalign), \
	MAX(offsetafter(DlModule, dm_tlsmsize), \
	MAX(offsetafter(DlModule, dm_tlsfsize), \
	MAX(offsetafter(DlModule, dm_tlsinit),  \
	    offsetafter(DlModule, dm_tlsoff))))))))))

#define OFFSETOF_DL_MODULE_FOR_TLS \
	MIN(offsetof(DlModule, dm_refcnt),   \
	MIN(offsetof(DlModule, dm_tls_arg),  \
	MIN(offsetof(DlModule, dm_tls_fini), \
	MIN(offsetof(DlModule, dm_tls_init), \
	MIN(offsetof(DlModule, dm_tlsstoff), \
	MIN(offsetof(DlModule, dm_tlsalign), \
	MIN(offsetof(DlModule, dm_tlsmsize), \
	MIN(offsetof(DlModule, dm_tlsfsize), \
	MIN(offsetof(DlModule, dm_tlsinit),  \
	    offsetof(DlModule, dm_tlsoff))))))))))



/* DL-based TLS memory management API.
 * These functions may be used to dynamically allocate TLS memory that works everywhere where
 * ATTR_THREAD-based TLS memory also works. - However using these functions, TLS memory can
 * be allocated dynamically at runtime (behaving the same as a call to dlopen() loading a
 * module containing a TLS segment would).
 * @param: NUM_BYTES:      The size of the TLS segment (in bytes)
 * @param: MIN_ALIGNMENT:  The minimum alignment requirements for the TLS segment base address.
 * @param: TEMPLATE_DATA:  Base address of an initialization template.
 *                         The first `TEMPLATE_SIZE' bytes of any per-thread data segment
 *                         that gets allocated will be initialized to the contents of these
 *                         values before `PERTHREAD_INIT' is optionally invoked in order to
 *                         perform additional initialization.
 * @param: TEMPLATE_SIZE:  The size of `TEMPLATE_DATA' in bytes, indicating the number of
 *                         leading bytes within the TLS segment that should be pre-defined
 *                         to mirror the contents of `TEMPLATE_DATA' at the time of a call
 *                         to this function (`TEMPLATE_DATA' need not remain valid or
 *                         accessible after this function returns)
 *                         Any memory after `TEMPLATE_SIZE', but before `NUM_BYTES' is initialized
 *                         to all ZEROes, however `TEMPLATE_SIZE' must not be greater than
 *                        `NUM_BYTES', and if it is, this function returns `NULL' and sets
 *                        `dlerror()' accordingly.
 * @param: PERTHREAD_INIT: An optional callback that will be invoked on a per-thread basis
 *                         in order to perform additional initialization of the associated
 *                         TLS segment within the associated thread.
 *                         This function will be called upon first access of the segment
 *                         within the thread using the data (s.a. `dltlsaddr()')
 *                         @param: ARG:  The value of `PERTHREAD_CALLBACK_ARG' passed to `dltlsalloc'
 *                         @param: BASE: The base address of the associated segment within the calling
 *                                       thread (same as the return value of `dltlsaddr()')
 * @param: PERTHREAD_FINI: An optional callback that behaves similar to `PERTHREAD_INIT',
 *                         but called by `pthread_exit()' or any other thread finalizer
 *                        (more specifically: by `dltlsfreeseg()') within any thread that
 *                         has been seen using the associated segment, and causing it to
 *                         be allocated and initialized for that thread.
 * @param: PERTHREAD_CALLBACK_ARG: A user-specified argument passed to the init/fini callbacks.
 * @return: * :            An opaque handle for the newly created TLS segment.
 *                         This handle may be used in future calls to `dltlsaddr()', and can be
 *                         destroyed (causing all threads that had previously allocated the
 *                         segment to delete it and optionally invoke finalizer callbacks) by
 *                         passing it to `dltlsfree()'
 * @return: NULL:          Failed to allocate the TLS segment (s.a. `dlerror()') */
INTERN WUNUSED DlModule *LIBCCALL
libdl_dltlsalloc(size_t num_bytes, size_t min_alignment,
                 void const *template_data, size_t template_size,
                 void (LIBCCALL *perthread_init)(void *arg, void *base),
                 void (LIBCCALL *perthread_fini)(void *arg, void *base),
                 void *perthread_callback_arg) {
	DlModule *result;
	if unlikely(template_size > num_bytes) {
		dl_seterrorf("TLS template size (%Iu) is greater than TLS memory size (%Iu)",
		             template_size, num_bytes);
		goto err;
	}
	if unlikely(min_alignment & (min_alignment - 1)) {
		dl_seterrorf("TLS alignment %Iu isn't a power-of-2",
		             min_alignment);
		goto err;
	}
	result = (DlModule *)malloc(SIZEOF_DL_MODULE_FOR_TLS);
	if unlikely(!result)
		goto err_nomem;
#ifndef NDEBUG
	/* Invalidate all of the `struct link_map' emulation garbage. */
	memset(result, 0xcc, OFFSETOF_DL_MODULE_FOR_TLS);
#endif /* !NDEBUG */
	result->dm_tlsoff   = 0;
	result->dm_tlsinit  = NULL;
	result->dm_tlsfsize = template_size;
	result->dm_tlsmsize = num_bytes;
	result->dm_tlsalign = min_alignment;
	result->dm_tlsstoff = 0;
	result->dm_tls_init = perthread_init;
	result->dm_tls_fini = perthread_fini;
	result->dm_tls_arg  = perthread_callback_arg;
	result->dm_refcnt   = 1;
	/* Copy TLS template data. */
	if (template_size) {
		result->dm_tlsinit = (byte_t *)malloc(template_size);
		if unlikely(!result->dm_tlsinit)
			goto err_nomem_r;
		memcpy((byte_t *)result->dm_tlsinit,
		       template_data,
		       template_size);
	}
	/* No need for any sort of registration.
	 * -> All of that is done lazily on a per-thread basis! */
	return result;
err_nomem_r:
	free(result);
err_nomem:
	dl_seterror_nomem();
err:
	return NULL;
}



/* Free a TLS segment previously allocated with `dltlsalloc()' */
INTERN WUNUSED NONNULL((1)) int LIBCCALL
libdl_dltlsfree(DlModule *self) {
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_nullmodule;
	DlModule_RemoveTLSExtension(self);
	/* Wait for other threads to complete finalization (which may happen
	 * if they began to do so, just before this function got called)
	 * s.a. `libdl_dltlsfreeseg()' doing a DlModule_TryIncref() to prevent
	 *       modules from unloading while TLS finalizers contained within
	 *       get invoked. */
	while unlikely(ATOMIC_READ(self->dm_refcnt) != 1)
		sys_sched_yield();
	free((byte_t *)self->dm_tlsinit);
	free(self);
	return 0;
err_nullmodule:
	return dl_seterror_badmodule(self);
}

DEFINE_PUBLIC_ALIAS(dltlsallocseg, libdl_dltlsallocseg);
DEFINE_PUBLIC_ALIAS(dltlsfreeseg, libdl_dltlsfreeseg);
DEFINE_PUBLIC_ALIAS(dltlsalloc, libdl_dltlsalloc);
DEFINE_PUBLIC_ALIAS(dltlsfree, libdl_dltlsfree);
DEFINE_PUBLIC_ALIAS(dltlsaddr, libdl_dltlsaddr);


/* Similar to `libdl_dltlsaddr()', but do no lazy allocation
 * and return NULL if the module doesn't have a TLS segment. */
INTERN WUNUSED NONNULL((1)) void *CC
DlModule_TryGetTLSAddr(DlModule *__restrict self) {
	byte_t *result;
	struct tls_segment *tls;
	struct dtls_extension *extab;
	if unlikely(!self->dm_tlsmsize)
		return NULL; /* No TLS segment. */
	tls = (struct tls_segment *)RD_TLS_BASE_REGISTER();
	/* Simple case: Static TLS */
	if (self->dm_tlsstoff)
		return (byte_t *)tls + self->dm_tlsstoff;
	atomic_rwlock_read(&tls->ts_exlock);
	extab  = dtls_extension_tree_locate(tls->ts_extree, (uintptr_t)self);
	result = extab ? extab->te_data : NULL;
	atomic_rwlock_endread(&tls->ts_exlock);
	return result;
}


DECL_END


#ifndef __INTELLISENSE__
#include "tls-get-addr.c.inl"
#define FAIL_ON_ERROR 1
#include "tls-get-addr.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBDL_TLS_C */
