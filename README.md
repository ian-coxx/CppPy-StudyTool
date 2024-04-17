# CppPy-StudyTool

## Author
- Ian Cox
- March 2024

## Summary
CppPy-StudyTool is designed to help users prepare for exams, featuring 4 fun & interactive game modes. These are flashcards, multiple choice, matching, and a timed challenge. The project was created utilizing C++ and Python. 

## V1 Concepts Used
1. **Class:**
    - The project includes a class `StudyTool`, separated into header (`studytool.h`) and implementation (`studytool.cpp`) files.
    - The class has at least two fields and contains multiple methods for flashcard practice and a multiple-choice game.

2. **Enumerated Type:**
    - Enumerated types are employed in the program to represent different game modes. For example, the user can choose between Flashcards Practice and the Multiple-Choice Game, each represented by an enumerated type.
        ```cpp
        enum GameMode {
            FLASHCARDS_PRACTICE,
            MULTIPLE_CHOICE_GAME
        };
        ```
      The `GameMode` enum is used in the program to provide clear options for the user to choose from when deciding which mode to play.

3. **Overloaded Operator(s):**
    - The StudyTool class features an overloaded equality operator (operator==), allowing comparison of two StudyTool objects based on their scores.

## V2 Updates & Concepts Used
1. **Random Number Generators:**
    - My code utilizes the C++ random library to generate random numbers for shuffling.
       ```cpp
         size_t randomIndex = (inputTerms.size() >= 4) ? rand() % 4 + 1 : rand() % inputTerms.size() + 1;
         ```
2. **String Manipulation:**
    - Used in the playflip method where terms and definitions are displayed.
    - Involved in handling terms, definitions, and user input for starring terms.
3. **I/O Streams:**
    - My code uses I/O streams to facilitate user interactions, such as displaying messages and obtaining input.
4. **Iterators:**
    - Used iterators to traverse through a vector, specifically in my playflip method to get through inputTerms and inputDefs using termIt and defIt.
    - ```cpp
        auto termIt = inputTerms.begin();
        auto defIt = inputDefs.begin();

        while (termIt != inputTerms.end() && defIt != inputDefs.end()) {
        ```
5. **Initializer Lists:**
    - I used an initializer list to ensure that my StudyTool object was configured with the given terms and definitions, as well as an initial score of 0.
    - ```cpp
        StudyTool(const std::vector<std::string>& inputTerms, const std::vector<std::string>& inputDefs)
        : terms(inputTerms), defs(inputDefs), score(0) {}

        ```
## V3 Updates
- My program now uses python to plot scores from three different game modes after being played more than once. These include multiple choice game, matching game, and timed challenge game modes. 
- The program runs at once, where the users plays it initally in C++ either through an IDE such as CLion, or through the terminal. The program then sends scores and game mode data to game_sessions.csv, which is then read into plots.py to plot a bar graph with scores on the y-axis and games played on the x-axis. 

## Known Bugs
- None.

## Future Work
With more time, the program could be expanded in the following ways:
- Enhance the user interface for a more engaging experience.
- Add additional game modes or features to diversify the study methods.

## Citations
- size_t: https://en.cppreference.com/w/cpp/types/size_t
- distance(): https://www.educative.io/answers/what-is-the-distance-function-in-cpp
- find(): https://cplusplus.com/reference/string/string/find/
- clear(): https://cplusplus.com/reference/vector/vector/clear/
- ignore(): https://cplusplus.com/reference/istream/istream/ignore/
- system("clear"): https://www.w3schools.blog/clear-screen-in-c-2
- switch: https://www.w3schools.com/cpp/cpp_switch.asp
- static_cast: https://www.geeksforgeeks.org/static_cast-in-cpp/
- chrono in c++: https://www.geeksforgeeks.org/chrono-in-c/
- chrono::system_clock: https://en.cppreference.com/w/cpp/chrono/system_clock
- chrono::steady_clock: https://en.cppreference.com/w/cpp/chrono/steady_clock
- pandas library python: https://www.geeksforgeeks.org/introduction-to-pandas-in-python/
- matplotlib: https://www.w3schools.com/python/matplotlib_pyplot.asp
