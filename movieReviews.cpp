//COMSC-210 | Lab 18 | Eric-Giulio Hedes
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Declare the Movie class
struct Review
{
    double rating; //Will be used for the random ratings
    string review; //Will be used for the reviews from the file
    Review *next; //Since this is a linked list, this'll be used
};

//Introduce the Movie class
class Movie
{
    //Here are the private functions
    private:
        //A simple title string :P
        string title;
        //This will be used for gathering ratings and structures
        Review *reviews;
        //removeList() is used here for easier code integration within the destructor & the copy assignment operator
        void removeList()
        {
            //Set up a temporary linked list
            Review *current = reviews;
            //Use a while() loop to delete every element from the list
            while(current != nullptr)
            {
                reviews = current->next;
                delete reviews;
                current = reviews;
            }
            //Then set the list as nullptr for no errors
            reviews = nullptr;
        }
    //Here are the public functions
    public:
        //getTitle() will return the title
        string getTitle() { return title; }
        //setTitle() will simply change the title with the use of a parameter
        void setTitle(string str) { title = str; }
        //Adding ratings & reviews here
        void addReview(double rating, string review)
        {
            //Create newVal, which'll be used for adding the rating & review values
            Review *newVal = new Review;
            newVal->rating = rating;
            newVal->review = review;
            //Set the newVal struct to reviews (or the head)
            newVal->next = reviews;
            reviews = newVal;

        }
        //getReviewAverage() will calculate the amount of ratings go get the average number
        double getReviewAverage()
        {
            //If there are no reviews, return 0
            if (reviews == nullptr) return 0;
            //Set up the starter average value
            double avg = 0;
            //You know the deal; use a Review node to go through the linked list
            Review *current = reviews;
            int size = 0;
            //Use a while() loop to iterate through the entire linked list loop
            while (current != nullptr)
            {
                size += 1;
                avg += current->rating;
                current = current->next;
            }
            //Return the average number divided by the size
            return avg / size;
        }
        //Print out the title & reviews
        void output()
        {
            //If the review list is empty, generate an error message
            if (reviews == nullptr) cout << "Empty list. Sorry!" << endl;
            else
            {
                //Set the precision to 1 for the review values
                cout.setf(ios::fixed|ios::showpoint);
                cout << setprecision(1);
                //Print out the movie title
                cout << "Movie Title: " << getTitle() << endl;
                //Use a Review node to go through all the linked list values
                Review *current = reviews;
                int count = 1;
                //Also a while() loop to properly iterate through all elements
                while (current != nullptr)
                {
                    cout << setw(10) << "> Review #" << count << ": " << current->rating << ": " << current->review << endl;
                    count += 1;
                    current = current->next;
                }
                //Print the average
                cout << setw(10) << "> Average: " << getReviewAverage() << endl << endl;
            }
        }
        //Movie Constructors
        Movie() : reviews(nullptr) { setTitle("N/A"); }
        Movie(string title) : reviews(nullptr) { setTitle(title); }
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

//Start of main()
int main()
{
    //Random seed generator
    srand(time(0));
    //Declare the movieList vector
    vector<Movie> movieList;
    //Also put in the input file
    ifstream file("input.txt");

    int index;
    string file_title, file_review[3];
    while (getline(file, file_title))
    {
        if (file_title.empty()) continue;
        for (int i = 0; i < 3; i++) getline(file, file_review[i]);

        Movie m;
        m.setTitle(file_title);
        for (int i = 0; i < 3; i++)
            m.addReview(double(rand() % 50) / 10, file_review[i]);
        movieList.push_back(m);
    }
    for (int i = 0; i < movieList.size(); i++)
        movieList[i].output();
}