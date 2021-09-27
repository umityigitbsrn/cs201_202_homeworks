#include "SimpleGenre.h"

Genre::Genre(const string gname){
    genreName = gname;
}

Genre::~Genre(){}

Genre::Genre(const Genre &genreToCopy){
    genreName = genreToCopy.genreName;
}

void Genre::operator=(const Genre &right){
    genreName = right.genreName;
}

string Genre::getGenreName() const{
    return genreName;
}

void Genre::setGenreName(const string gName){
    genreName = gName;
}
