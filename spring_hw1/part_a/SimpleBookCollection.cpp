#include "SimpleBookCollection.h"
#include <iostream>
#include <algorithm>

BookCollection::GenreNode* BookCollection::findGenre(string genreName){
    BookCollection::GenreNode* curr = head;

    while(curr != NULL){
        string s1 = (curr -> g).getGenreName();
        string s2 = genreName;

        transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
        transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

        if (s1.compare(s2) == 0)
            return curr;
        curr = curr -> next;
    }
    return NULL;
}

BookCollection::BookCollection(){
    head = NULL;
    genreCount = 0;
    name = "";
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
        (head -> g).setGenreName((bcToCopy.head -> g).getGenreName());

        BookCollection::GenreNode* newNode = head;

        for (BookCollection::GenreNode* curr = bcToCopy.head -> next;
                curr != NULL; curr = curr -> next){
            newNode -> next = new BookCollection::GenreNode;
            newNode = newNode -> next;
            (newNode -> g).setGenreName((curr -> g).getGenreName());
        }
        newNode -> next = NULL;
    }
    else{
        head = NULL;
    }
    genreCount = bcToCopy.genreCount;
}

void BookCollection::operator=(const BookCollection& right){

    //remove all the genres from previous head
    BookCollection::GenreNode* rem = head;
    while (rem != NULL){
        rem = rem -> next;
        delete head;
        head = rem;
    }

    if (right.head != NULL){

        //copy all those genres
        head = new BookCollection::GenreNode;
        (head -> g).setGenreName((right.head -> g).getGenreName());

        BookCollection::GenreNode* newNode = head;

        for (BookCollection::GenreNode* curr = right.head -> next;
                curr != NULL; curr = curr -> next){
            newNode -> next = new BookCollection::GenreNode;
            newNode = newNode -> next;
            (newNode -> g).setGenreName((curr -> g).getGenreName());
        }
        newNode -> next = NULL;
    }
    else{
        head = NULL;
    }
    genreCount = right.genreCount;
}

void BookCollection::displayGenres() const{
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

bool BookCollection::addGenre(const string genreName){
    BookCollection::GenreNode* check = findGenre(genreName);
    if (check != NULL){
        cout << "THIS GENRE NAME IS ALREADY EXIST" << endl;
        return false;
    }
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
        return true;
    }
}

bool BookCollection::removeGenre(const string genreName){
    BookCollection::GenreNode* check = findGenre(genreName);
    if (check == NULL){
        cout << "THIS GENRE NAME CANNOT BE FOUND" << endl;
        return false;
    }
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

        return true;
    }
}

string BookCollection::getName() const{
    return name;
}

void BookCollection::setName(const string bcName){
    name = bcName;
}
