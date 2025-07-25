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
#ifndef GUARD_LIBVIDEO_GFX_CODEC_CONVERTER_H
#define GUARD_LIBVIDEO_GFX_CODEC_CONVERTER_H 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <libvideo/gfx/codec/converter.h>

DECL_BEGIN

INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC initconv_from_p(struct video_converter *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC initconv_from_pa(struct video_converter *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC initconv_from_l(struct video_converter *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC initconv_from_la(struct video_converter *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC initconv_from_a(struct video_converter *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC initconv_from_rgb(struct video_converter *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC initconv_from_rgba(struct video_converter *__restrict self);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_CODEC_CONVERTER_H */
