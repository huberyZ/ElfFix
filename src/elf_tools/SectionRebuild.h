
#ifndef __SECTION_REBUILD_H__
#define __SECTION_REBUILD_H__

/******************************************************************************/
#include <string>
#include <vector>

class SectionRebuild
{
public:
    SectionRebuild();
 
    ~SectionRebuild();
    
    bool Rebuild(std::string elfPath);

    bool SaveRebuildElf(std::string dstFile);

private:
    bool loadElf();

    bool createSections();

    bool rebuildSymTabSize();

    bool rebuildSymItemSectionRef();

    int calcAddrSectionIdx(Elf32_Off offset);

    int calcVaFaGap(Elf32_Addr section_addr);

    int findStringIdxInStrtab(std::string str);
    
private:
    std::string elfContent; 

private:
    std::vector<ElfSegment> vecSegment;
    DynSection dynSection; 

    std::vector<ElfSection> elfSection;

    //string used to create .shstrtab
    std::string shStrTab;
};
#endif