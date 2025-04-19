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
/*!always_includes <__stdinc.h>*/
/*!always_includes <hybrid/compiler.h>*/
/*!always_includes <kos/anno.h>*/
/*!always_includes <kernel/compiler-branch-tracer.h>*/
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_COMPILER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_COMPILER_H 1

#include <__stdinc.h>
#include <hybrid/compiler.h>
#include <kernel/arch/compiler.h>
/**/

#include <kos/anno.h>
#include <kos/config/config.h> /* Pull in config-specific macro overrides */
#include <kos/refcnt.h>

#include "compiler-branch-tracer.h"

/************************************************************************/
/* GENERAL KERNEL CONFIGURATION OPTIONS                                 */
/************************************************************************/

/* Configuration option: The max number of CPUs supported by KOS. */
/*[[[config CONFIG_MAX_CPU_COUNT = 16]]]*/
#ifdef CONFIG_NO_SMP
#undef CONFIG_MAX_CPU_COUNT
#define CONFIG_MAX_CPU_COUNT 1
#elif !defined(CONFIG_MAX_CPU_COUNT)
#define CONFIG_MAX_CPU_COUNT 16
#elif (CONFIG_MAX_CPU_COUNT + 0) <= 1
#undef CONFIG_MAX_CPU_COUNT
#define CONFIG_NO_SMP
#define CONFIG_MAX_CPU_COUNT 1
#endif /* ... */
/*[[[end]]]*/

/************************************************************************/



/*
 * The meaning of NOBLOCK vs. <neither> vs. BLOCKING
 *
 * NOBLOCK:   The  function can be safely called, even while holding atomic locks,
 *            though  not necessarily while holding SMP locks. You may assume that
 *            the function doesn't include a call to `task_yield()' (though it may
 *            include a call  to `task_tryyield[_or_pause]()'), and  as such  will
 *            never throw `E_WOULDBLOCK' if called with preemption disabled.
 *
 * <neither>: The function may  acquire atomic locks  and throw E_WOULDBLOCK  from
 *            within  `task_yield()'  if  such  a  lock  cannot  be  acquired when
 *            preemption isn't enabled. However, the function isn't a cancellation
 *            point, and won't try to service RPCs either.
 *
 * BLOCKING:  The function is a cancellation point, in that it includes code-paths
 *            that include calls to `task_serve()'. As such, the function must not
 *            be called while holding  any sort of atomic  lock, and care must  be
 *            taken  if called while holding non-atomic locks, in which case there
 *            exists the possibility of a deadlock scenario.
 *
 */


/* Some extra kernel-specific annotations. */
#define FREE                 /* Annotation for functions / data that are apart of the .free section. */
#define THROWS_INDIRECT(...) /* Similar to `THROWS()', but the error is propgated by non-standard means. */
#define KERNEL               /* Annotation for kernel-space memory (default within kernel). */


#ifdef __INTELLISENSE__
#define ASMCALL __ATTR_CDECL /* Symbolic calling convention for custom assembler functions. */
#else /* __INTELLISENSE__ */
#define ASMCALL /* Symbolic calling convention for custom assembler functions. */
#endif /* !__INTELLISENSE__ */

#define BITSOF(x) (sizeof(x)*8)

#define ATTR_FREETEXT        FREE ATTR_SECTION(".text.free")
#define ATTR_FREERODATA      FREE ATTR_SECTION(".rodata.free")
#define ATTR_FREEDATA        FREE ATTR_SECTION(".data.free")
#define ATTR_FREEBSS         FREE ATTR_SECTION(".bss.free")
#define ATTR_FREETEXT_S(x)   FREE ATTR_SECTION(".text.free." x)
#define ATTR_FREERODATA_S(x) FREE ATTR_SECTION(".rodata.free." x)
#define ATTR_FREEDATA_S(x)   FREE ATTR_SECTION(".data.free." x)
#define ATTR_FREEBSS_S(x)    FREE ATTR_SECTION(".bss.free." x)

#define ATTR_HOTTEXT        ATTR_SECTION(".text.hot")
#define ATTR_HOTRODATA      ATTR_SECTION(".rodata.hot")
#define ATTR_HOTDATA        ATTR_SECTION(".data.hot")
#define ATTR_HOTBSS         ATTR_SECTION(".bss.hot")
#define ATTR_HOTTEXT_S(x)   ATTR_SECTION(".text.hot." x)
#define ATTR_HOTRODATA_S(x) ATTR_SECTION(".rodata.hot." x)
#define ATTR_HOTDATA_S(x)   ATTR_SECTION(".data.hot." x)
#define ATTR_HOTBSS_S(x)    ATTR_SECTION(".bss.hot." x)

