# COMP2412-DataStructures-Assignment3
## Mariam M
## Submission Note
All assignment questions and C++ implementations were completed by the assignment deadline.
At the time of submission I didn't have access to my regular development laptop/environment, including Docker/WSL and the CMake environment used for COMP2412. I therefore compiled and tested the individual C++ files using Godbolt Compiler Explorer [ godbolt.com in C++ ] to verify that they run correctly.
The CMake project files will be added/sent as soon as I regain access to my regular development environment. I'm submitting the completed source code and README now so that the completed work is recorded before the deadline.
Also- took calc in hs and work as calc tutor, hence calc stuff mentioned.

## 1a
Big O describes an asymptotic upper bound on an algorithm's growth rate, while Big Theta describes a tight bound. If f(n)∈Θ(g(n)), then f(n) grows at the same asymptotic rate as g(n). A function can belong to a Big O class that is not its tightest class.

## 1bi

So given the following ratio;

[The limit as n approaches infinity of f(n)/g(n) ]

of f(n)=n^2+3n+2 and g(n)=4n^2+2

= lim n->inf  n^2+3n+2/4n^2+2
    
= lim as n->inf  n^2+3n+2/4n^2+2 [take every term and divide by n^2]
(strat to use frm calc to solve limit)
    
= lim as n->inf   (n^2/n^2)+(3n/n^2)+(2/n^2)/(2n^2/n^2)+(2/n^2) 
(any fraction where degree on bottom is larger than degree on top is equal to essentially 0)

= lim as n->inf   (1)+(0)+(0)/(4)+(0)
= lim as n->inf   (1)/(4)
= (1)/(4)

So the limit n->inf of f(n)/g(n) is 1/4 (ie: a pos constant)

Therefore they are both quadratic, f(n) is in big theta of g(n), and have the same order of growth.

## 1bii

Given the following functions;

f(n)=2^n and g(n)=n^5

We know that a function with a fixed degree will grow much slower than an exponential function, which will grow... exponentially.

This means that f(n) will be bigger than g(n), when n is a decently large number. 

Therefore
=lim as n->inf of f(n)/g(n)
(think of what happens to f(n) as n becomes extremely large, and as g(n) becomes extremely large. f(n) will be larger past the point where the 2 functions intersect, therefore the number on the top of the fraction will be bigger) 
=lim as n->inf of big#/smaller#
=lim as n->inf is inf, because bigger number divided by smaller number will always get larger and larger.

Therefore f(n) grows faster than g(n), so f(n) is in Big Omega of g(n). Similarly, g(n) is in Big O of f(n).

## 1biii

Given the following functions; 
f(n)=log(n) and g(n)=n

