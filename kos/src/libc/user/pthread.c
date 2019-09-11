/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_PTHREAD_C
#define GUARD_LIBC_USER_PTHREAD_C 1

#include "../api.h"
#include "pthread.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:pthread_create,hash:0x2c792730]]]*/
/* Create a new thread, starting with execution of START-ROUTINE
 * getting passed ARG. Creation attributed come from ATTR. The new
 * handle is stored in *NEWTHREAD */
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_create") int
NOTHROW_NCX(LIBCCALL libc_pthread_create)(pthread_t *__restrict newthread,
                                          pthread_attr_t const *__restrict attr,
                                          __pthread_start_routine_t __start_routine,
                                          void *__restrict __arg)
/*[[[body:pthread_create]]]*/
{
	CRT_UNIMPLEMENTED("pthread_create"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_create]]]*/

/*[[[head:pthread_exit,hash:0xae89fc53]]]*/
/* Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
INTERN ATTR_NORETURN
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_exit") void
(LIBCCALL libc_pthread_exit)(void *retval)
/*[[[body:pthread_exit]]]*/
{
	CRT_UNIMPLEMENTED("pthread_exit"); /* TODO */
	libc_seterrno(ENOSYS);
	for (;;) {
	}
}
/*[[[end:pthread_exit]]]*/

/*[[[head:pthread_join,hash:0x181b1110]]]*/
/* Make calling thread wait for termination of the thread THREAD. The
 * exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
 * is not NULL */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_join") int
NOTHROW_RPC(LIBCCALL libc_pthread_join)(pthread_t pthread,
                                        void **thread_return)
/*[[[body:pthread_join]]]*/
{
	CRT_UNIMPLEMENTED("pthread_join"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_join]]]*/

/*[[[head:pthread_tryjoin_np,hash:0x7c5cc3a9]]]*/
/* Check whether thread THREAD has terminated. If yes return the status of
 * the thread in *THREAD_RETURN, if THREAD_RETURN is not NULL */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_tryjoin_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_tryjoin_np)(pthread_t pthread,
                                              void **thread_return)
/*[[[body:pthread_tryjoin_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_tryjoin_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_tryjoin_np]]]*/

/*[[[head:pthread_timedjoin_np,hash:0xf4f91e07]]]*/
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL. */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_timedjoin_np") int
NOTHROW_RPC(LIBCCALL libc_pthread_timedjoin_np)(pthread_t pthread,
                                                void **thread_return,
                                                struct timespec const *abstime)
/*[[[body:pthread_timedjoin_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_timedjoin_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_timedjoin_np]]]*/

/*[[[head:pthread_detach,hash:0x5b425455]]]*/
/* Indicate that the thread THREAD is never to be joined with PTHREAD_JOIN.
 * The resources of THREAD will therefore be freed immediately when it
 * terminates, instead of waiting for another thread to perform PTHREAD_JOIN
 * on it */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_detach") int
NOTHROW_NCX(LIBCCALL libc_pthread_detach)(pthread_t pthread)
/*[[[body:pthread_detach]]]*/
{
	CRT_UNIMPLEMENTED("pthread_detach"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_detach]]]*/

/*[[[head:pthread_self,hash:0xb0782c9b]]]*/
/* Obtain the identifier of the current thread */
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_self") pthread_t
NOTHROW_NCX(LIBCCALL libc_pthread_self)(void)
/*[[[body:pthread_self]]]*/
{
	CRT_UNIMPLEMENTED("pthread_self"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:pthread_self]]]*/

/*[[[head:pthread_attr_init,hash:0x25a8bb4c]]]*/
/* Initialize thread attribute *ATTR with default attributes
 * (detachstate is PTHREAD_JOINABLE, scheduling policy is SCHED_OTHER, no user-provided stack) */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_init") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_init)(pthread_attr_t *attr)
/*[[[body:pthread_attr_init]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_init]]]*/

/*[[[head:pthread_attr_destroy,hash:0x4d1c7f98]]]*/
/* Destroy thread attribute *ATTR */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_destroy") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_destroy)(pthread_attr_t *attr)
/*[[[body:pthread_attr_destroy]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_destroy]]]*/

/*[[[head:pthread_attr_getdetachstate,hash:0x89dce99b]]]*/
/* Get detach state attribute */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_getdetachstate") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getdetachstate)(pthread_attr_t const *attr,
                                                       int *detachstate)
/*[[[body:pthread_attr_getdetachstate]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_getdetachstate"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_getdetachstate]]]*/

/*[[[head:pthread_attr_setdetachstate,hash:0x54836e6d]]]*/
/* Set detach state attribute */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_setdetachstate") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setdetachstate)(pthread_attr_t *attr,
                                                       int detachstate)
/*[[[body:pthread_attr_setdetachstate]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_setdetachstate"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_setdetachstate]]]*/

/*[[[head:pthread_attr_getguardsize,hash:0x14fcebe5]]]*/
/* Get the size of the guard area created for stack overflow protection */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_getguardsize") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getguardsize)(pthread_attr_t const *attr,
                                                     size_t *guardsize)
/*[[[body:pthread_attr_getguardsize]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_getguardsize"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_getguardsize]]]*/

/*[[[head:pthread_attr_setguardsize,hash:0xb48685bc]]]*/
/* Set the size of the guard area created for stack overflow protection */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_setguardsize") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setguardsize)(pthread_attr_t *attr,
                                                     size_t guardsize)
/*[[[body:pthread_attr_setguardsize]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_setguardsize"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_setguardsize]]]*/

/*[[[head:pthread_attr_getschedparam,hash:0x3aa92248]]]*/
/* Return in *PARAM the scheduling parameters of *ATTR */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_getschedparam") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getschedparam)(pthread_attr_t const *__restrict attr,
                                                      struct sched_param *__restrict param)
/*[[[body:pthread_attr_getschedparam]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_getschedparam"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_getschedparam]]]*/

/*[[[head:pthread_attr_setschedparam,hash:0xa676b962]]]*/
/* Set scheduling parameters (priority, etc) in *ATTR according to PARAM */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_setschedparam") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setschedparam)(pthread_attr_t *__restrict attr,
                                                      struct sched_param const *__restrict param)
/*[[[body:pthread_attr_setschedparam]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_setschedparam"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_setschedparam]]]*/

/*[[[head:pthread_attr_getschedpolicy,hash:0x52c782d6]]]*/
/* Return in *POLICY the scheduling policy of *ATTR */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_getschedpolicy") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getschedpolicy)(pthread_attr_t const *__restrict attr,
                                                       int *__restrict policy)
/*[[[body:pthread_attr_getschedpolicy]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_getschedpolicy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_getschedpolicy]]]*/

/*[[[head:pthread_attr_setschedpolicy,hash:0x223e0274]]]*/
/* Set scheduling policy in *ATTR according to POLICY */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_setschedpolicy") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setschedpolicy)(pthread_attr_t *attr,
                                                       int policy)
/*[[[body:pthread_attr_setschedpolicy]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_setschedpolicy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_setschedpolicy]]]*/

