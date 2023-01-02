/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_SIGNAL_C
#define GUARD_LIBC_USER_SYS_SIGNAL_C 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <assert.h>
#include <malloc.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

#include "../libc/dl.h"
#include "../libc/tls.h"
#include "sys.signal.h"

DECL_BEGIN

/* Originally from DragonFly BSD:
 *    >> int sigblockall(void);
 *    >> int sigunblockall(void);
 *
 * Both  of these can _easily_ be implemented on-top of KOS's userprocmask
 * system (by having a dynamically allocated TLS variable to keep track of
 * recursion, and calling  `setsigmaskptr(3)' with a  full sigset when  it
 * becomes  non-zero, and calling it with the previous (saved) sigset when
 * it becomes zero again)
 */

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

struct sigblock_tls_struct {
	unsigned int sbt_recursion; /* Recursion counter for `sigblockall(3)' */
	sigset_t    *sbt_oldset;    /* [1..1][valid_if(sbt_recursion > 0)]
	                             * Signal set to restore when `sbt_recursion' hits 0 */
};

PRIVATE ATTR_SECTION(".data.crt.bsd.sched.signal")
pthread_key_t sigblock_tls_key = PTHREAD_ONCE_KEY_NP;

PRIVATE ATTR_SECTION(".text.crt.bsd.sched.signal") WUNUSED
struct sigblock_tls_struct *NOTHROW_NCX(LIBCCALL sigblock_gettls)(void) {
	struct sigblock_tls_struct *result;
	if (pthread_key_create_once_np(&sigblock_tls_key, &free) != EOK)
		return NULL;
	result = (struct sigblock_tls_struct *)pthread_getspecific(sigblock_tls_key);
	if (result == NULL) {
		result = (struct sigblock_tls_struct *)malloc(sizeof(struct sigblock_tls_struct));
		if unlikely(pthread_setspecific(sigblock_tls_key, result) != EOK) {
			free(result);
			result = NULL;
		}
	}
	return result;
}


/*[[[head:libc_sigblockall,hash:CRC-32=0x49596485]]]*/
/* >> sigblockall(3)
 * Block all signals (s.a. `setsigmaskfullptr(3)')
 * @return: >1: Signals were already blocked (recursion counter)
 * @return: 1 : Signals were just blocked
 * @return: -1: Error (on KOS, `errno' was modified in this case, but on DragonFly, it isn't) */
INTERN ATTR_SECTION(".text.crt.bsd.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigblockall)(void)
/*[[[body:libc_sigblockall]]]*/
{
	struct sigblock_tls_struct *tls;
	tls = sigblock_gettls();
	if unlikely(tls == NULL)
		return -1;
	if (tls->sbt_recursion++ == 0) {
		/* Initial recursion -> block all signals */
		tls->sbt_oldset = setsigmaskfullptr();
	}
	return tls->sbt_recursion;
}
/*[[[end:libc_sigblockall]]]*/

/*[[[head:libc_sigunblockall,hash:CRC-32=0x6a9e6aad]]]*/
/* >> sigunblockall(3)
 * Unblock all signals, undoing the effects of `sigblockall(3)'
 * @return: & 0x80000000: Signals were marked as pending while they were being blocked
 * @return: & 0x7fffffff != 0: Signals are still blocked (recursion counter)
 * @return: & 0x7fffffff == 0: Signals were just unblocked
 * @return: -1: Error (on KOS, `errno' was modified in this case, but on DragonFly, it isn't) */
INTERN ATTR_SECTION(".text.crt.bsd.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigunblockall)(void)
/*[[[body:libc_sigunblockall]]]*/
{
	uint32_t result;
	struct sigblock_tls_struct *tls;
	tls = sigblock_gettls();
	if unlikely(tls == NULL)
		return -1;

	assertf(tls->sbt_recursion != 0,
	        "sigunblockall(3): bad usage: no preceding call to `sigblockall(3)'");
	--tls->sbt_recursion;
	result = tls->sbt_recursion;

#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
	/* Indicate to our caller if signals are currently pending. */
	if (current.pt_pmask.lpm_pmask.pm_flags & USERPROCMASK_FLAG_HASPENDING)
		result |= UINT32_C(0x80000000);
#endif /* __LIBC_CONFIG_HAVE_USERPROCMASK */

	/* Initial recursion -> block all signals */
	if (tls->sbt_recursion == 0) {
		setsigmaskptr(tls->sbt_oldset);
		DBG_memset(&tls->sbt_oldset, 0xcc, sizeof(tls->sbt_oldset));
	}
	return (int)(unsigned int)result;
}
/*[[[end:libc_sigunblockall]]]*/


/*[[[start:exports,hash:CRC-32=0x1ea4981b]]]*/
DEFINE_PUBLIC_ALIAS(sigblockall, libc_sigblockall);
DEFINE_PUBLIC_ALIAS(sigunblockall, libc_sigunblockall);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SIGNAL_C */
