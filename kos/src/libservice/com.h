/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBSERVICE_COM_H
#define GUARD_LIBSERVICE_COM_H 1

#include "api.h"


/************************************************************************/
/* COM (Short for COMmunication)                                        */
/************************************************************************/

#include <hybrid/compiler.h>

#include <hybrid/atomic.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-lock.h>

#include <kos/except.h>
#include <kos/futex.h>
#include <kos/kernel/types.h>
#include <kos/refcnt.h>
#include <kos/types.h>

#include <signal.h>
#include <stddef.h>

#include <libc/signal.h>
#include <libservice/bits/com.h>
#include <libservice/types.h>


DECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

/* Helpers for preemption (iow: signal masking) control.
 * These may be used the same way that the kernel macros
 * of the same name are used. */
typedef sigset_t *pflag_t;
#define PREEMPTION_PUSHOFF()           __libc_setsigmaskfullptr()
#define PREEMPTION_POP(was)            __libc_setsigmaskptr(was)
#define atomic_lock_acquire_nopr(self) atomic_lock_acquire(self)

/*
 * Command execution mockup:
 *
 * CLIENT (approximation of functions returned by `service_dlsym()' or `ServiceDlSym()'):
 * >> int some_function_returned_by_service_dlsym(...) {
 * >>     struct service_shm *shm;
 * >>     size_t command_size = ...;                               // Flexible
 * >> #if EXCEPT_ENABLED
 * >>     struct service_com *com = ALLOCATE_COMMAND(&shm, command_size);
 * >>     assert(com != NULL); // Would have thrown E_BADALLOC otherwise
 * >> #else // EXCEPT_ENABLED
 * >>     struct service_com *com = ALLOCATE_COMMAND_NX(&shm, command_size);
 * >>     if (com == NULL) // `errno' was already set to `ENOMEM' by `ALLOCATE_COMMAND_NX'
 * >>         return <dl_error_return>; // As returned by `SERVICE_COM_DLSYM'
 * >> #endif // !EXCEPT_ENABLED
 * >>     TRY {
 * >>         FILL_IN_DATA(com, ...);                              // In buffers + registers
 * >>         uintptr_t cmd = com->sc_code;
 * >>         SLIST_ATOMIC_INSERT(&shm->s_commands, com, sc_link); // Removed server-side
 * >>     } EXCEPT {
 * >>         FREE_COMMAND(shm, com);
 * >>         RETHROW();
 * >>     }
 * >>     lfutex_wake((lfutex_t *)&shm->s_commands, 1); // Wake up server
 * >>
 * >>     // Wait for completion
 * >>     if (lfutex_waitwhile(&com->sc_code, cmd) != 0) {
 * >>         // Interrupted (abort the operation)
 * >>         assert(errno == EINTR);
 * >>         if (ATOMIC_CMPXCH(com->sc_code, cmd, SERVICE_COM_NOOP)) {
 * >>
 * >>             // The following sends an out-of-band command to the server which
 * >>             // will cause the thread servicing our command to receive a sporadic,
 * >>             // synchronous interrupt (s.a. `task_serve()') causing the next/
 * >>             // current blocking operation to be interrupted.
 * >>             INTERRUPT_SERVICE_OPERATION(shm, com);
 * >>
 * >>             // Wait for the `SERVICE_COM_NOOP' to complete.
 * >>             while (lfutex_waitwhile(&com->sc_code, cmd) != 0)
 * >>                 ;
 * >>             FREE_COMMAND(shm, com);
 * >> #if EXCEPT_ENABLED
 * >>             THROW(E_INTERRUPT);
 * >> #else // EXCEPT_ENABLED
 * >>             errno = EINTR;
 * >>             return <dl_error_return>; // As returned by `SERVICE_COM_DLSYM'
 * >> #endif // !EXCEPT_ENABLED
 * >>         }
 * >>     }
 * >>
 * >>     COPY_BACK_OUT_BUFFERS(..., com);                     // Out/in-out buffers
 * >>     if (SERVICE_COM_ISSPECIAL(com->sc_code)) {
 * >>         if (com->sc_code == SERVICE_COM_ST_EXCEPT) {
 * >> #if EXCEPT_ENABLED
 * >>             struct exception_data *ex = error_data();
 * >>             ex->e_code = com->sc_except.e_code;
 * >>             ex->e_args = com->sc_except.e_args;
 * >>             FREE_COMMAND(shm, com);
 * >>             error_throw_current();
 * >> #else // EXCEPT_ENABLED
 * >>             struct exception_data data;
 * >>             data.e_code = com->sc_except.e_code;
 * >>             data.e_args = com->sc_except.e_args;
 * >>             errno = error_as_erno(&data);
 * >>             FREE_COMMAND(shm, com);
 * >>             return <dl_error_return>; // As returned by `SERVICE_COM_DLSYM'
 * >> #endif // !EXCEPT_ENABLED
 * >>         }
 * >>         errno = (errno_t)-(intptr_t)com->sc_code;
 * >>     }
 * >>     int result = com->sc_retval.[...];
 * >>     FREE_COMMAND(shm, com);
 * >>     return result;
 * >> }
 *
 *
 * SERVER:
 *   These threads are  spawned/terminated such  that every  attached
 *   client  always has at  least 1 thread  that is waiting listening
 *   for new commands while other threads may currently be performing
 *   blocking operations.
 * >> void handle_command_thread(void) {
 * >>     for (;;) {
 * >>         struct service_com *com;
 * >>         uintptr_t code;
 * >>         com = CONSUME_PENDING_COMMAND_OR_WAITFOR_ARRIVAL();
 * >>
 * >> again:
 * >>         code = ATOMIC_READ(com->sc_code);
 * >>         if unlikely(SERVICE_COM_ISSPECIAL(code)) {
 * >>             switch (code) {
 * >>             case SERVICE_COM_DLSYM:
 * >>                ...;
 * >>                continue;
 * >>             case SERVICE_COM_NOOP:
 * >>                ...;
 * >>                continue;
 * >>             default:
 * >>                 break;
 * >>             }
 * >>         }
 * >>         // Returns the function for `SERVICE_COM_EXIT' if `code' doesn't exist
 * >>         T (*func)(...) = LOOKUP_FUNCTION(code);
 * >>         TRY {
 * >>             T result = (*func)(DECODE_ARGUMENTS(com->sc_generic.g_data));
 * >>             com->sc_retval = ENCODE_RETURN(result);
 * >>             ATOMIC_WRITE(com->sc_code, (uintptr_t)-(intptr_t)errno);
 * >>         } EXCEPT {
 * >>             if (was_throws(E_INTERRUPT)) // Thrown as the result of `INTERRUPT_SERVICE_OPERATION()'
 * >>                 goto again;
 * >>             struct exception_data *ex = error_data();
 * >>             com->sc_except.e_code = ex->e_code;
 * >>             com->sc_except.e_code = ex->e_args;
 * >>             if (!ATOMIC_CMPXCH(com->sc_code, code, SERVICE_COM_ST_EXCEPT))
 * >>                 goto again;
 * >>         }
 * >>         lfutex_wakeall(&com->sc_code); // Should only be 1, but better be safe and broadcast!
 * >>     }
 * >> }
 *
 * In the future, this design may be altered to make it more efficient
 * by  adding dedicated system calls for the above operations, and the
 * internal futex-related semantics may change. But the basic  concept
 * will always remain the same.
 *
 */

