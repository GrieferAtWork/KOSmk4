/*[[[magic
// Compile as `c', so we can use the "register" keyword for optimization hints
options["COMPILE.language"] = "c";
]]]*/
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
#ifndef GUARD_LIBREGEX_REGEXEC_C
#define GUARD_LIBREGEX_REGEXEC_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define LIBREGEX_WANT_PROTOTYPES

#include "api.h"
/**/
#include <hybrid/compiler.h>

#include <hybrid/minmax.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <bits/os/iovec.h>

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <unicode.h>

#include <libregex/regcomp.h>
#include <libregex/regexec.h>

#include "regexec.h"

#if 0
#include <sys/syslog.h>
#define HAVE_TRACE
#define TRACE(...) syslog(LOG_DEBUG, __VA_ARGS__)
#else
#define TRACE(...) (void)0
#endif

DECL_BEGIN

#define islf(ch) ((ch) == '\r' || (ch) == '\n')


#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

struct re_onfailure_item {
	byte_t const *rof_in; /* [1..1] Input data pointer to restore (points into some input buffer) */
	byte_t const *rof_pc; /* [1..1] Program counter to restore */
};

struct re_interpreter_inptr {
	byte_t const       *ri_in_ptr;    /* [<= ri_in_cend] Current input pointer. */
	byte_t const       *ri_in_cend;   /* End of the current input chunk */
	byte_t const       *ri_in_cbase;  /* [0..1] Original base pointer of current input IOV chunk */
	byte_t const       *ri_in_vbase;  /* [0..1] Virtual base pointer of current input IOV chunk (such that `ri_in_ptr - ri_in_vbase'
	                                   * produces offsets compatible with `struct re_exec::rx_startoff' and the like, including  the
	                                   * start/end offsets stored in `ri_pmatch') */
	struct iovec const *ri_in_miov;   /* [0..*] Further input chunks that have yet to be loaded. (current chunk originates from `ri_in_miov[-1]') */
	size_t              ri_in_mcnt;   /* # of remaining bytes in buffers described by `ri_in_miov[*]' */
};

struct re_interpreter {
	union {
		struct re_interpreter_inptr ri_in;        /* Input pointer controller. */
		struct {
			byte_t const           *ri_in_ptr;    /* [<= ri_in_cend] Current input pointer. */
			byte_t const           *ri_in_cend;   /* End of the current input chunk */
			byte_t const           *ri_in_cbase;  /* [0..1] Original base pointer of current input IOV chunk */
			byte_t const           *ri_in_vbase;  /* [0..1] Virtual base pointer of current input IOV chunk (such that `ri_in_ptr - ri_in_vbase'
			                                       * produces offsets compatible with `struct re_exec::rx_startoff' and the like, including  the
			                                       * start/end offsets stored in `ri_pmatch') */
			struct iovec const     *ri_in_miov;   /* [0..*] Further input chunks that have yet to be loaded. (current chunk originates from `ri_in_miov[-1]') */
			size_t                  ri_in_mcnt;   /* # of remaining bytes in buffers described by `ri_in_miov[*]' */
		};
	};
	struct iovec const             *ri_in_biov;   /* [0..*][<= ri_in_miov][const] Initial iov vector base (== `struct re_exec::rx_iov') */
	struct re_exec const           *ri_exec;      /* [1..1][const] Regex exec command block. */
	re_regmatch_t                  *ri_pmatch;    /* [1..ri_exec->rx_code->rc_ngrps][const] Group match start/end offset register buffer (owned if caller-provided buffer is too small). */
	struct re_onfailure_item       *ri_onfailv;   /* [0..ri_onfailc][owned(free)] On-failure stack */
	size_t                          ri_onfailc;   /* [<= ri_onfaila] # of elements on the on-failure stack */
	size_t                          ri_onfaila;   /* Allocated # of elements of `ri_onfailv' */
	struct re_interpreter_inptr     ri_bmatch;    /* USED INTERNALLY: pending best match */
	COMPILER_FLEXIBLE_ARRAY(byte_t, ri_vars);     /* [ri_exec->rx_code->rc_nvars] Space for variables used by code. */
};
#define re_interpreter_inptr_in_advance1(self)                                                           \
	(unlikely((self)->ri_in_ptr >= (self)->ri_in_cend) ? re_interpreter_inptr_nextchunk(self) : (void)0, \
	 ++(self)->ri_in_ptr)
#define re_interpreter_inptr_in_reverse1(self)                                                            \
	(unlikely((self)->ri_in_ptr <= (self)->ri_in_cbase) ? re_interpreter_inptr_prevchunk(self) : (void)0, \
	 --(self)->ri_in_ptr)
#define re_interpreter_in_chunkcontains(self, inptr) \
	((inptr) >= re_interpreter_in_chunkbase(self) && \
	 (inptr) <= re_interpreter_in_chunkend(self)) /* yes: '<=', because inptr == end-of-chunk means epsilon (in case of the last chunk) */
#define re_interpreter_in_isfirstchunk(self)    ((self)->ri_in_miov <= (self)->ri_in_biov + 1)           /* True if in first chunk */
#define re_interpreter_in_islastchunk(self)     ((self)->ri_in_mcnt <= 0)                                /* True if in last chunk */
#define re_interpreter_in_chunk_cangetc(self)   ((self)->ri_in_ptr < (self)->ri_in_cend)                 /* True if not at end of current chunk */
#define re_interpreter_in_chunk_canungetc(self) ((self)->ri_in_ptr > (self)->ri_in_cbase)                /* True if not at start of current chunk */
#define re_interpreter_in_chunkdone(self)       ((size_t)((self)->ri_in_ptr - (self)->ri_in_cbase))      /* Bytes already processed from current chunk */
#define re_interpreter_in_chunkleft(self)       ((size_t)((self)->ri_in_cend - (self)->ri_in_ptr))       /* Bytes left to read from current chunk */
#define re_interpreter_in_chunkbase(self)       ((self)->ri_in_cbase)                                    /* Current chunk base pointer */
#define re_interpreter_in_chunkend(self)        ((self)->ri_in_cend)                                     /* Current chunk end pointer */
#define re_interpreter_in_chunksize(self)       ((size_t)((self)->ri_in_cend - (self)->ri_in_cbase))     /* Total size of current chunk */
#define re_interpreter_in_chunkoffset(self)     ((size_t)((self)->ri_in_cbase - (self)->ri_in_vbase))    /* Offset of the currently loaded chunk */
#define re_interpreter_in_chunkendoffset(self)  ((size_t)((self)->ri_in_cend - (self)->ri_in_vbase))     /* Offset at the end of the currently loaded chunk */
#define re_interpreter_in_curoffset(self)       ((size_t)((self)->ri_in_ptr - (self)->ri_in_vbase))      /* Current offset from start of initial chunk */
#define re_interpreter_in_totalleft(self)       (re_interpreter_in_chunkleft(self) + (self)->ri_in_mcnt) /* Total # of bytes of input left */
#define re_interpreter_in_totalleftX(self)      (re_interpreter_in_totalleft(self) + (self)->ri_exec->rx_extra)

#define re_interpreter_is_soi(self)  ((self)->ri_in_ptr == (self)->ri_in_vbase) /* Must compare `==' in case `ri_in_vbase' had an underflow (`<' w/o underflow would already be an illegal state!) */
#define re_interpreter_is_eoi(self)  ((self)->ri_in_ptr >= (self)->ri_in_cend && (self)->ri_in_mcnt <= 0)
#define re_interpreter_is_eoiX(self) ((self)->ri_in_ptr >= (self)->ri_in_cend && (self)->ri_in_mcnt <= 0 && (self)->ri_exec->rx_extra <= 0)

#define re_interpreter_is_eoi_at_end_of_chunk(self) ((self)->ri_in_mcnt <= 0)

static_assert(offsetof(struct re_interpreter_inptr, ri_in_ptr) == offsetof(struct re_interpreter_inptr, ri_in_ptr));
static_assert(offsetof(struct re_interpreter_inptr, ri_in_cend) == offsetof(struct re_interpreter_inptr, ri_in_cend));
static_assert(offsetof(struct re_interpreter_inptr, ri_in_cbase) == offsetof(struct re_interpreter_inptr, ri_in_cbase));
static_assert(offsetof(struct re_interpreter_inptr, ri_in_vbase) == offsetof(struct re_interpreter_inptr, ri_in_vbase));
static_assert(offsetof(struct re_interpreter_inptr, ri_in_miov) == offsetof(struct re_interpreter_inptr, ri_in_miov));
static_assert(offsetof(struct re_interpreter_inptr, ri_in_mcnt) == offsetof(struct re_interpreter_inptr, ri_in_mcnt));

/* Load the next chunk into `self' */
#define re_interpreter_nextchunk(self) \
	re_interpreter_inptr_nextchunk(&(self)->ri_in)
PRIVATE NONNULL((1)) void
NOTHROW_NCX(CC re_interpreter_inptr_nextchunk)(struct re_interpreter_inptr *__restrict self) {
	struct iovec nextchunk;
	size_t old_chunk_endoffset;
	/* vvv This wouldn't account for `struct re_exec::rx_extra'! */
	/*assertf(self->ri_in_mcnt != 0, "No further chunks can be loaded");*/
	old_chunk_endoffset = re_interpreter_in_chunkendoffset(self);
	do {
		nextchunk = *self->ri_in_miov++;
	} while (nextchunk.iov_len == 0); /* Skip over empty chunks */
	if (nextchunk.iov_len > self->ri_in_mcnt)
		nextchunk.iov_len = self->ri_in_mcnt;
	self->ri_in_mcnt -= nextchunk.iov_len;
	self->ri_in_ptr   = (byte_t const *)nextchunk.iov_base;
	self->ri_in_cend  = (byte_t const *)nextchunk.iov_base + nextchunk.iov_len;
	self->ri_in_cbase = (byte_t const *)nextchunk.iov_base;
	self->ri_in_vbase = (byte_t const *)nextchunk.iov_base - old_chunk_endoffset;
}

/* Load the previous chunk into `self' */
#define re_interpreter_prevchunk(self) \
	re_interpreter_inptr_prevchunk(&(self)->ri_in)
