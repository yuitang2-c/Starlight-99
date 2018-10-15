#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class DynamicArray {
private:
	int size;
	int capacity;
	string *storage;
public:
	DynamicArray() {
		capacity = 1100;
		size = 0;
		storage = new string[capacity];
	}
	DynamicArray(int capacity) {
		this->capacity = capacity;
		size = 0;
		storage = new string[capacity];
	}
	~DynamicArray() {
		delete[] storage;
	}
	void setCapacity(int newCapacity) {
		//https://stackoverflow.com/questions/4979681/how-to-properly-free-a-stdstring-from-memory
		string *newStorage = new string[newCapacity];
		memcpy(newStorage, storage, sizeof(string)*size);
		capacity = newCapacity;
		storage = newStorage;
	}
	//edited...?
	void ensureCapacity(int minCapacity)
	{
		if (minCapacity > capacity) {
			//50% buffer
			int newCapacity = (capacity * 3) / 2 + 1;
			if (newCapacity < minCapacity)
				newCapacity = minCapacity;
			setCapacity(newCapacity);
		}
	}
	//bug exist after deleted a record
	void rangeCheck(int index) {
		if (index < 0 || index >= size)
			throw "Index out of bounds!";
	}
	void set(int index, int value) {
		rangeCheck(index);
		storage[index] = value;
	}
	string get(int index) {
		rangeCheck(index);
		return storage[index];
	}
	void removeAt(int index) {
		rangeCheck(index);
		int moveCount = size - index - 1;
		if (moveCount > 0)
			memmove(storage + index, storage + (index + 1), sizeof(string) * moveCount);
		size--;
		//pack();
	}
	void insertAt(int index, string content) {
		if (index < 0 || index > size)
			throw "Index out of bounds!";
		ensureCapacity(size + 1);
		int moveCount = size - index;
		if (moveCount != 0)
			memmove(storage + (index + 1), storage + index, sizeof(string) * moveCount);
		storage[index] = content;
		size++;
	}

	void searchByID(string key, int st, int ed) {
		int mid = (st + ed) / 2;
		string temp = get(mid);
		// cout << temp << endl; // debug
		// cout << key << endl; // debug
		// cout << temp.compare(0, 9, key) << endl; // debug
		if (temp.compare(0, 9, key) == 0) {
			removeAt(mid);
		}
		else if (st == mid || mid == ed) {
			cout << "target not found" << endl;
		}
		else if (temp.compare(0, 9, key) > 0) {
			searchByID(key, st, mid - 1);
		}
		else searchByID(key, mid + 1, ed);
	}

};

int main() {

	DynamicArray unmei;
	int position = 0;
	string name;
	ifstream inputFile;
	//can be developed as a control loop
	while (true) {
		cout << "enter the file path with xxx.txt format (e.g. DataSet1_1000.txt)" << endl;
		cin >> name;
		inputFile.open(name.c_str());
		if (inputFile.is_open()) {
			string temp;
			while (getline(inputFile, temp)) {
				unmei.insertAt(position, temp);
				//cout << unmei.get(position) << endl; //bebug message, can be deleted
				position++;
				temp.clear();
			}
			inputFile.close();
			name.clear();
		}
		else {
			cout << "Insert part ended. Move to delet part." << endl;
			break;
		}
	}

	//binary search
	string theQuery;
	while (true) {
		cout << "support id search only, plz input as 'ttXXXXXXX' format " << endl;
		cin >> theQuery;
		if (theQuery.compare("end") == 0) {
			cout << "delete part end. show updated record" << endl;
			break;
		}
		unmei.searchByID(theQuery, 0, position - 1);
		position--;
		theQuery.clear();
	}

	//bebug message, can be deleted
	for (int i = 0; i < position; i++) {
		cout << unmei.get(i) << endl;
	}

	system("pause");

	return 0;
}