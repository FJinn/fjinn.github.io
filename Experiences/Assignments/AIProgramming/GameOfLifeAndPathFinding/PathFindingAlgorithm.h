#ifndef PATHFINDINGALGORITHM_H
#define PATHFINDINGALGORITHM_H

#include <list>

// to set restart condition
bool restartSearch = false;
// 3 is non diagonal and 4 is diagonal
// number use to change texture and control diagonal finding
int diagonalNum = 3;
// bool to reset everything, especially reset currentBox points to null
bool isReset = false;
// bool to start/pause path finding
bool findStart = false;
// weight for a*
int weight = 1;

const int boardRow = 35;
const int boardColumn = 90;

const int boardSize = boardRow * boardColumn;

enum BoxState
{
	START,
	TARGET,
	// return shortest path
	PATH,
	WALL,
	// done picking and not target/start
	DONE,
	// current picking box
	NOW,
	BLANK
};

class BoxStatus
{
public:
	BoxState state;
	BoxStatus* parent;
	// or G cost
	int myDistance;
	bool isPicked;
	int myRow;
	int myColumn;
	// or H cost
	int distanceToTarget;
	// fCost = distanceFromTarget(heuristic) + myDistance
	int fCost;
};

class AIStrategy
{
public:
	virtual void RestartFindPath(BoxStatus* box[boardSize]) = 0;
	virtual void ResetCurrentBox(BoxStatus* box[boardSize]) = 0;
	virtual void FindPath(BoxStatus* box[boardSize]) = 0;
};

class AStar : public AIStrategy
{
public:
	// run the algorithm based on one box instead of whole board
	BoxStatus* currentBox;

	// cache targetBox
	BoxStatus* targetBox;

	// int to check lowest fCost value
	int minF;

	// use it to check all the available boxes' distance
	// open list
	std::list<BoxStatus*> children;

	// restart find path algorithmn if target is found, without clearing all the walls
	void RestartFindPath(BoxStatus* box[boardSize])
	{
		ResetCurrentBox(box);

		for (int k = 0; k < boardSize; k++)
		{
			box[k]->fCost = INT_MAX;
			if (box[k]->state != WALL && box[k]->state != START && box[k]->state != TARGET)
			{
				box[k]->state = BLANK;
			}
		}
	}

	// function to point currentBox to null
	void ResetCurrentBox(BoxStatus* box[boardSize])
	{
		for (int k = 0; k < boardSize; k++)
		{
			box[k]->fCost = INT_MAX;
			if (box[k]->state != START)
			{
				box[k]->myDistance = INT_MAX;
				box[k]->distanceToTarget = INT_MAX;
				box[k]->parent = NULL;
			}
			box[k]->isPicked = false;

			if (box[k]->myDistance != 0)
			{
				box[k]->myDistance = INT_MAX;
			}

			// set currentBox points to null
			isReset = true;
		}

		children.clear();

		currentBox = NULL;
	}

	// function to set boxes' fCost
	void SetFCost(BoxStatus* box)
	{
		// calculate distance to target
		int tempDistance = abs(box->myColumn - targetBox->myColumn) + abs(box->myRow - targetBox->myRow);
		box->distanceToTarget = tempDistance;

		box->fCost = box->myDistance + (box->distanceToTarget * weight);
	}

	// function to set boxes' gCost
	void SetGCost(BoxStatus* box, bool isDiagonal)
	{
		if (!isDiagonal)
		{
			// g cost = parent's g cost + 10
			box->myDistance = box->parent->myDistance + 10;
		}
		else if (isDiagonal)
		{
			// g cost = parent's g cost + 14 for diagonal
			box->myDistance = box->parent->myDistance + 14;
		}
	}

	// function to check if the box is in the open(children) list
	bool IsChild(BoxStatus* box)
	{
		for (std::list<BoxStatus*>::iterator i = children.begin(); i != children.end(); i++)
		{
			if (box == *i)
			{
				return true;
			}
		}
		// not in the list
		return false;
	}

