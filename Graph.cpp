#include "Graph.h"
#include<iterator>

void GraphIO::scanGraph(Graph& gp)
{
	std::ifstream Info("infoGraph.txt");
	int gSize;
	Info >> gSize;
	int adjVertex;
	int vertex;
	int width;
	for (int i = 0; i < gSize; i++) {
		Info >> vertex;
		Info >> adjVertex;
		if (adjVertex != -999) {
			Info >> width;
		}
		else continue;
		while (adjVertex != -999) {
			gp.insertEdge(vertex, adjVertex, width);
			Info>>adjVertex;
			if (adjVertex != -999) {
				Info >> width;
			}
		}

	}
	
}

bool Graph::insertEdge(int vertex, int to, int weight)
{
	Edge newEdge(to, weight);
	if (this->graph[vertex].isEmpty()) {
		++this->gSize;
	}
	if (this->graph[vertex].addEdge(newEdge)) {

		return true;
	}
	return false;


}

bool Graph::eraseVertex(int vertex)
{
	if (this->graph[vertex].ifExistance()) {
		graph[vertex].deleteVertex();
		for (int i = 0; i < this->maxSize; i++) {
			if (graph[i].ifExistance()) {
				for (int j = 0; j < graph[i].getCountOfEdge(); j++) {
					if (graph[i][j].getTo() == vertex) {
						graph[i].deleteEdge(j);
					}
				}
			}
		}


		return true;
	}

	return false;
}

void Graph::eraseEdgesWeight(int weight)
{
	for (int i = 0; i < maxSize; i++) {
		if (this->graph[i].ifExistance()) {
			this->graph[i].deleteEdgesWeight(weight);
		}
	}
}

void Vertex::deleteEdge(int index)
{
	auto It = std::find(this->egdes.begin(), this->egdes.end(), (*this)[index]);
	this->egdes.erase(It);
}

void Vertex::deleteEdgesWeight(int w)
{

	for (auto It = this->egdes.begin();It!=this->egdes.end(); ) {
		if (It->getWeight() == w) {
			auto ItErase = It;
			++It;
			this->egdes.erase(ItErase);
		}
		else{ ++It; }
	}
}

bool Vertex::addEdge(Edge tmp)
{
	/*FindEdge funcToFind(tmp);*/
	this->existance = true;
	auto It = std::find(this->egdes.begin(), this->egdes.end(), tmp);
	if (It != this->egdes.end()) {
		It->setWeight(tmp.getWeight());
		return false;
	}
	else {
		this->egdes.push_back(tmp);
		return true;
	}

}

bool Edge::operator==(const Edge& tmp)
{
	if (tmp.to == this->to) {
		return true;
	}
	return false;
}

bool Edge::operator!=( Edge& tmp)
{
	if (tmp.to != this->to) {
		return true;
	}
	return false;
}

void adjacencyList::printGraph(Graph& gp)
{
	for (int i = 0; i < gp.getMaxSize(); i++) {
		if (gp[i].ifExistance()) {
			std::cout << "[ " << i << " ] --> ";
			for (int j = 0; j < gp[i].getCountOfEdge(); j++) {
				std::cout<<"( "<<gp[i][j].getTo()<<", "<<gp[i][j].getWeight()<<" ) --> ";
			}
			std::cout << "nullptr\n";
		}
	}
}

void adjacencyMatrix::printGraph(Graph& gp)
{
	std::cout.width(3);
	std::cout << " ";
	for (int index = 0; index < gp.getMaxSize(); index++) {
		if (gp[index].ifExistance()) {
			std::cout.width(3);
			std::cout << index;
		}
	}
	std::cout << std::endl;
	for (int index = 0; index < gp.getMaxSize(); index++) {
		if (gp[index].ifExistance() && !gp[index].isEmpty()) {
			std::cout.width(3);
			std::cout << index;


			int It = 0;
			int ItEnd = gp[index].getCountOfEdge();
			for (int j = 0; j < gp.getMaxSize(); j++) {
				if (gp[j].ifExistance()) {

					if (gp[index][It].getTo() == j) {
						std::cout.width(3);
						std::cout << 1;
						It++;
						if (It == ItEnd)
							break;
					}
					else {
						std::cout.width(3);
						std::cout << " ";
					}
				}
			}
			std::cout << std::endl;
		}

	}
}
