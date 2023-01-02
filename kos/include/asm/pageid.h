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
#ifndef _ASM_PAGEID_H
#define _ASM_PAGEID_H 1

/* Convert  virtual memory addresses  to/form their compressed variants
 * in the form of Page-IDs, where  a Page-ID strips away any  redundant
 * address bits, as well as the unpagable lower `__ARCH_PAGESHIFT' bits
 * The  idea of this mechanism is to use it to define a special address
 * space  mechanism that can be used for encoding/decoding keys for use
 * with an address tree with the purpose of associating additional data
 * with specific addresses/address-ranges.
 * >> __ARCH_PAGEID_TYPE pageid  = __ARCH_PAGEID_ENCODE(addr);
 * >> void              *newaddr = __ARCH_PAGEID_DECODE(pageid);
 * Note that following  an encode+decode, the  resulting address is  always
 * floor-aligned  by a  multiple of  `__ARCH_PAGESIZE' (if  defined; if not
 * defined,  this mechanism is  unavailable), and may  not necessary be the
 * same as the floor-page-aligned value  of the original address, as  other
 * redundant  address may have  been stripped (an  example of this behavior
 * would be the  address-space sign-extension found  on x86_64  processors,
 * where these macros simply strip off redundant sign-bits during encoding,
 * but re-add then during decoding)
 * Additionally, the following constants are defined:
 *   - __ARCH_PAGEID_TYPE_SIZEOF: The size of `__ARCH_PAGEID_TYPE' in bytes
 *   - __ARCH_PAGEID_TYPE:        The smallest __UINTnn_TYPE__ such that `nn >= __ARCH_PAGEID_BITS'
 *   - __ARCH_PAGEID_BITS:        The number of bits used by a pageid (note that a pageid is always unsigned)
 *   - __ARCH_PAGEID_MAX:         The max possible page ID (`== (1 << __ARCH_PAGEID_BITS) - 1')
 */

#ifndef __ARCH_PAGEID_BITS
#include <asm/pagesize.h>
#ifdef __ARCH_PAGESHIFT
#include <hybrid/typecore.h>
#define __ARCH_PAGEID_BITS ((__SIZEOF_POINTER__ * 8) - __ARCH_PAGESHIFT)
#endif /* __ARCH_PAGESHIFT */
#endif /* !__ARCH_PAGEID_BITS */

#if !defined(__ARCH_PAGEID_MAX) && defined(__ARCH_PAGEID_BITS)
#include <hybrid/typecore.h>
#define __ARCH_PAGEID_MAX ((__CCAST(__UINTPTR_TYPE__) 1 << __ARCH_PAGEID_BITS) - 1)
#endif /* !__ARCH_PAGEID_MAX */

#if !defined(__ARCH_PAGEID_TYPE_SIZEOF) && defined(__ARCH_PAGEID_BITS)
#if __ARCH_PAGEID_BITS <= 8
#define __ARCH_PAGEID_TYPE_SIZEOF 1
#elif __ARCH_PAGEID_BITS <= 16
#define __ARCH_PAGEID_TYPE_SIZEOF 2
#elif __ARCH_PAGEID_BITS <= 32
#define __ARCH_PAGEID_TYPE_SIZEOF 4
#elif __ARCH_PAGEID_BITS <= 64
#define __ARCH_PAGEID_TYPE_SIZEOF 8
#else /* __ARCH_PAGEID_BITS <= ... */
#error "`__ARCH_PAGEID_BITS' is too large"
#endif /* __ARCH_PAGEID_BITS > ... */
#endif /* !__ARCH_PAGEID_TYPE_SIZEOF */

#if !defined(__ARCH_PAGEID_TYPE) && defined(__ARCH_PAGEID_TYPE_SIZEOF)
#include <hybrid/typecore.h>
#if __ARCH_PAGEID_TYPE_SIZEOF == 1
#define __ARCH_PAGEID_TYPE __UINT8_TYPE__
#elif __ARCH_PAGEID_TYPE_SIZEOF == 2
#define __ARCH_PAGEID_TYPE __UINT16_TYPE__
#elif __ARCH_PAGEID_TYPE_SIZEOF == 4
#define __ARCH_PAGEID_TYPE __UINT32_TYPE__
#elif __ARCH_PAGEID_TYPE_SIZEOF == 8
#define __ARCH_PAGEID_TYPE __UINT64_TYPE__
#endif /* __ARCH_PAGEID_TYPE_SIZEOF == ... */
#endif /* !__ARCH_PAGEID_TYPE */

#ifndef __ARCH_PAGEID_ENCODE
#include <asm/pagesize.h>
#ifdef __ARCH_PAGESHIFT
#include <hybrid/typecore.h>
#if __ARCH_PAGEID_TYPE_SIZEOF >= __SIZEOF_POINTER__
#define __ARCH_PAGEID_ENCODE(addr)   (__CCAST(__ARCH_PAGEID_TYPE)((addr) >> __ARCH_PAGESHIFT))
#else /* __ARCH_PAGEID_TYPE_SIZEOF >= __SIZEOF_POINTER__ */
#define __ARCH_PAGEID_ENCODE(addr)   (__CCAST(__ARCH_PAGEID_TYPE)(__CCAST(__UINTPTR_TYPE__)(addr) >> __ARCH_PAGESHIFT))
#endif /* __ARCH_PAGEID_TYPE_SIZEOF < __SIZEOF_POINTER__ */
#define __ARCH_PAGEID_DECODE(pageid) (__CCAST(void *)(__CCAST(__ARCH_PAGEID_TYPE)(pageid) << __ARCH_PAGESHIFT))
#endif /* __ARCH_PAGESHIFT */
#endif /* !__ARCH_PAGEID_ENCODE */

#endif /* !_ASM_PAGEID_H */
