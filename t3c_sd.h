#include "SD.h"
#include "FS.h"

class mSD_Class
{
private:
    /* data */
    bool Test=false;
    bool debugView = false;
public:

    /* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
    bool mSD_begin(uint8_t ssPin=SS, SPIClass &spi=SPI, uint32_t frequency=4000000, const char * mountpoint="/sd", uint8_t max_files=5, bool format_if_empty=false);
    uint8_t mSD_cardType();
    void mSD_listDirSerial(const char * dirname, uint8_t levels);
    uint16_t mSD_listFileCount(const char * dirname,const char* typeFile);
    void mSD_listFile(File  *root,const char * dirname,std::string *_pathFile);
    bool mSD_createDir(const char * path);
    bool mSD_removeDir(const char * path);
    bool mSD_writeFileString(const char * path, const char * message);
    bool mSD_appendFile(const char * path, const char * message);
    bool mSD_renameFile(const char * path1, const char * path2);
    bool mSD_deleteFile(const char * path);
    /*-------------------------------------------------------*/
    bool mSD_open(File  *file,const char * path,const char* mode);
    bool mSD_read(File  *file,uint8_t *buffer,uint32_t _size);
    bool mSD_seek(File *file,uint32_t pos,SeekMode _mode);
    void mSD_close(File  *file);
};

