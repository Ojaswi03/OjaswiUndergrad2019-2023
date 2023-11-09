import numpy as np
import optimizers
import sys  # for sys.float_info.epsilon


######################################################################
# class NeuralNetwork()
######################################################################

class NeuralNetwork():

    def __init__(self, n_inputs, n_hiddens_per_layer, n_outputs, activation_function='tanh'):
        self.n_inputs = n_inputs
        self.n_outputs = n_outputs
        self.activation_function = activation_function

        # Set self.n_hiddens_per_layer to [] if argument is 0, [], or [0]
        if n_hiddens_per_layer == 0 or n_hiddens_per_layer == [] or n_hiddens_per_layer == [0]:
            self.n_hiddens_per_layer = []
        else:
            self.n_hiddens_per_layer = n_hiddens_per_layer

        # Initialize weights, by first building list of all weight matrix shapes.
        n_in = n_inputs
        shapes = []
        for nh in self.n_hiddens_per_layer:
            shapes.append((n_in + 1, nh))
            n_in = nh
        shapes.append((n_in + 1, n_outputs))

        # self.all_weights:  vector of all weights
        # self.Ws: list of weight matrices by layer
        self.all_weights, self.Ws = self.make_weights_and_views(shapes)

        # Define arrays to hold gradient values.
        # One array for each W array with same shape.
        self.all_gradients, self.dE_dWs = self.make_weights_and_views(shapes)

        self.trained = False
        self.total_epochs = 0
        self.error_trace = []
        self.Xmeans = None
        self.Xstds = None
        self.Tmeans = None
        self.Tstds = None

    def make_weights_and_views(self, shapes):
        # vector of all weights built by horizontally stacking flatenned matrices
        # for each layer initialized with uniformly-distributed values.
        all_weights = np.hstack([np.random.uniform(size=shape).flat / np.sqrt(shape[0])
                                 for shape in shapes])
        # Build list of views by reshaping corresponding elements from vector of all weights
        # into correct shape for each layer.
        views = []
        start = 0
        for shape in shapes:
            size = shape[0] * shape[1]
            views.append(all_weights[start:start + size].reshape(shape))
            start += size
        return all_weights, views

    # Return string that shows how the constructor was called
    def __repr__(self):
        return f'{type(self).__name__}({self.n_inputs}, {self.n_hiddens_per_layer}, {self.n_outputs}, \'{self.activation_function}\')'

    # Return string that is more informative to the user about the state of this neural network.
    def __str__(self):
        result = self.__repr__()
        if len(self.error_trace) > 0:
            return self.__repr__() + f' trained for {len(self.error_trace)} epochs, final training error {self.error_trace[-1]:.4f}'

    def train(self, X, T, n_epochs, learning_rate, method='sgd', verbose=True):
        '''
train:
  X: n_samples x n_inputs matrix of input samples, one per row
  T: n_samples x n_outputs matrix of target output values, one sample per row
  n_epochs: number of passes to take through all samples updating weights each pass
  learning_rate: factor controlling the step size of each update
  method: is either 'sgd' or 'adam'
        '''

        # Setup standardization parameters
        if self.Xmeans is None:
            self.Xmeans = X.mean(axis=0)
            self.Xstds = X.std(axis=0)
            self.Xstds[self.Xstds == 0] = 1  # So we don't divide by zero when standardizing
            self.Tmeans = T.mean(axis=0)
            self.Tstds = T.std(axis=0)

        # Standardize X and T
        X = (X - self.Xmeans) / self.Xstds
        T = (T - self.Tmeans) / self.Tstds

        # Instantiate Optimizers object by giving it vector of all weights
        optimizer = optimizers.Optimizers(self.all_weights)

        # Define function to convert value from error_f into error in original T units,
        # but only if the network has a single output. Multiplying by self.Tstds for
        # multiple outputs does not correctly unstandardize the error.
        if len(self.Tstds) == 1:
            error_convert_f = lambda err: (np.sqrt(err) * self.Tstds)[0]  # to scalar
        else:
            error_convert_f = lambda err: np.sqrt(err)[0]  # to scalar

        if method == 'sgd':

            error_trace = optimizer.sgd(self.error_f, self.gradient_f,
                                        fargs=[X, T], n_epochs=n_epochs,
                                        learning_rate=learning_rate,
                                        error_convert_f=error_convert_f)

        elif method == 'adam':

            error_trace = optimizer.adam(self.error_f, self.gradient_f,
                                         fargs=[X, T], n_epochs=n_epochs,
                                         learning_rate=learning_rate,
                                         error_convert_f=error_convert_f)

        else:
            raise Exception("method must be 'sgd' or 'adam'")

        self.error_trace = error_trace

        # Return neural network object to allow applying other methods after training.
        #  Example:    Y = nnet.train(X, T, 100, 0.01).use(X)
        return self

    def relu(self, s):
        s[s < 0] = 0
        return s

    def grad_relu(self, s):
        return (s > 0).astype(int)

    def forward_pass(self, X):
        '''X assumed already standardized. Output returned as standardized.'''
        self.Ys = [X]
        for W in self.Ws[:-1]:
            if self.activation_function == 'relu':
                self.Ys.append(self.relu(self.Ys[-1] @ W[1:, :] + W[0:1, :]))
            else:
                self.Ys.append(np.tanh(self.Ys[-1] @ W[1:, :] + W[0:1, :]))
        last_W = self.Ws[-1]
        self.Ys.append(self.Ys[-1] @ last_W[1:, :] + last_W[0:1, :])
        return self.Ys

    # Function to be minimized by optimizer method, mean squared error
    def error_f(self, X, T):
        Ys = self.forward_pass(X)
        mean_sq_error = np.mean((T - Ys[-1]) ** 2)
        return mean_sq_error

    # Gradient of function to be minimized for use by optimizer method
    def gradient_f(self, X, T):
        '''Assumes forward_pass just called with layer outputs in self.Ys.'''
        error = T - self.Ys[-1]
        n_samples = X.shape[0]
        n_outputs = T.shape[1]
        delta = - error / (n_samples * n_outputs)
        n_layers = len(self.n_hiddens_per_layer) + 1
        # Step backwards through the layers to back-propagate the error (delta)
        for layeri in range(n_layers - 1, -1, -1):
            # gradient of all but bias weights
            self.dE_dWs[layeri][1:, :] = self.Ys[layeri].T @ delta
            # gradient of just the bias weights
            self.dE_dWs[layeri][0:1, :] = np.sum(delta, 0)
            # Back-propagate this layer's delta to previous layer
            if self.activation_function == 'relu':
                delta = delta @ self.Ws[layeri][1:, :].T * self.grad_relu(self.Ys[layeri])
            else:
                delta = delta @ self.Ws[layeri][1:, :].T * (1 - self.Ys[layeri] ** 2)
        return self.all_gradients

    def use(self, X):
        '''X assumed to not be standardized'''
        # Standardize X
        X = (X - self.Xmeans) / self.Xstds
        Ys = self.forward_pass(X)
        Y = Ys[-1]
        # Unstandardize output Y before returning it
        return Y * self.Tstds + self.Tmeans


