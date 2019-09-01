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
#ifndef _PARTS_REDIRECT_EXEC_H
#define _PARTS_REDIRECT_EXEC_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>

#if defined(__i386__) && !defined(__x86_64__)
/* On I386, we can take advantage of how varargs are passed as
 * a 4-byte aligned vector (with is the same as a pointer array) */
#define __REDIRECT_EXECL(T, execv, path, args)                        { return execv(path, (T **)&args); }
#define __REDIRECT_EXECLE(T, execve, path, args)                      { T **__penv = (T **)&args; while (*__penv++); return execve(path, (T **)&args, __penv); }
#define __REDIRECT_FEXECLAT(T, fexecvat, dfd, path, args)             { T **__pflags = (T **)&args; while (*__penv++); return fexecvat(dfd, path, (T **)&args, *(int *)__pflags); }
#define __REDIRECT_FEXECLEAT(T, fexecveat, dfd, path, args)           { T **__penv = (T **)&args; while (*__penv++); return fexecveat(dfd, path, (T **)&args, __penv, *(int *)(__penv+1)); }
#define __REDIRECT_FEXECLPAT(T, fexecvpat, file, args)                { T **__pflags = (T **)&args; while (*__penv++); return fexecvpat(file, (T **)&args, *(int *)__pflags); }
#define __REDIRECT_FEXECLPEAT(T, fexecvpeat, file, args)              { T **__penv = (T **)&args; while (*__penv++); return fexecvpeat(file, (T **)&args, __penv, *(int *)(__penv+1)); }
#define __REDIRECT_SPAWNL(T, spawnv, mode, path, args)                { return spawnv(mode, path, (T **)&args); }
#define __REDIRECT_SPAWNLE(T, spawnve, mode, path, args)              { T **__penv = (T **)&args; while (*__penv++); return spawnve(mode, path, (T **)&args, __penv); }
#define __REDIRECT_FSPAWNLAT(T, fspawnvat, mode, dfd, path, args)     { T **__pflags = (T **)&args; while (*__penv++); return fspawnvat(mode, dfd, path, (T **)&args, *(int *)__pflags); }
#define __REDIRECT_FSPAWNLEAT(T, fspawnveat, mode, dfd, path, args)   { T **__penv = (T **)&args; while (*__penv++); return fspawnveat(mode, dfd, path, (T **)&args, __penv, *(int *)(__penv+1)); }
#define __REDIRECT_FSPAWNLPAT(T, fspawnvpat, mode, file, args)        { T **__pflags = (T **)&args; while (*__penv++); return fspawnvpat(mode, file, (T **)&args, *(int *)__pflags); }
#define __REDIRECT_FSPAWNLPEAT(T, fspawnvpeat, mode, file, args)      { T **__penv = (T **)&args; while (*__penv++); return fspawnvpeat(mode, file, (T **)&args, __penv, *(int *)(__penv+1)); }
#if 1
#define __REDIRECT_XEXECL(T, Xexecv, path, args)                      { Xexecv(path, (T **)&args); }
#define __REDIRECT_XEXECLE(T, Xexecve, path, args)                    { T **__penv = (T **)&args; while (*__penv++); Xexecve(path, (T **)&args, __penv); }
#define __REDIRECT_XFEXECLAT(T, Xfexecvat, dfd, path, args)           { T **__pflags = (T **)&args; while (*__penv++); Xfexecvat(dfd, path, (T **)&args, *(int *)__pflags); }
#define __REDIRECT_XFEXECLEAT(T, Xfexecveat, dfd, path, args)         { T **__penv = (T **)&args; while (*__penv++); Xfexecveat(dfd, path, (T **)&args, __penv, *(int *)(__penv+1)); }
#define __REDIRECT_XFEXECLPAT(T, Xfexecvpat, file, args)              { T **__pflags = (T **)&args; while (*__penv++); Xfexecvpat(file, (T **)&args, *(int *)__pflags); }
#define __REDIRECT_XFEXECLPEAT(T, Xfexecvpeat, file, args)            { T **__penv = (T **)&args; while (*__penv++); Xfexecvpeat(file, (T **)&args, __penv, *(int *)(__penv+1)); }
#define __REDIRECT_XSPAWNL(T, Xspawnv, mode, path, args)              { return Xspawnv(mode, path, (T **)&args); }
#define __REDIRECT_XSPAWNLE(T, Xspawnve, mode, path, args)            { T **__penv = (T **)&args; while (*__penv++); return Xspawnve(mode, path, (T **)&args, __penv); }
#define __REDIRECT_XFSPAWNLAT(T, Xfspawnvat, mode, dfd, path, args)   { T **__pflags = (T **)&args; while (*__penv++); return Xfspawnvat(mode, dfd, path, (T **)&args, *(int *)__pflags); }
#define __REDIRECT_XFSPAWNLEAT(T, Xfspawnveat, mode, dfd, path, args) { T **__penv = (T **)&args; while (*__penv++); return Xfspawnveat(mode, dfd, path, (T **)&args, __penv, *(int *)(__penv+1)); }
#define __REDIRECT_XFSPAWNLPAT(T, Xfspawnvpat, mode, file, args)      { T **__pflags = (T **)&args; while (*__penv++); return Xfspawnvpat(mode, file, (T **)&args, *(int *)__pflags); }
#define __REDIRECT_XFSPAWNLPEAT(T, Xfspawnvpeat, mode, file, args)    { T **__penv = (T **)&args; while (*__penv++); return Xfspawnvpeat(mode, file, (T **)&args, __penv, *(int *)(__penv+1)); }
#endif
#else
#include <libc/malloc.h>
#include <hybrid/typecore.h>
__DECL_BEGIN
__LOCAL char **(__LIBCCALL __capture_exec_args)(char *__first,
                                                __builtin_va_list __args,
                                                char ***__penviron) {
	/* TODO: Can't use malloc(). - Might corrupt heap in vfork() scenario */
	char **__new_result, **__result = __NULLPTR;
	char *__arg;
	__SIZE_TYPE__ __count = 1;
	if (!__first) {
		__result    = (char **)__libc_malloc(sizeof(char *));
		__result[0] = __NULLPTR;
		return __result;
	}
	for (;;) {
		__new_result = (char **)__libc_realloc(__result, (__count + 2) *
		                                       sizeof(char *));
		if (!__new_result) {
			__libc_free(__result);
			return __NULLPTR;
		}
		__arg = __builtin_va_arg(__args, char *);
		(__result = __new_result)[__count++] = __arg;
	}
	__result[0]       = __first;
	__result[__count] = __NULLPTR;
	if (__penviron)
		*__penviron = __builtin_va_arg(__args, char **);
	return __result;
}

