//COMSC-210 | Lab 18 | Eric-Giulio Hedes
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//Declare the Movie class
struct Review
{
    double rating;
    string review;
    Review *next;
};

class Movie
{
    private:
        string title;
        Review *reviews;
    public:
        string getTitle() { return title; }
        void setTitle(string str) { title = str; }
        void addReview(Review *&r, double rating, string review)
        {
            Review *newVal = nullptr;
            if (!r)
            {
                r = newVal;
                newVal->next = nullptr;
                newVal->rating = rating;
                newVal->review = review;
            }
            else
            {
                newVal->next = r;
                newVal->rating = rating;
                newVal->review = review;
            }
        }
        //Movie Constructor
        Movie() : reviews(nullptr) {}
        //Movie Destructor
        ~Movie() { delete reviews; }
};