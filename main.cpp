#include <iostream>
#include <fstream>
using namespace std;

class Shelter {
private:
    struct Pet {
        string name;
        string type;
        string color;
        int id;
        int days_in_shelter;
    };
    
    Pet pets[100]; // Array to store up to 100 pets
    int num_of_pets;

public:
    Shelter() {
        num_of_pets = 0;
    }
    void menu() {
        int choice;
        do {
            cout << "\n1. Load Shelter\n2. Add Pet\n3. Oldest Resident\n4. Save\n5. Exit\nEnter choice: ";
            cin >> choice;
            if (choice == 1) {
                string filename;
                cout << "Enter filename: ";
                cin >> filename;
                loadFromFile(filename);
            } else if (choice == 2) {
                addPet();
            } else if (choice == 3) {
                findOldestResident();
            } else if (choice == 4) {
                string filename;
                cout << "Enter filename: ";
                cin >> filename;
                saveToFile(filename);
            }
        } while (choice != 5);
    }

    void loadFromFile(string filename) {
        ifstream file(filename);
        if (file.fail()) {
            cout << "Error opening file! Starting with an empty shelter.\n";
            return;
        }
        while (file >> pets[num_of_pets].name >> pets[num_of_pets].id >> pets[num_of_pets].type >> pets[num_of_pets].color >> pets[num_of_pets].days_in_shelter) {
            if (num_of_pets < 10) {
                pets[num_of_pets].days_in_shelter++; // Increment days
                num_of_pets++;
            }
        }
        file.close();
        cout << "Shelter loaded successfully! (Days in shelter incremented)\n";
    }

    void addPet() {
        if (num_of_pets >= 10) {
            cout << "Shelter is full! Cannot add more pets.\n";
            return;
        }
        cout << "Enter Pet Name: "; cin >> pets[num_of_pets].name;
        cout << "Enter Pet ID: "; cin >> pets[num_of_pets].id;
        cout << "Enter Pet Type: "; cin >> pets[num_of_pets].type;
        cout << "Enter Pet Color: "; cin >> pets[num_of_pets].color;
        pets[num_of_pets].days_in_shelter = 0;
        num_of_pets++;
        cout << "Pet added successfully!\n";
    }

    void findOldestResident() {
        if (num_of_pets == 0) {
            cout << "No pets in the shelter!\n";
            return;
        }
        Pet* oldest = &pets[0];
        for (int i = 1; i < num_of_pets; i++) {
            if (pets[i].days_in_shelter > oldest->days_in_shelter) {
                oldest = &pets[i];
            }
        }
        cout << "Oldest resident: \n";
        cout << "ID: " << oldest->id << ", Name: " << oldest->name << ", Type: " << oldest->type << ", Color: " << oldest->color << ", Days in Shelter: " << oldest->days_in_shelter << endl;
    }

    void saveToFile(string filename) {
        ofstream file(filename);
        if (file.fail()) {
            cout << "Error opening file!\n";
            return;
        }
        for (int i = 0; i < num_of_pets; i++) {
            file << pets[i].name << " " << pets[i].id << " " << pets[i].type << " " << pets[i].color << " " << pets[i].days_in_shelter << endl;
        }
        file.close();
        cout << "Shelter data saved!\n";
    }


};

int main() {
    cout << "Welcome to the Pet Shelter!\n";
    cout << "Would you like to use the system? (y/n): ";
    char response;
    cin >> response;
    if (response == 'y') {
        Shelter shelter;
        shelter.menu();
    }
    cout << "Thank you! Goodbye!\n";
    return 0;
}