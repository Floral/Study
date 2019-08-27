[TOC]

# Week 1

## classification of machine learning

- supervised learning
  - regression problem
  - classification problem
- unsupervised learning



## regression problem

### linear regression

#### Algorithm——Gradient Descent

- set a proper learning rate is important.
- negative feedback

the final optimal point maybe a local optimum as the start point varies. But in this linear problem(linear regression with one variable), the cost function is a convex quadratic function, so it have one global optimum only.



# Week 2

## Gradient Descent with multiple features

### Feature Scaling

The reason that why we want to use feature scaling is that:

If features are on a **similar**(or roughly the same) scale, the gradient descent can converge more quickly. Or you can say, the more small the ranges of features are, the more quickly the gradient will descent to the optimum.

There are two common method to implement the ideal status we look forward:

- **feature scaling**, this involves dividing the input values by the range(i.e. the maximum value minus the minimum value), and resulting in a new range of just 1.
- **mean normalization**, this involves input values minus the average for an input variable from the values input, and resulting in a new range which average is 0.

And we often take these two method together to get better efficiency：

$x_i=\frac{x_i-\mu_i}{s_i}$

where  $\mu_i$ is the average of all values for feature (i) and $s_i$ is the range of values (max-min), or standard deviation.



### Learning rate

It has to be proven that if the learning rate is sufficiently small, then the J($\theta$) will decrease on every iteration and converge. But it will be very slow surely.



### Polynomial regression

If the linear hypothesis function doesn't fit the data very well, we can **change the behavior or the form of function**(such as quadratic, cubic or square root). Then we need to change our cost function J($\theta $) too!

And don't forget to do feature scaling, cause the range of each feature can be very different after change.



### Normal Equation

Normal equation is another method to get solution for linear regression analytically.

With the knowledge of calculus, we explicitly take the derivatives with respect to the $\theta_j's$, then setting them to zero. After a series of mathematical transformation and calculation, we will get this equation as called **Normal Equation** above:

$\theta=(X^TX)^{-1}y$



> That let me recall the linear regression in probability, and there is a method which I think may come from the same mathematical method and get the same conclusion called **Least squares method**!





# Week 3

## Classification and Representation

### Binary classification problem

The dependent variable y can only take on two values, 0 and 1.

If we use the linear regression method which we have discussed above, the result may not fit very well(at a large probability).

Then we find a new function which called Logistic Function(or Sigmoid Function) to solve this problem by plugging $\theta^Tx$ into this function:

$h_\theta(x)=g(\theta^Tx)$

$z=\theta^Tx$

$h_\theta(z)=\frac{1}{1+e^{-z}}$

And the image of this function looks like this:

![img](https://d3c33hcgiwev3.cloudfront.net/imageAssetProxy.v1/1WFqZHntEead-BJkoDOYOw_2413fbec8ff9fa1f19aaf78265b8a33b_Logistic_function.png?expiry=1566432000000&hmac=U_NqmRQtdUeRXMiSEdvrpe4TT8t0iZBdTaibqbJR0wA)

Note that the result of this function is giving us a probability that it is 1.



### Decision Boundary

The **decision boundary** is the line that separates the area where y = 0 and where y = 1. It is created by our hypothesis function.

Commonly, we choose the linear x=0 to be the decision boundary of Logistic Function. If z is greater than or equals to zero, we choose the corresponding y to be 1.

Note that the input to the Sigmoid function g(z) (e.g. $\theta^Tx$ ) doesn't need to be linear, and could be other non-linear function forms, and maybe it works better!



## Logistic Regression Model

### Cost function

We cannot use the same cost function that we use for linear regression because the Logistic Function will cause the output to be wavy, causing many local optima. In other words, it will not be a convex function.

Instead, our cost function for logistic regression looks like:







## How to deal with multiclass classification problem?

### Use the method called "One-vs-all"

​	This method means pick one of the classes from all, and construct a binary classifier to classify this class against the rest.Then pick another classifier to construct another classifier until each class has one classifier!(That mean you have to construct n classifiers to complete this multiclass classification problem,n is the number of classes you want to classify) 



## Overfitting

If we make the fitting function to be high order polynomial such as $5^{th}$ order polynomial $\sum_{j=0}^{5}\theta_jx^j$ , then we mostly get the result figure that fit the data in training set very well, and the cost may approximates zero. But if we give it some samples which is not in the training set, the figure will probably give us a unpleasing result.

That is what we call "overfitting", and of course there are underfitting in contrary which denotes the fitting to training set is not well as we expect, or you can say "bad".

The common reason for overfitting is :

- too many features and so the degree of the equation is too high.



### How to reduce the probability to be overfitting?

There are two methods:

1. reduce the number of features

   - Manually select which features to keep.

   - Use a model selection algorithm (studied later in the course).

2. Regularization

   - Keep all the features, but reduce the magnitude of parameters $\theta_j$.
   - Regularization works well when we have a lot of slightly useful features.





# Week 4

## Neural Networks

### Model Representation







# Week 5

## Cost Function and Back Propagation




