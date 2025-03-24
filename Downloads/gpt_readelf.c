#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// ELF header structures
typedef struct {
    uint8_t e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} Elf64_Ehdr;

void print_elf_header(const Elf64_Ehdr *header) {
    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", header->e_ident[i]);
    }
    printf("\n");
    printf("  Type:                                 %x\n", header->e_type);
    printf("  Machine:                              %x\n", header->e_machine);
    printf("  Version:                              %x\n", header->e_version);
    printf("  Entry point address:                  %lx\n", header->e_entry);
    printf("  Start of program headers:             %lx (bytes into file)\n", header->e_phoff);
    printf("  Start of section headers:             %lx (bytes into file)\n", header->e_shoff);
    printf("  Flags:                                %x\n", header->e_flags);
    printf("  Size of this header:                  %d (bytes)\n", header->e_ehsize);
    printf("  Size of program header entry:         %d (bytes)\n", header->e_phentsize);
    printf("  Number of program header entries:     %d\n", header->e_phnum);
    printf("  Size of section header entry:         %d (bytes)\n", header->e_shentsize);
    printf("  Number of section header entries:     %d\n", header->e_shnum);
    printf("  Section header string table index:    %d\n", header->e_shstrndx);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <elf_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    Elf64_Ehdr header;
    if (fread(&header, sizeof(header), 1, file) != 1) {
        perror("Error reading file");
        fclose(file);
        return 1;
    }

    print_elf_header(&header);

    fclose(file);
    return 0;
}
