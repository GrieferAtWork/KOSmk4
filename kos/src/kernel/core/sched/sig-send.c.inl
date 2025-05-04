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
#if defined(__INTELLISENSE__) || defined(__DEEMON__)
#include "sig.c"

/*[[[deemon (printSigSendCInlOptions from "...include.sched.sig-config")();]]]*/
//#define DEFINE_sig_xsend
#define DEFINE_sig_xsendmany
//#define DEFINE_sig_send
//#define DEFINE_sig_altsend
//#define DEFINE_sig_send_nopr
//#define DEFINE_sig_altsend_nopr
//#define DEFINE_sig_send_cleanup_nopr
//#define DEFINE_sig_altsend_cleanup_nopr
//#define DEFINE_sig_sendas
//#define DEFINE_sig_altsendas
//#define DEFINE_sig_sendas_nopr
//#define DEFINE_sig_altsendas_nopr
//#define DEFINE_sig_sendas_cleanup_nopr
//#define DEFINE_sig_altsendas_cleanup_nopr
//#define DEFINE_sig_sendto
//#define DEFINE_sig_altsendto
//#define DEFINE_sig_sendto_nopr
//#define DEFINE_sig_altsendto_nopr
//#define DEFINE_sig_sendto_cleanup_nopr
//#define DEFINE_sig_altsendto_cleanup_nopr
//#define DEFINE_sig_sendasto
//#define DEFINE_sig_altsendasto
//#define DEFINE_sig_sendasto_nopr
//#define DEFINE_sig_altsendasto_nopr
//#define DEFINE_sig_sendasto_cleanup_nopr
//#define DEFINE_sig_altsendasto_cleanup_nopr
//#define DEFINE_sig_sendmany
//#define DEFINE_sig_altsendmany
//#define DEFINE_sig_sendmany_nopr
//#define DEFINE_sig_altsendmany_nopr
//#define DEFINE_sig_sendmany_cleanup_nopr
//#define DEFINE_sig_altsendmany_cleanup_nopr
//#define DEFINE_sig_sendmanyas
//#define DEFINE_sig_altsendmanyas
//#define DEFINE_sig_sendmanyas_nopr
//#define DEFINE_sig_altsendmanyas_nopr
//#define DEFINE_sig_sendmanyas_cleanup_nopr
//#define DEFINE_sig_altsendmanyas_cleanup_nopr
//#define DEFINE_sig_broadcast
//#define DEFINE_sig_altbroadcast
//#define DEFINE_sig_broadcast_nopr
//#define DEFINE_sig_altbroadcast_nopr
//#define DEFINE_sig_broadcast_for_fini
//#define DEFINE_sig_altbroadcast_for_fini
//#define DEFINE_sig_broadcast_for_fini_nopr
//#define DEFINE_sig_altbroadcast_for_fini_nopr
//#define DEFINE_sig_broadcast_cleanup_nopr
//#define DEFINE_sig_altbroadcast_cleanup_nopr
//#define DEFINE_sig_broadcast_for_fini_cleanup_nopr
//#define DEFINE_sig_altbroadcast_for_fini_cleanup_nopr
//#define DEFINE_sig_broadcastas
//#define DEFINE_sig_altbroadcastas
//#define DEFINE_sig_broadcastas_nopr
//#define DEFINE_sig_altbroadcastas_nopr
//#define DEFINE_sig_broadcastas_cleanup_nopr
//#define DEFINE_sig_altbroadcastas_cleanup_nopr
//#define DEFINE_sig_broadcastas_for_fini
//#define DEFINE_sig_altbroadcastas_for_fini
//#define DEFINE_sig_broadcastas_for_fini_nopr
//#define DEFINE_sig_altbroadcastas_for_fini_nopr
//#define DEFINE_sig_broadcastas_for_fini_cleanup_nopr
//#define DEFINE_sig_altbroadcastas_for_fini_cleanup_nopr
/*[[[end]]]*/
#endif /* __INTELLISENSE__ */

/*[[[deemon (printSigSendCInlHead from "...include.sched.sig-config")();]]]*/
#if (defined(DEFINE_sig_xsend) +                              \
     defined(DEFINE_sig_xsendmany) +                          \
     defined(DEFINE_sig_send) +                               \
     defined(DEFINE_sig_altsend) +                            \
     defined(DEFINE_sig_send_nopr) +                          \
     defined(DEFINE_sig_altsend_nopr) +                       \
     defined(DEFINE_sig_send_cleanup_nopr) +                  \
     defined(DEFINE_sig_altsend_cleanup_nopr) +               \
     defined(DEFINE_sig_sendas) +                             \
     defined(DEFINE_sig_altsendas) +                          \
     defined(DEFINE_sig_sendas_nopr) +                        \
     defined(DEFINE_sig_altsendas_nopr) +                     \
     defined(DEFINE_sig_sendas_cleanup_nopr) +                \
     defined(DEFINE_sig_altsendas_cleanup_nopr) +             \
     defined(DEFINE_sig_sendto) +                             \
     defined(DEFINE_sig_altsendto) +                          \
     defined(DEFINE_sig_sendto_nopr) +                        \
     defined(DEFINE_sig_altsendto_nopr) +                     \
     defined(DEFINE_sig_sendto_cleanup_nopr) +                \
     defined(DEFINE_sig_altsendto_cleanup_nopr) +             \
     defined(DEFINE_sig_sendasto) +                           \
     defined(DEFINE_sig_altsendasto) +                        \
     defined(DEFINE_sig_sendasto_nopr) +                      \
     defined(DEFINE_sig_altsendasto_nopr) +                   \
     defined(DEFINE_sig_sendasto_cleanup_nopr) +              \
     defined(DEFINE_sig_altsendasto_cleanup_nopr) +           \
     defined(DEFINE_sig_sendmany) +                           \
     defined(DEFINE_sig_altsendmany) +                        \
     defined(DEFINE_sig_sendmany_nopr) +                      \
     defined(DEFINE_sig_altsendmany_nopr) +                   \
     defined(DEFINE_sig_sendmany_cleanup_nopr) +              \
     defined(DEFINE_sig_altsendmany_cleanup_nopr) +           \
     defined(DEFINE_sig_sendmanyas) +                         \
     defined(DEFINE_sig_altsendmanyas) +                      \
     defined(DEFINE_sig_sendmanyas_nopr) +                    \
     defined(DEFINE_sig_altsendmanyas_nopr) +                 \
     defined(DEFINE_sig_sendmanyas_cleanup_nopr) +            \
     defined(DEFINE_sig_altsendmanyas_cleanup_nopr) +         \
     defined(DEFINE_sig_broadcast) +                          \
     defined(DEFINE_sig_altbroadcast) +                       \
     defined(DEFINE_sig_broadcast_nopr) +                     \
     defined(DEFINE_sig_altbroadcast_nopr) +                  \
     defined(DEFINE_sig_broadcast_for_fini) +                 \
     defined(DEFINE_sig_altbroadcast_for_fini) +              \
     defined(DEFINE_sig_broadcast_for_fini_nopr) +            \
     defined(DEFINE_sig_altbroadcast_for_fini_nopr) +         \
     defined(DEFINE_sig_broadcast_cleanup_nopr) +             \
     defined(DEFINE_sig_altbroadcast_cleanup_nopr) +          \
     defined(DEFINE_sig_broadcast_for_fini_cleanup_nopr) +    \
     defined(DEFINE_sig_altbroadcast_for_fini_cleanup_nopr) + \
     defined(DEFINE_sig_broadcastas) +                        \
     defined(DEFINE_sig_altbroadcastas) +                     \
     defined(DEFINE_sig_broadcastas_nopr) +                   \
     defined(DEFINE_sig_altbroadcastas_nopr) +                \
     defined(DEFINE_sig_broadcastas_cleanup_nopr) +           \
     defined(DEFINE_sig_altbroadcastas_cleanup_nopr) +        \
     defined(DEFINE_sig_broadcastas_for_fini) +               \
     defined(DEFINE_sig_altbroadcastas_for_fini) +            \
     defined(DEFINE_sig_broadcastas_for_fini_nopr) +          \
     defined(DEFINE_sig_altbroadcastas_for_fini_nopr) +       \
     defined(DEFINE_sig_broadcastas_for_fini_cleanup_nopr) +  \
     defined(DEFINE_sig_altbroadcastas_for_fini_cleanup_nopr)) != 1
