#include "Film.h"

Film::Film(const string fTitle, const string fDirector,
           const unsigned int fYear,
           const unsigned int fDuration)
{
    title = fTitle;
    director = fDirector;
    year = fYear;
    duration = fDuration;

    size = 1;
    actors = new Actor[size];
    noOfActors = 0;
}

Film::Film(const Film &fToCopy)
{
    title = fToCopy.getFilmTitle();
    director = fToCopy.getFilmDirector();
    year = fToCopy.getFilmYear();
    duration = fToCopy.getFilmDuration();

    if (actors != NULL)
    {
        delete []actors;
    }

    actors = new Actor[fToCopy.size];

    for (unsigned int i = 0; i < fToCopy.noOfActors; i++)
    {
        actors[i] = fToCopy.actors[i];
    }

    size = fToCopy.size;
    noOfActors = fToCopy.noOfActors;
}

Film::~Film()
{
    delete []actors;
}

void Film::operator=(const Film& right)
{
    if (this != &right)
    {
        title = right.getFilmTitle();
        director = right.getFilmDirector();
        year = right.getFilmYear();
        duration = right.getFilmDuration();

        if (actors != NULL)
        {
            delete []actors;
        }

        size = right.size;
        actors = new Actor[size];

        for (unsigned int i = 0; i < right.noOfActors; i++)
        {
            actors[i] = right.actors[i];
        }

        noOfActors = right.noOfActors;
    }
}

string Film::getFilmTitle() const
{
    return title;
}

string Film::getFilmDirector() const
{
    return director;
}

unsigned int Film::getFilmYear() const
{
    return year;
}

unsigned int Film::getFilmDuration() const
{
    return duration;
}

unsigned int Film::calculateAverageActorAge() const
{
    unsigned int total = 0;

    if (noOfActors == 0)
    {
        return 0;
    }

    for (unsigned int i = 0; i < noOfActors; i++)
    {
        total += (2019 - actors[i].getBirthYear());
    }

    return total/noOfActors;
}

ostream& operator<<(ostream& out, const Film& f)
{
    out << f.getFilmTitle() << ", " << f.getFilmDirector() << ", " <<
            f.getFilmYear() << ", " << f.getFilmDuration() << endl;

    for (unsigned int i = 0; i < f.noOfActors; i++)
    {
        out << "\t" << f.actors[i] << endl;
    }
    return out;
}