PRIVATE NONNULL((1)) void
NOTHROW_NCX(CC re_interpreter_inptr_prevchunk)(struct re_interpreter_inptr *__restrict self) {
	struct iovec prevchunk;
	size_t old_chunk_startoffset;
	size_t new_chunk_startoffset;
	old_chunk_startoffset = re_interpreter_in_chunkoffset(self);
	self->ri_in_mcnt += re_interpreter_in_chunksize(self);
	do {
		prevchunk = self->ri_in_miov[-2]; /* [-1] would be the current chunk... */
		--self->ri_in_miov;
	} while (prevchunk.iov_len == 0); /* Skip over empty chunks */
	new_chunk_startoffset = old_chunk_startoffset - prevchunk.iov_len;
	self->ri_in_ptr   = (byte_t const *)prevchunk.iov_base + prevchunk.iov_len;
	self->ri_in_cend  = (byte_t const *)prevchunk.iov_base + prevchunk.iov_len;
	self->ri_in_cbase = (byte_t const *)prevchunk.iov_base;
	self->ri_in_vbase = (byte_t const *)prevchunk.iov_base - new_chunk_startoffset;
}

#define re_interpreter_advance(self, num_bytes) \
	re_interpreter_inptr_advance(&(self)->ri_in, num_bytes)
PRIVATE NONNULL((1)) void
NOTHROW_NCX(CC re_interpreter_inptr_advance)(struct re_interpreter_inptr *__restrict self,
                                             size_t num_bytes) {
again:
	if likely(num_bytes <= re_interpreter_in_chunkleft(self)) {
		self->ri_in_ptr += num_bytes;
	} else {
		num_bytes -= re_interpreter_in_chunkleft(self);
		re_interpreter_inptr_nextchunk(self);
		goto again;
	}
}

#define re_interpreter_reverse(self, num_bytes) \
	re_interpreter_inptr_reverse(&(self)->ri_in, num_bytes)
PRIVATE NONNULL((1)) void
NOTHROW_NCX(CC re_interpreter_inptr_reverse)(struct re_interpreter_inptr *__restrict self,
                                             size_t num_bytes) {
again:
	if likely(num_bytes <= re_interpreter_in_chunkdone(self)) {
		self->ri_in_ptr -= num_bytes;
	} else {
		num_bytes -= re_interpreter_in_chunkdone(self);
		re_interpreter_inptr_prevchunk(self);
		goto again;
	}
}


/* Return the previous byte from input */
#define re_interpreter_prevbyte(self) \
	(likely(re_interpreter_in_chunk_canungetc(self)) ? (self)->ri_in_ptr[-1] : _re_interpreter_inptr_prevbyte(&(self)->ri_in))
#define re_interpreter_inptr_prevbyte(self) \
	(likely(re_interpreter_in_chunk_canungetc(self)) ? (self)->ri_in_ptr[-1] : _re_interpreter_inptr_prevbyte(self))
PRIVATE WUNUSED NONNULL((1)) byte_t
NOTHROW_NCX(CC _re_interpreter_inptr_prevbyte)(struct re_interpreter_inptr const *__restrict self) {
	struct iovec const *iov;
	iov = self->ri_in_miov - 2; /* -1 would be the current chunk */
	while (iov->iov_len == 0)
		--iov; /* Skip over empty chunks */
	return ((byte_t const *)iov->iov_base)[iov->iov_len - 1];
}

/* Return the next byte that will be read from input */
#define re_interpreter_nextbyte(self) \
	(likely(re_interpreter_in_chunk_cangetc(self)) ? *(self)->ri_in_ptr : _re_interpreter_inptr_nextbyte(&(self)->ri_in))
#define re_interpreter_inptr_nextbyte(self) \
	(likely(re_interpreter_in_chunk_cangetc(self)) ? *(self)->ri_in_ptr : _re_interpreter_inptr_nextbyte(self))
PRIVATE WUNUSED NONNULL((1)) byte_t
NOTHROW_NCX(CC _re_interpreter_inptr_nextbyte)(struct re_interpreter_inptr const *__restrict self) {
	struct iovec const *iov;
	/* vvv This wouldn't account for `struct re_exec::rx_extra'! */
	/*assertf(self->ri_in_mcnt != 0, "No further chunks can be loaded");*/
	iov = self->ri_in_miov;
	while (iov->iov_len == 0)
		++iov; /* Skip over empty chunks */
	return *(byte_t const *)iov->iov_base;
}

/* Peek memory that has been read in the past, copying up to `max_bytes' bytes of it into `buf'. */
PRIVATE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC re_interpreter_peekmem_bck)(struct re_interpreter const *__restrict self,
                                           void *buf, size_t max_bytes) {
	size_t avail, result;
	size_t total_prev = re_interpreter_in_curoffset(self);
	byte_t *dst = (byte_t *)buf + max_bytes;
	if (max_bytes > total_prev)
		max_bytes = total_prev;
	result = max_bytes;
	avail  = re_interpreter_in_chunkdone(self);
	if (avail > max_bytes)
		avail = max_bytes;
	dst -= avail;
	max_bytes -= avail;
	memcpy(dst, self->ri_in_ptr, avail);
	if (max_bytes) {
		struct iovec const *iov = self->ri_in_miov - 2; /* -1 would be the current chunk */
		do {
			avail = iov->iov_len;
			if (avail > max_bytes)
				avail = max_bytes;
			dst -= avail;
			memcpy(dst, (byte_t *)iov->iov_base + iov->iov_len - avail, avail);
			max_bytes -= avail;
			++iov;
		} while (max_bytes);
	}
	if (dst > (byte_t *)buf)
		memmovedown(dst, buf, max_bytes);
	return result;
}

/* Peek memory that will be read in the future, copying up to `max_bytes' bytes of it into `buf'.
 * NOTE: This function also allows access to trailing `rx_extra' extra bytes. */
PRIVATE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC re_interpreter_peekmem_fwd)(struct re_interpreter const *__restrict self,
                                           void *buf, size_t max_bytes) {
	size_t avail, result;
	size_t total_left = re_interpreter_in_totalleftX(self);
	if (max_bytes > total_left)
		max_bytes = total_left;
	result = max_bytes;
	avail  = re_interpreter_in_chunkleft(self);
	if (avail > max_bytes)
		avail = max_bytes;
	buf = mempcpy(buf, self->ri_in_ptr, avail);
	max_bytes -= avail;
	if (max_bytes) {
		struct iovec const *iov = self->ri_in_miov;
		do {
			avail = iov->iov_len;
			if (avail > max_bytes)
				avail = max_bytes;
			buf = mempcpy(buf, iov->iov_base, avail);
			max_bytes -= avail;
			++iov;
		} while (max_bytes);
	}
	return result;
}

/* Return the previous utf-8 character from input */
PRIVATE WUNUSED NONNULL((1)) char32_t
NOTHROW_NCX(CC re_interpreter_prevutf8)(struct re_interpreter const *__restrict self) {
	if likely(re_interpreter_in_chunk_canungetc(self)) {
		byte_t prevbyte = self->ri_in_ptr[-1];
		if likely(prevbyte < 0x80)
			return prevbyte;
		if likely((self->ri_in_ptr - UNICODE_UTF8_MAXLEN) <= self->ri_in_cbase) {
			/* Can just read the entire character from the current chunk */
			char const *reader = (char const *)self->ri_in_ptr;
			return unicode_readutf8_rev(&reader);
		}
	}

	if likely(re_interpreter_in_isfirstchunk(self)) {
		/* First chunk -> just read a restricted-length unicode character */
		char const *reader = (char const *)self->ri_in_ptr;
		assert(reader > (char const *)self->ri_in_cbase);
		return unicode_readutf8_rev_n(&reader, (char const *)self->ri_in_cbase);
	}

	/* Fallback: copy memory into a temporary buffer. */
	{
		size_t utf8_len;
		char utf8[UNICODE_UTF8_MAXLEN], *reader;
		utf8_len = re_interpreter_peekmem_bck(self, utf8, sizeof(utf8));
		reader   = utf8 + utf8_len;
		assert(utf8_len != 0);
		return unicode_readutf8_rev_n((char const **)&reader, utf8);
	}
}

/* Return the next utf-8 character that will be read from input */
PRIVATE WUNUSED NONNULL((1)) char32_t
NOTHROW_NCX(CC re_interpreter_nextutf8)(struct re_interpreter const *__restrict self) {
	if likely(re_interpreter_in_chunk_cangetc(self)) {
		uint8_t seqlen;
		byte_t nextbyte = *self->ri_in_ptr;
		if likely(nextbyte < 0x80)
			return nextbyte;
		seqlen = unicode_utf8seqlen[nextbyte];
		if unlikely(!seqlen)
			return nextbyte; /* Dangling follow-up byte? */
		if likely((self->ri_in_ptr + seqlen) <= self->ri_in_cend) {
			/* Can just read the entire character from the current chunk */
			char const *reader = (char const *)self->ri_in_ptr;
			return unicode_readutf8(&reader);
		}
	}

	if likely(re_interpreter_in_islastchunk(self)) {
		/* Last chunk -> just read a restricted-length unicode character */
		char const *reader = (char const *)self->ri_in_ptr;
		assert(reader < (char const *)self->ri_in_cend);
		return unicode_readutf8_n(&reader, (char const *)self->ri_in_cend);
	}

	/* Fallback: copy memory into a temporary buffer. */
	{
		size_t utf8_len;
		char utf8[UNICODE_UTF8_MAXLEN], *reader;
		utf8_len = re_interpreter_peekmem_fwd(self, utf8, sizeof(utf8));
		reader   = utf8;
		assert(utf8_len != 0);
		return unicode_readutf8_n((char const **)&reader, utf8 + utf8_len);
	}
}


/* Read a byte whilst advancing the input pointer. */
#define re_interpreter_readbyte(self)                                                              \
	(unlikely((self)->ri_in_ptr >= (self)->ri_in_cend) ? re_interpreter_nextchunk(self) : (void)0, \
	 *(self)->ri_in_ptr++)
#define re_interpreter_inptr_readbyte(self)                                                              \
	(unlikely((self)->ri_in_ptr >= (self)->ri_in_cend) ? re_interpreter_inptr_nextchunk(self) : (void)0, \
	 *(self)->ri_in_ptr++)

