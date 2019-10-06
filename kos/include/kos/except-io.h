/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_EXCEPT_IO_H
#define _KOS_EXCEPT_IO_H 1

#include <__stdinc.h>

__DECL_BEGIN

/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_IOERROR_REASON_GENERIC,         /* Generic error reason */
	E_IOERROR_REASON_ATA_DCR_ERR,     /* `ATA_DCR_ERR' was set */
	E_IOERROR_REASON_ATA_DCR_DF,      /* `ATA_DCR_DF' was set */
	E_IOERROR_REASON_ATA_DCR_ERR_DF,  /* `ATA_DCR_ERR' and `ATA_DCR_DF' were set */
	E_IOERROR_REASON_ATA_DCR_BSY,     /* Timeout while waiting for `ATA_DCR_BSY' */
	E_IOERROR_REASON_ATA_SECTOR_WAIT, /* Timeout while waiting for sector data */
	E_IOERROR_REASON_USB_SHORTPACKET, /* Short-packet-detect during a transfer without the `USB_TRANSFER_FLAG_SHORT' flag set. */
	E_IOERROR_REASON_UHCI_BADEP,      /* A `uhci_qh::qh_ep' field contained a bad value `POINTER[2]' */
	E_IOERROR_REASON_UHCI_TDCS,       /* At least one of the error bits of `UHCI_TDCS_*' is set (POINTER[2] is the `td_cs' field) */
	E_IOERROR_REASON_UHCI_INCOMPLETE, /* The `UHCI_TDCS_ACTIVE' bit got cleared without any apparent reason. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_IOERROR_REASON_GENERIC         E_IOERROR_REASON_GENERIC         /* Generic error reason */
#define E_IOERROR_REASON_ATA_DCR_ERR     E_IOERROR_REASON_ATA_DCR_ERR     /* `ATA_DCR_ERR' was set */
#define E_IOERROR_REASON_ATA_DCR_DF      E_IOERROR_REASON_ATA_DCR_DF      /* `ATA_DCR_DF' was set */
#define E_IOERROR_REASON_ATA_DCR_ERR_DF  E_IOERROR_REASON_ATA_DCR_ERR_DF  /* `ATA_DCR_ERR' and `ATA_DCR_DF' were set */
#define E_IOERROR_REASON_ATA_DCR_BSY     E_IOERROR_REASON_ATA_DCR_BSY     /* Timeout while waiting for `ATA_DCR_BSY' */
#define E_IOERROR_REASON_ATA_SECTOR_WAIT E_IOERROR_REASON_ATA_SECTOR_WAIT /* Timeout while waiting for sector data */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_IOERROR_REASON_GENERIC         0 /* Generic error reason */
#define E_IOERROR_REASON_ATA_DCR_ERR     1 /* `ATA_DCR_ERR' was set */
#define E_IOERROR_REASON_ATA_DCR_DF      2 /* `ATA_DCR_DF' was set */
#define E_IOERROR_REASON_ATA_DCR_ERR_DF  3 /* `ATA_DCR_ERR' and `ATA_DCR_DF' were set */
#define E_IOERROR_REASON_ATA_DCR_BSY     4 /* Timeout while waiting for `ATA_DCR_BSY' */
#define E_IOERROR_REASON_ATA_SECTOR_WAIT 5 /* Timeout while waiting for sector data */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/



__DECL_END

#endif /* !_KOS_EXCEPT_IO_H */
