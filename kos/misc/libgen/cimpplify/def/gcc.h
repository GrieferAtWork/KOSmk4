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

/* GCC */
#undef __INTELLISENSE__
#undef _MSC_VER
#undef __clang__
#undef __DEEMON__
#undef __INTEL_VERSION__
#undef __INTEL_COMPILER
#undef __ICL
#undef __ICC
#undef __ECC
#define __CC__ 1

#define __PREPROCESSOR_HAVE_CAT
#define __PREPROCESSOR_HAVE_STR
#define __PREPROCESSOR_HAVE_VA_ARGS
#define __PREPROCESSOR_HAVE_INCLUDE_NEXT
#define __PREPROCESSOR_HAVE_WARNING

#undef __COMPILER_NO_DOLLAR_IN_SYMBOL

#define __STDC__ 1
#define __P(x) x
#undef __NO_PROTOTYPES

#undef _OPENACC
#undef _OPENMP
#undef __cpp_transactional_memory
#define __GNUC__ 12
#define __GNUC_MINOR__ 1
#define __GNUC_PATCH__ 0
#define __GNUC_PATCHLEVEL__ 0
#define __GCC_VERSION_NUM 90100
#define __hybrid_alloca __builtin_alloca
#undef __NO_XBLOCK
#define __SYSDECL_BEGIN __DECL_BEGIN
#define __SYSDECL_END   __DECL_END
#define __likely(x)   (__builtin_expect(!!(x), 1))
#define __unlikely(x) (__builtin_expect(!!(x), 0))
#define likely(x)   (__builtin_expect(!!(x), 1))
#define unlikely(x) (__builtin_expect(!!(x), 0))
#define __COMPILER_HAVE_PRAGMA_PUSHMACRO
#define __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#define __COMPILER_HAVE_PRAGMA_GCC_VISIBILITY
#define __COMPILER_HAVE_LONGDOUBLE
#define __LONGDOUBLE long double
#define __COMPILER_HAVE_GCC_ASM
#define __COMPILER_HAVE_REGISTER_VARS
#define __COMPILER_HAVE_PRAGMA_PACK
#define __COMPILER_HAVE_ADDRESSIBLE_LABELS
#define __COMPILER_HAVE_TYPEOF
#define __COMPILER_HAVE_LONGLONG
#define __COMPILER_HAVE_TRANSPARENT_NONCLASS
#define __COMPILER_HAVE_TRANSPARENT_STRUCT
#define __COMPILER_HAVE_TRANSPARENT_UNION
#define __COMPILER_HAVE_VARIABLE_LENGTH_ARRAYS
#define __COMPILER_ASMNAME __asm__

#define __ATTR_NOINLINE __attribute__((__noinline__))
#define   ATTR_NOINLINE __attribute__((__noinline__))
#undef __NO_ATTR_NOINLINE

#define __ATTR_NORETURN __attribute__((__noreturn__))
#define   ATTR_NORETURN __attribute__((__noreturn__))
#undef __NO_ATTR_NORETURN

#undef __NO_ATTR_FALLTHROUGH

#define __NO_ATTR_W64
#define __ATTR_W64
#define   ATTR_W64

#define __ATTR_LEAF __attribute__((__leaf__))
#define   ATTR_LEAF __attribute__((__leaf__))
#undef __NO_ATTR_LEAF

#define __ATTR_PURE __attribute__((__pure__))
#define   ATTR_PURE __attribute__((__pure__))
#undef __NO_ATTR_PURE

#define __ATTR_CONST __attribute__((__const__))
#define   ATTR_CONST __attribute__((__const__))
#undef __NO_ATTR_CONST

#define __ATTR_FLATTEN __attribute__((__flatten__))
#define   ATTR_FLATTEN __attribute__((__flatten__))
#undef __NO_ATTR_FLATTEN

#define __ATTR_MALLOC __attribute__((__malloc__))
#define   ATTR_MALLOC __attribute__((__malloc__))
#undef __NO_ATTR_MALLOC

#define __ATTR_ALLOC_SIZE(ppars) __attribute__((__alloc_size__ ppars))
#define   ATTR_ALLOC_SIZE(ppars) __attribute__((__alloc_size__ ppars))
#undef __NO_ATTR_ALLOC_SIZE

#define __ATTR_UNUSED __attribute__((__unused__))
#define   ATTR_UNUSED __attribute__((__unused__))
#undef __NO_ATTR_UNUSED

#define __ATTR_USED __attribute__((__used__))
#define   ATTR_USED __attribute__((__used__))
#undef __NO_ATTR_USED

#define __ATTR_DEPRECATED_ __attribute__((__deprecated__))
#define   ATTR_DEPRECATED_ __attribute__((__deprecated__))
#define __ATTR_DEPRECATED(text) __attribute__((__deprecated__(text)))
#define   ATTR_DEPRECATED(text) __attribute__((__deprecated__(text)))
#undef __NO_ATTR_DEPRECATED

#define __ATTR_SENTINEL __attribute__((__sentinel__))
#define   ATTR_SENTINEL __attribute__((__sentinel__))
#define __ATTR_SENTINEL_O(x) __attribute__((__sentinel__(x)))
#define   ATTR_SENTINEL_O(x) __attribute__((__sentinel__(x)))
#undef __NO_ATTR_SENTINEL
#undef __NO_ATTR_SENTINEL_O

#define __ATTR_HOT __attribute__((__hot__))
#define   ATTR_HOT __attribute__((__hot__))
#undef __NO_ATTR_HOT

#define __ATTR_COLD __attribute__((__cold__))
#define   ATTR_COLD __attribute__((__cold__))
#undef __NO_ATTR_COLD

#define __ATTR_NOCLONE __attribute__((__noclone__))
#define   ATTR_NOCLONE __attribute__((__noclone__))
#undef __NO_ATTR_NOCLONE

#define __ATTR_THREAD_IS___thread
#define __ATTR_THREAD __thread
#define   ATTR_THREAD __thread
#undef __NO_ATTR_THREAD

#define __ATTR_ASSUME_ALIGNED(n) __attribute__((__assume_aligned__(n)))
#define   ATTR_ASSUME_ALIGNED(n) __attribute__((__assume_aligned__(n)))
#undef __NO_ATTR_ASSUME_ALIGNED

#define __ATTR_ALLOC_ALIGN(pari) __attribute__((__alloc_align__(pari)))
#define   ATTR_ALLOC_ALIGN(pari) __attribute__((__alloc_align__(pari)))
#undef __NO_ATTR_ALLOC_ALIGN

#define __ATTR_NOTHROW __attribute__((__nothrow__))
#define   ATTR_NOTHROW __attribute__((__nothrow__))
#undef __NO_ATTR_NOTHROW

#define __ATTR_OPTIMIZE(opt) __attribute__((__optimize__(opt)))
#define   ATTR_OPTIMIZE(opt) __attribute__((__optimize__(opt)))
#undef __NO_ATTR_OPTIMIZE

#define __ATTR_TRANSPARENT_UNION __attribute__((__transparent_union__))
#define   ATTR_TRANSPARENT_UNION __attribute__((__transparent_union__))
#undef __NO_ATTR_TRANSPARENT_UNION

#define __ATTR_FORMAT_PRINTF(fmt, args) __attribute__((__format__(__printf__, fmt, args)))
#define   ATTR_FORMAT_PRINTF(fmt, args) __attribute__((__format__(__printf__, fmt, args)))
#undef __NO_ATTR_FORMAT_PRINTF

#define __ATTR_FORMAT_SCANF(fmt, args)    __attribute__((__format__(__scanf__, fmt, args)))
#define   ATTR_FORMAT_SCANF(fmt, args)    __attribute__((__format__(__scanf__, fmt, args)))
#define __ATTR_FORMAT_STRFMON(fmt, args)  __attribute__((__format__(__strfmon__, fmt, args)))
#define   ATTR_FORMAT_STRFMON(fmt, args)  __attribute__((__format__(__strfmon__, fmt, args)))
#define __ATTR_FORMAT_STRFTIME(fmt, args) __attribute__((__format__(__strftime__, fmt, 0)))
#define   ATTR_FORMAT_STRFTIME(fmt, args) __attribute__((__format__(__strftime__, fmt, 0)))
#undef __NO_ATTR_FORMAT_SCANF
#undef __NO_ATTR_FORMAT_STRFMON
#undef __NO_ATTR_FORMAT_STRFTIME

#define __ATTR_NOPLT __attribute__((__noplt__))
#define   ATTR_NOPLT __attribute__((__noplt__))
#undef __NO_ATTR_NOPLT

#define __ATTR_NONNULL(ppars)     __attribute__((__nonnull__ ppars))
#define   ATTR_NONNULL(ppars)     __attribute__((__nonnull__ ppars))
#define __ATTR_NONNULL_CXX(ppars) __attribute__((__nonnull__ ppars))
#define   ATTR_NONNULL_CXX(ppars) __attribute__((__nonnull__ ppars))
#undef __NO_ATTR_NONNULL

#define __ATTR_ACCESS_NONE(ptr_index)        __attribute__((__access__(__none__, ptr_index)))
#define   ATTR_ACCESS_NONE(ptr_index)        __attribute__((__access__(__none__, ptr_index)))
#define __ATTR_INS(ptr_index, size_index)    __attribute__((__access__(__read_only__, ptr_index, size_index)))
#define   ATTR_INS(ptr_index, size_index)    __attribute__((__access__(__read_only__, ptr_index, size_index)))
#define __ATTR_OUTS(ptr_index, size_index)   __attribute__((__access__(__write_only__, ptr_index, size_index)))
#define   ATTR_OUTS(ptr_index, size_index)   __attribute__((__access__(__write_only__, ptr_index, size_index)))
#define __ATTR_INOUTS(ptr_index, size_index) __attribute__((__access__(__read_write__, ptr_index, size_index)))
#define   ATTR_INOUTS(ptr_index, size_index) __attribute__((__access__(__read_write__, ptr_index, size_index)))
#define __ATTR_IN_OPT(ptr_index)             __attribute__((__access__(__read_only__, ptr_index)))
#define   ATTR_IN_OPT(ptr_index)             __attribute__((__access__(__read_only__, ptr_index)))
#define __ATTR_OUT_OPT(ptr_index)            __attribute__((__access__(__write_only__, ptr_index)))
#define   ATTR_OUT_OPT(ptr_index)            __attribute__((__access__(__write_only__, ptr_index)))
#define __ATTR_INOUT_OPT(ptr_index)          __attribute__((__access__(__read_write__, ptr_index)))
#define   ATTR_INOUT_OPT(ptr_index)          __attribute__((__access__(__read_write__, ptr_index)))
#define __ATTR_IN(ptr_index)                 __attribute__((__access__(__read_only__, ptr_index), __nonnull__(ptr_index)))
#define   ATTR_IN(ptr_index)                 __attribute__((__access__(__read_only__, ptr_index), __nonnull__(ptr_index)))
#define __ATTR_OUT(ptr_index)                __attribute__((__access__(__write_only__, ptr_index), __nonnull__(ptr_index)))
#define   ATTR_OUT(ptr_index)                __attribute__((__access__(__write_only__, ptr_index), __nonnull__(ptr_index)))
#define __ATTR_INOUT(ptr_index)              __attribute__((__access__(__read_write__, ptr_index), __nonnull__(ptr_index)))
#define   ATTR_INOUT(ptr_index)              __attribute__((__access__(__read_write__, ptr_index), __nonnull__(ptr_index)))

#define __ATTR_WUNUSED __attribute__((__warn_unused_result__))
#define   ATTR_WUNUSED __attribute__((__warn_unused_result__))
#undef __NO_ATTR_WUNUSED

#define __ATTR_SELECTANY __attribute__((__selectany__))
#define   ATTR_SELECTANY __attribute__((__selectany__))
#undef __NO_ATTR_SELECTANY