/* Attributes for tiny pieces of data that are accessed extremely often,
 * usually done through reads, rather than writes. - This then allows us
 * to put all of them together, meaning that they can share cache-lines,
 * thus reducing the amount of necessary lookups in main memory. */
#define ATTR_READMOSTLY       ATTR_SECTION(".data.hot.read_mostly")
#define ATTR_WRITEMOSTLY      ATTR_SECTION(".data.hot.write_mostly")
#define ATTR_READMOSTLY_S(x)  ATTR_SECTION(".data.hot.read_mostly." x)
#define ATTR_WRITEMOSTLY_S(x) ATTR_SECTION(".data.hot.write_mostly." x)

#define ATTR_COLDTEXT        ATTR_SECTION(".text.cold")
#define ATTR_COLDRODATA      ATTR_SECTION(".rodata.cold")
#define ATTR_COLDDATA        ATTR_SECTION(".data.cold")
#define ATTR_COLDBSS         ATTR_SECTION(".bss.cold")
#define ATTR_COLDTEXT_S(x)   ATTR_SECTION(".text.cold." x)
#define ATTR_COLDRODATA_S(x) ATTR_SECTION(".rodata.cold." x)
#define ATTR_COLDDATA_S(x)   ATTR_SECTION(".data.cold." x)
#define ATTR_COLDBSS_S(x)    ATTR_SECTION(".bss.cold." x)

#define ATTR_TEXT        ATTR_SECTION(".text")
#define ATTR_RODATA      ATTR_SECTION(".rodata")
#define ATTR_DATA        ATTR_SECTION(".data")
#define ATTR_BSS         ATTR_SECTION(".bss")
#define ATTR_TEXT_S(x)   ATTR_SECTION(".text." s)
#define ATTR_RODATA_S(x) ATTR_SECTION(".rodata." s)
#define ATTR_DATA_S(x)   ATTR_SECTION(".data." s)
#define ATTR_BSS_S(x)    ATTR_SECTION(".bss." s)

#define FREESTR(s) XBLOCK({ PRIVATE ATTR_FREERODATA ATTR_ALIGNED(1) char const _free_str[] = s; XRETURN _free_str; })

#define ATTR_PERCPU      ATTR_SECTION(".data.percpu")  /* Per-cpu template data. */
#define ATTR_PERTASK     ATTR_SECTION(".data.pertask") /* Per-task template data. */
#define ATTR_PERMMAN     ATTR_SECTION(".data.permman") /* Per-memory-manager template data. */

/* Force  minimal alignment in data declarations. This
 * attribute  must be used when declaring ATTR_PERTASK
 * and ATTR_PERMMAN variables, so-as to ensure that no
 * unnecessary alignment-padding is inserted.
 *
 * For reference:
 * >>struct foo { void *a, *b, *c, *d; };
 * >>PUBLIC struct foo my_data_symbol = {};
 * ASM(x86_64-kos-gcc):
 * >>	.globl my_data_symbol
 * >>	.section .bss
 * >>	.align 32
 * >>	.type my_data_symbol, "object"
 * >>	.size my_data_symbol, 32
 * >>my_data_symbol:
 * >>	.zero 32
 *
 * Using this attribute:
 * >>struct foo { void *a, *b, *c, *d; };
 * >>PUBLIC ATTR_ALIGN(struct foo) my_data_symbol = {};
 * ASM(x86_64-kos-gcc):
 * >>	.globl my_data_symbol
 * >>	.section .bss
 * >>	.align 8
 * >>	.type my_data_symbol, "object"
 * >>	.size my_data_symbol, 32
 * >>my_data_symbol:
 * >>	.zero 32 */
#define ATTR_ALIGN(...)  ATTR_ALIGNED(COMPILER_ALIGNOF(__VA_ARGS__)) __VA_ARGS__



#if defined(__x86_64__)
#define FCALL ATTR_SYSVABI
#define KCALL ATTR_SYSVABI
#define VCALL ATTR_SYSVABI
#elif defined(__i386__)
#define FCALL ATTR_FASTCALL
#define KCALL ATTR_STDCALL
#define VCALL ATTR_CDECL
#else /* ... */
#define FCALL /* nothing */
#define KCALL /* nothing */
#define VCALL /* nothing */
#endif /* !... */


