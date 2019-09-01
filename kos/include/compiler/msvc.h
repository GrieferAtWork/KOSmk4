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
#define __GCC_VERSION(a,b,c) 0

#define __builtin_expect(x,y) (x)
#define __NO_builtin_expect    1
#define __likely      /* Nothing */
#define __unlikely    /* Nothing */
#define __P(x)                 x

#if defined(_MSC_EXTENSIONS) || _MSC_VER >= 1400
#   define __COMPILER_HAVE_LONGLONG 1
#endif
#define __COMPILER_HAVE_LONGDOUBLE 1
#if defined(_MSC_EXTENSIONS)/* || _MSC_VER >= ???? */
#define __COMPILER_HAVE_TRANSPARENT_STRUCT 1
#endif
#define __COMPILER_HAVE_TRANSPARENT_UNION 1
#define __COMPILER_HAVE_PRAGMA_PUSHMACRO 1
#define __COMPILER_HAVE_PRAGMA_DEPRECATED 1
#ifdef __CC__
#define __COMPILER_HAVE_PRAGMA_PACK 1
#endif
#ifndef __has_feature
#define __NO_has_feature 1
#define __has_feature(x) 0
#endif


#if __has_feature(cxx_auto_type) || \
   (defined(__cplusplus) && _MSC_VER >= 1600)
#   define __auto_type              auto
#   define __COMPILER_HAVE_AUTOTYPE 1
#endif

#if __has_feature(cxx_static_assert) || _MSC_VER >= 1600
#   define __STATIC_ASSERT(expr)         static_assert(expr,#expr)
#   define __STATIC_ASSERT_MSG(expr,msg) static_assert(expr,msg)
#elif __has_feature(c_static_assert) || \
     (defined(__STDC_VERSION__) && __STDC_VERSION__+0 >= 201112L)
/* XXX: Known Visual C/C++, checking for C11 may not actually allow us to assume this one... */
#   define __STATIC_ASSERT(expr)         _Static_assert(expr,#expr)
#   define __STATIC_ASSERT_MSG(expr,msg) _Static_assert(expr,msg)
#elif defined(__TPP_COUNTER)
#   define __STATIC_ASSERT(expr)         typedef int __PP_CAT2(__static_assert_,__TPP_COUNTER(__static_assert))[(expr)?1:-1]
#   define __STATIC_ASSERT_MSG(expr,msg) typedef int __PP_CAT2(__static_assert_,__TPP_COUNTER(__static_assert))[(expr)?1:-1]
#elif defined(__COUNTER__)
#   define __STATIC_ASSERT(expr)         typedef int __PP_CAT2(__static_assert_,__COUNTER__)[(expr)?1:-1]
#   define __STATIC_ASSERT_MSG(expr,msg) typedef int __PP_CAT2(__static_assert_,__COUNTER__)[(expr)?1:-1]
#else
#   define __STATIC_ASSERT(expr)         typedef int __PP_CAT2(__static_assert_,__LINE__)[(expr)?1:-1]
#   define __STATIC_ASSERT_MSG(expr,msg) typedef int __PP_CAT2(__static_assert_,__LINE__)[(expr)?1:-1]
#endif
#define __NO_ASMNAME             1
#define __ASMNAME(x)             /* Nothing */
#define __extension__            /* Nothing */
#define __ATTR_NOINLINE          __declspec(noinline)
#define __ATTR_NORETURN          __declspec(noreturn)
#define __NO_ATTR_FALLTHROUGH    1
#define __ATTR_FALLTHROUGH       /* Nothing */
#if !defined(__midl) && (defined(_X86_) || defined(_M_IX86))
#define __ATTR_W64               __w64
#else
#define __NO_ATTR_W64            1
#define __ATTR_W64               /* Nothing */
#endif
#define __ATTR_FASTCALL          __fastcall
#define __ATTR_STDCALL           __stdcall
#define __ATTR_CDECL             __cdecl
#define __ATTR_THISCALL          __thiscall
#ifdef _M_CEE_PURE
#define __ATTR_CLRCALL           __clrcall
#else
#define __NO_ATTR_CLRCALL        1
#define __ATTR_CLRCALL           /* nothing */
#endif
#if defined(__x86_64__) || defined(__amd64__) || defined(__amd64) || \
    defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
