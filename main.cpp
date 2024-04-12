#include "iostream"
#include "string"
#include <fstream>
using namespace std;


const unsigned char examsAmount = 3;
const unsigned char testsAmount = 5;
int studentsAmount = 0;
const unsigned char studentsArrayLen = 60;
const unsigned char dishesArrayLen = 60;
const unsigned char groupArrayLen = 30;


struct Student{
    string fullName;
    string gender;
    int group;
    int id = 0;
    int exams[examsAmount];
    int tests[testsAmount];
    float averageGrade;
};


//main funcs;

void clearStream() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void showMenu(){
    cout << "1. add new student\n";
    cout << "2. edit student info\n";
    cout << "3. show students\n";
    cout << "4. show students in group\n";
    cout << "5. show top 3 student\n";
    cout << "6. show students amount by gender\n";
    cout << "7. show students's grades info\n";
    cout << "8. show Ks' students\n";
    cout << "9. add students to file\n\n";
    cout << "IDZ\n";
    cout << "10. show canteen menu\n";
    cout << "11. top 3 best dishes\n";
    cout << "12. price less then you choose\n";
    cout << "13. make an order\n";
    cout << "14. add dish\n";
}



// declarations
void addStudentToArray(Student student, Student *students);
int countStudents(Student *students);
int showStudentsByGroup(int groupNum, Student *students, Student *group);
bool isNormalGender(string gender);
int countStudents(Student *students);
float avg( int *exams, int *tests);
Student findStudent(int group, int id, Student *students);

// STUDENTS--------------------------------------------------------------------------------------------

bool isNormalGender(string gender){
    if ( gender == "M" || gender == "F"){
        return true;
    }
    return false;
}

int countStudents(Student *students){
    studentsAmount = 0;
    for (int i = 0; i < studentsArrayLen; i++){
        if (!(students + i)->fullName.empty()){
            studentsAmount ++;
        }
    }
    return studentsAmount;
}


float avg( int *exams, int *tests){
    float sum = 0;
    float res = 0;
    for (int i = 0; i < examsAmount; i++){
        sum += float(*(exams + i));
    }
    for (int i = 0; i < testsAmount; i++){
        sum += float(*(tests + i));
    }
    res=sum/(examsAmount+testsAmount);
    return (res);
}


Student findStudent(int group, int id, Student *students){
    studentsAmount = countStudents(students);
    for (int i = 0; i < studentsAmount; i++ ){
        if ( (( students + i )->group == group) &&  (( students + i )->id == id) ) {
            return *( students + i );
        }
    }
    return Student();
}


void showStudentInfo(Student student){
    cout << "fullname: " << student.fullName <<"\n";
    cout << "group: " << student.group <<"\n";
    cout << "id: " << student.id <<"\n";
    cout << "gender: " << student.gender <<"\n";
    cout << "Exams: \n";
    for ( int i = 0; i < examsAmount; i ++ ){
        cout << student.exams[i] << " ";
    }

    cout << "tests: \n";
    for ( int i = 0; i < testsAmount; i ++ ){
        cout << student.tests[i] << " ";
    }

    cout << "avg Grade: " << student.averageGrade;
    cout << "\n";
}


Student* getAddress(int group, int id, Student *students){

    for (int i = 0; i < countStudents(students); i++){

        if ((students + i)->id == id && (students + i)->group == group){
            return (students + i);
        }
    }
    return nullptr;
}


void editStudent(Student *student, string parametr){ //#2
    string genderParam;

    if ( parametr == "fullname" ){
        cout << "enter new data: "; getline(cin, student->fullName);

    }else if( parametr == "gender" ){
        cout << "enter new data: "; cin >> genderParam; clearStream();
        if ( isNormalGender(genderParam) ){
            student->gender = genderParam;
        }else{
            cout << "unidentified gender, select M or F";
        }

    }else if( parametr == "group" ){
        cout << "enter new data: "; cin >> student->group; clearStream();

    }else if( parametr == "id" ){
        cout << "enter new data: "; cin >> student->id; clearStream();


    }else if( parametr == "exams marks" ){
        cout << "enter new data: ";
        for ( int i = 0; i < examsAmount; i++){
            cin >> student->exams[i];
        }
        clearStream();
        student->averageGrade = avg(student->exams, student->tests);

    }else if( parametr == "tests marks" ){
        cout << "enter new data: ";
        for ( int i = 0; i < testsAmount; i++){
            cin >> student->tests[i];
        }
        clearStream();
        student->averageGrade = avg(student->exams, student->tests);

    }else{
        cout << "this parameter does not exist";
    }
}



