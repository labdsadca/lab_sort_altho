#include<iostream>
#include<vector>
#include<string.h>
#include<fstream>
using namespace std;
vector<string> result;

int compare_id(string s, string s1){
	int i = 0;
	string id = "";
	int x = s.length();
	while(s[i] != ',' && i < x){
		id += s[i];
		i++;
	}
	string id1 = "";
	i = 0;
	x = s1.length();
	while(s1[i] != ',' && i < x){
		id1 += s1[i];
		i++;
	}
	return id.compare(id1);
}

void quick_sort(vector<int> &v, int l, int r){
	if(l >= r) return;
	string pivot = v[rand()%(r - l + 1) + l];
	int i = l, j = r;
	while(i <= j){
		while(compare_id(v[i], pivot) == -1){
			i++;
		}
		while(compare_id(v[j], pivot) == 1){
			j--;
		}
		if(i <= j){
			if(i < j) swap(v[i], v[j]);
			i++; j--;
		}
	}
	quick_sort(v, l, j);
	quick_sort(v, i, r);
}

void write_data_from_vector_into_file(vector<string> &result, ofstream &file_out){
	for(int  i = 0; i < 1000000, i++){
		file_out << result[i];
		if( i != 1000000 - 1){
			file_out << endl;
		}
	}
	result.clear();
	file_out.close();
}

void merge_3file(ifstream &file_1, ifstream &file_2, ifstream &file_3, ofstream &fout){
	string x; getline(file_1, x);
	string y; getline(file_2, y);
	string z; getline(file_3, z);
	while(!file_1.eof() && !file_2.eof() && !file_3.eof()){
		if(compare_id(x, y) != 1 && compare_id(x, z)){
			fout << x << endl;
			getline(file_1, x);
			continue;
		}
		if(compare_id(y, x) != 1 && compare_id(y, z) != 1){
			fout << y << endl;
			getline(file_2, y);
			continue;
		}
		if(compare_id(z, x) != 1 && compare_id(z, y) != 1){
			fout << z << endl;
			getline(file_3, z);
			continue;
		}
	}
	if(file_1.eof()){
		while(!file_2.eof() && !file_3.eof()){
			if(compare_id(y, z) != 1){
				fout << y << endl;
				getline(file_2, y);
			}
			else{
				fout << z << endl;
				getline(file_3, z);
			}
		}
		while(!file_2.eof()){
			fout << y << endl;
			getline(file_2, y);
		}
		while(!file_3.eof()){
			fout << z << endl;
			getline(file_3, z);
		}
	}
	else if(!file_2.eof()){
		while(!file_1.eof() && !file_3.eof()){
			if(compare_id(x, z)  != 1){
				fout << x << endl;
				getline(file_1, x);
			}
			else{
				fout << z << endl;
				getline(file_3, z);
			}
		}
		while(!file_1.eof()){
			fout << x << endl;
			getline(file_1, x);
		}
		while(!file_3.eof()){
			fout << z << endl;
			getline(file_3, z);
		}
	}
	else{
		while(!file_1.eof() && !file_2.eof()){
			if(compare_id(x, y) != 1){
				fout << x << endl;
				getline(file_1, x);
			}
			else{
				fout << y << endl;
				getline(file_3, y);
			}
		}
		while(!file_1.eof()){
			fout << x << endl;
			getline(file_1, x);
		}
		while(!file_2.eof()){
			fout << y << endl;
			getline(file_2, y);
		}
	}
	file_1.close(); file_2.close(); file_3.close();
	fout.close();
}

void merge_2file(ifstream &file_1, ifstream &file_2, ofstream &fout){
	string x; getline(file_1, x);
	string y; getline(file_2, y);
	while(!file_1.eof() && !file_2.eof()){
		if(compare_id(x, y) != 1){
			fout << x << endl;
			getline(file_1, x);
		}
		else{
			fout << y << endl;
			getline(file_2, y);
		}
	}
	while(!file_1.eof()){
		fout << x << endl;
		getline(file_1, x);
	}
	while(!file_2.eof()){
		fout << y << endl;
		getline(file_2, y);
	}
	file_1.close(); file_2.close();
	fout.close();
}

int main(){
	ifstream fin_1, fin_2, fin_3;
	ofstream fout_1;
	string title = "", x;
	fin_1.open("Books_rating.csv", ios::in|ios::binary);
	//lay dong dau tien cua file Books_rating.csv
	getline(fin_1, title);
	//thao tac chia va sort file
	int index = 0, number_file = 1;
	while(!fin_1.eof()){
		index++;
		getline(fin_1, x);
		result.push_back(x);
		if(index == 1000000){
			quicksort(result, 0, index - 1);
			string name_file = "split_file_" + to_string(number_file) + ".csv";
			number_file++;
			fout_1.open(name_file, ios::in|ios::binary);
			//lưu dữ liệu đã sort lên file
			write_data_from_vector_into_file(result, fout_1);
			index = 0;
		}
	}
	//merge du lieu tu ba file da duoc luu truoc do
	fin_1.open("split_file_1.csv", ios::in|ios::binary);
	fin_2.open("split_file_1.csv", ios::in|ios::binary);
	fin_3.open("split_file_1.csv", ios::in|ios::binary);
	fout_1.open("sorted_books_rating.csv", ios::out)
	fout << title << endl;
	merge_3file(fin_1, fin_2, fin_3, fout_1);
	for(int i = 1; i <= 3; i++){
		string name_file = "split_file_" + to_string(i) + ".csv";
		remove(name_file);
	}
}

