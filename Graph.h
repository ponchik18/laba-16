#pragma once
#include<list>
#include<fstream>
#include<iostream>
#include<queue>
#include<algorithm>
#include<memory>
#include<Windows.h>
#include<conio.h>
#include<valarray>
#define MAX_LOAD 0.4
#define UP 72
#define DOWN 80
#define ENTRY 13
#define ESC 27

class Edge {
	int to;
	int weight;
public:
	Edge(const Edge& tmp) { this->to = tmp.to; this->weight = tmp.weight; }
	void setWeight(int weight) { this->weight = weight; }
	Edge(int to = 0, int weight=0 ): to(to), weight(weight){}
	//int getFrom();
	int getTo() { return to; }
	int getWeight() { return weight;}
	bool operator == (const Edge& tmp);
	bool operator!=( Edge& tmp);
	bool operator == (int w) {
		if (weight == w) {
			return true;
		}
		return false;
	}
	bool operator != (int w) {
		if (weight != w) {
			return true;
		}
		return false;
	}

};

class FindEdge {
	Edge to;
public:
	FindEdge(Edge tmp):to(tmp){}
	bool operator==(Edge& tmp) {
		if (tmp == to)
			return true;
		return false;
	}
};
class Vertex {
	std::list<Edge> egdes;
	bool existance;
public:
	Vertex() { existance = false; }
	bool addEdge(Edge tmp);
	bool ifExistance() const { if (existance == true) { return true; } else return false; }
	void deleteEdge(int index);
	bool isEmpty() const {
		return this->egdes.empty();
	}
	int getCountOfEdge()const { return (int)this->egdes.size(); }
	Edge operator[](int index) {
		auto It = egdes.begin();
		for (int i = 0; i < this->egdes.size(); i++) {
			if (i == index) {
				return *It;
			}
			It++;
		}
	
	}
	void deleteVertex() {
		existance = false;
		this->egdes.clear();
	}
	void deleteEdgesWeight(int w);
	//void deleteEdgeTo(int w);
};
class Graph
{
	int maxSize;//max possible graph size
	int gSize;
	//std::list<int>* graph;
	std::unique_ptr<Vertex[]>graph;
public:
	Graph(int maxSize) :maxSize(maxSize) {
		gSize = 0;
		graph = std::make_unique<Vertex[]>(maxSize);
	}
	bool isEmpty() const { if (gSize == 0) return true; return false; }
	void clearGraph();
	bool insertEdge(int vertex, int to, int weight);
	bool eraseVertex(int vertex);
	void eraseEdgesWeight(int weight);
	int getMaxSize() { return maxSize; }
	Vertex operator[](int index) { return this->graph[index]; }
};

class PrintGraph {
public:
	virtual void printGraph(Graph& gp)=0;
};

class adjacencyList: public PrintGraph {
public:
	void printGraph(Graph& gp) override;
};

class adjacencyMatrix: public PrintGraph {
public:
	void printGraph(Graph& gp) override;
};



