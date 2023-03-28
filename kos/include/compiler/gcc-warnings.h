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

#ifndef __has_GCC_warning
#define __has_GCC_warning(x) __GCC_PRIVATE_W_IS_DEFINED(__GCC_HAS_WARNING_##x)
#define __GCC_PRIVATE_W_ARG_PLACEHOLDER__S(x) ,
#define __GCC_PRIVATE_W_ARG_PLACEHOLDER__X(x) ,
#define __GCC_PRIVATE_W_TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define __GCC_PRIVATE_W_TAKE_SECOND_ARG(x) __GCC_PRIVATE_W_TAKE_SECOND_ARG_IMPL x
#define __GCC_PRIVATE_W_IS_DEFINED3(x) __GCC_PRIVATE_W_TAKE_SECOND_ARG((x 1, 0))
#define __GCC_PRIVATE_W_IS_DEFINED2(x) __GCC_PRIVATE_W_IS_DEFINED3(__GCC_PRIVATE_W_ARG_PLACEHOLDER_##x)
#define __GCC_PRIVATE_W_IS_DEFINED(x) __GCC_PRIVATE_W_IS_DEFINED2(x)
#ifndef __GNUC_MINOR__
#define __GNUC_MINOR__ 0
#endif /* !__GNUC_MINOR__ */
#ifndef __GNUC_PATCH__
#ifdef __GNUC_PATCHLEVEL__
#define __GNUC_PATCH__ __GNUC_PATCHLEVEL__
#else /* __GNUC_PATCHLEVEL__ */
#define __GNUC_PATCH__ 0
#endif /* !__GNUC_PATCHLEVEL__ */
#endif /* !__GNUC_PATCH__ */
#ifndef __GCC_VERSION_NUM
#define __GCC_VERSION_NUM (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCH__)
#endif /* !__GCC_VERSION_NUM */
#define __PRIVATE_pragma_GCC_diagnostic_ignored_1__S(text)   __pragma(GCC diagnostic ignored text)
#define __PRIVATE_pragma_GCC_diagnostic_ignored_1__X(text)   __pragma(GCC diagnostic ignored text)
#define __PRIVATE_pragma_GCC_diagnostic_ignored_1(decl)      __PRIVATE_pragma_GCC_diagnostic_ignored_1_##decl
#define __PRIVATE_pragma_GCC_diagnostic_push_ignored_1(decl) __pragma_GCC_diagnostic_push __PRIVATE_pragma_GCC_diagnostic_ignored_1_##decl
#define __PRIVATE_pragma_GCC_diagnostic_pop_ignored_1(decl)  __pragma_GCC_diagnostic_pop
#define __PRIVATE_pragma_GCC_diagnostic_ignored_0(decl)           /* nothing */
#define __PRIVATE_pragma_GCC_diagnostic_push_ignored_0(decl)      /* nothing */
#define __PRIVATE_pragma_GCC_diagnostic_pop_ignored_0(decl)       /* nothing */
#define __PRIVATE_pragma_GCC_diagnostic_ignored_(cond, decl)      __PRIVATE_pragma_GCC_diagnostic_ignored_##cond(decl)
#define __PRIVATE_pragma_GCC_diagnostic_push_ignored_(cond, decl) __PRIVATE_pragma_GCC_diagnostic_push_ignored_##cond(decl)
#define __PRIVATE_pragma_GCC_diagnostic_pop_ignored_(cond, decl)  __PRIVATE_pragma_GCC_diagnostic_pop_ignored_##cond(decl)
#define __PRIVATE_pragma_GCC_diagnostic_ignored(cond, decl)       __PRIVATE_pragma_GCC_diagnostic_ignored_(cond, decl)
#define __PRIVATE_pragma_GCC_diagnostic_push_ignored(cond, decl)  __PRIVATE_pragma_GCC_diagnostic_push_ignored_(cond, decl)
#define __PRIVATE_pragma_GCC_diagnostic_pop_ignored(cond, decl)   __PRIVATE_pragma_GCC_diagnostic_pop_ignored_(cond, decl)
#define __pragma_GCC_diagnostic_push               _Pragma("GCC diagnostic push")
#define __pragma_GCC_diagnostic_pop                _Pragma("GCC diagnostic pop")
#define __pragma_GCC_diagnostic_ignored(name)      __PRIVATE_pragma_GCC_diagnostic_ignored(__GCC_PRIVATE_W_IS_DEFINED(__GCC_HAS_WARNING_##name), __GCC_HAS_WARNING_##name)
#define __pragma_GCC_diagnostic_push_ignored(name) __PRIVATE_pragma_GCC_diagnostic_push_ignored(__GCC_PRIVATE_W_IS_DEFINED(__GCC_HAS_WARNING_##name), __GCC_HAS_WARNING_##name)
#define __pragma_GCC_diagnostic_pop_ignored(name)  __PRIVATE_pragma_GCC_diagnostic_pop_ignored(__GCC_PRIVATE_W_IS_DEFINED(__GCC_HAS_WARNING_##name), __GCC_HAS_WARNING_##name)