/*[[[head:pthread_attr_getinheritsched,hash:0xd66f6554]]]*/
/* Return in *INHERIT the scheduling inheritance mode of *ATTR */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_getinheritsched") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getinheritsched)(pthread_attr_t const *__restrict attr,
                                                        int *__restrict inherit)
/*[[[body:pthread_attr_getinheritsched]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_getinheritsched"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_getinheritsched]]]*/

/*[[[head:pthread_attr_setinheritsched,hash:0x93dbf6a8]]]*/
/* Set scheduling inheritance mode in *ATTR according to INHERIT */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_setinheritsched") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setinheritsched)(pthread_attr_t *attr,
                                                        int inherit)
/*[[[body:pthread_attr_setinheritsched]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_setinheritsched"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_setinheritsched]]]*/

/*[[[head:pthread_attr_getscope,hash:0x68635b53]]]*/
/* Return in *SCOPE the scheduling contention scope of *ATTR */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_getscope") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getscope)(pthread_attr_t const *__restrict attr,
                                                 int *__restrict scope)
/*[[[body:pthread_attr_getscope]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_getscope"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_getscope]]]*/

/*[[[head:pthread_attr_setscope,hash:0xb1fc8720]]]*/
/* Set scheduling contention scope in *ATTR according to SCOPE */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_setscope") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setscope)(pthread_attr_t *attr,
                                                 int scope)
/*[[[body:pthread_attr_setscope]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_setscope"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_setscope]]]*/

/*[[[head:pthread_attr_getstackaddr,hash:0x185ffffb]]]*/
/* Return the previously set address for the stack */
INTERN ATTR_DEPRECATED_ NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_getstackaddr") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstackaddr)(pthread_attr_t const *__restrict attr,
                                                     void **__restrict stackaddr)
/*[[[body:pthread_attr_getstackaddr]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_getstackaddr"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_getstackaddr]]]*/

/*[[[head:pthread_attr_setstackaddr,hash:0xf99279c0]]]*/
/* Set the starting address of the stack of the thread to be created.
 * Depending on whether the stack grows up or down the value must either
 * be higher or lower than all the address in the memory block. The
 * minimal size of the block must be PTHREAD_STACK_MIN */
INTERN ATTR_DEPRECATED_ NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_setstackaddr") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setstackaddr)(pthread_attr_t *attr,
                                                     void *stackaddr)
/*[[[body:pthread_attr_setstackaddr]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_setstackaddr"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_setstackaddr]]]*/

/*[[[head:pthread_attr_getstacksize,hash:0x61e42f8c]]]*/
/* Return the currently used minimal stack size */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_getstacksize") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstacksize)(pthread_attr_t const *__restrict attr,
                                                     size_t *__restrict stacksize)
/*[[[body:pthread_attr_getstacksize]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_getstacksize"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_getstacksize]]]*/

/*[[[head:pthread_attr_setstacksize,hash:0x4aec6366]]]*/
/* Add information about the minimum stack size needed for the thread
 * to be started. This size must never be less than PTHREAD_STACK_MIN
 * and must also not exceed the system limits */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_setstacksize") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setstacksize)(pthread_attr_t *attr,
                                                     size_t stacksize)
/*[[[body:pthread_attr_setstacksize]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_setstacksize"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_setstacksize]]]*/

/*[[[head:pthread_attr_getstack,hash:0xf64dcf07]]]*/
/* Return the previously set address for the stack */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_getstack") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstack)(pthread_attr_t const *__restrict attr,
                                                 void **__restrict stackaddr,
                                                 size_t *__restrict stacksize)
/*[[[body:pthread_attr_getstack]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_getstack"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_getstack]]]*/

/*[[[head:pthread_attr_setstack,hash:0x223ad05c]]]*/
/* The following two interfaces are intended to replace the last two. They
 * require setting the address as well as the size since only setting the
 * address will make the implementation on some architectures impossible */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_setstack") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setstack)(pthread_attr_t *attr,
                                                 void *stackaddr,
                                                 size_t stacksize)
/*[[[body:pthread_attr_setstack]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_setstack"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_setstack]]]*/

/*[[[head:pthread_attr_setaffinity_np,hash:0xcc0b393f]]]*/
/* Thread created with attribute ATTR will be limited to run only on
 * the processors represented in CPUSET */
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_setaffinity_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setaffinity_np)(pthread_attr_t *attr,
                                                       size_t cpusetsize,
                                                       cpu_set_t const *cpuset)
/*[[[body:pthread_attr_setaffinity_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_setaffinity_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_setaffinity_np]]]*/

/*[[[head:pthread_attr_getaffinity_np,hash:0x9230c115]]]*/
/* Get bit set in CPUSET representing the processors threads created with ATTR can run on */
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_attr_getaffinity_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getaffinity_np)(pthread_attr_t const *attr,
                                                       size_t cpusetsize,
                                                       cpu_set_t *cpuset)
/*[[[body:pthread_attr_getaffinity_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_attr_getaffinity_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_attr_getaffinity_np]]]*/

/*[[[head:pthread_getattr_default_np,hash:0x72e45968]]]*/
/* Get the default attributes used by pthread_create in this process */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_getattr_default_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_getattr_default_np)(pthread_attr_t *attr)
/*[[[body:pthread_getattr_default_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_getattr_default_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_getattr_default_np]]]*/

/*[[[head:pthread_setattr_default_np,hash:0x182f89df]]]*/
/* Set the default attributes to be used by pthread_create in this process */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_setattr_default_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_setattr_default_np)(pthread_attr_t const *attr)
/*[[[body:pthread_setattr_default_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_setattr_default_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_setattr_default_np]]]*/

/*[[[head:pthread_getattr_np,hash:0xb6c78488]]]*/
/* Initialize thread attribute *ATTR with attributes corresponding to the
 * already running thread THREAD. It shall be called on uninitialized ATTR
 * and destroyed with pthread_attr_destroy when no longer needed */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_getattr_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_getattr_np)(pthread_t pthread,
                                              pthread_attr_t *attr)
/*[[[body:pthread_getattr_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_getattr_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_getattr_np]]]*/

/*[[[head:pthread_setschedparam,hash:0xe6d4a5c9]]]*/
/* Set the scheduling parameters for TARGET_THREAD according to POLICY and *PARAM */
INTERN NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_setschedparam") int
NOTHROW_NCX(LIBCCALL libc_pthread_setschedparam)(pthread_t target_thread,
                                                 int policy,
                                                 struct sched_param const *param)
/*[[[body:pthread_setschedparam]]]*/
{
	CRT_UNIMPLEMENTED("pthread_setschedparam"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_setschedparam]]]*/

/*[[[head:pthread_getschedparam,hash:0xb5f81358]]]*/
/* Return in *POLICY and *PARAM the scheduling parameters for TARGET_THREAD */
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_getschedparam") int
NOTHROW_NCX(LIBCCALL libc_pthread_getschedparam)(pthread_t target_thread,
                                                 int *__restrict policy,
                                                 struct sched_param *__restrict param)
/*[[[body:pthread_getschedparam]]]*/
{
	CRT_UNIMPLEMENTED("pthread_getschedparam"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_getschedparam]]]*/