	// Function to update each neighbours to this current node
	void SetNeighbourBox(BoxStatus* box, bool isDiagonal)
	{
		// wall or done, ignore this
		if (box->state == WALL || box->state == DONE)
		{
			return;
		}

		// If it isn’t in the open list, add it to the open list.
		// true if in children list, false if not
		if (!IsChild(box))
		{
			children.push_back(box);
			// Make the current node the parent of this node. 
			box->parent = currentBox;
			// Calculate the F, G, and H costs of the node.
			SetGCost(box, isDiagonal);
			SetFCost(box);
		}
		else
		{
			// cache current g cost
			int tempGCost;
			if (!isDiagonal)
			{
				// g cost = parent's g cost + 10
				tempGCost = box->parent->myDistance + 10;
			}
			else if (isDiagonal)
			{
				// g cost = parent's g cost + 14 for diagonal
				tempGCost = box->parent->myDistance + 14;
			}
			
			// If it is in the open list already, check to see if this path to that node is better, using G cost as the measure.
			// A lower G cost means that it is a better path. 
			if (tempGCost < box->myDistance)
			{
				// If so, change the parent of the node to the current node, and update the G and F scores of the node. 
				box->parent = currentBox;
				SetGCost(box, isDiagonal);
				SetFCost(box);
			}
		}
	}

	void FindPath(BoxStatus* box[boardSize])
	{
		// start point, when there is no children
		if (currentBox == NULL)
		{
			for (int k = 0; k < boardSize; k++)
			{
				// set up target box
				if (box[k]->state == TARGET)
				{
					targetBox = box[k];
					targetBox->distanceToTarget = 0;
					targetBox->fCost = 0;
				}
			}

			for (int k = 0; k < boardSize; k++)
			{
				if (box[k]->state == START)
				{
					// find start box and set it to currentBox
					currentBox = box[k];
					SetFCost(currentBox);
					// add to children
					children.push_back(currentBox);
				}
			}
		}

		// find and set minimum F cost
		for (std::list<BoxStatus*>::iterator i = children.begin(); i != children.end(); i++)
		{
			if (i == children.begin()) 
			{
				minF = (*i)->fCost;
				// pick the children as current box
				currentBox = (*i);
			}
			else if ((*i)->fCost < minF)
			{
				minF = (*i)->fCost;
				// pick the children as current box
				currentBox = (*i);
			}
		}

		// change its isPicked to true
		currentBox->isPicked = true;
		if (currentBox->state == BLANK)
		{
			// set its state as DONE
			currentBox->state = DONE;
		}

		// to erase the current box from open list
		for (std::list<BoxStatus*>::iterator j = children.begin(); j != children.end(); j++)
		{
			if ((*j) == currentBox)
			{
				children.erase(j);
				break;
			}
		}

		// check if currentBox = target, end algorithm and change all parents (exclude START) state to PATH
		if (currentBox->state == TARGET)
		{
			// do...while (currentBox->state != START)
			do
			{
				// set current box as the parent
				currentBox = currentBox->parent;
				// set currentBox state to PATH, if it is not START
				if (currentBox->state != START)
				{
					currentBox->state = PATH;
				}
			} while (currentBox->state != START);
			// end algorithm
			// stop finding path
			findStart = false;
			restartSearch = true;
			return;
		}

		// check if children list has target
		for (std::list<BoxStatus*>::iterator i = children.begin(); i != children.end(); i++)
		{
			// check if target, end algorithm and change all parents (exclude START) state to PATH
			if ((*i)->state == TARGET)
			{
				currentBox = (*i);
				// do...while (currentBox->state != START)
				do
				{
					// set current box as the parent
					currentBox = currentBox->parent;
					// set currentBox state to PATH, if it is not START
					if (currentBox->state != START)
					{
						currentBox->state = PATH;
					}
				} while (currentBox->state != START);
				// end algorithm
				// stop finding path
				findStart = false;
				restartSearch = true;
				return;
			}

		}

		// if blank, check following
		// set the children/currentBox surrounding boxes
		int currentIndex = currentBox->myRow + currentBox->myColumn * boardRow;
		// check if the next box to set up is at the edge
		// check if the next box is a blank box
		if (currentBox->myRow + 1 < boardRow && currentIndex + 1 < boardSize && (box[currentIndex + 1]->state == BLANK || box[currentIndex + 1]->state == TARGET)
			)
		{
			// up
			SetNeighbourBox(box[currentIndex + 1], false);
		}

		if (currentBox->myColumn - 1 >= 0 && currentIndex - boardRow >= 0 && (box[currentIndex - boardRow]->state == BLANK || box[currentIndex - boardRow]->state == TARGET)
			)
		{
			// left
			SetNeighbourBox(box[currentIndex - boardRow], false);
		}

		if (currentBox->myRow - 1 >= 0 && currentIndex - 1 >= 0 && (box[currentIndex - 1]->state == BLANK || box[currentIndex - 1]->state == TARGET)
			)
		{
			// down
			SetNeighbourBox(box[currentIndex - 1], false);
		}

		if (currentBox->myColumn + 1 < boardColumn && currentIndex + boardRow < boardSize && (box[currentIndex + boardRow]->state == BLANK || box[currentIndex + boardRow]->state == TARGET)
			)
		{
			// right
			SetNeighbourBox(box[currentIndex + boardRow], false);
		}

		//================================================================================
		//================================================================================
		// diagonal
		// enable based on diagonalNum
		if (diagonalNum == 4)
		{
			if (currentBox->myRow + 1 < boardRow && currentBox->myColumn - 1 >= 0 && currentIndex - boardRow-1 >= 0 && (box[currentIndex - boardRow - 1]->state == BLANK || box[currentIndex - boardRow - 1]->state == TARGET)
				&& box[currentIndex - boardRow - 1]->myRow == currentBox->myRow - 1 && box[currentIndex - boardRow - 1]->myColumn == currentBox->myColumn - 1
				)
			{
				// down left
				SetNeighbourBox(box[currentIndex - boardRow - 1], true);
			}

			if (currentBox->myColumn - 1 >= 0 && currentBox->myRow - 1 >= 0 && currentIndex - boardRow + 1 >= 0 && (box[currentIndex - boardRow + 1]->state == BLANK || box[currentIndex - boardRow + 1]->state == TARGET)
				&& box[currentIndex - boardRow + 1]->myRow == currentBox->myRow + 1 && box[currentIndex - boardRow + 1]->myColumn == currentBox->myColumn - 1
				)
			{
				// up left
				SetNeighbourBox(box[currentIndex - boardRow + 1], true);
			}

			if (currentBox->myRow - 1 >= 0 && currentBox->myColumn + 1 < boardColumn && currentIndex + boardRow - 1 < boardSize && (box[currentIndex + boardRow - 1]->state == BLANK || box[currentIndex + boardRow - 1]->state == TARGET)
				&& box[currentIndex + boardRow - 1]->myRow == currentBox->myRow - 1 && box[currentIndex + boardRow - 1]->myColumn == currentBox->myColumn + 1
				)
			{
				// down right
				SetNeighbourBox(box[currentIndex + boardRow - 1], true);
			}

			if (currentBox->myColumn + 1 < boardColumn && currentBox->myRow + 1 < boardRow && currentIndex + boardRow+1 < boardSize && (box[currentIndex + boardRow + 1]->state == BLANK || box[currentIndex + boardRow + 1]->state == TARGET)
				&& box[currentIndex + boardRow + 1]->myRow == currentBox->myRow + 1 && box[currentIndex + boardRow + 1]->myColumn == currentBox->myColumn + 1
				)
			{
				// up right
				SetNeighbourBox(box[currentIndex + boardRow + 1], true);
			}
		}
	}
};

