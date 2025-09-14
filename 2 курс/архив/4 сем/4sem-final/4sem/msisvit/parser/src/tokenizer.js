export function dissect(min, max, fn) {
  let array;
  let index;
  let tested = {};

  if (Array.isArray(min) && typeof fn === 'undefined') {
    array = min;
    min = 0;
    let predicate = max;
    max = array.length;
    fn = function (index) {
      return predicate(array[index], index);
    };
  }

  function test(i) {
    if (typeof tested[i] === 'undefined') {
      return tested[i] = fn(i);
    } else {
      return tested[i];
    }
  }

  while (max > min + 1) {
    index = min + Math.floor((max - min) / 2);

    if (test(index)) {
      max = index;
    } else {
      min = index;
    }
  }
  return test(min) ? min : max;
}


class Tokenizer {
  _buffered = '';
  _regexes = [];
  _checkToken;

  constructor(check_token_callback) {

    if (!(this instanceof Tokenizer)) {
      return new Tokenizer(check_token_callback);
    }

    this._checkToken = check_token_callback || (() => {
    });
  }

  transform(chunk) {
    let index = 0, step = 64;
    while (index < chunk.length) {
      this._tokenize(chunk.substr(index, step));
      index += step;
    }
  };

  _getMatchingRule(str) {
    for (let i = 0; i < this._regexes.length; ++i) {
      if (this._regexes[i].regex.test(str)) {
        return this._regexes[i];
      }
    }
    return null;
  };

  _tokenize(data, nobuffer) {
    // in case we buffered data on previous writes
    data = this._buffered + data;
    this._buffered = '';
    if (!data.length) {
      return;
    }

    const self = this;
    const maxIndex = dissect(0, data.length, function (index) {
      const buf = data.substring(0, index + 1);
      return self._getMatchingRule(buf) === null;
    });

    if (maxIndex === 0) {
      throw new SyntaxError('could not tokenize ' + JSON.stringify(data));
    } else if (maxIndex === data.length && !nobuffer) {
      this._buffered = data;
    } else {
      const str = data.substring(0, maxIndex);
      const rule = this._getMatchingRule(str);
      if (!rule) {
        throw new Error('wut ?');
      }
      this._checkToken(str, rule);
      this._tokenize(data.substring(maxIndex), nobuffer);
    }
  };

  addRule(regex, type) {
    if (!type) {
      if (Array.isArray(regex)) {
        return this.addRule(regex[0], regex[1]);
      } else if (regex) {
        return this.addRule(Tokenizer[regex]);
      } else {
        throw new Error('No parameters specified');
      }
    }

    if (!(regex instanceof RegExp) && !(typeof regex === 'function') && !(typeof type === 'string')) {
      throw new Error('Invalid regex');
    }

    this._regexes.push({regex: regex, type: type});
  };
}

Tokenizer.whitespace = [/^(\s)+$/, 'whitespace'];
Tokenizer.word = [/^\w+$/, 'word'];
Tokenizer.number = [/^\d+(\.\d+)?$/, 'number'];

//operators: operators
export function tokenize(callback) {
  const t = new Tokenizer(callback);
  t.addRule(/^\/\*([^*]|\*(?!\/))*\*\/$/, 'area comment');
  t.addRule(/^\/\*([^*]|\*(?!\/))*\*?$/, 'area comment continue');
  t.addRule(/^#[^\n]*$/, 'directive'); //operator
  t.addRule(/^\/\/[^\n]*$/, 'line comment');
  t.addRule(/^"([^"\n]|\\")*"?$/, 'quote'); //operand
  t.addRule(/^'(\\?[^'\n]|\\')'?$/, 'char'); //operand
  t.addRule(/^'[^']*$/, 'char continue'); //operand
  t.addRule(/^(case|\[\])$/, 'garbage');

  t.addRule(/^(do|while|if|for|switch|return|else)$/, 'statements'); //operator
  t.addRule(/^\w+\($/, 'function'); //operator
  t.addRule(/^\($/, 'open paren'); //operator
  t.addRule(/^\)$/, 'close paren');
  t.addRule(/^\[$/, 'open square'); //operator
  t.addRule(/^\]$/, 'close square');
  t.addRule(/^{$/, 'open curly');
  t.addRule(/^}$/, 'close curly');
  t.addRule(
    /^(>=|<=|[-<>~!%^&*\/+=?|.,:;]|->|<<|>>|\|\||&&|--|\+\+|[-+*|&%\/=]=)$/,
    'operator',
  ); //operator

  t.addRule(/^(void|int|string|char|unsigned|long|double|float)$/, 'identifier type');

  t.addRule(/^([_A-Za-z]\w*)$/, 'identifier'); //operand

  t.addRule(/^[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?$/, 'number'); //operand

  t.addRule(/^(\s+)$/, 'whitespace');
  t.addRule(/^\\\n?$/, 'line continue');
  return t;
}
