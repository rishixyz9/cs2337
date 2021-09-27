#include "File.h"
#include <iostream>

std::ostream& operator<<(std::ostream &out, File &f){
    //f.pathname << " " << f.filename;
    out << f.getDoc();
    return out;
}