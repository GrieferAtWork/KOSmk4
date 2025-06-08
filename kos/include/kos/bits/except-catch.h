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
/*!replace_with_include <kos/except.h>*/
#ifndef _KOS_BITS_EXCEPT_CATCH_H
#define _KOS_BITS_EXCEPT_CATCH_H 1

#include <kos/bits/exception_data.h>
#include <kos/except/codes.h>

#if defined(__cplusplus) || defined(__DEEMON__)
#include <__stdcxx.h>
#include <hybrid/pp/__va_nargs.h>

__CXXDECL_BEGIN

/* Support for filtered catch expressions */
namespace kos {namespace except {

/* These are the declarations of the magic, special types that
 * the KOS kernel and libc recognize as filtered KOS exception
 * handlers, when used in c++ `catch' statements.
 *
 * The magic here lies in the names of the c++ typeinfo() class
 * names  that end up  getting encoded into `.gcc_except_table'
 * when these are used:
 *
 * - f"N3kos6except12class_filterIL{_CXX_TEMPLATE_ARG_Un(sizeof(__except_class_t))}{_Class}EEE"
 * - f"N3kos6except11code_filterIL{_CXX_TEMPLATE_ARG_Un(sizeof(__except_code_t))}{_Code}EEE"
 *
 * These special type names are then recognized by libc's impl
 * for  `__gxx_personality_v0', which then treats them as only
 * being able to handle exceptions of the matching code/class.
 *
 * As such:
 * - The names (including namespace prefixes) here are part of the ABI
 * - There is no compile-time link between these class definitions
 *   here, and libc detecting catch-handlers for them at  runtime.
 */
template<__except_class_t _Class> class class_filter { };
template<__except_code_t _Code>
class code_filter: public class_filter<EXCEPT_CLASS(_Code)> { };


/* TODO: Instantiate "code_filter" to expand  to the sub-class fields  of
 *       the surrounding exception data (but still include leading fields
 *       from the base class):
 * >> template<> class code_filter<EXCEPT_CODEOF(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY)> {
 * >>     __syscall_ulong_t / *size_t* / ihm_num_bytes; / * The number of bytes that could not be allocated * /
 * >> };
 * >> ...
 */

/* Specialize exception filters to include exception argument information.
 * libc/kernel  will set-up the exception object's address as a pointer to
 * `&except_data()->e_args',  which  means `union exception_data_pointers'
 * can be used to interpret data.
 *
 * But since we can overload filters based on the selected exception code,
 * we can do even better than `union exception_data_pointers', by  instead
 * linking only the relevant exception data container! */

/*[[[deemon (printExceptionClassFilterSpecifications from ....misc.libgen.exceptinfo)(); ]]]*/
template<> class class_filter<E_BADALLOC>: public ::exception_badalloc_data { };
template<> class class_filter<E_BUFFER_TOO_SMALL>: public ::exception_buffer_too_small_data { };
template<> class class_filter<E_EXIT_PROCESS>: public ::exception_exit_process_data { };
template<> class class_filter<E_EXIT_THREAD>: public ::exception_exit_thread_data { };
template<> class class_filter<E_FSERROR>: public ::exception_fserror_data { };
#if !defined(__i386__) && !defined(__x86_64__)
template<> class class_filter<E_ILLEGAL_INSTRUCTION>: public ::exception_illegal_instruction_data { };
#endif /* !__i386__ && !__x86_64__ */
#if defined(__i386__) || defined(__x86_64__)
template<> class class_filter<E_ILLEGAL_INSTRUCTION>: public ::exception_illegal_instruction_data { };
#endif /* __i386__ || __x86_64__ */
template<> class class_filter<E_ILLEGAL_OPERATION>: public ::exception_illegal_operation_data { };
template<> class class_filter<E_INDEX_ERROR>: public ::exception_index_error_data { };
template<> class class_filter<E_INSUFFICIENT_RIGHTS>: public ::exception_insufficient_rights_data { };
template<> class class_filter<E_INVALID_ARGUMENT>: public ::exception_invalid_argument_data { };
template<> class class_filter<E_INVALID_HANDLE>: public ::exception_invalid_handle_data { };
template<> class class_filter<E_IOERROR>: public ::exception_ioerror_data { };
template<> class class_filter<E_NET_ERROR>: public ::exception_net_error_data { };
template<> class class_filter<E_NOT_EXECUTABLE>: public ::exception_not_executable_data { };
template<> class class_filter<E_NO_DEVICE>: public ::exception_no_device_data { };
template<> class class_filter<E_PROCESS_EXITED>: public ::exception_process_exited_data { };
template<> class class_filter<E_SEGFAULT>: public ::exception_segfault_data { };
template<> class class_filter<E_UNHANDLED_INTERRUPT>: public ::exception_unhandled_interrupt_data { };
template<> class class_filter<E_UNKNOWN_SYSTEMCALL>: public ::exception_unknown_systemcall_data { };
/*[[[end]]]*/

}} /* namespace... */

#ifdef __HYBRID_PP_VA_NARGS
#define __PRIVATE_EXCEPT_CXX_FILTER_CODE1(class)           ::kos::except::class_filter<(class)>
#define __PRIVATE_EXCEPT_CXX_FILTER_CODE2(class, subclass) ::kos::except::code_filter<(EXCEPT_CODE(class, subclass))>
#define __PRIVATE_EXCEPT_CXX_FILTER_CODEN2(n)   __PRIVATE_EXCEPT_CXX_FILTER_CODE##n
#define __PRIVATE_EXCEPT_CXX_FILTER_CODEN(n)    __PRIVATE_EXCEPT_CXX_FILTER_CODEN2(n)
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __PRIVATE_EXCEPT_CXX_FILTER_CODE(...)   __PRIVATE_EXCEPT_CXX_FILTER_CODEN(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __PRIVATE_EXCEPT_CXX_FILTER_CODE(args...) __PRIVATE_EXCEPT_CXX_FILTER_CODEN(__HYBRID_PP_VA_NARGS(args))(args)
#endif /* ... */

#define __PRIVATE_CATCH_1(class_or_code)     catch (__PRIVATE_EXCEPT_CXX_FILTER_CODE class_or_code)
#define __PRIVATE_CATCH_2(class_or_code, as) catch (__PRIVATE_EXCEPT_CXX_FILTER_CODE class_or_code const &as)
#define __PRIVATE_CATCHN2(n) __PRIVATE_CATCH_##n
#define __PRIVATE_CATCHN(n)  __PRIVATE_CATCHN2(n)

/* Usage:
 * >> TRY {
 * >>     foo();
 * >> } CATCH (E_BADALLOC) {
 * >>     printf("Oh no! Out of memory!\n");
 * >>     RETHROW();
 * >> } CATCH (E_INVALID_ARGUMENT, e) {
 * >>     printf("that's a bad argument: %u\n", (unsigned int)e.ia_context);
 * >> } */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CATCH(...)     __PRIVATE_CATCHN(__HYBRID_PP_VA_NARGS(__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CATCH(args...) __PRIVATE_CATCHN(__HYBRID_PP_VA_NARGS(args))(args)
#endif /* ... */
#endif /* __HYBRID_PP_VA_NARGS */

__CXXDECL_END
#endif /* __cplusplus */


#endif /* !_KOS_BITS_EXCEPT_CATCH_H */
