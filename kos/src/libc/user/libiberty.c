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
#ifndef GUARD_LIBC_USER_LIBIBERTY_C
#define GUARD_LIBC_USER_LIBIBERTY_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>
#include <linux/kcmp.h>
#include <sys/stat.h>

#include <assert.h>
#include <syscall.h>
#include <unistd.h>

#include "libiberty.h"

DECL_BEGIN

/*[[[head:libc_xmalloc_set_program_name,hash:CRC-32=0x72744191]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") void
NOTHROW_NCX(LIBCCALL libc_xmalloc_set_program_name)(char const *progname)
/*[[[body:libc_xmalloc_set_program_name]]]*/
/*AUTO*/{
	(void)progname;
	CRT_UNIMPLEMENTEDF("xmalloc_set_program_name(%q)", progname); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_xmalloc_set_program_name]]]*/

/*[[[head:libc_xmalloc_failed,hash:CRC-32=0xc75654bd]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_NORETURN void
(LIBCCALL libc_xmalloc_failed)(size_t num_bytes) THROWS(...)
/*[[[body:libc_xmalloc_failed]]]*/
/*AUTO*/{
	(void)num_bytes;
	CRT_UNIMPLEMENTEDF("xmalloc_failed(%Ix)", num_bytes); /* TODO */
	assert_failed("Not implemented");
}
/*[[[end:libc_xmalloc_failed]]]*/

/*[[[head:libc_fdmatch,hash:CRC-32=0xd02e5611]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_fdmatch)(fd_t fd1,
                                   fd_t fd2)
/*[[[body:libc_fdmatch]]]*/
{
#ifdef SYS_kcmp
	pid_t mypid = getpid();
	syscall_slong_t status;
	status = sys_kcmp(mypid, mypid, KCMP_FILE, fd1, fd2);
	if (status >= 0)
		return status == 0; /* 0: `KCMP_ORDER_EQUAL' */
	libc_seterrno_neg(status);
	return 0;
#else /* SYS_kcmp */
	struct stat st1, st2;
	if (fstat(fd1, &st1) == 0 && fstat(fd2, &st2) == 0) {
		return st1.st_dev == st2.st_dev &&
		       st1.st_ino == st2.st_ino;
	}
	return 0;
#endif /* !SYS_kcmp */
}
/*[[[end:libc_fdmatch]]]*/

/*[[[head:libc_buildargv,hash:CRC-32=0xb8366de1]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char **
NOTHROW_NCX(LIBCCALL libc_buildargv)(char const *a)
/*[[[body:libc_buildargv]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("buildargv(%q)", a); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_buildargv]]]*/

/*[[[head:libc_expandargv,hash:CRC-32=0xd31d24f8]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") NONNULL((1, 2)) void
NOTHROW_NCX(LIBCCALL libc_expandargv)(int *p_argc,
                                      char ***p_argv)
/*[[[body:libc_expandargv]]]*/
/*AUTO*/{
	(void)p_argc;
	(void)p_argv;
	CRT_UNIMPLEMENTEDF("expandargv(%p, %p)", p_argc, p_argv); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_expandargv]]]*/

/*[[[head:libc_writeargv,hash:CRC-32=0x25e9e974]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") int
NOTHROW_NCX(LIBCCALL libc_writeargv)(char *const *argv,
                                     FILE *fp)
/*[[[body:libc_writeargv]]]*/
/*AUTO*/{
	(void)argv;
	(void)fp;
	CRT_UNIMPLEMENTEDF("writeargv(%p, %p)", argv, fp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_writeargv]]]*/

/*[[[head:libd_concat_copy2,hash:CRC-32=0x957c2430]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.libiberty") char *
NOTHROW_NCX(VLIBDCALL libd_concat_copy2)(char const *first,
                                         ...)
/*[[[body:libd_concat_copy2]]]*/
/*AUTO*/{
	(void)first;
	CRT_UNIMPLEMENTEDF("concat_copy2(%q, ...)", first); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_concat_copy2]]]*/

/*[[[head:libc_concat_copy2,hash:CRC-32=0x5022194d]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") char *
NOTHROW_NCX(VLIBCCALL libc_concat_copy2)(char const *first,
                                         ...)
/*[[[body:libc_concat_copy2]]]*/
/*AUTO*/{
	(void)first;
	CRT_UNIMPLEMENTEDF("concat_copy2(%q, ...)", first); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_concat_copy2]]]*/

/*[[[head:libc_get_run_time,hash:CRC-32=0xacb9a4aa]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") long
NOTHROW_NCX(LIBCCALL libc_get_run_time)(void)
/*[[[body:libc_get_run_time]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("get_run_time"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_get_run_time]]]*/

