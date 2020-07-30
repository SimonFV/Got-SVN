const express = require('express');
//const mongoose = require('mongoose');
const bodyParser = require('body-parser');

const app = express();

const cors = require('cors');

app.use(cors());

app.use(bodyParser.json());

/*
// Connect to MongoDB
mongoose
  .connect(
    'mongodb://mongo:27017/docker-node-mongo',
    { useNewUrlParser: true }
  )
  .then(() => console.log('MongoDB Connected'))
  .catch(err => console.log(err));

*/


//ROUTES
app.get('/', (req, res) => {
  res.send("Hello from Server.");
});

/*
//GET ALL USERS
app.get('/api/users', async (req, res) => {
  try {
    const users = await User.find();
    res.json(users);
  }
  catch (err) {
    res.json({ message: err });
  }
});

//ADD USER
app.post('/api/users', async (req, res) => {
  const user = new User({
    id: req.body.id,
    name: req.body.name,
    age: req.body.age
  });

  try {
    const savedUser = await user.save();
    res.json(savedUser);
  }
  catch (err) {
    res.json({ message: err });
  }
});

//GET SPECIFIC USER
app.get('/api/users/:id', async (req, res) => {
  try {
    const user = await User.find({ id: parseInt(req.params.id) });
    res.json(user);
  }
  catch (err) {
    res.json({ message: err });
  }
});

//UPDATE SPECIFIC USER
app.patch('/api/users/:id', async (req, res) => {
  try {
    const updatedUser = await User.updateOne({ id: parseInt(req.params.id) },
      { $set: { id: req.body.id, name: req.body.name, age: req.body.age } }
    );
    res.json(updatedUser);
  }
  catch (err) {
    res.json({ message: err });
  }
});

//DELETE SPECIFIC USER
app.delete('/api/users/:id', async (req, res) => {
  try {
    const removedUser = await User.remove({ id: parseInt(req.params.id) });
    res.json(removedUser);
  }
  catch (err) {
    res.json({ message: err });
  }
});
*/


//Listen on port
const port = 3000;
app.listen(port, () => console.log('Server running...'));
