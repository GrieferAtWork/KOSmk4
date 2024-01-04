/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_DLFCN_H
#define _BITS_CRT_DLFCN_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

/* For the sake of keeping `libdl' from becoming bloated (too much),
 * some libdl  helper functions  are actually  implemented by  libc.
 *
 * This header defines the internal structures and macros needed by
 * those functions. */

__DECL_BEGIN

#if defined(__USE_GNU) && defined(__CRT_HAVE__dl_find_object)
#ifndef DLFO_STRUCT_HAS_EH_DBASE
#if defined(__nios2__) || (defined(__i386__) && !defined(__x86_64__))
#define DLFO_STRUCT_HAS_EH_DBASE 1
#else /* ... */
#define DLFO_STRUCT_HAS_EH_DBASE 0
#endif /* !... */
#endif /* !DLFO_STRUCT_HAS_EH_DBASE */

#ifndef DLFO_STRUCT_HAS_EH_COUNT
#if defined(__arm__)
#define DLFO_STRUCT_HAS_EH_COUNT 1
#else /* ... */
#define DLFO_STRUCT_HAS_EH_COUNT 0
#endif /* !... */
#endif /* !DLFO_STRUCT_HAS_EH_COUNT */

/* Name of the `.eh_frame' section loaded into `dlfo_eh_frame' */
#ifndef DLFO_EH_SEGMENT_TYPE
#ifdef __arm__
#define DLFO_EH_SEGMENT_TYPE PT_ARM_EXIDX
#else /* __arm__ */
#define DLFO_EH_SEGMENT_TYPE PT_GNU_EH_FRAME
#endif /* !__arm__ */
#endif /* !DLFO_EH_SEGMENT_TYPE */

struct link_map;
struct dl_find_object {
	__UINT64_TYPE__   dlfo_flags;     /* ??? */
	void             *dlfo_map_start; /* [1..1] Lowest address mapped by this module (mapping may not be continuous) */
	void             *dlfo_map_end;   /* [1..1] 1+ Greatest address mapped by this module (mapping may not be continuous) */
	struct link_map  *dlfo_link_map;  /* [1..1] Return value of `RTLD_DI_LINKMAP' */
	void             *dlfo_eh_frame;  /* [0..1] Return value of `dllocksection(this, NAMEOF(DLFO_EH_SEGMENT_TYPE))->ds_data' */
#if DLFO_STRUCT_HAS_EH_DBASE
	void             *dlfo_eh_dbase;  /* [1..1] Return value of `DLAUXCTRL_GET_DATABASE' */
#if __SIZEOF_POINTER__ < 8
	__UINT32_TYPE__ __dlfo_eh_dbase_pad;
#endif /* __SIZEOF_POINTER__ < 8 */
#endif /* DLFO_STRUCT_HAS_EH_DBASE */
#if DLFO_STRUCT_HAS_EH_COUNT
	__INT32_TYPE__    dlfo_eh_count;  /* == `dllocksection(this, NAMEOF(DLFO_EH_SEGMENT_TYPE))->ds_size / 8' */
	__UINT32_TYPE__ __dlfo_eh_count_pad;
#endif /* DLFO_STRUCT_HAS_EH_COUNT */
	__UINT64_TYPE__ __dflo_reserved[7];
};
#endif /* __USE_GNU && __CRT_HAVE__dl_find_object */

__DECL_END

#endif /* !_BITS_CRT_DLFCN_H */
