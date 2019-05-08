# Learning TensorFlow



## basic knowledge

### tensor



### graph

Graph does not compute the Intermediate results or final results,it only define how to compute them.

The code that we write to define how to get the prediction we want is defining graph.

### session

If we want to know the results of our NN(Neural Network),we need a session to compute them.

Any parameters in NN also needs `session.run()` to  compute.

## basic grammar

### tf.Variable

### tf.placeholder



## How to implement an NN?

1. prepare data set

2. construct NN's structure,from inputs to outputs(Forward Propagation)

3. iterate(Back Propagation)

4. apply



### Forward Propagation

to define the graph of  prediction

### Back Propagation

to define how to train your NN. eg: Gradient Descent.

### Activation Function

Using an activation function can construct an non-linear model to solve the problem better.

The most common activation function are:

1. relu(`tf.nn.relu()`)
2. sigmoid(`tf.nn.sigmoid()`)
3. tanh(`tf.nn.tanh()`)中间结果



### LOSS

The difference between the predicted value and the known answer.

Common loss for example:

`tf.reduce_mean(tf.square(y_-y))`

### Cross Entropy

The distance between two probability distributions.

#### softmax()

to make outputs meet the condition of probability distributions.



### Learning Rate

w~n+1~=w~n~-learning_rate*d(loss)



set a suitable learning rate is very important!

We can also use 

### Moving Average

also is called shadow value

### Regularization

regularization is to solve the overfitting problem.





## CNN(Convolutional neural network)

CNN is used to extract features to reduce the number of intermediate parameters.



### Some Main Module

#### 1.Convolutional

#### 2.Activation

#### 3.Pooling

#### 4.Fully connection

1 to 3 modules are used to extract features