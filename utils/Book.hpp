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
                 << "Publish Date: " << curr->bookPbDate << ",\t"
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
        int itemPerPage = 10;
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
        totalPage = (totalItem/10) + 1;
        currentPage = 1;
        string navKey;
        int lower = 0;
        int k = 0;
        while(1) {
            clearScreen();
            lower = ((currentPage-1)) * itemPerPage;
            cout << "===== View all book =====" << endl;
            cout << "Page "<< currentPage << " of " << totalPage << endl;
            //cout << "Total nav "<< ++k << endl;
            cout << "Total titles: "<< bookMap.size() << endl;
            cout << endl;
            cout << setw(25) << left << "     Title" 
                 << setw(20) << left << "     Author" 
                 << setw(20) << left << "     Publish date" 
                 << setw(11) << left << "     avaialable" 
                 << endl;
           // cout << "lower "<< lower << endl;
            map_it = bookMap.begin();
            for(int i = 0; i < lower; i++) {
                map_it++;
            }  // set initial display element
            if(currentPage != totalPage) {
                for(int i = 0; i < 10; map_it++, i++){
                    for(int i = 0; i < 82; i++) cout << "-";
                    cout<< endl;
                    cout << "| " << setw(25) << left << map_it->first << "";
                    list_it = map_it->second.begin();
                    cout << setw(20) << left << get<0>(*list_it) << "" 
                         << "     "  << setw(15) << left << get<1>(*list_it) << ""
                         << "        " << setw(7) << left << get<2>(*list_it) << "|";
                    cout << endl;
                }
            } else { // last page
                 for(int i = 0; map_it != bookMap.end(); map_it++){
                    for(int i = 0; i < 82; i++) cout << "-";
                    cout << endl;
                    cout << "| " << setw(25) << left << map_it->first << "";
                    list_it = map_it->second.begin();
                    cout << setw(20) << left << get<0>(*list_it) << "" 
                         << "     "<< setw(15) << left << get<1>(*list_it) << ""
                         << "        " << setw(7) << left << get<2>(*list_it) << "|";
                    cout << endl;
                }
            }
            cout << endl;
            cout << "*********************************************************" << endl;
            cout << "Navigation:  previous page '<-', next page '->', exit 'q'" << endl;
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


        //Update the availability of the book status
        bool updateBorrow(string inputItemID){
            BookNode* current = head;
            while(current != nullptr){
                if(current->bookID == inputItemID){
                    current->availability = false; //Mark it as unvailable
                    cout << "Book ID " << inputItemID << " has been marked as unavailable." << endl;
                    return true;
                }
                current = current->next;
            }
            cout << "Book ID " << inputItemID << " not found in the list." << endl;
            return false;
        }

    //Admin add book to booklist
    void add(string inputID, string inputTitle, string inputAuthName, string inputPublishDate){
        //availability set to true when add new book
        insertBack(inputID, inputTitle, inputAuthName, inputPublishDate, true);
        cout << "Book ID " << inputID << " has been added successfully." << endl;
    }
        
    //Edit books
    void edit(string inputID){
        BookNode* current = head;
        while(current != nullptr){
            if(current->bookID == inputID){
                cout << "Editing Book ID: " << inputID << endl;
                cout << "Current Title: " << current->bookTitle << endl;
                cout << "Enter new Title: ";
                cin.ignore();
                getline(cin, current->bookTitle);

                cout << "Current Author: " << current->bookAuthor << endl;
                cout << "Enter new Author: ";
                getline(cin, current->bookAuthor);
        
                cout << "Current Publish Date: " << current->bookPbDate << endl;
                cout << "Enter new Publish Date (format MM-YYYY): ";
                getline(cin, current->bookPbDate);

                cout << "Book ID " << inputID << " has been updated successfully!" << endl;
                return;
            }
            current = current->next;
        }
        cout << "Book ID " << inputID << " does not exist." << endl;
    }

    //Remove book by admin
    void remove(string inputID){
        BookNode* current = head;
        bool found = false;
        while(current != nullptr){
            if(current->bookID == inputID){
                found = true;
                break;
            }
            current = current->next;
        }

        if(!found){
            cout << "Input ID does not exist." << endl;
            return;
        }

        //If found
        removeID(inputID);
        cout << "Book ID " << inputID << "has been removed." << endl;
    }
    void searchByTitle(string inputName) {
        map<string, list<tuple<string, string, int>>> bookMap;
        map<string, list<tuple<string, string, int>>>::iterator map_it;
        list<tuple<string, string, int>>:: iterator list_it;
        //  <title, <auth, date, count>>
        BookNode* curr = head;
        int itemPerPage = 10;
        int totalPage;
        int totalItem;
        int currentPage;
        while(curr != nullptr) {
            if(inputName == curr->bookTitle) {
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
            } 
            curr = curr->next;
        }
        totalItem = bookMap.size();
        totalPage = (totalItem/10) + 1;
        currentPage = 1;
        string navKey;
        int lower = 0;
        int k = 0;
        while(1) {
            clearScreen();
            lower = ((currentPage-1)) * itemPerPage;
            cout << "===== Search by Title =====" << endl;
            cout << "Page "<< currentPage << " of " << totalPage << endl;
            cout << "Search input: " << inputName << endl;
            //cout << "Total nav "<< ++k << endl;
            cout << "Total titles: "<< bookMap.size() << endl;
            cout << endl;
            cout << setw(25) << left << "     Title" 
                 << setw(20) << left << "     Author" 
                 << setw(20) << left << "     Publish date" 
                 << setw(11) << left << "     avaialable" 
                 << endl;
           // cout << "lower "<< lower << endl;
            map_it = bookMap.begin();
            for(int i = 0; i < lower; i++) {
                map_it++;
            }  // set initial display element
            if(currentPage != totalPage) {
                for(int i = 0; i < 10; map_it++, i++){
                    for(int i = 0; i < 82; i++) cout << "-";
                    cout<< endl;
                    cout << "| " << setw(25) << left << map_it->first << "";
                    list_it = map_it->second.begin();
                    cout << setw(20) << left << get<0>(*list_it) << "" 
                         << "     "  << setw(15) << left << get<1>(*list_it) << ""
                         << "        " << setw(7) << left << get<2>(*list_it) << "|";
                    cout << endl;
                }
            } else { // last page
                 for(int i = 0; map_it != bookMap.end(); map_it++){
                    for(int i = 0; i < 82; i++) cout << "-";
                    cout << endl;
                    cout << "|" << setw(25) << left << map_it->first << "";
                    list_it = map_it->second.begin();
                    cout << setw(20) << left << get<0>(*list_it) << "" 
                         << "     "<< setw(15) << left << get<1>(*list_it) << ""
                         << "        " << setw(7) << left << get<2>(*list_it) << "|";
                    cout << endl;
                }
            }
            cout << endl;
            cout << "*********************************************************" << endl;
            cout << "Navigation:  previous page '<-', next page '->', exit 'q'" << endl;
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
    void searchByAuth(string inputName) {
        map<string, list<tuple<string, string, int>>> bookMap;
        map<string, list<tuple<string, string, int>>>::iterator map_it;
        list<tuple<string, string, int>>:: iterator list_it;
        //  <title, <auth, date, count>>
        BookNode* curr = head;
        int itemPerPage = 10;
        int totalPage;
        int totalItem;
        int currentPage;
        while(curr != nullptr) {
            if(inputName == curr->bookAuthor) {
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
            } 
            curr = curr->next;
        }
        totalItem = bookMap.size();
        totalPage = (totalItem/10) + 1;
        currentPage = 1;
        string navKey;
        int lower = 0;
        int k = 0;
        while(1) {
            clearScreen();
            lower = ((currentPage-1)) * itemPerPage;
            cout << "===== Search by Author =====" << endl;
            cout << "Page "<< currentPage << " of " << totalPage << endl;
            cout << "Search input: " << inputName << endl;
            //cout << "Total nav "<< ++k << endl;
            cout << "Total titles: "<< bookMap.size() << endl;
            cout << endl;
            cout << setw(25) << left << "     Title" 
                 << setw(20) << left << "     Author" 
                 << setw(20) << left << "     Publish date" 
                 << setw(11) << left << "     avaialable" 
                 << endl;
           // cout << "lower "<< lower << endl;
            map_it = bookMap.begin();
            for(int i = 0; i < lower; i++) {
                map_it++;
            }  // set initial display element
            if(currentPage != totalPage) {
                for(int i = 0; i < 10; map_it++, i++){
                    for(int i = 0; i < 82; i++) cout << "-";
                    cout<< endl;
                    cout << "| " << setw(25) << left << map_it->first << "";
                    list_it = map_it->second.begin();
                    cout << setw(20) << left << get<0>(*list_it) << "" 
                         << "     "  << setw(15) << left << get<1>(*list_it) << ""
                         << "        " << setw(7) << left << get<2>(*list_it) << "|";
                    cout << endl;
                }
            } else { // last page
                 for(int i = 0; map_it != bookMap.end(); map_it++){
                    for(int i = 0; i < 82; i++) cout << "-";
                    cout << endl;
                    cout << "| " << setw(25) << left << map_it->first << "";
                    list_it = map_it->second.begin();
                    cout << setw(20) << left << get<0>(*list_it) << "" 
                         << "     "<< setw(15) << left << get<1>(*list_it) << ""
                         << "        " << setw(7) << left << get<2>(*list_it) << "|";
                    cout << endl;
                }
            }
            cout << endl;
            cout << "*********************************************************" << endl;
            cout << "Navigation:  previous page '<-', next page '->', exit 'q'" << endl;
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