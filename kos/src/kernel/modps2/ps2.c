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
#ifndef GUARD_MODPS2_PS2_C
#define GUARD_MODPS2_PS2_C 1
#define _KOS_SOURCE 1

#include "ps2.h"

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/isr.h>
#include <kernel/printk.h>
#include <kernel/x86/pic.h> /* TODO: Non-portable! */
#include <sched/tsc.h>

#include <atomic.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>

#include "keyboard.h"
#include "mouse.h"

DECL_BEGIN

/* Refs:
 *   - http://www.scs.stanford.edu/14wi-cs140/pintos/specs/kbd/scancodes-9.html#ss9.1
 *   - http://www.scs.stanford.edu/14wi-cs140/pintos/specs/kbd/scancodes.html#toc11
 *   - https://wiki.osdev.org/PS/2_Keyboard
 *   - http://www.vetra.com/scancodes.html
 *   - https://www.win.tue.nl/~aeb/linux/kbd/scancodes-13.html
 */


/* Probing code from here on... */
PRIVATE NOBLOCK NOPREEMPT ATTR_FREETEXT void
NOTHROW(FCALL ps2_probe_process_data)(struct ps2_probe_data *__restrict probe_data,
                                      ps2_portid_t portno, u8 data) {
	struct ps2_probe_data &port = probe_data[portno];
/*	printk(KERN_DEBUG "[ps2#%" PRIu8 "] Received %#.2I8x\n", portno + 1, data);*/
	switch (port.pd_state) {

	case PS2_PROBE_STATE_UNCONFIGURED:
		if (data == 0xfa) {
			port.pd_status |= PS2_PROBE_STATUS_FACK;
		} else {
handle_resend_or_other:
			if (data == 0xfe) {
				port.pd_status |= PS2_PROBE_STATUS_FRESEND;
			} else {
				printk(KERN_WARNING "[ps2#%" PRIu8 "] Unexpected byte during probe %#.2I8x\n", portno + 1, data);
			}
		}
		break;

	case PS2_PROBE_STATE_ID_ACK:
		if (data == 0xfa) {
			port.pd_state = PS2_PROBE_STATE_ID_0;
		} else {
			goto handle_resend_or_other;
		}
		break;

	case PS2_PROBE_STATE_ID_0:
		port.pd_data.pd_id[0] = data;
		port.pd_state = PS2_PROBE_STATE_ID_1;
		break;

	case PS2_PROBE_STATE_ID_1:
		port.pd_data.pd_id[1] = data;
		port.pd_state = PS2_PROBE_STATE_UNCONFIGURED;
		break;

	case PS2_PROBE_STATE_DATA_ACK:
		if (data == 0xfa) {
			port.pd_state = PS2_PROBE_STATE_DATA_0;
		} else {
			goto handle_resend_or_other;
		}
		break;

	case PS2_PROBE_STATE_DATA_0:
		port.pd_data.pd_dat[0] = data;
		port.pd_state = PS2_PROBE_STATE_UNCONFIGURED;
		break;

	default:
		break;
	}
	sig_broadcast_nopr(&port.pd_avail);
}


PRIVATE NOBLOCK NOPREEMPT ATTR_FREETEXT bool
NOTHROW(FCALL ps2_probe_handle_interrupt)(void *arg) {
	u8 data, status = inb(PS2_STATUS);
	printk(KERN_TRACE "[ps2] ps2_probe_handle_interrupt: %#.2I8x\n", status);
	struct ps2_probe_data *probe = (struct ps2_probe_data *)arg;
	if (status & PS2_STATUS_OUTFULL2) {
		data = inb(PS2_DATA);
		ps2_probe_process_data(probe, PS2_PORT2, data);
	} else if (status & PS2_STATUS_OUTFULL) {
		data = inb(PS2_DATA);
		ps2_probe_process_data(probe, PS2_PORT1, data);
	} else {
		return false;
	}
	return true;
}


INTERN ATTR_FREETEXT void KCALL
ps2_probe_run_simple_ack_command(struct ps2_probe_data *__restrict probe_data,
                                 ps2_portid_t portno, u8 command) THROWS(E_IOERROR) {
	unsigned int attempt = 0;
	u8 status;
again:
	probe_data[portno].pd_status = 0;
	probe_data[portno].pd_state  = PS2_PROBE_STATE_UNCONFIGURED;
	COMPILER_WRITE_BARRIER();
	ps2_write_data(portno, command);
	for (;;) {
		ktime_t tmo;
		status = atomic_read(&probe_data[portno].pd_status);
		if (status != 0)
			break;
		task_connect_for_poll(&probe_data[portno].pd_avail);
		status = atomic_read(&probe_data[portno].pd_status);
		if (status != 0) {
			task_disconnectall();
			break;
		}
		tmo = ktime();
		tmo += relktime_from_milliseconds(ps2_command_timeout);
		if (!task_waitfor(tmo))
			THROW(E_IOERROR_TIMEOUT, E_IOERROR_SUBSYSTEM_HID);
	}
	if (status & PS2_PROBE_STATUS_FACK)
		return;
	if unlikely(attempt >= ps2_command_attempts)
		THROW(E_IOERROR_ERRORBIT, E_IOERROR_SUBSYSTEM_HID);
	++attempt;
	goto again;
}

