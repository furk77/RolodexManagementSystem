#include "rolodexlib.h"

using namespace std;

int main() {
    LinkedList entries;
    Trie nameTrie;
    AVLTree nameAVL;

    cout << "Welcome to the Rolodex program!!!\n\n";

    char choice;

    while (true) {
        cout << "Menu" << endl;
        cout << "1. Add an entry" << endl;
        cout << "2. Find entries" << endl;
        cout << "3. Edit an entry" << endl;
        cout << "4. Delete an entry" << endl;
        cout << "5. Print all entries" << endl;
        cout << "6. Sort all entries" << endl;
        cout << "7. Quit" << "\n\n";
        cout << "What would you like to do?: ";
        cin >> choice;
        cin.ignore(INF_FLAG, '\n');

        switch (toupper(choice)) {
            case '1': case 'A':
                addEntry(entries, nameTrie, nameAVL);
                break;
            case '2': case 'F':
                findEntries(entries, nameTrie);
                break;
            case '3': case 'E':
                editEntry(entries, nameTrie, nameAVL);
                break;
            case '4': case 'D':
                deleteEntry(entries, nameTrie, nameAVL);
                break;
            case '5': case 'P':
                printAllEntries(entries);
                break;
            case '6': case 'S':
                sortEntries(entries, nameAVL);
                break;
            case '7': case 'Q':
                cout << "\n";
                cout << "Thank you for using the rolodex program!!!\n";
                cout << "Have a great day!\n\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;
    }

    return 0;
}