__LOCAL char **(__LIBCCALL __capture_exec_argsf)(char *__first,
                                                 __builtin_va_list __args,
                                                 char ***__penviron,
                                                 int *__pflags) {
	/* TODO: Can't use malloc(). - Might corrupt heap in vfork() scenario */
	char **__new_result, **__result = __NULLPTR;
	char *__arg;
	__SIZE_TYPE__ __count = 1;
	if (!__first) {
		__result    = (char **)__libc_malloc(sizeof(char *));
		__result[0] = __NULLPTR;
		return __result;
	}
	for (;;) {
		__new_result = (char **)__libc_realloc(__result,
		                                         (__count + 2) *
		                                         sizeof(char *));
		if (!__new_result) {
			__libc_free(__result);
			return __NULLPTR;
		}
		__arg = __builtin_va_arg(__args, char *);
		(__result = __new_result)[__count++] = __arg;
	}
	__result[0]       = __first;
	__result[__count] = __NULLPTR;
	if (__penviron)
		*__penviron = __builtin_va_arg(__args, char **);
	*__pflags = __builtin_va_arg(__args, int);
	return __result;
}

#define __REDIRECT_EXECL(T, execv, path, args)                                       \
	{                                                                                \
		__builtin_va_list __execargs;                                                \
		T **__execargv;                                                              \
		int __execres;                                                               \
		__builtin_va_start(__execargs, args);                                        \
		__execargv = (T **)__capture_exec_args((char *)args, __execargs, __NULLPTR); \
		__builtin_va_end(__execargs);                                                \
		__execres = execv(path, __execargv);                                         \
		__libc_free(__execargv);                                                     \
		return __execres;                                                            \
	}
#define __REDIRECT_EXECLE(T, execve, path, args)                                                 \
	{                                                                                            \
		__builtin_va_list __execargs;                                                            \
		T **__execargv;                                                                          \
		T **__execenvp;                                                                          \
		int __execres;                                                                           \
		__builtin_va_start(__execargs, args);                                                    \
		__execargv = (T **)__capture_exec_args((char *)args, __execargs, (char ***)&__execenvp); \
		__builtin_va_end(__execargs);                                                            \
		__execres = execve(path, __execargv, __execenvp);                                        \
		__libc_free(__execargv);                                                                 \
		return __execres;                                                                        \
	}
