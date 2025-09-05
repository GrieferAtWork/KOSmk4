/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif(x -> x.startswith("-O"));
gcc_opt.append("-Os"); // Optimize for size (don't want to bloat libc too much with this compat stuff)
]]]*/
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
#ifndef GUARD_LIBC_USER_PRINTF_C
#define GUARD_LIBC_USER_PRINTF_C 1

#include "../api.h"
/**/

#include <features.h>
#include <hybrid/compiler.h>

#include <hybrid/__alloca.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <hybrid/__assert.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <hybrid/align.h>

#include <asm/redirect.h>
#include <bits/math-constants.h>
#include <bits/types.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <kos/exec/idata.h>
#include <kos/sched/shared-recursive-rwlock.h>
#include <kos/sched/shared-rwlock.h>
#include <kos/types.h>
#include <parts/uchar/format-printer.h>
#include <parts/wchar/format-printer.h>
#include <sys/mman.h>
#include <sys/param.h>
#include <sys/types.h>

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <format-printer.h>
#include <malloc.h>
#include <printf.h>
#include <pthread.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unicode.h>

#include <libc/parts.uchar.string.h>
#include <libc/string.h>
#include <libc/template/itoa_digits.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <libdebuginfo/addr2line.h>
#include <libdisasm/disassembler.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <libiberty.h>

#include "../auto/format-printer.h"
#include "../auto/parts.wchar.format-printer.h"
#include "../auto/string.h" /* Dependency of `#include <libc/template/format-printf.h>' */
#include "../libc/dl.h"     /* Prevent relocations against real <dlfcn.h> symbols. */
#include "../libc/globals.h"
#include "printf.h"
#include "stdio-api.h"
#include "stdio.h"
#include "unicode.h" /* Dependency of `#include <libc/template/format-printf.h>' */
#include "wchar.h"

#define bitsof(T) (sizeof(T) * NBBY)

DECL_BEGIN

#if __ARCH_REDIRECT_MAXBYTES != 0

/* Hook-supporting libc printf functions
 *
 * Once any of the functions below that inject custom printf hooks  have
 * been called, we use the `__arch_redirect()' mechanism to re-write the
 * code of:
 * - format_vprintf(3)       = libc_hooksup_format_vprintf
 * - format_vwprintf(3)      = libd_hooksup_format_vwprintf
 * - DOS$format_vwprintf(3)  = libc_hooksup_format_vwprintf
 *
 * Of course, that means that there is a small moment during which  calls
 * to printf() might crash if another thread is currently doing the first
 * call to one of the register-printf-hook functions, but really:  that's
 * not  something that should  happen; the register-printf-hook functions
 * should only be called during program startup.
 */
INTDEF ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) NONNULL((1)) ssize_t
(LIBCCALL libc_hooksup_format_vprintf)(pformatprinter printer, void *arg,
                                       char const *__restrict format,
                                       va_list args) THROWS(...);
INTDEF ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 0) NONNULL((1)) ssize_t
(LIBDCALL libd_hooksup_format_vwprintf)(pc16formatprinter printer, void *arg,
                                        char16_t const *__restrict format,
                                        va_list args) THROWS(...);
INTDEF ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 0) NONNULL((1)) ssize_t
(LIBKCALL libc_hooksup_format_vwprintf)(pc32formatprinter printer, void *arg,
                                        char32_t const *__restrict format,
                                        va_list args) THROWS(...);

/* Inject a single hook */
PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") int
NOTHROW_NCX(LIBCCALL inject_hook)(void const *pc, void const *function_to_inject) {
	int result;
	result = mprotect((void *)pc, __ARCH_REDIRECT_MAXBYTES, PROT_READ | PROT_EXEC | PROT_WRITE);
	if unlikely(result != 0)
		goto err;
	__arch_redirect((void *)pc, function_to_inject);
	result = mprotect((void *)pc, __ARCH_REDIRECT_MAXBYTES, PROT_READ | PROT_EXEC);
err:
	return result;
}

/* Inject all hooks */
PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") int
NOTHROW_NCX(LIBCCALL inject_hooks)(void) {
	int result = 0;
	result |= inject_hook((void const *)&libc_format_vprintf, (void const *)&libc_hooksup_format_vprintf);
	result |= inject_hook((void const *)&libd_format_vwprintf, (void const *)&libd_hooksup_format_vwprintf);
	result |= inject_hook((void const *)&libc_format_vwprintf, (void const *)&libc_hooksup_format_vwprintf);
	return result;
}

/* Printf lock used to sync custom printf specifiers, and their use */
PRIVATE ATTR_SECTION(".bss.crt.compat.glibc.printf")
DEFINE_SHARED_RWLOCK(specsup_printf);

