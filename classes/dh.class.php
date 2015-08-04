<?php

class dhstream {

    function dhstream($feedid, $streamid, $feedtype, $key) {
       $this->feedid = $feedid;
       $this->streamid = $streamid;
       $this->feedtype = $feedtype;
       if (strcmp($feedtype, "sensor")===0) $this->feedtype = "sensors";
       $this->key = $key;
    } 

    function useProxy($proxyURL){
       $this->proxyURL = $proxyURL;
    }
   
   function get($limit, $startdate, $enddate){
      $s = curl_init(); 
      $headers = array();
      $headers[] = "Accept: application/json";
      curl_setopt($s, CURLOPT_HTTPHEADER, $headers);       
      curl_setopt($s, CURLOPT_RETURNTRANSFER, true);		   
      $url = "https://api.beta.mksmart.org/$this->feedtype/feeds/$this->feedid/datastreams/$this->streamid/datapoints?limit=$limit&start=$startdate&end=$enddate";
      curl_setopt($s,CURLOPT_URL,$url);    
      curl_setopt($s, CURLOPT_USERPWD, $this->key.':');
      if (isset($this->proxyURL)){
            curl_setopt($s, CURLOPT_PROXY, $this->proxyURL);
      }
      $ress = curl_exec($s); 
      $status = curl_getinfo($s,CURLINFO_HTTP_CODE); 
      curl_close($s); 
      if ($status!==200){
         $o = new StdClass();
	 $o->type="Error";
	 $o->message="Could not access data stream";
	 $o->code=$status;
	 return $o;
      }
      return json_decode($ress);
   }
}

?>