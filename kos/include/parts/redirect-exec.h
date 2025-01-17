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
#ifndef _PARTS_REDIRECT_EXEC_H
#define _PARTS_REDIRECT_EXEC_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>

#if defined(__i386__) && !defined(__x86_64__)
/* On  i386, we can  take advantage of how  varargs are passed as
 * a 4-byte aligned vector (which is the same as a pointer array) */
#define __REDIRECT_EXECL(T, execv, path, args)                       { return execv(path, (T **)&args); }
#define __REDIRECT_EXECLE(T, execve, path, args)                     { T ***__penv = (T ***)&args; while (*__penv++); return execve(path, (T **)&args, *__penv); }
#define __REDIRECT_SPAWNL(T, spawnv, mode, path, args)               { return spawnv(mode, path, (T **)&args); }
#define __REDIRECT_SPAWNLE(T, spawnve, mode, path, args)             { T ***__penv = (T ***)&args; while (*__penv++); return spawnve(mode, path, (T **)&args, *__penv); }
#define __REDIRECT_FEXECLAT(T, fexecvat, dfd, path, args)            { T **__pflags = (T **)&args; while (*__penv++); return fexecvat(dfd, path, (T **)&args, *(int *)__pflags); }
#define __REDIRECT_FEXECLEAT(T, fexecveat, dfd, path, args)          { T ***__penv = (T ***)&args; while (*__penv++); return fexecveat(dfd, path, (T **)&args, *__penv, *(int *)(__penv + 1)); }
#define __REDIRECT_FSPAWNLAT(T, fspawnvat, mode, dfd, path, args)    { T **__pflags = (T **)&args; while (*__penv++); return fspawnvat(mode, dfd, path, (T **)&args, *(int *)__pflags); }
#define __REDIRECT_FSPAWNLEAT(T, fspawnveat, mode, dfd, path, args)  { T ***__penv = (T ***)&args; while (*__penv++); return fspawnveat(mode, dfd, path, (T **)&args, *__penv, *(int *)(__penv + 1)); }
#define __REDIRECT_XEXECL(T, Execv, path, args)                      { Execv(path, (T **)&args); }
#define __REDIRECT_XEXECLE(T, Execve, path, args)                    { T ***__penv = (T ***)&args; while (*__penv++); Execve(path, (T **)&args, *__penv); }
#define __REDIRECT_XSPAWNL(T, Spawnv, mode, path, args)              { return Spawnv(mode, path, (T **)&args); }
#define __REDIRECT_XSPAWNLE(T, Spawnve, mode, path, args)            { T ***__penv = (T ***)&args; while (*__penv++); return Spawnve(mode, path, (T **)&args, *__penv); }
#define __REDIRECT_XFEXECLAT(T, FExecvAt, dfd, path, args)           { T **__pflags = (T **)&args; while (*__penv++); FExecvAt(dfd, path, (T **)&args, *(int *)__pflags); }
#define __REDIRECT_XFEXECLEAT(T, FExecveAt, dfd, path, args)         { T ***__penv = (T ***)&args; while (*__penv++); FExecveAt(dfd, path, (T **)&args, *__penv, *(int *)(__penv + 1)); }
#define __REDIRECT_XFSPAWNLAT(T, FSpawnvAt, mode, dfd, path, args)   { T **__pflags = (T **)&args; while (*__penv++); return FSpawnvAt(mode, dfd, path, (T **)&args, *(int *)__pflags); }
#define __REDIRECT_XFSPAWNLEAT(T, FSpawnveAt, mode, dfd, path, args) { T ***__penv = (T ***)&args; while (*__penv++); return FSpawnveAt(mode, dfd, path, (T **)&args, *__penv, *(int *)(__penv + 1)); }
#else /* Arch... */
#include <hybrid/__alloca.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#ifdef __USE_DOS_ALTERATIONS
#define __PRIVATE_ARGV_CONST const
#else /* __USE_DOS_ALTERATIONS */
#define __PRIVATE_ARGV_CONST /* nothing */
#endif /* !__USE_DOS_ALTERATIONS */

