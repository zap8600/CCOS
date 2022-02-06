int floppy_wait_until_ready();
int floppy_getbyte();
int floppy_sendbyte(int b);
int floppy_wait(int sensi);
int floppy_reset();
int init_floppy();

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

enum FloppyCommands {
	READ_TRACK = 2,
	SPECIFY = 3,
	SENSE_DRIVE_STATUS = 4,
	WRITE_DATA = 5,
	READ_DATA = 6,
	RECALIBRATE = 7,
	SENSE_INTERRUPT = 8,
	WRITE_DELETED_DATA = 9,
	READ_ID = 10,
	READ_DELETED_DATA = 12,
	FORMAT_TRACK = 13,
	DUMPREG = 14,
	SEEK = 15,
	VERSION = 16,
	SCAN_EQUAL = 17,
	PERPENDICULAR_MODE = 18,
	CONFIGURE = 19,
	LOCK = 20,
	VERIFY = 22,
	SCAN_LOW_OR_EQUAL = 25,
	SCAN_HIGH_OR_EQUAL = 29
};

enum DORBitflags {
	MOTD = 0x80,
	MOTC = 0x40,
	MOTB = 0x20,
	MOTA = 0x10,
	IRQ = 8,
	RESET = 4,
	DSEL1_0 = 3
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
