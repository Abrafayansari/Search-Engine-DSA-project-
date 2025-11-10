#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
using namespace std;

void extract_from_files(vector <string>&f){
	for(int i=0;i<f.size();i++){
ifstream file(f[i].c_str());
if (!file) {
    cout << "Error opening file!" << endl;
    
    return;
}
string word;
while (file >> word) {
	for(int j=0;j<word.length();j++){
    	word[j]=tolower(word[j]);
	}
    cout << word << " "<<f[i] << endl;
}

	}
}

int main(){
	vector <string>f;
	f.push_back("t1.txt");
		f.push_back("t2.txt");

		extract_from_files(f);
	
}
