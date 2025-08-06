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
#ifndef _LIBUNWIND_EXCEPT_H
#define _LIBUNWIND_EXCEPT_H 1

#include "api.h"

#if defined(__KOS__) && defined(__KERNEL__)
/* The  KOS kernel  uses a different  exception ABI that  isn't compatible with
 * IA-64, since it doesn't need to ensure binary compatibility with regular C++
 * exceptions, and only needs to support KOS exceptions (<kos/except.h>) */
#include <kernel/rt/except-personality.h>
#else /* __KOS__ && __KERNEL__ */
#include <__crt.h>
#include <features.h>

#include <hybrid/__wordbits.h>

#include <bits/types.h>
#include <kos/except.h>

#include <libunwind/asm/features.h>

#include "eh_frame.h"

#ifdef __KOS__
/* Exception class for KOS kernel exceptions (exceptions thrown through <kos/except.h>)
 * NOTE: Exceptions of this class behave somewhat different from  other
 *       classes, in that unwinding happens (usually) in a single pass:
 * >> FOREACH(frame: stack) {
 * >>     context.uc_fde   = frame.fde();
 * >>     context.uc_state = GET_RETURN_REGISTER_STATE();
 * >>     reason = cfa.personality(1,
 * >>                              _UA_CLEANUP_PHASE | _UA_FORCE_UNWIND,
 * >>                              _UEC_KERNKOS,
 * >>                              KOS_EXCEPTION,
 * >>                              &context);
 * >>     if (reason == _URC_INSTALL_CONTEXT)
 * >>         RETURN_TO(context.uc_state);
 * >>     if (reason != _URC_CONTINUE_UNWIND)
 * >>         PRINT_ERROR_AND_TERMINATE();
 * >> }
 * However, personality function should still implement 2-step unwinding support,
 * as a handler-search phase is still performed during mode#4 exception handling.
 * For more information, see `<kos/except-handler.h>'
 */
#define _UEC_KERNKOS __ENCODE_INT64('K', 'E', 'R', 'N', 'K', 'O', 'S', '\0')
#endif /* __KOS__ */

#ifdef __CC__
__DECL_BEGIN

#if 0
/* BEGIN::: GCC DATA LAYOUT */
struct ATTR_PACKED gcc_lsda_callsite {
	/* Exception handling in GCC works as follows:
	 *   - If a function doesn't have a .cfi_personality function,
	 *     exceptions   will  simply  be  propagated  through  it.
	 *   - If  a function has `__gxx_personality_v0' or `__gcc_personality_v0'
	 *     as its personality function, its callsite table is searched for the
	 *     associated unwind PC.
	 *      - If the unwind PC wasn't found, then the program must std::terminate()
	 *      - If the unwind PC was found as a valid call-site,
	 *        then the associated action must be taken. */
	uintptr_t gcs_start;       /* [ENCODING(:gl_callsite_enc)]
	                            * Offset from the LSDA  landing base to the  first instruction byte that  is
	                            * covered by this exception handler. (i.e. to the start of guarded assembly) */
	uintptr_t gcs_size;        /* [ENCODING(:gl_callsite_enc)]
	                            * The number of contiguous bytes of text guarded, starting at `gcs_start' */
	uintptr_t gcs_handler;     /* [ENCODING(:gl_callsite_enc)]
	                            * Offset from the LSDA  landing base to the  first instruction apart of  the
	                            * exception handler's executing block. (i.e. the start of the catch-handler)
	                            * If there is no handler, this field is ZERO(0)
	                            * NOTE: Dependent on  architecture, certain  registers must  be filled  with
	                            *       exception-related data before the runtime may jump to this location. */
	dwarf_uleb128_t gcs_action;/* The action to take???
	                            * When zero, don't perform any action. (continue propagating the exception)
	                            * Otherwise,  this  is   1+  a   byte  offset  into   the  action   table?? */
};
struct ATTR_PACKED gcc_lsda {
	/* Format for the GCC LanguageSpecificData pointed to by `unwind_fde_struct::f_lsdaaddr' */
	u8              gl_landing_enc;  /* Encoding used for `gl_landing_pad' (One of `DW_EH_PE_*') */
	uintptr_t       gl_landing_pad;  /* [exists_if(gl_landing_enc != DW_EH_PE_omit)]
	                                  * [ENCODING(gl_landing_enc)] Base address of the landing pad
	                                  * When this field doesn't exist, `unwind_fde_struct::f_pcstart' will be used instead.
	                                  * -> This field usually doesn't exist. */
	u8              gl_typetab_enc;  /* Encoding used for fields in the type-table (One of `DW_EH_PE_*') */
	dwarf_uleb128_t gl_typetab_off;  /* [exists_if(gl_typetab_enc != DW_EH_PE_omit)]
	                                  * Offset from the next field to the start of the types
	                                  * table   used   for    matching   exception    types. */
	u8              gl_callsite_enc; /* Encoding used for fields in the call-site table (One of `DW_EH_PE_*') */
	dwarf_uleb128_t gl_callsite_siz; /* The size of the call-site table (in bytes) */
	/* -- This is where the callsite table goes. */
	struct gcc_lsda_callsite gl_callsites[1]; /* [* = AUTO(sizeof(.) == gl_callsite_siz)] */
	/* -- This is where the type table goes. */
};
/* END::: GCC DATA LAYOUT */
#endif


