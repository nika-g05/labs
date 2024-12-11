#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include<windows.h>

// Абстрактный класс для всех типов работников
class Employee {
public:
    virtual void printDetails() const = 0;
    virtual ~Employee() = default;
};

// Класс для медицинского работника
class MedicalEmployee : public Employee {
public:
    std::string name;
    std::string specialty;

    MedicalEmployee(std::string name, std::string specialty)
        : name(name), specialty(specialty) {}

    void printDetails() const override {
        std::cout << "Фамилия: " << name << ", Должность: " << specialty << std::endl;
    }
};

// Класс для рабочего времени 
class Shift {
public:
    std::string shiftTime;
    int hoursWorked;

    Shift(std::string shiftTime, int hoursWorked)
        : shiftTime(shiftTime), hoursWorked(hoursWorked) {}

    void printDetails() const {
        std::cout << "График: " << shiftTime << ", Часы работы: " << hoursWorked << std::endl;
    }
};

// Класс для записи времени работы
class WorkRecord {
public:
    std::shared_ptr<Employee> employee;
    std::shared_ptr<Shift> shift;

    WorkRecord(std::shared_ptr<Employee> employee, std::shared_ptr<Shift> shift)
        : employee(employee), shift(shift) {}

    void printDetails() const {
        employee->printDetails();
        shift->printDetails();
    }
};

// Абстрактная фабрика для создания сотрудников
class EmployeeFactory {
public:
    virtual std::shared_ptr<Employee> createEmployee(std::string name, std::string specialty) = 0;
    virtual ~EmployeeFactory() = default;
};

// Фабрика для создания медицинских работников
class MedicalEmployeeFactory : public EmployeeFactory {
public:
    std::shared_ptr<Employee> createEmployee(std::string name, std::string specialty) override {
        return std::make_shared<MedicalEmployee>(name, specialty);
    }
};

// Абстрактная фабрика для создания смен
class ShiftFactory {
public:
    virtual std::shared_ptr<Shift> createShift(std::string shiftTime, int hoursWorked) = 0;
    virtual ~ShiftFactory() = default;
};

// Фабрика для создания смен
class StandardShiftFactory : public ShiftFactory {
public:
    std::shared_ptr<Shift> createShift(std::string shiftTime, int hoursWorked) override {
        return std::make_shared<Shift>(shiftTime, hoursWorked);
    }
};

// Класс для управления рабочими записями
class WorkTimeManager {
private:
    std::vector<std::shared_ptr<WorkRecord>> records;

public:
    void addRecord(std::shared_ptr<WorkRecord> record) {
        records.push_back(record);
    }

    void removeRecord(int index) {
        if (index >= 0 && index < records.size()) {
            records.erase(records.begin() + index);
        }
    }

    void editRecord(int index, std::shared_ptr<WorkRecord> newRecord) {
        if (index >= 0 && index < records.size()) {
            records[index] = newRecord;
        }
    }

    void displayRecords() const {
        for (const auto& record : records) {
            record->printDetails();
            std::cout << "----------------------------------" << std::endl;
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        for (const auto& record : records) {
            outFile << "Специалист: " << std::endl;
            outFile << "Фамилия: " << dynamic_cast<MedicalEmployee*>(record->employee.get())->name << ", ";
            outFile << "Должность: " << dynamic_cast<MedicalEmployee*>(record->employee.get())->specialty << std::endl;
            outFile << "График: " << std::endl;
            outFile << "Время: " << record->shift->shiftTime << ", ";
            outFile << "Часы: " << record->shift->hoursWorked << std::endl;
            outFile << "----------------------------------" << std::endl;
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // Создание фабрик
    MedicalEmployeeFactory employeeFactory;
    StandardShiftFactory shiftFactory;

    // Создание сотрудников и смен
    auto emp1 = employeeFactory.createEmployee("Кривошеин", "Хирург");
    auto shift1 = shiftFactory.createShift("9:00 - 17:00 ", 8);

    // Создание записи рабочего времени
    WorkTimeManager manager;
    auto record1 = std::make_shared<WorkRecord>(emp1, shift1);
    manager.addRecord(record1);

    // Добавление второго сотрудника и смены
    auto emp2 = employeeFactory.createEmployee("Ковальчук", "Медсестра");
    auto shift2 = shiftFactory.createShift("5:00 - 9:00 ", 4);
    auto record2 = std::make_shared<WorkRecord>(emp2, shift2);
    manager.addRecord(record2);

    // Вывод записей
    manager.displayRecords();

    // Сохранение в файл
    manager.saveToFile("work_records.txt");

    return 0;
}