void addStudents2File(Student *students){
    ofstream out;
    out.open("/Users/sofiatimosenko/Desktop/studentsList.txt");
    if (out.is_open())
    {
        for ( int i = 0; i < countStudents(students); i++ ){
            out << (students + i)->fullName << endl;
            out << (students + i)->gender << endl;
            out << (students + i)->group << endl;
            out << (students + i)->id << endl;
            out << (students + i)->exams[0];
            for ( int j = 1; j < examsAmount; j++ ){
                out << " " << (students + i)->exams[j];
            }
            out << endl;

            out << (students + i)->tests[0];
            for ( int j = 1; j < testsAmount; j++ ){
                out << " " << (students + i)->tests[j];
            }
            out << endl;
            out << (students + i)->averageGrade << endl;
        }
    }
    else{
        cout << "error";
    }
    out.close();
    cout << "File has been written" << std::endl;
}


bool is_Excellent(Student student){

    for ( int i = 0; i < examsAmount; i++ ){
        if ( student.exams[i] != 5 ){
            return false;
        }
    }

    for ( int i = 0; i < testsAmount; i++ ) {
        if (student.tests[i] != 5) {
            return false;
        }
    }
    return true;
}


bool is_Good(Student student) {

    for (int i = 0; i < examsAmount; i++) {
        if (student.exams[i] == 3 || student.exams[i] == 2) {
            return false;
        }
    }
    for (int i = 0; i < testsAmount; i++) {
        if (student.tests[i] == 3 || student.tests[i] == 2) {
            return false;
        }
    }
    return true;
}
bool is_C_Student(Student student){
    for ( int i = 0; i < examsAmount; i++ ){
        if ( student.exams[i] < 4 ){
            return true;
        }
    }

    for ( int i = 0; i < testsAmount; i++ ) {
        if ( student.tests[i] < 4 ) {
            return true;
        }
    }
    return false;
}


void showStudentsByGrades(Student *students, int grade){

    if ( grade == 5 ){

        for ( int i = 0; i < countStudents(students); i++ ){

            if ( is_Excellent(*(students + i)) ){
                showStudentInfo(*(students + i));
            }

        }

    }else if( grade == 4 ){
        for ( int i = 0; i < countStudents(students); i++ ){
            if ( is_Good( *(students + i)) ){
                showStudentInfo(*(students + i));
            }
        }

    }else{
        for ( int i = 0; i < countStudents(students); i++ ){
            if ( is_C_Student(*(students + i)) ){
                showStudentInfo(*(students + i));
            }
        }
    }

}


void readFile(Student students[]){
    Student student;
    ifstream fin("/Users/sofiatimosenko/Desktop/studentsList.txt");
    if ( !fin.is_open() ){
        cout << "file's not open1";
    }
    else{
        while (fin.peek() != EOF){
            getline(fin, student.fullName);
            getline(fin, student.gender);
            fin >> student.group;
            fin >> student.id;

            for (int i = 0; i < examsAmount; i++) {
                fin >> student.exams[i];
            }
            for (int i = 0; i < testsAmount; i++) {
                fin >> student.tests[i];
            }
            fin >> student.averageGrade;
            fin.get();
            addStudentToArray(student, students);
        }
    }
    fin.close();
}


int showStudentsByGroup(int groupNum, Student *students, Student *group){
    studentsAmount = countStudents(students);
    int index = 0;
    for ( int i = 0; i < studentsAmount; i++ ){
        if( ((students + i)->group) == groupNum ){
            *(group + index) = *(students + i);
            index++;
        }
    }
    return index;
}