/************************************************************************/
/* All command codes >= this value have special meaning. */
#define _SERVICE_COM_SPECLIMIT ((uintptr_t)-4096)

/* Check if the given `code' has special meaning:
 *  - For the server: invoke a builtin command
 *  - For the client: either a non-zero errno, or an exception must be thrown */
#define SERVICE_COM_ISSPECIAL(code) ((code) >= _SERVICE_COM_SPECLIMIT)
/************************************************************************/



/************************************************************************/
/* Special commands supported by all servers. (send by the client) */
#define SERVICE_COM_EXIT           ((uintptr_t)0)     /* Terminate  the connection. Treated  as an invalid command
                                                       * by the server, who in response, will kill the connection. */
#define SERVICE_COM_DLSYM          ((uintptr_t)-4094) /* Special command: query symbol */
#define SERVICE_COM_NOOP           ((uintptr_t)-4093) /* Special command: do nothing */
/*      SERVICE_COM_               ((uintptr_t)-4092)  * ... */
/************************************************************************/



/************************************************************************/
/* Command status return completion codes (written by the server) */
#define SERVICE_COM_ST_SUCCESS     ((uintptr_t)0)       /* Success */
#define SERVICE_COM_ST_ERRNO(code) ((uintptr_t)-(code)) /* Success,  but with non-zero errno. Note that upon
                                                         * command  completion, the server will simply write
                                                         * back  the negative of  its current `errno' value.
                                                         * An  errno being set doesn't necessarily mean that
                                                         * the command failed, but when non-zero, the client
                                                         * will modify its own errno to match this value. */
#define SERVICE_COM_ST_EXCEPT      ((uintptr_t)-4095)   /* Error by means of a KOS exception that will be
                                                         * re-thrown within  the context  of the  client. */
/************************************************************************/


struct service_com_funinfo {
	uintptr_t                dl_comid;                    /* Command ID to invoke this function */
	union service_com_retval dl_error_return;             /* Return value for errors/exceptions. (usually `-1') */
	uint32_t                 dl_return;                   /* Function return type code (one of `SERVICE_TYPE_*') */
	uint32_t                 dl_params[SERVICE_ARGC_MAX]; /* Function parameter types (ends on EOF or first `SERVICE_TYPE_VOID') */
};

