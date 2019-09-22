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

#ifdef __ASSEMBLY__
#if __ASSEMBLY__+0 == 0
#undef __ASSEMBLY__
#define __ASSEMBLY__  1
#endif /* __ASSEMBLY__+0 == 0 */
#elif defined(__ASSEMBLER__)
#if __ASSEMBLER__+0 == 0
#define __ASSEMBLY__   1
#else /* __ASSEMBLER__+0 == 0 */
#define __ASSEMBLY__   __ASSEMBLER__
#endif /* __ASSEMBLER__+0 != 0 */
#elif defined(__assembler)
#if __assembler+0 == 0
#define __ASSEMBLY__   1
#else /* __assembler+0 == 0 */
#define __ASSEMBLY__   __assembler
#endif /* __assembler+0 != 0 */
#endif

/* Both `__ASSEMBLER__' and `__ASSEMBLY__'
 * are our general-purpose detection macros. */
#ifdef __ASSEMBLY__
#ifndef __ASSEMBLER__
#define __ASSEMBLER__  __ASSEMBLY__
#endif /* !__ASSEMBLER__ */
#endif /* __ASSEMBLY__ */

#if defined(__ASSEMBLER__) && defined(__LINKER__)
#error "Detected both assembler and linker?"
#endif /* __ASSEMBLER__ && __LINKER__ */


#ifdef __ASSEMBLER__
#define __DEFINE_PRIVATE_ALIAS(new,old)      .local new; .set new, old;
#define __DEFINE_PUBLIC_ALIAS(new,old)       .global new; .set new, old;
#define __DEFINE_INTERN_ALIAS(new,old)       .global new; .hidden new; .set new, old;
#define __DEFINE_PRIVATE_WEAK_ALIAS(new,old) .weak new; .local new; .set new, old;
#define __DEFINE_PUBLIC_WEAK_ALIAS(new,old)  .weak new; .global new; .set new, old;
#define __DEFINE_INTERN_WEAK_ALIAS(new,old)  .weak new; .global new; .hidden new; .set new, old;
#elif defined(__LINKER__)
#define __DEFINE_PRIVATE_ALIAS(new,old)      __DEFINE_INTERN_ALIAS(new,old)
#define __DEFINE_PRIVATE_WEAK_ALIAS(new,old) __DEFINE_INTERN_ALIAS(new,old)
#define __DEFINE_INTERN_WEAK_ALIAS(new,old)  __DEFINE_INTERN_ALIAS(new,old)
#define __DEFINE_PUBLIC_WEAK_ALIAS(new,old)  __DEFINE_PUBLIC_ALIAS(new,old)
#define __DEFINE_PUBLIC_ALIAS(new,old)       PROVIDE(new = ABSOLUTE(old))
#define __DEFINE_INTERN_ALIAS(new,old)       PROVIDE_HIDDEN(new = ABSOLUTE(old))
#else
#define __DEFINE_PRIVATE_ALIAS(new,old)      /* nothing */
#define __DEFINE_PRIVATE_WEAK_ALIAS(new,old) /* nothing */
#define __DEFINE_INTERN_WEAK_ALIAS(new,old)  /* nothing */
#define __DEFINE_PUBLIC_WEAK_ALIAS(new,old)  /* nothing */
#define __DEFINE_PUBLIC_ALIAS(new,old)       /* nothing */
#define __DEFINE_INTERN_ALIAS(new,old)       /* nothing */
#endif


#ifndef __GCC_VERSION
#define __GCC_VERSION(a, b, c) 0
#endif /* !__GCC_VERSION */
#define __builtin_expect(x, y) (x)
#define __NO_builtin_expect    1
#define __likely               /* Nothing */
#define __unlikely             /* Nothing */
#define __P(x)                 /* Nothing */
#ifdef __LINKER__
#define __STATIC_ASSERT(expr)          ASSERT(expr, #expr)
#define __STATIC_ASSERT_MSG(expr, msg) ASSERT(expr, msg)
#else /* __LINKER__ */
#define __STATIC_ASSERT(expr)          /* Nothing */
#define __STATIC_ASSERT_MSG(expr, msg) /* Nothing */
#endif /* !__LINKER__ */

