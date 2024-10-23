#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Info::Info() {
    this->name = "No Name Set";
    this->value = "No Value Set";
    this->next = nullptr;
}

Info::Info(std::string name, std::string value, Info *next) {
    this->name = name;
    this->value = value;
    this->next = next;
}

Contact::Contact() {
    this->first = "No First Set";
    this->last = "No Last Set";
    this->next = nullptr;
    this->headInfoList = nullptr;
}

Contact::Contact(std::string first, std::string last, Contact *next) {
    this->first = first;
    this->last = last;
    this->next = next;
    this->headInfoList = nullptr;
}

ContactList::ContactList() {
    this->headContactList = nullptr;
    this->count = 0;
}

int ContactList::getCount() {
    return this->count;
}

// print the specified contact and its information
// 1. return false and print nothing if the contact is not in the list
// 2. otherwise return true and print the contact
bool ContactList::printContact(std::ostream &os, std::string first, std::string last) { // DONE
    if (!exists(first, last)) return false;

    os << "Contact name: " << first << " " << last << endl;
    Contact *curContact = headContactList;
    while (curContact->first != first && curContact->last != last) {
        curContact= curContact->next;
    }

    for (Info *curInfo = curContact->headInfoList; curInfo != nullptr; curInfo = curInfo->next) {
        os << curInfo->name << " | " << curInfo->value << endl;
    }
    return true;
}

// print all contacts and their information
// print nothing if the list is empty
void ContactList::print(std::ostream &os) { // DONE
    for (Contact *cur = headContactList; cur != nullptr; cur = cur->next) {
        os << "Contact Name: " << cur->first << " " << cur->last << endl;
        if (cur->headInfoList != nullptr) {
            for (Info *infoCur = cur->headInfoList; infoCur != nullptr; infoCur = infoCur->next) {
                os << infoCur->name << " | " << infoCur->value << endl;
            }
        }
    }
}

// add a contact to the back of the list
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the back of the list
// - do not forget to update count
bool ContactList::addContact(std::string first, std::string last) { // DONE
    if (exists(first, last)) return false;

    count++;
    Contact *n = new Contact(first, last);
    if (headContactList == nullptr) { // empty list
        headContactList = n;
        return true;
    }

    Contact *end = headContactList;
    while(end->next != nullptr) { // other cases
        end = end->next;
    }
    end->next = n;
    
    return true;
}

// add info to the back of a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the back of the contact's list and return true
bool ContactList::addInfo(std::string first, std::string last, std::string infoName, std::string infoVal) { // DONE
    if (!exists(first, last)) return false; // step 1
    
    Info *n = new Info(infoName, infoVal);
    Contact *cur = headContactList;
    while (cur->first != first) {
        cur = cur->next;
    }
    
    Info *infoPtr = cur->headInfoList;
    while(infoPtr != nullptr) {
        if (infoPtr->name == infoName) { // step 2
            infoPtr->value = infoVal;
            delete n;
            return true;
        }
        infoPtr = infoPtr->next;
    }

    if (cur->headInfoList == nullptr) { // step 3
        cur->headInfoList = n;
    } else {
        Info *curInfo = cur->headInfoList;
        while (curInfo->next != nullptr) {
            curInfo = curInfo->next;
        }
        curInfo->next = n;
    }

    return true;
}

// add a contact to the list in ascending order by last name
//     if last names are equal, then order by first name ascending
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the list
// - do not forget to update count
// - compare strings with the built-in comparison operators: <, >, ==, etc.
// - a compare method/function is recommended
bool ContactList::addContactOrdered(std::string first, std::string last) { // FIXME: lastname same
    if (exists(first, last)) return false; // Contact is already in da List

    Contact *n = new Contact(first, last);
    if (headContactList == nullptr) { // List is empty
        headContactList = n;
        count++;
        return true;
    }

    char letterComp = headContactList->last[0];
    char newLetter = last[0];
    if (newLetter < letterComp) { // Does not require iteration if n is first alphabetically  
        n->next = headContactList;
        headContactList = n;
    } else {        
        Contact *prev = headContactList;
        Contact *cur = headContactList->next;
        while (cur != nullptr) {
            if (newLetter == cur->last[0]) { 
                if (n->last == cur->last) { // why doesn't this work ??
                    if (first[0] < cur->first[0]) break;
                    else {
                        prev = prev->next;
                        cur = cur->next;
                        break;
                    }
                }                
            }
            if (newLetter < cur->last[0]) break;

            prev = prev->next;
            cur = cur->next;
        }
        prev->next = n;
        n->next = cur;
    }

    count++;
    return true;
}

// add info to a contact's info list in ascending order by infoName
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the contact's list and return true
bool ContactList::addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal) { // DONE
    if (!exists(first, last)) return false; 

    Info *newInfo = new Info(infoName, infoVal);
    Contact *curContact = headContactList;
    while (curContact->first != first && curContact->last != last) { // finds desired contact
        curContact = curContact->next;
    }

    Info *infoPtr = curContact->headInfoList;
    while(infoPtr != nullptr) { // if infoName is already in list
        if (infoPtr->name == infoName) { // step 2
            infoPtr->value = infoVal;
            delete newInfo;
            return true;
        }
        infoPtr = infoPtr->next;
    }

    if (curContact->headInfoList == nullptr) { // step 3 empty list
        curContact->headInfoList = newInfo;
    } else { 
        if (infoName[0] < curContact->headInfoList->name[0]) {
            newInfo->next = curContact->headInfoList;
            curContact->headInfoList = newInfo;
        }
        Info *prev = curContact->headInfoList;
        Info *curInfo = curContact->headInfoList->next;
        while (curInfo != nullptr) { // other cases
            if (infoName[0] < curInfo->name[0]) break;
            prev = curInfo;
            curInfo = curInfo->next;
        }
        prev->next = newInfo;
        newInfo->next = curInfo;
    }
    return true;
}