/* Helpers for accessing `specsup_printf' */
#define /*        */ _specsup_printf_reap()        (void)0
#define /*        */ specsup_printf_reap()         (void)0
#define /*        */ specsup_printf_mustreap()     0
#define /*BLOCKING*/ specsup_printf_write()        shared_rwlock_write(&specsup_printf)
#define /*        */ specsup_printf_trywrite()     shared_rwlock_trywrite(&specsup_printf)
#define /*        */ specsup_printf_endwrite()     (shared_rwlock_endwrite(&specsup_printf), specsup_printf_reap())
#define /*        */ _specsup_printf_endwrite()    shared_rwlock_endwrite(&specsup_printf)
#define /*BLOCKING*/ specsup_printf_read()         shared_rwlock_read(&specsup_printf)
#define /*        */ specsup_printf_tryread()      shared_rwlock_tryread(&specsup_printf)
#define /*        */ _specsup_printf_endread()     shared_rwlock_endread(&specsup_printf)
#define /*        */ specsup_printf_endread()      (void)(shared_rwlock_endread(&specsup_printf) && (specsup_printf_reap(), 0))
#define /*        */ _specsup_printf_end()         shared_rwlock_end(&specsup_printf)
#define /*        */ specsup_printf_end()          (void)(shared_rwlock_end(&specsup_printf) && (specsup_printf_reap(), 0))
#define /*BLOCKING*/ specsup_printf_upgrade()      shared_rwlock_upgrade(&specsup_printf)
#define /*        */ specsup_printf_tryupgrade()   shared_rwlock_tryupgrade(&specsup_printf)
#define /*        */ specsup_printf_downgrade()    shared_rwlock_downgrade(&specsup_printf)
#define /*        */ specsup_printf_reading()      shared_rwlock_reading(&specsup_printf)
#define /*        */ specsup_printf_writing()      shared_rwlock_writing(&specsup_printf)
#define /*        */ specsup_printf_canread()      shared_rwlock_canread(&specsup_printf)
#define /*        */ specsup_printf_canwrite()     shared_rwlock_canwrite(&specsup_printf)
#define /*BLOCKING*/ specsup_printf_waitread()     shared_rwlock_waitread(&specsup_printf)
#define /*BLOCKING*/ specsup_printf_waitwrite()    shared_rwlock_waitwrite(&specsup_printf)



/* Define the base pointers (which have to be exposed
 * for libc4/5 compat) for the printf hooking system.
 *
 * For the sake of improving compatibility, a program
 * that imports these  points automatically gets  the
 * printf-hook system injected. */
#undef __printf_function_table
#undef __printf_arginfo_table
PRIVATE ATTR_SECTION(".bss.crt.compat.glibc.printf") printf_function **libc___printf_function_table = NULL;
PRIVATE ATTR_SECTION(".bss.crt.compat.glibc.printf") printf_arginfo_size_function **libc___printf_arginfo_table = NULL;

PRIVATE ATTR_SECTION(".bss.crt.compat.glibc.printf") pthread_once_t libc_printf_hook_didinit = PTHREAD_ONCE_INIT;
PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") void LIBCCALL libc_printf_hook_doinit(void) {
	/* Allocate tables. */
	libc___printf_function_table = (printf_function **)xcalloc(256, sizeof(printf_function *));
	libc___printf_arginfo_table  = (printf_arginfo_size_function **)xcalloc(256, sizeof(printf_arginfo_size_function *));

	/* Inject hooks. */
	if (inject_hooks() != 0)
		err(1, "libc: failed to inject printf hooks");
}

PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf")
void LIBCCALL libc_printf_hook_init(void) {
	pthread_once(&libc_printf_hook_didinit,
	             &libc_printf_hook_doinit);
}

INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") printf_function ***LIBCCALL
libc_resolve___printf_function_table(void) {
	libc_printf_hook_init();
	return &libc___printf_function_table;
}
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") printf_arginfo_size_function ***LIBCCALL
libc_resolve___printf_arginfo_table(void) {
	libc_printf_hook_init();
	return &libc___printf_arginfo_table;
}
DEFINE_PUBLIC_IDATA(__printf_function_table, libc_resolve___printf_function_table, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(__printf_arginfo_table, libc_resolve___printf_arginfo_table, __SIZEOF_POINTER__);
#define __printf_function_table GET_NOREL_GLOBAL(__printf_function_table)
#define __printf_arginfo_table  GET_NOREL_GLOBAL(__printf_arginfo_table)


/************************************************************************/
/* Table of custom printf format modifiers                              */
/************************************************************************/
typedef typeof(((struct printf_info *)0)->user) printf_userflag_t;
struct format_modifier {
	printf_userflag_t             fm_flag;  /* Format modifier flag */
	COMPILER_FLEXIBLE_ARRAY(char, fm_text); /* Text that is expected within the format-string */
};

/* [1..1][0..n][owned][lock(specsup_printf)] Sorted list of format modifiers. (allowing for bsearch) */
PRIVATE ATTR_SECTION(".bss.crt.compat.glibc.printf") struct format_modifier **format_mod_start = NULL;
PRIVATE ATTR_SECTION(".bss.crt.compat.glibc.printf") struct format_modifier **format_mod_end   = NULL;
PRIVATE ATTR_SECTION(".bss.crt.compat.glibc.printf") unsigned int format_mod_usedbits = 0;


/************************************************************************/
/* Array of custom printf format type loaders                           */
/************************************************************************/

/* [1..1][0..format_type_loadc][owned][lock(specsup_printf)]
 * Array of format type loader functions. The array index is the format type minus `PA_LAST'. */
PRIVATE ATTR_SECTION(".bss.crt.compat.glibc.printf") printf_va_arg_function **format_type_loadv = 0;
PRIVATE ATTR_SECTION(".bss.crt.compat.glibc.printf") size_t format_type_loadc = 0;


#define strstartcmp_8_8 strstartcmp

PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL strstartcmp_16_8)(char16_t const *str, char const *startswith) {
	char16_t c1;
	char c2;
	do {
		c2 = *startswith++;
		if (!c2)
			return 0;
		c1 = *str++;
		if unlikely(c1 != c2) {
			if (c1 < (unsigned char)c2)
				return -1;
			return 1;
		}
	} while (c1);
	return -1;
}

PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL strstartcmp_32_8)(char32_t const *str, char const *startswith) {
	char32_t c1;
	char c2;
	do {
		c2 = *startswith++;
		if (!c2)
			return 0;
		c1 = *str++;
		if unlikely(c1 != (unsigned char)c2) {
			if (c1 < (unsigned char)c2)
				return -1;
			return 1;
		}
	} while (c1);
	return -1;
}

/* Consume a user-defined format modifier from an 8-bit format string. */
PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") char const *
NOTHROW_NCX(LIBCCALL format_mod_consume8)(char const *__restrict format,
                                          struct printf_info *info) {
	struct format_modifier **lo, **hi;
again:
	lo = format_mod_start;
	hi = format_mod_end;
	while (lo < hi) {
		struct format_modifier **mid;
		int diff;
		mid  = lo + ((hi - lo) >> 1);
		diff = strstartcmp_8_8(format, (*mid)->fm_text);
		if (diff < 0) {
			hi = mid;
		} else if (diff > 0) {
			lo = mid + 1;
		} else {
			if (info)
				info->user |= (*mid)->fm_flag;
			format += strlen((*mid)->fm_text);
			goto again;
		}
	}
	return format;
}

/* Consume a user-defined format modifier from a 16-bit format string. */
PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") char16_t const *
NOTHROW_NCX(LIBCCALL format_mod_consume16)(char16_t const *__restrict format,
                                           struct printf_info *info) {
	struct format_modifier **lo, **hi;
again:
	lo = format_mod_start;
	hi = format_mod_end;
	while (lo < hi) {
		struct format_modifier **mid;
		int diff;
		mid  = lo + ((hi - lo) >> 1);
		diff = strstartcmp_16_8(format, (*mid)->fm_text);
		if (diff < 0) {
			hi = mid;
		} else if (diff > 0) {
			lo = mid + 1;
		} else {
			if (info)
				info->user |= (*mid)->fm_flag;
			format += strlen((*mid)->fm_text);
			goto again;
		}
	}
	return format;
}

/* Consume a user-defined format modifier from a 32-bit format string. */
PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") char32_t const *
NOTHROW_NCX(LIBCCALL format_mod_consume32)(char32_t const *__restrict format,
                                           struct printf_info *info) {
	struct format_modifier **lo, **hi;
again:
	lo = format_mod_start;
	hi = format_mod_end;
	while (lo < hi) {
		struct format_modifier **mid;
		int diff;
		mid  = lo + ((hi - lo) >> 1);
		diff = strstartcmp_32_8(format, (*mid)->fm_text);
		if (diff < 0) {
			hi = mid;
		} else if (diff > 0) {
			lo = mid + 1;
		} else {
			if (info)
				info->user |= (*mid)->fm_flag;
			format += strlen((*mid)->fm_text);
			goto again;
		}
	}
	return format;
}



/*[[[head:libc_register_printf_specifier,hash:CRC-32=0x705e4dc5]]]*/
/* >> register_printf_specifier(3), register_printf_function(3)
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") int
NOTHROW_NCX(LIBCCALL libc_register_printf_specifier)(__STDC_INT_AS_UINT_T spec,
                                                     printf_function *func,
                                                     printf_arginfo_size_function *arginfo)
/*[[[body:libc_register_printf_specifier]]]*/
{
	if ((unsigned int)spec > 0xff)
		return libc_seterrno(EINVAL);
	specsup_printf_write();
	__printf_function_table[(unsigned int)spec] = func;
	__printf_arginfo_table[(unsigned int)spec]  = arginfo;
	specsup_printf_endwrite();
	return 0;
}
/*[[[end:libc_register_printf_specifier]]]*/

/*[[[impl:libc_register_printf_function]]]*/
DEFINE_INTERN_ALIAS(libc_register_printf_function, libc_register_printf_specifier);