class GraphIO {
	//PrintGraph* write;
	std::unique_ptr<PrintGraph> write;

public:
	GraphIO(PrintGraph* write = nullptr) :write(write){}
	void scanGraph(Graph& gp);
	void SetPrintGraph(std::unique_ptr<PrintGraph> write) { this->write=std::move(write); }
	void print(Graph& gp) {
		write->printGraph(gp);
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class menu {
private:
	std::valarray<std::string> nameMenu;// меню выполнение программы
	int ActiveField;
	HANDLE console;
	size_t menuField;
	void ShowMenu();
	int returnField();
	void GoToXY(int x, int y);
	void ConsoleCursorVisible(bool show, short size) {
		CONSOLE_CURSOR_INFO CursorInfo;
		CursorInfo.bVisible = show;
		CursorInfo.dwSize = size;
		SetConsoleCursorInfo(console, &CursorInfo);
	}
	void HilghtlightField() {
		SetConsoleTextAttribute(console, 94);
	}
	void SimpleTextMenu() {
		SetConsoleTextAttribute(console, 158);
	}
	void makeSimpleColorForText() {
		SetConsoleTextAttribute(console, 240);
		/*for (int i = 0; i < 256; i++) {
			SetConsoleTextAttribute(console, i);
			std::cout << i << " TEXT SHOW NEXT COLOR\n";
		}*/
	}
	void conturMenu() {
		int Ypos = 8;

		SetConsoleTextAttribute(console, 0);
		do {
			GoToXY(32, Ypos);
			for (int i = 0; i < 50; i++) {
				std::cout << " ";
			}
			Ypos++;
		} while (Ypos - 7 <= this->nameMenu.size());
		makeSimpleColorForText();
		std::cout << "\n";
	}
public:
	int SelectMenu();
	menu(std::valarray<std::string> nm);
};
inline void menu::ShowMenu()
{
	GoToXY(52, 7);
	std::cout << "DIALOGUE";
	conturMenu();
	int Ypos = 8;
	for (int i = 0; i < this->nameMenu.size(); i++, Ypos++) {
		GoToXY(39, Ypos);
		if (this->ActiveField == i) {
			this->HilghtlightField();
			std::cout << "->" << this->nameMenu[i];
		}
		else {
			this->SimpleTextMenu();
			std::cout << this->nameMenu[i];
		}
	}
	this->makeSimpleColorForText();
	std::cout << "\n\n";
}

inline int menu::returnField()
{
	char ch;
	ch = _getch();
	if (ch == -32) ch = _getch(); // Отлавливаем стрелочки
	switch (ch)
	{
	case ESC:
		return -2;
	case DOWN:
		if (this->ActiveField < this->nameMenu.size() - 1)
			ActiveField++;
		break;
	case UP:
		if (ActiveField > 0)
			ActiveField--;
		break;
	case ENTRY:
		return ActiveField;
	default:
		break;
	}
	return -1;
}

inline int menu::SelectMenu()
{
	int flag = -1;
	while (flag == -1) {
		system("cls");
		ShowMenu();
		flag = returnField();
	}
	return flag;
}

inline menu::menu(std::valarray<std::string> nameMenu)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	this->nameMenu = nameMenu;
	ActiveField = 0;
	system("color F0");
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursorVisible(false, 25);
	menuField = nameMenu.size();
	makeSimpleColorForText();

}

inline void menu::GoToXY(int x, int y)
{
	COORD CursorPosition;
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}





class ImplementMenuParametr {
private:
	Graph *gp;
	GraphIO gpIO;
public:
	ImplementMenuParametr(int maxSize=10) {
		gp = new Graph(maxSize);
		gpIO.scanGraph(*gp);
	}
	bool operator()(int ParametrMenu) {
		switch (ParametrMenu) {
		case 0:
		{
			gpIO.SetPrintGraph(std::make_unique<adjacencyMatrix>());
			gpIO.print(*gp);
			std::cout << "\n";
			std::cout << "Процедура завершена!\n";
			system("pause");
			break;
		}
		case 1: {
			gpIO.SetPrintGraph(std::make_unique<adjacencyList>());
			gpIO.print(*gp);
			std::cout << "\n";
			std::cout << "Процедура завершена!\n";
			system("pause");
			break;
		}
		case 2: {
			int vertex;
			do {
				std::cout << "Введите вершину, которую хотите удалить: ";
				std::cin >> vertex;
				std:: cout << "\n";
			} while (vertex<0 || vertex>gp->getMaxSize());
			std::cout << "\n";
			gp->eraseVertex(vertex);
			std::cout << "Процедура завершена!\n";
			system("pause");
			break;
		}
		case 3:
		{
			int weight;
			do {
				std::cout << "Введите вес рёбер, которые хотите удалить: ";
				std::cin >> weight;
				std::cout << "\n";
			} while (weight<0 || weight>gp->getMaxSize());
			std::cout << "\n";
			gp->eraseEdgesWeight(weight);
			std::cout << "Процедура завершена!\n";
			system("pause");
			break;
		}
		case -2:
			return false;
			break;
		}
		return true;
	}
	~ImplementMenuParametr() {
		delete gp;
	}
};



