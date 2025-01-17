/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_SYS_MMIO_H
#define _I386_KOS_SYS_MMIO_H 1

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
#define __MEMPORT_T __UINTPTR_TYPE__
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

__UINT8_TYPE__ __NOTHROW(peekb)(__MEMPORT_T __addr);
__UINT16_TYPE__ __NOTHROW(peekw)(__MEMPORT_T __addr);
__UINT32_TYPE__ __NOTHROW(peekl)(__MEMPORT_T __addr);
void __NOTHROW(pokeb)(__MEMPORT_T __addr, __UINT8_TYPE__ __val);
void __NOTHROW(pokew)(__MEMPORT_T __addr, __UINT16_TYPE__ __val);
void __NOTHROW(pokel)(__MEMPORT_T __addr, __UINT32_TYPE__ __val);
__ATTR_NONNULL((2)) void __NOTHROW(peeksb)(__MEMPORT_T __addr, void *__buf, __SIZE_TYPE__ __n_bytes);
__ATTR_NONNULL((2)) void __NOTHROW(peeksw)(__MEMPORT_T __addr, void *__buf, __SIZE_TYPE__ __n_words);
__ATTR_NONNULL((2)) void __NOTHROW(peeksl)(__MEMPORT_T __addr, void *__buf, __SIZE_TYPE__ __n_dwords);
__ATTR_NONNULL((2)) void __NOTHROW(pokesb)(__MEMPORT_T __addr, void const *__buf, __SIZE_TYPE__ __n_bytes);
__ATTR_NONNULL((2)) void __NOTHROW(pokesw)(__MEMPORT_T __addr, void const *__buf, __SIZE_TYPE__ __n_words);
__ATTR_NONNULL((2)) void __NOTHROW(pokesl)(__MEMPORT_T __addr, void const *__buf, __SIZE_TYPE__ __n_dwords);
#if defined(__x86_64__) && defined(__UINT64_TYPE__)
__UINT64_TYPE__ __NOTHROW(peekq)(__MEMPORT_T __addr);
__ATTR_NONNULL((2)) void __NOTHROW(peeksq)(__MEMPORT_T __addr, void *__buf, __SIZE_TYPE__ __n_qword);
void __NOTHROW(pokeq)(__MEMPORT_T __addr, __UINT64_TYPE__ __val);
__ATTR_NONNULL((2)) void __NOTHROW(pokesq)(__MEMPORT_T __addr, void const *__buf, __SIZE_TYPE__ __n_qword);
#endif /* __x86_64__ && __UINT64_TYPE__ */

#elif defined(__COMPILER_HAVE_GCC_ASM)

#define peekb(port) peekb((__MEMPORT_T)(port))
__FORCELOCAL __ATTR_ARTIFICIAL __UINT8_TYPE__
__NOTHROW_NCX(peekb)(__MEMPORT_T __addr) {
	__register __UINT8_TYPE__ __rv;
	__COMPILER_READ_BARRIER();
	__asm__ __volatile__("movb %1, %0"
	                     : "=q" (__rv)
	                     : "m" (*(__UINT8_TYPE__ const volatile *)__addr));
	return __rv;
}

#define peeksb(port, addr, num_bytes) peeksb((__MEMPORT_T)(port), addr, num_bytes)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(peeksb)(__MEMPORT_T __addr,
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
		                     : "m" (*(__UINT8_TYPE__ const volatile *)__addr)
		                     , "D" (__buf)
		                     , "c" (__num_bytes));
	}
}

#define pokeb(port, val) pokeb((__MEMPORT_T)(port), val)
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_NCX(pokeb)(__MEMPORT_T __addr, __UINT8_TYPE__ __val) {
	__asm__ __volatile__("movb %1, %0"
	                     : "=m" (*(__UINT8_TYPE__ volatile *)__addr)
	                     : "q" (__val));
	__COMPILER_WRITE_BARRIER();
}