class Dijkstra : public AIStrategy
{
public:
	// to check and run box with current distance
	// manually initialize and deinitialize
	static int currentDistance;

	// run the algorithm based on one box instead of whole board
	BoxStatus* currentBox;

	// use it to check all the available boxes' distance
	std::list<BoxStatus*> children;

	// function to point currentBox to null
	void ResetCurrentBox(BoxStatus* box[boardSize])
	{
		currentBox = NULL;
		currentDistance = 0;
		children.clear();
	}

	// restart find path algorithmn if target is found, without clearing all the walls
	void RestartFindPath(BoxStatus* box[boardSize])
	{
		for (int k = 0; k < boardSize; k++)
		{
			box[k]->fCost = INT_MAX;
			if (box[k]->state != WALL && box[k]->state != START && box[k]->state != TARGET)
			{
				box[k]->state = BLANK;
			}

			if (box[k]->myDistance != 0)
			{
				box[k]->myDistance = INT_MAX;
			}

			box[k]->parent = NULL;

			box[k]->isPicked = false;
		}

		ResetCurrentBox(box);

	}


	void SetSurroundingBoxes(BoxStatus* box[boardSize])
	{
		int currentIndex = currentBox->myRow + currentBox->myColumn * boardRow;
		// increment = 10, diagonal increment is 4, so it will run diagonal first before continues
		// use own distance + 10, so diagonal will be + 14
		int nextdistance = currentBox->myDistance + 10;
		// diagonal boxes will have extra 4 distance
		int diagonalIncrement = 4;

		// check if the next box to set up is at the edge
		// check if the next box is a blank box
		// check if the next box distance is INT_MAX
		if (currentBox->myRow + 1 < boardRow && currentIndex + 1 < boardSize && (box[currentIndex + 1]->state == BLANK || box[currentIndex + 1]->state == TARGET) && box[currentIndex + 1]->myDistance == INT_MAX)
		{
			// up
			// set its distance to currentDistance + 1
			box[currentIndex + 1]->myDistance = nextdistance;
			// set its parent 
			box[currentIndex + 1]->parent = currentBox;
			// add to children
			children.push_back(box[currentIndex + 1]);
		}

		if (currentBox->myColumn - 1 >= 0 && currentIndex - boardRow >= 0 && (box[currentIndex - boardRow]->state == BLANK || box[currentIndex - boardRow]->state == TARGET) && box[currentIndex - boardRow]->myDistance == INT_MAX)
		{
			// left
			// set its distance to currentDistance + 1
			box[currentIndex - boardRow]->myDistance = nextdistance;
			// set its parent 
			box[currentIndex - boardRow]->parent = currentBox;
			// add to children
			children.push_back(box[currentIndex - boardRow]);
		}

		if (currentBox->myRow - 1 >= 0 && currentIndex - 1 >= 0 && (box[currentIndex - 1]->state == BLANK || box[currentIndex - 1]->state == TARGET) && box[currentIndex - 1]->myDistance == INT_MAX)
		{
			// down
			// set its distance to currentDistance + 1
			box[currentIndex - 1]->myDistance = nextdistance;
			// set its parent 
			box[currentIndex - 1]->parent = currentBox;
			// add to children
			children.push_back(box[currentIndex - 1]);
		}

		if (currentBox->myColumn + 1 < boardColumn && currentIndex + boardRow < boardSize && (box[currentIndex + boardRow]->state == BLANK || box[currentIndex + boardRow]->state == TARGET) && box[currentIndex + boardRow]->myDistance == INT_MAX)
		{
			// right
			// set its distance to currentDistance + 1
			box[currentIndex + boardRow]->myDistance = nextdistance;
			// set its parent 
			box[currentIndex + boardRow]->parent = currentBox;
			// add to children
			children.push_back(box[currentIndex + boardRow]);
		}

		//================================================================================
		//================================================================================
		// diagonal
		// enable based on diagonalNum
		if (diagonalNum == 4)
		{
			if (currentBox->myRow + 1 < boardRow && currentBox->myColumn - 1 >= 0 && currentIndex - boardRow - 1 >= 0 && (box[currentIndex - boardRow - 1]->state == BLANK || box[currentIndex - boardRow - 1]->state == TARGET) && box[currentIndex - boardRow - 1]->myDistance == INT_MAX
				&& box[currentIndex - boardRow-1]->myRow == currentBox->myRow - 1 && box[currentIndex - boardRow - 1]->myColumn == currentBox->myColumn - 1)
			{
				// up left
				// set its distance to currentDistance + 4
				box[currentIndex - boardRow - 1]->myDistance = nextdistance + diagonalIncrement;
				// set its parent 
				box[currentIndex - boardRow - 1]->parent = currentBox;
				// add to children
				children.push_back(box[currentIndex - boardRow - 1]);
			}

			if (currentBox->myColumn - 1 >= 0 && currentBox->myRow - 1 >= 0 && currentIndex - boardRow + 1 >= 0 && (box[currentIndex - boardRow + 1]->state == BLANK || box[currentIndex - boardRow + 1]->state == TARGET) && box[currentIndex - boardRow + 1]->myDistance == INT_MAX
				&& box[currentIndex - boardRow+1]->myRow == currentBox->myRow + 1 && box[currentIndex - boardRow + 1]->myColumn == currentBox->myColumn - 1)
			{
				// down left
				// set its distance to currentDistance + 4
				box[currentIndex - boardRow + 1]->myDistance = nextdistance + diagonalIncrement;
				// set its parent 
				box[currentIndex - boardRow + 1]->parent = currentBox;
				// add to children
				children.push_back(box[currentIndex - boardRow + 1]);
			}

			if (currentBox->myRow - 1 >= 0 && currentBox->myColumn + 1 < boardColumn && currentIndex + boardRow - 1 < boardSize && (box[currentIndex + boardRow - 1]->state == BLANK || box[currentIndex + boardRow - 1]->state == TARGET) && box[currentIndex + boardRow - 1]->myDistance == INT_MAX
				&& box[currentIndex + boardRow-1]->myRow == currentBox->myRow - 1 && box[currentIndex + boardRow - 1]->myColumn == currentBox->myColumn + 1)
			{
				// down right
				// set its distance to currentDistance + 4
				box[currentIndex + boardRow - 1]->myDistance = nextdistance + diagonalIncrement;
				// set its parent 
				box[currentIndex + boardRow - 1]->parent = currentBox;
				// add to children
				children.push_back(box[currentIndex + boardRow - 1]);
			}

			if (currentBox->myColumn + 1 < boardColumn && currentBox->myRow + 1 < boardRow && currentIndex + boardRow + 1 < boardSize && (box[currentIndex + boardRow + 1]->state == BLANK || box[currentIndex + boardRow + 1]->state == TARGET) && box[currentIndex + boardRow + 1]->myDistance == INT_MAX
				&& box[currentIndex + boardRow + 1]->myRow == currentBox->myRow + 1 && box[currentIndex + boardRow + 1]->myColumn == currentBox->myColumn + 1)
			{
				// up right
				// set its distance to currentDistance + 4
				box[currentIndex + boardRow + 1]->myDistance = nextdistance + diagonalIncrement;
				// set its parent 
				box[currentIndex + boardRow + 1]->parent = currentBox;
				// add to children
				children.push_back(box[currentIndex + boardRow + 1]);
			}
		}
	}

