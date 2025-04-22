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
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/dlfcn.h) */
/* (#) Portability: DJGPP         (/include/dlfcn.h) */
/* (#) Portability: DragonFly BSD (/include/dlfcn.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/dlfcn.h) */
/* (#) Portability: FreeBSD       (/include/dlfcn.h) */
/* (#) Portability: GNU C Library (/dlfcn/dlfcn.h) */
/* (#) Portability: GNU Hurd      (/usr/include/dlfcn.h) */
/* (#) Portability: MinGW         (/include/dlfcn.h) */
/* (#) Portability: NetBSD        (/include/dlfcn.h) */
/* (#) Portability: OpenBSD       (/include/dlfcn.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/dlfcn.h) */
/* (#) Portability: diet libc     (/include/dlfcn.h) */
/* (#) Portability: libc4/5       (/include/dlfcn.h) */
/* (#) Portability: libc6         (/include/dlfcn.h) */
/* (#) Portability: musl libc     (/include/dlfcn.h) */
/* (#) Portability: uClibc        (/include/dlfcn.h) */
#ifndef _DLFCN_H
#define _DLFCN_H 1

#include "__crt.h"
#include "__stdinc.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/crt/dlfcn.h>
#include <bits/types.h>

#include <libdl/asm/dlfcn.h>
#include <libdl/bits/dlfcn.h>

/* NOTE: To  use  anything from  this file,  you  must link  with '-ldl',
 *       Though also note that then using the gcc from the KOS toolchain,
 *       -ldl will be included as one of the default libraries to link
 *       against, the same way that -lc  is also one of those  default
 *       libraries. */


#if (defined(__USE_KOS) && defined(__DLCACHES_SECTION_NAME) && \
     defined(__ELF__) && !defined(__KERNEL__))
#include <hybrid/__asm.h>
#include <hybrid/typecore.h>

#include <asm/asmword.h> /* .wordptr */

/* Register a  cache-clear  function  to-be  invoked
 * when system/application memory starts to run out.
 * The prototype of such a function looks like:
 * >> DECL_BEGIN // Needs to be declared with `extern "C"' in c++-mode
 * >> DL_REGISTER_CACHE(my_cache_clear_function);
 * >> PRIVATE int my_cache_clear_function(void) {
 * >>     if (clear_my_caches() != NO_CACHES_CLEARED)
 * >>         return 1; // Hint that memory may have become available.
 * >>     return 0;     // Hint that no additional memory became available.
 * >> }
 * >> DECL_END
 * Functions  registered like this  from all loaded  modules will be executed
 * when `dlclearcaches(3D)' is called (which is called when mmap(2) fails due
 * to lack of memory, which itself is called when malloc(3) needs to allocate
 * more  memory, where  failure to acquire  some would normally  result in it
 * returning NULL. -  So long as  any one of  the DL-cache functions  returns
 * non-zero, the mmap(2) operation will  be re-attempted a limited number  of
 * times) */
#define DL_REGISTER_CACHE(func)                       \
	__ASM_BEGIN                                       \
	__ASM_L(.pushsection __DLCACHES_SECTION_NAME, "") \
	__ASM_L(	.align __SIZEOF_POINTER__)            \
	__ASM_L(	.wordptr func)                        \
	__ASM_L(.popsection)                              \
	__ASM_END                                         \
	__PRIVATE __ATTR_USED int (func)(void)
#endif /* __USE_KOS && __DLCACHES_SECTION_NAME && __ELF__ && !__KERNEL__ */

#ifndef __DLFCN_CC
#define __DLFCN_CC  __LIBCCALL
#define __DLFCN_VCC __VLIBCCALL
#endif /* !__DLFCN_CC */

/* The mode-argument to `dlopen(3D)' must contain one of the following: */
#ifdef __RTLD_LAZY
#define RTLD_LAZY __RTLD_LAZY /* Lazy function call binding. */
#endif /* __RTLD_LAZY */
#ifdef __RTLD_NOW
#define RTLD_NOW __RTLD_NOW /* Immediate function call binding. */
#endif /* __RTLD_NOW */
#ifdef __RTLD_BINDING_MASK
#define RTLD_BINDING_MASK __RTLD_BINDING_MASK /* Mask of binding time value. */
#endif /* __RTLD_BINDING_MASK */


/* The mode-argument to `dlopen(3D)' must contain one of the following: */
#ifdef __RTLD_GLOBAL
#define RTLD_GLOBAL __RTLD_GLOBAL /* If the following bit is  set in the mode-argument to  `dlopen',
                                   * the  symbols of the loaded object and its dependencies are made
                                   * visible as if the object were linked directly into the program. */
#endif /* __RTLD_GLOBAL */
#ifdef __RTLD_LOCAL
#define RTLD_LOCAL __RTLD_LOCAL /* Unix98 demands the following flag which is the inverse to RTLD_GLOBAL. */
#endif /* __RTLD_LOCAL */



/* The mode-argument to `dlopen(3D)' may optionally contain any of the following: */
#ifdef __RTLD_NOLOAD
#define RTLD_NOLOAD __RTLD_NOLOAD /* Do not load the object. */
#endif /* __RTLD_NOLOAD */

/* If the associated library uses a symbol that it itself also defines,
 * the the library will use its own symbol, rather than go through  the
 * global scope to find the first (primary) definition of some symbol.
 * e.g.:
 *    - libfoo: (linked against `libc.so')
 *       >> PUBLIC void *memcpy(void *dst, void const *src, size_t num_bytes) { ... }
 *       >> PUBLIC void foo() {
 *       >>     memcpy(a, b, 42);
 *       >> }
 *    - libc:
 *       >> PUBLIC void *memcpy(void *dst, void const *src, size_t num_bytes) { ... }
 * - When `libfoo' is loaded without `RTLD_DEEPBIND', its function
 *   `foo' will be using the memcpy() function provided by libc.so
 * - When  `libfoo' is loaded  with `RTLD_DEEPBIND', its function
 *   `foo' will be using the memcpy() function it defines itself.
 * NOTE: This is the same as the ELF tag `DF_SYMBOLIC' */
#ifdef __RTLD_DEEPBIND
#define RTLD_DEEPBIND __RTLD_DEEPBIND /* Use deep binding. */
#endif /* __RTLD_DEEPBIND */

#ifdef __RTLD_NODELETE
#define RTLD_NODELETE __RTLD_NODELETE /* Do not delete object when closed. */
#endif /* __RTLD_NODELETE */

#if defined(__USE_KOS) && defined(__RTLD_NOINIT)
#define RTLD_NOINIT __RTLD_NOINIT /* KOS Extension: Don't run module initializers, and consequently
                                   *                skip running finalizers as well.
                                   * When set, `dlopen(3D)' will immediately return to the caller upon success,
                                   * rather  than  running  initializers  of  all  affected  libraries   first.
                                   * HINT: You may  run  initializers  (and finalizers  during  exit())  at  a
                                   *       later time by calling `dlopen(3D)' again without passing this flag.
                                   * WARNING: Initializers of newly loaded dependencies will not be executed
                                   *          either! */
#endif /* __USE_KOS && __RTLD_NOINIT */

#if defined(__USE_NETBSD) && defined(__RTLD_LAZY)
#define DL_LAZY __RTLD_LAZY /* Lazy function call binding. */
#endif /* __USE_NETBSD && __RTLD_LAZY */


