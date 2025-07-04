/* HASH CRC-32:0xa5cfc35 */
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
#ifndef DFUN
#define DFUN(section, libd_name, libc_name, returnType, argc, /*argvTypes*/...)
#endif /* !DFUN */

#ifndef TP
#define TP TIn(__SIZEOF_POINTER__)
#endif /* !TP */
#ifndef THH
#define THH TIn(__SIZEOF_CHAR__)
#endif /* !THH */
#ifndef TH
#define TH TIn(__SIZEOF_SHORT__)
#endif /* !TH */
#ifndef TD
#define TD TIn(__SIZEOF_INT__)
#endif /* !TD */
#ifndef TL
#define TL TIn(__SIZEOF_LONG__)
#endif /* !TL */
#ifndef TLL
#define TLL TIn(__SIZEOF_LONG_LONG__)
#endif /* !TLL */
#ifndef TI
#define TI TIn(__SIZEOF_SIZE_T__)
#endif /* !TI */
#ifndef TI8
#define TI8 TIn(1)
#endif /* !TI8 */
#ifndef TI16
#define TI16 TIn(2)
#endif /* !TI16 */
#ifndef TI32
#define TI32 TIn(4)
#endif /* !TI32 */
#ifndef TI64
#define TI64 TIn(8)
#endif /* !TI64 */

/* aio */
DFUN(".text.crt.dos.utility.aio", libd_aio_read, libc_aio_read, TD, 1, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_write, libc_aio_write, TD, 1, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_fsync, libc_aio_fsync, TD, 2, TIn(__SIZEOF_OFLAG_T__), TP)
DFUN(".text.crt.dos.utility.aio", libd_lio_listio, libc_lio_listio, TD, 4, TD, TP, TD, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_error, libc_aio_error, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_return, libc_aio_return, TI, 1, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_cancel, libc_aio_cancel, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_suspend, libc_aio_suspend, TD, 3, TP, TD, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_read64, libc_aio_read64, TD, 1, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_write64, libc_aio_write64, TD, 1, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_fsync64, libc_aio_fsync64, TD, 2, TD, TP)
DFUN(".text.crt.dos.utility.aio", libd_lio_listio64, libc_lio_listio64, TD, 4, TD, TP, TD, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_error64, libc_aio_error64, TD, 1, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_return64, libc_aio_return64, TI, 1, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_cancel64, libc_aio_cancel64, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_suspend64, libc_aio_suspend64, TD, 3, TP, TD, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_suspendt64, libc_aio_suspendt64, TD, 3, TP, TD, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_suspend64t64, libc_aio_suspend64t64, TD, 3, TP, TD, TP)
DFUN(".text.crt.dos.utility.aio", libd_aio_init, libc_aio_init, TV, 1, TP)

/* aliases */
DFUN(".text.crt.dos.database.aliases", libd_getaliasent_r, libc_getaliasent_r, TIn(__SIZEOF_ERRNO_T__), 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.database.aliases", libd_getaliasbyname, libc_getaliasbyname, TP, 1, TP)
DFUN(".text.crt.dos.database.aliases", libd_getaliasbyname_r, libc_getaliasbyname_r, TIn(__SIZEOF_ERRNO_T__), 5, TP, TP, TP, TI, TP)

/* argp */
DFUN(".text.crt.dos.compat.glibc.string.argp", libd_argp_parse, libc_argp_parse, TIn(__SIZEOF_ERRNO_T__), 6, TP, TD, TP, TD, TP, TP)
DFUN(".text.crt.dos.compat.glibc.string.argp", libd_argp_help, libc_argp_help, TV, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.compat.glibc.string.argp", libd_argp_state_help, libc_argp_state_help, TV, 3, TP, TP, TD)
DFUN(".text.crt.dos.compat.glibc.string.argp", libd_argp_usage, libc_argp_usage, TV, 1, TP)
DFUN(".text.crt.dos.compat.glibc.string.argp", libd__option_is_short, libc__option_is_short, TD, 1, TP)
DFUN(".text.crt.dos.compat.glibc.string.argp", libd__option_is_end, libc__option_is_end, TD, 1, TP)
DFUN(".text.crt.dos.compat.glibc.string.argp", libd__argp_input, libc__argp_input, TP, 2, TP, TP)

/* argz */
DFUN(".text.crt.dos.string.argz", libd_argz_create, libc_argz_create, TIn(__SIZEOF_ERRNO_T__), 3, TP, TP, TP)
DFUN(".text.crt.dos.string.argz", libd_argz_create_sep, libc_argz_create_sep, TIn(__SIZEOF_ERRNO_T__), 4, TP, TD, TP, TP)
DFUN(".text.crt.dos.string.argz", libd_argz_count, libc_argz_count, TI, 2, TP, TI)
DFUN(".text.crt.dos.string.argz", libd_argz_extract, libc_argz_extract, TV, 3, TP, TI, TP)
DFUN(".text.crt.dos.string.argz", libd_argz_stringify, libc_argz_stringify, TV, 3, TP, TI, TD)
DFUN(".text.crt.dos.string.argz", libd_argz_append, libc_argz_append, TIn(__SIZEOF_ERRNO_T__), 4, TP, TP, TP, TI)
DFUN(".text.crt.dos.string.argz", libd_argz_add, libc_argz_add, TIn(__SIZEOF_ERRNO_T__), 3, TP, TP, TP)
DFUN(".text.crt.dos.string.argz", libd_argz_add_sep, libc_argz_add_sep, TIn(__SIZEOF_ERRNO_T__), 4, TP, TP, TP, TD)
DFUN(".text.crt.dos.string.argz", libd_argz_delete, libc_argz_delete, TV, 3, TP, TP, TP)
DFUN(".text.crt.dos.string.argz", libd_argz_insert, libc_argz_insert, TIn(__SIZEOF_ERRNO_T__), 4, TP, TP, TP, TP)
DFUN(".text.crt.dos.string.argz", libd_argz_replace, libc_argz_replace, TIn(__SIZEOF_ERRNO_T__), 5, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.string.argz", libd_argz_next, libc_argz_next, TP, 3, TP, TI, TP)

/* arpa.inet */
DFUN(".text.crt.dos.net.inet", libd_inet_netof, libc_inet_netof, TI32, 1, TS(__SIZEOF_IN_ADDR))
DFUN(".text.crt.dos.net.inet", libd_inet_lnaof, libc_inet_lnaof, TI32, 1, TS(__SIZEOF_IN_ADDR))
DFUN(".text.crt.dos.net.inet", libd_inet_makeaddr, libc_inet_makeaddr, TS(__SIZEOF_IN_ADDR), 2, TI32, TI32)
DFUN(".text.crt.dos.net.inet", libd_inet_addr, libc_inet_addr, TI32, 1, TP)
DFUN(".text.crt.dos.net.inet", libd_inet_ntoa, libc_inet_ntoa, TP, 1, TS(__SIZEOF_IN_ADDR))
DFUN(".text.crt.dos.net.inet", libd_inet_ntoa_r, libc_inet_ntoa_r, TP, 2, TS(__SIZEOF_IN_ADDR), TP)
DFUN(".text.crt.dos.net.inet", libd_inet_network, libc_inet_network, TI32, 1, TP)
DFUN(".text.crt.dos.net.inet", libd_inet_aton, libc_inet_aton, TD, 2, TP, TP)
DFUN(".text.crt.dos.net.inet", libd_inet_paton, libc_inet_paton, TD, 3, TP, TP, TD)
DFUN(".text.crt.dos.net.inet", libd_inet_neta, libc_inet_neta, TP, 3, TI32, TP, TI)
DFUN(".text.crt.dos.net.inet", libd_inet_net_ntop, libc_inet_net_ntop, TP, 5, TD, TP, TD, TP, TI)
DFUN(".text.crt.dos.net.inet", libd_inet_net_pton, libc_inet_net_pton, TD, 4, TD, TP, TP, TI)
DFUN(".text.crt.dos.net.inet", libd_inet_nsap_addr, libc_inet_nsap_addr, TD, 3, TP, TP, TD)
DFUN(".text.crt.dos.net.inet", libd_inet_nsap_ntoa, libc_inet_nsap_ntoa, TP, 3, TD, TP, TP)
DFUN(".text.crt.dos.net.inet", libd_inet_pton, libc_inet_pton, TD, 3, TD, TP, TP)
DFUN(".text.crt.dos.net.inet", libd_inet_ntop, libc_inet_ntop, TP, 4, TD, TP, TP, TIn(__SIZEOF_SOCKLEN_T__))

/* arpa.nameser */
DFUN(".text.crt.dos.net.nameser", libd_ns_get16, libc_ns_get16, TD, 1, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_get32, libc_ns_get32, TL, 1, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_put16, libc_ns_put16, TV, 2, TD, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_put32, libc_ns_put32, TV, 2, TL, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_initparse, libc_ns_initparse, TD, 3, TP, TD, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_skiprr, libc_ns_skiprr, TD, 4, TP, TP, TD, TD)
DFUN(".text.crt.dos.net.nameser", libd_ns_parserr, libc_ns_parserr, TD, 4, TP, TD, TD, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_sprintrr, libc_ns_sprintrr, TD, 6, TP, TP, TP, TP, TP, TI)
DFUN(".text.crt.dos.net.nameser", libd_ns_sprintrrf, libc_ns_sprintrrf, TD, 12, TP, TI, TP, TD, TD, TL, TP, TI, TP, TP, TP, TI)
DFUN(".text.crt.dos.net.nameser", libd_ns_format_ttl, libc_ns_format_ttl, TD, 3, TL, TP, TI)
DFUN(".text.crt.dos.net.nameser", libd_ns_parse_ttl, libc_ns_parse_ttl, TD, 2, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_datetosecs, libc_ns_datetosecs, TI32, 2, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_name_ntol, libc_ns_name_ntol, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.net.nameser", libd_ns_name_ntop, libc_ns_name_ntop, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.net.nameser", libd_ns_name_pton, libc_ns_name_pton, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.net.nameser", libd_ns_name_unpack, libc_ns_name_unpack, TD, 5, TP, TP, TP, TP, TI)
DFUN(".text.crt.dos.net.nameser", libd_ns_name_pack, libc_ns_name_pack, TD, 5, TP, TP, TD, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_name_uncompress, libc_ns_name_uncompress, TD, 5, TP, TP, TP, TP, TI)
DFUN(".text.crt.dos.net.nameser", libd_ns_name_compress, libc_ns_name_compress, TD, 5, TP, TP, TI, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_name_skip, libc_ns_name_skip, TD, 2, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_name_rollback, libc_ns_name_rollback, TV, 3, TP, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_sign, libc_ns_sign, TD, 10, TP, TP, TD, TD, TP, TP, TD, TP, TP, TIn(__SIZEOF_TIME_T__))
DFUN(".text.crt.dos.net.nameser", libd_ns_sign2, libc_ns_sign2, TD, 12, TP, TP, TD, TD, TP, TP, TD, TP, TP, TIn(__SIZEOF_TIME_T__), TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_sign_tcp, libc_ns_sign_tcp, TD, 6, TP, TP, TD, TD, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_ns_sign_tcp2, libc_ns_sign_tcp2, TD, 8, TP, TP, TD, TD, TP, TD, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_sign_tcp_init, libc_ns_sign_tcp_init, TD, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_find_tsig, libc_ns_find_tsig, TP, 2, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_verify, libc_ns_verify, TD, 9, TP, TP, TP, TP, TD, TP, TP, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_ns_verify_tcp, libc_ns_verify_tcp, TD, 4, TP, TP, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_ns_verify_tcp_init, libc_ns_verify_tcp_init, TD, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_samedomain, libc_ns_samedomain, TD, 2, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_subdomain, libc_ns_subdomain, TD, 2, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_ns_makecanon, libc_ns_makecanon, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.net.nameser", libd_ns_samename, libc_ns_samename, TD, 2, TP, TP)
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
DEFINE_INTERN_ALIAS(libd_dn_comp, libd_ns_name_compress);
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
DFUN(".text.crt.dos.net.nameser", libd_dn_comp, libc_dn_comp, TD, 5, TP, TP, TD, TP, TP)
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */

/* attr.attributes */
DFUN(".text.crt.dos.libattr", libd_attr_get, libc_attr_get, TD, 5, TP, TP, TP, TP, TD)
DFUN(".text.crt.dos.libattr", libd_attr_getf, libc_attr_getf, TD, 5, TIn(__SIZEOF_FD_T__), TP, TP, TP, TD)
DFUN(".text.crt.dos.libattr", libd_attr_set, libc_attr_set, TD, 5, TP, TP, TP, TD, TD)
DFUN(".text.crt.dos.libattr", libd_attr_setf, libc_attr_setf, TD, 5, TIn(__SIZEOF_FD_T__), TP, TP, TD, TD)
DFUN(".text.crt.dos.libattr", libd_attr_remove, libc_attr_remove, TD, 3, TP, TP, TD)
DFUN(".text.crt.dos.libattr", libd_attr_removef, libc_attr_removef, TD, 3, TIn(__SIZEOF_FD_T__), TP, TD)
DFUN(".text.crt.dos.libattr", libd_attr_list, libc_attr_list, TD, 5, TP, TP, TD, TD, TP)
DFUN(".text.crt.dos.libattr", libd_attr_listf, libc_attr_listf, TD, 5, TIn(__SIZEOF_FD_T__), TP, TD, TD, TP)
DFUN(".text.crt.dos.libattr", libd_attr_multi, libc_attr_multi, TD, 4, TP, TP, TD, TD)
DFUN(".text.crt.dos.libattr", libd_attr_multif, libc_attr_multif, TD, 4, TIn(__SIZEOF_FD_T__), TP, TD, TD)

/* bsd.libutil */
DFUN(".text.crt.dos.unsorted", libd_flopen, libc_flopen, TIn(__SIZEOF_FD_T__), 3, TP, TIn(__SIZEOF_OFLAG_T__), TIn(__SIZEOF_MODE_T__))
DFUN(".text.crt.dos.unsorted", libd_flopenat, libc_flopenat, TIn(__SIZEOF_FD_T__), 4, TIn(__SIZEOF_FD_T__), TP, TIn(__SIZEOF_OFLAG_T__), TIn(__SIZEOF_MODE_T__))

/* complex */
DFUN(".text.crt.dos.math.complex", libd_cabsf, libc_cabsf, TF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_cexpf, libc_cexpf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_clogf, libc_clogf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_cpowf, libc_cpowf, TCF, 2, TCF, TCF)
DFUN(".text.crt.dos.math.complex", libd_csqrtf, libc_csqrtf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_csinf, libc_csinf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_ccosf, libc_ccosf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_ctanf, libc_ctanf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_casinf, libc_casinf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_cacosf, libc_cacosf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_catanf, libc_catanf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_csinhf, libc_csinhf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_ccoshf, libc_ccoshf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_ctanhf, libc_ctanhf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_casinhf, libc_casinhf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_cacoshf, libc_cacoshf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_catanhf, libc_catanhf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_cargf, libc_cargf, TF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_conjf, libc_conjf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_crealf, libc_crealf, TF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_cimagf, libc_cimagf, TF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_cprojf, libc_cprojf, TCF, 1, TCF)
DFUN(".text.crt.dos.math.complex", libd_cabs, libc_cabs, TFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_cexp, libc_cexp, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_clog, libc_clog, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_cpow, libc_cpow, TCFD, 2, TCFD, TCFD)
DFUN(".text.crt.dos.math.complex", libd_csqrt, libc_csqrt, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_csin, libc_csin, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_ccos, libc_ccos, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_ctan, libc_ctan, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_casin, libc_casin, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_cacos, libc_cacos, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_catan, libc_catan, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_csinh, libc_csinh, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_ccosh, libc_ccosh, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_ctanh, libc_ctanh, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_casinh, libc_casinh, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_cacosh, libc_cacosh, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_catanh, libc_catanh, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_carg, libc_carg, TFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_conj, libc_conj, TCFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_creal, libc_creal, TFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_cimag, libc_cimag, TFD, 1, TCFD)
DFUN(".text.crt.dos.math.complex", libd_cproj, libc_cproj, TCFD, 1, TCFD)
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_cabsl, libd_cabs);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_cabsl, libc_cabsl, TFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_cexpl, libd_cexp);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_cexpl, libc_cexpl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_clogl, libd_clog);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_clogl, libc_clogl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_cpowl, libd_cpow);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_cpowl, libc_cpowl, TCFL, 2, TCFL, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_csqrtl, libd_csqrt);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_csqrtl, libc_csqrtl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_csinl, libd_csin);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_csinl, libc_csinl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_ccosl, libd_ccos);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_ccosl, libc_ccosl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_ctanl, libd_ctan);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_ctanl, libc_ctanl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_casinl, libd_casin);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_casinl, libc_casinl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_cacosl, libd_cacos);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_cacosl, libc_cacosl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_catanl, libd_catan);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_catanl, libc_catanl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_csinhl, libd_csinh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_csinhl, libc_csinhl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_ccoshl, libd_ccosh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_ccoshl, libc_ccoshl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_ctanhl, libd_ctanh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_ctanhl, libc_ctanhl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_casinhl, libd_casinh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_casinhl, libc_casinhl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_cacoshl, libd_cacosh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_cacoshl, libc_cacoshl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_catanhl, libd_catanh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_catanhl, libc_catanhl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_cargl, libd_carg);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_cargl, libc_cargl, TFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_conjl, libd_conj);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_conjl, libc_conjl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_creall, libd_creal);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_creall, libc_creall, TFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_cimagl, libd_cimag);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_cimagl, libc_cimagl, TFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_cprojl, libd_cproj);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.complex", libd_cprojl, libc_cprojl, TCFL, 1, TCFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */

/* conio */
DFUN(".text.crt.dos.conio", libd__putch, libc__putch, TD, 1, TD)
DFUN(".text.crt.dos.conio", libd__putch_nolock, libc__putch_nolock, TD, 1, TD)
DFUN(".text.crt.dos.conio", libd__ungetch, libc__ungetch, TD, 1, TD)
DFUN(".text.crt.dos.conio", libd__ungetch_nolock, libc__ungetch_nolock, TD, 1, TD)
DFUN(".text.crt.dos.conio", libd__cgets, libc__cgets, TP, 1, TP)
DFUN(".text.crt.dos.conio", libd__cgets_s, libc__cgets_s, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
DFUN(".text.crt.dos.conio", libd__cputs, libc__cputs, TD, 1, TP)
DFUN(".text.crt.dos.conio", libd___conio_common_vcprintf, libc___conio_common_vcprintf, TD, 4, TI64, TP, TP, TP)
DFUN(".text.crt.dos.conio", libd___conio_common_vcprintf_s, libc___conio_common_vcprintf_s, TD, 4, TI64, TP, TP, TP)
DEFINE_INTERN_ALIAS(libd___conio_common_vcprintf_p, libd___conio_common_vcprintf);
DFUN(".text.crt.dos.conio", libd___conio_common_vcscanf, libc___conio_common_vcscanf, TD, 4, TI64, TP, TP, TP)
DFUN(".text.crt.dos.conio", libd__vcprintf_l, libc__vcprintf_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.conio", libd__vcprintf_s_l, libc__vcprintf_s_l, TD, 3, TP, TP, TP)
DEFINE_INTERN_ALIAS(libd__vcprintf_p_l, libd__vcprintf_l);
DFUN(".text.crt.dos.conio", libd__vcscanf_l, libc__vcscanf_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.conio", libd__vcscanf_s_l, libc__vcscanf_s_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.conio", libd__vcprintf, libc__vcprintf, TD, 2, TP, TP)
DFUN(".text.crt.dos.conio", libd__vcprintf_s, libc__vcprintf_s, TD, 2, TP, TP)
DEFINE_INTERN_ALIAS(libd__vcprintf_p, libd__vcprintf);
DFUN(".text.crt.dos.conio", libd__vcscanf, libc__vcscanf, TD, 2, TP, TP)
DFUN(".text.crt.dos.conio", libd__vcscanf_s, libc__vcscanf_s, TD, 2, TP, TP)
DFUN(".text.crt.dos.conio", libd_gotoxy, libc_gotoxy, TV, 2, TD, TD)
DFUN(".text.crt.dos.conio", libd_textcolor, libc_textcolor, TV, 1, TD)
DFUN(".text.crt.dos.conio", libd_textbackground, libc_textbackground, TV, 1, TD)
DFUN(".text.crt.dos.conio", libd_textattr, libc_textattr, TV, 1, TD)
DFUN(".text.crt.dos.conio", libd__conio_getpass, libc__conio_getpass, TP, 2, TP, TP)
DFUN(".text.crt.dos.conio", libd_cputsxy, libc_cputsxy, TV, 3, TD, TD, TP)
DFUN(".text.crt.dos.conio", libd_putchxy, libc_putchxy, TV, 3, TD, TD, THH)
DFUN(".text.crt.dos.conio", libd_window, libc_window, TV, 4, TD, TD, TD, TD)
DFUN(".text.crt.dos.conio", libd_movetext, libc_movetext, TD, 6, TD, TD, TD, TD, TD, TD)

/* corecrt_malloc */
DFUN(".text.crt.dos.heap", libd__aligned_malloc, libc__aligned_malloc, TP, 2, TI, TI)
DFUN(".text.crt.dos.heap", libd__aligned_offset_malloc, libc__aligned_offset_malloc, TP, 3, TI, TI, TI)
DFUN(".text.crt.dos.heap", libd__aligned_realloc, libc__aligned_realloc, TP, 3, TP, TI, TI)
DFUN(".text.crt.dos.heap", libd__aligned_recalloc, libc__aligned_recalloc, TP, 4, TP, TI, TI, TI)
DFUN(".text.crt.dos.heap", libd__aligned_offset_realloc, libc__aligned_offset_realloc, TP, 4, TP, TI, TI, TI)
DFUN(".text.crt.dos.heap", libd__aligned_offset_recalloc, libc__aligned_offset_recalloc, TP, 5, TP, TI, TI, TI, TI)
DFUN(".text.crt.dos.heap", libd__aligned_msize, libc__aligned_msize, TI, 3, TP, TI, TI)
DFUN(".text.crt.dos.heap", libd__aligned_free, libc__aligned_free, TV, 1, TP)

/* crypt */
DFUN(".text.crt.dos.string.encrypt", libd_setkey, libc_setkey, TV, 1, TP)
DFUN(".text.crt.dos.string.encrypt", libd_crypt, libc_crypt, TP, 2, TP, TP)
DFUN(".text.crt.dos.string.encrypt", libd_encrypt, libc_encrypt, TV, 2, TP, TD)
DFUN(".text.crt.dos.string.encrypt", libd_crypt_r, libc_crypt_r, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.string.encrypt", libd_setkey_r, libc_setkey_r, TV, 2, TP, TP)
DFUN(".text.crt.dos.string.encrypt", libd_encrypt_r, libc_encrypt_r, TV, 3, TP, TD, TP)

/* ctype */
DFUN(".text.crt.dos.compat.glibc.ctype", libd___locale_ctype_ptr_l, libc___locale_ctype_ptr_l, TP, 1, TP)
DFUN(".text.crt.dos.unicode.static.ctype", libd_iscntrl, libc_iscntrl, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_isspace, libc_isspace, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_isupper, libc_isupper, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_islower, libc_islower, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_isalpha, libc_isalpha, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_isdigit, libc_isdigit, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_isxdigit, libc_isxdigit, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_isalnum, libc_isalnum, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_ispunct, libc_ispunct, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_isgraph, libc_isgraph, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_isprint, libc_isprint, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_tolower, libc_tolower, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_toupper, libc_toupper, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_isblank, libc_isblank, TD, 1, TD)
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_iscntrl_l, libd_iscntrl);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_iscntrl_l, libc_iscntrl_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_isspace_l, libd_isspace);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_isspace_l, libc_isspace_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_isupper_l, libd_isupper);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_isupper_l, libc_isupper_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_islower_l, libd_islower);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_islower_l, libc_islower_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_isalpha_l, libd_isalpha);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_isalpha_l, libc_isalpha_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_isdigit_l, libd_isdigit);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_isdigit_l, libc_isdigit_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_isxdigit_l, libd_isxdigit);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_isxdigit_l, libc_isxdigit_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_isalnum_l, libd_isalnum);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_isalnum_l, libc_isalnum_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_ispunct_l, libd_ispunct);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_ispunct_l, libc_ispunct_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_isgraph_l, libd_isgraph);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_isgraph_l, libc_isgraph_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_isprint_l, libd_isprint);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_isprint_l, libc_isprint_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_isblank_l, libd_isblank);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_isblank_l, libc_isblank_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_tolower_l, libd_tolower);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_tolower_l, libc_tolower_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_toupper_l, libd_toupper);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd_toupper_l, libc_toupper_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.static.ctype", libd___iscsymf, libc___iscsymf, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd___iscsym, libc___iscsym, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_isascii, libc_isascii, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd_toascii, libc_toascii, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd__tolower, libc__tolower, TD, 1, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd__toupper, libc__toupper, TD, 1, TD)
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd____mb_cur_max_l_func, libd___ctype_get_mb_cur_max);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.static.ctype", libd____mb_cur_max_l_func, libc____mb_cur_max_l_func, TD, 1, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.static.ctype", libd__chvalidator_l, libc__chvalidator_l, TD, 3, TP, TD, TD)
DFUN(".text.crt.dos.unicode.static.ctype", libd__isctype, libc__isctype, TD, 2, TD, TD)
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd__isctype_l, libd__isctype);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.unicode.locale.ctype", libd__isctype_l, libc__isctype_l, TD, 3, TD, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */

/* direct */
DFUN(".text.crt.dos.fs.property", libd__chdrive, libc__chdrive, TD, 1, TD)
DFUN(".text.crt.dos.fs.property", libd__getdiskfree, libc__getdiskfree, TD, 2, TD, TP)

/* dirent */
DFUN(".text.crt.dos.fs.dir", libd_closedir, libc_closedir, TD, 1, TP)
DFUN(".text.crt.dos.fs.dir", libd_fdclosedir, libc_fdclosedir, TIn(__SIZEOF_FD_T__), 1, TP)
DFUN(".text.crt.dos.fs.dir", libd_readdirk, libc_readdirk, TP, 1, TP)
DFUN(".text.crt.dos.fs.dir", libd_rewinddir, libc_rewinddir, TV, 1, TP)
DFUN(".text.crt.dos.fs.dir", libd_fdopendir, libc_fdopendir, TP, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.fs.dir", libd_readdirk64, libc_readdirk64, TP, 1, TP)
DFUN(".text.crt.dos.fs.dir", libd_readdirk_r, libc_readdirk_r, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.fs.dir", libd_readdirk64_r, libc_readdirk64_r, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.fs.dir", libd_seekdir, libc_seekdir, TV, 2, TP, TP)
DFUN(".text.crt.dos.fs.dir", libd_telldir, libc_telldir, TP, 1, TP)
DFUN(".text.crt.dos.fs.dir", libd_dirfd, libc_dirfd, TIn(__SIZEOF_FD_T__), 1, TP)
DFUN(".text.crt.dos.fs.dir", libd_alphasortk, libc_alphasortk, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.dir", libd_alphasortk64, libc_alphasortk64, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.dir", libd_getdirentries, libc_getdirentries, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TP)
DFUN(".text.crt.dos.fs.dir", libd_getdirentries64, libc_getdirentries64, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TP)
DFUN(".text.crt.dos.fs.dir", libd_versionsortk, libc_versionsortk, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.dir", libd_versionsortk64, libc_versionsortk64, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.dir", libd_kreaddir, libc_kreaddir, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TD)
DFUN(".text.crt.dos.fs.dir", libd_kreaddirf, libc_kreaddirf, TI, 5, TIn(__SIZEOF_FD_T__), TP, TI, TD, TIn(__SIZEOF_OFLAG_T__))
DFUN(".text.crt.dos.fs.dir", libd_kreaddir64, libc_kreaddir64, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TD)
DFUN(".text.crt.dos.fs.dir", libd_kreaddirf64, libc_kreaddirf64, TI, 5, TIn(__SIZEOF_FD_T__), TP, TI, TD, TIn(__SIZEOF_OFLAG_T__))

/* dyn-string */
DFUN(".text.crt.dos.libiberty", libd_dyn_string_init, libc_dyn_string_init, TD, 2, TP, TD)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_new, libc_dyn_string_new, TP, 1, TD)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_delete, libc_dyn_string_delete, TV, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_release, libc_dyn_string_release, TP, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_resize, libc_dyn_string_resize, TP, 2, TP, TD)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_clear, libc_dyn_string_clear, TV, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_copy, libc_dyn_string_copy, TD, 2, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_copy_cstr, libc_dyn_string_copy_cstr, TD, 2, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_prepend, libc_dyn_string_prepend, TD, 2, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_prepend_cstr, libc_dyn_string_prepend_cstr, TD, 2, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_insert, libc_dyn_string_insert, TD, 3, TP, TD, TP)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_insert_cstr, libc_dyn_string_insert_cstr, TD, 3, TP, TD, TP)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_insert_char, libc_dyn_string_insert_char, TD, 3, TP, TD, TD)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_append, libc_dyn_string_append, TD, 2, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_append_cstr, libc_dyn_string_append_cstr, TD, 2, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_append_char, libc_dyn_string_append_char, TD, 2, TP, TD)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_substring, libc_dyn_string_substring, TD, 4, TP, TP, TD, TD)
DFUN(".text.crt.dos.libiberty", libd_dyn_string_eq, libc_dyn_string_eq, TD, 2, TP, TP)

/* envz */
DFUN(".text.crt.dos.string.envz", libd_envz_entry, libc_envz_entry, TP, 3, TP, TI, TP)
DFUN(".text.crt.dos.string.envz", libd_envz_get, libc_envz_get, TP, 3, TP, TI, TP)
DFUN(".text.crt.dos.string.envz", libd_envz_add, libc_envz_add, TIn(__SIZEOF_ERRNO_T__), 4, TP, TP, TP, TP)
DFUN(".text.crt.dos.string.envz", libd_envz_merge, libc_envz_merge, TIn(__SIZEOF_ERRNO_T__), 5, TP, TP, TP, TI, TD)
DFUN(".text.crt.dos.string.envz", libd_envz_remove, libc_envz_remove, TV, 3, TP, TP, TP)
DFUN(".text.crt.dos.string.envz", libd_envz_strip, libc_envz_strip, TV, 2, TP, TP)

/* err */
DFUN(".text.crt.dos.error", libd_vwarn, libc_vwarn, TV, 2, TP, TP)
DFUN(".text.crt.dos.error", libd_vwarnc, libc_vwarnc, TV, 3, TIn(__SIZEOF_ERRNO_T__), TP, TP)
DFUN(".text.crt.dos.error", libd_vwarnx, libc_vwarnx, TV, 2, TP, TP)
DFUN(".text.crt.dos.error", libd_verr, libc_verr, TV, 3, TD, TP, TP)
DFUN(".text.crt.dos.error", libd_verrc, libc_verrc, TV, 4, TD, TIn(__SIZEOF_ERRNO_T__), TP, TP)
DFUN(".text.crt.dos.error", libd_verrx, libc_verrx, TV, 3, TD, TP, TP)

/* execinfo */
DFUN(".text.crt.dos.debug", libd_backtrace, libc_backtrace, TD, 2, TP, TD)
DFUN(".text.crt.dos.debug", libd_backtrace_symbols, libc_backtrace_symbols, TP, 2, TP, TD)
DFUN(".text.crt.dos.debug", libd_backtrace_symbols_fd, libc_backtrace_symbols_fd, TD, 3, TP, TD, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.debug", libd_backtrace_symbols_fmt, libc_backtrace_symbols_fmt, TP, 3, TP, TD, TP)
DFUN(".text.crt.dos.debug", libd_backtrace_symbols_fd_fmt, libc_backtrace_symbols_fd_fmt, TD, 4, TP, TD, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.debug", libd_backtrace_symbol_printf, libc_backtrace_symbol_printf, TI, 4, TP, TP, TP, TP)

/* fcntl */
DFUN(".text.crt.dos.io.utility", libd_readahead, libc_readahead, TI, 3, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFF64_T__), TI)
DFUN(".text.crt.dos.io.utility", libd_sync_file_range, libc_sync_file_range, TD, 4, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFF64_T__), TIn(__SIZEOF_OFF64_T__), TD)
DFUN(".text.crt.dos.io.utility", libd_vmsplice, libc_vmsplice, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TD)
DFUN(".text.crt.dos.io.utility", libd_splice, libc_splice, TI, 6, TIn(__SIZEOF_FD_T__), TP, TIn(__SIZEOF_FD_T__), TP, TI, TD)
DFUN(".text.crt.dos.io.utility", libd_tee, libc_tee, TI, 4, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_FD_T__), TI, TD)
DFUN(".text.crt.dos.io.utility", libd_name_to_handle_at, libc_name_to_handle_at, TD, 5, TIn(__SIZEOF_FD_T__), TP, TP, TP, TD)
DFUN(".text.crt.dos.io.utility", libd_open_by_handle_at, libc_open_by_handle_at, TIn(__SIZEOF_FD_T__), 3, TIn(__SIZEOF_FD_T__), TP, TD)
DFUN(".text.crt.dos.io.utility", libd_fallocate, libc_fallocate, TD, 4, TIn(__SIZEOF_FD_T__), TD, TIn(__SIZEOF_OFF32_T__), TIn(__SIZEOF_OFF32_T__))
DFUN(".text.crt.dos.io.utility", libd_fallocate64, libc_fallocate64, TD, 4, TIn(__SIZEOF_FD_T__), TD, TIn(__SIZEOF_OFF64_T__), TIn(__SIZEOF_OFF64_T__))
DFUN(".text.crt.dos.io.utility", libd_fcntl, libc_fcntl, TD, 3, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_FCNTL_T__), TP)
DFUN(".text.crt.dos.io.utility", libd_posix_fadvise, libc_posix_fadvise, TD, 4, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFF32_T__), TIn(__SIZEOF_OFF32_T__), TD)
DFUN(".text.crt.dos.io.utility", libd_posix_fallocate, libc_posix_fallocate, TD, 3, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFF32_T__), TIn(__SIZEOF_OFF32_T__))
DFUN(".text.crt.dos.io.large.utility", libd_posix_fadvise64, libc_posix_fadvise64, TD, 4, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFF64_T__), TIn(__SIZEOF_OFF64_T__), TD)
DFUN(".text.crt.dos.io.large.utility", libd_posix_fallocate64, libc_posix_fallocate64, TD, 3, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFF64_T__), TIn(__SIZEOF_OFF64_T__))
DFUN(".text.crt.dos.io.lock", libd_lockf, libc_lockf, TD, 3, TIn(__SIZEOF_FD_T__), TD, TIn(__SIZEOF_OFF32_T__))
DFUN(".text.crt.dos.io.large.lock", libd_lockf64, libc_lockf64, TD, 3, TIn(__SIZEOF_FD_T__), TD, TIn(__SIZEOF_OFF64_T__))
DFUN(".text.crt.dos.solaris.io", libd_directio, libc_directio, TD, 2, TIn(__SIZEOF_FD_T__), TD)

/* fenv */
DFUN(".text.crt.dos.math.fenv", libd_feraiseexcept, libc_feraiseexcept, TD, 1, TD)
DFUN(".text.crt.dos.math.fenv", libd_feclearexcept, libc_feclearexcept, TD, 1, TD)
DFUN(".text.crt.dos.math.fenv", libd_fegetexceptflag, libc_fegetexceptflag, TD, 2, TP, TD)
DFUN(".text.crt.dos.math.fenv", libd_fesetexceptflag, libc_fesetexceptflag, TD, 2, TP, TD)
DFUN(".text.crt.dos.math.fenv", libd_fetestexcept, libc_fetestexcept, TD, 1, TD)
DFUN(".text.crt.dos.math.fenv", libd_fesetround, libc_fesetround, TD, 1, TD)
DFUN(".text.crt.dos.math.fenv", libd_fegetenv, libc_fegetenv, TD, 1, TP)
DFUN(".text.crt.dos.math.fenv", libd_feholdexcept, libc_feholdexcept, TD, 1, TP)
DFUN(".text.crt.dos.math.fenv", libd_fesetenv, libc_fesetenv, TD, 1, TP)
DFUN(".text.crt.dos.math.fenv", libd_feupdateenv, libc_feupdateenv, TD, 1, TP)
DFUN(".text.crt.dos.math.fenv", libd_feenableexcept, libc_feenableexcept, TD, 1, TD)
DFUN(".text.crt.dos.math.fenv", libd_fedisableexcept, libc_fedisableexcept, TD, 1, TD)
DFUN(".text.crt.dos.math.fenv", libd_fesetexcept, libc_fesetexcept, TD, 1, TD)
DFUN(".text.crt.dos.math.fenv", libd_fetestexceptflag, libc_fetestexceptflag, TD, 2, TP, TD)
DFUN(".text.crt.dos.math.fenv", libd_fegetmode, libc_fegetmode, TD, 1, TP)
DFUN(".text.crt.dos.math.fenv", libd_fesetmode, libc_fesetmode, TD, 1, TP)

