---
name: fixJestTypeScriptTests
description: Fix Jest configuration and convert tests to proper Jest syntax for TypeScript
argument-hint: The test file or directory path to fix
---

Fix Jest test failures in TypeScript projects by:

1. **Diagnose the issue**: Examine error messages to identify whether the problem is:
   - Missing or incorrect Jest configuration for TypeScript
   - Non-standard test structure (e.g., exported functions instead of Jest syntax)
   - Syntax errors from improper test file format
   - Type-related issues in the test file or source code

2. **Configure Jest for TypeScript**:
   - Create or update `jest.config.js` with ts-jest preset
   - Set `testEnvironment` to 'node'
   - Configure `testMatch` pattern for `.test.ts` files
   - Add appropriate module file extensions

3. **Convert tests to proper Jest syntax**:
   - Replace exported test functions with `describe()` blocks for test suites
   - Use `test()` or `it()` blocks for individual test cases
   - Convert console.log statements to proper `expect()` assertions
   - Add meaningful assertions using Jest matchers (toBeCloseTo, toBe, toEqual, etc.)
   - Maintain test coverage while improving structure

4. **Fix related code issues**:
   - Resolve any bugs exposed by the tests
   - Fix type errors in source files that prevent tests from running
   - Ensure all methods tested actually exist and work correctly

5. **Verify the fix**:
   - Run the test suite to confirm all tests pass
   - Check that syntax errors are resolved
   - Ensure test output is meaningful and informative

Apply this to the specified test file or directory, making all necessary changes to get tests running successfully.
