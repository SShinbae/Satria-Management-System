#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Student {
    int id, age, roomFloor;
    string name, state, department, fees;

};

// Function prototypes
void customSwap(Student& a, Student& b, int& swapCount);
int partition(vector<Student>& students, int low, int high, int& swapCount);
void quickSort(vector<Student>& students, int low, int high, int& swapCount);
void loadStudents(const string& filename, vector<Student>& students);
int binarySearch(const vector<Student>& students, int l, int r, int x);
int linearSearch(const vector<Student>& students, int x);
void displayStudents(const vector<Student>& students, int displayLimit);
void merge(vector<Student>& students, int low, int mid, int high, int& swapCount);
void mergeSort(vector<Student>& students, int low, int high, int& swapCount);
double calculateAverageAge(const vector<Student>& students);
int calculateTotalDept(const vector<Student>& students);

string trim(const string& str);

// Function implementations
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\"");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\"");
    return str.substr(first, (last - first + 1));
}


int partition(vector<Student>& students, int low, int high, int& swapCount) {
    int pivot = students[high].id;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (students[j].id < pivot) {
            i++;
            customSwap(students[i], students[j], swapCount);
        }
    }
    customSwap(students[i + 1], students[high], swapCount);
    return i + 1;
}




/*
-----------------------------------------------------------------------------------
    QUICK SORT FUNCTION
-----------------------------------------------------------------------------------
*/
void quickSort(vector<Student>& students, int low, int high, int& swapCount) {
    if (low < high) {
        int pi = partition(students, low, high, swapCount);
        quickSort(students, low, pi - 1, swapCount);
        quickSort(students, pi + 1, high, swapCount);
    }
}




/*
-----------------------------------------------------------------------------------
    LOAD FILE FUNCTION
-----------------------------------------------------------------------------------
*/
void loadStudents(const string& filename, vector<Student>& students) {
    ifstream ip(filename);
    if (!ip.is_open()) {
        cerr << "Error: File could not be opened" << '\n';
        return;
    }

    string line;
    getline(ip, line); // Skip the header if present

    while (getline(ip, line)) {
        stringstream ss(line);
        Student tempStudent;
        string tempId, tempAge, tempRoomFloor;

        getline(ss, tempId, ',');
        getline(ss, tempStudent.name, ',');
        getline(ss, tempAge, ',');
        getline(ss, tempStudent.state, ',');
        getline(ss, tempStudent.department, ',');
        getline(ss, tempRoomFloor, ',');
        getline(ss, tempStudent.fees, '\n');

        tempStudent.id = stoi(trim(tempId));
        tempStudent.age = stoi(trim(tempAge));
        tempStudent.roomFloor = stoi(trim(tempRoomFloor));
        tempStudent.name = trim(tempStudent.name);
        tempStudent.state = trim(tempStudent.state);
        tempStudent.department = trim(tempStudent.department);
        tempStudent.fees = trim(tempStudent.fees);

        students.push_back(tempStudent); // Add the new student to the vector
    }

    ip.close();
}




/*
-----------------------------------------------------------------------------------
    MERGE FUNCTION
-----------------------------------------------------------------------------------
*/
void merge(vector<Student>& students, int low, int mid, int high, int& swapCount) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    vector<Student> left(n1), right(n2);

    for (int i = 0; i < n1; i++)
        left[i] = students[low + i];
    for (int j = 0; j < n2; j++)
        right[j] = students[mid + 1 + j];

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (left[i].id <= right[j].id) {
            students[k++] = left[i++];
        }
        else {
            students[k++] = right[j++];
            swapCount += n1 - i; // Counting swaps when elements are moved from left to right
        }
    }

    while (i < n1) {
        students[k++] = left[i++];
    }
    while (j < n2) {
        students[k++] = right[j++];
    }

}




/*
-----------------------------------------------------------------------------------
    MERGE SORT FUNCTION
-----------------------------------------------------------------------------------
*/
void mergeSort(vector<Student>& students, int low, int high, int& swapCount) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        mergeSort(students, low, mid, swapCount);
        mergeSort(students, mid + 1, high, swapCount);

        merge(students, low, mid, high, swapCount);
    }

    //cout << "Total Swaps = " << swapCount << endl;
}




