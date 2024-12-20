#ifndef User_hpp
#define User_hpp
#include "Common.hpp"
#define FILENAME "database/userDB.txt"
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
        int length;

    public: 
        UserList() {
            head = nullptr;
            tail = nullptr;
            length = 0;
        }

        string generateID() {
            return "userID" + to_string(length+1); 
        }

        void insertFront (string userName, string userPassword, string userBirthday) {
            string id = generateID();
            UserNode *newUser = new UserNode(userName, id, userPassword, userBirthday);
            if (head == nullptr) {
                head = tail = newUser;
            } else {
                newUser->next = head;
                head->prev = newUser;
                head = newUser;
            }
        }

        void insertBack(string userName, string userPassword, string userBirthday) {
            string id = generateID();
            UserNode *newUser = new UserNode(userName, id, userPassword, userBirthday);
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
                UserNode* newNode = new UserNode(UserName, UserId, UserPassword, UserBirthday);
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
            file << temp->userName << ","
                << temp->userId << ","
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
};

#endif