#define __extension__            /* Nothing */
#define __restrict               /* nothing */
#define __attribute__(x)         /* Nothing */

#define __ASMNAME(x)             /* Nothing */
#define __NO_ASMNAME             1
#define __ATTR_NOINLINE          /* Nothing */
#define __NO_ATTR_NOINLINE       1
#define __ATTR_NORETURN          /* Nothing */
#define __NO_ATTR_NORETURN       1
#define __ATTR_W64               /* Nothing */
#define __NO_ATTR_W64            1
#define __ATTR_FALLTHROUGH       /* Nothing */
#define __NO_ATTR_FALLTHROUGH    1
#define __ATTR_FASTCALL          /* Nothing */
#define __NO_ATTR_FASTCALL       1
#define __ATTR_STDCALL           /* Nothing */
#define __NO_ATTR_STDCALL        1
#define __ATTR_CDECL             /* Nothing */
#define __NO_ATTR_CDECL          1
#define __ATTR_MSABI             /* Nothing */
#define __NO_ATTR_MSABI          1
#define __ATTR_SYSVABI           /* Nothing */
#define __NO_ATTR_SYSVABI        1
#define __ATTR_PURE              /* Nothing */
#define __NO_ATTR_PURE           1
#define __ATTR_CONST             /* Nothing */
#define __NO_ATTR_CONST          1
#define __ATTR_LEAF              /* Nothing */
#define __NO_ATTR_LEAF           1
#define __ATTR_FLATTEN           /* Nothing */
#define __NO_ATTR_FLATTEN        1
#define __ATTR_MALLOC            /* Nothing */
#define __NO_ATTR_MALLOC         1
#define __ATTR_HOT               /* Nothing */
#define __NO_ATTR_HOT            1
#define __ATTR_COLD              /* Nothing */
#define __NO_ATTR_COLD           1
#define __ATTR_ALLOC_SIZE(ppars) /* Nothing */
#define __NO_ATTR_ALLOC_SIZE     1
#define __ATTR_ALLOC_ALIGN(pari) /* Nothing */
#define __NO_ATTR_ALLOC_ALIGN    1
#define __ATTR_ASSUME_ALIGNED(n) /* Nothing */
#define __NO_ATTR_ASSUME_ALIGNED 1
#define __ATTR_NOCLONE           /* Nothing */
#define __NO_ATTR_NOCLONE        1
#define __ATTR_USED              /* Nothing */
#define __NO_ATTR_USED           1
#define __ATTR_UNUSED            /* Nothing */
#define __NO_ATTR_UNUSED         1
#define __ATTR_SENTINEL          /* Nothing */
#define __NO_ATTR_SENTINEL       1
#define __ATTR_SENTINEL_O(x)     /* Nothing */
#define __NO_ATTR_SENTINEL_O     1
#define __ATTR_THREAD            /* Nothing */
#define __NO_ATTR_THREAD         1
#define __ATTR_DEPRECATED(text)  /* Nothing */
#define __NO_ATTR_DEPRECATED     1
#define __ATTR_ERROR(text)       /* Nothing */
#define __NO_ATTR_WARNING        1
#define __ATTR_ERROR(text)       /* Nothing */
#define __NO_ATTR_WARNING        1
#define __ATTR_SECTION(name)     /* Nothing */
#define __NO_ATTR_SECTION        1
#define __ATTR_NOTHROW           /* Nothing */
#define __NO_ATTR_NOTHROW        1
#define __ATTR_OPTIMIZE(opt)     /* Nothing */
#define __NO_ATTR_OPTIMIZE       1
#define __ATTR_RETNONNULL        /* Nothing */
#define __NO_ATTR_RETNONNULL     1
#define __ATTR_PACKED            /* Nothing */
#define __NO_ATTR_PACKED         1
#define __ATTR_ALIAS(name)       /* Nothing */
#define __NO_ATTR_ALIAS          1
#define __ATTR_ALIGNED(n)        /* Nothing */
#define __NO_ATTR_ALIGNED        1
#define __ATTR_WEAK              /* Nothing */
#define __NO_ATTR_WEAK           1
#define __ATTR_SELECTANY         /* Nothing */
#define __NO_ATTR_SELECTANY      1
#define __ATTR_RETURNS_TWICE     /* Nothing */
#define __NO_ATTR_RETURNS_TWICE  1
#define __ATTR_EXTERNALLY_VISIBLE /* Nothing */
#define __NO_ATTR_EXTERNALLY_VISIBLE 1
#define __ATTR_VISIBILITY(vis)   /* Nothing */
#define __NO_ATTR_VISIBILITY     1
#define __ATTR_FORMAT_PRINTF(fmt,args) /* Nothing */
#define __NO_ATTR_FORMAT_PRINTF  1
#define __ATTR_FORMAT_SCANF(fmt,args) /* Nothing */
#define __NO_ATTR_FORMAT_SCANF   1
#define __ATTR_FORMAT_STRFMON(fmt,args) /* Nothing */
#define __NO_ATTR_FORMAT_STRFMON 1
#define __ATTR_FORMAT_STRFTIME(fmt,args) /* Nothing */
#define __NO_ATTR_FORMAT_STRFTIME 1
#define __ATTR_DLLIMPORT         /* nothing */
#define __NO_ATTR_DLLIMPORT      1
#define __ATTR_DLLEXPORT         /* nothing */
#define __NO_ATTR_DLLEXPORT      1
#define __ATTR_NONNULL(ppars)         /* Nothing */
#define __NO_ATTR_NONNULL             1
#define __ATTR_WUNUSED                /* Nothing */
#define __NO_ATTR_WUNUSED             1
#define __ATTR_TRANSPARENT_UNION /* nothing */
#define __NO_ATTR_TRANSPARENT_UNION 1
#define __ATTR_INLINE            /* nothing */
#define __NO_ATTR_INLINE         1
#define __ATTR_FORCEINLINE       /* nothing */
#define __NO_ATTR_FORCEINLINE    1

