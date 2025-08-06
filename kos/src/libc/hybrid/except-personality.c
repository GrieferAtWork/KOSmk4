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
#ifndef GUARD_LIBC_HYBRID_EXCEPT_PERSONALITY_C
#define GUARD_LIBC_HYBRID_EXCEPT_PERSONALITY_C 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/bits/except-register-state-helpers.h>
#include <kos/bits/except-register-state.h>
#include <kos/except.h>
#include <kos/exec/idata.h>
#include <kos/types.h>

#include <ctype.h>
#include <dlfcn.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#include <libunwind/dwarf.h>
#include <libunwind/eh_frame.h>
#include <libunwind/except.h>

#include "../libc/except-libunwind.h"
#include "../libc/except.h"
#ifndef __KERNEL__
#include "../libc/dl.h"
#endif /* !__KERNEL__ */

#ifndef FCALL
#define FCALL __FCALL
#endif /* !FCALL */

DECL_BEGIN

struct cxx_std_typeinfo;
#ifdef _GLIBCXX_VTABLE_PADDING
#define _EXTRA_SIZEOF_cxx_std_typeinfo_vtable_struct 2
#else /* _GLIBCXX_VTABLE_PADDING */
#define _EXTRA_SIZEOF_cxx_std_typeinfo_vtable_struct 0
#endif /* !_GLIBCXX_VTABLE_PADDING */
#define SIZEOF_cxx_std_typeinfo_vtable_struct \
	((_EXTRA_SIZEOF_cxx_std_typeinfo_vtable_struct + 3) * __SIZEOF_POINTER__)
struct cxx_std_typeinfo_vtable_struct {
	ptrdiff_t tiv_whole_object;
#ifdef _GLIBCXX_VTABLE_PADDING
	ptrdiff_t tiv_padding1;
#endif /* _GLIBCXX_VTABLE_PADDING */
	void const *tiv_whole_type;
#ifdef _GLIBCXX_VTABLE_PADDING
	ptrdiff_t tiv_padding2;
#endif /* _GLIBCXX_VTABLE_PADDING */

	/* Actual VTable callbacks go here... */
	char const *(ATTR_CDECL *tiv_getname)(struct cxx_std_typeinfo *self);

#ifndef __KERNEL__
	/* TODO: Must implement enough stuff to be compatible with libstdc++ */
#endif /* !__KERNEL__ */
};

static_assert(sizeof(struct cxx_std_typeinfo_vtable_struct) ==
              SIZEOF_cxx_std_typeinfo_vtable_struct);

struct cxx_std_typeinfo {
	struct cxx_std_typeinfo_vtable_struct *ti_vtable;
	char const                            *ti_name;
};

PRIVATE char const *ATTR_CDECL
cxx_std_typeinfo_getname(struct cxx_std_typeinfo *self) {
	return self->ti_name;
}

PRIVATE struct cxx_std_typeinfo_vtable_struct cxx_std_typeinfo_vtable = {
	.tiv_whole_object = 0,
	.tiv_whole_type   = NULL, /* This would need to be the `&typeinfo(std::type_info)', but we don't care... */
};

DEFINE_PUBLIC_IDATA(_ZTVN10__cxxabiv117__class_type_infoE, resolve_cxx_std_typeinfo_vtable, SIZEOF_cxx_std_typeinfo_vtable_struct);
DEFINE_PUBLIC_IDATA(_ZTVN10__cxxabiv120__si_class_type_infoE, resolve_cxx_std_typeinfo_vtable, SIZEOF_cxx_std_typeinfo_vtable_struct);
INTERN SECTION_EXCEPT_TEXT struct cxx_std_typeinfo_vtable_struct *
NOTHROW(LIBCCALL resolve_cxx_std_typeinfo_vtable)(void) {
	if (cxx_std_typeinfo_vtable.tiv_getname == NULL) {
		cxx_std_typeinfo_vtable.tiv_getname = &cxx_std_typeinfo_getname;
	}
	return &cxx_std_typeinfo_vtable;
}



LOCAL SECTION_EXCEPT_TEXT WUNUSED ATTR_CONST unsigned int FCALL
size_of_encoded_value(unsigned char encoding) {
#if ((DW_EH_PE_absptr | DW_EH_PE_signed) == DW_EH_PE_signed && \
     (DW_EH_PE_udata2 | DW_EH_PE_signed) == DW_EH_PE_sdata2 && \
     (DW_EH_PE_udata4 | DW_EH_PE_signed) == DW_EH_PE_sdata4 && \
     (DW_EH_PE_udata8 | DW_EH_PE_signed) == DW_EH_PE_sdata8)
	switch (encoding & DW_EH_PE_OFFMASK & ~DW_EH_PE_signed) {
	case DW_EH_PE_udata2:
		return 2;
	case DW_EH_PE_udata4:
		return 4;
	case DW_EH_PE_udata8:
		return 8;
	default: break;
	}