#error "Must #define exactly one of these macros!"
#endif /* ... */

#ifdef DEFINE_sig_xsend
#define LOCAL_sig_send sig_xsend
#define LOCAL_IS_XSEND
#define LOCAL_IS_SEND
#define LOCAL_flags flags
#define LOCAL_HAVE_flags
#define LOCAL_HAVE_sender  /* Potentially; depends on `flags' */
#define LOCAL_HAVE_caller  /* Potentially; depends on `flags' */
#define LOCAL_HAVE_target  /* Potentially; depends on `flags' */
#define LOCAL_HAVE_cleanup /* Potentially; depends on `flags' */
#define LOCAL_HAVE_reprime
#elif defined(DEFINE_sig_xsendmany)
#define LOCAL_sig_send sig_xsendmany
#define LOCAL_IS_XSEND
#define LOCAL_IS_BROADCAST
#define LOCAL_flags flags
#define LOCAL_HAVE_maxcount
#define LOCAL_HAVE_flags
#define LOCAL_HAVE_sender  /* Potentially; depends on `flags' */
#define LOCAL_HAVE_caller  /* Potentially; depends on `flags' */
#define LOCAL_HAVE_cleanup /* Potentially; depends on `flags' */
#define LOCAL_HAVE_reprime
#define LOCAL_HAVE_destroy_later
#elif defined(DEFINE_sig_send)
#define LOCAL_sig_send sig_send
#define LOCAL_IS_SEND
#define LOCAL_flags SIG_XSEND_F_NORMAL
#elif defined(DEFINE_sig_altsend)
#define LOCAL_sig_send sig_altsend
#define LOCAL_IS_SEND
#define LOCAL_HAVE_sender
#define LOCAL_flags SIG_XSEND_F_SENDER
#elif defined(DEFINE_sig_send_nopr)
#define LOCAL_sig_send sig_send_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_flags SIG_XSEND_F_NOPR
#elif defined(DEFINE_sig_altsend_nopr)
#define LOCAL_sig_send sig_altsend_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER)
#elif defined(DEFINE_sig_send_cleanup_nopr)
#define LOCAL_sig_send sig_send_cleanup_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_altsend_cleanup_nopr)
#define LOCAL_sig_send sig_altsend_cleanup_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_sendas)
#define LOCAL_sig_send sig_sendas
#define LOCAL_IS_SEND
#define LOCAL_HAVE_caller
#define LOCAL_flags SIG_XSEND_F_NORMAL
#elif defined(DEFINE_sig_altsendas)
#define LOCAL_sig_send sig_altsendas
#define LOCAL_IS_SEND
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_flags SIG_XSEND_F_SENDER
#elif defined(DEFINE_sig_sendas_nopr)
#define LOCAL_sig_send sig_sendas_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_caller
#define LOCAL_flags SIG_XSEND_F_NOPR
#elif defined(DEFINE_sig_altsendas_nopr)
#define LOCAL_sig_send sig_altsendas_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER)
#elif defined(DEFINE_sig_sendas_cleanup_nopr)
#define LOCAL_sig_send sig_sendas_cleanup_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_altsendas_cleanup_nopr)
#define LOCAL_sig_send sig_altsendas_cleanup_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_sendto)
#define LOCAL_sig_send sig_sendto
#define LOCAL_IS_SEND
#define LOCAL_HAVE_target
#define LOCAL_flags SIG_XSEND_F_TARGET
#elif defined(DEFINE_sig_altsendto)
#define LOCAL_sig_send sig_altsendto
#define LOCAL_IS_SEND
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_target
#define LOCAL_flags (SIG_XSEND_F_SENDER | SIG_XSEND_F_TARGET)
#elif defined(DEFINE_sig_sendto_nopr)
#define LOCAL_sig_send sig_sendto_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_target
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_TARGET)
#elif defined(DEFINE_sig_altsendto_nopr)
#define LOCAL_sig_send sig_altsendto_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_target
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_TARGET)
#elif defined(DEFINE_sig_sendto_cleanup_nopr)
#define LOCAL_sig_send sig_sendto_cleanup_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_target
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_TARGET | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_altsendto_cleanup_nopr)
#define LOCAL_sig_send sig_altsendto_cleanup_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_target
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_TARGET | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_sendasto)
#define LOCAL_sig_send sig_sendasto
#define LOCAL_IS_SEND
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_target
#define LOCAL_flags SIG_XSEND_F_TARGET
#elif defined(DEFINE_sig_altsendasto)
#define LOCAL_sig_send sig_altsendasto
#define LOCAL_IS_SEND
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_target
#define LOCAL_flags (SIG_XSEND_F_SENDER | SIG_XSEND_F_TARGET)
#elif defined(DEFINE_sig_sendasto_nopr)
#define LOCAL_sig_send sig_sendasto_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_target
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_TARGET)
#elif defined(DEFINE_sig_altsendasto_nopr)
#define LOCAL_sig_send sig_altsendasto_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_target
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_TARGET)
#elif defined(DEFINE_sig_sendasto_cleanup_nopr)
#define LOCAL_sig_send sig_sendasto_cleanup_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_target
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_TARGET | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_altsendasto_cleanup_nopr)
#define LOCAL_sig_send sig_altsendasto_cleanup_nopr
#define LOCAL_IS_SEND
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_target
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_TARGET | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_sendmany)
#define LOCAL_sig_send sig_sendmany
#define LOCAL_IS_BROADCAST
#define LOCAL_HAVE_maxcount
#define LOCAL_flags SIG_XSEND_F_NORMAL
#elif defined(DEFINE_sig_altsendmany)
#define LOCAL_sig_send sig_altsendmany
#define LOCAL_IS_BROADCAST
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_maxcount
#define LOCAL_flags SIG_XSEND_F_SENDER
#elif defined(DEFINE_sig_sendmany_nopr)
#define LOCAL_sig_send sig_sendmany_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_maxcount
#define LOCAL_flags SIG_XSEND_F_NOPR
#elif defined(DEFINE_sig_altsendmany_nopr)
#define LOCAL_sig_send sig_altsendmany_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_maxcount
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER)
#elif defined(DEFINE_sig_sendmany_cleanup_nopr)
#define LOCAL_sig_send sig_sendmany_cleanup_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_cleanup
#define LOCAL_HAVE_maxcount
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_altsendmany_cleanup_nopr)
#define LOCAL_sig_send sig_altsendmany_cleanup_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_cleanup
#define LOCAL_HAVE_maxcount
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_sendmanyas)
#define LOCAL_sig_send sig_sendmanyas
#define LOCAL_IS_BROADCAST
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_maxcount
#define LOCAL_flags SIG_XSEND_F_NORMAL
#elif defined(DEFINE_sig_altsendmanyas)
#define LOCAL_sig_send sig_altsendmanyas
#define LOCAL_IS_BROADCAST
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_maxcount
#define LOCAL_flags SIG_XSEND_F_SENDER
#elif defined(DEFINE_sig_sendmanyas_nopr)
#define LOCAL_sig_send sig_sendmanyas_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_maxcount
#define LOCAL_flags SIG_XSEND_F_NOPR
#elif defined(DEFINE_sig_altsendmanyas_nopr)
#define LOCAL_sig_send sig_altsendmanyas_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_maxcount
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER)
#elif defined(DEFINE_sig_sendmanyas_cleanup_nopr)
#define LOCAL_sig_send sig_sendmanyas_cleanup_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_cleanup
#define LOCAL_HAVE_maxcount
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_altsendmanyas_cleanup_nopr)
#define LOCAL_sig_send sig_altsendmanyas_cleanup_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_cleanup
#define LOCAL_HAVE_maxcount
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_broadcast)
#define LOCAL_sig_send sig_broadcast
#define LOCAL_IS_BROADCAST
#define LOCAL_flags SIG_XSEND_F_NORMAL
#elif defined(DEFINE_sig_altbroadcast)
#define LOCAL_sig_send sig_altbroadcast
#define LOCAL_IS_BROADCAST
#define LOCAL_HAVE_sender
#define LOCAL_flags SIG_XSEND_F_SENDER
#elif defined(DEFINE_sig_broadcast_nopr)
#define LOCAL_sig_send sig_broadcast_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_flags SIG_XSEND_F_NOPR
#elif defined(DEFINE_sig_altbroadcast_nopr)
#define LOCAL_sig_send sig_altbroadcast_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER)
#elif defined(DEFINE_sig_broadcast_for_fini)
#define LOCAL_sig_send sig_broadcast_for_fini
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_FINI
#define LOCAL_flags SIG_XSEND_F_FINI
#elif defined(DEFINE_sig_altbroadcast_for_fini)
#define LOCAL_sig_send sig_altbroadcast_for_fini
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_FINI
#define LOCAL_HAVE_sender
#define LOCAL_flags (SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER)
#elif defined(DEFINE_sig_broadcast_for_fini_nopr)
#define LOCAL_sig_send sig_broadcast_for_fini_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_IS_FINI
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI)
#elif defined(DEFINE_sig_altbroadcast_for_fini_nopr)
#define LOCAL_sig_send sig_altbroadcast_for_fini_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_IS_FINI
#define LOCAL_HAVE_sender
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER)
#elif defined(DEFINE_sig_broadcast_cleanup_nopr)
#define LOCAL_sig_send sig_broadcast_cleanup_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_altbroadcast_cleanup_nopr)
#define LOCAL_sig_send sig_altbroadcast_cleanup_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_broadcast_for_fini_cleanup_nopr)
#define LOCAL_sig_send sig_broadcast_for_fini_cleanup_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_IS_FINI
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_altbroadcast_for_fini_cleanup_nopr)
#define LOCAL_sig_send sig_altbroadcast_for_fini_cleanup_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_IS_FINI
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_broadcastas)
#define LOCAL_sig_send sig_broadcastas
#define LOCAL_IS_BROADCAST
#define LOCAL_HAVE_caller
#define LOCAL_flags SIG_XSEND_F_NORMAL
#elif defined(DEFINE_sig_altbroadcastas)
#define LOCAL_sig_send sig_altbroadcastas
#define LOCAL_IS_BROADCAST
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_flags SIG_XSEND_F_SENDER
#elif defined(DEFINE_sig_broadcastas_nopr)
#define LOCAL_sig_send sig_broadcastas_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_caller
#define LOCAL_flags SIG_XSEND_F_NOPR
#elif defined(DEFINE_sig_altbroadcastas_nopr)
#define LOCAL_sig_send sig_altbroadcastas_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER)
#elif defined(DEFINE_sig_broadcastas_cleanup_nopr)
#define LOCAL_sig_send sig_broadcastas_cleanup_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_altbroadcastas_cleanup_nopr)
#define LOCAL_sig_send sig_altbroadcastas_cleanup_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_broadcastas_for_fini)
#define LOCAL_sig_send sig_broadcastas_for_fini
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_FINI
#define LOCAL_HAVE_caller
#define LOCAL_flags SIG_XSEND_F_FINI
#elif defined(DEFINE_sig_altbroadcastas_for_fini)
#define LOCAL_sig_send sig_altbroadcastas_for_fini
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_FINI
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_flags (SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER)
#elif defined(DEFINE_sig_broadcastas_for_fini_nopr)
#define LOCAL_sig_send sig_broadcastas_for_fini_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_IS_FINI
#define LOCAL_HAVE_caller
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI)
#elif defined(DEFINE_sig_altbroadcastas_for_fini_nopr)
#define LOCAL_sig_send sig_altbroadcastas_for_fini_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_IS_FINI
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER)
#elif defined(DEFINE_sig_broadcastas_for_fini_cleanup_nopr)
#define LOCAL_sig_send sig_broadcastas_for_fini_cleanup_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_IS_FINI
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_CLEANUP)
#elif defined(DEFINE_sig_altbroadcastas_for_fini_cleanup_nopr)
#define LOCAL_sig_send sig_altbroadcastas_for_fini_cleanup_nopr
#define LOCAL_IS_BROADCAST
#define LOCAL_IS_NOPR
#define LOCAL_IS_FINI
#define LOCAL_HAVE_sender
#define LOCAL_HAVE_caller
#define LOCAL_HAVE_cleanup
#define LOCAL_flags (SIG_XSEND_F_NOPR | SIG_XSEND_F_FINI | SIG_XSEND_F_SENDER | SIG_XSEND_F_CLEANUP)
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
/*[[[end]]]*/

