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
#ifndef GUARD_LIBDL_TLS_C
#define GUARD_LIBDL_TLS_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "dl.h"
/**/

#include <hybrid/minmax.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>

#include <kos/syscalls.h>

#include <inttypes.h>
#include <malloc.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

#include <libdl/tls.h>

#define RBTREE_LEFT_LEANING /* Use left-leaning trees */
#define RBTREE_NOTHROW      NOTHROW
#define RBTREE(name)        dtls_extension_tree_##name
#define RBTREE_T            struct dltls_extension
#define RBTREE_Tkey         DlModule *
#define RBTREE_NODEFIELD    te_tree
#define RBTREE_GETKEY       dtls_extension_getmodule
#define RBTREE_REDFIELD     te_redblack
#define RBTREE_REDBIT       DTLS_EXTENSION_REDBIT
#define RBTREE_KEY_LO(a, b) ((uintptr_t)(a) < (uintptr_t)(b))
#define RBTREE_KEY_EQ(a, b) ((uintptr_t)(a) == (uintptr_t)(b))
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

STATIC_ASSERT_MSG(offsetof(struct dltls_segment, ts_self) == 0,
                  "The self-pointer being at offset=0 is ABI mandated");

/* Minimum alignment of the static TLS segment. */
PRIVATE size_t tls_segment_align = COMPILER_ALIGNOF(struct dltls_segment);

/* Total size of the static TLS segment (including the `struct dltls_segment' descriptor)
 * NOTE: The segment base itself is then located at `p + tls_segment_size - sizeof(struct dltls_segment)' */
PRIVATE size_t tls_segment_size = sizeof(struct dltls_segment);
PRIVATE size_t tls_segment_size_no_segment = 0;

/* Initializer for the first `tls_segment_size_no_segment' bytes of the static TLS segment. */
PRIVATE void const *tls_segment_init = NULL;



INTERN NONNULL((1)) void
NOTHROW(CC DlModule_RemoveTLSExtension)(DlModule *__restrict self) {
	struct dltls_segment *iter;
	struct dltls_extension *chain, *next;
	chain = NULL;
again:
	dlglobals_tls_segment_read(&dl_globals);
	LIST_FOREACH (iter, &dl_globals.dg_tls_segment_list, ts_threads) {
		if (!dltls_segment_ex_trywrite(iter)) {
#ifndef __OPTIMIZE_SIZE__
			/* Try to get read-lock and check if this TLS segment even uses `self'
			 * If not, then we can simply skip it without ever having to acquire a
			 * write-lock! */
			if (!dltls_segment_ex_tryread(iter)) {
				next = dtls_extension_tree_locate(iter->ts_extree, self);
				dltls_segment_ex_endread(iter);
				if (!next)
					continue; /* Unused */
			}
#endif /* !__OPTIMIZE_SIZE__ */
			dlglobals_tls_segment_endread(&dl_globals);
			sys_sched_yield();
			goto again;
		}
		next = dtls_extension_tree_remove(&iter->ts_extree, self);
		dltls_segment_ex_endwrite(iter);
		if (next) {
			next->te_tree.rb_lhs = chain;
			chain                = next;
		}
	}
	dlglobals_tls_segment_endread(&dl_globals);

	/* Free all instances of extension data for this module. */
	while (chain) {
		next = chain->te_tree.rb_lhs;
		free(chain);
		chain = next;
	}
}


