#include "Arduino_UnifiedStorage.h"
#include <vector>

SDStorage storage;

const char testCaseID[] = "AUS_SPSD_FORMAT_004";

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println(testCaseID);
    Serial.println("---");

    Arduino_UnifiedStorage::debuggingModeEnabled = true;
    if (Arduino_UnifiedStorage::debuggingModeEnabled)
    {
        Serial.println("Arduino_UnifiedStorage debug messages ON.");
    }

    Serial.println("Before format:");

    // list all partitions
    std::vector<Partition> partitionsBefore = SDStorage::readPartitions();
    for (int i = 0; i < partitionsBefore.size(); i++)
    {
        Serial.println("Partition: " + String(i + 1));
        Serial.println("Size: " + String(partitionsBefore[i].size));
        Serial.println("Type: " + prettyPrintFileSystemType(partitionsBefore[i].fileSystemType));
        Serial.println();
    }

    storage.format(FS_FAT);

    Serial.println("After format:");

    // list all partitions
    std::vector<Partition> partitions = SDStorage::readPartitions();
    for (int i = 0; i < partitions.size(); i++)
    {
        Serial.println("Partition: " + String(i + 1));
        Serial.println("Size: " + String(partitions[i].size));
        Serial.println("Type: " + prettyPrintFileSystemType(partitions[i].fileSystemType));
        Serial.println();
    }
}

void loop()
{
}