#define __REDIRECT_SPAWNL(T, spawnv, mode, path, args)                               \
	{                                                                                \
		__builtin_va_list __execargs;                                                \
		T **__execargv;                                                              \
		int __execres;                                                               \
		__builtin_va_start(__execargs, args);                                        \
		__execargv = (T **)__capture_exec_args((char *)args, __execargs, __NULLPTR); \
		__builtin_va_end(__execargs);                                                \
		__execres = spawnv(mode, path, __execargv);                                  \
		__libc_free(__execargv);                                                     \
		return __execres;                                                            \
	}
#define __REDIRECT_SPAWNLE(T, spawnve, mode, path, args)                                         \
	{                                                                                            \
		__builtin_va_list __execargs;                                                            \
		T **__execargv;                                                                          \
		T **__execenvp;                                                                          \
		int __execres;                                                                           \
		__builtin_va_start(__execargs, args);                                                    \
		__execargv = (T **)__capture_exec_args((char *)args, __execargs, (char ***)&__execenvp); \
		__builtin_va_end(__execargs);                                                            \
		__execres = spawnve(mode, path, __execargv, __execenvp);                                 \
		__libc_free(__execargv);                                                                 \
		return __execres;                                                                        \
	}
#define __REDIRECT_FEXECLAT(T, fexecvat, dfd, path, args)                                         \
	{                                                                                             \
		__builtin_va_list __execargs;                                                             \
		T **__execargv;                                                                           \
		int __execres;                                                                            \
		int __fdflags;                                                                            \
		__builtin_va_start(__execargs, args);                                                     \
		__execargv = (T **)__capture_exec_argsf((char *)args, __execargs, __NULLPTR, &__fdflags); \
		__builtin_va_end(__execargs);                                                             \
		__execres = fexecvat(path, __execargv, __fdflags);                                        \
		__libc_free(__execargv);                                                                  \
		return __execres;                                                                         \
	}
#define __REDIRECT_FEXECLEAT(T, fexecveat, dfd, path, args)                                                   \
	{                                                                                                         \
		__builtin_va_list __execargs;                                                                         \
		T **__execargv;                                                                                       \
		T **__execenvp;                                                                                       \
		int __execres;                                                                                        \
		int __fdflags;                                                                                        \
		__builtin_va_start(__execargs, args);                                                                 \
		__execargv = (T **)__capture_exec_argsf((char *)args, __execargs, (char ***)&__execenvp, &__fdflags); \
		__builtin_va_end(__execargs);                                                                         \
		__execres = fexecveat(dfd, path, __execargv, __execenvp, __fdflags);                                  \
		__libc_free(__execargv);                                                                              \
		return __execres;                                                                                     \
	}
#define __REDIRECT_FEXECLPAT(T, fexecvpat, file, args)                                            \
	{                                                                                             \
		__builtin_va_list __execargs;                                                             \
		T **__execargv;                                                                           \
		int __execres;                                                                            \
		int __fdflags;                                                                            \
		__builtin_va_start(__execargs, args);                                                     \
		__execargv = (T **)__capture_exec_argsf((char *)args, __execargs, __NULLPTR, &__fdflags); \
		__builtin_va_end(__execargs);                                                             \
		__execres = fexecvpat(path, __execargv, __fdflags);                                       \
		__libc_free(__execargv);                                                                  \
		return __execres;                                                                         \
	}
#define __REDIRECT_FEXECLPEAT(T, fexecvpeat, path, args)                                                      \
	{                                                                                                         \
		__builtin_va_list __execargs;                                                                         \
		T **__execargv;                                                                                       \
		T **__execenvp;                                                                                       \
		int __execres;                                                                                        \
		int __fdflags;                                                                                        \
		__builtin_va_start(__execargs, args);                                                                 \
		__execargv = (T **)__capture_exec_argsf((char *)args, __execargs, (char ***)&__execenvp, &__fdflags); \
		__builtin_va_end(__execargs);                                                                         \
		__execres = fexecvpeat(path, __execargv, __execenvp, __fdflags);                                      \
		__libc_free(__execargv);                                                                              \
		return __execres;                                                                                     \
	}