#ifdef __hybrid_alloca
#define __PRIVATE_EXEC_CAPTURE_VARARGS0_EX(T, first_arg, out_argv, return_2big)                  \
	T __PRIVATE_ARGV_CONST **out_argv = __NULLPTR;                                               \
	if (first_arg) {                                                                             \
		__SIZE_TYPE__ __execargi, __execargc = 1;                                                \
		__builtin_va_list __execargs;                                                            \
		__builtin_va_start(__execargs, first_arg);                                               \
		while (__builtin_va_arg(__execargs, T __PRIVATE_ARGV_CONST *) != __NULLPTR)              \
			++__execargc;                                                                        \
		__builtin_va_end(__execargs);                                                            \
		out_argv = (T __PRIVATE_ARGV_CONST **)__hybrid_alloca((__execargc + 1) *                 \
		                                                      sizeof(T __PRIVATE_ARGV_CONST *)); \
		out_argv[0] = (T __PRIVATE_ARGV_CONST *)(first_arg);                                     \
		__builtin_va_start(__execargs, first_arg);                                               \
		for (__execargi = 1; __execargi < __execargc; ++__execargi)                              \
			out_argv[__execargi] = __builtin_va_arg(__execargs, T __PRIVATE_ARGV_CONST *);       \
		__builtin_va_end(__execargs);                                                            \
		out_argv[__execargc] = __NULLPTR;                                                        \
	} else {                                                                                     \
		out_argv = (T __PRIVATE_ARGV_CONST **)__hybrid_alloca(sizeof(T __PRIVATE_ARGV_CONST *)); \
		out_argv[0] = __NULLPTR;                                                                 \
	}

#define __PRIVATE_EXEC_CAPTURE_VARARGSN_EX(T, first_arg, out_argv, va_list_args, return_2big)    \
	__builtin_va_list va_list_args;                                                              \
	T __PRIVATE_ARGV_CONST **out_argv = __NULLPTR;                                               \
	__builtin_va_start(va_list_args, first_arg);                                                 \
	if (first_arg) {                                                                             \
		__SIZE_TYPE__ __execargi, __execargc = 1;                                                \
		while (__builtin_va_arg(va_list_args, T __PRIVATE_ARGV_CONST *) != __NULLPTR)            \
			++__execargc;                                                                        \
		__builtin_va_end(va_list_args);                                                          \
		out_argv = (T __PRIVATE_ARGV_CONST **)__hybrid_alloca((__execargc + 1) *                 \
		                                                      sizeof(T __PRIVATE_ARGV_CONST *)); \
		out_argv[0] = (T __PRIVATE_ARGV_CONST *)(first_arg);                                     \
		__builtin_va_start(va_list_args, first_arg);                                             \
		for (__execargi = 1; __execargi < __execargc; ++__execargi)                              \
			out_argv[__execargi] = __builtin_va_arg(va_list_args, T __PRIVATE_ARGV_CONST *);     \
		out_argv[__execargc] = __NULLPTR;                                                        \
		__builtin_va_arg(va_list_args, T __PRIVATE_ARGV_CONST *); /* NULL */                     \
	} else {                                                                                     \
		out_argv = (T __PRIVATE_ARGV_CONST **)__hybrid_alloca(sizeof(T __PRIVATE_ARGV_CONST *)); \
		out_argv[0] = __NULLPTR;                                                                 \
	}
#else /* __hybrid_alloca */
#include <libc/errno.h>

#ifdef __E2BIG
#define __PRIVATE_EXEC_CAPTURE_SETERRNO_2BIG() __libc_seterrno(__E2BIG)
#elif defined(__EINVAL)
#define __PRIVATE_EXEC_CAPTURE_SETERRNO_2BIG() __libc_seterrno(__EINVAL)
#elif defined(__ENOMEM)
#define __PRIVATE_EXEC_CAPTURE_SETERRNO_2BIG() __libc_seterrno(__ENOMEM)
#else /* ... */
#define __PRIVATE_EXEC_CAPTURE_SETERRNO_2BIG() __libc_seterrno(1)
#endif /* !... */

#ifndef __EXEC_ARGC_MAX
#define __EXEC_ARGC_MAX 128
#endif /* !__EXEC_ARGC_MAX */