#define __ATTR_WARNING(text)      __attribute__((__warning__(text)))
#define   ATTR_WARNING(text)      __attribute__((__warning__(text)))
#define __ATTR_ERROR(text)        __attribute__((__error__(text)))
#define   ATTR_ERROR(text)        __attribute__((__error__(text)))
#define __ATTR_SECTION(name)      __attribute__((__section__(name)))
#define   ATTR_SECTION(name)      __attribute__((__section__(name)))
#define __ATTR_RETNONNULL         __attribute__((__returns_nonnull__))
#define   ATTR_RETNONNULL         __attribute__((__returns_nonnull__))
#define __ATTR_PACKED             __attribute__((__packed__))
#define   ATTR_PACKED             __attribute__((__packed__))
#define __ATTR_ALIAS(name)        __attribute__((__alias__(name)))
#define   ATTR_ALIAS(name)        __attribute__((__alias__(name)))
#define __ATTR_ALIGNED(n)         __attribute__((__aligned__(n)))
#define   ATTR_ALIGNED(n)         __attribute__((__aligned__(n)))
#define __ATTR_WEAK               __attribute__((__weak__))
#define   ATTR_WEAK               __attribute__((__weak__))
#define __ATTR_RETURNS_TWICE      __attribute__((__returns_twice__))
#define   ATTR_RETURNS_TWICE      __attribute__((__returns_twice__))
#define __ATTR_EXTERNALLY_VISIBLE __attribute__((__externally_visible__))
#define   ATTR_EXTERNALLY_VISIBLE __attribute__((__externally_visible__))
#define __ATTR_VISIBILITY(vis)    __attribute__((__visibility__(vis)))
#define   ATTR_VISIBILITY(vis)    __attribute__((__visibility__(vis)))
#define __ATTR_LEAF_T             __attribute__((__leaf__))
#define   ATTR_LEAF_P             __attribute__((__leaf__))
#define __ATTR_PURE_T             __attribute__((__pure__))
#define   ATTR_PURE_T             __attribute__((__pure__))
#define __ATTR_CONST_T            __attribute__((__const__))
#define   ATTR_CONST_T            __attribute__((__const__))
#define __COMPILER_IMPURE()       __asm__("")
#define __XBLOCK                  __extension__
#define __XRETURN                 /* Nothing */

#define __ATTR_INLINE      __inline__
#define   ATTR_INLINE      __inline__
#undef __NO_ATTR_INLINE

#define __ATTR_FORCEINLINE __inline__ __attribute__((__always_inline__))
#define   ATTR_FORCEINLINE __inline__ __attribute__((__always_inline__))
#undef __NO_ATTR_FORCEINLINE

#define __ATTR_ARTIFICIAL __attribute__((__artificial__))
#define   ATTR_ARTIFICIAL __attribute__((__artificial__))
#undef __NO_ATTR_ARTIFICIAL

#define __ATTR_FORMAT_ARG(x) __attribute__((__format_arg__(x)))
#define   ATTR_FORMAT_ARG(x) __attribute__((__format_arg__(x)))
#undef __NO_ATTR_FORMAT_ARG

#define __LOCAL              static __inline__
#define   LOCAL              static __inline__
#define __FORCELOCAL         static __inline__ __attribute__((__always_inline__))
#define   FORCELOCAL         static __inline__ __attribute__((__always_inline__))
#define __EXTERN_INLINE      extern __inline__ __attribute__((__gnu_inline__))
#define   EXTERN_INLINE      extern __inline__ __attribute__((__gnu_inline__))
#define __EXTERN_FORCEINLINE extern __inline__ __attribute__((__always_inline__, __gnu_inline__))
#define   EXTERN_FORCEINLINE extern __inline__ __attribute__((__always_inline__, __gnu_inline__))
#undef __NO_EXTERN_INLINE
#define __LONGLONG  long long
#define __ULONGLONG unsigned long long
#define __COMPILER_FLEXIBLE_ARRAY(T, x) T x[]
#define __STATIC_IF if
#define __STATIC_ELSE else
#define __COMPILER_BARRIER()       __atomic_signal_fence(__ATOMIC_ACQ_REL)
#define __COMPILER_READ_BARRIER()  __atomic_signal_fence(__ATOMIC_ACQUIRE)
#define __COMPILER_WRITE_BARRIER() __atomic_signal_fence(__ATOMIC_RELEASE)
#define __COMPILER_IGNORE_UNINITIALIZED(var) var = var



#if __GCC_VERSION_NUM >= 29700
#pragma define __has_builtin __builtin_alloca
#pragma define __has_builtin __builtin_abs
#pragma define __has_builtin __builtin_fabs
#pragma define __has_builtin __builtin_labs
#pragma define __has_builtin __builtin_llabs
#pragma define __has_builtin __builtin_ffs
#pragma define __has_builtin __builtin_div
#pragma define __has_builtin __builtin_ldiv
#pragma define __has_builtin __builtin_ffloor
#pragma define __has_builtin __builtin_fceil
#pragma define __has_builtin __builtin_fmod
#pragma define __has_builtin __builtin_frem
#pragma define __has_builtin __builtin_memcpy
#pragma define __has_builtin __builtin_memcmp
#pragma define __has_builtin __builtin_memset
#pragma define __has_builtin __builtin_bzero
#pragma define __has_builtin __builtin_bcmp
#pragma define __has_builtin __builtin_strcpy
#pragma define __has_builtin __builtin_strcmp
#pragma define __has_builtin __builtin_strlen
#pragma define __has_builtin __builtin_fsqrt
#pragma define __has_builtin __builtin_sin
#pragma define __has_builtin __builtin_cos
#pragma define __has_builtin __builtin_getexp
#pragma define __has_builtin __builtin_getman
#pragma define __has_builtin __builtin_saveregs
#pragma define __has_builtin __builtin_classify_type
#pragma define __has_builtin __builtin_next_arg
#pragma define __has_builtin __builtin_args_info
#pragma define __has_builtin __builtin_constant_p
#pragma define __has_builtin __builtin_frame_address
#pragma define __has_builtin __builtin_return_address
#pragma define __has_builtin __builtin_aggregate_incoming_address
#pragma define __has_builtin __builtin_apply_args
#pragma define __has_builtin __builtin_apply
#pragma define __has_builtin __builtin_return
#pragma define __has_builtin __builtin_setjmp
#pragma define __has_builtin __builtin_longjmp
#pragma define __has_builtin __builtin_trap
#pragma define __has_builtin __builtin_putchar
#pragma define __has_builtin __builtin_puts
#pragma define __has_builtin __builtin_printf
#pragma define __has_builtin __builtin_fputc
#pragma define __has_builtin __builtin_fputs
#pragma define __has_builtin __builtin_fwrite
#pragma define __has_builtin __builtin_isgreater
#pragma define __has_builtin __builtin_isgreaterequal
#pragma define __has_builtin __builtin_isless
#pragma define __has_builtin __builtin_islessequal
#pragma define __has_builtin __builtin_islessgreater
#pragma define __has_builtin __builtin_isunordered
#pragma define __has_builtin __builtin_unwind_init
#pragma define __has_builtin __builtin_dwarf_cfa
#pragma define __has_builtin __builtin_dwarf_fp_regnum
#pragma define __has_builtin __builtin_init_dwarf_reg_sizes
#pragma define __has_builtin __builtin_frob_return_addr
#pragma define __has_builtin __builtin_extract_return_addr
#pragma define __has_builtin __builtin_eh_return
#pragma define __has_builtin __builtin_varargs_start
#pragma define __has_builtin __builtin_stdarg_start
#pragma define __has_builtin __builtin_va_end
#pragma define __has_builtin __builtin_va_copy
#pragma define __has_builtin __builtin_expect
#pragma define __has_builtin __builtin_new
#pragma define __has_builtin __builtin_vec_new
#pragma define __has_builtin __builtin_delete
#pragma define __has_builtin __builtin_vec_delete
#endif /* __GCC_VERSION_NUM >= 29700 */

#if __GCC_VERSION_NUM >= 30100
#pragma undef  __has_builtin __builtin_labs
#pragma undef  __has_builtin __builtin_llabs
#pragma define __has_builtin __builtin_conj
#pragma define __has_builtin __builtin_creal
#pragma define __has_builtin __builtin_cimag
#pragma define __has_builtin __builtin_index
#pragma define __has_builtin __builtin_rindex
#pragma define __has_builtin __builtin_strcat
#pragma define __has_builtin __builtin_strncat
#pragma define __has_builtin __builtin_strncpy
#pragma define __has_builtin __builtin_strncmp
#pragma define __has_builtin __builtin_strstr
#pragma define __has_builtin __builtin_strpbrk
#pragma define __has_builtin __builtin_strspn
#pragma define __has_builtin __builtin_strcspn
#pragma define __has_builtin __builtin_strchr
#pragma define __has_builtin __builtin_strrchr
#pragma define __has_builtin __builtin_fprintf
#endif /* __GCC_VERSION_NUM >= 30100 */

#if __GCC_VERSION_NUM >= 30200
#pragma undef  __has_builtin __builtin_div
#pragma undef  __has_builtin __builtin_ldiv
#pragma undef  __has_builtin __builtin_ffloor
#pragma undef  __has_builtin __builtin_fceil
#pragma undef  __has_builtin __builtin_fmod
#pragma undef  __has_builtin __builtin_frem
#pragma undef  __has_builtin __builtin_fsqrt
#pragma undef  __has_builtin __builtin_getexp
#pragma undef  __has_builtin __builtin_getman
#pragma undef  __has_builtin __builtin_init_dwarf_reg_sizes
#pragma undef  __has_builtin __builtin_new
#pragma undef  __has_builtin __builtin_vec_new
#pragma undef  __has_builtin __builtin_delete
#pragma undef  __has_builtin __builtin_vec_delete
#pragma define __has_builtin __builtin_labs
#pragma define __has_builtin __builtin_fabsf
#pragma define __has_builtin __builtin_fabsl
#pragma define __has_builtin __builtin_llabs
#pragma define __has_builtin __builtin_imaxabs
#pragma define __has_builtin __builtin_conjf
#pragma define __has_builtin __builtin_conjl
#pragma define __has_builtin __builtin_crealf
#pragma define __has_builtin __builtin_creall
#pragma define __has_builtin __builtin_cimagf
#pragma define __has_builtin __builtin_cimagl
#pragma define __has_builtin __builtin_sqrt
#pragma define __has_builtin __builtin_sqrtf
#pragma define __has_builtin __builtin_sinf
#pragma define __has_builtin __builtin_cosf
#pragma define __has_builtin __builtin_sqrtl
#pragma define __has_builtin __builtin_sinl
#pragma define __has_builtin __builtin_cosl
#pragma define __has_builtin __builtin_prefetch
#pragma define __has_builtin __builtin_putchar_unlocked
#pragma define __has_builtin __builtin_puts_unlocked
#pragma define __has_builtin __builtin_printf_unlocked
#pragma define __has_builtin __builtin_fputc_unlocked
#pragma define __has_builtin __builtin_fputs_unlocked
#pragma define __has_builtin __builtin_fwrite_unlocked
#pragma define __has_builtin __builtin_fprintf_unlocked
#pragma define __has_builtin __builtin_init_dwarf_reg_size_table
#pragma define __has_builtin __builtin_eh_return_data_regno
#endif /* __GCC_VERSION_NUM >= 30200 */

#if __GCC_VERSION_NUM >= 30300
#pragma undef  __has_builtin __builtin_varargs_start
#pragma define __has_builtin __builtin_va_start
#pragma define __has_builtin __builtin_abort
#pragma define __has_builtin __builtin_exit
#pragma define __has_builtin __builtin__exit
#pragma define __has_builtin __builtin__Exit
#endif /* __GCC_VERSION_NUM >= 30300 */