#define __ATTR_MSABI             /* Nothing (default) */
#else
#define __ATTR_MSABI             /* Nothing */
#define __NO_ATTR_MSABI          1
#endif
#define __ATTR_SYSVABI           /* Nothing */
#define __NO_ATTR_SYSVABI        1
#define __ATTR_PURE              __declspec(noalias)
#define __ATTR_CONST             __declspec(noalias)
#define __NO_ATTR_LEAF           1
#define __ATTR_LEAF              /* Nothing */
#define __NO_ATTR_FLATTEN        1
#define __ATTR_FLATTEN           /* Nothing */
#define __ATTR_MALLOC            __declspec(restrict)
#define __NO_ATTR_HOT            1
#define __ATTR_HOT               /* Nothing */
#define __NO_ATTR_COLD           1
#define __ATTR_COLD              /* Nothing */
#define __NO_ATTR_ALLOC_SIZE     1
#define __ATTR_ALLOC_SIZE(ppars) /* Nothing */
#define __NO_ATTR_ALLOC_ALIGN    1
#define __ATTR_ALLOC_ALIGN(pari) /* Nothing */
#define __NO_ATTR_ASSUME_ALIGNED 1
#define __ATTR_ASSUME_ALIGNED(n) /* Nothing */
#define __NO_ATTR_NOCLONE        1
#define __ATTR_NOCLONE           /* Nothing */
#define __NO_ATTR_USED           1
#define __ATTR_USED              /* Nothing */
#define __NO_ATTR_UNUSED         1
#define __ATTR_UNUSED            /* Nothing */
#define __NO_ATTR_SENTINEL       1
#define __ATTR_SENTINEL          /* Nothing */
#define __NO_ATTR_SENTINEL_O     1
#define __ATTR_SENTINEL_O(x)     /* Nothing */
#if _MSC_VER >= 1700
#   define __ATTR_THREAD         __declspec(thread)
#else
#   define __NO_ATTR_THREAD      1
#   define __ATTR_THREAD         /* Nothing */
#endif
#if _MSC_VER >= 1200
#   define __ATTR_DEPRECATED_    __declspec(deprecated)
#   define __ATTR_DEPRECATED(text) __declspec(deprecated(text))
#else
#   define __NO_ATTR_DEPRECATED  1
#   define __ATTR_DEPRECATED(text) /* Nothing */
#endif
#define __NO_ATTR_ERROR          1
#define __ATTR_ERROR(text)       /* Nothing */
#define __NO_ATTR_WARNING        1
#define __ATTR_WARNING(text)     /* Nothing */
#define __NO_ATTR_SECTION        1
#define __ATTR_SECTION(name)     /* Nothing */
#ifdef __cplusplus
#define __ATTR_NOTHROW           __declspec(nothrow)
#else
#define __NO_ATTR_NOTHROW        1
#define __ATTR_NOTHROW           /* Nothing */
#endif
#define __NO_ATTR_OPTIMIZE       1
#define __ATTR_OPTIMIZE(opt)     /* Nothing */
#define __NO_ATTR_NOTHROW_SUFFIX 1
#define __NO_ATTR_RETNONNULL     1
#define __ATTR_RETNONNULL        /* Nothing */
#define __NO_ATTR_PACKED         1
#define __ATTR_PACKED            /* Nothing */
#define __NO_ATTR_ALIAS          1
#define __ATTR_ALIAS(name)       /* Nothing */
#if _MSC_VER >= 1300
#   define __ATTR_ALIGNED(n)     __declspec(align(n))
#else
#   define __NO_ATTR_ALIGNED     1
#   define __ATTR_ALIGNED(n)     /* Nothing */
#endif
#define __ATTR_WEAK_IS_SELECTANY 1
#define __ATTR_WEAK              __declspec(selectany) /* For all that we care, it's basically the same. */
#define __ATTR_SELECTANY         __declspec(selectany)
#define __NO_ATTR_RETURNS_TWICE  1
#define __ATTR_RETURNS_TWICE     /* Nothing */
#define __NO_ATTR_EXTERNALLY_VISIBLE 1
#define __ATTR_EXTERNALLY_VISIBLE /* Nothing */
#define __NO_ATTR_VISIBILITY     1
#define __ATTR_VISIBILITY(vis)   /* Nothing */
#define __NO_ATTR_FORMAT_PRINTF  1
#define __ATTR_FORMAT_PRINTF(fmt,args) /* Nothing */
#define __NO_ATTR_FORMAT_SCANF   1
#define __ATTR_FORMAT_SCANF(fmt,args) /* Nothing */
#define __NO_ATTR_FORMAT_STRFMON 1
#define __ATTR_FORMAT_STRFMON(fmt,args) /* Nothing */
#define __NO_ATTR_FORMAT_STRFTIME 1
#define __ATTR_FORMAT_STRFTIME(fmt,args) /* Nothing */
#define __ATTR_DLLIMPORT         __declspec(dllimport)
#define __ATTR_DLLEXPORT         __declspec(dllexport)
#define __NO_ATTR_NONNULL        1
#define __ATTR_NONNULL(ppars)    /* Nothing */
#define __NO_ATTR_WUNUSED        1
#define __ATTR_WUNUSED           /* Nothing */
#define __NO_ATTR_TRANSPARENT_UNION 1
#define __ATTR_TRANSPARENT_UNION /* Nothing */
#define __NO_XBLOCK              1
#define __IF0                    __pragma(warning(suppress: 4127)) if(0)
#define __IF1                    __pragma(warning(suppress: 4127)) if(0)
#define __WHILE0                 __pragma(warning(suppress: 4127)) while(0)
#define __WHILE1                 __pragma(warning(suppress: 4127)) while(0)
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
#define __builtin_choose_expr(c,tt,ff) (__STATIC_IF(c){tt} __STATIC_ELSE(c){ff})
#else
#define __STATIC_IF(x)           __pragma(warning(suppress: 4127)) if(x)
#define __STATIC_ELSE(x)         __pragma(warning(suppress: 4127)) if(x)
#define __NO_builtin_choose_expr 1
#define __builtin_choose_expr(c,tt,ff) ((c)?(tt):(ff))
#endif
#define __NO_builtin_types_compatible_p   1
#define __builtin_types_compatible_p(...) 0
#define __XBLOCK(...)            do __VA_ARGS__ __WHILE0
#define __XRETURN                /* Nothing */
#undef __builtin_assume_has_sideeffects
#define __builtin_assume(x)      __assume(x)
#define __builtin_unreachable()  __assume(0)
#define __COMPILER_ALIGNOF       __alignof
#define __builtin_offsetof(s,m) ((__SIZE_TYPE__)&((s *)0)->m)
#define __ATTR_INLINE            __inline
#define __ATTR_FORCEINLINE       __forceinline
#define __LOCAL                  static __inline
#define __FORCELOCAL             static __forceinline
#define __LONGLONG               long long
#define __ULONGLONG              unsigned long long
#define __NO_builtin_constant_p  1
#define __builtin_constant_p(x) (__LINE__ == -1)
#define __restrict_arr           __restrict
#define __COMPILER_FLEXIBLE_ARRAY(T,x) T x[1024]
#define __attribute__(x)         /* Nothing */
#define __NO_COMPILER_IGNORE_UNINITIALIZED 1
#define __COMPILER_IGNORE_UNINITIALIZED(var) var

