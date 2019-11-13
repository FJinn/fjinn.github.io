#include "SpatialPartition.h"

Grid::Grid()
{
	// Clear the grid.
	for (int x = 0; x < NUM_CELLS; x++)
	{
		for (int y = 0; y < NUM_CELLS; y++)
		{
			cells_[x][y] = NULL;
		}
	}
}

void Grid::Add(GameObject * obj)
{ 
	// Determine which grid cell it's in.
	int cellX = (int)(obj->m_position.mVal[0] / CELL_SIZE_X);
	int cellY = (int)(obj->m_position.mVal[1] / CELL_SIZE_Y);

	if (cellX >= 10 || cellY >= 10 || cellX < 0 || cellY < 0)
	{
		std::cout << "EXCEED cell size : " << OBJECT_TAG << std::endl;

		return;
	}

	// Add to the front of list for the cell it's in.
	obj->m_prev = NULL;
	obj->m_next = cells_[cellX][cellY];
	cells_[cellX][cellY] = obj;

	if (obj->m_next != NULL)
	{
		obj->m_next->m_prev = obj;
	}
}

void Grid::HandleCollision()
{
	for (int x = 0; x < NUM_CELLS; x++)
	{
		for (int y = 0; y < NUM_CELLS; y++)
		{
			HandleCell(x, y);
		}
	}
}

void Grid::HandleCell(int x, int y)
{
	GameObject* obj = cells_[x][y];
	while (obj != NULL)
	{
		// Handle other units in this cell.
		HandleObject(obj, obj->m_next);
		
		// Also try the neighboring cells.
		if (x > 0 && y > 0) HandleObject(obj, cells_[x - 1][y - 1]);
		if (x > 0) HandleObject(obj, cells_[x - 1][y]);
		if (y > 0) HandleObject(obj, cells_[x][y - 1]);
		if (x > 0 && y < NUM_CELLS - 1)
		{
			HandleObject(obj, cells_[x - 1][y + 1]);
		}

		obj = obj->m_next;
	}
}

void Grid::HandleDeath(GameObject * obj)
{	
	// See which cell it was in.
	int oldCellX = (int)(obj->prev_position.mVal[0] / Grid::CELL_SIZE_X);
	int oldCellY = (int)(obj->prev_position.mVal[1] / Grid::CELL_SIZE_Y);

	// Unlink it from the list of its old cell.
	if (obj->m_prev != NULL)
	{
		obj->m_prev->m_next = obj->m_next;
	}

	if (obj->m_next != NULL)
	{
		obj->m_next->m_prev = obj->m_prev;
	}

	// If it's the head of a list, remove it.
	if (cells_[oldCellX][oldCellY] == obj)
	{
		cells_[oldCellX][oldCellY] = obj->m_next;
	}
	
}

void Grid::Move(GameObject* obj, Vector pos)
{
	// See which cell it was in.
	int oldCellX = (int)(obj->prev_position.mVal[0] / Grid::CELL_SIZE_X);
	int oldCellY = (int)(obj->prev_position.mVal[1] / Grid::CELL_SIZE_Y);

	// See which cell it's moving to.
	int cellX = (int)(pos.mVal[0] / Grid::CELL_SIZE_X);
	int cellY = (int)(pos.mVal[1] / Grid::CELL_SIZE_Y);

	obj->prev_position = pos;

	// If it didn't change cells, we're done.
	if (oldCellX == cellX && oldCellY == cellY) return;

	// Unlink it from the list of its old cell.
	if (obj->m_prev != NULL)
	{
		obj->m_prev->m_next = obj->m_next;
	}

	if (obj->m_next != NULL)
	{
		obj->m_next->m_prev = obj->m_prev;
	}

	// If it's the head of a list, remove it.
	if (cells_[oldCellX][oldCellY] == obj)
	{
		cells_[oldCellX][oldCellY] = obj->m_next;
	}

	// Add it back to the grid at its new cell.
	Add(obj);
}

void Grid::HandleObject(GameObject * obj, GameObject * other)
{
	while (other != NULL)
	{
	
		if (GJK_Updated(obj->GetCollider(), other->GetCollider()))
		{
			// do collision stuff
		}
					

		other = other->m_next;
	}
}
