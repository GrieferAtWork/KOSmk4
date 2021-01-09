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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/[...]/sys/io.h) */
/* (#) Portability: diet libc     (/include/sys/io.h) */
/* (#) Portability: musl libc     (/include/sys/io.h) */
#ifndef _SYS_IO_H
#define _SYS_IO_H 1

#include <__stdinc.h>
#include <features.h> /* __USE_KOS_KERNEL */

#include <hybrid/typecore.h>

#include <sys/perm.h>

#ifndef __SIZEOF_PORT_T__
#define __SIZEOF_PORT_T__ 2
#endif /* !__SIZEOF_PORT_T__ */

#ifndef __IOPORT_T
#if __SIZEOF_PORT_T__ == 2
#define __IOPORT_T __UINT16_TYPE__
#elif __SIZEOF_PORT_T__ == 4
#define __IOPORT_T __UINT32_TYPE__
#elif __SIZEOF_PORT_T__ == 8
#define __IOPORT_T __UINT64_TYPE__
#elif __SIZEOF_PORT_T__ == 1
#define __IOPORT_T __UINT8_TYPE__
#else /* __SIZEOF_PORT_T__ == ... */
#error "Unsupported `__SIZEOF_PORT_T__'"
#endif /* __SIZEOF_PORT_T__ != ... */
#endif /* !__IOPORT_T */

#ifndef __IOPORT
#define __IOPORT(x) (__CCAST(__IOPORT_T) x)
#endif /* !__IOPORT */


#ifdef __CC__
__SYSDECL_BEGIN

/* Prototypes for low-level I/O functions. Usually, architectures will override
 * this entire header in order to provide I/O port read/write primitives in the
 * form of FORCELOCAL-functions.
 * The prototypes in this header are mainly meant to describe the signatures that
 * architecture-specific implementations will mirror. */

extern __UINT8_TYPE__ __NOTHROW(inb)(__IOPORT_T __port);
extern __UINT16_TYPE__ __NOTHROW(inw)(__IOPORT_T __port);
extern __UINT32_TYPE__ __NOTHROW(inl)(__IOPORT_T __port);

extern __UINT8_TYPE__ __NOTHROW(inb_p)(__IOPORT_T __port);
extern __UINT16_TYPE__ __NOTHROW(inw_p)(__IOPORT_T __port);
extern __UINT32_TYPE__ __NOTHROW(inl_p)(__IOPORT_T __port);

extern void __NOTHROW(insb)(__IOPORT_T __port, void *__buf, __SIZE_TYPE__ __n_bytes);
extern void __NOTHROW(insw)(__IOPORT_T __port, void *__buf, __SIZE_TYPE__ __n_words);
extern void __NOTHROW(insl)(__IOPORT_T __port, void *__buf, __SIZE_TYPE__ __n_dwords);

extern void __NOTHROW(outsb)(__IOPORT_T __port, void const *__buf, __SIZE_TYPE__ __n_bytes);
extern void __NOTHROW(outsw)(__IOPORT_T __port, void const *__buf, __SIZE_TYPE__ __n_words);
extern void __NOTHROW(outsl)(__IOPORT_T __port, void const *__buf, __SIZE_TYPE__ __n_dwords);

#ifdef __USE_KOS_ALTERATIONS
extern void __NOTHROW(outb)(__IOPORT_T __port, __UINT8_TYPE__ __val);
extern void __NOTHROW(outw)(__IOPORT_T __port, __UINT16_TYPE__ __val);
extern void __NOTHROW(outl)(__IOPORT_T __port, __UINT32_TYPE__ __val);
extern void __NOTHROW(outb_p)(__IOPORT_T __port, __UINT8_TYPE__ __val);
extern void __NOTHROW(outw_p)(__IOPORT_T __port, __UINT16_TYPE__ __val);
extern void __NOTHROW(outl_p)(__IOPORT_T __port, __UINT32_TYPE__ __val);
#else /* __USE_KOS_ALTERATIONS */
extern void __NOTHROW(outb)(__UINT8_TYPE__ __val, __IOPORT_T __port);
extern void __NOTHROW(outw)(__UINT16_TYPE__ __val, __IOPORT_T __port);
extern void __NOTHROW(outl)(__UINT32_TYPE__ __val, __IOPORT_T __port);
extern void __NOTHROW(outb_p)(__UINT8_TYPE__ __val, __IOPORT_T __port);
extern void __NOTHROW(outw_p)(__UINT16_TYPE__ __val, __IOPORT_T __port);
extern void __NOTHROW(outl_p)(__UINT32_TYPE__ __val, __IOPORT_T __port);
#endif /* !__USE_KOS_ALTERATIONS */

#ifdef __USE_KOS_KERNEL
extern void __NOTHROW(io_delay)(void);
#endif /* __USE_KOS_KERNEL */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_IO_H */
