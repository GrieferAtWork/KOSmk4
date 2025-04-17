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
#ifndef GUARD_LIBSERVICE_CLIENT_C
#define GUARD_LIBSERVICE_CLIENT_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/sched/preemption.h>
#include <hybrid/unaligned.h>

#include <kos/except.h>
#include <kos/malloc.h>
#include <kos/rpc.h>
#include <kos/sys/epoll.h>
#include <kos/sys/mman.h>
#include <kos/sys/socket.h>
#include <kos/syscalls.h>
#include <kos/types.h>
#include <kos/unistd.h>
#include <sys/epoll.h>
#include <sys/poll.h>
#include <sys/un.h>

#include <alloca.h>
#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <malloc.h>
#include <sched.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libservice/client.h>

#include "client.h"
#include "com.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* XXX: Use a different signo for this? */
#define CLIENT_HUP_SIGNO SIGRPC


/* Check if `com_offset' is part of the given `pending_chain' */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(CC com_is_pending)(byte_t const *__restrict shm_base,
                           uintptr_t pending_chain,
                           uintptr_t com_offset) {
	while (pending_chain) {
		struct service_com *com;
		if (pending_chain == com_offset)
			return true;
		com = (struct service_com *)(shm_base + pending_chain);
		pending_chain = com->sc_link;
	}
	return false;
}

/* Shutdown the given service client in response to a remote HUP event. */
PRIVATE NOPREEMPT NONNULL((1)) void
NOTHROW(CC shutdown_client)(struct service *__restrict self) {
	uintptr_t comaddr, pending_chain;
	byte_t *shm_base;
	/* NOTE: Even though we get here asynchronously, this acquire cannot
	 *       block because this lock can  only be required when one  has
	 *       previously  disabled preemption (read:  had their thread be
	 *       masking all signals).
	 * Essentially, this right here is an SMP-lock acquisition, should
	 * you wish  to  use  terminology found  within  the  KOS  kernel. */
	atomic_lock_acquire(&self->s_shm_lock);
	comaddr       = atomic_xch(&self->s_active_list, SERVICE_ACTIVE_LIST_SHUTDOWN);
	pending_chain = atomic_xch(&self->s_shm->ssh_shm->s_commands, 0);
	shm_base      = self->s_shm->ssh_base;
	while (comaddr) {
		uintptr_t next;
		struct service_com *com;
		struct service_comdesc *comdesc;
		com     = (struct service_com *)(shm_base + comaddr);
		comdesc = container_of(com, struct service_comdesc, scd_com);
		next    = comdesc->scd_active_link;
		/* All active commands not part of the pending chain must first be canceled. */
		if (!com_is_pending(shm_base, pending_chain, comaddr)) {
			uintptr_t orig_code;
again_read_orig_code:
			orig_code = atomic_read(&com->sc_code);
			if (orig_code == SERVICE_COM_ST_SUCCESS || SERVICE_COM_ISSPECIAL(orig_code))
				goto next_command; /* Command already completed, so don't shut it down. */
			/* When a generic COM wrapper receives `SERVICE_COM_ST_ECHO',
			 * it  will interpret this  as an E_SERVICE_EXITED exception. */
			if (!atomic_cmpxch(&com->sc_code, orig_code, SERVICE_COM_ST_ECHO))
				goto again_read_orig_code;
		} else {
			/* When a generic COM wrapper receives `SERVICE_COM_ST_ECHO',
			 * it  will interpret this  as an E_SERVICE_EXITED exception.
			 *
			 * Technically,  we could write-back a proper exception here,
			 * but special `SERVICE_COM_ST_ECHO'  handling already  needs
			 * to exist for the case where the command is currently being
			 * executed, so might as well handle this case the same. */
			atomic_write(&com->sc_code, SERVICE_COM_ST_ECHO);
		}
next_command:
		/* Wake-up  anyone listening  for this command.  Always do this  to handle the
		 * race condition where the server dies after writing back the command status,
		 * but before it could broadcast the command's completion futex. */
		sys_lfutex(&com->sc_code, LFUTEX_WAKE, (lfutex_t)-1, NULL, 0);

		comaddr = next;
	}
	atomic_lock_release(&self->s_shm_lock);
}


