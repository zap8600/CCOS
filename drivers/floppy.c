#include "../cpu/ports.h"
#include "floppy.h"
#include "../cpu/isr.h"
#include "../libc/function.h"
#include "screen.h"

int fdc_flag = 0;

enum FloppyRegisters {
	STATUS_REGISTER_A = 0x3F0,
	STATUS_REGISTER_B = 0x3F1,
	DIGITAL_OUTPUT_REGISTER = 0x3F2,
	TAPE_DRIVE_REGISTER = 0x3F3,
	MAIN_STATUS_REGISTER = 0x3F4,
	DATARATE_SELECT_REGISTER = 0x3F4,
	DATA_FIFO = 0x3F5,
	DIGITAL_INPUT_REGISTER = 0x3F7,
	CONFIGURATION_CONTROL_REGISTER = 0x3F7
};

enum MSRBitflags {
	RQM = 0x80,
	DIO = 0x40,
	NDMA = 0x20,
	CB = 0x10,
	ACTD = 8,
	ACTC = 4,
	ACTB = 2,
	ACTA = 1
};

int floppy_wait_until_ready() {
	int counter, status;
	for(counter = 0; counter < 10000; counter++) {
		status = port_byte_in(MAIN_STATUS_REGISTER);
		if(status & RQM) {
			return(status);
		}
	}
	return (-1);
}

void floppy_sendbyte(int b) {
	port_byte_out(DATA_FIFO, b);
}

int floppy_reset() {
	/* char devs[] = {0x1C, 0x2D, 0x4E, 0x8F}; */
	port_byte_out(DIGITAL_OUTPUT_REGISTER, 0x00);
	port_byte_out(CONFIGURATION_CONTROL_REGISTER, 0x00);
	port_byte_out(DIGITAL_OUTPUT_REGISTER, 0x0C);
	floppy_wait_until_ready();
	return 1;
}

static void floppy_callback(registers_t regs) {
	fdc_flag = 0;
	UNUSED(regs);
}

int init_floppy() {
	int flag;
	register_interrupt_handler(IRQ6, floppy_callback);
	flag = floppy_reset();
	if (flag == 0) {
		kprint("\nError on floppy driver init.\n");
		return 0;
	}
	return 1;
}
