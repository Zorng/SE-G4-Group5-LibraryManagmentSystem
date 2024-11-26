#include <iostream>
#include <string>
using namespace std;

class TransactionNode{
    private:
        string transactionID;
        string itemID;
        string actorID;
        string time;
        string type;

        TransactionNode* prev;
        TransactionNode* next;
        //struct of borrower ID, borrowed book ID

        TransactionNode(string transactionID, string itemID, string actorID, string time, string type){
            this->transactionID = transactionID;            
            this->itemID = itemID;          
            this->actorID = actorID;            
            this->time = time;          
            this->type = type;          
        }

        //write a constructor for the class;

        //write a function that update the user transaction history whenever the transaction is made;
        friend class TransactionList;

};

class TransactionList{
    private:
        TransactionNode* head;
        TransactionNode* tail;
        int length;
    public:
        TransactionList(TransactionNode* head, TransactionNode* tail, int lenght){
            this->head = head;
            this->tail = tail;
            this->length = lenght;
        }

        int getLength() const{
            return length;
        }

        void insertFront(string& transactionID, string itemID, string& actorID, string& time, string& type){
            TransactionNode* newNode = new TransactionNode(transactionID, itemID, actorID, time, type);
            if(head = nullptr){
                head = tail = newNode;
            }else {
                newNode->next = head;
                head -> prev = newNode;
                head = newNode;
            }
            length++;
        }

        void insertBack(string& transactionID, string itemID, string& actorID, string& time, string& type){
            TransactionNode* newNode = new TransactionNode(transactionID, itemID, actorID, time, type);
            if(tail = nullptr){
                tail = head = newNode;
            }else {
                newNode->next = tail;
                tail -> prev = newNode;
                tail = newNode;
            }
            length++;
        }

        void remove_front(){
            if(head == nullptr){
                cout << "Error! empty database." << endl;
            }
            TransactionNode* temp = head;
            head->next = head;

            if(head != nullptr){
                head->prev = nullptr;
            }else{
                tail = nullptr;
            }
            delete temp;
            length--;

        }

        void remove_back(){
            if(tail == nullptr){
                cout << "Error! empty database." << endl;
            }
            TransactionNode* temp = tail;
            this->tail->next = tail;
            if(tail != nullptr){
                tail->prev = nullptr;
            }else{
                head = nullptr;
            }
            delete temp;
            length--;

        }

        void removeByID(){

        }

};