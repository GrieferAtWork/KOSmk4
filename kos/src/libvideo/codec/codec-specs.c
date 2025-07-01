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
#ifndef GUARD_LIBVIDEO_CODEC_CODEC_SPECS_C
#define GUARD_LIBVIDEO_CODEC_CODEC_SPECS_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include <kos/anno.h>

#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libvideo/codec/codecs.h>

#include "codec-specs.h"
#include "codecs.h"

DECL_BEGIN

/* Same as `video_codec_lookup()', and also only returns built-in codecs, but lookup
 * is  done via `specs', as opposed to the  caller having to provide the codec's ID.
 *
 * NOTE: This function doesn't need `vcs_pxsz' or `vcs_cbits' to be initialized. */
INTERN WUNUSED ATTR_PURE NONNULL((1)) struct video_codec const *CC
libvideo_codec_lookup_specs(struct video_codec_specs const *__restrict specs) {
	video_codec_t codec = VIDEO_CODEC_NONE;
	if (specs->vcs_flags & (VIDEO_CODEC_FLAG_LUM | VIDEO_CODEC_FLAG_PAL)) {
		/* Grayscale (luminance) or palette */
		if (specs->vcs_gmask == specs->vcs_rmask &&
		    specs->vcs_bmask == specs->vcs_rmask) {
			if (specs->vcs_rmask == (((uint32_t)1 << specs->vcs_bpp) - 1) && specs->vcs_amask == 0) {
				/* No alpha channel */
				switch (specs->vcs_bpp) {
				case 1: codec = VIDEO_CODEC_L1_MSB; break;
				case 2: codec = VIDEO_CODEC_L2_MSB; break;
				case 4: codec = VIDEO_CODEC_L4_MSB; break;
				case 8: codec = VIDEO_CODEC_L8; break;
				default: goto nope;
				}
				static_assert((VIDEO_CODEC_L1_MSB + 1) == VIDEO_CODEC_L1_LSB);
				static_assert((VIDEO_CODEC_L2_MSB + 1) == VIDEO_CODEC_L2_LSB);
				static_assert((VIDEO_CODEC_L4_MSB + 1) == VIDEO_CODEC_L4_LSB);
				if (VIDEO_CODEC_FLAG_ISLSB(specs->vcs_flags) && specs->vcs_bpp < 8)
					++codec;
			} else {
				/* With alpha channel */
				switch (specs->vcs_bpp) {

				case 2: {
					if (specs->vcs_rmask == 0x1 && specs->vcs_amask == 0x2) {
						codec = VIDEO_CODEC_LA11_MSB;
					} else if (specs->vcs_rmask == 0x2 && specs->vcs_amask == 0x1) {
						codec = VIDEO_CODEC_AL11_MSB;
					} else {
						goto nope;
					}
					static_assert((VIDEO_CODEC_AL11_MSB + 1) == VIDEO_CODEC_AL11_LSB);
					static_assert((VIDEO_CODEC_LA11_MSB + 1) == VIDEO_CODEC_LA11_LSB);
					if (VIDEO_CODEC_FLAG_ISLSB(specs->vcs_flags))
						++codec;
				}	break;

				case 4: {
					if (specs->vcs_rmask == 0x3 && specs->vcs_amask == 0xc) {
						codec = VIDEO_CODEC_LA22_MSB;
					} else if (specs->vcs_rmask == 0xc && specs->vcs_amask == 0x3) {
						codec = VIDEO_CODEC_AL22_MSB;
					} else if (specs->vcs_rmask == 0x7 && specs->vcs_amask == 0x8) {
						codec = VIDEO_CODEC_LA31_MSB;
					} else if (specs->vcs_rmask == 0xe && specs->vcs_amask == 0x1) {
						codec = VIDEO_CODEC_AL13_MSB;
					} else {
						goto nope;
					}
					static_assert((VIDEO_CODEC_LA22_MSB + 1) == VIDEO_CODEC_LA22_LSB);
					static_assert((VIDEO_CODEC_AL22_MSB + 1) == VIDEO_CODEC_AL22_LSB);
					static_assert((VIDEO_CODEC_LA31_MSB + 1) == VIDEO_CODEC_LA31_LSB);
					static_assert((VIDEO_CODEC_AL13_MSB + 1) == VIDEO_CODEC_AL13_LSB);
					if (VIDEO_CODEC_FLAG_ISLSB(specs->vcs_flags))
						++codec;
				}	break;

				case 8: {
					if (specs->vcs_rmask == 0x0f && specs->vcs_amask == 0xf0) {
						codec = VIDEO_CODEC_LA44;
					} else if (specs->vcs_rmask == 0xf0 && specs->vcs_amask == 0x0f) {
						codec = VIDEO_CODEC_AL44;
					} else if (specs->vcs_rmask == 0x7f && specs->vcs_amask == 0x80) {
						codec = VIDEO_CODEC_LA71;
					} else if (specs->vcs_rmask == 0xfe && specs->vcs_amask == 0x01) {
						codec = VIDEO_CODEC_AL17;
					} else {
						goto nope;
					}
				}	break;

				case 16: {
					if (specs->vcs_rmask == MASK2_LE(0x00ff) && specs->vcs_amask == MASK2_LE(0xff00)) {
						codec = VIDEO_CODEC_LA88;
					} else if (specs->vcs_rmask == MASK2_LE(0xff00) && specs->vcs_amask == MASK2_LE(0x00ff)) {
						codec = VIDEO_CODEC_AL88;
					} else {
						goto nope;
					}
				}	break;

				default: goto nope;
				}
			}
		}
		if (codec != VIDEO_CODEC_NONE && (specs->vcs_flags & VIDEO_CODEC_FLAG_PAL)) {
			/* Convert luminance codec to its palette equivalent */
#define LUM2PAL_OFFSET (VIDEO_CODEC_P1_MSB - VIDEO_CODEC_L1_MSB)
#define LUM2PAL(id)    ((id) + LUM2PAL_OFFSET)
			static_assert(LUM2PAL(VIDEO_CODEC_L1_MSB) == VIDEO_CODEC_P1_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_L1_LSB) == VIDEO_CODEC_P1_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_L2_MSB) == VIDEO_CODEC_P2_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_L2_LSB) == VIDEO_CODEC_P2_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_L4_MSB) == VIDEO_CODEC_P4_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_L4_LSB) == VIDEO_CODEC_P4_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_L8) == VIDEO_CODEC_P8);
			static_assert(LUM2PAL(VIDEO_CODEC_LA11_MSB) == VIDEO_CODEC_PA11_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_LA11_LSB) == VIDEO_CODEC_PA11_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_AL11_MSB) == VIDEO_CODEC_AP11_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_AL11_LSB) == VIDEO_CODEC_AP11_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_LA22_MSB) == VIDEO_CODEC_PA22_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_LA22_LSB) == VIDEO_CODEC_PA22_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_AL22_MSB) == VIDEO_CODEC_AP22_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_AL22_LSB) == VIDEO_CODEC_AP22_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_LA31_MSB) == VIDEO_CODEC_PA31_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_LA31_LSB) == VIDEO_CODEC_PA31_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_AL13_MSB) == VIDEO_CODEC_AP13_MSB);
			static_assert(LUM2PAL(VIDEO_CODEC_AL13_LSB) == VIDEO_CODEC_AP13_LSB);
			static_assert(LUM2PAL(VIDEO_CODEC_LA44) == VIDEO_CODEC_PA44);
			static_assert(LUM2PAL(VIDEO_CODEC_AL44) == VIDEO_CODEC_AP44);
			static_assert(LUM2PAL(VIDEO_CODEC_LA71) == VIDEO_CODEC_PA71);
			static_assert(LUM2PAL(VIDEO_CODEC_AL17) == VIDEO_CODEC_AP17);
			static_assert(LUM2PAL(VIDEO_CODEC_LA88) == VIDEO_CODEC_PA88);
			static_assert(LUM2PAL(VIDEO_CODEC_AL88) == VIDEO_CODEC_AP88);
			codec = LUM2PAL(codec);
