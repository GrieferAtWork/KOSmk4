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

/*[[[head:libc_aio_read,hash:CRC-32=0xa2205a2c]]]*/
/* >> aio_read(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_read)(struct aiocb *aiocbp)
/*[[[body:libc_aio_read]]]*/
/*AUTO*/{
	(void)aiocbp;
	CRT_UNIMPLEMENTEDF("aio_read(%p)", aiocbp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_aio_read]]]*/

/*[[[head:libc_aio_write,hash:CRC-32=0x37e8abb0]]]*/
/* >> aio_write(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_write)(struct aiocb *aiocbp)
/*[[[body:libc_aio_write]]]*/
/*AUTO*/{
	(void)aiocbp;
	CRT_UNIMPLEMENTEDF("aio_write(%p)", aiocbp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_aio_write]]]*/

/*[[[head:libc_lio_listio,hash:CRC-32=0x20e6156f]]]*/
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_lio_listio)(int mode,
                                      struct aiocb *const list[__restrict_arr],
                                      __STDC_INT_AS_SIZE_T nent,
                                      struct sigevent *__restrict sig)
/*[[[body:libc_lio_listio]]]*/
/*AUTO*/{
	(void)mode;
	(void)list;
	(void)nent;
	(void)sig;
	CRT_UNIMPLEMENTEDF("lio_listio(%x, %p, %x, %p)", mode, list, nent, sig); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_lio_listio]]]*/

/*[[[head:libc_aio_error,hash:CRC-32=0xf7f2e502]]]*/
/* >> aio_error(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_error)(struct aiocb const *aiocbp)
/*[[[body:libc_aio_error]]]*/
/*AUTO*/{
	(void)aiocbp;
	CRT_UNIMPLEMENTEDF("aio_error(%p)", aiocbp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_aio_error]]]*/

/*[[[head:libc_aio_return,hash:CRC-32=0x9ee14214]]]*/
/* >> aio_return(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) ssize_t
NOTHROW_NCX(LIBCCALL libc_aio_return)(struct aiocb *aiocbp)
/*[[[body:libc_aio_return]]]*/
/*AUTO*/{
	(void)aiocbp;
	CRT_UNIMPLEMENTEDF("aio_return(%p)", aiocbp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_aio_return]]]*/

/*[[[head:libc_aio_cancel,hash:CRC-32=0xc6cda7f]]]*/
/* >> aio_cancel(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_aio_cancel)(fd_t fildes,
                                      struct aiocb *aiocbp)
/*[[[body:libc_aio_cancel]]]*/
/*AUTO*/{
	(void)fildes;
	(void)aiocbp;
	CRT_UNIMPLEMENTEDF("aio_cancel(%" PRIxN(__SIZEOF_FD_T__) ", %p)", fildes, aiocbp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_aio_cancel]]]*/

/*[[[head:libc_aio_suspend,hash:CRC-32=0xd42ea9e4]]]*/
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3) */
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

/*[[[head:libc_aio_fsync,hash:CRC-32=0xe89759c5]]]*/
/* >> aio_fsync(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_aio_fsync)(int operation,
                                     struct aiocb *aiocbp)
/*[[[body:libc_aio_fsync]]]*/
/*AUTO*/{
	(void)operation;
	(void)aiocbp;
	CRT_UNIMPLEMENTEDF("aio_fsync(%x, %p)", operation, aiocbp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_aio_fsync]]]*/

/*[[[head:libc_aio_read64,hash:CRC-32=0x7729d2a3]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_read64, libc_aio_read);
#else /* MAGIC:alias */
/* >> aio_read(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_read64)(struct aiocb64 *aiocbp)
/*[[[body:libc_aio_read64]]]*/
/*AUTO*/{
	(void)aiocbp;
	CRT_UNIMPLEMENTEDF("aio_read64(%p)", aiocbp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_read64]]]*/

/*[[[head:libc_aio_write64,hash:CRC-32=0xefb73f4c]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_write64, libc_aio_write);
#else /* MAGIC:alias */
/* >> aio_write(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_write64)(struct aiocb64 *aiocbp)
/*[[[body:libc_aio_write64]]]*/
/*AUTO*/{
	(void)aiocbp;
	CRT_UNIMPLEMENTEDF("aio_write64(%p)", aiocbp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_write64]]]*/

/*[[[head:libc_lio_listio64,hash:CRC-32=0x2c76158f]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_lio_listio64, libc_aio_write);
#else /* MAGIC:alias */
/* >> aio_write(3) */
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

