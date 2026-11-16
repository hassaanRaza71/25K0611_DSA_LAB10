#include <iostream>
#include <cmath>

using namespace std;

class TheaterBookingSystem {
private:
    int table_size;
    int occupied_seats;
    int* seats;

    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

public:
    TheaterBookingSystem(int size) : occupied_seats(0) {
        if (!isPrime(size)) {
            cout << "Warning: " << size << " is not prime. Adjusting to next prime: ";
            while (!isPrime(size)) size++;
            cout << size << endl;
        }
        table_size = size;
        seats = new int[table_size];
        for (int i = 0; i < table_size; i++) {
            seats[i] = -1;
        }
    }

    ~TheaterBookingSystem() {
        delete[] seats;
    }

    double getLoadFactor() {
        return static_cast<double>(occupied_seats) / table_size;
    }

    bool bookSeat(int bookingID) {
        if (getLoadFactor() > 0.5) {
            cout << "[ALERT] Load Factor (" << getLoadFactor()
                 << ") exceeds 0.5! Booking blocked. Rehash required." << endl;
            return false;
        }

        int initial_index = bookingID % table_size;

        for (int j = 0; j < table_size; j++) {
            int current = (initial_index + j * j) % table_size;

            if (seats[current] == -1) {
                seats[current] = bookingID;
                occupied_seats++;
                cout << "Booking " << bookingID << " assigned to Seat " << current
                     << " (Load Factor: " << getLoadFactor() << ")" << endl;
                return true;
            }
        }
        cout << "Failed to find a seat for Booking " << bookingID << endl;
        return false;
    }
};

int main() {
    TheaterBookingSystem theater(7);
    theater.bookSeat(101);
    theater.bookSeat(108);
    theater.bookSeat(115);
    theater.bookSeat(200);
    theater.bookSeat(300);
    return 0;
}
