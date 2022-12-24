#include <iostream>
#include <string>
#include <fstream>


using namespace std;
template<typename T>
class Doubly
{
public:
	Doubly()
	{
		this->tail = nullptr;
		this->head = nullptr;
		this->size = 0;
	}
	unsigned int length() { return this->size; }
	void erase(unsigned int index)
	{
		if (index < 0 || index >(unsigned int)(size - 1))
			throw new out_of_range("Out of bound");
		int iteration = 0;
		auto currentNode = this->head;
		if (size == 1)
		{
			delete head;
			head = tail = nullptr;
			size--;
			return;
		}
		if (size > 1)
		{
			Node* temp = new Node();
			float midElement = ((float)(size - 1)) / 2;
			if (index <= midElement)
			{

				auto currentNode = this->head;
				if (index == 0)
				{
					temp = head->pNext;
					delete head;
					temp->pPrev = nullptr;
					head = temp;
					size--;
					return;
				}
				while (currentNode != nullptr)
				{
					if (iteration == index)
					{

						temp->pNext = currentNode->pNext;
						temp->pPrev = currentNode->pPrev;
						delete currentNode;
						temp->pPrev->pNext = temp->pNext;
						temp->pNext->pPrev = temp->pPrev;
						size--;
						return;
					}
					currentNode = currentNode->pNext;
					iteration++;
				}
			}
			else if (index > midElement)
			{
				auto currentNode = this->tail;
				iteration = size - 1;
				if (index == iteration)
				{
					temp = tail->pPrev;
					delete tail;
					temp->pNext = nullptr;
					tail = temp;
					size--;
					return;
				}
				while (currentNode != nullptr)
				{
					if (iteration == index)
					{
						temp->pNext = currentNode->pNext;
						temp->pPrev = currentNode->pPrev;
						delete currentNode;
						temp->pPrev->pNext = temp->pNext;
						temp->pNext->pPrev = temp->pPrev;
						size--;
						return;
					}
					currentNode = currentNode->pPrev;
					iteration--;
				}
			}
			throw exception("Something goes wrong while erasing");
		}
	}
	T& get(unsigned int index)
	{
		if (index < 0 || index >(unsigned int)(size - 1))
			throw new out_of_range("Out of bound");
		int iteration = 0;

		if (size == 1)
			return head->data;
		else if (size > 1)
		{
			float midElement = ((float)(size - 1)) / 2;
			if (index <= midElement)
			{
				auto currentNode = this->head;
				while (currentNode != nullptr)
				{
					if (iteration == index)
					{
						return currentNode->data;
					}
					currentNode = currentNode->pNext;
					iteration++;
				}
			}
			else if (index > midElement)
			{
				auto currentNode = this->tail;
				iteration = size - 1;
				while (currentNode != nullptr)
				{
					if (iteration == index)
					{
						return currentNode->data;
					}
					currentNode = currentNode->pPrev;
					iteration--;
				}
			}
		}
		throw exception("Something goes wrong :(");
	}
	void append(T data)
	{

		if (head == nullptr && tail == nullptr)
		{
			Node* first_node = new Node(data);
			tail = head = first_node;
			tail->pNext = nullptr;
			head->pPrev = nullptr;
			size++;
		}
		else
		{
			auto prevNode = tail;
			tail = new Node(data);
			prevNode->pNext = tail;
			tail->pPrev = prevNode;
			size++;
		}
	}
	void insert(unsigned int index, T value)
	{
		if (index < 0 || index >(unsigned int)(size))
			throw new out_of_range("Out of bound");
		if (index == size)
		{
			this->append(value);
			return;
		}
		auto currentNode = this->head;
		if (index == 0)
		{
			head = new Node(value);
			head->pNext = currentNode;
			currentNode->pPrev = head;
			size++;
			return;
		}

		float midElement = ((float)(size - 1)) / 2;
		int iteration = 0;
		if (index <= midElement)
		{
			Node* currentNode = this->head;
			for (unsigned int i = 0; i < index - 1; i++)
				currentNode = currentNode->pNext;
			Node* newNode = new Node(value, currentNode->pNext, currentNode->pPrev);
			currentNode->pNext = newNode;
			currentNode->pPrev = newNode;
			size++;
			return;
		}
		else if (index > midElement)
		{
			Node* currentNode = this->tail;
			for (unsigned int i = this->size - 1; i > index; i--)
				currentNode = currentNode->pPrev;
			Node* newNode = new Node(value, currentNode->pNext, currentNode->pPrev);
			currentNode->pNext = newNode;
			currentNode->pPrev = newNode;
			size++;
			return;
		}
		throw exception("Something goes wrong while erasing");
	}
	void clear()
	{
		while (size)
		{
			erase(0);
		}
		return;
	}
	T& operator[](unsigned int index)
	{
		if (index < 0 || index >(unsigned int)(size - 1))
			throw new out_of_range("Out of bound");
		int iteration = 0;

		if (size == 1)
			return head->data;
		else if (size > 1)
		{
			float midElement = ((float)(size - 1)) / 2;
			if (index <= midElement)
			{
				auto currentNode = this->head;
				while (currentNode != nullptr)
				{
					if (iteration == index)
					{
						return currentNode->data;
					}
					currentNode = currentNode->pNext;
					iteration++;
				}
			}
			else if (index > midElement)
			{
				auto currentNode = this->tail;
				iteration = size - 1;
				while (currentNode != nullptr)
				{
					if (iteration == index)
					{
						return currentNode->data;
					}
					currentNode = currentNode->pPrev;
					iteration--;
				}
			}
		}
		throw exception("Something goes wrong :(");
	}

private:
	class Node
	{
	public:
		Node* pNext;
		Node* pPrev;
		T data;
		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};
	Node* head;
	Node* tail;
	unsigned size;

};

