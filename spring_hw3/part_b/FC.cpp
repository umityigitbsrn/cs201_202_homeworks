#include "FC.h"

FC::FC()
{
    size = 1;
    films = new Film[size];
    noOfFilms = 0;
}

FC::FC(const FC &fcToCopy)
{
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
        {
            delete []films;
        }

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
        if (films[i].getFilmTitle().compare(fTitle) == 0 &&
            films[i].getFilmDirector().compare(fDirector) == 0)
            found = true;
    }

    if (!found)
    {
        Film film(fTitle, fDirector, fYear, fDuration);
        films[noOfFilms] = film;
        noOfFilms++;
    }

    if (noOfFilms >= (size / 2))
    {
        Film* tmp = new Film[size * 2];

        for (int i = 0; i < noOfFilms; i++)
            tmp[i] = films[i];

        if (films != NULL)
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
        if (films[i].getFilmDirector().compare(fDirector) == 0 &&
            films[i].getFilmTitle().compare(fTitle) == 0)
        {
            found = true;
            loc = i;
        }
    }

    if (found)
    {
        for(unsigned int i = loc; i < noOfFilms; i++)
        {
            films[i] = films[i + 1];
        }
        noOfFilms--;
    }

    if (noOfFilms < (size / 2))
    {
        Film* tmp = new Film[size / 2];

        for (int i = 0; i < noOfFilms; i++)
            tmp[i] = films[i];

        delete []films;

        films = tmp;

        size = size / 2;
    }

    return found;
}

unsigned int FC::getFilms(Film *&allFilms) const
{
    allFilms = new Film[noOfFilms];

    for(unsigned int i = 0; i < noOfFilms; i++)
        allFilms[i] = films[i];

    return noOfFilms;
}

bool FC::addActor(const string fTitle, const string fDirector,
                  const string aName, const string aBirthPlace,
                  const unsigned int aBirthYear)
{
    bool foundFilm = false;
    int locFilm;
    bool foundActor = false;

    for (unsigned int i = 0; i < noOfFilms && !foundFilm; i++)
    {
        if (films[i].getFilmDirector().compare(fDirector) == 0 &&
            films[i].getFilmTitle().compare(fTitle) == 0)
        {
            foundFilm = true;
            locFilm = i;
        }
    }

    if (!foundFilm)
        return false;

    for (unsigned int i = 0; i < films[locFilm].noOfActors && !foundActor; i++)
    {
        if (films[locFilm].actors[i].getName().compare(aName) == 0)
            foundActor = true;
    }

    if (foundActor)
        return false;

    if (films[locFilm].noOfActors >= (films[locFilm].size / 2))
    {
        Actor* tmp = new Actor[films[locFilm].size * 2];

        for (int i = 0; i < films[locFilm].noOfActors; i++)
        {
            tmp[i] = films[locFilm].actors[i];
        }

        delete []films[locFilm].actors;

        films[locFilm].actors = tmp;

        (films[locFilm].size) = (films[locFilm].size) * 2;
    }

    Actor a(aName, aBirthPlace, aBirthYear);
    films[locFilm].actors[films[locFilm].noOfActors] = a;
    films[locFilm].noOfActors++;

    return true;
}

bool FC::removeActors(const string fTitle, const string fDirector)
{
    bool found = false;
    int loc;

    for (unsigned int i = 0; i < noOfFilms && !found; i++)
    {
        if (films[i].getFilmTitle().compare(fTitle) == 0 &&
            films[i].getFilmDirector().compare(fDirector) == 0)
        {
            found = true;
            loc = i;
        }
    }

    if (!found)
        return false;

    if (films[loc].noOfActors != 0)
    {
        delete []films[loc].actors;
        films[loc].size = 1;
        films[loc].actors = new Actor[films[loc].size];
        films[loc].noOfActors = 0;
        return true;
    }

    return false;
}

unsigned int FC::calculateAverageDuration() const
{
    unsigned int total = 0;

    for (unsigned int i = 0; i < noOfFilms; i++)
    {
        total += films[i].getFilmDuration();
    }

    return total/noOfFilms;
}