/* Read a utf-8 character whilst advancing the input pointer. */
#define re_interpreter_readutf8(self) re_interpreter_inptr_readutf8(&(self)->ri_in)
PRIVATE WUNUSED NONNULL((1)) char32_t
NOTHROW_NCX(CC re_interpreter_inptr_readutf8)(struct re_interpreter_inptr *__restrict self) {
again:
	if likely(re_interpreter_in_chunk_cangetc(self)) {
		uint8_t seqlen;
		byte_t nextbyte = *self->ri_in_ptr;
		if likely(nextbyte < 0x80) {
			++self->ri_in_ptr;
			return nextbyte;
		}
		seqlen = unicode_utf8seqlen[nextbyte];
		if unlikely(!seqlen) {
			++self->ri_in_ptr;
			return nextbyte; /* Dangling follow-up byte? */
		}
		if likely((self->ri_in_ptr + seqlen) <= self->ri_in_cend) {
			/* Can just read the entire character from the current chunk */
			return unicode_readutf8((char const **)&self->ri_in_ptr);
		}
		if likely(re_interpreter_in_islastchunk(self)) {
			/* Last chunk -> just read a restricted-length unicode character */
			assert((char const *)self->ri_in_ptr < (char const *)self->ri_in_cend);
			return unicode_readutf8_n((char const **)&self->ri_in_ptr, (char const *)self->ri_in_cend);
		}

		/* Unicode character is spread across multiple chunks */
		{
			size_t firstchunk, missing, left;
			char utf8[UNICODE_UTF8_MAXLEN], *dst, *reader;
			firstchunk = re_interpreter_in_chunkleft(self);
			assert(seqlen > firstchunk);
			missing = seqlen - firstchunk;
			dst     = (char *)mempcpy(utf8, self->ri_in_ptr, firstchunk);
			re_interpreter_inptr_nextchunk(self);
			left = re_interpreter_in_totalleft(self);
			if (missing > left)
				missing = left;
			if (missing) {
				for (;;) {
					size_t avail = re_interpreter_in_chunkleft(self);
					if (avail > missing)
						avail = missing;
					dst = (char *)mempcpy(utf8, self->ri_in_ptr, avail);
					missing -= avail;
					self->ri_in_ptr += avail;
					if (!missing)
						break;
					re_interpreter_inptr_nextchunk(self);
				}
			}
			reader = utf8;
			return unicode_readutf8_n((char const **)&reader, dst);
		}
	} else {
		re_interpreter_inptr_nextchunk(self);
		goto again;
	}
}




/* Given an `inptr' that points into some unknown input data chunk,
 * load said chunk and set the input pointer of `self' to  `inptr'.
 *
 * Behavior is undefined when `inptr' isn't a valid input pointer. */
PRIVATE NONNULL((1, 2)) void
NOTHROW_NCX(CC re_interpreter_setinptr)(struct re_interpreter *__restrict self,
                                        byte_t const *inptr) {
	if (re_interpreter_in_chunkcontains(self, inptr)) {
		/* Simple case: don't need to change chunks */
		self->ri_in_ptr = inptr;
	} else {
		/* Complex case: need to find the chunk that `inptr' belongs to.
		 * -> First off: assume that it's from a past chunk. */
		size_t curr_chunk_start_offset = re_interpreter_in_chunkoffset(self);
		size_t prev_chunk_end_offset   = curr_chunk_start_offset;
		struct iovec const *prev_chunk = self->ri_in_miov - 2;
		while (prev_chunk >= self->ri_in_biov) {
			byte_t *prev_chunk_end = (byte_t *)prev_chunk->iov_base + prev_chunk->iov_len;
			if (inptr >= (byte_t *)prev_chunk->iov_base && inptr <= prev_chunk_end) {
				size_t inptr_offset;

				/* Found the chunk that the given inptr belongs to -> now load it! */
				inptr_offset = prev_chunk_end_offset;
				inptr_offset -= prev_chunk->iov_len;
				inptr_offset += (size_t)(inptr - (byte_t *)prev_chunk->iov_base);
				self->ri_in_mcnt += re_interpreter_in_chunkendoffset(self);
				self->ri_in_mcnt -= prev_chunk_end_offset;
				self->ri_in_ptr   = inptr;
				self->ri_in_cend  = prev_chunk_end;
				self->ri_in_cbase = (byte_t *)prev_chunk->iov_base;
				self->ri_in_vbase = inptr - inptr_offset;
				self->ri_in_miov  = prev_chunk + 1;
				return;
			}

			prev_chunk_end_offset -= prev_chunk->iov_len;
			--prev_chunk;
		}

		/* Pointer must be located some a future chunk. Seek until we find it! */
		do {
			re_interpreter_nextchunk(self);
		} while (!re_interpreter_in_chunkcontains(self, inptr));
		self->ri_in_ptr = inptr;
	}
}

/* Set the absolute offset of `self' */
PRIVATE NONNULL((1)) void
NOTHROW_NCX(CC re_interpreter_inptr_setoffset)(struct re_interpreter_inptr *__restrict self,
                                               size_t offset) {
	size_t curr_chunk_start_offset = re_interpreter_in_chunkoffset(self);
	size_t curr_chunk_end_offset   = re_interpreter_in_chunkendoffset(self);
	if (offset >= curr_chunk_start_offset &&
	    offset <= curr_chunk_end_offset) { /* <<< yes: "<=" (in case `offset' points to the end of  the
	                                        *     input buffer, we mustn't load an out-of-bounds chunk) */
		/* Simple case: don't need to change chunks */
		self->ri_in_ptr = self->ri_in_cbase + (offset - curr_chunk_start_offset);
	} else {
		size_t curr_offset = re_interpreter_in_curoffset(self);
		if (offset >= curr_chunk_end_offset) {
			/* Skip ahead */
			assert(offset > curr_offset);
			re_interpreter_inptr_advance(self, offset - curr_offset);
		} else {
			/* Rewind backwards */
			assert(offset < curr_chunk_start_offset);
			assert(offset < curr_offset);
			re_interpreter_inptr_reverse(self, curr_offset - offset);
		}
	}
}



/* Allocate a new regex interpreter */
#define re_interpreter_alloc(nvars) \
	((struct re_interpreter *)alloca(offsetof(struct re_interpreter, ri_vars) + (nvars) * sizeof(byte_t)))

/* Initialize a given regex */
PRIVATE WUNUSED NONNULL((1, 2)) re_errno_t
NOTHROW_NCX(CC re_interpreter_init)(struct re_interpreter *__restrict self,
                                    struct re_exec const *__restrict exec,
                                    size_t nmatch, re_regmatch_t *pmatch) {
	uint8_t ngrp;
	size_t in_len;
	struct iovec const *iov = exec->rx_iov;
	size_t startoff         = exec->rx_startoff;
	size_t endoff           = exec->rx_endoff;
	size_t chunkoff         = 0;
	if unlikely(startoff >= endoff) {
		static struct iovec const empty_iov = { NULL, 0 };
		/* Special case: input buffer is epsilon. */
		startoff = 0;
		endoff   = 0;
		if (exec->rx_extra != 0)
			goto load_normal_iov;
		iov              = &empty_iov;
		self->ri_in_biov = iov;
	} else {
		/* Seek ahead until the first relevant chunk */
load_normal_iov:
		self->ri_in_biov = iov;
		while (startoff >= iov->iov_len) {
			chunkoff += iov->iov_len;
			startoff -= iov->iov_len;
			endoff -= iov->iov_len;
			++iov;
		}
	}

	/* Fill in interpreter fields */
	self->ri_in_ptr   = (byte_t const *)iov->iov_base + startoff;
	in_len            = iov->iov_len - startoff;
	self->ri_in_cend  = self->ri_in_ptr + in_len;
	self->ri_in_vbase = self->ri_in_ptr - (chunkoff + startoff);
	self->ri_in_cbase = (byte_t const *)iov->iov_base;
	self->ri_in_miov  = iov + 1;
	self->ri_in_mcnt  = endoff - startoff;
	if (self->ri_in_mcnt >= in_len) {
		/* More memory may be had from extra chunks */
		self->ri_in_mcnt -= in_len;
	} else {
		/* All relevant memory is located in a single chunk. */
		in_len           = self->ri_in_mcnt;
		self->ri_in_cend = self->ri_in_ptr + in_len;
		self->ri_in_mcnt = 0;
	}
	self->ri_exec   = exec;
	self->ri_pmatch = pmatch;
	ngrp            = exec->rx_code->rc_ngrps;
	if (nmatch >= ngrp) {
		/* Able to use user-provided register buffer. */
	} else {
		/* Need to use our own register buffer. */
		self->ri_pmatch = (re_regmatch_t *)malloc(ngrp, sizeof(re_regmatch_t));
		if unlikely(!self->ri_pmatch)
			return RE_ESPACE;
	}
	/* Set all offsets to UINT_MAX */
	memset(self->ri_pmatch, 0xff, ngrp * sizeof(re_regmatch_t));
	self->ri_onfailv = NULL;
	self->ri_onfailc = 0;
	self->ri_onfaila = 0;
	DBG_memset(self->ri_vars, 0xcc, exec->rx_code->rc_nvars * sizeof(byte_t));
	return RE_NOERROR;
}

PRIVATE NONNULL((1)) void
NOTHROW_NCX(CC re_interpreter_fini)(struct re_interpreter *__restrict self,
                                    size_t nmatch, re_regmatch_t *pmatch) {
	free(self->ri_onfailv);
	if (self->ri_pmatch != pmatch) {
		/* Must copy over match information into user-provided buffer. */
		memcpy(pmatch, self->ri_pmatch, nmatch, sizeof(re_regmatch_t));
		free(self->ri_pmatch);
	}
}

