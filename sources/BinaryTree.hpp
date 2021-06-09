#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <queue>
#include <memory>
#include <set>
#include <map>




namespace ariel{
    template <typename T>
    
class BinaryTree{
    
    struct Tree{
        int size;
        
        T Value;
        Tree *parent;
        Tree *left;
        Tree *right;
        Tree(const T& val):Value(val){
            size =0;
            
            parent=nullptr;
            left=nullptr;
            right=nullptr;

        }
        ~Tree(){

        }
        Tree(const Tree & copy,Tree * Par=nullptr):Value(copy.Value),parent(Par){
            //cout<<"copy constructor get "<<copy.Value<<endl;
        
            
           if(copy.left){
               //cout<<"left send "<<copy.left->Value<<endl;
               left = new Tree(*copy.left,this);
           }
           else{
               left=nullptr;
           }
           if(copy.right){
              // cout<<"right send "<<copy.right->Value<<endl;
               right = new Tree(*copy.right,this);
           }
           else{
               right=nullptr;
           }
           
           size=copy.size;
           
           
            //cout <<copy.Value<<" val "<<Value<<endl;
            
            

        }
        Tree(Tree && toCopy)noexcept:size(0),Value(toCopy.Value){

        }
       
        Tree& operator=(const Tree& tree) noexcept {
            if(this!=tree){
                return *this;
            }
            
            return *this;
        }
        Tree& operator=(Tree&& tree)noexcept {
            size = 0;
            return *this;
        }

        
        
        
    
       
    };
    

    public:
    
   
    Tree * root;
    
    Tree * FindTree(Tree* node, T data){
        if(!node){
            return nullptr;
        }
        if(node->Value==data){
            return node;
        }
        Tree * templeft = FindTree(node->left,data);
        Tree * tempright = FindTree(node->right,data);
        if(templeft){return templeft;}
        if(tempright){return tempright;}
        return nullptr;

    }
    BinaryTree(Tree * r = nullptr):root(r){     
        
        
       
        
    }
    BinaryTree(const BinaryTree<T> & toCopy){
        
        root = new Tree(*toCopy.root);
       
    }
    BinaryTree(BinaryTree<T> && toCopy)noexcept{
        
        root=nullptr;
       
    }
    
    
    
    
    
    
   
    ~BinaryTree(){
        
        desctruct(root);
        root=nullptr;
        

    }
    void desctruct(Tree * node){
        if(!node){
            return;
        }
        if(node->left){
            desctruct(node->left);
            node->left = nullptr;
        }
        if(node->right){
            desctruct(node->right);
            node->right = nullptr;
        }
        
        delete node;
    }
    
    BinaryTree<T>& operator=(const BinaryTree<T>& ns){
        if(this != &ns){
           if(root){
            
            desctruct(root);
            }
            root = new Tree(*ns.root);
        }
        else{
            return *this;
        }
        
     
        return *this;
    }
    BinaryTree<T>& operator=(BinaryTree<T>&& ns)noexcept {
       
        
        if(root){
            
            desctruct(root);
        }
        root = new Tree(*ns.root);
     
        return *this;
    }

   
    BinaryTree<T>& add_root(T data){    
        if(root){            
            root->Value=data;
        }    
        else{
            
            Tree * temp=nullptr;
            temp = new Tree(data);        
            temp->Value = data;        
            root = temp;
            
        }
                   
        return *this;
    }
        
    
    BinaryTree<T>& add_left(T p ,T a){
        if(!root){
            throw std::invalid_argument("no root added");
        }
        Tree * xparent = FindTree(root,p);
        if(!xparent){
            throw std::invalid_argument("this value doesn't exist ");
        }
        if(xparent->left){
            xparent-> left->Value =a;
        }
        else{
            root->size++;
            Tree * child=nullptr;
            child = new Tree(a);
            child->Value = a;
            child->parent = xparent;        
            xparent->left = child;
              
        }
        
       
        return *this;
    }
        
    
    BinaryTree<T>& add_right(T p,T a){    
        if(!root){
            throw std::invalid_argument("no root added");
        }    
        Tree * xparent =  FindTree(root,p);
        if(!xparent){
            throw std::invalid_argument("this value doesn't exist ");
        }
        if(xparent->right){
            xparent-> right->Value =a;
        }
        else{
        root->size++;
        Tree * child=nullptr;
        child = new Tree(a);
        child->Value = a;
        child->parent = xparent;        
        xparent->right = child;
         
        }
            
        
        return *this;

    }
    
    
    
    enum trav{PRE,IN,POST};