#if __GCC_VERSION_NUM >= 30400
#pragma define __has_builtin __builtin_floor
#pragma define __has_builtin __builtin_floorf
#pragma define __has_builtin __builtin_floorl
#pragma define __has_builtin __builtin_ceil
#pragma define __has_builtin __builtin_ceilf
#pragma define __has_builtin __builtin_ceill
#pragma define __has_builtin __builtin_round
#pragma define __has_builtin __builtin_roundf
#pragma define __has_builtin __builtin_roundl
#pragma define __has_builtin __builtin_trunc
#pragma define __has_builtin __builtin_truncf
#pragma define __has_builtin __builtin_truncl
#pragma define __has_builtin __builtin_nearbyint
#pragma define __has_builtin __builtin_nearbyintf
#pragma define __has_builtin __builtin_nearbyintl
#pragma define __has_builtin __builtin_exp
#pragma define __has_builtin __builtin_log
#pragma define __has_builtin __builtin_expf
#pragma define __has_builtin __builtin_logf
#pragma define __has_builtin __builtin_expl
#pragma define __has_builtin __builtin_logl
#pragma define __has_builtin __builtin_inf
#pragma define __has_builtin __builtin_inff
#pragma define __has_builtin __builtin_infl
#pragma define __has_builtin __builtin_huge_val
#pragma define __has_builtin __builtin_huge_valf
#pragma define __has_builtin __builtin_huge_vall
#pragma define __has_builtin __builtin_nan
#pragma define __has_builtin __builtin_nanf
#pragma define __has_builtin __builtin_nanl
#pragma define __has_builtin __builtin_nans
#pragma define __has_builtin __builtin_nansf
#pragma define __has_builtin __builtin_nansl
#endif /* __GCC_VERSION_NUM >= 30400 */

#if __GCC_VERSION_NUM >= 30500
#pragma undef  __has_builtin __builtin_dwarf_fp_regnum
#pragma define __has_builtin __builtin_acos
#pragma define __has_builtin __builtin_acosf
#pragma define __has_builtin __builtin_acosh
#pragma define __has_builtin __builtin_acoshf
#pragma define __has_builtin __builtin_acoshl
#pragma define __has_builtin __builtin_acosl
#pragma define __has_builtin __builtin_asin
#pragma define __has_builtin __builtin_asinf
#pragma define __has_builtin __builtin_asinh
#pragma define __has_builtin __builtin_asinhf
#pragma define __has_builtin __builtin_asinhl
#pragma define __has_builtin __builtin_asinl
#pragma define __has_builtin __builtin_atan
#pragma define __has_builtin __builtin_atan2
#pragma define __has_builtin __builtin_atan2f
#pragma define __has_builtin __builtin_atan2l
#pragma define __has_builtin __builtin_atanf
#pragma define __has_builtin __builtin_atanh
#pragma define __has_builtin __builtin_atanhf
#pragma define __has_builtin __builtin_atanhl
#pragma define __has_builtin __builtin_atanl
#pragma define __has_builtin __builtin_cbrt
#pragma define __has_builtin __builtin_cbrtf
#pragma define __has_builtin __builtin_cbrtl
#pragma define __has_builtin __builtin_copysign
#pragma define __has_builtin __builtin_copysignf
#pragma define __has_builtin __builtin_copysignl
#pragma define __has_builtin __builtin_cosh
#pragma define __has_builtin __builtin_coshf
#pragma define __has_builtin __builtin_coshl
#pragma define __has_builtin __builtin_drem
#pragma define __has_builtin __builtin_dremf
#pragma define __has_builtin __builtin_dreml
#pragma define __has_builtin __builtin_erf
#pragma define __has_builtin __builtin_erfc
#pragma define __has_builtin __builtin_erfcf
#pragma define __has_builtin __builtin_erfcl
#pragma define __has_builtin __builtin_erff
#pragma define __has_builtin __builtin_erfl
#pragma define __has_builtin __builtin_exp10
#pragma define __has_builtin __builtin_exp10f
#pragma define __has_builtin __builtin_exp10l
#pragma define __has_builtin __builtin_exp2
#pragma define __has_builtin __builtin_exp2f
#pragma define __has_builtin __builtin_exp2l
#pragma define __has_builtin __builtin_expm1
#pragma define __has_builtin __builtin_expm1f
#pragma define __has_builtin __builtin_expm1l
#pragma define __has_builtin __builtin_fdim
#pragma define __has_builtin __builtin_fdimf
#pragma define __has_builtin __builtin_fdiml
#pragma define __has_builtin __builtin_fma
#pragma define __has_builtin __builtin_fmaf
#pragma define __has_builtin __builtin_fmal
#pragma define __has_builtin __builtin_fmax
#pragma define __has_builtin __builtin_fmaxf
#pragma define __has_builtin __builtin_fmaxl
#pragma define __has_builtin __builtin_fmin
#pragma define __has_builtin __builtin_fminf
#pragma define __has_builtin __builtin_fminl
#pragma define __has_builtin __builtin_fmod
#pragma define __has_builtin __builtin_fmodf
#pragma define __has_builtin __builtin_fmodl
#pragma define __has_builtin __builtin_frexp
#pragma define __has_builtin __builtin_frexpf
#pragma define __has_builtin __builtin_frexpl
#pragma define __has_builtin __builtin_gamma
#pragma define __has_builtin __builtin_gammaf
#pragma define __has_builtin __builtin_gammal
#pragma define __has_builtin __builtin_hypot
#pragma define __has_builtin __builtin_hypotf
#pragma define __has_builtin __builtin_hypotl
#pragma define __has_builtin __builtin_ilogb
#pragma define __has_builtin __builtin_ilogbf
#pragma define __has_builtin __builtin_ilogbl
#pragma define __has_builtin __builtin_j0
#pragma define __has_builtin __builtin_j0f
#pragma define __has_builtin __builtin_j0l
#pragma define __has_builtin __builtin_j1
#pragma define __has_builtin __builtin_j1f
#pragma define __has_builtin __builtin_j1l
#pragma define __has_builtin __builtin_jn
#pragma define __has_builtin __builtin_jnf
#pragma define __has_builtin __builtin_jnl
#pragma define __has_builtin __builtin_ldexp
#pragma define __has_builtin __builtin_ldexpf
#pragma define __has_builtin __builtin_ldexpl
#pragma define __has_builtin __builtin_lgamma
#pragma define __has_builtin __builtin_lgammaf
#pragma define __has_builtin __builtin_lgammal
#pragma define __has_builtin __builtin_llrint
#pragma define __has_builtin __builtin_llrintf
#pragma define __has_builtin __builtin_llrintl
#pragma define __has_builtin __builtin_llround
#pragma define __has_builtin __builtin_llroundf
#pragma define __has_builtin __builtin_llroundl
#pragma define __has_builtin __builtin_log10
#pragma define __has_builtin __builtin_log10f
#pragma define __has_builtin __builtin_log10l
#pragma define __has_builtin __builtin_log1p
#pragma define __has_builtin __builtin_log1pf
#pragma define __has_builtin __builtin_log1pl
#pragma define __has_builtin __builtin_log2
#pragma define __has_builtin __builtin_log2f
#pragma define __has_builtin __builtin_log2l
#pragma define __has_builtin __builtin_logb
#pragma define __has_builtin __builtin_logbf
#pragma define __has_builtin __builtin_logbl
#pragma define __has_builtin __builtin_lrint
#pragma define __has_builtin __builtin_lrintf
#pragma define __has_builtin __builtin_lrintl
#pragma define __has_builtin __builtin_lround
#pragma define __has_builtin __builtin_lroundf
#pragma define __has_builtin __builtin_lroundl
#pragma define __has_builtin __builtin_modf
#pragma define __has_builtin __builtin_modff
#pragma define __has_builtin __builtin_modfl
#pragma define __has_builtin __builtin_nextafter
#pragma define __has_builtin __builtin_nextafterf
#pragma define __has_builtin __builtin_nextafterl
#pragma define __has_builtin __builtin_nexttoward
#pragma define __has_builtin __builtin_nexttowardf
#pragma define __has_builtin __builtin_nexttowardl
#pragma define __has_builtin __builtin_pow
#pragma define __has_builtin __builtin_pow10
#pragma define __has_builtin __builtin_pow10f
#pragma define __has_builtin __builtin_pow10l
#pragma define __has_builtin __builtin_powf
#pragma define __has_builtin __builtin_powl
#pragma define __has_builtin __builtin_remainder
#pragma define __has_builtin __builtin_remainderf
#pragma define __has_builtin __builtin_remainderl
#pragma define __has_builtin __builtin_remquo
#pragma define __has_builtin __builtin_remquof
#pragma define __has_builtin __builtin_remquol
#pragma define __has_builtin __builtin_rint
#pragma define __has_builtin __builtin_rintf
#pragma define __has_builtin __builtin_rintl
#pragma define __has_builtin __builtin_scalb
#pragma define __has_builtin __builtin_scalbf
#pragma define __has_builtin __builtin_scalbl
#pragma define __has_builtin __builtin_scalbln
#pragma define __has_builtin __builtin_scalblnf
#pragma define __has_builtin __builtin_scalblnl
#pragma define __has_builtin __builtin_scalbn
#pragma define __has_builtin __builtin_scalbnf
#pragma define __has_builtin __builtin_scalbnl
#pragma define __has_builtin __builtin_significand
#pragma define __has_builtin __builtin_significandf
#pragma define __has_builtin __builtin_significandl
#pragma define __has_builtin __builtin_sincos
#pragma define __has_builtin __builtin_sincosf
#pragma define __has_builtin __builtin_sincosl
#pragma define __has_builtin __builtin_sinh
#pragma define __has_builtin __builtin_sinhf
#pragma define __has_builtin __builtin_sinhl
#pragma define __has_builtin __builtin_tan
#pragma define __has_builtin __builtin_tanf
#pragma define __has_builtin __builtin_tanh
#pragma define __has_builtin __builtin_tanhf
#pragma define __has_builtin __builtin_tanhl
#pragma define __has_builtin __builtin_tanl
#pragma define __has_builtin __builtin_tgamma
#pragma define __has_builtin __builtin_tgammaf
#pragma define __has_builtin __builtin_tgammal
#pragma define __has_builtin __builtin_y0
#pragma define __has_builtin __builtin_y0f
#pragma define __has_builtin __builtin_y0l
#pragma define __has_builtin __builtin_y1
#pragma define __has_builtin __builtin_y1f
#pragma define __has_builtin __builtin_y1l
#pragma define __has_builtin __builtin_yn
#pragma define __has_builtin __builtin_ynf
#pragma define __has_builtin __builtin_ynl
#pragma define __has_builtin __builtin_cabs
#pragma define __has_builtin __builtin_cabsf
#pragma define __has_builtin __builtin_cabsl
#pragma define __has_builtin __builtin_cacos
#pragma define __has_builtin __builtin_cacosf
#pragma define __has_builtin __builtin_cacosh
#pragma define __has_builtin __builtin_cacoshf
#pragma define __has_builtin __builtin_cacoshl
#pragma define __has_builtin __builtin_cacosl
#pragma define __has_builtin __builtin_carg
#pragma define __has_builtin __builtin_cargf
#pragma define __has_builtin __builtin_cargl
#pragma define __has_builtin __builtin_casin
#pragma define __has_builtin __builtin_casinf
#pragma define __has_builtin __builtin_casinh
#pragma define __has_builtin __builtin_casinhf
#pragma define __has_builtin __builtin_casinhl
#pragma define __has_builtin __builtin_casinl
#pragma define __has_builtin __builtin_catan
#pragma define __has_builtin __builtin_catanf
#pragma define __has_builtin __builtin_catanh
#pragma define __has_builtin __builtin_catanhf
#pragma define __has_builtin __builtin_catanhl
#pragma define __has_builtin __builtin_catanl
#pragma define __has_builtin __builtin_ccos
#pragma define __has_builtin __builtin_ccosf
#pragma define __has_builtin __builtin_ccosh
#pragma define __has_builtin __builtin_ccoshf
#pragma define __has_builtin __builtin_ccoshl
#pragma define __has_builtin __builtin_ccosl
#pragma define __has_builtin __builtin_cexp
#pragma define __has_builtin __builtin_cexpf
#pragma define __has_builtin __builtin_cexpl
#pragma define __has_builtin __builtin_cpow
#pragma define __has_builtin __builtin_cpowf
#pragma define __has_builtin __builtin_cpowl
#pragma define __has_builtin __builtin_cproj
#pragma define __has_builtin __builtin_cprojf
#pragma define __has_builtin __builtin_cprojl
#pragma define __has_builtin __builtin_csin
#pragma define __has_builtin __builtin_csinf
#pragma define __has_builtin __builtin_csinh
#pragma define __has_builtin __builtin_csinhf
#pragma define __has_builtin __builtin_csinhl
#pragma define __has_builtin __builtin_csinl
#pragma define __has_builtin __builtin_csqrt
#pragma define __has_builtin __builtin_csqrtf
#pragma define __has_builtin __builtin_csqrtl
#pragma define __has_builtin __builtin_ctan
#pragma define __has_builtin __builtin_ctanf
#pragma define __has_builtin __builtin_ctanh
#pragma define __has_builtin __builtin_ctanhf
#pragma define __has_builtin __builtin_ctanhl
#pragma define __has_builtin __builtin_ctanl
#pragma define __has_builtin __builtin_bcopy
#pragma define __has_builtin __builtin_ffsl
#pragma define __has_builtin __builtin_ffsll
#pragma define __has_builtin __builtin_memmove
#pragma define __has_builtin __builtin_mempcpy
#pragma define __has_builtin __builtin_stpcpy
#pragma define __has_builtin __builtin_strdup
#pragma define __has_builtin __builtin_fscanf
#pragma define __has_builtin __builtin_scanf
#pragma define __has_builtin __builtin_snprintf
#pragma define __has_builtin __builtin_sprintf
#pragma define __has_builtin __builtin_sscanf
#pragma define __has_builtin __builtin_vfprintf
#pragma define __has_builtin __builtin_vfscanf
#pragma define __has_builtin __builtin_vprintf
#pragma define __has_builtin __builtin_vscanf
#pragma define __has_builtin __builtin_vsnprintf
#pragma define __has_builtin __builtin_vsprintf
#pragma define __has_builtin __builtin_vsscanf
#pragma define __has_builtin __builtin_calloc
#pragma define __has_builtin __builtin_clz
#pragma define __has_builtin __builtin_clzl
#pragma define __has_builtin __builtin_clzll
#pragma define __has_builtin __builtin_ctz
#pragma define __has_builtin __builtin_ctzl
#pragma define __has_builtin __builtin_ctzll
#pragma define __has_builtin __builtin_dcgettext
#pragma define __has_builtin __builtin_dgettext
#pragma define __has_builtin __builtin_dwarf_sp_column
#pragma define __has_builtin __builtin_gettext
#pragma define __has_builtin __builtin_malloc
#pragma define __has_builtin __builtin_parity
#pragma define __has_builtin __builtin_parityl
#pragma define __has_builtin __builtin_parityll
#pragma define __has_builtin __builtin_popcount
#pragma define __has_builtin __builtin_popcountl
#pragma define __has_builtin __builtin_popcountll
#pragma define __has_builtin __builtin_strfmon
#pragma define __has_builtin __builtin_strftime
#endif /* __GCC_VERSION_NUM >= 30500 */

