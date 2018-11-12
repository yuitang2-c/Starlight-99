#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class node {
public:
	string tconst;
	string titleType;
	string primaryTitle;
	string startYear;
	string runtimeMinutes;
	//I need a counter for genres
	int genresCounter;
	string* genres;
	node* next;
public:
	node(string tconst, string titleType, string primaryTitle, string startYear, string runtimeMinutes, string genres) {
		this->tconst = tconst;
		this->titleType = titleType;
		this->primaryTitle = primaryTitle;
		this->startYear = startYear;
		this->runtimeMinutes = runtimeMinutes;
		this->next = NULL;
		//process genres
		int genresNo = 1;
		for (int i = 0; i < genres.size(); i++) {
			if (genres[i] == 44)	genresNo++;
		}
		this->genres = new string[genresNo];
		string soloGenres;
		//debug message
		//cout << genres << endl;
		int readGenresInOrder = 0;
		for (int i = 0; i < genres.size(); i++) {
			if (genres[i] == 44 || (genres[i] == 34 && i != 0)) {
				this->genres[readGenresInOrder].assign(soloGenres);
				readGenresInOrder = readGenresInOrder + 1;
				//debug message
				//cout << soloGenres << endl;
				soloGenres.erase();
			}
			else if (genres[i + 1] == NULL) {
				soloGenres += genres[i];
				this->genres[readGenresInOrder].assign(soloGenres);
				readGenresInOrder = readGenresInOrder + 1;
				//debug message
				//cout << soloGenres << endl;
				soloGenres.erase();
			}
			else {
				if (genres[i] != 34)
					soloGenres += genres[i];
			}
		}
		this->genresCounter = genresNo;
	}
};

class linkedList {
public:
	//head pointer
	node* head;
public:
	linkedList() {
		head = NULL;
	}
	bool isEmpty() {
		return head == NULL ? true : false;
	}
	void printList() {
		node *currNode = head;
		while (currNode) {
			cout << currNode->tconst << "\t" << currNode->titleType << "\t" << currNode->primaryTitle << "\t" << currNode->startYear << "\t" << currNode->runtimeMinutes << "\t";
			for (int i = 0; i < currNode->genresCounter; i++) cout << currNode->genres[i] << "\t";
			cout << endl;
			currNode = currNode->next;
		}
	}
	void insertRecord(string tconst, string titleType, string primaryTitle, string startYear, string runtimeMinutes, string genres) {
		node *newNode = new node(tconst, titleType, primaryTitle, startYear, runtimeMinutes, genres);
		if (isEmpty()) {
			head = newNode;
		}
		else {
			node *currNode = head;
			while (currNode->next) {
				currNode = currNode->next;
			}
			currNode->next = newNode;
		}
	}

};

int main() {
	linkedList unmei;
	string fileName;
	ifstream inputFile;
	while (true) {
		cout << "enter file path" << endl;
		cin >> fileName;
		inputFile.open(fileName.c_str());
		if (inputFile.is_open()) {
			string temp;
			while (getline(inputFile, temp)) {
				int counter = 0;
				string tconst, titleType, primaryTitle, startYear, runtimeMinutes, genres;
				for (int i = 0; i < temp.size(); i++) {
					if (temp[i] == 9) counter++;
					else {
						if (counter == 0) tconst += temp[i];
						if (counter == 1) titleType += temp[i];
						if (counter == 2) primaryTitle += temp[i];
						if (counter == 3) startYear += temp[i];
						if (counter == 4) runtimeMinutes += temp[i];
						if (counter == 5) genres += temp[i];
					}
				}
				unmei.insertRecord(tconst, titleType, primaryTitle, startYear, runtimeMinutes, genres);
				temp.clear();
			}
			inputFile.close();
			fileName.clear();
		}
		else {
			cout << "insert ended." << endl;
			break;
		}
		unmei.printList();
	}
	system("pause");
	return 0;
}