PRIVATE NONNULL((1, 2)) void PRPC_EXEC_CALLBACK_CC
client_hup_rpc(struct rpc_context *__restrict UNUSED(ctx),
               struct service *__restrict self) {
	/* API contracts guaranty that `self' remains valid until we:
	 *   - ... create an EPOLL monitor (such as an EPOLL RPC) for
	 *     `self->s_fd_srv' within controller `self->s_fd_ephup'.
	 *   - ... or  set `self->s_fd_srv = -1;'  as conforming  of
	 *     having shut down our connection to the remote server. */
	struct pollfd pfd[1];
	errno_t saved_errno;
	sigset_t *oldmask;

	/* Mask all signals. */
	oldmask = setsigmaskfullptr();

	/* We get here asynchronously, so we mustn't clobber `errno' */
	saved_errno = errno;

	/* First of: check if the HUP really happened, or it we only
	 *           got  here in response  to a sporadic interrupt.
	 *           EPOLL  RPCs make no guaranties that they _only_
	 *           fire when monitored events actually happen.
	 * -> They are free to trigger sporadically. */
	pfd[0].fd      = self->s_fd_srv;
	pfd[0].events  = POLLHUP | POLLRDHUP;
	pfd[0].revents = 0;
	if ((poll(pfd, 1, 0) != 0) || (pfd[0].revents != 0)) {
		/* Yes: the HUP really did happen! */
handle_hup:
		close(self->s_fd_srv);
		shutdown_client(self);
		COMPILER_BARRIER();
		self->s_fd_srv = -1; /* Allow `libservice_cancel_hup_rpc()' to stop blocking. */
		COMPILER_BARRIER();
	} else {
		struct epoll_event evt;
		/* It's a sporadic interrupt. -> Try to re-schedule  ourselves,
		 * but if that fails (e.g. due to ENOMEM), then act as though a
		 * HUP happened since we don't have any other means of handling
		 * errors at that point. */
		evt.events   = EPOLLHUP | EPOLLRDHUP;
		evt.data.ptr = self;
		COMPILER_BARRIER();
		if (epoll_rpc_exec(self->s_fd_ephup, self->s_fd_srv, &evt, getpid(),
		                   RPC_SIGNO(CLIENT_HUP_SIGNO) | RPC_SYNCMODE_ASYNC |
		                   RPC_SYSRESTART_RESTART | RPC_DOMAIN_PROCESS,
		                   (prpc_exec_callback_t)&client_hup_rpc) != 0)
			goto handle_hup;
		COMPILER_BARRIER();
		/* With the EPOLL RPC re-scheduled, we're no longer
		 * allowed to access any  of the fields of  `self'! */
	}

	/* Restore saved errno. */
	errno = saved_errno;

	/* Restore previously masked signals. */
	setsigmaskptr(oldmask);
}



