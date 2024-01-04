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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/[...]/sys/io.h) */
/* (#) Portability: diet libc     (/include/sys/io.h) */
/* (#) Portability: musl libc     (/include/sys/io.h) */
#ifndef _I386_KOS_SYS_IO_H
#define _I386_KOS_SYS_IO_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/typesizes.h> /* __SIZEOF_PORT_T__ */
#include <sys/perm.h>

#ifndef __SIZEOF_PORT_T__
#define __SIZEOF_PORT_T__ 2
#endif /* !__SIZEOF_PORT_T__ */

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

#ifndef __COMPILER_ASM_BUFFER
#define __COMPILER_ASM_BUFFER(T, s, p) (*(T *)(p))
#endif /* !__COMPILER_ASM_BUFFER */

#ifndef __port_t
#if __SIZEOF_PORT_T__ == 2
#define __port_t __UINT16_TYPE__
#elif __SIZEOF_PORT_T__ == 1
#define __port_t __UINT8_TYPE__
#elif __SIZEOF_PORT_T__ == 4
#define __port_t __UINT32_TYPE__
#elif __SIZEOF_PORT_T__ == 8
#define __port_t __UINT64_TYPE__
#else /* __SIZEOF_PORT_T__ == ... */
#include <bits/types.h>
#ifndef __port_t
#define __port_t __CRT_PRIVATE_ULNG(__SIZEOF_PORT_T__)
#endif /* !__port_t */
#endif /* __SIZEOF_PORT_T__ != ... */
#endif /* !__port_t */
#ifndef __IOPORT
#define __IOPORT(x) ((__port_t)x)
#endif /* !__IOPORT */
#ifndef __MEMPORT_T
#define __MEMPORT_T __UINTPTR_TYPE__
#endif /* !__MEMPORT_T */

#ifdef __INTELLISENSE__

__UINT8_TYPE__ __NOTHROW_KRN(inb)(__port_t __port);
__UINT16_TYPE__ __NOTHROW_KRN(inw)(__port_t __port);
__UINT32_TYPE__ __NOTHROW_KRN(inl)(__port_t __port);

__UINT8_TYPE__ __NOTHROW_KRN(inb_p)(__port_t __port);
__UINT16_TYPE__ __NOTHROW_KRN(inw_p)(__port_t __port);
__UINT32_TYPE__ __NOTHROW_KRN(inl_p)(__port_t __port);

void __NOTHROW_NCX(insb)(__port_t __port, void *__buf, __SIZE_TYPE__ __n_bytes);
void __NOTHROW_NCX(insw)(__port_t __port, void *__buf, __SIZE_TYPE__ __n_words);
void __NOTHROW_NCX(insl)(__port_t __port, void *__buf, __SIZE_TYPE__ __n_dwords);

void __NOTHROW_NCX(outsb)(__port_t __port, void const *__buf, __SIZE_TYPE__ __n_bytes);
void __NOTHROW_NCX(outsw)(__port_t __port, void const *__buf, __SIZE_TYPE__ __n_words);
void __NOTHROW_NCX(outsl)(__port_t __port, void const *__buf, __SIZE_TYPE__ __n_dwords);

#ifdef __USE_KOS_ALTERATIONS
void __NOTHROW_KRN(outb)(__port_t __port, __UINT8_TYPE__ __val);
void __NOTHROW_KRN(outw)(__port_t __port, __UINT16_TYPE__ __val);
void __NOTHROW_KRN(outl)(__port_t __port, __UINT32_TYPE__ __val);
void __NOTHROW_KRN(outb_p)(__port_t __port, __UINT8_TYPE__ __val);
void __NOTHROW_KRN(outw_p)(__port_t __port, __UINT16_TYPE__ __val);
void __NOTHROW_KRN(outl_p)(__port_t __port, __UINT32_TYPE__ __val);
#else /* __USE_KOS_ALTERATIONS */
void __NOTHROW_KRN(outb)(__UINT8_TYPE__ __val, __port_t __port);
void __NOTHROW_KRN(outw)(__UINT16_TYPE__ __val, __port_t __port);
void __NOTHROW_KRN(outl)(__UINT32_TYPE__ __val, __port_t __port);
void __NOTHROW_KRN(outb_p)(__UINT8_TYPE__ __val, __port_t __port);
void __NOTHROW_KRN(outw_p)(__UINT16_TYPE__ __val, __port_t __port);
void __NOTHROW_KRN(outl_p)(__UINT32_TYPE__ __val, __port_t __port);
#endif /* !__USE_KOS_ALTERATIONS */

