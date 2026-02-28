#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream name_score(filename);
    char line[200];

    while(name_score.getline(line,200)){
        char name[100];
        int s1,s2,s3;
        int sum;

        sscanf(line,"%[^:]: %d %d %d", name, &s1, &s2, &s3);
        sum = s1+s2+s3;

        char grade = score2grade(sum);

        names.push_back(name);
        scores.push_back(sum);
        grades.push_back(grade);
        // cout << name <<"," <<sum<<"," << grade <<endl;
    }

    name_score.close();
}

void getCommand(string &command, string &key){

    string line;
    cout<<"Please input your command: ";
    getline(cin,line);

    char cmd[50] , arg[100];

    int n = sscanf(line.c_str(), "%s %[^\n]" , cmd ,arg);
    command = toUpperStr(cmd);

    if(n == 2) key = toUpperStr(arg);
    else key = "";
}




void searchName(vector<string> &names, vector<int> &scores, vector<char> &grade,string key){
    bool check = false;

    cout << "---------------------------------\n";

    for(size_t  i = 0; i < names.size() ; i++){
        string n = toUpperStr(names[i]);
        string k = toUpperStr(key);
        if(n == k){
            cout<<names[i]<<"'s score = "<<scores[i]<<endl;
            cout<<names[i]<<"'s grade = "<<grade[i]<<endl;
            check = true;
            break;
        }
    }

    if(!check){
        cout<<"Cannot found.\n";
    }


    cout << "---------------------------------\n";
    
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades,string key){
    bool check = false;

    cout << "---------------------------------\n";

    for(size_t  i = 0; i < names.size() ; i++){
        if(grades[i] == key[0]){
            cout<<names[i]<<" ("<<scores[i]<<")"<<endl;
            check = true;
        }
    }

    if(!check){
        cout<<"Cannot found.\n";
    }


    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