/* Unwind personality function  integration to allow  for exception  handling.
 * Note that most of the stuff required during linking is actually implemented
 * as part of libc.so, rather than libunwind.so! */

typedef enum {
	_URC_NO_REASON                = 0, /* Continue-return value for `_Unwind_Stop_Fn' and `_Unwind_Trace_Fn' */
	_URC_FOREIGN_EXCEPTION_CAUGHT = 1, /* ??? (always passed as first argument to `_Unwind_Exception::exception_cleanup') */
	_URC_FATAL_PHASE2_ERROR       = 2, /* Fatal error during `_UA_CLEANUP_PHASE' */
	_URC_FATAL_PHASE1_ERROR       = 3, /* Fatal error during `_UA_SEARCH_PHASE' */
	_URC_NORMAL_STOP              = 4, /* ??? */
	_URC_END_OF_STACK             = 5, /* Don't continue unwinding */
	_URC_HANDLER_FOUND            = 6, /* During `_UA_SEARCH_PHASE':  A handler for the exception was found (continue with `_UA_CLEANUP_PHASE') */
	_URC_INSTALL_CONTEXT          = 7, /* During `_UA_CLEANUP_PHASE': The handler was applied. - Resume execution */
	_URC_CONTINUE_UNWIND          = 8  /* During  `_UA_SEARCH_PHASE': Continue searching in the next frame.
	                                    * During `_UA_CLEANUP_PHASE': Continue unwinding to the next frame. */
#ifdef LIBUNWIND_HAVE_UNWIND_VRS
	,
	_URC_OK      = _URC_NO_REASON, /* ARM-specific alias */
	_URC_FAILURE = 9               /* unspecified failure of some kind */
#endif /* LIBUNWIND_HAVE_UNWIND_VRS */
#if defined(__KOS__) && defined(__USE_KOS)
	,
	_URC_INSTALL_CONTEXT_NOW = 100, /* During `_UA_CLEANUP_PHASE': Same as `_URC_INSTALL_CONTEXT', but don't adjust for `DW_CFA_GNU_args_size' */
#endif /* __KOS__ && __USE_KOS */
} _Unwind_Reason_Code;