/*[[[head:pthread_setschedprio,hash:0x51685241]]]*/
/* Set the scheduling priority for TARGET_THREAD */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_setschedprio") int
NOTHROW_NCX(LIBCCALL libc_pthread_setschedprio)(pthread_t target_thread,
                                                int prio)
/*[[[body:pthread_setschedprio]]]*/
{
	CRT_UNIMPLEMENTED("pthread_setschedprio"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_setschedprio]]]*/

/*[[[head:pthread_getname_np,hash:0xd6b15969]]]*/
/* Get thread name visible in the kernel and its interfaces */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_getname_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_getname_np)(pthread_t target_thread,
                                              char *buf,
                                              size_t buflen)
/*[[[body:pthread_getname_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_getname_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_getname_np]]]*/

/*[[[head:pthread_setname_np,hash:0xc1746b8]]]*/
/* Set thread name visible in the kernel and its interfaces */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_setname_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_setname_np)(pthread_t target_thread,
                                              const char *name)
/*[[[body:pthread_setname_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_setname_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_setname_np]]]*/

/*[[[head:pthread_getconcurrency,hash:0xa4101949]]]*/
/* Determine level of concurrency */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_getconcurrency") int
NOTHROW_NCX(LIBCCALL libc_pthread_getconcurrency)(void)
/*[[[body:pthread_getconcurrency]]]*/
{
	CRT_UNIMPLEMENTED("pthread_getconcurrency"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_getconcurrency]]]*/

/*[[[head:pthread_setconcurrency,hash:0x1115c695]]]*/
/* Set new concurrency level to LEVEL */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_setconcurrency") int
NOTHROW_NCX(LIBCCALL libc_pthread_setconcurrency)(int level)
/*[[[body:pthread_setconcurrency]]]*/
{
	CRT_UNIMPLEMENTED("pthread_setconcurrency"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_setconcurrency]]]*/

/*[[[head:pthread_yield,hash:0x4f7d39c0]]]*/
/* Yield the processor to another thread or process.
 * This function is similar to the POSIX `sched_yield' function but
 * might be differently implemented in the case of a m-on-n thread
 * implementation */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_yield") int
NOTHROW_NCX(LIBCCALL libc_pthread_yield)(void)
/*[[[body:pthread_yield]]]*/
{
	CRT_UNIMPLEMENTED("pthread_yield"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_yield]]]*/

/*[[[head:pthread_setaffinity_np,hash:0xf99573c4]]]*/
/* Limit specified thread THREAD to run only on the processors represented in CPUSET */
INTERN NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_setaffinity_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_setaffinity_np)(pthread_t pthread,
                                                  size_t cpusetsize,
                                                  cpu_set_t const *cpuset)
/*[[[body:pthread_setaffinity_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_setaffinity_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_setaffinity_np]]]*/

/*[[[head:pthread_getaffinity_np,hash:0xa7d929c3]]]*/
/* Get bit set in CPUSET representing the processors THREAD can run on */
INTERN NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_getaffinity_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_getaffinity_np)(pthread_t pthread,
                                                  size_t cpusetsize,
                                                  cpu_set_t *cpuset)
/*[[[body:pthread_getaffinity_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_getaffinity_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_getaffinity_np]]]*/

/*[[[head:pthread_once,hash:0x3d398b2c]]]*/
/* Guarantee that the initialization function INIT_ROUTINE will be called
 * only once, even if pthread_once is executed several times with the
 * same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
 * extern variable initialized to PTHREAD_ONCE_INIT. */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_once") int
(LIBCCALL libc_pthread_once)(pthread_once_t *once_control,
                             __pthread_once_routine_t init_routine)
		__THROWS(...)
/*[[[body:pthread_once]]]*/
{
	CRT_UNIMPLEMENTED("pthread_once"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_once]]]*/

/*[[[head:pthread_setcancelstate,hash:0xf5f31589]]]*/
/* Set cancelability state of current thread to STATE,
 * returning old state in *OLDSTATE if OLDSTATE is not NULL */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_setcancelstate") int
NOTHROW_NCX(LIBCCALL libc_pthread_setcancelstate)(int state,
                                                  int *oldstate)
/*[[[body:pthread_setcancelstate]]]*/
{
	CRT_UNIMPLEMENTED("pthread_setcancelstate"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_setcancelstate]]]*/

/*[[[head:pthread_setcanceltype,hash:0x26cb3af0]]]*/
/* Set cancellation state of current thread to TYPE, returning the old
 * type in *OLDTYPE if OLDTYPE is not NULL */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_setcanceltype") int
NOTHROW_NCX(LIBCCALL libc_pthread_setcanceltype)(int type,
                                                 int *oldtype)
/*[[[body:pthread_setcanceltype]]]*/
{
	CRT_UNIMPLEMENTED("pthread_setcanceltype"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_setcanceltype]]]*/

/*[[[head:pthread_cancel,hash:0x862bfae3]]]*/
/* Cancel THREAD immediately or at the next possibility */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_cancel") int
NOTHROW_NCX(LIBCCALL libc_pthread_cancel)(pthread_t pthread)
/*[[[body:pthread_cancel]]]*/
{
	CRT_UNIMPLEMENTED("pthread_cancel"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_cancel]]]*/

/*[[[head:pthread_testcancel,hash:0xe029ced6]]]*/
/* Test for pending cancellation for the current thread and terminate
 * the thread as per pthread_exit(PTHREAD_CANCELED) if it has been
 * cancelled */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_testcancel") void
NOTHROW_RPC(LIBCCALL libc_pthread_testcancel)(void)
/*[[[body:pthread_testcancel]]]*/
{
	CRT_UNIMPLEMENTED("pthread_testcancel"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:pthread_testcancel]]]*/

/*[[[head:__pthread_unregister_cancel,hash:0xc9f7f793]]]*/
INTERN __cleanup_fct_attribute NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.__pthread_unregister_cancel") void
NOTHROW_NCX(LIBCCALL libc___pthread_unregister_cancel)(__pthread_unwind_buf_t *buf)
/*[[[body:__pthread_unregister_cancel]]]*/
{
	CRT_UNIMPLEMENTED("__pthread_unregister_cancel"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:__pthread_unregister_cancel]]]*/

/*[[[head:__pthread_unregister_cancel_restore,hash:0x5100d702]]]*/
INTERN __cleanup_fct_attribute NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.__pthread_unregister_cancel_restore") void
NOTHROW_NCX(LIBCCALL libc___pthread_unregister_cancel_restore)(__pthread_unwind_buf_t *buf)
/*[[[body:__pthread_unregister_cancel_restore]]]*/
{
	CRT_UNIMPLEMENTED("__pthread_unregister_cancel_restore"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:__pthread_unregister_cancel_restore]]]*/

