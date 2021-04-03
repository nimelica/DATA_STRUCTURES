#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include <map>
using namespace std;

class Book
{
public:
	//Setters
	void SetGenre(const string& newGenre) { genre = newGenre; }
	void SetTitle(const string& newTitle) { title = newTitle; }
	void SetAuthor(const string& newAuthor) { author = newAuthor; }
	void SetYear(const int& newYear) { year = newYear; }

	//Getters
	string GetGenre()const { return genre; }
	string GetTitle()const { return title; }
	string GetAuthor()const { return author; }
	int GetYear()const { return year; }

private:
	string genre;
	string title;
	string author;
	int year;
};

void Trim(string& data){
	data.erase(remove(data.begin(), data.end(), ' '), data.end());
}

void PrintData(vector<Book>& BooksVector)
{
	for (int i = 0; i < BooksVector.size(); i++){
		cout << "{genre:" << BooksVector[i].GetGenre() << ",title:" << BooksVector[i].GetTitle()
			<< ",author:" << BooksVector[i].GetAuthor() << ",year:" << BooksVector[i].GetYear() << "}\n";
	}
}

void ReadBySpaces() {
	ifstream fin("input.txt");
	int size;  fin >> size;
	string line = "", s_now = "";
	vector<string>vec;
	char space = ' ';

	while (getline(fin, line)) {
		if (!line.empty()) {
			while (size--) {
				int spaceIndex = line.find(space);
				s_now = line.substr(0, spaceIndex);
				line = line.substr(spaceIndex + 1);
				spaceIndex = line.find(space); //second space 

				vec.push_back(s_now);
			}
		}
	}
}

int getNumOfLineInFile(string filename)
{
	ifstream input;
	int lines;
	string line;

	input.open(filename);
	if (input.is_open()) {
		for (lines = 0; getline(input, line); lines++);
		input.close();
	}
	else {
		cout << "Could not open file " << filename << std::endl;
		exit(-1);
	}
	input.close();

	return lines;
}


void FileIntoQueue() { //READ FILE FROM AT THE END 
	//read the file
	ifstream fin("input.txt");
	if (!fin) { cerr << "FILE NOT FOUND!\n"; }

	string duty, strTime, line;
	char space = ' ';
	double time{};
	int posi;

	priority_queue<pair<string, double>>prique;

	//priority_queue<pair<string, double>>priq;
	while (getline(fin, line)) {
		if (line == " ") continue; //remove empty lines

		//find last space
		posi = (int)line.size() - 1;
		while (line[posi] != space) posi--;
		duty = line.substr(0, posi);
		strTime = line.substr(posi + 1);
		time = stod(strTime);

		//priq.push(make_pair(duty, time));
		prique.push({ duty, time });
		//or prique.push(make_pair(durt, time))
	}

	while (!prique.empty()) {
		cout << prique.top().first << " " << endl;
		prique.pop();
	}
}

void ReadFileIntoMap() {
	map<string, int>ordered_fruits;
	fstream fin("mapInput.txt");
	if (!fin) { cerr << "ERROR: FILE NOT FOUND!\n"; }
	int size{}; fin >> size;
	string fruit = "";

	for (size_t i = 0; i < size; i++) {
		fin >> fruit;
		auto freq = ordered_fruits.find(fruit);
		if (freq == ordered_fruits.end()) { //fruit count is only one since we do not encounter with same fruit again
			ordered_fruits[fruit] = 1;
		}
		else { //we found same fruit
			//freq->second++;
			ordered_fruits[fruit]++;
			cout << freq->first << " is already exists, incrementing count->" << freq->second << " " << endl;
		}
	}
	map<string, int>::iterator it;
	it = ordered_fruits.begin();
	for (; it != ordered_fruits.end(); it++) {
		cout << it->first << ": " << it->second << endl;
	}

	for (auto& it : ordered_fruits) {
		cout << it.first << ": " << it.second << endl;
	}
}

void ReadVector() {
	int i = 0;
	int size = 0;
	ifstream fin("input.txt");
	Book book;
	string sentence, genre, genreCat, title, titleCat, author, authorCat, year, yearCat;

	vector<Book>BooksVector;

	//Read File
	while (getline(fin, sentence)) //->read file by using delimetersand struct
	{
		if (sentence.empty()) continue;
		istringstream stream(sentence);

		bool spelled = false;

		if (sentence.find("genre") && sentence.find("title") && sentence.find("author") && sentence.find("year"))
		{
			stream.get();
			getline(stream, genreCat, ':');
			Trim(genreCat);
			if (genreCat == "genre") spelled = true;
			getline(stream, genre, ',');
			Trim(genre);
			book.SetGenre(genre);

			getline(stream, titleCat, ':');
			Trim(titleCat);
			if (titleCat == "title") spelled = true;
			getline(stream, title, ',');
			Trim(title);
			book.SetTitle(title);

			getline(stream, authorCat, ':');
			Trim(authorCat);
			if (authorCat == "author") spelled = true;
			getline(stream, author, ',');
			Trim(author);
			book.SetAuthor(author);

			getline(stream, yearCat, ':');
			Trim(yearCat);
			if (yearCat == "year") spelled = true;
			getline(stream, year, '}');
			Trim(year);
			book.SetYear(stoi(year));

			//Push datas in a vector
			BooksVector.push_back(book);
		}
	}
}


