#ifndef INITERROR_H
#define INITERROR_H
#include <string>
#include <SDL2/SDL.h>
class InitError : public std::exception
{
        std::string msg;
    public:
        InitError();
        InitError( const std::string & );
        virtual ~InitError() throw();
        virtual const char * what() const throw();

    protected:

    private:
};

#endif // INITERROR_H
