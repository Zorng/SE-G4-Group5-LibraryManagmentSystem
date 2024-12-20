#ifndef User_hpp
#define User_hpp
#include "Common.hpp"
#include <conio.h>
#define FILENAME "database/userDB.txt"
class UserNode {
    private:
        string userId;
        string userName;
        string userPassword;
        string userBirthday;
        UserNode *next;
        UserNode *prev;

        UserNode(string userId, string userName, string userPassword, string userBirthday) {
            this->userId = userId;
            this->userName = userName;
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
        int length;

    public: 
        UserList() {
            head = nullptr;
            tail = nullptr;
            length = 0;
        }


        void insertFront (string id, string userName, string userPassword, string userBirthday) {
            UserNode *newUser = new UserNode(id, userName , userPassword, userBirthday);
            if (head == nullptr) {
                head = tail = newUser;
            } else {
                newUser->next = head;
                head->prev = newUser;
                head = newUser;
            }
            length++;
        }

        void insertBack(string id, string userName, string userPassword, string userBirthday) {
            UserNode *newUser = new UserNode(id, userName, userPassword, userBirthday);
            if (tail == nullptr) {
                head = tail = newUser;
            } else {
                newUser->prev = tail;
                tail->next = newUser;
                tail = newUser;
            }
            length++;
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
            length--;
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
            length--;
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

   void loadUserFromFile(string filename){
        ifstream loadUser(filename);
        if(!loadUser){
            cout << "Failed to open file" << endl;
            return;
        }
        string line;
        while(getline(loadUser, line)){ // read full line
            stringstream UserInfo(line);
            string UserId, UserName, UserPassword, UserBirthday;

            if(getline(UserInfo, UserId, ',') &&
               getline(UserInfo, UserName, ',') &&
               getline(UserInfo, UserPassword, ',') &&
               getline(UserInfo, UserBirthday, ',')){
                UserNode* newNode = new UserNode(UserId, UserName, UserPassword, UserBirthday);
                if(head == nullptr){
                    head = tail = newNode;
                }else{
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;
                }
                length++;
            }
        }
        loadUser.close();
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
            file << temp->userId << ","
                << temp->userName << ","
                << temp->userPassword << ","
                << temp->userBirthday << endl;
            temp = temp->next;
        }
        file.close();
    }

    bool searchAndCompare(string inputID, string inputPassword){
        UserNode* curr = head;
        while(curr != nullptr){
            if(curr->userId == inputID && curr->userPassword == inputPassword){
                return true;
            }
            curr = curr->next; // move to next node
        }
        return false;
    }

    void displayUsers(){
        if(head == nullptr){
            cout << "No users in list!" << endl;
            return;
        }

        const int USERS_PER_PAGES = 10;
        int page = 0;
        // calculate total page
        int totalPage = (length + USERS_PER_PAGES - 1) / USERS_PER_PAGES;
        UserNode* curr = head;

        while(1){
            cout << "----- User List (Page " << page+1 << " of " << totalPage << ") -----" << endl;

            // display user in current page
            UserNode* temp = curr;
            for(int i = 0; i < USERS_PER_PAGES && temp != nullptr; i++){
                cout << "ID: " << temp->userId
                     << ", Name: " << temp->userName
                     << ", Birthaday: " << temp->userBirthday << endl;
                temp = temp->next;
            }

            cout << endl << "Use left arrow (<-) for previous page, "
                         << "Use right arrow (->) for next page, "
                         << "and Esc for exit." << endl;

            int key = _getch();
            if(key == 27){ // Esc key
                break;
            }else if(key == 77){ // right arrow
                page++;
                for(int i = 0; i < USERS_PER_PAGES && curr != nullptr; i++){
                    curr = curr->next;
                }
            }else if(key == 75){
                page--;
                curr = head; // let curr = first user of the page;
                for(int i = 0; i < USERS_PER_PAGES && curr != nullptr; i++){
                    curr = curr->next;
                }
            }
        }
    }

    void add(string inputID, string inputName, string inputPassword, string inputBD){
        UserNode* newNode = new UserNode(inputID, inputName, inputPassword, inputBD);
        if(head == nullptr){
            head = tail = newNode;
        }else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        length++;

        cout << "User with ID: " << inputID << " has beed added success." << endl;
    }
};

#endif