/* 
There is a supplier for mobile phones in locality and he needs a database for mobile phones to be maintained,
the database stores the following information about each of the mobile phones:

> the model name (considering the unique string name for each mobile), 
> price (considering no two mobile have the same price), 
> company (string), 
> camera megapixels (float), 
> colour (string), 
> RAM(integer), 
> battery backup (integer), 
> removable batteries (boolean). 

For Sam, the queries of concern are querying using Mobile Name and price (which are both unique, individual). 
The database is designed  using the AVL tree as the primary data structure. 


The database supports the following operations:

A: Add mobile to the database (name, price, company, camera, colour, RAM, battery, removable battery)
QP: Query database using price (prints “Not Found” in case of any issues)
QN: Query database using Name (prints “Not Found” in case of any issues)
DP: Query database using price and delete model for the database (prints “Not Found” in case of any issues)
DN: Query the database using the Name and delete model for the database (prints “Not Found” in case of any issues)
R: Get all mobile phones with price in a certain range (with price in ascending order)
T: Terminate the programme

Automatically   an auto-increment ID is also assigned to each database entry, 
and  operated id is printed in case of all operations



The inputs to the database and there corresponding outputs are as follows :


Input:
A Nokia 6.2, 12000, Nokia, 24, Grey, 8, 3000, 0
A Samsung Galaxy A12, 10000, Samsung, 8, Red, 6, 5000, 0
A Dell 1001, 13000, Dell, 4.5, Green, 7, 45000, 0
QP 12000
QP 7000
R 11500 14500
DN Nokia 6.2
A Xperia, 15000, Sony, 5.9, Blue, 10, 60000, 1
T

Output:
ID: 1
ID: 2
ID: 3
ID: 1, Nokia 6.2, 12000, Nokia, 24, Grey, 8, 3000, 0
Not Found
ID: 1, Nokia 6.2, 12000, Nokia, 24, Grey, 8, 3000, 0
ID: 3, Dell 1001, 13000, Dell, 4.5, Green, 7, 45000, 0
Deleted ID: 1
ID: 4


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
    char name[100];
    int price;
    char company[100];
    float camera_mp;
    char colour[100];
    int ram;
    int batttery_backup;
    int removable_batteries;
    int id;
	struct node *left;
	struct node *right;
	int height;
}Node;
int max(int a, int b);

int height(Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b)
{
	return (a > b)? a : b;
}
Node* newNode(char *name,int price,char *company,float camera_mp,char *colour,int ram,int batttery_backup,int removable_batteries,int id)
{
	Node* node = (Node*)malloc(sizeof(Node));
    int i;
    i=0;
    while(name[i]!='\0'){
      node->name[i] = name[i];
      i++;  
    }
    node->name[i] = '\0';
    node->price = price;
    //node->company = company;
    i=0;
    while(company[i]!='\0'){
      node->company[i] = company[i];
      i++;  
    }
    node->company[i] = '\0';
    node->camera_mp = camera_mp;
    //node->colour = colour;
    i=0;
    while(colour[i]!='\0'){
      node->colour[i] = colour[i];
      i++;  
    }
    node->colour[i] = '\0';
    node->ram = ram;
    node->batttery_backup = batttery_backup;
    node->removable_batteries = removable_batteries;
    node->id = id;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; 
	return(node);
}
Node *rightRotate(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;


	x->right = y;
	y->left = T2;


	y->height = max(height(y->left),
					height(y->right)) + 1;
	x->height = max(height(x->left),
					height(x->right)) + 1;


	return x;
}
Node *leftRotate(Node *x)
{
	Node *y = x->right;
	Node *T2 = y->left;


	y->left = x;
	x->right = T2;


	x->height = max(height(x->left),
					height(x->right)) + 1;
	y->height = max(height(y->left),
					height(y->right)) + 1;


	return y;
}

int getBalance(Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) -
		height(N->right);
}
Node * minValueNode(Node* node)
{
	Node* current = node;


	while (current->left != NULL)
		current = current->left;

	return current;
}
Node* insert(Node* node,char *name,int price,char *company,float camera_mp,char *colour,int ram,int batttery_backup,int removable_batteries,int id)
{

	if (node == NULL)
		return(newNode(name,price,company,camera_mp,colour,ram,batttery_backup,removable_batteries,id));

	if (price < node->price)
		node->left = insert(node->left,name,price,company,camera_mp,colour,ram,batttery_backup,removable_batteries,id);
	else if (price > node->price)
		node->right = insert(node->right,name,price,company,camera_mp,colour,ram,batttery_backup,removable_batteries,id);
	else 
		return node;

	node->height = 1 + max(height(node->left),
						height(node->right));

	int balance = getBalance(node);


	if (balance > 1 && price < node->left->price)
		return rightRotate(node);

	if (balance < -1 && price > node->right->price)
		return leftRotate(node);

	if (balance > 1 && price > node->left->price)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}


	if (balance < -1 && price < node->right->price)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}
Node* search(Node* root,int price){
    if(root==NULL || root->price==price){
        return root;
    }
    if(root->price>price){
        return search(root->left,price);
    }
    if(root->price<price){
        return search(root->right,price);
    }
}
void print(Node *root){
    float a = root->camera_mp;
    if(a-(int)a ==0){
        printf("ID: %d, %s, %d, %s, %d, %s, %d, %d, %d\n",root->id,root->name,root->price,root->company,(int)a,root->colour,root->ram,root->batttery_backup,root->removable_batteries);
    }
    else{
        printf("ID: %d, %s, %d, %s, %.1f, %s, %d, %d, %d\n",root->id,root->name,root->price,root->company,root->camera_mp,root->colour,root->ram,root->batttery_backup,root->removable_batteries);
    }
}
Node* deleteNode(Node* root, int price)
{

	if (root == NULL)
		return root;

	if ( price < root->price )
		root->left = deleteNode(root->left, price);

	else if( price > root->price)
		root->right = deleteNode(root->right, price);

	else
	{

		if( (root->left == NULL) ||
			(root->right == NULL) )
		{
			Node *temp = root->left ?
						root->left :
						root->right;


			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
			*root = *temp; 
			free(temp);
		}
		else
		{
			
			Node* temp = minValueNode(root->right);

            int i;
            i=0;
            while(temp->name[i]!='\0'){
                root->name[i] = temp->name[i];
                i++;
            }
            root->name[i] = '\0';
            root->price = temp->price;
 
            i=0;
            while(temp->company[i]!='\0'){
                root->company[i] = temp->company[i];
                i++;
            }
            root->company[i] = '\0';
            root->camera_mp = temp->camera_mp;

            i=0;
            while(temp->colour[i]!='\0'){
                root->colour[i] = temp->colour[i];
                i++;
            }
            root->colour[i] = '\0';
            root->ram = temp->ram;
            root->batttery_backup = temp->batttery_backup;
            root->removable_batteries = temp->removable_batteries;
            root->id = temp->id;

			root->right = deleteNode(root->right,
									temp->price);
		}
	}

	if (root == NULL)
	return root;

	root->height = 1 + max(height(root->left),
						height(root->right));

	int balance = getBalance(root);


	if (balance > 1 &&
		getBalance(root->left) >= 0)
		return rightRotate(root);


	if (balance > 1 &&
		getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 &&
		getBalance(root->right) <= 0)
		return leftRotate(root);


	if (balance < -1 &&
		getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}
void inorder_in_range(Node *root,int low,int high){
    if(root==NULL){
        return;
    }
    inorder_in_range(root->left,low,high);
    if(root->price>=low && root->price<=high){
        print(root);
    }
    inorder_in_range(root->right,low,high);
}
Node* insert_by_name(Node* node,char *name,int price,char *company,float camera_mp,char *colour,int ram,int batttery_backup,int removable_batteries,int id)
{

	if (node == NULL)
		return(newNode(name,price,company,camera_mp,colour,ram,batttery_backup,removable_batteries,id));

	if (strcmp(name,node->name)<0)
		node->left = insert_by_name(node->left,name,price,company,camera_mp,colour,ram,batttery_backup,removable_batteries,id);
	else if (strcmp(name,node->name)>0)
		node->right = insert_by_name(node->right,name,price,company,camera_mp,colour,ram,batttery_backup,removable_batteries,id);
	else 
		return node;


	node->height = 1 + max(height(node->left),
						height(node->right));

	int balance = getBalance(node);

	if (balance > 1 && strcmp(name,node->left->name)<0)
		return rightRotate(node);

	if (balance < -1 && strcmp(name,node->right->name)>0)
		return leftRotate(node);

	if (balance > 1 && strcmp(name,node->left->name)>0)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && strcmp(name,node->right->name)<0)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}
Node* search_by_name(Node* root,char* name){
    if(root==NULL || strcmp(name,root->name)==0){
        return root;
    }
    if(strcmp(root->name,name)>0){
        return search_by_name(root->left,name);
    }
    if(strcmp(root->name,name)<0){
        return search_by_name(root->right,name);
    }
}
Node* deleteNode_by_name(Node* root, char *name)
{
	
	if (root == NULL)
		return root;

	if (strcmp(name,root->name)<0)
		root->left = deleteNode_by_name(root->left, name);

	else if(strcmp(name,root->name)>0)
		root->right = deleteNode_by_name(root->right, name);

	else
	{

		if( (root->left == NULL) ||
			(root->right == NULL) )
		{
			Node *temp = root->left ?
						root->left :
						root->right;


			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else 
			*root = *temp; 
			free(temp);
		}
		else
		{
			Node* temp = minValueNode(root->right);

			int i;
            i=0;
            while(temp->name[i]!='\0'){
                root->name[i] = temp->name[i];
                i++;
            }
            root->name[i] = '\0';
            root->price = temp->price;
            //root->company = temp->company;
            i=0;
            while(temp->company[i]!='\0'){
                root->company[i] = temp->company[i];
                i++;
            }
            root->company[i] = '\0';
            root->camera_mp = temp->camera_mp;
            //root->colour = temp->colour;
            i=0;
            while(temp->colour[i]!='\0'){
                root->colour[i] = temp->colour[i];
                i++;
            }
            root->colour[i] = '\0';
            root->ram = temp->ram;
            root->batttery_backup = temp->batttery_backup;
            root->removable_batteries = temp->removable_batteries;
            root->id = temp->id;

			root->right = deleteNode_by_name(root->right,
									temp->name);
		}
	}
    if (root == NULL)
	return root;

	root->height = 1 + max(height(root->left),
						height(root->right));

	int balance = getBalance(root);

	if (balance > 1 &&
		getBalance(root->left) >= 0)
		return rightRotate(root);

	if (balance > 1 &&
		getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 &&
		getBalance(root->right) <= 0)
		return leftRotate(root);

	if (balance < -1 &&
		getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}
int main(){
    Node *root = NULL,*root_name = NULL;
    char s[1000];
    gets(s);
    int id = 1;
    while(s[0]!='T'){
        if(s[0]=='A'){
            int i=2;
            int idx = 0;
            char name[100],company[100],colour[100];
            int price,ram,battery_backup;
            float camera_mp;
            int removable_battery;
            for(int count=0;count<8;count++){
                if(count==0){
                    char word[100];
                    int j =0;
                    while(s[i]!=','){
                        word[j] = s[i];
                        i++;
                        j++;
                        if(s[i]=='\0'){
                            break;
                        }
                    }
                    word[j] = '\0';
                    j=0;
                    while(word[j]!='\0'){
                        name[j] = word[j];
                        j++;
                    }
                    name[j] = '\0';
                }
                if(count==1){
                    char word[100];
                    int j =0;
                    while(s[i]!=','){
                        word[j] = s[i];
                        i++;
                        j++;
                        if(s[i]=='\0'){
                            break;
                        }
                    }
                    word[j] = '\0';
                    price = atoi(word);
                }
                if(count==2){
                    char word[100];
                    int j =0;
                    while(s[i]!=','){
                        word[j] = s[i];
                        i++;
                        j++;
                        if(s[i]=='\0'){
                            break;
                        }
                    }
                    word[j] = '\0';
                    j=0;
                    while(word[j]!='\0'){
                        company[j] = word[j];
                        j++;
                    }
                    company[j] = '\0';
                }
                if(count==3){
                    char word[100];
                    int j =0;
                    int idx_point = 0;
                    while(s[i]!=','){
                        if(s[i]=='.'){
                            idx_point = i;
                        }
                        word[j] = s[i];
                        i++;
                        j++;
                        if(s[i]=='\0'){
                            break;
                        }
                    }
                    word[j] = '\0';
                    camera_mp = atof(word);
                }
                if(count==4){
                    char word[100];
                    int j =0;
                    while(s[i]!=','){
                        word[j] = s[i];
                        i++;
                        j++;
                        if(s[i]=='\0'){
                            break;
                        }
                    }
                    word[j] = '\0';
                    j=0;
                    while(word[j]!='\0'){
                        colour[j] = word[j];
                        j++;
                    }
                    colour[j] = '\0';
                }
                if(count==5){
                    char word[100];
                    int j =0;
                    while(s[i]!=','){
                        word[j] = s[i];
                        i++;
                        j++;
                        if(s[i]=='\0'){
                            break;
                        }
                    }
                    word[j] = '\0';
                    ram = atoi(word);
                }
                if(count==6){
                    char word[100];
                    int j =0;
                    while(s[i]!=','){
                        word[j] = s[i];
                        i++;
                        j++;
                        if(s[i]=='\0'){
                            break;
                        }
                    }
                    word[j] = '\0';
                    battery_backup = atoi(word);
                }
                if(count==7){
                    char word[100];
                    int j =0;
                    while(s[i]!=','){
                        word[j] = s[i];
                        i++;
                        j++;
                        if(s[i]=='\0'){
                            break;
                        }
                    }
                    word[j] = '\0';
                    removable_battery = word[0]=='1'?1:0;
                }
                i++;
                i++;
            }
            root = insert(root,name,price,company,camame : %era_mp,colour,ram,battery_backup,removable_battery,id);
            root_name = insert_by_name(root_name,name,price,company,camera_mp,colour,ram,battery_backup,removable_battery,id);
            printf("ID: %d\n",id);
            id++;
        }
        if(s[0]=='Q' && s[1]=='P'){
            int i=3;
            char temp[100];
            while(s[i]!='\0'){
                temp[i-3] = s[i];
                i++;
            }
            temp[i-3] = '\0';
            int price = atoi(temp);
            Node *search_node_result = search(root,price);
            if(search_node_result!=NULL){
                print(search_node_result);
            }
            if(search_node_result==NULL){
                printf("Not Found\n");
            }
        }
        if(s[0]=='Q' && s[1]=='N'){
            int i=3;
            char name[100];
            while(s[i]!='\0'){
                name[i-3] = s[i];
                i++;
            }
            name[i-3] = '\0';
            Node *search_node_result = search_by_name(root_name,name);
            if(search_node_result!=NULL){
                print(search_node_result);
            }
            if(search_node_result==NULL){
                printf("Not Found\n");
            }
        }
        if(s[0]=='D' && s[1]=='P'){
            int i=3;
            char temp[100];
            while(s[i]!='\0'){
                temp[i-3] = s[i];
                i++;
            }
            temp[i-3] = '\0';
            int price = atoi(temp);
            Node *search_node_result = search(root,price);
            if(search_node_result!=NULL){
                printf("Deleted ID: %d\n",search_node_result->id);
                root_name = deleteNode_by_name(root_name,search_node_result->name);
                root = deleteNode(root,price);  
            }
            if(search_node_result==NULL){
                printf("Not Found\n");
            }
        }
        if(s[0]=='D' && s[1]=='N'){
            int i=3;
            char name[100];
            while(s[i]!='\0'){
                name[i-3] = s[i];
                i++;
            }
            name[i-3] = '\0';
            Node *search_node_result = search_by_name(root_name,name);
            if(search_node_result!=NULL){
                printf("Deleted ID: %d\n",search_node_result->id);
                root = deleteNode(root,search_node_result->price);
                root_name = deleteNode_by_name(root_name,name);
            }
            if(search_node_result==NULL){
                printf("Not Found\n");
            }
        }
        if(s[0]=='R'){
            int k = 2;
            int l = 0;
            int low,high;
            char a[100];
            while(s[k]!=' '){
                a[l] = s[k];
                k++;
                l++;
            }
            k++;
            a[l] = '\0'; 
            low = atoi(a);
            l=0;
            char b[100];
            while(s[k]!='\0'){
                b[l] = s[k];
                k++;
                l++;
            }
            b[l] = '\0';
            high = atoi(b);        
            inorder_in_range(root,low,high);
        }
        gets(s);
    }     

    return 0;
}