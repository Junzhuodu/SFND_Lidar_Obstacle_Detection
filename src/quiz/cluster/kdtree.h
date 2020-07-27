/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "../../render/render.h"


// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	void insertHelper(Node** node, uint depth, std::vector<float>point, int id) {
		if (!(*node)) 
			*node = new Node(point, id); 
		else {
			uint currDim = depth % 2; 
			if (point[currDim] < (*node)->point[currDim]) 
				insertHelper(&((*node)->left), depth + 1, point, id);
			else
				insertHelper(&((*node)->right), depth + 1, point, id);
		}
	}

	void insert(std::vector<float> point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
		insertHelper(&root, 0, point, id);

	}

	void searchHelper(const std::vector<float>& target, Node* root, float distanceTol, uint depth, std::vector<int>& ids) {
		if (!root) return;
		float left_dist_x = target[0] - distanceTol - root->point[0];
		float right_dist_x = target[0] + distanceTol - root->point[0];		
		float left_dist_y = target[1] - distanceTol - root->point[1];
		float right_dist_y = target[1] + distanceTol - root->point[1];
		if (left_dist_x <= 0 && right_dist_x >= 0 && left_dist_y <= 0 && right_dist_y >= 0) {
			float distance = sqrt(pow(target[0] - root->point[0], 2) + pow(target[1] - root->point[1], 2));
			if (distance <= distanceTol)
				ids.push_back(root->id);
		}

		if (target[depth % 2] - distanceTol < root->point[depth % 2])
			searchHelper(target, root->left, distanceTol, depth + 1, ids);
		if (target[depth % 2] + distanceTol > root->point[depth % 2])
			searchHelper(target, root->right, distanceTol, depth + 1, ids);
	}

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;
		std::cout << "target: " << target[0] << "," << target[1] << " distTol: " << distanceTol << std::endl;
		searchHelper(target, root, distanceTol, 0, ids);
		return ids;
	}
	

};