PRIVATE WUNUSED NONNULL((1, 2)) bool
NOTHROW_NCX(CC re_interpreter_pushfail)(struct re_interpreter *__restrict self,
                                        byte_t const *pc) {
	struct re_onfailure_item *item;
	assert(self->ri_onfailc <= self->ri_onfaila);
	if unlikely(self->ri_onfailc >= self->ri_onfaila) {
		struct re_onfailure_item *new_onfail_v;
		size_t new_onfail_a;
		/* Must allocate more space for the on-fail buffer. */
		new_onfail_a = self->ri_onfaila * 2;
		if (new_onfail_a < 16)
			new_onfail_a = 16;
		/* TODO: There should be some upper limit on how many onfail items are  allowed
		 *       before a soft failure should be triggered (similar to the 16K limit on
		 *       regex code size) */
		new_onfail_v = (struct re_onfailure_item *)realloc(self->ri_onfailv, new_onfail_a,
		                                                   sizeof(struct re_onfailure_item));
		if unlikely(!new_onfail_v) {
			new_onfail_a = self->ri_onfailc + 1;
			new_onfail_v = (struct re_onfailure_item *)realloc(self->ri_onfailv, new_onfail_a,
			                                                   sizeof(struct re_onfailure_item));
			if unlikely(!new_onfail_v)
				return false; /* Out-of-memory :( */
		}
		self->ri_onfailv = new_onfail_v;
		self->ri_onfaila = new_onfail_a;
	}
	item = &self->ri_onfailv[self->ri_onfailc++];
	item->rof_in = self->ri_in_ptr;
	item->rof_pc = pc;
	return true;
}

/* Consume a repetition of bytes from `offset...+=num_bytes'
 * - Upon success (repeat was matched), return `true' and leave
 *   the current input pointer of `self' pointing to the end of
 *   the secondary match
 * - Upon failure (repeat wasn't matched), return `false' and
 *   leave the current input pointer of `self' undefined (but
 *   valid)
 * Assumes that `num_bytes != 0' */
PRIVATE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC re_interpreter_consume_repeat)(struct re_interpreter *__restrict self,
                                              re_regoff_t offset, size_t num_bytes) {
	struct re_interpreter_inptr srcptr;
	assert(num_bytes != 0);
	srcptr = self->ri_in;
	re_interpreter_inptr_setoffset(&srcptr, offset);
	for (;;) {
		size_t src_bytes, cur_bytes, com_bytes;
		src_bytes = re_interpreter_in_chunkleft(&srcptr);
		if (!src_bytes) {
			re_interpreter_inptr_nextchunk(&srcptr);
			src_bytes = re_interpreter_in_chunkleft(&srcptr);
		}
		cur_bytes = re_interpreter_in_chunkleft(self);
		if (!cur_bytes) {
			re_interpreter_nextchunk(self);
			cur_bytes = re_interpreter_in_chunkleft(self);
		}
		com_bytes = MIN(src_bytes, cur_bytes, num_bytes);
		assert(com_bytes != 0);
		/* Compare memory */
		if (bcmp(srcptr.ri_in_ptr, self->ri_in_ptr, com_bytes) != 0)
			return false;
		num_bytes -= com_bytes;
		if (!num_bytes)
			break;
		srcptr.ri_in_ptr += com_bytes;
		self->ri_in_ptr += com_bytes;
	}
	return true;
}


/* ASCII character trait flags (s.a. `/kos/kos/include/bits/crt/ctype.h') */
#define CTYPE_C_FLAG_CNTRL  0x01
#define CTYPE_C_FLAG_SPACE  0x02
#define CTYPE_C_FLAG_LOWER  0x04
#define CTYPE_C_FLAG_UPPER  0x08
#define CTYPE_C_FLAG_ALPHA  0x0c
#define CTYPE_C_FLAG_DIGIT  0x10
#define CTYPE_C_FLAG_XDIGIT 0x30
#define CTYPE_C_FLAG_ALNUM  0x1c
#define CTYPE_C_FLAG_PUNCT  0x40
#define CTYPE_C_FLAG_GRAPH  0x5c
#define CTYPE_C_FLAG_PRINT  0xdc


/* Execute the regex interpreter.
 * NOTE: The caller is  responsible for loading  a non-empty  chunk,
 *       unless the entire input buffer is empty. iow: this function
 *       is  allowed to  assume that  the current  chunk being empty
 *       also means that the entire input buffer is empty.
 *
 * @return: -RE_NOERROR: Input was matched.
 * @return: -RE_NOMATCH: Nothing was matched
 * @return: -RE_ESPACE:  Out of memory
 * @return: -RE_ESIZE:   On-failure stack before too large. */
