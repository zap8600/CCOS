#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"

void main() {
    isr_install();
    irq_install();

    clear_screen();
    kprint("Cotton Candy Shell vID\n"
        "Type  HELP  for commands.\n> ");
}

void user_input(char *input) {
    if (strcmp(input, "HELP") == 0) {
        kprint("HELP  Displays this information.\n"
               "END  Halts the CPU.\n"
               "PAGE  Requests a kmalloc().\n"
               "> ");
    } else if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU. Bye!\n"
               "You can now power off your computer.\n");
        asm volatile ("hlt");
    } else if (strcmp(input, "PAGE") == 0) {
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
        kprint("\n> ");
    } else {
        kprint(input);
        kprint(" is an invalid command.\n"
               "Type HELP for list of commands.\n"
               "> ");
    }
}
