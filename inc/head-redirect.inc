<title>Redirecting to chart...</title>

<?php

$idstring = $_POST['key'].$_POST['feedid'].$_POST['streamid'].$_POST['limit'].$_POST['title'].
	    $_POST['xlabel'].$_POST['ylabel'].$_POST['startdate'].$_POST['starttime'].
	    $_POST['enddate'].$_POST['endtime'].$_POST['color'].$_POST['bgcolor'].$_POST['tgcolor'];
	    $idstring=md5($idstring);
echo $_POST['color'];
include('config.php');

$cdb = new couchdb($couchdbserver,$couchdbport);
$ress=$cdb->send("GET", "/".$dbname."/".$idstring);
if (strpos($ress, "missing")!==false){
   echo "I don't know this document<br/>";
   $jsons = '{ "_id":"'.$idstring.'", "key":"'.$_POST['key'].
   '", "feedid":"'.$_POST['feedid'].'", "streamid":"'.$_POST['streamid'].
   '", "feedtype":"'.$_POST['feedtype'].'", "limit": "'.$_POST['limit'].
   '", "title":"'.$_POST['title'].'", "xlabel":"'.$_POST['xlabel'].
   '", "ylabel":"'.$_POST['ylabel'].
   '", "startdate":"'.$_POST['startdate'].
   '", "starttime":"'.$_POST['starttime'].
   '", "enddate":"'.$_POST['enddate'].
   '", "endtime":"'.$_POST['endtime'].
   '", "color":"'.$_POST['color'].
   '", "bgcolor":"'.$_POST['bgcolor'].
   '", "tgcolor":"'.$_POST['tgcolor'].
   '"}';
   echo "sending ".$jsons."</br>";
   $ress=$cdb->send("PUT", "/$dbname/".$idstring, $jsons);
   echo $ress;
} else {
  echo "I know this document<br/>";
  echo $ress;
}

?>

<meta http-equiv="refresh" content="0; url=?id=<?php echo $idstring; ?>" />
</head>

<body>
Redirecting to chart...

