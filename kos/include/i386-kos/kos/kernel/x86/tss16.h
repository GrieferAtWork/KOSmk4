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
#ifndef _I386_KOS_KOS_KERNEL_X86_TSS16_H
#define _I386_KOS_KOS_KERNEL_X86_TSS16_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

#define OFFSET_TSS16_LINK  0
#define OFFSET_TSS16_SP0   2
#define OFFSET_TSS16_SS0   4
#define OFFSET_TSS16_SP1   6
#define OFFSET_TSS16_SS1   8
#define OFFSET_TSS16_SP2   10
#define OFFSET_TSS16_SS2   12
#define OFFSET_TSS16_IP    14
#define OFFSET_TSS16_FLAGS 16
#define OFFSET_TSS16_AX    18
#define OFFSET_TSS16_CX    20
#define OFFSET_TSS16_DX    22
#define OFFSET_TSS16_BX    24
#define OFFSET_TSS16_SP    26
#define OFFSET_TSS16_BP    28
#define OFFSET_TSS16_SI    30
#define OFFSET_TSS16_DI    32
#define OFFSET_TSS16_ES    34
#define OFFSET_TSS16_CS    36
#define OFFSET_TSS16_SS    38
#define OFFSET_TSS16_DS    40
#define OFFSET_TSS16_LDTR  42
#define SIZEOF_TSS16       44
#define ALIGNOF_TSS16      2

#ifdef __CC__
__DECL_BEGIN

struct __ATTR_ALIGNED(ALIGNOF_TSS16) __ATTR_PACKED tss16 /*[PREFIX(t_)]*/ {
	__UINT16_TYPE__   t_link;
	__UINT16_TYPE__   t_sp0;
	__UINT16_TYPE__   t_ss0;
	__UINT16_TYPE__   t_sp1;
	__UINT16_TYPE__   t_ss1;
	__UINT16_TYPE__   t_sp2;
	__UINT16_TYPE__   t_ss2;
	__UINT16_TYPE__   t_ip;
	__UINT16_TYPE__   t_flags;
	__UINT16_TYPE__   t_ax;
	__UINT16_TYPE__   t_cx;
	__UINT16_TYPE__   t_dx;
	__UINT16_TYPE__   t_bx;
	__UINT16_TYPE__   t_sp;
	__UINT16_TYPE__   t_bp;
	__UINT16_TYPE__   t_si;
	__UINT16_TYPE__   t_di;
	__UINT16_TYPE__   t_es;
	__UINT16_TYPE__   t_cs;
	__UINT16_TYPE__   t_ss;
	__UINT16_TYPE__   t_ds;
	__UINT16_TYPE__   t_ldtr;
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_KERNEL_X86_TSS16_H */
