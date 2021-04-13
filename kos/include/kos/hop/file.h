/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_HOP_FILE_H
#define _KOS_HOP_FILE_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "openfd.h"

__DECL_BEGIN


#define __OFFSET_HOP_FILE_CMPXCHG_OFFSET_STRUCT_SIZE 0
#define __OFFSET_HOP_FILE_CMPXCHG_OFFSET_EXPOFFSET   8
#define __OFFSET_HOP_FILE_CMPXCHG_OFFSET_NEWOFFSET   16
#define __OFFSET_HOP_FILE_CMPXCHG_OFFSET_OLDOFFSET   24
#define __SIZEOF_HOP_FILE_CMPXCHG_OFFSET             32
#ifdef __CC__
struct hop_file_cmpxchg_offset /*[PREFIX(cxo_)]*/ {
	__uint32_t            cxo_struct_size;   /* [== sizeof(struct hop_file_cmpxchg_offset)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small  or doesn't match any  recognized
	                                          * structure version. */
	__uint32_t          __cxo_pad1;          /* ... */
	__uint64_t            cxo_expoffset;     /* [IN] The expected old file offset that must be matched
	                                          *      in order for `cxo_newoffset' to be successfully applied. */
	__uint64_t            cxo_newoffset;     /* [IN] The new file offset to set when `cxo_expoffset' was found. */
	__uint64_t            cxo_oldoffset;     /* [OUT] The actual old file-offset (always written) */
};
#endif /* __CC__ */



/************************************************************************/
/* HANDLE_TYPE_FILE                                                     */
/************************************************************************/
/* [struct hop_file_cmpxchg_offset *arg] Compare-exchange the current file offset. */
#define HOP_FILE_CMPXCHG_OFFSET HOP_CMD(HANDLE_TYPE_FILE, 0x0001)

/* [struct hop_openfd *result] Open the Inode that is backing the file.
 * @return: == result->of_hint */
#define HOP_FILE_OPENNODE       HOP_CMD(HANDLE_TYPE_FILE, 0x0002)

/* [struct hop_openfd *result] Open the path within which the
 * file is stored (the VFS path of its containing directory).
 * @return: == result->of_hint */
#define HOP_FILE_OPENPATH       HOP_CMD(HANDLE_TYPE_FILE, 0x0003)

/* [struct hop_openfd *result] Open the directory entry used to describe the file's INode.
 * @return: == result->of_hint */
#define HOP_FILE_OPENDENTRY     HOP_CMD(HANDLE_TYPE_FILE, 0x0004)


__DECL_END

#endif /* !_KOS_HOP_FILE_H */
