const express = require('express');
const app = express();
var md5 = require('md5');
 
console.log(md5('123'));

// Settings
app.set('port', process.env.PORT || 9000);

// Middlewares -> Funciones que se ejecutan antes de procesar algo
app.use(express.json());

// Routes (URL's)
app.use(require('./routes/database_got'));

// Starting the server
app.listen(app.get('port'), () => {
  console.log(`Server on port ${app.get('port')}`);
});