#ifdef __USE_KOS_KERNEL
void __NOTHROW_KRN(io_delay)(void);
#endif /* __USE_KOS_KERNEL */

#elif defined(__COMPILER_HAVE_GCC_ASM)
/* Using the same trick as the linux kernel... */
#define __IO_SLOWDOWN_IMPL "\noutb %%al,$0x80"
#if 0
#define __IO_SLOWDOWN  __IO_SLOWDOWN_IMPL \
                       __IO_SLOWDOWN_IMPL \
                       __IO_SLOWDOWN_IMPL
#else
#define __IO_SLOWDOWN  __IO_SLOWDOWN_IMPL
#endif


#define __PRIVATE_DEFINE_IO_IN(T, sfx, r, n, count)                          \
	__FORCELOCAL __ATTR_ARTIFICIAL T                                         \
	__NOTHROW_KRN(in##sfx)(__port_t __port) {                                \
		__register T __rv;                                                   \
		__asm__ __volatile__("in" #sfx " %w1, %0"                            \
		                     : "=a" (__rv)                                   \
		                     : "Nd" (__port));                               \
		return __rv;                                                         \
	}                                                                        \
	__FORCELOCAL __ATTR_ARTIFICIAL T                                         \
	__NOTHROW_KRN(in##sfx##_p)(__port_t __port) {                            \
		__register T __rv;                                                   \
		__asm__ __volatile__("in" #sfx " %w1, %0" __IO_SLOWDOWN              \
		                     : "=a" (__rv)                                   \
		                     : "Nd" (__port));                               \
		return __rv;                                                         \
	}                                                                        \
	__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void                  \
	__NOTHROW_NCX(ins##sfx)(__port_t __port,                                 \
	                        void *__buf,                                     \
	                        __SIZE_TYPE__ count) {                           \
		__asm__ __volatile__("rep; ins" #sfx                                 \
		                     : "=D" (__buf)                                  \
		                     , "=c" (count)                                  \
		                     , "=m" (__COMPILER_ASM_BUFFER(T, count, __buf)) \
		                     : "d" (__port)                                  \
		                     , "0" (__buf)                                   \
		                     , "1" (count));                                 \
	}

#ifdef __USE_KOS_ALTERATIONS
#define __PRIVATE_DEFINE_IO_OUT(T, sfx, s1, r, n, count)                      \
	__FORCELOCAL __ATTR_ARTIFICIAL void                                       \
	__NOTHROW_KRN(out##sfx)(__port_t __port, T __val) {                       \
		__asm__ __volatile__("out" #sfx " %" s1 "0, %w1"                      \
		                     :                                                \
		                     : "a" (__val)                                    \
		                     , "Nd" (__port));                                \
	}                                                                         \
	__FORCELOCAL __ATTR_ARTIFICIAL void                                       \
	__NOTHROW_KRN(out##sfx##_p)(__port_t __port, T __val) {                   \
		__asm__ __volatile__("out" #sfx " %" s1 "0, %w1" __IO_SLOWDOWN        \
		                     :                                                \
		                     : "a" (__val)                                    \
		                     , "Nd" (__port));                                \
	}                                                                         \
	__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void                   \
	__NOTHROW_NCX(outs##sfx)(__port_t __port,                                 \
	                         void const *__buf,                               \
	                         __SIZE_TYPE__ count) {                           \
		__asm__ __volatile__("rep; outs" #sfx                                 \
		                     : "=S" (__buf)                                   \
		                     , "=c" (count)                                   \
		                     : "d" (__port)                                   \
		                     , "0" (__buf)                                    \
		                     , "1" (count)                                    \
		                     , "m" (__COMPILER_ASM_BUFFER(T, count, __buf))); \
	}
