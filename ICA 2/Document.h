#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <iostream>

class Document {
    private:
        std::string document;
    public:
        Document(){
            document = "";
        }
        Document(std::string doc){
            document = doc;
        }
        std::string getDoc() const {
            return document;
        }
        void setDoc(std::string doc) {
            document = doc;
        }
        friend std::ostream& operator<<(std::ostream &out, const Document &doc);
        
};

#endif