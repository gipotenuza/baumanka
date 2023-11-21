#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h> 

struct Product {
    std::string Name;
    double price;
    std::string kolvo;
};

void addProductToFile(const Product& product) {
    std::ofstream outFile1("output.txt", std::ios::app);
    std::ofstream outFile("products.txt", std::ios::app);
    std::ifstream inFile("products.txt");
    if (outFile.is_open()) {
        outFile << product.Name << ", " << product.price << ", " << product.kolvo << std::endl;
        outFile.close();
        std::cout << "Продукт успешно добавлен." << std::endl;
    }
    else {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
    }
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (outFile1.is_open()) {
                outFile1 << line << std::endl;
            }
        }

        if (outFile1.is_open()) {
            outFile1 << std::endl;
        }
        outFile1.close();
        inFile.close(); // Закрытие файла
    }

}

void searchProductByName(const std::string& name) {
    std::ofstream outFile1("output.txt", std::ios::app);
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) {
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            size_t pos = line.find(',');
            std::string Name = line.substr(0, pos);
            if (Name == name) {
                std::cout << "Найден продукт: " << line << std::endl;
                if (outFile1.is_open()) {
                    outFile1 << "Найден продукт: " << line << std::endl << std::endl;
                    outFile1.close();
                    found = true;
                    break;
                }
            }
        }
        inFile.close();
        if (!found) {
            std::cout << "Продукт с таким именем не найден." << std::endl << std::endl;
            if (outFile1.is_open()) {
                outFile1 << "Продукт с таким именем не найден." << std::endl << std::endl;
                outFile1.close();
            }
        }
    }
    else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl << std::endl;
        if (outFile1.is_open()) {
            outFile1 << "Не удалось открыть файл для чтения." << std::endl << std::endl;
            outFile1.close();
        }
    }
}

void outputBelowPrice(const double price) {
    std::ofstream outFile1("output.txt", std::ios::app);
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) {
        int count = 0;
        std::string line;
        while (std::getline(inFile, line)) {
            size_t pos = line.find_first_of(',');
            double price1 = std::stod(line.substr(pos + 1));
            if (price1 <= price) {
                std::cout << line << std::endl;
                if (outFile1.is_open()) {
                    outFile1 << line << std::endl;
                }
            }
        }
        if (outFile1.is_open()) {
            outFile1 << std::endl;
        }
        outFile1.close();
        inFile.close();
    }
    else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl << std::endl;
        if (outFile1.is_open()) {
            outFile1 << "Не удалось открыть файл для чтения." << std::endl << std::endl;
            outFile1.close();
        }
    }
}

void sortProductsByPrice() {
    std::ofstream outFile1("output.txt", std::ios::app);
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) {
        // Чтение данных и сортировка (пузырьковая сортировка)
        std::string lines[100]; // Предполагаем, что не более 100 продуктов
        int count = 0;
        std::string line;
        while (std::getline(inFile, line)) {
            lines[count] = line;
            count++;
        }
        inFile.close();
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                size_t pos1 = lines[j].find_first_of(',');
                size_t pos2 = lines[j + 1].find_first_of(',');
                double price1 = std::stod(lines[j].substr(pos1 + 1));
                double price2 = std::stod(lines[j + 1].substr(pos2 + 1));
                if (price1 < price2) {
                    std::swap(lines[j], lines[j + 1]);
                }
            }
        }
        // Запись отсортированных данных обратно в файл
        std::ofstream outFile("products.txt");

        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << lines[i] << std::endl;
            }
            outFile.close();
            std::cout << "Продукты отсортированы по цене.." << std::endl;
        }
        else {
            std::cerr << "Не удалось открыть файл для записи." << std::endl;
        }

        if (outFile1.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile1 << lines[i] << std::endl;
            }
            outFile1 << std::endl;
            outFile1.close();
        }
        else {
            outFile1 << "Не удалось открыть файл для записи." << std::endl << std::endl;
            outFile1.close();
        }
    }
    else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl << std::endl;
        if (outFile1.is_open()) {
            outFile1 << "Не удалось открыть файл для чтения." << std::endl << std::endl;
            outFile1.close();
        }
    }
}

