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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/[...]/sys/io.h) */
/* (#) Portability: diet libc     (/include/sys/io.h) */
/* (#) Portability: musl libc     (/include/sys/io.h) */
#ifndef _SYS_IO_H
#define _SYS_IO_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h> /* __USE_KOS_KERNEL */

#include <hybrid/typecore.h>

#include <bits/typesizes.h> /* For `__SIZEOF_PORT_T__' */
#include <sys/perm.h>

#ifndef __port_t
#ifdef __SIZEOF_PORT_T__
#if __SIZEOF_PORT_T__ == 2
#define __port_t __UINT16_TYPE__
#elif __SIZEOF_PORT_T__ == 4
#define __port_t __UINT32_TYPE__
#elif __SIZEOF_PORT_T__ == 8
#define __port_t __UINT64_TYPE__
#elif __SIZEOF_PORT_T__ == 1
#define __port_t __UINT8_TYPE__
#else /* __SIZEOF_PORT_T__ == ... */
#error "Unsupported `__SIZEOF_PORT_T__'"
#endif /* __SIZEOF_PORT_T__ != ... */
#endif /* __SIZEOF_PORT_T__ */
#endif /* !__port_t */

#ifdef __port_t
#ifndef __IOPORT
#define __IOPORT(x) (__CCAST(__port_t) x)
#endif /* !__IOPORT */
#endif /* __port_t */

#ifndef __NOTHROW_KRN
#ifdef __KERNEL__
/* In kernel-space, I/O instruction should never fault. */
#define __NOTHROW_KRN __NOTHROW
#else /* __KERNEL__ */
/* In user-space, I/O instruction may fault due to lack
 * of access permissions. - As such, they can  generate
 * NonCalleXceptions, meaning we must use NOTHROW_NCX */
#define __NOTHROW_KRN __NOTHROW_NCX
#endif /* !__KERNEL__ */
#endif /* !__NOTHROW_KRN */

#ifdef __CC__
__SYSDECL_BEGIN

/* Prototypes for low-level I/O functions. Usually, architectures will override
 * this entire header in order to provide I/O port read/write primitives in the
 * form of FORCELOCAL-functions.
 * The prototypes in this header are mainly meant to describe the signatures that
 * architecture-specific implementations will mirror. */

#ifdef __port_t
__CDECLARE(,__UINT8_TYPE__,__NOTHROW_KRN,inb,(__port_t __port),(__port))
__CDECLARE(,__UINT16_TYPE__,__NOTHROW_KRN,inw,(__port_t __port),(__port))
__CDECLARE(,__UINT32_TYPE__,__NOTHROW_KRN,inl,(__port_t __port),(__port))
__CDECLARE(,__UINT8_TYPE__,__NOTHROW_KRN,inb_p,(__port_t __port),(__port))
__CDECLARE(,__UINT16_TYPE__,__NOTHROW_KRN,inw_p,(__port_t __port),(__port))
__CDECLARE(,__UINT32_TYPE__,__NOTHROW_KRN,inl_p,(__port_t __port),(__port))
__CDECLARE_VOID(__ATTR_NONNULL((2)),__NOTHROW_NCX,insb,(__port_t __port, void *__buf, __SIZE_TYPE__ __n_bytes),(__port,__buf,__n_bytes))
__CDECLARE_VOID(__ATTR_NONNULL((2)),__NOTHROW_NCX,insw,(__port_t __port, void *__buf, __SIZE_TYPE__ __n_words),(__port,__buf,__n_words))
__CDECLARE_VOID(__ATTR_NONNULL((2)),__NOTHROW_NCX,insl,(__port_t __port, void *__buf, __SIZE_TYPE__ __n_dwords),(__port,__buf,__n_dwords))
__CDECLARE_VOID(__ATTR_NONNULL((2)),__NOTHROW_NCX,outsb,(__port_t __port, void const *__buf, __SIZE_TYPE__ __n_bytes),(__port,__buf,__n_bytes))
__CDECLARE_VOID(__ATTR_NONNULL((2)),__NOTHROW_NCX,outsw,(__port_t __port, void const *__buf, __SIZE_TYPE__ __n_words),(__port,__buf,__n_words))
__CDECLARE_VOID(__ATTR_NONNULL((2)),__NOTHROW_NCX,outsl,(__port_t __port, void const *__buf, __SIZE_TYPE__ __n_dwords),(__port,__buf,__n_dwords))

#ifdef __USE_KOS_ALTERATIONS
__CREDIRECT_VOID(,__NOTHROW_KRN,__abi_outb,(__UINT8_TYPE__ __val, __port_t __port),outb,(__val,__port))
__CREDIRECT_VOID(,__NOTHROW_KRN,__abi_outw,(__UINT16_TYPE__ __val, __port_t __port),outw,(__val,__port))
__CREDIRECT_VOID(,__NOTHROW_KRN,__abi_outl,(__UINT32_TYPE__ __val, __port_t __port),outl,(__val,__port))
__CREDIRECT_VOID(,__NOTHROW_KRN,__abi_outb_p,(__UINT8_TYPE__ __val, __port_t __port),outb_p,(__val,__port))
__CREDIRECT_VOID(,__NOTHROW_KRN,__abi_outw_p,(__UINT16_TYPE__ __val, __port_t __port),outw_p,(__val,__port))
__CREDIRECT_VOID(,__NOTHROW_KRN,__abi_outl_p,(__UINT32_TYPE__ __val, __port_t __port),outl_p,(__val,__port))
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_KRN(__LIBCCALL outb)(__port_t __port, __UINT8_TYPE__ __val) { __abi_outb(__val, __port); }
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_KRN(__LIBCCALL outw)(__port_t __port, __UINT16_TYPE__ __val) { __abi_outw(__val, __port); }
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_KRN(__LIBCCALL outl)(__port_t __port, __UINT32_TYPE__ __val) { __abi_outl(__val, __port); }
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_KRN(__LIBCCALL outb_p)(__port_t __port, __UINT8_TYPE__ __val) { __abi_outb_p(__val, __port); }
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_KRN(__LIBCCALL outw_p)(__port_t __port, __UINT16_TYPE__ __val) { __abi_outw_p(__val, __port); }
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_KRN(__LIBCCALL outl_p)(__port_t __port, __UINT32_TYPE__ __val) { __abi_outl_p(__val, __port); }
#else /* __USE_KOS_ALTERATIONS */
__CDECLARE_VOID(,__NOTHROW_KRN,outb,(__UINT8_TYPE__ __val, __port_t __port),(__val,__port))
__CDECLARE_VOID(,__NOTHROW_KRN,outw,(__UINT16_TYPE__ __val, __port_t __port),(__val,__port))
__CDECLARE_VOID(,__NOTHROW_KRN,outl,(__UINT32_TYPE__ __val, __port_t __port),(__val,__port))
__CDECLARE_VOID(,__NOTHROW_KRN,outb_p,(__UINT8_TYPE__ __val, __port_t __port),(__val,__port))
__CDECLARE_VOID(,__NOTHROW_KRN,outw_p,(__UINT16_TYPE__ __val, __port_t __port),(__val,__port))
__CDECLARE_VOID(,__NOTHROW_KRN,outl_p,(__UINT32_TYPE__ __val, __port_t __port),(__val,__port))
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* __port_t */

#ifdef __USE_KOS_KERNEL
__CDECLARE_VOID(,__NOTHROW_KRN,io_delay,(void),())
#endif /* __USE_KOS_KERNEL */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_IO_H */