void showStudentsByID(int id, Student *students){

    for ( int i = 0 ; i < countStudents(students); i++ ) {
        if ((students + i)->id == id) {
            showStudentInfo(*(students + i));
        }
    }
}


void countStudentsByGender(Student *students){

    int MaleAmount = 0;
    int FemaleAmount = 0;

    for ( int i = 0; i < countStudents(students); i++ ){

        if ( (students + i)->gender == "M") {
            MaleAmount++;
        }else {
            FemaleAmount++;
        }
    }
    cout << "Male amount: " << MaleAmount <<"\n";
    cout << "Female amount: " << FemaleAmount <<"\n";
}

void sortStudentsByGrades(Student *students){
    studentsAmount = countStudents(students);
    for (int i = 0; i < studentsAmount / 2; i++){
        for ( int j = i; j < studentsAmount - i - 1; j++ ){
            if ( (students + j)->averageGrade < (students + j + 1)->averageGrade){
                swap(*(students + j), *(students + j + 1) );
            }
        }
        for ( int j = studentsAmount - 2 - i; j > i + 1; j-- ){
            if ( (students + j)->averageGrade > (students + j + 1)->averageGrade){
                swap(*(students + j), *(students + j - 1) );
            }
        }
    }
}

void addStudentToArray(Student student, Student students[]){
    students[countStudents(students)] = student;
}


// CANTEEN------------------------------------------------------------------------------------------

struct Dish{
    int id;
    string title;
    int weight;
    int price;
    int mark;
};

//funcs;
void showDishInfo(Dish dish){
    cout << "number: " << dish.id <<"\n";
    cout << "title: " << dish.title <<"\n";
    cout << "weight: " << dish.weight <<"\n";
    cout << "price: " << dish.price<<"\n";
    cout << "mark: " << dish.mark <<"\n";
    cout << "\n";
}
int countDishes(Dish *dishes){
    int dishesAmount = 0;
    for (int i = 0; i < dishesArrayLen; i++){
        if (!(dishes + i)->title.empty()){
            dishesAmount ++;
        }else{
            break;
        }
    }
    return dishesAmount;
}
void showDishesByID(int id, Dish *dishes){

    for ( int i = 0 ; i < countDishes(dishes); i++ ) {
        if ((dishes + i)->id == id) {
            showDishInfo(*(dishes + i));
        }
    }
}
void addDishToArray(Dish dish, Dish dishes[]){
    dishes[countDishes(dishes)] = dish;
}


Dish *isDishExists(Dish *dishes, string title){
    for ( int i = 0; i < countDishes(dishes); i++ ){
        if ( (dishes + i)->title == title){
            return (dishes + i);
        }
    }
    return nullptr;
}

void readFile(Dish dishes[]){
    Dish dish;
    ifstream fin("/Users/sofiatimosenko/Desktop/canteen.txt");
    if ( !fin.is_open() ){
        cout << "file's not open2";
    }
    else{
        while (fin.peek() != EOF){
            getline(fin, dish.title);
            fin >> dish.weight;
            fin >> dish.price;
            fin >> dish.mark;
            fin.get();
            addDishToArray(dish, dishes);
        }
    }
    fin.close();
}

void addDish2File(Dish *dishes){
    ofstream out;
    out.open("/Users/sofiatimosenko/Desktop/canteen.txt");
    if (out.is_open())
    {
        for ( int i = 0; i < countDishes(dishes); i++ ){
            out << (dishes + i)->title << endl;
            out << (dishes + i)->weight << endl;
            out << (dishes + i)->price << endl;
            out << (dishes + i)->mark << endl;
        }
    }
    else{
        cout << "error";
    }
    out.close();
    cout << "File has been written" << std::endl;
}


