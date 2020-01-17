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

/* Only symbols defined by the C standard */
#ifndef __CRT_STANDALONE

#ifndef __CRT_NO_CTYPE
#define __CRT_HAVE_isalnum 1
#define __CRT_HAVE_isalpha 1
#define __CRT_HAVE_iscntrl 1
#define __CRT_HAVE_isdigit 1
#define __CRT_HAVE_isgraph 1
#define __CRT_HAVE_islower 1
#define __CRT_HAVE_isprint 1
#define __CRT_HAVE_ispunct 1
#define __CRT_HAVE_isspace 1
#define __CRT_HAVE_isupper 1
#define __CRT_HAVE_isxdigit 1
#define __CRT_HAVE_tolower 1
#define __CRT_HAVE_toupper 1
#endif /* !__CRT_NO_CTYPE */

#ifndef __CRT_NO_MATH
#define __CRT_HAVE_sin 1
#define __CRT_HAVE_cos 1
#define __CRT_HAVE_tan 1
#define __CRT_HAVE_asin 1
#define __CRT_HAVE_acos 1
#define __CRT_HAVE_atan 1
#define __CRT_HAVE_atan2 1
#define __CRT_HAVE_sinh 1
#define __CRT_HAVE_cosh 1
#define __CRT_HAVE_tanh 1
#define __CRT_HAVE_exp 1
#define __CRT_HAVE_log 1
#define __CRT_HAVE_log10 1
#define __CRT_HAVE_pow 1
#define __CRT_HAVE_sqrt 1
#define __CRT_HAVE_ceil 1
#define __CRT_HAVE_floor 1
#define __CRT_HAVE_fabs 1
#define __CRT_HAVE_ldexp 1
#define __CRT_HAVE_frexp 1
#define __CRT_HAVE_modf 1
#define __CRT_HAVE_fmod 1
#endif /* !__CRT_NO_MATH */

#ifndef __CRT_NO_SIGNAL
#define __CRT_HAVE_signal 1
#define __CRT_HAVE_raise 1
#endif /* !__CRT_NO_SIGNAL */

#ifndef __CRT_NO_STDIO
#define __CRT_HAVE_fopen 1
#define __CRT_HAVE_freopen 1
#define __CRT_HAVE_fflush 1
#define __CRT_HAVE_fclose 1
#define __CRT_HAVE_remove 1
#define __CRT_HAVE_rename 1
#define __CRT_HAVE_tmpfile 1
#define __CRT_HAVE_tmpname 1
#define __CRT_HAVE_setvbuf 1
#define __CRT_HAVE_setbuf 1
#define __CRT_HAVE_fprintf 1
#define __CRT_HAVE_printf 1
#define __CRT_HAVE_sprintf 1
#define __CRT_HAVE_vfprintf 1
#define __CRT_HAVE_vprintf 1
#define __CRT_HAVE_vsprintf 1
#define __CRT_HAVE_fscanf 1
#define __CRT_HAVE_scanf 1
#define __CRT_HAVE_sscanf 1
#define __CRT_HAVE_fgetc 1
#define __CRT_HAVE_fgets 1
#define __CRT_HAVE_fputc 1
#define __CRT_HAVE_fputs 1
#define __CRT_HAVE_getc 1
#define __CRT_HAVE_getchar 1
#define __CRT_HAVE_gets 1
#define __CRT_HAVE_putc 1
#define __CRT_HAVE_putchar 1
#define __CRT_HAVE_puts 1
#define __CRT_HAVE_unget 1
#define __CRT_HAVE_fread 1
#define __CRT_HAVE_fwrite 1
#define __CRT_HAVE_fseek 1
#define __CRT_HAVE_ftell 1
#define __CRT_HAVE_rewind 1
#define __CRT_HAVE_fgetpos 1
#define __CRT_HAVE_fsetpos 1
#define __CRT_HAVE_clearerr 1
#define __CRT_HAVE_feof 1
#define __CRT_HAVE_ferror 1
#define __CRT_HAVE_perror 1
#endif /* !__CRT_NO_STDIO */

#ifndef __CRT_NO_STDLIB
#define __CRT_HAVE_atof 1
#define __CRT_HAVE_atoi 1
#define __CRT_HAVE_atol 1
#define __CRT_HAVE_strtod 1
#define __CRT_HAVE_strtol 1
#define __CRT_HAVE_strtoul 1
#define __CRT_HAVE_rand 1
#define __CRT_HAVE_srand 1
#define __CRT_HAVE_calloc 1
#define __CRT_HAVE_malloc 1
#define __CRT_HAVE_realloc 1
#define __CRT_HAVE_free 1
#define __CRT_HAVE_abort 1
#define __CRT_HAVE_exit 1
#define __CRT_HAVE_atexit 1
#define __CRT_HAVE_system 1
#define __CRT_HAVE_getenv 1
#define __CRT_HAVE_bsearch 1
#define __CRT_HAVE_qsort 1
#define __CRT_HAVE_abs 1
#define __CRT_HAVE_labs 1
#define __CRT_HAVE_div 1
#define __CRT_HAVE_ldiv 1
#endif /* !__CRT_NO_STDLIB */

#ifndef __CRT_NO_STRING
#define __CRT_HAVE_strcpy 1
#define __CRT_HAVE_strncpy 1
#define __CRT_HAVE_strcat 1
#define __CRT_HAVE_strncat 1
#define __CRT_HAVE_strcmp 1
#define __CRT_HAVE_strncmp 1
#define __CRT_HAVE_strchr 1
#define __CRT_HAVE_strrchr 1
#define __CRT_HAVE_strspn 1
#define __CRT_HAVE_strcspn 1
#define __CRT_HAVE_strpbrk 1
#define __CRT_HAVE_strstr 1
#define __CRT_HAVE_strlen 1
#define __CRT_HAVE_strerror 1
#define __CRT_HAVE_strtok 1
#define __CRT_HAVE_memcpy 1
#define __CRT_HAVE_memmove 1
#define __CRT_HAVE_memcmp 1
#define __CRT_HAVE_strchr 1
#define __CRT_HAVE_strchr 1
#endif /* !__CRT_NO_STRING */

#ifndef __CRT_NO_TIME
#define __CRT_HAVE_clock 1
#define __CRT_HAVE_time 1
#define __CRT_HAVE_difftime 1
#define __CRT_HAVE_mktime 1
#define __CRT_HAVE_asctime 1
#define __CRT_HAVE_ctime 1
#define __CRT_HAVE_gmtime 1
#define __CRT_HAVE_localtime 1
#define __CRT_HAVE_strftime 1
#endif /* !__CRT_NO_STRING */

#endif /* !__CRT_STANDALONE */
