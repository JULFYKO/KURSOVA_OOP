#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct Athlete {
    string surname;
    string ageCategory;
    string category;
    string title;
    string weightClass;
};


class KickCompetition {
private:
    vector<Athlete> athletes;
    
    struct Competition {
        string type;
        string date;
        unordered_map<string, int> results;
    };
    vector<Competition> competitions;
public:
    void addCompetitionType(const string& type, const string& date);
    void removeCompetition(const string& type);
    void editCompetition(const string& oldType, const string& newType);
    void recordResult(const string& type, const string& athlete, int score);
    void showCompetitions();
    void addAthlete(const Athlete& athlete);
    void showAthletes();
    void saveAthletes(const string& fileName);
    void loadAthletes(const string& fileName);
    void sortAthletesByAgeCategory();
    void sortAthletesByCategory();
    void sortAthletesByTitle();
    void sortAthletesByWeightClass();
};

void KickCompetition::addCompetitionType(const string& type, const string& date) {
    competitions.push_back({ type, date, {} });
    cout << "Competition type \"" << type << "\" added successfully.\n";
}

void KickCompetition::removeCompetition(const string& type) {
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

void KickCompetition::editCompetition(const string& oldType, const string& newType) {
    for (auto& competition : competitions) {
        if (competition.type == oldType) {
            competition.type = newType;
            cout << "Competition \"" << oldType << "\" renamed to \"" << newType << "\" successfully.\n";
            return;
        }
    }
    cout << "Competition \"" << oldType << "\" not found.\n";
}

void KickCompetition::recordResult(const string& type, const string& athlete, int score) {
    for (auto& competition : competitions) {
        if (competition.type == type) {
            competition.results[athlete] += score;
            cout << "Result recorded: " << athlete << " -> " << score << " points.\n";
            return;
        }
    }
    cout << "Competition \"" << type << "\" not found.\n";
}
void KickCompetition::showCompetitions() {
    if (competitions.empty()) {
        cout << "No competitions available.\n";
        return;
    }

    for (const auto& competition : competitions) {
        cout << "Competition Type: " << competition.type << "\n";
        cout << "Date: " << competition.date << "\n";
        if (competition.results.empty()) {
            cout << "No results yet.\n";
        }
        else {
            cout << "Results:\n";
            for (const auto& result : competition.results) {
                cout << result.first << ": " << result.second << " points\n";
            }
        }
        cout << "-------------------------\n";
    }
}

void KickCompetition::addAthlete(const Athlete& athlete) {
    athletes.push_back(athlete);
    cout << "Athlete \"" << athlete.surname << "\" added successfully.\n";
}

void KickCompetition::showAthletes() {
    cout << "List of Athletes:\n";
    for (const auto& athlete : athletes) {
        cout << "Surname: " << athlete.surname
            << ", Age Category: " << athlete.ageCategory
            << ", Category: " << athlete.category
            << ", Title: " << athlete.title
            << ", Weight Class: -" << athlete.weightClass << "\n";
    }
}

void KickCompetition::saveAthletes(const string& fileName) {
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

void KickCompetition::loadAthletes(const string& fileName) {
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

void KickCompetition::sortAthletesByAgeCategory() {
    sort(athletes.begin(), athletes.end(),
        [](const Athlete& a, const Athlete& b) {
            return a.ageCategory < b.ageCategory;
        });
    cout << "Athletes sorted by age category.\n";
}

void KickCompetition::sortAthletesByCategory() {
    sort(athletes.begin(), athletes.end(),
        [](const Athlete& a, const Athlete& b) {
            return a.category < b.category;
        });
    cout << "Athletes sorted by category.\n";
}

void KickCompetition::sortAthletesByTitle() {
    sort(athletes.begin(), athletes.end(),
        [](const Athlete& a, const Athlete& b) {
            return a.title < b.title;
        });
    cout << "Athletes sorted by title.\n";
}

void KickCompetition::sortAthletesByWeightClass() {
    sort(athletes.begin(), athletes.end(),
        [](const Athlete& a, const Athlete& b) {
            int weightA = stoi(a.weightClass);
            int weightB = stoi(b.weightClass);
            return weightA < weightB;
        });
    cout << "Athletes sorted by weight class.\n";
}
void printAscii() {
    cout << R"(
         :::::::::::      :::    :::       :::        ::::::::::    :::   :::       :::    :::       ::::::::
            :+:          :+:    :+:       :+:        :+:           :+:   :+:       :+:   :+:       :+:    :+:
           +:+          +:+    +:+       +:+        +:+            +:+ +:+        +:+  +:+        +:+    +:+
          +#+          +#+    +:+       +#+        :#::+::#        +#++:         +#++:++         +#+    +:+
         +#+          +#+    +#+       +#+        +#+              +#+          +#+  +#+        +#+    +#+
    #+# #+#          #+#    #+#       #+#        #+#              #+#          #+#   #+#       #+#    #+#
    #####            ########        ########## ###              ###          ###    ###       ########

)";
}