//----------------------------------------------------------------------------------------------------------------------
int main() {
    int index;
    int problem;
    int groupNum, id;
    string editingParam;
    Student students[studentsArrayLen];
    Student group[groupArrayLen];
    Dish dishes[dishesArrayLen];
    Dish *dishPTR;
    string title;
    Student student;
    Dish dish;
    Student *studentPTR;

    readFile(students);
    readFile(dishes);


    for (int repeats = 0; repeats < 100; repeats++) {
        cout << "\n";
        showMenu();
        cout << "choose number: ";
        cin >> problem;
        clearStream();
        cout << "\n";

        switch (problem) {

            case 1:
                cout << "fullName: ";
                getline(cin, student.fullName);
                cout << "gender: ";
                cin >> student.gender;
                clearStream();
                cout << "group: ";
                cin >> student.group;
                clearStream();
                cout << "id: ";
                cin >> student.id;
                clearStream();
                cout << "enter exam's grades by Space: ";
                for (int i = 0; i < examsAmount; i++) cin >> student.exams[i];
                clearStream();
                cout << "enter test's grades by Space: ";
                for (int i = 0; i < testsAmount; i++) cin >> student.tests[i];
                clearStream();
                student.averageGrade = avg(student.exams, student.tests);

                addStudentToArray(student, students);
                break;


            case 2:
                cout << "Edit student info\n";
                cout << "group: ";
                cin >> groupNum;
                clearStream();
                cout << "id: ";
                cin >> id;
                clearStream();
                studentPTR = getAddress(groupNum, id, students);
                if (studentPTR) {
                    if (!studentPTR->fullName.empty()) {
                        cout << "Choose parametr( fullname, gender, group, id, exams marks, tests marks ): ";
                        getline(cin, editingParam);
                        editStudent(studentPTR, editingParam);
                    }
                } else {
                    cout << "this student does not exist\n";
                }
                break;

            case 3:
                cout << "find student:\n";
                cout << "group: ";
                cin >> groupNum;
                clearStream();
                cout << "id: ";
                cin >> id;
                clearStream();
                student = findStudent(groupNum, id, students);
                if (!student.fullName.empty()) {
                    cout << "\n";
                    showStudentInfo(student);
                } else {
                    cout << "student is not found";
                }
                break;

            case 4:
                cout << "find students in group: ";
                cin >> groupNum;
                clearStream();
                cout << "\n";
                index = showStudentsByGroup(groupNum, students, group);
                if (!index) {
                    cout << "no such group";
                } else {
                    for (int i = 0; i < index; i++) {
                        showStudentInfo(group[i]);
                        cout << "\n";
                    }
                }
                break;

            case 5:
                sortStudentsByGrades(students);
                for (int i = 0; i < 3; i++) {
                    showStudentInfo(students[i]);
                    cout << "\n";
                }
                break;

            case 6:
                countStudentsByGender(students);
                cout << "\n";
                break;

            case 7:

                cout << "with high grant: ";
                showStudentsByGrades(students, 5);
                cout << "\n";
                cout << "with regular grant: ";
                cout << "\n";
                showStudentsByGrades(students, 4);
                cout << "\n";
                cout << "without grant: ";
                showStudentsByGrades(students, 3);
                cout << "\n";
                break;

            case 8:
                cout << "enter the number in the group: ";
                cin >> id;
                clearStream();
                showStudentsByID(id, students);
                break;

            case 9:
                cout << "saving changes to a file\n";
                addStudents2File(students);
                break;
            case 10:
                cout <<"MENU:\n";
                for(int i=0; i < 4; i++){
                    showDishInfo(dishes[i]);
                    cout << "\n";
                }
                break;
            case 11:
                cout <<"Top 3:\n";
                for (int i = 0; i < 3; i++) {
                    showDishInfo(dishes[i]);
                    cout << "\n";
                }
                break;
            case 12:
                int C;
                cout << "enter price: ";
                cin >> C;
                for (int i=0; i<countDishes(dishes);i++){
                    if (C>dish.price)
                }

                break;
            case 13:

                break;
            case 14:
                cout << "id: ";
                cin >> dish.id;
                cout <<"title: ";
                getline(cin, dish.title);
                clearStream();
                cout << "weight: ";
                cin >> dish.weight;
                clearStream();
                cout << "price: ";
                cin >> dish.price;
                clearStream();
                cout << "mark: ";
                cin >> dish.mark;
                addDishToArray(dish, dishes);
                cout << "saving changes to a file\n";
                addDish2File(dishes);
                break;
        }
    }
}
