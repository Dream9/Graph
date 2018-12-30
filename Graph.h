#pragma once
#ifndef _GRAPH_HEAD_
#define _GRAPH_HEAD_


#include<iostream>
#include<vector>
#include<string>
#include<exception>

//定义错误抛出类型
class Graph_err :public std::runtime_error{
public:
	explicit Graph_err(const std::string &s):std::runtime_error(s){}
};
//定义Graph
class Graph {

public:
	typedef std::vector<int> Iterator;

private:
	int v;//顶点数目
	int e;//边的数目
	std::vector<std::vector<int>>arr;//邻接表数组

public:
	Graph(int num);//创建一个含有num个顶点但不含边的图

	Graph(std::istream& in);//从标准输入流中读入一幅图

	void addEdge(int v, int w);//向图中添加一条边

	Iterator& adj(int v);//和v相邻的顶点

	std::string toString();//Graph的字符串表达

public:
	int V() const { return v; }//返回点数

	int E() const { return e; }//返回边数

	virtual void validate(int arg) const {
		if (arg<0 || arg>v)
			throw Graph_err("Invalid argument");
	}//有效性检验

	size_t degre(int v) {
		validate(v);
		return adj(v).size();
	}//某个点的度数
};



const std::string _v_err = "顶点数必须非负";
const std::string _e_err = "边数目必须非负";




#endif // !_GRAPH_HEAD_




