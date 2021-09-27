#include "Document.h"
#include <iostream>
#include <string>

std::ostream& operator<<(std::ostream &out, const Document &doc){
    out << doc.document;
    return out;
}