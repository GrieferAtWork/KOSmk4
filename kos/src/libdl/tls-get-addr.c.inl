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
#ifdef __INTELLISENSE__
#include "tls.c"
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#ifdef FAIL_ON_ERROR
/* Return a pointer to the base of the given module's
 * TLS  segment,  as  seen form  the  calling thread.
 * In the case of dynamic TLS, allocate missing segments lazily,
 * logging a system error and exiting the calling application if
 * doing so fails. */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) void *FCALL
libdl_dltlsbase(DlModule *__restrict self) THROWS(...)
#else /* FAIL_ON_ERROR */
/* Return the calling thread's base address of the TLS segment associated with `tls_handle'
 * NOTE: TLS  Segments are allocated and initialized lazily, meaning that the initializer
 *       passed to `dltlsalloc(3D)' will be called by this function upon the first use of
 *       that  segment within  each individual thread,  also causing the  finalizer to be
 *       enqueued for invocation when the calling thread exits.
 * WARNING: The order in which TLS finalizers are invoked is entirely UNDEFINED!
 * NOTE: the given  `tls_handle' may  also be  a module  handle, as  returned by  `dlopen(3D)',
 *       in which case this function  returns a pointer to the  TLS segment of that module  for
 *       the calling thread (e.g.: Such a pointer is needed by `unwind_emulator_t::sm_tlsbase')
 * @return: * :   Pointer to the base of the TLS segment associated with `tls_handle' within the calling thread.
 * @return: NULL: Invalid `tls_handle', or allocation/initialization failed. (s.a. `dlerror()') */
INTERN WUNUSED void *__DLFCN_DLTLSADDR2_CC
libdl_dltlsaddr2(NCX DlModule *self, NCX struct dltls_segment *seg) THROWS(E_SEGFAULT, ...)
#endif /* !FAIL_ON_ERROR */
{
#ifdef FAIL_ON_ERROR
	struct dltls_segment *seg;
#endif /* FAIL_ON_ERROR */
	struct dltls_extension *extab;
#ifndef FAIL_ON_ERROR
	if unlikely(!DL_VERIFY_MODULE_HANDLE(self))
		goto err_badmodule;
	if unlikely(!DL_VERIFY_TLS_SEGMENT(seg))
		goto err_badseg;
#else /* !FAIL_ON_ERROR */
	RD_TLS_BASE_REGISTER(*(void **)&seg);
#endif /* FAIL_ON_ERROR */

	/* Simple case: Static TLS, and special case: Empty TLS */
	if (self->dm_tlsstoff || unlikely(!self->dm_tlsmsize))
		return (byte_t *)seg + self->dm_tlsstoff;

	/* Complicated case: search the TLS extension table (used for those modules
	 * not part of the initial set of loaded libraries, but which were  instead
	 * loaded by a call to `dlopen(3D)') */
	dltls_segment_ex_read(seg);
	extab = dtls_extension_tree_locate(seg->ts_extree, self);
	dltls_segment_ex_endread(seg);
	if (extab)
		return extab->te_data;

	/* Lazily allocate missing extension tables.
	 * But first: Lazily allocate the TLS template initialize for this module. */
	if (!self->dm_tlsinit && self->dm_tlsfsize) {
		byte_t *init, *new_init;
		fd_t fd;
		ssize_t error;
		init = (byte_t *)malloc(self->dm_tlsfsize);
		if unlikely(!init)
			goto err_nomem;
		fd = DlModule_GetFd(self);
		if unlikely(fd < 0)
			goto err_init;
		error = preadall(fd, init, self->dm_tlsfsize, self->dm_tlsoff);
		if (E_ISERR(error)) {
			char error_fallback_buf[DL_STRERRORNAME_FALLBACK_LEN];
			dl_seterrorf("Failed to read %" PRIuSIZ " bytes of TLS template "
			             "data from %" PRIuN(__SIZEOF_ELFW(OFF__)) ": %s",
			             self->dm_tlsfsize, self->dm_tlsoff,
			             dl_strerrorname_np_s((errno_t)-error, error_fallback_buf));
err_init:
			free(init);
			goto err;
		}
		new_init = (byte_t *)atomic_cmpxch_val(&self->dm_tlsinit, NULL, init);
		if unlikely(new_init != NULL)
			free(init);
	}

	/* Allocate the actual extension table. */
	{
		uintptr_t data_offset;
		data_offset = sizeof(struct dltls_extension);
		data_offset += self->dm_tlsalign - 1;
		data_offset &= ~(self->dm_tlsalign - 1);
		extab = (struct dltls_extension *)memalign(self->dm_tlsalign,
		                                          data_offset + self->dm_tlsmsize);
		if unlikely(!extab)
			goto err_nomem;
		extab->te_module = self;

		/* Initialize the data contents of this extended TLS table. */
		bzero(mempcpy(extab->te_data = (byte_t *)extab + data_offset,
		              self->dm_tlsinit, self->dm_tlsfsize),
		      self->dm_tlsmsize - self->dm_tlsfsize); /* .bss */

		/* Invoke TLS initializers. */
		if (self->dm_tls_init) {
			TRY {
				(*self->dm_tls_init)(self->dm_tls_arg, extab->te_data, seg);
			} EXCEPT {
				free(extab);
				RETHROW();
			}
		}
	}

	/* XXX: This isn't re-entrant! - What if a signal handler accesses a TLS variable from
	 *      from  a dynamically loaded  library, while the  calling thread was interrupted
	 *      within the following atomic  lock? (In other words:  This lock needs to  allow
	 *      for recursion within the same thread)
	 * ->:  What about the fact that we're also using malloc() here? malloc() most definitely
	 *      isn't (and probably couldn't)  be re-entrant in the  general case... What do  the
	 *      specs say about  a signal  handler being the  first to  access some  thread-local
	 *      variable? */
	dltls_segment_ex_write(seg);
	{
		struct dltls_extension *newtab;
		newtab = dtls_extension_tree_locate(seg->ts_extree, self);
		if unlikely(newtab != NULL) {
			/* Some other thread already allocated the TLS segment for us
			 * XXX: Can this even happen? (I don't think it can, considering
			 *      we're using lazy allocations) */
			dltls_segment_ex_endwrite(seg);

			/* Invoke TLS finalizers. */
			RAII_FINALLY { free(extab); };
			if (self->dm_tls_fini)
				(*self->dm_tls_fini)(self->dm_tls_arg, extab->te_data, seg);
			return newtab->te_data;
		}
	}
	dtls_extension_tree_insert(&seg->ts_extree, extab);
	dltls_segment_ex_endwrite(seg);
	return extab->te_data;
err_nomem:
	dl_seterror_nomem();
err:
#ifdef FAIL_ON_ERROR
	syslog(LOG_ERR, "[rtld] Failed to allocate TLS segment for %q: %s\n",
	       self->dm_filename, dl_globals.dg_errmsg);
	sys_exit_group(EXIT_FAILURE);
#else /* FAIL_ON_ERROR */
	return NULL;
err_badmodule:
	dl_seterror_badmodule(self);
	goto err;
err_badseg:
	dl_seterror_badptr(seg);
	goto err;
#endif /* !FAIL_ON_ERROR */
}

#undef FAIL_ON_ERROR

DECL_END
