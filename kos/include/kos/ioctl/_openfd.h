/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_IOCTL__OPENFD_H
#define _KOS_IOCTL__OPENFD_H 1

#include <__stdinc.h>

#include <bits/types.h>


/*
 * The `openfd' structure is a common descriptor used by ioctls to
 * describe an abstract mechanism by which new file handles can be
 * opened.
 */


/* Values for `struct openfd::of_mode' */
#define OPENFD_MODE_AUTO       0x0000 /* Ignore `of_hint' and automatically select an appropriate handle
                                       * -> This is the same as `OPENFD_MODE_HINT' with `of_hint=0' */
#define OPENFD_MODE_HINT       0x0001 /* Install the newly opened handle into the lowest unused handle that is `>= of_hint' */
#define OPENFD_MODE_INTO       0x0002 /* Install the newly opened handle into `of_hint', automatically
                                       * closing any handle that may  have been stored inside  before.
                                       * Additionally, `of_hint' may be any writable symbolic handle (e.g. `AT_FDCWD') */
#define OPENFD_MODE_INTO_EXACT 0x0003 /* Same  as  `OPENFD_MODE_INTO', but  don't  recognize symbolic
                                       * handles, and throw an `E_INVALID_HANDLE_FILE' error instead. */


#define __OFFSET_OPENFD_MODE  0
#define __OFFSET_OPENFD_FLAGS 2
#define __OFFSET_OPENFD_HINT  4
#define __SIZEOF_OPENFD       8
#ifdef __CC__
__DECL_BEGIN

struct openfd /*[PREFIX(of_)]*/ {
	__uint16_t of_mode;  /* Open mode (One of `OPENFD_MODE_*') */
	__uint16_t of_flags; /* Set of `IO_CLOEXEC | IO_CLOFORK' */
	__int32_t  of_hint;  /* [in]  Open hint (s.a. `OPENFD_MODE_INTO')
	                      * [out] The ID of the handle that has been opened (must be close(2)'ed). */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_KOS_IOCTL__OPENFD_H */