class NeuralNetworkClassifier(NeuralNetwork):

    def __init__(self, n_inputs, n_hiddens_per_layer, n_outputs, activation_function='tanh'):
        super().__init__(n_inputs, n_hiddens_per_layer, n_outputs, activation_function)

    def makeIndicatorVars(self, T):
        # Make sure T is two-dimensional. Should be nSamples x 1.
        if T.ndim == 1:
            T = T.reshape((-1, 1))
        return (T == np.unique(T)).astype(int)

    def softmax(self, X):
        mx = max(0, np.max(X))
        expX = np.exp(X - mx)
        denom = np.sum(expX, axis=1).reshape((-1, 1)) + sys.float_info.epsilon
        gs = expX / denom
        return gs

    def error_f(self, X, T):
        # when you see this, make sure T are already indicator variables
        Ys = self.forward_pass(X)
        probs = self.softmax(Ys[-1])
        LL = T * np.log(probs + sys.float_info.epsilon)
        neg_mean_LL = - np.mean(LL)
        return neg_mean_LL
        # mean_sq_error = np.mean((T - Ys[-1]) ** 2)
        # return mean_sq_error

    def gradient_f(self, X, T):
        '''Assumes forward_pass just called with layer outputs in self.Ys.'''
        error = (T - self.softmax(self.Ys[-1]))
        delta = - error / (X.shape[0] * T.shape[1])
        n_layers = len(self.n_hiddens_per_layer) + 1
        # Step backwards through the layers to back-propagate the error (delta)
        for layeri in range(n_layers - 1, -1, -1):
            # gradient of all but bias weights
            self.dE_dWs[layeri][1:, :] = self.Ys[layeri].T @ delta
            # gradient of just the bias weights
            self.dE_dWs[layeri][0:1, :] = np.sum(delta, 0)
            # Back-propagate this layer's delta to previous layer
            if self.activation_function == 'relu':
                delta = delta @ self.Ws[layeri][1:, :].T * self.grad_relu(self.Ys[layeri])
            else:
                delta = delta @ self.Ws[layeri][1:, :].T * (1 - self.Ys[layeri] ** 2)
        return self.all_gradients

    def use(self, X):
        X = (X - self.Xmeans) / self.Xstds
        Ys = self.forward_pass(X)
        Y = self.softmax(Ys[-1])
        classes = self.classes[np.argmax(Y, axis=1)].reshape((-1, 1))
        return classes, Y

    def train(self, X, T, n_epochs, learning_rate, method='sgd', verbose=True):
        # Setup standardization parameters
        if self.Xmeans is None:
            self.Xmeans = X.mean(axis=0)
            self.Xstds = X.std(axis=0)
            self.Xstds[self.Xstds == 0] = 1  # So we don't divide by zero when standardizing

        # Standardize X
        X = (X - self.Xmeans) / self.Xstds

        self.classes = np.unique(T)

        TI = self.makeIndicatorVars(T)

        # Instantiate Optimizers object by giving it vector of all weights
        optimizer = optimizers.Optimizers(self.all_weights)

        # Define function to convert value from error_f into error in original T units,
        # but only if the network has a single output. Multiplying by self.Tstds for
        # multiple outputs does not correctly unstandardize the error.
        error_convert_f = lambda nll: np.exp(-nll)

        if method == 'sgd':

            error_trace = optimizer.sgd(self.error_f, self.gradient_f,
                                        fargs=[X, TI], n_epochs=n_epochs,
                                        learning_rate=learning_rate,
                                        error_convert_f=error_convert_f)

        elif method == 'adam':

            error_trace = optimizer.adam(self.error_f, self.gradient_f,
                                         fargs=[X, TI], n_epochs=n_epochs,
                                         learning_rate=learning_rate,
                                         error_convert_f=error_convert_f)

        else:
            raise Exception("method must be 'sgd' or 'adam'")

        self.error_trace = error_trace

        # Return neural network object to allow applying other methods after training.
        #  Example:    Y = nnet.train(X, T, 100, 0.01).use(X)
        return self