#include <kernel/compiler.h>

#include <kernel/panic.h>
#include <sched/sig-completion.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <hybrid/sched/preemption.h>

#include <assert.h>
#include <atomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

DECL_BEGIN

#ifdef LOCAL_IS_BROADCAST
#define LOCAL_return_t size_t
#else /* ... */
#define LOCAL_return_t bool
#endif /* !... */

#ifdef LOCAL_HAVE_sender
#define LOCAL_sig_restrict /* nothing */
#else /* ... */
#define LOCAL_sig_restrict __restrict
#endif /* !... */

#if defined(LOCAL_HAVE_flags) || (defined(LOCAL_HAVE_caller) && defined(LOCAL_HAVE_target))
#define LOCAL_task_restrict /* nothing */
#else /* ... */
#define LOCAL_task_restrict __restrict
#endif /* !... */

#ifdef LOCAL_HAVE_flags
#define LOCAL_cleanup_restrict /* nothing */
#else /* ... */
#define LOCAL_cleanup_restrict __restrict
#endif /* !... */



#ifdef LOCAL_IS_NOPR
#define LOCAL_task_yield() task_pause()
#else /* LOCAL_IS_NOPR */
#define LOCAL_task_yield() task_tryyield_or_pause()
#endif /* !LOCAL_IS_NOPR */



