//COMSC-210 | Lab 18 | Eric-Giulio Hedes
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 4;

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
        Review *getReview() { return reviews; }
        void addReview(double rating, string review)
        {
            Review *newVal = new Review;
            newVal->rating = rating;
            newVal->review = review;
            newVal->next = reviews;
            reviews = newVal;

        }
        //Print out the title & reviews
        void output()
        {
            cout << "Movie Title: " << getTitle() << endl;
            for (int i = 0; i < 3; i++)
                cout << setw(10) << "> Review #" << i+1 << getReview()->rating << endl;
        }
        //Movie Constructors
        Movie() : reviews(nullptr) {}
        Movie(double rating) : reviews(nullptr) {}
        //Movie Destructor
        ~Movie()
        {
            Review *current = reviews;
            while(current != nullptr)
            {
                reviews = current->next;
                delete reviews;
                current = reviews;
            }
            reviews = nullptr;
        }
};

int main()
{
    srand(time(0));
    vector<Movie> reviewList;
    for (int i = 0; i < SIZE; i++)
    {
        Movie temp;
        temp.addReview(rand() % 5, "wtf");
    }
}