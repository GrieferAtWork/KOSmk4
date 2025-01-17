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
#ifndef _HW_BUS_SERIAL_H
#define _HW_BUS_SERIAL_H 1

#include <__stdinc.h>

#include <sys/io.h>

/* Documentation derived from https://www.lammertbies.nl/comm/info/serial-uart.html */
#define SERIAL_IOADDR_RBR(base)  __IOPORT((base)+0) /* DLAB=0 Receiver buffer register (RO). */
#define SERIAL_IOADDR_THR(base)  __IOPORT((base)+0) /* DLAB=0 Transmitter holding register (WO). */
#define SERIAL_IOADDR_IER(base)  __IOPORT((base)+1) /* DLAB=0 Interrupt enable register (R/W). */
#define     SERIAL_EIR_RDA       0x01 /* Received data available */
#define     SERIAL_EIR_TRE       0x02 /* Transmitter holding register empty */
#define     SERIAL_EIR_RLSRC     0x04 /* Receiver line status register change */
#define     SERIAL_EIR_MSRC      0x08 /* Modem status register change */
#define     SERIAL_EIR_SM        0x10 /* Sleep mode (16750 only) */
#define     SERIAL_EIR_LPM       0x20 /* Low power mode (16750 only) */
#define SERIAL_IOADDR_IIR(base)  __IOPORT((base)+2) /* DLAB=0 Interrupt identification register (RO). */
#define     SERIAL_IRR_NIP       0x01 /* No interrupt pending */
#define     SERIAL_IRR_TYP       0x0e /* Mask for interrupt type. */
#define         SERIAL_IRR_TYP_MSC   0x00 /* Modem status change (reset by: MSR read) */
#define         SERIAL_IRR_TYP_TRE   0x02 /* Transmitter holding register empty (reset by: IIR read or THR write) */
#define         SERIAL_IRR_TYP_RDA   0x04 /* Received data available (reset by: RBR read) */
#define         SERIAL_IRR_TYP_LSC   0x06 /* Line status change (reset by: LSR read) */
#define         SERIAL_IRR_TYP_CTO   0x0c /* Character timeout (16550) (reset by: RBR read) */
#define     SERIAL_IRR_FIFO64    0x20 /* 64 byte FIFO enabled (16750) */
#define     SERIAL_IRR_FIFO      0xc0 /* Mask for FIFO mode */
#define         SERIAL_IRR_FIFO_NO   0x00 /* No FIFO */
#define         SERIAL_IRR_FIFO_BRK  0x80 /* Unusable FIFO (16550 only) */
#define         SERIAL_IRR_FIFO_YES  0xc0 /* FIFO enabled */
#define SERIAL_IOADDR_FCR(base)  __IOPORT((base)+2) /* DLAB=0 FIFO control register (WO). */
#define     SERIAL_FCR_ENABLED   0x01 /* Enable FIFO */
#define     SERIAL_FCR_CRFIFO    0x02 /* Clear receive FIFO */
#define     SERIAL_FCR_CTFIFO    0x04 /* Clear transmit FIFO */
#define     SERIAL_FCR_DMA       0x08 /* DMA mode mask */
#define         SERIAL_FCR_DMA_0     0x00 /* Select DMA mode 0 */
#define         SERIAL_FCR_DMA_1     0x08 /* Select DMA mode 1 */
#define     SERIAL_FCR_FIFO64    0x20 /* Enable 64 byte FIFO (16750) */
#define     SERIAL_FCR_RITL      0xc0 /* Mask for receive FIFO interrupt trigger level */
#define         SERIAL_FCR_RITL_1    0x00 /* 1 byte */
#define         SERIAL_FCR_RITL_4    0x40 /* 4 bytes */
#define         SERIAL_FCR_RITL_8    0x80 /* 8 bytes */
#define         SERIAL_FCR_RITL_14   0xc0 /* 14 bytes */
#define SERIAL_IOADDR_LCR(base)  __IOPORT((base)+3) /* Line control register (R/W). */
#define     SERIAL_LCR_DWL       0x03 /* Mask for data word length */
#define         SERIAL_LCR_DWL_5     0x00 /* 5 bits */
#define         SERIAL_LCR_DWL_6     0x01 /* 6 bits */
#define         SERIAL_LCR_DWL_7     0x02 /* 7 bits */
#define         SERIAL_LCR_DWL_8     0x03 /* 8 bits */
#define     SERIAL_LCR_STB       0x04 /* Mask for stop bit mode */
#define         SERIAL_LCR_STB_1     0x00 /* 1 stop bit */
#define         SERIAL_LCR_STB_1_5   0x04 /* 1.5 stop bits (SERIAL_LCR_DWL_5) */
#define         SERIAL_LCR_STB_2     0x04 /* 2 stop bits (SERIAL_LCR_DWL_6, SERIAL_LCR_DWL_7 or SERIAL_LCR_DWL_8) */
#define     SERIAL_LCR_PRT       0x1c /* Mask for parity mode */
#define         SERIAL_LCR_PRT_NO    0x00 /* No parity */
#define         SERIAL_LCR_PRT_ODD   0x04 /* Odd parity */
#define         SERIAL_LCR_PRT_EVEN  0x0c /* Even parity */
#define         SERIAL_LCR_PRT_HIGH  0x14 /* High parity (stick) */
#define         SERIAL_LCR_PRT_LOW   0x1c /* Low parity (stick) */
#define     SERIAL_LCR_BSE       0x40 /* Break signal enabled */
#define     SERIAL_LCR_DLAB      0x80 /* DLAB enable register (affects port behavior) */
#define SERIAL_IOADDR_MCR(base)  __IOPORT((base)+4) /* Modem control register (R/W). */
#define     SERIAL_MCR_DTR       0x01 /* Data terminal ready */
#define     SERIAL_MCR_RTS       0x02 /* Request to send */
#define     SERIAL_MCR_AXO1      0x04 /* Auxiliary output 1 */
#define     SERIAL_MCR_AXO2      0x08 /* Auxiliary output 2 */
#define     SERIAL_MCR_LPM       0x10 /* Loopback mode */
#define     SERIAL_MCR_AFC       0x20 /* Autoflow control (16750 only) */
#define SERIAL_IOADDR_LSR(base)  __IOPORT((base)+5) /* Line status register (RO). */
#define     SERIAL_LSR_DA        0x01 /* Data available */
#define     SERIAL_LSR_OE        0x02 /* Overrun error */
#define     SERIAL_LSR_PE        0x04 /* Parity error */
#define     SERIAL_LSR_FE        0x08 /* Framing error */
#define     SERIAL_LSR_BSR       0x10 /* Break signal received */
#define     SERIAL_LSR_THRE      0x20 /* THR is empty */
#define     SERIAL_LSR_THRELI    0x40 /* THR is empty, and line is idle */
#define     SERIAL_LSR_EFIFO     0x80 /* Errornous data in FIFO */
#define SERIAL_IOADDR_MSR(base)  __IOPORT((base)+6) /* Modem status register (RO). */
#define     SERIAL_MSR_CCS       0x01 /* change in Clear to send */
#define     SERIAL_MSR_CDR       0x02 /* change in Data set ready */
#define     SERIAL_MSR_TER       0x04 /* trailing edge Ring indicator */
#define     SERIAL_MSR_CCD       0x08 /* change in Carrier detect */
#define     SERIAL_MSR_CTS       0x10 /* Clear to send */
#define     SERIAL_MSR_DSR       0x20 /* Data set ready */
#define     SERIAL_MSR_RI        0x40 /* Ring indicator */
#define     SERIAL_MSR_CD        0x80 /* Carrier detect */
#define SERIAL_IOADDR_SCR(base)  __IOPORT((base)+7) /* Scratch register (R/W). */
#define SERIAL_IOADDR_DLL(base)  __IOPORT((base)+0) /* DLAB=1 divisor latch LSB */
#define SERIAL_IOADDR_DLM(base)  __IOPORT((base)+1) /* DLAB=1 divisor latch MSB */
#define     SERIAL_DL_50         0x0900 /* speed: 50      divisor: 2304 */
#define     SERIAL_DL_300        0x0180 /* speed: 300     divisor: 384 */
#define     SERIAL_DL_1200       0x0060 /* speed: 1200    divisor: 96 */
#define     SERIAL_DL_2400       0x0030 /* speed: 2400    divisor: 48 */
#define     SERIAL_DL_4800       0x0018 /* speed: 4800    divisor: 24 */
#define     SERIAL_DL_9600       0x000C /* speed: 9600    divisor: 12 */
#define     SERIAL_DL_19200      0x0006 /* speed: 19200   divisor: 6 */
#define     SERIAL_DL_38400      0x0003 /* speed: 38400   divisor: 3 */
#define     SERIAL_DL_57600      0x0002 /* speed: 57600   divisor: 2 */
#define     SERIAL_DL_115200     0x0001 /* speed: 115200  divisor: 1 */



#endif /* !_HW_BUS_SERIAL_H */
