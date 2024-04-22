#include "Arduino_UnifiedStorage.h"
#include "CRC.h" // https://github.com/RobTillaart/CRC

USBStorage storage;
CRC8 crc;

const char testCaseID[] = "AUS_SPUSB_FNBLFS_010";

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("---");
  Serial.print("Test Case ID: ");
  Serial.println(testCaseID);
  Serial.println("---");

  Arduino_UnifiedStorage::debuggingModeEnabled = false;
  if (Arduino_UnifiedStorage::debuggingModeEnabled)
  {
    Serial.println("Arduino_UnifiedStorage debug messages ON.");
  }

  storage = USBStorage();
  storage.format(FS_LITTLEFS);
  if (!storage.begin())
  {
    Serial.println("Error mounting storage device.");
  }

  // specify Test strings & CRC
  const char testContent[] = "Hello World!";
  for (int i = 0; i < strlen(testContent); i++)
  {
    crc.add(testContent[i]);
  }
  uint8_t testContentCRC8 = crc.calc();
  crc.reset();
  Serial.println("testContent value:" + String(testContent) + ". With CRC value:" + String(testContentCRC8));

  const char testFilename[] = "256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256chars256c.txt";
  for (int i = 0; i < strlen(testFilename); i++)
  {
    crc.add(testFilename[i]);
  }
  uint8_t testFilenameCRC8 = crc.calc();
  crc.reset();
  Serial.println("testFilename value:" + String(testFilename) + ". With CRC value:" + String(testFilenameCRC8));

  // Create empty file and set to WRITE mode
  Folder root = storage.getRootFolder();
  UFile file1 = root.createFile(testFilename, FileMode::WRITE);

  file1.write(testContent);
  file1.changeMode(FileMode::READ);

  file1.seek(0);
  String dataRead = "";
  while (file1.available())
  {
    char data = file1.read();
    crc.add(data);
    dataRead += data;
  }
  Serial.println();

  uint8_t dataReadCRC = crc.calc();

  Serial.println("Files found:");
  std::vector<UFile> files = root.getFiles();
  // Print files
  for (UFile file : files)
  {
    Serial.print("[F] ");
    Serial.println(file.getPath());
  }

  Serial.println("Data read was " + dataRead + " with CRC value " + String(dataReadCRC));
}

void loop()
{
}