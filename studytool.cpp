/**
 * studytool.cpp file for CppPy-StudyTool
 * Author: Ian Cox
 * March 2024
 *
 * Implementation file for the CppPy-StudyTool class.
 * This file contains the definitions of methods to facilitate interactive study sessions,
 * including flashcard practice and a multiple-choice game.
 * Known bugs: None.
 * TODO: N/A
 */

#include "studytool.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <vector>
#include <iomanip>
using namespace std;

/**
 * Constructor implementation
 * @param inputTerms
 * @param inputDefs
 */
StudyTool::StudyTool(const std::vector<std::string>& inputTerms, const std::vector<std::string>& inputDefs)
        : terms(inputTerms), defs(inputDefs), score(0) {}

/**
 * Flashcard practice game mode
 * Inputs:
 *   - const vector<string>& inputTerms: Vector containing study terms.
 *   - const vector<string>& inputDefs: Vector containing corresponding definitions.
 * Description:
 *   Allows the user to go through each term, revealing its definition, and optionally starring terms to review later.
 *   After reviewing all terms, the user can choose to study the starred terms.
 */
void StudyTool::playflip(const vector<string>& inputTerms, const vector<string>& inputDefs) {
    vector<string> starred;
    vector<string> starredDefs;
    size_t counter = 0;

    auto termIt = inputTerms.begin();
    auto defIt = inputDefs.begin();

    while (termIt != inputTerms.end() && defIt != inputDefs.end()) {
        cout << *termIt << endl;
        cout << "Click enter to flip card";

        if (cin.get() == '\n') {
            system("clear");
            cout << *defIt << endl;

            bool starTerm = true;
            while (starTerm) {
                cout << "Do you want to star this term or move on? [type 'star' to star or click enter to advance]";
                string star;
                getline(cin, star);

                if (star == "star") {
                    starred.push_back(*termIt);
                    starredDefs.push_back(*defIt);
                    starTerm = false;
                } else if (star.empty()) {
                    starTerm = false;
                }
            }

            ++termIt;
            ++defIt;
        }
    }

    counter = 0;
    string response;
    bool studyMore = true;

    while (studyMore) {
        cout << "Would you now like to study your starred terms? ['y' for yes, 'n' for no]: ";
        string study;
        getline(cin, study);
        
        if (study == "y") {
            for (const auto& s : starred) {
                cout << s << endl;
                cin.ignore();
                cout << "Click enter to flip card";
                if (cin.get() == '\n') {
                    system("clear");
                    cout << starredDefs[counter] << endl;
                }
                counter++;
            }
            studyMore = false;
        } else if (study == "n") {
            studyMore = false;
        } else {
            cout << "That was an invalid response, try again." << endl;
        }
    }
}

/**
 * Multiple-choice game mode
 * Inputs:
 *   - const vector<string>& inputTerms: Vector containing study terms.
 *   - const vector<string>& inputDefs: Vector containing corresponding definitions.
 * Returns:
 *   - int: User's score in the multiple-choice game.
 * Description:
 *   Presents study terms as multiple-choice questions, with the user selecting the correct definition.
 *   Scores are calculated based on the number of correct answers.
 */
int StudyTool::mult(const vector<string>& inputTerms, const vector<string>& inputDefs) {
    int score = 0;

    for (const auto &term : inputTerms) {
        cout << term << endl;
        size_t index = distance(inputTerms.begin(), find(inputTerms.begin(), inputTerms.end(), term));
        size_t cycle = 1;
        int correct = 0;
        vector<string> used;
        size_t rangeCycle = (inputTerms.size() >= 4) ? 5 : inputTerms.size() + 1;
        size_t randomIndex = (inputTerms.size() >= 4) ? rand() % 4 + 1 : rand() % inputTerms.size() + 1;

        while (cycle < rangeCycle) {
            if (cycle == randomIndex) {
                cout << cycle << ": " << inputDefs[index] << endl;
                correct = randomIndex;
                used.push_back(inputDefs[index]);
            } else {
                string randdef = inputDefs[rand() % inputDefs.size()];

                while (cycle != randomIndex && randdef == inputDefs[index]) {
                    randdef = inputDefs[rand() % inputDefs.size()];
                }
                bool doneUsed = true;

                while (doneUsed) {
                    if (find(used.begin(), used.end(), randdef) != used.end()) {
                        randdef = inputDefs[rand() % inputDefs.size()];
                    } else {
                        doneUsed = false;
                    }
                }
                cout << cycle << ": " << randdef << endl;
                used.push_back(randdef);
            }
            cycle++;
        }

        int guess;
        cout << "What is your guess? [enter a number 1-4]: ";

        while (!(cin >> guess) || guess < 1 || guess > 4) {
            cout << "Invalid input. Please enter a number between 1 and 4: ";
            cin.clear();
            cin.ignore();
        }

        if (correct == guess) {
            cout << "You were correct!" << endl;
            score++;
        } else {
            cout << "That's not correct. The correct answer was: " << correct << endl;
        }
        cin.ignore();
    }
    return score;
}

