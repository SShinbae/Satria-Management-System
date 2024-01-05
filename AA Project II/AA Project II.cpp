#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    int id, age, roomFloor;
    string name, state, department,fees;
};
//function
void quickSort(vector<Student>& students, int low, int high);
void loadStudents(const string& filename, vector<Student>& students);
void mergeSort(vector<Student>& students, int low, int high);
int binarySearch(const vector<Student>& students, const string& name);
int quickSearch(const vector<Student>& students, const string& name);
void displayStudents(const vector<Student>& students, int count);
// Function to trim whitespace from the start and end of a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

// Partition function used by QuickSort
int partition(vector<Student>& students, int low, int high) {
    string pivot = students[high].name;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (students[j].name.compare(pivot) < 0) {
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

//get student from CSV file
void loadStudents(const string& filename, vector<Student>& students)
{
    ifstream ip(filename);
    if (!ip.is_open()) {
        cerr << "Error: File could not be opened" << '\n';
        return;
    }

    string line;
    getline(ip, line); // Skip the header if present

    while (getline(ip, line)) {
        stringstream ss(line);
        Student student;
        string tempId, tempAge, tempRoomFloor;

        getline(ss, tempId, ',');
        getline(ss, student.name, ',');
        getline(ss, tempAge, ',');
        getline(ss, student.state, ',');
        getline(ss, student.department, ',');
        getline(ss, tempRoomFloor, ',');
        getline(ss, student.fees, '\n');

        student.id = stoi(trim(tempId));
        student.name = trim(student.name);
        student.age = stoi(trim(tempAge));
        student.state = trim(student.state);
        student.department = trim(student.department);
        student.roomFloor = stoi(trim(tempRoomFloor));
        student.fees = trim(student.fees);

        students.push_back(student);
    }

    ip.close();
}

// QuickSort function
void quickSort(vector<Student>& students, int low, int high) {
    if (low < high) {
        int pi = partition(students, low, high);
        quickSort(students, low, pi - 1);
        quickSort(students, pi + 1, high);
    }
}
void mergeSort(vector<Student>& students, int low, int high)
{
}
int binarySearch(const vector<Student>& students, const string& name)
{
    return 0;
}
int quickSearch(const vector<Student>& students, const string& name)
{
    return 0;
}
void displayStudents(const vector<Student>& students, int count)
{
    for (int i = 0; i < count && i < students.size(); ++i) {
        cout << "ID: " << students[i].id << '\n';
        cout << "Name: " << students[i].name << '\n';
        cout << "Age: " << students[i].age << '\n';
        cout << "State: " << students[i].state << '\n';
        cout << "Department: " << students[i].department << '\n';
        cout << "Room Floor: " << students[i].roomFloor << '\n';
        cout << "Fees: " << students[i].fees << '\n';
        cout << "______________________________" << '\n';
    }
}




void homeMenu() {
    cout << "\nSatria Management System" << endl;
    cout << "1) Sorting" << endl;
    cout << "2) Search" << endl;
    cout << "Enter choice: ";
}

//sortingMenu
void sortingMenu(vector<Student>& students) {
    if (students.empty()) {
        loadStudents("output1.csv", students); // Load students from file
    }

    int choice;
    cout << "Sorting Menu" << endl;
    cout << "1) Quick Sort" << endl;
    cout << "2) Merge Sort" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        quickSort(students, 0, students.size() - 1);
        displayStudents(students, min(100, static_cast<int>(students.size())));
        cout << "Students sorted using Quick Sort!" << endl;
        break;
    /*case 2:
        mergeSort(students, 0, students.size() - 1);
        cout << "Students sorted using Merge Sort!" << endl;
        displayStudents(students, min(100, static_cast<int>(students.size())));
        break;*/
    default:
        cout << "Invalid choice. Returning to main menu." << endl;
    }
}
//SearchMenu
void searchMenu(vector<Student>& students) {
    int choice;
    string name;
    cout << "Search Menu" << endl;
    cout << "1) Binary Search" << endl;
    cout << "2) Quick Search" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    cout << "Enter name to search: ";
    cin >> name;

    int index;
    switch (choice) {
    case 1:
        index = binarySearch(students, name);
        break;
    case 2:
        index = quickSearch(students, name);
        break;
    default:
        cout << "Invalid choice. Returning to main menu." << endl;
        return;
    }

    if (index != -1) {
        cout << "Student found: " << endl;
        cout << "ID: " << students[index].id << '\n';
        cout << "Name: " << students[index].name << '\n';
        // ... Print other details ...
    }
    else {
        cout << "Student not found." << endl;
    }

}

int main() {
    vector<Student> students;
    // ... Code to fill students from file ...

    int choice;
    do {
        homeMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            sortingMenu(students);
            break;
            /*case 2:
                searchMenu(students);
                break;*/
        default:
            cout << "Exiting Satria Management System." << endl;
        }
    } while (choice == 1 || choice == 2);
    return 0;
}
