#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Db
{
public:

    string way;
    vector <string> col;
    vector < vector <string> > matrix;

    Db(){

    }

    void updateColAndMatrix(){
        string a;
        ifstream fin;
        fin.open(way.c_str());
        if (!fin.is_open()){
            cout << "No db" << endl;
            return;
        }
        getline(fin, a);
        // cout << a << endl << a << endl;

        string b = "";
        for (int i = 0; i < a.size(); i++){
            if (a[i] != ' ') b += a[i];
            else {
                col.push_back(b);
                b = "";
            }
        }
        if (b != "")col.push_back( b);

        /*for (int i = 0; i < col.size(); i++){
            cout << col[i] << endl;
        }*/

        int c = 0;
        while (!fin.eof()) {
            b = "";
            getline(fin, a);
            vector <string> v;

            for (int i = 0; i < a.size(); i++){
                if (a[i] != ' ') b += a[i];
                else {
                    v.push_back(b);
                    b = "";
                }
            }
            if (b != "")v.push_back( b);

            matrix.push_back(v);
            /*
            for (int i = 0; i < col.size(); i++){
                cout << col[i] << endl;
            }
            */
        }

        /*
        for (int i = 0; i < matrix.size(); i++){
            for (int q = 0; q < matrix[i].size(); q++){
                cout << matrix[i][q] << " ";
            }
            cout << endl;
        }
        */
    }

    void print(){
        for (int i = 0; i < col.size(); i++){
            cout << setw(13) << col[i];
        }
        cout << endl;

        for (int i = 0; i < matrix.size(); i++){
            for (int q = 0; q < matrix[i].size(); q++){
                cout << setw(13) << matrix[i][q];
            }
            cout << endl;
        }
    }

    bool save(){
        ofstream fout;
        fout.open(way);

        for (int i = 0; i < col.size(); i++){
            fout << col[i] << " ";
        }
        fout << endl;

        for (int i = 0; i < matrix.size(); i++){
            for (int q = 0; q < matrix[i].size(); q++){
                fout << matrix[i][q] << " ";
            }
            if (i != matrix.size() - 1){
                fout << endl;
            }
        }
    }
};

Db studentsDb;
Db marksDb;
Db subjDb;

