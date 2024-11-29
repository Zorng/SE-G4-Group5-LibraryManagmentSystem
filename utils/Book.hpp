#ifndef Book_hpp
#define Book_hpp
#include "Common.hpp"
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
        Book(string primaryKey, string title, string authorName, string publishedYear, string isbn, string summary, bool vailable=true){
            this->primaryKey=primaryKey;
            this->title=title;
            this->authorName=authorName;
            this->publishedYear=publishedYear;
            this->isbn=isbn;
            this->summary=summary;
            // vailable(true){bookAmount++;}
        }        

        //write a function that show book information (except book summary);
        void showInfo() {
            cout << "Primary Key: " << primaryKey << endl;
            cout << "Title: " << title << endl;
            cout << "Author: " << authorName << endl;
            cout << "Published Year: " << publishedYear << endl;
            cout << "ISBN: " << isbn << endl;
            // cout << "Available: " << (available ? "Yes" : "No") << endl;
        } // Still fixing??

        //write a fucntion that show book summary;
        void showSummary() {
            cout << "Summary: " << summary << endl;
        } //fixing use file??

        //write a function that update the bookAmount when a book is added;
        void saveToFile() {
            ofstream file("books.txt", ios::app);
            if (file.is_open()) {
                file << primaryKey << "," << title << "," << authorName << "," << publishedYear << "," 
                    << isbn << "," << summary << "," /*<< available << endl*/;
                file.close();
            } else {
                cout << "Error!!" << endl;
            }
        }

        //write a function that upadte the borrowedBook when a borrow / return transaction is made;
};

#endif