/*[[[head:__pthread_unwind_next,hash:0xac4b429a]]]*/
/* Internal interface to initiate cleanup */
INTERN ATTR_WEAK __cleanup_fct_attribute ATTR_NORETURN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.__pthread_unwind_next") void
NOTHROW_NCX(LIBCCALL libc___pthread_unwind_next)(__pthread_unwind_buf_t *buf)
/*[[[body:__pthread_unwind_next]]]*/
{
	CRT_UNIMPLEMENTED("__pthread_unwind_next"); /* TODO */
	libc_seterrno(ENOSYS);
	for (;;) {
	}
}
/*[[[end:__pthread_unwind_next]]]*/


/*[[[head:pthread_mutex_init,hash:0x7172f919]]]*/
/* Initialize a mutex */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutex_init") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_init)(pthread_mutex_t *mutex,
                                              pthread_mutexattr_t const *mutexattr)
/*[[[body:pthread_mutex_init]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutex_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutex_init]]]*/

/*[[[head:pthread_mutex_destroy,hash:0x4fd538be]]]*/
/* Destroy a mutex */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutex_destroy") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_destroy)(pthread_mutex_t *mutex)
/*[[[body:pthread_mutex_destroy]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutex_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutex_destroy]]]*/

/*[[[head:pthread_mutex_trylock,hash:0x4a38cd92]]]*/
/* Try locking a mutex */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutex_trylock") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_trylock)(pthread_mutex_t *mutex)
/*[[[body:pthread_mutex_trylock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutex_trylock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutex_trylock]]]*/

/*[[[head:pthread_mutex_lock,hash:0x4a70e70f]]]*/
/* Lock a mutex */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutex_lock") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_lock)(pthread_mutex_t *mutex)
/*[[[body:pthread_mutex_lock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutex_lock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutex_lock]]]*/

/*[[[head:pthread_mutex_timedlock,hash:0x1f1c87ad]]]*/
/* Wait until lock becomes available, or specified time passes */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutex_timedlock") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_timedlock)(pthread_mutex_t *__restrict mutex,
                                                   struct timespec const *__restrict abstime)
/*[[[body:pthread_mutex_timedlock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutex_timedlock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutex_timedlock]]]*/

/*[[[head:pthread_mutex_unlock,hash:0x21cf3325]]]*/
/* Unlock a mutex */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutex_unlock") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_unlock)(pthread_mutex_t *mutex)
/*[[[body:pthread_mutex_unlock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutex_unlock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutex_unlock]]]*/

/*[[[head:pthread_mutex_getprioceiling,hash:0xfff2a821]]]*/
/* Get the priority ceiling of MUTEX */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutex_getprioceiling") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_getprioceiling)(pthread_mutex_t const *__restrict mutex,
                                                        int *__restrict prioceiling)
/*[[[body:pthread_mutex_getprioceiling]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutex_getprioceiling"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutex_getprioceiling]]]*/

/*[[[head:pthread_mutex_setprioceiling,hash:0xc6043f1]]]*/
/* Set the priority ceiling of MUTEX to PRIOCEILING, return old
 * priority ceiling value in *OLD_CEILING */
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutex_setprioceiling") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_setprioceiling)(pthread_mutex_t *__restrict mutex,
                                                        int prioceiling,
                                                        int *__restrict old_ceiling)
/*[[[body:pthread_mutex_setprioceiling]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutex_setprioceiling"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutex_setprioceiling]]]*/

/*[[[head:pthread_mutex_consistent,hash:0x4fd3aedc]]]*/
/* Declare the state protected by MUTEX as consistent */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutex_consistent") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_consistent)(pthread_mutex_t *mutex)
/*[[[body:pthread_mutex_consistent]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutex_consistent"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutex_consistent]]]*/

/*[[[head:pthread_mutex_consistent_np,hash:0x9557adc8]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutex_consistent_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_consistent_np)(pthread_mutex_t *mutex)
/*[[[body:pthread_mutex_consistent_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutex_consistent_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutex_consistent_np]]]*/

/*[[[head:pthread_mutexattr_init,hash:0x754a0]]]*/
/* Initialize mutex attribute object ATTR with default attributes (kind is PTHREAD_MUTEX_TIMED_NP) */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_init") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_init)(pthread_mutexattr_t *attr)
/*[[[body:pthread_mutexattr_init]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_init]]]*/

/*[[[head:pthread_mutexattr_destroy,hash:0x82a12936]]]*/
/* Destroy mutex attribute object ATTR */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_destroy") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_destroy)(pthread_mutexattr_t *attr)
/*[[[body:pthread_mutexattr_destroy]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_destroy]]]*/

/*[[[head:pthread_mutexattr_getpshared,hash:0x9c473119]]]*/
/* Get the process-shared flag of the mutex attribute ATTR */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_getpshared") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getpshared)(pthread_mutexattr_t const *__restrict attr,
                                                        int *__restrict pshared)
/*[[[body:pthread_mutexattr_getpshared]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_getpshared"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_getpshared]]]*/

/*[[[head:pthread_mutexattr_setpshared,hash:0xd02804ea]]]*/
/* Set the process-shared flag of the mutex attribute ATTR */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_setpshared") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setpshared)(pthread_mutexattr_t *attr,
                                                        int pshared)
/*[[[body:pthread_mutexattr_setpshared]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_setpshared"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_setpshared]]]*/

/*[[[head:pthread_mutexattr_gettype,hash:0xe0e0b169]]]*/
/* Return in *KIND the mutex kind attribute in *ATTR */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_gettype") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_gettype)(pthread_mutexattr_t const *__restrict attr,
                                                     int *__restrict kind)
/*[[[body:pthread_mutexattr_gettype]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_gettype"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_gettype]]]*/

/*[[[head:pthread_mutexattr_settype,hash:0x844fd22]]]*/
/* Set the mutex kind attribute in *ATTR to KIND (either PTHREAD_MUTEX_NORMAL,
 * PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK, or PTHREAD_MUTEX_DEFAULT) */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_settype") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_settype)(pthread_mutexattr_t *attr,
                                                     int kind)
/*[[[body:pthread_mutexattr_settype]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_settype"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_settype]]]*/

/*[[[head:pthread_mutexattr_getprotocol,hash:0x7abe7033]]]*/
/* Return in *PROTOCOL the mutex protocol attribute in *ATTR */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_getprotocol") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getprotocol)(pthread_mutexattr_t const *__restrict attr,
                                                         int *__restrict protocol)
/*[[[body:pthread_mutexattr_getprotocol]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_getprotocol"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_getprotocol]]]*/

/*[[[head:pthread_mutexattr_setprotocol,hash:0xf99434a6]]]*/
/* Set the mutex protocol attribute in *ATTR to PROTOCOL (either
 * PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, or PTHREAD_PRIO_PROTECT) */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_setprotocol") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setprotocol)(pthread_mutexattr_t *attr,
                                                         int protocol)
/*[[[body:pthread_mutexattr_setprotocol]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_setprotocol"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_setprotocol]]]*/

/*[[[head:pthread_mutexattr_getprioceiling,hash:0x8900a669]]]*/
/* Return in *PRIOCEILING the mutex prioceiling attribute in *ATTR */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_getprioceiling") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getprioceiling)(pthread_mutexattr_t const *__restrict attr,
                                                            int *__restrict prioceiling)
/*[[[body:pthread_mutexattr_getprioceiling]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_getprioceiling"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_getprioceiling]]]*/

