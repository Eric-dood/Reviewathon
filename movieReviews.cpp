//COMSC-210 | Lab 18 | Eric-Giulio Hedes
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//Declare the Movie class
struct Rating
{
    double rating;
    string review;
};

class Movie
{
    private:
        string title;
        Rating *reviews;
    public:
        string getTitle() { return title; }
        void setTitle(string str) { title = str; }
        Movie() : reviews(nullptr) {}
        ~Movie() { delete reviews; }
};