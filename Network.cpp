#include <iostream>

#include <fstream>
#include <chrono>
#include <random>
#include <cmath>

#include "Network.h"

/*
 * Constructor
 *
 * Parameters :
 *              nlayers : Number of layers
 *              npl     : array of size nlayers with number 
 *                                   of neurons per layers
 */
Network::Network(int nlayers, int *npl){

  std::cout << "Object Network : " << this << " created. Merci."<< std::endl;
  
  int tmp=0;

  n_layers = nlayers;

  neurons_per_layers = new int[nlayers];
  for(int i=0; i<nlayers; i++){
    neurons_per_layers[i] = npl[i];
    tmp += npl[i];
  }

  n_neurons = tmp;

  neurons_weights = new double[n_neurons];
  neurons_bias = new double[n_neurons];
  neurons_values = new double[n_neurons];

}

/*
 * Destructor
 *
 */
Network::~Network(){

  delete [] neurons_per_layers;
  delete [] neurons_weights;
  delete [] neurons_bias;
  delete [] neurons_values;

  std::cout << "Object Network : " << this << " destroyed. Merci." << std::endl;
}

/*
 * Set random values to initiliaze weights and bias of 
 * sigmoid neurons
 *
 */
void Network::setWeightsAndBias(){

  std::mt19937_64 rng;

  // initialize the random number generator with time-dependent seed
  uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
  rng.seed(ss);

  // initialize a uniform distribution between 0 and 1
  std::uniform_real_distribution<double> unif(0, 1);

  /* ready to generate random weights and bias */

  // no bias for first layer
  for(int i=0; i<neurons_per_layers[0]; i++){
    neurons_bias[i] = 0.0;
  }

  // no weights for last layer
  for(int i=n_neurons-1; i>n_neurons-neurons_per_layers[n_layers-1]; i--){
    neurons_weights[i] = 0.0;
  }

  // set random bias for all other neurons
  for (int i = neurons_per_layers[0]; i < n_neurons; i++){
    neurons_bias[i] = unif(rng);
  }

  // set random weight for all other neurons
  for (int i = 0; i < n_neurons-neurons_per_layers[n_layers-1]; i++){
    neurons_weights[i] = unif(rng);
  }

  std::cout << "> Weights and bias randomly set for sigmoid network. Merci."<< std::endl;

}

/*
 * Set or reset neurons values to zeros
 *
 */
void Network::resetNeuronsValues(){

  for(int i=0; i<n_neurons; i++){
    neurons_values[i] = 0.0;
  }

}

/*
 * Update the values of neurons in the network. First layer stay unchanger 
 * as long as it is the data input values for network.
 *
 */
void Network::analyze(){

  int i, j, tmp;

  double *w_dot_x = new double[n_layers];
  for(i=0; i<n_layers; i++){
    w_dot_x[i] = 0.0;
  }

  /* new values for neurons that we have to compute are values
   * of all layers except the first one since it's input
   */
  tmp = 0;
  for(i=0; i<n_layers-1; i++){
   
    /* weights dot x for the current layer */ 
    for(j=tmp; j<tmp+neurons_per_layers[i]; j++){
      w_dot_x[i] += neurons_weights[j] * neurons_values[j];
    }

    /* compute neurons values for next layer */
    tmp += neurons_per_layers[i];
    for(j=tmp; j<tmp+neurons_per_layers[i+1]; j++){
      neurons_values[j] = 1.0/(1.0+exp(-w_dot_x[i] - neurons_bias[j]));
    }

  }

  for(i=0; i<n_layers; i++){
    std::cout << " Layer " << i+1 << " -> ";
    std::cout << " w.x = " << w_dot_x[i] << std::endl;
  }
  
  delete [] w_dot_x;

}

/*
 * Function for training the network using MNIST data sets.
 *
 */
void Network::goForTraining(){

  /* Open data file */
  std::ifstream infile;
  infile.open("data_training/data0", std::ios::binary|std::ios::in);

  if( !infile.is_open() ){
    std::cout << "\x1b[31mError ! Cannot open file for training.\x1b[0m\n";
    return;
  }else{
    std::cout << "\x1b[31mGo for training baby.\x1b[0m\n";
  }

  /* see how well the network fit the real result */
  /* BRUTAL FOR THE MOMENT - first set of data are representing '0' */
  double *true_rst = new double[10];
  true_rst[0] = 1.0;
  for(int i=1; i<10; i++){ true_rst[i] = 0.0; }

  int last_neurons= n_neurons - neurons_per_layers[n_layers-1];

  double fcost = 0.0;

  /* get data and put them inside the neural network */  
  unsigned char pix;
  int imgpixel = 0;
  for(int nimg=0; nimg < 1000; nimg++){
    for(int i=0; i<784; i++){
      infile.read((char *) &pix, sizeof(char));
      //std::cout << "Pix read : " << (unsigned) pix << std::endl;

      neurons_values[i] = (unsigned) pix;
      neurons_values[i] /= 255; // normalisaaaafion
    }
    
    /* compute result from network */
    analyze();
    
    /* compute \|y(x) - a\|^2 = (y(x)-a) dot (y(x)-a) */
    double msq = 0.0;
    for(int i=0; i<10; i++){
      msq += (true_rst[i]-neurons_values[last_neurons])*(true_rst[i]-neurons_values[last_neurons]);
    }
    
    /* To compute the C(w,b) = 1/2n \sum \|y(x) - a\|^2 */
    fcost += msq;
    
    /* next img : first pixel start at every 784 px */
    //imgpixel += 784;

    std::cout << "Cost function img : " << nimg+1; 
    std::cout << " > " << msq << " |  > " << fcost << "\n";
  }
  

  fcost /= (2000); // because one set of data contains 1000 imgs (1/2n)

  /* close file */ 
  infile.close();

  delete [] true_rst;

}

/*
 * Display all weights of the neural network
 *
 */
void Network::showWeights(){

  int tmp = 0;

  for(int i=0; i<n_layers; i++){
    std::cout << " Layer : " << i << "\n" << std::endl;
    for(int j=tmp; j<tmp+neurons_per_layers[i]; j++){
      std::cout << "Weight neurons " << j+1 << " : " << neurons_weights[j];
      std::cout << " | Bias neurons " << neurons_bias[j] << std::endl;
    }
    tmp = neurons_per_layers[i] + tmp;
  }

}

/*
 * Display neurons values
 *
 */
void Network::showNeuronsValues(){
  int tmp = 0;

  for(int i=0; i<n_layers; i++){
    std::cout << ">\x1b[31mLayer : " << i << "\x1b[0m" << std::endl;
    for(int j=tmp; j<tmp+neurons_per_layers[i]; j++){
      std::cout << "Neurons " << j+1 ;
      std::cout << ", values -> " << neurons_values[j] << std::endl;
    }
    tmp = neurons_per_layers[i] + tmp;
    std::cout << std::endl;
  }
  
}
