# The third week

## The cost function of logistic function

 We can not use the cost function of linear regression!Because that cost function is not suitable for logistic function,the graph is an non-convex function and we cannot find the global optimism.



## How to deal with multiclass classification problem?

### Use the method called "One-vs-all"

​	This method means pick one of the classes from all, and construct a binary classifier to classify this class against the rest.Then pick another classifier to construct another classifier until each class has one classifier!(That mean you have to construct n classifiers to complete this multiclass classification problem,n is the number of classes you want to classify) 