/* Exception-enabled version of `libservice_open_nx()'. */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct service *CC
libservice_open(char const *filename) THROWS(E_FSERROR, E_BADALLOC, E_INTERRUPT) {
	struct service *result;
	result = (struct service *)Malloc(sizeof(struct service));
	TRY {
		REF struct service_shm_handle *shm;
		atomic_lock_init(&result->s_shm_lock);
		SLIST_INIT(&result->s_shm_lops);
		shm = service_shm_handle_alloc();
		TRY {
			shm->ssh_refcnt    = 1;
			shm->ssh_tree_lhs  = NULL;
			shm->ssh_tree_rhs  = NULL;
			shm->ssh_tree_red  = 1; /* Singular leaf is always red */
			shm->ssh_service   = result;
			result->s_shm      = shm;
			result->s_shm_tree = shm;
			atomic_rwlock_init(&result->s_textlock);
			SLIST_INIT(&result->s_txranges);
			SLIST_INIT(&result->s_ehranges);
			result->s_funcc = 0;
			result->s_funcv = NULL;

			/* Create the socket which we're going to use to communicate with the server. */
			result->s_fd_srv = Socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, PF_UNIX);
			TRY {
				/* Create the initial SHM fd */
				result->s_fd_shm = MemFdCreate(filename, MFD_CLOEXEC);
				TRY {
					struct service_shm_free *allfree;
					size_t pagesize = getpagesize();
					size_t shm_size = pagesize * 4;
					byte_t *shm_base;
					unsigned int bucket;

					/* This really shouldn't happen, but we mustn't assume anything about `getpagesize()'!
					 * Note that in all likelihood, the compiler will just optimize this away,  especially
					 * when `getpagesize()' expands to a constant integer. */
					if unlikely(shm_size < SERVICE_SHM_ALLOC_MINSIZE)
						shm_size = CEIL_ALIGN(SERVICE_SHM_ALLOC_MINSIZE, pagesize);

					/* Allocate the initial SHM buffer. */
					FTruncate(result->s_fd_shm, shm_size);
					result->s_fd_shm_size = shm_size;

					/* Create the initial SHM mapping. */
					shm_base = (byte_t *)MMap(NULL, shm_size, PROT_READ | PROT_WRITE,
					                          MAP_SHARED | MAP_FILE, result->s_fd_shm,
					                          0);

					/* Fill in the mapping location for the initial SHM region. */
					shm->ssh_base = shm_base;
					shm->ssh_endp = shm_base + shm_size;

					/* Register everything about the SHM control header as free memory. */
					allfree           = (struct service_shm_free *)shm->ssh_shm->s_data;
					allfree->ssf_size = (shm_size - offsetof(struct service_shm, s_data)) |
					                    SERVICE_SHM_FREE_REDBIT; /* Singular leaf is always red */
					allfree->ssf_node.rb_lhs = NULL;
					allfree->ssf_node.rb_rhs = NULL;
					result->s_shm_freetree = allfree;

					bucket = SERVICE_FREE_LIST_INDEX(shm_size);
					allfree->ssf_bysize.le_prev = &result->s_shm_freelist[bucket].lh_first;
					allfree->ssf_bysize.le_next = NULL;
					result->s_shm_freelist[bucket].lh_first = allfree;

					TRY {
						/* Create the EPOLL controller to listen for remote HUP events. */
						result->s_fd_ephup = EPollCreate1(EPOLL_CLOEXEC);
						TRY {
							struct sockaddr_un *sa;
							socklen_t sa_len;
							size_t filename_size;

							/* Connect to a unix domain socket bound to the given file. */
							filename_size  = (strlen(filename) + 1) * sizeof(char);
							sa_len         = offsetof(struct sockaddr_un, sun_path) + filename_size;
							sa             = (struct sockaddr_un *)alloca(sa_len);
							sa->sun_family = AF_UNIX;
							memcpy(sa->sun_path, filename, filename_size);
							Connect(result->s_fd_srv, (struct sockaddr *)sa, sa_len);

							/* Server handshake + acquire SHM handle. */
							{
								struct msghdr msg;
								struct cmsghdr *cmsg;
								char fd_buf[CMSG_SPACE(sizeof(fd_t))];
								struct iovec iov[1];
								bzero(fd_buf, sizeof(fd_buf));
								bzero(&msg, sizeof(msg));
								iov[0].iov_base    = (void *)LIBSERVICE_COM_HANDSHAKE_MESSAGE;
								iov[0].iov_len     = sizeof(LIBSERVICE_COM_HANDSHAKE_MESSAGE);
								msg.msg_iov        = iov;
								msg.msg_iovlen     = lengthof(iov);
								msg.msg_control    = fd_buf;
								msg.msg_controllen = sizeof(fd_buf);
								cmsg               = CMSG_FIRSTHDR(&msg);
								cmsg->cmsg_level   = SOL_SOCKET;
								cmsg->cmsg_type    = SCM_RIGHTS;
								cmsg->cmsg_len     = CMSG_LEN(sizeof(fd_t));
								UNALIGNED_SET((unsigned int *)CMSG_DATA(cmsg),
								              (unsigned int)result->s_fd_shm);
								SendMsg(result->s_fd_srv, &msg, 0);
							}

							/* Schedule an RPC to-be delivered upon HUP */
							{
								struct epoll_event evt;
								evt.events   = EPOLLHUP | EPOLLRDHUP;
								evt.data.ptr = result;
								EPollRpcExec(result->s_fd_ephup, result->s_fd_srv, &evt, getpid(),
								             RPC_SIGNO(CLIENT_HUP_SIGNO) | RPC_SYNCMODE_ASYNC |
								             RPC_SYSRESTART_RESTART | RPC_DOMAIN_PROCESS,
								             (prpc_exec_callback_t)&client_hup_rpc);
								/* FIXME: If  following the creation of an SHM client, the calling process
								 *        does a fork, everything will continue to function normally,  but
								 *        if the server then proceeds to terminate the connection, the HUP
								 *        RPC  will only be delivered to the original process. Children do
								 *        not receive the async notification! */
							}
						} EXCEPT {
							close(result->s_fd_ephup);
							RETHROW();
						}
					} EXCEPT {
						munmap(shm_base, service_shm_handle_getsize(shm));
						RETHROW();
					}
				} EXCEPT {
					close(result->s_fd_shm);
					RETHROW();
				}
			} EXCEPT {
				close(result->s_fd_srv);
				RETHROW();
			}
		} EXCEPT {
			service_shm_handle_free(shm);
			RETHROW();
		}
	} EXCEPT {
		free(result);
		RETHROW();
	}
	return result;
}