#else /* ... */
	switch (encoding & DW_EH_PE_OFFMASK) {
	case DW_EH_PE_udata2:
	case DW_EH_PE_sdata2:
		return 2;
	case DW_EH_PE_udata4:
	case DW_EH_PE_sdata4:
		return 4;
	case DW_EH_PE_udata8:
	case DW_EH_PE_sdata8:
		return 8;
	default: break;
	}
#endif /* !... */
	return sizeof(void *);
}


#define _CXX_TEMPLATE_ARG_UCHAR   "h"
#define _CXX_TEMPLATE_ARG_USHORT  "t"
#define _CXX_TEMPLATE_ARG_UINT    "j"
#define _CXX_TEMPLATE_ARG_ULONG   "m"
#define _CXX_TEMPLATE_ARG_ULLONG  "y"
#define _CXX_TEMPLATE_ARG_UINT128 "o"
#if __SIZEOF_CHAR__ == 1
#define _CXX_TEMPLATE_ARG_U1 _CXX_TEMPLATE_ARG_UCHAR
#elif __SIZEOF_SHORT__ == 1
#define _CXX_TEMPLATE_ARG_U1 _CXX_TEMPLATE_ARG_USHORT
#elif __SIZEOF_INT__ == 1
#define _CXX_TEMPLATE_ARG_U1 _CXX_TEMPLATE_ARG_UINT
#elif __SIZEOF_LONG__ == 1
#define _CXX_TEMPLATE_ARG_U1 _CXX_TEMPLATE_ARG_ULONG
#elif __SIZEOF_LONG_LONG__ == 1
#define _CXX_TEMPLATE_ARG_U1 _CXX_TEMPLATE_ARG_ULLONG
#endif /* ... == 1 */
#if __SIZEOF_CHAR__ == 2
#define _CXX_TEMPLATE_ARG_U2 _CXX_TEMPLATE_ARG_UCHAR
#elif __SIZEOF_SHORT__ == 2
#define _CXX_TEMPLATE_ARG_U2 _CXX_TEMPLATE_ARG_USHORT
#elif __SIZEOF_INT__ == 2
#define _CXX_TEMPLATE_ARG_U2 _CXX_TEMPLATE_ARG_UINT
#elif __SIZEOF_LONG__ == 2
#define _CXX_TEMPLATE_ARG_U2 _CXX_TEMPLATE_ARG_ULONG
#elif __SIZEOF_LONG_LONG__ == 2
#define _CXX_TEMPLATE_ARG_U2 _CXX_TEMPLATE_ARG_ULLONG
#endif /* ... == 2 */
#if __SIZEOF_CHAR__ == 4
#define _CXX_TEMPLATE_ARG_U4 _CXX_TEMPLATE_ARG_UCHAR
#elif __SIZEOF_SHORT__ == 4
#define _CXX_TEMPLATE_ARG_U4 _CXX_TEMPLATE_ARG_USHORT
#elif __SIZEOF_INT__ == 4
#define _CXX_TEMPLATE_ARG_U4 _CXX_TEMPLATE_ARG_UINT
#elif __SIZEOF_LONG__ == 4
#define _CXX_TEMPLATE_ARG_U4 _CXX_TEMPLATE_ARG_ULONG
#elif __SIZEOF_LONG_LONG__ == 4
#define _CXX_TEMPLATE_ARG_U4 _CXX_TEMPLATE_ARG_ULLONG
#endif /* ... == 4 */
#if __SIZEOF_CHAR__ == 8
#define _CXX_TEMPLATE_ARG_U8 _CXX_TEMPLATE_ARG_UCHAR
#elif __SIZEOF_SHORT__ == 8
#define _CXX_TEMPLATE_ARG_U8 _CXX_TEMPLATE_ARG_USHORT
#elif __SIZEOF_INT__ == 8
#define _CXX_TEMPLATE_ARG_U8 _CXX_TEMPLATE_ARG_UINT
#elif __SIZEOF_LONG__ == 8
#define _CXX_TEMPLATE_ARG_U8 _CXX_TEMPLATE_ARG_ULONG
#elif __SIZEOF_LONG_LONG__ == 8
#define _CXX_TEMPLATE_ARG_U8 _CXX_TEMPLATE_ARG_ULLONG
#endif /* ... == 8 */
#define _CXX_TEMPLATE_ARG_U16 _CXX_TEMPLATE_ARG_UINT128

