#include "utils/Common.hpp"
#include "utils/Admin.hpp"
#include "utils/User.hpp"
#include "utils/Book.hpp"
#include "utils/Transaction.hpp"

AdminList admin;
UserList user;
BookList book;
TransactionList transaction;

void UserMode();
void AdminMode();

int main(){

    string inputID;
    string inputPassword;

    

    admin.loadAdminFromFile("database/adminDB.txt");
    user.loadUserFromFile("database/userDB.txt");
    book.readBookDB("database/bookDB.txt");
    transaction.readTransactionDB("database/transactionDB.txt");

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

void UserMode(){
    int choice;
    while(1){
        clearScreen();
        cout << "----- USER PORTAL -----" << endl;
        cout << "1. View all Books" << endl;
        cout << "2. Search book by title" << endl;
        cout << "3. Search book by author" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter option: ";
        cin >> choice;

        switch(choice){
            case 1: { // view all book
                book.transformList();
                break;
            }
            case 2: { // search by title
                string searchInput;
                cout << "Enter a title: ";
                cin.ignore();
                getline(cin, searchInput);
                book.searchByTitle(searchInput);
                break;
            }
            case 3: { // search by author
                string searchInput;
                cout << "Enter author name: ";
                cin.ignore();
                getline(cin, searchInput);
                book.searchByAuth(searchInput);
                break;
            }
            case 0: {
                cout << "Exiting..." << endl;
                return;
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
        clearScreen();
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
        cout << "11. View transacions" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter option: ";
        cin >> choice;

        switch(choice){
            case 1: { // Permit a borrow
                string transID, inputItemID, inputUserID;
                cout << "Enter user ID: ";
                cin >> inputUserID;
                cout << "Enter book ID: ";
                cin >> inputItemID;
                cout << "Create transaction ID: ";
                cin >> transID;
                if(book.updateBorrow(inputItemID)){
                    book.saveBook("database/bookDB.txt");
                    transaction.addBorrow(transID, inputItemID, inputUserID, "Borrowing");
                    transaction.saveTransaction("database/transactionDB.txt");
                } else {
                    cout << "operation failed" << endl;
                }
                cin.ignore();
                cin.get();
                break;
            }
            case 2: { // Accept return
                string inputItemID;
                cout << "Enter book ID: ";
                cin >> inputItemID;
                transaction.acceptReturn(inputItemID);
                transaction.saveTransaction("database/transactionDB.txt");
                break;
            }
            case 3: { // View users
                user.displayUsers();
                break;
            }
            case 4: { // Add users
                string inputID, inputName, inputPswd, inputBD;
                cout << "Enter a new user id: ";
                cin >> inputID;
                cout << "Enter a new user name: ";
                cin >> inputName;
                cout << "Enter a new user password: ";
                cin >> inputPswd;
                cout << "Enter a new user birthday: ";
                cin >> inputBD;
                user.add(inputID, inputName, inputPswd, inputBD);
                user.saveUser("database/userDB.txt");
                break;
            }
            case 5: { // Edit users
                string inputId;
                cout << "Enter an ID to select a user: ";
                cin >> inputId;
                user.edit(inputId);
                user.saveUser("database/userDB.txt");
                break;
            }
            case 6: { // Remove users
                string inputId;
                cout << "Input a user id to remove: ";
                cin >> inputId;
                user.removeByID(inputId);
                user.saveUser("database/userDB.txt");
                break;
            }
            case 7: { // View books
                
                book.transformList();
                break;
            }
            case 8: { // Add books
                string inputId, inputTitle, inputAuthName, intputPbDate;
                cout << "Enter book id: ";
                cin >> inputId;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, inputTitle);
                cout << "Enter book author name: ";
                
                getline(cin, inputAuthName);;
                cout << "Enter book publish date: ";
                
                getline(cin, intputPbDate);
                book.add(inputId, inputTitle, inputAuthName, intputPbDate);
                book.saveBook("database/bookDB.txt");
                break;
            }
            case 9: { // edit books
                string inputId;
                cout << "Enter a book id to edit: ";
                cin >> inputId;
                book.edit(inputId);
                book.saveBook("database/bookDB.txt");
                break;
            }
            case 10: { // remove books
                string inputId;
                cout << "Enter a book id to remove: ";
                cin >> inputId;
                book.remove(inputId);
                book.saveBook("database/bookDB.txt");
                break;
            }
            case 11: { // view transaction
                transaction.showTrList();
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