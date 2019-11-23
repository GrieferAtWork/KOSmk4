/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_SYS_IO_H
#define _I386_KOS_SYS_IO_H 1
#define _SYS_IO_H 1

#include <__stdinc.h>
#include <__crt.h>
#include <features.h>
#include <sys/perm.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __COMPILER_ASM_BUFFER
#define __COMPILER_ASM_BUFFER(T, s, p) (*(T *)(p))
#endif /* !__COMPILER_ASM_BUFFER */

#ifndef __IOPORT_T
#define __IOPORT_T    __UINT16_TYPE__
#endif /* !__IOPORT_T */
#ifndef __IOPORT
#define __IOPORT(x)  ((__IOPORT_T)x)
#endif /* !__IOPORT */
#ifndef __MEMPORT_T
#define __MEMPORT_T   __UINTPTR_TYPE__
#endif /* !__MEMPORT_T */

#ifdef __INTELLISENSE__

__UINT8_TYPE__ __NOTHROW(__LIBCCALL inb)(__IOPORT_T __port);
__UINT8_TYPE__ __NOTHROW(__LIBCCALL inb_p)(__IOPORT_T __port);
void __NOTHROW(__LIBCCALL insb)(__IOPORT_T __port, void *__buf, __SIZE_TYPE__ __n_bytes);
void __NOTHROW(__LIBCCALL outb)(__IOPORT_T __port, __UINT8_TYPE__ __val);
void __NOTHROW(__LIBCCALL outb_p)(__IOPORT_T __port, __UINT8_TYPE__ __val);
void __NOTHROW(__LIBCCALL outsb)(__IOPORT_T __port, void const *__buf, __SIZE_TYPE__ __n_bytes);
__UINT16_TYPE__ __NOTHROW(__LIBCCALL inw)(__IOPORT_T __port);
__UINT16_TYPE__ __NOTHROW(__LIBCCALL inw_p)(__IOPORT_T __port);
void __NOTHROW(__LIBCCALL insw)(__IOPORT_T __port, void *__buf, __SIZE_TYPE__ __n_words);
void __NOTHROW(__LIBCCALL outw)(__IOPORT_T __port, __UINT16_TYPE__ __val);
void __NOTHROW(__LIBCCALL outw_p)(__IOPORT_T __port, __UINT16_TYPE__ __val);
void __NOTHROW(__LIBCCALL outsw)(__IOPORT_T __port, void const *__buf, __SIZE_TYPE__ __n_words);
__UINT32_TYPE__ __NOTHROW(__LIBCCALL inl)(__IOPORT_T __port);
__UINT32_TYPE__ __NOTHROW(__LIBCCALL inl_p)(__IOPORT_T __port);
void __NOTHROW(__LIBCCALL insl)(__IOPORT_T __port, void *__buf, __SIZE_TYPE__ __n_dwords);
void __NOTHROW(__LIBCCALL outl)(__IOPORT_T __port, __UINT32_TYPE__ __val);
void __NOTHROW(__LIBCCALL outl_p)(__IOPORT_T __port, __UINT32_TYPE__ __val);
void __NOTHROW(__LIBCCALL outsl)(__IOPORT_T __port, void const *__buf, __SIZE_TYPE__ __n_dwords);

#ifdef __USE_KOS_KERNEL
void __NOTHROW(__LIBCCALL io_delay)(void);
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


#define __MAKEIN(T, sfx, r, n, count)                                               \
	__FORCELOCAL T __NOTHROW(__LIBCCALL in##sfx)(__IOPORT_T __port) {               \
		__register T __rv;                                                          \
		__asm__ __volatile__("in" #sfx " %w1, %0"                                   \
		                     : "=a" (__rv)                                          \
		                     : "Nd" (__port));                                      \
		return __rv;                                                                \
	}                                                                               \
	__FORCELOCAL T __NOTHROW(__LIBCCALL in##sfx##_p)(__IOPORT_T __port) {           \
		__register T __rv;                                                          \
		__asm__ __volatile__("in" #sfx " %w1, %0" __IO_SLOWDOWN                     \
		                     : "=a" (__rv)                                          \
		                     : "Nd" (__port));                                      \
		return __rv;                                                                \
	}                                                                               \
	__FORCELOCAL void __NOTHROW_NCX(__LIBCCALL ins##sfx)(__IOPORT_T __port,         \
	                                                     void *__buf,               \
	                                                     __SIZE_TYPE__ count) {     \
		__asm__ __volatile__("rep; ins" #sfx                                        \
		                     : "=D" (__buf)                                         \
		                     , "=c" (count)                                         \
		                     , "=m" (__COMPILER_ASM_BUFFER(T, count, __buf))        \
		                     : "d" (__port)                                         \
		                     , "0" (__buf)                                          \
		                     , "1" (count));                                        \
	}