#define __INT8_TYPE__            signed __int8
#define __UINT8_TYPE__           unsigned __int8
#define __INT16_TYPE__           signed __int16
#define __UINT16_TYPE__          unsigned __int16
#define __INT32_TYPE__           signed __int32
#define __UINT32_TYPE__          unsigned __int32
#define __INT64_TYPE__           signed __int64
#define __UINT64_TYPE__          unsigned __int64

#ifndef __USER_LABEL_PREFIX__
#define __USER_LABEL_PREFIX__           _ /* XXX: This is always the case? */
#endif
#define __DEFINE_ALIAS_STR(x)           #x

#define __DEFINE_PRIVATE_ALIAS(new,old) \
  __pragma(comment(linker,"/alternatename:" __DEFINE_ALIAS_STR(new) "=" __DEFINE_ALIAS_STR(old)))
#define __DEFINE_PUBLIC_ALIAS(new,old)  \
  __pragma(comment(linker,"/alternatename:" __DEFINE_ALIAS_STR(new) "=" __DEFINE_ALIAS_STR(old))) \
  __pragma(comment(linker,"/export:" __DEFINE_ALIAS_STR(new)))
#define __DEFINE_INTERN_ALIAS(new,old)  \
  __pragma(comment(linker,"/alternatename:" __DEFINE_ALIAS_STR(new) "=" __DEFINE_ALIAS_STR(old)))

