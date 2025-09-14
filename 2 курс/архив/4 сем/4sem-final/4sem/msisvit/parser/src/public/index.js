let input = document.getElementById('input-file');



input.addEventListener('change', function (e) {
    var file = e.target.files[0];
    var reader = new FileReader();
    reader.onload = function (e) {
        var code = e.target.result;
        let textArea = document.getElementById('code');
        textArea.value = code;
    };
    reader.readAsText(file);
});


async function generateMetrics(){
  let code = document.getElementById('code').value;
  let options = {
    method: 'POST',
    headers: {
      "Content-type": "text/plain; charset=UTF-8"
    },
    body: code
  }

  await fetch('/analyse', options).then(response => {
    if (!response.ok) {
      console.error(response);
    } else {
      return response.json();
    }
  }).then(data => {
    parseData(data);
  }).catch(err => {
    console.error(err);
  });
}

function parseData(data){
  console.log(data);
  let table = document.getElementById('metrics-strings');
  table.innerHTML = '';
  let operators = data.operators;
  let operands = data.operands;
  let rows = [];
  for(let operator in operators){
    let newRow = document.createElement('tr');
    let operatorCeil = document.createElement('td');
    let countCeil = document.createElement('td');
    operatorCeil.innerHTML = operator;
    countCeil.innerHTML = operators[operator];
    newRow.appendChild(operatorCeil);
    newRow.appendChild(countCeil);
    rows.push(newRow);
    table.appendChild(newRow);
  }

  let rowCount = 0;
  for(let operand in operands){
    let row;
    if(rowCount < rows.length){
      row = rows[rowCount];
    }
    else {
      row = document.createElement('tr');
    }

    let operandCeil = document.createElement('td');
    let countCeil = document.createElement('td');
    operandCeil.innerHTML = operand;
    countCeil.innerHTML = operands[operand];

    let empty = document.createElement('td');

    if(rowCount >= rows.length){
      row.appendChild(empty);
      empty = document.createElement('td');
      row.appendChild(empty);
    }
    row.appendChild(operandCeil);
    row.appendChild(countCeil);
    if(rowCount < rows.length){
      rowCount++;
      continue;
    }
    table.appendChild(row);
  }
  document.getElementById('operator-count').innerText = data['N1'];
  document.getElementById('operand-count').innerText = data['N2'];
  document.getElementById('program-length').innerText = data['N'];
  document.getElementById('unique-operator-count').innerText = data['n1'];
  document.getElementById('unique-operand-count').innerText = data['n2'];
  document.getElementById('program-dict').innerText = data['n'];
  document.getElementById('program-volume').innerText = data['volume'];
  document.getElementById('program-difficulty').innerText = data['difficulty'];
  document.getElementById('program-effort').innerText = data['effort'];
  document.getElementById('program-bugs').innerText = data['bugs'];
  document.getElementById('program-time').innerText = data['time'];



}
