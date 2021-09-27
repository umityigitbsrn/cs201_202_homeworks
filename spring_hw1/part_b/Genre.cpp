#include "Genre.h"
#include <algorithm>
#include <iostream>

int Genre::compareCaseInsensitiveBook(string s1, string s2){
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

    return s1.compare(s2);
}

Genre::BookNode* Genre::findBook(string name){
    Genre::BookNode* curr = head;

    while(curr != NULL){
        if (compareCaseInsensitiveBook((curr -> b).getName(), name) == 0)
            return curr;
        curr = curr -> next;
    }
    return NULL;
}

Genre::Genre(const string gname){
    head = NULL;
    genreName = gname;
}

Genre::~Genre(){
    Genre::BookNode* curr = head;
    while(curr != NULL){
        curr = curr -> next;
        delete head;
        head = curr;
    }
}

Genre::Genre(const Genre &genreToCopy){
    if (genreToCopy.head != NULL){
        head = new Genre::BookNode;
        head -> b = genreToCopy.head -> b;

        Genre::BookNode* newNode = head;
        for (Genre::BookNode* curr = genreToCopy.head -> next; curr != NULL;
            curr = curr -> next){
                //diff
            newNode = newNode -> next;
            newNode = new Genre::BookNode;
            newNode -> b = curr -> b;
        }
        newNode -> next = NULL;
    }
    else
        head = NULL;
    genreName = genreToCopy.genreName;
}

void Genre::operator=(const Genre& right){
   Genre::BookNode* rem = head;
        while (rem != NULL){
            rem = rem -> next;
            delete head;
            head = rem;
        }
    if (right.head != NULL){

        //copy all those authors
        head = new Genre::BookNode;
        head -> b = right.head -> b;

        Genre::BookNode* newNode = head;
        for (Genre::BookNode* curr = right.head -> next; curr != NULL;
            curr = curr -> next){
                //diff
            newNode -> next = new Genre::BookNode;
            newNode = newNode -> next;
            newNode -> b = curr -> b;
        }
        newNode -> next = NULL;
    }
    else
        head = NULL;

    genreName = right.genreName;
}

string Genre::getGenreName() const{
    return genreName;
}

void Genre::setGenreName(const string gName){
    genreName = gName;
}

void Genre::addGenreBook(string name){
    Genre::BookNode* check = findBook(name);
    if (check != NULL){
        cout << "THIS BOOK NAME IS ALREADY EXIST" << endl;
    }
    else{
        if (head == NULL){
            head = new Genre::BookNode;
            (head -> b).setName(name);
            head -> next = NULL;
        }
        else{
            BookNode* curr = head;
            while(curr -> next != NULL)
                curr = curr -> next;
            Genre::BookNode* newNode = new Genre::BookNode;
            newNode -> next = curr -> next;
            curr -> next = newNode;
            (newNode -> b).setName(name);
        }
    }
}

void Genre::removeGenreBook(string name){
    Genre::BookNode* check = findBook(name);
    if (check == NULL){
        cout << "THIS BOOK NAME CANNOT BE FOUND" << endl;
    }
    else{
        if (check == head)
            head = head -> next;
        else{
            Genre::BookNode* prev = head;
            while (prev -> next != check)
                prev = prev -> next;
            prev -> next = check -> next;
        }
        check -> next = NULL;
        delete check;
        check = NULL;
    }
}

void Genre::addGenreAuthor(string name, int authorID, string authorName){
    Genre::BookNode* check = findBook(name);

    if (check == NULL)
        cout << "THIS BOOK CANNOT BE FOUND" << endl;
    else
        (check -> b).addAuthor(authorID, authorName);
}

void Genre::removeGenreAuthor(string name, int authorID){
    Genre::BookNode* check = findBook(name);

    if (check == NULL)
        cout << "THIS BOOK CANNOT BE FOUND" << endl;
    else
        (check -> b).removeAuthor(authorID);
}

void Genre::displayBook(){
    Genre::BookNode* curr = head;

    if (head == NULL)
        cout << "-EMPTY-" << endl;
    else{
        while(curr != NULL){
            cout << "Book: " << (curr -> b).getName() << endl;
            (curr -> b).displayAuthorsTab();
            curr = curr -> next;
        }
    }
}

bool Genre::containBookAuthor(int id, string& authorName){
    Genre::BookNode* curr = head;

    while(curr != NULL){
        if ((curr -> b).containAuthor(id, authorName))
            return true;
        curr = curr -> next;
    }
    return false;
}

Book* Genre::containAuthorArr(int id, int& size){
    int arrSize = 1;
    Book* arr = new Book[arrSize];
    Genre::BookNode* curr = head;
    int count = 0;

    while(curr != NULL){
        if ((curr -> b).containAuthor(id)){
            if (count + 1 == arrSize){
                Book* temp = new Book[arrSize * 2];
                for (int i = 0; i < arrSize; i++)
                    temp[i] = arr[i];
                delete []arr;
                arr = temp;
                arrSize *= 2;
            }
            arr[count] = (curr -> b);
            count++;
        }
        curr = curr -> next;
    }

    size = count;
    return arr;
}
