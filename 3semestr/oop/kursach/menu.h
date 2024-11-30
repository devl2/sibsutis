#include "func.h"

int menu(List& records) {
    List sortedRecords;
    tree* root = nullptr;

    Node* current = records.get_head();
    while (current) {
        sortedRecords.push_back(current->rec);
        current = current->next;
    }

    while (true) {
        std::cout << "\n=== Main Menu ===\n";
        std::cout << "1. Display Source Data\n";
        std::cout << "2. Sort Data\n";
        std::cout << "3. Search Records\n";
        std::cout << "4. Exit\n";
        std::cout << "===================\n";
        std::cout << "Please choose an option (1-4): ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                int currentPage = 0;
                while (true) {
                    records.display_records(currentPage * MAX_RECORDS, MAX_RECORDS);
                    std::cout << "Press 'q' to return to main menu: ";
                    char pageChoice;
                    std::cin >> pageChoice;
                    if (pageChoice == 'q' || pageChoice == 'Q') break;
                }
                break;
            }

            case 2: {
                int pageSize = 20;
                int currentPage = 0;

                DigitalSortStreetAndHouse(sortedRecords);

                while (true) {
                    std::cout << "\nPage " << (currentPage + 1) << ":\n";
                    sortedRecords.display_records(currentPage * pageSize, pageSize);
                    std::cout << "Sorted records count: " << sortedRecords.size() << std::endl;
                    
                    if ((currentPage + 1) * pageSize >= MAX_RECORDS) {
                        std::cout << "End" << std::endl; 
                        break;
                    }
                   
                    std::cout << "Press 'n' for next page, 'q' to exit: ";
                    
                    char pageChoice;
                    std::cin >> pageChoice;

                    if (pageChoice == 'n' || pageChoice == 'N') {
                        if ((currentPage + 1) * pageSize < MAX_RECORDS) {
                            currentPage++;
                        } else {
                            std::cout << "No more records." << std::endl;
                        }
                    } else if (pageChoice == 'q' || pageChoice == 'Q') {
                        currentPage = 0;
                        break;
                    } else {
                        std::cout << "Error! Please type 'n' or 'q'." << std::endl;
                    }
                }
                break;
            }

            case 3: {
                char prefix[4];
                char ch;
                int score = 0;
                cout << "Enter the first 3 letters of the street name: ";
                cin >> prefix;

                Queue foundRecords;
                binarySearch(sortedRecords, foundRecords, prefix); 

                cout << "Press 't' to create a tree by apartment number: ";
                cin >> ch;

                tree* root = nullptr;

                if (ch == 't' || ch == 'T') {
                    createOptimalSearchTree(root, foundRecords); 
                }

                cout << "Press 's' to search in the tree: ";
                cin >> ch;

                if (ch == 's' || ch == 'S') {
                    searchInTree(root);
                }

                clearTree(root);
                break;
            }

            case 4: {
                std::cout << "Exiting the menu." << std::endl;
                return 0;
            }

            default:
                std::cout << "Invalid choice! Please choose a number between 1 and 5." << std::endl;
                break;
        }
    }
}