typedef int _Unwind_Action; /* Set of `_UA_*' */
#define _UA_SEARCH_PHASE  1   /* First phase: Search for a handler */
#define _UA_CLEANUP_PHASE 2   /* First phase: Unwind up to some handler (execute finally blocks) */
#define _UA_HANDLER_FRAME 4   /* Set alongside `_UA_CLEANUP_PHASE' when the frame containing
                               * the  handler  from  `_UA_SEARCH_PHASE'  has  been  reached. */
#define _UA_FORCE_UNWIND  8   /* ??? Force unwinding ??? */
#define _UA_END_OF_STACK  16  /* Set if unwinding has become impossible. */

typedef __uintptr_t _Unwind_Word;            /* Unsigned unwind data-word */
typedef __intptr_t  _Unwind_Sword;           /* Signed unwind data-word */
typedef __uintptr_t _Unwind_Ptr;             /* Unwind pointer */
typedef __uintptr_t _Unwind_Internal_Ptr;    /* Unwind pointer */

/* Unwind exception class (One of `_UEC_*'; may also be some unrecognized value) */
#ifdef LIBUNWIND_HAVE_UNWIND_VRS
typedef char _Unwind_Exception_Class[8];
#else /* LIBUNWIND_HAVE_UNWIND_VRS */
typedef __uint64_t _Unwind_Exception_Class;
#endif /* !LIBUNWIND_HAVE_UNWIND_VRS */

struct _Unwind_Exception;
typedef __ATTR_NONNULL_T((2)) void
(__LIBKCALL *_Unwind_Exception_Cleanup_Fn)(_Unwind_Reason_Code __reason /* = _URC_FOREIGN_EXCEPTION_CAUGHT */,
                                           struct _Unwind_Exception *__restrict __exc);

#ifdef LIBUNWIND_HAVE_UNWIND_VRS
typedef _Unwind_Word _Unwind_EHT_Header;

/* Unwind state (first argument of `_Unwind_Personality_Fn') */
typedef enum {
	_US_VIRTUAL_UNWIND_FRAME  = 0,
	_US_UNWIND_FRAME_STARTING = 1,
	_US_UNWIND_FRAME_RESUME   = 2,
	_US_ACTION_MASK           = 3,
	_US_FORCE_UNWIND          = 8,
	_US_END_OF_STACK          = 16
} _Unwind_State;

/* Virtual Register Set*/
typedef enum {
	_UVRSC_CORE  = 0, /* integer register */
	_UVRSC_VFP   = 1, /* vfp */
	_UVRSC_FPA   = 2, /* fpa */
	_UVRSC_WMMXD = 3, /* Intel WMMX data register */
	_UVRSC_WMMXC = 4  /* Intel WMMX control register */
} _Unwind_VRS_RegClass;

typedef enum {
	_UVRSD_UINT32 = 0,
	_UVRSD_VFPX   = 1,
	_UVRSD_FPAX   = 2,
	_UVRSD_UINT64 = 3,
	_UVRSD_FLOAT  = 4,
	_UVRSD_DOUBLE = 5
} _Unwind_VRS_DataRepresentation;

typedef enum {
	_UVRSR_OK              = 0,
	_UVRSR_NOT_IMPLEMENTED = 1,
	_UVRSR_FAILED          = 2
} _Unwind_VRS_Result;