/*[[[head:libc_aio_error64,hash:CRC-32=0xd02c4e8]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_error64, libc_aio_error);
#else /* MAGIC:alias */
/* >> aio_error(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_error64)(struct aiocb64 const *aiocbp)
/*[[[body:libc_aio_error64]]]*/
/*AUTO*/{
	(void)aiocbp;
	CRT_UNIMPLEMENTEDF("aio_error64(%p)", aiocbp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_error64]]]*/

/*[[[head:libc_aio_return64,hash:CRC-32=0xda8523c7]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_return64, libc_aio_return);
#else /* MAGIC:alias */
/* >> aio_return(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) ssize_t
NOTHROW_NCX(LIBCCALL libc_aio_return64)(struct aiocb64 *aiocbp)
/*[[[body:libc_aio_return64]]]*/
/*AUTO*/{
	(void)aiocbp;
	CRT_UNIMPLEMENTEDF("aio_return64(%p)", aiocbp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_return64]]]*/

/*[[[head:libc_aio_cancel64,hash:CRC-32=0x2ed9234]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_cancel64, libc_aio_cancel);
#else /* MAGIC:alias */
/* >> aio_cancel(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_aio_cancel64)(fd_t fildes,
                                        struct aiocb64 *aiocbp)
/*[[[body:libc_aio_cancel64]]]*/
/*AUTO*/{
	(void)fildes;
	(void)aiocbp;
	CRT_UNIMPLEMENTEDF("aio_cancel64(%" PRIxN(__SIZEOF_FD_T__) ", %p)", fildes, aiocbp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_cancel64]]]*/

/*[[[head:libc_aio_suspend64,hash:CRC-32=0x2134f30c]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_suspend64, libc_aio_suspend);
#else /* MAGIC:alias */
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3) */
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

/*[[[head:libc_aio_fsync64,hash:CRC-32=0xf8b8d0f5]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_fsync64, libc_aio_fsync);
#else /* MAGIC:alias */
/* >> aio_fsync(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_aio_fsync64)(int operation,
                                       struct aiocb64 *aiocbp)
/*[[[body:libc_aio_fsync64]]]*/
/*AUTO*/{
	(void)operation;
	(void)aiocbp;
	CRT_UNIMPLEMENTEDF("aio_fsync64(%x, %p)", operation, aiocbp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_fsync64]]]*/

/*[[[head:libc_aio_suspendt64,hash:CRC-32=0x3ea5ca0]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_aio_suspendt64, libc_aio_suspend);
#elif __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_aio_suspendt64, libc_aio_suspend);
#else /* MAGIC:alias */
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3) */
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

/*[[[head:libc_aio_suspend64t64,hash:CRC-32=0x50d2b351]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_aio_suspend64t64, libc_aio_suspend);
#elif __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_suspend64t64, libc_aio_suspendt64);
#elif __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_aio_suspend64t64, libc_aio_suspend64);
#else /* MAGIC:alias */
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3) */
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

/*[[[start:exports,hash:CRC-32=0x77876dac]]]*/
DEFINE_PUBLIC_ALIAS(aio_read, libc_aio_read);
DEFINE_PUBLIC_ALIAS(aio_write, libc_aio_write);
DEFINE_PUBLIC_ALIAS(lio_listio, libc_lio_listio);
DEFINE_PUBLIC_ALIAS(aio_error, libc_aio_error);
DEFINE_PUBLIC_ALIAS(aio_return, libc_aio_return);
DEFINE_PUBLIC_ALIAS(aio_cancel, libc_aio_cancel);
DEFINE_PUBLIC_ALIAS(aio_suspend, libc_aio_suspend);
DEFINE_PUBLIC_ALIAS(aio_fsync, libc_aio_fsync);
DEFINE_PUBLIC_ALIAS(aio_read64, libc_aio_read64);
DEFINE_PUBLIC_ALIAS(aio_write64, libc_aio_write64);
DEFINE_PUBLIC_ALIAS(lio_listio64, libc_lio_listio64);
DEFINE_PUBLIC_ALIAS(aio_error64, libc_aio_error64);
DEFINE_PUBLIC_ALIAS(aio_return64, libc_aio_return64);
DEFINE_PUBLIC_ALIAS(aio_cancel64, libc_aio_cancel64);
DEFINE_PUBLIC_ALIAS(aio_suspend64, libc_aio_suspend64);
DEFINE_PUBLIC_ALIAS(aio_fsync64, libc_aio_fsync64);
DEFINE_PUBLIC_ALIAS(aio_suspendt64, libc_aio_suspendt64);
DEFINE_PUBLIC_ALIAS(aio_suspend64t64, libc_aio_suspend64t64);
DEFINE_PUBLIC_ALIAS(aio_init, libc_aio_init);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_AIO_C */