#define __PRIVATE_EXEC_CAPTURE_VARARGS0_EX(T, first_arg, out_argv, return_2big)            \
	T __PRIVATE_ARGV_CONST *out_argv[__EXEC_ARGC_MAX + 1];                                 \
	if ((out_argv[0] = (T __PRIVATE_ARGV_CONST *)first_arg) != __NULLPTR) {                \
		__SIZE_TYPE__ __execargi, __execargc = 1;                                          \
		__builtin_va_list __execargs;                                                      \
		__builtin_va_start(__execargs, first_arg);                                         \
		while (__builtin_va_arg(__execargs, T __PRIVATE_ARGV_CONST *) != __NULLPTR)        \
			++__execargc;                                                                  \
		__builtin_va_end(__execargs);                                                      \
		if __unlikely(__execargc > __EXEC_ARGC_MAX)                                        \
			return_2big;                                                                   \
		__builtin_va_start(__execargs, first_arg);                                         \
		for (__execargi = 1; __execargi < __execargc; ++__execargi)                        \
			out_argv[__execargi] = __builtin_va_arg(__execargs, T __PRIVATE_ARGV_CONST *); \
		__builtin_va_end(__execargs);                                                      \
		out_argv[__execargc] = __NULLPTR;                                                  \
	}
#define __PRIVATE_EXEC_CAPTURE_VARARGSN_EX(T, first_arg, out_argv, va_list_args, return_2big)    \
	T __PRIVATE_ARGV_CONST *out_argv[__EXEC_ARGC_MAX + 1];                                       \
	__builtin_va_start(va_list_args, first_arg);                                                 \
	if ((out_argv[0] = (T __PRIVATE_ARGV_CONST *)first_arg) != __NULLPTR) {                      \
		__SIZE_TYPE__ __execargi, __execargc = 1;                                                \
		while (__builtin_va_arg(va_list_args, T __PRIVATE_ARGV_CONST *) != __NULLPTR)            \
			++__execargc;                                                                        \
		__builtin_va_end(va_list_args);                                                          \
		if __unlikely(__execargc > __EXEC_ARGC_MAX)                                              \
			return_2big;                                                                         \
		__builtin_va_start(va_list_args, first_arg);                                             \
		for (__execargi = 1; __execargi < __execargc; ++__execargi)                              \
			out_argv[__execargi] = __builtin_va_arg(va_list_args, T __PRIVATE_ARGV_CONST *);     \
		out_argv[__execargc] = __NULLPTR;                                                        \
		__builtin_va_arg(va_list_args, T __PRIVATE_ARGV_CONST *); /* NULL */                     \
	}
#endif /* !__hybrid_alloca */

#define __PRIVATE_EXEC_CAPTURE_VARARGS0(T, first_arg, out_argv) \
	__PRIVATE_EXEC_CAPTURE_VARARGS0_EX(T, first_arg, out_argv, return __PRIVATE_EXEC_CAPTURE_SETERRNO_2BIG())
#define __PRIVATE_EXEC_CAPTURE_VARARGSN(T, first_arg, out_argv, va_list_args) \
	__PRIVATE_EXEC_CAPTURE_VARARGSN_EX(T, first_arg, out_argv, va_list_args, return __PRIVATE_EXEC_CAPTURE_SETERRNO_2BIG())

#define __REDIRECT_EXECL(T, execv, path, args)               \
	{                                                        \
		__PRIVATE_EXEC_CAPTURE_VARARGS0(T, args, __execargv) \
		return execv(path, __execargv);                      \
	}
#define __REDIRECT_EXECLE(T, execve, path, args)                                    \
	{                                                                               \
		T __PRIVATE_ARGV_CONST *const *__execenvp;                                  \
		__PRIVATE_EXEC_CAPTURE_VARARGSN(T, args, __execargv, __execargs)            \
		__execenvp = __builtin_va_arg(__execargs, T __PRIVATE_ARGV_CONST *const *); \
		__builtin_va_end(__execargs);                                               \
		return execve(path, __execargv, __execenvp);                                \
	}
#define __REDIRECT_SPAWNL(T, spawnv, mode, path, args)       \
	{                                                        \
		__PRIVATE_EXEC_CAPTURE_VARARGS0(T, args, __execargv) \
		return spawnv(mode, path, __execargv);               \
	}
