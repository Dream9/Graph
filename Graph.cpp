/*
 *Graph�Ļ���ʵ��
 **  A graph, implemented using an array of sets.
 *  Parallel edges and self-loops allowed.
 *
 *   a Graph tinyG.txt �ڴ����½ṹ
 * 13 13    //����v,e
 * 0 6      //�����
 * 1 2      //...
 * 
 */

#include"Graph.h"
#include<fstream>
#include<iostream>

inline Graph::Graph(int num) {
	if (num < 0)
		throw Graph_err(std::to_string(__LINE__)+__FILE__+_v_err);
	this->v = num;
	this->e = 0;
	this->arr.resize(v, {});
}
Graph::Graph(std::istream& in) {
	int v;
	int e;
	int w;

	in >> v >> e;
	this->v = v;
	this->e = 0;
	if(v<0)
		throw Graph_err(std::to_string(__LINE__) + __FILE__ +_v_err);
	if (e < 0)
		throw Graph_err(std::to_string(__LINE__) + __FILE__ + _e_err);
	this->arr.resize(v, {});
	while (e-->0) {
		in >> v >> w;
		validate(v);
		validate(w);
		addEdge(v, w);
	}

}

void Graph::addEdge(int first, int second) {
	//ע������û�п��Ǽӵ�����
	--first;//ע�������Ϊ123
	--second;//��Ӧ����Ϊ012
	arr[first].push_back(second);
	arr[second].push_back(first);
	++e;
}

const Graph::Iterator& Graph::adj(int num) const {
	//�������������vector������
	//�������vector�����е��˷ѿռ�
	--num;
	this->validate(num);
	return this->arr[num];
}

std::string Graph::toString()
{
	//ת��Ϊ�ַ������
	int iter = 0;
	std::string out = "";

	out += std::to_string(this->v) + "vertecies" + std::to_string(this->e) + "edge\r\n";
	for (; iter < this->v; ++iter) {
		out += std::to_string(iter) + ":";
		for (int jter : this->adj(iter)) {
			out += ","+std::to_string(jter);
		}
		out += "\r\n";
	}
	return out;
}

std::vector<int> Graph::DepthFirstSearch(int num) {
	//�ӿڣ�����dfs��Ԫ
	int len = this->V();
	std::vector<int> out;
	std::vector<bool>visited(len,false);
	//out.reserve(len);
	dfs(*this, num, visited,out);
	return out;
}
void dfs(const Graph& G, int num, std::vector<bool>&visited, std::vector<int>&out) {
	visited[num]=true;
	for (int cur : G.adj(num)) {
		if (!visited[cur])
			dfs(G, cur, visited, out);
	}
}


/*���Ժ���*/
int main(int argc, char**argv) {
	std::ifstream ceshi;
	ceshi.open("F:/yzhh/VS2017pro/Graph/Graph/data.txt");
	Graph test(ceshi);
	std::cout << test.V();
	ceshi.close();
}
