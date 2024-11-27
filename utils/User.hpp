#include <iostream>
#include <string>
using namespace std;

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
                head = newUser;
            } else {
                newUser->next = head;
                head->prev = newUser;
                head = newUser;
            }
        }

        void insertBack(string userName, string userId, string userPassword, string userBirthday) {
            UserNode *newUser = new UserNode(userName, userId, userPassword, userBirthday);
            if (head == nullptr) {
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
};