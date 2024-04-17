/**
 * studytool.h file for CppPy-StudyTool
 * Author: Ian Cox
 * March 2024
 *
 * Header file for the CppPy-StudyTool class, a study tool designed to help students prepare for exams, quizzes, and tests.
 * studytool.h provides methods for interactive study sessions, including flashcard practice and a multiple-choice game.
 * Known bugs: None.
 * TODO: N/A
 */

#ifndef M2AP_STUDYTOOL_H
#define M2AP_STUDYTOOL_H
#include <vector>
#include <string>
#include "GLFW/glfw3.h"
using namespace std;

struct GameSession {
    string gameMode;
    int numCorrectAnswers;
};

class StudyTool {
private:
    vector<string> terms;
    vector<string> defs;
    int score;

public:
    /**
     * Constructor using initializer list
     * @param inputTerms
     * @param inputDefs
     */
    StudyTool(const std::vector<std::string>& inputTerms, const std::vector<std::string>& inputDefs);

    /**
     * Flashcard practice game mode
     * Inputs:
     *   - const vector<string>& inputTerms: Vector containing study terms.
     *   - const vector<string>& inputDefs: Vector containing corresponding definitions.
     * Description:
     *   - Allows the user to go through each term, revealing its definition, and optionally starring terms to review later.
     *   - After reviewing all terms, the user can choose to study the starred terms.
     */
    void playflip(const vector<string>& inputTerms, const vector<string>& inputDefs);

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
    int mult(const vector<string>& inputTerms, const vector<string>& inputDefs);

    /**
     * Matching game mode
     * Inputs:
     *   - const vector<string>& inputTerms: Vector containing study terms.
     *   - const vector<string>& inputDefs: Vector containing corresponding definitions.
     * Description:
     *   - Presents terms and definitions shuffled, asking the user to match them.
     *   - Scores are calculated based on the number of correct matches.
     */
    int matchingGame(const vector<string>& inputTerms, const vector<string>& inputDefs);

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
    int timeChallenge(const vector<string>& inputTerms, const vector<string>& inputDefs, int timeLimit);

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
    bool operator==(const StudyTool& other) const;
};

#endif // M2AP_STUDYTOOL_H