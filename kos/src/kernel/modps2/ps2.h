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
#ifndef GUARD_MODPS2_PS2_H
#define GUARD_MODPS2_PS2_H 1

#include <kernel/compiler.h>

#include <kernel/except.h> /* THROW() */
#include <kernel/types.h>  /* jtime_t */
#include <sched/cpu.h>     /* jiffies */
#include <sched/task.h>    /* task_tryyield_or_pause */
#include <sched/signal.h>  /* struct sig */

#include <kos/io/ps2.h> /* PS2_* */
#include <sys/io.h>     /* (in|out)(b|w|l)[_p]() */

DECL_BEGIN

/* PS/2 port ids */
#define PS2_PORT1     0
#define PS2_PORT2     1
#define PS2_PORTCOUNT 2
typedef u8 ps2_portid_t; /* `PS2_PORT1' or `PS2_PORT2' */


INTDEF unsigned int ps2_infull_timeout;
INTDEF unsigned int ps2_outfull_timeout;
INTDEF unsigned int ps2_command_timeout;
INTDEF unsigned int ps2_command_attempts;

#define PS2_GET_ISR_FOR_PORT(portno) ((portno) == PS2_PORT1 ? X86_INTNO_PIC1_KBD : X86_INTNO_PIC2_PS2M)


/* Wait until `PS2_STATUS_INFULL' is clear */
LOCAL bool NOTHROW(KCALL ps2_waitfor_infull0_nx)(void) {
	jtime_t jtm_end = jiffies + ps2_infull_timeout;
	while (inb_p(PS2_STATUS) & PS2_STATUS_INFULL) {
		if unlikely(jiffies > jtm_end)
			return false;
		task_tryyield_or_pause();
	}
	return true;
}

/* Wait until `PS2_STATUS_OUTFULL' is set */
LOCAL bool NOTHROW(KCALL ps2_waitfor_outfull1_nx)(void) {
	jtime_t jtm_end = jiffies + ps2_outfull_timeout;
	while (!(inb_p(PS2_STATUS) & PS2_STATUS_OUTFULL)) {
		if unlikely(jiffies > jtm_end)
			return false;
		task_tryyield_or_pause();
	}
	return true;
}

LOCAL bool NOTHROW(KCALL ps2_write_cmd_nx)(u8 cmd) {
	if unlikely(!ps2_waitfor_infull0_nx())
		return false;
	outb_p(PS2_CMD, cmd);
	return true;
}
LOCAL bool NOTHROW(KCALL ps2_read_cmddata_nx)(u8 *__restrict presult) {
	if unlikely(!ps2_waitfor_outfull1_nx())
		return false;
	*presult = inb_p(PS2_DATA);
	return true;
}
LOCAL bool NOTHROW(KCALL ps2_write_cmddata_nx)(u8 data) {
	if unlikely(!ps2_waitfor_infull0_nx())
		return false;
	outb_p(PS2_DATA, data);
	return true;
}
LOCAL bool NOTHROW(KCALL ps2_write_data_nx)(ps2_portid_t portno, u8 data) {
	if (portno == PS2_PORT2) {
		if unlikely(!ps2_waitfor_infull0_nx())
			return false;
		outb_p(PS2_CMD, PS2_CONTROLLER_WRITE_PORT2_INPUT);
	}
	if unlikely(!ps2_waitfor_infull0_nx())
		return false;
	outb_p(PS2_DATA, data);
	return true;
}



LOCAL void KCALL ps2_write_cmd(u8 cmd) THROWS(E_IOERROR) {
	if unlikely(!ps2_write_cmd_nx(cmd))
		THROW(E_IOERROR_TIMEOUT, E_IOERROR_SUBSYSTEM_HID);
}
LOCAL u8 KCALL ps2_read_cmddata(void) THROWS(E_IOERROR) {
	u8 result;
	if unlikely(!ps2_read_cmddata_nx(&result))
		THROW(E_IOERROR_TIMEOUT, E_IOERROR_SUBSYSTEM_HID);
	return result;
}
LOCAL void KCALL ps2_write_cmddata(u8 data) THROWS(E_IOERROR) {
	if unlikely(!ps2_write_cmddata_nx(data))
		THROW(E_IOERROR_TIMEOUT, E_IOERROR_SUBSYSTEM_HID);
}
LOCAL void KCALL ps2_write_data(ps2_portid_t portno, u8 data) THROWS(E_IOERROR) {
	if unlikely(!ps2_write_data_nx(portno, data))
		THROW(E_IOERROR_TIMEOUT, E_IOERROR_SUBSYSTEM_HID);
}



/* Probing code from here on... */
#define PS2_PROBE_STATUS_FACK    0x01 /* Received `0xfa' */
#define PS2_PROBE_STATUS_FRESEND 0x02 /* Received `0xfe' */
#define PS2_PROBE_STATE_UNCONFIGURED 0x00 /* No special state. */
#define PS2_PROBE_STATE_ID_ACK       0x01 /* -> PS2_PROBE_STATE_ID_0 (expecting `0xfa'; reset to `PS2_PROBE_STATE_UNCONFIGURED' on error) */
#define PS2_PROBE_STATE_ID_0         0x02 /* -> PS2_PROBE_STATE_ID1 (expecting first byte `pd_id[0]') */
#define PS2_PROBE_STATE_ID_1         0x03 /* -> PS2_PROBE_STATE_UNCONFIGURED (expecting second byte `pd_id[1]') */
#define PS2_PROBE_STATE_DATA_ACK     0x04 /* -> PS2_PROBE_STATE_DATA_0 (expecting `0xfa'; reset to `PS2_PROBE_STATE_UNCONFIGURED' on error) */
#define PS2_PROBE_STATE_DATA_0       0x05 /* -> PS2_PROBE_STATE_UNCONFIGURED (expecting first byte `pd_dat[0]') */

struct ps2_probe_data {
	uint8_t    pd_state;  /* State machine state (One of `PS2_PROBE_STATE_*'). */
	uint8_t    pd_status; /* State machine status (Set of `PS2_PROBE_STATUS_F*'). */
	union {
		uint8_t pd_id[2];  /* ID bytes. */
		uint8_t pd_dat[1]; /* Data bytes. */
	} pd_data;
	struct sig pd_avail; /* Broadcast when a response is received */
};

INTDEF FREE void KCALL
ps2_probe_run_simple_ack_command(struct ps2_probe_data *__restrict probe_data,
                                 ps2_portid_t portno, u8 command) THROWS(E_IOERROR);
INTDEF FREE u8 KCALL
ps2_probe_run_ack_plus_data_command(struct ps2_probe_data *__restrict probe_data,
                                    ps2_portid_t portno, u8 command) THROWS(E_IOERROR);
INTDEF FREE u8 KCALL
ps2_run_identify_command(struct ps2_probe_data *__restrict probe_data,
                         ps2_portid_t portno, u8 id[2]) THROWS(E_IOERROR);



DECL_END

#endif /* !GUARD_MODPS2_PS2_H */
