/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

#ifndef __has_GCC_warning
#define __has_GCC_warning(x) __GCC_PRIVATE_W_IS_DEFINED(__GCC_HAS_WARNING_##x)
#define __GCC_PRIVATE_W_ARG_PLACEHOLDER__xS(x) ,
#define __GCC_PRIVATE_W_ARG_PLACEHOLDER__xX(x) ,
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
#define __PRIVATE_pragma_GCC_diagnostic_ignored_1__xS(text)  __pragma(GCC diagnostic ignored text)
#define __PRIVATE_pragma_GCC_diagnostic_ignored_1__xX(text)  __pragma(GCC diagnostic ignored text)
#define __PRIVATE_pragma_GCC_diagnostic_ignored_1(decl)      __PRIVATE_pragma_GCC_diagnostic_ignored_1_##decl
#define __PRIVATE_pragma_GCC_diagnostic_push_ignored_1(decl) __pragma_GCC_diagnostic_push __PRIVATE_pragma_GCC_diagnostic_ignored_1_##decl
#define __PRIVATE_pragma_GCC_diagnostic_pop_ignored_1(decl)  __pragma_GCC_diagnostic_pop
#define __PRIVATE_pragma_GCC_diagnostic_ignored_0(decl)           /* Nothing */
#define __PRIVATE_pragma_GCC_diagnostic_push_ignored_0(decl)      /* Nothing */
#define __PRIVATE_pragma_GCC_diagnostic_pop_ignored_0(decl)       /* Nothing */
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
#define __GCC_HAS_WARNING_W _xS("-W")
#define __GCC_HAS_WARNING_Wabi _xS("-Wabi")
#define __GCC_HAS_WARNING_Waggregate_return _xS("-Waggregate-return")
#define __GCC_HAS_WARNING_Wall _xS("-Wall")
#define __GCC_HAS_WARNING_Wbad_function_cast _xS("-Wbad-function-cast")
#define __GCC_HAS_WARNING_Wcast_align _xS("-Wcast-align")
#define __GCC_HAS_WARNING_Wcast_qual _xS("-Wcast-qual")
#define __GCC_HAS_WARNING_Wchar_subscripts _xS("-Wchar-subscripts")
#define __GCC_HAS_WARNING_Wcomment _xS("-Wcomment")
#define __GCC_HAS_WARNING_Wcomments _xS("-Wcomments")
#define __GCC_HAS_WARNING_Wconversion _xS("-Wconversion")
#define __GCC_HAS_WARNING_Wctor_dtor_privacy _xS("-Wctor-dtor-privacy")
#define __GCC_HAS_WARNING_Wdeclaration_after_statement _xS("-Wdeclaration-after-statement")
#define __GCC_HAS_WARNING_Wdeprecated _xS("-Wdeprecated")
#define __GCC_HAS_WARNING_Wdeprecated_declarations _xS("-Wdeprecated-declarations")
#define __GCC_HAS_WARNING_Wdisabled_optimization _xS("-Wdisabled-optimization")
#define __GCC_HAS_WARNING_Wdiv_by_zero _xS("-Wdiv-by-zero")
#define __GCC_HAS_WARNING_Weffcxx _xS("-Weffc++")
#define __GCC_HAS_WARNING_Wendif_labels _xS("-Wendif-labels")
#define __GCC_HAS_WARNING_Werror _xS("-Werror")
#define __GCC_HAS_WARNING_Werror_implicit_function_declaration _xS("-Werror-implicit-function-declaration")
#define __GCC_HAS_WARNING_Wextra _xS("-Wextra")
#define __GCC_HAS_WARNING_Wfloat_equal _xS("-Wfloat-equal")
#define __GCC_HAS_WARNING_Wformat _xS("-Wformat")
#define __GCC_HAS_WARNING_Wformat_extra_args _xS("-Wformat-extra-args")
#define __GCC_HAS_WARNING_Wformat_nonliteral _xS("-Wformat-nonliteral")
#define __GCC_HAS_WARNING_Wformat_security _xS("-Wformat-security")
#define __GCC_HAS_WARNING_Wformat_y2k _xS("-Wformat-y2k")
#define __GCC_HAS_WARNING_Wformat_zero_length _xS("-Wformat-zero-length")
#define __GCC_HAS_WARNING_Wimplicit _xS("-Wimplicit")
#define __GCC_HAS_WARNING_Wimplicit_function_declaration _xS("-Wimplicit-function-declaration")
#define __GCC_HAS_WARNING_Wimplicit_int _xS("-Wimplicit-int")
#define __GCC_HAS_WARNING_Wimport _xS("-Wimport")
#define __GCC_HAS_WARNING_Winit_self _xS("-Winit-self")
#define __GCC_HAS_WARNING_Winline _xS("-Winline")
#define __GCC_HAS_WARNING_Winvalid_offsetof _xS("-Winvalid-offsetof")
#define __GCC_HAS_WARNING_Winvalid_pch _xS("-Winvalid-pch")
#define __GCC_HAS_WARNING_Wlarger_than_ _xS("-Wlarger-than-")
#define __GCC_HAS_WARNING_Wlong_long _xS("-Wlong-long")
#define __GCC_HAS_WARNING_Wmain _xS("-Wmain")
#define __GCC_HAS_WARNING_Wmissing_braces _xS("-Wmissing-braces")
#define __GCC_HAS_WARNING_Wmissing_declarations _xS("-Wmissing-declarations")
#define __GCC_HAS_WARNING_Wmissing_format_attribute _xS("-Wmissing-format-attribute")
#define __GCC_HAS_WARNING_Wmissing_noreturn _xS("-Wmissing-noreturn")
#define __GCC_HAS_WARNING_Wmissing_prototypes _xS("-Wmissing-prototypes")
#define __GCC_HAS_WARNING_Wmultichar _xS("-Wmultichar")
#define __GCC_HAS_WARNING_Wnested_externs _xS("-Wnested-externs")
#define __GCC_HAS_WARNING_Wnon_template_friend _xS("-Wnon-template-friend")
#define __GCC_HAS_WARNING_Wnon_virtual_dtor _xS("-Wnon-virtual-dtor")
#define __GCC_HAS_WARNING_Wnonnull _xS("-Wnonnull")
#define __GCC_HAS_WARNING_Wold_style_cast _xS("-Wold-style-cast")
#define __GCC_HAS_WARNING_Wold_style_definition _xS("-Wold-style-definition")
#define __GCC_HAS_WARNING_Woverloaded_virtual _xS("-Woverloaded-virtual")
#define __GCC_HAS_WARNING_Wpacked _xS("-Wpacked")
#define __GCC_HAS_WARNING_Wpadded _xS("-Wpadded")
#define __GCC_HAS_WARNING_Wparentheses _xS("-Wparentheses")
#define __GCC_HAS_WARNING_Wpmf_conversions _xS("-Wpmf-conversions")
#define __GCC_HAS_WARNING_Wpointer_arith _xS("-Wpointer-arith")
#define __GCC_HAS_WARNING_Wprotocol _xS("-Wprotocol")
#define __GCC_HAS_WARNING_Wredundant_decls _xS("-Wredundant-decls")
#define __GCC_HAS_WARNING_Wreorder _xS("-Wreorder")
#define __GCC_HAS_WARNING_Wreturn_type _xS("-Wreturn-type")
#define __GCC_HAS_WARNING_Wselector _xS("-Wselector")
#define __GCC_HAS_WARNING_Wsequence_point _xS("-Wsequence-point")
#define __GCC_HAS_WARNING_Wshadow _xS("-Wshadow")
#define __GCC_HAS_WARNING_Wsign_compare _xS("-Wsign-compare")
#define __GCC_HAS_WARNING_Wsign_promo _xS("-Wsign-promo")
#define __GCC_HAS_WARNING_Wstrict_aliasing _xS("-Wstrict-aliasing")
#define __GCC_HAS_WARNING_Wstrict_prototypes _xS("-Wstrict-prototypes")
#define __GCC_HAS_WARNING_Wswitch _xS("-Wswitch")
#define __GCC_HAS_WARNING_Wswitch_default _xS("-Wswitch-default")
#define __GCC_HAS_WARNING_Wswitch_enum _xS("-Wswitch-enum")
#define __GCC_HAS_WARNING_Wsynth _xS("-Wsynth")
#define __GCC_HAS_WARNING_Wsystem_headers _xS("-Wsystem-headers")
#define __GCC_HAS_WARNING_Wtraditional _xS("-Wtraditional")
#define __GCC_HAS_WARNING_Wtrigraphs _xS("-Wtrigraphs")
#define __GCC_HAS_WARNING_Wundeclared_selector _xS("-Wundeclared-selector")
#define __GCC_HAS_WARNING_Wundef _xS("-Wundef")
#define __GCC_HAS_WARNING_Wuninitialized _xS("-Wuninitialized")
#define __GCC_HAS_WARNING_Wunknown_pragmas _xS("-Wunknown-pragmas")
#define __GCC_HAS_WARNING_Wunreachable_code _xS("-Wunreachable-code")
#define __GCC_HAS_WARNING_Wunused _xS("-Wunused")
#define __GCC_HAS_WARNING_Wunused_function _xS("-Wunused-function")
#define __GCC_HAS_WARNING_Wunused_label _xS("-Wunused-label")
#define __GCC_HAS_WARNING_Wunused_macros _xS("-Wunused-macros")
#define __GCC_HAS_WARNING_Wunused_parameter _xS("-Wunused-parameter")
#define __GCC_HAS_WARNING_Wunused_value _xS("-Wunused-value")
#define __GCC_HAS_WARNING_Wunused_variable _xS("-Wunused-variable")
#define __GCC_HAS_WARNING_Wwrite_strings _xS("-Wwrite-strings")
#endif /* __GCC_VERSION_NUM >= 30400 */