// Assignment 1: Graph construction
struct Node {
	string name, id;
	int weight{ 0 };
};

class Graph
{
public:
	Doubly<Node> nodes;
	Doubly<Doubly<int>> adj;
	void add_node(Node node)
	{
		nodes.append(node);
		//to make the adjacency matrix squared
		adj.append(Doubly<int>());
		for (unsigned i = 0; i < nodes.length(); i++)
		{
			for (unsigned j = 0; adj[i].length() != nodes.length(); j++)
			{
				adj[i].append(NULL);
			}
		}
	}

	unsigned find_index(string id) {
		for (unsigned i = 0; i < nodes.length(); i++)
			if (nodes[i].id == id)
				return i;
		throw exception("Was killed or does not exist!");
	}
	void print_weights()
	{
		int it = 1;
		for (unsigned i = 0; i < adj.length(); i++)
		{
			for (unsigned j = 0; j < adj[i].length(); j++)
			{
				if (adj[i][j] != 0)
				{
					cout << it << " " << nodes[i].id << "," << nodes[j].id << "  " << adj[i][j] << endl;
					it++;
				}

			}
		}
	}
	// Assignment 2: Compare two graphs
	void delete_edge(string from_id, string to_id)
	{
		adj[find_index(from_id)][find_index(to_id)] = 0;
	}
	void delete_node(string id)
	{
		unsigned index = find_index(id);
		nodes.erase(index);
		adj.erase(index);
		for (unsigned i = 0; i < adj.length(); i++)
			adj[i].erase(index);
	}
	void find_by_name(string name) {
		string id;
		cout << name << "\n";
		for (int i = 0; i < name.size(); i++)
		{
			if (name[i] == ' ')
			{
				id += '-';
				continue;
			}
			id += name[i];
		}
		for (unsigned i = 0; i < adj.length(); i++)
		{
			if (adj[find_index(id)][i] != 0)
			{
				cout << "\t - " << nodes[i].name << " [weight: " << adj[find_index(id)][i] << "]\n";
			}
		}
	}
	bool node_exists(string name) {
		for (unsigned i = 0; i < nodes.length(); i++)
		{
			if (nodes[i].name == name)
			{
				return true;
			}
		}
		return false;
	}
};

void read_nodes(Graph& graph, string DATASET)
{
	string line;
	ifstream file;
	file.open(DATASET, ios::in, ios::binary);
	getline(file, line);
	unsigned i{ 0 };
	while (i < line.size())
	{
		Node node;
		for (; i < line.size(); i++)
		{
			if (line[i] == ',')
				break;
			node.id += line[i];
		}
		i++;
		for (; i < line.size(); i++)
		{
			if (line[i] == '\r')
				break;
			node.name += line[i];
		}
		graph.add_node(node);
		i++;
	}


	file.close();
}
void read_weights(Graph& graph, string DATASET_WEIGHTS)
{
	string line;
	ifstream file;
	file.open(DATASET_WEIGHTS, ios::in, ios::binary);
	getline(file, line);
	unsigned i{ 0 };
	while (i < line.size())
	{
		string from, to, temp;
		short weight;
		for (; i < line.size(); i++)
		{
			if (line[i] == ',')
				break;
			from += line[i];
		}
		i++;
		for (; i < line.size(); i++)
		{
			if (line[i] == ',')
				break;
			to += line[i];
		}
		i++;
		for (; i < line.size(); i++)
		{
			if (line[i] == ',')
				break;
		}
		i++;
		for (; i < line.size(); i++)
		{
			if (line[i] == ',')
				break;
			temp += line[i];
		}
		weight = stoi(temp);
		i++;
		for (; i < line.size(); i++)
		{
			if (line[i] == '\r')
				break;
		}

		int index1 = graph.find_index(from);
		int index2 = graph.find_index(to);
		graph.adj[index1][index2] = weight;
		graph.adj[index2][index1] = weight;
		i++;
	}
	file.close();
}

