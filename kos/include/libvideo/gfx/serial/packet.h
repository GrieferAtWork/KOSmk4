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
#ifndef _LIBVIDEO_GFX_SERIAL_PACKET_H
#define _LIBVIDEO_GFX_SERIAL_PACKET_H 1

#include "../api.h"
/**/

#ifdef LIBVIDEO_GFX_EXPOSE_INTERNALS
#ifdef CONFIG_LIBVIDEO_HAVE_SERIALIZATION
#include <__stdinc.h>

#include <hybrid/typecore.h>
#include <bits/types.h>

#include "../../color.h"
#include "../../types.h"
#include "../serial.h"

#ifdef __CC__
__DECL_BEGIN

/* Generic, server-side ID for a buffer (allowing
 * the buffer to be used as source when blitting) */
typedef union __ATTR_PACKED {
	__UINT64_TYPE__ nbid_qwords[2];
	__UINT32_TYPE__ nbid_dwords[4];
	__UINT16_TYPE__ nbid_words[8];
	__UINT8_TYPE__ nbid_bytes[16];
} netbuf_id_t;

typedef union __ATTR_PACKED {
	__UINT32_TYPE__ nbc_color;
	struct {
		__UINT8_TYPE__ nbc_r;
		__UINT8_TYPE__ nbc_g;
		__UINT8_TYPE__ nbc_b;
		__UINT8_TYPE__ nbc_a;
	} nbc_channels;
} netbuf_color_t;

typedef union __ATTR_PACKED {
	__UINT64_TYPE__ nbc_color;
	struct {
		__le16 nbc_r;
		__le16 nbc_g;
		__le16 nbc_b;
		__le16 nbc_a;
	} nbc_channels;
} netbuf_color64_t;


/* Common header for packets sent by the client */
#define NETBUF_PACKET_HDR \
	__UINT8_TYPE__ nbp_cmd; /* Command code (one of `NETBUF_CMD_*') */
struct __ATTR_PACKED netbuf_packet {
	NETBUF_PACKET_HDR
	__COMPILER_FLEXIBLE_ARRAY(__BYTE_TYPE__, nbp_data); /* Command-specific data */
};

struct __ATTR_PACKED netbuf_cmd {
	NETBUF_PACKET_HDR
};






/* Possible values for `struct netbuf_packet::nbp_cmd' */
#define NETBUF_CMD_GETINFO       0x00 /* [REQ: "struct netbuf_cmd", RESP: "struct netbuf_info" or "struct netbuf_fdinfo"] Get buffer info (and FD, if available). */
#define NETBUF_CMD_GETCODEC      0x01 /* [REQ: "struct netbuf_cmd", RESP: "struct netbuf_codec"] Get extended codec info. Returns empty (`(*vdrio_readpacket)(...) == 0') if codec cannot be serialized */
#define NETBUF_CMD_GETPAL        0x02 /* [REQ: "struct netbuf_cmd", RESP: "struct netbuf_palette"] Get palette colors (palette size can be determined using `NETBUF_CMD_GETCODEC') Returns empty if there is no palette */
#define NETBUF_CMD_COLOR2PIXEL   0x03 /* [REQ: "struct netbuf_cmd_color2pixel", RESP: "struct netbuf_resp_color2pixel"] Convert a color into a pixel */
#define NETBUF_CMD_PIXEL2COLOR   0x04 /* [REQ: "struct netbuf_cmd_pixel2color", RESP: "struct netbuf_resp_pixel2color"] Convert a color into a pixel */
#define NETBUF_CMD_COLOR2PIXEL64 0x05 /* [REQ: "struct netbuf_cmd_color2pixel64", RESP: "struct netbuf_resp_color2pixel64"] Convert a color into a pixel */
#define NETBUF_CMD_PIXEL2COLOR64 0x06 /* [REQ: "struct netbuf_cmd_pixel2color64", RESP: "struct netbuf_resp_pixel2color64"] Convert a color into a pixel */
/* TODO: Commands for GFX operations */


/************************************************************************/
/* NETBUF_CMD_GETINFO                                                   */
/************************************************************************/
struct __ATTR_PACKED netbuf_info {
	netbuf_id_t nbi_id;    /* Buffer ID */
	__le32      nbi_xdim;  /* Buffer X dimension */
	__le32      nbi_ydim;  /* Buffer Y dimension */
	__le32      nbi_flags; /* Buffer GFX flags (set of `VIDEO_GFX_F_*') */
	__le32      nbi_ckey;  /* [valid_if(nbi_flags & VIDEO_GFX_F_COLORKEY)] Buffer color key, or `0' if unused */
	__le16      nbi_codec; /* Buffer codec ID (one of `VIDEO_CODEC_*').
	                        * If  unknown, use "NETBUF_CMD_GETCODEC" to retrieve specs.
	                        * If specs cannot be retrieved, FD cannot be used, a custom
	                        * codec  must be built using "VIDEO_CODEC_CUSTOM" (one that
	                        * has no-op pixel functions  and uses packets to  implement
	                        * pixel<=>color conversion) */
	__le16     _nbi_pad;   /* ... */
};

