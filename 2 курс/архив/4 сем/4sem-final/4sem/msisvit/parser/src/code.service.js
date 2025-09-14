import {tokenize} from './tokenizer.js';
import {parseCode} from './parse-code.js';

export function getHalstead(code) {
  const tokens = {};

  const t = tokenize((content, token) => {
    if (!tokens[token.type])
      tokens[token.type] = [];

    tokens[token.type].push(content);
  });

  t.transform(code);

  return parseCode(tokens);
}
