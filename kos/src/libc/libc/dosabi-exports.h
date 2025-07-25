/* HASH CRC-32:0x8356574f */
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
#ifndef DEFINE_PUBLIC_ALIAS
#define DEFINE_PUBLIC_ALIAS(new_name, old_name)
#endif /* !DEFINE_PUBLIC_ALIAS */

/* aio */
DEFINE_PUBLIC_ALIAS(DOS$aio_read, libd_aio_read);
DEFINE_PUBLIC_ALIAS(DOS$aio_write, libd_aio_write);
DEFINE_PUBLIC_ALIAS(DOS$aio_fsync, libd_aio_fsync);
DEFINE_PUBLIC_ALIAS(DOS$lio_listio, libd_lio_listio);
DEFINE_PUBLIC_ALIAS(DOS$aio_error, libd_aio_error);
DEFINE_PUBLIC_ALIAS(DOS$aio_return, libd_aio_return);
DEFINE_PUBLIC_ALIAS(DOS$aio_cancel, libd_aio_cancel);
DEFINE_PUBLIC_ALIAS(DOS$aio_suspend, libd_aio_suspend);
DEFINE_PUBLIC_ALIAS(DOS$aio_read64, libd_aio_read64);
DEFINE_PUBLIC_ALIAS(DOS$aio_write64, libd_aio_write64);
DEFINE_PUBLIC_ALIAS(DOS$aio_fsync64, libd_aio_fsync64);
DEFINE_PUBLIC_ALIAS(DOS$lio_listio64, libd_lio_listio64);
DEFINE_PUBLIC_ALIAS(DOS$aio_error64, libd_aio_error64);
DEFINE_PUBLIC_ALIAS(DOS$aio_return64, libd_aio_return64);
DEFINE_PUBLIC_ALIAS(DOS$aio_cancel64, libd_aio_cancel64);
DEFINE_PUBLIC_ALIAS(DOS$aio_suspend64, libd_aio_suspend64);
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__aio_suspend_time64, libd_aio_suspendt64);
DEFINE_PUBLIC_ALIAS(DOS$aio_suspendt64, libd_aio_suspendt64);
DEFINE_PUBLIC_ALIAS(DOS$__aio_suspend64_time64, libd_aio_suspend64t64);
DEFINE_PUBLIC_ALIAS(DOS$aio_suspend64t64, libd_aio_suspend64t64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$aio_init, libd_aio_init);

/* aliases */
DEFINE_PUBLIC_ALIAS(DOS$__getaliasent_r, libd_getaliasent_r);
DEFINE_PUBLIC_ALIAS(DOS$getaliasent_r, libd_getaliasent_r);
DEFINE_PUBLIC_ALIAS(DOS$getaliasbyname, libd_getaliasbyname);
DEFINE_PUBLIC_ALIAS(DOS$__getaliasbyname_r, libd_getaliasbyname_r);
DEFINE_PUBLIC_ALIAS(DOS$getaliasbyname_r, libd_getaliasbyname_r);

/* argp */
DEFINE_PUBLIC_ALIAS(DOS$__argp_parse, libd_argp_parse);
DEFINE_PUBLIC_ALIAS(DOS$argp_parse, libd_argp_parse);
DEFINE_PUBLIC_ALIAS(DOS$__argp_help, libd_argp_help);
DEFINE_PUBLIC_ALIAS(DOS$argp_help, libd_argp_help);
DEFINE_PUBLIC_ALIAS(DOS$__argp_state_help, libd_argp_state_help);
DEFINE_PUBLIC_ALIAS(DOS$argp_state_help, libd_argp_state_help);
DEFINE_PUBLIC_ALIAS(DOS$__argp_usage, libd_argp_usage);
DEFINE_PUBLIC_ALIAS(DOS$argp_usage, libd_argp_usage);
DEFINE_PUBLIC_ALIAS(DOS$__option_is_short, libd__option_is_short);
DEFINE_PUBLIC_ALIAS(DOS$_option_is_short, libd__option_is_short);
DEFINE_PUBLIC_ALIAS(DOS$__option_is_end, libd__option_is_end);
DEFINE_PUBLIC_ALIAS(DOS$_option_is_end, libd__option_is_end);
DEFINE_PUBLIC_ALIAS(DOS$__argp_input, libd__argp_input);
DEFINE_PUBLIC_ALIAS(DOS$_argp_input, libd__argp_input);

/* argz */
DEFINE_PUBLIC_ALIAS(DOS$__argz_create, libd_argz_create);
DEFINE_PUBLIC_ALIAS(DOS$argz_create, libd_argz_create);
DEFINE_PUBLIC_ALIAS(DOS$__argz_create_sep, libd_argz_create_sep);
DEFINE_PUBLIC_ALIAS(DOS$argz_create_sep, libd_argz_create_sep);
DEFINE_PUBLIC_ALIAS(DOS$__argz_count, libd_argz_count);
DEFINE_PUBLIC_ALIAS(DOS$argz_count, libd_argz_count);
DEFINE_PUBLIC_ALIAS(DOS$__argz_extract, libd_argz_extract);
DEFINE_PUBLIC_ALIAS(DOS$argz_extract, libd_argz_extract);
DEFINE_PUBLIC_ALIAS(DOS$__argz_stringify, libd_argz_stringify);
DEFINE_PUBLIC_ALIAS(DOS$argz_stringify, libd_argz_stringify);
DEFINE_PUBLIC_ALIAS(DOS$__argz_create_sep, libd_argz_append);
DEFINE_PUBLIC_ALIAS(DOS$__argz_append, libd_argz_append);
DEFINE_PUBLIC_ALIAS(DOS$argz_append, libd_argz_append);
DEFINE_PUBLIC_ALIAS(DOS$__argz_add, libd_argz_add);
DEFINE_PUBLIC_ALIAS(DOS$argz_add, libd_argz_add);
DEFINE_PUBLIC_ALIAS(DOS$__argz_add_sep, libd_argz_add_sep);
DEFINE_PUBLIC_ALIAS(DOS$argz_add_sep, libd_argz_add_sep);
DEFINE_PUBLIC_ALIAS(DOS$__argz_delete, libd_argz_delete);
DEFINE_PUBLIC_ALIAS(DOS$argz_delete, libd_argz_delete);
DEFINE_PUBLIC_ALIAS(DOS$__argz_insert, libd_argz_insert);
DEFINE_PUBLIC_ALIAS(DOS$argz_insert, libd_argz_insert);
DEFINE_PUBLIC_ALIAS(DOS$__argz_replace, libd_argz_replace);
DEFINE_PUBLIC_ALIAS(DOS$argz_replace, libd_argz_replace);
DEFINE_PUBLIC_ALIAS(DOS$__argz_next, libd_argz_next);
DEFINE_PUBLIC_ALIAS(DOS$argz_next, libd_argz_next);

/* arpa.inet */
DEFINE_PUBLIC_ALIAS(DOS$inet_netof, libd_inet_netof);
DEFINE_PUBLIC_ALIAS(DOS$inet_lnaof, libd_inet_lnaof);
DEFINE_PUBLIC_ALIAS(DOS$inet_makeaddr, libd_inet_makeaddr);
DEFINE_PUBLIC_ALIAS(DOS$inet_addr, libd_inet_addr);
DEFINE_PUBLIC_ALIAS(DOS$inet_ntoa, libd_inet_ntoa);
DEFINE_PUBLIC_ALIAS(DOS$inet_ntoa_r, libd_inet_ntoa_r);
DEFINE_PUBLIC_ALIAS(DOS$inet_network, libd_inet_network);
DEFINE_PUBLIC_ALIAS(DOS$inet_aton, libd_inet_aton);
DEFINE_PUBLIC_ALIAS(DOS$inet_paton, libd_inet_paton);
DEFINE_PUBLIC_ALIAS(DOS$inet_neta, libd_inet_neta);
DEFINE_PUBLIC_ALIAS(DOS$inet_net_ntop, libd_inet_net_ntop);
DEFINE_PUBLIC_ALIAS(DOS$inet_net_pton, libd_inet_net_pton);
DEFINE_PUBLIC_ALIAS(DOS$inet_nsap_addr, libd_inet_nsap_addr);
DEFINE_PUBLIC_ALIAS(DOS$inet_nsap_ntoa, libd_inet_nsap_ntoa);
DEFINE_PUBLIC_ALIAS(DOS$inet_pton, libd_inet_pton);
DEFINE_PUBLIC_ALIAS(DOS$inet_ntop, libd_inet_ntop);

/* arpa.nameser */
DEFINE_PUBLIC_ALIAS(DOS$ns_get16, libd_ns_get16);
DEFINE_PUBLIC_ALIAS(DOS$ns_get32, libd_ns_get32);
DEFINE_PUBLIC_ALIAS(DOS$putshort, libd_ns_put16);
DEFINE_PUBLIC_ALIAS(DOS$__putshort, libd_ns_put16);
DEFINE_PUBLIC_ALIAS(DOS$ns_put16, libd_ns_put16);
DEFINE_PUBLIC_ALIAS(DOS$putlong, libd_ns_put32);
DEFINE_PUBLIC_ALIAS(DOS$__putlong, libd_ns_put32);
DEFINE_PUBLIC_ALIAS(DOS$ns_put32, libd_ns_put32);
DEFINE_PUBLIC_ALIAS(DOS$ns_initparse, libd_ns_initparse);
DEFINE_PUBLIC_ALIAS(DOS$ns_skiprr, libd_ns_skiprr);
DEFINE_PUBLIC_ALIAS(DOS$ns_parserr, libd_ns_parserr);
DEFINE_PUBLIC_ALIAS(DOS$ns_sprintrr, libd_ns_sprintrr);
DEFINE_PUBLIC_ALIAS(DOS$ns_sprintrrf, libd_ns_sprintrrf);
DEFINE_PUBLIC_ALIAS(DOS$ns_format_ttl, libd_ns_format_ttl);
DEFINE_PUBLIC_ALIAS(DOS$ns_parse_ttl, libd_ns_parse_ttl);
DEFINE_PUBLIC_ALIAS(DOS$ns_datetosecs, libd_ns_datetosecs);
DEFINE_PUBLIC_ALIAS(DOS$ns_name_ntol, libd_ns_name_ntol);
DEFINE_PUBLIC_ALIAS(DOS$ns_name_ntop, libd_ns_name_ntop);
DEFINE_PUBLIC_ALIAS(DOS$ns_name_pton, libd_ns_name_pton);
DEFINE_PUBLIC_ALIAS(DOS$ns_name_unpack, libd_ns_name_unpack);
DEFINE_PUBLIC_ALIAS(DOS$ns_name_pack, libd_ns_name_pack);
DEFINE_PUBLIC_ALIAS(DOS$ns_name_uncompress, libd_ns_name_uncompress);
DEFINE_PUBLIC_ALIAS(DOS$ns_name_compress, libd_ns_name_compress);
DEFINE_PUBLIC_ALIAS(DOS$ns_name_skip, libd_ns_name_skip);
DEFINE_PUBLIC_ALIAS(DOS$ns_name_rollback, libd_ns_name_rollback);
DEFINE_PUBLIC_ALIAS(DOS$ns_sign, libd_ns_sign);
DEFINE_PUBLIC_ALIAS(DOS$ns_sign2, libd_ns_sign2);
DEFINE_PUBLIC_ALIAS(DOS$ns_sign_tcp, libd_ns_sign_tcp);
DEFINE_PUBLIC_ALIAS(DOS$ns_sign_tcp2, libd_ns_sign_tcp2);
DEFINE_PUBLIC_ALIAS(DOS$ns_sign_tcp_init, libd_ns_sign_tcp_init);
DEFINE_PUBLIC_ALIAS(DOS$ns_find_tsig, libd_ns_find_tsig);
DEFINE_PUBLIC_ALIAS(DOS$ns_verify, libd_ns_verify);
DEFINE_PUBLIC_ALIAS(DOS$ns_verify_tcp, libd_ns_verify_tcp);
DEFINE_PUBLIC_ALIAS(DOS$ns_verify_tcp_init, libd_ns_verify_tcp_init);
DEFINE_PUBLIC_ALIAS(DOS$ns_samedomain, libd_ns_samedomain);
DEFINE_PUBLIC_ALIAS(DOS$ns_subdomain, libd_ns_subdomain);
DEFINE_PUBLIC_ALIAS(DOS$ns_makecanon, libd_ns_makecanon);
DEFINE_PUBLIC_ALIAS(DOS$ns_samename, libd_ns_samename);
DEFINE_PUBLIC_ALIAS(DOS$__dn_comp, libd_dn_comp);
DEFINE_PUBLIC_ALIAS(DOS$dn_comp, libd_dn_comp);

/* attr.attributes */
DEFINE_PUBLIC_ALIAS(DOS$attr_get, libd_attr_get);
DEFINE_PUBLIC_ALIAS(DOS$attr_getf, libd_attr_getf);
DEFINE_PUBLIC_ALIAS(DOS$attr_set, libd_attr_set);
DEFINE_PUBLIC_ALIAS(DOS$attr_setf, libd_attr_setf);
DEFINE_PUBLIC_ALIAS(DOS$attr_remove, libd_attr_remove);
DEFINE_PUBLIC_ALIAS(DOS$attr_removef, libd_attr_removef);
DEFINE_PUBLIC_ALIAS(DOS$attr_list, libd_attr_list);
DEFINE_PUBLIC_ALIAS(DOS$attr_listf, libd_attr_listf);
DEFINE_PUBLIC_ALIAS(DOS$attr_multi, libd_attr_multi);
DEFINE_PUBLIC_ALIAS(DOS$attr_multif, libd_attr_multif);

/* bsd.libutil */
DEFINE_PUBLIC_ALIAS(DOS$flopen, libd_flopen);
DEFINE_PUBLIC_ALIAS(DOS$flopenat, libd_flopenat);

/* complex */
DEFINE_PUBLIC_ALIAS(DOS$__cabsf, libd_cabsf);
DEFINE_PUBLIC_ALIAS(DOS$cabsf, libd_cabsf);
DEFINE_PUBLIC_ALIAS(DOS$cexpf, libd_cexpf);
DEFINE_PUBLIC_ALIAS(DOS$clogf, libd_clogf);
DEFINE_PUBLIC_ALIAS(DOS$cpowf, libd_cpowf);
DEFINE_PUBLIC_ALIAS(DOS$csqrtf, libd_csqrtf);
DEFINE_PUBLIC_ALIAS(DOS$csinf, libd_csinf);
DEFINE_PUBLIC_ALIAS(DOS$ccosf, libd_ccosf);
DEFINE_PUBLIC_ALIAS(DOS$ctanf, libd_ctanf);
DEFINE_PUBLIC_ALIAS(DOS$casinf, libd_casinf);
DEFINE_PUBLIC_ALIAS(DOS$cacosf, libd_cacosf);
DEFINE_PUBLIC_ALIAS(DOS$catanf, libd_catanf);
DEFINE_PUBLIC_ALIAS(DOS$csinhf, libd_csinhf);
DEFINE_PUBLIC_ALIAS(DOS$ccoshf, libd_ccoshf);
DEFINE_PUBLIC_ALIAS(DOS$ctanhf, libd_ctanhf);
DEFINE_PUBLIC_ALIAS(DOS$casinhf, libd_casinhf);
DEFINE_PUBLIC_ALIAS(DOS$cacoshf, libd_cacoshf);
DEFINE_PUBLIC_ALIAS(DOS$catanhf, libd_catanhf);
DEFINE_PUBLIC_ALIAS(DOS$cargf, libd_cargf);
DEFINE_PUBLIC_ALIAS(DOS$conjf, libd_conjf);
DEFINE_PUBLIC_ALIAS(DOS$crealf, libd_crealf);
DEFINE_PUBLIC_ALIAS(DOS$cimagf, libd_cimagf);
DEFINE_PUBLIC_ALIAS(DOS$cprojf, libd_cprojf);
DEFINE_PUBLIC_ALIAS(DOS$_cabs, libd_cabs);
DEFINE_PUBLIC_ALIAS(DOS$__cabs, libd_cabs);
DEFINE_PUBLIC_ALIAS(DOS$cabs, libd_cabs);
DEFINE_PUBLIC_ALIAS(DOS$cexp, libd_cexp);
DEFINE_PUBLIC_ALIAS(DOS$clog, libd_clog);
DEFINE_PUBLIC_ALIAS(DOS$cpow, libd_cpow);
DEFINE_PUBLIC_ALIAS(DOS$csqrt, libd_csqrt);
DEFINE_PUBLIC_ALIAS(DOS$csin, libd_csin);
DEFINE_PUBLIC_ALIAS(DOS$ccos, libd_ccos);
DEFINE_PUBLIC_ALIAS(DOS$ctan, libd_ctan);
DEFINE_PUBLIC_ALIAS(DOS$casin, libd_casin);
DEFINE_PUBLIC_ALIAS(DOS$cacos, libd_cacos);
DEFINE_PUBLIC_ALIAS(DOS$catan, libd_catan);
DEFINE_PUBLIC_ALIAS(DOS$csinh, libd_csinh);
DEFINE_PUBLIC_ALIAS(DOS$ccosh, libd_ccosh);
DEFINE_PUBLIC_ALIAS(DOS$ctanh, libd_ctanh);
DEFINE_PUBLIC_ALIAS(DOS$casinh, libd_casinh);
DEFINE_PUBLIC_ALIAS(DOS$cacosh, libd_cacosh);
DEFINE_PUBLIC_ALIAS(DOS$catanh, libd_catanh);
DEFINE_PUBLIC_ALIAS(DOS$carg, libd_carg);
DEFINE_PUBLIC_ALIAS(DOS$conj, libd_conj);
DEFINE_PUBLIC_ALIAS(DOS$creal, libd_creal);
DEFINE_PUBLIC_ALIAS(DOS$cimag, libd_cimag);
DEFINE_PUBLIC_ALIAS(DOS$cproj, libd_cproj);
DEFINE_PUBLIC_ALIAS(DOS$__cabsl, libd_cabsl);
DEFINE_PUBLIC_ALIAS(DOS$cabsl, libd_cabsl);
DEFINE_PUBLIC_ALIAS(DOS$cexpl, libd_cexpl);
DEFINE_PUBLIC_ALIAS(DOS$clogl, libd_clogl);
DEFINE_PUBLIC_ALIAS(DOS$cpowl, libd_cpowl);
DEFINE_PUBLIC_ALIAS(DOS$csqrtl, libd_csqrtl);
DEFINE_PUBLIC_ALIAS(DOS$csinl, libd_csinl);
DEFINE_PUBLIC_ALIAS(DOS$ccosl, libd_ccosl);
DEFINE_PUBLIC_ALIAS(DOS$ctanl, libd_ctanl);
DEFINE_PUBLIC_ALIAS(DOS$casinl, libd_casinl);
DEFINE_PUBLIC_ALIAS(DOS$cacosl, libd_cacosl);
DEFINE_PUBLIC_ALIAS(DOS$catanl, libd_catanl);
DEFINE_PUBLIC_ALIAS(DOS$csinhl, libd_csinhl);
DEFINE_PUBLIC_ALIAS(DOS$ccoshl, libd_ccoshl);
DEFINE_PUBLIC_ALIAS(DOS$ctanhl, libd_ctanhl);
DEFINE_PUBLIC_ALIAS(DOS$casinhl, libd_casinhl);
DEFINE_PUBLIC_ALIAS(DOS$cacoshl, libd_cacoshl);
DEFINE_PUBLIC_ALIAS(DOS$catanhl, libd_catanhl);
DEFINE_PUBLIC_ALIAS(DOS$cargl, libd_cargl);
DEFINE_PUBLIC_ALIAS(DOS$conjl, libd_conjl);
DEFINE_PUBLIC_ALIAS(DOS$creall, libd_creall);
DEFINE_PUBLIC_ALIAS(DOS$cimagl, libd_cimagl);
DEFINE_PUBLIC_ALIAS(DOS$cprojl, libd_cprojl);

/* conio */
DEFINE_PUBLIC_ALIAS(DOS$_putch, libd__putch);
DEFINE_PUBLIC_ALIAS(DOS$_putch_nolock, libd__putch_nolock);
DEFINE_PUBLIC_ALIAS(DOS$_ungetch, libd__ungetch);
DEFINE_PUBLIC_ALIAS(DOS$_ungetch_nolock, libd__ungetch_nolock);
DEFINE_PUBLIC_ALIAS(DOS$_cgets, libd__cgets);
DEFINE_PUBLIC_ALIAS(DOS$_cgets_s, libd__cgets_s);
DEFINE_PUBLIC_ALIAS(DOS$_cputs, libd__cputs);
DEFINE_PUBLIC_ALIAS(DOS$__conio_common_vcprintf, libd___conio_common_vcprintf);
DEFINE_PUBLIC_ALIAS(DOS$__conio_common_vcprintf_s, libd___conio_common_vcprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$__conio_common_vcprintf_p, libd___conio_common_vcprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$__conio_common_vcscanf, libd___conio_common_vcscanf);
DEFINE_PUBLIC_ALIAS(DOS$_vcprintf_l, libd__vcprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vcprintf_s_l, libd__vcprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vcprintf_p_l, libd__vcprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vcscanf_l, libd__vcscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vcscanf_s_l, libd__vcscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vcprintf, libd__vcprintf);
DEFINE_PUBLIC_ALIAS(DOS$_vcprintf_s, libd__vcprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$_vcprintf_p, libd__vcprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vcscanf, libd__vcscanf);
DEFINE_PUBLIC_ALIAS(DOS$_vcscanf_s, libd__vcscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$gotoxy, libd_gotoxy);
DEFINE_PUBLIC_ALIAS(DOS$textcolor, libd_textcolor);
DEFINE_PUBLIC_ALIAS(DOS$textbackground, libd_textbackground);
DEFINE_PUBLIC_ALIAS(DOS$textattr, libd_textattr);
DEFINE_PUBLIC_ALIAS(DOS$_conio_getpass, libd__conio_getpass);
DEFINE_PUBLIC_ALIAS(DOS$cputsxy, libd_cputsxy);
DEFINE_PUBLIC_ALIAS(DOS$putchxy, libd_putchxy);
DEFINE_PUBLIC_ALIAS(DOS$window, libd_window);
DEFINE_PUBLIC_ALIAS(DOS$movetext, libd_movetext);

/* corecrt_malloc */
DEFINE_PUBLIC_ALIAS(DOS$_aligned_malloc, libd__aligned_malloc);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_offset_malloc, libd__aligned_offset_malloc);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_realloc, libd__aligned_realloc);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_recalloc, libd__aligned_recalloc);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_offset_realloc, libd__aligned_offset_realloc);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_offset_recalloc, libd__aligned_offset_recalloc);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_msize, libd__aligned_msize);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_free, libd__aligned_free);

/* crypt */
DEFINE_PUBLIC_ALIAS(DOS$setkey, libd_setkey);
DEFINE_PUBLIC_ALIAS(DOS$crypt, libd_crypt);
DEFINE_PUBLIC_ALIAS(DOS$encrypt, libd_encrypt);
DEFINE_PUBLIC_ALIAS(DOS$crypt_r, libd_crypt_r);
DEFINE_PUBLIC_ALIAS(DOS$setkey_r, libd_setkey_r);
DEFINE_PUBLIC_ALIAS(DOS$encrypt_r, libd_encrypt_r);

/* ctype */
DEFINE_PUBLIC_ALIAS(DOS$__locale_ctype_ptr_l, libd___locale_ctype_ptr_l);
DEFINE_PUBLIC_ALIAS(DOS$iscntrl, libd_iscntrl);
DEFINE_PUBLIC_ALIAS(DOS$isspace, libd_isspace);
DEFINE_PUBLIC_ALIAS(DOS$isupper, libd_isupper);
DEFINE_PUBLIC_ALIAS(DOS$islower, libd_islower);
DEFINE_PUBLIC_ALIAS(DOS$isalpha, libd_isalpha);
DEFINE_PUBLIC_ALIAS(DOS$isdigit, libd_isdigit);
DEFINE_PUBLIC_ALIAS(DOS$isxdigit, libd_isxdigit);
DEFINE_PUBLIC_ALIAS(DOS$isalnum, libd_isalnum);
DEFINE_PUBLIC_ALIAS(DOS$ispunct, libd_ispunct);
DEFINE_PUBLIC_ALIAS(DOS$isgraph, libd_isgraph);
DEFINE_PUBLIC_ALIAS(DOS$isprint, libd_isprint);
DEFINE_PUBLIC_ALIAS(DOS$tolower, libd_tolower);
DEFINE_PUBLIC_ALIAS(DOS$toupper, libd_toupper);
DEFINE_PUBLIC_ALIAS(DOS$isblank, libd_isblank);
DEFINE_PUBLIC_ALIAS(DOS$_iscntrl_l, libd_iscntrl_l);
DEFINE_PUBLIC_ALIAS(DOS$__iscntrl_l, libd_iscntrl_l);
DEFINE_PUBLIC_ALIAS(DOS$iscntrl_l, libd_iscntrl_l);
DEFINE_PUBLIC_ALIAS(DOS$_isspace_l, libd_isspace_l);
DEFINE_PUBLIC_ALIAS(DOS$__isspace_l, libd_isspace_l);
DEFINE_PUBLIC_ALIAS(DOS$isspace_l, libd_isspace_l);
DEFINE_PUBLIC_ALIAS(DOS$_isupper_l, libd_isupper_l);
DEFINE_PUBLIC_ALIAS(DOS$__isupper_l, libd_isupper_l);
DEFINE_PUBLIC_ALIAS(DOS$isupper_l, libd_isupper_l);
DEFINE_PUBLIC_ALIAS(DOS$_islower_l, libd_islower_l);
DEFINE_PUBLIC_ALIAS(DOS$__islower_l, libd_islower_l);
DEFINE_PUBLIC_ALIAS(DOS$islower_l, libd_islower_l);
DEFINE_PUBLIC_ALIAS(DOS$_isalpha_l, libd_isalpha_l);
DEFINE_PUBLIC_ALIAS(DOS$__isalpha_l, libd_isalpha_l);
DEFINE_PUBLIC_ALIAS(DOS$isalpha_l, libd_isalpha_l);
DEFINE_PUBLIC_ALIAS(DOS$_isdigit_l, libd_isdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$__isdigit_l, libd_isdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$isdigit_l, libd_isdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$_isxdigit_l, libd_isxdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$__isxdigit_l, libd_isxdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$isxdigit_l, libd_isxdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$_isalnum_l, libd_isalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$__isalnum_l, libd_isalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$isalnum_l, libd_isalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$_ispunct_l, libd_ispunct_l);
DEFINE_PUBLIC_ALIAS(DOS$__ispunct_l, libd_ispunct_l);
DEFINE_PUBLIC_ALIAS(DOS$ispunct_l, libd_ispunct_l);
DEFINE_PUBLIC_ALIAS(DOS$_isgraph_l, libd_isgraph_l);
DEFINE_PUBLIC_ALIAS(DOS$__isgraph_l, libd_isgraph_l);
DEFINE_PUBLIC_ALIAS(DOS$isgraph_l, libd_isgraph_l);
DEFINE_PUBLIC_ALIAS(DOS$_isprint_l, libd_isprint_l);
DEFINE_PUBLIC_ALIAS(DOS$__isprint_l, libd_isprint_l);
DEFINE_PUBLIC_ALIAS(DOS$isprint_l, libd_isprint_l);
DEFINE_PUBLIC_ALIAS(DOS$_isblank_l, libd_isblank_l);
DEFINE_PUBLIC_ALIAS(DOS$__isblank_l, libd_isblank_l);
DEFINE_PUBLIC_ALIAS(DOS$isblank_l, libd_isblank_l);
DEFINE_PUBLIC_ALIAS(DOS$_tolower_l, libd_tolower_l);
DEFINE_PUBLIC_ALIAS(DOS$__tolower_l, libd_tolower_l);
DEFINE_PUBLIC_ALIAS(DOS$tolower_l, libd_tolower_l);
DEFINE_PUBLIC_ALIAS(DOS$_toupper_l, libd_toupper_l);
DEFINE_PUBLIC_ALIAS(DOS$__toupper_l, libd_toupper_l);
DEFINE_PUBLIC_ALIAS(DOS$toupper_l, libd_toupper_l);
DEFINE_PUBLIC_ALIAS(DOS$__iscsymf, libd___iscsymf);
DEFINE_PUBLIC_ALIAS(DOS$__iscsym, libd___iscsym);
DEFINE_PUBLIC_ALIAS(DOS$__isascii, libd_isascii);
DEFINE_PUBLIC_ALIAS(DOS$isascii, libd_isascii);
DEFINE_PUBLIC_ALIAS(DOS$__toascii, libd_toascii);
DEFINE_PUBLIC_ALIAS(DOS$toascii, libd_toascii);
DEFINE_PUBLIC_ALIAS(DOS$_tolower, libd__tolower);
DEFINE_PUBLIC_ALIAS(DOS$_toupper, libd__toupper);
DEFINE_PUBLIC_ALIAS(DOS$___mb_cur_max_l_func, libd____mb_cur_max_l_func);
DEFINE_PUBLIC_ALIAS(DOS$_chvalidator_l, libd__chvalidator_l);
DEFINE_PUBLIC_ALIAS(DOS$_chvalidator, libd__isctype);
DEFINE_PUBLIC_ALIAS(DOS$_isctype, libd__isctype);
DEFINE_PUBLIC_ALIAS(DOS$_isctype_l, libd__isctype_l);

/* direct */
DEFINE_PUBLIC_ALIAS(DOS$_chdrive, libd__chdrive);
DEFINE_PUBLIC_ALIAS(DOS$_getdiskfree, libd__getdiskfree);

/* dirent */
DEFINE_PUBLIC_ALIAS(DOS$__libc_closedir, libd_closedir);
DEFINE_PUBLIC_ALIAS(DOS$__closedir, libd_closedir);
DEFINE_PUBLIC_ALIAS(DOS$closedir, libd_closedir);
DEFINE_PUBLIC_ALIAS(DOS$fdclosedir, libd_fdclosedir);
DEFINE_PUBLIC_ALIAS(DOS$readdirk, libd_readdirk);
DEFINE_PUBLIC_ALIAS(DOS$__libc_rewinddir, libd_rewinddir);
DEFINE_PUBLIC_ALIAS(DOS$rewinddir, libd_rewinddir);
DEFINE_PUBLIC_ALIAS(DOS$fdopendir, libd_fdopendir);
DEFINE_PUBLIC_ALIAS(DOS$readdirk64, libd_readdirk64);
DEFINE_PUBLIC_ALIAS(DOS$readdirk_r, libd_readdirk_r);
DEFINE_PUBLIC_ALIAS(DOS$readdirk64_r, libd_readdirk64_r);
DEFINE_PUBLIC_ALIAS(DOS$__libc_seekdir, libd_seekdir);
DEFINE_PUBLIC_ALIAS(DOS$seekdir, libd_seekdir);
DEFINE_PUBLIC_ALIAS(DOS$__libc_telldir, libd_telldir);
DEFINE_PUBLIC_ALIAS(DOS$telldir, libd_telldir);
DEFINE_PUBLIC_ALIAS(DOS$dirfd, libd_dirfd);
DEFINE_PUBLIC_ALIAS(DOS$alphasortk, libd_alphasortk);
DEFINE_PUBLIC_ALIAS(DOS$alphasortk64, libd_alphasortk64);
DEFINE_PUBLIC_ALIAS(DOS$__getdirentries, libd_getdirentries);
DEFINE_PUBLIC_ALIAS(DOS$__libc_getdirentries, libd_getdirentries);
DEFINE_PUBLIC_ALIAS(DOS$getdirentries, libd_getdirentries);
DEFINE_PUBLIC_ALIAS(DOS$getdirentries64, libd_getdirentries64);
DEFINE_PUBLIC_ALIAS(DOS$versionsortk, libd_versionsortk);
DEFINE_PUBLIC_ALIAS(DOS$versionsortk64, libd_versionsortk64);
DEFINE_PUBLIC_ALIAS(DOS$kreaddir, libd_kreaddir);
DEFINE_PUBLIC_ALIAS(DOS$kreaddirf, libd_kreaddirf);
DEFINE_PUBLIC_ALIAS(DOS$kreaddir64, libd_kreaddir64);
DEFINE_PUBLIC_ALIAS(DOS$kreaddirf64, libd_kreaddirf64);

/* dyn-string */
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_init, libd_dyn_string_init);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_new, libd_dyn_string_new);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_delete, libd_dyn_string_delete);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_release, libd_dyn_string_release);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_resize, libd_dyn_string_resize);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_clear, libd_dyn_string_clear);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_copy, libd_dyn_string_copy);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_copy_cstr, libd_dyn_string_copy_cstr);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_prepend, libd_dyn_string_prepend);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_prepend_cstr, libd_dyn_string_prepend_cstr);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_insert, libd_dyn_string_insert);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_insert_cstr, libd_dyn_string_insert_cstr);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_insert_char, libd_dyn_string_insert_char);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_append, libd_dyn_string_append);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_append_cstr, libd_dyn_string_append_cstr);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_append_char, libd_dyn_string_append_char);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_substring, libd_dyn_string_substring);
DEFINE_PUBLIC_ALIAS(DOS$dyn_string_eq, libd_dyn_string_eq);

/* envz */
DEFINE_PUBLIC_ALIAS(DOS$envz_entry, libd_envz_entry);
DEFINE_PUBLIC_ALIAS(DOS$envz_get, libd_envz_get);
DEFINE_PUBLIC_ALIAS(DOS$envz_add, libd_envz_add);
DEFINE_PUBLIC_ALIAS(DOS$envz_merge, libd_envz_merge);
DEFINE_PUBLIC_ALIAS(DOS$envz_remove, libd_envz_remove);
DEFINE_PUBLIC_ALIAS(DOS$envz_strip, libd_envz_strip);

/* err */
DEFINE_PUBLIC_ALIAS(DOS$vwarn, libd_vwarn);
DEFINE_PUBLIC_ALIAS(DOS$vwarnc, libd_vwarnc);
DEFINE_PUBLIC_ALIAS(DOS$vwarnx, libd_vwarnx);
DEFINE_PUBLIC_ALIAS(DOS$verr, libd_verr);
DEFINE_PUBLIC_ALIAS(DOS$verrc, libd_verrc);
DEFINE_PUBLIC_ALIAS(DOS$verrx, libd_verrx);

/* execinfo */
DEFINE_PUBLIC_ALIAS(DOS$__backtrace, libd_backtrace);
DEFINE_PUBLIC_ALIAS(DOS$backtrace, libd_backtrace);
DEFINE_PUBLIC_ALIAS(DOS$__backtrace_symbols, libd_backtrace_symbols);
DEFINE_PUBLIC_ALIAS(DOS$backtrace_symbols, libd_backtrace_symbols);
DEFINE_PUBLIC_ALIAS(DOS$__backtrace_symbols_fd, libd_backtrace_symbols_fd);
DEFINE_PUBLIC_ALIAS(DOS$backtrace_symbols_fd, libd_backtrace_symbols_fd);
DEFINE_PUBLIC_ALIAS(DOS$__backtrace_symbols, libd_backtrace_symbols_fmt);
DEFINE_PUBLIC_ALIAS(DOS$backtrace_symbols_fmt, libd_backtrace_symbols_fmt);
DEFINE_PUBLIC_ALIAS(DOS$__backtrace_symbols_fd, libd_backtrace_symbols_fd_fmt);
DEFINE_PUBLIC_ALIAS(DOS$backtrace_symbols_fd_fmt, libd_backtrace_symbols_fd_fmt);
DEFINE_PUBLIC_ALIAS(DOS$backtrace_symbol_printf, libd_backtrace_symbol_printf);

/* fcntl */
DEFINE_PUBLIC_ALIAS(DOS$readahead, libd_readahead);
DEFINE_PUBLIC_ALIAS(DOS$sync_file_range, libd_sync_file_range);
DEFINE_PUBLIC_ALIAS(DOS$vmsplice, libd_vmsplice);
DEFINE_PUBLIC_ALIAS(DOS$splice, libd_splice);
DEFINE_PUBLIC_ALIAS(DOS$tee, libd_tee);
DEFINE_PUBLIC_ALIAS(DOS$name_to_handle_at, libd_name_to_handle_at);
DEFINE_PUBLIC_ALIAS(DOS$open_by_handle_at, libd_open_by_handle_at);
DEFINE_PUBLIC_ALIAS(DOS$fallocate, libd_fallocate);
DEFINE_PUBLIC_ALIAS(DOS$fallocate64, libd_fallocate64);
DEFINE_PUBLIC_ALIAS(DOS$__fcntl, libd_fcntl);
DEFINE_PUBLIC_ALIAS(DOS$__libc_fcntl, libd_fcntl);
DEFINE_PUBLIC_ALIAS(DOS$fcntl, libd_fcntl);
DEFINE_PUBLIC_ALIAS(DOS$posix_fadvise, libd_posix_fadvise);
DEFINE_PUBLIC_ALIAS(DOS$posix_fallocate, libd_posix_fallocate);
DEFINE_PUBLIC_ALIAS(DOS$posix_fadvise64, libd_posix_fadvise64);
DEFINE_PUBLIC_ALIAS(DOS$posix_fallocate64, libd_posix_fallocate64);
DEFINE_PUBLIC_ALIAS(DOS$_locking, libd_lockf);
DEFINE_PUBLIC_ALIAS(DOS$lockf, libd_lockf);
DEFINE_PUBLIC_ALIAS(DOS$lockf64, libd_lockf64);
DEFINE_PUBLIC_ALIAS(DOS$directio, libd_directio);

/* fenv */
DEFINE_PUBLIC_ALIAS(DOS$feraiseexcept, libd_feraiseexcept);
DEFINE_PUBLIC_ALIAS(DOS$feclearexcept, libd_feclearexcept);
DEFINE_PUBLIC_ALIAS(DOS$fegetexceptflag, libd_fegetexceptflag);
DEFINE_PUBLIC_ALIAS(DOS$fesetexceptflag, libd_fesetexceptflag);
DEFINE_PUBLIC_ALIAS(DOS$fetestexcept, libd_fetestexcept);
DEFINE_PUBLIC_ALIAS(DOS$fesetround, libd_fesetround);
DEFINE_PUBLIC_ALIAS(DOS$fegetenv, libd_fegetenv);
DEFINE_PUBLIC_ALIAS(DOS$feholdexcept, libd_feholdexcept);
DEFINE_PUBLIC_ALIAS(DOS$fesetenv, libd_fesetenv);
DEFINE_PUBLIC_ALIAS(DOS$feupdateenv, libd_feupdateenv);
DEFINE_PUBLIC_ALIAS(DOS$feenableexcept, libd_feenableexcept);
DEFINE_PUBLIC_ALIAS(DOS$fedisableexcept, libd_fedisableexcept);
DEFINE_PUBLIC_ALIAS(DOS$fesetexcept, libd_fesetexcept);
DEFINE_PUBLIC_ALIAS(DOS$fetestexceptflag, libd_fetestexceptflag);
DEFINE_PUBLIC_ALIAS(DOS$fegetmode, libd_fegetmode);
DEFINE_PUBLIC_ALIAS(DOS$fesetmode, libd_fesetmode);

/* float */
DEFINE_PUBLIC_ALIAS(DOS$_controlfp, libd__controlfp);
DEFINE_PUBLIC_ALIAS(DOS$_set_controlfp, libd__set_controlfp);
DEFINE_PUBLIC_ALIAS(DOS$_controlfp_s, libd__controlfp_s);
DEFINE_PUBLIC_ALIAS(DOS$_statusfp2, libd__statusfp2);
DEFINE_PUBLIC_ALIAS(DOS$_control87, libd__control87);
DEFINE_PUBLIC_ALIAS(DOS$__control87_2, libd___control87_2);
DEFINE_PUBLIC_ALIAS(DOS$_fpclass, libd__fpclass);
DEFINE_PUBLIC_ALIAS(DOS$_fpclassf, libd__fpclassf);

/* fmtmsg */
DEFINE_PUBLIC_ALIAS(DOS$fmtmsg, libd_fmtmsg);
DEFINE_PUBLIC_ALIAS(DOS$addseverity, libd_addseverity);

/* fnmatch */
DEFINE_PUBLIC_ALIAS(DOS$fnmatch, libd_fnmatch);

/* format-printer */
DEFINE_PUBLIC_ALIAS(DOS$format_repeat, libd_format_repeat);
DEFINE_PUBLIC_ALIAS(DOS$format_quote, libd_format_escape);
DEFINE_PUBLIC_ALIAS(DOS$format_escape, libd_format_escape);
DEFINE_PUBLIC_ALIAS(DOS$format_hexdump, libd_format_hexdump);
DEFINE_PUBLIC_ALIAS(DOS$format_vprintf, libd_format_vprintf);
DEFINE_PUBLIC_ALIAS(DOS$format_vscanf, libd_format_vscanf);
DEFINE_PUBLIC_ALIAS(DOS$format_aprintf_pack, libd_format_aprintf_pack);
DEFINE_PUBLIC_ALIAS(DOS$format_aprintf_alloc, libd_format_aprintf_alloc);

/* fstab */
DEFINE_PUBLIC_ALIAS(DOS$getfsspec, libd_getfsspec);
DEFINE_PUBLIC_ALIAS(DOS$getfsfile, libd_getfsfile);

/* fts */
DEFINE_PUBLIC_ALIAS(DOS$fts_children, libd_fts_children);
DEFINE_PUBLIC_ALIAS(DOS$fts_close, libd_fts_close);
DEFINE_PUBLIC_ALIAS(DOS$fts_read, libd_fts_read);
DEFINE_PUBLIC_ALIAS(DOS$fts_set, libd_fts_set);
DEFINE_PUBLIC_ALIAS(DOS$fts64_children, libd_fts64_children);
DEFINE_PUBLIC_ALIAS(DOS$fts64_close, libd_fts64_close);
DEFINE_PUBLIC_ALIAS(DOS$fts64_read, libd_fts64_read);
DEFINE_PUBLIC_ALIAS(DOS$fts64_set, libd_fts64_set);

/* getopt */
DEFINE_PUBLIC_ALIAS(DOS$bsd_getopt, libd_getopt);
DEFINE_PUBLIC_ALIAS(DOS$getopt, libd_getopt);
DEFINE_PUBLIC_ALIAS(DOS$__posix_getopt, libd___posix_getopt);
DEFINE_PUBLIC_ALIAS(DOS$getopt_long, libd_getopt_long);
DEFINE_PUBLIC_ALIAS(DOS$getopt_long_only, libd_getopt_long_only);

/* grp */
DEFINE_PUBLIC_ALIAS(DOS$getgrgid, libd_getgrgid);
DEFINE_PUBLIC_ALIAS(DOS$getgrnam, libd_getgrnam);
DEFINE_PUBLIC_ALIAS(DOS$putgrent, libd_putgrent);
DEFINE_PUBLIC_ALIAS(DOS$__getgrgid_r, libd_getgrgid_r);
DEFINE_PUBLIC_ALIAS(DOS$getgrgid_r, libd_getgrgid_r);
DEFINE_PUBLIC_ALIAS(DOS$__getgrnam_r, libd_getgrnam_r);
DEFINE_PUBLIC_ALIAS(DOS$getgrnam_r, libd_getgrnam_r);
DEFINE_PUBLIC_ALIAS(DOS$__getgrent_r, libd_getgrent_r);
DEFINE_PUBLIC_ALIAS(DOS$getgrent_r, libd_getgrent_r);
DEFINE_PUBLIC_ALIAS(DOS$__fgetgrent_r, libd_fgetgrent_r);
DEFINE_PUBLIC_ALIAS(DOS$fgetgrent_r, libd_fgetgrent_r);
DEFINE_PUBLIC_ALIAS(DOS$fgetgrgid_r, libd_fgetgrgid_r);
DEFINE_PUBLIC_ALIAS(DOS$fgetgrnam_r, libd_fgetgrnam_r);
DEFINE_PUBLIC_ALIAS(DOS$fgetgrent, libd_fgetgrent);
DEFINE_PUBLIC_ALIAS(DOS$__setgroups, libd_setgroups);
DEFINE_PUBLIC_ALIAS(DOS$__libc_setgroups, libd_setgroups);
DEFINE_PUBLIC_ALIAS(DOS$setgroups, libd_setgroups);
DEFINE_PUBLIC_ALIAS(DOS$getgrouplist, libd_getgrouplist);
DEFINE_PUBLIC_ALIAS(DOS$initgroups, libd_initgroups);
DEFINE_PUBLIC_ALIAS(DOS$setgroupent, libd_setgroupent);
DEFINE_PUBLIC_ALIAS(DOS$gid_from_group, libd_gid_from_group);
DEFINE_PUBLIC_ALIAS(DOS$group_from_gid, libd_group_from_gid);

/* ifaddrs */
DEFINE_PUBLIC_ALIAS(DOS$getifaddrs, libd_getifaddrs);
DEFINE_PUBLIC_ALIAS(DOS$freeifaddrs, libd_freeifaddrs);

/* inttypes */
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ && __SIZEOF_INTMAX_T__ != 8
DEFINE_PUBLIC_ALIAS(DOS$imaxabs, libd_imaxabs);
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ && __SIZEOF_INTMAX_T__ != 8 */
#if __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS(DOS$imaxdiv, libd_imaxdiv);
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ */
#if __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ && __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8
DEFINE_PUBLIC_ALIAS(DOS$strtoimax, libd_strtoimax);
DEFINE_PUBLIC_ALIAS(DOS$strtoumax, libd_strtoumax);
DEFINE_PUBLIC_ALIAS(DOS$_strtoimax_l, libd_strtoimax_l);
DEFINE_PUBLIC_ALIAS(DOS$strtoimax_l, libd_strtoimax_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoumax_l, libd_strtoumax_l);
DEFINE_PUBLIC_ALIAS(DOS$strtoumax_l, libd_strtoumax_l);
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG_LONG__ && __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 */
DEFINE_PUBLIC_ALIAS(DOS$strtoi, libd_strtoi);
DEFINE_PUBLIC_ALIAS(DOS$strtou, libd_strtou);
DEFINE_PUBLIC_ALIAS(DOS$strtoi_l, libd_strtoi_l);
DEFINE_PUBLIC_ALIAS(DOS$strtou_l, libd_strtou_l);

/* io */
DEFINE_PUBLIC_ALIAS(DOS$_umask_s, libd__umask_s);
DEFINE_PUBLIC_ALIAS(DOS$_setmode, libd__setmode);
DEFINE_PUBLIC_ALIAS(DOS$_findclose, libd__findclose);
DEFINE_PUBLIC_ALIAS(DOS$_findnext, libd__findnext32);
DEFINE_PUBLIC_ALIAS(DOS$_findnext32, libd__findnext32);
DEFINE_PUBLIC_ALIAS(DOS$_findnexti64, libd__findnext32i64);
DEFINE_PUBLIC_ALIAS(DOS$_findnext32i64, libd__findnext32i64);
DEFINE_PUBLIC_ALIAS(DOS$_findnext64i32, libd__findnext64);
DEFINE_PUBLIC_ALIAS(DOS$_findnext64, libd__findnext64);
DEFINE_PUBLIC_ALIAS(DOS$_mktemp_s, libd__mktemp_s);
DEFINE_PUBLIC_ALIAS(DOS$_pipe, libd__pipe);
DEFINE_PUBLIC_ALIAS(DOS$_filelengthi64, libd__filelengthi64);
DEFINE_PUBLIC_ALIAS(DOS$__lock_fhandle, libd___lock_fhandle);
DEFINE_PUBLIC_ALIAS(DOS$_unlock_fhandle, libd__unlock_fhandle);
DEFINE_PUBLIC_ALIAS(DOS$_get_osfhandle, libd__get_osfhandle);
DEFINE_PUBLIC_ALIAS(DOS$_open_osfhandle, libd__open_osfhandle);
DEFINE_PUBLIC_ALIAS(DOS$_filelength, libd__filelength);
DEFINE_PUBLIC_ALIAS(DOS$_eof, libd__eof);

/* kos.dosfs */
DEFINE_PUBLIC_ALIAS(DOS$dosfs_setenabled, libd_dosfs_setenabled);

/* kos.nopf */
#include <kos/bits/nopf.h>
#ifndef __arch_readb_nopf
DEFINE_PUBLIC_ALIAS(DOS$readb_nopf, libd_readb_nopf);
#endif /* !__arch_readb_nopf */
#ifndef __arch_readw_nopf
DEFINE_PUBLIC_ALIAS(DOS$readw_nopf, libd_readw_nopf);
#endif /* !__arch_readw_nopf */
#ifndef __arch_readl_nopf
DEFINE_PUBLIC_ALIAS(DOS$readl_nopf, libd_readl_nopf);
#endif /* !__arch_readl_nopf */
#ifndef __arch_readq_nopf
DEFINE_PUBLIC_ALIAS(DOS$readq_nopf, libd_readq_nopf);
#endif /* !__arch_readq_nopf */
#ifndef __arch_writeb_nopf
DEFINE_PUBLIC_ALIAS(DOS$writeb_nopf, libd_writeb_nopf);
#endif /* !__arch_writeb_nopf */
#ifndef __arch_writew_nopf
DEFINE_PUBLIC_ALIAS(DOS$writew_nopf, libd_writew_nopf);
#endif /* !__arch_writew_nopf */
#ifndef __arch_writel_nopf
DEFINE_PUBLIC_ALIAS(DOS$writel_nopf, libd_writel_nopf);
#endif /* !__arch_writel_nopf */
#ifndef __arch_writeq_nopf
DEFINE_PUBLIC_ALIAS(DOS$writeq_nopf, libd_writeq_nopf);
#endif /* !__arch_writeq_nopf */
#ifndef __arch_memcpy_nopf
DEFINE_PUBLIC_ALIAS(DOS$memcpy_nopf, libd_memcpy_nopf);
#endif /* !__arch_memcpy_nopf */
#ifndef __arch_memset_nopf
DEFINE_PUBLIC_ALIAS(DOS$memset_nopf, libd_memset_nopf);
#endif /* !__arch_memset_nopf */
#ifndef __arch_nopf_memeq
DEFINE_PUBLIC_ALIAS(DOS$memeq_nopf, libd_memeq_nopf);
#endif /* !__arch_nopf_memeq */

/* kos.rpc */
DEFINE_PUBLIC_ALIAS(DOS$rpc_schedule, libd_rpc_schedule);
DEFINE_PUBLIC_ALIAS(DOS$rpc_exec, libd_rpc_exec);
DEFINE_PUBLIC_ALIAS(DOS$rpc_interrupt, libd_rpc_interrupt);
DEFINE_PUBLIC_ALIAS(DOS$RpcSchedule, libd_RpcSchedule);
DEFINE_PUBLIC_ALIAS(DOS$RpcExec, libd_RpcExec);
DEFINE_PUBLIC_ALIAS(DOS$RpcInterrupt, libd_RpcInterrupt);

/* kos.uuid */
DEFINE_PUBLIC_ALIAS(DOS$uuid_fromstr, libd_uuid_fromstr);

/* langinfo */
DEFINE_PUBLIC_ALIAS(DOS$nl_langinfo, libd_nl_langinfo);
DEFINE_PUBLIC_ALIAS(DOS$__nl_langinfo_l, libd_nl_langinfo_l);
DEFINE_PUBLIC_ALIAS(DOS$nl_langinfo_l, libd_nl_langinfo_l);

/* libgen */
DEFINE_PUBLIC_ALIAS(DOS$dirname, libd_dirname);
DEFINE_PUBLIC_ALIAS(DOS$__gnu_basename, libd___xpg_basename);
DEFINE_PUBLIC_ALIAS(DOS$__xpg_basename, libd___xpg_basename);
DEFINE_PUBLIC_ALIAS(DOS$bgets, libd_bgets);
DEFINE_PUBLIC_ALIAS(DOS$bufsplit, libd_bufsplit);
DEFINE_PUBLIC_ALIAS(DOS$strcadd, libd_strcadd);
DEFINE_PUBLIC_ALIAS(DOS$strccpy, libd_strccpy);
DEFINE_PUBLIC_ALIAS(DOS$streadd, libd_streadd);
DEFINE_PUBLIC_ALIAS(DOS$strecpy, libd_strecpy);
DEFINE_PUBLIC_ALIAS(DOS$strfind, libd_strfind);
DEFINE_PUBLIC_ALIAS(DOS$strrspn, libd_strrspn);
DEFINE_PUBLIC_ALIAS(DOS$strtrns, libd_strtrns);

/* libiberty */
DEFINE_PUBLIC_ALIAS(DOS$C_alloca, libd_C_alloca);
DEFINE_PUBLIC_ALIAS(DOS$stack_limit_increase, libd_stack_limit_increase);
#ifndef _WIN32
DEFINE_PUBLIC_ALIAS(DOS$dos_lbasename, libd_dos_lbasename);
#endif /* !_WIN32 */
#ifdef _WIN32
DEFINE_PUBLIC_ALIAS(DOS$unix_lbasename, libd_unix_lbasename);
#endif /* _WIN32 */
DEFINE_PUBLIC_ALIAS(DOS$lrealpath, libd_lrealpath);
DEFINE_PUBLIC_ALIAS(DOS$strtoerrno, libd_strtoerrno);
DEFINE_PUBLIC_ALIAS(DOS$unlock_stream, libd_unlock_stream);
DEFINE_PUBLIC_ALIAS(DOS$fopen_unlocked, libd_fopen_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fdopen_unlocked, libd_fdopen_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$spaces, libd_spaces);
DEFINE_PUBLIC_ALIAS(DOS$xmalloc_set_program_name, libd_xmalloc_set_program_name);
DEFINE_PUBLIC_ALIAS(DOS$xmalloc_failed, libd_xmalloc_failed);
DEFINE_PUBLIC_ALIAS(DOS$xmalloc, libd_xmalloc);
DEFINE_PUBLIC_ALIAS(DOS$xrealloc, libd_xrealloc);
DEFINE_PUBLIC_ALIAS(DOS$xcalloc, libd_xcalloc);
DEFINE_PUBLIC_ALIAS(DOS$xstrdup, libd_xstrdup);
DEFINE_PUBLIC_ALIAS(DOS$xstrndup, libd_xstrndup);
DEFINE_PUBLIC_ALIAS(DOS$xmemdup, libd_xmemdup);
DEFINE_PUBLIC_ALIAS(DOS$xvasprintf, libd_xvasprintf);
DEFINE_PUBLIC_ALIAS(DOS$dupargv, libd_dupargv);
DEFINE_PUBLIC_ALIAS(DOS$freeargv, libd_freeargv);
DEFINE_PUBLIC_ALIAS(DOS$countargv, libd_countargv);
DEFINE_PUBLIC_ALIAS(DOS$fdmatch, libd_fdmatch);
DEFINE_PUBLIC_ALIAS(DOS$buildargv, libd_buildargv);
DEFINE_PUBLIC_ALIAS(DOS$expandargv, libd_expandargv);
DEFINE_PUBLIC_ALIAS(DOS$writeargv, libd_writeargv);
DEFINE_PUBLIC_ALIAS(DOS$make_relative_prefix, libd_make_relative_prefix);
DEFINE_PUBLIC_ALIAS(DOS$make_relative_prefix_ignore_links, libd_make_relative_prefix_ignore_links);
DEFINE_PUBLIC_ALIAS(DOS$make_temp_file_with_prefix, libd_make_temp_file_with_prefix);
DEFINE_PUBLIC_ALIAS(DOS$make_temp_file, libd_make_temp_file);
DEFINE_PUBLIC_ALIAS(DOS$unlink_if_ordinary, libd_unlink_if_ordinary);
DEFINE_PUBLIC_ALIAS(DOS$xcrc32, libd_xcrc32);
DEFINE_PUBLIC_ALIAS(DOS$pex_run, libd_pex_run);
DEFINE_PUBLIC_ALIAS(DOS$pex_run_in_environment, libd_pex_run_in_environment);
DEFINE_PUBLIC_ALIAS(DOS$pex_input_file, libd_pex_input_file);
DEFINE_PUBLIC_ALIAS(DOS$pex_input_pipe, libd_pex_input_pipe);
DEFINE_PUBLIC_ALIAS(DOS$pex_read_output, libd_pex_read_output);
DEFINE_PUBLIC_ALIAS(DOS$pex_read_err, libd_pex_read_err);
DEFINE_PUBLIC_ALIAS(DOS$pex_get_status, libd_pex_get_status);
DEFINE_PUBLIC_ALIAS(DOS$pex_init, libd_pex_init);
DEFINE_PUBLIC_ALIAS(DOS$pex_get_times, libd_pex_get_times);
DEFINE_PUBLIC_ALIAS(DOS$pex_free, libd_pex_free);
DEFINE_PUBLIC_ALIAS(DOS$pex_one, libd_pex_one);
DEFINE_PUBLIC_ALIAS(DOS$pexecute, libd_pexecute);
DEFINE_PUBLIC_ALIAS(DOS$pwait, libd_pwait);

/* libintl */
DEFINE_PUBLIC_ALIAS(DOS$__dcgettext, libd_dcgettext);
DEFINE_PUBLIC_ALIAS(DOS$dcgettext, libd_dcgettext);
DEFINE_PUBLIC_ALIAS(DOS$__dgettext, libd_dgettext);
DEFINE_PUBLIC_ALIAS(DOS$dgettext, libd_dgettext);
DEFINE_PUBLIC_ALIAS(DOS$__gettext, libd_gettext);
DEFINE_PUBLIC_ALIAS(DOS$gettext, libd_gettext);
DEFINE_PUBLIC_ALIAS(DOS$ngettext, libd_ngettext);
DEFINE_PUBLIC_ALIAS(DOS$dngettext, libd_dngettext);
DEFINE_PUBLIC_ALIAS(DOS$__dcngettext, libd_dcngettext);
DEFINE_PUBLIC_ALIAS(DOS$dcngettext, libd_dcngettext);
DEFINE_PUBLIC_ALIAS(DOS$__textdomain, libd_textdomain);
DEFINE_PUBLIC_ALIAS(DOS$textdomain, libd_textdomain);
DEFINE_PUBLIC_ALIAS(DOS$__bindtextdomain, libd_bindtextdomain);
DEFINE_PUBLIC_ALIAS(DOS$bindtextdomain, libd_bindtextdomain);
DEFINE_PUBLIC_ALIAS(DOS$bind_textdomain_codeset, libd_bind_textdomain_codeset);

/* locale */
DEFINE_PUBLIC_ALIAS(DOS$setlocale, libd_setlocale);
DEFINE_PUBLIC_ALIAS(DOS$__newlocale, libd_newlocale);
DEFINE_PUBLIC_ALIAS(DOS$newlocale, libd_newlocale);
DEFINE_PUBLIC_ALIAS(DOS$__duplocale, libd_duplocale);
DEFINE_PUBLIC_ALIAS(DOS$duplocale, libd_duplocale);
DEFINE_PUBLIC_ALIAS(DOS$__freelocale, libd_freelocale);
DEFINE_PUBLIC_ALIAS(DOS$freelocale, libd_freelocale);
DEFINE_PUBLIC_ALIAS(DOS$__uselocale, libd_uselocale);
DEFINE_PUBLIC_ALIAS(DOS$uselocale, libd_uselocale);
DEFINE_PUBLIC_ALIAS(DOS$_configthreadlocale, libd__configthreadlocale);
DEFINE_PUBLIC_ALIAS(DOS$__create_locale, libd__create_locale);
DEFINE_PUBLIC_ALIAS(DOS$_create_locale, libd__create_locale);
DEFINE_PUBLIC_ALIAS(DOS$__free_locale, libd__free_locale);
DEFINE_PUBLIC_ALIAS(DOS$_free_locale, libd__free_locale);
DEFINE_PUBLIC_ALIAS(DOS$_Strftime, libd__Strftime);

/* malloc */
DEFINE_PUBLIC_ALIAS(DOS$_expand, libd_realloc_in_place);
DEFINE_PUBLIC_ALIAS(DOS$realloc_in_place, libd_realloc_in_place);
DEFINE_PUBLIC_ALIAS(DOS$aligned_alloc, libd_memalign);
DEFINE_PUBLIC_ALIAS(DOS$__libc_memalign, libd_memalign);
DEFINE_PUBLIC_ALIAS(DOS$__memalign, libd_memalign);
DEFINE_PUBLIC_ALIAS(DOS$memalign, libd_memalign);
DEFINE_PUBLIC_ALIAS(DOS$__pvalloc, libd_pvalloc);
DEFINE_PUBLIC_ALIAS(DOS$pvalloc, libd_pvalloc);
DEFINE_PUBLIC_ALIAS(DOS$__libc_valloc, libd_valloc);
DEFINE_PUBLIC_ALIAS(DOS$__valloc, libd_valloc);
DEFINE_PUBLIC_ALIAS(DOS$valloc, libd_valloc);
DEFINE_PUBLIC_ALIAS(DOS$posix_memalign, libd_posix_memalign);
DEFINE_PUBLIC_ALIAS(DOS$__malloc_trim, libd_malloc_trim);
DEFINE_PUBLIC_ALIAS(DOS$malloc_trim, libd_malloc_trim);
DEFINE_PUBLIC_ALIAS(DOS$_msize, libd_malloc_usable_size);
DEFINE_PUBLIC_ALIAS(DOS$_msize_debug, libd_malloc_usable_size);
DEFINE_PUBLIC_ALIAS(DOS$__malloc_usable_size, libd_malloc_usable_size);
DEFINE_PUBLIC_ALIAS(DOS$malloc_usable_size, libd_malloc_usable_size);
DEFINE_PUBLIC_ALIAS(DOS$__mallopt, libd_mallopt);
DEFINE_PUBLIC_ALIAS(DOS$mallopt, libd_mallopt);
DEFINE_PUBLIC_ALIAS(DOS$__memdup, libd_memdup);
DEFINE_PUBLIC_ALIAS(DOS$memdup, libd_memdup);
DEFINE_PUBLIC_ALIAS(DOS$__memcdup, libd_memcdup);
DEFINE_PUBLIC_ALIAS(DOS$memcdup, libd_memcdup);
DEFINE_PUBLIC_ALIAS(DOS$__libc_reallocarray, libd_reallocarray);
DEFINE_PUBLIC_ALIAS(DOS$reallocarray, libd_reallocarray);
DEFINE_PUBLIC_ALIAS(DOS$recalloc, libd_recalloc);
DEFINE_PUBLIC_ALIAS(DOS$_recalloc, libd_recallocv);
DEFINE_PUBLIC_ALIAS(DOS$recallocv, libd_recallocv);

/* math */
DEFINE_PUBLIC_ALIAS(DOS$__acos, libd_acos);
DEFINE_PUBLIC_ALIAS(DOS$acos, libd_acos);
DEFINE_PUBLIC_ALIAS(DOS$__asin, libd_asin);
DEFINE_PUBLIC_ALIAS(DOS$asin, libd_asin);
DEFINE_PUBLIC_ALIAS(DOS$__atan, libd_atan);
DEFINE_PUBLIC_ALIAS(DOS$atan, libd_atan);
DEFINE_PUBLIC_ALIAS(DOS$__atan2, libd_atan2);
DEFINE_PUBLIC_ALIAS(DOS$atan2, libd_atan2);
DEFINE_PUBLIC_ALIAS(DOS$__cos, libd_cos);
DEFINE_PUBLIC_ALIAS(DOS$cos, libd_cos);
DEFINE_PUBLIC_ALIAS(DOS$__sin, libd_sin);
DEFINE_PUBLIC_ALIAS(DOS$sin, libd_sin);
DEFINE_PUBLIC_ALIAS(DOS$__tan, libd_tan);
DEFINE_PUBLIC_ALIAS(DOS$tan, libd_tan);
DEFINE_PUBLIC_ALIAS(DOS$__acosf, libd_acosf);
DEFINE_PUBLIC_ALIAS(DOS$acosf, libd_acosf);
DEFINE_PUBLIC_ALIAS(DOS$__asinf, libd_asinf);
DEFINE_PUBLIC_ALIAS(DOS$asinf, libd_asinf);
DEFINE_PUBLIC_ALIAS(DOS$__atanf, libd_atanf);
DEFINE_PUBLIC_ALIAS(DOS$atanf, libd_atanf);
DEFINE_PUBLIC_ALIAS(DOS$__atan2f, libd_atan2f);
DEFINE_PUBLIC_ALIAS(DOS$atan2f, libd_atan2f);
DEFINE_PUBLIC_ALIAS(DOS$__cosf, libd_cosf);
DEFINE_PUBLIC_ALIAS(DOS$cosf, libd_cosf);
DEFINE_PUBLIC_ALIAS(DOS$__sinf, libd_sinf);
DEFINE_PUBLIC_ALIAS(DOS$sinf, libd_sinf);
DEFINE_PUBLIC_ALIAS(DOS$__tanf, libd_tanf);
DEFINE_PUBLIC_ALIAS(DOS$tanf, libd_tanf);
DEFINE_PUBLIC_ALIAS(DOS$__acosl, libd_acosl);
DEFINE_PUBLIC_ALIAS(DOS$acosl, libd_acosl);
DEFINE_PUBLIC_ALIAS(DOS$__asinl, libd_asinl);
DEFINE_PUBLIC_ALIAS(DOS$asinl, libd_asinl);
DEFINE_PUBLIC_ALIAS(DOS$__atanl, libd_atanl);
DEFINE_PUBLIC_ALIAS(DOS$atanl, libd_atanl);
DEFINE_PUBLIC_ALIAS(DOS$__atan2l, libd_atan2l);
DEFINE_PUBLIC_ALIAS(DOS$atan2l, libd_atan2l);
DEFINE_PUBLIC_ALIAS(DOS$__cosl, libd_cosl);
DEFINE_PUBLIC_ALIAS(DOS$cosl, libd_cosl);
DEFINE_PUBLIC_ALIAS(DOS$__sinl, libd_sinl);
DEFINE_PUBLIC_ALIAS(DOS$sinl, libd_sinl);
DEFINE_PUBLIC_ALIAS(DOS$__tanl, libd_tanl);
DEFINE_PUBLIC_ALIAS(DOS$tanl, libd_tanl);
DEFINE_PUBLIC_ALIAS(DOS$__cosh, libd_cosh);
DEFINE_PUBLIC_ALIAS(DOS$cosh, libd_cosh);
DEFINE_PUBLIC_ALIAS(DOS$__sinh, libd_sinh);
DEFINE_PUBLIC_ALIAS(DOS$sinh, libd_sinh);
DEFINE_PUBLIC_ALIAS(DOS$__tanh, libd_tanh);
DEFINE_PUBLIC_ALIAS(DOS$tanh, libd_tanh);
DEFINE_PUBLIC_ALIAS(DOS$__coshf, libd_coshf);
DEFINE_PUBLIC_ALIAS(DOS$coshf, libd_coshf);
DEFINE_PUBLIC_ALIAS(DOS$__sinhf, libd_sinhf);
DEFINE_PUBLIC_ALIAS(DOS$sinhf, libd_sinhf);
DEFINE_PUBLIC_ALIAS(DOS$__tanhf, libd_tanhf);
DEFINE_PUBLIC_ALIAS(DOS$tanhf, libd_tanhf);
DEFINE_PUBLIC_ALIAS(DOS$__coshl, libd_coshl);
DEFINE_PUBLIC_ALIAS(DOS$coshl, libd_coshl);
DEFINE_PUBLIC_ALIAS(DOS$__sinhl, libd_sinhl);
DEFINE_PUBLIC_ALIAS(DOS$sinhl, libd_sinhl);
DEFINE_PUBLIC_ALIAS(DOS$__tanhl, libd_tanhl);
DEFINE_PUBLIC_ALIAS(DOS$tanhl, libd_tanhl);
DEFINE_PUBLIC_ALIAS(DOS$__acosh, libd_acosh);
DEFINE_PUBLIC_ALIAS(DOS$acosh, libd_acosh);
DEFINE_PUBLIC_ALIAS(DOS$__asinh, libd_asinh);
DEFINE_PUBLIC_ALIAS(DOS$asinh, libd_asinh);
DEFINE_PUBLIC_ALIAS(DOS$__atanh, libd_atanh);
DEFINE_PUBLIC_ALIAS(DOS$atanh, libd_atanh);
DEFINE_PUBLIC_ALIAS(DOS$__acoshf, libd_acoshf);
DEFINE_PUBLIC_ALIAS(DOS$acoshf, libd_acoshf);
DEFINE_PUBLIC_ALIAS(DOS$__asinhf, libd_asinhf);
DEFINE_PUBLIC_ALIAS(DOS$asinhf, libd_asinhf);
DEFINE_PUBLIC_ALIAS(DOS$__atanhf, libd_atanhf);
DEFINE_PUBLIC_ALIAS(DOS$atanhf, libd_atanhf);
DEFINE_PUBLIC_ALIAS(DOS$__acoshl, libd_acoshl);
DEFINE_PUBLIC_ALIAS(DOS$acoshl, libd_acoshl);
DEFINE_PUBLIC_ALIAS(DOS$__asinhl, libd_asinhl);
DEFINE_PUBLIC_ALIAS(DOS$asinhl, libd_asinhl);
DEFINE_PUBLIC_ALIAS(DOS$__atanhl, libd_atanhl);
DEFINE_PUBLIC_ALIAS(DOS$atanhl, libd_atanhl);
DEFINE_PUBLIC_ALIAS(DOS$__exp, libd_exp);
DEFINE_PUBLIC_ALIAS(DOS$exp, libd_exp);
DEFINE_PUBLIC_ALIAS(DOS$__frexp, libd_frexp);
DEFINE_PUBLIC_ALIAS(DOS$frexp, libd_frexp);
DEFINE_PUBLIC_ALIAS(DOS$__ldexp, libd_ldexp);
DEFINE_PUBLIC_ALIAS(DOS$ldexp, libd_ldexp);
DEFINE_PUBLIC_ALIAS(DOS$__log, libd_log);
DEFINE_PUBLIC_ALIAS(DOS$log, libd_log);
DEFINE_PUBLIC_ALIAS(DOS$__log10, libd_log10);
DEFINE_PUBLIC_ALIAS(DOS$log10, libd_log10);
DEFINE_PUBLIC_ALIAS(DOS$__modf, libd_modf);
DEFINE_PUBLIC_ALIAS(DOS$modf, libd_modf);
DEFINE_PUBLIC_ALIAS(DOS$__expf, libd_expf);
DEFINE_PUBLIC_ALIAS(DOS$expf, libd_expf);
DEFINE_PUBLIC_ALIAS(DOS$__frexpf, libd_frexpf);
DEFINE_PUBLIC_ALIAS(DOS$frexpf, libd_frexpf);
DEFINE_PUBLIC_ALIAS(DOS$__ldexpf, libd_ldexpf);
DEFINE_PUBLIC_ALIAS(DOS$ldexpf, libd_ldexpf);
DEFINE_PUBLIC_ALIAS(DOS$__logf, libd_logf);
DEFINE_PUBLIC_ALIAS(DOS$logf, libd_logf);
DEFINE_PUBLIC_ALIAS(DOS$__log10f, libd_log10f);
DEFINE_PUBLIC_ALIAS(DOS$log10f, libd_log10f);
DEFINE_PUBLIC_ALIAS(DOS$__modff, libd_modff);
DEFINE_PUBLIC_ALIAS(DOS$modff, libd_modff);
DEFINE_PUBLIC_ALIAS(DOS$__expl, libd_expl);
DEFINE_PUBLIC_ALIAS(DOS$expl, libd_expl);
DEFINE_PUBLIC_ALIAS(DOS$__frexpl, libd_frexpl);
DEFINE_PUBLIC_ALIAS(DOS$frexpl, libd_frexpl);
DEFINE_PUBLIC_ALIAS(DOS$__ldexpl, libd_ldexpl);
DEFINE_PUBLIC_ALIAS(DOS$ldexpl, libd_ldexpl);
DEFINE_PUBLIC_ALIAS(DOS$__logl, libd_logl);
DEFINE_PUBLIC_ALIAS(DOS$logl, libd_logl);
DEFINE_PUBLIC_ALIAS(DOS$__log10l, libd_log10l);
DEFINE_PUBLIC_ALIAS(DOS$log10l, libd_log10l);
DEFINE_PUBLIC_ALIAS(DOS$__modfl, libd_modfl);
DEFINE_PUBLIC_ALIAS(DOS$modfl, libd_modfl);
DEFINE_PUBLIC_ALIAS(DOS$__expm1, libd_expm1);
DEFINE_PUBLIC_ALIAS(DOS$expm1, libd_expm1);
DEFINE_PUBLIC_ALIAS(DOS$__log1p, libd_log1p);
DEFINE_PUBLIC_ALIAS(DOS$log1p, libd_log1p);
DEFINE_PUBLIC_ALIAS(DOS$__logb, libd_logb);
DEFINE_PUBLIC_ALIAS(DOS$_logb, libd_logb);
DEFINE_PUBLIC_ALIAS(DOS$logb, libd_logb);
DEFINE_PUBLIC_ALIAS(DOS$__expm1f, libd_expm1f);
DEFINE_PUBLIC_ALIAS(DOS$expm1f, libd_expm1f);
DEFINE_PUBLIC_ALIAS(DOS$__log1pf, libd_log1pf);
DEFINE_PUBLIC_ALIAS(DOS$log1pf, libd_log1pf);
DEFINE_PUBLIC_ALIAS(DOS$__logbf, libd_logbf);
#ifdef __x86_64__
DEFINE_PUBLIC_ALIAS(DOS$_logbf, libd_logbf);
#endif /* __x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$logbf, libd_logbf);
DEFINE_PUBLIC_ALIAS(DOS$__expm1l, libd_expm1l);
DEFINE_PUBLIC_ALIAS(DOS$expm1l, libd_expm1l);
DEFINE_PUBLIC_ALIAS(DOS$__log1pl, libd_log1pl);
DEFINE_PUBLIC_ALIAS(DOS$log1pl, libd_log1pl);
DEFINE_PUBLIC_ALIAS(DOS$__logbl, libd_logbl);
DEFINE_PUBLIC_ALIAS(DOS$logbl, libd_logbl);
DEFINE_PUBLIC_ALIAS(DOS$__exp2, libd_exp2);
DEFINE_PUBLIC_ALIAS(DOS$exp2, libd_exp2);
DEFINE_PUBLIC_ALIAS(DOS$__log2, libd_log2);
DEFINE_PUBLIC_ALIAS(DOS$log2, libd_log2);
DEFINE_PUBLIC_ALIAS(DOS$__exp2f, libd_exp2f);
DEFINE_PUBLIC_ALIAS(DOS$exp2f, libd_exp2f);
DEFINE_PUBLIC_ALIAS(DOS$__log2f, libd_log2f);
DEFINE_PUBLIC_ALIAS(DOS$log2f, libd_log2f);
DEFINE_PUBLIC_ALIAS(DOS$__exp2l, libd_exp2l);
DEFINE_PUBLIC_ALIAS(DOS$exp2l, libd_exp2l);
DEFINE_PUBLIC_ALIAS(DOS$__log2l, libd_log2l);
DEFINE_PUBLIC_ALIAS(DOS$log2l, libd_log2l);
DEFINE_PUBLIC_ALIAS(DOS$__pow, libd_pow);
DEFINE_PUBLIC_ALIAS(DOS$pow, libd_pow);
DEFINE_PUBLIC_ALIAS(DOS$__sqrt, libd_sqrt);
DEFINE_PUBLIC_ALIAS(DOS$sqrt, libd_sqrt);
DEFINE_PUBLIC_ALIAS(DOS$__powf, libd_powf);
DEFINE_PUBLIC_ALIAS(DOS$powf, libd_powf);
DEFINE_PUBLIC_ALIAS(DOS$__sqrtf, libd_sqrtf);
DEFINE_PUBLIC_ALIAS(DOS$sqrtf, libd_sqrtf);
DEFINE_PUBLIC_ALIAS(DOS$__powl, libd_powl);
DEFINE_PUBLIC_ALIAS(DOS$powl, libd_powl);
DEFINE_PUBLIC_ALIAS(DOS$__sqrtl, libd_sqrtl);
DEFINE_PUBLIC_ALIAS(DOS$sqrtl, libd_sqrtl);
DEFINE_PUBLIC_ALIAS(DOS$_hypot, libd_hypot);
DEFINE_PUBLIC_ALIAS(DOS$__hypot, libd_hypot);
DEFINE_PUBLIC_ALIAS(DOS$hypot, libd_hypot);
DEFINE_PUBLIC_ALIAS(DOS$_hypotf, libd_hypotf);
DEFINE_PUBLIC_ALIAS(DOS$__hypotf, libd_hypotf);
DEFINE_PUBLIC_ALIAS(DOS$hypotf, libd_hypotf);
DEFINE_PUBLIC_ALIAS(DOS$__hypotl, libd_hypotl);
DEFINE_PUBLIC_ALIAS(DOS$hypotl, libd_hypotl);
DEFINE_PUBLIC_ALIAS(DOS$__cbrt, libd_cbrt);
DEFINE_PUBLIC_ALIAS(DOS$cbrt, libd_cbrt);
DEFINE_PUBLIC_ALIAS(DOS$__cbrtf, libd_cbrtf);
DEFINE_PUBLIC_ALIAS(DOS$cbrtf, libd_cbrtf);
DEFINE_PUBLIC_ALIAS(DOS$__cbrtl, libd_cbrtl);
DEFINE_PUBLIC_ALIAS(DOS$cbrtl, libd_cbrtl);
DEFINE_PUBLIC_ALIAS(DOS$__ceil, libd_ceil);
DEFINE_PUBLIC_ALIAS(DOS$ceil, libd_ceil);
DEFINE_PUBLIC_ALIAS(DOS$__fabs, libd_fabs);
DEFINE_PUBLIC_ALIAS(DOS$fabs, libd_fabs);
DEFINE_PUBLIC_ALIAS(DOS$__floor, libd_floor);
DEFINE_PUBLIC_ALIAS(DOS$floor, libd_floor);
DEFINE_PUBLIC_ALIAS(DOS$__fmod, libd_fmod);
DEFINE_PUBLIC_ALIAS(DOS$fmod, libd_fmod);
DEFINE_PUBLIC_ALIAS(DOS$__ceilf, libd_ceilf);
DEFINE_PUBLIC_ALIAS(DOS$ceilf, libd_ceilf);
DEFINE_PUBLIC_ALIAS(DOS$__fabsf, libd_fabsf);
DEFINE_PUBLIC_ALIAS(DOS$fabsf, libd_fabsf);
DEFINE_PUBLIC_ALIAS(DOS$__floorf, libd_floorf);
DEFINE_PUBLIC_ALIAS(DOS$floorf, libd_floorf);
DEFINE_PUBLIC_ALIAS(DOS$__fmodf, libd_fmodf);
DEFINE_PUBLIC_ALIAS(DOS$fmodf, libd_fmodf);
DEFINE_PUBLIC_ALIAS(DOS$__ceill, libd_ceill);
DEFINE_PUBLIC_ALIAS(DOS$ceill, libd_ceill);
DEFINE_PUBLIC_ALIAS(DOS$__fabsl, libd_fabsl);
DEFINE_PUBLIC_ALIAS(DOS$fabsl, libd_fabsl);
DEFINE_PUBLIC_ALIAS(DOS$__floorl, libd_floorl);
DEFINE_PUBLIC_ALIAS(DOS$floorl, libd_floorl);
DEFINE_PUBLIC_ALIAS(DOS$__fmodl, libd_fmodl);
DEFINE_PUBLIC_ALIAS(DOS$fmodl, libd_fmodl);
DEFINE_PUBLIC_ALIAS(DOS$__copysign, libd_copysign);
DEFINE_PUBLIC_ALIAS(DOS$_copysign, libd_copysign);
DEFINE_PUBLIC_ALIAS(DOS$copysign, libd_copysign);
DEFINE_PUBLIC_ALIAS(DOS$__nan, libd_nan);
DEFINE_PUBLIC_ALIAS(DOS$nan, libd_nan);
DEFINE_PUBLIC_ALIAS(DOS$_copysignf, libd_copysignf);
DEFINE_PUBLIC_ALIAS(DOS$__copysignf, libd_copysignf);
DEFINE_PUBLIC_ALIAS(DOS$copysignf, libd_copysignf);
DEFINE_PUBLIC_ALIAS(DOS$__nanf, libd_nanf);
DEFINE_PUBLIC_ALIAS(DOS$nanf, libd_nanf);
DEFINE_PUBLIC_ALIAS(DOS$__copysignl, libd_copysignl);
DEFINE_PUBLIC_ALIAS(DOS$copysignl, libd_copysignl);
DEFINE_PUBLIC_ALIAS(DOS$__nanl, libd_nanl);
DEFINE_PUBLIC_ALIAS(DOS$nanl, libd_nanl);
DEFINE_PUBLIC_ALIAS(DOS$__erf, libd_erf);
DEFINE_PUBLIC_ALIAS(DOS$erf, libd_erf);
DEFINE_PUBLIC_ALIAS(DOS$__erfc, libd_erfc);
DEFINE_PUBLIC_ALIAS(DOS$erfc, libd_erfc);
DEFINE_PUBLIC_ALIAS(DOS$gamma, libd_lgamma);
DEFINE_PUBLIC_ALIAS(DOS$__lgamma, libd_lgamma);
DEFINE_PUBLIC_ALIAS(DOS$__gamma, libd_lgamma);
DEFINE_PUBLIC_ALIAS(DOS$lgamma, libd_lgamma);
DEFINE_PUBLIC_ALIAS(DOS$__erff, libd_erff);
DEFINE_PUBLIC_ALIAS(DOS$erff, libd_erff);
DEFINE_PUBLIC_ALIAS(DOS$__erfcf, libd_erfcf);
DEFINE_PUBLIC_ALIAS(DOS$erfcf, libd_erfcf);
DEFINE_PUBLIC_ALIAS(DOS$gammaf, libd_lgammaf);
DEFINE_PUBLIC_ALIAS(DOS$__lgammaf, libd_lgammaf);
DEFINE_PUBLIC_ALIAS(DOS$__gammaf, libd_lgammaf);
DEFINE_PUBLIC_ALIAS(DOS$lgammaf, libd_lgammaf);
DEFINE_PUBLIC_ALIAS(DOS$__erfl, libd_erfl);
DEFINE_PUBLIC_ALIAS(DOS$erfl, libd_erfl);
DEFINE_PUBLIC_ALIAS(DOS$__erfcl, libd_erfcl);
DEFINE_PUBLIC_ALIAS(DOS$erfcl, libd_erfcl);
DEFINE_PUBLIC_ALIAS(DOS$gammal, libd_lgammal);
DEFINE_PUBLIC_ALIAS(DOS$__lgammal, libd_lgammal);
DEFINE_PUBLIC_ALIAS(DOS$__gammal, libd_lgammal);
DEFINE_PUBLIC_ALIAS(DOS$lgammal, libd_lgammal);
DEFINE_PUBLIC_ALIAS(DOS$__tgamma, libd_tgamma);
DEFINE_PUBLIC_ALIAS(DOS$tgamma, libd_tgamma);
DEFINE_PUBLIC_ALIAS(DOS$__tgammaf, libd_tgammaf);
DEFINE_PUBLIC_ALIAS(DOS$tgammaf, libd_tgammaf);
DEFINE_PUBLIC_ALIAS(DOS$__tgammal, libd_tgammal);
DEFINE_PUBLIC_ALIAS(DOS$tgammal, libd_tgammal);
DEFINE_PUBLIC_ALIAS(DOS$nearbyint, libd_rint);
DEFINE_PUBLIC_ALIAS(DOS$__rint, libd_rint);
DEFINE_PUBLIC_ALIAS(DOS$__nearbyint, libd_rint);
DEFINE_PUBLIC_ALIAS(DOS$rint, libd_rint);
DEFINE_PUBLIC_ALIAS(DOS$nexttoward, libd_nextafter);
DEFINE_PUBLIC_ALIAS(DOS$__nextafter, libd_nextafter);
DEFINE_PUBLIC_ALIAS(DOS$_nextafter, libd_nextafter);
DEFINE_PUBLIC_ALIAS(DOS$__nexttoward, libd_nextafter);
DEFINE_PUBLIC_ALIAS(DOS$nextafter, libd_nextafter);
DEFINE_PUBLIC_ALIAS(DOS$drem, libd_remainder);
DEFINE_PUBLIC_ALIAS(DOS$__remainder, libd_remainder);
DEFINE_PUBLIC_ALIAS(DOS$__drem, libd_remainder);
DEFINE_PUBLIC_ALIAS(DOS$remainder, libd_remainder);
DEFINE_PUBLIC_ALIAS(DOS$__ilogb, libd_ilogb);
DEFINE_PUBLIC_ALIAS(DOS$ilogb, libd_ilogb);
DEFINE_PUBLIC_ALIAS(DOS$nearbyintf, libd_rintf);
DEFINE_PUBLIC_ALIAS(DOS$__rintf, libd_rintf);
DEFINE_PUBLIC_ALIAS(DOS$__nearbyintf, libd_rintf);
DEFINE_PUBLIC_ALIAS(DOS$rintf, libd_rintf);
DEFINE_PUBLIC_ALIAS(DOS$nexttowardf, libd_nextafterf);
DEFINE_PUBLIC_ALIAS(DOS$__nextafterf, libd_nextafterf);
DEFINE_PUBLIC_ALIAS(DOS$__nexttowardf, libd_nextafterf);
#ifdef __x86_64__
DEFINE_PUBLIC_ALIAS(DOS$_nextafterf, libd_nextafterf);
#endif /* __x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$nextafterf, libd_nextafterf);
DEFINE_PUBLIC_ALIAS(DOS$dremf, libd_remainderf);
DEFINE_PUBLIC_ALIAS(DOS$__remainderf, libd_remainderf);
DEFINE_PUBLIC_ALIAS(DOS$__dremf, libd_remainderf);
DEFINE_PUBLIC_ALIAS(DOS$remainderf, libd_remainderf);
DEFINE_PUBLIC_ALIAS(DOS$__ilogbf, libd_ilogbf);
DEFINE_PUBLIC_ALIAS(DOS$ilogbf, libd_ilogbf);
DEFINE_PUBLIC_ALIAS(DOS$nearbyintl, libd_rintl);
DEFINE_PUBLIC_ALIAS(DOS$__rintl, libd_rintl);
DEFINE_PUBLIC_ALIAS(DOS$__nearbyintl, libd_rintl);
DEFINE_PUBLIC_ALIAS(DOS$rintl, libd_rintl);
DEFINE_PUBLIC_ALIAS(DOS$nexttowardl, libd_nextafterl);
DEFINE_PUBLIC_ALIAS(DOS$__nextafterl, libd_nextafterl);
DEFINE_PUBLIC_ALIAS(DOS$__nexttowardl, libd_nextafterl);
DEFINE_PUBLIC_ALIAS(DOS$nextafterl, libd_nextafterl);
DEFINE_PUBLIC_ALIAS(DOS$dreml, libd_remainderl);
DEFINE_PUBLIC_ALIAS(DOS$__remainderl, libd_remainderl);
DEFINE_PUBLIC_ALIAS(DOS$__dreml, libd_remainderl);
DEFINE_PUBLIC_ALIAS(DOS$remainderl, libd_remainderl);
DEFINE_PUBLIC_ALIAS(DOS$__ilogbl, libd_ilogbl);
DEFINE_PUBLIC_ALIAS(DOS$ilogbl, libd_ilogbl);
DEFINE_PUBLIC_ALIAS(DOS$__nexttoward, libd_nexttoward);
DEFINE_PUBLIC_ALIAS(DOS$nexttoward, libd_nexttoward);
DEFINE_PUBLIC_ALIAS(DOS$__scalbn, libd_scalbn);
DEFINE_PUBLIC_ALIAS(DOS$scalbn, libd_scalbn);
DEFINE_PUBLIC_ALIAS(DOS$__scalbln, libd_scalbln);
DEFINE_PUBLIC_ALIAS(DOS$scalbln, libd_scalbln);
DEFINE_PUBLIC_ALIAS(DOS$__round, libd_round);
DEFINE_PUBLIC_ALIAS(DOS$round, libd_round);
DEFINE_PUBLIC_ALIAS(DOS$__trunc, libd_trunc);
DEFINE_PUBLIC_ALIAS(DOS$trunc, libd_trunc);
DEFINE_PUBLIC_ALIAS(DOS$__remquo, libd_remquo);
DEFINE_PUBLIC_ALIAS(DOS$remquo, libd_remquo);
DEFINE_PUBLIC_ALIAS(DOS$__lrint, libd_lrint);
DEFINE_PUBLIC_ALIAS(DOS$lrint, libd_lrint);
DEFINE_PUBLIC_ALIAS(DOS$__lround, libd_lround);
DEFINE_PUBLIC_ALIAS(DOS$lround, libd_lround);
DEFINE_PUBLIC_ALIAS(DOS$__fdim, libd_fdim);
DEFINE_PUBLIC_ALIAS(DOS$fdim, libd_fdim);
DEFINE_PUBLIC_ALIAS(DOS$__fmax, libd_fmax);
DEFINE_PUBLIC_ALIAS(DOS$fmax, libd_fmax);
DEFINE_PUBLIC_ALIAS(DOS$__fmin, libd_fmin);
DEFINE_PUBLIC_ALIAS(DOS$fmin, libd_fmin);
DEFINE_PUBLIC_ALIAS(DOS$__fma, libd_fma);
DEFINE_PUBLIC_ALIAS(DOS$fma, libd_fma);
DEFINE_PUBLIC_ALIAS(DOS$__llrint, libd_llrint);
DEFINE_PUBLIC_ALIAS(DOS$llrint, libd_llrint);
DEFINE_PUBLIC_ALIAS(DOS$__llround, libd_llround);
DEFINE_PUBLIC_ALIAS(DOS$llround, libd_llround);
DEFINE_PUBLIC_ALIAS(DOS$__nexttowardf, libd_nexttowardf);
DEFINE_PUBLIC_ALIAS(DOS$nexttowardf, libd_nexttowardf);
DEFINE_PUBLIC_ALIAS(DOS$__scalbnf, libd_scalbnf);
DEFINE_PUBLIC_ALIAS(DOS$scalbnf, libd_scalbnf);
DEFINE_PUBLIC_ALIAS(DOS$__scalblnf, libd_scalblnf);
DEFINE_PUBLIC_ALIAS(DOS$scalblnf, libd_scalblnf);
DEFINE_PUBLIC_ALIAS(DOS$__roundf, libd_roundf);
DEFINE_PUBLIC_ALIAS(DOS$roundf, libd_roundf);
DEFINE_PUBLIC_ALIAS(DOS$__truncf, libd_truncf);
DEFINE_PUBLIC_ALIAS(DOS$truncf, libd_truncf);
DEFINE_PUBLIC_ALIAS(DOS$__remquof, libd_remquof);
DEFINE_PUBLIC_ALIAS(DOS$remquof, libd_remquof);
DEFINE_PUBLIC_ALIAS(DOS$__lrintf, libd_lrintf);
DEFINE_PUBLIC_ALIAS(DOS$lrintf, libd_lrintf);
DEFINE_PUBLIC_ALIAS(DOS$__lroundf, libd_lroundf);
DEFINE_PUBLIC_ALIAS(DOS$lroundf, libd_lroundf);
DEFINE_PUBLIC_ALIAS(DOS$__fdimf, libd_fdimf);
DEFINE_PUBLIC_ALIAS(DOS$fdimf, libd_fdimf);
DEFINE_PUBLIC_ALIAS(DOS$__fmaxf, libd_fmaxf);
DEFINE_PUBLIC_ALIAS(DOS$fmaxf, libd_fmaxf);
DEFINE_PUBLIC_ALIAS(DOS$__fminf, libd_fminf);
DEFINE_PUBLIC_ALIAS(DOS$fminf, libd_fminf);
DEFINE_PUBLIC_ALIAS(DOS$__fmaf, libd_fmaf);
DEFINE_PUBLIC_ALIAS(DOS$fmaf, libd_fmaf);
DEFINE_PUBLIC_ALIAS(DOS$__llrintf, libd_llrintf);
DEFINE_PUBLIC_ALIAS(DOS$llrintf, libd_llrintf);
DEFINE_PUBLIC_ALIAS(DOS$__llroundf, libd_llroundf);
DEFINE_PUBLIC_ALIAS(DOS$llroundf, libd_llroundf);
DEFINE_PUBLIC_ALIAS(DOS$__scalbnl, libd_scalbnl);
DEFINE_PUBLIC_ALIAS(DOS$scalbnl, libd_scalbnl);
DEFINE_PUBLIC_ALIAS(DOS$__scalblnl, libd_scalblnl);
DEFINE_PUBLIC_ALIAS(DOS$scalblnl, libd_scalblnl);
DEFINE_PUBLIC_ALIAS(DOS$__roundl, libd_roundl);
DEFINE_PUBLIC_ALIAS(DOS$roundl, libd_roundl);
DEFINE_PUBLIC_ALIAS(DOS$__truncl, libd_truncl);
DEFINE_PUBLIC_ALIAS(DOS$truncl, libd_truncl);
DEFINE_PUBLIC_ALIAS(DOS$__remquol, libd_remquol);
DEFINE_PUBLIC_ALIAS(DOS$remquol, libd_remquol);
DEFINE_PUBLIC_ALIAS(DOS$__lrintl, libd_lrintl);
DEFINE_PUBLIC_ALIAS(DOS$lrintl, libd_lrintl);
DEFINE_PUBLIC_ALIAS(DOS$__lroundl, libd_lroundl);
DEFINE_PUBLIC_ALIAS(DOS$lroundl, libd_lroundl);
DEFINE_PUBLIC_ALIAS(DOS$__fdiml, libd_fdiml);
DEFINE_PUBLIC_ALIAS(DOS$fdiml, libd_fdiml);
DEFINE_PUBLIC_ALIAS(DOS$__fmaxl, libd_fmaxl);
DEFINE_PUBLIC_ALIAS(DOS$fmaxl, libd_fmaxl);
DEFINE_PUBLIC_ALIAS(DOS$__fminl, libd_fminl);
DEFINE_PUBLIC_ALIAS(DOS$fminl, libd_fminl);
DEFINE_PUBLIC_ALIAS(DOS$__fmal, libd_fmal);
DEFINE_PUBLIC_ALIAS(DOS$fmal, libd_fmal);
DEFINE_PUBLIC_ALIAS(DOS$__llrintl, libd_llrintl);
DEFINE_PUBLIC_ALIAS(DOS$llrintl, libd_llrintl);
DEFINE_PUBLIC_ALIAS(DOS$__llroundl, libd_llroundl);
DEFINE_PUBLIC_ALIAS(DOS$llroundl, libd_llroundl);
DEFINE_PUBLIC_ALIAS(DOS$__sincos, libd_sincos);
DEFINE_PUBLIC_ALIAS(DOS$sincos, libd_sincos);
DEFINE_PUBLIC_ALIAS(DOS$__exp10, libd_exp10);
DEFINE_PUBLIC_ALIAS(DOS$exp10, libd_exp10);
DEFINE_PUBLIC_ALIAS(DOS$__pow10, libd_pow10);
DEFINE_PUBLIC_ALIAS(DOS$pow10, libd_pow10);
DEFINE_PUBLIC_ALIAS(DOS$__sincosf, libd_sincosf);
DEFINE_PUBLIC_ALIAS(DOS$sincosf, libd_sincosf);
DEFINE_PUBLIC_ALIAS(DOS$__exp10f, libd_exp10f);
DEFINE_PUBLIC_ALIAS(DOS$exp10f, libd_exp10f);
DEFINE_PUBLIC_ALIAS(DOS$__pow10f, libd_pow10f);
DEFINE_PUBLIC_ALIAS(DOS$pow10f, libd_pow10f);
DEFINE_PUBLIC_ALIAS(DOS$__sincosl, libd_sincosl);
DEFINE_PUBLIC_ALIAS(DOS$sincosl, libd_sincosl);
DEFINE_PUBLIC_ALIAS(DOS$__exp10l, libd_exp10l);
DEFINE_PUBLIC_ALIAS(DOS$exp10l, libd_exp10l);
DEFINE_PUBLIC_ALIAS(DOS$__pow10l, libd_pow10l);
DEFINE_PUBLIC_ALIAS(DOS$pow10l, libd_pow10l);
DEFINE_PUBLIC_ALIAS(DOS$__isinf, libd_isinf);
DEFINE_PUBLIC_ALIAS(DOS$isinf, libd_isinf);
DEFINE_PUBLIC_ALIAS(DOS$__isinff, libd_isinff);
DEFINE_PUBLIC_ALIAS(DOS$isinff, libd_isinff);
DEFINE_PUBLIC_ALIAS(DOS$__isinfl, libd_isinfl);
DEFINE_PUBLIC_ALIAS(DOS$isinfl, libd_isinfl);
DEFINE_PUBLIC_ALIAS(DOS$__finite, libd_finite);
DEFINE_PUBLIC_ALIAS(DOS$_finite, libd_finite);
DEFINE_PUBLIC_ALIAS(DOS$finite, libd_finite);
DEFINE_PUBLIC_ALIAS(DOS$__significand, libd_significand);
DEFINE_PUBLIC_ALIAS(DOS$significand, libd_significand);
DEFINE_PUBLIC_ALIAS(DOS$__finitef, libd_finitef);
#ifdef __x86_64__
DEFINE_PUBLIC_ALIAS(DOS$_finitef, libd_finitef);
#endif /* __x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$finitef, libd_finitef);
DEFINE_PUBLIC_ALIAS(DOS$__significandf, libd_significandf);
DEFINE_PUBLIC_ALIAS(DOS$significandf, libd_significandf);
DEFINE_PUBLIC_ALIAS(DOS$__finitel, libd_finitel);
DEFINE_PUBLIC_ALIAS(DOS$finitel, libd_finitel);
DEFINE_PUBLIC_ALIAS(DOS$__significandl, libd_significandl);
DEFINE_PUBLIC_ALIAS(DOS$significandl, libd_significandl);
DEFINE_PUBLIC_ALIAS(DOS$_isnan, libd_isnan);
DEFINE_PUBLIC_ALIAS(DOS$__isnan, libd_isnan);
DEFINE_PUBLIC_ALIAS(DOS$isnan, libd_isnan);
DEFINE_PUBLIC_ALIAS(DOS$__isnanf, libd_isnanf);
#ifdef __x86_64__
DEFINE_PUBLIC_ALIAS(DOS$_isnanf, libd_isnanf);
#endif /* __x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$isnanf, libd_isnanf);
DEFINE_PUBLIC_ALIAS(DOS$__isnanl, libd_isnanl);
DEFINE_PUBLIC_ALIAS(DOS$isnanl, libd_isnanl);
DEFINE_PUBLIC_ALIAS(DOS$_j0, libd_j0);
DEFINE_PUBLIC_ALIAS(DOS$__j0, libd_j0);
DEFINE_PUBLIC_ALIAS(DOS$j0, libd_j0);
DEFINE_PUBLIC_ALIAS(DOS$_j1, libd_j1);
DEFINE_PUBLIC_ALIAS(DOS$__j1, libd_j1);
DEFINE_PUBLIC_ALIAS(DOS$j1, libd_j1);
DEFINE_PUBLIC_ALIAS(DOS$_jn, libd_jn);
DEFINE_PUBLIC_ALIAS(DOS$__jn, libd_jn);
DEFINE_PUBLIC_ALIAS(DOS$jn, libd_jn);
DEFINE_PUBLIC_ALIAS(DOS$_y0, libd_y0);
DEFINE_PUBLIC_ALIAS(DOS$__y0, libd_y0);
DEFINE_PUBLIC_ALIAS(DOS$y0, libd_y0);
DEFINE_PUBLIC_ALIAS(DOS$_y1, libd_y1);
DEFINE_PUBLIC_ALIAS(DOS$__y1, libd_y1);
DEFINE_PUBLIC_ALIAS(DOS$y1, libd_y1);
DEFINE_PUBLIC_ALIAS(DOS$_yn, libd_yn);
DEFINE_PUBLIC_ALIAS(DOS$__yn, libd_yn);
DEFINE_PUBLIC_ALIAS(DOS$yn, libd_yn);
DEFINE_PUBLIC_ALIAS(DOS$__j0f, libd_j0f);
DEFINE_PUBLIC_ALIAS(DOS$j0f, libd_j0f);
DEFINE_PUBLIC_ALIAS(DOS$__j1f, libd_j1f);
DEFINE_PUBLIC_ALIAS(DOS$j1f, libd_j1f);
DEFINE_PUBLIC_ALIAS(DOS$__jnf, libd_jnf);
DEFINE_PUBLIC_ALIAS(DOS$jnf, libd_jnf);
DEFINE_PUBLIC_ALIAS(DOS$__y0f, libd_y0f);
DEFINE_PUBLIC_ALIAS(DOS$y0f, libd_y0f);
DEFINE_PUBLIC_ALIAS(DOS$__y1f, libd_y1f);
DEFINE_PUBLIC_ALIAS(DOS$y1f, libd_y1f);
DEFINE_PUBLIC_ALIAS(DOS$__ynf, libd_ynf);
DEFINE_PUBLIC_ALIAS(DOS$ynf, libd_ynf);
DEFINE_PUBLIC_ALIAS(DOS$__j0l, libd_j0l);
DEFINE_PUBLIC_ALIAS(DOS$j0l, libd_j0l);
DEFINE_PUBLIC_ALIAS(DOS$__j1l, libd_j1l);
DEFINE_PUBLIC_ALIAS(DOS$j1l, libd_j1l);
DEFINE_PUBLIC_ALIAS(DOS$__jnl, libd_jnl);
DEFINE_PUBLIC_ALIAS(DOS$jnl, libd_jnl);
DEFINE_PUBLIC_ALIAS(DOS$__y0l, libd_y0l);
DEFINE_PUBLIC_ALIAS(DOS$y0l, libd_y0l);
DEFINE_PUBLIC_ALIAS(DOS$__y1l, libd_y1l);
DEFINE_PUBLIC_ALIAS(DOS$y1l, libd_y1l);
DEFINE_PUBLIC_ALIAS(DOS$__ynl, libd_ynl);
DEFINE_PUBLIC_ALIAS(DOS$ynl, libd_ynl);
DEFINE_PUBLIC_ALIAS(DOS$__lgamma_r, libd_lgamma_r);
DEFINE_PUBLIC_ALIAS(DOS$lgamma_r, libd_lgamma_r);
DEFINE_PUBLIC_ALIAS(DOS$__lgammaf_r, libd_lgammaf_r);
DEFINE_PUBLIC_ALIAS(DOS$lgammaf_r, libd_lgammaf_r);
DEFINE_PUBLIC_ALIAS(DOS$__lgammal_r, libd_lgammal_r);
DEFINE_PUBLIC_ALIAS(DOS$lgammal_r, libd_lgammal_r);
DEFINE_PUBLIC_ALIAS(DOS$_scalb, libd_scalb);
DEFINE_PUBLIC_ALIAS(DOS$__scalb, libd_scalb);
DEFINE_PUBLIC_ALIAS(DOS$scalb, libd_scalb);
DEFINE_PUBLIC_ALIAS(DOS$_scalbf, libd_scalbf);
DEFINE_PUBLIC_ALIAS(DOS$__scalbf, libd_scalbf);
DEFINE_PUBLIC_ALIAS(DOS$scalbf, libd_scalbf);
DEFINE_PUBLIC_ALIAS(DOS$__scalbl, libd_scalbl);
DEFINE_PUBLIC_ALIAS(DOS$scalbl, libd_scalbl);
DEFINE_PUBLIC_ALIAS(DOS$_dsign, libd___signbit);
DEFINE_PUBLIC_ALIAS(DOS$__signbit, libd___signbit);
DEFINE_PUBLIC_ALIAS(DOS$_fdsign, libd___signbitf);
DEFINE_PUBLIC_ALIAS(DOS$__signbitf, libd___signbitf);
DEFINE_PUBLIC_ALIAS(DOS$_ldsign, libd___signbitl);
DEFINE_PUBLIC_ALIAS(DOS$__signbitl, libd___signbitl);
DEFINE_PUBLIC_ALIAS(DOS$issignaling, libd___issignaling);
DEFINE_PUBLIC_ALIAS(DOS$__issignaling, libd___issignaling);
DEFINE_PUBLIC_ALIAS(DOS$issignalingf, libd___issignalingf);
DEFINE_PUBLIC_ALIAS(DOS$__issignalingf, libd___issignalingf);
DEFINE_PUBLIC_ALIAS(DOS$__iscanonicall, libd___iscanonicall);
DEFINE_PUBLIC_ALIAS(DOS$issignalingl, libd___issignalingl);
DEFINE_PUBLIC_ALIAS(DOS$__issignalingl, libd___issignalingl);
DEFINE_PUBLIC_ALIAS(DOS$nextdown, libd_nextdown);
DEFINE_PUBLIC_ALIAS(DOS$nextup, libd_nextup);
DEFINE_PUBLIC_ALIAS(DOS$nextdownf, libd_nextdownf);
DEFINE_PUBLIC_ALIAS(DOS$nextupf, libd_nextupf);
DEFINE_PUBLIC_ALIAS(DOS$nextdownl, libd_nextdownl);
DEFINE_PUBLIC_ALIAS(DOS$nextupl, libd_nextupl);
DEFINE_PUBLIC_ALIAS(DOS$llogb, libd_llogb);
DEFINE_PUBLIC_ALIAS(DOS$roundeven, libd_roundeven);
DEFINE_PUBLIC_ALIAS(DOS$fromfp, libd_fromfp);
DEFINE_PUBLIC_ALIAS(DOS$ufromfp, libd_ufromfp);
DEFINE_PUBLIC_ALIAS(DOS$fromfpx, libd_fromfpx);
DEFINE_PUBLIC_ALIAS(DOS$ufromfpx, libd_ufromfpx);
DEFINE_PUBLIC_ALIAS(DOS$fmaxmag, libd_fmaxmag);
DEFINE_PUBLIC_ALIAS(DOS$fminmag, libd_fminmag);
DEFINE_PUBLIC_ALIAS(DOS$canonicalize, libd_canonicalize);
DEFINE_PUBLIC_ALIAS(DOS$llogbf, libd_llogbf);
DEFINE_PUBLIC_ALIAS(DOS$roundevenf, libd_roundevenf);
DEFINE_PUBLIC_ALIAS(DOS$fromfpf, libd_fromfpf);
DEFINE_PUBLIC_ALIAS(DOS$ufromfpf, libd_ufromfpf);
DEFINE_PUBLIC_ALIAS(DOS$fromfpxf, libd_fromfpxf);
DEFINE_PUBLIC_ALIAS(DOS$ufromfpxf, libd_ufromfpxf);
DEFINE_PUBLIC_ALIAS(DOS$fmaxmagf, libd_fmaxmagf);
DEFINE_PUBLIC_ALIAS(DOS$fminmagf, libd_fminmagf);
DEFINE_PUBLIC_ALIAS(DOS$canonicalizef, libd_canonicalizef);
DEFINE_PUBLIC_ALIAS(DOS$llogbl, libd_llogbl);
DEFINE_PUBLIC_ALIAS(DOS$roundevenl, libd_roundevenl);
DEFINE_PUBLIC_ALIAS(DOS$fromfpl, libd_fromfpl);
DEFINE_PUBLIC_ALIAS(DOS$ufromfpl, libd_ufromfpl);
DEFINE_PUBLIC_ALIAS(DOS$fromfpxl, libd_fromfpxl);
DEFINE_PUBLIC_ALIAS(DOS$ufromfpxl, libd_ufromfpxl);
DEFINE_PUBLIC_ALIAS(DOS$fmaxmagl, libd_fmaxmagl);
DEFINE_PUBLIC_ALIAS(DOS$fminmagl, libd_fminmagl);
DEFINE_PUBLIC_ALIAS(DOS$canonicalizel, libd_canonicalizel);
DEFINE_PUBLIC_ALIAS(DOS$_dpcomp, libd__dpcomp);
DEFINE_PUBLIC_ALIAS(DOS$_fdpcomp, libd__fdpcomp);
DEFINE_PUBLIC_ALIAS(DOS$_ldpcomp, libd__ldpcomp);
DEFINE_PUBLIC_ALIAS(DOS$_chgsignf, libd__chgsignf);
DEFINE_PUBLIC_ALIAS(DOS$_chgsign, libd__chgsign);

/* mbctype */
DEFINE_PUBLIC_ALIAS(DOS$_setmbcp, libd__setmbcp);
DEFINE_PUBLIC_ALIAS(DOS$_mbctouni_l, libd__mbctouni_l);
DEFINE_PUBLIC_ALIAS(DOS$_unitombc_l, libd__unitombc_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbkalnum, libd__ismbbkalnum);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbkprint, libd__ismbbkana);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbkana, libd__ismbbkana);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbkpunct, libd__ismbbkpunct);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbalpha, libd__ismbbalpha);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbpunct, libd__ismbbpunct);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbblank, libd__ismbbblank);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbalnum, libd__ismbbalnum);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbprint, libd__ismbbprint);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbgraph, libd__ismbbgraph);
DEFINE_PUBLIC_ALIAS(DOS$_ismbblead, libd__ismbblead);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbtrail, libd__ismbbtrail);
DEFINE_PUBLIC_ALIAS(DOS$_ismbblead_l, libd__ismbblead_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbtrail_l, libd__ismbbtrail_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbkalnum_l, libd__ismbbkalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbkprint_l, libd__ismbbkana_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbkana_l, libd__ismbbkana_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbkpunct_l, libd__ismbbkpunct_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbalpha_l, libd__ismbbalpha_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbpunct_l, libd__ismbbpunct_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbblank_l, libd__ismbbblank_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbalnum_l, libd__ismbbalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbprint_l, libd__ismbbprint_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbbgraph_l, libd__ismbbgraph_l);

/* mbstring */
DEFINE_PUBLIC_ALIAS(DOS$_mbbtombc, libd__mbbtombc);
DEFINE_PUBLIC_ALIAS(DOS$_mbbtype, libd__mbbtype);
DEFINE_PUBLIC_ALIAS(DOS$_mbctombb, libd__mbctombb);
DEFINE_PUBLIC_ALIAS(DOS$_mbsbtype, libd__mbsbtype);
DEFINE_PUBLIC_ALIAS(DOS$_mbscat_s, libd__mbscat_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbschr, libd__mbschr);
DEFINE_PUBLIC_ALIAS(DOS$_mbscmp, libd__mbscmp);
DEFINE_PUBLIC_ALIAS(DOS$_mbscoll, libd__mbscoll);
DEFINE_PUBLIC_ALIAS(DOS$_mbscpy_s, libd__mbscpy_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbscspn, libd__mbscspn);
DEFINE_PUBLIC_ALIAS(DOS$_mbsdec, libd__mbsdec);
DEFINE_PUBLIC_ALIAS(DOS$_mbsicmp, libd__mbsicmp);
DEFINE_PUBLIC_ALIAS(DOS$_mbsicoll, libd__mbsicoll);
DEFINE_PUBLIC_ALIAS(DOS$_mbsinc, libd__mbsinc);
DEFINE_PUBLIC_ALIAS(DOS$_mbslen, libd__mbslen);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnlen, libd__mbsnlen);
DEFINE_PUBLIC_ALIAS(DOS$_mbslwr_s, libd__mbslwr_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbslwr, libd__mbslwr);
DEFINE_PUBLIC_ALIAS(DOS$_mbsupr, libd__mbsupr);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcat_s, libd__mbsnbcat_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcat, libd__mbsnbcat);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcmp, libd__mbsnbcmp);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcoll, libd__mbsnbcoll);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcnt, libd__mbsnbcnt);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcpy_s, libd__mbsnbcpy_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcpy, libd__mbsnbcpy);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbicmp, libd__mbsnbicmp);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbicoll, libd__mbsnbicoll);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbset_s, libd__mbsnbset_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbset, libd__mbsnbset);
DEFINE_PUBLIC_ALIAS(DOS$_mbsncat_s, libd__mbsncat_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbsncat, libd__mbsncat);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnccnt, libd__mbsnccnt);
DEFINE_PUBLIC_ALIAS(DOS$_mbsncmp, libd__mbsncmp);
DEFINE_PUBLIC_ALIAS(DOS$_mbsncoll, libd__mbsncoll);
DEFINE_PUBLIC_ALIAS(DOS$_mbsncpy_s, libd__mbsncpy_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbsncpy, libd__mbsncpy);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnextc, libd__mbsnextc);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnicmp, libd__mbsnicmp);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnicoll, libd__mbsnicoll);
DEFINE_PUBLIC_ALIAS(DOS$_mbsninc, libd__mbsninc);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnset_s, libd__mbsnset_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnset, libd__mbsnset);
DEFINE_PUBLIC_ALIAS(DOS$_mbspbrk, libd__mbspbrk);
DEFINE_PUBLIC_ALIAS(DOS$_mbsrchr, libd__mbsrchr);
DEFINE_PUBLIC_ALIAS(DOS$_mbsrev, libd__mbsrev);
DEFINE_PUBLIC_ALIAS(DOS$_mbsset_s, libd__mbsset_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbsset, libd__mbsset);
DEFINE_PUBLIC_ALIAS(DOS$_mbsspn, libd__mbsspn);
DEFINE_PUBLIC_ALIAS(DOS$_mbsspnp, libd__mbsspnp);
DEFINE_PUBLIC_ALIAS(DOS$_mbsstr, libd__mbsstr);
DEFINE_PUBLIC_ALIAS(DOS$_mbstok, libd__mbstok);
DEFINE_PUBLIC_ALIAS(DOS$_mbstok_s, libd__mbstok_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbsupr_s, libd__mbsupr_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbclen, libd__mbclen);
DEFINE_PUBLIC_ALIAS(DOS$_mbccpy, libd__mbccpy);
DEFINE_PUBLIC_ALIAS(DOS$_mbccpy_s, libd__mbccpy_s);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcalnum, libd__ismbcalnum);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcalpha, libd__ismbcalpha);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcdigit, libd__ismbcdigit);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcgraph, libd__ismbcgraph);
DEFINE_PUBLIC_ALIAS(DOS$_ismbclegal, libd__ismbclegal);
DEFINE_PUBLIC_ALIAS(DOS$_ismbclower, libd__ismbclower);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcprint, libd__ismbcprint);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcpunct, libd__ismbcpunct);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcblank, libd__ismbcblank);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcspace, libd__ismbcspace);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcupper, libd__ismbcupper);
DEFINE_PUBLIC_ALIAS(DOS$_mbctolower, libd__mbctolower);
DEFINE_PUBLIC_ALIAS(DOS$_mbctoupper, libd__mbctoupper);
DEFINE_PUBLIC_ALIAS(DOS$_ismbchira, libd__ismbchira);
DEFINE_PUBLIC_ALIAS(DOS$_ismbckata, libd__ismbckata);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcsymbol, libd__ismbcsymbol);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcl0, libd__ismbcl0);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcl1, libd__ismbcl1);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcl2, libd__ismbcl2);
DEFINE_PUBLIC_ALIAS(DOS$_mbcjistojms, libd__mbcjistojms);
DEFINE_PUBLIC_ALIAS(DOS$_mbcjmstojis, libd__mbcjmstojis);
DEFINE_PUBLIC_ALIAS(DOS$_mbctohira, libd__mbctohira);
DEFINE_PUBLIC_ALIAS(DOS$_mbctokata, libd__mbctokata);
DEFINE_PUBLIC_ALIAS(DOS$_ismbslead, libd__ismbslead);
DEFINE_PUBLIC_ALIAS(DOS$_ismbstrail, libd__ismbstrail);
DEFINE_PUBLIC_ALIAS(DOS$_mbscat_l, libd__mbscat_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbscpy_l, libd__mbscpy_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbccpy_l, libd__mbccpy_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsncpy_l, libd__mbsncpy_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcpy_l, libd__mbsnbcpy_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbschr_l, libd__mbschr_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbscoll_l, libd__mbscoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsicoll_l, libd__mbsicoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsncoll_l, libd__mbsncoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnicoll_l, libd__mbsnicoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcoll_l, libd__mbsnbcoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbicoll_l, libd__mbsnbicoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbslwr_l, libd__mbslwr_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsupr_l, libd__mbsupr_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsinc_l, libd__mbsinc_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsninc_l, libd__mbsninc_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsdec_l, libd__mbsdec_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbscspn_l, libd__mbscspn_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbslen_l, libd__mbslen_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnlen_l, libd__mbsnlen_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsncat_l, libd__mbsncat_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcat_l, libd__mbsnbcat_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnccnt_l, libd__mbsnccnt_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcnt_l, libd__mbsnbcnt_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbscmp_l, libd__mbscmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsicmp_l, libd__mbsicmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsncmp_l, libd__mbsncmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnicmp_l, libd__mbsnicmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcmp_l, libd__mbsnbcmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbicmp_l, libd__mbsnbicmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnextc_l, libd__mbsnextc_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbspbrk_l, libd__mbspbrk_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsrchr_l, libd__mbsrchr_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsrev_l, libd__mbsrev_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsset_l, libd__mbsset_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnset_l, libd__mbsnset_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbset_l, libd__mbsnbset_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsspn_l, libd__mbsspn_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsspnp_l, libd__mbsspnp_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsstr_l, libd__mbsstr_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbstok_l, libd__mbstok_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbstok_s_l, libd__mbstok_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbclen_l, libd__mbclen_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbscat_s_l, libd__mbscat_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbscpy_s_l, libd__mbscpy_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbslwr_s_l, libd__mbslwr_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsupr_s_l, libd__mbsupr_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcat_s_l, libd__mbsnbcat_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbcpy_s_l, libd__mbsnbcpy_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnbset_s_l, libd__mbsnbset_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsncat_s_l, libd__mbsncat_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsncpy_s_l, libd__mbsncpy_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsnset_s_l, libd__mbsnset_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsset_s_l, libd__mbsset_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbccpy_s_l, libd__mbccpy_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbslead_l, libd__ismbslead_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbstrail_l, libd__ismbstrail_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbbtype_l, libd__mbbtype_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbsbtype_l, libd__mbsbtype_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbclegal_l, libd__ismbclegal_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbctolower_l, libd__mbctolower_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbctoupper_l, libd__mbctoupper_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcalnum_l, libd__ismbcalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcalpha_l, libd__ismbcalpha_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcdigit_l, libd__ismbcdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcgraph_l, libd__ismbcgraph_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbclower_l, libd__ismbclower_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcupper_l, libd__ismbcupper_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcprint_l, libd__ismbcprint_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcpunct_l, libd__ismbcpunct_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcblank_l, libd__ismbcblank_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcspace_l, libd__ismbcspace_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbchira_l, libd__ismbchira_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbckata_l, libd__ismbckata_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcsymbol_l, libd__ismbcsymbol_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcl0_l, libd__ismbcl0_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcl1_l, libd__ismbcl1_l);
DEFINE_PUBLIC_ALIAS(DOS$_ismbcl2_l, libd__ismbcl2_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbcjistojms_l, libd__mbcjistojms_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbcjmstojis_l, libd__mbcjmstojis_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbctohira_l, libd__mbctohira_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbctokata_l, libd__mbctokata_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbbtombc_l, libd__mbbtombc_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbctombb_l, libd__mbctombb_l);

/* mntent */
DEFINE_PUBLIC_ALIAS(DOS$__endmntent, libd_endmntent);
DEFINE_PUBLIC_ALIAS(DOS$endmntent, libd_endmntent);
DEFINE_PUBLIC_ALIAS(DOS$getmntent, libd_getmntent);
DEFINE_PUBLIC_ALIAS(DOS$__getmntent_r, libd_getmntent_r);
DEFINE_PUBLIC_ALIAS(DOS$getmntent_r, libd_getmntent_r);
DEFINE_PUBLIC_ALIAS(DOS$__addmntent, libd_addmntent);
DEFINE_PUBLIC_ALIAS(DOS$addmntent, libd_addmntent);
DEFINE_PUBLIC_ALIAS(DOS$__hasmntopt, libd_hasmntopt);
DEFINE_PUBLIC_ALIAS(DOS$hasmntopt, libd_hasmntopt);

/* mqueue */
DEFINE_PUBLIC_ALIAS(DOS$mq_open, libd_mq_open);
DEFINE_PUBLIC_ALIAS(DOS$mq_close, libd_mq_close);
DEFINE_PUBLIC_ALIAS(DOS$mq_getattr, libd_mq_getattr);
DEFINE_PUBLIC_ALIAS(DOS$mq_setattr, libd_mq_setattr);
DEFINE_PUBLIC_ALIAS(DOS$mq_unlink, libd_mq_unlink);
DEFINE_PUBLIC_ALIAS(DOS$mq_notify, libd_mq_notify);
DEFINE_PUBLIC_ALIAS(DOS$mq_receive, libd_mq_receive);
DEFINE_PUBLIC_ALIAS(DOS$mq_send, libd_mq_send);
DEFINE_PUBLIC_ALIAS(DOS$mq_timedreceive, libd_mq_timedreceive);
DEFINE_PUBLIC_ALIAS(DOS$mq_timedsend, libd_mq_timedsend);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__mq_timedreceive_time64, libd_mq_timedreceive64);
DEFINE_PUBLIC_ALIAS(DOS$mq_timedreceive64, libd_mq_timedreceive64);
DEFINE_PUBLIC_ALIAS(DOS$__mq_timedsend_time64, libd_mq_timedsend64);
DEFINE_PUBLIC_ALIAS(DOS$mq_timedsend64, libd_mq_timedsend64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* net.if */
DEFINE_PUBLIC_ALIAS(DOS$if_nametoindex, libd_if_nametoindex);
DEFINE_PUBLIC_ALIAS(DOS$if_indextoname, libd_if_indextoname);
DEFINE_PUBLIC_ALIAS(DOS$if_freenameindex, libd_if_freenameindex);

/* netdb */
DEFINE_PUBLIC_ALIAS(DOS$sethostent, libd_sethostent);
DEFINE_PUBLIC_ALIAS(DOS$gethostbyaddr, libd_gethostbyaddr);
DEFINE_PUBLIC_ALIAS(DOS$gethostbyname, libd_gethostbyname);
DEFINE_PUBLIC_ALIAS(DOS$setnetent, libd_setnetent);
DEFINE_PUBLIC_ALIAS(DOS$getnetbyaddr, libd_getnetbyaddr);
DEFINE_PUBLIC_ALIAS(DOS$getnetbyname, libd_getnetbyname);
DEFINE_PUBLIC_ALIAS(DOS$setservent, libd_setservent);
DEFINE_PUBLIC_ALIAS(DOS$getservbyname, libd_getservbyname);
DEFINE_PUBLIC_ALIAS(DOS$getservbyport, libd_getservbyport);
DEFINE_PUBLIC_ALIAS(DOS$setprotoent, libd_setprotoent);
DEFINE_PUBLIC_ALIAS(DOS$getprotobyname, libd_getprotobyname);
DEFINE_PUBLIC_ALIAS(DOS$getprotobynumber, libd_getprotobynumber);
DEFINE_PUBLIC_ALIAS(DOS$herror, libd_herror);
DEFINE_PUBLIC_ALIAS(DOS$hstrerror, libd_hstrerror);
DEFINE_PUBLIC_ALIAS(DOS$gethostbyname2, libd_gethostbyname2);
DEFINE_PUBLIC_ALIAS(DOS$__gethostent_r, libd_gethostent_r);
DEFINE_PUBLIC_ALIAS(DOS$gethostent_r, libd_gethostent_r);
DEFINE_PUBLIC_ALIAS(DOS$__gethostbyaddr_r, libd_gethostbyaddr_r);
DEFINE_PUBLIC_ALIAS(DOS$gethostbyaddr_r, libd_gethostbyaddr_r);
DEFINE_PUBLIC_ALIAS(DOS$__gethostbyname_r, libd_gethostbyname_r);
DEFINE_PUBLIC_ALIAS(DOS$gethostbyname_r, libd_gethostbyname_r);
DEFINE_PUBLIC_ALIAS(DOS$__gethostbyname2_r, libd_gethostbyname2_r);
DEFINE_PUBLIC_ALIAS(DOS$gethostbyname2_r, libd_gethostbyname2_r);
DEFINE_PUBLIC_ALIAS(DOS$__getnetent_r, libd_getnetent_r);
DEFINE_PUBLIC_ALIAS(DOS$getnetent_r, libd_getnetent_r);
DEFINE_PUBLIC_ALIAS(DOS$__getnetbyaddr_r, libd_getnetbyaddr_r);
DEFINE_PUBLIC_ALIAS(DOS$getnetbyaddr_r, libd_getnetbyaddr_r);
DEFINE_PUBLIC_ALIAS(DOS$__getnetbyname_r, libd_getnetbyname_r);
DEFINE_PUBLIC_ALIAS(DOS$getnetbyname_r, libd_getnetbyname_r);
DEFINE_PUBLIC_ALIAS(DOS$__getservent_r, libd_getservent_r);
DEFINE_PUBLIC_ALIAS(DOS$getservent_r, libd_getservent_r);
DEFINE_PUBLIC_ALIAS(DOS$__getservbyname_r, libd_getservbyname_r);
DEFINE_PUBLIC_ALIAS(DOS$getservbyname_r, libd_getservbyname_r);
DEFINE_PUBLIC_ALIAS(DOS$__getservbyport_r, libd_getservbyport_r);
DEFINE_PUBLIC_ALIAS(DOS$getservbyport_r, libd_getservbyport_r);
DEFINE_PUBLIC_ALIAS(DOS$__getprotoent_r, libd_getprotoent_r);
DEFINE_PUBLIC_ALIAS(DOS$getprotoent_r, libd_getprotoent_r);
DEFINE_PUBLIC_ALIAS(DOS$__getprotobyname_r, libd_getprotobyname_r);
DEFINE_PUBLIC_ALIAS(DOS$getprotobyname_r, libd_getprotobyname_r);
DEFINE_PUBLIC_ALIAS(DOS$__getprotobynumber_r, libd_getprotobynumber_r);
DEFINE_PUBLIC_ALIAS(DOS$getprotobynumber_r, libd_getprotobynumber_r);
DEFINE_PUBLIC_ALIAS(DOS$setnetgrent, libd_setnetgrent);
DEFINE_PUBLIC_ALIAS(DOS$getnetgrent, libd_getnetgrent);
DEFINE_PUBLIC_ALIAS(DOS$innetgr, libd_innetgr);
DEFINE_PUBLIC_ALIAS(DOS$__getnetgrent_r, libd_getnetgrent_r);
DEFINE_PUBLIC_ALIAS(DOS$getnetgrent_r, libd_getnetgrent_r);
DEFINE_PUBLIC_ALIAS(DOS$rcmd, libd_rcmd);
DEFINE_PUBLIC_ALIAS(DOS$rcmd_af, libd_rcmd_af);
DEFINE_PUBLIC_ALIAS(DOS$rexec, libd_rexec);
DEFINE_PUBLIC_ALIAS(DOS$rexec_af, libd_rexec_af);
DEFINE_PUBLIC_ALIAS(DOS$ruserok, libd_ruserok);
DEFINE_PUBLIC_ALIAS(DOS$ruserok_af, libd_ruserok_af);
DEFINE_PUBLIC_ALIAS(DOS$iruserok, libd_iruserok);
DEFINE_PUBLIC_ALIAS(DOS$iruserok_af, libd_iruserok_af);
DEFINE_PUBLIC_ALIAS(DOS$rresvport, libd_rresvport);
DEFINE_PUBLIC_ALIAS(DOS$rresvport_af, libd_rresvport_af);
DEFINE_PUBLIC_ALIAS(DOS$getaddrinfo, libd_getaddrinfo);
DEFINE_PUBLIC_ALIAS(DOS$freeaddrinfo, libd_freeaddrinfo);
DEFINE_PUBLIC_ALIAS(DOS$gai_strerror, libd_gai_strerror);
DEFINE_PUBLIC_ALIAS(DOS$getnameinfo, libd_getnameinfo);
DEFINE_PUBLIC_ALIAS(DOS$getaddrinfo_a, libd_getaddrinfo_a);
DEFINE_PUBLIC_ALIAS(DOS$gai_error, libd_gai_error);
DEFINE_PUBLIC_ALIAS(DOS$gai_cancel, libd_gai_cancel);
DEFINE_PUBLIC_ALIAS(DOS$gai_suspend, libd_gai_suspend);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__gai_suspend_time64, libd_gai_suspend64);
DEFINE_PUBLIC_ALIAS(DOS$gai_suspend64, libd_gai_suspend64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* netinet.ether */
DEFINE_PUBLIC_ALIAS(DOS$ether_ntoa, libd_ether_ntoa);
DEFINE_PUBLIC_ALIAS(DOS$ether_ntoa_r, libd_ether_ntoa_r);
DEFINE_PUBLIC_ALIAS(DOS$ether_aton, libd_ether_aton);
DEFINE_PUBLIC_ALIAS(DOS$ether_aton_r, libd_ether_aton_r);
DEFINE_PUBLIC_ALIAS(DOS$ether_aton_np, libd_ether_aton_np);
DEFINE_PUBLIC_ALIAS(DOS$ether_line, libd_ether_line);
DEFINE_PUBLIC_ALIAS(DOS$ether_line_np, libd_ether_line_np);
DEFINE_PUBLIC_ALIAS(DOS$ether_ntohost, libd_ether_ntohost);
DEFINE_PUBLIC_ALIAS(DOS$ether_hostton, libd_ether_hostton);

/* netinet.in */
DEFINE_PUBLIC_ALIAS(DOS$__htons, libd_htons);
DEFINE_PUBLIC_ALIAS(DOS$htons, libd_htons);
DEFINE_PUBLIC_ALIAS(DOS$__ntohs, libd_ntohs);
DEFINE_PUBLIC_ALIAS(DOS$ntohs, libd_ntohs);
DEFINE_PUBLIC_ALIAS(DOS$__htonl, libd_htonl);
DEFINE_PUBLIC_ALIAS(DOS$htonl, libd_htonl);
DEFINE_PUBLIC_ALIAS(DOS$__ntohl, libd_ntohl);
DEFINE_PUBLIC_ALIAS(DOS$ntohl, libd_ntohl);
DEFINE_PUBLIC_ALIAS(DOS$htonq, libd_htonq);
DEFINE_PUBLIC_ALIAS(DOS$ntohq, libd_ntohq);
DEFINE_PUBLIC_ALIAS(DOS$bindresvport, libd_bindresvport);
DEFINE_PUBLIC_ALIAS(DOS$bindresvport6, libd_bindresvport6);
DEFINE_PUBLIC_ALIAS(DOS$inet6_option_space, libd_inet6_option_space);
DEFINE_PUBLIC_ALIAS(DOS$inet6_option_init, libd_inet6_option_init);
DEFINE_PUBLIC_ALIAS(DOS$inet6_option_append, libd_inet6_option_append);
DEFINE_PUBLIC_ALIAS(DOS$inet6_option_alloc, libd_inet6_option_alloc);
DEFINE_PUBLIC_ALIAS(DOS$inet6_option_next, libd_inet6_option_next);
DEFINE_PUBLIC_ALIAS(DOS$inet6_option_find, libd_inet6_option_find);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_init, libd_inet6_opt_init);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_append, libd_inet6_opt_append);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_finish, libd_inet6_opt_finish);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_set_val, libd_inet6_opt_set_val);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_next, libd_inet6_opt_next);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_find, libd_inet6_opt_find);
DEFINE_PUBLIC_ALIAS(DOS$inet6_opt_get_val, libd_inet6_opt_get_val);
DEFINE_PUBLIC_ALIAS(DOS$inet6_rth_space, libd_inet6_rth_space);
DEFINE_PUBLIC_ALIAS(DOS$inet6_rth_init, libd_inet6_rth_init);
DEFINE_PUBLIC_ALIAS(DOS$inet6_rth_add, libd_inet6_rth_add);
DEFINE_PUBLIC_ALIAS(DOS$inet6_rth_reverse, libd_inet6_rth_reverse);
DEFINE_PUBLIC_ALIAS(DOS$inet6_rth_segments, libd_inet6_rth_segments);
DEFINE_PUBLIC_ALIAS(DOS$inet6_rth_getaddr, libd_inet6_rth_getaddr);
DEFINE_PUBLIC_ALIAS(DOS$getipv4sourcefilter, libd_getipv4sourcefilter);
DEFINE_PUBLIC_ALIAS(DOS$setipv4sourcefilter, libd_setipv4sourcefilter);
DEFINE_PUBLIC_ALIAS(DOS$getsourcefilter, libd_getsourcefilter);
DEFINE_PUBLIC_ALIAS(DOS$setsourcefilter, libd_setsourcefilter);

/* nl_types */
DEFINE_PUBLIC_ALIAS(DOS$catopen, libd_catopen);
DEFINE_PUBLIC_ALIAS(DOS$catgets, libd_catgets);
DEFINE_PUBLIC_ALIAS(DOS$catclose, libd_catclose);

/* objalloc */
DEFINE_PUBLIC_ALIAS(DOS$_objalloc_alloc, libd__objalloc_alloc);
DEFINE_PUBLIC_ALIAS(DOS$objalloc_free, libd_objalloc_free);
DEFINE_PUBLIC_ALIAS(DOS$objalloc_free_block, libd_objalloc_free_block);

/* obstack */
DEFINE_PUBLIC_ALIAS(DOS$_obstack_begin, libd__obstack_begin);
DEFINE_PUBLIC_ALIAS(DOS$_obstack_begin_1, libd__obstack_begin_1);
DEFINE_PUBLIC_ALIAS(DOS$_obstack_newchunk, libd__obstack_newchunk);
DEFINE_PUBLIC_ALIAS(DOS$_obstack_free, libd_obstack_free);
DEFINE_PUBLIC_ALIAS(DOS$obstack_free, libd_obstack_free);
DEFINE_PUBLIC_ALIAS(DOS$_obstack_memory_used, libd__obstack_memory_used);
DEFINE_PUBLIC_ALIAS(DOS$_obstack_allocated_p, libd__obstack_allocated_p);

/* partition */
DEFINE_PUBLIC_ALIAS(DOS$partition_new, libd_partition_new);
DEFINE_PUBLIC_ALIAS(DOS$partition_delete, libd_partition_delete);
DEFINE_PUBLIC_ALIAS(DOS$partition_union, libd_partition_union);
DEFINE_PUBLIC_ALIAS(DOS$partition_print, libd_partition_print);

/* process */
DEFINE_PUBLIC_ALIAS(DOS$_cwait, libd_cwait);
DEFINE_PUBLIC_ALIAS(DOS$cwait, libd_cwait);
DEFINE_PUBLIC_ALIAS(DOS$fspawnve, libd_fspawnve);
DEFINE_PUBLIC_ALIAS(DOS$_beginthread, libd__beginthread);
DEFINE_PUBLIC_ALIAS(DOS$_beginthreadex, libd__beginthreadex);
DEFINE_PUBLIC_ALIAS(DOS$_endthreadex, libd__endthreadex);
DEFINE_PUBLIC_ALIAS(DOS$_unloaddll, libd__unloaddll);
DEFINE_PUBLIC_ALIAS(DOS$_getdllprocaddr, libd__getdllprocaddr);

/* pthread */
DEFINE_PUBLIC_ALIAS(DOS$thr_exit, libd_pthread_exit);
DEFINE_PUBLIC_ALIAS(DOS$cthread_exit, libd_pthread_exit);
DEFINE_PUBLIC_ALIAS(DOS$pthread_exit, libd_pthread_exit);
DEFINE_PUBLIC_ALIAS(DOS$pthread_join, libd_pthread_join);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getresult_np, libd_pthread_getresult_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_peekjoin_np, libd_pthread_tryjoin_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_tryjoin_np, libd_pthread_tryjoin_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_timedjoin_np, libd_pthread_timedjoin_np);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__pthread_timedjoin_np64, libd_pthread_timedjoin64_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_timedjoin64_np, libd_pthread_timedjoin64_np);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$cthread_detach, libd_pthread_detach);
DEFINE_PUBLIC_ALIAS(DOS$pthread_detach, libd_pthread_detach);
DEFINE_PUBLIC_ALIAS(DOS$thrd_equal, libd_pthread_equal);
DEFINE_PUBLIC_ALIAS(DOS$pthread_equal, libd_pthread_equal);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_attr_init, libd_pthread_attr_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_init, libd_pthread_attr_init);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_attr_destroy, libd_pthread_attr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_destroy, libd_pthread_attr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getdetachstate, libd_pthread_attr_getdetachstate);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setdetachstate, libd_pthread_attr_setdetachstate);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getguardsize, libd_pthread_attr_getguardsize);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setguardsize, libd_pthread_attr_setguardsize);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getschedparam, libd_pthread_attr_getschedparam);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setschedparam, libd_pthread_attr_setschedparam);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getschedpolicy, libd_pthread_attr_getschedpolicy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setschedpolicy, libd_pthread_attr_setschedpolicy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getinheritsched, libd_pthread_attr_getinheritsched);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setinheritsched, libd_pthread_attr_setinheritsched);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getscope, libd_pthread_attr_getscope);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setscope, libd_pthread_attr_setscope);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getstackaddr, libd_pthread_attr_getstackaddr);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setstackaddr, libd_pthread_attr_setstackaddr);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getstacksize, libd_pthread_attr_getstacksize);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setstacksize, libd_pthread_attr_setstacksize);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getstack, libd_pthread_attr_getstack);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setstack, libd_pthread_attr_setstack);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_attr_setaffinity_np, libd_pthread_attr_setaffinity_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setaffinity_np, libd_pthread_attr_setaffinity_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getaffinity_np, libd_pthread_attr_getaffinity_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getattr_default_np, libd_pthread_getattr_default_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setattr_default_np, libd_pthread_setattr_default_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_get_np, libd_pthread_getattr_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getattr_np, libd_pthread_getattr_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setschedparam, libd_pthread_setschedparam);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getschedparam, libd_pthread_getschedparam);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setschedprio, libd_pthread_setschedprio);
DEFINE_PUBLIC_ALIAS(DOS$pthread_get_name_np, libd_pthread_getname_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getname_np, libd_pthread_getname_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_set_name_np, libd_pthread_setname_np);
DEFINE_PUBLIC_ALIAS(DOS$cthread_set_name, libd_pthread_setname_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setname_np, libd_pthread_setname_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_gettid_np, libd_pthread_gettid_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getpidfd_np, libd_pthread_getpidfd_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setpidfdallocated_np, libd_pthread_attr_setpidfdallocated_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getpidfdallocated_np, libd_pthread_attr_getpidfdallocated_np);
DEFINE_PUBLIC_ALIAS(DOS$thr_setconcurrency, libd_pthread_setconcurrency);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setconcurrency, libd_pthread_setconcurrency);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setaffinity_np, libd_pthread_setaffinity_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getaffinity_np, libd_pthread_getaffinity_np);
DEFINE_PUBLIC_ALIAS(DOS$call_once, libd_pthread_once);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_once, libd_pthread_once);
DEFINE_PUBLIC_ALIAS(DOS$pthread_once, libd_pthread_once);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setcancelstate, libd_pthread_setcancelstate);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setcanceltype, libd_pthread_setcanceltype);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cancel, libd_pthread_cancel);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_cleanup_routine, libd___pthread_cleanup_routine);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_register_cancel, libd___pthread_register_cancel);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_unregister_cancel, libd___pthread_unregister_cancel);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_register_cancel_defer, libd___pthread_register_cancel_defer);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_unregister_cancel_restore, libd___pthread_unregister_cancel_restore);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_unwind_next, libd___pthread_unwind_next);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_mutex_init, libd_pthread_mutex_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_init, libd_pthread_mutex_init);
DEFINE_PUBLIC_ALIAS(DOS$mtx_destroy, libd_pthread_mutex_destroy);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_mutex_destroy, libd_pthread_mutex_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_destroy, libd_pthread_mutex_destroy);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_mutex_trylock, libd_pthread_mutex_trylock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_trylock, libd_pthread_mutex_trylock);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_mutex_lock, libd_pthread_mutex_lock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_lock, libd_pthread_mutex_lock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_timedlock, libd_pthread_mutex_timedlock);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__pthread_mutex_timedlock64, libd_pthread_mutex_timedlock64);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_timedlock64, libd_pthread_mutex_timedlock64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_reltimedlock_np, libd_pthread_mutex_reltimedlock_np);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_reltimedlock64_np, libd_pthread_mutex_reltimedlock64_np);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$__pthread_mutex_unlock, libd_pthread_mutex_unlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_unlock, libd_pthread_mutex_unlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_getprioceiling, libd_pthread_mutex_getprioceiling);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_setprioceiling, libd_pthread_mutex_setprioceiling);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_consistent_np, libd_pthread_mutex_consistent);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_consistent, libd_pthread_mutex_consistent);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_mutexattr_init, libd_pthread_mutexattr_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_init, libd_pthread_mutexattr_init);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_mutexattr_destroy, libd_pthread_mutexattr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_destroy, libd_pthread_mutexattr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_getpshared, libd_pthread_mutexattr_getpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_setpshared, libd_pthread_mutexattr_setpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_getkind_np, libd_pthread_mutexattr_gettype);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_gettype, libd_pthread_mutexattr_gettype);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_setkind_np, libd_pthread_mutexattr_settype);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_mutexattr_settype, libd_pthread_mutexattr_settype);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_mutexattr_setkind_np, libd_pthread_mutexattr_settype);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_settype, libd_pthread_mutexattr_settype);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_getprotocol, libd_pthread_mutexattr_getprotocol);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_setprotocol, libd_pthread_mutexattr_setprotocol);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_getprioceiling, libd_pthread_mutexattr_getprioceiling);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_setprioceiling, libd_pthread_mutexattr_setprioceiling);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_getrobust_np, libd_pthread_mutexattr_getrobust);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_getrobust, libd_pthread_mutexattr_getrobust);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_setrobust_np, libd_pthread_mutexattr_setrobust);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutexattr_setrobust, libd_pthread_mutexattr_setrobust);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_rwlock_init, libd_pthread_rwlock_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_init, libd_pthread_rwlock_init);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_rwlock_destroy, libd_pthread_rwlock_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_destroy, libd_pthread_rwlock_destroy);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_rwlock_rdlock, libd_pthread_rwlock_rdlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_rdlock, libd_pthread_rwlock_rdlock);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_rwlock_tryrdlock, libd_pthread_rwlock_tryrdlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_tryrdlock, libd_pthread_rwlock_tryrdlock);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_rwlock_wrlock, libd_pthread_rwlock_wrlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_wrlock, libd_pthread_rwlock_wrlock);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_rwlock_trywrlock, libd_pthread_rwlock_trywrlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_trywrlock, libd_pthread_rwlock_trywrlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_timedrdlock, libd_pthread_rwlock_timedrdlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_timedwrlock, libd_pthread_rwlock_timedwrlock);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__pthread_rwlock_timedrdlock64, libd_pthread_rwlock_timedrdlock64);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_timedrdlock64, libd_pthread_rwlock_timedrdlock64);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_rwlock_timedwrlock64, libd_pthread_rwlock_timedwrlock64);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_timedwrlock64, libd_pthread_rwlock_timedwrlock64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_reltimedrdlock_np, libd_pthread_rwlock_reltimedrdlock_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_reltimedwrlock_np, libd_pthread_rwlock_reltimedwrlock_np);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_reltimedrdlock64_np, libd_pthread_rwlock_reltimedrdlock64_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_reltimedwrlock64_np, libd_pthread_rwlock_reltimedwrlock64_np);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$__pthread_rwlock_unlock, libd_pthread_rwlock_unlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlock_unlock, libd_pthread_rwlock_unlock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlockattr_init, libd_pthread_rwlockattr_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlockattr_destroy, libd_pthread_rwlockattr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlockattr_getpshared, libd_pthread_rwlockattr_getpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlockattr_setpshared, libd_pthread_rwlockattr_setpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlockattr_getkind_np, libd_pthread_rwlockattr_getkind_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_rwlockattr_setkind_np, libd_pthread_rwlockattr_setkind_np);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_cond_init, libd_pthread_cond_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_init, libd_pthread_cond_init);
DEFINE_PUBLIC_ALIAS(DOS$cnd_destroy, libd_pthread_cond_destroy);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_cond_destroy, libd_pthread_cond_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_destroy, libd_pthread_cond_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_signal, libd_pthread_cond_signal);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_broadcast, libd_pthread_cond_broadcast);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_wait, libd_pthread_cond_wait);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_timedwait, libd_pthread_cond_timedwait);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__pthread_cond_timedwait64, libd_pthread_cond_timedwait64);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_timedwait64, libd_pthread_cond_timedwait64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_timedwait_relative_np, libd_pthread_cond_reltimedwait_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_reltimedwait_np, libd_pthread_cond_reltimedwait_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_timedwait_relative64_np, libd_pthread_cond_reltimedwait64_np);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$pthread_cond_reltimedwait64_np, libd_pthread_cond_reltimedwait64_np);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$pthread_condattr_init, libd_pthread_condattr_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_condattr_destroy, libd_pthread_condattr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_condattr_getpshared, libd_pthread_condattr_getpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_condattr_setpshared, libd_pthread_condattr_setpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_condattr_getclock, libd_pthread_condattr_getclock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_condattr_setclock, libd_pthread_condattr_setclock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_spin_init, libd_pthread_spin_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_spin_destroy, libd_pthread_spin_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_spin_lock, libd_pthread_spin_lock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_spin_trylock, libd_pthread_spin_trylock);
DEFINE_PUBLIC_ALIAS(DOS$pthread_spin_unlock, libd_pthread_spin_unlock);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_barrier_init, libd_pthread_barrier_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrier_init, libd_pthread_barrier_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrier_destroy, libd_pthread_barrier_destroy);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_barrier_wait, libd_pthread_barrier_wait);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrier_wait, libd_pthread_barrier_wait);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrierattr_init, libd_pthread_barrierattr_init);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrierattr_destroy, libd_pthread_barrierattr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrierattr_getpshared, libd_pthread_barrierattr_getpshared);
DEFINE_PUBLIC_ALIAS(DOS$pthread_barrierattr_setpshared, libd_pthread_barrierattr_setpshared);
DEFINE_PUBLIC_ALIAS(DOS$tss_delete, libd_pthread_key_delete);
DEFINE_PUBLIC_ALIAS(DOS$pthread_key_delete, libd_pthread_key_delete);
DEFINE_PUBLIC_ALIAS(DOS$tss_get, libd_pthread_getspecific);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_getspecific, libd_pthread_getspecific);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getspecific, libd_pthread_getspecific);
DEFINE_PUBLIC_ALIAS(DOS$thr_setspecific, libd_pthread_setspecific);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_setspecific, libd_pthread_setspecific);
DEFINE_PUBLIC_ALIAS(DOS$pthread_setspecific, libd_pthread_setspecific);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getspecificptr_np, libd_pthread_getspecificptr_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getcpuclockid, libd_pthread_getcpuclockid);
DEFINE_PUBLIC_ALIAS(DOS$__pthread_atfork, libd_pthread_atfork);
DEFINE_PUBLIC_ALIAS(DOS$pthread_atfork, libd_pthread_atfork);
DEFINE_PUBLIC_ALIAS(DOS$pthread_set_num_processors_np, libd_pthread_set_num_processors_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setstartsuspended_np, libd_pthread_attr_setstartsuspended_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_getstartsuspended_np, libd_pthread_attr_getstartsuspended_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_suspend2_np, libd_pthread_suspend2_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_resume2_np, libd_pthread_resume2_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attach_np, libd_pthread_attach_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_enumthreads_np, libd_pthread_enumthreads_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attachtid_np, libd_pthread_attachtid_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attachpidfd_np, libd_pthread_attachpidfd_np);
DEFINE_PUBLIC_ALIAS(DOS$thr_continue, libd_pthread_continue_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_unsuspend_np, libd_pthread_continue_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_continue_np, libd_pthread_continue_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_attr_setcreatesuspend_np, libd_pthread_attr_setcreatesuspend_np);
DEFINE_PUBLIC_ALIAS(DOS$thr_suspend, libd_pthread_suspend_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_suspend_np, libd_pthread_suspend_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_resume_np, libd_pthread_resume_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_threadid_np, libd_pthread_getunique_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_getunique_np, libd_pthread_getunique_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_mutex_isowned_np, libd_pthread_mutex_isowned_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_switch_add_np, libd_pthread_switch_add_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_switch_delete_np, libd_pthread_switch_delete_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_get_stacksize_np, libd_pthread_get_stacksize_np);
DEFINE_PUBLIC_ALIAS(DOS$pthread_get_stackaddr_np, libd_pthread_get_stackaddr_np);

/* pthread_np */
DEFINE_PUBLIC_ALIAS(DOS$pthread_stackseg_np, libd_pthread_stackseg_np);

/* pty */
DEFINE_PUBLIC_ALIAS(DOS$openpty, libd_openpty);
DEFINE_PUBLIC_ALIAS(DOS$forkpty, libd_forkpty);

/* pwd */
DEFINE_PUBLIC_ALIAS(DOS$_getpwuid, libd_getpwuid);
DEFINE_PUBLIC_ALIAS(DOS$getpwuid, libd_getpwuid);
DEFINE_PUBLIC_ALIAS(DOS$_getpwnam, libd_getpwnam);
DEFINE_PUBLIC_ALIAS(DOS$getpwnam, libd_getpwnam);
DEFINE_PUBLIC_ALIAS(DOS$_fgetpwent, libd_fgetpwent);
DEFINE_PUBLIC_ALIAS(DOS$fgetpwent, libd_fgetpwent);
DEFINE_PUBLIC_ALIAS(DOS$putpwent, libd_putpwent);
DEFINE_PUBLIC_ALIAS(DOS$__getpwuid_r, libd_getpwuid_r);
DEFINE_PUBLIC_ALIAS(DOS$getpwuid_r, libd_getpwuid_r);
DEFINE_PUBLIC_ALIAS(DOS$__getpwnam_r, libd_getpwnam_r);
DEFINE_PUBLIC_ALIAS(DOS$getpwnam_r, libd_getpwnam_r);
DEFINE_PUBLIC_ALIAS(DOS$__getpwent_r, libd_getpwent_r);
DEFINE_PUBLIC_ALIAS(DOS$getpwent_r, libd_getpwent_r);
DEFINE_PUBLIC_ALIAS(DOS$__fgetpwent_r, libd_fgetpwent_r);
DEFINE_PUBLIC_ALIAS(DOS$fgetpwent_r, libd_fgetpwent_r);
DEFINE_PUBLIC_ALIAS(DOS$fgetpwuid_r, libd_fgetpwuid_r);
DEFINE_PUBLIC_ALIAS(DOS$fgetpwnam_r, libd_fgetpwnam_r);
DEFINE_PUBLIC_ALIAS(DOS$__getpw, libd_getpw);
DEFINE_PUBLIC_ALIAS(DOS$getpw, libd_getpw);
DEFINE_PUBLIC_ALIAS(DOS$_sgetpwent, libd_sgetpwent);
DEFINE_PUBLIC_ALIAS(DOS$sgetpwent, libd_sgetpwent);
DEFINE_PUBLIC_ALIAS(DOS$setpassent, libd_setpassent);
DEFINE_PUBLIC_ALIAS(DOS$uid_from_user, libd_uid_from_user);
DEFINE_PUBLIC_ALIAS(DOS$user_from_uid, libd_user_from_uid);
DEFINE_PUBLIC_ALIAS(DOS$pw_dup, libd_pw_dup);

/* readpassphrase */
DEFINE_PUBLIC_ALIAS(DOS$readpassphrase, libd_readpassphrase);

/* regex */
DEFINE_PUBLIC_ALIAS(DOS$re_set_syntax, libd_re_set_syntax);
DEFINE_PUBLIC_ALIAS(DOS$re_compile_pattern, libd_re_compile_pattern);
DEFINE_PUBLIC_ALIAS(DOS$re_compile_fastmap, libd_re_compile_fastmap);
DEFINE_PUBLIC_ALIAS(DOS$re_search, libd_re_search);
DEFINE_PUBLIC_ALIAS(DOS$re_search_2, libd_re_search_2);
DEFINE_PUBLIC_ALIAS(DOS$re_match, libd_re_match);
DEFINE_PUBLIC_ALIAS(DOS$re_match_2, libd_re_match_2);
DEFINE_PUBLIC_ALIAS(DOS$re_set_registers, libd_re_set_registers);
DEFINE_PUBLIC_ALIAS(DOS$regcomp, libd_regcomp);
DEFINE_PUBLIC_ALIAS(DOS$regexec, libd_regexec);
DEFINE_PUBLIC_ALIAS(DOS$regerror, libd_regerror);
DEFINE_PUBLIC_ALIAS(DOS$regfree, libd_regfree);
DEFINE_PUBLIC_ALIAS(DOS$regerrordesc_np, libd_regerrordesc_np);
DEFINE_PUBLIC_ALIAS(DOS$re_comp, libd_re_comp);
DEFINE_PUBLIC_ALIAS(DOS$re_exec, libd_re_exec);
DEFINE_PUBLIC_ALIAS(DOS$regsubprintv, libd_regsubprintv);
DEFINE_PUBLIC_ALIAS(DOS$regsubprint, libd_regsubprint);
DEFINE_PUBLIC_ALIAS(DOS$regnsub, libd_regnsub);
DEFINE_PUBLIC_ALIAS(DOS$regasub, libd_regasub);

/* regexp */
DEFINE_PUBLIC_ALIAS(DOS$__step, libd_step);
DEFINE_PUBLIC_ALIAS(DOS$step, libd_step);
DEFINE_PUBLIC_ALIAS(DOS$__advance, libd_advance);
DEFINE_PUBLIC_ALIAS(DOS$advance, libd_advance);

/* resolv */
DEFINE_PUBLIC_ALIAS(DOS$__fp_nquery, libd_fp_nquery);
DEFINE_PUBLIC_ALIAS(DOS$fp_nquery, libd_fp_nquery);
DEFINE_PUBLIC_ALIAS(DOS$__fp_query, libd_fp_query);
DEFINE_PUBLIC_ALIAS(DOS$fp_query, libd_fp_query);
DEFINE_PUBLIC_ALIAS(DOS$__hostalias, libd_hostalias);
DEFINE_PUBLIC_ALIAS(DOS$hostalias, libd_hostalias);
DEFINE_PUBLIC_ALIAS(DOS$__p_query, libd_p_query);
DEFINE_PUBLIC_ALIAS(DOS$p_query, libd_p_query);
DEFINE_PUBLIC_ALIAS(DOS$__res_isourserver, libd_res_isourserver);
DEFINE_PUBLIC_ALIAS(DOS$res_isourserver, libd_res_isourserver);
DEFINE_PUBLIC_ALIAS(DOS$__res_mkquery, libd_res_mkquery);
DEFINE_PUBLIC_ALIAS(DOS$res_mkquery, libd_res_mkquery);
DEFINE_PUBLIC_ALIAS(DOS$__res_query, libd_res_query);
DEFINE_PUBLIC_ALIAS(DOS$res_query, libd_res_query);
DEFINE_PUBLIC_ALIAS(DOS$__res_querydomain, libd_res_querydomain);
DEFINE_PUBLIC_ALIAS(DOS$res_querydomain, libd_res_querydomain);
DEFINE_PUBLIC_ALIAS(DOS$__res_search, libd_res_search);
DEFINE_PUBLIC_ALIAS(DOS$res_search, libd_res_search);
DEFINE_PUBLIC_ALIAS(DOS$__res_send, libd_res_send);
DEFINE_PUBLIC_ALIAS(DOS$res_send, libd_res_send);
DEFINE_PUBLIC_ALIAS(DOS$__res_hnok, libd_res_hnok);
DEFINE_PUBLIC_ALIAS(DOS$res_hnok, libd_res_hnok);
DEFINE_PUBLIC_ALIAS(DOS$__res_ownok, libd_res_ownok);
DEFINE_PUBLIC_ALIAS(DOS$res_ownok, libd_res_ownok);
DEFINE_PUBLIC_ALIAS(DOS$__res_mailok, libd_res_mailok);
DEFINE_PUBLIC_ALIAS(DOS$res_mailok, libd_res_mailok);
DEFINE_PUBLIC_ALIAS(DOS$__res_dnok, libd_res_dnok);
DEFINE_PUBLIC_ALIAS(DOS$res_dnok, libd_res_dnok);
DEFINE_PUBLIC_ALIAS(DOS$__sym_ston, libd_sym_ston);
DEFINE_PUBLIC_ALIAS(DOS$sym_ston, libd_sym_ston);
DEFINE_PUBLIC_ALIAS(DOS$__sym_ntos, libd_sym_ntos);
DEFINE_PUBLIC_ALIAS(DOS$sym_ntos, libd_sym_ntos);
DEFINE_PUBLIC_ALIAS(DOS$__sym_ntop, libd_sym_ntop);
DEFINE_PUBLIC_ALIAS(DOS$sym_ntop, libd_sym_ntop);
DEFINE_PUBLIC_ALIAS(DOS$__b64_ntop, libd_b64_ntop);
DEFINE_PUBLIC_ALIAS(DOS$b64_ntop, libd_b64_ntop);
DEFINE_PUBLIC_ALIAS(DOS$__b64_pton, libd_b64_pton);
DEFINE_PUBLIC_ALIAS(DOS$b64_pton, libd_b64_pton);
DEFINE_PUBLIC_ALIAS(DOS$__loc_aton, libd_loc_aton);
DEFINE_PUBLIC_ALIAS(DOS$loc_aton, libd_loc_aton);
DEFINE_PUBLIC_ALIAS(DOS$__loc_ntoa, libd_loc_ntoa);
DEFINE_PUBLIC_ALIAS(DOS$loc_ntoa, libd_loc_ntoa);
DEFINE_PUBLIC_ALIAS(DOS$__dn_skipname, libd_dn_skipname);
DEFINE_PUBLIC_ALIAS(DOS$dn_skipname, libd_dn_skipname);
DEFINE_PUBLIC_ALIAS(DOS$__p_class, libd_p_class);
DEFINE_PUBLIC_ALIAS(DOS$p_class, libd_p_class);
DEFINE_PUBLIC_ALIAS(DOS$__p_time, libd_p_time);
DEFINE_PUBLIC_ALIAS(DOS$p_time, libd_p_time);
DEFINE_PUBLIC_ALIAS(DOS$__p_type, libd_p_type);
DEFINE_PUBLIC_ALIAS(DOS$p_type, libd_p_type);
DEFINE_PUBLIC_ALIAS(DOS$__p_rcode, libd_p_rcode);
DEFINE_PUBLIC_ALIAS(DOS$p_rcode, libd_p_rcode);
DEFINE_PUBLIC_ALIAS(DOS$__p_cdnname, libd_p_cdnname);
DEFINE_PUBLIC_ALIAS(DOS$p_cdnname, libd_p_cdnname);
DEFINE_PUBLIC_ALIAS(DOS$__p_cdname, libd_p_cdname);
DEFINE_PUBLIC_ALIAS(DOS$p_cdname, libd_p_cdname);
DEFINE_PUBLIC_ALIAS(DOS$__p_fqnname, libd_p_fqnname);
DEFINE_PUBLIC_ALIAS(DOS$p_fqnname, libd_p_fqnname);
DEFINE_PUBLIC_ALIAS(DOS$__p_fqname, libd_p_fqname);
DEFINE_PUBLIC_ALIAS(DOS$p_fqname, libd_p_fqname);
DEFINE_PUBLIC_ALIAS(DOS$__p_option, libd_p_option);
DEFINE_PUBLIC_ALIAS(DOS$p_option, libd_p_option);
DEFINE_PUBLIC_ALIAS(DOS$__p_secstodate, libd_p_secstodate);
DEFINE_PUBLIC_ALIAS(DOS$p_secstodate, libd_p_secstodate);
DEFINE_PUBLIC_ALIAS(DOS$__dn_count_labels, libd_dn_count_labels);
DEFINE_PUBLIC_ALIAS(DOS$dn_count_labels, libd_dn_count_labels);
DEFINE_PUBLIC_ALIAS(DOS$__dn_expand, libd_dn_expand);
DEFINE_PUBLIC_ALIAS(DOS$dn_expand, libd_dn_expand);
DEFINE_PUBLIC_ALIAS(DOS$__res_nameinquery, libd_res_nameinquery);
DEFINE_PUBLIC_ALIAS(DOS$res_nameinquery, libd_res_nameinquery);
DEFINE_PUBLIC_ALIAS(DOS$__res_queriesmatch, libd_res_queriesmatch);
DEFINE_PUBLIC_ALIAS(DOS$res_queriesmatch, libd_res_queriesmatch);
DEFINE_PUBLIC_ALIAS(DOS$__p_section, libd_p_section);
DEFINE_PUBLIC_ALIAS(DOS$p_section, libd_p_section);
DEFINE_PUBLIC_ALIAS(DOS$__res_ninit, libd_res_ninit);
DEFINE_PUBLIC_ALIAS(DOS$res_ninit, libd_res_ninit);
DEFINE_PUBLIC_ALIAS(DOS$__res_nisourserver, libd_res_nisourserver);
DEFINE_PUBLIC_ALIAS(DOS$res_nisourserver, libd_res_nisourserver);
DEFINE_PUBLIC_ALIAS(DOS$__fp_resstat, libd_fp_resstat);
DEFINE_PUBLIC_ALIAS(DOS$fp_resstat, libd_fp_resstat);
DEFINE_PUBLIC_ALIAS(DOS$__res_npquery, libd_res_npquery);
DEFINE_PUBLIC_ALIAS(DOS$res_npquery, libd_res_npquery);
DEFINE_PUBLIC_ALIAS(DOS$__res_hostalias, libd_res_hostalias);
DEFINE_PUBLIC_ALIAS(DOS$res_hostalias, libd_res_hostalias);
DEFINE_PUBLIC_ALIAS(DOS$__res_nquery, libd_res_nquery);
DEFINE_PUBLIC_ALIAS(DOS$res_nquery, libd_res_nquery);
DEFINE_PUBLIC_ALIAS(DOS$__res_nsearch, libd_res_nsearch);
DEFINE_PUBLIC_ALIAS(DOS$res_nsearch, libd_res_nsearch);
DEFINE_PUBLIC_ALIAS(DOS$__res_nquerydomain, libd_res_nquerydomain);
DEFINE_PUBLIC_ALIAS(DOS$res_nquerydomain, libd_res_nquerydomain);
DEFINE_PUBLIC_ALIAS(DOS$__res_nmkquery, libd_res_nmkquery);
DEFINE_PUBLIC_ALIAS(DOS$res_nmkquery, libd_res_nmkquery);
DEFINE_PUBLIC_ALIAS(DOS$__res_nsend, libd_res_nsend);
DEFINE_PUBLIC_ALIAS(DOS$res_nsend, libd_res_nsend);
DEFINE_PUBLIC_ALIAS(DOS$__res_nclose, libd_res_nclose);
DEFINE_PUBLIC_ALIAS(DOS$res_nclose, libd_res_nclose);

/* rpc.netdb */
DEFINE_PUBLIC_ALIAS(DOS$setrpcent, libd_setrpcent);
DEFINE_PUBLIC_ALIAS(DOS$getrpcbyname, libd_getrpcbyname);
DEFINE_PUBLIC_ALIAS(DOS$getrpcbynumber, libd_getrpcbynumber);
DEFINE_PUBLIC_ALIAS(DOS$__getrpcbyname_r, libd_getrpcbyname_r);
DEFINE_PUBLIC_ALIAS(DOS$getrpcbyname_r, libd_getrpcbyname_r);
DEFINE_PUBLIC_ALIAS(DOS$__getrpcbynumber_r, libd_getrpcbynumber_r);
DEFINE_PUBLIC_ALIAS(DOS$getrpcbynumber_r, libd_getrpcbynumber_r);
DEFINE_PUBLIC_ALIAS(DOS$__getrpcent_r, libd_getrpcent_r);
DEFINE_PUBLIC_ALIAS(DOS$getrpcent_r, libd_getrpcent_r);

/* sched */
DEFINE_PUBLIC_ALIAS(DOS$unshare, libd_unshare);
DEFINE_PUBLIC_ALIAS(DOS$setns, libd_setns);
DEFINE_PUBLIC_ALIAS(DOS$exit_thread, libd_exit_thread);
DEFINE_PUBLIC_ALIAS(DOS$__sched_setparam, libd_sched_setparam);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sched_setparam, libd_sched_setparam);
DEFINE_PUBLIC_ALIAS(DOS$sched_setparam, libd_sched_setparam);
DEFINE_PUBLIC_ALIAS(DOS$__sched_getparam, libd_sched_getparam);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sched_getparam, libd_sched_getparam);
DEFINE_PUBLIC_ALIAS(DOS$sched_getparam, libd_sched_getparam);
DEFINE_PUBLIC_ALIAS(DOS$__sched_setscheduler, libd_sched_setscheduler);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sched_setscheduler, libd_sched_setscheduler);
DEFINE_PUBLIC_ALIAS(DOS$sched_setscheduler, libd_sched_setscheduler);
DEFINE_PUBLIC_ALIAS(DOS$__sched_getscheduler, libd_sched_getscheduler);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sched_getscheduler, libd_sched_getscheduler);
DEFINE_PUBLIC_ALIAS(DOS$sched_getscheduler, libd_sched_getscheduler);
DEFINE_PUBLIC_ALIAS(DOS$__sched_get_priority_max, libd_sched_get_priority_max);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sched_get_priority_max, libd_sched_get_priority_max);
DEFINE_PUBLIC_ALIAS(DOS$sched_get_priority_max, libd_sched_get_priority_max);
DEFINE_PUBLIC_ALIAS(DOS$__sched_get_priority_min, libd_sched_get_priority_min);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sched_get_priority_min, libd_sched_get_priority_min);
DEFINE_PUBLIC_ALIAS(DOS$sched_get_priority_min, libd_sched_get_priority_min);
DEFINE_PUBLIC_ALIAS(DOS$sched_setaffinity, libd_sched_setaffinity);
DEFINE_PUBLIC_ALIAS(DOS$sched_getaffinity, libd_sched_getaffinity);
DEFINE_PUBLIC_ALIAS(DOS$__sched_rr_get_interval, libd_sched_rr_get_interval);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sched_rr_get_interval, libd_sched_rr_get_interval);
DEFINE_PUBLIC_ALIAS(DOS$sched_rr_get_interval, libd_sched_rr_get_interval);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__sched_rr_get_interval64, libd_sched_rr_get_interval64);
DEFINE_PUBLIC_ALIAS(DOS$sched_rr_get_interval64, libd_sched_rr_get_interval64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* search */
DEFINE_PUBLIC_ALIAS(DOS$insque, libd_insque);
DEFINE_PUBLIC_ALIAS(DOS$remque, libd_remque);
DEFINE_PUBLIC_ALIAS(DOS$hsearch, libd_hsearch);
DEFINE_PUBLIC_ALIAS(DOS$hcreate, libd_hcreate);
DEFINE_PUBLIC_ALIAS(DOS$hsearch_r, libd_hsearch_r);
DEFINE_PUBLIC_ALIAS(DOS$hcreate_r, libd_hcreate_r);
DEFINE_PUBLIC_ALIAS(DOS$hdestroy_r, libd_hdestroy_r);

/* semaphore */
DEFINE_PUBLIC_ALIAS(DOS$sem_init, libd_sem_init);
DEFINE_PUBLIC_ALIAS(DOS$sem_destroy, libd_sem_destroy);
DEFINE_PUBLIC_ALIAS(DOS$sem_open, libd_sem_open);
DEFINE_PUBLIC_ALIAS(DOS$sem_close, libd_sem_close);
DEFINE_PUBLIC_ALIAS(DOS$sem_unlink, libd_sem_unlink);
DEFINE_PUBLIC_ALIAS(DOS$sem_wait, libd_sem_wait);
DEFINE_PUBLIC_ALIAS(DOS$sem_timedwait, libd_sem_timedwait);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__sem_timedwait64, libd_sem_timedwait64);
DEFINE_PUBLIC_ALIAS(DOS$sem_timedwait64, libd_sem_timedwait64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$sem_trywait, libd_sem_trywait);
DEFINE_PUBLIC_ALIAS(DOS$sem_post, libd_sem_post);
DEFINE_PUBLIC_ALIAS(DOS$sem_post_multiple, libd_sem_post_multiple);
DEFINE_PUBLIC_ALIAS(DOS$sem_getvalue, libd_sem_getvalue);

/* sgtty */
DEFINE_PUBLIC_ALIAS(DOS$gtty, libd_gtty);
DEFINE_PUBLIC_ALIAS(DOS$stty, libd_stty);

/* shadow */
DEFINE_PUBLIC_ALIAS(DOS$__getspnam, libd_getspnam);
DEFINE_PUBLIC_ALIAS(DOS$getspnam, libd_getspnam);
DEFINE_PUBLIC_ALIAS(DOS$fgetspent, libd_fgetspent);
DEFINE_PUBLIC_ALIAS(DOS$sgetspent, libd_sgetspent);
DEFINE_PUBLIC_ALIAS(DOS$putspent, libd_putspent);
DEFINE_PUBLIC_ALIAS(DOS$__getspent_r, libd_getspent_r);
DEFINE_PUBLIC_ALIAS(DOS$getspent_r, libd_getspent_r);
DEFINE_PUBLIC_ALIAS(DOS$__getspnam_r, libd_getspnam_r);
DEFINE_PUBLIC_ALIAS(DOS$getspnam_r, libd_getspnam_r);
DEFINE_PUBLIC_ALIAS(DOS$__sgetspent_r, libd_sgetspent_r);
DEFINE_PUBLIC_ALIAS(DOS$sgetspent_r, libd_sgetspent_r);
DEFINE_PUBLIC_ALIAS(DOS$__fgetspent_r, libd_fgetspent_r);
DEFINE_PUBLIC_ALIAS(DOS$fgetspent_r, libd_fgetspent_r);
DEFINE_PUBLIC_ALIAS(DOS$fgetspnam_r, libd_fgetspnam_r);

/* signal */
DEFINE_PUBLIC_ALIAS(DOS$tgkill, libd_tgkill);
DEFINE_PUBLIC_ALIAS(DOS$__sigblock, libd_sigblock);
DEFINE_PUBLIC_ALIAS(DOS$sigblock, libd_sigblock);
DEFINE_PUBLIC_ALIAS(DOS$__sigsetmask, libd_sigsetmask);
DEFINE_PUBLIC_ALIAS(DOS$sigsetmask, libd_sigsetmask);
DEFINE_PUBLIC_ALIAS(DOS$__sigpause, libd_sigpause);
DEFINE_PUBLIC_ALIAS(DOS$sigpause, libd_sigpause);
DEFINE_PUBLIC_ALIAS(DOS$sigreturn, libd_sigreturn);
DEFINE_PUBLIC_ALIAS(DOS$__xpg_sigpause, libd___xpg_sigpause);
DEFINE_PUBLIC_ALIAS(DOS$__kill, libd_kill);
DEFINE_PUBLIC_ALIAS(DOS$__libc_kill, libd_kill);
DEFINE_PUBLIC_ALIAS(DOS$kill, libd_kill);
DEFINE_PUBLIC_ALIAS(DOS$sigemptyset, libd_sigemptyset);
DEFINE_PUBLIC_ALIAS(DOS$sigfillset, libd_sigfillset);
DEFINE_PUBLIC_ALIAS(DOS$__sigaddset, libd_sigaddset);
DEFINE_PUBLIC_ALIAS(DOS$sigaddset, libd_sigaddset);
DEFINE_PUBLIC_ALIAS(DOS$__sigdelset, libd_sigdelset);
DEFINE_PUBLIC_ALIAS(DOS$sigdelset, libd_sigdelset);
DEFINE_PUBLIC_ALIAS(DOS$__sigismember, libd_sigismember);
DEFINE_PUBLIC_ALIAS(DOS$sigismember, libd_sigismember);
DEFINE_PUBLIC_ALIAS(DOS$__sigprocmask, libd_sigprocmask);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sigprocmask, libd_sigprocmask);
DEFINE_PUBLIC_ALIAS(DOS$pthread_sigmask, libd_sigprocmask);
DEFINE_PUBLIC_ALIAS(DOS$thr_sigsetmask, libd_sigprocmask);
DEFINE_PUBLIC_ALIAS(DOS$sigprocmask, libd_sigprocmask);
DEFINE_PUBLIC_ALIAS(DOS$setsigmaskptr, libd_setsigmaskptr);
DEFINE_PUBLIC_ALIAS(DOS$__sigsuspend, libd_sigsuspend);
DEFINE_PUBLIC_ALIAS(DOS$sigsuspend, libd_sigsuspend);
DEFINE_PUBLIC_ALIAS(DOS$__sigaction, libd_sigaction);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sigaction, libd_sigaction);
DEFINE_PUBLIC_ALIAS(DOS$sigaction, libd_sigaction);
DEFINE_PUBLIC_ALIAS(DOS$__sigpending, libd_sigpending);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sigpending, libd_sigpending);
DEFINE_PUBLIC_ALIAS(DOS$sigpending, libd_sigpending);
DEFINE_PUBLIC_ALIAS(DOS$__sigwait, libd_sigwait);
DEFINE_PUBLIC_ALIAS(DOS$sigwait, libd_sigwait);
DEFINE_PUBLIC_ALIAS(DOS$sigisemptyset, libd_sigisemptyset);
DEFINE_PUBLIC_ALIAS(DOS$sigandset, libd_sigandset);
DEFINE_PUBLIC_ALIAS(DOS$sigorset, libd_sigorset);
DEFINE_PUBLIC_ALIAS(DOS$signandset, libd_signandset);
DEFINE_PUBLIC_ALIAS(DOS$sigisfullset, libd_sigisfullset);
DEFINE_PUBLIC_ALIAS(DOS$__sigwaitinfo, libd_sigwaitinfo);
DEFINE_PUBLIC_ALIAS(DOS$sigwaitinfo, libd_sigwaitinfo);
DEFINE_PUBLIC_ALIAS(DOS$__sigtimedwait, libd_sigtimedwait);
DEFINE_PUBLIC_ALIAS(DOS$sigtimedwait, libd_sigtimedwait);
DEFINE_PUBLIC_ALIAS(DOS$sigqueue, libd_sigqueue);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__sigtimedwait64, libd_sigtimedwait64);
DEFINE_PUBLIC_ALIAS(DOS$sigtimedwait64, libd_sigtimedwait64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$sigqueueinfo, libd_sigqueueinfo);
DEFINE_PUBLIC_ALIAS(DOS$tgsigqueueinfo, libd_tgsigqueueinfo);
DEFINE_PUBLIC_ALIAS(DOS$killpg, libd_killpg);
DEFINE_PUBLIC_ALIAS(DOS$psignal, libd_psignal);
DEFINE_PUBLIC_ALIAS(DOS$psiginfo, libd_psiginfo);
DEFINE_PUBLIC_ALIAS(DOS$sigcodename_np, libd_sigcodename_np);
DEFINE_PUBLIC_ALIAS(DOS$sigcodedesc_np, libd_sigcodedesc_np);
DEFINE_PUBLIC_ALIAS(DOS$siginterrupt, libd_siginterrupt);
DEFINE_PUBLIC_ALIAS(DOS$sigstack, libd_sigstack);
DEFINE_PUBLIC_ALIAS(DOS$sigaltstack, libd_sigaltstack);
DEFINE_PUBLIC_ALIAS(DOS$sighold, libd_sighold);
DEFINE_PUBLIC_ALIAS(DOS$sigrelse, libd_sigrelse);
DEFINE_PUBLIC_ALIAS(DOS$sigignore, libd_sigignore);
DEFINE_PUBLIC_ALIAS(DOS$sigset, libd_sigset);
DEFINE_PUBLIC_ALIAS(DOS$__libc_allocate_rtsig_private, libd___libc_allocate_rtsig);
DEFINE_PUBLIC_ALIAS(DOS$__libc_allocate_rtsig, libd___libc_allocate_rtsig);
DEFINE_PUBLIC_ALIAS(DOS$thr_kill, libd_pthread_kill);
DEFINE_PUBLIC_ALIAS(DOS$pthread_kill, libd_pthread_kill);
DEFINE_PUBLIC_ALIAS(DOS$pthread_sigqueue, libd_pthread_sigqueue);
DEFINE_PUBLIC_ALIAS(DOS$signalnumber, libd_signalnumber);
DEFINE_PUBLIC_ALIAS(DOS$signalnext, libd_signalnext);
DEFINE_PUBLIC_ALIAS(DOS$sig2str, libd_sig2str);
DEFINE_PUBLIC_ALIAS(DOS$str2sig, libd_str2sig);

/* sort */
DEFINE_PUBLIC_ALIAS(DOS$sort_pointers, libd_sort_pointers);

/* spawn */
DEFINE_PUBLIC_ALIAS(DOS$posix_fspawn_np, libd_posix_fspawn_np);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn, libd_posix_spawn);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnp, libd_posix_spawnp);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_init, libd_posix_spawnattr_init);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_destroy, libd_posix_spawnattr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_getflags, libd_posix_spawnattr_getflags);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_setflags, libd_posix_spawnattr_setflags);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_getsigdefault, libd_posix_spawnattr_getsigdefault);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_setsigdefault, libd_posix_spawnattr_setsigdefault);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_getsigmask, libd_posix_spawnattr_getsigmask);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_setsigmask, libd_posix_spawnattr_setsigmask);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_getpgroup, libd_posix_spawnattr_getpgroup);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_setpgroup, libd_posix_spawnattr_setpgroup);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_getschedpolicy, libd_posix_spawnattr_getschedpolicy);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_setschedpolicy, libd_posix_spawnattr_setschedpolicy);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_getschedparam, libd_posix_spawnattr_getschedparam);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_setschedparam, libd_posix_spawnattr_setschedparam);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_init, libd_posix_spawn_file_actions_init);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_destroy, libd_posix_spawn_file_actions_destroy);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_addopen, libd_posix_spawn_file_actions_addopen);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_addclose, libd_posix_spawn_file_actions_addclose);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_adddup2, libd_posix_spawn_file_actions_adddup2);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_addtcsetpgrp_np, libd_posix_spawn_file_actions_addtcsetpgrp_np);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_addclosefrom_np, libd_posix_spawn_file_actions_addclosefrom_np);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_addchdir_np, libd_posix_spawn_file_actions_addchdir_np);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_addfchdir_np, libd_posix_spawn_file_actions_addfchdir_np);

/* ssp.string */
DEFINE_PUBLIC_ALIAS(DOS$__memcpy_chk, libd___memcpy_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmove_chk, libd___memmove_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memset_chk, libd___memset_chk);
DEFINE_PUBLIC_ALIAS(DOS$__strcat_chk, libd___strcat_chk);
DEFINE_PUBLIC_ALIAS(DOS$__strcpy_chk, libd___strcpy_chk);
DEFINE_PUBLIC_ALIAS(DOS$__strncat_chk, libd___strncat_chk);
DEFINE_PUBLIC_ALIAS(DOS$__strncpy_chk, libd___strncpy_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempcpy_chk, libd___mempcpy_chk);
DEFINE_PUBLIC_ALIAS(DOS$__stpcpy_chk, libd___stpcpy_chk);
DEFINE_PUBLIC_ALIAS(DOS$__stpncpy_chk, libd___stpncpy_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmove_chk, libd___mempmove_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempset_chk, libd___mempset_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmoveup_chk, libd___memmoveup_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovedown_chk, libd___memmovedown_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmoveup_chk, libd___mempmoveup_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovedown_chk, libd___mempmovedown_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memcpyc_chk, libd___memcpyc_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovec_chk, libd___memmovec_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempcpyc_chk, libd___mempcpyc_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovec_chk, libd___mempmovec_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmoveupc_chk, libd___memmoveupc_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovedownc_chk, libd___memmovedownc_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmoveupc_chk, libd___mempmoveupc_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovedownc_chk, libd___mempmovedownc_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memcpyw_chk, libd___memcpyw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempcpyw_chk, libd___mempcpyw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovew_chk, libd___memmovew_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memcpyl_chk, libd___memcpyl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempcpyl_chk, libd___mempcpyl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovel_chk, libd___memmovel_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovew_chk, libd___mempmovew_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovel_chk, libd___mempmovel_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memsetw_chk, libd___memsetw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempsetw_chk, libd___mempsetw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memsetl_chk, libd___memsetl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempsetl_chk, libd___mempsetl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmoveupw_chk, libd___memmoveupw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovedownw_chk, libd___memmovedownw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmoveupl_chk, libd___memmoveupl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovedownl_chk, libd___memmovedownl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmoveupw_chk, libd___mempmoveupw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovedownw_chk, libd___mempmovedownw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmoveupl_chk, libd___mempmoveupl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovedownl_chk, libd___mempmovedownl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memcpyq_chk, libd___memcpyq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempcpyq_chk, libd___mempcpyq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmoveq_chk, libd___memmoveq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmoveq_chk, libd___mempmoveq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memsetq_chk, libd___memsetq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempsetq_chk, libd___mempsetq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmoveupq_chk, libd___memmoveupq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovedownq_chk, libd___memmovedownq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmoveupq_chk, libd___mempmoveupq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovedownq_chk, libd___mempmovedownq_chk);

/* stdio */
DEFINE_PUBLIC_ALIAS(DOS$_fclose_nolock, libd_fclose);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fclose, libd_fclose);
DEFINE_PUBLIC_ALIAS(DOS$fclose, libd_fclose);
DEFINE_PUBLIC_ALIAS(DOS$fflush, libd_fflush);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fflush, libd_fflush);
DEFINE_PUBLIC_ALIAS(DOS$fflush_locked, libd_fflush);
DEFINE_PUBLIC_ALIAS(DOS$setbuf, libd_setbuf);
DEFINE_PUBLIC_ALIAS(DOS$setvbuf, libd_setvbuf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_setvbuf, libd_setvbuf);
DEFINE_PUBLIC_ALIAS(DOS$getc, libd_fgetc);
DEFINE_PUBLIC_ALIAS(DOS$fgetc, libd_fgetc);
DEFINE_PUBLIC_ALIAS(DOS$_IO_getc, libd_fgetc);
DEFINE_PUBLIC_ALIAS(DOS$getc_locked, libd_fgetc);
DEFINE_PUBLIC_ALIAS(DOS$putc, libd_fputc);
DEFINE_PUBLIC_ALIAS(DOS$fputc, libd_fputc);
DEFINE_PUBLIC_ALIAS(DOS$_IO_putc, libd_fputc);
DEFINE_PUBLIC_ALIAS(DOS$fputc_locked, libd_fputc);
DEFINE_PUBLIC_ALIAS(DOS$putc_locked, libd_fputc);
DEFINE_PUBLIC_ALIAS(DOS$_fputchar, libd_putchar);
DEFINE_PUBLIC_ALIAS(DOS$putchar_locked, libd_putchar);
DEFINE_PUBLIC_ALIAS(DOS$putchar, libd_putchar);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fgets, libd_fgets);
DEFINE_PUBLIC_ALIAS(DOS$fgets, libd_fgets);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fputs, libd_fputs);
DEFINE_PUBLIC_ALIAS(DOS$fputs, libd_fputs);
DEFINE_PUBLIC_ALIAS(DOS$_IO_puts, libd_puts);
DEFINE_PUBLIC_ALIAS(DOS$puts, libd_puts);
DEFINE_PUBLIC_ALIAS(DOS$ungetc, libd_ungetc);
DEFINE_PUBLIC_ALIAS(DOS$_IO_ungetc, libd_ungetc);
DEFINE_PUBLIC_ALIAS(DOS$fread, libd_fread);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fread, libd_fread);
DEFINE_PUBLIC_ALIAS(DOS$fwrite, libd_fwrite);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fwrite, libd_fwrite);
DEFINE_PUBLIC_ALIAS(DOS$fwrite_s, libd_fwrite);
DEFINE_PUBLIC_ALIAS(DOS$fseek, libd_fseek);
DEFINE_PUBLIC_ALIAS(DOS$ftell, libd_ftell);
DEFINE_PUBLIC_ALIAS(DOS$_IO_ftell, libd_ftell);
DEFINE_PUBLIC_ALIAS(DOS$rewind_unlocked, libd_rewind);
DEFINE_PUBLIC_ALIAS(DOS$rewind, libd_rewind);
DEFINE_PUBLIC_ALIAS(DOS$clearerr_unlocked, libd_clearerr);
DEFINE_PUBLIC_ALIAS(DOS$clearerr_locked, libd_clearerr);
DEFINE_PUBLIC_ALIAS(DOS$clearerr, libd_clearerr);
DEFINE_PUBLIC_ALIAS(DOS$_IO_feof, libd_feof);
DEFINE_PUBLIC_ALIAS(DOS$feof_unlocked, libd_feof);
DEFINE_PUBLIC_ALIAS(DOS$feof_locked, libd_feof);
DEFINE_PUBLIC_ALIAS(DOS$feof, libd_feof);
DEFINE_PUBLIC_ALIAS(DOS$_IO_ferror, libd_ferror);
DEFINE_PUBLIC_ALIAS(DOS$ferror_unlocked, libd_ferror);
DEFINE_PUBLIC_ALIAS(DOS$ferror_locked, libd_ferror);
DEFINE_PUBLIC_ALIAS(DOS$ferror, libd_ferror);
DEFINE_PUBLIC_ALIAS(DOS$_IO_perror, libd_perror);
DEFINE_PUBLIC_ALIAS(DOS$perror, libd_perror);
DEFINE_PUBLIC_ALIAS(DOS$fgetpos, libd_fgetpos);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fgetpos, libd_fgetpos);
DEFINE_PUBLIC_ALIAS(DOS$fsetpos, libd_fsetpos);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fsetpos, libd_fsetpos);
DEFINE_PUBLIC_ALIAS(DOS$_IO_vfprintf, libd_vfprintf);
DEFINE_PUBLIC_ALIAS(DOS$_vfprintf_p, libd_vfprintf);
DEFINE_PUBLIC_ALIAS(DOS$vfprintf, libd_vfprintf);
DEFINE_PUBLIC_ALIAS(DOS$vprintf, libd_vprintf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_vfscanf, libd_vfscanf);
DEFINE_PUBLIC_ALIAS(DOS$__vfscanf, libd_vfscanf);
DEFINE_PUBLIC_ALIAS(DOS$_doscan, libd_vfscanf);
DEFINE_PUBLIC_ALIAS(DOS$vfscanf, libd_vfscanf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_vscanf, libd_vscanf);
DEFINE_PUBLIC_ALIAS(DOS$vscanf, libd_vscanf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_gets, libd_gets);
DEFINE_PUBLIC_ALIAS(DOS$gets, libd_gets);
DEFINE_PUBLIC_ALIAS(DOS$__vsscanf, libd_vsscanf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_vsscanf, libd_vsscanf);
DEFINE_PUBLIC_ALIAS(DOS$vsscanf, libd_vsscanf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_vsprintf, libd_vsprintf);
DEFINE_PUBLIC_ALIAS(DOS$vsprintf, libd_vsprintf);
DEFINE_PUBLIC_ALIAS(DOS$__vsnprintf, libd_vsnprintf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_vsnprintf, libd_vsnprintf);
DEFINE_PUBLIC_ALIAS(DOS$vsnprintf, libd_vsnprintf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_vdprintf, libd_vdprintf);
DEFINE_PUBLIC_ALIAS(DOS$vdprintf, libd_vdprintf);
DEFINE_PUBLIC_ALIAS(DOS$tmpnam_r, libd_tmpnam_r);
DEFINE_PUBLIC_ALIAS(DOS$_IO_setbuffer, libd_setbuffer);
DEFINE_PUBLIC_ALIAS(DOS$setbuffer, libd_setbuffer);
DEFINE_PUBLIC_ALIAS(DOS$setlinebuf, libd_setlinebuf);
DEFINE_PUBLIC_ALIAS(DOS$_fflush_nolock, libd_fflush_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fflush_unlocked, libd_fflush_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fread_unlocked, libd_fread_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fread_nolock, libd_fread_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fwrite_unlocked, libd_fwrite_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fwrite_nolock, libd_fwrite_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fgetc_unlocked, libd_fgetc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$getc_unlocked, libd_fgetc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_getc_nolock, libd_fgetc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fgetc_nolock, libd_fgetc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$putc_unlocked, libd_fputc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fputc_unlocked, libd_fputc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_putc_nolock, libd_fputc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fputc_nolock, libd_fputc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vasnprintf, libd_vasnprintf);
DEFINE_PUBLIC_ALIAS(DOS$_tempnam, libd_tempnam);
DEFINE_PUBLIC_ALIAS(DOS$tempnam, libd_tempnam);
DEFINE_PUBLIC_ALIAS(DOS$_fdopen, libd_fdopen);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fdopen, libd_fdopen);
DEFINE_PUBLIC_ALIAS(DOS$fdopen, libd_fdopen);
DEFINE_PUBLIC_ALIAS(DOS$_fileno, libd_fileno);
DEFINE_PUBLIC_ALIAS(DOS$fileno_unlocked, libd_fileno);
DEFINE_PUBLIC_ALIAS(DOS$fileno_locked, libd_fileno);
DEFINE_PUBLIC_ALIAS(DOS$fileno, libd_fileno);
DEFINE_PUBLIC_ALIAS(DOS$fmemopen, libd_fmemopen);
DEFINE_PUBLIC_ALIAS(DOS$open_memstream, libd_open_memstream);
DEFINE_PUBLIC_ALIAS(DOS$__getdelim, libd_getdelim);
DEFINE_PUBLIC_ALIAS(DOS$_IO_getdelim, libd_getdelim);
DEFINE_PUBLIC_ALIAS(DOS$getdelim, libd_getdelim);
DEFINE_PUBLIC_ALIAS(DOS$__getline, libd_getline);
DEFINE_PUBLIC_ALIAS(DOS$_IO_getline, libd_getline);
DEFINE_PUBLIC_ALIAS(DOS$getline, libd_getline);
DEFINE_PUBLIC_ALIAS(DOS$putchar_unlocked, libd_putchar_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_lock_file, libd_flockfile);
DEFINE_PUBLIC_ALIAS(DOS$_IO_flockfile, libd_flockfile);
DEFINE_PUBLIC_ALIAS(DOS$__internal_flockfile, libd_flockfile);
DEFINE_PUBLIC_ALIAS(DOS$__flockfile, libd_flockfile);
DEFINE_PUBLIC_ALIAS(DOS$flockfile, libd_flockfile);
DEFINE_PUBLIC_ALIAS(DOS$_unlock_file, libd_funlockfile);
DEFINE_PUBLIC_ALIAS(DOS$_IO_funlockfile, libd_funlockfile);
DEFINE_PUBLIC_ALIAS(DOS$__internal_funlockfile, libd_funlockfile);
DEFINE_PUBLIC_ALIAS(DOS$__funlockfile, libd_funlockfile);
DEFINE_PUBLIC_ALIAS(DOS$funlockfile, libd_funlockfile);
DEFINE_PUBLIC_ALIAS(DOS$_IO_ftrylockfile, libd_ftrylockfile);
DEFINE_PUBLIC_ALIAS(DOS$__internal_ftrylockfile, libd_ftrylockfile);
DEFINE_PUBLIC_ALIAS(DOS$__ftrylockfile, libd_ftrylockfile);
DEFINE_PUBLIC_ALIAS(DOS$ftrylockfile, libd_ftrylockfile);
DEFINE_PUBLIC_ALIAS(DOS$__overflow, libd___overflow);
DEFINE_PUBLIC_ALIAS(DOS$_popen, libd_popen);
DEFINE_PUBLIC_ALIAS(DOS$_IO_popen, libd_popen);
DEFINE_PUBLIC_ALIAS(DOS$popen, libd_popen);
DEFINE_PUBLIC_ALIAS(DOS$_pclose, libd_pclose);
DEFINE_PUBLIC_ALIAS(DOS$pclose, libd_pclose);
DEFINE_PUBLIC_ALIAS(DOS$popenve, libd_popenve);
DEFINE_PUBLIC_ALIAS(DOS$_getw, libd_getw);
DEFINE_PUBLIC_ALIAS(DOS$getw, libd_getw);
DEFINE_PUBLIC_ALIAS(DOS$_putw, libd_putw);
DEFINE_PUBLIC_ALIAS(DOS$putw, libd_putw);
DEFINE_PUBLIC_ALIAS(DOS$fopencookie, libd_fopencookie);
DEFINE_PUBLIC_ALIAS(DOS$fgets_unlocked, libd_fgets_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fputs_unlocked, libd_fputs_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$obstack_vprintf, libd_obstack_vprintf);
DEFINE_PUBLIC_ALIAS(DOS$fseeko, libd_fseeko);
DEFINE_PUBLIC_ALIAS(DOS$ftello, libd_ftello);
DEFINE_PUBLIC_ALIAS(DOS$fseeko64, libd_fseeko64);
DEFINE_PUBLIC_ALIAS(DOS$__fseeko64, libd_fseeko64);
DEFINE_PUBLIC_ALIAS(DOS$fseek64, libd_fseeko64);
DEFINE_PUBLIC_ALIAS(DOS$_fseeki64, libd_fseeko64);
DEFINE_PUBLIC_ALIAS(DOS$ftello64, libd_ftello64);
DEFINE_PUBLIC_ALIAS(DOS$__ftello64, libd_ftello64);
DEFINE_PUBLIC_ALIAS(DOS$ftell64, libd_ftello64);
DEFINE_PUBLIC_ALIAS(DOS$_ftelli64, libd_ftello64);
DEFINE_PUBLIC_ALIAS(DOS$fgetpos64, libd_fgetpos64);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fgetpos64, libd_fgetpos64);
DEFINE_PUBLIC_ALIAS(DOS$fsetpos64, libd_fsetpos64);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fsetpos64, libd_fsetpos64);
DEFINE_PUBLIC_ALIAS(DOS$fopen_printer, libd_fopen_printer);
DEFINE_PUBLIC_ALIAS(DOS$_IO_vasprintf, libd_vasprintf);
DEFINE_PUBLIC_ALIAS(DOS$vasprintf, libd_vasprintf);
DEFINE_PUBLIC_ALIAS(DOS$fdreopen, libd_fdreopen);
DEFINE_PUBLIC_ALIAS(DOS$fdreopen_unlocked, libd_fdreopen_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fseek_unlocked, libd_fseek_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fseek_nolock, libd_fseek_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$ftell_unlocked, libd_ftell_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_ftell_nolock, libd_ftell_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fseeko_unlocked, libd_fseeko_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$ftello_unlocked, libd_ftello_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fgetpos_unlocked, libd_fgetpos_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fsetpos_unlocked, libd_fsetpos_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$getw_unlocked, libd_getw_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$putw_unlocked, libd_putw_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$setvbuf_unlocked, libd_setvbuf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$ungetc_unlocked, libd_ungetc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_ungetc_nolock, libd_ungetc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$getdelim_unlocked, libd_getdelim_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$getline_unlocked, libd_getline_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$rewind_unlocked, libd_rewind_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fisatty, libd_fisatty);
DEFINE_PUBLIC_ALIAS(DOS$frelease, libd_frelease);
DEFINE_PUBLIC_ALIAS(DOS$fftruncate, libd_fftruncate);
DEFINE_PUBLIC_ALIAS(DOS$fftruncate_unlocked, libd_fftruncate_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$puts_unlocked, libd_puts_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fseeko64_unlocked, libd_fseeko64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fseek64_unlocked, libd_fseeko64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fseeki64_nolock, libd_fseeko64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$ftello64_unlocked, libd_ftello64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$ftell64_unlocked, libd_ftello64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_ftelli64_nolock, libd_ftello64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fgetpos64_unlocked, libd_fgetpos64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fsetpos64_unlocked, libd_fsetpos64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fftruncate64, libd_fftruncate64);
DEFINE_PUBLIC_ALIAS(DOS$fftruncate64_unlocked, libd_fftruncate64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vfprintf_unlocked, libd_vfprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vprintf_s, libd_vprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vprintf_unlocked, libd_vprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vfscanf_unlocked, libd_vfscanf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vscanf_unlocked, libd_vscanf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fmtcheck, libd_fmtcheck);
DEFINE_PUBLIC_ALIAS(DOS$fgetln, libd_fgetln);
DEFINE_PUBLIC_ALIAS(DOS$funopen, libd_funopen);
DEFINE_PUBLIC_ALIAS(DOS$funopen2, libd_funopen2);
DEFINE_PUBLIC_ALIAS(DOS$funopen64, libd_funopen64);
DEFINE_PUBLIC_ALIAS(DOS$funopen2_64, libd_funopen2_64);
DEFINE_PUBLIC_ALIAS(DOS$__uflow, libd__filbuf);
DEFINE_PUBLIC_ALIAS(DOS$__underflow, libd__filbuf);
DEFINE_PUBLIC_ALIAS(DOS$__srget, libd__filbuf);
DEFINE_PUBLIC_ALIAS(DOS$_filbuf, libd__filbuf);
DEFINE_PUBLIC_ALIAS(DOS$__swbuf, libd__flsbuf);
DEFINE_PUBLIC_ALIAS(DOS$_flsbuf, libd__flsbuf);
DEFINE_PUBLIC_ALIAS(DOS$_setmaxstdio, libd__setmaxstdio);
DEFINE_PUBLIC_ALIAS(DOS$_set_printf_count_output, libd__set_printf_count_output);
DEFINE_PUBLIC_ALIAS(DOS$_set_output_format, libd__set_output_format);
DEFINE_PUBLIC_ALIAS(DOS$tmpnam_s, libd_tmpnam_s);
DEFINE_PUBLIC_ALIAS(DOS$clearerr_s, libd_clearerr_s);
DEFINE_PUBLIC_ALIAS(DOS$tmpfile_s, libd_tmpfile_s);
DEFINE_PUBLIC_ALIAS(DOS$fread_s, libd_fread_s);
DEFINE_PUBLIC_ALIAS(DOS$gets_s, libd_gets_s);
DEFINE_PUBLIC_ALIAS(DOS$_fread_nolock_s, libd__fread_nolock_s);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vfprintf, libd___stdio_common_vfprintf);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vfprintf_s, libd___stdio_common_vfprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vfprintf_p, libd___stdio_common_vfprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vsprintf, libd___stdio_common_vsprintf);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vsprintf_s, libd___stdio_common_vsprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vsnprintf_s, libd___stdio_common_vsnprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vsprintf_p, libd___stdio_common_vsprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vfscanf, libd___stdio_common_vfscanf);
DEFINE_PUBLIC_ALIAS(DOS$__stdio_common_vsscanf, libd___stdio_common_vsscanf);
DEFINE_PUBLIC_ALIAS(DOS$_vsnprintf_l, libd__vsnprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsprintf_s_l, libd__vsprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsprintf_p_l, libd__vsprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vscprintf_l, libd__vscprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vscprintf_p_l, libd__vscprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnprintf_c_l, libd__vsnprintf_c_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnprintf_s_l, libd__vsnprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfprintf_s_l, libd__vfprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfprintf_p_l, libd__vfprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfscanf_l, libd__vfscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfscanf_s_l, libd__vfscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnscanf_l, libd__vsnscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnscanf_s_l, libd__vsnscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vprintf_l, libd__vprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfprintf_l, libd__vfprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vscanf_l, libd__vscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsprintf_l, libd__vsprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfprintf_p, libd__vfprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vprintf_p, libd__vprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vsnprintf, libd__vsnprintf);
DEFINE_PUBLIC_ALIAS(DOS$_vsprintf_p, libd__vsprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vsnprintf_s, libd__vsnprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$_vscprintf, libd__vscprintf);
DEFINE_PUBLIC_ALIAS(DOS$_vscprintf_p, libd__vscprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vsnprintf_c, libd__vsnprintf_c);
DEFINE_PUBLIC_ALIAS(DOS$_vsscanf_l, libd__vsscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsscanf_s_l, libd__vsscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnscanf, libd__vsnscanf);
DEFINE_PUBLIC_ALIAS(DOS$_vsnscanf_s, libd__vsnscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$_vprintf_s_l, libd__vprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vprintf_p_l, libd__vprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vscanf_s_l, libd__vscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$vfprintf_s, libd_vfprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$vprintf_s, libd_vprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$vsprintf_s, libd_vsprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$vsnprintf_s, libd_vsnprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$vfscanf_s, libd_vfscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$vscanf_s, libd_vscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$vsscanf_s, libd_vsscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$_doprnt, libd__doprnt);

/* stdio_ext */
DEFINE_PUBLIC_ALIAS(DOS$__fbufsize, libd___fbufsize);
DEFINE_PUBLIC_ALIAS(DOS$__freading, libd___freading);
DEFINE_PUBLIC_ALIAS(DOS$__fwriting, libd___fwriting);
DEFINE_PUBLIC_ALIAS(DOS$__freadable, libd___freadable);
DEFINE_PUBLIC_ALIAS(DOS$__fwritable, libd___fwritable);
DEFINE_PUBLIC_ALIAS(DOS$__flbf, libd___flbf);
DEFINE_PUBLIC_ALIAS(DOS$fpurge, libd___fpurge);
DEFINE_PUBLIC_ALIAS(DOS$__fpurge, libd___fpurge);
DEFINE_PUBLIC_ALIAS(DOS$__fpending, libd___fpending);
DEFINE_PUBLIC_ALIAS(DOS$__fpending_unlocked, libd___fpending_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$__fsetlocking, libd___fsetlocking);
DEFINE_PUBLIC_ALIAS(DOS$__fseterr, libd___fseterr);
DEFINE_PUBLIC_ALIAS(DOS$__freadahead, libd___freadahead);
DEFINE_PUBLIC_ALIAS(DOS$__freadahead_unlocked, libd___freadahead_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$__freadptr, libd___freadptr);
DEFINE_PUBLIC_ALIAS(DOS$__freadptrinc, libd___freadptrinc);

/* stdlib */
#if __SIZEOF_INTMAX_T__ == __SIZEOF_INT__
DEFINE_PUBLIC_ALIAS(DOS$imaxabs, libd_abs);
#endif /* __SIZEOF_INTMAX_T__ == __SIZEOF_INT__ */
DEFINE_PUBLIC_ALIAS(DOS$abs, libd_abs);
#if __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS(DOS$imaxabs, libd_labs);
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS(DOS$labs, libd_labs);
#if __SIZEOF_INTMAX_T__ == __SIZEOF_INT__
DEFINE_PUBLIC_ALIAS(DOS$imaxdiv, libd_div);
#endif /* __SIZEOF_INTMAX_T__ == __SIZEOF_INT__ */
DEFINE_PUBLIC_ALIAS(DOS$div, libd_div);
#if __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS(DOS$imaxdiv, libd_ldiv);
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS(DOS$ldiv, libd_ldiv);
#if __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS(DOS$imaxabs, libd_llabs);
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS(DOS$llabs, libd_llabs);
DEFINE_PUBLIC_ALIAS(DOS$qabs, libd_llabs);
#if __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS(DOS$imaxdiv, libd_lldiv);
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS(DOS$lldiv, libd_lldiv);
DEFINE_PUBLIC_ALIAS(DOS$qdiv, libd_lldiv);
DEFINE_PUBLIC_ALIAS(DOS$mblen, libd_mblen);
DEFINE_PUBLIC_ALIAS(DOS$__libc_system, libd_system);
DEFINE_PUBLIC_ALIAS(DOS$system, libd_system);
DEFINE_PUBLIC_ALIAS(DOS$xexit, libd_exit);
DEFINE_PUBLIC_ALIAS(DOS$exit, libd_exit);
DEFINE_PUBLIC_ALIAS(DOS$_crt_atexit, libd_atexit);
DEFINE_PUBLIC_ALIAS(DOS$xatexit, libd_atexit);
DEFINE_PUBLIC_ALIAS(DOS$atexit, libd_atexit);
DEFINE_PUBLIC_ALIAS(DOS$quick_exit, libd_quick_exit);
DEFINE_PUBLIC_ALIAS(DOS$_crt_at_quick_exit, libd_at_quick_exit);
DEFINE_PUBLIC_ALIAS(DOS$at_quick_exit, libd_at_quick_exit);
DEFINE_PUBLIC_ALIAS(DOS$_exit, libd__Exit);
DEFINE_PUBLIC_ALIAS(DOS$_Exit, libd__Exit);
DEFINE_PUBLIC_ALIAS(DOS$__libc_malloc, libd_malloc);
DEFINE_PUBLIC_ALIAS(DOS$__malloc, libd_malloc);
DEFINE_PUBLIC_ALIAS(DOS$malloc, libd_malloc);
DEFINE_PUBLIC_ALIAS(DOS$__libc_calloc, libd_calloc);
DEFINE_PUBLIC_ALIAS(DOS$__calloc, libd_calloc);
DEFINE_PUBLIC_ALIAS(DOS$calloc, libd_calloc);
DEFINE_PUBLIC_ALIAS(DOS$__libc_realloc, libd_realloc);
DEFINE_PUBLIC_ALIAS(DOS$__realloc, libd_realloc);
DEFINE_PUBLIC_ALIAS(DOS$realloc, libd_realloc);
DEFINE_PUBLIC_ALIAS(DOS$cfree, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$__libc_free, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$__cfree, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$__free, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$_ZdaPv, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$_ZdlPv, libd_free);
#ifdef __LIBCCALL_CALLER_CLEANUP
DEFINE_PUBLIC_ALIAS(DOS$_ZdaPvRKSt9nothrow_t, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$_ZdlPvRKSt9nothrow_t, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$_ZdaPvSt11align_val_t, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$_ZdlPvSt11align_val_t, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$_ZdaPvmSt11align_val_t, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$_ZdlPvmSt11align_val_t, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$_ZdaPvSt11align_val_tRKSt9nothrow_t, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$_ZdlPvSt11align_val_tRKSt9nothrow_t, libd_free);
#endif /* __LIBCCALL_CALLER_CLEANUP */
DEFINE_PUBLIC_ALIAS(DOS$free, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$srand, libd_srand);
DEFINE_PUBLIC_ALIAS(DOS$atoi, libd_atoi);
DEFINE_PUBLIC_ALIAS(DOS$atol, libd_atol);
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS(DOS$strtoimax, libd_strtol);
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS(DOS$strtol, libd_strtol);
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS(DOS$strtoumax, libd_strtoul);
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS(DOS$strtoul, libd_strtoul);
DEFINE_PUBLIC_ALIAS(DOS$atoll, libd_atoll);
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS(DOS$strtoimax, libd_strtoll);
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS(DOS$strtoll, libd_strtoll);
DEFINE_PUBLIC_ALIAS(DOS$strtoq, libd_strtoll);
DEFINE_PUBLIC_ALIAS(DOS$__strtoq, libd_strtoll);
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS(DOS$strtoumax, libd_strtoull);
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS(DOS$strtoull, libd_strtoull);
DEFINE_PUBLIC_ALIAS(DOS$strtouq, libd_strtoull);
DEFINE_PUBLIC_ALIAS(DOS$__strtouq, libd_strtoull);
DEFINE_PUBLIC_ALIAS(DOS$atof, libd_atof);
DEFINE_PUBLIC_ALIAS(DOS$strtod, libd_strtod);
DEFINE_PUBLIC_ALIAS(DOS$__strtof, libd_strtof);
DEFINE_PUBLIC_ALIAS(DOS$strtof, libd_strtof);
DEFINE_PUBLIC_ALIAS(DOS$__strtold, libd_strtold);
DEFINE_PUBLIC_ALIAS(DOS$strtold, libd_strtold);
DEFINE_PUBLIC_ALIAS(DOS$strfromd, libd_strfromd);
DEFINE_PUBLIC_ALIAS(DOS$strfromf, libd_strfromf);
DEFINE_PUBLIC_ALIAS(DOS$strfroml, libd_strfroml);
DEFINE_PUBLIC_ALIAS(DOS$strtou32_r, libd_strtou32_r);
DEFINE_PUBLIC_ALIAS(DOS$strto32_r, libd_strto32_r);
DEFINE_PUBLIC_ALIAS(DOS$strtou64_r, libd_strtou64_r);
DEFINE_PUBLIC_ALIAS(DOS$strto64_r, libd_strto64_r);
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS(DOS$strtoumax, libd_strtou32);
#endif /* __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS(DOS$strtou32, libd_strtou32);
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS(DOS$strtoimax, libd_strto32);
#endif /* __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS(DOS$strto32, libd_strto32);
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS(DOS$strtoumax, libd_strtou64);
#endif /* __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS(DOS$_strtoui64, libd_strtou64);
DEFINE_PUBLIC_ALIAS(DOS$strtou64, libd_strtou64);
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS(DOS$strtoimax, libd_strto64);
#endif /* __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS(DOS$_strtoi64, libd_strto64);
DEFINE_PUBLIC_ALIAS(DOS$strto64, libd_strto64);
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS(DOS$strtoumax_l, libd_strtou32_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoumax_l, libd_strtou32_l);
#endif /* __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS(DOS$strtou32_l, libd_strtou32_l);
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS(DOS$strtoimax_l, libd_strto32_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoimax_l, libd_strto32_l);
#endif /* __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS(DOS$strto32_l, libd_strto32_l);
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS(DOS$strtoumax_l, libd_strtou64_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoumax_l, libd_strtou64_l);
#endif /* __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS(DOS$_strtoui64_l, libd_strtou64_l);
DEFINE_PUBLIC_ALIAS(DOS$strtou64_l, libd_strtou64_l);
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS(DOS$strtoimax_l, libd_strto64_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoimax_l, libd_strto64_l);
#endif /* __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS(DOS$_strtoi64_l, libd_strto64_l);
DEFINE_PUBLIC_ALIAS(DOS$strto64_l, libd_strto64_l);
DEFINE_PUBLIC_ALIAS(DOS$_gcvt, libd_gcvt);
DEFINE_PUBLIC_ALIAS(DOS$gcvt, libd_gcvt);
DEFINE_PUBLIC_ALIAS(DOS$rand_r, libd_rand_r);
DEFINE_PUBLIC_ALIAS(DOS$ecvt_r, libd_ecvt_r);
DEFINE_PUBLIC_ALIAS(DOS$fcvt_r, libd_fcvt_r);
DEFINE_PUBLIC_ALIAS(DOS$qgcvt, libd_qgcvt);
DEFINE_PUBLIC_ALIAS(DOS$qecvt_r, libd_qecvt_r);
DEFINE_PUBLIC_ALIAS(DOS$qfcvt_r, libd_qfcvt_r);
DEFINE_PUBLIC_ALIAS(DOS$qecvt, libd_qecvt);
DEFINE_PUBLIC_ALIAS(DOS$qfcvt, libd_qfcvt);
DEFINE_PUBLIC_ALIAS(DOS$getloadavg, libd_getloadavg);
DEFINE_PUBLIC_ALIAS(DOS$drand48_r, libd_drand48_r);
DEFINE_PUBLIC_ALIAS(DOS$erand48_r, libd_erand48_r);
DEFINE_PUBLIC_ALIAS(DOS$lrand48_r, libd_lrand48_r);
DEFINE_PUBLIC_ALIAS(DOS$nrand48_r, libd_nrand48_r);
DEFINE_PUBLIC_ALIAS(DOS$mrand48_r, libd_mrand48_r);
DEFINE_PUBLIC_ALIAS(DOS$jrand48_r, libd_jrand48_r);
DEFINE_PUBLIC_ALIAS(DOS$srand48_r, libd_srand48_r);
DEFINE_PUBLIC_ALIAS(DOS$seed48_r, libd_seed48_r);
DEFINE_PUBLIC_ALIAS(DOS$lcong48_r, libd_lcong48_r);
DEFINE_PUBLIC_ALIAS(DOS$__random_r, libd_random_r);
DEFINE_PUBLIC_ALIAS(DOS$random_r, libd_random_r);
DEFINE_PUBLIC_ALIAS(DOS$__srandom_r, libd_srandom_r);
DEFINE_PUBLIC_ALIAS(DOS$srandom_r, libd_srandom_r);
DEFINE_PUBLIC_ALIAS(DOS$__initstate_r, libd_initstate_r);
DEFINE_PUBLIC_ALIAS(DOS$initstate_r, libd_initstate_r);
DEFINE_PUBLIC_ALIAS(DOS$__setstate_r, libd_setstate_r);
DEFINE_PUBLIC_ALIAS(DOS$setstate_r, libd_setstate_r);
DEFINE_PUBLIC_ALIAS(DOS$mkstemps, libd_mkstemps);
DEFINE_PUBLIC_ALIAS(DOS$rpmatch, libd_rpmatch);
DEFINE_PUBLIC_ALIAS(DOS$mkstemps64, libd_mkstemps64);
DEFINE_PUBLIC_ALIAS(DOS$erand48, libd_erand48);
DEFINE_PUBLIC_ALIAS(DOS$nrand48, libd_nrand48);
DEFINE_PUBLIC_ALIAS(DOS$jrand48, libd_jrand48);
DEFINE_PUBLIC_ALIAS(DOS$srand48, libd_srand48);
DEFINE_PUBLIC_ALIAS(DOS$seed48, libd_seed48);
DEFINE_PUBLIC_ALIAS(DOS$lcong48, libd_lcong48);
DEFINE_PUBLIC_ALIAS(DOS$__srandom, libd_srandom);
DEFINE_PUBLIC_ALIAS(DOS$srandom, libd_srandom);
DEFINE_PUBLIC_ALIAS(DOS$__initstate, libd_initstate);
DEFINE_PUBLIC_ALIAS(DOS$initstate, libd_initstate);
DEFINE_PUBLIC_ALIAS(DOS$__setstate, libd_setstate);
DEFINE_PUBLIC_ALIAS(DOS$setstate, libd_setstate);
DEFINE_PUBLIC_ALIAS(DOS$l64a, libd_l64a);
DEFINE_PUBLIC_ALIAS(DOS$a64l, libd_a64l);
DEFINE_PUBLIC_ALIAS(DOS$_mktemp, libd_mktemp);
DEFINE_PUBLIC_ALIAS(DOS$__mktemp, libd_mktemp);
DEFINE_PUBLIC_ALIAS(DOS$mktemp, libd_mktemp);
DEFINE_PUBLIC_ALIAS(DOS$_ecvt, libd_ecvt);
DEFINE_PUBLIC_ALIAS(DOS$ecvt, libd_ecvt);
DEFINE_PUBLIC_ALIAS(DOS$_fcvt, libd_fcvt);
DEFINE_PUBLIC_ALIAS(DOS$fcvt, libd_fcvt);
DEFINE_PUBLIC_ALIAS(DOS$getsubopt, libd_getsubopt);
DEFINE_PUBLIC_ALIAS(DOS$mkstemp, libd_mkstemp);
DEFINE_PUBLIC_ALIAS(DOS$mkstemp64, libd_mkstemp64);
DEFINE_PUBLIC_ALIAS(DOS$mkdtemp, libd_mkdtemp);
DEFINE_PUBLIC_ALIAS(DOS$grantpt, libd_grantpt);
DEFINE_PUBLIC_ALIAS(DOS$unlockpt, libd_unlockpt);
DEFINE_PUBLIC_ALIAS(DOS$posix_openpt, libd_posix_openpt);
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___
DEFINE_PUBLIC_ALIAS(DOS$strtoimax_l, libd_strtol_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoimax_l, libd_strtol_l);
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___ */
DEFINE_PUBLIC_ALIAS(DOS$_strtol_l, libd_strtol_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtol_l, libd_strtol_l);
DEFINE_PUBLIC_ALIAS(DOS$strtol_l, libd_strtol_l);
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___
DEFINE_PUBLIC_ALIAS(DOS$strtoumax_l, libd_strtoul_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoumax_l, libd_strtoul_l);
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___ */
DEFINE_PUBLIC_ALIAS(DOS$_strtoul_l, libd_strtoul_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtoul_l, libd_strtoul_l);
DEFINE_PUBLIC_ALIAS(DOS$strtoul_l, libd_strtoul_l);
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___
DEFINE_PUBLIC_ALIAS(DOS$strtoimax_l, libd_strtoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoimax_l, libd_strtoll_l);
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___ */
DEFINE_PUBLIC_ALIAS(DOS$_strtoll_l, libd_strtoll_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtoll_l, libd_strtoll_l);
DEFINE_PUBLIC_ALIAS(DOS$strtoll_l, libd_strtoll_l);
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___
DEFINE_PUBLIC_ALIAS(DOS$strtoumax_l, libd_strtoull_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoumax_l, libd_strtoull_l);
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___ */
DEFINE_PUBLIC_ALIAS(DOS$_strtoull_l, libd_strtoull_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtoull_l, libd_strtoull_l);
DEFINE_PUBLIC_ALIAS(DOS$strtoull_l, libd_strtoull_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtod_l, libd_strtod_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtod_l, libd_strtod_l);
DEFINE_PUBLIC_ALIAS(DOS$strtod_l, libd_strtod_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtof_l, libd_strtof_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtof_l, libd_strtof_l);
DEFINE_PUBLIC_ALIAS(DOS$strtof_l, libd_strtof_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtold_l, libd_strtold_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtold_l, libd_strtold_l);
DEFINE_PUBLIC_ALIAS(DOS$strtold_l, libd_strtold_l);
DEFINE_PUBLIC_ALIAS(DOS$shexec, libd_shexec);
DEFINE_PUBLIC_ALIAS(DOS$lltostr, libd_lltostr);
DEFINE_PUBLIC_ALIAS(DOS$ulltostr, libd_ulltostr);
DEFINE_PUBLIC_ALIAS(DOS$reallocf, libd_reallocf);
DEFINE_PUBLIC_ALIAS(DOS$recallocarray, libd_recallocarray);
DEFINE_PUBLIC_ALIAS(DOS$freezero, libd_freezero);
DEFINE_PUBLIC_ALIAS(DOS$getbsize, libd_getbsize);
DEFINE_PUBLIC_ALIAS(DOS$daemonfd, libd_daemonfd);
DEFINE_PUBLIC_ALIAS(DOS$l64a_r, libd_l64a_r);
DEFINE_PUBLIC_ALIAS(DOS$setprogname, libd_setprogname);
DEFINE_PUBLIC_ALIAS(DOS$heapsort, libd_heapsort);
DEFINE_PUBLIC_ALIAS(DOS$mergesort, libd_mergesort);
DEFINE_PUBLIC_ALIAS(DOS$radixsort, libd_radixsort);
DEFINE_PUBLIC_ALIAS(DOS$sradixsort, libd_sradixsort);
DEFINE_PUBLIC_ALIAS(DOS$strtonum, libd_strtonum);
DEFINE_PUBLIC_ALIAS(DOS$mkostemp, libd_mkostemp);
DEFINE_PUBLIC_ALIAS(DOS$mkostemps, libd_mkostemps);
DEFINE_PUBLIC_ALIAS(DOS$mkostemp64, libd_mkostemp64);
DEFINE_PUBLIC_ALIAS(DOS$mkostemps64, libd_mkostemps64);
DEFINE_PUBLIC_ALIAS(DOS$devname, libd_devname);
DEFINE_PUBLIC_ALIAS(DOS$devname_r, libd_devname_r);
DEFINE_PUBLIC_ALIAS(DOS$humanize_number, libd_humanize_number);
DEFINE_PUBLIC_ALIAS(DOS$dehumanize_number, libd_dehumanize_number);
DEFINE_PUBLIC_ALIAS(DOS$reallocarr, libd_reallocarr);
DEFINE_PUBLIC_ALIAS(DOS$strsuftoll, libd_strsuftoll);
DEFINE_PUBLIC_ALIAS(DOS$strsuftollx, libd_strsuftollx);
DEFINE_PUBLIC_ALIAS(DOS$_set_doserrno, libd__set_doserrno);
DEFINE_PUBLIC_ALIAS(DOS$_set_purecall_handler, libd__set_purecall_handler);
DEFINE_PUBLIC_ALIAS(DOS$_set_invalid_parameter_handler, libd__set_invalid_parameter_handler);
DEFINE_PUBLIC_ALIAS(DOS$_get_pgmptr, libd__get_pgmptr);
DEFINE_PUBLIC_ALIAS(DOS$_set_fmode, libd__set_fmode);
DEFINE_PUBLIC_ALIAS(DOS$_get_fmode, libd__get_fmode);
DEFINE_PUBLIC_ALIAS(DOS$_set_abort_behavior, libd__set_abort_behavior);
#if __SIZEOF_INT__ != 8 && __SIZEOF_LONG__ != 8 && __SIZEOF_LONG_LONG__ != 8 && __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS(DOS$imaxabs, libd__abs64);
#endif /* __SIZEOF_INT__ != 8 && __SIZEOF_LONG__ != 8 && __SIZEOF_LONG_LONG__ != 8 && __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS(DOS$_abs64, libd__abs64);
DEFINE_PUBLIC_ALIAS(DOS$_atof_l, libd__atof_l);
DEFINE_PUBLIC_ALIAS(DOS$_atoi_l, libd__atoi_l);
DEFINE_PUBLIC_ALIAS(DOS$_atol_l, libd__atol_l);
DEFINE_PUBLIC_ALIAS(DOS$_atoll_l, libd__atoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_byteswap_ushort, libd__byteswap_ushort);
DEFINE_PUBLIC_ALIAS(DOS$_byteswap_ulong, libd__byteswap_ulong);
DEFINE_PUBLIC_ALIAS(DOS$_byteswap_uint64, libd__byteswap_uint64);
DEFINE_PUBLIC_ALIAS(DOS$_ltoa_s, libd__ltoa_s);
DEFINE_PUBLIC_ALIAS(DOS$_i64toa, libd__i64toa);
DEFINE_PUBLIC_ALIAS(DOS$_ui64toa, libd__ui64toa);
DEFINE_PUBLIC_ALIAS(DOS$_atoi64, libd__atoi64);
DEFINE_PUBLIC_ALIAS(DOS$_atoi64_l, libd__atoi64_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbstrlen, libd__mbstrlen);
DEFINE_PUBLIC_ALIAS(DOS$_mbstrnlen, libd__mbstrnlen);
DEFINE_PUBLIC_ALIAS(DOS$_mbstrlen_l, libd__mbstrlen_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbstrnlen_l, libd__mbstrnlen_l);
DEFINE_PUBLIC_ALIAS(DOS$_mblen_l, libd__mblen_l);
DEFINE_PUBLIC_ALIAS(DOS$_atoflt, libd__atoflt);
DEFINE_PUBLIC_ALIAS(DOS$_atoflt_l, libd__atoflt_l);
DEFINE_PUBLIC_ALIAS(DOS$_atodbl, libd__atodbl);
DEFINE_PUBLIC_ALIAS(DOS$_atodbl_l, libd__atodbl_l);
DEFINE_PUBLIC_ALIAS(DOS$_atoldbl, libd__atoldbl);
DEFINE_PUBLIC_ALIAS(DOS$_atoldbl_l, libd__atoldbl_l);
DEFINE_PUBLIC_ALIAS(DOS$_rotl, libd__rotl);
DEFINE_PUBLIC_ALIAS(DOS$_rotr, libd__rotr);
DEFINE_PUBLIC_ALIAS(DOS$_lrotl, libd__lrotl);
DEFINE_PUBLIC_ALIAS(DOS$_lrotr, libd__lrotr);
DEFINE_PUBLIC_ALIAS(DOS$_rotl64, libd__rotl64);
DEFINE_PUBLIC_ALIAS(DOS$_rotr64, libd__rotr64);
DEFINE_PUBLIC_ALIAS(DOS$_searchenv, libd__searchenv);
DEFINE_PUBLIC_ALIAS(DOS$_searchenv_s, libd__searchenv_s);
DEFINE_PUBLIC_ALIAS(DOS$_makepath, libd__makepath);
DEFINE_PUBLIC_ALIAS(DOS$_splitpath, libd__splitpath);
DEFINE_PUBLIC_ALIAS(DOS$_seterrormode, libd__seterrormode);
DEFINE_PUBLIC_ALIAS(DOS$_set_error_mode, libd__set_error_mode);
DEFINE_PUBLIC_ALIAS(DOS$_beep, libd__beep);
DEFINE_PUBLIC_ALIAS(DOS$__crtSleep, libd__sleep);
DEFINE_PUBLIC_ALIAS(DOS$_sleep, libd__sleep);
DEFINE_PUBLIC_ALIAS(DOS$_itoa, libd_itoa);
DEFINE_PUBLIC_ALIAS(DOS$itoa, libd_itoa);
DEFINE_PUBLIC_ALIAS(DOS$_ltoa, libd_ltoa);
DEFINE_PUBLIC_ALIAS(DOS$ltoa, libd_ltoa);
DEFINE_PUBLIC_ALIAS(DOS$_ultoa, libd_ultoa);
DEFINE_PUBLIC_ALIAS(DOS$ultoa, libd_ultoa);
DEFINE_PUBLIC_ALIAS(DOS$_onexit, libd_onexit);
DEFINE_PUBLIC_ALIAS(DOS$onexit, libd_onexit);
DEFINE_PUBLIC_ALIAS(DOS$_get_environ, libd__get_environ);

/* string */
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__memcpy_c, libd_memcpy);
DEFINE_PUBLIC_ALIAS(DOS$__memcpy_g, libd_memcpy);
DEFINE_PUBLIC_ALIAS(DOS$__memcpy_by4, libd_memcpy);
DEFINE_PUBLIC_ALIAS(DOS$__memcpy_by2, libd_memcpy);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$memcpy, libd_memcpy);
DEFINE_PUBLIC_ALIAS(DOS$memmove, libd_memmove);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__memset_cc, libd_memset);
DEFINE_PUBLIC_ALIAS(DOS$__memset_cg, libd_memset);
DEFINE_PUBLIC_ALIAS(DOS$__memset_ccn_by4, libd_memset);
DEFINE_PUBLIC_ALIAS(DOS$__memset_ccn_by2, libd_memset);
DEFINE_PUBLIC_ALIAS(DOS$__memset_gg, libd_memset);
DEFINE_PUBLIC_ALIAS(DOS$__memset_gcn_by4, libd_memset);
DEFINE_PUBLIC_ALIAS(DOS$__memset_gcn_by2, libd_memset);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$memset, libd_memset);
DEFINE_PUBLIC_ALIAS(DOS$__gcc_bcmp, libd_memcmp);
DEFINE_PUBLIC_ALIAS(DOS$memcmp, libd_memcmp);
DEFINE_PUBLIC_ALIAS(DOS$memchr, libd_memchr);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strlen_g, libd_strlen);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strlen, libd_strlen);
DEFINE_PUBLIC_ALIAS(DOS$index, libd_strchr);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strchr_g, libd_strchr);
DEFINE_PUBLIC_ALIAS(DOS$__strchr_c, libd_strchr);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strchr, libd_strchr);
DEFINE_PUBLIC_ALIAS(DOS$rindex, libd_strrchr);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strrchr_g, libd_strrchr);
DEFINE_PUBLIC_ALIAS(DOS$__strrchr_c, libd_strrchr);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strrchr, libd_strrchr);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strcmp_gg, libd_strcmp);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strcmp, libd_strcmp);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strncmp_g, libd_strncmp);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strncmp, libd_strncmp);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strstr_g, libd_strstr);
DEFINE_PUBLIC_ALIAS(DOS$__strstr_cg, libd_strstr);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strstr, libd_strstr);
DEFINE_PUBLIC_ALIAS(DOS$_mbscpy, libd_strcpy);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strcpy_g, libd_strcpy);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strcpy, libd_strcpy);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strncpy_byn, libd_strncpy);
DEFINE_PUBLIC_ALIAS(DOS$__strncpy_by4, libd_strncpy);
DEFINE_PUBLIC_ALIAS(DOS$__strncpy_by2, libd_strncpy);
DEFINE_PUBLIC_ALIAS(DOS$__strncpy_gg, libd_strncpy);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strncpy, libd_strncpy);
DEFINE_PUBLIC_ALIAS(DOS$_mbscat, libd_strcat);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strcat_g, libd_strcat);
DEFINE_PUBLIC_ALIAS(DOS$__strcat_c, libd_strcat);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strcat, libd_strcat);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strncat_g, libd_strncat);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strncat, libd_strncat);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strcspn_g, libd_strcspn);
DEFINE_PUBLIC_ALIAS(DOS$__strcspn_cg, libd_strcspn);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strcspn, libd_strcspn);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strspn_g, libd_strspn);
DEFINE_PUBLIC_ALIAS(DOS$__strspn_cg, libd_strspn);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strspn, libd_strspn);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strpbrk_g, libd_strpbrk);
DEFINE_PUBLIC_ALIAS(DOS$__strpbrk_cg, libd_strpbrk);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strpbrk, libd_strpbrk);
DEFINE_PUBLIC_ALIAS(DOS$strtok, libd_strtok);
DEFINE_PUBLIC_ALIAS(DOS$strcoll, libd_strcoll);
DEFINE_PUBLIC_ALIAS(DOS$strxfrm, libd_strxfrm);
DEFINE_PUBLIC_ALIAS(DOS$__strncnt, libd_strnlen);
DEFINE_PUBLIC_ALIAS(DOS$strnlen, libd_strnlen);
DEFINE_PUBLIC_ALIAS(DOS$__stpcpy, libd_stpcpy);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__stpcpy_g, libd_stpcpy);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$stpcpy, libd_stpcpy);
DEFINE_PUBLIC_ALIAS(DOS$__stpncpy, libd_stpncpy);
DEFINE_PUBLIC_ALIAS(DOS$stpncpy, libd_stpncpy);
DEFINE_PUBLIC_ALIAS(DOS$_strcoll_l, libd_strcoll_l);
DEFINE_PUBLIC_ALIAS(DOS$__strcoll_l, libd_strcoll_l);
DEFINE_PUBLIC_ALIAS(DOS$strcoll_l, libd_strcoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_strxfrm_l, libd_strxfrm_l);
DEFINE_PUBLIC_ALIAS(DOS$__strxfrm_l, libd_strxfrm_l);
DEFINE_PUBLIC_ALIAS(DOS$strxfrm_l, libd_strxfrm_l);
DEFINE_PUBLIC_ALIAS(DOS$__strndup, libd_strndup);
DEFINE_PUBLIC_ALIAS(DOS$strndup, libd_strndup);
DEFINE_PUBLIC_ALIAS(DOS$_strdup, libd_strdup);
DEFINE_PUBLIC_ALIAS(DOS$_mbsdup, libd_strdup);
DEFINE_PUBLIC_ALIAS(DOS$__strdup, libd_strdup);
DEFINE_PUBLIC_ALIAS(DOS$strdup, libd_strdup);
DEFINE_PUBLIC_ALIAS(DOS$strtok_s, libd_strtok_r);
DEFINE_PUBLIC_ALIAS(DOS$__strtok_r, libd_strtok_r);
DEFINE_PUBLIC_ALIAS(DOS$strtok_r, libd_strtok_r);
DEFINE_PUBLIC_ALIAS(DOS$memrchr, libd_memrchr);
DEFINE_PUBLIC_ALIAS(DOS$memmem, libd_memmem);
DEFINE_PUBLIC_ALIAS(DOS$__strcasestr, libd_strcasestr);
DEFINE_PUBLIC_ALIAS(DOS$strcasestr, libd_strcasestr);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__strchrnul_g, libd_strchrnul);
DEFINE_PUBLIC_ALIAS(DOS$__strchrnul_c, libd_strchrnul);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$strchrnul, libd_strchrnul);
DEFINE_PUBLIC_ALIAS(DOS$rawmemchr, libd_rawmemchr);
DEFINE_PUBLIC_ALIAS(DOS$__basename, libd_basename);
DEFINE_PUBLIC_ALIAS(DOS$lbasename, libd_basename);
#ifdef _WIN32
DEFINE_PUBLIC_ALIAS(DOS$dos_lbasename, libd_basename);
#endif /* _WIN32 */
#ifndef _WIN32
DEFINE_PUBLIC_ALIAS(DOS$unix_lbasename, libd_basename);
#endif /* !_WIN32 */
DEFINE_PUBLIC_ALIAS(DOS$basename, libd_basename);
DEFINE_PUBLIC_ALIAS(DOS$__strverscmp, libd_strverscmp);
DEFINE_PUBLIC_ALIAS(DOS$strverscmp, libd_strverscmp);
#if defined(__i386__) && !defined(__x86_64__)
DEFINE_PUBLIC_ALIAS(DOS$__mempcpy_byn, libd_mempcpy);
DEFINE_PUBLIC_ALIAS(DOS$__mempcpy_by4, libd_mempcpy);
DEFINE_PUBLIC_ALIAS(DOS$__mempcpy_by2, libd_mempcpy);
#endif /* __i386__ && !__x86_64__ */
DEFINE_PUBLIC_ALIAS(DOS$mempcpy, libd_mempcpy);
DEFINE_PUBLIC_ALIAS(DOS$strfry, libd_strfry);
DEFINE_PUBLIC_ALIAS(DOS$memfrob, libd_memfrob);
DEFINE_PUBLIC_ALIAS(DOS$_stricmp_l, libd_strcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$__strcasecmp_l, libd_strcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$strcasecmp_l, libd_strcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_strnicmp_l, libd_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_strncmpi_l, libd_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$__strncasecmp_l, libd_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$strncasecmp_l, libd_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$__strsep_g, libd_strsep);
DEFINE_PUBLIC_ALIAS(DOS$__strsep, libd_strsep);
DEFINE_PUBLIC_ALIAS(DOS$strsep, libd_strsep);
DEFINE_PUBLIC_ALIAS(DOS$bcopy, libd_bcopy);
DEFINE_PUBLIC_ALIAS(DOS$__bzero, libd_bzero);
DEFINE_PUBLIC_ALIAS(DOS$explicit_bzero, libd_bzero);
DEFINE_PUBLIC_ALIAS(DOS$bzero, libd_bzero);
DEFINE_PUBLIC_ALIAS(DOS$bzerow, libd_bzerow);
DEFINE_PUBLIC_ALIAS(DOS$bzerol, libd_bzerol);
#ifndef LIBC_ARCH_HAVE_BCMPW
DEFINE_PUBLIC_ALIAS(DOS$bcmpw, libd_bcmpw);
#endif /* !LIBC_ARCH_HAVE_BCMPW */
#ifndef LIBC_ARCH_HAVE_BCMPL
DEFINE_PUBLIC_ALIAS(DOS$bcmpl, libd_bcmpl);
#endif /* !LIBC_ARCH_HAVE_BCMPL */
DEFINE_PUBLIC_ALIAS(DOS$bzeroq, libd_bzeroq);
#ifndef LIBC_ARCH_HAVE_BCMPQ
DEFINE_PUBLIC_ALIAS(DOS$bcmpq, libd_bcmpq);
#endif /* !LIBC_ARCH_HAVE_BCMPQ */
DEFINE_PUBLIC_ALIAS(DOS$bzeroc, libd_bzeroc);
#ifndef LIBC_ARCH_HAVE_BCMPC
DEFINE_PUBLIC_ALIAS(DOS$bcmpc, libd_bcmpc);
#endif /* !LIBC_ARCH_HAVE_BCMPC */
#ifndef LIBC_ARCH_HAVE_BCMP
DEFINE_PUBLIC_ALIAS(DOS$__memcmpeq, libd_bcmp);
DEFINE_PUBLIC_ALIAS(DOS$bcmp, libd_bcmp);
#endif /* !LIBC_ARCH_HAVE_BCMP */
DEFINE_PUBLIC_ALIAS(DOS$_stricmp, libd_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$_strcmpi, libd_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$stricmp, libd_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$strcmpi, libd_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$__strcasecmp, libd_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$strcasecmp, libd_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$_strnicmp, libd_strncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$_strncmpi, libd_strncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$strnicmp, libd_strncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$strncmpi, libd_strncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$__strncasecmp, libd_strncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$strncasecmp, libd_strncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$__ffs, libd_ffs);
DEFINE_PUBLIC_ALIAS(DOS$ffs, libd_ffs);
DEFINE_PUBLIC_ALIAS(DOS$ffsl, libd_ffsl);
DEFINE_PUBLIC_ALIAS(DOS$ffsll, libd_ffsll);
DEFINE_PUBLIC_ALIAS(DOS$strlcat, libd_strlcat);
DEFINE_PUBLIC_ALIAS(DOS$strlcpy, libd_strlcpy);
DEFINE_PUBLIC_ALIAS(DOS$_memccpy, libd_memccpy);
DEFINE_PUBLIC_ALIAS(DOS$__memccpy, libd_memccpy);
DEFINE_PUBLIC_ALIAS(DOS$memccpy, libd_memccpy);
DEFINE_PUBLIC_ALIAS(DOS$wmemcpy, libd_memcpyw);
DEFINE_PUBLIC_ALIAS(DOS$memcpyw, libd_memcpyw);
DEFINE_PUBLIC_ALIAS(DOS$wmempcpy, libd_mempcpyw);
DEFINE_PUBLIC_ALIAS(DOS$mempcpyw, libd_mempcpyw);
DEFINE_PUBLIC_ALIAS(DOS$memcpyl, libd_memcpyl);
DEFINE_PUBLIC_ALIAS(DOS$mempcpyl, libd_mempcpyl);
DEFINE_PUBLIC_ALIAS(DOS$wmemmove, libd_memmovew);
DEFINE_PUBLIC_ALIAS(DOS$memmovew, libd_memmovew);
DEFINE_PUBLIC_ALIAS(DOS$wmempmove, libd_mempmovew);
DEFINE_PUBLIC_ALIAS(DOS$mempmovew, libd_mempmovew);
DEFINE_PUBLIC_ALIAS(DOS$memmovel, libd_memmovel);
DEFINE_PUBLIC_ALIAS(DOS$mempmovel, libd_mempmovel);
DEFINE_PUBLIC_ALIAS(DOS$memmoveupw, libd_memmoveupw);
DEFINE_PUBLIC_ALIAS(DOS$memmovedownw, libd_memmovedownw);
DEFINE_PUBLIC_ALIAS(DOS$mempmoveupw, libd_mempmoveupw);
DEFINE_PUBLIC_ALIAS(DOS$mempmovedownw, libd_mempmovedownw);
DEFINE_PUBLIC_ALIAS(DOS$memmoveupl, libd_memmoveupl);
DEFINE_PUBLIC_ALIAS(DOS$memmovedownl, libd_memmovedownl);
DEFINE_PUBLIC_ALIAS(DOS$mempmoveupl, libd_mempmoveupl);
DEFINE_PUBLIC_ALIAS(DOS$mempmovedownl, libd_mempmovedownl);
DEFINE_PUBLIC_ALIAS(DOS$wmemset, libd_memsetw);
DEFINE_PUBLIC_ALIAS(DOS$memsetw, libd_memsetw);
DEFINE_PUBLIC_ALIAS(DOS$wmempset, libd_mempsetw);
DEFINE_PUBLIC_ALIAS(DOS$mempsetw, libd_mempsetw);
DEFINE_PUBLIC_ALIAS(DOS$memsetl, libd_memsetl);
DEFINE_PUBLIC_ALIAS(DOS$mempsetl, libd_mempsetl);
DEFINE_PUBLIC_ALIAS(DOS$wmemcmp, libd_memcmpw);
DEFINE_PUBLIC_ALIAS(DOS$memcmpw, libd_memcmpw);
DEFINE_PUBLIC_ALIAS(DOS$memcmpl, libd_memcmpl);
DEFINE_PUBLIC_ALIAS(DOS$wmemchr, libd_memchrw);
DEFINE_PUBLIC_ALIAS(DOS$memchrw, libd_memchrw);
DEFINE_PUBLIC_ALIAS(DOS$memchrl, libd_memchrl);
DEFINE_PUBLIC_ALIAS(DOS$memrchrw, libd_memrchrw);
DEFINE_PUBLIC_ALIAS(DOS$memrchrl, libd_memrchrl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemchrw, libd_rawmemchrw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemchrl, libd_rawmemchrl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrchrw, libd_rawmemrchrw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrchrl, libd_rawmemrchrl);
DEFINE_PUBLIC_ALIAS(DOS$memendw, libd_memendw);
DEFINE_PUBLIC_ALIAS(DOS$memendl, libd_memendl);
DEFINE_PUBLIC_ALIAS(DOS$memrendw, libd_memrendw);
DEFINE_PUBLIC_ALIAS(DOS$memrendl, libd_memrendl);
DEFINE_PUBLIC_ALIAS(DOS$memlenw, libd_memlenw);
DEFINE_PUBLIC_ALIAS(DOS$memlenl, libd_memlenl);
DEFINE_PUBLIC_ALIAS(DOS$memrlenw, libd_memrlenw);
DEFINE_PUBLIC_ALIAS(DOS$memrlenl, libd_memrlenl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemlenw, libd_rawmemlenw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemlenl, libd_rawmemlenl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrlenw, libd_rawmemrlenw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrlenl, libd_rawmemrlenl);
DEFINE_PUBLIC_ALIAS(DOS$memcpyq, libd_memcpyq);
DEFINE_PUBLIC_ALIAS(DOS$mempcpyq, libd_mempcpyq);
DEFINE_PUBLIC_ALIAS(DOS$memmoveq, libd_memmoveq);
DEFINE_PUBLIC_ALIAS(DOS$mempmoveq, libd_mempmoveq);
DEFINE_PUBLIC_ALIAS(DOS$memmoveupq, libd_memmoveupq);
DEFINE_PUBLIC_ALIAS(DOS$memmovedownq, libd_memmovedownq);
DEFINE_PUBLIC_ALIAS(DOS$mempmoveupq, libd_mempmoveupq);
DEFINE_PUBLIC_ALIAS(DOS$mempmovedownq, libd_mempmovedownq);
DEFINE_PUBLIC_ALIAS(DOS$memsetq, libd_memsetq);
DEFINE_PUBLIC_ALIAS(DOS$mempsetq, libd_mempsetq);
DEFINE_PUBLIC_ALIAS(DOS$memcmpq, libd_memcmpq);
DEFINE_PUBLIC_ALIAS(DOS$memchrq, libd_memchrq);
DEFINE_PUBLIC_ALIAS(DOS$memrchrq, libd_memrchrq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemchrq, libd_rawmemchrq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrchrq, libd_rawmemrchrq);
DEFINE_PUBLIC_ALIAS(DOS$memendq, libd_memendq);
DEFINE_PUBLIC_ALIAS(DOS$memrendq, libd_memrendq);
DEFINE_PUBLIC_ALIAS(DOS$memlenq, libd_memlenq);
DEFINE_PUBLIC_ALIAS(DOS$memrlenq, libd_memrlenq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemlenq, libd_rawmemlenq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrlenq, libd_rawmemrlenq);
DEFINE_PUBLIC_ALIAS(DOS$memxchr, libd_memxchr);
DEFINE_PUBLIC_ALIAS(DOS$memrxchr, libd_memrxchr);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxchr, libd_rawmemxchr);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxchr, libd_rawmemrxchr);
DEFINE_PUBLIC_ALIAS(DOS$memxend, libd_memxend);
DEFINE_PUBLIC_ALIAS(DOS$memrxend, libd_memrxend);
DEFINE_PUBLIC_ALIAS(DOS$memxlen, libd_memxlen);
DEFINE_PUBLIC_ALIAS(DOS$memrxlen, libd_memrxlen);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxlen, libd_rawmemxlen);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxlen, libd_rawmemrxlen);
DEFINE_PUBLIC_ALIAS(DOS$memxchrw, libd_memxchrw);
DEFINE_PUBLIC_ALIAS(DOS$memxchrl, libd_memxchrl);
DEFINE_PUBLIC_ALIAS(DOS$memrxchrw, libd_memrxchrw);
DEFINE_PUBLIC_ALIAS(DOS$memrxchrl, libd_memrxchrl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxchrw, libd_rawmemxchrw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxchrl, libd_rawmemxchrl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxchrw, libd_rawmemrxchrw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxchrl, libd_rawmemrxchrl);
DEFINE_PUBLIC_ALIAS(DOS$memxendw, libd_memxendw);
DEFINE_PUBLIC_ALIAS(DOS$memxendl, libd_memxendl);
DEFINE_PUBLIC_ALIAS(DOS$memrxendw, libd_memrxendw);
DEFINE_PUBLIC_ALIAS(DOS$memrxendl, libd_memrxendl);
DEFINE_PUBLIC_ALIAS(DOS$memxlenw, libd_memxlenw);
DEFINE_PUBLIC_ALIAS(DOS$memxlenl, libd_memxlenl);
DEFINE_PUBLIC_ALIAS(DOS$memrxlenw, libd_memrxlenw);
DEFINE_PUBLIC_ALIAS(DOS$memrxlenl, libd_memrxlenl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxlenw, libd_rawmemxlenw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxlenl, libd_rawmemxlenl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxlenw, libd_rawmemrxlenw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxlenl, libd_rawmemrxlenl);
DEFINE_PUBLIC_ALIAS(DOS$memxchrq, libd_memxchrq);
DEFINE_PUBLIC_ALIAS(DOS$memrxchrq, libd_memrxchrq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxchrq, libd_rawmemxchrq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxchrq, libd_rawmemrxchrq);
DEFINE_PUBLIC_ALIAS(DOS$memxendq, libd_memxendq);
DEFINE_PUBLIC_ALIAS(DOS$memrxendq, libd_memrxendq);
DEFINE_PUBLIC_ALIAS(DOS$memxlenq, libd_memxlenq);
DEFINE_PUBLIC_ALIAS(DOS$memrxlenq, libd_memrxlenq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxlenq, libd_rawmemxlenq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxlenq, libd_rawmemrxlenq);
DEFINE_PUBLIC_ALIAS(DOS$memmoveup, libd_memmoveup);
DEFINE_PUBLIC_ALIAS(DOS$memmovedown, libd_memmovedown);
DEFINE_PUBLIC_ALIAS(DOS$memcmpc, libd_memcmpc);
DEFINE_PUBLIC_ALIAS(DOS$memcpyc, libd_memcpyc);
DEFINE_PUBLIC_ALIAS(DOS$mempcpyc, libd_mempcpyc);
DEFINE_PUBLIC_ALIAS(DOS$memmovec, libd_memmovec);
DEFINE_PUBLIC_ALIAS(DOS$mempmovec, libd_mempmovec);
DEFINE_PUBLIC_ALIAS(DOS$memmoveupc, libd_memmoveupc);
DEFINE_PUBLIC_ALIAS(DOS$mempmoveupc, libd_mempmoveupc);
DEFINE_PUBLIC_ALIAS(DOS$memmovedownc, libd_memmovedownc);
DEFINE_PUBLIC_ALIAS(DOS$mempmovedownc, libd_mempmovedownc);
DEFINE_PUBLIC_ALIAS(DOS$strend, libd_strend);
DEFINE_PUBLIC_ALIAS(DOS$strnend, libd_strnend);
DEFINE_PUBLIC_ALIAS(DOS$strnchr, libd_strnchr);
DEFINE_PUBLIC_ALIAS(DOS$strnrchr, libd_strnrchr);
DEFINE_PUBLIC_ALIAS(DOS$strrchrnul, libd_strrchrnul);
DEFINE_PUBLIC_ALIAS(DOS$strnchrnul, libd_strnchrnul);
DEFINE_PUBLIC_ALIAS(DOS$strnrchrnul, libd_strnrchrnul);
DEFINE_PUBLIC_ALIAS(DOS$stroff, libd_stroff);
DEFINE_PUBLIC_ALIAS(DOS$strroff, libd_strroff);
DEFINE_PUBLIC_ALIAS(DOS$strnoff, libd_strnoff);
DEFINE_PUBLIC_ALIAS(DOS$strnroff, libd_strnroff);
DEFINE_PUBLIC_ALIAS(DOS$mempset, libd_mempset);
DEFINE_PUBLIC_ALIAS(DOS$mempmove, libd_mempmove);
DEFINE_PUBLIC_ALIAS(DOS$mempmoveup, libd_mempmoveup);
DEFINE_PUBLIC_ALIAS(DOS$mempmovedown, libd_mempmovedown);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrchr, libd_rawmemrchr);
DEFINE_PUBLIC_ALIAS(DOS$memend, libd_memend);
DEFINE_PUBLIC_ALIAS(DOS$memrend, libd_memrend);
DEFINE_PUBLIC_ALIAS(DOS$memlen, libd_memlen);
DEFINE_PUBLIC_ALIAS(DOS$memrlen, libd_memrlen);
DEFINE_PUBLIC_ALIAS(DOS$rawmemlen, libd_rawmemlen);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrlen, libd_rawmemrlen);
DEFINE_PUBLIC_ALIAS(DOS$memrmem, libd_memrmem);
DEFINE_PUBLIC_ALIAS(DOS$mempatw, libd_mempatw);
DEFINE_PUBLIC_ALIAS(DOS$mempatl, libd_mempatl);
DEFINE_PUBLIC_ALIAS(DOS$mempatq, libd_mempatq);
DEFINE_PUBLIC_ALIAS(DOS$memicmp, libd_memcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$_memicmp, libd_memcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$memcasecmp, libd_memcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$memcasemem, libd_memcasemem);
DEFINE_PUBLIC_ALIAS(DOS$_memicmp_l, libd_memcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$memcasecmp_l, libd_memcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$memcasemem_l, libd_memcasemem_l);
DEFINE_PUBLIC_ALIAS(DOS$strcasestr_l, libd_strcasestr_l);
DEFINE_PUBLIC_ALIAS(DOS$vstrdupf, libd_vstrdupf);
DEFINE_PUBLIC_ALIAS(DOS$wildstrcmp, libd_wildstrcmp);
DEFINE_PUBLIC_ALIAS(DOS$wildstrcasecmp, libd_wildstrcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_strcmp, libd_fuzzy_strcmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_strncmp, libd_fuzzy_strncmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_strcasecmp, libd_fuzzy_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_strncasecmp, libd_fuzzy_strncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_memcmp, libd_fuzzy_memcmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_memcasecmp, libd_fuzzy_memcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_strcasecmp_l, libd_fuzzy_strcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_strncasecmp_l, libd_fuzzy_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$wildstrcasecmp_l, libd_wildstrcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_memcasecmp_l, libd_fuzzy_memcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wmemcmp, libd_fuzzy_memcmpw);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_memcmpw, libd_fuzzy_memcmpw);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wmemcmp, libd_fuzzy_memcmpl);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_memcmpl, libd_fuzzy_memcmpl);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_memcmpq, libd_fuzzy_memcmpq);
DEFINE_PUBLIC_ALIAS(DOS$_strncoll, libd_strncoll);
DEFINE_PUBLIC_ALIAS(DOS$strncoll, libd_strncoll);
DEFINE_PUBLIC_ALIAS(DOS$_stricoll, libd_strcasecoll);
DEFINE_PUBLIC_ALIAS(DOS$strcasecoll, libd_strcasecoll);
DEFINE_PUBLIC_ALIAS(DOS$_strnicoll, libd_strncasecoll);
DEFINE_PUBLIC_ALIAS(DOS$strncasecoll, libd_strncasecoll);
DEFINE_PUBLIC_ALIAS(DOS$strnrev, libd_strnrev);
DEFINE_PUBLIC_ALIAS(DOS$strnlwr, libd_strnlwr);
DEFINE_PUBLIC_ALIAS(DOS$strnupr, libd_strnupr);
DEFINE_PUBLIC_ALIAS(DOS$memrev, libd_memrev);
DEFINE_PUBLIC_ALIAS(DOS$_strncoll_l, libd_strncoll_l);
DEFINE_PUBLIC_ALIAS(DOS$strncoll_l, libd_strncoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_stricoll_l, libd_strcasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$strcasecoll_l, libd_strcasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_strnicoll_l, libd_strncasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$strncasecoll_l, libd_strncasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_strlwr_l, libd_strlwr_l);
DEFINE_PUBLIC_ALIAS(DOS$strlwr_l, libd_strlwr_l);
DEFINE_PUBLIC_ALIAS(DOS$_strupr_l, libd_strupr_l);
DEFINE_PUBLIC_ALIAS(DOS$strupr_l, libd_strupr_l);
DEFINE_PUBLIC_ALIAS(DOS$strnlwr_l, libd_strnlwr_l);
DEFINE_PUBLIC_ALIAS(DOS$strnupr_l, libd_strnupr_l);
DEFINE_PUBLIC_ALIAS(DOS$memrevw, libd_memrevw);
DEFINE_PUBLIC_ALIAS(DOS$memrevl, libd_memrevl);
DEFINE_PUBLIC_ALIAS(DOS$memrevq, libd_memrevq);
DEFINE_PUBLIC_ALIAS(DOS$strcmpz, libd_strcmpz);
DEFINE_PUBLIC_ALIAS(DOS$strstartcmp, libd_strstartcmp);
DEFINE_PUBLIC_ALIAS(DOS$strstartcmpz, libd_strstartcmpz);
DEFINE_PUBLIC_ALIAS(DOS$bitcpy, libd_bitcpy);
DEFINE_PUBLIC_ALIAS(DOS$strrstr, libd_strrstr);
DEFINE_PUBLIC_ALIAS(DOS$strlstrip, libd_strlstrip);
DEFINE_PUBLIC_ALIAS(DOS$strrstrip, libd_strrstrip);
DEFINE_PUBLIC_ALIAS(DOS$strstrip, libd_strstrip);
DEFINE_PUBLIC_ALIAS(DOS$_strlwr, libd_strlwr);
DEFINE_PUBLIC_ALIAS(DOS$strlwr, libd_strlwr);
DEFINE_PUBLIC_ALIAS(DOS$_strupr, libd_strupr);
DEFINE_PUBLIC_ALIAS(DOS$strupr, libd_strupr);
DEFINE_PUBLIC_ALIAS(DOS$_strset, libd_strset);
DEFINE_PUBLIC_ALIAS(DOS$strset, libd_strset);
DEFINE_PUBLIC_ALIAS(DOS$_strnset, libd_strnset);
DEFINE_PUBLIC_ALIAS(DOS$strnset, libd_strnset);
DEFINE_PUBLIC_ALIAS(DOS$_strrev, libd_strrev);
DEFINE_PUBLIC_ALIAS(DOS$strrev, libd_strrev);
DEFINE_PUBLIC_ALIAS(DOS$_strset_s, libd__strset_s);
DEFINE_PUBLIC_ALIAS(DOS$memcpy_s, libd_memcpy_s);
DEFINE_PUBLIC_ALIAS(DOS$memmove_s, libd_memmove_s);
DEFINE_PUBLIC_ALIAS(DOS$strcpy_s, libd_strcpy_s);
DEFINE_PUBLIC_ALIAS(DOS$strcat_s, libd_strcat_s);
DEFINE_PUBLIC_ALIAS(DOS$strncat_s, libd_strncat_s);
DEFINE_PUBLIC_ALIAS(DOS$strncpy_s, libd_strncpy_s);
DEFINE_PUBLIC_ALIAS(DOS$_strerror, libd__strerror);
DEFINE_PUBLIC_ALIAS(DOS$_strerror_s, libd__strerror_s);
DEFINE_PUBLIC_ALIAS(DOS$_strlwr_s, libd__strlwr_s);
DEFINE_PUBLIC_ALIAS(DOS$_strupr_s, libd__strupr_s);
DEFINE_PUBLIC_ALIAS(DOS$_strlwr_s_l, libd__strlwr_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_strupr_s_l, libd__strupr_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_strnset_s, libd__strnset_s);
DEFINE_PUBLIC_ALIAS(DOS$strnstr, libd_strnstr);
DEFINE_PUBLIC_ALIAS(DOS$strmode, libd_strmode);
DEFINE_PUBLIC_ALIAS(DOS$timingsafe_bcmp, libd_timingsafe_memcmp);
DEFINE_PUBLIC_ALIAS(DOS$timingsafe_memcmp, libd_timingsafe_memcmp);
DEFINE_PUBLIC_ALIAS(DOS$strtosigno, libd_strtosigno);
DEFINE_PUBLIC_ALIAS(DOS$stresep, libd_stresep);
DEFINE_PUBLIC_ALIAS(DOS$consttime_memequal, libd_consttime_memequal);
DEFINE_PUBLIC_ALIAS(DOS$uucopy, libd_uucopy);
DEFINE_PUBLIC_ALIAS(DOS$uucopystr, libd_uucopystr);
DEFINE_PUBLIC_ALIAS(DOS$__strtok_r_1c, libd___strtok_r_1c);
DEFINE_PUBLIC_ALIAS(DOS$__strsep_1c, libd___strsep_1c);
DEFINE_PUBLIC_ALIAS(DOS$__strsep_2c, libd___strsep_2c);
DEFINE_PUBLIC_ALIAS(DOS$__strsep_3c, libd___strsep_3c);
DEFINE_PUBLIC_ALIAS(DOS$__strcspn_c1, libd___strcspn_c1);
DEFINE_PUBLIC_ALIAS(DOS$__strcspn_c2, libd___strcspn_c2);
DEFINE_PUBLIC_ALIAS(DOS$__strcspn_c3, libd___strcspn_c3);
DEFINE_PUBLIC_ALIAS(DOS$__strspn_c1, libd___strspn_c1);
DEFINE_PUBLIC_ALIAS(DOS$__strspn_c2, libd___strspn_c2);
DEFINE_PUBLIC_ALIAS(DOS$__strspn_c3, libd___strspn_c3);
DEFINE_PUBLIC_ALIAS(DOS$__strpbrk_c2, libd___strpbrk_c2);
DEFINE_PUBLIC_ALIAS(DOS$__strpbrk_c3, libd___strpbrk_c3);

/* stringlist */
DEFINE_PUBLIC_ALIAS(DOS$sl_add, libd_sl_add);
DEFINE_PUBLIC_ALIAS(DOS$sl_free, libd_sl_free);
DEFINE_PUBLIC_ALIAS(DOS$sl_find, libd_sl_find);
DEFINE_PUBLIC_ALIAS(DOS$sl_delete, libd_sl_delete);

/* strings */
DEFINE_PUBLIC_ALIAS(DOS$popcount, libd_popcount);
DEFINE_PUBLIC_ALIAS(DOS$popcountl, libd_popcountl);
DEFINE_PUBLIC_ALIAS(DOS$popcountll, libd_popcountll);
DEFINE_PUBLIC_ALIAS(DOS$popcount32, libd_popcount32);
DEFINE_PUBLIC_ALIAS(DOS$popcount64, libd_popcount64);

/* stropts */
DEFINE_PUBLIC_ALIAS(DOS$isastream, libd_isastream);
DEFINE_PUBLIC_ALIAS(DOS$getmsg, libd_getmsg);
DEFINE_PUBLIC_ALIAS(DOS$getpmsg, libd_getpmsg);
DEFINE_PUBLIC_ALIAS(DOS$putmsg, libd_putmsg);
DEFINE_PUBLIC_ALIAS(DOS$putpmsg, libd_putpmsg);
DEFINE_PUBLIC_ALIAS(DOS$fattach, libd_fattach);
DEFINE_PUBLIC_ALIAS(DOS$fdetach, libd_fdetach);

/* sys.acct */
DEFINE_PUBLIC_ALIAS(DOS$__acct, libd_acct);
DEFINE_PUBLIC_ALIAS(DOS$__libc_acct, libd_acct);
DEFINE_PUBLIC_ALIAS(DOS$acct, libd_acct);

/* sys.auxv */
DEFINE_PUBLIC_ALIAS(DOS$__getauxval, libd_getauxval);
DEFINE_PUBLIC_ALIAS(DOS$getauxval, libd_getauxval);

/* sys.capability */
DEFINE_PUBLIC_ALIAS(DOS$capset, libd_capset);
DEFINE_PUBLIC_ALIAS(DOS$capget, libd_capget);

/* sys.epoll */
DEFINE_PUBLIC_ALIAS(DOS$epoll_create, libd_epoll_create);
DEFINE_PUBLIC_ALIAS(DOS$epoll_create1, libd_epoll_create1);
DEFINE_PUBLIC_ALIAS(DOS$epoll_ctl, libd_epoll_ctl);
DEFINE_PUBLIC_ALIAS(DOS$epoll_wait, libd_epoll_wait);
DEFINE_PUBLIC_ALIAS(DOS$epoll_pwait, libd_epoll_pwait);
DEFINE_PUBLIC_ALIAS(DOS$epoll_rpc_exec, libd_epoll_rpc_exec);

/* sys.eventfd */
DEFINE_PUBLIC_ALIAS(DOS$eventfd, libd_eventfd);
DEFINE_PUBLIC_ALIAS(DOS$eventfd_read, libd_eventfd_read);
DEFINE_PUBLIC_ALIAS(DOS$eventfd_write, libd_eventfd_write);

/* sys.file */
DEFINE_PUBLIC_ALIAS(DOS$__flock, libd_flock);
DEFINE_PUBLIC_ALIAS(DOS$syscall_flock, libd_flock);
DEFINE_PUBLIC_ALIAS(DOS$__syscall_flock, libd_flock);
DEFINE_PUBLIC_ALIAS(DOS$__libc_syscall_flock, libd_flock);
DEFINE_PUBLIC_ALIAS(DOS$flock, libd_flock);

/* sys.fsuid */
DEFINE_PUBLIC_ALIAS(DOS$__setfsuid, libd_setfsuid);
DEFINE_PUBLIC_ALIAS(DOS$__libc_setfsuid, libd_setfsuid);
DEFINE_PUBLIC_ALIAS(DOS$setfsuid, libd_setfsuid);
DEFINE_PUBLIC_ALIAS(DOS$__setfsgid, libd_setfsgid);
DEFINE_PUBLIC_ALIAS(DOS$__libc_setfsgid, libd_setfsgid);
DEFINE_PUBLIC_ALIAS(DOS$setfsgid, libd_setfsgid);

/* sys.inotify */
DEFINE_PUBLIC_ALIAS(DOS$inotify_init1, libd_inotify_init1);
DEFINE_PUBLIC_ALIAS(DOS$inotify_rm_watch, libd_inotify_rm_watch);

/* sys.ioctl */
DEFINE_PUBLIC_ALIAS(DOS$__ioctl, libd_ioctl);
DEFINE_PUBLIC_ALIAS(DOS$__libc_ioctl, libd_ioctl);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__ioctl_time64, libd_ioctl);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$ioctl, libd_ioctl);

/* sys.ipc */
DEFINE_PUBLIC_ALIAS(DOS$ftok, libd_ftok);

/* sys.klog */
DEFINE_PUBLIC_ALIAS(DOS$klogctl, libd_klogctl);

/* sys.mkdev */
DEFINE_PUBLIC_ALIAS(DOS$gnu_dev_makedev, libd_makedev);
DEFINE_PUBLIC_ALIAS(DOS$makedev, libd_makedev);
DEFINE_PUBLIC_ALIAS(DOS$gnu_dev_major, libd_major);
DEFINE_PUBLIC_ALIAS(DOS$major, libd_major);
DEFINE_PUBLIC_ALIAS(DOS$gnu_dev_minor, libd_minor);
DEFINE_PUBLIC_ALIAS(DOS$minor, libd_minor);
DEFINE_PUBLIC_ALIAS(DOS$__makedev, libd___makedev);
DEFINE_PUBLIC_ALIAS(DOS$__major, libd___major);
DEFINE_PUBLIC_ALIAS(DOS$__minor, libd___minor);

/* sys.mman */
DEFINE_PUBLIC_ALIAS(DOS$__mmap, libd_mmap);
DEFINE_PUBLIC_ALIAS(DOS$mmap, libd_mmap);
DEFINE_PUBLIC_ALIAS(DOS$__munmap, libd_munmap);
DEFINE_PUBLIC_ALIAS(DOS$__libc_munmap, libd_munmap);
DEFINE_PUBLIC_ALIAS(DOS$munmap, libd_munmap);
DEFINE_PUBLIC_ALIAS(DOS$__mprotect, libd_mprotect);
DEFINE_PUBLIC_ALIAS(DOS$__libc_mprotect, libd_mprotect);
DEFINE_PUBLIC_ALIAS(DOS$mprotect, libd_mprotect);
DEFINE_PUBLIC_ALIAS(DOS$__msync, libd_msync);
DEFINE_PUBLIC_ALIAS(DOS$__libc_msync, libd_msync);
DEFINE_PUBLIC_ALIAS(DOS$msync, libd_msync);
DEFINE_PUBLIC_ALIAS(DOS$__mlock, libd_mlock);
DEFINE_PUBLIC_ALIAS(DOS$__libc_mlock, libd_mlock);
DEFINE_PUBLIC_ALIAS(DOS$mlock, libd_mlock);
DEFINE_PUBLIC_ALIAS(DOS$__munlock, libd_munlock);
DEFINE_PUBLIC_ALIAS(DOS$__libc_munlock, libd_munlock);
DEFINE_PUBLIC_ALIAS(DOS$munlock, libd_munlock);
DEFINE_PUBLIC_ALIAS(DOS$__mlockall, libd_mlockall);
DEFINE_PUBLIC_ALIAS(DOS$__libc_mlockall, libd_mlockall);
DEFINE_PUBLIC_ALIAS(DOS$mlockall, libd_mlockall);
DEFINE_PUBLIC_ALIAS(DOS$__shm_directory, libd___shm_directory);
DEFINE_PUBLIC_ALIAS(DOS$shm_open, libd_shm_open);
DEFINE_PUBLIC_ALIAS(DOS$shm_unlink, libd_shm_unlink);
DEFINE_PUBLIC_ALIAS(DOS$__madvise, libd_madvise);
DEFINE_PUBLIC_ALIAS(DOS$madvise, libd_madvise);
DEFINE_PUBLIC_ALIAS(DOS$mincore, libd_mincore);
DEFINE_PUBLIC_ALIAS(DOS$mmap64, libd_mmap64);
DEFINE_PUBLIC_ALIAS(DOS$posix_madvise, libd_posix_madvise);
DEFINE_PUBLIC_ALIAS(DOS$__mremap, libd_mremap);
DEFINE_PUBLIC_ALIAS(DOS$__libc_mremap, libd_mremap);
DEFINE_PUBLIC_ALIAS(DOS$mremap, libd_mremap);
DEFINE_PUBLIC_ALIAS(DOS$remap_file_pages, libd_remap_file_pages);
DEFINE_PUBLIC_ALIAS(DOS$memfd_create, libd_memfd_create);
DEFINE_PUBLIC_ALIAS(DOS$mlock2, libd_mlock2);
#include <asm/pkey.h>
#ifdef __ARCH_HAVE_PKEY
DEFINE_PUBLIC_ALIAS(DOS$pkey_alloc, libd_pkey_alloc);
DEFINE_PUBLIC_ALIAS(DOS$pkey_set, libd_pkey_set);
DEFINE_PUBLIC_ALIAS(DOS$pkey_get, libd_pkey_get);
DEFINE_PUBLIC_ALIAS(DOS$pkey_free, libd_pkey_free);
DEFINE_PUBLIC_ALIAS(DOS$pkey_mprotect, libd_pkey_mprotect);
#endif /* __ARCH_HAVE_PKEY */
DEFINE_PUBLIC_ALIAS(DOS$fmapfile, libd_fmapfile);
DEFINE_PUBLIC_ALIAS(DOS$ffmapfile, libd_ffmapfile);
DEFINE_PUBLIC_ALIAS(DOS$unmapfile, libd_unmapfile);

/* sys.mount */
DEFINE_PUBLIC_ALIAS(DOS$__mount, libd_mount);
DEFINE_PUBLIC_ALIAS(DOS$__libc_mount, libd_mount);
DEFINE_PUBLIC_ALIAS(DOS$mount, libd_mount);
DEFINE_PUBLIC_ALIAS(DOS$__umount, libd_umount);
DEFINE_PUBLIC_ALIAS(DOS$__libc_umount, libd_umount);
DEFINE_PUBLIC_ALIAS(DOS$umount, libd_umount);
DEFINE_PUBLIC_ALIAS(DOS$umount2, libd_umount2);

/* sys.msg */
DEFINE_PUBLIC_ALIAS(DOS$msgctl, libd_msgctl);
DEFINE_PUBLIC_ALIAS(DOS$msgget, libd_msgget);
DEFINE_PUBLIC_ALIAS(DOS$__libc_msgrcv, libd_msgrcv);
DEFINE_PUBLIC_ALIAS(DOS$msgrcv, libd_msgrcv);
DEFINE_PUBLIC_ALIAS(DOS$__libc_msgsnd, libd_msgsnd);
DEFINE_PUBLIC_ALIAS(DOS$msgsnd, libd_msgsnd);

/* sys.perm */
#include <bits/typesizes.h>
#ifdef __SIZEOF_PORT_T__
DEFINE_PUBLIC_ALIAS(DOS$__ioperm, libd_ioperm);
DEFINE_PUBLIC_ALIAS(DOS$__libc_ioperm, libd_ioperm);
DEFINE_PUBLIC_ALIAS(DOS$ioperm, libd_ioperm);
DEFINE_PUBLIC_ALIAS(DOS$__iopl, libd_iopl);
DEFINE_PUBLIC_ALIAS(DOS$__libc_iopl, libd_iopl);
DEFINE_PUBLIC_ALIAS(DOS$iopl, libd_iopl);
#endif /* __SIZEOF_PORT_T__ */

/* sys.poll */
DEFINE_PUBLIC_ALIAS(DOS$__poll, libd_poll);
DEFINE_PUBLIC_ALIAS(DOS$__syscall_poll, libd_poll);
DEFINE_PUBLIC_ALIAS(DOS$poll, libd_poll);
DEFINE_PUBLIC_ALIAS(DOS$ppoll, libd_ppoll);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__ppoll64, libd_ppoll64);
DEFINE_PUBLIC_ALIAS(DOS$ppoll64, libd_ppoll64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* sys.prctl */
DEFINE_PUBLIC_ALIAS(DOS$prctl, libd_prctl);

/* sys.profil */
DEFINE_PUBLIC_ALIAS(DOS$sprofil, libd_sprofil);

/* sys.ptrace */
DEFINE_PUBLIC_ALIAS(DOS$ptrace, libd_ptrace);

/* sys.random */
DEFINE_PUBLIC_ALIAS(DOS$getrandom, libd_getrandom);
DEFINE_PUBLIC_ALIAS(DOS$getentropy, libd_getentropy);

/* sys.reboot */
DEFINE_PUBLIC_ALIAS(DOS$__reboot, libd_reboot);
DEFINE_PUBLIC_ALIAS(DOS$__libc_reboot, libd_reboot);
DEFINE_PUBLIC_ALIAS(DOS$reboot, libd_reboot);

/* sys.resource */
DEFINE_PUBLIC_ALIAS(DOS$prlimit, libd_prlimit);
DEFINE_PUBLIC_ALIAS(DOS$prlimit64, libd_prlimit64);
DEFINE_PUBLIC_ALIAS(DOS$__getrlimit, libd_getrlimit);
DEFINE_PUBLIC_ALIAS(DOS$__libc_getrlimit, libd_getrlimit);
DEFINE_PUBLIC_ALIAS(DOS$getrlimit, libd_getrlimit);
DEFINE_PUBLIC_ALIAS(DOS$__setrlimit, libd_setrlimit);
DEFINE_PUBLIC_ALIAS(DOS$__libc_setrlimit, libd_setrlimit);
DEFINE_PUBLIC_ALIAS(DOS$setrlimit, libd_setrlimit);
DEFINE_PUBLIC_ALIAS(DOS$__getrusage, libd_getrusage);
DEFINE_PUBLIC_ALIAS(DOS$__libc_getrusage, libd_getrusage);
DEFINE_PUBLIC_ALIAS(DOS$getrusage, libd_getrusage);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__getrusage64, libd_getrusage64);
DEFINE_PUBLIC_ALIAS(DOS$getrusage64, libd_getrusage64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$getpriority, libd_getpriority);
DEFINE_PUBLIC_ALIAS(DOS$__setpriority, libd_setpriority);
DEFINE_PUBLIC_ALIAS(DOS$__libc_setpriority, libd_setpriority);
DEFINE_PUBLIC_ALIAS(DOS$setpriority, libd_setpriority);
DEFINE_PUBLIC_ALIAS(DOS$getrlimit64, libd_getrlimit64);
DEFINE_PUBLIC_ALIAS(DOS$setrlimit64, libd_setrlimit64);

/* sys.select */
DEFINE_PUBLIC_ALIAS(DOS$__fdelt_warn, libd___fdelt_chk);
DEFINE_PUBLIC_ALIAS(DOS$__fdelt_chk, libd___fdelt_chk);
DEFINE_PUBLIC_ALIAS(DOS$__select, libd_select);
DEFINE_PUBLIC_ALIAS(DOS$select, libd_select);
DEFINE_PUBLIC_ALIAS(DOS$__pselect, libd_pselect);
DEFINE_PUBLIC_ALIAS(DOS$pselect, libd_pselect);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__select64, libd_select64);
DEFINE_PUBLIC_ALIAS(DOS$select64, libd_select64);
DEFINE_PUBLIC_ALIAS(DOS$__pselect64, libd_pselect64);
DEFINE_PUBLIC_ALIAS(DOS$pselect64, libd_pselect64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* sys.sem */
DEFINE_PUBLIC_ALIAS(DOS$semget, libd_semget);
DEFINE_PUBLIC_ALIAS(DOS$semop, libd_semop);
DEFINE_PUBLIC_ALIAS(DOS$semtimedop, libd_semtimedop);

/* sys.sendfile */
DEFINE_PUBLIC_ALIAS(DOS$sendfile, libd_sendfile);
DEFINE_PUBLIC_ALIAS(DOS$sendfile64, libd_sendfile64);

/* sys.shm */
DEFINE_PUBLIC_ALIAS(DOS$shmctl, libd_shmctl);
DEFINE_PUBLIC_ALIAS(DOS$shmget, libd_shmget);
DEFINE_PUBLIC_ALIAS(DOS$shmat, libd_shmat);
DEFINE_PUBLIC_ALIAS(DOS$shmdt, libd_shmdt);

/* sys.signalfd */
DEFINE_PUBLIC_ALIAS(DOS$signalfd, libd_signalfd);

/* sys.socket */
DEFINE_PUBLIC_ALIAS(DOS$__cmsg_nxthdr, libd___cmsg_nxthdr);
DEFINE_PUBLIC_ALIAS(DOS$__socket, libd_socket);
DEFINE_PUBLIC_ALIAS(DOS$socket, libd_socket);
DEFINE_PUBLIC_ALIAS(DOS$__socketpair, libd_socketpair);
DEFINE_PUBLIC_ALIAS(DOS$socketpair, libd_socketpair);
DEFINE_PUBLIC_ALIAS(DOS$__bind, libd_bind);
DEFINE_PUBLIC_ALIAS(DOS$bind, libd_bind);
DEFINE_PUBLIC_ALIAS(DOS$__getsockname, libd_getsockname);
DEFINE_PUBLIC_ALIAS(DOS$getsockname, libd_getsockname);
DEFINE_PUBLIC_ALIAS(DOS$__connect, libd_connect);
DEFINE_PUBLIC_ALIAS(DOS$__libc_connect, libd_connect);
DEFINE_PUBLIC_ALIAS(DOS$connect, libd_connect);
DEFINE_PUBLIC_ALIAS(DOS$__getpeername, libd_getpeername);
DEFINE_PUBLIC_ALIAS(DOS$getpeername, libd_getpeername);
DEFINE_PUBLIC_ALIAS(DOS$__send, libd_send);
DEFINE_PUBLIC_ALIAS(DOS$__libc_send, libd_send);
DEFINE_PUBLIC_ALIAS(DOS$send, libd_send);
DEFINE_PUBLIC_ALIAS(DOS$__recv, libd_recv);
DEFINE_PUBLIC_ALIAS(DOS$__libc_recv, libd_recv);
DEFINE_PUBLIC_ALIAS(DOS$recv, libd_recv);
DEFINE_PUBLIC_ALIAS(DOS$__sendto, libd_sendto);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sendto, libd_sendto);
DEFINE_PUBLIC_ALIAS(DOS$sendto, libd_sendto);
DEFINE_PUBLIC_ALIAS(DOS$__recvfrom, libd_recvfrom);
DEFINE_PUBLIC_ALIAS(DOS$__libc_recvfrom, libd_recvfrom);
DEFINE_PUBLIC_ALIAS(DOS$recvfrom, libd_recvfrom);
DEFINE_PUBLIC_ALIAS(DOS$__sendmsg, libd_sendmsg);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sendmsg, libd_sendmsg);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__sendmsg64, libd_sendmsg);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$sendmsg, libd_sendmsg);
DEFINE_PUBLIC_ALIAS(DOS$__recvmsg, libd_recvmsg);
DEFINE_PUBLIC_ALIAS(DOS$__libc_recvmsg, libd_recvmsg);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__recvmsg64, libd_recvmsg);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$recvmsg, libd_recvmsg);
DEFINE_PUBLIC_ALIAS(DOS$__getsockopt, libd_getsockopt);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__getsockopt64, libd_getsockopt);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$getsockopt, libd_getsockopt);
DEFINE_PUBLIC_ALIAS(DOS$__setsockopt, libd_setsockopt);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__setsockopt64, libd_setsockopt);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$setsockopt, libd_setsockopt);
DEFINE_PUBLIC_ALIAS(DOS$__listen, libd_listen);
DEFINE_PUBLIC_ALIAS(DOS$listen, libd_listen);
DEFINE_PUBLIC_ALIAS(DOS$__accept, libd_accept);
DEFINE_PUBLIC_ALIAS(DOS$__libc_accept, libd_accept);
DEFINE_PUBLIC_ALIAS(DOS$accept, libd_accept);
DEFINE_PUBLIC_ALIAS(DOS$__shutdown, libd_shutdown);
DEFINE_PUBLIC_ALIAS(DOS$shutdown, libd_shutdown);
DEFINE_PUBLIC_ALIAS(DOS$accept4, libd_accept4);
DEFINE_PUBLIC_ALIAS(DOS$__sendmmsg, libd_sendmmsg);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__sendmmsg64, libd_sendmmsg);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$sendmmsg, libd_sendmmsg);
DEFINE_PUBLIC_ALIAS(DOS$recvmmsg, libd_recvmmsg);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__recvmmsg64, libd_recvmmsg64);
DEFINE_PUBLIC_ALIAS(DOS$recvmmsg64, libd_recvmmsg64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$sockatmark, libd_sockatmark);
DEFINE_PUBLIC_ALIAS(DOS$isfdtype, libd_isfdtype);

/* sys.stat */
DEFINE_PUBLIC_ALIAS(DOS$_umask, libd_umask);
DEFINE_PUBLIC_ALIAS(DOS$__umask, libd_umask);
DEFINE_PUBLIC_ALIAS(DOS$__libc_umask, libd_umask);
DEFINE_PUBLIC_ALIAS(DOS$umask, libd_umask);
DEFINE_PUBLIC_ALIAS(DOS$__fchmod, libd_fchmod);
DEFINE_PUBLIC_ALIAS(DOS$__libc_fchmod, libd_fchmod);
DEFINE_PUBLIC_ALIAS(DOS$fchmod, libd_fchmod);
DEFINE_PUBLIC_ALIAS(DOS$futimens, libd_futimens);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__futimens64, libd_futimens64);
DEFINE_PUBLIC_ALIAS(DOS$futimens64, libd_futimens64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* sys.statfs */
DEFINE_PUBLIC_ALIAS(DOS$__statfs, libd_statfs);
DEFINE_PUBLIC_ALIAS(DOS$__libc_statfs, libd_statfs);
DEFINE_PUBLIC_ALIAS(DOS$statfs, libd_statfs);
DEFINE_PUBLIC_ALIAS(DOS$__fstatfs, libd_fstatfs);
DEFINE_PUBLIC_ALIAS(DOS$__libc_fstatfs, libd_fstatfs);
DEFINE_PUBLIC_ALIAS(DOS$fstatfs, libd_fstatfs);
DEFINE_PUBLIC_ALIAS(DOS$statfs64, libd_statfs64);
DEFINE_PUBLIC_ALIAS(DOS$fstatfs64, libd_fstatfs64);

/* sys.statvfs */
DEFINE_PUBLIC_ALIAS(DOS$statvfs, libd_statvfs);
DEFINE_PUBLIC_ALIAS(DOS$fstatvfs, libd_fstatvfs);
DEFINE_PUBLIC_ALIAS(DOS$statvfs64, libd_statvfs64);
DEFINE_PUBLIC_ALIAS(DOS$fstatvfs64, libd_fstatvfs64);

/* sys.swap */
DEFINE_PUBLIC_ALIAS(DOS$swapon, libd_swapon);
DEFINE_PUBLIC_ALIAS(DOS$__swapon, libd_swapon);
DEFINE_PUBLIC_ALIAS(DOS$__libc_swapon, libd_swapon);
DEFINE_PUBLIC_ALIAS(DOS$swapon, libd_swapon);
DEFINE_PUBLIC_ALIAS(DOS$swapoff, libd_swapoff);
DEFINE_PUBLIC_ALIAS(DOS$__swapoff, libd_swapoff);
DEFINE_PUBLIC_ALIAS(DOS$__libc_swapoff, libd_swapoff);
DEFINE_PUBLIC_ALIAS(DOS$swapoff, libd_swapoff);

/* sys.sysinfo */
DEFINE_PUBLIC_ALIAS(DOS$__sysinfo, libd_sysinfo);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sysinfo, libd_sysinfo);
DEFINE_PUBLIC_ALIAS(DOS$sysinfo, libd_sysinfo);

/* sys.syslog */
DEFINE_PUBLIC_ALIAS(DOS$openlog, libd_openlog);
DEFINE_PUBLIC_ALIAS(DOS$setlogmask, libd_setlogmask);
DEFINE_PUBLIC_ALIAS(DOS$vsyslog, libd_vsyslog);

/* sys.systeminfo */
DEFINE_PUBLIC_ALIAS(DOS$__solaris_sysinfo, libd___solaris_sysinfo);

/* sys.time */
DEFINE_PUBLIC_ALIAS(DOS$__gettimeofday, libd_gettimeofday);
DEFINE_PUBLIC_ALIAS(DOS$__libc_gettimeofday, libd_gettimeofday);
DEFINE_PUBLIC_ALIAS(DOS$gettimeofday, libd_gettimeofday);
DEFINE_PUBLIC_ALIAS(DOS$__getitimer, libd_getitimer);
DEFINE_PUBLIC_ALIAS(DOS$__libc_getitimer, libd_getitimer);
DEFINE_PUBLIC_ALIAS(DOS$getitimer, libd_getitimer);
DEFINE_PUBLIC_ALIAS(DOS$__setitimer, libd_setitimer);
DEFINE_PUBLIC_ALIAS(DOS$__libc_setitimer, libd_setitimer);
DEFINE_PUBLIC_ALIAS(DOS$setitimer, libd_setitimer);
DEFINE_PUBLIC_ALIAS(DOS$__utimes, libd_utimes);
DEFINE_PUBLIC_ALIAS(DOS$utimes, libd_utimes);
DEFINE_PUBLIC_ALIAS(DOS$futimesat, libd_futimesat);
DEFINE_PUBLIC_ALIAS(DOS$__settimeofday, libd_settimeofday);
DEFINE_PUBLIC_ALIAS(DOS$__libc_settimeofday, libd_settimeofday);
DEFINE_PUBLIC_ALIAS(DOS$settimeofday, libd_settimeofday);
DEFINE_PUBLIC_ALIAS(DOS$__adjtime, libd_adjtime);
DEFINE_PUBLIC_ALIAS(DOS$adjtime, libd_adjtime);
DEFINE_PUBLIC_ALIAS(DOS$lutimes, libd_lutimes);
DEFINE_PUBLIC_ALIAS(DOS$futimes, libd_futimes);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__gettimeofday64, libd_gettimeofday64);
DEFINE_PUBLIC_ALIAS(DOS$gettimeofday64, libd_gettimeofday64);
DEFINE_PUBLIC_ALIAS(DOS$__getitimer64, libd_getitimer64);
DEFINE_PUBLIC_ALIAS(DOS$getitimer64, libd_getitimer64);
DEFINE_PUBLIC_ALIAS(DOS$__setitimer64, libd_setitimer64);
DEFINE_PUBLIC_ALIAS(DOS$setitimer64, libd_setitimer64);
DEFINE_PUBLIC_ALIAS(DOS$__utimes64, libd_utimes64);
DEFINE_PUBLIC_ALIAS(DOS$utimes64, libd_utimes64);
DEFINE_PUBLIC_ALIAS(DOS$__settimeofday64, libd_settimeofday64);
DEFINE_PUBLIC_ALIAS(DOS$settimeofday64, libd_settimeofday64);
DEFINE_PUBLIC_ALIAS(DOS$__adjtime64, libd_adjtime64);
DEFINE_PUBLIC_ALIAS(DOS$adjtime64, libd_adjtime64);
DEFINE_PUBLIC_ALIAS(DOS$__lutimes64, libd_lutimes64);
DEFINE_PUBLIC_ALIAS(DOS$lutimes64, libd_lutimes64);
DEFINE_PUBLIC_ALIAS(DOS$__futimes64, libd_futimes64);
DEFINE_PUBLIC_ALIAS(DOS$futimes64, libd_futimes64);
DEFINE_PUBLIC_ALIAS(DOS$__futimesat64, libd_futimesat64);
DEFINE_PUBLIC_ALIAS(DOS$futimesat64, libd_futimesat64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* sys.timeb */
DEFINE_PUBLIC_ALIAS(DOS$_ftime, libd__ftime32);
DEFINE_PUBLIC_ALIAS(DOS$_ftime32, libd__ftime32);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$_ftime64, libd__ftime64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$_ftime32_s, libd__ftime32_s);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$_ftime64_s, libd__ftime64_s);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$ftime, libd_ftime);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$ftime64, libd_ftime64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* sys.timerfd */
DEFINE_PUBLIC_ALIAS(DOS$timerfd_create, libd_timerfd_create);
DEFINE_PUBLIC_ALIAS(DOS$timerfd_settime, libd_timerfd_settime);
DEFINE_PUBLIC_ALIAS(DOS$timerfd_gettime, libd_timerfd_gettime);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__timerfd_settime64, libd_timerfd_settime64);
DEFINE_PUBLIC_ALIAS(DOS$timerfd_settime64, libd_timerfd_settime64);
DEFINE_PUBLIC_ALIAS(DOS$__timerfd_gettime64, libd_timerfd_gettime64);
DEFINE_PUBLIC_ALIAS(DOS$timerfd_gettime64, libd_timerfd_gettime64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* sys.times */
DEFINE_PUBLIC_ALIAS(DOS$__times, libd_times);
DEFINE_PUBLIC_ALIAS(DOS$__libc_times, libd_times);
DEFINE_PUBLIC_ALIAS(DOS$times, libd_times);

/* sys.timex */
DEFINE_PUBLIC_ALIAS(DOS$__adjtimex, libd_adjtimex);
DEFINE_PUBLIC_ALIAS(DOS$__libc_adjtimex, libd_adjtimex);
DEFINE_PUBLIC_ALIAS(DOS$adjtimex, libd_adjtimex);
DEFINE_PUBLIC_ALIAS(DOS$ntp_gettimex, libd_ntp_gettimex);
DEFINE_PUBLIC_ALIAS(DOS$ntp_adjtime, libd_ntp_adjtime);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$___adjtimex64, libd_adjtimex64);
DEFINE_PUBLIC_ALIAS(DOS$adjtimex64, libd_adjtimex64);
DEFINE_PUBLIC_ALIAS(DOS$ntp_adjtime64, libd_ntp_adjtime64);
DEFINE_PUBLIC_ALIAS(DOS$__ntp_gettimex64, libd_ntp_gettimex64);
DEFINE_PUBLIC_ALIAS(DOS$ntp_gettimex64, libd_ntp_gettimex64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* sys.uio */
DEFINE_PUBLIC_ALIAS(DOS$process_vm_readv, libd_process_vm_readv);
DEFINE_PUBLIC_ALIAS(DOS$process_vm_writev, libd_process_vm_writev);
DEFINE_PUBLIC_ALIAS(DOS$__readv, libd_readv);
DEFINE_PUBLIC_ALIAS(DOS$syscall_readv, libd_readv);
DEFINE_PUBLIC_ALIAS(DOS$__syscall_readv, libd_readv);
DEFINE_PUBLIC_ALIAS(DOS$__libc_syscall_readv, libd_readv);
DEFINE_PUBLIC_ALIAS(DOS$__libc_readv, libd_readv);
DEFINE_PUBLIC_ALIAS(DOS$readv, libd_readv);
DEFINE_PUBLIC_ALIAS(DOS$__writev, libd_writev);
DEFINE_PUBLIC_ALIAS(DOS$__libc_writev, libd_writev);
DEFINE_PUBLIC_ALIAS(DOS$syscall_writev, libd_writev);
DEFINE_PUBLIC_ALIAS(DOS$__syscall_writev, libd_writev);
DEFINE_PUBLIC_ALIAS(DOS$__libc_syscall_writev, libd_writev);
DEFINE_PUBLIC_ALIAS(DOS$writev, libd_writev);
DEFINE_PUBLIC_ALIAS(DOS$preadv, libd_preadv);
DEFINE_PUBLIC_ALIAS(DOS$pwritev, libd_pwritev);
DEFINE_PUBLIC_ALIAS(DOS$preadv64, libd_preadv64);
DEFINE_PUBLIC_ALIAS(DOS$pwritev64, libd_pwritev64);

/* sys.ustat */
DEFINE_PUBLIC_ALIAS(DOS$prev_ustat, libd_ustat);
DEFINE_PUBLIC_ALIAS(DOS$__prev_ustat, libd_ustat);
DEFINE_PUBLIC_ALIAS(DOS$__libc_prev_ustat, libd_ustat);
DEFINE_PUBLIC_ALIAS(DOS$ustat, libd_ustat);

/* sys.utsname */
DEFINE_PUBLIC_ALIAS(DOS$__uname, libd_uname);
DEFINE_PUBLIC_ALIAS(DOS$__libc_uname, libd_uname);
DEFINE_PUBLIC_ALIAS(DOS$uname, libd_uname);

/* sys.vlimit */
DEFINE_PUBLIC_ALIAS(DOS$vlimit, libd_vlimit);

/* sys.vtimes */
DEFINE_PUBLIC_ALIAS(DOS$vtimes, libd_vtimes);

/* sys.wait */
DEFINE_PUBLIC_ALIAS(DOS$__wait, libd_wait);
DEFINE_PUBLIC_ALIAS(DOS$__libc_wait, libd_wait);
DEFINE_PUBLIC_ALIAS(DOS$wait, libd_wait);
DEFINE_PUBLIC_ALIAS(DOS$__waitpid, libd_waitpid);
DEFINE_PUBLIC_ALIAS(DOS$__libc_waitpid, libd_waitpid);
DEFINE_PUBLIC_ALIAS(DOS$waitpid, libd_waitpid);
DEFINE_PUBLIC_ALIAS(DOS$__waitid, libd_waitid);
DEFINE_PUBLIC_ALIAS(DOS$waitid, libd_waitid);
DEFINE_PUBLIC_ALIAS(DOS$__wait3, libd_wait3);
DEFINE_PUBLIC_ALIAS(DOS$wait3, libd_wait3);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__wait3_time64, libd_wait3_64);
DEFINE_PUBLIC_ALIAS(DOS$wait3_64, libd_wait3_64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$__wait4, libd_wait4);
DEFINE_PUBLIC_ALIAS(DOS$__libc_wait4, libd_wait4);
DEFINE_PUBLIC_ALIAS(DOS$wait4, libd_wait4);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__wait4_time64, libd_wait4_64);
DEFINE_PUBLIC_ALIAS(DOS$wait4_64, libd_wait4_64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$detach, libd_detach);

/* sys.xattr */
DEFINE_PUBLIC_ALIAS(DOS$setxattr, libd_setxattr);
DEFINE_PUBLIC_ALIAS(DOS$lsetxattr, libd_lsetxattr);
DEFINE_PUBLIC_ALIAS(DOS$fsetxattr, libd_fsetxattr);
DEFINE_PUBLIC_ALIAS(DOS$getxattr, libd_getxattr);
DEFINE_PUBLIC_ALIAS(DOS$lgetxattr, libd_lgetxattr);
DEFINE_PUBLIC_ALIAS(DOS$fgetxattr, libd_fgetxattr);
DEFINE_PUBLIC_ALIAS(DOS$listxattr, libd_listxattr);
DEFINE_PUBLIC_ALIAS(DOS$llistxattr, libd_llistxattr);
DEFINE_PUBLIC_ALIAS(DOS$flistxattr, libd_flistxattr);
DEFINE_PUBLIC_ALIAS(DOS$removexattr, libd_removexattr);
DEFINE_PUBLIC_ALIAS(DOS$lremovexattr, libd_lremovexattr);
DEFINE_PUBLIC_ALIAS(DOS$fremovexattr, libd_fremovexattr);

/* termios */
DEFINE_PUBLIC_ALIAS(DOS$cfgetospeed, libd_cfgetospeed);
DEFINE_PUBLIC_ALIAS(DOS$cfgetispeed, libd_cfgetispeed);
DEFINE_PUBLIC_ALIAS(DOS$cfsetospeed, libd_cfsetospeed);
DEFINE_PUBLIC_ALIAS(DOS$cfsetispeed, libd_cfsetispeed);
DEFINE_PUBLIC_ALIAS(DOS$__tcgetattr, libd_tcgetattr);
DEFINE_PUBLIC_ALIAS(DOS$tcgetattr, libd_tcgetattr);
DEFINE_PUBLIC_ALIAS(DOS$tcsetattr, libd_tcsetattr);
DEFINE_PUBLIC_ALIAS(DOS$tcsendbreak, libd_tcsendbreak);
DEFINE_PUBLIC_ALIAS(DOS$__libc_tcdrain, libd_tcdrain);
DEFINE_PUBLIC_ALIAS(DOS$tcdrain, libd_tcdrain);
DEFINE_PUBLIC_ALIAS(DOS$tcflush, libd_tcflush);
DEFINE_PUBLIC_ALIAS(DOS$tcflow, libd_tcflow);
DEFINE_PUBLIC_ALIAS(DOS$tcgetsid, libd_tcgetsid);
DEFINE_PUBLIC_ALIAS(DOS$tcsetsid, libd_tcsetsid);
DEFINE_PUBLIC_ALIAS(DOS$cfsetspeed, libd_cfsetspeed);
DEFINE_PUBLIC_ALIAS(DOS$cfmakeraw, libd_cfmakeraw);
DEFINE_PUBLIC_ALIAS(DOS$cfmakesane, libd_cfmakesane);
DEFINE_PUBLIC_ALIAS(DOS$tcgetwinsize, libd_tcgetwinsize);
DEFINE_PUBLIC_ALIAS(DOS$tcsetwinsize, libd_tcsetwinsize);

/* thread */
DEFINE_PUBLIC_ALIAS(DOS$thr_create, libd_thr_create);
DEFINE_PUBLIC_ALIAS(DOS$thr_join, libd_thr_join);
DEFINE_PUBLIC_ALIAS(DOS$thr_setprio, libd_thr_setprio);
DEFINE_PUBLIC_ALIAS(DOS$thr_getprio, libd_thr_getprio);
DEFINE_PUBLIC_ALIAS(DOS$thr_getspecific, libd_thr_getspecific);
DEFINE_PUBLIC_ALIAS(DOS$thr_stksegment, libd_thr_stksegment);

/* threads */
DEFINE_PUBLIC_ALIAS(DOS$thrd_sleep, libd_thrd_sleep);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__thrd_sleep64, libd_thrd_sleep64);
DEFINE_PUBLIC_ALIAS(DOS$thrd_sleep64, libd_thrd_sleep64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$thrd_exit, libd_thrd_exit);
DEFINE_PUBLIC_ALIAS(DOS$thrd_detach, libd_thrd_detach);
DEFINE_PUBLIC_ALIAS(DOS$thrd_join, libd_thrd_join);
DEFINE_PUBLIC_ALIAS(DOS$mtx_init, libd_mtx_init);
DEFINE_PUBLIC_ALIAS(DOS$mtx_lock, libd_mtx_lock);
DEFINE_PUBLIC_ALIAS(DOS$mtx_timedlock, libd_mtx_timedlock);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__mtx_timedlock64, libd_mtx_timedlock64);
DEFINE_PUBLIC_ALIAS(DOS$mtx_timedlock64, libd_mtx_timedlock64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$mtx_trylock, libd_mtx_trylock);
DEFINE_PUBLIC_ALIAS(DOS$mtx_unlock, libd_mtx_unlock);
DEFINE_PUBLIC_ALIAS(DOS$cnd_init, libd_cnd_init);
DEFINE_PUBLIC_ALIAS(DOS$cnd_signal, libd_cnd_signal);
DEFINE_PUBLIC_ALIAS(DOS$cnd_broadcast, libd_cnd_broadcast);
DEFINE_PUBLIC_ALIAS(DOS$cnd_wait, libd_cnd_wait);
DEFINE_PUBLIC_ALIAS(DOS$cnd_timedwait, libd_cnd_timedwait);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__cnd_timedwait64, libd_cnd_timedwait64);
DEFINE_PUBLIC_ALIAS(DOS$cnd_timedwait64, libd_cnd_timedwait64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$tss_create, libd_tss_create);
DEFINE_PUBLIC_ALIAS(DOS$tss_set, libd_tss_set);

/* time */
DEFINE_PUBLIC_ALIAS(DOS$__time, libd_time);
DEFINE_PUBLIC_ALIAS(DOS$__libc_time, libd_time);
DEFINE_PUBLIC_ALIAS(DOS$_time32, libd_time);
DEFINE_PUBLIC_ALIAS(DOS$time, libd_time);
DEFINE_PUBLIC_ALIAS(DOS$_difftime32, libd_difftime);
DEFINE_PUBLIC_ALIAS(DOS$difftime, libd_difftime);
DEFINE_PUBLIC_ALIAS(DOS$_mktime32, libd_mktime);
DEFINE_PUBLIC_ALIAS(DOS$timelocal, libd_mktime);
DEFINE_PUBLIC_ALIAS(DOS$mktime, libd_mktime);
DEFINE_PUBLIC_ALIAS(DOS$_ctime32, libd_ctime);
DEFINE_PUBLIC_ALIAS(DOS$ctime, libd_ctime);
DEFINE_PUBLIC_ALIAS(DOS$_gmtime32, libd_gmtime);
DEFINE_PUBLIC_ALIAS(DOS$gmtime, libd_gmtime);
DEFINE_PUBLIC_ALIAS(DOS$_localtime32, libd_localtime);
DEFINE_PUBLIC_ALIAS(DOS$localtime, libd_localtime);
DEFINE_PUBLIC_ALIAS(DOS$strftime, libd_strftime);
DEFINE_PUBLIC_ALIAS(DOS$asctime, libd_asctime);
DEFINE_PUBLIC_ALIAS(DOS$asctime_s, libd_asctime_s);
DEFINE_PUBLIC_ALIAS(DOS$_time64, libd_time64);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__time64, libd_time64);
DEFINE_PUBLIC_ALIAS(DOS$time64, libd_time64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$_difftime64, libd_difftime64);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__difftime64, libd_difftime64);
DEFINE_PUBLIC_ALIAS(DOS$difftime64, libd_difftime64);
DEFINE_PUBLIC_ALIAS(DOS$timelocal64, libd_mktime64);
DEFINE_PUBLIC_ALIAS(DOS$__mktime64, libd_mktime64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$_mktime64, libd_mktime64);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$mktime64, libd_mktime64);
DEFINE_PUBLIC_ALIAS(DOS$__ctime64, libd_ctime64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$_ctime64, libd_ctime64);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$ctime64, libd_ctime64);
DEFINE_PUBLIC_ALIAS(DOS$__gmtime64, libd_gmtime64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$_gmtime64, libd_gmtime64);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$gmtime64, libd_gmtime64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$_localtime64, libd_localtime64);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__localtime64, libd_localtime64);
DEFINE_PUBLIC_ALIAS(DOS$localtime64, libd_localtime64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$__stime, libd_stime);
DEFINE_PUBLIC_ALIAS(DOS$__libc_stime, libd_stime);
DEFINE_PUBLIC_ALIAS(DOS$stime, libd_stime);
DEFINE_PUBLIC_ALIAS(DOS$_mkgmtime, libd_timegm);
DEFINE_PUBLIC_ALIAS(DOS$_mkgmtime32, libd_timegm);
DEFINE_PUBLIC_ALIAS(DOS$timegm, libd_timegm);
DEFINE_PUBLIC_ALIAS(DOS$dysize, libd_dysize);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$stime64, libd_stime64);
DEFINE_PUBLIC_ALIAS(DOS$__timegm64, libd_timegm64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$_mkgmtime64, libd_timegm64);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$timegm64, libd_timegm64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$__nanosleep, libd_nanosleep);
DEFINE_PUBLIC_ALIAS(DOS$__libc_nanosleep, libd_nanosleep);
DEFINE_PUBLIC_ALIAS(DOS$__libc_nanosleep, libd_nanosleep);
DEFINE_PUBLIC_ALIAS(DOS$nanosleep, libd_nanosleep);
DEFINE_PUBLIC_ALIAS(DOS$__clock_getres, libd_clock_getres);
DEFINE_PUBLIC_ALIAS(DOS$clock_getres, libd_clock_getres);
DEFINE_PUBLIC_ALIAS(DOS$__clock_gettime, libd_clock_gettime);
DEFINE_PUBLIC_ALIAS(DOS$clock_gettime, libd_clock_gettime);
DEFINE_PUBLIC_ALIAS(DOS$__clock_settime, libd_clock_settime);
DEFINE_PUBLIC_ALIAS(DOS$clock_settime, libd_clock_settime);
DEFINE_PUBLIC_ALIAS(DOS$timer_create, libd_timer_create);
DEFINE_PUBLIC_ALIAS(DOS$timer_delete, libd_timer_delete);
DEFINE_PUBLIC_ALIAS(DOS$timer_settime, libd_timer_settime);
DEFINE_PUBLIC_ALIAS(DOS$timer_gettime, libd_timer_gettime);
DEFINE_PUBLIC_ALIAS(DOS$timer_getoverrun, libd_timer_getoverrun);
DEFINE_PUBLIC_ALIAS(DOS$__clock_nanosleep, libd_clock_nanosleep);
DEFINE_PUBLIC_ALIAS(DOS$clock_nanosleep, libd_clock_nanosleep);
DEFINE_PUBLIC_ALIAS(DOS$__clock_getcpuclockid, libd_clock_getcpuclockid);
DEFINE_PUBLIC_ALIAS(DOS$clock_getcpuclockid, libd_clock_getcpuclockid);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__nanosleep64, libd_nanosleep64);
DEFINE_PUBLIC_ALIAS(DOS$nanosleep64, libd_nanosleep64);
DEFINE_PUBLIC_ALIAS(DOS$__clock_getres64, libd_clock_getres64);
DEFINE_PUBLIC_ALIAS(DOS$clock_getres64, libd_clock_getres64);
DEFINE_PUBLIC_ALIAS(DOS$__clock_gettime64, libd_clock_gettime64);
DEFINE_PUBLIC_ALIAS(DOS$clock_gettime64, libd_clock_gettime64);
DEFINE_PUBLIC_ALIAS(DOS$__clock_settime64, libd_clock_settime64);
DEFINE_PUBLIC_ALIAS(DOS$clock_settime64, libd_clock_settime64);
DEFINE_PUBLIC_ALIAS(DOS$__timer_settime64, libd_timer_settime64);
DEFINE_PUBLIC_ALIAS(DOS$timer_settime64, libd_timer_settime64);
DEFINE_PUBLIC_ALIAS(DOS$__timer_gettime64, libd_timer_gettime64);
DEFINE_PUBLIC_ALIAS(DOS$timer_gettime64, libd_timer_gettime64);
DEFINE_PUBLIC_ALIAS(DOS$__clock_nanosleep_time64, libd_clock_nanosleep64);
DEFINE_PUBLIC_ALIAS(DOS$clock_nanosleep64, libd_clock_nanosleep64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$_timespec32_get, libd_timespec_get);
DEFINE_PUBLIC_ALIAS(DOS$timespec_get, libd_timespec_get);
DEFINE_PUBLIC_ALIAS(DOS$_timespec64_get, libd_timespec_get64);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__timespec_get64, libd_timespec_get64);
DEFINE_PUBLIC_ALIAS(DOS$timespec_get64, libd_timespec_get64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$_timespec32_get, libd_timespec_getres);
DEFINE_PUBLIC_ALIAS(DOS$timespec_getres, libd_timespec_getres);
DEFINE_PUBLIC_ALIAS(DOS$_timespec64_get, libd_timespec_getres64);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__timespec_getres64, libd_timespec_getres64);
DEFINE_PUBLIC_ALIAS(DOS$timespec_getres64, libd_timespec_getres64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$getdate, libd_getdate);
DEFINE_PUBLIC_ALIAS(DOS$_strftime_l, libd_strftime_l);
DEFINE_PUBLIC_ALIAS(DOS$__strftime_l, libd_strftime_l);
DEFINE_PUBLIC_ALIAS(DOS$strftime_l, libd_strftime_l);
DEFINE_PUBLIC_ALIAS(DOS$strptime, libd_strptime);
DEFINE_PUBLIC_ALIAS(DOS$strptime_l, libd_strptime_l);
DEFINE_PUBLIC_ALIAS(DOS$getdate_r, libd_getdate_r);
DEFINE_PUBLIC_ALIAS(DOS$clock_adjtime, libd_clock_adjtime);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__clock_adjtime64, libd_clock_adjtime64);
DEFINE_PUBLIC_ALIAS(DOS$clock_adjtime64, libd_clock_adjtime64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$__gmtime_r, libd_gmtime_r);
DEFINE_PUBLIC_ALIAS(DOS$gmtime_r, libd_gmtime_r);
DEFINE_PUBLIC_ALIAS(DOS$__localtime_r, libd_localtime_r);
DEFINE_PUBLIC_ALIAS(DOS$localtime_r, libd_localtime_r);
DEFINE_PUBLIC_ALIAS(DOS$ctime_r, libd_ctime_r);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__gmtime64_r, libd_gmtime64_r);
DEFINE_PUBLIC_ALIAS(DOS$gmtime64_r, libd_gmtime64_r);
DEFINE_PUBLIC_ALIAS(DOS$__localtime64_r, libd_localtime64_r);
DEFINE_PUBLIC_ALIAS(DOS$localtime64_r, libd_localtime64_r);
DEFINE_PUBLIC_ALIAS(DOS$__ctime64_r, libd_ctime64_r);
DEFINE_PUBLIC_ALIAS(DOS$ctime64_r, libd_ctime64_r);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(DOS$__asctime_r, libd_asctime_r);
DEFINE_PUBLIC_ALIAS(DOS$asctime_r, libd_asctime_r);
DEFINE_PUBLIC_ALIAS(DOS$_get_daylight, libd__get_daylight);
DEFINE_PUBLIC_ALIAS(DOS$_get_timezone, libd__get_timezone);
DEFINE_PUBLIC_ALIAS(DOS$_get_dstbias, libd__get_dstbias);
DEFINE_PUBLIC_ALIAS(DOS$_gmtime32_s, libd__gmtime32_s);
DEFINE_PUBLIC_ALIAS(DOS$_gmtime64_s, libd__gmtime64_s);
DEFINE_PUBLIC_ALIAS(DOS$_localtime32_s, libd__localtime32_s);
DEFINE_PUBLIC_ALIAS(DOS$_localtime64_s, libd__localtime64_s);
DEFINE_PUBLIC_ALIAS(DOS$_ctime32_s, libd__ctime32_s);
DEFINE_PUBLIC_ALIAS(DOS$_ctime64_s, libd__ctime64_s);
DEFINE_PUBLIC_ALIAS(DOS$_strtime, libd__strtime);
DEFINE_PUBLIC_ALIAS(DOS$_strdate, libd__strdate);
DEFINE_PUBLIC_ALIAS(DOS$_getsystime, libd__getsystime);
DEFINE_PUBLIC_ALIAS(DOS$_setsystime, libd__setsystime);
DEFINE_PUBLIC_ALIAS(DOS$__nanosleep_nocancel, libd___nanosleep_nocancel);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$__nanosleep64_nocancel, libd___nanosleep64_nocancel);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* timeval-utils */
DEFINE_PUBLIC_ALIAS(DOS$timeval_add, libd_timeval_add);
DEFINE_PUBLIC_ALIAS(DOS$timeval_sub, libd_timeval_sub);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$timeval_add64, libd_timeval_add64);
DEFINE_PUBLIC_ALIAS(DOS$timeval_sub64, libd_timeval_sub64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* ttyent */
DEFINE_PUBLIC_ALIAS(DOS$getttynam, libd_getttynam);

/* uchar */
DEFINE_PUBLIC_ALIAS(DOS$mbrtoc8, libd_mbrtoc8);
DEFINE_PUBLIC_ALIAS(DOS$c8rtomb, libd_c8rtomb);
DEFINE_PUBLIC_ALIAS(DOS$convert_freev, libd_convert_freev);
DEFINE_PUBLIC_ALIAS(DOS$convert_freevn, libd_convert_freevn);

/* ulimit */
DEFINE_PUBLIC_ALIAS(DOS$__ulimit, libd_ulimit);
DEFINE_PUBLIC_ALIAS(DOS$ulimit, libd_ulimit);

/* unicode */
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf8, libd_unicode_readutf8);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf8_rev, libd_unicode_readutf8_rev);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf8_n, libd_unicode_readutf8_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf8_rev_n, libd_unicode_readutf8_rev_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16, libd_unicode_readutf16);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_n, libd_unicode_readutf16_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_swap, libd_unicode_readutf16_swap);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_swap_n, libd_unicode_readutf16_swap_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_rev, libd_unicode_readutf16_rev);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_swap_rev, libd_unicode_readutf16_swap_rev);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_rev_n, libd_unicode_readutf16_rev_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_readutf16_swap_rev_n, libd_unicode_readutf16_swap_rev_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_writeutf8, libd_unicode_writeutf8);
DEFINE_PUBLIC_ALIAS(DOS$unicode_writeutf8_n, libd_unicode_writeutf8_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_writeutf16, libd_unicode_writeutf16);
DEFINE_PUBLIC_ALIAS(DOS$unicode_writeutf16_chk, libd_unicode_writeutf16_chk);
DEFINE_PUBLIC_ALIAS(DOS$unicode_len8to16, libd_unicode_len8to16);
DEFINE_PUBLIC_ALIAS(DOS$unicode_len8to32, libd_unicode_len8to32);
DEFINE_PUBLIC_ALIAS(DOS$unicode_8to16, libd_unicode_8to16);
DEFINE_PUBLIC_ALIAS(DOS$unicode_8to16_n, libd_unicode_8to16_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_8to16_chk, libd_unicode_8to16_chk);
DEFINE_PUBLIC_ALIAS(DOS$unicode_8to16_chk_n, libd_unicode_8to16_chk_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_8to32, libd_unicode_8to32);
DEFINE_PUBLIC_ALIAS(DOS$unicode_8to32_n, libd_unicode_8to32_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_16to8, libd_unicode_16to8);
DEFINE_PUBLIC_ALIAS(DOS$unicode_16to8_n, libd_unicode_16to8_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_16to32, libd_unicode_16to32);
DEFINE_PUBLIC_ALIAS(DOS$unicode_16to32_n, libd_unicode_16to32_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_32to8, libd_unicode_32to8);
DEFINE_PUBLIC_ALIAS(DOS$unicode_32to8_n, libd_unicode_32to8_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_32to16, libd_unicode_32to16);
DEFINE_PUBLIC_ALIAS(DOS$unicode_32to16_n, libd_unicode_32to16_n);
DEFINE_PUBLIC_ALIAS(DOS$unicode_c8toc16, libd_unicode_c8toc16);
DEFINE_PUBLIC_ALIAS(DOS$unicode_c8toc32, libd_unicode_c8toc32);
DEFINE_PUBLIC_ALIAS(DOS$unicode_c16toc8, libd_unicode_c16toc8);
DEFINE_PUBLIC_ALIAS(DOS$__unicode_descriptor, libd___unicode_descriptor);
DEFINE_PUBLIC_ALIAS(DOS$__unicode_descriptor_digit, libd___unicode_descriptor_digit);
DEFINE_PUBLIC_ALIAS(DOS$__unicode_descriptor_digit64, libd___unicode_descriptor_digit64);
DEFINE_PUBLIC_ALIAS(DOS$__unicode_descriptor_digitd, libd___unicode_descriptor_digitd);
DEFINE_PUBLIC_ALIAS(DOS$__unicode_descriptor_digitld, libd___unicode_descriptor_digitld);
DEFINE_PUBLIC_ALIAS(DOS$unicode_fold, libd_unicode_fold);

/* unistd */
DEFINE_PUBLIC_ALIAS(DOS$__pipe, libd_pipe);
DEFINE_PUBLIC_ALIAS(DOS$__libc_pipe, libd_pipe);
DEFINE_PUBLIC_ALIAS(DOS$pipe, libd_pipe);
DEFINE_PUBLIC_ALIAS(DOS$sleep, libd_sleep);
DEFINE_PUBLIC_ALIAS(DOS$_commit, libd_fsync);
DEFINE_PUBLIC_ALIAS(DOS$__fsync, libd_fsync);
DEFINE_PUBLIC_ALIAS(DOS$__libc_fsync, libd_fsync);
DEFINE_PUBLIC_ALIAS(DOS$fsync, libd_fsync);
DEFINE_PUBLIC_ALIAS(DOS$__setpgid, libd_setpgid);
DEFINE_PUBLIC_ALIAS(DOS$__libc_setpgid, libd_setpgid);
DEFINE_PUBLIC_ALIAS(DOS$setpgid, libd_setpgid);
DEFINE_PUBLIC_ALIAS(DOS$__getgroups, libd_getgroups);
DEFINE_PUBLIC_ALIAS(DOS$__libc_getgroups, libd_getgroups);
DEFINE_PUBLIC_ALIAS(DOS$getgroups, libd_getgroups);
DEFINE_PUBLIC_ALIAS(DOS$__setuid, libd_setuid);
DEFINE_PUBLIC_ALIAS(DOS$__libc_setuid, libd_setuid);
DEFINE_PUBLIC_ALIAS(DOS$setuid, libd_setuid);
DEFINE_PUBLIC_ALIAS(DOS$__setgid, libd_setgid);
DEFINE_PUBLIC_ALIAS(DOS$__libc_setgid, libd_setgid);
DEFINE_PUBLIC_ALIAS(DOS$setgid, libd_setgid);
DEFINE_PUBLIC_ALIAS(DOS$__alarm, libd_alarm);
DEFINE_PUBLIC_ALIAS(DOS$__libc_alarm, libd_alarm);
DEFINE_PUBLIC_ALIAS(DOS$alarm, libd_alarm);
DEFINE_PUBLIC_ALIAS(DOS$__fpathconf, libd_fpathconf);
DEFINE_PUBLIC_ALIAS(DOS$fpathconf, libd_fpathconf);
DEFINE_PUBLIC_ALIAS(DOS$__ttyname, libd_ttyname);
DEFINE_PUBLIC_ALIAS(DOS$ttyname, libd_ttyname);
DEFINE_PUBLIC_ALIAS(DOS$__ttyname_r, libd_ttyname_r);
DEFINE_PUBLIC_ALIAS(DOS$ttyname_r, libd_ttyname_r);
DEFINE_PUBLIC_ALIAS(DOS$tcgetpgrp, libd_tcgetpgrp);
DEFINE_PUBLIC_ALIAS(DOS$tcsetpgrp, libd_tcsetpgrp);
DEFINE_PUBLIC_ALIAS(DOS$_read, libd_read);
DEFINE_PUBLIC_ALIAS(DOS$__read, libd_read);
DEFINE_PUBLIC_ALIAS(DOS$__libc_read, libd_read);
DEFINE_PUBLIC_ALIAS(DOS$read, libd_read);
DEFINE_PUBLIC_ALIAS(DOS$_write, libd_write);
DEFINE_PUBLIC_ALIAS(DOS$__write, libd_write);
DEFINE_PUBLIC_ALIAS(DOS$__libc_write, libd_write);
DEFINE_PUBLIC_ALIAS(DOS$write, libd_write);
DEFINE_PUBLIC_ALIAS(DOS$readall, libd_readall);
#include <bits/crt/format-printer.h>
#if defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__
DEFINE_PUBLIC_ALIAS(DOS$write_printer, libd_writeall);
#endif /* __LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_INT__ == __SIZEOF_POINTER__ */
DEFINE_PUBLIC_ALIAS(DOS$writeall, libd_writeall);
DEFINE_PUBLIC_ALIAS(DOS$_lseek, libd_lseek);
DEFINE_PUBLIC_ALIAS(DOS$__lseek, libd_lseek);
DEFINE_PUBLIC_ALIAS(DOS$__libc_lseek, libd_lseek);
DEFINE_PUBLIC_ALIAS(DOS$lseek, libd_lseek);
DEFINE_PUBLIC_ALIAS(DOS$_isatty, libd_isatty);
DEFINE_PUBLIC_ALIAS(DOS$__isatty, libd_isatty);
DEFINE_PUBLIC_ALIAS(DOS$isatty, libd_isatty);
DEFINE_PUBLIC_ALIAS(DOS$_dup, libd_dup);
DEFINE_PUBLIC_ALIAS(DOS$__dup, libd_dup);
DEFINE_PUBLIC_ALIAS(DOS$__libc_dup, libd_dup);
DEFINE_PUBLIC_ALIAS(DOS$dup, libd_dup);
DEFINE_PUBLIC_ALIAS(DOS$_close, libd_close);
DEFINE_PUBLIC_ALIAS(DOS$__close, libd_close);
DEFINE_PUBLIC_ALIAS(DOS$__libc_close, libd_close);
DEFINE_PUBLIC_ALIAS(DOS$__close_nocancel, libd_close);
DEFINE_PUBLIC_ALIAS(DOS$close, libd_close);
DEFINE_PUBLIC_ALIAS(DOS$_lseeki64, libd_lseek64);
DEFINE_PUBLIC_ALIAS(DOS$llseek, libd_lseek64);
DEFINE_PUBLIC_ALIAS(DOS$__llseek, libd_lseek64);
DEFINE_PUBLIC_ALIAS(DOS$__libc_lseek64, libd_lseek64);
DEFINE_PUBLIC_ALIAS(DOS$__sys_llseek, libd_lseek64);
DEFINE_PUBLIC_ALIAS(DOS$lseek64, libd_lseek64);
DEFINE_PUBLIC_ALIAS(DOS$__libc_pread, libd_pread);
DEFINE_PUBLIC_ALIAS(DOS$pread, libd_pread);
DEFINE_PUBLIC_ALIAS(DOS$__libc_pwrite, libd_pwrite);
DEFINE_PUBLIC_ALIAS(DOS$pwrite, libd_pwrite);
DEFINE_PUBLIC_ALIAS(DOS$preadall, libd_preadall);
DEFINE_PUBLIC_ALIAS(DOS$pwriteall, libd_pwriteall);
DEFINE_PUBLIC_ALIAS(DOS$__pread64, libd_pread64);
DEFINE_PUBLIC_ALIAS(DOS$__libc_pread64, libd_pread64);
DEFINE_PUBLIC_ALIAS(DOS$pread64, libd_pread64);
DEFINE_PUBLIC_ALIAS(DOS$__pwrite64, libd_pwrite64);
DEFINE_PUBLIC_ALIAS(DOS$__libc_pwrite64, libd_pwrite64);
DEFINE_PUBLIC_ALIAS(DOS$pwrite64, libd_pwrite64);
DEFINE_PUBLIC_ALIAS(DOS$preadall64, libd_preadall64);
DEFINE_PUBLIC_ALIAS(DOS$pwriteall64, libd_pwriteall64);
DEFINE_PUBLIC_ALIAS(DOS$pipe2, libd_pipe2);
DEFINE_PUBLIC_ALIAS(DOS$syncfs, libd_syncfs);
DEFINE_PUBLIC_ALIAS(DOS$__group_member, libd_group_member);
DEFINE_PUBLIC_ALIAS(DOS$group_member, libd_group_member);
DEFINE_PUBLIC_ALIAS(DOS$getresuid, libd_getresuid);
DEFINE_PUBLIC_ALIAS(DOS$getresgid, libd_getresgid);
DEFINE_PUBLIC_ALIAS(DOS$setresuid, libd_setresuid);
DEFINE_PUBLIC_ALIAS(DOS$setresgid, libd_setresgid);
DEFINE_PUBLIC_ALIAS(DOS$usleep, libd_usleep);
DEFINE_PUBLIC_ALIAS(DOS$ualarm, libd_ualarm);
DEFINE_PUBLIC_ALIAS(DOS$__fchown, libd_fchown);
DEFINE_PUBLIC_ALIAS(DOS$__libc_fchown, libd_fchown);
DEFINE_PUBLIC_ALIAS(DOS$fchown, libd_fchown);
DEFINE_PUBLIC_ALIAS(DOS$__fchdir, libd_fchdir);
DEFINE_PUBLIC_ALIAS(DOS$__libc_fchdir, libd_fchdir);
DEFINE_PUBLIC_ALIAS(DOS$fchdir, libd_fchdir);
DEFINE_PUBLIC_ALIAS(DOS$__getpgid, libd_getpgid);
DEFINE_PUBLIC_ALIAS(DOS$__libc_getpgid, libd_getpgid);
DEFINE_PUBLIC_ALIAS(DOS$__bsd_getpgrp, libd_getpgid);
DEFINE_PUBLIC_ALIAS(DOS$getpgid, libd_getpgid);
DEFINE_PUBLIC_ALIAS(DOS$__getsid, libd_getsid);
DEFINE_PUBLIC_ALIAS(DOS$__libc_getsid, libd_getsid);
DEFINE_PUBLIC_ALIAS(DOS$getsid, libd_getsid);
DEFINE_PUBLIC_ALIAS(DOS$fexecve, libd_fexecve);
DEFINE_PUBLIC_ALIAS(DOS$__nice, libd_nice);
DEFINE_PUBLIC_ALIAS(DOS$__libc_nice, libd_nice);
DEFINE_PUBLIC_ALIAS(DOS$nice, libd_nice);
DEFINE_PUBLIC_ALIAS(DOS$confstr, libd_confstr);
DEFINE_PUBLIC_ALIAS(DOS$__setreuid, libd_setreuid);
DEFINE_PUBLIC_ALIAS(DOS$__libc_setreuid, libd_setreuid);
DEFINE_PUBLIC_ALIAS(DOS$setreuid, libd_setreuid);
DEFINE_PUBLIC_ALIAS(DOS$__setregid, libd_setregid);
DEFINE_PUBLIC_ALIAS(DOS$__libc_setregid, libd_setregid);
DEFINE_PUBLIC_ALIAS(DOS$setregid, libd_setregid);
DEFINE_PUBLIC_ALIAS(DOS$seteuid, libd_seteuid);
DEFINE_PUBLIC_ALIAS(DOS$setegid, libd_setegid);
DEFINE_PUBLIC_ALIAS(DOS$getlogin_r, libd_getlogin_r);
DEFINE_PUBLIC_ALIAS(DOS$__gethostname, libd_gethostname);
DEFINE_PUBLIC_ALIAS(DOS$gethostname, libd_gethostname);
DEFINE_PUBLIC_ALIAS(DOS$setlogin, libd_setlogin);
DEFINE_PUBLIC_ALIAS(DOS$__sethostname, libd_sethostname);
DEFINE_PUBLIC_ALIAS(DOS$__libc_sethostname, libd_sethostname);
DEFINE_PUBLIC_ALIAS(DOS$sethostname, libd_sethostname);
DEFINE_PUBLIC_ALIAS(DOS$sethostid, libd_sethostid);
DEFINE_PUBLIC_ALIAS(DOS$getdomainname, libd_getdomainname);
DEFINE_PUBLIC_ALIAS(DOS$__setdomainname, libd_setdomainname);
DEFINE_PUBLIC_ALIAS(DOS$__libc_setdomainname, libd_setdomainname);
DEFINE_PUBLIC_ALIAS(DOS$setdomainname, libd_setdomainname);
DEFINE_PUBLIC_ALIAS(DOS$profil, libd_profil);
DEFINE_PUBLIC_ALIAS(DOS$daemon, libd_daemon);
DEFINE_PUBLIC_ALIAS(DOS$revoke, libd_revoke);
DEFINE_PUBLIC_ALIAS(DOS$syscall, libd_syscall);
DEFINE_PUBLIC_ALIAS(DOS$__syscall, libd_syscall64);
DEFINE_PUBLIC_ALIAS(DOS$syscall64, libd_syscall64);
DEFINE_PUBLIC_ALIAS(DOS$getpassphrase, libd_getpass);
DEFINE_PUBLIC_ALIAS(DOS$getpass, libd_getpass);
DEFINE_PUBLIC_ALIAS(DOS$_chsize, libd_ftruncate);
DEFINE_PUBLIC_ALIAS(DOS$__ftruncate, libd_ftruncate);
DEFINE_PUBLIC_ALIAS(DOS$__libc_ftruncate, libd_ftruncate);
DEFINE_PUBLIC_ALIAS(DOS$chsize, libd_ftruncate);
DEFINE_PUBLIC_ALIAS(DOS$ftruncate, libd_ftruncate);
DEFINE_PUBLIC_ALIAS(DOS$_chsize_s, libd_ftruncate64);
DEFINE_PUBLIC_ALIAS(DOS$ftruncate64, libd_ftruncate64);
DEFINE_PUBLIC_ALIAS(DOS$__brk, libd_brk);
DEFINE_PUBLIC_ALIAS(DOS$brk, libd_brk);
DEFINE_PUBLIC_ALIAS(DOS$__sbrk, libd_sbrk);
DEFINE_PUBLIC_ALIAS(DOS$sbrk, libd_sbrk);
DEFINE_PUBLIC_ALIAS(DOS$__fdatasync, libd_fdatasync);
DEFINE_PUBLIC_ALIAS(DOS$__libc_fdatasync, libd_fdatasync);
DEFINE_PUBLIC_ALIAS(DOS$__libc_fsync, libd_fdatasync);
DEFINE_PUBLIC_ALIAS(DOS$fdatasync, libd_fdatasync);
DEFINE_PUBLIC_ALIAS(DOS$_swab, libd_swab);
DEFINE_PUBLIC_ALIAS(DOS$swab, libd_swab);
DEFINE_PUBLIC_ALIAS(DOS$ctermid, libd_ctermid);
DEFINE_PUBLIC_ALIAS(DOS$cuserid, libd_cuserid);
DEFINE_PUBLIC_ALIAS(DOS$getpassfd, libd_getpassfd);
DEFINE_PUBLIC_ALIAS(DOS$getpass_r, libd_getpass_r);
DEFINE_PUBLIC_ALIAS(DOS$setmode, libd_setmode);
DEFINE_PUBLIC_ALIAS(DOS$getmode, libd_getmode);
DEFINE_PUBLIC_ALIAS(DOS$getpeereid, libd_getpeereid);
DEFINE_PUBLIC_ALIAS(DOS$setruid, libd_setruid);
DEFINE_PUBLIC_ALIAS(DOS$setrgid, libd_setrgid);
DEFINE_PUBLIC_ALIAS(DOS$ctermid_r, libd_ctermid_r);
DEFINE_PUBLIC_ALIAS(DOS$__sysconf, libd_sysconf);
DEFINE_PUBLIC_ALIAS(DOS$sysconf, libd_sysconf);
DEFINE_PUBLIC_ALIAS(DOS$closefrom, libd_closefrom);
DEFINE_PUBLIC_ALIAS(DOS$close_range, libd_close_range);
DEFINE_PUBLIC_ALIAS(DOS$_tell, libd_tell);
DEFINE_PUBLIC_ALIAS(DOS$tell, libd_tell);
DEFINE_PUBLIC_ALIAS(DOS$_telli64, libd_tell64);
DEFINE_PUBLIC_ALIAS(DOS$tell64, libd_tell64);
DEFINE_PUBLIC_ALIAS(DOS$__read_nocancel, libd___read_nocancel);
DEFINE_PUBLIC_ALIAS(DOS$__write_nocancel, libd___write_nocancel);
DEFINE_PUBLIC_ALIAS(DOS$__pread64_nocancel, libd___pread64_nocancel);

/* util */
DEFINE_PUBLIC_ALIAS(DOS$opendev, libd_opendev);
DEFINE_PUBLIC_ALIAS(DOS$fparseln, libd_fparseln);

/* utime */
DEFINE_PUBLIC_ALIAS(DOS$_futime, libd_futime);
DEFINE_PUBLIC_ALIAS(DOS$_futime32, libd_futime);
DEFINE_PUBLIC_ALIAS(DOS$futime, libd_futime);
DEFINE_PUBLIC_ALIAS(DOS$_futime64, libd_futime64);
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(DOS$futime64, libd_futime64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* utmp */
DEFINE_PUBLIC_ALIAS(DOS$login_tty, libd_login_tty);
DEFINE_PUBLIC_ALIAS(DOS$login, libd_login);
DEFINE_PUBLIC_ALIAS(DOS$logout, libd_logout);
DEFINE_PUBLIC_ALIAS(DOS$logwtmp, libd_logwtmp);
DEFINE_PUBLIC_ALIAS(DOS$updwtmp, libd_updwtmp);
DEFINE_PUBLIC_ALIAS(DOS$__utmpname, libd_utmpname);
DEFINE_PUBLIC_ALIAS(DOS$utmpname, libd_utmpname);
DEFINE_PUBLIC_ALIAS(DOS$getutid, libd_getutid);
DEFINE_PUBLIC_ALIAS(DOS$getutline, libd_getutline);
DEFINE_PUBLIC_ALIAS(DOS$_pututline, libd_pututline);
DEFINE_PUBLIC_ALIAS(DOS$__pututline, libd_pututline);
DEFINE_PUBLIC_ALIAS(DOS$pututline, libd_pututline);
DEFINE_PUBLIC_ALIAS(DOS$__getutent_r, libd_getutent_r);
DEFINE_PUBLIC_ALIAS(DOS$getutent_r, libd_getutent_r);
DEFINE_PUBLIC_ALIAS(DOS$__getutid_r, libd_getutid_r);
DEFINE_PUBLIC_ALIAS(DOS$getutid_r, libd_getutid_r);
DEFINE_PUBLIC_ALIAS(DOS$__getutline_r, libd_getutline_r);
DEFINE_PUBLIC_ALIAS(DOS$getutline_r, libd_getutline_r);

/* utmpx */
DEFINE_PUBLIC_ALIAS(DOS$getutxid, libd_getutxid);
DEFINE_PUBLIC_ALIAS(DOS$getutxline, libd_getutxline);
DEFINE_PUBLIC_ALIAS(DOS$pututxline, libd_pututxline);
DEFINE_PUBLIC_ALIAS(DOS$utmpxname, libd_utmpxname);
DEFINE_PUBLIC_ALIAS(DOS$updwtmpx, libd_updwtmpx);
DEFINE_PUBLIC_ALIAS(DOS$getutmp, libd_getutmp);
DEFINE_PUBLIC_ALIAS(DOS$getutmpx, libd_getutmpx);

/* vis */
DEFINE_PUBLIC_ALIAS(DOS$vis, libd_vis);
DEFINE_PUBLIC_ALIAS(DOS$nvis, libd_nvis);
DEFINE_PUBLIC_ALIAS(DOS$svis, libd_svis);
DEFINE_PUBLIC_ALIAS(DOS$snvis, libd_snvis);
DEFINE_PUBLIC_ALIAS(DOS$strvis, libd_strvis);
DEFINE_PUBLIC_ALIAS(DOS$stravis, libd_stravis);
DEFINE_PUBLIC_ALIAS(DOS$strnvis_netbsd, libd_strnvis_netbsd);
DEFINE_PUBLIC_ALIAS(DOS$strnvis, libd_strnvis);
DEFINE_PUBLIC_ALIAS(DOS$strsvis, libd_strsvis);
DEFINE_PUBLIC_ALIAS(DOS$strsnvis, libd_strsnvis);
DEFINE_PUBLIC_ALIAS(DOS$strvisx, libd_strvisx);
DEFINE_PUBLIC_ALIAS(DOS$strnvisx, libd_strnvisx);
DEFINE_PUBLIC_ALIAS(DOS$strenvisx, libd_strenvisx);
DEFINE_PUBLIC_ALIAS(DOS$strsvisx, libd_strsvisx);
DEFINE_PUBLIC_ALIAS(DOS$strsnvisx, libd_strsnvisx);
DEFINE_PUBLIC_ALIAS(DOS$strsenvisx, libd_strsenvisx);
DEFINE_PUBLIC_ALIAS(DOS$strunvis, libd_strunvis);
DEFINE_PUBLIC_ALIAS(DOS$strnunvis_netbsd, libd_strnunvis_netbsd);
DEFINE_PUBLIC_ALIAS(DOS$strnunvis, libd_strnunvis);
DEFINE_PUBLIC_ALIAS(DOS$strunvisx, libd_strunvisx);
DEFINE_PUBLIC_ALIAS(DOS$strnunvisx, libd_strnunvisx);
DEFINE_PUBLIC_ALIAS(DOS$unvis, libd_unvis);

/* wchar */
DEFINE_PUBLIC_ALIAS(DOS$mbsinit, libd_mbsinit);
DEFINE_PUBLIC_ALIAS(DOS$fwide, libd_fwide);

/* wctype */
DEFINE_PUBLIC_ALIAS(DOS$wctrans, libd_wctrans);
DEFINE_PUBLIC_ALIAS(DOS$wctype, libd_wctype);
DEFINE_PUBLIC_ALIAS(DOS$__wctype_l, libd_wctype_l);
DEFINE_PUBLIC_ALIAS(DOS$wctype_l, libd_wctype_l);
DEFINE_PUBLIC_ALIAS(DOS$__wctrans_l, libd_wctrans_l);
DEFINE_PUBLIC_ALIAS(DOS$wctrans_l, libd_wctrans_l);
DEFINE_PUBLIC_ALIAS(DOS$isleadbyte, libd_isleadbyte);
DEFINE_PUBLIC_ALIAS(DOS$_isleadbyte_l, libd__isleadbyte_l);

/* wordexp */
DEFINE_PUBLIC_ALIAS(DOS$wordexp, libd_wordexp);
DEFINE_PUBLIC_ALIAS(DOS$wordfree, libd_wordfree);