/* float */
DFUN(".text.crt.dos.math.float", libd__controlfp, libc__controlfp, TI32, 2, TI32, TI32)
DFUN(".text.crt.dos.math.float", libd__set_controlfp, libc__set_controlfp, TV, 2, TI32, TI32)
DFUN(".text.crt.dos.math.float", libd__controlfp_s, libc__controlfp_s, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI32, TI32)
DFUN(".text.crt.dos.math.float", libd__statusfp2, libc__statusfp2, TV, 2, TP, TP)
DFUN(".text.crt.dos.math.float", libd__control87, libc__control87, TI32, 2, TI32, TI32)
DFUN(".text.crt.dos.math.float", libd___control87_2, libc___control87_2, TD, 4, TI32, TI32, TP, TP)
DFUN(".text.crt.dos.math.float", libd__fpclass, libc__fpclass, TD, 1, TFD)
DFUN(".text.crt.dos.math.float", libd__fpclassf, libc__fpclassf, TD, 1, TF)

/* fmtmsg */
DFUN(".text.crt.dos.fmtmsg", libd_fmtmsg, libc_fmtmsg, TD, 6, TL, TP, TD, TP, TP, TP)
DFUN(".text.crt.dos.fmtmsg", libd_addseverity, libc_addseverity, TD, 2, TD, TP)

/* fnmatch */
DFUN(".text.crt.dos.string.match", libd_fnmatch, libc_fnmatch, TD, 3, TP, TP, TD)

/* format-printer */
DFUN(".text.crt.dos.string.format", libd_format_repeat, libc_format_repeat, TI, 4, TP, TP, THH, TI)
DFUN(".text.crt.dos.string.format", libd_format_escape, libc_format_escape, TI, 5, TP, TP, TP, TI, TD)
DFUN(".text.crt.dos.string.format", libd_format_hexdump, libc_format_hexdump, TI, 6, TP, TP, TP, TI, TI, TD)
DFUN(".text.crt.dos.string.format", libd_format_vprintf, libc_format_vprintf, TI, 4, TP, TP, TP, TP)
DFUN(".text.crt.dos.string.format", libd_format_vscanf, libc_format_vscanf, TI, 5, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.string.format", libd_format_aprintf_pack, libc_format_aprintf_pack, TP, 2, TP, TP)
DFUN(".text.crt.dos.string.format", libd_format_aprintf_alloc, libc_format_aprintf_alloc, TP, 2, TP, TI)

/* fstab */
DFUN(".text.crt.dos.database.fstab", libd_getfsspec, libc_getfsspec, TP, 1, TP)
DFUN(".text.crt.dos.database.fstab", libd_getfsfile, libc_getfsfile, TP, 1, TP)

/* fts */
DFUN(".text.crt.dos.fs.fts", libd_fts_children, libc_fts_children, TP, 2, TP, TD)
DFUN(".text.crt.dos.fs.fts", libd_fts_close, libc_fts_close, TD, 1, TP)
DFUN(".text.crt.dos.fs.fts", libd_fts_read, libc_fts_read, TP, 1, TP)
DFUN(".text.crt.dos.fs.fts", libd_fts_set, libc_fts_set, TD, 3, TP, TP, TD)
DFUN(".text.crt.dos.fs.fts", libd_fts64_children, libc_fts64_children, TP, 2, TP, TD)
DFUN(".text.crt.dos.fs.fts", libd_fts64_close, libc_fts64_close, TD, 1, TP)
DFUN(".text.crt.dos.fs.fts", libd_fts64_read, libc_fts64_read, TP, 1, TP)
DFUN(".text.crt.dos.fs.fts", libd_fts64_set, libc_fts64_set, TD, 3, TP, TP, TD)

/* getopt */
DFUN(".text.crt.dos.application.getopt", libd_getopt, libc_getopt, TD, 3, TD, TP, TP)
DFUN(".text.crt.dos.application.getopt", libd___posix_getopt, libc___posix_getopt, TD, 3, TD, TP, TP)
DFUN(".text.crt.dos.application.getopt", libd_getopt_long, libc_getopt_long, TD, 5, TD, TP, TP, TP, TP)
DFUN(".text.crt.dos.application.getopt", libd_getopt_long_only, libc_getopt_long_only, TD, 5, TD, TP, TP, TP, TP)

/* grp */
DFUN(".text.crt.dos.database.grp", libd_getgrgid, libc_getgrgid, TP, 1, TIn(__SIZEOF_GID_T__))
DFUN(".text.crt.dos.database.grp", libd_getgrnam, libc_getgrnam, TP, 1, TP)
DFUN(".text.crt.dos.database.grp", libd_putgrent, libc_putgrent, TD, 2, TP, TP)
DFUN(".text.crt.dos.database.grp", libd_getgrgid_r, libc_getgrgid_r, TD, 5, TIn(__SIZEOF_GID_T__), TP, TP, TI, TP)
DFUN(".text.crt.dos.database.grp", libd_getgrnam_r, libc_getgrnam_r, TD, 5, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.database.grp", libd_getgrent_r, libc_getgrent_r, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.database.grp", libd_fgetgrent_r, libc_fgetgrent_r, TD, 5, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.database.grp", libd_fgetgrgid_r, libc_fgetgrgid_r, TIn(__SIZEOF_ERRNO_T__), 6, TP, TIn(__SIZEOF_GID_T__), TP, TP, TI, TP)
DFUN(".text.crt.dos.database.grp", libd_fgetgrnam_r, libc_fgetgrnam_r, TIn(__SIZEOF_ERRNO_T__), 6, TP, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.database.grp", libd_fgetgrent, libc_fgetgrent, TP, 1, TP)
DFUN(".text.crt.dos.database.grp", libd_setgroups, libc_setgroups, TD, 2, TI, TP)
DFUN(".text.crt.dos.database.grp", libd_getgrouplist, libc_getgrouplist, TD, 4, TP, TIn(__SIZEOF_GID_T__), TP, TP)
DFUN(".text.crt.dos.database.grp", libd_initgroups, libc_initgroups, TD, 2, TP, TIn(__SIZEOF_GID_T__))
DFUN(".text.crt.dos.database.grp", libd_setgroupent, libc_setgroupent, TD, 1, TD)
DFUN(".text.crt.dos.database.grp", libd_gid_from_group, libc_gid_from_group, TD, 2, TP, TP)
DFUN(".text.crt.dos.database.grp", libd_group_from_gid, libc_group_from_gid, TP, 2, TIn(__SIZEOF_GID_T__), TD)

/* ifaddrs */
DFUN(".text.crt.dos.unsorted", libd_getifaddrs, libc_getifaddrs, TD, 1, TP)
DFUN(".text.crt.dos.unsorted", libd_freeifaddrs, libc_freeifaddrs, TV, 1, TP)

/* inttypes */
#if __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ && __SIZEOF_INTMAX_T__ != 8
DFUN(".text.crt.dos.math.utility", libd_imaxabs, libc_imaxabs, TIn(__SIZEOF_INTMAX_T__), 1, TIn(__SIZEOF_INTMAX_T__))
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ && __SIZEOF_INTMAX_T__ != 8 */
#if __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__
DFUN(".text.crt.dos.math.utility", libd_imaxdiv, libc_imaxdiv, TS(__SIZEOF_IMAXDIV_STRUCT), 2, TIn(__SIZEOF_INTMAX_T__), TIn(__SIZEOF_INTMAX_T__))
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ */
#if __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ && __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8
DFUN(".text.crt.dos.unicode.static.convert", libd_strtoimax, libc_strtoimax, TIn(__SIZEOF_INTMAX_T__), 3, TP, TP, TD)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtoumax, libc_strtoumax, TIn(__SIZEOF_INTMAX_T__), 3, TP, TP, TD)
DFUN(".text.crt.dos.unicode.locale.convert", libd_strtoimax_l, libc_strtoimax_l, TIn(__SIZEOF_INTMAX_T__), 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.unicode.locale.convert", libd_strtoumax_l, libc_strtoumax_l, TIn(__SIZEOF_INTMAX_T__), 4, TP, TP, TD, TP)
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ && __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 */
DFUN(".text.crt.dos.unicode.static.convert", libd_strtoi, libc_strtoi, TIn(__SIZEOF_INTMAX_T__), 6, TP, TP, TD, TIn(__SIZEOF_INTMAX_T__), TIn(__SIZEOF_INTMAX_T__), TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtou, libc_strtou, TIn(__SIZEOF_INTMAX_T__), 6, TP, TP, TD, TIn(__SIZEOF_INTMAX_T__), TIn(__SIZEOF_INTMAX_T__), TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtoi_l, libc_strtoi_l, TIn(__SIZEOF_INTMAX_T__), 7, TP, TP, TD, TIn(__SIZEOF_INTMAX_T__), TIn(__SIZEOF_INTMAX_T__), TP, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtou_l, libc_strtou_l, TIn(__SIZEOF_INTMAX_T__), 7, TP, TP, TD, TIn(__SIZEOF_INTMAX_T__), TIn(__SIZEOF_INTMAX_T__), TP, TP)

/* io */
DFUN(".text.crt.dos.fs.property", libd__umask_s, libc__umask_s, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_MODE_T__), TP)
DFUN(".text.crt.dos.unsorted", libd__setmode, libc__setmode, TIn(__SIZEOF_OFLAG_T__), 2, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFLAG_T__))
DFUN(".text.crt.dos.fs.dir", libd__findclose, libc__findclose, TD, 1, TP)
DFUN(".text.crt.dos.fs.dir", libd__findnext32, libc__findnext32, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.dir", libd__findnext32i64, libc__findnext32i64, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.dir", libd__findnext64, libc__findnext64, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.utility", libd__mktemp_s, libc__mktemp_s, TIn(__SIZEOF_ERRNO_T__), 2, TP, TI)
DFUN(".text.crt.dos.fs.io", libd__pipe, libc__pipe, TD, 3, TP, TI32, TIn(__SIZEOF_OFLAG_T__))
DFUN(".text.crt.dos.fs.utility", libd__filelengthi64, libc__filelengthi64, TI64, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.fs.utility", libd___lock_fhandle, libc___lock_fhandle, TD, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.fs.utility", libd__unlock_fhandle, libc__unlock_fhandle, TV, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.fs.utility", libd__get_osfhandle, libc__get_osfhandle, TP, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.fs.utility", libd__open_osfhandle, libc__open_osfhandle, TIn(__SIZEOF_FD_T__), 2, TP, TIn(__SIZEOF_OFLAG_T__))
DFUN(".text.crt.dos.fs.utility", libd__filelength, libc__filelength, TI32, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.fs.utility", libd__eof, libc__eof, TD, 1, TIn(__SIZEOF_FD_T__))

/* kos.dosfs */
DFUN(".text.crt.dos.io.access", libd_dosfs_setenabled, libc_dosfs_setenabled, TD, 1, TD)

/* kos.nopf */
#include <kos/bits/nopf.h>
#ifndef __arch_readb_nopf
DFUN(".text.crt.string.nopf", libd_readb_nopf, libc_readb_nopf, TD, 2, TP, TP)
#endif /* !__arch_readb_nopf */
#ifndef __arch_readw_nopf
DFUN(".text.crt.string.nopf", libd_readw_nopf, libc_readw_nopf, TD, 2, TP, TP)
#endif /* !__arch_readw_nopf */
#ifndef __arch_readl_nopf
DFUN(".text.crt.string.nopf", libd_readl_nopf, libc_readl_nopf, TD, 2, TP, TP)
#endif /* !__arch_readl_nopf */
#ifndef __arch_readq_nopf
DFUN(".text.crt.string.nopf", libd_readq_nopf, libc_readq_nopf, TD, 2, TP, TP)
#endif /* !__arch_readq_nopf */
#ifndef __arch_writeb_nopf
DFUN(".text.crt.string.nopf", libd_writeb_nopf, libc_writeb_nopf, TD, 2, TP, TI8)
#endif /* !__arch_writeb_nopf */
#ifndef __arch_writew_nopf
DFUN(".text.crt.string.nopf", libd_writew_nopf, libc_writew_nopf, TD, 2, TP, TI16)
#endif /* !__arch_writew_nopf */
#ifndef __arch_writel_nopf
DFUN(".text.crt.string.nopf", libd_writel_nopf, libc_writel_nopf, TD, 2, TP, TI32)
#endif /* !__arch_writel_nopf */
#ifndef __arch_writeq_nopf
DFUN(".text.crt.string.nopf", libd_writeq_nopf, libc_writeq_nopf, TD, 2, TP, TI64)
#endif /* !__arch_writeq_nopf */
#ifndef __arch_memcpy_nopf
DFUN(".text.crt.string.nopf", libd_memcpy_nopf, libc_memcpy_nopf, TI, 3, TP, TP, TI)
#endif /* !__arch_memcpy_nopf */
#ifndef __arch_memset_nopf
DFUN(".text.crt.string.nopf", libd_memset_nopf, libc_memset_nopf, TI, 3, TP, TD, TI)
#endif /* !__arch_memset_nopf */
#ifndef __arch_nopf_memeq
DFUN(".text.crt.string.nopf", libd_memeq_nopf, libc_memeq_nopf, TI, 3, TP, TP, TI)
#endif /* !__arch_nopf_memeq */

/* kos.rpc */
DFUN(".text.crt.dos.sched.rpc", libd_rpc_schedule, libc_rpc_schedule, TD, 5, TIn(__SIZEOF_PID_T__), TD, TP, TP, TI)
DFUN(".text.crt.dos.sched.rpc", libd_rpc_exec, libc_rpc_exec, TD, 4, TIn(__SIZEOF_PID_T__), TD, TP, TP)
DFUN(".text.crt.dos.sched.rpc", libd_rpc_interrupt, libc_rpc_interrupt, TD, 2, TIn(__SIZEOF_PID_T__), TD)
DFUN(".text.crt.dos.sched.rpc", libd_RpcSchedule, libc_RpcSchedule, TV, 5, TIn(__SIZEOF_PID_T__), TD, TP, TP, TI)
DFUN(".text.crt.dos.sched.rpc", libd_RpcExec, libc_RpcExec, TV, 4, TIn(__SIZEOF_PID_T__), TD, TP, TP)
DFUN(".text.crt.dos.sched.rpc", libd_RpcInterrupt, libc_RpcInterrupt, TV, 2, TIn(__SIZEOF_PID_T__), TD)

/* kos.uuid */
DFUN(".text.crt.dos.sched.rpc", libd_uuid_fromstr, libc_uuid_fromstr, TP, 2, TP, TP)

/* langinfo */
DFUN(".text.crt.dos.i18n", libd_nl_langinfo, libc_nl_langinfo, TP, 1, TD)
DFUN(".text.crt.dos.i18n", libd_nl_langinfo_l, libc_nl_langinfo_l, TP, 2, TD, TP)

/* libgen */
DFUN(".text.crt.dos.unsorted", libd_dirname, libc_dirname, TP, 1, TP)
DFUN(".text.crt.dos.unsorted", libd___xpg_basename, libc___xpg_basename, TP, 1, TP)
DFUN(".text.crt.dos.solaris", libd_bgets, libc_bgets, TP, 4, TP, TI, TP, TP)
DFUN(".text.crt.dos.solaris", libd_bufsplit, libc_bufsplit, TI, 3, TP, TI, TP)
DFUN(".text.crt.dos.solaris", libd_strcadd, libc_strcadd, TP, 2, TP, TP)
DFUN(".text.crt.dos.solaris", libd_strccpy, libc_strccpy, TP, 2, TP, TP)
DFUN(".text.crt.dos.solaris", libd_streadd, libc_streadd, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.solaris", libd_strecpy, libc_strecpy, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.solaris", libd_strfind, libc_strfind, TD, 2, TP, TP)
DFUN(".text.crt.dos.solaris", libd_strrspn, libc_strrspn, TP, 2, TP, TP)
DFUN(".text.crt.dos.solaris", libd_strtrns, libc_strtrns, TP, 4, TP, TP, TP, TP)

/* libiberty */
DFUN(".text.crt.dos.libiberty", libd_C_alloca, libc_C_alloca, TP, 1, TI)
DFUN(".text.crt.dos.libiberty", libd_stack_limit_increase, libc_stack_limit_increase, TV, 1, TP)
#ifndef _WIN32
DFUN(".text.crt.dos.libiberty", libd_dos_lbasename, libc_dos_lbasename, TP, 1, TP)
#endif /* !_WIN32 */
#ifdef _WIN32
DFUN(".text.crt.dos.libiberty", libd_unix_lbasename, libc_unix_lbasename, TP, 1, TP)
#endif /* _WIN32 */
DFUN(".text.crt.dos.libiberty", libd_lrealpath, libc_lrealpath, TP, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_strtoerrno, libc_strtoerrno, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.libiberty", libd_unlock_stream, libc_unlock_stream, TV, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_fopen_unlocked, libc_fopen_unlocked, TP, 2, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_fdopen_unlocked, libc_fdopen_unlocked, TP, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.libiberty", libd_spaces, libc_spaces, TP, 1, TD)
DFUN(".text.crt.dos.libiberty", libd_xmalloc_set_program_name, libc_xmalloc_set_program_name, TV, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_xmalloc_failed, libc_xmalloc_failed, TV, 1, TI)
DFUN(".text.crt.dos.libiberty", libd_xmalloc, libc_xmalloc, TP, 1, TI)
DFUN(".text.crt.dos.libiberty", libd_xrealloc, libc_xrealloc, TP, 2, TP, TI)
DFUN(".text.crt.dos.libiberty", libd_xcalloc, libc_xcalloc, TP, 2, TI, TI)
DFUN(".text.crt.dos.libiberty", libd_xstrdup, libc_xstrdup, TP, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_xstrndup, libc_xstrndup, TP, 2, TP, TI)
DFUN(".text.crt.dos.libiberty", libd_xmemdup, libc_xmemdup, TP, 3, TP, TI, TI)
DFUN(".text.crt.dos.libiberty", libd_xvasprintf, libc_xvasprintf, TP, 2, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_dupargv, libc_dupargv, TP, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_freeargv, libc_freeargv, TV, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_countargv, libc_countargv, TD, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_fdmatch, libc_fdmatch, TD, 2, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.libiberty", libd_buildargv, libc_buildargv, TP, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_expandargv, libc_expandargv, TV, 2, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_writeargv, libc_writeargv, TD, 2, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_make_relative_prefix, libc_make_relative_prefix, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_make_relative_prefix_ignore_links, libc_make_relative_prefix_ignore_links, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_make_temp_file_with_prefix, libc_make_temp_file_with_prefix, TP, 2, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_make_temp_file, libc_make_temp_file, TP, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_unlink_if_ordinary, libc_unlink_if_ordinary, TD, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_xcrc32, libc_xcrc32, TI32, 3, TP, TD, TI32)
DFUN(".text.crt.dos.libiberty", libd_pex_run, libc_pex_run, TP, 7, TP, TD, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_pex_run_in_environment, libc_pex_run_in_environment, TP, 8, TP, TD, TP, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_pex_input_file, libc_pex_input_file, TP, 3, TP, TD, TP)
DFUN(".text.crt.dos.libiberty", libd_pex_input_pipe, libc_pex_input_pipe, TP, 2, TP, TD)
DFUN(".text.crt.dos.libiberty", libd_pex_read_output, libc_pex_read_output, TP, 2, TP, TD)
DFUN(".text.crt.dos.libiberty", libd_pex_read_err, libc_pex_read_err, TP, 2, TP, TD)
DFUN(".text.crt.dos.libiberty", libd_pex_get_status, libc_pex_get_status, TD, 3, TP, TD, TP)
DFUN(".text.crt.dos.libiberty", libd_pex_init, libc_pex_init, TP, 3, TD, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_pex_get_times, libc_pex_get_times, TD, 3, TP, TD, TP)
DFUN(".text.crt.dos.libiberty", libd_pex_free, libc_pex_free, TV, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_pex_one, libc_pex_one, TP, 8, TD, TP, TP, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_pexecute, libc_pexecute, TD, 7, TP, TP, TP, TP, TP, TP, TD)
DFUN(".text.crt.dos.libiberty", libd_pwait, libc_pwait, TD, 3, TD, TP, TD)

/* libintl */
DFUN(".text.crt.dos.i18n", libd_dcgettext, libc_dcgettext, TP, 3, TP, TP, TD)
DFUN(".text.crt.dos.i18n", libd_dgettext, libc_dgettext, TP, 2, TP, TP)
DFUN(".text.crt.dos.i18n", libd_gettext, libc_gettext, TP, 1, TP)
DFUN(".text.crt.dos.i18n", libd_ngettext, libc_ngettext, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.i18n", libd_dngettext, libc_dngettext, TP, 4, TP, TP, TP, TP)
DFUN(".text.crt.dos.i18n", libd_dcngettext, libc_dcngettext, TP, 5, TP, TP, TP, TP, TD)
DFUN(".text.crt.dos.i18n", libd_textdomain, libc_textdomain, TP, 1, TP)
DFUN(".text.crt.dos.i18n", libd_bindtextdomain, libc_bindtextdomain, TP, 2, TP, TP)
DFUN(".text.crt.dos.i18n", libd_bind_textdomain_codeset, libc_bind_textdomain_codeset, TP, 2, TP, TP)

/* locale */
DFUN(".text.crt.dos.i18n", libd_setlocale, libc_setlocale, TP, 2, TD, TP)
DFUN(".text.crt.dos.i18n", libd_newlocale, libc_newlocale, TP, 3, TD, TP, TP)
DFUN(".text.crt.dos.i18n", libd_duplocale, libc_duplocale, TP, 1, TP)
DFUN(".text.crt.dos.i18n", libd_freelocale, libc_freelocale, TV, 1, TP)
DFUN(".text.crt.dos.i18n", libd_uselocale, libc_uselocale, TP, 1, TP)
DFUN(".text.crt.dos.i18n", libd__configthreadlocale, libc__configthreadlocale, TD, 1, TD)
DFUN(".text.crt.dos.i18n", libd__create_locale, libc__create_locale, TP, 2, TD, TP)
DFUN(".text.crt.dos.i18n", libd__free_locale, libc__free_locale, TV, 1, TP)
DFUN(".text.crt.dos.i18n", libd__Strftime, libc__Strftime, TI, 5, TP, TI, TP, TP, TP)

/* malloc */
DFUN(".text.crt.dos.heap.helpers", libd_realloc_in_place, libc_realloc_in_place, TP, 2, TP, TI)
DFUN(".text.crt.dos.heap.malloc", libd_memalign, libc_memalign, TP, 2, TI, TI)
DFUN(".text.crt.dos.heap.rare_helpers", libd_pvalloc, libc_pvalloc, TP, 1, TI)
DFUN(".text.crt.dos.heap.rare_helpers", libd_valloc, libc_valloc, TP, 1, TI)
DFUN(".text.crt.dos.heap.rare_helpers", libd_posix_memalign, libc_posix_memalign, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TI)
DFUN(".text.crt.dos.heap.utility", libd_malloc_trim, libc_malloc_trim, TD, 1, TI)
DFUN(".text.crt.dos.heap.helpers", libd_malloc_usable_size, libc_malloc_usable_size, TI, 1, TP)
DFUN(".text.crt.dos.heap.utility", libd_mallopt, libc_mallopt, TD, 2, TD, TD)
DFUN(".text.crt.dos.heap.rare_helpers", libd_memdup, libc_memdup, TP, 2, TP, TI)
DFUN(".text.crt.dos.heap.rare_helpers", libd_memcdup, libc_memcdup, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.heap.rare_helpers", libd_reallocarray, libc_reallocarray, TP, 3, TP, TI, TI)
DFUN(".text.crt.dos.heap.rare_helpers", libd_recalloc, libc_recalloc, TP, 2, TP, TI)
DFUN(".text.crt.dos.heap.rare_helpers", libd_recallocv, libc_recallocv, TP, 3, TP, TI, TI)

/* math */
DFUN(".text.crt.dos.math.math", libd_acos, libc_acos, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_asin, libc_asin, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_atan, libc_atan, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_atan2, libc_atan2, TFD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_cos, libc_cos, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_sin, libc_sin, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_tan, libc_tan, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_acosf, libc_acosf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_asinf, libc_asinf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_atanf, libc_atanf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_atan2f, libc_atan2f, TF, 2, TF, TF)
DFUN(".text.crt.dos.math.math", libd_cosf, libc_cosf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_sinf, libc_sinf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_tanf, libc_tanf, TF, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_acosl, libd_acos);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_acosl, libc_acosl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_asinl, libd_asin);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_asinl, libc_asinl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_atanl, libd_atan);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_atanl, libc_atanl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_atan2l, libd_atan2);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_atan2l, libc_atan2l, TFL, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_cosl, libd_cos);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_cosl, libc_cosl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_sinl, libd_sin);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_sinl, libc_sinl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_tanl, libd_tan);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_tanl, libc_tanl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_cosh, libc_cosh, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_sinh, libc_sinh, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_tanh, libc_tanh, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_coshf, libc_coshf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_sinhf, libc_sinhf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_tanhf, libc_tanhf, TF, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_coshl, libd_cosh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_coshl, libc_coshl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_sinhl, libd_sinh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_sinhl, libc_sinhl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_tanhl, libd_tanh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_tanhl, libc_tanhl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_acosh, libc_acosh, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_asinh, libc_asinh, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_atanh, libc_atanh, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_acoshf, libc_acoshf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_asinhf, libc_asinhf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_atanhf, libc_atanhf, TF, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_acoshl, libd_acosh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_acoshl, libc_acoshl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_asinhl, libd_asinh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_asinhl, libc_asinhl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_atanhl, libd_atanh);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_atanhl, libc_atanhl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_exp, libc_exp, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_frexp, libc_frexp, TFD, 2, TFD, TP)
DFUN(".text.crt.dos.math.math", libd_ldexp, libc_ldexp, TFD, 2, TFD, TD)
DFUN(".text.crt.dos.math.math", libd_log, libc_log, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_log10, libc_log10, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_modf, libc_modf, TFD, 2, TFD, TP)
DFUN(".text.crt.dos.math.math", libd_expf, libc_expf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_frexpf, libc_frexpf, TF, 2, TF, TP)
DFUN(".text.crt.dos.math.math", libd_ldexpf, libc_ldexpf, TF, 2, TF, TD)
DFUN(".text.crt.dos.math.math", libd_logf, libc_logf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_log10f, libc_log10f, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_modff, libc_modff, TF, 2, TF, TP)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_expl, libd_exp);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_expl, libc_expl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_frexpl, libd_frexp);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_frexpl, libc_frexpl, TFL, 2, TFL, TP)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_ldexpl, libd_ldexp);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_ldexpl, libc_ldexpl, TFL, 2, TFL, TD)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_logl, libd_log);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_logl, libc_logl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_log10l, libd_log10);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_log10l, libc_log10l, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_modfl, libd_modf);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_modfl, libc_modfl, TFL, 2, TFL, TP)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_expm1, libc_expm1, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_log1p, libc_log1p, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_logb, libc_logb, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_expm1f, libc_expm1f, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_log1pf, libc_log1pf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_logbf, libc_logbf, TF, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_expm1l, libd_expm1);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_expm1l, libc_expm1l, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_log1pl, libd_log1p);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_log1pl, libc_log1pl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_logbl, libd_logb);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_logbl, libc_logbl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_exp2, libc_exp2, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_log2, libc_log2, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_exp2f, libc_exp2f, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_log2f, libc_log2f, TF, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_exp2l, libd_exp2);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_exp2l, libc_exp2l, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_log2l, libd_log2);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_log2l, libc_log2l, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_pow, libc_pow, TFD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_sqrt, libc_sqrt, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_powf, libc_powf, TF, 2, TF, TF)
DFUN(".text.crt.dos.math.math", libd_sqrtf, libc_sqrtf, TF, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_powl, libd_pow);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_powl, libc_powl, TFL, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_sqrtl, libd_sqrt);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_sqrtl, libc_sqrtl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_hypot, libc_hypot, TFD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_hypotf, libc_hypotf, TF, 2, TF, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_hypotl, libd_hypot);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_hypotl, libc_hypotl, TFL, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_cbrt, libc_cbrt, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_cbrtf, libc_cbrtf, TF, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_cbrtl, libd_cbrt);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_cbrtl, libc_cbrtl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_ceil, libc_ceil, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_fabs, libc_fabs, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_floor, libc_floor, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_fmod, libc_fmod, TFD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_ceilf, libc_ceilf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_fabsf, libc_fabsf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_floorf, libc_floorf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_fmodf, libc_fmodf, TF, 2, TF, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_ceill, libd_ceil);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_ceill, libc_ceill, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_fabsl, libd_fabs);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_fabsl, libc_fabsl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_floorl, libd_floor);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_floorl, libc_floorl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_fmodl, libd_fmod);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_fmodl, libc_fmodl, TFL, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_copysign, libc_copysign, TFD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_nan, libc_nan, TFD, 1, TP)
DFUN(".text.crt.dos.math.math", libd_copysignf, libc_copysignf, TF, 2, TF, TF)
DFUN(".text.crt.dos.math.math", libd_nanf, libc_nanf, TF, 1, TP)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_copysignl, libd_copysign);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_copysignl, libc_copysignl, TFL, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_nanl, libd_nan);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_nanl, libc_nanl, TFL, 1, TP)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_erf, libc_erf, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_erfc, libc_erfc, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_lgamma, libc_lgamma, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_erff, libc_erff, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_erfcf, libc_erfcf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_lgammaf, libc_lgammaf, TF, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_erfl, libd_erf);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_erfl, libc_erfl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_erfcl, libd_erfc);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_erfcl, libc_erfcl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_lgammal, libc_lgammal, TFL, 1, TFL)
DFUN(".text.crt.dos.math.math", libd_tgamma, libc_tgamma, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_tgammaf, libc_tgammaf, TF, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_tgammal, libd_tgamma);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_tgammal, libc_tgammal, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_rint, libc_rint, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_nextafter, libc_nextafter, TFD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_remainder, libc_remainder, TFD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_ilogb, libc_ilogb, TD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_rintf, libc_rintf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_nextafterf, libc_nextafterf, TF, 2, TF, TF)
DFUN(".text.crt.dos.math.math", libd_remainderf, libc_remainderf, TF, 2, TF, TF)
DFUN(".text.crt.dos.math.math", libd_ilogbf, libc_ilogbf, TD, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_rintl, libd_rint);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_rintl, libc_rintl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_nextafterl, libd_nextafter);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_nextafterl, libc_nextafterl, TFL, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_remainderl, libd_remainder);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_remainderl, libc_remainderl, TFL, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_ilogbl, libd_ilogb);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_ilogbl, libc_ilogbl, TD, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_nexttoward, libd_nextafter);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_nexttoward, libc_nexttoward, TFD, 2, TFD, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_scalbn, libc_scalbn, TFD, 2, TFD, TD)
DFUN(".text.crt.dos.math.math", libd_scalbln, libc_scalbln, TFD, 2, TFD, TL)
DFUN(".text.crt.dos.math.math", libd_round, libc_round, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_trunc, libc_trunc, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_remquo, libc_remquo, TFD, 3, TFD, TFD, TP)
DFUN(".text.crt.dos.math.math", libd_lrint, libc_lrint, TL, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_lround, libc_lround, TL, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_fdim, libc_fdim, TFD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_fmax, libc_fmax, TFD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_fmin, libc_fmin, TFD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_fma, libc_fma, TFD, 3, TFD, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_llrint, libc_llrint, TLL, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_llround, libc_llround, TLL, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_nexttowardf, libc_nexttowardf, TF, 2, TF, TFL)
DFUN(".text.crt.dos.math.math", libd_scalbnf, libc_scalbnf, TF, 2, TF, TD)
DFUN(".text.crt.dos.math.math", libd_scalblnf, libc_scalblnf, TF, 2, TF, TL)
DFUN(".text.crt.dos.math.math", libd_roundf, libc_roundf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_truncf, libc_truncf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_remquof, libc_remquof, TF, 3, TF, TF, TP)
DFUN(".text.crt.dos.math.math", libd_lrintf, libc_lrintf, TL, 1, TF)
DFUN(".text.crt.dos.math.math", libd_lroundf, libc_lroundf, TL, 1, TF)
DFUN(".text.crt.dos.math.math", libd_fdimf, libc_fdimf, TF, 2, TF, TF)
DFUN(".text.crt.dos.math.math", libd_fmaxf, libc_fmaxf, TF, 2, TF, TF)
DFUN(".text.crt.dos.math.math", libd_fminf, libc_fminf, TF, 2, TF, TF)
DFUN(".text.crt.dos.math.math", libd_fmaf, libc_fmaf, TF, 3, TF, TF, TF)
DFUN(".text.crt.dos.math.math", libd_llrintf, libc_llrintf, TLL, 1, TF)
DFUN(".text.crt.dos.math.math", libd_llroundf, libc_llroundf, TLL, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_scalbnl, libd_scalbn);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_scalbnl, libc_scalbnl, TFL, 2, TFL, TD)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_scalblnl, libd_scalbln);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_scalblnl, libc_scalblnl, TFL, 2, TFL, TL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_roundl, libd_round);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_roundl, libc_roundl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_truncl, libd_trunc);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_truncl, libc_truncl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_remquol, libd_remquo);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_remquol, libc_remquol, TFL, 3, TFL, TFL, TP)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_lrintl, libd_remquo);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_lrintl, libc_lrintl, TL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_lroundl, libc_lroundl, TL, 1, TFL)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_fdiml, libd_fdim);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_fdiml, libc_fdiml, TFL, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_fmaxl, libd_fmax);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_fmaxl, libc_fmaxl, TFL, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_fminl, libd_fmin);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_fminl, libc_fminl, TFL, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_fmal, libd_fma);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_fmal, libc_fmal, TFL, 3, TFL, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_llrintl, libd_llrint);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_llrintl, libc_llrintl, TLL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_llroundl, libd_llround);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_llroundl, libc_llroundl, TLL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_sincos, libc_sincos, TV, 3, TFD, TP, TP)
DFUN(".text.crt.dos.math.math", libd_exp10, libc_exp10, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_pow10, libc_pow10, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_sincosf, libc_sincosf, TV, 3, TF, TP, TP)
DFUN(".text.crt.dos.math.math", libd_exp10f, libc_exp10f, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_pow10f, libc_pow10f, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_sincosl, libc_sincosl, TV, 3, TFL, TP, TP)
DFUN(".text.crt.dos.math.math", libd_exp10l, libc_exp10l, TFL, 1, TFL)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_pow10l, libd_pow10);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_pow10l, libc_pow10l, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_isinf, libc_isinf, TD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_isinff, libc_isinff, TD, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_isinfl, libd_isinf);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_isinfl, libc_isinfl, TD, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_finite, libc_finite, TD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_significand, libc_significand, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_finitef, libc_finitef, TD, 1, TF)
DFUN(".text.crt.dos.math.math", libd_significandf, libc_significandf, TF, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_finitel, libd_finite);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_finitel, libc_finitel, TD, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_significandl, libd_significand);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_significandl, libc_significandl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_isnan, libc_isnan, TD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_isnanf, libc_isnanf, TD, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_isnanl, libd_isnan);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_isnanl, libc_isnanl, TD, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_j0, libc_j0, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_j1, libc_j1, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_jn, libc_jn, TFD, 2, TD, TFD)
DFUN(".text.crt.dos.math.math", libd_y0, libc_y0, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_y1, libc_y1, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_yn, libc_yn, TFD, 2, TD, TFD)
DFUN(".text.crt.dos.math.math", libd_j0f, libc_j0f, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_j1f, libc_j1f, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_jnf, libc_jnf, TF, 2, TD, TF)
DFUN(".text.crt.dos.math.math", libd_y0f, libc_y0f, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_y1f, libc_y1f, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_ynf, libc_ynf, TF, 2, TD, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_j0l, libd_j0);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_j0l, libc_j0l, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_j1l, libd_j1);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_j1l, libc_j1l, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_jnl, libd_jn);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_jnl, libc_jnl, TFL, 2, TD, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_y0l, libd_y0);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_y0l, libc_y0l, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_y1l, libd_y1);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_y1l, libc_y1l, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_ynl, libd_yn);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_ynl, libc_ynl, TFL, 2, TD, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_lgamma_r, libc_lgamma_r, TFD, 2, TFD, TP)
DFUN(".text.crt.dos.math.math", libd_lgammaf_r, libc_lgammaf_r, TF, 2, TF, TP)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_lgammal_r, libd_lgamma_r);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_lgammal_r, libc_lgammal_r, TFL, 2, TFL, TP)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_scalb, libc_scalb, TFD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_scalbf, libc_scalbf, TF, 2, TF, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_scalbl, libd_scalb);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_scalbl, libc_scalbl, TFL, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd___signbit, libc___signbit, TD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd___signbitf, libc___signbitf, TD, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd___signbitl, libd___signbit);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd___signbitl, libc___signbitl, TD, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd___issignaling, libc___issignaling, TD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd___issignalingf, libc___issignalingf, TD, 1, TF)
DFUN(".text.crt.dos.math.math", libd___iscanonicall, libc___iscanonicall, TD, 1, TFL)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd___issignalingl, libd___issignaling);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd___issignalingl, libc___issignalingl, TD, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_nextdown, libc_nextdown, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_nextup, libc_nextup, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_nextdownf, libc_nextdownf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_nextupf, libc_nextupf, TF, 1, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_nextdownl, libd_nextdown);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_nextdownl, libc_nextdownl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_nextupl, libd_nextup);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_nextupl, libc_nextupl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libd_llogb, libd_ilogb);
#else /* __SIZEOF_INT__ == __SIZEOF_LONG__ */
DFUN(".text.crt.dos.math.math", libd_llogb, libc_llogb, TL, 1, TFD)
#endif /* __SIZEOF_INT__ != __SIZEOF_LONG__ */
DFUN(".text.crt.dos.math.math", libd_roundeven, libc_roundeven, TFD, 1, TFD)
DFUN(".text.crt.dos.math.math", libd_fromfp, libc_fromfp, TIn(__SIZEOF_INTMAX_T__), 3, TFD, TD, TD)
DFUN(".text.crt.dos.math.math", libd_ufromfp, libc_ufromfp, TIn(__SIZEOF_INTMAX_T__), 3, TFD, TD, TD)
DFUN(".text.crt.dos.math.math", libd_fromfpx, libc_fromfpx, TIn(__SIZEOF_INTMAX_T__), 3, TFD, TD, TD)
DFUN(".text.crt.dos.math.math", libd_ufromfpx, libc_ufromfpx, TIn(__SIZEOF_INTMAX_T__), 3, TFD, TD, TD)
DFUN(".text.crt.dos.math.math", libd_fmaxmag, libc_fmaxmag, TFD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_fminmag, libc_fminmag, TFD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd_canonicalize, libc_canonicalize, TD, 2, TP, TP)
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libd_llogbf, libd_ilogbf);
#else /* __SIZEOF_INT__ == __SIZEOF_LONG__ */
DFUN(".text.crt.dos.math.math", libd_llogbf, libc_llogbf, TL, 1, TF)
#endif /* __SIZEOF_INT__ != __SIZEOF_LONG__ */
DFUN(".text.crt.dos.math.math", libd_roundevenf, libc_roundevenf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd_fromfpf, libc_fromfpf, TIn(__SIZEOF_INTMAX_T__), 3, TF, TD, TD)
DFUN(".text.crt.dos.math.math", libd_ufromfpf, libc_ufromfpf, TIn(__SIZEOF_INTMAX_T__), 3, TF, TD, TD)
DFUN(".text.crt.dos.math.math", libd_fromfpxf, libc_fromfpxf, TIn(__SIZEOF_INTMAX_T__), 3, TF, TD, TD)
DFUN(".text.crt.dos.math.math", libd_ufromfpxf, libc_ufromfpxf, TIn(__SIZEOF_INTMAX_T__), 3, TF, TD, TD)
DFUN(".text.crt.dos.math.math", libd_fmaxmagf, libc_fmaxmagf, TF, 2, TF, TF)
DFUN(".text.crt.dos.math.math", libd_fminmagf, libc_fminmagf, TF, 2, TF, TF)
DFUN(".text.crt.dos.math.math", libd_canonicalizef, libc_canonicalizef, TD, 2, TP, TP)
#if __SIZEOF_INT__ == __SIZEOF_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
DEFINE_INTERN_ALIAS(libd_llogbl, libd_ilogb);
#elif __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libd_llogbl, libd_ilogbl);
#elif defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
DEFINE_INTERN_ALIAS(libd_llogbl, libd_llogbl);
#else /* ... */
DFUN(".text.crt.dos.math.math", libd_llogbl, libc_llogbl, TL, 1, TFL)
#endif /* !... */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_roundevenl, libd_roundeven);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_roundevenl, libc_roundevenl, TFL, 1, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_fromfpl, libd_fromfp);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_fromfpl, libc_fromfpl, TIn(__SIZEOF_INTMAX_T__), 3, TFL, TD, TD)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_ufromfpl, libd_ufromfp);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_ufromfpl, libc_ufromfpl, TIn(__SIZEOF_INTMAX_T__), 3, TFL, TD, TD)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_fromfpxl, libd_fromfpx);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_fromfpxl, libc_fromfpxl, TIn(__SIZEOF_INTMAX_T__), 3, TFL, TD, TD)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_ufromfpxl, libd_ufromfpx);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_ufromfpxl, libc_ufromfpxl, TIn(__SIZEOF_INTMAX_T__), 3, TFL, TD, TD)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_fmaxmagl, libd_fmaxmag);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_fmaxmagl, libc_fmaxmagl, TFL, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_fminmagl, libd_fminmag);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_fminmagl, libc_fminmagl, TFL, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_canonicalizel, libd_canonicalize);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd_canonicalizel, libc_canonicalizel, TD, 2, TP, TP)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd__dpcomp, libc__dpcomp, TD, 2, TFD, TFD)
DFUN(".text.crt.dos.math.math", libd__fdpcomp, libc__fdpcomp, TD, 2, TF, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd__ldpcomp, libd__dpcomp);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd__ldpcomp, libc__ldpcomp, TD, 2, TFL, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.math.math", libd__chgsignf, libc__chgsignf, TF, 1, TF)
DFUN(".text.crt.dos.math.math", libd__chgsign, libc__chgsign, TFD, 1, TFD)

