/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_PROCESS_C
#define GUARD_LIBC_USER_PROCESS_C 1

#include "../api.h"
/**/

#include <sys/wait.h>

#include <stdlib.h>

#include "../libc/dl.h"
#include "process.h"

DECL_BEGIN

#undef environ
#ifndef __environ_defined
#define __environ_defined 1
extern char **environ;
#endif /* !__environ_defined */
DECLARE_NOREL_GLOBAL_META(char **, environ);
#define environ  GET_NOREL_GLOBAL(environ)


/*[[[start:implementation]]]*/

/*[[[head:_beginthread,hash:CRC-32=0x6b63b655]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.sched.thread._beginthread") uintptr_t
NOTHROW_NCX(LIBCCALL libc__beginthread)(__dos_beginthread_entry_t entry,
                                        u32 stacksz,
                                        void *arg)
/*[[[body:_beginthread]]]*/
{
	(void)entry;
	(void)stacksz;
	(void)arg;
	CRT_UNIMPLEMENTED("_beginthread"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_beginthread]]]*/

/*[[[head:_beginthreadex,hash:CRC-32=0x5be0a6dc]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.sched.thread._beginthreadex") uintptr_t
NOTHROW_NCX(LIBCCALL libc__beginthreadex)(void *sec,
                                          u32 stacksz,
                                          __dos_beginthreadex_entry_t entry,
                                          void *arg,
                                          u32 flags,
                                          u32 *threadaddr)
/*[[[body:_beginthreadex]]]*/
{
	(void)sec;
	(void)stacksz;
	(void)entry;
	(void)arg;
	(void)flags;
	(void)threadaddr;
	CRT_UNIMPLEMENTED("_beginthreadex"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_beginthreadex]]]*/

/*[[[head:_endthread,hash:CRC-32=0xd28aafa8]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.sched.thread._endthread") void
NOTHROW_NCX(LIBCCALL libc__endthread)(void)
/*[[[body:_endthread]]]*/
{
	CRT_UNIMPLEMENTED("_endthread"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:_endthread]]]*/

/*[[[head:_endthreadex,hash:CRC-32=0x1b75da54]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.sched.thread._endthreadex") void
NOTHROW_NCX(LIBCCALL libc__endthreadex)(u32 exitcode)
/*[[[body:_endthreadex]]]*/
{
	(void)exitcode;
	CRT_UNIMPLEMENTED("_endthreadex"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:_endthreadex]]]*/

INTDEF void LIBCCALL libc_run_atexit(int status);

/*[[[head:_cexit,hash:CRC-32=0x980bd302]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.sched.process._cexit") void
(LIBCCALL libc__cexit)(void)
		__THROWS(...)
/*[[[body:_cexit]]]*/
{
	/* Same as `exit()', but without actually exiting... */
	dlauxctrl(NULL, DLAUXCTRL_RUNTLSFINI, NULL, NULL);
	libc_run_atexit(0);
	dlauxctrl(NULL, DLAUXCTRL_RUNFINI, NULL, NULL);
}
/*[[[end:_cexit]]]*/


/*[[[head:_loaddll,hash:CRC-32=0x122b8fc8]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.dlfcn._loaddll") intptr_t
(LIBCCALL libc__loaddll)(char __KOS_FIXED_CONST *file)
		__THROWS(...)
/*[[[body:_loaddll]]]*/
{
	return (intptr_t)(uintptr_t)dlopen(file, RTLD_LOCAL);
}
/*[[[end:_loaddll]]]*/

/*[[[head:_unloaddll,hash:CRC-32=0xe5af5eb5]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.dlfcn._unloaddll") int
(LIBCCALL libc__unloaddll)(intptr_t hnd)
		__THROWS(...)
/*[[[body:_unloaddll]]]*/
{
	return dlclose((void *)(uintptr_t)hnd);
}
/*[[[end:_unloaddll]]]*/

