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
#ifndef __PP_STR
#include "pp-generic.h"
#endif /* !__PP_STR */

#ifdef __ASSEMBLY__
#if __ASSEMBLY__+0 == 0
#undef __ASSEMBLY__
#define __ASSEMBLY__ 1
#endif /* __ASSEMBLY__+0 == 0 */
#elif defined(__ASSEMBLER__)
#if __ASSEMBLER__+0 == 0
#define __ASSEMBLY__ 1
#else /* __ASSEMBLER__+0 == 0 */
#define __ASSEMBLY__   __ASSEMBLER__
#endif /* __ASSEMBLER__+0 != 0 */
#elif defined(__assembler)
#if __assembler+0 == 0
#define __ASSEMBLY__ 1
#else /* __assembler+0 == 0 */
#define __ASSEMBLY__ __assembler
#endif /* __assembler+0 != 0 */
#endif

/* Both  `__ASSEMBLER__'  and `__ASSEMBLY__'
 * are our general-purpose detection macros. */
#ifdef __ASSEMBLY__
#ifndef __ASSEMBLER__
#define __ASSEMBLER__ __ASSEMBLY__
#endif /* !__ASSEMBLER__ */
#endif /* __ASSEMBLY__ */

#if defined(__ASSEMBLER__) && defined(__LINKER__)
#error "Detected both assembler and linker?"
#endif /* __ASSEMBLER__ && __LINKER__ */


#ifndef __has_feature
#define __NO_has_feature
#define __has_feature(x) 0
#endif /* !__has_feature */

#ifndef __has_extension
#ifndef __NO_has_feature
#define __NO_has_extension
#endif /* !__NO_has_feature */
#define __has_extension  __has_feature
#endif /* !__has_extension */

#ifndef __has_include
#define __NO_has_include
#define __has_include(x) 0
#endif /* !__has_include */

#ifndef __has_include_next
#define __NO_has_include_next
#define __has_include_next(x) 0
#endif /* !__has_include */

#ifndef __TPP_VERSION__
#undef __has_attribute
#define __NO_has_attribute
#define __has_attribute(x) 0

#undef __has_declspec_attribute
#define __NO_has_declspec_attribute
#define __has_declspec_attribute(x) 0

#undef __has_cpp_attribute
#define __NO_has_cpp_attribute
#define __has_cpp_attribute(x) 0

#undef __has_builtin
#define __NO_has_builtin
#define __has_builtin(x) 0
#else /* !__TPP_VERSION__ */
#define __NO_has_attribute
#define __NO_has_declspec_attribute
#define __NO_has_cpp_attribute
#define __NO_has_builtin
#endif /* __TPP_VERSION__ */


#ifdef __INTELLISENSE__
#define __DEFINE_PRIVATE_ALIAS(new, old)      /* Nothing */
#define __DEFINE_PRIVATE_WEAK_ALIAS(new, old) /* Nothing */
#define __DEFINE_INTERN_WEAK_ALIAS(new, old)  /* Nothing */
#define __DEFINE_PUBLIC_WEAK_ALIAS(new, old)  /* Nothing */
#define __DEFINE_PUBLIC_ALIAS(new, old)       /* Nothing */
#define __DEFINE_INTERN_ALIAS(new, old)       /* Nothing */
#elif defined(__ASSEMBLER__)
#define __DEFINE_PRIVATE_ALIAS(new, old)      .local new; .set new, old;
#define __DEFINE_PUBLIC_ALIAS(new, old)       .global new; .set new, old;
#define __DEFINE_INTERN_ALIAS(new, old)       .global new; .hidden new; .set new, old;
#define __DEFINE_PRIVATE_WEAK_ALIAS(new, old) .weak new; .local new; .set new, old;
#define __DEFINE_PUBLIC_WEAK_ALIAS(new, old)  .weak new; .global new; .set new, old;
#define __DEFINE_INTERN_WEAK_ALIAS(new, old)  .weak new; .global new; .hidden new; .set new, old;
#elif defined(__LINKER__)
#define __DEFINE_PRIVATE_ALIAS(new, old)      __DEFINE_INTERN_ALIAS(new, old)
#define __DEFINE_PRIVATE_WEAK_ALIAS(new, old) __DEFINE_INTERN_ALIAS(new, old)
#define __DEFINE_INTERN_WEAK_ALIAS(new, old)  __DEFINE_INTERN_ALIAS(new, old)
#define __DEFINE_PUBLIC_WEAK_ALIAS(new, old)  __DEFINE_PUBLIC_ALIAS(new, old)
#define __DEFINE_PUBLIC_ALIAS(new, old)       PROVIDE(new = ABSOLUTE(old))
#define __DEFINE_INTERN_ALIAS(new, old)       PROVIDE_HIDDEN(new = ABSOLUTE(old))
#else /* ... */
#define __DEFINE_PRIVATE_ALIAS(new, old)      /* Nothing */
#define __DEFINE_PRIVATE_WEAK_ALIAS(new, old) /* Nothing */
#define __DEFINE_INTERN_WEAK_ALIAS(new, old)  /* Nothing */
#define __DEFINE_PUBLIC_WEAK_ALIAS(new, old)  /* Nothing */
#define __DEFINE_PUBLIC_ALIAS(new, old)       /* Nothing */
#define __DEFINE_INTERN_ALIAS(new, old)       /* Nothing */
#endif /* !... */


