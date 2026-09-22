#pragma once

#include <iostream>
#include <stdexcept>


using namespace std;

class PR_ERROR : public exception{
private:
    string message;
public:
    PR_ERROR(const string& message);
    const char* what() const noexcept override;
};

class Permission : public PR_ERROR{
private:

public:
    Permission(const string& message);

};

class Existance : public PR_ERROR{
private:

public:
    Existance(const string& message);
};

class Format : public PR_ERROR
{
private:
    
public:
    Format(const string& message);
};

class Level : public PR_ERROR
{
private:
   
public:
    Level(const string& message);
};