/* Frame unwinding state.  */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("data")
#pragma push_macro("next")
#pragma push_macro("bytes_left")
#pragma push_macro("words_left")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef data
#undef next
#undef bytes_left
#undef words_left
typedef struct {
	_Unwind_Word  data;       /* ??? */
	_Unwind_Word *next;       /* ??? */
	__uint8_t     bytes_left; /* ??? */
	__uint8_t     words_left; /* ??? */
} __gnu_unwind_state;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("words_left")
#pragma pop_macro("bytes_left")
#pragma pop_macro("next")
#pragma pop_macro("data")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* LIBUNWIND_HAVE_UNWIND_VRS */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("exception_class")
#pragma push_macro("exception_cleanup")
#pragma push_macro("private_1")
#pragma push_macro("private_2")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef exception_class
#undef exception_cleanup
#undef private_1
#undef private_2
#ifdef LIBUNWIND_HAVE_UNWIND_VRS
/* NOTE: On ARM/VRS, this structure is aliased as `_Unwind_Control_Block' */
#define _Unwind_Control_Block _Unwind_Exception
struct __ATTR_ALIGNED(8) _Unwind_Exception
#else /* LIBUNWIND_HAVE_UNWIND_VRS */
struct _Unwind_Exception
#endif /* !LIBUNWIND_HAVE_UNWIND_VRS */
{
	_Unwind_Exception_Class      exception_class;   /* Exception class (one of `_UEC_*') */
	_Unwind_Exception_Cleanup_Fn exception_cleanup; /* [0..1] Exception cleanup function
	                                                 * This callback is invoked once the exception has been handled. */
#ifdef LIBUNWIND_HAVE_UNWIND_VRS
	struct {
		_Unwind_Word reserved1; /* ??? */
		_Unwind_Word reserved2; /* ??? */
		_Unwind_Word reserved3; /* ??? */
		_Unwind_Word reserved4; /* ??? */
		_Unwind_Word reserved5; /* ??? */
	} unwinder_cache;
	struct {
		_Unwind_Word sp;            /* ??? */
		_Unwind_Word bitpattern[5]; /* ??? */
	} barrier_cache;
	struct {
		_Unwind_Word bitpattern[4]; /* ??? */
	} cleanup_cache;
	struct {
		_Unwind_Word fnstart;      /* ??? */
		_Unwind_EHT_Header *ehtp;  /* ??? */
		_Unwind_Word additional;   /* ??? */
		_Unwind_Word reserved1;    /* ??? */
	} pr_cache;
#else /* LIBUNWIND_HAVE_UNWIND_VRS */
	_Unwind_Word private_1; /* ... */
	_Unwind_Word private_2; /* ... */
#endif /* !LIBUNWIND_HAVE_UNWIND_VRS */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("private_2")
#pragma pop_macro("private_1")
#pragma pop_macro("exception_cleanup")
#pragma pop_macro("exception_class")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

struct _Unwind_Context /* Opaque structure */
#ifdef __USE_KOS
{
#ifdef LIBUNWIND_HAVE_UNWIND_VRS
	/* TODO: `.ARM.extab' data (and some way of telling if we're not actually using the `uc_fde'-format) */
	unwind_fde_t             uc_fde;            /* FDE descriptor. */
#else /* LIBUNWIND_HAVE_UNWIND_VRS */
	unwind_fde_t             uc_fde;            /* FDE descriptor. */
#endif /* !LIBUNWIND_HAVE_UNWIND_VRS */
	except_register_state_t *uc_state;          /* [1..1] The register state that is loaded when resuming execution. */
	void const              *uc_adjpc;          /* Currently relevant program counter. Same as PC in `uc_state',
	                                             * but already adjusted as per `uc_pc_before_insn' (such that it
	                                             * can always be used in "uc_adjpc >= start && uc_adjpc < end") */
	__BOOL                   uc_pc_before_insn; /* Non-zero if the last FDE was a signal frame. */
}
#endif /* __USE_KOS */
;

typedef _Unwind_Reason_Code
(__LIBKCALL *_Unwind_Stop_Fn)(int __version /*=1*/,
                              _Unwind_Action __actions,
                              _Unwind_Exception_Class __exception_class,
                              struct _Unwind_Exception *__exc,
                              struct _Unwind_Context *__context, void *__stop_arg);

typedef _Unwind_Reason_Code
(__LIBKCALL *_Unwind_Trace_Fn)(struct _Unwind_Context *__context, void *__trace_arg);



/* NOTE: `__gcc_personality_v0' has the prototype `_Unwind_Personality_Fn' */
#ifdef LIBUNWIND_HAVE_UNWIND_VRS
typedef __ATTR_NONNULL_T((2, 3)) _Unwind_Reason_Code
__NOTHROW_NCX_T(__LIBKCALL *_Unwind_Personality_Fn)(_Unwind_State __state,
                                                    struct _Unwind_Control_Block *__ucb,
                                                    struct _Unwind_Context *__ctx);
typedef _Unwind_Personality_Fn personality_routine;
#else /* LIBUNWIND_HAVE_UNWIND_VRS */
typedef __ATTR_NONNULL_T((4, 5)) _Unwind_Reason_Code
__NOTHROW_NCX_T(__LIBKCALL *_Unwind_Personality_Fn)(int __version /* = 1 */,
                                                    _Unwind_Action __actions,
                                                    _Unwind_Exception_Class __exception_class,
                                                    struct _Unwind_Exception *__restrict __ue_header,
                                                    struct _Unwind_Context *__restrict __context);
#endif /* !LIBUNWIND_HAVE_UNWIND_VRS */

/* TODO: Declare these functions as __LIBKCALL, rather than __LIBCCALL! */

/* Exception ABI functions exported by libc.so */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_RaiseException)
__CDECLARE(__ATTR_NONNULL((1)),_Unwind_Reason_Code,__NOTHROW_NCX,_Unwind_RaiseException,(struct _Unwind_Exception *__restrict __exception_object),(__exception_object))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_RaiseException */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_Resume)
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_NONNULL((1)),__NOTHROW_NCX,_Unwind_Resume,(struct _Unwind_Exception *__restrict __exception_object),(__exception_object))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_Resume */
/* Why wasn't this called `_Unwind_ResumeOrRethrow'???
 * Everything else uses proper CamelCase, so why does this one do so this half-heartedly?
 * s.a. https://refspecs.linuxfoundation.org/LSB_5.0.0/LSB-Core-generic/LSB-Core-generic/baselib--unwind-resume-or-rethrow.html */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_Resume_or_Rethrow)
