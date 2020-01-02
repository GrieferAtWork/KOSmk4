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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_SYS_MMIO_H
#define _I386_KOS_SYS_MMIO_H 1
#define _SYS_IO_H 1

#include <__stdinc.h>
#include <__crt.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __COMPILER_ASM_BUFFER
#define __COMPILER_ASM_BUFFER(T, s, p) (*(T *)(p))
#endif /* !__COMPILER_ASM_BUFFER */

#ifndef __MEMPORT_T
#define __MEMPORT_T   __UINTPTR_TYPE__
#endif /* !__MEMPORT_T */

#ifndef __MEMPORT_CONST_T
#define __MEMPORT_CONST_T __MEMPORT_T
#endif /* !__MEMPORT_CONST_T */

#if defined(__INTELLISENSE__) && defined(__cplusplus)
#undef __MEMPORT_T
#undef __MEMPORT_CONST_T
#define __MEMPORT_T       __NAMESPACE_INT_SYM ____INTELLISENSE_memport_t
#define __MEMPORT_CONST_T __NAMESPACE_INT_SYM ____INTELLISENSE_memport_const_t
__NAMESPACE_INT_BEGIN
extern "C++" {
class ____INTELLISENSE_memport_t {
public:
	template<class __T> ____INTELLISENSE_memport_t(__T *);
	____INTELLISENSE_memport_t(__UINTPTR_TYPE__);
};
class ____INTELLISENSE_memport_const_t {
public:
	template<class __T> ____INTELLISENSE_memport_const_t(__T const *);
	____INTELLISENSE_memport_const_t(__UINTPTR_TYPE__);
};
}
__NAMESPACE_INT_END

__UINT8_TYPE__ __NOTHROW(__LIBCCALL readb)(__MEMPORT_T __addr);
void __NOTHROW(__LIBCCALL readsb)(__MEMPORT_T __addr, void *__buf, __SIZE_TYPE__ __n_bytes);
void __NOTHROW(__LIBCCALL writeb)(__MEMPORT_T __addr, __UINT8_TYPE__ __val);
void __NOTHROW(__LIBCCALL writesb)(__MEMPORT_T __addr, void const *__buf, __SIZE_TYPE__ __n_bytes);
__UINT16_TYPE__ __NOTHROW(__LIBCCALL readw)(__MEMPORT_T __addr);
void __NOTHROW(__LIBCCALL readsw)(__MEMPORT_T __addr, void *__buf, __SIZE_TYPE__ __n_words);
void __NOTHROW(__LIBCCALL writew)(__MEMPORT_T __addr, __UINT16_TYPE__ __val);
void __NOTHROW(__LIBCCALL writesw)(__MEMPORT_T __addr, void const *__buf, __SIZE_TYPE__ __n_words);
__UINT32_TYPE__ __NOTHROW(__LIBCCALL readl)(__MEMPORT_T __addr);
void __NOTHROW(__LIBCCALL readsl)(__MEMPORT_T __addr, void *__buf, __SIZE_TYPE__ __n_dwords);
void __NOTHROW(__LIBCCALL writel)(__MEMPORT_T __addr, __UINT32_TYPE__ __val);
void __NOTHROW(__LIBCCALL writesl)(__MEMPORT_T __addr, void const *__buf, __SIZE_TYPE__ __n_dwords);
#ifdef __x86_64__
__UINT64_TYPE__ __NOTHROW(__LIBCCALL readq)(__MEMPORT_T __addr);
void __NOTHROW(__LIBCCALL readsq)(__MEMPORT_T __addr, void *__buf, __SIZE_TYPE__ __n_qword);
void __NOTHROW(__LIBCCALL writeq)(__MEMPORT_T __addr, __UINT64_TYPE__ __val);
void __NOTHROW(__LIBCCALL writesq)(__MEMPORT_T __addr, void const *__buf, __SIZE_TYPE__ __n_qword);
#endif /* __x86_64__ */

#elif defined(__COMPILER_HAVE_GCC_ASM)

#define readb(port) readb((__MEMPORT_T)(port))
__FORCELOCAL __UINT8_TYPE__
__NOTHROW_NCX(__LIBCCALL readb)(__MEMPORT_T __addr) {
	__register __UINT8_TYPE__ __rv;
	__COMPILER_READ_BARRIER();
	__asm__ __volatile__("movb %1, %0"
	                     : "=q" (__rv)
	                     : "m" (*(__UINT8_TYPE__ volatile const *)__addr));
	return __rv;
}