/*[[[head:_getdllprocaddr,hash:CRC-32=0xf0e809eb]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.dlfcn._getdllprocaddr") __procfun
(LIBCCALL libc__getdllprocaddr)(intptr_t hnd,
                                char __KOS_FIXED_CONST *symname,
                                intptr_t ord)
		__THROWS(...)
/*[[[body:_getdllprocaddr]]]*/
{
	(void)ord;
	return (__procfun)dlsym((void *)(uintptr_t)hnd, symname);
}
/*[[[end:_getdllprocaddr]]]*/

/*[[[head:cwait,hash:CRC-32=0xee0a97bc]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.exec.spawn.cwait") pid_t
NOTHROW_RPC(LIBCCALL libc_cwait)(int *tstat,
                                 pid_t pid,
                                 int action)
/*[[[body:cwait]]]*/
{
	/* This one's pretty simple, because it's literally just a waitpid() system call...
	 * (It even returns the same thing, that being the PID of the joined process...) */
	/* NOTE: Apparently, the `action' argument is completely ignored... */
	(void)action;
	return waitpid(pid, tstat, WEXITED);
}
/*[[[end:cwait]]]*/

/*[[[head:spawnv,hash:CRC-32=0x56f6f306]]]*/
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.spawn.spawnv") pid_t
NOTHROW_RPC(LIBCCALL libc_spawnv)(int mode,
                                  char const *__restrict path,
                                  __TARGV)
/*[[[body:spawnv]]]*/
{
	(void)mode;
	(void)path;
	(void)___argv;
	CRT_UNIMPLEMENTED("spawnv"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:spawnv]]]*/

/*[[[head:spawnve,hash:CRC-32=0xcf3d7097]]]*/
INTERN NONNULL((2, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.spawn.spawnve") pid_t
NOTHROW_RPC(LIBCCALL libc_spawnve)(int mode,
                                   char const *__restrict path,
                                   __TARGV,
                                   __TENVP)
/*[[[body:spawnve]]]*/
{
	(void)mode;
	(void)path;
	(void)___argv;
	(void)___envp;
	CRT_UNIMPLEMENTED("spawnve"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:spawnve]]]*/

/*[[[head:spawnvp,hash:CRC-32=0x3a44237]]]*/
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.spawn.spawnvp") pid_t
NOTHROW_RPC(LIBCCALL libc_spawnvp)(int mode,
                                   char const *__restrict file,
                                   __TARGV)
/*[[[body:spawnvp]]]*/
{
	(void)mode;
	(void)file;
	(void)___argv;
	CRT_UNIMPLEMENTED("spawnvp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:spawnvp]]]*/

/*[[[head:spawnvpe,hash:CRC-32=0x9ef0e3b5]]]*/
INTERN NONNULL((2, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.spawn.spawnvpe") pid_t
NOTHROW_RPC(LIBCCALL libc_spawnvpe)(int mode,
                                    char const *__restrict file,
                                    __TARGV,
                                    __TENVP)
/*[[[body:spawnvpe]]]*/
{
	(void)mode;
	(void)file;
	(void)___argv;
	(void)___envp;
	CRT_UNIMPLEMENTED("spawnvpe"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:spawnvpe]]]*/

/*[[[head:spawnl,hash:CRC-32=0x13ab784c]]]*/
INTERN ATTR_SENTINEL NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.spawn.spawnl") pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnl)(int mode,
                                   char const *__restrict path,
                                   char const *args,
                                   ... /*, (char *)NULL*/)
/*[[[body:spawnl]]]*/
{
	(void)mode;
	(void)path;
	(void)args;
	CRT_UNIMPLEMENTED("spawnl"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:spawnl]]]*/

/*[[[head:spawnle,hash:CRC-32=0x7fbe68bf]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.spawn.spawnle") pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnle)(int mode,
                                    char const *__restrict path,
                                    char const *args,
                                    ... /*, (char *)NULL, char **environ*/)
/*[[[body:spawnle]]]*/
{
	(void)mode;
	(void)path;
	(void)args;
	CRT_UNIMPLEMENTED("spawnle"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:spawnle]]]*/

