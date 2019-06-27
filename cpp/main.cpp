#include "menu.h"

void startScheduler() {
    Scheduler cfScheduler;
    while (true) {
        menu(cfScheduler);
        cout << "\n\nEnter 0 to exit : ";
        std::cin >> data;
        if (data == 0)
            break;
    }

    return;
}

int main() {
    do {
        startScheduler();
        cout << "\n\Enter 0 to exit: ";
        std::cin >> data;

    } while (data != 0);

    return 0;
}