/*[[[head:pthread_mutexattr_setprioceiling,hash:0xc0bfe7bc]]]*/
/* Set the mutex prioceiling attribute in *ATTR to PRIOCEILING */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_setprioceiling") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setprioceiling)(pthread_mutexattr_t *attr,
                                                            int prioceiling)
/*[[[body:pthread_mutexattr_setprioceiling]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_setprioceiling"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_setprioceiling]]]*/

/*[[[head:pthread_mutexattr_getrobust,hash:0x611b3bf9]]]*/
/* Get the robustness flag of the mutex attribute ATTR */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_getrobust") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getrobust)(pthread_mutexattr_t const *attr,
                                                       int *robustness)
/*[[[body:pthread_mutexattr_getrobust]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_getrobust"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_getrobust]]]*/

/*[[[head:pthread_mutexattr_getrobust_np,hash:0xa6828bec]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_getrobust_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getrobust_np)(pthread_mutexattr_t const *attr,
                                                          int *robustness)
/*[[[body:pthread_mutexattr_getrobust_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_getrobust_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_getrobust_np]]]*/

/*[[[head:pthread_mutexattr_setrobust,hash:0x2df54ae7]]]*/
/* Set the robustness flag of the mutex attribute ATTR */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_setrobust") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setrobust)(pthread_mutexattr_t *attr,
                                                       int robustness)
/*[[[body:pthread_mutexattr_setrobust]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_setrobust"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_setrobust]]]*/

/*[[[head:pthread_mutexattr_setrobust_np,hash:0xe20e5969]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_mutexattr_setrobust_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setrobust_np)(pthread_mutexattr_t *attr,
                                                          int robustness)
/*[[[body:pthread_mutexattr_setrobust_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_mutexattr_setrobust_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_mutexattr_setrobust_np]]]*/

/*[[[head:pthread_rwlock_init,hash:0x241ace82]]]*/
/* Initialize read-write lock RWLOCK using attributes ATTR,
 * or use the default values if later is NULL */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlock_init") int
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_init)(pthread_rwlock_t *__restrict rwlock,
                                               pthread_rwlockattr_t const *__restrict attr)
/*[[[body:pthread_rwlock_init]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlock_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlock_init]]]*/

/*[[[head:pthread_rwlock_destroy,hash:0x42651f59]]]*/
/* Destroy read-write lock RWLOCK */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlock_destroy") int
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_destroy)(pthread_rwlock_t *rwlock)
/*[[[body:pthread_rwlock_destroy]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlock_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlock_destroy]]]*/

/*[[[head:pthread_rwlock_rdlock,hash:0x2e641057]]]*/
/* Acquire read lock for RWLOCK */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlock_rdlock") int
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_rdlock)(pthread_rwlock_t *rwlock)
/*[[[body:pthread_rwlock_rdlock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlock_rdlock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlock_rdlock]]]*/

/*[[[head:pthread_rwlock_tryrdlock,hash:0xf1177727]]]*/
/* Try to acquire read lock for RWLOCK */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlock_tryrdlock") int
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_tryrdlock)(pthread_rwlock_t *rwlock)
/*[[[body:pthread_rwlock_tryrdlock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlock_tryrdlock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlock_tryrdlock]]]*/

/*[[[head:pthread_rwlock_timedrdlock,hash:0x663dc8ac]]]*/
/* Try to acquire read lock for RWLOCK or return after specfied time */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlock_timedrdlock") int
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedrdlock)(pthread_rwlock_t *__restrict rwlock,
                                                      struct timespec const *__restrict abstime)
/*[[[body:pthread_rwlock_timedrdlock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlock_timedrdlock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlock_timedrdlock]]]*/

/*[[[head:pthread_rwlock_wrlock,hash:0xff34c810]]]*/
/* Acquire write lock for RWLOCK */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlock_wrlock") int
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_wrlock)(pthread_rwlock_t *rwlock)
/*[[[body:pthread_rwlock_wrlock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlock_wrlock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlock_wrlock]]]*/

/*[[[head:pthread_rwlock_trywrlock,hash:0xf172f542]]]*/
/* Try to acquire write lock for RWLOCK */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlock_trywrlock") int
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_trywrlock)(pthread_rwlock_t *rwlock)
/*[[[body:pthread_rwlock_trywrlock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlock_trywrlock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlock_trywrlock]]]*/

/*[[[head:pthread_rwlock_timedwrlock,hash:0xfdad7f7d]]]*/
/* Try to acquire write lock for RWLOCK or return after specfied time */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlock_timedwrlock") int
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedwrlock)(pthread_rwlock_t *__restrict rwlock,
                                                      struct timespec const *__restrict abstime)
/*[[[body:pthread_rwlock_timedwrlock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlock_timedwrlock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlock_timedwrlock]]]*/

/*[[[head:pthread_rwlock_unlock,hash:0xd4ad2ce8]]]*/
/* Unlock RWLOCK */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlock_unlock") int
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_unlock)(pthread_rwlock_t *rwlock)
/*[[[body:pthread_rwlock_unlock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlock_unlock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlock_unlock]]]*/

/*[[[head:pthread_rwlockattr_init,hash:0x2fe619a]]]*/
/* Initialize attribute object ATTR with default values */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlockattr_init") int
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_init)(pthread_rwlockattr_t *attr)
/*[[[body:pthread_rwlockattr_init]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlockattr_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlockattr_init]]]*/

/*[[[head:pthread_rwlockattr_destroy,hash:0x9164f4dc]]]*/
/* Destroy attribute object ATTR */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlockattr_destroy") int
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_destroy)(pthread_rwlockattr_t *attr)
/*[[[body:pthread_rwlockattr_destroy]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlockattr_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlockattr_destroy]]]*/

/*[[[head:pthread_rwlockattr_getpshared,hash:0xb119a939]]]*/
/* Return current setting of process-shared attribute of ATTR in PSHARED */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlockattr_getpshared") int
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_getpshared)(pthread_rwlockattr_t const *__restrict attr,
                                                         int *__restrict pshared)
/*[[[body:pthread_rwlockattr_getpshared]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlockattr_getpshared"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlockattr_getpshared]]]*/

/*[[[head:pthread_rwlockattr_setpshared,hash:0x42897da2]]]*/
/* Set process-shared attribute of ATTR to PSHARED */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlockattr_setpshared") int
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_setpshared)(pthread_rwlockattr_t *attr,
                                                         int pshared)
/*[[[body:pthread_rwlockattr_setpshared]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlockattr_setpshared"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlockattr_setpshared]]]*/

/*[[[head:pthread_rwlockattr_getkind_np,hash:0xac68fb51]]]*/
/* Return current setting of reader/writer preference */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlockattr_getkind_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_getkind_np)(pthread_rwlockattr_t const *__restrict attr,
                                                         int *__restrict pref)
/*[[[body:pthread_rwlockattr_getkind_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlockattr_getkind_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlockattr_getkind_np]]]*/

