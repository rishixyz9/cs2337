#include "EMail.h"
#include "Document.h"
#include <string>

std::ostream& operator<<(std::ostream &out, const EMail& email){
	out << email.sender << "\n" << email.getDoc() << "\n" << email.recipient;
	return out;
}