#else /* __USE_KOS_ALTERATIONS */
#define __PRIVATE_DEFINE_IO_OUT(T, sfx, s1, r, n, count)                      \
	__FORCELOCAL __ATTR_ARTIFICIAL void                                       \
	__NOTHROW_KRN(out##sfx)(T __val, __port_t __port) {                       \
		__asm__ __volatile__("out" #sfx " %" s1 "0, %w1"                      \
		                     :                                                \
		                     : "a" (__val)                                    \
		                     , "Nd" (__port));                                \
	}                                                                         \
	__FORCELOCAL __ATTR_ARTIFICIAL void                                       \
	__NOTHROW_KRN(out##sfx##_p)(T __val, __port_t __port) {                   \
		__asm__ __volatile__("out" #sfx " %" s1 "0, %w1" __IO_SLOWDOWN        \
		                     :                                                \
		                     : "a" (__val)                                    \
		                     , "Nd" (__port));                                \
	}                                                                         \
	__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void                   \
	__NOTHROW_NCX(outs##sfx)(__port_t __port,                                 \
	                         void const *__buf,                               \
	                         __SIZE_TYPE__ count) {                           \
		__asm__ __volatile__("rep; outs" #sfx                                 \
		                     : "=S" (__buf)                                   \
		                     , "=c" (count)                                   \
		                     : "d" (__port)                                   \
		                     , "0" (__buf)                                    \
		                     , "1" (count)                                    \
		                     , "m" (__COMPILER_ASM_BUFFER(T, count, __buf))); \
	}
#endif /* !__USE_KOS_ALTERATIONS */

__PRIVATE_DEFINE_IO_IN(__UINT8_TYPE__, b, "q", 1, __n_bytes)
__PRIVATE_DEFINE_IO_IN(__UINT16_TYPE__, w, "r", 2, __n_words)
__PRIVATE_DEFINE_IO_IN(__UINT32_TYPE__, l, "r", 4, __n_dwords)
__PRIVATE_DEFINE_IO_OUT(__UINT8_TYPE__, b, "b", "q", 1, __n_bytes)
__PRIVATE_DEFINE_IO_OUT(__UINT16_TYPE__, w, "w", "r", 2, __n_words)
__PRIVATE_DEFINE_IO_OUT(__UINT32_TYPE__, l, "", "r", 4, __n_dwords)
#undef __PRIVATE_DEFINE_IO_OUT
#undef __PRIVATE_DEFINE_IO_IN

#if defined(__USE_KOS_KERNEL)
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_KRN(__LIBCCALL io_delay)(void) {
	__asm__ __volatile__(__IO_SLOWDOWN
	                     :
	                     :
	                     : "memory");
}
#endif /* __USE_KOS_KERNEL */
#else /* GCC... */

