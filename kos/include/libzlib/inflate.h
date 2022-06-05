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
#ifndef _LIBZLIB_INFLATE_H
#define _LIBZLIB_INFLATE_H 1

#include "api.h"

#include <hybrid/__bitfield.h>

#include <bits/types.h>

/* Specs for how to inflate zlib-compressed data blobs can be found here:
 *  - https://www.w3.org/Graphics/PNG/RFC-1951
 */


/* Q: Why didn't you just use the real zlib, or something equivalent like miniz?
 * A: I wanted an inflate solution that could (in theory) function without the use
 *    of dynamically allocated heap memory, given enough time.
 *    Besides that: have you looked at how wasteful miniz is when it comes to memory
 *    allocations? geez... that thing is a monster!
 *
 */

__DECL_BEGIN

struct zlib_header {
	__uint8_t zh_cmf; /* Compression Method */
	__uint8_t zh_flg; /* Flags */
};

#define __SIZEOF_ZLIB_TREEENT 4
struct zlib_treeent {
	/* NOTE: The decompressed symbol value is the index of the entry! */
#if 1
	__uint8_t    te_len;      /* Entry length. */
	__uint8_t    te_pad;      /* ... */
#else
	__HYBRID_BITFIELD16_T te_len : 4;  /* Entry length. */
	__HYBRID_BITFIELD16_T te_pad : 12; /* ... */
#endif
	__uint16_t   te_code;     /* Compressed bit sequence (with a length of `te_len' bits). */
};


struct zlib_cache;
#define ZLIB_TREE_BODY(maxlen)                                                            \
	{                                                                                     \
		__uint16_t          zr_count;        /* Size of the tree. */                      \
		__uint8_t           zr_minlen;       /* Length (in bits) of the smallest code. */ \
		__uint8_t           zr_maxlen;       /* Length (in bits) of the largest code. */  \
		struct zlib_treeent zt_tree[maxlen]; /* [zr_count] The associated tree. */        \
	}
struct zlib_tree ZLIB_TREE_BODY(288);

#define ZLIB_WINDOW_BODY(maxlen)                                                                               \
	{                                                                                                          \
		__uint16_t zw_next;         /* Index of the next byte to-be written. */                                \
		__uint16_t zw_used;         /* Used buffer size. */                                                    \
		__uint16_t zw_mask;         /* [const][== sizeof(zw_buffer) - 1] The size of the window buffer. */     \
		__byte_t zw_buffer[maxlen]; /* [zw_size + 1] The window buffer (NOTE: size _must_ be a power-of-2). */ \
	}

struct zlib_window ZLIB_WINDOW_BODY(0x10000);

struct zlib_reader {
	__byte_t const        *zr_inbase;      /* [1..1][const] (compressed) input data base pointer */
	__byte_t const        *zr_incur;       /* [1..?] (compressed) input data read pointer */
	__byte_t const        *zr_inend;       /* [1..?][const] (compressed) input data end pointer */
	__uintptr_t            zr_offset;      /* Number of decompressed bytes between `zr_inbase' and `zr_incur' */
	__uintptr_t            zr_state;       /* Deflate state (internal) */
	struct zlib_window    *zr_window;      /* [0..1] Sliding window buffer (optional). */
	union {
		__uint32_t         zr_bitbuf;      /* Buffer of pending bits (next bit is `zr_bitbuf & 1') */
		__uint8_t         _zr_bitbyteN[4];
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define zlib_reader_zr_bitbyte(i) _zr_bitbyteN[i]
			__uint8_t      zr_bitbyte0;
			__uint8_t      zr_bitbyte1;
			__uint8_t      zr_bitbyte2;
			__uint8_t      zr_bitbyte3;
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define zlib_reader_zr_bitbyte(i) _zr_bitbyteN[3 - (i)]
			__uint8_t      zr_bitbyte3;
			__uint8_t      zr_bitbyte2;
			__uint8_t      zr_bitbyte1;
			__uint8_t      zr_bitbyte0;
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
	};
	__size_t                   zr_count;       /* Internal, temporary variable (used during read operations). */
	__size_t                   zr_index;       /* Internal, temporary variable (used during read operations). */
	__byte_t const            *zr_inblock;     /* [0..1] (compressed) input data of where the current block has started. */
	__uintptr_t                zr_inblocko;    /* [valid_if(zr_inblock)] Number of decompressed bytes between `zr_inbase' and `zr_inblock' */
	__uint32_t                 zr_inblockb;    /* [valid_if(zr_inblock)] Bit buffer for `zr_inblock' */
	__uint8_t                  zr_inblockc;    /* [valid_if(zr_inblock)] Bit count for `zr_inblock' */
	__uint8_t                  zr_bitcnt;      /* # of pending bits (in `zr_bitbuf') */
	__uint8_t                  zr_blkhead;     /* Current block header (&1: Last block; >>1: block type) */
	__uint8_t                  zr_temp;        /* Used internally */
	__uint8_t                  zr_flags;       /* Set of `_ZLIB_READER_PFLAG_*' */
#define _ZLIB_READER_PFLAG_CACHECHANGED 0x01   /* Set if caches have been changed. */
#define _ZLIB_READER_PFLAG_LINEARREPEAT 0x02   /* Perform linear distance repeat operations. */
#define _ZLIB_READER_PFLAG_LINEARREPDID 0x04   /* Returned because of a linear repeat. */
	struct zlib_header         zr_header;      /* ZLib Header. */
	struct ZLIB_TREE_BODY(288) zr_symboltree;  /* Symbol tree. (`te_len' is 0-15 each) */
	struct ZLIB_TREE_BODY(32)  zr_disttree;    /* Distance tree. (`te_len' is 0-5 each) */
	struct ZLIB_TREE_BODY(19)  zr_clentree;    /* Code length tree. (`te_len' is 0-7 each) */
	struct zlib_cache         *zr_symbolcache; /* [0..1][owned] Tree translation cache for `zr_symboltree'. */
};

