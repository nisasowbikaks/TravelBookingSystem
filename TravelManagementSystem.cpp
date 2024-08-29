#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>

using namespace std;

struct User {
    int userId;
    string name;
};

struct Bus {
    int busId;
    string route;
    string date;
    int availableSeats;
    double ticketCost;
};

struct Booking {
    int bookingId;
    int userId;
    int busId;
    int tickets;
    string date;
    bool operator<(const Booking& other) const {
        return date > other.date;
    }
};

class BusTicketBookingSystem {
private:
    map<int, User> users;
    map<int, Bus> buses;
    priority_queue<Booking> bookings;
    int bookingCounter = 0;

public:
    BusTicketBookingSystem() {
        addBus(1, "Route A", "2024-07-01", 50, 15.0);
        addBus(2, "Route B", "2024-07-01", 40, 20.0);
        addBus(3, "Route C", "2024-07-01", 30, 25.0);
        addBus(4, "Route D", "2024-07-02", 60, 18.0);
        addBus(5, "Route E", "2024-07-02", 45, 22.0);
    }

    void addUser(int userId, const string& name) {
        users[userId] = {userId, name};
    }

    void addBus(int busId, const string& route, const string& date, int availableSeats, double ticketCost) {
        buses[busId] = {busId, route, date, availableSeats, ticketCost};
    }

    void bookTicket(int userId, int busId, int tickets, const string& date) {
        if (users.find(userId) == users.end()) {
            cerr << "User not found!" << endl;
            return;
        }
        if (buses.find(busId) == buses.end()) {
            cerr << "Bus not found!" << endl;
            return;
        }

        if (buses[busId].availableSeats < tickets) {
            cerr << "No available seats on this bus!" << endl;
            return;
        }

        Booking newBooking = {bookingCounter++, userId, busId, tickets, date};
        bookings.push(newBooking);
        buses[busId].availableSeats -= tickets;
        cout << "Booking successful for user " << userId << " on bus " << busId << endl;
        cout << "Bus ID: " << busId << ", Route: " << buses[busId].route
             << ", Date: " << buses[busId].date << ", Available Seats: " << buses[busId].availableSeats
             << ", Ticket Cost: $" << buses[busId].ticketCost << endl;
    }

    void processBookings() {
        while (!bookings.empty()) {
            Booking b = bookings.top();
            bookings.pop();
            cout << "Processing booking " << b.bookingId << " for user " << b.userId
                 << " on bus " << b.busId << ", Tickets: " << b.tickets << endl;
        }
    }

    void displayUsers() {
        for (const auto& user : users) {
            cout << "User ID: " << user.first << ", Name: " << user.second.name << endl;
        }
    }

    void displayBuses() {
        for (const auto& bus : buses) {
            cout << "Bus ID: " << bus.first << ", Route: " << bus.second.route
                 << ", Date: " << bus.second.date << ", Available Seats: " << bus.second.availableSeats
                 << ", Ticket Cost: $" << bus.second.ticketCost << endl;
        }
    }
};

int main() {
    BusTicketBookingSystem system;
    int choice;

    while (true) {
        cout << "\nBus Ticket Booking System\n";
        cout << "1. Add User\n";
        cout << "2. Display Bus Details\n";
        cout << "3. Book Ticket\n";
        cout << "4. Process Bookings\n";
        cout << "5. Display Users\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int userId;
            string name;
            cout << "Enter User ID: ";
            cin >> userId;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            system.addUser(userId, name);

        } else if (choice == 2) {
            system.displayBuses();

        } else if (choice == 3) {
            int userId, busId, tickets;
            string date;
            cout << "Enter User ID: ";
            cin >> userId;
            cout << "Enter Bus ID: ";
            cin >> busId;
            cout << "Enter Number of Tickets: ";
            cin >> tickets;
            cin.ignore();
            cout << "Enter Booking Date (YYYY-MM-DD): ";
            getline(cin, date);
            system.bookTicket(userId, busId, tickets, date);

        } else if (choice == 4) {
            system.processBookings();

        } else if (choice == 5) {
            system.displayUsers();

        } else if (choice == 6) {
            break;

        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
