#ifndef Admin_hpp
#define Admin_hpp
#include "Common.hpp"

class AdminNode {
private:
    string adminId;
    string adminName;
    string adminPassword;
    string adminBirthday;
    AdminNode* prev;
    AdminNode* next;
    
    //create a constructor for librarian object
    AdminNode(string adminId, string adminName, string adminPassword, string adminBirthday){
        this->adminId = adminId;
        this->adminName = adminName;
        this->adminPassword = adminPassword;
        this->adminBirthday = adminBirthday;
        prev = nullptr;
        next = nullptr;
    }
    friend class AdminList;
};

class AdminList{
private:
    AdminNode* head;
    AdminNode* tail;
    int length;
public:
    AdminList(){
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    int getLength(){
        return length;
    }

    // insert front
    void insertFront(string id, string adminName, string adminPassword, string adminBirthday){
        AdminNode* newNode = new AdminNode(id, adminName, adminPassword, adminBirthday);
        if(head == nullptr){
            head = tail = newNode;
        }else{
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        length++;
        // cout << "Admin added at front!" << endl;
    }

    // insert back
    void insertBack(string id, string adminName, string adminPassword, string adminBirthday){
        AdminNode* newNode = new AdminNode(id, adminName, adminPassword, adminBirthday);
        if(head == nullptr){
            head = tail = newNode;
        }else{
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        length++;
        // cout << "Admin added at back!" << endl;
    }

    // display admin
    void displayAdmin(){
        if(head == nullptr){
            cout << "No admin!" << endl;
            return;
        }
        AdminNode* curr = head;
        cout << "----- Admin List -----" << endl;
        while(curr != nullptr){
            cout << "ID: " << curr->adminId << ","
                 << " Name: " << curr->adminName << ","
                 << " Birthday: " << curr->adminBirthday << endl;
            curr = curr->next;
        }
    }

    void removeFront(){
        if(head == nullptr){
            cout << "No admin to remove" << endl;
        }
        AdminNode* temp = head;
        // if have only one admin
        if(head == tail){
            head = tail = nullptr;
        }else{
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        length--;
        cout << "Admin remove from the front" << endl;
    }

    void removeBack(){
        if(head == nullptr){
            cout << "No admin to remove" << endl;
        }
        AdminNode* temp = tail;
        // if have only one admin
        if(head == tail){
            head = tail = nullptr;
        }else{
            tail = tail->prev;
            head->next = nullptr;
        }
        delete temp;
        length--;
        cout << "Admin remove from the back" << endl;
    }

    void removeByID(string adminId){
        AdminNode* curr = head;
        bool found = false;
        while(curr != nullptr){
            if(curr->adminId == adminId){
                found = true;
                if(curr->prev != nullptr){
                    curr->prev->next = curr->next;
                }else{
                    head = curr->next;
                }

                if(curr->next != nullptr){
                    curr->next->prev = curr->prev;
                }else{
                    tail = curr->prev;
                }
                delete curr;
                length--;
                cout << "Admin with ID: " << adminId << " removed" << endl;
                break;
            }
            curr = curr->next;
        }
        if(!found){
            cout << "Admin with ID: " << adminId << " not found" << endl;
        }
    }
    void saveAdmin(string filename){
        ofstream saveAdminToFile(filename);
        if(!saveAdminToFile){
            cout << "File failed to open" << endl;
            return;
        }
        AdminNode* curr = head;
        while(curr != nullptr){
            saveAdminToFile << curr->adminId << ","
                            << curr->adminName << ","
                            << curr->adminPassword << ","
                            << curr->adminBirthday << endl;
            curr = curr->next;
        }
        saveAdminToFile.close();
        cout << "Save success" << endl;
    }

    void loadAdminFromFile(string filename){
        ifstream loadAdmin(filename);
        if(!loadAdmin){
            cout << "Failed to open file" << endl;
            return;
        }
        string line;
        while(getline(loadAdmin, line)){ // read full line
            stringstream adminInfo(line);
            string adminId, adminName, adminPassword, adminBirthday;

            if(getline(adminInfo, adminId, ',') &&
               getline(adminInfo, adminName, ',') &&
               getline(adminInfo, adminPassword, ',') &&
               getline(adminInfo, adminBirthday, ',')){
                AdminNode* newNode = new AdminNode(adminId, adminName, adminPassword, adminBirthday);
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
        loadAdmin.close();
    }

    bool searchAndCompare(string inputID, string inputPassword){
        AdminNode* curr = head;
        while(curr != nullptr){
            if(curr->adminId == inputID && curr->adminPassword == inputPassword){
                return true;
            }
            curr = curr->next; // move to next node
        }
        return false;
    }
};
#endif

