#include "rolodexlib.h"

using namespace std;

bool InsCaseComparison(const char& ch1, const char& ch2) {
    return (tolower(ch1) == tolower(ch2));
}

bool InsCaseComparison(const string& str1, const string& str2) {
    if (str1.length() != str2.length()) {
        return false;
    }

    for (size_t i = 0; i < str1.length(); ++i) {
        if (!InsCaseComparison(str1[i], str2[i])) {
            return false;
        }
    }

    return true;
}

void addEntry(LinkedList& entries, Trie& nameTrie, AVLTree& nameAVL) {
    Rolodex newEntry;
    string firstName, lastName, address, phone, email;

    cout << "Enter the first name: ";
    getline(cin, firstName);
    cout << "Enter the last name: ";
    getline(cin, lastName);
    cout << "Enter the address: ";
    getline(cin, address);
    cout << "Enter the phone number: ";
    getline(cin, phone);
    cout << "Enter the email address: ";
    getline(cin, email);

    newEntry.setFullName(firstName, lastName);
    newEntry.setAddress(address);
    newEntry.setPhone(phone);
    newEntry.setEmail(email);

    entries.add(newEntry);
    size_t index = entries.getSize() - 1;
    nameTrie.insert(newEntry.getFullName(), index);
    nameAVL.insert(newEntry.getFullName(), index);

    cout << "Entry added successfully." << endl;
}

void findEntries(const LinkedList& entries, const Trie& nameTrie) {
    if (entries.getSize() == 0) {
        cout << "The rolodex is empty." << endl;
        return;
    }

    string searchTerm;
    cout << "Enter the name to search for: ";
    getline(cin, searchTerm);

    vector<size_t> indices = nameTrie.search(searchTerm);
    if (!indices.empty()) {
        for (size_t index : indices) {
            const Rolodex& entry = entries.get(index);
            cout << "Name: " << entry.getFullName() << endl;
            cout << "Address: " << entry.getAddress() << endl;
            cout << "Phone: " << entry.getPhone() << endl;
            cout << "Email: " << entry.getEmail() << endl;
        }
    } else {
        cout << "No matching entries found." << endl;
    }
}

void editEntry(LinkedList& entries, Trie& nameTrie, AVLTree& nameAVL) {
    if (entries.getSize() == 0) {
        cout << "The rolodex is empty." << endl;
        return;
    }

    string searchTerm;
    cout << "Enter the name of the entry to edit: ";
    getline(cin, searchTerm);

    vector<size_t> indices = nameTrie.search(searchTerm);
    if (!indices.empty()) {
        size_t index = indices[0]; // Assume editing the first match
        Rolodex& entry = entries.get(index);

        string firstName, lastName, address, phone, email;

        cout << "Enter the new/current first name: ";
        getline(cin, firstName);
        cout << "Enter the new/current last name: ";
        getline(cin, lastName);
        cout << "Enter the new/current address: ";
        getline(cin, address);
        cout << "Enter the new/current phone number: ";
        getline(cin, phone);
        cout << "Enter the new/current email address: ";
        getline(cin, email);

        entry.setFullName(firstName, lastName);
        entry.setAddress(address);
        entry.setPhone(phone);
        entry.setEmail(email);

        cout << "Entry updated successfully." << endl;
    } else {
        cout << "No matching entries found." << endl;
    }
}

void deleteEntry(LinkedList& entries, Trie& nameTrie, AVLTree& nameAVL) {
    if (entries.getSize() == 0) {
        cout << "The rolodex is empty." << endl;
        return;
    }

    string searchTerm;
    cout << "Enter the name of the entry to delete: ";
    getline(cin, searchTerm);

    vector<size_t> indices = nameTrie.search(searchTerm);
    if (!indices.empty()) {
        size_t index = indices[0]; // Assume deleting the first match
        entries.remove(index);
        
        cout << "Entry deleted successfully." << endl;
    }
    else {
        cout << "No matching entries found." << endl;
    }
}

/*************  ✨ Codeium Command ⭐  *************/
/**
 * Prints all entries in the rolodex sorted by name.
 * @param entries LinkedList of all entries
 * @param nameAVL AVLTree of all names in the rolodex
 */
/******  fb418ea5-bca1-42a7-b465-4176a8c801ff  *******/
void sortEntries(const LinkedList& entries, const AVLTree& nameAVL) {
    vector<size_t> sortedIndices = nameAVL.getSortedIndices();
    cout << "Sorted Entries by Name:" << endl;
    for (size_t index : sortedIndices) {
        const Rolodex& entry = entries.get(index);
        cout << "Name: " << entry.getFullName() << endl;
        cout << "Address: " << entry.getAddress() << endl;
        cout << "Phone: " << entry.getPhone() << endl;
        cout << "Email: " << entry.getEmail() << endl;
    }
}

void printAllEntries(const LinkedList& entries) {
    if (entries.getSize() == 0) {
        cout << "The rolodex is empty." << endl;
        return;
    }

    Node* current = entries.getHead();
    size_t index = 0;
    while (current) {
        const Rolodex& entry = current->data;
        cout << "============================" << endl;
        cout << "Entry #" << ++index << ":" << endl;
        cout << "Name: " << entry.getFullName() << endl;
        cout << "Address: " << entry.getAddress() << endl;
        cout << "Phone: " << entry.getPhone() << endl;
        cout << "Email: " << entry.getEmail() << endl;
        cout << "============================" << endl;
        current = current->next;
    }
}