#if defined(__USE_NETBSD) || defined(__USE_SOLARIS) || defined(__USE_GNU)
/* If the first argument of `dlsym(3D)' or `dlvsym(3D)' is set to
 * RTLD_NEXT, the run-time address of the symbol called `name' in
 * the  next shared  object is  returned. The  "next" relation is
 * defined  by  the  order   the  shared  objects  were   loaded.
 * Or for the C-savvy:
 *     `RTLD_DEFAULT' <==> `#include'
 *     `RTLD_NEXT'    <==> `#include_next' */
#ifdef __RTLD_NEXT
#define RTLD_NEXT __RTLD_NEXT
#endif /* __RTLD_NEXT */

/* If the first argument to `dlsym(3D)' or `dlvsym(3D)' is set to
 * RTLD_DEFAULT the run-time address of the symbol called  `name'
 * in the global scope is returned.
 * HINT: The global scope is the  same as that of  the root executable, as  seen
 *       under /proc/PID/exe (or as returned by `dlmodulename(dlopen(NULL, 0))'. */
#ifdef __RTLD_DEFAULT
#define RTLD_DEFAULT __RTLD_DEFAULT
#endif /* __RTLD_DEFAULT */

/* Search the calling module. */
#ifdef __RTLD_SELF
#define RTLD_SELF __RTLD_SELF
#endif /* __RTLD_SELF */

/* Special namespace ID values. */
#ifdef __USE_GNU
#ifdef __LM_ID_BASE
#define LM_ID_BASE __LM_ID_BASE /* Initial namespace. */
#endif /* __LM_ID_BASE */
#ifdef __LM_ID_NEWLM
#define LM_ID_NEWLM __LM_ID_NEWLM /* For dlmopen: request new namespace. */
#endif /* __LM_ID_NEWLM */
#endif /* __USE_GNU */
#endif /* __USE_NETBSD || __USE_SOLARIS || __USE_GNU */



#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifdef __USE_GNU
/* Type for namespace indices. */
#ifdef __Lmid_t
typedef __Lmid_t Lmid_t;
#endif /* __Lmid_t */
#endif /* __USE_GNU */


/* Lazily load a shared library file, and return a handle to said file.
 * @param: filename: The filename of the shared library.
 *                   If  this string contains  at least 1 '/'-character,
 *                   the string will be  interpreted as a raw  filename,
 *                   such that passing it to open(2) would return a file
 *                   handle for the named library file.
 *                   In this case, `filename' may either be an absolute path,
 *                   or a path relative to the current working directory,  as
 *                   set by `chdir(2)'
 *                   If  `filename'  doesn't  contain  any  '/'-characters,  the  string
 *                   is  the  filename  of the  library  (e.g. "libc.so"),  and  will be
 *                   searched for in the set  of system library locations, as  specified
 *                   by  a  ':'-separated string  read  from `getenv("LD_LIBRARY_PATH")'
 *                   at  the time of  the process having been  started, or defaulting to
 *                   a set of paths that include at least "/usr/lib:/lib" in that order.
 *                   When `NULL' is  passed for  this argument,  a handle  for the  main
 *                   executable module  (i.e. the  `readlink /proc/self/exe' binary)  is
 *                   returned.
 * @param: mode:     Exactly  one  of  [RTLD_LAZY, RTLD_NOW],  or'd  with
 *                   exactly one of [RTLD_GLOBAL, RTLD_LOCAL], optionally
 *                   or'd with any of the other `RTLD_*' flags.
 * @return: * :   A handle to the library that got loaded.
 * @return: NULL: Failed to load the library. - Call `dlerror(3D)' to get an error message. */
#ifdef __CRT_HAVE_dlopen
__IMPDEF __ATTR_WUNUSED void *(__DLFCN_CC dlopen)(char const *__filename, int __mode) /*__THROWS(...)*/;
#endif /* __CRT_HAVE_dlopen */

/* Close  a  previously  opened  dynamic  module  handle,  as  returned by
 * `dlopen(3D)',  and  some of  the other  functions  found in  this file.
 * Note  that  this call  is implemented  as  a decref()  operation, since
 * multiple calls to `dlopen(3D)' for the same library will try to  ensure
 * that  only  a single  instance of  some unique  library is  ever loaded
 * at the same time. However, every call to `dlopen(3D)' should eventually
 * be followed by a call to `dlclose(3D)' with that same handle, such that
 * once some specific handle is closed for the last time, the library  can
 * be unloaded.
 * Note  also that  if this function  does actually unload  a library, user-
 * defined callbacks may be invoked, including `__attribute__((destructor))'
 * callbacks,  as well  as callbacks  registered dynamically  through use of
 * `DLAUXCTRL_ADD_FINALIZER' (which in turn is used by `__cxa_atexit()')
 * @return: 0 : Successfully closed the given handle.
 * @return: * : Failed to close  the handle  (which is likely  to simply  be
 *              invalid; s.a. `dlerror(3D)') Warning: Don't just willy-nilly
 *              pass invalid  handles to  this  function. Depending  on  how
 *              libdl   was  configured,  only  minimal  validation  may  be
 *              performed.  The  only  guaranty  made  is  that NULL-handles
 *              are always handled as fail-safe! */
#ifdef __CRT_HAVE_dlclose
__IMPDEF __ATTR_NONNULL((1)) int
(__DLFCN_CC dlclose)(void *__handle) /*__THROWS(...)*/;
#endif /* __CRT_HAVE_dlclose */

/* Lookup the load address of a  symbol within a shared library  `handle',
 * given  its `symbol_name'. If no such symbol exists, `NULL' is returned,
 * and `dlerror(3D)' is modified to return a human-readable error message.
 * WARNING: If  the actual address of the symbol is `NULL', then this
 *          function will still return `NULL', though will not modify
 *          the return value of `dlerror(3D)'.
 *          In normal applications, this would normally never be the case,
 *          as  libdl, as well as `ld', will  take care not to link object
 *          files such that symbols could end up overlapping with  `NULL'.
 *          However, with the existence of `STT_GNU_IFUNC' (as usable  via
 *          `__attribute__((ifunc("resolver")))'), it  is easily  possible
 *          to force some symbol to overlap with NULL.
 *          Also note that upon success,  `dlerror(3D)' will not have  been
 *          modified, meaning that if a prior error has yet to be consumed,
 *          a NULL return value, and a non-NULL `dlerror(3D)' may still not
 *          guaranty that the symbol really doesn't exist. To be absolutely
 *          certain  that  NULL  would  be  correct,  use  the   following:
 *          >> void *result;
 *          >> dlerror(); // Clear preceding error
 *          >> result = dlsym(handle, symbol_name);
 *          >> if (result == NULL) {
 *          >>     char *message = dlerror();
 *          >>     if (message != NULL) // Symbol lookup really failed.
 *          >>         fprintf(stderr, "dlerror: %s\n", message);
 *          >> }
 * @param: handle: The dynamic library handle of  the library which should  be
 *                 searched  for the specified `symbol_name', before moving on
 *                 to also search all of those libraries' dependencies for the
 *                 same `symbol_name', and  so on,  following a  breadth-first
 *                 search approach.
 *                 Alternatively, you may also pass `RTLD_DEFAULT' or `RTLD_NEXT'
 *                 to make use  of special symbol  lookup resolutions  documented
 *                 more extensively alongside these constants.
 * @return: * :    The address of the symbol in question.
 * @return: NULL:  No such symbol  (`dlerror() != NULL'), or the  symbol has  been
 *                 linked to be loaded at the address `NULL' (`dlerror() == NULL') */
