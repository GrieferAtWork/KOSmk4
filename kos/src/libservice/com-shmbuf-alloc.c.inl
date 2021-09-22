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
#ifdef __INTELLISENSE__
#include "com.c"
//#define DEFINE_libservice_shmbuf_alloc_nopr
#define DEFINE_libservice_shmbuf_alloc_nopr_nx
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_libservice_shmbuf_alloc_nopr) + defined(DEFINE_libservice_shmbuf_alloc_nopr_nx)) != 1
#error "Must #define exactly one of `DEFINE_libservice_shmbuf_alloc_nopr', `DEFINE_libservice_shmbuf_alloc_nopr_nx'"
#endif /* ... */

DECL_BEGIN

/* Allocate SHM memory.
 * @param: num_bytes_with_extra: Lower bound for number of bytes to allocate, plus extra space:
 * >> num_bytes_with_extra = MAX(SERVICE_SHM_ALLOC_MINSIZE,
 * >>                            CEIL_ALIGN(num_bytes, SERVICE_SHM_ALLOC_ALIGN) +
 * >>                            SERVICE_SHM_ALLOC_EXTRA); */
#ifdef DEFINE_libservice_shmbuf_alloc_nopr_nx
INTERN NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) service_buf_t
NOTHROW(FCALL libservice_shmbuf_alloc_nopr_nx)(struct service *__restrict self,
                                               size_t num_bytes_with_extra)
#else /* DEFINE_libservice_shmbuf_alloc_nopr_nx */
INTERN NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) service_buf_t FCALL
libservice_shmbuf_alloc_nopr(struct service *__restrict self,
                             size_t num_bytes_with_extra)
		THROWS(E_BADALLOC)
#endif /* !DEFINE_libservice_shmbuf_alloc_nopr_nx */
{
	/* TODO */
	(void)self;
	(void)num_bytes_with_extra;
	abort();
}

DECL_END

#undef DEFINE_libservice_shmbuf_alloc_nopr_nx
#undef DEFINE_libservice_shmbuf_alloc_nopr