#define __REDIRECT_FSPAWNLAT(T, fspawnvat, mode, dfd, path, args)                                    \
	{                                                                                                \
		__builtin_va_list __spawnargs;                                                               \
		T **__spawnargv;                                                                             \
		pid_t __spawnres;                                                                            \
		int __fdflags;                                                                               \
		__builtin_va_start(__spawnargs, args);                                                       \
		__spawnargv = (T **)__capture_spawn_argsf((char *)args, __spawnargs, __NULLPTR, &__fdflags); \
		__builtin_va_end(__spawnargs, args);                                                         \
		__spawnres = fspawnvat(mode, path, __spawnargv, __fdflags);                                  \
		__libc_free(__spawnargv);                                                                    \
		return __spawnres;                                                                           \
	}
#define __REDIRECT_FSPAWNLEAT(T, fspawnveat, mode, dfd, path, args)                                               \
	{                                                                                                             \
		__builtin_va_list __spawnargs;                                                                            \
		T **__spawnargv;                                                                                          \
		T **__spawnenvp;                                                                                          \
		pid_t __spawnres;                                                                                         \
		int __fdflags;                                                                                            \
		__builtin_va_start(__spawnargs, args);                                                                    \
		__spawnargv = (T **)__capture_spawn_argsf((char *)args, __spawnargs, (char ***)&__spawnenvp, &__fdflags); \
		__builtin_va_end(__spawnargs, args);                                                                      \
		__spawnres = fspawnveat(mode, dfd, path, __spawnargv, __spawnenvp, __fdflags);                            \
		__libc_free(__spawnargv);                                                                                 \
		return __spawnres;                                                                                        \
	}
#define __REDIRECT_FSPAWNLPAT(T, fspawnvpat, mode, file, args)                                       \
	{                                                                                                \
		__builtin_va_list __spawnargs;                                                               \
		T **__spawnargv;                                                                             \
		pid_t __spawnres;                                                                            \
		int __fdflags;                                                                               \
		__builtin_va_start(__spawnargs, args);                                                       \
		__spawnargv = (T **)__capture_spawn_argsf((char *)args, __spawnargs, __NULLPTR, &__fdflags); \
		__builtin_va_end(__spawnargs, args);                                                         \
		__spawnres = fspawnvpat(mode, path, __spawnargv, __fdflags);                                 \
		__libc_free(__spawnargv);                                                                    \
		return __spawnres;                                                                           \
	}
#define __REDIRECT_FSPAWNLPEAT(T, fspawnvpeat, mode, path, args)                                                  \
	{                                                                                                             \
		__builtin_va_list __spawnargs;                                                                            \
		T **__spawnargv;                                                                                          \
		T **__spawnenvp;                                                                                          \
		pid_t __spawnres;                                                                                         \
		int __fdflags;                                                                                            \
		__builtin_va_start(__spawnargs, args);                                                                    \
		__spawnargv = (T **)__capture_spawn_argsf((char *)args, __spawnargs, (char ***)&__spawnenvp, &__fdflags); \
		__builtin_va_end(__spawnargs, args);                                                                      \
		__spawnres = fspawnvpeat(mode, path, __spawnargv, __spawnenvp, __fdflags);                                \
		__libc_free(__spawnargv);                                                                                 \
		return __spawnres;                                                                                        \
	}

#if 1
#define __REDIRECT_XEXECL(T, Xexecv, path, args)                                     \
	{                                                                                \
		__builtin_va_list __execargs;                                                \
		T **__execargv;                                                              \
		__builtin_va_start(__execargs, args);                                        \
		__execargv = (T **)__capture_exec_args((char *)args, __execargs, __NULLPTR); \
		__builtin_va_end(__execargs);                                                \
		__TRY {                                                                      \
			Xexecv(path, __execargv);                                                \
		}                                                                            \
		__FINALLY {                                                                  \
			__libc_free(__spawnargv);                                                \
		}                                                                            \
	}
#define __REDIRECT_XEXECLE(T, Xexecve, path, args)                                               \
	{                                                                                            \
		__builtin_va_list __execargs;                                                            \
		T **__execargv;                                                                          \
		T **__execenvp;                                                                          \
		__builtin_va_start(__execargs, args);                                                    \
		__execargv = (T **)__capture_exec_args((char *)args, __execargs, (char ***)&__execenvp); \
		__builtin_va_end(__execargs);                                                            \
		__TRY {                                                                                  \
			Xexecve(path, __execargv, __execenvp);                                               \
		}                                                                                        \
		__FINALLY {                                                                              \
			__libc_free(__spawnargv);                                                            \
		}                                                                                        \
	}
