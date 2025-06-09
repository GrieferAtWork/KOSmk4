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
#ifndef GUARD_LIBC_HYBRID_EXCEPT_C
#define GUARD_LIBC_HYBRID_EXCEPT_C 1

#include "../api.h"
/**/

#include <kos/bits/except-register-state-helpers.h>
#include <kos/bits/except-register-state.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unwind.h>

#include "except.h"

/* User-/Kernel-space hybrid exception API. */

#ifdef __KERNEL__
#include <kernel/except.h>
#include <kernel/arch/syslog.h>
#else /* __KERNEL__ */
#include "../libc/except.h" /* For optimized exception info access. */
#endif /* !__KERNEL__ */

#include "../libc/assert.h"

#ifdef __CC__
DECL_BEGIN

#ifndef SECTION_EXCEPT_TEXT
#define SECTION_EXCEPT_TEXT    /* nothing */
#endif /* !SECTION_EXCEPT_TEXT */
#ifndef SECTION_EXCEPT_DATA
#define SECTION_EXCEPT_DATA    /* nothing */
#endif /* !SECTION_EXCEPT_DATA */
#ifndef SECTION_EXCEPT_BSS
#define SECTION_EXCEPT_BSS     /* nothing */
#endif /* !SECTION_EXCEPT_BSS */
#ifndef SECTION_EXCEPT_RODATA
#define SECTION_EXCEPT_RODATA  /* nothing */
#endif /* !SECTION_EXCEPT_RODATA */
#ifndef SECTION_EXCEPT_STRING
#define SECTION_EXCEPT_STRING  /* nothing */
#endif /* !SECTION_EXCEPT_STRING */



/* [ 1] TRY {
 * [ 2]     foo();
 * [ 3] } EXCEPT {
 * [ 4]     NESTED_TRY {
 * [ 5]         bar();
 * [ 6]     } EXCEPT {
 * [ 7]         foobar();
 * [ 8]         RETHROW();
 * [ 9]     }
 * [10]     RETHROW();
 * [11] }
 *
 * Equivalent:
 * >> foo();                                // [ 2]
 * >> if (EXCEPTION_THROWN) {
 * >>     __cxa_begin_catch();              // [ 3]
 * >>     struct _exception_nesting_data nest;
 * >>     except_nesting_begin(&nest);
 * >>     bar();                            // [ 5]
 * >>     if (EXCEPTION_THROWN) {
 * >>         __cxa_begin_catch();          // [ 6]
 * >>         foobar();                     // [ 7]
 * >>         except_rethrow();             // [ 8]
 * >>         __cxa_end_catch();            // [ 9]
 * >>         except_nesting_end(&nest);
 * >>     } else {
 * >>         except_nesting_end(&nest);
 * >>         except_rethrow();             // [10]
 * >>     }
 * >>     __cxa_end_catch();                // [11]
 * >> }
 */

/* Only export  __cxa_* functions  as weak  in user-space,  such  that
 * libstdc++ can override them, should that library end up being used. */
#ifdef __KERNEL__
DEFINE_PUBLIC_ALIAS(__cxa_begin_catch, libc_cxa_begin_catch);
DEFINE_PUBLIC_ALIAS(__cxa_end_catch, libc_cxa_end_catch);
#else /* __KERNEL__ */
DEFINE_PUBLIC_WEAK_ALIAS(__cxa_begin_catch, libc_cxa_begin_catch);
DEFINE_PUBLIC_WEAK_ALIAS(__cxa_end_catch, libc_cxa_end_catch);
#endif /* !__KERNEL__ */

INTERN SECTION_EXCEPT_TEXT ATTR_CONST void *CXA_CC
libc_cxa_begin_catch(cxa_unwind_exception_t *ptr) {
	/* This function returns the address that would
	 * be assigned to the exception storage object:
	 * >> try {
	 * >>     ...
	 * >> } catch (MyException &exc) {
	 * >>     printk("exc @ %p\n", &exc); // Prints the address that this function returns.
	 * >> }
	 * The given `ptr' is what `libc_except_unwind()' originally set as value
	 * for the `CFI_UNWIND_REGISTER_EXCEPTION' register. */
#ifndef NDEBUG
	struct exception_info *info;
	info = except_info();
	assertf(info->ei_code != E_OK || info->ei_nesting != 0,
	        "Exception handler entered, but no exception set");
#ifdef __KERNEL__
	assertf(ptr == (void *)&info->ei_data.e_args,
	        "Exception pointer should be the exception data-area");
#else /* __KERNEL__ */
	assertf(ptr == (void *)&info->ei_data.e_args,
	        "Exception pointer should be ");
#endif /* !__KERNEL__ */
#if defined(__KERNEL__) && 0
	x86_syslog_printf("%%{vinfo:/os/kernel.bin:%p:%p:%%f(%%l,%%c) : %%n : %%p} : %p : "
	                  "__cxa_begin_catch [%#" PRIx8 "] [error=%s ("
	                  "%.4" PRIxN(__SIZEOF_EXCEPT_CLASS_T__) ":"
	                  "%.4" PRIxN(__SIZEOF_EXCEPT_SUBCLASS_T__) ")]\n",
	                  __builtin_return_address(0),
	                  __builtin_return_address(0),
	                  THIS_TASK,
	                  info->ei_flags,
	                  except_name(info->ei_code),
	                  EXCEPT_CLASS(info->ei_code),
	                  EXCEPT_SUBCLASS(info->ei_code));
#endif
#endif /* !NDEBUG */
#ifdef __KERNEL__
	/* In the kernel, "ptr" */
	return ptr;
#else /* __KERNEL__ */

	return except_args();
#endif /* !__KERNEL__ */
}

