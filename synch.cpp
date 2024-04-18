/*  
    Synchronize two folders periodically
    Match source folder content -> replica folder content

    Log operations to a log file and to the console output
        Operations: File create, copy and remove

    Possibility to specify paths of the folders and log file via command
    line arguments, to customize the synchronization process
*/

#include <iostream>
#include <filesystem>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>

using namespace std;
using namespace std::filesystem;

// Folders syncronization 
void syncFolders(const path& sourcePath, const path& replicaPath) {
    // Iterate through the source directory
    for (auto const& dir_entry : directory_iterator(sourcePath)) {
        cout << "source: " << dir_entry.path() << endl;
        cout << "replica: " << replicaPath << endl;
        // Replicate source content paths to replica
        auto const& source = dir_entry.path();
        auto const& replica = replicaPath / source.filename();
        
        if (is_regular_file(source)) {
            if(exists(replica) && last_write_time(replica) == last_write_time(source)) {
                continue; // synchronized
            } else {
                if (exists(replica)) {
                    // remove
                }
                else {
                    // copy
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {

    // Confirm the number of recieved arguments
    if (argc != 5) {
        cerr << "Too few arguments in function call" << endl;
        return 1;
    }

    // Get folder paths, synchronization interval and log file path from the command line 
    const path sourcePath = argv[1];
    const path replicaPath = argv[2];
    const path logPath = argv[3];

    // Verify argument validity as a time input
    const string syncInterval = argv[4];
    try {

        // Convert an argument (sring) into an int value
        const int secInterval = stoi(syncInterval);

        // Handle negative time value
        if (secInterval <= 0) {
            cerr << "Synchronization time should be a positive value" << endl;
            return 1;
        }

        // Class template that represents a time interval
        const  chrono::seconds interval(secInterval);

        // Check if the specified directories exist
        if (!exists(sourcePath)) {
            cerr << "Directory not found: " << argv[1] << endl;
            return 1;
        }
        if (!exists(replicaPath)) {
            // create a new folder and copy source folder contents
            return 0;
        }

        while (true) {
            // syncFolders(sourcePath, replicaPath, syncInterval, logPath)
            // Block execution of a thread for the specified time
            this_thread::sleep_for(interval);
        }
    } catch (const invalid_argument& err) {
        cerr << "The value provided is not valid" << endl;
        return 1;
    } catch (const out_of_range& err) {
        cerr << "The value provided is out of range" << std::endl;
        return 1;
    }

    return 0;

    // argv: source folder, replica folder, synch interval, log file path8
    // Create()
    // Copy()
    // Remove()
    // Log()
}
