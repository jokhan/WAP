/*
 * author: jokhan
 * date: 2016.10.1
 * function: main.cc
 */
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class MagicCube {
	private:
	public:
		int len;
		vector<int> nums;
		void setLen( int len );
		void printCube();
		void initSmallerCube();
		void inputNums();
		//transform the location in vector to the postion in the cube
		void locToPos( const int &location, int &index1, int &index2, int &index3 );
		bool isAllZeros();
		friend bool isRightLocation( const MagicCube &bigCube, const MagicCube &smallCube, int location, int P );
		friend void putSmallCube( MagicCube &bigCube, const MagicCube &smallCube, int location );
		friend void vectorToMap( const MagicCube &bigCube, multimap<int,int> &mapNums );
};

struct SmallCubes {
	MagicCube smallCube;
	int index;
};

bool compare( SmallCubes smallOne, SmallCubes smallAnother );

int main()
{
	int M,N,P;
	//****input data*****//
	cin >> M;
	cin >> N;
	cin >> P;
	MagicCube bigCube, smallerCube[N];
	SmallCubes smallCubes[N];
	bigCube.setLen( M );
	bigCube.inputNums();
	for( int i = 0; i < N; ++ i ) {
		smallerCube[i].initSmallerCube();
		smallCubes[i].smallCube = smallerCube[i];
		smallCubes[i].index = i;
	}
	//******************//
	
	//******solution****//
	int posOfSmall[N];   //answer
	multimap<int,int> mapNums;
	multimap<int,int>::iterator iter; 
	vectorToMap( bigCube, mapNums );

	//sort small cubes, and put the bigger first
	sort( smallCubes, smallCubes + N, compare );
	//int putCubesNum = 0;     //the number of smaller cubes which are put
	for( int i = 0; i < N; ++ i ) {
		int target = (P - smallCubes[i].smallCube.nums.at(0)) % P;
		int count = mapNums.count( target );
		iter = mapNums.find( target );
		for( int j = 0; j < count; ++ j, ++ iter ) {
			if( isRightLocation( bigCube, smallCubes[i].smallCube, iter->second,P ) ) {
				putSmallCube( bigCube, smallCubes[i].smallCube, iter->second );
				posOfSmall[ smallCubes[i].index ] = iter->second;
				//vectorToMap( bigCube, mapNums );
				break;
			}
		}
	}

	//******************//
	
	//******output data**//	
	/*
	// output SmallCubes
	for( int i = 0; i < N; ++ i )
		cout << smallCubes[i].index << endl;
	cout << "big:" << endl;
	// output MagicCube
	bigCube.printCube();
	cout << "small::" << endl;
	for( int i = 0; i < N; ++ i ) {
		cout << i << endl;
		smallerCube[i].printCube();
	}
	// output map
	cout << "multimap:" << endl;
	for( iter = mapNums.begin(); iter != mapNums.end(); ++ iter )
		cout << iter->first << ":" << iter->second << endl;
	cout << endl;
	*/
	//output solution
	for( int i = 0; i < N; ++ i ) {
		int index1,index2,index3;
		bigCube.locToPos( posOfSmall[i], index1, index2, index3 );
		cout << index1 << " " << index2 << " " << index3 << endl;
	}
	//******************//
	return 0;
}

void MagicCube::printCube() 
{
	for( unsigned int i = 0; i < nums.size(); ++ i ) {
		int index1,index2,index3;
		locToPos( i, index1, index2, index3 );
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

void MagicCube::locToPos( const int &location, int &index1, int &index2, int &index3 )
{
	int left = location;
	index1 = left / ( len * len );
	left -= index1 * len * len;
	index2 = left / len;
	left -= index2 * len;
	index3 = left;
}

bool MagicCube::isAllZeros()
{
	for( unsigned int i = 0; i < nums.size(); ++ i ) {
		if( nums.at(i) != 0 )
			return false;
	}
	return true;
}

void MagicCube::setLen( int len )
{
	this->len = len;
}

void putSmallCube( MagicCube &bigCube, const MagicCube &smallCube, int location )
{
	for( int i = 0; i < smallCube.len; ++ i )
		for( int j = 0; j < smallCube.len; ++ j )
			for( int k = 0; k < smallCube.len; ++k ) {
				int bigPos = location + k + j * bigCube.len + i * bigCube.len * bigCube.len;
				bigCube.nums.at( bigPos) = 0;
			}
	
}

bool isRightLocation( const MagicCube &bigCube, const MagicCube &smallCube, int location, int P )
{
	for( int i = 0; i < smallCube.len; ++ i )
		for( int j = 0; j < smallCube.len; ++ j )
			for( int k = 0; k < smallCube.len; ++k ) {
				int smallPos = k + j * smallCube.len + i * smallCube.len * smallCube.len;
				int bigPos = location + k + j * bigCube.len + i * bigCube.len * bigCube.len;
				if( ( bigCube.nums.at( bigPos ) + smallCube.nums.at( smallPos ) ) % P != 0 )
					return false;
			}
	return true;
}

void vectorToMap( const MagicCube &bigCube, multimap<int,int> &mapNums )
{
	mapNums.clear();
	for( unsigned int i = 0; i < bigCube.nums.size(); ++ i )
	{
		mapNums.insert( pair<int,int>( bigCube.nums.at(i), i ) );
	}
}

bool compare( SmallCubes smallOne, SmallCubes smallAnother )
{
	return smallOne.smallCube.len > smallAnother.smallCube.len;
}
