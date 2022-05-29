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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_TB_H
#define GUARD_KERNEL_INCLUDE_KERNEL_TB_H 1

#include <kernel/compiler.h>

#include <kernel/syslog.h>
#include <kernel/types.h>

#include <bits/crt/format-printer.h>

#ifdef __CC__
DECL_BEGIN

struct ucpustate;
struct lcpustate;
struct kcpustate;
struct icpustate;
struct scpustate;
struct fcpustate;

/* Dump   a  traceback  for  the  given  cpu  state.
 * Tracebacks are printed using `addr2line_printf()' */
FUNDEF NONNULL((1)) ssize_t FCALL print_traceback(__pformatprinter printer, void *arg, unsigned int n_skip DFL(0));
FUNDEF NONNULL((1, 3)) ssize_t FCALL print_traceback_ucpustate(__pformatprinter printer, void *arg, struct ucpustate const *__restrict state, unsigned int n_skip DFL(0));
FUNDEF NONNULL((1, 3)) ssize_t FCALL print_traceback_lcpustate(__pformatprinter printer, void *arg, struct lcpustate const *__restrict state, unsigned int n_skip DFL(0));
FUNDEF NONNULL((1, 3)) ssize_t FCALL print_traceback_kcpustate(__pformatprinter printer, void *arg, struct kcpustate const *__restrict state, unsigned int n_skip DFL(0));
FUNDEF NONNULL((1, 3)) ssize_t FCALL print_traceback_icpustate(__pformatprinter printer, void *arg, struct icpustate const *__restrict state, unsigned int n_skip DFL(0));
FUNDEF NONNULL((1, 3)) ssize_t FCALL print_traceback_scpustate(__pformatprinter printer, void *arg, struct scpustate const *__restrict state, unsigned int n_skip DFL(0));
FUNDEF NONNULL((1, 3)) ssize_t FCALL print_traceback_fcpustate(__pformatprinter printer, void *arg, struct fcpustate const *__restrict state, unsigned int n_skip DFL(0));

/* Print a traceback to the system log, using `KERN_RAW' */
FUNDEF void FCALL tb(void);
FUNDEF void FCALL tbn(unsigned int n_skip);
LOCAL NONNULL((1)) void FCALL tb_ucpustate(struct ucpustate const *__restrict state, unsigned int n_skip DFL(0)) { print_traceback_ucpustate(&syslog_printer, SYSLOG_LEVEL_RAW, state, n_skip); }
LOCAL NONNULL((1)) void FCALL tb_lcpustate(struct lcpustate const *__restrict state, unsigned int n_skip DFL(0)) { print_traceback_lcpustate(&syslog_printer, SYSLOG_LEVEL_RAW, state, n_skip); }
LOCAL NONNULL((1)) void FCALL tb_kcpustate(struct kcpustate const *__restrict state, unsigned int n_skip DFL(0)) { print_traceback_kcpustate(&syslog_printer, SYSLOG_LEVEL_RAW, state, n_skip); }
LOCAL NONNULL((1)) void FCALL tb_icpustate(struct icpustate const *__restrict state, unsigned int n_skip DFL(0)) { print_traceback_icpustate(&syslog_printer, SYSLOG_LEVEL_RAW, state, n_skip); }
LOCAL NONNULL((1)) void FCALL tb_scpustate(struct scpustate const *__restrict state, unsigned int n_skip DFL(0)) { print_traceback_scpustate(&syslog_printer, SYSLOG_LEVEL_RAW, state, n_skip); }
LOCAL NONNULL((1)) void FCALL tb_fcpustate(struct fcpustate const *__restrict state, unsigned int n_skip DFL(0)) { print_traceback_fcpustate(&syslog_printer, SYSLOG_LEVEL_RAW, state, n_skip); }

#ifdef __cplusplus
extern "C++" {
FUNDEF void FCALL tb(unsigned int n_skip) ASMNAME("tbn");
LOCAL NONNULL((1)) void FCALL tb(struct ucpustate const *__restrict state, unsigned int n_skip DFL(0)) { tb_ucpustate(state, n_skip); }
LOCAL NONNULL((1)) void FCALL tb(struct lcpustate const *__restrict state, unsigned int n_skip DFL(0)) { tb_lcpustate(state, n_skip); }
LOCAL NONNULL((1)) void FCALL tb(struct kcpustate const *__restrict state, unsigned int n_skip DFL(0)) { tb_kcpustate(state, n_skip); }
LOCAL NONNULL((1)) void FCALL tb(struct icpustate const *__restrict state, unsigned int n_skip DFL(0)) { tb_icpustate(state, n_skip); }
LOCAL NONNULL((1)) void FCALL tb(struct scpustate const *__restrict state, unsigned int n_skip DFL(0)) { tb_scpustate(state, n_skip); }
LOCAL NONNULL((1)) void FCALL tb(struct fcpustate const *__restrict state, unsigned int n_skip DFL(0)) { tb_fcpustate(state, n_skip); }
} /* extern "C++" */
#endif /* __cplusplus */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_TB_H */
