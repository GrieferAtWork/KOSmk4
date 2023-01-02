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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_ISR_H
#define GUARD_KERNEL_INCLUDE_KERNEL_ISR_H 1

#include <kernel/compiler.h>

#include <kernel/arch/isr.h>
#include <kernel/types.h>

#include <kos/kernel/handle.h>

#include <stdbool.h>

#ifdef __CC__
DECL_BEGIN

struct driver;

/* Prototype for a device-related ISR (Interrupt Service Routine)
 * @return: true:  The interrupt was successfully handled.
 * @return: false: The interrupt must have been meant for some other handler. */
typedef NOBLOCK NOPREEMPT bool NOTHROW_T(FCALL *isr_function_t)(void *arg);

/* A greedy ISR function doesn't need to check if an interrupt actually belongs to
 * its associated device. Instead, it is installed as the last one in line for its
 * associated interrupt vector, or as the only callback for that vector. */
typedef NOBLOCK NOPREEMPT void NOTHROW_T(FCALL *isr_greedy_function_t)(void *arg);

/* Register ISR handlers, either by automatically selecting an
 * appropriate  vector, or by  specifying the required vector.
 * WARNING: The caller is responsible to ensure that any given func+arg
 *          combination will only be registered once.
 * @return: ISR_VECTOR_INVALID: The given `func' maps to a driver that is currently being finalized.
 * @throws: E_SEGFAULT:         The given `func' doesn't map to the static segment of any known driver.
 * @throws: E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS: The given, or all vectors are already in use,
 *                                                     or the  given  vector  cannot  be  allocated. */
FUNDEF isr_vector_t KCALL isr_register(isr_function_t func, void *arg) THROWS(E_BADALLOC);
FUNDEF isr_vector_t KCALL isr_register_at(isr_vector_t vector, isr_function_t func, void *arg) THROWS(E_BADALLOC);
FUNDEF isr_vector_t KCALL isr_register_greedy(isr_greedy_function_t func, void *arg) THROWS(E_BADALLOC, E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS);
FUNDEF isr_vector_t KCALL isr_register_greedy_at(isr_vector_t vector, isr_greedy_function_t func, void *arg) THROWS(E_BADALLOC, E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS);

/* Unregister a callback registered
 * When `vector' is equal to `ISR_VECTOR_INVALID', true is returned and the function is a no-op
 * Also: Yes, these unregister functions can throw E_BADALLOC, so they should only
 *       be called from  driver-level finalizers, rather  than object-level  ones.
 * @return: true:  The ISR was successfully unregistered.
 * @return: false: No ISR matching the given arguments was registered for `vector' */
#if defined(__cplusplus) && !defined(__NO_ASMNAME)
extern "C++" {
FUNDEF NOBLOCK bool KCALL isr_unregister(isr_function_t func) THROWS(E_BADALLOC) ASMNAME("isr_unregister_any");
FUNDEF NOBLOCK bool KCALL isr_unregister(isr_greedy_function_t func) THROWS(E_BADALLOC) ASMNAME("isr_unregister_any");
FUNDEF NOBLOCK bool KCALL isr_unregister(isr_function_t func, void *arg) THROWS(E_BADALLOC) ASMNAME("isr_unregister");
FUNDEF NOBLOCK bool KCALL isr_unregister(isr_greedy_function_t func, void *arg) THROWS(E_BADALLOC) ASMNAME("isr_unregister");
FUNDEF NOBLOCK bool KCALL isr_unregister_at(isr_vector_t vector, isr_function_t func) THROWS(E_BADALLOC) ASMNAME("isr_unregister_any_at");
FUNDEF NOBLOCK bool KCALL isr_unregister_at(isr_vector_t vector, isr_greedy_function_t func) THROWS(E_BADALLOC) ASMNAME("isr_unregister_any_at");
FUNDEF NOBLOCK bool KCALL isr_unregister_at(isr_vector_t vector, isr_function_t func, void *arg) THROWS(E_BADALLOC) ASMNAME("isr_unregister_at");
FUNDEF NOBLOCK bool KCALL isr_unregister_at(isr_vector_t vector, isr_greedy_function_t func, void *arg) THROWS(E_BADALLOC) ASMNAME("isr_unregister_at");
FUNDEF NOBLOCK bool KCALL isr_unregister_any(isr_function_t func) THROWS(E_BADALLOC) ASMNAME("isr_unregister_any");
FUNDEF NOBLOCK bool KCALL isr_unregister_any(isr_greedy_function_t func) THROWS(E_BADALLOC) ASMNAME("isr_unregister_any");
FUNDEF NOBLOCK bool KCALL isr_unregister_any_at(isr_vector_t vector, isr_function_t func) THROWS(E_BADALLOC) ASMNAME("isr_unregister_any_at");
FUNDEF NOBLOCK bool KCALL isr_unregister_any_at(isr_vector_t vector, isr_greedy_function_t func) THROWS(E_BADALLOC) ASMNAME("isr_unregister_any_at");
}
#else /* __cplusplus && !__NO_ASMNAME */
FUNDEF NOBLOCK bool KCALL isr_unregister(void *func, void *arg) THROWS(E_BADALLOC);
FUNDEF NOBLOCK bool KCALL isr_unregister_at(isr_vector_t vector, void *func, void *arg) THROWS(E_BADALLOC);
FUNDEF NOBLOCK bool KCALL isr_unregister_any(void *func) THROWS(E_BADALLOC);
FUNDEF NOBLOCK bool KCALL isr_unregister_any_at(isr_vector_t vector, void *func) THROWS(E_BADALLOC);
#endif /* !__cplusplus || __NO_ASMNAME */

