#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

/*I used the book code that the professor provided on the pdf. I shifted the public and private variables and functions around and changed a little code here and there
In addition, I also got rid of any functions that I haven't used directly*/
/**************************************************************Start of Book Code********************************************************************/
template <typename Comparable>
struct BinaryNode
{
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
        : element( theElement ), left( lt ), right( rt ) { }
};

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinaryNode<Comparable> *root;
    BinarySearchTree( ) :root( NULL )
    {
    }

    BinarySearchTree( const BinarySearchTree & rhs ) : root( NULL )
    {
        *this = rhs;
    }

    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    bool isEmpty( ) const
    {
        return root == NULL;
    }

    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    void insert( const Comparable & x )
    {
        insert( x, root );
    }

  private:
     void insert( const Comparable & x, BinaryNode<Comparable> * & t )
    {
        if( t == NULL )
            t = new BinaryNode<Comparable>( x, NULL, NULL );
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }

    bool contains( const Comparable & x, BinaryNode<Comparable> *t ) const
    {
        if( t == NULL )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }

    void printTree( BinaryNode<Comparable> *t, ostream & out ) const
    {
        if( t != NULL )
        {
            printTree( t->left, out );
            out << t->element << " ";
            printTree( t->right, out );
        }
    }
};
/**************************************************************End of Book Code********************************************************************/

/*Below are my splinter() and prettyPrint() functions. I made a recurisve splinterHelper() to help the splinter() tranverse the BinarySearchTree.*/
/**************************************************************Begining of my Code********************************************************************/
template<typename T> void splinterHelper(BinaryNode<T> *curr, BinarySearchTree<T> *staticTree, BinarySearchTree<T> *sameTree, BinarySearchTree<T> *differentTree)
{
  if(curr == NULL){
    return;
  }

  if(staticTree->contains(curr->element))
  {
    sameTree->insert(curr->element);
  }
  else
  {
    differentTree->insert(curr->element);
  }
  splinterHelper(curr->left, staticTree, sameTree, differentTree);
  splinterHelper(curr->right, staticTree, sameTree, differentTree);
}

template<typename T> void splinter(BinarySearchTree<T> *A, BinarySearchTree<T> *B, BinarySearchTree<T>* &C, BinarySearchTree<T>* &D)
{
  BinaryNode<T> *tempNode = A->root;
  splinterHelper(tempNode, B, C, D);

  tempNode = B->root;
  splinterHelper(tempNode, C, C, D);
}


template<typename T> void prettyPrint(BinaryNode<T> *curr, string linePrefix, string nodeTag, ostream &ofs)
{
  if(curr == NULL)
  {
    return;
  }

  string leftLinePrefix = "  ";
  string rightLinePrefix = "  ";
  string leftNodeTag = " / ";
  string rightNodeTag = " \\ ";

  if(nodeTag == " / ")
  {
    rightLinePrefix = "| ";
  }
  else if(nodeTag == " \\ ")
  {
    leftLinePrefix = "| ";
  }

  if(nodeTag.size() == 0)
  {
    nodeTag = "< ";
  }

  prettyPrint(curr->left, linePrefix + leftLinePrefix, leftNodeTag, ofs);
  ofs << linePrefix << nodeTag << curr->element << endl;
  prettyPrint(curr->right, linePrefix + rightLinePrefix, rightNodeTag, ofs);
}

int main(int argc, char**argv)
{
  if(argc != 2)
	{
		cout << "INVAILD NUMBER OF PARAMETERS" << endl;
		return 1;
	}

	string fileName = argv[1];
	string outputFileName = fileName.substr(0, fileName.size()-4) + ".out";
  ofstream ofs;
  ofs.open(outputFileName.c_str());

  ifstream txt;
  txt.open(fileName.c_str());
  if(!txt.is_open())
  {
      cout << "ERROR----INVALID FILENAME. PLEASE CHECK FOR SPELLING" << endl;
      return 1;
  }

	string temp;
  unsigned testNumber = 1;

  while(getline(txt, temp))
  {
    BinarySearchTree<int> *A = new BinarySearchTree<int>(); //Stores first line
  	BinarySearchTree<int> *B = new BinarySearchTree<int>(); //Stores second line
  	BinarySearchTree<int> *C= new BinarySearchTree<int>(); //Stores common elements in both A and B
  	BinarySearchTree<int> *D= new BinarySearchTree<int>(); //Stores discommon elements in A and B

    int number;
  	stringstream convert(temp);
  	while(convert >> number)
  	{
  		A->insert(number);
  	}

    getline(txt, temp);
    stringstream convertAgain(temp);
    while(convertAgain >> number)
    {
      B->insert(number);
    }

    splinter(A, B, C, D);

    ofs << "TEST CASE: " << testNumber << endl;
    A->printTree(ofs); ofs << endl;
  	B->printTree(ofs); ofs << endl;
  	C->printTree(ofs); ofs << endl;
  	D->printTree(ofs); ofs << endl << endl;

    prettyPrint(A->root, "", "", ofs);
    ofs << endl;
    prettyPrint(B->root, "", "", ofs);
    ofs << endl;
    prettyPrint(C->root, "", "", ofs);
    ofs << endl;
    prettyPrint(D->root, "", "", ofs);
    ofs << endl;

    testNumber++;
  }
	txt.close();
}
/**************************************************************End of my Code********************************************************************/