	void FindPath(BoxStatus* box[boardSize])
	{
		// start point, when there is no children
		if (currentBox == NULL)
		{
			for (int k = 0; k < boardSize; k++)
			{
				if (box[k]->state == START)
				{
					// find start box and set it to currentBox
					currentBox = box[k];
					// set its surrounding boxes
					SetSurroundingBoxes(box);
					// set current distance to 1 manually
					// because of diagonal it start with 10 for up down left right
					// then diagonal will be 10 + 4, + 10 of up down left right
					// increment = 10
					currentDistance = 10;
					// done with this loop
					break;
				}
			}
		}

		// run diagonal first
		// search the children and run those distance matches with current distance
		if (diagonalNum == 4)
		{
			for (std::list<BoxStatus*>::iterator i = children.begin(); i != children.end(); i++)
			{
				if ((*i)->myDistance < currentDistance && (*i)->isPicked == false)
				{
					// pick the children as current box
					currentBox = (*i);

					// change its isPicked to true
					currentBox->isPicked = true;

					// check if it is target or blank, if target, end algorithm and change all parents (exclude START) state to PATH
					if (currentBox->state == TARGET)
					{
						// do...while (currentBox->state != START)
						do
						{
							// set current box as the parent
							currentBox = currentBox->parent;
							// set currentBox state to PATH, if it is not START
							if (currentBox->state != START)
							{
								currentBox->state = PATH;
							}
						} while (currentBox->state != START);
						// end algorithm
						// stop finding path
						findStart = false;
						restartSearch = true;
						return;
					}
					// if blank
					else if (currentBox->state == BLANK)
					{
						// set the children/currentBox surrounding boxes
						SetSurroundingBoxes(box);
						// set its state as DONE
						currentBox->state = DONE;
					}
				}
			}
		}

		// run normal current distance after diagonal
		for (std::list<BoxStatus*>::iterator j = children.begin(); j != children.end(); j++)
		{
			if ((*j)->myDistance == currentDistance && (*j)->isPicked == false)
			{
				// pick the children as current box
				currentBox = (*j);

				// change its isPicked to true
				currentBox->isPicked = true;

				// check if it is target or blank, if target, end algorithm and change all parents (exclude START) state to PATH
				if (currentBox->state == TARGET)
				{
					// do...while (currentBox->state != START)
					do
					{
						// set current box as the parent
						currentBox = currentBox->parent;
						// set currentBox state to PATH, if it is not START
						if (currentBox->state != START)
						{
							currentBox->state = PATH;
						}
					} while (currentBox->state != START);
					// end algorithm
					// stop finding path
					findStart = false;
					restartSearch = true;
					return;
				}
				// if blank
				else if (currentBox->state == BLANK)
				{
					// set the children/currentBox surrounding boxes
					SetSurroundingBoxes(box);
					// set its state as DONE
					currentBox->state = DONE;
				}
			}
		}

		// erase those that is already picked and push into children list
		for (std::list<BoxStatus*>::iterator l = children.begin(); l != children.end(); l++)
		{
			if ((*l)->myDistance < currentDistance && (*l)->isPicked == true)
			{
				// erase l from children
				l = children.erase(l);
			}
		}
		
		// after done with all children (matches with current distance)
		// increase current distance by one 
		// increment = 10
		currentDistance += 10;
	} 
};

#endif 
