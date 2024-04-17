/**
 * main.cpp file for CppPy-StudyTool
 * Author: Ian Cox
 * March 2024
 *
 * This file allows users to input study terms and their definitions, offering flashcards practice and a multiple-choice game.
 * Known bugs: None.
 * TODO: N/A
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "studytool.h"
using namespace std;

enum GameMode {
    FLASHCARDS_PRACTICE,
    MULTIPLE_CHOICE_GAME,
    MATCHING_GAME,
    TIME_CHALLENGE
};

void writeToCSV(const std::vector<GameSession>& sessions) {
    ofstream outFile("../game_sessions.csv");

    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file game_sessions.csv" << endl;
        return;
    }

    outFile << "GameMode,NumCorrectAnswers\n";

    for (const auto& session : sessions) {
        outFile << session.gameMode << "," << session.numCorrectAnswers << "\n";
    }

    outFile.close();

    cout << "Data written to game_sessions.csv" << endl;
}

int main() {
    cout << "Hi, welcome to C++ Study Tool. This program will help prepare you for your exams in an exciting manner!"
         << endl;
    cout << "Created by Ian Cox" << endl;

    vector<GameSession> sessions;
    int multGamesPlayed = 0;
    int matchGamesPlayed = 0;
    int timedGamesPlayed = 0;

    vector<string> terms;
    vector<string> defs;
    bool play = true;

    while (play) {
        string term, def;
        cout << "Enter a term: ";
        cin >> term;
        terms.push_back(term);
        cout << "Enter the definition for the term that you just entered: ";
        cin >> def;
        defs.push_back(def);
        bool againCorrect = true;
        bool firstTime = true;

        while (againCorrect) {
            string input;
            cout << "Would you like to add another term + definition or stop ['y' to add more, 'n' to stop]: ";

            if (firstTime) {
                cin.ignore();
                firstTime = false;
            }
            getline(cin, input);

            if (input == "n") {
                againCorrect = false;
                play = false;
            } else if (input == "y") {
                againCorrect = false;
            } else {
                cout << "The value that you entered was invalid. Click enter to try again." << endl;
                cin.ignore();
            }
        }
    }

    StudyTool studyTool(terms, defs);
    int firstScore = 0;
    bool playAgain = true;

    while (playAgain) {
        string input;
        cout << "Now the fun part... What mode would you like to play?" << endl;
        cout << "1.) Flashcards Practice [enter '1']" << endl;
        cout << "2.) Multiple Choice Game [enter '2']" << endl;
        cout << "3.) Matching Game [enter '3']" << endl;
        cout << "4.) Time-Based Challenge [enter '4']" << endl;

        cin.clear();
        getline(cin, input);

        GameMode mode;

        if (input.length() == 1) {
            char modeChar = input[0];

            if (modeChar == '1') {
                mode = FLASHCARDS_PRACTICE;
            } else if (modeChar == '2') {
                mode = MULTIPLE_CHOICE_GAME;
            } else if (modeChar == '3') {
                mode = MATCHING_GAME;
            } else if (modeChar == '4') {
                mode = TIME_CHALLENGE;
            } else {
                cout << "The value that you entered was invalid. Click enter to try again." << endl;
                cin.ignore();
                continue;
            }

            switch (mode) {
                case FLASHCARDS_PRACTICE:
                    studyTool.playflip(terms, defs);
                    break;

                case MULTIPLE_CHOICE_GAME: {
                    vector<int> scores;
                    int score = 0;
                    if (firstScore == 0) {
                        firstScore = studyTool.mult(terms, defs);
                        cout << "Your score: " << firstScore << endl;
                        score = firstScore;
                    } else {
                        int recentScore = studyTool.mult(terms, defs);
                        cout << "Your score: " << recentScore << endl;
                        if (recentScore == firstScore) {
                            cout << "Your most recent score is equal to your first score." << endl;
                        } else if (recentScore > firstScore) {
                            cout << "Your most recent score is higher than your first score!" << endl;
                        } else {
                            cout << "Your most recent score is lower than your first score." << endl;
                        }
                        score = recentScore;
                    }

                    sessions.push_back({"MultipleChoiceGame", score});
                    multGamesPlayed ++;

                    if (multGamesPlayed >= 2) {
                        string graphInput;
                        cout << "Do you want a breakdown of your multiple choice game scores in a python plotted graph? [enter 'y' for yes or 'n' for no]" << endl;
                        getline(cin, graphInput);

                        while (graphInput != "y" && graphInput != "n") {
                            cout << "Invalid input. Do you want a breakdown of your multiple choice game scores in a python plotted graph? [enter 'y' for yes or 'n' for no]" << endl;
                            getline(cin, graphInput);
                        }

                        if (graphInput == "y") {
                            writeToCSV(sessions);
                            system("python3 ../plots.py");
                        }
                    }

                    break;
                }
                case MATCHING_GAME: {
                    int score = studyTool.matchingGame(terms, defs);
                    sessions.push_back({"MatchingGame", score});
                    matchGamesPlayed ++;

                    if (matchGamesPlayed >= 2) {
                        string graphInput;
                        cout << "Do you want a breakdown of your matching game scores in a python plotted graph? [enter 'y' for yes or 'n' for no]" << endl;
                        getline(cin, graphInput);

                        while (graphInput != "y" && graphInput != "n") {
                            cout << "Invalid input. Do you want a breakdown of your matching game scores in a python plotted graph? [enter 'y' for yes or 'n' for no]" << endl;
                            getline(cin, graphInput);
                        }

                        if (graphInput == "y") {
                            writeToCSV(sessions);
                            system("python3 ../plots.py");
                        }
                    }

                    break;
                }
                case TIME_CHALLENGE: {
                    int timeLimit;
                    cout << "Enter the time limit for the challenge in seconds: ";
                    cin >> timeLimit;
                    int score = studyTool.timeChallenge(terms, defs, timeLimit);
                    sessions.push_back({"TimeChallenge", score});
                    timedGamesPlayed ++;

                    if (timedGamesPlayed >= 2) {
                        string graphInput;
                        cout << "Do you want a breakdown of your time challenge game scores in a python plotted graph? [enter 'y' for yes or 'n' for no]" << endl;
                        getline(cin, graphInput);

                        while (graphInput != "y" && graphInput != "n") {
                            cout << "Invalid input. Do you want a breakdown of your time challenge game scores in a python plotted graph? [enter 'y' for yes or 'n' for no]" << endl;
                            getline(cin, graphInput);
                        }

                        if (graphInput == "y") {
                            writeToCSV(sessions);
                            system("python3 ../plots.py");
                        }
                    }

                    break;
                }
                default:
                    break;
            }

        } else {
            cout << "The value that you entered was invalid. Click enter to try again." << endl;
            cin.ignore();
            continue;
        }

        bool againCorrect = true;

        while (againCorrect) {
            string input;
            cout << "Do you want to play again? ['y' for yes, 'n' for no]: ";

            getline(cin, input);

            if (input == "n") {
                againCorrect = false;
                playAgain = false;
                cout << "Thanks for using the C++ Study Tool. Goodbye!" << endl;
            } else if (input == "y") {
                againCorrect = false;
            } else {
                cout << "The value that you entered was invalid. Click enter to try again." << endl;
                cin.ignore();
            }
        }


    }

    return 0;
}
