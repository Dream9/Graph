#pragma once
#ifndef _GRAPH_HEAD_
#define _GRAPH_HEAD_


#include<iostream>
#include<vector>
#include<string>
#include<exception>

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
	T key;
};
//
template<typename T,typename W>
struct weightEdge :public Edge<T> {
	W weight;
};

//����Graph
class Graph {

public:
	typedef std::vector<int> Iterator;

private:
	int v;//������Ŀ
	int e;//�ߵ���Ŀ
	std::vector<std::vector<int>>arr;//�ڽӱ�����

public:
	Graph(int num);//����һ������num�����㵫�����ߵ�ͼ
	Graph(std::istream& in);//�ӱ�׼�������ж���һ��ͼ
	void addEdge(int first, int second);//��ͼ�����һ����
	const Iterator& adj(int num) const;//��v���ڵĶ���,ֻ�Ǳ������������޸�
	std::string toString();//Graph���ַ������
	/*����*/
	std::vector<int> DepthFirstSearch(int num);//ͼ����ʼ��
	friend void dfs(const Graph& G, int num, std::vector<bool>&visited, std::vector<int>&out);


public:
	int V() const { return v; }//���ص���
	int E() const { return e; }//���ر���
	virtual void validate(int arg) const {
		if (arg<0 || arg>v)
			throw Graph_err("Invalid argument");
	}//��Ч�Լ���
	size_t degre(int num) {
		validate(num);
		return adj(num).size();
	}//ĳ����Ķ���

private:
	void 
};



const std::string _v_err = "����������Ǹ�";
const std::string _e_err = "����Ŀ����Ǹ�";




#endif // !_GRAPH_HEAD_




