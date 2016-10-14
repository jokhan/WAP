/*
 * author: jokhan
 * date: 2016年 10月 14日 星期五 19:59:04 CST
 * function: main.cpp
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

char p[1];

void Int2Str( const int &num, string &str );
bool compare( const string &str1, const string &str2 );


int main()
{
	int num[4] = {3,30,9,34};
	string str[4];
	string result = "";
	for( int i = 0; i < 4; ++ i ) {
		Int2Str( num[i], str[i] );
	}
	sort( str, str + 4, compare );
	for( int i = 0; i < 4; ++ i ) {
		result += str[i];
	}
	cout << result << endl;
}

void Int2Str( const int &num, string &str )
{
	sprintf( p, "%d", num );
	str = p;
}

bool compare( const string &str1, const string &str2 )
{
	int len1 = str1.size();
	int len2 = str2.size();
	while( len1 > 0 && len2 > 0 ) {
		int tmp = str1.at( str1.size() - len1 ) - str2.at( str2.size() - len2 );
		if( tmp != 0 )
			return str1.at( str1.size() - len1 ) > str2.at( str2.size() - len2 );
		-- len1;
		-- len2;
	}
	if( len1 > 0 ) {
		return str1.at( str2.size() ) > str1.at( str2.size() - 1 );	
	} else if ( len2 > 0 ) {
		return str2.at( str1.size() ) > str2.at( str1.size() - 1 );
	} else {
		return true;
	}
}
