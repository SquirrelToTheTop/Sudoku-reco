#include <iostream>

#include "Solver.h"

/*
 * Constructor
 *
 */
Solver::Solver(int **the_grid){

  std::cout << "Object Solver : " << this << " created. Merci."<< std::endl;  

  /* Oioioh solvant solveur solve moi */
  backtracking(the_grid, 0, 0);

}

/*
 * Destructor
 *
 */
Solver::~Solver(){

  std::cout << "Object Solver : " << this << " destroyed. Merci." << std::endl;
 
}

/*
 * Solving sudoku using backtracking
 *
 */
bool Solver::backtracking(int **grid, int row, int col){

  int i;

  if( row == N ){
    //update_qtgrid(grid);
    return true;
  }

  if( grid[row][col] == 0 ){
    for(i=1; i<=N; i++){
      if( test_num(grid, i, row, col) ){
        grid[row][col] = i;
        //update_qtgrid(grid);
        if( col == N-1 ){
          if( backtracking(grid, row+1, 0) ) return true;
        }
        else{
          if( backtracking(grid, row, col+1) ) return true;
        }
      }
      grid[row][col] = 0;
    }
  }else{
    if( col == N-1 ){
      if( backtracking(grid, row+1, 0) ) return true;
    }
    else{
      if( backtracking(grid, row, col+1) ) return true;
    }
  }

  return false;
}

/*
 * Test a number in a specific cell
 */
bool Solver::test_num(int **grid, int num, int row, int col){

  int i, j, idi, idj;

  if( grid[row][col] != 0 ){
    return false;
  }else{

    for(i=0; i<N; i++){
      if( grid[row][i] == num || grid[i][col] == num ){
        return false;
      }
    }

    idi = (row/3) * 3;
    idj = (col/3) * 3;
    for(i=idi; i<idi+3; i++){
      for(j=idj; j<idj+3; j++){
        if( grid[i][j] == num ){
          return false;
        }
      }
    }
  }

  return true;
}
