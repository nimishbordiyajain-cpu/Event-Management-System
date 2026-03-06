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
    string name, phone;
    int count = 0;

    while (file >> name >> phone)
    {
        count++;
    }

    file.close();
    return count;
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
    cin >> name;

    cout << "Enter Phone Number: ";
    cin >> phone;

    ifstream checkFile("participants.txt");

    while (checkFile >> fileName >> filePhone)
    {
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

    cout << "Participant Registered Successfully!\n";
}

void viewParticipants()
{
    ifstream file("participants.txt");
    string name, phone;

    cout << "\n------ Participant List ------\n";

    while (file >> name >> phone)
    {
        cout << "Name: " << name << " | Phone: " << phone << endl;
    }

    file.close();
}

void cancelRegistration()
{
    string cancelName, cancelPhone;
    string name, phone;
    bool found = false;

    cout << "\nEnter Name: ";
    cin >> cancelName;

    cout << "Enter Phone Number: ";
    cin >> cancelPhone;

    ifstream file("participants.txt");
    ofstream temp("temp.txt");

    while (file >> name >> phone)
    {
        if (name == cancelName && phone == cancelPhone)
        {
            found = true;
            continue; // delete only this exact record
        }

        temp << name << " " << phone << endl;
    }

    file.close();
    temp.close();

    remove("participants.txt");
    rename("temp.txt", "participants.txt");

    if (found)
        cout << "Registration Cancelled Successfully!\n";
    else
        cout << "Error: Name and phone number not found.\n";
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
        cout << "3. View Participants\n";
        cout << "4. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            registerParticipant();
        }
        else if (choice == 2)
        {
            cancelRegistration();
        }
        else if (choice == 3)
        {
            viewParticipants();
        }
        else if (choice == 4)
        {
            cout << "Exiting Program...\n";
        }
        else
        {
            cout << "Invalid Choice!\n";
        }

    } while (choice != 4);

    return 0;
}