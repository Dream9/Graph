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




/*测试函数*/
int main(int argc, char**argv) {
	std::ifstream ceshi;
	ceshi.open("F:/yzhh/VS2017pro/Graph/Graph/data.txt");
	Graph<int> test(ceshi);
	std::vector<int>dfs_ans = test.BreathFirstSearch(1);
	std::cout << test.V();
	
	ceshi.close();
}
