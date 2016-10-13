/*
 * author: jokhan
 * date: 2016.10.1
 * function: main.cc
 */
#include <iostream>
#include <map>

using namespace std;

struct RoomNode {
	int index;
	RoomNode *next;
	RoomNode( int x ): index(x), next(NULL){}
};

struct RoomHead {
	int totalSati;    // the satisfaction of room i if a router is put in it
	RoomNode *next;
	RoomHead(int x): totalSati(x), next(NULL){}
	RoomHead(): totalSati(0), next(NULL){}
};

void addNode( RoomHead &head, int index );
bool delNode( RoomHead &head, int index );
//transfer S[index-1] into zero, and the total S of adjacent room is changed
void selfZeroSati( map<int, RoomHead> &mapHead, int index, int S[] );
void delHead( map<int, RoomHead> &mapHead, int index, int S[] );
int maxMapHead( map<int, RoomHead> &mapHead );
void printRoom( const RoomHead &head );

int main()
{
	//****input data****/
	int N;  // the number of rooms
	int M;  // the number of routers
	cin >> N;
	cin >> M;
	int S[N];
	//RoomHead head[N];
	map<int, RoomHead> mapHead;
	map<int, RoomHead>::iterator iter;
	for( int i = 0; i < N; i ++ ) {
		cin >> S[i];
		RoomHead *tmp = new RoomHead( S[i] );
		mapHead[i + 1] = *tmp;
	}
	for( int i = 0; i < N - 1; ++ i ) {
		int tmpx, tmpy;
		cin >> tmpx >> tmpy;
		addNode( mapHead[tmpx], tmpy );
		mapHead[tmpx].totalSati += S[tmpy - 1];
		addNode( mapHead[tmpy], tmpx );
		mapHead[tmpy].totalSati += S[tmpx - 1];
	}
	//******************//
	
	//*****solution*****//
	int answer = 0;
	int index;
	for( int i = 0; i < M; ++ i ) {
		index = maxMapHead( mapHead );
		answer += mapHead[index].totalSati;
		delHead( mapHead, index, S );
	}
	//******************//
	
	//****output data****//
	/*
	//output map
	//delHead( mapHead, 3, S );
	for( iter = mapHead.begin(); iter != mapHead.end(); ++ iter ) {
		cout << iter->first; 
		printRoom( iter->second );
	}
	//output S
	for( int i = 0; i < N; i ++ ) {
		cout << S[i] << " "; 
	}
	cout << endl;
	*/
	//output result
	cout << answer << endl;
	//cout << endl;
	//******************//
	return 0;
}

void addNode( RoomHead &head, int index)
{
	RoomNode *p = new RoomNode( index );
	p->next = head.next;
	head.next = p;
}

bool delNode( RoomHead &head, int index )
{
	if( (head.next)->index == index ) {
		head.next = (head.next)->next;
		return true;
	}
	RoomNode *p = head.next;
	while( p->next != NULL ) {
		if( p->next->index == index ) {
			p->next = p->next->next;
			return true;
		}
	}
	return false;
}

void selfZeroSati( map<int, RoomHead> &mapHead, int index, int S[] )
{
	RoomNode *p = mapHead[index].next;
	mapHead[index].totalSati -= S[index-1];
	while( p != NULL ) {
		RoomHead *pHead = &mapHead[p->index];
		//delNode( *pHead, index );
		pHead->totalSati -= S[ index - 1 ];
		//selfZeroSati( mapHead, p->index, S );
		p = p->next;
	}
	S[index-1] = 0;
	//delete it from the map
}

void delHead( map<int, RoomHead> &mapHead, int index, int S[] )
{
	selfZeroSati( mapHead, index, S );
	RoomNode *p = mapHead[index].next;
	//close the door
	while( p != NULL ) {
		RoomHead *pHead = &mapHead[p->index];
		delNode( *pHead, index );
		selfZeroSati( mapHead, p->index, S );
		p = p->next;
	}
	mapHead[index].next = NULL;
	mapHead[index].totalSati = 0;
	//delete it from map
	map<int, RoomHead>::iterator iter;
	iter = mapHead.find( index );
	mapHead.erase( iter );
	
}

int maxMapHead( map<int, RoomHead> &mapHead )
{
	int index;
	int max = -1;
	map<int, RoomHead>::iterator iter;
	for( iter = mapHead.begin(); iter != mapHead.end(); ++ iter ) {
		if( (iter->second).totalSati > max ) {
			max = (iter->second).totalSati;
			index = iter->first;
		}
	}
	return index;
}

void printRoom( const RoomHead &head )
{
	cout << " |" << head.totalSati << "| ";
	RoomNode *p = head.next;
	while( p != NULL ) {
		cout << p->index << "-";
		p = p->next;
	}
	cout << "NULL" << endl;
}