__NAMESPACE_INT_BEGIN
extern __UINT8_TYPE__ __NOTHROW_KRN(__cdecl __inbyte)(__port_t __port);
extern __UINT16_TYPE__ __NOTHROW_KRN(__cdecl __inword)(__port_t __port);
extern __ULONG32_TYPE__ __NOTHROW_KRN(__cdecl __indword)(__port_t __port);
extern void __NOTHROW_NCX(__cdecl __inbytestring)(__port_t __port, __UINT8_TYPE__ *__addr, __LONGSIZE_TYPE__ __n_bytes);
extern void __NOTHROW_NCX(__cdecl __inwordstring)(__port_t __port, __UINT16_TYPE__ *__addr, __LONGSIZE_TYPE__ __n_words);
extern void __NOTHROW_NCX(__cdecl __indwordstring)(__port_t __port, __ULONG32_TYPE__ *__addr, __LONGSIZE_TYPE__ __n_dwords);
extern void __NOTHROW_KRN(__cdecl __outbyte)(__port_t __port, __UINT8_TYPE__ __val);
extern void __NOTHROW_KRN(__cdecl __outword)(__port_t __port, __UINT16_TYPE__ __val);
extern void __NOTHROW_KRN(__cdecl __outdword)(__port_t __port, __ULONG32_TYPE__ __val);
extern void __NOTHROW_NCX(__cdecl __outbytestring)(__port_t __port, __UINT8_TYPE__ *__addr, __LONGSIZE_TYPE__ __n_bytes);
extern void __NOTHROW_NCX(__cdecl __outwordstring)(__port_t __port, __UINT16_TYPE__ *__addr, __LONGSIZE_TYPE__ __n_words);
extern void __NOTHROW_NCX(__cdecl __outdwordstring)(__port_t __port, __ULONG32_TYPE__ *__addr, __LONGSIZE_TYPE__ __n_dwords);
#pragma intrinsic(__inbyte)
#pragma intrinsic(__inword)
#pragma intrinsic(__indword)
#pragma intrinsic(__inbytestring)
#pragma intrinsic(__inwordstring)
#pragma intrinsic(__indwordstring)
#pragma intrinsic(__outbyte)
#pragma intrinsic(__outword)
#pragma intrinsic(__outdword)
#pragma intrinsic(__outbytestring)
#pragma intrinsic(__outwordstring)
#pragma intrinsic(__outdwordstring)
__NAMESPACE_INT_END

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("out")
#pragma push_macro("al")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef out
#undef al

/* Using the same trick as the linux kernel... */
#ifdef __x86_64__
#define __IO_SLOWDOWN_IMPL (__NAMESPACE_INT_SYM __outbyte)(0x80, 0);
#else /* __x86_64__ */
#define __IO_SLOWDOWN_IMPL __asm { out 0x80, al }
#endif /* !__x86_64__ */
#if 0
#define __IO_SLOWDOWN  \
	__IO_SLOWDOWN_IMPL \
	__IO_SLOWDOWN_IMPL \
	__IO_SLOWDOWN_IMPL
#else
#define __IO_SLOWDOWN  __IO_SLOWDOWN_IMPL
#endif

__FORCELOCAL __ATTR_ARTIFICIAL __UINT8_TYPE__
__NOTHROW_KRN(inb)(__port_t __port) {
	return (__NAMESPACE_INT_SYM __inbyte)(__port);
}

__FORCELOCAL __ATTR_ARTIFICIAL __UINT16_TYPE__
__NOTHROW_KRN(inw)(__port_t __port) {
	return (__NAMESPACE_INT_SYM __inword)(__port);
}

__FORCELOCAL __ATTR_ARTIFICIAL __UINT32_TYPE__
__NOTHROW_KRN(inl)(__port_t __port) {
	return (__UINT32_TYPE__)(__NAMESPACE_INT_SYM __indword)(__port);
}

__FORCELOCAL __ATTR_ARTIFICIAL __UINT8_TYPE__
__NOTHROW_KRN(inb_p)(__port_t __port) {
	__UINT8_TYPE__ __res;
	__res = (__NAMESPACE_INT_SYM __inbyte)(__port);
	__IO_SLOWDOWN
	return __res;
}

__FORCELOCAL __ATTR_ARTIFICIAL __UINT16_TYPE__
__NOTHROW_KRN(inw_p)(__port_t __port) {
	__UINT16_TYPE__ __res;
	__res = (__NAMESPACE_INT_SYM __inword)(__port);
	__IO_SLOWDOWN
	return __res;
}