#define __MAKEOUT(T, sfx, s1, r, n, count)                                                      \
	__FORCELOCAL void __NOTHROW(__LIBCCALL out##sfx)(__IOPORT_T __port, T __val) {              \
		__asm__ __volatile__("out" #sfx " %" s1 "0, %w1"                                        \
		                     :                                                                  \
		                     : "a" (__val)                                                      \
		                     , "Nd" (__port));                                                  \
	}                                                                                           \
	__FORCELOCAL void __NOTHROW(__LIBCCALL out##sfx##_p)(__IOPORT_T __port, T __val) {          \
		__asm__ __volatile__("out" #sfx " %" s1 "0, %w1" __IO_SLOWDOWN                          \
		                     :                                                                  \
		                     : "a" (__val)                                                      \
		                     , "Nd" (__port));                                                  \
	}                                                                                           \
	__FORCELOCAL void __NOTHROW_NCX(__LIBCCALL outs##sfx)(__IOPORT_T __port,                    \
	                                                      void const *__buf,                    \
	                                                      __SIZE_TYPE__ count) {                \
		__asm__ __volatile__("rep; outs" #sfx                                                   \
		                     : "=S" (__buf)                                                     \
		                     , "=c" (count)                                                     \
		                     : "d" (__port)                                                     \
		                     , "0" (__buf)                                                      \
		                     , "1" (count)                                                      \
		                     , "m" (__COMPILER_ASM_BUFFER(T, count, __buf)));                   \
	}


__MAKEIN(__UINT8_TYPE__, b, "q", 1, __n_bytes)
__MAKEIN(__UINT16_TYPE__, w, "r", 2, __n_words)
__MAKEIN(__UINT32_TYPE__, l, "r", 4, __n_dwords)
__MAKEOUT(__UINT8_TYPE__, b, "b", "q", 1, __n_bytes)
__MAKEOUT(__UINT16_TYPE__, w, "w", "r", 2, __n_words)
__MAKEOUT(__UINT32_TYPE__, l, "", "r", 4, __n_dwords)

#if defined(__USE_KOS_KERNEL)
__FORCELOCAL void __NOTHROW(__LIBCCALL io_delay)(void) {
	__asm__ __volatile__(__IO_SLOWDOWN
	                     :
	                     :
	                     : "memory");
}
#endif /* __USE_KOS_KERNEL */
#else /* GCC... */

