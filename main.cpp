#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

// Structure to hold task details
struct Task {
    std::string name;
    std::vector<std::string> steps;
    std::string category;
    int weight; // Used for weighted randomization
};

int main() {
    // Seed the random number generator
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    
    std::vector<Task> taskPool;
    char addMore = 'y';

    std::cout << "--- Daily Challenge Randomizer Initializer ---\n";

    // 1-3. Loop to gather tasks from the user
    while (addMore == 'y' || addMore == 'Y') {
        Task newTask;
        
        std::cout << "\nEnter the name of the task: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        std::getline(std::cin, newTask.name);

        int stepCount = 0;
        std::cout << "How many steps to complete the task? ";
        std::cin >> stepCount;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int i = 0; i < stepCount; ++i) {
            std::string stepDesc;
            std::cout << "Enter instruction for step " << (i + 1) << ": ";
            std::getline(std::cin, stepDesc);
            newTask.steps.push_back(stepDesc);
        }

        // 4-7. Categorize and assign weights based on step count
        if (stepCount < 10) {
            newTask.category = "Easy";
            newTask.weight = 3; // 3x more common than hard
        } else if (stepCount >= 10 && stepCount <= 15) {
            newTask.category = "Medium";
            newTask.weight = 2; // 2x more common than hard
        } else {
            newTask.category = "Hard";
            newTask.weight = 1; // Base weight
        }

        taskPool.push_back(newTask);

        std::cout << "Task added successfully as [" << newTask.category << "]! Add another task? (y/n): ";
        std::cin >> addMore;
    }

    if (taskPool.empty()) {
        std::cout << "No tasks entered. Exiting program.\n";
        return 0;
    }