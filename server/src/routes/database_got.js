const express = require('express');
const router = express.Router();

const mysqlConnection  = require('../database.js');

// Volver un archivo a un commit posterior
router.get('/commit_posterior', (req, res) => {
  const { hash_commit, nombre_archivo} = req.body;
  mysqlConnection.query("SELECT diff.codigo_diff_posterior " +
              "FROM diff JOIN commit ON diff.relacion_commit = commit.id_commit " +
              "WHERE commit.hash_commit ='" + hash_commit + "' AND diff.nombre_archivo = '" + 
               nombre_archivo + "' " , {hash_commit, nombre_archivo}, (err, rows, fields) => {
    if(!err) {
      res.json(rows);
    } else {
      console.log(err);
    }
  });  
});

// Devolver un archivo a un commit anterior
router.get('/commit_anterior', (req, res) => {
  const { hash_commit, nombre_archivo} = req.body;
  mysqlConnection.query("SELECT diff.codigo_diff_anterior " +
              "FROM diff JOIN commit ON diff.relacion_commit = commit.id_commit " +
              "WHERE commit.hash_commit ='" + hash_commit + "' AND diff.nombre_archivo = '" + 
               nombre_archivo + "' " , {hash_commit, nombre_archivo}, (err, rows, fields) => {
    if(!err) {
      res.json(rows);
    } else {
      console.log(err);
    }
  });  
});

// Mostrar modificaciones de todos los archivos respecto a un commit anterior
router.get('/modificaciones_commit_anterior', (req, res) => {
  const { hash_commit } = req.body;
  mysqlConnection.query("SELECT diff.nombre_archivo " +
              "FROM diff JOIN commit ON diff.relacion_commit = commit.id_commit " +
              "WHERE commit.hash_commit ='" + hash_commit + "' " 
              , {hash_commit}, (err, rows, fields) => {
    if(!err) {
      res.json(rows);
    } else {
      console.log(err);
    }
  });  
});

// Mostrar agregados de todos los archivos respecto a un commit anterior
router.get('/agregados_commit_anterior', (req, res) => {
  const { hash_commit } = req.body;
  mysqlConnection.query("SELECT archivo.nombre_archivo " +
              "FROM archivo JOIN commit ON archivo.relacion_commit = commit.id_commit " +
              "WHERE commit.hash_commit ='" + hash_commit + "' " 
              , {hash_commit}, (err, rows, fields) => {
    if(!err) {
      res.json(rows);
    } else {
      console.log(err);
    }
  });  
});

// Mostrar modificaciones respecto a un commit 
router.get('/modificaciones_commit', (req, res) => {
  const { hash_commit, nombre_archivo} = req.body;
  mysqlConnection.query("SELECT diff.nombre_archivo " +
              "FROM diff JOIN commit ON diff.relacion_commit = commit.id_commit " +
              "WHERE commit.hash_commit ='" + hash_commit + "' AND diff.nombre_archivo = '" + 
               nombre_archivo + "' " , {hash_commit, nombre_archivo}, (err, rows, fields) => {
    if(!err) {
      res.json(rows);
    } else {
      console.log(err);
    }
  });  
});

// Mostrar agregados respecto a un commit
router.get('/agregados_commit', (req, res) => {
  const { hash_commit, nombre_archivo} = req.body;
  mysqlConnection.query("SELECT archivo.nombre_archivo " +
              "FROM archivo JOIN commit ON archivo.relacion_commit = commit.id_commit " +
              "WHERE commit.hash_commit ='" + hash_commit + "' AND archivo.nombre_archivo = '" + 
               nombre_archivo + "' " , {hash_commit, nombre_archivo}, (err, rows, fields) => {
    if(!err) {
      res.json(rows);
    } else {
      console.log(err);
    }
  });  
});

// INSERT AN NEW COMMIT
router.post('/commit', (req, res) => {
  const {hash_commit, comentario} = req.body;
  mysqlConnection.query('INSERT INTO commit SET?', {hash_commit, comentario}, (err, rows, fields) => {
    if(!err) {
      res.json({status: 'Commit Saved'});
    } else {
      console.log("err");
    }
  });
});

// INSERT AN NEW ARCHIVO
router.post('/archivo', (req, res) => {
  const {nombre_archivo, codigo_huffman, relacion_commit} = req.body;
  mysqlConnection.query('INSERT INTO archivo SET?', {nombre_archivo, codigo_huffman, relacion_commit}, (err, rows, fields) => {
    if(!err) {
      res.json({status: 'Archivo Saved'});
    } else {
      console.log("err");
    }
  });
});

// INSERT AN NEW DIFF
router.post('/diff', (req, res) => {
  const {nombre_archivo, codigo_diff_anterior, codigo_diff_siguiente, checksum, relacion_commit} = req.body;
  mysqlConnection.query('INSERT INTO diff SET?', {nombre_archivo, codigo_diff_anterior, codigo_diff_siguiente, checksum, relacion_commit}, (err, rows, fields) => {
    if(!err) {
      res.json({status: 'Diff Saved'});
    } else {
      console.log("err_diff");
    }
  });
});

// DELETE An Employee
router.delete('/:id', (req, res) => {
  const { id } = req.params;
  mysqlConnection.query('DELETE FROM employee WHERE id = ?', [id], (err, rows, fields) => {
    if(!err) {
      res.json({status: 'Employee Deleted'});
    } else {
      console.log(err);
    }
  });
});

// UPDATE An Employee
router.put('/:id', (req, res) => {
  const { name, salary } = req.body;
  const { id } = req.params;
  mysqlConnection.query('UPDATE employee SET? WHERE id = ?', [{name, salary}, id], (err, rows, fields) => {
    if(!err) {
      res.json({status: 'Employee Updated'});
    } else {
      console.log(err);
    }
  });
});


module.exports = router;
