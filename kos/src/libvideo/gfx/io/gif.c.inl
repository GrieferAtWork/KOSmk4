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
#ifndef GUARD_LIBVIDEO_GFX_IO_GIF_C_INL
#define GUARD_LIBVIDEO_GFX_IO_GIF_C_INL 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>
#include <sys/mman.h>
#include <sys/syslog.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h> /* EOF */
#include <string.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/anim.h>
#include <libvideo/gfx/buffer.h>
/**/

#include "../io-utils.h"
#include "../ram-buffer.h"

DECL_BEGIN

/* Based on information found here: https://en.wikipedia.org/wiki/GIF
 * Also somewhat derived from SDL-image,  but not enough to point  at
 * anything  and  say "Hey! I've seen that one"  (because  I re-wrote
 * everything myself) */
#define GET_LE16(p) (((p)[0]) | ((p)[1] << 8))

struct ATTR_PACKED GIF_header {
	byte_t gh_magic[6];
	byte_t gh_lscr_width[2];    /* "Logical screen" width */
	byte_t gh_lscr_height[2];   /* "Logical screen" height */
	byte_t gh_ctrl;             /* Control  byte:  use  "2 << (gh_ctrl & 0x07)"  as  default  size  for  palettes;
	                             * Control byte: mask "0x80" indicates presence of global GCT (global color table) */
	byte_t gh_lscr_background;  /* "Logical screen" background (ignored) */
	byte_t gh_lscr_aspectratio; /* "Logical screen" aspect ratio (ignored) */
	/* Global color (if present) is here */
};

struct ATTR_PACKED GIF_FRAME_header {
	byte_t gfh_magic[1]; /* "," */
	byte_t gfh_x[2];     /* X offset */
	byte_t gfh_y[2];     /* Y offset */
	byte_t gfh_w[2];     /* Width */
	byte_t gfh_h[2];     /* Height */
	byte_t gfh_ctrl;     /* Control   byte:  use  "2 << (gh_ctrl & 0x07)"  as  size  for  palette;
	                      * Control byte: mask "0x80" indicates presence of local CT (color table)
	                      * Control byte: mask "0x40" indicates use of interlacing */
};

/* GIF disposal effects */
#define GIF_DISPOSE_NA                 0 /* No disposal specified */
#define GIF_DISPOSE_NONE               1 /* Do not dispose */
#define GIF_DISPOSE_RESTORE_BACKGROUND 2 /* Restore to background */
#define GIF_DISPOSE_RESTORE_PREVIOUS   3 /* Restore to previous */

struct gif_config {
	video_pixel_t gc_trans;   /* Color key for transparency */
	byte_t        gc_dispose; /* Disposal effect (one of `GIF_DISPOSE_*') */
	uint16_t      gc_delay;   /* Delay time between frames (in 1/100th seconds) default is 10 */
};

PRIVATE NONNULL((1, 2)) void CC
gif_config_populate_showfor(struct gif_config *__restrict self,
                            struct video_anim_frameinfo *__restrict info) {
	if (self->gc_delay < 2) {
		info->vafi_showfor.tv_sec  = 0;
		info->vafi_showfor.tv_usec = 100000; /* 1/10'th of a second */
	} else {
		info->vafi_showfor.tv_sec  = (self->gc_delay / 100);
		info->vafi_showfor.tv_usec = (self->gc_delay % 100) * 10000;
	}
}


/* Call after reading the '!' used to start a gif "extension" block
 * @return: * :   New read pointer
 * @return: NULL: gif file is corrupted */
PRIVATE WUNUSED NONNULL((1, 2)) byte_t const *CC
gif_config_parse_extension(struct gif_config *__restrict self,
                           byte_t const *reader, byte_t const *eof) {
	byte_t id  = *reader++;
	byte_t len = *reader++;
	if ((reader + len) >= eof)
		goto fail;
	switch (id) {

	case 0xf9: /* Graphic Control Extension */
		if (len < 4)
			break;
		self->gc_dispose = (reader[0] >> 2) & 0x7;
		self->gc_delay   = GET_LE16(reader + 1);
		if (reader[0] & 1) {
			self->gc_trans = reader[3];
		}
		break;

	default: break;
	}
	while (len) {
		reader += len;
		len = *reader++;
		if ((reader + len) >= eof)
			goto fail;
	}
	return reader;
fail:
	return NULL;
}


/************************************************************************/
/* GIF LWZ DECOMPRESSER                                                 */
/************************************************************************/
typedef uint_fast16_t lwz_code_t;
typedef uint_least16_t lwz_scode_t;
#define LWZ_EOF       ((lwz_code_t)-1)
#define LWZ_MAX_BITS  12
#define LWZ_MAX_CODES (1 << LWZ_MAX_BITS)
#define LWZ_NULL_CODE ((lwz_code_t)0xffff)

typedef struct {
	/* Code size configs */
	uint_fast8_t   lwz_min_codesize; /* Minimum code size (first byte of the stream) */
	uint_fast8_t   lwz_codesize;     /* [>= lwz_min_code_size + 1] Current code size */
	lwz_code_t     lwz_clearcode;    /* Clear code value (resets the decompresser) */
	lwz_code_t     lwz_eofcode;      /* EOF code (causes decompression to halt) */
	lwz_code_t     lwz_nextcode;     /* The next available code for the dictionary (starts after EOI) */
	lwz_code_t     lwz_codecount;    /* # of codes for the current code size (aka. first invalid code) */

	/* Decompression dicts */
	lwz_scode_t    lwz_prefix[LWZ_MAX_CODES]; /* Code prefix map */
	byte_t         lwz_suffix[LWZ_MAX_CODES]; /* Code suffix map */
	byte_t         lwz_stack[LWZ_MAX_CODES];  /* [0..lwz_stacksize] Temp. buffer for decompressed data */
	uint_fast16_t  lwz_stacksize;             /* Length of `lwz_stack' */

	/* Decompression state */
	lwz_code_t     lwz_prevcode;  /* Last-read code */
	byte_t         lwz_firstbyte; /* First byte of decompressed data (for repeats) */
	shift_t        lwz_bitoff;    /* Bit-offset into `lwz_blockptr' for next byte to read */

	/* I/O state */
	byte_t const  *lwz_eof;        /* [const] Hard EOF pointer */
	byte_t const  *lwz_reader;     /* [<= lwz_eof] To to start of next block yet-to-be processed */
	byte_t const  *lwz_blockptr;   /* [<= lwz_reader] Next byte in the current block to be read */

	bool lwz_empty_block_encountered; /* True if an empty block was encountered */
} LWZ_state;