PRIVATE WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC libre_interp_exec)(__register struct re_interpreter *__restrict self) {
	__register byte_t opcode;
	__register byte_t const *pc;

	/* Initialize program counter. */
	{
		struct re_code const *code;
		code = self->ri_exec->rx_code;
		pc   = code->rc_code;

		/* Try to do a quick can-check via the fast-map */
		if (re_interpreter_in_chunk_cangetc(self)) {
			byte_t fmap;
			fmap = *self->ri_in_ptr;
			fmap = code->rc_fmap[fmap];
			if (fmap == 0xff)
				return -RE_NOMATCH;
			pc += fmap;
		} else if (code->rc_minmatch > 0) {
			/* Input buffer is epsilon, but regex has a non-  zero
			 * minimal match length -> regex can't possibly match! */
			return -RE_NOMATCH;
		}
	}

	/* Initialize the best match as not-matched-yet */
	self->ri_bmatch.ri_in_ptr  = (byte_t *)1;
	self->ri_bmatch.ri_in_cend = (byte_t *)0;
#define best_match_isvalid() (self->ri_bmatch.ri_in_ptr <= self->ri_bmatch.ri_in_cend)

	/* Helper macros */
#define DISPATCH()     goto dispatch
#ifdef HAVE_TRACE
#define ONFAIL()       do{ TRACE("ONFAIL: %d\n", __LINE__); goto onfail; }__WHILE0
#define TARGET(opcode) __IF0 { case opcode: TRACE("%#.4Ix: %s\n", (pc - 1) - self->ri_exec->rx_code->rc_code, #opcode); }
#else /* HAVE_TRACE */
#define ONFAIL()       goto onfail
#define TARGET(opcode) case opcode:
#endif /* !HAVE_TRACE */
#define PUSHFAIL(pc)   do { if unlikely(!re_interpreter_pushfail(self, pc)) goto err_nomem; } __WHILE0
#define getb()         (*pc++)
#define getw()         (pc += 2, (int16_t)UNALIGNED_GET16((uint16_t const *)(pc - 2)))

	/* The main dispatch loop */
dispatch:
	opcode = getb();
	switch (opcode) {

		TARGET(REOP_EXACT) {
			byte_t count = getb();
			assert(count >= 2);
			for (;;) {
				size_t avail = re_interpreter_in_chunkleft(self);
				if (avail == 0) {
					if (re_interpreter_is_eoi_at_end_of_chunk(self))
						ONFAIL();
					re_interpreter_nextchunk(self);
					avail = re_interpreter_in_chunkleft(self);
				}
				assert(avail >= 1);
				if likely(avail >= count) {
					/* Everything left to compare is in the current chunk */
					if (bcmp(self->ri_in_ptr, pc, count) != 0)
						ONFAIL();
					self->ri_in_ptr += count;
					pc += count;
					break;
				} else {
					/* Input string spans across multiple chunks */
					if (bcmp(self->ri_in_ptr, pc, avail) != 0)
						ONFAIL();
					self->ri_in_ptr += avail;
					pc += avail;
					count -= avail;
				}
			}
			DISPATCH();
		}

		TARGET(REOP_EXACT_ASCII_ICASE) {
			byte_t count = getb();
			assert(count >= 2);
			for (;;) {
				size_t avail = re_interpreter_in_chunkleft(self);
				if (avail == 0) {
					if (re_interpreter_is_eoi_at_end_of_chunk(self))
						ONFAIL();
					re_interpreter_nextchunk(self);
					avail = re_interpreter_in_chunkleft(self);
				}
				assert(avail >= 1);
				if likely(avail >= count) {
					/* Everything left to compare is in the current chunk */
					if (memcasecmp(self->ri_in_ptr, pc, count) != 0)
						ONFAIL();
					self->ri_in_ptr += count;
					pc += count;
					break;
				} else {
					/* Input string spans across multiple chunks */
					if (memcasecmp(self->ri_in_ptr, pc, avail) != 0)
						ONFAIL();
					self->ri_in_ptr += avail;
					pc += avail;
					count -= avail;
				}
			}
			DISPATCH();
		}

		TARGET(REOP_EXACT_UTF8_ICASE) {
			byte_t count = getb();
			byte_t const *newpc = pc;
			assert(count >= 1);
			do {
				char32_t expected, actual;
				if (re_interpreter_is_eoi(self))
					ONFAIL();
				actual   = re_interpreter_readutf8(self);
				expected = unicode_readutf8((char const **)&newpc);
				if (actual != expected) {
					actual   = unicode_tolower(actual);
					expected = unicode_tolower(expected);
					if (actual != expected)
						ONFAIL();
				}
			} while (--count);
			pc = newpc;
			DISPATCH();
		}

		TARGET(REOP_ANY) {
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			(void)re_interpreter_readbyte(self);
			DISPATCH();
		}

		TARGET(REOP_ANY_NOTLF) {
			byte_t ch;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch = re_interpreter_readbyte(self);
			if (islf(ch))
				ONFAIL();
			DISPATCH();
		}

		TARGET(REOP_ANY_NOTNUL) {
			byte_t ch;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch = re_interpreter_readbyte(self);
			if (ch == '\0')
				ONFAIL();
			DISPATCH();
		}

		TARGET(REOP_ANY_NOTNUL_NOTLF) {
			byte_t ch;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch = re_interpreter_readbyte(self);
			if (ch == '\0' || islf(ch))
				ONFAIL();
			DISPATCH();
		}

		TARGET(REOP_ANY_NOTNUL_NOTLF_UTF8) {
			char32_t ch;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch = re_interpreter_readutf8(self);
			if (ch == '\0' || unicode_islf(ch))
				ONFAIL();
			DISPATCH();
		}

		TARGET(REOP_CHAR) {
			/* Followed by 1 byte that must be matched exactly */
			byte_t ch, b;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			b  = getb();
			ch = re_interpreter_readbyte(self);
			if (ch == b)
				DISPATCH();
			ONFAIL();
		}

		TARGET(REOP_CHAR2) {
			/* Followed by 2 bytes, one of which must be matched exactly (for "[ab]" or "a" -> "[aA]" in ICASE-mode) */
			byte_t ch, b1, b2;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			b1 = getb();
			b2 = getb();
			ch = re_interpreter_readbyte(self);
			if (ch == b1 || ch == b2)
				DISPATCH();
			ONFAIL();
		}

		TARGET(REOP_CONTAINS_UTF8) {
			byte_t count = getb();
			char32_t ch;
			byte_t const *newpc;
			assert(count >= 1);
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch = re_interpreter_readutf8(self);
			newpc = pc;
			for (;;) {
				char32_t other_ch;
				other_ch = unicode_readutf8((char const **)&newpc);
				if (ch == other_ch)
					break;
				if (!--count)
					ONFAIL();
			}
			/* Consume remaining characters */
			for (; count; --count)
				unicode_readutf8((char const **)&newpc);
			pc = newpc;
			DISPATCH();
		}

		TARGET(REOP_CONTAINS_UTF8_NOT) {
			byte_t count = getb();
			char32_t ch;
			byte_t const *newpc;
			assert(count >= 1);
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch = re_interpreter_readutf8(self);
			newpc = pc;
			do {
				char32_t other_ch;
				other_ch = unicode_readutf8((char const **)&newpc);
				if (ch == other_ch)
					ONFAIL();
			} while (--count);
			pc = newpc;
			DISPATCH();
		}

		TARGET(REOP_BITSET) {
			byte_t ch;
			byte_t layout        = getb();
			uint8_t bitset_minch = REOP_BITSET_LAYOUT_GETBASE(layout);
			uint8_t bitset_size  = REOP_BITSET_LAYOUT_GETBYTES(layout);
			uint8_t bitset_bits  = bitset_size * 8;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch = re_interpreter_readbyte(self);
			if (!OVERFLOW_USUB(ch, bitset_minch, &ch)) {
				if (ch < bitset_bits) {
					if ((pc[ch / 8] & (1 << (ch % 8))) != 0) {
						pc += bitset_size;
						DISPATCH();
					}
				}
			}
			ONFAIL();
		}

		TARGET(REOP_BITSET_NOT) {
			byte_t ch;
			byte_t layout        = getb();
			uint8_t bitset_minch = REOP_BITSET_LAYOUT_GETBASE(layout);
			uint8_t bitset_size  = REOP_BITSET_LAYOUT_GETBYTES(layout);
			uint8_t bitset_bits  = bitset_size * 8;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch = re_interpreter_readbyte(self);
			if (!OVERFLOW_USUB(ch, bitset_minch, &ch)) {
				if (ch < bitset_bits) {
					if ((pc[ch / 8] & (1 << (ch % 8))) != 0)
						ONFAIL();
				}
			}
			pc += bitset_size;
			DISPATCH();
		}

		TARGET(REOP_BITSET_UTF8_NOT) {
			char32_t ch;
			byte_t byte_ch;
			byte_t layout        = getb();
			uint8_t bitset_minch = REOP_BITSET_LAYOUT_GETBASE(layout);
			uint8_t bitset_size  = REOP_BITSET_LAYOUT_GETBYTES(layout);
			uint8_t bitset_bits  = bitset_size * 8;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch = re_interpreter_readutf8(self);
			if (ch <= 0xff) { /* `> 0xff' can never be apart of the bitset, which can only describe 00-FF */
				if (!OVERFLOW_USUB((uint8_t)ch, bitset_minch, &byte_ch)) {
					if (ch < bitset_bits) {
						if ((pc[ch / 8] & (1 << (ch % 8))) != 0)
							ONFAIL();
					}
				}
			}
			pc += bitset_size;
			DISPATCH();
		}


		/* Group repetition */
		TARGET(REOP_GROUP_MATCH) {
			uint8_t gid = getb();
			re_regmatch_t match;
			assert(gid < self->ri_exec->rx_code->rc_ngrps);
			match = self->ri_pmatch[gid];
			if (match.rm_so == RE_REGOFF_UNSET ||
			    match.rm_eo == RE_REGOFF_UNSET)
				ONFAIL();
#if 0 /* TODO: This can currently fail because ONFAIL() doesn't roll back group matches... */
			assertf(self->ri_pmatch[gid].rm_so <= self->ri_pmatch[gid].rm_eo,
			        "self->ri_pmatch[%1$I8u].rm_so = %2$Iu\n"
			        "self->ri_pmatch[%1$I8u].rm_eo = %3$Iu",
			        gid, match.rm_so, match.rm_eo);
#endif
			if (match.rm_so < match.rm_eo) {
				if (!re_interpreter_consume_repeat(self, match.rm_so,
				                                   match.rm_eo - match.rm_so))
					ONFAIL();
			}
			DISPATCH();
		}

		TARGET(REOP_GROUP_MATCH_JMIN ... REOP_GROUP_MATCH_JMAX) {
			uint8_t gid = getb();
			re_regmatch_t match;
			assert(gid < self->ri_exec->rx_code->rc_ngrps);
			match = self->ri_pmatch[gid];
			if (match.rm_so == RE_REGOFF_UNSET ||
			    match.rm_eo == RE_REGOFF_UNSET)
				ONFAIL();
#if 0 /* TODO: This can currently fail because ONFAIL() doesn't roll back group matches... */
			assertf(self->ri_pmatch[gid].rm_so <= self->ri_pmatch[gid].rm_eo,
			        "self->ri_pmatch[%1$I8u].rm_so = %2$Iu\n"
			        "self->ri_pmatch[%1$I8u].rm_eo = %3$Iu",
			        gid, match.rm_so, match.rm_eo);
#endif
			if (match.rm_so < match.rm_eo) {
				if (!re_interpreter_consume_repeat(self, match.rm_so,
				                                   match.rm_eo - match.rm_so))
					ONFAIL();
			} else {
				/* Empty group -> do a custom jump-ahead */
				pc += REOP_GROUP_MATCH_Joff(opcode);
			}
			DISPATCH();
		}



		/* Numerical attribute classes */
		TARGET(REOP_ASCII_ISDIGIT_cmp_MIN ... REOP_ASCII_ISDIGIT_cmp_MAX) {
			byte_t ch, digit, operand = getb();
			bool ismatch;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch = re_interpreter_readbyte(self);
			if (!isdigit(ch))
				ONFAIL();
			digit = ch - '0';
			switch (opcode) {
			case REOP_ASCII_ISDIGIT_EQ:
				ismatch = digit == operand;
				break;
			case REOP_ASCII_ISDIGIT_NE:
				ismatch = digit != operand;
				break;
			case REOP_ASCII_ISDIGIT_LO:
				ismatch = digit < operand;
				break;
			case REOP_ASCII_ISDIGIT_LE:
				ismatch = digit <= operand;
				break;
			case REOP_ASCII_ISDIGIT_GR:
				ismatch = digit > operand;
				break;
			case REOP_ASCII_ISDIGIT_GE:
				ismatch = digit >= operand;
				break;
			default: __builtin_unreachable();
			}
			if (ismatch)
				DISPATCH();
			ONFAIL();
		}

		TARGET(REOP_UTF8_ISDIGIT_cmp_MIN ... REOP_UTF8_ISDIGIT_cmp_MAX)
		TARGET(REOP_UTF8_ISNUMERIC_cmp_MIN ... REOP_UTF8_ISNUMERIC_cmp_MAX) {
			char32_t ch;
			uint64_t digit;
			byte_t operand = getb();
			bool ismatch;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch = re_interpreter_readutf8(self);
			if (opcode >= REOP_UTF8_ISDIGIT_cmp_MIN &&
			    opcode <= REOP_UTF8_ISDIGIT_cmp_MAX) {
				if (!unicode_isdigit(ch))
					ONFAIL();
			} else {
				if (!unicode_isnumeric(ch))
					ONFAIL();
			}
			digit = unicode_getnumeric64(ch);
			switch (opcode) {
			case REOP_UTF8_ISDIGIT_EQ:
			case REOP_UTF8_ISNUMERIC_EQ:
				ismatch = digit == operand;
				break;
			case REOP_UTF8_ISDIGIT_NE:
			case REOP_UTF8_ISNUMERIC_NE:
				ismatch = digit != operand;
				break;
			case REOP_UTF8_ISDIGIT_LO:
			case REOP_UTF8_ISNUMERIC_LO:
				ismatch = digit < operand;
				break;
			case REOP_UTF8_ISDIGIT_LE:
			case REOP_UTF8_ISNUMERIC_LE:
				ismatch = digit <= operand;
				break;
			case REOP_UTF8_ISDIGIT_GR:
			case REOP_UTF8_ISNUMERIC_GR:
				ismatch = digit > operand;
				break;
			case REOP_UTF8_ISDIGIT_GE:
			case REOP_UTF8_ISNUMERIC_GE:
				ismatch = digit >= operand;
				break;
			default: __builtin_unreachable();
			}
			if (ismatch)
				DISPATCH();
			ONFAIL();
		}




		/************************************************************************/
		/* ASCII character traits                                               */
		/************************************************************************/
		TARGET(REOP_TRAIT_ASCII_MIN ... REOP_ASCII_ISPRINT_NOT) {
			static_assert(!REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISCNTRL));
			static_assert(REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISCNTRL_NOT));
			static_assert(!REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISSPACE));
			static_assert(REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISSPACE_NOT));
			static_assert(!REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISUPPER));
			static_assert(REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISUPPER_NOT));
			static_assert(!REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISLOWER));
			static_assert(REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISLOWER_NOT));
			static_assert(!REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISALPHA));
			static_assert(REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISALPHA_NOT));
			static_assert(!REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISDIGIT));
			static_assert(REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISDIGIT_NOT));
			static_assert(!REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISXDIGIT));
			static_assert(REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISXDIGIT_NOT));
			static_assert(!REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISALNUM));
			static_assert(REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISALNUM_NOT));
			static_assert(!REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISPUNCT));
			static_assert(REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISPUNCT_NOT));
			static_assert(!REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISGRAPH));
			static_assert(REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISGRAPH_NOT));
			static_assert(!REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISPRINT));
			static_assert(REOP_TRAIT_ASCII_ISNOT(REOP_ASCII_ISPRINT_NOT));
			static byte_t const traits[] = {
#define DEF_TRAIT(opcode, mask) [(opcode - REOP_TRAIT_ASCII_MIN)] = mask
				DEF_TRAIT(REOP_ASCII_ISCNTRL, CTYPE_C_FLAG_CNTRL),      /* `iscntrl(ch) == true' */
				DEF_TRAIT(REOP_ASCII_ISCNTRL_NOT, CTYPE_C_FLAG_CNTRL),  /* `iscntrl(ch) == false' */
				DEF_TRAIT(REOP_ASCII_ISSPACE, CTYPE_C_FLAG_SPACE),      /* `isspace(ch) == true' */
				DEF_TRAIT(REOP_ASCII_ISSPACE_NOT, CTYPE_C_FLAG_SPACE),  /* `isspace(ch) == false' */
				DEF_TRAIT(REOP_ASCII_ISUPPER, CTYPE_C_FLAG_UPPER),      /* `isupper(ch) == true' */
				DEF_TRAIT(REOP_ASCII_ISUPPER_NOT, CTYPE_C_FLAG_UPPER),  /* `isupper(ch) == false' */
				DEF_TRAIT(REOP_ASCII_ISLOWER, CTYPE_C_FLAG_LOWER),      /* `islower(ch) == true' */
				DEF_TRAIT(REOP_ASCII_ISLOWER_NOT, CTYPE_C_FLAG_LOWER),  /* `islower(ch) == false' */
				DEF_TRAIT(REOP_ASCII_ISALPHA, CTYPE_C_FLAG_ALPHA),      /* `isalpha(ch) == true' */
				DEF_TRAIT(REOP_ASCII_ISALPHA_NOT, CTYPE_C_FLAG_ALPHA),  /* `isalpha(ch) == false' */
				DEF_TRAIT(REOP_ASCII_ISDIGIT, CTYPE_C_FLAG_DIGIT),      /* `isdigit(ch) == true' */
				DEF_TRAIT(REOP_ASCII_ISDIGIT_NOT, CTYPE_C_FLAG_DIGIT),  /* `isdigit(ch) == false' */
				DEF_TRAIT(REOP_ASCII_ISXDIGIT, CTYPE_C_FLAG_DIGIT),     /* `isxdigit(ch) == true' */
				DEF_TRAIT(REOP_ASCII_ISXDIGIT_NOT, CTYPE_C_FLAG_DIGIT), /* `isxdigit(ch) == false' */
				DEF_TRAIT(REOP_ASCII_ISALNUM, CTYPE_C_FLAG_ALNUM),      /* `isalnum(ch) == true' */
				DEF_TRAIT(REOP_ASCII_ISALNUM_NOT, CTYPE_C_FLAG_ALNUM),  /* `isalnum(ch) == false' */
				DEF_TRAIT(REOP_ASCII_ISPUNCT, CTYPE_C_FLAG_PUNCT),      /* `ispunct(ch) == true' */
				DEF_TRAIT(REOP_ASCII_ISPUNCT_NOT, CTYPE_C_FLAG_PUNCT),  /* `ispunct(ch) == false' */
				DEF_TRAIT(REOP_ASCII_ISGRAPH, CTYPE_C_FLAG_GRAPH),      /* `isgraph(ch) == true' */
				DEF_TRAIT(REOP_ASCII_ISGRAPH_NOT, CTYPE_C_FLAG_GRAPH),  /* `isgraph(ch) == false' */
				DEF_TRAIT(REOP_ASCII_ISPRINT, CTYPE_C_FLAG_PRINT),      /* `isprint(ch) == true' */
				DEF_TRAIT(REOP_ASCII_ISPRINT_NOT, CTYPE_C_FLAG_PRINT),  /* `isprint(ch) == false' */
#undef DEF_TRAIT
			};
			byte_t ch;
			byte_t ch_flags, trait;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch       = re_interpreter_readbyte(self);
			ch_flags = __ctype_C_flags[ch];
			trait    = traits[opcode - REOP_TRAIT_ASCII_MIN];
			ch_flags &= trait;
			if (REOP_TRAIT_ASCII_ISNOT(opcode)) {
				if (ch_flags == 0)
					DISPATCH();
			} else {
				if (ch_flags != 0)
					DISPATCH();
			}
			ONFAIL();
		}

		TARGET(REOP_ASCII_ISBLANK)
		TARGET(REOP_ASCII_ISBLANK_NOT)
		TARGET(REOP_ASCII_ISSYMSTRT)
		TARGET(REOP_ASCII_ISSYMSTRT_NOT)
		TARGET(REOP_ASCII_ISSYMCONT)
		TARGET(REOP_ASCII_ISSYMCONT_NOT) {
			byte_t ch;
			bool hastrait;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch = re_interpreter_readbyte(self);
			switch (opcode) {
			case REOP_ASCII_ISBLANK:
			case REOP_ASCII_ISBLANK_NOT:
				hastrait = isblank(ch);
				break;
			case REOP_ASCII_ISSYMSTRT:
			case REOP_ASCII_ISSYMSTRT_NOT:
				hastrait = issymstrt(ch);
				break;
			case REOP_ASCII_ISSYMCONT:
			case REOP_ASCII_ISSYMCONT_NOT:
				hastrait = issymcont(ch);
				break;
			default: __builtin_unreachable();
			}
			if (REOP_TRAIT_ASCII_ISNOT(opcode)) {
				if (!hastrait)
					DISPATCH();
			} else {
				if (hastrait)
					DISPATCH();
			}
			ONFAIL();
		}




		/************************************************************************/
		/* Unicode character traits                                             */
		/************************************************************************/
		TARGET(REOP_TRAIT_UTF8_MIN ... REOP_TRAIT_UTF8_MAX) {
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISCNTRL));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISCNTRL_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISSPACE));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISSPACE_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISUPPER));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISUPPER_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISLOWER));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISLOWER_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISALPHA));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISALPHA_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISDIGIT));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISDIGIT_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISXDIGIT));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISXDIGIT_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISALNUM));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISALNUM_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISPUNCT));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISPUNCT_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISGRAPH));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISGRAPH_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISPRINT));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISPRINT_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISBLANK));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISBLANK_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISSYMSTRT));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISSYMSTRT_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISSYMCONT));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISSYMCONT_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISTAB));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISTAB_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISWHITE));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISWHITE_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISEMPTY));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISEMPTY_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISLF));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISLF_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISHEX));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISHEX_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISTITLE));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISTITLE_NOT));
			static_assert(!REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISNUMERIC));
			static_assert(REOP_TRAIT_UTF8_ISNOT(REOP_UTF8_ISNUMERIC_NOT));
			static uint16_t const traits[] = {
#define DEF_TRAIT(opcode, mask) [(opcode - REOP_TRAIT_UTF8_MIN)] = mask
				DEF_TRAIT(REOP_UTF8_ISCNTRL, __UNICODE_ISCNTRL),         /* `unicode_iscntrl(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISCNTRL_NOT, __UNICODE_ISCNTRL),     /* `unicode_iscntrl(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISSPACE, __UNICODE_ISSPACE),         /* `unicode_isspace(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISSPACE_NOT, __UNICODE_ISSPACE),     /* `unicode_isspace(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISUPPER, __UNICODE_ISUPPER),         /* `unicode_isupper(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISUPPER_NOT, __UNICODE_ISUPPER),     /* `unicode_isupper(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISLOWER, __UNICODE_ISLOWER),         /* `unicode_islower(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISLOWER_NOT, __UNICODE_ISLOWER),     /* `unicode_islower(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISALPHA, __UNICODE_ISALPHA),         /* `unicode_isalpha(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISALPHA_NOT, __UNICODE_ISALPHA),     /* `unicode_isalpha(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISDIGIT, __UNICODE_ISDIGIT),         /* `unicode_isdigit(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISDIGIT_NOT, __UNICODE_ISDIGIT),     /* `unicode_isdigit(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISXDIGIT, __UNICODE_ISXDIGIT),       /* `unicode_isxdigit(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISXDIGIT_NOT, __UNICODE_ISXDIGIT),   /* `unicode_isxdigit(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISALNUM, __UNICODE_ISALNUM),         /* `unicode_isalnum(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISALNUM_NOT, __UNICODE_ISALNUM),     /* `unicode_isalnum(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISPUNCT, __UNICODE_ISPUNCT),         /* `unicode_ispunct(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISPUNCT_NOT, __UNICODE_ISPUNCT),     /* `unicode_ispunct(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISGRAPH, __UNICODE_ISGRAPH),         /* `unicode_isgraph(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISGRAPH_NOT, __UNICODE_ISGRAPH),     /* `unicode_isgraph(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISPRINT, __UNICODE_ISPRINT),         /* `unicode_isprint(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISPRINT_NOT, __UNICODE_ISPRINT),     /* `unicode_isprint(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISBLANK, __UNICODE_ISBLANK),         /* `unicode_isblank(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISBLANK_NOT, __UNICODE_ISBLANK),     /* `unicode_isblank(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISSYMSTRT, __UNICODE_ISSYMSTRT),     /* `unicode_issymstrt(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISSYMSTRT_NOT, __UNICODE_ISSYMSTRT), /* `unicode_issymstrt(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISSYMCONT, __UNICODE_ISSYMCONT),     /* `unicode_issymcont(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISSYMCONT_NOT, __UNICODE_ISSYMCONT), /* `unicode_issymcont(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISTAB, __UNICODE_ISTAB),             /* `unicode_istab(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISTAB_NOT, __UNICODE_ISTAB),         /* `unicode_istab(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISWHITE, __UNICODE_ISWHITE),         /* `unicode_iswhite(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISWHITE_NOT, __UNICODE_ISWHITE),     /* `unicode_iswhite(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISEMPTY, __UNICODE_ISEMPTY),         /* `unicode_isempty(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISEMPTY_NOT, __UNICODE_ISEMPTY),     /* `unicode_isempty(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISLF, __UNICODE_ISLF),               /* `unicode_islf(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISLF_NOT, __UNICODE_ISLF),           /* `unicode_islf(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISHEX, __UNICODE_ISHEX),             /* `unicode_ishex(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISHEX_NOT, __UNICODE_ISHEX),         /* `unicode_ishex(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISTITLE, __UNICODE_ISTITLE),         /* `unicode_istitle(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISTITLE_NOT, __UNICODE_ISTITLE),     /* `unicode_istitle(ch) == false' */
				DEF_TRAIT(REOP_UTF8_ISNUMERIC, __UNICODE_ISNUMERIC),     /* `unicode_isnumeric(ch) == true' */
				DEF_TRAIT(REOP_UTF8_ISNUMERIC_NOT, __UNICODE_ISNUMERIC), /* `unicode_isnumeric(ch) == false' */
#undef DEF_TRAIT
			};
			char32_t ch;
			uint16_t ch_flags, trait;
			if (re_interpreter_is_eoi(self))
				ONFAIL();
			ch       = re_interpreter_readutf8(self);
			ch_flags = __unicode_descriptor(ch)->__ut_flags;
			trait    = traits[opcode - REOP_TRAIT_UTF8_MIN];
			ch_flags &= trait;
			if (REOP_TRAIT_UTF8_ISNOT(opcode)) {
				if (ch_flags == 0)
					DISPATCH();
			} else {
				if (ch_flags != 0)
					DISPATCH();
			}
			ONFAIL();
		}




		/************************************************************************/
		/* Opcodes for asserting the current position in input (these don't consume anything) */
		/************************************************************************/
		TARGET(REOP_AT_SOI) {
			/* Start-of-input */
			if (!re_interpreter_is_soi(self))
				ONFAIL();
			DISPATCH();
		}

		TARGET(REOP_AT_EOI) {
			/* End-of-input */
			if (!re_interpreter_is_eoi(self))
				ONFAIL();
			DISPATCH();
		}

		TARGET(REOP_AT_SOL) {
			/* Start-of-line (following a line-feed, or `REOP_AT_SOI' unless `RE_EXEC_NOTBOL' was set) */
			if (re_interpreter_is_soi(self)) {
				if (!(self->ri_exec->rx_eflags & RE_EXEC_NOTBOL))
					DISPATCH();
			} else {
				byte_t prevbyte;
				prevbyte = re_interpreter_prevbyte(self);
				if (islf(prevbyte))
					DISPATCH();
			}
			ONFAIL();
		}

		TARGET(REOP_AT_SOL_UTF8) {
			/* Start-of-line (following a line-feed, or `REOP_AT_SOI' unless `RE_EXEC_NOTBOL' was set) */
			if (re_interpreter_is_soi(self)) {
				if (!(self->ri_exec->rx_eflags & RE_EXEC_NOTBOL))
					DISPATCH();
			} else {
				char32_t prevchar;
				prevchar = re_interpreter_prevutf8(self);
				if (unicode_islf(prevchar))
					DISPATCH();
			}
			ONFAIL();
		}

		TARGET(REOP_AT_EOL) {
			/* End-of-line (preceding a line-feed, or `REOP_AT_EOI' unless `RE_EXEC_NOTEOL' was set) */
			if (re_interpreter_is_eoiX(self)) {
				if (!(self->ri_exec->rx_eflags & RE_EXEC_NOTEOL))
					DISPATCH();
			} else {
				byte_t nextbyte;
				nextbyte = re_interpreter_nextbyte(self);
				if (islf(nextbyte))
					DISPATCH();
			}
			ONFAIL();
		}

		TARGET(REOP_AT_EOL_UTF8) {
			/* End-of-line (preceding a line-feed, or `REOP_AT_EOI' unless `RE_EXEC_NOTEOL' was set) */
			if (re_interpreter_is_eoiX(self)) {
				if (!(self->ri_exec->rx_eflags & RE_EXEC_NOTEOL))
					DISPATCH();
			} else {
				char32_t nextchar;
				nextchar = re_interpreter_nextutf8(self);
				if (unicode_islf(nextchar))
					DISPATCH();
			}
			ONFAIL();
		}

		TARGET(REOP_AT_WOB)     /* WOrdBoundary (preceding and next character have non-equal `issymcont(ch)'; OOB counts as `issymcont == false') */
		TARGET(REOP_AT_WOB_NOT) /* NOT WOrdBoundary (preceding and next character have equal `issymcont(ch)'; OOB counts as `issymcont == false') */
		TARGET(REOP_AT_SOW)     /* StartOfWord (preceding and next character are `!issymcont(lhs) && issymcont(rhs)'; OOB counts as `issymcont == false') */
		TARGET(REOP_AT_EOW)     /* EndOfWord (preceding and next character are `issymcont(lhs) && !issymcont(rhs)'; OOB counts as `issymcont == false') */
		{
			bool previs = re_interpreter_is_soi(self) ? false : !!issymcont(re_interpreter_prevbyte(self));
			bool nextis = re_interpreter_is_eoiX(self) ? false : !!issymcont(re_interpreter_nextbyte(self));
			bool ismatch;
			switch (opcode) {
			case REOP_AT_WOB:
				ismatch = previs == nextis;
				break;
			case REOP_AT_WOB_NOT:
				ismatch = previs != nextis;
				break;
			case REOP_AT_SOW:
				ismatch = !previs && nextis;
				break;
			case REOP_AT_EOW:
				ismatch = previs && !nextis;
				break;
			default: __builtin_unreachable();
			}
			if (ismatch)
				DISPATCH();
			ONFAIL();
		}

		TARGET(REOP_AT_WOB_UTF8)     /* WOrdBoundary (preceding and next character have non-equal `issymcont(ch)'; OOB counts as `issymcont == false') */
		TARGET(REOP_AT_WOB_UTF8_NOT) /* NOT WOrdBoundary (preceding and next character have equal `issymcont(ch)'; OOB counts as `issymcont == false') */
		TARGET(REOP_AT_SOW_UTF8)     /* StartOfWord (preceding and next character are `!issymcont(lhs) && issymcont(rhs)'; OOB counts as `issymcont == false') */
		TARGET(REOP_AT_EOW_UTF8)     /* EndOfWord (preceding and next character are `issymcont(lhs) && !issymcont(rhs)'; OOB counts as `issymcont == false') */
		{
			bool previs = re_interpreter_is_soi(self) ? false : !!unicode_issymcont(re_interpreter_prevutf8(self));
			bool nextis = re_interpreter_is_eoiX(self) ? false : !!unicode_issymcont(re_interpreter_nextutf8(self));
			bool ismatch;
			switch (opcode) {
			case REOP_AT_WOB_UTF8:
				ismatch = previs == nextis;
				break;
			case REOP_AT_WOB_UTF8_NOT:
				ismatch = previs != nextis;
				break;
			case REOP_AT_SOW_UTF8:
				ismatch = !previs && nextis;
				break;
			case REOP_AT_EOW_UTF8:
				ismatch = previs && !nextis;
				break;
			default: __builtin_unreachable();
			}
			if (ismatch)
				DISPATCH();
			ONFAIL();
		}

		TARGET(REOP_AT_SOS_UTF8) {
			/* StartOfSymbol (preceding and next character are `!issymcont(lhs) && issymstrt(rhs)'; OOB counts as `issymcont[/strt] == false') */
			bool previs = re_interpreter_is_soi(self) ? false : !!unicode_issymcont(re_interpreter_prevutf8(self));
			bool nextis = re_interpreter_is_eoiX(self) ? false : !!unicode_issymstrt(re_interpreter_nextutf8(self));
			if (!previs && nextis)
				DISPATCH();
			ONFAIL();
		}




		/************************************************************************/
		/* Opcodes for expression logic and processing.                         */
		/************************************************************************/
		TARGET(REOP_GROUP_START) {
			uint8_t gid = getb();
			assert(gid < self->ri_exec->rx_code->rc_ngrps);
			/* Set start-of-group offset */
			self->ri_pmatch[gid].rm_so = re_interpreter_in_curoffset(self);
			DISPATCH();
		}

		TARGET(REOP_GROUP_END) {
			uint8_t gid = getb();
			assert(gid < self->ri_exec->rx_code->rc_ngrps);
			/* Set end-of-group offset */
			self->ri_pmatch[gid].rm_eo = re_interpreter_in_curoffset(self);
			DISPATCH();
		}

		TARGET(REOP_GROUP_END_JMIN ... REOP_GROUP_END_JMAX) {
			uint8_t gid = getb();
			assert(gid < self->ri_exec->rx_code->rc_ngrps);
			/* Set end-of-group offset */
			self->ri_pmatch[gid].rm_eo = re_interpreter_in_curoffset(self);
#if 0 /* TODO: This can currently fail because ONFAIL() doesn't roll back group matches... */
			assertf(self->ri_pmatch[gid].rm_so <= self->ri_pmatch[gid].rm_eo,
			        "self->ri_pmatch[%1$I8u].rm_so = %2$Iu\n"
			        "self->ri_pmatch[%1$I8u].rm_eo = %3$Iu",
			        gid,
			        (size_t)self->ri_pmatch[gid].rm_so,
			        (size_t)self->ri_pmatch[gid].rm_eo);
#endif
			if (self->ri_pmatch[gid].rm_so >= self->ri_pmatch[gid].rm_eo) {
				/* Group matched epsilon -> must skip ahead a little bit */
				pc += REOP_GROUP_END_Joff(opcode);
			}
			DISPATCH();
		}

		TARGET(REOP_JMP_ONFAIL) {
			int16_t delta = getw();
			PUSHFAIL(pc + delta);
			DISPATCH();
		}

		TARGET(REOP_JMP) {
			int16_t delta = getw();
			pc += delta;
			DISPATCH();
		}

		TARGET(REOP_JMP_AND_RETURN_ONFAIL) {
			int16_t delta = getw();
			PUSHFAIL(pc);
			pc += delta;
			DISPATCH();
		}

		TARGET(REOP_DEC_JMP) {
			uint8_t varid = getb();
			int16_t delta = getw();
			assert(varid < self->ri_exec->rx_code->rc_nvars);
			if (self->ri_vars[varid] != 0) {
				--self->ri_vars[varid];
				pc += delta;
				DISPATCH();
			}
			DISPATCH();
		}

		TARGET(REOP_DEC_JMP_AND_RETURN_ONFAIL) {
			uint8_t varid = getb();
			int16_t delta = getw();
			assert(varid < self->ri_exec->rx_code->rc_nvars);
			if (self->ri_vars[varid] != 0) {
				--self->ri_vars[varid];
				PUSHFAIL(pc);
				pc += delta;
				DISPATCH();
			}
			DISPATCH();
		}

		TARGET(REOP_SETVAR) {
			uint8_t varid = getb();
			uint8_t value = getb();
			assert(varid < self->ri_exec->rx_code->rc_nvars);
			/* Assign value to variable */
			self->ri_vars[varid] = value;
			DISPATCH();
		}

		TARGET(REOP_NOP) {
			DISPATCH();
		}

		TARGET(REOP_MATCHED) {
			/* Compare with a previous match. */
			if (self->ri_onfailc != 0) {
				/* Check if our current match is the best it can get. */
				if (re_interpreter_is_eoi(&self->ri_in)) {
					/* No need to keep going! -- It can't get any better than this. */
					return -RE_NOERROR;
				}

				/* Still have to roll back in order test more code-paths
				 * -> In  this case,  check if  the current  match is better
				 *    than the previous best match, and replace the previous
				 *    one if the new one is better. */
				if (!best_match_isvalid() || (re_interpreter_in_curoffset(self) >
				                              re_interpreter_in_curoffset(&self->ri_bmatch)))
					self->ri_bmatch = self->ri_in;
				ONFAIL();
			}

			/* No more on-fail branches
			 * -> check  if the current match is better than the best. If
			 *    it isn't, then restore the best match before returning. */
			if (best_match_isvalid() && (re_interpreter_in_curoffset(&self->ri_bmatch) >
			                             re_interpreter_in_curoffset(self))) {
return_best_match:
				self->ri_in = self->ri_bmatch;
			}
			/* Fallthru to the PERFECT_MATCH opcode */
			return -RE_NOERROR;
		}

		TARGET(REOP_MATCHED_PERFECT) {
			/* Just indicate success for the current match! */
			return -RE_NOERROR;
		}

	default:
		__builtin_unreachable();
		break;
	}
	__builtin_unreachable();
	{
		struct re_onfailure_item *item;
onfail:
		if (self->ri_onfailc <= 0) {
			/* If there was a match, then return it. */
			if (best_match_isvalid())
				goto return_best_match;
			return -RE_NOMATCH;
		}
		item = &self->ri_onfailv[--self->ri_onfailc];
		pc   = item->rof_pc;
		re_interpreter_setinptr(self, item->rof_in);
		/* TODO: The ONFAIL-system needs some way to set group match start/end addresses back to UNSET:
		 * >> "(f(o)o|foobar)" MATCH "foobar"
		 * This should result in an UNSET match for group[1], but that isn't the case in our current impl!
		 */
		DISPATCH();
	}