/*[[[head:libc_make_relative_prefix,hash:CRC-32=0x6ed98811]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_make_relative_prefix)(char const *a,
                                                char const *b,
                                                char const *c)
/*[[[body:libc_make_relative_prefix]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	CRT_UNIMPLEMENTEDF("make_relative_prefix(%q, %q, %q)", a, b, c); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_make_relative_prefix]]]*/

/*[[[head:libc_make_relative_prefix_ignore_links,hash:CRC-32=0x12954e87]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_make_relative_prefix_ignore_links)(const char *a,
                                                             const char *b,
                                                             const char *c)
/*[[[body:libc_make_relative_prefix_ignore_links]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	CRT_UNIMPLEMENTEDF("make_relative_prefix_ignore_links(%q, %q, %q)", a, b, c); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_make_relative_prefix_ignore_links]]]*/

/*[[[head:libc_choose_tmpdir,hash:CRC-32=0x3cecd4b]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_RETNONNULL WUNUSED const char *
NOTHROW_NCX(LIBCCALL libc_choose_tmpdir)(void)
/*[[[body:libc_choose_tmpdir]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("choose_tmpdir"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_choose_tmpdir]]]*/

/*[[[head:libc_choose_temp_base,hash:CRC-32=0x36925431]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_choose_temp_base)(void)
/*[[[body:libc_choose_temp_base]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("choose_temp_base"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_choose_temp_base]]]*/

/*[[[head:libc_make_temp_file,hash:CRC-32=0x65ba2155]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_make_temp_file)(char const *a)
/*[[[body:libc_make_temp_file]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("make_temp_file(%q)", a); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_make_temp_file]]]*/

/*[[[head:libc_make_temp_file_with_prefix,hash:CRC-32=0x7ef5c1f7]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_make_temp_file_with_prefix)(const char *a,
                                                      const char *b)
/*[[[body:libc_make_temp_file_with_prefix]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	CRT_UNIMPLEMENTEDF("make_temp_file_with_prefix(%q, %q)", a, b); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_make_temp_file_with_prefix]]]*/

/*[[[head:libc_unlink_if_ordinary,hash:CRC-32=0xddd3a563]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") int
NOTHROW_NCX(LIBCCALL libc_unlink_if_ordinary)(char const *a)
/*[[[body:libc_unlink_if_ordinary]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("unlink_if_ordinary(%q)", a); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_unlink_if_ordinary]]]*/

/*[[[head:libc_physmem_total,hash:CRC-32=0x9f48ae5c]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_CONST WUNUSED double
NOTHROW_NCX(LIBCCALL libc_physmem_total)(void)
/*[[[body:libc_physmem_total]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("physmem_total"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_physmem_total]]]*/

/*[[[head:libc_physmem_available,hash:CRC-32=0x9311214a]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_PURE WUNUSED double
NOTHROW_NCX(LIBCCALL libc_physmem_available)(void)
/*[[[body:libc_physmem_available]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("physmem_available"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_physmem_available]]]*/

/*[[[head:libc_xcrc32,hash:CRC-32=0x5bdf587a]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") unsigned int
NOTHROW_NCX(LIBCCALL libc_xcrc32)(unsigned char const *a,
                                  int b,
                                  unsigned int c)
/*[[[body:libc_xcrc32]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	CRT_UNIMPLEMENTEDF("xcrc32(%p, %x, %x)", a, b, c); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_xcrc32]]]*/

/*[[[head:libc_hex_init,hash:CRC-32=0xd35a74f8]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") void
NOTHROW_NCX(LIBCCALL libc_hex_init)(void)
/*[[[body:libc_hex_init]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("hex_init"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_hex_init]]]*/

/*[[[head:libc_pex_run,hash:CRC-32=0x586b8bbd]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") const char *
NOTHROW_NCX(LIBCCALL libc_pex_run)(struct pex_obj *obj,
                                   int flags,
                                   const char *executable,
                                   char *const *argv,
                                   const char *outname,
                                   const char *errname,
                                   int *err)
/*[[[body:libc_pex_run]]]*/
/*AUTO*/{
	(void)obj;
	(void)flags;
	(void)executable;
	(void)argv;
	(void)outname;
	(void)errname;
	(void)err;
	CRT_UNIMPLEMENTEDF("pex_run(%p, %x, %q, %p, %q, %q, %p)", obj, flags, executable, argv, outname, errname, err); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_pex_run]]]*/

