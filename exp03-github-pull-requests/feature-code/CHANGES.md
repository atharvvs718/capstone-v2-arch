# Code to add on the feature branch (Step 4 of the guide)

## 1. In index.html — add two buttons after the Subtract button:
    <button onclick="calculate('*')">Multiply</button>
    <button onclick="calculate('/')">Divide</button>

## 2. In script.js — add these two lines after `if (op === '-') ...`:
  if (op === '*') result = a * b;
  if (op === '/') result = b !== 0 ? a / b : 'cannot divide by zero';