/*
-----------------------------------------------------------------------------------
    CALCULATE TOTAL STUDENT FROM DEPT FUNCTION
-----------------------------------------------------------------------------------
*/
int calculateTotalDept(const vector<Student>& students) {
    if (students.empty()) {
        return 0.0; // Return 0 if there are no students
    }

    int ftmkDept = 0;
    int ftkekDept = 0;
    int fpttDept = 0;
    for (const auto& student : students) {
        if (student.department == "FTMK") {
            ftmkDept++;
        }
        else if (student.department == "FTKEK") {
            ftkekDept++;
        }
        else if (student.department == "FPTT") {
            fpttDept++;
        }
    }

    cout << "\nTotal student for FTMK department = " << ftmkDept << endl;
    cout << "Total student for FTKEK department = " << ftkekDept << endl;
    cout << "Total student for FPTT department = " << fpttDept << "\n" << endl;

    return ftmkDept, ftkekDept, fpttDept;
}




/*
-----------------------------------------------------------------------------------
    CALCULATE AVERAGE AGE FUNCTION
-----------------------------------------------------------------------------------
*/
double calculateAverageAge(const vector<Student>& students) {
    if (students.empty()) {
        return 0.0; // Return 0 if there are no students
    }

    int totalAge = 0;
    for (const auto& student : students) {
        totalAge += student.age;
    }

    return static_cast<double>(totalAge) / students.size();
}




/*
-----------------------------------------------------------------------------------
    BINARY SEARCH FUNCTION
-----------------------------------------------------------------------------------
*/
int binarySearch(const Student students[], int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;

        if (students[mid].id == x)
            return mid;

        if (students[mid].id > x)
            return binarySearch(students, l, mid - 1, x);

        return binarySearch(students, mid + 1, r, x);
    }

    return -1;
}




/*
-----------------------------------------------------------------------------------
    LINEAR SEARCH FUNCTION
-----------------------------------------------------------------------------------
*/
int linearSearch(const Student students[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (students[i].id == x) {
            return i;
        }
    }
    return -1;
}




/*
-----------------------------------------------------------------------------------
    SWAP FUNCTION
-----------------------------------------------------------------------------------
*/
void customSwap(Student& a, Student& b, int& swapCount) {
    swap(a, b);  // Swaps the entire Student objects
    swapCount++;
}




/*
-----------------------------------------------------------------------------------
    MERGE SWAP FUNCTION
-----------------------------------------------------------------------------------
*/
int binarySearch(const vector<Student>& students, int l, int r, int x) {
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (students[mid].id == x) {
            return mid;
        }
        else if (students[mid].id < x) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return -1;
}




/*
-----------------------------------------------------------------------------------
    LINEAR SEARCH FUNCTION
-----------------------------------------------------------------------------------
*/
int linearSearch(const vector<Student>& students, int x) {
    for (int i = 0; i < students.size(); ++i) {
        if (students[i].id == x) {
            return i;
        }
    }
    return -1;
}