#define __CXX_TEMPLATE_ARG_Un(n) _CXX_TEMPLATE_ARG_U##n
#define _CXX_TEMPLATE_ARG_Un(n) __CXX_TEMPLATE_ARG_Un(n)


/* Check if "cxx_typename" is able to handle the currently thrown KOS exception.
 * We recognize the following c++ types:
 * - kos::except::class_filter<except_class_t>: "N3kos6except12class_filterILy<"%d" % except_class()>EEE"
 * - kos::except::code_filter<except_code_t>:   "N3kos6except11code_filterILj<"%d" % except_code()>EEE"
 */
LOCAL SECTION_EXCEPT_TEXT WUNUSED ATTR_PURE NONNULL((1)) bool FCALL
kos_exceptfilter_matches_current_exception(char const *cxx_typename) {
	static char const common_prefix[] = "N3kos6except";
	static char const class_filter_prefix[] = "12class_filterIL" _CXX_TEMPLATE_ARG_Un(__SIZEOF_EXCEPT_CLASS_T__);
	static char const code_filter_prefix[] = "11code_filterIL" _CXX_TEMPLATE_ARG_Un(__SIZEOF_EXCEPT_CODE_T__);
	static char const common_suffix[] = "EEE";
	if (bcmp(cxx_typename, common_prefix,
	         COMPILER_STRLEN(common_prefix), sizeof(char)) != 0)
		return false;
	cxx_typename += COMPILER_STRLEN(common_prefix);
	if (bcmp(cxx_typename, class_filter_prefix, COMPILER_STRLEN(class_filter_prefix), sizeof(char)) == 0) {
		cxx_typename += COMPILER_STRLEN(class_filter_prefix);
		if (isdigit(*cxx_typename)) {
			except_class_t filtered_class = *cxx_typename - '0';
			while ((++cxx_typename, isdigit(*cxx_typename))) {
				filtered_class *= 10;
				filtered_class += *cxx_typename - '0';
			}
			if (strcmp(cxx_typename, common_suffix) == 0)
				return filtered_class == except_class();
		}
	} else if (bcmp(cxx_typename, code_filter_prefix, COMPILER_STRLEN(code_filter_prefix), sizeof(char)) == 0) {
		cxx_typename += COMPILER_STRLEN(code_filter_prefix);
		if (isdigit(*cxx_typename)) {
			except_code_t filtered_code = *cxx_typename - '0';
			while ((++cxx_typename, isdigit(*cxx_typename))) {
				filtered_code *= 10;
				filtered_code += *cxx_typename - '0';
			}
			if (strcmp(cxx_typename, common_suffix) == 0)
				return filtered_code == except_code();
		}
	}
	return false;
}


/* This  function  is hooked  by CFI  under `struct unwind_fde_struct::f_persofun'
 * It's exact prototype and behavior are therefor not mandated by how GCC uses it. */
