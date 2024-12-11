#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

class Passenger {
public:
    std::string name;
    int age;

    Passenger(const std::string& name, int age) : name(name), age(age) {}
};

class Ticket {
public:
    int ticketId;
    Passenger passenger;

    Ticket(int id, const Passenger& p) : ticketId(id), passenger(p) {}
};

class Trip {
public:
    std::string destination;
    std::vector<Ticket> tickets;

    Trip(const std::string& dest) : destination(dest) {}

    void addTicket(const Ticket& ticket) {
        tickets.push_back(ticket);
    }

    void removeTicket(int ticketId) {
        tickets.erase(std::remove_if(tickets.begin(), tickets.end(),
            [ticketId](const Ticket& t) { return t.ticketId == ticketId; }), tickets.end());
    }

    void displayTickets() const {
        std::cout << std::setiosflags(std::ios::left)
            << std::setw(10) << "Ticket ID"
            << std::setw(20) << "Passenger Name"
            << std::setw(5) << "Age" << std::endl;

        for (const auto& ticket : tickets) {
            std::cout << std::setw(10) << ticket.ticketId
                << std::setw(20) << ticket.passenger.name
                << std::setw(5) << ticket.passenger.age << std::endl;
        }
    }
};

class Staff {
public:
    std::string name;
    std::string role;

    Staff(const std::string& name, const std::string& role) : name(name), role(role) {}
};

class Train {
public:
    std::string trainNumber;
    Trip trip;

    Train(const std::string& number, const Trip& t) : trainNumber(number), trip(t) {}

    void displayTrip() const {
        std::cout << "Train Number: " << trainNumber << ", Destination: " << trip.destination << std::endl;
        trip.displayTickets();
    }
};

int main() {
   
    Trip trip("Moscow");
    trip.addTicket(Ticket(1, Passenger("Ivan Ivanov", 30)));
    trip.addTicket(Ticket(2, Passenger("Maria Petrovna", 25)));

    Train train("123A", trip);
    train.displayTrip();

    // Удаление билета
    trip.removeTicket(1);
    std::cout << "\nAfter removing ticket 1:\n";
    train.displayTrip();

    // Проверка состояния потока
    std::cout << std::endl << "Stream state: " << std::endl;
    if (std::cin.eof()) {
        std::cout << "End of file reached." << std::endl;
    }
    else if (std::cin.fail()) {
        std::cout << "Input operation failed." << std::endl;
    }
    else if (std::cin.good()) {
        std::cout << "Stream is good." << std::endl;
    }
    else if (std::cin.bad()) {
        std::cout << "Stream is bad." << std::endl;
    }

    return 0;
}