/* mbctype */
DFUN(".text.crt.dos.mbstring", libd__setmbcp, libc__setmbcp, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__mbctouni_l, libc__mbctouni_l, TI32, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__unitombc_l, libc__unitombc_l, TD, 2, TI32, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbbkalnum, libc__ismbbkalnum, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbbkana, libc__ismbbkana, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbbkpunct, libc__ismbbkpunct, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbbalpha, libc__ismbbalpha, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbbpunct, libc__ismbbpunct, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbbblank, libc__ismbbblank, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbbalnum, libc__ismbbalnum, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbbprint, libc__ismbbprint, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbbgraph, libc__ismbbgraph, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbblead, libc__ismbblead, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbbtrail, libc__ismbbtrail, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbblead_l, libc__ismbblead_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbbtrail_l, libc__ismbbtrail_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbbkalnum_l, libc__ismbbkalnum_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbbkana_l, libc__ismbbkana_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbbkpunct_l, libc__ismbbkpunct_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbbalpha_l, libc__ismbbalpha_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbbpunct_l, libc__ismbbpunct_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbbblank_l, libc__ismbbblank_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbbalnum_l, libc__ismbbalnum_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbbprint_l, libc__ismbbprint_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbbgraph_l, libc__ismbbgraph_l, TD, 2, TD, TP)

/* mbstring */
DFUN(".text.crt.dos.mbstring", libd__mbbtombc, libc__mbbtombc, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__mbbtype, libc__mbbtype, TD, 2, THH, TD)
DFUN(".text.crt.dos.mbstring", libd__mbctombb, libc__mbctombb, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__mbsbtype, libc__mbsbtype, TD, 2, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbscat_s, libc__mbscat_s, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbschr, libc__mbschr, TP, 2, TP, TD)
DFUN(".text.crt.dos.mbstring", libd__mbscmp, libc__mbscmp, TD, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbscoll, libc__mbscoll, TD, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbscpy_s, libc__mbscpy_s, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbscspn, libc__mbscspn, TI, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsdec, libc__mbsdec, TP, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsicmp, libc__mbsicmp, TD, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsicoll, libc__mbsicoll, TD, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsinc, libc__mbsinc, TP, 1, TP)
DFUN(".text.crt.dos.mbstring", libd__mbslen, libc__mbslen, TI, 1, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnlen, libc__mbsnlen, TI, 2, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbslwr_s, libc__mbslwr_s, TIn(__SIZEOF_ERRNO_T__), 2, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbslwr, libc__mbslwr, TP, 1, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsupr, libc__mbsupr, TP, 1, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcat_s, libc__mbsnbcat_s, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcat, libc__mbsnbcat, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcmp, libc__mbsnbcmp, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcoll, libc__mbsnbcoll, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcnt, libc__mbsnbcnt, TI, 2, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcpy_s, libc__mbsnbcpy_s, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcpy, libc__mbsnbcpy, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnbicmp, libc__mbsnbicmp, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnbicoll, libc__mbsnbicoll, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnbset_s, libc__mbsnbset_s, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TD, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnbset, libc__mbsnbset, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsncat_s, libc__mbsncat_s, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsncat, libc__mbsncat, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnccnt, libc__mbsnccnt, TI, 2, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsncmp, libc__mbsncmp, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsncoll, libc__mbsncoll, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsncpy_s, libc__mbsncpy_s, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsncpy, libc__mbsncpy, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnextc, libc__mbsnextc, TD, 1, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnicmp, libc__mbsnicmp, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnicoll, libc__mbsnicoll, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsninc, libc__mbsninc, TP, 2, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnset_s, libc__mbsnset_s, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TD, TI)
DFUN(".text.crt.dos.mbstring", libd__mbsnset, libc__mbsnset, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.mbstring", libd__mbspbrk, libc__mbspbrk, TP, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsrchr, libc__mbsrchr, TP, 2, TP, TD)
DFUN(".text.crt.dos.mbstring", libd__mbsrev, libc__mbsrev, TP, 1, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsset_s, libc__mbsset_s, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TD)
DFUN(".text.crt.dos.mbstring", libd__mbsset, libc__mbsset, TP, 2, TP, TD)
DFUN(".text.crt.dos.mbstring", libd__mbsspn, libc__mbsspn, TI, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsspnp, libc__mbsspnp, TP, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsstr, libc__mbsstr, TP, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbstok, libc__mbstok, TP, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbstok_s, libc__mbstok_s, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsupr_s, libc__mbsupr_s, TIn(__SIZEOF_ERRNO_T__), 2, TP, TI)
DFUN(".text.crt.dos.mbstring", libd__mbclen, libc__mbclen, TI, 1, TP)
DFUN(".text.crt.dos.mbstring", libd__mbccpy, libc__mbccpy, TV, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbccpy_s, libc__mbccpy_s, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcalnum, libc__ismbcalnum, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbcalpha, libc__ismbcalpha, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbcdigit, libc__ismbcdigit, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbcgraph, libc__ismbcgraph, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbclegal, libc__ismbclegal, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbclower, libc__ismbclower, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbcprint, libc__ismbcprint, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbcpunct, libc__ismbcpunct, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbcblank, libc__ismbcblank, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbcspace, libc__ismbcspace, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbcupper, libc__ismbcupper, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__mbctolower, libc__mbctolower, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__mbctoupper, libc__mbctoupper, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbchira, libc__ismbchira, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbckata, libc__ismbckata, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbcsymbol, libc__ismbcsymbol, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbcl0, libc__ismbcl0, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbcl1, libc__ismbcl1, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbcl2, libc__ismbcl2, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__mbcjistojms, libc__mbcjistojms, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__mbcjmstojis, libc__mbcjmstojis, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__mbctohira, libc__mbctohira, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__mbctokata, libc__mbctokata, TD, 1, TD)
DFUN(".text.crt.dos.mbstring", libd__ismbslead, libc__ismbslead, TD, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbstrail, libc__ismbstrail, TD, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbscat_l, libc__mbscat_l, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbscpy_l, libc__mbscpy_l, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbccpy_l, libc__mbccpy_l, TV, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsncpy_l, libc__mbsncpy_l, TP, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcpy_l, libc__mbsnbcpy_l, TP, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbschr_l, libc__mbschr_l, TP, 3, TP, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__mbscoll_l, libc__mbscoll_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsicoll_l, libc__mbsicoll_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsncoll_l, libc__mbsncoll_l, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnicoll_l, libc__mbsnicoll_l, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcoll_l, libc__mbsnbcoll_l, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnbicoll_l, libc__mbsnbicoll_l, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbslwr_l, libc__mbslwr_l, TP, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsupr_l, libc__mbsupr_l, TP, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsinc_l, libc__mbsinc_l, TP, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsninc_l, libc__mbsninc_l, TP, 3, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsdec_l, libc__mbsdec_l, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbscspn_l, libc__mbscspn_l, TI, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbslen_l, libc__mbslen_l, TI, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnlen_l, libc__mbsnlen_l, TI, 3, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsncat_l, libc__mbsncat_l, TP, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcat_l, libc__mbsnbcat_l, TP, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnccnt_l, libc__mbsnccnt_l, TI, 3, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcnt_l, libc__mbsnbcnt_l, TI, 3, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbscmp_l, libc__mbscmp_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsicmp_l, libc__mbsicmp_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsncmp_l, libc__mbsncmp_l, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnicmp_l, libc__mbsnicmp_l, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcmp_l, libc__mbsnbcmp_l, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnbicmp_l, libc__mbsnbicmp_l, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnextc_l, libc__mbsnextc_l, TD, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbspbrk_l, libc__mbspbrk_l, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsrchr_l, libc__mbsrchr_l, TP, 3, TP, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsrev_l, libc__mbsrev_l, TP, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsset_l, libc__mbsset_l, TP, 3, TP, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnset_l, libc__mbsnset_l, TP, 4, TP, TD, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnbset_l, libc__mbsnbset_l, TP, 4, TP, TD, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsspn_l, libc__mbsspn_l, TI, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsspnp_l, libc__mbsspnp_l, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsstr_l, libc__mbsstr_l, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbstok_l, libc__mbstok_l, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbstok_s_l, libc__mbstok_s_l, TP, 4, TP, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbclen_l, libc__mbclen_l, TI, 2, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbscat_s_l, libc__mbscat_s_l, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbscpy_s_l, libc__mbscpy_s_l, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbslwr_s_l, libc__mbslwr_s_l, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsupr_s_l, libc__mbsupr_s_l, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcat_s_l, libc__mbsnbcat_s_l, TIn(__SIZEOF_ERRNO_T__), 5, TP, TI, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnbcpy_s_l, libc__mbsnbcpy_s_l, TIn(__SIZEOF_ERRNO_T__), 5, TP, TI, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnbset_s_l, libc__mbsnbset_s_l, TIn(__SIZEOF_ERRNO_T__), 5, TP, TI, TD, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsncat_s_l, libc__mbsncat_s_l, TIn(__SIZEOF_ERRNO_T__), 5, TP, TI, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsncpy_s_l, libc__mbsncpy_s_l, TIn(__SIZEOF_ERRNO_T__), 5, TP, TI, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsnset_s_l, libc__mbsnset_s_l, TIn(__SIZEOF_ERRNO_T__), 5, TP, TI, TD, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsset_s_l, libc__mbsset_s_l, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__mbccpy_s_l, libc__mbccpy_s_l, TIn(__SIZEOF_ERRNO_T__), 5, TP, TI, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbslead_l, libc__ismbslead_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbstrail_l, libc__ismbstrail_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.mbstring", libd__mbbtype_l, libc__mbbtype_l, TD, 3, THH, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__mbsbtype_l, libc__mbsbtype_l, TD, 3, TP, TI, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbclegal_l, libc__ismbclegal_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__mbctolower_l, libc__mbctolower_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__mbctoupper_l, libc__mbctoupper_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcalnum_l, libc__ismbcalnum_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcalpha_l, libc__ismbcalpha_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcdigit_l, libc__ismbcdigit_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcgraph_l, libc__ismbcgraph_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbclower_l, libc__ismbclower_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcupper_l, libc__ismbcupper_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcprint_l, libc__ismbcprint_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcpunct_l, libc__ismbcpunct_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcblank_l, libc__ismbcblank_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcspace_l, libc__ismbcspace_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbchira_l, libc__ismbchira_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbckata_l, libc__ismbckata_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcsymbol_l, libc__ismbcsymbol_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcl0_l, libc__ismbcl0_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcl1_l, libc__ismbcl1_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__ismbcl2_l, libc__ismbcl2_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__mbcjistojms_l, libc__mbcjistojms_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__mbcjmstojis_l, libc__mbcjmstojis_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__mbctohira_l, libc__mbctohira_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__mbctokata_l, libc__mbctokata_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__mbbtombc_l, libc__mbbtombc_l, TD, 2, TD, TP)
DFUN(".text.crt.dos.mbstring", libd__mbctombb_l, libc__mbctombb_l, TD, 2, TD, TP)

/* mntent */
DFUN(".text.crt.dos.database.mntent", libd_endmntent, libc_endmntent, TD, 1, TP)
DFUN(".text.crt.dos.database.mntent", libd_getmntent, libc_getmntent, TP, 1, TP)
DFUN(".text.crt.dos.database.mntent", libd_getmntent_r, libc_getmntent_r, TP, 4, TP, TP, TP, TD)
DFUN(".text.crt.dos.database.mntent", libd_addmntent, libc_addmntent, TD, 2, TP, TP)
DFUN(".text.crt.dos.database.mntent", libd_hasmntopt, libc_hasmntopt, TP, 2, TP, TP)

/* mqueue */
DFUN(".text.crt.dos.utility.mqueue", libd_mq_open, libc_mq_open, TD, 3, TP, TIn(__SIZEOF_OFLAG_T__), TIn(__SIZEOF_MODE_T__))
DFUN(".text.crt.dos.utility.mqueue", libd_mq_close, libc_mq_close, TD, 1, TD)
DFUN(".text.crt.dos.utility.mqueue", libd_mq_getattr, libc_mq_getattr, TD, 2, TD, TP)
DFUN(".text.crt.dos.utility.mqueue", libd_mq_setattr, libc_mq_setattr, TD, 3, TD, TP, TP)
DFUN(".text.crt.dos.utility.mqueue", libd_mq_unlink, libc_mq_unlink, TD, 1, TP)
DFUN(".text.crt.dos.utility.mqueue", libd_mq_notify, libc_mq_notify, TD, 2, TD, TP)
DFUN(".text.crt.dos.utility.mqueue", libd_mq_receive, libc_mq_receive, TI, 4, TD, TP, TI, TP)
DFUN(".text.crt.dos.utility.mqueue", libd_mq_send, libc_mq_send, TD, 4, TD, TP, TI, TD)
DFUN(".text.crt.dos.utility.mqueue", libd_mq_timedreceive, libc_mq_timedreceive, TI, 5, TD, TP, TI, TP, TP)
DFUN(".text.crt.dos.utility.mqueue", libd_mq_timedsend, libc_mq_timedsend, TD, 5, TD, TP, TI, TD, TP)
DFUN(".text.crt.dos.utility.mqueue", libd_mq_timedreceive64, libc_mq_timedreceive64, TI, 5, TD, TP, TI, TP, TP)
DFUN(".text.crt.dos.utility.mqueue", libd_mq_timedsend64, libc_mq_timedsend64, TD, 5, TD, TP, TI, TD, TP)

/* net.if */
DFUN(".text.crt.dos.net.interface", libd_if_nametoindex, libc_if_nametoindex, TD, 1, TP)
DFUN(".text.crt.dos.net.interface", libd_if_indextoname, libc_if_indextoname, TP, 2, TD, TP)
DFUN(".text.crt.dos.net.interface", libd_if_freenameindex, libc_if_freenameindex, TV, 1, TP)

/* netdb */
DFUN(".text.crt.dos.net.db", libd_sethostent, libc_sethostent, TV, 1, TD)
DFUN(".text.crt.dos.net.db", libd_gethostbyaddr, libc_gethostbyaddr, TP, 3, TP, TIn(__SIZEOF_SOCKLEN_T__), TD)
DFUN(".text.crt.dos.net.db", libd_gethostbyname, libc_gethostbyname, TP, 1, TP)
DFUN(".text.crt.dos.net.db", libd_setnetent, libc_setnetent, TV, 1, TD)
DFUN(".text.crt.dos.net.db", libd_getnetbyaddr, libc_getnetbyaddr, TP, 2, TI32, TD)
DFUN(".text.crt.dos.net.db", libd_getnetbyname, libc_getnetbyname, TP, 1, TP)
DFUN(".text.crt.dos.net.db", libd_setservent, libc_setservent, TV, 1, TD)
DFUN(".text.crt.dos.net.db", libd_getservbyname, libc_getservbyname, TP, 2, TP, TP)
DFUN(".text.crt.dos.net.db", libd_getservbyport, libc_getservbyport, TP, 2, TD, TP)
DFUN(".text.crt.dos.net.db", libd_setprotoent, libc_setprotoent, TV, 1, TD)
DFUN(".text.crt.dos.net.db", libd_getprotobyname, libc_getprotobyname, TP, 1, TP)
DFUN(".text.crt.dos.net.db", libd_getprotobynumber, libc_getprotobynumber, TP, 1, TD)
DFUN(".text.crt.dos.net.db", libd_herror, libc_herror, TV, 1, TP)
DFUN(".text.crt.dos.net.db", libd_hstrerror, libc_hstrerror, TP, 1, TD)
DFUN(".text.crt.dos.net.db", libd_gethostbyname2, libc_gethostbyname2, TP, 2, TP, TD)
DFUN(".text.crt.dos.net.db", libd_gethostent_r, libc_gethostent_r, TD, 5, TP, TP, TI, TP, TP)
DFUN(".text.crt.dos.net.db", libd_gethostbyaddr_r, libc_gethostbyaddr_r, TD, 8, TP, TIn(__SIZEOF_SOCKLEN_T__), TD, TP, TP, TI, TP, TP)
DFUN(".text.crt.dos.net.db", libd_gethostbyname_r, libc_gethostbyname_r, TD, 6, TP, TP, TP, TI, TP, TP)
DFUN(".text.crt.dos.net.db", libd_gethostbyname2_r, libc_gethostbyname2_r, TD, 7, TP, TD, TP, TP, TI, TP, TP)
DFUN(".text.crt.dos.net.db", libd_getnetent_r, libc_getnetent_r, TD, 5, TP, TP, TI, TP, TP)
DFUN(".text.crt.dos.net.db", libd_getnetbyaddr_r, libc_getnetbyaddr_r, TD, 7, TI32, TD, TP, TP, TI, TP, TP)
DFUN(".text.crt.dos.net.db", libd_getnetbyname_r, libc_getnetbyname_r, TD, 6, TP, TP, TP, TI, TP, TP)
DFUN(".text.crt.dos.net.db", libd_getservent_r, libc_getservent_r, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.net.db", libd_getservbyname_r, libc_getservbyname_r, TD, 6, TP, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.net.db", libd_getservbyport_r, libc_getservbyport_r, TD, 6, TD, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.net.db", libd_getprotoent_r, libc_getprotoent_r, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.net.db", libd_getprotobyname_r, libc_getprotobyname_r, TD, 5, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.net.db", libd_getprotobynumber_r, libc_getprotobynumber_r, TD, 5, TD, TP, TP, TI, TP)
DFUN(".text.crt.dos.net.db", libd_setnetgrent, libc_setnetgrent, TD, 1, TP)
DFUN(".text.crt.dos.net.db", libd_getnetgrent, libc_getnetgrent, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.net.db", libd_innetgr, libc_innetgr, TD, 4, TP, TP, TP, TP)
DFUN(".text.crt.dos.net.db", libd_getnetgrent_r, libc_getnetgrent_r, TD, 5, TP, TP, TP, TP, TI)
DFUN(".text.crt.dos.net.db", libd_rcmd, libc_rcmd, TD, 6, TP, TI16, TP, TP, TP, TP)
DFUN(".text.crt.dos.net.db", libd_rcmd_af, libc_rcmd_af, TD, 7, TP, TI16, TP, TP, TP, TP, TI16)
DFUN(".text.crt.dos.net.db", libd_rexec, libc_rexec, TD, 6, TP, TD, TP, TP, TP, TP)
DFUN(".text.crt.dos.net.db", libd_rexec_af, libc_rexec_af, TD, 7, TP, TD, TP, TP, TP, TP, TI16)
DFUN(".text.crt.dos.net.db", libd_ruserok, libc_ruserok, TD, 4, TP, TD, TP, TP)
DFUN(".text.crt.dos.net.db", libd_ruserok_af, libc_ruserok_af, TD, 5, TP, TD, TP, TP, TI16)
DFUN(".text.crt.dos.net.db", libd_iruserok, libc_iruserok, TD, 4, TI32, TD, TP, TP)
DFUN(".text.crt.dos.net.db", libd_iruserok_af, libc_iruserok_af, TD, 5, TP, TD, TP, TP, TI16)
DFUN(".text.crt.dos.net.db", libd_rresvport, libc_rresvport, TD, 1, TP)
DFUN(".text.crt.dos.net.db", libd_rresvport_af, libc_rresvport_af, TD, 2, TP, TI16)
DFUN(".text.crt.dos.net.db", libd_getaddrinfo, libc_getaddrinfo, TD, 4, TP, TP, TP, TP)
DFUN(".text.crt.dos.net.db", libd_freeaddrinfo, libc_freeaddrinfo, TV, 1, TP)
DFUN(".text.crt.dos.net.db", libd_gai_strerror, libc_gai_strerror, TP, 1, TD)
DFUN(".text.crt.dos.net.db", libd_getnameinfo, libc_getnameinfo, TD, 7, TP, TIn(__SIZEOF_SOCKLEN_T__), TP, TIn(__SIZEOF_SOCKLEN_T__), TP, TIn(__SIZEOF_SOCKLEN_T__), TD)
DFUN(".text.crt.dos.net.db", libd_getaddrinfo_a, libc_getaddrinfo_a, TD, 4, TD, TP, TD, TP)
DFUN(".text.crt.dos.net.db", libd_gai_error, libc_gai_error, TD, 1, TP)
DFUN(".text.crt.dos.net.db", libd_gai_cancel, libc_gai_cancel, TD, 1, TP)
DFUN(".text.crt.dos.net.db", libd_gai_suspend, libc_gai_suspend, TD, 3, TP, TD, TP)
DFUN(".text.crt.dos.net.db", libd_gai_suspend64, libc_gai_suspend64, TD, 3, TP, TD, TP)

/* netinet.ether */
DFUN(".text.crt.dos.net.ether", libd_ether_ntoa, libc_ether_ntoa, TP, 1, TP)
DFUN(".text.crt.dos.net.ether", libd_ether_ntoa_r, libc_ether_ntoa_r, TP, 2, TP, TP)
DFUN(".text.crt.dos.net.ether", libd_ether_aton, libc_ether_aton, TP, 1, TP)
DFUN(".text.crt.dos.net.ether", libd_ether_aton_r, libc_ether_aton_r, TP, 2, TP, TP)
DFUN(".text.crt.dos.net.ether", libd_ether_aton_np, libc_ether_aton_np, TP, 2, TP, TP)
DFUN(".text.crt.dos.net.ether", libd_ether_line, libc_ether_line, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.net.ether", libd_ether_line_np, libc_ether_line_np, TP, 2, TP, TP)
DFUN(".text.crt.dos.net.ether", libd_ether_ntohost, libc_ether_ntohost, TD, 2, TP, TP)
DFUN(".text.crt.dos.net.ether", libd_ether_hostton, libc_ether_hostton, TD, 2, TP, TP)

/* netinet.in */
DFUN(".text.crt.dos.net.convert", libd_htons, libc_htons, TI16, 1, TI16)
DFUN(".text.crt.dos.net.convert", libd_ntohs, libc_ntohs, TI16, 1, TI16)
DFUN(".text.crt.dos.net.convert", libd_htonl, libc_htonl, TI32, 1, TI32)
DFUN(".text.crt.dos.net.convert", libd_ntohl, libc_ntohl, TI32, 1, TI32)
DFUN(".text.crt.dos.net.convert", libd_htonq, libc_htonq, TI64, 1, TI64)
DFUN(".text.crt.dos.net.convert", libd_ntohq, libc_ntohq, TI64, 1, TI64)
DFUN(".text.crt.dos.net.inet.6.bind_reserved", libd_bindresvport, libc_bindresvport, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.net.inet.6.bind_reserved", libd_bindresvport6, libc_bindresvport6, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.net.inet.6.RFC_2292", libd_inet6_option_space, libc_inet6_option_space, TD, 1, TD)
DFUN(".text.crt.dos.net.inet.6.RFC_2292", libd_inet6_option_init, libc_inet6_option_init, TD, 3, TP, TP, TD)
DFUN(".text.crt.dos.net.inet.6.RFC_2292", libd_inet6_option_append, libc_inet6_option_append, TD, 4, TP, TP, TD, TD)
DFUN(".text.crt.dos.net.inet.6.RFC_2292", libd_inet6_option_alloc, libc_inet6_option_alloc, TP, 4, TP, TD, TD, TD)
DFUN(".text.crt.dos.net.inet.6.RFC_2292", libd_inet6_option_next, libc_inet6_option_next, TD, 2, TP, TP)
DFUN(".text.crt.dos.net.inet.6.RFC_2292", libd_inet6_option_find, libc_inet6_option_find, TD, 3, TP, TP, TD)
DFUN(".text.crt.dos.net.inet.6.RFC_3542", libd_inet6_opt_init, libc_inet6_opt_init, TD, 2, TP, TIn(__SIZEOF_SOCKLEN_T__))
DFUN(".text.crt.dos.net.inet.6.RFC_3542", libd_inet6_opt_append, libc_inet6_opt_append, TD, 7, TP, TIn(__SIZEOF_SOCKLEN_T__), TD, TI8, TIn(__SIZEOF_SOCKLEN_T__), TI8, TP)
DFUN(".text.crt.dos.net.inet.6.RFC_3542", libd_inet6_opt_finish, libc_inet6_opt_finish, TD, 3, TP, TIn(__SIZEOF_SOCKLEN_T__), TD)
DFUN(".text.crt.dos.net.inet.6.RFC_3542", libd_inet6_opt_set_val, libc_inet6_opt_set_val, TD, 4, TP, TD, TP, TIn(__SIZEOF_SOCKLEN_T__))
DFUN(".text.crt.dos.net.inet.6.RFC_3542", libd_inet6_opt_next, libc_inet6_opt_next, TD, 6, TP, TIn(__SIZEOF_SOCKLEN_T__), TD, TP, TP, TP)
DFUN(".text.crt.dos.net.inet.6.RFC_3542", libd_inet6_opt_find, libc_inet6_opt_find, TD, 6, TP, TIn(__SIZEOF_SOCKLEN_T__), TD, TI8, TP, TP)
DFUN(".text.crt.dos.net.inet.6.RFC_3542", libd_inet6_opt_get_val, libc_inet6_opt_get_val, TD, 4, TP, TD, TP, TIn(__SIZEOF_SOCKLEN_T__))
DFUN(".text.crt.dos.net.inet.6.RFC_3542", libd_inet6_rth_space, libc_inet6_rth_space, TIn(__SIZEOF_SOCKLEN_T__), 2, TD, TD)
DFUN(".text.crt.dos.net.inet.6.RFC_3542", libd_inet6_rth_init, libc_inet6_rth_init, TP, 4, TP, TIn(__SIZEOF_SOCKLEN_T__), TD, TD)
DFUN(".text.crt.dos.net.inet.6.RFC_3542", libd_inet6_rth_add, libc_inet6_rth_add, TD, 2, TP, TP)
DFUN(".text.crt.dos.net.inet.6.RFC_3542", libd_inet6_rth_reverse, libc_inet6_rth_reverse, TD, 2, TP, TP)
DFUN(".text.crt.dos.net.inet.6.RFC_3542", libd_inet6_rth_segments, libc_inet6_rth_segments, TD, 1, TP)
DFUN(".text.crt.dos.net.inet.6.RFC_3542", libd_inet6_rth_getaddr, libc_inet6_rth_getaddr, TP, 2, TP, TD)
DFUN(".text.crt.dos.net.inet.6.ipv4_source_filter", libd_getipv4sourcefilter, libc_getipv4sourcefilter, TD, 6, TIn(__SIZEOF_FD_T__), TS(__SIZEOF_IN_ADDR), TS(__SIZEOF_IN_ADDR), TP, TP, TP)
DFUN(".text.crt.dos.net.inet.6.ipv4_source_filter", libd_setipv4sourcefilter, libc_setipv4sourcefilter, TD, 6, TIn(__SIZEOF_FD_T__), TS(__SIZEOF_IN_ADDR), TS(__SIZEOF_IN_ADDR), TI32, TI32, TP)
DFUN(".text.crt.dos.net.inet.6.source_filter", libd_getsourcefilter, libc_getsourcefilter, TD, 7, TIn(__SIZEOF_FD_T__), TI32, TP, TIn(__SIZEOF_SOCKLEN_T__), TP, TP, TP)
DFUN(".text.crt.dos.net.inet.6.source_filter", libd_setsourcefilter, libc_setsourcefilter, TD, 7, TIn(__SIZEOF_FD_T__), TI32, TP, TIn(__SIZEOF_SOCKLEN_T__), TI32, TI32, TP)

/* nl_types */
DFUN(".text.crt.dos.heap.malloc", libd_catopen, libc_catopen, TP, 2, TP, TD)
DFUN(".text.crt.dos.heap.malloc", libd_catgets, libc_catgets, TP, 4, TP, TD, TD, TP)
DFUN(".text.crt.dos.heap.malloc", libd_catclose, libc_catclose, TD, 1, TP)

/* objalloc */
DFUN(".text.crt.dos.libiberty", libd__objalloc_alloc, libc__objalloc_alloc, TP, 2, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_objalloc_free, libc_objalloc_free, TV, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_objalloc_free_block, libc_objalloc_free_block, TV, 2, TP, TP)

/* obstack */
DFUN(".text.crt.dos.heap.obstack", libd__obstack_begin, libc__obstack_begin, TD, 5, TP, TI, TI, TP, TP)
DFUN(".text.crt.dos.heap.obstack", libd__obstack_begin_1, libc__obstack_begin_1, TD, 6, TP, TI, TI, TP, TP, TP)
DFUN(".text.crt.dos.heap.obstack", libd__obstack_newchunk, libc__obstack_newchunk, TV, 2, TP, TI)
DFUN(".text.crt.dos.heap.obstack", libd_obstack_free, libc_obstack_free, TV, 2, TP, TP)
DFUN(".text.crt.dos.heap.obstack", libd__obstack_memory_used, libc__obstack_memory_used, TI, 1, TP)
DFUN(".text.crt.dos.heap.obstack", libd__obstack_allocated_p, libc__obstack_allocated_p, TD, 2, TP, TP)

/* partition */
DFUN(".text.crt.dos.libiberty", libd_partition_new, libc_partition_new, TP, 1, TD)
DFUN(".text.crt.dos.libiberty", libd_partition_delete, libc_partition_delete, TV, 1, TP)
DFUN(".text.crt.dos.libiberty", libd_partition_union, libc_partition_union, TD, 3, TP, TD, TD)
DFUN(".text.crt.dos.libiberty", libd_partition_print, libc_partition_print, TV, 2, TP, TP)

/* process */
DFUN(".text.crt.dos.fs.exec.spawn", libd_cwait, libc_cwait, TIn(__SIZEOF_PID_T__), 3, TP, TIn(__SIZEOF_PID_T__), TD)
DFUN(".text.crt.dos.fs.exec.spawn", libd_fspawnve, libc_fspawnve, TIn(__SIZEOF_PID_T__), 4, TD, TIn(__SIZEOF_FD_T__), TP, TP)
DFUN(".text.crt.dos.sched.thread", libd__beginthread, libc__beginthread, TP, 3, TP, TI32, TP)
DFUN(".text.crt.dos.sched.thread", libd__beginthreadex, libc__beginthreadex, TP, 6, TP, TI32, TP, TP, TI32, TP)
DFUN(".text.crt.dos.sched.thread", libd__endthreadex, libc__endthreadex, TV, 1, TI32)
DFUN(".text.crt.dos.fs.dlfcn", libd__unloaddll, libc__unloaddll, TD, 1, TP)
DFUN(".text.crt.dos.fs.dlfcn", libd__getdllprocaddr, libc__getdllprocaddr, TP, 3, TP, TP, TP)

/* pthread */
DFUN(".text.crt.dos.sched.pthread", libd_pthread_exit, libc_pthread_exit, TV, 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_join, libc_pthread_join, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_getresult_np, libc_pthread_getresult_np, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_tryjoin_np, libc_pthread_tryjoin_np, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_timedjoin_np, libc_pthread_timedjoin_np, TIn(__SIZEOF_ERRNO_T__), 3, TIn(__SIZEOF_PTHREAD_T), TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_timedjoin64_np, libc_pthread_timedjoin64_np, TIn(__SIZEOF_ERRNO_T__), 3, TIn(__SIZEOF_PTHREAD_T), TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_detach, libc_pthread_detach, TIn(__SIZEOF_ERRNO_T__), 1, TIn(__SIZEOF_PTHREAD_T))
DFUN(".text.crt.dos.sched.pthread", libd_pthread_equal, libc_pthread_equal, TD, 2, TIn(__SIZEOF_PTHREAD_T), TIn(__SIZEOF_PTHREAD_T))
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_init, libc_pthread_attr_init, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_destroy, libc_pthread_attr_destroy, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_getdetachstate, libc_pthread_attr_getdetachstate, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_setdetachstate, libc_pthread_attr_setdetachstate, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_getguardsize, libc_pthread_attr_getguardsize, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_setguardsize, libc_pthread_attr_setguardsize, TIn(__SIZEOF_ERRNO_T__), 2, TP, TI)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_getschedparam, libc_pthread_attr_getschedparam, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_setschedparam, libc_pthread_attr_setschedparam, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_getschedpolicy, libc_pthread_attr_getschedpolicy, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_setschedpolicy, libc_pthread_attr_setschedpolicy, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_getinheritsched, libc_pthread_attr_getinheritsched, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_setinheritsched, libc_pthread_attr_setinheritsched, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_getscope, libc_pthread_attr_getscope, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_setscope, libc_pthread_attr_setscope, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_getstackaddr, libc_pthread_attr_getstackaddr, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_setstackaddr, libc_pthread_attr_setstackaddr, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_getstacksize, libc_pthread_attr_getstacksize, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_setstacksize, libc_pthread_attr_setstacksize, TIn(__SIZEOF_ERRNO_T__), 2, TP, TI)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_getstack, libc_pthread_attr_getstack, TIn(__SIZEOF_ERRNO_T__), 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_setstack, libc_pthread_attr_setstack, TIn(__SIZEOF_ERRNO_T__), 3, TP, TP, TI)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_setaffinity_np, libc_pthread_attr_setaffinity_np, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_attr_getaffinity_np, libc_pthread_attr_getaffinity_np, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_getattr_default_np, libc_pthread_getattr_default_np, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_setattr_default_np, libc_pthread_setattr_default_np, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_getattr_np, libc_pthread_getattr_np, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_setschedparam, libc_pthread_setschedparam, TIn(__SIZEOF_ERRNO_T__), 3, TIn(__SIZEOF_PTHREAD_T), TD, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_getschedparam, libc_pthread_getschedparam, TIn(__SIZEOF_ERRNO_T__), 3, TIn(__SIZEOF_PTHREAD_T), TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_setschedprio, libc_pthread_setschedprio, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_getname_np, libc_pthread_getname_np, TIn(__SIZEOF_ERRNO_T__), 3, TIn(__SIZEOF_PTHREAD_T), TP, TI)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_setname_np, libc_pthread_setname_np, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TP)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_gettid_np, libc_pthread_gettid_np, TIn(__SIZEOF_PID_T__), 1, TIn(__SIZEOF_PTHREAD_T))
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_getpidfd_np, libc_pthread_getpidfd_np, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TP)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_attr_setpidfdallocated_np, libc_pthread_attr_setpidfdallocated_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_attr_getpidfdallocated_np, libc_pthread_attr_getpidfdallocated_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_setconcurrency, libc_pthread_setconcurrency, TIn(__SIZEOF_ERRNO_T__), 1, TD)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_setaffinity_np, libc_pthread_setaffinity_np, TIn(__SIZEOF_ERRNO_T__), 3, TIn(__SIZEOF_PTHREAD_T), TI, TP)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_getaffinity_np, libc_pthread_getaffinity_np, TIn(__SIZEOF_ERRNO_T__), 3, TIn(__SIZEOF_PTHREAD_T), TI, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_once, libc_pthread_once, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_setcancelstate, libc_pthread_setcancelstate, TIn(__SIZEOF_ERRNO_T__), 2, TD, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_setcanceltype, libc_pthread_setcanceltype, TIn(__SIZEOF_ERRNO_T__), 2, TD, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_cancel, libc_pthread_cancel, TIn(__SIZEOF_ERRNO_T__), 1, TIn(__SIZEOF_PTHREAD_T))
DFUN(".text.crt.dos.sched.pthread", libd___pthread_cleanup_routine, libc___pthread_cleanup_routine, TV, 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd___pthread_register_cancel, libc___pthread_register_cancel, TV, 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd___pthread_unregister_cancel, libc___pthread_unregister_cancel, TV, 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd___pthread_register_cancel_defer, libc___pthread_register_cancel_defer, TV, 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd___pthread_unregister_cancel_restore, libc___pthread_unregister_cancel_restore, TV, 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd___pthread_unwind_next, libc___pthread_unwind_next, TV, 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutex_init, libc_pthread_mutex_init, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutex_destroy, libc_pthread_mutex_destroy, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutex_trylock, libc_pthread_mutex_trylock, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutex_lock, libc_pthread_mutex_lock, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutex_timedlock, libc_pthread_mutex_timedlock, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutex_timedlock64, libc_pthread_mutex_timedlock64, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutex_reltimedlock_np, libc_pthread_mutex_reltimedlock_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutex_reltimedlock64_np, libc_pthread_mutex_reltimedlock64_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutex_unlock, libc_pthread_mutex_unlock, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutex_getprioceiling, libc_pthread_mutex_getprioceiling, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutex_setprioceiling, libc_pthread_mutex_setprioceiling, TIn(__SIZEOF_ERRNO_T__), 3, TP, TD, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutex_consistent, libc_pthread_mutex_consistent, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutexattr_init, libc_pthread_mutexattr_init, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutexattr_destroy, libc_pthread_mutexattr_destroy, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutexattr_getpshared, libc_pthread_mutexattr_getpshared, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutexattr_setpshared, libc_pthread_mutexattr_setpshared, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutexattr_gettype, libc_pthread_mutexattr_gettype, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutexattr_settype, libc_pthread_mutexattr_settype, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutexattr_getprotocol, libc_pthread_mutexattr_getprotocol, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutexattr_setprotocol, libc_pthread_mutexattr_setprotocol, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutexattr_getprioceiling, libc_pthread_mutexattr_getprioceiling, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutexattr_setprioceiling, libc_pthread_mutexattr_setprioceiling, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutexattr_getrobust, libc_pthread_mutexattr_getrobust, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_mutexattr_setrobust, libc_pthread_mutexattr_setrobust, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_init, libc_pthread_rwlock_init, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_destroy, libc_pthread_rwlock_destroy, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_rdlock, libc_pthread_rwlock_rdlock, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_tryrdlock, libc_pthread_rwlock_tryrdlock, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_wrlock, libc_pthread_rwlock_wrlock, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_trywrlock, libc_pthread_rwlock_trywrlock, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_timedrdlock, libc_pthread_rwlock_timedrdlock, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_timedwrlock, libc_pthread_rwlock_timedwrlock, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_timedrdlock64, libc_pthread_rwlock_timedrdlock64, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_timedwrlock64, libc_pthread_rwlock_timedwrlock64, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_reltimedrdlock_np, libc_pthread_rwlock_reltimedrdlock_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_reltimedwrlock_np, libc_pthread_rwlock_reltimedwrlock_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_reltimedrdlock64_np, libc_pthread_rwlock_reltimedrdlock64_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_reltimedwrlock64_np, libc_pthread_rwlock_reltimedwrlock64_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlock_unlock, libc_pthread_rwlock_unlock, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlockattr_init, libc_pthread_rwlockattr_init, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlockattr_destroy, libc_pthread_rwlockattr_destroy, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlockattr_getpshared, libc_pthread_rwlockattr_getpshared, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlockattr_setpshared, libc_pthread_rwlockattr_setpshared, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlockattr_getkind_np, libc_pthread_rwlockattr_getkind_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_rwlockattr_setkind_np, libc_pthread_rwlockattr_setkind_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_cond_init, libc_pthread_cond_init, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_cond_destroy, libc_pthread_cond_destroy, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_cond_signal, libc_pthread_cond_signal, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_cond_broadcast, libc_pthread_cond_broadcast, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_cond_wait, libc_pthread_cond_wait, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_cond_timedwait, libc_pthread_cond_timedwait, TIn(__SIZEOF_ERRNO_T__), 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_cond_timedwait64, libc_pthread_cond_timedwait64, TIn(__SIZEOF_ERRNO_T__), 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_cond_reltimedwait_np, libc_pthread_cond_reltimedwait_np, TIn(__SIZEOF_ERRNO_T__), 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_cond_reltimedwait64_np, libc_pthread_cond_reltimedwait64_np, TIn(__SIZEOF_ERRNO_T__), 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_condattr_init, libc_pthread_condattr_init, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_condattr_destroy, libc_pthread_condattr_destroy, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_condattr_getpshared, libc_pthread_condattr_getpshared, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_condattr_setpshared, libc_pthread_condattr_setpshared, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_condattr_getclock, libc_pthread_condattr_getclock, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_condattr_setclock, libc_pthread_condattr_setclock, TIn(__SIZEOF_ERRNO_T__), 2, TP, TIn(__SIZEOF_CLOCKID_T__))
DFUN(".text.crt.dos.sched.pthread", libd_pthread_spin_init, libc_pthread_spin_init, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_spin_destroy, libc_pthread_spin_destroy, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_spin_lock, libc_pthread_spin_lock, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_spin_trylock, libc_pthread_spin_trylock, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_spin_unlock, libc_pthread_spin_unlock, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_barrier_init, libc_pthread_barrier_init, TIn(__SIZEOF_ERRNO_T__), 3, TP, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_barrier_destroy, libc_pthread_barrier_destroy, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_barrier_wait, libc_pthread_barrier_wait, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_barrierattr_init, libc_pthread_barrierattr_init, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_barrierattr_destroy, libc_pthread_barrierattr_destroy, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_barrierattr_getpshared, libc_pthread_barrierattr_getpshared, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_barrierattr_setpshared, libc_pthread_barrierattr_setpshared, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_key_delete, libc_pthread_key_delete, TIn(__SIZEOF_ERRNO_T__), 1, TIn(__SIZEOF_PTHREAD_KEY_T))
DFUN(".text.crt.dos.sched.pthread", libd_pthread_getspecific, libc_pthread_getspecific, TP, 1, TIn(__SIZEOF_PTHREAD_KEY_T))
DFUN(".text.crt.dos.sched.pthread", libd_pthread_setspecific, libc_pthread_setspecific, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_KEY_T), TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_getspecificptr_np, libc_pthread_getspecificptr_np, TP, 1, TIn(__SIZEOF_PTHREAD_KEY_T))
DFUN(".text.crt.dos.sched.pthread", libd_pthread_getcpuclockid, libc_pthread_getcpuclockid, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TP)
DFUN(".text.crt.dos.sched.pthread", libd_pthread_atfork, libc_pthread_atfork, TIn(__SIZEOF_ERRNO_T__), 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_set_num_processors_np, libc_pthread_set_num_processors_np, TIn(__SIZEOF_ERRNO_T__), 1, TD)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_attr_setstartsuspended_np, libc_pthread_attr_setstartsuspended_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_attr_getstartsuspended_np, libc_pthread_attr_getstartsuspended_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_suspend2_np, libc_pthread_suspend2_np, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TP)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_resume2_np, libc_pthread_resume2_np, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TP)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_attach_np, libc_pthread_attach_np, TV, 1, TIn(__SIZEOF_PTHREAD_T))
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_enumthreads_np, libc_pthread_enumthreads_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_attachtid_np, libc_pthread_attachtid_np, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PID_T__), TP)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_attachpidfd_np, libc_pthread_attachpidfd_np, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_continue_np, libc_pthread_continue_np, TIn(__SIZEOF_ERRNO_T__), 1, TIn(__SIZEOF_PTHREAD_T))
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_attr_setcreatesuspend_np, libc_pthread_attr_setcreatesuspend_np, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_suspend_np, libc_pthread_suspend_np, TIn(__SIZEOF_ERRNO_T__), 1, TIn(__SIZEOF_PTHREAD_T))
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_resume_np, libc_pthread_resume_np, TIn(__SIZEOF_ERRNO_T__), 1, TIn(__SIZEOF_PTHREAD_T))
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_getunique_np, libc_pthread_getunique_np, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TP)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_mutex_isowned_np, libc_pthread_mutex_isowned_np, TD, 1, TP)
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_switch_add_np, libc_pthread_switch_add_np, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DEFINE_INTERN_ALIAS(libd_pthread_switch_delete_np, libd_pthread_switch_add_np);
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_get_stacksize_np, libc_pthread_get_stacksize_np, TI, 1, TIn(__SIZEOF_PTHREAD_T))
DFUN(".text.crt.dos.sched.pthread_ext", libd_pthread_get_stackaddr_np, libc_pthread_get_stackaddr_np, TP, 1, TIn(__SIZEOF_PTHREAD_T))

