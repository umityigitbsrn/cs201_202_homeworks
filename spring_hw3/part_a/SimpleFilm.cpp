#include "SimpleFilm.h"

Film::Film(const string fTitle, const string fDirector,
                       const unsigned int fYear,
                       const unsigned int fDuration)
{
    title = fTitle;
    director = fDirector;
    year = fYear;
    duration = fDuration;
}

Film::Film(const Film &fToCopy)
{
    title = fToCopy.getTitle();
    director = fToCopy.getDirector();
    year = fToCopy.getYear();
    duration = fToCopy.getDuration();
}

Film::~Film(){}

void Film::operator=(const Film &right)
{
    if (this != &right)
    {
        title = right.getTitle();
        director = right.getDirector();
        year = right.getYear();
        duration = right.getDuration();
    }
}

string Film::getTitle() const
{
    return title;
}

string Film::getDirector() const
{
    return director;
}

unsigned int Film::getYear() const
{
    return year;
}

unsigned int Film::getDuration() const
{
    return duration;
}

ostream& operator<<(ostream& out, const Film& f)
{
    out << f.getTitle() << ", " << f.getYear() << ", "
        << f.getDirector() << ", " << f.getDuration() << " min" << endl;
    return out;
}
