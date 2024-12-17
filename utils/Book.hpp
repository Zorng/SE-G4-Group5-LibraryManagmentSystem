#ifndef Book_hpp
#define Book_hpp
#include "Common.hpp"

class BookNode{
    private:
        string bookID;
        string bookTitle;
        string bookAuthor;
        string bookPbDate;
        string summary;
        int totalAmount;
        int borrowedAmount;
        //totalAvailable = totalAmount - borrowedAmount
        BookNode* prev;
        BookNode* next;
    public:
        //constructor;
        BookNode(string bookID, string bookTitle, string bookAuthor, string bookPbDate, string summary = "", int totalAmount = 0, int borrowedAmount = 0){
            this->bookID=bookID;
            this->bookTitle=bookTitle;
            this->bookAuthor=bookAuthor;
            this->bookPbDate=bookPbDate;
            this->summary=summary;
            this->totalAmount=totalAmount;
            this->borrowedAmount=borrowedAmount;
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
        int counter = 1; //static counter

        //Generate ID for each book
        string generateID(){
            return "IDBOOK" + to_string(counter++);
        }
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
                    cout << "Total Amount: " << current->totalAmount << endl;
                    cout << "Borrowed: " << current->borrowedAmount << endl;
                    return;
                }
                current = current->next;
            }
            cout << "Book with ID " << id << " not found." << endl;
        }


        void insertFront(string title, string author, string pbDate, string summary = "", int totalAmount = 0){
            string id = generateID();
            BookNode* newNode = new BookNode(id, title, author, pbDate, summary, totalAmount, 0);
            if(!head){
                head = tail = newNode;
            } else{
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            ++length;
        }        

        void insertBack(string title, string author, string pbDate, string summary = "", int totalAmount = 0){
            string id = generateID();
            BookNode* newNode = new BookNode(id, title, author, pbDate, summary, totalAmount, 0);
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

            string line, title, author, pbDate, summary;
            int totalAmount;
            while (getline(file, line)){
                stringstream ss(line);
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, pbDate, ',');
                getline(ss, summary, ',');
                ss >> totalAmount;

                insertBack(title, author, pbDate, summary, totalAmount);
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
                                << curr->totalAmount << ","
                                << curr->borrowedAmount << endl;
                                
                curr = curr->next;
            }
            savebookToFile.close();
            cout << "Save success" << endl;
        }
};
#endif