#if __GCC_VERSION_NUM >= 30400
#define __GCC_HAS_WARNING_W _S("-W")
#define __GCC_HAS_WARNING_Wabi _S("-Wabi")
#define __GCC_HAS_WARNING_Waggregate_return _S("-Waggregate-return")
#define __GCC_HAS_WARNING_Wall _S("-Wall")
#define __GCC_HAS_WARNING_Wbad_function_cast _S("-Wbad-function-cast")
#define __GCC_HAS_WARNING_Wcast_align _S("-Wcast-align")
#define __GCC_HAS_WARNING_Wcast_qual _S("-Wcast-qual")
#define __GCC_HAS_WARNING_Wchar_subscripts _S("-Wchar-subscripts")
#define __GCC_HAS_WARNING_Wcomment _S("-Wcomment")
#define __GCC_HAS_WARNING_Wcomments _S("-Wcomments")
#define __GCC_HAS_WARNING_Wconversion _S("-Wconversion")
#define __GCC_HAS_WARNING_Wctor_dtor_privacy _S("-Wctor-dtor-privacy")
#define __GCC_HAS_WARNING_Wdeclaration_after_statement _S("-Wdeclaration-after-statement")
#define __GCC_HAS_WARNING_Wdeprecated _S("-Wdeprecated")
#define __GCC_HAS_WARNING_Wdeprecated_declarations _S("-Wdeprecated-declarations")
#define __GCC_HAS_WARNING_Wdisabled_optimization _S("-Wdisabled-optimization")
#define __GCC_HAS_WARNING_Wdiv_by_zero _S("-Wdiv-by-zero")
#define __GCC_HAS_WARNING_Weffcxx _S("-Weffc++")
#define __GCC_HAS_WARNING_Wendif_labels _S("-Wendif-labels")
#define __GCC_HAS_WARNING_Werror _S("-Werror")
#define __GCC_HAS_WARNING_Werror_implicit_function_declaration _S("-Werror-implicit-function-declaration")
#define __GCC_HAS_WARNING_Wextra _S("-Wextra")
#define __GCC_HAS_WARNING_Wfloat_equal _S("-Wfloat-equal")
#define __GCC_HAS_WARNING_Wformat _S("-Wformat")
#define __GCC_HAS_WARNING_Wformat_extra_args _S("-Wformat-extra-args")
#define __GCC_HAS_WARNING_Wformat_nonliteral _S("-Wformat-nonliteral")
#define __GCC_HAS_WARNING_Wformat_security _S("-Wformat-security")
#define __GCC_HAS_WARNING_Wformat_y2k _S("-Wformat-y2k")
#define __GCC_HAS_WARNING_Wformat_zero_length _S("-Wformat-zero-length")
#define __GCC_HAS_WARNING_Wimplicit _S("-Wimplicit")
#define __GCC_HAS_WARNING_Wimplicit_function_declaration _S("-Wimplicit-function-declaration")
#define __GCC_HAS_WARNING_Wimplicit_int _S("-Wimplicit-int")
#define __GCC_HAS_WARNING_Wimport _S("-Wimport")
#define __GCC_HAS_WARNING_Winit_self _S("-Winit-self")
#define __GCC_HAS_WARNING_Winline _S("-Winline")
#define __GCC_HAS_WARNING_Winvalid_offsetof _S("-Winvalid-offsetof")
#define __GCC_HAS_WARNING_Winvalid_pch _S("-Winvalid-pch")
#define __GCC_HAS_WARNING_Wlarger_than_ _S("-Wlarger-than-")
#define __GCC_HAS_WARNING_Wlong_long _S("-Wlong-long")
#define __GCC_HAS_WARNING_Wmain _S("-Wmain")
#define __GCC_HAS_WARNING_Wmissing_braces _S("-Wmissing-braces")
#define __GCC_HAS_WARNING_Wmissing_declarations _S("-Wmissing-declarations")
#define __GCC_HAS_WARNING_Wmissing_format_attribute _S("-Wmissing-format-attribute")
#define __GCC_HAS_WARNING_Wmissing_noreturn _S("-Wmissing-noreturn")
#define __GCC_HAS_WARNING_Wmissing_prototypes _S("-Wmissing-prototypes")
#define __GCC_HAS_WARNING_Wmultichar _S("-Wmultichar")
#define __GCC_HAS_WARNING_Wnested_externs _S("-Wnested-externs")
#define __GCC_HAS_WARNING_Wnon_template_friend _S("-Wnon-template-friend")
#define __GCC_HAS_WARNING_Wnon_virtual_dtor _S("-Wnon-virtual-dtor")
#define __GCC_HAS_WARNING_Wnonnull _S("-Wnonnull")
#define __GCC_HAS_WARNING_Wold_style_cast _S("-Wold-style-cast")
#define __GCC_HAS_WARNING_Wold_style_definition _S("-Wold-style-definition")
#define __GCC_HAS_WARNING_Woverloaded_virtual _S("-Woverloaded-virtual")
#define __GCC_HAS_WARNING_Wpacked _S("-Wpacked")
#define __GCC_HAS_WARNING_Wpadded _S("-Wpadded")
#define __GCC_HAS_WARNING_Wparentheses _S("-Wparentheses")
#define __GCC_HAS_WARNING_Wpmf_conversions _S("-Wpmf-conversions")
#define __GCC_HAS_WARNING_Wpointer_arith _S("-Wpointer-arith")
#define __GCC_HAS_WARNING_Wprotocol _S("-Wprotocol")
#define __GCC_HAS_WARNING_Wredundant_decls _S("-Wredundant-decls")
#define __GCC_HAS_WARNING_Wreorder _S("-Wreorder")
#define __GCC_HAS_WARNING_Wreturn_type _S("-Wreturn-type")
#define __GCC_HAS_WARNING_Wselector _S("-Wselector")
#define __GCC_HAS_WARNING_Wsequence_point _S("-Wsequence-point")
#define __GCC_HAS_WARNING_Wshadow _S("-Wshadow")
#define __GCC_HAS_WARNING_Wsign_compare _S("-Wsign-compare")
#define __GCC_HAS_WARNING_Wsign_promo _S("-Wsign-promo")
#define __GCC_HAS_WARNING_Wstrict_aliasing _S("-Wstrict-aliasing")
#define __GCC_HAS_WARNING_Wstrict_prototypes _S("-Wstrict-prototypes")
#define __GCC_HAS_WARNING_Wswitch _S("-Wswitch")
#define __GCC_HAS_WARNING_Wswitch_default _S("-Wswitch-default")
#define __GCC_HAS_WARNING_Wswitch_enum _S("-Wswitch-enum")
#define __GCC_HAS_WARNING_Wsynth _S("-Wsynth")
#define __GCC_HAS_WARNING_Wsystem_headers _S("-Wsystem-headers")
#define __GCC_HAS_WARNING_Wtraditional _S("-Wtraditional")
#define __GCC_HAS_WARNING_Wtrigraphs _S("-Wtrigraphs")
#define __GCC_HAS_WARNING_Wundeclared_selector _S("-Wundeclared-selector")
#define __GCC_HAS_WARNING_Wundef _S("-Wundef")
#define __GCC_HAS_WARNING_Wuninitialized _S("-Wuninitialized")
#define __GCC_HAS_WARNING_Wunknown_pragmas _S("-Wunknown-pragmas")
#define __GCC_HAS_WARNING_Wunreachable_code _S("-Wunreachable-code")
#define __GCC_HAS_WARNING_Wunused _S("-Wunused")
#define __GCC_HAS_WARNING_Wunused_function _S("-Wunused-function")
#define __GCC_HAS_WARNING_Wunused_label _S("-Wunused-label")
#define __GCC_HAS_WARNING_Wunused_macros _S("-Wunused-macros")
#define __GCC_HAS_WARNING_Wunused_parameter _S("-Wunused-parameter")
#define __GCC_HAS_WARNING_Wunused_value _S("-Wunused-value")
#define __GCC_HAS_WARNING_Wunused_variable _S("-Wunused-variable")
#define __GCC_HAS_WARNING_Wwrite_strings _S("-Wwrite-strings")
#endif /* __GCC_VERSION_NUM >= 30400 */

