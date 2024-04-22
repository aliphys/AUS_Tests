#include "Arduino_UnifiedStorage.h"
#include <vector>

// Create a vector of partitions with one partition of 16MB using LittleFS
std::vector<Partition> partitioningScheme = {
    {12288, FS_LITTLEFS}, // 12 MB LittleFS Partition
};

const char testCaseID[] = "AUS_SPIS_FORMAT_002";

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