#if __GCC_VERSION_NUM >= 40000
#pragma define __has_builtin __builtin_signbit
#pragma define __has_builtin __builtin_signbitf
#pragma define __has_builtin __builtin_signbitl
#pragma define __has_builtin __builtin_isalnum
#pragma define __has_builtin __builtin_isalpha
#pragma define __has_builtin __builtin_isascii
#pragma define __has_builtin __builtin_isblank
#pragma define __has_builtin __builtin_iscntrl
#pragma define __has_builtin __builtin_isdigit
#pragma define __has_builtin __builtin_isgraph
#pragma define __has_builtin __builtin_islower
#pragma define __has_builtin __builtin_isprint
#pragma define __has_builtin __builtin_ispunct
#pragma define __has_builtin __builtin_isspace
#pragma define __has_builtin __builtin_isupper
#pragma define __has_builtin __builtin_isxdigit
#pragma define __has_builtin __builtin_toascii
#pragma define __has_builtin __builtin_tolower
#pragma define __has_builtin __builtin_toupper
#pragma define __has_builtin __builtin_iswalnum
#pragma define __has_builtin __builtin_iswalpha
#pragma define __has_builtin __builtin_iswblank
#pragma define __has_builtin __builtin_iswcntrl
#pragma define __has_builtin __builtin_iswdigit
#pragma define __has_builtin __builtin_iswgraph
#pragma define __has_builtin __builtin_iswlower
#pragma define __has_builtin __builtin_iswprint
#pragma define __has_builtin __builtin_iswpunct
#pragma define __has_builtin __builtin_iswspace
#pragma define __has_builtin __builtin_iswupper
#pragma define __has_builtin __builtin_iswxdigit
#pragma define __has_builtin __builtin_towlower
#pragma define __has_builtin __builtin_towupper
#pragma define __has_builtin __builtin_clzimax
#pragma define __has_builtin __builtin_ctzimax
#pragma define __has_builtin __builtin_execl
#pragma define __has_builtin __builtin_execlp
#pragma define __has_builtin __builtin_execle
#pragma define __has_builtin __builtin_execv
#pragma define __has_builtin __builtin_execvp
#pragma define __has_builtin __builtin_execve
#pragma define __has_builtin __builtin_extend_pointer
#pragma define __has_builtin __builtin_ffsimax
#pragma define __has_builtin __builtin_fork
#pragma define __has_builtin __builtin_finite
#pragma define __has_builtin __builtin_finitef
#pragma define __has_builtin __builtin_finitel
#pragma define __has_builtin __builtin_isinf
#pragma define __has_builtin __builtin_isinff
#pragma define __has_builtin __builtin_isinfl
#pragma define __has_builtin __builtin_isnan
#pragma define __has_builtin __builtin_isnanf
#pragma define __has_builtin __builtin_isnanl
#pragma define __has_builtin __builtin_parityimax
#pragma define __has_builtin __builtin_popcountimax
#pragma define __has_builtin __builtin_stack_save
#pragma define __has_builtin __builtin_stack_restore
#pragma define __has_builtin __builtin_update_setjmp_buf
#pragma define __has_builtin __builtin_init_trampoline
#pragma define __has_builtin __builtin_adjust_trampoline
#pragma define __has_builtin __builtin_nonlocal_goto
#pragma define __has_builtin __builtin_profile_func_enter
#pragma define __has_builtin __builtin_profile_func_exit
#endif /* __GCC_VERSION_NUM >= 40000 */

#if __GCC_VERSION_NUM >= 40100
#pragma undef  __has_builtin __builtin_profile_func_enter
#pragma undef  __has_builtin __builtin_profile_func_exit
#pragma define __has_builtin __builtin_powi
#pragma define __has_builtin __builtin_powif
#pragma define __has_builtin __builtin_powil
#pragma define __has_builtin profile_func_enter
#pragma define __has_builtin profile_func_exit
#endif /* __GCC_VERSION_NUM >= 40100 */

#if __GCC_VERSION_NUM >= 40200
#pragma define __has_builtin __builtin_lceil
#pragma define __has_builtin __builtin_lceilf
#pragma define __has_builtin __builtin_lceill
#pragma define __has_builtin __builtin_lfloor
#pragma define __has_builtin __builtin_lfloorf
#pragma define __has_builtin __builtin_lfloorl
#pragma define __has_builtin __builtin_llceil
#pragma define __has_builtin __builtin_llceilf
#pragma define __has_builtin __builtin_llceill
#pragma define __has_builtin __builtin_llfloor
#pragma define __has_builtin __builtin_llfloorf
#pragma define __has_builtin __builtin_llfloorl
#pragma define __has_builtin __builtin_clog
#pragma define __has_builtin __builtin_clogf
#pragma define __has_builtin __builtin_clogl
#pragma define __has_builtin __builtin_clog10
#pragma define __has_builtin __builtin_clog10f
#pragma define __has_builtin __builtin_clog10l
#pragma define __has_builtin __builtin_stpncpy
#pragma define __has_builtin __builtin_strcasecmp
#pragma define __has_builtin __builtin_strndup
#pragma define __has_builtin __builtin_strncasecmp
#pragma define __has_builtin __builtin_object_size
#pragma define __has_builtin __builtin___memcpy_chk
#pragma define __has_builtin __builtin___memmove_chk
#pragma define __has_builtin __builtin___mempcpy_chk
#pragma define __has_builtin __builtin___memset_chk
#pragma define __has_builtin __builtin___stpcpy_chk
#pragma define __has_builtin __builtin___strcat_chk
#pragma define __has_builtin __builtin___strcpy_chk
#pragma define __has_builtin __builtin___strncat_chk
#pragma define __has_builtin __builtin___strncpy_chk
#pragma define __has_builtin __builtin___snprintf_chk
#pragma define __has_builtin __builtin___sprintf_chk
#pragma define __has_builtin __builtin___vsnprintf_chk
#pragma define __has_builtin __builtin___vsprintf_chk
#pragma define __has_builtin __builtin___fprintf_chk
#pragma define __has_builtin __builtin___printf_chk
#pragma define __has_builtin __builtin___vfprintf_chk
#pragma define __has_builtin __builtin___vprintf_chk
#pragma define __has_builtin __sync_fetch_and_add
#pragma define __has_builtin __sync_fetch_and_add_1
#pragma define __has_builtin __sync_fetch_and_add_2
#pragma define __has_builtin __sync_fetch_and_add_4
#pragma define __has_builtin __sync_fetch_and_add_8
#pragma define __has_builtin __sync_fetch_and_sub
#pragma define __has_builtin __sync_fetch_and_sub_1
#pragma define __has_builtin __sync_fetch_and_sub_2
#pragma define __has_builtin __sync_fetch_and_sub_4
#pragma define __has_builtin __sync_fetch_and_sub_8
#pragma define __has_builtin __sync_fetch_and_or
#pragma define __has_builtin __sync_fetch_and_or_1
#pragma define __has_builtin __sync_fetch_and_or_2
#pragma define __has_builtin __sync_fetch_and_or_4
#pragma define __has_builtin __sync_fetch_and_or_8
#pragma define __has_builtin __sync_fetch_and_and
#pragma define __has_builtin __sync_fetch_and_and_1
#pragma define __has_builtin __sync_fetch_and_and_2
#pragma define __has_builtin __sync_fetch_and_and_4
#pragma define __has_builtin __sync_fetch_and_and_8
#pragma define __has_builtin __sync_fetch_and_xor
#pragma define __has_builtin __sync_fetch_and_xor_1
#pragma define __has_builtin __sync_fetch_and_xor_2
#pragma define __has_builtin __sync_fetch_and_xor_4
#pragma define __has_builtin __sync_fetch_and_xor_8
#pragma define __has_builtin __sync_fetch_and_nand
#pragma define __has_builtin __sync_fetch_and_nand_1
#pragma define __has_builtin __sync_fetch_and_nand_2
#pragma define __has_builtin __sync_fetch_and_nand_4
#pragma define __has_builtin __sync_fetch_and_nand_8
#pragma define __has_builtin __sync_add_and_fetch
#pragma define __has_builtin __sync_add_and_fetch_1
#pragma define __has_builtin __sync_add_and_fetch_2
#pragma define __has_builtin __sync_add_and_fetch_4
#pragma define __has_builtin __sync_add_and_fetch_8
#pragma define __has_builtin __sync_sub_and_fetch
#pragma define __has_builtin __sync_sub_and_fetch_1
#pragma define __has_builtin __sync_sub_and_fetch_2
#pragma define __has_builtin __sync_sub_and_fetch_4
#pragma define __has_builtin __sync_sub_and_fetch_8
#pragma define __has_builtin __sync_or_and_fetch
#pragma define __has_builtin __sync_or_and_fetch_1
#pragma define __has_builtin __sync_or_and_fetch_2
#pragma define __has_builtin __sync_or_and_fetch_4
#pragma define __has_builtin __sync_or_and_fetch_8
#pragma define __has_builtin __sync_and_and_fetch
#pragma define __has_builtin __sync_and_and_fetch_1
#pragma define __has_builtin __sync_and_and_fetch_2
#pragma define __has_builtin __sync_and_and_fetch_4
#pragma define __has_builtin __sync_and_and_fetch_8
#pragma define __has_builtin __sync_xor_and_fetch
#pragma define __has_builtin __sync_xor_and_fetch_1
#pragma define __has_builtin __sync_xor_and_fetch_2
#pragma define __has_builtin __sync_xor_and_fetch_4
#pragma define __has_builtin __sync_xor_and_fetch_8
#pragma define __has_builtin __sync_nand_and_fetch
#pragma define __has_builtin __sync_nand_and_fetch_1
#pragma define __has_builtin __sync_nand_and_fetch_2
#pragma define __has_builtin __sync_nand_and_fetch_4
#pragma define __has_builtin __sync_nand_and_fetch_8
#pragma define __has_builtin __sync_bool_compare_and_swap
#pragma define __has_builtin __sync_bool_compare_and_swap_1
#pragma define __has_builtin __sync_bool_compare_and_swap_2
#pragma define __has_builtin __sync_bool_compare_and_swap_4
#pragma define __has_builtin __sync_bool_compare_and_swap_8
#pragma define __has_builtin __sync_val_compare_and_swap
#pragma define __has_builtin __sync_val_compare_and_swap_1
#pragma define __has_builtin __sync_val_compare_and_swap_2
#pragma define __has_builtin __sync_val_compare_and_swap_4
#pragma define __has_builtin __sync_val_compare_and_swap_8
#pragma define __has_builtin __sync_lock_test_and_set
#pragma define __has_builtin __sync_lock_test_and_set_1
#pragma define __has_builtin __sync_lock_test_and_set_2
#pragma define __has_builtin __sync_lock_test_and_set_4
#pragma define __has_builtin __sync_lock_test_and_set_8
#pragma define __has_builtin __sync_lock_release
#pragma define __has_builtin __sync_lock_release_1
#pragma define __has_builtin __sync_lock_release_2
#pragma define __has_builtin __sync_lock_release_4
#pragma define __has_builtin __sync_lock_release_8
#pragma define __has_builtin __sync_synchronize
#endif /* __GCC_VERSION_NUM >= 40200 */