// remove the contact and its info from the list
// 1. return false and do nothing if the contact is not in the list
// 2. otherwise return true and remove the contact and its info
// - do not forget to update count
bool ContactList::removeContact(std::string first, std::string last) { // DONE
    if (!exists(first, last)) return false;

    count--;
    if (headContactList->first == first && headContactList->last == last) { // requires no looping
        Contact *temp = headContactList;
        headContactList = headContactList->next;
        delete temp;
        return true;
    }

    Contact *prev = headContactList;
    Contact *cur = headContactList->next;
    while(cur->first != first && cur->last != last) { // gots to loop
        cur = cur->next;
        prev = prev->next;
    }
    prev->next = cur->next;
    delete cur;
    return true;
}

// remove the info from a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. return false and do nothing if the info is not in the contact's info list
// 3. otherwise return true and remove the info from the contact's list
bool ContactList::removeInfo(std::string first, std::string last, std::string infoName) { // DONE
    if (!exists(first, last)) return false;

    Contact *curContact = headContactList;
    while (curContact->first != first && curContact->last != last) {
        curContact = curContact->next;
    }

    if (!infoExists(curContact->headInfoList, infoName)) return false;

    if (curContact->headInfoList->name == infoName) { // if info is first of the list
        Info *temp = curContact->headInfoList;
        curContact->headInfoList = curContact->headInfoList->next;
        delete temp;
        return true;
    }

    Info *prev = curContact->headInfoList;
    Info *curInfo = curContact->headInfoList->next;
    while (curInfo->name != infoName) { // other cases
        curInfo = curInfo->next;
        prev = prev->next;
    }
    prev->next = curInfo->next;
    delete curInfo;
    return true;
}

bool ContactList::exists(std::string first, std::string last) { // checks if item exists in list
    for (Contact *cur = headContactList; cur != nullptr; cur = cur->next) {
        if (cur->first == first && cur->last == last) {
                return true;
            }
    }   
    return false;
}

bool ContactList::infoExists(Info* headInfo, std::string infoName) { // checks if info exists in the contact
    for (Info *curInfo = headInfo; curInfo != nullptr; curInfo = curInfo->next) {
        if (curInfo->name == infoName) {
            return true;
        }
    }
    return false;
}


// destroy the list by removing all contacts and their infos
ContactList::~ContactList() { // this works now :]
    Contact *curContact = headContactList;
    while (curContact != nullptr) {
        Contact *nextContact = curContact->next;
        Info *curInfo = curContact->headInfoList;
        while (curInfo != nullptr) {
            Info *nextInfo = curInfo->next;
            delete curInfo;
            curInfo = nextInfo;
        }
        delete curContact;
        curContact = nextContact;
    }
}

// deep copy the source list
// - do not forget to update count
ContactList::ContactList(const ContactList &src) { // doneski
    this->headContactList = nullptr;
    this->count = 0;

    Contact *srcContact = src.headContactList;
    while (srcContact != nullptr) {
        Contact *newContact = new Contact(srcContact->first, srcContact->last);
        Info *srcInfo = srcContact->headInfoList;
        while (srcInfo != nullptr) {
            Info *newInfo = new Info(srcInfo->name, srcInfo->value);
            if (newContact->headInfoList == nullptr) {
                newContact->headInfoList = newInfo;
            } else {
                Info *lastInfo = newContact->headInfoList;
                while (lastInfo->next != nullptr) {
                    lastInfo = lastInfo->next;
                }
                lastInfo->next = newInfo;
            }
            srcInfo = srcInfo->next;
        }
        if (this->headContactList == nullptr) {
            this->headContactList = newContact;
        } else {
            Contact *lastContact = this->headContactList;
            while (lastContact->next != nullptr) {
                lastContact = lastContact->next;
            }
            lastContact->next = newContact;
        }
        srcContact = srcContact->next;
        this->count++;
    }
}

// remove all contacts and their info then deep copy the source list
// - do not forget to update count
const ContactList &ContactList::operator=(const ContactList &src) { // doneski
    if (this != &src) {
        Contact *curContact = this->headContactList;
        while (curContact != nullptr) {
            Contact *nextContact = curContact->next;
            Info *curInfo = curContact->headInfoList;
            while (curInfo != nullptr) {
                Info *nextInfo = curInfo->next;
                delete curInfo;
                curInfo = nextInfo;
            }
            delete curContact;
            curContact = nextContact;
        }

        this->headContactList = nullptr;
        this->count = 0;
        Contact *srcContact = src.headContactList;
        while (srcContact != nullptr) {
            Contact *newContact = new Contact(srcContact->first, srcContact->last);
            Info *srcInfo = srcContact->headInfoList;
            while (srcInfo != nullptr) {
                Info *newInfo = new Info(srcInfo->name, srcInfo->value);
                if (newContact->headInfoList == nullptr) {
                    newContact->headInfoList = newInfo;
                } else {
                    Info *lastInfo = newContact->headInfoList;
                    while (lastInfo->next != nullptr) {
                        lastInfo = lastInfo->next;
                    }
                    lastInfo->next = newInfo;
                }
                srcInfo = srcInfo->next;
            }
            if (this->headContactList == nullptr) {
                this->headContactList = newContact;
            } else {
                Contact *lastContact = this->headContactList;
                while (lastContact->next != nullptr) {
                    lastContact = lastContact->next;
                }
                lastContact->next = newContact;
            }
            srcContact = srcContact->next;
            this->count++;
        }
    }
    return *this;
}