/* Breakpoint */
#ifndef __CC__
#define BREAKPOINT() /* nothing */
#elif defined(__INTELLISENSE__)
FUNDEF void NOTHROW(KCALL BREAKPOINT)(void);
#define BREAKPOINT        BREAKPOINT
#else /* ... */
#include <debugger/config.h>
#ifndef CONFIG_NO_KERNEL_DEBUGGER
#define BREAKPOINT() ({ FUNDEF void KCALL dbg(void); dbg(); })
#else /* !CONFIG_NO_KERNEL_DEBUGGER */
#define BREAKPOINT() (void)0 /* ??? */
#endif /* CONFIG_NO_KERNEL_DEBUGGER */
#endif /* !... */


#ifndef __COMPILER_UNIQUE
#define __COMPILER_UNIQUE_IMPL2(x, y) x##y
#define __COMPILER_UNIQUE_IMPL(x, y) __COMPILER_UNIQUE_IMPL2(x, y)
#ifdef __COUNTER__
#define __COMPILER_UNIQUE(x) __COMPILER_UNIQUE_IMPL(x, __COUNTER__)
#else /* __COUNTER__ */
#define __COMPILER_UNIQUE(x) __COMPILER_UNIQUE_IMPL(x, __LINE__)
#endif /* !__COUNTER__ */
#endif /* !__COMPILER_UNIQUE */




#ifdef __CC__
#if defined(__clang_tidy__) && !defined(NO_INSTRUMENT_KMALLOC)
#ifndef ____os_free_defined
#define ____os_free_defined
#define __os_free __builtin_free
#endif /* !____os_free_defined */
#endif /* __clang_tidy__ && !NO_INSTRUMENT_KMALLOC */

#ifdef __cplusplus
#include <__stdcxx.h>


/* Re-define `__builtin_offsetof()' to prevent GCC warnings about
 * offsetof()  being  undefined  when  we  use  type  inheritace.
 * IT'S ONLY UNDEFINED WHEN THERE'S A V-TABLE, NOT IF  EVERYTHING
 * IS POD AND DOESN'T EVEN PROVIDE ANY CONSTRUCTORS! */
#if __GNUC__ < 6 && !defined(__clang__)
#undef __builtin_offsetof
#ifdef __INTELLISENSE_SIZE_TYPE__
#define __builtin_offsetof(s, m) ((__INTELLISENSE_SIZE_TYPE__)&((s *)0)->m)
#else /* __INTELLISENSE_SIZE_TYPE__ */
#include <hybrid/typecore.h>
#define __builtin_offsetof(s, m) ((__SIZE_TYPE__)&((s *)0)->m)
#endif /* !__INTELLISENSE_SIZE_TYPE__ */
#endif /* __GNUC__ < 6 && !__clang__ */






#include <asm/asmword.h>
#ifdef __ASSEMBLER__
#define DEFINE_ABS_CALLBACK(sect, func) .pushsection sect; .wordptr func; .popsection
#ifdef __ARCH_HAVE_wordrel
#define DEFINE_REL_CALLBACK(sect, func) .pushsection sect; .wordrel func; .popsection
#endif /* __ARCH_HAVE_wordrel */
#ifdef __ARCH_HAVE_wordoff
#define DEFINE_OFF_CALLBACK(sect, func) .pushsection sect; .wordoff func; .popsection
#endif /* __ARCH_HAVE_wordoff */
#else /* __ASSEMBLER__ */
#define DEFINE_ABS_CALLBACK(sect, func) __asm__(".pushsection " sect "\n\t\t.wordptr " PP_PRIVATE_STR(func) "\n\t.popsection")
#ifdef __ARCH_HAVE_wordrel
#define DEFINE_REL_CALLBACK(sect, func) __asm__(".pushsection " sect "\n\t\t.wordrel " PP_PRIVATE_STR(func) "\n\t.popsection")
#endif /* __ARCH_HAVE_wordrel */
#ifdef __ARCH_HAVE_wordoff
#define DEFINE_OFF_CALLBACK(sect, func) __asm__(".pushsection " sect "\n\t\t.wordoff " PP_PRIVATE_STR(func) "\n\t.popsection")
#endif /* __ARCH_HAVE_wordoff */
#endif /* !__ASSEMBLER__ */

