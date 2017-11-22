
//Authors
// Alexandre Pelletier - 27259492
// Martin Spasov 40000916
// Loic Huss - 40000298
#include "indexer.h"
#include "movie_indexer.h"
#include "document.h"
#include "Query_Result.h"
#include "sentence.h"
#include "sentence_tokenizer.h"
#include "movie_tokenizer.h"
#include "index_exception.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <cstring>
#include <sstream>
#include <limits>

using namespace std;

int getIntInput(string message, int skipNum, int max, int min=0);

bool findMovie( movie_indexer& movIdx);

int main() {
    movie_indexer movIdx;
    vector<movie> movVec;
    movie_tokenizer mt;
    string metadata = "movie.metadata.tsv";
    string descriptions = "plot_summaries.txt";

    cout << "-----------------------------------------" << endl << endl;
    cout << "Loading the list of movies. This may take a while..." << endl;
    
    movVec = mt.movie_tokenize(metadata, descriptions);

    int start_index = clock();
    try{
        movVec = mt.movie_tokenize(metadata, descriptions);
    }catch (runtime_error& ex){
        cout<<ex.what()<<endl;
        return 1;
    }
    for(vector<movie>::iterator movIt = movVec.begin(); movIt != movVec.end(); ++movIt){
        &*movIt >> movIdx;
    }
    int stop_index = clock();
    cout << "Time for indexing: " << (stop_index - start_index)/double(CLOCKS_PER_SEC)*1000 << endl;
    movIdx.normalize();
    cout << "Finished loading!" << endl << endl;
    cout << "-----------------------------------------" << endl << endl;
    bool movieFound = false;
    do {
        movieFound = findMovie(movIdx);
    }while (!movieFound);
    cout << "Goodbye!" <<endl;
    string stall;
    cin >> stall;

    return 0;
}

bool findMovie( movie_indexer& movIdx){
    bool getMoreFavourites = false;
    try {
        do {
            string favMovieName;
            cout << "What is your favourite movie?" << endl;
            getline(cin, favMovieName);
            vector<movie *> favMovies = movIdx[favMovieName];
            movie *favMovie;
            bool choseAMovie = false;

            while (!choseAMovie) {
                if (favMovies.size() > 0) {
                    cout << endl << "Which one of these is your favourite?" << endl;
                    for (int i = 0; i < favMovies.size(); ++i) {
                        cout << "[" << i << "] - " << *favMovies[i] << endl;
                    }
                    cout << endl;
                    int numInput = getIntInput("Please choose...", -1, favMovies.size() - 1);
                    favMovie = favMovies[numInput];
                    choseAMovie = true;
                } else {
                    throw index_exception();
                }
            }

            cout << endl << "-----------------------------------------" << endl << endl;

            cout << "Computing a recommendations list. This may take a while..." << endl << endl;
            Query_Result movQ;
            movQ.query(movIdx, favMovie->get_content());
            cout << "Finished computations!" << endl;
            cout << endl << "-----------------------------------------" << endl << endl;

            int numRecommendations = getIntInput("How many recommendations would you like? (-1 to skip)", -1,
                                                 movIdx.getSize() - 1, 1);
            if (numRecommendations == -1) {
                numRecommendations = 5;
            }
            cout << endl << "-----------------------------------------" << endl << endl;

            vector<index_item *> movieRecommendations;
            movieRecommendations = movQ.getTopNResults(numRecommendations, favMovie);

            cout << "Here are our recommendations: " << endl;
            for (vector<index_item *>::iterator itemsIt = movieRecommendations.begin();
                 itemsIt != movieRecommendations.end(); ++itemsIt) {
                movie *mov = dynamic_cast<movie *>(*itemsIt);
                cout << *mov << endl;
            }

            string continuePlease;
            cout << endl << "Would you like to get recommendations for another movie? (Enter Y/Yes)" << endl;
            cin >> continuePlease;
            transform(continuePlease.begin(), continuePlease.end(), continuePlease.begin(), ::toupper);

            getMoreFavourites = (continuePlease == "Y" || continuePlease == "YES");
        } while (getMoreFavourites);
    }
    catch (index_exception& ex){
        cout<< ex.what() <<endl;
        return false;
    }
    return true;
}

int getIntInput(string message, int skipNum, int max, int min){
    bool isNumberInput = false;
    int input;
    while(!isNumberInput) {
        cout << message << " (" << min << "-" << max << ")" << endl;
        string temp;
        cin >> temp;
        stringstream convertor;
        convertor << temp;
        convertor >> input;

        //make sure it's an int
        if(convertor.fail() || (input != skipNum && (input < min || input > max))){
            cout << "Please enter a valid number..." << endl << endl;
        }
        else{
            isNumberInput = true;
        }
    }
    return input;
}