#undef LUM2PAL_OFFSET
#undef LUM2PAL
		}
	} else {
#define SET_CODEC(c) do{codec = (c); goto return_codec;}__WHILE0
		switch (specs->vcs_bpp) {
		case 32:
			if (specs->vcs_rmask == MASK4_LE(0x000000ff)) {
				if (specs->vcs_gmask == MASK4_LE(0x0000ff00) &&
				    specs->vcs_bmask == MASK4_LE(0x00ff0000)) {
					if (specs->vcs_amask == MASK4_LE(0xff000000)) {
						SET_CODEC(VIDEO_CODEC_RGBA8888);
					} else if (specs->vcs_amask == 0) {
						SET_CODEC(VIDEO_CODEC_RGBX8888);
					}
				}
			} else if (specs->vcs_amask == MASK4_LE(0x000000ff)) {
				if (specs->vcs_gmask == MASK4_LE(0x00ff0000)) {
					if (specs->vcs_rmask == MASK4_LE(0x0000ff00) &&
					    specs->vcs_bmask == MASK4_LE(0xff000000)) {
						SET_CODEC(VIDEO_CODEC_ARGB8888);
					} else if (specs->vcs_rmask == MASK4_LE(0xff000000) &&
					           specs->vcs_bmask == MASK4_LE(0x0000ff00)) {
						SET_CODEC(VIDEO_CODEC_ABGR8888);
					}
				}
			} else if (specs->vcs_bmask == MASK4_LE(0x000000ff)) {
				if (specs->vcs_gmask == MASK4_LE(0x0000ff00) &&
				    specs->vcs_rmask == MASK4_LE(0x00ff0000)) {
					if (specs->vcs_amask == MASK4_LE(0xff000000)) {
						SET_CODEC(VIDEO_CODEC_BGRA8888);
					} else if (specs->vcs_amask == 0) {
						SET_CODEC(VIDEO_CODEC_BGRX8888);
					}
				}
			} else {
				if (specs->vcs_rmask == MASK4_LE(0x0000ff00)) {
					if (specs->vcs_gmask == MASK4_LE(0x00ff0000) &&
					    specs->vcs_bmask == MASK4_LE(0xff000000) &&
					    specs->vcs_amask == 0)
						SET_CODEC(VIDEO_CODEC_XRGB8888);
				} else if (specs->vcs_bmask == MASK4_LE(0x0000ff00)) {
					if (specs->vcs_gmask == MASK4_LE(0x00ff0000) &&
					    specs->vcs_rmask == MASK4_LE(0xff000000) &&
					    specs->vcs_amask == 0)
						SET_CODEC(VIDEO_CODEC_XBGR8888);
				}
			}
			break;

		case 24:
			if (specs->vcs_amask == 0 &&
			    specs->vcs_gmask == MASK3_LE(0x00ff00)) {
				if (specs->vcs_rmask == MASK3_LE(0x0000ff) &&
				    specs->vcs_bmask == MASK3_LE(0xff0000)) {
					SET_CODEC(VIDEO_CODEC_RGB888);
				} else if (specs->vcs_rmask == MASK3_LE(0xff0000) &&
				           specs->vcs_bmask == MASK3_LE(0x0000ff)) {
					SET_CODEC(VIDEO_CODEC_BGR888);
				}
			}
			break;

		case 16:
			if (specs->vcs_rmask == MASK2_LE(0x000f)) {
				if (specs->vcs_gmask == MASK2_LE(0x00f0) &&
				    specs->vcs_bmask == MASK2_LE(0x0f00)) {
					if (specs->vcs_amask == MASK2_LE(0xf000)) {
						SET_CODEC(VIDEO_CODEC_RGBA4444);
					} else if (specs->vcs_amask == 0) {
						SET_CODEC(VIDEO_CODEC_RGBX4444);
					}
				}
			} else if (specs->vcs_bmask == MASK2_LE(0x000f)) {
				if (specs->vcs_gmask == MASK2_LE(0x00f0) &&
				    specs->vcs_rmask == MASK2_LE(0x0f00)) {
					if (specs->vcs_amask == MASK2_LE(0xf000)) {
						SET_CODEC(VIDEO_CODEC_BGRA4444);
					} else if (specs->vcs_amask == 0) {
						SET_CODEC(VIDEO_CODEC_BGRX4444);
					}
				}
			} else if (specs->vcs_amask == MASK2_LE(0x000f)) {
				if (specs->vcs_gmask == MASK2_LE(0x0f00)) {
					if (specs->vcs_rmask == MASK2_LE(0x00f0) &&
					    specs->vcs_bmask == MASK2_LE(0xf000)) {
						SET_CODEC(VIDEO_CODEC_ARGB4444);
					} else if (specs->vcs_rmask == MASK2_LE(0xf000) &&
					           specs->vcs_bmask == MASK2_LE(0x00f0)) {
						SET_CODEC(VIDEO_CODEC_ABGR4444);
					}
				}
			} else if (specs->vcs_amask == 0) {
				if (specs->vcs_gmask == MASK2_LE(0x0f00)) {
					if (specs->vcs_rmask == MASK2_LE(0x00f0) &&
					    specs->vcs_bmask == MASK2_LE(0xf000)) {
						SET_CODEC(VIDEO_CODEC_XRGB4444);
					} else if (specs->vcs_rmask == MASK2_LE(0xf000) &&
					           specs->vcs_bmask == MASK2_LE(0x00f0)) {
						SET_CODEC(VIDEO_CODEC_XBGR4444);
					}
				}
			}

			if (specs->vcs_amask == 0 &&
			    specs->vcs_gmask == MASK2_LE(0x07e0)) {
				if (specs->vcs_rmask == MASK2_LE(0x001f)) {
					if (specs->vcs_bmask == MASK2_LE(0xf800))
						SET_CODEC(VIDEO_CODEC_RGB565);
				} else if (specs->vcs_bmask == MASK2_LE(0x001f)) {
					if (specs->vcs_rmask == MASK2_LE(0xf800))
						SET_CODEC(VIDEO_CODEC_BGR565);
				}
			}

			if (specs->vcs_rmask == MASK2_LE(0x001f)) {
				if (specs->vcs_gmask == MASK2_LE(0x03e0) &&
				    specs->vcs_bmask == MASK2_LE(0x7c00)) {
					if (specs->vcs_amask == MASK2_LE(0x8000)) {
						SET_CODEC(VIDEO_CODEC_RGBA5551);
					} else if (specs->vcs_amask == 0) {
						SET_CODEC(VIDEO_CODEC_RGBX5551);
					}
				}
			} else if (specs->vcs_amask == MASK2_LE(0x0001)) {
				if (specs->vcs_gmask == MASK2_LE(0x07c0)) {
					if (specs->vcs_rmask == MASK2_LE(0x003e) &&
					    specs->vcs_bmask == MASK2_LE(0xf800)) {
						SET_CODEC(VIDEO_CODEC_ARGB1555);
					} else if (specs->vcs_bmask == MASK2_LE(0x003e) &&
					           specs->vcs_rmask == MASK2_LE(0xf800)) {
						SET_CODEC(VIDEO_CODEC_ABGR1555);
					}
				}
			} else if (specs->vcs_bmask == MASK2_LE(0x001f)) {
				if (specs->vcs_gmask == MASK2_LE(0x03e0) &&
				    specs->vcs_rmask == MASK2_LE(0x7c00)) {
					if (specs->vcs_amask == MASK2_LE(0x8000)) {
						SET_CODEC(VIDEO_CODEC_BGRA5551);
					} else if (specs->vcs_amask == 0) {
						SET_CODEC(VIDEO_CODEC_BGRX5551);
					}
				}
			} else if (specs->vcs_amask == 0) {
				if (specs->vcs_gmask == MASK2_LE(0x07c0)) {
					if (specs->vcs_rmask == MASK2_LE(0x003e) &&
					    specs->vcs_bmask == MASK2_LE(0xf800)) {
						SET_CODEC(VIDEO_CODEC_XRGB1555);
					} else if (specs->vcs_bmask == MASK2_LE(0x003e) &&
					           specs->vcs_rmask == MASK2_LE(0xf800)) {
						SET_CODEC(VIDEO_CODEC_XBGR1555);
					}
				}
			}
			break;

		case 8:
			/* 1-byte, direct-color codecs */
			if (specs->vcs_amask == 0) {
				switch (specs->vcs_rmask) {

				case 0xe0:
					if (specs->vcs_gmask == 0x1c &&
					    specs->vcs_bmask == 0x03)
						SET_CODEC(VIDEO_CODEC_RGB332);
					if (specs->vcs_gmask == 0x18 &&
					    specs->vcs_bmask == 0x07)
						SET_CODEC(VIDEO_CODEC_RGB323);
					break;

				case 0xc0:
					if (specs->vcs_gmask == 0x38 &&
					    specs->vcs_bmask == 0x07)
						SET_CODEC(VIDEO_CODEC_RGB233);
					if (specs->vcs_gmask == 0x30 &&
					    specs->vcs_bmask == 0x0c)
						SET_CODEC(VIDEO_CODEC_RGBX2222);
					break;

				case 0x30:
					if (specs->vcs_gmask == 0x0c &&
					    specs->vcs_bmask == 0x03)
						SET_CODEC(VIDEO_CODEC_XRGB2222);
					break;

				case 0x0c:
					if (specs->vcs_gmask == 0x30 &&
					    specs->vcs_bmask == 0xc0)
						SET_CODEC(VIDEO_CODEC_BGRX2222);
					break;

				case 0x07:
					if (specs->vcs_gmask == 0x18 &&
					    specs->vcs_bmask == 0xe0)
						SET_CODEC(VIDEO_CODEC_BGR323);
					if (specs->vcs_gmask == 0x38 &&
					    specs->vcs_bmask == 0xc0)
						SET_CODEC(VIDEO_CODEC_BGR233);
					break;

				case 0x03:
					if (specs->vcs_gmask == 0x1c &&
					    specs->vcs_bmask == 0xe0)
						SET_CODEC(VIDEO_CODEC_BGR332);
					if (specs->vcs_gmask == 0x0c &&
					    specs->vcs_bmask == 0x30)
						SET_CODEC(VIDEO_CODEC_XBGR2222);
					break;

				default: goto nope;
				}
			} else {
				switch (specs->vcs_rmask) {

				case 0xc0:
					if (specs->vcs_gmask == 0x30 &&
					    specs->vcs_bmask == 0x0c &&
					    specs->vcs_amask == 0x03)
						SET_CODEC(VIDEO_CODEC_RGBA2222);
					break;

				case 0x30:
					if (specs->vcs_gmask == 0x0c &&
					    specs->vcs_bmask == 0x03 &&
					    specs->vcs_amask == 0xc0)
						SET_CODEC(VIDEO_CODEC_ARGB2222);
					break;

				case 0x0c:
					if (specs->vcs_gmask == 0x30 &&
					    specs->vcs_bmask == 0xc0 &&
					    specs->vcs_amask == 0x03)
						SET_CODEC(VIDEO_CODEC_BGRA2222);
					break;

				case 0x03:
					if (specs->vcs_gmask == 0x0c &&
					    specs->vcs_bmask == 0x30 &&
					    specs->vcs_amask == 0xc0)
						SET_CODEC(VIDEO_CODEC_ABGR2222);
					break;

				default: goto nope;
				}
			}
			break;

		default: goto nope;
		}
	}
