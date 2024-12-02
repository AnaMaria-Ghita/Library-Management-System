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
     void checkAvailability(){
        if (isAvailable) {
            cout << "Status: Available." << endl;
        }
        else {
            cout << "Status: Not available." << endl;
        }
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


   return 0;
}