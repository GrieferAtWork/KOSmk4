/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_COMPAT_LINUX_LDT_H
#define _I386_KOS_KOS_COMPAT_LINUX_LDT_H 1

#include <__stdinc.h>

#include <hybrid/__bitfield.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

#undef entry_number
#undef base_addr
#undef limit
#undef seg_32bit
#undef contents
#undef read_exec_only
#undef limit_in_pages
#undef seg_not_present
#undef useable

struct linux_user_desc {
	__UINT32_TYPE__      entry_number;
	__ULONGPTR_TYPE__    base_addr;
	__UINT32_TYPE__      limit;
	__HYBRID_BITFIELD8_T seg_32bit : 1;
	__HYBRID_BITFIELD8_T contents : 2;
	__HYBRID_BITFIELD8_T read_exec_only : 1;
	__HYBRID_BITFIELD8_T limit_in_pages : 1;
	__HYBRID_BITFIELD8_T seg_not_present : 1;
	__HYBRID_BITFIELD8_T useable : 1;
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_COMPAT_LINUX_LDT_H */