#if __GCC_VERSION_NUM >= 40000
#define __GCC_HAS_WARNING_Wfatal_errors _S("-Wfatal-errors")
#define __GCC_HAS_WARNING_Wmissing_field_initializers _S("-Wmissing-field-initializers")
#define __GCC_HAS_WARNING_Wmissing_include_dirs _S("-Wmissing-include-dirs")
#define __GCC_HAS_WARNING_Wvariadic_macros _S("-Wvariadic-macros")
#endif /* __GCC_VERSION_NUM >= 40000 */

#if __GCC_VERSION_NUM >= 40100
#define __GCC_HAS_WARNING_Wnormalized _X("-Wnormalized=")
#define __GCC_HAS_WARNING_Wpointer_sign _S("-Wpointer-sign")
#endif /* __GCC_VERSION_NUM >= 40100 */

#if __GCC_VERSION_NUM >= 40200
#define __GCC_HAS_WARNING_Wassign_intercept _S("-Wassign-intercept")
#define __GCC_HAS_WARNING_Wattributes _S("-Wattributes")
#define __GCC_HAS_WARNING_Wcxx_compat _S("-Wc++-compat")
#define __GCC_HAS_WARNING_Wint_to_pointer_cast _S("-Wint-to-pointer-cast")
#define __GCC_HAS_WARNING_Wpointer_to_int_cast _S("-Wpointer-to-int-cast")
#define __GCC_HAS_WARNING_Wpragmas _S("-Wpragmas")
#define __GCC_HAS_WARNING_Wstack_protector _S("-Wstack-protector")
#define __GCC_HAS_WARNING_Wstrict_null_sentinel _S("-Wstrict-null-sentinel")
#define __GCC_HAS_WARNING_Wstrict_selector_match _S("-Wstrict-selector-match")
#define __GCC_HAS_WARNING_Wunsafe_loop_optimizations _S("-Wunsafe-loop-optimizations")
#define __GCC_HAS_WARNING_Wvolatile_register_var _S("-Wvolatile-register-var")
#endif /* __GCC_VERSION_NUM >= 40200 */

#if __GCC_VERSION_NUM >= 40300
#define __GCC_HAS_WARNING_Walways_true _S("-Walways-true")
#define __GCC_HAS_WARNING_Woverflow _S("-Woverflow")
#define __GCC_HAS_WARNING_Woverlength_strings _S("-Woverlength-strings")
#define __GCC_HAS_WARNING_Woverride_init _S("-Woverride-init")
#define __GCC_HAS_WARNING_Wstring_literal_comparison _S("-Wstring-literal-comparison")
#endif /* __GCC_VERSION_NUM >= 40300 */