=lim as n->inf of f(n)/g(n)
=lim as n->inf of log(n)/n 
(this is an inf/inf situation in calculus speak, ie; an indeterminate form. So apply l'hopitals rule, derive top and bottom)
=lim as n->inf of (1/n)/1
=lim as n->inf is (1/n)
(if n just keeps growing and growing, the quotient will keep getting smaller and smaller, eventually being basically 0)
=lim as n->inf is 0

Therefore log growth is slower than linear growth, or f(n) is in big O with g(n), or similarly g(n) is in big omega with f(n). 

## 1biv

Given the functions;

f(n)=n! and g(n)=2^n

and 
=lim as x->inf of f(n)/g(n)
=lim as x->inf of n!/2^n
(since factorials have faster growth rate than exponential func, fraction eventually grows faster than exponential growth when n gets infinitely bigger)
= lim as x->inf is inf 
 
Therefore f(n) is in omega with g(n), or similarly, g(n) is in big O with f(n)

## 1ci

Insertion Sort:
basically treats the start of the array as the part that is already sorted
starting at the second item, save current value as the key

then compare key to vals before it. If vals before it are larger, move them one position to the right until correct location for key is found

So idea is basically:
current key -> check vals before key -> shift larger vals right -> put key into correct spot

Worst case would be something like array already sorted in reverse order

In that case:
first key may need 1 comparison/move
next may need 2
next may need 3
etc.

So total is:
1 + 2 + 3 + ... + (n-1)
which grows quadratically
Therefore worst case time complexity for insertion sort is theta(n^2)

## 1cii

Merge Sort:
recursively divide range;

MERGE_SORT(A,left,right)
    if left >= right:
        return
    middle = floor((left + right) / 2)
    MERGE_SORT(A,left,middle)
    MERGE_SORT(A,middle+1,right)
    MERGE(A,left,middle,right)

Basically array gets split in half again and again until each section is only 1 item
Then the pieces get merged back together in sorted order
During merge, compare current vals from the left + right sections and take whichever is smaller
There are around log(n) levels of splitting, and each level eventually has to deal with all n items during merge

So:
n work per level * log(n) levels
Therefore Merge Sort time complexity is theta(n log n).

## 1ciii

AVLSort:

Based on AVLTreeExample.cpp from class.

general idea:
input array -> insert vals into AVL -> balance when needed -> inorder traversal -> sorted result

The AVL tree is also a binary search tree, so vals smaller than a node go left and vals larger go right
Unlike normal BST, the AVL keeps itself balanced. The balance code checks heights and uses left/right rotations if a side gets too tall
After all input vals have been inserted, doing an inorder traversal:
left -> root -> right
gives the vals in ascending order

Since AVL stays balanced, height is around log(n)
So one insert takes big O(log n)
Doing this n times:
n * log(n)
= big O(n log n)

Then inorder traversal visits all n nodes once, so that part is big O(n)
Therefore total AVLSort time is theta(n log n).

## 2

For question 2 I implemented a Min Heap
For the heap array I left index 0 unused, meaning the first actual item/root is at index 1

This lets the tree positions be found using:
parent = i / 2
left child = 2 * i
right child = 2 * i + 1

### Insert

When inserting value, its first put at the next available spot at end of heap
Then compare it to its parent
If new val is smaller than parent, swap and continue going upward until min-heap order is correct
Since the heap height is around log(n), Insert is big O(log n)


### getMin

Since this is a MIN heap, smallest item is always at root
Root is heap[1]
So getMin is big O(1)

### extractMin

Save min value from root
Move last item in heap to root
Remove last spot
Then compare new root downward with its children
If one of its children is smaller, swap with smaller child and continue until min-heap order is fixed
This only follows one path through height of heap, therefore extractMin is big O(log n)


### Sorting the 1000 random numbers

Generated 1000 random nums and inserted all of them into MinHeap
Then repeatedly used extractMin and put each returned value into sorted vector
Since extractMin always removes smallest remaining val, output becomes ascending order
For testing, only printed first 30 before + after because printing all 1000 makes output kinda ridiculous, but all 1000 vals are still generated and sorted

Complexity:
n inserts * big O(log n)
= big O(n log n)

Then:
n extractMin calls * big O(log n)
= big O(n log n)
So total heap sort time is theta(n log n)

## 3

Question 3 uses hash table w/ separate chaining
Each slot in table points to a linked list

So if 2 different keys hash to same slot, that is a collision and both can still be stored in that slots linked list instead of replacing one another

### Hash function

Assignment said strings must be keys and also said NOT to use std::hash

The class hash example uses modulo:
h(k) = k mod m
So for string keys I first make a numeric key by adding numeric/character values in the string

Then:
hash location = numeric key mod table capacity

### Load factor

load factor = number of stored items / number of slots
or:
load factor = n / m

Assignment says:
if load factor > 0.75 -> double table
if load factor < 0.25 -> halve table

### Insert

Find slot using hash function
Search linked list to see if key already exists
If already exists, update value
Otherwise make new node and put into linked list
Then increase item count
After insertion, check load factor
If over 0.75, resize table to double capacity

### Search

Hash the key to find correct slot
Then do sequential search through only the linked list at slot
If matching key is found, return its value

### Delete

C++ already uses the word delete as a keyword, so function in code is named removeKey instead
Find correct slot using hash
Search linked list
When matching node found, change pointers so node is removed from chain, then delete
Decrease number of items
Then check load factor
If load factor falls below 0.25, halve table size

### Resizing / rehashing

Important part is that vals CANNOT just stay at same slot when table changes size
Because hash location depends on m/table capacity
So when capacity changes, every existing key gets hashed again and moved into new table
This is rehashing
The resize itself needs to visit all stored items so a resize is big O(n)
However doubling does not happen on every insert

Table sizes grow:
4 -> 8 -> 16 -> 32 -> etc
So resize is occasional instead of every operation
Program also deletes enough values at end to prove table can shrink again

## 4

For question 4, represented each graph using adjacency lists
Assignment doesn't say which order to process adjacent verts in when there are multiple choices, so used alphabetical order consistently [txtbk]
DFS uses stack
BFS uses queue

### DFS

Start by pushing a onto stack
Pop next vert
If not visited, mark visited and print it
Then add its unvisited neighbours to stack
Since stack is LIFO, neighbours are pushed in reverse alphabetical order so alphabetically earliest one gets popped first

### BFS

Start by enqueueing a
Remove/dequeue front vert and print it
Then add unvisited adjacent verts to back of queue
This means verts are processed level-by-level away from starting point

### Graph I

DFS pop sequence starting at a:
a c d f b e

BFS dequeue sequence starting at a:
a c d e f b

The outer g-h-i-j rectangle is a separate connected component from a-f
Since traversal starts at a, g/h/i/j are not reached

### Graph II

DFS pop sequence:
a b c d h g f e

BFS dequeue sequence:
a b e c f d g h

### Graph III

DFS pop sequence:
a b d f c g e

BFS dequeue sequence:
a b c d e f g

### Graph IV

Graph IV is directed, so arrow direction matters.

represented outgoing edges as:
a: c
b: a
c: b, d
d: a

numbers/weights on edges not needed to decide DFS or BFS traversal order for this question
DFS pop sequence:
a c b d

BFS dequeue sequence:
a c b d

## Executables

Question 1ci:
question_1ci

Question 1cii:
question_1cii

Question 1ciii:
question_1ciii

Question 2:
question_2

Question 3:
question_3

Question 4:
question_4
