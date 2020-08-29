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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_COMPILER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_COMPILER_H 1

#include <__stdinc.h>
#include <hybrid/compiler.h>

#include <hybrid/__atomic.h>

#include <kos/anno.h>
#include <kos/refcnt.h>

#include "compiler-branch-tracer.h"

#if defined(__CC__) && defined(__cplusplus) && defined(__GNUC__) && __GNUC__ >= 6
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#endif

#define PHYS           __PHYS          /* Annotation for physical pointers */
#define VIRT           __VIRT          /* Annotation for virtual pointers */
#define USER           __USER          /* Annotation for user-space memory (default outside kernel). */
#define CHECKED        __CHECKED       /* Annotation for checked memory. */
#define UNCHECKED      __UNCHECKED     /* Annotation for unchecked memory. */
#define KERNEL         __KERNEL        /* Annotation for kernel-space memory (default within kernel). */
#ifndef WEAK
#define WEAK           __WEAK          /* Annotation for weakly referenced data/data updated randomly with both the old/new state remaining valid. */
#endif /* !WEAK */
#define REF            __REF           /* Annotation for reference holders/transfers.
                                        * When used on a struct-field/local/global variable: Reference storage
                                        * When used on a return type: The function returns a reference
                                        * When used on an argument: The function inherited a reference (but look out for `inherit(<condition>)' annotations) */
#define FREE           /* ... */       /* Annotation for functions / data that are apart of the .free section. */
#define NOBLOCK        __NOBLOCK       /* Annotation for functions that are guarantied to never block,
                                        * making them safe to-be called from any asynchronous context. */
#define NOBLOCK_IF(x)  __NOBLOCK_IF(x) /* Same as `NOBLOCK', but only when `x' is true. */
#define NOCONNECT      __NOCONNECT     /* Annotation for functions which may only be called when
                                        * the calling thread isn't already connected to a signal. */
#define NOPREEMPT      __NOPREEMPT     /* Annotation for functions that may only be called with preemption disabled. */
#define THROWS         __THROWS        /* Annotation for the set of error codes/classes/sub-classes that may be thrown by a function.
                                        * You may include `...' as a possible error code to indicate that the function
                                        * is also allowed to throw any other kind of exception, usually indicative of
                                        * the function following a path that includes a call to `task_serve()'
                                        * Note however that this is merely for documentation purposes, as well as to
                                        * document the ~expected~ error codes (e.g. anything that can throw E_SEGFAULT
                                        * usually does so by accessing user-space memory, which also implies access to
                                        * VIO callbacks, and the fact that VIO is also allowed to throw arbitrary exceptions,
                                        * meaning that technically speaking, `E_SEGFAULT' would also imply `...').
                                        * Any function that isn't `__NOTHROW()' is still always allowed to throw any error
                                        * that isn't apart of the `__THROWS()' set. */
#define THROWS_INDIRECT(...)           /* Similar to `THROWS()', but the error is propgated by non-standard means. */


#ifdef __INTELLISENSE__
#define ASMCALL __ATTR_CDECL /* Symbolic calling convention for custom assembler functions. */
#else /* __INTELLISENSE__ */
#define ASMCALL /* Symbolic calling convention for custom assembler functions. */
#endif /* !__INTELLISENSE__ */

#define BITSOF(x) (sizeof(x)*8)


#define __DEFINE_SYMBOL_STR(x) #x
#define DEFINE_PRIVATE_SYMBOL(name, value, size)      __asm__(".type " __DEFINE_SYMBOL_STR(name) ", @object\n\t.local " __DEFINE_SYMBOL_STR(name) "\n\t.set " __DEFINE_SYMBOL_STR(name) ",%p0\n\t.size " __DEFINE_SYMBOL_STR(name) ",%p1" : : "X" (value), "X" (size))
#define DEFINE_PUBLIC_SYMBOL(name, value, size)       __asm__(".type " __DEFINE_SYMBOL_STR(name) ", @object\n\t.global " __DEFINE_SYMBOL_STR(name) "\n\t.set " __DEFINE_SYMBOL_STR(name) ",%p0\n\t.size " __DEFINE_SYMBOL_STR(name) ",%p1" : : "X" (value), "X" (size))
#define DEFINE_INTERN_SYMBOL(name, value, size)       __asm__(".type " __DEFINE_SYMBOL_STR(name) ", @object\n\t.global " __DEFINE_SYMBOL_STR(name) "\n\t.hidden " __DEFINE_SYMBOL_STR(name) "\n\t.set " __DEFINE_SYMBOL_STR(name) ",%p0\n\t.size " __DEFINE_SYMBOL_STR(name) ",%p1" : : "X" (value), "X" (size))
#define DEFINE_PRIVATE_WEAK_SYMBOL(name, value, size) __asm__(".type " __DEFINE_SYMBOL_STR(name) ", @object\n\t.weak " __DEFINE_SYMBOL_STR(name) "\n\t.local " __DEFINE_SYMBOL_STR(name) "\n\t.set " __DEFINE_SYMBOL_STR(name) ",%p0\n\t.size " __DEFINE_SYMBOL_STR(name) ",%p1" : : "X" (value), "X" (size))
#define DEFINE_PUBLIC_WEAK_SYMBOL(name, value, size)  __asm__(".type " __DEFINE_SYMBOL_STR(name) ", @object\n\t.weak " __DEFINE_SYMBOL_STR(name) "\n\t.global " __DEFINE_SYMBOL_STR(name) "\n\t.set " __DEFINE_SYMBOL_STR(name) ",%p0\n\t.size " __DEFINE_SYMBOL_STR(name) ",%p1" : : "X" (value), "X" (size))
#define DEFINE_INTERN_WEAK_SYMBOL(name, value, size)  __asm__(".type " __DEFINE_SYMBOL_STR(name) ", @object\n\t.weak " __DEFINE_SYMBOL_STR(name) "\n\t.global " __DEFINE_SYMBOL_STR(name) "\n\t.hidden " __DEFINE_SYMBOL_STR(name) "\n\t.set " __DEFINE_SYMBOL_STR(name) ",%p0\n\t.size " __DEFINE_SYMBOL_STR(name) ",%p1" : : "X" (value), "X" (size))



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
#define ATTR_PERVM       ATTR_SECTION(".data.pervm")   /* Per-virtual-memory template data. */
#define ATTR_PERTASK     ATTR_SECTION(".data.pertask") /* Per-task template data. */



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
#ifndef CONFIG_NO_DEBUGGER
#define BREAKPOINT() ({ FUNDEF void KCALL dbg(void); dbg(); })
#else /* !CONFIG_NO_DEBUGGER */
#define BREAKPOINT() (void)0 /* ??? */
#endif /* CONFIG_NO_DEBUGGER */
#endif /* !... */

#define __COMPILER_UNIQUE_IMPL2(x, y) x##y
#define __COMPILER_UNIQUE_IMPL(x, y) __COMPILER_UNIQUE_IMPL2(x, y)
#ifdef __COUNTER__
#define __COMPILER_UNIQUE(x) __COMPILER_UNIQUE_IMPL(x, __COUNTER__)
#else /* __COUNTER__ */
#define __COMPILER_UNIQUE(x) __COMPILER_UNIQUE_IMPL(x, __LINE__)
#endif /* !__COUNTER__ */




#if defined(__cplusplus) && defined(__CC__)
#include <__stdcxx.h>


/* Re-define `__builtin_offsetof()' to prevent GCC warnings about
 * offsetof() being undefined when we use type inheritace.
 * IT'S ONLY UNDEFINED WHEN THERE'S A V-TABLE, NOT IF EVERYTHING
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
		::refcnt_methods<T>::decref(&this->m_ptr);
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
		::refcnt_methods<T>::decref_likely(&this->m_ptr);
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
		::refcnt_methods<T>::decref_unlikely(&this->m_ptr);
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
		::refcnt_methods<T>::decref_nokill(&this->m_ptr);
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
		::refcnt_methods<T>::destroy(&this->m_ptr);
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
			::refcnt_methods<T>::decref(this->m_ptr);
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
			::refcnt_methods<T>::decref_likely(this->m_ptr);
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
			::refcnt_methods<T>::decref_unlikely(this->m_ptr);
	}
};

__NAMESPACE_INT_END

#define FINALLY_DECREF(ptr)           __NAMESPACE_INT_SYM _finally_decref<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fdecref)(*(ptr))
#define FINALLY_DECREF_LIKELY(ptr)    __NAMESPACE_INT_SYM _finally_decref_likely<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fdecref_l)(*(ptr))
#define FINALLY_DECREF_UNLIKELY(ptr)  __NAMESPACE_INT_SYM _finally_decref_unlikely<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fdecref_u)(*(ptr))
#define FINALLY_DECREF_NOKILL(ptr)    __NAMESPACE_INT_SYM _finally_decref_nokill<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fdecref_nk)(*(ptr))
#define FINALLY_DESTROY(ptr)          __NAMESPACE_INT_SYM _finally_destroy<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fdestroy)(*(ptr))
#define FINALLY_XDECREF(ptr)          __NAMESPACE_INT_SYM _finally_xdecref<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fxdecref)(ptr)
#define FINALLY_XDECREF_LIKELY(ptr)   __NAMESPACE_INT_SYM _finally_xdecref_likely<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fxdecref_l)(ptr)
#define FINALLY_XDECREF_UNLIKELY(ptr) __NAMESPACE_INT_SYM _finally_xdecref_unlikely<REFCNT_METHODS_BASE_P(*(ptr))> __COMPILER_UNIQUE(__fxdecref_u)(ptr)



#ifdef __INTELLISENSE__
template<class T> class sync_methods {
public:
	static NONNULL((1)) void (KCALL read)(T *__restrict self) THROWS(E_WOULDBLOCK, ...);
	static NONNULL((1)) void (KCALL write)(T *__restrict self) THROWS(E_WOULDBLOCK, ...);
	static NONNULL((1)) bool (KCALL upgrade)(T *__restrict self) THROWS(E_WOULDBLOCK, ...);
	static WUNUSED NONNULL((1)) bool (KCALL read_nx)(T *__restrict self) __CXX_NOEXCEPT;
	static WUNUSED NONNULL((1)) bool (KCALL write_nx)(T *__restrict self) __CXX_NOEXCEPT;
	static WUNUSED NONNULL((1)) unsigned int (KCALL upgrade_nx)(T *__restrict self) __CXX_NOEXCEPT;
	static WUNUSED NOBLOCK NONNULL((1)) bool (KCALL tryread)(T *__restrict self) __CXX_NOEXCEPT;
	static WUNUSED NOBLOCK NONNULL((1)) bool (KCALL trywrite)(T *__restrict self) __CXX_NOEXCEPT;
	static WUNUSED NOBLOCK NONNULL((1)) bool (KCALL tryupgrade)(T *__restrict self) __CXX_NOEXCEPT;
	static NOBLOCK NONNULL((1)) void (KCALL downgrade)(T *__restrict self) __CXX_NOEXCEPT;
	static NOBLOCK NONNULL((1)) void (KCALL endread)(T *__restrict self) __CXX_NOEXCEPT;
	static NOBLOCK NONNULL((1)) void (KCALL endwrite)(T *__restrict self) __CXX_NOEXCEPT;
	static NOBLOCK NONNULL((1)) void (KCALL end)(T *__restrict self) __CXX_NOEXCEPT;
	static WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL reading)(T const *__restrict self) __CXX_NOEXCEPT;
	static WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL writing)(T const *__restrict self) __CXX_NOEXCEPT;
	static WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL canread)(T const *__restrict self) __CXX_NOEXCEPT;
	static WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL canwrite)(T const *__restrict self) __CXX_NOEXCEPT;
};
#else /* __INTELLISENSE__ */
template<class T> class sync_methods;
#endif /* !__INTELLISENSE__ */
__NAMESPACE_INT_BEGIN
template<class T> class _sync_reader {
	__CXX_DELETE_CTOR(_sync_reader);
	__CXX_DELETE_COPY(_sync_reader);
	__CXX_DELETE_COPY_ASSIGN(_sync_reader);
private:
	T &m_lock;
public:
	__CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK _sync_reader(T &_lock): m_lock(_lock) {
		sync_methods<T>::read(&_lock);
	}
	__CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK ~_sync_reader() __CXX_NOEXCEPT {
		sync_methods<T>::endread(&m_lock);
	}
	__CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK operator bool() const __CXX_NOEXCEPT {
		return true;
	}
};
template<class T> class _sync_writer {
	__CXX_DELETE_CTOR(_sync_writer);
	__CXX_DELETE_COPY(_sync_writer);
	__CXX_DELETE_COPY_ASSIGN(_sync_writer);
private:
	T &m_lock;
public:
	__CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK _sync_writer(T &_lock): m_lock(_lock) {
		sync_methods<T>::write(&_lock);
	}
	__CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK ~_sync_writer() __CXX_NOEXCEPT {
		sync_methods<T>::endwrite(&m_lock);
	}
	__CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK operator bool() const __CXX_NOEXCEPT {
		return true;
	}
};
template<class T> class _finally_endread {
	__CXX_DELETE_CTOR(_finally_endread);
	__CXX_DELETE_COPY(_finally_endread);
	__CXX_DELETE_COPY_ASSIGN(_finally_endread);
private:
	T &m_lock;
public:
	__CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK _finally_endread(T &_lock) __CXX_NOEXCEPT
	    : m_lock(_lock) { }
	__CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK ~_finally_endread() __CXX_NOEXCEPT {
		sync_methods<T>::endread(&m_lock);
	}
	__CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK operator bool() const __CXX_NOEXCEPT {
		return true;
	}
};
template<class T> class _finally_endwrite {
	__CXX_DELETE_CTOR(_finally_endwrite);
	__CXX_DELETE_COPY(_finally_endwrite);
	__CXX_DELETE_COPY_ASSIGN(_finally_endwrite);
private:
	T &m_lock;
public:
	__CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK _finally_endwrite(T &_lock) __CXX_NOEXCEPT
	    : m_lock(_lock) { }
	__CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK ~_finally_endwrite() __CXX_NOEXCEPT {
		sync_methods<T>::endwrite(&m_lock);
	}
	__CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK operator bool() const __CXX_NOEXCEPT {
		return true;
	}
};
__NAMESPACE_INT_END
} /* extern "C++" */

#define SCOPED_READLOCK(lock)   __NAMESPACE_INT_SYM _sync_reader< __typeof__(*(lock)) > __COMPILER_UNIQUE(__rlock)(*(lock))
#define SCOPED_WRITELOCK(lock)  __NAMESPACE_INT_SYM _sync_writer< __typeof__(*(lock)) > __COMPILER_UNIQUE(__wlock)(*(lock))
#define FINALLY_ENDREAD(lock)   __NAMESPACE_INT_SYM _finally_endread< __typeof__(*(lock)) > __COMPILER_UNIQUE(__ferlock)(*(lock))
#define FINALLY_ENDWRITE(lock)  __NAMESPACE_INT_SYM _finally_endwrite< __typeof__(*(lock)) > __COMPILER_UNIQUE(__fewlock)(*(lock))

#define __DEFINE_SYNC_PROXY(T, field)                                                                                                                                          \
	extern "C++" {                                                                                                                                                             \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_tryread)(T *__restrict self) { return sync_tryread(&(self)->field); }                    \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_trywrite)(T *__restrict self) { return sync_trywrite(&(self)->field); }                  \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_tryupgrade)(T *__restrict self) { return sync_tryupgrade(&(self)->field); }              \
	/* Returns true if the lock could be upgraded without having to temporarily release all locks.                                                                             \
	 * NOTE: When this function returns by throwing an exception, the                                                                                                          \
	 *       previously acquired read-lock has already been released! */                                                                                                       \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) __BOOL (KCALL sync_upgrade)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { return sync_upgrade(&(self)->field); }       \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL sync_read)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { sync_read(&(self)->field); }                      \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL sync_write)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { sync_write(&(self)->field); }                    \
	/* NOTE: The lock is always upgraded for `return != 0', but when `2' is returned,                                                                                          \
	 *       no lock may have been held temporarily, meaning that the caller should                                                                                            \
	 *       re-load local copies of affected resources.                                                                                                                       \
	 * @return: 0 : A previously held read-lock was lost and could not be re-acquired.                                                                                         \
	 * @return: 1 : Successfully upgraded the read-only to a write-lock.                                                                                                       \
	 * @return: 2 : Successfully upgraded the read-only to a write-lock,                                                                                                       \
	 *              but at one point, no lock at all was being held. */                                                                                                        \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) WUNUSED unsigned int NOTHROW(KCALL sync_upgrade_nx)(T *__restrict self) { return sync_upgrade_nx(&(self)->field); }      \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) WUNUSED __BOOL NOTHROW(KCALL sync_read_nx)(T *__restrict self) { return sync_read_nx(&(self)->field); }                  \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) WUNUSED __BOOL NOTHROW(KCALL sync_write_nx)(T *__restrict self) { return sync_write_nx(&(self)->field); }                \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_downgrade)(T *__restrict self) { sync_downgrade(&(self)->field); }                                 \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_endread)(T *__restrict self) { sync_endread(&(self)->field); }                                     \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_endwrite)(T *__restrict self) { sync_endwrite(&(self)->field); }                                   \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_end)(T *__restrict self) { sync_end(&(self)->field); }                                             \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_reading)(T const *__restrict self) { return sync_reading(&(self)->field); }    \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_writing)(T const *__restrict self) { return sync_writing(&(self)->field); }    \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_canread)(T const *__restrict self) { return sync_canread(&(self)->field); }              \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_canwrite)(T const *__restrict self) { return sync_canwrite(&(self)->field); }            \
	template<> class sync_methods< T > {                                                                                                                                       \
	public:                                                                                                                                                                    \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL read)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { sync_read(&(self)->field); }         \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL write)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { sync_write(&(self)->field); }       \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) bool (KCALL upgrade)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { return sync_upgrade(&(self)->field); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT WUNUSED NONNULL((1)) bool (KCALL read_nx)(T *__restrict self) __CXX_NOEXCEPT { return sync_read_nx(&(self)->field); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT WUNUSED NONNULL((1)) bool (KCALL write_nx)(T *__restrict self) __CXX_NOEXCEPT { return sync_write_nx(&(self)->field); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT WUNUSED NONNULL((1)) unsigned int (KCALL upgrade_nx)(T *__restrict self) __CXX_NOEXCEPT { return sync_upgrade_nx(&(self)->field); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK NONNULL((1)) bool (KCALL tryread)(T *__restrict self) __CXX_NOEXCEPT { return sync_tryread(&(self)->field); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK NONNULL((1)) bool (KCALL trywrite)(T *__restrict self) __CXX_NOEXCEPT { return sync_trywrite(&(self)->field); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK NONNULL((1)) bool (KCALL tryupgrade)(T *__restrict self) __CXX_NOEXCEPT { return sync_tryupgrade(&(self)->field); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL downgrade)(T *__restrict self) __CXX_NOEXCEPT { sync_downgrade(&(self)->field); }            \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL endread)(T *__restrict self) __CXX_NOEXCEPT { sync_endread(&(self)->field); }                \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL endwrite)(T *__restrict self) __CXX_NOEXCEPT { sync_endwrite(&(self)->field); }              \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL end)(T *__restrict self) __CXX_NOEXCEPT { sync_end(&(self)->field); }                        \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL reading)(T const *__restrict self) __CXX_NOEXCEPT { return sync_reading(&(self)->field); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL writing)(T const *__restrict self) __CXX_NOEXCEPT { return sync_writing(&(self)->field); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL canread)(T const *__restrict self) __CXX_NOEXCEPT { return sync_canread(&(self)->field); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL canwrite)(T const *__restrict self) __CXX_NOEXCEPT { return sync_canwrite(&(self)->field); } \
	};                                                                                                                                                                         \
	}


