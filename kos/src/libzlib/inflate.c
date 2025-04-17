/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBZLIB_INFLATE_C
#define GUARD_LIBZLIB_INFLATE_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/byteorder.h>
#include <hybrid/wordbits.h>

#include <kos/kernel/types.h>
#include <kos/types.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <libzlib/error.h>
#include <libzlib/inflate.h>

#include "inflate.h"

#ifdef __KERNEL__
#include <kernel/malloc.h>
#include <kernel/panic.h>

#include <atomic.h>
#endif /* __KERNEL__ */

/* TODO: Re-write this entire implementation to not operate in a
 *       way to produce 1-byte-at-a-time, but rather chunk-wise:
 * >> error_code_t zlib_read(void *compressed_data, size_t compressed_size,
 * >>                        void *decompressed_data, size_t decompressed_size,
 * >>                        pos_t skipped_bytes);
 *
 * There should also be a way to automatically cache decompresser states at
 * fixed compressed-blob offsets. The final goal of this new implementation
 * is the ability to write a new filesystem driver that allows mounting  of
 * zip files, which itself is based on a mechanism that allows lazy init of
 * memory-mapped compressed streams,  where `mfile_ops::mo_loadblocks'  can
 * be  used to dynamically  load the compressed  data-blob for the accessed
 * file range, and then decompress that blob on-demand.
 *
 * Q: Why?
 * A: Because `/usr/libexec/gcc/i686-kos/12.1.0/cc1'  has a  `.debug_info'
 *    section that is  > 116MiB  large, and while  that's not  compressed,
 *    I would love to be  able to compress it to  save disk space. But  by
 *    doing that, the kernel's debugger would currently need to decompress
 *    that entire section all  at once (which just  fails due to OOM),  as
 *    the current system  is only  able to  decompress an  entire file  at
 *    once, rather than do so chunk-wise.
 *
 * So the goal is for the builtin debugger (as well as libdl.so's equivalent
 * function `dlinflatesection()') to use a kernel function to create  memory
 * mappings of compressed  file data blobs  that can be  used to access  the
 * decompressed memory  on-the-fly in  a way  that allows  `system_cc()'  to
 * do  its usual thing of unloading the  parts you're not looking at, making
 * it possible to map compressed blobs larger than available memory.
 *
 *
 * XXX: Before doing this, implement linux's userfaultfd mechanism. I believe
 *      that it  can be  used to  essentially implement  `mo_loadblocks'  and
 *      `mo_saveblocks' in user-space (though I'm  not entirely sure). If  it
 *      can't be used  for that,  look int  how linux's  FUSE (Filesystem  in
 *      USErspace works), since that one *has* to be able to implement  these
 *      operators in user-space. Finally, if all  else fails, add a new  KOS-
 *      specific file object that *can* be used to do exactly this.
 * XXX: It might be really cool to support FUSE simply because that would mean
 *      KOS could be running unmodified versions of linux FUSE-based  drivers!
 */

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#define ZT_CACHE_BITS         10
#define ZT_CACHE_SIZE         (1 << ZT_CACHE_BITS)
#define ZT_CACHEENT_SIZESHIFT 9
#define ZT_CACHEENT_SYMBMASK  511

/* NOTE: This lookup table idea is derived from miniz */
struct zlib_cache {
	u16 c_lookup[ZT_CACHE_SIZE];
};

#ifdef __KERNEL__
PRIVATE struct zlib_cache static_zlib_cache;
PRIVATE bool static_zlib_cache_inuse = false;

PRIVATE struct zlib_cache *CC zlib_cache_alloc(void) {
	struct zlib_cache *result;
	if (kernel_poisoned()) {
		/* Try not to make use of the heap after being poisoned! */
alloc_static:
		if (atomic_xch(&static_zlib_cache_inuse, true))
			return NULL;
		return &static_zlib_cache;
	}
	result = (struct zlib_cache *)kmalloc_nx(sizeof(struct zlib_cache),
	                                         GFP_PREFLT);
	if (!result)
		goto alloc_static;
	return result;
}
PRIVATE void CC zlib_cache_free(/*nullable*/ struct zlib_cache *self) {
	if (self == &static_zlib_cache) {
		atomic_write(&static_zlib_cache_inuse, false);
	} else {
		kfree(self);
	}
}
#else /* __KERNEL__ */
PRIVATE struct zlib_cache *CC zlib_cache_alloc(void) {
	return (struct zlib_cache *)malloc(sizeof(struct zlib_cache));
}
PRIVATE void CC zlib_cache_free(/*nullable*/ struct zlib_cache *self) {
	free(self);
}
#endif /* !__KERNEL__ */







/* Initialize a ZLIB reader, given an initial data blob. */
INTERN NONNULL((1)) void
NOTHROW_NCX(CC libzlib_reader_init)(struct zlib_reader *__restrict self,
                                    void const *blob, size_t blob_size) {
	DBG_memset(self, 0xcc, sizeof(*self));
	self->zr_inbase      = (byte_t const *)blob;
	self->zr_incur       = (byte_t const *)blob;
	self->zr_inend       = (byte_t const *)blob + blob_size;
	self->zr_state       = 0;
	self->zr_bitcnt      = 0;
	self->zr_offset      = 0;
	self->zr_window      = NULL;
	self->zr_flags       = 0;
	self->zr_bitbuf      = 0;
	self->zr_symbolcache = zlib_cache_alloc();
}

