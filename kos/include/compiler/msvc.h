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
/*!included_by <__stdinc.h>*/
#define __builtin_expect(x, y) (x)
#define __NO_builtin_expect
#define __likely   /* Nothing */
#define __unlikely /* Nothing */
#define __P(x)     x

#ifndef __STDC__
/* We need `__STDC__' to be defined since its the indicator for a modern preprocessor to be available. */
#define __STDC__ 1
#endif /* !__STDC__ */

#if defined(_MSC_EXTENSIONS) || _MSC_VER >= 1400
#define __COMPILER_HAVE_LONGLONG
#endif /* _MSC_EXTENSIONS || _MSC_VER >= 1400 */
#define __COMPILER_HAVE_LONGDOUBLE
#ifndef __LONGDOUBLE
#define __LONGDOUBLE long double
#endif /* !__LONGDOUBLE */
#if defined(_MSC_EXTENSIONS)/* || _MSC_VER >= ???? */
#define __COMPILER_HAVE_TRANSPARENT_STRUCT
#endif /* _MSC_EXTENSIONS */
#define __COMPILER_HAVE_TRANSPARENT_UNION
#define __COMPILER_HAVE_PRAGMA_PUSHMACRO
#define __COMPILER_HAVE_PRAGMA_DEPRECATED
#ifdef __CC__
#define __COMPILER_HAVE_PRAGMA_PACK
#endif /* __CC__ */

#ifndef __has_builtin
#define __NO_has_builtin
#define __has_builtin(x) 0
#endif /* !__has_builtin */

#ifndef __has_feature
#define __NO_has_feature
#define __has_feature(x) 0
#endif /* !__has_feature */

#ifndef __has_extension
#ifndef __NO_has_feature
#define __NO_has_extension
#endif /* !__NO_has_feature */
#define __has_extension __has_feature
#endif /* !__has_extension */

#ifndef __has_attribute
#define __NO_has_attribute
#define __has_attribute(x) 0
#endif /* !__has_attribute */

#ifndef __has_declspec_attribute
#define __NO_has_declspec_attribute
#define __has_declspec_attribute(x) 0
#endif /* !__has_declspec_attribute */

#ifndef __has_cpp_attribute
#define __NO_has_cpp_attribute
#define __has_cpp_attribute(x) 0
#endif /* !__has_cpp_attribute */

#ifndef __has_include
#define __NO_has_include
#define __has_include(x) 0
#endif /* !__has_include */

#ifndef __has_include_next
#define __NO_has_include_next
#define __has_include_next(x) 0
#endif /* !__has_include */

/* Try to detect the "Visual Assist X Inspector" (which uses a weird port of clang) */
#if (defined(__cplusplus) && defined(__STDC_NO_THREADS__) && \
     !defined(__NO_has_builtin) && __has_builtin(__builtin_choose_expr))
#define __VASSISTX_INSPECT__
#endif /* ... */



#if __has_feature(cxx_auto_type) || \
   (defined(__cplusplus) && _MSC_VER >= 1600)
#define __auto_type auto
#define __COMPILER_HAVE_AUTOTYPE
#endif /* ... */

#if (__has_feature(cxx_static_assert) ||                               \
     (defined(__cpp_static_assert) && __cpp_static_assert + 0 != 0) || \
     _MSC_VER >= 1600)
#if defined(__cpp_static_assert) && __cpp_static_assert + 0 >= 201411
#define __STATIC_ASSERT_IS_static_assert
#define __STATIC_ASSERT static_assert
#else /* __cpp_static_assert >= 201411 */
#define __STATIC_ASSERT(expr) static_assert(expr, #expr)
#endif /* __cpp_static_assert < 201411 */
#define __STATIC_ASSERT_MSG_IS_static_assert
#define __STATIC_ASSERT_MSG static_assert
#elif (__has_feature(c_static_assert) || \
       (defined(__STDC_VERSION__) && __STDC_VERSION__ + 0 >= 201112L))
/* XXX: Knowing Visual C/C++, checking for C11 may not actually allow us to assume this one... */
#define __STATIC_ASSERT_IS__Static_assert
#define __STATIC_ASSERT(expr) _Static_assert(expr, #expr)
#define __STATIC_ASSERT_MSG   _Static_assert
#elif defined(__TPP_COUNTER)
#define __STATIC_ASSERT(expr)          typedef int __PP_CAT2(__static_assert_, __TPP_COUNTER(__static_assert))[(expr) ? 1 : -1]
#define __STATIC_ASSERT_MSG(expr, msg) typedef int __PP_CAT2(__static_assert_, __TPP_COUNTER(__static_assert))[(expr) ? 1 : -1]
#elif defined(__COUNTER__)
#define __STATIC_ASSERT(expr)          typedef int __PP_CAT2(__static_assert_, __COUNTER__)[(expr) ? 1 : -1]
#define __STATIC_ASSERT_MSG(expr, msg) typedef int __PP_CAT2(__static_assert_, __COUNTER__)[(expr) ? 1 : -1]
#else /* ... */
#define __STATIC_ASSERT(expr)          typedef int __PP_CAT2(__static_assert_, __LINE__)[(expr) ? 1 : -1]
#define __STATIC_ASSERT_MSG(expr, msg) typedef int __PP_CAT2(__static_assert_, __LINE__)[(expr) ? 1 : -1]
#endif /* !... */
#define __NO_ASMNAME
#define __COMPILER_ASMNAME(x) /* Nothing */
#define __extension__ /* Nothing */
#define __ATTR_NOINLINE __declspec(noinline)

