#include "Error.hpp"

PR_ERROR::PR_ERROR(const string& message)
    : message(message){}

const char* PR_ERROR::what() const noexcept{
    return message.c_str(); 
}

Permission::Permission(const string& message)
   : PR_ERROR(message){}

Existance::Existance(const string& message)
    : PR_ERROR(message){}

Format::Format(const string& message)
    : PR_ERROR(message){}

Level::Level(const string& message)
    : PR_ERROR(message){}