/*[[[head:pthread_rwlockattr_setkind_np,hash:0xd765291c]]]*/
/* Set reader/write preference */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_rwlockattr_setkind_np") int
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_setkind_np)(pthread_rwlockattr_t *attr,
                                                         int pref)
/*[[[body:pthread_rwlockattr_setkind_np]]]*/
{
	CRT_UNIMPLEMENTED("pthread_rwlockattr_setkind_np"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_rwlockattr_setkind_np]]]*/

/*[[[head:pthread_cond_init,hash:0xeb013f90]]]*/
/* Initialize condition variable COND using attributes ATTR, or use
 * the default values if later is NULL */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_cond_init") int
NOTHROW_NCX(LIBCCALL libc_pthread_cond_init)(pthread_cond_t *__restrict cond,
                                             pthread_condattr_t const *__restrict cond_attr)
/*[[[body:pthread_cond_init]]]*/
{
	CRT_UNIMPLEMENTED("pthread_cond_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_cond_init]]]*/

/*[[[head:pthread_cond_destroy,hash:0xc579f868]]]*/
/* Destroy condition variable COND */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_cond_destroy") int
NOTHROW_NCX(LIBCCALL libc_pthread_cond_destroy)(pthread_cond_t *cond)
/*[[[body:pthread_cond_destroy]]]*/
{
	CRT_UNIMPLEMENTED("pthread_cond_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_cond_destroy]]]*/

/*[[[head:pthread_cond_signal,hash:0xb1d22618]]]*/
/* Wake up one thread waiting for condition variable COND */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_cond_signal") int
NOTHROW_NCX(LIBCCALL libc_pthread_cond_signal)(pthread_cond_t *cond)
/*[[[body:pthread_cond_signal]]]*/
{
	CRT_UNIMPLEMENTED("pthread_cond_signal"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_cond_signal]]]*/

/*[[[head:pthread_cond_broadcast,hash:0x7c4ef97c]]]*/
/* Wake up all threads waiting for condition variables COND */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_cond_broadcast") int
NOTHROW_NCX(LIBCCALL libc_pthread_cond_broadcast)(pthread_cond_t *cond)
/*[[[body:pthread_cond_broadcast]]]*/
{
	CRT_UNIMPLEMENTED("pthread_cond_broadcast"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_cond_broadcast]]]*/

/*[[[head:pthread_cond_wait,hash:0x3155eeeb]]]*/
/* Wait for condition variable COND to be signaled or broadcast.
 * MUTEX is assumed to be locked before. */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_cond_wait") int
NOTHROW_RPC(LIBCCALL libc_pthread_cond_wait)(pthread_cond_t *__restrict cond,
                                             pthread_mutex_t *__restrict mutex)
/*[[[body:pthread_cond_wait]]]*/
{
	CRT_UNIMPLEMENTED("pthread_cond_wait"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_cond_wait]]]*/

/*[[[head:pthread_cond_timedwait,hash:0x59876f39]]]*/
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_cond_timedwait") int
NOTHROW_RPC(LIBCCALL libc_pthread_cond_timedwait)(pthread_cond_t *__restrict cond,
                                                  pthread_mutex_t *__restrict mutex,
                                                  struct timespec const *__restrict abstime)
/*[[[body:pthread_cond_timedwait]]]*/
{
	CRT_UNIMPLEMENTED("pthread_cond_timedwait"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_cond_timedwait]]]*/

/*[[[head:pthread_condattr_init,hash:0x31adb5c9]]]*/
/* Initialize condition variable attribute ATTR */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_condattr_init") int
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_init)(pthread_condattr_t *attr)
/*[[[body:pthread_condattr_init]]]*/
{
	CRT_UNIMPLEMENTED("pthread_condattr_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_condattr_init]]]*/

/*[[[head:pthread_condattr_destroy,hash:0xc3fdd11c]]]*/
/* Destroy condition variable attribute ATTR */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_condattr_destroy") int
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_destroy)(pthread_condattr_t *attr)
/*[[[body:pthread_condattr_destroy]]]*/
{
	CRT_UNIMPLEMENTED("pthread_condattr_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_condattr_destroy]]]*/

/*[[[head:pthread_condattr_getpshared,hash:0xcc7de771]]]*/
/* Get the process-shared flag of the condition variable attribute ATTR */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_condattr_getpshared") int
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_getpshared)(pthread_condattr_t const *__restrict attr,
                                                       int *__restrict pshared)
/*[[[body:pthread_condattr_getpshared]]]*/
{
	CRT_UNIMPLEMENTED("pthread_condattr_getpshared"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_condattr_getpshared]]]*/

/*[[[head:pthread_condattr_setpshared,hash:0x1afcd015]]]*/
/* Set the process-shared flag of the condition variable attribute ATTR */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_condattr_setpshared") int
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_setpshared)(pthread_condattr_t *attr,
                                                       int pshared)
/*[[[body:pthread_condattr_setpshared]]]*/
{
	CRT_UNIMPLEMENTED("pthread_condattr_setpshared"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_condattr_setpshared]]]*/

/*[[[head:pthread_condattr_getclock,hash:0xa8a9d780]]]*/
/* Get the clock selected for the condition variable attribute ATTR */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_condattr_getclock") int
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_getclock)(pthread_condattr_t const *__restrict attr,
                                                     clockid_t *__restrict clock_id)
/*[[[body:pthread_condattr_getclock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_condattr_getclock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_condattr_getclock]]]*/

/*[[[head:pthread_condattr_setclock,hash:0x5750f84f]]]*/
/* Set the clock selected for the condition variable attribute ATTR */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_condattr_setclock") int
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_setclock)(pthread_condattr_t *attr,
                                                     clockid_t clock_id)
/*[[[body:pthread_condattr_setclock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_condattr_setclock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_condattr_setclock]]]*/

/*[[[head:pthread_spin_init,hash:0xe06c3852]]]*/
/* Initialize the spinlock LOCK. If PSHARED is nonzero the
 * spinlock can be shared between different processes */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_spin_init") int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_init)(pthread_spinlock_t *lock,
                                             int pshared)