#if __GCC_VERSION_NUM >= 40000
#define __GCC_HAS_WARNING_Wfatal_errors _xS("-Wfatal-errors")
#define __GCC_HAS_WARNING_Wmissing_field_initializers _xS("-Wmissing-field-initializers")
#define __GCC_HAS_WARNING_Wmissing_include_dirs _xS("-Wmissing-include-dirs")
#define __GCC_HAS_WARNING_Wvariadic_macros _xS("-Wvariadic-macros")
#endif /* __GCC_VERSION_NUM >= 40000 */

#if __GCC_VERSION_NUM >= 40100
#define __GCC_HAS_WARNING_Wnormalized _xX("-Wnormalized=")
#define __GCC_HAS_WARNING_Wpointer_sign _xS("-Wpointer-sign")
#endif /* __GCC_VERSION_NUM >= 40100 */

#if __GCC_VERSION_NUM >= 40200
#define __GCC_HAS_WARNING_Wassign_intercept _xS("-Wassign-intercept")
#define __GCC_HAS_WARNING_Wattributes _xS("-Wattributes")
#define __GCC_HAS_WARNING_Wcxx_compat _xS("-Wc++-compat")
#define __GCC_HAS_WARNING_Wint_to_pointer_cast _xS("-Wint-to-pointer-cast")
#define __GCC_HAS_WARNING_Wpointer_to_int_cast _xS("-Wpointer-to-int-cast")
#define __GCC_HAS_WARNING_Wpragmas _xS("-Wpragmas")
#define __GCC_HAS_WARNING_Wstack_protector _xS("-Wstack-protector")
#define __GCC_HAS_WARNING_Wstrict_null_sentinel _xS("-Wstrict-null-sentinel")
#define __GCC_HAS_WARNING_Wstrict_selector_match _xS("-Wstrict-selector-match")
#define __GCC_HAS_WARNING_Wunsafe_loop_optimizations _xS("-Wunsafe-loop-optimizations")
#define __GCC_HAS_WARNING_Wvolatile_register_var _xS("-Wvolatile-register-var")
#endif /* __GCC_VERSION_NUM >= 40200 */

