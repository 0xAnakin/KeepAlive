#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <windows.h>

int SEC = 1000;
char ARR[11] = "0123456789";

// Check if a char array contains a character
bool contains(const char* arr, size_t len, const char& ch)
{
    bool result = false;
    // Iterate over the char array
    for (int i = 0; i < len; i++)
    {
        // Check if element at ith index in array
        // is equal to the given character
        if (arr[i] == ch)
        {
            // Match found
            result = true;
            break;
        }
    }
    return result;
}

bool is_valid_integer_integer(const std::string& str) 
{    
    if (str.empty() || str[0] == '0') {
        return false;
    }

    for (int i = 0; i < str.size(); i++) {
        if (!contains(ARR, strlen(ARR), str[i])) {
            return false;
        } 
    }

    return true;
}

int main(int argc, char* argv[])
{   

    int min = 1; // 1 minutes
    int max = 5;  // 5 minutes

    if (argc > 1) 
    {
        if (is_valid_integer_integer(argv[1]))
        {   
            min = atoi(argv[1]);
        }

        if (argc > 2)
        {
            if (is_valid_integer_integer(argv[2]))
            {
                int new_max = atoi(argv[2]);
                // in case new_max is not bigger than min, adjust it
                max = new_max > min ? new_max : min + 1;
                
            }
        }
        else 
        {
            // if no second argument make max 1 minute bigger
            max = min + 1; 
        }

    }
    
    std::cout << "interval range: " << min << "mins - " << max << "mins" << std::endl;

    std::srand(std::time(0));

    while (true) {
        
        // sleep interval
        int interval_in_minutes = std::rand() % (max - min + 1) + min;
        
        // Create an array of INPUT structures to hold the inputs
        INPUT inputs[2] = {};

        // Set up the INPUT structure for a key press event
        inputs[0].type = INPUT_KEYBOARD;  // Specify input type as keyboard
        inputs[0].ki.wVk = VK_SPACE;      // Virtual-key code for the SPACE key

        // Set up the INPUT structure for a key release event
        inputs[1].type = INPUT_KEYBOARD;  // Specify input type as keyboard
        inputs[1].ki.wVk = VK_SPACE;      // Virtual-key code for the SPACE key
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;  // Specify key release event

        // Send the inputs to the system
        UINT uSent = SendInput(2, inputs, sizeof(INPUT));

        if (uSent != 2)  // Check if all inputs were successfully sent
        {
            // If the function fails, it returns 0
            // MessageBox(NULL, L"Failed to send SPACE key input.", L"Error", MB_OK | MB_ICONERROR);
            std::cerr << "Failed to send SPACE key input" << std::endl;
        }
        
        std::cout << "Sleeping for " << interval_in_minutes << "mins" << std::endl;
        
        std::this_thread::sleep_for(std::chrono::minutes(interval_in_minutes));
        
    }

    exit(0);

}