/*[[[body:pthread_spin_init]]]*/
{
	CRT_UNIMPLEMENTED("pthread_spin_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_spin_init]]]*/

/*[[[head:pthread_spin_destroy,hash:0xc458338c]]]*/
/* Destroy the spinlock LOCK */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_spin_destroy") int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_destroy)(pthread_spinlock_t *lock)
/*[[[body:pthread_spin_destroy]]]*/
{
	CRT_UNIMPLEMENTED("pthread_spin_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_spin_destroy]]]*/

/*[[[head:pthread_spin_lock,hash:0x6581e584]]]*/
/* Wait until spinlock LOCK is retrieved */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_spin_lock") int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_lock)(pthread_spinlock_t *lock)
/*[[[body:pthread_spin_lock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_spin_lock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_spin_lock]]]*/

/*[[[head:pthread_spin_trylock,hash:0x74a058b9]]]*/
/* Try to lock spinlock LOCK */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_spin_trylock") int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_trylock)(pthread_spinlock_t *lock)
/*[[[body:pthread_spin_trylock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_spin_trylock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_spin_trylock]]]*/

/*[[[head:pthread_spin_unlock,hash:0xc78957cc]]]*/
/* Release spinlock LOCK */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_spin_unlock") int
NOTHROW_NCX(LIBCCALL libc_pthread_spin_unlock)(pthread_spinlock_t *lock)
/*[[[body:pthread_spin_unlock]]]*/
{
	CRT_UNIMPLEMENTED("pthread_spin_unlock"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_spin_unlock]]]*/

/*[[[head:pthread_barrier_init,hash:0xccf89fee]]]*/
/* Initialize BARRIER with the attributes in ATTR.
 * The barrier is opened when COUNT waiters arrived */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_barrier_init") int
NOTHROW_NCX(LIBCCALL libc_pthread_barrier_init)(pthread_barrier_t *__restrict barrier,
                                                pthread_barrierattr_t const *__restrict attr,
                                                unsigned int count)
/*[[[body:pthread_barrier_init]]]*/
{
	CRT_UNIMPLEMENTED("pthread_barrier_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_barrier_init]]]*/

/*[[[head:pthread_barrier_destroy,hash:0x292d09c2]]]*/
/* Destroy a previously dynamically initialized barrier BARRIER */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_barrier_destroy") int
NOTHROW_NCX(LIBCCALL libc_pthread_barrier_destroy)(pthread_barrier_t *barrier)
/*[[[body:pthread_barrier_destroy]]]*/
{
	CRT_UNIMPLEMENTED("pthread_barrier_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_barrier_destroy]]]*/

/*[[[head:pthread_barrier_wait,hash:0x72d93c0]]]*/
/* Wait on barrier BARRIER */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_barrier_wait") int
NOTHROW_RPC(LIBCCALL libc_pthread_barrier_wait)(pthread_barrier_t *barrier)
/*[[[body:pthread_barrier_wait]]]*/
{
	CRT_UNIMPLEMENTED("pthread_barrier_wait"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_barrier_wait]]]*/

/*[[[head:pthread_barrierattr_init,hash:0x9bebcec1]]]*/
/* Initialize barrier attribute ATTR */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_barrierattr_init") int
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_init)(pthread_barrierattr_t *attr)
/*[[[body:pthread_barrierattr_init]]]*/
{
	CRT_UNIMPLEMENTED("pthread_barrierattr_init"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_barrierattr_init]]]*/

/*[[[head:pthread_barrierattr_destroy,hash:0x264a2c06]]]*/
/* Destroy previously dynamically initialized barrier attribute ATTR */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_barrierattr_destroy") int
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_destroy)(pthread_barrierattr_t *attr)
/*[[[body:pthread_barrierattr_destroy]]]*/
{
	CRT_UNIMPLEMENTED("pthread_barrierattr_destroy"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_barrierattr_destroy]]]*/

/*[[[head:pthread_barrierattr_getpshared,hash:0xd0c63a95]]]*/
/* Get the process-shared flag of the barrier attribute ATTR */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_barrierattr_getpshared") int
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_getpshared)(pthread_barrierattr_t const *__restrict attr,
                                                          int *__restrict pshared)
/*[[[body:pthread_barrierattr_getpshared]]]*/
{
	CRT_UNIMPLEMENTED("pthread_barrierattr_getpshared"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_barrierattr_getpshared]]]*/

/*[[[head:pthread_barrierattr_setpshared,hash:0xadbaa2ef]]]*/
/* Set the process-shared flag of the barrier attribute ATTR */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_barrierattr_setpshared") int
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_setpshared)(pthread_barrierattr_t *attr,
                                                          int pshared)
/*[[[body:pthread_barrierattr_setpshared]]]*/
{
	CRT_UNIMPLEMENTED("pthread_barrierattr_setpshared"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_barrierattr_setpshared]]]*/

/*[[[head:pthread_key_create,hash:0x156e9206]]]*/
/* Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. DESTR_FUNCTION, if non-NULL, is called with the value
 * associated to that key when the key is destroyed.
 * DESTR_FUNCTION is not called if the value associated is NULL when
 * the key is destroyed */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_key_create") int
NOTHROW_NCX(LIBCCALL libc_pthread_key_create)(pthread_key_t *key,
                                              __pthread_destr_function_t destr_function)
/*[[[body:pthread_key_create]]]*/
{
	CRT_UNIMPLEMENTED("pthread_key_create"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_key_create]]]*/

/*[[[head:pthread_key_delete,hash:0xb02ecd2e]]]*/
/* Destroy KEY */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_key_delete") int
NOTHROW_NCX(LIBCCALL libc_pthread_key_delete)(pthread_key_t key)
/*[[[body:pthread_key_delete]]]*/
{
	CRT_UNIMPLEMENTED("pthread_key_delete"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_key_delete]]]*/

/*[[[head:pthread_getspecific,hash:0x8b7c3509]]]*/
/* Return current value of the thread-specific data slot identified by KEY */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_getspecific") void *
NOTHROW_NCX(LIBCCALL libc_pthread_getspecific)(pthread_key_t key)
/*[[[body:pthread_getspecific]]]*/
{
	CRT_UNIMPLEMENTED("pthread_getspecific"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:pthread_getspecific]]]*/

/*[[[head:pthread_setspecific,hash:0x961b2acd]]]*/
/* Store POINTER in the thread-specific data slot identified by KEY */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_setspecific") int
NOTHROW_NCX(LIBCCALL libc_pthread_setspecific)(pthread_key_t key,
                                               void const *pointer)
/*[[[body:pthread_setspecific]]]*/
{
	CRT_UNIMPLEMENTED("pthread_setspecific"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_setspecific]]]*/

/*[[[head:pthread_getcpuclockid,hash:0xc6feb5b]]]*/
/* Get ID of CPU-time clock for thread THREAD_ID */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_getcpuclockid") int
NOTHROW_NCX(LIBCCALL libc_pthread_getcpuclockid)(pthread_t pthread_id,
                                                 clockid_t *clock_id)
/*[[[body:pthread_getcpuclockid]]]*/
{
	CRT_UNIMPLEMENTED("pthread_getcpuclockid"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_getcpuclockid]]]*/

