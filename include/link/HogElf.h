#include "HogBase.h"

constexpr unsigned char ARCH = 2; // 64 bit elf. If you're not on 64 bit, you don't deserve my code.
constexpr unsigned char ELF[]{0x7F, 0x45, 0x4c, 0x46};

struct Elf64_Ehdr 
{
    unsigned char e_ident[16];  // ELF header - I.E. `.elf`
    uint16_t      e_type;       // Object file type (e.g., executable, shared object, relocatable)
    uint16_t      e_machine;    // Target architecture (e.g., x86, ARM, PowerPC)
    uint32_t      e_version;    // ELF specification version
    uint64_t      e_entry;      // Virtual address of the entry point (where execution begins)
    uint64_t      e_phoff;      // Offset to the program header table
    uint64_t      e_shoff;      // Offset to the section header table
    uint32_t      e_flags;      // Processor-specific flags
    uint16_t      e_ehsize;     // Size of the ELF header (in bytes)
    uint16_t      e_phentsize;  // Size of each entry in the program header table (in bytes)
    uint16_t      e_phnum;      // Number of entries in the program header table
    uint16_t      e_shentsize;  // Size of each entry in the section header table (in bytes)
    uint16_t      e_shnum;      // Number of entries in the section header table
    uint16_t      e_shstrndx;   // Section header table index of the section containing section names
};

namespace ElfUtils
{
    bool HostSystemIsLittleEndian();
    bool HostSystemIsBigEndian();
    Elf64_Ehdr ConstructHeaderForHostMachine();

    /* FIXME: Unimplemented
     * 
     * enum class TargetSystem {};
     * bool TargetSystemIsLittleEndian(TargetSystem aTargetSystem);
     * bool TargetSystemIsBigEndian(TargetSystem aTargetSystem);
     */
}