/* Finalize the given zlib reader. */
INTERN NONNULL((1)) void
NOTHROW_NCX(CC libzlib_reader_fini)(struct zlib_reader *__restrict self) {
	zlib_cache_free(self->zr_symbolcache);
	/* ... */
	DBG_memset(self, 0xcc, sizeof(*self));
}


#define SAVE_AND_LOAD (, )

#define _SAVE_IMPL2(save, load) save
#define _SAVE_IMPL(a, b) a b
#define SAVE() _SAVE_IMPL(_SAVE_IMPL2, SAVE_AND_LOAD)

#define _LOAD_IMPL2(save, load) load
#define _LOAD_IMPL(a, b) a b
#define LOAD() _LOAD_IMPL(_LOAD_IMPL2, SAVE_AND_LOAD)


#define ZL_STATE_BEGIN        \
	switch (self->zr_state) { \
	case 0:
#define ZL_STATE_END                            \
	default:                                    \
		result = ZLIB_ERROR_BAD_INTERNAL_STATE; \
		break;                                  \
	}
enum{ _zl_startid = __COUNTER__ };
#define YIELD(val)                                  \
	do {                                            \
		enum { _myid = __COUNTER__ - _zl_startid }; \
		result = (val);                             \
		self->zr_state = _myid;                     \
		SAVE();                                     \
		goto done;                                  \
	case _myid:                                     \
		LOAD();                                     \
	}	__WHILE0

#define YIELD_FOREVER(val)                          \
	do {                                            \
		enum { _myid = __COUNTER__ - _zl_startid }; \
		self->zr_state = _myid;                     \
	case _myid:                                     \
		result = (val);                             \
		goto done;                                  \
	}	__WHILE0

#define GETC(value)                              \
	do {                                         \
		while (self->zr_incur >= self->zr_inend) \
			YIELD(decompressed_bytes);           \
		(value) = *self->zr_incur++;             \
	}	__WHILE0

#define REQUIREBITS(num_bits)                                 \
	do {                                                      \
		while (self->zr_bitcnt < (num_bits)) {                \
			byte_t _byte;                                     \
			assert(self->zr_bitcnt <= 24);                    \
			GETC(_byte);                                      \
			self->zr_bitbuf |= (u32)_byte << self->zr_bitcnt; \
			self->zr_bitcnt += 8;                             \
			assert(self->zr_bitcnt <= 32);                    \
		}                                                     \
	}	__WHILE0

#define PEEKBITS(num_bits) \
	(self->zr_bitbuf & (((u32)1 << (num_bits)) - 1))
#define TAKEBITS(num_bits)           \
	(self->zr_bitbuf >>= (num_bits), \
	 self->zr_bitcnt -= (num_bits))

#define GETBITS(result, num_bits)      \
	do {                               \
		REQUIREBITS(num_bits);         \
		(result) = PEEKBITS(num_bits); \
		TAKEBITS(num_bits);            \
	}	__WHILE0

