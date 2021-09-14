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
#ifndef GUARD_LIBC_USER_AIO_C
#define GUARD_LIBC_USER_AIO_C 1

#include "../api.h"
/**/

#include "aio.h"

DECL_BEGIN

/*[[[head:libc_aio_read,hash:CRC-32=0xde6b5ca4]]]*/
/* >> aio_read(3), aio_read64(3)
 * Begin an async `pread(2)' operation:
 * >> pread(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pread(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `read(2)' is called instead (in which case `self->aio_offset' is ignored) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_read)(struct aiocb *self)
/*[[[body:libc_aio_read]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("aio_read(%p)", self); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_aio_read]]]*/

/*[[[head:libc_aio_write,hash:CRC-32=0xc5e8e2b2]]]*/
/* >> aio_write(3), aio_write64(3)
 * Begin an async `pwrite(2)' operation:
 * >> pwrite(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pwrite(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `write(2)' is called instead (in which case `self->aio_offset' is ignored) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_write)(struct aiocb *self)
/*[[[body:libc_aio_write]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("aio_write(%p)", self); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_aio_write]]]*/

/*[[[head:libc_lio_listio,hash:CRC-32=0x709fa4c8]]]*/
/* >> lio_listio(3), lio_listio64(3)
 * Execute/perform  a `list' of  AIO operations, where  each element of `list'
 * describes a read (`elem->aio_lio_opcode == LIO_READ'), write (`LIO_WRITE'),
 * or no-op (`LIO_NOP') operation.
 *
 * Once all operations are in progress, and `mode == LIO_WAIT', wait for all
 * of  them to complete  and return `0' on  success, or `-1'  is any of them
 * failed (individual errors/return values can be queried via `aio_error(3)'
 * and `aio_return(3)' on each of the elements from `list')
 *
 * Alternatively, when `mode == LIO_NOWAIT', AIO is performed asynchronously,
 * and the function returns immediatly once all operations have been started.
 * If this was successful, return `0', or `-1' if doing so failed  (`errno').
 * Also note that on error, all  of the already-started operations will  have
 * been canceled even before this function returns.
 * Additionally, the given `sig' (if non-NULL) will be assigned as a master
 * completion event that is only triggered once _all_ of the AIO operations
 * have completed. Note that in this case, `sig' will/has always be invoked
 * if this function returns `0', even if  any of the AIO operations end  up
 * being canceled (s.a. `aio_cancel(3)') before they could be performed.
 *
 * @param: mode: One of `LIO_WAIT', `LIO_NOWAIT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_lio_listio)(int mode,
                                      struct aiocb *const list[__restrict_arr],
                                      __STDC_INT_AS_SIZE_T nent,
                                      struct sigevent *__restrict sigev)
/*[[[body:libc_lio_listio]]]*/
/*AUTO*/{
	(void)mode;
	(void)list;
	(void)nent;
	(void)sigev;
	CRT_UNIMPLEMENTEDF("lio_listio(%x, %p, %x, %p)", mode, list, nent, sigev); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_lio_listio]]]*/

/*[[[head:libc_aio_error,hash:CRC-32=0x963ee296]]]*/
/* >> aio_error(3), aio_error64(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress (or pending)
 * @return: ECANCELED:   Operation was canceled (s.a. `aio_cancel(3)')
 * @return: * :          The   `errno'  with  which   the  async  operation  failed.
 *                       s.a. `pread(2)', `pwrite(2)', `fsync(2)' and `fdatasync(2)' */
INTERN ATTR_SECTION(".text.crt.utility.aio") WUNUSED NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_aio_error)(struct aiocb const *self)
/*[[[body:libc_aio_error]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("aio_error(%p)", self); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_aio_error]]]*/

/*[[[head:libc_aio_return,hash:CRC-32=0xc4e63bd7]]]*/
/* >> aio_return(3), aio_return64(3)
 * @return: * : Return value of async `pread(2)', `pwrite(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: [errno=EINVAL] `self' is invalid (including the case where `self' is still
 *                             in progress), or  its return value  has already been  read. */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) ssize_t
NOTHROW_NCX(LIBCCALL libc_aio_return)(struct aiocb *self)
/*[[[body:libc_aio_return]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("aio_return(%p)", self); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_aio_return]]]*/

