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
            prev = nullptr;
            next = nullptr;        
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
            if(!tail){
                tail = head = newNode;
            }else {
                tail->next = newNode;
                newNode->prev = tail;
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
        void readTransactionDB(string filename){
            ifstream file(filename);
            if(!file.is_open()){
                cerr << "Unable to open file: " << filename << endl;
                return;
            }

            string line, id, itemId, actorId, type;
            
            while (getline(file, line)){
                stringstream ss(line);
                getline(ss, id, ',');
                getline(ss, itemId, ',');
                getline(ss, actorId, ',');
                getline(ss, type, ',');
                insertBack(id, itemId, actorId, type);
            }
            file.close();
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
    void addBorrow(string id, string itemID, string actorID, string type){
        insertBack(id, itemID, actorID, "Borrowing");
        cout << "added " << id << endl; 
    }
    void acceptReturn(string inputitemID){
        TransactionNode* curr = head;

        while(curr != nullptr){
            if(curr->itemID == inputitemID){
                curr->type = "Returned";
                cout << "Item " << inputitemID << " marked as returned.";
                
                return;
            }
            curr = curr->next;
        }

        cout << "Input item ID does not exist in transaction list";
    }
    
    void showTrList() {
        TransactionNode* curr = head;
        const int tr_PER_PAGES = 10;
        int totalPage = (length + tr_PER_PAGES - 1) / tr_PER_PAGES;
        int page = 0;
        cout    << setw(20) << left << "      Transaction ID" 
                 << setw(20) << left << "     Item ID" 
                 << setw(20) << left << "     User ID" 
                 << setw(20) << left << "     Status" 
                 << endl;
        // while(curr != nullptr) {
        //     cout << endl;
        //     cout << "| " << setw(20) << curr->transactionID << ""
        //          << "    " << setw(16)<< curr->itemID << ""
        //          << "    " << setw(16)<< curr->actorID << ""
        //          << "    " << setw(16)<< curr->type << "|" <<
        //     endl;
        //     curr = curr->next;
        // }
        while(1) {
            clearScreen();
            cout << "----- Transaction List (Page " << page+1 << " of " << totalPage << ") -----" << endl;
            cout << setw(20) << left << "      Transaction ID" 
                 << setw(20) << left << "     Item ID" 
                 << setw(20) << left << "     User ID" 
                 << setw(20) << left << "     Status" 
                 << endl;
            for(int i = 0; i < tr_PER_PAGES && curr != nullptr; i++){
                for(int i = 0; i < 82; i++) cout << "-";
                cout << endl;
                cout << "| " << setw(20) << curr->transactionID << ""
                    << "    " << setw(16)<< curr->itemID << ""
                    << "    " << setw(16)<< curr->actorID << ""
                    << "    " << setw(16)<< curr->type << "|" <<
                endl;
                curr = curr->next;
            }
            cout << "*********************************************************" << endl;
            cout << "Navigation:  previous page '<-', next page '->', exit 'q'" << endl;
            string input = readNav();
            if(input == "exit"){
                break;
            }else if(input == "right" && page+1 < totalPage){
                for(int i = 0; i < tr_PER_PAGES && curr != nullptr; i++){
                    curr = curr->next;
                }
                page++;
            }else if(input == "left" && page > 0){
                curr = head;
                for(int i = 0; i < (page-1) * tr_PER_PAGES; i++){
                    curr = curr->next;
                }
                page--;
            }
        }
    }
};
#endif