struct service_com_exceptinfo {
	union {
		error_code_t              e_code;     /* Exception code. */
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			error_class_t         e_class;    /* Exception class. */
			error_subclass_t      e_subclass; /* Exception sub-class. */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			error_subclass_t      e_subclass; /* Exception sub-class. */
			error_class_t         e_class;    /* Exception class. */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		};
	};
	union exception_data_pointers e_args;     /* Exception arguments. */
};

struct service_com {
	uintptr_t sc_link; /* Offset to next command. */
	uintptr_t sc_code; /* [in]  Service function ID, or one of `SERVICE_COM_*'
	                    * [out] Operation status code (one of `SERVICE_COM_ST_*') */
	union {
		/* [in] Generic command data payload. The actual layout of this data area
		 *      depends on the type codes of the command being invoked, as well
		 *      as the current architecture. */
		struct {
			COMPILER_FLEXIBLE_ARRAY(byte_t, g_data);
		} sc_generic;

		/* [out] Response to all commands that aren't `SERVICE_COM_ISSPECIAL()' on
		 *       entry. This is the actual return value of the command function. */
		union service_com_retval sc_retval;

		/* [in][SERVICE_COM_DLSYM] NUL-terminated name of the symbol being queried. */
		struct {
			COMPILER_FLEXIBLE_ARRAY(char, dl_name);
		} sc_dlsym;

		/* [out][SERVICE_COM_ST_SUCCESS] Success return value for `SERVICE_COM_DLSYM'.
		 * On error, that  command will return  with `SERVICE_COM_ISSPECIAL()',  which
		 * is  either an errno  value (which should  cause `service_dlsym()' to simply
		 * return `NULL' after applying the errno), or `SERVICE_COM_ST_EXCEPT'  (which
		 * should simply be re-thrown like normal) */
		struct service_com_funinfo sc_dlsym_success;

		/* [out][SERVICE_COM_ST_EXCEPT] Exception data. */
		struct service_com_exceptinfo sc_except;
	};
};


/* Layout of the shared memory region between client/server */
struct service_shm {
	lfutex_t                        s_commands; /* [0..n] List  of pending commands in form of offset
	                                             * to first pending commands (futex-send after added) */
	COMPILER_FLEXIBLE_ARRAY(byte_t, s_data);    /* Buffer area begins here (entirely client-side managed) */
};


struct service;
struct service_shm_handle {
	WEAK refcnt_t       ssh_refcnt;  /* Reference counter. */
	struct service_shm *ssh_shm;     /* [1..ssh_size][owned][const] Shared memory region base  address.
	                                  * This pointer is the result of `mmap(fd: ssh_service->s_fd_shm)' */
	size_t              ssh_size;    /* [lock(READ(ATOMIC), WRITE(ATOMIC && INCREASE_ONLY &&
	                                  *                           ssh_service->s_shmlock)]
	                                  * Shared memory region size may not be reduced */
	uintptr_t           ssh_isred;   /* [lock(ssh_service->s_shmlock)] Non-zero  if  this is  a  red node
	                                  * within the tree of all SHM handles (using the SHM mapping address
	                                  * ranges) */
	struct service     *ssh_service; /* [1..1][const] The associated service. */
};

/* Destroy the given handle.
 * HINT: This function uses lockops to remove `self' from `self->ssh_service->s_shm_tree'! */
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL service_shm_handle_destroy)(struct service_shm_handle *__restrict self);
__DEFINE_REFCOUNT_FUNCTIONS(struct service_shm_handle, ssh_refcnt, service_shm_handle_destroy)

