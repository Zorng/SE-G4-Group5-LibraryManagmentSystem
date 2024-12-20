#ifndef Transaction_hpp
#define Transaction_hpp
#include "Common.hpp"
class TransactionNode{
    private:
        string transactionID;
        string itemID;
        string actorID;
        string type;

        TransactionNode* prev;
        TransactionNode* next;
        //struct of borrower ID, borrowed book ID

        TransactionNode(string transactionID, string itemID, string actorID, string type){
            this->transactionID = transactionID;            
            this->itemID = itemID;          
            this->actorID = actorID;                     
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
        TransactionList(){
            this->head = nullptr;
            this->tail = nullptr;
            this->length = 0;
        }

        int getLength() const{
            return length;
        }

        void insertFront(string id, string itemID, string  actorID, string type){
            
            TransactionNode* newNode = new TransactionNode(id, itemID, actorID, type);
            if(head == nullptr){
                head = tail = newNode;
            }else {
                newNode->next = head;
                head -> prev = newNode;
                head = newNode;
            }
            length++;
        }

        void insertBack(string id, string itemID, string actorID, string type){
            
            TransactionNode* newNode = new TransactionNode(id, itemID, actorID, type);
            if(tail == nullptr){
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
        void loadTransactionFromFile(string filename){
            ifstream loadTransaction(filename);
            if(!loadTransaction){
                cout << "Failed to open file" << endl;
                return;
            }
            string line;
            while(getline(loadTransaction, line)){ // read full line
                stringstream TransactionInfo(line);
                string TrID, TrItemID, TrActorID, TrTime, TrType;

                if(getline(TransactionInfo, TrID, ',') &&
                getline(TransactionInfo, TrItemID, ',') &&
                getline(TransactionInfo, TrActorID, ',') &&
                getline(TransactionInfo, TrTime, ',') &&
                getline(TransactionInfo, TrType, ',')){
                    TransactionNode* newNode = new TransactionNode(TrID, TrItemID, TrActorID, TrType);
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
        loadTransaction.close();
    }

        void saveTransaction(string filename) {
            ofstream saveTransactionToFile(filename);
            if(!saveTransactionToFile){
                cout << "File failed to open" << endl;
                return;
            }
            TransactionNode* curr = head;
            while(curr != nullptr){
                saveTransactionToFile << curr->transactionID << ","
                                << curr->itemID << ","
                                << curr->actorID << ","
                                << curr->type<< endl;
                curr = curr->next;
            }
            saveTransactionToFile.close();
            cout << "Save success" << endl;
        }

        void displayTransaction(){
        if(head == nullptr){
            cout << "No Transaction!" << endl;
            return;
        }
        TransactionNode* curr = head;
        cout << "----- Transaction List -----" << endl;
        while(curr != nullptr){
            cout << "ID: " << curr->transactionID << ","
                 << " itemID: " << curr->itemID << ","
                 << " ActorID: " << curr->actorID << ","
                 << " Type: " << curr->type << endl;
            curr = curr->next;
        }
    }


};
#endif