#define __REDIRECT_SPAWNLE(T, spawnve, mode, path, args)                            \
	{                                                                               \
		T __PRIVATE_ARGV_CONST *const *__execenvp;                                  \
		__PRIVATE_EXEC_CAPTURE_VARARGSN(T, args, __execargv, __execargs)            \
		__execenvp = __builtin_va_arg(__execargs, T __PRIVATE_ARGV_CONST *const *); \
		__builtin_va_end(__execargs);                                               \
		return spawnve(mode, path, __execargv, __execenvp);                         \
	}
#define __REDIRECT_FEXECLAT(T, fexecvat, dfd, path, args)                \
	{                                                                    \
		__atflag_t __execflags;                                          \
		__PRIVATE_EXEC_CAPTURE_VARARGSN(T, args, __execargv, __execargs) \
		__execflags = __builtin_va_arg(__execargs, __atflag_t);          \
		__builtin_va_end(__execargs);                                    \
		return fexecvat(dfd, path, __execargv, __execflags);             \
	}
#define __REDIRECT_FEXECLEAT(T, fexecveat, dfd, path, args)                          \
	{                                                                                \
		T __PRIVATE_ARGV_CONST *const *__execenvp;                                   \
		__atflag_t __execflags;                                                      \
		__PRIVATE_EXEC_CAPTURE_VARARGSN(T, args, __execargv, __execargs)             \
		__execenvp  = __builtin_va_arg(__execargs, T __PRIVATE_ARGV_CONST *const *); \
		__execflags = __builtin_va_arg(__execargs, __atflag_t);                      \
		__builtin_va_end(__execargs);                                                \
		return fexecveat(dfd, path, __execargv, __execenvp, __execflags);            \
	}
#define __REDIRECT_FSPAWNLAT(T, fspawnvat, mode, dfd, path, args)        \
	{                                                                    \
		__atflag_t __execflags;                                          \
		__PRIVATE_EXEC_CAPTURE_VARARGSN(T, args, __execargv, __execargs) \
		__execflags = __builtin_va_arg(__execargs, __atflag_t);          \
		__builtin_va_end(__execargs);                                    \
		return fspawnvat(mode, path, __execargv, __execflags);           \
	}
#define __REDIRECT_FSPAWNLEAT(T, fspawnveat, mode, dfd, path, args)                  \
	{                                                                                \
		T __PRIVATE_ARGV_CONST *const *__execenvp;                                   \
		__atflag_t __execflags;                                                      \
		__PRIVATE_EXEC_CAPTURE_VARARGSN(T, args, __execargv, __execargs)             \
		__execenvp  = __builtin_va_arg(__execargs, T __PRIVATE_ARGV_CONST *const *); \
		__execflags = __builtin_va_arg(__execargs, __atflag_t);                      \
		__builtin_va_end(__execargs);                                                \
		return fspawnveat(mode, path, __execargv, __execenvp, __execflags);          \
	}

#ifdef __hybrid_alloca
#define __PRIVATE_XEXEC_CAPTURE_VARARGS0(T, first_arg, out_argv) \
	__PRIVATE_EXEC_CAPTURE_VARARGS0_EX(T, first_arg, out_argv, ___NEVER_USED___)
#define __PRIVATE_XEXEC_CAPTURE_VARARGSN(T, first_arg, out_argv, va_list_args) \
	__PRIVATE_EXEC_CAPTURE_VARARGSN_EX(T, first_arg, out_argv, va_list_args, ___NEVER_USED___)
#elif defined(__KOS__) || __has_include(<kos/except.h>)
#include <kos/except.h>
#if defined(THROW) && defined(E_INVALID_ARGUMENT)
#define __PRIVATE_XEXEC_CAPTURE_VARARGS0(T, first_arg, out_argv) \
	__PRIVATE_EXEC_CAPTURE_VARARGS0_EX(T, first_arg, out_argv, THROW(E_INVALID_ARGUMENT))
#define __PRIVATE_XEXEC_CAPTURE_VARARGSN(T, first_arg, out_argv, va_list_args) \
	__PRIVATE_EXEC_CAPTURE_VARARGSN_EX(T, first_arg, out_argv, va_list_args, THROW(E_INVALID_ARGUMENT))
#endif /* THROW && E_INVALID_ARGUMENT */
#endif /* ... */

