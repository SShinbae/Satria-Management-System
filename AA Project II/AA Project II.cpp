#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct Student {
    int id, age, roomFloor;
    string name, state, department, fees;
};

const int MAX_STUDENTS = 10000;  // Adjust the size according to your needs

// Function prototypes
void customSwap(Student& a, Student& b, int& swapCount);
void quickSort(Student students[], int low, int high, int& swapCount);
void loadStudents(const string& filename, Student students[], int& numStudents);
int binarySearch(const Student students[], int l, int r, int x);
int linearSearch(const Student students[], int n, int x);
void displayStudents(const Student students[], int count);

// Function to trim whitespace from the start and end of a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

int partition(Student students[], int low, int high, int& swapCount) {
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

void customSwap(Student& a, Student& b, int& swapCount) {
    swap(a.id, b.id);
    swapCount++;
}

void quickSort(Student students[], int low, int high, int& swapCount) {
    if (low < high) {
        int pi = partition(students, low, high, swapCount);
        quickSort(students, low, pi - 1, swapCount);
        quickSort(students, pi + 1, high, swapCount);
    }
}

void loadStudents(const string& filename, Student students[], int& numStudents) {
    ifstream ip(filename);
    if (!ip.is_open()) {
        cerr << "Error: File could not be opened" << '\n';
        return;
    }

    string line;
    getline(ip, line); // Skip the header if present

    while (getline(ip, line) && numStudents < MAX_STUDENTS) {
        stringstream ss(line);
        string tempId, tempAge, tempRoomFloor;

        getline(ss, tempId, ',');
        getline(ss, students[numStudents].name, ',');
        getline(ss, tempAge, ',');
        getline(ss, students[numStudents].state, ',');
        getline(ss, students[numStudents].department, ',');
        getline(ss, tempRoomFloor, ',');
        getline(ss, students[numStudents].fees, '\n');

        students[numStudents].id = stoi(trim(tempId));
        students[numStudents].name = trim(students[numStudents].name);
        students[numStudents].age = stoi(trim(tempAge));
        students[numStudents].state = trim(students[numStudents].state);
        students[numStudents].department = trim(students[numStudents].department);
        students[numStudents].roomFloor = stoi(trim(tempRoomFloor));
        students[numStudents].fees = trim(students[numStudents].fees);

        numStudents++;
    }

    ip.close();
}

void merge(Student students[], int low, int mid, int high, int& swapCount) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    Student* left = new Student[n1];
    Student* right = new Student[n2];

    for (int i = 0; i < n1; i++)
        left[i] = students[low + i];
    for (int j = 0; j < n2; j++)
        right[j] = students[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = low;

    while (i < n1 && j < n2) {
        if (left[i].id <= right[j].id) {
            students[k++] = left[i++];
        }
        else {
            students[k++] = right[j++];
            swapCount += n1 - i;  // Increment swap count for every element moved from the left to the right
        }
    }

    while (i < n1) {
        students[k++] = left[i++];
    }
    while (j < n2) {
        students[k++] = right[j++];
    }

    delete[] left;
    delete[] right;
}

void mergeSort(Student students[], int low, int high, int& swapCount) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        mergeSort(students, low, mid, swapCount);
        mergeSort(students, mid + 1, high, swapCount);

        merge(students, low, mid, high, swapCount);
    }
}

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

int linearSearch(const Student students[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (students[i].id == x) {
            return i;
        }
    }
    return -1;
}

void displayStudents(const Student students[], int count) {
    const int fieldWidth = 20;  // Adjust the width according to your needs

    cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "ID" << string(fieldWidth - 2, ' ') << "|Name" << string(fieldWidth - 4, ' ')
        << "|Age" << string(fieldWidth - 2, ' ') << "|State" << string(fieldWidth - 6, ' ')
        << "|Department" << string(fieldWidth - 10, ' ') << "|Room Floor" << string(fieldWidth - 10, ' ')
        << "|Fees" << string(fieldWidth - 1, ' ') << "|" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < count; ++i) {
        cout << students[i].id << string(fieldWidth - to_string(students[i].id).length(), ' ')
            << "|" << students[i].name << string(fieldWidth - students[i].name.length(), ' ')
            << "|" << students[i].age << string(fieldWidth - to_string(students[i].age).length(), ' ')
            << "|" << students[i].state << string(fieldWidth - students[i].state.length(), ' ')
            << "|" << students[i].department << string(fieldWidth - students[i].department.length(), ' ')
            << "|" << students[i].roomFloor << string(fieldWidth - to_string(students[i].roomFloor).length(), ' ')
            << "|" << students[i].fees << string(fieldWidth - students[i].fees.length(), ' ') << "|" << endl;
    }
    cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
}

int main() {
    Student students[MAX_STUDENTS];
    int numStudents = 0;
    int swapCount = 0;  // Global variable to track total swaps

    int choice;
    do {
        cout << "\nSatria Management System" << endl;
        cout << "1) Sorting" << endl;
        cout << "2) Search" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            if (numStudents == 0) {
                loadStudents("output2.csv", students, numStudents);
            }

            int sortChoice;
            cout << "Sorting Menu" << endl;
            cout << "1) Quick Sort" << endl;
            cout << "2) Merge Sort" << endl;
            cout << "Enter choice: ";
            cin >> sortChoice;

            swapCount = 0;  // Reset swap count

            switch (sortChoice) {
            case 1:
                cout << "\nStudents sorted using Quick Sort!" << endl;
                quickSort(students, 0, numStudents - 1, swapCount);
                displayStudents(students, min(100, numStudents));
                cout << "Total swaps: " << swapCount << endl;
                break;
            case 2:
                cout << "\nStudents sorted using Merge Sort!" << endl;
                mergeSort(students, 0, numStudents - 1, swapCount);
                displayStudents(students, min(100, numStudents));
                cout << "Total swaps: " << swapCount << endl;
                break;
            default:
                cout << "Invalid choice. Returning to the main menu." << endl;
            }
        } break;
        case 2: {
            if (numStudents == 0) {
                loadStudents("output2.csv", students, numStudents); // Load students from file
            }

            int searchChoice;
            string name;
            cout << "Search Menu" << endl;
            cout << "1) Binary Search" << endl;
            cout << "2) Linear Search" << endl;
            cout << "Enter choice: ";
            cin >> searchChoice;

            switch (searchChoice) {
            case 1: {
                cout << "Enter ID to search: ";
                int idToSearch;
                cin >> idToSearch;

                int index = binarySearch(students, 0, numStudents - 1, idToSearch);

                if (index != -1) {
                    cout << "Student found: " << endl;
                    cout << "ID: " << students[index].id << '\n';
                    cout << "Name: " << students[index].name << '\n';
                    // ... Print other details ...
                }
                else {
                    cout << "Student not found." << endl;
                }

            } break;
            case 2: {
                cout << "Enter ID to search: ";
                int idToSearch;
                cin >> idToSearch;

                int index = linearSearch(students, numStudents, idToSearch);

                if (index != -1) {
                    cout << "Student found: " << endl;
                    cout << "ID: " << students[index].id << '\n';
                    cout << "Name: " << students[index].name << '\n';
                    // ... Print other details ...
                }
                else {
                    cout << "Student not found." << endl;
                }
            } break;
            default:
                cout << "Invalid choice. Returning to main menu." << endl;
            }
        } break;
        default:
            cout << "Exiting Satria Management System." << endl;
        }
    } while (choice == 1 || choice == 2);

    return 0;
}