// Assignment 3: Compare two graphs
void print_new(Graph& graph2, Graph& graph1)
{
	string name;
	bool new_character{};
	int amount{ 0 };
	cout << "New characters:\n";
	for (unsigned i = 0; i < graph2.nodes.length(); i++)
	{
		for (unsigned j = 0; j < graph1.nodes.length(); j++)
		{
			if (graph2.nodes[i].id == graph1.nodes[j].id)
			{
				new_character = false;
				break;
			}
			else
			{
				new_character = true;
				name = graph2.nodes[i].id;
			}

		}
		if (new_character == true)
		{
			amount++;
			cout << "\t- " << name << '\n';
		}
	}
	cout << "Amount of new characters: " << amount << '\n' << '\n';

}
void print_dead(Graph& graph1, Graph& graph2)
{
	string name;
	bool dead{};
	int amount{ 0 };
	cout << "Dead characters:\n";
	for (unsigned i = 0; i < graph1.nodes.length(); i++)
	{
		for (unsigned j = 0; j < graph2.nodes.length(); j++)
		{
			if (graph1.nodes[i].id == graph2.nodes[j].id)
			{
				dead = false;
				break;
			}
			else
			{
				dead = true;
				name = graph1.nodes[i].id;
			}

		}
		if (dead == true)
		{
			amount++;
			cout << "\t- " << name << '\n';
		}
	}
	cout << "Amount of depth: " << amount << '\n' << '\n';
}
// Assignment 4: Compare two graphs
void print_top_10(Graph graph)
{
	int sum{ 0 };
	cout << "top 10 fat characters:\n\n";
	Doubly<Node> sorted_nodes;
	for (unsigned i = 0; i < graph.nodes.length(); i++)
	{
		sorted_nodes.append(graph.nodes[i]);
	}
	for (unsigned i = 0; i < graph.nodes.length(); i++)
	{
		for (unsigned j = 0; j < graph.adj[i].length(); j++)
		{
			sorted_nodes[i].weight += graph.adj[j][i];
		}
	}
	for (unsigned i = 1; i < graph.nodes.length(); i++)
	{
		for (unsigned j = i; j > 0 && sorted_nodes[j - 1].weight > sorted_nodes[j].weight; j--)
		{
			Node temp = sorted_nodes[j - 1];
			sorted_nodes[j - 1] = sorted_nodes[j];
			sorted_nodes[j] = temp;
		}
	}
	for (unsigned i = sorted_nodes.length() - 1; i > sorted_nodes.length() - 11; i--)
	{
		cout << sorted_nodes.length() - i << ". " << sorted_nodes[i].id << " [weight: " << sorted_nodes[i].weight << "]" << endl;
	}
	cout << "\n\ntop 10 skinny characters:\n\n";
	for (unsigned i = 0; i < 10; i++)
	{
		cout << i + 1 << ". " << sorted_nodes[i].id << " [weight: " << sorted_nodes[i].weight << "]" << endl;
	}

}


int main()
{
	string book1("asoiaf-book1-nodes.csv");
	string book1_weights("asoiaf-book1-edges.csv");
	string book2("asoiaf-book2-nodes.csv");
	string book2_weights("asoiaf-book2-edges.csv");


	Graph graph, graph2;
	read_nodes(graph, book1);
	read_weights(graph, book1_weights);
	read_nodes(graph2, book2);
	read_weights(graph2, book2_weights);

	cout << "#####################################################\n\n";
	print_top_10(graph);
	cout << "\n#####################################################\n\n";

	cout << "before edge deletion:\n";
	graph.find_by_name("Addam Marbrand");
	graph.delete_edge("Addam-Marbrand", "Jaime-Lannister");
	cout << "\nAfter edge deletion:\n";
	graph.find_by_name("Addam Marbrand");

	cout << "\n#####################################################\n";
	cout << "\nAddam Marbrand exists: " << graph.node_exists("Addam Marbrand");
	graph.delete_node("Addam-Marbrand");
	cout << "\nAddam Marbrand has been deleted\nAddam Marbrand exists: " << graph.node_exists("Addam Marbrand");
	cout << "\n\n#####################################################\n\n";

	print_dead(graph, graph2);
	cout << "#####################################################\n\n";
	print_new(graph2, graph);
	cout << "#####################################################\n\n";

}
