#include <iostream>
using namespace std;
class String
  {
  public:
    /// Both constructors should construct
    /// this String from the parameter s
    String( const char * s = "");
    String( const String & s );
    String& operator = ( const String & s );
    char & operator [] ( int index );
    int size();
    String reverse(); // does not modify this String
    int indexOf( const char c );
    int indexOf( const String& pattern );
    bool operator == ( const String& s );
    bool operator != ( const String& s );
    bool operator > ( const String& s );
    bool operator < ( const String& s );
    bool operator <= ( const String& s );
    bool operator >= ( const String& s );
    /// concatenates this and s to return result
    String operator + ( const String& s );
    /// concatenates s onto end of this
    String& operator += ( const String& s );
    void print( ostream & out ) const;
    void read( istream & in );
    ~String();
    static void final_report_on_allocations()
    {
      if (allocations > 0) error("Memory Leak in class String");
      if (allocations < 0) error("Too many delete[]s in class String");
      if (allocations == 0)
      cout << "Allocations & deallocations match\n";
    }
    static int allocations;
  private:
    bool inBounds( int i )
    {
      return i >= 0 && i < strlen(buf);
    }
    static char * new_char_array( int n_bytes )
    {
      ++allocations;
      return new char[n_bytes];
    }
    static void delete_char_array( char * p )
    {
      --allocations;
      if (allocations < 0) error("more delete[] than new[]");
      delete [] p;
    }
    static void error( const char * p )
    {
      cerr << "Error (class String): " << p << endl;
    }
    void dynamic_alloc(const char *src);
    static int strlen(const char *src);
    static char *strdup(const char *src); // notice this new function
    static char * strcpy( char *dest, const char *src );
    static char * strcat(char *dest, const char *src);
    static int strcmp( const char *left, const char *right );
    static int strncmp( const char *left, const char *right, int n );
    static char * strchr( char *str, int c );
    static char * strstr( char *haystack, char *needle ); 
    static const char * strchr( const char *str, int c );
    static const char * strstr( const char *haystack, const char *needle );
    char * buf; // base of array for the characters in this string
    // DO NOT add a length data member!! use the null terminator
  };
  ostream & operator << ( ostream & out, const String& str );
  istream & operator >> ( istream & in, String & str );
