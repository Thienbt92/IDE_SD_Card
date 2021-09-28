#include "t3c_sd.h"

bool mSD_Class::mSD_begin(uint8_t ssPin, SPIClass &spi, uint32_t frequency, const char * mountpoint, uint8_t max_files,bool format_if_empty)
{
  return SD.begin(ssPin,spi,frequency,mountpoint,max_files,format_if_empty);
}
/**
 * Đọc loại thẻ nhớ đang dùng
    CARD_NONE,
    CARD_MMC,
    CARD_SD,
    CARD_SDHC,
    CARD_UNKNOWN
 */ 
uint8_t  mSD_Class::mSD_cardType()
{
  return SD.cardType();
}
/**
 * Hiển Thị Danh Sách Folder Lên Serial
 * */
void mSD_Class::mSD_listDirSerial(const char * dirname, uint8_t levels)
{
  Serial.printf("Listing directory: %s\n", dirname);
  File root = SD.open(dirname);
  if(!root)
  {
    Serial.println("Failed to open directory");
    return;
  }
  if(!root.isDirectory())
  {
    Serial.println("Not a directory");
    return;
  }
  File file = root.openNextFile();
  while(file)
  {
    if(file.isDirectory())
    {
      Serial.print("  DIR : ");
      Serial.println(file.name());
    } 
    else 
    {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}
void mSD_Class::mSD_listFile(File  *root,const char * dirname,String *_pathFile)
{
  if(!*root) 
  {
    *root = SD.open(dirname);
  }
  if((root->isDirectory())==false)
    return;

  File file = root->openNextFile();
  while(file.isDirectory())
  {
    file = root->openNextFile();
  }
  *_pathFile = file.name();
}

bool mSD_Class::mSD_createDir(const char * path)
{
  if(debugView==true)
    Serial.printf("Creating Dir: %s\n", path);
  if(SD.mkdir(path))
  {
    if(debugView==true)
      Serial.println("Dir created");
    return true;
  } 
  else 
  {
    if(debugView==true)
      Serial.println("mkdir failed");
    return false;
  }
}

bool mSD_Class::mSD_removeDir(const char * path)
{
  if(debugView==true)
    Serial.printf("Removing Dir: %s\n", path);
  if(SD.rmdir(path))
  {
    if(debugView==true)
      Serial.println("Dir removed");
      return true;
  } 
  else 
  {
    if(debugView==true)
      Serial.println("rmdir failed");
    return false;
  }
}

bool mSD_Class::mSD_writeFileString(const char * path, const char * message)
{
  if(debugView==true)
    Serial.printf("Writing file: %s\n", path);

  File file = SD.open(path, FILE_WRITE);
  if(!file)
  {
    if(debugView==true)
      Serial.println("Failed to open file for writing");
    return false;
  }
  if(file.print(message))
  {
    if(debugView==true)
      Serial.println("File written"); 
  } 
  else 
  {
    if(debugView==true)
      Serial.println("Write failed");
  }
  file.close();
  return true;
}

bool mSD_Class::mSD_appendFile(const char * path, const char * message)
{
  if(debugView==true)
    Serial.printf("Appending to file: %s\n", path);
  File file = SD.open(path, FILE_APPEND);
  if(!file)
  {
    if(debugView==true)
      Serial.println("Failed to open file for appending");
    return false;
  }
  if(file.print(message))
  {
    if(debugView==true)
      Serial.println("Message appended");
  } 
  else 
  {
    if(debugView==true)
      Serial.println("Append failed");
  }
  file.close();
  return true;
}

bool mSD_Class::mSD_renameFile(const char * path1, const char * path2)
{
  if(debugView==true)
    Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (SD.rename(path1, path2)) 
  {
    if(debugView==true)
      Serial.println("File renamed");
    return true;
  } 
  else 
  {
    if(debugView==true)
      Serial.println("Rename failed");
    return false;
  }
}

bool mSD_Class::mSD_deleteFile(const char * path)
{
  if(debugView==true)
    Serial.printf("Deleting file: %s\n", path);
  if(SD.remove(path))
  {
    if(debugView==true)
      Serial.println("File deleted");
    return true;
  } 
  else 
  {
    if(debugView==true)
      Serial.println("Delete failed");
    return false;
  }
}
/************************************************************************/
bool mSD_Class::mSD_open(File  *file,const char * path,const char* mode)
{
  *file = SD.open(path,mode);
  if(*file)
    return true;
  return false;
}
bool mSD_Class::mSD_read(File  *file,uint8_t *buffer,uint32_t _size)
{
  file->read(buffer,_size);
  /*if(file->read(buffer,_size)==-1);
  {
    file->close();
    return false;
  }
  file->close();*/
  return true;
}
bool mSD_Class::mSD_seek(File *file,uint32_t pos,SeekMode _mode)
{
  return file->seek(pos,_mode);
}
void mSD_Class::mSD_close(File  *file)
{
  file->close();
}