/* pthread_np */
DFUN(".text.crt.dos.sched.pthread", libd_pthread_stackseg_np, libc_pthread_stackseg_np, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TP)

/* pty */
DFUN(".text.crt.dos.io.tty", libd_openpty, libc_openpty, TD, 5, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.io.tty", libd_forkpty, libc_forkpty, TIn(__SIZEOF_PID_T__), 4, TP, TP, TP, TP)

/* pwd */
DFUN(".text.crt.dos.database.pwd", libd_getpwuid, libc_getpwuid, TP, 1, TIn(__SIZEOF_UID_T__))
DFUN(".text.crt.dos.database.pwd", libd_getpwnam, libc_getpwnam, TP, 1, TP)
DFUN(".text.crt.dos.database.pwd", libd_fgetpwent, libc_fgetpwent, TP, 1, TP)
DFUN(".text.crt.dos.database.pwd", libd_putpwent, libc_putpwent, TD, 2, TP, TP)
DFUN(".text.crt.dos.database.pwd", libd_getpwuid_r, libc_getpwuid_r, TIn(__SIZEOF_ERRNO_T__), 5, TIn(__SIZEOF_UID_T__), TP, TP, TI, TP)
DFUN(".text.crt.dos.database.pwd", libd_getpwnam_r, libc_getpwnam_r, TIn(__SIZEOF_ERRNO_T__), 5, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.database.pwd", libd_getpwent_r, libc_getpwent_r, TIn(__SIZEOF_ERRNO_T__), 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.database.pwd", libd_fgetpwent_r, libc_fgetpwent_r, TIn(__SIZEOF_ERRNO_T__), 5, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.database.pwd", libd_fgetpwuid_r, libc_fgetpwuid_r, TIn(__SIZEOF_ERRNO_T__), 6, TP, TIn(__SIZEOF_UID_T__), TP, TP, TI, TP)
DFUN(".text.crt.dos.database.pwd", libd_fgetpwnam_r, libc_fgetpwnam_r, TIn(__SIZEOF_ERRNO_T__), 6, TP, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.database.pwd", libd_getpw, libc_getpw, TD, 2, TIn(__SIZEOF_UID_T__), TP)
DFUN(".text.crt.compat.linux", libd_sgetpwent, libc_sgetpwent, TP, 1, TP)
DFUN(".text.crt.dos.database.pwd", libd_setpassent, libc_setpassent, TD, 1, TD)
DFUN(".text.crt.dos.database.pwd", libd_uid_from_user, libc_uid_from_user, TD, 2, TP, TP)
DFUN(".text.crt.dos.database.pwd", libd_user_from_uid, libc_user_from_uid, TP, 2, TIn(__SIZEOF_UID_T__), TD)
DFUN(".text.crt.dos.database.pwd", libd_pw_dup, libc_pw_dup, TP, 1, TP)

/* readpassphrase */
DFUN(".text.crt.dos.bsd", libd_readpassphrase, libc_readpassphrase, TP, 4, TP, TP, TI, TD)

/* regex */
DFUN(".text.crt.dos.utility.regex", libd_re_set_syntax, libc_re_set_syntax, TIn(__SIZEOF_REG_SYNTAX_T__), 1, TIn(__SIZEOF_REG_SYNTAX_T__))
DFUN(".text.crt.dos.utility.regex", libd_re_compile_pattern, libc_re_compile_pattern, TP, 3, TP, TI, TP)
DFUN(".text.crt.dos.utility.regex", libd_re_compile_fastmap, libc_re_compile_fastmap, TD, 1, TP)
DFUN(".text.crt.dos.utility.regex", libd_re_search, libc_re_search, TD, 6, TP, TP, TD, TD, TD, TP)
DFUN(".text.crt.dos.utility.regex", libd_re_search_2, libc_re_search_2, TD, 9, TP, TP, TD, TP, TD, TD, TD, TP, TD)
DFUN(".text.crt.dos.utility.regex", libd_re_match, libc_re_match, TD, 5, TP, TP, TD, TD, TP)
DFUN(".text.crt.dos.utility.regex", libd_re_match_2, libc_re_match_2, TD, 8, TP, TP, TD, TP, TD, TD, TP, TD)
DFUN(".text.crt.dos.utility.regex", libd_re_set_registers, libc_re_set_registers, TV, 5, TP, TP, TD, TP, TP)
DFUN(".text.crt.dos.utility.regex", libd_regcomp, libc_regcomp, TD, 3, TP, TP, TD)
DFUN(".text.crt.dos.utility.regex", libd_regexec, libc_regexec, TD, 5, TP, TP, TI, TP, TD)
DFUN(".text.crt.dos.utility.regex", libd_regerror, libc_regerror, TI, 4, TD, TP, TP, TI)
DFUN(".text.crt.dos.utility.regex", libd_regfree, libc_regfree, TV, 1, TP)
DFUN(".text.crt.dos.utility.regex", libd_regerrordesc_np, libc_regerrordesc_np, TP, 1, TD)
DFUN(".text.crt.compat.glibc.regex", libd_re_comp, libc_re_comp, TP, 1, TP)
DFUN(".text.crt.compat.glibc.regex", libd_re_exec, libc_re_exec, TD, 1, TP)
DFUN(".text.crt.dos.utility.regex", libd_regsubprintv, libc_regsubprintv, TI, 6, TP, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.utility.regex", libd_regsubprint, libc_regsubprint, TI, 6, TP, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.utility.regex", libd_regnsub, libc_regnsub, TI, 5, TP, TI, TP, TP, TP)
DFUN(".text.crt.dos.utility.regex", libd_regasub, libc_regasub, TI, 4, TP, TP, TP, TP)

/* regexp */
DFUN(".text.crt.dos.compat.glibc.regex", libd_step, libc_step, TD, 2, TP, TP)
DFUN(".text.crt.dos.compat.glibc.regex", libd_advance, libc_advance, TD, 2, TP, TP)

/* resolv */
DFUN(".text.crt.dos.net.nameser", libd_fp_nquery, libc_fp_nquery, TV, 3, TP, TD, TP)
DFUN(".text.crt.dos.net.nameser", libd_fp_query, libc_fp_query, TV, 2, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_hostalias, libc_hostalias, TP, 1, TP)
DFUN(".text.crt.dos.net.nameser", libd_p_query, libc_p_query, TV, 1, TP)
DFUN(".text.crt.dos.net.nameser", libd_res_isourserver, libc_res_isourserver, TD, 1, TP)
DFUN(".text.crt.dos.net.nameser", libd_res_mkquery, libc_res_mkquery, TD, 9, TD, TP, TD, TD, TP, TD, TP, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_res_query, libc_res_query, TD, 5, TP, TD, TD, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_res_querydomain, libc_res_querydomain, TD, 6, TP, TP, TD, TD, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_res_search, libc_res_search, TD, 5, TP, TD, TD, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_res_send, libc_res_send, TD, 4, TP, TD, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_res_hnok, libc_res_hnok, TD, 1, TP)
DFUN(".text.crt.dos.net.nameser", libd_res_ownok, libc_res_ownok, TD, 1, TP)
DFUN(".text.crt.dos.net.nameser", libd_res_mailok, libc_res_mailok, TD, 1, TP)
DFUN(".text.crt.dos.net.nameser", libd_res_dnok, libc_res_dnok, TD, 1, TP)
DFUN(".text.crt.dos.net.nameser", libd_sym_ston, libc_sym_ston, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_sym_ntos, libc_sym_ntos, TP, 3, TP, TD, TP)
DFUN(".text.crt.dos.net.nameser", libd_sym_ntop, libc_sym_ntop, TP, 3, TP, TD, TP)
DFUN(".text.crt.dos.net.nameser", libd_b64_ntop, libc_b64_ntop, TD, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.net.nameser", libd_b64_pton, libc_b64_pton, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.net.nameser", libd_loc_aton, libc_loc_aton, TD, 2, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_loc_ntoa, libc_loc_ntoa, TP, 2, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_dn_skipname, libc_dn_skipname, TD, 2, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_p_class, libc_p_class, TP, 1, TD)
DFUN(".text.crt.dos.net.nameser", libd_p_time, libc_p_time, TP, 1, TI32)
DFUN(".text.crt.dos.net.nameser", libd_p_type, libc_p_type, TP, 1, TD)
DFUN(".text.crt.dos.net.nameser", libd_p_rcode, libc_p_rcode, TP, 1, TD)
DFUN(".text.crt.dos.net.nameser", libd_p_cdnname, libc_p_cdnname, TP, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.net.nameser", libd_p_cdname, libc_p_cdname, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_p_fqnname, libc_p_fqnname, TP, 5, TP, TP, TD, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_p_fqname, libc_p_fqname, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_p_option, libc_p_option, TP, 1, TL)
DFUN(".text.crt.dos.net.nameser", libd_p_secstodate, libc_p_secstodate, TP, 1, TL)
DFUN(".text.crt.dos.net.nameser", libd_dn_count_labels, libc_dn_count_labels, TD, 1, TP)
DFUN(".text.crt.dos.net.nameser", libd_dn_expand, libc_dn_expand, TD, 5, TP, TP, TP, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_res_nameinquery, libc_res_nameinquery, TD, 5, TP, TD, TD, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_res_queriesmatch, libc_res_queriesmatch, TD, 4, TP, TP, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_p_section, libc_p_section, TP, 2, TD, TD)
DFUN(".text.crt.dos.net.nameser", libd_res_ninit, libc_res_ninit, TD, 1, TP)
DFUN(".text.crt.dos.net.nameser", libd_res_nisourserver, libc_res_nisourserver, TD, 2, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_fp_resstat, libc_fp_resstat, TV, 2, TP, TP)
DFUN(".text.crt.dos.net.nameser", libd_res_npquery, libc_res_npquery, TV, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.net.nameser", libd_res_hostalias, libc_res_hostalias, TP, 4, TP, TP, TP, TI)
DFUN(".text.crt.dos.net.nameser", libd_res_nquery, libc_res_nquery, TD, 6, TP, TP, TD, TD, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_res_nsearch, libc_res_nsearch, TD, 6, TP, TP, TD, TD, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_res_nquerydomain, libc_res_nquerydomain, TD, 7, TP, TP, TP, TD, TD, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_res_nmkquery, libc_res_nmkquery, TD, 10, TP, TD, TP, TD, TD, TP, TD, TP, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_res_nsend, libc_res_nsend, TD, 5, TP, TP, TD, TP, TD)
DFUN(".text.crt.dos.net.nameser", libd_res_nclose, libc_res_nclose, TV, 1, TP)

/* rpc.netdb */
DFUN(".text.crt.dos.net.rpc", libd_setrpcent, libc_setrpcent, TV, 1, TD)
DFUN(".text.crt.dos.net.rpc", libd_getrpcbyname, libc_getrpcbyname, TP, 1, TP)
DFUN(".text.crt.dos.net.rpc", libd_getrpcbynumber, libc_getrpcbynumber, TP, 1, TD)
DFUN(".text.crt.dos.net.rpc", libd_getrpcbyname_r, libc_getrpcbyname_r, TD, 5, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.net.rpc", libd_getrpcbynumber_r, libc_getrpcbynumber_r, TD, 5, TD, TP, TP, TI, TP)
DFUN(".text.crt.dos.net.rpc", libd_getrpcent_r, libc_getrpcent_r, TD, 4, TP, TP, TI, TP)

/* sched */
DFUN(".text.crt.dos.sched.utility", libd_unshare, libc_unshare, TD, 1, TD)
DFUN(".text.crt.dos.sched.utility", libd_setns, libc_setns, TD, 2, TIn(__SIZEOF_FD_T__), TD)
DFUN(".text.crt.dos.sched.access", libd_exit_thread, libc_exit_thread, TV, 1, TD)
DFUN(".text.crt.dos.sched.param", libd_sched_setparam, libc_sched_setparam, TD, 2, TIn(__SIZEOF_PID_T__), TP)
DFUN(".text.crt.dos.sched.param", libd_sched_getparam, libc_sched_getparam, TD, 2, TIn(__SIZEOF_PID_T__), TP)
DFUN(".text.crt.dos.sched.param", libd_sched_setscheduler, libc_sched_setscheduler, TD, 3, TIn(__SIZEOF_PID_T__), TD, TP)
DFUN(".text.crt.dos.sched.param", libd_sched_getscheduler, libc_sched_getscheduler, TD, 1, TIn(__SIZEOF_PID_T__))
DFUN(".text.crt.dos.sched.param", libd_sched_get_priority_max, libc_sched_get_priority_max, TD, 1, TD)
DFUN(".text.crt.dos.sched.param", libd_sched_get_priority_min, libc_sched_get_priority_min, TD, 1, TD)
DFUN(".text.crt.dos.sched.param", libd_sched_setaffinity, libc_sched_setaffinity, TD, 3, TIn(__SIZEOF_PID_T__), TI, TP)
DFUN(".text.crt.dos.sched.param", libd_sched_getaffinity, libc_sched_getaffinity, TD, 3, TIn(__SIZEOF_PID_T__), TI, TP)
DFUN(".text.crt.dos.sched.param", libd_sched_rr_get_interval, libc_sched_rr_get_interval, TD, 2, TIn(__SIZEOF_PID_T__), TP)
DFUN(".text.crt.dos.sched.param", libd_sched_rr_get_interval64, libc_sched_rr_get_interval64, TD, 2, TIn(__SIZEOF_PID_T__), TP)

/* search */
DFUN(".text.crt.dos.utility.search", libd_insque, libc_insque, TV, 2, TP, TP)
DFUN(".text.crt.dos.utility.search", libd_remque, libc_remque, TV, 1, TP)
DFUN(".text.crt.dos.utility.search", libd_hsearch, libc_hsearch, TP, 2, TS(__SIZEOF_ENTRY), TD)
DFUN(".text.crt.dos.utility.search", libd_hcreate, libc_hcreate, TD, 1, TI)
DFUN(".text.crt.dos.utility.search", libd_hsearch_r, libc_hsearch_r, TD, 4, TS(__SIZEOF_ENTRY), TD, TP, TP)
DFUN(".text.crt.dos.utility.search", libd_hcreate_r, libc_hcreate_r, TD, 2, TI, TP)
DFUN(".text.crt.dos.utility.search", libd_hdestroy_r, libc_hdestroy_r, TV, 1, TP)

/* semaphore */
DFUN(".text.crt.dos.sched.semaphore", libd_sem_init, libc_sem_init, TD, 3, TP, TD, TD)
DFUN(".text.crt.dos.sched.semaphore", libd_sem_destroy, libc_sem_destroy, TD, 1, TP)
DFUN(".text.crt.dos.sched.semaphore", libd_sem_open, libc_sem_open, TP, 4, TP, TIn(__SIZEOF_OFLAG_T__), TIn(__SIZEOF_MODE_T__), TD)
DFUN(".text.crt.dos.sched.semaphore", libd_sem_close, libc_sem_close, TD, 1, TP)
DFUN(".text.crt.dos.sched.semaphore", libd_sem_unlink, libc_sem_unlink, TD, 1, TP)
DFUN(".text.crt.dos.sched.semaphore", libd_sem_wait, libc_sem_wait, TD, 1, TP)
DFUN(".text.crt.dos.sched.semaphore", libd_sem_timedwait, libc_sem_timedwait, TD, 2, TP, TP)
DFUN(".text.crt.dos.sched.semaphore", libd_sem_timedwait64, libc_sem_timedwait64, TD, 2, TP, TP)
DFUN(".text.crt.dos.sched.semaphore", libd_sem_trywait, libc_sem_trywait, TD, 1, TP)
DFUN(".text.crt.dos.sched.semaphore", libd_sem_post, libc_sem_post, TD, 1, TP)
DFUN(".text.crt.dos.sched.semaphore", libd_sem_post_multiple, libc_sem_post_multiple, TD, 2, TP, TD)
DFUN(".text.crt.dos.sched.semaphore", libd_sem_getvalue, libc_sem_getvalue, TD, 2, TP, TP)

/* sgtty */
DFUN(".text.crt.dos.database.utmpx", libd_gtty, libc_gtty, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.database.utmpx", libd_stty, libc_stty, TD, 2, TIn(__SIZEOF_FD_T__), TP)

/* shadow */
DFUN(".text.crt.dos.database.shadow", libd_getspnam, libc_getspnam, TP, 1, TP)
DFUN(".text.crt.dos.database.shadow", libd_fgetspent, libc_fgetspent, TP, 1, TP)
DFUN(".text.crt.dos.database.shadow", libd_sgetspent, libc_sgetspent, TP, 1, TP)
DFUN(".text.crt.dos.database.shadow", libd_putspent, libc_putspent, TD, 2, TP, TP)
DFUN(".text.crt.dos.database.shadow", libd_getspent_r, libc_getspent_r, TIn(__SIZEOF_ERRNO_T__), 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.database.shadow", libd_getspnam_r, libc_getspnam_r, TIn(__SIZEOF_ERRNO_T__), 5, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.database.shadow", libd_sgetspent_r, libc_sgetspent_r, TIn(__SIZEOF_ERRNO_T__), 5, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.database.shadow", libd_fgetspent_r, libc_fgetspent_r, TIn(__SIZEOF_ERRNO_T__), 5, TP, TP, TP, TI, TP)
DFUN(".text.crt.dos.database.shadow", libd_fgetspnam_r, libc_fgetspnam_r, TIn(__SIZEOF_ERRNO_T__), 6, TP, TP, TP, TP, TI, TP)

/* signal */
DFUN(".text.crt.dos.sched.signal", libd_tgkill, libc_tgkill, TD, 3, TIn(__SIZEOF_PID_T__), TIn(__SIZEOF_PID_T__), TIn(__SIZEOF_SIGNO_T__))
DFUN(".text.crt.dos.sched.signal", libd_sigblock, libc_sigblock, TD, 1, TD)
DFUN(".text.crt.dos.sched.signal", libd_sigsetmask, libc_sigsetmask, TD, 1, TD)
DFUN(".text.crt.dos.sched.signal", libd_sigpause, libc_sigpause, TD, 1, TD)
DFUN(".text.crt.dos.sched.signal", libd_sigreturn, libc_sigreturn, TV, 1, TP)
DFUN(".text.crt.dos.sched.signal", libd___xpg_sigpause, libc___xpg_sigpause, TD, 1, TIn(__SIZEOF_SIGNO_T__))
DFUN(".text.crt.dos.sched.signal", libd_kill, libc_kill, TD, 2, TIn(__SIZEOF_PID_T__), TIn(__SIZEOF_SIGNO_T__))
DFUN(".text.crt.dos.sched.signal", libd_sigemptyset, libc_sigemptyset, TD, 1, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigfillset, libc_sigfillset, TD, 1, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigaddset, libc_sigaddset, TD, 2, TP, TIn(__SIZEOF_SIGNO_T__))
DFUN(".text.crt.dos.sched.signal", libd_sigdelset, libc_sigdelset, TD, 2, TP, TIn(__SIZEOF_SIGNO_T__))
DFUN(".text.crt.dos.sched.signal", libd_sigismember, libc_sigismember, TD, 2, TP, TIn(__SIZEOF_SIGNO_T__))
DFUN(".text.crt.dos.sched.signal", libd_sigprocmask, libc_sigprocmask, TD, 3, TD, TP, TP)
DFUN(".text.crt.dos.sched.signal", libd_setsigmaskptr, libc_setsigmaskptr, TP, 1, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigsuspend, libc_sigsuspend, TD, 1, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigaction, libc_sigaction, TD, 3, TIn(__SIZEOF_SIGNO_T__), TP, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigpending, libc_sigpending, TD, 1, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigwait, libc_sigwait, TD, 2, TP, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigisemptyset, libc_sigisemptyset, TD, 1, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigandset, libc_sigandset, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigorset, libc_sigorset, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.signal", libd_signandset, libc_signandset, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigisfullset, libc_sigisfullset, TD, 1, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigwaitinfo, libc_sigwaitinfo, TD, 2, TP, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigtimedwait, libc_sigtimedwait, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigqueue, libc_sigqueue, TD, 3, TIn(__SIZEOF_PID_T__), TIn(__SIZEOF_SIGNO_T__), TS(__SIZEOF_SIGVAL CONST))
DFUN(".text.crt.dos.sched.signal", libd_sigtimedwait64, libc_sigtimedwait64, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigqueueinfo, libc_sigqueueinfo, TD, 3, TIn(__SIZEOF_PID_T__), TIn(__SIZEOF_SIGNO_T__), TP)
DFUN(".text.crt.dos.sched.signal", libd_tgsigqueueinfo, libc_tgsigqueueinfo, TD, 4, TIn(__SIZEOF_PID_T__), TIn(__SIZEOF_PID_T__), TIn(__SIZEOF_SIGNO_T__), TP)
DFUN(".text.crt.dos.sched.signal", libd_killpg, libc_killpg, TD, 2, TIn(__SIZEOF_PID_T__), TIn(__SIZEOF_SIGNO_T__))
DFUN(".text.crt.dos.sched.signal", libd_psignal, libc_psignal, TV, 2, TIn(__SIZEOF_SIGNO_T__), TP)
DFUN(".text.crt.dos.sched.signal", libd_psiginfo, libc_psiginfo, TV, 2, TP, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigcodename_np, libc_sigcodename_np, TP, 2, TIn(__SIZEOF_SIGNO_T__), TD)
DFUN(".text.crt.dos.sched.signal", libd_sigcodedesc_np, libc_sigcodedesc_np, TP, 2, TIn(__SIZEOF_SIGNO_T__), TD)
DFUN(".text.crt.dos.sched.signal", libd_siginterrupt, libc_siginterrupt, TD, 2, TIn(__SIZEOF_SIGNO_T__), TD)
DFUN(".text.crt.dos.sched.signal", libd_sigstack, libc_sigstack, TD, 2, TP, TP)
DFUN(".text.crt.dos.sched.signal", libd_sigaltstack, libc_sigaltstack, TD, 2, TP, TP)
DFUN(".text.crt.dos.sched.signal", libd_sighold, libc_sighold, TD, 1, TIn(__SIZEOF_SIGNO_T__))
DFUN(".text.crt.dos.sched.signal", libd_sigrelse, libc_sigrelse, TD, 1, TIn(__SIZEOF_SIGNO_T__))
DFUN(".text.crt.dos.sched.signal", libd_sigignore, libc_sigignore, TD, 1, TIn(__SIZEOF_SIGNO_T__))
DFUN(".text.crt.dos.sched.signal", libd_sigset, libc_sigset, TP, 2, TIn(__SIZEOF_SIGNO_T__), TP)
DFUN(".text.crt.dos.sched.signal", libd___libc_allocate_rtsig, libc___libc_allocate_rtsig, TIn(__SIZEOF_SIGNO_T__), 1, TD)
DFUN(".text.crt.dos.sched.signal", libd_pthread_kill, libc_pthread_kill, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TIn(__SIZEOF_SIGNO_T__))
DFUN(".text.crt.dos.sched.signal", libd_pthread_sigqueue, libc_pthread_sigqueue, TIn(__SIZEOF_ERRNO_T__), 3, TIn(__SIZEOF_PTHREAD_T), TIn(__SIZEOF_SIGNO_T__), TS(__SIZEOF_SIGVAL CONST))
DFUN(".text.crt.dos.sched.signal", libd_signalnumber, libc_signalnumber, TIn(__SIZEOF_SIGNO_T__), 1, TP)
DFUN(".text.crt.dos.sched.signal", libd_signalnext, libc_signalnext, TIn(__SIZEOF_SIGNO_T__), 1, TIn(__SIZEOF_SIGNO_T__))
DFUN(".text.crt.dos.solaris", libd_sig2str, libc_sig2str, TD, 2, TIn(__SIZEOF_SIGNO_T__), TP)
DFUN(".text.crt.dos.solaris", libd_str2sig, libc_str2sig, TD, 2, TP, TP)

/* sort */
DFUN(".text.crt.dos.libiberty", libd_sort_pointers, libc_sort_pointers, TV, 3, TI, TP, TP)

/* spawn */
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_fspawn_np, libc_posix_fspawn_np, TIn(__SIZEOF_ERRNO_T__), 6, TP, TIn(__SIZEOF_FD_T__), TP, TP, TP, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawn, libc_posix_spawn, TIn(__SIZEOF_ERRNO_T__), 6, TP, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnp, libc_posix_spawnp, TIn(__SIZEOF_ERRNO_T__), 6, TP, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_init, libc_posix_spawnattr_init, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_destroy, libc_posix_spawnattr_destroy, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_getflags, libc_posix_spawnattr_getflags, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_setflags, libc_posix_spawnattr_setflags, TIn(__SIZEOF_ERRNO_T__), 2, TP, TH)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_getsigdefault, libc_posix_spawnattr_getsigdefault, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_setsigdefault, libc_posix_spawnattr_setsigdefault, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_getsigmask, libc_posix_spawnattr_getsigmask, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_setsigmask, libc_posix_spawnattr_setsigmask, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_getpgroup, libc_posix_spawnattr_getpgroup, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_setpgroup, libc_posix_spawnattr_setpgroup, TIn(__SIZEOF_ERRNO_T__), 2, TP, TIn(__SIZEOF_PID_T__))
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_getschedpolicy, libc_posix_spawnattr_getschedpolicy, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_setschedpolicy, libc_posix_spawnattr_setschedpolicy, TIn(__SIZEOF_ERRNO_T__), 2, TP, TD)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_getschedparam, libc_posix_spawnattr_getschedparam, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawnattr_setschedparam, libc_posix_spawnattr_setschedparam, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawn_file_actions_init, libc_posix_spawn_file_actions_init, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawn_file_actions_destroy, libc_posix_spawn_file_actions_destroy, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawn_file_actions_addopen, libc_posix_spawn_file_actions_addopen, TIn(__SIZEOF_ERRNO_T__), 5, TP, TIn(__SIZEOF_FD_T__), TP, TIn(__SIZEOF_OFLAG_T__), TIn(__SIZEOF_MODE_T__))
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawn_file_actions_addclose, libc_posix_spawn_file_actions_addclose, TIn(__SIZEOF_ERRNO_T__), 2, TP, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawn_file_actions_adddup2, libc_posix_spawn_file_actions_adddup2, TIn(__SIZEOF_ERRNO_T__), 3, TP, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawn_file_actions_addtcsetpgrp_np, libc_posix_spawn_file_actions_addtcsetpgrp_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawn_file_actions_addclosefrom_np, libc_posix_spawn_file_actions_addclosefrom_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawn_file_actions_addchdir_np, libc_posix_spawn_file_actions_addchdir_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
DFUN(".text.crt.dos.fs.exec.posix_spawn", libd_posix_spawn_file_actions_addfchdir_np, libc_posix_spawn_file_actions_addfchdir_np, TIn(__SIZEOF_ERRNO_T__), 2, TP, TIn(__SIZEOF_FD_T__))

/* ssp.string */
DFUN(".text.crt.dos.ssp.string.memory", libd___memcpy_chk, libc___memcpy_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmove_chk, libc___memmove_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memset_chk, libc___memset_chk, TP, 4, TP, TD, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___strcat_chk, libc___strcat_chk, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___strcpy_chk, libc___strcpy_chk, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___strncat_chk, libc___strncat_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___strncpy_chk, libc___strncpy_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempcpy_chk, libc___mempcpy_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___stpcpy_chk, libc___stpcpy_chk, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___stpncpy_chk, libc___stpncpy_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmove_chk, libc___mempmove_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempset_chk, libc___mempset_chk, TP, 4, TP, TD, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmoveup_chk, libc___memmoveup_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmovedown_chk, libc___memmovedown_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmoveup_chk, libc___mempmoveup_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmovedown_chk, libc___mempmovedown_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memcpyc_chk, libc___memcpyc_chk, TP, 5, TP, TP, TI, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmovec_chk, libc___memmovec_chk, TP, 5, TP, TP, TI, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempcpyc_chk, libc___mempcpyc_chk, TP, 5, TP, TP, TI, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmovec_chk, libc___mempmovec_chk, TP, 5, TP, TP, TI, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmoveupc_chk, libc___memmoveupc_chk, TP, 5, TP, TP, TI, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmovedownc_chk, libc___memmovedownc_chk, TP, 5, TP, TP, TI, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmoveupc_chk, libc___mempmoveupc_chk, TP, 5, TP, TP, TI, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmovedownc_chk, libc___mempmovedownc_chk, TP, 5, TP, TP, TI, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memcpyw_chk, libc___memcpyw_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempcpyw_chk, libc___mempcpyw_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmovew_chk, libc___memmovew_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memcpyl_chk, libc___memcpyl_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempcpyl_chk, libc___mempcpyl_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmovel_chk, libc___memmovel_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmovew_chk, libc___mempmovew_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmovel_chk, libc___mempmovel_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memsetw_chk, libc___memsetw_chk, TP, 4, TP, TI16, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempsetw_chk, libc___mempsetw_chk, TP, 4, TP, TI16, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memsetl_chk, libc___memsetl_chk, TP, 4, TP, TI32, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempsetl_chk, libc___mempsetl_chk, TP, 4, TP, TI32, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmoveupw_chk, libc___memmoveupw_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmovedownw_chk, libc___memmovedownw_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmoveupl_chk, libc___memmoveupl_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmovedownl_chk, libc___memmovedownl_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmoveupw_chk, libc___mempmoveupw_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmovedownw_chk, libc___mempmovedownw_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmoveupl_chk, libc___mempmoveupl_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmovedownl_chk, libc___mempmovedownl_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memcpyq_chk, libc___memcpyq_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempcpyq_chk, libc___mempcpyq_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmoveq_chk, libc___memmoveq_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmoveq_chk, libc___mempmoveq_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memsetq_chk, libc___memsetq_chk, TP, 4, TP, TI64, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempsetq_chk, libc___mempsetq_chk, TP, 4, TP, TI64, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmoveupq_chk, libc___memmoveupq_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___memmovedownq_chk, libc___memmovedownq_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmoveupq_chk, libc___mempmoveupq_chk, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.ssp.string.memory", libd___mempmovedownq_chk, libc___mempmovedownq_chk, TP, 4, TP, TP, TI, TI)

/* stdio */
DFUN(".text.crt.dos.FILE.locked.access", libd_fclose, libc_fclose, TD, 1, TP)
DFUN(".text.crt.dos.FILE.locked.write.utility", libd_fflush, libc_fflush, TD, 1, TP)
DFUN(".text.crt.dos.FILE.locked.read.utility", libd_setbuf, libc_setbuf, TV, 2, TP, TP)
DFUN(".text.crt.dos.FILE.locked.read.utility", libd_setvbuf, libc_setvbuf, TD, 4, TP, TP, TD, TI)
DFUN(".text.crt.dos.FILE.locked.read.getc", libd_fgetc, libc_fgetc, TD, 1, TP)
DFUN(".text.crt.dos.FILE.locked.write.putc", libd_fputc, libc_fputc, TD, 2, TD, TP)
DFUN(".text.crt.dos.FILE.locked.write.putc", libd_putchar, libc_putchar, TD, 1, TD)
DFUN(".text.crt.dos.FILE.locked.read.read", libd_fgets, libc_fgets, TP, 3, TP, TD, TP)
DFUN(".text.crt.dos.FILE.locked.write.write", libd_fputs, libc_fputs, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.locked.write.write", libd_puts, libc_puts, TD, 1, TP)
DFUN(".text.crt.dos.FILE.locked.read.getc", libd_ungetc, libc_ungetc, TD, 2, TD, TP)
DFUN(".text.crt.dos.FILE.locked.read.read", libd_fread, libc_fread, TI, 4, TP, TI, TI, TP)
DFUN(".text.crt.dos.FILE.locked.write.write", libd_fwrite, libc_fwrite, TI, 4, TP, TI, TI, TP)
DFUN(".text.crt.dos.FILE.locked.seek.seek", libd_fseek, libc_fseek, TD, 3, TP, TL, TD)
DFUN(".text.crt.dos.FILE.locked.seek.seek", libd_ftell, libc_ftell, TL, 1, TP)
DFUN(".text.crt.dos.FILE.locked.seek.utility", libd_rewind, libc_rewind, TV, 1, TP)
DFUN(".text.crt.dos.FILE.locked.access", libd_clearerr, libc_clearerr, TV, 1, TP)
DFUN(".text.crt.dos.FILE.locked.read.utility", libd_feof, libc_feof, TD, 1, TP)
DFUN(".text.crt.dos.FILE.locked.utility", libd_ferror, libc_ferror, TD, 1, TP)
DFUN(".text.crt.dos.errno.utility", libd_perror, libc_perror, TV, 1, TP)
DFUN(".text.crt.dos.FILE.locked.seek.pos", libd_fgetpos, libc_fgetpos, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.locked.seek.pos", libd_fsetpos, libc_fsetpos, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.locked.write.printf", libd_vfprintf, libc_vfprintf, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.FILE.locked.write.printf", libd_vprintf, libc_vprintf, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.locked.read.scanf", libd_vfscanf, libc_vfscanf, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.FILE.locked.read.scanf", libd_vscanf, libc_vscanf, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.locked.read.read", libd_gets, libc_gets, TP, 1, TP)
DFUN(".text.crt.dos.unicode.static.format.scanf", libd_vsscanf, libc_vsscanf, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.unicode.static.format.printf", libd_vsprintf, libc_vsprintf, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.unicode.static.format.printf", libd_vsnprintf, libc_vsnprintf, TD, 4, TP, TI, TP, TP)
DFUN(".text.crt.dos.io.write", libd_vdprintf, libc_vdprintf, TD, 3, TIn(__SIZEOF_FD_T__), TP, TP)
DFUN(".text.crt.dos.fs.utility", libd_tmpnam_r, libc_tmpnam_r, TP, 1, TP)
DFUN(".text.crt.dos.FILE.locked.read.utility", libd_setbuffer, libc_setbuffer, TV, 3, TP, TP, TI)
DFUN(".text.crt.dos.FILE.locked.read.utility", libd_setlinebuf, libc_setlinebuf, TV, 1, TP)
DFUN(".text.crt.dos.FILE.unlocked.write.utility", libd_fflush_unlocked, libc_fflush_unlocked, TD, 1, TP)
DFUN(".text.crt.dos.FILE.unlocked.read.read", libd_fread_unlocked, libc_fread_unlocked, TI, 4, TP, TI, TI, TP)
DFUN(".text.crt.dos.FILE.unlocked.write.write", libd_fwrite_unlocked, libc_fwrite_unlocked, TI, 4, TP, TI, TI, TP)
DFUN(".text.crt.dos.FILE.unlocked.read.getc", libd_fgetc_unlocked, libc_fgetc_unlocked, TD, 1, TP)
DFUN(".text.crt.dos.FILE.unlocked.write.putc", libd_fputc_unlocked, libc_fputc_unlocked, TD, 2, TD, TP)
DFUN(".text.crt.dos.FILE.unlocked.write.putc", libd_vasnprintf, libc_vasnprintf, TP, 4, TP, TP, TP, TP)
DFUN(".text.crt.dos.fs.utility", libd_tempnam, libc_tempnam, TP, 2, TP, TP)
DFUN(".text.crt.dos.FILE.locked.utility", libd_fdopen, libc_fdopen, TP, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.FILE.locked.utility", libd_fileno, libc_fileno, TIn(__SIZEOF_FD_T__), 1, TP)
DFUN(".text.crt.dos.FILE.locked.access", libd_fmemopen, libc_fmemopen, TP, 3, TP, TI, TP)
DFUN(".text.crt.dos.FILE.locked.access", libd_open_memstream, libc_open_memstream, TP, 2, TP, TP)
DFUN(".text.crt.dos.FILE.locked.read.read", libd_getdelim, libc_getdelim, TI, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.FILE.locked.read.read", libd_getline, libc_getline, TI, 3, TP, TP, TP)
DFUN(".text.crt.dos.FILE.unlocked.write.putc", libd_putchar_unlocked, libc_putchar_unlocked, TD, 1, TD)
DFUN(".text.crt.dos.FILE.locked.utility", libd_flockfile, libc_flockfile, TV, 1, TP)
DFUN(".text.crt.dos.FILE.locked.utility", libd_funlockfile, libc_funlockfile, TV, 1, TP)
DFUN(".text.crt.dos.FILE.locked.utility", libd_ftrylockfile, libc_ftrylockfile, TD, 1, TP)
DFUN(".text.crt.dos.FILE.locked.write.write", libd___overflow, libc___overflow, TD, 2, TP, TD)
DFUN(".text.crt.dos.FILE.utility.popen", libd_popen, libc_popen, TP, 2, TP, TP)
DFUN(".text.crt.dos.FILE.utility.popen", libd_pclose, libc_pclose, TD, 1, TP)
DFUN(".text.crt.dos.FILE.utility.popen", libd_popenve, libc_popenve, TP, 4, TP, TP, TP, TP)
DFUN(".text.crt.dos.FILE.locked.read.getc", libd_getw, libc_getw, TD, 1, TP)
DFUN(".text.crt.dos.FILE.locked.write.putc", libd_putw, libc_putw, TD, 2, TD, TP)
DFUN(".text.crt.dos.FILE.locked.access", libd_fopencookie, libc_fopencookie, TP, 3, TP, TP, TS(__SIZEOF_COOKIE_IO_FUNCTIONS_T))
DFUN(".text.crt.dos.FILE.unlocked.read.read", libd_fgets_unlocked, libc_fgets_unlocked, TP, 3, TP, TD, TP)
DFUN(".text.crt.dos.FILE.unlocked.write.write", libd_fputs_unlocked, libc_fputs_unlocked, TD, 2, TP, TP)
DFUN(".text.crt.dos.heap.obstack", libd_obstack_vprintf, libc_obstack_vprintf, TD, 3, TP, TP, TP)
#include <features.h>
#include <bits/types.h>
#if __SIZEOF_OFF_T__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libd_fseeko, libd_fseek);
#else /* __SIZEOF_OFF_T__ == __SIZEOF_LONG__ */
DFUN(".text.crt.dos.FILE.locked.seek.seek", libd_fseeko, libc_fseeko, TD, 3, TP, TIn(__SIZEOF_OFF_T__), TD)
#endif /* __SIZEOF_OFF_T__ != __SIZEOF_LONG__ */
#if __SIZEOF_OFF_T__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libd_ftello, libd_ftell);
#else /* __SIZEOF_OFF_T__ == __SIZEOF_LONG__ */
DFUN(".text.crt.dos.FILE.locked.seek.seek", libd_ftello, libc_ftello, TIn(__SIZEOF_OFF_T__), 1, TP)
#endif /* __SIZEOF_OFF_T__ != __SIZEOF_LONG__ */
DFUN(".text.crt.dos.FILE.locked.seek.seek", libd_fseeko64, libc_fseeko64, TD, 3, TP, TIn(__SIZEOF_OFF64_T__), TD)
DFUN(".text.crt.dos.FILE.locked.seek.seek", libd_ftello64, libc_ftello64, TIn(__SIZEOF_OFF64_T__), 1, TP)
DFUN(".text.crt.dos.FILE.locked.seek.pos", libd_fgetpos64, libc_fgetpos64, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.locked.seek.pos", libd_fsetpos64, libc_fsetpos64, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.locked.access", libd_fopen_printer, libc_fopen_printer, TP, 2, TP, TP)
DFUN(".text.crt.dos.heap.strdup", libd_vasprintf, libc_vasprintf, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.FILE.locked.access", libd_fdreopen, libc_fdreopen, TP, 3, TIn(__SIZEOF_FD_T__), TP, TP)
DFUN(".text.crt.dos.FILE.unlocked.access", libd_fdreopen_unlocked, libc_fdreopen_unlocked, TP, 3, TIn(__SIZEOF_FD_T__), TP, TP)
DFUN(".text.crt.dos.FILE.unlocked.seek.seek", libd_fseek_unlocked, libc_fseek_unlocked, TD, 3, TP, TL, TD)
DFUN(".text.crt.dos.FILE.unlocked.seek.seek", libd_ftell_unlocked, libc_ftell_unlocked, TL, 1, TP)
#if __SIZEOF_OFF_T__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libd_fseeko_unlocked, libd_fseek_unlocked);
#else /* __SIZEOF_OFF_T__ == __SIZEOF_LONG__ */
DFUN(".text.crt.dos.FILE.unlocked.seek.seek", libd_fseeko_unlocked, libc_fseeko_unlocked, TD, 3, TP, TIn(__SIZEOF_OFF_T__), TD)
#endif /* __SIZEOF_OFF_T__ != __SIZEOF_LONG__ */
#if __SIZEOF_OFF_T__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libd_ftello_unlocked, libd_ftell_unlocked);
#else /* __SIZEOF_OFF_T__ == __SIZEOF_LONG__ */
DFUN(".text.crt.dos.FILE.unlocked.seek.seek", libd_ftello_unlocked, libc_ftello_unlocked, TIn(__SIZEOF_OFF_T__), 1, TP)
#endif /* __SIZEOF_OFF_T__ != __SIZEOF_LONG__ */
DFUN(".text.crt.dos.FILE.unlocked.seek.pos", libd_fgetpos_unlocked, libc_fgetpos_unlocked, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.unlocked.seek.pos", libd_fsetpos_unlocked, libc_fsetpos_unlocked, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.unlocked.read.getc", libd_getw_unlocked, libc_getw_unlocked, TD, 1, TP)
DFUN(".text.crt.dos.FILE.unlocked.write.putc", libd_putw_unlocked, libc_putw_unlocked, TD, 2, TD, TP)
DFUN(".text.crt.dos.FILE.unlocked.read.utility", libd_setvbuf_unlocked, libc_setvbuf_unlocked, TD, 4, TP, TP, TD, TI)
DFUN(".text.crt.dos.FILE.unlocked.read.getc", libd_ungetc_unlocked, libc_ungetc_unlocked, TD, 2, TD, TP)
DFUN(".text.crt.dos.FILE.unlocked.read.read", libd_getdelim_unlocked, libc_getdelim_unlocked, TI, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.FILE.unlocked.read.read", libd_getline_unlocked, libc_getline_unlocked, TI, 3, TP, TP, TP)
DFUN(".text.crt.dos.FILE.unlocked.seek.utility", libd_rewind_unlocked, libc_rewind_unlocked, TV, 1, TP)
DFUN(".text.crt.dos.io.tty", libd_fisatty, libc_fisatty, TD, 1, TP)
DFUN(".text.crt.dos.FILE.locked.utility", libd_frelease, libc_frelease, TIn(__SIZEOF_FD_T__), 1, TP)
DFUN(".text.crt.dos.FILE.locked.utility", libd_fftruncate, libc_fftruncate, TD, 2, TP, TIn(__SIZEOF_OFF32_T__))
DFUN(".text.crt.dos.FILE.unlocked.utility", libd_fftruncate_unlocked, libc_fftruncate_unlocked, TD, 2, TP, TIn(__SIZEOF_OFF32_T__))
DFUN(".text.crt.dos.FILE.unlocked.write.write", libd_puts_unlocked, libc_puts_unlocked, TD, 1, TP)
DFUN(".text.crt.dos.FILE.unlocked.seek.seek", libd_fseeko64_unlocked, libc_fseeko64_unlocked, TD, 3, TP, TIn(__SIZEOF_OFF64_T__), TD)
DFUN(".text.crt.dos.FILE.unlocked.seek.seek", libd_ftello64_unlocked, libc_ftello64_unlocked, TIn(__SIZEOF_OFF64_T__), 1, TP)
DFUN(".text.crt.dos.FILE.unlocked.seek.pos", libd_fgetpos64_unlocked, libc_fgetpos64_unlocked, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.unlocked.seek.pos", libd_fsetpos64_unlocked, libc_fsetpos64_unlocked, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.locked.utility", libd_fftruncate64, libc_fftruncate64, TD, 2, TP, TIn(__SIZEOF_OFF64_T__))
DFUN(".text.crt.dos.FILE.unlocked.utility", libd_fftruncate64_unlocked, libc_fftruncate64_unlocked, TD, 2, TP, TIn(__SIZEOF_OFF64_T__))
DFUN(".text.crt.dos.FILE.unlocked.write.printf", libd_vfprintf_unlocked, libc_vfprintf_unlocked, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.FILE.unlocked.write.printf", libd_vprintf_unlocked, libc_vprintf_unlocked, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.unlocked.read.scanf", libd_vfscanf_unlocked, libc_vfscanf_unlocked, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.FILE.unlocked.read.scanf", libd_vscanf_unlocked, libc_vscanf_unlocked, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.unlocked.read.scanf", libd_fmtcheck, libc_fmtcheck, TP, 2, TP, TP)
DFUN(".text.crt.dos.FILE.unlocked.read.scanf", libd_fgetln, libc_fgetln, TP, 2, TP, TP)
DFUN(".text.crt.dos.FILE.locked.utility", libd_funopen, libc_funopen, TP, 5, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.FILE.locked.utility", libd_funopen2, libc_funopen2, TP, 6, TP, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.FILE.locked.utility", libd_funopen64, libc_funopen64, TP, 5, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.FILE.locked.utility", libd_funopen2_64, libc_funopen2_64, TP, 6, TP, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.FILE.locked.read.read", libd__filbuf, libc__filbuf, TD, 1, TP)
DFUN(".text.crt.dos.FILE.locked.write.write", libd__flsbuf, libc__flsbuf, TD, 2, TD, TP)
DFUN(".text.crt.dos.FILE.utility", libd__setmaxstdio, libc__setmaxstdio, TD, 1, TD)
DFUN(".text.crt.dos.FILE.utility", libd__set_printf_count_output, libc__set_printf_count_output, TD, 1, TD)
DFUN(".text.crt.dos.FILE.utility", libd__set_output_format, libc__set_output_format, TI32, 1, TI32)
DFUN(".text.crt.dos.fs.utility", libd_tmpnam_s, libc_tmpnam_s, TIn(__SIZEOF_ERRNO_T__), 2, TP, TI)
DFUN(".text.crt.dos.FILE.locked.utility", libd_clearerr_s, libc_clearerr_s, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.FILE.locked.access", libd_tmpfile_s, libc_tmpfile_s, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.FILE.locked.read.read", libd_fread_s, libc_fread_s, TI, 5, TP, TI, TI, TI, TP)
DFUN(".text.crt.dos.FILE.locked.read.read", libd_gets_s, libc_gets_s, TP, 2, TP, TI)
DFUN(".text.crt.dos.FILE.unlocked.read.read", libd__fread_nolock_s, libc__fread_nolock_s, TI, 5, TP, TI, TI, TI, TP)
DFUN(".text.crt.dos.unicode.locale.format.printf", libd___stdio_common_vfprintf, libc___stdio_common_vfprintf, TD, 5, TI64, TP, TP, TP, TP)
DEFINE_INTERN_ALIAS(libd___stdio_common_vfprintf_s, libd___stdio_common_vfprintf);
DEFINE_INTERN_ALIAS(libd___stdio_common_vfprintf_p, libd___stdio_common_vfprintf);
DFUN(".text.crt.dos.unicode.locale.format.printf", libd___stdio_common_vsprintf, libc___stdio_common_vsprintf, TD, 6, TI64, TP, TI, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.format.printf", libd___stdio_common_vsprintf_s, libc___stdio_common_vsprintf_s, TD, 6, TI64, TP, TI, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.format.printf", libd___stdio_common_vsnprintf_s, libc___stdio_common_vsnprintf_s, TD, 7, TI64, TP, TI, TI, TP, TP, TP)
DEFINE_INTERN_ALIAS(libd___stdio_common_vsprintf_p, libd___stdio_common_vsprintf);
DFUN(".text.crt.dos.FILE.locked.read.scanf", libd___stdio_common_vfscanf, libc___stdio_common_vfscanf, TD, 5, TI64, TP, TP, TP, TP)
DFUN(".text.crt.dos.FILE.locked.read.scanf", libd___stdio_common_vsscanf, libc___stdio_common_vsscanf, TD, 6, TI64, TP, TI, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.format.printf", libd__vsnprintf_l, libc__vsnprintf_l, TD, 5, TP, TI, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.format.printf", libd__vsprintf_s_l, libc__vsprintf_s_l, TD, 5, TP, TI, TP, TP, TP)
DEFINE_INTERN_ALIAS(libd__vsprintf_p_l, libd__vsnprintf_l);
DFUN(".text.crt.dos.unicode.locale.format.printf", libd__vscprintf_l, libc__vscprintf_l, TD, 3, TP, TP, TP)
DEFINE_INTERN_ALIAS(libd__vscprintf_p_l, libd__vscprintf_l);
DFUN(".text.crt.dos.unicode.locale.format.printf", libd__vsnprintf_c_l, libc__vsnprintf_c_l, TD, 5, TP, TI, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.format.printf", libd__vsnprintf_s_l, libc__vsnprintf_s_l, TD, 6, TP, TI, TI, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.format.printf", libd__vfprintf_s_l, libc__vfprintf_s_l, TD, 4, TP, TP, TP, TP)
DEFINE_INTERN_ALIAS(libd__vfprintf_p_l, libd__vfprintf_l);
DFUN(".text.crt.dos.FILE.locked.read.scanf", libd__vfscanf_l, libc__vfscanf_l, TD, 4, TP, TP, TP, TP)
DEFINE_INTERN_ALIAS(libd__vfscanf_s_l, libd__vfscanf_l);
DFUN(".text.crt.dos.FILE.locked.read.scanf", libd__vsnscanf_l, libc__vsnscanf_l, TD, 5, TP, TI, TP, TP, TP)
DEFINE_INTERN_ALIAS(libd__vsnscanf_s_l, libd__vsnscanf_l);
DFUN(".text.crt.dos.unicode.locale.format.printf", libd__vprintf_l, libc__vprintf_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.format.printf", libd__vfprintf_l, libc__vfprintf_l, TD, 4, TP, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.format.printf", libd__vscanf_l, libc__vscanf_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.format.printf", libd__vsprintf_l, libc__vsprintf_l, TD, 4, TP, TP, TP, TP)
DEFINE_INTERN_ALIAS(libd__vfprintf_p, libd_vfprintf);
DEFINE_INTERN_ALIAS(libd__vprintf_p, libd_vprintf);
DFUN(".text.crt.dos.unicode.static.format.printf", libd__vsnprintf, libc__vsnprintf, TD, 4, TP, TI, TP, TP)
DEFINE_INTERN_ALIAS(libd__vsprintf_p, libd_vsnprintf);
DFUN(".text.crt.dos.unicode.static.format.printf", libd__vsnprintf_s, libc__vsnprintf_s, TD, 5, TP, TI, TI, TP, TP)
DFUN(".text.crt.dos.unicode.static.format.printf", libd__vscprintf, libc__vscprintf, TD, 2, TP, TP)
DEFINE_INTERN_ALIAS(libd__vscprintf_p, libd__vscprintf);
DFUN(".text.crt.dos.unicode.static.format.printf", libd__vsnprintf_c, libc__vsnprintf_c, TD, 4, TP, TI, TP, TP)
DFUN(".text.crt.dos.FILE.locked.read.scanf", libd__vsscanf_l, libc__vsscanf_l, TD, 4, TP, TP, TP, TP)
DEFINE_INTERN_ALIAS(libd__vsscanf_s_l, libd__vsscanf_l);
DFUN(".text.crt.dos.FILE.locked.read.scanf", libd__vsnscanf, libc__vsnscanf, TD, 4, TP, TI, TP, TP)
DEFINE_INTERN_ALIAS(libd__vsnscanf_s, libd__vsnscanf);
DFUN(".text.crt.dos.unicode.locale.format.printf", libd__vprintf_s_l, libc__vprintf_s_l, TD, 3, TP, TP, TP)
DEFINE_INTERN_ALIAS(libd__vprintf_p_l, libd__vprintf_l);
DFUN(".text.crt.dos.FILE.locked.read.scanf", libd__vscanf_s_l, libc__vscanf_s_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.unicode.static.format.printf", libd_vfprintf_s, libc_vfprintf_s, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.unicode.static.format.printf", libd_vprintf_s, libc_vprintf_s, TD, 2, TP, TP)
DFUN(".text.crt.dos.unicode.static.format.printf", libd_vsprintf_s, libc_vsprintf_s, TD, 4, TP, TI, TP, TP)
DFUN(".text.crt.dos.unicode.static.format.printf", libd_vsnprintf_s, libc_vsnprintf_s, TD, 5, TP, TI, TI, TP, TP)
DFUN(".text.crt.dos.FILE.locked.read.scanf", libd_vfscanf_s, libc_vfscanf_s, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.FILE.locked.read.scanf", libd_vscanf_s, libc_vscanf_s, TD, 2, TP, TP)
DFUN(".text.crt.dos.FILE.locked.read.scanf", libd_vsscanf_s, libc_vsscanf_s, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.compat.linux", libd__doprnt, libc__doprnt, TD, 3, TP, TP, TP)

/* stdio_ext */
DFUN(".text.crt.dos.FILE.utility.ext", libd___fbufsize, libc___fbufsize, TI, 1, TP)
DFUN(".text.crt.dos.FILE.utility.ext", libd___freading, libc___freading, TD, 1, TP)
DFUN(".text.crt.dos.FILE.utility.ext", libd___fwriting, libc___fwriting, TD, 1, TP)
DFUN(".text.crt.dos.FILE.utility.ext", libd___freadable, libc___freadable, TD, 1, TP)
DFUN(".text.crt.dos.FILE.utility.ext", libd___fwritable, libc___fwritable, TD, 1, TP)
DFUN(".text.crt.dos.FILE.utility.ext", libd___flbf, libc___flbf, TD, 1, TP)
DFUN(".text.crt.dos.FILE.utility.ext", libd___fpurge, libc___fpurge, TV, 1, TP)
DFUN(".text.crt.dos.FILE.utility.ext", libd___fpending, libc___fpending, TI, 1, TP)
DFUN(".text.crt.dos.FILE.utility.ext", libd___fpending_unlocked, libc___fpending_unlocked, TI, 1, TP)
DFUN(".text.crt.dos.FILE.utility.ext", libd___fsetlocking, libc___fsetlocking, TD, 2, TP, TD)
DFUN(".text.crt.dos.FILE.utility.ext", libd___fseterr, libc___fseterr, TV, 1, TP)
DFUN(".text.crt.dos.FILE.utility.ext", libd___freadahead, libc___freadahead, TI, 1, TP)
DFUN(".text.crt.dos.FILE.utility.ext", libd___freadahead_unlocked, libc___freadahead_unlocked, TI, 1, TP)
DFUN(".text.crt.dos.FILE.utility.ext", libd___freadptr, libc___freadptr, TP, 2, TP, TP)
DFUN(".text.crt.dos.FILE.utility.ext", libd___freadptrinc, libc___freadptrinc, TV, 2, TP, TI)

/* stdlib */
DFUN(".text.crt.dos.math.utility", libd_abs, libc_abs, TD, 1, TD)
DFUN(".text.crt.dos.math.utility", libd_labs, libc_labs, TL, 1, TL)
DFUN(".text.crt.dos.math.utility", libd_div, libc_div, TS(__SIZEOF_DIV_STRUCT), 2, TD, TD)
DFUN(".text.crt.dos.math.utility", libd_ldiv, libc_ldiv, TS(__SIZEOF_LDIV_STRUCT), 2, TL, TL)
DFUN(".text.crt.dos.math.utility", libd_llabs, libc_llabs, TLL, 1, TLL)
DFUN(".text.crt.dos.math.utility", libd_lldiv, libc_lldiv, TS(__SIZEOF_LLDIV_STRUCT), 2, TLL, TLL)
DFUN(".text.crt.dos.wchar.unicode.static.mbs", libd_mblen, libc_mblen, TD, 2, TP, TI)
DFUN(".text.crt.dos.fs.exec.system", libd_system, libc_system, TD, 1, TP)
DFUN(".text.crt.dos.application.exit", libd_exit, libc_exit, TV, 1, TD)
DFUN(".text.crt.dos.sched.process", libd_atexit, libc_atexit, TD, 1, TP)
DFUN(".text.crt.dos.sched.process", libd_quick_exit, libc_quick_exit, TV, 1, TD)
DFUN(".text.crt.dos.sched.process", libd_at_quick_exit, libc_at_quick_exit, TD, 1, TP)
DFUN(".text.crt.dos.application.exit", libd__Exit, libc__Exit, TV, 1, TD)
DFUN(".text.crt.dos.heap.malloc", libd_malloc, libc_malloc, TP, 1, TI)
DFUN(".text.crt.dos.heap.malloc", libd_calloc, libc_calloc, TP, 2, TI, TI)
DFUN(".text.crt.dos.heap.malloc", libd_realloc, libc_realloc, TP, 2, TP, TI)
DFUN(".text.crt.dos.heap.malloc", libd_free, libc_free, TV, 1, TP)
DFUN(".text.crt.dos.random", libd_srand, libc_srand, TV, 1, TL)
DFUN(".text.crt.dos.unicode.static.convert", libd_atoi, libc_atoi, TD, 1, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_atol, libc_atol, TL, 1, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtol, libc_strtol, TL, 3, TP, TP, TD)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtoul, libc_strtoul, TL, 3, TP, TP, TD)
DFUN(".text.crt.dos.unicode.static.convert", libd_atoll, libc_atoll, TLL, 1, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtoll, libc_strtoll, TLL, 3, TP, TP, TD)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtoull, libc_strtoull, TLL, 3, TP, TP, TD)
DFUN(".text.crt.dos.unicode.static.convert", libd_atof, libc_atof, TFD, 1, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtod, libc_strtod, TFD, 2, TP, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtof, libc_strtof, TF, 2, TP, TP)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_strtold, libd_strtod);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unicode.static.convert", libd_strtold, libc_strtold, TFL, 2, TP, TP)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unsorted", libd_strfromd, libc_strfromd, TI32, 4, TP, TI, TP, TFD)
DFUN(".text.crt.dos.unsorted", libd_strfromf, libc_strfromf, TI32, 4, TP, TI, TP, TF)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_strfroml, libd_strfromd);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unsorted", libd_strfroml, libc_strfroml, TI32, 4, TP, TI, TP, TFL)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unicode.static.convert", libd_strtou32_r, libc_strtou32_r, TI32, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strto32_r, libc_strto32_r, TI32, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtou64_r, libc_strtou64_r, TI64, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strto64_r, libc_strto64_r, TI64, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtou32, libc_strtou32, TI32, 3, TP, TP, TD)
DFUN(".text.crt.dos.unicode.static.convert", libd_strto32, libc_strto32, TI32, 3, TP, TP, TD)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtou64, libc_strtou64, TI64, 3, TP, TP, TD)
DFUN(".text.crt.dos.unicode.static.convert", libd_strto64, libc_strto64, TI64, 3, TP, TP, TD)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtou32_l, libc_strtou32_l, TI32, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strto32_l, libc_strto32_l, TI32, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtou64_l, libc_strtou64_l, TI64, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strto64_l, libc_strto64_l, TI64, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_gcvt, libc_gcvt, TP, 3, TFD, TD, TP)
DFUN(".text.crt.dos.random", libd_rand_r, libc_rand_r, TD, 1, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_ecvt_r, libc_ecvt_r, TD, 6, TFD, TD, TP, TP, TP, TI)
DFUN(".text.crt.dos.unicode.static.convert", libd_fcvt_r, libc_fcvt_r, TD, 6, TFD, TD, TP, TP, TP, TI)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_qgcvt, libd_gcvt);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unicode.static.convert", libd_qgcvt, libc_qgcvt, TP, 3, TFL, TD, TP)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_qecvt_r, libd_ecvt_r);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unicode.static.convert", libd_qecvt_r, libc_qecvt_r, TD, 6, TFL, TD, TP, TP, TP, TI)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_qfcvt_r, libd_fcvt_r);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unicode.static.convert", libd_qfcvt_r, libc_qfcvt_r, TD, 6, TFL, TD, TP, TP, TP, TI)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_qecvt, libd_ecvt);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unicode.static.convert", libd_qecvt, libc_qecvt, TP, 4, TFL, TD, TP, TP)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_qfcvt, libd_fcvt);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unicode.static.convert", libd_qfcvt, libc_qfcvt, TP, 4, TFL, TD, TP, TP)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.system.utility", libd_getloadavg, libc_getloadavg, TD, 2, TP, TD)
DFUN(".text.crt.dos.random", libd_drand48_r, libc_drand48_r, TD, 2, TP, TP)
DFUN(".text.crt.dos.random", libd_erand48_r, libc_erand48_r, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.random", libd_lrand48_r, libc_lrand48_r, TD, 2, TP, TP)
DFUN(".text.crt.dos.random", libd_nrand48_r, libc_nrand48_r, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.random", libd_mrand48_r, libc_mrand48_r, TD, 2, TP, TP)
DFUN(".text.crt.dos.random", libd_jrand48_r, libc_jrand48_r, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.random", libd_srand48_r, libc_srand48_r, TD, 2, TL, TP)
DFUN(".text.crt.dos.random", libd_seed48_r, libc_seed48_r, TD, 2, TP, TP)
DFUN(".text.crt.dos.random", libd_lcong48_r, libc_lcong48_r, TD, 2, TP, TP)
DFUN(".text.crt.dos.random", libd_random_r, libc_random_r, TD, 2, TP, TP)
DFUN(".text.crt.dos.random", libd_srandom_r, libc_srandom_r, TD, 2, TD, TP)
DFUN(".text.crt.dos.random", libd_initstate_r, libc_initstate_r, TD, 4, TD, TP, TI, TP)
DFUN(".text.crt.dos.random", libd_setstate_r, libc_setstate_r, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.utility", libd_mkstemps, libc_mkstemps, TIn(__SIZEOF_FD_T__), 2, TP, TD)
DFUN(".text.crt.dos.utility.locale", libd_rpmatch, libc_rpmatch, TD, 1, TP)
DFUN(".text.crt.dos.fs.utility", libd_mkstemps64, libc_mkstemps64, TIn(__SIZEOF_FD_T__), 2, TP, TD)
DFUN(".text.crt.dos.random", libd_erand48, libc_erand48, TFD, 1, TP)
DFUN(".text.crt.dos.random", libd_nrand48, libc_nrand48, TL, 1, TP)
DFUN(".text.crt.dos.random", libd_jrand48, libc_jrand48, TL, 1, TP)
DFUN(".text.crt.dos.random", libd_srand48, libc_srand48, TV, 1, TL)
DFUN(".text.crt.dos.random", libd_seed48, libc_seed48, TP, 1, TP)
DFUN(".text.crt.dos.random", libd_lcong48, libc_lcong48, TV, 1, TP)
DFUN(".text.crt.dos.random", libd_srandom, libc_srandom, TV, 1, TD)
DFUN(".text.crt.dos.random", libd_initstate, libc_initstate, TP, 3, TD, TP, TI)
DFUN(".text.crt.dos.random", libd_setstate, libc_setstate, TP, 1, TP)
DFUN(".text.crt.dos.bsd", libd_l64a, libc_l64a, TP, 1, TL)
DFUN(".text.crt.dos.bsd", libd_a64l, libc_a64l, TL, 1, TP)
DFUN(".text.crt.dos.fs.utility", libd_mktemp, libc_mktemp, TP, 1, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_ecvt, libc_ecvt, TP, 4, TFD, TD, TP, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_fcvt, libc_fcvt, TP, 4, TFD, TD, TP, TP)
DFUN(".text.crt.dos.application.getopt", libd_getsubopt, libc_getsubopt, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.fs.utility", libd_mkstemp, libc_mkstemp, TIn(__SIZEOF_FD_T__), 1, TP)
DFUN(".text.crt.dos.fs.utility", libd_mkstemp64, libc_mkstemp64, TIn(__SIZEOF_FD_T__), 1, TP)
DFUN(".text.crt.dos.fs.utility", libd_mkdtemp, libc_mkdtemp, TP, 1, TP)
DFUN(".text.crt.dos.io.tty", libd_grantpt, libc_grantpt, TD, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.io.tty", libd_unlockpt, libc_unlockpt, TD, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.io.tty", libd_posix_openpt, libc_posix_openpt, TIn(__SIZEOF_FD_T__), 1, TIn(__SIZEOF_OFLAG_T__))
DFUN(".text.crt.dos.unicode.static.convert", libd_strtol_l, libc_strtol_l, TL, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtoul_l, libc_strtoul_l, TL, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtoll_l, libc_strtoll_l, TLL, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtoull_l, libc_strtoull_l, TLL, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtod_l, libc_strtod_l, TFD, 3, TP, TP, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd_strtof_l, libc_strtof_l, TF, 3, TP, TP, TP)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd_strtold_l, libd_strtod_l);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unicode.static.convert", libd_strtold_l, libc_strtold_l, TFL, 3, TP, TP, TP)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.fs.exec.system", libd_shexec, libc_shexec, TD, 1, TP)
DFUN(".text.crt.dos.solaris", libd_lltostr, libc_lltostr, TP, 2, TLL, TP)
DFUN(".text.crt.dos.solaris", libd_ulltostr, libc_ulltostr, TP, 2, TLL, TP)
DFUN(".text.crt.dos.heap.rare_helpers", libd_reallocf, libc_reallocf, TP, 2, TP, TI)
DFUN(".text.crt.dos.heap.rare_helpers", libd_recallocarray, libc_recallocarray, TP, 4, TP, TI, TI, TI)
DFUN(".text.crt.dos.heap.rare_helpers", libd_freezero, libc_freezero, TV, 2, TP, TI)
DFUN(".text.crt.dos.bsd", libd_getbsize, libc_getbsize, TP, 2, TP, TP)
DFUN(".text.crt.dos.system.utility", libd_daemonfd, libc_daemonfd, TD, 2, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.bsd", libd_l64a_r, libc_l64a_r, TD, 3, TL, TP, TD)
DFUN(".text.crt.dos.bsd", libd_setprogname, libc_setprogname, TV, 1, TP)
DFUN(".text.crt.dos.bsd", libd_heapsort, libc_heapsort, TD, 4, TP, TI, TI, TP)
DFUN(".text.crt.dos.bsd", libd_mergesort, libc_mergesort, TD, 4, TP, TI, TI, TP)
DFUN(".text.crt.dos.bsd", libd_radixsort, libc_radixsort, TD, 4, TP, TD, TP, TD)
DFUN(".text.crt.dos.bsd", libd_sradixsort, libc_sradixsort, TD, 4, TP, TD, TP, TD)
DFUN(".text.crt.dos.bsd", libd_strtonum, libc_strtonum, TLL, 4, TP, TLL, TLL, TP)
DFUN(".text.crt.dos.fs.utility", libd_mkostemp, libc_mkostemp, TIn(__SIZEOF_FD_T__), 2, TP, TIn(__SIZEOF_OFLAG_T__))
DFUN(".text.crt.dos.fs.utility", libd_mkostemps, libc_mkostemps, TIn(__SIZEOF_FD_T__), 3, TP, TD, TIn(__SIZEOF_OFLAG_T__))
DFUN(".text.crt.dos.fs.utility", libd_mkostemp64, libc_mkostemp64, TIn(__SIZEOF_FD_T__), 2, TP, TIn(__SIZEOF_OFLAG_T__))
DFUN(".text.crt.dos.fs.utility", libd_mkostemps64, libc_mkostemps64, TIn(__SIZEOF_FD_T__), 3, TP, TD, TIn(__SIZEOF_OFLAG_T__))
DFUN(".text.crt.dos.bsd", libd_devname, libc_devname, TP, 2, TIn(__SIZEOF_DEV_T__), TIn(__SIZEOF_MODE_T__))
DFUN(".text.crt.dos.bsd", libd_devname_r, libc_devname_r, TD, 4, TIn(__SIZEOF_DEV_T__), TIn(__SIZEOF_MODE_T__), TP, TI)
DFUN(".text.crt.dos.bsd", libd_humanize_number, libc_humanize_number, TD, 6, TP, TI, TI64, TP, TD, TD)
DFUN(".text.crt.dos.bsd", libd_dehumanize_number, libc_dehumanize_number, TD, 2, TP, TP)
DFUN(".text.crt.dos.heap.rare_helpers", libd_reallocarr, libc_reallocarr, TD, 3, TP, TI, TI)
DFUN(".text.crt.dos.bsd", libd_strsuftoll, libc_strsuftoll, TLL, 4, TP, TP, TLL, TLL)
DFUN(".text.crt.dos.bsd", libd_strsuftollx, libc_strsuftollx, TLL, 6, TP, TP, TLL, TLL, TP, TI)
DFUN(".text.crt.dos.errno", libd__set_doserrno, libc__set_doserrno, TIn(__SIZEOF_ERRNO_T__), 1, TI32)
DFUN(".text.crt.dos.errno", libd__set_purecall_handler, libc__set_purecall_handler, TP, 1, TP)
DFUN(".text.crt.dos.errno", libd__set_invalid_parameter_handler, libc__set_invalid_parameter_handler, TP, 1, TP)
DFUN(".text.crt.dos.application.init", libd__get_pgmptr, libc__get_pgmptr, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.FILE.utility", libd__set_fmode, libc__set_fmode, TIn(__SIZEOF_ERRNO_T__), 1, TD)
DFUN(".text.crt.dos.FILE.utility", libd__get_fmode, libc__get_fmode, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.errno", libd__set_abort_behavior, libc__set_abort_behavior, TD, 2, TD, TD)
DFUN(".text.crt.dos.math.utility", libd__abs64, libc__abs64, TI64, 1, TI64)
DFUN(".text.crt.dos.unicode.locale.convert", libd__atof_l, libc__atof_l, TFD, 2, TP, TP)
DFUN(".text.crt.dos.unicode.locale.convert", libd__atoi_l, libc__atoi_l, TD, 2, TP, TP)
DFUN(".text.crt.dos.unicode.locale.convert", libd__atol_l, libc__atol_l, TL, 2, TP, TP)
DFUN(".text.crt.dos.unicode.locale.convert", libd__atoll_l, libc__atoll_l, TLL, 2, TP, TP)
DFUN(".text.crt.dos.math.utility", libd__byteswap_ushort, libc__byteswap_ushort, TI16, 1, TI16)
DFUN(".text.crt.dos.math.utility", libd__byteswap_ulong, libc__byteswap_ulong, TI32, 1, TI32)
DFUN(".text.crt.dos.math.utility", libd__byteswap_uint64, libc__byteswap_uint64, TI64, 1, TI64)
DEFINE_INTERN_ALIAS(libd__ltoa_s, libd__itoa_s);
DFUN(".text.crt.dos.unicode.static.convert", libd__i64toa, libc__i64toa, TP, 3, TI64, TP, TD)
DFUN(".text.crt.dos.unicode.static.convert", libd__ui64toa, libc__ui64toa, TP, 3, TI64, TP, TD)
DFUN(".text.crt.dos.unicode.static.convert", libd__atoi64, libc__atoi64, TI64, 1, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd__atoi64_l, libc__atoi64_l, TI64, 2, TP, TP)
DFUN(".text.crt.dos.wchar.unicode.static.mbs", libd__mbstrlen, libc__mbstrlen, TI, 1, TP)
DFUN(".text.crt.dos.wchar.unicode.static.mbs", libd__mbstrnlen, libc__mbstrnlen, TI, 2, TP, TI)
DFUN(".text.crt.dos.wchar.unicode.static.mbs", libd__mbstrlen_l, libc__mbstrlen_l, TI, 2, TP, TP)
DFUN(".text.crt.dos.wchar.unicode.static.mbs", libd__mbstrnlen_l, libc__mbstrnlen_l, TI, 3, TP, TI, TP)
DFUN(".text.crt.dos.wchar.unicode.static.mbs", libd__mblen_l, libc__mblen_l, TD, 3, TP, TI, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd__atoflt, libc__atoflt, TD, 2, TP, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd__atoflt_l, libc__atoflt_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd__atodbl, libc__atodbl, TD, 2, TP, TP)
DFUN(".text.crt.dos.unicode.static.convert", libd__atodbl_l, libc__atodbl_l, TD, 3, TP, TP, TP)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd__atoldbl, libd__atodbl);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unicode.static.convert", libd__atoldbl, libc__atoldbl, TD, 2, TP, TP)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd__atoldbl_l, libd__atodbl_l);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unicode.static.convert", libd__atoldbl_l, libc__atoldbl_l, TD, 3, TP, TP, TP)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libd__rotl, libd__rotl64);
#else /* __SIZEOF_INT__ == 8 */
DFUN(".text.crt.dos.math.utility", libd__rotl, libc__rotl, TD, 2, TD, TD)
#endif /* __SIZEOF_INT__ != 8 */
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libd__rotr, libd__rotr64);
#else /* __SIZEOF_INT__ == 8 */
DFUN(".text.crt.dos.math.utility", libd__rotr, libc__rotr, TD, 2, TD, TD)
#endif /* __SIZEOF_INT__ != 8 */
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libd__lrotl, libd__rotl);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libd__lrotl, libd__rotl64);
#else /* ... */
DFUN(".text.crt.dos.math.utility", libd__lrotl, libc__lrotl, TL, 2, TL, TD)
#endif /* !... */
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libd__lrotr, libd__rotr);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libd__lrotr, libd__rotr64);
#else /* ... */
DFUN(".text.crt.dos.math.utility", libd__lrotr, libc__lrotr, TL, 2, TL, TD)
#endif /* !... */
DFUN(".text.crt.dos.math.utility", libd__rotl64, libc__rotl64, TI64, 2, TI64, TD)
DFUN(".text.crt.dos.math.utility", libd__rotr64, libc__rotr64, TI64, 2, TI64, TD)
DFUN(".text.crt.dos.fs.utility", libd__searchenv, libc__searchenv, TV, 3, TP, TP, TP)
DFUN(".text.crt.dos.fs.utility", libd__searchenv_s, libc__searchenv_s, TIn(__SIZEOF_ERRNO_T__), 4, TP, TP, TP, TI)
DFUN(".text.crt.dos.fs.utility", libd__makepath, libc__makepath, TV, 5, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.fs.utility", libd__splitpath, libc__splitpath, TV, 5, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.errno", libd__seterrormode, libc__seterrormode, TV, 1, TD)
DFUN(".text.crt.dos.errno", libd__set_error_mode, libc__set_error_mode, TD, 1, TD)
DFUN(".text.crt.dos.system", libd__beep, libc__beep, TV, 2, TD, TD)
DFUN(".text.crt.dos.bsd", libd__sleep, libc__sleep, TV, 1, TI32)
DFUN(".text.crt.dos.unicode.static.convert", libd_itoa, libc_itoa, TP, 3, TD, TP, TD)
DFUN(".text.crt.dos.unicode.static.convert", libd_ltoa, libc_ltoa, TP, 3, TL, TP, TD)
DFUN(".text.crt.dos.unicode.static.convert", libd_ultoa, libc_ultoa, TP, 3, TL, TP, TD)
DFUN(".text.crt.dos.sched.process", libd_onexit, libc_onexit, TP, 1, TP)
DFUN(".text.crt.dos.fs.environ", libd__get_environ, libc__get_environ, TIn(__SIZEOF_ERRNO_T__), 1, TP)