err_nomem:
	return -RE_ESPACE;
#undef PUSHFAIL
#undef TARGET
#undef ONFAIL
#undef DISPATCH
#undef getw
#undef getb
}


/* Execute a regular expression.
 * @param: nmatch: # of elements to fill in `pmatch'
 * @param: pmatch: Offsets of matched groups (up to the first `nmatch' groups
 *                 are written, but only on success; iow: when `return >= 0')
 *                 Offsets written INCLUDE `exec->rx_startoff'
 * @return: >= 0:        The # of bytes starting at `exec->rx_startoff' that got matched.
 * @return: -RE_NOMATCH: Nothing was matched
 * @return: -RE_ESPACE:  Out of memory
 * @return: -RE_ESIZE:   On-failure stack before too large. */
INTERN WUNUSED NONNULL((1)) ssize_t
NOTHROW_NCX(CC libre_exec_match)(struct re_exec const *__restrict exec,
                                 size_t nmatch, re_regmatch_t *pmatch) {
	ssize_t result;
	re_errno_t error;
	struct re_interpreter *interp;
	/* Setup */
	interp = re_interpreter_alloc(exec->rx_code->rc_nvars);
	error  = re_interpreter_init(interp, exec, nmatch, pmatch);
	if unlikely(error != 0)
		goto err;
	/* Execute */
	result = libre_interp_exec(interp);
	if (result == -RE_NOERROR)
		result = re_interpreter_in_curoffset(interp) - exec->rx_startoff;
	re_interpreter_fini(interp, nmatch, pmatch);
	return result;
err:
	return -error;
}