INTERN ATTR_FREETEXT u8 KCALL
ps2_probe_run_ack_plus_data_command(struct ps2_probe_data *__restrict probe_data,
                                    ps2_portid_t portno, u8 command) THROWS(E_IOERROR) {
	unsigned int attempt = 0;
	u8 state, status;
again:
	probe_data[portno].pd_status = 0;
	probe_data[portno].pd_state  = PS2_PROBE_STATE_DATA_ACK;
	COMPILER_WRITE_BARRIER();
	ps2_write_data(portno, command);
	for (;;) {
		ktime_t tmo;
		state  = atomic_read(&probe_data[portno].pd_state);
		status = atomic_read(&probe_data[portno].pd_status);
		if (state == PS2_PROBE_STATE_UNCONFIGURED || (status & PS2_PROBE_STATUS_FRESEND))
			break;
		task_connect_for_poll(&probe_data[portno].pd_avail);
		state  = atomic_read(&probe_data[portno].pd_state);
		status = atomic_read(&probe_data[portno].pd_status);
		if (state == PS2_PROBE_STATE_UNCONFIGURED || (status & PS2_PROBE_STATUS_FRESEND)) {
			task_disconnectall();
			break;
		}
		tmo = ktime();
		tmo += relktime_from_milliseconds(ps2_command_timeout);
		if (!task_waitfor(tmo)) {
			state  = atomic_read(&probe_data[portno].pd_state);
			status = atomic_read(&probe_data[portno].pd_status);
			if (status & PS2_PROBE_STATUS_FRESEND)
				goto try_resend;
			THROW(E_IOERROR_TIMEOUT, E_IOERROR_SUBSYSTEM_HID);
		}
	}
	if (state == PS2_PROBE_STATE_UNCONFIGURED)
		return probe_data[portno].pd_data.pd_dat[0];
try_resend:
	if unlikely(attempt >= ps2_command_attempts)
		THROW(E_IOERROR_ERRORBIT, E_IOERROR_SUBSYSTEM_HID);
	++attempt;
	goto again;
}


INTERN ATTR_FREETEXT u8 KCALL
ps2_run_identify_command(struct ps2_probe_data *__restrict probe_data,
                         ps2_portid_t portno, u8 id[2]) THROWS(E_IOERROR) {
	unsigned int attempt = 0;
	u8 state, status;
again:
	probe_data[portno].pd_status = 0;
	probe_data[portno].pd_state  = PS2_PROBE_STATE_ID_ACK;
	COMPILER_WRITE_BARRIER();
	ps2_write_data(portno, PS2_KEYBOARD_CMD_IDENTIFY);
	for (;;) {
		ktime_t tmo;
		state  = atomic_read(&probe_data[portno].pd_state);
		status = atomic_read(&probe_data[portno].pd_status);
		if (state == PS2_PROBE_STATE_UNCONFIGURED || (status & PS2_PROBE_STATUS_FRESEND))
			break;
		task_connect_for_poll(&probe_data[portno].pd_avail);
		state  = atomic_read(&probe_data[portno].pd_state);
		status = atomic_read(&probe_data[portno].pd_status);
		if (state == PS2_PROBE_STATE_UNCONFIGURED || (status & PS2_PROBE_STATUS_FRESEND)) {
			task_disconnectall();
			break;
		}
		tmo = ktime();
		tmo += relktime_from_milliseconds(ps2_command_timeout);
		if (!task_waitfor(tmo)) {
			state  = atomic_read(&probe_data[portno].pd_state);
			status = atomic_read(&probe_data[portno].pd_status);
			if (status & PS2_PROBE_STATUS_FRESEND)
				goto try_resend;
			if (state == PS2_PROBE_STATE_ID_0)
				return 0; /* 0 identify bytes. */
			if (state == PS2_PROBE_STATE_ID_1) {
				id[0] = probe_data[portno].pd_data.pd_id[0];
				return 1; /* 1 identify byte. */
			}
			THROW(E_IOERROR_TIMEOUT, E_IOERROR_SUBSYSTEM_HID);
		}
	}
	if (state == PS2_PROBE_STATE_UNCONFIGURED) {
		id[0] = probe_data[portno].pd_data.pd_id[0];
		id[1] = probe_data[portno].pd_data.pd_id[1];
		return 2; /* 2 identify bytes. */
	}
try_resend:
	if unlikely(attempt >= ps2_command_attempts)
		THROW(E_IOERROR_ERRORBIT, E_IOERROR_SUBSYSTEM_HID);
	++attempt;
	goto again;
}