/*
-----------------------------------------------------------------------------------
    DISPLAY DATA FUNCTION
-----------------------------------------------------------------------------------
*/
void displayStudents(const vector<Student>& students, int displayLimit) {

    const int fieldWidth = 20;
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << "ID\t|Name\t\t\t|Age\t|State\t\t|Department\t|Room Floor\t|Fees\t\t|" << endl;
    /*cout << "ID" << string(fieldWidth - 2, ' ') << "|Name" << string(fieldWidth - 4, ' ')
        << "|Age" << string(fieldWidth - 2, ' ') << "|State" << string(fieldWidth - 6, ' ')
        << "|Department" << string(fieldWidth - 10, ' ') << "|Room Floor" << string(fieldWidth - 10, ' ')
        << "|Fees" << string(fieldWidth - 1, ' ') << "|" << endl;*/
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    int count = 0;
    for (const auto& student : students) {

        if (count >= displayLimit) break;

        if (student.name.length() >= 15) {
            if (student.state.length() > 5) {
                if (student.fees.length() > 5) {
                    cout << student.id << "\t|" << student.name << "\t|" << student.age << "\t|" << student.state << "\t|" << student.department << "\t\t|";
                    cout << student.roomFloor << "\t\t|" << student.fees << "\t|" << endl;
                }
                else {
                    cout << student.id << "\t|" << student.name << "\t|" << student.age << "\t|" << student.state << "\t|" << student.department << "\t\t|";
                    cout << student.roomFloor << "\t\t|" << student.fees << "\t\t|" << endl;
                }

            }
            else {

                if (student.fees.length() > 5) {
                    cout << student.id << "\t|" << student.name << "\t|" << student.age << "\t|" << student.state << "\t\t|" << student.department << "\t\t|";
                    cout << student.roomFloor << "\t\t|" << student.fees << "\t|" << endl;
                }
                else {
                    cout << student.id << "\t|" << student.name << "\t|" << student.age << "\t|" << student.state << "\t\t|" << student.department << "\t\t|";
                    cout << student.roomFloor << "\t\t|" << student.fees << "\t\t|" << endl;
                }
            }
        }
        else {
            if (student.state.length() > 5) {

                if (student.fees.length() > 5) {
                    cout << student.id << "\t|" << student.name << "\t\t|" << student.age << "\t|" << student.state << "\t|" << student.department << "\t\t|";
                    cout << student.roomFloor << "\t\t|" << student.fees << "\t|" << endl;
                }
                else {
                    cout << student.id << "\t|" << student.name << "\t\t|" << student.age << "\t|" << student.state << "\t|" << student.department << "\t\t|";
                    cout << student.roomFloor << "\t\t|" << student.fees << "\t\t|" << endl;
                }
            }
            else {
                if (student.fees.length() > 5) {
                    cout << student.id << "\t|" << student.name << "\t\t|" << student.age << "\t|" << student.state << "\t\t|" << student.department << "\t\t|";
                    cout << student.roomFloor << "\t\t|" << student.fees << "\t|" << endl;
                }
                else {
                    cout << student.id << "\t|" << student.name << "\t\t|" << student.age << "\t|" << student.state << "\t\t|" << student.department << "\t\t|";
                    cout << student.roomFloor << "\t\t|" << student.fees << "\t\t|" << endl;
                }
            }
        }


        /* cout << student.id << string(fieldWidth - to_string(student.id).length(), ' ')
             << "|" << student.name << string(fieldWidth - student.name.length(), ' ')
             << "|" << student.age << string(fieldWidth - to_string(student.age).length(), ' ')
             << "|" << student.state << string(fieldWidth - student.state.length(), ' ')
             << "|" << student.department << string(fieldWidth - student.department.length(), ' ')
             << "|" << student.roomFloor << string(fieldWidth - to_string(student.roomFloor).length(), ' ')
             << "|" << student.fees << string(fieldWidth - student.fees.length(), ' ') << "|" << endl;*/

        count++;
    }
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
}




/*
-----------------------------------------------------------------------------------
    MAIN FUNCTION
-----------------------------------------------------------------------------------
*/