#ifdef __CRT_HAVE_dlsym
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((2)) void *
(__DLFCN_CC dlsym)(void *__handle, char const *__restrict __symbol_name) /*__THROWS(...)*/;
#elif defined(__CRT_HAVE_dlfunc)
__COMPILER_REDIRECT(__IMPDEF,__ATTR_WUNUSED __ATTR_NONNULL((2)),void *,,__DLFCN_CC,
                    dlsym,(void *__handle, char const *__restrict __symbol_name),dlfunc,(__handle,__symbol_name)) /*__THROWS(...)*/
#endif /* ... */

/* Return  and clear the  current libdl error message  string, such that for
 * any error that occurs, this function will only returns non-NULL once. The
 * returned string has a human-readable format and is generated dynamically,
 * meaning that it  may contain  information that  is more  specific than  a
 * simple  `File or directory not found' message, but rather something along
 * the  lines  of  `Symbol "foo" could not be found in library "libfoo.so"'.
 * The implementation of this function looks like:
 * >> return atomic_xch(&error_message_pointer, NULL);
 *
 * Where internally, libdl will set `error_message_pointer' to a non-NULL pointer
 * when an error happens.
 * @return: * :   A pointer  to a  volatile (as  in: the  same memory  area may  be
 *                overwritten once the next dl-error happens in either the calling,
 *                !_or any other thread_!), human-readable description of the  last
 *                error that  happened during  execution of  any of  the  functions
 *                exported from libdl.
 * @return: NULL: No error happened, or the last error has already been consumed. */
#ifdef __CRT_HAVE_dlerror
__IMPDEF char *__NOTHROW(__DLFCN_CC dlerror)(void);
#endif /* __CRT_HAVE_dlerror */


#ifdef __USE_BSD
struct __dlfunc_arg { int __dlfunc_dummy; };
typedef void (*dlfunc_t)(struct __dlfunc_arg);

/* Alias  for `dlsym(3D)' that allows the return value to be cast to a function
 * prototype  without resulting in  a compiler warning  due to a non-compliance
 * with official C  standards (since  C says  that casting  between a  function
 * pointer and a data-pointer (such as `void *') results in undefined behavior,
 * though  also note that  the POSIX standard (due  to this exact short-coming)
 * extends  upon this by  specifying that no data  is lost when  such a cast is
 * performed) */
#ifdef __CRT_HAVE_dlsym
__COMPILER_REDIRECT(__IMPDEF,__ATTR_WUNUSED __ATTR_NONNULL((2)),dlfunc_t,,__DLFCN_CC,
                    dlfunc,(void *__handle, char const *__restrict __symbol_name),dlsym,(__handle,__symbol_name)) /*__THROWS(...)*/
#elif defined(__CRT_HAVE_dlfunc)
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((2)) dlfunc_t
(__DLFCN_CC dlfunc)(void *__handle, char const *__restrict __symbol_name) /*__THROWS(...)*/;
#endif /* ... */
#endif /* __USE_BSD */

/* BSD also has a function `fdlopen(3D)' that does the same as ours does. */
#if defined(__USE_KOS) || defined(__USE_BSD)
/* Open a library, given a file descriptor previously acquired by `open(2)'
 * NOTE: This function will inherit the given `fd' on success.
 * @param: fd:   The file descriptor to use & inherit for the shared library
 * @param: mode: Exactly  one  of  [RTLD_LAZY, RTLD_NOW],  or'd  with
 *               exactly one of [RTLD_GLOBAL, RTLD_LOCAL], optionally
 *               or'd with any of the other `RTLD_*' flags. */
#ifdef __CRT_HAVE_dlfopen
__COMPILER_REDIRECT(__IMPDEF,__ATTR_WUNUSED,void *,,__DLFCN_CC,
                    fdlopen,(/*inherit(on_success)*/ __fd_t __fd, int __mode),dlfopen,(__fd,__mode)) /*__THROWS(...)*/
#elif defined(__CRT_HAVE_fdlopen)
__IMPDEF __ATTR_WUNUSED void *(__DLFCN_CC fdlopen)(/*inherit(on_success)*/ __fd_t __fd, int __mode) /*__THROWS(...)*/;
#endif /* ... */
#endif /* __USE_KOS || __USE_BSD */


#ifdef __USE_KOS
/* New DL Functions added with KOSmk4 */

/* Check if a given module is exception aware.
 * TODO: Figure out how we want to detect this condition...
 * @param: handle: The module to check
 * @return: 1 : The given module is exception aware
 * @return: 0 : The given module isn't exception aware
 * @return: * : The given module handler is invalid (s.a. `dlerror(3D)') */
#ifdef __CRT_HAVE_dlexceptaware
__IMPDEF __ATTR_WUNUSED int
__NOTHROW_NCX(__DLFCN_CC dlexceptaware)(void *__handle);
#endif /* __CRT_HAVE_dlexceptaware */


#if (defined(__CRT_HAVE_dlgethandle) || defined(__CRT_HAVE_dlgetmodule) || \
     defined(__CRT_HAVE_dlsectionmodule))
#ifndef DLGETHANDLE_FNORMAL
#define DLGETHANDLE_FNORMAL 0x0000 /* Return weak pointer to a module handle */
#define DLGETHANDLE_FINCREF 0x0001 /* Return a new reference, that must be closed by `dlclose(return)' */
/*TODO: DLGETHANDLE_FNODESC 0x0002  * If given the address of a PLT-style wrapper function, return the
                                    * module defining that wrapper, rather than the pointed-to module. */
#endif /* !DLGETHANDLE_FNORMAL */
#ifdef __CRT_HAVE_dlgetmodule
#ifndef DLGETHANDLE_FNOCASE
#define DLGETHANDLE_FNOCASE 0x8000 /* For `dlgetmodule(3D)': Ignore casing when comparing module names. */
#endif /* !DLGETHANDLE_FNOCASE */
#endif /* __CRT_HAVE_dlgetmodule */
#endif /* ... */

/* Return the handle of an already loaded library, given a static data/text pointer
 * @param: flags: Set of `DLGETHANDLE_F*' */
#ifdef __CRT_HAVE_dlgethandle
#ifndef __dlgethandle_defined
#define __dlgethandle_defined
__IMPDEF __ATTR_WUNUSED void *
__NOTHROW(__DLFCN_CC dlgethandle)(void const *__static_pointer,
                                  unsigned int __flags __DFL(DLGETHANDLE_FNORMAL));
#endif /* !__dlgethandle_defined */
#endif /* __CRT_HAVE_dlgethandle */

/* Return the handle of an already loaded library, given its name
 * @param: name:  One of the following (checked in this order):
 *                 - "/lib/libc.so"
 *                 - "libc.so"
 *                 - "libc"
 *                 - "c"
 *                 - "/LIB/LIBC.SO"  (requires `DLGETHANDLE_FNOCASE')
 *                 - "LIBC.SO"       (requires `DLGETHANDLE_FNOCASE')
 *                 - "LIBC"          (requires `DLGETHANDLE_FNOCASE')
 *                 - "C"             (requires `DLGETHANDLE_FNOCASE')
 *                Alternatively, `NULL' can be passed to return a handle for the caller's module.
 * @param: flags: Set of `DLGETHANDLE_F*' */
