#include<iostream>
#include <thread>  
#include <stdexcept> 
using namespace std;
const string RESET = "\033[0m";
const string RED_TEXT = "\033[31m";
const string GREEN_TEXT = "\033[32m";
const string YELLOW_TEXT = "\033[33m";
const string BLUE_TEXT = "\033[34m";
const string CYAN_TEXT = "\033[36m";
const string MAGENTA_TEXT = "\033[35m";
const string BOLD = "\033[1m";
const string UNDERLINE = "\033[4m";

const string BLUE_BG = "\033[44m";
const string YELLOW_BG = "\033[43m";
const string WHITE_BG = "\033[47m";

// Function to clear the screen
void clearScreen() {
    cout << "\033[2J\033[H";
}



struct Pair {
    int first;
    int second;
};
class Relation
{
    int* set;
    int size;
    int totalRelations;
    Pair** cartesian;
    Pair* relations;

public:
    Relation()
    {
        int totalElements;
        cout << "Enter the total number of elements in the set: ";
        cin >> totalElements;
        size = totalElements;
        set = new int[totalElements];
        for (int i = 0; i < totalElements; i++) {
            cout << "Enter Element " << i + 1 << ": ";
            cin >> set[i];
        }

        cout << "Enter the number of relations: ";
        cin >> totalRelations;

        relations = new Pair[totalRelations];
        for (int i = 0; i < totalRelations; i++) {
            cout << "Enter Relation " << i + 1 << " (First Element): ";
            cin >> relations[i].first;
            cout << "Enter Relation " << i + 1 << " (Second Element): ";
            cin >> relations[i].second;
        }
    }

