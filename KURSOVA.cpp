#include "KURSOVA.h"
#include <iostream>
void displayMenu(KickCompetition& manager) {
    int option;
    KickCompetition competitionManager;

    while (true) {
        system("cls");
        printAscii();
        cout << "Menu:\n";
        cout << "1. Add Athlete\n";
        cout << "2. Show Athletes\n";
        cout << "3. Save Athletes\n";
        cout << "4. Load Athletes\n";
        cout << "5. Sort Athletes by Age Category\n";
        cout << "6. Sort Athletes by Category\n";
        cout << "7. Sort Athletes by Title\n";
        cout << "8. Sort Athletes by Weight Class\n";
        cout << "9. Add Competition\n";
        cout << "10. Remove Competition\n";
        cout << "11.Edit Competition\n";
        cout << "12. Record Result\n";
        cout << "13. Show Competitions\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
        case 1: {
            Athlete athlete;
            cout << "Enter surname: ";
            cin >> athlete.surname;
            cout << "Enter age category: ";
            cin >> athlete.ageCategory;
            cout << "Enter category: ";
            cin >> athlete.category;
            cout << "Enter title: ";
            cin >> athlete.title;
            cout << "Enter weight class: ";
            cin >> athlete.weightClass;
            manager.addAthlete(athlete);
            break;
        }
        case 2:
            manager.showAthletes();
            break;
        case 3: {
            string fileName;
            cout << "Enter file name to save athletes: ";
            cin >> fileName;
            manager.saveAthletes(fileName);
            break;
        }
        case 4: {
            string fileName;
            cout << "Enter file name to load athletes: ";
            cin >> fileName;
            manager.loadAthletes(fileName);
            break;
        }
        case 5:
            manager.sortAthletesByAgeCategory();
            break;
        case 6:
            manager.sortAthletesByCategory();
            break;
        case 7:
            manager.sortAthletesByTitle();
            break;
        case 8:
            manager.sortAthletesByWeightClass();
            break;
        case 9: {
            string type, date;
            cout << "Enter competition type: ";
            cin >> type;
            cout << "Enter competition date: ";
            cin >> date;
            competitionManager.addCompetitionType(type, date);
            break;
        }
        case 10: {
            string type;
            cout << "Enter competition type to remove: ";
            cin >> type;
            competitionManager.removeCompetition(type);
            break;
        }
        case 11: {
            string oldType, newType;
            cout << "Enter old competition type: ";
            cin >> oldType;
            cout << "Enter new competition type: ";
            cin >> newType;
            competitionManager.editCompetition(oldType, newType);
            break;
        }
        case 12: {
            string type, athlete;
            int score;
            cout << "Enter competition type: ";
            cin >> type;
            cout << "Enter athlete name: ";
            cin >> athlete;
            cout << "Enter score: ";
            cin >> score;
            competitionManager.recordResult(type, athlete, score);
            break;
        }
        case 13: {
            competitionManager.showCompetitions();
            break;
        }

        case 0:
            return;
        default:
            cout << "Invalid option. Try again.\n";
        }
        system("pause");
    }
}

int main() {
    KickCompetition manager;
    displayMenu(manager);
    return 0;
}