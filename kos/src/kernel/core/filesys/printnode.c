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
#ifndef GUARD_KERNEL_CORE_FILESYS_PRINTNODE_C
#define GUARD_KERNEL_CORE_FILESYS_PRINTNODE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/printnode.h>
#include <kernel/iovec.h>
#include <kernel/mman/phys-access.h>
#include <kernel/mman/phys.h>

#include <kos/io.h>
#include <sys/stat.h>

#include <assert.h>
#include <format-printer.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN


/* Default operators for `struct fdirnode_ops' */
PUBLIC NONNULL((1)) void KCALL /* Writes `0' into `st_size' and `st_blocks' */
printnode_v_stat(struct mfile *__restrict UNUSED(self),
                 USER CHECKED struct stat *result)
		THROWS(...) {
	result->st_size   = 0;
	result->st_blocks = 0;
}


struct vprinter_data {
	USER CHECKED byte_t *vpd_buf; /* [?..?] Destination buffer. */
	size_t               vpd_siz; /* Remaining buffer space. */
	size_t               vpd_pos; /* # of leading bytes to skip. */
};

PRIVATE NONNULL((1)) ssize_t FORMATPRINTER_CC
vprinter_cb(void *arg, char const *__restrict data, size_t datalen) {
	struct vprinter_data *me = (struct vprinter_data *)arg;
	if (me->vpd_pos != 0) {
		if (me->vpd_pos >= datalen) {
			/* Unused leading chunk. */
			me->vpd_pos -= datalen;
			return 0;
		}
		data += me->vpd_pos;
		datalen -= me->vpd_pos;
		me->vpd_pos = 0;
	}
	if (me->vpd_siz <= datalen) {
		/* Last chunk. */
		memcpy(me->vpd_buf, data, me->vpd_siz);
		me->vpd_siz = 0;
		return -1; /* Stop printing. */
	}
	/* Normal chunk. */
	memcpy(me->vpd_buf, data, datalen);
	me->vpd_buf += datalen;
	me->vpd_siz -= datalen;
	return 0;
}


PUBLIC WUNUSED NONNULL((1)) size_t KCALL /* Populates `dst' via `pno_print' */
printnode_v_pread(struct mfile *__restrict self, USER CHECKED void *dst,
                  size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	struct vprinter_data data;
	struct printnode_ops const *ops;
	struct printnode *me;
#if __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__
	size_t io_max;
	if unlikely(addr > (pos_t)SIZE_MAX)
		return 0;
	io_max = ((size_t)SIZE_MAX - addr) + 1;
	if unlikely(num_bytes > io_max)
		num_bytes = io_max;
#endif /* __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__ */
	me  = mfile_asprintnode(self);
	ops = printnode_getops(me);

	/* Fill in printer data. */
	data.vpd_buf = (USER CHECKED byte_t *)dst;
	data.vpd_siz = num_bytes;
	data.vpd_pos = (size_t)addr;

	/* Invoke the printer. */
	(*ops->pno_print)(me, &vprinter_cb, &data, (size_t)addr);

	/* Return the number of written bytes (== input_size - unused_size) */
	return num_bytes - data.vpd_siz;
}



struct vvprinter_data {
	struct iov_buffer const  *vvpd_buf; /* [1..1][const] IOV buffer */
	struct iov_entry          vvpd_ent; /* Current IOV entry. */
	size_t                    vvpd_nxt; /* Index of next `vvpd_ent' to load from `vvpd_buf' */
	size_t                    vvpd_siz; /* Remaining buffer space. */
	size_t                    vvpd_pos; /* # of leading bytes to skip. */
};

PRIVATE NONNULL((1)) void FCALL
vvprinter_putdata(struct vvprinter_data *__restrict self,
                  char const *__restrict data, size_t datalen) {
again:
	if (self->vvpd_ent.ive_size >= datalen) {
		/* Singular IOV target. */
		memcpy(self->vvpd_ent.ive_base, data, datalen);
		self->vvpd_ent.ive_base += datalen;
		self->vvpd_ent.ive_size -= datalen;
		return;
	}

	/* Fill unused part of previous buffer. */
	memcpy(self->vvpd_ent.ive_base, data, self->vvpd_ent.ive_size);
	data += self->vvpd_ent.ive_size;
	datalen -= self->vvpd_ent.ive_size;

	/* Load next buffer. */
	{
		struct iov_buffer const *buf;
		buf = self->vvpd_buf;
		assertf(self->vvpd_nxt < buf->iv_entc,
		        "This would mean that the `num_bytes' originally given "
		        "alongside the buffer were larger than `iov_buffer_size()'");
		self->vvpd_ent = buf->iv_entv[self->vvpd_nxt];
		++self->vvpd_nxt;
		if (self->vvpd_nxt == buf->iv_entc)
			self->vvpd_ent.ive_size = buf->iv_last;
	}

	/* Keep on truckin' with the next buffer. */
	goto again;
}

