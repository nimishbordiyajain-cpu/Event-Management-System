#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string eventName = "Tech Fest";
string eventDate = "25-04-2026";
int maxParticipants = 5;

int countParticipants()
{
    ifstream file("participants.txt");
    string line;
    int count = 0;
    while (getline(file, line))
    {
        if (!line.empty()) count++;
    }
    file.close();
    return count;
}

void viewEventDetails()
{
    cout << "\n===== Event Details =====\n";
    cout << "Event Name: " << eventName << endl;
    cout << "Event Date: " << eventDate << endl;
    cout << "Maximum Participants: " << maxParticipants << endl;
    cout << "Current Participants: " << countParticipants() << endl;
    cout << "Slots Available: " << maxParticipants - countParticipants() << endl;
}

void registerParticipant()
{
    string name, phone;
    string fileName, filePhone;
    bool duplicate = false;

    if (countParticipants() >= maxParticipants)
    {
        cout << "\nEvent Full! Registration Closed.\n";
        return;
    }

    cout << "\nEnter Participant Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Phone Number: ";
    cin >> phone;

    ifstream checkFile("participants.txt");
    string line;
    while (getline(checkFile, line))
    {
        if (line.empty()) continue;
        int lastSpace = line.rfind(' ');
        filePhone = line.substr(lastSpace + 1);
        if (filePhone == phone)
        {
            duplicate = true;
            break;
        }
    }
    checkFile.close();

    if (duplicate)
    {
        cout << "Error: This phone number is already registered.\n";
        return;
    }

    ofstream file("participants.txt", ios::app);
    file << name << " " << phone << endl;
    file.close();

    cout << "Registration Successful\n";
    cout << "Total Participants: " << countParticipants() << endl;
}

void viewParticipants()
{
    ifstream file("participants.txt");
    string line;
    int sr = 1;

    cout << "\n------ Participant List ------\n";
    while (getline(file, line))
    {
        if (line.empty()) continue;
        int lastSpace = line.rfind(' ');
        string name = line.substr(0, lastSpace);
        string phone = line.substr(lastSpace + 1);
        cout << sr++ << ". Name: " << name << " | Phone: " << phone << endl;
    }
    file.close();

    cout << "Total Participants: " << countParticipants() << endl;
}

void cancelRegistration()
{
    string cancelName, cancelPhone;
    bool found = false;

    cout << "\nEnter Name: ";
    cin.ignore();
    getline(cin, cancelName);
    cout << "Enter Phone Number: ";
    cin >> cancelPhone;

    ifstream file("participants.txt");
    ofstream temp("temp.txt");
    string line;

    while (getline(file, line))
    {
        if (line.empty()) continue;
        int lastSpace = line.rfind(' ');
        string name = line.substr(0, lastSpace);
        string phone = line.substr(lastSpace + 1);

        if (name == cancelName && phone == cancelPhone)
        {
            found = true;
            continue;
        }
        temp << line << endl;
    }

    file.close();
    temp.close();
    remove("participants.txt");
    rename("temp.txt", "participants.txt");

    if (found)
    {
        cout << "Registration Cancelled Successfully!\n";
        cout << "Total Participants: " << countParticipants() << endl;
    }
    else
    {
        cout << "Error: Name and phone number not found.\n";
    }
}

int main()
{
    int choice;

    cout << "===== Event Management System =====\n";
    cout << "Event Name: " << eventName << endl;
    cout << "Event Date: " << eventDate << endl;
    cout << "Maximum Participants: " << maxParticipants << endl;

    do
    {
        cout << "\n------ MENU ------\n";
        cout << "1. Register Participant\n";
        cout << "2. Cancel Registration\n";
        cout << "3. View Event Details\n";
        cout << "4. View Participants\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
            registerParticipant();
        else if (choice == 2)
            cancelRegistration();
        else if (choice == 3)
            viewEventDetails();
        else if (choice == 4)
            viewParticipants();
        else if (choice == 5)
            cout << "Exiting Program...\n";
        else
            cout << "Invalid Choice!\n";

    } while (choice != 5);

    return 0;
}