#if __GCC_VERSION_NUM >= 40300
#define __GCC_HAS_WARNING_Walways_true _xS("-Walways-true")
#define __GCC_HAS_WARNING_Woverflow _xS("-Woverflow")
#define __GCC_HAS_WARNING_Woverlength_strings _xS("-Woverlength-strings")
#define __GCC_HAS_WARNING_Woverride_init _xS("-Woverride-init")
#define __GCC_HAS_WARNING_Wstring_literal_comparison _xS("-Wstring-literal-comparison")
#endif /* __GCC_VERSION_NUM >= 40300 */

#if __GCC_VERSION_NUM >= 40400
#undef __GCC_HAS_WARNING_Walways_true
#undef __GCC_HAS_WARNING_Wstring_literal_comparison
#define __GCC_HAS_WARNING_Waddress _xS("-Waddress")
#define __GCC_HAS_WARNING_Warray_bounds _xS("-Warray-bounds")
#define __GCC_HAS_WARNING_Wclobbered _xS("-Wclobbered")
#define __GCC_HAS_WARNING_Wcoverage_mismatch _xS("-Wcoverage-mismatch")
#define __GCC_HAS_WARNING_Wcxx0x_compat _xS("-Wc++0x-compat")
#define __GCC_HAS_WARNING_Wempty_body _xS("-Wempty-body")
#define __GCC_HAS_WARNING_Wformat_contains_nul _xS("-Wformat-contains-nul")
#define __GCC_HAS_WARNING_Wignored_qualifiers _xS("-Wignored-qualifiers")
#define __GCC_HAS_WARNING_Wlogical_op _xS("-Wlogical-op")
#define __GCC_HAS_WARNING_Wmissing_parameter_type _xS("-Wmissing-parameter-type")
#define __GCC_HAS_WARNING_Wold_style_declaration _xS("-Wold-style-declaration")
#define __GCC_HAS_WARNING_Wsign_conversion _xS("-Wsign-conversion")
#define __GCC_HAS_WARNING_Wstrict_overflow _xS("-Wstrict-overflow")
#define __GCC_HAS_WARNING_Wtraditional_conversion _xS("-Wtraditional-conversion")
#define __GCC_HAS_WARNING_Wtype_limits _xS("-Wtype-limits")
#define __GCC_HAS_WARNING_Wvla _xS("-Wvla")
#endif /* __GCC_VERSION_NUM >= 40400 */

#if __GCC_VERSION_NUM >= 40500
#define __GCC_HAS_WARNING_Wbuiltin_macro_redefined _xS("-Wbuiltin-macro-redefined")
#define __GCC_HAS_WARNING_Wdisallowed_function_list _xX("-Wdisallowed-function-list=")
#define __GCC_HAS_WARNING_Wenum_compare _xS("-Wenum-compare")
#define __GCC_HAS_WARNING_Wframe_larger_than _xX("-Wframe-larger-than=")
#define __GCC_HAS_WARNING_Wlarger_than _xX("-Wlarger-than=")
#define __GCC_HAS_WARNING_Wmudflap _xS("-Wmudflap")
#define __GCC_HAS_WARNING_Wpacked_bitfield_compat _xS("-Wpacked-bitfield-compat")
#define __GCC_HAS_WARNING_Wpsabi _xS("-Wpsabi")
#define __GCC_HAS_WARNING_Wsync_nand _xS("-Wsync-nand")
#endif /* __GCC_VERSION_NUM >= 40500 */

