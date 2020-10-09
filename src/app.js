const express = require('express');
const morgan = require('morgan');
const helmet = require('helmet');
const cors = require('cors');
const fs = require('fs')


require('dotenv').config();

const middlewares = require('./middlewares');
const api = require('./api');

const app = express();

app.use(cors());

app.get('/bootstrap', (req,res) => {
    fs.createReadStream(__dirname + '/assets/bootstrap.min.css').pipe(res)
})

app.get('/jquery', (req,res) => {
    fs.createReadStream(__dirname + '/assets/jquery.js').pipe(res)
})

app.get('/', (req, res) => {
    fs.createReadStream(__dirname + "/view/index.html").pipe(res)
});

app.use('/api/v1', api);

app.use(middlewares.notFound);
app.use(middlewares.errorHandler);

module.exports = app;
