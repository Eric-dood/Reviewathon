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
        void copyConstructInit(Review *n1, Review *n2, Review *n3)
        {
            while (n2 != nullptr)
            {
                n1 = new Review;
                n1->rating = n2->rating; //Set up the rating
                n1->review = n2->review; //Set up the review
                n1->next = nullptr; //Set the next value as nullptr
                //If the reviews list is empty, 
                if (reviews == nullptr) reviews = n1;
                else n3->next = n1;
                n3 = n1;
                n2 = n2->next;
            }
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
                //Add up the size number by 1
                size += 1;
                //Add up the avergae by the rating
                avg += current->rating;
                //Go through the next element
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
                    //Print the review & ratings
                    cout << setw(10) << "> Review #" << count << ": " << current->rating << ": " << current->review << endl;
                    //Add up the count number by 1
                    count += 1;
                    //Go through the next element
                    current = current->next;
                }
                //Print the average
                cout << setw(10) << "> Average: " << getReviewAverage() << endl << endl;
            }
        }
        //Movie Constructors
        Movie() : reviews(nullptr) { setTitle("N/A"); }
        Movie(string title) : reviews(nullptr) { setTitle(title); }
        //Copy constructor; will be useful for vectors and such
        Movie(const Movie& o)
        {
            //Set the title as the other title
            title = o.title;
            //For now, set the reviews as the nullptr
            reviews = nullptr;
            //Bundle up all of those nodes
            Review* newNode = nullptr, *current = o.reviews, *tail = nullptr;
            //use copyConstructInit() for simpler code
            copyConstructInit(newNode, current, tail);
        }
        //Movie Destructor
        ~Movie() { removeList(); } //Simply reuse removeList lol
        //Copy assignment operator
        Movie& operator=(const Movie& o)
        {
            //If 'this' doesn't have a obj
            if (this != &o)
            {
                //Remove the list
                removeList();
                //Set up the title as o.title & reviews as nullptr
                title = o.title;
                reviews = nullptr;
                //Set up the nodes
                Review* newNode = nullptr, *current = o.reviews, *tail = nullptr;
                //use copyConstructInit() for simpler code
                copyConstructInit(newNode, current, tail);
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
    string filename = "input.txt"; //Will be used for the file name
    ifstream file(filename);

    int index;
    string file_title, file_review[3];
    //If the file does not exist, generate a error message
    if (!file.good()) cout << "No sight of '" << filename << "' file so far." << endl;
    else //Otherwise continue as normal
    {
        //Do a while() loop to get all of the files
        while (getline(file, file_title))
        {
            //If the title does not exist, continue
            if (file_title.empty()) continue;
            //Get all of the three reviews
            for (int i = 0; i < 3; i++) getline(file, file_review[i]);
            //Generate a temporary Movie object called m
            Movie m;
            //Set the title of the m object
            m.setTitle(file_title);
            //Also set the reviews of the m object
            for (int i = 0; i < 3; i++)
                m.addReview(double(rand() % 50) / 10, file_review[i]);
            //Add up the m object to the movieList vector
            movieList.push_back(m);
        }
        //After the whole loop is done, output all of the movie names & reviews!
        for (int i = 0; i < movieList.size(); i++)
            movieList[i].output();
    }
}