PRIVATE ATTR_FREETEXT void KCALL
ps2_probe_port(struct ps2_probe_data *__restrict probe_data,
               ps2_portid_t portno) {
	u8 nid_port, id_port[2];
	TRY {
		ps2_probe_run_simple_ack_command(probe_data, portno, PS2_KEYBOARD_CMD_DISABLE_SCANNING);
	} EXCEPT {
		if (!was_thrown(E_IOERROR))
			RETHROW();
		except_printf(FREESTR("disabling scanning on ps2 port #%u"),
		              portno + 1);
	}
	nid_port = ps2_run_identify_command(probe_data, portno, id_port);
	if (nid_port == 0) {
init_keyboard:
		ps2_keyboard_create(probe_data, portno);
	} else if (nid_port == 2 && id_port[0] == 0xab) {
		/* Assume that any 2-byte sequence that starts with `0xab' is a keyboard */
		goto init_keyboard;
	} else if (nid_port == 1 && id_port[0] == 0x00) {
init_mouse:
		ps2_mouse_create(probe_data, portno);
	} else {
		printk(FREESTR(KERN_WARNING "[ps2] Failed to detect device on port #%u [id=["), portno + 1);
		if (nid_port >= 1)
			printk(FREESTR(KERN_WARNING "%#.2I8x"), id_port[0]);
		if (nid_port >= 2)
			printk(FREESTR(KERN_WARNING ",%#.2I8x"), id_port[1]);
		printk(FREESTR(KERN_WARNING "]] assume it's a %s\n"),
		       portno == PS2_PORT1 ? FREESTR("keyboard")
		                           : FREESTR("mouse"));
		if (portno == PS2_PORT1)
			goto init_keyboard;
		goto init_mouse;
	}
}

PRIVATE ATTR_FREETEXT void KCALL
ps2_probe_install_handlers(struct ps2_probe_data *__restrict probe_data) {
	isr_register_at(X86_INTNO_PIC1_KBD, /* TODO: Non-portable! */
	                &ps2_probe_handle_interrupt, probe_data);
	isr_register_at(X86_INTNO_PIC2_PS2M, /* TODO: Non-portable! */
	                &ps2_probe_handle_interrupt, probe_data);
}

PRIVATE ATTR_FREETEXT void KCALL
ps2_probe_delete_handlers(struct ps2_probe_data *__restrict probe_data) {
	isr_unregister_at(X86_INTNO_PIC1_KBD, /* TODO: Non-portable! */
	                  &ps2_probe_handle_interrupt, probe_data);
	isr_unregister_at(X86_INTNO_PIC2_PS2M, /* TODO: Non-portable! */
	                  &ps2_probe_handle_interrupt, probe_data);
}

PRIVATE ATTR_FREEBSS struct ps2_probe_data ps2_probe_data_buffer[PS2_PORTCOUNT];

PRIVATE NOBLOCK ATTR_FREETEXT bool
NOTHROW(KCALL early_poll_probe)(u8 *__restrict presult) {
	unsigned int i;
	for (i = 0; i < PS2_PORTCOUNT; ++i) {
		if (ps2_probe_data_buffer[i].pd_state == PS2_PROBE_STATE_UNCONFIGURED) {
			/* Some data byte was received by this port! */
			*presult = ps2_probe_data_buffer[i].pd_data.pd_dat[0];
			return true;
		}
	}
	return false;
}

