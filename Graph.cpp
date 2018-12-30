/*
 *Graph�Ļ���ʵ��
 **  A graph, implemented using an array of sets.
 *  Parallel edges and self-loops allowed.
 *
 *   a Graph tinyG.txt �ڴ����½ṹ
 * 13 13    //����v,e
 * 0 6      //�����
 * 1 2
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

void Graph::addEdge(int v, int w) {
	//ע������û�п��Ǽӵ�����
	--v;//ע�������Ϊ123
	--w;//��Ӧ����Ϊ012
	arr[v].push_back(w);
	arr[w].push_back(v);
	++e;
}

Graph::Iterator& Graph::adj(int v) {
	//�������������vector������
	this->validate(v);
	return this->arr[v];
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

int main(int argc, char**argv) {
	std::ifstream ceshi;
	ceshi.open("F:/yzhh/VS2017pro/Graph/Graph/data.txt");
	Graph test(ceshi);
	std::cout << test.V();
	ceshi.close();
}
