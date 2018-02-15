#include <iostream>

#include "Win.h"
#include "Solver.h"

#define N 9

Win::Win() : QWidget(){

  int i, j;
  int off_border_x, off_border_y, inter = 20;
  int width_btn, height_btn;

  off_border_x = 15;
  off_border_y = 15;    

  width_cell = 30;
  height_cell = 30;

  width_btn = 100;
  height_btn = 30;

  width_win = N*width_cell+off_border_x*2+10;
  height_win = N*height_cell+off_border_x*2+110;

  setFixedSize(width_win, height_win);

  /* Define grid of QTextEdit */
  qt_grid = new QTextEdit**[N];
  g = new int*[N];
  for(i=0; i<N; i++){
    qt_grid[i] = new QTextEdit*[N];
    g[i] = new int[N];
  }
  
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){          

      qt_grid[i][j] = new QTextEdit("0", this);
      qt_grid[i][j]->setFixedWidth(width_cell);
      qt_grid[i][j]->setFixedHeight(height_cell);
      qt_grid[i][j]->move(off_border_x+j*(width_cell), off_border_y+i*(height_cell));
      
      if( (j+1)%3 == 0){
	off_border_x += 5;
      }

    }
    
    off_border_x = 15;

    if( (i+1)%3 == 0){
      off_border_y += 5;
    }

  }
  
  btn_load = new QPushButton("Reset ?", this);
  btn_solve = new QPushButton("Solve ?", this);

  btn_load->setFixedWidth(width_btn);
  btn_load->setFixedHeight(height_btn);
  
  btn_solve->setFixedWidth(width_btn);
  btn_solve->setFixedHeight(height_btn);

  btn_load->move(off_border_x,N*height_cell+off_border_x*2+inter);
  btn_solve->move(width_win-off_border_y-width_btn,N*height_cell+off_border_x*2+inter);

  connect(btn_load, SIGNAL(clicked()), this, SLOT(reset_sudoku()));
  connect(btn_solve, SIGNAL(clicked()), this, SLOT(solve_sudoku()));
  
}

/*
 * Destructor
 *
 */
Win::~Win(){
  clean_mem();
}

void Win::reset_sudoku(){
  int i,j;

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      qt_grid[i][j]->setReadOnly(false);
      g[i][j]=0;
    }
  }

  update_qtgrid(g);
}

void Win::solve_sudoku(){
  int i, j;
  bool ok;
  QString tmp_cell;

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      qt_grid[i][j]->setReadOnly(true);
      g[i][j] = (qt_grid[i][j]->toPlainText()).toInt(&ok,10);      
    }
  }

  Solver solvons_le(g);

  update_qtgrid(g);
  
}

void Win::update_qtgrid(int **grid){
  int i, j;
  QString tmp;

  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      tmp = QString::number(grid[i][j]);
      qt_grid[i][j]->setText(tmp);
    }
  }
  qApp->processEvents();
}

void Win::clean_mem(){
  int i;

  for(i=0; i<N; i++)
    delete [] qt_grid[i];
  delete [] qt_grid;
}