/* string */
DFUN(".text.crt.dos.string.memory", libd_memcpy, libc_memcpy, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memmove, libc_memmove, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memset, libc_memset, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_memcmp, libc_memcmp, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memchr, libc_memchr, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_strlen, libc_strlen, TI, 1, TP)
DFUN(".text.crt.dos.string.memory", libd_strchr, libc_strchr, TP, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_strrchr, libc_strrchr, TP, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_strcmp, libc_strcmp, TD, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_strncmp, libc_strncmp, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_strstr, libc_strstr, TP, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_strcpy, libc_strcpy, TP, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_strncpy, libc_strncpy, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_strcat, libc_strcat, TP, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_strncat, libc_strncat, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_strcspn, libc_strcspn, TI, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_strspn, libc_strspn, TI, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_strpbrk, libc_strpbrk, TP, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_strtok, libc_strtok, TP, 2, TP, TP)
DFUN(".text.crt.dos.unicode.static.memory", libd_strcoll, libc_strcoll, TD, 2, TP, TP)
DFUN(".text.crt.dos.unicode.static.memory", libd_strxfrm, libc_strxfrm, TI, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_strnlen, libc_strnlen, TI, 2, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_stpcpy, libc_stpcpy, TP, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_stpncpy, libc_stpncpy, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.unicode.locale.memory", libd_strcoll_l, libc_strcoll_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd_strxfrm_l, libc_strxfrm_l, TI, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.heap.strdup", libd_strndup, libc_strndup, TP, 2, TP, TI)
DFUN(".text.crt.dos.heap.strdup", libd_strdup, libc_strdup, TP, 1, TP)
DFUN(".text.crt.dos.string.memory", libd_strtok_r, libc_strtok_r, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_memrchr, libc_memrchr, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_memmem, libc_memmem, TP, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.unicode.static.memory", libd_strcasestr, libc_strcasestr, TP, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_strchrnul, libc_strchrnul, TP, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_rawmemchr, libc_rawmemchr, TP, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_basename, libc_basename, TP, 1, TP)
DFUN(".text.crt.dos.string.memory", libd_strverscmp, libc_strverscmp, TD, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_mempcpy, libc_mempcpy, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_strfry, libc_strfry, TP, 1, TP)
DFUN(".text.crt.dos.string.memory", libd_memfrob, libc_memfrob, TP, 2, TP, TI)
DFUN(".text.crt.dos.unicode.locale.memory", libd_strcasecmp_l, libc_strcasecmp_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd_strncasecmp_l, libc_strncasecmp_l, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.string.memory", libd_strsep, libc_strsep, TP, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_bcopy, libc_bcopy, TV, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_bzero, libc_bzero, TV, 2, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_bzerow, libc_bzerow, TV, 2, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_bzerol, libc_bzerol, TV, 2, TP, TI)
#ifndef LIBC_ARCH_HAVE_BCMPW
DEFINE_INTERN_ALIAS(libd_bcmpw, libd_memcmpw);
#endif /* !LIBC_ARCH_HAVE_BCMPW */
#ifndef LIBC_ARCH_HAVE_BCMPL
DEFINE_INTERN_ALIAS(libd_bcmpl, libd_memcmpl);
#endif /* !LIBC_ARCH_HAVE_BCMPL */
DFUN(".text.crt.dos.string.memory", libd_bzeroq, libc_bzeroq, TV, 2, TP, TI)
#ifndef LIBC_ARCH_HAVE_BCMPQ
DEFINE_INTERN_ALIAS(libd_bcmpq, libd_memcmpq);
#endif /* !LIBC_ARCH_HAVE_BCMPQ */
DFUN(".text.crt.dos.string.memory", libd_bzeroc, libc_bzeroc, TV, 3, TP, TI, TI)
#ifndef LIBC_ARCH_HAVE_BCMPC
DFUN(".text.crt.dos.string.memory", libd_bcmpc, libc_bcmpc, TD, 4, TP, TP, TI, TI)
#endif /* !LIBC_ARCH_HAVE_BCMPC */
#ifndef LIBC_ARCH_HAVE_BCMP
DEFINE_INTERN_ALIAS(libd_bcmp, libd_memcmp);
#endif /* !LIBC_ARCH_HAVE_BCMP */
DFUN(".text.crt.dos.unicode.static.memory", libd_strcasecmp, libc_strcasecmp, TD, 2, TP, TP)
DFUN(".text.crt.dos.unicode.static.memory", libd_strncasecmp, libc_strncasecmp, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_ffs, libc_ffs, TD, 1, TD)
DFUN(".text.crt.dos.string.memory", libd_ffsl, libc_ffsl, TD, 1, TL)
DFUN(".text.crt.dos.string.memory", libd_ffsll, libc_ffsll, TD, 1, TLL)
DFUN(".text.crt.dos.string.memory", libd_strlcat, libc_strlcat, TI, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_strlcpy, libc_strlcpy, TI, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memccpy, libc_memccpy, TP, 4, TP, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_memcpyw, libc_memcpyw, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempcpyw, libc_mempcpyw, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memcpyl, libc_memcpyl, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempcpyl, libc_mempcpyl, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memmovew, libc_memmovew, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmovew, libc_mempmovew, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memmovel, libc_memmovel, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmovel, libc_mempmovel, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memmoveupw, libc_memmoveupw, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memmovedownw, libc_memmovedownw, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmoveupw, libc_mempmoveupw, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmovedownw, libc_mempmovedownw, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memmoveupl, libc_memmoveupl, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memmovedownl, libc_memmovedownl, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmoveupl, libc_mempmoveupl, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmovedownl, libc_mempmovedownl, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memsetw, libc_memsetw, TP, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_mempsetw, libc_mempsetw, TP, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_memsetl, libc_memsetl, TP, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_mempsetl, libc_mempsetl, TP, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_memcmpw, libc_memcmpw, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memcmpl, libc_memcmpl, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memchrw, libc_memchrw, TP, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_memchrl, libc_memchrl, TP, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_memrchrw, libc_memrchrw, TP, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_memrchrl, libc_memrchrl, TP, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_rawmemchrw, libc_rawmemchrw, TP, 2, TP, TI16)
DFUN(".text.crt.dos.string.memory", libd_rawmemchrl, libc_rawmemchrl, TP, 2, TP, TI32)
DFUN(".text.crt.dos.string.memory", libd_rawmemrchrw, libc_rawmemrchrw, TP, 2, TP, TI16)
DFUN(".text.crt.dos.string.memory", libd_rawmemrchrl, libc_rawmemrchrl, TP, 2, TP, TI32)
DFUN(".text.crt.dos.string.memory", libd_memendw, libc_memendw, TP, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_memendl, libc_memendl, TP, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_memrendw, libc_memrendw, TP, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_memrendl, libc_memrendl, TP, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_memlenw, libc_memlenw, TI, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_memlenl, libc_memlenl, TI, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_memrlenw, libc_memrlenw, TI, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_memrlenl, libc_memrlenl, TI, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_rawmemlenw, libc_rawmemlenw, TI, 2, TP, TI16)
DFUN(".text.crt.dos.string.memory", libd_rawmemlenl, libc_rawmemlenl, TI, 2, TP, TI32)
DFUN(".text.crt.dos.string.memory", libd_rawmemrlenw, libc_rawmemrlenw, TI, 2, TP, TI16)
DFUN(".text.crt.dos.string.memory", libd_rawmemrlenl, libc_rawmemrlenl, TI, 2, TP, TI32)
DFUN(".text.crt.dos.string.memory", libd_memcpyq, libc_memcpyq, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempcpyq, libc_mempcpyq, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memmoveq, libc_memmoveq, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmoveq, libc_mempmoveq, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memmoveupq, libc_memmoveupq, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memmovedownq, libc_memmovedownq, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmoveupq, libc_mempmoveupq, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmovedownq, libc_mempmovedownq, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memsetq, libc_memsetq, TP, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_mempsetq, libc_mempsetq, TP, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_memcmpq, libc_memcmpq, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memchrq, libc_memchrq, TP, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_memrchrq, libc_memrchrq, TP, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_rawmemchrq, libc_rawmemchrq, TP, 2, TP, TI64)
DFUN(".text.crt.dos.string.memory", libd_rawmemrchrq, libc_rawmemrchrq, TP, 2, TP, TI64)
DFUN(".text.crt.dos.string.memory", libd_memendq, libc_memendq, TP, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_memrendq, libc_memrendq, TP, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_memlenq, libc_memlenq, TI, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_memrlenq, libc_memrlenq, TI, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_rawmemlenq, libc_rawmemlenq, TI, 2, TP, TI64)
DFUN(".text.crt.dos.string.memory", libd_rawmemrlenq, libc_rawmemrlenq, TI, 2, TP, TI64)
DFUN(".text.crt.dos.string.memory", libd_memxchr, libc_memxchr, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_memrxchr, libc_memrxchr, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_rawmemxchr, libc_rawmemxchr, TP, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_rawmemrxchr, libc_rawmemrxchr, TP, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_memxend, libc_memxend, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_memrxend, libc_memrxend, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_memxlen, libc_memxlen, TI, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_memrxlen, libc_memrxlen, TI, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_rawmemxlen, libc_rawmemxlen, TI, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_rawmemrxlen, libc_rawmemrxlen, TI, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_memxchrw, libc_memxchrw, TP, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_memxchrl, libc_memxchrl, TP, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_memrxchrw, libc_memrxchrw, TP, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_memrxchrl, libc_memrxchrl, TP, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_rawmemxchrw, libc_rawmemxchrw, TP, 2, TP, TI16)
DFUN(".text.crt.dos.string.memory", libd_rawmemxchrl, libc_rawmemxchrl, TP, 2, TP, TI32)
DFUN(".text.crt.dos.string.memory", libd_rawmemrxchrw, libc_rawmemrxchrw, TP, 2, TP, TI16)
DFUN(".text.crt.dos.string.memory", libd_rawmemrxchrl, libc_rawmemrxchrl, TP, 2, TP, TI32)
DFUN(".text.crt.dos.string.memory", libd_memxendw, libc_memxendw, TP, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_memxendl, libc_memxendl, TP, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_memrxendw, libc_memrxendw, TP, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_memrxendl, libc_memrxendl, TP, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_memxlenw, libc_memxlenw, TI, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_memxlenl, libc_memxlenl, TI, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_memrxlenw, libc_memrxlenw, TI, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_memrxlenl, libc_memrxlenl, TI, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_rawmemxlenw, libc_rawmemxlenw, TI, 2, TP, TI16)
DFUN(".text.crt.dos.string.memory", libd_rawmemxlenl, libc_rawmemxlenl, TI, 2, TP, TI32)
DFUN(".text.crt.dos.string.memory", libd_rawmemrxlenw, libc_rawmemrxlenw, TI, 2, TP, TI16)
DFUN(".text.crt.dos.string.memory", libd_rawmemrxlenl, libc_rawmemrxlenl, TI, 2, TP, TI32)
DFUN(".text.crt.dos.string.memory", libd_memxchrq, libc_memxchrq, TP, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_memrxchrq, libc_memrxchrq, TP, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_rawmemxchrq, libc_rawmemxchrq, TP, 2, TP, TI64)
DFUN(".text.crt.dos.string.memory", libd_rawmemrxchrq, libc_rawmemrxchrq, TP, 2, TP, TI64)
DFUN(".text.crt.dos.string.memory", libd_memxendq, libc_memxendq, TP, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_memrxendq, libc_memrxendq, TP, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_memxlenq, libc_memxlenq, TI, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_memrxlenq, libc_memrxlenq, TI, 3, TP, TI64, TI)
DFUN(".text.crt.dos.string.memory", libd_rawmemxlenq, libc_rawmemxlenq, TI, 2, TP, TI64)
DFUN(".text.crt.dos.string.memory", libd_rawmemrxlenq, libc_rawmemrxlenq, TI, 2, TP, TI64)
DFUN(".text.crt.dos.string.memory", libd_memmoveup, libc_memmoveup, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memmovedown, libc_memmovedown, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memcmpc, libc_memcmpc, TD, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.string.memory", libd_memcpyc, libc_memcpyc, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.string.memory", libd_mempcpyc, libc_mempcpyc, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.string.memory", libd_memmovec, libc_memmovec, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmovec, libc_mempmovec, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.string.memory", libd_memmoveupc, libc_memmoveupc, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmoveupc, libc_mempmoveupc, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.string.memory", libd_memmovedownc, libc_memmovedownc, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmovedownc, libc_mempmovedownc, TP, 4, TP, TP, TI, TI)
DFUN(".text.crt.dos.string.memory", libd_strend, libc_strend, TP, 1, TP)
DFUN(".text.crt.dos.string.memory", libd_strnend, libc_strnend, TP, 2, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_strnchr, libc_strnchr, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_strnrchr, libc_strnrchr, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_strrchrnul, libc_strrchrnul, TP, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_strnchrnul, libc_strnchrnul, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_strnrchrnul, libc_strnrchrnul, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_stroff, libc_stroff, TI, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_strroff, libc_strroff, TI, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_strnoff, libc_strnoff, TI, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_strnroff, libc_strnroff, TI, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_mempset, libc_mempset, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmove, libc_mempmove, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmoveup, libc_mempmoveup, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempmovedown, libc_mempmovedown, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_rawmemrchr, libc_rawmemrchr, TP, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_memend, libc_memend, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_memrend, libc_memrend, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_memlen, libc_memlen, TI, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_memrlen, libc_memrlen, TI, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_rawmemlen, libc_rawmemlen, TI, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_rawmemrlen, libc_rawmemrlen, TI, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_memrmem, libc_memrmem, TP, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_mempatw, libc_mempatw, TP, 3, TP, TI16, TI)
DFUN(".text.crt.dos.string.memory", libd_mempatl, libc_mempatl, TP, 3, TP, TI32, TI)
DFUN(".text.crt.dos.string.memory", libd_mempatq, libc_mempatq, TP, 3, TP, TI64, TI)
DFUN(".text.crt.dos.unicode.static.memory", libd_memcasecmp, libc_memcasecmp, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.unicode.static.memory", libd_memcasemem, libc_memcasemem, TP, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.unicode.locale.memory", libd_memcasecmp_l, libc_memcasecmp_l, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd_memcasemem_l, libc_memcasemem_l, TP, 5, TP, TI, TP, TI, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd_strcasestr_l, libc_strcasestr_l, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.heap.strdup", libd_vstrdupf, libc_vstrdupf, TP, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_wildstrcmp, libc_wildstrcmp, TD, 2, TP, TP)
DFUN(".text.crt.dos.unicode.static.memory", libd_wildstrcasecmp, libc_wildstrcasecmp, TD, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_fuzzy_strcmp, libc_fuzzy_strcmp, TI, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_fuzzy_strncmp, libc_fuzzy_strncmp, TI, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.unicode.static.memory", libd_fuzzy_strcasecmp, libc_fuzzy_strcasecmp, TI, 2, TP, TP)
DFUN(".text.crt.dos.unicode.static.memory", libd_fuzzy_strncasecmp, libc_fuzzy_strncasecmp, TI, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_fuzzy_memcmp, libc_fuzzy_memcmp, TI, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.unicode.static.memory", libd_fuzzy_memcasecmp, libc_fuzzy_memcasecmp, TI, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.unicode.locale.memory", libd_fuzzy_strcasecmp_l, libc_fuzzy_strcasecmp_l, TI, 3, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd_fuzzy_strncasecmp_l, libc_fuzzy_strncasecmp_l, TI, 5, TP, TI, TP, TI, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd_wildstrcasecmp_l, libc_wildstrcasecmp_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd_fuzzy_memcasecmp_l, libc_fuzzy_memcasecmp_l, TI, 5, TP, TI, TP, TI, TP)
DFUN(".text.crt.dos.string.memory", libd_fuzzy_memcmpw, libc_fuzzy_memcmpw, TI, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_fuzzy_memcmpl, libc_fuzzy_memcmpl, TI, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_fuzzy_memcmpq, libc_fuzzy_memcmpq, TI, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.unicode.static.memory", libd_strncoll, libc_strncoll, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.unicode.static.memory", libd_strcasecoll, libc_strcasecoll, TD, 2, TP, TP)
DFUN(".text.crt.dos.unicode.static.memory", libd_strncasecoll, libc_strncasecoll, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_strnrev, libc_strnrev, TP, 2, TP, TI)
DFUN(".text.crt.dos.unicode.static.memory", libd_strnlwr, libc_strnlwr, TP, 2, TP, TI)
DFUN(".text.crt.dos.unicode.static.memory", libd_strnupr, libc_strnupr, TP, 2, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memrev, libc_memrev, TP, 2, TP, TI)
DFUN(".text.crt.dos.unicode.locale.memory", libd_strncoll_l, libc_strncoll_l, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd_strcasecoll_l, libc_strcasecoll_l, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd_strncasecoll_l, libc_strncasecoll_l, TD, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd_strlwr_l, libc_strlwr_l, TP, 2, TP, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd_strupr_l, libc_strupr_l, TP, 2, TP, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd_strnlwr_l, libc_strnlwr_l, TP, 3, TP, TI, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd_strnupr_l, libc_strnupr_l, TP, 3, TP, TI, TP)
DFUN(".text.crt.dos.string.memory", libd_memrevw, libc_memrevw, TP, 2, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memrevl, libc_memrevl, TP, 2, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memrevq, libc_memrevq, TP, 2, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_strcmpz, libc_strcmpz, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_strstartcmp, libc_strstartcmp, TD, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_strstartcmpz, libc_strstartcmpz, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_bitcpy, libc_bitcpy, TV, 5, TP, TI, TP, TI, TI)
DFUN(".text.crt.dos.string.memory", libd_strrstr, libc_strrstr, TP, 2, TP, TP)
DFUN(".text.crt.dos.string.memory", libd_strlstrip, libc_strlstrip, TP, 1, TP)
DFUN(".text.crt.dos.string.memory", libd_strrstrip, libc_strrstrip, TP, 1, TP)
DFUN(".text.crt.dos.string.memory", libd_strstrip, libc_strstrip, TP, 1, TP)
DFUN(".text.crt.dos.unicode.static.memory", libd_strlwr, libc_strlwr, TP, 1, TP)
DFUN(".text.crt.dos.unicode.static.memory", libd_strupr, libc_strupr, TP, 1, TP)
DFUN(".text.crt.dos.string.memory", libd_strset, libc_strset, TP, 2, TP, TD)
DFUN(".text.crt.dos.string.memory", libd_strnset, libc_strnset, TP, 3, TP, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_strrev, libc_strrev, TP, 1, TP)
DFUN(".text.crt.dos.string.memory", libd__strset_s, libc__strset_s, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TD)
DFUN(".text.crt.dos.string.memory", libd_memcpy_s, libc_memcpy_s, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_memmove_s, libc_memmove_s, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_strcpy_s, libc_strcpy_s, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
DFUN(".text.crt.dos.string.memory", libd_strcat_s, libc_strcat_s, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
DFUN(".text.crt.dos.string.memory", libd_strncat_s, libc_strncat_s, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_strncpy_s, libc_strncpy_s, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.errno", libd__strerror, libc__strerror, TP, 1, TP)
DFUN(".text.crt.dos.errno", libd__strerror_s, libc__strerror_s, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
DFUN(".text.crt.dos.unicode.static.memory", libd__strlwr_s, libc__strlwr_s, TIn(__SIZEOF_ERRNO_T__), 2, TP, TI)
DFUN(".text.crt.dos.unicode.static.memory", libd__strupr_s, libc__strupr_s, TIn(__SIZEOF_ERRNO_T__), 2, TP, TI)
DFUN(".text.crt.dos.unicode.locale.memory", libd__strlwr_s_l, libc__strlwr_s_l, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
DFUN(".text.crt.dos.unicode.locale.memory", libd__strupr_s_l, libc__strupr_s_l, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
DFUN(".text.crt.dos.string.memory", libd__strnset_s, libc__strnset_s, TIn(__SIZEOF_ERRNO_T__), 4, TP, TI, TD, TI)
DFUN(".text.crt.dos.string.memory", libd_strnstr, libc_strnstr, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.bsd.strstat", libd_strmode, libc_strmode, TV, 2, TIn(__SIZEOF_MODE_T__), TP)
DFUN(".text.crt.dos.bsd", libd_timingsafe_memcmp, libc_timingsafe_memcmp, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.string.memory", libd_strtosigno, libc_strtosigno, TIn(__SIZEOF_SIGNO_T__), 1, TP)
DFUN(".text.crt.dos.string.memory", libd_stresep, libc_stresep, TP, 3, TP, TP, TD)
DFUN(".text.crt.dos.bsd", libd_consttime_memequal, libc_consttime_memequal, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.solaris", libd_uucopy, libc_uucopy, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.solaris", libd_uucopystr, libc_uucopystr, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.compat.glibc", libd___strtok_r_1c, libc___strtok_r_1c, TP, 3, TP, THH, TP)
DFUN(".text.crt.dos.compat.glibc", libd___strsep_1c, libc___strsep_1c, TP, 2, TP, THH)
DFUN(".text.crt.dos.compat.glibc", libd___strsep_2c, libc___strsep_2c, TP, 3, TP, THH, THH)
DFUN(".text.crt.dos.compat.glibc", libd___strsep_3c, libc___strsep_3c, TP, 4, TP, THH, THH, THH)
DFUN(".text.crt.dos.compat.glibc", libd___strcspn_c1, libc___strcspn_c1, TI, 2, TP, TD)
DFUN(".text.crt.dos.compat.glibc", libd___strcspn_c2, libc___strcspn_c2, TI, 3, TP, TD, TD)
DFUN(".text.crt.dos.compat.glibc", libd___strcspn_c3, libc___strcspn_c3, TI, 4, TP, TD, TD, TD)
DFUN(".text.crt.dos.compat.glibc", libd___strspn_c1, libc___strspn_c1, TI, 2, TP, TD)
DFUN(".text.crt.dos.compat.glibc", libd___strspn_c2, libc___strspn_c2, TI, 3, TP, TD, TD)
DFUN(".text.crt.dos.compat.glibc", libd___strspn_c3, libc___strspn_c3, TI, 4, TP, TD, TD, TD)
DFUN(".text.crt.dos.compat.glibc", libd___strpbrk_c2, libc___strpbrk_c2, TP, 3, TP, TD, TD)
DFUN(".text.crt.dos.compat.glibc", libd___strpbrk_c3, libc___strpbrk_c3, TP, 4, TP, TD, TD, TD)

/* stringlist */
DFUN(".text.crt.dos.bsd.stringlist", libd_sl_add, libc_sl_add, TD, 2, TP, TP)
DFUN(".text.crt.dos.bsd.stringlist", libd_sl_free, libc_sl_free, TV, 2, TP, TD)
DFUN(".text.crt.dos.bsd.stringlist", libd_sl_find, libc_sl_find, TP, 2, TP, TP)
DFUN(".text.crt.dos.bsd.stringlist", libd_sl_delete, libc_sl_delete, TD, 3, TP, TP, TD)

/* strings */
DFUN(".text.crt.dos.string.memory", libd_popcount, libc_popcount, TD, 1, TD)
DFUN(".text.crt.dos.string.memory", libd_popcountl, libc_popcountl, TD, 1, TL)
DFUN(".text.crt.dos.string.memory", libd_popcountll, libc_popcountll, TD, 1, TLL)
DFUN(".text.crt.dos.string.memory", libd_popcount32, libc_popcount32, TD, 1, TI32)
DFUN(".text.crt.dos.string.memory", libd_popcount64, libc_popcount64, TD, 1, TI64)

/* stropts */
DFUN(".text.crt.dos.io.stropts", libd_isastream, libc_isastream, TD, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.io.stropts", libd_getmsg, libc_getmsg, TD, 4, TIn(__SIZEOF_FD_T__), TP, TP, TP)
DFUN(".text.crt.dos.io.stropts", libd_getpmsg, libc_getpmsg, TD, 5, TIn(__SIZEOF_FD_T__), TP, TP, TP, TP)
DFUN(".text.crt.dos.io.stropts", libd_putmsg, libc_putmsg, TD, 4, TIn(__SIZEOF_FD_T__), TP, TP, TD)
DFUN(".text.crt.dos.io.stropts", libd_putpmsg, libc_putpmsg, TD, 5, TIn(__SIZEOF_FD_T__), TP, TP, TD, TD)
DFUN(".text.crt.dos.io.stropts", libd_fattach, libc_fattach, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.io.stropts", libd_fdetach, libc_fdetach, TD, 1, TP)

/* sys.acct */
DFUN(".text.crt.dos.fs.modify", libd_acct, libc_acct, TD, 1, TP)

/* sys.auxv */
DFUN(".text.crt.dos.system.auxv", libd_getauxval, libc_getauxval, TP, 1, TP)

/* sys.capability */
DFUN(".text.crt.dos.capability", libd_capset, libc_capset, TD, 2, TP, TP)
DFUN(".text.crt.dos.capability", libd_capget, libc_capget, TD, 2, TP, TP)

/* sys.epoll */
DFUN(".text.crt.dos.io.poll", libd_epoll_create, libc_epoll_create, TIn(__SIZEOF_FD_T__), 1, TD)
DFUN(".text.crt.dos.io.poll", libd_epoll_create1, libc_epoll_create1, TIn(__SIZEOF_FD_T__), 1, TD)
DFUN(".text.crt.dos.io.poll", libd_epoll_ctl, libc_epoll_ctl, TD, 4, TIn(__SIZEOF_FD_T__), TD, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.io.poll", libd_epoll_wait, libc_epoll_wait, TD, 4, TIn(__SIZEOF_FD_T__), TP, TD, TD)
DFUN(".text.crt.dos.io.poll", libd_epoll_pwait, libc_epoll_pwait, TD, 5, TIn(__SIZEOF_FD_T__), TP, TD, TD, TP)
DFUN(".text.crt.dos.io.poll", libd_epoll_rpc_exec, libc_epoll_rpc_exec, TD, 6, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_FD_T__), TP, TIn(__SIZEOF_PID_T__), TD, TP)

/* sys.eventfd */
DFUN(".text.crt.dos.sched.eventfd", libd_eventfd, libc_eventfd, TIn(__SIZEOF_FD_T__), 2, TD, TD)
DFUN(".text.crt.dos.sched.eventfd", libd_eventfd_read, libc_eventfd_read, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.sched.eventfd", libd_eventfd_write, libc_eventfd_write, TD, 2, TIn(__SIZEOF_FD_T__), TI64)

/* sys.file */
DFUN(".text.crt.dos.unsorted", libd_flock, libc_flock, TD, 2, TIn(__SIZEOF_FD_T__), TD)

/* sys.fsuid */
DFUN(".text.crt.dos.sched.user", libd_setfsuid, libc_setfsuid, TD, 1, TIn(__SIZEOF_UID_T__))
DFUN(".text.crt.dos.sched.user", libd_setfsgid, libc_setfsgid, TD, 1, TIn(__SIZEOF_GID_T__))

/* sys.inotify */
DFUN(".text.crt.dos.unsorted", libd_inotify_init1, libc_inotify_init1, TIn(__SIZEOF_FD_T__), 1, TD)
DFUN(".text.crt.dos.unsorted", libd_inotify_rm_watch, libc_inotify_rm_watch, TD, 2, TIn(__SIZEOF_FD_T__), TD)

/* sys.ioctl */
DFUN(".text.crt.dos.io.utility", libd_ioctl, libc_ioctl, TD, 3, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_IOCTL_T__), TP)

/* sys.ipc */
DFUN(".text.crt.dos.unsorted", libd_ftok, libc_ftok, TIn(__SIZEOF_KEY_T__), 2, TP, TD)

/* sys.klog */
DFUN(".text.crt.dos.utility.klog", libd_klogctl, libc_klogctl, TD, 3, TD, TP, TD)

/* sys.mkdev */
DFUN(".text.crt.dos.system.utility", libd_makedev, libc_makedev, TIn(__SIZEOF_DEV_T__), 2, TIn(__SIZEOF_MAJOR_T__), TIn(__SIZEOF_MINOR_T__))
DFUN(".text.crt.dos.system.utility", libd_major, libc_major, TIn(__SIZEOF_MAJOR_T__), 1, TIn(__SIZEOF_DEV_T__))
DFUN(".text.crt.dos.system.utility", libd_minor, libc_minor, TIn(__SIZEOF_MINOR_T__), 1, TIn(__SIZEOF_DEV_T__))
DFUN(".text.crt.dos.system.utility", libd___makedev, libc___makedev, TIn(__SIZEOF_DEV_T__), 3, TD, TIn(__SIZEOF_MAJOR_T__), TIn(__SIZEOF_MINOR_T__))
DFUN(".text.crt.dos.system.utility", libd___major, libc___major, TIn(__SIZEOF_MAJOR_T__), 2, TD, TIn(__SIZEOF_DEV_T__))
DFUN(".text.crt.dos.system.utility", libd___minor, libc___minor, TIn(__SIZEOF_MINOR_T__), 2, TD, TIn(__SIZEOF_DEV_T__))

/* sys.mman */
DFUN(".text.crt.dos.heap.mman", libd_mmap, libc_mmap, TP, 6, TP, TI, TD, TD, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFF32_T__))
DFUN(".text.crt.dos.heap.mman", libd_munmap, libc_munmap, TD, 2, TP, TI)
DFUN(".text.crt.dos.system.mman", libd_mprotect, libc_mprotect, TD, 3, TP, TI, TD)
DFUN(".text.crt.dos.system.mman", libd_msync, libc_msync, TD, 3, TP, TI, TD)
DFUN(".text.crt.dos.system.mman", libd_mlock, libc_mlock, TD, 2, TP, TI)
DFUN(".text.crt.dos.system.mman", libd_munlock, libc_munlock, TD, 2, TP, TI)
DFUN(".text.crt.dos.system.mman", libd_mlockall, libc_mlockall, TD, 1, TD)
DFUN(".text.crt.dos.compat.glibc", libd___shm_directory, libc___shm_directory, TP, 1, TP)
DFUN(".text.crt.dos.system.mman", libd_shm_open, libc_shm_open, TIn(__SIZEOF_FD_T__), 3, TP, TIn(__SIZEOF_OFLAG_T__), TIn(__SIZEOF_MODE_T__))
DFUN(".text.crt.dos.system.mman", libd_shm_unlink, libc_shm_unlink, TD, 1, TP)
DFUN(".text.crt.dos.system.mman", libd_madvise, libc_madvise, TD, 3, TP, TI, TD)
DFUN(".text.crt.dos.system.mman", libd_mincore, libc_mincore, TD, 3, TP, TI, TP)
DFUN(".text.crt.dos.heap.mman", libd_mmap64, libc_mmap64, TP, 6, TP, TI, TD, TD, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFF64_T__))
DFUN(".text.crt.dos.system.mman", libd_posix_madvise, libc_posix_madvise, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TD)
DFUN(".text.crt.dos.heap.mman", libd_mremap, libc_mremap, TP, 5, TP, TI, TI, TD, TP)
DFUN(".text.crt.dos.system.mman", libd_remap_file_pages, libc_remap_file_pages, TD, 5, TP, TI, TD, TI, TD)
DFUN(".text.crt.dos.system.mman", libd_memfd_create, libc_memfd_create, TIn(__SIZEOF_FD_T__), 2, TP, TD)
DFUN(".text.crt.dos.system.mman", libd_mlock2, libc_mlock2, TD, 3, TP, TI, TD)
#include <asm/pkey.h>
#ifdef __ARCH_HAVE_PKEY
DFUN(".text.crt.dos.system.mman", libd_pkey_alloc, libc_pkey_alloc, TD, 2, TD, TD)
DFUN(".text.crt.dos.system.mman", libd_pkey_set, libc_pkey_set, TD, 2, TD, TD)
DFUN(".text.crt.dos.system.mman", libd_pkey_get, libc_pkey_get, TD, 1, TD)
DFUN(".text.crt.dos.system.mman", libd_pkey_free, libc_pkey_free, TD, 1, TD)
DFUN(".text.crt.dos.system.mman", libd_pkey_mprotect, libc_pkey_mprotect, TD, 4, TP, TI, TD, TD)
#endif /* __ARCH_HAVE_PKEY */
DFUN(".text.crt.dos.system.mman", libd_fmapfile, libc_fmapfile, TD, 7, TP, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFF64_T__), TI, TI, TI, TD)
DFUN(".text.crt.dos.system.mman", libd_ffmapfile, libc_ffmapfile, TD, 7, TP, TP, TIn(__SIZEOF_OFF64_T__), TI, TI, TI, TD)
DFUN(".text.crt.dos.system.mman", libd_unmapfile, libc_unmapfile, TD, 1, TP)

/* sys.mount */
DFUN(".text.crt.dos.fs.mount", libd_mount, libc_mount, TD, 5, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.fs.mount", libd_umount, libc_umount, TD, 1, TP)
DFUN(".text.crt.dos.fs.mount", libd_umount2, libc_umount2, TD, 2, TP, TD)

/* sys.msg */
DFUN(".text.crt.dos.sched.msg", libd_msgctl, libc_msgctl, TD, 3, TD, TD, TP)
DFUN(".text.crt.dos.sched.msg", libd_msgget, libc_msgget, TD, 2, TIn(__SIZEOF_KEY_T__), TD)
DFUN(".text.crt.dos.sched.msg", libd_msgrcv, libc_msgrcv, TI, 5, TD, TP, TI, TP, TD)
DFUN(".text.crt.dos.sched.msg", libd_msgsnd, libc_msgsnd, TD, 4, TD, TP, TI, TD)

/* sys.perm */
#include <bits/typesizes.h>
#ifdef __SIZEOF_PORT_T__
DFUN(".text.crt.dos.system.ioperm", libd_ioperm, libc_ioperm, TD, 3, TP, TP, TD)
DFUN(".text.crt.dos.system.ioperm", libd_iopl, libc_iopl, TD, 1, TD)
#endif /* __SIZEOF_PORT_T__ */

/* sys.poll */
DFUN(".text.crt.dos.io.poll", libd_poll, libc_poll, TD, 3, TP, TP, TD)
DFUN(".text.crt.dos.io.poll", libd_ppoll, libc_ppoll, TD, 4, TP, TP, TP, TP)
DFUN(".text.crt.dos.io.poll", libd_ppoll64, libc_ppoll64, TD, 4, TP, TP, TP, TP)

/* sys.prctl */
DFUN(".text.crt.dos.unsorted", libd_prctl, libc_prctl, TD, 5, TD, TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__))

/* sys.profil */
DFUN(".text.crt.compat.glibc", libd_sprofil, libc_sprofil, TD, 4, TP, TD, TP, TD)

/* sys.ptrace */
DFUN(".text.crt.dos.system.ptrace", libd_ptrace, libc_ptrace, TP, 4, TD, TIn(__SIZEOF_PID_T__), TP, TP)

/* sys.random */
DFUN(".text.crt.dos.system.random", libd_getrandom, libc_getrandom, TI, 3, TP, TI, TD)
DFUN(".text.crt.dos.system.random", libd_getentropy, libc_getentropy, TD, 2, TP, TI)

/* sys.reboot */
DFUN(".text.crt.dos.system.reboot", libd_reboot, libc_reboot, TD, 1, TD)

/* sys.resource */
DFUN(".text.crt.dos.sched.resource", libd_prlimit, libc_prlimit, TD, 4, TIn(__SIZEOF_PID_T__), TD, TP, TP)
DFUN(".text.crt.dos.sched.resource", libd_prlimit64, libc_prlimit64, TD, 4, TIn(__SIZEOF_PID_T__), TD, TP, TP)
DFUN(".text.crt.dos.sched.resource", libd_getrlimit, libc_getrlimit, TD, 2, TD, TP)
DFUN(".text.crt.dos.sched.resource", libd_setrlimit, libc_setrlimit, TD, 2, TD, TP)
DFUN(".text.crt.dos.sched.resource", libd_getrusage, libc_getrusage, TD, 2, TD, TP)
DFUN(".text.crt.dos.sched.resource", libd_getrusage64, libc_getrusage64, TD, 2, TD, TP)
DFUN(".text.crt.dos.sched.resource", libd_getpriority, libc_getpriority, TD, 2, TD, TIn(__SIZEOF_ID_T__))
DFUN(".text.crt.dos.sched.resource", libd_setpriority, libc_setpriority, TD, 3, TD, TIn(__SIZEOF_ID_T__), TD)
DFUN(".text.crt.dos.sched.resource", libd_getrlimit64, libc_getrlimit64, TD, 2, TD, TP)
DFUN(".text.crt.dos.sched.resource", libd_setrlimit64, libc_setrlimit64, TD, 2, TD, TP)

/* sys.select */
DFUN(".text.crt.dos.io.poll", libd___fdelt_chk, libc___fdelt_chk, TP, 1, TP)
DFUN(".text.crt.dos.io.poll", libd_select, libc_select, TD, 5, TD, TP, TP, TP, TP)
DFUN(".text.crt.dos.io.poll", libd_pselect, libc_pselect, TD, 6, TD, TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.io.poll", libd_select64, libc_select64, TD, 5, TD, TP, TP, TP, TP)
DFUN(".text.crt.dos.io.poll", libd_pselect64, libc_pselect64, TD, 6, TD, TP, TP, TP, TP, TP)

/* sys.sem */
DFUN(".text.crt.dos.io.poll", libd_semget, libc_semget, TD, 3, TIn(__SIZEOF_KEY_T__), TD, TD)
DFUN(".text.crt.dos.io.poll", libd_semop, libc_semop, TD, 3, TD, TP, TI)
DFUN(".text.crt.dos.io.poll", libd_semtimedop, libc_semtimedop, TD, 4, TD, TP, TI, TP)

/* sys.sendfile */
DFUN(".text.crt.dos.fs.statfs.statfs", libd_sendfile, libc_sendfile, TI, 4, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_FD_T__), TP, TI)
DFUN(".text.crt.dos.fs.statfs.statfs", libd_sendfile64, libc_sendfile64, TI, 4, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_FD_T__), TP, TI)

/* sys.shm */
DFUN(".text.crt.dos.utility.shm", libd_shmctl, libc_shmctl, TD, 3, TD, TD, TP)
DFUN(".text.crt.dos.utility.shm", libd_shmget, libc_shmget, TD, 3, TIn(__SIZEOF_KEY_T__), TI, TD)
DFUN(".text.crt.dos.utility.shm", libd_shmat, libc_shmat, TP, 3, TD, TP, TD)
DFUN(".text.crt.dos.utility.shm", libd_shmdt, libc_shmdt, TD, 1, TP)

/* sys.signalfd */
DFUN(".text.crt.dos.sched.signalfd", libd_signalfd, libc_signalfd, TIn(__SIZEOF_FD_T__), 3, TIn(__SIZEOF_FD_T__), TP, TD)

/* sys.socket */
DFUN(".text.crt.dos.net.socket", libd___cmsg_nxthdr, libc___cmsg_nxthdr, TP, 2, TP, TP)
DFUN(".text.crt.dos.net.socket", libd_socket, libc_socket, TIn(__SIZEOF_FD_T__), 3, TD, TD, TD)
DFUN(".text.crt.dos.net.socket", libd_socketpair, libc_socketpair, TD, 4, TD, TD, TD, TP)
DFUN(".text.crt.dos.net.socket", libd_bind, libc_bind, TD, 3, TIn(__SIZEOF_FD_T__), TP, TIn(__SIZEOF_SOCKLEN_T__))
DFUN(".text.crt.dos.net.socket", libd_getsockname, libc_getsockname, TD, 3, TIn(__SIZEOF_FD_T__), TP, TP)
DFUN(".text.crt.dos.net.socket", libd_connect, libc_connect, TD, 3, TIn(__SIZEOF_FD_T__), TP, TIn(__SIZEOF_SOCKLEN_T__))
DFUN(".text.crt.dos.net.socket", libd_getpeername, libc_getpeername, TD, 3, TIn(__SIZEOF_FD_T__), TP, TP)
DFUN(".text.crt.dos.net.socket", libd_send, libc_send, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TD)
DFUN(".text.crt.dos.net.socket", libd_recv, libc_recv, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TD)
DFUN(".text.crt.dos.net.socket", libd_sendto, libc_sendto, TI, 6, TIn(__SIZEOF_FD_T__), TP, TI, TD, TP, TIn(__SIZEOF_SOCKLEN_T__))
DFUN(".text.crt.dos.net.socket", libd_recvfrom, libc_recvfrom, TI, 6, TIn(__SIZEOF_FD_T__), TP, TI, TD, TP, TP)
DFUN(".text.crt.dos.net.socket", libd_sendmsg, libc_sendmsg, TI, 3, TIn(__SIZEOF_FD_T__), TP, TD)
DFUN(".text.crt.dos.net.socket", libd_recvmsg, libc_recvmsg, TI, 3, TIn(__SIZEOF_FD_T__), TP, TD)
DFUN(".text.crt.dos.net.socket", libd_getsockopt, libc_getsockopt, TD, 5, TIn(__SIZEOF_FD_T__), TD, TD, TP, TP)
DFUN(".text.crt.dos.net.socket", libd_setsockopt, libc_setsockopt, TD, 5, TIn(__SIZEOF_FD_T__), TD, TD, TP, TIn(__SIZEOF_SOCKLEN_T__))
DFUN(".text.crt.dos.net.socket", libd_listen, libc_listen, TD, 2, TIn(__SIZEOF_FD_T__), TD)
DFUN(".text.crt.dos.net.socket", libd_accept, libc_accept, TIn(__SIZEOF_FD_T__), 3, TIn(__SIZEOF_FD_T__), TP, TP)
DFUN(".text.crt.dos.net.socket", libd_shutdown, libc_shutdown, TD, 2, TIn(__SIZEOF_FD_T__), TD)
DFUN(".text.crt.dos.net.socket", libd_accept4, libc_accept4, TIn(__SIZEOF_FD_T__), 4, TIn(__SIZEOF_FD_T__), TP, TP, TD)
DFUN(".text.crt.dos.net.socket", libd_sendmmsg, libc_sendmmsg, TD, 4, TIn(__SIZEOF_FD_T__), TP, TD, TD)
DFUN(".text.crt.dos.net.socket", libd_recvmmsg, libc_recvmmsg, TD, 5, TIn(__SIZEOF_FD_T__), TP, TD, TD, TP)
DFUN(".text.crt.dos.net.socket", libd_recvmmsg64, libc_recvmmsg64, TD, 5, TIn(__SIZEOF_FD_T__), TP, TD, TD, TP)
DFUN(".text.crt.dos.net.socket", libd_sockatmark, libc_sockatmark, TD, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.net.socket", libd_isfdtype, libc_isfdtype, TD, 2, TIn(__SIZEOF_FD_T__), TD)

/* sys.stat */
DFUN(".text.crt.dos.fs.basic_property", libd_umask, libc_umask, TIn(__SIZEOF_MODE_T__), 1, TIn(__SIZEOF_MODE_T__))
DFUN(".text.crt.dos.fs.modify", libd_fchmod, libc_fchmod, TD, 2, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_MODE_T__))
DFUN(".text.crt.dos.fs.modify_time", libd_futimens, libc_futimens, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.fs.modify_time", libd_futimens64, libc_futimens64, TD, 2, TIn(__SIZEOF_FD_T__), TP)

/* sys.statfs */
DFUN(".text.crt.dos.fs.statfs.statfs", libd_statfs, libc_statfs, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.statfs.statfs", libd_fstatfs, libc_fstatfs, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.fs.statfs.statfs", libd_statfs64, libc_statfs64, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.statfs.statfs", libd_fstatfs64, libc_fstatfs64, TD, 2, TIn(__SIZEOF_FD_T__), TP)

/* sys.statvfs */
DFUN(".text.crt.dos.fs.statfs.statvfs", libd_statvfs, libc_statvfs, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.statfs.statvfs", libd_fstatvfs, libc_fstatvfs, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.fs.statfs.statvfs", libd_statvfs64, libc_statvfs64, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.statfs.statvfs", libd_fstatvfs64, libc_fstatvfs64, TD, 2, TIn(__SIZEOF_FD_T__), TP)

/* sys.swap */
DFUN(".text.crt.dos.fs.swap", libd_swapon, libc_swapon, TD, 2, TP, TD)
DFUN(".text.crt.dos.fs.swap", libd_swapoff, libc_swapoff, TD, 1, TP)

/* sys.sysinfo */
DFUN(".text.crt.dos.system.info", libd_sysinfo, libc_sysinfo, TD, 1, TP)

/* sys.syslog */
DFUN(".text.crt.dos.system.syslog", libd_openlog, libc_openlog, TV, 3, TP, TD, TD)
DFUN(".text.crt.dos.system.syslog", libd_setlogmask, libc_setlogmask, TD, 1, TD)
DFUN(".text.crt.dos.system.syslog", libd_vsyslog, libc_vsyslog, TV, 3, TD, TP, TP)

/* sys.systeminfo */
DFUN(".text.crt.dos.system.info", libd___solaris_sysinfo, libc___solaris_sysinfo, TD, 3, TD, TP, TL)

/* sys.time */
DFUN(".text.crt.dos.time", libd_gettimeofday, libc_gettimeofday, TD, 2, TP, TP)
DFUN(".text.crt.dos.time", libd_getitimer, libc_getitimer, TD, 2, TD, TP)
DFUN(".text.crt.dos.time", libd_setitimer, libc_setitimer, TD, 3, TD, TP, TP)
DFUN(".text.crt.dos.fs.modify_time", libd_utimes, libc_utimes, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.modify_time", libd_futimesat, libc_futimesat, TD, 3, TIn(__SIZEOF_FD_T__), TP, TP)
DFUN(".text.crt.dos.system.adjtime", libd_settimeofday, libc_settimeofday, TD, 2, TP, TP)
DFUN(".text.crt.dos.system.adjtime", libd_adjtime, libc_adjtime, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.modify_time", libd_lutimes, libc_lutimes, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.modify_time", libd_futimes, libc_futimes, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.time", libd_gettimeofday64, libc_gettimeofday64, TD, 2, TP, TP)
DFUN(".text.crt.dos.time", libd_getitimer64, libc_getitimer64, TD, 2, TD, TP)
DFUN(".text.crt.dos.time", libd_setitimer64, libc_setitimer64, TD, 3, TD, TP, TP)
DFUN(".text.crt.dos.fs.modify_time", libd_utimes64, libc_utimes64, TD, 2, TP, TP)
DFUN(".text.crt.dos.system.adjtime", libd_settimeofday64, libc_settimeofday64, TD, 2, TP, TP)
DFUN(".text.crt.dos.system.adjtime", libd_adjtime64, libc_adjtime64, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.modify_time", libd_lutimes64, libc_lutimes64, TD, 2, TP, TP)
DFUN(".text.crt.dos.fs.modify_time", libd_futimes64, libc_futimes64, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.fs.modify_time", libd_futimesat64, libc_futimesat64, TD, 3, TIn(__SIZEOF_FD_T__), TP, TP)

/* sys.timeb */
DFUN(".text.crt.dos.unsorted", libd__ftime32, libc__ftime32, TV, 1, TP)
DFUN(".text.crt.dos.unsorted", libd__ftime64, libc__ftime64, TV, 1, TP)
DFUN(".text.crt.dos.unsorted", libd__ftime32_s, libc__ftime32_s, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.unsorted", libd__ftime64_s, libc__ftime64_s, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.unsorted", libd_ftime, libc_ftime, TD, 1, TP)
DFUN(".text.crt.dos.unsorted", libd_ftime64, libc_ftime64, TD, 1, TP)

/* sys.timerfd */
DFUN(".text.crt.dos.timer", libd_timerfd_create, libc_timerfd_create, TIn(__SIZEOF_FD_T__), 2, TIn(__SIZEOF_CLOCKID_T__), TD)
DFUN(".text.crt.dos.timer", libd_timerfd_settime, libc_timerfd_settime, TD, 4, TIn(__SIZEOF_FD_T__), TD, TP, TP)
DFUN(".text.crt.dos.timer", libd_timerfd_gettime, libc_timerfd_gettime, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.timer", libd_timerfd_settime64, libc_timerfd_settime64, TD, 4, TIn(__SIZEOF_FD_T__), TD, TP, TP)
DFUN(".text.crt.dos.timer", libd_timerfd_gettime64, libc_timerfd_gettime64, TD, 2, TIn(__SIZEOF_FD_T__), TP)

/* sys.times */
DFUN(".text.crt.dos.unsorted", libd_times, libc_times, TIn(__SIZEOF_CLOCK_T__), 1, TP)

/* sys.timex */
DFUN(".text.crt.dos.unsorted", libd_adjtimex, libc_adjtimex, TD, 1, TP)
DFUN(".text.crt.dos.unsorted", libd_ntp_gettimex, libc_ntp_gettimex, TD, 1, TP)
DFUN(".text.crt.dos.unsorted", libd_ntp_adjtime, libc_ntp_adjtime, TD, 1, TP)
DFUN(".text.crt.dos.unsorted", libd_adjtimex64, libc_adjtimex64, TD, 1, TP)
DFUN(".text.crt.dos.unsorted", libd_ntp_adjtime64, libc_ntp_adjtime64, TD, 1, TP)
DFUN(".text.crt.dos.unsorted", libd_ntp_gettimex64, libc_ntp_gettimex64, TD, 1, TP)

/* sys.uio */
DFUN(".text.crt.dos.unsorted", libd_process_vm_readv, libc_process_vm_readv, TI, 6, TIn(__SIZEOF_PID_T__), TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.unsorted", libd_process_vm_writev, libc_process_vm_writev, TI, 6, TIn(__SIZEOF_PID_T__), TP, TP, TP, TP, TP)
DFUN(".text.crt.dos.unsorted", libd_readv, libc_readv, TI, 3, TIn(__SIZEOF_FD_T__), TP, TD)
DFUN(".text.crt.dos.unsorted", libd_writev, libc_writev, TI, 3, TIn(__SIZEOF_FD_T__), TP, TD)
DFUN(".text.crt.dos.unsorted", libd_preadv, libc_preadv, TI, 4, TIn(__SIZEOF_FD_T__), TP, TD, TIn(__SIZEOF_OFF_T__))
DFUN(".text.crt.dos.unsorted", libd_pwritev, libc_pwritev, TI, 4, TIn(__SIZEOF_FD_T__), TP, TD, TIn(__SIZEOF_OFF_T__))
DFUN(".text.crt.dos.unsorted", libd_preadv64, libc_preadv64, TI, 4, TIn(__SIZEOF_FD_T__), TP, TD, TIn(__SIZEOF_OFF64_T__))
DFUN(".text.crt.dos.unsorted", libd_pwritev64, libc_pwritev64, TI, 4, TIn(__SIZEOF_FD_T__), TP, TD, TIn(__SIZEOF_OFF64_T__))

/* sys.ustat */
DFUN(".text.crt.dos.unsorted", libd_ustat, libc_ustat, TD, 2, TIn(__SIZEOF_DEV_T__), TP)

/* sys.utsname */
DFUN(".text.crt.dos.unsorted", libd_uname, libc_uname, TD, 1, TP)

/* sys.vlimit */
DFUN(".text.crt.compat.glibc", libd_vlimit, libc_vlimit, TD, 2, TD, TD)

/* sys.vtimes */
DFUN(".text.crt.compat.glibc", libd_vtimes, libc_vtimes, TD, 2, TP, TP)

/* sys.wait */
DFUN(".text.crt.dos.sched.wait", libd_wait, libc_wait, TIn(__SIZEOF_PID_T__), 1, TP)
DFUN(".text.crt.dos.sched.wait", libd_waitpid, libc_waitpid, TIn(__SIZEOF_PID_T__), 3, TIn(__SIZEOF_PID_T__), TP, TD)
DFUN(".text.crt.dos.sched.wait", libd_waitid, libc_waitid, TD, 4, TD, TIn(__SIZEOF_ID_T__), TP, TD)
DFUN(".text.crt.dos.sched.wait", libd_wait3, libc_wait3, TIn(__SIZEOF_PID_T__), 3, TP, TD, TP)
DFUN(".text.crt.dos.sched.wait", libd_wait3_64, libc_wait3_64, TIn(__SIZEOF_PID_T__), 3, TP, TD, TP)
DFUN(".text.crt.dos.sched.wait", libd_wait4, libc_wait4, TIn(__SIZEOF_PID_T__), 4, TIn(__SIZEOF_PID_T__), TP, TD, TP)
DFUN(".text.crt.dos.sched.wait", libd_wait4_64, libc_wait4_64, TIn(__SIZEOF_PID_T__), 4, TIn(__SIZEOF_PID_T__), TP, TD, TP)
DFUN(".text.crt.dos.sched.wait", libd_detach, libc_detach, TD, 1, TIn(__SIZEOF_PID_T__))

/* sys.xattr */
DFUN(".text.crt.dos.unsorted", libd_setxattr, libc_setxattr, TD, 5, TP, TP, TP, TI, TD)
DFUN(".text.crt.dos.unsorted", libd_lsetxattr, libc_lsetxattr, TD, 5, TP, TP, TP, TI, TD)
DFUN(".text.crt.dos.unsorted", libd_fsetxattr, libc_fsetxattr, TD, 5, TIn(__SIZEOF_FD_T__), TP, TP, TI, TD)
DFUN(".text.crt.dos.unsorted", libd_getxattr, libc_getxattr, TI, 4, TP, TP, TP, TI)
DFUN(".text.crt.dos.unsorted", libd_lgetxattr, libc_lgetxattr, TI, 4, TP, TP, TP, TI)
DFUN(".text.crt.dos.unsorted", libd_fgetxattr, libc_fgetxattr, TI, 4, TIn(__SIZEOF_FD_T__), TP, TP, TI)
DFUN(".text.crt.dos.unsorted", libd_listxattr, libc_listxattr, TI, 3, TP, TP, TI)
DFUN(".text.crt.dos.unsorted", libd_llistxattr, libc_llistxattr, TI, 3, TP, TP, TI)
DFUN(".text.crt.dos.unsorted", libd_flistxattr, libc_flistxattr, TI, 3, TIn(__SIZEOF_FD_T__), TP, TI)
DFUN(".text.crt.dos.unsorted", libd_removexattr, libc_removexattr, TD, 2, TP, TP)
DFUN(".text.crt.dos.unsorted", libd_lremovexattr, libc_lremovexattr, TD, 2, TP, TP)
DFUN(".text.crt.dos.unsorted", libd_fremovexattr, libc_fremovexattr, TD, 2, TIn(__SIZEOF_FD_T__), TP)

/* termios */
DFUN(".text.crt.dos.io.tty", libd_cfgetospeed, libc_cfgetospeed, TI32, 1, TP)
DFUN(".text.crt.dos.io.tty", libd_cfgetispeed, libc_cfgetispeed, TI32, 1, TP)
DFUN(".text.crt.dos.io.tty", libd_cfsetospeed, libc_cfsetospeed, TD, 2, TP, TI32)
DFUN(".text.crt.dos.io.tty", libd_cfsetispeed, libc_cfsetispeed, TD, 2, TP, TI32)
DFUN(".text.crt.dos.io.tty", libd_tcgetattr, libc_tcgetattr, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.io.tty", libd_tcsetattr, libc_tcsetattr, TD, 3, TIn(__SIZEOF_FD_T__), TD, TP)
DFUN(".text.crt.dos.io.tty", libd_tcsendbreak, libc_tcsendbreak, TD, 2, TIn(__SIZEOF_FD_T__), TD)
DFUN(".text.crt.dos.io.tty", libd_tcdrain, libc_tcdrain, TD, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.io.tty", libd_tcflush, libc_tcflush, TD, 2, TIn(__SIZEOF_FD_T__), TD)
DFUN(".text.crt.dos.io.tty", libd_tcflow, libc_tcflow, TD, 2, TIn(__SIZEOF_FD_T__), TD)
DFUN(".text.crt.dos.io.tty", libd_tcgetsid, libc_tcgetsid, TIn(__SIZEOF_PID_T__), 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.io.tty", libd_tcsetsid, libc_tcsetsid, TD, 2, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_PID_T__))
DFUN(".text.crt.dos.io.tty", libd_cfsetspeed, libc_cfsetspeed, TD, 2, TP, TI32)
DFUN(".text.crt.dos.io.tty", libd_cfmakeraw, libc_cfmakeraw, TV, 1, TP)
DFUN(".text.crt.dos.io.tty", libd_cfmakesane, libc_cfmakesane, TV, 1, TP)
DFUN(".text.crt.dos.io.tty", libd_tcgetwinsize, libc_tcgetwinsize, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.io.tty", libd_tcsetwinsize, libc_tcsetwinsize, TD, 2, TIn(__SIZEOF_FD_T__), TP)

/* thread */
DFUN(".text.crt.dos.sched.threads", libd_thr_create, libc_thr_create, TIn(__SIZEOF_ERRNO_T__), 6, TP, TI, TP, TP, TL, TP)
DFUN(".text.crt.dos.sched.threads", libd_thr_join, libc_thr_join, TIn(__SIZEOF_ERRNO_T__), 3, TIn(__SIZEOF_PTHREAD_T), TP, TP)
DFUN(".text.crt.dos.sched.threads", libd_thr_setprio, libc_thr_setprio, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TD)
DFUN(".text.crt.dos.sched.threads", libd_thr_getprio, libc_thr_getprio, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_T), TP)
DFUN(".text.crt.dos.sched.threads", libd_thr_getspecific, libc_thr_getspecific, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PTHREAD_KEY_T), TP)
DFUN(".text.crt.dos.sched.threads", libd_thr_stksegment, libc_thr_stksegment, TIn(__SIZEOF_ERRNO_T__), 1, TP)

/* threads */
DFUN(".text.crt.dos.sched.threads", libd_thrd_sleep, libc_thrd_sleep, TD, 2, TP, TP)
DFUN(".text.crt.dos.sched.threads", libd_thrd_sleep64, libc_thrd_sleep64, TD, 2, TP, TP)
DFUN(".text.crt.dos.sched.threads", libd_thrd_exit, libc_thrd_exit, TV, 1, TD)
DFUN(".text.crt.dos.sched.threads", libd_thrd_detach, libc_thrd_detach, TD, 1, TIn(__SIZEOF_PTHREAD_T))
DFUN(".text.crt.dos.sched.threads", libd_thrd_join, libc_thrd_join, TD, 2, TIn(__SIZEOF_PTHREAD_T), TP)
DFUN(".text.crt.dos.sched.threads", libd_mtx_init, libc_mtx_init, TD, 2, TP, TD)
DFUN(".text.crt.dos.sched.threads", libd_mtx_lock, libc_mtx_lock, TD, 1, TP)
DFUN(".text.crt.dos.sched.threads", libd_mtx_timedlock, libc_mtx_timedlock, TD, 2, TP, TP)
DFUN(".text.crt.dos.sched.threads", libd_mtx_timedlock64, libc_mtx_timedlock64, TD, 2, TP, TP)
DFUN(".text.crt.dos.sched.threads", libd_mtx_trylock, libc_mtx_trylock, TD, 1, TP)
DFUN(".text.crt.dos.sched.threads", libd_mtx_unlock, libc_mtx_unlock, TD, 1, TP)
DFUN(".text.crt.dos.sched.threads", libd_cnd_init, libc_cnd_init, TD, 1, TP)
DFUN(".text.crt.dos.sched.threads", libd_cnd_signal, libc_cnd_signal, TD, 1, TP)
DFUN(".text.crt.dos.sched.threads", libd_cnd_broadcast, libc_cnd_broadcast, TD, 1, TP)
DFUN(".text.crt.dos.sched.threads", libd_cnd_wait, libc_cnd_wait, TD, 2, TP, TP)
DFUN(".text.crt.dos.sched.threads", libd_cnd_timedwait, libc_cnd_timedwait, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.threads", libd_cnd_timedwait64, libc_cnd_timedwait64, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.threads", libd_tss_create, libc_tss_create, TD, 2, TP, TP)
DFUN(".text.crt.dos.sched.threads", libd_tss_set, libc_tss_set, TD, 2, TIn(__SIZEOF_PTHREAD_KEY_T), TP)

/* time */
DFUN(".text.crt.dos.time", libd_time, libc_time, TIn(__SIZEOF_TIME_T__), 1, TP)
DFUN(".text.crt.dos.time", libd_difftime, libc_difftime, TFD, 2, TIn(__SIZEOF_TIME_T__), TIn(__SIZEOF_TIME_T__))
DFUN(".text.crt.dos.time", libd_mktime, libc_mktime, TIn(__SIZEOF_TIME_T__), 1, TP)
DFUN(".text.crt.dos.time", libd_ctime, libc_ctime, TP, 1, TP)
DFUN(".text.crt.dos.time", libd_gmtime, libc_gmtime, TP, 1, TP)
DFUN(".text.crt.dos.time", libd_localtime, libc_localtime, TP, 1, TP)
DFUN(".text.crt.dos.time", libd_strftime, libc_strftime, TI, 4, TP, TI, TP, TP)
DFUN(".text.crt.dos.time", libd_asctime, libc_asctime, TP, 1, TP)
DFUN(".text.crt.dos.time", libd_asctime_s, libc_asctime_s, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
DFUN(".text.crt.dos.time", libd_time64, libc_time64, TIn(__SIZEOF_TIME64_T__), 1, TP)
DFUN(".text.crt.dos.time", libd_difftime64, libc_difftime64, TFD, 2, TIn(__SIZEOF_TIME64_T__), TIn(__SIZEOF_TIME64_T__))
DFUN(".text.crt.dos.time", libd_mktime64, libc_mktime64, TIn(__SIZEOF_TIME64_T__), 1, TP)
DFUN(".text.crt.dos.time", libd_ctime64, libc_ctime64, TP, 1, TP)
DFUN(".text.crt.dos.time", libd_gmtime64, libc_gmtime64, TP, 1, TP)
DFUN(".text.crt.dos.time", libd_localtime64, libc_localtime64, TP, 1, TP)
DFUN(".text.crt.dos.time", libd_stime, libc_stime, TD, 1, TP)
DFUN(".text.crt.dos.time", libd_timegm, libc_timegm, TIn(__SIZEOF_TIME_T__), 1, TP)
DFUN(".text.crt.dos.time", libd_dysize, libc_dysize, TD, 1, TD)
DFUN(".text.crt.dos.time", libd_stime64, libc_stime64, TD, 1, TP)
DFUN(".text.crt.dos.time", libd_timegm64, libc_timegm64, TIn(__SIZEOF_TIME64_T__), 1, TP)
DFUN(".text.crt.dos.time", libd_nanosleep, libc_nanosleep, TD, 2, TP, TP)
DFUN(".text.crt.dos.time", libd_clock_getres, libc_clock_getres, TD, 2, TIn(__SIZEOF_CLOCKID_T__), TP)
DFUN(".text.crt.dos.time", libd_clock_gettime, libc_clock_gettime, TD, 2, TIn(__SIZEOF_CLOCKID_T__), TP)
DFUN(".text.crt.dos.time", libd_clock_settime, libc_clock_settime, TD, 2, TIn(__SIZEOF_CLOCKID_T__), TP)
DFUN(".text.crt.dos.timer", libd_timer_create, libc_timer_create, TD, 3, TIn(__SIZEOF_CLOCKID_T__), TP, TP)
DFUN(".text.crt.dos.timer", libd_timer_delete, libc_timer_delete, TD, 1, TIn(__SIZEOF_TIMER_T__))
DFUN(".text.crt.dos.timer", libd_timer_settime, libc_timer_settime, TD, 4, TIn(__SIZEOF_TIMER_T__), TD, TP, TP)
DFUN(".text.crt.dos.timer", libd_timer_gettime, libc_timer_gettime, TD, 2, TIn(__SIZEOF_TIMER_T__), TP)
DFUN(".text.crt.dos.timer", libd_timer_getoverrun, libc_timer_getoverrun, TD, 1, TIn(__SIZEOF_TIMER_T__))
DFUN(".text.crt.dos.time", libd_clock_nanosleep, libc_clock_nanosleep, TIn(__SIZEOF_ERRNO_T__), 4, TIn(__SIZEOF_CLOCKID_T__), TD, TP, TP)
DFUN(".text.crt.dos.time", libd_clock_getcpuclockid, libc_clock_getcpuclockid, TIn(__SIZEOF_ERRNO_T__), 2, TIn(__SIZEOF_PID_T__), TP)
DFUN(".text.crt.dos.time", libd_nanosleep64, libc_nanosleep64, TD, 2, TP, TP)
DFUN(".text.crt.dos.time", libd_clock_getres64, libc_clock_getres64, TD, 2, TIn(__SIZEOF_CLOCKID_T__), TP)
DFUN(".text.crt.dos.time", libd_clock_gettime64, libc_clock_gettime64, TD, 2, TIn(__SIZEOF_CLOCKID_T__), TP)
DFUN(".text.crt.dos.time", libd_clock_settime64, libc_clock_settime64, TD, 2, TIn(__SIZEOF_CLOCKID_T__), TP)
DFUN(".text.crt.dos.timer", libd_timer_settime64, libc_timer_settime64, TD, 4, TIn(__SIZEOF_TIMER_T__), TD, TP, TP)
DFUN(".text.crt.dos.timer", libd_timer_gettime64, libc_timer_gettime64, TD, 2, TIn(__SIZEOF_TIMER_T__), TP)
DFUN(".text.crt.dos.time", libd_clock_nanosleep64, libc_clock_nanosleep64, TIn(__SIZEOF_ERRNO_T__), 4, TIn(__SIZEOF_CLOCKID_T__), TD, TP, TP)
DFUN(".text.crt.dos.time", libd_timespec_get, libc_timespec_get, TD, 2, TP, TD)
DFUN(".text.crt.dos.time", libd_timespec_get64, libc_timespec_get64, TD, 2, TP, TD)
DFUN(".text.crt.dos.time", libd_timespec_getres, libc_timespec_getres, TD, 2, TP, TD)
DFUN(".text.crt.dos.time", libd_timespec_getres64, libc_timespec_getres64, TD, 2, TP, TD)
DFUN(".text.crt.dos.time", libd_getdate, libc_getdate, TP, 1, TP)
DFUN(".text.crt.dos.time", libd_strftime_l, libc_strftime_l, TI, 5, TP, TI, TP, TP, TP)
DFUN(".text.crt.dos.time", libd_strptime, libc_strptime, TP, 3, TP, TP, TP)
DFUN(".text.crt.dos.time", libd_strptime_l, libc_strptime_l, TP, 4, TP, TP, TP, TP)
DFUN(".text.crt.dos.time", libd_getdate_r, libc_getdate_r, TD, 2, TP, TP)
DFUN(".text.crt.dos.time", libd_clock_adjtime, libc_clock_adjtime, TD, 2, TIn(__SIZEOF_CLOCKID_T__), TP)
DFUN(".text.crt.dos.time", libd_clock_adjtime64, libc_clock_adjtime64, TD, 2, TIn(__SIZEOF_CLOCKID_T__), TP)
DFUN(".text.crt.dos.time", libd_gmtime_r, libc_gmtime_r, TP, 2, TP, TP)
DFUN(".text.crt.dos.time", libd_localtime_r, libc_localtime_r, TP, 2, TP, TP)
DFUN(".text.crt.dos.time", libd_ctime_r, libc_ctime_r, TP, 2, TP, TP)
DFUN(".text.crt.dos.time", libd_gmtime64_r, libc_gmtime64_r, TP, 2, TP, TP)
DFUN(".text.crt.dos.time", libd_localtime64_r, libc_localtime64_r, TP, 2, TP, TP)
DFUN(".text.crt.dos.time", libd_ctime64_r, libc_ctime64_r, TP, 2, TP, TP)
DFUN(".text.crt.dos.time", libd_asctime_r, libc_asctime_r, TP, 2, TP, TP)
DFUN(".text.crt.dos.time.timezone", libd__get_daylight, libc__get_daylight, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.time.timezone", libd__get_timezone, libc__get_timezone, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.time.timezone", libd__get_dstbias, libc__get_dstbias, TIn(__SIZEOF_ERRNO_T__), 1, TP)
DFUN(".text.crt.dos.time", libd__gmtime32_s, libc__gmtime32_s, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libd__gmtime64_s, libd__gmtime32_s);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
DFUN(".text.crt.dos.time", libd__gmtime64_s, libc__gmtime64_s, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DFUN(".text.crt.dos.time", libd__localtime32_s, libc__localtime32_s, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libd__localtime64_s, libd__localtime32_s);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
DFUN(".text.crt.dos.time", libd__localtime64_s, libc__localtime64_s, TIn(__SIZEOF_ERRNO_T__), 2, TP, TP)
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DFUN(".text.crt.dos.time", libd__ctime32_s, libc__ctime32_s, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libd__ctime64_s, libd__ctime32_s);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
DFUN(".text.crt.dos.time", libd__ctime64_s, libc__ctime64_s, TIn(__SIZEOF_ERRNO_T__), 3, TP, TI, TP)
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DFUN(".text.crt.dos.time", libd__strtime, libc__strtime, TP, 1, TP)
DFUN(".text.crt.dos.time", libd__strdate, libc__strdate, TP, 1, TP)
DFUN(".text.crt.dos.time", libd__getsystime, libc__getsystime, TD, 1, TP)
DFUN(".text.crt.dos.time", libd__setsystime, libc__setsystime, TD, 2, TP, TD)
DFUN(".text.crt.dos.compat.glibc", libd___nanosleep_nocancel, libc___nanosleep_nocancel, TD, 2, TP, TP)
DFUN(".text.crt.dos.compat.glibc", libd___nanosleep64_nocancel, libc___nanosleep64_nocancel, TD, 2, TP, TP)

/* timeval-utils */
DFUN(".text.crt.dos.libiberty", libd_timeval_add, libc_timeval_add, TV, 3, TP, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_timeval_sub, libc_timeval_sub, TV, 3, TP, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_timeval_add64, libc_timeval_add64, TV, 3, TP, TP, TP)
DFUN(".text.crt.dos.libiberty", libd_timeval_sub64, libc_timeval_sub64, TV, 3, TP, TP, TP)

/* ttyent */
DFUN(".text.crt.dos.database.tty", libd_getttynam, libc_getttynam, TP, 1, TP)

/* uchar */
DFUN(".text.crt.dos.wchar.unicode.static.mbs", libd_mbrtoc8, libc_mbrtoc8, TI, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.wchar.unicode.static.mbs", libd_c8rtomb, libc_c8rtomb, TI, 3, TP, TI8, TP)
DFUN(".text.crt.dos.wchar.unicode.convert", libd_convert_freev, libc_convert_freev, TV, 1, TP)
DFUN(".text.crt.dos.wchar.unicode.convert", libd_convert_freevn, libc_convert_freevn, TV, 2, TP, TI)

/* ulimit */
DFUN(".text.crt.dos.unsorted", libd_ulimit, libc_ulimit, TP, 2, TD, TL)

/* unicode */
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_readutf8, libc_unicode_readutf8, TI32, 1, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_readutf8_rev, libc_unicode_readutf8_rev, TI32, 1, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_readutf8_n, libc_unicode_readutf8_n, TI32, 2, TP, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_readutf8_rev_n, libc_unicode_readutf8_rev_n, TI32, 2, TP, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_readutf16, libc_unicode_readutf16, TI32, 1, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_readutf16_n, libc_unicode_readutf16_n, TI32, 2, TP, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_readutf16_swap, libc_unicode_readutf16_swap, TI32, 1, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_readutf16_swap_n, libc_unicode_readutf16_swap_n, TI32, 2, TP, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_readutf16_rev, libc_unicode_readutf16_rev, TI32, 1, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_readutf16_swap_rev, libc_unicode_readutf16_swap_rev, TI32, 1, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_readutf16_rev_n, libc_unicode_readutf16_rev_n, TI32, 2, TP, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_readutf16_swap_rev_n, libc_unicode_readutf16_swap_rev_n, TI32, 2, TP, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_writeutf8, libc_unicode_writeutf8, TP, 2, TP, TI32)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_writeutf8_n, libc_unicode_writeutf8_n, TP, 3, TP, TI32, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_writeutf16, libc_unicode_writeutf16, TP, 2, TP, TI32)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_writeutf16_chk, libc_unicode_writeutf16_chk, TP, 2, TP, TI32)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_len8to16, libc_unicode_len8to16, TI, 2, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_len8to32, libc_unicode_len8to32, TI, 2, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_8to16, libc_unicode_8to16, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_8to16_n, libc_unicode_8to16_n, TP, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_8to16_chk, libc_unicode_8to16_chk, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_8to16_chk_n, libc_unicode_8to16_chk_n, TP, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_8to32, libc_unicode_8to32, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_8to32_n, libc_unicode_8to32_n, TP, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_16to8, libc_unicode_16to8, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_16to8_n, libc_unicode_16to8_n, TP, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_16to32, libc_unicode_16to32, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_16to32_n, libc_unicode_16to32_n, TP, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_32to8, libc_unicode_32to8, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_32to8_n, libc_unicode_32to8_n, TP, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_32to16, libc_unicode_32to16, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_32to16_n, libc_unicode_32to16_n, TP, 4, TP, TI, TP, TI)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_c8toc16, libc_unicode_c8toc16, TI, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_c8toc32, libc_unicode_c8toc32, TI, 4, TP, TP, TI, TP)
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_c16toc8, libc_unicode_c16toc8, TI, 3, TP, TI16, TP)
DFUN(".text.crt.dos.unicode.UTF", libd___unicode_descriptor, libc___unicode_descriptor, TP, 1, TI32)
DFUN(".text.crt.dos.unicode.UTF", libd___unicode_descriptor_digit, libc___unicode_descriptor_digit, TI8, 1, TI8)
DFUN(".text.crt.dos.unicode.UTF", libd___unicode_descriptor_digit64, libc___unicode_descriptor_digit64, TI64, 1, TI8)
DFUN(".text.crt.dos.unicode.UTF", libd___unicode_descriptor_digitd, libc___unicode_descriptor_digitd, TFD, 1, TI8)
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libd___unicode_descriptor_digitld, libd___unicode_descriptor_digitd);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unicode.UTF", libd___unicode_descriptor_digitld, libc___unicode_descriptor_digitld, TFL, 1, TI8)
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
DFUN(".text.crt.dos.unicode.UTF", libd_unicode_fold, libc_unicode_fold, TP, 2, TI32, TP)

/* unistd */
DFUN(".text.crt.dos.io.access", libd_pipe, libc_pipe, TD, 1, TP)
DFUN(".text.crt.dos.system.utility", libd_sleep, libc_sleep, TD, 1, TD)
DFUN(".text.crt.dos.io.sync", libd_fsync, libc_fsync, TD, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.sched.process", libd_setpgid, libc_setpgid, TD, 2, TIn(__SIZEOF_PID_T__), TIn(__SIZEOF_PID_T__))
DFUN(".text.crt.dos.sched.user", libd_getgroups, libc_getgroups, TD, 2, TD, TP)
DFUN(".text.crt.dos.sched.user", libd_setuid, libc_setuid, TD, 1, TIn(__SIZEOF_UID_T__))
DFUN(".text.crt.dos.sched.user", libd_setgid, libc_setgid, TD, 1, TIn(__SIZEOF_GID_T__))
DFUN(".text.crt.dos.system.utility", libd_alarm, libc_alarm, TD, 1, TD)
DFUN(".text.crt.dos.fs.property", libd_fpathconf, libc_fpathconf, TP, 2, TIn(__SIZEOF_FD_T__), TD)
DFUN(".text.crt.dos.io.tty", libd_ttyname, libc_ttyname, TP, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.io.tty", libd_ttyname_r, libc_ttyname_r, TIn(__SIZEOF_ERRNO_T__), 3, TIn(__SIZEOF_FD_T__), TP, TI)
DFUN(".text.crt.dos.io.tty", libd_tcgetpgrp, libc_tcgetpgrp, TIn(__SIZEOF_PID_T__), 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.io.tty", libd_tcsetpgrp, libc_tcsetpgrp, TD, 2, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_PID_T__))
DFUN(".text.crt.dos.io.read", libd_read, libc_read, TI, 3, TIn(__SIZEOF_FD_T__), TP, TI)
DFUN(".text.crt.dos.io.write", libd_write, libc_write, TI, 3, TIn(__SIZEOF_FD_T__), TP, TI)
DFUN(".text.crt.dos.io.read", libd_readall, libc_readall, TI, 3, TIn(__SIZEOF_FD_T__), TP, TI)
DFUN(".text.crt.dos.io.write", libd_writeall, libc_writeall, TI, 3, TIn(__SIZEOF_FD_T__), TP, TI)
DFUN(".text.crt.dos.io.seek", libd_lseek, libc_lseek, TIn(__SIZEOF_OFF_T__), 3, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFF_T__), TD)
DFUN(".text.crt.dos.io.tty", libd_isatty, libc_isatty, TD, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.io.access", libd_dup, libc_dup, TIn(__SIZEOF_FD_T__), 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.io.access", libd_close, libc_close, TD, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.io.large.seek", libd_lseek64, libc_lseek64, TIn(__SIZEOF_OFF64_T__), 3, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFF64_T__), TD)
DFUN(".text.crt.dos.io.read", libd_pread, libc_pread, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TIn(__SIZEOF_OFF32_T__))
DFUN(".text.crt.dos.io.write", libd_pwrite, libc_pwrite, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TIn(__SIZEOF_OFF32_T__))
DFUN(".text.crt.dos.io.read", libd_preadall, libc_preadall, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TIn(__SIZEOF_OFF32_T__))
DFUN(".text.crt.dos.io.write", libd_pwriteall, libc_pwriteall, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TIn(__SIZEOF_OFF32_T__))
DFUN(".text.crt.dos.io.large.read", libd_pread64, libc_pread64, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TIn(__SIZEOF_OFF64_T__))
DFUN(".text.crt.dos.io.large.write", libd_pwrite64, libc_pwrite64, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TIn(__SIZEOF_OFF64_T__))
DFUN(".text.crt.dos.io.large.read", libd_preadall64, libc_preadall64, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TIn(__SIZEOF_OFF64_T__))
DFUN(".text.crt.dos.io.large.write", libd_pwriteall64, libc_pwriteall64, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TIn(__SIZEOF_OFF64_T__))
DFUN(".text.crt.dos.io.access", libd_pipe2, libc_pipe2, TD, 2, TP, TIn(__SIZEOF_OFLAG_T__))
DFUN(".text.crt.dos.fs.modify", libd_syncfs, libc_syncfs, TD, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.sched.user", libd_group_member, libc_group_member, TD, 1, TIn(__SIZEOF_GID_T__))
DFUN(".text.crt.dos.sched.user", libd_getresuid, libc_getresuid, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.user", libd_getresgid, libc_getresgid, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.sched.user", libd_setresuid, libc_setresuid, TD, 3, TIn(__SIZEOF_UID_T__), TIn(__SIZEOF_UID_T__), TIn(__SIZEOF_UID_T__))
DFUN(".text.crt.dos.sched.user", libd_setresgid, libc_setresgid, TD, 3, TIn(__SIZEOF_GID_T__), TIn(__SIZEOF_GID_T__), TIn(__SIZEOF_GID_T__))
DFUN(".text.crt.dos.system.utility", libd_usleep, libc_usleep, TD, 1, TIn(__SIZEOF_USECONDS_T__))
DFUN(".text.crt.dos.system.utility", libd_ualarm, libc_ualarm, TIn(__SIZEOF_USECONDS_T__), 2, TIn(__SIZEOF_USECONDS_T__), TIn(__SIZEOF_USECONDS_T__))
DFUN(".text.crt.dos.fs.modify", libd_fchown, libc_fchown, TD, 3, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_UID_T__), TIn(__SIZEOF_GID_T__))
DFUN(".text.crt.dos.fs.basic_property", libd_fchdir, libc_fchdir, TD, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.sched.user", libd_getpgid, libc_getpgid, TIn(__SIZEOF_PID_T__), 1, TIn(__SIZEOF_PID_T__))
DFUN(".text.crt.dos.sched.process", libd_getsid, libc_getsid, TIn(__SIZEOF_PID_T__), 1, TIn(__SIZEOF_PID_T__))
DFUN(".text.crt.dos.fs.exec.exec", libd_fexecve, libc_fexecve, TD, 3, TIn(__SIZEOF_FD_T__), TP, TP)
DFUN(".text.crt.dos.sched.param", libd_nice, libc_nice, TD, 1, TD)
DFUN(".text.crt.dos.system.configuration", libd_confstr, libc_confstr, TI, 3, TD, TP, TI)
DFUN(".text.crt.dos.sched.user", libd_setreuid, libc_setreuid, TD, 2, TIn(__SIZEOF_UID_T__), TIn(__SIZEOF_UID_T__))
DFUN(".text.crt.dos.sched.user", libd_setregid, libc_setregid, TD, 2, TIn(__SIZEOF_GID_T__), TIn(__SIZEOF_GID_T__))
DFUN(".text.crt.dos.sched.user", libd_seteuid, libc_seteuid, TD, 1, TIn(__SIZEOF_UID_T__))
DFUN(".text.crt.dos.sched.user", libd_setegid, libc_setegid, TD, 1, TIn(__SIZEOF_GID_T__))
DFUN(".text.crt.dos.io.tty", libd_getlogin_r, libc_getlogin_r, TD, 2, TP, TI)
DFUN(".text.crt.dos.system.configuration", libd_gethostname, libc_gethostname, TD, 2, TP, TI)
DFUN(".text.crt.dos.io.tty", libd_setlogin, libc_setlogin, TD, 1, TP)
DFUN(".text.crt.dos.system.configuration", libd_sethostname, libc_sethostname, TD, 2, TP, TI)
DFUN(".text.crt.dos.system.configuration", libd_sethostid, libc_sethostid, TD, 1, TP)
DFUN(".text.crt.dos.system.configuration", libd_getdomainname, libc_getdomainname, TD, 2, TP, TI)
DFUN(".text.crt.dos.system.configuration", libd_setdomainname, libc_setdomainname, TD, 2, TP, TI)
DFUN(".text.crt.dos.system.utility", libd_profil, libc_profil, TD, 4, TP, TI, TI, TD)
DFUN(".text.crt.dos.system.utility", libd_daemon, libc_daemon, TD, 2, TD, TD)
DFUN(".text.crt.dos.fs.modify", libd_revoke, libc_revoke, TD, 1, TP)
DFUN(".text.crt.dos.system.utility", libd_syscall, libc_syscall, TP, 7, TP, TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__))
DFUN(".text.crt.dos.system.utility", libd_syscall64, libc_syscall64, TI64, 7, TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__), TIn(__SIZEOF_SYSCALL_LONG_T__))
DFUN(".text.crt.dos.io.tty", libd_getpass, libc_getpass, TP, 1, TP)
DFUN(".text.crt.dos.io.write", libd_ftruncate, libc_ftruncate, TD, 2, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFF32_T__))
DFUN(".text.crt.dos.io.large.write", libd_ftruncate64, libc_ftruncate64, TD, 2, TIn(__SIZEOF_FD_T__), TIn(__SIZEOF_OFF64_T__))
DFUN(".text.crt.dos.heap.utility", libd_brk, libc_brk, TD, 1, TP)
DFUN(".text.crt.dos.heap.utility", libd_sbrk, libc_sbrk, TP, 1, TP)
DFUN(".text.crt.dos.io.sync", libd_fdatasync, libc_fdatasync, TD, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.string.memory", libd_swab, libc_swab, TV, 3, TP, TP, TD)
DFUN(".text.crt.dos.io.tty", libd_ctermid, libc_ctermid, TP, 1, TP)
DFUN(".text.crt.dos.io.tty", libd_cuserid, libc_cuserid, TP, 1, TP)
DFUN(".text.crt.dos.bsd", libd_getpassfd, libc_getpassfd, TP, 6, TP, TP, TI, TP, TD, TD)
DFUN(".text.crt.dos.bsd", libd_getpass_r, libc_getpass_r, TP, 3, TP, TP, TI)
DFUN(".text.crt.dos.bsd", libd_setmode, libc_setmode, TP, 1, TP)
DFUN(".text.crt.dos.bsd", libd_getmode, libc_getmode, TIn(__SIZEOF_MODE_T__), 2, TP, TIn(__SIZEOF_MODE_T__))
DFUN(".text.crt.dos.bsd", libd_getpeereid, libc_getpeereid, TD, 3, TIn(__SIZEOF_FD_T__), TP, TP)
DFUN(".text.crt.dos.bsd.user", libd_setruid, libc_setruid, TD, 1, TIn(__SIZEOF_UID_T__))
DFUN(".text.crt.dos.bsd.user", libd_setrgid, libc_setrgid, TD, 1, TIn(__SIZEOF_GID_T__))
DFUN(".text.crt.dos.io.tty", libd_ctermid_r, libc_ctermid_r, TP, 1, TP)
DFUN(".text.crt.dos.system.configuration", libd_sysconf, libc_sysconf, TP, 1, TD)
DFUN(".text.crt.dos.bsd.io.access", libd_closefrom, libc_closefrom, TV, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.bsd.io.access", libd_close_range, libc_close_range, TD, 3, TD, TD, TD)
DFUN(".text.crt.dos.solaris", libd_tell, libc_tell, TIn(__SIZEOF_OFF_T__), 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.solaris", libd_tell64, libc_tell64, TIn(__SIZEOF_OFF64_T__), 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.compat.glibc", libd___read_nocancel, libc___read_nocancel, TI, 3, TIn(__SIZEOF_FD_T__), TP, TI)
DFUN(".text.crt.dos.compat.glibc", libd___write_nocancel, libc___write_nocancel, TI, 3, TIn(__SIZEOF_FD_T__), TP, TI)
DFUN(".text.crt.dos.compat.glibc", libd___pread64_nocancel, libc___pread64_nocancel, TI, 4, TIn(__SIZEOF_FD_T__), TP, TI, TIn(__SIZEOF_OFF64_T__))

/* util */
DFUN(".text.crt.dos.io.tty", libd_opendev, libc_opendev, TIn(__SIZEOF_FD_T__), 4, TP, TIn(__SIZEOF_OFLAG_T__), TD, TP)
DFUN(".text.crt.dos.FILE.locked.read.read", libd_fparseln, libc_fparseln, TP, 5, TP, TP, TP, TP, TD)

/* utime */
DFUN(".text.crt.dos.fs.modify_time", libd_futime, libc_futime, TD, 2, TIn(__SIZEOF_FD_T__), TP)
DFUN(".text.crt.dos.fs.modify_time", libd_futime64, libc_futime64, TD, 2, TIn(__SIZEOF_FD_T__), TP)

/* utmp */
DFUN(".text.crt.dos.io.tty", libd_login_tty, libc_login_tty, TD, 1, TIn(__SIZEOF_FD_T__))
DFUN(".text.crt.dos.database.utmp", libd_login, libc_login, TV, 1, TP)
DFUN(".text.crt.dos.database.utmp", libd_logout, libc_logout, TD, 1, TP)
DFUN(".text.crt.dos.database.utmp", libd_logwtmp, libc_logwtmp, TV, 3, TP, TP, TP)
DFUN(".text.crt.dos.database.utmp", libd_updwtmp, libc_updwtmp, TV, 2, TP, TP)
DFUN(".text.crt.dos.database.utmp", libd_utmpname, libc_utmpname, TD, 1, TP)
DFUN(".text.crt.dos.database.utmp", libd_getutid, libc_getutid, TP, 1, TP)
DFUN(".text.crt.dos.database.utmp", libd_getutline, libc_getutline, TP, 1, TP)
DFUN(".text.crt.dos.database.utmp", libd_pututline, libc_pututline, TP, 1, TP)
DFUN(".text.crt.dos.database.utmp", libd_getutent_r, libc_getutent_r, TD, 2, TP, TP)
DFUN(".text.crt.dos.database.utmp", libd_getutid_r, libc_getutid_r, TD, 3, TP, TP, TP)
DFUN(".text.crt.dos.database.utmp", libd_getutline_r, libc_getutline_r, TD, 3, TP, TP, TP)

/* utmpx */
DFUN(".text.crt.dos.database.utmpx", libd_getutxid, libc_getutxid, TP, 1, TP)
DFUN(".text.crt.dos.database.utmpx", libd_getutxline, libc_getutxline, TP, 1, TP)
DFUN(".text.crt.dos.database.utmpx", libd_pututxline, libc_pututxline, TP, 1, TP)
DFUN(".text.crt.dos.database.utmpx", libd_utmpxname, libc_utmpxname, TD, 1, TP)
DFUN(".text.crt.dos.database.utmpx", libd_updwtmpx, libc_updwtmpx, TV, 2, TP, TP)
DFUN(".text.crt.dos.database.utmpx", libd_getutmp, libc_getutmp, TV, 2, TP, TP)
DFUN(".text.crt.dos.database.utmpx", libd_getutmpx, libc_getutmpx, TV, 2, TP, TP)

/* vis */
DFUN(".text.crt.dos.bsd.vis", libd_vis, libc_vis, TP, 4, TP, TD, TD, TD)
DFUN(".text.crt.dos.bsd.vis", libd_nvis, libc_nvis, TP, 5, TP, TI, TD, TD, TD)
DFUN(".text.crt.dos.bsd.vis", libd_svis, libc_svis, TP, 5, TP, TD, TD, TD, TP)
DFUN(".text.crt.dos.bsd.vis", libd_snvis, libc_snvis, TP, 6, TP, TI, TD, TD, TD, TP)
DFUN(".text.crt.dos.bsd.vis", libd_strvis, libc_strvis, TD, 3, TP, TP, TD)
DFUN(".text.crt.dos.bsd.vis", libd_stravis, libc_stravis, TD, 3, TP, TP, TD)
DFUN(".text.crt.dos.bsd.vis", libd_strnvis_netbsd, libc_strnvis_netbsd, TD, 4, TP, TI, TP, TD)
DFUN(".text.crt.dos.bsd.vis", libd_strnvis, libc_strnvis, TD, 4, TP, TP, TI, TD)
DFUN(".text.crt.dos.bsd.vis", libd_strsvis, libc_strsvis, TD, 4, TP, TP, TD, TP)
DFUN(".text.crt.dos.bsd.vis", libd_strsnvis, libc_strsnvis, TD, 5, TP, TI, TP, TD, TP)
DFUN(".text.crt.dos.bsd.vis", libd_strvisx, libc_strvisx, TD, 4, TP, TP, TI, TD)
DFUN(".text.crt.dos.bsd.vis", libd_strnvisx, libc_strnvisx, TD, 5, TP, TI, TP, TI, TD)
DFUN(".text.crt.dos.bsd.vis", libd_strenvisx, libc_strenvisx, TD, 6, TP, TI, TP, TI, TD, TP)
DFUN(".text.crt.dos.bsd.vis", libd_strsvisx, libc_strsvisx, TD, 5, TP, TP, TI, TD, TP)
DFUN(".text.crt.dos.bsd.vis", libd_strsnvisx, libc_strsnvisx, TD, 6, TP, TI, TP, TI, TD, TP)
DFUN(".text.crt.dos.bsd.vis", libd_strsenvisx, libc_strsenvisx, TD, 7, TP, TI, TP, TI, TD, TP, TP)
DFUN(".text.crt.dos.bsd.vis", libd_strunvis, libc_strunvis, TD, 2, TP, TP)
DFUN(".text.crt.dos.bsd.vis", libd_strnunvis_netbsd, libc_strnunvis_netbsd, TD, 3, TP, TI, TP)
DFUN(".text.crt.dos.bsd.vis", libd_strnunvis, libc_strnunvis, TD, 3, TP, TP, TI)
DFUN(".text.crt.dos.bsd.vis", libd_strunvisx, libc_strunvisx, TD, 3, TP, TP, TD)
DFUN(".text.crt.dos.bsd.vis", libd_strnunvisx, libc_strnunvisx, TD, 4, TP, TI, TP, TD)
DFUN(".text.crt.dos.bsd.vis", libd_unvis, libc_unvis, TD, 4, TP, TD, TP, TD)

/* wchar */
DFUN(".text.crt.dos.wchar.unicode.static.mbs", libd_mbsinit, libc_mbsinit, TD, 1, TP)
DFUN(".text.crt.dos.wchar.FILE.locked.utility", libd_fwide, libc_fwide, TD, 2, TP, TD)

/* wctype */
DFUN(".text.crt.dos.wchar.unicode.static.ctype", libd_wctrans, libc_wctrans, TIn(__SIZEOF_WCTRANS_T__), 1, TP)
DFUN(".text.crt.dos.wchar.unicode.static.ctype", libd_wctype, libc_wctype, TIn(__SIZEOF_WCTYPE_T__), 1, TP)
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_wctype_l, libd_wctype);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.wchar.unicode.locale.ctype", libd_wctype_l, libc_wctype_l, TIn(__SIZEOF_WCTYPE_T__), 2, TP, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_wctrans_l, libd_wctrans);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.wchar.unicode.locale.ctype", libd_wctrans_l, libc_wctrans_l, TIn(__SIZEOF_WCTRANS_T__), 2, TP, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.wchar.unicode.static.mbs", libd_isleadbyte, libc_isleadbyte, TD, 1, TD)
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd__isleadbyte_l, libd_isleadbyte);
#else /* __LIBDCALL_CALLER_CLEANUP */
DFUN(".text.crt.dos.wchar.unicode.locale.mbs", libd__isleadbyte_l, libc__isleadbyte_l, TD, 2, TD, TP)
#endif /* !__LIBDCALL_CALLER_CLEANUP */

/* wordexp */
DFUN(".text.crt.dos.wordexp", libd_wordexp, libc_wordexp, TD, 3, TP, TP, TD)
DFUN(".text.crt.dos.wordexp", libd_wordfree, libc_wordfree, TV, 1, TP)