#if __GCC_VERSION_NUM >= 40300
#pragma define __has_builtin __builtin_infd32
#pragma define __has_builtin __builtin_infd64
#pragma define __has_builtin __builtin_infd128
#pragma define __has_builtin __builtin_nand32
#pragma define __has_builtin __builtin_nand64
#pragma define __has_builtin __builtin_nand128
#pragma define __has_builtin __builtin_putc
#pragma define __has_builtin __builtin_putc_unlocked
#pragma define __has_builtin __builtin_finited32
#pragma define __has_builtin __builtin_finited64
#pragma define __has_builtin __builtin_finited128
#pragma define __has_builtin __builtin_isinfd32
#pragma define __has_builtin __builtin_isinfd64
#pragma define __has_builtin __builtin_isinfd128
#pragma define __has_builtin __builtin_isnand32
#pragma define __has_builtin __builtin_isnand64
#pragma define __has_builtin __builtin_isnand128
#pragma define __has_builtin __builtin_setjmp_setup
#pragma define __has_builtin __builtin_setjmp_dispatcher
#pragma define __has_builtin __builtin_setjmp_receiver
#pragma define __has_builtin __sync_fetch_and_add_16
#pragma define __has_builtin __sync_fetch_and_sub_16
#pragma define __has_builtin __sync_fetch_and_or_16
#pragma define __has_builtin __sync_fetch_and_and_16
#pragma define __has_builtin __sync_fetch_and_xor_16
#pragma define __has_builtin __sync_fetch_and_nand_16
#pragma define __has_builtin __sync_add_and_fetch_16
#pragma define __has_builtin __sync_sub_and_fetch_16
#pragma define __has_builtin __sync_or_and_fetch_16
#pragma define __has_builtin __sync_and_and_fetch_16
#pragma define __has_builtin __sync_xor_and_fetch_16
#pragma define __has_builtin __sync_nand_and_fetch_16
#pragma define __has_builtin __sync_bool_compare_and_swap_16
#pragma define __has_builtin __sync_val_compare_and_swap_16
#pragma define __has_builtin __sync_lock_test_and_set_16
#pragma define __has_builtin __sync_lock_release_16
#endif /* __GCC_VERSION_NUM >= 40300 */

#if __GCC_VERSION_NUM >= 40400
#pragma define __has_builtin __builtin_gamma_r
#pragma define __has_builtin __builtin_gammaf_r
#pragma define __has_builtin __builtin_gammal_r
#pragma define __has_builtin __builtin_lgamma_r
#pragma define __has_builtin __builtin_lgammaf_r
#pragma define __has_builtin __builtin_lgammal_r
#pragma define __has_builtin __builtin_signbitd32
#pragma define __has_builtin __builtin_signbitd64
#pragma define __has_builtin __builtin_signbitd128
#pragma define __has_builtin __builtin_cexpi
#pragma define __has_builtin __builtin_cexpif
#pragma define __has_builtin __builtin_cexpil
#pragma define __has_builtin __builtin_memchr
#pragma define __has_builtin __builtin_bswap32
#pragma define __has_builtin __builtin_bswap64
#pragma define __has_builtin __builtin___clear_cache
#pragma define __has_builtin __builtin_free
#pragma define __has_builtin __builtin_isfinite
#pragma define __has_builtin __builtin_isnormal
#pragma define __has_builtin __builtin_realloc
#pragma define __has_builtin __builtin_va_arg_pack
#pragma define __has_builtin __builtin_va_arg_pack_len
#pragma define __has_builtin __builtin___emutls_get_address
#pragma define __has_builtin __builtin___emutls_register_common
#endif /* __GCC_VERSION_NUM >= 40400 */

#if __GCC_VERSION_NUM >= 40500
#pragma undef  __has_builtin __builtin_stdarg_start
#pragma undef  __has_builtin __builtin___emutls_get_address
#pragma undef  __has_builtin __builtin___emutls_register_common
#pragma define __has_builtin __builtin_fpclassify
#pragma define __has_builtin __builtin_isinf_sign
#endif /* __GCC_VERSION_NUM >= 40500 */

#if __GCC_VERSION_NUM >= 40600
#pragma define __has_builtin __builtin_unreachable
#pragma define __has_builtin __builtin_unwind_resume
#pragma define __has_builtin __builtin_eh_pointer
#pragma define __has_builtin __builtin_eh_filter
#pragma define __has_builtin __builtin_eh_copy_values
#endif /* __GCC_VERSION_NUM >= 40600 */

#if __GCC_VERSION_NUM >= 40700
#pragma undef  __has_builtin __builtin_args_info
#pragma undef  __has_builtin profile_func_enter
#pragma undef  __has_builtin profile_func_exit
#pragma define __has_builtin __cyg_profile_func_enter
#pragma define __has_builtin __cyg_profile_func_exit
#endif /* __GCC_VERSION_NUM >= 40700 */