#if __GCC_VERSION_NUM >= 40600
#undef __GCC_HAS_WARNING_Wdisallowed_function_list
#define __GCC_HAS_WARNING_Wconversion_null _xS("-Wconversion-null")
#define __GCC_HAS_WARNING_Wjump_misses_init _xS("-Wjump-misses-init")
#define __GCC_HAS_WARNING_Wunsuffixed_float_constants _xS("-Wunsuffixed-float-constants")
#define __GCC_HAS_WARNING_Wunused_result _xS("-Wunused-result")
#endif /* __GCC_VERSION_NUM >= 40600 */

#if __GCC_VERSION_NUM >= 40700
#undef __GCC_HAS_WARNING_Werror
#undef __GCC_HAS_WARNING_Wfatal_errors
#undef __GCC_HAS_WARNING_Wframe_larger_than
#undef __GCC_HAS_WARNING_Wimport
#undef __GCC_HAS_WARNING_Wpsabi
#undef __GCC_HAS_WARNING_Wsign_conversion
#undef __GCC_HAS_WARNING_Wunreachable_code
#define __GCC_HAS_WARNING_Wcpp _xS("-Wcpp")
#define __GCC_HAS_WARNING_Wdouble_promotion _xS("-Wdouble-promotion")
#define __GCC_HAS_WARNING_Wnoexcept _xS("-Wnoexcept")
#define __GCC_HAS_WARNING_Wproperty_assign_default _xS("-Wproperty-assign-default")
#define __GCC_HAS_WARNING_Wsuggest_attribute_const _xS("-Wsuggest-attribute=const")
#define __GCC_HAS_WARNING_Wsuggest_attribute_noreturn _xS("-Wsuggest-attribute=noreturn")
#define __GCC_HAS_WARNING_Wsuggest_attribute_pure _xS("-Wsuggest-attribute=pure")
#define __GCC_HAS_WARNING_Wtrampolines _xS("-Wtrampolines")
#define __GCC_HAS_WARNING_Wunused_but_set_parameter _xS("-Wunused-but-set-parameter")
#define __GCC_HAS_WARNING_Wunused_but_set_variable _xS("-Wunused-but-set-variable")
#endif /* __GCC_VERSION_NUM >= 40700 */

#if __GCC_VERSION_NUM >= 40800
#define __GCC_HAS_WARNING_Wcxx11_compat _xS("-Wc++11-compat")
#define __GCC_HAS_WARNING_Wdelete_non_virtual_dtor _xS("-Wdelete-non-virtual-dtor")
#define __GCC_HAS_WARNING_Wfree_nonheap_object _xS("-Wfree-nonheap-object")
#define __GCC_HAS_WARNING_Winvalid_memory_model _xS("-Winvalid-memory-model")
#define __GCC_HAS_WARNING_Wmaybe_uninitialized _xS("-Wmaybe-uninitialized")
#define __GCC_HAS_WARNING_Wnarrowing _xS("-Wnarrowing")
#define __GCC_HAS_WARNING_Wstack_usage _xX("-Wstack-usage=")
#define __GCC_HAS_WARNING_Wunused_local_typedefs _xS("-Wunused-local-typedefs")
#define __GCC_HAS_WARNING_Wvector_operation_performance _xS("-Wvector-operation-performance")
#define __GCC_HAS_WARNING_Wzero_as_null_pointer_constant _xS("-Wzero-as-null-pointer-constant")
#endif /* __GCC_VERSION_NUM >= 40800 */

#if __GCC_VERSION_NUM >= 40900
#undef __GCC_HAS_WARNING_Wmissing_format_attribute
#undef __GCC_HAS_WARNING_Wmissing_noreturn
#define __GCC_HAS_WARNING_Wabi_tag _xS("-Wabi-tag")
#define __GCC_HAS_WARNING_Waggressive_loop_optimizations _xS("-Waggressive-loop-optimizations")
#define __GCC_HAS_WARNING_Winherited_variadic_ctor _xS("-Winherited-variadic-ctor")
#define __GCC_HAS_WARNING_Wliteral_suffix _xS("-Wliteral-suffix")
#define __GCC_HAS_WARNING_Wpedantic _xS("-Wpedantic")
#define __GCC_HAS_WARNING_Wreturn_local_addr _xS("-Wreturn-local-addr")
#define __GCC_HAS_WARNING_Wsizeof_pointer_memaccess _xS("-Wsizeof-pointer-memaccess")
#define __GCC_HAS_WARNING_Wsuggest_attribute_format _xS("-Wsuggest-attribute=format")
#define __GCC_HAS_WARNING_Wuseless_cast _xS("-Wuseless-cast")
#define __GCC_HAS_WARNING_Wvarargs _xS("-Wvarargs")
#define __GCC_HAS_WARNING_Wvirtual_move_assign _xS("-Wvirtual-move-assign")
#endif /* __GCC_VERSION_NUM >= 40900 */