return_codec:
	return libvideo_codec_lookup(codec);
nope:
	return NULL;
}


PRIVATE struct video_codec_handle dummy_handle = {
	.vch_refcnt  = 0x7fff,
	.vch_destroy = (void (CC *)(struct video_codec_handle *__restrict))(void *)-1,
};


struct video_codec_custom_handle: video_codec_handle {
	struct video_codec_custom vcch_aligned;
	struct video_codec_custom vcch_unaligned;
};

PRIVATE NONNULL((1)) void CC
video_codec_custom_handle_destroy(struct video_codec_handle *__restrict self) {
	struct video_codec_custom_handle *me;
	me = (struct video_codec_custom_handle *)self;
	free(me);
}



/* Same as `video_codec_lookup_specs()', but can also be used to construct
 * new codecs on-the-fly. Because this function is able/allowed to  create
 * new codecs on-the-fly, the caller must take ownership of a reference to
 * `*p_handle'  on success, and  keep that reference alive  for as long as
 * the the returned codec is in-use.
 *
 * When the described codec is actually a built-in one, this function always
 * succeeds,  and a  reference to a  dummy object is  stored in `*p_handle'.
 *
 * NOTE: This function doesn't need `vcs_pxsz' or `vcs_cbits' to be initialized.
 *
 * @return: * :   The codec in question (`*p_handle' must be inherited in this case)
 * @return: NULL: [EINVAL] Impossible codec
 * @return: NULL: [ENOMEM] Out-of-memory
 * @return: NULL: [*] Error */