#define pokesb(port, addr, num_bytes) pokesb((__MEMPORT_T)(port), addr, num_bytes)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(pokesb)(__MEMPORT_T __addr,
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

#define peekw(port) peekw((__MEMPORT_T)(port))
__FORCELOCAL __ATTR_ARTIFICIAL __UINT16_TYPE__
__NOTHROW_NCX(peekw)(__MEMPORT_T __addr) {
	__register __UINT16_TYPE__ __rv;
	__COMPILER_READ_BARRIER();
	__asm__ __volatile__("movw %1, %0"
	                     : "=r" (__rv)
	                     : "m" (*(__UINT16_TYPE__ const volatile *)__addr));
	return __rv;
}

#define peeksw(port, addr, num_words) peeksw((__MEMPORT_T)(port), addr, num_words)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(peeksw)(__MEMPORT_T __addr,
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
		                     : "m" (*(__UINT16_TYPE__ const volatile *)__addr)
		                     , "D" (__buf)
		                     , "c" (__num_words));
	}
}

#define pokew(port, val) pokew((__MEMPORT_T)(port), val)
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_NCX(pokew)(__MEMPORT_T __addr, __UINT16_TYPE__ __val) {
	__asm__ __volatile__("movw %1, %0"
	                     : "=m" (*(__UINT16_TYPE__ volatile *)__addr)
	                     : "r" (__val));
	__COMPILER_WRITE_BARRIER();
}

#define pokesw(port, addr, num_words) pokesw((__MEMPORT_T)(port), addr, num_words)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(pokesw)(__MEMPORT_T __addr,
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

#define peekl(port) peekl((__MEMPORT_T)(port))
__FORCELOCAL __ATTR_ARTIFICIAL __UINT32_TYPE__
__NOTHROW_NCX(peekl)(__MEMPORT_T __addr) {
	__register __UINT32_TYPE__ __rv;
	__COMPILER_READ_BARRIER();
	__asm__ __volatile__("movl %1, %0"
	                     : "=r" (__rv)
	                     : "m" (*(__UINT32_TYPE__ const volatile *)__addr));
	return __rv;
}

#define peeksl(port, addr, num_dwords) peeksl((__MEMPORT_T)(port), addr, num_dwords)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(peeksl)(__MEMPORT_T __addr,
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
		                     : "m" (*(__UINT32_TYPE__ const volatile *)__addr)
		                     , "D" (__buf)
		                     , "c" (__num_dwords));
	}
}

#define pokel(port, val) pokel((__MEMPORT_T)(port), val)
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_NCX(pokel)(__MEMPORT_T __addr, __UINT32_TYPE__ __val) {
	__asm__ __volatile__("movl %1, %0"
	                     : "=m" (*(__UINT32_TYPE__ volatile *)__addr)
	                     : "r" (__val));
	__COMPILER_WRITE_BARRIER();
}

#define pokesl(port, addr, num_dwords) pokesl((__MEMPORT_T)(port), addr, num_dwords)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(pokesl)(__MEMPORT_T __addr,
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

#if defined(__x86_64__) && defined(__UINT64_TYPE__)
#define peekq(port) peekq((__MEMPORT_T)(port))
__FORCELOCAL __ATTR_ARTIFICIAL __UINT64_TYPE__
__NOTHROW_NCX(peekq)(__MEMPORT_T __addr) {
	__register __UINT64_TYPE__ __rv;
	__COMPILER_READ_BARRIER();
	__asm__ __volatile__("movq %1, %0"
	                     : "=r" (__rv)
	                     : "m" (*(__UINT64_TYPE__ const volatile *)__addr));
	return __rv;
}

#define peeksq(port, addr, num_qwords) peeksq((__MEMPORT_T)(port), addr, num_qwords)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(peeksq)(__MEMPORT_T __addr,
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
		                     : "m" (*(__UINT64_TYPE__ const volatile *)__addr)
		                     , "D" (__buf)
		                     , "c" (__num_qwords));
	}
}