#ifdef __KERNEL__
DEFINE_PUBLIC_ALIAS(__gcc_personality_v0, libc_gxx_personality_v0);
DEFINE_PUBLIC_ALIAS(__gxx_personality_v0, libc_gxx_personality_v0);
INTERN WUNUSED NONNULL((1)) _Unwind_Reason_Code
NOTHROW(EXCEPT_PERSONALITY_CC libc_gxx_personality_v0)(struct _Unwind_Context *__restrict context)
#else /* __KERNEL__ */
INTERN SECTION_EXCEPT_TEXT _Unwind_Reason_Code LIBCCALL
libc_gxx_personality_kernexcept(struct _Unwind_Context *__restrict context, bool phase_2)
#endif /* !__KERNEL__ */
{
	byte_t landingpad_encoding;
	byte_t callsite_encoding;
	byte_t ttype_encoding;
	byte_t const *reader;
	byte_t const *landingpad;
	byte_t const *callsite_end; /* aka. "action_table" */
	byte_t const *type_table;
	size_t callsite_size;

	reader     = (byte_t const *)_Unwind_GetLanguageSpecificData(context);
	landingpad = (byte_t const *)_Unwind_GetRegionStart(context);
	type_table = NULL;

	/* NOTE: `reader' points to a `struct gcc_lsda' */
	landingpad_encoding = *reader++; /* gl_landing_enc */
	if (landingpad_encoding != DW_EH_PE_omit) {
		/* gl_landing_pad */
		landingpad = dwarf_decode_pointer((byte_t const **)&reader, landingpad_encoding,
		                                  sizeof(void *), &context->uc_fde.f_bases);
	}
	ttype_encoding = *reader++; /* gl_typetab_enc */
	if (ttype_encoding != DW_EH_PE_omit) {
		dwarf_uleb128_t offset;
		offset   = dwarf_decode_uleb128((byte_t const **)&reader); /* gl_typetab_off */
		type_table = reader + offset;
	}
	callsite_encoding = *reader++; /* gl_callsite_enc */
	callsite_size     = dwarf_decode_uleb128((byte_t const **)&reader);
	callsite_end      = reader + callsite_size;
next_handler:
	while (reader < callsite_end) {
		uintptr_t start, size, handler, action;
		byte_t const *startpc, *endpc;
		start   = (uintptr_t)dwarf_decode_pointer((byte_t const **)&reader, callsite_encoding, sizeof(void *), &context->uc_fde.f_bases); /* gcs_start */
		size    = (uintptr_t)dwarf_decode_pointer((byte_t const **)&reader, callsite_encoding, sizeof(void *), &context->uc_fde.f_bases); /* gcs_size */
		handler = (uintptr_t)dwarf_decode_pointer((byte_t const **)&reader, callsite_encoding, sizeof(void *), &context->uc_fde.f_bases); /* gcs_handler */
		action  = (uintptr_t)dwarf_decode_uleb128((byte_t const **)&reader);                                                              /* gcs_action */
		startpc = landingpad + start;
		endpc   = startpc + size;

		/* The  callsite-table is sorted  by its start-address, so
		 * we can stop on a handler past the PC we're looking for. */
		if (context->uc_adjpc < startpc)
			break; /* Won't find it anymore... */
		if (context->uc_adjpc >= endpc)
			continue; /* Our handler (if present) is yet-to-come */

		/* Found our handler! */
		if (handler == 0)
			return _URC_CONTINUE_UNWIND; /* No handler -> exception should be propagated. */

		/* Special case for user-space: prior to phase_2, only check if a handler exists. */
#ifndef __KERNEL__
		if (!phase_2) {
			if (!action)
				continue; /* Non-catching handlers aren't viable receivers before phase #2 */
			return _URC_HANDLER_FOUND;
		}
#endif /* !__KERNEL__ */

		/* Do action-based filtering. */
		if (action != 0) {
			/* Scan the action table on the look-out for c++ typeinfo
			 * that  may  be specifying  custom KOS  exception masks. */
			byte_t const *action_record;
			dwarf_sleb128_t ar_filter, ar_disp;
			action_record = callsite_end + action - 1;

			/* NOTE: The format of GCC type  info in exception handlers  is
			 *       explained here: https://www.airs.com/blog/archives/464 */
			for (;;) {
				byte_t const *action_record_p;
				ar_filter = dwarf_decode_sleb128((byte_t const **)&action_record);
				action_record_p = action_record; /* "ar_disp" is relative to the *start* of itself (rather than its end) */
				ar_disp = dwarf_decode_sleb128((byte_t const **)&action_record_p);
				if (ar_filter == 0) {
					/* Cleanup handler (just execute the handler) */
					break;
				} else if (ar_filter > 0) {
					/* Positive filter values are handlers. */
					byte_t const *type_record_ptr;
					byte_t const *type_record_addr;
					uintptr_t ar_filter_scaled;
					struct cxx_std_typeinfo *cxx_type_record;
					char const *cxx_type_name;
					ar_filter_scaled = (uintptr_t)ar_filter * size_of_encoded_value(ttype_encoding);
					type_record_addr = type_table - ar_filter_scaled;
					type_record_ptr = dwarf_decode_pointer(&type_record_addr, ttype_encoding,
					                                       sizeof(void *),
					                                       &context->uc_fde.f_bases);

					/* At this point, `type_record' actually is a (nullable) `std::type_info *' */
					if (type_record_ptr == NULL)
						goto filtered_match; /* A NULL-filter means: catch-all */
					cxx_type_record = (struct cxx_std_typeinfo *)type_record_ptr;
					cxx_type_name   = cxx_type_record->ti_name;
					if unlikely(!cxx_type_name)
						goto filtered_match; /* ??? */
					if (kos_exceptfilter_matches_current_exception(cxx_type_name)) {
						/* Set the switch-register to tell code which type filter ended up matching */
filtered_match:
						/* Yes: this handler *can* handle the exception */
						except_register_state_set_unwind_switch(context->uc_state, ar_filter);
						break;
					}
				} else {
					/* Negative filter values are exception specifications. (whatever that means) */
					break;
				}
				if (ar_disp == 0)
					goto next_handler;
				action_record += ar_disp;
			}
		}

		/* The ABI wants us to fill %eax with a pointer to the exception (`_Unwind_Exception').
		 * However, since KOS exception is  kept a bit simpler (so-as  to allow it to  function
		 * without the need of dynamic memory allocation), just pass TLS exception data. */
#ifdef __KERNEL__
		except_register_state_set_unwind_exception(context->uc_state, except_args());
#else /* __KERNEL__ */
		/* Must assign the fake KOS unwind exception so "libc_Unwind_Resume_impl()" works. */
		except_register_state_set_unwind_exception(context->uc_state, libc_get_kos_unwind_exception());
#endif /* !__KERNEL__ */

		/* Jump to the associated handler */
		except_register_state_setpc(context->uc_state, landingpad + handler);
		return _URC_INSTALL_CONTEXT;
	}

	/* Default behavior: abort exception handling (this function was marked as NOTHROW) */
	return _URC_END_OF_STACK;
}


