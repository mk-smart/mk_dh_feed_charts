<div id="main">
     <form action="" method="POST">
     <?php 
     if (isset($_GET['feedid'])) {?>
     	   <input type="text" name="feedid" id="feedid" placeholder="Feed ID" value="<?php echo $_GET['feedid'];?>"/><br/>
     <?php } else {?>
     	   <input type="text" name="feedid" id="feedid" placeholder="Feed ID"/><br/>
     <?php } ?>
	   <input type="hidden" name="feedtype" id="feedtype" value="sensors"/>
 	   <input type="text" name="streamid" id="streamid" placeholder="Stream ID (defaut: 0)"/><br/>
	   <input type="text" name="key" id="key" placeholder="API Key"/><br/>
	   <br/>
  	   <input type="text" name="limit" id="limit" placeholder="Number of datapoints (default: 100)"/><br/>	  	   
	   <strong>From:</strong><br/>
  	   <input type="date" name="startdate" id="startdate" placeholder="Start date (default: yesterday)"/><br/>
  	   <input type="time" name="starttime" id="starttime" placeholder="Start time (default: 24 hours ago1)"/><br/>
	   <input style="width: 40px; margin-left: 0px; padding-left: 0px;" type="radio" name="relativestart" value="day">last day</input>
	   <input style="width: 40px" type="radio" name="relativestart" value="week">last week</input>
	   <input style="width: 40px" type="radio" name="relativestart" value="month">last month</input>
	   <input style="width: 40px" type="radio" name="relativestart" value="year">last year</input><br/>
	   <strong>To:</strong><br/>
  	   <input type="date" name="enddate" id="enddate" placeholder="End date (default: today)"/><br/>
  	   <input type="time" name="endtime" id="endtime" placeholder="End time (default: now)"/><br/>	   
	   <br/>
	   <input type="text" name="title" id="title" placeholder="Chart title (default: none)"/><br/>
	   <input type="text" name="xlabel" id="xlabel" placeholder="Title of X axis (default: Timeline)"/><br/>
	   <input type="text" name="ylabel" id="ylabel" placeholder="Title of Y axis (default: Values)"/><br/>
	   <strong>Colours:</strong><br/>
	   <strong>Chart:</strong> 
	   <input style="width: 40px; height: 40px;" type="color" name="color" id="color" placeholder="Chart Color (default: Blue)" value="#6666ff"/>
	   <strong>Background:</strong> 
	   <input style="width: 40px; height: 40px;" type="color" name="bgcolor" id="bgcolor" placeholder="Background Color (default: White)" value="#ffffff"/>
	   <strong>Text/grid:</strong> 
	   <input style="width: 40px; height: 40px;" type="color" name="tgcolor" id="tgcolor" placeholder="Text and grid Color (default: Grey)" value="#666666"/>	   
	   <br/>
   	   <input type="submit" />
     </form>
</div>
