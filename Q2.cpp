#include <iostream>

using namespace std;

enum SlotState { EMPTY, OCCUPIED, DELETED };

struct Locker {
    int packageID;
    SlotState state;
    Locker() : packageID(-1), state(EMPTY) {}
};

class WarehouseLockerSystem {
private:
    int table_size;
    Locker* lockers;

    int hashFunction(int id) {
        return id % table_size;
    }

public:
    WarehouseLockerSystem(int size) : table_size(size) {
        lockers = new Locker[table_size];
    }

    ~WarehouseLockerSystem() {
        delete[] lockers;
    }

    void assignLocker(int packageID) {
        int index = hashFunction(packageID);
        int probes = 0;

        for (int i = 0; i < table_size; i++) {
            int current = (index + i) % table_size;

            if (lockers[current].state == EMPTY || lockers[current].state == DELETED) {
                lockers[current].packageID = packageID;
                lockers[current].state = OCCUPIED;
                cout << "Package " << packageID << " assigned to Locker " << current
                     << " (Probes: " << probes << ")" << endl;
                return;
            }
            probes++;
        }
        cout << "Warehouse Full! Could not store Package " << packageID << endl;
    }

    int findPackage(int packageID) {
        int index = hashFunction(packageID);

        for (int i = 0; i < table_size; i++) {
            int current = (index + i) % table_size;

            if (lockers[current].state == EMPTY) {
                return -1;
            }
            if (lockers[current].state == OCCUPIED && lockers[current].packageID == packageID) {
                return current;
            }
        }
        return -1;
    }

    void pickupPackage(int packageID) {
        int lockerIndex = findPackage(packageID);
        if (lockerIndex != -1) {
            lockers[lockerIndex].state = DELETED;
            lockers[lockerIndex].packageID = -1;
            cout << "Package " << packageID << " picked up from Locker " << lockerIndex
                 << " (Marked DELETED)." << endl;
        } else {
            cout << "Package " << packageID << " not found." << endl;
        }
    }
};

int main() {
    WarehouseLockerSystem warehouse(7);
    warehouse.assignLocker(10);
    warehouse.assignLocker(17);
    warehouse.assignLocker(24);

    warehouse.pickupPackage(17);
    cout << "Searching for Package 24 after deletion of 17: Locker "
         << warehouse.findPackage(24) << endl;
    return 0;
}