#define __builtin_expect(x, y) (x)
#define __NO_builtin_expect
#define __likely   /* Nothing */
#define __unlikely /* Nothing */
#define __P(x)     /* Nothing */
#ifdef __LINKER__
#define __STATIC_ASSERT(expr)          ASSERT(expr, #expr)
#define __STATIC_ASSERT_MSG(expr, msg) ASSERT(expr, msg)
#else /* __LINKER__ */
#define __STATIC_ASSERT(expr)          /* Nothing */
#define __STATIC_ASSERT_MSG(expr, msg) /* Nothing */
#endif /* !__LINKER__ */

#define __extension__    /* Nothing */
#define __attribute__(x) /* Nothing */

#define __NO_ASMNAME
#define __COMPILER_ASMNAME(x) /* Nothing */

#define __NO_ATTR_NOINLINE
#define __ATTR_NOINLINE /* Nothing */
#define __NO_ATTR_NORETURN
#define __ATTR_NORETURN /* Nothing */
#define __NO_ATTR_W64
#define __ATTR_W64 /* Nothing */
#define __NO_ATTR_FALLTHROUGH
#define __ATTR_FALLTHROUGH /* Nothing */
#define __NO_ATTR_FASTCALL
#define __ATTR_FASTCALL /* Nothing */
#define __NO_ATTR_STDCALL
#define __ATTR_STDCALL /* Nothing */
#define __NO_ATTR_CDECL
#define __ATTR_CDECL /* Nothing */
#define __NO_ATTR_MSABI
#define __ATTR_MSABI /* Nothing */
#define __NO_ATTR_SYSVABI
#define __ATTR_SYSVABI /* Nothing */
#define __NO_ATTR_PURE
#define __ATTR_PURE /* Nothing */
#define __NO_ATTR_CONST
#define __ATTR_CONST /* Nothing */
#define __NO_ATTR_LEAF
#define __ATTR_LEAF /* Nothing */
#define __NO_ATTR_FLATTEN
#define __ATTR_FLATTEN /* Nothing */
#define __NO_ATTR_MALLOC
#define __ATTR_MALLOC /* Nothing */
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
#define __NO_ATTR_THREAD
#define __ATTR_THREAD /* Nothing */
#define __NO_ATTR_DEPRECATED
#define __ATTR_DEPRECATED(text) /* Nothing */
#define __NO_ATTR_ERROR
#define __ATTR_ERROR(text) /* Nothing */
#define __NO_ATTR_WARNING
#define __ATTR_WARNING(text) /* Nothing */
#define __NO_ATTR_SECTION
#define __ATTR_SECTION(name) /* Nothing */
#define __NO_ATTR_NOTHROW
#define __ATTR_NOTHROW /* Nothing */
#define __NO_ATTR_OPTIMIZE
#define __ATTR_OPTIMIZE(opt) /* Nothing */
#define __NO_ATTR_RETNONNULL
#define __ATTR_RETNONNULL /* Nothing */
#define __NO_ATTR_PACKED
#define __ATTR_PACKED /* Nothing */
#define __NO_ATTR_ALIAS
#define __ATTR_ALIAS(name) /* Nothing */
#define __NO_ATTR_ALIGNED
#define __ATTR_ALIGNED(n) /* Nothing */
#define __NO_ATTR_WEAK
#define __ATTR_WEAK /* Nothing */
#define __NO_ATTR_SELECTANY
#define __ATTR_SELECTANY /* Nothing */
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
#define __NO_ATTR_DLLIMPORT
#define __ATTR_DLLIMPORT /* Nothing */
#define __NO_ATTR_DLLEXPORT
#define __ATTR_DLLEXPORT /* Nothing */
#define __NO_ATTR_NOPLT
#define __ATTR_NOPLT /* Nothing */
#define __NO_ATTR_NONNULL
#define __ATTR_NONNULL(ppars)     /* Nothing */
#define __ATTR_NONNULL_CXX(ppars) /* Nothing */
#define __NO_ATTR_WUNUSED
#define __ATTR_WUNUSED /* Nothing */
#define __NO_ATTR_TRANSPARENT_UNION
#define __ATTR_TRANSPARENT_UNION /* Nothing */
#define __NO_ATTR_INLINE
#define __ATTR_INLINE /* Nothing */
#define __NO_ATTR_FORCEINLINE
#define __ATTR_FORCEINLINE /* Nothing */
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

