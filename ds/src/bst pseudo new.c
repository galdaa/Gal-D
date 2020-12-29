
typedef struct bst bst_t;
typedef struct node node_t;
typedef node_t* bst_iter_t;

struct node
{
	void *data;
	node_t *parent;
	node_t *right;
	node_t *left;
};

struct bst
{
	node_t *dummy; dummy->data=root, dummy->parent=max 
	int (*cmp_func)(const void *data, const void *input);
};


bst_t *BSTCreate(int (*cmp_func)(const void *data, const void *input));
alloc bst for tree/if fail return NULL
alloc node for dummy /if fail free(tree) return NULL
dummy->data = NULL;
dummy->parent = NULL;
dummy->right = NULL;
dummy->left = NULL;

tree->dummy = dummy;
tree->cmp_func = cmp_func;

return 0;


void BSTDestroy(bst_t *tree);
start from End backwards...[][][][][]
if !empty 
	run from root in postorder & free the nodes:
	
	temp = tree->dummy->data;
	
	do
	{
		runner = temp;
		while(NULL != runner->right && NULL != runner->left)
		{
			if(NULL != runner->left)
				runner = runner->left
			else
				runner = runner->right
		} 
		temp = tunner->parent;
		free(runner);
		
	}while (NULL != temp)
	
free(tree->dummy)
free(tree)
	
		

bst_iter_t BSTInsert(bst_t *tree, const void *data);
creat new node

if tree empty
	tree->dummy->parent= new
	tree->dummy->data = new

else
	*opt':	
	if data is bigger then end->parent
		insert right to end->parent & update dummy->parent = new
	
	run until leaf:
		if data is smaller
			go left
		else 
			go right
	if data is smaller
		insert left
	else 
		insert right
	
/*
 * Description: This function is used for removing a given iterator.
 * Only the given iterator is removed, not its sub-tree.
 * If the root iterator is removed, a new root is chosen by the following rule:
 *  - left child, if exists.
 *  - otherwise, right child, if exists.
 *  - otherwise, the tree remains empty.
 * Return value: Nothing.
 * Time complexity: Average: O(log n), Worst: O(n). 
 */
void BSTRemove(bst_iter_t iter); oppsite order
if is leaf
	if iter is dummy->parent update
		dummy->parent=iter->parent
		if iter is root: udate dummy
	free
else if have only one child
	if parent>iter
		iter->parents->right = child
	else
	 	iter->parents->left = child
	
	if iter is root: udate dummy
	free iter
else if have two childrens
	if iter->left have right
		Next(iter)->left = iter->left->right
	swap(iter->left, iter):
		iter->perant-> left/right = iter->left
		iter->left->parent = iter->perant
		iter->left->right = iter->right
	if iter is root: udate dummy
	free iter
	

/********************************* Basic Utility ******************************/

/*
 * Description: This function is used for getting the size of a given BST.
 * pointed by tree (amount of elements).
 * Return value: This function returns the number of elements in the BST  
 * pointed to by tree.
 * Time complexity: O(n).
 */
size_t BSTSize(const bst_t *tree);
	count = 0
	run from root in postorder & count the nodes:
	
	temp = tree->dummy->data;
	
	do
	{
		runner = temp;
		while(NULL != runner->right && NULL != runner->left)
		{
			if(NULL != runner->left)
				runner = runner->left
			else
				runner = runner->right
		} 
		temp = tunner->parent;
		++count
		
	}while (NULL != temp)

/*
 * Description: This function returns whether the given BST is empty.
 * Return value: 1 (true) if the size of BST pointed by tree is 0,
 * 0 (false) otherwise.
 * Time complexity: O(1).
 */ 
int BSTIsEmpty(const bst_t *tree);
	*tree->dummy->data == NULL

int BSTIsSameIter(bst_iter_t one, bst_iter_t other);
return (one->parent == other->parent && 
	one->data == other->data && 
	one->right == other->right && 
	one->left == other->left);
/*
 * Description: This function is used for getting the next iterator 
 * (bst_iter_t) after the provided one.
 * Return value: The function will return the next iterator after the provided.
 * Calling BSTNext(BSTEnd(tree)) will yield itself.
 * Time complexity: Average: O(log n), Worst: O(n). 
 */
bst_iter_t BSTNext(bst_iter_t iter);
if iter == end
	return iter
	
if is no right && parent < iterat
	return NULL	
if there right:
	runner = right
	
	while runner have left go left untill NULL
	
	return runner
else if there parent:
	return parent
/*
 * Description: This function is used for getting the previous iterator 
 * (bst_iter_t) before the provided one.
 * Return value: The function will return the prev iterator before the provided.
 * If the provided iterator is the first iter, the function itself.
 * Time complexity: Average: O(log n), Worst: O(n). 
 */
bst_iter_t BSTPrev(bst_iter_t iter);
if is no left && parent > iterat
	return NULL	
if there left:
	runner = left
	
	while runner have right go right untill NULL
	
	return runner
else if there parent:
	return parent
	
/*
 * Description: This function is used for getting the iterator holding minimal 
 * data (bst_iter_t) of the BST pointed by tree.
 * Return value: The function will return iterator holding minimal data.
 * If the tree is empty, return the end iterator.
 * Time complexity: Average: O(log n), Worst: O(n). 
 */
bst_iter_t BSTBegin(const bst_t *tree); 
	If the tree is empty, return the end iterator.
	
	runner = root

	while runner have left go left untill NULL

	return runner

bst_iter_t BSTEnd(const bst_t *tree); 
return tree->dummy;

void *BSTGetData(bst_iter_t iter);
return iter->data;
/******************************** Advanced ************************************/

/*
 * Description: This function is used for iterating over the given
 * range and performing an action on every node. 
 * The action user's action function should return 0 on success.
 * The function will call the passed action function on each iterator in
 * the range. If one of the calls to the activation function fails (returns a 
 * non 0 value), the iteration stops.
 * Return value: This function returns 0 on success, 1 on failure.
 * Pay attention! If the value of the field by which the tree is sorted will be 
 * changed the whole list is compromised!
 * UB: - if from is smaller than to.
 *     - if from and to are not of the same tree.
 * Time complexity: O(n).
 */
int BSTForEach(bst_iter_t from,
               bst_iter_t to,
               int (*action)(void *data, void *params),
               void *params);
runner = from

while runner->data < to->data
	action(runner->data,params)/if fail stop..
	runner = Next(runner);
/*
 * Description: Traverse the given tree and search for an exact match to value.
 * The search is done using the comparison function which was provided
 * by the user in BSTCreate.
 * Return value: This function returns the found iterator (which contains the
 * desired value) on success, if no match was found return the end iterator.
 * Time complexity: Average: O(log n), Worst: O(n). 
 */
bst_iter_t BSTFind(const bst_t *tree,
                   const void *value);
if tree !empty

	if data is bigger then end->parent
		return End
	
	run from root until leaf:
		if runner->data == value
			return runner
			
		if data is smaller
			go left
		else 
			go right


