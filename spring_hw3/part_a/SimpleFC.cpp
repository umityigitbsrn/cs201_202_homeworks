#include "SimpleFC.h"

FC::FC()
{
    size = 1;
    films = new Film[size];
    noOfFilms = 0;
}

FC::FC(const FC &fcToCopy)
{
    if (films != NULL)
    {
        delete []films;
    }

    films = new Film[fcToCopy.size];

    for (unsigned int i = 0; i < fcToCopy.noOfFilms; i++)
    {
        films[i] = fcToCopy.films[i];
    }

    size = fcToCopy.size;
    noOfFilms = fcToCopy.noOfFilms;
}

FC::~FC()
{
    delete []films;
}

void FC::operator=(const FC &right)
{
    if (this != &right)
    {
        if (films != NULL)
            delete []films;

        films = new Film[right.size];

        for (unsigned int i = 0; i < right.noOfFilms; i++)
        {
            films[i] = right.films[i];
        }

        size = right.size;
        noOfFilms = right.noOfFilms;
    }
}

bool FC::addFilm(const string fTitle, const string fDirector,
                 const unsigned int fYear,
                 const unsigned int fDuration)
{
    bool found = false;

    for (unsigned int i = 0; i < noOfFilms && !found; i++)
    {
        if (films[i].getDirector().compare(fDirector) == 0 &&
            films[i].getTitle().compare(fTitle) == 0)
            found = true;
    }

    if (!found)
    {
        Film film(fTitle, fDirector, fYear, fDuration);
        films[noOfFilms] = film;
        noOfFilms++;
    }

    if (noOfFilms >= (size/2))
    {
        Film* tmp = new Film[size * 2];

        for (int i = 0; i < noOfFilms; i++)
            tmp[i] = films[i];

        delete []films;

        films = tmp;

        size = size * 2;
    }

    return !found;
}

bool FC::removeFilm(const string fTitle, const string fDirector)
{
    bool found = false;
    unsigned int loc = 0;

    for (unsigned int i = 0; i < noOfFilms && !found; i++)
    {
        if (films[i].getDirector().compare(fDirector) == 0 &&
            films[i].getTitle().compare(fTitle) == 0)
        {
            found = true;
            loc = i;
        }
    }

    if (found)
    {
        for(unsigned int i = loc; i < noOfFilms; i++)
            films[i] = films[i + 1];
        noOfFilms--;
    }

    if (noOfFilms < (size/2))
    {
        Film* tmp = new Film[size / 2];

        for (int i = 0; i < noOfFilms; i++)
            tmp[i] = films[i];

        delete []films;

       films = tmp;
       size = size/2;
    }

    return found;
}

unsigned int FC::getFilms(Film *&allFilms) const
{
    allFilms = new Film[size];

    for(unsigned int i = 0; i < noOfFilms; i++)
        allFilms[i] = films[i];

    return noOfFilms;
}