#if __GCC_VERSION_NUM >= 40400
#undef __GCC_HAS_WARNING_Walways_true
#undef __GCC_HAS_WARNING_Wstring_literal_comparison
#define __GCC_HAS_WARNING_Waddress _S("-Waddress")
#define __GCC_HAS_WARNING_Warray_bounds _S("-Warray-bounds")
#define __GCC_HAS_WARNING_Wclobbered _S("-Wclobbered")
#define __GCC_HAS_WARNING_Wcoverage_mismatch _S("-Wcoverage-mismatch")
#define __GCC_HAS_WARNING_Wcxx0x_compat _S("-Wc++0x-compat")
#define __GCC_HAS_WARNING_Wempty_body _S("-Wempty-body")
#define __GCC_HAS_WARNING_Wformat_contains_nul _S("-Wformat-contains-nul")
#define __GCC_HAS_WARNING_Wignored_qualifiers _S("-Wignored-qualifiers")
#define __GCC_HAS_WARNING_Wlogical_op _S("-Wlogical-op")
#define __GCC_HAS_WARNING_Wmissing_parameter_type _S("-Wmissing-parameter-type")
#define __GCC_HAS_WARNING_Wold_style_declaration _S("-Wold-style-declaration")
#define __GCC_HAS_WARNING_Wsign_conversion _S("-Wsign-conversion")
#define __GCC_HAS_WARNING_Wstrict_overflow _S("-Wstrict-overflow")
#define __GCC_HAS_WARNING_Wtraditional_conversion _S("-Wtraditional-conversion")
#define __GCC_HAS_WARNING_Wtype_limits _S("-Wtype-limits")
#define __GCC_HAS_WARNING_Wvla _S("-Wvla")
#endif /* __GCC_VERSION_NUM >= 40400 */

#if __GCC_VERSION_NUM >= 40500
#define __GCC_HAS_WARNING_Wbuiltin_macro_redefined _S("-Wbuiltin-macro-redefined")
#define __GCC_HAS_WARNING_Wdisallowed_function_list _X("-Wdisallowed-function-list=")
#define __GCC_HAS_WARNING_Wenum_compare _S("-Wenum-compare")
#define __GCC_HAS_WARNING_Wframe_larger_than _X("-Wframe-larger-than=")
#define __GCC_HAS_WARNING_Wlarger_than _X("-Wlarger-than=")
#define __GCC_HAS_WARNING_Wmudflap _S("-Wmudflap")
#define __GCC_HAS_WARNING_Wpacked_bitfield_compat _S("-Wpacked-bitfield-compat")
#define __GCC_HAS_WARNING_Wpsabi _S("-Wpsabi")
#define __GCC_HAS_WARNING_Wsync_nand _S("-Wsync-nand")
#endif /* __GCC_VERSION_NUM >= 40500 */

#if __GCC_VERSION_NUM >= 40600
#undef __GCC_HAS_WARNING_Wdisallowed_function_list
#define __GCC_HAS_WARNING_Wconversion_null _S("-Wconversion-null")
#define __GCC_HAS_WARNING_Wjump_misses_init _S("-Wjump-misses-init")
#define __GCC_HAS_WARNING_Wunsuffixed_float_constants _S("-Wunsuffixed-float-constants")
#define __GCC_HAS_WARNING_Wunused_result _S("-Wunused-result")
#endif /* __GCC_VERSION_NUM >= 40600 */

#if __GCC_VERSION_NUM >= 40700
#undef __GCC_HAS_WARNING_Werror
#undef __GCC_HAS_WARNING_Wfatal_errors
#undef __GCC_HAS_WARNING_Wframe_larger_than
#undef __GCC_HAS_WARNING_Wimport
#undef __GCC_HAS_WARNING_Wpsabi
#undef __GCC_HAS_WARNING_Wsign_conversion
#undef __GCC_HAS_WARNING_Wunreachable_code
#define __GCC_HAS_WARNING_Wcpp _S("-Wcpp")
#define __GCC_HAS_WARNING_Wdouble_promotion _S("-Wdouble-promotion")
#define __GCC_HAS_WARNING_Wnoexcept _S("-Wnoexcept")
#define __GCC_HAS_WARNING_Wproperty_assign_default _S("-Wproperty-assign-default")
#define __GCC_HAS_WARNING_Wsuggest_attribute_const _S("-Wsuggest-attribute=const")
#define __GCC_HAS_WARNING_Wsuggest_attribute_noreturn _S("-Wsuggest-attribute=noreturn")
#define __GCC_HAS_WARNING_Wsuggest_attribute_pure _S("-Wsuggest-attribute=pure")
#define __GCC_HAS_WARNING_Wtrampolines _S("-Wtrampolines")
#define __GCC_HAS_WARNING_Wunused_but_set_parameter _S("-Wunused-but-set-parameter")
#define __GCC_HAS_WARNING_Wunused_but_set_variable _S("-Wunused-but-set-variable")
#endif /* __GCC_VERSION_NUM >= 40700 */