/* Load next block of GIF image data */
PRIVATE WUNUSED NONNULL((1)) bool CC
_LWZ_load_next_block(LWZ_state *self) {
	byte_t size;

	/* After an empty block was encountered, there will be no more data */
	if (self->lwz_empty_block_encountered)
		return false;

	/* Check for hard EOF */
	if unlikely(self->lwz_reader >= self->lwz_eof)
		return false;

	/* Read size of next block */
	size = *self->lwz_reader++;
	if (size == 0) {
		self->lwz_empty_block_encountered = true;
		return false;
	}

	/* Set-up pointer for processing the block, but
	 * enforce  the hard EOF of the memory mapping. */
	self->lwz_blockptr = self->lwz_reader;
	self->lwz_reader += size;
	if unlikely(self->lwz_reader > self->lwz_eof)
		self->lwz_reader = self->lwz_eof;
	return true;
}

/* Read the next couple of bits from the compressed
 * stream as a code,  which is then returned.  Upon
 * some sort of EOF, return "LWZ_EOF" instead. */
PRIVATE WUNUSED NONNULL((1)) lwz_code_t CC
_LWZ_read_code(LWZ_state *__restrict self) {
	lwz_code_t code = 0;
	shift_t read_bits = 0;
	do {
		byte_t byte, bit;

		/* Check for EOF */
		if (self->lwz_blockptr >= self->lwz_reader) {
			if (!_LWZ_load_next_block(self))
				return LWZ_EOF;
		}

		/* Read 1 bit */
		byte = *self->lwz_blockptr;
		bit  = (byte >> self->lwz_bitoff) & 1;

		/* Add bit to result */
		code |= bit << read_bits;
		++read_bits;
		++self->lwz_bitoff;

		/* Move to next byte if need be */
		if (self->lwz_bitoff >= 8) {
			++self->lwz_blockptr;
			self->lwz_bitoff = 0;
		}
	} while (read_bits < self->lwz_codesize);
	return code;
}

/* Initialize the LWZ decompresser
 * @return: 0 : Success
 * @return: -1: Corrupted stream (`errno' was already modified) */
PRIVATE WUNUSED NONNULL((1, 2, 3)) int CC
LWZ_state_init(LWZ_state *self, byte_t const *data, byte_t const *eof) {
	lwz_code_t i;

	/* Ensure that we're not already at EOF */
	if unlikely(data >= eof)
		goto fail;

	/* Read code size config byte */
	self->lwz_min_codesize = *data;
	if unlikely(self->lwz_min_codesize > LWZ_MAX_BITS)
		goto fail;

	/* Initialize code controls based on "lwz_min_codesize" */
	self->lwz_clearcode = 1 << self->lwz_min_codesize;
	self->lwz_eofcode   = self->lwz_clearcode + 1;
	self->lwz_nextcode  = self->lwz_eofcode + 1;
	self->lwz_codesize  = self->lwz_min_codesize + 1;
	self->lwz_codecount = 1 << self->lwz_codesize;

	/* Initialize dicts. */
	for (i = 0; i < self->lwz_clearcode; ++i) {
		self->lwz_prefix[i] = LWZ_NULL_CODE;
		self->lwz_suffix[i] = (byte_t)i;
	}

	/* First block starts after the "lwz_min_codesize" byte */
	self->lwz_reader    = data + 1;
	self->lwz_eof       = eof;
	self->lwz_stacksize = 0;
	self->lwz_prevcode  = LWZ_EOF;
	self->lwz_firstbyte = 0;
	self->lwz_bitoff    = 0;
	self->lwz_empty_block_encountered = false;

	/* Load the first block */
	if unlikely(!_LWZ_load_next_block(self))
		goto fail;
	return 0;
fail:
	errno = EINVAL;
	return -1;
}

/* Read next decompressed byte, or return "EOF" once all have been read.
 * In  the later case,  `self->lwz_reader' will point  at the first byte
 * that comes after the end of the compressed block-stream. */
PRIVATE WUNUSED NONNULL((1)) int CC
LWZ_state_getc(LWZ_state *__restrict self) {
#define stack_push(v)                                               \
	do {                                                            \
		if (self->lwz_stacksize >= COMPILER_LENOF(self->lwz_stack)) \
			return EOF;                                             \
		self->lwz_stack[self->lwz_stacksize++] = (v);               \
	}	__WHILE0
	while (self->lwz_stacksize == 0) {
		lwz_code_t adj_code, code = _LWZ_read_code(self);
		if (code == LWZ_EOF)
			return EOF;
		if (code == self->lwz_clearcode) {
			self->lwz_codesize  = self->lwz_min_codesize + 1;
			self->lwz_nextcode  = self->lwz_eofcode + 1;
			self->lwz_codecount = 1 << self->lwz_codesize;
			self->lwz_prevcode  = LWZ_EOF;
			continue;
		}
		if (code == self->lwz_eofcode) { /* EOF code encountered */
			/* Skip any additional blocks that might be there */
			while (_LWZ_load_next_block(self))
				;
			return EOF;
		}
		if (self->lwz_prevcode == LWZ_EOF) {
			stack_push(self->lwz_suffix[code]);
			self->lwz_prevcode  = code;
			self->lwz_firstbyte = self->lwz_suffix[code];
			break;
		}
		adj_code = code;
		if (adj_code >= self->lwz_nextcode) {
			stack_push(self->lwz_firstbyte);
			adj_code = self->lwz_prevcode;
		}
		while (adj_code >= self->lwz_clearcode && self->lwz_prefix[adj_code] != LWZ_NULL_CODE) {
			stack_push(self->lwz_suffix[adj_code]);
			adj_code = self->lwz_prefix[adj_code];
		}
		self->lwz_firstbyte = self->lwz_suffix[adj_code];
		stack_push(self->lwz_firstbyte);
		if (self->lwz_nextcode < LWZ_MAX_CODES) {
			self->lwz_prefix[self->lwz_nextcode] = self->lwz_prevcode;
			self->lwz_suffix[self->lwz_nextcode] = self->lwz_firstbyte;
			++self->lwz_nextcode;
			if (self->lwz_nextcode >= self->lwz_codecount && self->lwz_codesize < LWZ_MAX_BITS) {
				++self->lwz_codesize;
				self->lwz_codecount = 1 << self->lwz_codesize;
			}
		}
		self->lwz_prevcode = code;
	}
	return self->lwz_stack[--self->lwz_stacksize];
#undef stack_push
}