#if _MSC_VER >= 1200
#define __ATTR_NORETURN_IS___declspec_noreturn
#define __ATTR_NORETURN __declspec(noreturn)
#else /* _MSC_VER >= 1200 */
#define __NO_ATTR_NORETURN
#define __ATTR_NORETURN /* Nothing */
#endif /* _MSC_VER < 1200 */
#define __NO_ATTR_FALLTHROUGH
#define __ATTR_FALLTHROUGH /* Nothing */
#if !defined(__midl) && (defined(_X86_) || defined(_M_IX86))
#define __ATTR_W64 __w64
#else /* !__midl && (_X86_ || _M_IX86) */
#define __NO_ATTR_W64
#define __ATTR_W64 /* Nothing */
#endif /* __midl || (!_X86_ && !_M_IX86) */
#define __ATTR_FASTCALL_IS___fastcall
#define __ATTR_FASTCALL __fastcall
#define __ATTR_STDCALL_IS___stdcall
#define __ATTR_STDCALL __stdcall
#define __ATTR_CDECL_IS___cdecl
#define __ATTR_CDECL __cdecl
#define __ATTR_THISCALL_IS___thiscall
#define __ATTR_THISCALL __thiscall
#ifdef _M_CEE_PURE
#define __ATTR_CLRCALL_IS___clrcall
#define __ATTR_CLRCALL __clrcall
#else /* _M_CEE_PURE */
#define __NO_ATTR_CLRCALL
#define __ATTR_CLRCALL /* Nothing */
#endif /* !_M_CEE_PURE */
#if (defined(__x86_64__) || defined(__amd64__) || defined(__amd64) || \
     defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64))