/* TODO: selectany? */
#define __DEFINE_PRIVATE_WEAK_ALIAS(new,old) __DEFINE_PRIVATE_ALIAS(new,old)
#define __DEFINE_PUBLIC_WEAK_ALIAS(new,old)  __DEFINE_PUBLIC_ALIAS(new,old)
#define __DEFINE_INTERN_WEAK_ALIAS(new,old)  __DEFINE_INTERN_ALIAS(new,old)


#if !defined(__INTELLISENSE__)
/* This works, but may be very expensive because I've got a feeling
 * that all of these ~comments~ must be passed via the commandline... */
#define __REDIRECT_PP_STR2(x) #x
#define __REDIRECT_PP_STR(x) __REDIRECT_PP_STR2(x)
#define __REDIRECT_ASSEMBLY(x,y) \
  __pragma(comment(linker,"/alternatename:" __REDIRECT_PP_STR(__USER_LABEL_PREFIX__) #x "=" __REDIRECT_PP_STR(__USER_LABEL_PREFIX__) #y)) \
  __pragma(comment(linker,"/alternatename:__imp_" __REDIRECT_PP_STR(__USER_LABEL_PREFIX__) #x "=__imp_" __REDIRECT_PP_STR(__USER_LABEL_PREFIX__) #y)) \
  __pragma(comment(linker,"/alternatename:__imp__" __REDIRECT_PP_STR(__USER_LABEL_PREFIX__) #x "=__imp__" __REDIRECT_PP_STR(__USER_LABEL_PREFIX__) #y))
#define __REDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args)                                       decl attr Treturn nothrow(cc name) param; __REDIRECT_ASSEMBLY(name,asmname)
#define __REDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args)                                          decl attr void nothrow(cc name) param; __REDIRECT_ASSEMBLY(name,asmname)
#define __VREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)    decl attr Treturn nothrow(cc name) param; __REDIRECT_ASSEMBLY(name,asmname)
#define __VREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)       decl attr void nothrow(cc name) param; __REDIRECT_ASSEMBLY(name,asmname)
#define __VFREDIRECT(decl,attr,Treturn,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) decl attr Treturn nothrow(cc name) paramf; __REDIRECT_ASSEMBLY(name,asmnamef)
#define __VFREDIRECT_VOID(decl,attr,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    decl attr void nothrow(cc name) paramf; __REDIRECT_ASSEMBLY(name,asmnamef)
#define __XREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code)                                      decl attr Treturn nothrow(cc name) param; __REDIRECT_ASSEMBLY(name,asmname)
#define __XREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code)                                         decl attr void nothrow(cc name) param; __REDIRECT_ASSEMBLY(name,asmname)
#endif


/* Define intrinsic barrier functions. */
#ifdef __cplusplus
namespace __intern { extern "C" {
#endif /* __cplusplus */
#if defined(__i386__) || defined(__i386) || defined(i386) || \
    defined(__I86__) || defined(_M_IX86) || defined(__X86__) || \
    defined(_X86_) || defined(__THW_INTEL__) || defined(__INTEL__) || \
    defined(__x86_64__) || defined(__amd64__) || defined(__amd64) || \
    defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64) || \
    defined(_WIN64) || defined(WIN64)
extern void (__cdecl _m_prefetch)(void *);
#pragma intrinsic(_m_prefetch)
#ifdef __cplusplus
#define __builtin_prefetch(addr,...) ::__intern::_m_prefetch(addr)
#else /* __cplusplus */
#define __builtin_prefetch(addr,...) _m_prefetch(addr)
#endif /* !__cplusplus */
#else
#define __NO_builtin_prefetch    1
#define __builtin_prefetch(...) (void)0
#endif
extern void (__cdecl _ReadBarrier)(void);
extern void (__cdecl _WriteBarrier)(void);
extern void (__cdecl _ReadWriteBarrier)(void);
#pragma intrinsic(_ReadBarrier)
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)
#ifdef __cplusplus
#define __COMPILER_BARRIER()       ::__intern::_ReadWriteBarrier()
#define __COMPILER_READ_BARRIER()  ::__intern::_ReadBarrier()
#define __COMPILER_WRITE_BARRIER() ::__intern::_WriteBarrier()
#else /* __cplusplus */
#define __COMPILER_BARRIER()       _ReadWriteBarrier()
#define __COMPILER_READ_BARRIER()  _ReadBarrier()
#define __COMPILER_WRITE_BARRIER() _WriteBarrier()
#endif /* !__cplusplus */
#ifdef __cplusplus
} }
#endif /* __cplusplus */

#ifdef __cplusplus
#ifdef __INTELLISENSE__
#   define __NULLPTR    nullptr
#else
#   define __NULLPTR          0
#endif
#else
#   define __NULLPTR ((void *)0)
#endif

/* Emulate the `__OPTIMIZE__' predefined macro, used in various headers. */
#if defined(RELEASE) || defined(_RELEASE)
#ifndef _RELEASE
#   define _RELEASE  RELEASE
#endif
#if (_RELEASE+0) >= 1
#   define __OPTIMIZE__ _RELEASE
#else
#   define __OPTIMIZE__ 3
#endif
#endif

#ifdef _NATIVE_WCHAR_T_DEFINED
#define __native_wchar_t_defined 1
#endif
#ifdef _WCHAR_T_DEFINED
#define __wchar_t_defined 1
#endif


/* Define varargs macros expected by system headers. */
#ifdef _M_CEE_PURE
typedef System::ArgIterator __builtin_va_list;
#else /* _M_CEE_PURE */
#define __builtin_va_list  char *
#endif  /* _M_CEE_PURE */
#ifdef __cplusplus
#define __MSVC_VA_ADDROF(v)   &reinterpret_cast<char const &>(v)
#else
#define __MSVC_VA_ADDROF(v)   &(v)
#endif
#if defined(__i386__) || defined(__i386) || defined(i386) || \
    defined(__I86__) || defined(_M_IX86) || defined(__X86__) || \
    defined(_X86_) || defined(__THW_INTEL__) || defined(__INTEL__)
#define __VA_SIZEOF(n)                 ((sizeof(n)+3)&~3)
#define __builtin_va_start(ap,last_arg) (void)((ap) = (__builtin_va_list)__MSVC_VA_ADDROF(last_arg)+__VA_SIZEOF(last_arg)
#define __builtin_va_arg(ap,T)          (*(T *)(((ap) += __VA_SIZEOF(T)-__VA_SIZEOF(T)
#define __builtin_va_end(ap)            (void)0
#elif defined(__x86_64__) || defined(__amd64__) || defined(__amd64) || \
      defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64) || \
      defined(_WIN64) || defined(WIN64)
#ifdef __cplusplus
namespace __intern { extern "C" {
extern void (__cdecl __va_start)(__builtin_va_list *, ...);
extern __declspec(dllimport) void (__cdecl _vacopy)(__builtin_va_list *, __builtin_va_list);
} }
#define __builtin_va_start(ap,x) ::__intern::__va_start(&ap,x)
#define __builtin_va_copy(dstap,srcap) ::__intern::_vacopy(&(dstap),srcap)
#else
extern void (__cdecl __va_start)(__builtin_va_list *, ...);
extern __declspec(dllimport) void (__cdecl _vacopy)(__builtin_va_list *, __builtin_va_list);
#define __builtin_va_start(ap,x) __va_start(&ap,x)
#define __builtin_va_copy(dstap,srcap) _vacopy(&(dstap),srcap)
#endif
#define __builtin_va_arg(ap,T) \
    ((sizeof(T) > 8 || (sizeof(T)&(sizeof(T) - 1)) != 0) ? **(T **)((ap += 8)-8) : *(T *)((ap += 8)-8))
#define __builtin_va_end(ap)    (void)0
#else /* ... */
#define __VA_SIZEOF(n)            ((sizeof(n)+3)&~3)
#define __builtin_va_start(ap,v)  (ap = (__builtin_va_list)__MSVC_VA_ADDROF(v)+__VA_SIZEOF(v))
#define __builtin_va_arg(ap,T)    (*(T *)((ap += __VA_SIZEOF(T))-__VA_SIZEOF(T)))
#define __builtin_va_end(ap)      (void)0
#endif /* !... */
#ifndef __builtin_va_copy
#define __builtin_va_copy(dstap,srcap)  (void)((dstap) = (srcap))
#endif /* !__builtin_va_copy */

#if defined(__INTELLISENSE__) && defined(__cplusplus)
/* Help detect invalid argument count that can easily be caused by copying the `va_start'
 * source line and replacing `start' with `end' without removing the section argument.
 * (The following hack causes the second argument red in such use cases to be underlined red). */
#undef __builtin_va_end
void __builtin_va_end(__builtin_va_list &__ap);
#define __builtin_va_end  __builtin_va_end
#endif

#pragma warning(disable: 4514) /* Unused inline function was removed. */
#pragma warning(disable: 4574) /* Nonsensical preprocessor warning. */
#pragma warning(disable: 4710) /* Function not inlined (Emit for local varargs functions...) */
#ifndef __cplusplus
/* Disable some warnings that are caused by function redirections in system headers. */
#define __REDIRECT_WSUPPRESS_BEGIN \
 __pragma(warning(push)) \
 __pragma(warning(disable: /* Redirections  */4210 4028 4142 4565 4559 4211 4115 4996 \
                           /* Unnamed union */4201))

#define __REDIRECT_WSUPPRESS_END   __pragma(warning(pop))
/* Suppress warnings caused by C-mode redirections in system headers. */
#define __SYSDECL_BEGIN __DECL_BEGIN __REDIRECT_WSUPPRESS_BEGIN
#define __SYSDECL_END   __REDIRECT_WSUPPRESS_END __DECL_END
#else
/* Disable some warnings that are caused by function redirections in system headers. */
/* Suppress warnings caused by C-mode redirections in system headers. */
#define __SYSDECL_BEGIN __DECL_BEGIN __pragma(warning(push)) __pragma(warning(disable: /* Unnamed union */4201))
#define __SYSDECL_END   __pragma(warning(pop)) __DECL_END
#endif
