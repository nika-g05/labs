#include <iostream>
#include <queue>
#include <stack>
#include <vector>
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

    // Для приоритетной очереди
    bool operator<(const MedicalWorker& other) const {
        return hoursWorked < other.hoursWorked; // Сортировка по убыванию часов
    }
};

class WorkerManager {
private:
    std::queue<MedicalWorker> workerQueue; // Очередь
    std::stack<MedicalWorker> workerStack; // Стек
    std::priority_queue<MedicalWorker> workerPriorityQueue; // Приоритетная очередь

public:
    void addWorker(const MedicalWorker& worker) {
        workerQueue.push(worker);
        workerStack.push(worker);
        workerPriorityQueue.push(worker);
    }

    void removeWorkerFromQueue() {
        if (!workerQueue.empty()) {
            workerQueue.pop();
        }
        else {
            std::cout << "Очередь пуста." << std::endl;
        }
    }

    void removeWorkerFromStack() {
        if (!workerStack.empty()) {
            workerStack.pop();
        }
        else {
            std::cout << "Стек пуст." << std::endl;
        }
    }

    void displayWorkers() const {
        std::cout << "Работники в очереди:" << std::endl;
        std::queue<MedicalWorker> tempQueue = workerQueue; // Копируем очередь для отображения
        while (!tempQueue.empty()) {
            tempQueue.front().display();
            tempQueue.pop();
        }

        std::cout << "Работники в стеке:" << std::endl;
        std::stack<MedicalWorker> tempStack = workerStack; // Копируем стек для отображения
        while (!tempStack.empty()) {
            tempStack.top().display();
            tempStack.pop();
        }

        std::cout << "Работники в приоритетной очереди:" << std::endl;
        std::priority_queue<MedicalWorker> tempPriorityQueue = workerPriorityQueue; // Копируем приоритетную очередь для отображения
        while (!tempPriorityQueue.empty()) {
            tempPriorityQueue.top().display();
            tempPriorityQueue.pop();
        }
    }

    void searchWorker(const std::string& name) const {
        std::queue<MedicalWorker> tempQueue = workerQueue;
        bool found = false;

        while (!tempQueue.empty()) {
            if (tempQueue.front().name == name) {
                tempQueue.front().display();
                found = true;
                break;
            }
            tempQueue.pop();
        }

        if (!found) {
            std::cout << "Работник не найден в очереди." << std::endl;
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        std::queue<MedicalWorker> tempQueue = workerQueue;
        while (!tempQueue.empty()) {
            file << tempQueue.front().name << "," << tempQueue.front().hoursWorked << std::endl;
            tempQueue.pop();
        }
        file.close();
    }
};

void displayMenu() {
    std::cout << "1. Добавить работника\n";
    std::cout << "2. Удалить работника из очереди\n";
    std::cout << "3. Удалить работника из стека\n";
    std::cout << "4. Показать всех работников\n";
    std::cout << "5. Найти работника\n";
    std::cout << "6. Сохранить в файл\n";
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
            manager.removeWorkerFromQueue();
            break;
        case 3:
            manager.removeWorkerFromStack();
            break;
        case 4:
            manager.displayWorkers();
            break;
        case 5:
            std::cout << "Введите имя для поиска: ";
            std::cin >> name;
            manager.searchWorker(name);
            break;
        case 6:
            manager.saveToFile("workers.txt");
            std::cout << "Данные сохранены в файл workers.txt." << std::endl;
            break;
        case 0:
            return 0;
        default:
            std::cout << "Неверный выбор." << std::endl;
        }
    }

    return 0;
}