__FORCELOCAL __ATTR_ARTIFICIAL __UINT32_TYPE__
__NOTHROW_KRN(inl_p)(__port_t __port) {
	__UINT32_TYPE__ __res;
	__res = (__UINT32_TYPE__)(__NAMESPACE_INT_SYM __indword)(__port);
	__IO_SLOWDOWN
	return __res;
}

__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(insb)(__port_t __port, void *__buf, __SIZE_TYPE__ __n_bytes) {
	(__NAMESPACE_INT_SYM __inbytestring)(__port, (__UINT8_TYPE__ *)__buf, (__LONGSIZE_TYPE__)__n_bytes);
}

__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(insw)(__port_t __port, void *__buf, __SIZE_TYPE__ __n_words) {
	(__NAMESPACE_INT_SYM __inwordstring)(__port, (__UINT16_TYPE__ *)__buf, (__LONGSIZE_TYPE__)__n_words);
}

__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(insl)(__port_t __port, void *__buf, __SIZE_TYPE__ __n_dwords) {
	(__NAMESPACE_INT_SYM __indwordstring)(__port, (__ULONG32_TYPE__ *)__buf, (__LONGSIZE_TYPE__)__n_dwords);
}

#ifdef __USE_KOS_ALTERATIONS
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_KRN(outb)(__port_t __port, __UINT8_TYPE__ __val) {
	(__NAMESPACE_INT_SYM __outbyte)(__port, __val);
}

__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_KRN(outw)(__port_t __port, __UINT16_TYPE__ __val) {
	(__NAMESPACE_INT_SYM __outword)(__port, __val);
}

__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_KRN(outl)(__port_t __port, __UINT32_TYPE__ __val) {
	(__NAMESPACE_INT_SYM __outdword)(__port, (__ULONG32_TYPE__)__val);
}

__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_KRN(outb_p)(__port_t __port, __UINT8_TYPE__ __val) {
	(__NAMESPACE_INT_SYM __outbyte)(__port, __val);
	__IO_SLOWDOWN
}

__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_KRN(outw_p)(__port_t __port, __UINT16_TYPE__ __val) {
	(__NAMESPACE_INT_SYM __outword)(__port, __val);
	__IO_SLOWDOWN
}

__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_KRN(outl_p)(__port_t __port, __UINT32_TYPE__ __val) {
	(__NAMESPACE_INT_SYM __outdword)(__port, (__ULONG32_TYPE__)__val);
	__IO_SLOWDOWN
}
#else /* __USE_KOS_ALTERATIONS */
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_KRN(outb)(__UINT8_TYPE__ __val, __port_t __port) {
	(__NAMESPACE_INT_SYM __outbyte)(__port, __val);
}

__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_KRN(outw)(__UINT16_TYPE__ __val, __port_t __port) {
	(__NAMESPACE_INT_SYM __outword)(__port, __val);
}

__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_KRN(outl)(__UINT32_TYPE__ __val, __port_t __port) {
	(__NAMESPACE_INT_SYM __outdword)(__port, (__ULONG32_TYPE__)__val);
}

__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_KRN(outb_p)(__UINT8_TYPE__ __val, __port_t __port) {
	(__NAMESPACE_INT_SYM __outbyte)(__port, __val);
	__IO_SLOWDOWN
}

__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_KRN(outw_p)(__UINT16_TYPE__ __val, __port_t __port) {
	(__NAMESPACE_INT_SYM __outword)(__port, __val);
	__IO_SLOWDOWN
}

__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_KRN(outl_p)(__UINT32_TYPE__ __val, __port_t __port) {
	(__NAMESPACE_INT_SYM __outdword)(__port, (__ULONG32_TYPE__)__val);
	__IO_SLOWDOWN
}
#endif /* !__USE_KOS_ALTERATIONS */