#define __DEFINE_SYNC_RWLOCK(T, _tryread, _read, _read_nx, _endread, _reading, _canread,                                                                         \
                             _trywrite, _write, _write_nx, _endwrite, _writing, _canwrite,                                                                       \
                             _end, _tryupgrade, _upgrade, _upgrade_nx, _downgrade)                                                                               \
	extern "C++" {                                                                                                                                               \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_tryread)(T *__restrict self) { return _tryread(self); }                    \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_trywrite)(T *__restrict self) { return _trywrite(self); }                  \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_tryupgrade)(T *__restrict self) { return _tryupgrade(self); }              \
	/* Returns true if the lock could be upgraded without having to temporarily release all locks.                                                               \
	 * NOTE: When this function returns by throwing an exception, the                                                                                            \
	 *       previously acquired read-lock has already been released! */                                                                                         \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) __BOOL (KCALL sync_upgrade)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { return _upgrade(self); }       \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL sync_read)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { _read(self); }                      \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL sync_write)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { _write(self); }                    \
	/* NOTE: The lock is always upgraded for `return != 0', but when `2' is returned,                                                                            \
	 *       no lock may have been held temporarily, meaning that the caller should                                                                              \
	 *       re-load local copies of affected resources.                                                                                                         \
	 * @return: 0 : A previously held read-lock was lost and could not be re-acquired.                                                                           \
	 * @return: 1 : Successfully upgraded the read-only to a write-lock.                                                                                         \
	 * @return: 2 : Successfully upgraded the read-only to a write-lock,                                                                                         \
	 *              but at one point, no lock at all was being held. */                                                                                          \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) WUNUSED unsigned int NOTHROW(KCALL sync_upgrade_nx)(T *__restrict self) { return _upgrade_nx(self); }      \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) WUNUSED __BOOL NOTHROW(KCALL sync_read_nx)(T *__restrict self) { return _read_nx(self); }                  \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) WUNUSED __BOOL NOTHROW(KCALL sync_write_nx)(T *__restrict self) { return _write_nx(self); }                \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_downgrade)(T *__restrict self) { _downgrade(self); }                                 \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_endread)(T *__restrict self) { _endread(self); }                                     \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_endwrite)(T *__restrict self) { _endwrite(self); }                                   \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_end)(T *__restrict self) { _end(self); }                                             \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_reading)(T const *__restrict self) { return _reading(self); }    \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_writing)(T const *__restrict self) { return _writing(self); }    \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_canread)(T const *__restrict self) { return _canread(self); }    \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_canwrite)(T const *__restrict self) { return _canwrite(self); }  \
	template<> class sync_methods< T > {                                                                                                                         \
	public:                                                                                                                                                      \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL read)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { _read(self); }         \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL write)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { _write(self); }       \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) bool (KCALL upgrade)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { return _upgrade(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT WUNUSED NONNULL((1)) bool (KCALL read_nx)(T *__restrict self) __CXX_NOEXCEPT { return _read_nx(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT WUNUSED NONNULL((1)) bool (KCALL write_nx)(T *__restrict self) __CXX_NOEXCEPT { return _write_nx(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT WUNUSED NONNULL((1)) unsigned int (KCALL upgrade_nx)(T *__restrict self) __CXX_NOEXCEPT { return _upgrade_nx(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK NONNULL((1)) bool (KCALL tryread)(T *__restrict self) __CXX_NOEXCEPT { return _tryread(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK NONNULL((1)) bool (KCALL trywrite)(T *__restrict self) __CXX_NOEXCEPT { return _trywrite(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK NONNULL((1)) bool (KCALL tryupgrade)(T *__restrict self) __CXX_NOEXCEPT { return _tryupgrade(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL downgrade)(T *__restrict self) __CXX_NOEXCEPT { _downgrade(self); }            \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL endread)(T *__restrict self) __CXX_NOEXCEPT { _endread(self); }                \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL endwrite)(T *__restrict self) __CXX_NOEXCEPT { _endwrite(self); }              \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL end)(T *__restrict self) __CXX_NOEXCEPT { _end(self); }                        \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL reading)(T const *__restrict self) __CXX_NOEXCEPT { return _reading(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL writing)(T const *__restrict self) __CXX_NOEXCEPT { return _writing(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL canread)(T const *__restrict self) __CXX_NOEXCEPT { return _canread(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL canwrite)(T const *__restrict self) __CXX_NOEXCEPT { return _canwrite(self); } \
	};                                                                                                                                                           \
	}

#define __DEFINE_SYNC_MUTEX(T, _tryacquire, _acquire, _acquire_nx, _release, _acquired, _available)                                                       \
	extern "C++" {                                                                                                                                        \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_tryread)(T *__restrict self) { return _tryacquire(self); }          \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_trywrite)(T *__restrict self) { return _tryacquire(self); }         \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_tryupgrade)(T *__restrict UNUSED(self)) { return true; }            \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_downgrade)(T *__restrict UNUSED(self)) { }                                    \
	/* Returns true if the lock could be upgraded without having to temporarily release all locks.                                                        \
	 * NOTE: When this function returns by throwing an exception, the                                                                                     \
	 *       previously acquired read-lock has already been released! */                                                                                  \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) __BOOL NOTHROW(KCALL sync_upgrade)(T *__restrict UNUSED(self)) { return true; }                     \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL sync_read)(T *__restrict self) { _acquire(self); }                                      \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL sync_write)(T *__restrict self) { _acquire(self); }                                     \
	/* NOTE: The lock is always upgraded for `return != 0', but when `2' is returned,                                                                     \
	 *       no lock may have been held temporarily, meaning that the caller should                                                                       \
	 *       re-load local copies of affected resources.                                                                                                  \
	 * @return: 0 : A previously held read-lock was lost and could not be re-acquired.                                                                    \
	 * @return: 1 : Successfully upgraded the read-only to a write-lock.                                                                                  \
	 * @return: 2 : Successfully upgraded the read-only to a write-lock,                                                                                  \
	 *              but at one point, no lock at all was being held. */                                                                                   \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) unsigned int NOTHROW(KCALL sync_upgrade_nx)(T *__restrict UNUSED(self)) { return 1; }               \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) WUNUSED __BOOL NOTHROW(KCALL sync_read_nx)(T *__restrict self) { return _acquire_nx(self); }        \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) WUNUSED __BOOL NOTHROW(KCALL sync_write_nx)(T *__restrict self) { return _acquire_nx(self); }       \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_endread)(T *__restrict self) { _release(self); }                              \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_endwrite)(T *__restrict self) { _release(self); }                             \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_end)(T *__restrict self) { _release(self); }                                  \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_reading)(T const *__restrict self) { return _acquired(self); } \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_writing)(T const *__restrict self) { return _acquired(self); } \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_canread)(T const *__restrict self) { return _available(self); } \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_canwrite)(T const *__restrict self) { return _available(self); } \
	template<> class sync_methods< T > {                                                                                                                  \
	public:                                                                                                                                               \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL read)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { _acquire(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL write)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { _acquire(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) bool (KCALL upgrade)(T *__restrict UNUSED(self)) THROWS(E_WOULDBLOCK, ...) { return true; } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT WUNUSED NONNULL((1)) bool (KCALL read_nx)(T *__restrict self) __CXX_NOEXCEPT { return _acquire_nx(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT WUNUSED NONNULL((1)) bool (KCALL write_nx)(T *__restrict self) __CXX_NOEXCEPT { return _acquire_nx(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT WUNUSED NONNULL((1)) unsigned int (KCALL upgrade_nx)(T *__restrict UNUSED(self)) __CXX_NOEXCEPT { return 1; } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK NONNULL((1)) bool (KCALL tryread)(T *__restrict self) __CXX_NOEXCEPT { return _tryacquire(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK NONNULL((1)) bool (KCALL trywrite)(T *__restrict self) __CXX_NOEXCEPT { return _tryacquire(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK NONNULL((1)) bool (KCALL tryupgrade)(T *__restrict UNUSED(self)) __CXX_NOEXCEPT { return true; } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL downgrade)(T *__restrict UNUSED(self)) __CXX_NOEXCEPT { }               \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL endread)(T *__restrict self) __CXX_NOEXCEPT { _release(self); }         \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL endwrite)(T *__restrict self) __CXX_NOEXCEPT { _release(self); }        \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL end)(T *__restrict self) __CXX_NOEXCEPT { _release(self); }             \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL reading)(T const *__restrict self) __CXX_NOEXCEPT { return _acquired(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL writing)(T const *__restrict self) __CXX_NOEXCEPT { return _acquired(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL canread)(T const *__restrict self) __CXX_NOEXCEPT { return _available(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL canwrite)(T const *__restrict self) __CXX_NOEXCEPT { return _available(self); } \
	};                                                                                                                                                    \
	}

#define __DEFINE_SYNC_SEMAPHORE(T, _trywait, _wait, _wait_nx, _post, _available)                                                                          \
	extern "C++" {                                                                                                                                        \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_tryread)(T *__restrict self) { return _trywait(self); }             \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_trywrite)(T *__restrict self) { return _trywait(self); }            \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_tryupgrade)(T *__restrict UNUSED(self)) { return true; }            \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_downgrade)(T *__restrict UNUSED(self)) { }                                    \
	/* Returns true if the lock could be upgraded without having to temporarily release all locks.                                                        \
	 * NOTE: When this function returns by throwing an exception, the                                                                                     \
	 *       previously acquired read-lock has already been released! */                                                                                  \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) __BOOL NOTHROW(KCALL sync_upgrade)(T *__restrict UNUSED(self)) { return true; }                     \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL sync_read)(T *__restrict self) { _wait(self); }                                         \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL sync_write)(T *__restrict self) { _wait(self); }                                        \
	/* NOTE: The lock is always upgraded for `return != 0', but when `2' is returned,                                                                     \
	 *       no lock may have been held temporarily, meaning that the caller should                                                                       \
	 *       re-load local copies of affected resources.                                                                                                  \
	 * @return: 0 : A previously held read-lock was lost and could not be re-acquired.                                                                    \
	 * @return: 1 : Successfully upgraded the read-only to a write-lock.                                                                                  \
	 * @return: 2 : Successfully upgraded the read-only to a write-lock,                                                                                  \
	 *              but at one point, no lock at all was being held. */                                                                                   \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) unsigned int NOTHROW(KCALL sync_upgrade_nx)(T *__restrict UNUSED(self)) { return 1; }               \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) WUNUSED __BOOL NOTHROW(KCALL sync_read_nx)(T *__restrict self) { return _wait_nx(self); }           \
	FORCELOCAL ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) WUNUSED __BOOL NOTHROW(KCALL sync_write_nx)(T *__restrict self) { return _wait_nx(self); }          \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_endread)(T *__restrict self) { _post(self); }                                 \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_endwrite)(T *__restrict self) { _post(self); }                                \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void NOTHROW(KCALL sync_end)(T *__restrict self) { _post(self); }                                     \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_reading)(T const *__restrict UNUSED(self)) { return true; } \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_writing)(T const *__restrict UNUSED(self)) { return true; } \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_canread)(T const *__restrict self) { return _available(self); } \
	FORCELOCAL ATTR_ARTIFICIAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL NOTHROW(KCALL sync_canwrite)(T const *__restrict self) { return _available(self); } \
	template<> class sync_methods< T > {                                                                                                                  \
	public:                                                                                                                                               \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL read)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { _wait(self); }  \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) void (KCALL write)(T *__restrict self) THROWS(E_WOULDBLOCK, ...) { _wait(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOCONNECT NONNULL((1)) bool (KCALL upgrade)(T *__restrict UNUSED(self)) THROWS(E_WOULDBLOCK, ...) { return true; } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOCONNECT NONNULL((1)) bool (KCALL read_nx)(T *__restrict self) __CXX_NOEXCEPT { return _wait_nx(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOCONNECT NONNULL((1)) bool (KCALL write_nx)(T *__restrict self) __CXX_NOEXCEPT { return _wait_nx(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOCONNECT NONNULL((1)) unsigned int (KCALL upgrade_nx)(T *__restrict UNUSED(self)) __CXX_NOEXCEPT { return 1; } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK NONNULL((1)) bool (KCALL tryread)(T *__restrict self) __CXX_NOEXCEPT { return _trywait(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK NONNULL((1)) bool (KCALL trywrite)(T *__restrict self) __CXX_NOEXCEPT { return _trywait(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK NONNULL((1)) bool (KCALL tryupgrade)(T *__restrict UNUSED(self)) __CXX_NOEXCEPT { return true; } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL downgrade)(T *__restrict UNUSED(self)) __CXX_NOEXCEPT { }               \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL endread)(T *__restrict self) __CXX_NOEXCEPT { _post(self); }            \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL endwrite)(T *__restrict self) __CXX_NOEXCEPT { _post(self); }           \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void (KCALL end)(T *__restrict self) __CXX_NOEXCEPT { _post(self); }                \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL reading)(T const *__restrict UNUSED(self)) __CXX_NOEXCEPT { return true; } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL writing)(T const *__restrict UNUSED(self)) __CXX_NOEXCEPT { return true; } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL canread)(T const *__restrict self) __CXX_NOEXCEPT { return _available(self); } \
		static __CXX_FORCEINLINE ATTR_ARTIFICIAL WUNUSED NOBLOCK ATTR_PURE NONNULL((1)) bool (KCALL canwrite)(T const *__restrict self) __CXX_NOEXCEPT { return _available(self); } \
	};                                                                                                                                                    \
	}



#else /* __cplusplus */
#define __DEFINE_SYNC_PROXY(T, field)                                  /* nothing */
#define __DEFINE_SYNC_RWLOCK(T, _tryread, _read, _read_nx, _endread, _reading, _canread,   \
                             _trywrite, _write, _write_nx, _endwrite, _writing, _canwrite, \
                             _end, _tryupgrade, _upgrade, _upgrade_nx, _downgrade)                  /* nothing */
#define __DEFINE_SYNC_MUTEX(T, _tryacquire, _acquire, _acquire_nx, _release, _acquired, _available) /* nothing */
#define __DEFINE_SYNC_SEMAPHORE(T, _trywait, _wait, _wait_nx, _post, _available)                    /* nothing */
#endif /* !__cplusplus */

#define DEFINE_REFCOUNT_FUNCTIONS        __DEFINE_REFCNT_FUNCTIONS
#define DEFINE_REFCOUNT_FUNCTIONS_EX     __DEFINE_REFCNT_FUNCTIONS_EX
#define DEFINE_WEAKREFCOUNT_FUNCTIONS    __DEFINE_WEAKREFCNT_FUNCTIONS
#define DEFINE_WEAKREFCOUNT_FUNCTIONS_EX __DEFINE_WEAKREFCNT_FUNCTIONS_EX

#include <kernel/arch/compiler.h>

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_COMPILER_H */
