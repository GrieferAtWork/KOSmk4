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
#ifndef _LIBVIDEO_GFX_API_H
#define _LIBVIDEO_GFX_API_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

/*#define LIBVIDEO_GFX_EXPOSE_INTERNALS*/

/* Feature flag: are 64-bit pixel formats supported? */
#ifndef CONFIG_NO_VIDEO_CODEC_HAVE_PIXEL64
#define CONFIG_VIDEO_CODEC_HAVE_PIXEL64
#endif /* !CONFIG_NO_VIDEO_CODEC_HAVE_PIXEL64 */

#if defined(__i386__) && !defined(__x86_64__)
#define LIBVIDEO_GFX_CC  __ATTR_STDCALL
#define LIBVIDEO_GFX_FCC __ATTR_FASTCALL
#ifndef CONFIG_NO_VIDEO_CODEC_HAVE__VC_SETPIXEL3
#define VIDEO_CODEC_HAVE__VC_SETPIXEL3
#endif /* !CONFIG_NO_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */
#else /* ... */
#define LIBVIDEO_GFX_CC  /* nothing */
#define LIBVIDEO_GFX_FCC /* nothing */
#endif /* !... */

#if (!defined(LIBVIDEO_GFX_WANT_PROTOTYPES) && \
     defined(__KOS__) && defined(__KERNEL__))
#define LIBVIDEO_GFX_WANT_PROTOTYPES
#endif /* ... */

#if (defined(__KOS__) && defined(__KERNEL__) && \
     defined(BUILDING_KERNEL_CORE))
#define LIBVIDEO_GFX_DECL __PUBDEF
#elif defined(__LIBVIDEO_GFX_STATIC)
#define LIBVIDEO_GFX_DECL __INTDEF
#else /* ... */
#define LIBVIDEO_GFX_DECL __IMPDEF
#endif /* !... */

/* Library name for use with `dlopen(3D)' */
#define LIBVIDEO_GFX_LIBRARY_NAME "libvideo-gfx.so"

#endif /* !_LIBVIDEO_GFX_API_H */
