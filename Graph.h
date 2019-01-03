#pragma once
#ifndef _GRAPH_HEAD_
#define _GRAPH_HEAD_


#include<iostream>
#include<vector>
#include<string>
#include<exception>
#include<map>
#include<set>
#include<queue>

const std::string _v_err = "顶点数必须非负";
const std::string _e_err = "边数目必须非负";
template<typename> class Graph;
template<typename T>
void bfs(const Graph<T>&,T,std::vector<T>&);
template<typename T>
void dfs(const Graph<T>&, T, std::set<T>, std::vector<T>&);

//定义错误抛出类型
class Graph_err :public std::runtime_error{
public:
	explicit Graph_err(const std::string &s):std::runtime_error(s){}
};

//定义节点类型
template<typename T>
struct Node {
	T val;
	Node<T>*next;

	Node<T>() { next = nullptr; }
	Node<T>(const T _ty) {
		val = _ty;
		next = nullptr;
	}
};
//定义带权的节点
template<typename T,typename W=int>
struct Node_weight :public Node<T> {
	W weight;
	Node_weight<T,W>(const T _ty, const W _wy) :Node<T>(_ty) { weight = _wy; }
	bool operator<(const Node_weight<T, W>&sec) { return this->weight < sec.weight; }
};
//重新规划了一下
//定义edge
template<typename T>
struct Edge {
	T to;
	Edge(T val) :to(val) {};
};
//
template<typename T,typename W>
struct weightEdge :public Edge<T> {
	T from;
	W weight;
	weightEdge(T _f, T _t) :from(_f), to(_t) {};
	bool operator<(const weightEdge&a) { return std::less<W>(this->weight, a.weight) };
};

//定义Graph
template<typename T>
class Graph {

public:
	typedef Edge<T> entity;
	typedef std::vector<entity> Iterator;
	
private:

	int v;//顶点数目
	int e;//边的数目
	std::map<T,Iterator>arr;//邻接表数组,,考虑了采用键值对,,也可以采用 vector

public:
	Graph(int num);//创建一个含有num个顶点但不含边的图
	Graph(std::istream& in);//从标准输入流中读入一幅图
	void addEdge(T first, T second);//向图中添加一条边
	const Iterator& adj(T num) const;//和v相邻的顶点,只是遍历，不能做修改
	std::string toString();//Graph的字符串表达
	/*遍历*/
	//dfs版
	std::vector<T> DepthFirstSearch(T num);//图，起始点
	friend void dfs<T>(const Graph<T> &, T, std::set<T>&, std::vector<T>&);
	//bfs版
	std::vector<T> BreathFirstSearch(T num);
	friend void bfs<T> (const Graph& G, T num, std::vector<T>&out);

public:
	int V() const { return v; }//返回点数
	int E() const { return e; }//返回边数
	virtual void validate(int arg) const {
		//主要保证在使用vector时候不会越界
		/*
		if (arg<0 || arg>v)
			throw Graph_err("Invalid argument");
		*/
	}//有效性检验
	size_t degre(int num) {
		validate(num);
		return adj(num).size();
	}//某个点的度数

private:
	//
};





/*具体实现*/
template<typename T>
inline Graph<T>::Graph(int num) {
	if (num < 0)
		throw Graph_err(std::to_string(__LINE__) + __FILE__ + _v_err);
	this->v = num;
	this->e = 0;
	this->arr.resize(v, {});
}
template<typename T>
Graph<T>::Graph(std::istream& in) {
	T first;
	T second;
	int iter;
	in >> this->v >> iter;

	if (this->v < 0)
		throw Graph_err(std::to_string(__LINE__) + __FILE__ + _v_err);
	if (this->e < 0)
		throw Graph_err(std::to_string(__LINE__) + __FILE__ + _e_err);
	//如果不采用vector,下面的可以忽略
	//this->arr.resize(v, {});
	while (iter-- > 0) {
		in >> first >> second;
		validate(first);
		validate(second);
		addEdge(first, second);
	}

}

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
template<typename T>
void Graph<T>::addEdge(T first, T second) {
	//重新采用map规划后，不需下面两句
	//--first;//注意点序列为123
	//--second;//对应索引为012
	arr[first].push_back(entity(second));
	arr[second].push_back(entity(first));
	++e;
}
template<typename T>
const typename Graph<T>::Iterator& Graph<T>::adj(T num) const {
	//返回相连顶点的vector的引用
	//--num;
	//this->validate(num);
	auto ans = this->arr.find(num);
	if (ans == this->arr.end())
		throw;
	return ans->second;
}
template<typename T>
std::string Graph<T>::toString()
{
	//转换为字符串输出
	int iter = 0;
	std::string out = "";

	out += std::to_string(this->v) + "vertecies" + std::to_string(this->e) + "edge\r\n";
	for (; iter < this->v; ++iter) {
		out += std::to_string(iter) + ":";
		for (entity jter : this->adj(iter)) {
			out += "," + std::to_string(jter.to);
		}
		out += "\r\n";
	}
	return out;
}

template<typename T>
std::vector<T> Graph<T>::DepthFirstSearch(T num) {
	//接口，调用dfs友元
	int len = this->V();
	std::vector<T> out;
	std::set<T>visited;
	//out.reserve(len);
	dfs(*this, num, visited, out);
	return out;
}

template<typename T>
std::vector<T> Graph<T>::BreathFirstSearch(T num){
	//接口，调用bfs
	std::vector<T> out;
	bfs(*this, num, out);
	return out;

}
/*友元bfs的定义*/
template<typename T>
void bfs(const Graph<T>& G, T num, std::vector<T>&out) { 
	/*借助于queue实现*/
	std::queue<T>que;
	que.push(num);
	std::set<T>visited;
	while (!que.empty()) {
		T current = que.front();
		que.pop();
		if (visited.insert(current).second) {
			for (auto iter : G.adj(current)) {
				que.push(iter.to);
			}
			out.push_back(current);
		}
	}

}/*友元dfs的定义*/
template<typename T>
void dfs(const Graph<T> & G, T num, std::set<T>&visited, std::vector<T>&out) {
		/*由于采用了map的实现，那么也就不能用vector记录访问了，改用set*/
	/*借助stack，也可以不用递归*/
	out.push_back(num);
	visited.insert(num);
	for (typename Graph<T>::entity cur : G.adj(num)) {
		if (visited.insert(cur.to).second)
			dfs(G, cur.to, visited, out);
	}
}
#endif // !_GRAPH_HEAD_