/* Check if the end of data stream has been reached. */
#define zlib_reader_eof(self) ((self)->zr_state == 1)



/* Initialize a ZLIB reader, given an initial data blob. */
typedef __ATTR_NONNULL_T((1)) void
__NOTHROW_NCX_T(LIBZLIB_CC *PZLIB_READER_INIT)(struct zlib_reader *__restrict self,
                                               void const *blob, size_t blob_size);
#ifdef LIBZLIB_WANT_PROTOTYPES
LIBZLIB_DECL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(LIBZLIB_CC zlib_reader_init)(struct zlib_reader *__restrict self,
                                           void const *blob, size_t blob_size);
#endif /* LIBZLIB_WANT_PROTOTYPES */


/* Finalize the given zlib reader. */
typedef __ATTR_NONNULL_T((1)) void
__NOTHROW_NCX_T(LIBZLIB_CC *PZLIB_READER_FINI)(struct zlib_reader *__restrict self);
#ifdef LIBZLIB_WANT_PROTOTYPES
LIBZLIB_DECL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(LIBZLIB_CC zlib_reader_fini)(struct zlib_reader *__restrict self);
#endif /* LIBZLIB_WANT_PROTOTYPES */


/* Decompress up to `bufsize' bytes from `self'
 * If an error occurs during this operation, return one of `ZLIB_ERROR_*'
 * @param: buf :           The destination buffer, or `NULL' if data should be skipped.
 * @return: > 0 :          The actual number of decompressed bytes.
 * @return: 0 :            End  of  input  stream,  or  want  more  input   data.
 *                         You may check for the former using `zlib_reader_eof()'
 * @return: ZLIB_ERROR_* : Deflate error. */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __ssize_t
(LIBZLIB_CC *PZLIB_READER_READ)(struct zlib_reader *__restrict self,
                                void *buf, __size_t bufsize);
#ifdef LIBZLIB_WANT_PROTOTYPES
LIBZLIB_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ssize_t LIBZLIB_CC
zlib_reader_read(struct zlib_reader *__restrict self,
                 void *buf, __size_t bufsize);
#endif /* LIBZLIB_WANT_PROTOTYPES */

/* Feed the given ZLIB reader  another blob of compressed  data.
 * This function must be called to continue decompression  after
 * `zlib_reader_read()' returned 0 with a non-empty buffer size,
 * and `zlib_reader_eof(self)' also returning false.
 * WARNING: In order for `feed' to function properly, the reader
 *          must   have  access  to  a  sliding  window  buffer.
 *          Otherwise,  you must ensure that the compressed data
 *          blob is already complete from the get-go. */
typedef __ATTR_NONNULL_T((1)) void
(LIBZLIB_CC *PZLIB_READER_FEED)(struct zlib_reader *__restrict self,
                                void const *blob, size_t blob_size);
#ifdef LIBZLIB_WANT_PROTOTYPES
LIBZLIB_DECL __ATTR_NONNULL((1)) void LIBZLIB_CC
zlib_reader_feed(struct zlib_reader *__restrict self,
                 void const *blob, size_t blob_size);
#endif /* LIBZLIB_WANT_PROTOTYPES */

/* NOTE: All of the following functions can only (safely) be used if  the
 *       entire compressed data blob is already known from the beginning! */

/* Set the absolute reader position.
 * @return: >= 0:          The new (actually set) absolute position.
 * @return: ZLIB_ERROR_* : Deflate error. */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __ssize_t
(LIBZLIB_CC *PZLIB_READER_SETPOS)(struct zlib_reader *__restrict self,
                                  __uintptr_t pos);
#ifdef LIBZLIB_WANT_PROTOTYPES
LIBZLIB_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ssize_t LIBZLIB_CC
zlib_reader_setpos(struct zlib_reader *__restrict self,
                   __uintptr_t pos);
#endif /* LIBZLIB_WANT_PROTOTYPES */

/* Rewind the given reader. */
typedef __ATTR_NONNULL_T((1)) void
(LIBZLIB_CC *PZLIB_READER_REWIND)(struct zlib_reader *__restrict self);
#ifdef LIBZLIB_WANT_PROTOTYPES
LIBZLIB_DECL __ATTR_NONNULL((1)) void LIBZLIB_CC
zlib_reader_rewind(struct zlib_reader *__restrict self);
#endif /* LIBZLIB_WANT_PROTOTYPES */


__DECL_END

#endif /* !_LIBZLIB_INFLATE_H */
