// Strategy.  Use recursive composition 
// 
// Benefit:  
//		No more type checking and type casting 
 
 
#include <iostream>
#include <string>
#include <vector>
using namespace std;

///////////////////////////////////////////////////////////////
// Component class 
///////////////////////////////////////////////////////////////
class AbsFile { 
public: 
   virtual void ls() = 0;														//*********
protected: 
   string name_; 
   static int  indent_; 
}; 

int AbsFile::indent_ = 0; 

///////////////////////////////////////////////////////////////
// Leaf class 
///////////////////////////////////////////////////////////////


class File: public AbsFile { 

public: 
   File( char* n ) {  name_= n ; } 

   void ls()																				//*********
	 { 
      for (int i=0; i < indent_; i++)    cout << ' '; 
      cout << name_ << endl; 
	 } 
}; 



///////////////////////////////////////////////////////////////
// Composite  class 
///////////////////////////////////////////////////////////////
class Dir : public AbsFile {  
public: 
	Dir(char* n) 
		: files_(0) //使files_擁有5個元素
	{ 	
		name_ = n; 		
		total_ = 0; 
	}
   void add( AbsFile* f ) { 
	   vector<AbsFile*>::iterator it = find(files_.begin(), files_.end(), f);
	   if (it == files_.end()) {
		   files_.push_back(f);
		   total_++;
	   }	   
   } 
   void remove(AbsFile* f) {
		   vector<AbsFile*>::iterator it = find(files_.begin(), files_.end(), f);
		   if (it != files_.end()) {
			   files_.erase(it);
			   total_--;
		   }
   }


   void ls() {  
	  int i;	  
	  for (i=0; i < indent_; i++)   cout << ' '; 
      cout << name_ << ":" << endl; 
      indent_ += 3; 

	  i = 0;
	  for (auto it = files_.begin(); i < total_; it++, i++)
		  (*it)->ls();
	  /* 或
	  for (i=0; i < total_; i++)
	  files_[i]->ls();
	  */
	  indent_ -= 3;
   } 

private: 
   vector<AbsFile*> files_;
   int       total_; 
}; 

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void main( void ) { 
   Dir   one("1"), two("2"), three("3"); 
   File  a("a"), b("b"), c("c"), d("d"), e("e"); 

   one.add( &a ); 
   one.add( &two ); 
   one.add( &b ); 

   two.add( &c ); 
   two.add( &d ); 
   two.add( &three ); 

   three.add( &e ); 
   one.ls();

   //cout << endl;
   //two.ls();
   //cout << endl;
   //three.ls();


/////////////////////////////
// 1) 實作 remove function
	one.remove( &b );		 
	two.remove( &c );
    one.ls(); 

/////////////////////////////
// 2) add 不加入重複
	one.add( &a );			//重複: 不加入a
    one.ls(); 

/////////////////////////////
// 3) 修改 vector<AbsFile*> files_ 成自動擴展容量的陣列 
		// add 使用 push_back 
		// add 不加入重複
		
    File 	 a1("a1"), a2("a2"), a3("a3"), a4("a4"), a5("a5"), a6("a6"), a7("a7"), a8("a8"), a9("a9"), a10("a10");
	one.add( &a1 );  
	one.add( &a2 );  
	one.add( &a3 );  
	one.add( &a4 );  
	one.add( &a5 );  
	one.add( &a6 );  
	one.add( &a7 );  
	one.add( &a8 );  
	one.add( &a9 );  
	one.add( &a10 );  
	one.ls();
  
	one.add( &a1 );
	one.add( &a2 );
	one.add( &a3 );
	one.add( &a4 );
	one.add( &a5 );
	one.add( &a6 );
	one.add( &a7 );
	one.add( &a8 );
	one.add( &a9 );
	one.add( &a10 );
	one.ls();



	

   system("pause");
} 

/*
輸出:

1:
   a
   2:
      c
      d
      3:
         e
   b

*/