#if __GCC_VERSION_NUM >= 41000
#undef __GCC_HAS_WARNING_Wmudflap
#define __GCC_HAS_WARNING_Wconditionally_supported _xS("-Wconditionally-supported")
#define __GCC_HAS_WARNING_Wdate_time _xS("-Wdate-time")
#define __GCC_HAS_WARNING_Wdelete_incomplete _xS("-Wdelete-incomplete")
#define __GCC_HAS_WARNING_Wopenmp_simd _xS("-Wopenmp-simd")
#endif /* __GCC_VERSION_NUM >= 41000 */

#if __GCC_VERSION_NUM >= 50000
#define __GCC_HAS_WARNING_Wc90_c99_compat _xS("-Wc90-c99-compat")
#define __GCC_HAS_WARNING_Wdesignated_init _xS("-Wdesignated-init")
#define __GCC_HAS_WARNING_Wdiscarded_qualifiers _xS("-Wdiscarded-qualifiers")
#define __GCC_HAS_WARNING_Wformat_signedness _xS("-Wformat-signedness")
#define __GCC_HAS_WARNING_Wincompatible_pointer_types _xS("-Wincompatible-pointer-types")
#define __GCC_HAS_WARNING_Wint_conversion _xS("-Wint-conversion")
#define __GCC_HAS_WARNING_Wlogical_not_parentheses _xS("-Wlogical-not-parentheses")
#define __GCC_HAS_WARNING_Wmemset_transposed_args _xS("-Wmemset-transposed-args")
#define __GCC_HAS_WARNING_Wodr _xS("-Wodr")
#define __GCC_HAS_WARNING_Wshadow_ivar _xS("-Wshadow-ivar")
#define __GCC_HAS_WARNING_Wsizeof_array_argument _xS("-Wsizeof-array-argument")
#define __GCC_HAS_WARNING_Wsuggest_final_methods _xS("-Wsuggest-final-methods")
#define __GCC_HAS_WARNING_Wsuggest_final_types _xS("-Wsuggest-final-types")
#define __GCC_HAS_WARNING_Wswitch_bool _xS("-Wswitch-bool")
#endif /* __GCC_VERSION_NUM >= 50000 */

#if __GCC_VERSION_NUM >= 60000
#define __GCC_HAS_WARNING_Wbool_compare _xS("-Wbool-compare")
#define __GCC_HAS_WARNING_Wc99_c11_compat _xS("-Wc99-c11-compat")
#define __GCC_HAS_WARNING_Wchkp _xS("-Wchkp")
#define __GCC_HAS_WARNING_Wcxx14_compat _xS("-Wc++14-compat")
#define __GCC_HAS_WARNING_Wdiscarded_array_qualifiers _xS("-Wdiscarded-array-qualifiers")
#define __GCC_HAS_WARNING_Wshift_count_negative _xS("-Wshift-count-negative")
#define __GCC_HAS_WARNING_Wshift_count_overflow _xS("-Wshift-count-overflow")
#define __GCC_HAS_WARNING_Wsized_deallocation _xS("-Wsized-deallocation")
#define __GCC_HAS_WARNING_Wsuggest_override _xS("-Wsuggest-override")
#endif /* __GCC_VERSION_NUM >= 60000 */

#if __GCC_VERSION_NUM >= 70000
#define __GCC_HAS_WARNING_Wduplicated_cond _xS("-Wduplicated-cond")
#define __GCC_HAS_WARNING_Wfloat_conversion _xS("-Wfloat-conversion")
#define __GCC_HAS_WARNING_Wframe_address _xS("-Wframe-address")
#define __GCC_HAS_WARNING_Wframe_larger_than _xX("-Wframe-larger-than=")
#define __GCC_HAS_WARNING_Whsa _xS("-Whsa")
#define __GCC_HAS_WARNING_Wignored_attributes _xS("-Wignored-attributes")
#define __GCC_HAS_WARNING_Wlto_type_mismatch _xS("-Wlto-type-mismatch")
#define __GCC_HAS_WARNING_Wmisleading_indentation _xS("-Wmisleading-indentation")
#define __GCC_HAS_WARNING_Wmissing_format_attribute _xS("-Wmissing-format-attribute")
#define __GCC_HAS_WARNING_Wmissing_noreturn _xS("-Wmissing-noreturn")
#define __GCC_HAS_WARNING_Wmultiple_inheritance _xS("-Wmultiple-inheritance")
#define __GCC_HAS_WARNING_Wnamespaces _xS("-Wnamespaces")
#define __GCC_HAS_WARNING_Wnonnull_compare _xS("-Wnonnull-compare")
#define __GCC_HAS_WARNING_Wnull_dereference _xS("-Wnull-dereference")
#define __GCC_HAS_WARNING_Woverride_init_side_effects _xS("-Woverride-init-side-effects")
#define __GCC_HAS_WARNING_Wplacement_new _xS("-Wplacement-new")
#define __GCC_HAS_WARNING_Wscalar_storage_order _xS("-Wscalar-storage-order")
#define __GCC_HAS_WARNING_Wshift_negative_value _xS("-Wshift-negative-value")
#define __GCC_HAS_WARNING_Wshift_overflow _xS("-Wshift-overflow")
#define __GCC_HAS_WARNING_Wsign_conversion _xS("-Wsign-conversion")
#define __GCC_HAS_WARNING_Wsubobject_linkage _xS("-Wsubobject-linkage")
#define __GCC_HAS_WARNING_Wtautological_compare _xS("-Wtautological-compare")
#define __GCC_HAS_WARNING_Wtemplates _xS("-Wtemplates")
#define __GCC_HAS_WARNING_Wterminate _xS("-Wterminate")
#define __GCC_HAS_WARNING_Wunreachable_code _xS("-Wunreachable-code")
#define __GCC_HAS_WARNING_Wunused_const_variable _xS("-Wunused-const-variable")
#define __GCC_HAS_WARNING_Wvirtual_inheritance _xS("-Wvirtual-inheritance")
#endif /* __GCC_VERSION_NUM >= 70000 */

