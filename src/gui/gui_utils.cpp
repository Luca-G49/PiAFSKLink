#include "gui_utils.h"
#include "app_config.h"
#include <iostream>
#include <string>
#include <iomanip>

// Funzione per pulire il terminale
void clearTerminal() {
#ifdef _WIN32
    system("cls"); // Per Windows
#else
    system("clear"); // Per Linux/Mac
#endif
}

// Funzione per visualizzare un titolo stilizzato
void printTitle() {

    // Get App configuration
    Config::AppConfig& config = Config::get();

    std::cout << "\033[1;34m" << std::string(51, '=') << "\033[0m" << std::endl;
    std::cout << "\033[1;33m" << std::setw(30) << std::right << config.appName << "\033[0m" << std::endl; // Colore giallo per il titolo
    std::cout << "\033[1;34m" << std::string(51, '=') << "\033[0m" << std::endl; // Bordo blu per il titolo
}

// Funzione per creare un bordo visivo
void printBorder(const std::string& title) {
    std::cout << "\033[1;34m+-------------------------------------------------+\033[0m\n";  // Colore blu per il bordo superiore
    if (!title.empty()) {
        std::cout << "\033[1;32m| " << std::setw(48) << std::left << title << "|\033[0m\n";  // Colore verde per il titolo del blocco
        std::cout << "\033[1;34m+-------------------------------------------------+\033[0m\n";  // Colore blu per il bordo inferiore
    }
}