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
#ifndef _BITS_OS_KOS_IFMAP_H
#define _BITS_OS_KOS_IFMAP_H 1

#include <__stdinc.h>

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("mem_start")
#pragma push_macro("mem_end")
#pragma push_macro("base_addr")
#pragma push_macro("irq")
#pragma push_macro("dma")
#pragma push_macro("port")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef mem_start
#undef mem_end
#undef base_addr
#undef irq
#undef dma
#undef port
struct ifmap {
	__ULONGPTR_TYPE__ mem_start;
	__ULONGPTR_TYPE__ mem_end;
	__UINT16_TYPE__   base_addr;
	__UINT8_TYPE__    irq;
	__UINT8_TYPE__    dma;
	__UINT8_TYPE__    port;
	__UINT8_TYPE__    __ifm_pad[3]; /* 3 bytes spare */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("port")
#pragma pop_macro("dma")
#pragma pop_macro("irq")
#pragma pop_macro("base_addr")
#pragma pop_macro("mem_end")
#pragma pop_macro("mem_start")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_IFMAP_H */