struct isr_vector_handler {
	isr_function_t        ivh_fun; /* [1..1][const] Handler function. */
	void                 *ivh_arg; /* [?..?][const] Handler argument. */
	REF struct driver    *ivh_drv; /* [1..1][const] Driver associated with the greedy handler. */
	/* The following 2  statistics are  used for automatic  optimization to  always try  to
	 * handle incoming interrupts first with the  handler with the best hit-to-miss  ratio.
	 * To deal with the risk of overflows, either of these statistics overflowing is lazily
	 * handled by dividing both stats by 2.
	 * WARNING: These numbers may not be 100% correct. - Don't rely on them for the purpose of an application state */
	WEAK size_t           ivh_hit; /* Number of times that this handler was a hit */
	WEAK size_t           ivh_mis; /* Number of times that this handler was a miss */
};


struct isr_vector_state {
	WEAK refcnt_t                                      ivs_refcnt;     /* Reference counter. */
	size_t                                             ivs_heapsize;   /* [const] Allocated heap size. */
	isr_greedy_function_t                              ivs_greedy_fun; /* [valid_if(ivs_greedy_drv != NULL)][1..1][const] Greedy vector handler. */
	void                                              *ivs_greedy_arg; /* [valid_if(ivs_greedy_drv != NULL)][?..?][const] Greedy vector handler argument. */
	REF struct driver                                 *ivs_greedy_drv; /* [0..1][const] Driver associated with the greedy handler. */
	WEAK size_t                                        ivs_greedy_cnt; /* Number of times that the greedy handler was called.
	                                                                    * WARNING: This number may not be 100% correct. - Don't rely on it for the purpose of an application state */
	WEAK size_t                                        ivs_unhandled;  /* Number of unhandled interrupts that occurred on this vector.
	                                                                    * WARNING: This number may not be 100% correct. - Don't rely on it for the purpose of an application state */
	size_t                                             ivs_handc;      /* [const] Number of handlers. */
	COMPILER_FLEXIBLE_ARRAY(struct isr_vector_handler, ivs_handv);     /* [ivs_handc] Vector of handlers. */
};

FUNDEF NOBLOCK void NOTHROW(KCALL isr_vector_state_destroy)(struct isr_vector_state *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct isr_vector_state, ivs_refcnt, isr_vector_state_destroy)

/* Return the usage descriptor for the given ISR vector. */
FUNDEF NOBLOCK ATTR_RETNONNULL REF struct isr_vector_state *
NOTHROW(KCALL isr_usage_of)(isr_vector_t vector);

/* Trigger the given ISR vector, returning true if any handler returned
 * true, or if a greedy handler was defined. Otherwise, return `false'. */
FUNDEF NOBLOCK bool NOTHROW(KCALL isr_vector_trigger)(isr_vector_t vector);



/* Register  a  handle-based   ISR  handler,   either  by   automatically
 * selecting an appropriate vector, or by specifying the required vector.
 * WARNING: The caller is responsible to ensure that any given func+arg
 *          combination will only be registered once.
 * These functions are quite similar to those above, however ISR
 * callback invocation is improved such that:
 *   - `*func' is invoked with a temporary reference to the  associated
 *     object, and in the event of the associated object already having
 *     been destroyed (i.e. having its reference counter set to 0), the
 *     callback will not be destroyed.
 *   - Unregistering ISR callbacks can be done non-blocking-ly, and the
 *     exposed `hisr_unregister[_at]()' functions should be called from
 *     the destructor of `ob_pointer'
 * As such, these functions should be used to register interrupt handlers
 * on  a per-object  basis, while the  functions above should  be used to
 * register interrupt handlers on a per-driver basis.
 * @param: ob_pointer: Handle data pointer.
 * @param: ob_type:    Handle type (one of `HT_*')
 * @throws: E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS: The given, or all vectors are already in use,
 *                                                     or the  given  vector  cannot  be  allocated. */
