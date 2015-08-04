<?php

include("inc/preamble.inc");

// if includes key, feed id and stream id, redirect to chart with code.
if (
    isset($_POST["key"]) &&
    isset($_POST["feedid"]) &&
    isset($_POST["feedtype"]) &&
    isset($_POST["streamid"])
    ) {
  include("inc/head-redirect.inc");
 } else if(isset($_GET['id']) || isset($_POST['id'])){
  include("inc/head-chart.inc");
  include("inc/chart.inc");
	 // get the key, feedid and streamid from couchdb
	 // create the javascript chart
	 // include the embed link (if not "embed" parameter)
 } else {
  include("inc/head-form.inc");
  include("inc/form.inc");
}

include("inc/footer.inc");

?>

