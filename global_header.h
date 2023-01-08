#ifndef GLOBAL_HEADER_H
#define GLOBAL_HEADER_H
#include <exception>
#include <string>

class Matrice_Except:public std::exception
{
public:
    explicit Matrice_Except(std::string&& str) throw():
        m_msg(str)
    {}
    virtual const char* what() const throw()
    {
        return m_msg.c_str();
    }
    virtual ~Matrice_Except()
    {}
private:
    std::string m_msg;
};

#endif // GLOBAL_HEADER_H
