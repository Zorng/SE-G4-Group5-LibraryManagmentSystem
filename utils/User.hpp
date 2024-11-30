#ifndef User_hpp
#define User_hpp
#include "Common.hpp"
#define FILENAME "../database/userDB.txt"
class UserNode {
    private:
        string userName;
        string userId;
        string userPassword;
        string userBirthday;
        UserNode *next;
        UserNode *prev;

        UserNode( string userName, string userId, string userPassword, string userBirthday) {
            this->userName = userName;
            this->userId = userId;
            this->userBirthday = userBirthday;
            this->userPassword = userPassword;
            next = nullptr;
            prev = nullptr;
        }

        friend class UserList;
};

class UserList {
    private:
        UserNode *head;
        UserNode *tail;

    public: 
        UserList() {
            head = nullptr;
            tail = nullptr;
        }

        void insertFront (string userName, string userId, string userPassword, string userBirthday) {
            UserNode *newUser = new UserNode(userName, userId, userPassword, userBirthday);
            if (head == nullptr) {
                head = tail = newUser;
            } else {
                newUser->next = head;
                head->prev = newUser;
                head = newUser;
            }
        }

        void insertBack(string userName, string userId, string userPassword, string userBirthday) {
            UserNode *newUser = new UserNode(userName, userId, userPassword, userBirthday);
            if (tail == nullptr) {
                head = tail = newUser;
            } else {
                newUser->prev = tail;
                tail->next = newUser;
                tail = newUser;
            }
        }

        void removeFront() {
            if (head == nullptr) {
                cout << "List is empty" << endl;
                return;
            }

            UserNode *temp = head;
            if (head == tail) {
                head = tail = nullptr;
            } else {
                head = head->next;
                head->prev = nullptr;
            }
            delete temp;
        }

        void removeBack() {
            if (tail == nullptr) {
                cout << "List is empty" << endl;
                return;
            }

            UserNode *temp = tail;
            if (head == tail) {
                head = tail = nullptr;
            } else {
                tail = tail->prev;
                tail->next = nullptr;
            }
            delete temp;
        }

        void removeByID(string userId) {
            if (head == nullptr) {
                cout << "List is empty" << endl;
                return;
            }

            UserNode *temp = head;
            while (temp != nullptr && temp->userId != userId) {
                temp = temp->next;
            }

            if (temp == nullptr) {
                cout << "User with ID " << userId << " not found." << endl;
                return;
            }

            if (temp == head) {
                removeFront();
            } else if (temp == tail) {
                removeBack();
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
            }
        }

        void printUsers() {
            if (head == nullptr) {
                cout << "User list is empty." << endl;
                return;
            }

            UserNode* temp = head;
            cout << "Users in the list:" << endl;
            while (temp != nullptr) {
                cout << "Name: " << temp->userName
                    << ", ID: " << temp->userId
                    << ", Birthday: " << temp->userBirthday
                    << endl;
                temp = temp->next;
            }
    }

    void readUserDB(const string& filename) {
        ifstream file(filename);
        if (file.fail()) {
            cout << "Failed to open a file " << filename << endl;
            return;
        }

        string userName, userId, userPassword, userBirthday;
        while (file >> userName >> userId >> userPassword >> userBirthday) {
            insertBack(userName,  userId,  userPassword,  userBirthday);
        }

        file.close();
    }

    void writeUserDB() {
        fstream file;
        file.open(FILENAME, ofstream::app);
        if (file.fail()) {
            cout << "Failed to open a file " << FILENAME << endl;
            return;
        }

        UserNode *temp = head;
        while (temp != nullptr) {
            file << temp->userName << " "
                << temp->userId << " "
                << temp->userPassword << " "
                << temp->userBirthday << endl;
            temp = temp->next;
        }
        file.close();
    }
};

#endif