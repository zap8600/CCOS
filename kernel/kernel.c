#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"

void main() {
    isr_install();
    irq_install();

    kprint("Cotton Candy Shell v1.0 DEV\n"
        "Type  HELP  for commands.\n> ");
}

void user_input(char *input) {
    if (strcmp(input, "HELP") == 0) {
        kprint("\nCD  Change folders"
            "\nDIR  List files in current folder
            "\nMKDIR");
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
}