#ifndef __KERNEL__
/* Define these functions strongly, since we *always* want to  intercept
 * call to these **BEFORE** libstdc++ can  see them. This is because  we
 * need to implement our own, custom handling for "_UEC_KERNKOS" without
 * libstdc++ being able to see those exception.
 *
 * At runtime, we then lazily forward anything that isn't _UEC_KERNKOS
 * to the next implementation (which should be libstdc++'s if the load
 * order was set-up correctly)
 *
 * When libc ended up being loaded **AFTER** libstdc++, we still have a
 * bit of the upper hand, since KOS exception throwing always has to go
 * through libc, and "../libc/except.c" tries  to handle the case of  a
 * KOS exception, and a personality function originating from libstdc++
 * (s.a. `is_standard_gcc_except_table_personality()') by ignoring  the
 * personality function  and calling  `libc_gxx_personality_kernexcept'
 * instead.
 *
 * As such, custom KOS exception handling should always work properly,
 * even if libstdc++ was loaded, and even if it was loaded before libc
 * was. */
DEFINE_PUBLIC_ALIAS(__gxx_personality_v0, libc_gxx_personality_v0);
DEFINE_PUBLIC_ALIAS(__gcc_personality_v0, libc_gxx_personality_v0);

PRIVATE SECTION_EXCEPT_TEXT WUNUSED _Unwind_Personality_Fn LIBCCALL
libc_get_next_gxx_personality_v0__uncached(void) {
	/* The perfect usage-example for "RTLD_NEXT" -- find any mention of "__gxx_personality_v0"
	 * that  appears **AFTER** the calling module (our's;  aka: libc's) in the dynamic linkage
	 * order.
	 *
	 * iow: when libstdc++ was loaded **AFTER** libc, this will return it's impl. */
	void *result = dlsym(RTLD_NEXT, "__gxx_personality_v0");
	if (result == NULL)
		result = dlsym(RTLD_NEXT, "__gcc_personality_v0");
	return (_Unwind_Personality_Fn)result;
}

PRIVATE SECTION_EXCEPT_BSS _Unwind_Personality_Fn libc_next_gxx_personality_v0 = NULL;
PRIVATE SECTION_EXCEPT_TEXT WUNUSED _Unwind_Personality_Fn LIBCCALL
libc_get_next_gxx_personality_v0(void) {
	if (libc_next_gxx_personality_v0 == NULL)
		libc_next_gxx_personality_v0 = libc_get_next_gxx_personality_v0__uncached();
	return libc_next_gxx_personality_v0;
}

INTERN SECTION_EXCEPT_TEXT _Unwind_Reason_Code LIBCCALL
libc_gxx_personality_v0(int version /* = 1 */,
                        _Unwind_Action actions,
                        _Unwind_Exception_Class exception_class,
                        struct _Unwind_Exception *ue_header,
                        struct _Unwind_Context *context) {

	/* Special handling for KOS exceptions... */
	if likely(version == 1 && exception_class == _UEC_KERNKOS)
		return libc_gxx_personality_kernexcept(context, (actions & _UA_FORCE_UNWIND) != 0);

	/* Anything else gets forwarded to the next gxx personality as per
	 * the dynamic linking order. */
	{
		_Unwind_Personality_Fn next = libc_get_next_gxx_personality_v0();
		if likely(next != NULL)
			return (*next)(version, actions, exception_class, ue_header, context);
	}

	/* Fallback: no piece of code  that's currently loaded can  handle
	 * this type of exception using a gcc-compatible exception handler
	 * table. */
	(void)actions;
	(void)exception_class;
	(void)ue_header;
	(void)context;
	return _URC_FATAL_PHASE1_ERROR;
}
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_HYBRID_EXCEPT_PERSONALITY_C */