void sortProductsByKolvo() {
    std::ifstream inFile("products.txt");
    std::ofstream outFile1("output.txt", std::ios::app);
    if (inFile.is_open()) {
        // Чтение данных и сортировка (пузырьковая сортировка)
        std::string lines[100]; // Предполагаем, что не более 100 продуктов
        int count = 0;
        std::string line;
        while (std::getline(inFile, line)) {
            lines[count] = line;
            count++;
        }
        inFile.close();
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                size_t pos1 = lines[j].find_last_of(', ');
                size_t pos2 = lines[j + 1].find_last_of(', ');
                int kolvo1 = std::stod(lines[j].substr(pos1 + 1));
                int kolvo2 = std::stod(lines[j + 1].substr(pos2 + 1));
                if (kolvo1 < kolvo2) {
                    std::swap(lines[j], lines[j + 1]);
                }
            }
        }
        // Запись отсортированных данных обратно в файл
        std::ofstream outFile("products.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << lines[i] << std::endl;
            }
            outFile.close();
            std::cout << "Продукты отсортированы по количеству." << std::endl;
        }
        else {
            std::cerr << "Не удалось открыть файл для записи." << std::endl;
        }

        if (outFile1.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile1 << lines[i] << std::endl;
            }
            outFile1 << std::endl;
            outFile1.close();
        }
        else {
            outFile1 << "Не удалось открыть файл для записи." << std::endl << std::endl;
            outFile1.close();
        }

    }
    else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl << std::endl;
        if (outFile1.is_open()) {
            outFile1 << "Продукты отсортированы по количеству." << std::endl << std::endl;
            outFile1.close();
        }
    }
}

void output() {
    std::ofstream outFile1("output.txt", std::ios::app);
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
            if (outFile1.is_open()) {
                outFile1 << line << std::endl;
            }
        }
        if (outFile1.is_open()) {
            outFile1 << std::endl;
        }
        outFile1.close();
        inFile.close(); // Закрытие файла
    }
}


int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    double pr;
    std::string name;

    do {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить продукт" << std::endl;
        std::cout << "2. Поиск продукта по названию" << std::endl;
        std::cout << "3. Сортировать продукты по цене" << std::endl;
        std::cout << "4. Сортировать продукты по количеству" << std::endl;
        std::cout << "5. Вывести информацию о продуктах" << std::endl;
        std::cout << "6. Вывести информацию о продуктах не более данной цены" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cin.ignore();
            std::string Name, kolvo;
            double price;
            std::cout << "Введите название продукта: ";
            std::getline(std::cin, Name);
            if (Name.empty()) {
                std::cout << "Ввод прерван." << std::endl;
                break;
            }
            std::cout << "Введите цену продукта: ";
            std::cin >> price;
            std::cin.ignore();
            std::cout << "Введите количество продукта: ";
            std::getline(std::cin, kolvo);
            Product newProduct = { Name, price, kolvo };
            addProductToFile(newProduct);
            break;
        }
        case 2: {
            std::cin.ignore();
            std::cout << "Введите название продукта для поиска: ";
            std::getline(std::cin, name);
            searchProductByName(name);
            break;
        }
        case 3: {
            sortProductsByPrice();
            break;
        }
        case 4: {
            sortProductsByKolvo();
            break;
        }
        case 5: {
            output();
            break;
        }
        case 6: {
            std::cin.ignore();
            std::cout << "Введите цену: ";
            std::cin >> pr;
            outputBelowPrice(pr);
            break;
        }
        case 0: {
            std::cout << "Программа завершена." << std::endl;
            break;
        }
        default: {
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            break;
        }
        }
    } while (choice != 0);

    return 0;
}