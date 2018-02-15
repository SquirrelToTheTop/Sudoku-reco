#include <iostream>
#include <QApplication>

/* personnal headers */
#include "Win.h"
#include "Network.h"

int main(int argc, char *argv[]){

  if( argc < 2 ){
    std::cout << "\nI need arguments, thanks. " <<  argv[0] << ".exe\n" << std::endl;

    return 1;

  }else{

    std::string tmp_argv = argv[1];

    if( tmp_argv == "sudoku" ){
      QApplication app(argc, argv);
    
      Win win_grid;
  
      win_grid.show();

      return app.exec();

    }else if( tmp_argv == "training" ){      
      std::cout << "\nWorking on that " <<  argv[0] << ".exe\n" << std::endl;

      int *test = new int[3];
      test[0] = 784;
      test[1] = 15;
      test[2] = 10;

      Network philibert(3, test);
      philibert.setWeightsAndBias();
      philibert.goForTraining();
      //philibert.showWeights();

      return 0;

    }else{
      std::cout << "\nI don't understood your arguments. " <<  argv[0] << ".exe\n" << std::endl;

      return 1;
    }

  }
   
}