INTERN SECTION_EXCEPT_TEXT void CXA_CC
libc_cxa_end_catch(void) {
	/* This  function is called  at the end  of any user-defined catch-block
	 * (that isn't noexcept), similar to how `__cxa_begin_catch()' is always
	 * called at the start:
	 * >> try {
	 * >>     ...
	 * >> } catch (MyException) {
	 * >>     MyException &exc = *__cxa_begin_catch(?);
	 * >>     try {
	 * >>         printk("exc @ %p\n", &exc);
	 * >>     } finally {
	 * >>         __cxa_end_catch();
	 * >>     }
	 * >> }
	 * Looking at this, you should realize that it is therefor guarantied that
	 * every call to `__cxa_begin_catch()' is followed by `__cxa_end_catch()'.
	 * The book recommends that these  functions should be used for  reference
	 * counting of the number of recursive location where the exception object
	 * is being used. */

	/* For our purposes, we only get here when an EXCEPT block reaches
	 * its  end, and we  delete the exception  if it wasn't re-thrown. */
	struct exception_info *info;
	info = except_info();
#if defined(__KERNEL__) && 0
	x86_syslog_printf("%%{vinfo:/os/kernel.bin:%p:%p:%%f(%%l,%%c) : %%n : %%p} : %p : "
	                  "__cxa_end_catch%s [%#Ix] [error=%s ("
	                  "%.4" PRIxN(__SIZEOF_EXCEPT_CLASS_T__) ":"
	                  "%.4" PRIxN(__SIZEOF_EXCEPT_SUBCLASS_T__) ")]\n",
	                  __builtin_return_address(0),
	                  __builtin_return_address(0),
	                  THIS_TASK,
	                  info->ei_flags & EXCEPT_FRETHROW ? "" : " [delete]",
	                  info->ei_flags,
	                  except_name(info->ei_code),
	                  EXCEPT_CLASS(info->ei_code),
	                  EXCEPT_SUBCLASS(info->ei_code));
#endif
	assertf(info->ei_code != E_OK || info->ei_nesting != 0,
	        "Exception handler entered, but no exception set");
	if (!(info->ei_flags & EXCEPT_FRETHROW))
		info->ei_code = EXCEPT_CODEOF(E_OK);
	info->ei_flags &= ~(EXCEPT_FRETHROW);
}


/* Bad usage: missing nesting for TRY. */
INTERN SECTION_EXCEPT_TEXT ATTR_COLD ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL libc_except_badusage_no_nesting)(except_register_state_t const *state) {
	struct assert_args args;
	except_register_state_to_kcpustate(state, &args.aa_state);
	args.aa_file   = NULL;
	args.aa_line   = 0;
	args.aa_func   = NULL;
	args.aa_format = "Recursive `TRY' isn't nested; use `NESTED_TRY' instead";
	args.aa_expr   = "TRY";
	libc_assertion_failure_core(&args);
}


#ifndef NDEBUG
PRIVATE SECTION_EXCEPT_TEXT ATTR_COLD ATTR_NORETURN NONNULL((1)) void
assert_failf_at(except_register_state_t const *state,
                char const *__restrict expr,
                char const *__restrict format, ...) {
	struct assert_args args;
	va_start(args.aa_args, format);
	except_register_state_to_kcpustate(state, &args.aa_state);
	args.aa_expr   = expr;
	args.aa_file   = NULL;
	args.aa_line   = 0;
	args.aa_func   = NULL;
	args.aa_format = format;
	libc_assertion_failure_core(&args);
}

/* Bad usage: Attempted to call `RETHROW()' from outside of a catch-block. */
INTERN SECTION_EXCEPT_TEXT ATTR_COLD ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL libc_except_badusage_rethrow_outside_catch)(except_register_state_t const *state) {
	assert_failf_at(state, "RETHROW()", "RETHROW() outside of catch-block");
}

/* Bad usage: Attempted to  call `THROW()'  from inside  of a  catch-block,
 *            without wrapping the throwing code location inside of another
 *            NESTED_TRY-block. */
INTERN SECTION_EXCEPT_TEXT ATTR_COLD ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL libc_except_badusage_throw_inside_catch)(except_register_state_t const *state,
                                                       except_code_t code, size_t argc,
                                                       va_list args) {
	char args_buf[EXCEPTION_DATA_POINTERS * (4 + sizeof(void *) * 2) + 1];
	char *endp = args_buf;
	if unlikely(argc > EXCEPTION_DATA_POINTERS)
		argc = EXCEPTION_DATA_POINTERS; /* Shouldn't happen... */
	for (; argc; --argc) {
		void *arg = va_arg(args, void *);
		endp += sprintf(endp, ", %#" PRIxPTR, arg);
	}
	*endp = '\0';
	assert_failf_at(state, "THROW(...)",
	                "THROW(%s%s) ("
	                "%.4" PRIxN(__SIZEOF_EXCEPT_CLASS_T__) ":"
	                "%.4" PRIxN(__SIZEOF_EXCEPT_SUBCLASS_T__) ""
	                ") inside of catch-block\n"
	                "Consider adding/changing a surrounding `TRY' between "
	                "here and the nearest `EXCEPT' to `NESTED_TRY'",
	                except_name(code),
	                args_buf,
	                EXCEPT_CLASS(code),
	                EXCEPT_SUBCLASS(code));
}
#endif /* !NDEBUG */


DECL_END
#endif /* __CC__ */


#endif /* !GUARD_LIBC_HYBRID_EXCEPT_C */
