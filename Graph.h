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

	void addEdge(int v, int w);//��ͼ�����һ����

	Iterator& adj(int v);//��v���ڵĶ���

	std::string toString();//Graph���ַ������

public:
	int V() const { return v; }//���ص���

	int E() const { return e; }//���ر���

	virtual void validate(int arg) const {
		if (arg<0 || arg>v)
			throw Graph_err("Invalid argument");
	}//��Ч�Լ���

	size_t degre(int v) {
		validate(v);
		return adj(v).size();
	}//ĳ����Ķ���
};



const std::string _v_err = "����������Ǹ�";
const std::string _e_err = "����Ŀ����Ǹ�";




#endif // !_GRAPH_HEAD_




