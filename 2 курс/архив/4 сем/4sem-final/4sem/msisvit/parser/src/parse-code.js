export function parseCode(tokens) {
  const operators = {};
  const operands = {};

  function addOperator(op) {
    if (!operators[op]) {
      operators[op] = 1;
    } else {
      operators[op] += 1;
    }
  }

  function addOperand(op) {
    if (!operands[op]) {
      operands[op] = 1;
    } else {
      operands[op] += 1;
    }
  }

  if (tokens['function']) {
    for (const func of tokens['function']) {
      const funcPretty = func + ')';
      if (['printf()', 'scanf()'].includes(funcPretty))
        addOperator(funcPretty);
      else if (operands[funcPretty])
        addOperator(funcPretty)
      else
        addOperand(funcPretty)
    }
  }


  if (tokens['operator'])
    for (const op of tokens['operator']) {
      addOperator(op);
    }

  if (tokens['open square'])
    for (const op of tokens['open square']) {
      const opPretty = op + ']';
      addOperator(opPretty);
    }

  if (tokens['open paren'])
    for (const op of tokens['open paren']) {
      const opPretty = op + ')';
      addOperator(opPretty);
    }

  if (tokens['open curly'])
    for (const op of tokens['open curly']) {
      const opPretty = op + '}';
      addOperator(opPretty);
    }

  if (tokens['statements']) {
    for (const op of tokens['statements']) {
      if (op === 'switch') {
        addOperator('switch...case')
      }
      if (op === 'else') {
        if (operators['if']) {
          operators['if'] -= 1;
        } else {
          operators['if'] = -1;
        }

        addOperator('if...else');
        continue;
      }
      if (op !== 'do')
        addOperator(op);
      else {
        addOperator('do...while');
        if (operators['while']) {
          operators['while'] -= 1;
        } else {
          operators['while'] = -1;
        }
      }
    }
    if (operators['while'] === 0) {
      delete operators['while'];
    }
    if (operators['if'] === 0) {
      delete operators['if'];
    }

    if (operators['while']) {
      operators['()'] -= operators['while']
    }

    if (operators['do...while']) {
      operators['()'] -= operators['do...while']
    }

    if (operators['if']) {
      operators['()'] -= operators['if']
    }

    if (operators['if...else']) {
      operators['()'] -= operators['if...else']
    }

    if (operators['for']) {
      operators['()'] -= operators['for']
    }

    if (operators['()'] === 0)
      delete operators['()']
  }


  if (tokens['identifier']) {
    for (const op of tokens['identifier']) {
      addOperand(op);
    }
  }

  if (tokens['number']) {
    for (const op of tokens['number']) {
      addOperand(op);
    }
  }

  if (tokens['char']) {
    for (const op of tokens['char']) {
      addOperand(op);
    }
  }

  if (tokens['quote']) {
    for (const op of tokens['quote']) {
      addOperand(op);
    }
  }

  const n1 = Object.keys(operators).length;
  const n2 = Object.keys(operands).length;
  const N1 = Object.values(operators).reduce((a, b) => a + b, 0);
  const N2 = Object.values(operands).reduce((a, b) => a + b, 0);
  const n = n1 + n2;
  const N = N1 + N2;

  const volume = N * Math.log2(n);
  const difficulty = n1 / 2 * N2 / n2;
  const effort = difficulty * volume;
  const time = effort / 18;
  const bugs = Math.pow(effort, 2 / 3) / 3000;

  return {operators, operands, n1, n2, N1, N2, n, N, volume, difficulty, effort, time, bugs};
}



