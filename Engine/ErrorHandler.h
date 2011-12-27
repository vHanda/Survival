/*
 * Survival
 *
 * Copyright (C) 2009-2011 Vishesh Handa <me@vhanda.in>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

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