#define __REDIRECT_XSPAWNL(T, Xspawnv, mode, path, args)                             \
	{                                                                                \
		__builtin_va_list __execargs;                                                \
		T **__execargv;                                                              \
		int __execres;                                                               \
		__builtin_va_start(__execargs, args);                                        \
		__execargv = (T **)__capture_exec_args((char *)args, __execargs, __NULLPTR); \
		__builtin_va_end(__execargs);                                                \
		__TRY {                                                                      \
			__execres = Xspawnv(mode, path, __execargv);                             \
		}                                                                            \
		__FINALLY {                                                                  \
			__libc_free(__spawnargv);                                                \
		}                                                                            \
		return __execres;                                                            \
	}
#define __REDIRECT_XSPAWNLE(T, Xspawnve, mode, path, args)                                       \
	{                                                                                            \
		__builtin_va_list __execargs;                                                            \
		T **__execargv;                                                                          \
		T **__execenvp;                                                                          \
		int __execres;                                                                           \
		__builtin_va_start(__execargs, args);                                                    \
		__execargv = (T **)__capture_exec_args((char *)args, __execargs, (char ***)&__execenvp); \
		__builtin_va_end(__execargs);                                                            \
		__TRY {                                                                                  \
			__execres = Xspawnve(mode, path, __execargv, __execenvp);                            \
		}                                                                                        \
		__FINALLY {                                                                              \
			__libc_free(__spawnargv);                                                            \
		}                                                                                        \
		return __execres;                                                                        \
	}
#define __REDIRECT_XFEXECLAT(T, Xfexecvat, dfd, path, args)                                       \
	{                                                                                             \
		__builtin_va_list __execargs;                                                             \
		T **__execargv;                                                                           \
		int __fdflags;                                                                            \
		__builtin_va_start(__execargs, args);                                                     \
		__execargv = (T **)__capture_exec_argsf((char *)args, __execargs, __NULLPTR, &__fdflags); \
		__builtin_va_end(__execargs);                                                             \
		__TRY {                                                                                   \
			Xfexecvat(path, __execargv, __fdflags);                                               \
		}                                                                                         \
		__FINALLY {                                                                               \
			__libc_free(__execargv);                                                              \
		}                                                                                         \
	}
#define __REDIRECT_XFEXECLEAT(T, Xfexecveat, dfd, path, args)                                                 \
	{                                                                                                         \
		__builtin_va_list __execargs;                                                                         \
		T **__execargv;                                                                                       \
		T **__execenvp;                                                                                       \
		int __fdflags;                                                                                        \
		__builtin_va_start(__execargs, args);                                                                 \
		__execargv = (T **)__capture_exec_argsf((char *)args, __execargs, (char ***)&__execenvp, &__fdflags); \
		__builtin_va_end(__execargs);                                                                         \
		__TRY {                                                                                               \
			Xfexecveat(dfd, path, __execargv, __execenvp, __fdflags);                                         \
		}                                                                                                     \
		__FINALLY {                                                                                           \
			__libc_free(__execargv);                                                                          \
		}                                                                                                     \
	}
#define __REDIRECT_XFEXECLPAT(T, Xfexecvpat, file, args)                                          \
	{                                                                                             \
		__builtin_va_list __execargs;                                                             \
		T **__execargv;                                                                           \
		int __fdflags;                                                                            \
		__builtin_va_start(__execargs, args);                                                     \
		__execargv = (T **)__capture_exec_argsf((char *)args, __execargs, __NULLPTR, &__fdflags); \
		__builtin_va_end(__execargs);                                                             \
		__TRY {                                                                                   \
			Xfexecvpat(path, __execargv, __fdflags);                                              \
		}                                                                                         \
		__FINALLY {                                                                               \
			__libc_free(__execargv);                                                              \
		}                                                                                         \
	}
