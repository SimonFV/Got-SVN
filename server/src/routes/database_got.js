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
      res.status(200).json(rows);
    } else {
      res.status(500).send('Operacion fallida al solicitar ir a commit posterior!');
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
      res.status(200).json(rows);
    } else {
      res.status(500).send('Operacion fallida al solicitar devolver commit anterior!');
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
      res.status(200).json(rows);
    } else {
      res.status(500).send('Operacion fallida al solicitar modificacion commit anterior!');
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
      res.status(200).json(rows);
    } else {
      res.status(500).send('Operacion fallida al solicitar agregados commit anterior!');
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
      res.status(200).json(rows);
    } else {
      res.status(500).send('Operacion fallida al solicitar modificaciones commit!');
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
      res.status(200).json(rows);
    } else {
      res.status(500).send('Operacion fallida al solicitar agregados commit!');
    }
  });  
});

// INSERT AN NEW COMMIT
router.post('/commit', (req, res) => {
  const {hash_commit, comentario} = req.body;
  mysqlConnection.query('INSERT INTO commit SET?', {hash_commit, comentario}, (err, rows, fields) => {
    if(!err) {
      res.status(200).send('Commit insertado!');
    } else {
      res.status(500).send('Operacion fallida al insertar commit!');
    }
  });
});

// INSERT AN NEW ARCHIVO
router.post('/archivo', (req, res) => {
  const {nombre_archivo, codigo_huffman, relacion_commit} = req.body;
  mysqlConnection.query('INSERT INTO archivo SET?', {nombre_archivo, codigo_huffman, relacion_commit}, (err, rows, fields) => {
    if(!err) {
      res.status(200).send('Archivo insertado!');
    } else {
      res.status(500).send('Operacion fallida al insertar archivo!');
    }
  });
});

// INSERT AN NEW DIFF
router.post('/diff', (req, res) => {
  const {nombre_archivo, codigo_diff_anterior, codigo_diff_siguiente, checksum, relacion_commit} = req.body;
  mysqlConnection.query('INSERT INTO diff SET?', {nombre_archivo, codigo_diff_anterior, codigo_diff_siguiente, checksum, relacion_commit}, (err, rows, fields) => {
    if(!err) {
      res.status(200).send('Diff insertado!');
    } else {
      res.status(500).send('Operacion fallida al insertar diff!');
    }
  });
});

// UPDATE An campo DIFF (codigo_diff_anterior)
router.put('/:id_diff', (req, res) => {
  const { codigo_diff_anterior } = req.body;
  const { id_diff } = req.params;
  console.log(codigo_diff_anterior);
  mysqlConnection.query('UPDATE diff SET codigo_diff_anterior = ? WHERE id_diff = ?', [codigo_diff_anterior, id_diff], (err, rows, fields) => {
    if(!err) {
      res.status(200).send('Diff actualizado!');
    } else {
      res.status(500).send('Operacion fallida al actualizar campo diff!');
    }
  });
});

// DELETE An Employee
/*router.delete('/:id', (req, res) => {
  const { id } = req.params;
  mysqlConnection.query('DELETE FROM employee WHERE id = ?', [id], (err, rows, fields) => {
    if(!err) {
      res.json({status: 'Employee Deleted'});
    } else {
      console.log(err);
    }
  });
});*/

module.exports = router;
