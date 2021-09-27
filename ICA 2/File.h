#ifndef FILE_H
#define FILE_H
#include "Document.h"
#include <iostream>
#include <string>

class File : public Document {
    public: 
        File(){
            pathname = "";
            filename = "";
        }
        File(std::string doc, std::string pname, std::string fname) : Document(doc){
            pathname = pname;
            filename = fname;
        }
        std::string getPath() const{
            return pathname;
        }
        std::string getFile() const{
            return filename;
        }
        void setPath(std::string p){
            pathname = p;
        }
        void setFile(std::string f){
            filename = f;
        }
        friend std::ostream& operator<<(std::ostream &out, File &f);
    private:
        std::string pathname;
        std::string filename;
};
#endif