#if __GCC_VERSION_NUM >= 40800
#define __GCC_HAS_WARNING_Wcxx11_compat _S("-Wc++11-compat")
#define __GCC_HAS_WARNING_Wdelete_non_virtual_dtor _S("-Wdelete-non-virtual-dtor")
#define __GCC_HAS_WARNING_Wfree_nonheap_object _S("-Wfree-nonheap-object")
#define __GCC_HAS_WARNING_Winvalid_memory_model _S("-Winvalid-memory-model")
#define __GCC_HAS_WARNING_Wmaybe_uninitialized _S("-Wmaybe-uninitialized")
#define __GCC_HAS_WARNING_Wnarrowing _S("-Wnarrowing")
#define __GCC_HAS_WARNING_Wstack_usage _X("-Wstack-usage=")
#define __GCC_HAS_WARNING_Wunused_local_typedefs _S("-Wunused-local-typedefs")
#define __GCC_HAS_WARNING_Wvector_operation_performance _S("-Wvector-operation-performance")
#define __GCC_HAS_WARNING_Wzero_as_null_pointer_constant _S("-Wzero-as-null-pointer-constant")
#endif /* __GCC_VERSION_NUM >= 40800 */

#if __GCC_VERSION_NUM >= 40900
#undef __GCC_HAS_WARNING_Wmissing_format_attribute
#undef __GCC_HAS_WARNING_Wmissing_noreturn
#define __GCC_HAS_WARNING_Wabi_tag _S("-Wabi-tag")
#define __GCC_HAS_WARNING_Waggressive_loop_optimizations _S("-Waggressive-loop-optimizations")
#define __GCC_HAS_WARNING_Winherited_variadic_ctor _S("-Winherited-variadic-ctor")
#define __GCC_HAS_WARNING_Wliteral_suffix _S("-Wliteral-suffix")
#define __GCC_HAS_WARNING_Wpedantic _S("-Wpedantic")
#define __GCC_HAS_WARNING_Wreturn_local_addr _S("-Wreturn-local-addr")
#define __GCC_HAS_WARNING_Wsizeof_pointer_memaccess _S("-Wsizeof-pointer-memaccess")
#define __GCC_HAS_WARNING_Wsuggest_attribute_format _S("-Wsuggest-attribute=format")
#define __GCC_HAS_WARNING_Wuseless_cast _S("-Wuseless-cast")
#define __GCC_HAS_WARNING_Wvarargs _S("-Wvarargs")
#define __GCC_HAS_WARNING_Wvirtual_move_assign _S("-Wvirtual-move-assign")
#endif /* __GCC_VERSION_NUM >= 40900 */

#if __GCC_VERSION_NUM >= 41000
#undef __GCC_HAS_WARNING_Wmudflap
#define __GCC_HAS_WARNING_Wconditionally_supported _S("-Wconditionally-supported")
#define __GCC_HAS_WARNING_Wdate_time _S("-Wdate-time")
#define __GCC_HAS_WARNING_Wdelete_incomplete _S("-Wdelete-incomplete")
#define __GCC_HAS_WARNING_Wopenmp_simd _S("-Wopenmp-simd")
#endif /* __GCC_VERSION_NUM >= 41000 */

#if __GCC_VERSION_NUM >= 50000
#define __GCC_HAS_WARNING_Wc90_c99_compat _S("-Wc90-c99-compat")
#define __GCC_HAS_WARNING_Wdesignated_init _S("-Wdesignated-init")
#define __GCC_HAS_WARNING_Wdiscarded_qualifiers _S("-Wdiscarded-qualifiers")
#define __GCC_HAS_WARNING_Wformat_signedness _S("-Wformat-signedness")
#define __GCC_HAS_WARNING_Wincompatible_pointer_types _S("-Wincompatible-pointer-types")
#define __GCC_HAS_WARNING_Wint_conversion _S("-Wint-conversion")
#define __GCC_HAS_WARNING_Wlogical_not_parentheses _S("-Wlogical-not-parentheses")
#define __GCC_HAS_WARNING_Wmemset_transposed_args _S("-Wmemset-transposed-args")
#define __GCC_HAS_WARNING_Wodr _S("-Wodr")
#define __GCC_HAS_WARNING_Wshadow_ivar _S("-Wshadow-ivar")
#define __GCC_HAS_WARNING_Wsizeof_array_argument _S("-Wsizeof-array-argument")
#define __GCC_HAS_WARNING_Wsuggest_final_methods _S("-Wsuggest-final-methods")
#define __GCC_HAS_WARNING_Wsuggest_final_types _S("-Wsuggest-final-types")
#define __GCC_HAS_WARNING_Wswitch_bool _S("-Wswitch-bool")
#endif /* __GCC_VERSION_NUM >= 50000 */

#if __GCC_VERSION_NUM >= 60000
#define __GCC_HAS_WARNING_Wbool_compare _S("-Wbool-compare")
#define __GCC_HAS_WARNING_Wc99_c11_compat _S("-Wc99-c11-compat")
#define __GCC_HAS_WARNING_Wchkp _S("-Wchkp")
#define __GCC_HAS_WARNING_Wcxx14_compat _S("-Wc++14-compat")
#define __GCC_HAS_WARNING_Wdiscarded_array_qualifiers _S("-Wdiscarded-array-qualifiers")
#define __GCC_HAS_WARNING_Wshift_count_negative _S("-Wshift-count-negative")
#define __GCC_HAS_WARNING_Wshift_count_overflow _S("-Wshift-count-overflow")
#define __GCC_HAS_WARNING_Wsized_deallocation _S("-Wsized-deallocation")
#define __GCC_HAS_WARNING_Wsuggest_override _S("-Wsuggest-override")
#endif /* __GCC_VERSION_NUM >= 60000 */

