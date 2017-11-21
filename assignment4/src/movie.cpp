#include "movie.h"

movie::movie()
    :id(0),name(""),release_date("")
{
}

movie::~movie()
{
}

movie::movie(int i, string n, string r_d)
    :id(i),name(n),release_date(r_d)
{
}

int movie::get_id()
{
    return id;
}

string movie::get_name()
{
    return name;
}

void movie::set_content(string c)
{
    this->content = c;
}

ostream & operator <<(ostream & os,movie & mov) {
    os << "Title: " << mov.get_name() << " Release Date: " << mov.release_date << " Description: " << mov.get_content() << endl;
    return os;
}