/*[[[head:libc_pex_run_in_environment,hash:CRC-32=0xf718ce3b]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") const char *
NOTHROW_NCX(LIBCCALL libc_pex_run_in_environment)(struct pex_obj *obj,
                                                  int flags,
                                                  const char *executable,
                                                  char *const *argv,
                                                  char *const *env,
                                                  const char *outname,
                                                  const char *errname,
                                                  int *err)
/*[[[body:libc_pex_run_in_environment]]]*/
/*AUTO*/{
	(void)obj;
	(void)flags;
	(void)executable;
	(void)argv;
	(void)env;
	(void)outname;
	(void)errname;
	(void)err;
	CRT_UNIMPLEMENTEDF("pex_run_in_environment(%p, %x, %q, %p, %p, %q, %q, %p)", obj, flags, executable, argv, env, outname, errname, err); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_pex_run_in_environment]]]*/

/*[[[head:libc_pex_input_file,hash:CRC-32=0xb63b82c0]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") FILE *
NOTHROW_NCX(LIBCCALL libc_pex_input_file)(struct pex_obj *obj,
                                          int flags,
                                          const char *in_name)
/*[[[body:libc_pex_input_file]]]*/
/*AUTO*/{
	(void)obj;
	(void)flags;
	(void)in_name;
	CRT_UNIMPLEMENTEDF("pex_input_file(%p, %x, %q)", obj, flags, in_name); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_pex_input_file]]]*/

/*[[[head:libc_pex_input_pipe,hash:CRC-32=0x6b8b4300]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") FILE *
NOTHROW_NCX(LIBCCALL libc_pex_input_pipe)(struct pex_obj *obj,
                                          int binary)
/*[[[body:libc_pex_input_pipe]]]*/
/*AUTO*/{
	(void)obj;
	(void)binary;
	CRT_UNIMPLEMENTEDF("pex_input_pipe(%p, %x)", obj, binary); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_pex_input_pipe]]]*/

/*[[[head:libc_pex_read_output,hash:CRC-32=0x36027dcf]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") FILE *
NOTHROW_NCX(LIBCCALL libc_pex_read_output)(struct pex_obj *obj,
                                           int binary)
/*[[[body:libc_pex_read_output]]]*/
/*AUTO*/{
	(void)obj;
	(void)binary;
	CRT_UNIMPLEMENTEDF("pex_read_output(%p, %x)", obj, binary); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_pex_read_output]]]*/

/*[[[head:libc_pex_read_err,hash:CRC-32=0x994cafdd]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") FILE *
NOTHROW_NCX(LIBCCALL libc_pex_read_err)(struct pex_obj *obj,
                                        int binary)
/*[[[body:libc_pex_read_err]]]*/
/*AUTO*/{
	(void)obj;
	(void)binary;
	CRT_UNIMPLEMENTEDF("pex_read_err(%p, %x)", obj, binary); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_pex_read_err]]]*/

/*[[[head:libc_pex_get_status,hash:CRC-32=0x6f9bc095]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") int
NOTHROW_NCX(LIBCCALL libc_pex_get_status)(struct pex_obj *obj,
                                          int count,
                                          int *vector)
/*[[[body:libc_pex_get_status]]]*/
/*AUTO*/{
	(void)obj;
	(void)count;
	(void)vector;
	CRT_UNIMPLEMENTEDF("pex_get_status(%p, %x, %p)", obj, count, vector); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_pex_get_status]]]*/

/*[[[head:libc_pex_init,hash:CRC-32=0x785d8055]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") struct pex_obj *
NOTHROW_NCX(LIBCCALL libc_pex_init)(int flags,
                                    char const *pname,
                                    char const *tempbase)
/*[[[body:libc_pex_init]]]*/
/*AUTO*/{
	(void)flags;
	(void)pname;
	(void)tempbase;
	CRT_UNIMPLEMENTEDF("pex_init(%x, %q, %q)", flags, pname, tempbase); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_pex_init]]]*/

/*[[[head:libc_pex_get_times,hash:CRC-32=0xc9857d24]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") int
NOTHROW_NCX(LIBCCALL libc_pex_get_times)(struct pex_obj *obj,
                                         int count,
                                         struct pex_time *vector)
/*[[[body:libc_pex_get_times]]]*/
/*AUTO*/{
	(void)obj;
	(void)count;
	(void)vector;
	CRT_UNIMPLEMENTEDF("pex_get_times(%p, %x, %p)", obj, count, vector); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_pex_get_times]]]*/

/*[[[head:libc_pex_free,hash:CRC-32=0xd0d99d0b]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") void
NOTHROW_NCX(LIBCCALL libc_pex_free)(struct pex_obj *obj)
/*[[[body:libc_pex_free]]]*/
/*AUTO*/{
	(void)obj;
	CRT_UNIMPLEMENTEDF("pex_free(%p)", obj); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_pex_free]]]*/

