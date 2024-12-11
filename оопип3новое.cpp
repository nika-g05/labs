#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <fstream>
#include <string>
#include <algorithm>
#include<windows.h>

class MedicalWorker {
public:
    std::string name;
    int hoursWorked;

    MedicalWorker(const std::string& name, int hours) : name(name), hoursWorked(hours) {}

    void display() const {
        std::cout << "Имя: " << name << ", Отработанные часы: " << hoursWorked << std::endl;
    }
};

class Container {
public:
    virtual void add(const MedicalWorker& worker) = 0;
    virtual void remove(const std::string& name) = 0;
    virtual void edit(const std::string& name, int newHours) = 0;
    virtual void display() const = 0;
    virtual void saveToFile(const std::string& filename) const = 0;
    virtual void search(const std::string& name) const = 0;
    virtual void sort() = 0;
};

class VectorContainer : public Container {
private:
    std::vector<MedicalWorker> workers;

public:
    void add(const MedicalWorker& worker) override {
        workers.push_back(worker);
    }

    void remove(const std::string& name) override {
        workers.erase(std::remove_if(workers.begin(), workers.end(),
            [&name](const MedicalWorker& w) { return w.name == name; }),
            workers.end());
    }

    void edit(const std::string& name, int newHours) override {
        for (auto& worker : workers) {
            if (worker.name == name) {
                worker.hoursWorked = newHours;
                break;
            }
        }
    }

    void display() const override {
        for (const auto& worker : workers) {
            worker.display();
        }
    }

    void saveToFile(const std::string& filename) const override {
        std::ofstream file(filename);
        for (const auto& worker : workers) {
            file << worker.name << "," << worker.hoursWorked << std::endl;
        }
    }

    void search(const std::string& name) const override {
        for (const auto& worker : workers) {
            if (worker.name == name) {
                worker.display();
                return;
            }
        }
        std::cout << "Работник не найден." << std::endl;
    }

    void sort() override {
        std::sort(workers.begin(), workers.end(), [](const MedicalWorker& a, const MedicalWorker& b) {
            return a.name < b.name;
            });
    }
};

class ListContainer : public Container {
private:
    std::list<MedicalWorker> workers;

public:
    void add(const MedicalWorker& worker) override {
        workers.push_back(worker);
    }

    void remove(const std::string& name) override {
        workers.remove_if([&name](const MedicalWorker& w) { return w.name == name; });
    }

    void edit(const std::string& name, int newHours) override {
        for (auto& worker : workers) {
            if (worker.name == name) {
                worker.hoursWorked = newHours;
                break;
            }
        }
    }

    void display() const override {
        for (const auto& worker : workers) {
            worker.display();
        }
    }

    void saveToFile(const std::string& filename) const override {
        std::ofstream file(filename);
        for (const auto& worker : workers) {
            file << worker.name << "," << worker.hoursWorked << std::endl;
        }
    }

    void search(const std::string& name) const override {
        for (const auto& worker : workers) {
            if (worker.name == name) {
                worker.display();
                return;
            }
        }
        std::cout << "Работник не найден." << std::endl;
    }

    void sort() override {
        workers.sort([](const MedicalWorker& a, const MedicalWorker& b) {
            return a.name < b.name;
            });
    }
};

class ArrayContainer : public Container {
private:
    std::array<MedicalWorker, 100> workers;
    size_t size = 0;

public:
    void add(const MedicalWorker& worker) override {
        if (size < workers.size()) {
            workers[size++] = worker;
        }
        else {
            std::cout << "Массив переполнен." << std::endl;
        }
    }

    void remove(const std::string& name) override {
        for (size_t i = 0; i < size; ++i) {
            if (workers[i].name == name) {
                workers[i] = workers[--size]; 
                return;
            }
        }
    }

    void edit(const std::string& name, int newHours) override {
        for (size_t i = 0; i < size; ++i) {
            if (workers[i].name == name) {
                workers[i].hoursWorked = newHours;
                break;
            }
        }
    }

    void display() const override {
        for (size_t i = 0; i < size; ++i) {
            workers[i].display();
        }
    }

    void saveToFile(const std::string& filename) const override {
        std::ofstream file(filename);
        for (size_t i = 0; i < size; ++i) {
            file << workers[i].name << "," << workers[i].hoursWorked << std::endl;
        }
    }

    void search(const std::string& name) const override {
        for (size_t i = 0; i < size; ++i) {
            if (workers[i].name == name) {
                workers[i].display();
                return;
            }
        }
        std::cout << "Работник не найден." << std::endl;
    }

    void sort() override {
        std::sort(workers.begin(), workers.begin() + size, [](const MedicalWorker& a, const MedicalWorker& b) {
            return a.name < b.name;
            });
    }
};

void displayMenu() {
    std::cout << "1. Добавить работника\n";
    std::cout << "2. Удалить работника\n";
    std::cout << "3. Редактировать работника\n";
    std::cout << "4. Показать всех работников\n";
    std::cout << "5. Сохранить в файл\n";
    std::cout << "6. Найти работника\n";
    std::cout << "7. Отсортировать работников\n";
    std::cout << "0. Выход\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    VectorContainer workers;
    int choice;
    std::string name;
    int hours;

    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Введите имя и отработанные часы: ";
            std::cin >> name >> hours;
            workers.add(MedicalWorker(name, hours));
            break;
        case 2:
            std::cout << "Введите имя для удаления: ";
            std::cin >> name;
            workers.remove(name);
            break;
        case 3:
            std::cout << "Введите имя и новые часы: ";
            std::cin >> name >> hours;
            workers.edit(name, hours);
            break;
        case 4:
            workers.display();
            break;
        case 5:
            workers.saveToFile("workers.txt");
            break;
        case 6:
            std::cout << "Введите имя для поиска: ";
            std::cin >> name;
            workers.search(name);
            break;
        case 7:
            workers.sort();
            std::cout << "Работники отсортированы по имени." << std::endl;
            break;
        case 0:
            return 0;
        default:
            std::cout << "Неверный выбор." << std::endl;
        }
    }

    return 0;
}