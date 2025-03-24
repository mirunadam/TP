#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <elf.h>

void find_sys(unsigned char u){
	switch (u)
	{
	case 0x00:
		printf("System V\n");
		break;
	case 0x01:
		printf("HP-UX\n");
		break;
	case 0x02:
		printf("NetBSD\n");
		break;
	case 0x03:
		printf("Linux\n");
		break;
	case 0x04:
		printf("GNU Hurd\n");
		break;
	case 0x06:
		printf("Solaris\n");
		break;
	case 0x07:
		printf("AIX\n");
		break;
	case 0x08:
		printf("IRIX\n");
		break;
	case 0x09:
		printf("FreeBDS\n");
		break;
	case 0x0A:
		printf("Tru64\n");
		break;
	case 0x0B:
		printf("Novell Modesto\n");
		break;
	case 0x0C:
		printf("OpenBSD\n");
		break;
	case 0x0D:
		printf("OpenVMS\n");
		break;
	case 0x0E:
		printf("NonStop Kernel\n");
		break;
	case 0x0F:
		printf("AROS\n");
		break;
	case 0x10:
		printf("FenixOS\n");
		break;
	case 0x11:
		printf("Nuxi CloudABI\n");
		break;
	case 0x12:
		printf("Stratus Technologies OpenVOS\n");
		break;
	default: printf("...mystery...\n");
		break;
	}
}

void find_type(unsigned int u[2]){
	switch (u[2])
	{
	case 0x00:
		printf("unknown\n");
		break;
	case 0x01:
		printf("relocatable file\n");
		break;
	case 0x02:
		printf("Executable file\n");
		break;
	case 0x03:
		printf("Shared object\n");
		break;
	case 0x04:
		printf("Core file\n");
		break;
	case 0xFE00:
		printf("Reserved inclusive range. Operating system specific. \n");
		break;
	case 0xFEFF:
		printf("Reserved inclusive range. Operating system specific. \n");
		break;
	case 0xFF00:
		printf("Reserved inclusive range. Processor specific.  \n");
		break;
	case 0xFFFF:
		printf("Reserved inclusive range. Processor specific.  \n");
		break;
	default: printf("...mystery...\n");
		break;
	}
}