__NAMESPACE_INT_BEGIN
extern __UINT8_TYPE__ __NOTHROW(__cdecl __inbyte)(__IOPORT_T __port);
extern __UINT16_TYPE__ __NOTHROW(__cdecl __inword)(__IOPORT_T __port);
extern __ULONG32_TYPE__ __NOTHROW(__cdecl __indword)(__IOPORT_T __port);
extern void __NOTHROW_NCX(__cdecl __inbytestring)(__IOPORT_T __port, __UINT8_TYPE__ *__addr, __LONGSIZE_TYPE__ __n_bytes);
extern void __NOTHROW_NCX(__cdecl __inwordstring)(__IOPORT_T __port, __UINT16_TYPE__ *__addr, __LONGSIZE_TYPE__ __n_words);
extern void __NOTHROW_NCX(__cdecl __indwordstring)(__IOPORT_T __port, __ULONG32_TYPE__ *__addr, __LONGSIZE_TYPE__ __n_dwords);
extern void __NOTHROW(__cdecl __outbyte)(__IOPORT_T __port, __UINT8_TYPE__ __val);
extern void __NOTHROW(__cdecl __outword)(__IOPORT_T __port, __UINT16_TYPE__ __val);
extern void __NOTHROW(__cdecl __outdword)(__IOPORT_T __port, __ULONG32_TYPE__ __val);
extern void __NOTHROW_NCX(__cdecl __outbytestring)(__IOPORT_T __port, __UINT8_TYPE__ *__addr, __LONGSIZE_TYPE__ __n_bytes);
extern void __NOTHROW_NCX(__cdecl __outwordstring)(__IOPORT_T __port, __UINT16_TYPE__ *__addr, __LONGSIZE_TYPE__ __n_words);
extern void __NOTHROW_NCX(__cdecl __outdwordstring)(__IOPORT_T __port, __ULONG32_TYPE__ *__addr, __LONGSIZE_TYPE__ __n_dwords);
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
#else
#define __IO_SLOWDOWN_IMPL __asm { out 0x80, al }
#endif
#if 0
#define __IO_SLOWDOWN  __IO_SLOWDOWN_IMPL \
                       __IO_SLOWDOWN_IMPL \
                       __IO_SLOWDOWN_IMPL
#else
#define __IO_SLOWDOWN  __IO_SLOWDOWN_IMPL
#endif

__FORCELOCAL __UINT8_TYPE__ __NOTHROW(__LIBCCALL inb)(__IOPORT_T __port) {
	return (__NAMESPACE_INT_SYM __inbyte)(__port);
}

__FORCELOCAL __UINT16_TYPE__ __NOTHROW(__LIBCCALL inw)(__IOPORT_T __port) {
	return (__NAMESPACE_INT_SYM __inword)(__port);
}

__FORCELOCAL __UINT32_TYPE__ __NOTHROW(__LIBCCALL inl)(__IOPORT_T __port) {
	return (__UINT32_TYPE__)(__NAMESPACE_INT_SYM __indword)(__port);
}

__FORCELOCAL __UINT8_TYPE__ __NOTHROW(__LIBCCALL inb_p)(__IOPORT_T __port) {
	__UINT8_TYPE__ __res = (__NAMESPACE_INT_SYM __inbyte)(__port);
	__IO_SLOWDOWN return __res;
}

__FORCELOCAL __UINT16_TYPE__ __NOTHROW(__LIBCCALL inw_p)(__IOPORT_T __port) {
	__UINT16_TYPE__ __res = (__NAMESPACE_INT_SYM __inword)(__port);
	__IO_SLOWDOWN return __res;
}

__FORCELOCAL __UINT32_TYPE__ __NOTHROW(__LIBCCALL inl_p)(__IOPORT_T __port) {
	__UINT32_TYPE__ __res = (__UINT32_TYPE__)(__NAMESPACE_INT_SYM __indword)(__port);
	__IO_SLOWDOWN return __res;
}

__FORCELOCAL void __NOTHROW_NCX(__LIBCCALL insb)(__IOPORT_T __port,
                                                 void *__buf,
                                                 __SIZE_TYPE__ __n_bytes) {
	(__NAMESPACE_INT_SYM __inbytestring)(__port, (__UINT8_TYPE__ *)__buf, (__LONGSIZE_TYPE__)__n_bytes);
}

__FORCELOCAL void __NOTHROW_NCX(__LIBCCALL insw)(__IOPORT_T __port,
                                                 void *__buf,
                                                 __SIZE_TYPE__ __n_words) {
	(__NAMESPACE_INT_SYM __inwordstring)(__port, (__UINT16_TYPE__ *)__buf, (__LONGSIZE_TYPE__)__n_words);
}

__FORCELOCAL void __NOTHROW_NCX(__LIBCCALL insl)(__IOPORT_T __port,
                                                 void *__buf,
                                                 __SIZE_TYPE__ __n_dwords) {
	(__NAMESPACE_INT_SYM __indwordstring)(__port, (__ULONG32_TYPE__ *)__buf, (__LONGSIZE_TYPE__)__n_dwords);
}

__FORCELOCAL void __NOTHROW(__LIBCCALL outb)(__IOPORT_T __port,
                                             __UINT8_TYPE__ __val) {
	(__NAMESPACE_INT_SYM __outbyte)(__port, __val);
}