#ifdef __CRT_HAVE_dlgetmodule
__IMPDEF __ATTR_WUNUSED void *
__NOTHROW_NCX(__DLFCN_CC dlgetmodule)(char const *__name,
                                      unsigned int __flags __DFL(DLGETHANDLE_FNORMAL));
#endif /* __CRT_HAVE_dlgetmodule */

/* Return the internally used file descriptor for the given module `handle'
 * Note  however that this  descriptor is usually  only opened for reading!
 * @param: handle: A handle returned by `dlopen(3D)'.
 * @return: * : An open file descriptor for the given module `handle'
 *              WARNING: Attempting  to  close()  this  handle  may  cause  future
 *                       operations  performed with the associated module to fail!
 *                       Additionally, using dlclose() to close `handle' after the
 *                       module's fd was already  closed will attempt to  re-close
 *                       that same fd, possibly closing  some other handle if  the
 *                       same slot was re-used in the mean time.
 * @return: -1: Error (s.a. `dlerror(3D)') */
#ifdef __CRT_HAVE_dlmodulefd
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
__NOTHROW_NCX(__DLFCN_CC dlmodulefd)(void *__handle);
#endif /* __CRT_HAVE_dlmodulefd */

/* Return the internally  used filename for  the given module  `handle'
 * Note that this path is an absolute, canonical (realpath()) filename.
 * @param: handle: A handle returned by `dlopen(3D)'.
 * @return: * :    The absolute, unambiguous filename for the given module `handle'
 * @return: NULL:  Error (s.a. `dlerror(3D)') */
#ifdef __CRT_HAVE_dlmodulename
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *
__NOTHROW_NCX(__DLFCN_CC dlmodulename)(void *__handle);
#endif /* __CRT_HAVE_dlmodulename */

/* Return the base address offset chosen by ASLR, which is added to addresses of the given module `handle'.
 * WARNING: This function usually  returns `NULL' for  the root executable,  in which case  dlerror(3D)
 *          is not  modified, meaning  that  in order  to  safely use  this  function, you  must  first
 *          call `dlerror(3D)'  in order  to clear  any  existing errors,  then invoke  this  function,
 *          and call `dlerror(3D)' again when  NULL is returned to check  if an error really  occurred.
 *          Or alternatively,  you  can  simply  make  sure that  `handle'  isn't  invalid,  since  the
 *          only case  when this  function  can ever  fail  is when  `handle'  was already  closed,  is
 *          `NULL', or isn't a pointer returned by `dlopen(3D)', `dlgetmodule(3D)' or `dlgethandle(3D)'
 * @param: handle: A handle returned by `dlopen(3D)'.
 * @return: * : The load address / module base for the given `handle'.
 * @return: 0 : Error (s.a. `dlerror(3D)'), or load-address of ZERO */
#ifdef __CRT_HAVE_dlmodulebase
#ifndef __dlmodulebase_defined
#define __dlmodulebase_defined
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) __uintptr_t
__NOTHROW_NCX(__DLFCN_CC dlmodulebase)(void *__handle);
#endif /* !__dlmodulebase_defined */
#endif /* __CRT_HAVE_dlmodulebase */



#if (defined(__CRT_HAVE_dllocksection) || defined(__CRT_HAVE_dlunlocksection) || \
     defined(__CRT_HAVE_dlsectionname) || defined(__CRT_HAVE_dlsectionindex) ||  \
     defined(__CRT_HAVE_dlsectionmodule) || defined(__CRT_HAVE_dlinflatesection))
#ifndef __dl_section_defined
#define __dl_section_defined
struct dl_section {
	void       *const ds_data;    /* [0..ds_size][const] Memory mapping for the section's contents. (`(void *)-1' instead of `NULL') */
	__size_t    const ds_size;    /* [const] Size of the section (in bytes) */
	__size_t    const ds_entsize; /* [const] Section entity size (or 0 if unknown) */
	__uintptr_t const ds_link;    /* [const] Index of another section that is linked by this one (or `0' if unused) */
	__uintptr_t const ds_info;    /* [const] Index of another section that is linked by this one (or `0' if unused) */
	__uintptr_t const ds_flags;   /* [const] Section flags (set of `SHF_*' from <elf.h>) */
};
#endif /* !__dl_section_defined */


#ifdef __CRT_HAVE_dllocksection
#ifndef DLLOCKSECTION_FNORMAL
#define DLLOCKSECTION_FNORMAL   0x0000 /* Normal section locking flags. */
#define DLLOCKSECTION_FINDEX    0x0001 /* The given `name' is actually the `(uintptr_t)name' index of the section */
#define DLLOCKSECTION_FNODATA   0x0002 /* Do not lock section data into memory, though if section data
                                        * had already been loaded, then  this flag is simply  ignored. */
#endif /* !DLLOCKSECTION_FNORMAL */

/* Lock a named section of a given dynamic library into memory.
 * @param: handle: Handle for the library who's section `name' should be locked & loaded.
 * @param: name:   Name of the section to load into memory.
 * @return: * :    A reference to a locked section object (s.a. the exposed portion of the struct above),
 *                 and allows the user to access the contents of the section, as it is loaded in  memory.
 *                 Note however that the actual  section data is usually mapped  as read-only, or at  the
 *                 very least `MAP_PRIVATE', meaning that writes aren't written back to the library file!
 * @return: NULL:  Error (s.a. `dlerror(3D)'; usually: unknown section) */
#ifndef __dllocksection_defined
#define __dllocksection_defined
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) /*REF*/ struct dl_section *
__NOTHROW_NCX(__DLFCN_CC dllocksection)(void *__handle,
                                        char const *__restrict __name,
                                        unsigned int __flags __DFL(DLLOCKSECTION_FNORMAL));
#endif /* !__dllocksection_defined */
#endif /* __CRT_HAVE_dllocksection */

/* Unlock a locked section, as previously returned by `dllocksection(3D)'
 * HINT: Think of this function as a decref(), where `dllocksection(3D)'
 *       returns a reference you inherit as the caller
 * @return: 0 : Successfully unlocked the given section `sect'
 * @return: * : Error (s.a. `dlerror(3D)') */
#ifdef __CRT_HAVE_dlunlocksection
#ifndef __dlunlocksection_defined
#define __dlunlocksection_defined
__IMPDEF __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__DLFCN_CC dlunlocksection)(/*REF*/ struct dl_section *__sect);
#endif /* !__dlunlocksection_defined */
#endif /* __CRT_HAVE_dlunlocksection */

/* Return the name of a given section, or NULL on error
 * WARNING: The name of a section can no longer be queried after the associated
 *          module  has been unloaded! If this has happened, `NULL' is returned
 *          and dlerror(3D) is set accordingly.
 *          Because the names  of sections  are stored  alongside the  module, if  you
 *          can't guaranty that  the module  associated with the  section doesn't  get
 *          unloaded while you're accessing the section's name, you must first acquire
 *          your own reference  to that module  through use of  `dlsectionmodule(3D)':
 *          >> void *mod = dlsectionmodule(my_sect, DLGETHANDLE_FINCREF);
 *          >> char const *name = dlsectionname(my_sect);
 *          >> // Make use of `name' (also check if `name' is NULL; if it is, `mod'
 *          >> // will probably also be NULL if the module had already been unloaded)
 *          >> ...
 *          >> dlclose(mod); */
