#include <iostream>
#include <list>
#include <iterator>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

void printList(const string& title, const list<int>& l) {
    cout << title;
    if (l.empty()) cout << "(список порожній)";
    for (int x : l) cout << x << " ";
    cout << endl;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    int n;
    cout << "Введіть кількість елементів N (N > 0): ";
    while (!(cin >> n) || n <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка! N має бути додатним цілим числом. Повторіть: ";
    }

    list<int> numbers;
    cout << "Введіть " << n << " цілих чисел: ";
    for (int i = 0; i < n; ++i) {
        int x;
        while (!(cin >> x)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка! Введіть ціле число: ";
        }
        numbers.push_back(x);
    }

    printList("\nПочатковий список:                   ", numbers);

    // 1) Видалення елемента після кожного 4
    int removed = 0;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it == 4) {
            auto nxt = next(it);
            if (nxt != numbers.end()) {   // елемент після 4 існує
                numbers.erase(nxt);
                ++removed;
            }
        }
    }
    printList("Після видалення елементів після 4: ", numbers);
    cout << "  (видалено елементів: " << removed << ")\n";

    // 2) Вставка 0 перед кожним 1
    int inserted = 0;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it == 1) {
            numbers.insert(it, 0);        // insert вставляє ПЕРЕД it
            ++inserted;
        }
    }
    printList("Після вставки 0 перед кожним 1:    ", numbers);
    cout << "  (вставлено нулів: " << inserted << ")\n";

    printList("\nРезультуючий список:                 ", numbers);
    return 0;
}