#define __NO_XBLOCK              1
#define __builtin_choose_expr(c,tt,ff) ((c)?(tt):(ff))
#define __NO_builtin_choose_expr 1
#define __NO_builtin_types_compatible_p   1
#define __builtin_types_compatible_p(...) 0
#undef __builtin_assume_has_sideeffects
#define __builtin_assume(x)      /* nothing */
#define __builtin_unreachable()  /* nothing */
#define __LOCAL                  /* nothing */
#define __FORCELOCAL             /* nothing */
#define __NO_builtin_constant_p  1
#ifdef __LINKER__
#define __builtin_constant_p(x)  1 /* Anything the linker can work with is constant. */
#else /* __LINKER__ */
#define __builtin_constant_p(x)  0
#endif /* !__LINKER__ */
#define __restrict_arr           /* nothing */
#define __COMPILER_FLEXIBLE_ARRAY(T,x) /* nothing */

#define __NO_COMPILER_IGNORE_UNINITIALIZED 1
#define __COMPILER_IGNORE_UNINITIALIZED(var) var

#define __COMPILER_BARRIER()       /* nothing */
#define __COMPILER_READ_BARRIER()  /* nothing */
#define __COMPILER_WRITE_BARRIER() /* nothing */

#define __NULLPTR                0


#ifdef __LINKER__
/* Help figure out the origin of illegal preprocessor content in linker scripts. */
#define struct    <<__FILE__:__LINE__:ERROR: Invalid keyword: 'struct'>>
#define union     <<__FILE__:__LINE__:ERROR: Invalid keyword: 'union'>>
#define typedef   <<__FILE__:__LINE__:ERROR: Invalid keyword: 'typedef'>>
#define enum      <<__FILE__:__LINE__:ERROR: Invalid keyword: 'enum'>>
#endif /* __LINKER__ */
