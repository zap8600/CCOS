#include "../cpu/ports.h"
#include "floppy.h"
#include "../cpu/isr.h"
#include "../libc/function.h"
#include "screen.h"

int fdc_flag = 0;
int fdc_status[7] = { 0 };
int ST0 = 0;
int fdc_track = 0xFF;

enum Datarates {
	TWOEIGHTEIGHT = 3,
	ONEFOURFOUR = 0
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

int floppy_getbyte() {
	int msr;
	msr = floppy_wait_until_ready();
	if (msr < 0) {
		return(-1);
	}
	return(port_byte_in(DATA_FIFO));
}

int floppy_sendbyte(int b) {
	int msr;
	msr = floppy_wait_until_ready();
	if (msr < 0) {
		return(-1);
	}
	port_byte_out(DATA_FIFO, b);
	return 0;
}

int floppy_wait(int sensei) {
	int i;
	fdc_flag = 1;
	while(fdc_flag) ;
	i = 0;
	while((i < 7) && (port_byte_in(MAIN_STATUS_REGISTER)) & CB) {
		fdc_status[i++] = floppy_getbyte();
	}
	if(sensei) {
		floppy_sendbyte(SENSE_INTERRUPT);
		ST0 = floppy_getbyte();
		fdc_track = floppy_getbyte();
	}
	return 1;
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
	int v;
	register_interrupt_handler(IRQ6, floppy_callback);
	flag = floppy_reset();
	if (flag == 0) {
		kprint("\nError on floppy driver init.\n");
		return 0;
	}
	floppy_sendbyte(VERSION);
	v = floppy_getbyte();
	if (v == 0xFF) {
		kprint("\nFloppy Controller not found.");
	} else if (v == 0x80) {
		kprint("\nNEC Floppy Controller found.");
	} else if (v == 0x81) {
		kprint("\nVMware Floppy Controller found.");
	} else if (v == 0x90) {
		kprint("\nEnhanced Floppy Controller found.");
	} else {
		kprint("\nUnknown Floppy Controller found.");
	}
	return 1;
}