#include "Arduino_UnifiedStorage.h"

SDStorage storage;

const char testCaseID[] = "AUS_SPSD_CRRLFS_002";

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

  storage = SDStorage();
  storage.format(FS_LITTLEFS);
  if (!storage.begin())
  {
    Serial.println("Error mounting storage device.");
  }

  // Create empty file and set to WRITE mode
  Serial.println("Creating Files...");
  Folder root = storage.getRootFolder();
  Folder subdir = root.createSubfolder("subdir");

  UFile file1 = subdir.createFile("file1.txt", FileMode::WRITE);
  UFile file2 = subdir.createFile("file2.txt", FileMode::WRITE);
  UFile file3 = subdir.createFile("file3.txt", FileMode::WRITE);
  UFile file4 = subdir.createFile("file4.txt", FileMode::WRITE);
  UFile file5 = subdir.createFile("file5.txt", FileMode::WRITE);

  Serial.println("Changing FileMode...");
  file1.changeMode(FileMode::READ);
  file2.changeMode(FileMode::READ);
  file3.changeMode(FileMode::READ);
  file4.changeMode(FileMode::READ);
  file5.changeMode(FileMode::READ);

  Serial.println("Files found...");
  std::vector<UFile> filesBefore = subdir.getFiles();
  // Print files
  for (UFile file : filesBefore)
  {
    Serial.print("[F] ");
    Serial.println(file.getPath());
  }

  Serial.println("Deleting Files...");
  file1.remove();
  file2.remove();
  file3.remove();
  file4.remove();
  file5.remove();

  Serial.println("Files found...");
  std::vector<UFile> files = subdir.getFiles();
  // Print files
  for (UFile file : files)
  {
    Serial.print("[F] ");
    Serial.println(file.getPath());
  }
}

void loop()
{
}