#include "String.h"

void test_constructor_and_print()
{
	cout<<"Testing constructor and print:"<<endl;
	String s("Hello World");
	cout<<s<<endl;
}

void test_assignment()
{
	cout<<"Testing assignment:"<<endl;
	String s;
	String another_s("some text");
	s=another_s;
	cout<<s<<endl;
}

void test_index()
{
	cout<<"Testing index operator:"<<endl;
	String s("0123456789");
	int size=s.size();
	cout<<s<<endl;
	for(int i=0;i<size;++i)
		cout<<"Index:"<<i<<" "<<s[i]<<endl;
}

void test_reverse()
{
	cout<<"Testing reverse:"<<endl;
	String s("abcdefg123456789");
	cout<<s<<endl;
	cout<<s.reverse()<<endl;
}

void test_indexOf()
{
	cout<<"Testing indexOf:"<<endl;
	String s("asdf asdf 1234 aaaa bbccd");
	cout<<s<<endl;
	cout<<"Index of 'a':"<<s.indexOf('a')<<endl;
	cout<<"Index of '1':"<<s.indexOf('1')<<endl;
	cout<<"Index of 'z':"<<s.indexOf('z')<<endl;
	cout<<"Index of '1234':"<<s.indexOf(String("1234"))<<endl;
	cout<<"Index of 'asdf':"<<s.indexOf(String("asdf"))<<endl;
	cout<<"Index of 'aaa':"<<s.indexOf(String("aaa"))<<endl;
	cout<<"Index of 'bbccdd':"<<s.indexOf(String("bbccdd"))<<endl;
	String ns("banana");
	cout<<ns<<endl;
	cout<<"Index of 'an':"<<ns.indexOf(String("an"))<<endl;
	cout<<"Index of 'baan':"<<ns.indexOf(String("baan"))<<endl;
}

const char* bool_to_str(bool exp)
{
	return exp?"true":"false";
}

void test_operators()
{
	cout<<"Testing operators:"<<endl;
	String s1("123");
	String s2;
	String s3("123");
	String s4("1234");
	cout<<"s1:"<<s1<<endl;
	cout<<"s2:"<<s2<<endl;
	cout<<"s3:"<<s3<<endl;
	cout<<"s4:"<<s4<<endl;
	cout<<"s1==s2?"<<bool_to_str(s1==s2)<<endl;
	cout<<"s1==s3?"<<bool_to_str(s1==s3)<<endl;
	cout<<"s3!=s4?"<<bool_to_str(s3!=s4)<<endl;
	cout<<"s2>s1?"<<bool_to_str(s2>s1)<<endl;
	cout<<"s1<s4?"<<bool_to_str(s1<s4)<<endl;
	cout<<"s1>=s3?"<<bool_to_str(s1>=s3)<<endl;
	cout<<"s2>=s4?"<<bool_to_str(s2>=s4)<<endl;
	cout<<"s2+s4="<<s2+s4<<endl;
	s1+=s3;
	cout<<"s1+=s3"<<s1<<endl;
}

void test_read()
{
	cout<<"Testing read:"<<endl;
    	String s;
	cin>>s;
	cout<<s<<endl;
}
int main()
{
	test_constructor_and_print();
	test_assignment();
	test_index();
	test_reverse();
	test_indexOf();
	test_operators();
	test_read();
	return 0;
}
