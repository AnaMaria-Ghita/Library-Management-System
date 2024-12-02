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
public:
    static int numberBooks;
    static int numberUsers;
    //constructors
    Book(const int id, const char* title, const char* author, const char* genre, bool isAvailable): id(id), isAvailable(true){
        this->title=new char[strlen(title)+1];
        strcpy(this-> title, title);
       
        this->author=new char[strlen(author)+1];
        strcpy(this-> author, author);

        this->genre=new char[strlen(genre)+1];
        strcpy(this-> genre, genre);

        numberBooks++;
    }
    Book(): id(0), isAvailable(true), title(nullptr), author(nullptr), genre(nullptr){

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

        return os;
    }

    friend istream& operator>>(istream& is, Book& book){
        cout << "Write the new genre of the book: ";
        is>>book.genre;

        return is;
    }

    //methods
     bool checkAvailability(){
     return isAvailable;
    }
    void markBorrowed(){
        isAvailable=false;
    }
    void markReturned(){
        isAvailable=true; 
    }

};

int Book::numberBooks = 0;
int Book::numberUsers = 0;

int main(){
    Book b1(100, "Alice's Adventures in Wonderland", "Lewis Carrol", "Fantasy", true );
    cout << b1 << endl;
    cin>>b1;
    cout << b1;

    return 0;
}