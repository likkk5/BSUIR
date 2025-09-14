import express from 'express';
import {getHalstead} from './code.service.js';
import path from 'path';
import {fileURLToPath} from 'url';

const port = process.env.PORT || 3000;

const app = express();

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);
app.use(express.static(__dirname + '/public'));

app.use( (req, res, next) => {
  const contentType = req.headers['content-type'] || ''
    , mime = contentType.split(';')[0];

  if (mime !== 'text/plain') {
    return next();
  }

  let data = '';
  req.setEncoding('utf8');
  req.on('data', function (chunk) {
    data += chunk;
  });
  req.on('end', function () {
    req.rawBody = data;
    next();
  });
});



app.post('/analyse', (req, res) => {
  try {
    const code = req.rawBody;
    console.log(code);
    res.json(getHalstead(code));
  } catch (err) {
    console.error(err)
  }
});


app.listen(port, (err) => {
  if (err) {
    console.error(err);
    process.exit(1);
  } else
    console.log('server is running at port ' + port);
});