#define __NO_XBLOCK
#define __builtin_choose_expr(c, tt, ff) ((c) ? (tt) : (ff))
#define __NO_builtin_choose_expr
#define __NO_builtin_types_compatible_p
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __builtin_types_compatible_p(...)
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __builtin_types_compatible_p(T1,T2)
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#undef __builtin_assume_has_sideeffects
#define __builtin_assume(x)     /* Nothing */
#define __builtin_unreachable() /* Nothing */
#define __LOCAL                 /* Nothing */
#define __FORCELOCAL            /* Nothing */
#define __NO_EXTERN_INLINE
#define __EXTERN_INLINE      /* Nothing */
#define __EXTERN_FORCEINLINE /* Nothing */
#define __NO_builtin_constant_p
#define __builtin_LINE() __LINE__
#define __builtin_FILE() __FILE__
#define __NO_builtin_FUNCTION
#define __builtin_FUNCTION() ""
#define __FUNCTION__ ""

#define __DECL_BEGIN                        /* Nothing */
#define __DECL_END                          /* Nothing */
#define __CXX11_CONSTEXPR                   /* Nothing */
#define __CXX11_CONSTEXPR_OR_CONST          /* Nothing */
#define __CXX14_CONSTEXPR                   /* Nothing */
#define __CXX14_CONSTEXPR_OR_CONST          /* Nothing */
#define __CXX_NOEXCEPT                      /* Nothing */
#define __NAMESPACE_STD_BEGIN               /* Nothing */
#define __NAMESPACE_STD_END                 /* Nothing */
#define __NAMESPACE_STD_SYM                 /* Nothing */
#define __NAMESPACE_STD_USING(x)            /* Nothing */
#define __NAMESPACE_GLB_SYM                 /* Nothing */
#define __NAMESPACE_GLB_USING(x)            /* Nothing */
#define __NAMESPACE_GLB_USING_TYPE(x)       /* Nothing */
#define __NAMESPACE_GLB_USING_OR_IMPL(x, i) /* Nothing */
#define __NAMESPACE_INT_BEGIN               /* Nothing */
#define __NAMESPACE_INT_END                 /* Nothing */
#define __NAMESPACE_INT_SYM                 /* Nothing */
#define __NAMESPACE_INT_LSYM                /* Nothing */
#define __DFL(expr)                         /* Nothing */
#define __register                          /* Nothing */
#define __BOOL                              /* Nothing */
#define __COMPILER_REQTYPE(T, v)            (v)


#ifdef __LINKER__
#define __builtin_constant_p(x) 1 /* Anything the linker can work with is constant. */
#else /* __LINKER__ */
#define __builtin_constant_p(x) 0
#endif /* !__LINKER__ */

#define __restrict     /* Nothing */
#define __restrict_arr /* Nothing */
#define __COMPILER_FLEXIBLE_ARRAY(T, x) /* Nothing */

#define __NO_COMPILER_IGNORE_UNINITIALIZED
#define __COMPILER_IGNORE_UNINITIALIZED(var) var

#define __COMPILER_BARRIER()       /* Nothing */
#define __COMPILER_READ_BARRIER()  /* Nothing */
#define __COMPILER_WRITE_BARRIER() /* Nothing */
#define __COMPILER_IMPURE()        /* Nothing */

#define __NULLPTR 0


#ifdef __LINKER__
/* Help figure out the origin of illegal preprocessor content in linker scripts. */
#define struct    <<__FILE__:__LINE__:ERROR: Invalid keyword: 'struct'>>
#define union     <<__FILE__:__LINE__:ERROR: Invalid keyword: 'union'>>
#define typedef   <<__FILE__:__LINE__:ERROR: Invalid keyword: 'typedef'>>
#define enum      <<__FILE__:__LINE__:ERROR: Invalid keyword: 'enum'>>
#ifdef __INTELLISENSE__
#define ENTRY(...)
#define PROVIDE(...)
#define PROVIDE_HIDDEN(...)
#define SECTIONS int foo()
#define ABSOLUTE(...) __VA_ARGS__
#define KEEP(...)
#define BLOCK(...) __VA_ARGS__
#define AT(...)
#define ADDR(...)
#define ALIGN(...) __VA_ARGS__
#endif /* __INTELLISENSE__ */
#endif /* __LINKER__ */