#if defined(LOCAL_HAVE_caller) && defined(LOCAL_HAVE_flags)
#define LOCAL_task_wake(thread)                                                          \
	((LOCAL_flags & SIG_XSEND_F_CALLER)                                                  \
	 ? task_wake_as(thread, caller, take_wake_flags__from__sig_xsend_flags(LOCAL_flags)) \
	 : task_wake(thread, take_wake_flags__from__sig_xsend_flags(LOCAL_flags)))
#elif defined(LOCAL_HAVE_caller)
#define LOCAL_task_wake(thread) \
	task_wake_as(thread, caller, take_wake_flags__from__sig_xsend_flags(LOCAL_flags))
#else /* LOCAL_HAVE_caller */
#define LOCAL_task_wake(thread) task_wake(thread, take_wake_flags__from__sig_xsend_flags(LOCAL_flags))
#endif /* !LOCAL_HAVE_caller */




PUBLIC NOBLOCK LOCAL_return_t
NOTHROW(FCALL LOCAL_sig_send)(struct sig *LOCAL_sig_restrict self
#ifdef LOCAL_HAVE_maxcount
                              , size_t maxcount
#define LOCAL_maxcount_MINUS_result() (maxcount - result)
#else /* LOCAL_HAVE_maxcount */
#define LOCAL_maxcount_MINUS_result() ((size_t)-1)
#endif /* !LOCAL_HAVE_maxcount */
#ifdef LOCAL_HAVE_flags
                              , unsigned int flags
#endif /* LOCAL_HAVE_flags */
#ifdef LOCAL_HAVE_sender
                              , struct sig *sender
#define LOCAL_sender_OPT sender
#define LOCAL_sender     sender
#else /* LOCAL_HAVE_sender */
#define LOCAL_sender_OPT NULL
#define LOCAL_sender     self
#endif /* !LOCAL_HAVE_sender */
#ifdef LOCAL_HAVE_caller
                              , struct task *LOCAL_task_restrict caller
#define LOCAL_caller caller
#else /* LOCAL_HAVE_caller */
#define LOCAL_caller THIS_TASK
#endif /* LOCAL_HAVE_caller */
#ifdef LOCAL_HAVE_target
                              , struct task *LOCAL_task_restrict target
#endif /* LOCAL_HAVE_target */
#ifdef LOCAL_HAVE_cleanup
                              , struct sig_cleanup_callback *LOCAL_cleanup_restrict cleanup
#define LOCAL_cleanup_OPT cleanup
#ifdef LOCAL_HAVE_flags
#define LOCAL_cleanup      ((flags & SIG_XSEND_F_CLEANUP) ? cleanup : NULL)
#define LOCAL_runcleanup() ((LOCAL_flags & SIG_XSEND_F_CLEANUP) ? (*cleanup->scc_cb)(cleanup) : (void)0)
#else /* LOCAL_HAVE_flags */
#define LOCAL_cleanup      cleanup
#define LOCAL_runcleanup() (*cleanup->scc_cb)(cleanup)
#endif /* !LOCAL_HAVE_flags */
#else /* LOCAL_HAVE_cleanup */
#define LOCAL_cleanup_OPT  NULL
#define LOCAL_cleanup      NULL
#define LOCAL_runcleanup() (void)0
#endif /* !LOCAL_HAVE_cleanup */
#ifdef LOCAL_HAVE_reprime
                              , struct sigcon *reprime
#define LOCAL_reprime reprime
#else /* LOCAL_HAVE_reprime */
#define LOCAL_reprime NULL
#endif /* LOCAL_HAVE_reprime */
#ifdef LOCAL_HAVE_destroy_later
                              , struct task *destroy_later
#define LOCAL_destroy_later destroy_later
#else /* LOCAL_HAVE_destroy_later */
#define LOCAL_destroy_later NULL
#endif /* LOCAL_HAVE_destroy_later */
                              ) {
	struct sigcon *sigctl;
	struct sigcon *receiver;
	struct taskcons *tcs;
#ifdef LOCAL_IS_BROADCAST
	size_t result = 0;
#if defined(LOCAL_HAVE_maxcount) || !defined(LOCAL_HAVE_flags)
	struct sigcon *lastcon;
#endif /* LOCAL_HAVE_maxcount || LOCAL_HAVE_flags */
#else /* LOCAL_IS_BROADCAST */
	struct sigcon *remainder;
#endif /* !LOCAL_IS_BROADCAST */
#ifdef LOCAL_IS_NOPR
#define LOCAL_was PREEMPTION_OFF_VALUE
#define LOCAL_preemption_wason() 0
#else /* !LOCAL_IS_NOPR */
	preemption_flag_t was;
#define LOCAL_was was
#define LOCAL_preemption_wason() preemption_wason(&was)
#endif /* LOCAL_IS_NOPR */
#ifdef LOCAL_HAVE_flags
	struct sig_post_completion *phase2 = NULL;
	struct sig_completion_context context;
	if (!(flags & SIG_XSEND_F_SENDER))
		sender = self;
#endif /* LOCAL_HAVE_flags */


	/* Check for special case: not allowed to send *any* signals */
#ifdef LOCAL_HAVE_maxcount
	if unlikely(!maxcount) {
#ifdef LOCAL_HAVE_flags
		if (flags & SIG_XSEND_F_LOCKED) {
			/* Inherit lock from caller */
			atomic_and((uintptr_t *)&self->s_con, ~SIG_SMPLOCK);
			assert(!preemption_ison() || kernel_poisoned());
			LOCAL_runcleanup(); /* for sig_send_cleanup */
			if (!(flags & SIG_XSEND_F_NOPR))
				PREEMPTION_ENABLE();
		} else
#endif /* LOCAL_HAVE_flags */
		{
			LOCAL_runcleanup(); /* for sig_send_cleanup */
		}
#ifdef LOCAL_HAVE_destroy_later
		destroy_tasks(destroy_later);
#endif /* LOCAL_HAVE_destroy_later */
		return 0;
	}
#endif /* LOCAL_HAVE_maxcount */


#if defined(SIG_SMPLOCK) || !defined(LOCAL_IS_NOPR)
again:
#endif /* SIG_SMPLOCK || !LOCAL_IS_NOPR */

	sigctl = atomic_read(&self->s_con);
#ifdef SIG_SMPLOCK
	assertf((uintptr_t)sigctl != (0 | SIG_SMPLOCK),
	        "SIG_SMPLOCK must not appear without connections");
#endif /* SIG_SMPLOCK */
#ifdef LOCAL_HAVE_flags
	if (flags & SIG_XSEND_F_LOCKED) {
		/* Inherit lock from caller */
#ifdef SIG_SMPLOCK
		assertf((uintptr_t)sigctl & SIG_SMPLOCK,
		        "SIG_SMPLOCK should have been set by the caller!");
		sigctl = (struct sigcon *)((uintptr_t)sigctl & ~SIG_SMPLOCK);
#endif /* SIG_SMPLOCK */
		assert(!preemption_ison() || kernel_poisoned());
		was = PREEMPTION_ON_VALUE;
		if (flags & SIG_XSEND_F_NOPR)
			was = PREEMPTION_OFF_VALUE;
	} else
#endif /* LOCAL_HAVE_flags */
	{
		if ((uintptr_t)sigctl == 0) {
			/* Special case: no-one is connected */
			LOCAL_runcleanup(); /* for sig_send_cleanup */
#ifdef LOCAL_HAVE_destroy_later
			destroy_tasks(destroy_later);
#endif /* LOCAL_HAVE_destroy_later */
			return 0;
		}

#ifdef SIG_SMPLOCK
		if ((uintptr_t)sigctl & SIG_SMPLOCK) {
			LOCAL_task_yield();
			goto again;
		}
#endif /* SIG_SMPLOCK */

#ifndef LOCAL_IS_NOPR
#ifdef LOCAL_HAVE_flags
		if (LOCAL_flags & SIG_XSEND_F_NOPR)
			assert(!preemption_ison() || kernel_poisoned());
#endif /* LOCAL_HAVE_flags */
		preemption_pushoff(&was);
#else /* !LOCAL_IS_NOPR */
		assert(!preemption_ison() || kernel_poisoned());
#endif /* LOCAL_IS_NOPR */

		/* Acquire SMP-lock */
#ifdef SIG_SMPLOCK
		if (!atomic_cmpxch_weak(&self->s_con, sigctl,
		                        (struct sigcon *)((uintptr_t)sigctl | SIG_SMPLOCK))) {
#ifndef LOCAL_IS_NOPR
			preemption_pop(&was);
#endif /* !LOCAL_IS_NOPR */
			goto again;
		}
#endif /* SIG_SMPLOCK */
	}

	/* Debug assertions hook to verify integrity of the connection ring. */
	sigcon_verify_ring_beforesend(sigctl);

#ifdef LOCAL_IS_BROADCAST
	/* Enumerate all receivers and signal each of them. */
	receiver = sigctl;
#if defined(LOCAL_HAVE_maxcount) || !defined(LOCAL_HAVE_flags)
	lastcon = sigctl->sc_prev;
#endif /* LOCAL_HAVE_maxcount || !LOCAL_HAVE_flags */
	do {
		bool bcast_ok;
		uintptr_t stat = atomic_read(&receiver->sc_stat);
		struct sigcon *next = receiver->sc_next;
		assert(SIGCON_STAT_ISCONNECTED(stat));
//		assert(receiver->sc_prev->sc_next  ==  receiver);  /*  Cannot  be  asserted  because  we  might  no  longer  own  "receiver->sc_prev".  Also:  we  destroy  these  links  via  DBG_memset */
//		assert(receiver->sc_next->sc_prev == receiver); /* Cannot be asserted because we might no longer own "receiver->sc_next" (if it is "sigctl"). Also: we destroy these links via DBG_memset */
		DBG_memset(&receiver->sc_prev, 0xcc, sizeof(receiver->sc_prev));
		DBG_memset(&receiver->sc_next, 0xcc, sizeof(receiver->sc_next));

		if (SIGCON_STAT_ISCOMP(stat)) {
			struct sigcon_comp *sc = (struct sigcon_comp *)receiver;
#ifdef LOCAL_HAVE_flags
			context.scc_sender = sender;
			context.scc_caller = caller;
			invoke_sig_completion(&phase2, sc, &context);
			if (!(context.scc_status & SIG_COMPLETION__F_REPRIME) || (flags & SIG_XSEND_F_FINI)) {
				/* This releases our ownership of "receiver" */
				atomic_write(&receiver->sc_stat, SIGCON_STAT_ST_THRBCAST);
			} else {
				/* Insert into "reprime" queue (at the end, such that order is maintained)
				 * Note that  repriming isn't  allowed during  `sig_broadcast_for_fini()`! */
				if (reprime == NULL) {
					sigcon_link_self(sc);
					reprime = sc;
				} else {
					sigcon_link_insert_before(sc, reprime);
				}
				sigcon_verify_ring_afterinsert(reprime);
			}

			bcast_ok = (context.scc_status & SIG_COMPLETION__F_NONVIABLE) == 0;
#else /* LOCAL_HAVE_flags */
#define LOCAL_sig_completion_invoke_and_continue_broadcast()                            \
			sig_completion_invoke_and_continue_broadcast(self,                          \
			                                             LOCAL_sender,                  \
			                                             sc,                            \
			                                             next,                          \
			                                             lastcon,                       \
			                                             sigctl,                        \
			                                             LOCAL_maxcount_MINUS_result(), \
			                                             LOCAL_caller,                  \
			                                             LOCAL_reprime,  /* XXX: This should always be "NULL" */ \
			                                             LOCAL_cleanup,                 \
			                                             LOCAL_destroy_later,           \
			                                             LOCAL_was,                     \
			                                             LOCAL_flags)
#if defined(__OPTIMIZE__) && !defined(__OPTIMIZE_SIZE__)
			if (result == 0) /* So the compiler can generate a tail-call */
				return LOCAL_sig_completion_invoke_and_continue_broadcast();
#endif /* __OPTIMIZE__ && !__OPTIMIZE_SIZE__ */
			result += LOCAL_sig_completion_invoke_and_continue_broadcast();
			return result;
#undef LOCAL_sig_completion_invoke_and_continue_broadcast
#endif /* !LOCAL_HAVE_flags */
		} else {
			tcs = (struct taskcons *)(stat & ~SIGCON_STAT_F_POLL);
			bcast_ok = atomic_cmpxch(&tcs->tcs_deliver, NULL, self);
			if (bcast_ok) {
				/* First signal delivered -> must wake the thread after locks were released. */
				REF struct task *thread = xincref(atomic_read(&tcs->tcs_thread));
				atomic_write(&receiver->sc_stat, SIGCON_STAT_ST_THRBCAST); /* This releases our ownership of "receiver" */
				if (thread) {
					LOCAL_task_wake(thread);
					if unlikely(atomic_decfetch(&thread->t_refcnt) == 0) {
#ifdef LOCAL_HAVE_destroy_later
						sig_destroylater_next(thread) = destroy_later;
						destroy_later = thread;
#else /* LOCAL_HAVE_destroy_later */
						unsigned int rest_flags = (LOCAL_flags & ~SIG_XSEND_F_NOPR) | SIG_XSEND_F_LOCKED |
						                          (LOCAL_preemption_wason() ? 0 : SIG_XSEND_F_NOPR);
						sig_destroylater_next(thread) = NULL;
#define LOCAL_sig_xsendmany()                                                     \
						sig_xsendmany(self, LOCAL_maxcount_MINUS_result(),        \
						              rest_flags, LOCAL_sender_OPT, LOCAL_caller, \
						              LOCAL_cleanup_OPT, NULL, thread)
#if defined(__OPTIMIZE__) && !defined(__OPTIMIZE_SIZE__)
						if (result == 0) /* So the compiler can generate a tail-call */
							return LOCAL_sig_xsendmany();
#endif /* __OPTIMIZE__ && !__OPTIMIZE_SIZE__ */
						result += LOCAL_sig_xsendmany();
						return result;
#undef LOCAL_sig_xsendmany
#endif /* !LOCAL_HAVE_destroy_later */
					}
				}
			} else {
				atomic_write(&receiver->sc_stat, SIGCON_STAT_ST_THRBCAST); /* This releases our ownership of "receiver" */
			}
		}

		/* Keep track of the # of successful non-poll broadcasts */
		if (bcast_ok && !(stat & SIGCON_STAT_F_POLL)) {
			++result;
#ifdef LOCAL_HAVE_maxcount
			if (result >= maxcount) {
				/* Stop prematurely */
				assert((receiver == lastcon) == (next == sigctl));
				if unlikely(next == sigctl)
					break; /* No connections remain -> can use the normal branch below. */

				/* Must write-back to "self" a ring (with a head at "next"):
				 * [next] ---------...---------> [lastcon]
				 *   ^                               |
				 *   |                               v
				 * [reprime->sc_prev] <---...--- [reprime]
				 */
				lastcon->sc_next = next;
				next->sc_prev = lastcon;
#ifdef LOCAL_HAVE_reprime
				next = combine_remainder_and_reprime(next, reprime);
#endif /* LOCAL_HAVE_reprime */

				sigcon_verify_ring_aftersend(next);
				atomic_write(&self->s_con, next);
				goto done_sig_unlocked;
			}
#endif /* LOCAL_HAVE_maxcount */
		}

		/* Move on to the next receiver */
		receiver = next;
	} while (receiver != sigctl);

	/* Release SMP-lock; only reprimed connections remain */
#if defined(LOCAL_HAVE_reprime) && !defined(sigcon_verify_ring_IS_NOOP)
	if (LOCAL_reprime)
		sigcon_verify_ring_aftersend(LOCAL_reprime);
#endif /* LOCAL_HAVE_reprime && !sigcon_verify_ring_IS_NOOP */
	atomic_write(&self->s_con, LOCAL_reprime);

#ifdef LOCAL_HAVE_maxcount
done_sig_unlocked:
#endif /* LOCAL_HAVE_maxcount */

	/* for sig_broadcast_cleanup */
	LOCAL_runcleanup();

	/* Restore preemption stat */
#ifndef LOCAL_IS_NOPR
	preemption_pop(&was);
#endif /* !LOCAL_IS_NOPR */

	/* Finish destruction of dead threads */
#ifdef LOCAL_HAVE_destroy_later
	destroy_tasks(destroy_later);
#endif /* LOCAL_HAVE_destroy_later */

	/* Run phase#2 signal completion callbacks */
#ifdef LOCAL_HAVE_flags
	sig_run_phase_2(phase2, &context);
#endif /* LOCAL_HAVE_flags */
	return result;
#else /* LOCAL_IS_BROADCAST */
again_find_receiver:
	receiver = sigctl;
	assert(receiver->sc_sig == self);

#ifdef LOCAL_HAVE_flags
	if (flags & SIG_XSEND_F_TARGET)
#endif /* LOCAL_HAVE_flags */
#if defined(LOCAL_HAVE_flags) || defined(LOCAL_HAVE_target)
	{
		/* Send to specific thread */
		for (;;) {
			tcs = atomic_read_relaxed(&receiver->sc_cons);
			assert(SIGCON_STAT_ISCONNECTED((uintptr_t)tcs));
			if (SIGCON_STAT_ISTHREAD((uintptr_t)tcs)) {
				struct task *thread = atomic_read(&tcs->tcs_thread);
				if (thread == target)
					break; /* Found our target! */
			}
			receiver = receiver->sc_next;
			if (receiver == sigctl) {
				sigcon_verify_ring_aftersend(sigctl);
				atomic_write(&self->s_con, sigctl); /* Release SMP-lock */
				LOCAL_runcleanup();                 /* for sig_send_cleanup */
#ifndef LOCAL_IS_NOPR
				preemption_pop(&was);
#endif /* !LOCAL_IS_NOPR */
				return false;
			}
		}

		/* Figure out what's going to the queue's new head. */
		remainder = sigctl;
		if unlikely(remainder == receiver) {
			remainder = receiver->sc_next;
			if unlikely(remainder == receiver)
				remainder = NULL; /* Special case: last connection goes away */
		}
	}
#endif /* LOCAL_HAVE_flags || LOCAL_HAVE_target */
#ifdef LOCAL_HAVE_flags
	else
#endif /* LOCAL_HAVE_flags */
#if defined(LOCAL_HAVE_flags) || !defined(LOCAL_HAVE_target)
	{
		/* Default target selection algorithm */
		if (atomic_read_relaxed(&receiver->sc_stat) & SIGCON_STAT_F_POLL) {
			/* Try  to find a  non-polling receiver, and if  we manage to find
			 * one, shove all of the poll-based ones to the back of the queue. */
			struct sigcon *poll_head;
			struct sigcon *poll_tail;
			do {
				assert(receiver->sc_prev->sc_next == receiver);
				assert(receiver->sc_next->sc_prev == receiver);
				assert((receiver->sc_next != receiver) || (receiver->sc_next == sigctl));
				receiver = receiver->sc_next;
				if (receiver == sigctl) {
					/* All  remaining   connections  are   poll-based.
					 * Essentially the same as "sig_broadcast()", but:
					 * - Allowed to assume that the wait queue is non-empty
					 * - Inherits the SMP-lock to "self"
					 * - Inherits the preemption state in "was"
					 * For more info, see description of `sig_broadcast()` */

					unsigned int bcast_flags = (LOCAL_flags & ~SIG_XSEND_F_NOPR) | SIG_XSEND_F_LOCKED |
					                           (LOCAL_preemption_wason() ? 0 : SIG_XSEND_F_NOPR);
#ifdef LOCAL_HAVE_flags
					if (phase2) {
						sig_xbroadcast(self, bcast_flags, LOCAL_sender_OPT,
						               LOCAL_caller, LOCAL_cleanup_OPT,
						               LOCAL_reprime, LOCAL_destroy_later);
						sig_run_phase_2(phase2, &context);
						return false;
					}
#endif /* LOCAL_HAVE_flags */

					/* NOTE: This call should always return "0" */
					return sig_xbroadcast(self, bcast_flags, LOCAL_sender_OPT,
					                      LOCAL_caller, LOCAL_cleanup_OPT,
					                      LOCAL_reprime, LOCAL_destroy_later);
				}
			} while (atomic_read_relaxed(&receiver->sc_stat) & SIGCON_STAT_F_POLL);

			/* Shove the chain of poll-based receivers to the back of the queue. */
			poll_head = sigctl;
			poll_tail = receiver->sc_prev;
			assert(poll_tail != receiver);
			assert(poll_tail->sc_next == receiver);

			/* Unlink poll-based connections from queue */
			poll_head->sc_prev->sc_next = receiver;
			receiver->sc_prev = poll_head->sc_prev;

			remainder = receiver->sc_next;
			assert(remainder != receiver);

			/* Re-insert poll-based connections before "remainder" (which will become the queue's
			 * new head, meaning that anything that appears before it will actually appear at the
			 * end of the queue) */
			poll_head->sc_prev = remainder->sc_prev;
			poll_head->sc_prev->sc_next = poll_head;
			poll_tail->sc_next = remainder;
			remainder->sc_prev = poll_tail;
		} else {
			remainder = receiver->sc_next;
			if unlikely(remainder == receiver)
				remainder = NULL; /* Special case: last connection goes away */
		}
	}
#endif /* LOCAL_HAVE_flags || !LOCAL_HAVE_target */

	/* Remove "receiver" from the wait queue. */
	assert(receiver != remainder);
	assert(receiver->sc_prev->sc_next == receiver);
	assert(receiver->sc_next->sc_prev == receiver);
	receiver->sc_prev->sc_next = receiver->sc_next;
	receiver->sc_next->sc_prev = receiver->sc_prev;

	/* Load the status/task word of "receiver" */
	tcs = atomic_read_relaxed(&receiver->sc_cons);
	assert(SIGCON_STAT_ISCONNECTED((uintptr_t)tcs));

	/* Deal with completion-callbacks */
#if defined(LOCAL_HAVE_flags) || !defined(LOCAL_HAVE_target)
	if unlikely(SIGCON_STAT_ISCOMP((uintptr_t)tcs)) {
#ifdef LOCAL_HAVE_flags
		/* Signal completion callback. */
		context.scc_sender = sender;
		context.scc_caller = caller;
		invoke_sig_completion(&phase2, (struct sigcon_comp *)receiver, &context);

		if (!(context.scc_status & SIG_COMPLETION__F_REPRIME) || (flags & SIG_XSEND_F_FINI)) {
			/* Release out ownership of "receiver" (if it wasn't reprimed) */
			atomic_write(&receiver->sc_stat, SIGCON_STAT_ST_THRSENT);
		} else {
			/* Re-prime connection */
			if (reprime == NULL) {
				sigcon_link_self(receiver);
				reprime = receiver;
			} else {
				sigcon_link_insert_before(receiver, reprime);
			}
			sigcon_verify_ring_afterinsert(reprime);
		}

		/* Deal with the case where the completion function didn't accept the signal. */
		if (context.scc_status & SIG_COMPLETION__F_NONVIABLE)
			goto handle_non_viable_receiver;
#else /* LOCAL_HAVE_flags */
#ifdef LOCAL_HAVE_destroy_later
#error "Invalid configuration"
#endif /* LOCAL_HAVE_destroy_later */
		return sig_completion_invoke_and_unlock_and_preemption_pop(self,
		                                                           LOCAL_sender,
		                                                           (struct sigcon_comp *)receiver,
		                                                           remainder,
		                                                           LOCAL_caller,
		                                                           LOCAL_reprime, /* XXX: This should always be "NULL" */
		                                                           LOCAL_cleanup,
		                                                           LOCAL_was,
		                                                           LOCAL_flags);
#endif /* !LOCAL_HAVE_flags */
	} else
#endif /* LOCAL_HAVE_flags || !LOCAL_HAVE_target */
	{
		tcs = (struct taskcons *)((uintptr_t)tcs & ~SIGCON_STAT_F_POLL);
		assert(SIGCON_STAT_ISTHREAD((uintptr_t)tcs));

		/* Try to set out signal as the sender. "sig_altsend"
		 * sets the given  signal here,  rather than  "self". */
		if (!atomic_cmpxch(&tcs->tcs_deliver, NULL, LOCAL_sender)) {
			/* Failed to deliver signal :(
			 * - Mark the receiver for broadcast
			 * - Jump back to find another receiver (this one we already removed from the queue) */
			atomic_write(&receiver->sc_stat, SIGCON_STAT_ST_THRBCAST); /* This releases our ownership of "receiver" */

#ifdef LOCAL_HAVE_flags
handle_non_viable_receiver:
#endif /* LOCAL_HAVE_flags */
			/* Check for special case: no other connections remain. */
			if (!remainder) {
#if defined(LOCAL_HAVE_reprime) && !defined(sigcon_verify_ring_IS_NOOP)
				if (LOCAL_reprime)
					sigcon_verify_ring_aftersend(LOCAL_reprime);
#endif /* LOCAL_HAVE_reprime && !sigcon_verify_ring_IS_NOOP */
				atomic_write(&self->s_con, LOCAL_reprime);
				LOCAL_runcleanup();
#ifndef LOCAL_IS_NOPR
				preemption_pop(&was);
#endif /* !LOCAL_IS_NOPR */
#ifdef LOCAL_HAVE_destroy_later
				destroy_tasks(destroy_later);
#endif /* LOCAL_HAVE_destroy_later */
#ifdef LOCAL_HAVE_flags
				sig_run_phase_2(phase2, &context);
#endif /* LOCAL_HAVE_flags */
				return false;
			}

			/* vvv this write  isn't necessary,  because "self->s_con"  isn't anywhere  after
			 *     the "again_find_receiver" label (because there is no jump back to "again",
			 *     which is the only place where such a read happens) */
			sigcon_verify_ring_duringsend(remainder);
//			atomic_write(&self->s_con, (struct sigcon *)((uintptr_t)remainder | SIG_SMPLOCK)); /* Keep SMP-lock */
			sigctl = remainder;
			goto again_find_receiver;
		}
	}

	/* Merge remaining connections with those that ought to be re-primed. */
#ifdef LOCAL_HAVE_reprime
	remainder = combine_remainder_and_reprime(remainder, reprime);
#endif /* LOCAL_HAVE_reprime */

	/* First signal delivered -> must wake the thread after locks were released. */
	{
		REF struct task *thread;
		thread = xincref(atomic_read(&tcs->tcs_thread));
		atomic_write(&receiver->sc_stat, SIGCON_STAT_ST_THRSENT); /* This releases our ownership of "receiver" */
#ifndef sigcon_verify_ring_IS_NOOP
		if (remainder)
			sigcon_verify_ring_aftersend(remainder);
#endif /* !sigcon_verify_ring_IS_NOOP */
		atomic_write(&self->s_con, remainder);                    /* Release SMP-lock */
		LOCAL_runcleanup();                                       /* for sig_send_cleanup */
#ifndef LOCAL_IS_NOPR
		preemption_pop(&was);
#endif /* !LOCAL_IS_NOPR */
		if (thread) {
			LOCAL_task_wake(thread);
			decref_unlikely(thread);
		}
	}
#ifdef LOCAL_HAVE_destroy_later
	destroy_tasks(destroy_later);
#endif /* LOCAL_HAVE_destroy_later */
#ifdef LOCAL_HAVE_flags
	sig_run_phase_2(phase2, &context);
#endif /* LOCAL_HAVE_flags */
	return true;
#endif /* !LOCAL_IS_BROADCAST */
#undef LOCAL_cleanup_OPT
#undef LOCAL_sender_OPT
#undef LOCAL_destroy_later
#undef LOCAL_reprime
#undef LOCAL_runcleanup
#undef LOCAL_cleanup
#undef LOCAL_sender
#undef LOCAL_caller
#undef LOCAL_was
#undef LOCAL_preemption_wason
#undef LOCAL_maxcount_MINUS_result
}