/*[[[head:libc_register_printf_modifier,hash:CRC-32=0xe89a1e5]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_register_printf_modifier)(__WCHAR32_TYPE__ const *str)
/*[[[body:libc_register_printf_modifier]]]*/
{
	int result;
	struct format_modifier *newmod;
	size_t i, oldsize, newsize, modlen;
	struct format_modifier **lo, **hi;
	/* Validate that all characters of `str' fall into the single-byte range. */
	for (i = 0; str[i]; ++i) {
		if ((uint32_t)str[i] >= 0x100)
			return libc_seterrno(EINVAL);
	}
	modlen = wcslen((wchar_t const *)str);
	newmod = (struct format_modifier *)malloc(offsetof(struct format_modifier, fm_text) +
	                                          (modlen + 1) * sizeof(char));
	if unlikely(!newmod)
		return -1;
	for (i = 0; i <= modlen; ++i)
		newmod->fm_text[i] = (char)(unsigned char)(uint32_t)str[i];
	specsup_printf_write();
	lo = format_mod_start;
	hi = format_mod_end;
	while (lo < hi) {
		struct format_modifier **mid;
		int diff;
		mid  = lo + ((hi - lo) >> 1);
		diff = strcmp((*mid)->fm_text, newmod->fm_text);
		if (diff < 0) {
			lo = mid + 1;
		} else if (diff > 0) {
			hi = mid;
		} else {
			/* Sequence was already defined */
			result = (*mid)->fm_flag;
			goto done_unlock_free;
		}
	}

	/* Check if we can still allocate more bits. */
	if unlikely(format_mod_usedbits >= bitsof(printf_userflag_t)) {
		result = libc_seterrno(ENOSPC);
		goto done_unlock_free;
	}

	/* Must insert a new entry at `lo' */
	assert(lo == hi);
	i       = (size_t)(lo - format_mod_start);
	oldsize = (size_t)(format_mod_end - format_mod_start);
	newsize = oldsize + 1;
	lo      = format_mod_start;
	lo      = (struct format_modifier **)realloc(lo, newsize, sizeof(struct format_modifier *));
	if unlikely(!lo) {
		specsup_printf_endwrite();
		free(newmod);
		return -1;
	}
	memmoveup(&lo[i + 1], &lo[i], oldsize - i,
	          sizeof(struct format_modifier *));
	lo[i] = newmod;

	/* Assign a modifier bit to use for the caller's string. */
	result = 1 << format_mod_usedbits;
	newmod->fm_flag = result;
	++format_mod_usedbits;
	specsup_printf_endwrite();
	return result;
done_unlock_free:
	specsup_printf_endwrite();
	free(newmod);
	return result;
}
/*[[[end:libc_register_printf_modifier]]]*/


/*[[[head:libc_register_printf_type,hash:CRC-32=0xb7ea678e]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_register_printf_type)(printf_va_arg_function *fct)
/*[[[body:libc_register_printf_type]]]*/
{
	int result;
	printf_va_arg_function **newtab;
	specsup_printf_write();
	result = PA_LAST + format_type_loadc;
	if unlikely(result >= 0x100) {
		/* Cannot allocate more types :( */
		result = libc_seterrno(ENOSPC);
		goto done;
	}
	newtab = (printf_va_arg_function **)realloc(format_type_loadv,
	                                            format_type_loadc + 1,
	                                            sizeof(printf_va_arg_function *));
	if unlikely(!newtab) {
		result = -1;
		goto done;
	}
	format_type_loadv = newtab;
	format_type_loadv[format_type_loadc] = fct;
	++format_type_loadc;
done:
	specsup_printf_endwrite();
	return result;
}
/*[[[end:libc_register_printf_type]]]*/


/************************************************************************/
/* Printf helper functions                                              */
/************************************************************************/

PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") size_t
NOTHROW_NCX(LIBCCALL printf_typeinfo_extrasize)(int const *typev,
                                                __STDC_INT_AS_SIZE_T const *sizev,
                                                size_t argc) {
	size_t i, result = 0;
	for (i = 0; i < argc; ++i) {
		size_t argsize;
		unsigned int argtype = (unsigned int)typev[i];
		if (argtype & PA_FLAG_PTR)
			goto do_pointer;
		switch (argtype & 0xff) {
		case PA_INT:
			argsize = __SIZEOF_INT__;
			if (argtype & PA_FLAG_LONG_LONG) {
				argsize = __SIZEOF_LONG_LONG__;
			} else if (argtype & PA_FLAG_LONG) {
				argsize = __SIZEOF_LONG__;
			} else if (argtype & PA_FLAG_SHORT) {
				argsize = __SIZEOF_SHORT__;
			}
			break;
		case PA_CHAR:
			argsize = __SIZEOF_CHAR__;
			break;
		case PA_WCHAR:
			argsize = __SIZEOF_WCHAR_T__;
			break;
		case PA_STRING:
		case PA_WSTRING:
		case PA_POINTER:
do_pointer:
			argsize = __SIZEOF_POINTER__;
			break;
		case PA_FLOAT:
			argsize = __SIZEOF_FLOAT__;
			break;
		case PA_DOUBLE:
#ifdef __COMPILER_HAVE_LONGDOUBLE
			if (argtype & PA_FLAG_LONG_DOUBLE) {
				argsize = __SIZEOF_LONG_DOUBLE__;
			} else
#endif /* __COMPILER_HAVE_LONGDOUBLE */
			{
				argsize = __SIZEOF_DOUBLE__;
			}
			break;
		default:
			argsize = sizev[i];
			break;
		}
		argsize = CEIL_ALIGN(argsize, __ALIGNOF_MAX_ALIGN_T__);
		result += argsize;
	}
	return result;
}

#ifdef __VA_LIST_IS_ARRAY
PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") void **
NOTHROW_NCX(LIBCCALL printf_typeinfo_load)(int const *typev,
                                           __STDC_INT_AS_SIZE_T const *sizev,
                                           size_t argc, byte_t *outbuf,
                                           byte_t const *pdata, va_list vargs,
                                           bool should_construct_array)
#else /* __VA_LIST_IS_ARRAY */
PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") void **
NOTHROW_NCX(LIBCCALL printf_typeinfo_load)(int const *typev,
                                           __STDC_INT_AS_SIZE_T const *sizev,
                                           size_t argc, byte_t *outbuf,
                                           byte_t const *pdata, va_list *p_args,
                                           bool should_construct_array)
