#ifndef ROLODEXLIB_H
#define ROLODEXLIB_H

#include <iostream>
#include <string>
#include <limits>
#include "trie.h"
#include "avltree.h"

using namespace std;
constexpr streamsize INF_FLAG{numeric_limits<streamsize>::max()};

enum CompTo { Name, Address, Phone, Email };

class Rolodex {
    string fname, lname;
    string address;
    string phone;
    string email;

public:
    Rolodex() = default;
    Rolodex(const Rolodex & copy) = default;

    string getFullName() const {
        return fname + " " + lname;
    }

    string getAddress() const {
        return address;
    }

    string getPhone() const {
        return phone;
    }

    string getEmail() const {
        return email;
    }

    void setFullName(const string& firstName, const string& lastName) {
        fname = firstName;
        lname = lastName;
    }

    void setAddress(const string& addr) {
        address = addr;
    }

    void setPhone(const string& ph) {
        phone = ph;
    }

    void setEmail(const string& emailAddr) {
        email = emailAddr;
    }

    short compare(const string& comp_this, CompTo to_this) const {
        switch (to_this) {
            case Name:
                return static_cast<short>(getFullName().compare(comp_this));
            case Address:
                return static_cast<short>(address.compare(comp_this));
            case Phone:
                return static_cast<short>(phone.compare(comp_this));
            case Email:
                return static_cast<short>(email.compare(comp_this));
            default:
                return 0;
        }
    }

    Rolodex & operator=(const Rolodex & c) = default;
};

struct Node {
    Rolodex data;
    Node* next;

    Node(const Rolodex& entry) : data(entry), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    size_t size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        size = 0;
    }

    void add(const Rolodex& entry) {
        Node* newNode = new Node(entry);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        ++size;
    }

    Node* getHead() const {
        return head;
    }

    size_t getSize() const {
        return size;
    }

    Rolodex& get(size_t index) const {
        Node* current = head;
        for (size_t i = 0; i < index && current; ++i) {
            current = current->next;
        }
        if (current) {
            return current->data;
        }
        throw std::out_of_range("Index out of range");
    }

    void remove(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        Node* prev = nullptr;
        for (size_t i = 0; i < index; ++i) {
            prev = current;
            current = current->next;
        }

        if (prev) {
            prev->next = current->next;
        } else {
            head = current->next;
        }

        delete current;
        --size;
    }
};

class LinkedList;

bool InsCaseComparison(const char& ch1, const char& ch2);

bool InsCaseComparison(const std::string& str1, const std::string& str2);

void addEntry(LinkedList& entries, Trie& nameTrie, AVLTree& nameAVL);

void findEntries(const LinkedList& entries, const Trie& nameTrie);

void editEntry(LinkedList& entries, Trie& nameTrie, AVLTree& nameAVL);

void deleteEntry(LinkedList& entries, Trie& nameTrie, AVLTree& nameAVL);

void sortEntries(const LinkedList& entries, const AVLTree& nameAVL);

void printAllEntries(const LinkedList& entries);

#endif
