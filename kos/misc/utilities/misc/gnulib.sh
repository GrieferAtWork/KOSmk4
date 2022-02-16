# Copyright (c) 2019-2022 Griefer@Work
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgement (see the following) in the product
#    documentation is required:
#    Portions Copyright (c) 2019-2022 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

############################################################################
# Various hacks to satisfy gnulib configure scripts
#
# Created manually by grep-ing gnulib's /m4 folder for `AC_RUN_IFELSE`,
# and going through all of the results to gather variable names, as well
# as determine if the respective feature is present on KOS.
############################################################################

############################################################################
# Options we intentionally don't set (because they're too CPU-specific):
# - gl_cv_cc_double_expbit0
# - gl_cv_cc_float_expbit0
# - gl_cv_cc_long_double_expbit0
############################################################################

. "$KOS_MISC/utilities/misc/target-info.sh"

PACKAGE_CONFIG_SITE="
ac_cv_func__set_invalid_parameter_handler=no            # We might emulate it, but not by default; plus: this tends to screw up a bunch of stuff...
gl_cv_func_aligned_alloc_works=yes                      # aligned_alloca()
ac_cv_c_stack_direction=$TARGET_CONFIG_STACK_DIRECTION
gl_cv_func_btowc_nul=yes                                # assert(btowc(0) == 0)
gl_cv_func_btowc_eof=yes                                # assert(btowc(EOF) == WEOF)
gl_cv_func_c32rtomb_retval=yes                          # assert(c32rtomb (NULL, 0, NULL) == 1)
ac_cv_func_calloc_0_nonnull=yes                         # assert(calloc(0, 0) != NULL)
gl_cv_func_realpath_works=yes                           # realpath(3)
gl_cv_func_cbrtf_works=yes
gl_cv_func_cbrtl_ieee=yes
gl_cv_func_cbrtl_works=yes
gl_cv_func_ceil_ieee=yes
gl_cv_func_ceilf_ieee=yes
gl_cv_func_ceill_ieee=yes
gl_cv_func_ceill_works=yes
ac_cv_func_chown_works=yes
gl_cv_func_chown_slash_works=yes                        # symlink(\"file\", \"link\"); assert(chown(\"link/\") != 0)
gl_cv_func_chown_ctime_works=no                         # symlink(3) updates st_ctime (doesn't on KOS, where st_ctime is file-creation time)
gl_cv_func_chown_follows_symlink=yes
gl_cv_struct_dirent_d_ino=yes
gl_cv_func_dup_works=yes
gl_cv_func_dup2_works=yes
gl_cv_func_duplocale_works=yes
gl_cv_func_exp2_works=yes
gl_cv_func_exp2l_works=yes
gl_cv_func_exp2l_ieee=yes
gl_cv_func_expl_works=yes
gl_cv_func_expm1_ieee=yes
gl_cv_func_expm1f_ieee=yes
gl_cv_func_expm1f_works=yes
gl_cv_func_expm1l_works=yes
gl_cv_func_fabsl_works=yes
gl_cv_func_open_directory_works=yes                     # assert(open(\".\", O_RDONLY) != -1)
gl_cv_func_fchmodat_works=yes
gl_cv_func_fchownat_nofollow_works=yes                  # AT_SYMLINK_NOFOLLOW
gl_cv_func_fchownat_empty_filename_works=yes            # assert(fchownat(fd, \"\", ...) != 0)
gl_cv_func_fclose_stdin=yes
gl_cv_func_fcntl_f_dupfd_works=yes
gl_cv_func_fcntl_f_dupfd_cloexec=yes
gl_cv_header_working_fcntl_h=yes
gl_cv_func_fdopen_works=yes
gl_cv_func_fdopendir_works=yes
gl_cv_func_fflush_stdin=yes
gl_cv_func_ffsll_works=yes
gl_cv_func_floor_ieee=yes
gl_cv_func_floorf_ieee=yes
gl_cv_func_fma_works=yes
gl_cv_func_fmaf_works=yes
gl_cv_func_fmal_works=yes
gl_cv_func_fmod_ieee=yes
gl_cv_func_fmodf_ieee=yes
gl_cv_func_fmodl_ieee=yes
gl_cv_func_fnmatch_posix=yes
gl_cv_func_fnmatch_gnu=yes    # GNU extensions (s.a. __USE_GNU in <fnmatch.h>)
gl_cv_func_fopen_slash=yes    # assert(fopen(\"foo/\") == NULL)
gl_cv_func_fopen_mode_x=yes   # Support for \"x\" option
gl_cv_func_fopen_mode_e=yes   # Support for \"e\" option
gl_cv_func_fpurge_works=yes
gl_cv_func_freopen_works_on_closed=yes   # freopen() works after close(fileno())
gl_cv_func_frexp_works=yes
gl_cv_func_frexpf_works=yes
gl_cv_func_frexpl_works=yes
gl_cv_func_fstatat_zero_flag=yes   # assert(fstatat(AT_FDCWD, \".\", atflags: 0) == 0)
fu_cv_sys_stat_statfs2_frsize=yes  # DECLARED(statfs(char const *file, struct statfs *buf)) && EXISTS(struct statfs::f_frsize)
fu_cv_sys_stat_statfs3_osf1=no     # Some other statfs() variant
fu_cv_sys_stat_statfs2_bsize=yes   # DECLARED(statfs(char const *file, struct statfs *buf)) && EXISTS(struct statfs::f_bsize)
fu_cv_sys_stat_statfs4=no          # Some other statfs() variant
gl_cv_func_ftello_works=yes
gl_cv_func_futimens_works=yes
gl_cv_func_getcwd_null=yes         # assert(getcwd(NULL, 0) != NULL)   -- malloc'd buffer
gl_cv_func_getcwd_succeeds_beyond_4k=yes  # getcwd() with strlen(\$PWD) >= 4096 works  (KOS never imposes path limits, so: yes)
gl_cv_func_getcwd_path_max=yes            # getcwd() works for paths > PATH_MAX        (KOS never imposes path limits, so: yes)
gl_cv_func_working_getdelim=yes
gl_cv_func_getdtablesize_works=yes
ac_cv_func_getgroups_works=yes            # assert(getgroups(0, NULL) != -1)
gl_cv_func_getgroups_works=yes            # assert(getgroups(-1, list) == -1)
am_cv_func_working_getline=yes
gl_cv_func_getlogin_r_works=yes
gl_cv_func_getopt_posix=yes
gl_cv_func_getopt_gnu=yes
gl_cv_func_getopt_long_gnu=yes
gl_cv_glob_lists_symlinks=yes    # If a program ever needs it, _I_ want to implement it!
gl_cv_func_hypot_ieee=yes
gl_cv_func_hypotf_ieee=yes
gl_cv_func_hypotf_works=yes
gl_cv_func_hypotl_ieee=yes
gl_cv_func_hypotl_works=yes
am_cv_func_iconv_works=yes
gl_cv_func_iconv_supports_utf=yes
gl_cv_func_ilogb_works=yes
gl_cv_func_ilogbf_works=yes
gl_cv_func_ilogbl_works=yes
gl_cv_func_itold_works=yes
gt_cv_locale_fake=no
gt_cv_func_uselocale_works=yes
gl_cv_pipes_are_fifos=yes       # fstate(pipe()) --> S_IFIFO
gl_cv_func_isfinitel_works=yes
gl_cv_func_isinfl_works=yes
gl_cv_func_isnanf_works=yes
gl_cv_func_isnanl_works=yes
gl_cv_func_iswdigit_works=yes
gl_cv_func_iswxdigit_works=yes
gl_cv_func_ldexpl_works=yes
gl_cv_func_link_works=yes
gl_cv_func_linkat_nofollow=yes
gl_cv_func_linkat_slash=yes
gl_cv_func_link_follows_symlink=no  # link(symlink) creates hard-links of symlinks; use AT_SYMLINK_FOLLOW to follow them
gl_cv_func_log_ieee=yes
gl_cv_func_log_works=yes
gl_cv_func_log1p_ieee=yes
gl_cv_func_log1pf_ieee=yes
gl_cv_func_log1pf_works=yes
gl_cv_func_log1pl_ieee=yes
gl_cv_func_log1pl_works=yes
gl_cv_func_log2_ieee=yes
gl_cv_func_log2_works=yes
gl_cv_func_log2f_ieee=yes
gl_cv_func_log2f_works=yes
gl_cv_func_log2l_works=yes
gl_cv_func_log10_ieee=yes
gl_cv_func_log10_works=yes
gl_cv_func_log10f_ieee=yes
gl_cv_func_log10f_works=yes
gl_cv_func_log10l_works=yes
gl_cv_func_logb_works=yes
gl_cv_func_logbf_works=yes
gl_cv_func_logbl_works=yes
gl_cv_func_logf_ieee=yes
gl_cv_func_logf_works=yes
gl_cv_func_logl_works=yes
ac_cv_type_long_long_int=yes                       # At least with gcc
gl_cv_func_lstat_dereferences_slashed_symlink=yes  # lstat(\"symlink/\") still dereferences (yes, it does on KOS)
ac_cv_func_malloc_0_nonnull=yes                    # assert(malloc(0) != NULL)
gl_cv_malloc_alignment=$TARGET_CONFIG_ALIGNOF_MAXALIGN_T
gl_cv_func_mbrlen_incomplete_state=yes
gl_cv_func_mbrlen_retval=yes
gl_cv_func_mbrlen_nul_retval=yes
gl_cv_func_mbrlen_empty_input=yes
gl_cv_func_mbrtoc32_empty_input=yes
gl_cv_func_mbrtoc32_C_locale_sans_EILSEQ=no   # our C locale is utf-8, so e.g.: mbrtoc32(&wc, \"\\x80\", 1, &mbs) == (size_t)-2   (-2: incomplete sequence)
gl_cv_func_mbrtoc32_sanitycheck=yes
gl_cv_func_mbrtowc_incomplete_state=yes
gl_cv_func_mbrtowc_sanitycheck=yes
gl_cv_func_mbrtowc_null_arg1=yes
gl_cv_func_mbrtowc_null_arg2=yes
gl_cv_func_mbrtowc_retval=yes
gl_cv_func_mbrtowc_nul_retval=yes
gl_cv_func_mbrtowc_stores_incomplete=yes
gl_cv_func_mbrtowc_empty_input=yes
gl_cv_func_mbrtowc_C_locale_sans_EILSEQ=yes   # our C locale is utf-8, so e.g.: mbrtowc(&wc, \"\\x80\", 1, &mbs) == (size_t)-2   (-2: incomplete sequence)
gl_cv_func_mbsnrtowcs_works_in_traditional_locale=yes
gl_cv_func_mbsrtowcs_works=yes
gl_cv_func_memalign_works=yes
gl_cv_func_memchr_works=yes
gl_cv_func_memcmp_working=yes
gl_cv_func_memmem_works_always=yes          # We actually have 2 memmem() versions (s.a. _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE; but the regular one is standard-conforming)
gl_cv_func_memmem_works_fast=yes            # Yes: our memmem() does a memchr(needle[0]) to filter candidates, so its the \"fast\" variant
gl_cv_func_mkdir_trailing_slash_works=yes   # assert(mkdir(\"foo/\") == 0)
gl_cv_func_mkdir_trailing_dot_works=yes     # assert(mkdir(\"foo/./\") != 0)
gl_cv_func_mkfifo_works=yes                 # assert(mkfifo(\"foo/\") != 0)
gl_cv_func_mkfifoat_works=yes               # assert(mkfifoat(\"foo/\") != 0)
gl_cv_func_mknod_works=yes                  # mknod() can create FIFO w/o root (yes; that works on KOS)
gl_cv_func_working_mkstemp=yes
gl_cv_func_working_mktime=yes
gl_cv_func_modf_ieee=yes
gl_cv_func_modff_ieee=yes
gl_cv_func_modfl_ieee=yes
gl_cv_func_mprotect_works=yes
gl_cv_func_nanosleep=yes
gl_cv_func_nl_langinfo_yesexpr_works=yes   # assert(strcmp(nl_langinfo(YESEXPR), \"\") != 0)
gl_cv_func_open_slash=yes                  # assert(open(\"file/\") == -1)
gl_cv_func_perror_works=yes
ac_cv_func_poll=yes
gl_cv_func_poll=yes
gl_cv_func_popen_works=yes
gl_cv_func_posix_memalign_works=yes
gl_cv_func_posix_spawn_works=yes
gl_cv_func_posix_spawn_secure_exec=yes   # Yes, our posix_spawn() doesn't accept shell-scripts w/o #!-marker
gl_cv_func_posix_spawnp_secure_exec=yes  # *ditto*
gl_cv_func_posix_spawn_file_actions_addclose_works=yes
gl_cv_func_posix_spawn_file_actions_adddup2_works=yes
gl_cv_func_posix_spawn_file_actions_addopen_works=yes
gl_cv_func_pread_works=yes
gl_cv_func_printf_sizes_c99=yes
gl_cv_func_printf_long_double=yes
gl_cv_func_printf_infinite=yes
gl_cv_func_printf_infinite_long_double=yes
gl_cv_func_printf_directive_a=yes
gl_cv_func_printf_directive_f=yes
gl_cv_func_printf_directive_n=yes
gl_cv_func_printf_directive_ls=yes
gl_cv_func_printf_positions=yes      # Probably someday... (but already say we do)
gl_cv_func_printf_flag_grouping=yes
gl_cv_func_printf_flag_leftadjust=yes
gl_cv_func_printf_flag_zero=yes
gl_cv_func_printf_precision=yes
gl_cv_func_snprintf_truncation_c99=yes   # Yes, we do this now. But once-upon-a-time, this was a bug (s.a. snprintf(3))
gl_cv_func_snprintf_retval_c99=yes
gl_cv_func_snprintf_directive_n=yes
gl_cv_func_snprintf_size1=yes
gl_cv_func_vsnprintf_zerosize_c99=yes
gl_cv_func_pselect_detects_ebadf=yes
gl_cv_pthread_rwlock_rdlock_prefer_writer=no   # No, on KOS readers are preferred
gl_cv_func_pthread_sigmask_in_libc_works=yes   # Yes, we have pthread_sigmask() w/o -lpthread (actually, we don't have -lpthread)
gl_cv_func_pthread_sigmask_return_works=yes
gl_cv_func_pthread_sigmask_unblock_works=yes
gl_cv_func_ptsname_sets_errno=yes
gl_cv_func_ptsname_r_retval_ok=yes
gl_cv_func_isatty_sets_errno=yes
gl_cv_func_svid_putenv=yes
gl_cv_func_pwrite_works=yes
gl_cv_func_readlink_trailing_slash=yes    # assert(readlink(\"file/\") == -1)
gl_cv_func_readlink_truncate=yes          # Oof; don't remind me (s.a. AT_READLINK_REQSIZE)
ac_cv_func_realloc_0_nonnull=yes          # assert(realloc(NULL, 0) != NULL)
gl_cv_func_re_compile_pattern_working=yes # Not yet, but hopefully someday
gl_cv_func_remainder_ieee=yes
gl_cv_func_remainderf_ieee=yes
gl_cv_func_remainderf_works=yes
gl_cv_func_remainderl_ieee=yes
gl_cv_func_remainderl_works=yes
gl_cv_func_remove_dir_works=yes           # Yes, remove() also removes directories (s.a. AT_REMOVEREG | AT_REMOVEDIR)
gl_cv_func_rename_slash_dst_works=yes     # FIXME: yeah, this one's not 100% (s.a. sys_renameat2_impl)
gl_cv_func_rename_slash_src_works=yes     # FIXME: *ditto*
gl_cv_func_rename_link_works=yes
gl_cv_func_rename_dest_works=yes
gl_cv_func_rintl_works=yes
gl_cv_func_rmdir_works=yes
gl_cv_func_rmdir_errno_not_empty=ENOTEMPTY
gl_cv_func_round_works=yes
gl_cv_func_round_ieee=yes
gl_cv_func_roundf_works=yes
gl_cv_func_roundf_ieee=yes
gl_cv_func_roundl_ieee=yes
gl_cv_func_select_supports0=yes   # select(0, NULL, NULL, NULL, ...) works
gl_cv_func_select_detects_ebadf=yes
gl_cv_func_setenv_works=yes
gl_cv_func_unsetenv_works=yes
gl_cv_func_setlocale_works=yes
sv_cv_sigaltstack=yes
sv_cv_sigaltstack_low_base=yes
gl_cv_func_signbit=yes
gl_cv_func_signbit_builtins=yes # At least on gcc
gl_cv_func_signbit_gcc=yes      # Alias used by older gnulibs
gl_cv_func_sleep_works=yes
gl_cv_func_sqrtl_works=yes
gl_cv_func_stat_file_slash=yes   # assert(stat(\"file/\") == -1)
gl_cv_header_working_stdint_h=yes
gl_cv_func_stpncpy=yes
gl_cv_func_strcasestr_works_always=yes
gl_cv_func_strcasestr_linear=yes
gl_cv_func_strchrnul_works=yes
gl_cv_func_working_strerror=yes
gl_cv_func_strerror_0_works=yes
gl_cv_func_strerror_r_works=yes
gl_cv_func_strerrorname_np_works=yes
gl_cv_strfmon_l_works=yes  # It doesn't, but I don't want it to be substituted; if it ends up needed, _I'll_ implement it
gl_cv_func_strncat_works=yes
gl_cv_func_strndup_works=yes
gl_cv_func_working_strsignal=yes
gl_cv_func_strstr_works_always=yes
gl_cv_func_strstr_linear=yes
gl_cv_func_strtod_works=yes
gl_cv_func_strtoimax=yes
gl_cv_func_strtok_r_works=yes
gl_cv_func_strtol_works=yes
gl_cv_func_strtold_works=yes
gl_cv_func_strtoll_works=yes
gl_cv_func_strtoul_works=yes
gl_cv_func_strtoull_works=yes
gl_cv_func_symlink_works=yes     # assert(symlink(\"content\", \"file/\") == -1)
gl_cv_func_symlinkat_works=yes   # assert(symlinkat(\"content\", \"file/\") == -1)
gl_cv_func_thrd_join_works=yes
gl_cv_have_weak=yes              # KOS uses ELF, so yes
gl_cv_func_localtime_works=yes
gl_cv_func_tmpfile_works=yes
gl_cv_func_trunc_ieee=yes
gl_cv_func_truncate_works=yes    # assert(truncate(\"file/\") == -1)
gl_cv_func_truncf_ieee=yes
gl_cv_func_truncl_works=yes
gl_cv_func_truncl_ieee=yes
gl_cv_func_tdelete_works=yes
gl_cv_func_ttyname_r_not_stub=yes
gl_cv_func_ttyname_r_works=yes
gl_cv_func_ungetc_works=yes
gl_cv_func_unlink_honors_slashes=yes    # assert(unlink(\"file/\") == -1)
gl_cv_func_unlink_parent_fails=yes      # assert(unlink(\"..\") == -1)
gl_cv_func_unlink_busy_text=yes         # assert(unlink(readlink(\"/proc/self/exe\")) == 0)   (yes: this works on KOS)
gl_cv_func_usleep_works=yes
gl_cv_func_utime_file_slash=yes         # assert(utime(\"file/\") == -1)
gl_cv_func_futimesat_works=yes          # assert(futimesat(fd, NULL, NULL) == 0)
gl_cv_func_utimensat_works=yes
gl_cv_func_working_utimes=yes
gl_cv_func_wcrtomb_works=yes
gl_cv_func_wcrtomb_retval=yes
gl_cv_func_wcsnrtombs_works_in_traditional_locale=yes
gl_cv_func_wcsrtombs_termination=yes
gl_cv_func_wcsrtombs_null=yes
gl_cv_func_wctob_works=yes
gl_cv_func_iswcntrl_works=yes
gl_cv_func_wcwidth_works=yes

# Some more found in nano
gl_cv_func_printf_enomem=yes
gt_cv_func_printf_posix=yes
gl_cv_func_gettimeofday_clobber=no      # No, our gettimeofday() doesn't clobber localtime(3)'s buffer
gt_cv_int_divbyzero_sigfpe=yes
gl_cv_C_locale_sans_EILSEQ=no
$PACKAGE_CONFIG_SITE
"
