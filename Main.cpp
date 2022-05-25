#include"Graph.h"

int main() {

	std::valarray<std::string> nameMenu = {
		"Вывод графа(матрица смежности)",
		"Вывод графа(список смежности)",
		"Удалить вершину",
		"Удалить рёбра, с определённым весом",
	};

	menu name(nameMenu);

	ImplementMenuParametr realisation;
	bool flag = true;
	int menuNum = 0;
	while (flag) {
		flag = realisation(name.SelectMenu());
	}
	return 0;
}