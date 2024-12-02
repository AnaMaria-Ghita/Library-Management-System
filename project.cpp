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
    //constructors
    Book(const int id, const char* title, const char* author, char* genre, bool isAvailable): id(id), isAvailable(true){
        this->title=new char[strlen(title)+1];
        strcpy(this-> title, title);
       
        this->author=new char[strlen(author)+1];
        strcpy(this-> author, author);

        this->genre=new char[strlen(genre)+1];
        strcpy(this-> genre, genre);

        numberBooks++;
    }
    Book(): id(0), isAvailable(true){
        this->title=new char[strlen("NA")+1];
        strcpy(this-> title, "NA");
       
        this->author=new char[strlen("NA")+1];
        strcpy(this-> author, "NA");

        this->genre=new char[strlen("NA")+1];
        strcpy(this-> genre, "NA");

        numberBooks++;
    }
    //destructor
    ~Book(){
        delete[] title;
        delete[] author;
        delete[] genre;
    }
};

int Book::numberBooks = 0;
int main(){


    return 0;
}