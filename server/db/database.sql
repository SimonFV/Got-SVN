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
  codigo_huffman VARCHAR(128) NOT NULL,
  relacion_commit INT NOT NULL, 
  FOREIGN KEY (relacion_commit) REFERENCES commit(id_commit)
);

-- Crear primer commit

INSERT INTO commit (hash_commit, comentario)
  values ('###', 'primer commit');

INSERT INTO archivo (nombre_archivo, codigo_huffman, relacion_commit)
  values
  ('.gotignore', '100001', '1'), 
  ('a.cpp', '101011', '1'),
  ('b.cpp', '100010', '1');


-- Crear segundo commit

INSERT INTO commit (hash_commit, comentario)
  values ('$$$', 'segundo commit');

INSERT INTO diff (nombre_archivo, codigo_diff_anterior, codigo_diff_posterior, checksum, relacion_commit)
  values 
  ('a.cpp', '9d', '9d', '010111', '2'),
  ('b.cpp', '9d', '8d-10a', '101011', '2');

INSERT INTO archivo (nombre_archivo, codigo_huffman, relacion_commit)
  values
  ('c.cpp', '101011', '2');

-- Crear tercer commit

INSERT INTO commit (hash_commit, comentario)
  values ('&&&', 'tercer commit');

INSERT INTO diff (nombre_archivo, codigo_diff_anterior, codigo_diff_posterior, checksum, relacion_commit)
  values 
  ('a.cpp', '9da', '9sd', '0110111', '3'),
  ('b.cpp', '88d-10a', '2', '1011011', '3');

INSERT INTO archivo (nombre_archivo, codigo_huffman, relacion_commit)
  values
  ('d.cpp', '101011', '3');

select * from commit;
select * from diff;
select * from archivo;

-- Devolver un archivo a un commit anterior

SELECT diff.codigo_diff_anterior
       FROM diff JOIN commit ON diff.relacion_commit = commit.id_commit
       WHERE commit.hash_commit = '&&&'
	 AND diff.nombre_archivo = 'a.cpp';

-- Mostrar modificaciones de todos los archivos respecto a un commit anterior  

SELECT diff.nombre_archivo AS Modificaciones
       FROM diff JOIN commit ON diff.relacion_commit = commit.id_commit
   	 WHERE commit.hash_commit = '&&&';

-- Mostrar agregados de todos los archivos respecto a un commit anterior  

SELECT archivo.nombre_archivo AS Agregados
       FROM archivo JOIN commit ON archivo.relacion_commit = commit.id_commit
       WHERE commit.hash_commit = '&&&';

-- Mostrar modificaciones respecto a un commit 

SELECT diff.nombre_archivo AS Modificaciones
       FROM diff JOIN commit ON diff.relacion_commit = commit.id_commit
   	 WHERE commit.hash_commit = '&&&'
	 AND diff.nombre_archivo = 'b.cpp';

-- Mostrar agregados respecto a un commit

SELECT archivo.nombre_archivo AS Agregados
       FROM archivo JOIN commit ON archivo.relacion_commit = commit.id_commit
       WHERE commit.hash_commit = '&&&'
	 AND archivo.nombre_archivo = 'd.cpp';


UPDATE diff SET codigo_diff_anterior = 'DDD' WHERE id_diff = '1';