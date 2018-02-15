#ifndef DEF_NETWORK
#define DEF_NETWORK

class Network{

 public:
  Network(int, int *);  
  ~Network();

  /* Set or reset random value to weights & bias */
  void setWeightsAndBias();

  /* set or reset neurons values to zero */
  void resetNeuronsValues();

  /* update values of network, ie : analyze input data to get result from network */
  void analyze();

  /* Training the network */
  void goForTraining();

  /* Display weights */
  void showWeights();

  /* Display neurons values */
  void showNeuronsValues();

 private:
  
  /*
   * n_layers = number of layers, the model is composed of 3 layers
   * n_neurons = total number of neurons
   */
  int n_layers, n_neurons;
  
  /* array of size n_layers :
   *   neurons_per_layers[0] -> number of neurons in input layers (n_neurons = n_pixels)
   *   neurons_per_layers[1] -> number of neurons of first hidden layer
   *   neurons_per_layers[n_layers-1] -> number of neurons in final layer (10 neurons)
   */
  int *neurons_per_layers;
  
  /* Characteristics of neurons : weights and biais
   * -> remember that first layer (input layers) neurons have no biais (biais set to 0)
   * -> remember that last layer, neurons have no weight (weights set to 0)
   */
  double *neurons_weights, *neurons_bias;

  /*
   * Array containing the value of the neuron (input/output)
   *
   */
  double *neurons_values;

};

#endif