INTERN WUNUSED NONNULL((1, 2)) struct video_codec const *CC
libvideo_codec_fromspecs(struct video_codec_specs const *__restrict specs,
                         /*out*/ REF struct video_codec_handle **__restrict p_handle) {
	struct video_codec_custom_handle *custom;
	struct video_codec const *builtin;

	/* Check if the codec is available as a built-in */
	builtin = libvideo_codec_lookup_specs(specs);
	if (builtin) {
		*p_handle = &dummy_handle;
		video_codec_handle_incref(&dummy_handle);
		return builtin;
	}

	/* Allocate a custom codec handle (aligned-only for now) */
	custom = (struct video_codec_custom_handle *)malloc(offsetafter(struct video_codec_custom_handle, vcch_aligned));
	if unlikely(!custom)
		return NULL;

	/* Populate the new codec's specs. */
	memcpy(&custom->vcch_aligned.vc_specs, specs,
	       sizeof(struct video_codec_specs));
	if unlikely(!libvideo_codec_populate_custom(&custom->vcch_aligned, false))
		goto err_inval;

	/* Check if we also need the unaligned version of the codec. */
	if (custom->vcch_aligned.vc_nalgn == NULL) {
		struct video_codec_custom_handle *full_custom;
		full_custom = (struct video_codec_custom_handle *)realloc(custom, sizeof(struct video_codec_custom_handle));
		if unlikely(!full_custom) {
			free(custom);
			return NULL;
		}
		custom = full_custom;
		memcpy(&custom->vcch_unaligned.vc_specs, specs,
		       sizeof(struct video_codec_specs));
		if unlikely(!libvideo_codec_populate_custom(&custom->vcch_unaligned, true))
			goto err_inval;
		assert(custom->vcch_unaligned.vc_nalgn == &custom->vcch_unaligned);
		custom->vcch_aligned.vc_nalgn = &custom->vcch_unaligned;
	}

	/* Finish initialization & return the aligned version of the codec. */
	custom->vch_refcnt  = 1;
	custom->vch_destroy = &video_codec_custom_handle_destroy;
	*p_handle = custom;
	return &custom->vcch_aligned;
err_inval:
	free(custom);
	errno = EINVAL;
	return NULL;
}


DEFINE_PUBLIC_ALIAS(video_codec_lookup_specs, libvideo_codec_lookup_specs);
DEFINE_PUBLIC_ALIAS(video_codec_fromspecs, libvideo_codec_fromspecs);

DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_CODEC_SPECS_C */
