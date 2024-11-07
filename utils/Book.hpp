#include <iostream>
#include <string>
using namespace std;

class Book {
    private:
        static int bookAmount;
        static int borrowedAmount;
        //currently available book = bookAmount - borrowedBook;
        string primaryKey;
        string title;
        string authorName;
        string publishedYear;
        string isbn;
        string summary;
        bool vailable; 
    public:
        //create a contructor for the class;

        //write a function that show book information (except book summary);

        //write a fucntion that show book summary;

        //write a function that update the bookAmount when a book is added;

        //write a function that upadte the borrowedBook when a borrow / return transaction is made;
};