/*[[[head:libc_aio_cancel,hash:CRC-32=0x247db22a]]]*/
/* >> aio_cancel(3), aio_cancel64(3)
 * Cancel  a specific AIO  operation (self != NULL),  or all operations currently
 * operating on a given `fd' (self !=  NULL && fd == self->aio_fildes). For  this
 * purpose,  it is undefined if the numerical value of `fd' is used for searching
 * active operations, or the pointed-to kernel object. As such, it is recommended
 * that you always aio_cancel the same fd as was also used when the AIO operation
 * was initiated.
 * NOTE: When `AIO_CANCELED' is  returned, the completion  event of `self',  as
 *       specified in `self->aio_sigevent' will _NOT_ have been triggered,  and
 *       never  will be triggered. An exception to this is when `lio_listio(3)'
 *       was used to start `self'  via `LIO_NOWAIT' and `sigev != NULL',  which
 *       will still be triggered at some pointer after all remaining operations
 *       of the same AIO set have completed, or were canceled as well. The same
 *       also applies to operations of `fd' when `self == NULL'.
 * @return: AIO_CANCELED:    Operations canceled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 * @return: AIO_ALLDONE:     Operations were already completed before the call was made
 * @return: -1:              Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.utility.aio") int
NOTHROW_NCX(LIBCCALL libc_aio_cancel)(fd_t fd,
                                      struct aiocb *self)
/*[[[body:libc_aio_cancel]]]*/
/*AUTO*/{
	(void)fd;
	(void)self;
	CRT_UNIMPLEMENTEDF("aio_cancel(%" PRIxN(__SIZEOF_FD_T__) ", %p)", fd, self); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_aio_cancel]]]*/

/*[[[head:libc_aio_suspend,hash:CRC-32=0xf4e3c229]]]*/
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_aio_suspend)(struct aiocb const *const list[],
                                       __STDC_INT_AS_SIZE_T nent,
                                       struct timespec const *__restrict timeout)
/*[[[body:libc_aio_suspend]]]*/
{
	(void)list;
	(void)nent;
	(void)timeout;
	CRT_UNIMPLEMENTEDF("aio_suspend(%p, %" PRIuSIZ ", %p)", list, nent, timeout); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_aio_suspend]]]*/

/*[[[head:libc_aio_fsync,hash:CRC-32=0x1f05b6a9]]]*/
/* >> aio_fsync(3), aio_fsync64(3)
 * Begin an async `fsync(2)' operation:
 * >> if (operation == O_SYNC) {
 * >>     fsync(self->aio_fildes);
 * >> } else if (operation == O_DSYNC) {
 * >>     fdatasync(self->aio_fildes);
 * >> }
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * @param: operation: One of `O_SYNC' or `O_DSYNC'
 * @return: 0 : Operation was started successfully
 * @return: -1: [errno=EAGAIN] Insufficient resources  (read:  `ENOMEM',  but  posix
 *                             didn't want to use that errno for whatever reason...)
 * @return: -1: [errno=EINVAL] `operation' was invalid */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_aio_fsync)(oflag_t operation,
                                     struct aiocb *self)
/*[[[body:libc_aio_fsync]]]*/
/*AUTO*/{
	(void)operation;
	(void)self;
	CRT_UNIMPLEMENTEDF("aio_fsync(%" PRIxN(__SIZEOF_OFLAG_T__) ", %p)", operation, self); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_aio_fsync]]]*/

/*[[[head:libc_aio_read64,hash:CRC-32=0xb2f80750]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_read64, libc_aio_read);
#else /* MAGIC:alias */
/* >> aio_read(3), aio_read64(3)
 * Begin an async `pread(2)' operation:
 * >> pread(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pread(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `read(2)' is called instead (in which case `self->aio_offset' is ignored) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_read64)(struct aiocb64 *self)
/*[[[body:libc_aio_read64]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("aio_read64(%p)", self); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_read64]]]*/

/*[[[head:libc_aio_write64,hash:CRC-32=0xbb483c11]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_write64, libc_aio_write);
#else /* MAGIC:alias */
/* >> aio_write(3), aio_write64(3)
 * Begin an async `pwrite(2)' operation:
 * >> pwrite(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pwrite(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `write(2)' is called instead (in which case `self->aio_offset' is ignored) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_write64)(struct aiocb64 *self)
/*[[[body:libc_aio_write64]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("aio_write64(%p)", self); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_write64]]]*/

