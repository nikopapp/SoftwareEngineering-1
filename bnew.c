

int bgame (void)
{
  /* this is the grid */
  cell grid[H][W];

  initGrid(grid);

  /* foreground layer test */
  player = grid[6][6].foreground = newEntity(passable,'@',6,6);

  /* lightbulbs and switches */
  newBulb(grid, 2, 1);
  newBulb(grid, 3, 1);
  newBulb(grid, 4, 1);
  newBulb(grid, 5, 1);
  newBulb(grid, 6, 1);
  newBulb(grid, 7, 1);
  newBulb(grid, 8, 1);
  newBulb(grid, 9, 1);

  fillGrid(grid);
  
  
}