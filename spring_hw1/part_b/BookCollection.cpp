#include "BookCollection.h"
#include <iostream>
#include <algorithm>

int BookCollection::compareCaseInsensitive(string s1, string s2){
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

    return s1.compare(s2);
}

BookCollection::GenreNode* BookCollection::findGenre(string genreName){
    BookCollection::GenreNode* curr = head;

    while(curr != NULL){
        if (compareCaseInsensitive((curr -> g).getGenreName() , genreName) == 0)
            return curr;
        curr = curr -> next;
    }
    return NULL;
}

BookCollection::BookCollection(){
    head = NULL;
    genreCount = 0;
}

BookCollection::~BookCollection(){
    BookCollection::GenreNode* curr = head;
    while (curr != NULL){
        curr = curr -> next;
        delete head;
        head = curr;
    }
}

BookCollection::BookCollection(const BookCollection& bcToCopy){
    if (bcToCopy.head != NULL){
        head = new BookCollection::GenreNode;
        head -> g = bcToCopy.head -> g;

        BookCollection::GenreNode* newNode = head;

        for (BookCollection::GenreNode* curr = bcToCopy.head -> next;
                curr != NULL; curr = curr -> next){
            newNode -> next = new BookCollection::GenreNode;
            newNode = newNode -> next;
            newNode -> g = curr -> g;
        }
        newNode -> next = NULL;
    }
    else{
        head = NULL;
    }
    genreCount = bcToCopy.genreCount;
}

void BookCollection::operator=(const BookCollection& right){
    BookCollection::GenreNode* rem = head;
    while (rem != NULL){
        rem = rem -> next;
        delete head;
        head = rem;
    }

    if (right.head != NULL){

        //copy all those genres
        head = new BookCollection::GenreNode;
        head -> g = right.head -> g;

        BookCollection::GenreNode* newNode = head;

        for (BookCollection::GenreNode* curr = right.head -> next;
                curr != NULL; curr = curr -> next){
            newNode -> next = new BookCollection::GenreNode;
            newNode = newNode -> next;
            newNode -> g = curr -> g;
        }
        newNode -> next = NULL;
    }
    else{
        head = NULL;
    }
    genreCount = right.genreCount;
}

void BookCollection::addGenre(string genreName){
    BookCollection::GenreNode* check = findGenre(genreName);
    if (check != NULL)
        cout << "THIS GENRE NAME IS ALREADY EXIST" << endl;
    else{
        if (head == NULL){
            head = new BookCollection::GenreNode;
            (head -> g).setGenreName(genreName);
            head -> next = NULL;
        }
        else{
            GenreNode* curr = head;
            while(curr -> next != NULL)
                curr = curr -> next;
            BookCollection::GenreNode* newNode = new BookCollection::GenreNode;
            newNode -> next = curr -> next;
            curr -> next = newNode;
            (newNode -> g).setGenreName(genreName);
        }
        genreCount++;
    }
}

void BookCollection::removeGenre(string genreName){
    BookCollection::GenreNode* check = findGenre(genreName);
    if (check == NULL)
        cout << "THIS GENRE NAME CANNOT BE FOUND" << endl;
    else{
        if (check == head)
            head = head -> next;
        else{
            BookCollection::GenreNode* prev = head;
            while (prev -> next != check)
                prev = prev -> next;
            prev -> next = check -> next;
        }
        check -> next = NULL;
        delete check;
        check = NULL;

        genreCount--;
    }
}

void BookCollection::displayAllGenres() const{
    if (head == NULL)
        cout << "--EMPTY--" << endl;
    else{
        BookCollection::GenreNode* curr = head;
        while (curr != NULL){
            cout << "Genre " << (curr -> g).getGenreName() << endl;
            curr = curr -> next;
        }
    }
}

void BookCollection::addBook(string genreName, string bookName){
    BookCollection::GenreNode* check = findGenre(genreName);
    if (check == NULL)
        cout << "THIS GENRE NAME CANNOT BE FOUND" << endl;
    else
        (check -> g).addGenreBook(bookName);
}

void BookCollection::removeBook(string genreName, string bookName){
    BookCollection::GenreNode* check = findGenre(genreName);
    if (check == NULL)
        cout << "THIS GENRE CANNOT BE FOUND" << endl;
    else
        (check -> g).removeGenreBook(bookName);
}

void BookCollection::addAuthor(string genreName, string bookName, int authorID, string authorName){
    BookCollection::GenreNode* check = findGenre(genreName);
    if (check == NULL)
        cout << "THIS GENRE NAME CANNOT BE FOUND" << endl;
    else
        (check -> g).addGenreAuthor(bookName, authorID, authorName);
}

void BookCollection::removeAuthor(string genreName, string bookName, int authorID){
    BookCollection::GenreNode* check = findGenre(genreName);
    if (check == NULL)
        cout << "THIS GENRE NAME CANNOT BE FOUND" << endl;
    else
        (check -> g).removeGenreAuthor(bookName, authorID);
}

void BookCollection::displayGenre(string genreName){
    BookCollection::GenreNode* check = findGenre(genreName);

    if(check == NULL)
        cout << "-EMPTY-" << endl;
    else{
        cout << "Genre: " << (check -> g).getGenreName() << endl;
        (check -> g).displayBook();
    }
}

bool BookCollection::containAuthorID(int id, string& authorName){
    BookCollection::GenreNode* curr = head;

    while(curr != NULL){
        if ((curr -> g).containBookAuthor(id, authorName))
            return true;
        curr = curr -> next;
    }
    return false;
}

void BookCollection::displayAuthor(int authorID){
    string authorName;
    int size;
    BookCollection::GenreNode* curr = head;
    bool found = containAuthorID(authorID, authorName);
    if (!found)
        cout << "--EMPTY--" << endl;
    else{
        cout << "Author ID: " << authorID << " Author Name: " << authorName << endl;
        while(curr != NULL){
            if ((curr -> g).containBookAuthor(authorID, authorName)){
                cout << "Genre: " << (curr -> g).getGenreName() << endl;
                Book* arr = (curr -> g).containAuthorArr(authorID, size);
                for (int i = 0; i < size; i++){
                    cout << "\t" << "Book: " << arr[i].getName() << endl;
                }
                delete [] arr;
            }
            curr = curr -> next;
        }
    }
}

