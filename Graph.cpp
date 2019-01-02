/*
 *Graph的基本实现
 **  A graph, implemented using an array of sets.
 *  Parallel edges and self-loops allowed.
 *
 *   a Graph tinyG.txt 期待以下结构
 * 13 13    //代表v,e
 * 0 6      //代表边
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
	//注意这里没有考虑加点的情况
	--first;//注意点序列为123
	--second;//对应索引为012
	arr[first].push_back(second);
	arr[second].push_back(first);
	++e;
}

const Graph::Iterator& Graph::adj(int num) const {
	//返回相连顶点的vector的引用
	//这里采用vector，，有点浪费空间
	--num;
	this->validate(num);
	return this->arr[num];
}

std::string Graph::toString()
{
	//转换为字符串输出
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
	//接口，调用dfs友元
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


/*测试函数*/
int main(int argc, char**argv) {
	std::ifstream ceshi;
	ceshi.open("F:/yzhh/VS2017pro/Graph/Graph/data.txt");
	Graph test(ceshi);
	std::cout << test.V();
	ceshi.close();
}
