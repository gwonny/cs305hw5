/* CS 305 HW5
 * Spring 2018
 * Johnny Huang
 * Tic Tac Toe Tree
 *
 * This file controls the the creation of intermediate nodes, winners for nodes, and the computer's decisionmaking
 * gametree.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "gametree.h"

GameNode* createNode(char b[3][3], int row, int col, char player)//creates intermediate nodes after tree (children)
{
	if(b[row][col]!=' ')//if the area is empty, nothing needs to be done
	{
		return NULL;
	}
	else
	{
		GameNode* newnode = (GameNode*)malloc(sizeof(GameNode));//allocates memory for the node
		
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				newnode->board[i][j] = b[i][j];//transfers preexisting node info onto the (current) children's node board
			}
		}
		
		newnode->board[row][col] = player;//puts either human or comp move onto board
		newnode->score = '#';//score is yet to be determined
		newnode->player = player;//assigns current player to node
		
		if(winner(b, player))
		{
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					newnode->children[i][j]=NULL;//if the winner is determined, all children are nulld
				}
			}
		}
		else
		{
			if(player=='O')
			{
				for(int i=0; i<3; i++)
				{
					for(int j=0; j<3; j++)
					{
						newnode->children[i][j]=createNode(newnode->board, i, j, 'X');//else, create children of node with other player
					}
				}
			}
			else
			{
				for(int i=0; i<3; i++)
				{
					for(int j=0; j<3; j++)
					{
						newnode->children[i][j]=createNode(newnode->board, i, j, 'O');//player swapped, like ^
					}
				}
			}
		}
		return newnode;
		
	}
}

void calculateScores(GameNode * tree)
{
	int numX =0;//used to track the number of X, O, and T's for each node
	int numO =0;
	int numT =0;
	
	if(tree==NULL)//if node doesnt exist, leave
	{
		return;
	}
	else if(isLeaf(tree))//if it's a leaf, and a winner, set the winner player
	{
		if(winner(tree->board, tree->player))
		{
			tree->score = tree->player;
			if(tree->player=='X')
			{
				numX++;
			}
			else
			{
				numO++;
			}
		}
		else//else, make it a tie T
		{
			tree->score = 'T';
			numT++;
		}
	}
	
		
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(tree->children[i][j]!=NULL)
			{
				calculateScores(tree->children[i][j]);//do this to all the children too
			}
		}
	}


	int counter =0;//tracks if there is an inconsistent player when comparing children score with node's player
	
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(tree->children[i][j]!=NULL)
			{
				if(tree->children[i][j]->score!=tree->player)
				{
					counter++;
				}
			}
		}
	}
	
	
	if(counter)//if inconsistent at least once, sets score to other player
	{
		if(tree->player = 'X')
		{
			tree->score = 'O';
		}
		else
		{
			tree->score = 'X';
		}
	}
	else if(!counter)
	{
		tree->score = tree->player;//otherwise, it's a tie
	}
	else
	{
		tree->score = 'T';
	}
	
}

GameNode * computerMove(GameNode * tree)//how the computer makes moves
{
	if(tree==NULL)
	{
		return NULL;
	}
	else
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if(tree->children[i][j]!=NULL)
				{
					if(tree->children[i][j]->score=='X')//prioritizes movement by looking at score: 1. Chooses computer score if it exists, 2. Tie score, 3. Player's score
					{
						return tree->children[i][j];
					}
					else if(tree->children[i][j]->score=='T')
					{
						return tree->children[i][j];
					}
					else
					{
						return tree->children[i][j];
					}
				}
			}
		}
	}
}

	