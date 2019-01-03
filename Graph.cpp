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




/*���Ժ���*/
int main(int argc, char**argv) {
	std::ifstream ceshi;
	ceshi.open("F:/yzhh/VS2017pro/Graph/Graph/data.txt");
	Graph<int> test(ceshi);
	std::vector<int>dfs_ans = test.BreathFirstSearch(1);
	std::cout << test.V();
	
	ceshi.close();
}
