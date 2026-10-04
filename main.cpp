#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
using namespace std;

// Structure to hold task details
struct Task {
    string name;
    vector<string> steps;
    string category;
    int weight; // Used for weighted randomization
};

int main() {
    // Seed the random number generator
    mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    
    vector<Task> taskPool;
    char addMore = 'y';

    cout << "--- Daily Challenge Randomizer Initializer ---\n";

    // 1-3. Loop to gather tasks from the user
    while (addMore == 'y' || addMore == 'Y') {
        Task newTask;
        
        cout << "\nEnter the name of the task: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        getline(cin, newTask.name);

        int stepCount = 0;
        cout << "How many steps to complete the task? ";
        cin >> stepCount;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < stepCount; ++i) {
            string stepDesc;
            cout << "Enter instruction for step " << (i + 1) << ": ";
            getline(std::cin, stepDesc);
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

        cout << "Task added successfully as [" << newTask.category << "]! Add another task? (y/n): ";
        cin >> addMore;
    }

    if (taskPool.empty()) {
        cout << "No tasks entered. Exiting program.\n";
        return 0;
    }
    
    // 8. Weighted Randomizer Selection
    // Build a distribution array where tasks appear multiple times according to their weight
    vector<size_t> weightedPool;
    for (size_t i = 0; i < taskPool.size(); ++i) {
        for (int w = 0; w < taskPool[i].weight; ++w) {
            weightedPool.push_back(i);
        }
    }

    uniform_int_distribution<size_t> dist(0, weightedPool.size() - 1);
    size_t randomIndex = weightedPool[dist(rng)];
    Task selectedTask = taskPool[randomIndex];

    // 9. Output the selected task and its instructions
    cout << "   Today's mission:   \n";
    cout << "========================================" << endl;
    cout << "Task Name: " << selectedTask.name << " (" << selectedTask.category << ")" << endl;
    cout << "Instructions:" << endl;

    for (size_t i = 0; i < selectedTask.steps.size(); ++i) {
        cout << "  " << (i + 1) << ". " << selectedTask.steps[i] << endl;
    }
    cout << "========================================" << endl;

    return 0;
}