#define __ATTR_MSABI /* Nothing (default) */
#else /* X64... */
#define __NO_ATTR_MSABI
#define __ATTR_MSABI /* Nothing */
#endif /* !X64... */
#define __NO_ATTR_SYSVABI
#define __ATTR_SYSVABI /* Nothing */
#define __ATTR_PURE  __declspec(noalias)
#define __ATTR_CONST __declspec(noalias)
#define __NO_ATTR_LEAF
#define __ATTR_LEAF /* Nothing */
#define __NO_ATTR_FLATTEN
#define __ATTR_FLATTEN /* Nothing */
#define __ATTR_MALLOC __declspec(restrict)
#define __NO_ATTR_HOT
#define __ATTR_HOT /* Nothing */
#define __NO_ATTR_COLD
#define __ATTR_COLD /* Nothing */
#define __NO_ATTR_ALLOC_SIZE
#define __ATTR_ALLOC_SIZE(ppars) /* Nothing */
#define __NO_ATTR_ALLOC_ALIGN
#define __ATTR_ALLOC_ALIGN(pari) /* Nothing */
#define __NO_ATTR_ASSUME_ALIGNED
#define __ATTR_ASSUME_ALIGNED(n) /* Nothing */
#define __NO_ATTR_NOCLONE
#define __ATTR_NOCLONE /* Nothing */
#define __NO_ATTR_USED
#define __ATTR_USED /* Nothing */
#define __NO_ATTR_UNUSED
#define __ATTR_UNUSED /* Nothing */
#define __NO_ATTR_SENTINEL
#define __ATTR_SENTINEL /* Nothing */
#define __NO_ATTR_SENTINEL_O
#define __ATTR_SENTINEL_O(x) /* Nothing */
#if _MSC_VER >= 1700
#define __ATTR_THREAD_IS___declspec_thread
#define __ATTR_THREAD __declspec(thread)
#else /* _MSC_VER >= 1700 */
#define __NO_ATTR_THREAD
#define __ATTR_THREAD /* Nothing */
#endif /* _MSC_VER < 1700 */
#if _MSC_VER >= 1200
#define __ATTR_DEPRECATED_      __declspec(deprecated)
#define __ATTR_DEPRECATED(text) __declspec(deprecated(text))
#else /* _MSC_VER >= 1200 */
#define __NO_ATTR_DEPRECATED
#define __ATTR_DEPRECATED(text) /* Nothing */
#endif /* _MSC_VER < 1200 */
#define __NO_ATTR_ERROR
#define __ATTR_ERROR(text) /* Nothing */
#define __NO_ATTR_WARNING
#define __ATTR_WARNING(text) /* Nothing */
#define __NO_ATTR_SECTION
#define __ATTR_SECTION(name) /* Nothing */
#ifdef __cplusplus
#define __ATTR_NOTHROW __declspec(nothrow)
#else /* __cplusplus */
#define __NO_ATTR_NOTHROW
#define __ATTR_NOTHROW /* Nothing */
#endif /* !__cplusplus */
#define __NO_ATTR_OPTIMIZE
#define __ATTR_OPTIMIZE(opt) /* Nothing */
#define __NO_ATTR_NOTHROW_SUFFIX
#define __NO_ATTR_RETNONNULL
#define __ATTR_RETNONNULL /* Nothing */
#define __NO_ATTR_PACKED
#define __ATTR_PACKED /* Nothing */
#define __NO_ATTR_ALIAS
#define __ATTR_ALIAS(name) /* Nothing */
#if _MSC_VER >= 1300
#define __ATTR_ALIGNED(n) __declspec(align(n))
#else /* _MSC_VER >= 1300 */
#define __NO_ATTR_ALIGNED
#define __ATTR_ALIGNED(n) /* Nothing */
#endif /* _MSC_VER < 1300 */
#define __ATTR_WEAK_IS_ATTR_SELECTANY
#define __ATTR_WEAK      __declspec(selectany) /* For all that we care, it's basically the same. */
#define __ATTR_SELECTANY __declspec(selectany)
#define __NO_ATTR_RETURNS_TWICE
#define __ATTR_RETURNS_TWICE /* Nothing */
#define __NO_ATTR_EXTERNALLY_VISIBLE
#define __ATTR_EXTERNALLY_VISIBLE /* Nothing */
#define __NO_ATTR_VISIBILITY
#define __ATTR_VISIBILITY(vis) /* Nothing */
#define __NO_ATTR_FORMAT_PRINTF
#define __ATTR_FORMAT_PRINTF(fmt, args) /* Nothing */
#define __NO_ATTR_FORMAT_SCANF
#define __ATTR_FORMAT_SCANF(fmt, args) /* Nothing */
#define __NO_ATTR_FORMAT_STRFMON
#define __ATTR_FORMAT_STRFMON(fmt, args) /* Nothing */
#define __NO_ATTR_FORMAT_STRFTIME
#define __ATTR_FORMAT_STRFTIME(fmt, args) /* Nothing */
#define __ATTR_DLLIMPORT __declspec(dllimport)
#define __ATTR_DLLEXPORT __declspec(dllexport)
#define __NO_ATTR_NOPLT
#define __ATTR_NOPLT /* Nothing */
#define __NO_ATTR_NONNULL
#define __ATTR_NONNULL(ppars)     /* Nothing */
#define __ATTR_NONNULL_CXX(ppars) /* Nothing */
#define __NO_ATTR_WUNUSED
#define __ATTR_WUNUSED /* Nothing */
#define __NO_ATTR_TRANSPARENT_UNION
#define __ATTR_TRANSPARENT_UNION /* Nothing */
#define __NO_ATTR_ARTIFICIAL
#define __ATTR_ARTIFICIAL /* Nothing */
#define __NO_ATTR_FORMAT_ARG
#define __ATTR_FORMAT_ARG(x) /* Nothing */
#define __NO_ATTR_ACCESS
#define __ATTR_ACCESS_NONE(ptr_index)        /* Nothing */
#define __ATTR_INS(ptr_index, size_index)    /* Nothing */
#define __ATTR_OUTS(ptr_index, size_index)   /* Nothing */
#define __ATTR_INOUTS(ptr_index, size_index) /* Nothing */
#define __ATTR_IN_OPT(ptr_index)             /* Nothing */
#define __ATTR_OUT_OPT(ptr_index)            /* Nothing */
#define __ATTR_INOUT_OPT(ptr_index)          /* Nothing */
#define __ATTR_IN(ptr_index)                 /* Nothing */
#define __ATTR_OUT(ptr_index)                /* Nothing */
#define __ATTR_INOUT(ptr_index)              /* Nothing */
#define __ATTR_FDARG(fd_index)               /* Nothing */
#define __ATTR_FDREAD(fd_index)              /* Nothing */
#define __ATTR_FDWRITE(fd_index)             /* Nothing */

#define __IF0    __pragma(warning(suppress: 4127)) if(0)
#define __IF1    __pragma(warning(suppress: 4127)) if(1)
#define __WHILE0 __pragma(warning(suppress: 4127)) while(0)
#define __WHILE1 __pragma(warning(suppress: 4127)) while(1)

