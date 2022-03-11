/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

/* Delete CRT features related to printf
 *
 * This can be used to force-enable header emulation of printf in order to
 * enable  all  of  KOS's  printf  extensions.  (s.a. `__WANT_KOS_PRINTF') */
#undef __CRT_HAVE___stdio_common_vfprintf
#undef __CRT_HAVE___stdio_common_vfprintf_p
#undef __CRT_HAVE___stdio_common_vfprintf_s
#undef __CRT_HAVE___stdio_common_vfwprintf
#undef __CRT_HAVE___stdio_common_vfwprintf_p
#undef __CRT_HAVE___stdio_common_vfwprintf_s
#undef __CRT_HAVE___stdio_common_vsnprintf_s
#undef __CRT_HAVE___stdio_common_vsnwprintf_s
#undef __CRT_HAVE___stdio_common_vsprintf
#undef __CRT_HAVE___stdio_common_vsprintf_p
#undef __CRT_HAVE___stdio_common_vsprintf_s
#undef __CRT_HAVE___stdio_common_vswprintf
#undef __CRT_HAVE___stdio_common_vswprintf_p
#undef __CRT_HAVE___stdio_common_vswprintf_s
#undef __CRT_HAVE___swprintf_l
#undef __CRT_HAVE___vswprintf_l
#undef __CRT_HAVE__fprintf_l
#undef __CRT_HAVE__fprintf_p
#undef __CRT_HAVE__fprintf_p_l
#undef __CRT_HAVE__fprintf_s_l
#undef __CRT_HAVE__fwprintf_l
#undef __CRT_HAVE__fwprintf_p
#undef __CRT_HAVE__fwprintf_p_l
#undef __CRT_HAVE__fwprintf_s_l
#undef __CRT_HAVE__printf_l
#undef __CRT_HAVE__printf_p
#undef __CRT_HAVE__printf_p_l
#undef __CRT_HAVE__printf_s_l
#undef __CRT_HAVE__scprintf
#undef __CRT_HAVE__scprintf_l
#undef __CRT_HAVE__scprintf_p
#undef __CRT_HAVE__scprintf_p_l
#undef __CRT_HAVE__scwprintf
#undef __CRT_HAVE__scwprintf_l
#undef __CRT_HAVE__scwprintf_p
#undef __CRT_HAVE__scwprintf_p_l
#undef __CRT_HAVE__snprintf
#undef __CRT_HAVE__snprintf_c
#undef __CRT_HAVE__snprintf_c_l
#undef __CRT_HAVE__snprintf_l
#undef __CRT_HAVE__snprintf_s
#undef __CRT_HAVE__snprintf_s_l
#undef __CRT_HAVE__snwprintf
#undef __CRT_HAVE__snwprintf_l
#undef __CRT_HAVE__snwprintf_s
#undef __CRT_HAVE__snwprintf_s_l
#undef __CRT_HAVE__sprintf_l
#undef __CRT_HAVE__sprintf_p
#undef __CRT_HAVE__sprintf_p_l
#undef __CRT_HAVE__sprintf_s_l
#undef __CRT_HAVE__swprintf
#undef __CRT_HAVE__swprintf_c
#undef __CRT_HAVE__swprintf_c_l
#undef __CRT_HAVE__swprintf_p
#undef __CRT_HAVE__swprintf_p_l
#undef __CRT_HAVE__swprintf_s_l
#undef __CRT_HAVE__vcprintf
#undef __CRT_HAVE__vcprintf_l
#undef __CRT_HAVE__vcprintf_p
#undef __CRT_HAVE__vcprintf_p_l
#undef __CRT_HAVE__vcprintf_s
#undef __CRT_HAVE__vcprintf_s_l
#undef __CRT_HAVE__vcwprintf
#undef __CRT_HAVE__vcwprintf_l
#undef __CRT_HAVE__vcwprintf_p
#undef __CRT_HAVE__vcwprintf_p_l
#undef __CRT_HAVE__vcwprintf_s
#undef __CRT_HAVE__vcwprintf_s_l
#undef __CRT_HAVE__vfprintf_l
#undef __CRT_HAVE__vfprintf_p
#undef __CRT_HAVE__vfprintf_p_l
#undef __CRT_HAVE__vfprintf_s_l
#undef __CRT_HAVE__vfwprintf_l
#undef __CRT_HAVE__vfwprintf_p
#undef __CRT_HAVE__vfwprintf_p_l
#undef __CRT_HAVE__vfwprintf_s_l
#undef __CRT_HAVE__vprintf_l
#undef __CRT_HAVE__vprintf_p
#undef __CRT_HAVE__vprintf_p_l
#undef __CRT_HAVE__vprintf_s_l
#undef __CRT_HAVE__vscprintf
#undef __CRT_HAVE__vscprintf_l
#undef __CRT_HAVE__vscprintf_p
#undef __CRT_HAVE__vscprintf_p_l
#undef __CRT_HAVE__vscwprintf
#undef __CRT_HAVE__vscwprintf_l
#undef __CRT_HAVE__vscwprintf_p
#undef __CRT_HAVE__vscwprintf_p_l
#undef __CRT_HAVE__vsnprintf
#undef __CRT_HAVE__vsnprintf_c
#undef __CRT_HAVE__vsnprintf_c_l
#undef __CRT_HAVE__vsnprintf_l
#undef __CRT_HAVE__vsnprintf_s
#undef __CRT_HAVE__vsnprintf_s_l
#undef __CRT_HAVE__vsnwprintf
#undef __CRT_HAVE__vsnwprintf_l
#undef __CRT_HAVE__vsnwprintf_s
#undef __CRT_HAVE__vsnwprintf_s_l
#undef __CRT_HAVE__vsprintf_l
#undef __CRT_HAVE__vsprintf_p
#undef __CRT_HAVE__vsprintf_p_l
#undef __CRT_HAVE__vsprintf_s_l
#undef __CRT_HAVE__vswprintf
#undef __CRT_HAVE__vswprintf_c
#undef __CRT_HAVE__vswprintf_c_l
#undef __CRT_HAVE__vswprintf_l
#undef __CRT_HAVE__vswprintf_p
#undef __CRT_HAVE__vswprintf_p_l
#undef __CRT_HAVE__vswprintf_s_l
#undef __CRT_HAVE__vwprintf_l
#undef __CRT_HAVE__vwprintf_p
#undef __CRT_HAVE__vwprintf_p_l
#undef __CRT_HAVE__vwprintf_s_l
#undef __CRT_HAVE__wprintf_l
#undef __CRT_HAVE__wprintf_p
#undef __CRT_HAVE__wprintf_p_l
#undef __CRT_HAVE__wprintf_s_l
#undef __CRT_HAVE_asnprintf
#undef __CRT_HAVE_asprintf
#undef __CRT_HAVE_dprintf
#undef __CRT_HAVE_fprintf
#undef __CRT_HAVE_fprintf_s
#undef __CRT_HAVE_fwprintf
#undef __CRT_HAVE_fwprintf_s
#undef __CRT_HAVE_printf
#undef __CRT_HAVE_printf_s
#undef __CRT_HAVE_snprintf
#undef __CRT_HAVE_sprintf
#undef __CRT_HAVE_sprintf_s
#undef __CRT_HAVE_swprintf
#undef __CRT_HAVE_swprintf
#undef __CRT_HAVE_swprintf_s
#undef __CRT_HAVE_vasnprintf
#undef __CRT_HAVE_vasprintf
#undef __CRT_HAVE_vdprintf
#undef __CRT_HAVE_vfprintf
#undef __CRT_HAVE_vfprintf_s
#undef __CRT_HAVE_vfwprintf
#undef __CRT_HAVE_vfwprintf_s
#undef __CRT_HAVE_vprintf
#undef __CRT_HAVE_vprintf_s
#undef __CRT_HAVE_vsnprintf
#undef __CRT_HAVE_vsnprintf
#undef __CRT_HAVE_vsprintf
#undef __CRT_HAVE_vsprintf_s
#undef __CRT_HAVE_vswprintf
#undef __CRT_HAVE_vswprintf_s
#undef __CRT_HAVE_vwprintf
#undef __CRT_HAVE_vwprintf_s
#undef __CRT_HAVE_wprintf
#undef __CRT_HAVE_wprintf_s
