#include<stdio.h>
#include<stdlib.h>
int count=0;
struct node {
	int data;
	struct node *left, *right, *parent;
}*root = 0;


int height(struct node *ptr) {	
	int l_count = 0, r_count = 0;
	if(ptr != 0) {
			l_count = 1 + height(ptr->left);
			r_count = 1 + height(ptr->right);
			return (l_count > r_count)? l_count: r_count;
	} else return 0;
}

int difference(struct node *ptr) {
		return height(ptr->left) - height(ptr->right);
}

void rotateLeft(struct node *ptr, struct node *pivot) {
	struct node *temp = 0;
	pivot->parent = ptr->parent;
	if(ptr->parent != 0) {
		if(ptr == (ptr->parent)->right)
			(ptr->parent)->right = pivot;
		else
			(ptr->parent)->left = pivot;
	} else {
			pivot->parent = 0;
			root = pivot;
	}
	if(pivot->left != 0)
			temp = pivot->left;
	pivot->left = ptr;
	(pivot->left)->right = temp;
	ptr->parent = pivot;
}

void rotateRight(struct node *ptr, struct node *pivot) {
	struct node *temp = 0;
	pivot->parent = ptr->parent;
	if(ptr->parent != 0) {
		if(ptr == (ptr->parent)->left)
			(ptr->parent)->left = pivot;
		else
			(ptr->parent)->right = pivot;
	} else {
			pivot->parent = 0;
			root = pivot;
	}
	if(pivot->right != 0)
			temp = pivot ->right;
	pivot->right = ptr;
	(pivot->right)->left = temp;
	ptr->parent = pivot;
}

void balance(struct node *ptr) {
	if(difference(ptr) == 0)
			return;
	else if(difference(ptr) == -2) {
		if(difference(ptr->right) <= 0)
				rotateLeft(ptr,ptr->right);	//RR
		else {								//RL
				rotateRight(ptr->right,(ptr->right)->left);
				rotateLeft(ptr, ptr->right);
		}
	} else if(difference(ptr) == 2) {
		if(difference(ptr->left) > 0)
				rotateRight(ptr,ptr->left); //LL
		else {								//RL
				rotateLeft(ptr->left,(ptr->left)->right);
				rotateRight(ptr,ptr->left);
		}
	} else {

		if(ptr->left != 0)
				balance(ptr->left);
		if(ptr->right != 0)
				balance(ptr->right);
	}
	
}
void delete(struct node *ptr, int data)
{
	if(ptr->data > data)
		delete(ptr->left, data);
	else if(ptr->data < data)
		delete(ptr->right, data);
	else
	{
		struct node *temp=0, *temp1=0;
		if(ptr->left == 0 && ptr->right == 0) {
			if(ptr->parent->left == ptr)
				ptr->parent->left = 0;
			else ptr->parent->right = 0;
			free(ptr);
		}
		else if(ptr->left != 0){
			temp = ptr->left;
			temp1 = temp->right;
			while(temp1 != 0)
				temp1 = temp1->right;
			temp->data = temp1->data;
			if(temp1->parent->left ==temp1)
					temp1->parent->left = 0;
			else temp1->parent->right = 0;
			free(temp1);

		}
		else {
			temp =ptr->right;
			temp1 = temp->left;
			while(temp1 != 0)
					temp1 = temp1->left;
			temp->data = temp1->data;
			if(temp1->parent->left ==temp1)
					temp1->parent->left = 0;
			else temp1->parent->right = 0;
			free(temp1);
		}

	}
	balance(root);
}

struct node * create(struct node * ptr, int data) {
		struct node *new = malloc(sizeof(struct node));
		new->data = data;
		new->parent = ptr;
		new->left = 0;
		new->right = 0;
		return new;
}
void insert(struct node *ptr, int data) {	
	if(ptr == 0 && ptr == root)
			root = create(ptr, data);
	else if((data > ptr->data) && (ptr->right != 0))
			insert(ptr->right, data);
	else if(data > ptr->data)
			ptr->right = create(ptr, data);
	else if((data < ptr->data) && (ptr->left != 0))
			insert(ptr->left, data);
	else
			ptr->left = create(ptr, data);
	balance(root);
}
void inorder(struct node *ptr) {
	if(ptr != 0) {
			inorder(ptr->left);
			printf("%d \t",ptr->data);
			inorder(ptr->right);
	}
}
	
void preorder(struct node *ptr) {
	if(ptr != 0) {
			printf("%d \t",ptr->data);
			preorder(ptr->left);
			preorder(ptr->right);
	}
}

void postorder(struct node *ptr)
{
	if(ptr != 0) {
			postorder(ptr->left);
			postorder(ptr->right);
			printf("%d \t",ptr->data);
	}
}
main() {
	struct node *a;
	root = 0;
	insert(root, 23);
	insert(root,16);
	insert(root,25);
	insert(root,14);
	insert(root,27);
	insert(root,12);
	insert(root,28);
	insert(root,29);
	printf("Inorder:\t");
	inorder(root);
	printf("\nPreorder:\t");
	preorder(root);
	printf("\nPostorder:\t");
	postorder(root);
	printf("\nDeleting the data: 16\n");
	delete(root, 16);
	balance(root);
	printf("Inorder:\t");
	inorder(root);
	printf("\nPreorder:\t");
	preorder(root);
	printf("\nPostorder:\t");
	postorder(root);
}