#define vargs (*p_args)
#endif /* !__VA_LIST_IS_ARRAY */
{
	size_t i;
	void **result;
	result = (void **)outbuf;
	if (should_construct_array)
		outbuf += argc * sizeof(void *); /* Elements of array passed to `printf_function' */
	for (i = 0; i < argc; ++i) {
		size_t argsize;
		unsigned int argtype = (unsigned int)typev[i];
		if (argtype & PA_FLAG_PTR)
			goto do_pointer;
		switch (argtype & 0xff) {
		case PA_INT:
			if (argtype & PA_FLAG_LONG_LONG) {
				if (pdata == NULL)
					*(__LONGLONG *)outbuf = va_arg(vargs, __LONGLONG);
				argsize = __SIZEOF_LONG_LONG__;
			} else if (argtype & PA_FLAG_LONG) {
				if (pdata == NULL)
					*(long *)outbuf = va_arg(vargs, long);
				argsize = __SIZEOF_LONG__;
			} else if (argtype & PA_FLAG_SHORT) {
				if (pdata == NULL)
					*(short *)outbuf = (short)va_arg(vargs, int);
				argsize = __SIZEOF_SHORT__;
			} else {
				if (pdata == NULL)
					*(int *)outbuf = va_arg(vargs, int);
				argsize = __SIZEOF_INT__;
			}
			break;
		case PA_CHAR:
			argsize = __SIZEOF_CHAR__;
			if (pdata == NULL)
				*(char *)outbuf = (char)va_arg(vargs, int);
			break;
		case PA_WCHAR:
			argsize = __SIZEOF_WCHAR_T__;
			if (pdata == NULL)
				*(wchar_t *)outbuf = (wchar_t)va_arg(vargs, wint_t);
			break;
		case PA_STRING:
		case PA_WSTRING:
		case PA_POINTER:
do_pointer:
			argsize = __SIZEOF_POINTER__;
			if (pdata == NULL)
				*(void **)outbuf = (void *)va_arg(vargs, void *);
			break;
		case PA_FLOAT:
			argsize = __SIZEOF_FLOAT__;
			if (pdata == NULL)
				*(float *)outbuf = (float)va_arg(vargs, double);
			break;
		case PA_DOUBLE:
#ifdef __COMPILER_HAVE_LONGDOUBLE
			if (argtype & PA_FLAG_LONG_DOUBLE) {
				argsize = __SIZEOF_LONG_DOUBLE__;
				if (pdata == NULL)
					*(__LONGDOUBLE *)outbuf = va_arg(vargs, __LONGDOUBLE);
			} else
#endif /* __COMPILER_HAVE_LONGDOUBLE */
			{
				argsize = __SIZEOF_DOUBLE__;
				if (pdata == NULL)
					*(double *)outbuf = va_arg(vargs, double);
			}
			break;

		default:
			argsize = sizev[i];
			break;
		}
		if (pdata == NULL) {
			if (should_construct_array)
				result[i] = (void *)outbuf;
			argsize = CEIL_ALIGN(argsize, __ALIGNOF_MAX_ALIGN_T__);
			outbuf += argsize;
		} else {
			if (should_construct_array)
				result[i] = (void *)pdata;
			argsize = CEIL_ALIGN(argsize, __ALIGNOF_MAX_ALIGN_T__);
			pdata += argsize;
		}
	}
	return result;
#undef vargs
}


struct format_file_printer: FILE {
	struct iofile_data ffp_exdat;   /* Extended file data */
	pformatprinter     ffp_printer; /* [1..1] Output printer */
	void              *ffp_arg;     /* Output printer cookie */
	ssize_t            ffp_error;   /* Format output error code. */
};

#define FORMAT_FILE_PRINTER_FLAGS \
	(IO_RW | IO_HASVTAB | IO_NODYNSCALE | IO_NOTATTY | _IO_NOLOCK_OPT)


PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") ssize_t LIBKCALL
format_file_printer_write(void *cookie, void const *buf, size_t num_bytes) {
	ssize_t result;
	struct format_file_printer *me;
	me = (struct format_file_printer *)cookie;
	result = me->ffp_error;
	if (result >= 0) {
		result = (*me->ffp_printer)(me->ffp_arg, (char const *)buf, num_bytes);
		me->ffp_error = result;
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") NONNULL((1, 2)) void
NOTHROW_NCX(LIBCCALL format_file_printer_init)(struct format_file_printer *__restrict self,
                                               pformatprinter printer, void *arg) {
	bzero(self, sizeof(*self));
	self->if_flag     = FORMAT_FILE_PRINTER_FLAGS;
	self->if_exdata   = &self->ffp_exdat;
	self->ffp_printer = printer;
	self->ffp_arg     = arg;
	shared_recursive_rwlock_cinit(&self->ffp_exdat.io_lock);
	__mbstate_cinit(&self->ffp_exdat.io_mbs);
	self->ffp_exdat.io_writefn = &format_file_printer_write;
	self->ffp_exdat.io_cookie  = self;
}

PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") ssize_t LIBCCALL
invoke_printf_function8(pformatprinter printer, void *arg,
                        struct printf_info const *info,
                        void const *const *args) {
	ssize_t result;
	struct format_file_printer ffile;
	__printf_function *handler;
	assertf(info->spec <= 0xff, "%u", (unsigned int)info->spec);
	handler = __printf_function_table[info->spec];
	assertf(handler, "%u", (unsigned int)info->spec);

	/* Setup a simple on-stack FILE that writes to `printer' */
	format_file_printer_init(&ffile, printer, arg);

	/* Actually invoke the handler. */
	result = (ssize_t)(*handler)(file_touser(&ffile), info, args);
	if (ffile.ffp_error < 0 && result >= 0)
		result = ffile.ffp_error;
	assert(!(ffile.if_flag & IO_MALLBUF));
	assert(ffile.if_bufsiz == 0);
	return result;
}





struct format_file_c16printer: FILE {
	struct iofile_data       ffp_exdat; /* Extended file data */
	struct format_8to16_data ffp_out;   /* Output descriptor. */
	ssize_t                  ffp_error; /* Format output error code. */
};


PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") ssize_t LIBKCALL
format_file_c16printer_write(void *cookie, void const *buf, size_t num_bytes) {
	ssize_t result;
	struct format_file_c16printer *me;
	me = (struct format_file_c16printer *)cookie;
	result = me->ffp_error;
	if (result >= 0) {
		result = format_8to16(&me->ffp_out, (char const *)buf, num_bytes);
		me->ffp_error = result;
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") NONNULL((1, 2)) void
NOTHROW_NCX(LIBCCALL format_file_c16printer_init)(struct format_file_c16printer *__restrict self,
                                                  pc16formatprinter printer, void *arg) {
	bzero(self, sizeof(*self));
	self->if_flag            = FORMAT_FILE_PRINTER_FLAGS;
	self->if_exdata          = &self->ffp_exdat;
	self->ffp_out.fd_printer = printer;
	self->ffp_out.fd_arg     = arg;
	shared_recursive_rwlock_cinit(&self->ffp_exdat.io_lock);
	__mbstate_cinit(&self->ffp_exdat.io_mbs);
	self->ffp_exdat.io_writefn = &format_file_c16printer_write;
	self->ffp_exdat.io_cookie  = self;
}

PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") ssize_t LIBCCALL
invoke_printf_function16(pc16formatprinter printer, void *arg,
                         struct printf_info const *info,
                         void const *const *args) {
	ssize_t result;
	struct format_file_c16printer ffile;
	__printf_function *handler;
	assertf(info->spec <= 0xff, "%u", (unsigned int)info->spec);
	handler = __printf_function_table[info->spec];
	assertf(handler, "%u", (unsigned int)info->spec);

	/* Setup a simple on-stack FILE that writes to `printer' */
	format_file_c16printer_init(&ffile, printer, arg);

	/* Actually invoke the handler. */
	result = (ssize_t)(*handler)(file_touser(&ffile), info, args);
	if (ffile.ffp_error < 0 && result >= 0)
		result = ffile.ffp_error;
	assert(!(ffile.if_flag & IO_MALLBUF));
	assert(ffile.if_bufsiz == 0);
	return result;
}


struct format_file_c32printer: FILE {
	struct iofile_data       ffp_exdat; /* Extended file data */
	struct format_8to32_data ffp_out;   /* Output descriptor. */
	ssize_t                  ffp_error; /* Format output error code. */
};


PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") ssize_t LIBKCALL
format_file_c32printer_write(void *cookie, void const *buf, size_t num_bytes) {
	ssize_t result;
	struct format_file_c32printer *me;
	me = (struct format_file_c32printer *)cookie;
	result = me->ffp_error;
	if (result >= 0) {
		result = format_8to32(&me->ffp_out, (char const *)buf, num_bytes);
		me->ffp_error = result;
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") NONNULL((1, 2)) void
NOTHROW_NCX(LIBCCALL format_file_c32printer_init)(struct format_file_c32printer *__restrict self,
                                                  pc32formatprinter printer, void *arg) {
	bzero(self, sizeof(*self));
	self->if_flag            = FORMAT_FILE_PRINTER_FLAGS;
	self->if_exdata          = &self->ffp_exdat;
	self->ffp_out.fd_printer = printer;
	self->ffp_out.fd_arg     = arg;
	shared_recursive_rwlock_cinit(&self->ffp_exdat.io_lock);
	__mbstate_cinit(&self->ffp_exdat.io_mbs);
	self->ffp_exdat.io_writefn = &format_file_c32printer_write;
	self->ffp_exdat.io_cookie  = self;
}

PRIVATE ATTR_SECTION(".text.crt.compat.glibc.printf") ssize_t LIBCCALL
invoke_printf_function32(pc32formatprinter printer, void *arg,
                         struct printf_info const *info,
                         void const *const *args) {
	ssize_t result;
	struct format_file_c32printer ffile;
	__printf_function *handler;
	assertf(info->spec <= 0xff, "%u", (unsigned int)info->spec);
	handler = __printf_function_table[info->spec];
	assertf(handler, "%u", (unsigned int)info->spec);

	/* Setup a simple on-stack FILE that writes to `printer' */
	format_file_c32printer_init(&ffile, printer, arg);

	/* Actually invoke the handler. */
	result = (ssize_t)(*handler)(file_touser(&ffile), info, args);
	if (ffile.ffp_error < 0 && result >= 0)
		result = ffile.ffp_error;
	assert(!(ffile.if_flag & IO_MALLBUF));
	assert(ffile.if_bufsiz == 0);
	return result;
}



ATTR_SECTION(".text.crt.compat.glibc.printf")
INTERN ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) NONNULL((1)) ssize_t
(LIBCCALL libc_hooksup_format_vprintf)(pformatprinter printer, void *arg,
                                       char const *__restrict format,
                                       va_list args) THROWS(...) {
#ifndef __INTELLISENSE__
#define __PRINTF_HOOKS /* Enable printf-hook support in the implementation of `format_printf()' */
#define __FORMAT_PRINTER           printer
#define __FORMAT_ARG               arg
#define __FORMAT_FORMAT            format
#define __FORMAT_ARGS              args
#define __CHAR_TYPE                char
#define __CHAR_SIZE                __SIZEOF_CHAR__
#define __FORMAT_STRERROR          libc_strerror
#define __FORMAT_REPEAT            libc_format_repeat
#define __FORMAT_HEXDUMP           libc_format_hexdump
#define __FORMAT_WIDTH             libc_format_width
#define __FORMAT_ESCAPE            libc_format_escape
#define __FORMAT_WIDTH16           libd_format_wwidth
#define __FORMAT_WIDTH32           libc_format_wwidth
#define __FORMAT_ESCAPE16          libd_format_wescape
#define __FORMAT_ESCAPE32          libc_format_wescape
#define __FORMAT_UNICODE_WRITECHAR libc_unicode_writeutf8
#define __FORMAT_UNICODE_FORMAT16  libd_format_wto8
#define __FORMAT_UNICODE_FORMAT32  libc_format_wto8
#include <libc/template/format-printf.h>
#endif /* !__INTELLISENSE__ */
}

ATTR_SECTION(".text.crt.compat.glibc.printf")
INTERN ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 0) NONNULL((1)) ssize_t
(LIBDCALL libd_hooksup_format_vwprintf)(pc16formatprinter printer, void *arg,
                                        char16_t const *__restrict format,
                                        va_list args) THROWS(...) {
#ifndef __INTELLISENSE__
#define __PRINTF_HOOKS /* Enable printf-hook support in the implementation of `format_printf()' */
#define __FORMAT_PRINTER            printer
#define __FORMAT_ARG                arg
#define __FORMAT_FORMAT             format
#define __FORMAT_ARGS               args
#define __CHAR_TYPE                 char16_t
#define __CHAR_SIZE                 2
#define __FORMAT_STRERROR           libd_strerror
#define __FORMAT_REPEAT             libd_format_wrepeat
#define __FORMAT_HEXDUMP            libd_format_whexdump
#define __FORMAT_WIDTH              libd_format_wwidth
#define __FORMAT_ESCAPE             libd_format_wescape
#define __FORMAT_WIDTH8             libc_format_width
#define __FORMAT_ESCAPE8            libc_format_escape
#define __FORMAT_UNICODE_FORMAT8    libd_format_8tow
#define __FORMAT_WIDTH32            libc_format_wwidth
#define __FORMAT_ESCAPE32           libc_format_wescape
#define __FORMAT_UNICODE_WRITECHAR  libc_unicode_writeutf16
#define __FORMAT_UNICODE_FORMAT32   libc_format_wto16
#include <libc/template/format-printf.h>
#endif /* !__INTELLISENSE__ */
}

ATTR_SECTION(".text.crt.compat.glibc.printf")
INTERN ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 0) NONNULL((1)) ssize_t
(LIBKCALL libc_hooksup_format_vwprintf)(pc32formatprinter printer, void *arg,
                                        char32_t const *__restrict format,
                                        va_list args) THROWS(...) {
#ifndef __INTELLISENSE__
#define __PRINTF_HOOKS /* Enable printf-hook support in the implementation of `format_printf()' */
#define __FORMAT_PRINTER            printer
#define __FORMAT_ARG                arg
#define __FORMAT_FORMAT             format
#define __FORMAT_ARGS               args
#define __CHAR_TYPE                 char32_t
#define __CHAR_SIZE                 4
#define __FORMAT_STRERROR           libc_strerror
#define __FORMAT_REPEAT             libc_format_wrepeat
#define __FORMAT_HEXDUMP            libc_format_whexdump
#define __FORMAT_WIDTH              libc_format_wwidth
#define __FORMAT_ESCAPE             libc_format_wescape
#define __FORMAT_WIDTH8             libc_format_width
#define __FORMAT_ESCAPE8            libc_format_escape
#define __FORMAT_UNICODE_FORMAT8    libc_format_8tow
#define __FORMAT_WIDTH16            libd_format_wwidth
#define __FORMAT_ESCAPE16           libd_format_wescape
#define __FORMAT_UNICODE_WRITECHAR(dst, ch) ((dst)[0] = (ch), (dst) + 1)
#define __FORMAT_UNICODE_FORMAT16   libd_format_wto32
#include <libc/template/format-printf.h>
#endif /* !__INTELLISENSE__ */
}


#else /* __ARCH_REDIRECT_MAXBYTES != 0 */
#ifdef __LIBCCALL_CALLER_CLEANUP
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") int
NOTHROW_NCX(LIBCCALL libc_printf_notsup)(void) {
	return libc_seterrno(ENOSYS);
}

DEFINE_INTERN_ALIAS(libc_register_printf_specifier, libc_printf_notsup);
DEFINE_INTERN_ALIAS(libc_register_printf_function, libc_printf_notsup);
DEFINE_INTERN_ALIAS(libc_register_printf_modifier, libc_printf_notsup);
DEFINE_INTERN_ALIAS(libc_register_printf_type, libc_printf_notsup);
#else /* __LIBCCALL_CALLER_CLEANUP */

DEFINE_INTERN_ALIAS(libc_register_printf_function, libc_register_printf_specifier);
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") NONNULL((2, 3)) int
NOTHROW_NCX(LIBCCALL libc_register_printf_specifier)(__STDC_INT_AS_UINT_T spec,
                                                     printf_function *func,
                                                     printf_arginfo_size_function *arginfo) {
	(void)spec;
	(void)func;
	(void)arginfo;
	return libc_seterrno(ENOSYS);
}

INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_register_printf_modifier)(__WCHAR32_TYPE__ const *str) {
	(void)str;
	return libc_seterrno(ENOSYS);
}
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_register_printf_type)(printf_va_arg_function *fct) {
	(void)fct;
	return libc_seterrno(ENOSYS);
}
#endif /* !__LIBCCALL_CALLER_CLEANUP */

#endif /* __ARCH_REDIRECT_MAXBYTES != 0 */

/*[[[head:libc_parse_printf_format,hash:CRC-32=0xdc912d99]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") ATTR_OUTS(3, 2) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_parse_printf_format)(char const *__restrict fmt,
                                               size_t n,
                                               int *__restrict argtypes)
/*[[[body:libc_parse_printf_format]]]*/
/*AUTO*/{
	(void)fmt;
	(void)n;
	(void)argtypes;
	CRT_UNIMPLEMENTEDF("parse_printf_format(fmt: %q, n: %Ix, argtypes: %p)", fmt, n, argtypes); /* TODO */
	return (size_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc_parse_printf_format]]]*/

