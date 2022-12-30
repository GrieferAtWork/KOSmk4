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
/* (#) Portability: Cygwin    (/winsup/cygwin/include/asm/types.h) */
/* (#) Portability: Linux     (/usr/include/[...]/asm/types.h) */
/* (#) Portability: diet libc (/include/asm/types.h) */
#ifndef _ASM_TYPES_H
#define _ASM_TYPES_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <asm/bitsperlong.h> /* Also a dependency of Glibc's `<asm/types.h>' */

#ifdef __CC__
__DECL_BEGIN

#ifndef ____s8_defined
#define ____s8_defined
/* These need to be typedefs, since 3rd party headers like
 * <drm.h>  will try to re-define these through additional
 * typedefs that would cause compiler errors if we defined
 * them as pure macros here.
 * Think: `typedef int8_t __s8;', which would break if
 *        it expanded to `typedef int8_t signed char;'
 * NOTE: STDC allows for re-typedef-ing a declaration, so
 *       long as  nothing changes,  so as  long as  these
 *       typedefs match what is  found in said 3rd  party
 *       headers, there'll be no problem. */
typedef __INT8_TYPE__ __s8;
#define __s8 __s8
typedef __UINT8_TYPE__ __u8;
#define __u8 __u8
typedef __INT16_TYPE__ __s16;
#define __s16 __s16
typedef __UINT16_TYPE__ __u16;
#define __u16 __u16
typedef __INT32_TYPE__ __s32;
#define __s32 __s32
typedef __UINT32_TYPE__ __u32;
#define __u32 __u32
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ __s64;
#define __s64 __s64
#endif /* __INT64_TYPE__ */
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ __u64;
#define __u64 __u64
#endif /* __UINT64_TYPE__ */
#endif /* !____s8_defined */

__DECL_END
#endif /* __CC__ */

#endif /* !_ASM_TYPES_H */
