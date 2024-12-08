#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Book {
private:
    int bookID;
    char* title;
    char* author;
    char* genre;
    bool isAvailable;
    int numberUsers;
public:
    static int numberBooks;
    //constructors
    Book(const int bookID, const char* title, const char* author, const char* genre, bool isAvailable): bookID(bookID), isAvailable(true), numberUsers(0){
        this->title=new char[strlen(title)+1];
        strcpy(this-> title, title);
       
        this->author=new char[strlen(author)+1];
        strcpy(this-> author, author);

        this->genre=new char[strlen(genre)+1];
        strcpy(this-> genre, genre);

        numberBooks++;
    }
    Book(): bookID(0), isAvailable(true), title(nullptr), author(nullptr), genre(nullptr), numberUsers(0){

        numberBooks++;
    }
    //destructor
    ~Book(){
        delete[] title;
        delete[] author;
        delete[] genre;
    }

    //constructor de afisare
    friend ostream& operator<<(ostream& os, Book& book){
        os<<"ID: "<< book.bookID <<endl;
        os<<"Title: "<<book.title<<endl;
        os<<"Author: "<<book.author<<endl;
        os<<"Genre: "<<book.genre<<endl;
        os<<"Status: ";
        if(book.isAvailable){
            os<<"Available"<<endl;
        }
        else{
            os<<"Not available"<<endl;
        }
        os<<"Number of users: "<<book.numberUsers<<endl;

        return os;
    }

    friend istream& operator>>(istream& is, Book& book){
        cout << "Write the new genre of the book: ";
        is>>book.genre;

        return is;
    }

    //methods
     bool checkAvailability() const { 

        return isAvailable; 
     }

    void markBorrowed(){
        isAvailable=false;
        numberUsers++;
    }
    void markReturned(){
        isAvailable=true; 
    }
    void checkNumberUsers(){
    cout << "Number of users: " << numberUsers << endl;
    }

    int getBookID() const { 
        return bookID;
    }

};


class User{
private:
    int userID;
    char* fName;
    char* lName;
    int age;
    int numberBooksBorr;
    int* booksBorr;
public:
    User(int userID, const char* fName, const char* lName, int age, int numberBooksBorr, int* booksBorr): userID(userID), age(age), numberBooksBorr(numberBooksBorr){
        this->fName=new char[strlen(fName)+1];
        strcpy(this-> fName, fName);

        this->lName=new char[strlen(lName)+1];
        strcpy(this-> lName, lName);

        this->booksBorr=new int[numberBooksBorr];
        for (int i = 0; i < numberBooksBorr; i++)
        {
            this->booksBorr[i]=booksBorr[i];
        }
    }
    User():userID(0), fName(nullptr), lName(nullptr), age(0), numberBooksBorr(0), booksBorr(nullptr){

    } 
    ~User(){
        delete[] fName;
        delete[] lName;
        delete[] booksBorr;
    }

    //methods
    void borrBook(int bookID){
       
        int* temp = new int[numberBooksBorr + 1];

        for (int i = 0; i < numberBooksBorr; i++) {
            temp[i] = booksBorr[i];
        }

        temp[numberBooksBorr] = bookID;

        delete[] booksBorr;
        booksBorr = temp;

        numberBooksBorr++;

        cout << "Book ID " << bookID << " borrowed by " << fName << " " << lName << "." << endl;
    }
    void returnedBook(int bookID){
        int* temp = new int[numberBooksBorr-1];

        for (int i = 0; i < numberBooksBorr; i++)
        {
            if(booksBorr[i]!=bookID){
                temp[i] = booksBorr[i];
            }
        }

        delete[] booksBorr;
        booksBorr = temp;
        
        numberBooksBorr--;

        cout << "Book ID " << bookID << " returned by " << fName << " " << lName << "." << endl;
    }