#ifdef __cplusplus
namespace __intern {
template<bool> struct __msvc_static_if {};
template<> struct __msvc_static_if<true> { bool __is_true__(); };
}
#define __STATIC_IF(c) \
	__if_exists(::__intern::__msvc_static_if<((c))>::__is_true__)
#define __STATIC_ELSE(c) \
	__if_not_exists(::__intern::__msvc_static_if<((c))>::__is_true__)
/* Use our hacky `static_if' to emulate `__builtin_choose_expr' */
#define __builtin_choose_expr(c, tt, ff) (__STATIC_IF(c){tt} __STATIC_ELSE(c){ff})
#else /* __cplusplus */
#define __STATIC_IF(x)   __pragma(warning(suppress : 4127)) if(x)
#define __STATIC_ELSE(x) __pragma(warning(suppress : 4127)) if(x)
#define __NO_builtin_choose_expr
#define __builtin_choose_expr(c, tt, ff) ((c) ? (tt) : (ff))
#endif /* !__cplusplus */

#define __NO_builtin_types_compatible_p
#define __builtin_types_compatible_p(...) 1

#ifdef __clang__
#define __XBLOCK  /* Nothing */
#define __XRETURN /* Nothing */
#else /* __clang__ */
#define __NO_XBLOCK
#define __XBLOCK(...) do __VA_ARGS__ __WHILE0
#define __XRETURN /* Nothing */
#endif /* !__clang__ */

#undef __builtin_assume_has_sideeffects
#define __builtin_assume(x) __assume(x)

#define __builtin_LINE() __LINE__
#define __builtin_FILE() __FILE__
#define __builtin_FUNCTION() __FUNCTION__
#define __builtin_unreachable() __assume(0)
#define __COMPILER_ALIGNOF_IS___alignof
#define __COMPILER_ALIGNOF __alignof
#define __builtin_offsetof(s, m) ((__SIZE_TYPE__) & ((s *)0)->m)
#define __ATTR_INLINE_IS___inline
#define __ATTR_INLINE      __inline
#define __ATTR_FORCEINLINE_IS___FORCEINLINE
#define __ATTR_FORCEINLINE __forceinline
#define __LOCAL            static __inline
#define __FORCELOCAL       static __forceinline
#define __NO_EXTERN_INLINE
#define __EXTERN_INLINE      static __inline
#define __EXTERN_FORCEINLINE static __forceinline
#define __LONGLONG           long long
#define __ULONGLONG          unsigned long long
#define __NO_builtin_constant_p
#define __builtin_constant_p(x) (__LINE__ == -1)
#define __restrict_arr __restrict
#define __COMPILER_HAVE_VARIABLE_LENGTH_ARRAYS
#define __COMPILER_FLEXIBLE_ARRAY(T, x) T x[0xffff]
#define __attribute__(x)         /* Nothing */
#define __NO_COMPILER_IGNORE_UNINITIALIZED
#define __COMPILER_IGNORE_UNINITIALIZED(var) var
#define __COMPILER_DELETE_ASSUMPTIONS(var) (void)0

#define __INT8_TYPE__   signed __int8
#define __UINT8_TYPE__  unsigned __int8
#define __INT16_TYPE__  signed __int16
#define __UINT16_TYPE__ unsigned __int16
#define __INT32_TYPE__  signed __int32
#define __UINT32_TYPE__ unsigned __int32
#define __INT64_TYPE__  signed __int64
#define __UINT64_TYPE__ unsigned __int64

#ifndef __USER_LABEL_PREFIX__
#if (defined(__x86_64__) || defined(__amd64__) || defined(__amd64) || \
     defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64) ||     \
     defined(_WIN64) || defined(WIN64))
#define __USER_LABEL_PREFIX_IS_EMPTY
#define __USER_LABEL_PREFIX__ /* Nothing */
#else /* ... */
#define __USER_LABEL_PREFIX__ _
#endif /* !... */
#endif /* !__USER_LABEL_PREFIX__ */

#define __DEFINE_ALIAS_STR(x) #x
#define __DEFINE_PRIVATE_ALIAS(new, old) \
	__pragma(comment(linker, "/alternatename:" __DEFINE_ALIAS_STR(new) "=" __DEFINE_ALIAS_STR(old)))
#define __DEFINE_PUBLIC_ALIAS(new, old)                                                              \
	__pragma(comment(linker, "/alternatename:" __DEFINE_ALIAS_STR(new) "=" __DEFINE_ALIAS_STR(old))) \
	__pragma(comment(linker, "/export:" __DEFINE_ALIAS_STR(new)))
#define __DEFINE_INTERN_ALIAS(new, old) \
	__pragma(comment(linker, "/alternatename:" __DEFINE_ALIAS_STR(new) "=" __DEFINE_ALIAS_STR(old)))

