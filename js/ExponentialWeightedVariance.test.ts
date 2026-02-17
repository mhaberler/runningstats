import { ExponentialWeightedVariance } from './ExponentialWeightedVariance';

describe('ExponentialWeightedVariance', () => {
    describe('initialization', () => {
        test('should initialize with default alpha', () => {
            const ewv = new ExponentialWeightedVariance();
            expect(ewv.getAlpha()).toBe(0.1);
            expect(ewv.mean()).toBe(0);
            expect(ewv.variance()).toBe(0);
            expect(ewv.numDataValues()).toBe(0);
            expect(ewv.isInitialized()).toBe(false);
        });

        test('should initialize with custom alpha', () => {
            const ewv = new ExponentialWeightedVariance(0.5);
            expect(ewv.getAlpha()).toBe(0.5);
        });
    });

    describe('basic statistics', () => {
        test('should track mean and variance for simple data', () => {
            const ewv = new ExponentialWeightedVariance(0.1);
            const data = [1, 2, 3, 4, 5];

            data.forEach(x => ewv.push(x));

            expect(ewv.numDataValues()).toBe(5);
            expect(ewv.mean()).toBeGreaterThan(0);
            expect(ewv.variance()).toBeGreaterThan(0);
            expect(ewv.isInitialized()).toBe(true);
        });

        test('should have zero variance for constant values', () => {
            const ewv = new ExponentialWeightedVariance(0.1);

            // Push same value multiple times (need many iterations for convergence with low alpha)
            for (let i = 0; i < 100; i++) {
                ewv.push(5.0);
            }

            // With alpha=0.1 and 100 iterations, should be very close to 5.0
            expect(ewv.mean()).toBeCloseTo(5.0, 1);
            expect(ewv.variance()).toBeCloseTo(0.0, 2);
        });

        test('should calculate standard deviation correctly', () => {
            const ewv = new ExponentialWeightedVariance(0.2);

            for (let i = 0; i < 10; i++) {
                ewv.push(i);
            }

            const stddev = ewv.standardDeviation();
            const variance = ewv.variance();

            expect(stddev).toBeCloseTo(Math.sqrt(variance), 10);
        });

        test('should handle single value correctly', () => {
            const ewv = new ExponentialWeightedVariance(0.3);
            ewv.push(7.5);

            // After one value, mean = alpha * value = 0.3 * 7.5 = 2.25
            expect(ewv.mean()).toBeCloseTo(2.25, 10);
            // Variance = (1-alpha) * (diff * incr) = 0.7 * (7.5 * 2.25) = 11.8125
            expect(ewv.variance()).toBeCloseTo(11.8125, 4);
            expect(ewv.numDataValues()).toBe(1);
        });
    });

    describe('alpha parameter effects', () => {
        test('higher alpha should converge faster to recent values', () => {
            const data = [1, 2, 3, 4, 5, 10, 10, 10, 10, 10];

            const ewvLow = new ExponentialWeightedVariance(0.1);
            const ewvMid = new ExponentialWeightedVariance(0.5);
            const ewvHigh = new ExponentialWeightedVariance(0.9);

            data.forEach(x => {
                ewvLow.push(x);
                ewvMid.push(x);
                ewvHigh.push(x);
            });

            // Higher alpha should have mean closer to recent values (10)
            expect(ewvHigh.mean()).toBeGreaterThan(ewvMid.mean());
            expect(ewvMid.mean()).toBeGreaterThan(ewvLow.mean());
        });

        test('should allow alpha to be changed', () => {
            const ewv = new ExponentialWeightedVariance(0.1);

            ewv.setAlpha(0.8);
            expect(ewv.getAlpha()).toBe(0.8);

            // Verify new alpha is used in calculations
            ewv.push(5);
            ewv.push(10);

            expect(ewv.mean()).toBeGreaterThan(7); // Should be closer to 10 with high alpha
        });
    });

    describe('variance behavior', () => {
        test('should track variance for alternating values', () => {
            const ewv = new ExponentialWeightedVariance(0.2);

            // Alternating between 0 and 10
            for (let i = 0; i < 50; i++) {
                ewv.push(i % 2 === 0 ? 0 : 10);
            }

            // Mean should be around 5, variance should be significant
            expect(ewv.mean()).toBeGreaterThan(3);
            expect(ewv.mean()).toBeLessThan(7);
            expect(ewv.variance()).toBeGreaterThan(10);
        });

        test('should decrease variance when values stabilize', () => {
            const ewv = new ExponentialWeightedVariance(0.3);

            // Start with varying values
            [1, 5, 2, 8, 3].forEach(x => ewv.push(x));
            const varianceAfterVarying = ewv.variance();

            // Then add constant values
            for (let i = 0; i < 20; i++) {
                ewv.push(5);
            }
            const varianceAfterStable = ewv.variance();

            expect(varianceAfterStable).toBeLessThan(varianceAfterVarying);
        });
    });

    describe('utility methods', () => {
        test('should clear correctly', () => {
            const ewv = new ExponentialWeightedVariance(0.2);

            [1, 2, 3, 4, 5].forEach(x => ewv.push(x));

            expect(ewv.isInitialized()).toBe(true);

            ewv.clear();

            expect(ewv.mean()).toBe(0);
            expect(ewv.variance()).toBe(0);
            expect(ewv.numDataValues()).toBe(0);
            expect(ewv.isInitialized()).toBe(false);
        });

        test('should clone correctly', () => {
            const ewv = new ExponentialWeightedVariance(0.3);
            [1, 2, 3, 4, 5].forEach(x => ewv.push(x));

            const clone = ewv.clone();

            expect(clone.getAlpha()).toBe(ewv.getAlpha());
            expect(clone.mean()).toBe(ewv.mean());
            expect(clone.variance()).toBe(ewv.variance());
            expect(clone.numDataValues()).toBe(ewv.numDataValues());

            // Verify independence
            ewv.push(10);
            expect(clone.mean()).not.toBe(ewv.mean());
        });

        test('should maintain state after alpha change', () => {
            const ewv = new ExponentialWeightedVariance(0.1);
            [1, 2, 3].forEach(x => ewv.push(x));

            const meanBefore = ewv.mean();
            const varianceBefore = ewv.variance();
            const countBefore = ewv.numDataValues();

            ewv.setAlpha(0.5);

            // Changing alpha shouldn't affect existing state
            expect(ewv.mean()).toBe(meanBefore);
            expect(ewv.variance()).toBe(varianceBefore);
            expect(ewv.numDataValues()).toBe(countBefore);
        });
    });

    describe('edge cases', () => {
        test('should handle very small alpha', () => {
            const ewv = new ExponentialWeightedVariance(0.01);
            [1, 2, 3, 4, 5, 15, 20].forEach(x => ewv.push(x));

            // With very small alpha, should change slowly
            expect(ewv.mean()).toBeLessThan(10);
        });

        test('should handle alpha close to 1', () => {
            const ewv = new ExponentialWeightedVariance(0.99);
            [1, 2, 3, 4, 5, 100].forEach(x => ewv.push(x));

            // With alpha near 1, should track most recent value closely
            expect(ewv.mean()).toBeGreaterThan(90);
        });

        test('should handle negative values', () => {
            const ewv = new ExponentialWeightedVariance(0.2);
            [-5, -3, -1, 0, 1, 3, 5].forEach(x => ewv.push(x));

            expect(ewv.mean()).toBeDefined();
            expect(ewv.variance()).toBeGreaterThanOrEqual(0);
        });

        test('should handle large values', () => {
            const ewv = new ExponentialWeightedVariance(0.1);
            [1000, 2000, 3000, 4000, 5000].forEach(x => ewv.push(x));

            expect(ewv.mean()).toBeGreaterThan(0);
            expect(ewv.variance()).toBeGreaterThan(0);
            expect(isFinite(ewv.mean())).toBe(true);
            expect(isFinite(ewv.variance())).toBe(true);
        });
    });
});
