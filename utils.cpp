#include <iostream>
using namespace std;
#define FILE_COUNT 5

class S_Node {
public:
    string data;
    S_Node* next;
    S_Node(string val) {
        data = val;
        next = nullptr;
    }
};

class FNF{
public:
    string file_Name;
    int frequency;

    FNF() { file_Name = ""; frequency = 0; } 
    FNF(string v,int f){
        frequency=f;
        file_Name=v;
    }
};

class Node {
public:
    string word;
    FNF *arr;
     int index=0;
    Node *left;
    Node *right;
    int height;

    Node(string d){
        word = d;
        height = 0;
        arr = new FNF[FILE_COUNT]; 
        left = right = NULL;
    }   
    
    ~Node() { 
	delete[] arr;
	 }

    
    void add_FNF(string f,int fr){
    if(index<FILE_COUNT){
    	arr[index++]=FNF(f,fr);
    	return;
	}
    cout<<"FNF out of bound";
    return;
    	
	}


	
	void inc_frequency(string file_name){
	for(int i=0;i<index;i++){
		if(file_name==arr[i].file_Name){
			arr[i].frequency++;
			return;
		}
	}
	add_FNF(file_name,1);
	}
};

class Stack {
private:
    S_Node* top;
public:
    Stack() {
        top = nullptr;
    }

    void push(string url) {
        S_Node* newNode = new S_Node(url);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (top == nullptr) {
            cout << "History is empty" << endl;
            return;
        }
        S_Node* temp = top;
        top = top->next;
        delete temp;
    }

    string peek() {
        if (top == nullptr) {
            return "";
        }
        return top->data;
    }

    void display() {
        if (top == nullptr) {
            cout << "History is empty" << endl;
            return;
        }
        cout << "Browsing History:" << endl;
        S_Node* temp = top;
        int count = 1;
        while (temp != nullptr) {
            cout << count << ". " << temp->data << endl;
            temp = temp->next;
            count++;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};


class Queue {
private:
    S_Node* front;
    S_Node* rear;
    int count;
    const int MAX_SIZE = 5;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    void enqueue(string url) {
        if (count >= MAX_SIZE) {
            dequeue();
        }
        
        S_Node* newNode = new Node(url);
        
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }

    void dequeue() {
        if (front == nullptr) {
            return;
        }
        S_Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        count--;
    }

    void display() {
        if (front == nullptr) {
            cout << "No recent searches" << endl;
            return;
        }
        cout << "Recent 5 Searches:" << endl;
        S_Node* temp = front;
        int position = 1;
        while (temp != nullptr) {
            cout << position << ". " << temp->data << endl;
            temp = temp->next;
            position++;
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }
};v

class Avl{
public:
int maxi(int d1,int d2){
    return d1>d2?d1:d2;
}

int calculate_Height(Node *root){
    if(root==NULL) return -1;
    return 1 + maxi(calculate_Height(root->left), calculate_Height(root->right));
}

int bf(Node *root){
    if(root==NULL) return 0;
    int lh = root->left ? root->left->height : -1;
    int rh = root->right ? root->right->height : -1;
    return lh - rh;
}

Node* rotate_right(Node *root){
    Node *x = root->left;
    Node *temp = x->right;
    x->right = root;
    root->left = temp;
    root->height = calculate_Height(root);
    x->height = calculate_Height(x);
    return x;
}

Node* rotate_left(Node *root){
    Node *x = root->right;
    Node *temp = x->left;
    x->left = root;
    root->right = temp;
    root->height = calculate_Height(root);
    x->height = calculate_Height(x);
    return x;
}

Node* minValueNode(Node* root){
    Node* current = root;
    while(current && current->left != NULL)
        current = current->left;
    return current;
}

Node* insert(Node * &root, string d,string file_name){
    if(root == NULL) {
    	Node *n=new Node(d);
    	n->add_FNF(file_name,1);
    	return n;
	}
	if(d==root->word){
		root->inc_frequency(file_name);
		return root;
	}
    if(d < root->word)
        root->left = insert(root->left, d,file_name);
    else if(d > root->word)
        root->right = insert(root->right, d,file_name);
    else
        return root;

    root->height = calculate_Height(root);
    int b = bf(root);

    if(b > 1){ // left heavy
        if(d < root->left->word)
            return rotate_right(root);
        else{
            root->left = rotate_left(root->left);
            return rotate_right(root);
        }
    }

    if(b < -1){ // right heavy
        if(d > root->right->word)
            return rotate_left(root);
        else{
            root->right = rotate_right(root->right);
            return rotate_left(root);
        }
    }

    return root;
}

Node* deleteNode(Node* root, string d){
    if(root == NULL) return root;

    if(d < root->word)
        root->left = deleteNode(root->left, d);
    else if(d > root->word)
        root->right = deleteNode(root->right, d);
    else {
        if(root->left == NULL || root->right == NULL){
            Node* temp = root->left ? root->left : root->right;
            if(temp == NULL){
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->word = temp->word;
            root->right = deleteNode(root->right, temp->word);
        }
    }

    if(root == NULL) return root;

    root->height = calculate_Height(root);
    int b = bf(root);

    if(b > 1){
        if(bf(root->left) >= 0)
            return rotate_right(root);
        else{
            root->left = rotate_left(root->left);
            return rotate_right(root);
        }
    }

    if(b < -1){
        if(bf(root->right) <= 0)
            return rotate_left(root);
        else{
            root->right = rotate_right(root->right);
            return rotate_left(root);
        }
    }

    return root;
}

void printarr(int j,Node *root){
	for(int i=0;i<j;i++){
		cout<< " "<<root->arr[i].file_Name<< " "<<root->arr[i].frequency<<" " ;
	}
	cout<<endl;
}

void inorder(Node* root){
    if(root == NULL) return;
    inorder(root->left);
    cout << root->word << " ";
    printarr(root->index,root);
    inorder(root->right);
}
};
class heap{
	public:
	int arr[1000];
	int size;
	
	heap(){
		size=0;
	}
	
	void insert(int d){
		if(size==1000)return;
		size++;
		arr[size]=d;
		int i=size;
		while(i>1){
			int parent=i/2;
			
			if(arr[parent]<arr[i]){
			   swap(arr[parent],arr[i]);
			   i=parent;
			}else{
				return;
			}
			
		}
	}
	
	void delete_from_heap(){
		if(size==0)return;
		arr[1]=arr[size];
		size--;
		heapify(arr,size,1);
	}
	
	void heapify(int arr1[],int size1,int i){
		int tobesort=i;
		int left=2*i;
		int right=2*i+1;
				
		if(left<=size1&&arr1[left]>arr1[tobesort]){
			tobesort=left;
		}
		 if(right<=size1&&arr1[right]>arr1[tobesort]){
		tobesort=right;
		}
		
		if(i!=tobesort){
			swap(arr1[tobesort],arr1[i]);
			heapify(arr1,size1,tobesort);
		}
	
	
	}
	
	void heap_sort(){
		for(int i=size;i>1;i--){
			swap(arr[i],arr[1]);
		heapify(arr,i-1,1);
		}
	}
};

//int main(){
//   
//    int arr[5]={3,42,8,32,77};
//    heap h;
//   for(int i=(5/2)-1;i>=0;i--){
//    h.heapify(arr,4,i);
//}
//	
//	for(int i=0;i<5;i++){
//		cout<<arr[i]<<" ";
//	}
//
//    return 0;
//}