/*[[[head:spawnlp,hash:CRC-32=0x650d3228]]]*/
INTERN ATTR_SENTINEL NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.spawn.spawnlp") pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnlp)(int mode,
                                    char const *__restrict file,
                                    char const *args,
                                    ... /*, (char *)NULL*/)
/*[[[body:spawnlp]]]*/
{
	(void)mode;
	(void)file;
	(void)args;
	CRT_UNIMPLEMENTED("spawnlp"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:spawnlp]]]*/

/*[[[head:spawnlpe,hash:CRC-32=0x6022363f]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.exec.spawn.spawnlpe") pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnlpe)(int mode,
                                     char const *__restrict file,
                                     char const *args,
                                     ... /*, (char *)NULL, char **environ*/)
/*[[[body:spawnlpe]]]*/
{
	(void)mode;
	(void)file;
	(void)args;
	CRT_UNIMPLEMENTED("spawnlpe"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:spawnlpe]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x4a13c599]]]*/
#undef spawnl
#undef _spawnl
#undef spawnlp
#undef _spawnlp
#undef spawnle
#undef _spawnle
#undef spawnlpe
#undef _spawnlpe
DEFINE_PUBLIC_WEAK_ALIAS(_beginthread, libc__beginthread);
DEFINE_PUBLIC_WEAK_ALIAS(_beginthreadex, libc__beginthreadex);
DEFINE_PUBLIC_WEAK_ALIAS(_endthread, libc__endthread);
DEFINE_PUBLIC_WEAK_ALIAS(_endthreadex, libc__endthreadex);
DEFINE_PUBLIC_WEAK_ALIAS(_cexit, libc__cexit);
DEFINE_PUBLIC_WEAK_ALIAS(_loaddll, libc__loaddll);
DEFINE_PUBLIC_WEAK_ALIAS(_unloaddll, libc__unloaddll);
DEFINE_PUBLIC_WEAK_ALIAS(_getdllprocaddr, libc__getdllprocaddr);
DEFINE_PUBLIC_WEAK_ALIAS(cwait, libc_cwait);
DEFINE_PUBLIC_WEAK_ALIAS(_cwait, libc_cwait);
DEFINE_PUBLIC_WEAK_ALIAS(spawnv, libc_spawnv);
DEFINE_PUBLIC_WEAK_ALIAS(_spawnv, libc_spawnv);
DEFINE_PUBLIC_WEAK_ALIAS(spawnvp, libc_spawnvp);
DEFINE_PUBLIC_WEAK_ALIAS(_spawnvp, libc_spawnvp);
DEFINE_PUBLIC_WEAK_ALIAS(spawnve, libc_spawnve);
DEFINE_PUBLIC_WEAK_ALIAS(_spawnve, libc_spawnve);
DEFINE_PUBLIC_WEAK_ALIAS(spawnvpe, libc_spawnvpe);
DEFINE_PUBLIC_WEAK_ALIAS(_spawnvpe, libc_spawnvpe);
DEFINE_PUBLIC_WEAK_ALIAS(spawnl, libc_spawnl);
DEFINE_PUBLIC_WEAK_ALIAS(_spawnl, libc_spawnl);
DEFINE_PUBLIC_WEAK_ALIAS(spawnlp, libc_spawnlp);
DEFINE_PUBLIC_WEAK_ALIAS(_spawnlp, libc_spawnlp);
DEFINE_PUBLIC_WEAK_ALIAS(spawnle, libc_spawnle);
DEFINE_PUBLIC_WEAK_ALIAS(_spawnle, libc_spawnle);
DEFINE_PUBLIC_WEAK_ALIAS(spawnlpe, libc_spawnlpe);
DEFINE_PUBLIC_WEAK_ALIAS(_spawnlpe, libc_spawnlpe);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PROCESS_C */