#define readsb(port, addr, num_bytes) readsb((__MEMPORT_T)(port), addr, num_bytes)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL readsb)(__MEMPORT_T __addr,
                                 void *__buf,
                                 __SIZE_TYPE__ __num_bytes) {
	if (__num_bytes) {
		__register __UINT8_TYPE__ __temp;
		__COMPILER_READ_BARRIER();
		__asm__ __volatile__("1:\n\t"
		                     "movb %2, %1\n\t"
		                     "stosb\n\t"
		                     "loop 1b"
		                     : "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __num_bytes, __buf))
		                     , "=&a" (__temp)
		                     : "m" (*(__UINT8_TYPE__ volatile const *)__addr)
		                     , "D" (__buf)
		                     , "c" (__num_bytes));
	}
}

#define writeb(port, val) writeb((__MEMPORT_T)(port), val)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writeb)(__MEMPORT_T __addr, __UINT8_TYPE__ __val) {
	__asm__ __volatile__("movb %1, %0"
	                     : "=m" (*(__UINT8_TYPE__ volatile *)__addr)
	                     : "q" (__val));
	__COMPILER_WRITE_BARRIER();
}

#define writesb(port, addr, num_bytes) writesb((__MEMPORT_T)(port), addr, num_bytes)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writesb)(__MEMPORT_T __addr,
                                  void const *__buf,
                                  __SIZE_TYPE__ __num_bytes) {
	if (__num_bytes) {
		__register __UINT8_TYPE__ __temp;
		__asm__ __volatile__("1:\n\t"
		                     "lodsb\n\t"
		                     "movb %1, %2\n\t"
		                     "loop 1b"
		                     : "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, __num_bytes, __buf))
		                     , "=&a" (__temp)
		                     : "m" (*(__UINT8_TYPE__ volatile *)__addr)
		                     , "S" (__buf)
		                     , "c" (__num_bytes));
		__COMPILER_WRITE_BARRIER();
	}
}

#define readw(port) readw((__MEMPORT_T)(port))
__FORCELOCAL __UINT16_TYPE__
__NOTHROW_NCX(__LIBCCALL readw)(__MEMPORT_T __addr) {
	__register __UINT16_TYPE__ __rv;
	__COMPILER_READ_BARRIER();
	__asm__ __volatile__("movw %1, %0"
	                     : "=r" (__rv)
	                     : "m" (*(__UINT16_TYPE__ volatile const *)__addr));
	return __rv;
}

#define readsw(port, addr, num_words) readsw((__MEMPORT_T)(port), addr, num_words)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL readsw)(__MEMPORT_T __addr,
                                 void *__buf,
                                 __SIZE_TYPE__ __num_words) {
	if (__num_words) {
		__register __UINT16_TYPE__ __temp;
		__COMPILER_READ_BARRIER();
		__asm__ __volatile__("1:\n\t"
		                     "movw %2, %1\n\t"
		                     "stosw\n\t"
		                     "loop 1b"
		                     : "=m" (__COMPILER_ASM_BUFFER(__UINT16_TYPE__, __num_words, __buf))
		                     , "=&a" (__temp)
		                     : "m" (*(__UINT16_TYPE__ volatile const *)__addr)
		                     , "D" (__buf)
		                     , "c" (__num_words));
	}
}

#define writew(port, val) writew((__MEMPORT_T)(port), val)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writew)(__MEMPORT_T __addr, __UINT16_TYPE__ __val) {
	__asm__ __volatile__("movw %1, %0"
	                     : "=m" (*(__UINT16_TYPE__ volatile *)__addr)
	                     : "r" (__val));
	__COMPILER_WRITE_BARRIER();
}