/* Initialize the static TLS bindings table from the set of currently loaded modules. */
INTERN WUNUSED int
NOTHROW_RPC(CC DlModule_InitStaticTLSBindings)(void) {
	DlModule *iter;
	ptrdiff_t endptr = 0;

	/* Assign static TLS offsets to all currently loaded modules.
	 * NOTE: Since we've yet to invoke a  user-defined code (other than IFUNC  selectors),
	 *       we are allowed to assume that no threads other than the calling (main) thread
	 *       are currently running, meaning we don't have to do any sort of lock for this! */
	DLIST_FOREACH (iter, &dl_globals.dg_alllist, dm_modules) {
		if (!iter->dm_tlsmsize)
			continue;
		if (iter->dm_ops)
			continue;
		if (tls_segment_align < iter->dm_tlsalign)
			tls_segment_align = iter->dm_tlsalign;
		endptr -= iter->dm_tlsmsize;
		endptr &= ~(iter->dm_tlsalign - 1);
		iter->dm_tlsstoff = endptr;
	}
	tls_segment_size_no_segment = (size_t)-endptr;
	tls_segment_init = malloc(tls_segment_size_no_segment);
	if unlikely(!tls_segment_init)
		goto err_nomem;

	/* Load static TLS template data */
	DLIST_FOREACH (iter, &dl_globals.dg_alllist, dm_modules) {
		byte_t *dst;
		if (!iter->dm_tlsmsize)
			continue;
		if (iter->dm_ops)
			continue;
		dst = (byte_t *)tls_segment_init +
		      tls_segment_size_no_segment +
		      iter->dm_tlsstoff;
		if (iter->dm_tlsfsize) {
			fd_t fd = DlModule_GetFd(iter);
			if unlikely(fd < 0)
				goto err;
			if (preadall(fd, dst, iter->dm_tlsfsize, iter->dm_tlsoff) <= 0) {
				dl_seterrorf("%q: Failed to read %" PRIuSIZ " bytes of TLS "
				             "template data from %" PRIuN(__SIZEOF_ELFW(OFF__)),
				             iter->dm_filename, iter->dm_tlsfsize, iter->dm_tlsoff);
				goto err;
			}
		}
		/* ZERO-initialize trailing TLS BSS bytes. */
		bzero(dst + iter->dm_tlsfsize,
		      iter->dm_tlsmsize -
		      iter->dm_tlsfsize);
	}
	tls_segment_size = tls_segment_size_no_segment;
	tls_segment_size += sizeof(struct dltls_segment);
	return 0;
err_nomem:
	dl_seterror_nomem();
err:
	return -1;
}

PRIVATE NONNULL((1)) void
NOTHROW(CC try_incref_extension_table_modules)(struct dltls_extension *__restrict self) {
	DlModule *mod;
again:
	mod = dtls_extension_getmodule(self);
	if (mod && !tryincref(mod))
		self->te_redblack &= 1;
	if (self->te_tree.rb_lhs) {
		if (self->te_tree.rb_rhs)
			try_incref_extension_table_modules(self->te_tree.rb_rhs);
		self = self->te_tree.rb_lhs;
		goto again;
	}
	if (self->te_tree.rb_rhs) {
		self = self->te_tree.rb_rhs;
		goto again;
	}
}

