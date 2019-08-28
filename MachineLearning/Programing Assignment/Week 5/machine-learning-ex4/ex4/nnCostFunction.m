function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

% Setup some useful variables
m = size(X, 1);
         
% You need to return the following variables correctly 
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a 
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the 
%               first time.
%
% Part 3: Implement regularization with the cost function and gradients.
%(m, input_layer_size - 1
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%


% part 1:
% cost function without regularization
a1=[ones(m,1) X];    % add a(1)0
z2=Theta1*a1';  % 25x5000
a2=sigmoid(z2);    a2=[ones(1,m);a2];    % add a(2)0 26x5000
z3=Theta2*a2;
a3=sigmoid(z3);  % 10x5000
h_theta=a3;
[~,p] = max(a3,[],1);
% h_theta = zeros(size(a3));
% for i=1:size(a3,2)
%     h_theta(p(i),i)=1;
% end
t=zeros(m,num_labels);  %5000x10
for i=1:m
   t(i,y(i))=1; 
end

J_of_each = zeros(1,m);
for i=1:m
    J_of_each(1,i) = (-t(i,:)*log(h_theta(:,i))-(1-t(i,:))*log(1-h_theta(:,i)));
end
J = sum(J_of_each)/m;

% regularization
regularization_term = (lambda/(2*m))*(sum(sum(Theta1(:,[2:end]).^2))+...
                        sum(sum(Theta2(:,[2:end]).^2)));
J = J + regularization_term;


% part 2:
t=t';
Delta1 = zeros(size(Theta1));  % 25x401
Delta2 = zeros(size(Theta2));  % 10x26
for i=1:m
    delta3 = h_theta(:,i) - t(:,i);     % 10x1
    delta2 = Theta2'*delta3.*[1;sigmoidGradient(z2(:,i))];   % 26x1
    Delta2 = Delta2+delta3*a2(:,i)';    % 10x26
    Delta1 = Delta1+delta2(2:end)*a1(i,:);  %25x401
end

Theta1_grad = Delta1/m;
Theta2_grad = Delta2/m;

% regularization
Theta1_grad = Theta1_grad+[zeros(hidden_layer_size,1) lambda/m*Theta1(:,2:end)];
Theta2_grad = Theta2_grad+[zeros(num_labels,1) lambda/m*Theta2(:,2:end)];

% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];


end
