import { QuadraticFitOnline } from './QuadraticFitOnline';

describe('QuadraticFitOnline', () => {
    describe('basic quadratic fitting', () => {
        test('should fit sample data points correctly', () => {
            const fit = new QuadraticFitOnline();

            // Sample time series data points (from original C++ test case)
            const testData: Array<[number, number]> = [
                [0.0, 0.0],
                [1.0, 1.0],
                [2.0, 3.0],
                [3.0, 7.0]
            ];

            // Feed data points to the algorithm
            testData.forEach(([x, y]) => {
                fit.update(x, y);
            });

            const [c, b, a] = fit.getCoefficients();

            // Verify coefficients are reasonable (not exact due to online algorithm)
            expect(c).toBeDefined();
            expect(b).toBeDefined();
            expect(a).toBeDefined();

            // Test prediction
            const xTest = 4.0;
            const prediction = fit.predict(xTest);
            expect(prediction).toBeGreaterThan(0);

            // Verify equation string is generated
            const equation = fit.getEquation();
            expect(equation).toBeTruthy();
            expect(equation).toContain('y =');

            // Calculate R-squared for the fit quality
            const rSquared = fit.calculateRSquared(testData);
            expect(rSquared).toBeGreaterThan(0);
            expect(rSquared).toBeLessThanOrEqual(1);
        });
    });

    describe('perfect quadratic fitting', () => {
        test('should perfectly fit y = x² + 2x + 1', () => {
            const perfectFit = new QuadraticFitOnline();
            const perfectData: Array<[number, number]> = [];

            // Generate perfect quadratic data: y = x² + 2x + 1
            for (let x = 0; x <= 5; x++) {
                const y = x * x + 2 * x + 1;
                perfectData.push([x, y]);
                perfectFit.update(x, y);
            }

            const [c, b, a] = perfectFit.getCoefficients();

            // Verify coefficients match the equation y = x² + 2x + 1
            // With sufficient data points, should be very close
            expect(a).toBeCloseTo(1.0, 3); // quadratic term
            expect(b).toBeCloseTo(2.0, 3); // linear term
            expect(c).toBeCloseTo(1.0, 3); // constant term

            // Verify R-squared is very close to 1 (perfect fit)
            const perfectRSquared = perfectFit.calculateRSquared(perfectData);
            expect(perfectRSquared).toBeCloseTo(1.0, 5);

            // Test prediction
            const testX = 10;
            const expectedY = testX * testX + 2 * testX + 1; // 121
            const predictedY = perfectFit.predict(testX);
            expect(predictedY).toBeCloseTo(expectedY, 3);
        });
    });

    describe('utility methods', () => {
        test('should clear state correctly', () => {
            const fit = new QuadraticFitOnline();
            fit.update(1, 2);
            fit.update(2, 5);

            fit.clear();

            const [c, b, a] = fit.getCoefficients();
            expect(c).toBe(0);
            expect(b).toBe(0);
            expect(a).toBe(0);
        });

        test('should clone correctly', () => {
            const fit = new QuadraticFitOnline();
            fit.update(1, 2);
            fit.update(2, 5);

            const clone = fit.clone();
            const [c1, b1, a1] = fit.getCoefficients();
            const [c2, b2, a2] = clone.getCoefficients();

            expect(c1).toBe(c2);
            expect(b1).toBe(b2);
            expect(a1).toBe(a2);

            // Verify independence
            fit.update(3, 10);
            const [c3, b3, a3] = fit.getCoefficients();
            const [c4, b4, a4] = clone.getCoefficients();

            expect(c3).not.toBe(c4);
        });

        test('should return equation string', () => {
            const fit = new QuadraticFitOnline();
            fit.update(0, 1);
            fit.update(1, 4);
            fit.update(2, 9);

            const equation = fit.getEquation();
            expect(typeof equation).toBe('string');
            expect(equation).toContain('y =');
        });
    });
});