int main() {
    vector<Student> students;
    loadStudents("output2.csv", students);
    int swapCount = 0;
    int numStudents = 0;

    int choice;
    do {
        cout << "----------------------------------------------------------------------------------" << endl;
        cout << "SATRIA MANAGEMENT SYSTEM" << endl;
        cout << "1) Unsort Data" << endl;
        cout << "2) Sorting" << endl;
        cout << "3) Search" << endl;
        cout << "4) Additional Features" << endl;
        cout << "5) Exit" << endl;
        cout << "----------------------------------------------------------------------------------" << endl;
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Unsorted Data" << endl;
            displayStudents(students, min(100, static_cast<int>(students.size())));
            main();
            break;
        }
        case 2: {
            int sortChoice = 0;
            string sortChoiceWord = "";
            do {
                cout << "----------------------------------------------------------------------------------" << endl;
                cout << "Sorting Menu" << endl;
                cout << "1) Quick Sort" << endl;
                cout << "2) Merge Sort" << endl;
                cout << "3) Back" << endl;
                cout << "----------------------------------------------------------------------------------" << endl;
                cout << "\nEnter choice: ";
                cin >> sortChoice;

                swapCount = 0; // Reset swap count before sorting
                switch (sortChoice) {
                case 1:
                    cout << "\nStudents sorted using Quick Sort!" << endl;
                    quickSort(students, 0, students.size() - 1, swapCount); // Pass swapCount here
                    displayStudents(students, min(100, static_cast<int>(students.size())));
                    cout << "Total swaps: " << swapCount << "\n" << endl;
                    main();
                    break;
                case 2:
                    cout << "\nStudents sorted using Merge Sort!" << endl;
                    mergeSort(students, 0, students.size() - 1, swapCount);
                    displayStudents(students, min(100, static_cast<int>(students.size())));
                    cout << "Total swaps: " << swapCount << "\n" << endl;
                    main();
                    break;
                case 3:
                    main();
                default:
                    if (!cin.fail()) {
                        cout << "Please input a valid number!" << "\n" << endl;
                        sortChoiceWord = to_string(sortChoice);
                    }
                    else {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter an integer!" << "\n" << endl;
                        sortChoiceWord = to_string(sortChoice);
                    }
                }

            } while ((sortChoiceWord != "1") && (sortChoiceWord != "2") && (sortChoiceWord != "3"));


        }
        case 3: {
            int searchChoice = 0;
            string searchChoiceWord = "";
            do {
                cout << "----------------------------------------------------------------------------------" << endl;
                cout << "Search Menu" << endl;
                cout << "1) Binary Search" << endl;
                cout << "2) Linear Search" << endl;
                cout << "3) Back" << endl;
                cout << "----------------------------------------------------------------------------------" << endl;
                cout << "Enter choice: ";
                cin >> searchChoice;


                int index = -1;
                if (searchChoice == 1) {
                    cout << "Enter ID to search: ";
                    int idToSearch;
                    cin >> idToSearch;

                    // Make sure students are sorted before binary search
                    quickSort(students, 0, students.size() - 1, swapCount);
                    index = binarySearch(students, 0, students.size() - 1, idToSearch);

                    if (index != -1) {
                        cout << "\nStudent found: " << endl;
                        cout << "ID: " << students[index].id << '\n';
                        cout << "Name: " << students[index].name << '\n';
                        cout << "Age: " << students[index].age << '\n';
                        cout << "Department: " << students[index].department << "\n" << endl;
                        // ... Print other details ...
                    }
                    else {
                        cout << "Student not found." << endl;
                    }
                    main();
                }
                else if (searchChoice == 2) {
                    cout << "Enter ID to search: ";
                    int idToSearch;
                    cin >> idToSearch;

                    index = linearSearch(students, idToSearch);

                    if (index != -1) {
                        cout << "\nStudent found: " << endl;
                        cout << "ID: " << students[index].id << '\n';
                        cout << "Name: " << students[index].name << '\n';
                        cout << "Age: " << students[index].age << '\n';
                        cout << "Department: " << students[index].department << "\n" << endl;
                        // ... Print other details ...
                    }
                    else {
                        cout << "Student not found." << endl;
                    }
                    main();
                }
                else if (searchChoice == 3) {
                    main();
                }
                else {
                    if (!cin.fail()) {
                        cout << "Please input a valid number!" << "\n" << endl;
                        searchChoiceWord = to_string(searchChoice);
                    }
                    else {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter an integer!" << "\n" << endl;
                        searchChoiceWord = to_string(searchChoice);
                    }
                }
            } while ((searchChoiceWord != "1") && (searchChoiceWord != "2") && (searchChoiceWord != "3"));


        }
        case 4: {
            int searchChoice = 0;
            string searchChoiceWord = "";

            do {
                cout << "\n----------------------------------------------------------------------------------" << endl;
                cout << "Additional Features Menu" << endl;
                cout << "1) Calculate Age" << endl;
                cout << "2) Total Student from each department" << endl;
                cout << "3) Back" << endl;
                cout << "----------------------------------------------------------------------------------" << endl;
                cout << "Enter choice: ";
                cin >> searchChoice;

                switch (searchChoice)
                {
                case 1: {
                    // Inside your main function, possibly at the end or wherever you find appropriate
                    double averageAge = calculateAverageAge(students);
                    cout << "\nAverage age of students: " << averageAge << "\n" << endl;
                    main();
                    break;
                }
                case 2: {
                    calculateTotalDept(students);
                    main();
                    break;
                }
                case 3: {
                    main();
                }
                default:
                    if (!cin.fail()) {
                        cout << "Please input a valid number!" << "\n" << endl;
                        searchChoiceWord = to_string(searchChoice);
                    }
                    else {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter an integer!" << "\n" << endl;
                        searchChoiceWord = to_string(searchChoice);
                    }
                }
            } while ((searchChoiceWord != "1") && (searchChoiceWord != "2") && (searchChoiceWord != "3"));


        }
        case 5: {
            break;
        }
        default:
            if (!cin.fail()) {
                cout << "Please input a valid number!" << "\n" << endl;
                main();
            }
            else {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid input. Please enter an integer!" << "\n" << endl;
                main();
            }

        }
    } while (choice == 1 || choice == 2);

}
