function calculate(op) {
  const a = parseFloat(document.getElementById('a').value);
  const b = parseFloat(document.getElementById('b').value);
  if (isNaN(a) || isNaN(b)) {
    document.getElementById('result').innerText = 'Result: enter both numbers';
    return;
  }
  let result;
  if (op === '+') result = a + b;
  if (op === '-') result = a - b;
  document.getElementById('result').innerText = 'Result: ' + result;
}