     //constructor de afisare
    friend ostream& operator<<(ostream& os, User& user){
        os<<"User ID: "<<user.userID<<endl;
        os<<"First name: "<< user.fName <<endl;
        os<<"Last name: "<<user.lName<<endl;
        os<<"Age: "<<user.age<<endl;
        os<<"Number of books borrowed: " <<user.numberBooksBorr<<endl;
        os<<"Books borrowed: ";
        for (int i = 0; i < user.numberBooksBorr; i++)
        {
            os<<user.booksBorr[i] << ", ";
        }

        return os;
    }

      friend istream& operator>>(istream& is, User& user){
        cout <<"Write the new first name: ";
        delete[] user.fName;

        char temp[100];
        is>>temp;

        user.fName = new char [strlen(temp)+1];
        strcpy(user.fName, temp);

        return is;
    }


};

class Library {
private:
    Book** books;
    User** users;
    int numberUsers;
    int numberBooks;
public:
    Library() {
        this->books = nullptr;
        this->users = nullptr;
        this->numberBooks = 0;
        this->numberUsers = 0;
    }
    ~Library() {
        delete[] books;
        delete[] users;
    }

    void addBook(const int id, const char* title, const char* author, const char* genre, bool avail) {
        Book** newBooks = new Book * [numberBooks + 1];

        for (int i = 0; i < numberBooks; i++) {
            newBooks[i] = books[i];
        }

        newBooks[numberBooks] = new Book(id, title, author, genre, avail);

        delete[] books;
        books = newBooks;
        numberBooks++;
    }

    void displayBooks() const {
        for (int i = 0; i < numberBooks; i++) {
            std::cout << *(books[i]);
            std::cout << "-----------------" << endl;
        }
    }

    void searchBookByID(int id) const {
        for (int i = 0; i < numberBooks; i++) {
            if (books[i]->getBookID() == id) {
                std::cout << *(books[i]);
                return;
            }
        }
        cout << "Book with ID " << id << " was not found." << endl;
    }

    void borrowBook(int id) {
        for (int i = 0; i < numberBooks; i++) {
            if (books[i]->getBookID() == id) {
                if (books[i]->checkAvailability()) {
                    books[i]->markBorrowed();
                    std::cout << "Book with ID " << id << " has been borrowed." << endl;
                    numberUsers++;
                }
                else {
                    std::cout << "Book with ID " << id << " is already borrowed." << endl;
                }
                return;
            }
        }
        cout << "Book with ID " << id << " was not found." << endl;
    }

    void returnBook(int id) {
        for (int i = 0; i < numberBooks; i++) {
            if (books[i]->getBookID() == id) {
                if (!books[i]->checkAvailability()) {
                    books[i]->markReturned();
                    std::cout << "Book with ID " << id << " has been returned." << endl;
                }
                else {
                    std::cout << "Book with ID " << id << " was not borrowed." << endl;
                }
                return;
            }
        }
        cout << "Book with ID " << id << " not found." << endl;
    }
};

int Book::numberBooks = 0;

int main(){
   Book b1(100, "Alice's Adventures in Wonderland", "Lewis Carrol", "Fantasy", true);
   cout << b1 << endl;
   cin >> b1;
   cout << b1 << endl << endl;

   b1.checkAvailability();
   b1.checkNumberUsers();

   b1.markBorrowed();
   b1.checkAvailability();
   b1.checkNumberUsers();
   
   //User(int id, const char* fname, const char* lName, int age, int numberBooksBorr, int* booksBorr)
    int borrowedBooks[] = { 101, 102, 103 };
    User user1(1, "Ana", "Ghita", 25, 3, borrowedBooks);
    cout << user1 << endl;
    cin >> user1;

    cout << endl;
    user1.borrBook(100);
    cout << user1 << endl;
    user1.returnedBook(100);
    cout << user1 << endl;


    Library lib;
    lib.addBook(101, "Harry Potter and the philosopher's stone", "J. K. Rowling", "fantasy", true);
    lib.addBook(102, "1984", "George Orwell", "dystopian fiction", true);
    lib.addBook(103, "The Great Gatsby", "F. Scott Fitzgerald", "action", true);
    lib.displayBooks();

    lib.borrowBook(102);

    lib.borrowBook(102);

    lib.returnBook(102);

    lib.searchBookByID(103);

   return 0;
}