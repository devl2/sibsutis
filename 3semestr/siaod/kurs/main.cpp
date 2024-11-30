#include "menu.h"

int main() {
	SetConsoleCP(866);
    SetConsoleOutputCP(866);

    List records = data(MAX_RECORDS);
    tree* root = nullptr;
    menu(records);
    return 0;
}