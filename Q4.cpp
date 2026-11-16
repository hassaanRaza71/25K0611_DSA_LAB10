#include <iostream>

using namespace std;

class BankVaultSystem {
private:
    int table_size;
    int prime;
    int* vaults;

    int hash1(int key) {
        return key % table_size;
    }

    int hash2(int key) {
        return prime - (key % prime);
    }

public:
    BankVaultSystem(int size, int p) : table_size(size), prime(p) {
        vaults = new int[table_size];
        for (int i = 0; i < table_size; i++) {
            vaults[i] = -1;
        }
    }

    ~BankVaultSystem() {
        delete[] vaults;
    }

    bool assignVault(int vaultCode) {
        int h1 = hash1(vaultCode);
        int h2 = hash2(vaultCode);

        for (int j = 0; j < table_size; j++) {
            int current = (h1 + j * h2) % table_size;

            if (vaults[current] == -1) {
                vaults[current] = vaultCode;
                cout << "Vault Code " << vaultCode << " stored at Vault #" << current
                     << " (Jumps: " << j << ")" << endl;
                return true;
            }
        }

        cout << "[ERROR] Infinite loop / cycle detected for Vault Code " << vaultCode
             << ". Step size (" << h2 << ") and table size (" << table_size
             << ") are not co-prime or table is full." << endl;
        return false;
    }

    int searchVault(int vaultCode) {
        int h1 = hash1(vaultCode);
        int h2 = hash2(vaultCode);

        for (int j = 0; j < table_size; j++) {
            int current = (h1 + j * h2) % table_size;

            if (vaults[current] == -1) {
                return -1;
            }
            if (vaults[current] == vaultCode) {
                return current;
            }
        }
        return -1;
    }
};

int main() {
    BankVaultSystem bank(10, 7);

    bank.assignVault(20);
    bank.assignVault(30);
    bank.assignVault(40);
    bank.assignVault(50);
    bank.assignVault(70);
    bank.assignVault(10);

    return 0;
}