/* Helpers for operating with SHM handle tree functions. */
#define service_shm_handle_getminaddr(self) ((byte_t *)(self)->ssh_shm)
#define service_shm_handle_getmaxaddr(self) ((byte_t *)(self)->ssh_shm + (self)->ssh_size - 1)



struct postlockop {
	SLIST_ENTRY(postlockop) plo_link;
	NOBLOCK void       (CC *plo_func)(struct postlockop *__restrict self);
};
struct lockop;
SLIST_HEAD(lockop_slist, lockop);
struct lockop {
	SLIST_ENTRY(lockop)             lo_link;
	NOBLOCK struct postlockop *(CC *lo_func)(struct lockop *__restrict self);
};

struct service_shm_free;
LIST_HEAD(service_shm_free_list, service_shm_free);
struct service_shm_free {
	RBTREE_NODE(service_shm_free) ssf_node;   /* [lock(:s_shmlock)] Node tree. */
	LIST_ENTRY(service_shm_free)  ssf_bysize; /* [lock(:s_shmlock)] Link entry for free ranges by size. */
	size_t                        ssf_size;   /* [lock(:s_shmlock)] Node size. */
};

/* The minimum size of a free block of SHM memory, and thus also the minimum
 * size for an allocation. We subtract */
#define SERVICE_SHM_ALLOC_MINSIZE sizeof(struct service_shm_free)
#define SERVICE_SHM_ALLOC_ALIGN   sizeof(void *)
#define SERVICE_SHM_ALLOC_EXTRA   sizeof(size_t) /* # of extra bytes that must always be allocated  */


/* Helpers for operating with free range tree functions. */
#define service_shm_free_getminaddr(self) ((byte_t *)(self))
#define service_shm_free_getmaxaddr(self) ((byte_t *)(self) + (self)->ssf_size - 1)


#define SERVICE_FREE_LIST_COUNT  7 /* Number of free list buckets. */
#define _SERVICE_FREE_LIST_SHIFT 7 /* Shift between free range size and bucket index */

/* Given a free node size, return its bucket index. */
#define SERVICE_FREE_LIST_INDEX(size)                                \
	((size) >= (SERVICE_FREE_LIST_COUNT << _SERVICE_FREE_LIST_SHIFT) \
	 ? SERVICE_FREE_LIST_COUNT                                       \
	 : (size) >> _SERVICE_FREE_LIST_SHIFT)

struct service {
	struct atomic_lock                     s_shmlock;      /* Lock for `s_shm' and related members.
	                                                        * NOTE: This lock may only be acquired/released while the calling
	                                                        *       thread is masking _all_ signals! This is required to keep
	                                                        *       the  libservice client API  reentrance-safe, as there are
	                                                        *       cases  where this lock needs to be acquired when a client
	                                                        *       invokes a server function. */
	struct lockop_slist                    s_shmlock_lop;  /* Lock operations for `s_shmlock' */
	REF struct service_shm_handle         *s_shm;          /* [1..1][lock(s_shmlock)]
	                                                        * Current SHM  mapping. (may  be altered  when size  needs to  be
	                                                        * increased, yet doing so isn't possible due to size constraints) */
	LLRBTREE_ROOT(service_shm_handle_list) s_shm_tree;     /* [1..n][owned][lock(s_shmlock)] Tree of all (non-free'd) SHM handles. */
	RBTREE_ROOT(service_shm_free)          s_shm_freetree; /* [lock(s_shmlock)] Tree of free nodes. */
	struct service_shm_free_list           s_shm_freelist[SERVICE_FREE_LIST_COUNT];
	                                                       /* [lock(s_shmlock)] Free list by size. */
	fd_t                                   s_fd_srv;       /* [const][owned] File descriptor for the unix domain socket connected to the server. */
	fd_t                                   s_fd_shm;       /* [const][owned] File descriptor for the shared memory region. */
	/* TODO: Allocation helpers for mapping PROT_EXEC memory (for use by arch-specific wrapper function generators) */
	/* TODO: Allocation helpers for creating `.eh_frame' data (registered via `__register_frame()') (for use by arch-specific wrapper function generators)
	 * NOTE: For  */
	/* TODO: Cache of already-loaded service functions (such that `service_dlsym()'  can
	 *       re-return identical pointers for symbols after they've already been loaded) */
};


