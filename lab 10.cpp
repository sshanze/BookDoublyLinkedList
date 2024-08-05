#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class Book
{
	friend class BookList;

private:
	int id; /**id of a book.*/
	string title; /**name of a book.*/
	float price; /**price of a book.*/
	Book* next; /**address of the next available object.*/
	Book* pre; /**address of the previous available object.*/
public:

	Book(int id, string title, float price, Book* next, Book* pre)
	{
		this->id = id;
		this->title = title;
		this->price = price;
		this->next = next;
		this->pre = pre;
	}

	void bookDetails()
	{
		cout << "ID:" << id << endl;
		cout << "Title:" << title << endl;
		cout << "price" << endl;
	}

};
class BookList
{
private:
	Book* head;
	Book* cursor;
	Book* last;
public:

	BookList(Book* head, Book* cursor, Book* last)
	{
		this->head = NULL;
		this->cursor = NULL;
		this->last=NULL;
	}
	~BookList()
	{
		while (head != NULL)
		{
			Book* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void insert(const Book& newItem)
	{
		Book* newBook = new Book(newItem.id, newItem.title, newItem.price, NULL, NULL);

		if (head == NULL)
		{
			head = newBook;
			cursor = newBook;
			last = newBook;
		}
		else
		{
			newBook->next = cursor->next;
			newBook->pre = cursor;

			if (cursor->next != NULL)
			{
				cursor->next->pre = newBook;
			}
			else
			{
				last = newBook;
			}
			cursor->next = newBook;
			cursor = newBook;
		}
	}

	void remove()
	{
		if (head != NULL)
		{
			Book* temp = cursor;

			if (cursor->pre != NULL)
			{
				cursor->pre->next = cursor->next;
			}
			else
			{
				head = cursor->next;
			}
			if (cursor->next != NULL)
			{
				cursor->next->pre = cursor->pre;
				cursor = cursor->next;
			}

			else
			{
				cursor = last;
			}
			delete temp;
		}
	}

	void search(string title)
	{
		Book* temp = head;
		bool found = false;

		while (temp != NULL)
		{
			if (temp->title == title)
			{
				temp->bookDetails();
				found = true;
			}
			temp = temp->next;
		}
		if (!found)
		{
			cout << "Book not found" << endl;
		}
	}

	void replace(const Book& newItem)
	{
		if (head != NULL)
		{
			cursor->id = newItem.id;
			cursor->title = newItem.title;
			cursor->price = newItem.price;
		}
	}

	bool isEmpty() const
	{
		return head == NULL;
	}

	void gotoBeginning()
	{
		if (head != NULL)
		{
			cursor = head;
		}
	}

	void gotoEnd()
	{
		if (head != NULL)
		{
			cursor = last;
		}
	}

	bool gotoNext()
	{
		if (head != NULL && cursor->next != NULL)
		{
			cursor = cursor->next;
			return true;
		}
		return false;
	}

	bool gotoPrior()
	{
		if (head != NULL && cursor->pre != NULL)
		{
			cursor = cursor->pre;
			return true;
		}
		return false;
	}

	Book getCursor()
	{
		if (head != NULL)
		{
			return *cursor;
		}
		else
		{
			cout << "No list exist" << endl;
		}
	}

	void showStructureForward() const
	{
		Book* temp = last;

		while (temp != NULL)
		{
			temp->bookDetails();
			temp = temp->next;
		}
		if (head == NULL)
		{
			cout << "List is Empty " << endl;
		}
	}

	void showStructureReverse() const
	{
		Book* temp = last;

		while (temp != NULL)
		{
			temp->bookDetails();
			temp = temp->pre;
		}
		if (head == NULL)
		{
			cout << "List is Empty " << endl;
		}
	}
};

int main()
{

	BookList booklist;

	ifstream inputFile("input.txt");

	if (!inputFile) {
		cerr << "FILE NOT FOUND" << endl;
		return 1;
	}

	int id;
	string title;
	float price;

	while (inputFile >> id) {
		inputFile.ignore();

		getline(inputFile, title);
		inputFile >> price;
		inputFile.ignore();

		Book newBook(id, price, title, NULL, NULL);
		booklist.insert(newBook);
	}

	inputFile.close();

	booklist.showStructureForward();
	cout << endl;


	booklist.search("BOOK2");
	cout << endl;

	booklist.gotoBeginning();
	booklist.remove();
	booklist.showStructureForward();
	cout << endl;

	booklist.replace(Book(1, "NEW BOOK", 19.99));
	booklist.showStructureForward();
	cout << endl;


	return 0;
}
}