<?php
require_once(__DIR__ . "/config.php");
function connect()
{
	$db = pg_connect('host=$host_db port=$port_db user=$user_db password=$pass_db dbname=$dbname');
	return $db;
}
?>