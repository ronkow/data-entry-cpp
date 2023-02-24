#include "search.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define DATA_PATH "C:\\your_path\\data-entry-and-search-cpp\\data\\data.csv"

//-----------------
// RETRIEVE RECORDS
// PRINT RECORDS
//-----------------

void retrieve_all_data(string filepath)
{
	string line, token;
	ifstream myfile(DATA_PATH);
	
	cout << '\n'; 
	cout << "ALL RECORDS" << '\n';
	cout << "-----------" << '\n';
	cout << "NAME\tGENDER\tBIRTH YEAR" << '\n';
	
	if (myfile.is_open()) {			
	
		while (getline(myfile, line, '\n')) {
	
        	if (line.substr(0, 4) != "name") {
                istringstream line2(line);
			 
			    while (getline(line2, token, ',')) {   
			        cout << token << '\t';
			    }
				cout << '\n';
			}
		}
		myfile.close();
	}
}


//-----------------
// SAVE RECORDS
//-----------------

void save_record(vector<string> records)
{
	ofstream myfile(DATA_PATH, ios::app);
	
	if (myfile.is_open()) {
		
		for (auto record: records){
            myfile << record << '\n';
		}
		myfile.close();
	}	
}

//-----------------
// ENTER RECORD
//-----------------

string enter_name()
{
	string name;
	
	cout << "Enter the name:" << '\n';
    cin >> name;
	
	return name;
}


string enter_gender()
{
	string gender;
	
	cout << "Enter the gender:" << '\n';
    cin >> gender;
	
	transform(gender.begin(), gender.end(), gender.begin(), ::toupper);
	
	while (gender != "M" && gender != "F") {
	    cout << "Invalid entry. Enter a gender m or f:" << '\n';
	    cin >> gender;
	}
	
	return gender;
}


string enter_birthyear()
{
	string year;
	int y;
	
	cout << "Enter the birth year:" << '\n';
    cin >> year;
	stringstream(year) >> y;
	
	while (y < 1960 || y > 2022){
	    cout << "Invalid entry. Enter a year from 1960 to 2022:" << '\n';
	    cin >> year;
	    stringstream(year) >> y;
	}
	
	return year;
}


string enter_another_record()
{
	string yes_no;
		
	cout << '\n';
	cout << "Do you want to enter another record? (y/n)" << '\n';
	cin >> yes_no;
	cout << '\n';
    
	while (yes_no != "y" && yes_no != "Y" && yes_no != "n" && yes_no != "N") {
	    cout << "Invalid entry. Enter y or n:" << '\n';
		cin >> yes_no;
	}
	
	return yes_no;
}


// TODO: VALIDATE NAME
vector<string> enter_record()
{
	string name, gender, birthyear, record, yes_no;
    vector<string> records;
		
	cout << '\n';
	cout << "DATA ENTRY" << '\n';
	cout << "----------" << '\n';
	
	name = enter_name();
	gender = enter_gender();
	birthyear = enter_birthyear();
	
	record = name + ',' + gender + ',' + birthyear;
    records.push_back(record);

	yes_no = enter_another_record();
	
	while (yes_no == "y" || yes_no == "Y") {
	   	name = enter_name();
	    gender = enter_gender();
	    birthyear = enter_birthyear();
		
	    record = name + ',' + gender + ',' + birthyear;
		records.push_back(record);
		
		yes_no = enter_another_record();
	}
	
    cout << '\n';	
	cout << "RECORDS ENTERED" << '\n';
	cout << "---------------" << '\n';

    // TODO: IMPROVE OUTPUT FORMAT
    for (auto record: records){
        cout << record << '\n';
	}	
	return records;
}

//-----------------
// USER OPTIONS
//-----------------

string select_option()
{
    string  x;
	
	cout << '\n';
    cout << "STUDENT DATASTORE" << '\n';
    cout << "-----------------" << '\n';
    cout << "Select an option" << '\n';
    cout << "1. Retrieve all records" << '\n';
    cout << "2. Enter records" << '\n';
	cout << "3. Search for records" << '\n';
    cout << "4. Quit" << '\n';
    cin >> x;
    
	while (x != "1" && x != "2" && x != "3" && x != "4") {		
        cout << "Invalid entry. Enter 1, 2, 3 or 4:" << '\n';
        cin >> x;
    }
	
    return x;
}

//------------------
//MAIN
//------------------

int main() 
{
    string x;
	vector<string> records;

    while (true) {
        
        x = select_option();

        if (x == "1") {
            retrieve_all_data(DATA_PATH);
        }
        else if (x == "2") {
            records = enter_record();
            save_record(records);
        }
        else if (x == "3") {
            search();
        }
        else {
            return 0;
        }        
    }
    return 0;
}
