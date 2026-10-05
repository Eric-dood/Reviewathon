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
        void removeList()
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
    public:
        string getTitle() { return title; }
        void setTitle(string str) { title = str; }
        void addReview(double rating, string review)
        {
            Review *newVal = new Review;
            newVal->rating = rating;
            newVal->review = review;
            newVal->next = reviews;
            reviews = newVal;

        }
        double getReviewAverage()
        {
            if (reviews == nullptr) return 0;

            double avg;
            Review *current = reviews;
            int size = 0;
            while (current != nullptr)
            {
                size += 1;
                avg += current->rating;
                current = current->next;
            }
            return avg / size;
        }
        //Print out the title & reviews
        void output()
        {
            cout << "Movie Title: " << getTitle() << endl;
            Review *current = reviews;
            int count = 1;
            while (current != nullptr)
            {
                cout << setw(10) << "> Review #" << count << ": " << current->rating << ": " << current->review << endl;
                count += 1;
                current = current->next;
            }
            cout << setw(10) << "> Average: " << getReviewAverage() << endl << endl;
        }
        //Movie Constructors
        Movie() : reviews(nullptr) {}
        Movie(string title) : reviews(nullptr) { setTitle(title); }
        Movie(string title, double rating) : reviews(nullptr) { setTitle(title); }
        //Copy constructor
        Movie(const Movie& o)
        {
            title = o.title;
            reviews = nullptr;
            Review* newNode = nullptr, *current = o.reviews, *tail = nullptr;
            while (current != nullptr)
            {
                newNode = new Review;
                newNode->rating = current->rating;
                newNode->review = current->review;
                newNode->next = nullptr;
                if (reviews == nullptr) reviews = newNode;
                else tail->next = newNode;
                tail = newNode;
                current = current->next;
            }
        }
        //Movie Destructor
        ~Movie() { removeList(); }
        //Copy assignment operator
        Movie& operator=(const Movie& o)
        {
            if (this != &o)
            {
                removeList();
                title = o.title;
                reviews = nullptr;
                Review* newNode = nullptr, *current = o.reviews, *tail = nullptr;
                while (current != nullptr)
                {
                    newNode = new Review;
                    newNode->rating = current->rating;
                    newNode->review = current->review;
                    newNode->next = nullptr;
                    if (reviews == nullptr) reviews = newNode;
                    else tail->next = newNode;
                    tail = newNode;
                    current = current->next;
                }
            }
            return *this;
        }
};

int main()
{
    srand(time(0));
    vector<Movie> reviewList;
    ifstream file;
    file.open("input.txt");

    string file_title, file_review;
    while (getline(file, file_title))
    {
        file.ignore();
        for (int i = 0; i < 3; i++)
            getline(file, file_review);
    }

    for (int i = 0; i < SIZE; i++)
    {
        Movie temp;
        temp = Movie("title");
        for (int i = 0; i < 3; i++)
            temp.addReview(double(rand() % 50) / 10, "wtf");
        reviewList.push_back(temp);
    }
    for (int i = 0; i < SIZE; i++)
        reviewList[i].output();
}