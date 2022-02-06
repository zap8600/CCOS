#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "../drivers/floppy.h"

int svstr = 0;
char usrstr[20];

void main() {
	clear_screen();
	kprint("Installing Interrupts...");
    isr_install();
    irq_install();
    kprint("\nCotton Candy Shell v0.0.2\n"
        "Type  HELP  for commands.\n> ");
}

void user_input(char *input) {
    if (strcmp(input, "HELP") == 0) {
        kprint("\nHELP  Displays this information.\n"
               "END  Halts the CPU.\n"
               "PAGE  Requests a kmalloc().\n"
			   "FLOPPY CHECK  Waits until the floppy drive is ready.\n"
			   "CLEAR  Clears the screen.\n"
			   "SAVE STRING  Saves a string from the user.\n"
			   "READ STRING  Reads the saved string\n"
			   "FLOPPY VERSION  Checks what floppy controller is found.\n"
               "\n> ");
    } else if (strcmp(input, "END") == 0) {
        kprint("\nStopping the CPU. Bye!\n"
               "You can now power off your computer.\n");
        asm volatile ("hlt");
    } else if (strcmp(input, "PAGE") == 0) {
		kprint("\n");
        u32 phys_addr;
        u32 page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n\n> ");
    } else if (strcmp(input, "FLOPPY CHECK") == 0) {
		floppy_wait_until_ready();
		kprint("\nFloppy is now ready.\n"
		       "\n> ");
	} else if (strcmp(input, "CLEAR") == 0) {
		clear_screen();
		kprint("> ");
	} else if (strcmp(input, "FLOPPY VERSION") == 0) {
		int v;
		floppy_wait_until_ready();
		floppy_sendbyte(VERSION);
		v = floppy_getbyte();
		if (v == 0xFF) {
			kprint("\nFloppy Controller not found.\n");
		} else if (v == 0x80) {
			kprint("\nNEC Floppy Controller found.\n");
		} else if (v == 0x81) {
			kprint("\nVMware Floppy Controller found.\n");
		} else if (v == 0x90) {
			kprint("\nEnhanced Floppy Controller found.\n");
		} else {
			kprint("\nUnknown Floppy Controller found.\n");
		}
		kprint("\n> ");
	} else if (strcmp(input, "SAVE STRING") == 0) {
		svstr = 1;
		kprint("\nPlease input string."
		       "\nOnly one string will be saved"
			   "\n20 characters max.\n"
			   "\n> ");
	} else if (svstr == 1) {
		svstr = 0;
		strcpy(usrstr, input);
		kprint("\nString saved!\n"
		       "\n> ");
	} else if (strcmp(input, "READ STRING") == 0) {
		kprint("\nYour string is: ");
		kprint(usrstr);
		kprint("\n\n> ");
	} else {
		kprint("\n");
        kprint(input);
        kprint(" is an invalid command.\n"
               "Type HELP for list of commands.\n"
               "\n> ");
    }
}