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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_CC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_CC_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

/* Clear global caches. */

#ifdef __CC__
DECL_BEGIN

#ifndef __gfp_t_defined
#define __gfp_t_defined
typedef unsigned int gfp_t;
#endif /* !__gfp_t_defined */

/* Simplified cache-clear state for `system_cc_s' */
#ifndef __ccstate_t_defined
#define __ccstate_t_defined
typedef uint32_t ccstate_t;
#define CCSTATE_INIT       0
#define ccstate_init(self) (void)(*(self) = CCSTATE_INIT)
#endif /* !__ccstate_t_defined */

struct ccinfo {
	gfp_t            ci_gfp;      /* [const] Flags for recursive allocations, possibly or'd with GFP_ATOMIC. */
#ifdef __WANT_CCINFO__ci_state
	union {
		struct {
			uint16_t ci_version;  /* [in]  Version number from previous cache-clear  attempts.
			                       *       Set to `0' during the initial call to `system_cc()'
			                       * [out] New system cache version. */
			uint16_t ci_attempt;  /* [in|out] Attempt number. */
		};
		ccstate_t   _ci_state;    /* [in|out] Version state. */
	};
#else /* __WANT_CCINFO__ci_state */
	uint16_t         ci_version;  /* [in]  Version number from previous cache-clear  attempts.
	                               *       Set to `0' during the initial call to `system_cc()'
	                               * [out] New system cache version. */
	uint16_t         ci_attempt;  /* [in|out] Attempt number. */
#endif /* !__WANT_CCINFO__ci_state */
	size_t           ci_bytes;    /* [out] Approximation of virtual/physical memory that became available (in bytes). */
	size_t           ci_minbytes; /* [const] Minimum # of bytes to free before stopping. */
};
#define ccinfo_init(self, gfp, minbytes_hint) \
	((self)->ci_gfp      = (gfp),             \
	 (self)->ci_version  = 0,                 \
	 (self)->ci_attempt  = 0,                 \
	 (self)->ci_minbytes = (minbytes_hint))

/* Check if operation must be non-blocking. */
#define ccinfo_noblock(self) ((self)->ci_gfp & GFP_ATOMIC)
#define ccinfo_isdone(self)  ((self)->ci_bytes >= (self)->ci_minbytes)
#define ccinfo_gfp(self)     (self)->ci_gfp

/* Account for memory being freed. */
#define ccinfo_account(self, num_bytes) \
	((self)->ci_bytes += (num_bytes))


/* Max # of attempts before unconditional give-up. ("/proc/kos/cc-max-attempts")
 *
 * This  limit is needed in order to prevent infinite loops due to a piece of code
 * that  tries (and fails) to allocate a large amount of memory, but before it can
 * do that, it succeeds in allocating a  small amount of memory that somehow  ends
 * up in some sort of cache (a great example is the unwind-cache of drivers, which
 * is used by trace-malloc, which in turn is used every time you do `kmalloc()') */
DATDEF uint16_t system_cc_maxattempts;


/* Clear global system caches.
 * @param: info: [in|out] Specification on how caches should be cleared.
 * @return: true:  At least something (may) have become available
 *                 since the last time you tried to clear caches.
 * @return: false: Nothing could be cleared :( */
FUNDEF NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) __BOOL
NOTHROW(FCALL system_cc)(struct ccinfo *__restrict info);

/* Helper  wrapper  for  `system_cc()'  that   throws
 * `E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY' on error. */
FUNDEF NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void FCALL
system_cc_virtual_memory(struct ccinfo *__restrict info)
		THROWS(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY);

/* Simplified cache-clear functions that always try to free at least 1
 * byte,  but will get more aggressive as  attempts go on. This is the
 * preferred way of  doing cache-clear operations  and should be  used
 * like this:
 * >>     ccstate_t ccstate = CCSTATE_INIT;
 * >> again:
 * >>     result = try_allocate();
 * >>     if (!result)
 * >>         goto nomem;
 * >>     return result;
 * >> nomem:
 * >>     if (system_cc_s(&ccstate))
 * >>         goto again;
 * >>     THROW(E_BADALLOC);
 * Note that nesting within `try_allocate()'  is OK, though should  be
 * avoided for the sake of performance and more effective cc-handling. */
FUNDEF ATTR_COLD WUNUSED ATTR_INOUT(1) __BOOL NOTHROW(FCALL system_cc_s)(ccstate_t *__restrict p_state);
FUNDEF NOBLOCK ATTR_COLD WUNUSED ATTR_INOUT(1) __BOOL NOTHROW(FCALL system_cc_s_noblock)(ccstate_t *__restrict p_state);
FUNDEF NOBLOCK_IF(gfp & GFP_ATOMIC) ATTR_COLD WUNUSED  ATTR_INOUT(1) __BOOL
NOTHROW(FCALL system_cc_s_ex)(ccstate_t *__restrict p_state, gfp_t gfp);


/************************************************************************/
/* Helper functions to clear the caches of known objects.               */
/************************************************************************/
struct ringbuffer;
struct linebuffer;

/* Free unused space from `self'. */
FUNDEF NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_ringbuffer)(struct ringbuffer *__restrict self,
                                    struct ccinfo *__restrict info);

/* Free unused space from `self'. */
FUNDEF NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1, 2)) void
NOTHROW(KCALL system_cc_linebuffer)(struct linebuffer *__restrict self,
                                    struct ccinfo *__restrict info);

/* Clear buffers associated with a given handle object. */
FUNDEF NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((2, 3)) void
NOTHROW(KCALL system_cc_handle)(uintptr_half_t handle_typ,
                                void *__restrict handle_ptr,
                                struct ccinfo *__restrict info);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_CC_H */
