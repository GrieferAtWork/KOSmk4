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
	if (specs->vcs_flags & VIDEO_CODEC_FLAG_GRAY) {
		if (specs->vcs_rmask == (((uint32_t)1 << specs->vcs_bpp) - 1) &&
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
		if (specs->vcs_rmask == (((uint32_t)1 << specs->vcs_bpp) - 1) &&
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
