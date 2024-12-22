#include "utils/Common.hpp"
#include "utils/Admin.hpp"
#include "utils/User.hpp"
#include "utils/Book.hpp"
#include "utils/Transaction.hpp"

void UserMode(){
    int choice;
    while(1){
        cout << "----- USER PORTAL -----" << endl;
        cout << "1. View all Books" << endl;
        cout << "2. Search book by title" << endl;
        cout << "3. Search book by author" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter option: ";
        cin >> choice;

        switch(choice){
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 0: {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "INVALID CHOICE! PLease try again..." << endl;
                break;
            }
        }
    }
}

void AdminMode(){
    int choice;
    while(1){
        cout << "----- ADMIN PORTAL -----" << endl;
        cout << "1. Permit a borrow" << endl;
        cout << "2. Accept return" << endl;
        cout << "3. View users" << endl;
        cout << "4. Add users" << endl;
        cout << "5. Edit users" << endl;
        cout << "6. Remove users" << endl;
        cout << "7. View books" << endl;
        cout << "8. Add books" << endl;
        cout << "9. Edit books" << endl;
        cout << "10. Remove books" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter option: ";
        cin >> choice;

        switch(choice){
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                break;
            }
            case 7: {
                break;
            }
            case 8: {
                break;
            }
            case 9: {
                break;
            }
            case 10: {
                break;
            }
            case 0: {
                cout << "Exiting..." << endl;
                return;
            }
            default: {
                cout << "INVALID CHOICE! PLease try again..." << endl;
                break;
            }
        }
    }
}

int main(){

    string inputID;
    string inputPassword;

    AdminList admin;
    UserList user;
    BookList book;
    TransactionList transaction;

    admin.loadAdminFromFile("database/adminDB.txt");
    user.loadUserFromFile("database/userDB.txt");
    book.readBookDB("database/bookDB.txt");
    transaction.loadTransactionFromFile("database/transactionDB.txt");

    while(true){
        clearScreen();
        cout << "----- Login Screen -----" << endl;
        cout << "Input ID: ";
        cin >> inputID;
        cout << "Input Password: ";
        cin >> inputPassword;

        // convert the input to uppercase to avoid case sensitive
        for(size_t i = 0; i < inputID.length(); i++){
            inputID[i] = toupper(inputID[i]);
        }

        // check if input start with user or admin
        if(inputID.substr(0,4) == "USER"){
            if(user.searchAndCompare(inputID, inputPassword)){
                cout << "User login success" << endl;
                UserMode();
                break;
            }else{
                cout << "User login failed" << endl;
            }
        }else if(inputID.substr(0,5) == "ADMIN"){
            if(admin.searchAndCompare(inputID, inputPassword)){
                cout << "Admin login success" << endl;
                AdminMode();
                break;
            }else{
                cout << "Admin login failed" << endl;
            }
        }else{
            cout << "INVALID ID! Please try again" << endl; 
        }

        cout << "Press Enter to continue..." << endl;
        cin.ignore();
        cin.get();

    }

    return 0;
}
   