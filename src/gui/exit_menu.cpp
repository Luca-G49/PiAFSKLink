#include "gui_utils.h"
#include <thread>


// Exit menu
void exit_menu(){
    clearTerminal();
    printBorder("Goodbye, thank you for using the application!");
    std::this_thread::sleep_for(std::chrono::seconds(2));
}