/* Reap lock operations of `self->s_shmlock_lop' */
INTDEF NOBLOCK WUNUSED NONNULL((1)) void
NOTHROW(CC _libservice_shmlock_reap)(struct service *__restrict self);
#define libservice_shmlock_mustreap(self) (ATOMIC_READ((self)->s_shmlock_lop.slh_first) != NULL)
#define libservice_shmlock_reap(self)     (void)(!libservice_shmlock_mustreap(self) || (_libservice_shmlock_reap(self), 0))

/* Acquire or release a lock to `self->s_shmlock_lop'
 * Note that these functions must only be called when preemption is disabled,
 * and  that as far  as multi-threading semantics go,  these functions may be
 * considered NOBLOCK, and `s_shmlock' be  considered an SMP-lock! Also  note
 * the  *_nopr suffix, meaning  that all signals must  be masked before these
 * functions  may be called, and that they  must remain masked for the entire
 * duration of the lock being acquired! */
#define libservice_shmlock_tryacquire_nopr(self) atomic_lock_tryacquire(&(self)->s_shmlock)
#define libservice_shmlock_acquire_nopr(self)    atomic_lock_acquire_nopr(&(self)->s_shmlock)
#define libservice_shmlock_release_nopr_f(self)  atomic_lock_release(&(self)->s_shmlock)
#define libservice_shmlock_release_nopr(self)    (atomic_lock_release(&(self)->s_shmlock), libservice_shmlock_reap(self))

/* Helpers to automatically  disable preemption before  acquire,
 * and re-enable after release. Note that the disable here works
 * recursively! */
#define libservice_shmlock_acquire(self)     \
	do {                                     \
		pflag_t _was = PREEMPTION_PUSHOFF(); \
		libservice_shmlock_acquire_nopr(self)
#define libservice_shmlock_release(self)       \
		libservice_shmlock_release_nopr(self); \
		PREEMPTION_POP(_was);                  \
	} __WHILE0

struct service_wrapper_buffer {
	byte_t *swb_txbuf; /* [1..swb_txsiz] Text buffer. */
	size_t  swb_txsiz; /* [>= SERVICE_ARCH_MIN_TXBUF_SIZE] */
	byte_t *swb_ehbuf; /* [1..swb_ehsiz] Text buffer. */
	size_t  swb_ehsiz; /* [>= SERVICE_ARCH_MIN_EHBUF_SIZE] */
};

/* Bits for `libservice_dlsym_create_wrapper::flags' */
#define SERVICE_WRAPPER_FLAG_NORMAL 0x0000 /* Normal flags. */
#define SERVICE_WRAPPER_FLAG_EXCEPT 0x0001 /* The function makes use of exception, rather than
                                            * using `errno'. For differences, see the mock for
                                            * `CLIENT' above. */

/* Return values of `libservice_dlsym_create_wrapper' */
#define LIBSERVICE_DLSYM_CREATE_WRAPPER_SUCCESS 0 /* Success */
#define LIBSERVICE_DLSYM_CREATE_WRAPPER_MORE_TX 1 /* Need more space in .text */
#define LIBSERVICE_DLSYM_CREATE_WRAPPER_MORE_EH 2 /* Need more space in .eh_frame */

/* Implemented  by  arch-specific code:  Assemble  a custom
 * function that invokes a function as specified by `info',
 * returning a pointer to the  base of said function.
 * @param: info:   Information about the function to-be called.
 * @param: result: [in|out] Buffer storage info. Actually used buffer
 *                 sizes are written back to `swb_txsiz' and `swb_ehsiz'
 *                 prior to returning `LIBSERVICE_DLSYM_CREATE_WRAPPER_SUCCESS'
 * @param: flags:  Set of `SERVICE_WRAPPER_FLAG_*'
 * @return: * : One of `LIBSERVICE_DLSYM_CREATE_WRAPPER_*' */
INTDEF WUNUSED NONNULL((1, 2, 3)) unsigned int
NOTHROW(CC libservice_dlsym_create_wrapper)(struct service *__restrict self,
                                            struct service_com_funinfo const *__restrict info,
                                            struct service_wrapper_buffer *__restrict buffers,
                                            unsigned int flags);


/* Lookup a function exported by the service, and if not already loaded, ask the
 * server for information about the function before creating a wrapper for it,
 * which is then cached before also being returned. */
INTDEF WUNUSED NONNULL((1, 2)) void *CC
libservice_dlsym_lookup_or_create(struct service *__restrict self,
                                  char const *__restrict name,
                                  bool uses_exceptions)
		THROWS(E_NO_SUCH_OBJECT, E_BADALLOC, E_INTERRUPT);

