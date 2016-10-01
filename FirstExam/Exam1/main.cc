/*
 * author: jokhan
 * date: 2016.10.1
 * function: main.cc
 */
#include <iostream>
#include <vector>

using namespace std;

class MagicCube {
	public:
		int len;
		vector<int> nums;
		void printCube();
		void initSmallerCube();
		void inputNums();
};


int main()
{
	//****input data*****//
	int M,N,P;
	cin >> M;
	cin >> N;
	cin >> P;
	MagicCube bigCube, smallerCube[N];
	bigCube.len = M;
	bigCube.inputNums();
	for( int i = 0; i < N; ++ i ) {
		
		smallerCube[i].initSmallerCube();
	}
	//******************//
	
	cout << "big:" << endl;
	bigCube.printCube();
	cout << "small::" << endl;
	for( int i = 0; i < N; ++ i ) {
		cout << i << endl;
		smallerCube[i].printCube();
	}
	return 0;
}

void MagicCube::printCube() 
{
	for( int i = 0; i < nums.size(); ++ i ) {
		int left = i;
		int index1 = left / ( len * len );
		left -= index1 * len * len;
		int index2 = left / len;
		left -= index2 * len;
		int index3 = left;
		cout << "[" << index1 << "," << index2 << "," << index3 << "]";
		cout << nums.at(i) << endl;
	}
}

void MagicCube::initSmallerCube()
{
	cin >> len;
	inputNums();
}

void MagicCube::inputNums()
{
	for( int i = 0; i < len * len * len; ++ i ) {
		int tmp;
		cin >> tmp;
		nums.push_back( tmp );
	}
}
