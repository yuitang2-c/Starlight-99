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
	//edited
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
};

int main() {

	DynamicArray unmei;
	int position = 0;
	string name;
	ifstream inputFile;
	cin >> name;
	inputFile.open(name.c_str());
	if (inputFile.is_open()) {
		string temp;
		while (getline(inputFile,temp)) {
			unmei.insertAt(position, temp);
			cout << unmei.get(position) << endl;
			position++;
			temp.clear();
		}
		inputFile.close();
	}
	else cout << "error";

	for (int i = 0; i < position; i++) {
		cout << unmei.get(i) << endl;
	}

	system("pause");

	return 0;
}