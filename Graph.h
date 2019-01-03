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

const std::string _v_err = "����������Ǹ�";
const std::string _e_err = "����Ŀ����Ǹ�";
template<typename> class Graph;
template<typename T>
void bfs(const Graph<T>&,T,std::vector<T>&);
template<typename T>
void dfs(const Graph<T>&, T, std::set<T>, std::vector<T>&);

//��������׳�����
class Graph_err :public std::runtime_error{
public:
	explicit Graph_err(const std::string &s):std::runtime_error(s){}
};

//����ڵ�����
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
//�����Ȩ�Ľڵ�
template<typename T,typename W=int>
struct Node_weight :public Node<T> {
	W weight;
	Node_weight<T,W>(const T _ty, const W _wy) :Node<T>(_ty) { weight = _wy; }
	bool operator<(const Node_weight<T, W>&sec) { return this->weight < sec.weight; }
};
//���¹滮��һ��
//����edge
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

//����Graph
template<typename T>
class Graph {

public:
	typedef Edge<T> entity;
	typedef std::vector<entity> Iterator;
	
private:

	int v;//������Ŀ
	int e;//�ߵ���Ŀ
	std::map<T,Iterator>arr;//�ڽӱ�����,,�����˲��ü�ֵ��,,Ҳ���Բ��� vector

public:
	Graph(int num);//����һ������num�����㵫�����ߵ�ͼ
	Graph(std::istream& in);//�ӱ�׼�������ж���һ��ͼ
	void addEdge(T first, T second);//��ͼ�����һ����
	const Iterator& adj(T num) const;//��v���ڵĶ���,ֻ�Ǳ������������޸�
	std::string toString();//Graph���ַ������
	/*����*/
	//dfs��
	std::vector<T> DepthFirstSearch(T num);//ͼ����ʼ��
	friend void dfs<T>(const Graph<T> &, T, std::set<T>&, std::vector<T>&);
	//bfs��
	std::vector<T> BreathFirstSearch(T num);
	friend void bfs<T> (const Graph& G, T num, std::vector<T>&out);

public:
	int V() const { return v; }//���ص���
	int E() const { return e; }//���ر���
	virtual void validate(int arg) const {
		//��Ҫ��֤��ʹ��vectorʱ�򲻻�Խ��
		/*
		if (arg<0 || arg>v)
			throw Graph_err("Invalid argument");
		*/
	}//��Ч�Լ���
	size_t degre(int num) {
		validate(num);
		return adj(num).size();
	}//ĳ����Ķ���

private:
	//
};





/*����ʵ��*/
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
	//���������vector,����Ŀ��Ժ���
	//this->arr.resize(v, {});
	while (iter-- > 0) {
		in >> first >> second;
		validate(first);
		validate(second);
		addEdge(first, second);
	}

}

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
template<typename T>
void Graph<T>::addEdge(T first, T second) {
	//���²���map�滮�󣬲�����������
	//--first;//ע�������Ϊ123
	//--second;//��Ӧ����Ϊ012
	arr[first].push_back(entity(second));
	arr[second].push_back(entity(first));
	++e;
}
template<typename T>
const typename Graph<T>::Iterator& Graph<T>::adj(T num) const {
	//�������������vector������
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
	//ת��Ϊ�ַ������
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
	//�ӿڣ�����dfs��Ԫ
	int len = this->V();
	std::vector<T> out;
	std::set<T>visited;
	//out.reserve(len);
	dfs(*this, num, visited, out);
	return out;
}

template<typename T>
std::vector<T> Graph<T>::BreathFirstSearch(T num){
	//�ӿڣ�����bfs
	std::vector<T> out;
	bfs(*this, num, out);
	return out;

}
/*��Ԫbfs�Ķ���*/
template<typename T>
void bfs(const Graph<T>& G, T num, std::vector<T>&out) { 
	/*������queueʵ��*/
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

}/*��Ԫdfs�Ķ���*/
template<typename T>
void dfs(const Graph<T> & G, T num, std::set<T>&visited, std::vector<T>&out) {
		/*���ڲ�����map��ʵ�֣���ôҲ�Ͳ�����vector��¼�����ˣ�����set*/
	/*����stack��Ҳ���Բ��õݹ�*/
	out.push_back(num);
	visited.insert(num);
	for (typename Graph<T>::entity cur : G.adj(num)) {
		if (visited.insert(cur.to).second)
			dfs(G, cur.to, visited, out);
	}
}
#endif // !_GRAPH_HEAD_