#ifdef BUILDING_KERNEL_CORE
#define DEFINE_CALLBACK_IS_ABS
#define DEFINE_CALLBACK DEFINE_ABS_CALLBACK
#elif defined(__ARCH_HAVE_wordrel)
#define DEFINE_CALLBACK_IS_REL
#define DEFINE_CALLBACK DEFINE_REL_CALLBACK
#elif defined(__ARCH_HAVE_wordoff)
#define DEFINE_CALLBACK_IS_OFF
#define DEFINE_CALLBACK DEFINE_OFF_CALLBACK
#else /* ... */
#error "No way to implement `DEFINE_CALLBACK'"
#endif /* !... */


#ifdef __CHECKER__
#define FINALLY_DECREF(ptr)           decref(ptr)
#define FINALLY_DECREF_LIKELY(ptr)    decref_likely(ptr)
#define FINALLY_DECREF_UNLIKELY(ptr)  decref_unlikely(ptr)
#define FINALLY_DECREF_NOKILL(ptr)    decref_nokill(ptr)
#define FINALLY_DESTROY(ptr)          destroy(ptr)
#define FINALLY_XDECREF(ptr)          xdecref(ptr)
#define FINALLY_XDECREF_LIKELY(ptr)   xdecref_likely(ptr)
#define FINALLY_XDECREF_UNLIKELY(ptr) xdecref_unlikely(ptr)
#else /* __CHECKER__ */
extern "C++" {
__NAMESPACE_INT_BEGIN
template<class T> class _finally_decref {
	__CXX_DELETE_CTOR(_finally_decref);
	__CXX_DELETE_COPY(_finally_decref);
	__CXX_DELETE_COPY_ASSIGN(_finally_decref);
private:
	T &m_ptr;
public:
	__CXX_FORCEINLINE ATTR_ARTIFICIAL _finally_decref(T &ptr) __CXX_NOEXCEPT
	    : m_ptr(ptr) { }
	__CXX_FORCEINLINE ATTR_ARTIFICIAL ~_finally_decref() __CXX_NOEXCEPT {
		(::refcnt_methods<T>::decref)(&this->m_ptr);
	}
};
template<class T> class _finally_decref_likely {
	__CXX_DELETE_CTOR(_finally_decref_likely);
	__CXX_DELETE_COPY(_finally_decref_likely);
	__CXX_DELETE_COPY_ASSIGN(_finally_decref_likely);
private:
	T &m_ptr;
public:
	__CXX_FORCEINLINE ATTR_ARTIFICIAL _finally_decref_likely(T &ptr) __CXX_NOEXCEPT
	    : m_ptr(ptr) { }
	__CXX_FORCEINLINE ATTR_ARTIFICIAL ~_finally_decref_likely() __CXX_NOEXCEPT {
		(::refcnt_methods<T>::decref_likely)(&this->m_ptr);
	}
};
template<class T> class _finally_decref_unlikely {
	__CXX_DELETE_CTOR(_finally_decref_unlikely);
	__CXX_DELETE_COPY(_finally_decref_unlikely);
	__CXX_DELETE_COPY_ASSIGN(_finally_decref_unlikely);
private:
	T &m_ptr;
public:
	__CXX_FORCEINLINE ATTR_ARTIFICIAL _finally_decref_unlikely(T &ptr) __CXX_NOEXCEPT
	    : m_ptr(ptr) { }
	__CXX_FORCEINLINE ATTR_ARTIFICIAL ~_finally_decref_unlikely() __CXX_NOEXCEPT {
		(::refcnt_methods<T>::decref_unlikely)(&this->m_ptr);
	}
};
template<class T> class _finally_decref_nokill {
	__CXX_DELETE_CTOR(_finally_decref_nokill);
	__CXX_DELETE_COPY(_finally_decref_nokill);
	__CXX_DELETE_COPY_ASSIGN(_finally_decref_nokill);
private:
	T &m_ptr;
public:
	__CXX_FORCEINLINE ATTR_ARTIFICIAL _finally_decref_nokill(T &ptr) __CXX_NOEXCEPT
	    : m_ptr(ptr) { }
	__CXX_FORCEINLINE ATTR_ARTIFICIAL ~_finally_decref_nokill() __CXX_NOEXCEPT {
		(::refcnt_methods<T>::decref_nokill)(&this->m_ptr);
	}
};
template<class T> class _finally_destroy {
	__CXX_DELETE_CTOR(_finally_destroy);
	__CXX_DELETE_COPY(_finally_destroy);
	__CXX_DELETE_COPY_ASSIGN(_finally_destroy);
private:
	T &m_ptr;
public:
	__CXX_FORCEINLINE ATTR_ARTIFICIAL _finally_destroy(T &ptr) __CXX_NOEXCEPT
	    : m_ptr(ptr) { }
	__CXX_FORCEINLINE ATTR_ARTIFICIAL ~_finally_destroy() __CXX_NOEXCEPT {
		(::refcnt_methods<T>::destroy)(&this->m_ptr);
	}
};


template<class T> class _finally_xdecref {
	__CXX_DELETE_CTOR(_finally_xdecref);
	__CXX_DELETE_COPY(_finally_xdecref);
	__CXX_DELETE_COPY_ASSIGN(_finally_xdecref);
private:
	T *m_ptr;
public:
	__CXX_FORCEINLINE ATTR_ARTIFICIAL _finally_xdecref(T *ptr) __CXX_NOEXCEPT
	    : m_ptr(ptr) { }
	__CXX_FORCEINLINE ATTR_ARTIFICIAL ~_finally_xdecref() __CXX_NOEXCEPT {
		if (this->m_ptr)
			(::refcnt_methods<T>::decref)(this->m_ptr);
	}
};
template<class T> class _finally_xdecref_likely {
	__CXX_DELETE_CTOR(_finally_xdecref_likely);
	__CXX_DELETE_COPY(_finally_xdecref_likely);
	__CXX_DELETE_COPY_ASSIGN(_finally_xdecref_likely);
private:
	T *m_ptr;
public:
	__CXX_FORCEINLINE ATTR_ARTIFICIAL _finally_xdecref_likely(T *ptr) __CXX_NOEXCEPT
	    : m_ptr(ptr) { }
	__CXX_FORCEINLINE ATTR_ARTIFICIAL ~_finally_xdecref_likely() __CXX_NOEXCEPT {
		if (this->m_ptr)
			(::refcnt_methods<T>::decref_likely)(this->m_ptr);
	}
};
template<class T> class _finally_xdecref_unlikely {
	__CXX_DELETE_CTOR(_finally_xdecref_unlikely);
	__CXX_DELETE_COPY(_finally_xdecref_unlikely);
	__CXX_DELETE_COPY_ASSIGN(_finally_xdecref_unlikely);
private:
	T *m_ptr;
public:
	__CXX_FORCEINLINE ATTR_ARTIFICIAL _finally_xdecref_unlikely(T *ptr) __CXX_NOEXCEPT
	    : m_ptr(ptr) { }
	__CXX_FORCEINLINE ATTR_ARTIFICIAL ~_finally_xdecref_unlikely() __CXX_NOEXCEPT {
		if (this->m_ptr)
			(::refcnt_methods<T>::decref_unlikely)(this->m_ptr);
	}
};
__NAMESPACE_INT_END
} /* extern "C++" */

