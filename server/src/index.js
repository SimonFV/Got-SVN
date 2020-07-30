const express = require('express');
const app = express();

// Settings
app.set('port', process.env.PORT || 4000);

// Middlewares -> Funciones que se ejecutan antes de procesar algo
app.use(express.json());

// Routes (URL's)
app.use(require('./routes/employees'));

// Starting the server
app.listen(app.get('port'), () => {
  console.log(`Server on port ${app.get('port')}`);
});
