#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <algorithm>
#include<windows.h>

class MedicalWorker {
public:
    std::string name;
    int hoursWorked;

    MedicalWorker() : name(""), hoursWorked(0) {}

    MedicalWorker(const std::string& name, int hours) : name(name), hoursWorked(hours) {}

    void display() const {
        std::cout << "Имя: " << name << ", Отработанные часы: " << hoursWorked << std::endl;
    }
};

class WorkerManager {
private:
    std::map<std::string, MedicalWorker> workerMap;
    std::multimap<std::string, MedicalWorker> workerMultiMap;
    std::unordered_map<std::string, MedicalWorker> workerUnorderedMap;
    std::set<std::string> workerSet;
    std::unordered_set<std::string> workerUnorderedSet;

public:
    void addWorker(const MedicalWorker& worker) {
        workerMap[worker.name] = worker;
        workerMultiMap.insert({ worker.name, worker });
        workerUnorderedMap[worker.name] = worker;
        workerSet.insert(worker.name);
        workerUnorderedSet.insert(worker.name);
    }

    void removeWorker(const std::string& name) {
        workerMap.erase(name);
        workerMultiMap.erase(name);
        workerUnorderedMap.erase(name);
        workerSet.erase(name);
        workerUnorderedSet.erase(name);
    }

    void editWorker(const std::string& name, int newHours) {
        auto it = workerMap.find(name);
        if (it != workerMap.end()) {
            it->second.hoursWorked = newHours;
        }
    }

    void displayWorkers() const {
        std::cout << "Работники:" << std::endl;
        for (const auto& pair : workerMap) { // Используем 'pair' для итерации
            const auto& worker = pair.second; // Получаем 'worker' из 'pair'
            worker.display();
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        for (const auto& pair : workerMap) { // Используем 'pair' для итерации
            const auto& worker = pair.second; // Получаем 'worker' из 'pair'
            file << worker.name << "," << worker.hoursWorked << std::endl;
        }
    }

    void searchWorker(const std::string& name) const {
        auto it = workerMap.find(name);
        if (it != workerMap.end()) {
            it->second.display();
        }
        else {
            std::cout << "Работник не найден." << std::endl;
        }
    }

    void filterWorkers(int minHours) const {
        std::cout << "Работники с отработанными часами более " << minHours << ":" << std::endl;
        for (const auto& pair : workerMap) { // Используем 'pair' для итерации
            const auto& worker = pair.second; // Получаем 'worker' из 'pair'
            if (worker.hoursWorked > minHours) {
                worker.display();
            }
        }
    }
};

void displayMenu() {
    std::cout << "1. Добавить работника\n";
    std::cout << "2. Удалить работника\n";
    std::cout << "3. Редактировать работника\n";
    std::cout << "4. Показать всех работников\n";
    std::cout << "5. Сохранить в файл\n";
    std::cout << "6. Найти работника\n";
    std::cout << "7. Фильтровать работников по часам\n";
    std::cout << "0. Выход\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    WorkerManager manager;
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
            manager.addWorker(MedicalWorker(name, hours));
            break;
        case 2:
            std::cout << "Введите имя для удаления: ";
            std::cin >> name;
            manager.removeWorker(name);
            break;
        case 3:
            std::cout << "Введите имя и новые часы: ";
            std::cin >> name >> hours;
            manager.editWorker(name, hours);
            break;
        case 4:
            manager.displayWorkers();
            break;
        case 5:
            manager.saveToFile("workers.txt");
            break;
        case 6:
            std::cout << "Введите имя для поиска: ";
            std::cin >> name;
            manager.searchWorker(name);
            break;
        case 7:
            std::cout << "Введите минимальное количество часов: ";
            std::cin >> hours;
            manager.filterWorkers(hours);
            break;
        case 0:
            return 0;
        default:
            std::cout << "Неверный выбор." << std::endl;
        }
    }

    return 0;
}