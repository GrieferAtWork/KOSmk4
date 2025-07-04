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
/*!replace_with_include <sys/mman.h>*/
#ifndef _BITS_CRT_MAPFILE_H
#define _BITS_CRT_MAPFILE_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

/* Flags for `fmapfile(3)' */
#define __FMAPFILE_READALL   0x0001 /* Flag: use `preadall(3)' / `readall(3)' instead of `pread(2)' / `read(2)' */
#define __FMAPFILE_MUSTMMAP  0x0002 /* Flag: require the use of a mmap(2) */
#define __FMAPFILE_MAPSHARED 0x0004 /* Flag: when using mmap, don't map as MAP_PRIVATE, but use MAP_SHARED (don't pass a non-zero `num_trailing_nulbytes' in this case!) */
#define __FMAPFILE_ATSTART   0x0008 /* Flag: assume that the given file's pointer is located at the file's beginning (pass `offset=0' when using this flag) */

#ifdef __CC__
__DECL_BEGIN

struct mapfile {
	__BYTE_TYPE__  *mf_addr;    /* [0..mf_size][owned] Base address of the file mapping. */
	__SIZE_TYPE__   mf_size;    /* Mapping size (in bytes, excluding trailing NUL-bytes) */
	__SIZE_TYPE__ __mf_mapsize; /* Used internally: the mmap'd file size, or `0' if `mf_addr' was malloc'd */
};

/* Returns  non-zero if `mmap(2)'  was used to create  the mapping of `self',
 * consequently also meaning that `munmap(2)' will be used by `unmapfile(3)'.
 *
 * NOTE: Don't use this information to try and unmap the buffer yourself! That
 *       should only be done by `unmapfile(3)' itself (e.g. an  implementation
 *       for windows would not have munmap(2), but would still have other ways
 *       of creating/deleting file mappings).
 *       Instead, this macro is only provided as an optimization hint meaning
 *       that (when being true) that memory pointed-to by `mf_addr' *may* get
 *       initialized lazily upon first access. */
#define mapfile_usesmmap(self)  ((self)->__mf_mapsize != 0)

/* Configure `self' to do `free(self->mf_addr)' in `unmapfile(3)' */
#define __mapfile_setheap(self) (void)((self)->__mf_mapsize = 0)


__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_MAPFILE_H */
