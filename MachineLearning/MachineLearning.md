# The first week

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



# The second week

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





# The third week

## The cost function of logistic function

 We can not use the cost function of linear regression!Because that cost function is not suitable for logistic function,the graph is an non-convex function and we cannot find the global optimism.



## How to deal with multiclass classification problem?

### Use the method called "One-vs-all"

​	This method means pick one of the classes from all, and construct a binary classifier to classify this class against the rest.Then pick another classifier to construct another classifier until each class has one classifier!(That mean you have to construct n classifiers to complete this multiclass classification problem,n is the number of classes you want to classify) 