#ifdef __CRT_HAVE_dlsectionname
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *
__NOTHROW_NCX(__DLFCN_CC dlsectionname)(struct dl_section *__sect);
#endif /* __CRT_HAVE_dlsectionname */

/* Returns  the index of a given section, or `(size_t)-1' on error. */
#ifdef __CRT_HAVE_dlsectionindex
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(__DLFCN_CC dlsectionindex)(struct dl_section *__sect);
#endif /* __CRT_HAVE_dlsectionindex */

/* Return the module associated with a given section, or `NULL' on error.
 * @param: flags: Set of `DLGETHANDLE_F*'
 * @return: * :   A pointer, or reference to the module handle (when `DLGETHANDLE_FINCREF' was given)
 * @return: NULL: Error (s.a. `dlerror(3D)'; usually, the module was already unloaded) */
#ifdef __CRT_HAVE_dlsectionmodule
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__DLFCN_CC dlsectionmodule)(struct dl_section *__sect,
                                          unsigned int __flags __DFL(DLGETHANDLE_FNORMAL));
#endif /* __CRT_HAVE_dlsectionmodule */

/* Try to inflate compressed  module sections (`SHF_COMPRESSED'), returning  a
 * pointer  to a decompressed  data blob that is  lazily allocated for `sect',
 * and will be freed once the section ends up being unloaded. The given `sect'
 * may  not be loaded  with `DLLOCKSECTION_FNODATA' if  this function shall be
 * used  later; if the (compressed) data used  for backing `sect' has not been
 * loaded, this function will fail.
 * When the given `sect' isn't actually compressed, this function will simply
 * return  a pointer to `sect->ds_data', and fill `*psize' (if non-NULL) with
 * `ds_size'. Otherwise, inflated data and its size are returned.
 * NOTE: This function requires libdl to  lazily load the KOS system  library
 *       `libzlib.so', as found  apart of  the KOS source  tree. Should  that
 *       library not be  loaded already,  or should loading  of said  library
 *       fail for any reason, this function will also fail, and `dlerror(3D)'
 *       will reflect what went wrong when trying to load said library.
 * NOTE: The backing memory for the deflated data blob is allocated lazily and
 *       will not be freed before `sect' is `dlunlocksection(3D)'ed the same #
 *       of times that it was `dllocksection(3D)'ed.
 * @param: psize: When non-NULL, store the size of the inflated (decompressed)
 *                data blob that is returned.
 * @return: * :   A pointer to the inflated data that is backing `sect'. When
 *                `sect'  isn't compressed, this  function will simply return
 *                the section's normal data blob, that is `sect->ds_data'
 * @return: NULL: Error (s.a. `dlerror(3D)') */
#ifdef __CRT_HAVE_dlinflatesection
#ifndef __dlinflatesection_defined
#define __dlinflatesection_defined
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__DLFCN_CC dlinflatesection)(struct dl_section *__sect,
                                           __size_t *__psize);
#endif /* !__dlinflatesection_defined */
#endif /* __CRT_HAVE_dlinflatesection */
#endif /* ... */


/* Clear internal caches used by loaded modules in order to free  up
 * available memory. This function  is automatically called by  libc
 * when `mmap(2)' fails due to lack of available virtual or physical
 * memory. For more information, see `DL_REGISTER_CACHE(3D)'
 * @return: 0: No optional memory could be released.
 * @return: 1: Some optional memory was released. */
#ifdef __CRT_HAVE_dlclearcaches
__IMPDEF int (__DLFCN_CC dlclearcaches)(void) /*__THROWS(...)*/;
#endif /* __CRT_HAVE_dlclearcaches */

/* Allocate/Free a static TLS segment
 * These functions are called by by libc in  order to safely create a new thread, such  that
 * all current and future modules are able to store thread-local storage within that thread.
 * NOTE: The caller is responsible to store the returned segment to the appropriate TLS register.
 * @return: * :   Pointer to the newly allocated TLS segment.
 * @return: NULL: Error (s.a. dlerror(3D)) */
#ifdef __CRT_HAVE_dltlsallocseg
__IMPDEF __ATTR_WUNUSED void *
__NOTHROW_NCX(__DLFCN_CC dltlsallocseg)(void);
#endif /* __CRT_HAVE_dltlsallocseg */

/* Free a previously allocated static TLS segment (usually called by `pthread_exit(3)' and friends). */
#ifdef __CRT_HAVE_dltlsfreeseg
__IMPDEF __ATTR_NONNULL((1)) int
(__DLFCN_CC dltlsfreeseg)(void *__ptr) /*__THROWS(...)*/;
#endif /* __CRT_HAVE_dltlsfreeseg */

/* DL-based TLS memory management API.
 * These functions may be used to dynamically allocate TLS memory that works everywhere where
 * ATTR_THREAD-based TLS memory also works. - However, using these functions, TLS memory  can
 * be allocated dynamically at runtime (behaving the same as a call to `dlopen(3D)' loading a
 * module containing a TLS segment would).
 * @param: min_alignment:  The minimum alignment requirements for the TLS segment base address.
 * @param: num_bytes:      The size of the TLS segment (in bytes)
 * @param: template_data:  Base address of an initialization template.
 *                         The first `template_size' bytes  of any per-thread data  segment
 *                         that gets allocated will be initialized to the contents of these
 *                         values before `perthread_init' is optionally invoked in order to
 *                         perform additional initialization.
 *                         This template is copied by this function and does not need to  keep
 *                         pointing at a valid memory location after `dltlsalloc(3D)' returns!
 * @param: template_size:  The size of `template_data' in bytes, indicating the number  of
 *                         leading bytes within the TLS segment that should be pre-defined
 *                         to mirror the contents of `template_data' at the time of a call
 *                         to this function (`template_data' itself need not remain  valid
 *                         or accessible after this function returns)
 *                         Any memory after `template_size', but before `num_bytes' is
 *                         initialized to all ZEROes, however `template_size' must not
 *                         be greater than  `num_bytes', and if  it is, this  function
 *                         returns `NULL' and sets `dlerror(3D)' accordingly.
 * @param: perthread_init: An optional callback that will be invoked on a per-thread basis
 *                         in order to perform additional initialization of the associated
 *                         TLS segment within the associated thread.
 *                         This function will be called upon first access of the segment
 *                         within  the  thread  using  the  data  (s.a. `dltlsaddr(3D)')
 *                         @param: arg:  The value of `perthread_callback_arg' passed to `dltlsalloc'
 *                         @param: base: The base  address  of  the  associated  segment  within  the
 *                                       calling thread (same as the return value of `dltlsaddr(3D)')
 *                         @param: tls_segment: The TLS segment  to which `base'  belongs (usually  that
 *                                              of the calling thread, unless `dltlsaddr2(3D)' was used)
 * @param: perthread_fini: An optional callback  that behaves  similar to  `perthread_init',
 *                         but called  by `pthread_exit(3)'  or any  other thread  finalizer
 *                         (more specifically: by `dltlsfreeseg(3D)') within any thread that
 *                         has been seen  using the  associated segment, and  causing it  to
 *                         be allocated and initialized for that thread.
 *                         Note that the actual thread calling this function may not necessarily
 *                         be the same thread that originally called `perthread_init', only that
 *                         any  call to `perthread_init' will always be followed by another call
 *                         to this function at some later point in time!
 * @param: perthread_callback_arg: A user-specified argument passed to the init/fini callbacks.
 * @return: * :            An opaque handle for the newly created TLS segment.
 *                         This handle may be used in future calls to `dltlsaddr(3D)', and can be
 *                         destroyed (causing  all  threads  that had  previously  allocated  the
 *                         segment  to delete  it and  optionally invoke  finalizer callbacks) by
 *                         passing it to `dltlsfree(3D)'
 * @return: NULL:          Failed to allocate the TLS segment (s.a. `dlerror(3D)') */