#if __GCC_VERSION_NUM >= 70001
#define __GCC_HAS_WARNING_Waligned_new _xX("-Waligned-new=")
#define __GCC_HAS_WARNING_Walloc_size_larger_than _xX("-Walloc-size-larger-than=")
#define __GCC_HAS_WARNING_Walloc_zero _xS("-Walloc-zero")
#define __GCC_HAS_WARNING_Walloca _xS("-Walloca")
#define __GCC_HAS_WARNING_Walloca_larger_than _xX("-Walloca-larger-than=")
#define __GCC_HAS_WARNING_Wbool_operation _xS("-Wbool-operation")
#define __GCC_HAS_WARNING_Wbuiltin_declaration_mismatch _xS("-Wbuiltin-declaration-mismatch")
#define __GCC_HAS_WARNING_Wcxx17_compat _xS("-Wc++17-compat")
#define __GCC_HAS_WARNING_Wcxx1z_compat _xS("-Wc++1z-compat")
#define __GCC_HAS_WARNING_Wdangling_else _xS("-Wdangling-else")
#define __GCC_HAS_WARNING_Wduplicate_decl_specifier _xS("-Wduplicate-decl-specifier")
#define __GCC_HAS_WARNING_Wduplicated_branches _xS("-Wduplicated-branches")
#define __GCC_HAS_WARNING_Wexpansion_to_defined _xS("-Wexpansion-to-defined")
#define __GCC_HAS_WARNING_Wformat_overflow _xS("-Wformat-overflow")
#define __GCC_HAS_WARNING_Wformat_truncation _xS("-Wformat-truncation")
#define __GCC_HAS_WARNING_Wimplicit_fallthrough _xS("-Wimplicit-fallthrough")
#define __GCC_HAS_WARNING_Wint_in_bool_context _xS("-Wint-in-bool-context")
#define __GCC_HAS_WARNING_Wmemset_elt_size _xS("-Wmemset-elt-size")
#define __GCC_HAS_WARNING_Wpointer_compare _xS("-Wpointer-compare")
#define __GCC_HAS_WARNING_Wpsabi _xS("-Wpsabi")
#define __GCC_HAS_WARNING_Wregister _xS("-Wregister")
#define __GCC_HAS_WARNING_Wrestrict _xS("-Wrestrict")
#define __GCC_HAS_WARNING_Wshadow_compatible_local _xS("-Wshadow-compatible-local")
#define __GCC_HAS_WARNING_Wshadow_global _xS("-Wshadow=global")
#define __GCC_HAS_WARNING_Wshadow_local _xS("-Wshadow-local")
#define __GCC_HAS_WARNING_Wstringop_overflow _xS("-Wstringop-overflow")
#define __GCC_HAS_WARNING_Wswitch_unreachable _xS("-Wswitch-unreachable")
#define __GCC_HAS_WARNING_Wvla_larger_than _xX("-Wvla-larger-than=")
#endif /* __GCC_VERSION_NUM >= 70001 */

#if __GCC_VERSION_NUM >= 80000
#define __GCC_HAS_WARNING_Wnoexcept_type _xS("-Wnoexcept-type")
#endif /* __GCC_VERSION_NUM >= 80000 */