#define writesw(port, addr, num_words) writesw((__MEMPORT_T)(port), addr, num_words)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writesw)(__MEMPORT_T __addr,
                                  void const *__buf,
                                  __SIZE_TYPE__ __num_words) {
	if (__num_words) {
		__register __UINT16_TYPE__ __temp;
		__asm__ __volatile__("1:\n\t"
		                     "lodsw\n\t"
		                     "movw %1, %2\n\t"
		                     "loop 1b"
		                     : "=m" (__COMPILER_ASM_BUFFER(__UINT16_TYPE__, __num_words, __buf))
		                     , "=&a" (__temp)
		                     : "m" (*(__UINT16_TYPE__ volatile *)__addr)
		                     , "S" (__buf)
		                     , "c" (__num_words));
		__COMPILER_WRITE_BARRIER();
	}
}

#define readl(port) readl((__MEMPORT_T)(port))
__FORCELOCAL __UINT32_TYPE__
__NOTHROW_NCX(__LIBCCALL readl)(__MEMPORT_T __addr) {
	__register __UINT32_TYPE__ __rv;
	__COMPILER_READ_BARRIER();
	__asm__ __volatile__("movl %1, %0"
	                     : "=r" (__rv)
	                     : "m" (*(__UINT32_TYPE__ volatile const *)__addr));
	return __rv;
}

#define readsl(port, addr, num_dwords) readsl((__MEMPORT_T)(port), addr, num_dwords)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL readsl)(__MEMPORT_T __addr,
                                 void *__buf,
                                 __SIZE_TYPE__ __num_dwords) {
	if (__num_dwords) {
		__register __UINT32_TYPE__ __temp;
		__COMPILER_READ_BARRIER();
		__asm__ __volatile__("1:\n\t"
		                     "movl %2, %1\n\t"
		                     "stosl\n\t"
		                     "loop 1b"
		                     : "=m" (__COMPILER_ASM_BUFFER(__UINT32_TYPE__, __num_dwords, __buf))
		                     , "=&a" (__temp)
		                     : "m" (*(__UINT32_TYPE__ volatile const *)__addr)
		                     , "D" (__buf)
		                     , "c" (__num_dwords));
	}
}

#define writel(port, val) writel((__MEMPORT_T)(port), val)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writel)(__MEMPORT_T __addr, __UINT32_TYPE__ __val) {
	__asm__ __volatile__("movl %1, %0"
	                     : "=m" (*(__UINT32_TYPE__ volatile *)__addr)
	                     : "r" (__val));
	__COMPILER_WRITE_BARRIER();
}

#define writesl(port, addr, num_dwords) writesl((__MEMPORT_T)(port), addr, num_dwords)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writesl)(__MEMPORT_T __addr,
                                  void const *__buf,
                                  __SIZE_TYPE__ __num_dwords) {
	if (__num_dwords) {
		__register __UINT32_TYPE__ __temp;
		__asm__ __volatile__("1:\n\t"
		                     "lodsl\n\t"
		                     "movl %1, %2\n\t"
		                     "loop 1b"
		                     : "=m" (__COMPILER_ASM_BUFFER(__UINT32_TYPE__, __num_dwords, __buf))
		                     , "=&a" (__temp)
		                     : "m" (*(__UINT32_TYPE__ volatile *)__addr)
		                     , "S" (__buf)
		                     , "c" (__num_dwords));
		__COMPILER_WRITE_BARRIER();
	}
}

#ifdef __x86_64__
#define readq(port) readq((__MEMPORT_T)(port))
__FORCELOCAL __UINT64_TYPE__
__NOTHROW_NCX(__LIBCCALL readq)(__MEMPORT_T __addr) {
	__register __UINT64_TYPE__ __rv;
	__COMPILER_READ_BARRIER();
	__asm__ __volatile__("movq %1, %0"
	                     : "=r" (__rv)
	                     : "m" (*(__UINT64_TYPE__ volatile const *)__addr));
	return __rv;
}

#define readsq(port, addr, num_qwords) readsq((__MEMPORT_T)(port), addr, num_qwords)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL readsq)(__MEMPORT_T __addr,
                                 void *__buf,
                                 __SIZE_TYPE__ __num_qwords) {
	if (__num_qwords) {
		__register __UINT64_TYPE__ __temp;
		__COMPILER_READ_BARRIER();
		__asm__ __volatile__("1:\n\t"
		                     "movq %2, %1\n\t"
		                     "stosq\n\t"
		                     "loop 1b"
		                     : "=m" (__COMPILER_ASM_BUFFER(__UINT64_TYPE__, __num_qwords, __buf))
		                     , "=&a" (__temp)
		                     : "m" (*(__UINT64_TYPE__ volatile const *)__addr)
		                     , "D" (__buf)
		                     , "c" (__num_qwords));
	}
}