/* Client API interface for service. Note that opening the same
 * service more than once will return unique handles each time,
 * and  also establish individual connections to the associated
 * server!
 *
 * @return: * :   Opaque handle for the service. In this case,  the
 *                server is/has/will have created a context for the
 *                current process.
 * @return: NULL: [errno=ENOENT] No function exists with the given name.
 * @return: NULL: [errno=EINTR]  The calling thread was interrupted.
 * @return: NULL: [errno=ENOMEM] Insufficient memory. */
INTERN WUNUSED NONNULL((1)) struct service *
NOTHROW_RPC(CC libservice_open_nx)(char const *filename) {
	NESTED_TRY {
		return libservice_open(filename);
	} EXCEPT {
		except_class_t cls = except_class();
		if (EXCEPTCLASS_ISRTLPRIORITY(cls))
			RETHROW();
		errno = except_as_errno(except_data());
	}
	return NULL;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC destroy_shm_handle)(struct service_shm_handle *__restrict self) {
	struct service_shm_handle *lhs, *rhs;
again:
	lhs = self->ssh_tree_lhs;
	rhs = self->ssh_tree_rhs;

	/* Unmap this SHM mapping. */
	munmap(self->ssh_base, service_shm_handle_getsize(self));

	/* Free the handle descriptor itself. */
	service_shm_handle_free_nopr(self);
	if (lhs) {
		if (rhs)
			destroy_shm_handle(rhs);
		self = lhs;
		goto again;
	}
	if (rhs) {
		self = rhs;
		goto again;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC unmap_text_range_list)(struct service_text_range_slist *__restrict self) {
	struct service_text_range *iter;
	SLIST_FOREACH_SAFE (iter, self, str_link) {
		munmap(iter, iter->str_size);
	}
}

__LIBC void __LIBCCALL __deregister_frame(void *begin);

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC unregister_text_range_list)(struct service_text_range_slist *__restrict self) {
	struct service_text_range *iter;
	SLIST_FOREACH (iter, self, str_link) {
		__deregister_frame(iter->str_data);
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC libservice_cancel_hup_rpc)(struct service *__restrict self) {
	/* Quick check: has the HUP-RPC callback already finished running? */
again:
	if (atomic_read(&self->s_fd_srv) == -1)
		return;
	if (epoll_ctl(self->s_fd_ephup, EPOLL_CTL_DEL, self->s_fd_srv, NULL) != 0) {
		assert(errno == ENOENT);

		/* Special  case: the RPC has already been fired. In this case we have to
		 * make certain the associated callback isn't being executed at this very
		 * moment in some other thread of our process.
		 *
		 * For this purpose, the RPC callback can complete in 1 of 2 ways:
		 *   - Confirmation of HUP by setting `self->s_fd_srv = -1'
		 *   - Sporadic interrupt by re-queuing itself to listen for more HUPs
		 *
		 * We check for the former  by seeing if `self->s_fd_srv == -1'  has
		 * been set, and if it hasn't, we  yield in hopes to get the  thread
		 * currently hosting the RPC to give it a chance to complete, before
		 * starting over with our attempt to delete the RPC. */
		if (atomic_read(&self->s_fd_srv) == -1)
			return;
		sched_yield();
		goto again;
	}
}

/* Close/detach a given service. WARNING: After this function was called,
 * all function pointers  returned by `service_dlsym()'  will point  into
 * the void /  into unmapped memory.  As such, it  is up to  the user  to
 * ensure that no part  of the process  is still using  a service at  the
 * time of it being closed.
 * Services not closed when the calling process exits, or makes a call
 * to one  of the  `exec()' functions  will be  closed  automatically. */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(CC libservice_close)(struct service *__restrict self) {
	size_t i;

	/* Stop  listening for HUPs. This must be done explicitly in case
	 * the EPOLL controller would continue to exist after the close()
	 * below, as would be the case when our process got fork'd  after
	 * a service was created. */
	libservice_cancel_hup_rpc(self);

	/* Close internal file descriptors. */
	if (self->s_fd_srv != -1)
		close(self->s_fd_srv);
	close(self->s_fd_ephup);
	close(self->s_fd_shm);

	/* Destroy all SHM handles. */
	destroy_shm_handle(self->s_shm);

	/* Free Function descriptor */
	for (i = 0; i < self->s_funcc; ++i)
		free(self->s_funcv[i]);
	free(self->s_funcv);

	/* Unregister unwind information */
	unregister_text_range_list(&self->s_ehranges);

	/* Free .text/.eh_frame buffers */
	unmap_text_range_list(&self->s_txranges);
	unmap_text_range_list(&self->s_ehranges);

	/* Free the main control structure. */
	free(self);
}


/* The heart-piece of all of libservice:  lookup a symbol exported by  the
 * given service `self', dynamically generate a callback wrapper function,
 * and finally return the address of said wrapper function which can  then
 * be called like any other C-function (using `CC' calling
 * convention, which is guarantied to be the default calling convention
 * for the current architecture)
 *
 * Note that server functions like those generated by this API are always
 * re-entrance safe, in that they can  be invoked from any context  (esp.
 * including signal handler) and by  any number of threads,  irregardless
 * of how  the server-side  implementation of  the function  looks  like!
 * Generally  speaking, you  can think  of service  functions like system
 * calls,  and as a matter of fact:  the entire idea of service functions
 * stems from the idea of having a user-space API to expose inter-process
 * functions which can be called from an arbitrary context similar to how
 * system calls also can!
 *
 * @return: * :   Pointer to the service wrapper function.
 * @return: NULL: [errno=ENOENT] No function exists with the given name.
 * @return: NULL: [errno=EINTR]  The calling thread was interrupted.
 * @return: NULL: [errno=ENOMEM] Insufficient memory. */
INTERN WUNUSED NONNULL((1, 2)) void *
NOTHROW_RPC(CC libservice_dlsym_nx)(struct service *__restrict self,
                                    char const *__restrict symname) {
	void *result;
	NESTED_TRY {
		result = libservice_dlsym_lookup_or_create(self, symname, SERVICE_FUNCTION_ENTRY_KIND_NORMAL);
	} EXCEPT {
		except_class_t cls = except_class();
		if (EXCEPTCLASS_ISRTLPRIORITY(cls))
			RETHROW();
		errno  = except_as_errno(except_data());
		result = NULL;
	}
	return result;
}

INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) void *CC
libservice_dlsym(struct service *__restrict self, char const *__restrict symname)
		THROWS(E_NO_SUCH_OBJECT, E_BADALLOC, E_INTERRUPT) {
	void *result;
	result = libservice_dlsym_lookup_or_create(self, symname, SERVICE_FUNCTION_ENTRY_KIND_EXCEPT);
	return result;
}






