#ifndef Transaction_hpp
#define Transaction_hpp
#include "Common.hpp"
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

        void insertFront(string& transactionID, string& itemID, string& actorID, string& time, string& type){
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

        void insertBack(string& transactionID, string& itemID, string& actorID, string& time, string& type){
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

        void removeByID(string& transactionID){
            TransactionNode* curr = head;

            while(curr != nullptr){
                if(curr->transactionID == transactionID){
                    if(curr->prev != nullptr){
                        curr->prev->next=curr->next;
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

                    cout << "ID " << transactionID << " has been sucessfully deleted!";
                }else{
                    cout << "Invalid ID!" << endl;
                }
            }

        }
        void readTransactionDB(string& transactionDB){
            fstream file("transactionDB.txt");

            if(!file.is_open()){
                cout << "Error opening file!" << endl;
            }
            string transactionID, itemID, actorID, time, type;
            while(file << transactionID << itemID << actorID << time << type){
                insertBack(transactionID, itemID, actorID, time, type);
            }
            file.close();
        }

};
#endif