#ifdef __CRT_HAVE_dltlsalloc
__IMPDEF __ATTR_WUNUSED void *
__NOTHROW(__DLFCN_CC dltlsalloc)(__size_t __min_alignment, __size_t __num_bytes,
                                 void const *__template_data, __size_t __template_size,
                                 void (__DLFCN_CC *__perthread_init)(void *__arg, void *__base, void *__tls_segment),
                                 void (__DLFCN_CC *__perthread_fini)(void *__arg, void *__base, void *__tls_segment),
                                 void *__perthread_callback_arg);
#endif /* __CRT_HAVE_dltlsalloc */

/* Free a TLS segment previously allocated with `dltlsalloc(3D)' */
#ifdef __CRT_HAVE_dltlsfree
__IMPDEF __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__DLFCN_CC dltlsfree)(void *__tls_handle);
#endif /* __CRT_HAVE_dltlsfree */

#ifndef __DLFCN_DLTLSADDR_CC
#define __DLFCN_DLTLSADDR_CC  __DLFCN_CC
#endif /* !__DLFCN_DLTLSADDR_CC */
#ifndef __DLFCN_DLTLSADDR2_CC
#define __DLFCN_DLTLSADDR2_CC __DLFCN_CC
#endif /* !__DLFCN_DLTLSADDR2_CC */


/* Return the calling thread's base address of the TLS segment associated with `tls_handle'
 * NOTE: TLS  Segments are allocated and initialized lazily, meaning that the initializer
 *       passed to `dltlsalloc(3D)' will be called by this function upon the first use of
 *       that  segment within  each individual thread,  also causing the  finalizer to be
 *       enqueued for invocation when the calling thread exits.
 * WARNING: The order in which TLS finalizers are invoked is entirely UNDEFINED!
 * NOTE: the given  `tls_handle' may  also be  a module  handle, as  returned by  `dlopen(3D)',
 *       in which case this function  returns a pointer to the  TLS segment of that module  for
 *       the calling thread (e.g.: Such a pointer is needed by `unwind_emulator_t::sm_tlsbase')
 * @return: * :   Pointer to the base of the TLS segment associated with `tls_handle' within the calling thread.
 * @return: NULL: Invalid `tls_handle', or allocation/initialization failed. (s.a. `dlerror(3D)') */
#ifdef __CRT_HAVE_dltlsaddr
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
(__DLFCN_DLTLSADDR_CC dltlsaddr)(void *__tls_handle)
		/*__THROWS(...)*/;
#endif /* __CRT_HAVE_dltlsaddr */

/* >> dltlsaddr2(3D)
 * Same as `dltlsaddr(3D)', but used to lookup a TLS block relative to a given `tls_segment',
 * where the later was previously  allocated using `dltlsallocseg(3D)'. This function  allows
 * the caller to get a pointer to the TLS  data of another thread, and is used to  initialize
 * the `pthread_self(3)' of a newly created thread from within `pthread_create(3)'.
 * @return: * :   Pointer to the base of the TLS segment associated with `tls_handle'
 *                within the given `tls_segment'.
 * @return: NULL: Invalid `tls_handle' or `tls_segment', or
 *                allocation/initialization failed. (s.a. `dlerror(3D)') */
#ifdef __CRT_HAVE_dltlsaddr2
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) void *
(__DLFCN_DLTLSADDR2_CC dltlsaddr2)(void *__tls_handle,
                                   void *__tls_segment)
		/*__THROWS(...)*/;
#endif /* __CRT_HAVE_dltlsaddr2 */


/* Perform an auxiliary control command about a given module `handle'
 * This function is used internally, and invocation requirements for different values
 * for `cmd' may change in the future. - It's purpose is to provide access to binary-
 * specific information about loaded modules.
 * @param: handle:   Handle of the module for which to query information,
 *                   or  NULL  to   query  for   the  root   application.
 *                   Some commands  may not  make use  of this  argument.
 * @param: cmd:      The command with which information should be requested.
 * @return: NULL: No information available, or no buffer was provided (depending on `cmd')
 * @return: NULL: Error: Unknown `cmd' (s.a. dlerror(3D))
 * @return: NULL: Error: Invalid `handle' (s.a. dlerror(3D)) */
#ifdef __CRT_HAVE_dlauxctrl
__IMPDEF void *(__DLFCN_VCC dlauxctrl)(void *__handle,
                                       unsigned int __cmd,
                                       ...) /*__THROWS(...)*/;

#define DLAUXCTRL_MOD_INCREF         0xa001 /* incref() the module handle (always re-returns `handle') */
#define DLAUXCTRL_MOD_DECREF         0xa002 /* decref() the module handle (always re-returns `handle') */
#define DLAUXCTRL_MOD_WEAKINCREF     0xa003 /* weakincref() the module handle (always re-returns `handle') */
#define DLAUXCTRL_MOD_WEAKDECREF     0xa004 /* weakdecref() the module handle (always re-returns `handle') */
#define DLAUXCTRL_MOD_TRYINCREF      0xa005 /* tryincref() the module handle (always re-returns `handle', or `NULL' if the module was destroyed) */
#define DLAUXCTRL_MOD_NOTDESTROYED   0xa006 /* check if the module wasdestroyed() (re-returns `handle' if not, or `NULL' if so) */
#define DLAUXCTRL_GET_TEXTBASE       0xa010 /* Return the text base address, as needed for unwinding. Return NULL on failure, but don't set an error */
#define DLAUXCTRL_GET_DATABASE       0xa011 /* Return the data base address, as needed for unwinding. Return NULL on failure, but don't set an error */
#define DLAUXCTRL_GET_LOADSTART      0xa012 /* Return the lowest address mapped by the module */
#define DLAUXCTRL_GET_LOADEND        0xa013 /* Return 1+ the greatest address mapped by the module */
#define DLAUXCTRL_RUNFINI            0xd101 /* Run all library finalizers. `handle' is ignored but should be any valid module handle, or `NULL',
                                             * and  all  other arguments  are also  ignored; always  returns  `NULL', but  doesn't set  an error */
#define DLAUXCTRL_RUNTLSFINI         0xd102 /* Run TLS library finalizers for the calling thread. `handle' is ignored but should
                                             * be  any valid module handle, or `NULL', and all other arguments are also ignored.
                                             * Always returns `NULL', but doesn't set an error */
#define DLAUXCTRL_ADD_FINALIZER      0xd103 /* Register a dynamic finalizer callback for `handle':
                                             * >> callback = va_arg(void(__DLFCN_CC *)(void *));
                                             * >> arg      = va_arg(void *);
                                             * NOTE: When returning `handle', and `handle' was `NULL', the
                                             *       handle  for the root application is returned instead.
                                             * @return: handle: Re-returns `handle' upon success.
                                             * @return: handle: Module finalizers  have  already  been  invoked.  In
                                             *                  this case, `callback' was invoked prior to returning
                                             * @return: NULL:   Invalid `handle' (dlerror(3D) is modified)
                                             * @return: NULL:   Failed to allocate additional memory for registering `callback'. */
