/* HASH CRC-32:0xc6b6d366 */
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
/* (#) Portability: OpenSolaris (/usr/src/lib/libbc/inc/include/vfork.h) */
#ifndef _VFORK_H
#define _VFORK_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/vfork.h> /* os-specific vfork(2) caveats: __ARCH_HAVE_*_VFORK */
#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __vfork_defined
#define __vfork_defined
#ifdef __CRT_HAVE_vfork
/* >> vfork(2)
 * Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the  parent process remaining suspended until  the
 * child process invokes one of the following system calls:
 *   - `_exit(2)'  Terminate the child process. Be sure to use `_exit' (or `_Exit')
 *                 instead of the regular `exit(3)', since the later would  include
 *                 the invocation of `atexit(3)' handlers, which would then run  in
 *                 the context of a VM that isn't actually about to be destroyed.
 *   - `execve(2)' Create a new VM that is populated with the specified process
 *                 image. The parent process will  only be resumed in case  the
 *                 new  program image could  be loaded successfully. Otherwise,
 *                 the call  to  `execve(2)'  returns normally  in  the  child.
 *                 Other functions from the exec()-family behave the same
 *
 * Care  must be taken when using this system call, since you have to make sure that
 * the  child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in  the parent process. The  same also goes for  heap
 * functions,  but generally speaking:  you really shouldn't  do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3),  which
 * is something that KOS intentionally doesn't do,  since I feel like doing so  only
 * adds unnecessary bloat to code that doesn't rely on this)
 *
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which  case the parent process will not  actually get suspended until the child
 * process performs any of the actions above. */
__CDECLARE(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,vfork,(void),())
#elif defined(__CRT_HAVE___vfork)
/* >> vfork(2)
 * Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the  parent process remaining suspended until  the
 * child process invokes one of the following system calls:
 *   - `_exit(2)'  Terminate the child process. Be sure to use `_exit' (or `_Exit')
 *                 instead of the regular `exit(3)', since the later would  include
 *                 the invocation of `atexit(3)' handlers, which would then run  in
 *                 the context of a VM that isn't actually about to be destroyed.
 *   - `execve(2)' Create a new VM that is populated with the specified process
 *                 image. The parent process will  only be resumed in case  the
 *                 new  program image could  be loaded successfully. Otherwise,
 *                 the call  to  `execve(2)'  returns normally  in  the  child.
 *                 Other functions from the exec()-family behave the same
 *
 * Care  must be taken when using this system call, since you have to make sure that
 * the  child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in  the parent process. The  same also goes for  heap
 * functions,  but generally speaking:  you really shouldn't  do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3),  which
 * is something that KOS intentionally doesn't do,  since I feel like doing so  only
 * adds unnecessary bloat to code that doesn't rely on this)
 *
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which  case the parent process will not  actually get suspended until the child
 * process performs any of the actions above. */
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,vfork,(void),__vfork,())
#elif defined(__CRT_HAVE___libc_vfork)
/* >> vfork(2)
 * Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the  parent process remaining suspended until  the
 * child process invokes one of the following system calls:
 *   - `_exit(2)'  Terminate the child process. Be sure to use `_exit' (or `_Exit')
 *                 instead of the regular `exit(3)', since the later would  include
 *                 the invocation of `atexit(3)' handlers, which would then run  in
 *                 the context of a VM that isn't actually about to be destroyed.
 *   - `execve(2)' Create a new VM that is populated with the specified process
 *                 image. The parent process will  only be resumed in case  the
 *                 new  program image could  be loaded successfully. Otherwise,
 *                 the call  to  `execve(2)'  returns normally  in  the  child.
 *                 Other functions from the exec()-family behave the same
 *
 * Care  must be taken when using this system call, since you have to make sure that
 * the  child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in  the parent process. The  same also goes for  heap
 * functions,  but generally speaking:  you really shouldn't  do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3),  which
 * is something that KOS intentionally doesn't do,  since I feel like doing so  only
 * adds unnecessary bloat to code that doesn't rely on this)
 *
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which  case the parent process will not  actually get suspended until the child
 * process performs any of the actions above. */
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,vfork,(void),__libc_vfork,())
#else /* ... */
#undef __vfork_defined
#endif /* !... */
#endif /* !__vfork_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_VFORK_H */