/* TODO: selectany? */
#define __DEFINE_PRIVATE_WEAK_ALIAS(new, old) __DEFINE_PRIVATE_ALIAS(new, old)
#define __DEFINE_PUBLIC_WEAK_ALIAS(new, old)  __DEFINE_PUBLIC_ALIAS(new, old)
#define __DEFINE_INTERN_WEAK_ALIAS(new, old)  __DEFINE_INTERN_ALIAS(new, old)


#if !defined(__INTELLISENSE__)
/* This works, but may be very  expensive because I've got a  feeling
 * that all of these ~comments~ must be passed via the commandline... */
#define __REDIRECT_PP_STR2(x) #x
#define __REDIRECT_PP_STR(x) __REDIRECT_PP_STR2(x)
#define __REDIRECT_ASSEMBLY(x, y)                                                                                                                        \
	__pragma(comment(linker, "/alternatename:" __REDIRECT_PP_STR(__USER_LABEL_PREFIX__) #x "=" __REDIRECT_PP_STR(__USER_LABEL_PREFIX__) #y))             \
	__pragma(comment(linker, "/alternatename:__imp_" __REDIRECT_PP_STR(__USER_LABEL_PREFIX__) #x "=__imp_" __REDIRECT_PP_STR(__USER_LABEL_PREFIX__) #y)) \
	__pragma(comment(linker, "/alternatename:__imp__" __REDIRECT_PP_STR(__USER_LABEL_PREFIX__) #x "=__imp__" __REDIRECT_PP_STR(__USER_LABEL_PREFIX__) #y))
#define __COMPILER_SREDIRECT(decl,attr,T,name,asmname)                                                                  decl attr T name; __REDIRECT_ASSEMBLY(name,asmname)
#define __COMPILER_SREDIRECT2(decl,attr,Tdecl,name,asmname)                                                             decl attr Tdecl; __REDIRECT_ASSEMBLY(name,asmname)
#define __COMPILER_REDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args)                                       decl attr Treturn nothrow(cc name) param; __REDIRECT_ASSEMBLY(name,asmname)
#define __COMPILER_REDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args)                                          decl attr void nothrow(cc name) param; __REDIRECT_ASSEMBLY(name,asmname)
#define __COMPILER_VREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)    decl attr Treturn nothrow(cc name) (____PRIVATE_VREDIRECT_UNPACK param,...); __REDIRECT_ASSEMBLY(name,asmname)
#define __COMPILER_VREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)       decl attr void nothrow(cc name) (____PRIVATE_VREDIRECT_UNPACK param,...); __REDIRECT_ASSEMBLY(name,asmname)
#define __COMPILER_VFREDIRECT(decl,attr,Treturn,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) decl attr Treturn nothrow(cc name) paramf; __REDIRECT_ASSEMBLY(name,asmnamef)
#define __COMPILER_VFREDIRECT_VOID(decl,attr,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    decl attr void nothrow(cc name) paramf; __REDIRECT_ASSEMBLY(name,asmnamef)
#define __COMPILER_XREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code)                                      decl attr Treturn nothrow(cc name) param; __REDIRECT_ASSEMBLY(name,asmname)
#define __COMPILER_XREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code)                                         decl attr void nothrow(cc name) param; __REDIRECT_ASSEMBLY(name,asmname)
#endif /* !__INTELLISENSE__ */



/* Define intrinsic barrier functions. */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#if (defined(__i386__) || defined(__i386) || defined(i386) ||          \
     defined(__I86__) || defined(_M_IX86) || defined(__X86__) ||       \
     defined(_X86_) || defined(__THW_INTEL__) || defined(__INTEL__) || \
     defined(__x86_64__) || defined(__amd64__) || defined(__amd64) ||  \
     defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64) ||      \
     defined(_WIN64) || defined(WIN64))
#ifndef _m_prefetch
#define _m_prefetch _m_prefetch
extern void (__cdecl _m_prefetch)(void *);
#pragma intrinsic(_m_prefetch)
#endif /* !_m_prefetch */
#define __builtin_prefetch(addr, ...) _m_prefetch(addr)
#else /* ... */
#define __NO_builtin_prefetch   1
#define __builtin_prefetch(...) (void)0
#endif /* !... */
#ifndef _ReadBarrier
#define _ReadBarrier _ReadBarrier
extern void (__cdecl _ReadBarrier)(void);
#pragma intrinsic(_ReadBarrier)
#endif /* !_ReadBarrier */
#ifndef _WriteBarrier
#define _WriteBarrier _WriteBarrier
extern void (__cdecl _WriteBarrier)(void);
#pragma intrinsic(_WriteBarrier)
#endif /* !_WriteBarrier */
#ifndef _ReadWriteBarrier
#define _ReadWriteBarrier _ReadWriteBarrier
extern void (__cdecl _ReadWriteBarrier)(void);
#pragma intrinsic(_ReadWriteBarrier)
#endif /* !_ReadWriteBarrier */
#define __COMPILER_BARRIER()       _ReadWriteBarrier()
#define __COMPILER_READ_BARRIER()  _ReadBarrier()
#define __COMPILER_WRITE_BARRIER() _WriteBarrier()
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#define __COMPILER_IMPURE() (void)0

#ifdef __cplusplus
#if defined(__INTELLISENSE__) || defined(__VASSISTX_INSPECT__)
#define __NULLPTR nullptr
#else /* __INTELLISENSE__ */
#define __NULLPTR 0
#endif /* !__INTELLISENSE__ */
#else /* __cplusplus */
#define __NULLPTR ((void *)0)
#endif /* !__cplusplus */

/* Emulate the `__OPTIMIZE__' predefined macro, used in various headers. */
#if defined(RELEASE) || defined(_RELEASE)
#ifndef _RELEASE
#define _RELEASE RELEASE
#endif /* !_RELEASE */
#ifndef __OPTIMIZE__
#if (_RELEASE+0) >= 1
#define __OPTIMIZE__ _RELEASE
#else /* (_RELEASE+0) >= 1 */
#define __OPTIMIZE__ 3
#endif /* (_RELEASE+0) < 1 */
#endif /* !__OPTIMIZE__ */
#endif /* RELEASE || _RELEASE */

#ifdef _NATIVE_WCHAR_T_DEFINED
#define __native_wchar_t_defined
#endif /* _NATIVE_WCHAR_T_DEFINED */
#ifdef _WCHAR_T_DEFINED
#define __wchar_t_defined
#endif /* _WCHAR_T_DEFINED */

/* Define varargs macros expected by system headers. */
#ifdef _M_CEE_PURE
typedef System::ArgIterator __builtin_va_list;
#else /* _M_CEE_PURE */
#define __builtin_va_list char *
#endif  /* _M_CEE_PURE */
#ifdef __cplusplus
#define __MSVC_VA_ADDROF(v) &reinterpret_cast<char const &>(v)
#else /* __cplusplus */
#define __MSVC_VA_ADDROF(v) &(v)
#endif /* !__cplusplus */
#if (defined(__i386__) || defined(__i386) || defined(i386) || \
     defined(__I86__) || defined(_M_IX86) || defined(__X86__) || \
     defined(_X86_) || defined(__THW_INTEL__) || defined(__INTEL__))
#define __VA_SIZEOF(n)                   ((sizeof(n) + 3) & ~3)
#define __builtin_va_start(ap, last_arg) (void)((ap) = (__builtin_va_list)__MSVC_VA_ADDROF(last_arg) + __VA_SIZEOF(last_arg))
#define __builtin_va_arg(ap, T)          (*(T *)(((ap) += __VA_SIZEOF(T)) - __VA_SIZEOF(T)))
#define __builtin_va_end(ap)             (void)0
#elif (defined(__x86_64__) || defined(__amd64__) || defined(__amd64) || \
       defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64) || \
       defined(_WIN64) || defined(WIN64))
#ifdef __cplusplus
namespace __intern {
extern "C" {
extern void (__cdecl __va_start)(__builtin_va_list *, ...);
extern __declspec(dllimport) void (__cdecl _vacopy)(__builtin_va_list *, __builtin_va_list);
} /* extern "C" */
} /* namespace __intern */
#define __builtin_va_start(ap, x)       ::__intern::__va_start(&ap, x)
#define __builtin_va_copy(dstap, srcap) ::__intern::_vacopy(&(dstap), srcap)
#else /* __cplusplus */
extern void (__cdecl __va_start)(__builtin_va_list *, ...);
extern __declspec(dllimport) void (__cdecl _vacopy)(__builtin_va_list *, __builtin_va_list);
#define __builtin_va_start(ap, x)       __va_start(&ap, x)
#define __builtin_va_copy(dstap, srcap) _vacopy(&(dstap), srcap)
#endif /* !__cplusplus */
#define __builtin_va_arg(ap, T)                            \
	((sizeof(T) > 8 || (sizeof(T) & (sizeof(T) - 1)) != 0) \
	 ? **(T **)((ap += 8) - 8)                             \
	 : *(T *)((ap += 8) - 8))
#define __builtin_va_end(ap) (void)0
#else /* ... */
#define __VA_SIZEOF(n)            ((sizeof(n) + 3) & ~3)
#define __builtin_va_start(ap, v) (ap = (__builtin_va_list)__MSVC_VA_ADDROF(v) + __VA_SIZEOF(v)))
#define __builtin_va_arg(ap, T)   (*(T *)((ap += __VA_SIZEOF(T)) - __VA_SIZEOF(T)))
#define __builtin_va_end(ap)      (void)0
#endif /* !... */
#ifndef __builtin_va_copy
#define __builtin_va_copy(dstap, srcap) (void)((dstap) = (srcap))
#endif /* !__builtin_va_copy */

#if defined(__INTELLISENSE__) && defined(__cplusplus)
/* Help  detect invalid argument count that can easily be caused by copying the `va_start'
 * source line and  replacing `start'  with `end'  without removing  the second  argument.
 * (The following hack causes the second argument in such use cases to be underlined red). */
#undef __builtin_va_end
void __builtin_va_end(__builtin_va_list &__ap);
#define __builtin_va_end  __builtin_va_end
#endif /* __INTELLISENSE__ && __cplusplus */

#ifdef _PREFAST_ /* Disable BS code analysis warnings that are based on miss-guided opinions */
#pragma warning(disable: 26493 26494 26477 26438 26446 26482 26485 26448 26462 26496 26461 26476 26481 6255 26427)
#pragma warning(disable: 26489 26486 26487 26451 26492 26430 28182) /* There warnings would be helpful... IF THEY WORKED! */
#ifdef __cplusplus
#pragma warning(disable: 26429 26440 26457 26826)
#endif /* __cplusplus */
#endif /* _PREFAST_ */

#pragma warning(disable: 4514) /* Unused inline function was removed. */
#pragma warning(disable: 4574) /* Nonsensical preprocessor warning. */
#pragma warning(disable: 4710) /* Function not inlined (Emit for local varargs functions...) */
#pragma warning(disable: 4711) /* Function inlined despite no `inline' keyword */
#pragma warning(disable: 4201) /* nonstandard extension used: nameless struct/union (they're standard now...) */
#ifdef __cplusplus
#pragma warning(disable: 4644) /* Annoying warning about use of `offsetof' in constant expressions (). */
#define __SYSDECL_BEGIN __DECL_BEGIN
#define __SYSDECL_END   __DECL_END
#else /* __cplusplus */
/* Disable some warnings that are caused by function redirections in system headers. */
#define __REDIRECT_WSUPPRESS_BEGIN                                                        \
	__pragma(warning(push))                                                               \
	__pragma(warning(disable: /* Redirections  */ 4210 4028 4142 4565 4559 4211 4115 4996))
#define __REDIRECT_WSUPPRESS_END __pragma(warning(pop))
/* Suppress warnings caused by C-mode redirections in system headers. */
#define __SYSDECL_BEGIN __DECL_BEGIN __REDIRECT_WSUPPRESS_BEGIN
#define __SYSDECL_END   __REDIRECT_WSUPPRESS_END __DECL_END
#endif /* !__cplusplus */


/* Try to emulate gcc-style warning suppression directives. */
#ifndef __has_GCC_warning
#define __has_GCC_warning(x) __GCC_PRIVATE_W_IS_DEFINED(__GCC_HAS_WARNING_##x)
#define __GCC_PRIVATE_W_ARG_PLACEHOLDER__xS(x) ,
#define __GCC_PRIVATE_W_TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define __GCC_PRIVATE_W_TAKE_SECOND_ARG(x) __GCC_PRIVATE_W_TAKE_SECOND_ARG_IMPL x
#define __GCC_PRIVATE_W_IS_DEFINED3(x) __GCC_PRIVATE_W_TAKE_SECOND_ARG((x 1, 0))
#define __GCC_PRIVATE_W_IS_DEFINED2(x) __GCC_PRIVATE_W_IS_DEFINED3(__GCC_PRIVATE_W_ARG_PLACEHOLDER_##x)
#define __GCC_PRIVATE_W_IS_DEFINED(x) __GCC_PRIVATE_W_IS_DEFINED2(x)

#define __PRIVATE_pragma_GCC_diagnostic_ignored_1__xS(ids)   __pragma(warning(disable: ids))
#define __PRIVATE_pragma_GCC_diagnostic_ignored_1(decl)      __PRIVATE_pragma_GCC_diagnostic_ignored_1_##decl
#define __PRIVATE_pragma_GCC_diagnostic_push_ignored_1(decl) __pragma_GCC_diagnostic_push __PRIVATE_pragma_GCC_diagnostic_ignored_1_##decl
#define __PRIVATE_pragma_GCC_diagnostic_pop_ignored_1(decl)  __pragma_GCC_diagnostic_pop
#define __PRIVATE_pragma_GCC_diagnostic_ignored_0(decl)            /* Nothing */
#define __PRIVATE_pragma_GCC_diagnostic_push_ignored_0(decl)       /* Nothing */
#define __PRIVATE_pragma_GCC_diagnostic_pop_ignored_0(decl)        /* Nothing */
#define __PRIVATE_pragma_GCC_diagnostic_ignored__(cond, decl)      __PRIVATE_pragma_GCC_diagnostic_ignored_##cond(decl)
#define __PRIVATE_pragma_GCC_diagnostic_ignored_(cond, decl)       __PRIVATE_pragma_GCC_diagnostic_ignored__(cond, decl)
#define __PRIVATE_pragma_GCC_diagnostic_push_ignored__(cond, decl) __PRIVATE_pragma_GCC_diagnostic_push_ignored_##cond(decl)
#define __PRIVATE_pragma_GCC_diagnostic_push_ignored_(cond, decl)  __PRIVATE_pragma_GCC_diagnostic_push_ignored__(cond, decl)
#define __PRIVATE_pragma_GCC_diagnostic_pop_ignored__(cond, decl)  __PRIVATE_pragma_GCC_diagnostic_pop_ignored_##cond(decl)
#define __PRIVATE_pragma_GCC_diagnostic_pop_ignored_(cond, decl)   __PRIVATE_pragma_GCC_diagnostic_pop_ignored__(cond, decl)
#define __PRIVATE_pragma_GCC_diagnostic_ignored(cond, decl)        __PRIVATE_pragma_GCC_diagnostic_ignored_(cond, decl)
#define __PRIVATE_pragma_GCC_diagnostic_push_ignored(cond, decl)   __PRIVATE_pragma_GCC_diagnostic_push_ignored_(cond, decl)
#define __PRIVATE_pragma_GCC_diagnostic_pop_ignored(cond, decl)    __PRIVATE_pragma_GCC_diagnostic_pop_ignored_(cond, decl)
#define __pragma_GCC_diagnostic_push               __pragma(warning(push))
#define __pragma_GCC_diagnostic_pop                __pragma(warning(pop))
#define __pragma_GCC_diagnostic_ignored(name)      __PRIVATE_pragma_GCC_diagnostic_ignored(__GCC_PRIVATE_W_IS_DEFINED(__GCC_HAS_WARNING_##name), __GCC_HAS_WARNING_##name)
#define __pragma_GCC_diagnostic_push_ignored(name) __PRIVATE_pragma_GCC_diagnostic_push_ignored(__GCC_PRIVATE_W_IS_DEFINED(__GCC_HAS_WARNING_##name), __GCC_HAS_WARNING_##name)
#define __pragma_GCC_diagnostic_pop_ignored(name)  __PRIVATE_pragma_GCC_diagnostic_pop_ignored(__GCC_PRIVATE_W_IS_DEFINED(__GCC_HAS_WARNING_##name), __GCC_HAS_WARNING_##name)
#define __pragma_MSVC_diagnostic_ignored           __PRIVATE_pragma_GCC_diagnostic_ignored_1__xS
#define __pragma_MSVC_diagnostic_push_ignored      __pragma_GCC_diagnostic_push __PRIVATE_pragma_GCC_diagnostic_ignored_1__xS
#define __pragma_MSVC_diagnostic_pop_ignored(ids)  __pragma_GCC_diagnostic_pop

/* Mapping of msvc warning IDs to gcc warning names */
#define __GCC_HAS_WARNING_Wuninitialized _xS(4700)
#define __GCC_HAS_WARNING_Wunreachable_code _xS(4702)
#define __GCC_HAS_WARNING_Wmaybe_uninitialized _xS(4701 4703)
#define __GCC_HAS_WARNING_Wcast_function_type _xS(4054 4152)
#if _MSC_VER >= 1500
#define __GCC_HAS_WARNING_MSconditional_expression_is_constant _xS(4127)
#endif /* _MSC_VER >= 1500 */
#define __GCC_HAS_WARNING_Wdiv_by_zero _xS(4723 4724)
#define __GCC_HAS_WARNING_Winvalid_offsetof _xS(4597 4749 4842)
#define __GCC_HAS_WARNING_Woverflow _xS(4056 4178 4340 4427 4756 4757)
#define __GCC_HAS_WARNING_Wunused_parameter _xS(4100)
#define __GCC_HAS_WARNING_Wunused_variable _xS(4101 4189)
#define __GCC_HAS_WARNING_Wunused_but_set_variable _xS(4189)
#define __GCC_HAS_WARNING_Wunused_label _xS(4102)
#define __GCC_HAS_WARNING_Wbuiltin_macro_redefined _xS(4117)
#define __GCC_HAS_WARNING_Wreturn_local_addr _xS(4172)
#define __GCC_HAS_WARNING_Wshift_count_negative _xS(4293)
#define __GCC_HAS_WARNING_Wshift_count_overflow _xS(4293 4333)
#define __GCC_HAS_WARNING_Wformat_extra_args _xS(4474)
#define __GCC_HAS_WARNING_Wunused_function _xS(4505)
#define __GCC_HAS_WARNING_Wunused_value _xS(4555)
#define __GCC_HAS_WARNING_Wint_in_bool_context _xS(4800)
#define __GCC_HAS_WARNING_Wswitch_bool _xS(4808)
#define __GCC_HAS_WARNING_Wtrigraphs _xS(4837)
#define __GCC_HAS_WARNING_Wdeprecated _xS(4973 4974)
#endif /* !__has_GCC_warning */
