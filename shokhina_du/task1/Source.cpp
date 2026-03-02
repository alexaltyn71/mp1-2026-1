#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class LengthConverter {
private:
    double meters;
    // структура для хранения информации о единице измерения
    struct UnitInfo {
        string name;
        string abbreviation;
        double coefficient;  // коэффициент для перевода из метров в данную единицу
    };

    // массив всех доступных единиц измерения
    vector<UnitInfo> units;

    // константы для перевода из метров в другие единицы
    static constexpr double METERS_TO_INCH = 39.3701;               // 1 дюйм = 0.0254 м
    static constexpr double METERS_TO_FOOT = 3.28084;               // 1 фут = 0.3048 м
    static constexpr double METERS_TO_YARD = 1.09361;               // 1 ярд = 0.9144 м
    static constexpr double METERS_TO_MILE = 0.000621371;           // 1 миля = 1609.344 м
    static constexpr double METERS_TO_NAUTICAL_MILE = 0.000539957;  // 1 морская миля = 1852 м
    static constexpr double METERS_TO_LEAGUE = 0.000207125;         // 1 лига = 4828 м
    static constexpr double METERS_TO_VERSTA = 0.000937383;         // 1 верста = 1066.8 м
    static constexpr double METERS_TO_SAGENE = 0.468691;            // 1 сажень = 2.1336 м
    static constexpr double METERS_TO_ARSHIN = 1.40607;             // 1 аршин = 0.7112 м
    static constexpr double METERS_TO_AU = 6.68459e-12;             // 1 а.е. = 149597870700 м

public:
    LengthConverter() : meters(0.0) {
        initializeUnits();
    }

    // единицы измерения
    void initializeUnits() {
        units = {
            {"Метры", "m", 1.0},
            {"Дюймы", "in", METERS_TO_INCH},
            {"Футы", "ft", METERS_TO_FOOT},
            {"Ярды", "yd", METERS_TO_YARD},
            {"Мили", "mi", METERS_TO_MILE},
            {"Морские мили", "nmi", METERS_TO_NAUTICAL_MILE},
            {"Лиги", "lea", METERS_TO_LEAGUE},
            {"Версты", "verst", METERS_TO_VERSTA},
            {"Сажени", "sag", METERS_TO_SAGENE},
            {"Аршины", "arsh", METERS_TO_ARSHIN},
            {"Астрономические единицы", "AU", METERS_TO_AU}
        };
    }

    // установка длины (в метрах)
    void setLengthInMeters() {
        cout << "Введите длину в метрах: ";
        cin >> meters;
        if (meters < 0) {
            cout << "Длина не может быть отрицательной. Установлено значение 0.\n";
            meters = 0;
        }
        cout << "------------------------------------------\n";
    }

    // перевод в другие единицы измерения
    void setLengthInSelectedUnit() {
        displayUnitSelection();
        int choice;
        cout << "Выберите единицу измерения (1-" << units.size() << "): ";
        cin >> choice;

        if (choice >= 1 && choice <= static_cast<int>(units.size())) {
            double value;
            cout << "Введите длину в " << units[choice - 1].name << ": ";
            cin >> value;

            if (value < 0) {
                cout << "Длина не может быть отрицательной. Операция отменена.\n";
            }
            else {
                meters = value / units[choice - 1].coefficient;
                cout << "Длина установлена: " << value << " " << units[choice - 1].abbreviation
                    << " = " << meters << " м\n";
            }
        }
        else {
            cout << "Неверный выбор.\n";
        }
        cout << "------------------------------------------\n";
    }

    void displayInMeters() const {
        cout << fixed << setprecision(3);
        cout << "Текущая длина: " << meters << " метров\n";
        cout << "------------------------------------------\n";
    }

    void displayInSelectedUnit() const {
        displayUnitSelection();

        int choice;
        cout << "Выберите единицу измерения для вывода (1-" << units.size() << "): ";
        cin >> choice;

        if (choice >= 1 && choice <= static_cast<int>(units.size())) {
            double convertedValue = meters * units[choice - 1].coefficient;
            cout << fixed << setprecision(6);
            cout << meters << " м = " << convertedValue << " " << units[choice - 1].abbreviation
                << " (" << units[choice - 1].name << ")\n";
        }
        else {
            cout << "Неверный выбор.\n";
        }
        cout << "------------------------------------------\n";
    }

    void displayUnitSelection() const {
        cout << "\n====== ДОСТУПНЫЕ ЕДИНИЦЫ ИЗМЕРЕНИЯ ======\n";
        for (size_t i = 0; i < units.size(); ++i) {
            cout << i + 1 << ". " << units[i].name << " (" << units[i].abbreviation << ")\n";
        }
        cout << "------------------------------------------\n";
    }

    // отображение длины во всех единицах
    void displayInAllUnits() const {
        cout << fixed << setprecision(6);
        cout << "\n=== ДЛИНА В РАЗЛИЧНЫХ ЕДИНИЦАХ ИЗМЕРЕНИЯ ===\n";
        cout << "Метры: " << meters << " м\n";
        for (size_t i = 1; i < units.size(); ++i) {
            double convertedValue = meters * units[i].coefficient;
            cout << units[i].name << ": " << convertedValue << " " << units[i].abbreviation << "\n";
        }
        cout << "------------------------------------------\n";
    }

    // меню
    void displayMenu() const {
        cout << "\n========== МЕНЮ КОНВЕРТЕРА ДЛИН ==========\n";
        cout << "1. Установить новую длину в метрах\n";
        cout << "2. Установить новую длину в другой единице\n";
        cout << "3. Вывести текущую длину в метрах\n";
        cout << "4. Вывести текущую длину в конкретной единице\n";
        cout << "5. Вывести текущую длину во всех единицах\n";
        cout << "6. Выход из программы\n";
        cout << "Выберите действие (1-6): ";
    }

    // запуск
    void run() {
        int choice;
        cout << "======= ПРОГРАММА КОНВЕРТАЦИИ ДЛИН =======\n";
        cout << "Сначала введите начальную длину. ";
        setLengthInMeters();

        do {
            displayMenu();
            cin >> choice;

            switch (choice) {
            case 1:
                setLengthInMeters();
                break;
            case 2:
                setLengthInSelectedUnit();
                break;
            case 3:
                displayInMeters();
                break;
            case 4:
                displayInSelectedUnit();
                break;
            case 5:
                displayInAllUnits();
                break;
            case 6:
                break;
            default:
                cout << "Неверный выбор. Пожалуйста, выберите 1-6.\n";
            }
        } while (choice != 6);
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    LengthConverter converter;
    converter.run();

    return 0;
}