PRIVATE NOBLOCK ATTR_FREETEXT bool
NOTHROW(KCALL early_poll_outport)(u8 *__restrict presult) {
	u8 status;
	/* Check the status port before checking  for interrupts such that the  check
	 * happens interlocked with a possible interrupt happening between us reading
	 * the status port, and us reading the data port (where reading the data port
	 * clears the PS2_STATUS_OUTFULL bit of the status port, which might also  be
	 * done by the interrupt handler) */
	COMPILER_BARRIER();
	status = inb_p(PS2_STATUS);
	COMPILER_BARRIER();
	if (early_poll_probe(presult))
		return true;
	COMPILER_BARRIER();
	/* Check if the status port indicates that data may be available. */
	if (status & PS2_STATUS_OUTFULL) {
		u8 data;
		data = inb_p(PS2_DATA);
		COMPILER_BARRIER();
		/* Check once again for the possibility that what we've just
		 * read into `data' may have been garbage when an  interrupt
		 * could have already performed the read before we did. */
		if (early_poll_probe(presult))
			return true;
		/* Nope! No interrupt has done the deed of reading the port,
		 * so  we  know that  `data'  is the  correct  result value.
		 * FIXME: This only works when PS/2 interrupt are handled
		 *        by the same CPU as the one that we're currently
		 *        running under! */
		*presult = data;
		return true;
	}
	return false;
}

PRIVATE ATTR_FREETEXT DRIVER_INIT void KCALL ps2_init(void) {
	u8 data;
	ps2_portid_t portno;
	bzero(ps2_probe_data_buffer, sizeof(ps2_probe_data_buffer));
	ps2_probe_install_handlers(ps2_probe_data_buffer);
	RAII_FINALLY { ps2_probe_delete_handlers(ps2_probe_data_buffer); };

	/* Configure the PS/2 controller. */
	ps2_write_cmd(PS2_CONTROLLER_DISABLE_PORT1);
	ps2_write_cmd(PS2_CONTROLLER_DISABLE_PORT2);
	inb_p(PS2_DATA); /* Make sure that there is no dangling data */

	/* Workaround: If the  controller is  configured to  have interrupts  enabled
	 *             for  either PORT1 or  PORT2, then instead of  us being able to
	 *             read  command data  in the  following call,  the response byte
	 *             will have already been read by `ps2_probe_handle_interrupt()',
	 *             such that the following line will cause an exception
	 *             `E_IOERROR_TIMEOUT:E_IOERROR_SUBSYSTEM_HID'   to   be   thrown.
	 *             The problem here is that the bit  that can tell us if the  PS/2
	 *             controller is able to trigger interrupts right now is contained
	 *             in the very byte which we're trying to extract from the  thing.
	 * Solution:   Configure the probe controller to accept interrupt data while
	 *             simultaneously polling the port ourself.
	 *             This gives us 3 different paths to success:
	 *               #1: We manage to read the port ourself and interrupts were disabled.
	 *               #2: We manage to read the port ourself and interrupts were enabled,
	 *                   and  the device  did send an  interrupt that was  entered as an
	 *                   Unhandled interrupt.
	 *               #3: We don't manage to read the port ourself, but we do notice that
	 *                   one  of  the  probe  controllers  has  received  a  data  byte. */
	{
		unsigned int i;
		for (i = 0; i < PS2_PORTCOUNT; ++i)
			ps2_probe_data_buffer[i].pd_state = PS2_PROBE_STATE_DATA_0;
	}
	COMPILER_BARRIER();
	ps2_write_cmd(PS2_CONTROLLER_RRAM(0));
	COMPILER_BARRIER();
	if (!early_poll_outport(&data)) {
		/* Setup a timeout. */
		struct timespec timeout;
		timeout = realtime();
		timeout.add_milliseconds(ps2_outfull_timeout);
		while (!early_poll_outport(&data)) {
			if unlikely(realtime() > timeout)
				THROW(E_IOERROR_TIMEOUT, E_IOERROR_SUBSYSTEM_HID);
			task_tryyield_or_pause();
		}
	}

	/* Set up the PS/2 device configuration. */
	data |= (PS2_CONTROLLER_CFG_PORT1_IRQ |
	         PS2_CONTROLLER_CFG_PORT2_IRQ |
	         PS2_CONTROLLER_CFG_SYSTEMFLAG);
	data &= ~(PS2_CONTROLLER_CFG_PORT1_TRANSLATE);
	ps2_write_cmd(PS2_CONTROLLER_WRAM(0));
	ps2_write_cmddata((u8)data);
	ps2_write_cmd(PS2_CONTROLLER_ENABLE_PORT2);
	ps2_write_cmd(PS2_CONTROLLER_ENABLE_PORT1);

	/* Try to probe PS/2 ports. */
	for (portno = 0; portno < PS2_PORTCOUNT; ++portno) {
		TRY {
			ps2_probe_port(ps2_probe_data_buffer, portno);
		} EXCEPT {
			if (!was_thrown(E_IOERROR))
				RETHROW();
			except_printf("probing ps/2 port #%u", portno + 1);
		}
	}
}


DECL_END

#endif /* !GUARD_MODPS2_PS2_C */
