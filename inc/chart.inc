
<?php
include('config.php');
// TODO: table option in additon to chart... (using datatables)

$cdb = new couchdb($couchdbserver,$couchdbport);
$ress=$cdb->send("GET", "/".$dbname."/".$_GET['id']);
$resj=json_decode($ress);

$dhs = new dhstream($resj->feedid, $resj->streamid, $resj->feedtype, $resj->key);
//$dhs->useProxy("wwwcache.open.ac.uk:80");
$today = new DateTime();
if (isset($resj->limit) && strcmp($resj->limit, "")!==0){
  $l = $resj->limit;
} else {
  $l = 100;
}
if (isset($resj->startdate) && strcmp($resj->startdate, "")!==0) {
   $sd= $resj->startdate;
} else {
   $yesterday=new Datetime();
   $yesterday->setTimeStamp(time()-(60*60*24));
   $sd= $yesterday->format('Y-m-d');
}
if (isset($resj->starttime) && strcmp($resj->starttime, "")!==0) {
   $sd.="T".$resj->starttime.$today->format("O");
} else {
  $sd.="T".$today->format("H:i:sO");
}
if (isset($resj->enddate) && strcmp($resj->enddate, "")!==0) {
   $ed= $resj->enddate;
} else {
   $ed= $today->format('Y-m-d');
}
if (isset($resj->endtime) && strcmp($resj->endtime, "")!==0) {
   $ed.="T".$resj->endtime.$today->format("O");
} else {
  $ed.="T".$today->format("H:i:sO");
}
$data = $dhs->get($l, $sd, $ed);

if (isset($resj->color) && strcmp($resj->color, "")!==0){
   $color=$resj->color;
} else {
   $color="#6666ff";
}
if (isset($resj->bgcolor) && strcmp($resj->bgcolor, "")!==0){
   $bgcolor=$resj->bgcolor;
} else {
   $bgcolor="#ffffff";
}
if (isset($resj->tgcolor) && strcmp($resj->tgcolor, "")!==0){
   $tgcolor=$resj->tgcolor;
} else {
   $tgcolor="#666666";
}
?>

<div id="chartContainer" style="height: 400px; width: 100%;"> </div>
<div id="message"> </div>

<script type="text/javascript">
window.onload = function () {
    <?php
       if (isset($data->type) && strcmp($data->type, "Error")===0){
    ?>
         document.getElementById("message").innerHTML = "Error: <?php echo $data->message; ?> - code <?php echo $data->code; ?>";
    <?php 
       } else {
   ?>
   
    CanvasJS.addColorSet("DHColorSet",["<?php echo $color; ?>"]); 

    var chart = new CanvasJS.Chart("chartContainer",
    {
      title:{
        <?php 
        if (isset($resj->title)) echo 'text: "'.$resj->title.'"';
	else echo 'text: ""';
	?>
    },
    colorSet: "DHColorSet",
    axisX:{
    <?php 
       if (isset($resj->xlabel) && strcmp($resj->xlabel, "")!==0) echo 'title: "'.$resj->xlabel.'"';
       else echo 'title: "Timeline"';
       ?>,
       gridThickness: 1, 
       gridColor: "<?php echo $tgcolor; ?>",
       titleFontColor: "<?php echo $tgcolor; ?>",
       labelFontColor: "<?php echo $tgcolor; ?>",
       tickColor: "<?php echo $tgcolor; ?>",
       lineColor: "<?php echo $tgcolor; ?>"
    },
    zoomEnabled: true, 
    backgroundColor: "<?php echo $bgcolor; ?>",
    axisY: {
    <?php 
       if (isset($resj->ylabel) && strcmp($resj->ylabel, "")!==0) echo 'title: "'.$resj->ylabel.'"';
       else echo 'title: "Values"';
       ?>,
       gridThickness: 1, 
       gridColor: "<?php echo $tgcolor; ?>",
       titleFontColor: "<?php echo $tgcolor; ?>",
       labelFontColor: "<?php echo $tgcolor; ?>",
       tickColor: "<?php echo $tgcolor; ?>",
       lineColor: "<?php echo $tgcolor; ?>"
    },
    data: [
    {        
        type: "area",
	// type: "spline",
        dataPoints: [
	<?php
	    $count = 0;
            foreach($data as $item){
	            echo "{ x: ".convertDate($item->time).", y: $item->value}";
		    $count++;
		    if ($count!==count($data)) echo ",";
	    }
	?>

        ]
    }
    ]
});
    chart.render();
    <?php } ?>
}
</script>

<?php

function convertDate($ds){
   $day = substr($ds,5,2);
   $month = substr($ds,8,3);
   if (strcmp($month, "Jan")===0) $month=0;
   if (strcmp($month, "Feb")===0) $month=1;
   if (strcmp($month, "Mar")===0) $month=2;
   if (strcmp($month, "Apr")===0) $month=3;
   if (strcmp($month, "May")===0) $month=4;
   if (strcmp($month, "Jun")===0) $month=5;
   if (strcmp($month, "Jul")===0) $month=6;
   if (strcmp($month, "Aug")===0) $month=7;
   if (strcmp($month, "Sep")===0) $month=8;
   if (strcmp($month, "Oct")===0) $month=9;
   if (strcmp($month, "Nov")===0) $month=10;
   if (strcmp($month, "Dec")===0) $month=11;
   $year = substr($ds,12,4);
   $hour = substr($ds,17,2);
   $minutes = substr($ds,20,2);
   $secs = substr($ds,23,2);
   return "new Date($year, $month, ".intval($day).", ".intval($hour).", ".intval($minutes).", ".intval($secs).")";
}
?>