#ifndef __fpos_t_defined
#include <__stdinc.h>
#include <features.h>
#include <bits/types.h>
#ifndef __fpos_t_defined
#define __fpos_t_defined 1
__SYSDECL_BEGIN
#ifdef __std_fpos_t_defined
__NAMESPACE_STD_USING(fpos_t)
#else /* __std_fpos_t_defined */
typedef __FS_TYPE(pos) fpos_t;
#endif /* !__std_fpos_t_defined */
__SYSDECL_END
#endif /* !__fpos_t_defined */
#endif /* !__fpos_t_defined */
