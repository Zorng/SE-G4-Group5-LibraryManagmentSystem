#include <iostream>
#include "../utils/User.hpp"

int main() {
  UserList userList;

    userList.insertFront("Alice", "001", "pass123", "1995-05-20");
    userList.insertBack("Bob", "002", "pass456", "1993-08-15");
    userList.insertBack("Charlie", "003", "pass789", "1998-01-25");
    userList.printUsers();
    userList.writeUserDB();

  return 0;
}