__CDECLARE(__ATTR_NONNULL((1)),_Unwind_Reason_Code,__NOTHROW_NCX,_Unwind_Resume_or_Rethrow,(struct _Unwind_Exception *__restrict __exception_object),(__exception_object))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_Resume_or_Rethrow */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_DeleteException)
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_Unwind_DeleteException,(struct _Unwind_Exception *__restrict __exception_object),(__exception_object))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_DeleteException */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_GetGR)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),_Unwind_Word,__NOTHROW_NCX,_Unwind_GetGR,(struct _Unwind_Context __KOS_FIXED_CONST *__restrict __context, int __index),(__context,__index))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_GetGR */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_SetGR)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_NONNULL((1)),__NOTHROW_NCX,_Unwind_SetGR,(struct _Unwind_Context *__restrict __context, int __index, _Unwind_Word __value),(__context,__index,__value))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_SetGR */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_GetIP)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),_Unwind_Ptr,__NOTHROW_NCX,_Unwind_GetIP,(struct _Unwind_Context __KOS_FIXED_CONST *__restrict __context),(__context))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_GetIP */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_SetIP)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_NONNULL((1)),__NOTHROW_NCX,_Unwind_SetIP,(struct _Unwind_Context *__restrict __context, _Unwind_Ptr __value),(__context,__value))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_SetIP */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_GetLanguageSpecificData)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),_Unwind_Ptr,__NOTHROW_NCX,_Unwind_GetLanguageSpecificData,(struct _Unwind_Context __KOS_FIXED_CONST *__restrict __context),(__context))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_GetLanguageSpecificData */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_GetRegionStart)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),_Unwind_Ptr,__NOTHROW_NCX,_Unwind_GetRegionStart,(struct _Unwind_Context __KOS_FIXED_CONST *__restrict __context),(__context))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_GetRegionStart */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_GetIPInfo)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),_Unwind_Ptr,__NOTHROW_NCX,_Unwind_GetIPInfo,(struct _Unwind_Context __KOS_FIXED_CONST *__restrict __context, int *__restrict __p_ip_before_insn),(__context,__p_ip_before_insn))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_GetIPInfo */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_ForcedUnwind)
__CDECLARE(__ATTR_NONNULL((1, 2)),_Unwind_Reason_Code,__NOTHROW_NCX,_Unwind_ForcedUnwind,(struct _Unwind_Exception *__restrict __exception_object, _Unwind_Stop_Fn __stop, void *__stop_arg),(__exception_object,__stop,__stop_arg))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_ForcedUnwind */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_Backtrace)
__CDECLARE(__ATTR_NONNULL((1)),_Unwind_Reason_Code,__NOTHROW_NCX,_Unwind_Backtrace,(_Unwind_Trace_Fn __func, void *__arg),(__func,__arg))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_Backtrace */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_GetCFA)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),_Unwind_Word,__NOTHROW_NCX,_Unwind_GetCFA,(struct _Unwind_Context /*__KOS_FIXED_CONST*/ *__restrict __context),(__context)) /* Only non-const for lazy initialized fields! */
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_GetCFA */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_GetDataRelBase)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),_Unwind_Ptr,__NOTHROW_NCX,_Unwind_GetDataRelBase,(struct _Unwind_Context /*__KOS_FIXED_CONST*/ *__restrict __context),(__context)) /* Only non-const for lazy initialized fields! */
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_GetDataRelBase */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_GetTextRelBase)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),_Unwind_Ptr,__NOTHROW_NCX,_Unwind_GetTextRelBase,(struct _Unwind_Context /*__KOS_FIXED_CONST*/ *__restrict __context),(__context)) /* Only non-const for lazy initialized fields! */
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_GetTextRelBase */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_FindEnclosingFunction)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,void *,__NOTHROW_NCX,_Unwind_FindEnclosingFunction,(void __KOS_FIXED_CONST *__pc),(__pc))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_FindEnclosingFunction */