PRIVATE NONNULL((1)) void CC
decref_tls_extension_modules(struct dltls_extension *__restrict self)
		THROWS(...) {
	DlModule *mod;
	struct dltls_extension *minptr, *maxptr;
again:
	mod = dtls_extension_getmodule(self);
	if (mod)
		decref(mod);
	minptr = self->te_tree.rb_lhs;
	maxptr = self->te_tree.rb_rhs;
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

PRIVATE NONNULL((1, 2)) void CC
fini_tls_extension_tables(struct dltls_extension *__restrict self,
                          struct dltls_segment *__restrict segment)
		THROWS(...) {
	DlModule *mod;
	struct dltls_extension *minptr, *maxptr;
again:
	mod = dtls_extension_getmodule(self);
	if (mod != NULL) {
		void (*callback)(void *arg, void *tls_segment, void *base);
		callback = mod->dm_tls_fini;
		if (callback) {
			TRY {
				(*callback)(mod->dm_tls_arg, self->te_data, segment);
			} EXCEPT {
				decref_tls_extension_modules(self);
				RETHROW();
			}
		}
		decref(mod);
	}
	minptr = self->te_tree.rb_lhs;
	maxptr = self->te_tree.rb_rhs;
	free(self);
	if (minptr) {
		if (maxptr)
			fini_tls_extension_tables(maxptr, segment);
		self = minptr;
		goto again;
	}
	if (maxptr) {
		self = maxptr;
		goto again;
	}
}

/* Run finalizers for all TLS segments allocated within the calling thread. */
INTERN void CC DlModule_RunAllTlsFinalizers(void) THROWS(...) {
	struct dltls_segment *self;
	struct dltls_extension *ext_free;
	RD_TLS_BASE_REGISTER(*(void **)&self);
	if unlikely(!self)
		return;
	dltls_segment_ex_write(self);
	ext_free = self->ts_extree;
	if (ext_free) {
		try_incref_extension_table_modules(ext_free);
		dltls_segment_ex_endwrite(self);
		/* Free the extension tables, and invoke finalizers. */
		fini_tls_extension_tables(ext_free, self);
	} else {
		dltls_segment_ex_endwrite(self);
	}
}


/* Allocate/Free a static TLS segment
 * These functions are called by by libc in  order to safely create a new thread, such  that
 * all current and future modules are able to store thread-local storage within that thread.
 * NOTE: The caller is responsible to store the returned segment to the appropriate TLS register.
 * @return: * :   Pointer to the newly allocated TLS segment.
 * @return: NULL: Error (s.a. dlerror()) */
INTERN ATTR_MALLOC WUNUSED struct dltls_segment *
NOTHROW(DLFCN_CC libdl_dltlsallocseg)(void) {
	struct dltls_segment *result;
	result = (struct dltls_segment *)memalign(tls_segment_align,
	                                          tls_segment_size);
	if unlikely(!result)
		goto err_nomem;
	result = (struct dltls_segment *)mempcpy(result, tls_segment_init,
	                                         tls_segment_size_no_segment);
	result->ts_self = result;
	atomic_rwlock_init(&result->ts_exlock);
	result->ts_extree = NULL;
	dlglobals_tls_segment_write(&dl_globals);
	LIST_INSERT_HEAD(&dl_globals.dg_tls_segment_list, result, ts_threads);
	dlglobals_tls_segment_endwrite(&dl_globals);
	return result;
err_nomem:
	dl_seterror_nomem();
	return NULL;
}

PRIVATE NONNULL((1, 2)) void CC
delete_extension_tables(struct dltls_extension *__restrict self,
                        struct dltls_segment *__restrict segment)
		THROWS(...) {
	DlModule *mod;
	struct dltls_extension *minptr, *maxptr;
again:
	mod = dtls_extension_getmodule(self);
	if (mod != NULL) {
		void (*callback)(void *arg, void *base, void *tls_segment);
		callback = mod->dm_tls_fini;
		if (callback) {
			TRY {
				(*callback)(mod->dm_tls_arg, self->te_data, segment);
			} EXCEPT {
				decref_tls_extension_modules(self);
				RETHROW();
			}
		}
		decref(mod);
	}
	minptr = self->te_tree.rb_lhs;
	maxptr = self->te_tree.rb_rhs;
	free(self);
	if (minptr) {
		if (maxptr)
			delete_extension_tables(maxptr, segment);
		self = minptr;
		goto again;
	}
	if (maxptr) {
		self = maxptr;
		goto again;
	}
}

LOCAL NONNULL((1)) void CC
clear_extension_table(struct dltls_segment *__restrict self)
		THROWS(...) {
	struct dltls_extension *ext_free;
	dltls_segment_ex_write(self);
	ext_free = self->ts_extree;
	if (ext_free) {
		self->ts_extree = NULL;
		try_incref_extension_table_modules(ext_free);
		dltls_segment_ex_endwrite(self);
		/* Free the extension tables, and invoke finalizers. */
		delete_extension_tables(ext_free, self);
	} else {
		dltls_segment_ex_endwrite(self);
	}
}

/* Free a previously allocated static TLS segment (usually called by `pthread_exit()' and friends). */
INTERN NONNULL((1)) int DLFCN_CC
libdl_dltlsfreeseg(USER struct dltls_segment *seg)
		THROWS(E_SEGFAULT, ...) {
	if unlikely(!DL_VERIFY_TLS_SEGMENT(seg))
		goto err_badptr;
	dlglobals_tls_segment_write(&dl_globals);
	LIST_REMOVE(seg, ts_threads);
	dlglobals_tls_segment_endwrite(&dl_globals);
	clear_extension_table(seg);
	free((byte_t *)seg - tls_segment_size_no_segment);
	return 0;
err_badptr:
	return dl_seterror_badptr(seg);
}


#define SIZEOF_DL_MODULE_FOR_TLS                \
	MAX_C(offsetafter(DlModule, dm_refcnt),     \
	      offsetafter(DlModule, dm_weakrefcnt), \
	      offsetafter(DlModule, dm_tls_arg),    \
	      offsetafter(DlModule, dm_tls_fini),   \
	      offsetafter(DlModule, dm_tls_init),   \
	      offsetafter(DlModule, dm_tlsstoff),   \
	      offsetafter(DlModule, dm_tlsalign),   \
	      offsetafter(DlModule, dm_tlsmsize),   \
	      offsetafter(DlModule, dm_tlsfsize),   \
	      offsetafter(DlModule, dm_tlsinit),    \
	      offsetafter(DlModule, dm_tlsoff))

#define OFFSETOF_DL_MODULE_FOR_TLS           \
	MIN_C(offsetof(DlModule, dm_refcnt),     \
	      offsetof(DlModule, dm_weakrefcnt), \
	      offsetof(DlModule, dm_tls_arg),    \
	      offsetof(DlModule, dm_tls_fini),   \
	      offsetof(DlModule, dm_tls_init),   \
	      offsetof(DlModule, dm_tlsstoff),   \
	      offsetof(DlModule, dm_tlsalign),   \
	      offsetof(DlModule, dm_tlsmsize),   \
	      offsetof(DlModule, dm_tlsfsize),   \
	      offsetof(DlModule, dm_tlsinit),    \
	      offsetof(DlModule, dm_tlsoff))


/* DL-based TLS memory management API.
 * These functions may be used to dynamically allocate TLS memory that works everywhere where
 * ATTR_THREAD-based TLS memory also works. - However, using these functions, TLS memory  can
 * be  allocated dynamically at runtime (behaving the same  as a call to `dlopen()' loading a
 * module containing a TLS segment would).
 * @param: num_bytes:      The size of the TLS segment (in bytes)
 * @param: min_alignment:  The minimum alignment requirements for the TLS segment base address.
 * @param: template_data:  Base address of an initialization template.
 *                         The first `template_size' bytes  of any per-thread data  segment
 *                         that gets allocated will be initialized to the contents of these
 *                         values before `perthread_init' is optionally invoked in order to
 *                         perform additional initialization.
 *                         This template is copied by this function and does not need to keep
 *                         pointing at a valid memory location after `dltlsalloc()'  returns!
 * @param: template_size:  The size of `template_data' in bytes, indicating the number  of
 *                         leading bytes within the TLS segment that should be pre-defined
 *                         to mirror the contents of `template_data' at the time of a call
 *                         to this function (`template_data' itself need not remain  valid
 *                         or accessible after this function returns)
 *                         Any memory after `template_size', but before `num_bytes' is
 *                         initialized to all ZEROes, however `template_size' must not
 *                         be greater than  `num_bytes', and if  it is, this  function
 *                         returns `NULL' and sets `dlerror()' accordingly.
 * @param: perthread_init: An optional callback that will be invoked on a per-thread basis
 *                         in order to perform additional initialization of the associated
 *                         TLS segment within the associated thread.
 *                         This function will be called upon first access of the segment
 *                         within   the  thread  using  the  data  (s.a.  `dltlsaddr()')
 *                         @param: arg:  The value of `perthread_callback_arg' passed to `dltlsalloc'
 *                         @param: base: The base  address of  the  associated segment  within  the
 *                                       calling thread (same as the return value of `dltlsaddr()')
 *                         @param: tls_segment: The TLS segment to which `base' belongs (usually  that
 *                                              of the calling thread, unless `dltlsaddr2()' was used)
 * @param: perthread_fini: An  optional callback that behaves similar to `perthread_init',
 *                         but called by  `pthread_exit()' or any  other thread  finalizer
 *                         (more specifically: by `dltlsfreeseg()') within any thread that
 *                         has been seen using the  associated segment, and causing it  to
 *                         be allocated and initialized for that thread.
 *                         Note that the actual thread calling this function may not necessarily
 *                         be the same thread that originally called `perthread_init', only that
 *                         any  call to `perthread_init' will always be followed by another call
 *                         to this function at some later point in time!
 * @param: perthread_callback_arg: A user-specified argument passed to the init/fini callbacks.
 * @return: * :            An opaque handle for the newly created TLS segment.
 *                         This handle may be used in future calls to `dltlsaddr()', and can be
 *                         destroyed (causing  all threads  that had  previously allocated  the
 *                         segment to delete it and  optionally invoke finalizer callbacks)  by
 *                         passing it to `dltlsfree()'
 * @return: NULL:          Failed to allocate the TLS segment (s.a. `dlerror()') */
INTERN WUNUSED DlModule *
NOTHROW(DLFCN_CC libdl_dltlsalloc)(size_t num_bytes, size_t min_alignment,
                                   USER void const *template_data, size_t template_size,
                                   void (DLFCN_CC USER *perthread_init)(void *arg, void *base, void *tls_segment),
                                   void (DLFCN_CC USER *perthread_fini)(void *arg, void *base, void *tls_segment),
                                   USER void *perthread_callback_arg) {
	DlModule *result;
	if unlikely(template_size > num_bytes) {
		dl_seterrorf("TLS template size (%" PRIuSIZ ") is greater than TLS memory size (%" PRIuSIZ ")",
		             template_size, num_bytes);
		goto err;
	}
	if unlikely(min_alignment & (min_alignment - 1)) {
		dl_seterrorf("TLS alignment %" PRIuSIZ " isn't a power-of-2",
		             min_alignment);
		goto err;
	}
	result = (DlModule *)malloc(SIZEOF_DL_MODULE_FOR_TLS);
	if unlikely(!result)
		goto err_nomem;

	/* Invalidate all of the `struct link_map' emulation garbage. */
	DBG_memset(result, 0xcc, OFFSETOF_DL_MODULE_FOR_TLS);
	result->dm_tlsoff     = 0;
	result->dm_tlsinit    = NULL;
	result->dm_tlsfsize   = template_size;
	result->dm_tlsmsize   = num_bytes;
	result->dm_tlsalign   = min_alignment;
	result->dm_tlsstoff   = 0;
	result->dm_tls_init   = perthread_init;
	result->dm_tls_fini   = perthread_fini;
	result->dm_tls_arg    = perthread_callback_arg;
	result->dm_refcnt     = 1;
	result->dm_weakrefcnt = 1;

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
INTERN int
NOTHROW_NCX(DLFCN_CC libdl_dltlsfree)(USER DlModule *self)
		THROWS(E_SEGFAULT) {
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_nullmodule;
	DlModule_RemoveTLSExtension(self);

	/* Wait for other threads to complete finalization (which may happen
	 * if  they began  to do so,  just before this  function got called)
	 * s.a. `libdl_dltlsfreeseg()' doing a tryincref() to prevent
	 *       modules from unloading while TLS finalizers contained within
	 *       get invoked. */
	while unlikely(ATOMIC_READ(self->dm_refcnt) != 1)
		sys_sched_yield();
	free((byte_t *)self->dm_tlsinit);
	weakdecref_likely(self);
	return 0;
err_nullmodule:
	return dl_seterror_badmodule(self);
}

DEFINE_PUBLIC_ALIAS(dltlsallocseg, libdl_dltlsallocseg);
DEFINE_PUBLIC_ALIAS(dltlsfreeseg, libdl_dltlsfreeseg);
DEFINE_PUBLIC_ALIAS(dltlsalloc, libdl_dltlsalloc);
DEFINE_PUBLIC_ALIAS(dltlsfree, libdl_dltlsfree);
DEFINE_PUBLIC_ALIAS(dltlsaddr, libdl_dltlsaddr);
DEFINE_PUBLIC_ALIAS(dltlsaddr2, libdl_dltlsaddr2);


/* Similar to `libdl_dltlsaddr()', but do no lazy allocation
 * and return NULL if the module doesn't have a TLS segment. */
INTERN WUNUSED NONNULL((1)) void *
NOTHROW_NCX(CC DlModule_TryGetTLSAddr)(USER DlModule *self)
		THROWS(E_SEGFAULT) {
	byte_t *result;
	struct dltls_segment *tls;
	struct dltls_extension *extab;
	if unlikely(!self->dm_tlsmsize)
		return NULL; /* No TLS segment. */
	RD_TLS_BASE_REGISTER(*(void **)&tls);

	/* Simple case: Static TLS */
	if (self->dm_tlsstoff)
		return (byte_t *)tls + self->dm_tlsstoff;
	dltls_segment_ex_read(tls);
	extab  = dtls_extension_tree_locate(tls->ts_extree, self);
	result = extab ? extab->te_data : NULL;
	dltls_segment_ex_endread(tls);
	return result;
}



INTERN WUNUSED void *__DLFCN_DLTLSADDR_CC
libdl_dltlsaddr(USER DlModule *self) THROWS(E_SEGFAULT, ...) {
	void *result;
	struct dltls_segment *seg;
	RD_TLS_BASE_REGISTER(*(void **)&seg);
	result = libdl_dltlsaddr2(self, seg);
	return result;
}


DECL_END


#ifndef __INTELLISENSE__
#include "tls-get-addr.c.inl"
#define FAIL_ON_ERROR 1
#include "tls-get-addr.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBDL_TLS_C */