FUNDEF isr_vector_t KCALL hisr_register(isr_function_t func, void *ob_pointer, uintptr_half_t ob_type) THROWS(E_BADALLOC);
FUNDEF isr_vector_t KCALL hisr_register_at(isr_vector_t vector, isr_function_t func, void *ob_pointer, uintptr_half_t ob_type) THROWS(E_BADALLOC);
FUNDEF isr_vector_t KCALL hisr_register_greedy(isr_greedy_function_t func, void *ob_pointer, uintptr_half_t ob_type) THROWS(E_BADALLOC, E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS);
FUNDEF isr_vector_t KCALL hisr_register_greedy_at(isr_vector_t vector, isr_greedy_function_t func, void *ob_pointer, uintptr_half_t ob_type) THROWS(E_BADALLOC, E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS);

#if defined(__cplusplus) && !defined(__NO_ASMNAME)
#define __PRIVATE_FORWARD_DECLARE_HANDLE_TYPES(HT, T) T;
HANDLE_FOREACH_CUSTOMTYPE(__PRIVATE_FORWARD_DECLARE_HANDLE_TYPES)
#undef __PRIVATE_FORWARD_DECLARE_HANDLE_TYPES
extern "C++" {
FUNDEF NOBLOCK bool NOTHROW(KCALL hisr_unregister)(isr_function_t func, void *ob_pointer, uintptr_half_t ob_type) ASMNAME("hisr_unregister");
FUNDEF NOBLOCK bool NOTHROW(KCALL hisr_unregister)(isr_greedy_function_t func, void *ob_pointer, uintptr_half_t ob_type) ASMNAME("hisr_unregister");
FUNDEF NOBLOCK bool NOTHROW(KCALL hisr_unregister_at)(isr_vector_t vector, isr_function_t func, void *ob_pointer, uintptr_half_t ob_type) ASMNAME("isr_unregister_any");
FUNDEF NOBLOCK bool NOTHROW(KCALL hisr_unregister_at)(isr_vector_t vector, isr_greedy_function_t func, void *ob_pointer, uintptr_half_t ob_type) ASMNAME("isr_unregister_any");

#define DEFINE_HISR_REGISTER_WRAPPER(HT, T)                                                         \
	LOCAL isr_vector_t KCALL hisr_register(isr_function_t func, T *ob_pointer) THROWS(E_BADALLOC) { \
		return hisr_register(func, (void *)ob_pointer, HT);                                         \
	}                                                                                               \
	LOCAL isr_vector_t KCALL                                                                        \
	hisr_register_at(isr_vector_t vector, isr_function_t func, T *ob_pointer) THROWS(E_BADALLOC) {  \
		return hisr_register_at(vector, func, (void *)ob_pointer, HT);                              \
	}                                                                                               \
	LOCAL isr_vector_t KCALL                                                                        \
	hisr_register_greedy(isr_greedy_function_t func, T *ob_pointer)                                 \
			THROWS(E_BADALLOC, E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS) {                         \
		return hisr_register_greedy(func, (void *)ob_pointer, HT);                                  \
	}                                                                                               \
	LOCAL isr_vector_t KCALL                                                                        \
	hisr_register_greedy_at(isr_vector_t vector, isr_greedy_function_t func, T *ob_pointer)         \
			THROWS(E_BADALLOC, E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS) {                         \
		return hisr_register_greedy_at(vector, func, (void *)ob_pointer, HT);                       \
	}                                                                                               \
	LOCAL NOBLOCK bool                                                                              \
	NOTHROW(KCALL hisr_unregister)(isr_function_t func, T *ob_pointer) {                            \
		return hisr_unregister(func, (void *)ob_pointer, HT);                                       \
	}                                                                                               \
	LOCAL NOBLOCK bool                                                                              \
	NOTHROW(KCALL hisr_unregister)(isr_greedy_function_t func, T *ob_pointer) {                     \
		return hisr_unregister(func, (void *)ob_pointer, HT);                                       \
	}                                                                                               \
	LOCAL NOBLOCK bool                                                                              \
	NOTHROW(KCALL hisr_unregister_at)(isr_vector_t vector,                                          \
	                                  isr_function_t func, T *ob_pointer) {                         \
		return hisr_unregister_at(vector, func, (void *)ob_pointer, HT);                            \
	}                                                                                               \
	LOCAL NOBLOCK bool                                                                              \
	NOTHROW(KCALL hisr_unregister_at)(isr_vector_t vector,                                          \
	                                  isr_greedy_function_t func, T *ob_pointer) {                  \
		return hisr_unregister_at(vector, func, (void *)ob_pointer, HT);                            \
	}
HANDLE_FOREACH_CUSTOMTYPE(DEFINE_HISR_REGISTER_WRAPPER)
#undef DEFINE_HISR_REGISTER_WRAPPER
} /* extern "C++" */
#else /* __cplusplus && !__NO_ASMNAME */
FUNDEF NOBLOCK bool NOTHROW(KCALL hisr_unregister)(void *func, void *ob_pointer, uintptr_half_t ob_type);
FUNDEF NOBLOCK bool NOTHROW(KCALL hisr_unregister_at)(isr_vector_t vector, void *func, void *ob_pointer, uintptr_half_t ob_type);
#endif /* !__cplusplus || __NO_ASMNAME */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_ISR_H */
