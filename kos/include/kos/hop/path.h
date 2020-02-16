/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_HOP_PATH_H
#define _KOS_HOP_PATH_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "openfd.h"

__DECL_BEGIN




/* For `HANDLE_TYPE_PATH' */
#define HOP_PATH_RECENT     0x00060001 /* Cache the given path as having been used recently. */
#define HOP_PATH_OPENPARENT 0x00060002 /* [struct hop_openfd *result] Open the parent node of a given path.
                                        * @throw: E_NO_SUCH_OBJECT: The given path already describes the filesystem root
                                        *                          (either the real one, or the one set by `chroot()') */
#define HOP_PATH_OPENVFS    0x00060003 /* [struct hop_openfd *result] Open the filesystem root object
                                        * @throw: E_NO_SUCH_OBJECT: The VFS root isn't accessible due to `chroot()' having
                                        *                           being used to hide it from view. */
#define HOP_PATH_OPENNODE   0x00060004 /* [struct hop_openfd *result] Open the mounted/bound INode associated with the path */
#define HOP_PATH_OPENDENTRY 0x00060005 /* [struct hop_openfd *result] Open the directory entry detailing the name of the path */
#define HOP_PATH_ISDRIVE    0x00060006 /* [uint32_t *result] Return the number of times that the given path is bound as a DOS-drive */
#define HOP_PATH_GETNAME    0x00060007 /* [struct hop_path_getname *data] Read the name of the given path */
#define HOP_PATH_OPENCHILD  0x00060008 /* [struct hop_path_openchild *data] Open a child of the given path */
#define HOP_PATH_RENAME     0x00060009 /* [struct hop_path_rename *data] Rename a child entry within a given path (wrapper for `path_rename()') */
#define HOP_PATH_TRAVERSE   0x0006000a /* [struct hop_path_traverse *data] Traverse the filesystem, starting at the given path (wrapper for `path_traverse_ex()') */

__DECL_END

#endif /* !_KOS_HOP_PATH_H */