#if __GCC_VERSION_NUM >= 70000
#define __GCC_HAS_WARNING_Wduplicated_cond _S("-Wduplicated-cond")
#define __GCC_HAS_WARNING_Wfloat_conversion _S("-Wfloat-conversion")
#define __GCC_HAS_WARNING_Wframe_address _S("-Wframe-address")
#define __GCC_HAS_WARNING_Wframe_larger_than _X("-Wframe-larger-than=")
#define __GCC_HAS_WARNING_Whsa _S("-Whsa")
#define __GCC_HAS_WARNING_Wignored_attributes _S("-Wignored-attributes")
#define __GCC_HAS_WARNING_Wlto_type_mismatch _S("-Wlto-type-mismatch")
#define __GCC_HAS_WARNING_Wmisleading_indentation _S("-Wmisleading-indentation")
#define __GCC_HAS_WARNING_Wmissing_format_attribute _S("-Wmissing-format-attribute")
#define __GCC_HAS_WARNING_Wmissing_noreturn _S("-Wmissing-noreturn")
#define __GCC_HAS_WARNING_Wmultiple_inheritance _S("-Wmultiple-inheritance")
#define __GCC_HAS_WARNING_Wnamespaces _S("-Wnamespaces")
#define __GCC_HAS_WARNING_Wnonnull_compare _S("-Wnonnull-compare")
#define __GCC_HAS_WARNING_Wnull_dereference _S("-Wnull-dereference")
#define __GCC_HAS_WARNING_Woverride_init_side_effects _S("-Woverride-init-side-effects")
#define __GCC_HAS_WARNING_Wplacement_new _S("-Wplacement-new")
#define __GCC_HAS_WARNING_Wscalar_storage_order _S("-Wscalar-storage-order")
#define __GCC_HAS_WARNING_Wshift_negative_value _S("-Wshift-negative-value")
#define __GCC_HAS_WARNING_Wshift_overflow _S("-Wshift-overflow")
#define __GCC_HAS_WARNING_Wsign_conversion _S("-Wsign-conversion")
#define __GCC_HAS_WARNING_Wsubobject_linkage _S("-Wsubobject-linkage")
#define __GCC_HAS_WARNING_Wtautological_compare _S("-Wtautological-compare")
#define __GCC_HAS_WARNING_Wtemplates _S("-Wtemplates")
#define __GCC_HAS_WARNING_Wterminate _S("-Wterminate")
#define __GCC_HAS_WARNING_Wunreachable_code _S("-Wunreachable-code")
#define __GCC_HAS_WARNING_Wunused_const_variable _S("-Wunused-const-variable")
#define __GCC_HAS_WARNING_Wvirtual_inheritance _S("-Wvirtual-inheritance")
#endif /* __GCC_VERSION_NUM >= 70000 */

#if __GCC_VERSION_NUM >= 70001
#define __GCC_HAS_WARNING_Waligned_new _X("-Waligned-new=")
#define __GCC_HAS_WARNING_Walloc_size_larger_than _X("-Walloc-size-larger-than=")
#define __GCC_HAS_WARNING_Walloc_zero _S("-Walloc-zero")
#define __GCC_HAS_WARNING_Walloca _S("-Walloca")
#define __GCC_HAS_WARNING_Walloca_larger_than _X("-Walloca-larger-than=")
#define __GCC_HAS_WARNING_Wbool_operation _S("-Wbool-operation")
#define __GCC_HAS_WARNING_Wbuiltin_declaration_mismatch _S("-Wbuiltin-declaration-mismatch")
#define __GCC_HAS_WARNING_Wcxx17_compat _S("-Wc++17-compat")
#define __GCC_HAS_WARNING_Wcxx1z_compat _S("-Wc++1z-compat")
#define __GCC_HAS_WARNING_Wdangling_else _S("-Wdangling-else")
#define __GCC_HAS_WARNING_Wduplicate_decl_specifier _S("-Wduplicate-decl-specifier")
#define __GCC_HAS_WARNING_Wduplicated_branches _S("-Wduplicated-branches")
#define __GCC_HAS_WARNING_Wexpansion_to_defined _S("-Wexpansion-to-defined")
#define __GCC_HAS_WARNING_Wformat_overflow _S("-Wformat-overflow")
#define __GCC_HAS_WARNING_Wformat_truncation _S("-Wformat-truncation")
#define __GCC_HAS_WARNING_Wimplicit_fallthrough _S("-Wimplicit-fallthrough")
#define __GCC_HAS_WARNING_Wint_in_bool_context _S("-Wint-in-bool-context")
#define __GCC_HAS_WARNING_Wmemset_elt_size _S("-Wmemset-elt-size")
#define __GCC_HAS_WARNING_Wpointer_compare _S("-Wpointer-compare")
#define __GCC_HAS_WARNING_Wpsabi _S("-Wpsabi")
#define __GCC_HAS_WARNING_Wregister _S("-Wregister")
#define __GCC_HAS_WARNING_Wrestrict _S("-Wrestrict")
#define __GCC_HAS_WARNING_Wshadow_compatible_local _S("-Wshadow-compatible-local")
#define __GCC_HAS_WARNING_Wshadow_global _S("-Wshadow=global")
#define __GCC_HAS_WARNING_Wshadow_local _S("-Wshadow-local")
#define __GCC_HAS_WARNING_Wstringop_overflow _S("-Wstringop-overflow")
#define __GCC_HAS_WARNING_Wswitch_unreachable _S("-Wswitch-unreachable")
#define __GCC_HAS_WARNING_Wvla_larger_than _X("-Wvla-larger-than=")
#endif /* __GCC_VERSION_NUM >= 70001 */

