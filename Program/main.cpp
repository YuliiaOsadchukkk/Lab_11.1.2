
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void write_file(fstream& f) 
{
	f.seekp(0, ios::beg);
	float tmp;
	char ch;
	do
	{
		cout << "enter digit: "; cin >> tmp;
		f.write((char*)&tmp, sizeof(float));
		cout << "continue? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
}

void draw_file(fstream& f) {	
	f.clear();
	f.seekg(0, ios_base::beg);
	float tmp;
	while (!f.eof()) {
		f.read((char*)&tmp, sizeof(float));
		if (f.eof())
			break;
		cout << tmp << endl;
	}
}
	
void change(fstream& in, fstream& out) {
	in.clear();
	in.seekg(0, ios::beg);
	out.seekp(0, ios::beg);
	int tmp;
	while (!in.eof()) {
		in.read((char*)&tmp, sizeof(float));
		if (in.eof())
			break;
		if (tmp > 0.)
			out.write((char*)&tmp, sizeof(float));
	}
}

void main() {
	string t;

	cout << "Input in filename: "; cin >> t;

	fstream fin(t, ios::in | ios::binary);
	if (!fin.is_open())
	{
		fin.open(t, ios::in | ios::out | ios::trunc | ios::binary);
		if (fin.is_open())
			write_file(fin);
		else {
			cout << "Incorrect in file name!";
			return;
		}
	}

	cout << "Input out filename: "; cin >> t;
	fstream fout(t, ios::in | ios::out | ios::trunc | ios::binary);
	if (fout.is_open()) {
		change(fin, fout);
		draw_file(fout);
		fout.close();
	}
	else cout << "Incorrect out file name!";
	fin.close();
}