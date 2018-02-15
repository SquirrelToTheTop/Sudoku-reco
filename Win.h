#ifndef DEF_WIN
#define DEF_WIN

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>

class Win : public QWidget{

  Q_OBJECT
  
 public:
  Win();
  ~Win();

 private slots:
    void solve_sudoku();
    void reset_sudoku();

 private:
    QTextEdit ***qt_grid;

    QPushButton *btn_load;
    QPushButton *btn_solve;

    int width_cell, height_cell;
    int width_win, height_win;
    int **g;

    void clean_mem();
    void update_qtgrid(int **);
};

#endif
