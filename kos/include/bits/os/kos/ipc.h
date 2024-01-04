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
#ifndef _BITS_OS_KOS_IPC_H
#define _BITS_OS_KOS_IPC_H 1

#include <__stdinc.h>

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("key")
#pragma push_macro("uid")
#pragma push_macro("gid")
#pragma push_macro("cuid")
#pragma push_macro("cgid")
#pragma push_macro("mode")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef key
#undef uid
#undef gid
#undef cuid
#undef cgid
#undef mode

struct ipc_perm {
#if defined(__COMPILER_HAVE_TRANSPARENT_UNION) && !defined(__key)
	union {
		__key_t        key;    /* ??? */
		__key_t      __key;    /* ??? */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION && !__key */
#ifndef __key
#define __key          key
#endif /* !__key */
	__key_t            key;    /* ??? */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION || __key */
	__uid_t            uid;    /* ??? */
	__gid_t            gid;    /* ??? */
	__uid_t            cuid;   /* ??? */
	__gid_t            cgid;   /* ??? */
	__UINT16_TYPE__    mode;   /* ??? */
	__UINT16_TYPE__    __pad1;
	__UINT16_TYPE__    __seq;  /* ??? */
	__UINT16_TYPE__    __pad2;
	__syscall_ulong_t  __glibc_reserved1;
	__syscall_ulong_t  __glibc_reserved2;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("mode")
#pragma pop_macro("cgid")
#pragma pop_macro("cuid")
#pragma pop_macro("gid")
#pragma pop_macro("uid")
#pragma pop_macro("key")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_OS_KOS_IPC_H */