#define pokeq(port, val) pokeq((__MEMPORT_T)(port), val)
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_NCX(pokeq)(__MEMPORT_T __addr, __UINT64_TYPE__ __val) {
	__asm__ __volatile__("movq %1, %0"
	                     : "=m" (*(__UINT64_TYPE__ volatile *)__addr)
	                     : "r" (__val));
	__COMPILER_WRITE_BARRIER();
}

#define pokesq(port, addr, num_qwords) pokesq((__MEMPORT_T)(port), addr, num_qwords)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(pokesq)(__MEMPORT_T __addr,
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
#endif /* __x86_64__ && __UINT64_TYPE__ */

#else /* __COMPILER_HAVE_GCC_ASM */

#define peekb(port) peekb((__MEMPORT_T)(port))
__FORCELOCAL __ATTR_ARTIFICIAL __UINT8_TYPE__
__NOTHROW_NCX(peekb)(__MEMPORT_T __addr) {
	__COMPILER_READ_BARRIER();
	return *(__UINT8_TYPE__ const volatile *)__addr;
}

#define peeksb(port, addr, num_bytes) peeksb((__MEMPORT_T)(port), addr, num_bytes)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(peeksb)(__MEMPORT_T __addr,
                      void *__buf,
                      __SIZE_TYPE__ __num_bytes) {
	__COMPILER_READ_BARRIER();
	for (; __num_bytes; --__num_bytes, __buf = (__UINT8_TYPE__ *)__buf + 1) {
		*(__UINT8_TYPE__ *)__buf = *(__UINT8_TYPE__ const volatile *)__addr;
	}
}

#define pokeb(port, val) pokeb((__MEMPORT_T)(port), val)
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_NCX(pokeb)(__MEMPORT_T __addr, __UINT8_TYPE__ __val) {
	*(__UINT8_TYPE__ volatile *)__addr = __val;
	__COMPILER_WRITE_BARRIER();
}

#define pokesb(port, addr, num_bytes) pokesb((__MEMPORT_T)(port), addr, num_bytes)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(pokesb)(__MEMPORT_T __addr,
                      void const *__buf,
                      __SIZE_TYPE__ __num_bytes) {
	for (; __num_bytes; --__num_bytes, __buf = (__UINT8_TYPE__ *)__buf + 1) {
		*(__UINT8_TYPE__ volatile *)__addr = *(__UINT8_TYPE__ *)__buf;
	}
	__COMPILER_WRITE_BARRIER();
}

#define peekw(port) peekw((__MEMPORT_T)(port))
__FORCELOCAL __ATTR_ARTIFICIAL __UINT16_TYPE__
__NOTHROW_NCX(peekw)(__MEMPORT_T __addr) {
	__COMPILER_READ_BARRIER();
	return *(__UINT16_TYPE__ const volatile *)__addr;
}

#define peeksw(port, addr, num_words) peeksw((__MEMPORT_T)(port), addr, num_words)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(peeksw)(__MEMPORT_T __addr,
                      void *__buf,
                      __SIZE_TYPE__ __num_words) {
	__COMPILER_READ_BARRIER();
	for (; __num_words; --__num_words, __buf = (__UINT16_TYPE__ *)__buf + 1) {
		*(__UINT16_TYPE__ *)__buf = *(__UINT16_TYPE__ const volatile *)__addr;
	}
}

#define pokew(port, val) pokew((__MEMPORT_T)(port), val)
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_NCX(pokew)(__MEMPORT_T __addr, __UINT16_TYPE__ __val) {
	*(__UINT16_TYPE__ volatile *)__addr = __val;
	__COMPILER_WRITE_BARRIER();
}

#define pokesw(port, addr, num_words) pokesw((__MEMPORT_T)(port), addr, num_words)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(pokesw)(__MEMPORT_T __addr,
                      void const *__buf,
                      __SIZE_TYPE__ __num_words) {
	for (; __num_words; --__num_words, __buf = (__UINT16_TYPE__ *)__buf + 1) {
		*(__UINT16_TYPE__ volatile *)__addr = *(__UINT16_TYPE__ *)__buf;
	}
	__COMPILER_WRITE_BARRIER();
}