#if __GCC_VERSION_NUM >= 80001
#define __GCC_HAS_WARNING_Wattribute_alias _xS("-Wattribute-alias")
#define __GCC_HAS_WARNING_Wcast_align_strict _xS("-Wcast-align=strict")
#define __GCC_HAS_WARNING_Wcast_function_type _xS("-Wcast-function-type")
#define __GCC_HAS_WARNING_Wcatch_value _xS("-Wcatch-value")
#define __GCC_HAS_WARNING_Wclass_memaccess _xS("-Wclass-memaccess")
#define __GCC_HAS_WARNING_Wextra_semi _xS("-Wextra-semi")
#define __GCC_HAS_WARNING_Wif_not_aligned _xS("-Wif-not-aligned")
#define __GCC_HAS_WARNING_Wmultistatement_macros _xS("-Wmultistatement-macros")
#define __GCC_HAS_WARNING_Wpacked_not_aligned _xS("-Wpacked-not-aligned")
#define __GCC_HAS_WARNING_Wsizeof_pointer_div _xS("-Wsizeof-pointer-div")
#define __GCC_HAS_WARNING_Wstringop_truncation _xS("-Wstringop-truncation")
#define __GCC_HAS_WARNING_Wsuggest_attribute_cold _xS("-Wsuggest-attribute=cold")
#define __GCC_HAS_WARNING_Wsuggest_attribute_malloc _xS("-Wsuggest-attribute=malloc")
#endif /* __GCC_VERSION_NUM >= 80001 */

#if __GCC_VERSION_NUM >= 90000
#define __GCC_HAS_WARNING_Wmissing_attributes _xS("-Wmissing-attributes")
#endif /* __GCC_VERSION_NUM >= 90000 */

#if __GCC_VERSION_NUM >= 90001
#define __GCC_HAS_WARNING_Wabsolute_value _xS("-Wabsolute-value")
#define __GCC_HAS_WARNING_Waddress_of_packed_member _xS("-Waddress-of-packed-member")
#define __GCC_HAS_WARNING_Wattribute_warning _xS("-Wattribute-warning")
#define __GCC_HAS_WARNING_Wc11_c2x_compat _xS("-Wc11-c2x-compat")
#define __GCC_HAS_WARNING_Wcannot_profile _xS("-Wcannot-profile")
#define __GCC_HAS_WARNING_Wclass_conversion _xS("-Wclass-conversion")
#define __GCC_HAS_WARNING_Wdeprecated_copy _xS("-Wdeprecated-copy")
#define __GCC_HAS_WARNING_Wdeprecated_copy_dtor _xS("-Wdeprecated-copy-dtor")
#define __GCC_HAS_WARNING_Winit_list_lifetime _xS("-Winit-list-lifetime")
#define __GCC_HAS_WARNING_Wmissing_profile _xS("-Wmissing-profile")
#define __GCC_HAS_WARNING_Wno_alloc_size_larger_than _xS("-Wno-alloc-size-larger-than")
#define __GCC_HAS_WARNING_Wno_alloca_larger_than _xS("-Wno-alloca-larger-than")
#define __GCC_HAS_WARNING_Wno_attribute_alias _xS("-Wno-attribute-alias")
#define __GCC_HAS_WARNING_Wno_vla_larger_than _xS("-Wno-vla-larger-than")
#define __GCC_HAS_WARNING_Wpessimizing_move _xS("-Wpessimizing-move")
#define __GCC_HAS_WARNING_Wprio_ctor_dtor _xS("-Wprio-ctor-dtor")
#define __GCC_HAS_WARNING_Wredundant_move _xS("-Wredundant-move")
#endif /* __GCC_VERSION_NUM >= 90001 */

#if __GCC_VERSION_NUM >= 100000
#undef __GCC_HAS_WARNING_Wno_attribute_alias
#endif /* __GCC_VERSION_NUM >= 100000 */

#if __GCC_VERSION_NUM >= 100001
#define __GCC_HAS_WARNING_Wcomma_subscript _xS("-Wcomma-subscript")
#define __GCC_HAS_WARNING_Wcxx20_compat _xS("-Wc++20-compat")
#define __GCC_HAS_WARNING_Wcxx2a_compat _xS("-Wc++2a-compat")
#define __GCC_HAS_WARNING_Wenum_conversion _xS("-Wenum-conversion")
#define __GCC_HAS_WARNING_Wformat_diag _xS("-Wformat-diag")
#define __GCC_HAS_WARNING_Winaccessible_base _xS("-Winaccessible-base")
#define __GCC_HAS_WARNING_Wmismatched_tags _xS("-Wmismatched-tags")
#define __GCC_HAS_WARNING_Wredundant_tags _xS("-Wredundant-tags")
#define __GCC_HAS_WARNING_Wstring_compare _xS("-Wstring-compare")
#define __GCC_HAS_WARNING_Wswitch_outside_range _xS("-Wswitch-outside-range")
#define __GCC_HAS_WARNING_Wvolatile _xS("-Wvolatile")
#define __GCC_HAS_WARNING_Wzero_length_bounds _xS("-Wzero-length-bounds")
#endif /* __GCC_VERSION_NUM >= 100001 */

#if __GCC_VERSION_NUM >= 110000
#define __GCC_HAS_WARNING_Warith_conversion _xS("-Warith-conversion")
#define __GCC_HAS_WARNING_Wno_frame_larger_than _xS("-Wno-frame-larger-than")
#define __GCC_HAS_WARNING_Wno_larger_than _xS("-Wno-larger-than")
#define __GCC_HAS_WARNING_Wno_stack_usage _xS("-Wno-stack-usage")
#endif /* __GCC_VERSION_NUM >= 110000 */

