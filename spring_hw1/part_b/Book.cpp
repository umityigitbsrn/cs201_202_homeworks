#include "Book.h"
#include <iostream>

Book::AuthorNode* Book::findAuthor(int id){
    Book::AuthorNode* curr = head;

    while(curr != NULL){
        if ((curr -> a).getID() == id)
            return curr;
        curr = curr -> next;
    }
    return NULL;
}

Book::Book(){
    head = NULL;
    name = "";
}

Book::Book(const string name){
    head = NULL;
    this -> name = name;
}

Book::~Book(){
    Book::AuthorNode* curr = head;
    while (curr != NULL){
        curr = curr -> next;
        delete head;
        head = curr;
    }
}

Book::Book(const Book& bookToCopy){
    if (bookToCopy.head != NULL){
        head = new Book::AuthorNode;
        (head -> a).setName((bookToCopy.head -> a).getName());
        (head -> a).setID((bookToCopy.head -> a).getID());

        Book::AuthorNode* newNode = head;

        for (Book::AuthorNode* curr = bookToCopy.head -> next;
                curr != NULL; curr = curr -> next){
            newNode -> next = new Book::AuthorNode;
            newNode = newNode -> next;
            (newNode -> a).setID((curr -> a).getID());
            (newNode -> a).setName((curr -> a).getName());
        }
        newNode -> next = NULL;
    }
    else{
        head = NULL;
    }
    name = bookToCopy.name;
}

void Book::operator=(const Book& right){
    Book::AuthorNode* rem = head;
        while (rem != NULL){
            rem = rem -> next;
            delete head;
            head = rem;
        }

    if (right.head != NULL){

        //remove all the authors from previous head

        //copy all those authors
        head = new Book::AuthorNode;
        (head -> a).setName((right.head -> a).getName());
        (head -> a).setID((right.head -> a).getID());

        Book::AuthorNode* newNode = head;

        for (Book::AuthorNode* curr = right.head -> next;
                curr != NULL; curr = curr -> next){
            newNode -> next = new Book::AuthorNode;
            newNode = newNode -> next;
            (newNode -> a).setID((curr -> a).getID());
            (newNode -> a).setName((curr -> a).getName());
        }
        newNode -> next = NULL;
    }
    else{
        head = NULL;
    }
    name = right.name;
}

string Book::getName() const{
    return name;
}

void Book::setName(const string bookName){
    name = bookName;
}

bool Book::addAuthor(const int id, const string name){
    Book::AuthorNode* check = findAuthor(id);
    if (check != NULL){
        cout << "THIS AUTHOR ID IS ALREADY EXIST" << endl;
        return false;
    }
    else{
        if (head == NULL){
            head = new Book::AuthorNode;
            (head -> a).setName(name);
            (head -> a).setID(id);
            head -> next = NULL;
        }
        else{
            AuthorNode* curr = head;
            while(curr -> next != NULL)
                curr = curr -> next;

            Book::AuthorNode* newNode = new Book::AuthorNode;
            newNode -> next = curr -> next;
            curr -> next = newNode;
            (newNode -> a).setName(name);
            (newNode -> a).setID(id);
        }
        return true;
    }
}

bool Book::removeAuthor(const int id){
    Book::AuthorNode* check = findAuthor(id);
    if (check == NULL){
        cout << "THIS AUTHOR ID CANNOT BE FOUND" << endl;
        return false;
    }
    else{
        if (check == head)
            head = head -> next;
        else{
            Book::AuthorNode* prev = head;
            while (prev -> next != check)
                prev = prev -> next;
            prev -> next = check -> next;
        }
        check -> next = NULL;
        delete check;
        check = NULL;

        return true;
    }
}

void Book::displayAuthorsTab() const{
    if (head == NULL)
        cout << "-EMPTY-" << endl;
    else{
        Book::AuthorNode* curr = head;

        while (curr != NULL){
            cout << "\t" << "Author ID: " << (curr -> a).getID() << " Author Name: " <<
                    (curr -> a).getName() << endl;
            curr = curr -> next;
        }
    }
}

void Book::displayAuthors() const{
    if (head == NULL)
        cout << "-EMPTY-" << endl;
    else{
        Book::AuthorNode* curr = head;

        while (curr != NULL){
            cout << "Author ID: " << (curr -> a).getID() << " Author Name: " <<
                    (curr -> a).getName() << endl;
            curr = curr -> next;
        }
    }
}

bool Book::containAuthor(int id, string& authorName){
    Book::AuthorNode* check = findAuthor(id);
    if(check == NULL)
        return false;
    else{
        authorName = (check -> a).getName();
        return true;
    }
}

bool Book::containAuthor(int id){
    Book::AuthorNode* check = findAuthor(id);

    if (check == NULL)
        return false;
    else
        return true;
}