/* Similar to `re_exec_match', try to match pattern  against the given input buffer. Do  this
 * with increasing offsets for the first `search_range' bytes, meaning at most `search_range'
 * regex matches will be performed.
 * @param: search_range: One plus the max starting  byte offset (from `exec->rx_startoff')  to
 *                       check. Too great values for `search_range' are automatically clamped.
 * @param: nmatch: # of elements to fill in `pmatch'
 * @param: pmatch: Offsets of matched groups (up to the first `nmatch' groups
 *                 are written, but only on success; iow: when `return >= 0')
 *                 Offsets written INCLUDE `exec->rx_startoff'
 * @param: p_match_size: When non-NULL, store the # of bytes that were here on success
 *                       This would have been  the return value of  `re_exec_match()'.
 * @return: >= 0:        The offset where the matched area starts (`< exec->rx_startoff + search_range').
 * @return: -RE_NOMATCH: Nothing was matched
 * @return: -RE_ESPACE:  Out of memory
 * @return: -RE_ESIZE:   On-failure stack before too large. */
INTERN WUNUSED NONNULL((1)) ssize_t
NOTHROW_NCX(CC libre_exec_search)(struct re_exec const *__restrict exec, size_t search_range,
                                  size_t nmatch, re_regmatch_t *pmatch, size_t *p_match_size) {
	ssize_t result;
	re_errno_t error;
	struct re_interpreter *interp;
	struct re_interpreter_inptr used_inptr;
	size_t match_offset, total_left, min_match;
	total_left = exec->rx_endoff - exec->rx_startoff;
	min_match  = exec->rx_code->rc_minmatch;
	if (OVERFLOW_USUB(total_left, min_match, &total_left))
		return -RE_NOMATCH; /* Buffer is to small to ever match */

	/* Clamp the max possible search area */
	if (search_range > total_left)
		search_range = total_left;
	if unlikely(!search_range)
		return -RE_NOMATCH; /* Not supposed to do any searches? -- OK then... */

	/* Setup */
	interp = re_interpreter_alloc(exec->rx_code->rc_nvars);
	error  = re_interpreter_init(interp, exec, nmatch, pmatch);
	if unlikely(error != 0)
		goto err;

	/* Do the search-loop */
	used_inptr   = interp->ri_in;
	match_offset = exec->rx_startoff;
	for (;;) {
		result = libre_interp_exec(interp);
		if (result != -RE_NOMATCH) {
			/* Set success result values if we didn't get here due to an error. */
			if likely(result == -RE_NOERROR) {
				if (p_match_size != NULL)
					*p_match_size = re_interpreter_in_curoffset(interp) - exec->rx_startoff;
				result = (ssize_t)match_offset;
			}
			break;
		}
		--search_range;
		if (search_range == 0)
			break;
		++match_offset;
		re_interpreter_inptr_in_advance1(&used_inptr);
		interp->ri_in = used_inptr;
	}

	/* Cleanup */
	re_interpreter_fini(interp, nmatch, pmatch);
	return result;
err:
	return -error;
}