class NeuralNetworkClassifierCNN(NeuralNetworkClassifier):

    def __init__(self, n_inputs, n_hiddens_per_layer, n_outputs, patch_size, stride, activation_function='tanh'):
        #super().__init__(n_inputs, n_hiddens_per_layer, n_outputs)
        # Initialize weights, by first building list of all weight matrix shapes.
        self.n_inputs = n_inputs
        self.n_outputs = n_outputs
        self.activation_function = activation_function
        self.patch_size = patch_size
        self.stride = stride

        if n_hiddens_per_layer == 0 or n_hiddens_per_layer == [] or n_hiddens_per_layer == [0]:
            self.n_hiddens_per_layer = []
        else:
            self.n_hiddens_per_layer = n_hiddens_per_layer

        # Initialize weights, by first building list of all weight matrix shapes.
        n_in = n_inputs
        shapes = []
        # First build shape of weight matrix for convolutional layer.  Only one allowed.
        shapes = [(self.patch_size * self.patch_size + 1, n_hiddens_per_layer[0])]
        input_size = int(np.sqrt(n_inputs))
        n_in = ((input_size - self.patch_size) // self.stride + 1) ** 2 * self.n_hiddens_per_layer[0]
        for nh in self.n_hiddens_per_layer[1:]:
            shapes.append((n_in + 1, nh))
            n_in = nh
        shapes.append((n_in + 1, self.n_outputs))

        # self.all_weights:  vector of all weights
        # self.Ws: list of weight matrices by layer
        self.all_weights, self.Ws = self.make_weights_and_views(shapes)

        # Define arrays to hold gradient values.
        # One array for each W array with same shape.
        self.all_gradients, self.dE_dWs = self.make_weights_and_views(shapes)

        self.trained = False
        self.total_epochs = 0
        self.error_trace = []
        self.Xmeans = None
        self.Xstds = None

    # Return string that shows how the constructor was called
    def __repr__(self):
        return f'{type(self).__name__}({self.n_inputs}, {self.n_hiddens_per_layer}, {self.n_outputs}, {self.patch_size}, {self.stride}, \'{self.activation_function}\')'
        
    # Return string that is more informative to the user about the state of this neural network.
    def __str__(self):
        result = self.__repr__()
        if len(self.error_trace) > 0:
            return self.__repr__() + f' trained for {len(self.error_trace)} epochs, final training error {self.error_trace[-1]:.4f}'

    def makeIndicatorVars(self, T):
        # Make sure T is two-dimensional. Should be nSamples x 1.
        if T.ndim == 1:
            T = T.reshape((-1, 1))
        return (T == np.unique(T)).astype(int)

    def _make_patches(self, X, patch_size, stride=1):
        X = np.ascontiguousarray(X)  # make sure X values are contiguous in memory

        n_samples = X.shape[0]
        image_size = int(np.sqrt(X.shape[1]))
        n_patches = (image_size - patch_size) // stride + 1
        nb = X.itemsize  # number of bytes each value
        new_shape = [n_samples, n_patches, n_patches, patch_size, patch_size]
        new_strides = [image_size * image_size * nb,
                       image_size * stride * nb,
                       stride * nb,
                       image_size * nb,
                       nb]
        X = np.lib.stride_tricks.as_strided(X, shape=new_shape, strides=new_strides)
        X = X.reshape(n_samples, n_patches * n_patches, patch_size * patch_size)
        return X

    def use(self, X):
        '''X assumed to not be standardized. Returns (classes, class_probabilities)'''
        # Standardize X
        X = (X - self.Xmeans) / self.Xstds
        # Convert flattened samples into patches
        X_patches = self._make_patches(X, self.patch_size, self.stride)
        Ys = self.forward_pass(X_patches)
        Y = self.softmax(Ys[-1])
        classes = self.classes[np.argmax(Y, axis=1)].reshape(-1, 1)
        return classes, Y

    def forward_pass(self, X_patches):
        '''X assumed already standardized. Output returned as standardized.'''
        self.Ys = [X_patches]
        for layer_i, W in enumerate(self.Ws[:-1]):
            if self.activation_function == 'relu':
                self.Ys.append(self.relu(self.Ys[-1] @ W[1:, :] + W[0:1, :]))
            else:
                self.Ys.append(np.tanh(self.Ys[-1] @ W[1:, :] + W[0:1, :]))
            # If convolutional layer, flatten each sample into vector for input to following f
            # fully-connected layer.
            if layer_i == 0:
                self.Ys[-1] = self.Ys[-1].reshape(self.Ys[-1].shape[0], -1)
        last_W = self.Ws[-1]
        self.Ys.append(self.Ys[-1] @ last_W[1:, :] + last_W[0:1, :])
        return self.Ys

    def train(self, X, T, n_epochs, learning_rate, method='sgd', verbose=True):
        # Setup standardization parameters
        if self.Xmeans is None:
            self.Xmeans = X.mean(axis=0)
            self.Xstds = X.std(axis=0)
            self.Xstds[self.Xstds == 0] = 1  # So we don't divide by zero when standardizing

        # Standardize X
        X = (X - self.Xmeans) / self.Xstds

        X_patches = self._make_patches(X, self.patch_size, self.stride)

        self.classes = np.unique(T)

        T_indicator_vars = self.makeIndicatorVars(T)

        # Instantiate Optimizers object by giving it vector of all weights
        optimizer = optimizers.Optimizers(self.all_weights)

        # Define function to convert value from error_f into error in original T units,
        # but only if the network has a single output. Multiplying by self.Tstds for
        # multiple outputs does not correctly unstandardize the error.
        error_convert_f = lambda nll: np.exp(-nll)

        if method == 'sgd':

            error_trace = optimizer.sgd(self.error_f, self.gradient_f,
                                        fargs=[X_patches, T_indicator_vars], n_epochs=n_epochs,
                                        learning_rate=learning_rate,
                                        error_convert_f=error_convert_f)

        elif method == 'adam':

            error_trace = optimizer.adam(self.error_f, self.gradient_f,
                                        fargs=[X_patches, T_indicator_vars], n_epochs=n_epochs,
                                        learning_rate=learning_rate,
                                        error_convert_f=error_convert_f)

        else:
            raise Exception("method must be 'sgd' or 'adam'")

        self.error_trace = error_trace

        # Return neural network object to allow applying other methods after training.
        #  Example:    Y = nnet.train(X, T, 100, 0.01).use(X)
        return self

    # Gradient of function to be minimized for use by optimizer method
    def gradient_f(self, X, T):
        '''Assumes forward_pass just called with layer outputs in self.Ys.'''
        #X_patches = self._make_patches(X, self.patch_size, self.stride)
        error = (T - self.softmax(self.Ys[-1]))
        #error = T - self.Ys[-1]
        n_samples = X.shape[0]
        n_outputs = T.shape[1]
        delta = - error / (n_samples * n_outputs)
        n_layers = len(self.n_hiddens_per_layer) + 1
        # Step backwards through the layers to back-propagate the error (delta)
        for layeri in range(n_layers - 1, -1, -1):
            if layeri == 0:
                patch_n_values = X.shape[-1]
                n_conv_units = self.n_hiddens_per_layer[0]
                delta_reshaped = delta.reshape(-1, n_conv_units)
                # And we must reshape the convolutional layer input matrix to a compatible shape.
                conv_layer_inputs_reshaped = self.Ys[0].reshape(-1, patch_n_values)
                # Now we can calculate the dE_dWs for the convolutional layer with a simple matrix
                # multiplication.
                self.dE_dWs[layeri][1:, :] = conv_layer_inputs_reshaped.T @ delta_reshaped
                self.dE_dWs[layeri][0:1, :] = np.sum(delta_reshaped, axis=0)
            else:
                # gradient of all but bias weights
                self.dE_dWs[layeri][1:, :] = self.Ys[layeri].T @ delta
                # gradient of just the bias weights
                self.dE_dWs[layeri][0:1, :] = np.sum(delta, 0)
                # Back-propagate this layer's delta to previous layer
                if self.activation_function == 'relu':
                    delta = delta @ self.Ws[layeri][1:, :].T * self.grad_relu(self.Ys[layeri])
                else:
                    delta = delta @ self.Ws[layeri][1:, :].T * (1 - self.Ys[layeri] ** 2)
        return self.all_gradients


# this is for the neural network classifier CNN
if __name__ == '__main__':
    import numpy as np
    import matplotlib.pyplot as plt

    square = np.array([[0] * 20,
                       [0] * 20,
                       [0] * 20,
                       [0] * 20,
                       [0] * 4 + [1] * 12 + [0] * 4,
                       [0] * 4 + [1] + [0] * 10 + [1] + [0] * 4,
                       [0] * 4 + [1] + [0] * 10 + [1] + [0] * 4,
                       [0] * 4 + [1] + [0] * 10 + [1] + [0] * 4,
                       [0] * 4 + [1] + [0] * 10 + [1] + [0] * 4,
                       [0] * 4 + [1] + [0] * 10 + [1] + [0] * 4,
                       [0] * 4 + [1] + [0] * 10 + [1] + [0] * 4,
                       [0] * 4 + [1] + [0] * 10 + [1] + [0] * 4,
                       [0] * 4 + [1] + [0] * 10 + [1] + [0] * 4,
                       [0] * 4 + [1] + [0] * 10 + [1] + [0] * 4,
                       [0] * 4 + [1] + [0] * 10 + [1] + [0] * 4,
                       [0] * 4 + [1] * 12 + [0] * 4,
                       [0] * 20,
                       [0] * 20,
                       [0] * 20,
                       [0] * 20])
    diamond = np.array([[0] * 20,
                        [0] * 20,
                        [0] * 20,
                        [0] * 20,
                        [0] * 9 + [1] + [0] * 10,
                        [0] * 8 + [1, 0, 1] + [0] * 9,
                        [0] * 7 + [1, 0, 0, 0, 1] + [0] * 8,
                        [0] * 6 + [1, 0, 0, 0, 0, 0, 1] + [0] * 7,
                        [0] * 5 + [1, 0, 0, 0, 0, 0, 0, 0, 1] + [0] * 6,
                        [0] * 4 + [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1] + [0] * 5,
                        [0] * 3 + [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1] + [0] * 4,
                        [0] * 4 + [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1] + [0] * 5,
                        [0] * 5 + [1, 0, 0, 0, 0, 0, 0, 0, 1] + [0] * 6,
                        [0] * 6 + [1, 0, 0, 0, 0, 0, 1] + [0] * 7,
                        [0] * 7 + [1, 0, 0, 0, 1] + [0] * 8,
                        [0] * 8 + [1, 0, 1] + [0] * 9,
                        [0] * 9 + [1] + [0] * 10,
                        [0] * 20,
                        [0] * 20,
                        [0] * 20])


    def draw_neg_image(image, label=''):
        plt.imshow(-image, cmap='gray')
        plt.xticks([])
        plt.yticks([])
        plt.title(label)


    def make_images(n_each_class):
        images = np.zeros((n_each_class * 2, 20, 20))  # nSamples, rows, columns
        radii = 3 + np.random.randint(10 - 5, size=(n_each_class * 2, 1))
        centers = np.zeros((n_each_class * 2, 2))
        for i in range(n_each_class * 2):
            r = radii[i, 0]
            centers[i, :] = r + 1 + np.random.randint(18 - 2 * r, size=(1, 2))
            x = int(centers[i, 0])
            y = int(centers[i, 1])
            if i < n_each_class:
                # squares
                images[i, x - r:x + r, y + r] = 1.0
                images[i, x - r:x + r, y - r] = 1.0
                images[i, x - r, y - r:y + r] = 1.0
                images[i, x + r, y - r:y + r + 1] = 1.0
            else:
                # diamonds
                images[i, range(x - r, x), range(y, y + r)] = 1.0
                images[i, range(x - r, x), range(y, y - r, -1)] = 1.0
                images[i, range(x, x + r + 1), range(y + r, y - 1, -1)] = 1.0
                images[i, range(x, x + r), range(y - r, y)] = 1.0
        T = np.array(['square'] * n_each_class + ['diamond'] * n_each_class).reshape(-1, 1)
        return images, T


    n_each_class = 100
    Xtrain, Ttrain = make_images(n_each_class)
    Xtest, Ttest = make_images(n_each_class)
    Xtrain = Xtrain.reshape(Xtrain.shape[0], -1)
    Xtest = Xtest.reshape(Xtest.shape[0], -1)

    nnet = NeuralNetworkClassifierCNN(Xtrain.shape[1], [2], len(np.unique(Ttrain)),
                                         patch_size=5, stride=2)

    import time

    start_time = time.time()
    nnet.train(Xtrain, Ttrain, 2000, learning_rate=0.01, verbose=True, method='adam')
    classes_train, probs_train = nnet.use(Xtrain)

    print(f'took {time.time() - start_time} seconds')
    print(f'Train percent correct {100 * np.mean(Ttrain == classes_train)}')

    classes_test, probs_test = nnet.use(Xtest)
    print(f'Test fraction correct {100 * np.mean(Ttest == classes_test)}')

    plt.figure(figsize=(10, 5))
    plt.subplot(1, 2, 1)
    plt.plot(nnet.error_trace)

    Ttest_i = (Ttest == 'diamond').astype(int)

    plt.subplot(1, 2, 2)
    plt.plot(Ttest_i, 'o-')
    plt.plot(probs_test[:, :], '-')
    plt.legend(('Ttest', 'Probs Class 1', 'Probs Class 0'))
    plt.show()
    
'''

# This is for the neural network classifier

if __name__ == '__main__':
    import matplotlib.pyplot as plt

    X = np.arange(100).reshape((-1, 1))
    T = X.copy()
    T[T <= 25] = 25
    T[np.logical_and(25 < T, T <= 75)] = 75
    T[T > 75] = 100

    hiddens = [10]
    nnet = NeuralNetworkClassifier(X.shape[1], hiddens, len(np.unique(T)))
    nnet.train(X, T, 200, 0.01, method='adam', verbose=True)

    plt.subplot(1, 2, 1)
    plt.plot(nnet.error_trace)
    plt.xlabel('Epoch')
    plt.ylabel('Likelihood')

    plt.subplot(1, 2, 2)
    plt.plot(T + 5, 'o-', label='T + 5')  # to see, when predicted overlap T very closely
    plt.plot(nnet.use(X)[0], 'o-', label='Y')
    plt.legend()


    def confusion_matrix(Y_classes, Ttest):
        table = []
        class_names = np.unique(T)
        for true_class in np.unique(T):
            row = []
            for predicted_class in np.unique(T):
                row.append(100 * np.mean(Y_classes[Ttest == true_class] == predicted_class))
                # row.append(f'{100 * np.mean(Classes[Ttrain == true_class] == predicted_class):0.1f}')
            table.append(row)
        import pandas
        conf_matrix = pandas.DataFrame(table, index=class_names, columns=class_names)
        return conf_matrix


    Y_classes, Y_probs = nnet.use(X)
    conf_matrix = confusion_matrix(Y_classes, T)
    print(conf_matrix)
'''