void find_machine(unsigned char u[2]){
	switch (u[2])
	{

	case 0x01:
		printf("AT&T WE 32100\n");
		break;
	case 0x02:
		printf("SPARC\n");
		break;
	case 0x03:
		printf("x86\n");
		break;
	case 0x04:
		printf("Motorola 68000 (M68k)\n");
		break;
	case 0x05:
		printf("Motorola 88000 (M88k)\n");
		break;
	case 0x06:
		printf("Intel MCU\n");
		break;
	case 0x07:
		printf("Intel 80860\n");
		break;
	case 0x08:
		printf("MIPS\n");
		break;
	case 0x09:
		printf("IBM System/370\n");
		break;
	case 0x0A:
		printf("MIPS RS3000 Little-endian\n");
		break;
	case 0x0F:
		printf("Hewlett-Packard PA-RISC\n");
		break;
	case 0x13:
		printf("Intel 80960\n");
		break;
	case 0x2B:
		printf("SPARC Version 9\n");
		break;
	case 0x2C:
		printf("Siemens TriCore embedded processor\n");
		break;
    case 0x2D:
            printf("Argonaut RISC Core\n");
            break;
    case 0x2E:
            printf("Hitachi H8/300\n");
            break;
    case 0x2F:
            printf("Hitachi H8/300H\n");
            break;
    case 0x30:
            printf("Hitachi H8S\n");
            break;
    case 0x31:
            printf("Hitachi H8/500\n");
            break;
    case 0x32:
            printf("IA-64\n");
            break;
    case 0x33:
            printf("Stanford MIPS-X\n");
            break;
    case 0x34:
            printf("Motorola ColdFire\n");
            break;
    case 0x35:
            printf("Motorola M68HC12\n");
            break;
    case 0x36:
            printf("Fujitsu MMA Multimedia Accelerator\n");
            break;
    case 0x37:
            printf("Siemens PCP\n");
            break;
    case 0x38:
            printf("Sony nCPU embedded RISC processor\n");
            break;
    case 0x39:
            printf("Denso NDR1 microprocessor\n");
            break;
    case 0x3A:
            printf("Motorola Star*Core processor\n");
            break;			
    case 0x3B:
            printf("Toyota ME16 processor\n");
            break;
    case 0x3C:
            printf("STMicroelectronics ST100 processor\n");
            break;
    case 0x3D:
            printf("Advanced Logic Corp. TinyJ embedded processor family\n");
            break;
    case 0x3e:
            printf("AMD x86-64\n");
            break;
    case 0x3F:
            printf("Sony DSP Processor\n");
            break;
    case 0x40:
            printf("Digital Equipment Corp. PDP-10\n");
            break;
    case 0x41:
            printf("Digital Equipment Corp. PDP-11\n");
            break;
    case 0x42:
            printf("Siemens FX66 microcontroller\n");
            break;
    case 0x43:
            printf("STMicroelectronics ST9+ 8/16 bit microcontroller\n");
            break;
    case 0x44:
            printf("STMicroelectronics ST7 8-bit microcontroller\n");
            break;
    case 0x45:
            printf("Motorola MC68HC16 Microcontroller\n");
            break;
    case 0x46:
            printf("Motorola MC68HC11 Microcontroller\n");
            break;
    case 0x47:
            printf("Motorola MC68HC08 Microcontroller\n");
            break;
    case 0x48:
            printf("Motorola MC68HC05 Microcontroller\n");
            break;
    case 0x49:
            printf("Silicon Graphics SVx\n");
            break;
    case 0x4A:
            printf("STMicroelectronics ST19 8-bit microcontroller\n");
            break;
    case 0x4B:
            printf("Digital VAX\n");
            break;
    case 0x4C:
            printf("Axis Communications 32-bit embedded processor\n");
            break;
    case 0x4D:
            printf("Infineon Technologies 32-bit embedded processor\n");
            break;
    case 0x4E:
            printf("Element 14 64-bit DSP Processor\n");
            break;
    case 0x4F:
            printf("LSI Logic 16-bit DSP Processor\n");
            break;
    case 0x8C:
            printf("TMS320C6000 Family\n");
            break;
    case 0xAF:
            printf("MCST Elbrus e2k\n");
            break;
    case 0xB7:
            printf("Arm 64-bits (Armv8/AArch64)\n");
            break;
    case 0xDC:
            printf("Zilog Z80\n");
            break;
    case 0xF3:
            printf("RISC-V\n");
            break;
    case 0xF7:
            printf("Berkeley Packet Filter\n");
            break;
    case 0x101:
            printf("WDC 65C816\n");
            break;
	default: printf("...mystery...\n");
		break;
	}
}


