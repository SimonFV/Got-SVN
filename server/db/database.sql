create database DB_GOT;
use DB_GOT;

drop table diff;
drop table archivo;
drop table commit;

CREATE TABLE commit (
  id_commit INT PRIMARY KEY AUTO_INCREMENT,
  hash_commit VARCHAR(128) NOT NULL,
  comentario VARCHAR(128) NOT NULL
);

CREATE TABLE diff (
  id_diff INT PRIMARY KEY AUTO_INCREMENT,
  nombre_archivo VARCHAR(128) NOT NULL,
  codigo_diff_anterior VARCHAR(128) NOT NULL,
  codigo_diff_posterior VARCHAR(128) NOT NULL,
  checksum VARCHAR(128) NOT NULL,
  relacion_commit INT NOT NULL, 
  FOREIGN KEY (relacion_commit) REFERENCES commit(id_commit)
);

CREATE TABLE archivo (
  id_archivo INT PRIMARY KEY AUTO_INCREMENT,
  nombre_archivo VARCHAR(128) NOT NULL,
  codigo_huffman BLOB NOT NULL,
  simbolo_codigo VARCHAR(128) NOT NULL,
  relacion_commit INT NOT NULL, 
  FOREIGN KEY (relacion_commit) REFERENCES commit(id_commit)
);