#define MAX_BITS 15 /* max # of compressed bits for any literal */

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW_NCX(CC zlib_tree_construct_cache)(struct zlib_tree *__restrict tree,
                                          struct zlib_cache *__restrict cache) {
	u16 i;
	bzero(cache->c_lookup, sizeof(cache->c_lookup));
	for (i = 0; i < tree->zr_count; ++i) {
		u16 cacheent, rev_code;
		u8 len = tree->zt_tree[i].te_len;
		if (!len || len > ZT_CACHE_BITS)
			continue;
		rev_code = tree->zt_tree[i].te_code;
		cacheent = ((u16)len << ZT_CACHEENT_SIZESHIFT) | i;
		while (rev_code < ZT_CACHE_SIZE) {
			cache->c_lookup[rev_code] = cacheent;
			rev_code += (1 << len);
		}
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW_NCX(CC zlib_tree_construct)(struct zlib_tree *__restrict tree) {
	u16 i, code, bits, minbits, maxbits;
	u16 next_code[MAX_BITS + 2];
	u16 bl_count[MAX_BITS + 1];
	/* Count the number of codes for each bit-length */
	memsetw(bl_count + 1, 0, MAX_BITS);
	for (i = 0; i < tree->zr_count; ++i) {
		u8 num_bits = tree->zt_tree[i].te_len;
		assert(num_bits <= MAX_BITS);
		++bl_count[num_bits];
	}
	/* Calculate the codes for each symbol (as documented in the DEFLATE specs,
	 * which  can  be  found  here:   https://www.w3.org/Graphics/PNG/RFC-1951)
	 * Note however that minor modifications have been made. */
	code = 0;
	next_code[1] = 0;
	for (bits = 1; bits <= MAX_BITS; ++bits) {
		code = (code + bl_count[bits]) << 1;
		next_code[bits + 1] = code;
	}
	for (i = 0; i < tree->zr_count; ++i) {
		u8 len = tree->zt_tree[i].te_len;
		if (len != 0) {
			u16 rev_code;
			code = next_code[len]++;
			/* Reverse the bit-order of the code, to achieve natural alignment. */
			for (rev_code = 0, bits = 0; bits < len; ++bits, code >>= 1)
				rev_code = (rev_code << 1) | (code & 1);
			tree->zt_tree[i].te_code = rev_code;
		}
	}
	/* Also calculate the shortest and longest compressed bit sequences. */
	for (minbits = 1; minbits <= MAX_BITS; ++minbits) {
		if (bl_count[minbits] != 0)
			break;
	}
	for (maxbits = MAX_BITS; maxbits > minbits; --maxbits) {
		if (bl_count[maxbits] != 0)
			break;
	}
	tree->zr_minlen = minbits;
	tree->zr_maxlen = maxbits;
}


/* Perform a (very) slow find operation  to determine the correct tree  entry
 * for decoding the given compressed code. When NULL is returned, the  caller
 * should  either re-try  the find operation  with more bits  (so-long as the
 * given `compressed_bits' doesn't exceed `tree->zr_maxlen'), or give up once
 * the max number of addressable bits has been reached. (in which case a data
 * error should be reported) */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) struct zlib_treeent *
NOTHROW_NCX(CC zlib_tree_find_slow)(struct zlib_tree *__restrict tree,
                                    u16 compressed_code,
                                    u8 compressed_bits) {
	u16 i;
	assertf(!(compressed_code & ~((1 << compressed_bits) - 1)),
	        "compressed_code must be masked by the caller\n"
	        "compressed_code = %#" PRIx16 "\n"
	        "compressed_bits = %" PRIu8,
	        compressed_code,
	        compressed_bits);
	assertf(compressed_bits >= tree->zr_minlen &&
	        compressed_bits <= tree->zr_maxlen,
	        "compressed_bits must be within the limits of the table\n"
	        "compressed_bits = %" PRIu8 "\n"
	        "tree->zr_minlen = %" PRIu8 "\n"
	        "tree->zr_maxlen = %" PRIu8,
	        compressed_bits,
	        tree->zr_minlen,
	        tree->zr_maxlen);
	for (i = 0; i < tree->zr_count; ++i) {
		if (tree->zt_tree[i].te_len != compressed_bits)
			continue;
		if (tree->zt_tree[i].te_code != compressed_code)
			continue;
		return &tree->zt_tree[i];
	}
	return NULL;
}

#define HOFF_DECODE_NOCACHE(result, tree)                        \
	for (self->zr_temp = (tree).zr_minlen;; ++self->zr_temp) {   \
		struct zlib_treeent *_ent;                               \
		REQUIREBITS(self->zr_temp);                              \
		_ent = zlib_tree_find_slow((struct zlib_tree *)&(tree),  \
		                           (u16)PEEKBITS(self->zr_temp), \
		                           self->zr_temp);               \
		if (_ent) {                                              \
			(result) = (u16)((_ent) - (tree).zt_tree);           \
			TAKEBITS(self->zr_temp);                             \
			break;                                               \
		}                                                        \
		if (self->zr_temp >= (tree).zr_maxlen)                   \
			YIELD_FOREVER(ZLIB_ERROR_UNKNOWN_SEQUENCE);          \
	}


static_assert(sizeof(struct zlib_treeent) == __SIZEOF_ZLIB_TREEENT);
#if __SIZEOF_ZLIB_TREEENT == 2
#define ZLIB_TREEENT_WORD(te_len)               ENCODE_INT16(te_len, 0, 0)
#define ZLIB_TREEENT_MEMSET(base, word, count)  ((struct zlib_treeent *)memsetw(base, word, count))
#define ZLIB_TREEENT_MEMPSET(base, word, count) ((struct zlib_treeent *)mempsetw(base, word, count))
#elif __SIZEOF_ZLIB_TREEENT == 4
#define ZLIB_TREEENT_WORD(te_len)               ENCODE_INT32(te_len, 0, 0, 0)
#define ZLIB_TREEENT_MEMSET(base, word, count)  ((struct zlib_treeent *)memsetl(base, word, count))
#define ZLIB_TREEENT_MEMPSET(base, word, count) ((struct zlib_treeent *)mempsetl(base, word, count))
#else
#error "Unsupported sizeof(struct zlib_treeent)"
#endif


/* DONT REMOVE THIS!
 * This line ensures that state=1 isn't being used in  `libzlib_reader_read',
 * since that state is treated special, as it indicates a graceful EOF state,
 * as well as state=2 be used to point after the header loading portion. */
enum { _counter_spin = __COUNTER__, _counter_spin2 = __COUNTER__ };


/* Same  as   `zlib_reader_read()',  but   read  from   a
 * specific `pos', rather than from the current position.
 * WARNING: This function is rather slow and should not be used unless absolutely necessary!
 *          If    possible,   you   should    always   use   `zlib_reader_read()'   instead!
 * NOTE: This function makes sure not to clobber the reader's previous state. */
PRIVATE WUNUSED NONNULL((1)) ssize_t CC
zlib_reader_pread(struct zlib_reader *__restrict self,
                  void *buf, size_t bufsize, uintptr_t pos);


LOCAL NONNULL((1)) void CC
zlib_window_putc(struct zlib_window *__restrict self,
                 byte_t b) {
	self->zw_buffer[self->zw_next] = b;
	++self->zw_next;
	self->zw_next &= self->zw_mask;
	if (self->zw_used <= self->zw_mask)
		++self->zw_used;
}

LOCAL NONNULL((1)) void CC
zlib_window_write(struct zlib_window *__restrict self,
                  void const *buf, size_t num_bytes) {
	/* TODO: This can be done much better! */
	size_t i;
	for (i = 0; i < num_bytes; ++i) {
		zlib_window_putc(self, ((byte_t *)buf)[i]);
	}
}



/* Decompress up to `bufsize' bytes from `self'
 * If an error occurs during this operation, return one of `ZLIB_ERROR_*'
 * @param: buf :           The destination buffer, or `NULL' if data should be skipped.
 * @return: > 0 :          The actual number of decompressed bytes.
 * @return: 0 :            End  of  input  stream,  or  want  more  input   data.
 *                         You may check for the former using `zlib_reader_eof()'
 * @return: ZLIB_ERROR_* : Deflate error. */
INTERN WUNUSED NONNULL((1)) ssize_t CC
libzlib_reader_read(struct zlib_reader *__restrict self,
                    void *buf, size_t bufsize) {
	ssize_t result;
	size_t decompressed_bytes = 0;
	ZL_STATE_BEGIN;
	GETC(self->zr_header.zh_cmf);
	GETC(self->zr_header.zh_flg);
	/* Validate the header. */
	if ((((u16)(self->zr_header.zh_cmf * 256) + (u16)(self->zr_header.zh_flg)) % 31) != 0 ||
	    (self->zr_header.zh_cmf & 0x0f) != 0x08 || /* Needs to be the `inflate' compression method. */
	    (self->zr_header.zh_flg & 0x20) != 0 /* Require no dictionary */)
		YIELD_FOREVER(ZLIB_ERROR_BAD_HEADER);
	ATTR_FALLTHROUGH
case 2:
	do {
		unsigned int block_type;
		self->zr_inblock  = self->zr_incur;
		self->zr_inblockb = self->zr_bitbuf;
		self->zr_inblockc = self->zr_bitcnt;
		self->zr_inblocko = self->zr_offset + decompressed_bytes;
		GETBITS(self->zr_blkhead, 3);
		block_type = self->zr_blkhead >> 1;
		if (block_type == 0) {
			/* Raw data block. */
			/* Discard bits to ensure byte-alignment */
			if (self->zr_bitcnt & 7) {
				self->zr_bitbuf >>= self->zr_bitcnt & 7;
				self->zr_bitcnt &= ~7;
			}
			/* Read in the raw-data block header. */
			REQUIREBITS(32);
			assert(self->zr_bitcnt == 32);
			self->zr_bitcnt = 0;
			self->zr_count = ((u16)self->zlib_reader_zr_bitbyte(0) |
			                  (u16)self->zlib_reader_zr_bitbyte(1) << 8);
			if ((u16)self->zr_count != ((u16)0xffff ^
			                            ((u16)self->zlib_reader_zr_bitbyte(2) |
			                             (u16)self->zlib_reader_zr_bitbyte(3) << 8)))
				YIELD_FOREVER(ZLIB_ERROR_BAD_RAW_CHECKSUM);
			/* Copy a total of `self->zr_count' bytes of data directly from the input data stream.
			 * Since source data isn't actually compressed, we can just directly copy bytes  over. */
			while (self->zr_count) {
				size_t copybytes;
				copybytes = (size_t)(self->zr_inend - self->zr_incur);
				if (!copybytes) {
					YIELD(decompressed_bytes);
					continue;
				}
				if (copybytes > bufsize)
					copybytes = bufsize;
				if (self->zr_window)
					zlib_window_write(self->zr_window, self->zr_incur, copybytes);
				if (buf) {
					memcpy(buf, self->zr_incur, copybytes);
					buf = (byte_t *)buf + copybytes;
				}
				assert(copybytes <= bufsize);
				assert(copybytes <= self->zr_count);
				decompressed_bytes += copybytes;
				bufsize -= copybytes;
				self->zr_count -= copybytes;
			}
		} else if (block_type == 3) {
			YIELD_FOREVER(ZLIB_ERROR_BAD_BLOCK_TYPE);
		} else {
			/* block_type == 1 || block_type == 2 */
			if (block_type == 1) {
				/* Fixed translation table. */
				struct zlib_treeent *p = self->zr_symboltree.zt_tree;
				p = ZLIB_TREEENT_MEMPSET(p, ZLIB_TREEENT_WORD(8), (143 - 0) + 1);
				p = ZLIB_TREEENT_MEMPSET(p, ZLIB_TREEENT_WORD(9), (255 - 144) + 1);
				p = ZLIB_TREEENT_MEMPSET(p, ZLIB_TREEENT_WORD(7), (279 - 256) + 1);
				p = ZLIB_TREEENT_MEMPSET(p, ZLIB_TREEENT_WORD(8), (287 - 280) + 1);
				assert(p == COMPILER_ENDOF(self->zr_symboltree.zt_tree));
				assert(self->zr_symboltree.zt_tree[0].te_len == 8);
				assert(self->zr_symboltree.zt_tree[0].te_code == 0);
				self->zr_symboltree.zr_count  = 288;
				ZLIB_TREEENT_MEMSET(self->zr_disttree.zt_tree,
				                    ZLIB_TREEENT_WORD(5), 32);
				self->zr_disttree.zr_count  = 32;
			} else {
				GETBITS(self->zr_symboltree.zr_count, 5);
				GETBITS(self->zr_disttree.zr_count, 5);
				GETBITS(self->zr_clentree.zr_count, 4);
				self->zr_symboltree.zr_count += 257;
				self->zr_disttree.zr_count += 1;
				self->zr_clentree.zr_count += 4;
				assert(self->zr_symboltree.zr_count >= 257 && self->zr_symboltree.zr_count <= 288);
				assert(self->zr_disttree.zr_count >= 1 && self->zr_disttree.zr_count <= 32);
				assert(self->zr_clentree.zr_count >= 4 && self->zr_clentree.zr_count <= 19);
				bzero(self->zr_clentree.zt_tree, sizeof(self->zr_clentree.zt_tree));
				for (self->zr_index = 0;
				     self->zr_index < self->zr_clentree.zr_count; ++self->zr_index) {
					PRIVATE u8 const demangle_bitspercln_index[] = {
						16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
					unsigned int bitsforcln, index;
					GETBITS(bitsforcln, 3);
					index = demangle_bitspercln_index[self->zr_index];
					self->zr_clentree.zt_tree[index].te_len = bitsforcln;
				}
				self->zr_clentree.zr_count = 19;
				zlib_tree_construct((struct zlib_tree *)&self->zr_clentree);
				/* Decode the literal/length alphabet */
				self->zr_count = self->zr_symboltree.zr_count +
				                 self->zr_disttree.zr_count;
				for (self->zr_index = 0; self->zr_index < self->zr_count;) {
					u8 value, repval, repcnt;
					HOFF_DECODE_NOCACHE(value, self->zr_clentree);
					assert(value >= 0 && value <= 18);
					if (value <= 15) {
						if (self->zr_index < self->zr_symboltree.zr_count) {
							self->zr_symboltree.zt_tree[self->zr_index].te_len = value;
						} else {
							self->zr_disttree.zt_tree[self->zr_index - self->zr_symboltree.zr_count].te_len = value;
						}
						++self->zr_index;
						continue;
					}
					/* Repeat sequences. */
					if (value == 16) {
						/* Repeat the previous length-value. */
						if unlikely(self->zr_index == 0)
							YIELD_FOREVER(ZLIB_ERROR_LEN_REPEAT_ZERO);
						GETBITS(repcnt, 2);
						repcnt += 3;
						repval = self->zr_index <= self->zr_symboltree.zr_count
						         ? self->zr_symboltree.zt_tree[self->zr_index - 1].te_len
						         : self->zr_disttree.zt_tree[(self->zr_index - 1) - self->zr_symboltree.zr_count].te_len;
					} else if (value == 17) {
						/* Repeat 0s */
						GETBITS(repcnt, 3);
						repcnt += 3;
						repval = 0;
					} else {
						assert(value == 18);
						/* Repeat even more 0s */
						GETBITS(repcnt, 7);
						repcnt += 11;
						repval = 0;
					}
					/* Check if the repeat count is in-bounds */
					if unlikely(self->zr_index + repcnt > self->zr_count)
						YIELD_FOREVER(ZLIB_ERROR_LEN_REPEAT_LARGE);
					/* Output the values. */
					if (self->zr_index >= self->zr_symboltree.zr_count) {
						/* Output only into `zr_disttree' */
						ZLIB_TREEENT_MEMSET(self->zr_disttree.zt_tree +
						                    (self->zr_index - self->zr_symboltree.zr_count),
						                    ZLIB_TREEENT_WORD(repval), repcnt);
					} else if (self->zr_index + repcnt <= self->zr_symboltree.zr_count) {
						/* Output only into `zr_symboltree' */
						ZLIB_TREEENT_MEMSET(self->zr_symboltree.zt_tree + self->zr_index,
						                    ZLIB_TREEENT_WORD(repval), repcnt);
					} else {
						u16 symbol_count;
						/* Output into both `zr_symboltree' and `zr_disttree' */
						assert(self->zr_symboltree.zr_count > self->zr_index);
						symbol_count = self->zr_symboltree.zr_count - self->zr_index;
						ZLIB_TREEENT_MEMSET(self->zr_symboltree.zt_tree + self->zr_index,
						                    ZLIB_TREEENT_WORD(repval), symbol_count);
						ZLIB_TREEENT_MEMSET(self->zr_disttree.zt_tree,
						                    ZLIB_TREEENT_WORD(repval), repcnt - symbol_count);
					}
					self->zr_index += repcnt;
				}
			}
			/* Construct the symbol and distance trees. */
			zlib_tree_construct((struct zlib_tree *)&self->zr_symboltree);
			zlib_tree_construct((struct zlib_tree *)&self->zr_disttree);
			if (self->zr_symbolcache) {
				zlib_tree_construct_cache((struct zlib_tree *)&self->zr_symboltree,
				                          self->zr_symbolcache);
			}
			/* Do the actual decompressing! */
			for (;;) {
				u16 symbol;
				u32 distance, length;
				/* Base amount of copied bytes for each extended code. */
				PRIVATE u16 const length_base[31] = {
					3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31,
					35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258,
					0, 0 /* These  last  2   aren't  defined   by  the   standard.
					      * By using `0' for them, we can detect them as an error.
					      * HINT: These would belong to symbol codes `286' and `287' */
				};
				/* # of additional bits used to extend the copy-length. */
				PRIVATE u8 const length_bits[31] = {
					0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
					3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0,
					0, 0 /* Again: These last 2 aren't actually defined. */
				};
				PRIVATE u16 const distance_base[32] = {
					1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
					257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577,
					0, 0 /* These two are undefined by the standard. */
				};
				PRIVATE u8 const distance_bits[32] = {
					0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
					7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13,
					0, 0 /* These two are undefined by the standard. */
				};
				while (!bufsize)
					YIELD(decompressed_bytes);
				if (self->zr_symbolcache) {
					u16 ent;
					REQUIREBITS(ZT_CACHE_BITS);
					ent = self->zr_symbolcache->c_lookup[PEEKBITS(ZT_CACHE_BITS)];
					if (!ent)
						goto decode_symbol_nocache;
					TAKEBITS((u8)(ent >> ZT_CACHEENT_SIZESHIFT));
					symbol = ent & ZT_CACHEENT_SYMBMASK;
				} else {
decode_symbol_nocache:
					HOFF_DECODE_NOCACHE(symbol,
					                    self->zr_symboltree);
				}
				if (symbol <= 0xff) {
					if (self->zr_window)
						zlib_window_putc(self->zr_window, (byte_t)symbol);
					if (buf) {
						*(byte_t *)buf = (byte_t)symbol;
						buf = (byte_t *)buf + 1;
					}
					++decompressed_bytes;
					--bufsize;
					continue;
				}
				assert(symbol >= 256 && symbol <= 287);
				if (symbol == 256)
					break; /* End-of-block */
				/* Distance / Length compression. */
				length = length_base[symbol - 257];
				if (length_bits[symbol - 257]) {
					u16 extra;
#undef SAVE_AND_LOAD
#define SAVE_AND_LOAD                                     \
					(/*save:*/ (self->zr_index = symbol), \
					 /*load:*/ (symbol = self->zr_index,  \
					            length = length_base[symbol - 257]))
					GETBITS(extra, length_bits[symbol - 257]);
#undef SAVE_AND_LOAD
#define SAVE_AND_LOAD (, )
					length += extra;
				}
				/* Decode the compressed distance data word. */
#undef SAVE_AND_LOAD
#define SAVE_AND_LOAD                                 \
				(/*save:*/ (self->zr_count = length), \
				 /*load:*/ (length = self->zr_count))
				HOFF_DECODE_NOCACHE(symbol, self->zr_disttree);
#undef SAVE_AND_LOAD
#define SAVE_AND_LOAD (, )
				assert(symbol >= 0 && symbol <= 31);
				distance = distance_base[symbol];
				if (distance_bits[symbol]) {
					u16 extra;
#undef SAVE_AND_LOAD
#define SAVE_AND_LOAD                                                              \
					(/*save:*/ (self->zr_count = length, self->zr_index = symbol), \
					 /*load:*/ (length = self->zr_count, symbol = self->zr_index, distance = distance_base[symbol]))
					GETBITS(extra, distance_bits[symbol]);
#undef SAVE_AND_LOAD
#define SAVE_AND_LOAD (, )
					distance += extra;
				}
				/* At this point, we've decoded both `length' and `distance'!
				 * -> Time to the the actual work. */
				if unlikely(!distance)
					YIELD_FOREVER(ZLIB_ERROR_BAD_DISTANCE);
				if unlikely(!length)
					YIELD_FOREVER(ZLIB_ERROR_BAD_LENGTH);
again_check_buf_for_repeat:
				/* Repeat data that isn't already  contained within the output  buffer.
				 * Doing this is somewhat more complex, since it requires us to either:
				 *  - Make use of a sliding window (which would have to 32K bytes large)
				 *  - Rewind the inflate stream to  the location that should be  copied.
				 *    Though this method requires that the input data blob be continuous */
				if (self->zr_window &&
				    distance <= self->zr_window->zw_used) {
					/* TODO: Copy from the sliding window. */
				}
				/* Without any output buffer or sliding window, we don't have to do anything! */
				if ((!buf && !self->zr_window) || !bufsize) {
					if (bufsize >= length) {
						bufsize -= length;
						decompressed_bytes += length;
						continue;
					}
					decompressed_bytes += bufsize;
					length -= bufsize;
					goto save_distance_and_length_and_yield;
				}
				assert(bufsize != 0);
				/* Check  for  the  simple  case:  The  data to-be
				 * repeated is apart of the current output buffer. */
				if (distance <= decompressed_bytes && buf) {
					byte_t const *src;
					size_t pattern_length;
repeat_pattern_inline_in_buf:
					src = (byte_t const *)buf - distance;
					if (distance >= length) {
						/* Non-overlapping (don't produce a repeating pattern) */
						if (bufsize >= length) {
							if (self->zr_window)
								zlib_window_write(self->zr_window, src, length);
							memcpy(buf, src, length);
							buf = (byte_t *)buf + length;
							bufsize -= length;
							decompressed_bytes += length;
							continue;
						}
						if (self->zr_window)
							zlib_window_write(self->zr_window, src, bufsize);
						memcpy(buf, src, bufsize);
						decompressed_bytes += bufsize;
						length -= bufsize;
save_distance_and_length_and_yield:
						self->zr_index = distance;
						self->zr_count = length;
						YIELD(decompressed_bytes);
						distance = self->zr_index;
						length   = self->zr_count;
						goto again_check_buf_for_repeat;
					}
					/* Overlapping (produce a repeating pattern) */
					pattern_length = distance;
					while (length) {
						size_t partlen;
						partlen = distance;
						if (partlen > length)
							partlen = length;
						if (partlen > bufsize) {
							partlen = bufsize;
							if (!bufsize) {
								u32 new_distance;
								new_distance = ((byte_t *)buf - (byte_t const *)src) + pattern_length;
								if (distance < new_distance)
									distance = new_distance;
								goto save_distance_and_length_and_yield;
							}
						}
						if (self->zr_window)
							zlib_window_write(self->zr_window, src, partlen);
						memcpy(buf, src, partlen);
						bufsize -= partlen;
						buf = (byte_t *)buf + partlen;
						decompressed_bytes += partlen;
						distance += partlen;
						length -= partlen;
					}
					continue;
				}
				assert(distance > decompressed_bytes);
				/* The complicated case: Rewind the stream so we can read from a past position. */
				{
					uintptr_t obo;
					size_t read_count;
					obo = self->zr_offset + decompressed_bytes;
					if unlikely(distance > obo) {
						/* The target location is located out-of-bounds.
						 * XXX: This could also  happen when  the user has  fed us  with
						 *      a  secondary input  data blob,  in which  case we should
						 *      indicate an  out-of-memory error  when we  don't have  a
						 *      window (which would mean that we were unable to allocate
						 *      one at some point in the past) */
						YIELD_FOREVER(ZLIB_ERROR_OOB_DISTANCE);
					}
					obo -= distance;
					read_count = length;
					if (read_count > bufsize)
						read_count = bufsize;
					if (read_count > distance)
						read_count = distance; /* Deal with repeating patterns */
					self->zr_offset += decompressed_bytes;
					if (self->zr_flags & _ZLIB_READER_PFLAG_LINEARREPEAT) {
						self->zr_index = obo;
						self->zr_count = read_count;
						self->zr_flags |= _ZLIB_READER_PFLAG_LINEARREPDID;
						result = (ssize_t)decompressed_bytes;
						goto done;
					}
					result = zlib_reader_pread(self, buf, read_count, obo);
					if unlikely(result < 0)
						return result;
					self->zr_offset -= decompressed_bytes;
					assertf((size_t)result == read_count,
					        "This shouldn't happen since our current buffer position "
					        "should be located _after_ the position that we were reading "
					        "from, so to get an EOF by reading from an earlier position, "
					        "there has to be some kind of inconsistency within the inflate "
					        "reader itself\n"
					        "result     = %" PRIuSIZ "\n"
					        "read_count = %" PRIuSIZ,
					        result, read_count);
					decompressed_bytes += read_count;
					length             -= read_count;
					bufsize            -= read_count;
					buf = (byte_t *)buf + read_count;
					if (!length)
						continue;
					if (!bufsize)
						goto save_distance_and_length_and_yield;
					/* This is the repeating-pattern case */
					assert(distance == read_count);
					goto repeat_pattern_inline_in_buf;
				}
				/* Continue processing data that hasn't already been read. */
				if (length != 0)
					goto again_check_buf_for_repeat;
			}
		}
	} while (!(self->zr_blkhead & 1)); /* Continue while not having reached the last block. */
	/* Natural EOF */
	self->zr_state = 1;
	ATTR_FALLTHROUGH
case 1:
	result = (ssize_t)decompressed_bytes;
	break;
	ZL_STATE_END;
done:
	self->zr_offset += decompressed_bytes;
	return result;
}


/* Feed the given ZLIB reader  another blob of compressed  data.
 * This function must be called to continue decompression  after
 * `zlib_reader_read()' returned 0 with a non-empty buffer size,
 * and `zlib_reader_eof(self)' also returning false.
 * WARNING: In order for `feed' to function properly, the reader
 *          must   have  access  to  a  sliding  window  buffer.
 *          Otherwise,  you must ensure that the compressed data
 *          blob is already complete from the get-go. */
INTERN NONNULL((1)) void CC
libzlib_reader_feed(struct zlib_reader *__restrict self,
                    void const *blob, size_t blob_size) {
	assertf(self->zr_incur >= self->zr_inbase &&
	        self->zr_incur <= self->zr_inend,
	        "Out-of-bounds in-pointer");
	assertf(self->zr_incur >= self->zr_inend,
	        "in-pointer not at the end, yet");
	assertf(!zlib_reader_eof(self),
	        "EOF has already been reached");
	self->zr_inbase  = (byte_t const *)blob;
	self->zr_incur   = (byte_t const *)blob;
	self->zr_inend   = (byte_t const *)blob + blob_size;
	self->zr_state   = 2;
	self->zr_offset  = 0;
	self->zr_inblock = NULL;
}



/* Set the absolute reader position.
 * @return: >= 0:          The new (actually set) absolute position.
 * @return: ZLIB_ERROR_* : Deflate error. */
INTERN WUNUSED NONNULL((1)) ssize_t CC
libzlib_reader_setpos(struct zlib_reader *__restrict self,
                      uintptr_t pos) {
	ssize_t result;
	/* Check if the given `pos' lies within the current block, in which
	 * case we won't have to walk through all compressed data prior  to
	 * the current `pos'. */
	if (pos > self->zr_offset) {
		result = libzlib_reader_read(self, NULL, pos - self->zr_offset);
	} else {
		if (self->zr_inblock && pos >= self->zr_inblocko) {
			self->zr_state  = 2;
			self->zr_incur  = self->zr_inblock;
			self->zr_bitbuf = self->zr_inblockb;
			self->zr_bitcnt = self->zr_inblockc;
			self->zr_offset = self->zr_inblocko;
			result = (ssize_t)self->zr_inblocko;
			pos -= (size_t)result;
			if (pos != 0)
				result = libzlib_reader_read(self, NULL, pos);
		} else {
			/* Rewind the reader, and skip until `pos' */
			libzlib_reader_rewind(self);
			result = libzlib_reader_read(self, NULL, pos);
		}
	}
	if (result >= 0)
		result = self->zr_offset;
	return result;
}

/* Rewind the given reader. */
INTERN NONNULL((1)) void CC
libzlib_reader_rewind(struct zlib_reader *__restrict self) {
	self->zr_incur   = self->zr_inbase;
	self->zr_state   = 2;
	self->zr_offset  = 0;
	self->zr_bitcnt  = 0;
	self->zr_inblock = NULL;
}


PRIVATE WUNUSED NONNULL((1)) ssize_t CC
zlib_reader_pread_clobber(struct zlib_reader *__restrict self,
                          void *buf, size_t bufsize, uintptr_t pos) {
	ssize_t result, addend = 0;
again_setpos:
	result = libzlib_reader_setpos(self, pos);
	if unlikely(result < 0)
		goto err;
	if likely((uintptr_t)result == pos) {
		self->zr_flags |= _ZLIB_READER_PFLAG_LINEARREPEAT;
		result = libzlib_reader_read(self, buf, bufsize);
		if unlikely(result < 0)
			goto err;
		if (self->zr_flags & _ZLIB_READER_PFLAG_LINEARREPDID) {
			addend += (size_t)result;
			bufsize -= (size_t)result;
			buf = (byte_t *)buf + (size_t)result;
			assert(self->zr_count <= bufsize);
			/* Read from (possibly) 2 locations:
			 * >> PREAD(self->zr_index, buf, self->zr_count);
			 * >> PREAD(pos, buf + self->zr_count, bufsize - self->zr_count);
			 * The  second  read  will  be  performed  later  by  our caller. */
			bufsize = self->zr_count; /* Truncate to the first read */
			pos = self->zr_index; /* Resume at the saved position. */
			self->zr_flags &= ~(_ZLIB_READER_PFLAG_LINEARREPEAT |
			                    _ZLIB_READER_PFLAG_LINEARREPDID);
			self->zr_state = 2;
			goto again_setpos;
		}
	}
	return result + addend;
err:
	return result;
}

/* Same  as   `zlib_reader_read()',  but   read  from   a
 * specific `pos', rather than from the current position.
 * WARNING: This function is rather slow and should not be used unless absolutely necessary!
 *          If    possible,   you   should    always   use   `zlib_reader_read()'   instead!
 * NOTE: This function makes sure not to clobber the reader's previous state. */
PRIVATE WUNUSED NONNULL((1)) ssize_t CC
zlib_reader_pread(struct zlib_reader *__restrict self,
                  void *buf, size_t bufsize, uintptr_t pos) {
	ssize_t result;
	struct zlib_reader saved_reader;
	assert(buf);
	self->zr_flags &= ~_ZLIB_READER_PFLAG_CACHECHANGED;
	memcpy(&saved_reader, self, sizeof(struct zlib_reader));
	result = zlib_reader_pread_clobber(self, buf, bufsize, pos);
	if likely(result >= 0) {
		while (result && (size_t)result < bufsize) {
			ssize_t temp;
			/* Read more (this can happen as the result of split repeat operations) */
			temp = zlib_reader_pread_clobber(self,
			                                 (byte_t *)buf + (size_t)result,
			                                 bufsize - (size_t)result,
			                                 pos + (size_t)result);
			if unlikely(temp < 0)
				return temp;
			result += temp;
		}
		/* Don't restore modified cache pointers. */
		if (!(self->zr_flags & _ZLIB_READER_PFLAG_CACHECHANGED)) {
			assert(!(saved_reader.zr_flags & _ZLIB_READER_PFLAG_CACHECHANGED));
			assert(self->zr_symbolcache == saved_reader.zr_symbolcache);
			memcpy(self, &saved_reader, sizeof(struct zlib_reader));
		} else {
			saved_reader.zr_symbolcache = self->zr_symbolcache;
			memcpy(self, &saved_reader, sizeof(struct zlib_reader));
			/* Re-construct caches (if possible) */
			if (self->zr_symbolcache) {
				zlib_tree_construct_cache((struct zlib_tree *)&self->zr_symboltree,
				                          self->zr_symbolcache);
			}
		}
	}
	return result;
}


DEFINE_PUBLIC_ALIAS(zlib_reader_init, libzlib_reader_init);
DEFINE_PUBLIC_ALIAS(zlib_reader_fini, libzlib_reader_fini);
DEFINE_PUBLIC_ALIAS(zlib_reader_read, libzlib_reader_read);
DEFINE_PUBLIC_ALIAS(zlib_reader_feed, libzlib_reader_feed);
DEFINE_PUBLIC_ALIAS(zlib_reader_setpos, libzlib_reader_setpos);
DEFINE_PUBLIC_ALIAS(zlib_reader_rewind, libzlib_reader_rewind);

DECL_END

#endif /* !GUARD_LIBZLIB_INFLATE_C */
