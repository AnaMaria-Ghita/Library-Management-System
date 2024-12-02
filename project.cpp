#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Book {
private:
    int id;
    char* title;
    char* author;
    char* genre;
    bool isAvailable;
    int numberUsers;
public:
    static int numberBooks;
    //constructors
    Book(const int id, const char* title, const char* author, const char* genre, bool isAvailable): id(id), isAvailable(true), numberUsers(0){
        this->title=new char[strlen(title)+1];
        strcpy(this-> title, title);
       
        this->author=new char[strlen(author)+1];
        strcpy(this-> author, author);

        this->genre=new char[strlen(genre)+1];
        strcpy(this-> genre, genre);

        numberBooks++;
    }
    Book(): id(0), isAvailable(true), title(nullptr), author(nullptr), genre(nullptr), numberUsers(0){

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
        os<<"ID: "<< book.id <<endl;
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
   

   return 0;
}