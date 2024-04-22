#include "Arduino_UnifiedStorage.h"
#include <vector>

// Create a vector of partitions with 6MB LittleFS + 6MB FAT partitions 
std::vector<Partition> partitioningScheme = {
    {6144, FS_LITTLEFS}, // 6 MB LittleFS Partition
    {6144, FS_FAT}, // 6 MB FAT Partition
};

const char testCaseID[] = "AUS_SPIS_FORMAT_003";

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("---");
    Serial.print("Test Case ID: ");
    Serial.println(testCaseID);
    Serial.println("---");

    Arduino_UnifiedStorage::debuggingModeEnabled = true;
    if (Arduino_UnifiedStorage::debuggingModeEnabled) {
        Serial.println("Arduino_UnifiedStorage debug messages ON.");
    }

    
    bool partitioned = InternalStorage::partition(partitioningScheme);

    // list all partitions
    std::vector<Partition> partitions = InternalStorage::readPartitions();
    for (int i = 0; i < partitions.size(); i++) {
        Serial.println("Partition: " + String(i + 1));
        Serial.println("Size: "      + String(partitions[i].size));
        Serial.println("Type: "      + prettyPrintFileSystemType(partitions[i].fileSystemType));
        Serial.println();
    }
}

void loop() {
}