#if __GCC_VERSION_NUM >= 80000
#define __GCC_HAS_WARNING_Wnoexcept_type _S("-Wnoexcept-type")
#endif /* __GCC_VERSION_NUM >= 80000 */

#if __GCC_VERSION_NUM >= 80001
#define __GCC_HAS_WARNING_Wattribute_alias _S("-Wattribute-alias")
#define __GCC_HAS_WARNING_Wcast_align_strict _S("-Wcast-align=strict")
#define __GCC_HAS_WARNING_Wcast_function_type _S("-Wcast-function-type")
#define __GCC_HAS_WARNING_Wcatch_value _S("-Wcatch-value")
#define __GCC_HAS_WARNING_Wclass_memaccess _S("-Wclass-memaccess")
#define __GCC_HAS_WARNING_Wextra_semi _S("-Wextra-semi")
#define __GCC_HAS_WARNING_Wif_not_aligned _S("-Wif-not-aligned")
#define __GCC_HAS_WARNING_Wmultistatement_macros _S("-Wmultistatement-macros")
#define __GCC_HAS_WARNING_Wpacked_not_aligned _S("-Wpacked-not-aligned")
#define __GCC_HAS_WARNING_Wsizeof_pointer_div _S("-Wsizeof-pointer-div")
#define __GCC_HAS_WARNING_Wstringop_truncation _S("-Wstringop-truncation")
#define __GCC_HAS_WARNING_Wsuggest_attribute_cold _S("-Wsuggest-attribute=cold")
#define __GCC_HAS_WARNING_Wsuggest_attribute_malloc _S("-Wsuggest-attribute=malloc")
#endif /* __GCC_VERSION_NUM >= 80001 */

#if __GCC_VERSION_NUM >= 90000
#define __GCC_HAS_WARNING_Wmissing_attributes _S("-Wmissing-attributes")
#endif /* __GCC_VERSION_NUM >= 90000 */

#if __GCC_VERSION_NUM >= 90001
#define __GCC_HAS_WARNING_Wabsolute_value _S("-Wabsolute-value")
#define __GCC_HAS_WARNING_Waddress_of_packed_member _S("-Waddress-of-packed-member")
#define __GCC_HAS_WARNING_Wattribute_warning _S("-Wattribute-warning")
#define __GCC_HAS_WARNING_Wc11_c2x_compat _S("-Wc11-c2x-compat")
#define __GCC_HAS_WARNING_Wcannot_profile _S("-Wcannot-profile")
#define __GCC_HAS_WARNING_Wclass_conversion _S("-Wclass-conversion")
#define __GCC_HAS_WARNING_Wdeprecated_copy _S("-Wdeprecated-copy")
#define __GCC_HAS_WARNING_Wdeprecated_copy_dtor _S("-Wdeprecated-copy-dtor")
#define __GCC_HAS_WARNING_Winit_list_lifetime _S("-Winit-list-lifetime")
#define __GCC_HAS_WARNING_Wmissing_profile _S("-Wmissing-profile")
#define __GCC_HAS_WARNING_Wno_alloc_size_larger_than _S("-Wno-alloc-size-larger-than")
#define __GCC_HAS_WARNING_Wno_alloca_larger_than _S("-Wno-alloca-larger-than")
#define __GCC_HAS_WARNING_Wno_attribute_alias _S("-Wno-attribute-alias")
#define __GCC_HAS_WARNING_Wno_vla_larger_than _S("-Wno-vla-larger-than")
#define __GCC_HAS_WARNING_Wpessimizing_move _S("-Wpessimizing-move")
#define __GCC_HAS_WARNING_Wprio_ctor_dtor _S("-Wprio-ctor-dtor")
#define __GCC_HAS_WARNING_Wredundant_move _S("-Wredundant-move")
#endif /* __GCC_VERSION_NUM >= 90001 */

#if __GCC_VERSION_NUM >= 100000
#undef __GCC_HAS_WARNING_Wno_attribute_alias
#endif /* __GCC_VERSION_NUM >= 100000 */

#if __GCC_VERSION_NUM >= 100001
#define __GCC_HAS_WARNING_Wcomma_subscript _S("-Wcomma-subscript")
#define __GCC_HAS_WARNING_Wcxx20_compat _S("-Wc++20-compat")
#define __GCC_HAS_WARNING_Wcxx2a_compat _S("-Wc++2a-compat")
#define __GCC_HAS_WARNING_Wenum_conversion _S("-Wenum-conversion")
#define __GCC_HAS_WARNING_Wformat_diag _S("-Wformat-diag")
#define __GCC_HAS_WARNING_Winaccessible_base _S("-Winaccessible-base")
#define __GCC_HAS_WARNING_Wmismatched_tags _S("-Wmismatched-tags")
#define __GCC_HAS_WARNING_Wredundant_tags _S("-Wredundant-tags")
#define __GCC_HAS_WARNING_Wstring_compare _S("-Wstring-compare")
#define __GCC_HAS_WARNING_Wswitch_outside_range _S("-Wswitch-outside-range")
#define __GCC_HAS_WARNING_Wvolatile _S("-Wvolatile")
#define __GCC_HAS_WARNING_Wzero_length_bounds _S("-Wzero-length-bounds")
#endif /* __GCC_VERSION_NUM >= 100001 */

