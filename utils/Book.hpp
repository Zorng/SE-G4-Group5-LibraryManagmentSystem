#ifndef Book_hpp
#define Book_hpp
#include "Common.hpp"

class BookNode{
    private:
        string bookID;
        string bookTitle;
        string bookAuthor;
        string bookPbDate;
        bool availability;
        BookNode* prev;
        BookNode* next;
    public:
        //constructor;
        BookNode(string bookID, string bookTitle, string bookAuthor, string bookPbDate, bool status){
            this->bookID=bookID;
            this->bookTitle=bookTitle;
            this->bookAuthor=bookAuthor;
            this->bookPbDate=bookPbDate;
            this->availability = status;
            this->prev = nullptr;
            this->next = nullptr;
        }   

        //Allow access to BookList class
        friend class BookList;     
};

class BookList {
    private:
        BookNode* head;
        BookNode* tail;
        int length;

        //Generate ID for each book
    public:
        BookList(){
            head=nullptr;
            tail=nullptr;
            length=0;
        }

        int getLength() {
            return length;
        }

        //function to display book information (without summary) by ID of the book
        void showBookInfo(string id) {
            BookNode* current = head;
            while (current) {
                if (current->bookID == id) {
                    cout << "Book ID: " << current->bookID << endl;
                    cout << "Title: " << current->bookTitle << endl;
                    cout << "Author: " << current->bookAuthor << endl;
                    cout << "Published Date: " << current->bookPbDate << endl;
                    return;
                }
                current = current->next;
            }
            cout << "Book with ID " << id << " not found." << endl;
        }


        void insertFront(string id, string title, string author, string pbDate, bool status){
            BookNode* newNode = new BookNode(id, title, author, pbDate, status);
            if(!head){
                head = tail = newNode;
            } else{
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            ++length;
        }        

        void insertBack(string id, string title, string author, string pbDate, bool status){

            BookNode* newNode = new BookNode(id, title, author, pbDate, status);
            if(!tail){
                head = tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            ++length;
        }

        void removeFront(){
            if(!head) return;
            BookNode* temp = head;
            head = head->next;
            if(head){
                head->prev = nullptr;
            } else{
                tail = nullptr;
            }
            delete temp;
            --length;
        }

        void removeBack(){
            if (!tail) return;
            BookNode* temp = tail;
            tail = tail->prev;
            if (tail){
                tail->next = nullptr;
            }else{
                head = nullptr;
            }
            delete temp;
            --length;
        }

        void removeID(string id){
            BookNode* current = head;
            while (current){
                if (current->bookID == id){
                    if(current->prev){
                        current->prev->next = current->next;
                    } else {
                        head = current->next;
                    }

                    if (current->next){
                        current->next->prev = current->prev;
                    } else{
                        tail = current->prev;
                    }

                    delete current;
                    --length;
                    return;
                }
                current = current->next;
            }
        }

        //Read book from file and add them to the list
        void readBookDB(string bookDB){
            ifstream file(bookDB);
            if(!file.is_open()){
                cerr << "Unable to open file: " << bookDB << endl;
                return;
            }

            string line, id, title, author, pbDate, status;
            int totalAmount;
            while (getline(file, line)){
                stringstream ss(line);
                getline(ss, id, ',');
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, pbDate, ',');
                getline(ss, status, ',');
                bool st;
                if(status == "0") st = false;
                else st = true;
                insertBack(id, title, author, pbDate, st);
            }

            file.close();
        }

        void saveBook(string filename){
            ofstream savebookToFile(filename);
            if(!savebookToFile){
                cout << "File failed to open" << endl;
                return;
            }
            BookNode* curr = head;
            while(curr != nullptr){
                savebookToFile << curr->bookID << ","
                                << curr->bookTitle << ","
                                << curr->bookAuthor << ","
                                << curr->bookPbDate << ","
                                << curr->availability<< endl;
                                
                curr = curr->next;
            }
            savebookToFile.close();
            cout << "Save success" << endl;
        }

        void print() {
            BookNode* curr = head;
            cout << "----- Book List -----" << endl;
            while(curr != nullptr){
            cout << "ID: " << curr->bookID << ",\t"
                 << "Name: " << curr->bookTitle << ",\t"
                 << "Birthday: " << curr->bookPbDate << ",\t"
                 << "Availability: " << curr->availability << endl;
            curr = curr->next;
            }
        }

    void transformList() {
        map<string, list<tuple<string, string, int>>> bookMap;
        map<string, list<tuple<string, string, int>>>::iterator map_it;
        list<tuple<string, string, int>>:: iterator list_it;
        //  <title, <auth, date, count>>
        BookNode* curr = head;
        int itemPerPage = 5;
        int totalPage;
        int totalItem;
        int currentPage;
        while(curr != nullptr) {
            if(bookMap.size() == 0) {
                bookMap[curr->bookTitle].push_back(make_tuple(curr->bookAuthor, curr->bookPbDate, 1));
            } else {
                for(map_it = bookMap.begin(); map_it != bookMap.end(); ++map_it){
                    if(map_it->first == curr->bookTitle){
                        get<2>(*map_it->second.begin())++;
                    } 
                }
                if (map_it == bookMap.end()) {
                    bookMap[curr->bookTitle].push_back(make_tuple(curr->bookAuthor, curr->bookPbDate, 1));
                }
            } 
            curr = curr->next;
        }
        totalItem = bookMap.size();
        totalPage = (totalItem/5) + 1;
        currentPage = 1;
        string navKey;
        int lower = 0;
        int k = 0;
        while(1) {
            system("clear");
            lower = ((currentPage-1)) * itemPerPage;
            cout << "========================================" << endl;
            cout << "Press left arrow to go to previous page, right arrow to go to next page, q to exit" << endl;
            cout << "Press right arrow to go to next page" << endl;
            cout << "Press q to exit" << endl;
            cout << "========================================" << endl;
            cout << "Current page "<< currentPage << endl;
            cout << "Total page "<< totalPage << endl;
            //cout << "Total nav "<< ++k << endl;
            cout << "Total titles: "<< bookMap.size() << endl;
            cout << "========================================" << endl;
            cout << "title\t" << "auth\t" << "publish date\t" << "avaialable" << endl;
           // cout << "lower "<< lower << endl;
            map_it = bookMap.begin();
            for(int i = 0; i < lower; i++) {
                map_it++;
            }  // set initial display element
            if(currentPage != totalPage) {
                for(int i = 0; i < 5; map_it++, i++){
                    cout << map_it->first << ", ";
                    list_it = map_it->second.begin();
                    cout << get<0>(*list_it) << ", " << get<1>(*list_it) << ", " << get<2>(*list_it);
                    cout << endl;
                }
            } else { // last page
                 for(int i = 0; map_it != bookMap.end(); map_it++){
                    cout << map_it->first << ", ";
                    list_it = map_it->second.begin();
                    cout << get<0>(*list_it) << ", " << get<1>(*list_it) << ", " << get<2>(*list_it);
                    cout << endl;
                }
            }
            navKey = readNav();
            if(navKey == "left") {
                if(currentPage != 1) currentPage--;
            } else if (navKey == "right") {
                if(currentPage < totalPage) currentPage++;
            } else if (navKey == "exit") {
                break;
            }
        }
    }
};


#endif