#define writeq(port, val) writeq((__MEMPORT_T)(port), val)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writeq)(__MEMPORT_T __addr, __UINT64_TYPE__ __val) {
	__asm__ __volatile__("movq %1, %0"
	                     : "=m" (*(__UINT64_TYPE__ volatile *)__addr)
	                     : "r" (__val));
	__COMPILER_WRITE_BARRIER();
}

#define writesq(port, addr, num_qwords) writesq((__MEMPORT_T)(port), addr, num_qwords)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writesq)(__MEMPORT_T __addr,
                                  void const *__buf,
                                  __SIZE_TYPE__ __num_qwords) {
	if (__num_qwords) {
		__register __UINT64_TYPE__ __temp;
		__asm__ __volatile__("1:\n\t"
		                     "lodsq\n\t"
		                     "movq %1, %2\n\t"
		                     "loop 1b"
		                     : "=m" (__COMPILER_ASM_BUFFER(__UINT64_TYPE__, __num_qwords, __buf))
		                     , "=&a" (__temp)
		                     : "m" (*(__UINT64_TYPE__ volatile *)__addr)
		                     , "S" (__buf)
		                     , "c" (__num_qwords));
		__COMPILER_WRITE_BARRIER();
	}
}
#endif /* __x86_64__ */

#else /* __COMPILER_HAVE_GCC_ASM */

#define readb(port) readb((__MEMPORT_T)(port))
__FORCELOCAL __UINT8_TYPE__
__NOTHROW_NCX(__LIBCCALL readb)(__MEMPORT_T __addr) {
	__COMPILER_READ_BARRIER();
	return *(__UINT8_TYPE__ volatile const *)__addr;
}

#define readsb(port, addr, num_bytes) readsb((__MEMPORT_T)(port), addr, num_bytes)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL readsb)(__MEMPORT_T __addr,
                                 void *__buf,
                                 __SIZE_TYPE__ __num_bytes) {
	__COMPILER_READ_BARRIER();
	for (; __num_bytes; --__num_bytes, __buf = (__UINT8_TYPE__ *)__buf + 1) {
		*(__UINT8_TYPE__ *)__buf = *(__UINT8_TYPE__ volatile const *)__addr;
	}
}

#define writeb(port, val) writeb((__MEMPORT_T)(port), val)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writeb)(__MEMPORT_T __addr, __UINT8_TYPE__ __val) {
	*(__UINT8_TYPE__ volatile *)__addr = __val;
	__COMPILER_WRITE_BARRIER();
}

#define writesb(port, addr, num_bytes) writesb((__MEMPORT_T)(port), addr, num_bytes)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writesb)(__MEMPORT_T __addr,
                                  void const *__buf,
                                  __SIZE_TYPE__ __num_bytes) {
	for (; __num_bytes; --__num_bytes, __buf = (__UINT8_TYPE__ *)__buf + 1) {
		*(__UINT8_TYPE__ volatile *)__addr = *(__UINT8_TYPE__ *)__buf;
	}
	__COMPILER_WRITE_BARRIER();
}

#define readw(port) readw((__MEMPORT_T)(port))
__FORCELOCAL __UINT16_TYPE__
__NOTHROW_NCX(__LIBCCALL readw)(__MEMPORT_T __addr) {
	__COMPILER_READ_BARRIER();
	return *(__UINT16_TYPE__ volatile const *)__addr;
}

#define readsw(port, addr, num_words) readsw((__MEMPORT_T)(port), addr, num_words)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL readsw)(__MEMPORT_T __addr,
                                 void *__buf,
                                 __SIZE_TYPE__ __num_words) {
	__COMPILER_READ_BARRIER();
	for (; __num_words; --__num_words, __buf = (__UINT16_TYPE__ *)__buf + 1) {
		*(__UINT16_TYPE__ *)__buf = *(__UINT16_TYPE__ volatile const *)__addr;
	}
}

