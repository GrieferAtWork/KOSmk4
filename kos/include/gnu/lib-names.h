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

#define LD_LINUX_SO                     "libdl.so"
#define LD_SO                           LD_LINUX_SO
//#define LIBANL_SO                     "libanl.so"
//#define LIBBROKENLOCALE_SO            "libBrokenLocale.so"
//#define LIBCIDN_SO                    "libcidn.so"
//#define LIBCRYPT_SO                   "libcrypt.so"
#define LIBC_SO                         "libc.so"
#define LIBDL_SO                        LD_LINUX_SO
#define LIBGCC_S_SO                     "libgcc_s.so.1"
//#define LIBMVEC_SO                    "libmvec.so"
#define LIBM_SO                         "libc.so" /* Integrated into libc (but also exists as an empty library) */
//#define LIBNSL_SO                     "libnsl.so"
//#define LIBNSS_COMPAT_SO              "libnss_compat.so"
//#define LIBNSS_DB_SO                  "libnss_db.so"
//#define LIBNSS_DNS_SO                 "libnss_dns.so"
//#define LIBNSS_FILES_SO               "libnss_files.so"
//#define LIBNSS_HESIOD_SO              "libnss_hesiod.so"
//#define LIBNSS_LDAP_SO                "libnss_ldap.so"
//#define LIBNSS_NISPLUS_SO             "libnss_nisplus.so"
//#define LIBNSS_NIS_SO                 "libnss_nis.so"
//#define LIBNSS_TEST1_SO               "libnss_test1.so"
#define LIBPTHREAD_SO                   LIBC_SO
//#define LIBRESOLV_SO                  "libresolv.so"
#define LIBRT_SO                        "libc.so" /* Integrated into libc */
//#define LIBTHREAD_DB_SO               "libthread_db.so"
#define LIBUTIL_SO                      LIBC_SO