#define peekl(port) peekl((__MEMPORT_T)(port))
__FORCELOCAL __ATTR_ARTIFICIAL __UINT32_TYPE__
__NOTHROW_NCX(peekl)(__MEMPORT_T __addr) {
	__COMPILER_READ_BARRIER();
	return *(__UINT32_TYPE__ const volatile *)__addr;
}

#define peeksl(port, addr, num_dwords) peeksl((__MEMPORT_T)(port), addr, num_dwords)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(peeksl)(__MEMPORT_T __addr,
                      void *__buf,
                      __SIZE_TYPE__ __num_dwords) {
	__COMPILER_READ_BARRIER();
	for (; __num_dwords; --__num_dwords, __buf = (__UINT32_TYPE__ *)__buf + 1) {
		*(__UINT32_TYPE__ *)__buf = *(__UINT32_TYPE__ const volatile *)__addr;
	}
}

#define pokel(port, val) pokel((__MEMPORT_T)(port), val)
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_NCX(pokel)(__MEMPORT_T __addr, __UINT32_TYPE__ __val) {
	*(__UINT32_TYPE__ volatile *)__addr = __val;
	__COMPILER_WRITE_BARRIER();
}

#define pokesl(port, addr, num_dwords) pokesl((__MEMPORT_T)(port), addr, num_dwords)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(pokesl)(__MEMPORT_T __addr,
                      void const *__buf,
                      __SIZE_TYPE__ __num_dwords) {
	for (; __num_dwords; --__num_dwords, __buf = (__UINT32_TYPE__ *)__buf + 1) {
		*(__UINT32_TYPE__ volatile *)__addr = *(__UINT32_TYPE__ *)__buf;
	}
	__COMPILER_WRITE_BARRIER();
}

#if defined(__x86_64__) && defined(__UINT64_TYPE__)
#define peekq(port) peekq((__MEMPORT_T)(port))
__FORCELOCAL __ATTR_ARTIFICIAL __UINT64_TYPE__
__NOTHROW_NCX(peekq)(__MEMPORT_T __addr) {
	__COMPILER_READ_BARRIER();
	return *(__UINT64_TYPE__ const volatile *)__addr;
}

#define peeksq(port, addr, num_qwords) peeksq((__MEMPORT_T)(port), addr, num_qwords)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(peeksq)(__MEMPORT_T __addr,
                      void *__buf,
                      __SIZE_TYPE__ __num_qwords) {
	__COMPILER_READ_BARRIER();
	for (; __num_qwords; --__num_qwords, __buf = (__UINT64_TYPE__ *)__buf + 1) {
		*(__UINT64_TYPE__ *)__buf = *(__UINT64_TYPE__ const volatile *)__addr;
	}
}

#define pokeq(port, val) pokeq((__MEMPORT_T)(port), val)
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_NCX(pokeq)(__MEMPORT_T __addr, __UINT64_TYPE__ __val) {
	*(__UINT64_TYPE__ volatile *)__addr = __val;
	__COMPILER_WRITE_BARRIER();
}

#define pokesq(port, addr, num_qwords) pokesq((__MEMPORT_T)(port), addr, num_qwords)
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(pokesq)(__MEMPORT_T __addr,
                      void const *__buf,
                      __SIZE_TYPE__ __num_qwords) {
	for (; __num_qwords; --__num_qwords, __buf = (__UINT64_TYPE__ *)__buf + 1) {
		*(__UINT64_TYPE__ volatile *)__addr = *(__UINT64_TYPE__ *)__buf;
	}
	__COMPILER_WRITE_BARRIER();
}
#endif /* __x86_64__ && __UINT64_TYPE__ */

#endif /* !__COMPILER_HAVE_GCC_ASM */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_SYS_MMIO_H */