#if __GCC_VERSION_NUM >= 110001
#define __GCC_HAS_WARNING_WNSObject_attribute _xS("-WNSObject-attribute")
#define __GCC_HAS_WARNING_Warray_parameter _xS("-Warray-parameter")
#define __GCC_HAS_WARNING_Wctad_maybe_unsupported _xS("-Wctad-maybe-unsupported")
#define __GCC_HAS_WARNING_Wdeprecated_enum_enum_conversion _xS("-Wdeprecated-enum-enum-conversion")
#define __GCC_HAS_WARNING_Wdeprecated_enum_float_conversion _xS("-Wdeprecated-enum-float-conversion")
#define __GCC_HAS_WARNING_Wmismatched_dealloc _xS("-Wmismatched-dealloc")
#define __GCC_HAS_WARNING_Wmismatched_new_delete _xS("-Wmismatched-new-delete")
#define __GCC_HAS_WARNING_Wobjc_root_class _xS("-Wobjc-root-class")
#define __GCC_HAS_WARNING_Wrange_loop_construct _xS("-Wrange-loop-construct")
#define __GCC_HAS_WARNING_Wsizeof_array_div _xS("-Wsizeof-array-div")
#define __GCC_HAS_WARNING_Wstringop_overread _xS("-Wstringop-overread")
#define __GCC_HAS_WARNING_Wtsan _xS("-Wtsan")
#define __GCC_HAS_WARNING_Wvexing_parse _xS("-Wvexing-parse")
#define __GCC_HAS_WARNING_Wvla_parameter _xS("-Wvla-parameter")
#endif /* __GCC_VERSION_NUM >= 110001 */

#if __GCC_VERSION_NUM >= 120001
#define __GCC_HAS_WARNING_Warray_compare _xS("-Warray-compare")
#define __GCC_HAS_WARNING_Wbidi_chars _xS("-Wbidi-chars")
#define __GCC_HAS_WARNING_Wcoverage_invalid_line_number _xS("-Wcoverage-invalid-line-number")
#define __GCC_HAS_WARNING_Wcxx11_extensions _xS("-Wc++11-extensions")
#define __GCC_HAS_WARNING_Wcxx14_extensions _xS("-Wc++14-extensions")
#define __GCC_HAS_WARNING_Wcxx17_extensions _xS("-Wc++17-extensions")
#define __GCC_HAS_WARNING_Wcxx20_extensions _xS("-Wc++20-extensions")
#define __GCC_HAS_WARNING_Wcxx23_extensions _xS("-Wc++23-extensions")
#define __GCC_HAS_WARNING_Wdangling_pointer _xS("-Wdangling-pointer")
#define __GCC_HAS_WARNING_Wexceptions _xS("-Wexceptions")
#define __GCC_HAS_WARNING_Winfinite_recursion _xS("-Winfinite-recursion")
#define __GCC_HAS_WARNING_Winterference_size _xS("-Winterference-size")
#define __GCC_HAS_WARNING_Winvalid_imported_macros _xS("-Winvalid-imported-macros")
#define __GCC_HAS_WARNING_Wmissing_requires _xS("-Wmissing-requires")
#define __GCC_HAS_WARNING_Wmissing_template_keyword _xS("-Wmissing-template-keyword")
#define __GCC_HAS_WARNING_Wopenacc_parallelism _xS("-Wopenacc-parallelism")
#define __GCC_HAS_WARNING_Wuse_after_free _xS("-Wuse-after-free")
#endif /* __GCC_VERSION_NUM >= 120001 */

#if __GCC_VERSION_NUM >= 130000
#define __GCC_HAS_WARNING_Wtrivial_auto_var_init _xS("-Wtrivial-auto-var-init")
#endif /* __GCC_VERSION_NUM >= 130000 */

#if __GCC_VERSION_NUM >= 130001
#define __GCC_HAS_WARNING_Wchanges_meaning _xS("-Wchanges-meaning")
#define __GCC_HAS_WARNING_Wcomplain_wrong_lang _xS("-Wcomplain-wrong-lang")
#define __GCC_HAS_WARNING_Wdangling_reference _xS("-Wdangling-reference")
#define __GCC_HAS_WARNING_Wenum_int_mismatch _xS("-Wenum-int-mismatch")
#define __GCC_HAS_WARNING_Winvalid_constexpr _xS("-Winvalid-constexpr")
#define __GCC_HAS_WARNING_Winvalid_utf8 _xS("-Winvalid-utf8")
#define __GCC_HAS_WARNING_Wself_move _xS("-Wself-move")
#define __GCC_HAS_WARNING_Wstrict_flex_arrays _xS("-Wstrict-flex-arrays")
#define __GCC_HAS_WARNING_Wunicode _xS("-Wunicode")
#define __GCC_HAS_WARNING_Wxor_used_as_pow _xS("-Wxor-used-as-pow")
#endif /* __GCC_VERSION_NUM >= 130001 */
#endif /* !__has_GCC_warning */
