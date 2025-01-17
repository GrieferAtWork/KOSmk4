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
#ifndef GUARD_MODGDBSERVER_GDB_INFO_H
#define GUARD_MODGDBSERVER_GDB_INFO_H 1

#include <kernel/compiler.h>

#include <format-printer.h>

#include "gdb.h"


DECL_BEGIN

struct task;
struct mman;

/* NOTE: All of the following functions return negative ERRNO values on failure. */
/* Print a human-readable name for `thread' */
INTDEF NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadName)(pformatprinter printer, void *arg,
                                       struct task *__restrict thread);

/* `qXfer:exec-file:read': Print the absolute filename for the original
 * binary  passed to exec()  when the process  of `thread' was started.
 * (`/proc/${PID_OF(thread)}/exe') */
INTDEF NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadExecFile)(pformatprinter printer, void *arg,
                                           struct task *__restrict thread,
                                           bool filename_only);

/* Print the commandline of a given `thread' */
INTDEF NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadCommandline)(pformatprinter printer, void *arg,
                                              struct task *__restrict thread);

/* `qXfer:features:read': Print the named features file `filename' */
INTDEF NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintFeaturesFile)(pformatprinter printer, void *arg,
                                         char const *__restrict filename);

/* `qXfer:libraries:read': Print the list of library loaded into the current process. */
INTDEF NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintLibraryList)(pformatprinter printer, void *arg,
                                        struct task *__restrict thread);
INTDEF NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintMManLibraryList)(pformatprinter printer, void *arg,
                                            struct mman *__restrict effective_mm);

/* `qXfer:threads:read': Print the list of threads apart of the current process. */
INTDEF NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadList)(pformatprinter printer, void *arg);

/* `qXfer:osdata:read:<name>': Print os-specific data.
 * @return: -ENOENT: Invalid `name' */
INTDEF NONNULL((1, 3, 4)) ssize_t
NOTHROW(FCALL GDBInfo_PrintOSData)(pformatprinter printer, void *arg,
                                   char const *__restrict name,
                                   struct task *__restrict thread);




DECL_END

#endif /* !GUARD_MODGDBSERVER_GDB_INFO_H */