int main(int argc, char *argv[]) {
	FILE *fp;
	unsigned char magic;
	unsigned char elf[3];

	if (argc != 2) {
		printf("Wrong number of arguments. Use:\n");
		printf("%s filename.x\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	printf("Start processing..\n");

	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		perror("fopen()");
		exit(EXIT_FAILURE);
	}

	if (fread(&magic, 1, 1, fp) != 1) {
		perror("fread()");
		exit(EXIT_FAILURE);
	}

	if (magic == 0x7f) printf("Magic valure for ELF found\n");
	else {
		printf("This seems not to be a valid ELF program\n");
		exit(EXIT_FAILURE);
	}

	if (fread(elf, 3, 1, fp) != 1) {
		perror("fread()\n");
		printf("Line number is %u\n", __LINE__);
		printf("Source code file is %s\n", __FILE__);
		exit(EXIT_FAILURE);
	}

	if ((elf[0] != 'E') || (elf[1] != 'L') || 
	    (elf[2] != 'F')) {
		printf("This is not an ELF file!!\n");
		exit(EXIT_FAILURE);
	} else printf("ELF file found! Printing header:\n");

	unsigned char class;
	int check_format=0;
	if(fread(&class, 1, 1, fp)!=0){
		printf("class: ");
		if(class == 0x2){
			printf("ELF64\n");
			check_format=1;
		}
		else if(class == 0x1){
			printf("ELF32\n");
		}
	}
	unsigned char data;
	if(fread(&data, 1, 1, fp)!=0){
		printf("data: ");
		if(data == 0x1){
			printf("little endian\n");
		}
		else if(data == 0x2){
			printf("big endian\n");
		}
	}
	unsigned char version;
	if(fread(&version, 1, 1, fp)!=0){
		printf("version: ");
		if(version == 0x1){
			printf("1, current version\n");
		}
	}

	unsigned char osabi;
	if(fread(&osabi, 1,1, fp)!=0){
		printf("operating system: ");
		find_sys(osabi);
	}

	unsigned char abi_version;
	if(fread(&abi_version, 1, 1, fp)!=0){
		printf("ABI version: %x\n", abi_version);
	}
	
	unsigned char padd[7];
	if(fread(&padd, 7, 1, fp)!=0){
		printf("Padding bytes read\n");
	}
	


	unsigned int type[2];
	if(fread(&type, 2, 1, fp)!=0){
		printf("file type: ");
		find_type(type);
	}

	unsigned char machine[2];
	if(fread(&machine, 2, 1, fp)!=0){
		printf("machine arhitecture: ");
		find_machine(machine);
	}



unsigned char version2[4];
if(fread(&version2, 4, 1, fp)!=0){
	if (version2==0x01){
		printf("version: ");
		printf("%x\n", version2);
	}
}

if(check_format==0){
	unsigned char entry[4];
	unsigned char phoff[4];
	unsigned char shoff[4];
	if(fread(&entry, 4, 1, fp)!=0){
		printf("entry point address: ");
		printf("0x%x\n", entry);
	}
	if(fread(&phoff, 4, 1, fp)!=0){
		printf("pointer to the start of the program header: ");
		printf("0x%x\n", phoff);
	}
	if(fread(&shoff, 4, 1, fp)!=0){
		printf("pointer to the start of the section header table: ");
		printf("0x%x\n", shoff);
	}
}
else if(check_format==1){
	unsigned char entry[8];
	unsigned char phoff[8];
	unsigned char shoff[8];
	if(fread(&entry, 8, 1, fp)!=0){
		printf("entry point address: ");
		printf("0x%x\n", entry);
	}
	if(fread(&phoff, 8, 1, fp)!=0){
		printf("pointer to the start of the program header: ");
		printf("0x%x\n", phoff);
	}
	if(fread(&shoff, 8, 1, fp)!=0){
		printf("pointer to the start of the section header table: ");
		printf("0x%x\n", shoff);
	}
}

uint16_t flags;
if(fread(&flags, 4, 1, fp)!=0){
		printf("flags: ");
		printf("0x%x\n", flags);
	}
uint16_t ehsize;
if(fread(&ehsize, 2, 1, fp)!=0){
		printf("size of header: ");
		if(check_format==0){
			printf("52 bytes\n");
		}
		if(check_format==1){
			printf("64 bytes\n");
		}
	}

uint16_t phentsize;
if(fread(&phentsize, 2, 1, fp)!=0){
		printf("size of the header table entry: ");
		if(phentsize==0x20){
			printf("32 bit\n");
		}
		if(phentsize==0x38){
			printf("64 bit\n");
		}
	}
uint16_t phnum;
if(fread(&phnum, 2, 1, fp)!=0){
		printf("number of entries in the program header table: ");
		printf("%d\n", phnum);
	}


uint16_t shentsize;
if(fread(&shentsize, 2, 1, fp)!=0){
		printf("size of the section header table entry: ");
		if(shentsize==0x28){
			printf("32 bit\n");
		}
		if(shentsize==0x40){
			printf("64 bit\n");
		}
	}

uint16_t shnum;
if(fread(&shnum, 2, 1, fp)!=0){
		printf("number of entries in the section header table: ");
		printf("%x\n", shnum);
	}

uint16_t shstrndx;
if(fread(&shstrndx, 2, 1, fp)!=0){
		printf("index of the section header table entry that contains the section names: ");
		printf("%d\n", shstrndx);
	}

	if (fclose(fp) != 0) {
		perror("fclose()");
		exit(EXIT_FAILURE);	
	}

	return 0;
}