/* Ask the server for information about the function `name', and store it in `*info' */
INTDEF WUNUSED NONNULL((1, 2, 3)) void CC
libservice_dlsym_getinfo(struct service *__restrict self, char const *__restrict name,
                         /*out*/ struct service_com_funinfo *__restrict info)
		THROWS(E_NO_SUCH_OBJECT, E_BADALLOC, E_INTERRUPT);




/* Return the SHM base address of the region that contains
 * `addr'. If no  such SHM region  exists, return  `NULL'. */
INTDEF NOBLOCK WUNUSED NONNULL((1)) struct service_shm *
NOTHROW(CC libservice_shm_ataddr)(struct service *__restrict self,
                                  void const *addr);
INTDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) struct service_shm *
NOTHROW(CC libservice_shm_ataddr_nopr)(struct service *__restrict self,
                                       void const *addr);



/* Buffer allocation descriptor. */
struct service_buf {
	void               *sb_ptr; /* [0..1] Allocated pointer. (Until free'd,  holds
	                             * a reference to `HANDLE_OF(sb_shm)->ssh_refcnt') */
	struct service_shm *sb_shm; /* [1..1][valid_if(sb_ptr)] The SHM mapping containing `sb_ptr' */
};
#define libservice_shmbuf_get_base_addr(ptr)     (((size_t *)(ptr)) - 1)
#define libservice_shmbuf_get_total_size(ptr)    (((size_t const *)(ptr))[-1])
#define libservice_shmbuf_set_total_size(ptr, v) (void)(((size_t *)(ptr))[-1] = (v))
#define libservice_shmbuf_get_usable_size(ptr)   (libservice_shmbuf_get_total_size(ptr) - SERVICE_SHM_ALLOC_EXTRA)

/* Allocate SHM memory.
 * @param: num_bytes_with_extra: Lower bound for number of bytes to allocate, plus extra space:
 * >> num_bytes_with_extra = MAX(SERVICE_SHM_ALLOC_MINSIZE,
 * >>                            CEIL_ALIGN(num_bytes, SERVICE_SHM_ALLOC_ALIGN) +
 * >>                            SERVICE_SHM_ALLOC_EXTRA); */
INTDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) struct service_buf
NOTHROW(CC libservice_shmbuf_alloc_nopr_nx)(struct service *__restrict self,
                                            size_t num_bytes_with_extra);
INTDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) struct service_buf CC
libservice_shmbuf_alloc_nopr(struct service *__restrict self,
                             size_t num_bytes_with_extra)
		THROWS(E_BADALLOC);

/* Try to allocate at least  `num_bytes' at `shm', returning  the
 * number of actually allocated bytes  on success, or `0' if  the
 * allocation was impossible because the target address range  is
 * already allocated, or attempting to mmap it failed. Note  that
 * this function doesn't impose any restrictions on minimal alloc
 * size,  and that it _will_ allocate less than the usual minimum
 * of `SERVICE_SHM_ALLOC_MINSIZE' (if possible), meaning that the
 * caller  is responsible to only call this function if they will
 * follow-up by merging the  resulting region with a  neighboring
 * previously-allocated buffer!
 *
 * This function is simply used to implement `service_buffer_realloc'. */
INTDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1, 3)) size_t
NOTHROW(CC libservice_shmbuf_allocat_nopr)(struct service *__restrict self,
                                           struct service_shm *__restrict shm,
                                           void *ptr, size_t num_bytes);

/* Mark the given buffer range as free.
 * @assume(num_bytes >= SERVICE_SHM_ALLOC_MINSIZE);
 * @assume(IS_ALIGNED(ptr, SERVICE_SHM_ALLOC_ALIGN));
 * @assume(shm == libservice_shm_ataddr(self, ptr)); */
INTDEF NOBLOCK NOPREEMPT NONNULL((1, 3)) void
NOTHROW(CC libservice_shmbuf_freeat_nopr)(struct service *__restrict self,
                                          struct service_shm *__restrict shm,
                                          void *ptr, size_t num_bytes);
#define libservice_shmbuf_free_nopr(self, shm, ptr)                     \
	libservice_shmbuf_freeat_nopr(self, shm,                            \
	                              libservice_shmbuf_get_base_addr(ptr), \
	                              libservice_shmbuf_get_total_size(ptr))



DECL_END

#endif /* !GUARD_LIBSERVICE_COM_H */