struct gif_anim;
struct gif_buffer: video_rambuffer {
	struct gif_config gb_cfg;      /* [const] Default config */
	byte_t           *gb_scratch;  /* [0..1][owned] Scratch buffer for doing frame I/O */
	byte_t           *gb_restore;  /* [0..1][owned] Pointer to video at start of frame when `gb_cfg.gc_dispose == GIF_DISPOSE_RESTORE_PREVIOUS' */
	byte_t const     *gb_reader;   /* [1..1] Pointer at ';' if last frame rendered, or ',' if there is more */
	byte_t const     *gb_lct;      /* [0..gb_lct_len] Currently used local color table */
	unsigned int      gb_lct_len;  /* Length of the currently used local color table */
	LWZ_state         gb_lzw;      /* LZW reader used to decompress frame data */
	video_color_t     gb_colorkey; /* Forced color-key, or "0" if not needed */
	bool gb_encountered_GIF_DISPOSE_RESTORE_PREVIOUS; /* True if "GIF_DISPOSE_RESTORE_PREVIOUS" was encountered */
};

PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
gifbuffer_initgfx__with_colorkey(struct video_gfx *__restrict self) {
	struct gif_buffer *me = (struct gif_buffer *)self->vx_buffer;
	self->vx_colorkey = me->gb_colorkey;
	return rambuffer_initgfx(self);
}

PRIVATE NONNULL((1)) void FCC
gifbuffer_destroy(struct video_buffer *__restrict self) {
	struct gif_buffer *me = (struct gif_buffer *)self;
	free(me->gb_scratch);
	free(me->gb_restore);
	rambuffer_destroy(me);
}