        class iterator{
                struct Tree * Current;
                struct Tree * Previous;
                int _size;
                enum trav _Order;
            public:
                iterator(trav order,Tree * current =nullptr):Current(current){
                    if(Current){
                        _size=Current->size;
                    }
                    else{
                        return;
                    }
                    _Order=order;
                    Previous=nullptr;
                    if(order==trav::POST){                
                        while(Current->right||Current->left){
                            if(!Current->left&&Current->right){
                                goRight();
                         }
                            while(Current->left){
                                goLeft();
                            }
                        }}
                    else if(order==trav::IN){
                        while(Current->left){
                            goLeft();
                        }
                    }
                    else{
                        Previous=Current;
                    }
            
                };
                iterator(){
                    Current=nullptr;
                    Previous=nullptr;
                    _size=0;

                    }
                     
                iterator& operator++(){        
                    if(!Current){
                        return *this;
                    }
                    if(_Order==trav::POST){
                        postorder();
                    }
                    else if(_Order==trav::PRE){
                        preorder();
                    }
                    else{                
                        inorder();                
                    }

                    
                    return *this;
                }

                void preorder(){
                    if(Current->right!=Previous&&Current->left!=Previous&&Current->left){              
                        goLeft();}
                    else if(Current->right!=Previous&&Current->right){
                        goRight();}
                    else if(!Current->parent){
                        Current =nullptr;}
                    else{
                        goUp();
                        ++*this;}
                }

                void inorder(){
                    
                if((Current->left!=Previous&&Current->left)&&Current->right!=Previous){
                        
                        while(Current->left){
                            goLeft();
                        }
                    }
                else if(Current->right!=Previous&&Current->right){
                      
                        goRight();
                        while(Current->left){
                            goLeft();
                        }
                    }            
                else{
                        
                        if(!Current->parent){
                            
                            Current=nullptr;
                            return;
                        }
                        
                        goUp();
                        if((Current->right&&Current->right==Previous)){
                                ++*this;
                               
                        }
                            
                        
                        
                    }
                }
                
                void postorder(){
                    
                    if(Current->left!=Previous&&Current->left&&Current->right!=Previous){
                        while(Current->left){
                            goLeft();
                        }
                    }
                    else if(Current->right!=Previous&&Current->right){
                        goRight();
                        while(!Current->left&&Current->right){
                            goRight();
                        }
                                        
                        while(Current->left){
                            goLeft();
                        }
                    }            
                    else{        
                        if(!Current->parent){
                            Current=nullptr;
                            return;
                        }           
                        goUp();
                            if(Current->right&&Current->right!=Previous){
                            ++*this;
                            }
                        
                    }

                    
                }

                void goLeft(){
                    Previous=Current;
                    Current=Current->left;
                }
                void goRight(){
                    Previous=Current;
                    Current=Current->right;
                }
                void goUp(){
                    Previous = Current;
                    Current = Current->parent;
                }
                Tree* operator-(){
                    return Current;
                }
                T& operator*() const{
                    return Current->Value;
                }
                T* operator->() const{
                    return &Current->Value;
                }
                iterator operator++(int) {
                
                    iterator tmp= *this;
                    ++*this;
                    return tmp;
                }
                

                bool operator!=(const iterator& other) const {
                    
                    return Current!=other.Current;
                }
                bool operator==(const iterator& other) const {
                    
                    return Current==other.Current;
                }

                int size(){
                    return _size;
                }


    };   


    
    iterator begin(){
        
        return iterator{trav::IN,root};
    }
    iterator end(){
        
        return iterator{};
    }
   


    
    
        
    iterator begin_preorder(){
            return iterator{trav::PRE,root};
    }
    iterator end_preorder(){
            return iterator{};
    }
    
    iterator begin_inorder(){
            return iterator{trav::IN,root};
    }

    
    iterator end_inorder(){
        return iterator{};
    }

    iterator begin_postorder(){
        return iterator{trav::POST,root};
    }

    
    iterator end_postorder(){
        return iterator{};
    }
    
    
    int getDepth(Tree * branch,int count){
        
        if(!branch){
            return count-1;
        }
        
        
        return max(getDepth(branch->left,count+1),getDepth(branch->right,count+1));
        

    }
    void getQ(std::queue<T> * g,Tree * te, int depth,int cutoff){
        
        if(depth==cutoff){
            
            g->push(te->Value);
        }
        else{
            if(te->left){
                getQ(g,te->left,depth+1,cutoff);
            }
            else{
                g->push(root->Value);
            }
            if(te->right){
                
                getQ(g,te->right,depth+1,cutoff);
            }
            else{
                g->push(root->Value);
            }



        }    
        
        
        



    }
    

    friend std::ostream& operator<<(std::ostream& os, const BinaryTree<T>& m){
        /*queue<T> g;
        
        int depth = m.getDepth(m.root,0);
        Tree * current = m.root;
        
        for (size_t i = 0; i <= depth; i++)
        {
            m.getQ(&g,m.root,0,i);
        }
        
        T x;
        
        while(!g.empty()){
            x = g.front();
            g.pop();
            os <<x<<" ";
        }
      
        */
            
        
        

 
       
        return os;
    }
    

    
       
};
}
