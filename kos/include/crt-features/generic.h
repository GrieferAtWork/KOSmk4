/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

/* Only symbols defined by the C standard */
#ifndef __CRT_STANDALONE

#ifndef __CRT_NO_CTYPE
#define __CRT_HAVE_isalnum
#define __CRT_HAVE_isalpha
#define __CRT_HAVE_iscntrl
#define __CRT_HAVE_isdigit
#define __CRT_HAVE_isgraph
#define __CRT_HAVE_islower
#define __CRT_HAVE_isprint
#define __CRT_HAVE_ispunct
#define __CRT_HAVE_isspace
#define __CRT_HAVE_isupper
#define __CRT_HAVE_isxdigit
#define __CRT_HAVE_tolower
#define __CRT_HAVE_toupper
#endif /* !__CRT_NO_CTYPE */

#ifndef __CRT_NO_MATH
#define __CRT_HAVE_sin
#define __CRT_HAVE_cos
#define __CRT_HAVE_tan
#define __CRT_HAVE_asin
#define __CRT_HAVE_acos
#define __CRT_HAVE_atan
#define __CRT_HAVE_atan2
#define __CRT_HAVE_sinh
#define __CRT_HAVE_cosh
#define __CRT_HAVE_tanh
#define __CRT_HAVE_exp
#define __CRT_HAVE_log
#define __CRT_HAVE_log10
#define __CRT_HAVE_pow
#define __CRT_HAVE_sqrt
#define __CRT_HAVE_ceil
#define __CRT_HAVE_floor
#define __CRT_HAVE_fabs
#define __CRT_HAVE_ldexp
#define __CRT_HAVE_frexp
#define __CRT_HAVE_modf
#define __CRT_HAVE_fmod
#endif /* !__CRT_NO_MATH */

#ifndef __CRT_NO_SIGNAL
#define __CRT_HAVE_signal
#define __CRT_HAVE_raise
#endif /* !__CRT_NO_SIGNAL */

#ifndef __CRT_NO_STDIO
#define __CRT_HAVE_fopen
#define __CRT_HAVE_freopen
#define __CRT_HAVE_fflush
#define __CRT_HAVE_fclose
#define __CRT_HAVE_remove
#define __CRT_HAVE_rename
#define __CRT_HAVE_tmpfile
#define __CRT_HAVE_tmpname
#define __CRT_HAVE_setvbuf
#define __CRT_HAVE_setbuf
#define __CRT_HAVE_fprintf
#define __CRT_HAVE_printf
#define __CRT_HAVE_sprintf
#define __CRT_HAVE_vfprintf
#define __CRT_HAVE_vprintf
#define __CRT_HAVE_vsprintf
#define __CRT_HAVE_fscanf
#define __CRT_HAVE_scanf
#define __CRT_HAVE_sscanf
#define __CRT_HAVE_fgetc
#define __CRT_HAVE_fgets
#define __CRT_HAVE_fputc
#define __CRT_HAVE_fputs
#define __CRT_HAVE_getc
#define __CRT_HAVE_getchar
#define __CRT_HAVE_gets
#define __CRT_HAVE_putc
#define __CRT_HAVE_putchar
#define __CRT_HAVE_puts
#define __CRT_HAVE_unget
#define __CRT_HAVE_fread
#define __CRT_HAVE_fwrite
#define __CRT_HAVE_fseek
#define __CRT_HAVE_ftell
#define __CRT_HAVE_rewind
#define __CRT_HAVE_fgetpos
#define __CRT_HAVE_fsetpos
#define __CRT_HAVE_clearerr
#define __CRT_HAVE_feof
#define __CRT_HAVE_ferror
#define __CRT_HAVE_perror
#endif /* !__CRT_NO_STDIO */

#ifndef __CRT_NO_STDLIB
#define __CRT_HAVE_atof
#define __CRT_HAVE_atoi
#define __CRT_HAVE_atol
#define __CRT_HAVE_strtod
#define __CRT_HAVE_strtol
#define __CRT_HAVE_strtoul
#define __CRT_HAVE_rand
#define __CRT_HAVE_srand
#define __CRT_HAVE_calloc
#define __CRT_HAVE_malloc
#define __CRT_HAVE_realloc
#define __CRT_HAVE_free
#define __CRT_HAVE_abort
#define __CRT_HAVE_exit
#define __CRT_HAVE_atexit
#define __CRT_HAVE_system
#define __CRT_HAVE_getenv
#define __CRT_HAVE_bsearch
#define __CRT_HAVE_qsort
#define __CRT_HAVE_abs
#define __CRT_HAVE_labs
#define __CRT_HAVE_div
#define __CRT_HAVE_ldiv
#endif /* !__CRT_NO_STDLIB */

#ifndef __CRT_NO_STRING
#define __CRT_HAVE_strcpy
#define __CRT_HAVE_strncpy
#define __CRT_HAVE_strcat
#define __CRT_HAVE_strncat
#define __CRT_HAVE_strcmp
#define __CRT_HAVE_strncmp
#define __CRT_HAVE_strchr
#define __CRT_HAVE_strrchr
#define __CRT_HAVE_strspn
#define __CRT_HAVE_strcspn
#define __CRT_HAVE_strpbrk
#define __CRT_HAVE_strstr
#define __CRT_HAVE_strlen
#define __CRT_HAVE_strerror
#define __CRT_HAVE_strtok
#define __CRT_HAVE_memcpy
#define __CRT_HAVE_memmove
#define __CRT_HAVE_memcmp
#define __CRT_HAVE_strchr
#define __CRT_HAVE_strchr
#endif /* !__CRT_NO_STRING */

#ifndef __CRT_NO_TIME
#define __CRT_HAVE_clock
#define __CRT_HAVE_time
#define __CRT_HAVE_difftime
#define __CRT_HAVE_mktime
#define __CRT_HAVE_asctime
#define __CRT_HAVE_ctime
#define __CRT_HAVE_gmtime
#define __CRT_HAVE_localtime
#define __CRT_HAVE_strftime
#endif /* !__CRT_NO_STRING */

#endif /* !__CRT_STANDALONE */