#define DLAUXCTRL_GET_MAIN_TLSSEG    0xd181 /* Return a pointer to the main thread's TLS segment. The caller must ensure that this
                                             * segment has not, and will not be  deleted. Otherwise, behavior is undefined. -  The
                                             * given `handle' is ignored and there is no error-return-value. */
#define DLAUXCTRL_GET_TLSSEG_COUNT   0xd182 /* Return the number of currently allocated TLS segments (usually the same as # of running threads). */
#define DLAUXCTRL_GET_TLSSEG_VALID   0xd183 /* Return non-zero if `va_arg(void *)' is a valid TLS segment (Not to be confused with TLS handles, which are just regular DL handles). */
#define DLAUXCTRL_FOREACH_TLSSEG     0xd184 /* Enumerate allocated TLS segments:
                                             * >> callback = va_arg(void *(__DLFCN_CC *)(void *cookie, void *tls_segment));
                                             * >> cookie   = va_arg(void *);
                                             * CAUTION: The given `callback' is enumerated while an internal lock is held (this
                                             *          is required to prevent the `tls_segment's passed from being deallocated
                                             *          while the call is being made). As such, the callback must be careful as
                                             *          to which function it calls, or face a deadlock.
                                             * NOTE: The given `handle' is ignored and there is no error-return-value
                                             * @return: * :   `callback' returned a non-NULL value (the return value) for the
                                             *                last  enumerated `tls_segment', following which enumeration was
                                             *                halted.
                                             * @return: NULL: All TLS segments were enumerated and passed to `callback'
                                             * @return: NULL: No TLS segments were enumerated, because none are allocated */
#define DLAUXCTRL_REGISTER_EXTENSION 0xd201 /* Register an extension to libdl:
                                             * >> extension              = va_arg(struct dlmodule_format *);
                                             * >> sizeof_dlmodule_format = va_arg(size_t);
                                             * >> sizeof_dlcore_ops      = va_arg(size_t);
                                             * NOTE: When returning `handle', and `handle' was `NULL', the
                                             *       handle  for the root application is returned instead.
                                             * @return: handle: Re-returns `handle' upon success.
                                             * @return: NULL:   Invalid `handle' (dlerror(3D) is modified)
                                             * @return: NULL:   `extension' is an invalid pointer
                                             * @return: NULL:   Unsupported value for `sizeof_dlmodule_format' (dlerror(3D) is modified)
                                             * @return: NULL:   Unsupported value for `sizeof_dlcore_ops' (dlerror(3D) is modified)
                                             * @return: NULL:   `extension->df_open' does not map to a static memory segment (dlerror(3D) is modified)
                                             * NOTE: Upon success, the module containing `extension->df_open' becomes undeletable. */
#define DLAUXCTRL_GET_DEPENDS        0xd202 /* [size_t *pcount [0..1]] Returns the module's vector of module dependencies (`MODULE **') */
#define DLAUXCTRL_ELF_CHECK          0xef00 /* Check if this module is an ELF module (re-returns `handle' if so, otherwise returns `NULL' but leaves `dlerror(3D)' unmodified) */
#define DLAUXCTRL_ELF_GET_PHDRS      0xef01 /* [size_t *pcount [0..1]] Returns the module's vector of program headers (`ElfW(Phdr) *') */
#define DLAUXCTRL_ELF_GET_SHDRS      0xef02 /* [size_t *pcount [0..1]] Returns the module's vector of section headers (`ElfW(Shdr) *') */
#define DLAUXCTRL_ELF_GET_DYN        0xef03 /* [size_t *pcount [0..1]] Returns the module's vector of dynamic tags (`ElfW(Dyn) *') */
#define DLAUXCTRL_ELF_GET_DYNSYM     0xef04 /* [size_t *pcount [0..1]] Returns the module's dynamic symbol table (`ElfW(Sym) *')
                                             * If  the  number  of  symbols  is  unknown,  `(size_t)-1'  written  to  `*pcount'. */
#define DLAUXCTRL_ELF_GET_DYNSTR     0xef05 /* Returns the module's dynamic string table (`char const *') */
#define DLAUXCTRL_ELF_GET_SHSTRTAB   0xef06 /* Returns the module's section header name string table (`char const *') */
#define DLAUXCTRL_ELF_GET_LSYMBOL    0xef07 /* [ElfW(Sym) const *dlauxctrl(..., char const *name)] Return a pointer to the named local symbol. */
#define DLAUXCTRL_ELF_SYMADDR        0xef08 /* [void *dlauxctrl(..., ElfW(Sym) const *sym)] Return the effective address of `sym'. */
#endif /* __CRT_HAVE_dlauxctrl */

#endif /* __USE_KOS */





#if defined(__USE_GNU) || defined(__USE_NETBSD) || defined(__USE_SOLARIS)
#ifdef __CRT_HAVE_dladdr
#ifndef __Dl_info_defined
#define __Dl_info_defined
typedef struct __dl_info_struct Dl_info;
#endif /* !__Dl_info_defined */

/* >> dladdr(3D)
 * Query information on the symbol/module associated with a given `address'
 * @param: address: The address to query information about.
 * @param: info:    Output buffer for where to put information.
 * @return: 1 : Success. (yes: this function returns boolean-style)
 * @return: 0 : Error (s.a. `dlerror(3D)') */
__IMPDEF __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__DLFCN_CC dladdr)(void const *__address,
                                 Dl_info *__info);
#endif /* __CRT_HAVE_dladdr */

