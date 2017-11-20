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
