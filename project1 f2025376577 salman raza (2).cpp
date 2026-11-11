#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student
{
    string name;
    string regNo;
    int marks[5];
    float average;
    char grade;

    void calcResult();
    void display();
};

// Function Prototypes
void enterStudents(Student batch[], int size);
Student* findTopper(Student* ptr, int size);
void saveToFile(Student batch[], int size);
void loadFromFile();

int main()
{
    Student batch[5];
    Student *topper;
    Student *extra = NULL;

    int choice;

    do
    {
        cout << "\n========== STUDENT RESULT MANAGEMENT SYSTEM ==========\n";
        cout << "1. Enter Students\n";
        cout << "2. Show All Results\n";
        cout << "3. Show Topper\n";
        cout << "4. Save To File\n";
        cout << "5. Load From File\n";
        cout << "6. Extra Student (Dynamic Memory)\n";
        cout << "7. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
        case 1:
            enterStudents(batch,5);

            for(int i=0;i<5;i++)
                batch[i].calcResult();

            cout << "\nData Entered Successfully.\n";
            break;

        case 2:
            for(int i=0;i<5;i++)
                batch[i].display();
            break;

        case 3:
            topper = findTopper(batch,5);

            cout << "\n***** TOPPER *****\n";
            topper->display();
            break;

        case 4:
            saveToFile(batch,5);
            break;

        case 5:
            loadFromFile();
            break;

        case 6:
            extra = new Student;

            cout << "\nEnter Extra Student Name: ";
            cin.ignore();
            getline(cin,extra->name);

            cout << "Enter Registration Number: ";
            getline(cin,extra->regNo);

            cout << "Enter Marks of 5 Subjects:\n";
            for(int i=0;i<5;i++)
            {
                cout << "Subject " << i+1 << ": ";
                cin >> extra->marks[i];
            }

            extra->calcResult();

            cout << "\nExtra Student Result\n";
            extra->display();

            delete extra;
            extra = NULL;

            cout << "\nMemory Deleted Successfully.\n";
            break;

        case 7:
            cout << "\nProgram Ended.\n";
            break;

        default:
            cout << "Invalid Choice.\n";
        }

    }while(choice!=7);

    return 0;
}

// Member Function
void Student::calcResult()
{
    int sum=0;

    for(int i=0;i<5;i++)
        sum += marks[i];

    average = sum/5.0;

    if(average>=80)
        grade='A';
    else if(average>=65)
        grade='B';
    else if(average>=50)
        grade='C';
    else if(average>=40)
        grade='D';
    else
        grade='F';
}

// Member Function
void Student::display()
{
    cout << "\n---------------------------------\n";
    cout << "Name : " << name << endl;
    cout << "Registration No : " << regNo << endl;

    cout << "Marks : ";
    for(int i=0;i<5;i++)
        cout << marks[i] << " ";

    cout << "\nAverage : " << average;
    cout << "\nGrade : " << grade << endl;
    cout << "---------------------------------\n";
}

// Input Function
void enterStudents(Student batch[], int size)
{
    cin.ignore();

    for(int i=0;i<size;i++)
    {
        cout << "\nStudent " << i+1 << endl;

        cout << "Enter Name: ";
        getline(cin,batch[i].name);

        cout << "Enter Registration Number: ";
        getline(cin,batch[i].regNo);

        cout << "Enter Marks of 5 Subjects:\n";

        for(int j=0;j<5;j++)
        {
            cout << "Subject " << j+1 << ": ";
            cin >> batch[i].marks[j];
        }

        cin.ignore();
    }
}

// Pointer Function
Student* findTopper(Student* ptr,int size)
{
    Student *top = ptr;

    for(int i=1;i<size;i++)
    {
        if((ptr+i)->average > top->average)
            top = ptr+i;
    }

    return top;
}

// File Write Function
void saveToFile(Student batch[], int size)
{
    ofstream file("results.txt");

    if(!file)
    {
        cout << "File cannot be opened.\n";
        return;
    }

    for(int i=0;i<size;i++)
    {
        file << batch[i].name << ",";
        file << batch[i].regNo << ",";

        for(int j=0;j<5;j++)
            file << batch[i].marks[j] << ",";

        file << batch[i].average << ",";
        file << batch[i].grade << endl;
    }

    file.close();

    cout << "\nData Saved Successfully.\n";
}

// File Read Function
void loadFromFile()
{
    ifstream file("results.txt");

    if(!file)
    {
        cout << "\nFile does not exist.\n";
        return;
    }

    string line;

    cout << "\n===== FILE DATA =====\n";

    while(getline(file,line))
    {
        cout << line << endl;
    }

    file.close();
}
