#ifndef __GENRE_H
#define __GENRE_H
#include "Book.h"

class Genre
{
public:
    Genre(const string gname = "");
    ~Genre ();
    Genre (const Genre &genreToCopy);
    void operator=(const Genre &right);
    string getGenreName() const;
    void setGenreName(const string gName);
    void addGenreBook(string name);
    void removeGenreBook(string name);
    void addGenreAuthor(string name, int authorID, string authorName);
    void removeGenreAuthor(string name, int authorID);
    void displayBook();
    bool containBookAuthor(int id, string& authorName);
    Book* containAuthorArr(int id, int& size);
private:
    struct BookNode{
        Book b;
        BookNode* next;
    };
    BookNode* head;
    string genreName;
    BookNode* findBook(string name);
    int compareCaseInsensitiveBook(string s1, string s2);
};
#endif

