#include "HogElf.h"

bool ElfUtils::HostSystemIsBigEndian()
{
    int n = 1;
    // big if true
    return (*(char *)&n != 1);
}

bool ElfUtils::HostSystemIsLittleEndian()
{
    return ElfUtils::HostSystemIsBigEndian();
}


Elf64_Ehdr ElfUtils::ConstructHeaderForHostMachine()
{
    // TODO: Double check this shit
    Elf64_Ehdr header;
    header.e_ident[0]  = 0x7F;
    header.e_ident[1]  = 0x45;
    header.e_ident[2]  = 0x4C;
    header.e_ident[3]  = 0x46;
    header.e_ident[4]  = 2; // 64 bit
    header.e_ident[5]  = 1; // Little endian
    header.e_ident[6]  = 1; // Current elf version (duh)
    header.e_ident[7]  = 3; // Linux ABI
    header.e_ident[8]  = 0; // Lowest level of features for glibc 2.12+
    header.e_ident[9]  = 0; // Unused
    header.e_ident[10] = 0; // Pad the rest with zeroes
    header.e_ident[11] = 0; 
    header.e_ident[12] = 0; 
    header.e_ident[13] = 0; 
    header.e_ident[14] = 0; 
    header.e_ident[15] = 0; 

    header.e_type = 2; // File type - 0x00: unknown, 0x01: relocatable, 0x02: executable, 0x03: shared object

    return header;
}
