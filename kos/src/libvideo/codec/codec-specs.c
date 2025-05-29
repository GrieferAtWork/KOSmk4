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

#include <errno.h>
#include <stddef.h>
#include <kos/anno.h>
#include <stdint.h>

#include <libvideo/codec/codecs.h>

#include "codec-specs.h"
#include "codecs.h"

DECL_BEGIN

/* Same as `video_codec_lookup()', and also only returns built-in codecs, but lookup
 * is  done via `specs', as opposed to the  caller having to provide the codec's ID.
 *
 * NOTE: This function doesn't need `vcs_pxsz' to be initialized. */
INTERN WUNUSED ATTR_PURE NONNULL((1)) struct video_codec const *CC
libvideo_codec_lookup_specs(struct video_codec_specs const *__restrict specs) {
	video_codec_t codec = VIDEO_CODEC_NONE;
	if (specs->vcs_flags & VIDEO_CODEC_FLAG_GRAY) {
		if (specs->vcs_bpp == specs->vcs_cbits &&
		    specs->vcs_rmask == (((uint32_t)1 << specs->vcs_bpp) - 1) &&
		    specs->vcs_gmask == specs->vcs_rmask &&
		    specs->vcs_bmask == specs->vcs_rmask &&
		    specs->vcs_amask == 0) {
			switch (specs->vcs_bpp) {
			case 1: codec = VIDEO_CODEC_GRAY2_LSB; break;
			case 2: codec = VIDEO_CODEC_GRAY4_LSB; break;
			case 4: codec = VIDEO_CODEC_GRAY16_LSB; break;
			case 8: codec = VIDEO_CODEC_GRAY256; break;
			default: goto nope;
			}
			static_assert(VIDEO_CODEC_GRAY2_MSB == (VIDEO_CODEC_GRAY2_LSB + 1));
			static_assert(VIDEO_CODEC_GRAY4_MSB == (VIDEO_CODEC_GRAY4_LSB + 1));
			static_assert(VIDEO_CODEC_GRAY16_MSB == (VIDEO_CODEC_GRAY16_LSB + 1));
			if ((specs->vcs_flags & VIDEO_CODEC_FLAG_MSB) && specs->vcs_bpp < 8)
				++codec;
		}
	} else if (specs->vcs_flags & VIDEO_CODEC_FLAG_PAL) {
		if (specs->vcs_bpp == specs->vcs_cbits &&
		    specs->vcs_rmask == (((uint32_t)1 << specs->vcs_bpp) - 1) &&
		    specs->vcs_gmask == specs->vcs_rmask &&
		    specs->vcs_bmask == specs->vcs_rmask &&
		    specs->vcs_amask == 0) {
			switch (specs->vcs_bpp) {
			case 1: codec = VIDEO_CODEC_PAL2_LSB; break;
			case 2: codec = VIDEO_CODEC_PAL4_LSB; break;
			case 4: codec = VIDEO_CODEC_PAL16_LSB; break;
			case 8: codec = VIDEO_CODEC_PAL256; break;
			default: goto nope;
			}
			static_assert(VIDEO_CODEC_PAL2_MSB == (VIDEO_CODEC_PAL2_LSB + 1));
			static_assert(VIDEO_CODEC_PAL4_MSB == (VIDEO_CODEC_PAL4_LSB + 1));
			static_assert(VIDEO_CODEC_PAL16_MSB == (VIDEO_CODEC_PAL16_LSB + 1));
			if ((specs->vcs_flags & VIDEO_CODEC_FLAG_MSB) && specs->vcs_bpp < 8)
				++codec;
		}
	} else {
#define SET_CODEC(c) do{codec = (c); goto return_codec;}__WHILE0
		switch (specs->vcs_bpp) {
		case 32:
			if (specs->vcs_rmask == MASK4(0xff000000)) {
				if (specs->vcs_gmask == MASK4(0x00ff0000) &&
				    specs->vcs_bmask == MASK4(0x0000ff00)) {
					if (specs->vcs_amask == MASK4(0x000000ff)) {
						SET_CODEC(VIDEO_CODEC_RGBA8888);
					} else if (specs->vcs_amask == 0) {
						SET_CODEC(VIDEO_CODEC_RGBX8888);
					}
				}
			} else if (specs->vcs_amask == MASK4(0xff000000)) {
				if (specs->vcs_gmask == MASK4(0x0000ff00)) {
					if (specs->vcs_rmask == MASK4(0x00ff0000) &&
					    specs->vcs_bmask == MASK4(0x000000ff)) {
						SET_CODEC(VIDEO_CODEC_ARGB8888);
					} else if (specs->vcs_rmask == MASK4(0x000000ff) &&
					           specs->vcs_bmask == MASK4(0x00ff0000)) {
						SET_CODEC(VIDEO_CODEC_ABGR8888);
					}
				}
			} else if (specs->vcs_bmask == MASK4(0xff000000)) {
				if (specs->vcs_gmask == MASK4(0x00ff0000) &&
				    specs->vcs_rmask == MASK4(0x0000ff00)) {
					if (specs->vcs_amask == MASK4(0x000000ff)) {
						SET_CODEC(VIDEO_CODEC_BGRA8888);
					} else if (specs->vcs_amask == 0) {
						SET_CODEC(VIDEO_CODEC_BGRX8888);
					}
				}
			} else {
				if (specs->vcs_rmask == MASK4(0x00ff0000)) {
					if (specs->vcs_gmask == MASK4(0x0000ff00) &&
					    specs->vcs_bmask == MASK4(0x000000ff) &&
					    specs->vcs_amask == 0)
						SET_CODEC(VIDEO_CODEC_XRGB8888);
				} else if (specs->vcs_bmask == MASK4(0x00ff0000)) {
					if (specs->vcs_gmask == MASK4(0x0000ff00) &&
					    specs->vcs_rmask == MASK4(0x000000ff) &&
					    specs->vcs_amask == 0)
						SET_CODEC(VIDEO_CODEC_XBGR8888);
				}
			}
			break;

		case 24:
			if (specs->vcs_amask == 0 &&
			    specs->vcs_gmask == MASK3(0x00ff00)) {
				if (specs->vcs_rmask == MASK3(0xff0000) &&
				    specs->vcs_bmask == MASK3(0x0000ff)) {
					SET_CODEC(VIDEO_CODEC_RGB888);
				} else if (specs->vcs_rmask == MASK3(0x0000ff) &&
				           specs->vcs_bmask == MASK3(0xff0000)) {
					SET_CODEC(VIDEO_CODEC_BGR888);
				}
			}
			break;

		case 16:
			if (specs->vcs_rmask == MASK2(0xf000)) {
				if (specs->vcs_gmask == MASK2(0x0f00) &&
				    specs->vcs_bmask == MASK2(0x00f0)) {
					if (specs->vcs_amask == MASK2(0x000f)) {
						SET_CODEC(VIDEO_CODEC_RGBA4444);
					} else if (specs->vcs_amask == 0) {
						SET_CODEC(VIDEO_CODEC_RGBX4444);
					}
				}
			} else if (specs->vcs_bmask == MASK2(0xf000)) {
				if (specs->vcs_gmask == MASK2(0x0f00) &&
				    specs->vcs_rmask == MASK2(0x00f0)) {
					if (specs->vcs_amask == MASK2(0x000f)) {
						SET_CODEC(VIDEO_CODEC_BGRA4444);
					} else if (specs->vcs_amask == 0) {
						SET_CODEC(VIDEO_CODEC_BGRX4444);
					}
				}
			} else if (specs->vcs_amask == MASK2(0xf000)) {
				if (specs->vcs_gmask == MASK2(0x00f0)) {
					if (specs->vcs_rmask == MASK2(0x0f00) &&
					    specs->vcs_bmask == MASK2(0x000f)) {
						SET_CODEC(VIDEO_CODEC_ARGB4444);
					} else if (specs->vcs_rmask == MASK2(0x000f) &&
					           specs->vcs_bmask == MASK2(0x0f00)) {
						SET_CODEC(VIDEO_CODEC_ABGR4444);
					}
				}
			} else if (specs->vcs_amask == 0) {
				if (specs->vcs_gmask == MASK2(0x00f0)) {
					if (specs->vcs_rmask == MASK2(0x0f00) &&
					    specs->vcs_bmask == MASK2(0x000f)) {
						SET_CODEC(VIDEO_CODEC_XRGB4444);
					} else if (specs->vcs_rmask == MASK2(0x000f) &&
					           specs->vcs_bmask == MASK2(0x0f00)) {
						SET_CODEC(VIDEO_CODEC_XBGR4444);
					}
				}
			}

			if (specs->vcs_amask == 0 &&
			    specs->vcs_gmask == MASK2(0x07e0)) {
				if (specs->vcs_rmask == MASK2(0xf800)) {
					if (specs->vcs_bmask == MASK2(0x001f))
						SET_CODEC(VIDEO_CODEC_RGB565);
				} else if (specs->vcs_bmask == MASK2(0xf800)) {
					if (specs->vcs_rmask == MASK2(0x001f))
						SET_CODEC(VIDEO_CODEC_BGR565);
				}
			}

			if (specs->vcs_rmask == MASK2(0xf800)) {
				if (specs->vcs_gmask == MASK2(0x07c0) &&
				    specs->vcs_bmask == MASK2(0x003e)) {
					if (specs->vcs_amask == MASK2(0x0001)) {
						SET_CODEC(VIDEO_CODEC_RGBA5551);
					} else if (specs->vcs_amask == 0) {
						SET_CODEC(VIDEO_CODEC_RGBX5551);
					}
				}
			} else if (specs->vcs_amask == MASK2(0x8000)) {
				if (specs->vcs_gmask == MASK2(0x03e0)) {
					if (specs->vcs_rmask == MASK2(0x7c00) &&
					    specs->vcs_bmask == MASK2(0x001f)) {
						SET_CODEC(VIDEO_CODEC_ARGB1555);
					} else if (specs->vcs_bmask == MASK2(0x7c00) &&
					           specs->vcs_rmask == MASK2(0x001f)) {
						SET_CODEC(VIDEO_CODEC_ABGR1555);
					}
				}
			} else if (specs->vcs_bmask == MASK2(0xf800)) {
				if (specs->vcs_gmask == MASK2(0x07c0) &&
				    specs->vcs_rmask == MASK2(0x003e)) {
					if (specs->vcs_amask == MASK2(0x0001)) {
						SET_CODEC(VIDEO_CODEC_BGRA5551);
					} else if (specs->vcs_amask == 0) {
						SET_CODEC(VIDEO_CODEC_BGRX5551);
					}
				}
			} else if (specs->vcs_amask == 0) {
				if (specs->vcs_gmask == MASK2(0x03e0)) {
					if (specs->vcs_rmask == MASK2(0x7c00) &&
					    specs->vcs_bmask == MASK2(0x001f)) {
						SET_CODEC(VIDEO_CODEC_XRGB1555);
					} else if (specs->vcs_bmask == MASK2(0x7c00) &&
					           specs->vcs_rmask == MASK2(0x001f)) {
						SET_CODEC(VIDEO_CODEC_XBGR1555);
					}
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
	.vch_refcnt  = 100,
	.vch_destroy = (void (CC *)(struct video_codec_handle *__restrict))(void *)-1,
};


/* Same as `video_codec_lookup_specs()', but can  also be used to  construct
 * new codecs on-the-fly (if supported/implemented by the host architecture)
 *
 * Because this function is able/allowed to create new codecs on-the-fly, the
 * caller must take ownership of a  reference to `*p_handle' on success,  and
 * keep that reference alive for as long as the returned codec is in-use.
 *
 * When the described codec is actually a built-in one, this function always
 * succeeds,  and a  reference to a  dummy object is  stored in `*p_handle'.
 *
 * NOTE: This function doesn't need `vcs_pxsz' to be initialized.
 *
 * @return: * :   The codec in question (`*p_handle' must be inherited in this case)
 * @return: NULL: [EINVAL] Impossible codec
 * @return: NULL: [ENOMEM] Out-of-memory or too many custom codecs allocated already
 * @return: NULL: [*] Error */
INTERN WUNUSED NONNULL((1, 2)) struct video_codec const *CC
libvideo_codec_fromspecs(struct video_codec_specs const *__restrict specs,
                         /*out*/ REF struct video_codec_handle **__restrict p_handle) {
	struct video_codec const *result;
	result = libvideo_codec_lookup_specs(specs);
	if (result) {
		*p_handle = &dummy_handle;
		video_codec_handle_incref(&dummy_handle);
		return result;
	}

	/* TODO: Arch-specific code generators for wrappers that simply
	 *       pass an the codec itself as an additional argument  to
	 *       common, generic implementations of line functions. */

	errno = ENOMEM;
	return NULL;
}


DEFINE_PUBLIC_ALIAS(video_codec_lookup_specs, libvideo_codec_lookup_specs);
DEFINE_PUBLIC_ALIAS(video_codec_fromspecs, libvideo_codec_fromspecs);

DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_CODEC_SPECS_C */