int main()
{

    studentsDb.way = "students.txt";
    marksDb.way = "marks.txt";
    subjDb.way = "subj.txt";

    studentsDb.updateColAndMatrix();
    marksDb.updateColAndMatrix();
    subjDb.updateColAndMatrix();

    cout << "Hello User!" << endl;

    while(true) {
        cout << "Select The command" << endl;
        cout << "1) print db" << endl; // +
        cout << "2) add new row" << endl; // +
        cout << "3) delete row" << endl; // +
        cout << "4) change value // beta" << endl;
        cout << "5) exit programme" << endl; // +

        string a;
        cin >> a;

        if (a == "1"){
            cout << "Select db:" <<endl;
            cout << "1) students " << endl;
            cout << "2) marks" << endl;
            cout << "3) subj" << endl;
            cout << "4) all" << endl;
            int b;
            cin >> b;
            if (b == 1){
                studentsDb.print();
            }
            else if (b == 2){
                marksDb.print();
            }
            else if (b == 3){
                subjDb.print();
            }
            else if (b == 4){
                studentsDb.print();
                cout << endl;
                marksDb.print();
                cout << endl;
                subjDb.print();
            }
        }
        else if (a == "2"){
            cout << "Select db:" <<endl;
            cout << "1) students " << endl;
            cout << "2) marks" << endl;
            cout << "3) subj" << endl;
            int b;
            cin >> b;
            if (b == 1){
                string name, secondName, age;
                cout << "enter name" << endl;
                cin >> name;
                cout << "enter secondName" << endl;
                cin >> secondName;
                cout << "enter age" <<endl;
                cin >> age;

                // cout << studentsDb.matrix.size() << endl;
                // cout << studentsDb.matrix[studentsDb.matrix.size()-1][0] << endl;

                int lastId = atoi(studentsDb.matrix[studentsDb.matrix.size()-1][0].c_str());
                vector <string> v;
                v.push_back(to_string(lastId + 1));
                v.push_back(name);
                v.push_back(secondName);
                v.push_back(age);

                studentsDb.matrix.push_back(v);
                studentsDb.save();
            }
            else if (b == 2){
                string studID, subjId, mark;
                cout << "enter student id" << endl;
                cin >> studID;
                cout << "enter subject id" << endl;
                cin >> subjId;
                cout << "enter mark" <<endl;
                cin >> mark;

                // cout << studentsDb.matrix.size() << endl;
                // cout << studentsDb.matrix[studentsDb.matrix.size()-1][0] << endl;

                int lastId = atoi(marksDb.matrix[marksDb.matrix.size()-1][0].c_str());
                vector <string> v;
                v.push_back(to_string(lastId + 1));
                v.push_back(studID);
                v.push_back(subjId);
                v.push_back(mark);

                marksDb.matrix.push_back(v);
                marksDb.save();
            }
            else if (b == 3){
                string subN;
                cout << "enter subject name" << endl;
                cin >> subN;

                // cout << studentsDb.matrix.size() << endl;
                // cout << studentsDb.matrix[studentsDb.matrix.size()-1][0] << endl;

                int lastId = atoi(subjDb.matrix[subjDb.matrix.size()-1][0].c_str());
                vector <string> v;
                v.push_back(to_string(lastId + 1));
                v.push_back(subN);

                subjDb.matrix.push_back(v);
                subjDb.save();
            }
        }
        else if (a == "3"){
            cout << "Select db:" <<endl;
            cout << "1) students " << endl;
            cout << "2) marks" << endl;
            cout << "3) subj" << endl;
            int b, id;
            cin >> b;
            cout << "enter id" << endl;
            cin >> id;

            if (b == 1){
                vector < vector < string > > newV;
                for (int i = 0; i < studentsDb.matrix.size(); i++){
                    if (atoi(studentsDb.matrix[i][0].c_str()) != id)
                        newV.push_back(studentsDb.matrix[i]);
                }
                studentsDb.matrix = newV;
                studentsDb.save();
            }
            else if (b == 2){
                vector < vector < string > > newV;
                for (int i = 0; i < marksDb.matrix.size(); i++){
                    if (atoi(marksDb.matrix[i][0].c_str()) != id)
                        newV.push_back(marksDb.matrix[i]);
                }
                marksDb.matrix = newV;
                marksDb.save();
            }
            else if (b == 3){
                vector < vector < string > > newV;
                for (int i = 0; i < subjDb.matrix.size(); i++){
                    if (atoi(subjDb.matrix[i][0].c_str()) != id)
                        newV.push_back(subjDb.matrix[i]);
                }
                subjDb.matrix = newV;
                subjDb.save();
            }
        }
        else if (a == "4"){
            cout << "Select db:" <<endl;
            cout << "1) students " << endl;
            cout << "2) marks" << endl;
            cout << "3) subj" << endl;
            int b;
            cin >> b;
            cout << "Select colunm" << endl;
            if (b == 1){
                cout << "1) name" << endl;
                cout << "2) second_name" << endl;
                cout << "3) age" << endl;
                int c;
                cin >> c;
                cout << "enter new value" << endl;
                string newVal;
                cin >> newVal;
                if (c == 1){
                    //studentsDb.matrix[] =
                }
                else if (c == 2) {

                }
                else if (c == 3){

                }
            }
            else if (b == 2){
                cout << "1) id_st" << endl;
                cout << "2) id_sub" << endl;
                cout << "3) mark" << endl;
                int c;
                cin >> c;
                cout << "enter new value" << endl;
                string newVal;
                cin >> newVal;
                if (c == 1){

                }
                else if (c == 2) {

                }
                else if (c == 3){

                }
            }
            else if (b == 3){
                cout << "1) subj_name" << endl;
                int c;
                cin >> c;
                cout << "enter new value" << endl;
                string newVal;
                cin >> newVal;
                if (c == 1){

                }
            }
        }
        else if (a == "5"){
            break;
        }
    }

    cout << "Bye, User" << endl;
    return 0;
}
