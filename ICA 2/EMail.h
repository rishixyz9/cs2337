#ifndef EMail_H
#define EMail_H

#include "Document.h"
#include <string>

class EMail: public Document{
private:
    std::string sender;
    std::string recipient;
    std::string title;

public:
    //EMail():Document(){}
    Email(){
        sender="";
        recipient="";
        title="";
    }

    EMail(std::string docu, std::string temp1, std::string temp2, std::string temp3) : Document(docu){
        sender = temp1;
        recipient = temp2;
        title = temp3;
    }

    std::string getSender(){return sender;}
    std::string getRecipient(){return recipient;}
    std::string getTitle(){return title;}

    friend std::ostream& operator<<(std::ostream &out, const EMail& email);

};

#endif