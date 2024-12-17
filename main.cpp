#include "utils/User.hpp"

int main() {
    UserList usrList;
    usrList.loadUserFromFile("database/userDB.txt");
    usrList.insertBack("abcd", "1234", "12-12-12");
    usrList.insertBack("umah", "4444", "12-12-12");
    usrList.insertBack("hook", "2222", "12-12-12");
    usrList.printUsers();
    usrList.writeUserDB();
    return 0;
}