/*[[[head:libc_lio_listio64,hash:CRC-32=0x14f16859]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_lio_listio64, libc_lio_listio);
#else /* MAGIC:alias */
/* >> lio_listio(3), lio_listio64(3)
 * Execute/perform  a `list' of  AIO operations, where  each element of `list'
 * describes a read (`elem->aio_lio_opcode == LIO_READ'), write (`LIO_WRITE'),
 * or no-op (`LIO_NOP') operation.
 *
 * Once all operations are in progress, and `mode == LIO_WAIT', wait for all
 * of  them to complete  and return `0' on  success, or `-1'  is any of them
 * failed (individual errors/return values can be queried via `aio_error(3)'
 * and `aio_return(3)' on each of the elements from `list')
 *
 * Alternatively, when `mode == LIO_NOWAIT', AIO is performed asynchronously,
 * and the function returns immediatly once all operations have been started.
 * If this was successful, return `0', or `-1' if doing so failed  (`errno').
 * Also note that on error, all  of the already-started operations will  have
 * been canceled even before this function returns.
 * Additionally, the given `sig' (if non-NULL) will be assigned as a master
 * completion event that is only triggered once _all_ of the AIO operations
 * have completed. Note that in this case, `sig' will/has always be invoked
 * if this function returns `0', even if  any of the AIO operations end  up
 * being canceled (s.a. `aio_cancel(3)') before they could be performed.
 *
 * @param: mode: One of `LIO_WAIT', `LIO_NOWAIT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_lio_listio64)(int mode,
                                        struct aiocb64 *const list[__restrict_arr],
                                        __STDC_INT_AS_SIZE_T nent,
                                        struct sigevent *__restrict sig)
/*[[[body:libc_lio_listio64]]]*/
/*AUTO*/{
	(void)mode;
	(void)list;
	(void)nent;
	(void)sig;
	CRT_UNIMPLEMENTEDF("lio_listio64(%x, %p, %x, %p)", mode, list, nent, sig); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_lio_listio64]]]*/

/*[[[head:libc_aio_error64,hash:CRC-32=0xb1705fa]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_error64, libc_aio_error);
#else /* MAGIC:alias */
/* >> aio_error(3), aio_error64(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress (or pending)
 * @return: ECANCELED:   Operation was canceled (s.a. `aio_cancel(3)')
 * @return: * :          The   `errno'  with  which   the  async  operation  failed.
 *                       s.a. `pread(2)', `pwrite(2)', `fsync(2)' and `fdatasync(2)' */
INTERN ATTR_SECTION(".text.crt.utility.aio") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_error64)(struct aiocb64 const *self)
/*[[[body:libc_aio_error64]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("aio_error64(%p)", self); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_error64]]]*/

/*[[[head:libc_aio_return64,hash:CRC-32=0xe0faf6ac]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_return64, libc_aio_return);
#else /* MAGIC:alias */
/* >> aio_return(3), aio_return64(3)
 * @return: * : Return value of async `pread(2)', `pwrite(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: [errno=EINVAL] `self' is invalid (including the case where `self' is still
 *                             in progress), or  its return value  has already been  read. */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) ssize_t
NOTHROW_NCX(LIBCCALL libc_aio_return64)(struct aiocb64 *self)
/*[[[body:libc_aio_return64]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("aio_return64(%p)", self); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_return64]]]*/

/*[[[head:libc_aio_cancel64,hash:CRC-32=0x4696ac61]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_cancel64, libc_aio_cancel);
#else /* MAGIC:alias */
/* >> aio_cancel(3), aio_cancel64(3)
 * Cancel  a specific AIO  operation (self != NULL),  or all operations currently
 * operating on a given `fd' (self !=  NULL && fd == self->aio_fildes). For  this
 * purpose,  it is undefined if the numerical value of `fd' is used for searching
 * active operations, or the pointed-to kernel object. As such, it is recommended
 * that you always aio_cancel the same fd as was also used when the AIO operation
 * was initiated.
 * NOTE: When `AIO_CANCELED' is  returned, the completion  event of `self',  as
 *       specified in `self->aio_sigevent' will _NOT_ have been triggered,  and
 *       never  will be triggered. An exception to this is when `lio_listio(3)'
 *       was used to start `self'  via `LIO_NOWAIT' and `sigev != NULL',  which
 *       will still be triggered at some pointer after all remaining operations
 *       of the same AIO set have completed, or were canceled as well. The same
 *       also applies to operations of `fd' when `self == NULL'.
 * @return: AIO_CANCELED:    Operations canceled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 * @return: AIO_ALLDONE:     Operations were already completed before the call was made
 * @return: -1:              Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.utility.aio") int
NOTHROW_NCX(LIBCCALL libc_aio_cancel64)(fd_t fildes,
                                        struct aiocb64 *self)
/*[[[body:libc_aio_cancel64]]]*/
/*AUTO*/{
	(void)fildes;
	(void)self;
	CRT_UNIMPLEMENTEDF("aio_cancel64(%" PRIxN(__SIZEOF_FD_T__) ", %p)", fildes, self); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_cancel64]]]*/

/*[[[head:libc_aio_suspend64,hash:CRC-32=0x97789d07]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_suspend64, libc_aio_suspend);
#else /* MAGIC:alias */
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_suspend64)(struct aiocb64 const *const list[],
                                         __STDC_INT_AS_SIZE_T nent,
                                         struct timespec const *__restrict timeout)
/*[[[body:libc_aio_suspend64]]]*/
{
	(void)list;
	(void)nent;
	(void)timeout;
	CRT_UNIMPLEMENTEDF("aio_suspend64(%p, %" PRIuSIZ ", %p)", list, nent, timeout); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_suspend64]]]*/

