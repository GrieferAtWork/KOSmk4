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
#ifdef __INTELLISENSE__
#include "tls.c"
#endif

DECL_BEGIN

/* Return a pointer to the base of the given module's
 * TLS segment, as seen form the calling thread.
 * In the case of dynamic TLS, allocate missing segments lazily,
 * logging a system error and exiting the calling application if
 * doing so fails. */
#ifdef FAIL_ON_ERROR
INTERN WUNUSED ATTR_RETNONNULL void *ATTR_FASTCALL
libdl_dltlsbase(DlModule *__restrict self)
#else /* FAIL_ON_ERROR */
INTERN WUNUSED void *LIBCCALL
libdl_dltlsaddr(DlModule *__restrict self)
#endif /* !FAIL_ON_ERROR */
{
	byte_t *result;
	struct dtls_extension *extab;
	result = (byte_t *)RD_TLS_BASE_REGISTER();
	if (self->dm_tlsstoff || unlikely(!self->dm_tlsmsize))
		return result + self->dm_tlsstoff;
	/* FIXME: This isn't re-entrant! - What if a signal handler accesses a TLS variable from
	 *        from a dynamically loaded library, while the calling thread was interrupted
	 *        within the following atomic lock? (In other words: This lock needs to allow
	 *        for recursion within the same thread) */
	atomic_rwlock_read(&((struct tls_segment *)result)->ts_exlock);
	extab = dtls_extension_tree_locate(((struct tls_segment *)result)->ts_extree, (uintptr_t)self);
	atomic_rwlock_endread(&((struct tls_segment *)result)->ts_exlock);
	if (extab)
		return extab->te_data;
	/* Lazily allocate missing extension tables.
	 * But first: Lazily allocate the TLS template initialize for this module. */
	if (!self->dm_tlsinit && self->dm_tlsfsize) {
		byte_t *init, *new_init;
		fd_t fd;
		init = (byte_t *)malloc(self->dm_tlsfsize);
		if unlikely(!init)
			goto err_nomem;
		fd = DlModule_GetFd(self);
		if unlikely(fd < 0)
			goto err;
		if (preadall(fd, init, self->dm_tlsfsize, self->dm_tlsoff) <= 0) {
#if ELF_POINTER_SIZE >= 8
			elf_setdlerrorf("Failed to read %Iu bytes of TLS template data from %I64u",
			                self->dm_tlsfsize, (uint64_t)self->dm_tlsoff);
#else /* ELF_POINTER_SIZE >= 8 */
			elf_setdlerrorf("Failed to read %Iu bytes of TLS template data from %I32u",
			                self->dm_tlsfsize, (uint32_t)self->dm_tlsoff);
#endif /* ELF_POINTER_SIZE < 8 */
			goto err;
		}
		new_init = (byte_t *)ATOMIC_CMPXCH_VAL(self->dm_tlsinit,
		                                       NULL,
		                                       init);
		if unlikely(new_init != NULL)
			free(init);
	}
	/* Allocate the actual extension table. */
	{
		uintptr_t data_offset;
		data_offset = sizeof(struct dtls_extension);
		data_offset += self->dm_tlsalign - 1;
		data_offset &= ~(self->dm_tlsalign - 1);
		extab = (struct dtls_extension *)memalign(self->dm_tlsalign,
		                                          data_offset + self->dm_tlsmsize);
		if unlikely(!extab)
			goto err_nomem;
		extab->te_tree.a_vaddr = (uintptr_t)self;
		/* Initialize the data contents of this extended TLS table. */
		memset(mempcpy(extab->te_data = (byte_t *)extab + data_offset,
		               self->dm_tlsinit,
		               self->dm_tlsfsize),
		       0, /* .bss */
		       self->dm_tlsmsize - self->dm_tlsfsize);
		/* Invoke TLS initializers. */
		if (self->dm_tls_init) {
			TRY {
				(*self->dm_tls_init)(self->dm_tls_arg, extab->te_data);
			} EXCEPT {
				free(extab);
				RETHROW();
			}
		}
	}
	atomic_rwlock_write(&((struct tls_segment *)result)->ts_exlock);
	{
		struct dtls_extension *newtab;
		newtab = dtls_extension_tree_locate(((struct tls_segment *)result)->ts_extree,
		                                    (uintptr_t)self);
		if unlikely(newtab != NULL) {
			/* Some other thread already allocated the TLS segment for us
			 * XXX: Can this even happen? (I don't think it can, considering
			 *      we're using lazy allocations) */
			atomic_rwlock_endwrite(&((struct tls_segment *)result)->ts_exlock);
			/* Invoke TLS finalizers. */
			if (self->dm_tls_fini) {
				TRY {
					(*self->dm_tls_fini)(self->dm_tls_arg, extab->te_data);
				} EXCEPT {
					free(extab);
					RETHROW();
				}
			}
			free(extab);
			return newtab->te_data;
		}
	}
	dtls_extension_tree_insert(&((struct tls_segment *)result)->ts_extree, extab);
	atomic_rwlock_endwrite(&((struct tls_segment *)result)->ts_exlock);
	return extab->te_data;
err_nomem:
	elf_setdlerror_nomem();
err:
#ifdef FAIL_ON_ERROR
	syslog(LOG_ERR, "[rtld] Failed to allocate TLS segment for %q: %s\n",
	       self->dm_filename, elf_dlerror_message);
	sys_exit_group(EXIT_FAILURE);
#else /* FAIL_ON_ERROR */
	return NULL;
#endif /* !FAIL_ON_ERROR */
}

#undef FAIL_ON_ERROR

DECL_END
