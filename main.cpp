#include "utils/Common.hpp"
#include "utils/Admin.hpp"
#include "utils/User.hpp"
#include "utils/Book.hpp"
#include "utils/Transaction.hpp"


string getOsName()
{
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
}

void clearScreen() {
    string osName = getOsName();
    if(osName == "Windows 32-bit") {
        cout << "i am window" << endl;
        system("cls");
    } else if (osName == "Mac OSX") {
        cout << "i am mac" << endl;
        system("clear");
    } else if(osName == "Windows 64-bit") {
        cout << "i am window" << endl;
        system("cls");
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
                break;
            }else{
                cout << "User login failed" << endl;
            }
        }else if(inputID.substr(0,5) == "ADMIN"){
            if(admin.searchAndCompare(inputID, inputPassword)){
                cout << "Admin login success" << endl;
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
   