#ifdef __CRT_HAVE_dlinfo
#if !defined(RTLD_DI_LMID) && defined(__RTLD_DI_LMID)
#define RTLD_DI_LMID        __RTLD_DI_LMID        /* Unsupported on KOS */
#endif /* !RTLD_DI_LMID && __RTLD_DI_LMID */
#if !defined(RTLD_DI_LINKMAP) && defined(__RTLD_DI_LINKMAP)
#define RTLD_DI_LINKMAP     __RTLD_DI_LINKMAP     /* [struct link_map **arg] -- *arg = GET_LINK_MAP_FOR(handle) (on KOS: this is the same as `handle') */
#endif /* !RTLD_DI_LINKMAP && __RTLD_DI_LINKMAP */
#if !defined(RTLD_DI_CONFIGADDR) && defined(__RTLD_DI_CONFIGADDR)
#define RTLD_DI_CONFIGADDR  __RTLD_DI_CONFIGADDR  /* [Dl_info *arg] Fill in `dli_fname' (module filename) and `dli_fbase' (module start address; NOT load address! Unsupported by Glibc!) */
#endif /* !RTLD_DI_CONFIGADDR && __RTLD_DI_CONFIGADDR */
#if !defined(RTLD_DI_SERINFO) && defined(__RTLD_DI_SERINFO)
typedef struct __Dl_serpath Dl_serpath;
typedef struct __Dl_serinfo Dl_serinfo;
#define RTLD_DI_SERINFO     __RTLD_DI_SERINFO     /* [Dl_serinfo *arg] Return search path information */
#endif /* !RTLD_DI_SERINFO && __RTLD_DI_SERINFO */
#if !defined(RTLD_DI_SERINFOSIZE) && defined(__RTLD_DI_SERINFOSIZE)
#define RTLD_DI_SERINFOSIZE __RTLD_DI_SERINFOSIZE /* [Dl_serinfo *arg] Like `__RTLD_DI_SERINFO', but only fill in `dls_size' and `dls_cnt' */
#endif /* !RTLD_DI_SERINFOSIZE && __RTLD_DI_SERINFOSIZE */
#if !defined(RTLD_DI_ORIGIN) && defined(__RTLD_DI_ORIGIN)
#define RTLD_DI_ORIGIN      __RTLD_DI_ORIGIN      /* [char *arg] strcpy(3) the `$ORIGIN' of this module (WARNING: UNBOUNDED BUFFER COPY) */
#endif /* !RTLD_DI_ORIGIN && __RTLD_DI_ORIGIN */
#if !defined(RTLD_DI_PROFILENAME) && defined(__RTLD_DI_PROFILENAME)
#define RTLD_DI_PROFILENAME __RTLD_DI_PROFILENAME /* Unsupported on KOS (and neither supported by Glibc) */
#endif /* !RTLD_DI_PROFILENAME && __RTLD_DI_PROFILENAME */
#if !defined(RTLD_DI_PROFILEOUT) && defined(__RTLD_DI_PROFILEOUT)
#define RTLD_DI_PROFILEOUT  __RTLD_DI_PROFILEOUT  /* Unsupported on KOS (and neither supported by Glibc) */
#endif /* !RTLD_DI_PROFILEOUT && __RTLD_DI_PROFILEOUT */
#if !defined(RTLD_DI_TLS_MODID) && defined(__RTLD_DI_TLS_MODID)
#define RTLD_DI_TLS_MODID   __RTLD_DI_TLS_MODID   /* [size_t *arg] Store TLS module id (on KOS: this is the same as `handle') */
#endif /* !RTLD_DI_TLS_MODID && __RTLD_DI_TLS_MODID */
#if !defined(RTLD_DI_TLS_DATA) && defined(__RTLD_DI_TLS_DATA)
#define RTLD_DI_TLS_DATA    __RTLD_DI_TLS_DATA    /* [void **arg] Same as `dltlsaddr(3)', but don't allocate TLS if not already done -- Writes NULL if not allocated or no PT_TLS segment */
#endif /* !RTLD_DI_TLS_DATA && __RTLD_DI_TLS_DATA */
#if !defined(RTLD_DI_PHDR) && defined(__RTLD_DI_PHDR)
#define RTLD_DI_PHDR        __RTLD_DI_PHDR        /* [ElfW(Phdr) const **] Store PHDR vector pointer, and return # of contained elements (only supported for ELF modules) */
#endif /* !RTLD_DI_PHDR && __RTLD_DI_PHDR */
#if !defined(RTLD_DI_MAX) && defined(__RTLD_DI_MAX)
#define RTLD_DI_MAX         __RTLD_DI_MAX
#endif /* !RTLD_DI_MAX && __RTLD_DI_MAX */
#if !defined(RTLD_DI_ARGSINFO) && defined(__RTLD_DI_ARGSINFO)
typedef struct __Dl_argsinfo Dl_argsinfo;
typedef struct __Dl_argsinfo Dl_argsinfo_t;
#define RTLD_DI_ARGSINFO    __RTLD_DI_ARGSINFO /* [Dl_argsinfo *arg] Return information from the program PEB. */
#endif /* !RTLD_DI_ARGSINFO && __RTLD_DI_ARGSINFO */


/* >> dlinfo(3)
 * Query auxiliary information on `handle', according to `request'
 * @param: request: One of `RTLD_DI_*'.
 * @param: arg:     Request-specific data (see docs of `RTLD_DI_*' codes).
 * @return: 0 : Success.
 * @return: -1: Error (s.a. `dlerror(3D)') */
__IMPDEF __ATTR_NONNULL((1, 3)) int
__NOTHROW_NCX(__DLFCN_CC dlinfo)(void *__restrict __handle,
                                 int __request,
                                 void *__arg);
#endif /* __CRT_HAVE_dlinfo */
#endif /* __USE_GNU || __USE_NETBSD || __USE_SOLARIS */


#ifdef __USE_GNU
#if defined(__CRT_HAVE_dlmopen) && defined(__Lmid_t)
__IMPDEF void *(__DLFCN_CC dlmopen)(__Lmid_t __nsid, char const *__file, int __mode) /*__THROWS(...)*/;
#endif /* __CRT_HAVE_dlmopen && __Lmid_t */

#ifdef __CRT_HAVE_dlvsym
__IMPDEF __ATTR_NONNULL((2, 3)) void *
(__DLFCN_CC dlvsym)(void *__restrict __handle,
                    char const *__name,
                    char const *__version) /*__THROWS(...)*/;
#endif /* __CRT_HAVE_dlvsym */

#ifdef __CRT_HAVE_dladdr1
#ifdef __RTLD_DL_SYMENT
#define RTLD_DL_SYMENT __RTLD_DL_SYMENT
#endif /* __RTLD_DL_SYMENT */
#ifdef __RTLD_DL_LINKMAP
#define RTLD_DL_LINKMAP __RTLD_DL_LINKMAP
#endif /* __RTLD_DL_LINKMAP */

#ifndef __Dl_info_defined
#define __Dl_info_defined
typedef struct __dl_info_struct Dl_info;
#endif /* !__Dl_info_defined */

__IMPDEF __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__DLFCN_CC dladdr1)(void const *__address, Dl_info *__info,
                                  void **__extra_info, int __flags);
#endif /* __CRT_HAVE_dladdr1 */


#ifdef __CRT_HAVE__dl_find_object
struct dl_find_object;

/* >> _dl_find_object(3)
 * Find information about the module at `address'.
 * Similar to  the KOS-specific  `dlgethandle(3D)'
 * NOTE: On KOS, this function is implemented in libc!
 * @return: 0:  Success
 * @return: -1: Error */
__IMPDEF __ATTR_OUT(2) int
__NOTHROW_NCX(__DLFCN_CC _dl_find_object)(void const *__address,
                                          struct dl_find_object *__result);
#endif /* __CRT_HAVE__dl_find_object */


#ifndef DL_CALL_FCT
/* To support profiling of shared objects it is a good idea to  call
 * the function found using `dlsym' using the following macro  since
 * these  calls do not use the PLT.  But this would mean the dynamic
 * loader has no chance to find out when the function is called. The
 * macro applies the necessary magic so that profiling is  possible.
 * Rewrite
 *      foo = (*fctp)(arg1, arg2);
 * into
 *      foo = DL_CALL_FCT(fctp, (arg1, arg2));
 */
#ifdef __CRT_HAVE__dl_mcount_wrapper_check
#define DL_CALL_FCT(fctp, args) \
	(_dl_mcount_wrapper_check((void *)(fctp)), (*(fctp))args)
__IMPDEF void __NOTHROW_NCX(__DLFCN_CC _dl_mcount_wrapper_check)(void *__selfpc);
#else /* __CRT_HAVE__dl_mcount_wrapper_check */
#define DL_CALL_FCT(fctp, args) (*(fctp)) args)
#endif /* !__CRT_HAVE__dl_mcount_wrapper_check */
#endif /* !DL_CALL_FCT */
#endif /* __USE_GNU */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_DLFCN_H */