/*[[[head:libc_pex_one,hash:CRC-32=0xb3939f44]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") const char *
NOTHROW_NCX(LIBCCALL libc_pex_one)(int flags,
                                   const char *executable,
                                   char *const *argv,
                                   const char *pname,
                                   const char *outname,
                                   const char *errname,
                                   int *status,
                                   int *err)
/*[[[body:libc_pex_one]]]*/
/*AUTO*/{
	(void)flags;
	(void)executable;
	(void)argv;
	(void)pname;
	(void)outname;
	(void)errname;
	(void)status;
	(void)err;
	CRT_UNIMPLEMENTEDF("pex_one(%x, %q, %p, %q, %q, %q, %p, %p)", flags, executable, argv, pname, outname, errname, status, err); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_pex_one]]]*/

/*[[[head:libc_pexecute,hash:CRC-32=0x33da2718]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") int
NOTHROW_NCX(LIBCCALL libc_pexecute)(char const *a,
                                    char *const *b,
                                    char const *c,
                                    char const *d,
                                    char **e,
                                    char **f,
                                    int g)
/*[[[body:libc_pexecute]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	(void)f;
	(void)g;
	CRT_UNIMPLEMENTEDF("pexecute(%q, %p, %q, %q, %p, %p, %x)", a, b, c, d, e, f, g); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_pexecute]]]*/

/*[[[head:libc_pwait,hash:CRC-32=0x2186d3db]]]*/
INTERN ATTR_SECTION(".text.crt.libiberty") int
NOTHROW_NCX(LIBCCALL libc_pwait)(int a,
                                 int *b,
                                 int c)
/*[[[body:libc_pwait]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	CRT_UNIMPLEMENTEDF("pwait(%x, %p, %x)", a, b, c); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_pwait]]]*/

/*[[[start:exports,hash:CRC-32=0xe92c7205]]]*/
DEFINE_PUBLIC_ALIAS(xmalloc_set_program_name, libc_xmalloc_set_program_name);
DEFINE_PUBLIC_ALIAS(xmalloc_failed, libc_xmalloc_failed);
DEFINE_PUBLIC_ALIAS(fdmatch, libc_fdmatch);
DEFINE_PUBLIC_ALIAS(buildargv, libc_buildargv);
DEFINE_PUBLIC_ALIAS(expandargv, libc_expandargv);
DEFINE_PUBLIC_ALIAS(writeargv, libc_writeargv);
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$concat_copy2, libd_concat_copy2);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(concat_copy2, libc_concat_copy2);
DEFINE_PUBLIC_ALIAS(get_run_time, libc_get_run_time);
DEFINE_PUBLIC_ALIAS(make_relative_prefix, libc_make_relative_prefix);
DEFINE_PUBLIC_ALIAS(make_relative_prefix_ignore_links, libc_make_relative_prefix_ignore_links);
DEFINE_PUBLIC_ALIAS(choose_tmpdir, libc_choose_tmpdir);
DEFINE_PUBLIC_ALIAS(choose_temp_base, libc_choose_temp_base);
DEFINE_PUBLIC_ALIAS(make_temp_file, libc_make_temp_file);
DEFINE_PUBLIC_ALIAS(make_temp_file_with_prefix, libc_make_temp_file_with_prefix);
DEFINE_PUBLIC_ALIAS(unlink_if_ordinary, libc_unlink_if_ordinary);
DEFINE_PUBLIC_ALIAS(physmem_total, libc_physmem_total);
DEFINE_PUBLIC_ALIAS(physmem_available, libc_physmem_available);
DEFINE_PUBLIC_ALIAS(xcrc32, libc_xcrc32);
DEFINE_PUBLIC_ALIAS(hex_init, libc_hex_init);
DEFINE_PUBLIC_ALIAS(pex_run, libc_pex_run);
DEFINE_PUBLIC_ALIAS(pex_run_in_environment, libc_pex_run_in_environment);
DEFINE_PUBLIC_ALIAS(pex_input_file, libc_pex_input_file);
DEFINE_PUBLIC_ALIAS(pex_input_pipe, libc_pex_input_pipe);
DEFINE_PUBLIC_ALIAS(pex_read_output, libc_pex_read_output);
DEFINE_PUBLIC_ALIAS(pex_read_err, libc_pex_read_err);
DEFINE_PUBLIC_ALIAS(pex_get_status, libc_pex_get_status);
DEFINE_PUBLIC_ALIAS(pex_init, libc_pex_init);
DEFINE_PUBLIC_ALIAS(pex_get_times, libc_pex_get_times);
DEFINE_PUBLIC_ALIAS(pex_free, libc_pex_free);
DEFINE_PUBLIC_ALIAS(pex_one, libc_pex_one);
DEFINE_PUBLIC_ALIAS(pexecute, libc_pexecute);
DEFINE_PUBLIC_ALIAS(pwait, libc_pwait);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_LIBIBERTY_C */
