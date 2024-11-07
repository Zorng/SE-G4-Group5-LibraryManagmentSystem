# Scope of project

We will create functionalities of the Library Managment System according to the scope of the project. The scope of this project is broken down into multiple evolution starting from *Basic* to *Evolution 1*, *Evolution 2*, ... *Evolution N* (maybe at most Evolution 3). Each evolution can only be developed only if the previous evolution is completed. We start from building the *Basic* evolution.

## Basic

**<u>NOTE</u>: In this context, item is refered as book and vice versa. So, item database is book database**<br>
Requiremnts are listed below:<br>
- The system can only be used after logged in.
- The system has a user database that store username and user password, user's ID and user's currently borrowing books.
- The system has a item (in this case the item is book) database that stores item's unique ID, item's information (book title, author, category, ISBN ...), current number of item available.
- The system has a transaction database that is updated each time a transaction is made. Each transaction contain: transaction ID, user ID, time of transaction, type of transaction (borrow or return).
- A user can log in from user mode by input username and password registerd in user database.
- A logged in user can:
  - View all books in book database. Books are displayed in lexical order
  - search a book by name ***or*** by author's name. The searched book displays its information an its number available.
  - borrow a book by inputting the book's ID (item's ID)
  - return a book by inputting the book's ID (item's ID)
  - see his or her own transaction history. Transactions are shown by the most current transaction on top and the least current transaction at the bottom.
- An admin can log in from admin mode by inputting adminUsername and adminPassword
- A logged in admin can:
  - View all books in book database. Books are displayed in lexical order
  - search a book by name ***or*** by author's name. The searched book displays its information an its number available.
  - Manipulate book in book database (add, edit, remove)
  - View all users in user database. Users are displayed by order of userID
  - Manipulate user in user database (add, edit, remove)
  - View transaction database. Transactions are shown by the most current transaction on top and the least.
  
## Evolution 1
- Add new attribute called *category* in book database
- Add a new mode for guest. In this mode, the system can be used without loggin in, but with limitation.
- In guest mode, a guest can:
  - View all books in book database. Books are displayed in lexical order
  - search a book by name ***or*** by author's name. The searched book displays its information an its number available.
  - View books by category. Books are displayed in lexical order
- Add new feature for user:
  - View books by category. Books are displayed in lexical order
- Add new feature for admin:
  - View books by category. Books are displayed in lexical order
  
<br>
<br>
<br>
To be continued ...