#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


class Person {
protected:
    string name;
    int age;
public:
    Person() : name(""), age(0) {}
    Person(string n, int a) : name(n), age(a) {}

    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    friend ostream& operator<<(ostream& out, const Person& p) {
        out << p.name << " " << p.age;
        return out;
    }

    friend istream& operator>>(istream& in, Person& p) {
        in >> p.name >> p.age;
        return in;
    }
};


class Passenger : public Person {
private:
    string ticketNumber;
public:
    Passenger() : Person(), ticketNumber("") {}
    Passenger(string n, int a, string t) : Person(n, a), ticketNumber(t) {}

    void display() const override {
        cout << "Passenger: ";
        Person::display();
        cout << "Ticket Number: " << ticketNumber << endl;
    }

    friend ostream& operator<<(ostream& out, const Passenger& p) {
        out << static_cast<const Person&>(p) << " " << p.ticketNumber;
        return out;
    }

    friend istream& operator>>(istream& in, Passenger& p) {
        in >> static_cast<Person&>(p) >> p.ticketNumber;
        return in;
    }
};


class Staff : public Person {
private:
    string position;
public:
    Staff() : Person(), position("") {}
    Staff(string n, int a, string pos) : Person(n, a), position(pos) {}

    void display() const override {
        cout << "Staff: ";
        Person::display();
        cout << "Position: " << position << endl;
    }

    friend ostream& operator<<(ostream& out, const Staff& s) {
        out << static_cast<const Person&>(s) << " " << s.position;
        return out;
    }

    friend istream& operator>>(istream& in, Staff& s) {
        in >> static_cast<Person&>(s) >> s.position;
        return in;
    }
};


class TrainCar {
private:
    int number;
    vector<Passenger> passengers;
public:
    TrainCar() : number(0) {}
    TrainCar(int num) : number(num) {}

    void addPassenger(const Passenger& p) {
        passengers.push_back(p);
    }

    void display() const {
        cout << "Train Car Number: " << number << endl;
        for (const auto& passenger : passengers) {
            passenger.display();
        }
    }

    friend ostream& operator<<(ostream& out, const TrainCar& car) {
        out << car.number << endl;
        for (const auto& passenger : car.passengers) {
            out << passenger << endl;
        }
        return out;
    }

    friend istream& operator>>(istream& in, TrainCar& car) {
        in >> car.number;
        Passenger p;
        while (in >> p) {
            car.passengers.push_back(p);
        }
        return in;
    }
};

// класс, который агрегирует объекты класса Staff
//и компонуется с классом TrainCar
class Train {
private:
    string trainNumber;
    vector<Staff> staff;
    vector<TrainCar> cars;
public:
    Train() : trainNumber("") {}
    Train(string num) : trainNumber(num) {}

    void addStaff(const Staff& s) {
        staff.push_back(s);
    }

    void addCar(const TrainCar& car) {
        cars.push_back(car);
    }
    
    void display() const {
        cout << "Train Number: " << trainNumber << endl;
        cout << "Staff:" << endl;
        for (const auto& s : staff) {
            s.display();
        }
        cout << "Cars:" << endl;
        for (const auto& car : cars) {
            car.display();
        }
    }
    // выводить информацию о поезде в поток 
    friend ostream& operator<<(ostream& out, const Train& train) {
        out << train.trainNumber << endl;
        for (const auto& s : train.staff) {
            out << s << endl;
        }
        for (const auto& car : train.cars) {
            out << car << endl;
        }
        return out;
    }
    // читать информацию о поезде из потока
    friend istream& operator>>(istream& in, Train& train) {
        in >> train.trainNumber;
        Staff s;
        while (in >> s) {
            train.staff.push_back(s);
        }
        TrainCar car;
        while (in >> car) {
            train.cars.push_back(car);
        }
        return in;
    }
};

// Функции работы с файлами
void saveTrainToFile(const Train& train, const string& filename) {
    ofstream file(filename, ios::out);
    if (file.is_open()) {
        file << train;
        file.close();
    }
}
// Загрузка из файла
Train loadTrainFromFile(const string& filename) {
    ifstream file(filename, ios::in);
    Train train;
    if (file.is_open()) {
        file >> train;
        file.close();
    }
    return train;
}

int main() {
    
    Train train("Train 001");

    Staff conductor("Ivan Petrov", 45, "Conductor");
    Staff driver("Alexey Sidorov", 50, "Driver");

    train.addStaff(conductor);
    train.addStaff(driver);

    TrainCar car1(1);
    car1.addPassenger(Passenger("John Doe", 30, "T12345"));
    car1.addPassenger(Passenger("Jane Smith", 28, "T67890"));

    train.addCar(car1);

    saveTrainToFile(train, "train_data.txt");

    Train loadedTrain = loadTrainFromFile("train_data.txt");
    loadedTrain.display();

    return 0;
}