/*[[[head:libc_printf_size,hash:CRC-32=0x618e6bdf]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_printf_size)(FILE *__restrict fp,
                                       struct printf_info const *info,
                                       void const *const *__restrict args)
/*[[[body:libc_printf_size]]]*/
/*AUTO*/{
	(void)fp;
	(void)info;
	(void)args;
	CRT_UNIMPLEMENTEDF("printf_size(fp: %p, info: %p, args: %p)", fp, info, args); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_printf_size]]]*/

/*[[[head:libc_printf_size_info,hash:CRC-32=0xb8e9c95d]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") NONNULL((1, 3)) int
NOTHROW_NCX(LIBCCALL libc_printf_size_info)(struct printf_info const *__restrict info,
                                            size_t n,
                                            int *__restrict argtypes)
/*[[[body:libc_printf_size_info]]]*/
/*AUTO*/{
	(void)info;
	(void)n;
	(void)argtypes;
	CRT_UNIMPLEMENTEDF("printf_size_info(info: %p, n: %Ix, argtypes: %p)", info, n, argtypes); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_printf_size_info]]]*/


/*[[[start:exports,hash:CRC-32=0x820e3a9e]]]*/
DEFINE_PUBLIC_ALIAS_P(register_printf_specifier,libc_register_printf_specifier,,int,NOTHROW_NCX,LIBCCALL,(__STDC_INT_AS_UINT_T spec, printf_function *func, printf_arginfo_size_function *arginfo),(spec,func,arginfo));
DEFINE_PUBLIC_ALIAS_P(__register_printf_function,libc_register_printf_function,,int,NOTHROW_NCX,LIBCCALL,(__STDC_INT_AS_UINT_T spec, printf_function *func, printf_arginfo_function *arginfo),(spec,func,arginfo));
DEFINE_PUBLIC_ALIAS_P(register_printf_function,libc_register_printf_function,,int,NOTHROW_NCX,LIBCCALL,(__STDC_INT_AS_UINT_T spec, printf_function *func, printf_arginfo_function *arginfo),(spec,func,arginfo));
DEFINE_PUBLIC_ALIAS_P(register_printf_modifier,libc_register_printf_modifier,WUNUSED NONNULL((1)),int,NOTHROW_NCX,LIBCCALL,(__WCHAR32_TYPE__ const *str),(str));
DEFINE_PUBLIC_ALIAS_P(register_printf_type,libc_register_printf_type,WUNUSED NONNULL((1)),int,NOTHROW_NCX,LIBCCALL,(printf_va_arg_function *fct),(fct));
DEFINE_PUBLIC_ALIAS_P(parse_printf_format,libc_parse_printf_format,ATTR_OUTS(3, 2) NONNULL((1)),size_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict fmt, size_t n, int *__restrict argtypes),(fmt,n,argtypes));
DEFINE_PUBLIC_ALIAS_P(printf_size,libc_printf_size,NONNULL((1, 2, 3)),int,NOTHROW_NCX,LIBCCALL,(FILE *__restrict fp, struct printf_info const *info, void const *const *__restrict args),(fp,info,args));
DEFINE_PUBLIC_ALIAS_P(printf_size_info,libc_printf_size_info,NONNULL((1, 3)),int,NOTHROW_NCX,LIBCCALL,(struct printf_info const *__restrict info, size_t n, int *__restrict argtypes),(info,n,argtypes));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PRINTF_C */