/* arm-specific `_Unwind_VRS_*' API */
#ifdef LIBUNWIND_HAVE_UNWIND_VRS
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_VRS_Set)
__CDECLARE(__ATTR_NONNULL((1, 5)),_Unwind_VRS_Result,__NOTHROW_NCX,_Unwind_VRS_Set,(struct _Unwind_Context *__ctx, _Unwind_VRS_RegClass __cls, _Unwind_Word __regno, _Unwind_VRS_DataRepresentation __repr, void /*__KOS_FIXED_CONST*/ *__src),(__ctx,__cls,__regno,__repr,__src))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_VRS_Set */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_VRS_Get)
__CDECLARE(__ATTR_NONNULL((1, 5)),_Unwind_VRS_Result,__NOTHROW_NCX,_Unwind_VRS_Get,(struct _Unwind_Context /*__KOS_FIXED_CONST*/ *__ctx, _Unwind_VRS_RegClass __cls, _Unwind_Word __regno, _Unwind_VRS_DataRepresentation __repr, void *__dst),(__ctx,__cls,__regno,__repr,__dst))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_VRS_Get */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_VRS_Pop)
__CDECLARE(__ATTR_NONNULL((1)),_Unwind_VRS_Result,__NOTHROW_NCX,_Unwind_VRS_Pop,(struct _Unwind_Context *__ctx, _Unwind_VRS_RegClass __cls, _Unwind_Word __regno, _Unwind_VRS_DataRepresentation __repr),(__ctx,__cls,__regno,__repr))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_VRS_Pop */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE__Unwind_Complete)
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_Unwind_Complete,(struct _Unwind_Control_Block *__ucbp),(__ucbp))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE__Unwind_Complete */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE___gnu_unwind_frame)
__CDECLARE(__ATTR_NONNULL((1, 2)),_Unwind_Reason_Code,__NOTHROW_NCX,__gnu_unwind_frame,(struct _Unwind_Control_Block *__ucb, struct _Unwind_Context *__ctx),(__ucb,__ctx))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE___gnu_unwind_frame */
#if !defined(__CRT_KOS_PRIMARY) || defined(__CRT_HAVE___gnu_unwind_execute)
__CDECLARE(__ATTR_NONNULL((1, 2)),_Unwind_Reason_Code,__NOTHROW_NCX,__gnu_unwind_execute,(struct _Unwind_Context *__ctx, __gnu_unwind_state *__state),(__ctx,__state))
#endif /* !__CRT_KOS_PRIMARY || __CRT_HAVE___gnu_unwind_execute */
#endif /* LIBUNWIND_HAVE_UNWIND_VRS */

__DECL_END
#endif /* __CC__ */
#endif /* !__KOS__ || !__KERNEL__ */

#endif /* !_LIBUNWIND_EXCEPT_H */