/*[[[head:libc_aio_fsync64,hash:CRC-32=0x6a58ee02]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_fsync64, libc_aio_fsync);
#else /* MAGIC:alias */
/* >> aio_fsync(3), aio_fsync64(3)
 * Begin an async `fsync(2)' operation:
 * >> if (operation == O_SYNC) {
 * >>     fsync(self->aio_fildes);
 * >> } else if (operation == O_DSYNC) {
 * >>     fdatasync(self->aio_fildes);
 * >> }
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * @param: operation: One of `O_SYNC' or `O_DSYNC'
 * @return: 0 : Operation was started successfully
 * @return: -1: [errno=EAGAIN] Insufficient resources  (read:  `ENOMEM',  but  posix
 *                             didn't want to use that errno for whatever reason...)
 * @return: -1: [errno=EINVAL] `operation' was invalid */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_aio_fsync64)(int operation,
                                       struct aiocb64 *self)
/*[[[body:libc_aio_fsync64]]]*/
/*AUTO*/{
	(void)operation;
	(void)self;
	CRT_UNIMPLEMENTEDF("aio_fsync64(%x, %p)", operation, self); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_fsync64]]]*/

/*[[[head:libc_aio_suspendt64,hash:CRC-32=0x58d14f29]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_aio_suspendt64, libc_aio_suspend);
#elif __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_aio_suspendt64, libc_aio_suspend);
#else /* MAGIC:alias */
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_suspendt64)(struct aiocb const *const list[],
                                          __STDC_INT_AS_SIZE_T nent,
                                          struct timespec64 const *__restrict timeout)
/*[[[body:libc_aio_suspendt64]]]*/
{
	(void)list;
	(void)nent;
	(void)timeout;
	CRT_UNIMPLEMENTEDF("aio_suspendt64(%p, %" PRIuSIZ ", %p)", list, nent, timeout); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_suspendt64]]]*/

/*[[[head:libc_aio_suspend64t64,hash:CRC-32=0x975e949]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_aio_suspend64t64, libc_aio_suspend);
#elif __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_suspend64t64, libc_aio_suspendt64);
#elif __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_aio_suspend64t64, libc_aio_suspend64);
#else /* MAGIC:alias */
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_suspend64t64)(struct aiocb64 const *const list[],
                                            __STDC_INT_AS_SIZE_T nent,
                                            struct timespec64 const *__restrict timeout)
/*[[[body:libc_aio_suspend64t64]]]*/
{
	(void)list;
	(void)nent;
	(void)timeout;
	CRT_UNIMPLEMENTEDF("aio_suspend64t64(%p, %" PRIuSIZ ", %p)", list, nent, timeout); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_suspend64t64]]]*/

/*[[[head:libc_aio_init,hash:CRC-32=0xa55f7c91]]]*/
/* >> aio_init(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_aio_init)(struct aioinit const *init)
/*[[[body:libc_aio_init]]]*/
/*AUTO*/{
	(void)init;
	CRT_UNIMPLEMENTEDF("aio_init(%p)", init); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_aio_init]]]*/

/*[[[start:exports,hash:CRC-32=0x91b3c220]]]*/
DEFINE_PUBLIC_ALIAS(aio_read, libc_aio_read);
DEFINE_PUBLIC_ALIAS(aio_write, libc_aio_write);
DEFINE_PUBLIC_ALIAS(aio_fsync, libc_aio_fsync);
DEFINE_PUBLIC_ALIAS(lio_listio, libc_lio_listio);
DEFINE_PUBLIC_ALIAS(aio_error, libc_aio_error);
DEFINE_PUBLIC_ALIAS(aio_return, libc_aio_return);
DEFINE_PUBLIC_ALIAS(aio_cancel, libc_aio_cancel);
DEFINE_PUBLIC_ALIAS(aio_suspend, libc_aio_suspend);
DEFINE_PUBLIC_ALIAS(aio_read64, libc_aio_read64);
DEFINE_PUBLIC_ALIAS(aio_write64, libc_aio_write64);
DEFINE_PUBLIC_ALIAS(aio_fsync64, libc_aio_fsync64);
DEFINE_PUBLIC_ALIAS(lio_listio64, libc_lio_listio64);
DEFINE_PUBLIC_ALIAS(aio_error64, libc_aio_error64);
DEFINE_PUBLIC_ALIAS(aio_return64, libc_aio_return64);
DEFINE_PUBLIC_ALIAS(aio_cancel64, libc_aio_cancel64);
DEFINE_PUBLIC_ALIAS(aio_suspend64, libc_aio_suspend64);
DEFINE_PUBLIC_ALIAS(aio_suspendt64, libc_aio_suspendt64);
DEFINE_PUBLIC_ALIAS(aio_suspend64t64, libc_aio_suspend64t64);
DEFINE_PUBLIC_ALIAS(aio_init, libc_aio_init);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_AIO_C */