__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(outsb)(__port_t __port, void const *__buf, __SIZE_TYPE__ __n_bytes) {
	(__NAMESPACE_INT_SYM __outbytestring)(__port, (__UINT8_TYPE__ *)__buf, (__SIZE_TYPE__)__n_bytes);
}

__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(outsw)(__port_t __port, void const *__buf, __SIZE_TYPE__ __n_words) {
	(__NAMESPACE_INT_SYM __outwordstring)(__port, (__UINT16_TYPE__ *)__buf, (__SIZE_TYPE__)__n_words);
}

__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(outsl)(__port_t __port, void const *__buf, __SIZE_TYPE__ __n_dwords) {
	(__NAMESPACE_INT_SYM __outdwordstring)(__port, (__ULONG32_TYPE__ *)__buf, (__SIZE_TYPE__)__n_dwords);
}

#if defined(__USE_KOS_KERNEL)
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_KRN(io_delay)(void) { __IO_SLOWDOWN }
#endif /* __USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("al")
#pragma pop_macro("out")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef __IO_SLOWDOWN
#undef __IO_SLOWDOWN_IMPL

#define inb(port)                              ((__NAMESPACE_INT_SYM __inbyte)(port))
#define inw(port)                              ((__NAMESPACE_INT_SYM __inword)(port))
#define inl(port)             ((__UINT32_TYPE__)(__NAMESPACE_INT_SYM __indword)(port))
#define insb(port, addr, n_bytes)              ((__NAMESPACE_INT_SYM __inbytestring)(port, (__UINT8_TYPE__ *)(addr), (__LONGSIZE_TYPE__)(n_bytes)))
#define insw(port, addr, n_words)              ((__NAMESPACE_INT_SYM __inwordstring)(port, (__UINT16_TYPE__ *)(addr), (__LONGSIZE_TYPE__)(n_words)))
#define insl(port, addr, n_dwords)             ((__NAMESPACE_INT_SYM __indwordstring)(port, (__ULONG32_TYPE__ *)(addr), (__LONGSIZE_TYPE__)(n_dwords)))
#ifdef __USE_KOS_ALTERATIONS
#define outb(port, val)                        ((__NAMESPACE_INT_SYM __outbyte)(port, val))
#define outw(port, val)                        ((__NAMESPACE_INT_SYM __outword)(port, val))
#define outl(port, val)                        ((__NAMESPACE_INT_SYM __outdword)(port, (__ULONG32_TYPE__)(val)))
#else /* __USE_KOS_ALTERATIONS */
#define outb(val, port)                        ((__NAMESPACE_INT_SYM __outbyte)(port, val))
#define outw(val, port)                        ((__NAMESPACE_INT_SYM __outword)(port, val))
#define outl(val, port)                        ((__NAMESPACE_INT_SYM __outdword)(port, (__ULONG32_TYPE__)(val)))
#endif /* !__USE_KOS_ALTERATIONS */
#define outsb(port, addr, n_bytes)             ((__NAMESPACE_INT_SYM __outbytestring)(port, (__UINT8_TYPE__ *)(addr), (__SIZE_TYPE__)(n_bytes)))
#define outsw(port, addr, n_words)             ((__NAMESPACE_INT_SYM __outwordstring)(port, (__UINT16_TYPE__ *)(addr), (__SIZE_TYPE__)(n_words)))
#define outsl(port, addr, n_dwords)            ((__NAMESPACE_INT_SYM __outdwordstring)(port, (__ULONG32_TYPE__ *)(addr), (__SIZE_TYPE__)(n_dwords)))
#endif /* !GCC... */

#undef __IO_SLOWDOWN
#undef __IO_SLOWDOWN_IMPL

__SYSDECL_END
#endif /* __CC__ */

#ifndef __IOPORT
#define __IOPORT(x) x
#endif /* !__IOPORT */

#endif /* !_I386_KOS_SYS_IO_H */