    void CartesianProduct()
    {
        cartesian = new Pair * [size];
        for (int i = 0; i < size; i++)
        {
            cartesian[i] = new Pair[size];
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cartesian[i][j].first = set[i];
                cartesian[i][j].second = set[j];
            }
        }
    }

    bool ReflexiveCheck()
    {
        for (int i = 0; i < size; i++)
        {
            bool found = false;
            for (int j = 0; j < totalRelations; j++)
            {
                if (relations[j].first == set[i] && relations[j].second == set[i])
                {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }
        return true;
    }
    bool IrreflexiveCheck()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < totalRelations; j++)
            {
                if (relations[j].first == set[i] && relations[j].second == set[i])
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool SymmetricCheck()
    {
        for (int i = 0; i < totalRelations; i++)
        {
            int a = relations[i].first;
            int b = relations[i].second;
            bool found = false;
            for (int j = 0; j < totalRelations; j++)
            {
                if (relations[j].first == b && relations[j].second == a)
                {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return false;
            }
        }
        return true;
    }
    bool AntisymmetricCheck() {
        for (int i = 0; i < totalRelations; i++) {
            int a = relations[i].first;
            int b = relations[i].second;
            for (int j = 0; j < totalRelations; j++) {
                if (relations[j].first == b && relations[j].second == a) {
                    if (a != b) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    bool TransitiveCheck() {
        for (int i = 0; i < totalRelations; i++)
        {
            int a = relations[i].first;
            int b = relations[i].second;

            for (int j = 0; j < totalRelations; j++)
            {
                int c = relations[j].second;

                if (b == relations[j].first)
                {
                    bool found = false;

                    for (int k = 0; k < totalRelations; k++)
                    {
                        if (a == relations[k].first && c == relations[k].second)
                        {
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool EquivalenceCheck()
    {
        return ReflexiveCheck() && SymmetricCheck() && TransitiveCheck();
    }

};
class Set
{
    int* set1;
    int* set2;
    int size1;
    int size2;
    Pair** cartesian;
public:
    Set()
    {
        cout << "Enter The Number Of Elemnet in Set 1 :";
        cin >> size1;
        set1 = new int[size1];
        for (int i = 0;i < size1;i++)
        {
            cout << "Enter The Element Numeber " << i + 1 << " : ";
            cin >> set1[i];
        }
        cout << "Enter The Number Of Elemnet in Set 2 :";
        cin >> size2;
        set2 = new int[size2];
        for (int i = 0;i < size2;i++)
        {
            cout << "Enter The Element Numeber " << i + 1 << " : ";
            cin >> set2[i];
        }
    }
    void Union()
    {
        clearScreen();
        int* unionarray = new int[size1 + size2];
        int count = 0;

        // Copy elements from set1 to unionarray
        for (int i = 0; i < size1; i++)
        {
            bool isDuplicate = false;
            for (int j = 0; j < count; j++)
            {
                if (unionarray[j] == set1[i])
                {
                    isDuplicate = true;
                    break;
                }
            }

            if (!isDuplicate)
            {
                unionarray[count] = set1[i];
                count++;
            }
        }

        for (int i = 0; i < size2; i++)
        {
            bool isDuplicate = false;
            for (int j = 0; j < count; j++)
            {
                if (unionarray[j] == set2[i])
                {
                    isDuplicate = true;
                    break;
                }
            }

            if (!isDuplicate)
            {
                unionarray[count] = set2[i];
                count++;
            }
        }

        cout << GREEN_TEXT << "Union Of Sets: { ";
        for (int i = 0; i < count; i++)
        {
            cout << YELLOW_TEXT << unionarray[i] << " ";
        }
        cout << GREEN_TEXT << "}" << endl;

        delete[] unionarray;
    }

    void Intersection()
    {
        clearScreen();
        int* intersectionarray = new int[size1];
        for (int i = 0; i < size1; i++)
        {
            intersectionarray[i] = 0;
        }

        int count = 0;
        for (int i = 0; i < size1; i++)
        {
            for (int j = 0; j < size2; j++)
            {
                if (set1[i] == set2[j])
                {
                    intersectionarray[count] = set1[i];
                    count++;
                }
            }
        }
        cout << GREEN_TEXT << "Intersection of sets: { ";
        for (int i = 0; i < size1; i++)
        {
            if (intersectionarray[i] != 0)
            {
                cout << YELLOW_TEXT << intersectionarray[i] << " ";
            }
        }
        cout << GREEN_TEXT << "}" << endl;

    }
    void Multiplication()
    {
        clearScreen();
        cartesian = new Pair * [size1];
        for (int i = 0; i < size1; i++)
        {
            cartesian[i] = new Pair[size2];
        }
        for (int i = 0; i < size1; i++)
        {
            for (int j = 0; j < size2; j++)
            {
                cartesian[i][j].first = set1[i];
                cartesian[i][j].second = set2[j];
            }
        }
        cout << GREEN_TEXT << " Multiplication Is : " << RED_TEXT << " { ";
        for (int i = 0; i < size1; i++)
        {
            for (int j = 0; j < size2; j++)
            {
                cout << YELLOW_TEXT << "(" << cartesian[i][j].first << ", " << cartesian[i][j].second << ")  ";
            }
            cout << RED_TEXT << " }";
            cout << endl;
        }
    }
    void Difference()
    {
        clearScreen();
        int* differenceArray = new int[size1];
        int count = 0;
        for (int i = 0; i < size1; i++)
        {
            bool foundInSet2 = false;
            for (int j = 0; j < size2; j++)
            {
                if (set1[i] == set2[j])
                {
                    foundInSet2 = true;
                    break;
                }
            }
            if (!foundInSet2)
            {
                differenceArray[count] = set1[i];
                count++;
            }
        }
        cout << GREEN_TEXT << "Set1 - Set2 (A - B) = {";
        for (int i = 0; i < count; i++)
        {
            cout << YELLOW_TEXT << differenceArray[i];
            if (i < count - 1)
            {
                cout << ", ";
            }
        }
        cout << GREEN_TEXT << "}" << endl;

    }

};
void animateLoading() {
    cout << BLUE_TEXT << "Processing";
    for (int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << ".";
        cout.flush();
        if (i % 3 == 0) cout << RESET;
        else if (i % 3 == 1) cout << RED_TEXT;
        else cout << GREEN_TEXT;
    }
    cout << RESET << endl;
}
void printASCIIArt() {
    cout << " ____     ___  _       ____  ______  ____  ___   ____    _____      ____  ____   ___         _____   ___  ______  _____" << endl;
    cout << "|    \\   /  _]| T     /    T|      Tl    j/   \\ |    \\  / ___/     /    T|    \\ |   \\       / ___/  /  _]|      T/ ___/" << endl;
    cout << "|  D  ) /  [_ | |    Y  o  ||      | |  TY     Y|  _  Y(   \\_     Y  o  ||  _  Y|    \\     (   \\_  /  [_ |      (   \\_ " << endl;
    cout << "|    / Y    _]| l___ |     |l_j  l_j |  ||  O  ||  |  | \\__  T    |     ||  |  ||  D  Y     \\__  TY    _]l_j  l_j\\__  T" << endl;
    cout << "|    \\ |   [_ |     T|  _  |  |  |   |  ||     ||  |  | /  \\ |    |  _  ||  |  ||     |     /  \\ ||   [_   |  |  /  \\ |" << endl;
    cout << "|  .  Y|     T|     ||  |  |  |  |   j  ll     !|  |  | \\    |    |  |  ||  |  ||     |     \\    ||     T  |  |  \\    |" << endl;
    cout << "l__j\\_jl_____jl_____jl__j__j  l__j  |____j\\___/ l__j__j  \\___j    l__j__jl__j__jl_____j      \\___jl_____j  l__j   \\___j" << endl;
}

int main() {
    int choice;

    clearScreen();
    printASCIIArt();
    cout << WHITE_BG << BLUE_TEXT << "Welcome to the Set and Relation Operations Program!" << RESET << endl;

    do {
        cout << CYAN_TEXT << "Choose an option:" << RESET << endl;
        cout << "1. Relations" << endl;
        cout << "2. Sets" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            clearScreen();
            Relation r;
            int relationChoice;

            cout << BLUE_BG << CYAN_TEXT << "Relation Operations:" << RESET << endl;

            do {
                cout << "1. Check Reflexive" << endl;
                cout << "2. Check Irreflexive" << endl;
                cout << "3. Check Symmetric" << endl;
                cout << "4. Check Antisymmetric" << endl;
                cout << "5. Check Transitive" << endl;
                cout << "6. Check Equivalence" << endl;
                cout << "7. Back to the main menu" << endl;
                cout << "Enter your choice: ";
                cin >> relationChoice;

                try {
                    switch (relationChoice) {
                    case 1:
                        clearScreen();
                        printASCIIArt();
                        animateLoading();
                        if (r.ReflexiveCheck()) {
                            cout << GREEN_TEXT << "The relation is reflexive." << RESET << endl;
                        }
                        else {
                            cout << RED_TEXT << "The relation is not reflexive." << RESET << endl;
                        }
                        break;
                    case 2:
                        clearScreen();
                        printASCIIArt();
                        animateLoading();
                        if (r.IrreflexiveCheck()) {
                            cout << GREEN_TEXT << "The relation is irreflexive." << RESET << endl;
                        }
                        else {
                            cout << RED_TEXT << "The relation is not irreflexive." << RESET << endl;
                        }
                        break;
                    case 3:
                        clearScreen();
                        printASCIIArt();
                        animateLoading();
                        if (r.SymmetricCheck()) {
                            cout << GREEN_TEXT << "The relation is symmetric." << RESET << endl;
                        }
                        else {
                            cout << RED_TEXT << "The relation is not symmetric." << RESET << endl;
                        }
                        break;
                    case 4:
                        clearScreen();
                        printASCIIArt();
                        animateLoading();
                        if (r.AntisymmetricCheck()) {
                            cout << GREEN_TEXT << "The relation is antisymmetric." << RESET << endl;
                        }
                        else {
                            cout << RED_TEXT << "The relation is not antisymmetric." << RESET << endl;
                        }
                        break;
                    case 5:
                        clearScreen();
                        printASCIIArt();
                        animateLoading();
                        if (r.TransitiveCheck()) {
                            cout << GREEN_TEXT << "The relation is transitive." << RESET << endl;
                        }
                        else {
                            cout << RED_TEXT << "The relation is not transitive." << RESET << endl;
                        }
                        break;
                    case 6:
                        clearScreen();
                        printASCIIArt();
                        animateLoading();
                        if (r.EquivalenceCheck()) {
                            cout << GREEN_TEXT << "The relation is an equivalence relation." << RESET << endl;
                        }
                        else {
                            cout << RED_TEXT << "The relation is not an equivalence relation." << RESET << endl;
                        }
                        break;
                    case 7:
                        clearScreen();
                        printASCIIArt();
                        cout << "Returning to the main menu." << endl;
                        break;
                    default:
                        clearScreen();
                        cout << RED_TEXT << "Invalid choice. Please try again." << RESET << endl;
                    }
                }
                catch (exception& e) {
                    clearScreen();
                    cerr << RED_TEXT << "Error: " << e.what() << RESET << endl;
                }
            } while (relationChoice != 7);
            break;
        }
        case 2: {
            clearScreen();
            printASCIIArt();
            Set s1;
            int setChoice;

            cout << BLUE_BG << CYAN_TEXT << "Set Operations:" << RESET << endl;

            do {
                cout << RESET << "1. Union" << endl;
                cout << "2. Intersection" << endl;
                cout << "3. Multiplication" << endl;
                cout << "4. Difference" << endl;
                cout << "5. Back to the main menu" << endl;
                cout << "Enter your choice: ";
                cin >> setChoice;

                try {
                    switch (setChoice) {
                    case 1:
                        clearScreen();
                        printASCIIArt();
                        animateLoading();
                        s1.Union();
                        break;
                    case 2:
                        clearScreen();
                        animateLoading();
                        s1.Intersection();
                        break;
                    case 3:
                        clearScreen();
                        printASCIIArt();
                        animateLoading();
                        s1.Multiplication();
                        break;
                    case 4:
                        clearScreen();
                        printASCIIArt();
                        animateLoading();
                        s1.Difference();
                        break;
                    case 5:
                        clearScreen();
                        printASCIIArt();
                        cout << "Returning to the main menu." << endl;
                        break;
                    default:
                        clearScreen();
                        printASCIIArt();
                        cout << RED_TEXT << "Invalid choice. Please try again." << RESET << endl;
                    }
                }
                catch (exception& e) {
                    clearScreen();
                    printASCIIArt();
                    cerr << RED_TEXT << "Error: " << e.what() << RESET << endl;
                }
            } while (setChoice != 5);
            break;
        }
        case 3:
            clearScreen();
            printASCIIArt();
            cout << BLUE_BG << CYAN_TEXT << "Exiting the program." << RESET << endl;
            break;
        default:
            clearScreen();
            printASCIIArt();
            cout << RED_TEXT << "Invalid choice. Please try again." << RESET << endl;
        }
    } while (choice != 3);

    return 0;
}