struct __ATTR_PACKED netbuf_fdinfo {
	struct netbuf_info nbfi_info;   /* Basic buffer info */
	__le32             nbfi_total;  /* s.a. `struct video_buffer_fdinfo::vbfdi_total' */
	__le32             nbfi_stride; /* s.a. `struct video_buffer_fdinfo::vbfdi_stride' */
	__le32             nbfi_bxoff;  /* s.a. `struct video_buffer_fdinfo::vbfdi_bxoff' */
	__le32             nbfi_bxrem;  /* s.a. `struct video_buffer_fdinfo::vbfdi_bxrem' */
	__le32             nbfi_hwops;  /* s.a. `struct video_buffer_fdinfo::vbfdi_hwops' */
	__le32             nbfi_xdim;   /* s.a. `struct video_buffer_fdinfo::vbfdi_xdim' */
	__le32             nbfi_ydim;   /* s.a. `struct video_buffer_fdinfo::vbfdi_ydim' */
	__le32             nbfi_cxoff;  /* s.a. `struct video_buffer_fdinfo::vbfdi_cxoff' (!SIGNED) */
	__le32             nbfi_cyoff;  /* s.a. `struct video_buffer_fdinfo::vbfdi_cyoff' (!SIGNED) */
};


/************************************************************************/
/* NETBUF_CMD_GETCODEC                                                  */
/************************************************************************/
struct __ATTR_PACKED netbuf_codec {
	__UINT8_TYPE__   nbc_flags;  /* s.a. `struct video_codec_specs::vcs_flags' */
	__UINT8_TYPE__   nbc_bpp;    /* s.a. `struct video_codec_specs::vcs_bpp' */
	__UINT8_TYPE__  _nbc_pad[6]; /* ... */
	__le64           nbc_rmask;  /* s.a. `struct video_codec_specs::vcs_rmask' */
	__le64           nbc_gmask;  /* s.a. `struct video_codec_specs::vcs_gmask' */
	__le64           nbc_bmask;  /* s.a. `struct video_codec_specs::vcs_bmask' */
	__le64           nbc_amask;  /* s.a. `struct video_codec_specs::vcs_amask' */
};


/************************************************************************/
/* NETBUF_CMD_GETPAL                                                    */
/************************************************************************/
struct __ATTR_PACKED netbuf_palette {
	netbuf_color_t bp_colors[256]; /* Palette colors (may be more than 256 elements) */
};


/************************************************************************/
/* NETBUF_CMD_COLOR2PIXEL                                               */
/************************************************************************/
struct __ATTR_PACKED netbuf_cmd_color2pixel {
	NETBUF_PACKET_HDR
	__UINT8_TYPE__ _nbc2p_pad[3]; /* ... */
	netbuf_color_t nbc2p_color; /* Color to convert */
};
struct __ATTR_PACKED netbuf_resp_color2pixel {
	__le32 nbrc2p_pixel; /* Converted pixel */
};


/************************************************************************/
/* NETBUF_CMD_PIXEL2COLOR                                               */
/************************************************************************/
struct netbuf_cmd_pixel2color {
	NETBUF_PACKET_HDR
	__UINT8_TYPE__ _nbc2p_pad[3]; /* ... */
	__le32 nbp2c_pixel; /* Pixel to convert */
};
struct netbuf_resp_pixel2color {
	netbuf_color_t nbrp2c_color; /* Converted color */
};


/************************************************************************/
/* NETBUF_CMD_COLOR2PIXEL64                                             */
/************************************************************************/
struct netbuf_cmd_color2pixel64 {
	NETBUF_PACKET_HDR
	__UINT8_TYPE__ _nbc2p_pad[7]; /* ... */
	netbuf_color64_t nbc2p_color; /* Color to convert */
};
struct netbuf_resp_color2pixel64 {
	__le64 nbrc2p_pixel; /* Converted pixel */
};


/************************************************************************/
/* NETBUF_CMD_PIXEL2COLOR64                                             */
/************************************************************************/
struct netbuf_cmd_pixel2color64 {
	NETBUF_PACKET_HDR
	__UINT8_TYPE__ _nbc2p_pad[7]; /* ... */
	__le64 nbp2c_pixel; /* Pixel to convert */
};
struct netbuf_resp_pixel2color64 {
	netbuf_color64_t nbrp2c_color; /* Converted color */
};


__DECL_END
#endif /* __CC__ */
#endif /* CONFIG_LIBVIDEO_HAVE_SERIALIZATION */
#endif /* LIBVIDEO_GFX_EXPOSE_INTERNALS */

#endif /* !_LIBVIDEO_GFX_SERIAL_PACKET_H */