#define __REDIRECT_XFEXECLPEAT(T, Xfexecvpeat, path, args)                                                    \
	{                                                                                                         \
		__builtin_va_list __execargs;                                                                         \
		T **__execargv;                                                                                       \
		T **__execenvp;                                                                                       \
		int __fdflags;                                                                                        \
		__builtin_va_start(__execargs, args);                                                                 \
		__execargv = (T **)__capture_exec_argsf((char *)args, __execargs, (char ***)&__execenvp, &__fdflags); \
		__builtin_va_end(__execargs);                                                                         \
		__TRY {                                                                                               \
			Xfexecvpeat(path, __execargv, __execenvp, __fdflags);                                             \
		}                                                                                                     \
		__FINALLY {                                                                                           \
			__libc_free(__execargv);                                                                          \
		}                                                                                                     \
	}
#define __REDIRECT_XFSPAWNLAT(T, Xfspawnvat, mode, dfd, path, args)                                  \
	{                                                                                                \
		__builtin_va_list __spawnargs;                                                               \
		T **__spawnargv;                                                                             \
		pid_t __spawnres;                                                                            \
		int __fdflags;                                                                               \
		__builtin_va_start(__spawnargs, args);                                                       \
		__spawnargv = (T **)__capture_spawn_argsf((char *)args, __spawnargs, __NULLPTR, &__fdflags); \
		__builtin_va_end(__spawnargs, args);                                                         \
		__TRY {                                                                                      \
			__spawnres = Xfspawnvat(mode, path, __spawnargv, __fdflags);                             \
		}                                                                                            \
		__FINALLY {                                                                                  \
			__libc_free(__spawnargv);                                                                \
		}                                                                                            \
		return __spawnres;                                                                           \
	}
#define __REDIRECT_XFSPAWNLEAT(T, Xfspawnveat, mode, dfd, path, args)                                             \
	{                                                                                                             \
		__builtin_va_list __spawnargs;                                                                            \
		T **__spawnargv;                                                                                          \
		T **__spawnenvp;                                                                                          \
		pid_t __spawnres;                                                                                         \
		int __fdflags;                                                                                            \
		__builtin_va_start(__spawnargs, args);                                                                    \
		__spawnargv = (T **)__capture_spawn_argsf((char *)args, __spawnargs, (char ***)&__spawnenvp, &__fdflags); \
		__builtin_va_end(__spawnargs, args);                                                                      \
		__TRY {                                                                                                   \
			__spawnres = Xfspawnveat(mode, dfd, path, __spawnargv, __spawnenvp, __fdflags);                       \
		}                                                                                                         \
		__FINALLY {                                                                                               \
			__libc_free(__spawnargv);                                                                             \
		}                                                                                                         \
		return __spawnres;                                                                                        \
	}
#define __REDIRECT_XFSPAWNLPAT(T, Xfspawnvpat, mode, file, args)                                     \
	{                                                                                                \
		__builtin_va_list __spawnargs;                                                               \
		T **__spawnargv;                                                                             \
		pid_t __spawnres;                                                                            \
		int __fdflags;                                                                               \
		__builtin_va_start(__spawnargs, args);                                                       \
		__spawnargv = (T **)__capture_spawn_argsf((char *)args, __spawnargs, __NULLPTR, &__fdflags); \
		__builtin_va_end(__spawnargs, args);                                                         \
		__TRY {                                                                                      \
			__spawnres = Xfspawnvpat(mode, path, __spawnargv, __fdflags);                            \
		}                                                                                            \
		__FINALLY {                                                                                  \
			__libc_free(__spawnargv);                                                                \
		}                                                                                            \
		return __spawnres;                                                                           \
	}
#define __REDIRECT_XFSPAWNLPEAT(T, Xfspawnvpeat, mode, path, args)                                                \
	{                                                                                                             \
		__builtin_va_list __spawnargs;                                                                            \
		T **__spawnargv;                                                                                          \
		T **__spawnenvp;                                                                                          \
		pid_t __spawnres;                                                                                         \
		int __fdflags;                                                                                            \
		__builtin_va_start(__spawnargs, args);                                                                    \
		__spawnargv = (T **)__capture_spawn_argsf((char *)args, __spawnargs, (char ***)&__spawnenvp, &__fdflags); \
		__builtin_va_end(__spawnargs, args);                                                                      \
		__TRY {                                                                                                   \
			__spawnres = Xfspawnvpeat(mode, path, __spawnargv, __spawnenvp, __fdflags);                           \
		}                                                                                                         \
		__FINALLY {                                                                                               \
			__libc_free(__spawnargv);                                                                             \
		}                                                                                                         \
		return __spawnres;                                                                                        \
	}
#endif

__DECL_END
#endif

#endif /* !_PARTS_REDIRECT_EXEC_H */
