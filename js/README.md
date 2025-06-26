# Running Statistics - TypeScript Implementation

This directory contains TypeScript implementations of the C++ statistical classes. All template parameters have been removed and the classes now work specifically with JavaScript numbers.

## Classes

### CircularBuffer
A circular buffer implementation that automatically overwrites old data when the buffer is full.

```typescript
const buffer = new CircularBuffer(5);
buffer.push(1);
buffer.push(2);
console.log(buffer.toArray()); // [1, 2]
```

### RunningVariance
Calculates running variance and mean using Welford's online algorithm.

```typescript
const rv = new RunningVariance();
rv.push(1);
rv.push(2);
rv.push(3);
console.log(rv.mean()); // Mean of all values
console.log(rv.variance()); // Sample variance
```

### RollingVariance
Calculates variance over a fixed-size sliding window using an efficient rolling algorithm.

```typescript
const rollVar = new RollingVariance(10); // Window size of 10
rollVar.push(1);
rollVar.push(2);
console.log(rollVar.variance()); // Variance of last 10 values
```

### WindowVariance
Combines CircularBuffer with RunningVariance to calculate variance over a sliding window.

```typescript
const wv = new WindowVariance(5); // Window size of 5
wv.add(1);
wv.add(2);
console.log(wv.variance()); // Variance of values in window
console.log(wv.getValues()); // Array of current window values
```

## Building

```bash
npm install
npm run build
```

## Usage

```typescript
import { CircularBuffer, RunningVariance, RollingVariance, WindowVariance } from './index';
```

## Key Changes from C++

1. **No Templates**: All classes work with JavaScript `number` type
2. **Memory Management**: No manual memory management (garbage collected)
3. **Iterators**: CircularBuffer uses JavaScript's `Symbol.iterator` for `for...of` loops
4. **Method Names**: Converted to camelCase following JavaScript conventions
5. **Return Types**: Methods that returned by reference now return values directly
6. **Null Safety**: Methods that could fail (like `pop()`) return `null` instead of boolean success flags

## Performance Notes

- All classes maintain O(1) operations for their core functionality
- RollingVariance is more efficient than WindowVariance for pure variance calculation
- WindowVariance provides more flexibility with access to individual window values