__FORCELOCAL void __NOTHROW(__LIBCCALL outw)(__IOPORT_T __port,
                                             __UINT16_TYPE__ __val) {
	(__NAMESPACE_INT_SYM __outword)(__port, __val);
}

__FORCELOCAL void __NOTHROW(__LIBCCALL outl)(__IOPORT_T __port,
                                             __UINT32_TYPE__ __val) {
	(__NAMESPACE_INT_SYM __outdword)(__port, (__ULONG32_TYPE__)__val);
}

__FORCELOCAL void __NOTHROW(__LIBCCALL outb_p)(__IOPORT_T __port,
                                               __UINT8_TYPE__ __val) {
	(__NAMESPACE_INT_SYM __outbyte)(__port, __val);
	__IO_SLOWDOWN
}

__FORCELOCAL void __NOTHROW(__LIBCCALL outw_p)(__IOPORT_T __port,
                                               __UINT16_TYPE__ __val) {
	(__NAMESPACE_INT_SYM __outword)(__port, __val);
	__IO_SLOWDOWN
}

__FORCELOCAL void __NOTHROW(__LIBCCALL outl_p)(__IOPORT_T __port,
                                               __UINT32_TYPE__ __val) {
	(__NAMESPACE_INT_SYM __outdword)(__port, (__ULONG32_TYPE__)__val);
	__IO_SLOWDOWN
}

__FORCELOCAL void __NOTHROW_NCX(__LIBCCALL outsb)(__IOPORT_T __port,
                                                  void const *__buf,
                                                  __SIZE_TYPE__ __n_bytes) {
	(__NAMESPACE_INT_SYM __outbytestring)(__port, (__UINT8_TYPE__ *)__buf, (__SIZE_TYPE__)__n_bytes);
}

__FORCELOCAL void __NOTHROW_NCX(__LIBCCALL outsw)(__IOPORT_T __port,
                                                  void const *__buf,
                                                  __SIZE_TYPE__ __n_words) {
	(__NAMESPACE_INT_SYM __outwordstring)(__port, (__UINT16_TYPE__ *)__buf, (__SIZE_TYPE__)__n_words);
}

__FORCELOCAL void __NOTHROW_NCX(__LIBCCALL outsl)(__IOPORT_T __port,
                                                  void const *__buf,
                                                  __SIZE_TYPE__ __n_dwords) {
	(__NAMESPACE_INT_SYM __outdwordstring)(__port, (__ULONG32_TYPE__ *)__buf, (__SIZE_TYPE__)__n_dwords);
}

#if defined(__USE_KOS_KERNEL)
__FORCELOCAL void __NOTHROW(__LIBCCALL io_delay)(void) { __IO_SLOWDOWN }
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
#define outb(port, val)                        ((__NAMESPACE_INT_SYM __outbyte)(port, val))
#define outw(port, val)                        ((__NAMESPACE_INT_SYM __outword)(port, val))
#define outl(port, val)                        ((__NAMESPACE_INT_SYM __outdword)(port, (__ULONG32_TYPE__)(val)))
#define outsb(port, addr, n_bytes)             ((__NAMESPACE_INT_SYM __outbytestring)(port, (__UINT8_TYPE__ *)(addr), (__SIZE_TYPE__)(n_bytes)))
#define outsw(port, addr, n_words)             ((__NAMESPACE_INT_SYM __outwordstring)(port, (__UINT16_TYPE__ *)(addr), (__SIZE_TYPE__)(n_words)))
#define outsl(port, addr, n_dwords)            ((__NAMESPACE_INT_SYM __outdwordstring)(port, (__ULONG32_TYPE__ *)(addr), (__SIZE_TYPE__)(n_dwords)))
#endif /* !GCC... */

#undef __MAKEOUT
#undef __MAKEIN
#undef __IO_SLOWDOWN
#undef __IO_SLOWDOWN_IMPL

__SYSDECL_END
#endif /* __CC__ */

#ifndef __IOPORT
#define __IOPORT(x)    x
#endif /* !__IOPORT */

#endif /* !_I386_KOS_SYS_IO_H */