#define writew(port, val) writew((__MEMPORT_T)(port), val)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writew)(__MEMPORT_T __addr, __UINT16_TYPE__ __val) {
	*(__UINT16_TYPE__ volatile *)__addr = __val;
	__COMPILER_WRITE_BARRIER();
}

#define writesw(port, addr, num_words) writesw((__MEMPORT_T)(port), addr, num_words)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writesw)(__MEMPORT_T __addr,
                                  void const *__buf,
                                  __SIZE_TYPE__ __num_words) {
	for (; __num_words; --__num_words, __buf = (__UINT16_TYPE__ *)__buf + 1) {
		*(__UINT16_TYPE__ volatile *)__addr = *(__UINT16_TYPE__ *)__buf;
	}
	__COMPILER_WRITE_BARRIER();
}

#define readl(port) readl((__MEMPORT_T)(port))
__FORCELOCAL __UINT32_TYPE__
__NOTHROW_NCX(__LIBCCALL readl)(__MEMPORT_T __addr) {
	__COMPILER_READ_BARRIER();
	return *(__UINT32_TYPE__ volatile const *)__addr;
}

#define readsl(port, addr, num_dwords) readsl((__MEMPORT_T)(port), addr, num_dwords)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL readsl)(__MEMPORT_T __addr,
                                 void *__buf,
                                 __SIZE_TYPE__ __num_dwords) {
	__COMPILER_READ_BARRIER();
	for (; __num_dwords; --__num_dwords, __buf = (__UINT32_TYPE__ *)__buf + 1) {
		*(__UINT32_TYPE__ *)__buf = *(__UINT32_TYPE__ volatile const *)__addr;
	}
}

#define writel(port, val) writel((__MEMPORT_T)(port), val)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writel)(__MEMPORT_T __addr, __UINT32_TYPE__ __val) {
	*(__UINT32_TYPE__ volatile *)__addr = __val;
	__COMPILER_WRITE_BARRIER();
}

#define writesl(port, addr, num_dwords) writesl((__MEMPORT_T)(port), addr, num_dwords)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writesl)(__MEMPORT_T __addr,
                                  void const *__buf,
                                  __SIZE_TYPE__ __num_dwords) {
	for (; __num_dwords; --__num_dwords, __buf = (__UINT32_TYPE__ *)__buf + 1) {
		*(__UINT32_TYPE__ volatile *)__addr = *(__UINT32_TYPE__ *)__buf;
	}
	__COMPILER_WRITE_BARRIER();
}

#ifdef __x86_64__
#define readq(port) readq((__MEMPORT_T)(port))
__FORCELOCAL __UINT64_TYPE__
__NOTHROW_NCX(__LIBCCALL readq)(__MEMPORT_T __addr) {
	__COMPILER_READ_BARRIER();
	return *(__UINT64_TYPE__ volatile const *)__addr;
}

#define readsq(port, addr, num_qwords) readsq((__MEMPORT_T)(port), addr, num_qwords)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL readsq)(__MEMPORT_T __addr,
                                 void *__buf,
                                 __SIZE_TYPE__ __num_qwords) {
	__COMPILER_READ_BARRIER();
	for (; __num_qwords; --__num_qwords, __buf = (__UINT64_TYPE__ *)__buf + 1) {
		*(__UINT64_TYPE__ *)__buf = *(__UINT64_TYPE__ volatile const *)__addr;
	}
}

#define writeq(port, val) writeq((__MEMPORT_T)(port), val)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writeq)(__MEMPORT_T __addr, __UINT64_TYPE__ __val) {
	*(__UINT64_TYPE__ volatile *)__addr = __val;
	__COMPILER_WRITE_BARRIER();
}

#define writesq(port, addr, num_qwords) writesq((__MEMPORT_T)(port), addr, num_qwords)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL writesq)(__MEMPORT_T __addr,
                                  void const *__buf,
                                  __SIZE_TYPE__ __num_qwords) {
	for (; __num_qwords; --__num_qwords, __buf = (__UINT64_TYPE__ *)__buf + 1) {
		*(__UINT64_TYPE__ volatile *)__addr = *(__UINT64_TYPE__ *)__buf;
	}
	__COMPILER_WRITE_BARRIER();
}
#endif /* __x86_64__ */

#endif /* !__COMPILER_HAVE_GCC_ASM */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_SYS_MMIO_H */