#if __GCC_VERSION_NUM >= 110000
#define __GCC_HAS_WARNING_Warith_conversion _S("-Warith-conversion")
#define __GCC_HAS_WARNING_Wno_frame_larger_than _S("-Wno-frame-larger-than")
#define __GCC_HAS_WARNING_Wno_larger_than _S("-Wno-larger-than")
#define __GCC_HAS_WARNING_Wno_stack_usage _S("-Wno-stack-usage")
#endif /* __GCC_VERSION_NUM >= 110000 */

#if __GCC_VERSION_NUM >= 110001
#define __GCC_HAS_WARNING_WNSObject_attribute _S("-WNSObject-attribute")
#define __GCC_HAS_WARNING_Warray_parameter _S("-Warray-parameter")
#define __GCC_HAS_WARNING_Wctad_maybe_unsupported _S("-Wctad-maybe-unsupported")
#define __GCC_HAS_WARNING_Wdeprecated_enum_enum_conversion _S("-Wdeprecated-enum-enum-conversion")
#define __GCC_HAS_WARNING_Wdeprecated_enum_float_conversion _S("-Wdeprecated-enum-float-conversion")
#define __GCC_HAS_WARNING_Wmismatched_dealloc _S("-Wmismatched-dealloc")
#define __GCC_HAS_WARNING_Wmismatched_new_delete _S("-Wmismatched-new-delete")
#define __GCC_HAS_WARNING_Wobjc_root_class _S("-Wobjc-root-class")
#define __GCC_HAS_WARNING_Wrange_loop_construct _S("-Wrange-loop-construct")
#define __GCC_HAS_WARNING_Wsizeof_array_div _S("-Wsizeof-array-div")
#define __GCC_HAS_WARNING_Wstringop_overread _S("-Wstringop-overread")
#define __GCC_HAS_WARNING_Wtsan _S("-Wtsan")
#define __GCC_HAS_WARNING_Wvexing_parse _S("-Wvexing-parse")
#define __GCC_HAS_WARNING_Wvla_parameter _S("-Wvla-parameter")
#endif /* __GCC_VERSION_NUM >= 110001 */

#if __GCC_VERSION_NUM >= 120001
#define __GCC_HAS_WARNING_Warray_compare _S("-Warray-compare")
#define __GCC_HAS_WARNING_Wbidi_chars _S("-Wbidi-chars")
#define __GCC_HAS_WARNING_Wcoverage_invalid_line_number _S("-Wcoverage-invalid-line-number")
#define __GCC_HAS_WARNING_Wcxx11_extensions _S("-Wc++11-extensions")
#define __GCC_HAS_WARNING_Wcxx14_extensions _S("-Wc++14-extensions")
#define __GCC_HAS_WARNING_Wcxx17_extensions _S("-Wc++17-extensions")
#define __GCC_HAS_WARNING_Wcxx20_extensions _S("-Wc++20-extensions")
#define __GCC_HAS_WARNING_Wcxx23_extensions _S("-Wc++23-extensions")
#define __GCC_HAS_WARNING_Wdangling_pointer _S("-Wdangling-pointer")
#define __GCC_HAS_WARNING_Wexceptions _S("-Wexceptions")
#define __GCC_HAS_WARNING_Winfinite_recursion _S("-Winfinite-recursion")
#define __GCC_HAS_WARNING_Winterference_size _S("-Winterference-size")
#define __GCC_HAS_WARNING_Winvalid_imported_macros _S("-Winvalid-imported-macros")
#define __GCC_HAS_WARNING_Wmissing_requires _S("-Wmissing-requires")
#define __GCC_HAS_WARNING_Wmissing_template_keyword _S("-Wmissing-template-keyword")
#define __GCC_HAS_WARNING_Wopenacc_parallelism _S("-Wopenacc-parallelism")
#define __GCC_HAS_WARNING_Wuse_after_free _S("-Wuse-after-free")
#endif /* __GCC_VERSION_NUM >= 120001 */

#if __GCC_VERSION_NUM >= 130000
#define __GCC_HAS_WARNING_Wtrivial_auto_var_init _S("-Wtrivial-auto-var-init")
#endif /* __GCC_VERSION_NUM >= 130000 */

#if __GCC_VERSION_NUM >= 130001
#define __GCC_HAS_WARNING_Wchanges_meaning _S("-Wchanges-meaning")
#define __GCC_HAS_WARNING_Wcomplain_wrong_lang _S("-Wcomplain-wrong-lang")
#define __GCC_HAS_WARNING_Wdangling_reference _S("-Wdangling-reference")
#define __GCC_HAS_WARNING_Wenum_int_mismatch _S("-Wenum-int-mismatch")
#define __GCC_HAS_WARNING_Winvalid_constexpr _S("-Winvalid-constexpr")
#define __GCC_HAS_WARNING_Winvalid_utf8 _S("-Winvalid-utf8")
#define __GCC_HAS_WARNING_Wself_move _S("-Wself-move")
#define __GCC_HAS_WARNING_Wstrict_flex_arrays _S("-Wstrict-flex-arrays")
#define __GCC_HAS_WARNING_Wunicode _S("-Wunicode")
#define __GCC_HAS_WARNING_Wxor_used_as_pow _S("-Wxor-used-as-pow")
#endif /* __GCC_VERSION_NUM >= 130001 */
#endif /* !__has_GCC_warning */