#define FINALLY_DECREF(ptr)           __NAMESPACE_INT_SYM _finally_decref<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fdecref)(*(ptr))
#define FINALLY_DECREF_LIKELY(ptr)    __NAMESPACE_INT_SYM _finally_decref_likely<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fdecref_l)(*(ptr))
#define FINALLY_DECREF_UNLIKELY(ptr)  __NAMESPACE_INT_SYM _finally_decref_unlikely<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fdecref_u)(*(ptr))
#define FINALLY_DECREF_NOKILL(ptr)    __NAMESPACE_INT_SYM _finally_decref_nokill<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fdecref_nk)(*(ptr))
#define FINALLY_DESTROY(ptr)          __NAMESPACE_INT_SYM _finally_destroy<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fdestroy)(*(ptr))
#define FINALLY_XDECREF(ptr)          __NAMESPACE_INT_SYM _finally_xdecref<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fxdecref)(ptr)
#define FINALLY_XDECREF_LIKELY(ptr)   __NAMESPACE_INT_SYM _finally_xdecref_likely<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fxdecref_l)(ptr)
#define FINALLY_XDECREF_UNLIKELY(ptr) __NAMESPACE_INT_SYM _finally_xdecref_unlikely<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fxdecref_u)(ptr)
#endif /* !__CHECKER__ */
#endif /* __cplusplus */
#endif /* __CC__ */

#define DEFINE_REFCNT_FUNCTIONS       __DEFINE_REFCNT_FUNCTIONS
#define DEFINE_REFCNT_FUNCTIONS_P     __DEFINE_REFCNT_FUNCTIONS_P
#define DEFINE_WEAKREFCNT_FUNCTIONS   __DEFINE_WEAKREFCNT_FUNCTIONS
#define DEFINE_WEAKREFCNT_FUNCTIONS_P __DEFINE_WEAKREFCNT_FUNCTIONS_P

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_COMPILER_H */
