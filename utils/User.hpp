#ifndef User_hpp
#define User_hpp
#include "Common.hpp"
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

    void saveUser(string filename){
            ofstream savebookToFile(filename);
            if(!savebookToFile){
                cout << "File failed to open" << endl;
                return;
            }
            UserNode* curr = head;
            while(curr != nullptr){
                savebookToFile << curr->userId<< ","
                                << curr->userName << ","
                                << curr->userPassword << ","
                                << curr->userBirthday << endl;
                                
                curr = curr->next;
            }
            savebookToFile.close();
            cout << "Save success" << endl;
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
            clearScreen();
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
                         << "and q for exit." << endl;

            string input = readNav();
            if(input == "exit"){
                break;
            }else if(input == "right" && page+1 < totalPage){
                for(int i = 0; i < USERS_PER_PAGES && curr != nullptr; i++){
                    curr = curr->next;
                }
                page++;
            }else if(input == "left" && page > 0){
                curr = head;
                for(int i = 0; i < (page-1) * USERS_PER_PAGES; i++){
                    curr = curr->next;
                }
                page--;
            }
        }
    }

    void add(string inputID, string inputName, string inputPassword, string inputBD){
        insertBack(inputID, inputName, inputPassword, inputBD);
        cout << "User with ID: " << inputID << " has beed added success." << endl;
    }

    void edit(string inputID){
        if(head == nullptr){
            cout << "User list is Empty!" << endl;
            return;
        }

        UserNode* curr = head;
        while(curr != nullptr){
            if(curr->userId == inputID) {
                cout << "User found. Enter new Info: " << endl;
                cout << "Enter new User Name: ";
                cin.ignore(); // hamdle new line char
                getline(cin, curr->userName);
                cout << "Enter new User Password: ";
                //cin.ignore(); // hamdle new line char
                getline(cin, curr->userPassword);
                cout << "Enter new User Birthday (YYYY-MM-DD): ";
                 // hamdle new line char
                getline(cin, curr->userBirthday);

                cout << "User info updated success" << endl;
                return;
            }
            curr = curr->next;
        }
        // if not match
        cout << "User with ID: " << inputID << " not found." << endl;
    }

    void remove(string inputID){
        if(head == nullptr){
            cout << "User list is Empty!" << endl;
            return;
        }

        UserNode* curr = head;
        
        while(curr != nullptr){
            if(curr->userId == inputID){
                if(curr == head){ // if node to remove is head
                    head = curr->next;
                    if(head != nullptr){
                        head->prev = nullptr;
                    }
                }else if(head == tail){ //if node to remove is tail
                    tail = curr->prev;
                    if(tail != nullptr){
                        tail->next = nullptr;
                    }
                }else{
                    // if node in middle
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                }

                // if the list become empty
                if(head == nullptr){
                    tail = nullptr;
                }

                delete curr;
                length--;
                cout << "User with ID: " << inputID << " has been removed." << endl;
                return;
            }
            curr = curr->next;
        }
        cout << "User with ID: " << inputID << " not found." << endl;
    }
};

#endif