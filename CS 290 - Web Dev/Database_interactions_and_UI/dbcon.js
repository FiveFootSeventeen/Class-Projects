var mysql = require('mysql');
var pool = mysql.createPool({
  connectionLimit : 10;
  host            : 'classmysql.engr.oregonstate.edu',
  user            : 'cs290_lenoja',
  password        : '1376',
  database        : 'cs290_lenoja'
});

module.exports.pool = pool;
