// grok conversation: https://grok.com/share/bGVnYWN5_7e91020c-652b-4ec1-ba92-9f6ceacd7440

#include <Eigen/Dense>

class QuadraticFitOnline {
  private:
    Eigen::Vector3f beta;  // Coefficients [c, b, a]
    Eigen::Matrix3f P;     // Inverse covariance matrix

  public:
    // Constructor: Initialize beta to zero and P to a large diagonal matrix
    QuadraticFitOnline() {
        beta.setZero();
        P = 1e6 * Eigen::Matrix3f::Identity();
    }

    // Update the fit with a new data point (x, y)
    void update(float x, float y) {
        // Feature vector: [1, x, x^2]
        Eigen::Vector3f x_vec(1.0, x, x * x);

        // Compute P * x_vec
        Eigen::Vector3f Px = P * x_vec;

        // Compute the scalar denominator
        float scalar = 1.0 + x_vec.dot(Px);

        // Compute the gain vector K
        Eigen::Vector3f K = Px / scalar;

        // Compute the prediction error
        float error = y - x_vec.dot(beta);

        // Update the coefficients
        beta += K * error;

        // Update the covariance matrix P (symmetric update)
        P -= (Px * Px.transpose()) / scalar;
    }

    // Get the current coefficients [c, b, a]
    Eigen::Vector3f getCoefficients() const {
        return beta;
    }

    // Predict y for a given x
    float predict(float x) const {
        Eigen::Vector3f x_vec(1.0, x, x * x);
        return x_vec.dot(beta);
    }
};

#if 0
#include <iostream>

int main() {
    QuadraticFitOnline fit;

    // Sample time series data points
    float x[] = {0.0, 1.0, 2.0, 3.0};
    float y[] = {0.0, 1.0, 3.0, 7.0}; // Example data (not perfectly quadratic)
    int n = 4;

    // Feed data points to the algorithm
    for (int i = 0; i < n; ++i) {
        fit.update(x[i], y[i]);
        Eigen::Vector3f coeffs = fit.getCoefficients();
        std::cout << "After point (" << x[i] << ", " << y[i] << "): "
                  << "c = " << coeffs[0] << ", b = " << coeffs[1]
                  << ", a = " << coeffs[2] << std::endl;
    }

    // Predict a value
    float x_test = 4.0;
    std::cout << "Predicted y at x = " << x_test << ": "
              << fit.predict(x_test) << std::endl;

    return 0;
}
#endif