#if __GCC_VERSION_NUM >= 40800
#pragma define __has_builtin __builtin_iceil
#pragma define __has_builtin __builtin_iceilf
#pragma define __has_builtin __builtin_iceill
#pragma define __has_builtin __builtin_ifloor
#pragma define __has_builtin __builtin_ifloorf
#pragma define __has_builtin __builtin_ifloorl
#pragma define __has_builtin __builtin_irint
#pragma define __has_builtin __builtin_irintf
#pragma define __has_builtin __builtin_irintl
#pragma define __has_builtin __builtin_iround
#pragma define __has_builtin __builtin_iroundf
#pragma define __has_builtin __builtin_iroundl
#pragma define __has_builtin __builtin_clrsb
#pragma define __has_builtin __builtin_clrsbimax
#pragma define __has_builtin __builtin_clrsbl
#pragma define __has_builtin __builtin_clrsbll
#pragma define __has_builtin __builtin_assume_aligned
#pragma define __has_builtin __builtin_init_heap_trampoline
#pragma define __has_builtin __builtin_alloca_with_align
#pragma define __has_builtin __builtin___stpncpy_chk
#pragma define __has_builtin __atomic_test_and_set
#pragma define __has_builtin __atomic_clear
#pragma define __has_builtin __atomic_exchange
#pragma define __has_builtin __atomic_exchange_n
#pragma define __has_builtin __atomic_exchange_1
#pragma define __has_builtin __atomic_exchange_2
#pragma define __has_builtin __atomic_exchange_4
#pragma define __has_builtin __atomic_exchange_8
#pragma define __has_builtin __atomic_exchange_16
#pragma define __has_builtin __atomic_load
#pragma define __has_builtin __atomic_load_n
#pragma define __has_builtin __atomic_load_1
#pragma define __has_builtin __atomic_load_2
#pragma define __has_builtin __atomic_load_4
#pragma define __has_builtin __atomic_load_8
#pragma define __has_builtin __atomic_load_16
#pragma define __has_builtin __atomic_compare_exchange
#pragma define __has_builtin __atomic_compare_exchange_n
#pragma define __has_builtin __atomic_compare_exchange_1
#pragma define __has_builtin __atomic_compare_exchange_2
#pragma define __has_builtin __atomic_compare_exchange_4
#pragma define __has_builtin __atomic_compare_exchange_8
#pragma define __has_builtin __atomic_compare_exchange_16
#pragma define __has_builtin __atomic_store
#pragma define __has_builtin __atomic_store_n
#pragma define __has_builtin __atomic_store_1
#pragma define __has_builtin __atomic_store_2
#pragma define __has_builtin __atomic_store_4
#pragma define __has_builtin __atomic_store_8
#pragma define __has_builtin __atomic_store_16
#pragma define __has_builtin __atomic_add_fetch
#pragma define __has_builtin __atomic_add_fetch_1
#pragma define __has_builtin __atomic_add_fetch_2
#pragma define __has_builtin __atomic_add_fetch_4
#pragma define __has_builtin __atomic_add_fetch_8
#pragma define __has_builtin __atomic_add_fetch_16
#pragma define __has_builtin __atomic_sub_fetch
#pragma define __has_builtin __atomic_sub_fetch_1
#pragma define __has_builtin __atomic_sub_fetch_2
#pragma define __has_builtin __atomic_sub_fetch_4
#pragma define __has_builtin __atomic_sub_fetch_8
#pragma define __has_builtin __atomic_sub_fetch_16
#pragma define __has_builtin __atomic_and_fetch
#pragma define __has_builtin __atomic_and_fetch_1
#pragma define __has_builtin __atomic_and_fetch_2
#pragma define __has_builtin __atomic_and_fetch_4
#pragma define __has_builtin __atomic_and_fetch_8
#pragma define __has_builtin __atomic_and_fetch_16
#pragma define __has_builtin __atomic_nand_fetch
#pragma define __has_builtin __atomic_nand_fetch_1
#pragma define __has_builtin __atomic_nand_fetch_2
#pragma define __has_builtin __atomic_nand_fetch_4
#pragma define __has_builtin __atomic_nand_fetch_8
#pragma define __has_builtin __atomic_nand_fetch_16
#pragma define __has_builtin __atomic_xor_fetch
#pragma define __has_builtin __atomic_xor_fetch_1
#pragma define __has_builtin __atomic_xor_fetch_2
#pragma define __has_builtin __atomic_xor_fetch_4
#pragma define __has_builtin __atomic_xor_fetch_8
#pragma define __has_builtin __atomic_xor_fetch_16
#pragma define __has_builtin __atomic_or_fetch
#pragma define __has_builtin __atomic_or_fetch_1
#pragma define __has_builtin __atomic_or_fetch_2
#pragma define __has_builtin __atomic_or_fetch_4
#pragma define __has_builtin __atomic_or_fetch_8
#pragma define __has_builtin __atomic_or_fetch_16
#pragma define __has_builtin __atomic_fetch_add
#pragma define __has_builtin __atomic_fetch_add_1
#pragma define __has_builtin __atomic_fetch_add_2
#pragma define __has_builtin __atomic_fetch_add_4
#pragma define __has_builtin __atomic_fetch_add_8
#pragma define __has_builtin __atomic_fetch_add_16
#pragma define __has_builtin __atomic_fetch_sub
#pragma define __has_builtin __atomic_fetch_sub_1
#pragma define __has_builtin __atomic_fetch_sub_2
#pragma define __has_builtin __atomic_fetch_sub_4
#pragma define __has_builtin __atomic_fetch_sub_8
#pragma define __has_builtin __atomic_fetch_sub_16
#pragma define __has_builtin __atomic_fetch_and
#pragma define __has_builtin __atomic_fetch_and_1
#pragma define __has_builtin __atomic_fetch_and_2
#pragma define __has_builtin __atomic_fetch_and_4
#pragma define __has_builtin __atomic_fetch_and_8
#pragma define __has_builtin __atomic_fetch_and_16
#pragma define __has_builtin __atomic_fetch_nand
#pragma define __has_builtin __atomic_fetch_nand_1
#pragma define __has_builtin __atomic_fetch_nand_2
#pragma define __has_builtin __atomic_fetch_nand_4
#pragma define __has_builtin __atomic_fetch_nand_8
#pragma define __has_builtin __atomic_fetch_nand_16
#pragma define __has_builtin __atomic_fetch_xor
#pragma define __has_builtin __atomic_fetch_xor_1
#pragma define __has_builtin __atomic_fetch_xor_2
#pragma define __has_builtin __atomic_fetch_xor_4
#pragma define __has_builtin __atomic_fetch_xor_8
#pragma define __has_builtin __atomic_fetch_xor_16
#pragma define __has_builtin __atomic_fetch_or
#pragma define __has_builtin __atomic_fetch_or_1
#pragma define __has_builtin __atomic_fetch_or_2
#pragma define __has_builtin __atomic_fetch_or_4
#pragma define __has_builtin __atomic_fetch_or_8
#pragma define __has_builtin __atomic_fetch_or_16
#pragma define __has_builtin __atomic_always_lock_free
#pragma define __has_builtin __atomic_is_lock_free
#pragma define __has_builtin __atomic_thread_fence
#pragma define __has_builtin __atomic_signal_fence
#ifdef __cpp_transactional_memory
#pragma define __has_builtin __builtin__ITM_beginTransaction
#pragma define __has_builtin __builtin__ITM_commitTransaction
#pragma define __has_builtin __builtin__ITM_commitTransactionEH
#pragma define __has_builtin __builtin__ITM_abortTransaction
#pragma define __has_builtin __builtin__ITM_changeTransactionMode
#pragma define __has_builtin __builtin__ITM_memcpyRtWt
#pragma define __has_builtin __builtin__ITM_memmoveRtWt
#pragma define __has_builtin __builtin__ITM_memsetW
#pragma define __has_builtin __builtin__ITM_getTMCloneOrIrrevocable
#pragma define __has_builtin __builtin__ITM_getTMCloneSafe
#pragma define __has_builtin __builtin__ITM_malloc
#pragma define __has_builtin __builtin__ITM_calloc
#pragma define __has_builtin __builtin__ITM_free
#pragma define __has_builtin __builtin__ITM_LU1
#pragma define __has_builtin __builtin__ITM_LU2
#pragma define __has_builtin __builtin__ITM_LU4
#pragma define __has_builtin __builtin__ITM_LU8
#pragma define __has_builtin __builtin__ITM_LF
#pragma define __has_builtin __builtin__ITM_LD
#pragma define __has_builtin __builtin__ITM_LE
#pragma define __has_builtin __builtin__ITM_LB
#pragma define __has_builtin __builtin__ITM_WU1
#pragma define __has_builtin __builtin__ITM_WaRU1
#pragma define __has_builtin __builtin__ITM_WaWU1
#pragma define __has_builtin __builtin__ITM_WU2
#pragma define __has_builtin __builtin__ITM_WaRU2
#pragma define __has_builtin __builtin__ITM_WaWU2
#pragma define __has_builtin __builtin__ITM_WU4
#pragma define __has_builtin __builtin__ITM_WaRU4
#pragma define __has_builtin __builtin__ITM_WaWU4
#pragma define __has_builtin __builtin__ITM_WU8
#pragma define __has_builtin __builtin__ITM_WaRU8
#pragma define __has_builtin __builtin__ITM_WaWU8
#pragma define __has_builtin __builtin__ITM_WF
#pragma define __has_builtin __builtin__ITM_WaRF
#pragma define __has_builtin __builtin__ITM_WaWF
#pragma define __has_builtin __builtin__ITM_WD
#pragma define __has_builtin __builtin__ITM_WaRD
#pragma define __has_builtin __builtin__ITM_WaWD
#pragma define __has_builtin __builtin__ITM_WE
#pragma define __has_builtin __builtin__ITM_WaRE
#pragma define __has_builtin __builtin__ITM_WaWE
#pragma define __has_builtin __builtin__ITM_RU1
#pragma define __has_builtin __builtin__ITM_RaRU1
#pragma define __has_builtin __builtin__ITM_RaWU1
#pragma define __has_builtin __builtin__ITM_RfWU1
#pragma define __has_builtin __builtin__ITM_RU2
#pragma define __has_builtin __builtin__ITM_RaRU2
#pragma define __has_builtin __builtin__ITM_RaWU2
#pragma define __has_builtin __builtin__ITM_RfWU2
#pragma define __has_builtin __builtin__ITM_RU4
#pragma define __has_builtin __builtin__ITM_RaRU4
#pragma define __has_builtin __builtin__ITM_RaWU4
#pragma define __has_builtin __builtin__ITM_RfWU4
#pragma define __has_builtin __builtin__ITM_RU8
#pragma define __has_builtin __builtin__ITM_RaRU8
#pragma define __has_builtin __builtin__ITM_RaWU8
#pragma define __has_builtin __builtin__ITM_RfWU8
#pragma define __has_builtin __builtin__ITM_RF
#pragma define __has_builtin __builtin__ITM_RaRF
#pragma define __has_builtin __builtin__ITM_RaWF
#pragma define __has_builtin __builtin__ITM_RfWF
#pragma define __has_builtin __builtin__ITM_RD
#pragma define __has_builtin __builtin__ITM_RaRD
#pragma define __has_builtin __builtin__ITM_RaWD
#pragma define __has_builtin __builtin__ITM_RfWD
#pragma define __has_builtin __builtin__ITM_RE
#pragma define __has_builtin __builtin__ITM_RaRE
#pragma define __has_builtin __builtin__ITM_RaWE
#pragma define __has_builtin __builtin__ITM_RfWE
#endif /* __cpp_transactional_memory */
#endif /* __GCC_VERSION_NUM >= 40800 */

#if __GCC_VERSION_NUM >= 40900
#pragma define __has_builtin __builtin_bswap16
#pragma define __has_builtin __builtin_FILE
#pragma define __has_builtin __builtin_FUNCTION
#pragma define __has_builtin __builtin_LINE
#endif /* __GCC_VERSION_NUM >= 40900 */

#if __GCC_VERSION_NUM >= 41000
#pragma undef  __has_builtin __builtin_setjmp_dispatcher
#pragma define __has_builtin __builtin_fabsd32
#pragma define __has_builtin __builtin_fabsd64
#pragma define __has_builtin __builtin_fabsd128
#pragma define __has_builtin __builtin_posix_memalign
#pragma define __has_builtin __atomic_feraiseexcept
#pragma define __has_builtin __cilkrts_enter_frame_1
#pragma define __has_builtin __cilkrts_enter_frame_fast_1
#pragma define __has_builtin __cilkrts_detach
#pragma define __has_builtin __cilkrts_rethrow
#pragma define __has_builtin __cilkrts_synched
#pragma define __has_builtin __cilkrts_sync
#pragma define __has_builtin __cilkrts_leave_frame
#pragma define __has_builtin __cilkrts_pop_frame
#pragma define __has_builtin __cilkrts_save_fp_ctrl_state
#endif /* __GCC_VERSION_NUM >= 41000 */

#if __GCC_VERSION_NUM >= 50000
#pragma define __has_builtin __builtin_aligned_alloc
#endif /* __GCC_VERSION_NUM >= 50000 */

#if __GCC_VERSION_NUM >= 60000
#pragma define __has_builtin __builtin_add_overflow
#pragma define __has_builtin __builtin_sub_overflow
#pragma define __has_builtin __builtin_mul_overflow
#pragma define __has_builtin __builtin_sadd_overflow
#pragma define __has_builtin __builtin_saddl_overflow
#pragma define __has_builtin __builtin_saddll_overflow
#pragma define __has_builtin __builtin_ssub_overflow
#pragma define __has_builtin __builtin_ssubl_overflow
#pragma define __has_builtin __builtin_ssubll_overflow
#pragma define __has_builtin __builtin_smul_overflow
#pragma define __has_builtin __builtin_smull_overflow
#pragma define __has_builtin __builtin_smulll_overflow
#pragma define __has_builtin __builtin_uadd_overflow
#pragma define __has_builtin __builtin_uaddl_overflow
#pragma define __has_builtin __builtin_uaddll_overflow
#pragma define __has_builtin __builtin_usub_overflow
#pragma define __has_builtin __builtin_usubl_overflow
#pragma define __has_builtin __builtin_usubll_overflow
#pragma define __has_builtin __builtin_umul_overflow
#pragma define __has_builtin __builtin_umull_overflow
#pragma define __has_builtin __builtin_umulll_overflow
#ifdef _OPENACC
#pragma define __has_builtin __builtin_acc_get_device_type
#pragma define __has_builtin __builtin_GOACC_data_start
#pragma define __has_builtin __builtin_GOACC_data_end
#pragma define __has_builtin __builtin_GOACC_enter_exit_data
#pragma define __has_builtin __builtin_GOACC_parallel
#pragma define __has_builtin __builtin_GOACC_update
#pragma define __has_builtin __builtin_GOACC_wait
#pragma define __has_builtin __builtin_GOACC_get_thread_num
#pragma define __has_builtin __builtin_GOACC_get_num_threads
#endif /* _OPENACC */
#pragma define __has_builtin __builtin_acc_on_device
#pragma define __has_builtin __cilkrts_cilk_for_32
#pragma define __has_builtin __cilkrts_cilk_for_64
#pragma define __has_builtin __chkp_intersect
#pragma define __has_builtin __chkp_sizeof
#pragma define __has_builtin __chkp_narrow
#pragma define __has_builtin __builtin___chkp_bndcl
#pragma define __has_builtin __builtin___chkp_bndcu
#pragma define __has_builtin __builtin___chkp_bndstx
#pragma define __has_builtin __builtin___chkp_bndldx
#pragma define __has_builtin __builtin___chkp_bndret
#pragma define __has_builtin __builtin___chkp_bndmk
#pragma define __has_builtin __builtin___chkp_extract_lower
#pragma define __has_builtin __builtin___chkp_extract_upper
#pragma define __has_builtin __builtin___bnd_set_ptr_bounds
#pragma define __has_builtin __builtin___bnd_init_ptr_bounds
#pragma define __has_builtin __builtin___bnd_null_ptr_bounds
#pragma define __has_builtin __builtin___bnd_copy_ptr_bounds
#pragma define __has_builtin __builtin___bnd_narrow_ptr_bounds
#pragma define __has_builtin __builtin___bnd_store_ptr_bounds
#pragma define __has_builtin __builtin___bnd_chk_ptr_lbounds
#pragma define __has_builtin __builtin___bnd_chk_ptr_ubounds
#pragma define __has_builtin __builtin___bnd_chk_ptr_bounds
#pragma define __has_builtin __builtin___bnd_get_ptr_lbound
#pragma define __has_builtin __builtin___bnd_get_ptr_ubound
#pragma define __has_builtin __builtin_chkp_memcpy_nobnd
#pragma define __has_builtin __builtin_chkp_memcpy_nochk
#pragma define __has_builtin __builtin_chkp_memcpy_nobnd_nochk
#pragma define __has_builtin __builtin_chkp_memmove_nobnd
#pragma define __has_builtin __builtin_chkp_memmove_nochk
#pragma define __has_builtin __builtin_chkp_memmove_nobnd_nochk
#pragma define __has_builtin __builtin_chkp_mempcpy_nobnd
#pragma define __has_builtin __builtin_chkp_mempcpy_nochk
#pragma define __has_builtin __builtin_chkp_mempcpy_nobnd_nochk
#pragma define __has_builtin __builtin_chkp_memset_nobnd
#pragma define __has_builtin __builtin_chkp_memset_nochk
#pragma define __has_builtin __builtin_chkp_memset_nobnd_nochk
#endif /* __GCC_VERSION_NUM >= 60000 */

