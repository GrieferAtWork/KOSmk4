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
#ifndef _KOS_HOP_PATH_H
#define _KOS_HOP_PATH_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "openfd.h"

__DECL_BEGIN

/************************************************************************/
/* HANDLE_TYPE_PATH                                                     */
/************************************************************************/

/* Cache the given path as having been used recently. */
#define HOP_PATH_RECENT     HOP_CMD(HANDLE_TYPE_PATH, 0x0001)

/* [struct hop_openfd *result] Open the parent node of a given path.
 * @return: == result->of_hint
 * @throw: E_NO_SUCH_OBJECT: The given path already describes the filesystem root
 *                          (either the real one, or the one set by `chroot()') */
#define HOP_PATH_OPENPARENT HOP_CMD(HANDLE_TYPE_PATH, 0x0002)

/* [struct hop_openfd *result] Open the filesystem root object
 * @return: == result->of_hint
 * @throw: E_NO_SUCH_OBJECT: The VFS root isn't accessible due to `chroot()' having
 *                           being used to hide it from view. */
#define HOP_PATH_OPENVFS    HOP_CMD(HANDLE_TYPE_PATH, 0x0003)

/* [struct hop_openfd *result] Open the mounted/bound INode associated with the path
 * @return: == result->of_hint */
#define HOP_PATH_OPENNODE   HOP_CMD(HANDLE_TYPE_PATH, 0x0004)

/* [struct hop_openfd *result] Open the directory entry detailing the name of the path
 * @return: == result->of_hint */
#define HOP_PATH_OPENDENTRY HOP_CMD(HANDLE_TYPE_PATH, 0x0005)

/* [uint32_t *result] Return the number of times that the given path is bound as a DOS-drive */
#define HOP_PATH_ISDRIVE    HOP_CMD(HANDLE_TYPE_PATH, 0x0006)

/* [struct hop_path_getname *arg] Read the name of the given path */
#define HOP_PATH_GETNAME    HOP_CMD(HANDLE_TYPE_PATH, 0x0007)

/* [struct hop_path_openchild *arg] Open a child of the given path
 * @return: == arg->poc_result.of_hint */
#define HOP_PATH_OPENCHILD  HOP_CMD(HANDLE_TYPE_PATH, 0x0008)

/* [struct hop_path_rename *arg] Rename a child entry within a given path (wrapper for `path_rename()') */
#define HOP_PATH_RENAME     HOP_CMD(HANDLE_TYPE_PATH, 0x0009)

/* [struct hop_path_traverse *arg] Traverse the filesystem, starting at the given path (wrapper for `path_traverse_ex()') */
#define HOP_PATH_TRAVERSE   HOP_CMD(HANDLE_TYPE_PATH, 0x000a)

__DECL_END

#endif /* !_KOS_HOP_PATH_H */