/*[[[head:pthread_atfork,hash:0x4d3e373e]]]*/
/* Install handlers to be called when a new process is created with FORK.
 * The PREPARE handler is called in the parent process just before performing
 * FORK. The PARENT handler is called in the parent process just after FORK.
 * The CHILD handler is called in the child process. Each of the three
 * handlers can be NULL, meaning that no handler needs to be called at that
 * point.
 * PTHREAD_ATFORK can be called several times, in which case the PREPARE
 * handlers are called in LIFO order (last added with PTHREAD_ATFORK,
 * first called before FORK), and the PARENT and CHILD handlers are called
 * in FIFO (first added, first called) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_atfork") int
NOTHROW_NCX(LIBCCALL libc_pthread_atfork)(__pthread_atfork_func_t prepare,
                                          __pthread_atfork_func_t parent,
                                          __pthread_atfork_func_t child)
/*[[[body:pthread_atfork]]]*/
{
	CRT_UNIMPLEMENTED("pthread_atfork"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:pthread_atfork]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x7032d735]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(pthread_create, libc_pthread_create);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_exit, libc_pthread_exit);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_join, libc_pthread_join);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_tryjoin_np, libc_pthread_tryjoin_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_timedjoin_np, libc_pthread_timedjoin_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_detach, libc_pthread_detach);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_self, libc_pthread_self);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_init, libc_pthread_attr_init);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_destroy, libc_pthread_attr_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_getdetachstate, libc_pthread_attr_getdetachstate);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_setdetachstate, libc_pthread_attr_setdetachstate);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_getguardsize, libc_pthread_attr_getguardsize);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_setguardsize, libc_pthread_attr_setguardsize);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_getschedparam, libc_pthread_attr_getschedparam);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_setschedparam, libc_pthread_attr_setschedparam);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_getschedpolicy, libc_pthread_attr_getschedpolicy);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_setschedpolicy, libc_pthread_attr_setschedpolicy);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_getinheritsched, libc_pthread_attr_getinheritsched);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_setinheritsched, libc_pthread_attr_setinheritsched);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_getscope, libc_pthread_attr_getscope);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_setscope, libc_pthread_attr_setscope);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_getstackaddr, libc_pthread_attr_getstackaddr);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_setstackaddr, libc_pthread_attr_setstackaddr);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_getstacksize, libc_pthread_attr_getstacksize);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_setstacksize, libc_pthread_attr_setstacksize);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_getstack, libc_pthread_attr_getstack);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_setstack, libc_pthread_attr_setstack);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_setaffinity_np, libc_pthread_attr_setaffinity_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_attr_getaffinity_np, libc_pthread_attr_getaffinity_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_getattr_default_np, libc_pthread_getattr_default_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_setattr_default_np, libc_pthread_setattr_default_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_getattr_np, libc_pthread_getattr_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_setschedparam, libc_pthread_setschedparam);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_getschedparam, libc_pthread_getschedparam);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_setschedprio, libc_pthread_setschedprio);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_getname_np, libc_pthread_getname_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_setname_np, libc_pthread_setname_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_getconcurrency, libc_pthread_getconcurrency);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_setconcurrency, libc_pthread_setconcurrency);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_yield, libc_pthread_yield);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_setaffinity_np, libc_pthread_setaffinity_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_getaffinity_np, libc_pthread_getaffinity_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_once, libc_pthread_once);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_setcancelstate, libc_pthread_setcancelstate);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_setcanceltype, libc_pthread_setcanceltype);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_cancel, libc_pthread_cancel);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_testcancel, libc_pthread_testcancel);
DEFINE_PUBLIC_WEAK_ALIAS(__pthread_unregister_cancel, libc___pthread_unregister_cancel);
DEFINE_PUBLIC_WEAK_ALIAS(__pthread_unregister_cancel_restore, libc___pthread_unregister_cancel_restore);
DEFINE_PUBLIC_WEAK_ALIAS(__pthread_unwind_next, libc___pthread_unwind_next);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutex_init, libc_pthread_mutex_init);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutex_destroy, libc_pthread_mutex_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutex_trylock, libc_pthread_mutex_trylock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutex_lock, libc_pthread_mutex_lock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutex_timedlock, libc_pthread_mutex_timedlock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutex_unlock, libc_pthread_mutex_unlock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutex_getprioceiling, libc_pthread_mutex_getprioceiling);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutex_setprioceiling, libc_pthread_mutex_setprioceiling);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutex_consistent, libc_pthread_mutex_consistent);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutex_consistent_np, libc_pthread_mutex_consistent_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_init, libc_pthread_mutexattr_init);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_destroy, libc_pthread_mutexattr_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_getpshared, libc_pthread_mutexattr_getpshared);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_setpshared, libc_pthread_mutexattr_setpshared);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_gettype, libc_pthread_mutexattr_gettype);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_settype, libc_pthread_mutexattr_settype);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_getprotocol, libc_pthread_mutexattr_getprotocol);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_setprotocol, libc_pthread_mutexattr_setprotocol);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_getprioceiling, libc_pthread_mutexattr_getprioceiling);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_setprioceiling, libc_pthread_mutexattr_setprioceiling);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_getrobust, libc_pthread_mutexattr_getrobust);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_setrobust, libc_pthread_mutexattr_setrobust);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_getrobust_np, libc_pthread_mutexattr_getrobust_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_mutexattr_setrobust_np, libc_pthread_mutexattr_setrobust_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlock_init, libc_pthread_rwlock_init);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlock_destroy, libc_pthread_rwlock_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlock_rdlock, libc_pthread_rwlock_rdlock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlock_tryrdlock, libc_pthread_rwlock_tryrdlock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlock_timedrdlock, libc_pthread_rwlock_timedrdlock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlock_wrlock, libc_pthread_rwlock_wrlock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlock_trywrlock, libc_pthread_rwlock_trywrlock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlock_timedwrlock, libc_pthread_rwlock_timedwrlock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlock_unlock, libc_pthread_rwlock_unlock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlockattr_init, libc_pthread_rwlockattr_init);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlockattr_destroy, libc_pthread_rwlockattr_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlockattr_getpshared, libc_pthread_rwlockattr_getpshared);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlockattr_setpshared, libc_pthread_rwlockattr_setpshared);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlockattr_getkind_np, libc_pthread_rwlockattr_getkind_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_rwlockattr_setkind_np, libc_pthread_rwlockattr_setkind_np);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_cond_init, libc_pthread_cond_init);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_cond_destroy, libc_pthread_cond_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_cond_signal, libc_pthread_cond_signal);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_cond_broadcast, libc_pthread_cond_broadcast);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_cond_wait, libc_pthread_cond_wait);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_cond_timedwait, libc_pthread_cond_timedwait);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_condattr_init, libc_pthread_condattr_init);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_condattr_destroy, libc_pthread_condattr_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_condattr_getpshared, libc_pthread_condattr_getpshared);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_condattr_setpshared, libc_pthread_condattr_setpshared);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_condattr_getclock, libc_pthread_condattr_getclock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_condattr_setclock, libc_pthread_condattr_setclock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_spin_init, libc_pthread_spin_init);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_spin_destroy, libc_pthread_spin_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_spin_lock, libc_pthread_spin_lock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_spin_trylock, libc_pthread_spin_trylock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_spin_unlock, libc_pthread_spin_unlock);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_barrier_init, libc_pthread_barrier_init);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_barrier_destroy, libc_pthread_barrier_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_barrier_wait, libc_pthread_barrier_wait);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_barrierattr_init, libc_pthread_barrierattr_init);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_barrierattr_destroy, libc_pthread_barrierattr_destroy);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_barrierattr_getpshared, libc_pthread_barrierattr_getpshared);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_barrierattr_setpshared, libc_pthread_barrierattr_setpshared);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_key_create, libc_pthread_key_create);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_key_delete, libc_pthread_key_delete);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_getspecific, libc_pthread_getspecific);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_setspecific, libc_pthread_setspecific);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_getcpuclockid, libc_pthread_getcpuclockid);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_atfork, libc_pthread_atfork);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PTHREAD_C */
