#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

struct Athlete {
    string surname;
    string ageCategory;
    string category;
    string title;
    string weightClass;
};

struct Competition {
    string type;
    string date;
    map<string, int> results;
};

class KickboxingCompetition {
private:
    vector<Athlete> athletes;
    vector<Competition> competitions;

public:
    void addCompetitionType(const string& type, const string& date);
    void removeCompetition(const string& type);
    void editCompetition(const string& oldType, const string& newType);
    void recordResult(const string& type, const string& athlete, int score);
    void addAthlete(const Athlete& athlete);
    void showAthletes();

    void saveAthletes(const string& fileName);
    void loadAthletes(const string& fileName);

    void sortAthletesByAgeCategory();
    void sortAthletesByCategory();
    void sortAthletesByTitle();
    void sortAthletesByWeightClass();
};

void KickboxingCompetition::addCompetitionType(const string& type, const string& date) {
    competitions.push_back({ type, date, {} });
    cout << "Competition type \"" << type << "\" added successfully.\n";
}

void KickboxingCompetition::removeCompetition(const string& type) {
    auto it = remove_if(competitions.begin(), competitions.end(),
        [&type](const Competition& c) { return c.type == type; });
    if (it != competitions.end()) {
        competitions.erase(it, competitions.end());
        cout << "Competition \"" << type << "\" removed successfully.\n";
    }
    else {
        cout << "Competition \"" << type << "\" not found.\n";
    }
}

void KickboxingCompetition::editCompetition(const string& oldType, const string& newType) {
    for (auto& competition : competitions) {
        if (competition.type == oldType) {
            competition.type = newType;
            cout << "Competition \"" << oldType << "\" renamed to \"" << newType << "\" successfully.\n";
            return;
        }
    }
    cout << "Competition \"" << oldType << "\" not found.\n";
}

void KickboxingCompetition::recordResult(const string& type, const string& athlete, int score) {
    for (auto& competition : competitions) {
        if (competition.type == type) {
            competition.results[athlete] += score;
            cout << "Result recorded: " << athlete << " -> " << score << " points.\n";
            return;
        }
    }
    cout << "Competition \"" << type << "\" not found.\n";
}

void KickboxingCompetition::addAthlete(const Athlete& athlete) {
    athletes.push_back(athlete);
    cout << "Athlete \"" << athlete.surname << "\" added successfully.\n";
}

void KickboxingCompetition::showAthletes() {
    cout << "List of Athletes:\n";
    for (const auto& athlete : athletes) {
        cout << "Surname: " << athlete.surname
            << ", Age Category: " << athlete.ageCategory
            << ", Category: " << athlete.category
            << ", Title: " << athlete.title
            << ", Weight Class: -" << athlete.weightClass << "\n";
    }
}

void KickboxingCompetition::saveAthletes(const string& fileName) {
    ofstream file(fileName);
    if (!file) {
        cerr << "Error opening file for saving athletes.\n";
        return;
    }

    for (const auto& athlete : athletes) {
        file << athlete.surname << ","
            << athlete.ageCategory << ","
            << athlete.category << ","
            << athlete.title << ","
            << athlete.weightClass << "\n";
    }

    file.close();
    cout << "Athletes saved successfully to " << fileName << ".\n";
}

void KickboxingCompetition::loadAthletes(const string& fileName) {
    string fileToLoad = (fileName.empty() || fileName == "/") ? "athletes.txt" : fileName;
    ifstream file(fileToLoad);
    if (!file) {
        cerr << "Error opening file for loading athletes.\n";
        return;
    }

    athletes.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);

        Athlete athlete;
        athlete.surname = line.substr(0, pos1);
        athlete.ageCategory = line.substr(pos1 + 1, pos2 - pos1 - 1);
        athlete.category = line.substr(pos2 + 1, pos3 - pos2 - 1);
        athlete.title = line.substr(pos3 + 1, pos4 - pos3 - 1);
        athlete.weightClass = line.substr(pos4 + 1);

        athletes.push_back(athlete);
    }

    file.close();
    cout << "Athletes loaded successfully from " << fileToLoad << ".\n";
}

void KickboxingCompetition::sortAthletesByAgeCategory() {
    sort(athletes.begin(), athletes.end(),
        [](const Athlete& a, const Athlete& b) {
            return a.ageCategory < b.ageCategory;
        });
    cout << "Athletes sorted by age category.\n";
}

void KickboxingCompetition::sortAthletesByCategory() {
    sort(athletes.begin(), athletes.end(),
        [](const Athlete& a, const Athlete& b) {
            return a.category < b.category;
        });
    cout << "Athletes sorted by category.\n";
}

void KickboxingCompetition::sortAthletesByTitle() {
    sort(athletes.begin(), athletes.end(),
        [](const Athlete& a, const Athlete& b) {
            return a.title < b.title;
        });
    cout << "Athletes sorted by title.\n";
}

void KickboxingCompetition::sortAthletesByWeightClass() {
    sort(athletes.begin(), athletes.end(),
        [](const Athlete& a, const Athlete& b) {
            int weightA = stoi(a.weightClass);
            int weightB = stoi(b.weightClass);
            return weightA < weightB;
        });
    cout << "Athletes sorted by weight class.\n";
}

void displayMenu(KickboxingCompetition& manager) {
    int option;

    while (true) {
        system("cls");
        cout << "Menu:\n";
        cout << "1. Add Athlete\n";
        cout << "2. Show Athletes\n";
        cout << "3. Save Athletes\n";
        cout << "4. Load Athletes\n";
        cout << "5. Sort Athletes by Age Category\n";
        cout << "6. Sort Athletes by Category\n";
        cout << "7. Sort Athletes by Title\n";
        cout << "8. Sort Athletes by Weight Class\n";
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
        case 0:
            return;
        default:
            cout << "Invalid option. Try again.\n";
        }
        system("pause");
    }
}