PRIVATE NONNULL((1)) ssize_t FORMATPRINTER_CC
vvprinter_cb(void *arg, char const *__restrict data, size_t datalen) {
	struct vvprinter_data *me = (struct vvprinter_data *)arg;
	if (me->vvpd_pos != 0) {
		if (me->vvpd_pos >= datalen) {
			/* Unused leading chunk. */
			me->vvpd_pos -= datalen;
			return 0;
		}
		data += me->vvpd_pos;
		datalen -= me->vvpd_pos;
		me->vvpd_pos = 0;
	}
	if (me->vvpd_siz <= datalen) {
		/* Last chunk. */
		if likely(me->vvpd_siz != 0)
			vvprinter_putdata(me, data, me->vvpd_siz);
		me->vvpd_siz = 0;
		return -1; /* Stop printing. */
	}

	/* Normal chunk. */
	vvprinter_putdata(me, data, datalen);
	me->vvpd_siz -= datalen;
	return 0;
}

PUBLIC WUNUSED NONNULL((1, 2)) size_t KCALL
printnode_v_preadv(struct mfile *__restrict self, struct iov_buffer *__restrict dst,
                   size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	struct vvprinter_data data;
	struct printnode_ops const *ops;
	struct printnode *me;
#if __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__
	size_t io_max;
	if unlikely(addr > (pos_t)SIZE_MAX)
		return 0;
	io_max = ((size_t)SIZE_MAX - addr) + 1;
	if unlikely(num_bytes > io_max)
		num_bytes = io_max;
#endif /* __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__ */
	me  = mfile_asprintnode(self);
	ops = printnode_getops(me);

	/* Fill in printer data. */
	data.vvpd_buf = dst;
	data.vvpd_ent = dst->iv_head;
	data.vvpd_nxt = 1;
	data.vvpd_siz = num_bytes;
	data.vvpd_pos = (size_t)addr;

	/* Invoke the printer. */
	(*ops->pno_print)(me, &vvprinter_cb, &data, (size_t)addr);

	/* Return the number of written bytes (== input_size - unused_size) */
	return num_bytes - data.vvpd_siz;
}




PUBLIC_CONST struct mfile_stream_ops const printnode_v_stream_ops = {
	.mso_pread  = &printnode_v_pread,
	.mso_preadv = &printnode_v_preadv,
	.mso_stat   = &printnode_v_stat,
};



struct pprinter_data {
	physaddr_t ppd_buf; /* Physical destination buffer address. */
	size_t     ppd_siz; /* Remaining buffer space. */
	size_t     ppd_pos; /* # of leading bytes to skip. */
};

PRIVATE NONNULL((1)) ssize_t FORMATPRINTER_CC
pprinter_cb(void *arg, char const *__restrict data, size_t datalen) {
	struct pprinter_data *me = (struct pprinter_data *)arg;
	if (me->ppd_pos != 0) {
		if (me->ppd_pos >= datalen) {
			/* Unused leading chunk. */
			me->ppd_pos -= datalen;
			return 0;
		}
		data += me->ppd_pos;
		datalen -= me->ppd_pos;
		me->ppd_pos = 0;
	}
	if (me->ppd_siz <= datalen) {
		/* Last chunk. */
		copytophys(me->ppd_buf, data, me->ppd_siz);
		me->ppd_siz = 0;
		return -1; /* Stop printing. */
	}
	/* Normal chunk. */
	copytophys(me->ppd_buf, data, datalen);
	me->ppd_buf += datalen;
	me->ppd_siz -= datalen;
	return 0;
}


PUBLIC NONNULL((1, 5)) void KCALL /* Populates `buf' via `pno_print' */
printnode_v_loadblocks(struct mfile *__restrict self, pos_t addr,
                       physaddr_t buf, size_t num_bytes,
                       struct aio_multihandle *__restrict UNUSED(aio)) {
	struct pprinter_data data;
	struct printnode_ops const *ops;
	struct printnode *me;
#if __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__
	size_t io_max;
	if unlikely(addr > (pos_t)SIZE_MAX) {
		bzerophyscc(buf, num_bytes);
		return;
	}
	io_max = ((size_t)SIZE_MAX - addr) + 1;
	if unlikely(num_bytes > io_max) {
		bzerophyscc(buf + io_max, num_bytes - io_max);
		num_bytes = io_max;
	}
#endif /* __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__ */
	me  = mfile_asprintnode(self);
	ops = printnode_getops(me);

	/* Fill in printer data. */
	data.ppd_buf = buf;
	data.ppd_siz = num_bytes;
	data.ppd_pos = (size_t)addr;

	/* Invoke the printer. */
	(*ops->pno_print)(me, &pprinter_cb, &data, (size_t)addr);

	/* Fill any unused bytes with all zeroes. */
	bzerophyscc(data.ppd_buf, data.ppd_siz);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_PRINTNODE_C */