/* Same as `re_exec_search()', but perform searching with starting
 * offsets in  `[exec->rx_endoff - search_range, exec->rx_endoff)'
 * Too  great values for `search_range' are automatically clamped.
 * The return value will thus also be within that same range. */
INTERN WUNUSED NONNULL((1)) ssize_t
NOTHROW_NCX(CC libre_exec_rsearch)(struct re_exec const *__restrict exec, size_t search_range,
                                   size_t nmatch, re_regmatch_t *pmatch, size_t *p_match_size) {
	ssize_t result;
	re_errno_t error;
	struct re_interpreter *interp;
	struct re_interpreter_inptr used_inptr;
	size_t match_offset, total_left, min_match;
	total_left = exec->rx_endoff - exec->rx_startoff;
	min_match  = exec->rx_code->rc_minmatch;
	if (OVERFLOW_USUB(total_left, min_match, &total_left))
		return -RE_NOMATCH; /* Buffer is to small to ever match */

	/* Clamp the max possible search area */
	if (search_range > total_left)
		search_range = total_left;
	if unlikely(!search_range)
		return -RE_NOMATCH; /* Not supposed to do any searches? -- OK then... */

	/* Setup */
	interp = re_interpreter_alloc(exec->rx_code->rc_nvars);
	error  = re_interpreter_init(interp, exec, nmatch, pmatch);
	if unlikely(error != 0)
		goto err;

	/* Do the search-loop */
	re_interpreter_inptr_advance(&interp->ri_in, total_left);
	used_inptr   = interp->ri_in;
	match_offset = total_left;
	for (;;) {
		result = libre_interp_exec(interp);
		if (result != -RE_NOMATCH) {
			/* Set success result values if we didn't get here due to an error. */
			if likely(result == -RE_NOERROR) {
				if (p_match_size != NULL)
					*p_match_size = re_interpreter_in_curoffset(interp) - exec->rx_startoff;
				result = (ssize_t)match_offset;
			}
			break;
		}
		--search_range;
		if (search_range == 0)
			break;
		--match_offset;
		re_interpreter_inptr_in_reverse1(&used_inptr);
		interp->ri_in = used_inptr;
	}

	/* Cleanup */
	re_interpreter_fini(interp, nmatch, pmatch);
	return result;
err:
	return -error;
}



/* Exports */
DEFINE_PUBLIC_ALIAS(re_exec_match, libre_exec_match);
DEFINE_PUBLIC_ALIAS(re_exec_search, libre_exec_search);
DEFINE_PUBLIC_ALIAS(re_exec_rsearch, libre_exec_rsearch);

DECL_END

#endif /* !GUARD_LIBREGEX_REGEXEC_C */