#ifdef __PRIVATE_XEXEC_CAPTURE_VARARGS0
#define __REDIRECT_XEXECL(T, Execv, path, args)               \
	{                                                         \
		__PRIVATE_XEXEC_CAPTURE_VARARGS0(T, args, __execargv) \
		Execv(path, __execargv);                              \
	}
#define __REDIRECT_XEXECLE(T, Execve, path, args)                                   \
	{                                                                               \
		T __PRIVATE_ARGV_CONST *const *__execenvp;                                  \
		__PRIVATE_XEXEC_CAPTURE_VARARGSN(T, args, __execargv, __execargs)           \
		__execenvp = __builtin_va_arg(__execargs, T __PRIVATE_ARGV_CONST *const *); \
		__builtin_va_end(__execargs);                                               \
		Execve(path, __execargv, __execenvp);                                       \
	}
#define __REDIRECT_XSPAWNL(T, Spawnv, mode, path, args)      \
	{                                                        \
		__PRIVATE_EXEC_CAPTURE_VARARGS0(T, args, __execargv) \
		return Spawnv(mode, path, __execargv);               \
	}
#define __REDIRECT_XSPAWNLE(T, Spawnve, mode, path, args)                           \
	{                                                                               \
		T __PRIVATE_ARGV_CONST *const *__execenvp;                                  \
		__PRIVATE_XEXEC_CAPTURE_VARARGSN(T, args, __execargv, __execargs)           \
		__execenvp = __builtin_va_arg(__execargs, T __PRIVATE_ARGV_CONST *const *); \
		__builtin_va_end(__execargs);                                               \
		return Spawnve(mode, path, __execargv, __execenvp);                         \
	}
#define __REDIRECT_XFEXECLAT(T, FExecvAt, dfd, path, args)                \
	{                                                                     \
		__atflag_t __execflags;                                           \
		__PRIVATE_XEXEC_CAPTURE_VARARGSN(T, args, __execargv, __execargs) \
		__execflags = __builtin_va_arg(__execargs, __atflag_t);           \
		__builtin_va_end(__execargs);                                     \
		FExecvAt(dfd, path, __execargv, __execflags);                     \
	}
#define __REDIRECT_XFEXECLEAT(T, FExecveAt, dfd, path, args)                         \
	{                                                                                \
		T __PRIVATE_ARGV_CONST *const *__execenvp;                                   \
		__atflag_t __execflags;                                                      \
		__PRIVATE_XEXEC_CAPTURE_VARARGSN(T, args, __execargv, __execargs)            \
		__execenvp  = __builtin_va_arg(__execargs, T __PRIVATE_ARGV_CONST *const *); \
		__execflags = __builtin_va_arg(__execargs, __atflag_t);                      \
		__builtin_va_end(__execargs);                                                \
		FExecveAt(dfd, path, __execargv, __execenvp, __execflags);                   \
	}
#define __REDIRECT_XFSPAWNLAT(T, FSpawnvAt, mode, dfd, path, args)        \
	{                                                                     \
		__atflag_t __execflags;                                           \
		__PRIVATE_XEXEC_CAPTURE_VARARGSN(T, args, __execargv, __execargs) \
		__execflags = __builtin_va_arg(__execargs, __atflag_t);           \
		__builtin_va_end(__execargs);                                     \
		return FSpawnvAt(mode, path, __execargv, __execflags);            \
	}
#define __REDIRECT_XFSPAWNLEAT(T, FSpawnveAt, mode, dfd, path, args)                 \
	{                                                                                \
		T __PRIVATE_ARGV_CONST *const *__execenvp;                                   \
		__atflag_t __execflags;                                                      \
		__PRIVATE_XEXEC_CAPTURE_VARARGSN(T, args, __execargv, __execargs)            \
		__execenvp  = __builtin_va_arg(__execargs, T __PRIVATE_ARGV_CONST *const *); \
		__execflags = __builtin_va_arg(__execargs, __atflag_t);                      \
		__builtin_va_end(__execargs);                                                \
		return FSpawnveAt(mode, path, __execargv, __execenvp, __execflags);          \
	}
#endif /* __PRIVATE_XEXEC_CAPTURE_VARARGS0 */

#endif /* !Arch... */

#endif /* !_PARTS_REDIRECT_EXEC_H */