INTERN NOBLOCK NONNULL((1)) void
NOTHROW(CC libservice_buffer_free)(struct service *__restrict self,
                                   void *ptr) {
	struct service_shm_handle *shm;
	preemption_flag_t was;
	if (!ptr)
		return;
	preemption_pushoff(&was);
	shm = libservice_shm_handle_ataddr_nopr(self, ptr);
	assertf(shm, "service_buffer_free(%p): Invalid pointer", ptr);
	libservice_shmbuf_free_nopr(self, shm, ptr);
	preemption_pop(&was);
}


/* Returns the usable size of the given `ptr'. */
INTERN NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(CC libservice_buffer_malloc_usable_size)(struct service *__restrict self,
                                                 void *ptr) {
	(void)self;
	if (!ptr)
		return 0;
	return libservice_shmbuf_get_usable_size(ptr);
}

#ifndef __INTELLISENSE__
DECL_END
#include "client-impl.c.inl"
#define LOCAL_DEFINE_NOEXCEPT
#include "client-impl.c.inl"
DECL_BEGIN
#endif /* !__INTELLISENSE__ */






/* Exports */
DEFINE_PUBLIC_ALIAS(service_open, libservice_open_nx);
DEFINE_PUBLIC_ALIAS(service_close, libservice_close);
DEFINE_PUBLIC_ALIAS(service_dlsym, libservice_dlsym_nx);
DEFINE_PUBLIC_ALIAS(service_buffer_malloc, libservice_buffer_malloc_nx);
DEFINE_PUBLIC_ALIAS(service_buffer_calloc, libservice_buffer_calloc_nx);
DEFINE_PUBLIC_ALIAS(service_buffer_realloc, libservice_buffer_realloc_nx);
DEFINE_PUBLIC_ALIAS(service_buffer_free, libservice_buffer_free);
DEFINE_PUBLIC_ALIAS(service_buffer_malloc_usable_size, libservice_buffer_malloc_usable_size);
DEFINE_PUBLIC_ALIAS(ServiceOpen, libservice_open);
DEFINE_PUBLIC_ALIAS(ServiceDlSym, libservice_dlsym);
DEFINE_PUBLIC_ALIAS(ServiceBufferMalloc, libservice_buffer_malloc);
DEFINE_PUBLIC_ALIAS(ServiceBufferCalloc, libservice_buffer_calloc);
DEFINE_PUBLIC_ALIAS(ServiceBufferRealloc, libservice_buffer_realloc);

DECL_END

#endif /* !GUARD_LIBSERVICE_CLIENT_C */
