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
#include "access.c"
#define DEFINE_IO_READ 1
//#define DEFINE_IO_WRITE 1
#endif /* __INTELLISENSE__ */

#ifdef __KERNEL__
#include <kernel/mman/phys-access.h>

DECL_BEGIN

#if (defined(DEFINE_IO_READ) + defined(DEFINE_IO_WRITE)) != 1
#error "Must #define DEFINE_IO_READ or DEFINE_IO_WRITE before #include-ing  this file"
#endif /* (DEFINE_IO_READ + DEFINE_IO_WRITE) != 1 */


#ifdef DEFINE_IO_READ
INTERN NONNULL((1)) void CC
libvio_copyfromvio_to_phys(struct vioargs *__restrict args,
                           vio_addr_t offset, physaddr_t buf,
                           size_t num_bytes)
#elif defined(DEFINE_IO_WRITE)
INTERN NONNULL((1)) void CC
libvio_copytovio_from_phys(struct vioargs *__restrict args,
                           vio_addr_t offset, physaddr_t buf,
                           size_t num_bytes)
#endif /* ... */
		__THROWS(...) {
	PHYS_VARS;
	byte_t *vbuf;
#ifdef DEFINE_IO_READ
	IF_PHYS_IDENTITY(buf, num_bytes, {
		libvio_copyfromvio(args, offset,
		                   PHYS_TO_IDENTITY(buf),
		                   num_bytes);
		return;
	});
#elif defined(DEFINE_IO_WRITE)
	IF_PHYS_IDENTITY(buf, num_bytes, {
		libvio_copytovio(args, offset,
		                 PHYS_TO_IDENTITY(buf),
		                 num_bytes);
		return;
	});
#endif /* ... */
	if unlikely(!num_bytes)
		return;
	vbuf = phys_pushaddr(buf);

	/* FINALLY is required, because VIO access may throw exceptions. */
	RAII_FINALLY { phys_pop(); };
	for (;;) {
		size_t page_bytes;
		page_bytes = PAGESIZE - ((uintptr_t)vbuf & PAGEMASK);
		if (page_bytes > num_bytes)
			page_bytes = num_bytes;
		/* Copy memory. */
#ifdef DEFINE_IO_READ
		libvio_copyfromvio(args, offset, vbuf, page_bytes);
#elif defined(DEFINE_IO_WRITE)
		libvio_copytovio(args, offset, vbuf, page_bytes);
#endif /* ... */
		if (page_bytes >= num_bytes)
			break;
		num_bytes -= page_bytes;
		buf += page_bytes;
		offset += page_bytes;
		vbuf = phys_loadpage(buf);
	}
}


#undef DEFINE_IO_WRITE
#undef DEFINE_IO_READ


DECL_END
#endif /* __KERNEL__ */
