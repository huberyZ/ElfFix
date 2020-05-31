#include "elf_header.h"
#include "log.h"
#include "util/util.h"
#include <string>

CElfHeader::CElfHeader()
{
    memset(&elfHeader, 0, sizeof(elfHeader));
}


CElfHeader::~CElfHeader()
{

}

bool CElfHeader::InitHeader(std::string content)
{
    if (content.size() < sizeof(Elf32_Ehdr)){
        Loge("init elf header err: elf size %d", content.size());
        return false;
    }

    memcpy((char *)&elfHeader, content.c_str(), sizeof(Elf32_Ehdr));

    return isValid();
}

static int GetElfMachine() {
#if defined(__arm__)
    return EM_ARM;
#elif defined(__aarch64__)
    return EM_AARCH64;
#elif defined(__i386__)
    return EM_386;
#elif defined(__mips__)
    return EM_MIPS;
#elif defined(__x86_64__)
    return EM_X86_64;
#endif

    return EM_ARM;
}

bool CElfHeader::isValid()
{
    if (memcmp(elfHeader.e_ident, ELFMAG, SELFMAG) != 0) {
        Logd("elf header magic is invalid.");
        return false;
    }

    int elfClass = elfHeader.e_ident[EI_CLASS];
    if (elfClass != ELFCLASS32) {
        Loge("elf is not 32bit")
        return false;
    }

    if (elfHeader.e_ident[EI_DATA] != ELFDATA2LSB) {
        Loge("elf header is not little-endian: %d", elfHeader.e_ident[EI_DATA]);
        return false;
    }

    if (elfHeader.e_type != ET_DYN) {
        Loge("elf header has unexpected e_type: %d", elfHeader.e_type);
        return false;
    }

    if (elfHeader.e_version != EV_CURRENT) {
        Loge("elf header has unexpected e_version: %d", elfHeader.e_version);
        return false;
    }

    if (elfHeader.e_machine != GetElfMachine()) {
        Loge("elf header has unexpected e_machine: %d", elfHeader.e_machine);
        return false;
    }

    Logd("elf header is valid");
    return true;
}

std::string CElfHeader::HeaderInfo()
{
    std::string elfHeader;
    elfHeader += ("Elf Header Size: " + Utils::Itoa(elfHeader.e_ehsize) + "\n");
    elfHeader += ("Type: " + getElfType(elfHeader.e_type) + "\n");
    elfHeader += ("Machine: " + Utils::Itoa(elfHeader.e_machine) + "\n");
    elfHeader += ("Version: " + Utils::Itoa(elfHeader.e_version) + "\n");
    elfHeader += ("Entry: " + Utils::Itoa(elfHeader.e_entry) + "\n");
    elfHeader += ("Program Header Offset: " + Utils::Itoa(elfHeader.e_phoff) + "\n");
    elfHeader += ("Program Header Item Size: " + Utils::Itoa(elfHeader.e_phentsize) + "\n");
    elfHeader += ("Program Header Count: " + Utils::Itoa(elfHeader.e_phnum) + "\n");
    elfHeader += ("Section Header Offset: " + Utils::Itoa(elfHeader.e_shoff) + "\n");
    elfHeader += ("Section Header Item Size: " + Utils::Itoa(elfHeader.e_shentsize) + "\n");
    elfHeader += ("Section Header Count: " + Utils::Itoa(elfHeader.e_shnum) + "\n");
    elfHeader += ("Section Header StringTable Index: " + Utils::Itoa(elfHeader.e_shstrndx) + "\n");
    elfHeader += ("Flags: " + Utils::Itoa(elfHeader.e_flags) + "\n");
    
    return elfHeader;
}

std::string CElfHeader::getElfType(Elf32_Half type)
{
    switch (type){
    case ET_NONE:
        return "ET_NONE";
    case ET_REL:
        return "ET_REL";
    case ET_EXEC:
        return "ET_EXEC";
    case ET_DYN:
        return "ET_DYN";
    case ET_CORE:
        return "ET_CORE";
    case ET_LOPROC:
        return "ET_LOPROC";
    case ET_HIPROC:
        return "ET_HIPROC";
    default:
        return "ET_UNKOWN";
    }
}