#undef LOCAL_task_yield
#undef LOCAL_task_wake

#undef LOCAL_cleanup_restrict
#undef LOCAL_task_restrict
#undef LOCAL_sig_restrict
#undef LOCAL_return_t

DECL_END

/*[[[deemon (printSigSendCInlTail from "...include.sched.sig-config")();]]]*/
#undef LOCAL_sig_send
#undef LOCAL_IS_BROADCAST
#undef LOCAL_IS_XSEND
#undef LOCAL_IS_NOPR
#undef LOCAL_IS_FINI
#undef LOCAL_HAVE_maxcount
#undef LOCAL_HAVE_flags
#undef LOCAL_HAVE_sender
#undef LOCAL_HAVE_caller
#undef LOCAL_HAVE_target
#undef LOCAL_HAVE_cleanup
#undef LOCAL_HAVE_reprime
#undef LOCAL_HAVE_destroy_later
#undef LOCAL_flags

#undef DEFINE_sig_altbroadcastas_for_fini_cleanup_nopr
#undef DEFINE_sig_broadcastas_for_fini_cleanup_nopr
#undef DEFINE_sig_altbroadcastas_for_fini_nopr
#undef DEFINE_sig_broadcastas_for_fini_nopr
#undef DEFINE_sig_altbroadcastas_for_fini
#undef DEFINE_sig_broadcastas_for_fini
#undef DEFINE_sig_altbroadcastas_cleanup_nopr
#undef DEFINE_sig_broadcastas_cleanup_nopr
#undef DEFINE_sig_altbroadcastas_nopr
#undef DEFINE_sig_broadcastas_nopr
#undef DEFINE_sig_altbroadcastas
#undef DEFINE_sig_broadcastas
#undef DEFINE_sig_altbroadcast_for_fini_cleanup_nopr
#undef DEFINE_sig_broadcast_for_fini_cleanup_nopr
#undef DEFINE_sig_altbroadcast_cleanup_nopr
#undef DEFINE_sig_broadcast_cleanup_nopr
#undef DEFINE_sig_altbroadcast_for_fini_nopr
#undef DEFINE_sig_broadcast_for_fini_nopr
#undef DEFINE_sig_altbroadcast_for_fini
#undef DEFINE_sig_broadcast_for_fini
#undef DEFINE_sig_altbroadcast_nopr
#undef DEFINE_sig_broadcast_nopr
#undef DEFINE_sig_altbroadcast
#undef DEFINE_sig_broadcast
#undef DEFINE_sig_altsendmanyas_cleanup_nopr
#undef DEFINE_sig_sendmanyas_cleanup_nopr
#undef DEFINE_sig_altsendmanyas_nopr
#undef DEFINE_sig_sendmanyas_nopr
#undef DEFINE_sig_altsendmanyas
#undef DEFINE_sig_sendmanyas
#undef DEFINE_sig_altsendmany_cleanup_nopr
#undef DEFINE_sig_sendmany_cleanup_nopr
#undef DEFINE_sig_altsendmany_nopr
#undef DEFINE_sig_sendmany_nopr
#undef DEFINE_sig_altsendmany
#undef DEFINE_sig_sendmany
#undef DEFINE_sig_altsendasto_cleanup_nopr
#undef DEFINE_sig_sendasto_cleanup_nopr
#undef DEFINE_sig_altsendasto_nopr
#undef DEFINE_sig_sendasto_nopr
#undef DEFINE_sig_altsendasto
#undef DEFINE_sig_sendasto
#undef DEFINE_sig_altsendto_cleanup_nopr
#undef DEFINE_sig_sendto_cleanup_nopr
#undef DEFINE_sig_altsendto_nopr
#undef DEFINE_sig_sendto_nopr
#undef DEFINE_sig_altsendto
#undef DEFINE_sig_sendto
#undef DEFINE_sig_altsendas_cleanup_nopr
#undef DEFINE_sig_sendas_cleanup_nopr
#undef DEFINE_sig_altsendas_nopr
#undef DEFINE_sig_sendas_nopr
#undef DEFINE_sig_altsendas
#undef DEFINE_sig_sendas
#undef DEFINE_sig_altsend_cleanup_nopr
#undef DEFINE_sig_send_cleanup_nopr
#undef DEFINE_sig_altsend_nopr
#undef DEFINE_sig_send_nopr
#undef DEFINE_sig_altsend
#undef DEFINE_sig_send
#undef DEFINE_sig_xsendmany
#undef DEFINE_sig_xsend
/*[[[end]]]*/
