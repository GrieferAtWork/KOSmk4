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
#ifndef __GUARD_HYBRID___ROTATE_H
#define __GUARD_HYBRID___ROTATE_H 1

#include "../__stdinc.h"
#include "typecore.h"

__DECL_BEGIN

#define __hybrid_rol8_c(x,shift)   (((x)>>(0x8-((shift)&0x07)))|((x)<<((shift)&0x07)))
#define __hybrid_ror8_c(x,shift)   (((x)<<(0x8-((shift)&0x07)))|((x)>>((shift)&0x07)))
#define __hybrid_rol16_c(x,shift)  (((x)>>(0x10-((shift)&0x0f)))|((x)<<((shift)&0x0f)))
#define __hybrid_ror16_c(x,shift)  (((x)<<(0x10-((shift)&0x0f)))|((x)>>((shift)&0x0f)))
#define __hybrid_rol32_c(x,shift)  (((x)>>(0x20-((shift)&0x1f)))|((x)<<((shift)&0x1f)))
#define __hybrid_ror32_c(x,shift)  (((x)<<(0x20-((shift)&0x1f)))|((x)>>((shift)&0x1f)))
#ifdef __UINT64_TYPE__
#define __hybrid_rol64_c(x,shift)  (((x)>>(0x40-((shift)&0x3f)))|((x)<<((shift)&0x3f)))
#define __hybrid_ror64_c(x,shift)  (((x)<<(0x40-((shift)&0x3f)))|((x)>>((shift)&0x3f)))
#ifdef __UINT128_TYPE__
#define __hybrid_rol128_c(x,shift) (((x)>>(0x80-((shift)&0x7f)))|((x)<<((shift)&0x7f)))
#define __hybrid_ror128_c(x,shift) (((x)<<(0x80-((shift)&0x7f)))|((x)>>((shift)&0x7f)))
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */

/* TODO: X86-specific inline-assembly implementation */

#define __hybrid_rol8(x,shift)   __hybrid_rol8_c(x,shift)
#define __hybrid_ror8(x,shift)   __hybrid_ror8_c(x,shift)
#define __hybrid_rol16(x,shift)  __hybrid_rol16_c(x,shift)
#define __hybrid_ror16(x,shift)  __hybrid_ror16_c(x,shift)
#define __hybrid_rol32(x,shift)  __hybrid_rol32_c(x,shift)
#define __hybrid_ror32(x,shift)  __hybrid_ror32_c(x,shift)
#ifdef __UINT64_TYPE__
#define __hybrid_rol64(x,shift)  __hybrid_rol64_c(x,shift)
#define __hybrid_ror64(x,shift)  __hybrid_ror64_c(x,shift)
#ifdef __UINT128_TYPE__
#define __hybrid_rol128(x,shift) __hybrid_rol128_c(x,shift)
#define __hybrid_ror128(x,shift) __hybrid_ror128_c(x,shift)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */

#ifndef __NO_builtin_choose_expr
#if !defined(__UINT64_TYPE__)
#define __hybrid_rol(x,shift) __builtin_choose_expr(sizeof(x) == 1,__hybrid_rol8(x,shift),__builtin_choose_expr(sizeof(x) == 2,__hybrid_rol16(x,shift),__hybrid_rol32(x,shift)))
#define __hybrid_ror(x,shift) __builtin_choose_expr(sizeof(x) == 1,__hybrid_ror8(x,shift),__builtin_choose_expr(sizeof(x) == 2,__hybrid_ror16(x,shift),__hybrid_ror32(x,shift)))
#elif !defined(__UINT128_TYPE__)
#define __hybrid_rol(x,shift) __builtin_choose_expr(sizeof(x) == 1,__hybrid_rol8(x,shift),__builtin_choose_expr(sizeof(x) == 2,__hybrid_rol16(x,shift),__builtin_choose_expr(sizeof(x) == 4,__hybrid_rol32(x,shift),__hybrid_rol64(x,shift))))
#define __hybrid_ror(x,shift) __builtin_choose_expr(sizeof(x) == 1,__hybrid_ror8(x,shift),__builtin_choose_expr(sizeof(x) == 2,__hybrid_ror16(x,shift),__builtin_choose_expr(sizeof(x) == 4,__hybrid_ror32(x,shift),__hybrid_ror64(x,shift))))
#else
#define __hybrid_rol(x,shift) __builtin_choose_expr(sizeof(x) == 1,__hybrid_rol8(x,shift),__builtin_choose_expr(sizeof(x) == 2,__hybrid_rol16(x,shift),__builtin_choose_expr(sizeof(x) == 4,__hybrid_rol32(x,shift),__builtin_choose_expr(sizeof(x) == 8,__hybrid_rol64(x,shift),__hybrid_rol128(x,shift)))))
#define __hybrid_ror(x,shift) __builtin_choose_expr(sizeof(x) == 1,__hybrid_ror8(x,shift),__builtin_choose_expr(sizeof(x) == 2,__hybrid_ror16(x,shift),__builtin_choose_expr(sizeof(x) == 4,__hybrid_ror32(x,shift),__builtin_choose_expr(sizeof(x) == 8,__hybrid_ror64(x,shift),__hybrid_ror128(x,shift)))))
#endif
#else /* !__NO_builtin_choose_expr */
#if !defined(__UINT64_TYPE__)
#define __hybrid_rol(x,shift) (sizeof(x) == 1 ? __hybrid_rol8(x,shift) : sizeof(x) == 2 ? __hybrid_rol16(x,shift) : __hybrid_rol32(x,shift))
#define __hybrid_ror(x,shift) (sizeof(x) == 1 ? __hybrid_ror8(x,shift) : sizeof(x) == 2 ? __hybrid_ror16(x,shift) : __hybrid_ror32(x,shift))
#elif !defined(__UINT128_TYPE__)
#define __hybrid_rol(x,shift) (sizeof(x) == 1 ? __hybrid_rol8(x,shift) : sizeof(x) == 2 ? __hybrid_rol16(x,shift) : sizeof(x) == 4 ? __hybrid_rol32(x,shift) : __hybrid_rol64(x,shift))
#define __hybrid_ror(x,shift) (sizeof(x) == 1 ? __hybrid_ror8(x,shift) : sizeof(x) == 2 ? __hybrid_ror16(x,shift) : sizeof(x) == 4 ? __hybrid_ror32(x,shift) : __hybrid_ror64(x,shift))
#else
#define __hybrid_rol(x,shift) (sizeof(x) == 1 ? __hybrid_rol8(x,shift) : sizeof(x) == 2 ? __hybrid_rol16(x,shift) : sizeof(x) == 4 ? __hybrid_rol32(x,shift) : sizeof(x) == 8 ? __hybrid_rol64(x,shift) : __hybrid_rol128(x,shift))
#define __hybrid_ror(x,shift) (sizeof(x) == 1 ? __hybrid_ror8(x,shift) : sizeof(x) == 2 ? __hybrid_ror16(x,shift) : sizeof(x) == 4 ? __hybrid_ror32(x,shift) : sizeof(x) == 8 ? __hybrid_ror64(x,shift) : __hybrid_ror128(x,shift))
#endif
#endif /* __NO_builtin_choose_expr */


__DECL_END

#endif /* !__GUARD_HYBRID___ROTATE_H */
