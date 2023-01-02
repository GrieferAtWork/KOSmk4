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
/* (#) Portability: MinGW        (/mingw-w64-headers/include/sal.h) */
/* (#) Portability: NetBSD       (/sys/arch/[...]/include/sal.h) */
/* (#) Portability: Windows Kits (/shared/sal.h) */
#ifndef _SAL_H
#define _SAL_H 1

#include "__stdinc.h"

/* NOTE: This header never ~really~ implements SAL. - It _always_ just acts as a stub. */

#define _Always_(annos)
#define _Always_impl_(annos)
#define _Analysis_assume_nullterminated_(x)
#define _Analysis_mode_(mode)
#define _Analysis_mode_impl_(mode)
#define _Analysis_noreturn_
#define _At_(target, annos)
#define _At_buffer_(target, iter, bound, annos)
#define _At_buffer_impl_(target, iter, bound, annos)
#define _At_impl_(target, annos)
#define _COM_Outptr_
#define _COM_Outptr_opt_
#define _COM_Outptr_opt_result_maybenull_
#define _COM_Outptr_result_maybenull_
#define _Called_from_function_class_(x)
#define _Check_return_impl_
#define _Const_
#define _Deref2_post1_impl_(p1)
#define _Deref2_pre1_impl_(p1)
#define _Deref2_pre_readonly_
#define _Deref2_ret1_impl_(p1)
#define _Deref_in_bound_
#define _Deref_in_bound_impl_
#define _Deref_in_range_(lb, ub)
#define _Deref_in_range_impl_(min, max)
#define _Deref_inout_bound_
#define _Deref_inout_z_
#define _Deref_inout_z_bytecap_c_(size)
#define _Deref_inout_z_cap_c_(size)
#define _Deref_opt_out_
#define _Deref_opt_out_opt_
#define _Deref_opt_out_opt_z_
#define _Deref_opt_out_z_
#define _Deref_out_
#define _Deref_out_bound_
#define _Deref_out_bound_impl_
#define _Deref_out_opt_
#define _Deref_out_opt_z_
#define _Deref_out_range_(lb, ub)
#define _Deref_out_range_impl_(min, max)
#define _Deref_out_z_
#define _Deref_out_z_bytecap_c_(size)
#define _Deref_out_z_cap_c_(size)
#define _Deref_post1_impl_(p1)
#define _Deref_post2_impl_(p1, p2)
#define _Deref_post3_impl_(p1, p2, p3)
#define _Deref_post_bytecap_(size)
#define _Deref_post_bytecap_c_(size)
#define _Deref_post_bytecap_x_(size)
#define _Deref_post_bytecount_(size)
#define _Deref_post_bytecount_c_(size)
#define _Deref_post_bytecount_x_(size)
#define _Deref_post_cap_(size)
#define _Deref_post_cap_c_(size)
#define _Deref_post_cap_x_(size)
#define _Deref_post_count_(size)
#define _Deref_post_count_c_(size)
#define _Deref_post_count_x_(size)
#define _Deref_post_maybenull_
#define _Deref_post_notnull_
#define _Deref_post_null_
#define _Deref_post_opt_bytecap_(size)
#define _Deref_post_opt_bytecap_c_(size)
#define _Deref_post_opt_bytecap_x_(size)
#define _Deref_post_opt_bytecount_(size)
#define _Deref_post_opt_bytecount_c_(size)
#define _Deref_post_opt_bytecount_x_(size)
#define _Deref_post_opt_cap_(size)
#define _Deref_post_opt_cap_c_(size)
#define _Deref_post_opt_cap_x_(size)
#define _Deref_post_opt_count_(size)
#define _Deref_post_opt_count_c_(size)
#define _Deref_post_opt_count_x_(size)
#define _Deref_post_opt_valid_
#define _Deref_post_opt_valid_bytecap_(size)
#define _Deref_post_opt_valid_bytecap_c_(size)
#define _Deref_post_opt_valid_bytecap_x_(size)
#define _Deref_post_opt_valid_cap_(size)
#define _Deref_post_opt_valid_cap_c_(size)
#define _Deref_post_opt_valid_cap_x_(size)
#define _Deref_post_opt_z_
#define _Deref_post_opt_z_bytecap_(size)
#define _Deref_post_opt_z_bytecap_c_(size)
#define _Deref_post_opt_z_bytecap_x_(size)
#define _Deref_post_opt_z_cap_(size)
#define _Deref_post_opt_z_cap_c_(size)
#define _Deref_post_opt_z_cap_x_(size)
#define _Deref_post_valid_
#define _Deref_post_valid_bytecap_(size)
#define _Deref_post_valid_bytecap_c_(size)
#define _Deref_post_valid_bytecap_x_(size)
#define _Deref_post_valid_cap_(size)
#define _Deref_post_valid_cap_c_(size)
#define _Deref_post_valid_cap_x_(size)
#define _Deref_post_z_
#define _Deref_post_z_bytecap_(size)
#define _Deref_post_z_bytecap_c_(size)
#define _Deref_post_z_bytecap_x_(size)
#define _Deref_post_z_cap_(size)
#define _Deref_post_z_cap_c_(size)
#define _Deref_post_z_cap_x_(size)
#define _Deref_pre1_impl_(p1)
#define _Deref_pre2_impl_(p1, p2)
#define _Deref_pre3_impl_(p1, p2, p3)
#define _Deref_pre_bytecap_(size)
#define _Deref_pre_bytecap_c_(size)
#define _Deref_pre_bytecap_x_(size)
#define _Deref_pre_bytecount_(size)
#define _Deref_pre_bytecount_c_(size)
#define _Deref_pre_bytecount_x_(size)
#define _Deref_pre_cap_(size)
#define _Deref_pre_cap_c_(size)
#define _Deref_pre_cap_x_(size)
#define _Deref_pre_count_(size)
#define _Deref_pre_count_c_(size)
#define _Deref_pre_count_x_(size)
#define _Deref_pre_invalid_
#define _Deref_pre_maybenull_
#define _Deref_pre_notnull_
#define _Deref_pre_null_
#define _Deref_pre_opt_bytecap_(size)
#define _Deref_pre_opt_bytecap_c_(size)
#define _Deref_pre_opt_bytecap_x_(size)
#define _Deref_pre_opt_bytecount_(size)
#define _Deref_pre_opt_bytecount_c_(size)
#define _Deref_pre_opt_bytecount_x_(size)
#define _Deref_pre_opt_cap_(size)
#define _Deref_pre_opt_cap_c_(size)
#define _Deref_pre_opt_cap_x_(size)
#define _Deref_pre_opt_count_(size)
#define _Deref_pre_opt_count_c_(size)
#define _Deref_pre_opt_count_x_(size)
#define _Deref_pre_opt_valid_
#define _Deref_pre_opt_valid_bytecap_(size)
#define _Deref_pre_opt_valid_bytecap_c_(size)
#define _Deref_pre_opt_valid_bytecap_x_(size)
#define _Deref_pre_opt_valid_cap_(size)
#define _Deref_pre_opt_valid_cap_c_(size)
#define _Deref_pre_opt_valid_cap_x_(size)
#define _Deref_pre_opt_z_
#define _Deref_pre_opt_z_bytecap_(size)
#define _Deref_pre_opt_z_bytecap_c_(size)
#define _Deref_pre_opt_z_bytecap_x_(size)
#define _Deref_pre_opt_z_cap_(size)
#define _Deref_pre_opt_z_cap_c_(size)
#define _Deref_pre_opt_z_cap_x_(size)
#define _Deref_pre_readonly_
#define _Deref_pre_valid_
#define _Deref_pre_valid_bytecap_(size)
#define _Deref_pre_valid_bytecap_c_(size)
#define _Deref_pre_valid_bytecap_x_(size)
#define _Deref_pre_valid_cap_(size)
#define _Deref_pre_valid_cap_c_(size)
#define _Deref_pre_valid_cap_x_(size)
#define _Deref_pre_writeonly_
#define _Deref_pre_z_
#define _Deref_pre_z_bytecap_(size)
#define _Deref_pre_z_bytecap_c_(size)
#define _Deref_pre_z_bytecap_x_(size)
#define _Deref_pre_z_cap_(size)
#define _Deref_pre_z_cap_c_(size)
#define _Deref_pre_z_cap_x_(size)
#define _Deref_prepost_bytecap_(size)
#define _Deref_prepost_bytecap_x_(size)
#define _Deref_prepost_bytecount_(size)
#define _Deref_prepost_bytecount_x_(size)
#define _Deref_prepost_cap_(size)
#define _Deref_prepost_cap_x_(size)
#define _Deref_prepost_count_(size)
#define _Deref_prepost_count_x_(size)
#define _Deref_prepost_opt_bytecap_(size)
#define _Deref_prepost_opt_bytecap_x_(size)
#define _Deref_prepost_opt_bytecount_(size)
#define _Deref_prepost_opt_bytecount_x_(size)
#define _Deref_prepost_opt_cap_(size)
#define _Deref_prepost_opt_cap_x_(size)
#define _Deref_prepost_opt_count_(size)
#define _Deref_prepost_opt_count_x_(size)
#define _Deref_prepost_opt_valid_
#define _Deref_prepost_opt_valid_bytecap_(size)
#define _Deref_prepost_opt_valid_bytecap_x_(size)
#define _Deref_prepost_opt_valid_cap_(size)
#define _Deref_prepost_opt_valid_cap_x_(size)
#define _Deref_prepost_opt_z_
#define _Deref_prepost_opt_z_bytecap_(size)
#define _Deref_prepost_opt_z_cap_(size)
#define _Deref_prepost_valid_
#define _Deref_prepost_valid_bytecap_(size)
#define _Deref_prepost_valid_bytecap_x_(size)
#define _Deref_prepost_valid_cap_(size)
#define _Deref_prepost_valid_cap_x_(size)
#define _Deref_prepost_z_
#define _Deref_prepost_z_bytecap_(size)
#define _Deref_prepost_z_cap_(size)
#define _Deref_ret1_impl_(p1)
#define _Deref_ret2_impl_(p1, p2)
#define _Deref_ret3_impl_(p1, p2, p3)
#define _Deref_ret_bound_
#define _Deref_ret_bound_impl_
#define _Deref_ret_opt_z_
#define _Deref_ret_range_(lb, ub)
#define _Deref_ret_range_impl_(min, max)
#define _Deref_ret_z_
#define _Enum_is_bitflag_
#define _Field_range_(min, max)
#define _Field_range_impl_(min, max)
#define _Field_size_(size)
#define _Field_size_bytes_(size)
#define _Field_size_bytes_full_(size)
#define _Field_size_bytes_full_opt_(size)
#define _Field_size_bytes_opt_(size)
#define _Field_size_bytes_part_(size, count)
#define _Field_size_bytes_part_opt_(size, count)
#define _Field_size_full_(size)
#define _Field_size_full_opt_(size)
#define _Field_size_opt_(size)
#define _Field_size_part_(size, count)
#define _Field_size_part_opt_(size, count)
#define _Field_z_
#define _Format_string_impl_(kind, where)
#define _Function_class_(x)
#define _GrouP_(annos)
#define _GrouP_impl_(annos)
#define _Group_(annos)
#define _Group_impl_(annos)
#define _In_
#define _In_bound_
#define _In_bound_impl_
#define _In_bytecount_(size)
#define _In_bytecount_c_(size)
#define _In_bytecount_x_(size)
#define _In_count_(size)
#define _In_count_c_(size)
#define _In_count_x_(size)
#define _In_defensive_(annotes)
#define _In_function_class_(x)
#define _In_opt_
#define _In_opt_bytecount_(size)
#define _In_opt_bytecount_c_(size)
#define _In_opt_bytecount_x_(size)
#define _In_opt_count_(size)
#define _In_opt_count_c_(size)
#define _In_opt_count_x_(size)
#define _In_opt_ptrdiff_count_(size)
#define _In_opt_z_
#define _In_opt_z_bytecount_(size)
#define _In_opt_z_bytecount_c_(size)
#define _In_opt_z_count_(size)
#define _In_opt_z_count_c_(size)
#define _In_ptrdiff_count_(size)
#define _In_range_(lb, ub)
#define _In_range_impl_(min, max)
#define _In_reads_(size)
#define _In_reads_bytes_(size)
#define _In_reads_bytes_opt_(size)
#define _In_reads_opt_(size)
#define _In_reads_opt_z_(size)
#define _In_reads_or_z_(size)
#define _In_reads_or_z_opt_(size)
#define _In_reads_to_ptr_(ptr)
#define _In_reads_to_ptr_opt_(ptr)
#define _In_reads_to_ptr_opt_z_(ptr)
#define _In_reads_to_ptr_z_(ptr)
#define _In_reads_z_(size)
#define _In_z_
#define _In_z_bytecount_(size)
#define _In_z_bytecount_c_(size)
#define _In_z_count_(size)
#define _In_z_count_c_(size)
#define _Inout_
#define _Inout_bytecap_(size)
#define _Inout_bytecap_c_(size)
#define _Inout_bytecap_x_(size)
#define _Inout_bytecount_(size)
#define _Inout_bytecount_c_(size)
#define _Inout_bytecount_x_(size)
#define _Inout_cap_(size)
#define _Inout_cap_c_(size)
#define _Inout_cap_x_(size)
#define _Inout_count_(size)
#define _Inout_count_c_(size)
#define _Inout_count_x_(size)
#define _Inout_defensive_(annotes)
#define _Inout_opt_
#define _Inout_opt_bytecap_(size)
#define _Inout_opt_bytecap_c_(size)
#define _Inout_opt_bytecap_x_(size)
#define _Inout_opt_bytecount_(size)
#define _Inout_opt_bytecount_c_(size)
#define _Inout_opt_bytecount_x_(size)
#define _Inout_opt_cap_(size)
#define _Inout_opt_cap_c_(size)
#define _Inout_opt_cap_x_(size)
#define _Inout_opt_count_(size)
#define _Inout_opt_count_c_(size)
#define _Inout_opt_count_x_(size)
#define _Inout_opt_ptrdiff_count_(size)
#define _Inout_opt_z_
#define _Inout_opt_z_bytecap_(size)
#define _Inout_opt_z_bytecap_c_(size)
#define _Inout_opt_z_bytecap_x_(size)
#define _Inout_opt_z_bytecount_(size)
#define _Inout_opt_z_bytecount_c_(size)
#define _Inout_opt_z_cap_(size)
#define _Inout_opt_z_cap_c_(size)
#define _Inout_opt_z_cap_x_(size)
#define _Inout_opt_z_count_(size)
#define _Inout_opt_z_count_c_(size)
#define _Inout_ptrdiff_count_(size)
#define _Inout_updates_(size)
#define _Inout_updates_all_(size)
#define _Inout_updates_all_opt_(size)
#define _Inout_updates_bytes_(size)
#define _Inout_updates_bytes_all_(size)
#define _Inout_updates_bytes_all_opt_(size)
#define _Inout_updates_bytes_opt_(size)
#define _Inout_updates_bytes_to_(size, count)
#define _Inout_updates_bytes_to_opt_(size, count)
#define _Inout_updates_opt_(size)
#define _Inout_updates_opt_z_(size)
#define _Inout_updates_to_(size, count)
#define _Inout_updates_to_opt_(size, count)
#define _Inout_updates_z_(size)
#define _Inout_z_
#define _Inout_z_bytecap_(size)
#define _Inout_z_bytecap_c_(size)
#define _Inout_z_bytecap_x_(size)
#define _Inout_z_bytecount_(size)
#define _Inout_z_bytecount_c_(size)
#define _Inout_z_cap_(size)
#define _Inout_z_cap_c_(size)
#define _Inout_z_cap_x_(size)
#define _Inout_z_count_(size)
#define _Inout_z_count_c_(size)
#define _Literal_
#define _Literal_impl_
#define _Maybe_raises_SEH_exception_
#define _Maybenull_
#define _Maybenull_impl_
#define _Maybevalid_
#define _Maybevalid_impl_
#define _Must_inspect_impl_
#define _Must_inspect_result_
#define _Notliteral_
#define _Notliteral_impl_
#define _Notnull_
#define _Notnull_impl_
#define _Notref_
#define _Notref_impl_
#define _Notvalid_
#define _Notvalid_impl_
#define _NullNull_terminated_
#define _NullNull_terminated_impl_
#define _Null_
#define _Null_impl_
#define _Null_terminated_
#define _Null_terminated_impl_
#define _On_failure_(annos)
#define _On_failure_impl_(annos)
#define _Out_
#define _Out_bound_
#define _Out_bound_impl_
#define _Out_bytecap_(size)
#define _Out_bytecap_c_(size)
#define _Out_bytecap_post_bytecount_(cap, count)
#define _Out_bytecap_x_(size)
#define _Out_bytecapcount_(capcount)
#define _Out_bytecapcount_x_(capcount)
#define _Out_cap_(size)
#define _Out_cap_c_(size)
#define _Out_cap_m_(mult, size)
#define _Out_cap_post_count_(cap, count)
#define _Out_cap_x_(size)
#define _Out_capcount_(capcount)
#define _Out_capcount_x_(capcount)
#define _Out_defensive_(annotes)
#define _Out_opt_
#define _Out_opt_bytecap_(size)
#define _Out_opt_bytecap_c_(size)
#define _Out_opt_bytecap_post_bytecount_(cap, count)
#define _Out_opt_bytecap_x_(size)
#define _Out_opt_bytecapcount_(capcount)
#define _Out_opt_bytecapcount_x_(capcount)
#define _Out_opt_cap_(size)
#define _Out_opt_cap_c_(size)
#define _Out_opt_cap_m_(mult, size)
#define _Out_opt_cap_post_count_(cap, count)
#define _Out_opt_cap_x_(size)
#define _Out_opt_capcount_(capcount)
#define _Out_opt_capcount_x_(capcount)
#define _Out_opt_ptrdiff_cap_(size)
#define _Out_opt_z_bytecap_(size)
#define _Out_opt_z_bytecap_c_(size)
#define _Out_opt_z_bytecap_post_bytecount_(cap, count)
#define _Out_opt_z_bytecap_x_(size)
#define _Out_opt_z_bytecapcount_(capcount)
#define _Out_opt_z_cap_(size)
#define _Out_opt_z_cap_c_(size)
#define _Out_opt_z_cap_m_(mult, size)
#define _Out_opt_z_cap_post_count_(cap, count)
#define _Out_opt_z_cap_x_(size)
#define _Out_opt_z_capcount_(capcount)
#define _Out_ptrdiff_cap_(size)
#define _Out_range_(lb, ub)
#define _Out_range_impl_(min, max)
#define _Out_writes_(size)
#define _Out_writes_all_(size)
#define _Out_writes_all_opt_(size)
#define _Out_writes_bytes_(size)
#define _Out_writes_bytes_all_(size)
#define _Out_writes_bytes_all_opt_(size)
#define _Out_writes_bytes_opt_(size)
#define _Out_writes_bytes_to_(size, count)
#define _Out_writes_bytes_to_opt_(size, count)
#define _Out_writes_opt_(size)
#define _Out_writes_opt_z_(size)
#define _Out_writes_to_(size, count)
#define _Out_writes_to_opt_(size, count)
#define _Out_writes_to_ptr_(ptr)
#define _Out_writes_to_ptr_opt_(ptr)
#define _Out_writes_to_ptr_opt_z_(ptr)
#define _Out_writes_to_ptr_z_(ptr)
#define _Out_writes_z_(size)
#define _Out_z_bytecap_(size)
#define _Out_z_bytecap_c_(size)
#define _Out_z_bytecap_post_bytecount_(cap, count)
#define _Out_z_bytecap_x_(size)
#define _Out_z_bytecapcount_(capcount)
#define _Out_z_cap_(size)
#define _Out_z_cap_c_(size)
#define _Out_z_cap_m_(mult, size)
#define _Out_z_cap_post_count_(cap, count)
#define _Out_z_cap_x_(size)
#define _Out_z_capcount_(capcount)
#define _Outptr_
#define _Outptr_opt_
#define _Outptr_opt_result_buffer_(size)
#define _Outptr_opt_result_buffer_all_(size)
#define _Outptr_opt_result_buffer_all_maybenull_(size)
#define _Outptr_opt_result_buffer_maybenull_(size)
#define _Outptr_opt_result_buffer_to_(size, count)
#define _Outptr_opt_result_buffer_to_maybenull_(size, count)
#define _Outptr_opt_result_bytebuffer_(size)
#define _Outptr_opt_result_bytebuffer_all_(size)
#define _Outptr_opt_result_bytebuffer_all_maybenull_(size)
#define _Outptr_opt_result_bytebuffer_maybenull_(size)
#define _Outptr_opt_result_bytebuffer_to_(size, count)
#define _Outptr_opt_result_bytebuffer_to_maybenull_(size, count)
#define _Outptr_opt_result_maybenull_
#define _Outptr_opt_result_maybenull_z_
#define _Outptr_opt_result_nullonfailure_
#define _Outptr_opt_result_z_
#define _Outptr_result_buffer_(size)
#define _Outptr_result_buffer_all_(size)
#define _Outptr_result_buffer_all_maybenull_(size)
#define _Outptr_result_buffer_maybenull_(size)
#define _Outptr_result_buffer_to_(size, count)
#define _Outptr_result_buffer_to_maybenull_(size, count)
#define _Outptr_result_bytebuffer_(size)
#define _Outptr_result_bytebuffer_all_(size)
#define _Outptr_result_bytebuffer_all_maybenull_(size)
#define _Outptr_result_bytebuffer_maybenull_(size)
#define _Outptr_result_bytebuffer_to_(size, count)
#define _Outptr_result_bytebuffer_to_maybenull_(size, count)
#define _Outptr_result_maybenull_
#define _Outptr_result_maybenull_z_
#define _Outptr_result_nullonfailure_
#define _Outptr_result_z_
#define _Outref_
#define _Outref_result_buffer_(size)
#define _Outref_result_buffer_all_(size)
#define _Outref_result_buffer_all_maybenull_(size)
#define _Outref_result_buffer_maybenull_(size)
#define _Outref_result_buffer_to_(size, count)
#define _Outref_result_buffer_to_maybenull_(size, count)
#define _Outref_result_bytebuffer_(size)
#define _Outref_result_bytebuffer_all_(size)
#define _Outref_result_bytebuffer_all_maybenull_(size)
#define _Outref_result_bytebuffer_maybenull_(size)
#define _Outref_result_bytebuffer_to_(size, count)
#define _Outref_result_bytebuffer_to_maybenull_(size, count)
#define _Outref_result_maybenull_
#define _Outref_result_nullonfailure_
#define _Points_to_data_
#define _Points_to_data_impl_
#define _Post1_impl_(p1)
#define _Post2_impl_(p1, p2)
#define _Post3_impl_(p1, p2, p3)
#define _Post_
#define _Post_bytecap_(size)
#define _Post_bytecount_(size)
#define _Post_bytecount_c_(size)
#define _Post_bytecount_x_(size)
#define _Post_cap_(size)
#define _Post_count_(size)
#define _Post_count_c_(size)
#define _Post_count_x_(size)
#define _Post_defensive_
#define _Post_equal_to_(expr)
#define _Post_impl_
#define _Post_invalid_
#define _Post_maybenull_
#define _Post_maybez_
#define _Post_notnull_
#define _Post_null_
#define _Post_ptr_invalid_
#define _Post_readable_byte_size_(size)
#define _Post_readable_size_(size)
#define _Post_satisfies_(cond)
#define _Post_satisfies_impl_(expr)
#define _Post_valid_
#define _Post_valid_impl_
#define _Post_writable_byte_size_(size)
#define _Post_writable_size_(size)
#define _Post_z_
#define _Post_z_bytecount_(size)
#define _Post_z_bytecount_c_(size)
#define _Post_z_bytecount_x_(size)
#define _Post_z_count_(size)
#define _Post_z_count_c_(size)
#define _Post_z_count_x_(size)
#define _Pre1_impl_(p1)
#define _Pre2_impl_(p1, p2)
#define _Pre3_impl_(p1, p2, p3)
#define _Pre_
#define _Pre_bytecap_(size)
#define _Pre_bytecap_c_(size)
#define _Pre_bytecap_x_(size)
#define _Pre_bytecount_(size)
#define _Pre_bytecount_c_(size)
#define _Pre_bytecount_x_(size)
#define _Pre_cap_(size)
#define _Pre_cap_c_(size)
#define _Pre_cap_c_one_
#define _Pre_cap_for_(param)
#define _Pre_cap_m_(mult, size)
#define _Pre_cap_x_(size)
#define _Pre_count_(size)
#define _Pre_count_c_(size)
#define _Pre_count_x_(size)
#define _Pre_defensive_
#define _Pre_equal_to_(expr)
#define _Pre_impl_
#define _Pre_invalid_
#define _Pre_maybenull_
#define _Pre_notnull_
#define _Pre_null_
#define _Pre_opt_bytecap_(size)
#define _Pre_opt_bytecap_c_(size)
#define _Pre_opt_bytecap_x_(size)
#define _Pre_opt_bytecount_(size)
#define _Pre_opt_bytecount_c_(size)
#define _Pre_opt_bytecount_x_(size)
#define _Pre_opt_cap_(size)
#define _Pre_opt_cap_c_(size)
#define _Pre_opt_cap_c_one_
#define _Pre_opt_cap_for_(param)
#define _Pre_opt_cap_m_(mult, size)
#define _Pre_opt_cap_x_(size)
#define _Pre_opt_count_(size)
#define _Pre_opt_count_c_(size)
#define _Pre_opt_count_x_(size)
#define _Pre_opt_ptrdiff_cap_(ptr)
#define _Pre_opt_ptrdiff_count_(ptr)
#define _Pre_opt_valid_
#define _Pre_opt_valid_bytecap_(size)
#define _Pre_opt_valid_bytecap_c_(size)
#define _Pre_opt_valid_bytecap_x_(size)
#define _Pre_opt_valid_cap_(size)
#define _Pre_opt_valid_cap_c_(size)
#define _Pre_opt_valid_cap_x_(size)
#define _Pre_opt_z_
#define _Pre_opt_z_bytecap_(size)
#define _Pre_opt_z_bytecap_c_(size)
#define _Pre_opt_z_bytecap_x_(size)
#define _Pre_opt_z_cap_(size)
#define _Pre_opt_z_cap_c_(size)
#define _Pre_opt_z_cap_x_(size)
#define _Pre_ptrdiff_cap_(ptr)
#define _Pre_ptrdiff_count_(ptr)
#define _Pre_readable_byte_size_(size)
#define _Pre_readable_size_(size)
#define _Pre_readonly_
#define _Pre_satisfies_(cond)
#define _Pre_satisfies_impl_(expr)
#define _Pre_unknown_
#define _Pre_valid_
#define _Pre_valid_bytecap_(size)
#define _Pre_valid_bytecap_c_(size)
#define _Pre_valid_bytecap_x_(size)
#define _Pre_valid_cap_(size)
#define _Pre_valid_cap_c_(size)
#define _Pre_valid_cap_x_(size)
#define _Pre_valid_impl_
#define _Pre_writable_byte_size_(size)
#define _Pre_writable_size_(size)
#define _Pre_writeonly_
#define _Pre_z_
#define _Pre_z_bytecap_(size)
#define _Pre_z_bytecap_c_(size)
#define _Pre_z_bytecap_x_(size)
#define _Pre_z_cap_(size)
#define _Pre_z_cap_c_(size)
#define _Pre_z_cap_x_(size)
#define _Prepost_bytecount_(size)
#define _Prepost_bytecount_c_(size)
#define _Prepost_bytecount_x_(size)
#define _Prepost_count_(size)
#define _Prepost_count_c_(size)
#define _Prepost_count_x_(size)
#define _Prepost_opt_bytecount_(size)
#define _Prepost_opt_bytecount_c_(size)
#define _Prepost_opt_bytecount_x_(size)
#define _Prepost_opt_count_(size)
#define _Prepost_opt_count_c_(size)
#define _Prepost_opt_count_x_(size)
#define _Prepost_opt_valid_
#define _Prepost_opt_z_
#define _Prepost_valid_
#define _Prepost_z_
#define _Printf_format_string_
#define _Printf_format_string_impl_
#define _Printf_format_string_params_(x)
#define _Raises_SEH_exception_
#define _Range_impl_(min, max)
#define _Readable_bytes_(size)
#define _Readable_bytes_impl_(size)
#define _Readable_elements_(size)
#define _Readable_elements_impl_(size)
#define _Reserved_
#define _Result_nullonfailure_
#define _Result_zeroonfailure_
#define _Ret1_impl_(p1)
#define _Ret2_impl_(p1, p2)
#define _Ret3_impl_(p1, p2, p3)
#define _Ret_
#define _Ret_bound_
#define _Ret_bound_impl_
#define _Ret_bytecap_(size)
#define _Ret_bytecap_c_(size)
#define _Ret_bytecap_x_(size)
#define _Ret_bytecount_(size)
#define _Ret_bytecount_c_(size)
#define _Ret_bytecount_x_(size)
#define _Ret_cap_(size)
#define _Ret_cap_c_(size)
#define _Ret_cap_x_(size)
#define _Ret_count_(size)
#define _Ret_count_c_(size)
#define _Ret_count_x_(size)
#define _Ret_maybenull_
#define _Ret_maybenull_z_
#define _Ret_notnull_
#define _Ret_null_
#define _Ret_opt_
#define _Ret_opt_bytecap_(size)
#define _Ret_opt_bytecap_c_(size)
#define _Ret_opt_bytecap_x_(size)
#define _Ret_opt_bytecount_(size)
#define _Ret_opt_bytecount_c_(size)
#define _Ret_opt_bytecount_x_(size)
#define _Ret_opt_cap_(size)
#define _Ret_opt_cap_c_(size)
#define _Ret_opt_cap_x_(size)
#define _Ret_opt_count_(size)
#define _Ret_opt_count_c_(size)
#define _Ret_opt_count_x_(size)
#define _Ret_opt_valid_
#define _Ret_opt_z_
#define _Ret_opt_z_bytecap_(size)
#define _Ret_opt_z_bytecount_(size)
#define _Ret_opt_z_cap_(size)
#define _Ret_opt_z_count_(size)
#define _Ret_range_(lb, ub)
#define _Ret_range_impl_(min, max)
#define _Ret_valid_
#define _Ret_valid_impl_
#define _Ret_writes_(size)
#define _Ret_writes_bytes_(size)
#define _Ret_writes_bytes_maybenull_(size)
#define _Ret_writes_bytes_to_(size, count)
#define _Ret_writes_bytes_to_maybenull_(size, count)
#define _Ret_writes_maybenull_(size)
#define _Ret_writes_maybenull_z_(size)
#define _Ret_writes_to_(size, count)
#define _Ret_writes_to_maybenull_(size, count)
#define _Ret_writes_z_(size)
#define _Ret_z_
#define _Ret_z_bytecap_(size)
#define _Ret_z_bytecount_(size)
#define _Ret_z_cap_(size)
#define _Ret_z_count_(size)
#define _Return_type_success_(expr)
#define _SAL_nop_impl_ X
#define _SA_annotes0(n)
#define _SA_annotes1(n, pp1)
#define _SA_annotes2(n, pp1, pp2)
#define _SA_annotes3(n, pp1, pp2, pp3)
#define _Satisfies_impl_(expr)
#define _Scanf_format_string_
#define _Scanf_format_string_impl_
#define _Scanf_format_string_params_(x)
#define _Scanf_s_format_string_
#define _Scanf_s_format_string_impl_
#define _Scanf_s_format_string_params_(x)
#define _Strict_type_match_
#define _Struct_size_bytes_(size)
#define _Success_(expr)
#define _Success_impl_(expr)
#define _Unchanged_(e)
#define _Use_decl_anno_impl_
#define _Use_decl_annotations_
#define _Valid_
#define _Valid_impl_
#define _When_(expr, annos)
#define _When_impl_(expr, annos)
#define _Writable_bytes_(size)
#define _Writable_bytes_impl_(size)
#define _Writable_elements_(size)
#define _Writable_elements_impl_(size)
#define __ANNOTATION(fun)
#define __PRIMOP(type, fun)
#define __QUALIFIER(type, fun)
#define __bcount(size)
#define __bcount_opt(size)
#define __blocksOn(resource)
#define __byte_readableTo(size)
#define __byte_writableTo(size)
#define __callback
#define __checkReturn
#define __control_entrypoint(category)
#define __data_entrypoint(category)
#define __deref
#define __deref_bcount(size)
#define __deref_bcount_opt(size)
#define __deref_ecount(size)
#define __deref_ecount_opt(size)
#define __deref_inout
#define __deref_inout_bcount(size)
#define __deref_inout_bcount_full(size)
#define __deref_inout_bcount_full_opt(size)
#define __deref_inout_bcount_nz(size)
#define __deref_inout_bcount_nz_opt(size)
#define __deref_inout_bcount_opt(size)
#define __deref_inout_bcount_part(size, length)
#define __deref_inout_bcount_part_opt(size, length)
#define __deref_inout_bcount_z(size)
#define __deref_inout_bcount_z_opt(size)
#define __deref_inout_ecount(size)
#define __deref_inout_ecount_full(size)
#define __deref_inout_ecount_full_opt(size)
#define __deref_inout_ecount_nz(size)
#define __deref_inout_ecount_nz_opt(size)
#define __deref_inout_ecount_opt(size)
#define __deref_inout_ecount_part(size, length)
#define __deref_inout_ecount_part_opt(size, length)
#define __deref_inout_ecount_z(size)
#define __deref_inout_ecount_z_opt(size)
#define __deref_inout_nz
#define __deref_inout_nz_opt
#define __deref_inout_opt
#define __deref_inout_z
#define __deref_inout_z_opt
#define __deref_opt_bcount(size)
#define __deref_opt_bcount_opt(size)
#define __deref_opt_ecount(size)
#define __deref_opt_ecount_opt(size)
#define __deref_opt_inout
#define __deref_opt_inout_bcount(size)
#define __deref_opt_inout_bcount_full(size)
#define __deref_opt_inout_bcount_full_opt(size)
#define __deref_opt_inout_bcount_nz(size)
#define __deref_opt_inout_bcount_nz_opt(size)
#define __deref_opt_inout_bcount_opt(size)
#define __deref_opt_inout_bcount_part(size, length)
#define __deref_opt_inout_bcount_part_opt(size, length)
#define __deref_opt_inout_bcount_z(size)
#define __deref_opt_inout_bcount_z_opt(size)
#define __deref_opt_inout_ecount(size)
#define __deref_opt_inout_ecount_full(size)
#define __deref_opt_inout_ecount_full_opt(size)
#define __deref_opt_inout_ecount_nz(size)
#define __deref_opt_inout_ecount_nz_opt(size)
#define __deref_opt_inout_ecount_opt(size)
#define __deref_opt_inout_ecount_part(size, length)
#define __deref_opt_inout_ecount_part_opt(size, length)
#define __deref_opt_inout_ecount_z(size)
#define __deref_opt_inout_ecount_z_opt(size)
#define __deref_opt_inout_nz
#define __deref_opt_inout_nz_opt
#define __deref_opt_inout_opt
#define __deref_opt_inout_z
#define __deref_opt_inout_z_opt
#define __deref_opt_out
#define __deref_opt_out_bcount(size)
#define __deref_opt_out_bcount_full(size)
#define __deref_opt_out_bcount_full_opt(size)
#define __deref_opt_out_bcount_nz_opt(size)
#define __deref_opt_out_bcount_opt(size)
#define __deref_opt_out_bcount_part(size, length)
#define __deref_opt_out_bcount_part_opt(size, length)
#define __deref_opt_out_bcount_z_opt(size)
#define __deref_opt_out_ecount(size)
#define __deref_opt_out_ecount_full(size)
#define __deref_opt_out_ecount_full_opt(size)
#define __deref_opt_out_ecount_nz_opt(size)
#define __deref_opt_out_ecount_opt(size)
#define __deref_opt_out_ecount_part(size, length)
#define __deref_opt_out_ecount_part_opt(size, length)
#define __deref_opt_out_ecount_z_opt(size)
#define __deref_opt_out_nz_opt
#define __deref_opt_out_opt
#define __deref_opt_out_z
#define __deref_opt_out_z_opt
#define __deref_out
#define __deref_out_bcount(size)
#define __deref_out_bcount_full(size)
#define __deref_out_bcount_full_opt(size)
#define __deref_out_bcount_nz(size)
#define __deref_out_bcount_nz_opt(size)
#define __deref_out_bcount_opt(size)
#define __deref_out_bcount_part(size, length)
#define __deref_out_bcount_part_opt(size, length)
#define __deref_out_bcount_z(size)
#define __deref_out_bcount_z_opt(size)
#define __deref_out_ecount(size)
#define __deref_out_ecount_full(size)
#define __deref_out_ecount_full_opt(size)
#define __deref_out_ecount_nz(size)
#define __deref_out_ecount_nz_opt(size)
#define __deref_out_ecount_opt(size)
#define __deref_out_ecount_part(size, length)
#define __deref_out_ecount_part_opt(size, length)
#define __deref_out_ecount_z(size)
#define __deref_out_ecount_z_opt(size)
#define __deref_out_nz
#define __deref_out_nz_opt
#define __deref_out_opt
#define __deref_out_z
#define __deref_out_z_opt
#define __ecount(size)
#define __ecount_opt(size)
#define __elem_readableTo(size)
#define __elem_writableTo(size)
#define __exceptthat
#define __format_string
#define __in
#define __in_bcount(size)
#define __in_bcount_nz(size)
#define __in_bcount_nz_opt(size)
#define __in_bcount_opt(size)
#define __in_bcount_z(size)
#define __in_bcount_z_opt(size)
#define __in_ecount(size)
#define __in_ecount_nz(size)
#define __in_ecount_nz_opt(size)
#define __in_ecount_opt(size)
#define __in_ecount_z(size)
#define __in_ecount_z_opt(size)
#define __in_nz
#define __in_nz_opt
#define __in_opt
#define __in_z
#define __in_z_opt
#define __inexpressible_readableTo(size)
#define __inexpressible_writableTo(size)
#define __inner_blocksOn(resource)
#define __inner_callback
#define __inner_control_entrypoint(category)
#define __inner_data_entrypoint(category)
#define __inner_exceptthat
#define __inner_fallthrough
#define __inner_fallthrough_dec
#define __inner_override
#define __inner_typefix(ctype)
#define __inout
#define __inout_bcount(size)
#define __inout_bcount_full(size)
#define __inout_bcount_full_opt(size)
#define __inout_bcount_nz(size)
#define __inout_bcount_nz_opt(size)
#define __inout_bcount_opt(size)
#define __inout_bcount_part(size, length)
#define __inout_bcount_part_opt(size, length)
#define __inout_bcount_z(size)
#define __inout_bcount_z_opt(size)
#define __inout_ecount(size)
#define __inout_ecount_full(size)
#define __inout_ecount_full_opt(size)
#define __inout_ecount_nz(size)
#define __inout_ecount_nz_opt(size)
#define __inout_ecount_opt(size)
#define __inout_ecount_part(size, length)
#define __inout_ecount_part_opt(size, length)
#define __inout_ecount_z(size)
#define __inout_ecount_z_opt(size)
#define __inout_ecount_z_opt(size)
#define __inout_nz
#define __inout_nz_opt
#define __inout_opt
#define __inout_z
#define __inout_z_opt
#define __maybenull
#define __maybereadonly
#define __maybevalid
#define __notnull
#define __notreadonly
#define __notvalid
#define __null
#define __nullnullterminated
#define __nullterminated
#define __on_failure(annotes)
#define __out
#define __out_bcount(size)
#define __out_bcount_full(size)
#define __out_bcount_full_opt(size)
#define __out_bcount_full_z(size)
#define __out_bcount_full_z_opt(size)
#define __out_bcount_nz(size)
#define __out_bcount_nz_opt(size)
#define __out_bcount_opt(size)
#define __out_bcount_part(size, length)
#define __out_bcount_part_opt(size, length)
#define __out_bcount_part_z(size, length)
#define __out_bcount_part_z_opt(size, length)
#define __out_bcount_z(size)
#define __out_bcount_z_opt(size)
#define __out_ecount(size)
#define __out_ecount_full(size)
#define __out_ecount_full_opt(size)
#define __out_ecount_full_z(size)
#define __out_ecount_full_z_opt(size)
#define __out_ecount_nz(size)
#define __out_ecount_nz_opt(size)
#define __out_ecount_opt(size)
#define __out_ecount_part(size, length)
#define __out_ecount_part_opt(size, length)
#define __out_ecount_part_z(size, length)
#define __out_ecount_part_z_opt(size, length)
#define __out_ecount_z(size)
#define __out_ecount_z_opt(size)
#define __out_nz
#define __out_nz_opt
#define __out_opt
#define __out_z
#define __out_z_opt
#define __override
#define __post
#define __post_deref_except_maybenull
#define __post_except_maybenull
#define __postcond(expr)
#define __pre
#define __pre_deref_except_maybenull
#define __pre_except_maybenull
#define __precond(expr)
#define __readableTo(extent)
#define __readonly
#define __refparam
#define __reserved
#define __specstrings
#define __success(expr)
#define __typefix(ctype)
#define __useHeader
#define __valid
#define __writableTo(size)

#define _SAL1_Source_(Name, args, annotes)
#define _SAL1_1_Source_(Name, args, annotes)
#define _SAL1_2_Source_(Name, args, annotes)
#define _SAL2_Source_(Name, args, annotes)
#define _SAL_L_Source_(Name, args, annotes)


//#define __GENSYM(x) __MKID(x,__COUNTER__)
//#define     __MKID(x,y)      ___MKID(x,y)
//#define ___MKID(x,y) x##y

#define _Check_return_ __ATTR_WUNUSED
#ifndef __nothrow
#define __nothrow __ATTR_NOTHROW
#endif /* !__nothrow */
#ifndef __fallthrough
#define __fallthrough
#endif /* !__fallthrough */
#ifndef __analysis_assume
#define __analysis_assume(expr)
#endif /* !__analysis_assume */
#ifndef _Analysis_assume_
#define _Analysis_assume_(expr)
#endif /* !_Analysis_assume_ */

#include "ConcurrencySal.h"

#endif /* !_SAL_H */
