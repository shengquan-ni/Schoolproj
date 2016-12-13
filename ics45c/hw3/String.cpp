#include "String.h"
#include <cassert>
String::String(const char* s)
{
	strcpy(buf,s);
}

String::String(const String& s)
{
	strcpy(buf,s.buf);
}

String& String::operator = (const String &s)
{
	if(this!=&s)
		strcpy(buf,s.buf);
	return *this;
}

char& String::operator [] (int index)
{
	assert(inBounds(index));
	return buf[index];
}

int String::size()
{
	return strlen(buf);
}

String String::reverse()
{
	String res(buf);
	int s=size();
	for(int i=0;i<s/2;++i)
	{
		char temp=res.buf[i];
		res.buf[i]=res.buf[s-i-1];
		res.buf[s-i-1]=temp;
	}
	return res;
}

int String::indexOf(const char c)
{
	const char* result=strchr(buf,c);
	return result?result-buf:-1;
}

int String::indexOf(const String& pattern)
{
	const char* result=strstr(buf,pattern.buf);
	return result?result-buf:-1;
}

bool String::operator == (const String& s)
{
	return strcmp(buf,s.buf)==0;
}

bool String::operator != (const String& s)
{
	return strcmp(buf,s.buf)!=0;
}

bool String::operator > (const String& s)
{
	return strcmp(buf,s.buf)>0;
}

bool String::operator < (const String& s)
{
	return strcmp(buf,s.buf)<0;
}

bool String::operator >= (const String& s)
{
	return strcmp(buf,s.buf)>=0;
}

bool String::operator <=(const String& s)
{
	return strcmp(buf,s.buf)<=0;
}

String String::operator + (const String& s)
{
	char newstr[MAXLEN];
	strcpy(newstr,buf);
	strcat(newstr,s.buf);
	return String(newstr);
}

String& String::operator += (const String& s)
{
	strcat(buf,s.buf);
	return *this;
}

void String::print( ostream& out) const
{
	out<<"String: "<<buf;
}

void String::read( istream& in)
{
	char temp[MAXLEN];
	cin>>temp;
	*this+=String(temp);
}

int String::strlen(const char* s)
{
	if(s==NULL)return 0;
	int len=0;
	for(;*s++!='\0';)
		len++;
	return len;
}

char* String::strcpy(char* dest, const char* src)
{
	assert(dest!=NULL && src!=NULL);
	if(dest==src)return dest;
	char* result=dest;
	int srclen = strlen(src);
	if (srclen > MAXLEN - 1)
		for (int i = 0; i < MAXLEN - 1; ++i)
			*dest++ = *src++;
	else
		while((*dest++=*src++)!='\0');
	return result;
}

char* String::strcat(char* dest,const char* src)
{
	assert(dest!=NULL && src!=NULL);
	int destlen=strlen(dest);
	int srclen=strlen(src);
	char* result=dest;
	while(*dest!='\0')dest++;
	if(destlen+srclen>MAXLEN-1)
	{
		int size=MAXLEN-1-destlen;
		for(int i=0;i<size;++i)
			*dest++=*src++;
	}
	else
		while(*src!='\0')*dest++=*src++;
        *dest='\0';
	return result;
}

int String::strcmp(const char* left, const char* right)
{
	assert(left!=NULL && right!=NULL);
	while((*left!='\0' && *right!='\0') && *left==*right)left++,right++;
	return *left-*right;
}

int String::strncmp(const char* left, const char* right, int n)
{
	assert(left!=NULL && right!=NULL);
	for(int i=0;i<n;++i)
		if((*left!='\0' && *right!='\0') && *left==*right)
			++left,++right;
		else
			return *left-*right;
	return 0;
}

char* String::strchr(char* str,int c)
{
	assert(str!=NULL);
	while(*str!='\0' && *str!=c)
		++str;
	return (*str==c)?str:NULL;
}

char* String::strstr(char* haystack, char* needle)
{
	assert(haystack!=NULL && needle!=NULL);
	int needlelen=strlen(needle);
	int haystacklen=strlen(haystack);
	int nextpos[256];
	for(int i=0;i<256;++i)
	{
		nextpos[i]=needlelen+1;
	}
	for(int i=0;i<needlelen;++i)
	{
		nextpos[(unsigned char)needle[i]]=needlelen-i;
	}
	int pos=0,temp,i;
	while(pos<=(haystacklen-needlelen))
	{
		temp=pos;
		for(i=0;i<needlelen;++i,++temp)
		{
			if(haystack[temp]!=needle[i])
			{
				pos+=nextpos[(unsigned char)haystack[pos+needlelen]];
				break;
			}
		}
		if(i==needlelen)
			return haystack+pos;
	}
	return NULL;
}

const char * String::strstr(const char *haystack,const char *needle )
{
	return static_cast<const char*>(strstr(const_cast<char*>(haystack),const_cast<char*>(needle)));
}

const char * String::strchr(const char* str,int c)
{
	return static_cast<const char*>(strchr(const_cast<char*>(str),c));

}

ostream & operator << (ostream& out, const String& str)
{
	str.print(out);
	return out;
}

istream & operator >> (istream& in, String& str)
{
	str.read(in);
	return in;
}
