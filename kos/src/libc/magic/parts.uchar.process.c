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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[define_replacement(pid_t = __pid_t)]

%{
#include <features.h>
#include <process.h>
#include <uchar.h>
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__

}

%[define_wchar_replacement(__TWARGV = __T16ARGV, __T32ARGV)]
%[define_wchar_replacement(__TWENVP = __T16ENVP, __T32ENVP)]
%{
#ifndef __T16ARGV
#ifdef __USE_DOS
#define __T16ARGV char16_t const *const *__restrict ___argv
#define __T16ENVP char16_t const *const *__restrict ___envp
#else /* __USE_DOS */
#define __T16ARGV char16_t *const ___argv[__restrict_arr]
#define __T16ENVP char16_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__T16ARGV */
#ifndef __T32ARGV
#ifdef __USE_DOS
#define __T32ARGV char32_t const *const *__restrict ___argv
#define __T32ENVP char32_t const *const *__restrict ___envp
#else /* __USE_DOS */
#define __T32ARGV char32_t *const ___argv[__restrict_arr]
#define __T32ENVP char32_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__T32ARGV */
}

c16execv(*) %{uchar("wexecv")}
c32execv(*) %{uchar("wexecv")}
c16execve(*) %{uchar("wexecve")}
c32execve(*) %{uchar("wexecve")}
c16execvp(*) %{uchar("wexecvp")}
c32execvp(*) %{uchar("wexecvp")}
c16execvpe(*) %{uchar("wexecvpe")}
c32execvpe(*) %{uchar("wexecvpe")}
c16execl(*) %{uchar("wexecl")}
c32execl(*) %{uchar("wexecl")}
c16execlp(*) %{uchar("wexeclp")}
c32execlp(*) %{uchar("wexeclp")}
c16execle(*) %{uchar("wexecle")}
c32execle(*) %{uchar("wexecle")}
c16execlpe(*) %{uchar("wexeclpe")}
c32execlpe(*) %{uchar("wexeclpe")}

c16spawnv(*) %{uchar("wspawnv")}
c32spawnv(*) %{uchar("wspawnv")}
c16spawnve(*) %{uchar("wspawnve")}
c32spawnve(*) %{uchar("wspawnve")}
c16spawnvp(*) %{uchar("wspawnvp")}
c32spawnvp(*) %{uchar("wspawnvp")}
c16spawnvpe(*) %{uchar("wspawnvpe")}
c32spawnvpe(*) %{uchar("wspawnvpe")}
c16spawnl(*) %{uchar("wspawnl")}
c32spawnl(*) %{uchar("wspawnl")}
c16spawnlp(*) %{uchar("wspawnlp")}
c32spawnlp(*) %{uchar("wspawnlp")}
c16spawnle(*) %{uchar("wspawnle")}
c32spawnle(*) %{uchar("wspawnle")}
c16spawnlpe(*) %{uchar("wspawnlpe")}
c32spawnlpe(*) %{uchar("wspawnlpe")}

c16system(*) %{uchar("wsystem")}
c32system(*) %{uchar("wsystem")}

%{

#endif /* __CC__ */

__SYSDECL_END

}

