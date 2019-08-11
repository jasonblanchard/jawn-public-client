require('dotenv').config();

var express = require('express');
var morgan = require('morgan');
var path = require('path');
var fs = require('fs');

var app = express();

app.use(morgan(':method :url :status :res[content-length] - :response-time ms'));
app.use('/static', express.static(path.resolve(__dirname + '/../client/build')));

app.get('/health', (request, response) => {
  return response.json({ status: 'ok', service: 'public-client', version: 1 });
});

app.get('/*', (request, response, next) => {
  fs.readFile(path.resolve(__dirname + '/../client/build/index.html'), 'utf8', (error, file) => {
    if (error) {
      return next(error);
    }
    let hydratedHtml = file.replace("{%env%}", `
    var homepagePath='${process.env.HOMEPAGE_PATH}';
    var authApiPath = '${process.env.AUTH_API_PATH}';
    var basePath = '${process.env.BASE_PATH}';
    `);
    hydratedHtml = hydratedHtml.replace('{%basePath%}', process.env.BASE_PATH);
    return response.send(hydratedHtml);
  });
});

app.use((err, request, response, next) => {
  console.log(err);

  response.status(500)
  response.json({ error: "Something went wrong" });
});

const port = process.env.PORT || 8082;
app.listen(port, () => {
  console.log(`>>> Listening on port ${port} <<<`);
});