#undef gifbuffer_ops
PRIVATE struct video_buffer_ops gifbuffer_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _gifbuffer_ops(void) {
	if unlikely(!gifbuffer_ops.vi_destroy) {
		video_buffer_ops_set_LOCKOPS_like_RAMBUFFER(&gifbuffer_ops);
		video_buffer_ops_set_GFXOPS_like_RAMBUFFER(&gifbuffer_ops);
		COMPILER_WRITE_BARRIER();
		gifbuffer_ops.vi_destroy = &gifbuffer_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &gifbuffer_ops;
}
#define gifbuffer_ops (*_gifbuffer_ops())

#undef gifbuffer_ops__with_color_key
PRIVATE struct video_buffer_ops gifbuffer_ops__with_color_key = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _gifbuffer_ops__with_color_key(void) {
	if unlikely(!gifbuffer_ops__with_color_key.vi_destroy) {
		video_buffer_ops_set_LOCKOPS_like_RAMBUFFER(&gifbuffer_ops__with_color_key);
		gifbuffer_ops__with_color_key.vi_initgfx    = &gifbuffer_initgfx__with_colorkey;
		gifbuffer_ops__with_color_key.vi_updategfx  = &rambuffer_updategfx;
		gifbuffer_ops__with_color_key.vi_noblendgfx = &rambuffer_noblend;
		COMPILER_WRITE_BARRIER();
		gifbuffer_ops__with_color_key.vi_destroy = &gifbuffer_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &gifbuffer_ops__with_color_key;
}
#define gifbuffer_ops__with_color_key (*_gifbuffer_ops__with_color_key())


struct gif_anim: video_anim {
	struct mapfile            ga_file;    /* [const][owned] Memory-mapping for the gif file */
	byte_t const             *ga_gct;     /* [0..ga_gct_len][const] Global color table */
	unsigned int              ga_gct_len; /* [const] Global color table length */
	byte_t const             *ga_frame1;  /* [1..1][const] Points after the ',' of the first frame */
	byte_t const             *ga_eof;     /* [1..1][const] to the end of the GIF file (== ga_file.mf_addr + ga_file.mf_size) */
	struct gif_config         ga_cfg;     /* [const] Default config */
	bool ga_no_GIF_DISPOSE_RESTORE_PREVIOUS; /* True if "GIF_DISPOSE_RESTORE_PREVIOUS" never appears */
	uint_fast8_t ga_frame1_global_trans;  /* One of `GIF_ANIM_FRAME1_GLOBAL_TRANS__*' */
#define GIF_ANIM_FRAME1_GLOBAL_TRANS__UNKNOWN 0 /* Unknown state */
#define GIF_ANIM_FRAME1_GLOBAL_TRANS__YES     1 /* First frame **does** have pixels matching `gc_trans' */
#define GIF_ANIM_FRAME1_GLOBAL_TRANS__NO      2 /* First frame **doesn't** have pixels matching `gc_trans' */
};

PRIVATE NONNULL((1)) void CC
gif_anim_destroy(struct video_anim *__restrict self) {
	struct gif_anim *me = (struct gif_anim *)self;
	(void)unmapfile(&me->ga_file);
	free(me);
}

/* @param: ctrl_byte: `struct GIF_FRAME_header::gfh_ctrl'
 * @return: * :   New reader pointer
 * @return: NULL: I/O error (corrupt data; `errno' was modified) */
PRIVATE WUNUSED NONNULL((1, 2, 6, 7)) byte_t const *CC
gif_read_frame(struct gif_buffer *__restrict self,
               byte_t *__restrict dst, size_t dst_stride,
               uint16_t w, uint16_t h,
               byte_t const *reader, byte_t const *eof,
               byte_t ctrl_byte, video_pixel_t trans) {
	int byte;
	LWZ_state *lwz = &self->gb_lzw;

	/* Initialize LWZ reader */
	if unlikely(LWZ_state_init(lwz, reader, eof))
		goto fail;

	/* Read pixel data and populate "dst" buffer */
	if unlikely(w <= 0 ||h <= 0)
		goto done_read_remainder;

	if (trans <= 0xff) {
		if (ctrl_byte & 0x40) {
			uint16_t x, y;
			/* Interlaced... */
			for (y = 0; y < h; y += 8) { /* L0 */
				byte_t *line = dst + y * dst_stride;
				for (x = 0; x < w; ++x) {
					byte = LWZ_state_getc(lwz);
					if unlikely(byte == EOF)
						goto done;
					if (byte != (byte_t)trans)
						*line = (byte_t)byte;
					++line;
				}
			}
			for (y = 4; y < h; y += 8) { /* L4 */
				byte_t *line = dst + y * dst_stride;
				for (x = 0; x < w; ++x) {
					byte = LWZ_state_getc(lwz);
					if unlikely(byte == EOF)
						goto done;
					if (byte != (byte_t)trans)
						*line = (byte_t)byte;
					++line;
				}
			}
			for (y = 2; y < h; y += 4) { /* L2+6 */
				byte_t *line = dst + y * dst_stride;
				for (x = 0; x < w; ++x) {
					byte = LWZ_state_getc(lwz);
					if unlikely(byte == EOF)
						goto done;
					if (byte != (byte_t)trans)
						*line = (byte_t)byte;
					++line;
				}
			}
			for (y = 1; y < h; y += 2) { /* L1+3+5+7 */
				byte_t *line = dst + y * dst_stride;
				for (x = 0; x < w; ++x) {
					byte = LWZ_state_getc(lwz);
					if unlikely(byte == EOF)
						goto done;
					if (byte != (byte_t)trans)
						*line = (byte_t)byte;
					++line;
				}
			}
		} else {
			/* Non-interlaced... */
			byte_t *img_end = dst + dst_stride * h;
			if (dst_stride == w) {
				do {
					byte = LWZ_state_getc(lwz);
					if unlikely(byte == EOF)
						goto done;
					if (byte != (byte_t)trans)
						*dst = (byte_t)byte;
				} while (++dst < img_end);
			} else {
				uint16_t y = 0;
				do {
					byte_t *line = dst + dst_stride * y;
					byte_t *line_end = line + w;
					do {
						byte = LWZ_state_getc(lwz);
						if unlikely(byte == EOF)
							goto done;
						if (byte != (byte_t)trans)
							*line = (byte_t)byte;
					} while (++line < line_end);
				} while (++y < h);
			}
		}
	} else {
		if (ctrl_byte & 0x40) {
			uint16_t x, y;
			/* Interlaced... */
			for (y = 0; y < h; y += 8) { /* L0 */
				byte_t *line = dst + y * dst_stride;
				for (x = 0; x < w; ++x) {
					byte = LWZ_state_getc(lwz);
					if unlikely(byte == EOF)
						goto done;
					*line++ = (byte_t)byte;
				}
			}
			for (y = 4; y < h; y += 8) { /* L4 */
				byte_t *line = dst + y * dst_stride;
				for (x = 0; x < w; ++x) {
					byte = LWZ_state_getc(lwz);
					if unlikely(byte == EOF)
						goto done;
					*line++ = (byte_t)byte;
				}
			}
			for (y = 2; y < h; y += 4) { /* L2+6 */
				byte_t *line = dst + y * dst_stride;
				for (x = 0; x < w; ++x) {
					byte = LWZ_state_getc(lwz);
					if unlikely(byte == EOF)
						goto done;
					*line++ = (byte_t)byte;
				}
			}
			for (y = 1; y < h; y += 2) { /* L1+3+5+7 */
				byte_t *line = dst + y * dst_stride;
				for (x = 0; x < w; ++x) {
					byte = LWZ_state_getc(lwz);
					if unlikely(byte == EOF)
						goto done;
					*line++ = (byte_t)byte;
				}
			}
		} else {
			/* Non-interlaced... */
			byte_t *img_end = dst + dst_stride * h;
			if (dst_stride == w) {
				do {
					byte = LWZ_state_getc(lwz);
					if unlikely(byte == EOF)
						goto done;
					*dst++ = (byte_t)byte;
				} while (dst < img_end);
			} else {
				uint16_t y = 0;
				do {
					byte_t *line = dst + dst_stride * y;
					byte_t *line_end = line + w;
					do {
						byte = LWZ_state_getc(lwz);
						if unlikely(byte == EOF)
							goto done;
						*line++ = (byte_t)byte;
					} while (line < line_end);
				} while (++y < h);
			}
		}
	}

	/* Read any remaining data... (there shouldn't be any, but better be safe...) */
	while (byte != EOF) {
done_read_remainder:
		byte = LWZ_state_getc(lwz);
	}
done:
	return lwz->lwz_reader;
fail:
	return NULL;
}

/* Called with "reader" pointing after the ',' of the frame to paint */
PRIVATE WUNUSED NONNULL((1, 2, 3, 4)) byte_t const *CC
gif_anim_paintframe(struct gif_anim const *__restrict anim,
                    struct gif_buffer *__restrict self,
                    byte_t const *reader, byte_t const *eof) {
	byte_t ctrl;
	byte_t const *lct;
	unsigned int lct_len;
	struct video_codec const *codec;
	uint16_t frame_x, frame_y;
	uint16_t frame_w, frame_h;
	video_coord_t frame_endx;
	video_coord_t frame_endy;

	/* Read frame position and dimensions */
	frame_x = GET_LE16(reader + 0); /* struct GIF_FRAME_header::gfh_x */
	frame_y = GET_LE16(reader + 2); /* struct GIF_FRAME_header::gfh_y */
	frame_w = GET_LE16(reader + 4); /* struct GIF_FRAME_header::gfh_w */
	frame_h = GET_LE16(reader + 6); /* struct GIF_FRAME_header::gfh_h */
	reader += 8; /* Point "reader" at `struct GIF_FRAME_header::gfh_ctrl' */

	/* Read frame control byte */
	ctrl = *reader++;
	if (ctrl & 0x80) {
		static_assert((2 << (0xff & 0x07)) <= 256);
		lct_len = 2 << (ctrl & 0x07);
		if ((reader + (lct_len * 3)) >= eof)
			goto fail;
		lct = reader;
		reader += lct_len * 3;
	} else {
		lct     = anim->ga_gct;
		lct_len = anim->ga_gct_len;
		if unlikely(!lct)
			goto fail;
	}

	/* Check if we need to convert from a palette-based output buffer to a direct-color one */
	codec = self->vb_format.vf_codec;
	if ((self->gb_lct != lct) &&
	    (codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL) &&
	    /* When the old frame gets disposed, then we also don't need DCOL mode */
	    (self->gb_cfg.gc_dispose != GIF_DISPOSE_RESTORE_BACKGROUND)) {

		/* Must convert from P8 to RGB888/RGBA8888 */
		byte_t *dcol_buf, *dcol_end, *pal_buf, *pal_iter;
		size_t dcol_stride, dcol_total;
		struct video_palette *pal = self->vb_format.vf_pal;
		assert(pal);

		/* Only the transparency-config of the first frame (i.e. the "gobal transparency")
		 * determines  if the output image itself has transparency. In frames there-after,
		 * transparency only applies when it comes to inter-frame composition.
		 *
		 * As such, the only way for later frames to turn pixels back to transparent is to
		 * use "GIF_DISPOSE_RESTORE_BACKGROUND" to make *all* pixels transparent, and then
		 * proceed to re-paint the entire canvas, or use "GIF_DISPOSE_RESTORE_PREVIOUS" to
		 * restore a previous frame that had transparency at the intended locations. */
		codec = video_codec_lookup(anim->ga_cfg.gc_trans <= 0xff
		                           ? VIDEO_CODEC_RGBA8888
		                           : VIDEO_CODEC_RGB888);
		if unlikely(!codec) {
			errno = ENODEV;
			goto err;
		}

		/* Allocate new buffer for direct-color mode */
		assert(codec->vc_specs.vcs_pxsz == 3 ||
		       codec->vc_specs.vcs_pxsz == 4);
		dcol_stride = self->vb_xdim * codec->vc_specs.vcs_pxsz;
		dcol_total  = dcol_stride * self->vb_ydim;
		dcol_buf = (byte_t *)malloc(dcol_total);
		if unlikely(!dcol_buf)
			goto err;
		pal_buf = self->rb_data;
		self->rb_data   = dcol_buf;
		self->rb_stride = dcol_stride;
		dcol_end = dcol_buf + dcol_total;
		free(self->gb_restore);
		self->gb_restore = NULL;

		/* Convert pixel data */
		pal_iter = pal_buf;
		if (codec->vc_specs.vcs_pxsz == 3) {
			do {
				byte_t pixel = *pal_iter++;
				video_color_t color = pal->vp_pal[pixel];
				*dcol_buf++ = VIDEO_COLOR_GET_RED(color);
				*dcol_buf++ = VIDEO_COLOR_GET_GREEN(color);
				*dcol_buf++ = VIDEO_COLOR_GET_BLUE(color);
			} while (dcol_buf < dcol_end);
		} else {
			do {
				byte_t pixel = *pal_iter++;
				video_color_t color;
				if (pixel == anim->ga_cfg.gc_trans) {
					color = 0;
				} else {
					color = pal->vp_pal[pixel];
				}
				*(uint32_t *)dcol_buf = color;
				dcol_buf += 4;
			} while (dcol_buf < dcol_end);
		}
		self->vb_ops = &gifbuffer_ops; /* Set regular ops (in case color-key was set before) */
		self->vb_format.vf_codec = codec;
		self->vb_format.vf_pal   = NULL;
		video_palette_decref(pal);
		if (malloc_usable_size(pal_buf) > malloc_usable_size(self->gb_scratch)) {
			free(self->gb_scratch);
			self->gb_scratch = pal_buf;
		} else {
			free(pal_buf);
		}
	}

	/* Remember the new (current) LCT as being active */
	self->gb_lct     = lct;
	self->gb_lct_len = lct_len;

	/* Apply dispose effects */
	switch (self->gb_cfg.gc_dispose) {

	case GIF_DISPOSE_RESTORE_BACKGROUND: {
		/* Backup previous frame & clear background for new
		 * frame with  "global transparency" (if  defined). */
		size_t rb_total = self->rb_stride * self->vb_ydim;
		if (anim->ga_cfg.gc_trans != 0 && anim->ga_cfg.gc_trans <= 0xff) {
			if (!anim->ga_no_GIF_DISPOSE_RESTORE_PREVIOUS) {
				if (!self->gb_restore) {
					byte_t *backup = (byte_t *)malloc(rb_total);
					if unlikely(!backup)
						goto err;
					self->gb_restore = self->rb_data;
					self->rb_data    = backup;
				} else {
					byte_t *backup   = self->gb_restore;
					self->gb_restore = self->rb_data;
					self->rb_data    = backup;
				}
			}
			memset(self->rb_data, anim->ga_cfg.gc_trans, rb_total);
		} else if (anim->ga_no_GIF_DISPOSE_RESTORE_PREVIOUS) {
			bzero(self->rb_data, rb_total);
		} else if (!self->gb_restore) {
			byte_t *backup = (byte_t *)calloc(rb_total);
			if unlikely(!backup)
				goto err;
			self->gb_restore = self->rb_data;
			self->rb_data    = backup;
		} else {
			byte_t *backup   = self->gb_restore;
			self->gb_restore = self->rb_data;
			self->rb_data    = backup;
			bzero(backup, rb_total);
		}
	}	break;

	case GIF_DISPOSE_RESTORE_PREVIOUS:
		self->gb_encountered_GIF_DISPOSE_RESTORE_PREVIOUS = true;
		/* Restore previous frame */
		if (self->gb_restore) {
			size_t rb_total = self->rb_stride * self->vb_ydim;
			memcpy(self->rb_data, self->gb_restore, rb_total);
		}
		break;

	default: {
		/* Backup current frame in case "GIF_DISPOSE_RESTORE_PREVIOUS" ever gets  used
		 * Otherwise, don't do anything to the canvas and paint the new frame over-top */
		size_t rb_total;
		if (anim->ga_no_GIF_DISPOSE_RESTORE_PREVIOUS)
			break;
		rb_total = self->rb_stride * self->vb_ydim;
		if (!self->gb_restore) {
			self->gb_restore = (byte_t *)malloc(rb_total);
			if unlikely(!self->gb_restore)
				goto err;
		}
		memcpy(self->gb_restore, self->rb_data, rb_total);
	}	break;

	}

	frame_endx = (video_coord_t)frame_x + frame_w;
	frame_endy = (video_coord_t)frame_y + frame_h;

	/* Check if we can directly render into the frame buffer, or if we have
	 * to  go through the  extra work of using  a temporary scratch buffer. */
	if ((codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL) &&
	    likely(frame_endx <= self->vb_xdim && frame_endy <= self->vb_ydim)) {
		/* Can render directly into the frame buffer (no scratch buffer needed) */
		byte_t *dst;
		dst = self->rb_data + frame_x + frame_y * self->rb_stride;
		reader = gif_read_frame(self, dst, self->rb_stride, frame_w, frame_h,
		                        reader, eof, ctrl, self->gb_cfg.gc_trans);
		if unlikely(!reader)
			goto err;

check_for_global_transparency:
		switch (self->gb_cfg.gc_dispose) {
		case GIF_DISPOSE_RESTORE_BACKGROUND:
			/* When  the background (all-transparent) was restored, there is
			 * always some transparency if the frame doesn't cover the whole
			 * canvas. */
			if (frame_x > 0 || frame_y > 0 || frame_w < self->vb_xdim || frame_h < self->vb_ydim) {
set_has_global_transparency:
				self->gb_colorkey = self->vb_format.vf_pal->vp_pal[anim->ga_cfg.gc_trans];
				self->vb_ops = &gifbuffer_ops__with_color_key;
				break;
			}
			ATTR_FALLTHROUGH
		case GIF_DISPOSE_RESTORE_PREVIOUS:
			/* Check if pixel data contains transparent pixels */
			if (memchr(self->rb_data, anim->ga_cfg.gc_trans,
			           self->rb_stride * self->vb_ydim))
				goto set_has_global_transparency;
			self->vb_ops = &gifbuffer_ops;
			break;
		default: break;
		}
	} else {
		/* Must read into a temporary scratch buffer */
		size_t reqsize, avlsize;
		byte_t const *src;
		byte_t *dst;
		uint16_t x, y;

		/* Make sure there is enough space in the scratch-buffer to hold this frame. */
		reqsize = frame_w * frame_h * 1;
		avlsize = malloc_usable_size(self->gb_scratch);
		if (reqsize > avlsize) {
			byte_t *newbuf = (byte_t *)realloc(self->gb_scratch, reqsize);
			if unlikely(!newbuf)
				goto err;
			self->gb_scratch = newbuf;
		}

		/* Read frame into scratch buffer */
		reader = gif_read_frame(self, self->gb_scratch,
		                        frame_w, frame_w, frame_h,
		                        reader, eof, ctrl, (video_pixel_t)-1);
		if unlikely(!reader)
			goto err;

		/* Force-clamp frame coords to valid coords.
		 * These should never point out-of-bounds, but better be safe than sorry. */
		if unlikely(frame_endx > self->vb_xdim) {
			if (frame_w > self->vb_xdim)
				frame_w = self->vb_xdim;
			frame_x = self->vb_xdim - frame_w;
		}
		if unlikely(frame_endy > self->vb_ydim) {
			if (frame_h > self->vb_ydim)
				frame_h = self->vb_ydim;
			frame_y = self->vb_ydim - frame_h;
		}

		/* Render scratch buffer onto frame and translate palette indices. */
		assert(codec->vc_specs.vcs_pxsz == 1 || /* Palette-based */
		       codec->vc_specs.vcs_pxsz == 3 || /* RGB888 */
		       codec->vc_specs.vcs_pxsz == 4);  /* RGBA8888 */
		src = self->gb_scratch;
		dst = self->rb_data + (frame_x * codec->vc_specs.vcs_pxsz) + (frame_y * self->rb_stride);
		switch (codec->vc_specs.vcs_pxsz) {
		case 1:
			for (y = 0; y < frame_h; ++y) {
				byte_t *line = dst;
				for (x = 0; x < frame_w; ++x) {
					byte_t pixel = *src++;
					if (pixel != self->gb_cfg.gc_trans)
						*line = pixel;
					++line;
				}
				dst += self->rb_stride;
			}
			goto check_for_global_transparency;
		case 3:
			for (y = 0; y < frame_h; ++y) {
				byte_t *line = dst;
				for (x = 0; x < frame_w; ++x) {
					byte_t pixel = *src++;
					if (pixel != self->gb_cfg.gc_trans) {
						uint8_t r, g, b;
						if (pixel >= lct_len) {
							r = g = b = 0;
						} else {
							r = lct[pixel * 3 + 0];
							g = lct[pixel * 3 + 1];
							b = lct[pixel * 3 + 2];
						}
						line[0] = r;
						line[1] = g;
						line[2] = b;
					}
					line += 3;
				}
				dst += self->rb_stride;
			}
			break;
		case 4:
			for (y = 0; y < frame_h; ++y) {
				byte_t *line = dst;
				for (x = 0; x < frame_w; ++x) {
					byte_t pixel = *src++;
					if (pixel != self->gb_cfg.gc_trans) {
						video_color_t color;
						if (pixel >= lct_len) {
							color = 0;
						} else {
							uint8_t r = lct[pixel * 3 + 0];
							uint8_t g = lct[pixel * 3 + 1];
							uint8_t b = lct[pixel * 3 + 2];
							color = VIDEO_COLOR_RGB(r, g, b);
						}
						*(uint32_t *)line = color;
					}
					line += 4;
				}
				dst += self->rb_stride;
			}
			break;
		default: __builtin_unreachable();
		}
	}

	return reader;
fail:
	errno = EINVAL;
err:
	return NULL;
}


PRIVATE WUNUSED ATTR_IN(1) ATTR_OUT(2) REF struct video_buffer *CC
gif_anim_firstframe(struct video_anim const *__restrict self,
                    struct video_anim_frameinfo *__restrict info) {
	struct gif_anim *me = (struct gif_anim *)self;
	REF struct gif_buffer *result;
	byte_t const *reader = me->ga_frame1;
	byte_t const *eof = me->ga_eof;
	struct video_codec const *codec;
	REF struct video_palette *pal;
	byte_t ctrl;
	uint16_t frame_x, frame_y;
	uint16_t frame_w, frame_h;
	video_coord_t frame_endx;
	video_coord_t frame_endy;
	size_t rb_total;

	/* Fill in frame info */
	info->vafi_frameid = 0;
	gif_config_populate_showfor(&me->ga_cfg, info);

	/* Create main animation frame buffer */
	result = (REF struct gif_buffer *)malloc(sizeof(struct gif_buffer));
	if unlikely(!result)
		goto err;
	result->vb_refcnt   = 1;
	result->vb_ops      = &gifbuffer_ops;
	result->vb_xdim     = me->va_xdim;
	result->vb_ydim     = me->va_ydim;
	result->rb_stride   = me->va_xdim * 1;
	result->gb_cfg      = me->ga_cfg;
	result->gb_restore  = NULL;
	result->gb_scratch  = NULL;
	result->gb_lct      = NULL;
	result->gb_lct_len  = 0;
	result->gb_colorkey = 0;
	result->gb_encountered_GIF_DISPOSE_RESTORE_PREVIOUS = false;

	/* Read frame position and dimensions */
	frame_x = GET_LE16(reader + 0); /* struct GIF_FRAME_header::gfh_x */
	frame_y = GET_LE16(reader + 2); /* struct GIF_FRAME_header::gfh_y */
	frame_w = GET_LE16(reader + 4); /* struct GIF_FRAME_header::gfh_w */
	frame_h = GET_LE16(reader + 6); /* struct GIF_FRAME_header::gfh_h */
	reader += 8; /* Point "reader" at `struct GIF_FRAME_header::gfh_ctrl' */

	/* Read frame control byte */
	ctrl = *reader++;
	if (ctrl & 0x80) {
		static_assert((2 << (0xff & 0x07)) <= 256);
		result->gb_lct_len = 2 << (ctrl & 0x07);
		result->gb_lct = reader;
		reader += result->gb_lct_len * 3;
		if (reader >= eof)
			goto fail_r;
	} else {
		result->gb_lct_len = me->ga_gct_len;
		result->gb_lct = me->ga_gct;
		if unlikely(!result->gb_lct_len)
			goto fail_r;
	}

	/* First frame can always be rendered using a palette */
	codec = video_codec_lookup(VIDEO_CODEC_P8);
	if unlikely(!codec) {
		errno = ENODEV;
		goto err_r;
	}
	pal = video_palette_create(256);
	if unlikely(!pal)
		goto err_r;
	{
		video_pixel_t i;
		byte_t const *lct_reader = result->gb_lct;
		for (i = 0; i < result->gb_lct_len; ++i) {
			byte_t r = *lct_reader++;
			byte_t g = *lct_reader++;
			byte_t b = *lct_reader++;
			pal->vp_pal[i] = VIDEO_COLOR_RGB(r, g, b);
			if (i == me->ga_cfg.gc_trans)
				pal->vp_pal[i] = 0;
		}
	}
	result->vb_format.vf_codec = codec;
	result->vb_format.vf_pal   = pal;

	/* Fill with global transparency, or "0" if not defined */
	rb_total = me->va_xdim * 1 * me->va_ydim;
	if (me->ga_cfg.gc_trans <= 0xff && me->ga_cfg.gc_trans != 0) {
		result->rb_data = (byte_t *)malloc(rb_total);
		if unlikely(!result->rb_data)
			goto err_r_pal;
		memset(result->rb_data, me->ga_cfg.gc_trans, rb_total);
	} else {
		result->rb_data = (byte_t *)calloc(rb_total);
		if unlikely(!result->rb_data)
			goto err_r_pal;
	}

	/* Force-clamp frame coords to valid coords.
	 * These should never point out-of-bounds, but better be safe than sorry. */
	frame_endx = (video_coord_t)frame_x + frame_w;
	frame_endy = (video_coord_t)frame_y + frame_h;
	if unlikely(frame_endx > result->vb_xdim) {
		if (frame_w > result->vb_xdim)
			frame_w = result->vb_xdim;
		frame_x = result->vb_xdim - frame_w;
	}
	if unlikely(frame_endy > result->vb_ydim) {
		if (frame_h > result->vb_ydim)
			frame_h = result->vb_ydim;
		frame_y = result->vb_ydim - frame_h;
	}

	/* Read frame into buffer */
	reader = gif_read_frame(result,
	                        result->rb_data + frame_x + frame_y * result->rb_stride,
	                        result->rb_stride, frame_w, frame_h, reader, eof, ctrl,
	                        (video_pixel_t)-1);
	if unlikely(!reader)
		goto err_r_pal_data;

	/* Set-up global color-key for used during GFX (if needed) */
	switch (me->ga_frame1_global_trans) {

	case GIF_ANIM_FRAME1_GLOBAL_TRANS__UNKNOWN: {
		/* Check if frame has "transparent" pixels:
		 * - First frame does not paint whole image -> everything outside is global transparency!
		 * - If pixel data contains a "transparent" pixel, then frame1 also needs global transparency */
		assert(rb_total == me->va_xdim * 1 * me->va_ydim);
		if (frame_x > 0 || frame_y > 0 || frame_w < result->vb_xdim || frame_h < result->vb_ydim ||
		    memchr(result->rb_data, me->ga_cfg.gc_trans, rb_total)) {
			me->ga_frame1_global_trans = GIF_ANIM_FRAME1_GLOBAL_TRANS__YES;
			goto have_global_trans;
		}
		me->ga_frame1_global_trans = GIF_ANIM_FRAME1_GLOBAL_TRANS__NO;
	}	break;

	case GIF_ANIM_FRAME1_GLOBAL_TRANS__YES:
have_global_trans:
		/* Use special operators to force a color key into a GFX context */
		result->gb_colorkey = result->vb_format.vf_pal->vp_pal[me->ga_cfg.gc_trans];
		result->vb_ops = &gifbuffer_ops__with_color_key;
		break;

	case GIF_ANIM_FRAME1_GLOBAL_TRANS__NO:
		break;

	default: __builtin_unreachable();
	}
	result->gb_reader = reader;
	return result;
fail_r:
	errno = EINVAL;
	goto err_r;
err_r_pal_data:
	free(result->gb_restore);
	free(result->rb_data);
err_r_pal:
	video_palette_decref(result->vb_format.vf_pal);
err_r:
	free(result);
err:
	return NULL;
}

PRIVATE WUNUSED ATTR_IN(1) ATTR_INOUT(2) ATTR_INOUT(3) REF struct video_buffer *CC
gif_anim_nextframe(struct video_anim const *__restrict self,
                   /*inherit(on_success)*/ REF struct video_buffer *__restrict buf,
                   struct video_anim_frameinfo *__restrict info) {
	struct gif_anim *me = (struct gif_anim *)self;
	REF struct gif_buffer *result = (REF struct gif_buffer *)buf;
	byte_t const *reader, *eof;
	byte_t ctrl;
#undef gifbuffer_ops
#undef gifbuffer_ops__with_color_key
	assert(result->vb_ops == &gifbuffer_ops ||
	       result->vb_ops == &gifbuffer_ops__with_color_key);
#define gifbuffer_ops (*_gifbuffer_ops())
#define gifbuffer_ops__with_color_key (*_gifbuffer_ops__with_color_key())

	/* Indicate next frame in caller-given "info" */
	++info->vafi_frameid;

	/* Start reading blocks until we hit another frame */
	reader = result->gb_reader;
	eof    = me->ga_eof;
	for (;;) {
		if unlikely(reader >= eof)
			goto rewind;
		ctrl = *reader++;
		if (ctrl == ';')
			goto rewind;
		if (ctrl == '!') {
			reader = gif_config_parse_extension(&result->gb_cfg, reader, eof);
			if unlikely(!reader)
				goto fail;
			continue;
		}
		if (ctrl == ',')
			break; /* Got start of first frame! */
		syslog(LOG_WARN, "[libvideo-gfx][gif] Unexpected block indicator: %#" PRIx8 "\n", ctrl);
	}

	/* Now after ',' of next frame */
	if ((reader + 10) >= eof)
		goto fail;

read_frame_at_header:
	/* Paint the next frame */
	reader = gif_anim_paintframe(me, result, reader, eof);
	if unlikely(!reader)
		goto err;

	/* Fill in frame info */
	gif_config_populate_showfor(&result->gb_cfg, info);
	result->gb_reader = reader;
	return result;
rewind:
	if (!result->gb_encountered_GIF_DISPOSE_RESTORE_PREVIOUS) {
		me->ga_no_GIF_DISPOSE_RESTORE_PREVIOUS = true;
		free(result->gb_restore); /* Will no longer be needed during next iteration... */
		result->gb_restore = NULL;
	}
	if (info->vafi_frameid == 1) {
		/* Tried to render the first frame, but got nothing.
		 * This has to be a single-frame gif file (i.e.  not
		 * animated) */
		info->vafi_frameid         = 0;
		info->vafi_showfor.tv_sec  = 999999;
		info->vafi_showfor.tv_usec = 999999;
		return result;
	}
	info->vafi_frameid = 0;
	result->gb_cfg = me->ga_cfg;
	reader = me->ga_frame1;
	goto read_frame_at_header;
fail:
	errno = EINVAL;
err:
	return NULL;
}



#undef gif_anim_ops
PRIVATE struct video_anim_ops gif_anim_ops = {};
PRIVATE struct video_anim_ops *CC _gif_anim_ops(void) {
	if (!gif_anim_ops.vao_destroy) {
		gif_anim_ops.vao_nextframe  = &gif_anim_nextframe;
		gif_anim_ops.vao_firstframe = &gif_anim_firstframe;
		COMPILER_WRITE_BARRIER();
		gif_anim_ops.vao_destroy = &gif_anim_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &gif_anim_ops;
}
#define gif_anim_ops (*_gif_anim_ops())


/* GIF */
INTERN WUNUSED REF struct video_anim *CC
libvideo_anim_open_gif(void const *blob, size_t blob_size,
                       struct mapfile *p_mapfile) {
	REF struct gif_anim *result;
	struct GIF_header const *header;
	byte_t const *reader, *eof;
	eof    = (byte_t const *)blob + blob_size;
	header = (struct GIF_header const *)blob;
	if (blob_size <= sizeof(struct GIF_header))
		goto fail;
	if (header->gh_magic[0] != 'G')
		goto fail;
	if (header->gh_magic[1] != 'I')
		goto fail;
	if (header->gh_magic[2] != 'F')
		goto fail;
	if (header->gh_magic[3] != '8')
		goto fail;
	if ((header->gh_magic[4] != '7' || header->gh_magic[5] != 'a') &&
	    (header->gh_magic[4] != '9' || header->gh_magic[5] != 'a'))
		goto fail;
	reader = (byte_t const *)header + 13;

	/* Allocate gif buffer */
	result = (REF struct gif_anim *)malloc(sizeof(struct gif_anim));
	if unlikely(!result)
		goto err;

	/* Read global color table */
	result->ga_gct = reader;
	result->ga_gct_len = 0;
	if (header->gh_ctrl & 0x80) {
		unsigned int gct_entries;
		static_assert((2 << (0xff & 0x07)) <= 256);
		gct_entries = 2 << (header->gh_ctrl & 0x07);
		result->ga_gct_len = gct_entries;
		reader += gct_entries * 3;
		if (reader >= eof)
			goto err_r;
	}

	/* Default init config */
	result->ga_cfg.gc_trans   = (video_pixel_t)-1;
	result->ga_cfg.gc_dispose = GIF_DISPOSE_NA;
	result->ga_cfg.gc_delay   = 10;
	result->ga_no_GIF_DISPOSE_RESTORE_PREVIOUS = false;

	/* Read blocks until we hit the first frame */
	for (;;) {
		byte_t ctrl;
		if (reader >= eof)
			goto fail_r;
		ctrl = *reader++;
		if (ctrl == ';')
			goto fail_r; /* EOF-marker before first frame? */
		if (ctrl == '!') {
			reader = gif_config_parse_extension(&result->ga_cfg, reader, eof);
			if unlikely(!reader)
				goto fail_r;
			/* Restoring the previous image at the start would just re-restore the background. */
			if (result->ga_cfg.gc_dispose == GIF_DISPOSE_RESTORE_PREVIOUS)
				result->ga_cfg.gc_dispose = GIF_DISPOSE_RESTORE_BACKGROUND;
			continue;
		}
		if (ctrl == ',')
			break; /* Got start of first frame! */
		syslog(LOG_WARN, "[libvideo-gfx][gif] Unexpected block indicator: %#" PRIx8 "\n", ctrl);
	}

	/* Ensure that there is enough data for the first frame's header */
	if ((reader + 10) >= eof)
		goto fail_r;

	/* Fill in standard fields of "result" */
	result->va_refcnt = 1;
	result->va_ops    = &gif_anim_ops;
	result->va_xdim   = GET_LE16(header->gh_lscr_width);
	result->va_ydim   = GET_LE16(header->gh_lscr_height);
	if (result->va_xdim < ((video_dim_t)GET_LE16(reader + 0) + GET_LE16(reader + 4)))
		result->va_xdim = ((video_dim_t)GET_LE16(reader + 0) + GET_LE16(reader + 4));
	if (result->va_ydim < ((video_dim_t)GET_LE16(reader + 2) + GET_LE16(reader + 6)))
		result->va_ydim = ((video_dim_t)GET_LE16(reader + 2) + GET_LE16(reader + 6));

	/* Fill in "result" */
	if (p_mapfile) {
		result->ga_file = *p_mapfile;
		bzero(p_mapfile, sizeof(*p_mapfile)); /* Steal */
		result->ga_frame1 = reader;
		result->ga_eof    = eof;
	} else {
		uintptr_t frame1_offset;
		byte_t const *copy_base = reader;
		if (result->ga_gct_len)
			copy_base = result->ga_gct;
		frame1_offset = (uintptr_t)(reader - copy_base);
		result->ga_file.mf_size = (size_t)(eof - copy_base);
		result->ga_file.mf_addr = (byte_t *)memdup(copy_base, result->ga_file.mf_size);
		if unlikely(!result->ga_file.mf_addr)
			goto err_r;
		__mapfile_setheap(&result->ga_file);
		result->ga_gct    = result->ga_file.mf_addr;
		result->ga_frame1 = result->ga_file.mf_addr + frame1_offset;
		result->ga_eof    = result->ga_file.mf_addr + result->ga_file.mf_size;
	}

	result->ga_frame1_global_trans = GIF_ANIM_FRAME1_GLOBAL_TRANS__UNKNOWN;
	/* If there is no global transparency, first frame can't possible use it */
	if (result->ga_cfg.gc_trans > 0xff)
		result->ga_frame1_global_trans = GIF_ANIM_FRAME1_GLOBAL_TRANS__NO;
	return result;
err_r:
	free(result);
err:
	return NULL;
fail_r:
	free(result);
fail:
	return VIDEO_ANIM_WRONG_FMT;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_GIF_C_INL */