/**
 * Matching game mode
 * Inputs:
 *   - const vector<string>& inputTerms: Vector containing study terms.
 *   - const vector<string>& inputDefs: Vector containing corresponding definitions.
 * Description:
 *   - Presents terms and definitions shuffled, asking the user to match them.
 *   - Scores are calculated based on the number of correct matches.
 */
int StudyTool::matchingGame(const vector<string>& inputTerms, const vector<string>& inputDefs) {
    // Check if there are enough terms and definitions
    if (inputTerms.size() < 2 || inputDefs.size() < 2 || inputTerms.size() != inputDefs.size()) {
        cout << "Insufficient terms and definitions for the matching game." << endl;
        return 0;
    }

    // Combine terms and definitions into a single vector of pairs
    vector<pair<string, string>> shuffledPairs;
    for (size_t i = 0; i < inputTerms.size(); ++i) {
        shuffledPairs.push_back(make_pair(inputTerms[i], inputDefs[i]));
    }

    // Seed for random number generation
    unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());

    // Shuffle the pairs using <algorithm> and <random>
    shuffle(shuffledPairs.begin(), shuffledPairs.end(), std::default_random_engine(seed));

    // Display shuffled terms and ask the user to match them
    int score = 0;
    cout << "Matching Game: Match the terms with their correct definitions" << endl;

    for (const auto& pair : shuffledPairs) {
        cout << pair.first << " -> ";
        string userAnswer;
        getline(cin, userAnswer);

        if (userAnswer == pair.second) {
            cout << "Correct!" << endl;
            ++score;
        } else {
            cout << "Incorrect. The correct definition was: " << pair.second << endl;
        }
    }

    // Display final score
    cout << "Matching Game Score: " << score << " out of " << shuffledPairs.size() << endl;

    return score;
}

/**
 * Time-based challenge game mode
 * Inputs:
 *   - const vector<string>& inputTerms: Vector containing study terms.
 *   - const vector<string>& inputDefs: Vector containing corresponding definitions.
 *   - int timeLimit: Time limit for the challenge in seconds.
 * Returns:
 *   - int: User's score in the time-based challenge.
 * Description:
 *   - Presents study terms with a time limit for the user to answer as many as possible.
 *   - Scores are calculated based on the number of correct answers.
 */
int StudyTool::timeChallenge(const vector<string>& inputTerms, const vector<string>& inputDefs, int timeLimit) {
    int score = 0;

    cout << "Time-Based Challenge: Answer as many questions as possible within " << timeLimit << " seconds." << endl;
    cout << "Press enter to start the challenge..." << endl;
    cin.ignore();

    auto startTime = chrono::steady_clock::now();
    auto endTime = startTime + chrono::seconds(timeLimit);

    for (const auto& term : inputTerms) {
        if (chrono::steady_clock::now() > endTime) {
            cout << "Time's up! Challenge completed." << endl;
            break;
        }

        cout << term << " -> ";
        string userAnswer;
        getline(cin, userAnswer);

        size_t index = distance(inputTerms.begin(), find(inputTerms.begin(), inputTerms.end(), term));
        if (userAnswer == inputDefs[index]) {
            cout << "Correct!" << endl;
            ++score;
        } else {
            cout << "Incorrect. The correct definition was: " << inputDefs[index] << endl;
        }
    }

    // Display final score
    cout << "Time-Based Challenge Score: " << score << " out of " << inputTerms.size() << endl;

    return score;
}

/**
 * Overloaded equality operator
 * Inputs:
 *   - const StudyTool& other: Reference to another StudyTool object for comparison.
 * Returns:
 *   - bool: True if the current StudyTool's score is equal to the provided StudyTool's score, false otherwise.
 * Description:
 *   - Compares two StudyTool objects for equality based on their scores.
 *   - Returns true if the scores are identical, and false otherwise.
 */
bool StudyTool::operator==(const StudyTool& other) const {
    return score == other.score;
}