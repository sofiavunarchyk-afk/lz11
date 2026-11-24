#include <iostream>
#include <list>
#include <string>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

struct Book {
    string title;
    string author;
    int year;
    double price;
};

// кількість символів у UTF-8 рядку (для рівного вирівнювання кирилиці)
size_t utf8Len(const string& s) {
    size_t n = 0;
    for (unsigned char c : s)
        if ((c & 0xC0) != 0x80) ++n;
    return n;
}

string pad(const string& s, size_t w) {
    size_t l = utf8Len(s);
    return l >= w ? s : s + string(w - l, ' ');
}

void printBooks(const list<Book>& books) {
    cout << pad("Назва", 26) << pad("Автор", 24) << pad("Рік", 7) << "Ціна (грн)\n";
    cout << string(70, '-') << "\n";
    if (books.empty()) {
        cout << "(список порожній)\n";
        return;
    }
    for (const Book& b : books) {
        cout << pad(b.title, 26) << pad(b.author, 24)
             << pad(to_string(b.year), 7)
             << fixed << setprecision(2) << b.price << "\n";
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    list<Book> books = {
        {"Кобзар",                "Тарас Шевченко",        2019, 280.00},
        {"Тіні забутих предків",  "Михайло Коцюбинський",  2021, 120.00},
        {"Лісова пісня",          "Леся Українка",         2022, 145.50},
        {"Захар Беркут",          "Іван Франко",           2018,  95.00},
        {"Місто",                 "Валерьян Підмогильний", 2023, 210.00},
        {"Перехресні стежки",     "Іван Франко",           2021, 175.00}
    };

    cout << "1) Початковий список книг:\n";
    printBooks(books);

    // Додавання на початок і в кінець
    books.push_front({"Чистий код", "Роберт Мартін", 2022, 890.00});
    books.push_back({"Тореадори з Васюківки", "Всеволод Нестайко", 2024, 130.00});
    cout << "\n2) Після додавання книги на початок і в кінець:\n";
    printBooks(books);

    // Фільтрація: книги після 2020 р.
    cout << "\n3) Книги, видані після 2020 р.:\n";
    list<Book> filtered;
    for (const Book& b : books)
        if (b.year > 2020) filtered.push_back(b);
    printBooks(filtered);

    // Видалення: ціна менша за 150 грн
    books.remove_if([](const Book& b) { return b.price < 150; });
    cout << "\n4) Після видалення книг дешевших за 150 грн:\n";
    printBooks(books);

    // Сортування за ціною зростанням
    books.sort([](const Book& a, const Book& b) { return a.price < b.price; });
    cout << "\n5) Після сортування за ціною (зростання):\n";
    printBooks(books);

    return 0;
}