#if __GCC_VERSION_NUM >= 70000
#pragma undef  __has_builtin __builtin_GOACC_parallel
#pragma undef  __has_builtin __builtin_GOACC_get_thread_num
#pragma undef  __has_builtin __builtin_GOACC_get_num_threads
#ifdef _OPENACC
#pragma define __has_builtin __builtin_GOACC_parallel_keyed
#pragma define __has_builtin __builtin_GOACC_declare
#endif /* _OPENACC */
#ifdef __cpp_transactional_memory
#pragma define __has_builtin __builtin__ITM_memcpyRnWt
#pragma define __has_builtin __builtin__ITM_memcpyRtWn
#endif /* __cpp_transactional_memory */
#endif /* __GCC_VERSION_NUM >= 70000 */

#if __GCC_VERSION_NUM >= 70001
#pragma define __has_builtin __builtin_copysignf16
#pragma define __has_builtin __builtin_copysignf32
#pragma define __has_builtin __builtin_copysignf64
#pragma define __has_builtin __builtin_copysignf128
#pragma define __has_builtin __builtin_copysignf32x
#pragma define __has_builtin __builtin_copysignf64x
#pragma define __has_builtin __builtin_copysignf128x
#pragma define __has_builtin __builtin_fabsf16
#pragma define __has_builtin __builtin_fabsf32
#pragma define __has_builtin __builtin_fabsf64
#pragma define __has_builtin __builtin_fabsf128
#pragma define __has_builtin __builtin_fabsf32x
#pragma define __has_builtin __builtin_fabsf64x
#pragma define __has_builtin __builtin_fabsf128x
#pragma define __has_builtin __builtin_huge_valf16
#pragma define __has_builtin __builtin_huge_valf32
#pragma define __has_builtin __builtin_huge_valf64
#pragma define __has_builtin __builtin_huge_valf128
#pragma define __has_builtin __builtin_huge_valf32x
#pragma define __has_builtin __builtin_huge_valf64x
#pragma define __has_builtin __builtin_huge_valf128x
#pragma define __has_builtin __builtin_inff16
#pragma define __has_builtin __builtin_inff32
#pragma define __has_builtin __builtin_inff64
#pragma define __has_builtin __builtin_inff128
#pragma define __has_builtin __builtin_inff32x
#pragma define __has_builtin __builtin_inff64x
#pragma define __has_builtin __builtin_inff128x
#pragma define __has_builtin __builtin_nanf16
#pragma define __has_builtin __builtin_nanf32
#pragma define __has_builtin __builtin_nanf64
#pragma define __has_builtin __builtin_nanf128
#pragma define __has_builtin __builtin_nanf32x
#pragma define __has_builtin __builtin_nanf64x
#pragma define __has_builtin __builtin_nanf128x
#pragma define __has_builtin __builtin_nansf16
#pragma define __has_builtin __builtin_nansf32
#pragma define __has_builtin __builtin_nansf64
#pragma define __has_builtin __builtin_nansf128
#pragma define __has_builtin __builtin_nansf32x
#pragma define __has_builtin __builtin_nansf64x
#pragma define __has_builtin __builtin_nansf128x
#pragma define __has_builtin __builtin_add_overflow_p
#pragma define __has_builtin __builtin_sub_overflow_p
#pragma define __has_builtin __builtin_mul_overflow_p
#pragma define __has_builtin __builtin_init_descriptor
#pragma define __has_builtin __builtin_adjust_descriptor
#pragma define __has_builtin __builtin_memcmp_eq
#endif /* __GCC_VERSION_NUM >= 70001 */

