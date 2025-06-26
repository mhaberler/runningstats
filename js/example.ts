import { CircularBuffer, RunningVariance, RollingVariance, WindowVariance } from './index';

// Example usage and tests
console.log('=== CircularBuffer Test ===');
const cb = new CircularBuffer(3);
cb.push(1);
cb.push(2);
cb.push(3);
console.log('Buffer contents:', cb.toArray()); // [1, 2, 3]
cb.push(4); // Should overwrite the first element
console.log('After adding 4:', cb.toArray()); // [4, 2, 3] or similar based on implementation

console.log('\n=== RunningVariance Test ===');
const rv = new RunningVariance();
[1, 2, 3, 4, 5].forEach(x => rv.push(x));
console.log('Mean:', rv.mean());
console.log('Variance:', rv.variance());
console.log('Standard Deviation:', rv.standardDeviation());

console.log('\n=== RollingVariance Test ===');
const rollVar = new RollingVariance(3);
[1, 2, 3, 4, 5].forEach(x => rollVar.push(x));
console.log('Rolling Mean:', rollVar.getMean());
console.log('Rolling Variance:', rollVar.variance());
console.log('Rolling Std Dev:', rollVar.standardDeviation());

console.log('\n=== WindowVariance Test ===');
const wv = new WindowVariance(3);
[1, 2, 3, 4, 5].forEach(x => wv.add(x));
console.log('Window Mean:', wv.mean());
console.log('Window Variance:', wv.variance());
console.log('Window Values:', wv.getValues());
console.log('Window Size:', wv.getWindowSize());
console.log('Current Size:', wv.getCurrentSize());
console.log('Is Full:', wv.isFull());
