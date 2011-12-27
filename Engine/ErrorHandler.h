#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <exception>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>

class GameException : public std::exception {
public :
    std::string string;

    GameException(std::string str) throw()
    : string(str)  {}
    ~GameException() throw() {}

    virtual const char * what() throw()
    { return string.c_str(); }
};

#define _str(x) #x
#define G_THROW(s) \
    { \
        std::stringstream __ss; \
        __ss << "Error (" << __FILE__ << ", " << __LINE__ << ") => "; \
        __ss << s << std::endl; \
        throw GameException( __ss.str() ); \
    }

    //___gstr( std::string("Error ") + __FILE__ +  " ");
    //___gstr += _str(__LINE__);
    //___gstr += " ";
    //___gstr += s;
    //throw GameException(___gstr);

inline void handleException(GameException e)
{
    std::cout << std::endl << e.what() << std::endl;
    std::ofstream file("Error.txt");
    file << e.what();
    file.close();
}


#endif // ERRORHANDLER_H