#if __GCC_VERSION_NUM >= 80001
#pragma undef  __has_builtin __cilkrts_enter_frame_1
#pragma undef  __has_builtin __cilkrts_enter_frame_fast_1
#pragma undef  __has_builtin __cilkrts_detach
#pragma undef  __has_builtin __cilkrts_rethrow
#pragma undef  __has_builtin __cilkrts_synched
#pragma undef  __has_builtin __cilkrts_sync
#pragma undef  __has_builtin __cilkrts_leave_frame
#pragma undef  __has_builtin __cilkrts_pop_frame
#pragma undef  __has_builtin __cilkrts_save_fp_ctrl_state
#pragma undef  __has_builtin __cilkrts_cilk_for_32
#pragma undef  __has_builtin __cilkrts_cilk_for_64
#pragma define __has_builtin __builtin_ceilf16
#pragma define __has_builtin __builtin_ceilf32
#pragma define __has_builtin __builtin_ceilf64
#pragma define __has_builtin __builtin_ceilf128
#pragma define __has_builtin __builtin_ceilf32x
#pragma define __has_builtin __builtin_ceilf64x
#pragma define __has_builtin __builtin_ceilf128x
#pragma define __has_builtin __builtin_feclearexcept
#pragma define __has_builtin __builtin_fegetenv
#pragma define __has_builtin __builtin_fegetexceptflag
#pragma define __has_builtin __builtin_fegetround
#pragma define __has_builtin __builtin_feholdexcept
#pragma define __has_builtin __builtin_feraiseexcept
#pragma define __has_builtin __builtin_fesetenv
#pragma define __has_builtin __builtin_fesetexceptflag
#pragma define __has_builtin __builtin_fesetround
#pragma define __has_builtin __builtin_fetestexcept
#pragma define __has_builtin __builtin_feupdateenv
#pragma define __has_builtin __builtin_floorf16
#pragma define __has_builtin __builtin_floorf32
#pragma define __has_builtin __builtin_floorf64
#pragma define __has_builtin __builtin_floorf128
#pragma define __has_builtin __builtin_floorf32x
#pragma define __has_builtin __builtin_floorf64x
#pragma define __has_builtin __builtin_floorf128x
#pragma define __has_builtin __builtin_fmaf16
#pragma define __has_builtin __builtin_fmaf32
#pragma define __has_builtin __builtin_fmaf64
#pragma define __has_builtin __builtin_fmaf128
#pragma define __has_builtin __builtin_fmaf32x
#pragma define __has_builtin __builtin_fmaf64x
#pragma define __has_builtin __builtin_fmaf128x
#pragma define __has_builtin __builtin_fmaxf16
#pragma define __has_builtin __builtin_fmaxf32
#pragma define __has_builtin __builtin_fmaxf64
#pragma define __has_builtin __builtin_fmaxf128
#pragma define __has_builtin __builtin_fmaxf32x
#pragma define __has_builtin __builtin_fmaxf64x
#pragma define __has_builtin __builtin_fmaxf128x
#pragma define __has_builtin __builtin_fminf16
#pragma define __has_builtin __builtin_fminf32
#pragma define __has_builtin __builtin_fminf64
#pragma define __has_builtin __builtin_fminf128
#pragma define __has_builtin __builtin_fminf32x
#pragma define __has_builtin __builtin_fminf64x
#pragma define __has_builtin __builtin_fminf128x
#pragma define __has_builtin __builtin_nearbyintf16
#pragma define __has_builtin __builtin_nearbyintf32
#pragma define __has_builtin __builtin_nearbyintf64
#pragma define __has_builtin __builtin_nearbyintf128
#pragma define __has_builtin __builtin_nearbyintf32x
#pragma define __has_builtin __builtin_nearbyintf64x
#pragma define __has_builtin __builtin_nearbyintf128x
#pragma define __has_builtin __builtin_rintf16
#pragma define __has_builtin __builtin_rintf32
#pragma define __has_builtin __builtin_rintf64
#pragma define __has_builtin __builtin_rintf128
#pragma define __has_builtin __builtin_rintf32x
#pragma define __has_builtin __builtin_rintf64x
#pragma define __has_builtin __builtin_rintf128x
#pragma define __has_builtin __builtin_roundf16
#pragma define __has_builtin __builtin_roundf32
#pragma define __has_builtin __builtin_roundf64
#pragma define __has_builtin __builtin_roundf128
#pragma define __has_builtin __builtin_roundf32x
#pragma define __has_builtin __builtin_roundf64x
#pragma define __has_builtin __builtin_roundf128x
#pragma define __has_builtin __builtin_sqrtf16
#pragma define __has_builtin __builtin_sqrtf32
#pragma define __has_builtin __builtin_sqrtf64
#pragma define __has_builtin __builtin_sqrtf128
#pragma define __has_builtin __builtin_sqrtf32x
#pragma define __has_builtin __builtin_sqrtf64x
#pragma define __has_builtin __builtin_sqrtf128x
#pragma define __has_builtin __builtin_truncf16
#pragma define __has_builtin __builtin_truncf32
#pragma define __has_builtin __builtin_truncf64
#pragma define __has_builtin __builtin_truncf128
#pragma define __has_builtin __builtin_truncf32x
#pragma define __has_builtin __builtin_truncf64x
#pragma define __has_builtin __builtin_truncf128x
#pragma define __has_builtin __builtin_alloca_with_align_and_max
#if defined(_OPENACC) || defined(_OPENMP)
#pragma define __has_builtin __builtin_omp_get_thread_num
#pragma define __has_builtin __builtin_omp_get_num_threads
#pragma define __has_builtin __builtin_omp_get_team_num
#pragma define __has_builtin __builtin_omp_get_num_teams
#pragma define __has_builtin __builtin_GOMP_atomic_start
#pragma define __has_builtin __builtin_GOMP_atomic_end
#pragma define __has_builtin __builtin_GOMP_barrier
#pragma define __has_builtin __builtin_GOMP_barrier_cancel
#pragma define __has_builtin __builtin_GOMP_taskwait
#pragma define __has_builtin __builtin_GOMP_taskyield
#pragma define __has_builtin __builtin_GOMP_taskgroup_start
#pragma define __has_builtin __builtin_GOMP_taskgroup_end
#pragma define __has_builtin __builtin_GOMP_cancel
#pragma define __has_builtin __builtin_GOMP_cancellation_point
#pragma define __has_builtin __builtin_GOMP_critical_start
#pragma define __has_builtin __builtin_GOMP_critical_end
#pragma define __has_builtin __builtin_GOMP_critical_name_start
#pragma define __has_builtin __builtin_GOMP_critical_name_end
#pragma define __has_builtin __builtin_GOMP_loop_static_start
#pragma define __has_builtin __builtin_GOMP_loop_dynamic_start
#pragma define __has_builtin __builtin_GOMP_loop_guided_start
#pragma define __has_builtin __builtin_GOMP_loop_runtime_start
#pragma define __has_builtin __builtin_GOMP_loop_nonmonotonic_dynamic_start
#pragma define __has_builtin __builtin_GOMP_loop_nonmonotonic_guided_start
#pragma define __has_builtin __builtin_GOMP_loop_ordered_static_start
#pragma define __has_builtin __builtin_GOMP_loop_ordered_dynamic_start
#pragma define __has_builtin __builtin_GOMP_loop_ordered_guided_start
#pragma define __has_builtin __builtin_GOMP_loop_ordered_runtime_start
#pragma define __has_builtin __builtin_GOMP_loop_doacross_static_start
#pragma define __has_builtin __builtin_GOMP_loop_doacross_dynamic_start
#pragma define __has_builtin __builtin_GOMP_loop_doacross_guided_start
#pragma define __has_builtin __builtin_GOMP_loop_doacross_runtime_start
#pragma define __has_builtin __builtin_GOMP_loop_static_next
#pragma define __has_builtin __builtin_GOMP_loop_dynamic_next
#pragma define __has_builtin __builtin_GOMP_loop_guided_next
#pragma define __has_builtin __builtin_GOMP_loop_runtime_next
#pragma define __has_builtin __builtin_GOMP_loop_nonmonotonic_dynamic_next
#pragma define __has_builtin __builtin_GOMP_loop_nonmonotonic_guided_next
#pragma define __has_builtin __builtin_GOMP_loop_ordered_static_next
#pragma define __has_builtin __builtin_GOMP_loop_ordered_dynamic_next
#pragma define __has_builtin __builtin_GOMP_loop_ordered_guided_next
#pragma define __has_builtin __builtin_GOMP_loop_ordered_runtime_next
#pragma define __has_builtin __builtin_GOMP_loop_ull_static_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_dynamic_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_guided_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_runtime_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_nonmonotonic_dynamic_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_nonmonotonic_guided_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_ordered_static_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_ordered_dynamic_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_ordered_guided_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_ordered_runtime_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_doacross_static_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_doacross_dynamic_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_doacross_guided_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_doacross_runtime_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_static_next
#pragma define __has_builtin __builtin_GOMP_loop_ull_dynamic_next
#pragma define __has_builtin __builtin_GOMP_loop_ull_guided_next
#pragma define __has_builtin __builtin_GOMP_loop_ull_runtime_next
#pragma define __has_builtin __builtin_GOMP_loop_ull_nonmonotonic_dynamic_next
#pragma define __has_builtin __builtin_GOMP_loop_ull_nonmonotonic_guided_next
#pragma define __has_builtin __builtin_GOMP_loop_ull_ordered_static_next
#pragma define __has_builtin __builtin_GOMP_loop_ull_ordered_dynamic_next
#pragma define __has_builtin __builtin_GOMP_loop_ull_ordered_guided_next
#pragma define __has_builtin __builtin_GOMP_loop_ull_ordered_runtime_next
#pragma define __has_builtin __builtin_GOMP_parallel_loop_static
#pragma define __has_builtin __builtin_GOMP_parallel_loop_dynamic
#pragma define __has_builtin __builtin_GOMP_parallel_loop_guided
#pragma define __has_builtin __builtin_GOMP_parallel_loop_runtime
#pragma define __has_builtin __builtin_GOMP_parallel_loop_nonmonotonic_dynamic
#pragma define __has_builtin __builtin_GOMP_parallel_loop_nonmonotonic_guided
#pragma define __has_builtin __builtin_GOMP_loop_end
#pragma define __has_builtin __builtin_GOMP_loop_end_cancel
#pragma define __has_builtin __builtin_GOMP_loop_end_nowait
#pragma define __has_builtin __builtin_GOMP_ordered_start
#pragma define __has_builtin __builtin_GOMP_ordered_end
#pragma define __has_builtin __builtin_GOMP_doacross_post
#pragma define __has_builtin __builtin_GOMP_doacross_wait
#pragma define __has_builtin __builtin_GOMP_doacross_ull_post
#pragma define __has_builtin __builtin_GOMP_doacross_ull_wait
#pragma define __has_builtin __builtin_GOMP_parallel
#pragma define __has_builtin __builtin_GOMP_task
#pragma define __has_builtin __builtin_GOMP_taskloop
#pragma define __has_builtin __builtin_GOMP_taskloop_ull
#pragma define __has_builtin __builtin_GOMP_sections_start
#pragma define __has_builtin __builtin_GOMP_sections_next
#pragma define __has_builtin __builtin_GOMP_parallel_sections
#pragma define __has_builtin __builtin_GOMP_sections_end
#pragma define __has_builtin __builtin_GOMP_sections_end_cancel
#pragma define __has_builtin __builtin_GOMP_sections_end_nowait
#pragma define __has_builtin __builtin_GOMP_single_start
#pragma define __has_builtin __builtin_GOMP_single_copy_start
#pragma define __has_builtin __builtin_GOMP_single_copy_end
#pragma define __has_builtin __builtin_GOMP_offload_register_ver
#pragma define __has_builtin __builtin_GOMP_offload_unregister_ver
#pragma define __has_builtin __builtin_GOMP_target_ext
#pragma define __has_builtin __builtin_GOMP_target_data_ext
#pragma define __has_builtin __builtin_GOMP_target_end_data
#pragma define __has_builtin __builtin_GOMP_target_update_ext
#pragma define __has_builtin __builtin_GOMP_target_enter_exit_data
#pragma define __has_builtin __builtin_GOMP_teams
#endif /* defined(_OPENACC) || defined(_OPENMP) */
#endif /* __GCC_VERSION_NUM >= 80001 */

#if __GCC_VERSION_NUM >= 90001
#pragma undef  __has_builtin __chkp_intersect
#pragma undef  __has_builtin __chkp_sizeof
#pragma undef  __has_builtin __chkp_narrow
#pragma undef  __has_builtin __builtin___chkp_bndcl
#pragma undef  __has_builtin __builtin___chkp_bndcu
#pragma undef  __has_builtin __builtin___chkp_bndstx
#pragma undef  __has_builtin __builtin___chkp_bndldx
#pragma undef  __has_builtin __builtin___chkp_bndret
#pragma undef  __has_builtin __builtin___chkp_bndmk
#pragma undef  __has_builtin __builtin___chkp_extract_lower
#pragma undef  __has_builtin __builtin___chkp_extract_upper
#pragma undef  __has_builtin __builtin___bnd_set_ptr_bounds
#pragma undef  __has_builtin __builtin___bnd_init_ptr_bounds
#pragma undef  __has_builtin __builtin___bnd_null_ptr_bounds
#pragma undef  __has_builtin __builtin___bnd_copy_ptr_bounds
#pragma undef  __has_builtin __builtin___bnd_narrow_ptr_bounds
#pragma undef  __has_builtin __builtin___bnd_store_ptr_bounds
#pragma undef  __has_builtin __builtin___bnd_chk_ptr_lbounds
#pragma undef  __has_builtin __builtin___bnd_chk_ptr_ubounds
#pragma undef  __has_builtin __builtin___bnd_chk_ptr_bounds
#pragma undef  __has_builtin __builtin___bnd_get_ptr_lbound
#pragma undef  __has_builtin __builtin___bnd_get_ptr_ubound
#pragma undef  __has_builtin __builtin_chkp_memcpy_nobnd
#pragma undef  __has_builtin __builtin_chkp_memcpy_nochk
#pragma undef  __has_builtin __builtin_chkp_memcpy_nobnd_nochk
#pragma undef  __has_builtin __builtin_chkp_memmove_nobnd
#pragma undef  __has_builtin __builtin_chkp_memmove_nochk
#pragma undef  __has_builtin __builtin_chkp_memmove_nobnd_nochk
#pragma undef  __has_builtin __builtin_chkp_mempcpy_nobnd
#pragma undef  __has_builtin __builtin_chkp_mempcpy_nochk
#pragma undef  __has_builtin __builtin_chkp_mempcpy_nobnd_nochk
#pragma undef  __has_builtin __builtin_chkp_memset_nobnd
#pragma undef  __has_builtin __builtin_chkp_memset_nochk
#pragma undef  __has_builtin __builtin_chkp_memset_nobnd_nochk
#pragma define __has_builtin __builtin_strnlen
#pragma define __has_builtin __builtin_expect_with_probability
#pragma define __has_builtin __builtin_strcmp_eq
#pragma define __has_builtin __builtin_strncmp_eq
#pragma define __has_builtin __builtin_speculation_safe_value
#pragma define __has_builtin __builtin_speculation_safe_value_ptr
#pragma define __has_builtin __builtin_speculation_safe_value_1
#pragma define __has_builtin __builtin_speculation_safe_value_2
#pragma define __has_builtin __builtin_speculation_safe_value_4
#pragma define __has_builtin __builtin_speculation_safe_value_8
#pragma define __has_builtin __builtin_speculation_safe_value_16
#ifdef _OPENACC
#pragma define __has_builtin __builtin_goacc_parlevel_id
#pragma define __has_builtin __builtin_goacc_parlevel_size
#endif /* _OPENACC */
#if defined(_OPENACC) || defined(_OPENMP)
#pragma define __has_builtin __builtin_GOMP_taskwait_depend
#pragma define __has_builtin __builtin_GOMP_loop_nonmonotonic_runtime_start
#pragma define __has_builtin __builtin_GOMP_loop_maybe_nonmonotonic_runtime_start
#pragma define __has_builtin __builtin_GOMP_loop_start
#pragma define __has_builtin __builtin_GOMP_loop_ordered_start
#pragma define __has_builtin __builtin_GOMP_loop_doacross_start
#pragma define __has_builtin __builtin_GOMP_loop_nonmonotonic_runtime_next
#pragma define __has_builtin __builtin_GOMP_loop_maybe_nonmonotonic_runtime_next
#pragma define __has_builtin __builtin_GOMP_loop_ull_nonmonotonic_runtime_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_maybe_nonmonotonic_runtime_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_ordered_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_doacross_start
#pragma define __has_builtin __builtin_GOMP_loop_ull_nonmonotonic_runtime_next
#pragma define __has_builtin __builtin_GOMP_loop_ull_maybe_nonmonotonic_runtime_next
#pragma define __has_builtin __builtin_GOMP_parallel_loop_nonmonotonic_runtime
#pragma define __has_builtin __builtin_GOMP_parallel_loop_maybe_nonmonotonic_runtime
#pragma define __has_builtin __builtin_GOMP_parallel_reductions
#pragma define __has_builtin __builtin_GOMP_sections2_start
#pragma define __has_builtin __builtin_GOMP_teams_reg
#pragma define __has_builtin __builtin_GOMP_taskgroup_reduction_register
#pragma define __has_builtin __builtin_GOMP_taskgroup_reduction_unregister
#pragma define __has_builtin __builtin_GOMP_task_reduction_remap
#pragma define __has_builtin __builtin_GOMP_workshare_task_reduction_unregister
#endif /* defined(_OPENACC) || defined(_OPENMP) */
#endif /* __GCC_VERSION_NUM >= 90001 */
