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
#ifndef _KOS_HOP_HANDLE_H
#define _KOS_HOP_HANDLE_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "openfd.h"

__DECL_BEGIN

#define __OFFSET_HOP_HANDLE_STAT_STRUCT_SIZE 0
#define __OFFSET_HOP_HANDLE_STAT_MODE        4
#define __OFFSET_HOP_HANDLE_STAT_TYPE        8
#define __OFFSET_HOP_HANDLE_STAT_KIND        10
#define __OFFSET_HOP_HANDLE_STAT_REFCNT      16
#define __OFFSET_HOP_HANDLE_STAT_ADDRESS     24
#define __OFFSET_HOP_HANDLE_STAT_TYPENAME    32
#define __SIZEOF_HOP_HANDLE_STAT             64
#ifdef __CC__
struct hop_handle_stat /*[PREFIX(hs_)]*/ {
	__uint32_t            hs_struct_size;  /* [== sizeof(struct hop_handle_stat)]
	                                        * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                        * this value is too small or doesn't match any recognized
	                                        * structure version. */
	__uint16_t            hs_mode;         /* The I/O mode with which this handle operates (set of `IO_*'). */
	__uint16_t          __hs_pad1;         /* ... */
	__uint16_t            hs_type;         /* The handle type (one of `HANDLE_TYPE_*'). */
	__uint16_t            hs_kind;         /* The handle kind (one of `HANDLE_TYPEKIND_*'). */
	__uint32_t          __hs_pad2;         /* ... */
	__uint64_t            hs_refcnt;       /* Reference counter of this handle. */
	__uint64_t            hs_address;      /* Kernel-space pointer to the address where data of this handle is stored.
	                                        * Note: Do not rely on this actually being the proper address when interfacing
	                                        *       with custom drivers (as a matter of fact: custom drivers should never
	                                        *       blindly trust kernel-space pointers passed from user-space, and should
	                                        *       always instead make use of handles to kernel-space objects).
	                                        *       Anyways: the kernel is allowed to mangle the actual address however
	                                        *                it pleases, so-long as the value stored here ends up being
	                                        *                system-wide persistent-unique for as long as references
	                                        *                exist for the handle. */
	char                  hs_typename[32]; /* The name of the handle's type. */
};
#endif /* __CC__ */

/* For any kind of handle */
#define HOP_HANDLE_STAT                0xffff0001 /* [struct hop_handle_stat *result] Read information about the given handle */
#define HOP_HANDLE_NOOP                0xffff0002 /* Do nothing other than verifying that `fd' is a valid handle. */
#define HOP_HANDLE_REOPEN              0xffff0003 /* [struct hop_openfd *result] Re-open the given handle
                                                   * NOTE: The value returned by `hop()' is identical to the value written to `result->of_hint'. */
#define HOP_HANDLE_GET_REFCNT          0xffff0004 /* [uint64_t *result] Return the reference counter for the given handle. */
#define HOP_HANDLE_GET_ADDRESS         0xffff0005 /* [uint64_t *result] Return the kernel-space address of the handle (s.a. `struct hop_handle_stat::hs_address'). */
#define HOP_HANDLE_GET_TYPE            0xffff0006 /* [uint16_t *result] Return the handle's type. */
#define HOP_HANDLE_GET_KIND            0xffff0007 /* [uint16_t *result] Return the handle's kind. */
#define HOP_HANDLE_GET_MODE            0xffff0008 /* [uint16_t *result] Return the handle's I/O mode (s.a. `iomode_t'). */
#define HOP_HANDLE_DUP                 0xffff0009 /* Quick alias for `dup(fd)' (`hop()' returns the new file handle) */
#define HOP_HANDLE_DUP_CLOEXEC         0xffff000a /* Quick alias for `dup(fd)' + set the CLOEXEC flag (`hop()' returns the new file handle) */
#define HOP_HANDLE_DUP_CLOFORK         0xffff000b /* Quick alias for `dup(fd)' + set the CLOFORK flag (`hop()' returns the new file handle) */
#define HOP_HANDLE_DUP_CLOEXEC_CLOFORK 0xffff000c /* Quick alias for `dup(fd)' + set the CLOEXEC+CLOFORK flag (`hop()' returns the new file handle) */
/* TODO: Wrapper for `handle_print()' */
/* TODO: Wrapper for `handle_datasize()' */


__DECL_END

#endif /* !_KOS_HOP_HANDLE_H */
